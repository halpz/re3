#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "Bike.h"
#include "CarCtrl.h"
#include "Cranes.h"
#include "Credits.h"
#include "CutsceneMgr.h"
#include "DMAudio.h"
#include "FileMgr.h"
#include "Fire.h"
#include "Frontend.h"
#include "Garages.h"
#include "General.h"
#ifdef MISSION_REPLAY
#include "GenericGameStorage.h"
#endif
#include "Hud.h"
#include "Messages.h"
#include "Pad.h"
#include "Particle.h"
#include "Phones.h"
#include "Population.h"
#include "Pools.h"
#include "Record.h"
#include "Remote.h"
#include "Restart.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "Streaming.h"
#include "Weather.h"
#include "Zones.h"
#include "main.h"
#include "GameLogic.h"
#include "Sprite.h"
#include "CarAI.h"
#include "Pickups.h"
#include "Fluff.h"
#include "CustomSoundTrack.h"

// LCS: file done except TODOs

#ifdef USE_DEBUG_SCRIPT_LOADER
extern const char* scriptfile;
#endif

bool CRunningScript::ThisIsAValidRandomCop(uint32 mi, int cop, int swat, int fbi, int army, int miami)
{
	switch (mi)
	{
	case MI_COP: if (cop) return true; break;
	case MI_SWAT: if (swat) return true; break;
	case MI_FBI: if (fbi) return true; break;
	case MI_ARMY: if (army) return true; break;
	default: if (mi >= MI_VICE1 && mi <= MI_VICE8 && miami) return true; break;
	}
	return false;
}

bool CRunningScript::ThisIsAValidRandomPed(uint32 pedtype, int civ, int gang, int criminal)
{
    switch (pedtype) {
    case PEDTYPE_CIVMALE:
    case PEDTYPE_CIVFEMALE:
        return civ;
    case PEDTYPE_GANG1:
    case PEDTYPE_GANG2:
    case PEDTYPE_GANG3:
    case PEDTYPE_GANG4:
    case PEDTYPE_GANG5:
    case PEDTYPE_GANG6:
    case PEDTYPE_GANG7:
    case PEDTYPE_GANG8:
    case PEDTYPE_GANG9:
        return gang;
    case PEDTYPE_CRIMINAL:
    case PEDTYPE_PROSTITUTE:
        return criminal;
    default:
        return false;
    }
}

int8 CRunningScript::ProcessCommands1000To1099(int32 command)
{
	switch (command) {
	//case COMMAND_FLASH_RADAR_BLIP:
	case COMMAND_IS_CHAR_IN_CONTROL:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPed->IsPedInControl());
		return 0;
	}
	case COMMAND_SET_GENERATE_CARS_AROUND_CAMERA:
		CollectParameters(&m_nIp, 1);
		CCarCtrl::bCarsGeneratedAroundCamera = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	case COMMAND_CLEAR_SMALL_PRINTS:
		CMessages::ClearSmallMessagesOnly();
		//CHud::ClearSmallMessages(); // TODO
		return 0;
	case COMMAND_HAS_MILITARY_CRANE_COLLECTED_ALL_CARS:
		UpdateCompareFlag(CCranes::HaveAllCarsBeenCollectedByMilitaryCrane());
		return 0;
	case COMMAND_SET_UPSIDEDOWN_CAR_NOT_DAMAGED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		//assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		// they call this for bikes again, we don't really want to destroy the structure...
#ifdef FIX_BUGS
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR)
#endif
			((CAutomobile*)pVehicle)->bNotDamagedUpsideDown = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_CAN_PLAYER_START_MISSION:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPlayerPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPlayerPed);
		UpdateCompareFlag(pPlayerPed->CanStartMission() || pPlayerPed->m_nPedState == PED_DRIVING);
		return 0;
	}
	case COMMAND_MAKE_PLAYER_SAFE_FOR_CUTSCENE:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		CPad::GetPad(GET_INTEGER_PARAM(0))->SetDisablePlayerControls(PLAYERCONTROL_CUTSCENE);
		pPlayerInfo->MakePlayerSafe(true);
		CCutsceneMgr::StartCutsceneProcessing();
		return 0;
	}
	case COMMAND_USE_TEXT_COMMANDS:
		CollectParameters(&m_nIp, 1);
		CTheScripts::UseTextCommands = (GET_INTEGER_PARAM(0) != 0) ? 2 : 1;
		return 0;
	case COMMAND_SET_THREAT_FOR_PED_TYPE:
		CollectParameters(&m_nIp, 2);
		CPedType::AddThreat(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_CLEAR_THREAT_FOR_PED_TYPE:
		CollectParameters(&m_nIp, 2);
		CPedType::RemoveThreat(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_GET_CAR_COLOURS:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->m_currentColour1);
		SET_INTEGER_PARAM(1, pVehicle->m_currentColour2);
		StoreParameters(&m_nIp, 2);
		return 0;
	}
	case COMMAND_SET_ALL_CARS_CAN_BE_DAMAGED:
		CollectParameters(&m_nIp, 1);
		CWorld::SetAllCarsCanBeDamaged(GET_INTEGER_PARAM(0) != 0);
		if (!GET_INTEGER_PARAM(0))
			CWorld::ExtinguishAllCarFiresInArea(FindPlayerCoors(), 4000.0f);
		return 0;
	case COMMAND_SET_CAR_CAN_BE_DAMAGED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		pVehicle->bCanBeDamaged = GET_INTEGER_PARAM(1) != 0;
		if (!GET_INTEGER_PARAM(1))
			pVehicle->ExtinguishCarFire();
		return 0;
	}
	//case COMMAND_MAKE_PLAYER_UNSAFE:
	/*
	case COMMAND_LOAD_COLLISION:
	{
		CollectParameters(&m_nIp, 1);
		CTimer::Stop();
		CGame::currLevel = (eLevelName)GET_INTEGER_PARAM(0);
		ISLAND_LOADING_IS(LOW)
		{
			CStreaming::RemoveUnusedBigBuildings(CGame::currLevel);
			CStreaming::RemoveUnusedBuildings(CGame::currLevel);
		}
		CCollision::SortOutCollisionAfterLoad();
		ISLAND_LOADING_ISNT(HIGH)
		{
			CStreaming::RequestIslands(CGame::currLevel);
			CStreaming::LoadAllRequestedModels(true);
		}
		CTimer::Update();
		return 0;
	}
	case COMMAND_GET_BODY_CAST_HEALTH:
	//	SET_INTEGER_PARAM(0, CObject::nBodyCastHealth);
	//	StoreParameters(&m_nIp, 1);
		return 0;
	*/
	case COMMAND_SET_CHARS_CHATTING:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed1 = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pPed2 = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pPed1 && pPed2);
		pPed1->SetChat(pPed2, GET_INTEGER_PARAM(2));
		pPed2->SetChat(pPed1, GET_INTEGER_PARAM(2));
		return 0;
	}
	//case COMMAND_MAKE_PLAYER_SAFE:
	/*
	case COMMAND_SET_CAR_STAYS_IN_CURRENT_LEVEL:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(1))
			pVehicle->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pVehicle->GetPosition());
		else
			pVehicle->m_nZoneLevel = LEVEL_GENERIC;
		return 0;
	}
	case COMMAND_SET_CHAR_STAYS_IN_CURRENT_LEVEL:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1))
			pPed->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pPed->GetPosition());
		else
			pPed->m_nZoneLevel = LEVEL_GENERIC;
		return 0;
	}
	*/
	case COMMAND_SET_DRUNK_INPUT_DELAY:
	{
		CollectParameters(&m_nIp, 2);
		assert(GET_INTEGER_PARAM(1) < CPad::DRUNK_STEERING_BUFFER_SIZE);
		CPad::GetPad(GET_INTEGER_PARAM(0))->SetDrunkInputDelay(GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_SET_CHAR_MONEY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_nPedMoney = GET_INTEGER_PARAM(1);
		pPed->bMoneyHasBeenGivenByScript = true;
		return 0;
	}
	//case COMMAND_INCREASE_CHAR_MONEY:
	case COMMAND_GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVector result = Multiply3x3(pObject->GetMatrix(), GET_VECTOR_PARAM(1)) + pObject->GetPosition();
		SET_VECTOR_PARAM(0, result);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_REGISTER_LIFE_SAVED:
		CStats::AnotherLifeSavedWithAmbulance();
		return 0;
	case COMMAND_REGISTER_CRIMINAL_CAUGHT:
		CStats::AnotherCriminalCaught();
		return 0;
	case COMMAND_REGISTER_AMBULANCE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelAmbulanceMission(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_FIRE_EXTINGUISHED:
		CStats::AnotherFireExtinguished();
		return 0;
	case COMMAND_TURN_PHONE_ON:
		CollectParameters(&m_nIp, 1);
		gPhoneInfo.m_aPhones[GET_INTEGER_PARAM(0)].m_nState = PHONE_STATE_9;
		return 0;
	/*
	case COMMAND_REGISTER_LONGEST_DODO_FLIGHT:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLongestFlightInDodo(GET_INTEGER_PARAM(0));
		return 0;
	*/
	case COMMAND_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVector result = Multiply3x3(pVehicle->GetMatrix(), GET_VECTOR_PARAM(1)) + pVehicle->GetPosition();
		SET_VECTOR_PARAM(0, result);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_TOTAL_NUMBER_OF_KILL_FRENZIES:
		CollectParameters(&m_nIp, 1);
		CStats::SetTotalNumberKillFrenzies(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_BLOW_UP_RC_BUGGY:
		CWorld::Players[CWorld::PlayerInFocus].BlowUpRCBuggy(true);
		return 0;
	/*
	case COMMAND_REMOVE_CAR_FROM_CHASE:
		CollectParameters(&m_nIp, 1);
		CRecordDataForChase::RemoveCarFromChase(GET_INTEGER_PARAM(0));
		return 0;
	*/
	case COMMAND_IS_FRENCH_GAME:
		UpdateCompareFlag(CGame::frenchGame);
		return 0;
	case COMMAND_IS_GERMAN_GAME:
		UpdateCompareFlag(CGame::germanGame);
		return 0;
	case COMMAND_CLEAR_MISSION_AUDIO:
		CollectParameters(&m_nIp, 1);
		DMAudio.ClearMissionAudio(GET_INTEGER_PARAM(0) - 1);
		return 0;
	/*
	case COMMAND_SET_FADE_IN_AFTER_NEXT_ARREST:
		CollectParameters(&m_nIp, 1);
		CRestart::bFadeInAfterNextArrest = !!GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_FADE_IN_AFTER_NEXT_DEATH:
		CollectParameters(&m_nIp, 1);
		CRestart::bFadeInAfterNextDeath = !!GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_GANG_PED_MODEL_PREFERENCE:
		CollectParameters(&m_nIp, 2);
		CGangs::SetGangPedModelOverride(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	*/
	case COMMAND_SET_CHAR_USE_PEDNODE_SEEK:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1))
			pPed->m_pNextPathNode = nil;
		pPed->bUsePedNodeSeek = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	/*
	case COMMAND_SWITCH_VEHICLE_WEAPONS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bGunSwitchedOff = !GET_INTEGER_PARAM(1);
		return 0;
	}
	*/
	case COMMAND_SET_GET_OUT_OF_JAIL_FREE:
		CollectParameters(&m_nIp, 2);
		CWorld::Players[GET_INTEGER_PARAM(0)].m_bGetOutOfJailFree = !!GET_INTEGER_PARAM(1);
		return 0;
	case COMMAND_SET_FREE_HEALTH_CARE:
		CollectParameters(&m_nIp, 2);
		CWorld::Players[GET_INTEGER_PARAM(0)].m_bGetOutOfHospitalFree = !!GET_INTEGER_PARAM(1);
		return 0;
	/*
	case COMMAND_IS_CAR_DOOR_CLOSED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(!pVehicle->IsDoorMissing((eDoors)GET_INTEGER_PARAM(1)) && pVehicle->IsDoorClosed((eDoors)GET_INTEGER_PARAM(1)));
		return 0;
	}
	*/
	case COMMAND_LOAD_AND_LAUNCH_MISSION:
		return 0;
	case COMMAND_LOAD_AND_LAUNCH_MISSION_INTERNAL:
	{
#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
		uint32 oldIp = m_nIp;
#endif
		CollectParameters(&m_nIp, 1);

		if (CTheScripts::NumberOfExclusiveMissionScripts > 0) {
			if (GET_INTEGER_PARAM(0) < UINT16_MAX - 1)
				return 0;
			SET_INTEGER_PARAM(0, UINT16_MAX - GET_INTEGER_PARAM(0));
		}
#ifdef MISSION_REPLAY
		missionRetryScriptIndex = GET_INTEGER_PARAM(0);
#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
		if (CTheScripts::MissionSupportsMissionReplay(missionRetryScriptIndex)){
			if (!AlreadySavedGame) {
				m_nIp = oldIp - 2;
				SaveGameForPause(SAVE_TYPE_QUICKSAVE_FOR_SCRIPT);
				AlreadySavedGame = true;
				return 0;
			}
			else {
				AlreadySavedGame = false;
			}
		}
#endif
#endif
		CTimer::Suspend();
		int offset = CTheScripts::MultiScriptArray[GET_INTEGER_PARAM(0)] + 8;
		int size = CTheScripts::MultiScriptArray[GET_INTEGER_PARAM(0) + 1] - CTheScripts::MultiScriptArray[GET_INTEGER_PARAM(0)];
		if (size <= 0)
			size = CTheScripts::LargestMissionScriptSize;
		CFileMgr::Seek(gScriptsFile, offset, 0);
		CFileMgr::Read(gScriptsFile, (const char*)&CTheScripts::ScriptSpace[CTheScripts::MainScriptSize], size);
		CRunningScript* pMissionScript = CTheScripts::StartNewScript(CTheScripts::MainScriptSize);
		CTimer::Resume();
		pMissionScript->m_bIsMissionScript = true;
		pMissionScript->m_bMissionFlag = true;
		CTheScripts::bAlreadyRunningAMissionScript = true;
		memset(&CTheScripts::ScriptSpace[CTheScripts::NumTrueGlobals * 4 + 8], 0, CTheScripts::MostGlobals * 4);
		pMissionScript->Process();
		return 0;
	}
	case COMMAND_SET_OBJECT_DRAW_LAST:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bDrawLast = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_GET_AMMO_IN_PLAYER_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		SET_INTEGER_PARAM(0, 0);
		for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
			if (pPed->GetWeapon(i).m_eWeaponType == (eWeaponType)GET_INTEGER_PARAM(1))
				SET_INTEGER_PARAM(0, pPed->GetWeapon(i).m_nAmmoTotal);
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	/*
	case COMMAND_GET_AMMO_IN_CHAR_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CWeapon* pWeaponSlot = &pPed->m_weapons[GET_INTEGER_PARAM(1)];
		if (pWeaponSlot->m_eWeaponType == (eWeaponType)GET_INTEGER_PARAM(1))
			SET_INTEGER_PARAM(0, pWeaponSlot->m_nAmmoTotal);
		else
			SET_INTEGER_PARAM(0, 0);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_REGISTER_KILL_FRENZY_PASSED:
		CStats::AnotherKillFrenzyPassed();
		return 0;
	*/
	case COMMAND_SET_CHAR_SAY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		switch (GET_INTEGER_PARAM(1)) {
		case 15:
			pPed->Say(0x93); // TODO
			break;
		default:
			break;
		}
		return 0;
	}
	case COMMAND_SET_NEAR_CLIP:
		CollectParameters(&m_nIp, 1);
		TheCamera.SetNearClipScript(GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_SET_RADIO_CHANNEL:
		CollectParameters(&m_nIp, 2);
		if (!cCustomSoundTrack::Instance()->IsPlaying())
			DMAudio.SetRadioChannel(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	/*
	case COMMAND_OVERRIDE_HOSPITAL_LEVEL:
		CollectParameters(&m_nIp, 1);
		CRestart::OverrideHospitalLevel = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_OVERRIDE_POLICE_STATION_LEVEL:
		CollectParameters(&m_nIp, 1);
		CRestart::OverridePoliceStationLevel = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_FORCE_RAIN:
		CollectParameters(&m_nIp, 1);
		CWeather::bScriptsForceRain = !!GET_INTEGER_PARAM(0);
		return 0;
	*/
	case COMMAND_DOES_GARAGE_CONTAIN_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		UpdateCompareFlag(CGarages::IsThisCarWithinGarageArea(GET_INTEGER_PARAM(0), pVehicle));
		return 0;
	}
	case COMMAND_SET_CAR_TRACTION:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		float fTraction = GET_FLOAT_PARAM(1);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR || pVehicle->m_vehType == VEHICLE_TYPE_BIKE);
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR)
			((CAutomobile*)pVehicle)->m_fTraction = fTraction;
		else
			((CBike*)pVehicle)->m_fTraction = fTraction;
		return 0;
	}
	case COMMAND_ARE_MEASUREMENTS_IN_METRES:
#ifdef USE_MEASUREMENTS_IN_METERS
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_CONVERT_METRES_TO_FEET:
	{
		CollectParameters(&m_nIp, 1);
		float fMeterValue = GET_FLOAT_PARAM(0);
		float fFeetValue = fMeterValue / METERS_IN_FOOT;
		SET_FLOAT_PARAM(0, fFeetValue);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_MARK_ROADS_BETWEEN_LEVELS:
	{
		CollectParameters(&m_nIp, 6);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		float supZ = GET_FLOAT_PARAM(5);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(0);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(1);
		}
		if (infZ > supZ) {
			infZ = GET_FLOAT_PARAM(5);
			supZ = GET_FLOAT_PARAM(2);
		}
		ThePaths.MarkRoadsBetweenLevelsInArea(infX, supX, infY, supY, infZ, supZ);
		return 0;
	}
	case COMMAND_MARK_PED_ROADS_BETWEEN_LEVELS:
	{
		CollectParameters(&m_nIp, 6);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		float supZ = GET_FLOAT_PARAM(5);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(0);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(1);
		}
		if (infZ > supZ) {
			infZ = GET_FLOAT_PARAM(5);
			supZ = GET_FLOAT_PARAM(2);
		}
		ThePaths.PedMarkRoadsBetweenLevelsInArea(infX, supX, infY, supY, infZ, supZ);
		return 0;
	}
	case COMMAND_SET_CAR_AVOID_LEVEL_TRANSITIONS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_bStayInCurrentLevel = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	/*
	case COMMAND_SET_CHAR_AVOID_LEVEL_TRANSITIONS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pPed);
		// not implemented
		return 0;
	}
	case COMMAND_IS_THREAT_FOR_PED_TYPE:
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(CPedType::IsThreat(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)));
		return 0;
	*/
	case COMMAND_CLEAR_AREA_OF_CHARS:
	{
		CollectParameters(&m_nIp, 6);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		float supZ = GET_FLOAT_PARAM(5);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(0);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(1);
		}
		if (infZ > supZ) {
			infZ = GET_FLOAT_PARAM(5);
			supZ = GET_FLOAT_PARAM(2);
		}
		CWorld::ClearPedsFromArea(infX, infY, infZ, supX, supY, supZ);
		return 0;
	}
	case COMMAND_SET_TOTAL_NUMBER_OF_MISSIONS:
		CollectParameters(&m_nIp, 1);
		CStats::SetTotalNumberMissions(CGame::germanGame ? GET_INTEGER_PARAM(0) - 2 : GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CONVERT_METRES_TO_FEET_INT:
		CollectParameters(&m_nIp, 1);
		GET_INTEGER_PARAM(0) *= FEET_IN_METER;
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_REGISTER_FASTEST_TIME:
		CollectParameters(&m_nIp, 2);
		CStats::RegisterFastestTime(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_REGISTER_HIGHEST_SCORE:
		CollectParameters(&m_nIp, 2);
		CStats::RegisterHighestScore(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pPed);
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(2) < 0)
			pPed->WarpPedIntoCarAsPassenger(pVehicle, GET_INTEGER_PARAM(2));
		else {
			script_assert(GET_INTEGER_PARAM(2) >= 0 && GET_INTEGER_PARAM(2) < ARRAY_SIZE(pVehicle->pPassengers));
			pPed->WarpPedIntoCarAsPassenger(pVehicle, GET_INTEGER_PARAM(2));
		}
		return 0;

	}
	case COMMAND_IS_CAR_PASSENGER_SEAT_FREE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(GET_INTEGER_PARAM(1) < pVehicle->m_nNumMaxPassengers && pVehicle->pPassengers[GET_INTEGER_PARAM(1)] == nil);
		return 0;
	}
	case COMMAND_GET_CHAR_IN_CAR_PASSENGER_SEAT:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(GET_INTEGER_PARAM(1) >= 0 && GET_INTEGER_PARAM(1) < ARRAY_SIZE(pVehicle->pPassengers));
		CPed* pPassenger = pVehicle->pPassengers[GET_INTEGER_PARAM(1)];
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pPassenger));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_IS_CHRIS_CRIMINAL:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bChrisCriminal = !!GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_START_CREDITS:
		CollectParameters(&m_nIp, 1);
		CCredits::Start(); // TODO: CCredits::Start(GET_INTEGER_PARAM(0))
		return 0;
	case COMMAND_STOP_CREDITS:
		CCredits::Stop();
		return 0;
	case COMMAND_ARE_CREDITS_FINISHED:
		UpdateCompareFlag(CCredits::AreCreditsDone());
		return 0;
	case COMMAND_CREATE_SINGLE_PARTICLE:
		CollectParameters(&m_nIp, 8);
		CParticle::AddParticle((tParticleType)GET_INTEGER_PARAM(0), GET_VECTOR_PARAM(1),
			GET_VECTOR_PARAM(4), nil, GET_FLOAT_PARAM(7), 0, 0, 0, 0);
		return 0;
	/*
	case COMMAND_SET_CHAR_IGNORE_LEVEL_TRANSITIONS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1))
			pPed->m_nZoneLevel = LEVEL_IGNORE;
		else
			pPed->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pPed->GetPosition());
		return 0;
	}
	case COMMAND_GET_CHASE_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CRecordDataForChase::TurnChaseCarIntoScriptCar(GET_INTEGER_PARAM(0));
		SET_INTEGER_PARAM(0, CPools::GetVehiclePool()->GetIndex(pVehicle));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_CAR);
		return 0;
	}
	case COMMAND_START_BOAT_FOAM_ANIMATION:
		CSpecialParticleStuff::StartBoatFoamAnimation();
		return 0;
	case COMMAND_UPDATE_BOAT_FOAM_ANIMATION:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CSpecialParticleStuff::UpdateBoatFoamAnimation(&pObject->GetMatrix());
		return 0;
	}
	*/
	case COMMAND_SET_MUSIC_DOES_FADE:
		CollectParameters(&m_nIp, 1);
		TheCamera.m_bIgnoreFadingStuffForMusic = (GET_INTEGER_PARAM(0) == 0);
		return 0;
	/*
	case COMMAND_SET_INTRO_IS_PLAYING:
		CollectParameters(&m_nIp, 1);
		if (GET_INTEGER_PARAM(0)) {
			CGame::playingIntro = true;
			CStreaming::RemoveCurrentZonesModels();
		} else {
			CGame::playingIntro = false;
			DMAudio.ChangeMusicMode(MUSICMODE_GAME);
			int mi;
			CModelInfo::GetModelInfo("bridgefukb", &mi);
			CStreaming::RequestModel(mi, STREAMFLAGS_DEPENDENCY);
			CStreaming::LoadAllRequestedModels(false);
		}
		return 0;
	case COMMAND_SET_PLAYER_HOOKER:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		if (GET_INTEGER_PARAM(1) < 0) {
			pPlayerInfo->m_pHooker = nil;
			pPlayerInfo->m_nNextSexFrequencyUpdateTime = 0;
			pPlayerInfo->m_nNextSexMoneyUpdateTime = 0;
		} else {
			CPed* pHooker = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
			script_assert(pHooker);
			pPlayerInfo->m_pHooker = (CCivilianPed*)pHooker;
			pPlayerInfo->m_nSexFrequency = 1000;
			pPlayerInfo->m_nNextSexFrequencyUpdateTime = CTimer::GetTimeInMilliseconds() + 1000;
			pPlayerInfo->m_nNextSexMoneyUpdateTime = CTimer::GetTimeInMilliseconds() + 3000;
		}
		return 0;
	}
	*/
	case COMMAND_PLAY_END_OF_GAME_TUNE:
		DMAudio.ChangeMusicMode(MUSICMODE_FRONTEND);
		DMAudio.PlayFrontEndTrack(STREAMED_SOUND_CUTSCENE_FINALE, 1); // third parameter is 1
		return 0;
	case COMMAND_STOP_END_OF_GAME_TUNE:
		DMAudio.StopCutSceneMusic();
		DMAudio.ChangeMusicMode(MUSICMODE_GAME);
		return 0;
	case COMMAND_GET_CAR_MODEL:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->GetModelIndex());
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_PLAYER_SITTING_IN_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		UpdateCompareFlag(pPed->GetPedState() == PED_DRIVING && pPed->m_objective != OBJECTIVE_LEAVE_CAR && pPed->m_pMyVehicle == pVehicle);
		return 0;
	}
	case COMMAND_IS_PLAYER_SITTING_IN_ANY_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->GetPedState() == PED_DRIVING && pPed->m_objective != OBJECTIVE_LEAVE_CAR);
		return 0;
	}
	/*
	case COMMAND_SET_SCRIPT_FIRE_AUDIO:
		CollectParameters(&m_nIp, 2);
		gFireManager.SetScriptFireAudio(GET_INTEGER_PARAM(0), !!GET_INTEGER_PARAM(1));
		return 0;
	*/
	case COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED:
		UpdateCompareFlag(CVehicle::bAllDodosCheat || CVehicle::bCheat3 || CVehicle::bHoverCheat || CVehicle::bCheat8 || CVehicle::bCheat9);
		return 0;
	case COMMAND_SET_CHAR_SUFFERS_CRITICAL_HITS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bNoCriticalHits = (GET_INTEGER_PARAM(1) == 0);
		return 0;
	}
	/*
	case COMMAND_IS_PLAYER_LIFTING_A_PHONE:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->GetPedState() == PED_MAKE_CALL);
		return 0;
	}
	*/
	case COMMAND_IS_CHAR_SITTING_IN_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		UpdateCompareFlag(pPed->GetPedState() == PED_DRIVING && pPed->m_objective != OBJECTIVE_LEAVE_CAR && pPed->m_pMyVehicle == pVehicle);
		return 0;
	}
	case COMMAND_IS_CHAR_SITTING_IN_ANY_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->GetPedState() == PED_DRIVING && pPed->m_objective != OBJECTIVE_LEAVE_CAR);
		return 0;
	}
	case COMMAND_IS_PLAYER_ON_FOOT:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(!pPed->bInVehicle && pPed->m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER &&
			pPed->m_objective != OBJECTIVE_ENTER_CAR_AS_DRIVER);
		return 0;
	}
	case COMMAND_IS_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(!pPed->bInVehicle && pPed->m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER &&
			pPed->m_objective != OBJECTIVE_ENTER_CAR_AS_DRIVER);
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands1100To1199(int32 command)
{
	char tmp[48];
	switch (command) {
	/*
	case COMMAND_LOAD_COLLISION_WITH_SCREEN:
		CollectParameters(&m_nIp, 1);
		CTimer::Stop();
		CGame::currLevel = (eLevelName)GET_INTEGER_PARAM(0);
		if (CGame::currLevel != CCollision::ms_collisionInMemory) {
			ISLAND_LOADING_IS(LOW)
			{
				DMAudio.SetEffectsFadeVol(0);
				CPad::StopPadsShaking();
				CCollision::LoadCollisionScreen(CGame::currLevel);
				DMAudio.Service();
			}
			CPopulation::DealWithZoneChange(CCollision::ms_collisionInMemory, CGame::currLevel, false);

			ISLAND_LOADING_IS(LOW)
			{
				CStreaming::RemoveUnusedBigBuildings(CGame::currLevel);
				CStreaming::RemoveUnusedBuildings(CGame::currLevel);
			}
			CCollision::SortOutCollisionAfterLoad();

			ISLAND_LOADING_ISNT(HIGH)
				CStreaming::RequestIslands(CGame::currLevel);

			ISLAND_LOADING_IS(LOW)
				CStreaming::RequestBigBuildings(CGame::currLevel);

			ISLAND_LOADING_ISNT(HIGH)
				CStreaming::LoadAllRequestedModels(true);

			ISLAND_LOADING_IS(LOW)
				DMAudio.SetEffectsFadeVol(127);
		}
		CTimer::Update();
		return 0;
	*/
	case COMMAND_LOAD_SPLASH_SCREEN:
		CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			tmp[i] = tolower(tmp[i]);
		m_nIp += 8;
		LoadSplash(tmp);
		return 0;
	/*
	case COMMAND_SET_CAR_IGNORE_LEVEL_TRANSITIONS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(1))
			pVehicle->m_nZoneLevel = LEVEL_IGNORE;
		else
			pVehicle->m_nZoneLevel = CTheZones::GetLevelFromPosition(&pVehicle->GetPosition());
		return 0;
	}
	case COMMAND_MAKE_CRAIGS_CAR_A_BIT_STRONGER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		CAutomobile* pCar = (CAutomobile*)pVehicle;
		pCar->bMoreResistantToDamage = GET_INTEGER_PARAM(1);
		return 0;
	}
	*/
	case COMMAND_SET_JAMES_CAR_ON_PATH_TO_PLAYER:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CCarCtrl::JoinCarWithRoadSystemGotoCoors(pVehicle, FindPlayerCoors(), false);
		return 0;
	}
	case COMMAND_LOAD_END_OF_GAME_TUNE:
		return 0;
	case COMMAND_ENABLE_PLAYER_CONTROL_CAMERA:
		CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_CAMERA);
		return 0;
	case COMMAND_SET_OBJECT_ROTATION:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CWorld::Remove(pObject);
		pObject->SetOrientation(
			DEGTORAD(GET_FLOAT_PARAM(1)),
			DEGTORAD(GET_FLOAT_PARAM(2)),
			DEGTORAD(GET_FLOAT_PARAM(3)));
		pObject->GetMatrix().UpdateRW();
		pObject->UpdateRwFrame();
		CWorld::Add(pObject);
		return 0;
	}
	case COMMAND_GET_DEBUG_CAMERA_COORDINATES:
		SET_VECTOR_PARAM(0, TheCamera.Cams[2].Source);
		StoreParameters(&m_nIp, 3);
		return 0;
	/*
	case COMMAND_GET_DEBUG_CAMERA_FRONT_VECTOR:
		SET_VECTOR_PARAM(0, TheCamera.Cams[2].Front);
		StoreParameters(&m_nIp, 3);
		return 0;
	case COMMAND_IS_PLAYER_TARGETTING_ANY_CHAR:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		CEntity* pTarget = pPed->m_pPointGunAt;
		UpdateCompareFlag(pTarget && pTarget->IsPed());
		return 0;
	}
	*/
	case COMMAND_IS_PLAYER_TARGETTING_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		CPed* pTestedPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTestedPed);
		CEntity* pTarget = pPed->m_pPointGunAt;
		bool bTargetting = pTarget && pTarget->IsPed() && pTarget == pTestedPed;
#ifdef GTA_PC
		static int nCounter = 0;
		nCounter = Max(0, nCounter - 1);
		if (!pPed->GetWeapon()->IsTypeMelee() && !bTargetting) {
			if ((pTestedPed->GetPosition() - TheCamera.GetPosition()).Magnitude() < 10.0f) {
				CVector vTestedPos(pTestedPed->GetPosition().x, pTestedPed->GetPosition().y, pTestedPed->GetPosition().z + 0.4);
				CVector vScreenPos;
				float w, h;
				if (CSprite::CalcScreenCoors(vTestedPos, &vScreenPos, &w, &h, false)) {
					CVector2D vCrosshairPosition(CCamera::m_f3rdPersonCHairMultX * RsGlobal.maximumWidth, CCamera::m_f3rdPersonCHairMultY * RsGlobal.maximumHeight);
					float fScreenDistance = ((CVector2D)vScreenPos - vCrosshairPosition).Magnitude();
					if (SCREEN_STRETCH_X(0.45f) > fScreenDistance / w) {
						CColPoint point;
						CEntity* entity;
						if (!CWorld::ProcessLineOfSight(TheCamera.GetPosition() + 2.0f * TheCamera.GetForward(),
							vTestedPos, point, entity, true, true, true, true, true, false) ||
							entity == pTestedPed) {
							nCounter += 2;
							if (nCounter > 20) {
								bTargetting = true;
								nCounter = 20;
							}
						}
					}
				}
			}
		}
#endif
		UpdateCompareFlag(bTargetting);
		return 0;
	}
	case COMMAND_IS_PLAYER_TARGETTING_OBJECT:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		CObject* pTestedObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTestedObject);
		CEntity* pTarget = pPed->m_pPointGunAt;
		bool bTargetting = pTarget && pTarget->IsObject() && pTarget == pTestedObject;
#ifdef GTA_PC // we will never know if section is real
		static int nCounter = 0;
		nCounter = Max(0, nCounter - 1);
		if (!pPed->GetWeapon()->IsTypeMelee() && !bTargetting) {
			if ((pTestedObject->GetPosition() - TheCamera.GetPosition()).Magnitude() < 10.0f) {
				CVector vTestedPos(pTestedObject->GetPosition().x, pTestedObject->GetPosition().y, pTestedObject->GetPosition().z);
				CVector vScreenPos;
				float w, h;
				if (CSprite::CalcScreenCoors(vTestedPos, &vScreenPos, &w, &h, false)) {
					CVector2D vCrosshairPosition(CCamera::m_f3rdPersonCHairMultX * RsGlobal.maximumWidth, CCamera::m_f3rdPersonCHairMultY * RsGlobal.maximumHeight);
					float fScreenDistance = ((CVector2D)vScreenPos - vCrosshairPosition).Magnitude();
					if (SCREEN_STRETCH_X(0.45f) > fScreenDistance / w) {
						CColPoint point;
						CEntity* entity;
						if (!CWorld::ProcessLineOfSight(TheCamera.GetPosition() + 2.0f * TheCamera.GetForward(),
							vTestedPos, point, entity, true, true, true, true, true, false) ||
							entity == pTestedObject) {
							nCounter += 2;
							if (nCounter > 20) {
								bTargetting = true;
								nCounter = 20;
							}
						}
					}
				}
			}
		}
		UpdateCompareFlag(bTargetting);
#endif
		return 0;
	}
	case COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME:
	{
		CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			tmp[i] = tolower(tmp[i]);
		m_nIp += 8;
		CRunningScript* pScript = CTheScripts::pActiveScripts;
		while (pScript) {
			CRunningScript* pNext = pScript->next;
			if (strcmp(pScript->m_abScriptName, tmp) == 0) {
				pScript->RemoveScriptFromList(&CTheScripts::pActiveScripts);
				pScript->AddScriptToList(&CTheScripts::pIdleScripts);
			}
			pScript = pNext;
		}
		return 0;
	}
	case COMMAND_DISPLAY_TEXT_WITH_NUMBER:
	{
		CollectParameters(&m_nIp, 2);
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtX = GET_FLOAT_PARAM(0);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtY = GET_FLOAT_PARAM(1);
		CollectParameters(&m_nIp, 1);
		CMessages::InsertNumberInString(text, GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1,
			CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame++].m_Text);
		return 0;
	}
	case COMMAND_DISPLAY_TEXT_WITH_2_NUMBERS:
	{
		CollectParameters(&m_nIp, 2);
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtX = GET_FLOAT_PARAM(0);
		CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame].m_fAtY = GET_FLOAT_PARAM(1);
		CollectParameters(&m_nIp, 2);
		CMessages::InsertNumberInString(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1,
			CTheScripts::IntroTextLines[CTheScripts::NumberOfIntroTextLinesThisFrame++].m_Text);
		return 0;
	}
	case COMMAND_FAIL_CURRENT_MISSION:
		CTheScripts::FailCurrentMission = 2;
#ifdef MISSION_REPLAY
		MissionSkipLevel = 0;
#endif
		return 0;
	case COMMAND_GET_CLOSEST_OBJECT_OF_TYPE:
	{
		return 0;
/*
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float range = GET_FLOAT_PARAM(3);
		int mi = GET_INTEGER_PARAM(4) < 0 ? CTheScripts::UsedObjectArray[-GET_INTEGER_PARAM(4)].index : GET_INTEGER_PARAM(4);
		int16 total;
		CEntity* apEntities[16];
		CWorld::FindObjectsOfTypeInRange(mi, pos, range, true, &total, 16, apEntities, false, false, false, true, true);
		CEntity* pClosestEntity = nil;
		float min_dist = 2.0f * range;
		for (int i = 0; i < total; i++) {
			float dist = (apEntities[i]->GetPosition() - pos).Magnitude();
			if (dist < min_dist) {
				min_dist = dist;
				pClosestEntity = apEntities[i];
			}
		}
		if (pClosestEntity && pClosestEntity->IsDummy()) {
			CPopulation::ConvertToRealObject((CDummyObject*)pClosestEntity);
			CWorld::FindObjectsOfTypeInRange(mi, pos, range, true, &total, 16, apEntities, false, false, false, true, true);
			pClosestEntity = nil;
			float min_dist = 2.0f * range;
			for (int i = 0; i < total; i++) {
				float dist = (apEntities[i]->GetPosition() - pos).Magnitude();
				if (dist < min_dist) {
					min_dist = dist;
					pClosestEntity = apEntities[i];
				}
			}
			if (pClosestEntity->IsDummy())
				pClosestEntity = nil;
		}
		if (pClosestEntity) {
			script_assert(pClosestEntity->IsObject());
			CObject* pObject = (CObject*)pClosestEntity;
			pObject->ObjectCreatedBy = MISSION_OBJECT;
			SET_INTEGER_PARAM(0, CPools::GetObjectPool()->GetIndex(pObject));
		} else {
			SET_INTEGER_PARAM(0, -1);
		}
		StoreParameters(&m_nIp, 1);
		return 0;
*/
	}
	/*
	case COMMAND_PLACE_OBJECT_RELATIVE_TO_OBJECT:
	{
		CollectParameters(&m_nIp, 5);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CObject* pTarget = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTarget);
		CVector offset = GET_VECTOR_PARAM(2);
		CPhysical::PlacePhysicalRelativeToOtherPhysical(pTarget, pObject, offset);
		return 0;
	}
	*/
	case COMMAND_SET_ALL_OCCUPANTS_OF_CAR_LEAVE_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CCarAI::TellOccupantsToLeaveCar(pVehicle);
		return 0;
	}
	case COMMAND_SET_INTERPOLATION_PARAMETERS:
		CollectParameters(&m_nIp, 2);
		TheCamera.SetParametersForScriptInterpolation(GET_FLOAT_PARAM(0), 100.0f - GET_FLOAT_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	/*
	case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING_TOWARDS_POINT:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float destX = GET_FLOAT_PARAM(3);
		float destY = GET_FLOAT_PARAM(4);
		int32 nid = ThePaths.FindNodeClosestToCoors(pos, 0, 999999.9f, true, true);
		CPathNode* pNode = &ThePaths.m_pathNodes[nid];
		SET_VECTOR_PARAM(0, pNode->GetPosition());
		SET_FLOAT_PARAM(3, ThePaths.FindNodeOrientationForCarPlacementFacingDestination(nid, destX, destY, true));
		StoreParameters(&m_nIp, 4);
		return 0;
	}
	case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING_AWAY_POINT:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float destX = GET_FLOAT_PARAM(3);
		float destY = GET_FLOAT_PARAM(4);
		int32 nid = ThePaths.FindNodeClosestToCoors(pos, 0, 999999.9f, true, true);
		CPathNode* pNode = &ThePaths.m_pathNodes[nid];
		SET_VECTOR_PARAM(0, pNode->GetPosition());
		SET_FLOAT_PARAM(3, ThePaths.FindNodeOrientationForCarPlacementFacingDestination(nid, destX, destY, false));
		StoreParameters(&m_nIp, 4);
		return 0;
	}
	*/
	case COMMAND_GET_DEBUG_CAMERA_POINT_AT:
		SET_VECTOR_PARAM(0, TheCamera.Cams[2].Source + TheCamera.Cams[2].Front);
		StoreParameters(&m_nIp, 3);
		return 0;
	case COMMAND_ATTACH_CHAR_TO_CAR:
	{
		CollectParameters(&m_nIp, 8);
		CPed *pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVehicle *pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->AttachPedToEntity(pVehicle, GET_VECTOR_PARAM(2), GET_INTEGER_PARAM(5), DEGTORAD(GET_FLOAT_PARAM(6)), (eWeaponType)GET_INTEGER_PARAM(7));
		return 0;
	}
	case COMMAND_DETACH_CHAR_FROM_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CPed *pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed && pPed->m_attachedTo) {
			pPed->DettachPedFromEntity();
			pPed->bIsAimingGun = false;
		}
		return 0;
	}
	case COMMAND_SET_CAR_CHANGE_LANE: // for some reason changed in SA
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_bStayInFastLane = !GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_CLEAR_CHAR_LAST_WEAPON_DAMAGE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed)
			pPed->m_lastWepDam = -1;
		else
			debug("CLEAR_CHAR_LAST_WEAPON_DAMAGE - Character doesn't exist\n");
		return 0;
	}
	case COMMAND_CLEAR_CAR_LAST_WEAPON_DAMAGE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (pVehicle)
			pVehicle->m_nLastWeaponDamage = -1;
		else
			debug("CLEAR_CAR_LAST_WEAPON_DAMAGE - Vehicle doesn't exist\n");
		return 0;
	}
	case COMMAND_GET_RANDOM_COP_IN_AREA:
	{
		CollectParameters(&m_nIp, 9);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		float x1 = GET_FLOAT_PARAM(0);
		float y1 = GET_FLOAT_PARAM(1);
		float x2 = GET_FLOAT_PARAM(2);
		float y2 = GET_FLOAT_PARAM(3);
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (CTheScripts::LastRandomPedId == CPools::GetPedPool()->GetIndex(pPed))
				continue;
			if (pPed->m_nPedType != PEDTYPE_COP)
				continue;
			if (!ThisIsAValidRandomCop(pPed->GetModelIndex(), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(8)))
				continue;
			if (pPed->CharCreatedBy != RANDOM_CHAR)
				continue;
			if (!pPed->IsPedInControl() && pPed->GetPedState() != PED_DRIVING && pPed->GetPedState() != PED_ABSEIL)
				continue;
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->bIsLeader || pPed->m_leader)
				continue;
			if (!pPed->IsWithinArea(x1, y1, x2, y2))
				continue;
			if (pos.z - COP_PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + COP_PED_FIND_Z_OFFSET < pPed->GetPosition().z)
				continue;
			ped_handle = CPools::GetPedPool()->GetIndex(pPed);
			CTheScripts::LastRandomPedId = ped_handle;
			pPed->CharCreatedBy = MISSION_CHAR;
			pPed->bRespondsToThreats = false;
			++CPopulation::ms_nTotalMissionPeds;
			if (m_bIsMissionScript)
				CTheScripts::MissionCleanUp.AddEntityToList(ped_handle, CLEANUP_CHAR);
		}
		SET_INTEGER_PARAM(0, ped_handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	/*
	case COMMAND_GET_RANDOM_COP_IN_ZONE:
	{
		char zone[KEY_LENGTH_IN_SCRIPT];
		strncpy(zone, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		int nZone = CTheZones::FindZoneByLabelAndReturnIndex(zone, ZONE_DEFAULT);
		if (nZone != -1)
			m_nIp += KEY_LENGTH_IN_SCRIPT;
		CZone* pZone = CTheZones::GetNavigationZone(nZone);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (CTheScripts::LastRandomPedId == CPools::GetPedPool()->GetIndex(pPed))
				continue;
			if (pPed->m_nPedType != PEDTYPE_COP)
				continue;
			if (pPed->CharCreatedBy != RANDOM_CHAR)
				continue;
			if (!pPed->IsPedInControl() && pPed->GetPedState() != PED_DRIVING)
				continue;
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->bIsLeader || pPed->m_leader)
				continue;
			if (!CTheZones::PointLiesWithinZone(&pPed->GetPosition(), pZone))
				continue;
			if (pos.z - COP_PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + COP_PED_FIND_Z_OFFSET < pPed->GetPosition().z)
				continue;
			ped_handle = CPools::GetPedPool()->GetIndex(pPed);
			CTheScripts::LastRandomPedId = ped_handle;
			pPed->CharCreatedBy = MISSION_CHAR;
			pPed->bRespondsToThreats = false;
			++CPopulation::ms_nTotalMissionPeds;
			if (m_bIsMissionScript)
				CTheScripts::MissionCleanUp.AddEntityToList(ped_handle, CLEANUP_CHAR);
		}
		SET_INTEGER_PARAM(0, ped_handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	*/
	case COMMAND_SET_CHAR_OBJ_FLEE_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_FLEE_CAR, pVehicle);
		return 0;
	}
	case COMMAND_GET_DRIVER_OF_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CPed* pDriver = pVehicle->pDriver;
		if (pDriver)
			SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pDriver));
		else
			SET_INTEGER_PARAM(0, -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_NUMBER_OF_FOLLOWERS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pLeader = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pLeader);
		int total = 0;
		int i = CPools::GetPedPool()->GetSize();
		while (--i) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (pPed->m_leader == pLeader)
				total++;
		}
		SET_INTEGER_PARAM(0, total);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GIVE_REMOTE_CONTROLLED_MODEL_TO_PLAYER:
	{
		CollectParameters(&m_nIp, 6);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRemote::GivePlayerRemoteControlledCar(pos.x, pos.y, pos.z, DEGTORAD(GET_FLOAT_PARAM(4)), GET_INTEGER_PARAM(5));
		return 0;
	}
	case COMMAND_GET_CURRENT_PLAYER_WEAPON:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->GetWeapon()->m_eWeaponType);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_CURRENT_CHAR_WEAPON:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->GetWeapon()->m_eWeaponType);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_2D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_2D:
	case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_2D:
	case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_3D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_3D:
	case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_3D:
		LocateCharObjectCommand(command, &m_nIp);
		return 0;
	case COMMAND_SET_CAR_TEMP_ACTION:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_nTempAction = (uint8)GET_INTEGER_PARAM(1);
		pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + GET_INTEGER_PARAM(2);
		return 0;
	}
	/*
	case COMMAND_SET_CAR_HANDBRAKE_TURN_RIGHT:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_nTempAction = TEMPACT_HANDBRAKETURNRIGHT;
		pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CAR_HANDBRAKE_STOP:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->AutoPilot.m_nTempAction = TEMPACT_HANDBRAKESTRAIGHT;
		pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + GET_INTEGER_PARAM(1);
		return 0;
	}
	*/
	case COMMAND_IS_CHAR_ON_ANY_BIKE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle&& pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BIKE);
		return 0;
	}
	/*
	case COMMAND_LOCATE_SNIPER_BULLET_2D:
	case COMMAND_LOCATE_SNIPER_BULLET_3D:
		LocateSniperBulletCommand(command, &m_nIp);
		return 0;
	case COMMAND_GET_NUMBER_OF_SEATS_IN_MODEL:
		CollectParameters(&m_nIp, 1);
		SET_INTEGER_PARAM(0, CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(GET_INTEGER_PARAM(0)) + 1);
		StoreParameters(&m_nIp, 1);
		return 0;
	*/
	case COMMAND_IS_PLAYER_ON_ANY_BIKE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BIKE);
		return 0;
	}
	/*
	case COMMAND_IS_CHAR_LYING_DOWN:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bFallenDown);
		return 0;
	}
	*/
	case COMMAND_CAN_CHAR_SEE_DEAD_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		int pedtype = GET_INTEGER_PARAM(1);
		bool can = false;
		for (int i = 0; i < pPed->m_numNearPeds; i++) {
			CPed* pTestPed = pPed->m_nearPeds[i];
			if (pTestPed->m_fHealth <= 0.0f && pTestPed->m_nPedType == pedtype && pPed->OurPedCanSeeThisOne(pTestPed))
				can = true;
		}
		UpdateCompareFlag(can);
		return 0;
	}
	case COMMAND_SET_ENTER_CAR_RANGE_MULTIPLIER:
		CollectParameters(&m_nIp, 1);
		CPed::nEnterCarRangeMultiplier = GET_FLOAT_PARAM(0);
		return 0;
	case COMMAND_SET_THREAT_REACTION_RANGE_MULTIPLIER:
		CollectParameters(&m_nIp, 1);
		CPed::nThreatReactionRangeMultiplier = GET_FLOAT_PARAM(0);
		if (CPed::nThreatReactionRangeMultiplier < 1)
			CPed::nThreatReactionRangeMultiplier = 1;
		return 0;
	case COMMAND_SET_CHAR_CEASE_ATTACK_TIMER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_ceaseAttackTimer = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_GET_REMOTE_CONTROLLED_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CWorld::Players[GET_INTEGER_PARAM(0)].m_pRemoteVehicle;
		if (pVehicle)
			SET_INTEGER_PARAM(0, CPools::GetVehiclePool()->GetIndex(pVehicle));
		else
			SET_INTEGER_PARAM(0, -1);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_PC_VERSION:
#ifdef GTA_PC
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	//case COMMAND_REPLAY:
	//case COMMAND_IS_REPLAY_PLAYING:
	case COMMAND_IS_MODEL_AVAILABLE:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CModelInfo::GetModelInfo(GET_INTEGER_PARAM(0)) != nil);
		return 0;
	case COMMAND_SHUT_CHAR_UP:
		CollectParameters(&m_nIp, 2);
		DMAudio.SetPedTalkingStatus(CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0)), GET_INTEGER_PARAM(1) == 0);
		return 0;
	case COMMAND_SET_ENABLE_RC_DETONATE:
		CollectParameters(&m_nIp, 1);
		CVehicle::bDisableRemoteDetonation = !GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_CAR_RANDOM_ROUTE_SEED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_nRouteSeed = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_IS_ANY_PICKUP_AT_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		CRunningScript::UpdateCompareFlag(CPickups::TestForPickupsInBubble(pos, GET_FLOAT_PARAM(3)));
		return 0;
	}
	//case COMMAND_GET_FIRST_PICKUP_COORDS:
	//case COMMAND_GET_NEXT_PICKUP_COORDS:
	case COMMAND_REMOVE_ALL_CHAR_WEAPONS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->ClearWeapons();
		return 0;
	}
	case COMMAND_HAS_PLAYER_GOT_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		bool bFound = false;
		for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
			if (pPed->GetWeapon(i).m_eWeaponType == GET_INTEGER_PARAM(1)) {
				bFound = true;
				break;
			}
		}
		UpdateCompareFlag(bFound);
		return 0;
	}
	case COMMAND_HAS_CHAR_GOT_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		bool bFound = false;
		for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
			if (pPed->GetWeapon(i).m_eWeaponType == GET_INTEGER_PARAM(1)) {
				bFound = true;
				break;
			}
		}
		UpdateCompareFlag(bFound);
		return 0;
	}
	//case COMMAND_IS_PLAYER_FACING_CHAR:
	case COMMAND_SET_TANK_DETONATE_CARS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle && pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		((CAutomobile*)pVehicle)->bTankDetonateCars = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_GET_POSITION_OF_ANALOGUE_STICKS:
	{
		CollectParameters(&m_nIp, 1);
		CPad* pPad = CPad::GetPad(GET_INTEGER_PARAM(0));
		SET_INTEGER_PARAM(0, pPad->NewState.LeftStickX);
		SET_INTEGER_PARAM(1, pPad->NewState.LeftStickY);
		SET_INTEGER_PARAM(2, pPad->NewState.RightStickX);
		SET_INTEGER_PARAM(3, pPad->NewState.RightStickY);
		StoreParameters(&m_nIp, 4);
		return 0;
	}
	case COMMAND_IS_CAR_ON_FIRE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		bool bOnFire = false;
		if (pVehicle->m_pCarFire)
			bOnFire = true;
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR && ((CAutomobile*)pVehicle)->Damage.GetEngineStatus() >= ENGINE_STATUS_ON_FIRE)
			bOnFire = true;
		if (pVehicle->m_fHealth < 250.0f)
			bOnFire = true;
		UpdateCompareFlag(bOnFire);
		return 0;
	}
	case COMMAND_IS_CAR_TYRE_BURST:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		bool bIsBurst = false;
		CBike* pBike = (CBike*)pVehicle;
		if (pVehicle->IsBike()) {
			if (GET_INTEGER_PARAM(1) == 4) {
				for (int i = 0; i < 2; i++) {
					if (pBike->m_wheelStatus[i] == WHEEL_STATUS_BURST)
						bIsBurst = true;
				}
			}
			else {
				if (GET_INTEGER_PARAM(1) == 2)
					SET_INTEGER_PARAM(1, 0);
				if (GET_INTEGER_PARAM(1) == 3)
					SET_INTEGER_PARAM(1, 1);
				bIsBurst = pBike->m_wheelStatus[GET_INTEGER_PARAM(1)] == WHEEL_STATUS_BURST;
			}
		}
		else {
			CAutomobile* pCar = (CAutomobile*)pVehicle;
			if (GET_INTEGER_PARAM(1) == 4) {
				for (int i = 0; i < 4; i++) {
					if (pCar->Damage.GetWheelStatus(i) == WHEEL_STATUS_BURST)
						bIsBurst = true;
				}
			}
			else
				bIsBurst = pCar->Damage.GetWheelStatus(GET_INTEGER_PARAM(1) == WHEEL_STATUS_BURST);
		}
		UpdateCompareFlag(bIsBurst);
		return 0;
	}
	//case COMMAND_SET_CAR_DRIVE_STRAIGHT_AHEAD:
	//case COMMAND_SET_CAR_WAIT:
	//case COMMAND_IS_PLAYER_STANDING_ON_A_VEHICLE:
	//case COMMAND_IS_PLAYER_FOOT_DOWN:
	//case COMMAND_IS_CHAR_FOOT_DOWN:
	case COMMAND_INITIALISE_OBJECT_PATH: {
		CollectParameters(&m_nIp, 2);
		int32 counter = 0;
		while (counter < 3 && CScriptPaths::aArray[counter].m_state != SCRIPT_PATH_DISABLED) {
			counter++;
		}
		CScriptPaths::aArray[counter].InitialiseOne(GET_INTEGER_PARAM(0), GET_FLOAT_PARAM(1));
		SET_INTEGER_PARAM(0, counter);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_START_OBJECT_ON_PATH:
	{
		CollectParameters(&m_nIp, 2);
		CObject *pObj = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		assert(pObj);
		CScriptPaths::aArray[GET_INTEGER_PARAM(1)].SetObjectToControl(pObj);
		return 0;
	}
	case COMMAND_SET_OBJECT_PATH_SPEED:
	{
		CollectParameters(&m_nIp, 2);
		CScriptPaths::aArray[GET_INTEGER_PARAM(0)].m_fSpeed = GET_FLOAT_PARAM(1);
		return 0;
	}
	case COMMAND_SET_OBJECT_PATH_POSITION:
	{
		CollectParameters(&m_nIp, 2);
		CScriptPaths::aArray[GET_INTEGER_PARAM(0)].m_fPosition = GET_FLOAT_PARAM(1);
		return 0;
	}
	//case COMMAND_GET_OBJECT_DISTANCE_ALONG_PATH:
	case COMMAND_CLEAR_OBJECT_PATH:
	{
		CollectParameters(&m_nIp, 1);
		CScriptPaths::aArray[GET_INTEGER_PARAM(0)].Clear();
		return 0;
	}
	case COMMAND_HELI_GOTO_COORDS:
	{
		CollectParameters(&m_nIp, 5);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle && pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI);
		((CAutomobile*)pVehicle)->TellHeliToGoToCoors(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), GET_FLOAT_PARAM(3), GET_INTEGER_PARAM(4));
		return 0;
	}
	case COMMAND_IS_INT_VAR_EQUAL_TO_CONSTANT:
	{
		int32* ptr = GetPointerToScriptVariable(&m_nIp, VAR_GLOBAL);
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(*ptr == GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_IS_INT_LVAR_EQUAL_TO_CONSTANT:
	{
		int32* ptr = GetPointerToScriptVariable(&m_nIp, VAR_LOCAL);
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(*ptr == GET_INTEGER_PARAM(0));
		return 0;
	}
	case COMMAND_GET_DEAD_CHAR_PICKUP_COORDS:
	{
		CollectParameters(&m_nIp, 1);
		CPed *pTarget = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CVector pos;
		pTarget->CreateDeadPedPickupCoors(&pos.x, &pos.y, &pos.z);
		SET_VECTOR_PARAM(0, pos);
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_CREATE_PROTECTION_PICKUP:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GetActualPickupIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CPickups::GenerateNewOne(pos, MI_PICKUP_REVENUE, PICKUP_ASSET_REVENUE, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4))); // TODO: gpModelIndices
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	/*
	case COMMAND_IS_CHAR_IN_ANY_BOAT:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BOAT);
		return 0;
	}
	*/
	case COMMAND_IS_PLAYER_IN_ANY_BOAT:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BOAT);
		return 0;
	}
	/*
	case COMMAND_IS_CHAR_IN_ANY_HELI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI);
		return 0;
	}
	*/
	case COMMAND_IS_PLAYER_IN_ANY_HELI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI);
		return 0;
	}
	/*
	case COMMAND_IS_CHAR_IN_ANY_PLANE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_PLANE);
		return 0;
	}
	*/
	case COMMAND_IS_PLAYER_IN_ANY_PLANE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI);
		return 0;
	}
	case COMMAND_IS_CHAR_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pPed && pPed->bIsInWater);
		return 0;
	}
	case COMMAND_SET_VAR_INT_TO_CONSTANT:
	{
		int32* ptr = GetPointerToScriptVariable(&m_nIp, VAR_GLOBAL);
		CollectParameters(&m_nIp, 1);
		*ptr = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_SET_LVAR_INT_TO_CONSTANT:
	{
		int32* ptr = GetPointerToScriptVariable(&m_nIp, VAR_LOCAL);
		CollectParameters(&m_nIp, 1);
		*ptr = GET_INTEGER_PARAM(0);
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}
