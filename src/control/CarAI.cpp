#include "common.h"
#include "patcher.h"
#include "CarAI.h"

#include "AccidentManager.h"
#include "AutoPilot.h"
#include "CarCtrl.h"
#include "General.h"
#include "ModelIndices.h"
#include "PlayerPed.h"
#include "Timer.h"
#include "TrafficLights.h"
#include "Vehicle.h"
#include "World.h"
#include "ZoneCull.h"

#define DISTANCE_TO_SWITCH_DISTANCE_GOTO 20.0f

float CCarAI::FindSwitchDistanceClose(CVehicle*)
{
	return 30.0f;
}

float CCarAI::FindSwitchDistanceFar(CVehicle* pVehicle)
{
	return pVehicle->bIsLawEnforcer ? 50.0f : 35.0f;
}

void CCarAI::UpdateCarAI(CVehicle* pVehicle)
{
	//((void(*)(CVehicle*))(0x413E50))(pVehicle);
	//return;
	if (pVehicle->bIsLawEnforcer){
		if (pVehicle->AutoPilot.m_nCarMission == MISSION_BLOCKCAR_FARAWAY ||
			pVehicle->AutoPilot.m_nCarMission == MISSION_RAMPLAYER_FARAWAY ||
			pVehicle->AutoPilot.m_nCarMission == MISSION_BLOCKPLAYER_CLOSE ||
			pVehicle->AutoPilot.m_nCarMission == MISSION_RAMPLAYER_CLOSE)
			pVehicle->AutoPilot.m_nCruiseSpeed = FindPoliceCarSpeedForWantedLevel(pVehicle);
	}
	switch (pVehicle->m_status){
	case STATUS_PLAYER:
	case STATUS_PLAYER_PLAYBACKFROMBUFFER:
	case STATUS_TRAIN_MOVING:
	case STATUS_TRAIN_NOT_MOVING:
	case STATUS_HELI:
	case STATUS_PLANE:
	case STATUS_PLAYER_REMOTE:
	case STATUS_PLAYER_DISABLED:
		break;
	case STATUS_SIMPLE:
	case STATUS_PHYSICS:
		switch (pVehicle->AutoPilot.m_nCarMission) {
		case MISSION_RAMPLAYER_FARAWAY:
			if (FindSwitchDistanceClose(pVehicle) > (FindPlayerCoors() - pVehicle->GetPosition()).Magnitude2D() ||
				pVehicle->AutoPilot.m_bIgnorePathfinding) {
				pVehicle->AutoPilot.m_nCarMission = MISSION_RAMPLAYER_CLOSE;
				if (pVehicle->UsesSiren(pVehicle->GetModelIndex()))
					pVehicle->m_bSirenOrAlarm = true;
			}
			if (FindPlayerPed()->m_pWanted->m_bIgnoredByEveryone || pVehicle->bIsLawEnforcer &&
				(FindPlayerPed()->m_pWanted->m_nWantedLevel == 0 || FindPlayerPed()->m_pWanted->m_bIgnoredByCops || CCullZones::NoPolice())) {
				CCarCtrl::JoinCarWithRoadSystem(pVehicle);
				pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
				pVehicle->m_bSirenOrAlarm = false;
				if (CCullZones::NoPolice())
					pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			break;
		case MISSION_RAMPLAYER_CLOSE:
			if (FindSwitchDistanceFar(pVehicle) < (FindPlayerCoors() - pVehicle->GetPosition()).Magnitude2D() ||
				pVehicle->AutoPilot.m_bIgnorePathfinding) {
				if (FindPlayerVehicle()) {
					if (pVehicle->GetHasCollidedWith(FindPlayerVehicle())) {
						if (pVehicle->AutoPilot.m_nTempAction != TEMPACT_TURNLEFT && pVehicle->AutoPilot.m_nTempAction != TEMPACT_TURNRIGHT) {
							if (FindPlayerVehicle()->GetMoveSpeed().Magnitude() < 0.05f) {
								pVehicle->AutoPilot.m_nTempAction = TEMPACT_REVERSE;
								pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 800;
							}
							else {
								pVehicle->AutoPilot.m_nTempAction = TEMPACT_REVERSE;
								pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 50;
							}
						}
					}
				}
				if (FindPlayerVehicle() && FindPlayerVehicle()->GetMoveSpeed().Magnitude() < 0.05f)
#ifdef FIX_BUGS
					pVehicle->m_nTimeBlocked += CTimer::GetTimeStepInMilliseconds();
#else
					pVehicle->m_nTimeBlocked += 1000.0f / 60.0f * CTimer::GetTimeStep();
#endif
				else
					pVehicle->m_nTimeBlocked = 0;
				if (!FindPlayerVehicle() || FindPlayerVehicle()->IsUpsideDown() ||
					FindPlayerVehicle()->GetMoveSpeed().Magnitude() < 0.05f && pVehicle->m_nTimeBlocked > 2500) {
					if (pVehicle->bIsLawEnforcer &&
						(pVehicle->GetModelIndex() != MI_RHINO || pVehicle->m_randomSeed > 10000) &&
						(FindPlayerCoors() - pVehicle->GetPosition()).Magnitude2D() < 10.0f) {
						TellOccupantsToLeaveCar(pVehicle);
						pVehicle->AutoPilot.m_nCruiseSpeed = 0;
						pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
						if (FindPlayerPed()->m_pWanted->m_nWantedLevel <= 1)
							pVehicle->m_bSirenOrAlarm = false;
					}
				}
			}
			else if (!CCarCtrl::JoinCarWithRoadSystemGotoCoors(pVehicle, FindPlayerCoors(), true)){
				pVehicle->AutoPilot.m_nCarMission = MISSION_RAMPLAYER_FARAWAY;
				pVehicle->m_bSirenOrAlarm = false;
				pVehicle->m_nCarHornTimer = 0;
			}
			if (FindPlayerPed()->m_pWanted->m_bIgnoredByEveryone || pVehicle->bIsLawEnforcer &&
				(FindPlayerPed()->m_pWanted->m_nWantedLevel == 0 || FindPlayerPed()->m_pWanted->m_bIgnoredByCops || CCullZones::NoPolice())){
				CCarCtrl::JoinCarWithRoadSystem(pVehicle);
				pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
				pVehicle->m_bSirenOrAlarm = false;
				if (CCullZones::NoPolice())
					pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			else if (pVehicle->bIsLawEnforcer)
				MellowOutChaseSpeed(pVehicle);
			break;
		case MISSION_BLOCKPLAYER_FARAWAY:
			if (FindSwitchDistanceClose(pVehicle) > (FindPlayerCoors() - pVehicle->GetPosition()).Magnitude2D() ||
				pVehicle->AutoPilot.m_bIgnorePathfinding) {
				pVehicle->AutoPilot.m_nCarMission = MISSION_BLOCKPLAYER_CLOSE;
				if (pVehicle->UsesSiren(pVehicle->GetModelIndex()))
					pVehicle->m_bSirenOrAlarm = true;
			}
			if (FindPlayerPed()->m_pWanted->m_bIgnoredByEveryone || pVehicle->bIsLawEnforcer &&
				(FindPlayerPed()->m_pWanted->m_nWantedLevel == 0 || FindPlayerPed()->m_pWanted->m_bIgnoredByCops || CCullZones::NoPolice())) {
				CCarCtrl::JoinCarWithRoadSystem(pVehicle);
				pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
				pVehicle->m_bSirenOrAlarm = false;
				if (CCullZones::NoPolice())
					pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			break;
		case MISSION_BLOCKPLAYER_CLOSE:
			if (FindSwitchDistanceFar(pVehicle) < (FindPlayerCoors() - pVehicle->GetPosition()).Magnitude2D() ||
				pVehicle->AutoPilot.m_bIgnorePathfinding) {
				if (FindPlayerVehicle() && FindPlayerVehicle()->GetMoveSpeed().Magnitude() < 0.05f)
#ifdef FIX_BUGS
					pVehicle->m_nTimeBlocked += CTimer::GetTimeStepInMilliseconds();
#else
					pVehicle->m_nTimeBlocked += 1000.0f / 60.0f * CTimer::GetTimeStep();
#endif
				else
					pVehicle->m_nTimeBlocked = 0;
				if (!FindPlayerVehicle() || FindPlayerVehicle()->IsUpsideDown() ||
					FindPlayerVehicle()->GetMoveSpeed().Magnitude() < 0.05f && pVehicle->m_nTimeBlocked > 2500) {
					if (pVehicle->bIsLawEnforcer &&
						(pVehicle->GetModelIndex() != MI_RHINO || pVehicle->m_randomSeed > 10000) &&
						(FindPlayerCoors() - pVehicle->GetPosition()).Magnitude2D() < 10.0f) {
						TellOccupantsToLeaveCar(pVehicle);
						pVehicle->AutoPilot.m_nCruiseSpeed = 0;
						pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
						if (FindPlayerPed()->m_pWanted->m_nWantedLevel <= 1)
							pVehicle->m_bSirenOrAlarm = false;
					}
				}
			}else if (!CCarCtrl::JoinCarWithRoadSystemGotoCoors(pVehicle, FindPlayerCoors(), true)) {
				pVehicle->AutoPilot.m_nCarMission = MISSION_BLOCKPLAYER_FARAWAY;
				pVehicle->m_bSirenOrAlarm = false;
				pVehicle->m_nCarHornTimer = 0;
			}
			if (FindPlayerPed()->m_pWanted->m_bIgnoredByEveryone || pVehicle->bIsLawEnforcer &&
				(FindPlayerPed()->m_pWanted->m_nWantedLevel == 0 || FindPlayerPed()->m_pWanted->m_bIgnoredByCops || CCullZones::NoPolice())) {
				CCarCtrl::JoinCarWithRoadSystem(pVehicle);
				pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
				pVehicle->m_bSirenOrAlarm = false;
				if (CCullZones::NoPolice())
					pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			else if (pVehicle->bIsLawEnforcer)
				MellowOutChaseSpeed(pVehicle);
			break;
		case MISSION_GOTOCOORDS:
			if ((pVehicle->AutoPilot.m_vecDestinationCoors - pVehicle->GetPosition()).Magnitude2D() < DISTANCE_TO_SWITCH_DISTANCE_GOTO ||
			  pVehicle->AutoPilot.m_bIgnorePathfinding)
				pVehicle->AutoPilot.m_nCarMission = MISSION_GOTOCOORDS_STRAIGHT;
			break;
		case MISSION_GOTOCOORDS_STRAIGHT:
		{
			float distance = (pVehicle->AutoPilot.m_vecDestinationCoors - pVehicle->GetPosition()).Magnitude2D();
			if ((pVehicle->bIsAmbulanceOnDuty || pVehicle->bIsFireTruckOnDuty) && distance < 20.0f)
				pVehicle->AutoPilot.m_nCarMission = MISSION_EMERGENCYVEHICLE_STOP;
			if (distance < 5.0f){
				pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
				pVehicle->AutoPilot.m_nTempAction = TEMPACT_NONE;
			}
			else if (distance > 35.0f && !pVehicle->AutoPilot.m_bIgnorePathfinding && (CTimer::GetFrameCounter() & 7) == 0){
				pVehicle->AutoPilot.m_nTempAction = TEMPACT_NONE;
				pVehicle->AutoPilot.m_nCarMission = (CCarCtrl::JoinCarWithRoadSystemGotoCoors(pVehicle, pVehicle->AutoPilot.m_vecDestinationCoors, true)) ?
					MISSION_GOTOCOORDS_STRAIGHT : MISSION_GOTOCOORDS;
			}
			break;
		}
		case MISSION_EMERGENCYVEHICLE_STOP:
			if (pVehicle->GetMoveSpeed().Magnitude2D() < 0.01f){
				if (pVehicle->bIsAmbulanceOnDuty){
					float distance = 30.0f;
					if (gAccidentManager.FindNearestAccident(pVehicle->AutoPilot.m_vecDestinationCoors, &distance)){
						TellOccupantsToLeaveCar(pVehicle);
						pVehicle->AutoPilot.m_nCarMission = MISSION_STOP_FOREVER;
					}else{
						CCarCtrl::JoinCarWithRoadSystem(pVehicle);
						pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
						pVehicle->m_bSirenOrAlarm = false;
						pVehicle->AutoPilot.m_nCruiseSpeed = 17;
						if (pVehicle->bIsAmbulanceOnDuty){
							pVehicle->bIsAmbulanceOnDuty = false;
							--CCarCtrl::NumAmbulancesOnDuty;
						}
					}
				}
				if (pVehicle->bIsFireTruckOnDuty) {
					float distance = 30.0f;
					if (gFireManager.FindNearestFire(pVehicle->AutoPilot.m_vecDestinationCoors, &distance)) {
						TellOccupantsToLeaveCar(pVehicle);
						pVehicle->AutoPilot.m_nCarMission = MISSION_STOP_FOREVER;
					}
					else {
						CCarCtrl::JoinCarWithRoadSystem(pVehicle);
						pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
						pVehicle->m_bSirenOrAlarm = false;
						pVehicle->AutoPilot.m_nCruiseSpeed = 17;
						if (pVehicle->bIsFireTruckOnDuty) {
							pVehicle->bIsFireTruckOnDuty = false;
							--CCarCtrl::NumFiretrucksOnDuty;
						}
					}
				}
			}
			break;
		case MISSION_GOTOCOORDS_ACCURATE:
			if ((pVehicle->AutoPilot.m_vecDestinationCoors - pVehicle->GetPosition()).Magnitude2D() < 20.0f ||
			  pVehicle->AutoPilot.m_bIgnorePathfinding)
				pVehicle->AutoPilot.m_nCarMission = MISSION_GOTO_COORDS_STRAIGHT_ACCURATE;
			break;
		case MISSION_GOTO_COORDS_STRAIGHT_ACCURATE:
		{
			float distance = (pVehicle->AutoPilot.m_vecDestinationCoors - pVehicle->GetPosition()).Magnitude2D();
			if (distance < 1.0f) {
				pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
				pVehicle->AutoPilot.m_nTempAction = TEMPACT_NONE;
			}
			else if (distance > 35.0f && !pVehicle->AutoPilot.m_bIgnorePathfinding && (CTimer::GetFrameCounter() & 7) == 0) {
				pVehicle->AutoPilot.m_nTempAction = TEMPACT_NONE;
				pVehicle->AutoPilot.m_nCarMission = (CCarCtrl::JoinCarWithRoadSystemGotoCoors(pVehicle, pVehicle->AutoPilot.m_vecDestinationCoors, true)) ?
					MISSION_GOTOCOORDS_STRAIGHT : MISSION_GOTOCOORDS;
			}
			break;
		}
		case MISSION_RAMCAR_FARAWAY:
			if (pVehicle->AutoPilot.m_pTargetCar){
				if ((pVehicle->GetPosition() - pVehicle->AutoPilot.m_pTargetCar->GetPosition()).Magnitude2D() < FindSwitchDistanceClose(pVehicle) ||
				  pVehicle->AutoPilot.m_bIgnorePathfinding)
					pVehicle->AutoPilot.m_nCarMission = MISSION_RAMCAR_CLOSE;
			}else{
				pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			break;
		case MISSION_RAMCAR_CLOSE:
			if (pVehicle->AutoPilot.m_pTargetCar){
				/* PlayerPed? */
				if (FindPlayerPed()->m_pWanted->m_bIgnoredByEveryone || pVehicle->bIsLawEnforcer &&
				  (FindPlayerPed()->m_pWanted->m_nWantedLevel == 0 || FindPlayerPed()->m_pWanted->m_bIgnoredByCops || CCullZones::NoPolice())){
					CCarCtrl::JoinCarWithRoadSystem(pVehicle);
					pVehicle->AutoPilot.m_nCarMission = MISSION_CRUISE;
					pVehicle->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_STOP_FOR_CARS;
					pVehicle->m_bSirenOrAlarm = false;
					if (CCullZones::NoPolice())
						pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
				}
				if ((pVehicle->AutoPilot.m_pTargetCar->GetPosition() - pVehicle->GetPosition()).Magnitude2D() <= FindSwitchDistanceFar(pVehicle) ||
				  pVehicle->AutoPilot.m_bIgnorePathfinding){
					if (pVehicle->GetHasCollidedWith(pVehicle->AutoPilot.m_pTargetCar)){
						if (pVehicle->GetMoveSpeed().Magnitude() < 0.04f){
							pVehicle->AutoPilot.m_nTempAction = TEMPACT_REVERSE;
							pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 800;
						}
					}
				}else{
					pVehicle->AutoPilot.m_nCarMission = MISSION_RAMCAR_FARAWAY;
					CCarCtrl::JoinCarWithRoadSystem(pVehicle);
				}
			}else{
				pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			break;
		case MISSION_BLOCKCAR_FARAWAY:
			if (pVehicle->AutoPilot.m_pTargetCar){
				if ((pVehicle->AutoPilot.m_pTargetCar->GetPosition() - pVehicle->GetPosition()).Magnitude2D() < FindSwitchDistanceClose(pVehicle) ||
				  pVehicle->AutoPilot.m_bIgnorePathfinding){
					pVehicle->AutoPilot.m_nCarMission = MISSION_BLOCKCAR_CLOSE;
					if (pVehicle->UsesSiren(pVehicle->GetModelIndex()))
						pVehicle->m_bSirenOrAlarm = true;
				}
			}else{
				pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			break;
		case MISSION_BLOCKCAR_CLOSE:
			if (pVehicle->AutoPilot.m_pTargetCar){
				if ((pVehicle->AutoPilot.m_pTargetCar->GetPosition() - pVehicle->GetPosition()).Magnitude2D() > FindSwitchDistanceFar(pVehicle) &&
				  !pVehicle->AutoPilot.m_bIgnorePathfinding){
					pVehicle->AutoPilot.m_nCarMission = MISSION_BLOCKCAR_FARAWAY;
					pVehicle->m_bSirenOrAlarm = false;
					pVehicle->m_nCarHornTimer = 0;
					CCarCtrl::JoinCarWithRoadSystem(pVehicle);
				}
			}else{
				pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
			}
			break;
		default:
			if (pVehicle->bIsLawEnforcer && FindPlayerPed()->m_pWanted->m_nWantedLevel > 0 && !CCullZones::NoPolice()){
				if (ABS(FindPlayerCoors().x - pVehicle->GetPosition().x) > 10.0f ||
				  ABS(FindPlayerCoors().y - pVehicle->GetPosition().y) > 10.0f){
					pVehicle->AutoPilot.m_nCruiseSpeed = FindPoliceCarSpeedForWantedLevel(pVehicle);
					pVehicle->m_status = STATUS_PHYSICS;
					pVehicle->AutoPilot.m_nCarMission = FindPoliceCarMissionForWantedLevel();
					pVehicle->AutoPilot.m_nTempAction = TEMPACT_NONE;
					pVehicle->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
				}else if (pVehicle->AutoPilot.m_nCarMission == MISSION_CRUISE){
					pVehicle->m_status = STATUS_PHYSICS;
					TellOccupantsToLeaveCar(pVehicle);
					pVehicle->AutoPilot.m_nCruiseSpeed = 0;
					pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
					if (FindPlayerPed()->m_pWanted->m_nWantedLevel <= 1)
						pVehicle->m_bSirenOrAlarm = false;
				}
			}
			break;
		}
		break;
	case STATUS_ABANDONED:
	case STATUS_WRECKED:
		pVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
		pVehicle->AutoPilot.m_nCruiseSpeed = 0;
		break;
	}
	float flatSpeed = pVehicle->GetMoveSpeed().MagnitudeSqr2D();
	if (flatSpeed > SQR(0.018f)){
		pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds();
		pVehicle->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
	}
	if (pVehicle->m_status == STATUS_PHYSICS && pVehicle->AutoPilot.m_nTempAction == TEMPACT_NONE){
		if (pVehicle->AutoPilot.m_nCarMission != MISSION_NONE){
			if (pVehicle->AutoPilot.m_nCarMission != MISSION_STOP_FOREVER &&
			  pVehicle->AutoPilot.m_nCruiseSpeed != 0 &&
			  (pVehicle->VehicleCreatedBy != RANDOM_VEHICLE || pVehicle->AutoPilot.m_nCarMission != MISSION_CRUISE)){
				if (pVehicle->AutoPilot.m_nDrivingStyle != DRIVINGSTYLE_STOP_FOR_CARS){
					if (CTimer::GetTimeInMilliseconds() - pVehicle->m_nLastTimeCollided > 500)
						pVehicle->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
					if (flatSpeed < SQR(0.018f) && CTimer::GetTimeInMilliseconds() - pVehicle->AutoPilot.m_nAntiReverseTimer > 2000){
						pVehicle->AutoPilot.m_nTempAction = TEMPACT_REVERSE;
						if (pVehicle->AutoPilot.m_nCarMission != MISSION_NONE &&
						  pVehicle->AutoPilot.m_nCarMission != MISSION_CRUISE || pVehicle->VehicleCreatedBy == RANDOM_VEHICLE)
							pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 1500;
						else
							pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 750;
						pVehicle->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
						if (pVehicle->VehicleCreatedBy == RANDOM_VEHICLE)
							pVehicle->AutoPilot.m_nDrivingStyle = max(DRIVINGSTYLE_AVOID_CARS, pVehicle->AutoPilot.m_nDrivingStyle);
						pVehicle->PlayCarHorn();
					}
				}
			}
		}
	}
	if ((pVehicle->m_randomSeed & 7) == 0){
		if (CTimer::GetTimeInMilliseconds() - pVehicle->AutoPilot.m_nTimeTempAction > 30000 &&
		  CTimer::GetPreviousTimeInMilliseconds() - pVehicle->AutoPilot.m_nTimeTempAction <= 30000 &&
		  pVehicle->AutoPilot.m_nCarMission == MISSION_CRUISE &&
		  !CTrafficLights::ShouldCarStopForBridge(pVehicle)){
			pVehicle->m_status = STATUS_PHYSICS;
			CCarCtrl::SwitchVehicleToRealPhysics(pVehicle);
			pVehicle->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
			pVehicle->AutoPilot.m_nTempAction = TEMPACT_REVERSE;
			pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 400;
		}
	}
	if (pVehicle->GetUp().z < 0.7f){
		pVehicle->AutoPilot.m_nTempAction = TEMPACT_WAIT;
		pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 1000;
	}
	if (pVehicle->AutoPilot.m_nTempAction == TEMPACT_NONE){
		switch (pVehicle->AutoPilot.m_nCarMission){
		case MISSION_RAMPLAYER_FARAWAY:
		case MISSION_RAMPLAYER_CLOSE:
		case MISSION_BLOCKPLAYER_FARAWAY:
		case MISSION_BLOCKPLAYER_CLOSE:
			if (FindPlayerSpeed().Magnitude() > pVehicle->GetMoveSpeed().Magnitude()){
				if (FindPlayerSpeed().Magnitude() > 0.1f){
					if (DotProduct2D(FindPlayerVehicle()->GetForward(), pVehicle->GetForward()) > 0.0f){
						CVector2D dist = pVehicle->GetPosition() - FindPlayerCoors();
						CVector2D speed = FindPlayerSpeed();
						if (0.5f * dist.Magnitude() * speed.Magnitude() < DotProduct2D(dist, speed)){
							if ((FindPlayerCoors() - pVehicle->GetPosition()).Magnitude() > 12.0f){
								pVehicle->AutoPilot.m_nTempAction = TEMPACT_WAIT;
								pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 500;
							}
						}
					}
				}
			}
			break;
		}
	}
	if (pVehicle->pDriver && pVehicle->pDriver->m_objective == OBJECTIVE_KILL_CHAR_ANY_MEANS){
		if ((pVehicle->GetPosition() - FindPlayerCoors()).Magnitude() < 15.0f){
			if (!FindPlayerVehicle() || pVehicle->GetHasCollidedWith(FindPlayerVehicle())){
				pVehicle->AutoPilot.m_nTempAction = TEMPACT_WAIT;
				pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 3000;
			}
		}
	}
	if (pVehicle->m_bSirenOrAlarm){
		if ((uint8)(pVehicle->m_randomSeed ^ CGeneral::GetRandomNumber()) == 0xAD)
			pVehicle->m_nCarHornTimer = 45;
	}
}

void CCarAI::CarHasReasonToStop(CVehicle* pVehicle)
{
	pVehicle->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
}

WRAPPER float CCarAI::GetCarToGoToCoors(CVehicle*, CVector*) { EAXJMP(0x413E50); }
WRAPPER void CCarAI::AddPoliceOccupants(CVehicle*) { EAXJMP(0x415C60); }
WRAPPER void CCarAI::AddAmbulanceOccupants(CVehicle*) { EAXJMP(0x415CE0); }
WRAPPER void CCarAI::AddFiretruckOccupants(CVehicle*) { EAXJMP(0x415D00); }
WRAPPER void CCarAI::TellOccupantsToLeaveCar(CVehicle*) { EAXJMP(0x415D20); }
WRAPPER void CCarAI::TellCarToRamOtherCar(CVehicle*, CVehicle*) { EAXJMP(0x415D90); }
WRAPPER void CCarAI::TellCarToBlockOtherCar(CVehicle*, CVehicle*) { EAXJMP(0x415DE0); }
WRAPPER eCarMission CCarAI::FindPoliceCarMissionForWantedLevel() { EAXJMP(0x415E30); }
WRAPPER int32 CCarAI::FindPoliceCarSpeedForWantedLevel(CVehicle*) { EAXJMP(0x415EB0); }
WRAPPER void CCarAI::MellowOutChaseSpeed(CVehicle*) { EAXJMP(0x416050); }
WRAPPER void CCarAI::MakeWayForCarWithSiren(CVehicle *veh) { EAXJMP(0x416280); }

STARTPATCHES
ENDPATCHES