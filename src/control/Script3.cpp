#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "Boat.h"
#include "CarCtrl.h"
#include "Clock.h"
#include "ColStore.h"
#include "Coronas.h"
#include "Cranes.h"
#include "CutsceneMgr.h"
#include "Darkel.h"
#include "Explosion.h"
#include "Fire.h"
#include "General.h"
#include "Garages.h"
#include "Heli.h"
#include "Messages.h"
#include "Pad.h"
#include "ParticleObject.h"
#include "Phones.h"
#include "Pickups.h"
#include "PointLights.h"
#include "Population.h"
#include "Pools.h"
#include "ProjectileInfo.h"
#include "Radar.h"
#include "Restart.h"
#include "Stats.h"
#include "Streaming.h"
#include "User.h"
#include "WaterLevel.h"
#include "Weather.h"
#include "Zones.h"
#include "GameLogic.h"
#include "Bike.h"
#include "Wanted.h"

// LCS: file done except TODOs

int8 CRunningScript::ProcessCommands500To599(int32 command)
{
	switch (command) {
	case COMMAND_IS_CAR_UPSIDEDOWN:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetUp().z <= UPSIDEDOWN_UP_THRESHOLD);
		return 0;
	}
	case COMMAND_GET_PLAYER_CHAR:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		SET_INTEGER_PARAM(0, CPools::GetPedPool()->GetIndex(pPed));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_CANCEL_OVERRIDE_RESTART:
		CRestart::CancelOverrideRestart();
		return 0;
	case COMMAND_SET_POLICE_IGNORE_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->m_pWanted->m_bIgnoredByCops = true;
			CWorld::StopAllLawEnforcersInTheirTracks();
		}
		else {
			pPed->m_pWanted->m_bIgnoredByCops = false;
		}
		return 0;
	}
	/*
	case COMMAND_ADD_PAGER_MESSAGE_WITH_NUMBER:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CUserDisplay::Pager.AddMessageWithNumber(text, GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1,
			GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3));
		return 0;
	}
	*/
	case COMMAND_START_KILL_FRENZY:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 8);
		CDarkel::StartFrenzy((eWeaponType)GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2),
			GET_INTEGER_PARAM(3), text, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5),
			GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7) != 0, false);
		return 0;
	}
	case COMMAND_READ_KILL_FRENZY_STATUS:
	{
		SET_INTEGER_PARAM(0, CDarkel::ReadStatus());
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SQRT:
	{
		CollectParameters(&m_nIp, 1);
		SET_FLOAT_PARAM(0, Sqrt(GET_FLOAT_PARAM(0)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_LOCATE_PLAYER_ANY_MEANS_CAR_2D:
	case COMMAND_LOCATE_PLAYER_ON_FOOT_CAR_2D:
	case COMMAND_LOCATE_PLAYER_IN_CAR_CAR_2D:
	case COMMAND_LOCATE_PLAYER_ANY_MEANS_CAR_3D:
	case COMMAND_LOCATE_PLAYER_ON_FOOT_CAR_3D:
	case COMMAND_LOCATE_PLAYER_IN_CAR_CAR_3D:
		LocatePlayerCarCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_2D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_2D:
	case COMMAND_LOCATE_CHAR_IN_CAR_CAR_2D:
	case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_3D:
	case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_3D:
	case COMMAND_LOCATE_CHAR_IN_CAR_CAR_3D:
		LocateCharCarCommand(command, &m_nIp);
		return 0;
	case COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE:
		CollectParameters(&m_nIp, 2);
		SET_FLOAT_PARAM(0, CGeneral::GetRandomNumberInRange(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_GENERATE_RANDOM_INT_IN_RANGE:
		CollectParameters(&m_nIp, 2);
		SET_INTEGER_PARAM(0, CGeneral::GetRandomNumberInRange(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_LOCK_CAR_DOORS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_nDoorLock = (eCarLock)GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_EXPLODE_CAR:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bCanBeDamaged = true;
		pVehicle->BlowUpCar(nil);
		return 0;
	}
	case COMMAND_ADD_EXPLOSION:
		CollectParameters(&m_nIp, 4);
		CExplosion::AddExplosion(nil, nil, (eExplosionType)GET_INTEGER_PARAM(3), GET_VECTOR_PARAM(0), 0, true); // last argument is 0 (default? - TODO)
		return 0;

	case COMMAND_IS_CAR_UPRIGHT:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetUp().z >= 0.0f);
		return 0;
	}
	case COMMAND_TURN_CHAR_TO_FACE_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CVehicle* pVehicle = pSourcePed->bInVehicle ? pSourcePed->m_pMyVehicle : nil;
		CVector2D sourcePos = pSourcePed->bInVehicle ? pVehicle->GetPosition() : pSourcePed->GetPosition();
		CVector2D targetPos = pTargetPed->bInVehicle ? pTargetPed->m_pMyVehicle->GetPosition() : pTargetPed->GetPosition();
		float angle = CGeneral::GetATanOfXY(sourcePos.x - targetPos.x, sourcePos.y - targetPos.y) + HALFPI;
		if (angle > TWOPI)
			angle -= TWOPI;
		if (!pVehicle) {
			pSourcePed->m_fRotationCur = angle;
			pSourcePed->m_fRotationDest = angle;
			pSourcePed->SetHeading(angle);
		}
		return 0;
	}
	case COMMAND_TURN_CHAR_TO_FACE_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pTargetPed = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		CVehicle* pVehicle = pSourcePed->bInVehicle ? pSourcePed->m_pMyVehicle : nil;
		CVector2D sourcePos = pSourcePed->bInVehicle ? pVehicle->GetPosition() : pSourcePed->GetPosition();
		CVector2D targetPos = pTargetPed->bInVehicle ? pTargetPed->m_pMyVehicle->GetPosition() : pTargetPed->GetPosition();
		float angle = CGeneral::GetATanOfXY(sourcePos.x - targetPos.x, sourcePos.y - targetPos.y) + HALFPI;
		if (angle > TWOPI)
			angle -= TWOPI;
		if (!pVehicle) {
			pSourcePed->m_fRotationCur = angle;
			pSourcePed->m_fRotationDest = angle;
			pSourcePed->SetHeading(angle);
		}
		return 0;
	}
	case COMMAND_TURN_PLAYER_TO_FACE_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CVehicle* pVehicle = pSourcePed->bInVehicle ? pSourcePed->m_pMyVehicle : nil;
		CVector2D sourcePos = pSourcePed->bInVehicle ? pVehicle->GetPosition() : pSourcePed->GetPosition();
		CVector2D targetPos = pTargetPed->bInVehicle ? pTargetPed->m_pMyVehicle->GetPosition() : pTargetPed->GetPosition();
		float angle = CGeneral::GetATanOfXY(sourcePos.x - targetPos.x, sourcePos.y - targetPos.y) + HALFPI;
		if (angle > TWOPI)
			angle -= TWOPI;
		if (!pVehicle) {
			pSourcePed->m_fRotationCur = angle;
			pSourcePed->m_fRotationDest = angle;
			pSourcePed->SetHeading(angle);
		}
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_GOTO_COORD_ON_FOOT:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector target;
		target.x = GET_FLOAT_PARAM(1);
		target.y = GET_FLOAT_PARAM(2);
		target.z = CWorld::FindGroundZForCoord(target.x, target.y);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GOTO_AREA_ON_FOOT, target);
		return 0;
	}
	//case COMMAND_SET_CHAR_OBJ_GOTO_COORD_IN_CAR:
	case COMMAND_CREATE_PICKUP:
	{
		CollectParameters(&m_nIp, 5);
		int16 model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		CVector pos = GET_VECTOR_PARAM(2);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GetActualPickupIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CPickups::GenerateNewOne(pos, model, GET_INTEGER_PARAM(1), 0));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_HAS_PICKUP_BEEN_COLLECTED:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CPickups::IsPickUpPickedUp(GET_INTEGER_PARAM(0)) != 0);
		return 0;
	case COMMAND_REMOVE_PICKUP:
		CollectParameters(&m_nIp, 1);
		CPickups::RemovePickUp(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_SET_TAXI_LIGHTS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		((CAutomobile*)pVehicle)->SetTaxiLight(GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_PRINT_BIG_Q:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		CMessages::AddBigMessageQ(text, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1) - 1);
		return 0;
	}
	case COMMAND_PRINT_WITH_NUMBER_BIG_Q:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 3);
		CMessages::AddBigMessageWithNumberQ(text, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2) - 1,
			GET_INTEGER_PARAM(0), -1, -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_SET_GARAGE:
	{
		CollectParameters(&m_nIp, 9);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float X2 = GET_FLOAT_PARAM(3);
		float Y2 = GET_FLOAT_PARAM(4);
		float supX = GET_FLOAT_PARAM(5);
		float supY = GET_FLOAT_PARAM(6);
		float supZ = GET_FLOAT_PARAM(7);
		SET_INTEGER_PARAM(0, CGarages::AddOne(infX, infY, infZ, X2, Y2, supX, supY, supZ, GET_INTEGER_PARAM(8), 0));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	/*
	case COMMAND_SET_GARAGE_WITH_CAR_MODEL:
	{
		CollectParameters(&m_nIp, 10);
		float infX = GET_FLOAT_PARAM(0);
		float infY = GET_FLOAT_PARAM(1);
		float infZ = GET_FLOAT_PARAM(2);
		float X2 = GET_FLOAT_PARAM(3);
		float Y2 = GET_FLOAT_PARAM(4);
		float supX = GET_FLOAT_PARAM(5);
		float supY = GET_FLOAT_PARAM(6);
		float supZ = GET_FLOAT_PARAM(7);
		SET_INTEGER_PARAM(0, CGarages::AddOne(infX, infY, infZ, X2, Y2, supX, supY, supZ, GET_INTEGER_PARAM(8), GET_INTEGER_PARAM(9)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	*/
	case COMMAND_SET_TARGET_CAR_FOR_MISSION_GARAGE:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pTarget;
		if (GET_INTEGER_PARAM(1) >= 0) {
			pTarget = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		}
		else {
			pTarget = nil;
		}
		CGarages::SetTargetCarForMissonGarage(GET_INTEGER_PARAM(0), pTarget);
		return 0;
	}
	case COMMAND_IS_CAR_IN_MISSION_GARAGE:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CGarages::HasCarBeenDroppedOffYet(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_SET_FREE_BOMBS:
		CollectParameters(&m_nIp, 1);
		CGarages::SetFreeBombs(GET_INTEGER_PARAM(0) != 0);
		return 0;
	/*
	case COMMAND_SET_POWERPOINT:
	{
		CollectParameters(&m_nIp, 7);
		float f1 = GET_FLOAT_PARAM(0);
		float f2 = GET_FLOAT_PARAM(1);
		float f3 = GET_FLOAT_PARAM(2);
		float f4 = GET_FLOAT_PARAM(3);
		float f5 = GET_FLOAT_PARAM(4);
		float f6 = GET_FLOAT_PARAM(5);
		float temp;

		if (f1 > f4) {
			temp = f1;
			f1 = f4;
			f4 = temp;
		}

		if (f2 > f5) {
			temp = f2;
			f2 = f5;
			f5 = temp;
		}

		if (f3 > f6) {
			temp = f3;
			f3 = f6;
			f6 = temp;
		}

		CPowerPoints::GenerateNewOne(f1, f2, f3, f4, f5, f6, *(uint8*)&GET_INTEGER_PARAM(6));

		return 0;
	}
	case COMMAND_SET_ALL_TAXI_LIGHTS:
		CollectParameters(&m_nIp, 1);
		CAutomobile::SetAllTaxiLights(GET_INTEGER_PARAM(0) != 0);
		return 0;
	*/
	case COMMAND_IS_CAR_ARMED_WITH_ANY_BOMB:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
#ifdef FIX_BUGS
		if (pVehicle->IsCar())
			UpdateCompareFlag(((CAutomobile*)pVehicle)->m_bombType != 0);
		else if (pVehicle->IsBike())
			UpdateCompareFlag(((CBike*)pVehicle)->m_bombType != 0);
		else
			UpdateCompareFlag(false);
#else
		CAutomobile* pCar = (CVehicle*)pVehicle;
		UpdateCompareFlag(pCar->m_bombType != 0); //TODO: enum
#endif
		return 0;
	}
	case COMMAND_APPLY_BRAKES_TO_PLAYERS_CAR:
		CollectParameters(&m_nIp, 2);
		CPad::GetPad(GET_INTEGER_PARAM(0))->bApplyBrakes = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	case COMMAND_SET_PLAYER_HEALTH:
	{
		CollectParameters(&m_nIp, 2);
		CPlayerPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		pPed->m_fHealth = Min(GET_INTEGER_PARAM(1), CWorld::Players[GET_INTEGER_PARAM(0)].m_nMaxHealth);
		return 0;
	}
	case COMMAND_SET_CHAR_HEALTH:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		if (GET_INTEGER_PARAM(1)) {
			pPed->m_fHealth = GET_INTEGER_PARAM(1);
		}
		else if (pPed->bInVehicle) {
			pPed->SetDead();
			if (!pPed->IsPlayer())
				pPed->FlagToDestroyWhenNextProcessed();
		}
		else {
			pPed->SetDie(); // last argument = 13 (default? TODO)
		}
		return 0;
	}
	case COMMAND_SET_CAR_HEALTH:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->m_fHealth = GET_INTEGER_PARAM(1);
		return 0;
	}
	case COMMAND_GET_PLAYER_HEALTH:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_fHealth);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_CHAR_HEALTH:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		SET_INTEGER_PARAM(0, pPed->m_fHealth);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_CAR_HEALTH:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_INTEGER_PARAM(0, pVehicle->m_fHealth);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_CAR_ARMED_WITH_BOMB:
	{
		CollectParameters(&m_nIp, 2);
		CAutomobile* pVehicle = (CAutomobile*)CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
#ifdef FIX_BUGS
		if (pVehicle->IsCar())
			UpdateCompareFlag(((CAutomobile*)pVehicle)->m_bombType == GET_INTEGER_PARAM(1));
		else if (pVehicle->IsBike())
			UpdateCompareFlag(((CBike*)pVehicle)->m_bombType == GET_INTEGER_PARAM(1));
		else
			UpdateCompareFlag(false);
#else
		CAutomobile* pCar = (CVehicle*)pVehicle;
		UpdateCompareFlag(pCar->m_bombType != 0); //TODO: enum
#endif
		return 0;
	}
	case COMMAND_CHANGE_CAR_COLOUR:
	{
		CollectParameters(&m_nIp, 3);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		if (GET_INTEGER_PARAM(1) >= 256 || GET_INTEGER_PARAM(2) >= 256)
			debug("CHANGE_CAR_COLOUR - Colours must be less than %d", 256);
		pVehicle->m_currentColour1 = GET_INTEGER_PARAM(1);
		pVehicle->m_currentColour2 = GET_INTEGER_PARAM(2);
		return 0;
	}
	case COMMAND_SWITCH_PED_ROADS_ON:
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
		ThePaths.SwitchPedRoadsOffInArea(infX, supX, infY, supY, infZ, supZ, false);
		return 0;
	}
	case COMMAND_SWITCH_PED_ROADS_OFF:
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
		ThePaths.SwitchPedRoadsOffInArea(infX, supX, infY, supY, infZ, supZ, true);
		return 0;
	}
	case COMMAND_CHAR_LOOK_AT_CHAR_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pSourcePed);
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTargetPed);
		pSourcePed->SetLookFlag(pTargetPed, true, true);
		pSourcePed->SetLookTimer(60000);
		return 0;
	}
	case COMMAND_CHAR_LOOK_AT_PLAYER_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pSourcePed);
		CPed* pTargetPed = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		script_assert(pTargetPed);
		pSourcePed->SetLookFlag(pTargetPed, true);
		pSourcePed->SetLookTimer(60000);
		return 0;
	}
	case COMMAND_PLAYER_LOOK_AT_CHAR_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pSourcePed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pSourcePed);
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pTargetPed);
		pSourcePed->SetLookFlag(pTargetPed, true);
		pSourcePed->SetLookTimer(60000);
		return 0;
	}
	case COMMAND_STOP_CHAR_LOOKING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pSourcePed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pSourcePed);
		pSourcePed->ClearLookFlag();
		pSourcePed->bKeepTryingToLook = false;
		if (pSourcePed->GetPedState() == PED_LOOK_HEADING || pSourcePed->GetPedState() == PED_LOOK_ENTITY)
			pSourcePed->RestorePreviousState();
		return 0;
	}
	case COMMAND_STOP_PLAYER_LOOKING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pSourcePed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pSourcePed);
		pSourcePed->ClearLookFlag();
		pSourcePed->bKeepTryingToLook = false;
		if (pSourcePed->GetPedState() == PED_LOOK_HEADING || pSourcePed->GetPedState() == PED_LOOK_ENTITY)
			pSourcePed->RestorePreviousState();
		return 0;
	}
	/*
	case COMMAND_SWITCH_HELICOPTER:
		CollectParameters(&m_nIp, 1);
		CHeli::ActivateHeli(GET_INTEGER_PARAM(0) != 0);
		return 0;
	*/
	//case COMMAND_SET_GANG_ATTITUDE:
	//case COMMAND_SET_GANG_GANG_ATTITUDE:
	//case COMMAND_SET_GANG_PLAYER_ATTITUDE:
	case COMMAND_SET_GANG_PED_MODELS:
		CollectParameters(&m_nIp, 3);
		CGangs::SetGangPedModels(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	case COMMAND_SET_GANG_CAR_MODEL:
		CollectParameters(&m_nIp, 2);
		CGangs::SetGangVehicleModel(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1));
		return 0;
	case COMMAND_SET_GANG_WEAPONS:
		CollectParameters(&m_nIp, 3);
		CGangs::SetGangWeapons(GET_INTEGER_PARAM(0), (eWeaponType)GET_INTEGER_PARAM(1), (eWeaponType)GET_INTEGER_PARAM(2));
		return 0;
	/*
	case COMMAND_SET_CHAR_OBJ_RUN_TO_AREA:
	{
		CollectParameters(&m_nIp, 5);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		float infX = GET_FLOAT_PARAM(1);
		float infY = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_RUN_TO_AREA, pos, radius);
		return 0;
	}
	*/
	case COMMAND_SET_CHAR_OBJ_RUN_TO_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CVector pos;
		pos.x = GET_FLOAT_PARAM(1);
		pos.y = GET_FLOAT_PARAM(2);
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_RUN_TO_AREA, pos);
		return 0;
	}
	/*
	case COMMAND_IS_PLAYER_TOUCHING_OBJECT_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(1));
		bool isTouching = false;
		if (pPed->bInVehicle)
			isTouching = false;
		else if (pPed->GetHasCollidedWith(pObject))
			isTouching = true;
		UpdateCompareFlag(isTouching);
		return 0;
	}
	case COMMAND_IS_CHAR_TOUCHING_OBJECT_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(1));
		bool isTouching = false;
		if (pPed->InVehicle())
			isTouching = false;
		else if (pPed->GetHasCollidedWith(pObject))
			isTouching = true;
		UpdateCompareFlag(isTouching);
		return 0;
	}
	*/
	case COMMAND_LOAD_SPECIAL_CHARACTER:
	{
		CollectParameters(&m_nIp, 1);
		char name[16];
		strncpy(name, (char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			name[i] = tolower(name[i]);
		CStreaming::RequestSpecialChar(GET_INTEGER_PARAM(0) - 1, name, STREAMFLAGS_DEPENDENCY | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		return 0;
	}
	case COMMAND_HAS_SPECIAL_CHARACTER_LOADED:
	{
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CStreaming::HasSpecialCharLoaded(GET_INTEGER_PARAM(0) - 1));
		return 0;
	}
	/*
	case COMMAND_FLASH_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bHasBlip = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_FLASH_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bHasBlip = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_FLASH_OBJECT:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		pObject->bHasBlip = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	*/
	case COMMAND_IS_PLAYER_IN_REMOTE_MODE:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CWorld::Players[GET_INTEGER_PARAM(0)].IsPlayerInRemoteMode());
		return 0;
	case COMMAND_ARM_CAR_WITH_BOMB:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
#ifdef FIX_BUGS
		if (pVehicle->IsCar()) {
			((CAutomobile*)pVehicle)->m_bombType = GET_INTEGER_PARAM(1);
			((CAutomobile*)pVehicle)->m_pBombRigger = FindPlayerPed();
		}
		else if (pVehicle->IsBike()) {
			((CBike*)pVehicle)->m_bombType = GET_INTEGER_PARAM(1);
			((CBike*)pVehicle)->m_pBombRigger = FindPlayerPed();
		}
#else
		((CAutomobile*)pVehicle)->m_bombType = GET_INTEGER_PARAM(1);
		((CAutomobile*)pVehicle)->m_pBombRigger = FindPlayerPed();
#endif
		return 0;
	}
	case COMMAND_SET_CHAR_PERSONALITY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->SetPedStats((ePedStats)GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_SET_CUTSCENE_OFFSET:
		CollectParameters(&m_nIp, 3);
		CCutsceneMgr::SetCutsceneOffset(GET_VECTOR_PARAM(0));
		return 0;
	case COMMAND_SET_ANIM_GROUP_FOR_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_animGroup = (AssocGroupId)GET_INTEGER_PARAM(1);
		pPed->bOverrideMoveAnim = false;
		return 0;
	}
	/*
	case COMMAND_SET_ANIM_GROUP_FOR_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		pPed->m_animGroup = (AssocGroupId)GET_INTEGER_PARAM(1);
		return 0;
	}
	*/
	case COMMAND_REQUEST_MODEL:
	{
		CollectParameters(&m_nIp, 1);
		int model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		CStreaming::RequestModel(model, STREAMFLAGS_DEPENDENCY | STREAMFLAGS_NOFADE | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
		if (model == MI_MINIGUN)
#ifdef FIX_BUGS
			CStreaming::RequestModel(MI_MINIGUN2, STREAMFLAGS_DEPENDENCY | STREAMFLAGS_NOFADE | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
#else
			CStreaming::RequestModel(MI_MINIGUN2, STREAMFLAGS_DEPENDENCY | STREAMFLAGS_NOFADE | STREAMFLAGS_SCRIPTOWNED);
#endif
		return 0;
	}
	case COMMAND_HAS_MODEL_LOADED:
	{
		CollectParameters(&m_nIp, 1);
		int model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		UpdateCompareFlag(CStreaming::HasModelLoaded(model)/* || cWorldStream::Instance()->pDynamic(model, 0) */); // TODO
		return 0;
	}
	case COMMAND_MARK_MODEL_AS_NO_LONGER_NEEDED:
	{
		CollectParameters(&m_nIp, 1);
		int model = GET_INTEGER_PARAM(0);
		if (model < 0)
			model = CTheScripts::UsedObjectArray[-model].index;
		if (m_bIsMissionScript)
			CStreaming::SetMissionDoesntRequireModel(model);
		else
			CStreaming::SetAmbientMissionDoesntRequireModel(model);
		return 0;
	}
	case COMMAND_GRAB_PHONE:
	{
		CollectParameters(&m_nIp, 2);
		SET_INTEGER_PARAM(0, gPhoneInfo.GrabPhone(GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	/*
	case COMMAND_SET_REPEATED_PHONE_MESSAGE:
	{
		CollectParameters(&m_nIp, 1);
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		gPhoneInfo.SetPhoneMessage_Repeatedly(GET_INTEGER_PARAM(0), text, nil, nil, nil, nil, nil);
		return 0;
	}
	case COMMAND_SET_PHONE_MESSAGE:
	{
		CollectParameters(&m_nIp, 1);
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		gPhoneInfo.SetPhoneMessage_JustOnce(GET_INTEGER_PARAM(0), text, nil, nil, nil, nil, nil);
		return 0;
	}
	case COMMAND_HAS_PHONE_DISPLAYED_MESSAGE:
	{
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(gPhoneInfo.HasMessageBeenDisplayed(GET_INTEGER_PARAM(0)));
		return 0;
	}
	*/
	case COMMAND_TURN_PHONE_OFF:
	{
		CollectParameters(&m_nIp, 1);
		gPhoneInfo.SetPhoneMessage_JustOnce(GET_INTEGER_PARAM(0), nil, nil, nil, nil, nil, nil);
		return 0;
	}
	case COMMAND_DRAW_CORONA:
	{
		uint32 ip = m_nIp;
		int32* ptr = GetPointerToScriptVariable(&ip, 0);
		CollectParameters(&m_nIp, 9);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CCoronas::RegisterCorona((uintptr)ptr, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(8),
			255, pos, -GET_FLOAT_PARAM(3), 450.0f, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), 1, 0, 0, 0.0f);
		return 0;
	}
	/*
	case COMMAND_DRAW_LIGHT:
	{
		CollectParameters(&m_nIp, 6);
		CVector pos = GET_VECTOR_PARAM(0);
		CVector unused(0.0f, 0.0f, 0.0f);
		CPointLights::AddLight(0, GET_VECTOR_PARAM(0), CVector(0.0f, 0.0f, 0.0f), 12.0f,
			GET_INTEGER_PARAM(3) / 255.0f, GET_INTEGER_PARAM(4) / 255.0f, GET_INTEGER_PARAM(5) / 255.0f, 0, true);
		return 0;
	}
	*/
	case COMMAND_STORE_WEATHER:
		CWeather::StoreWeatherState();
		return 0;
	case COMMAND_RESTORE_WEATHER:
		CWeather::RestoreWeatherState();
	case COMMAND_STORE_CLOCK:
		CClock::StoreClock();
		return 0;
	case COMMAND_RESTORE_CLOCK:
		CClock::RestoreClock();
		return 0;
	case COMMAND_RESTART_CRITICAL_MISSION:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRestart::OverrideNextRestart(pos, GET_FLOAT_PARAM(3));
		if (CWorld::Players[CWorld::PlayerInFocus].m_WBState != WBSTATE_PLAYING)
			printf("RESTART_CRITICAL_MISSION - Player state is not PLAYING\n");
		CWorld::Players[CWorld::PlayerInFocus].PlayerFailedCriticalMission();
		return 0;
	}
	case COMMAND_IS_PLAYER_PLAYING:
	{
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(CWorld::Players[GET_INTEGER_PARAM(0)].m_WBState == WBSTATE_PLAYING);
		return 0;
	}
#ifdef GTA_SCRIPT_COLLECTIVE
	case COMMAND_SET_COLL_OBJ_NO_OBJ:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_NONE);
		return 0;
#endif
	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands600To699(int32 command)
{
	switch (command){
#ifdef GTA_SCRIPT_COLLECTIVE
	case COMMAND_SET_COLL_OBJ_WAIT_ON_FOOT:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_WAIT_ON_FOOT);
		return 0;
	case COMMAND_SET_COLL_OBJ_FLEE_ON_FOOT_TILL_SAFE:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE);
		return 0;
	case COMMAND_SET_COLL_OBJ_GUARD_SPOT:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GUARD_AREA, pos);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_GUARD_AREA:
	{
		CollectParameters(&m_nIp, 5);
		float infX = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(3);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		float infY = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(4);
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GUARD_AREA, pos, radius);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_WAIT_IN_CAR:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_WAIT_IN_CAR);
		return 0;
	case COMMAND_SET_COLL_OBJ_KILL_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_KILL_CHAR_ON_FOOT, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_KILL_PLAYER_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_KILL_CHAR_ON_FOOT, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_KILL_CHAR_ANY_MEANS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_KILL_CHAR_ANY_MEANS, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_KILL_PLAYER_ANY_MEANS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_KILL_CHAR_ANY_MEANS, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_TILL_SAFE:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_FLEE_PLAYER_ON_FOOT_TILL_SAFE:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_FLEE_PLAYER_ON_FOOT_ALWAYS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_GOTO_CHAR_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_CHAR_ON_FOOT, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_GOTO_PLAYER_ON_FOOT:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(1)].m_pPed;
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_CHAR_ON_FOOT, pPed);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_LEAVE_CAR:
		CollectParameters(&m_nIp, 1);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_LEAVE_CAR);
		return 0;
	case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_PASSENGER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_ENTER_CAR_AS_PASSENGER, pVehicle);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_DRIVER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_ENTER_CAR_AS_DRIVER, pVehicle);
		return 0;
	}
	/*
	case COMMAND_SET_COLL_OBJ_FOLLOW_CAR_IN_CAR:
	case COMMAND_SET_COLL_OBJ_FIRE_AT_OBJECT_FROM_VEHICLE:
	case COMMAND_SET_COLL_OBJ_DESTROY_OBJECT:
	*/
	case COMMAND_SET_COLL_OBJ_DESTROY_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(1));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_DESTROY_CAR, pVehicle);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_GOTO_AREA_ON_FOOT:
	{
		CollectParameters(&m_nIp, 5);
		float infX = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(3);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		float infY = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(4);
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_AREA_ON_FOOT, pos, radius);
		return 0;
	}
	/*
	case COMMAND_SET_COLL_OBJ_GOTO_AREA_IN_CAR:
	case COMMAND_SET_COLL_OBJ_FOLLOW_CAR_ON_FOOT_WITH_OFFSET:
	case COMMAND_SET_COLL_OBJ_GUARD_ATTACK:
	*/
	case COMMAND_SET_COLL_OBJ_FOLLOW_ROUTE:
		CollectParameters(&m_nIp, 3);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_FOLLOW_ROUTE, GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2));
		return 0;
	case COMMAND_SET_COLL_OBJ_GOTO_COORD_ON_FOOT:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), CWorld::FindGroundZForCoord(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2)));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_AREA_ON_FOOT, pos);
		return 0;
	}
	//case COMMAND_SET_COLL_OBJ_GOTO_COORD_IN_CAR:
	case COMMAND_SET_COLL_OBJ_RUN_TO_AREA:
	{
		CollectParameters(&m_nIp, 5);
		float infX = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(3);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		float infY = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(4);
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_RUN_TO_AREA, pos, radius);
		return 0;
	}
	case COMMAND_SET_COLL_OBJ_RUN_TO_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2), CWorld::FindGroundZForCoord(GET_FLOAT_PARAM(1), GET_FLOAT_PARAM(2)));
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_RUN_TO_AREA, pos);
		return 0;
	}
	case COMMAND_ADD_PEDS_IN_AREA_TO_COLL:
	{
		CollectParameters(&m_nIp, 3);
		float X = GET_FLOAT_PARAM(0);
		float Y = GET_FLOAT_PARAM(1);
		float Z = CWorld::FindGroundZForCoord(X, Y);
		float radius = GET_FLOAT_PARAM(2);
		SET_INTEGER_PARAM(0, CTheScripts::AddPedsInAreaToCollective(X, Y, Z, radius));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_PEDS_IN_VEHICLE_TO_COLL:
		CollectParameters(&m_nIp, 1);
		SET_INTEGER_PARAM(0, CTheScripts::AddPedsInVehicleToCollective(GET_INTEGER_PARAM(0)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_CLEAR_COLL:
		CollectParameters(&m_nIp, 1);
		for (int i = 0; i < MAX_NUM_COLLECTIVES; i++) {
			if (CTheScripts::CollectiveArray[i].colIndex == GET_INTEGER_PARAM(0)) {
				CTheScripts::CollectiveArray[i].colIndex = -1;
				CTheScripts::CollectiveArray[i].pedIndex = 0;
			}
		}
		return 0;
	case COMMAND_IS_COLL_IN_CARS:
	{
		CollectParameters(&m_nIp, 1);
		bool result = true;
		for (int i = 0; i < MAX_NUM_COLLECTIVES; i++) {
			CPed* pPed = CPools::GetPedPool()->GetAt(CTheScripts::CollectiveArray[i].pedIndex);
			if (!pPed) {
				CTheScripts::CollectiveArray[i].colIndex = -1;
				CTheScripts::CollectiveArray[i].pedIndex = 0;
			}
			else {
				result = false;
				break;
			}
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_LOCATE_COLL_ANY_MEANS_2D:
	case COMMAND_LOCATE_COLL_ON_FOOT_2D:
	case COMMAND_LOCATE_COLL_IN_CAR_2D:
	case COMMAND_LOCATE_STOPPED_COLL_ANY_MEANS_2D:
	case COMMAND_LOCATE_STOPPED_COLL_ON_FOOT_2D:
	case COMMAND_LOCATE_STOPPED_COLL_IN_CAR_2D:
		LocateCollectiveCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_COLL_ANY_MEANS_CHAR_2D:
	case COMMAND_LOCATE_COLL_ON_FOOT_CHAR_2D:
	case COMMAND_LOCATE_COLL_IN_CAR_CHAR_2D:
		LocateCollectiveCharCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_COLL_ANY_MEANS_CAR_2D:
	case COMMAND_LOCATE_COLL_ON_FOOT_CAR_2D:
	case COMMAND_LOCATE_COLL_IN_CAR_CAR_2D:
		LocateCollectiveCarCommand(command, &m_nIp);
		return 0;
	case COMMAND_LOCATE_COLL_ANY_MEANS_PLAYER_2D:
	case COMMAND_LOCATE_COLL_ON_FOOT_PLAYER_2D:
	case COMMAND_LOCATE_COLL_IN_CAR_PLAYER_2D:
		LocateCollectivePlayerCommand(command, &m_nIp);
		return 0;
	case COMMAND_IS_COLL_IN_AREA_2D:
	case COMMAND_IS_COLL_IN_AREA_ON_FOOT_2D:
	case COMMAND_IS_COLL_IN_AREA_IN_CAR_2D:
	case COMMAND_IS_COLL_STOPPED_IN_AREA_2D:
	case COMMAND_IS_COLL_STOPPED_IN_AREA_ON_FOOT_2D:
	case COMMAND_IS_COLL_STOPPED_IN_AREA_IN_CAR_2D:
		CollectiveInAreaCheckCommand(command, &m_nIp);
		return 0;
	case COMMAND_GET_NUMBER_OF_PEDS_IN_COLL:
	{
		CollectParameters(&m_nIp, 1);
		int total = 0;
		for (int i = 0; i < MAX_NUM_COLLECTIVES; i++) {
			CPed* pPed = CPools::GetPedPool()->GetAt(CTheScripts::CollectiveArray[i].pedIndex);
			if (!pPed) {
				CTheScripts::CollectiveArray[i].colIndex = -1;
				CTheScripts::CollectiveArray[i].pedIndex = 0;
			}
			else {
				total++;
			}
		}
		SET_INTEGER_PARAM(0, total);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
#endif
	case COMMAND_SET_CHAR_HEED_THREATS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bRespondsToThreats = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_PLAYER_HEED_THREATS:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		pPed->bRespondsToThreats = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_GET_CONTROLLER_MODE:
#if defined(GTA_PC) && !defined(DETECT_PAD_INPUT_SWITCH)
		SET_INTEGER_PARAM(0, 0);
#else
		SET_INTEGER_PARAM(0, CPad::IsAffectedByController ? CPad::GetPad(0)->Mode : 0);
#endif
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_CAN_RESPRAY_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		//assert(pVehicle->m_vehType == VEHICLE_TYPE_CAR);
		// they DO call this for bikes, we don't really want to destroy the structure...
#ifdef FIX_BUGS
		if (pVehicle->m_vehType == VEHICLE_TYPE_CAR)
#endif
			((CAutomobile*)pVehicle)->bFixedColour = (GET_INTEGER_PARAM(1) == 0);
#ifdef FIX_BUGS
		else if (pVehicle->m_vehType == VEHICLE_TYPE_BIKE)
			((CBike*)pVehicle)->bFixedColour = (GET_INTEGER_PARAM(1) == 0);
#endif
		
		return 0;
	}
	case COMMAND_IS_TAXI:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->IsTaxi());
		return 0;
	}
	case COMMAND_UNLOAD_SPECIAL_CHARACTER:
		CollectParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CStreaming::SetMissionDoesntRequireSpecialChar(GET_INTEGER_PARAM(0) - 1);
		else
			CStreaming::SetAmbientMissionDoesntRequireSpecialChar(GET_INTEGER_PARAM(0) - 1);
		return 0;
	case COMMAND_RESET_NUM_OF_MODELS_KILLED_BY_PLAYER:
		CDarkel::ResetModelsKilledByPlayer();
		return 0;
	case COMMAND_GET_NUM_OF_MODELS_KILLED_BY_PLAYER:
		CollectParameters(&m_nIp, 1);
		SET_INTEGER_PARAM(0, CDarkel::QueryModelsKilledByPlayer(GET_INTEGER_PARAM(0)));
		StoreParameters(&m_nIp, 1);
		return 0;
	/*
	case COMMAND_ACTIVATE_GARAGE:
		CollectParameters(&m_nIp, 1);
		CGarages::ActivateGarage(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_SWITCH_TAXI_TIMER:
	{
		CollectParameters(&m_nIp, 1);
		if (GET_INTEGER_PARAM(0) != 0){
			CWorld::Players[CWorld::PlayerInFocus].m_nUnusedTaxiTimer = CTimer::GetTimeInMilliseconds();
			CWorld::Players[CWorld::PlayerInFocus].m_bUnusedTaxiThing = true;
		}else{
			CWorld::Players[CWorld::PlayerInFocus].m_bUnusedTaxiThing = false;
		}
		return 0;
	}
	*/
	case COMMAND_CREATE_OBJECT_NO_OFFSET:
	{
		CollectParameters(&m_nIp, 4);
		int mi = GET_INTEGER_PARAM(0) >= 0 ? GET_INTEGER_PARAM(0) : CTheScripts::UsedObjectArray[-GET_INTEGER_PARAM(0)].index;
		CObject* pObj = new CObject(mi, false);
;		pObj->ObjectCreatedBy = MISSION_OBJECT;
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pObj->SetPosition(pos);
		pObj->SetOrientation(0.0f, 0.0f, 0.0f);
		pObj->GetMatrix().UpdateRW();
		pObj->UpdateRwFrame();
		CBaseModelInfo* pModelInfo = CModelInfo::GetModelInfo(mi);
		if (pModelInfo->IsBuilding() && ((CSimpleModelInfo*)pModelInfo)->m_isBigBuilding)
			pObj->SetupBigBuilding();
		CTheScripts::ClearSpaceForMissionEntity(pos, pObj);
		CWorld::Add(pObj);
		SET_INTEGER_PARAM(0, CPools::GetObjectPool()->GetIndex(pObj));
		StoreParameters(&m_nIp, 1);
		if (m_bIsMissionScript)
			CTheScripts::MissionCleanUp.AddEntityToList(GET_INTEGER_PARAM(0), CLEANUP_OBJECT);
		return 0;
	}
	case COMMAND_IS_BOAT:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_BOAT);
		return 0;
	}
	/*
	case COMMAND_SET_CHAR_OBJ_GOTO_AREA_ANY_MEANS:
	{
		CollectParameters(&m_nIp, 5);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		float infX = GET_FLOAT_PARAM(1);
		float infY = GET_FLOAT_PARAM(2);
		float supX = GET_FLOAT_PARAM(3);
		float supY = GET_FLOAT_PARAM(4);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_GOTO_AREA_ANY_MEANS, pos, radius);
		return 0;
	}
#ifdef GTA_SCRIPT_COLLECTIVE
	case COMMAND_SET_COLL_OBJ_GOTO_AREA_ANY_MEANS:
	{
		CollectParameters(&m_nIp, 5);
		float infX = GET_FLOAT_PARAM(1);
		float supX = GET_FLOAT_PARAM(3);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(3);
			supX = GET_FLOAT_PARAM(1);
		}
		float infY = GET_FLOAT_PARAM(2);
		float supY = GET_FLOAT_PARAM(4);
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(4);
			supY = GET_FLOAT_PARAM(2);
		}
		CVector pos;
		pos.x = (infX + supX) / 2;
		pos.y = (infY + supY) / 2;
		pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		float radius = Max(pos.x - infX, pos.y - infY);
		CTheScripts::SetObjectiveForAllPedsInCollective(GET_INTEGER_PARAM(0), OBJECTIVE_GOTO_AREA_ANY_MEANS, pos, radius);
		return 0;
	}
#endif
*/
	case COMMAND_IS_PLAYER_STOPPED:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayer = &CWorld::Players[GET_INTEGER_PARAM(0)];
		UpdateCompareFlag(CTheScripts::IsPlayerStopped(pPlayer));
		return 0;
	
	}
	case COMMAND_IS_CHAR_STOPPED:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(CTheScripts::IsPedStopped(pPed));
		return 0;
	}
	case COMMAND_MESSAGE_WAIT:
		CollectParameters(&m_nIp, 2);
		m_nWakeTime = CTimer::GetTimeInMilliseconds() + GET_INTEGER_PARAM(0);
		if (GET_INTEGER_PARAM(1) != 0)
			m_bSkipWakeTime = true;
		return 1;
	/*
	case COMMAND_ADD_PARTICLE_EFFECT:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CParticleObject::AddObject(GET_INTEGER_PARAM(0), pos, GET_INTEGER_PARAM(4) != 0);
		return 0;
	}
	*/
	case COMMAND_SWITCH_WIDESCREEN:
		CollectParameters(&m_nIp, 1);
		if (GET_INTEGER_PARAM(0) != 0)
			TheCamera.SetWideScreenOn();
		else {
			// TODO(LCS): unknown field
			TheCamera.SetWideScreenOff();
		}
		return 0;
	/*
	case COMMAND_ADD_SPRITE_BLIP_FOR_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetEntityBlip(BLIP_CAR, GET_INTEGER_PARAM(0), 0, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(1));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_SPRITE_BLIP_FOR_CHAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetEntityBlip(BLIP_CHAR, GET_INTEGER_PARAM(0), 1, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(1));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_SPRITE_BLIP_FOR_OBJECT:
	{
		CollectParameters(&m_nIp, 2);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetEntityBlip(BLIP_OBJECT, GET_INTEGER_PARAM(0), 6, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(1));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	*/
	case COMMAND_ADD_SPRITE_BLIP_FOR_CONTACT_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetCoordBlip(BLIP_CONTACT_POINT, pos, 2, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(3));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_ADD_SPRITE_BLIP_FOR_COORD:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CRadar::GetActualBlipArrayIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		int id = CRadar::SetCoordBlip(BLIP_COORD, pos, 4, BLIP_DISPLAY_BOTH);
		CRadar::SetBlipSprite(id, GET_INTEGER_PARAM(3));
		SET_INTEGER_PARAM(0, id);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_ONLY_DAMAGED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bOnlyDamagedByPlayer = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_CAR_ONLY_DAMAGED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bOnlyDamagedByPlayer = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_SET_CHAR_PROOFS:
	{
		CollectParameters(&m_nIp, 6);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bBulletProof = (GET_INTEGER_PARAM(1) != 0);
		pPed->bFireProof = (GET_INTEGER_PARAM(2) != 0);
		pPed->bExplosionProof = (GET_INTEGER_PARAM(3) != 0);
		pPed->bCollisionProof = (GET_INTEGER_PARAM(4) != 0);
		pPed->bMeleeProof = (GET_INTEGER_PARAM(5) != 0);
		return 0;
	}
	case COMMAND_SET_CAR_PROOFS:
	{
		CollectParameters(&m_nIp, 6);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bBulletProof = (GET_INTEGER_PARAM(1) != 0);
		pVehicle->bFireProof = (GET_INTEGER_PARAM(2) != 0);
		pVehicle->bExplosionProof = (GET_INTEGER_PARAM(3) != 0);
		pVehicle->bCollisionProof = (GET_INTEGER_PARAM(4) != 0);
		pVehicle->bMeleeProof = (GET_INTEGER_PARAM(5) != 0);
		return 0;
	}
	case COMMAND_IS_PLAYER_IN_ANGLED_AREA_2D:
	case COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_2D:
	case COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_2D:
	case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_2D:
	case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_2D:
	case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_2D:
	case COMMAND_IS_PLAYER_IN_ANGLED_AREA_3D:
	case COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_3D:
	case COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_3D:
	case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_3D:
	case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_3D:
	case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_3D:
		PlayerInAngledAreaCheckCommand(command, &m_nIp);
		return 0;
	/*
	case COMMAND_DEACTIVATE_GARAGE:
		CollectParameters(&m_nIp, 1);
		CGarages::DeActivateGarage(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_GET_NUMBER_OF_CARS_COLLECTED_BY_GARAGE:
		CollectParameters(&m_nIp, 1);
		SET_INTEGER_PARAM(0, CGarages::QueryCarsCollected(GET_INTEGER_PARAM(0)));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_HAS_CAR_BEEN_TAKEN_TO_GARAGE:
		CollectParameters(&m_nIp, 2);
		UpdateCompareFlag(CGarages::HasThisCarBeenCollected(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1) - 1));
		return 0;
	*/
	default:
		script_assert(0);
	}
	return -1;
}

int8 CRunningScript::ProcessCommands700To799(int32 command)
{
	switch (command){
	/*
	case COMMAND_SET_SWAT_REQUIRED:
		CollectParameters(&m_nIp, 1);
		FindPlayerPed()->m_pWanted->m_bSwatRequired = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	case COMMAND_SET_FBI_REQUIRED:
		CollectParameters(&m_nIp, 1);
		FindPlayerPed()->m_pWanted->m_bFbiRequired = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	case COMMAND_SET_ARMY_REQUIRED:
		CollectParameters(&m_nIp, 1);
		FindPlayerPed()->m_pWanted->m_bArmyRequired = (GET_INTEGER_PARAM(0) != 0);
		return 0;
	*/
	case COMMAND_IS_CAR_IN_WATER:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		UpdateCompareFlag(pVehicle && pVehicle->bIsInWater);
		return 0;
	}
	case COMMAND_GET_CLOSEST_CHAR_NODE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CPathNode* pNode = &ThePaths.m_pathNodes[ThePaths.FindNodeClosestToCoors(pos, 1, 800.0f, true)];
		SET_VECTOR_PARAM(0, pNode->GetPosition());
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_GET_CLOSEST_CAR_NODE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		SET_VECTOR_PARAM(0, ThePaths.FindNodeCoorsForScript(ThePaths.FindNodeClosestToCoors(pos, 0, 800.0f, true, true)));
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_CAR_GOTO_COORDINATES_ACCURATE:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += pVehicle->GetDistanceFromCentreOfMassToBaseOfModel();
		uint8 nOldMission = pVehicle->AutoPilot.m_nCarMission;
		if (CCarCtrl::JoinCarWithRoadSystemGotoCoors(pVehicle, pos, false))
			pVehicle->AutoPilot.m_nCarMission = MISSION_GOTO_COORDS_STRAIGHT_ACCURATE;
		else
			pVehicle->AutoPilot.m_nCarMission = MISSION_GOTOCOORDS_ACCURATE;
		pVehicle->SetStatus(STATUS_PHYSICS);
		pVehicle->bEngineOn = true;
		pVehicle->AutoPilot.m_nCruiseSpeed = Max(1, pVehicle->AutoPilot.m_nCruiseSpeed);
		if (nOldMission != pVehicle->AutoPilot.m_nCarMission)
			pVehicle->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
		return 0;
	}
	/*
	case COMMAND_START_PACMAN_RACE:
		CollectParameters(&m_nIp, 1);
		CPacManPickups::StartPacManRace(GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_START_PACMAN_RECORD:
		CPacManPickups::StartPacManRecord();
		return 0;
	case COMMAND_GET_NUMBER_OF_POWER_PILLS_EATEN:
		SET_INTEGER_PARAM(0, CPacManPickups::QueryPowerPillsEatenInRace());
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_CLEAR_PACMAN:
		CPacManPickups::CleanUpPacManStuff();
		return 0;
	case COMMAND_START_PACMAN_SCRAMBLE:
	{
		CollectParameters(&m_nIp, 5);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CPacManPickups::StartPacManScramble(pos, GET_FLOAT_PARAM(3), GET_INTEGER_PARAM(4));
		return 0;
	}
	case COMMAND_GET_NUMBER_OF_POWER_PILLS_CARRIED:
		SET_INTEGER_PARAM(0, CPacManPickups::QueryPowerPillsCarriedByPlayer());
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_CLEAR_NUMBER_OF_POWER_PILLS_CARRIED:
		CPacManPickups::ResetPowerPillsCarriedByPlayer();
		return 0;
	*/
	case COMMAND_IS_CAR_ON_SCREEN:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(TheCamera.IsSphereVisible(pVehicle->GetBoundCentre(), pVehicle->GetBoundRadius()));
		return 0;
	}
	case COMMAND_IS_CHAR_ON_SCREEN:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(TheCamera.IsSphereVisible(pPed->GetBoundCentre(), pPed->GetBoundRadius()));
		return 0;
	}
	case COMMAND_IS_OBJECT_ON_SCREEN:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		UpdateCompareFlag(TheCamera.IsSphereVisible(pObject->GetBoundCentre(), pObject->GetBoundRadius()));
		return 0;
	}
	case COMMAND_GOSUB_FILE:
	{
		CollectParameters(&m_nIp, 2);
		script_assert(m_nStackPointer < MAX_STACK_DEPTH);
		m_anStack[m_nStackPointer++] = m_nIp;
		SetIP(GET_INTEGER_PARAM(0));
		// GET_INTEGER_PARAM(1) == filename
		return 0;
	}
	case COMMAND_GET_GROUND_Z_FOR_3D_COORD:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		bool success;
		SET_FLOAT_PARAM(0, CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &success));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_START_SCRIPT_FIRE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		SET_INTEGER_PARAM(0, gFireManager.StartScriptFire(pos, nil, 0.8f, 1));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_IS_SCRIPT_FIRE_EXTINGUISHED:
		CollectParameters(&m_nIp, 1);
		UpdateCompareFlag(gFireManager.IsScriptFireExtinguish(GET_INTEGER_PARAM(0)));
		return 0;
	case COMMAND_REMOVE_SCRIPT_FIRE:
		CollectParameters(&m_nIp, 1);
		gFireManager.RemoveScriptFire(GET_INTEGER_PARAM(0));
		return 0;
	/*
	case COMMAND_SET_COMEDY_CONTROLS:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		pVehicle->bComedyControls = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	*/
	case COMMAND_BOAT_GOTO_COORDS:
	{
		CollectParameters(&m_nIp, 4);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_BOAT);
		CBoat* pBoat = (CBoat*)pVehicle;
		CVector pos = GET_VECTOR_PARAM(1);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &pos.z, false);
		pBoat->AutoPilot.m_nCarMission = MISSION_GOTOCOORDS_ASTHECROWSWIMS;
		pBoat->AutoPilot.m_vecDestinationCoors = pos;
		pBoat->SetStatus(STATUS_PHYSICS);
		pBoat->bEngineOn = true;
		pBoat->AutoPilot.m_nCruiseSpeed = Max(1, pBoat->AutoPilot.m_nCruiseSpeed);
		pBoat->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
		return 0;
	}
	case COMMAND_BOAT_STOP:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_BOAT);
		CBoat* pBoat = (CBoat*)pVehicle;
		pBoat->AutoPilot.m_nCarMission = MISSION_NONE;
		pBoat->SetStatus(STATUS_PHYSICS);
		pBoat->bEngineOn = false;
		pBoat->AutoPilot.m_nCruiseSpeed = 0;
		return 0;
	}
	case COMMAND_IS_PLAYER_SHOOTING_IN_AREA:
	{
		CollectParameters(&m_nIp, 6);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		float x1 = GET_FLOAT_PARAM(1);
		float y1 = GET_FLOAT_PARAM(2);
		float x2 = GET_FLOAT_PARAM(3);
		float y2 = GET_FLOAT_PARAM(4);
		UpdateCompareFlag(pPed->bIsShooting && pPed->IsWithinArea(x1, y1, x2, y2));
		if (GET_INTEGER_PARAM(5))
			CTheScripts::HighlightImportantArea((uintptr)this + m_nIp, x1, y1, x2, y2, MAP_Z_LOW_LIMIT);
		/*
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugSquare(x1, y1, x2, y2);
		*/
		return 0;
	}
	case COMMAND_IS_CHAR_SHOOTING_IN_AREA:
	{
		CollectParameters(&m_nIp, 6);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		float x1 = GET_FLOAT_PARAM(1);
		float y1 = GET_FLOAT_PARAM(2);
		float x2 = GET_FLOAT_PARAM(3);
		float y2 = GET_FLOAT_PARAM(4);
		UpdateCompareFlag(pPed->bIsShooting && pPed->IsWithinArea(x1, y1, x2, y2));
		if (GET_INTEGER_PARAM(5))
			CTheScripts::HighlightImportantArea((uintptr)this + m_nIp, x1, y1, x2, y2, MAP_Z_LOW_LIMIT);
		/*
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugSquare(x1, y1, x2, y2);
		*/
		return 0;
	}
	case COMMAND_IS_CURRENT_PLAYER_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(GET_INTEGER_PARAM(1) == pPed->GetWeapon()->m_eWeaponType);
		return 0;
	}
	case COMMAND_IS_CURRENT_CHAR_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(GET_INTEGER_PARAM(1) == pPed->GetWeapon()->m_eWeaponType);
		return 0;
	}
	/*
	case COMMAND_CLEAR_NUMBER_OF_POWER_PILLS_EATEN:
		CPacManPickups::ResetPowerPillsEatenInRace();
		return 0;
	case COMMAND_ADD_POWER_PILL:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		CPacManPickups::GenerateOnePMPickUp(pos);
		return 0;
	}
	*/
	case COMMAND_SET_BOAT_CRUISE_SPEED:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		script_assert(pVehicle->m_vehType == VEHICLE_TYPE_BOAT);
		CBoat* pBoat = (CBoat*)pVehicle;
		pBoat->AutoPilot.m_nCruiseSpeed = GET_FLOAT_PARAM(1);
		return 0;
	}
	case COMMAND_GET_RANDOM_CHAR_IN_AREA:
	{
		CollectParameters(&m_nIp, 7);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		float x1 = GET_FLOAT_PARAM(0);
		float y1 = GET_FLOAT_PARAM(1);
		float x2 = GET_FLOAT_PARAM(2);
		float y2 = GET_FLOAT_PARAM(3);
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1){
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
			if (!ThisIsAValidRandomPed(pPed->m_nPedType, GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7)))
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
	case COMMAND_GET_RANDOM_CHAR_IN_ZONE:
	{
		char zone[KEY_LENGTH_IN_SCRIPT];
		strncpy(zone, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		int nZone = CTheZones::FindZoneByLabelAndReturnIndex(zone, ZONE_DEFAULT);
		if (nZone != -1)
			m_nIp += KEY_LENGTH_IN_SCRIPT;
		CZone* pZone = CTheZones::GetNavigationZone(nZone);
		CollectParameters(&m_nIp, 3);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
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
			if (!ThisIsAValidRandomPed(pPed->m_nPedType, GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2)))
				continue;
			if (pPed->bIsLeader || pPed->m_leader)
				continue;
			if (!CTheZones::PointLiesWithinZone(&pPed->GetPosition(), pZone))
				continue;
			if (pos.z - PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + PED_FIND_Z_OFFSET < pPed->GetPosition().z)
				continue;
			bool found;
			CWorld::FindRoofZFor3DCoord(pos.x, pos.y, pos.z, &found);
			if (found)
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
	case COMMAND_IS_PLAYER_IN_TAXI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle->IsTaxi());
		return 0;
	}
	case COMMAND_IS_PLAYER_SHOOTING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[GET_INTEGER_PARAM(0)].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bIsShooting);
		return 0;
	}
	case COMMAND_IS_CHAR_SHOOTING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(pPed->bIsShooting);
		return 0;
	}
	case COMMAND_CREATE_MONEY_PICKUP:
	{
		CollectParameters(&m_nIp, 4);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GetActualPickupIndex(CollectNextParameterWithoutIncreasingPC(m_nIp));
		SET_INTEGER_PARAM(0, CPickups::GenerateNewOne(pos, MI_MONEY, PICKUP_MONEY, GET_INTEGER_PARAM(3)));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_ACCURACY:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->m_wepAccuracy = Min(100, GET_INTEGER_PARAM(1) * 1.25f);
		return 0;
	}
	case COMMAND_GET_CAR_SPEED:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		SET_FLOAT_PARAM(0, pVehicle->GetSpeed().Magnitude() * GAME_SPEED_TO_METERS_PER_SECOND);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_LOAD_CUTSCENE:
	{
		char name[KEY_LENGTH_IN_SCRIPT];
		strncpy(name, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		// unknown call FUN_29df68(name) on PS2 - not on PSP
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CColStore::RemoveAllCollision();
		CCutsceneMgr::LoadCutsceneData(name);
		return 0;
	}
	case COMMAND_CREATE_CUTSCENE_OBJECT:
	{
		CollectParameters(&m_nIp, 1);
		CCutsceneObject* pCutObj = CCutsceneMgr::CreateCutsceneObject(GET_INTEGER_PARAM(0));
		SET_INTEGER_PARAM(0, CPools::GetObjectPool()->GetIndex(pCutObj));
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CUTSCENE_ANIM:
	{
		CollectParameters(&m_nIp, 1);
		char name[KEY_LENGTH_IN_SCRIPT];
		CObject* pObject = CPools::GetObjectPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pObject);
		strncpy(name, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CCutsceneMgr::SetCutsceneAnim(name, pObject);
		return 0;
	}
	case COMMAND_START_CUTSCENE:
		CCutsceneMgr::StartCutscene();
		return 0;
	case COMMAND_GET_CUTSCENE_TIME:
		SET_INTEGER_PARAM(0, CCutsceneMgr::GetCutsceneTimeInMilleseconds());
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_HAS_CUTSCENE_FINISHED:
	{
		bool bFinished = CCutsceneMgr::HasCutsceneFinished();
		if (bFinished)
			printf("cutscene has now finished\n");
		UpdateCompareFlag(bFinished);
		return 0;
	}
	case COMMAND_CLEAR_CUTSCENE:
		// unknown call on PS2 FUN_29DFA0() - not on PSP
		printf("clear cutscene\n");
		CCutsceneMgr::DeleteCutsceneData();
		return 0;
	case COMMAND_RESTORE_CAMERA_JUMPCUT:
		TheCamera.RestoreWithJumpCut();
		return 0;
	case COMMAND_CREATE_COLLECTABLE1:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GenerateNewOne(pos, MI_COLLECTABLE1, PICKUP_COLLECTABLE1, 0); // TODO: gpModelIndices
		return 0;
	}
	case COMMAND_SET_COLLECTABLE1_TOTAL:
		CollectParameters(&m_nIp, 1);
		CWorld::Players[CWorld::PlayerInFocus].m_nTotalPackages = GET_INTEGER_PARAM(0);
		return 0;
	/*
	case COMMAND_IS_PROJECTILE_IN_AREA:
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
		UpdateCompareFlag(CProjectileInfo::IsProjectileInRange(infX, supX, infY, supY, infZ, supZ, false));
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugCube(infX, infY, infZ, supX, supY, supZ);
		return 0;
	}
	case COMMAND_DESTROY_PROJECTILES_IN_AREA:
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
		UpdateCompareFlag(CProjectileInfo::IsProjectileInRange(infX, supX, infY, supY, infZ, supZ, true));
		if (CTheScripts::DbgFlag)
			CTheScripts::DrawDebugCube(infX, infY, infZ, supX, supY, supZ);
		return 0;
	}
	case COMMAND_DROP_MINE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GenerateNewOne(pos, MI_CARMINE, PICKUP_MINE_INACTIVE, 0);
		return 0;
	}
	case COMMAND_DROP_NAUTICAL_MINE:
	{
		CollectParameters(&m_nIp, 3);
		CVector pos = GET_VECTOR_PARAM(0);
		if (pos.z <= MAP_Z_LOW_LIMIT)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + PICKUP_PLACEMENT_OFFSET;
		CPickups::GenerateNewOne(pos, MI_NAUTICALMINE, PICKUP_MINE_INACTIVE, 0);
		return 0;
	}
	*/
	case COMMAND_IS_CHAR_MODEL:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		UpdateCompareFlag(GET_INTEGER_PARAM(1) == pPed->GetModelIndex());
		return 0;
	}
	case COMMAND_LOAD_SPECIAL_MODEL:
	{
		CollectParameters(&m_nIp, 1);
		char name[KEY_LENGTH_IN_SCRIPT];
		strncpy(name, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		for (int i = 0; i < KEY_LENGTH_IN_SCRIPT; i++)
			name[i] = tolower(name[i]);
		CStreaming::RequestSpecialModel(GET_INTEGER_PARAM(0), name, STREAMFLAGS_DEPENDENCY | (m_bIsMissionScript ? STREAMFLAGS_SCRIPTOWNED : STREAMFLAGS_AMBIENT_SCRIPT_OWNED));
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		return 0;
	}
	//case COMMAND_CREATE_CUTSCENE_HEAD:
	//case COMMAND_SET_CUTSCENE_HEAD_ANIM:
	case COMMAND_SIN:
		CollectParameters(&m_nIp, 1);
		SET_FLOAT_PARAM(0, Sin(DEGTORAD(GET_FLOAT_PARAM(0))));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_COS:
		CollectParameters(&m_nIp, 1);
		SET_FLOAT_PARAM(0, Cos(DEGTORAD(GET_FLOAT_PARAM(0))));
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_GET_CAR_FORWARD_X:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		float forwardX = pVehicle->GetForward().x / pVehicle->GetForward().Magnitude2D();
		SET_FLOAT_PARAM(0, forwardX);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_CAR_FORWARD_Y:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		float forwardY = pVehicle->GetForward().y / pVehicle->GetForward().Magnitude2D();
		SET_FLOAT_PARAM(0, forwardY);
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_CHANGE_GARAGE_TYPE:
		CollectParameters(&m_nIp, 2);
		CGarages::ChangeGarageType(GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), 0);
		return 0;
	case COMMAND_ACTIVATE_CRUSHER_CRANE:
	{
		CollectParameters(&m_nIp, 10);
		float infX = GET_FLOAT_PARAM(2);
		float infY = GET_FLOAT_PARAM(3);
		float supX = GET_FLOAT_PARAM(4);
		float supY = GET_FLOAT_PARAM(5);
		if (infX > supX) {
			infX = GET_FLOAT_PARAM(4);
			supX = GET_FLOAT_PARAM(2);
		}
		if (infY > supY) {
			infY = GET_FLOAT_PARAM(5);
			supY = GET_FLOAT_PARAM(3);
		}
		CCranes::ActivateCrane(infX, supX, infY, supY,
			GET_FLOAT_PARAM(6), GET_FLOAT_PARAM(7), GET_FLOAT_PARAM(8),
			DEGTORAD(GET_FLOAT_PARAM(9)), true, false,
			GET_FLOAT_PARAM(0), GET_FLOAT_PARAM(1));
		return 0;
	}
	case COMMAND_PRINT_WITH_2_NUMBERS:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_2_NUMBERS_NOW:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_2_NUMBERS_SOON:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 4);
		CMessages::AddMessageSoonWithNumber(text, GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), -1, -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_3_NUMBERS:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 5);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), -1, -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_3_NUMBERS_NOW:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 5);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), -1, -1, -1);
		return 0;
	}
	/*
	case COMMAND_PRINT_WITH_3_NUMBERS_SOON:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 5);
		CMessages::AddMessageSoonWithNumber(text, GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), -1, -1, -1);
		return 0;
	}
	*/
	case COMMAND_PRINT_WITH_4_NUMBERS:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 6);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), -1, -1);
		return 0;
	}
	/*
	case COMMAND_PRINT_WITH_4_NUMBERS_NOW:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 6);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_4_NUMBERS_SOON:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 6);
		CMessages::AddMessageSoonWithNumber(text, GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), -1, -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_5_NUMBERS:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 7);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_5_NUMBERS_NOW:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 7);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), -1);
		return 0;
	}
	case COMMAND_PRINT_WITH_5_NUMBERS_SOON:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 7);
		CMessages::AddMessageSoonWithNumber(text, GET_INTEGER_PARAM(5), GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), -1);
		return 0;
	}
	*/
	case COMMAND_PRINT_WITH_6_NUMBERS:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 8);
		CMessages::AddMessageWithNumber(text, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5));
		return 0;
	}
	/*
	case COMMAND_PRINT_WITH_6_NUMBERS_NOW:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 8);
		CMessages::AddMessageJumpQWithNumber(text, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5));
		return 0;
	}
	case COMMAND_PRINT_WITH_6_NUMBERS_SOON:
	{
		wchar* text = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 8);
		CMessages::AddMessageSoonWithNumber(text, GET_INTEGER_PARAM(6), GET_INTEGER_PARAM(7), GET_INTEGER_PARAM(0), GET_INTEGER_PARAM(1), GET_INTEGER_PARAM(2), GET_INTEGER_PARAM(3), GET_INTEGER_PARAM(4), GET_INTEGER_PARAM(5));
		return 0;
	}
	*/
	case COMMAND_SET_CHAR_OBJ_FOLLOW_CHAR_IN_FORMATION:
	{
		CollectParameters(&m_nIp, 3);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		CPed* pTargetPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		pPed->bScriptObjectiveCompleted = false;
		pPed->SetObjective(OBJECTIVE_FOLLOW_CHAR_IN_FORMATION, pTargetPed);
		pPed->SetFormation((eFormation)GET_INTEGER_PARAM(2));
		return 0;
	}
	case COMMAND_PLAYER_MADE_PROGRESS:
		CollectParameters(&m_nIp, 1);
		CStats::ProgressMade += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_SET_PROGRESS_TOTAL:
		CollectParameters(&m_nIp, 1);
		CStats::TotalProgressInGame = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_JUMP_DISTANCE:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpDistance = Max(CStats::MaximumJumpDistance, GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_HEIGHT:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpHeight = Max(CStats::MaximumJumpHeight, GET_FLOAT_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_FLIPS:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpFlips = Max(CStats::MaximumJumpFlips, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_SPINS:
		CollectParameters(&m_nIp, 1);
		CStats::MaximumJumpSpins = Max(CStats::MaximumJumpSpins, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_JUMP_STUNT:
		CollectParameters(&m_nIp, 1);
		CStats::BestStuntJump = Max(CStats::BestStuntJump, GET_INTEGER_PARAM(0));
		return 0;
	case COMMAND_REGISTER_UNIQUE_JUMP_FOUND:
		++CStats::NumberOfUniqueJumpsFound;
		return 0;
	case COMMAND_SET_UNIQUE_JUMPS_TOTAL:
		CollectParameters(&m_nIp, 1);
		CStats::TotalNumberOfUniqueJumps = GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI:
		++CStats::PassengersDroppedOffWithTaxi;
		return 0;
	case COMMAND_REGISTER_MONEY_MADE_TAXI:
		CollectParameters(&m_nIp, 1);
		CStats::MoneyMadeWithTaxi += GET_INTEGER_PARAM(0);
		return 0;
	case COMMAND_REGISTER_MISSION_GIVEN:
		++CStats::MissionsGiven;
		return 0;
	case COMMAND_REGISTER_MISSION_PASSED:
	{
		char name[KEY_LENGTH_IN_SCRIPT];
		strncpy(name, (const char*)&CTheScripts::ScriptSpace[m_nIp], KEY_LENGTH_IN_SCRIPT);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		strncpy(CStats::LastMissionPassedName, name, KEY_LENGTH_IN_SCRIPT);
		++CStats::MissionsPassed;
		CStats::CheckPointReachedSuccessfully();
		CTheScripts::LastMissionPassedTime = CTimer::GetTimeInMilliseconds();
		CGameLogic::RemoveShortCutDropOffPointForMission();
		return 0;
	}
	case COMMAND_SET_CHAR_RUNNING:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pPed);
		pPed->bIsRunning = (GET_INTEGER_PARAM(1) != 0);
		return 0;
	}
	case COMMAND_REMOVE_ALL_SCRIPT_FIRES:
		gFireManager.RemoveAllScriptFires();
		return 0;
	/*
	case COMMAND_IS_FIRST_CAR_COLOUR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->m_currentColour1 == GET_INTEGER_PARAM(1));
		return 0;
	}
	case COMMAND_IS_SECOND_CAR_COLOUR:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		script_assert(pVehicle);
		UpdateCompareFlag(pVehicle->m_currentColour2 == GET_INTEGER_PARAM(1));
		return 0;
	}
	*/
	case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		bool result = false;
		if (!pPed)
			printf("HAS_CHAR_BEEN_DAMAGED_BY_WEAPON - Character doesn't exist\n");
		else {
			if (GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYMELEE || GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYWEAPON)
				result = CheckDamagedWeaponType(pPed->m_lastWepDam, GET_INTEGER_PARAM(1));
			else
				result = GET_INTEGER_PARAM(1) == pPed->m_lastWepDam;
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_WEAPON:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(GET_INTEGER_PARAM(0));
		bool result = false;
		if (!pVehicle)
			printf("HAS_CAR_BEEN_DAMAGED_BY_WEAPON - Vehicle doesn't exist\n");
		else {
			if (GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYMELEE || GET_INTEGER_PARAM(1) == WEAPONTYPE_ANYWEAPON)
				result = CheckDamagedWeaponType(pVehicle->m_nLastWeaponDamage, GET_INTEGER_PARAM(1));
			else
				result = GET_INTEGER_PARAM(1) == pVehicle->m_nLastWeaponDamage;
		}
		UpdateCompareFlag(result);
		return 0;
	}
	case COMMAND_IS_CHAR_IN_CHARS_GROUP:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(0));
		CPed* pLeader = CPools::GetPedPool()->GetAt(GET_INTEGER_PARAM(1));
		script_assert(pPed);
		script_assert(pLeader);
		UpdateCompareFlag(pPed->m_leader == pLeader && !pPed->bWaitForLeaderToComeCloser);
		return 0;
	}
	default:
		script_assert(0);
	}
	return -1;
}
