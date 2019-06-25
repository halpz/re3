#include "common.h"
#include "patcher.h"
#include "BulletTraces.h"
#include "Clock.h"
#include "Draw.h"
#include "math/Matrix.h"
#include "ModelIndices.h"
#include "Replay.h"
#include "Pad.h"
#include "Pools.h"
#include "CutsceneMgr.h"
#include "Timer.h"
#include "Weather.h"
#include "Font.h"
#include "Text.h"

uint8 &CReplay::Mode = *(uint8*)0x95CD5B;
CAddressInReplayBuffer &CReplay::Record = *(CAddressInReplayBuffer*)0x942F7C;
CAddressInReplayBuffer &CReplay::Playback = *(CAddressInReplayBuffer*)0x8F5F48;
uint8 *&CReplay::pBuf0 = *(uint8**)0x8E2C64;
CAutomobile *&CReplay::pBuf1 = *(CAutomobile**)0x8E2C68;
uint8 *&CReplay::pBuf2 = *(uint8**)0x8E2C6C;
CPlayerPed *&CReplay::pBuf3 = *(CPlayerPed**)0x8E2C70;
uint8 *&CReplay::pBuf4 = *(uint8**)0x8E2C74;
CCutsceneHead *&CReplay::pBuf5 = *(CCutsceneHead**)0x8E2C78;
uint8 *&CReplay::pBuf6 = *(uint8**)0x8E2C80;
CPtrNode *&CReplay::pBuf7 = *(CPtrNode**)0x8E2C84;
uint8 *&CReplay::pBuf8 = *(uint8**)0x8E2C54;
CEntryInfoNode *&CReplay::pBuf9 = *(CEntryInfoNode**)0x8E2C58;
uint8 *&CReplay::pBuf10 = *(uint8**)0x8F2C28;
CDummyPed *&CReplay::pBuf11 = *(CDummyPed**)0x8F2C2C;
CBlip *&CReplay::pRadarBlips = *(CBlip**)0x8F29F8;
CCamera *&CReplay::pStoredCam = *(CCamera**)0x8F2C34;
CSector *&CReplay::pWorld1 = *(CSector**)0x8E29C4;
CReference *&CReplay::pEmptyReferences = *(CReference**)0x8F256C;
CStoredDetailedAnimationState *&CReplay::pPedAnims = *(CStoredDetailedAnimationState**)0x8F6260;
CPickup *&CReplay::pPickups = *(CPickup**)0x8F1A48;
CReference *&CReplay::pReferences = *(CReference**)0x880FAC;
uint8(&CReplay::BufferStatus)[8] = *(uint8(*)[8])*(uintptr*)0x8804D8;
uint8(&CReplay::Buffers)[8][100000] = *(uint8(*)[8][100000])*(uintptr*)0x779958;
bool &CReplay::bPlayingBackFromFile = *(bool*)0x95CD58;
bool &CReplay::bReplayEnabled = *(bool*)0x617CAC;
uint32 &CReplay::SlowMotion = *(uint32*)0x9414D4;
uint32 &CReplay::FramesActiveLookAroundCam = *(uint32*)0x880F84;
bool &CReplay::bDoLoadSceneWhenDone = *(bool*)0x95CD76;

void PrintElementsInPtrList(void) 
{
	for (CPtrNode* node = CWorld::GetBigBuildingList(LEVEL_NONE).first; node; node = node->next) {
		// Most likely debug print was present here
	}
}

void CReplay::Init(void)
{
	pBuf0 = nil;
	pBuf1 = nil;
	pBuf2 = nil;
	pBuf3 = nil;
	pBuf4 = nil;
	pBuf5 = nil;
	pBuf6 = nil;
	pBuf7 = nil;
	pBuf8 = nil;
	pBuf9 = nil;
	pBuf10 = nil;
	pBuf11 = nil;
	pRadarBlips = nil;
	pStoredCam = nil;
	pWorld1 = nil;
	pEmptyReferences = nil;
	pPedAnims = nil;
	pPickups = nil;
	pReferences = nil;
	Mode = MODE_RECORD;
	Playback.m_nOffset = 0;
	Playback.m_pBase = nil;
	Playback.m_bSlot = 0;
	Record.m_nOffset = 0;
	Record.m_pBase = nil;
	Record.m_bSlot = 0;
	for (int i = 0; i < 8; i++)
		BufferStatus[i] = REPLAYBUFFER_UNUSED;
	Record.m_bSlot = 0;
	Record.m_pBase = Buffers[0];
	BufferStatus[0] = REPLAYBUFFER_RECORD;
	Buffers[0][Record.m_nOffset] = REPLAYPACKET_END;
	bPlayingBackFromFile = false;
	bReplayEnabled = true;
	SlowMotion = 1;
	FramesActiveLookAroundCam = 0;
	bDoLoadSceneWhenDone = false;
}

void CReplay::DisableReplays(void)
{
	bReplayEnabled = false;
}

void CReplay::EnableReplays(void)
{
	bReplayEnabled = true;
}

void PlayReplayFromHD(void);
void CReplay::Update(void)
{
	if (CCutsceneMgr::IsCutsceneProcessing() || CTimer::GetIsPaused())
		return;
	switch (Mode){
	case MODE_RECORD:
		RecordThisFrame();
		break;
	case MODE_PLAYBACK:
		PlaybackThisFrame();
		break;
	}
	if (CDraw::FadeValue || !bReplayEnabled)
		return;
	if (Mode == MODE_PLAYBACK){
		if (CPad::NewKeyState.F[0] && !CPad::OldKeyState.F[0])
			FinishPlayback();
	}
	else if (Mode == MODE_RECORD){
		if (CPad::NewKeyState.F[0] && !CPad::OldKeyState.F[0])
			TriggerPlayback(REPLAYCAMMODE_ASSTORED, 0.0f, 0.0f, 0.0f, false);
		if (CPad::NewKeyState.F[1] && !CPad::OldKeyState.F[1])
			SaveReplayToHD();
		if (CPad::NewKeyState.F[2] && !CPad::OldKeyState.F[2])
			PlayReplayFromHD();
	}
}

#if 0
WRAPPER void CReplay::RecordThisFrame(void) { EAXJMP(0x5932B0); }
#else

void CReplay::RecordThisFrame(void)
{
	tGeneralPacket* general = (tGeneralPacket*)&Record.m_pBase[Record.m_nOffset];
	general->type = REPLAYPACKET_GENERAL;
	general->camera_pos.CopyOnlyMatrix(&TheCamera.GetMatrix());
	FindPlayerCoors(general->player_pos);
	general->in_rcvehicle = CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle ? true : false;
	Record.m_nOffset += sizeof(*general);
	tClockPacket* clock = (tClockPacket*)&Record.m_pBase[Record.m_nOffset];
	clock->type = REPLAYPACKET_CLOCK;
	clock->hours = CClock::GetHours();
	clock->minutes = CClock::GetMinutes();
	Record.m_nOffset += sizeof(*clock);
	tWeatherPacket* weather = (tWeatherPacket*)&Record.m_pBase[Record.m_nOffset];
	weather->type = REPLAYPACKET_WEATHER;
	weather->old_weather = CWeather::OldWeatherType;
	weather->new_weather = CWeather::NewWeatherType;
	weather->interpolation = CWeather::InterpolationValue;
	Record.m_nOffset += sizeof(*weather);
	tTimerPacket* timer = (tTimerPacket*)&Record.m_pBase[Record.m_nOffset];
	timer->type = REPLAYPACKET_TIMER;
	timer->timer = CTimer::GetTimeInMilliseconds();
	Record.m_nOffset += sizeof(*timer);
	CVehiclePool* vehicles = CPools::GetVehiclePool();
	for (int i = 0; i < vehicles->GetSize(); i++){
		CVehicle* v = vehicles->GetSlot(i);
		if (v && v->m_rwObject && v->GetModelIndex() != MI_AIRTRAIN && v->GetModelIndex() != MI_TRAIN)
			StoreCarUpdate(v, i);
	}
	CPedPool* peds = CPools::GetPedPool();
	for (int i = 0; i < peds->GetSize(); i++) {
		CPed* p = peds->GetSlot(i);
		if (!p || !p->m_rwObject)
			continue;
		if (!p->bRecordedForReplay){
			tPedHeaderPacket* ph = (tPedHeaderPacket*)&Record.m_pBase[Record.m_nOffset];
			ph->type = REPLAYPACKET_PED_HEADER;
			ph->index = i;
			ph->mi = p->GetModelIndex();
			ph->pedtype = p->m_nPedType;
			Record.m_nOffset += sizeof(*ph);
			p->bRecordedForReplay = true;
		}
		StorePedUpdate(p, i);
	}
	for (uint8 i = 0; i < 16; i++){
		if (!CBulletTraces::aTraces[i].m_bInUse)
			continue;
		tBulletTracePacket* bt = (tBulletTracePacket*)&Record.m_pBase[Record.m_nOffset];
		bt->type = REPLAYPACKET_BULLETTRACES;
		bt->index = i;
		bt->frames = CBulletTraces::aTraces[i].m_bFramesInUse;
		bt->lifetime = CBulletTraces::aTraces[i].m_bLifeTime;
		bt->inf = CBulletTraces::aTraces[i].m_vecInf;
		bt->sup = CBulletTraces::aTraces[i].m_vecSup;
		Record.m_nOffset += sizeof(*bt);
	}
	tEndOfFramePacket* eof = (tEndOfFramePacket*)&Record.m_pBase[Record.m_nOffset];
	eof->type = REPLAYPACKET_ENDOFFRAME;
	Record.m_nOffset += sizeof(*eof);
	if (Record.m_nOffset <= 97000){
		/* Unsafe assumption which can cause buffer overflow
		 * if size of next frame exceeds 3000 bytes.
		 * Most notably it causes various timecyc errors. */
		Record.m_pBase[Record.m_nOffset] = REPLAYPACKET_END;
		return;
	}
	Record.m_pBase[Record.m_nOffset] = REPLAYPACKET_END;
	BufferStatus[Record.m_bSlot] = REPLAYBUFFER_PLAYBACK;
	Record.m_bSlot = (Record.m_bSlot + 1) % 8;
	BufferStatus[Record.m_bSlot] = REPLAYBUFFER_RECORD;
	Record.m_pBase = Buffers[Record.m_bSlot];
	Record.m_nOffset = 0;
	*Record.m_pBase = REPLAYPACKET_END;
	MarkEverythingAsNew();
}
#endif
WRAPPER void CReplay::StorePedUpdate(CPed *ped, int id) { EAXJMP(0x5935B0); }
WRAPPER void CReplay::StorePedAnimation(CPed *ped, CStoredAnimationState *state) { EAXJMP(0x593670); }
WRAPPER void CReplay::StoreDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state) { EAXJMP(0x593BB0); }
WRAPPER void CReplay::ProcessPedUpdate(CPed *ped, float interpolation, CAddressInReplayBuffer *buffer) { EAXJMP(0x594050); }
WRAPPER void CReplay::RetrievePedAnimation(CPed *ped, CStoredAnimationState *state) { EAXJMP(0x5942A0); }
WRAPPER void CReplay::RetrieveDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state) { EAXJMP(0x5944B0); }
WRAPPER void CReplay::PlaybackThisFrame(void) { EAXJMP(0x5946B0); }
WRAPPER void CReplay::StoreCarUpdate(CVehicle *vehicle, int id) { EAXJMP(0x5947F0); }
WRAPPER void CReplay::ProcessCarUpdate(CVehicle *vehicle, float interpolation, CAddressInReplayBuffer *buffer) { EAXJMP(0x594D10); }
WRAPPER bool CReplay::PlayBackThisFrameInterpolation(CAddressInReplayBuffer *buffer, float interpolation, uint32 *pTimer) { EAXJMP(0x595240); }
WRAPPER void CReplay::FinishPlayback(void) { EAXJMP(0x595B20); }
WRAPPER void CReplay::Shutdown(void) { EAXJMP(0x595BD0); }
WRAPPER void CReplay::ProcessReplayCamera(void) { EAXJMP(0x595C40); }
WRAPPER void CReplay::TriggerPlayback(uint8 cam_mode, float cam_x, float cam_y, float cam_z, bool load_scene) { EAXJMP(0x596030); }
WRAPPER void CReplay::StoreStuffInMem(void) { EAXJMP(0x5961F0); }
WRAPPER void CReplay::RestoreStuffFromMem(void) { EAXJMP(0x5966E0); }
WRAPPER void CReplay::EmptyPedsAndVehiclePools(void) { EAXJMP(0x5970E0); }
WRAPPER void CReplay::EmptyAllPools(void) { EAXJMP(0x5971B0); }
WRAPPER void CReplay::MarkEverythingAsNew(void) { EAXJMP(0x597280); }
WRAPPER void CReplay::SaveReplayToHD(void) { EAXJMP(0x597330); }
WRAPPER void PlayReplayFromHD(void) { EAXJMP(0x597420); }
WRAPPER void CReplay::StreamAllNecessaryCarsAndPeds(void) { EAXJMP(0x597560); }
WRAPPER void CReplay::FindFirstFocusCoordinate(CVector *coord) { EAXJMP(0x5975E00); }
WRAPPER bool CReplay::ShouldStandardCameraBeProcessed(void) { EAXJMP(0x597680); }
WRAPPER void CReplay::ProcessLookAroundCam(void) { EAXJMP(0x5976C0); }
WRAPPER size_t CReplay::FindSizeOfPacket(uint8 type) { EAXJMP(0x597CC0); }

#if 0
WRAPPER void CReplay::Display(void) { EAXJMP(0x595EE0); }
#else
void CReplay::Display()
{
	if (CReplay::IsPlayingBack() && CTimer::GetFrameCounter() + 1 & 0x20) {
		CFont::SetPropOn();
		CFont::SetBackgroundOff();
		CFont::SetScale(SCREEN_SCALE_X(1.5f), SCREEN_SCALE_Y(1.5f));
		CFont::SetAlignment(ALIGN_LEFT);
		CFont::SetColor(CRGBA(255, 255, 200, 200));
		CFont::SetFontStyle(FONT_BANK);
		CFont::PrintString(SCREEN_SCALE_X(63.5f), SCREEN_SCALE_Y(30.0f), TheText.Get("REPLAY"));
	}
}
#endif

STARTPATCHES
InjectHook(0x592FC0, PrintElementsInPtrList, PATCH_JUMP);
InjectHook(0x592FE0, CReplay::Init, PATCH_JUMP);
InjectHook(0x593150, CReplay::DisableReplays, PATCH_JUMP);
InjectHook(0x593150, CReplay::EnableReplays, PATCH_JUMP);
InjectHook(0x593170, CReplay::Update, PATCH_JUMP);
ENDPATCHES
