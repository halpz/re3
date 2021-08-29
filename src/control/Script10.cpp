#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "CarCtrl.h"
#include "DMAudio.h"
#include "Frontend.h"
#include "GameLogic.h"
#include "Garages.h"
#include "General.h"
#include "Hud.h"
#include "Messages.h"
#include "Object.h"
#include "Pad.h"
#include "Pickups.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "Vehicle.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "User.h"
#include "Weather.h"
#include "World.h"

bool gDeveloperFlag;

int8 CRunningScript::ProcessCommands1600To1699(int32 command)
{
	switch (command) {
	case COMMAND_ADD_NOODLES_DELIVERED:
		CollectParameters(&m_nIp, 1);
		// CStats::NoodlesDelievered += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_SCRAPYARD_CHALLENGE_SCORE:
		CollectParameters(&m_nIp, 1);
		//CStats::TopScrapyardChallengeScore = Max(CStats::TopScrapyardChallengeScore, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_9MM_MAYHEM_SCORE:
		CollectParameters(&m_nIp, 1);
		//CStats::Top9mmMayhemScore = Max(CStats::Top9mmMayhemScore, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_SCOOTER_SHOOTER_SCORE:
		CollectParameters(&m_nIp, 1);
		//CStats::TopScooterShooterScore = Max(CStats::TopScooterShooterScore, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_ADD_MONEY_MADE_FROM_TOURIST:
		CollectParameters(&m_nIp, 1);
		// CStats::MoneyMadeFromTourist += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_ADD_TOURISTS_TAKEN_TO_SPOTS:
		CollectParameters(&m_nIp, 1);
		// CStats::TouristsTakenToSpots += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_ADD_EXPORTED_CARS:
		CollectParameters(&m_nIp, 1);
		// CStats::NumberOfExportedCars += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_TOTAL_EXPORT_CARS:
		CollectParameters(&m_nIp, 1);
		// CStats::TotalNumberOfCarExport = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_DIRT_BIKE_FASTEST_LAP:
		CollectParameters(&m_nIp, 2);
		// CStats::RegisterDirtBikeFastestLap(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_REGISTER_DIRT_BIKE_FASTEST_TIME:
		CollectParameters(&m_nIp, 2);
		// CStats::RegisterDirtBikeFastestTime(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_REGISTER_DIRT_BIKE_AIR_TIME:
		CollectParameters(&m_nIp, 1);
		//CStats::DirtBikeMostAir = Max(CStats::DirtBikeMostAir, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_ADD_ARROW_3D_MARKER:
	{
		uint32 ip = m_nIp;
		uint32 id = (uint32)(uintptr)GetPointerToScriptVariable(&ip, 0);
		CollectParameters(&m_nIp, 10);
		CVector pos = GET_VECTOR_PARAM(0);
		CVector dir = GET_VECTOR_PARAM(3);
		pos.z += GET_FLOAT_PARAM(9) + 7.0f;
		//C3dMarkers::PlaceMarker(id, MARKERTYPE_ARROW, pos, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(8), 200, 1, 3.2f, 1, dir, 1.0f, 0, 0); - TODO
		return 0;
	}
	case COMMAND_PRINT_NOW_OVERRIDE_FADE:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // true, true
		return 0;
	}
	case COMMAND_GET_PICKUP_VALUE:
	{
		CollectParameters(&m_nIp, 1);
		SET_INTEGER_PARAM(0, CPickups::GetValue(GET_INTEGER_PARAM(0)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_PICKUP_VALUE:
	{
		CollectParameters(&m_nIp, 2);
		CPickups::SetValue(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_DEVELOPER:
#ifdef GTA_NETWORK
		UpdateCompareFlag(gDeveloperFlag || gIsMultiplayerGame);
#else
		UpdateCompareFlag(gDeveloperFlag);
#endif
		return 0;
	case COMMAND_SET_DEVELOPER_FLAG:
		CollectParameters(&m_nIp, 1);
		gDeveloperFlag = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_WICHITA_WIPEOUT_SCORE:
		CollectParameters(&m_nIp, 1);
		//CStats::TopWichitaWipeoutScore = Max(CStats::TopWichitaWipeoutScore, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_ATTACH_OBJECT_TO_CAR:
	{
		CollectParameters(&m_nIp, 5);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		CVector offset = GET_VECTOR_PARAM(2);
		// pObject->AttachObjectToEntity(pVehicle, offset);
		return 0;
	}
	case COMMAND_DETACH_OBJECT_FROM_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		// if (pObject && pObject->m_pAttachedTo)
		//	pObject->DettachObjectFromEntity();
		return 0;
	}
	case COMMAND_SET_PAD_STICKS_MULTIPLIER:
	{
		CollectParameters(&m_nIp, 2);
		CPad::GetPad(0)->unk_B4 = GET_FLOAT_PARAM(0);
		CPad::GetPad(0)->unk_B8 = GET_FLOAT_PARAM(1);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // false, true
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW_OVERRIDE_FADE:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // true, true
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_SUBTITLE_NOW_NO_BRIEF:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		if (FrontEndMenuManager.m_PrefsShowSubtitles)
			CMessages::AddMessageJumpQ(key, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)); // false, false
		else
			CMessages::AddToPreviousBriefArray(key, -1, -1, -1, -1, -1, -1, nil);
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_NOW_NO_BRIEF:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddMessageJumpQWithNumber(key, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1); // 0
		return 0;
	}
	case COMMAND_GET_ANGLE_BETWEEN_POINTS:
	{
		CollectParameters(&m_nIp, 4);
		SET_FLOAT_PARAM(0, CGeneral::GetAngleBetweenPoints(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), GET_FLOAT_PARAM(3)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_OVERRIDE_CHAR_MOVE_ANIM:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOverrideMoveAnim = true;
		return 0;
	}
	case COMMAND_1627:
	{
		CollectParameters(&m_nIp, 1);
		// something related to debug menu, not implemented
		return 0;
	}
	case COMMAND_ENABLE_EMERGENCY_VEHICLES:
	{
		CollectParameters(&m_nIp, 1);
		gbEmergencyVehiclesEnabled = GET_INTEGER_PARAM(0) != 0;
		return 0;
	}
	case COMMAND_ADD_UNLOCKED_COSTUME:
		CollectParameters(&m_nIp, 1);
		// CStats::AddUnlockedCostume(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CLEAR_MULTIPLAYER_SPLASH_SCREEN:
		// ClearMultiplayerSplashScreen();
		return 0;
	case COMMAND_PRINT_WITH_2_NUMBERS_NOW_NO_BRIEF:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageJumpQWithNumber(key, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1); // 0
		return 0;
	}
	case COMMAND_GET_OBJECT_ORIENTATION:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		SET_FLOAT_PARAM(1, LimitAngleOnCircle(RADTODEG(Asin(pObject->GetForward().z))));
		SET_FLOAT_PARAM(2, LimitAngleOnCircle(RADTODEG(Atan2(-pObject->GetForward().x, pObject->GetForward().y))));
		SET_FLOAT_PARAM(0, LimitAngleOnCircle(RADTODEG(Atan2(-pObject->GetRight().z, pObject->GetUp().z))));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_SET_OBJECT_ORIENTATION:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->SetOrientation(DEGTORAD(GET_FLOAT_PARAM(2)), DEGTORAD(GET_FLOAT_PARAM(1)), DEGTORAD(GET_FLOAT_PARAM(3)));
		return 0;
	}
	case COMMAND_CHANGE_ONSCREEN_COUNTER_PREFIX:
	{
		uint16 offset = (uint8*)GetPointerToScriptVariable(&m_nIp, VAR_GLOBAL) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 1);
		CUserDisplay::OnscnTimer.ChangeCounterPrefix(offset, GET_INTEGER_PARAM(0) != 0);
		return 0;
	}
	case COMMAND_STORE_PLAYER_OUTFIT:
	{
		char tmp[12]; // TODO
		CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			CGameLogic::mStoredPlayerOutfit[i] = tmp[i];
		printf("STORED PLAYOUR OUTFIT : %s\n", CGameLogic::mStoredPlayerOutfit);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		return 0;
	}
	case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_STRING:
	{
		char onscreen_str1[12];
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp, 0) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 2);
		wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]);
		strncpy(onscreen_str1, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CUserDisplay::OnscnTimer.AddCounter(var, GET_INTEGER_PARAM(1), onscreen_str1, 0, GET_INTEGER_PARAM(0), nil, 0);
		return 0;
	}
	case COMMAND_SET_PLAYER_CURRENT_WEAPON_AMMO_IN_CLIP:
	{
		CollectParameters(&m_nIp, 1);
		CWeapon* pWeapon = FindPlayerPed()->GetWeapon();
		if (pWeapon && GET_INTEGER_PARAM(0))
			pWeapon->m_nAmmoInClip = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_SET_CHAR_WAIT_STATE_REPEAT:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed)
			pPed->SetWaitState((eWaitState)GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2) >= 0 ? &GET_INTEGER_PARAM(2) : nil, true);
		return 0;
	}
	case COMMAND_REGISTER_BEST_TIME_GOGO_FAGGIO:
		CollectParameters(&m_nIp, 1);
		// CStats::RegisterBestTimeGoGoFaggio(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_LOCK_GARAGE:
		CollectParameters(&m_nIp, 2);
		CGarages::LockGarage(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_IS_FINAL_GAME:
#ifdef FINAL
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_SET_ALLOWED_COLLISION:
	{
		CollectParameters(&m_nIp, 2);
		CTheScripts::AllowedCollision[0] = GET_INTEGER_PARAM(0);
		CTheScripts::AllowedCollision[1] = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_REGISTER_GUARDIAN_ANGEL_LEVEL:
		CollectParameters(&m_nIp, 3);
		//CStats::GuardianAngelHighestLevel_Ind = Max(CStats::GuardianAngelHighestLevel_Ind, GET_INTEGER_PARAM(0));
		//CStats::GuardianAngelHighestLevel_Com = Max(CStats::GuardianAngelHighestLevel_Com, GET_INTEGER_PARAM(1));
		//CStats::GuardianAngelHighestLevel_Sub = Max(CStats::GuardianAngelHighestLevel_Sub, GET_INTEGER_PARAM(2));
		return 0;
	case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_NUMBER_AND_2_STRINGS:
	{
		char onscreen_str1[12];
		char onscreen_str2[12];
		uint16 var = (uint8*)GetPointerToScriptVariable(&m_nIp, 0) - CTheScripts::ScriptSpace;
		CollectParameters(&m_nIp, 3);
		wchar* text = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]);
		strncpy(onscreen_str1, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		wchar* text2 = TheText.Get((char*)&CTheScripts::ScriptSpace[m_nIp]);
		strncpy(onscreen_str2, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CUserDisplay::OnscnTimer.AddCounter(var, GET_INTEGER_PARAM(1), onscreen_str2, 0, GET_INTEGER_PARAM(0), onscreen_str1, GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_GET_PLAYER_STORED_WEAPON:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_storedWeapon);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISABLE_PAUSE_MENU:
		CollectParameters(&m_nIp, 1);
		// FrontEndMenuManager.mDisablePauseMenu = GET_INTEGER_PARAM(0) != 0; // TODO: static + member
		return 0;
	case COMMAND_IS_CHANNEL_PLAYING:
		CollectParameters(&m_nIp, 1);
		//UpdateCompareFlag(DMAudio.IsChannelPlaying(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_SET_CLOCK_EVENT_WARNING:
		CollectParameters(&m_nIp, 3);
		/*
		if (CHud::m_ClockEventWarningMinutes || GET_INTEGER_PARAMS(2)){
			CHud::m_ClockEventWarningMinutes = GET_INTEGER_PARAMS(2);
			CHud::m_ClockEventMinutes = GET_INTEGER_PARAMS(1);
			CHud::m_ClockEventHours = GET_INTEGER_PARAMS(0);
			CHud::m_ClockEventFlashTimer = 0;
		}
		*/
		return 0;
	case COMMAND_SET_EXTRA_COLOUR_LIGHT_DIRECTION:
		CollectParameters(&m_nIp, 3);
		// CWeather::ExtraColourLightDir = GET_VECTOR_PARAM(0);
		// CWeather::ExtraColourLightDir.Normalise();
		return 0;
	case COMMAND_SET_CHAR_CAN_BE_TARGETTED_BY_LEADER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bCanBeTargettedByLeader = GET_INTEGER_PARAM(1) != 0;
		return 0;
	}
	case COMMAND_PRINT_HELP_NO_BRIEF:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false); // + false, false
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER_NO_BRIEF:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + false
		return 0;
	}
	case COMMAND_PRINT_HELP_ALWAYS_NO_BRIEF:
	{
		// CHud::mAlwaysAllowHelpText = true;
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false); // + false, false
		return 0;
	}
	case COMMAND_PRINT_HELP_FOREVER_ALWAYS_NO_BRIEF:
	{
		// CHud::mAlwaysAllowHelpText = true;
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CHud::SetHelpMessage(text, false, true); // + false
		return 0;
	}
	case COMMAND_SET_CAR_IS_REWARD:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bRewardVehicle = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_FREEZE_ALL_PLAYER_FOLLOWERS:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPlayerPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPlayerPed);
		for (int i = 0; i < CPools::GetVehiclePool()->GetSize(); i++) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (pPed && IsPedPointerValid(pPed)) {
				if (pPed->m_leader == pPlayerPed || (pPed->m_objective == OBJECTIVE_FOLLOW_CHAR_IN_FORMATION && pPed->m_pedInObjective == pPlayerPed))
					pPed->bIsFrozen = (GET_INTEGER_PARAM(1) != 0);
			}
		}
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}