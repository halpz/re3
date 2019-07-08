#include "common.h"
#include "patcher.h"
#include "AnimBlendAssociation.h"
#include "Boat.h"
#include "SpecialFX.h"
#include "CarCtrl.h"
#include "CivilianPed.h"
#include "Clock.h"
#include "DMAudio.h"
#include "Draw.h"
#include "FileMgr.h"
#include "Heli.h"
#include "main.h"
#include "Matrix.h"
#include "ModelIndices.h"
#include "ModelInfo.h"
#include "Object.h"
#include "Pad.h"
#include "Phones.h"
#include "Pickups.h"
#include "Plane.h"
#include "Pools.h"
#include "Population.h"
#include "Replay.h"
#include "RpAnimBlend.h"
#include "RwHelper.h"
#include "CutsceneMgr.h"
#include "Skidmarks.h"
#include "Streaming.h"
#include "Timer.h"
#include "Train.h"
#include "Weather.h"
#include "Zones.h"
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
uint8 *&CReplay::pRadarBlips = *(uint8**)0x8F29F8;
uint8 *&CReplay::pStoredCam = *(uint8**)0x8F2C34;
uint8 *&CReplay::pWorld1 = *(uint8**)0x8E29C4;
CReference *&CReplay::pEmptyReferences = *(CReference**)0x8F256C;
CStoredDetailedAnimationState *&CReplay::pPedAnims = *(CStoredDetailedAnimationState**)0x8F6260;
uint8 *&CReplay::pPickups = *(uint8**)0x8F1A48;
uint8 *&CReplay::pReferences = *(uint8**)0x880FAC;
uint8(&CReplay::BufferStatus)[8] = *(uint8(*)[8])*(uintptr*)0x8804D8;
uint8(&CReplay::Buffers)[8][100000] = *(uint8(*)[8][100000])*(uintptr*)0x779958;
bool &CReplay::bPlayingBackFromFile = *(bool*)0x95CD58;
bool &CReplay::bReplayEnabled = *(bool*)0x617CAC;
uint32 &CReplay::SlowMotion = *(uint32*)0x9414D4;
uint32 &CReplay::FramesActiveLookAroundCam = *(uint32*)0x880F84;
bool &CReplay::bDoLoadSceneWhenDone = *(bool*)0x95CD76;
CPtrList &CReplay::WorldPtrList = *(CPtrList*)0x880F90;
CPtrList &CReplay::BigBuildingPtrList = *(CPtrList*)0x941284;
CWanted &CReplay::PlayerWanted = *(CWanted*)0x8F6278;
CPlayerInfo &CReplay::PlayerInfo = *(CPlayerInfo*)0x8F5840;
uint32 &CReplay::Time1 = *(uint32*)0x8F29DC;
uint32 &CReplay::Time2 = *(uint32*)0x8F29D0;
uint32 &CReplay::Time3 = *(uint32*)0x8F29D4;
uint32 &CReplay::Time4 = *(uint32*)0x8F29C8;
uint32 &CReplay::Frame = *(uint32*)0x8F2554;
uint8 &CReplay::ClockHours = *(uint8*)0x95CDC5;
uint8 &CReplay::ClockMinutes = *(uint8*)0x95CDA2;
uint16 &CReplay::OldWeatherType = *(uint16*)0x95CCEA;
uint16 &CReplay::NewWeatherType = *(uint16*)0x95CC6E;
float &CReplay::WeatherInterpolationValue = *(float*)0x8F1A28;
float &CReplay::TimeStepNonClipped = *(float*)0x8F5FF4;
float &CReplay::TimeStep = *(float*)0x8F2C24;
float &CReplay::TimeScale = *(float*)0x880E20;
float &CReplay::CameraFixedX = *(float*)0x943054;
float &CReplay::CameraFixedY = *(float*)0x943058;
float &CReplay::CameraFixedZ = *(float*)0x94305C;
int32 &CReplay::OldRadioStation = *(int32*)0x94151C;
int8 &CReplay::CameraMode = *(int8*)0x95CD5F;
bool &CReplay::bAllowLookAroundCam = *(bool*)0x95CDCD;
float &CReplay::LoadSceneX = *(float*)0x880F9C;
float &CReplay::LoadSceneY = *(float*)0x880F98;
float &CReplay::LoadSceneZ = *(float*)0x880F94;
float &CReplay::CameraFocusX = *(float*)0x942F5C;
float &CReplay::CameraFocusY = *(float*)0x942F74;
float &CReplay::CameraFocusZ = *(float*)0x942F58;
bool &CReplay::bPlayerInRCBuggy = *(bool*)0x95CDC3;
float &CReplay::fDistanceLookAroundCam = *(float*)0x885B44;
float &CReplay::fBetaAngleLookAroundCam = *(float*)0x94072C;
float &CReplay::fAlphaAngleLookAroundCam = *(float*)0x8F2A0C;

static void(*(&CBArray)[30])(CAnimBlendAssociation*, void*) = *(void(*(*)[30])(CAnimBlendAssociation*, void*))*(uintptr*)0x61052C;
static void(*CBArray_RE3[])(CAnimBlendAssociation*, void*) =
{
	nil, &CPed::PedGetupCB, &CPed::PedStaggerCB, &CPed::PedEvadeCB, &CPed::FinishDieAnimCB,
	&CPed::FinishedWaitCB, &CPed::FinishLaunchCB, &CPed::FinishHitHeadCB, &CPed::PedAnimGetInCB, &CPed::PedAnimDoorOpenCB,
	&CPed::PedAnimPullPedOutCB, &CPed::PedAnimDoorCloseCB, &CPed::SetInCarCB, &CPed::PedSetOutCarCB, &CPed::PedAnimAlignCB,
	&CPed::PedSetDraggedOutCarCB, &CPed::PedAnimStepOutCarCB, &CPed::PedSetInTrainCB, &CPed::PedSetOutTrainCB, &CPed::FinishedAttackCB,
	&CPed::FinishFightMoveCB, &PhonePutDownCB, &PhonePickUpCB, &CPed::PedAnimDoorCloseRollingCB, &CPed::FinishJumpCB,
	&CPed::PedLandCB, &FinishFuckUCB, &CPed::RestoreHeadingRateCB, &CPed::PedSetQuickDraggedOutCarPositionCB, &CPed::PedSetDraggedOutCarPositionCB
};

#if 0
WRAPPER uint8 FindCBFunctionID(void(*f)(CAnimBlendAssociation*, void*)) { EAXJMP(0x584E70); }
#else
static uint8 FindCBFunctionID(void(*f)(CAnimBlendAssociation*, void*))
{
	for (int i = 0; i < sizeof(CBArray) / sizeof(*CBArray); i++){
		if (CBArray[i] == f)
			return i;
	}
	for (int i = 0; i < sizeof(CBArray_RE3) / sizeof(*CBArray_RE3); i++) {
		if (CBArray_RE3[i] == f)
			return i;
	}
	return 0;
}
#endif

static void(*FindCBFunction(uint8 id))(CAnimBlendAssociation*, void*)
{
	return CBArray_RE3[id];
}

#if 0
WRAPPER static void ApplyPanelDamageToCar(uint32, CAutomobile*, bool) { EAXJMP(0x584EA0); }
#else
static void ApplyPanelDamageToCar(uint32 panels, CAutomobile* vehicle, bool flying)
{
	if(vehicle->Damage.GetPanelStatus(VEHPANEL_FRONT_LEFT) != CDamageManager::GetPanelStatus(panels, VEHPANEL_FRONT_LEFT)){
		vehicle->Damage.SetPanelStatus(VEHPANEL_FRONT_LEFT, CDamageManager::GetPanelStatus(panels, VEHPANEL_FRONT_LEFT));
		vehicle->SetPanelDamage(CAR_WING_LF, VEHPANEL_FRONT_LEFT, flying);
	}
	if(vehicle->Damage.GetPanelStatus(VEHPANEL_FRONT_RIGHT) != CDamageManager::GetPanelStatus(panels, VEHPANEL_FRONT_RIGHT)){
		vehicle->Damage.SetPanelStatus(VEHPANEL_FRONT_RIGHT, CDamageManager::GetPanelStatus(panels, VEHPANEL_FRONT_RIGHT));
		vehicle->SetPanelDamage(CAR_WING_RF, VEHPANEL_FRONT_RIGHT, flying);
	}
	if(vehicle->Damage.GetPanelStatus(VEHPANEL_REAR_LEFT) != CDamageManager::GetPanelStatus(panels, VEHPANEL_REAR_LEFT)){
		vehicle->Damage.SetPanelStatus(VEHPANEL_REAR_LEFT, CDamageManager::GetPanelStatus(panels, VEHPANEL_REAR_LEFT));
		vehicle->SetPanelDamage(CAR_WING_LR, VEHPANEL_REAR_LEFT, flying);
	}
	if(vehicle->Damage.GetPanelStatus(VEHPANEL_REAR_RIGHT) != CDamageManager::GetPanelStatus(panels, VEHPANEL_REAR_RIGHT)){
		vehicle->Damage.SetPanelStatus(VEHPANEL_REAR_RIGHT, CDamageManager::GetPanelStatus(panels, VEHPANEL_REAR_RIGHT));
		vehicle->SetPanelDamage(CAR_WING_RR, VEHPANEL_REAR_RIGHT, flying);
	}
	if(vehicle->Damage.GetPanelStatus(VEHPANEL_WINDSCREEN) != CDamageManager::GetPanelStatus(panels, VEHPANEL_WINDSCREEN)){
		vehicle->Damage.SetPanelStatus(VEHPANEL_WINDSCREEN, CDamageManager::GetPanelStatus(panels, VEHPANEL_WINDSCREEN));
		vehicle->SetPanelDamage(CAR_WINDSCREEN, VEHPANEL_WINDSCREEN, flying);
	}
	if(vehicle->Damage.GetPanelStatus(VEHBUMPER_FRONT) != CDamageManager::GetPanelStatus(panels, VEHBUMPER_FRONT)){
		vehicle->Damage.SetPanelStatus(VEHBUMPER_FRONT, CDamageManager::GetPanelStatus(panels, VEHBUMPER_FRONT));
		vehicle->SetPanelDamage(CAR_BUMP_FRONT, VEHBUMPER_FRONT, flying);
	}
	if(vehicle->Damage.GetPanelStatus(VEHBUMPER_REAR) != CDamageManager::GetPanelStatus(panels, VEHBUMPER_REAR)){
		vehicle->Damage.SetPanelStatus(VEHBUMPER_REAR, CDamageManager::GetPanelStatus(panels, VEHBUMPER_REAR));
		vehicle->SetPanelDamage(CAR_BUMP_REAR, VEHBUMPER_REAR, flying);
	}
}
#endif

void PrintElementsInPtrList(void) 
{
	for (CPtrNode* node = CWorld::GetBigBuildingList(LEVEL_NONE).first; node; node = node->next) {
		/* Most likely debug print was present here */
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
	general->player_pos = FindPlayerCoors();
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
		if (!p->bHasAlreadyBeenRecorded){
			tPedHeaderPacket* ph = (tPedHeaderPacket*)&Record.m_pBase[Record.m_nOffset];
			ph->type = REPLAYPACKET_PED_HEADER;
			ph->index = i;
			ph->mi = p->GetModelIndex();
			ph->pedtype = p->m_nPedType;
			Record.m_nOffset += sizeof(*ph);
			p->bHasAlreadyBeenRecorded = true;
		}
		StorePedUpdate(p, i);
	}
	for (uint8 i = 0; i < 16; i++){
		if (!CBulletTraces::aTraces[i].m_bInUse)
			continue;
		tBulletTracePacket* bt = (tBulletTracePacket*)&Record.m_pBase[Record.m_nOffset];
		bt->type = REPLAYPACKET_BULLET_TRACES;
		bt->index = i;
		bt->frames = CBulletTraces::aTraces[i].m_framesInUse;
		bt->lifetime = CBulletTraces::aTraces[i].m_lifeTime;
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

#if 0
WRAPPER void CReplay::StorePedUpdate(CPed *ped, int id) { EAXJMP(0x5935B0); }
#else
void CReplay::StorePedUpdate(CPed *ped, int id)
{
	tPedUpdatePacket* pp = (tPedUpdatePacket*)&Record.m_pBase[Record.m_nOffset];
	pp->type = REPLAYPACKET_PED_UPDATE;
	pp->index = id;
	pp->heading = 128.0f / M_PI * ped->m_fRotationCur;
	pp->matrix.CompressFromFullMatrix(ped->GetMatrix());
	pp->assoc_group_id = ped->m_animGroup;
	/* 	Would be more sane to use GetJustIndex(ped->m_pMyVehicle) in following assignment */
	if (ped->bInVehicle && ped->m_pMyVehicle)
		pp->vehicle_index = (CPools::GetVehiclePool()->GetIndex(ped->m_pMyVehicle) >> 8) + 1;
	else
		pp->vehicle_index = 0;
	pp->weapon_model = ped->m_wepModelID;
	StorePedAnimation(ped, &pp->anim_state);
	Record.m_nOffset += sizeof(tPedUpdatePacket);
}
#endif

#if 0
WRAPPER void CReplay::StorePedAnimation(CPed *ped, CStoredAnimationState *state) { EAXJMP(0x593670); }
#else
void CReplay::StorePedAnimation(CPed *ped, CStoredAnimationState *state)
{
	CAnimBlendAssociation* second;
	float blend_amount;
	CAnimBlendAssociation* main = RpAnimBlendClumpGetMainAssociation((RpClump*)ped->m_rwObject, &second, &blend_amount);
	if (main){
		state->animId = main->animId;
		state->time = 255.0f / 4.0f * max(0.0f, min(4.0f, main->currentTime));
		state->speed = 255.0f / 3.0f * max(0.0f, min(3.0f, main->speed));
	}else{
		state->animId = 3;
		state->time = 0;
		state->speed = 85;
	}
	if (second) {
		state->secAnimId = second->animId;
		state->secTime = 255.0f / 4.0f * max(0.0f, min(4.0f, second->currentTime));
		state->secSpeed = 255.0f / 3.0f * max(0.0f, min(3.0f, second->speed));
		state->blendAmount = 255.0f / 2.0f * max(0.0f, min(2.0f, blend_amount));
	}else{
		state->secAnimId = 0;
		state->secTime = 0;
		state->secSpeed = 0;
		state->blendAmount = 0;
	}
	CAnimBlendAssociation* partial = RpAnimBlendClumpGetMainPartialAssociation((RpClump*)ped->m_rwObject);
	if (partial) {
		state->partAnimId = partial->animId;
		state->partAnimTime = 255.0f / 4.0f * max(0.0f, min(4.0f, partial->currentTime));
		state->partAnimSpeed = 255.0f / 3.0f * max(0.0f, min(3.0f, partial->speed));
		state->partBlendAmount = 255.0f / 2.0f * max(0.0f, min(2.0f, partial->blendAmount));
	}else{
		state->partAnimId = 0;
		state->partAnimTime = 0;
		state->partAnimSpeed = 0;
		state->partBlendAmount = 0;
	}
}
#endif

#if 0
WRAPPER void CReplay::StoreDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state) { EAXJMP(0x593BB0); }
#else
void CReplay::StoreDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state)
{
	for (int i = 0; i < 3; i++){
		CAnimBlendAssociation* assoc = RpAnimBlendClumpGetMainAssociation_N((RpClump*)ped->m_rwObject, i);
		if (assoc){
			state->aAnimId[i] = assoc->animId;
			state->aCurTime[i] = 255.0f / 4.0f * max(0.0f, min(4.0f, assoc->currentTime));
			state->aSpeed[i] = 255.0f / 3.0f * max(0.0f, min(3.0f, assoc->speed));
			state->aBlendAmount[i] = 255.0f / 2.0f * max(0.0f, min(2.0f, assoc->blendAmount));
			state->aFlags[i] = assoc->flags;
			if (assoc->callbackType == CAnimBlendAssociation::CB_FINISH || assoc->callbackType == CAnimBlendAssociation::CB_DELETE) {
				state->aFunctionCallbackID[i] = FindCBFunctionID(assoc->callback);
				if (assoc->callbackType == CAnimBlendAssociation::CB_FINISH)
					state->aFunctionCallbackID[i] |= 0x80;
			}else{
				state->aFunctionCallbackID[i] = 0;
			}
		}else{
			state->aAnimId[i] = NUM_ANIMS;
			state->aCurTime[i] = 0;
			state->aSpeed[i] = 85;
			state->aFunctionCallbackID[i] = 0;
			state->aFlags[i] = 0;
		}
	}
	for (int i = 0; i < 6; i++) {
		CAnimBlendAssociation* assoc = RpAnimBlendClumpGetMainPartialAssociation_N((RpClump*)ped->m_rwObject, i);
		if (assoc) {
			state->aAnimId2[i] = assoc->animId;
			state->aCurTime2[i] = 255.0f / 4.0f * max(0.0f, min(4.0f, assoc->currentTime));
			state->aSpeed2[i] = 255.0f / 3.0f * max(0.0f, min(3.0f, assoc->speed));
			state->aBlendAmount2[i] = 255.0f / 2.0f * max(0.0f, min(2.0f, assoc->blendAmount));
			state->aFlags2[i] = assoc->flags;
			if (assoc->callbackType == CAnimBlendAssociation::CB_FINISH || assoc->callbackType == CAnimBlendAssociation::CB_DELETE) {
				state->aFunctionCallbackID2[i] = FindCBFunctionID(assoc->callback);
				if (assoc->callbackType == CAnimBlendAssociation::CB_FINISH)
					state->aFunctionCallbackID2[i] |= 0x80;
			}else{
				state->aFunctionCallbackID2[i] = 0;
			}
		}
		else {
			state->aAnimId2[i] = NUM_ANIMS;
			state->aCurTime2[i] = 0;
			state->aSpeed2[i] = 85;
			state->aFunctionCallbackID2[i] = 0;
			state->aFlags2[i] = 0;
		}
	}
}
#endif
#if 0
WRAPPER void CReplay::ProcessPedUpdate(CPed *ped, float interpolation, CAddressInReplayBuffer *buffer) { EAXJMP(0x594050); }
#else
void CReplay::ProcessPedUpdate(CPed *ped, float interpolation, CAddressInReplayBuffer *buffer)
{
	tPedUpdatePacket *pp = (tPedUpdatePacket*)&buffer->m_pBase[buffer->m_nOffset];
	if (!ped){
		debug("Replay:Ped wasn't there\n");
		buffer->m_nOffset += sizeof(tPedUpdatePacket);
		return;
	}
	ped->m_fRotationCur = pp->heading * M_PI / 128.0f;
	ped->m_fRotationDest = pp->heading * M_PI / 128.0f;
	CMatrix ped_matrix;
	pp->matrix.DecompressIntoFullMatrix(ped_matrix);
	ped->GetMatrix() = ped->GetMatrix() * CMatrix(1.0f - interpolation);
	ped->GetMatrix().GetPosition() *= (1.0f - interpolation);
	ped->GetMatrix() += CMatrix(interpolation) * ped_matrix;
	if (pp->vehicle_index) {
		ped->m_pMyVehicle = CPools::GetVehiclePool()->GetSlot(pp->vehicle_index - 1);
		ped->bInVehicle = pp->vehicle_index;
	}
	else {
		ped->m_pMyVehicle = nil;
		ped->bInVehicle = false;
	}
	if (pp->assoc_group_id != ped->m_animGroup) {
		ped->m_animGroup = (AssocGroupId)pp->assoc_group_id;
		if (ped == FindPlayerPed())
			((CPlayerPed*)ped)->ReApplyMoveAnims();
	}
	RetrievePedAnimation(ped, &pp->anim_state);
	ped->RemoveWeaponModel(-1);
	if (pp->weapon_model != (uint8)-1)
		ped->AddWeaponModel(pp->weapon_model);
	CWorld::Remove(ped);
	CWorld::Add(ped);
	buffer->m_nOffset += sizeof(tPedUpdatePacket);
}
#endif

#if 0
WRAPPER void CReplay::RetrievePedAnimation(CPed *ped, CStoredAnimationState *state) { EAXJMP(0x5942A0); }
#else
void CReplay::RetrievePedAnimation(CPed *ped, CStoredAnimationState *state)
{
	CAnimBlendAssociation* anim1 = CAnimManager::BlendAnimation(
		(RpClump*)ped->m_rwObject,
		(state->animId > 3) ? ASSOCGRP_STD : ped->m_animGroup,
		(AnimationId)state->animId, 100.0f);
	anim1->SetCurrentTime(state->time * 4.0f / 255.0f);
	anim1->speed = state->speed * 3.0f / 255.0f;
	anim1->SetBlend(1.0f, 1.0f);
	anim1->callbackType = CAnimBlendAssociation::CB_NONE;
	if (state->blendAmount && state->secAnimId){
		float time = state->secTime * 4.0f / 255.0f;
		float speed = state->secSpeed * 3.0f / 255.0f;
		float blend = state->blendAmount * 2.0f / 255.0f;
		CAnimBlendAssociation* anim2 = CAnimManager::BlendAnimation(
			(RpClump*)ped->m_rwObject,
			(state->secAnimId > 3) ? ASSOCGRP_STD : ped->m_animGroup,
			(AnimationId)state->secAnimId, 100.0f);
		anim2->SetCurrentTime(time);
		anim2->speed = speed;
		anim2->SetBlend(blend, 1.0f);
		anim2->callbackType = CAnimBlendAssociation::CB_NONE;
	}
	RpAnimBlendClumpRemoveAssociations((RpClump*)ped->m_rwObject, 0x10);
	if (state->partAnimId){
		float time = state->partAnimTime * 4.0f / 255.0f;
		float speed = state->partAnimSpeed * 3.0f / 255.0f;
		float blend = state->partBlendAmount * 2.0f / 255.0f;
		if (blend > 0.0f && state->partAnimId != ANIM_IDLE_STANCE){
			CAnimBlendAssociation* anim3 = CAnimManager::BlendAnimation(
				(RpClump*)ped->m_rwObject, ASSOCGRP_STD, (AnimationId)state->partAnimId, 1000.0f);
			anim3->SetCurrentTime(time);
			anim3->speed = speed;
			anim3->SetBlend(blend, 0.0f);
		}
	}
}
#endif

#if 0
WRAPPER void CReplay::RetrieveDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state) { EAXJMP(0x5944B0); }
#else
void CReplay::RetrieveDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state)
{
	for (int i = 0; i < 3; i++){
		if (state->aAnimId[i] == NUM_ANIMS)
			continue;
		CAnimBlendAssociation* anim = CAnimManager::BlendAnimation(
			(RpClump*)ped->m_rwObject,
			state->aAnimId[i] > 3 ? ASSOCGRP_STD : ped->m_animGroup,
			(AnimationId)state->aAnimId[i], 100.0f);
		anim->SetCurrentTime(state->aCurTime[i] * 4.0f / 255.0f);
		anim->speed = state->aSpeed[i] * 3.0f / 255.0f;
		/* Lack of commented out calculation causes megajump */
		anim->SetBlend(state->aBlendAmount[i] /* * 2.0f / 255.0f */, 1.0f);
		anim->flags = state->aFlags[i];
		uint8 callback = state->aFunctionCallbackID[i];
		if (!callback)
			anim->callbackType = CAnimBlendAssociation::CB_NONE;
		else if (callback & 0x80)
			anim->SetFinishCallback(FindCBFunction(callback & 0x7F), ped);
		else
			anim->SetDeleteCallback(FindCBFunction(callback & 0x7F), ped);
	}
	for (int i = 0; i < 6; i++) {
		if (state->aAnimId2[i] == NUM_ANIMS)
			continue;
		CAnimBlendAssociation* anim = CAnimManager::BlendAnimation(
			(RpClump*)ped->m_rwObject,
			state->aAnimId2[i] > 3 ? ASSOCGRP_STD : ped->m_animGroup,
			(AnimationId)state->aAnimId2[i], 100.0f);
		anim->SetCurrentTime(state->aCurTime2[i] * 4.0f / 255.0f);
		anim->speed = state->aSpeed2[i] * 3.0f / 255.0f;
		/* Lack of commented out calculation causes megajump */
		anim->SetBlend(state->aBlendAmount2[i] /* * 2.0f / 255.0f */, 1.0f);
		anim->flags = state->aFlags2[i];
		uint8 callback = state->aFunctionCallbackID2[i];
		if (!callback)
			anim->callbackType = CAnimBlendAssociation::CB_NONE;
		else if (callback & 0x80)
			anim->SetFinishCallback(FindCBFunction(callback & 0x7F), ped);
		else
			anim->SetDeleteCallback(FindCBFunction(callback & 0x7F), ped);
	}
}
#endif

#if 0
WRAPPER void CReplay::PlaybackThisFrame(void) { EAXJMP(0x5946B0); }
#else
void CReplay::PlaybackThisFrame(void)
{
	static int SlowMotionCounter = 0;
	CAddressInReplayBuffer buf = Playback;
	if (PlayBackThisFrameInterpolation(&buf, 1.0f, nil)){
		DMAudio.SetEffectsFadeVol(127);
		DMAudio.SetMusicFadeVol(127);
		return;
	}
	if (SlowMotionCounter){
		CAddressInReplayBuffer buf_sm = buf;
		if (PlayBackThisFrameInterpolation(&buf_sm, SlowMotionCounter * 1.0f / SlowMotion, nil)){
			DMAudio.SetEffectsFadeVol(127);
			DMAudio.SetMusicFadeVol(127);
			return;
		}
	}
	SlowMotionCounter = (SlowMotionCounter + 1) % SlowMotion;
	if (SlowMotionCounter == 0)
		Playback = buf;
	ProcessLookAroundCam();
	DMAudio.SetEffectsFadeVol(0);
	DMAudio.SetMusicFadeVol(0);
}
#endif

#if 0
WRAPPER void CReplay::StoreCarUpdate(CVehicle *vehicle, int id) { EAXJMP(0x5947F0); }
#else
void CReplay::StoreCarUpdate(CVehicle *vehicle, int id)
{
	tVehicleUpdatePacket* vp = (tVehicleUpdatePacket*)&Record.m_pBase[Record.m_nOffset];
	vp->type = REPLAYPACKET_VEHICLE;
	vp->index = id;
	vp->matrix.CompressFromFullMatrix(vehicle->GetMatrix());
	vp->health = vehicle->m_fHealth / 4.0f; /* Not anticipated that health can be > 1000. */
	vp->acceleration = vehicle->m_fGasPedal * 100.0f;
	vp->panels = vehicle->IsCar() ? ((CAutomobile*)vehicle)->Damage.m_panelStatus : 0;
	vp->velocityX = 8000.0f * max(-4.0f, min(4.0f, vehicle->GetSpeed().x)); /* 8000!? */
	vp->velocityY = 8000.0f * max(-4.0f, min(4.0f, vehicle->GetSpeed().y));
	vp->velocityZ = 8000.0f * max(-4.0f, min(4.0f, vehicle->GetSpeed().z));
	vp->mi = vehicle->GetModelIndex();
	vp->primary_color = vehicle->m_currentColour1;
	vp->secondary_color = vehicle->m_currentColour2;
	if (vehicle->GetModelIndex() == MI_RHINO)
		vp->car_gun = 128.0f / M_PI * ((CAutomobile*)vehicle)->m_fCarGunLR;
	else
		vp->wheel_state = 50.0f * vehicle->m_fSteerAngle;
	if (vehicle->IsCar()){
		CAutomobile* car = (CAutomobile*)vehicle;
		for (int i = 0; i < 4; i++){
			vp->wheel_susp_dist[i] = 50.0f * car->m_aSuspensionSpringRatio[i];
			vp->wheel_rotation[i] = 128.0f / M_PI * car->m_aWheelRotation[i];
		}
		vp->door_angles[0] = 127.0f / M_PI * car->Doors[2].m_fAngle;
		vp->door_angles[1] = 127.0f / M_PI * car->Doors[3].m_fAngle;
		vp->door_status = 0;
		for (int i = 0; i < 6; i++){
			if (car->Damage.GetDoorStatus(i) == 3)
				vp->door_status |= BIT(i);
		}
	}
	Record.m_nOffset += sizeof(tVehicleUpdatePacket);
}
#endif

#if 0
WRAPPER void CReplay::ProcessCarUpdate(CVehicle *vehicle, float interpolation, CAddressInReplayBuffer *buffer) { EAXJMP(0x594D10); }
#else
void CReplay::ProcessCarUpdate(CVehicle *vehicle, float interpolation, CAddressInReplayBuffer *buffer)
{
	tVehicleUpdatePacket* vp = (tVehicleUpdatePacket*)&buffer->m_pBase[buffer->m_nOffset];
	if (!vehicle){
		debug("Replay:Car wasn't there");
		return;
	}
	CMatrix vehicle_matrix;
	vp->matrix.DecompressIntoFullMatrix(vehicle_matrix);
	vehicle->GetMatrix() = vehicle->GetMatrix() * CMatrix(1.0f - interpolation);
	vehicle->GetMatrix().GetPosition() *= (1.0f - interpolation);
	vehicle->GetMatrix() += CMatrix(interpolation) * vehicle_matrix;
	vehicle->m_vecTurnSpeed = CVector(0.0f, 0.0f, 0.0f);
	vehicle->m_fHealth = 4 * vp->health;
	vehicle->m_fGasPedal = vp->acceleration / 100.0f;
	if (vehicle->IsCar())
		ApplyPanelDamageToCar(vp->panels, (CAutomobile*)vehicle, true);
	vehicle->m_vecMoveSpeed = CVector(vp->velocityX / 8000.0f, vp->velocityY / 8000.0f, vp->velocityZ / 8000.0f);
	if (vehicle->GetModelIndex() == MI_RHINO) {
		((CAutomobile*)vehicle)->m_fCarGunLR = vp->car_gun * M_PI / 128.0f;
		vehicle->m_fSteerAngle = 0.0f;
	}else{
		vehicle->m_fSteerAngle = vp->wheel_state / 50.0f;
	}
	if (vehicle->IsCar()) {
		CAutomobile* car = (CAutomobile*)vehicle;
		for (int i = 0; i < 4; i++) {
			car->m_aSuspensionSpringRatio[i] = vp->wheel_susp_dist[i] / 50.0f;
			car->m_aWheelRotation[i] = vp->wheel_rotation[i] * M_PI / 128.0f;
		}
		car->Doors[2].m_fAngle = car->Doors[2].m_fPrevAngle = vp->door_angles[0] * M_PI / 127.0f;
		car->Doors[3].m_fAngle = car->Doors[3].m_fPrevAngle = vp->door_angles[1] * M_PI / 127.0f;
		if (vp->door_angles[0])
			car->Damage.SetDoorStatus(2, 2);
		if (vp->door_angles[1])
			car->Damage.SetDoorStatus(3, 2);
		if (vp->door_status & 1 && car->Damage.GetDoorStatus(DOOR_BONNET) != 3){
			car->Damage.SetDoorStatus(DOOR_BONNET, 3);
			car->SetDoorDamage(CAR_BONNET, DOOR_BONNET, true);
		}
		if (vp->door_status & 2 && car->Damage.GetDoorStatus(DOOR_BOOT) != 3) {
			car->Damage.SetDoorStatus(DOOR_BOOT, 3);
			car->SetDoorDamage(CAR_BOOT, DOOR_BOOT, true);
		}
		if (vp->door_status & 4 && car->Damage.GetDoorStatus(DOOR_FRONT_LEFT) != 3) {
			car->Damage.SetDoorStatus(DOOR_FRONT_LEFT, 3);
			car->SetDoorDamage(CAR_DOOR_LF, DOOR_FRONT_LEFT, true);
		}
		if (vp->door_status & 8 && car->Damage.GetDoorStatus(DOOR_FRONT_RIGHT) != 3) {
			car->Damage.SetDoorStatus(DOOR_FRONT_RIGHT, 3);
			car->SetDoorDamage(CAR_DOOR_RF, DOOR_FRONT_RIGHT, true);
		}
		if (vp->door_status & 0x10 && car->Damage.GetDoorStatus(DOOR_REAR_LEFT) != 3) {
			car->Damage.SetDoorStatus(DOOR_REAR_LEFT, 3);
			car->SetDoorDamage(CAR_DOOR_LR, DOOR_REAR_LEFT, true);
		}
		if (vp->door_status & 0x20 && car->Damage.GetDoorStatus(DOOR_REAR_RIGHT) != 3) {
			car->Damage.SetDoorStatus(DOOR_REAR_RIGHT, 3);
			car->SetDoorDamage(CAR_DOOR_RR, DOOR_REAR_RIGHT, true);
		}
		vehicle->bEngineOn = true;
		if (vehicle->IsCar())
			((CAutomobile*)vehicle)->m_nDriveWheelsOnGround = 4;
		CWorld::Remove(vehicle);
		CWorld::Add(vehicle);
		if (vehicle->IsBoat())
			((CBoat*)vehicle)->m_bIsAnchored = false;
	}
}
#endif

#if 0
WRAPPER bool CReplay::PlayBackThisFrameInterpolation(CAddressInReplayBuffer *buffer, float interpolation, uint32 *pTimer) { EAXJMP(0x595240); }
#else
bool CReplay::PlayBackThisFrameInterpolation(CAddressInReplayBuffer *buffer, float interpolation, uint32 *pTimer){
	/* Mistake. Not even sure what this is even doing here...
	 * PlayerWanted is a backup to restore at the end of replay.
	 * Setting current wanted pointer to it makes it useless.
	 * Causes picking up bribes in replays reducing wanted level bug.
	 * Obviously fact of picking them up is a bug on its own,
	 * but it doesn't cancel this one.
	 */
	FindPlayerPed()->m_pWanted = &PlayerWanted;

	CBulletTraces::Init();
	float split = 1.0f - interpolation;
	int ped_min_index = 0; /* Optimization due to peds and vehicles placed in buffer sequentially. */
	int vehicle_min_index = 0; /* So next ped can't have pool index less than current. */
	for(;;){
		uint8* ptr = buffer->m_pBase;
		uint32 offset = buffer->m_nOffset;
		uint8 type = ptr[offset];
		if (type == REPLAYPACKET_ENDOFFRAME)
			break;
		switch (type) {
		case REPLAYPACKET_END:
		{
			int slot = buffer->m_bSlot;
			if (BufferStatus[slot] == REPLAYBUFFER_RECORD) {
				FinishPlayback();
				return true;
			}
			buffer->m_bSlot = (slot + 1) % 8;
			buffer->m_nOffset = 0;
			buffer->m_pBase = Buffers[buffer->m_bSlot];
			ped_min_index = 0;
			vehicle_min_index = 0;
			break;
		}
		case REPLAYPACKET_VEHICLE:
		{
			tVehicleUpdatePacket* vp = (tVehicleUpdatePacket*)&ptr[offset];
			for (int i = vehicle_min_index; i < vp->index; i++) {
				CVehicle* v = CPools::GetVehiclePool()->GetSlot(i);
				if (!v)
					continue;
				/* Removing vehicles not present in this frame. */
				CWorld::Remove(v);
				delete v;
			}
			vehicle_min_index = vp->index + 1;
			CVehicle* v = CPools::GetVehiclePool()->GetSlot(vp->index);
			CVehicle* new_v;
			if (!v) {
				int mi = vp->mi;
				if (CStreaming::ms_aInfoForModel[mi].m_loadState != 1) {
					CStreaming::RequestModel(mi, 0);
				}
				else {
					if (mi == MI_DEADDODO || mi == MI_AIRTRAIN) {
						new_v = new(vp->index << 8) CPlane(mi, 2);
					}
					else if (mi == MI_TRAIN) {
						new_v = new(vp->index << 8) CTrain(mi, 2);
					}
					else if (mi == MI_CHOPPER || mi == MI_ESCAPE) {
						new_v = new(vp->index << 8) CHeli(mi, 2);
					}
					else if (CModelInfo::IsBoatModel(mi)){
						new_v = new(vp->index << 8) CBoat(mi, 2);
					}
					else{
						new_v = new(vp->index << 8) CAutomobile(mi, 2);
					}
					new_v->m_status = STATUS_PLAYER_PLAYBACKFROMBUFFER;
					vp->matrix.DecompressIntoFullMatrix(new_v->GetMatrix());
					new_v->m_currentColour1 = vp->primary_color;
					new_v->m_currentColour2 = vp->secondary_color;
					CWorld::Add(new_v);
				}
			}
			ProcessCarUpdate(CPools::GetVehiclePool()->GetSlot(vp->index), interpolation, buffer);
			buffer->m_nOffset += sizeof(tVehicleUpdatePacket);
			break;
		}
		case REPLAYPACKET_PED_HEADER:
		{
			tPedHeaderPacket* ph = (tPedHeaderPacket*)&ptr[offset];
			if (!CPools::GetPedPool()->GetSlot(ph->index)) {
				if (CStreaming::ms_aInfoForModel[ph->mi].m_loadState != 1) {
					CStreaming::RequestModel(ph->mi, 0);
				}
				else {
					CPed* new_p = new(ph->index << 8) CCivilianPed(ph->pedtype, ph->mi);
					new_p->m_status = STATUS_PLAYER_PLAYBACKFROMBUFFER;
					new_p->GetMatrix().SetUnity();
					CWorld::Add(new_p);
				}
			}
			buffer->m_nOffset += sizeof(tPedHeaderPacket);
			break;
		}
		case REPLAYPACKET_PED_UPDATE:
		{
			tPedUpdatePacket* pu = (tPedUpdatePacket*)&ptr[offset];
			for (int i = ped_min_index; i < pu->index; i++) {
				CPed* p = CPools::GetPedPool()->GetSlot(i);
				if (!p)
					continue;
				/* Removing peds not present in this frame. */
				CWorld::Remove(p);
				delete p;
			}
			ped_min_index = pu->index + 1;
			ProcessPedUpdate(CPools::GetPedPool()->GetSlot(pu->index), interpolation, buffer);
			break;
		}
		case REPLAYPACKET_GENERAL:
		{
			tGeneralPacket* pg = (tGeneralPacket*)&ptr[offset];
			TheCamera.GetMatrix() = TheCamera.GetMatrix() * CMatrix(split);
			TheCamera.GetMatrix().GetPosition() *= split;
			TheCamera.GetMatrix() += CMatrix(interpolation) * pg->camera_pos;
			RwMatrix* pm = RwFrameGetMatrix(RwCameraGetFrame(TheCamera.m_pRwCamera));
			pm->pos = *(RwV3d*)TheCamera.GetMatrix().GetPosition();
			pm->at = *(RwV3d*)TheCamera.GetMatrix().GetForward();
			pm->up = *(RwV3d*)TheCamera.GetMatrix().GetUp();
			pm->right = *(RwV3d*)TheCamera.GetMatrix().GetRight();
			CameraFocusX = split * CameraFocusX + interpolation * pg->player_pos.x;
			CameraFocusY = split * CameraFocusY + interpolation * pg->player_pos.y;
			CameraFocusZ = split * CameraFocusZ + interpolation * pg->player_pos.z;
			bPlayerInRCBuggy = pg->in_rcvehicle;
			buffer->m_nOffset += sizeof(tGeneralPacket);
			break;
		}
		case REPLAYPACKET_CLOCK:
		{
			tClockPacket* pc = (tClockPacket*)&ptr[offset];
			CClock::SetGameClock(pc->hours, pc->minutes);
			buffer->m_nOffset += sizeof(tClockPacket);
			break;
		}
		case REPLAYPACKET_WEATHER:
		{
			tWeatherPacket* pw = (tWeatherPacket*)&ptr[offset];
			CWeather::OldWeatherType = pw->old_weather;
			CWeather::NewWeatherType = pw->new_weather;
			CWeather::InterpolationValue = pw->interpolation;
			buffer->m_nOffset += sizeof(tWeatherPacket);
			break;
		}
		case REPLAYPACKET_ENDOFFRAME:
		{
			/* Not supposed to be here. */
			buffer->m_nOffset++;
			break;
		}
		case REPLAYPACKET_TIMER:
		{
			tTimerPacket* pt = (tTimerPacket*)&ptr[offset];
			if (pTimer)
				*pTimer = pt->timer;
			CTimer::SetTimeInMilliseconds(pt->timer);
			buffer->m_nOffset += sizeof(tTimerPacket);
			break;
		}
		case REPLAYPACKET_BULLET_TRACES:
		{
			tBulletTracePacket* pb = (tBulletTracePacket*)&ptr[offset];
			CBulletTraces::aTraces[pb->index].m_bInUse = true;
			CBulletTraces::aTraces[pb->index].m_framesInUse = pb->frames;
			CBulletTraces::aTraces[pb->index].m_lifeTime = pb->lifetime;
			CBulletTraces::aTraces[pb->index].m_vecInf = pb->inf;
			CBulletTraces::aTraces[pb->index].m_vecSup = pb->sup;
			buffer->m_nOffset += sizeof(tBulletTracePacket);
		}
		default:
			break;
		}
	}
	buffer->m_nOffset += 4;
	for (int i = vehicle_min_index; i < CPools::GetVehiclePool()->GetSize(); i++) {
		CVehicle* v = CPools::GetVehiclePool()->GetSlot(i);
		if (!v)
			continue;
		/* Removing vehicles not present in this frame. */
		CWorld::Remove(v);
		delete v;
	}
	for (int i = ped_min_index; i < CPools::GetPedPool()->GetSize(); i++) {
		CPed* p = CPools::GetPedPool()->GetSlot(i);
		if (!p)
			continue;
		/* Removing peds not present in this frame. */
		CWorld::Remove(p);
		delete p;
	}
	ProcessReplayCamera();
	return false;
}
#endif
#if 0
WRAPPER void CReplay::FinishPlayback(void) { EAXJMP(0x595B20); }
#else
void CReplay::FinishPlayback(void)
{
	if (Mode != MODE_PLAYBACK)
		return;
	EmptyAllPools();
	RestoreStuffFromMem();
	Mode = MODE_RECORD;
	if (bDoLoadSceneWhenDone){
		CVector v_ls(LoadSceneX, LoadSceneY, LoadSceneZ);
		CGame::currLevel = CTheZones::GetLevelFromPosition(v_ls);
		CCollision::SortOutCollisionAfterLoad();
		CStreaming::LoadScene(v_ls);
	}
	bDoLoadSceneWhenDone = false;
	if (bPlayingBackFromFile){
		Init();
		MarkEverythingAsNew();
	}
	DMAudio.SetEffectsFadeVol(127);
	DMAudio.SetMusicFadeVol(127);
}
#endif

#if 0
WRAPPER void CReplay::EmptyReplayBuffer(void) { EAXJMP(0x595BD0); }
#else
void CReplay::EmptyReplayBuffer(void)
{
	if (Mode == MODE_PLAYBACK)
		return;
	for (int i = 0; i < 8; i++){
		BufferStatus[i] = REPLAYBUFFER_UNUSED;
	}
	Record.m_bSlot = 0;
	Record.m_pBase = Buffers[0];
	BufferStatus[0] = REPLAYBUFFER_RECORD;
	Record.m_pBase[Record.m_nOffset] = 0;
	MarkEverythingAsNew();
}
#endif

#if 0
WRAPPER void CReplay::ProcessReplayCamera(void) { EAXJMP(0x595C40); }
#else
void CReplay::ProcessReplayCamera(void)
{
	switch (CameraMode) {
	case REPLAYCAMMODE_TOPDOWN:
	{
		TheCamera.GetMatrix().GetPosition() = CVector(CameraFocusX, CameraFocusY, CameraFocusZ + 15.0f);
		TheCamera.GetMatrix().GetForward() = CVector(0.0f, 0.0f, -1.0f);
		TheCamera.GetMatrix().GetUp() = CVector(0.0f, 1.0f, 0.0f);
		TheCamera.GetMatrix().GetRight() = CVector(1.0f, 0.0f, 0.0f);
		RwMatrix* pm = RwFrameGetMatrix(RwCameraGetFrame(TheCamera.m_pRwCamera));
		pm->pos = *(RwV3d*)&TheCamera.GetMatrix().GetPosition();
		pm->at = *(RwV3d*)&TheCamera.GetMatrix().GetForward();
		pm->up = *(RwV3d*)&TheCamera.GetMatrix().GetUp();
		pm->right = *(RwV3d*)&TheCamera.GetMatrix().GetRight();
		break;
	}
	case REPLAYCAMMODE_FIXED:
	{
		TheCamera.GetMatrix().GetPosition() = CVector(CameraFixedX, CameraFixedY, CameraFixedZ);
		CVector forward(CameraFocusX - CameraFixedX, CameraFocusY - CameraFixedY, CameraFocusZ - CameraFixedZ);
		forward.Normalise();
		CVector right = CrossProduct(CVector(0.0f, 0.0f, 1.0f), forward);
		right.Normalise();
		CVector up = CrossProduct(forward, right);
		up.Normalise();
		TheCamera.GetMatrix().GetForward() = forward;
		TheCamera.GetMatrix().GetUp() = up;
		TheCamera.GetMatrix().GetRight() = right;
		RwMatrix* pm = RwFrameGetMatrix(RwCameraGetFrame(TheCamera.m_pRwCamera));
		pm->pos = *(RwV3d*)&TheCamera.GetMatrix().GetPosition();
		pm->at = *(RwV3d*)&TheCamera.GetMatrix().GetForward();
		pm->up = *(RwV3d*)&TheCamera.GetMatrix().GetUp();
		pm->right = *(RwV3d*)&TheCamera.GetMatrix().GetRight();
		break;
	}
	default:
		break;
	}
	TheCamera.m_vecGameCamPos = TheCamera.GetMatrix().GetPosition();
	TheCamera.CalculateDerivedValues();
	RwMatrixUpdate(RwFrameGetMatrix(RwCameraGetFrame(TheCamera.m_pRwCamera)));
	RwFrameUpdateObjects(RwCameraGetFrame(TheCamera.m_pRwCamera));
}
#endif

#if 0
WRAPPER void CReplay::TriggerPlayback(uint8 cam_mode, float cam_x, float cam_y, float cam_z, bool load_scene) { EAXJMP(0x596030); }
#else
void CReplay::TriggerPlayback(uint8 cam_mode, float cam_x, float cam_y, float cam_z, bool load_scene)
{
	if (Mode != MODE_RECORD)
		return;
	CameraFixedX = cam_x;
	CameraFixedY = cam_y;
	CameraFixedZ = cam_z;
	Mode = MODE_PLAYBACK;
	FramesActiveLookAroundCam = 0;
	CameraMode = cam_mode;
	bAllowLookAroundCam = true;
	bPlayingBackFromFile = false;
	OldRadioStation = DMAudio.GetRadioInCar();
	DMAudio.ChangeMusicMode(0);
	DMAudio.SetEffectsFadeVol(0);
	DMAudio.SetMusicFadeVol(0);
	int current;
	for (current = 0; current < 8; current++)
		if (BufferStatus[current] == REPLAYBUFFER_RECORD)
			break;
	int first;
	for (first = (current + 1) % 8; ; first = (first + 1) % 8)
		if (BufferStatus[first] == REPLAYBUFFER_RECORD || BufferStatus[first] == REPLAYBUFFER_PLAYBACK)
			break;
	Playback.m_bSlot = first;
	Playback.m_nOffset = 0;
	Playback.m_pBase = Buffers[first];
	CObject::DeleteAllTempObjectInArea(CVector(0.0f, 0.0f, 0.0f), 1000000.0f);
	StoreStuffInMem();
	EmptyPedsAndVehiclePools();
	SlowMotion = 1;
	CSkidmarks::Clear();
	StreamAllNecessaryCarsAndPeds();
	if (load_scene)
		bDoLoadSceneWhenDone = false;
	else{
		bDoLoadSceneWhenDone = true;
		LoadSceneX = TheCamera.GetPosition().x;
		LoadSceneY = TheCamera.GetPosition().y;
		LoadSceneZ = TheCamera.GetPosition().z;
		CVector ff_coord;
		FindFirstFocusCoordinate(&ff_coord);
		CGame::currLevel = CTheZones::GetLevelFromPosition(ff_coord);
		CCollision::SortOutCollisionAfterLoad();
		CStreaming::LoadScene(ff_coord);
	}
	if (cam_mode == REPLAYCAMMODE_ASSTORED)
		TheCamera.CarZoomIndicator = 5.0f;
}
#endif

#if 0
WRAPPER void CReplay::StoreStuffInMem(void) { EAXJMP(0x5961F0); }
#else
void CReplay::StoreStuffInMem(void)
{
	CPools::GetVehiclePool()->Store(pBuf0, pBuf1);
	CPools::GetPedPool()->Store(pBuf2, pBuf3);
	CPools::GetObjectPool()->Store(pBuf4, pBuf5);
	CPools::GetPtrNodePool()->Store(pBuf6, pBuf7);
	CPools::GetEntryInfoNodePool()->Store(pBuf8, pBuf9);
	CPools::GetDummyPool()->Store(pBuf10, pBuf11);
	pWorld1 = new uint8[sizeof(CSector) * NUMSECTORS_X * NUMSECTORS_Y];
	memcpy(pWorld1, CWorld::GetSector(0, 0), NUMSECTORS_X * NUMSECTORS_Y * sizeof(CSector));
	WorldPtrList = CWorld::GetMovingEntityList();
	BigBuildingPtrList = CWorld::GetBigBuildingList(LEVEL_NONE);
	pPickups = new uint8[sizeof(CPickup) * NUMPICKUPS];
	memcpy(pPickups, CPickups::aPickUps, NUMPICKUPS * sizeof(CPickup));
	pReferences = new uint8[(sizeof(CReference) * NUMREFERENCES)];
	memcpy(pReferences, CReferences::aRefs, NUMREFERENCES * sizeof(CReference));
	pEmptyReferences = CReferences::pEmptyList;
	pStoredCam = new uint8[sizeof(CCamera)];
	memcpy(pStoredCam, &TheCamera, sizeof(CCamera));
	pRadarBlips = new uint8[sizeof(CBlip) * NUMRADARBLIPS];
	memcpy(pRadarBlips, CRadar::ms_RadarTrace, NUMRADARBLIPS * sizeof(CBlip));
	PlayerWanted = *FindPlayerPed()->m_pWanted;
	PlayerInfo = CWorld::Players[0];
	Time1 = CTimer::GetTimeInMilliseconds();
	Time2 = CTimer::GetTimeInMillisecondsNonClipped();
	Time3 = CTimer::GetPreviousTimeInMilliseconds();
	Time4 = CTimer::GetTimeInMillisecondsPauseMode();
	Frame = CTimer::GetFrameCounter();
	ClockHours = CClock::GetHours();
	ClockMinutes = CClock::GetMinutes();
	OldWeatherType = CWeather::OldWeatherType;
	NewWeatherType = CWeather::NewWeatherType;
	WeatherInterpolationValue = CWeather::InterpolationValue;
	TimeStepNonClipped = CTimer::GetTimeStepNonClipped();
	TimeStep = CTimer::GetTimeStep();
	TimeScale = CTimer::GetTimeScale();
	int size = CPools::GetPedPool()->GetSize();
	pPedAnims = (CStoredDetailedAnimationState*)malloc(size * sizeof(CStoredDetailedAnimationState));
	for (int i = 0; i < size; i++) {
		CPed* ped = CPools::GetPedPool()->GetSlot(i);
		if (ped)
			StoreDetailedPedAnimation(ped, &pPedAnims[i]);
	}
}
#endif

#if 0
WRAPPER void CReplay::RestoreStuffFromMem(void) { EAXJMP(0x5966E0); }
#else
void CReplay::RestoreStuffFromMem(void)
{
	CPools::GetVehiclePool()->CopyBack(pBuf0, pBuf1);
	CPools::GetPedPool()->CopyBack(pBuf2, pBuf3);
	CPools::GetObjectPool()->CopyBack(pBuf4, pBuf5);
	CPools::GetPtrNodePool()->CopyBack(pBuf6, pBuf7);
	CPools::GetEntryInfoNodePool()->CopyBack(pBuf8, pBuf9);
	CPools::GetDummyPool()->CopyBack(pBuf10, pBuf11);
	memcpy(CWorld::GetSector(0, 0), pWorld1, sizeof(CSector) * NUMSECTORS_X * NUMSECTORS_Y);
	delete[] pWorld1;
	pWorld1 = nil;
	CWorld::GetMovingEntityList() = WorldPtrList;
	CWorld::GetBigBuildingList(LEVEL_NONE) = BigBuildingPtrList;
	memcpy(CPickups::aPickUps, pPickups, sizeof(CPickup) * NUMPICKUPS);
	delete[] pPickups;
	pPickups = nil;
	memcpy(CReferences::aRefs, pReferences, sizeof(CReference) * NUMREFERENCES);
	delete[] pReferences;
	pReferences = nil;
	CReferences::pEmptyList = pEmptyReferences;
	pEmptyReferences = nil;
	memcpy(&TheCamera, pStoredCam, sizeof(CCamera));
	delete[] pStoredCam;
	pStoredCam = nil;
	memcpy(CRadar::ms_RadarTrace, pRadarBlips, sizeof(CBlip) * NUMRADARBLIPS);
	delete[] pRadarBlips;
	pRadarBlips = nil;
	FindPlayerPed()->m_pWanted = new CWanted(PlayerWanted); /* Nice memory leak */
	CWorld::Players[0] = PlayerInfo;
	int i = CPools::GetPedPool()->GetSize();
	while (i--){
		CPed* ped = CPools::GetPedPool()->GetSlot(i);
		if (!ped)
			continue;
		int mi = ped->GetModelIndex();
		CStreaming::RequestModel(mi, 0);
		CStreaming::LoadAllRequestedModels(false);
		ped->m_rwObject = nil;
		ped->m_modelIndex = -1;
		ped->SetModelIndex(mi);
		ped->m_pVehicleAnim = 0;
		ped->m_audioEntityId = DMAudio.CreateEntity(0, ped);
		DMAudio.SetEntityStatus(ped->m_audioEntityId, true);
		CPopulation::UpdatePedCount(ped->m_nPedType, false);
		if (ped->m_wepModelID >= 0)
			ped->AddWeaponModel(ped->m_wepModelID);
	}
	i = CPools::GetVehiclePool()->GetSize();
	while (i--){
		CVehicle* vehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!vehicle)
			continue;
		int mi = vehicle->GetModelIndex();
		CStreaming::RequestModel(mi, 0);
		CStreaming::LoadAllRequestedModels(false);
		vehicle->m_rwObject = nil;
		vehicle->m_modelIndex = -1;
		vehicle->SetModelIndex(mi);
		if (mi == MI_DODO){
			CAutomobile* dodo = (CAutomobile*)vehicle;
			RpAtomicSetFlags(GetFirstObject(dodo->m_aCarNodes[CAR_WHEEL_LF]), 0);
			CMatrix tmp1;
			tmp1.Attach(RwFrameGetMatrix(dodo->m_aCarNodes[CAR_WHEEL_RF]), false);
			CMatrix tmp2(RwFrameGetMatrix(dodo->m_aCarNodes[CAR_WHEEL_LF]), false);
			tmp1.GetPosition() += CVector(tmp2.GetPosition().x + 0.1f, 0.0f, tmp2.GetPosition().z);
			tmp1.UpdateRW();
		}
		if (vehicle->IsCar()){
			CAutomobile* car = (CAutomobile*)vehicle;
			int32 panels = car->Damage.m_panelStatus;
			car->Damage.m_panelStatus = 0;
			ApplyPanelDamageToCar(panels, car, true);
			car->SetDoorDamage(CAR_BONNET, DOOR_BONNET, true);
			car->SetDoorDamage(CAR_BOOT, DOOR_BOOT, true);
			car->SetDoorDamage(CAR_DOOR_LF, DOOR_FRONT_LEFT, true);
			car->SetDoorDamage(CAR_DOOR_RF, DOOR_FRONT_RIGHT, true);
			car->SetDoorDamage(CAR_DOOR_LR, DOOR_REAR_LEFT, true);
			car->SetDoorDamage(CAR_DOOR_RR, DOOR_REAR_RIGHT, true);
		}
		vehicle->m_audioEntityId = DMAudio.CreateEntity(0, vehicle);
		DMAudio.SetEntityStatus(vehicle->m_audioEntityId, true);
		CCarCtrl::UpdateCarCount(vehicle, false);
		if ((mi == MI_AIRTRAIN || mi == MI_DEADDODO) && vehicle->m_rwObject){
			CVehicleModelInfo* info = (CVehicleModelInfo*)CModelInfo::GetModelInfo(mi);
			if (RwObjectGetType(vehicle->m_rwObject) == rpATOMIC){
				vehicle->GetMatrix().Detach();
				if (vehicle->m_rwObject){
					if (RwObjectGetType(vehicle->m_rwObject) == rpATOMIC){
						RwFrame* frame = RpAtomicGetFrame(vehicle->m_rwObject);
						RpAtomicDestroy((RpAtomic*)vehicle->m_rwObject);
						RwFrameDestroy(frame);
					}
					vehicle->m_rwObject = nil;
				}
			}else{
				vehicle->DeleteRwObject();
				int model_id = info->m_wheelId;
				if (model_id != -1){
					if ((vehicle->m_rwObject = CModelInfo::GetModelInfo(model_id)->CreateInstance())){
						vehicle->GetMatrix().AttachRW(&((RwFrame*)vehicle->m_rwObject->parent)->modelling, false);
					}
				}
			}
		}
	}
	PrintElementsInPtrList();
	i = CPools::GetObjectPool()->GetSize();
	while (i--){
		CObject* object = CPools::GetObjectPool()->GetSlot(i);
		if (!object)
			continue;
		int mi = object->GetModelIndex();
		CStreaming::RequestModel(mi, 0);
		CStreaming::LoadAllRequestedModels(false);
		object->m_rwObject = nil;
		object->m_modelIndex = -1;
		object->SetModelIndex(mi);
		object->GetMatrix().m_attachment = nil;
		if (RwObjectGetType(object->m_rwObject) == rpATOMIC)
			object->GetMatrix().AttachRW(RwFrameGetMatrix(RpAtomicGetFrame(object->m_rwObject)), false);
	}
	i = CPools::GetDummyPool()->GetSize();
	while (i--){
		CDummy* dummy = CPools::GetDummyPool()->GetSlot(i);
		if (!dummy)
			continue;
		int mi = dummy->GetModelIndex();
		CStreaming::RequestModel(mi, 0);
		CStreaming::LoadAllRequestedModels(false);
		dummy->m_rwObject = nil;
		dummy->m_modelIndex = -1;
		dummy->SetModelIndex(mi);
		dummy->GetMatrix().m_attachment = nil;
		if (RwObjectGetType(dummy->m_rwObject) == rpATOMIC)
			dummy->GetMatrix().AttachRW(RwFrameGetMatrix(RpAtomicGetFrame(dummy->m_rwObject)), false);
	}
	CTimer::SetTimeInMilliseconds(Time1);
	CTimer::SetTimeInMillisecondsNonClipped(Time2);
	CTimer::SetPreviousTimeInMilliseconds(Time3);
	CTimer::SetTimeInMillisecondsPauseMode(Time4);
	CTimer::SetTimeScale(TimeScale);
	CTimer::SetFrameCounter(Frame);
	CTimer::SetTimeStep(TimeStep);
	CTimer::SetTimeStepNonClipped(TimeStepNonClipped);
	CClock::SetGameClock(ClockHours, ClockMinutes);
	CWeather::OldWeatherType = OldWeatherType;
	CWeather::NewWeatherType = NewWeatherType;
	CWeather::InterpolationValue = WeatherInterpolationValue;
	for (int i = 0; i < CPools::GetPedPool()->GetSize(); i++) {
		CPed* ped = CPools::GetPedPool()->GetSlot(i);
		if (!ped)
			continue;
		RetrieveDetailedPedAnimation(ped, &pPedAnims[i]);
	}
	free(pPedAnims);
	pPedAnims = nil;
	DMAudio.ChangeMusicMode(0);
	DMAudio.SetRadioInCar(OldRadioStation);
	DMAudio.ChangeMusicMode(1);
}
#endif

#if 0
WRAPPER void CReplay::EmptyPedsAndVehiclePools(void) { EAXJMP(0x5970E0); }
#else
void CReplay::EmptyPedsAndVehiclePools(void)
{
	int i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* v = CPools::GetVehiclePool()->GetSlot(i);
		if (!v)
			continue;
		CWorld::Remove(v);
		delete v;
	}
	i = CPools::GetPedPool()->GetSize();
	while (i--) {
		CPed* p = CPools::GetPedPool()->GetSlot(i);
		if (!p)
			continue;
		CWorld::Remove(p);
		delete p;
	}
}
#endif

#if 0
WRAPPER void CReplay::EmptyAllPools(void) { EAXJMP(0x5971B0); }
#else
void CReplay::EmptyAllPools(void)
{
	EmptyPedsAndVehiclePools();
	int i = CPools::GetObjectPool()->GetSize();
	while (i--) {
		CObject* o = CPools::GetObjectPool()->GetSlot(i);
		if (!o)
			continue;
		CWorld::Remove(o);
		delete o;
	}
	i = CPools::GetDummyPool()->GetSize();
	while (i--) {
		CDummy* d = CPools::GetDummyPool()->GetSlot(i);
		if (!d)
			continue;
		CWorld::Remove(d);
		delete d;
	}
}
#endif

#if 0
WRAPPER void CReplay::MarkEverythingAsNew(void) { EAXJMP(0x597280); }
#else
void CReplay::MarkEverythingAsNew(void)
{
	int i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* v = CPools::GetVehiclePool()->GetSlot(i);
		if (!v)
			continue;
		v->bHasAlreadyBeenRecorded = false;
	}
	i = CPools::GetPedPool()->GetSize();
	while (i--) {
		CPed* p = CPools::GetPedPool()->GetSlot(i);
		if (!p)
			continue;
		p->bHasAlreadyBeenRecorded = false;
	}
}
#endif

#if 0
WRAPPER void CReplay::SaveReplayToHD(void) { EAXJMP(0x597330); }
#else
void CReplay::SaveReplayToHD(void)
{
	CFileMgr::SetDirMyDocuments();
	int fw = CFileMgr::OpenFileForWriting("replay.rep");
	if (fw < 0){
		debug("Couldn't open replay.rep for writing");
		CFileMgr::SetDir("");
		return;
	}
	CFileMgr::Write(fw, "gta3_7f", sizeof("gta3_7f"));
	int current;
	for (current = 0; current < 8; current++)
		if (BufferStatus[current] == REPLAYBUFFER_RECORD)
			break;
	int first;
	for (first = (current + 1) % 8; ; first = (first + 1) % 8)
		if (BufferStatus[first] == REPLAYBUFFER_RECORD || BufferStatus[first] == REPLAYBUFFER_PLAYBACK)
			break;
	for(int i = first;; i = (i + 1) % 8 ){
		CFileMgr::Write(fw, (char*)Buffers[first], sizeof(Buffers[first]));
		if (BufferStatus[i] == REPLAYBUFFER_RECORD)
			break;
	}
	CFileMgr::CloseFile(fw);
	CFileMgr::SetDir("");
}
#endif

#if 0
WRAPPER void PlayReplayFromHD(void) { EAXJMP(0x597420); }
#else
void PlayReplayFromHD(void)
{
	CFileMgr::SetDirMyDocuments();
	int fr = CFileMgr::OpenFile("replay.rep", "rb");
	if (fr < 0) {
		debug("Couldn't open replay.rep for reading");
		/* Forgot to SetDir? */
		return;
	}
	CFileMgr::Read(fr, gString, 8);
	if (strncmp(gString, "gta3_7f", sizeof("gta3_7f"))){
		CFileMgr::CloseFile(fr);
		debug("Wrong file type for replay");
		CFileMgr::SetDir("");
		return;
	}
	int slot;
	for (slot = 0; CFileMgr::Read(fr, (char*)CReplay::Buffers[slot], sizeof(CReplay::Buffers[slot])); slot++)
		CReplay::BufferStatus[slot] = CReplay::REPLAYBUFFER_PLAYBACK;
	CReplay::BufferStatus[slot - 1] = CReplay::REPLAYBUFFER_RECORD;
	while (slot < 8)
		CReplay::BufferStatus[slot++] = CReplay::REPLAYBUFFER_UNUSED;
	CFileMgr::CloseFile(fr);
	CFileMgr::SetDir("");
	CReplay::TriggerPlayback(CReplay::REPLAYCAMMODE_ASSTORED, 0.0f, 0.0f, 0.0f, false);
	CReplay::bPlayingBackFromFile = true;
	CReplay::bAllowLookAroundCam = true;
	CReplay::StreamAllNecessaryCarsAndPeds();
}
#endif

#if 0
WRAPPER void CReplay::StreamAllNecessaryCarsAndPeds(void) { EAXJMP(0x597560); }
#else
void CReplay::StreamAllNecessaryCarsAndPeds(void)
{
	for (int slot = 0; slot < 8; slot++) {
		if (BufferStatus[slot] == REPLAYBUFFER_UNUSED)
			continue;
		for (int offset = 0; Buffers[slot][offset] != REPLAYPACKET_END; offset += FindSizeOfPacket(Buffers[slot][offset])) {
			switch (Buffers[slot][offset]) {
			case REPLAYPACKET_VEHICLE:
				CStreaming::RequestModel(((tVehicleUpdatePacket*)&Buffers[slot][offset])->mi, 0);
				break;
			case REPLAYPACKET_PED_HEADER:
				CStreaming::RequestModel(((tPedHeaderPacket*)&Buffers[slot][offset])->mi, 0);
				break;
			default:
				break;
			}
		}
	}
	CStreaming::LoadAllRequestedModels(false);
}
#endif

#if 0
WRAPPER void CReplay::FindFirstFocusCoordinate(CVector *coord) { EAXJMP(0x5975E0); }
#else
void CReplay::FindFirstFocusCoordinate(CVector *coord)
{
	*coord = CVector(0.0f, 0.0f, 0.0f);
	for (int slot = 0; slot < 8; slot++) {
		if (BufferStatus[slot] == REPLAYBUFFER_UNUSED)
			continue;
		for (int offset = 0; Buffers[slot][offset] != REPLAYPACKET_END; offset += FindSizeOfPacket(Buffers[slot][offset])) {
			if (Buffers[slot][offset] == REPLAYPACKET_GENERAL) {
				*coord = ((tGeneralPacket*)&Buffers[slot][offset])->player_pos;
				return;
			}
		}
	}
}
#endif

#if 0
WRAPPER bool CReplay::ShouldStandardCameraBeProcessed(void) { EAXJMP(0x597680); }
#else
bool CReplay::ShouldStandardCameraBeProcessed(void)
{
	if (Mode != MODE_PLAYBACK)
		return true;
	if (FramesActiveLookAroundCam || bPlayerInRCBuggy)
		return false;
	return FindPlayerVehicle() != nil;
}
#endif

#if 0
WRAPPER void CReplay::ProcessLookAroundCam(void) { EAXJMP(0x5976C0); }
#else
void CReplay::ProcessLookAroundCam(void)
{
	if (!bAllowLookAroundCam)
		return;
	float x_moved = CPad::NewMouseControllerState.x / 200.0f;
	float y_moved = CPad::NewMouseControllerState.y / 200.0f;
	if (x_moved > 0.01f || y_moved > 0.01f) {
		if (FramesActiveLookAroundCam == 0)
			fDistanceLookAroundCam = 9.0f;
		FramesActiveLookAroundCam = 60;
	}
	if (bPlayerInRCBuggy)
		FramesActiveLookAroundCam = 0;
	if (!FramesActiveLookAroundCam)
		return;
	--FramesActiveLookAroundCam;
	fBetaAngleLookAroundCam += x_moved;
	if (CPad::NewMouseControllerState.LMB && CPad::NewMouseControllerState.RMB)
		fDistanceLookAroundCam = max(3.0f, min(15.0f, fDistanceLookAroundCam + 2.0f * y_moved));
	else
		fAlphaAngleLookAroundCam = max(0.1f, min(1.5f, fAlphaAngleLookAroundCam + y_moved));
	CVector camera_pt(
		fDistanceLookAroundCam * Sin(fBetaAngleLookAroundCam) * Cos(fAlphaAngleLookAroundCam),
		fDistanceLookAroundCam * Cos(fBetaAngleLookAroundCam) * Cos(fAlphaAngleLookAroundCam),
		fDistanceLookAroundCam * Sin(fAlphaAngleLookAroundCam)
	);
	CVector focus = CVector(CameraFocusX, CameraFocusY, CameraFocusZ);
	camera_pt += focus;
	CColPoint cp;
	CEntity* pe = nil;
	if (CWorld::ProcessLineOfSight(focus, camera_pt, cp, pe, true, false, false, false, false, true, true)){
		camera_pt = cp.point;
		CVector direction = focus - cp.point;
		direction.Normalise();
		camera_pt += direction / 4.0f;
	}
	CVector forward = focus - camera_pt;
	forward.Normalise();
	CVector right = CrossProduct(CVector(0.0f, 0.0f, 1.0f), forward);
	right.Normalise();
	CVector up = CrossProduct(forward, right);
	up.Normalise();
	TheCamera.GetMatrix().GetForward() = forward;
	TheCamera.GetMatrix().GetUp() = up;
	TheCamera.GetMatrix().GetRight() = right;
	TheCamera.GetMatrix().GetPosition() = camera_pt;
	RwMatrix* pm = RwFrameGetMatrix(RwCameraGetFrame(TheCamera.m_pRwCamera));
	pm->pos = *(RwV3d*)&TheCamera.GetMatrix().GetPosition();
	pm->at = *(RwV3d*)&TheCamera.GetMatrix().GetForward();
	pm->up = *(RwV3d*)&TheCamera.GetMatrix().GetUp();
	pm->right = *(RwV3d*)&TheCamera.GetMatrix().GetRight();
	TheCamera.CalculateDerivedValues();
	RwMatrixUpdate(RwFrameGetMatrix(RwCameraGetFrame(TheCamera.m_pRwCamera)));
	RwFrameUpdateObjects(RwCameraGetFrame(TheCamera.m_pRwCamera));
}
#endif

#if 0
WRAPPER size_t CReplay::FindSizeOfPacket(uint8 type) { EAXJMP(0x597CC0); }
#else
size_t CReplay::FindSizeOfPacket(uint8 type)
{
	switch (type) {
	case REPLAYPACKET_END:			return 4;
	case REPLAYPACKET_VEHICLE:		return sizeof(tVehicleUpdatePacket);
	case REPLAYPACKET_PED_HEADER:	return sizeof(tPedHeaderPacket);
	case REPLAYPACKET_PED_UPDATE:	return sizeof(tPedUpdatePacket);
	case REPLAYPACKET_GENERAL:		return sizeof(tGeneralPacket);
	case REPLAYPACKET_CLOCK:		return sizeof(tClockPacket);
	case REPLAYPACKET_WEATHER:		return sizeof(tWeatherPacket);
	case REPLAYPACKET_ENDOFFRAME:	return 4;
	case REPLAYPACKET_TIMER:		return sizeof(tTimerPacket);
	case REPLAYPACKET_BULLET_TRACES:return sizeof(tBulletTracePacket);
	default: break;
	}
	return 0;
}
#endif

#if 0
WRAPPER void CReplay::Display(void) { EAXJMP(0x595EE0); }
#else
void CReplay::Display()
{
	static int counter = 0;
	if (Mode == MODE_RECORD)
		return;
	counter = (counter + 1) % 65536;
	if ((counter & 0x20) == 0)
		return;
	CFont::SetPropOn();
	CFont::SetBackgroundOff();
	CFont::SetScale(SCREEN_SCALE_X(1.5f), SCREEN_SCALE_Y(1.5f));
	CFont::SetAlignment(ALIGN_LEFT);
	CFont::SetColor(CRGBA(255, 255, 200, 200));
	CFont::SetFontStyle(FONT_BANK);
	if (Mode == MODE_PLAYBACK)
		CFont::PrintString(SCREEN_SCALE_X(63.5f), SCREEN_SCALE_Y(30.0f), TheText.Get("REPLAY"));
}
#endif

STARTPATCHES
InjectHook(0x592FE0, &CReplay::Init, PATCH_JUMP);
InjectHook(0x593150, &CReplay::DisableReplays, PATCH_JUMP);
InjectHook(0x593160, &CReplay::EnableReplays, PATCH_JUMP);
InjectHook(0x593170, &CReplay::Update, PATCH_JUMP);
InjectHook(0x595B20, &CReplay::FinishPlayback, PATCH_JUMP);
InjectHook(0x595BD0, &CReplay::EmptyReplayBuffer, PATCH_JUMP);
InjectHook(0x595EE0, &CReplay::Display, PATCH_JUMP);
InjectHook(0x596030, &CReplay::TriggerPlayback, PATCH_JUMP);
InjectHook(0x597560, &CReplay::StreamAllNecessaryCarsAndPeds, PATCH_JUMP);
InjectHook(0x597680, &CReplay::ShouldStandardCameraBeProcessed, PATCH_JUMP);
ENDPATCHES
