#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "DMAudio.h"
#include "GameLogic.h"
#include "Garages.h"
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
		break;
	case COMMAND_WANTED_STARS_ARE_FLASHING:
	{
		CWanted *pWanted = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pWanted;
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
		DMAudio.PlayRadioAnnouncement(ScriptParams[0] + STREAMED_SOUND_ANNOUNCE_BRIDGE_CLOSED);
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
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CVector pos = pPlayerInfo->GetPos();
		CZone *infoZone = CTheZones::FindInformationZoneForPosition(&pos);
		UpdateCompareFlag(strncmp(key, infoZone->name, 8) == 0);
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
				CTheScripts::MissionCleanup.AddEntityToList(ped_handle, CLEANUP_CHAR);
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
		CObject *pHeli = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
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
	default:
		script_assert(0);
	}
	return -1;
}
