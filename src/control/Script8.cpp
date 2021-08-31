#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "Bike.h"
#include "DMAudio.h"
#ifdef MORE_LANGUAGES
#include "Frontend.h"
#endif
#include "GameLogic.h"
#include "Garages.h"
#ifdef MISSION_REPLAY
#include "GenericGameStorage.h"
#endif
#include "Hud.h"
#include "Pad.h"
#include "PedAttractor.h"
#include "Pickups.h"
#include "Population.h"
#include "Pools.h"
#include "RpAnimBlend.h"
#include "Stats.h"
#include "VisibilityPlugins.h"
#include "Wanted.h"
#include "WaterLevel.h"
#include "World.h"
#include "Zones.h"

// LCS: file done except TODOs (also check commented out strings)

int8 CRunningScript::ProcessCommands1400To1499(int32 command)
{
	switch (command) {
	case COMMAND_REGISTER_VIGILANTE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelVigilanteMission(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_CLEAR_ALL_CHAR_ANIMS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		if (pPed && pPed->GetPedState() != PED_DRIVING && pPed->GetPedState() != PED_AIM_GUN) {
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
			CAnimManager::AddAnimation(pPed->GetClump(), pPed->m_animGroup, ANIM_STD_IDLE);
			pPed->bIsPedDieAnimPlaying = false;
		}
		return 0;
	}
	case COMMAND_SET_MAXIMUM_NUMBER_OF_CARS_IN_GARAGE:
		CollectParameters(&m_nIp, 2);
		CGarages::SetMaxNumStoredCarsForGarage(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_WANTED_STARS_ARE_FLASHING:
	{
		CWanted* pWanted = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pWanted;
		UpdateCompareFlag(pWanted->m_nMinWantedLevel - pWanted->GetWantedLevel() > 0);
		return 0;
	}
	case COMMAND_SET_ALLOW_HURRICANES:
		CollectParameters(&m_nIp, 1);
		CStats::NoMoreHurricanes = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_PLAY_ANNOUNCEMENT:
	{
		CollectParameters(&m_nIp, 1);
		DMAudio.PlayRadioAnnouncement(GET_INTEGER_PARAM(0) + STREAMED_SOUND_NEWS_A);
		return 0;
	}
	case COMMAND_SET_PLAYER_IS_IN_STADIUM:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::bPlayerIsInTheStatium = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_GET_BUS_FARES_COLLECTED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
		SET_INTEGER_PARAM(0, pPlayerInfo->m_pPed->m_nLastBusFareCollected);
		pPlayerInfo->m_pPed->m_nLastBusFareCollected = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, 0);
		if (pPed->m_objective == OBJECTIVE_NONE && !pPed->bHasAlreadyUsedAttractor) {
			C2dEffect* pEffect = (C2dEffect*)GetPedAttractorManager()->GetEffectForIceCreamVan(pVehicle, pPed->GetPosition()); // has to be casted, because inner methods are const
			if (pEffect) {
				CVector pos;
				CPedAttractorManager::ComputeEffectPos(pEffect, pVehicle->GetMatrix(), pos);
				if ((pPed->GetPosition() - pos).MagnitudeSqr() < SQR(20.0f)) {
					if (GetPedAttractorManager()->HasEmptySlot(pEffect) && GetPedAttractorManager()->IsApproachable(pEffect, pVehicle->GetMatrix(), 0, pPed)) {
						if (GetPedAttractorManager()->RegisterPedWithAttractor(pPed, pEffect, pVehicle->GetMatrix()))
							SET_INTEGER_PARAM(0, 1);
					}
				}
			}
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISPLAY_RADAR:
		CollectParameters(&m_nIp, 1);
		CHud::m_HideRadar = GET_INTEGER_PARAM(0) == 0;
		// on PS2 two flags are set, on mobile none
		return 0;
	case COMMAND_REGISTER_BEST_POSITION:
		CollectParameters(&m_nIp, 2);
		CStats::RegisterBestPosition(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_IS_PLAYER_IN_INFO_ZONE:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[GET_INTEGER_PARAM(0)];
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
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
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
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bHasAlreadyUsedAttractor);
		return 0;
	}
	case COMMAND_SET_LOAD_COLLISION_FOR_CAR_FLAG:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		if (GET_INTEGER_PARAM(1)) {
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
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
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
		CWeapon::AddGunFlashBigGuns(GET_VECTOR_PARAM(0), GET_VECTOR_PARAM(3));
		return 0;
	}
	case COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bBoughtIceCream);
		return 0;
	}
	case COMMAND_GET_PROGRESS_PERCENTAGE:
		SET_FLOAT_PARAM(0, CStats::GetPercentageProgress());
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_SHORTCUT_PICKUP_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutPointAfterDeath(GET_VECTOR_PARAM(0), GET_FLOAT_PARAM(3));
		return 0;
	}
	case COMMAND_SET_SHORTCUT_DROPOFF_POINT_FOR_MISSION:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutDropOffPointForMission(GET_VECTOR_PARAM(0), GET_FLOAT_PARAM(3));
		return 0;
	}
	case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_AREA:
	{
		CollectParameters(&m_nIp, 7);
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
			if (!ThisIsAValidRandomPed(pPed->m_nPedType, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6)))
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
		SET_INTEGER_PARAM(0, ped_handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	//case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_ZONE:
	case COMMAND_UNLOCK_ALL_CAR_DOORS_IN_AREA:
	{
		CollectParameters(&m_nIp, 4);
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(3);
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
		CGangs::SetWillAttackPlayerWithCops((ePedType)((int)PEDTYPE_GANG1 + GET_INTEGER_PARAM(0)), !!GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bHeldHostageInCar = GET_INTEGER_PARAM(1);
		pPed->b1A4_2 = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_VEHICLE_TO_FADE_IN:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVisibilityPlugins::SetClumpAlpha(pVehicle->GetClump(), GET_INTEGER_PARAM(1));
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
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle && pPed->m_pMyVehicle == CGameLogic::pShortCutTaxi);
		return 0;
	}
	case COMMAND_IS_CHAR_DUCKING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(RpAnimBlendClumpGetAssociation(pPed->GetClump(), ANIM_STD_DUCK_DOWN) != nil);
		return 0;
	}
	case COMMAND_CREATE_DUST_EFFECT_FOR_CUTSCENE_HELI:
	{
		CollectParameters(&m_nIp, 3);
		CObject* pHeli = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		bool found = false;
		float waterLevel = -1000.0f;
		CVector pos = pHeli->GetPosition();
		float radius = GET_FLOAT_PARAM(1);
		float ground = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &found);
		if (!CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &waterLevel, false))
			waterLevel = 0.0f;
		if (waterLevel > ground)
			ground = waterLevel;
		if (GET_INTEGER_PARAM(2) > 8)
			SET_INTEGER_PARAM(2, 8);
		CVehicle::HeliDustGenerate(pHeli, (pos.z - ground - 1.0f - radius) * 0.3 + radius, ground, GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_REGISTER_FIRE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelFireMission(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_IS_AUSTRALIAN_GAME:
		UpdateCompareFlag(false); // should we make some check?
		return 0;
	case COMMAND_DISARM_CAR_BOMB:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (pVehicle->IsCar()) {
			if (((CAutomobile*)pVehicle)->m_bombType != CARBOMB_NONE) {
				((CAutomobile*)pVehicle)->m_bombType = CARBOMB_NONE;
				((CAutomobile*)pVehicle)->m_pBombRigger = nil;
			}
		}
#ifdef FIX_BUGS
		else if (pVehicle->IsBike()) {
			if (((CBike*)pVehicle)->m_bombType != CARBOMB_NONE) {
				((CBike*)pVehicle)->m_bombType = CARBOMB_NONE;
				((CBike*)pVehicle)->m_pBombRigger = nil;
			}
		}
#endif
		return 0;
	}
	case COMMAND_IS_JAPANESE_GAME:
#ifdef MORE_LANGUAGES
		UpdateCompareFlag(FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_JAPANESE);
#elif (defined GTAVC_JP_PATCH)
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
	case COMMAND_1442:
		CollectParameters(&m_nIp, 4);
		return 0;
	//case COMMAND_1443:
	case COMMAND_GET_DISTANCE_BETWEEN_2D_POINTS:
	{
		CollectParameters(&m_nIp, 4);
		float X1 = GET_FLOAT_PARAM(0);
		float Y1 = GET_FLOAT_PARAM(1);
		float X2 = GET_FLOAT_PARAM(2);
		float Y2 = GET_FLOAT_PARAM(3);
		float fDistance = Sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
		SET_FLOAT_PARAM(0, fDistance);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_DISTANCE_BETWEEN_3D_POINTS:
	{
		CollectParameters(&m_nIp, 6);
		float X1 = GET_FLOAT_PARAM(0);
		float Y1 = GET_FLOAT_PARAM(1);
		float Z1 = GET_FLOAT_PARAM(2);
		float X2 = GET_FLOAT_PARAM(3);
		float Y2 = GET_FLOAT_PARAM(4);
		float Z2 = GET_FLOAT_PARAM(5);
		float fDistance = Sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2) + (Z1 - Z2) * (Z1 - Z2));
		SET_FLOAT_PARAM(0, fDistance);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DOT_PRODUCT_2D:
	{
		CollectParameters(&m_nIp, 4);
		float X1 = GET_FLOAT_PARAM(0);
		float Y1 = GET_FLOAT_PARAM(1);
		float X2 = GET_FLOAT_PARAM(2);
		float Y2 = GET_FLOAT_PARAM(3);
		float fDistance = X1 * X2 + Y1 * Y2;
		SET_FLOAT_PARAM(0, fDistance);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DOT_PRODUCT_3D:
	{
		CollectParameters(&m_nIp, 6);
		float X1 = GET_FLOAT_PARAM(0);
		float Y1 = GET_FLOAT_PARAM(1);
		float Z1 = GET_FLOAT_PARAM(2);
		float X2 = GET_FLOAT_PARAM(3);
		float Y2 = GET_FLOAT_PARAM(4);
		float Z2 = GET_FLOAT_PARAM(5);
		float fDistance = X1 * X2 + Y1 * Y2 + Z1 * Z2;
		SET_FLOAT_PARAM(0, fDistance);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DEBUG_PRINT_WITH_1_FLOAT:
		return 0;
	case COMMAND_DEBUG_PRINT_WITH_2_FLOATS:
		return 0;
	case COMMAND_DEBUG_PRINT_WITH_3_FLOATS:
		return 0;
	case COMMAND_GET_PAD_BUTTON_STATE:
	{
		CollectParameters(&m_nIp, 1);
		switch (GET_INTEGER_PARAM(0)) {
		case 0: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetOddJobTrigger()); break;
		case 1: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetBrake()); break;
		case 2: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSteeringLeftRight()); break;
		case 3: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSteeringUpDown()); break;
		case 4: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetCarGunLeftRight()); break;
		case 5: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetCarGunUpDown()); break;
		case 6: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetPedWalkLeftRight()); break;
		case 7: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetPedWalkUpDown()); break;
		case 8: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookLeft()); break;
		case 9: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookRight()); break;
		case 10: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookBehindForCar()); break;
		case 11: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetLookBehindForPed()); break;
		case 12: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetHorn()); break;
		case 13: SET_INTEGER_PARAM(0, CPad::GetPad(0)->HornJustDown()); break;
		case 14: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetCarGunFired()); break;
		case 15: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CarGunJustDown()); break;
		case 16: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetHandBrake()); break;
		case 17: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetBrake()); break;
		case 18: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetExitVehicle()); break;
		case 19: SET_INTEGER_PARAM(0, CPad::GetPad(0)->ExitVehicleJustDown()); break;
		case 20: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetWeapon()); break;
		case 21: SET_INTEGER_PARAM(0, CPad::GetPad(0)->WeaponJustDown()); break;
		case 22: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetAccelerate()); break;
		case 23: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CycleCameraModeUpJustDown()); break;
		case 24: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CycleWeaponLeftJustDown()); break;
		case 25: SET_INTEGER_PARAM(0, CPad::GetPad(0)->CycleWeaponRightJustDown()); break;
		case 26: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetTarget()); break;
		case 27: SET_INTEGER_PARAM(0, CPad::GetPad(0)->TargetJustDown()); break;
		case 28: SET_INTEGER_PARAM(0, CPad::GetPad(0)->JumpJustDown()); break;
		case 29: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSprint()); break;
		case 30: SET_INTEGER_PARAM(0, CPad::GetPad(0)->ShiftTargetLeftJustDown()); break;
		case 31: SET_INTEGER_PARAM(0, CPad::GetPad(0)->ForceCameraBehindPlayer()); break;
		case 32: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperZoomIn()); break;
		case 33: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperZoomOut()); break;
		case 34: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperModeLookLeftRight()); break;
		case 35: SET_INTEGER_PARAM(0, CPad::GetPad(0)->SniperModeLookUpDown()); break;
		case 36: SET_INTEGER_PARAM(0, CPad::GetPad(0)->LookAroundLeftRight()); break;
		case 37: SET_INTEGER_PARAM(0, CPad::GetPad(0)->LookAroundUpDown()); break;
		case 38: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiLeft()); break;
		case 39: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiRight()); break;
		case 40: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiUp()); break;
		case 41: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiDown()); break;
		case 42: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiSelect()); break;
		case 43: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GuiBack()); break;
		case 44: SET_INTEGER_PARAM(0, CPad::GetPad(0)->GetSkipCutscene()); if (GET_INTEGER_PARAM(0)) TheCamera.m_bIgnoreFadingStuffForMusic = false; break; // spectacular hack
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_NAVIGATION_ARROW:
	{
		CollectParameters(&m_nIp, 3);
		// cNavArrow::SetTarget(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(0)); // TODO, although it's unused
		return 0;
	}
	case COMMAND_CLEAR_NAVIGATION_ARROW:
	{
		// cNavArrow::ClearTarget(); // TODO, although it's unused
		return 0;
	}
	case COMMAND_CALL:
	case COMMAND_CALLNOT:
	{
		m_anStack[m_nStackPointer++] = m_nIp | BIT(STACKVALUE_IS_FUNCTION_CALL_BIT) | ((command == COMMAND_CALLNOT) ? BIT(STACKVALUE_INVERT_RETURN_BIT) : 0);
		uint8 nInputParams = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint8 nOutputParameters = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint8 nLocalsOffset = CTheScripts::Read1ByteFromScript(&m_nIp);
		uint32 nIPBeforeParameters = m_nIp;
		CollectParameters(&m_nIp, 1);
		if (nInputParams)
			CollectParameters(&m_nIp, nInputParams, &m_anLocalVariables[m_nLocalsPointer + nLocalsOffset]);
		m_nLocalsPointer += nLocalsOffset;
		m_anStack[m_nStackPointer - 1] |= (m_nIp - nIPBeforeParameters) << STACKVALUE_IP_PARAMS_OFFSET;
		if (GET_INTEGER_PARAM(0) < 0)
			m_nIp = CTheScripts::MainScriptSize - GET_INTEGER_PARAM(0);
		else
			m_nIp = GET_INTEGER_PARAM(0);
		return 0;
	}
	case COMMAND_IS_CAR_AUTOMOBILE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_FIRST_VEHICLE && pVehicle->GetModelIndex() < MI_FERRY);
		return 0;
	}
	case COMMAND_IS_CAR_BIKE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_ANGEL && pVehicle->GetModelIndex() <= MI_SANCHEZ);
		return 0;
	}
		return 0;
	case COMMAND_IS_CAR_PLANE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_AIRTRAIN && pVehicle->GetModelIndex() <= MI_DEADDODO);
		return 0;
	}
	case COMMAND_IS_CAR_HELI:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetModelIndex() >= MI_ESCAPE && pVehicle->GetModelIndex() <= MI_CHOPPER);
		return 0;
	}
#ifdef FIX_BUGS
	case COMMAND_1476: // they DO have it in script
		return 0;
#endif
	case COMMAND_RETURN_IF_TRUE:
		if (m_bCondResult) {
			ReturnFromGosubOrFunction();
		}
		return 0;
	case COMMAND_RETURN_TRUE_IF_TRUE:
		if (m_bCondResult) {
			UpdateCompareFlag(false);
			ReturnFromGosubOrFunction();
		}
		return 0;
	case COMMAND_SET_CHAR_ONLY_ALLOWED_TO_SIT_BEHIND:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOnlyAllowedToSitBehind = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_RC_HELI_HEIGHT_LIMIT:
		CollectParameters(&m_nIp, 1);
		CVehicle::rcHeliHeightLimit = GET_FLOAT_PARAM(0);
		return 0;
	case COMMAND_CREATE_SCRIPT_CORONA:
	{
		CollectParameters(&m_nIp, 9);
		base::cSList<script_corona>::tSItem* pCorona = new base::cSList<script_corona>::tSItem();
		pCorona->item.x = GET_FLOAT_PARAM(0);
		pCorona->item.y = GET_FLOAT_PARAM(1);
		pCorona->item.z = GET_FLOAT_PARAM(2);
		pCorona->item.id = CTheScripts::NextScriptCoronaID++;
		if (pCorona->item.z <= MAP_Z_LOW_LIMIT)
			pCorona->item.z = CWorld::FindGroundZForCoord(pCorona->item.x, pCorona->item.y);
		pCorona->item.size = GET_FLOAT_PARAM(3);
		pCorona->item.r = GET_INTEGER_PARAM(6);
		pCorona->item.g = GET_INTEGER_PARAM(7);
		pCorona->item.b = GET_INTEGER_PARAM(8);
		pCorona->item.type = GET_INTEGER_PARAM(4);
		pCorona->item.flareType = GET_INTEGER_PARAM(5);
		SET_INTEGER_PARAM(0, pCorona->item.id);
		CTheScripts::mCoronas.Insert(pCorona);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_REMOVE_SCRIPT_CORONA:
	{
		CollectParameters(&m_nIp, 1);
		for (base::cSList<script_corona>::tSItem* i = CTheScripts::mCoronas.first; i; i = i->next) {
			if (i->item.id == GET_INTEGER_PARAM(0)) {
				CTheScripts::mCoronas.Remove(i);
				delete i;
				break;
			}
		}
		return 0;
	}
	case COMMAND_IS_BOAT_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CBoat* pVehicle = (CBoat*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle && pVehicle->IsBoat());
		UpdateCompareFlag(pVehicle->bBoatInWater);
		return 0;
	}
	case COMMAND_IS_CAR_DRIVER_BEING_JACKED:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->bIsBeingCarJacked);
		return 0;
	}
	case COMMAND_SET_CHAR_ONLY_ALLOWED_TO_SIT_IN_FRONT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOnlyAllowedToSitInFront = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_SET_CAR_TILTED_BY_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pVehicle);
		pVehicle->ApplyTurnForce(0.0f, 0.0f, CGeneral::GetRandomNumberInRange(-0.8f, -1.2f)* pPed->m_fMass,
			pPed->GetPosition().x - pVehicle->GetPosition().x, pPed->GetPosition().y - pVehicle->GetPosition().y, 0.0f);
		DMAudio.PlayOneShot(pVehicle->m_audioEntityId, SOUND_CAR_JERK, 0.0f);
		return 0;
	}
	case COMMAND_GET_WEAPON_TYPE_FOR_PICKUP_IN_AREA:
	{
		CollectParameters(&m_nIp, 4);
		float X = GET_FLOAT_PARAM(0);
		float Y = GET_FLOAT_PARAM(1);
		float Z = GET_FLOAT_PARAM(2);
		float radius = GET_FLOAT_PARAM(3);
		int model = -1;
		bool found = false;
		for (uint32 i = 0; i < NUMPICKUPS; i++) {
			CPickup* pPickup = &CPickups::aPickUps[i];
			if (pPickup->m_eType != PICKUP_NONE) {
				CVector fDist = pPickup->m_vecPos - CVector(X, Y, Z);
#ifndef FIX_BUGS // this breaks ALL pickups!
				pPickup->m_eModelIndex = 4;
#endif
				if (fDist.Magnitude() < radius && pPickup->m_pObject) {
					found = true;
					model = CPickups::WeaponForModel(pPickup->m_pObject->GetModelIndex());
				}
			}
		}
		SET_INTEGER_PARAM(0, model);
		StoreParameters(&m_nIp, 1);
	}
	case COMMAND_IS_PLAYER_USING_FIRST_PERSON_WEAPON_CAMERA:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(TheCamera.Using1stPersonWeaponMode());
		return 0;
	//case COMMAND_1489:
	//case COMMAND_1490:
	//case COMMAND_1491:
	case COMMAND_SET_DEBUG_MENU_ACTIVE:
		CollectParameters(&m_nIp, 1);
		// this sets two values on PS2 and PSP, but not on mobile - TODO?
		return 0;
	case COMMAND_SET_DRAW_HUD:
		CollectParameters(&m_nIp, 1);
		CHud::m_Wants_To_Draw_Hud = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	case COMMAND_GET_RANDOM_CHAR_IN_AREA_NO_CHECKS:
	{
		CollectParameters(&m_nIp, 4);
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
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->m_nWaitState != WAITSTATE_FALSE)
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
		SET_INTEGER_PARAM(0, ped_handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_RANDOM_CAR_IN_AREA_NO_CHECKS_NO_SAVE:
	{
		CollectParameters(&m_nIp, 4);
		int handle = -1;
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(3);
		while (i-- && handle == -1) {
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
			if (!pVehicle)
				continue;
			if (!pVehicle->IsWithinArea(infX, infY, supX, supY))
				continue;
			handle = CPools::GetVehiclePool()->GetIndex(pVehicle);
		}
		SET_INTEGER_PARAM(0, handle);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_STORE_CAR_COLLIDED_WITH_NO_SAVE:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (!pVehicle)
			printf("STORE_CAR_COLLIDED_WITH_NO_SAVE - Car doesn\'t exist\n");
		else {
			if (pVehicle->m_pLastDamageEntity == nil)
				SET_INTEGER_PARAM(0, -1);
			else {
				// what they are doing is not very safe as m_pLastDamageEntity doesn't have to be CVehicle
#ifdef FIX_BUGS
				if (!pVehicle->m_pLastDamageEntity->IsVehicle()) {
					SET_INTEGER_PARAM(0, -1);
				}
				else
#endif
				{
					SET_INTEGER_PARAM(0, CPools::GetVehiclePool()->GetIndex((CVehicle*)pVehicle->m_pLastDamageEntity));
					pVehicle->m_pLastDamageEntity = nil;
				}
			}
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}
