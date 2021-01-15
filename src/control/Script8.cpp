#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "DMAudio.h"
#if ((defined GTAVC_JP_PATCH || defined SUPPORT_JAPANESE_SCRIPT) && defined MORE_LANGUAGES)
#include "Frontend.h"
#endif
#include "GameLogic.h"
#include "Garages.h"
#ifdef MISSION_REPLAY
#include "GenericGameStorage.h"
#endif
#if (defined GTA_PC && !defined GTAVC_JP_PATCH || defined GTA_XBOX || defined SUPPORT_XBOX_SCRIPT || defined GTA_MOBILE || defined SUPPORT_MOBILE_SCRIPT)
#include "General.h"
#include "maths.h"
#endif
#include "Hud.h"
#include "Pad.h"
#include "PedAttractor.h"
#include "Population.h"
#include "Pools.h"
#include "RpAnimBlend.h"
#include "Stats.h"
#include "VisibilityPlugins.h"
#include "Wanted.h"
#include "WaterLevel.h"
#include "World.h"
#include "Zones.h"

int8 CRunningScript::ProcessCommands1400To1499(int32 command)
{
	switch (command) {
	case COMMAND_REGISTER_VIGILANTE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelVigilanteMission(ScriptParams[0]);
		return 0;
	case COMMAND_CLEAR_ALL_CHAR_ANIMS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		if (!pPed->bInVehicle) {
			pPed->m_pVehicleAnim = nil;
			pPed->RestartNonPartialAnims();
			RpAnimBlendClumpRemoveAllAssociations(pPed->GetClump());
			pPed->SetPedState(PED_IDLE);
			pPed->SetMoveState(PEDMOVE_STILL);
			pPed->m_nLastPedState = PED_NONE;
			pPed->ClearAimFlag();
			pPed->ClearLookFlag();
			pPed->bIsPointingGunAt = false;
			if (pPed->IsPlayer())
				((CPlayerPed*)pPed)->m_fMoveSpeed = 0.0f;
			else
				pPed->m_nStoredMoveState = PEDMOVE_STILL;
			CAnimManager::AddAnimation(pPed->GetClump(), pPed->m_animGroup, ANIM_IDLE_STANCE);
			pPed->bIsPedDieAnimPlaying = false;
		}
		return 0;
	}
	case COMMAND_SET_MAXIMUM_NUMBER_OF_CARS_IN_GARAGE:
		CollectParameters(&m_nIp, 2);
		CGarages::SetMaxNumStoredCarsForGarage(ScriptParams[0], ScriptParams[1]);
		return 0;
	case COMMAND_WANTED_STARS_ARE_FLASHING:
	{
		CWanted* pWanted = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pWanted;
		UpdateCompareFlag(pWanted->m_nMinWantedLevel - pWanted->m_nWantedLevel > 0);
		return 0;
	}
	case COMMAND_SET_ALLOW_HURRICANES:
		CollectParameters(&m_nIp, 1);
		CStats::NoMoreHurricanes = ScriptParams[0];
		return 0;
	case COMMAND_PLAY_ANNOUNCEMENT:
	{
		CollectParameters(&m_nIp, 1);
		DMAudio.PlayRadioAnnouncement(ScriptParams[0] + STREAMED_SOUND_NEWS_A);
		return 0;
	}
	case COMMAND_SET_PLAYER_IS_IN_STADIUM:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::bPlayerIsInTheStatium = ScriptParams[0];
		return 0;
	}
	case COMMAND_GET_BUS_FARES_COLLECTED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[ScriptParams[0]];
		ScriptParams[0] = pPlayerInfo->m_pPed->m_nLastBusFareCollected;
		pPlayerInfo->m_pPed->m_nLastBusFareCollected = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[1]);
		script_assert(pVehicle);
		ScriptParams[0] = 0;
		if (pPed->m_objective == OBJECTIVE_NONE && !pPed->bHasAlreadyUsedAttractor) {
			C2dEffect* pEffect = (C2dEffect*)GetPedAttractorManager()->GetEffectForIceCreamVan(pVehicle, pPed->GetPosition()); // has to be casted, because inner methods are const
			if (pEffect) {
				CVector pos;
				CPedAttractorManager::ComputeEffectPos(pEffect, pVehicle->GetMatrix(), pos);
				if ((pPed->GetPosition() - pos).MagnitudeSqr() < SQR(20.0f)) {
					if (GetPedAttractorManager()->HasEmptySlot(pEffect) && GetPedAttractorManager()->IsApproachable(pEffect, pVehicle->GetMatrix(), 0, pPed)) {
						if (GetPedAttractorManager()->RegisterPedWithAttractor(pPed, pEffect, pVehicle->GetMatrix()))
							ScriptParams[0] = 1;
					}
				}
			}
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISPLAY_RADAR:
		CollectParameters(&m_nIp, 1);
		CHud::m_HideRadar = ScriptParams[0] == 0;
		return 0;
	case COMMAND_REGISTER_BEST_POSITION:
		CollectParameters(&m_nIp, 2);
		CStats::RegisterBestPosition(ScriptParams[0], ScriptParams[1]);
		return 0;
	case COMMAND_IS_PLAYER_IN_INFO_ZONE:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[ScriptParams[0]];
		char key[KEY_LENGTH_IN_SCRIPT];
		memset(key, 0, KEY_LENGTH_IN_SCRIPT);
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CVector pos = pPlayerInfo->GetPos();
		CZone* infoZone = CTheZones::FindInformationZoneForPosition(&pos);
		UpdateCompareFlag(strncmp(key, infoZone->name, 8) == 0); // original code doesn't seem to be using strncmp in here and compare 2 ints instead
		return 0;
	}
	case COMMAND_CLEAR_CHAR_ICE_CREAM_PURCHASE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		if (pPed->m_attractor)
			GetPedAttractorManager()->DeRegisterPed(pPed, pPed->m_attractor);
		return 0;
	}
	case COMMAND_IS_IN_CAR_FIRE_BUTTON_PRESSED:
		UpdateCompareFlag(CPad::GetPad(0)->GetCarGunFired());
		return 0;
	case COMMAND_HAS_CHAR_ATTEMPTED_ATTRACTOR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		UpdateCompareFlag(pPed->bHasAlreadyUsedAttractor);
		return 0;
	}
	case COMMAND_SET_LOAD_COLLISION_FOR_CAR_FLAG:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[0]);
		script_assert(pVehicle);
		if (ScriptParams[1]) {
			pVehicle->bDontLoadCollision = false;
			if (m_bMissionFlag) {
				CWorld::Remove(pVehicle);
				pVehicle->bIsStaticWaitingForCollision = true;
				CWorld::Add(pVehicle);
			}
		}
		else {
			pVehicle->bDontLoadCollision = true;
			if (pVehicle->bIsStaticWaitingForCollision) {
				pVehicle->bIsStaticWaitingForCollision = false;
				if (!pVehicle->GetIsStatic())
					pVehicle->AddToMovingList();
			}
		}
		return 0;
	}
	case COMMAND_SET_LOAD_COLLISION_FOR_CHAR_FLAG:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		if (ScriptParams[1]) {
			pPed->bDontLoadCollision = false;
			if (m_bMissionFlag) {
				CWorld::Remove(pPed);
				pPed->bIsStaticWaitingForCollision = true;
				CWorld::Add(pPed);
			}
		}
		else {
			pPed->bDontLoadCollision = true;
			if (pPed->bIsStaticWaitingForCollision) {
				pPed->bIsStaticWaitingForCollision = false;
				if (!pPed->GetIsStatic())
					pPed->AddToMovingList();
			}
		}
		return 0;
	}
	//case COMMAND_SET_LOAD_COLLISION_FOR_OBJECT_FLAG:
	case COMMAND_ADD_BIG_GUN_FLASH:
	{
		CollectParameters(&m_nIp, 6);
		CWeapon::AddGunFlashBigGuns(*(CVector*)&ScriptParams[0], *(CVector*)&ScriptParams[3]);
		return 0;
	}
	case COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		UpdateCompareFlag(pPed->bBoughtIceCream);
		return 0;
	}
	case COMMAND_GET_PROGRESS_PERCENTAGE:
		*(float*)&ScriptParams[0] = CStats::GetPercentageProgress();
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_SHORTCUT_PICKUP_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutPointAfterDeath(*(CVector*)&ScriptParams[0], *(float*)&ScriptParams[3]);
		return 0;
	}
	case COMMAND_SET_SHORTCUT_DROPOFF_POINT_FOR_MISSION:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutDropOffPointForMission(*(CVector*)&ScriptParams[0], *(float*)&ScriptParams[3]);
		return 0;
	}
	case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_AREA:
	{
		CollectParameters(&m_nIp, 7);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		float x1 = *(float*)&ScriptParams[0];
		float y1 = *(float*)&ScriptParams[1];
		float x2 = *(float*)&ScriptParams[2];
		float y2 = *(float*)&ScriptParams[3];
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (CTheScripts::LastRandomPedId == CPools::GetPedPool()->GetIndex(pPed))
				continue;
			if (pPed->CharCreatedBy != RANDOM_CHAR)
				continue;
			if (!pPed->IsPedInControl())
				continue;
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->m_nWaitState != WAITSTATE_FALSE)
				continue;
			if (pPed->bHasAlreadyUsedAttractor)
				continue;
			if (pPed->m_attractor)
				continue;
			if (!ThisIsAValidRandomPed(pPed->m_nPedType, ScriptParams[4], ScriptParams[5], ScriptParams[6]))
				continue;
			if (pPed->bIsLeader || pPed->m_leader)
				continue;
			if (!pPed->IsWithinArea(x1, y1, x2, y2))
				continue;
			if (pos.z - PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + PED_FIND_Z_OFFSET < pPed->GetPosition().z)
				continue;
			ped_handle = CPools::GetPedPool()->GetIndex(pPed);
			CTheScripts::LastRandomPedId = ped_handle;
			pPed->CharCreatedBy = MISSION_CHAR;
			pPed->bRespondsToThreats = false;
			++CPopulation::ms_nTotalMissionPeds;
			if (m_bIsMissionScript)
				CTheScripts::MissionCleanUp.AddEntityToList(ped_handle, CLEANUP_CHAR);
		}
		ScriptParams[0] = ped_handle;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	//case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_ZONE:
	case COMMAND_UNLOCK_ALL_CAR_DOORS_IN_AREA:
	{
		CollectParameters(&m_nIp, 4);
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = *(float*)&ScriptParams[0];
		float infY = *(float*)&ScriptParams[1];
		float supX = *(float*)&ScriptParams[2];
		float supY = *(float*)&ScriptParams[3];
		while (i--) {
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
			if (!pVehicle)
				continue;
			if (pVehicle->IsWithinArea(infX, infY, supX, supY))
				pVehicle->m_nDoorLock = CARLOCK_UNLOCKED;
		}
		return 0;
	}
	case COMMAND_SET_GANG_ATTACK_PLAYER_WITH_COPS:
		CollectParameters(&m_nIp, 2);
		CGangs::SetWillAttackPlayerWithCops((ePedType)((int)PEDTYPE_GANG1 + ScriptParams[0]), !!ScriptParams[1]);
		return 0;
	case COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		pPed->bHeldHostageInCar = ScriptParams[1];
		return 0;
	}
	case COMMAND_SET_VEHICLE_TO_FADE_IN:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[0]);
		script_assert(pVehicle);
		CVisibilityPlugins::SetClumpAlpha(pVehicle->GetClump(), ScriptParams[1]);
		return 0;
	}
	case COMMAND_REGISTER_ODDJOB_MISSION_PASSED:
		++CStats::MissionsPassed;
		CStats::CheckPointReachedSuccessfully();
		CTheScripts::LastMissionPassedTime = CTimer::GetTimeInMilliseconds();
		CGameLogic::RemoveShortCutDropOffPointForMission();
		return 0;
	case COMMAND_IS_PLAYER_IN_SHORTCUT_TAXI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[ScriptParams[0]].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle && pPed->m_pMyVehicle == CGameLogic::pShortCutTaxi);
		return 0;
	}
	case COMMAND_IS_CHAR_DUCKING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		UpdateCompareFlag(RpAnimBlendClumpGetAssociation(pPed->GetClump(), ANIM_DUCK_DOWN) != nil);
		return 0;
	}
	case COMMAND_CREATE_DUST_EFFECT_FOR_CUTSCENE_HELI:
	{
		CollectParameters(&m_nIp, 3);
		CObject* pHeli = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		bool found = false;
		float waterLevel = -1000.0f;
		CVector pos = pHeli->GetPosition();
		float radius = *(float*)&ScriptParams[1];
		float ground = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &found);
		if (!CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &waterLevel, false))
			waterLevel = 0.0f;
		if (waterLevel > ground)
			ground = waterLevel;
		if (ScriptParams[2] > 8)
			ScriptParams[2] = 8;
		CVehicle::HeliDustGenerate(pHeli, (pos.z - ground - 1.0f - radius) * 0.3 + radius, ground, ScriptParams[2]);
		return 0;
	}
	case COMMAND_REGISTER_FIRE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelFireMission(ScriptParams[0]);
		return 0;
	case COMMAND_IS_AUSTRALIAN_GAME:
		UpdateCompareFlag(false); // should we make some check?
		return 0;
	case COMMAND_DISARM_CAR_BOMB:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[0]);
		if (pVehicle->m_bombType != CARBOMB_NONE) {
			pVehicle->m_bombType = CARBOMB_NONE;
			pVehicle->m_pBombRigger = nil;
		}
		return 0;
	}
	case COMMAND_IS_JAPANESE_GAME:
#ifdef MORE_LANGUAGES
		UpdateCompareFlag(FrontEndMenuManager.m_PrefsLanguage == LANGUAGE_JAPANESE);
#elif (defined GTAVC_JP_PATCH)
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_1442:
		script_assert(false);
		return 0;
	case COMMAND_1443:
		script_assert(false);
		return 0;
	case COMMAND_1444:
		script_assert(false);
		return 0;
	case COMMAND_1445:
		script_assert(false);
		return 0;
	case COMMAND_1446:
		script_assert(false);
		return 0;
	case COMMAND_1447:
		script_assert(false);
		return 0;
	case COMMAND_1448:
		script_assert(false);
		return 0;
	case COMMAND_1449:
		script_assert(false);
		return 0;
	case COMMAND_1450:
		script_assert(false);
		return 0;
	case COMMAND_1451:
		CollectParameters(&m_nIp, 1);
		// TODO (GET_PAD_BUTTON_STATE)
		ScriptParams[0] = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_1452:
		script_assert(false);
		return 0;
	case COMMAND_1453:
		script_assert(false);
		return 0;
	case COMMAND_CALL:
	case COMMAND_NOTCALL:
	{
		m_anStack[m_nStackPointer++] = m_nIp | BIT(STACKVALUE_IS_FUNCTION_CALL_BIT) | ((command == COMMAND_NOTCALL) ? BIT(STACKVALUE_INVERT_RETURN_BIT) : 0);
		uint8 nInputParams = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint8 nOutputParameters = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint8 nLocalsOffset = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint32 nIPBeforeParameters = m_nIp;
		CollectParameters(&m_nIp, 1);
		if (nInputParams)
			CollectParameters(&m_nIp, nInputParams, &m_anLocalVariables[m_nLocalsPointer + nLocalsOffset]);
		m_nLocalsPointer += nLocalsOffset;
		m_anStack[m_nStackPointer - 1] |= (m_nIp - nIPBeforeParameters) << STACKVALUE_IP_PARAMS_OFFSET;
		if (ScriptParams[0] < 0)
			m_nIp = CTheScripts::MainScriptSize - ScriptParams[0];
		else
			m_nIp = ScriptParams[0];
		return 0;
	}
	case COMMAND_1456:
		script_assert(false);
		return 0;
	case COMMAND_1457:
		script_assert(false);
		return 0;
	case COMMAND_1458:
		script_assert(false);
		return 0;
	case COMMAND_1459:
		script_assert(false);
		return 0;
	case COMMAND_1460:
		script_assert(false);
		return 0;
	case COMMAND_1461:
		script_assert(false);
		return 0;
	case COMMAND_1462:
		script_assert(false);
		return 0;
	case COMMAND_1463:
		script_assert(false);
		return 0;
	case COMMAND_1464:
		script_assert(false);
		return 0;
	case COMMAND_1465:
		script_assert(false);
		return 0;
	case COMMAND_1466:
		script_assert(false);
		return 0;
	case COMMAND_1467:
		script_assert(false);
		return 0;
	case COMMAND_1468:
		script_assert(false);
		return 0;
	case COMMAND_1469:
		script_assert(false);
		return 0;
	case COMMAND_1470:
		script_assert(false);
		return 0;
	case COMMAND_1471:
		script_assert(false);
		return 0;
	case COMMAND_1472:
		script_assert(false);
		return 0;
	case COMMAND_1473:
		script_assert(false);
		return 0;
	case COMMAND_1474:
		script_assert(false);
		return 0;
	case COMMAND_1475:
		script_assert(false);
		return 0;
	case COMMAND_1476:
		script_assert(false);
		return 0;
	case COMMAND_1477:
		script_assert(false);
		return 0;
	case COMMAND_1478:
		script_assert(false);
		return 0;
	case COMMAND_1479:
		CollectParameters(&m_nIp, 2);
		// TODO (SET_CHAR_ONLY_ENTER_BACK_DOOR)
		return 0;
	case COMMAND_1480:
		script_assert(false);
		return 0;
	case COMMAND_1481:
		script_assert(false);
		return 0;
	case COMMAND_1482:
		script_assert(false);
		return 0;
	case COMMAND_1483:
		script_assert(false);
		return 0;
	case COMMAND_1484:
		script_assert(false);
		return 0;
	case COMMAND_1485:
		script_assert(false);
		return 0;
	case COMMAND_1486:
		script_assert(false);
		return 0;
	case COMMAND_1487:
		script_assert(false);
		return 0;
	case COMMAND_1488:
		script_assert(false);
		return 0;
	case COMMAND_1489:
		script_assert(false);
		return 0;
	case COMMAND_1490:
		script_assert(false);
		return 0;
	case COMMAND_1491:
		script_assert(false);
		return 0;
	case COMMAND_1492:
		script_assert(false);
		return 0;
	case COMMAND_1493:
		script_assert(false);
		return 0;
	case COMMAND_1494:
		script_assert(false);
		return 0;
	case COMMAND_1495:
		script_assert(false);
		return 0;
	case COMMAND_1496:
		script_assert(false);
		return 0;
	case COMMAND_1497:
		script_assert(false);
		return 0;
	case COMMAND_1498:
		script_assert(false);
		return 0;
	case COMMAND_1499:
		script_assert(false);
		return 0;
	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands1500To1599(int32 command)
{
	switch (command) {
	case COMMAND_1500:
		script_assert(false);
		return 0;
	case COMMAND_1501:
		script_assert(false);
		return 0;
	case COMMAND_1502:
		script_assert(false);
		return 0;
	case COMMAND_1503:
		script_assert(false);
		return 0;
	case COMMAND_1504:
		script_assert(false);
		return 0;
	case COMMAND_1505:
		script_assert(false);
		return 0;
	case COMMAND_1506:
		script_assert(false);
		return 0;
	case COMMAND_1507:
		script_assert(false);
		return 0;
	case COMMAND_1508:
		script_assert(false);
		return 0;
	case COMMAND_1509:
		script_assert(false);
		return 0;
	case COMMAND_1510:
		script_assert(false);
		return 0;
	case COMMAND_1511:
		script_assert(false);
		return 0;
	case COMMAND_1512:
		script_assert(false);
		return 0;
	case COMMAND_1513:
		script_assert(false);
		return 0;
	case COMMAND_1514:
		script_assert(false);
		return 0;
	case COMMAND_1515:
		script_assert(false);
		return 0;
	case COMMAND_1516:
		script_assert(false);
		return 0;
	case COMMAND_1517:
		script_assert(false);
		return 0;
	case COMMAND_1518:
		// TODO (?)
		UpdateCompareFlag(true);
		return 0;
	case COMMAND_1519:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_NUMBER_USJ_FOUND?)
		return 0;
	case COMMAND_1520:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_TOTAL_HIDDEN_PACKAGES?)
		return 0;
	case COMMAND_1521:
		script_assert(false);
		return 0;
	case COMMAND_1522:
		script_assert(false);
		return 0;
	case COMMAND_1523:
		script_assert(false);
		return 0;
	case COMMAND_1524:
		script_assert(false);
		return 0;
	case COMMAND_1525:
		script_assert(false);
		return 0;
	case COMMAND_1526:
		script_assert(false);
		return 0;
	case COMMAND_1527:
		script_assert(false);
		return 0;
	case COMMAND_1528:
		script_assert(false);
		return 0;
	case COMMAND_1529:
		script_assert(false);
		return 0;
	case COMMAND_1530:
		script_assert(false);
		return 0;
	case COMMAND_1531:
		script_assert(false);
		return 0;
	case COMMAND_1532:
		script_assert(false);
		return 0;
	case COMMAND_1533:
		script_assert(false);
		return 0;
	case COMMAND_1534:
		script_assert(false);
		return 0;
	case COMMAND_1535:
		script_assert(false);
		return 0;
	case COMMAND_1536:
		script_assert(false);
		return 0;
	case COMMAND_1537:
		script_assert(false);
		return 0;
	case COMMAND_1538:
		script_assert(false);
		return 0;
	case COMMAND_1539:
		//TODO (REGISTER_OUTFIT_CHANGE)
		return 0;
	case COMMAND_1540:
		script_assert(false);
		return 0;
	case COMMAND_1541:
		script_assert(false);
		return 0;
	case COMMAND_1542:
		script_assert(false);
		return 0;
	case COMMAND_1543:
		script_assert(false);
		return 0;
	case COMMAND_1544:
		script_assert(false);
		return 0;
	case COMMAND_1545:
		script_assert(false);
		return 0;
	case COMMAND_1546:
		script_assert(false);
		return 0;
	case COMMAND_1547:
		script_assert(false);
		return 0;
	case COMMAND_1548:
		// TODO (GET_ONFOOT_CAMERA_MODE)
		ScriptParams[0] = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_1549:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_ONFOOT_CAMERA_MODE?)
		return 0;
	case COMMAND_1550:
		script_assert(false);
		return 0;
	case COMMAND_1551:
		script_assert(false);
		return 0;
	case COMMAND_1552:
		script_assert(false);
		return 0;
	case COMMAND_1553:
		script_assert(false);
		return 0;
	case COMMAND_1554:
		script_assert(false);
		return 0;
	case COMMAND_1555:
		CollectParameters(&m_nIp, 1);
		// TODO (FREEZE_ONFOOT_CAMERA_MODE?)
		return 0;
	case COMMAND_1556:
		script_assert(false);
		return 0;
	case COMMAND_1557:
		script_assert(false);
		return 0;
	case COMMAND_1558:
		UpdateCompareFlag(false);
		// TODO
		return 0;
	case COMMAND_1559:
		script_assert(false);
		return 0;
	case COMMAND_1560:
		// TODO (IS_E3_BUILD?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1561:
		// TODO (check, SET_FS_DESTROYED_FLAG)
		CTheScripts::FSDestroyedFlag = GetPointerToScriptVariable(&m_nIp, VAR_GLOBAL) - (int32*)CTheScripts::ScriptSpace;
		return 0;
	case COMMAND_1562:
		script_assert(false);
		return 0;
	case COMMAND_1563:
		script_assert(false);
		return 0;
	case COMMAND_1564:
		script_assert(false);
		return 0;
	case COMMAND_1565:
		script_assert(false);
		return 0;
	case COMMAND_1566:
		script_assert(false);
		return 0;
	case COMMAND_1567:
		CollectParameters(&m_nIp, 1);
		// TODO (BUILD_WORLD_GEOMETRY)
		return 0;
	case COMMAND_1568:
		script_assert(false);
		return 0;
	case COMMAND_1569:
		// TODO (IS_MULTIPLAYER_ACTIVE?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1570:
		script_assert(false);
		return 0;
	case COMMAND_1571:
		script_assert(false);
		return 0;
	case COMMAND_1572:
		script_assert(false);
		return 0;
	case COMMAND_1573:
		script_assert(false);
		return 0;
	case COMMAND_1574:
		script_assert(false);
		return 0;
	case COMMAND_1575:
		script_assert(false);
		return 0;
	case COMMAND_1576:
		script_assert(false);
		return 0;
	case COMMAND_1577:
		script_assert(false);
		return 0;
	case COMMAND_1578:
		script_assert(false);
		return 0;
	case COMMAND_1579:
		script_assert(false);
		return 0;
	case COMMAND_1580:
		script_assert(false);
		return 0;
	case COMMAND_1581:
	{
		// TODO (SET_HELP_MESSAGE?)
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		return 0;
	}
	case COMMAND_1582:
		script_assert(false);
		return 0;
	case COMMAND_1583:
		script_assert(false);
		return 0;
	case COMMAND_1584:
		script_assert(false);
		return 0;
	case COMMAND_1585:
		script_assert(false);
		return 0;
	case COMMAND_1586:
		script_assert(false);
		return 0;
	case COMMAND_1587:
		script_assert(false);
		return 0;
	case COMMAND_1588:
		script_assert(false);
		return 0;
	case COMMAND_1589:
		CollectParameters(&m_nIp, 2);
		// TODO (SWAP_BUILDING?)
		return 0;
	case COMMAND_1590:
		script_assert(false);
		return 0;
	case COMMAND_1591:
		script_assert(false);
		return 0;
	case COMMAND_1592:
		script_assert(false);
		return 0;
	case COMMAND_1593:
		script_assert(false);
		return 0;
	case COMMAND_1594:
		script_assert(false);
		return 0;
	case COMMAND_1595:
		script_assert(false);
		return 0;
	case COMMAND_1596:
		script_assert(false);
		return 0;
	case COMMAND_1597:
		script_assert(false);
		return 0;
	case COMMAND_1598:
		script_assert(false);
		return 0;
	case COMMAND_1599:
		script_assert(false);
		return 0;
	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands1600To1699(int32 command)
{
	switch (command) {
	case COMMAND_1600:
		script_assert(false);
		return 0;
	case COMMAND_1601:
		script_assert(false);
		return 0;
	case COMMAND_1602:
		script_assert(false);
		return 0;
	case COMMAND_1603:
		script_assert(false);
		return 0;
	case COMMAND_1604:
		script_assert(false);
		return 0;
	case COMMAND_1605:
		script_assert(false);
		return 0;
	case COMMAND_1606:
		script_assert(false);
		return 0;
	case COMMAND_1607:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_TOTAL_CARS_FOR_EXPORT)
		return 0;
	case COMMAND_1608:
		script_assert(false);
		return 0;
	case COMMAND_1609:
		script_assert(false);
		return 0;
	case COMMAND_1610:
		script_assert(false);
		return 0;
	case COMMAND_1611:
		script_assert(false);
		return 0;
	case COMMAND_1612:
		script_assert(false);
		return 0;
	case COMMAND_1613:
		script_assert(false);
		return 0;
	case COMMAND_1614:
		script_assert(false);
		return 0;
	case COMMAND_1615:
		// TODO (GET_DEVELOPER_FLAG?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1616:
		// TODO (SET_DEVELOPER_FLAG)
		return 0;
	case COMMAND_1617:
		script_assert(false);
		return 0;
	case COMMAND_1618:
		script_assert(false);
		return 0;
	case COMMAND_1619:
		script_assert(false);
		return 0;
	case COMMAND_1620:
		script_assert(false);
		return 0;
	case COMMAND_1621:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		// TODO (SET_SUBTITLE_TEXT)
		return 0;
	}
	case COMMAND_1622:
		script_assert(false);
		return 0;
	case COMMAND_1623:
		script_assert(false);
		return 0;
	case COMMAND_1624:
		script_assert(false);
		return 0;
	case COMMAND_1625:
		script_assert(false);
		return 0;
	case COMMAND_1626:
		script_assert(false);
		return 0;
	case COMMAND_1627:
		script_assert(false);
		return 0;
	case COMMAND_1628:
		script_assert(false);
		return 0;
	case COMMAND_1629:
		script_assert(false);
		return 0;
	case COMMAND_1630:
		script_assert(false);
		return 0;
	case COMMAND_1631:
		script_assert(false);
		return 0;
	case COMMAND_1632:
		script_assert(false);
		return 0;
	case COMMAND_1633:
		script_assert(false);
		return 0;
	case COMMAND_1634:
		script_assert(false);
		return 0;
	case COMMAND_1635:
	{
		char tmp[12]; // TODO
		CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		// TODO (CHANGE_STORED_PLAYER_OUTFIT?)
		return 0;
	}
	case COMMAND_1636:
		script_assert(false);
		return 0;
	case COMMAND_1637:
		script_assert(false);
		return 0;
	case COMMAND_1638:
		script_assert(false);
		return 0;
	case COMMAND_1639:
		script_assert(false);
		return 0;
	case COMMAND_1640:
		CollectParameters(&m_nIp, 2);
		// TODO (LOCK_GARAGE?)
		return 0;
	case COMMAND_1641:
		// TODO
		UpdateCompareFlag(true);
		return 0;
	case COMMAND_1642:
		script_assert(false);
		return 0;
	case COMMAND_1643:
		script_assert(false);
		return 0;
	case COMMAND_1644:
		script_assert(false);
		return 0;
	case COMMAND_1645:
	{
		CollectParameters(&m_nIp, 1);
		// TODO (GET_STORED_WEAPON?)
		CPed* pPed = CWorld::Players[ScriptParams[0]].m_pPed;
		script_assert(pPed);
		ScriptParams[0] = pPed->m_storedWeapon;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_1646:
		CollectParameters(&m_nIp, 1);
		// TODO (DISABLE_PAUSE_MENU?)
		return 0;
	case COMMAND_1647:
		CollectParameters(&m_nIp, 1);
		// TODO (IS_CHANNEL_PLAYING?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1648:
		CollectParameters(&m_nIp, 3);
		// TODO (SET_CLOCK_EVENT_WARNING);
		return 0;
	case COMMAND_1649:
		CollectParameters(&m_nIp, 3);
		// TODO (SET_EXTRA_COLOUR_DIRECTION)
		return 0;
	case COMMAND_1650:
		script_assert(false);
		return 0;
	case COMMAND_1651:
		script_assert(false);
		return 0;
	case COMMAND_1652:
		script_assert(false);
		return 0;
	case COMMAND_1653:
		script_assert(false);
		return 0;
	case COMMAND_1654:
		script_assert(false);
		return 0;
	case COMMAND_1655:
		script_assert(false);
		return 0;
	case COMMAND_1656:
		CollectParameters(&m_nIp, 2);
		// TODO (?)
		return 0;
	default:
		script_assert(0);
	}
	return -1;
}
