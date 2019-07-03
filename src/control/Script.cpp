#include "common.h"
#include "patcher.h"

#include "Script.h"

#include "Camera.h"
#include "CarCtrl.h"
#include "DMAudio.h"
#include "Hud.h"
#include "ModelIndices.h"
#include "PlayerInfo.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "Population.h"
#include "Streaming.h"
#include "User.h"
#include "Weather.h"
#include "World.h"

uint8 (&CTheScripts::ScriptSpace)[160 * 1024] = *(uint8(*)[160 * 1024])*(uintptr*)0x74B248;
CTextLine (&CTheScripts::IntroTextLines)[2] = *(CTextLine (*)[2])*(uintptr*)0x70EA74;
CScriptRectangle (&CTheScripts::IntroRectangles)[16] = *(CScriptRectangle (*)[16])*(uintptr*)0x72D108;
CSprite2d (&CTheScripts::ScriptSprites)[16] = *(CSprite2d(*)[16])*(uintptr*)0x72B090;
bool &CTheScripts::DbgFlag = *(bool*)0x95CD87;
uint32 &CTheScripts::OnAMissionFlag = *(uint32*)0x8F2A24;
int32 &CTheScripts::StoreVehicleIndex = *(int32*)0x8F5F3C;
bool &CTheScripts::StoreVehicleWasRandom = *(bool*)0x95CDBC;

CMissionCleanup(&CTheScripts::MissionCleanup) = *(CMissionCleanup*)0x8F2AD8;
CUpsideDownCarCheck(&CTheScripts::UpsideDownCars) = *(CUpsideDownCarCheck*)0x6EE450;
CStuckCarCheck(&CTheScripts::StuckCars) = *(CStuckCarCheck*)0x87C588;

CMissionCleanup::CMissionCleanup()
{
	Init();
}

void CMissionCleanup::Init()
{
	for (int i = 0; i < MAX_CLEANUP; i++){
		m_sEntities[i].type = CLEANUP_UNUSED;
		m_sEntities[i].id = 0;
	}
}

CMissionCleanupEntity* CMissionCleanup::FindFree()
{
	for (int i = 0; i < MAX_CLEANUP; i++){
		if (m_sEntities[i].type == CLEANUP_UNUSED)
			return &m_sEntities[i];
	}
	assert(0);
	return nil;
}

void CMissionCleanup::AddEntityToList(int32 id, uint8 type)
{
	CMissionCleanupEntity* pNew = FindFree();
	if (!pNew)
		return;
	pNew->id = id;
	pNew->type = type;
	m_bCount++;
}

void CMissionCleanup::RemoveEntityFromList(int32 id, uint8 type)
{
	for (int i = 0; i < MAX_CLEANUP; i++){
		if (m_sEntities[i].type == type && m_sEntities[i].id == 0){
			m_sEntities[i].id = 0;
			m_sEntities[i].type = CLEANUP_UNUSED;
		}
	}
}

void CMissionCleanup::Process()
{
	CPopulation::m_AllRandomPedsThisType = -1;
	CPopulation::PedDensityMultiplier = 1.0f;
	CCarCtrl::CarDensityMultiplier = 1.0;
	FindPlayerPed()->m_pWanted->m_fCrimeSensitivity = 1.0f;
	TheCamera.Restore();
	TheCamera.SetWidescreenOff();
	DMAudio.ClearMissionAudio();
	CWeather::ReleaseWeather();
	for (int i = 0; i < NUM_OF_SPECIAL_CHARS; i++)
		CStreaming::SetMissionDoesntRequireSpecialChar(i);
	for (int i = 0; i < NUM_OF_CUTSCENE_OBJECTS; i++)
		CStreaming::SetMissionDoesntRequireModel(MI_CUTOBJ01 + i);
	CStreaming::ms_disableStreaming = false;
	CHud::m_ItemToFlash = -1;
	CHud::SetHelpMessage(nil, false);
	CUserDisplay::OnscnTimer.m_bDisabled = false;
	CWorld::Players[0].m_pPed->m_pWanted->m_IsIgnoredByCops = false;
	CWorld::Players[0].m_pPed->m_pWanted->m_IsIgnoredByEveryOne = false;
	CWorld::Players[0].MakePlayerSafe(false);
	CTheScripts::StoreVehicleIndex = -1;
	CTheScripts::StoreVehicleWasRandom = true;
	CTheScripts::UpsideDownCars.Init();
	CTheScripts::StuckCars.Init();
	for (int i = 0; i < MAX_CLEANUP; i++){
		if (m_sEntities[i].type == CLEANUP_UNUSED)
			continue;
		switch (m_sEntities[i].type) {
		case CLEANUP_CAR:
		{
			CVehicle* v = CPools::GetVehiclePool()->GetAt(m_sEntities[i].id);
			if (v)
				CTheScripts::CleanUpThisVehicle(v);
			break;
		}
		case CLEANUP_CHAR:
		{
			CPed* p = CPools::GetPedPool()->GetAt(m_sEntities[i].id);
			if (p)
				CTheScripts::CleanUpThisPed(p);
			break;
		}
		case CLEANUP_OBJECT:
		{
			CObject* o = CPools::GetObjectPool()->GetAt(m_sEntities[i].id);
			if (o)
				CTheScripts::CleanUpThisObject(o);
			break;
		}
		default:
			break;
		}
	}
}

void CUpsideDownCarCheck::Init()
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		m_sCars[i].m_nVehicleIndex = -1;
		m_sCars[i].m_nVehicleIndex = 0;
	}
}

void CStuckCarCheck::Init()
{
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++) {
		m_sCars[i].m_nVehicleIndex = -1;
		m_sCars[i].m_vecPos = CVector(-5000.0f, -5000.0f, -5000.0f);
		m_sCars[i].m_nStartTime = -1;
		m_sCars[i].m_fDistance = 0.0f;
		m_sCars[i].m_nStuckTime = 0;
		m_sCars[i].m_bStuck = false;
	}
}

WRAPPER void CTheScripts::CleanUpThisVehicle(CVehicle*) { EAXJMP(0x4548D0); }
WRAPPER void CTheScripts::CleanUpThisPed(CPed*) { EAXJMP(0x4547A0); }
WRAPPER void CTheScripts::CleanUpThisObject(CObject*) { EAXJMP(0x454910); }
WRAPPER bool CTheScripts::IsPlayerOnAMission() { EAXJMP(0x439410); }
WRAPPER void CTheScripts::ScriptDebugLine3D(float x1, float y1, float z1, float x2, float y2, float z2, int col, int col2) { EAXJMP(0x4534E0); }

STARTPATCHES
InjectHook(0x437AE0, &CMissionCleanup::Init, PATCH_JUMP);
InjectHook(0x437BA0, &CMissionCleanup::AddEntityToList, PATCH_JUMP);
InjectHook(0x437BD0, &CMissionCleanup::RemoveEntityFromList, PATCH_JUMP);
InjectHook(0x437C10, &CMissionCleanup::Process, PATCH_JUMP);
ENDPATCHES