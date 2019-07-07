#include "common.h"
#include "patcher.h"

#include "Script.h"

#include "Camera.h"
#include "CarCtrl.h"
#include "DMAudio.h"
#include "FileMgr.h"
#include "Hud.h"
#include "ModelIndices.h"
#include "PlayerInfo.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "Population.h"
#include "Replay.h"
#include "Streaming.h"
#include "User.h"
#include "Weather.h"
#include "World.h"

uint8 (&CTheScripts::ScriptSpace)[SIZE_SCRIPT_SPACE] = *(uint8(*)[SIZE_SCRIPT_SPACE])*(uintptr*)0x74B248;
CRunningScript(&CTheScripts::ScriptsArray)[MAX_NUM_SCRIPTS] = *(CRunningScript(*)[MAX_NUM_SCRIPTS])*(uintptr*)0x6F5C08;
int32(&CTheScripts::BaseBriefIdForContact)[MAX_NUM_CONTACTS] = *(int32(*)[MAX_NUM_CONTACTS])*(uintptr*)0x880200;
int32(&CTheScripts::OnAMissionForContactFlag)[MAX_NUM_CONTACTS] = *(int32(*)[MAX_NUM_CONTACTS])*(uintptr*)0x8622F0;
CTextLine (&CTheScripts::IntroTextLines)[MAX_NUM_INTRO_TEXT_LINES] = *(CTextLine (*)[MAX_NUM_INTRO_TEXT_LINES])*(uintptr*)0x70EA68;
CScriptRectangle (&CTheScripts::IntroRectangles)[MAX_NUM_INTRO_RECTANGLES] = *(CScriptRectangle (*)[MAX_NUM_INTRO_RECTANGLES])*(uintptr*)0x72D108;
CSprite2d (&CTheScripts::ScriptSprites)[MAX_NUM_SCRIPT_SRPITES] = *(CSprite2d(*)[MAX_NUM_SCRIPT_SRPITES])*(uintptr*)0x72B090;
CScriptSphere(&CTheScripts::ScriptSphereArray)[MAX_NUM_SCRIPT_SPHERES] = *(CScriptSphere(*)[MAX_NUM_SCRIPT_SPHERES])*(uintptr*)0x727D60;
tCollectiveData(&CTheScripts::CollectiveArray)[MAX_NUM_COLLECTIVES] = *(tCollectiveData(*)[MAX_NUM_COLLECTIVES])*(uintptr*)0x6FA008;
tUsedObject(&CTheScripts::UsedObjectArray)[MAX_NUM_USED_OBJECTS] = *(tUsedObject(*)[MAX_NUM_USED_OBJECTS])*(uintptr*)0x6E69C8;
int32(&CTheScripts::MultiScriptArray)[MAX_NUM_MISSION_SCRIPTS] = *(int32(*)[MAX_NUM_MISSION_SCRIPTS])*(uintptr*)0x6F0558;
tBuildingSwap(&CTheScripts::BuildingSwapArray)[MAX_NUM_BUILDING_SWAPS] = *(tBuildingSwap(*)[MAX_NUM_BUILDING_SWAPS])*(uintptr*)0x880E30;
CEntity*(&CTheScripts::InvisibilitySettingArray)[MAX_NUM_INVISIBILITY_SETTINGS] = *(CEntity*(*)[MAX_NUM_INVISIBILITY_SETTINGS])*(uintptr*)0x8620F0;
bool &CTheScripts::DbgFlag = *(bool*)0x95CD87;
uint32 &CTheScripts::OnAMissionFlag = *(uint32*)0x8F1B64;
int32 &CTheScripts::StoreVehicleIndex = *(int32*)0x8F5F3C;
bool &CTheScripts::StoreVehicleWasRandom = *(bool*)0x95CDBC;
CRunningScript *&CTheScripts::pIdleScripts = *(CRunningScript**)0x9430D4;
CRunningScript *&CTheScripts::pActiveScripts = *(CRunningScript**)0x8E2BF4;
uint32 &CTheScripts::NextFreeCollectiveIndex = *(uint32*)0x942F98;
int32 &CTheScripts::LastRandomPedId = *(int32*)0x8F251C;
uint16 &CTheScripts::NumberOfUsedObjects = *(uint16*)0x95CC72;
bool &CTheScripts::bAlreadyRunningAMissionScript = *(bool*)0x95CDB3;
bool &CTheScripts::bUsingAMultiScriptFile = *(bool*)0x95CD55;
uint16 &CTheScripts::NumberOfMissionScripts = *(uint16*)0x95CC9A;
uint32 &CTheScripts::LargestMissionScriptSize = *(uint32*)0x9414C8;
uint32 &CTheScripts::MainScriptSize = *(uint32*)0x9405A4;
uint8 &CTheScripts::FailCurrentMission = *(uint8*)0x95CD41;
uint8 &CTheScripts::CountdownToMakePlayerUnsafe = *(uint8*)0x95CD51;
uint8 &CTheScripts::DelayMakingPlayerUnsafeThisTime = *(uint8*)0x95CD88;
uint16 &CTheScripts::NumScriptDebugLines = *(uint16*)0x95CC42;
uint16 &CTheScripts::NumberOfIntroRectanglesThisFrame = *(uint16*)0x95CC88;
uint16 &CTheScripts::NumberOfIntroTextLinesThisFrame = *(uint16*)0x95CC32;
bool &CTheScripts::UseTextCommands = *(bool*)0x95CD57;
CMissionCleanup (&CTheScripts::MissionCleanup) = *(CMissionCleanup*)0x8F2A24;
CUpsideDownCarCheck (&CTheScripts::UpsideDownCars) = *(CUpsideDownCarCheck*)0x6EE450;
CStuckCarCheck (&CTheScripts::StuckCars) = *(CStuckCarCheck*)0x87C588;
uint16 &CTheScripts::CommandsExecuted = *(uint16*)0x95CCA6;
uint16 &CTheScripts::ScriptsUpdated = *(uint16*)0x95CC5E;
int32(&ScriptParams)[32] = *(int32(*)[32])*(uintptr*)0x6ED460;

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

/* NB: CUpsideDownCarCheck is not used by actual script at all
 * It has a weird usage: AreAnyCarsUpsideDown would fail any mission
 * just like death or arrest. */

void CUpsideDownCarCheck::Init()
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		m_sCars[i].m_nVehicleIndex = -1;
		m_sCars[i].m_nVehicleIndex = 0;
	}
}

bool CUpsideDownCarCheck::IsCarUpsideDown(int32 id)
{
	CVehicle* v = CPools::GetVehiclePool()->GetAt(id);
	return v->GetUp().z <= -0.97f &&
		v->GetMoveSpeed().Magnitude() < 0.01f &&
		v->GetTurnSpeed().Magnitude() < 0.02f;
}

void CUpsideDownCarCheck::UpdateTimers()
{
	uint32 timeStep = CTimer::GetTimeStepInMilliseconds();
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		CVehicle* v = CPools::GetVehiclePool()->GetAt(m_sCars[i].m_nVehicleIndex);
		if (v){
			if (IsCarUpsideDown(m_sCars[i].m_nVehicleIndex))
				m_sCars[i].m_nUpsideDownTimer += timeStep;
			else
				m_sCars[i].m_nUpsideDownTimer = 0;
		}else{
			m_sCars[i].m_nVehicleIndex = -1;
			m_sCars[i].m_nUpsideDownTimer = 0;
		}
	}
}

bool CUpsideDownCarCheck::AreAnyCarsUpsideDown()
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex >= 0 && m_sCars[i].m_nUpsideDownTimer > 1000)
			return true;
	}
	return false;
}

void CUpsideDownCarCheck::AddCarToCheck(int32 id)
{
	uint16 index = 0;
	while (index < MAX_UPSIDEDOWN_CAR_CHECKS && m_sCars[index].m_nVehicleIndex >= 0)
		index++;
	if (index >= MAX_UPSIDEDOWN_CAR_CHECKS)
		return;
	m_sCars[index].m_nVehicleIndex = id;
	m_sCars[index].m_nUpsideDownTimer = 0;
}

void CUpsideDownCarCheck::RemoveCarFromCheck(int32 id)
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id){
			m_sCars[i].m_nVehicleIndex = -1;
			m_sCars[i].m_nUpsideDownTimer = 0;
		}
	}
}

bool CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile(int32 id)
{
	for (int i = 0; i < MAX_UPSIDEDOWN_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id)
			return m_sCars[i].m_nUpsideDownTimer > 1000;
	}
	return false;
}

void CStuckCarCheckEntry::Reset()
{
	m_nVehicleIndex = -1;
	m_vecPos = CVector(-5000.0f, -5000.0f, -5000.0f);
	m_nLastCheck = -1;
	m_fRadius = 0.0f;
	m_nStuckTime = 0;
	m_bStuck = false;
}

void CStuckCarCheck::Init()
{
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++) {
		m_sCars[i].Reset();
	}
}

void CStuckCarCheck::Process()
{
	uint32 timer = CTimer::GetTimeInMilliseconds();
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex < 0)
			continue;
		if (timer <= m_sCars[i].m_nStuckTime + m_sCars[i].m_nLastCheck)
			continue;
		CVehicle* pv = CPools::GetVehiclePool()->GetAt(m_sCars[i].m_nVehicleIndex);
		if (!pv){
			m_sCars[i].Reset();
			continue;
		}
		float distance = (pv->GetPosition() - m_sCars[i].m_vecPos).Magnitude();
		m_sCars[i].m_bStuck = distance < m_sCars[i].m_fRadius;
		m_sCars[i].m_vecPos = pv->GetPosition();
		m_sCars[i].m_nLastCheck = timer;
	}
}

void CStuckCarCheck::AddCarToCheck(int32 id, float radius, uint32 time)
{
	CVehicle* pv = CPools::GetVehiclePool()->GetAt(id);
	if (!pv)
		return;
	int index = 0;
	while (index < MAX_STUCK_CAR_CHECKS && m_sCars[index].m_nVehicleIndex >= 0)
		index++;
	/* Would be nice to return if index >= MAX_STUCK_CAR_CHECKS... */
	m_sCars[index].m_nVehicleIndex = id;
	m_sCars[index].m_vecPos = pv->GetPosition();
	m_sCars[index].m_nLastCheck = CTimer::GetTimeInMilliseconds();
	m_sCars[index].m_fRadius = radius;
	m_sCars[index].m_nStuckTime = time;
	m_sCars[index].m_bStuck = false;
}

void CStuckCarCheck::RemoveCarFromCheck(int32 id)
{
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id){
			m_sCars[i].Reset();
		}
	}
}

bool CStuckCarCheck::HasCarBeenStuckForAWhile(int32 id)
{
	for (int i = 0; i < MAX_STUCK_CAR_CHECKS; i++){
		if (m_sCars[i].m_nVehicleIndex == id)
			return m_sCars[i].m_bStuck;
	}
	return false;
}

void CRunningScript::CollectParameters(uint32* pIp, int16 total)
{
	for (int16 i = 0; i < total; i++){
		float tmp;
		switch (CTheScripts::Read1ByteFromScript(pIp))
		{
		case ARGUMENT_INT32:
			ScriptParams[i] = CTheScripts::Read4BytesFromScript(pIp);
			break;
		case ARGUMENT_GLOBALVAR:
			ScriptParams[i] = *((int32*)&CTheScripts::ScriptSpace[CTheScripts::Read2BytesFromScript(pIp)]);
			break;
		case ARGUMENT_LOCALVAR:
			ScriptParams[i] = m_anLocalVariables[CTheScripts::Read2BytesFromScript(pIp)];
			break;
		case ARGUMENT_INT8:
			ScriptParams[i] = CTheScripts::Read1ByteFromScript(pIp);
			break;
		case ARGUMENT_INT16:
			ScriptParams[i] = CTheScripts::Read2BytesFromScript(pIp);
			break;
		case ARGUMENT_FLOAT:
			tmp = CTheScripts::ReadFloatFromScript(pIp);
			ScriptParams[i] = *(int32*)&tmp;
			break;
		default:
			assert(0);
			break;
		}
	}
}

int32 CRunningScript::CollectNextParameterWithoutIncreasingPC(uint32 ip)
{
	uint32* pIp = &ip;
	float tmp;
	switch (CTheScripts::Read1ByteFromScript(pIp))
	{
	case ARGUMENT_INT32:
		return CTheScripts::Read4BytesFromScript(pIp);
	case ARGUMENT_GLOBALVAR:
		return *((int32*)&CTheScripts::ScriptSpace[CTheScripts::Read2BytesFromScript(pIp)]);
	case ARGUMENT_LOCALVAR:
		return m_anLocalVariables[CTheScripts::Read2BytesFromScript(pIp)];
	case ARGUMENT_INT8:
		return CTheScripts::Read1ByteFromScript(pIp);
	case ARGUMENT_INT16:
		return CTheScripts::Read2BytesFromScript(pIp);
	case ARGUMENT_FLOAT:
		tmp = CTheScripts::ReadFloatFromScript(pIp);
		return *(int32*)&tmp;
	default:
		assert(0);
	}
	return -1;
}

void CRunningScript::StoreParameters(uint32* pIp, int16 number)
{
	for (int16 i = 0; i < number; i++){
		switch (CTheScripts::Read1ByteFromScript(pIp)) {
		case ARGUMENT_GLOBALVAR:
			*(int32*)&CTheScripts::ScriptSpace[CTheScripts::Read2BytesFromScript(pIp)] = ScriptParams[i];
			break;
		case ARGUMENT_LOCALVAR:
			m_anLocalVariables[CTheScripts::Read2BytesFromScript(pIp)] = ScriptParams[i];
			break;
		default:
			assert(0);
		}
	}
}

int32 *CRunningScript::GetPointerToScriptVariable(uint32* pIp, int16 type)
{
	switch (CTheScripts::Read1ByteFromScript(pIp))
	{
	case ARGUMENT_GLOBALVAR:
		assert(type == VAR_GLOBAL);
		return (int32*)&CTheScripts::ScriptSpace[CTheScripts::Read2BytesFromScript(pIp)];
	case ARGUMENT_LOCALVAR:
		assert(type == VAR_LOCAL);
		return &m_anLocalVariables[CTheScripts::Read2BytesFromScript(pIp)];
	default:
		assert(0);
	}
	return nil;
}

void CRunningScript::Init()
{
	strcpy(m_abScriptName, "noname");
	next = prev = nil;
	m_nIp = 0;
	for (int i = 0; i < MAX_STACK_DEPTH; i++)
		m_anStack[i] = 0;
	m_nStackPointer = 0;
	m_nWakeTime = 0;
	m_bCondResult = false;
	m_bIsMissionThread = false;
	m_bSkipWakeTime = false;
	for (int i = 0; i < NUM_LOCAL_VARS + NUM_TIMERS; i++)
		m_anLocalVariables[i] = 0;
	m_nAndOrState = 0;
	m_bNotFlag = false;
	m_bWBCheckEnabled = true;
	m_bWBChecked = false;
	m_bMissionFlag = false;
}

#ifdef USE_DEBUG_SCRIPT_LOADER
int open_script()
{
	static int scriptToLoad = 1;

	if (GetAsyncKeyState('G') & 0x8000)
		scriptToLoad = 0;
	if (GetAsyncKeyState('R') & 0x8000)
		scriptToLoad = 1;
	if (GetAsyncKeyState('D') & 0x8000)
		scriptToLoad = 2;

	switch (scriptToLoad) {
	case 0: return CFileMgr::OpenFile("main.scm", "rb");
	case 1: return CFileMgr::OpenFile("main_freeroam.scm", "rb");
	case 2: return CFileMgr::OpenFile("main_d.scm", "rb");
	}
	return CFileMgr::OpenFile("main.scm", "rb");
}
#endif

void CTextLine::Reset()
{
	m_fScaleX = 0.48f;
	m_fScaleY = 1.12f;
	m_sColor = CRGBA(225, 225, 225, 255);
	m_bJustify = false;
	m_bRightJustify = false;
	m_bCentered = false;
	m_bBackground = false;
	m_bBackgroundOnly = false;
	m_fWrapX = 182.0f; /* TODO: scaling as bugfix */
	m_fCenterSize = 640.0f; /* --||-- */
	m_sBackgroundColor = CRGBA(128, 128, 128, 128);
	m_bTextProportional = true;
	m_bTextBeforeFade = false;
	m_nFont = 2; /* enum? */
	m_fAtX = 0.0f;
	m_fAtY = 0.0f;
	memset(&m_Text, 0, sizeof(m_Text));
}

void CTheScripts::Init()
{
	for (int i = 0; i < SIZE_SCRIPT_SPACE; i++)
		ScriptSpace[i] = 0;
	pActiveScripts = pIdleScripts = nil;
	for (int i = 0; i < MAX_NUM_SCRIPTS; i++){
		ScriptsArray[i].Init();
		ScriptsArray[i].AddScriptToList(&pIdleScripts);
	}
	MissionCleanup.Init();
	UpsideDownCars.Init();
	StuckCars.Init();
	CFileMgr::SetDir("data");
#ifdef USE_DEBUG_SCRIPT_LOADER
	int mainf = open_script();
#else
	int mainf = CFileMgr::OpenFile("main.scm", "rb");
#endif
	CFileMgr::Read(mainf, (char*)ScriptSpace, SIZE_MAIN_SCRIPT);
	CFileMgr::CloseFile(mainf);
	CFileMgr::SetDir("");
	StoreVehicleIndex = -1;
	StoreVehicleWasRandom = true;
	OnAMissionFlag = 0;
	for (int i = 0; i < MAX_NUM_CONTACTS; i++){
		BaseBriefIdForContact[i] = 0;
		OnAMissionForContactFlag[i] = 0;
	}
	for (int i = 0; i < MAX_NUM_COLLECTIVES; i++){
		CollectiveArray[i].index = -1;
		CollectiveArray[i].unk_data = 0;
	}
	NextFreeCollectiveIndex = 0;
	LastRandomPedId = -1;
	for (int i = 0; i < MAX_NUM_USED_OBJECTS; i++){
		memset(&UsedObjectArray[i].name, 0, sizeof(UsedObjectArray[i].name));
		UsedObjectArray[i].index = 0;
	}
	NumberOfUsedObjects = 0;
	ReadObjectNamesFromScript();
	UpdateObjectIndices();
	bAlreadyRunningAMissionScript = false;
	bUsingAMultiScriptFile = true;
	for (int i = 0; i < MAX_NUM_MISSION_SCRIPTS; i++)
		MultiScriptArray[i] = 0;
	NumberOfMissionScripts = 0;
	LargestMissionScriptSize = 0;
	MainScriptSize = 0;
	ReadMultiScriptFileOffsetsFromScript();
	FailCurrentMission = 0;
	CountdownToMakePlayerUnsafe = 0;
	DbgFlag = 0;
	DelayMakingPlayerUnsafeThisTime = 0;
	NumScriptDebugLines = 0;
	for (int i = 0; i < MAX_NUM_SCRIPT_SPHERES; i++){
		ScriptSphereArray[i].m_bInUse = false;
		ScriptSphereArray[i].m_Index = 1;
		ScriptSphereArray[i].m_Id = 0;
		ScriptSphereArray[i].m_vecCenter = CVector(0.0f, 0.0f, 0.0f);
		ScriptSphereArray[i].m_fRadius = 0.0f;
	}
	for (int i = 0; i < MAX_NUM_INTRO_TEXT_LINES; i++){
		IntroTextLines[i].Reset();
	}
	NumberOfIntroTextLinesThisFrame = 0;
	UseTextCommands = false;
	for (int i = 0; i < MAX_NUM_INTRO_RECTANGLES; i++){
		IntroRectangles[i].m_Type = 0;
		IntroRectangles[i].m_bBeforeFade = false;
		IntroRectangles[i].m_nTextureId = -1;
		IntroRectangles[i].m_sRect = CRect(0.0f, 0.0f, 0.0f, 0.0f);
		IntroRectangles[i].m_sColor = CRGBA(255, 255, 255, 255);
	}
	NumberOfIntroRectanglesThisFrame = 0;
	for (int i = 0; i < MAX_NUM_BUILDING_SWAPS; i++){
		BuildingSwapArray[i].m_pBuilding = nil;
		BuildingSwapArray[i].m_nNewModel = -1;
		BuildingSwapArray[i].m_nOldModel = -1;
	}
	for (int i = 0; i < MAX_NUM_INVISIBILITY_SETTINGS; i++)
		InvisibilitySettingArray[i] = nil;
}

void CRunningScript::RemoveScriptFromList(CRunningScript** ppScript)
{
	if (prev)
		prev->next = next;
	else
		*ppScript = next;
	if (next)
		next->prev = prev;
}

void CRunningScript::AddScriptToList(CRunningScript** ppScript)
{
	next = *ppScript;
	prev = nil;
	if (*ppScript)
		(*ppScript)->prev = this;
	*ppScript = this;
}

CRunningScript* CTheScripts::StartNewScript(uint32 ip)
{
	CRunningScript* pNew = pIdleScripts;
	assert(pNew);
	pNew->RemoveScriptFromList(&pIdleScripts);
	pNew->Init();
	pNew->SetIP(ip);
	pNew->AddScriptToList(&pActiveScripts);
	return pNew;
}

void CTheScripts::Process()
{
	if (CReplay::IsPlayingBack())
		return;
	CommandsExecuted = 0;
	ScriptsUpdated = 0;
	float timeStep = CTimer::GetTimeStepInMilliseconds();
	UpsideDownCars.UpdateTimers();
	StuckCars.Process();
	DrawScriptSpheres();
	if (FailCurrentMission)
		--FailCurrentMission;
	if (CountdownToMakePlayerUnsafe){
		if (--CountdownToMakePlayerUnsafe == 0)
			CWorld::Players[0].MakePlayerSafe(false);
	}
	if (UseTextCommands){
		for (int i = 0; i < MAX_NUM_INTRO_TEXT_LINES; i++)
			IntroTextLines[i].Reset();
		NumberOfIntroRectanglesThisFrame = 0;
		for (int i = 0; i < MAX_NUM_INTRO_RECTANGLES; i++){
			IntroRectangles[i].m_Type = 0;
			IntroRectangles[i].m_bBeforeFade = false;
		}
		NumberOfIntroRectanglesThisFrame = 0;
		if (UseTextCommands == 1)
			UseTextCommands = 0;
	}
	CRunningScript* script = pActiveScripts;
	while (script != nil){
		CRunningScript* next = script->GetNext();
		++ScriptsUpdated;
		script->UpdateTimers(timeStep);
		script->Process();
		script = next;
	}
	DbgFlag = false;
}

CRunningScript* CTheScripts::StartTestScript()
{
	return StartNewScript(0);
}

bool CTheScripts::IsPlayerOnAMission()
{
	return OnAMissionFlag && *(int32*)&ScriptSpace[OnAMissionFlag] == 1;
}

WRAPPER void CRunningScript::Process() { EAXJMP(0x439440); }
WRAPPER void CTheScripts::DrawScriptSpheres() { EAXJMP(0x44FAC0); }
WRAPPER void CTheScripts::ScriptDebugLine3D(float x1, float y1, float z1, float x2, float y2, float z2, int col, int col2) { EAXJMP(0x4534E0); }
WRAPPER void CTheScripts::CleanUpThisVehicle(CVehicle*) { EAXJMP(0x4548D0); }
WRAPPER void CTheScripts::CleanUpThisPed(CPed*) { EAXJMP(0x4547A0); }
WRAPPER void CTheScripts::CleanUpThisObject(CObject*) { EAXJMP(0x454910); }
WRAPPER void CTheScripts::ReadObjectNamesFromScript() { EAXJMP(0x454960); }
WRAPPER void CTheScripts::UpdateObjectIndices() { EAXJMP(0x454AD0); }
WRAPPER void CTheScripts::ReadMultiScriptFileOffsetsFromScript() { EAXJMP(0x454BC0); }

STARTPATCHES
InjectHook(0x437AE0, &CMissionCleanup::Init, PATCH_JUMP);
InjectHook(0x437BA0, &CMissionCleanup::AddEntityToList, PATCH_JUMP);
InjectHook(0x437BD0, &CMissionCleanup::RemoveEntityFromList, PATCH_JUMP);
InjectHook(0x437C10, &CMissionCleanup::Process, PATCH_JUMP);
InjectHook(0x437DC0, &CUpsideDownCarCheck::Init, PATCH_JUMP);
InjectHook(0x437EE0, &CUpsideDownCarCheck::UpdateTimers, PATCH_JUMP);
InjectHook(0x437F80, &CUpsideDownCarCheck::AreAnyCarsUpsideDown, PATCH_JUMP);
InjectHook(0x437FB0, &CUpsideDownCarCheck::AddCarToCheck, PATCH_JUMP);
InjectHook(0x437FE0, &CUpsideDownCarCheck::RemoveCarFromCheck, PATCH_JUMP);
InjectHook(0x438010, &CUpsideDownCarCheck::HasCarBeenUpsideDownForAWhile, PATCH_JUMP);
InjectHook(0x438050, &CStuckCarCheck::Init, PATCH_JUMP);
InjectHook(0x4380A0, &CStuckCarCheck::Process, PATCH_JUMP);
InjectHook(0x4381C0, &CStuckCarCheck::AddCarToCheck, PATCH_JUMP);
InjectHook(0x438240, &CStuckCarCheck::RemoveCarFromCheck, PATCH_JUMP);
InjectHook(0x4382A0, &CStuckCarCheck::HasCarBeenStuckForAWhile, PATCH_JUMP);
InjectHook(0x4382E0, &CRunningScript::CollectParameters, PATCH_JUMP);
InjectHook(0x438460, &CRunningScript::CollectNextParameterWithoutIncreasingPC, PATCH_JUMP);
InjectHook(0x4385A0, &CRunningScript::StoreParameters, PATCH_JUMP);
InjectHook(0x438640, &CRunningScript::GetPointerToScriptVariable, PATCH_JUMP);
InjectHook(0x438790, &CTheScripts::Init, PATCH_JUMP);
InjectHook(0x439000, &CTheScripts::StartNewScript, PATCH_JUMP);
InjectHook(0x439040, &CTheScripts::Process, PATCH_JUMP);
InjectHook(0x439400, &CTheScripts::StartTestScript, PATCH_JUMP);
InjectHook(0x439410, &CTheScripts::IsPlayerOnAMission, PATCH_JUMP);
ENDPATCHES