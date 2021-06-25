#include "common.h"

#include "main.h"
#include "Particle.h"
#include "RpAnimBlend.h"
#include "Ped.h"
#include "Wanted.h"
#include "AnimBlendAssociation.h"
#include "DMAudio.h"
#include "General.h"
#include "HandlingMgr.h"
#include "Replay.h"
#include "Camera.h"
#include "PedPlacement.h"
#include "ZoneCull.h"
#include "Pad.h"
#include "Pickups.h"
#include "Train.h"
#include "PedRoutes.h"
#include "CopPed.h"
#include "Script.h"
#include "CarCtrl.h"
#include "WaterLevel.h"
#include "CarAI.h"
#include "Zones.h"
#include "Cranes.h"
#include "PedAttractor.h"
#include "Bike.h"
#include "Weather.h"
#include "GameLogic.h"
#include "Streaming.h"

CVector vecPedCarDoorAnimOffset;
CVector vecPedCarDoorLoAnimOffset;
CVector vecPedVanRearDoorAnimOffset;
CVector vecPedQuickDraggedOutCarAnimOffset;
CVector vecPedDraggedOutCarAnimOffset;
CVector vecPedTrainDoorAnimOffset;
CVector vecPedStdBikeJumpRhsAnimOffset;
CVector vecPedVespaBikeJumpRhsAnimOffset;
CVector vecPedHarleyBikeJumpRhsAnimOffset;
CVector vecPedDirtBikeJumpRhsAnimOffset;
CVector vecPedBikeKickAnimOffset;

void
CPed::SetObjectiveTimer(int time)
{
	if (time == 0) {
		m_objectiveTimer = 0;
	} else if (CTimer::GetTimeInMilliseconds() > m_objectiveTimer) {
		m_objectiveTimer = CTimer::GetTimeInMilliseconds() + time;
	}
}

void
CPed::SetStoredObjective(void)
{
	if (m_objective == m_prevObjective)
		return;

	switch (m_objective) {
		case OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_KILL_CHAR_ON_FOOT:
		case OBJECTIVE_KILL_CHAR_ANY_MEANS:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING:
		case OBJECTIVE_HASSLE_CHAR:
		case OBJECTIVE_FOLLOW_CHAR_IN_FORMATION:
		case OBJECTIVE_LEAVE_CAR:
		case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
		case OBJECTIVE_ENTER_CAR_AS_DRIVER:
		case OBJECTIVE_GOTO_AREA_ON_FOOT:
		case OBJECTIVE_RUN_TO_AREA:
		case OBJECTIVE_GOTO_SEAT_ON_FOOT:
		case OBJECTIVE_GOTO_ATM_ON_FOOT:
		case OBJECTIVE_GOTO_BUS_STOP_ON_FOOT:
		case OBJECTIVE_GOTO_PIZZA_ON_FOOT:
		case OBJECTIVE_GOTO_SHELTER_ON_FOOT:
		case OBJECTIVE_SPRINT_TO_AREA:
		case OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT:
			return;
		default:
			m_prevObjective = m_objective;
	}
}

void
CPed::ForceStoredObjective(eObjective objective)
{
	if (objective != OBJECTIVE_ENTER_CAR_AS_DRIVER && objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER) {
		m_prevObjective = m_objective;
		return;
	}

	switch (m_objective) {
		case OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_KILL_CHAR_ON_FOOT:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING:
		case OBJECTIVE_HASSLE_CHAR:
		case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
		case OBJECTIVE_ENTER_CAR_AS_DRIVER:
		case OBJECTIVE_GOTO_AREA_ON_FOOT:
		case OBJECTIVE_RUN_TO_AREA:
		case OBJECTIVE_GOTO_SEAT_ON_FOOT:
		case OBJECTIVE_GOTO_ATM_ON_FOOT:
		case OBJECTIVE_GOTO_BUS_STOP_ON_FOOT:
		case OBJECTIVE_GOTO_PIZZA_ON_FOOT:
		case OBJECTIVE_GOTO_SHELTER_ON_FOOT:
		case OBJECTIVE_SPRINT_TO_AREA:
		case OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT:
			return;
		default:
			m_prevObjective = m_objective;
	}
}

bool
CPed::IsTemporaryObjective(eObjective objective)
{
	return objective == OBJECTIVE_LEAVE_CAR || objective == OBJECTIVE_SET_LEADER ||
		objective == OBJECTIVE_LEAVE_CAR_AND_DIE || objective == OBJECTIVE_ENTER_CAR_AS_DRIVER ||
		objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER;
}

void
CPed::SetObjective(eObjective newObj)
{
	if (DyingOrDead() || m_attachedTo)
		return;

	if (newObj == OBJECTIVE_NONE) {
		if ((m_objective == OBJECTIVE_LEAVE_CAR || m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER
			|| m_objective == OBJECTIVE_LEAVE_CAR_AND_DIE) && !IsPlayer() && !IsPedInControl()) {

			bStartWanderPathOnFoot = true;
		} else {
			m_objective = OBJECTIVE_NONE;
			m_prevObjective = OBJECTIVE_NONE;
		}
	} else if (m_prevObjective != newObj || m_prevObjective == OBJECTIVE_NONE) {
		SetObjectiveTimer(0);

		if (m_objective == newObj)
			return;

		if (IsTemporaryObjective(m_objective)) {
			m_prevObjective = newObj;
		} else {
			if (m_objective != newObj)
				SetStoredObjective();

			m_objective = newObj;
		}
		bObjectiveCompleted = false;

		switch (newObj) {
			case OBJECTIVE_NONE:
				m_prevObjective = OBJECTIVE_NONE;
				break;
			case OBJECTIVE_HAIL_TAXI:
				m_nWaitTimer = 0;
				SetIdle();
				SetMoveState(PEDMOVE_STILL);
				break;
			default:
				break;
		}
	}
}

void
CPed::SetObjective(eObjective newObj, void *entity)
{
	if (DyingOrDead())
		return;

	if (m_prevObjective == newObj && m_prevObjective != OBJECTIVE_NONE)
		return;

	if (entity == this)
		return;

	if (m_attachedTo && newObj != OBJECTIVE_KILL_CHAR_ON_FOOT && newObj != OBJECTIVE_KILL_CHAR_ANY_MEANS && newObj != OBJECTIVE_DESTROY_OBJECT && newObj != OBJECTIVE_DESTROY_CAR)
		return;

	if (m_objective == newObj) {
		switch (newObj) {
			case OBJECTIVE_KILL_CHAR_ON_FOOT:
			case OBJECTIVE_KILL_CHAR_ANY_MEANS:
			case OBJECTIVE_GOTO_CHAR_ON_FOOT:
			case OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING:
			case OBJECTIVE_HASSLE_CHAR:
			case OBJECTIVE_FOLLOW_CHAR_IN_FORMATION:
			case OBJECTIVE_GOTO_AREA_ANY_MEANS:
			case OBJECTIVE_GUARD_ATTACK:
			case OBJECTIVE_KILL_CHAR_ON_BOAT:
			case OBJECTIVE_SOLICIT_FOOT:
				if (m_pedInObjective == entity)
					return;
				break;
			case OBJECTIVE_LEAVE_CAR:
			case OBJECTIVE_FLEE_CAR:
			case OBJECTIVE_LEAVE_CAR_AND_DIE:
				return;
			case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
			case OBJECTIVE_ENTER_CAR_AS_DRIVER:
			case OBJECTIVE_DESTROY_CAR:
			case OBJECTIVE_SOLICIT_VEHICLE:
			case OBJECTIVE_BUY_ICE_CREAM:
				if (m_carInObjective == entity)
					return;

				if (newObj == OBJECTIVE_BUY_ICE_CREAM && bBoughtIceCream)
					return;

				break;
			case OBJECTIVE_SET_LEADER:
				if (m_leader == entity)
					return;
				break;
			case OBJECTIVE_AIM_GUN_AT:
				if (m_pedInObjective == entity)
					return;
				break;
			default:
				break;
		}
	} else {
		if (newObj != OBJECTIVE_WAIT_IN_CAR_THEN_GET_OUT && (newObj == OBJECTIVE_LEAVE_CAR || newObj == OBJECTIVE_LEAVE_CAR_AND_DIE)
			&& !bInVehicle)
			return;
	}

	bObjectiveCompleted = false;
	ClearPointGunAt();
	m_objectiveTimer = 0;
	if (IsTemporaryObjective(m_objective) && !IsTemporaryObjective(newObj)) {
		m_prevObjective = newObj;
	} else {
		if (m_objective != newObj) {
			if (IsTemporaryObjective(newObj))
				ForceStoredObjective(newObj);
			else
				SetStoredObjective();
		}
		m_objective = newObj;
	}

	switch (newObj) {
		case OBJECTIVE_WAIT_ON_FOOT_FOR_COP:
			m_pedInObjective = (CPed*)entity;
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			SetIdle();
			SetLook(m_pedInObjective);
			break;
		case OBJECTIVE_WAIT_IN_CAR_THEN_GET_OUT:

			// In this special case, entity parameter isn't CEntity, but int.
			SetObjectiveTimer((uintptr)entity);
			break;
		case OBJECTIVE_KILL_CHAR_ON_FOOT:
		case OBJECTIVE_KILL_CHAR_ANY_MEANS:
		case OBJECTIVE_MUG_CHAR:
		case OBJECTIVE_KILL_CHAR_ON_BOAT:
			m_pNextPathNode = nil;
			bUsePedNodeSeek = false;

			if (m_pedInObjective)
				m_pedInObjective->CleanUpOldReference((CEntity**)&m_pedInObjective);
			if (m_pLookTarget)
				m_pLookTarget->CleanUpOldReference(&m_pLookTarget);
			
			m_pLookTarget = (CEntity*)entity;
			m_pedInObjective = (CPed*)entity;
			m_vecSeekPos = CVector(0.0f, 0.0f, 0.0f);
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			// m_pLookTarget = (CEntity*)entity; // duplicate
			m_pLookTarget->RegisterReference((CEntity**)&m_pLookTarget);
			break;
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING:
		case OBJECTIVE_HASSLE_CHAR:
		case OBJECTIVE_GUARD_ATTACK:

			if (m_pedInObjective)
				m_pedInObjective->CleanUpOldReference((CEntity**)&m_pedInObjective);
			m_pedInObjective = (CPed*)entity;
			m_vecSeekPos = CVector(0.0f, 0.0f, 0.0f);
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			break;
		case OBJECTIVE_FOLLOW_CHAR_IN_FORMATION:
			m_pedInObjective = (CPed*)entity;
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			m_pedFormation = FORMATION_REAR;
			break;
		case OBJECTIVE_LEAVE_CAR:
		case OBJECTIVE_LEAVE_CAR_AND_DIE:
		case OBJECTIVE_FLEE_CAR:
			m_carInObjective = (CVehicle*)entity;
			m_carInObjective->RegisterReference((CEntity **)&m_carInObjective);
			if (m_carInObjective->bIsBus && m_leaveCarTimer == 0) {
				for (int i = 0; i < m_carInObjective->m_nNumMaxPassengers; i++) {
					if (m_carInObjective->pPassengers[i] == this) {
						m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 1200 * i;
						break;
					}
				}
			}

			break;
		case OBJECTIVE_DESTROY_OBJECT:
			SetWeaponLockOnTarget((CEntity*)entity);
			break;
		case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
		case OBJECTIVE_ENTER_CAR_AS_DRIVER:
			if (m_nMoveState == PEDMOVE_STILL)
				SetMoveState(PEDMOVE_RUN);

			if (((CVehicle*)entity)->IsBoat() && !IsPlayer() && m_pCurrentPhysSurface != entity) {
				RestorePreviousObjective();
				break;
			}
			// fall through
		case OBJECTIVE_DESTROY_CAR:
		case OBJECTIVE_SOLICIT_VEHICLE:
		case OBJECTIVE_BUY_ICE_CREAM:
			m_carInObjective = (CVehicle*)entity;
			m_carInObjective->RegisterReference((CEntity**)&m_carInObjective);
			m_pSeekTarget = m_carInObjective;
			m_pSeekTarget->RegisterReference((CEntity**)&m_pSeekTarget);
			m_vecSeekPos = CVector(0.0f, 0.0f, 0.0f);
			if (newObj == OBJECTIVE_SOLICIT_VEHICLE) {
				m_objectiveTimer = CTimer::GetTimeInMilliseconds() + 10000;
			} else if (m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER && CharCreatedBy == MISSION_CHAR &&
					(m_carInObjective->GetStatus() == STATUS_PLAYER_DISABLED || CPad::GetPad(CWorld::PlayerInFocus)->ArePlayerControlsDisabled())) {
				SetObjectiveTimer(14000);
			} else {
				m_objectiveTimer = 0;
			}
			break;
		case OBJECTIVE_SET_LEADER:
			SetLeader((CEntity*)entity);
			RestorePreviousObjective();
			break;
		case OBJECTIVE_AIM_GUN_AT:
			m_pedInObjective = (CPed*)entity;
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			break;
		case OBJECTIVE_SOLICIT_FOOT:
			m_pedInObjective = (CPed*)entity;
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			break;
		default:
			break;
	}
}

void
CPed::SetObjective(eObjective newObj, CVector dest, float safeDist)
{
	if (DyingOrDead())
		return;

	if (m_prevObjective != OBJECTIVE_NONE && m_prevObjective == newObj)
		return;

	if (m_objective == newObj) {
		if (newObj == OBJECTIVE_GOTO_AREA_ANY_MEANS || newObj == OBJECTIVE_GOTO_AREA_ON_FOOT || newObj == OBJECTIVE_RUN_TO_AREA || newObj == OBJECTIVE_SPRINT_TO_AREA) {
			if (m_nextRoutePointPos == dest && m_distanceToCountSeekDone == safeDist)
				return;
		}
		else if (newObj == OBJECTIVE_GUARD_SPOT) {
			if (m_vecSpotToGuard == dest && m_radiusToGuard == safeDist)
				return;
		}
	}

	ClearPointGunAt();
	SetObjectiveTimer(0);
	bObjectiveCompleted = false;
	if (IsTemporaryObjective(m_objective)) {
		m_prevObjective = newObj;
	}
	else {
		if (m_objective != newObj)
			SetStoredObjective();

		m_objective = newObj;
	}

	if (newObj == OBJECTIVE_GUARD_SPOT) {
		m_vecSpotToGuard = dest;
		m_radiusToGuard = safeDist;
	}
	else if (newObj == OBJECTIVE_GOTO_AREA_ANY_MEANS || newObj == OBJECTIVE_GOTO_AREA_ON_FOOT || newObj == OBJECTIVE_RUN_TO_AREA || newObj == OBJECTIVE_SPRINT_TO_AREA) {
		m_pNextPathNode = nil;
		m_nextRoutePointPos = dest;
		m_vecSeekPos = m_nextRoutePointPos;
		bUsePedNodeSeek = true;
	}
}

// Only used in 01E1: SET_CHAR_OBJ_FOLLOW_ROUTE opcode
// IDA fails very badly in here, puts a fake loop and ignores SetFollowRoute call...
void
CPed::SetObjective(eObjective newObj, int16 routePoint, int16 routeType)
{
	if (DyingOrDead())
		return;

	if (m_prevObjective == newObj && m_prevObjective != OBJECTIVE_NONE)
		return;

	if (m_objective == newObj && newObj == OBJECTIVE_FOLLOW_ROUTE && m_routeLastPoint == routePoint && m_routeType == routeType)
		return;

	ClearPointGunAt();
	SetObjectiveTimer(0);

	bObjectiveCompleted = false;
	if (IsTemporaryObjective(m_objective)) {
		m_prevObjective = newObj;
	} else {
		if (m_objective != newObj)
			SetStoredObjective();

		m_objective = newObj;
	}

	if (newObj == OBJECTIVE_FOLLOW_ROUTE) {
		SetFollowRoute(routePoint, routeType);
	}
}

void
CPed::SetObjective(eObjective newObj, CVector dest)
{
	if (DyingOrDead())
		return;

	if (m_prevObjective != OBJECTIVE_NONE && m_prevObjective == newObj)
		return;

	if (m_objective == newObj) {
		if (newObj == OBJECTIVE_GOTO_AREA_ANY_MEANS || newObj == OBJECTIVE_GOTO_AREA_ON_FOOT || newObj == OBJECTIVE_RUN_TO_AREA || newObj == OBJECTIVE_SPRINT_TO_AREA) {
			if (m_nextRoutePointPos == dest)
				return;
		} else if (newObj == OBJECTIVE_GUARD_SPOT) {
			if (m_vecSpotToGuard == dest)
				return;
		}
	}

	ClearPointGunAt();
	m_objectiveTimer = 0;
	bObjectiveCompleted = false;
	switch (newObj) {
		case OBJECTIVE_GUARD_SPOT:
			m_vecSpotToGuard = dest;
			m_radiusToGuard = 5.0f;
			SetMoveState(PEDMOVE_STILL);
			break;
		case OBJECTIVE_GUARD_AREA:
		case OBJECTIVE_WAIT_IN_CAR:
		case OBJECTIVE_WAIT_IN_CAR_THEN_GET_OUT:
		case OBJECTIVE_KILL_CHAR_ON_FOOT:
		case OBJECTIVE_KILL_CHAR_ANY_MEANS:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING:
		case OBJECTIVE_HASSLE_CHAR:
		case OBJECTIVE_FOLLOW_CHAR_IN_FORMATION:
		case OBJECTIVE_LEAVE_CAR:
		case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
		case OBJECTIVE_ENTER_CAR_AS_DRIVER:
		case OBJECTIVE_FOLLOW_CAR_IN_CAR:
		case OBJECTIVE_FIRE_AT_OBJECT_FROM_VEHICLE:
		case OBJECTIVE_DESTROY_OBJECT:
		case OBJECTIVE_DESTROY_CAR:
		case OBJECTIVE_GOTO_AREA_IN_CAR:
		case OBJECTIVE_FOLLOW_CAR_ON_FOOT_WITH_OFFSET:
		case OBJECTIVE_GUARD_ATTACK:
		case OBJECTIVE_SET_LEADER:
		case OBJECTIVE_FOLLOW_ROUTE:
		case OBJECTIVE_SOLICIT_VEHICLE:
		case OBJECTIVE_HAIL_TAXI:
		case OBJECTIVE_CATCH_TRAIN:
		case OBJECTIVE_BUY_ICE_CREAM:
		case OBJECTIVE_STEAL_ANY_CAR:
		case OBJECTIVE_STEAL_ANY_MISSION_CAR:
		case OBJECTIVE_MUG_CHAR:
		case OBJECTIVE_LEAVE_CAR_AND_DIE:
		case OBJECTIVE_FLEE_CAR:
		case OBJECTIVE_SUN_BATHE:
		case OBJECTIVE_AIM_GUN_AT:
		case OBJECTIVE_WANDER:
		case OBJECTIVE_WAIT_ON_FOOT_AT_SHELTER:
		case OBJECTIVE_KILL_CHAR_ON_BOAT:
		case OBJECTIVE_SOLICIT_FOOT:
		case OBJECTIVE_WAIT_ON_FOOT_AT_BUS_STOP:
			break;
		case OBJECTIVE_GOTO_AREA_ANY_MEANS:
		case OBJECTIVE_GOTO_AREA_ON_FOOT:
		case OBJECTIVE_GOTO_SEAT_ON_FOOT:
		case OBJECTIVE_GOTO_ATM_ON_FOOT:
		case OBJECTIVE_GOTO_BUS_STOP_ON_FOOT:
		case OBJECTIVE_GOTO_PIZZA_ON_FOOT:
		case OBJECTIVE_GOTO_SHELTER_ON_FOOT:
		case OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT:
			bIsRunning = false;
			m_pNextPathNode = nil;
			m_nextRoutePointPos = dest;
			m_vecSeekPos = m_nextRoutePointPos;
			m_distanceToCountSeekDone = 0.5f;
			if (newObj == OBJECTIVE_GOTO_ATM_ON_FOOT) {
				m_distanceToCountSeekDone = m_attractor->GetDistanceToCountSeekDone();
				m_acceptableHeadingOffset = m_attractor->GetAcceptableHeading();
			}
			if (newObj == OBJECTIVE_GOTO_SEAT_ON_FOOT) {
				m_distanceToCountSeekDone = m_attractor->GetDistanceToCountSeekDone();
				m_acceptableHeadingOffset = m_attractor->GetAcceptableHeading();
			}
			if (newObj == OBJECTIVE_GOTO_BUS_STOP_ON_FOOT) {
				m_distanceToCountSeekDone = m_attractor->GetDistanceToCountSeekDone();
				m_acceptableHeadingOffset = m_attractor->GetAcceptableHeading();
			}
			if (newObj == OBJECTIVE_GOTO_PIZZA_ON_FOOT) {
				m_distanceToCountSeekDone = m_attractor->GetDistanceToCountSeekDone();
				m_acceptableHeadingOffset = m_attractor->GetAcceptableHeading();
			}
			if (newObj == OBJECTIVE_GOTO_SHELTER_ON_FOOT) {
				bIsRunning = true;
				m_distanceToCountSeekDone = m_attractor->GetDistanceToCountSeekDone();
				m_acceptableHeadingOffset = m_attractor->GetAcceptableHeading();
			}
			if (newObj == OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT) {
				bIsRunning = true;
				m_distanceToCountSeekDone = m_attractor->GetDistanceToCountSeekDone();
				m_acceptableHeadingOffset = m_attractor->GetAcceptableHeading();
			}
			bUsePedNodeSeek = false;
			if (sq(m_distanceToCountSeekDone) > (m_nextRoutePointPos - GetPosition()).MagnitudeSqr2D()) {
				if (!IsUseAttractorObjective(m_objective))
					return;
				if (Abs(m_fRotationCur - m_attractorHeading) < m_acceptableHeadingOffset)
					return;
			}
			break;
		case OBJECTIVE_RUN_TO_AREA:
		case OBJECTIVE_SPRINT_TO_AREA:
			bIsRunning = true;
			m_pNextPathNode = nil;
			m_nextRoutePointPos = dest;
			m_vecSeekPos = m_nextRoutePointPos;
			m_distanceToCountSeekDone = 0.5f;
			bUsePedNodeSeek = true;
			if (sq(m_distanceToCountSeekDone) > (m_nextRoutePointPos - GetPosition()).MagnitudeSqr2D())
				return;
			break;
		default: break;
	}

	if (IsTemporaryObjective(m_objective)) {
		m_prevObjective = newObj;
	} else {
		if (m_objective != newObj)
			SetStoredObjective();

		m_objective = newObj;
	}
}

void
CPed::SetObjective(eObjective newObj, float heading, const CVector& pos)
{
	switch (newObj) {
	case OBJECTIVE_GOTO_SEAT_ON_FOOT:
	case OBJECTIVE_GOTO_ATM_ON_FOOT:
	case OBJECTIVE_GOTO_BUS_STOP_ON_FOOT:
	case OBJECTIVE_GOTO_PIZZA_ON_FOOT:
	case OBJECTIVE_GOTO_SHELTER_ON_FOOT:
	case OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT:
		ClearPointGunAt();
		SetObjective(newObj, pos);
		m_attractorHeading = heading;
	}
}

void
CPed::ClearObjective(void)
{
	if (IsPedInControl() || m_nPedState == PED_DRIVING) {
		m_objective = OBJECTIVE_NONE;
		m_pedInObjective = nil;
		m_carInObjective = nil;

		if (m_nPedState == PED_DRIVING && m_pMyVehicle) {
			if (m_pMyVehicle->pDriver != this) {
				if(!IsPlayer())
					bWanderPathAfterExitingCar = true;

				SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
			}
			m_nLastPedState = PED_NONE;
		} else {
			SetIdle();
			SetMoveState(PEDMOVE_STILL);
		}
	} else {
		bClearObjective = true;
	}
}

void
CPed::ClearLeader(void)
{
	if (!m_leader)
		return;

	m_leader = nil;
	if (IsPedInControl()) {
		SetObjective(OBJECTIVE_NONE);
		if (CharCreatedBy == MISSION_CHAR) {
			SetIdle();
		} else {
			SetWanderPath(CGeneral::GetRandomNumberInRange(0,8));
		}
	} else if (m_objective != OBJECTIVE_NONE) {
		bClearObjective = true;
	}
}

void
CPed::UpdateFromLeader(void)
{
	if (CTimer::GetTimeInMilliseconds() <= m_objectiveTimer)
		return;

	if (!m_leader)
		return;

	CVector leaderDist;
	if (m_leader->InVehicle())
		leaderDist = m_leader->m_pMyVehicle->GetPosition() - GetPosition();
	else
		leaderDist = m_leader->GetPosition() - GetPosition();

	if (leaderDist.Magnitude() > 30.0f) {
		if (bWaitForLeaderToComeCloser) {
			if (IsPedInControl()) {
				SetObjective(OBJECTIVE_NONE);
				SetIdle();
				SetMoveState(PEDMOVE_STILL);
			}
			return;
		}
		bWaitForLeaderToComeCloser = true;
	} else
		bWaitForLeaderToComeCloser = false;

	if (IsPedInControl()) {
		if (m_nWaitState == WAITSTATE_PLAYANIM_TAXI)
			WarpPedToNearLeaderOffScreen();

		if (m_leader->m_nPedState == PED_DEAD) {
			SetLeader(nil);
			SetObjective(OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE);
			return;
		}
		if (!m_leader->bInVehicle) {
			if (m_leader->m_objective != OBJECTIVE_ENTER_CAR_AS_DRIVER) {
				if (bInVehicle) {
					if (m_objective != OBJECTIVE_WAIT_IN_CAR_THEN_GET_OUT && m_objective != OBJECTIVE_LEAVE_CAR)
						SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);

					return;
				}
				if (m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER) {
					RestorePreviousObjective();
					RestorePreviousState();
				}
			}
			if (m_nPedType == PEDTYPE_PROSTITUTE && CharCreatedBy == RANDOM_CHAR) {
				SetLeader(nil);
				return;
			}
		}
		if (!bInVehicle && m_leader->bInVehicle && m_leader->m_nPedState == PED_DRIVING) {
			if (m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER && m_objective != OBJECTIVE_ENTER_CAR_AS_DRIVER) {
				if (m_leader->m_pMyVehicle->m_nNumPassengers < m_leader->m_pMyVehicle->m_nNumMaxPassengers)
					SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, m_leader->m_pMyVehicle);
			}
		} else if (m_leader->m_objective == OBJECTIVE_NONE || (m_leader->IsPlayer() && m_leader->m_objective == OBJECTIVE_WAIT_ON_FOOT)
			|| m_objective == m_leader->m_objective) {

			if (m_leader->m_nPedState == PED_ATTACK && !bDontFight) {
				CEntity *lookTargetOfLeader = m_leader->m_pLookTarget;

				if (lookTargetOfLeader && m_objective != OBJECTIVE_KILL_CHAR_ON_FOOT && lookTargetOfLeader->IsPed() && lookTargetOfLeader != this) {
					SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, lookTargetOfLeader);
					SetObjectiveTimer(8000);
					SetLookFlag(m_leader->m_pLookTarget, false);
					SetLookTimer(500);
				}
			} else {
				if (IsPedInControl() && m_nPedState != PED_ATTACK) {
					if (m_leader->m_objective == OBJECTIVE_NONE && m_objective == OBJECTIVE_NONE && m_leader->m_nPedState == PED_CHAT && m_nPedState == PED_CHAT) {
						SetObjective(OBJECTIVE_NONE);
					} else {
						SetObjective(OBJECTIVE_GOTO_CHAR_ON_FOOT, m_leader);
						SetObjectiveTimer(0);
					}
				}
				if (m_nPedState == PED_IDLE && m_leader->IsPlayer() && !bDontFight) {
					if (ScanForThreats() && m_threatEntity) {
						m_pLookTarget = m_threatEntity;
						m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
						TurnBody();
						if (m_attackTimer < CTimer::GetTimeInMilliseconds() && !GetWeapon()->IsTypeMelee()) {
							SetWeaponLockOnTarget(m_threatEntity);
							SetAttack(m_threatEntity);
						}
					}
				}
			}
		} else {
			switch (m_leader->m_objective) {
				case OBJECTIVE_WAIT_ON_FOOT:
				case OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE:
				case OBJECTIVE_WAIT_IN_CAR:
				case OBJECTIVE_FOLLOW_ROUTE:
					SetObjective(m_leader->m_objective);
					m_objectiveTimer = m_leader->m_objectiveTimer;
					break;
				case OBJECTIVE_GUARD_SPOT:
					SetObjective(OBJECTIVE_GUARD_SPOT, m_leader->m_vecSpotToGuard);
					m_objectiveTimer = m_leader->m_objectiveTimer;
					break;
				case OBJECTIVE_KILL_CHAR_ON_FOOT:
				case OBJECTIVE_KILL_CHAR_ANY_MEANS:
				case OBJECTIVE_GOTO_CHAR_ON_FOOT:
				case OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING:
				case OBJECTIVE_HASSLE_CHAR:
					if (m_leader->m_pedInObjective) {
						SetObjective(m_leader->m_objective, m_leader->m_pedInObjective);
						m_objectiveTimer = m_leader->m_objectiveTimer;
					}
					break;
				case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
				case OBJECTIVE_ENTER_CAR_AS_DRIVER:
					if (m_leader->m_carInObjective) {
						m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 150;
						SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, m_leader->m_carInObjective);
						return;
					}
					break;
				case OBJECTIVE_GUARD_ATTACK:
					return;
				case OBJECTIVE_HAIL_TAXI:
					m_leader = nil;
					SetObjective(OBJECTIVE_NONE);
					break;
				default:
					SetObjective(OBJECTIVE_GOTO_CHAR_ON_FOOT, m_leader);
					SetObjectiveTimer(0);
					break;
			}
		}
	} else if (bInVehicle) {
		if ((!m_leader->bInVehicle || m_leader->m_nPedState == PED_EXIT_CAR) && m_objective != OBJECTIVE_WAIT_IN_CAR_THEN_GET_OUT) {

			switch (m_leader->m_objective) {
				case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
				case OBJECTIVE_ENTER_CAR_AS_DRIVER:
					if (m_pMyVehicle == m_leader->m_pMyVehicle || m_pMyVehicle == m_leader->m_carInObjective)
						break;

					// fall through
				default:
					if (m_pMyVehicle && m_objective != OBJECTIVE_LEAVE_CAR) {
						m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 250;
						SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
					}

					break;
			}
		}
	}
}

void
CPed::RestorePreviousObjective(void)
{
	if (m_objective == OBJECTIVE_NONE)
		return;

	if (m_objective != OBJECTIVE_LEAVE_CAR && m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER && m_objective != OBJECTIVE_ENTER_CAR_AS_DRIVER
		&& m_nPedState != PED_CARJACK)
		m_pedInObjective = nil;

	if (m_objective == OBJECTIVE_WAIT_IN_CAR_THEN_GET_OUT) {
		m_objective = OBJECTIVE_NONE;
		if (m_pMyVehicle)
			SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);

	} else {
		m_objective = m_prevObjective;
		m_prevObjective = OBJECTIVE_NONE;
	}
	bObjectiveCompleted = false;
}

void
CPed::ProcessObjective(void)
{
	if (bClearObjective && (IsPedInControl() || m_nPedState == PED_DRIVING)) {
		ClearObjective();
		bClearObjective = false;
	}
	UpdateFromLeader();

	CVector carOrOurPos;
	CVector targetCarOrHisPos;
	CVector distWithTarget;

	if (m_objective != OBJECTIVE_NONE && (IsPedInControl() || m_nPedState == PED_DRIVING)) {
		if (bInVehicle) {
			if (!m_pMyVehicle) {
				bInVehicle = false;
				return;
			}
			carOrOurPos = m_pMyVehicle->GetPosition();
		} else {
			carOrOurPos = GetPosition();
		}

		if (m_pedInObjective) {
			if (m_pedInObjective->InVehicle() && m_pedInObjective->m_nPedState != PED_DRAG_FROM_CAR) {
				targetCarOrHisPos = m_pedInObjective->m_pMyVehicle->GetPosition();
			} else {
				targetCarOrHisPos = m_pedInObjective->GetPosition();
			}
			distWithTarget = targetCarOrHisPos - carOrOurPos;
		} else if (m_carInObjective) {
			targetCarOrHisPos = m_carInObjective->GetPosition();
			distWithTarget = targetCarOrHisPos - carOrOurPos;
		}

		switch (m_objective) {
			case OBJECTIVE_WAIT_ON_FOOT:
				if (GetPedState() == PED_DRIVING)
					m_objective = OBJECTIVE_NONE;
				else {
					SetIdle();
					if (m_attractor) {
						if (m_objectiveTimer && CTimer::GetTimeInMilliseconds() > m_nWaitTimer) {
							GetPedAttractorManager()->BroadcastDeparture(this, m_attractor);
							m_objectiveTimer = 0;
						}
					} else {
						m_objective = OBJECTIVE_NONE;
						SetMoveState(PEDMOVE_STILL);
					}
				}
				break;
			case OBJECTIVE_WAIT_ON_FOOT_FOR_COP:
				if (!m_pedInObjective) {
					m_objective = OBJECTIVE_NONE;
					SetWanderPath(CGeneral::GetRandomNumberInRange(0.f, 8.f));
				} else if (m_pedInObjective->m_nPedType == PEDTYPE_COP && m_pedInObjective->m_nPedState == PED_DEAD) {
					m_objective = OBJECTIVE_NONE;
					SetWanderPath(CGeneral::GetRandomNumberInRange(0.f, 8.f));
					m_pedInObjective = nil;
				}
				break;
			case OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE:
				if (m_leaveCarTimer >= CTimer::GetTimeInMilliseconds())
					break;

				if (InVehicle()) {
					SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
					bFleeAfterExitingCar = true;
				} else if (m_nPedState != PED_FLEE_POS) {
					CVector2D fleePos = GetPosition();
					SetFlee(fleePos, 10000);
					bUsePedNodeSeek = true;
					m_pNextPathNode = nil;
				}
				break;
			case OBJECTIVE_GUARD_SPOT:
			{
				distWithTarget = m_vecSpotToGuard - GetPosition();
				if (m_pedInObjective) {
					SetLookFlag(m_pedInObjective, true);
					m_pLookTarget = m_pedInObjective;
					m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
					TurnBody();
				}
				float distWithTargetSc = distWithTarget.Magnitude();
				if (2.0f * m_radiusToGuard >= distWithTargetSc) {
					if (m_pedInObjective && m_pedInObjective->m_nPedState != PED_DEAD) {
						if (distWithTargetSc <= m_radiusToGuard)
							SetIdle();
						else {
							CVector seekPos = m_vecSpotToGuard;
							SetSeek(seekPos, m_radiusToGuard);
						}
					} else if (CTimer::GetTimeInMilliseconds() > m_lookTimer) {
						int threatType = ScanForThreats();
						SetLookTimer(CGeneral::GetRandomNumberInRange(500, 1500));

						// Second condition is pointless and isn't there in Mobile.
						if (threatType == PED_FLAG_GUN || (threatType == PED_FLAG_EXPLOSION && m_threatEntity) || m_threatEntity) {
							if (m_threatEntity->IsPed())
								SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, m_threatEntity);
						}
					}
				} else {
					CVector seekPos = m_vecSpotToGuard;
					SetSeek(seekPos, m_radiusToGuard);
				}
				break;
			}
			case OBJECTIVE_WAIT_IN_CAR:
				SetPedState(PED_DRIVING);
				break;
			case OBJECTIVE_WAIT_IN_CAR_THEN_GET_OUT:
				SetPedState(PED_DRIVING);
				break;
			case OBJECTIVE_KILL_CHAR_ANY_MEANS:
			{
				if (m_pedInObjective) {
					if (m_pedInObjective->IsPlayer() && CharCreatedBy != MISSION_CHAR
						&& m_nPedType != PEDTYPE_COP && FindPlayerPed()->m_pWanted->m_CurrentCops != 0
						&& !bKindaStayInSamePlace) {

						SetObjective(OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE);
						break;
					}
					if (InVehicle()) {
						if (distWithTarget.Magnitude() >= 20.0f || m_pMyVehicle->m_vecMoveSpeed.MagnitudeSqr() >= sq(0.02f)) {

							if (((m_pMyVehicle->pDriver == this && m_pMyVehicle->AutoPilot.m_nCarMission == MISSION_NONE) || m_pMyVehicle->AutoPilot.m_nCarMission == MISSION_CRUISE)
								&& !m_pMyVehicle->m_nGettingInFlags) {
								m_pMyVehicle->SetStatus(STATUS_PHYSICS);
								m_pMyVehicle->AutoPilot.m_nPrevRouteNode = 0;
								if (m_nPedType == PEDTYPE_COP) {
									m_pMyVehicle->AutoPilot.m_nCruiseSpeed = (FindPlayerPed()->m_pWanted->GetWantedLevel() * 0.1f + 0.6f) * (GAME_SPEED_TO_CARAI_SPEED * m_pMyVehicle->pHandling->Transmission.fMaxCruiseVelocity);
									m_pMyVehicle->AutoPilot.m_nCarMission = CCarAI::FindPoliceCarMissionForWantedLevel();
								} else {
									m_pMyVehicle->AutoPilot.m_nCruiseSpeed = GAME_SPEED_TO_CARAI_SPEED * m_pMyVehicle->pHandling->Transmission.fMaxCruiseVelocity * 0.8f;
									m_pMyVehicle->AutoPilot.m_nCarMission = MISSION_RAMPLAYER_FARAWAY;
								}
								m_pMyVehicle->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
							}
						} else {
							bool targetHasVeh = m_pedInObjective->bInVehicle;
							if (!targetHasVeh || targetHasVeh && m_pedInObjective->m_pMyVehicle->CanPedExitCar(false)) {
								m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
								m_pMyVehicle->AutoPilot.m_nCarMission = MISSION_NONE;
								SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
							}
						}
						break;
					}
					if (distWithTarget.Magnitude() > 30.0f && !bKindaStayInSamePlace) {
						if (m_pMyVehicle) {
							m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
							SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, m_pMyVehicle);
						} else {
							float closestVehDist = 60.0f;
							int16 lastVehicle;
							CEntity* vehicles[8];
							CWorld::FindObjectsInRange(GetPosition(), ENTER_CAR_MAX_DIST, true, &lastVehicle, 6, vehicles, false, true, false, false, false);
							CVehicle *foundVeh = nil;
							for(int i = 0; i < lastVehicle; i++) {
								CVehicle *nearVeh = (CVehicle*)vehicles[i];
								/*
								Not used.
								CVector vehSpeed = nearVeh->GetSpeed();
								CVector ourSpeed = GetSpeed();
								*/
								CVector vehDistVec = nearVeh->GetPosition() - GetPosition();
								if (vehDistVec.Magnitude() < closestVehDist && m_pedInObjective->m_pMyVehicle != nearVeh
									&& nearVeh->CanPedOpenLocks(this) && nearVeh->m_fHealth > 250.f) {

									foundVeh = nearVeh;
									closestVehDist = vehDistVec.Magnitude();
								}
							}
							m_pMyVehicle = foundVeh;
							if (m_pMyVehicle) {
								m_pMyVehicle->RegisterReference((CEntity **) &m_pMyVehicle);
								m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
								SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, m_pMyVehicle);
							} else if (!GetIsOnScreen()) {
								CVector ourPos = GetPosition();
								int closestNode = ThePaths.FindNodeClosestToCoors(ourPos, PATH_CAR, 20.0f);
								if (closestNode >= 0) {
									int16 colliding;
									CWorld::FindObjectsKindaColliding(
										ThePaths.m_pathNodes[closestNode].GetPosition(), 10.0f, true, &colliding, 2, nil, false, true, true, false, false);
									if (!colliding) {
										CZoneInfo zoneInfo;
										int chosenCarClass;
										CTheZones::GetZoneInfoForTimeOfDay(&ourPos, &zoneInfo);
										int chosenModel = CCarCtrl::ChooseModel(&zoneInfo, &chosenCarClass);
										CVehicle *newVeh = nil;
										if (chosenModel != -1) {
											if (CModelInfo::IsBikeModel(chosenModel)) {
												newVeh = new CBike(chosenModel, RANDOM_VEHICLE);
											} else {
												newVeh = new CAutomobile(chosenModel, RANDOM_VEHICLE);
											}
										}
										if (newVeh) {
											newVeh->GetMatrix().GetPosition() = ThePaths.m_pathNodes[closestNode].GetPosition();
											newVeh->GetMatrix().GetPosition().z += 4.0f;
											newVeh->SetHeading(DEGTORAD(200.0f));
											newVeh->SetStatus(STATUS_ABANDONED);
											newVeh->m_nDoorLock = CARLOCK_UNLOCKED;
											CWorld::Add(newVeh);
											m_pMyVehicle = newVeh;
											if (m_pMyVehicle) {
												m_pMyVehicle->RegisterReference((CEntity **) &m_pMyVehicle);
												m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
												SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, m_pMyVehicle);
											}
										}
									}
								}
							}
						}
						break;
					}
				} else {
					ClearLookFlag();
					bObjectiveCompleted = true;
				}
			}
			case OBJECTIVE_KILL_CHAR_ON_FOOT:
			{
				if (m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT && InVehicle()) {
					SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
					break;
				}
				if (!m_pedInObjective || m_pedInObjective->DyingOrDead()) {
					bObjectiveCompleted = true;
					ClearLookFlag();
					SetMoveAnim();
					break;
				}
				if (m_pedInObjective) {
					int status;
					if (GetWeapon()->IsTypeMelee())
						status = KillCharOnFootMelee(carOrOurPos, targetCarOrHisPos, distWithTarget);
					else
						status = KillCharOnFootArmed(carOrOurPos, targetCarOrHisPos, distWithTarget);

					if (status == WATCH_UNTIL_HE_DISAPPEARS)
						return;
					if (status == CANT_ATTACK)
						break;
				}
				SetMoveAnim();
				break;
			}
			case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
			case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
			{
				if (InVehicle()) {
					if (m_nPedState == PED_DRIVING)
						SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
				} else if (m_nPedState != PED_FLEE_ENTITY) {
					int time;
					if (m_objective == OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS)
						time = 0;
					else
						time = 6000;

					SetFindPathAndFlee(m_pedInObjective, time);
					if (m_pedStats == CPedStats::ms_apPedStats[PEDSTAT_FIREMAN])
						bMakeFleeScream = true;
				}
				break;
			}
			case OBJECTIVE_GOTO_CHAR_ON_FOOT:
			case OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING:
			case OBJECTIVE_HASSLE_CHAR:
			{
				if (m_pedInObjective) {
					float safeDistance = 2.0f;
					if (m_pedInObjective->bInVehicle)
						safeDistance = 3.0f;
					if (m_objective == OBJECTIVE_HASSLE_CHAR)
						safeDistance = 1.0f;

					float distWithTargetSc = distWithTarget.Magnitude();
					if (m_nPedStateTimer < CTimer::GetTimeInMilliseconds()) {
						if (distWithTargetSc <= safeDistance) {
							bScriptObjectiveCompleted = true;
							if (m_nPedState != PED_ATTACK) {
								SetIdle();
								if (m_pLookTarget)
									m_pLookTarget->CleanUpOldReference(&m_pLookTarget);
								m_pLookTarget = m_pedInObjective;
								m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
								TurnBody();
							}
							if (distWithTargetSc > 2.0f)
								SetMoveState(m_pedInObjective->m_nMoveState);
							else
								SetMoveState(PEDMOVE_STILL);

							if (m_objective == OBJECTIVE_HASSLE_CHAR) {
								Say(SOUND_PED_COP_ASK_FOR_ID);
								m_pedInObjective->Say(SOUND_PED_INNOCENT);
								m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 3000;
								m_pedInObjective->m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 3000;
								SetObjective(OBJECTIVE_WANDER);
								m_pedInObjective->SetObjective(OBJECTIVE_WANDER);
								CVector2D dist = GetPosition() - m_pedInObjective->GetPosition();
								m_nPathDir = CGeneral::GetNodeHeadingFromVector(dist.x, dist.y);
								m_pedInObjective->m_nPathDir = CGeneral::GetNodeHeadingFromVector(-dist.x, -dist.y);
							}
						} else {
							SetSeek(m_pedInObjective, safeDistance);
							if (distWithTargetSc >= 5.0f) {
								if (m_leader && m_leader->m_nMoveState == PEDMOVE_SPRINT)
									SetMoveState(PEDMOVE_SPRINT);
								else
									SetMoveState(PEDMOVE_RUN);
							} else {
								if (m_leader && m_leader->m_nMoveState != PEDMOVE_STILL
									&& m_leader->m_nMoveState != PEDMOVE_NONE) {
									if (m_leader->IsPlayer()) {
										if (distWithTargetSc >= 3.0f && FindPlayerPed()->m_fMoveSpeed >= 1.3f)
											SetMoveState(PEDMOVE_RUN);
										else
											SetMoveState(PEDMOVE_WALK);
									} else {
										SetMoveState(m_leader->m_nMoveState);
									}
								} else if (distWithTargetSc <= 3.0f) {
									SetMoveState(PEDMOVE_WALK);
								} else {
									SetMoveState(PEDMOVE_RUN);
								}
							}
						}
						if (m_objective == OBJECTIVE_GOTO_CHAR_ON_FOOT_WALKING && m_nMoveState > PEDMOVE_STILL)
							SetMoveState(PEDMOVE_WALK);
					}
				} else {
					SetObjective(OBJECTIVE_NONE);
				}
				break;
			}
			case OBJECTIVE_FOLLOW_CHAR_IN_FORMATION:
			{
				if (m_pedInObjective) {
					CVector posToGo = GetFormationPosition();
					distWithTarget = posToGo - carOrOurPos;
					SetSeek(posToGo, 1.0f);
					if (distWithTarget.Magnitude() <= 3.0f) {
						SetSeek(posToGo, 1.0f);
						if (m_pedInObjective && m_pedInObjective->m_nMoveState != PEDMOVE_STILL)
							SetMoveState(m_pedInObjective->m_nMoveState);
					} else {
						SetSeek(posToGo, 1.0f);
						SetMoveState(PEDMOVE_RUN);
					}
				} else {
					SetObjective(OBJECTIVE_NONE);
				}
				break;
			}
			case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
			{
				if (m_carInObjective) {
					if (!bInVehicle && m_carInObjective->m_nNumPassengers >= m_carInObjective->m_nNumMaxPassengers) {
						RestorePreviousObjective();
						RestorePreviousState();
						if (IsPedInControl())
							m_pMyVehicle = nil;

						break;
					}

					if (m_prevObjective == OBJECTIVE_HAIL_TAXI && !((CAutomobile*)m_carInObjective)->bTaxiLight) {
						RestorePreviousObjective();
						ClearObjective();
						SetWanderPath(CGeneral::GetRandomNumber() & 7);
						bIsRunning = false;
						break;
					}
					if (m_objectiveTimer && m_objectiveTimer < CTimer::GetTimeInMilliseconds()) {
						if (!EnteringCar()) {
							bool foundSeat = false;
							if (m_carInObjective->IsBike()) {
								if (!m_carInObjective->pPassengers[0] && !(m_carInObjective->m_nGettingInFlags & (CAR_DOOR_FLAG_RR | CAR_DOOR_FLAG_LR))) {
									m_vehDoor = CAR_DOOR_RR;
									foundSeat = true;
								}
							} else {
								if (m_carInObjective->pPassengers[0] || m_carInObjective->m_nGettingInFlags & CAR_DOOR_FLAG_RF) {
									if (m_carInObjective->pPassengers[1] || m_carInObjective->m_nGettingInFlags & CAR_DOOR_FLAG_LR) {
										if (m_carInObjective->pPassengers[2] || m_carInObjective->m_nGettingInFlags & CAR_DOOR_FLAG_RR) {
											foundSeat = false;
										} else {
											m_vehDoor = CAR_DOOR_RR;
											foundSeat = true;
										}
									} else {
										m_vehDoor = CAR_DOOR_LR;
										foundSeat = true;
									}
								} else {
									m_vehDoor = CAR_DOOR_RF;
									foundSeat = true;
								}
							}
							for (int i = 2; i < m_carInObjective->m_nNumMaxPassengers; ++i) {
								if (!m_carInObjective->pPassengers[i] && !(m_carInObjective->m_nGettingInFlags & CAR_DOOR_FLAG_RF)) {
									m_vehDoor = CAR_DOOR_RF;
									foundSeat = true;
								}
							}
							if (foundSeat) {
								SetPosition(GetPositionToOpenCarDoor(m_carInObjective, m_vehDoor));
								SetEnterCar(m_carInObjective, m_vehDoor);
							}
						}
						m_objectiveTimer = 0;
					}
				}
				// fall through
			}
			case OBJECTIVE_ENTER_CAR_AS_DRIVER:
			{
				if (!m_carInObjective || bInVehicle) {
					if (bInVehicle && m_pMyVehicle != m_carInObjective) {
						SetExitCar(m_pMyVehicle, 0);
					} else {
						bObjectiveCompleted = true;
						bScriptObjectiveCompleted = true;
						RestorePreviousState();
					}
				} else {
					if (m_leaveCarTimer > CTimer::GetTimeInMilliseconds()) {
						SetMoveState(PEDMOVE_STILL);
						break;
					}
					if (IsPedInControl()) {
						if (m_prevObjective == OBJECTIVE_KILL_CHAR_ANY_MEANS) {
							if (distWithTarget.Magnitude() < 20.0f) {
								RestorePreviousObjective();
								RestorePreviousState();
								return;
							}
							if (m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER) {
								if (m_carInObjective->pDriver && !IsPlayer()) {
									if (m_carInObjective->pDriver->m_objective == OBJECTIVE_KILL_CHAR_ANY_MEANS && m_carInObjective->pDriver != m_pedInObjective) {
										SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, m_carInObjective);
										m_carInObjective->bIsBeingCarJacked = false;
									}
								}
							}
						} else if (m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER) {
							if (m_carInObjective->pDriver
								&& (CharCreatedBy != MISSION_CHAR || m_carInObjective->pDriver->CharCreatedBy != RANDOM_CHAR)
								) {
								if (m_carInObjective->pDriver->m_nPedType == m_nPedType) {
									SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, m_carInObjective);
									m_carInObjective->bIsBeingCarJacked = false;
								}
							}
						}
						if (m_carInObjective->IsUpsideDown() && m_carInObjective->m_vehType != VEHICLE_TYPE_BIKE) {
							RestorePreviousObjective();
							RestorePreviousState();
							return;
						}
						if (!m_carInObjective->IsBoat() || m_nPedState == PED_SEEK_IN_BOAT) {
							if (m_nPedState != PED_SEEK_CAR)
								SetSeekCar(m_carInObjective, 0);
						} else {
							SetSeekBoatPosition(m_carInObjective);
						}
						if (m_nMoveState == PEDMOVE_STILL && !bVehEnterDoorIsBlocked)
							SetMoveState(PEDMOVE_RUN);

						if (m_carInObjective && m_carInObjective->m_fHealth > 0.0f) {
							distWithTarget = m_carInObjective->GetPosition() - GetPosition();
							if (!bInVehicle) {
								if (nEnterCarRangeMultiplier * ENTER_CAR_MAX_DIST < distWithTarget.Magnitude()) {
									if (!m_carInObjective->pDriver && !m_carInObjective->GetIsOnScreen() && !GetIsOnScreen())
										WarpPedToNearEntityOffScreen(m_carInObjective);

									if (CharCreatedBy != MISSION_CHAR || m_prevObjective == OBJECTIVE_KILL_CHAR_ANY_MEANS
										|| IsPlayer() && !CPad::GetPad(0)->ArePlayerControlsDisabled()) {
										RestorePreviousObjective();
										RestorePreviousState();
										if (IsPedInControl())
											m_pMyVehicle = nil;
									} else {
										SetIdle();
										SetMoveState(PEDMOVE_STILL);
									}
								}
							}
						} else if (!bInVehicle) {
							RestorePreviousObjective();
							RestorePreviousState();
							if (IsPedInControl())
								m_pMyVehicle = nil;
						}
					}
				}
				break;
			}
			case OBJECTIVE_DESTROY_OBJECT:
				if (m_pPointGunAt) {
					if (m_nPedState != PED_ATTACK)
						SetAttack(m_pPointGunAt);
				} else {
					bScriptObjectiveCompleted = true;
					RestorePreviousObjective();
				}
				break;
			case OBJECTIVE_DESTROY_CAR:
			{
				if (!m_carInObjective) {
					ClearLookFlag();
					bObjectiveCompleted = true;
					break;
				}
				float distWithTargetSc = distWithTarget.Magnitude();
				CWeaponInfo *wepInfo = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);
				float wepRange = wepInfo->m_fRange;
				m_pLookTarget = m_carInObjective;
				m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);

				m_pSeekTarget = m_carInObjective;
				m_pSeekTarget->RegisterReference((CEntity**) &m_pSeekTarget);

				TurnBody();
				if (m_carInObjective->m_fHealth <= 0.0f) {
					ClearLookFlag();
					bScriptObjectiveCompleted = true;
					break;
				}

				if (m_attackTimer < CTimer::GetTimeInMilliseconds() && distWithTargetSc < wepRange) {
					// I hope so
					CVector ourHead = GetMatrix() * CVector(0.5f, 0.0f, 0.6f);
					CVector maxShotPos = m_carInObjective->GetPosition() - ourHead;
					maxShotPos *= wepInfo->m_fRange / maxShotPos.Magnitude();
					maxShotPos += ourHead;

					CColPoint foundCol;
					CEntity *foundEnt;

					CWorld::bIncludeDeadPeds = true;
					CWorld::ProcessLineOfSight(ourHead, maxShotPos, foundCol, foundEnt, true, true, true, true, false, true, false);
					CWorld::bIncludeDeadPeds = false;
					if (foundEnt == m_carInObjective) {
						SetAttack(m_carInObjective);
						SetWeaponLockOnTarget(m_carInObjective);
						SetShootTimer(CGeneral::GetRandomNumberInRange(500, 2000));
						if (distWithTargetSc > 10.0f && !bKindaStayInSamePlace) {
							SetAttackTimer(CGeneral::GetRandomNumberInRange(2000, 5000));
						} else {
							SetAttackTimer(CGeneral::GetRandomNumberInRange(50, 300));
							SetMoveState(PEDMOVE_STILL);
						}
					}
				} else if (m_nPedState != PED_ATTACK && !bKindaStayInSamePlace) {
					if (wepRange <= 5.0f) {
						if (Abs(distWithTarget.x) > wepRange || Abs(distWithTarget.y) > wepRange ||
							(distWithTarget.z > -1.0f && distWithTarget.z < 0.3)) {
							SetSeek(m_carInObjective, 3.0f);
							SetMoveState(PEDMOVE_RUN);
						} else {
							SetIdle();
						}
					} else {
						float safeDistance = wepRange * 0.25f;

						SetSeek(m_carInObjective, safeDistance);
						SetMoveState(PEDMOVE_RUN);
					}
				}
				SetLookFlag(m_carInObjective, false);
				TurnBody();
				break;
			}
			case OBJECTIVE_GOTO_AREA_ON_FOOT:
			case OBJECTIVE_RUN_TO_AREA:
			case OBJECTIVE_SPRINT_TO_AREA:
			{
				if (InVehicle()) {
					SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
				} else {
					distWithTarget = m_nextRoutePointPos - GetPosition();
					distWithTarget.z = 0.0f;
					if (sq(m_distanceToCountSeekDone) >= distWithTarget.MagnitudeSqr()) {
						bObjectiveCompleted = true;
						bScriptObjectiveCompleted = true;
						SetMoveState(PEDMOVE_STILL);
					} else if (CTimer::GetTimeInMilliseconds() > m_nPedStateTimer || m_nPedState != PED_SEEK_POS) {
						if (bUsePedNodeSeek) {
							CVector bestCoords(0.0f, 0.0f, 0.0f);
							m_vecSeekPos = m_nextRoutePointPos;

							if (!m_pNextPathNode) {
								bool found = FindBestCoordsFromNodes(m_vecSeekPos, &bestCoords);
								if (m_pNextPathNode) {
									// Because it already does that if it finds better coords.
									if (!found) {
										bestCoords = CPathFind::TakeWidthIntoAccountForWandering(m_pNextPathNode, m_randomSeed);
									}
									if ((bestCoords - GetPosition()).Magnitude2D() < m_distanceToCountSeekDone) {
										m_pNextPathNode = nil;
										bUsePedNodeSeek = false;
									}
								}
							}
							if (m_pNextPathNode)
								m_vecSeekPos = CPathFind::TakeWidthIntoAccountForWandering(m_pNextPathNode, m_randomSeed);
						}
						CVector seekPos = m_vecSeekPos;
						SetSeek(m_vecSeekPos, m_distanceToCountSeekDone);
					}
				}

				break;
			}
			case OBJECTIVE_GUARD_ATTACK:
			{
				if (m_pedInObjective) {
					SetLookFlag(m_pedInObjective, true);
					m_pLookTarget = m_pedInObjective;
					m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
					m_lookTimer = m_attackTimer;
					TurnBody();
					float distWithTargetSc = distWithTarget.Magnitude();
					if (distWithTargetSc >= 20.0f) {
						RestorePreviousObjective();
					} else if (m_attackTimer < CTimer::GetTimeInMilliseconds()) {
						if (m_nPedState != PED_SEEK_ENTITY && distWithTargetSc >= 2.0f) {
							SetSeek(m_pedInObjective, 1.0f);
						} else {
							SetAttack(m_pedInObjective);
							SetShootTimer(CGeneral::GetRandomNumberInRange(500.0f, 1500.0f));
						}
						SetAttackTimer(1000);
					}
				} else {
					RestorePreviousObjective();
				}
				break;
			}
			case OBJECTIVE_FOLLOW_ROUTE:
				if (HaveReachedNextPointOnRoute(1.0f)) {
					int nextPoint = GetNextPointOnRoute();
					m_nextRoutePointPos = CRouteNode::GetPointPosition(nextPoint);
				} else {
					CVector seekPos = m_nextRoutePointPos;
					SetSeek(seekPos, 0.8f);
				}
				break;
			case OBJECTIVE_SOLICIT_VEHICLE:
				if (m_carInObjective) {
					if (m_objectiveTimer <= CTimer::GetTimeInMilliseconds()) {
						if (!bInVehicle) {
							SetObjective(OBJECTIVE_NONE);
							SetWanderPath(CGeneral::GetRandomNumber() & 7);
							m_objectiveTimer = CTimer::GetTimeInMilliseconds() + 10000;
							if (IsPedInControl())
								m_pMyVehicle = nil;
						}
					} else {
						if (m_nPedState != PED_FLEE_ENTITY && m_nPedState != PED_SOLICIT)
							SetSeekCar(m_carInObjective, 0);
					}
				} else {
					RestorePreviousObjective();
					RestorePreviousState();
					if (IsPedInControl())
						m_pMyVehicle = nil;
				}
				break;
			case OBJECTIVE_HAIL_TAXI:
				if (!RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_HAILTAXI) && CTimer::GetTimeInMilliseconds() > m_nWaitTimer) {
					Say(SOUND_PED_TAXI_WAIT);
					CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_HAILTAXI, 4.0f);
					m_nWaitTimer = CTimer::GetTimeInMilliseconds() + 2000;
				}
				break;
			case OBJECTIVE_CATCH_TRAIN:
			{
				if (m_carInObjective) {
					SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, m_carInObjective);
				} else {
					CVehicle* trainToEnter = nil;
					float closestCarDist = CHECK_NEARBY_THINGS_MAX_DIST;
					CVector pos = GetPosition();
					int16 lastVehicle;
					CEntity* vehicles[8];

					CWorld::FindObjectsInRange(pos, 10.0f, true, &lastVehicle, 6, vehicles, false, true, false, false, false);
					for (int i = 0; i < lastVehicle; i++) {
						CVehicle* nearVeh = (CVehicle*)vehicles[i];
						if (nearVeh->IsTrain()) {
							CVector vehDistVec = GetPosition() - nearVeh->GetPosition();
							float vehDist = vehDistVec.Magnitude();
							if (vehDist < closestCarDist && m_pedInObjective->m_pMyVehicle != nearVeh)
							{
								trainToEnter = nearVeh;
								closestCarDist = vehDist;
							}
						}
					}
					if (trainToEnter) {
						m_carInObjective = trainToEnter;
						m_carInObjective->RegisterReference((CEntity **) &m_carInObjective);
					}
				}
				break;
			}
			case OBJECTIVE_BUY_ICE_CREAM:
				if (m_carInObjective) {
					if (m_nPedState != PED_FLEE_ENTITY && m_nPedState != PED_BUY_ICECREAM && m_nPedState != PED_CHAT)
						SetSeekCar(m_carInObjective, 0);
				}
				break;
			case OBJECTIVE_STEAL_ANY_CAR:
			case OBJECTIVE_STEAL_ANY_MISSION_CAR:
			{
				if (bInVehicle) {
					bScriptObjectiveCompleted = true;
					RestorePreviousObjective();
				} else if (m_carJackTimer < CTimer::GetTimeInMilliseconds()) {
					CVehicle *carToSteal = nil;
					float closestCarDist = nEnterCarRangeMultiplier * ENTER_CAR_MAX_DIST;
					CVector pos = GetPosition();
					int16 lastVehicle;
					CEntity *vehicles[8];

					CWorld::FindObjectsInRange(pos, closestCarDist, true, &lastVehicle, 6, vehicles, false, true, false, false, false);
					for(int i = 0; i < lastVehicle; i++) {
						CVehicle *nearVeh = (CVehicle*)vehicles[i];
						if (m_objective == OBJECTIVE_STEAL_ANY_MISSION_CAR || nearVeh->VehicleCreatedBy != MISSION_VEHICLE) {
							if (nearVeh->m_vecMoveSpeed.Magnitude() <= 0.1f) {
								if (nearVeh->CanPedOpenLocks(this)) {
									CVector vehDistVec = GetPosition() - nearVeh->GetPosition();
									float vehDist = vehDistVec.Magnitude();
									if (vehDist < closestCarDist) {
										carToSteal = nearVeh;
										closestCarDist = vehDist;
									}
								}
							}
						}
					}
					if (carToSteal) {
						SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, carToSteal);
						m_carJackTimer = CTimer::GetTimeInMilliseconds() + 5000;
					} else {
						RestorePreviousObjective();
						RestorePreviousState();
					}
				}
				break;
			}
			case OBJECTIVE_MUG_CHAR:
			{
				if (m_pedInObjective) {
					if (m_pedInObjective->IsPlayer() || m_pedInObjective->bInVehicle || m_pedInObjective->m_fHealth <= 0.0f) {
						ClearObjective();
						return;
					}
					if (m_pedInObjective->m_nMoveState > PEDMOVE_WALK) {
						ClearObjective();
						return;
					}
					if (m_pedInObjective->m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT && m_pedInObjective->m_pedInObjective == this) {
						SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, m_pedInObjective);
						SetMoveState(PEDMOVE_SPRINT);
						return;
					}
					if (m_pedInObjective->m_nPedState == PED_FLEE_ENTITY && m_fleeFrom == this
						|| m_pedInObjective->m_objective == OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE && m_pedInObjective->m_pedInObjective == this) {
						ClearObjective();
						SetFindPathAndFlee(m_pedInObjective, 15000, true);
						return;
					}
					float distWithTargetScSqr = distWithTarget.MagnitudeSqr();
					if (distWithTargetScSqr <= sq(10.0f)) {
						if (distWithTargetScSqr <= sq(1.4f)) {
							CAnimBlendAssociation *reloadAssoc = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_PARTIAL_FUCKU);
							m_fRotationDest = CGeneral::GetRadianAngleBetweenPoints(
								m_pedInObjective->GetPosition().x, m_pedInObjective->GetPosition().y,
								GetPosition().x, GetPosition().y);

							if (reloadAssoc || !m_pedInObjective->IsPedShootable()) {
								if (reloadAssoc &&
									(!reloadAssoc->IsRunning() || reloadAssoc->GetProgress() > 0.8f)) {
									CAnimBlendAssociation *punchAssoc = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_PARTIAL_PUNCH, 8.0f);
									punchAssoc->flags |= ASSOC_DELETEFADEDOUT;
									punchAssoc->flags |= ASSOC_FADEOUTWHENDONE;
									CVector2D offset(distWithTarget.x, distWithTarget.y);
									int dir = m_pedInObjective->GetLocalDirection(offset);
									m_pedInObjective->StartFightDefend(dir, HITLEVEL_HIGH, 5);
									m_pedInObjective->ReactToAttack(this);
									m_pedInObjective->Say(SOUND_PED_ROBBED);
									Say(SOUND_PED_MUGGING);
									bRichFromMugging = true;

									// FIX: ClearObjective() clears m_pedInObjective, so get it before call
									CPed *victim = m_pedInObjective;
									ClearObjective();
									if (victim->m_objective != OBJECTIVE_KILL_CHAR_ON_FOOT
										|| victim->m_pedInObjective != this) {
										SetFindPathAndFlee(victim, 15000, true);
										m_nLastPedState = PED_WANDER_PATH;
									} else {
										SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, victim);
										SetMoveState(PEDMOVE_SPRINT);
										m_nLastPedState = PED_WANDER_PATH;
									}
								}
							} else {
								eWeaponType weaponType = GetWeapon()->m_eWeaponType;
								if (weaponType != WEAPONTYPE_UNARMED && weaponType != WEAPONTYPE_BASEBALLBAT)
									SetCurrentWeapon(WEAPONTYPE_UNARMED);

								CAnimBlendAssociation *newReloadAssoc = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_PARTIAL_FUCKU, 8.0f);
								newReloadAssoc->flags |= ASSOC_DELETEFADEDOUT;
								newReloadAssoc->flags |= ASSOC_FADEOUTWHENDONE;
							}
						} else {
							SetSeek(m_pedInObjective, 1.0f);
							CAnimBlendAssociation *walkAssoc = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_WALK);

							if (walkAssoc)
								walkAssoc->speed = 1.3f;
						}
					} else {
						ClearObjective();
						SetWanderPath(CGeneral::GetRandomNumber() & 7);
					}
				} else {
					m_objective = OBJECTIVE_NONE;
					ClearObjective();
				}
			}
			// fall through
			case OBJECTIVE_WANDER:
				if (CTimer::GetTimeInMilliseconds() > m_leaveCarTimer && !bInVehicle) {
					m_leaveCarTimer = 0;
					m_objective = OBJECTIVE_NONE;
					SetWanderPath(m_nPathDir);
				}
				break;
			case OBJECTIVE_LEAVE_CAR_AND_DIE:
			{
				if (CTimer::GetTimeInMilliseconds() > m_leaveCarTimer) {
					if (InVehicle()) {
						if (m_nPedState != PED_EXIT_CAR && m_nPedState != PED_DRAG_FROM_CAR && m_nPedState != PED_EXIT_TRAIN) {
							if (m_pMyVehicle->IsBoat())
								SetExitBoat(m_pMyVehicle);
							else if (m_pMyVehicle->bIsBus)
								SetExitCar(m_pMyVehicle, 0);
							else {
								eCarNodes doorNode = CAR_DOOR_LF;
								if (m_pMyVehicle->pDriver != this) {
									if (m_pMyVehicle->pPassengers[0] == this) {
										doorNode = CAR_DOOR_RF;
									} else if (m_pMyVehicle->pPassengers[1] == this) {
										doorNode = CAR_DOOR_LR;
									} else if (m_pMyVehicle->pPassengers[2] == this) {
										doorNode = CAR_DOOR_RR;
									}
								}
								SetBeingDraggedFromCar(m_pMyVehicle, doorNode, false);
							}
						}
					}
				}
				break;
			}
			case OBJECTIVE_GOTO_AREA_ANY_MEANS:
			{
				distWithTarget = m_nextRoutePointPos - GetPosition();
				distWithTarget.z = 0.0f;
				if (InVehicle()) {
					CCarAI::GetCarToGoToCoors(m_pMyVehicle, &m_nextRoutePointPos);
					CCarCtrl::RegisterVehicleOfInterest(m_pMyVehicle);
					if (distWithTarget.MagnitudeSqr() < sq(20.0f)) {
						m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
						ForceStoredObjective(OBJECTIVE_GOTO_AREA_ANY_MEANS);
						SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
					}
					break;
				}
				if (distWithTarget.Magnitude() > 30.0f) {
					if (m_pMyVehicle) {
						m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
					} else {
						float closestVehDist = SQR(60.0f);
						int16 lastVehicle;
						CEntity* vehicles[8];
						// NB: 25.0f in here is prolly a forgotten setting, all other places now use 30.0f (ENTER_CAR_MAX_DIST)
						CWorld::FindObjectsInRange(GetPosition(), 25.0f, true, &lastVehicle, 6, vehicles, false, true, false, false, false);
						CVehicle* foundVeh = nil;
						for (int i = 0; i < lastVehicle; i++) {
							CVehicle* nearVeh = (CVehicle*)vehicles[i];
							/*
							Not used.
							CVector vehSpeed = nearVeh->GetSpeed();
							CVector ourSpeed = GetSpeed();
							*/
							CVector vehDistVec = nearVeh->GetPosition() - GetPosition();
							if (vehDistVec.MagnitudeSqr() < closestVehDist && m_pedInObjective->m_pMyVehicle != nearVeh) {
								foundVeh = nearVeh;
								closestVehDist = vehDistVec.MagnitudeSqr();
							}
						}
						m_pMyVehicle = foundVeh;
						if (m_pMyVehicle) {
							m_pMyVehicle->RegisterReference((CEntity **) &m_pMyVehicle);
							m_pMyVehicle->AutoPilot.m_nCruiseSpeed = 0;
							SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, m_pMyVehicle);
						}
					}
					break;
				}
				// Falls to different objectives in III and VC
#ifdef FIX_BUGS
				break;
#else
				// fall through
#endif
			}
			case OBJECTIVE_GOTO_SEAT_ON_FOOT:
			case OBJECTIVE_GOTO_ATM_ON_FOOT:
			case OBJECTIVE_GOTO_BUS_STOP_ON_FOOT:
			case OBJECTIVE_GOTO_PIZZA_ON_FOOT:
			case OBJECTIVE_GOTO_SHELTER_ON_FOOT:
			case OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT:
				if (CTimer::GetTimeInMilliseconds() > m_objectiveTimer) {
					m_objectiveTimer = 0;
					if (m_attractor)
						GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
				} else {
					CVector distance = m_nextRoutePointPos - GetPosition();
					distance.z = 0.0f;
					if (m_objective == OBJECTIVE_GOTO_SHELTER_ON_FOOT) {
						if (m_nMoveState == PEDMOVE_RUN && distance.MagnitudeSqr() < SQR(2.0f)) {
							SetMoveState(PEDMOVE_WALK);
							bIsRunning = false;
						}
						if (CWeather::Rain < 0.2f && m_attractor) {
							GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
							return;
						}
					}
					else if (m_objective == OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT) {
						if (m_nMoveState == PEDMOVE_RUN && distance.MagnitudeSqr() < SQR(4.0f)) {
							SetMoveState(PEDMOVE_WALK);
							bIsRunning = false;
						}
						CVehicle* pIceCreamVan = GetPedAttractorManager()->GetIceCreamVanForEffect(m_attractor->GetEffect());
						if (0.01f * CTimer::GetTimeStep() * 5.0f < pIceCreamVan->m_fDistanceTravelled) {
							GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
							return;
						}
						if (!pIceCreamVan->pDriver ||
							!pIceCreamVan->pDriver->IsPlayer() ||
							pIceCreamVan->pDriver->GetPedState() == PED_ARRESTED ||
							pIceCreamVan->pDriver->GetPedState() == PED_DEAD) {
							GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
							return;
						}
						if (!pIceCreamVan->m_bSirenOrAlarm) {
							GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
							return;
						}
						if (pIceCreamVan->GetStatus() == STATUS_WRECKED) {
							GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
							return;
						}
					}
					if (sq(m_distanceToCountSeekDone) < distance.MagnitudeSqr()) {
						if (CTimer::GetTimeInMilliseconds() > m_nPedStateTimer || GetPedState() != PED_SEEK_POS) {
							m_vecSeekPos = m_nextRoutePointPos;
							SetSeek(m_vecSeekPos, m_distanceToCountSeekDone);
						}
					}
					else {
						if (!bReachedAttractorHeadingTarget) {
							float fHeadingDistance = m_fRotationCur - m_attractorHeading;
							float fSinHeading = Sin(fHeadingDistance);
							float fCosHeading = Cos(fHeadingDistance);
							if (fSinHeading > 0.0f) {
								if (fCosHeading > 0.0f)
									m_attractorHeading = m_fRotationCur - Asin(fSinHeading);
								else
									m_attractorHeading = m_fRotationCur - Acos(fCosHeading);
							}
							else {
								if (fCosHeading > 0.0f)
									m_attractorHeading = m_fRotationCur - Asin(fSinHeading);
								else
									m_attractorHeading = m_fRotationCur + Acos(fCosHeading);
							}
							m_fRotationDest = m_attractorHeading;
							m_headingRate = 3.5f;
							bReachedAttractorHeadingTarget = true;
							bTurnedAroundOnAttractor = false;
						}
						if (Abs(m_fRotationCur - m_attractorHeading) >= m_acceptableHeadingOffset &&
							Abs(m_fRotationCur - m_attractorHeading + TWOPI) >= m_acceptableHeadingOffset &&
							Abs(m_fRotationCur - m_attractorHeading - TWOPI) >= m_acceptableHeadingOffset)
							SetMoveState(PEDMOVE_STILL);
						else {
							m_fRotationDest = m_fRotationCur;
							bReachedAttractorHeadingTarget = false;
							bObjectiveCompleted = true;
							bScriptObjectiveCompleted = true;
							RestoreHeadingRate();
							GetPedAttractorManager()->BroadcastArrival(this, m_attractor);
							if (GetPedAttractorManager()->IsAtHeadOfQueue(this, m_attractor)) {
								switch (m_objective) {
								case OBJECTIVE_GOTO_SEAT_ON_FOOT:
									if (!bTurnedAroundOnAttractor) {
										ClearObjective();
										SetWaitState(WAITSTATE_SIT_DOWN, 0);
									}
									else {
										ClearObjective();
										SetWaitState(WAITSTATE_SIT_DOWN_RVRS, 0);
									}
									break;
								case OBJECTIVE_GOTO_ATM_ON_FOOT:
									ClearObjective();
									SetWaitState(WAITSTATE_USE_ATM, 0);
									break;
								case OBJECTIVE_GOTO_BUS_STOP_ON_FOOT:
									ClearObjective();
									SetObjective(OBJECTIVE_WAIT_ON_FOOT_AT_BUS_STOP);
									break;
								case OBJECTIVE_GOTO_PIZZA_ON_FOOT:
									ClearObjective();
									m_prevObjective = OBJECTIVE_NONE;
									SetObjective(OBJECTIVE_WAIT_ON_FOOT);
									m_objectiveTimer = CTimer::GetTimeInMilliseconds() + m_attractor->GetHeadOfQueueWaitTime();
									break;
								case OBJECTIVE_GOTO_SHELTER_ON_FOOT:
									m_prevObjective = OBJECTIVE_NONE;
									SetObjective(OBJECTIVE_WAIT_ON_FOOT_AT_SHELTER);
									break;
								case OBJECTIVE_GOTO_ICE_CREAM_VAN_ON_FOOT:
									m_prevObjective = OBJECTIVE_NONE;
									SetObjective(OBJECTIVE_WAIT_ON_FOOT_AT_ICE_CREAM_VAN);
									break;
								}
							} else {
								m_prevObjective = OBJECTIVE_NONE;
								SetObjective(OBJECTIVE_WAIT_ON_FOOT);
								m_objectiveTimer = 0;
							}
						}
					}
				}
				return;
			case OBJECTIVE_FLEE_CAR:
				if (!bInVehicle && m_nPedState != PED_FLEE_ENTITY && m_pMyVehicle) {
					RestorePreviousObjective();
					SetFlee(m_pMyVehicle, 6000);
					break;
				}
				// fall through
			case OBJECTIVE_LEAVE_CAR:
				if (CTimer::GetTimeInMilliseconds() > m_leaveCarTimer) {
					if (InVehicle() &&
						(FindPlayerPed() != this || !CPad::GetPad(0)->GetAccelerate() || bBusJacked)) {

						if (m_nPedState != PED_EXIT_CAR && m_nPedState != PED_DRAG_FROM_CAR && m_nPedState != PED_EXIT_TRAIN
							&& (m_nPedType != PEDTYPE_COP
								|| m_pMyVehicle->IsBoat()
								|| m_pMyVehicle->m_vecMoveSpeed.MagnitudeSqr2D() < sq(0.005f))) {
#ifdef GTA_TRAIN
							if (m_pMyVehicle->IsTrain())
								SetExitTrain(m_pMyVehicle);
							else
#endif
							if (m_pMyVehicle->IsBoat())
								SetExitBoat(m_pMyVehicle);
							else
								SetExitCar(m_pMyVehicle, 0);
						}
					} else {
						RestorePreviousObjective();
					}
				}
				if (bHeldHostageInCar) {
					if (CTheScripts::IsPlayerOnAMission()) {
						CVehicle *playerVeh = FindPlayerVehicle();
						if (playerVeh && playerVeh->IsPassenger(this)) {
							if (m_leaveCarTimer != 0)
								m_leaveCarTimer = 0;
						}
					}
				}
				break;
			case OBJECTIVE_AIM_GUN_AT:
				if (m_pedInObjective) {
					if (!bObstacleShowedUpDuringKillObjective)
						SetPointGunAt(m_pedInObjective);

					if (m_nMoveState == PEDMOVE_STILL && IsPedInControl()) {
						SetLookFlag(m_pedInObjective, false);
						TurnBody();
					}
				} else {
					ClearObjective();
				}
				break;
			case OBJECTIVE_WAIT_ON_FOOT_AT_SHELTER:
				SetIdle();
				if (m_attractor && CWeather::Rain < 0.2f)
					GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
				break;
			case OBJECTIVE_KILL_CHAR_ON_BOAT:
				SetPedStats(PEDSTAT_TOUGH_GUY);
				if (bInVehicle) {
					if (m_pedInObjective && m_pedInObjective->m_pCurrentPhysSurface != m_pMyVehicle) {
						bObjectiveCompleted = true;
						ClearObjective();
						CCarCtrl::SwitchVehicleToRealPhysics(m_pMyVehicle);
						m_pMyVehicle->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
						m_pMyVehicle->AutoPilot.m_nCruiseSpeed = GAME_SPEED_TO_CARAI_SPEED * m_pMyVehicle->pHandling->Transmission.fMaxCruiseVelocity;
						m_pMyVehicle->SetStatus(STATUS_PHYSICS);
					} else {
						SetObjective(OBJECTIVE_LEAVE_CAR, m_pMyVehicle);
					}
				} else if (m_pedInObjective && !m_pedInObjective->DyingOrDead() &&
					(!m_pCurrentPhysSurface || !m_pedInObjective->m_pCurrentPhysSurface ||
						m_pedInObjective->m_pCurrentPhysSurface == m_pCurrentPhysSurface)) {

					CBoat *boatWeAreOn = nil;
					if (m_pCurrentPhysSurface && m_pCurrentPhysSurface->IsVehicle() && ((CVehicle*)m_pCurrentPhysSurface)->IsBoat())
						boatWeAreOn = (CBoat*)m_pCurrentPhysSurface;

					if (boatWeAreOn) {
						SetObjective(OBJECTIVE_RUN_TO_AREA, boatWeAreOn->GetPosition() - (boatWeAreOn->GetForward() * 10.f));
					} else if (m_pedInObjective) {
						SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS, m_pedInObjective);
					}
					SetMoveAnim();
				} else {
					ClearLookFlag();
					SetMoveAnim();
					if (m_pCurrentPhysSurface && m_pCurrentPhysSurface->IsVehicle())
						SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, m_pCurrentPhysSurface);
				}
				break;
			case OBJECTIVE_SOLICIT_FOOT:
				if (m_pedInObjective) {
					if (m_objectiveTimer < CTimer::GetTimeInMilliseconds())
						bScriptObjectiveCompleted = true;
				} else {
					bScriptObjectiveCompleted = true;
				}
				break;
			case OBJECTIVE_WAIT_ON_FOOT_AT_BUS_STOP:
				SetIdle();
				if (m_attractor) {
					float left = GetPosition().x - 10.0f;
					float right = GetPosition().x + 10.0f;
					float top = GetPosition().y - 10.0f;
					float bottom = GetPosition().y + 10.0f;
					int xstart = Max(0, CWorld::GetSectorIndexX(left));
					int xend = Min(NUMSECTORS_X - 1, CWorld::GetSectorIndexX(right));
					int ystart = Max(0, CWorld::GetSectorIndexY(top));
					int yend = Min(NUMSECTORS_Y - 1, CWorld::GetSectorIndexY(bottom));
					assert(xstart <= xend);
					assert(ystart <= yend);

					float minDistance = SQR(10.0f);
					CVehicle* pBus = nil;

					for (int y = ystart; y <= yend; y++) {
						for (int x = xstart; x <= xend; x++) {
							CSector* s = CWorld::GetSector(x, y);
							for (CPtrNode* pNode = s->m_lists[ENTITYLIST_VEHICLES].first; pNode != nil; pNode = pNode->next) {
								CEntity* pEntity = (CEntity*)pNode->item;
								if (!pEntity->IsVehicle())
									continue;
								CVehicle* pVehicle = (CVehicle*)pEntity;
								if (!pVehicle->bIsBus)
									continue;
								if (pVehicle->GetMoveSpeed().MagnitudeSqr() >= SQR(0.005f))
									continue;
								float distanceSq = (GetPosition() - pVehicle->GetPosition()).MagnitudeSqr();
								if (distanceSq < minDistance) {
									minDistance = distanceSq;
									pBus = pVehicle;
								}
							}
						}
					}

					if (pBus) {
						if (pBus->m_nNumPassengers >= pBus->m_nNumMaxPassengers - 1)
							SetObjective(OBJECTIVE_WAIT_ON_FOOT);
						else {
							GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
							SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, pBus);
							bDontDragMeOutCar = true;
							bRemoveMeWhenIGotIntoCar = true;
							CPlayerPed *player = FindPlayerPed();
							if (pBus->IsPassenger(player) || pBus->IsDriver(player)) {
								bCollectBusFare = true;
							}
						}
					}
				}
				break;
			case OBJECTIVE_WAIT_ON_FOOT_AT_ICE_CREAM_VAN:
			{
				SetIdle();
				CVehicle* pIceCreamVan = GetPedAttractorManager()->GetIceCreamVanForEffect(m_attractor->GetEffect());
				if (m_attractor && m_nWaitState != WAITSTATE_PLAYANIM_CHAT && pIceCreamVan && pIceCreamVan->pDriver && pIceCreamVan->pDriver->IsPlayer()) {
					int time = 5000;
					SetWaitState(WAITSTATE_PLAYANIM_CHAT, &time);
					break;
				}
				if (!m_attractor)
					break;
				CVehicle* pVan = GetPedAttractorManager()->GetIceCreamVanForEffect(m_attractor->GetEffect());
				if (!pVan)
					break;
				if (0.01f * CTimer::GetTimeStep() * 5.0f < pVan->m_fDistanceTravelled) {
					GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
					break;
				}
				if (!pVan->pDriver || !pVan->pDriver->IsPlayer() || pVan->pDriver->GetPedState() == PED_ARRESTED || pVan->pDriver->GetPedState() == PED_DEAD) {
					GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
					break;
				}
				if (!pVan->m_bSirenOrAlarm) {
					GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
					return; // Why?
				}
				if (pVan->GetStatus() == STATUS_WRECKED) {
					GetPedAttractorManager()->DeRegisterPed(this, m_attractor);
					return; // Why?
				}
				break;
			}
		}
		if (bObjectiveCompleted
			|| m_objectiveTimer > 0 && CTimer::GetTimeInMilliseconds() > m_objectiveTimer) {
			RestorePreviousObjective();
			if (m_objectiveTimer > CTimer::GetTimeInMilliseconds() || !m_objectiveTimer)
				m_objectiveTimer = CTimer::GetTimeInMilliseconds() - 1;

			if (CharCreatedBy != RANDOM_CHAR || bInVehicle) {
				if (IsPedInControl())
					RestorePreviousState();
			} else {
				SetWanderPath(CGeneral::GetRandomNumber() & 7);
			}
			ClearAimFlag();
			ClearLookFlag();
		}
	}
}

void
CPed::SetFollowRoute(int16 currentPoint, int16 routeType)
{
	m_routeLastPoint = currentPoint;
	m_routeType = routeType;
	m_routePointsBeingPassed = 1;
	m_routePointsPassed = 0;
	m_objective = OBJECTIVE_FOLLOW_ROUTE;
	m_routeStartPoint = CRouteNode::GetRouteStart(currentPoint);
	m_nextRoutePointPos = CRouteNode::GetPointPosition(GetNextPointOnRoute());
}

int
CPed::GetNextPointOnRoute(void)
{
	int16 nextPoint = m_routePointsBeingPassed + m_routePointsPassed + m_routeStartPoint;

	// Route is complete
	if (nextPoint < 0 || nextPoint > NUMPEDROUTES || m_routeLastPoint != CRouteNode::GetRouteThisPointIsOn(nextPoint)) {

		switch (m_routeType) {
			case PEDROUTE_STOP_WHEN_DONE:
				nextPoint = -1;
				break;
			case PEDROUTE_GO_BACKWARD_WHEN_DONE:
				m_routePointsBeingPassed = -m_routePointsBeingPassed;
				nextPoint = m_routePointsBeingPassed + m_routePointsPassed + m_routeStartPoint;
				break;
			case PEDROUTE_GO_TO_START_WHEN_DONE:
				m_routePointsPassed = -1;
				nextPoint = m_routePointsBeingPassed + m_routePointsPassed + m_routeStartPoint;
				break;
			default:
				break;
		}
	}
	return nextPoint;
}

bool
CPed::HaveReachedNextPointOnRoute(float distToCountReached)
{
	if ((m_nextRoutePointPos - GetPosition()).Magnitude2D() < distToCountReached) {
		m_routePointsPassed += m_routePointsBeingPassed;
		return true;
	}
	return false;
}

bool
CPed::CanSeeEntity(CEntity *entity, float threshold)
{
	float neededAngle = CGeneral::GetRadianAngleBetweenPoints(
		entity->GetPosition().x,
		entity->GetPosition().y,
		GetPosition().x,
		GetPosition().y);

	if (neededAngle < 0.0f)
		neededAngle += TWOPI;
	else if (neededAngle > TWOPI)
		neededAngle -= TWOPI;

	float ourAngle = m_fRotationCur;
	if (ourAngle < 0.0f)
		ourAngle += TWOPI;
	else if (ourAngle > TWOPI)
		ourAngle -= TWOPI;

	float neededTurn = Abs(neededAngle - ourAngle);

	return neededTurn < threshold || TWOPI - threshold < neededTurn;
}

// Only used while deciding which gun ped should switch to, if no ammo left.
bool
CPed::SelectGunIfArmed(void)
{
	for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
		if (GetWeapon(i).m_nAmmoTotal > 0) {
			eWeaponType weaponType = GetWeapon(i).m_eWeaponType;

			if (weaponType == WEAPONTYPE_COLT45 || weaponType == WEAPONTYPE_UZI || weaponType == WEAPONTYPE_MP5 || weaponType == WEAPONTYPE_M4 ||
				weaponType == WEAPONTYPE_COLT45 || weaponType == WEAPONTYPE_PYTHON || weaponType == WEAPONTYPE_SHOTGUN ||
				weaponType == WEAPONTYPE_SPAS12_SHOTGUN || weaponType == WEAPONTYPE_STUBBY_SHOTGUN ||
				weaponType == WEAPONTYPE_ROCKETLAUNCHER || weaponType == WEAPONTYPE_SNIPERRIFLE || weaponType == WEAPONTYPE_FLAMETHROWER) {
				SetCurrentWeapon(i);
				return true;
			}
		}
	}
	SetCurrentWeapon(WEAPONTYPE_UNARMED);
	return false;
}
void
CPed::ReactToPointGun(CEntity *entWithGun)
{
	CPed *pedWithGun = (CPed*)entWithGun;
	int waitTime;

	if (IsPlayer() || !IsPedInControl() || (CharCreatedBy == MISSION_CHAR && !bCrouchWhenScared))
		return;

	if (m_leader == pedWithGun)
		return;

	if (m_nWaitState == WAITSTATE_PLAYANIM_HANDSUP || m_nWaitState == WAITSTATE_PLAYANIM_HANDSCOWER ||
		(GetPosition() - pedWithGun->GetPosition()).MagnitudeSqr2D() > 225.0f || (m_nPedType == PEDTYPE_GANG7 && pedWithGun == FindPlayerPed()))
		return;

	if (m_leader) {
		if (FindPlayerPed() == m_leader)
			return;

		ClearLeader();
	}
	if (m_pedStats->m_flags & STAT_GUN_PANIC
		&& (m_nPedState != PED_ATTACK || GetWeapon()->IsTypeMelee())
		&& m_nPedState != PED_FLEE_ENTITY && m_nPedState != PED_AIM_GUN) {

		waitTime = CGeneral::GetRandomNumberInRange(3000, 6000);
		SetWaitState(WAITSTATE_PLAYANIM_HANDSCOWER, &waitTime);
		Say(SOUND_PED_HANDS_COWER);
		m_pLookTarget = pedWithGun;
		m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
		SetMoveState(PEDMOVE_NONE);

	} else if (m_nPedType != pedWithGun->m_nPedType) {
		if (IsGangMember() || m_nPedType == PEDTYPE_EMERGENCY || m_nPedType == PEDTYPE_FIREMAN) {
			RegisterThreatWithGangPeds(pedWithGun);
		}

		if (m_nPedType == PEDTYPE_COP) {
			if (pedWithGun->IsPlayer()) {
				((CPlayerPed*)pedWithGun)->m_pWanted->SetWantedLevelNoDrop(2);
				if (bCrouchWhenShooting || bKindaStayInSamePlace) {
					SetDuck(CGeneral::GetRandomNumberInRange(1000, 3000));
					return;
				}
			}
		}

		if (m_nPedType != PEDTYPE_COP
			&& (m_nPedState != PED_ATTACK || GetWeapon()->IsTypeMelee())
			&& (m_nPedState != PED_FLEE_ENTITY || pedWithGun->IsPlayer() && m_fleeFrom != pedWithGun)
			&& m_nPedState != PED_AIM_GUN && m_objective != OBJECTIVE_KILL_CHAR_ON_FOOT) {

			waitTime = CGeneral::GetRandomNumberInRange(3000, 6000);
			SetWaitState(WAITSTATE_PLAYANIM_HANDSUP, &waitTime);
			Say(SOUND_PED_HANDS_UP);
			m_pLookTarget = pedWithGun;
			m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
			SetMoveState(PEDMOVE_NONE);
			if (m_nPedState == PED_FLEE_ENTITY) {
				m_fleeFrom = pedWithGun;
				m_fleeFrom->RegisterReference((CEntity **) &m_fleeFrom);
			}

			if (FindPlayerPed() == pedWithGun && bRichFromMugging) {
				int money = CGeneral::GetRandomNumberInRange(100, 300);
				int pickupCount = money / 40 + 1;
				int moneyPerPickup = money / pickupCount;

				for (int i = 0; i < pickupCount; i++) {
					float pickupX = 1.5f * Sin((CGeneral::GetRandomNumber() % 256)/256.0f * TWOPI) + GetPosition().x;
					float pickupY = 1.5f * Cos((CGeneral::GetRandomNumber() % 256)/256.0f * TWOPI) + GetPosition().y;
					bool found = false;
					float groundZ = CWorld::FindGroundZFor3DCoord(pickupX, pickupY, GetPosition().z, &found) + 0.5f;
					if (found) {
						CPickups::GenerateNewOne(CVector(pickupX, pickupY, groundZ), MI_MONEY, PICKUP_MONEY, moneyPerPickup + (CGeneral::GetRandomNumber() & 7));
					}
				}
				bRichFromMugging = false;
			}
		}
	}
}

void
CPed::ReactToAttack(CEntity *attacker)
{
	if (IsPlayer() && attacker->IsPed()) {
		InformMyGangOfAttack(attacker);
		SetLookFlag(attacker, true);
		SetLookTimer(700);
		return;
	}
	
	if (m_nPedType == PEDTYPE_GANG7 && attacker->IsPed() && ((CPed*)attacker)->IsPlayer()) {
		if (m_nPedState != PED_FALL) {
			SetFall(15000, (AnimationId)(ANIM_STD_KO_FRONT + CGeneral::GetRandomNumberInRange(0, 5)), 0);
		}

	} else if (m_nPedState == PED_DRIVING && InVehicle()
		&& (m_pMyVehicle->pDriver == this || m_pMyVehicle->pDriver && m_pMyVehicle->pDriver->m_nPedState == PED_DRIVING && m_pMyVehicle->pDriver->m_objective != OBJECTIVE_LEAVE_CAR_AND_DIE)) {

		if (m_pMyVehicle->VehicleCreatedBy == RANDOM_VEHICLE
			&& (m_pMyVehicle->GetStatus() == STATUS_SIMPLE || m_pMyVehicle->GetStatus() == STATUS_PHYSICS)
			&& m_pMyVehicle->AutoPilot.m_nCarMission == MISSION_CRUISE) {

			CCarCtrl::SwitchVehicleToRealPhysics(m_pMyVehicle);
			m_pMyVehicle->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
			m_pMyVehicle->AutoPilot.m_nCruiseSpeed = GAME_SPEED_TO_CARAI_SPEED * m_pMyVehicle->pHandling->Transmission.fMaxCruiseVelocity;
			m_pMyVehicle->SetStatus(STATUS_PHYSICS);
		}

	} else if ((IsPedInControl() || m_nPedState == PED_DRIVING) && (CharCreatedBy != MISSION_CHAR || bRespondsToThreats)) {
		if (m_leader != attacker && (!m_leader || FindPlayerPed() != m_leader) && attacker->IsPed()) {

			CPed *attackerPed = (CPed*)attacker; 
			if (bNotAllowedToDuck) {
				if (!attackerPed->GetWeapon()->IsTypeMelee()) {
					m_duckAndCoverTimer = CTimer::GetTimeInMilliseconds();
					return;
				}
			} else if (bCrouchWhenShooting || bKindaStayInSamePlace) {
				SetDuck(CGeneral::GetRandomNumberInRange(1000,3000));
				return;
			}

			if (m_nWaitState == WAITSTATE_STRIPPER) {
				ClearWaitState();
				SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, attacker);
				SetObjectiveTimer(20000);

			} else {
				if (m_pedStats->m_fear <= 100 - attackerPed->m_pedStats->m_temper) {
					if (m_pedStats != attackerPed->m_pedStats) {
						if (IsGangMember() || m_nPedType == PEDTYPE_EMERGENCY || m_nPedType == PEDTYPE_FIREMAN) {
							RegisterThreatWithGangPeds(attackerPed);
						}
						if (!attackerPed->GetWeapon()->IsTypeMelee() && GetWeapon()->IsTypeMelee()) {
							SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, attacker);
							SetMoveState(PEDMOVE_RUN);
						} else {
							SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, attacker);
							SetObjectiveTimer(20000);
						}
					}
				} else {
					SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, attackerPed);
					SetMoveState(PEDMOVE_RUN);
					if (attackerPed->GetWeapon()->IsTypeMelee())
						Say(SOUND_PED_FLEE_RUN);
				}
			}
		}
	}
}

void
CPed::PedAnimAlignCB(CAnimBlendAssociation *animAssoc, void *arg)
{
	CPed *ped = (CPed*)arg;

	CVehicle *veh = ped->m_pMyVehicle;
	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;

	if (!ped->IsNotInWreckedVehicle())
		return;

	if (!ped->EnteringCar()) {
		if (ped->m_nPedState != PED_DRIVING)
			ped->QuitEnteringCar();

		return;
	}

	if (!ped->m_vehDoor) {
		ped->QuitEnteringCar();
		return;
	}

	if (ped->m_fHealth == 0.0f) {
		ped->QuitEnteringCar();
		return;
	}
	bool itsVan = !!veh->bIsVan;
	bool itsBus = !!veh->bIsBus;
	bool itsLow = !!veh->bLowVehicle;
	eDoors enterDoor;

	switch (ped->m_vehDoor) {
		case CAR_DOOR_RF:
			itsVan = false;
			enterDoor = DOOR_FRONT_RIGHT;
			break;
		case CAR_DOOR_RR:
			enterDoor = DOOR_REAR_RIGHT;
			break;
		case CAR_DOOR_LF:
			itsVan = false;
			enterDoor = DOOR_FRONT_LEFT;
			break;
		case CAR_DOOR_LR:
			enterDoor = DOOR_REAR_LEFT;
			break;
		default:
			break;
	}

	if (veh->IsBike()) {
		CPed *pedToDragOut = nil;
		if (veh->GetStatus() == STATUS_ABANDONED) {
			if (ped->m_vehDoor == CAR_WINDSCREEN) {
				ped->m_pVehicleAnim = CAnimManager::BlendAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType, ANIM_BIKE_KICK, 6.0f);
				ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
				((CBike*)veh)->bIsBeingPickedUp = true;

			} else if (veh->GetRight().z >= 0.5f || veh->GetRight().z <= -0.5f || veh->GetUp().z <= 0.0f) {
				if (enterDoor == DOOR_FRONT_LEFT || enterDoor == DOOR_REAR_LEFT) {
					if (veh->GetRight().z > 0.0f)
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_BIKE_PICKUP_LHS);
					else
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_BIKE_PULLUP_LHS);

				} else {
					if (veh->GetRight().z < 0.0f)
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_BIKE_PICKUP_RHS);
					else
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_BIKE_PULLUP_RHS);
				}
				ped->m_pVehicleAnim->SetFinishCallback(PedAnimDoorOpenCB, ped);

			} else {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType,
					enterDoor == DOOR_FRONT_LEFT || enterDoor == DOOR_REAR_LEFT ? ANIM_BIKE_JUMPON_LHS : ANIM_BIKE_JUMPON_RHS);
				ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
				((CBike*)veh)->bIsBeingPickedUp = true;
			}
		} else if (ped->m_vehDoor == CAR_WINDSCREEN) {
			if (veh->pDriver->m_nPedState != PED_DRIVING || veh->pDriver->bDontDragMeOutCar) {
				ped->QuitEnteringCar();
			} else {
				ped->m_pVehicleAnim = CAnimManager::BlendAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType, ANIM_BIKE_KICK, 6.0f);
				ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
				pedToDragOut = veh->pDriver;
			}
			((CBike*)veh)->bIsBeingPickedUp = true;
		} else {
			if (enterDoor == DOOR_FRONT_LEFT || enterDoor == DOOR_FRONT_RIGHT) {
				if (veh->pDriver) {
					if (veh->m_vecMoveSpeed.Magnitude() > 0.2f) {
						ped->QuitEnteringCar();
						ped->SetFall(1000, ped->m_vehDoor == CAR_DOOR_LF || ped->m_vehDoor == CAR_DOOR_LR ? ANIM_STD_HIGHIMPACT_RIGHT : ANIM_STD_HIGHIMPACT_LEFT, false);
						return;
					}
					if (veh->pDriver->m_nPedState != PED_DRIVING || veh->pDriver->bDontDragMeOutCar) {
						ped->QuitEnteringCar();
					} else {
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, enterDoor == DOOR_FRONT_LEFT ? ANIM_STD_BIKE_ELBOW_LHS : ANIM_STD_BIKE_ELBOW_RHS);
						ped->m_pVehicleAnim->SetFinishCallback(PedAnimPullPedOutCB, ped);
						pedToDragOut = veh->pDriver;
					}
					((CBike*)veh)->bIsBeingPickedUp = true;

				} else {
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType, enterDoor == DOOR_FRONT_LEFT ? ANIM_BIKE_JUMPON_LHS : ANIM_BIKE_JUMPON_RHS);
					ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
					((CBike*)veh)->bIsBeingPickedUp = true;
				}
			} else {
				if (veh->pPassengers[0]) {
					if (veh->m_vecMoveSpeed.Magnitude() > 0.2f) {
						ped->QuitEnteringCar();
						ped->SetFall(1000, ped->m_vehDoor == CAR_DOOR_LF || ped->m_vehDoor == CAR_DOOR_LR ? ANIM_STD_HIGHIMPACT_RIGHT : ANIM_STD_HIGHIMPACT_LEFT, false);
						return;
					}
					if (veh->pPassengers[0]->m_nPedState != PED_DRIVING || veh->pPassengers[0]->bDontDragMeOutCar) {
						ped->QuitEnteringCar();
					} else {
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD,
							enterDoor == DOOR_REAR_LEFT ? ANIM_STD_BIKE_ELBOW_LHS : ANIM_STD_BIKE_ELBOW_RHS);
						ped->m_pVehicleAnim->SetFinishCallback(PedAnimPullPedOutCB, ped);
						pedToDragOut = veh->pPassengers[0];
					}
					((CBike*)veh)->bIsBeingPickedUp = true;

				} else {
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(),
						((CBike*)veh)->m_bikeAnimType, enterDoor == DOOR_REAR_LEFT ? ANIM_BIKE_JUMPON_LHS : ANIM_BIKE_JUMPON_RHS);
					ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
					((CBike*)veh)->bIsBeingPickedUp = true;
				}
			}
		}

		if (pedToDragOut) {
			pedToDragOut->SetBeingDraggedFromCar(veh, ped->m_vehDoor, false);
			if (pedToDragOut->IsGangMember())
				pedToDragOut->RegisterThreatWithGangPeds(ped);

			if (ped->m_nPedType == PEDTYPE_COP && pedToDragOut == FindPlayerPed() && veh->IsBike())
				((CCopPed*)ped)->m_bDragsPlayerFromCar = 1;

			if (pedToDragOut == veh->pDriver) {
				if (veh->pPassengers[0])
					veh->pPassengers[0]->SetBeingDraggedFromCar(veh, CAR_DOOR_LR, false);
			}
		}
		return;
	}

	if (veh->IsDoorMissing(enterDoor) || veh->IsDoorFullyOpen(enterDoor)) {

		veh->AutoPilot.m_nCruiseSpeed = 0;
		if (ped->m_nPedState == PED_CARJACK || veh->m_nNumMaxPassengers == 0 && veh->pDriver && enterDoor == DOOR_FRONT_RIGHT) {
			ped->PedAnimDoorOpenCB(nil, ped);
			return;
		}
		if (enterDoor != DOOR_FRONT_LEFT && enterDoor != DOOR_REAR_LEFT) {
			if (itsVan) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_GET_IN_REAR_RHS);
			} else if (itsBus) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_GET_IN_RHS);
			} else if (itsLow) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_RHS);
			} else {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_RHS);
			}
		} else if (itsVan) {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_GET_IN_REAR_LHS);
		} else if (itsBus) {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_GET_IN_LHS);
		} else if (itsLow) {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_LHS);
		} else {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LHS);
		}
		ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);

	} else if (veh->CanPedOpenLocks(ped)) {

		veh->AutoPilot.m_nCruiseSpeed = 0;
		if (enterDoor != DOOR_FRONT_LEFT && enterDoor != DOOR_REAR_LEFT) {
			if (itsVan) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_OPEN_DOOR_REAR_RHS);
			} else if (itsBus) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_OPEN_RHS);
			} else {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_OPEN_DOOR_RHS);
			}
		} else if (itsVan) {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_OPEN_DOOR_REAR_LHS);
		} else if (itsBus) {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_OPEN_LHS);
		} else {

			if (ped->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER && veh->pDriver) {

				if (!veh->bLowVehicle
					&& veh->pDriver->CharCreatedBy != MISSION_CHAR
					&& veh->pDriver->m_nPedState == PED_DRIVING) {

					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_QUICKJACK);
					ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);

					CPlayerPed *player = nil;
					CCopPed *cop = nil;
					veh->MakeNonDraggedPedsLeaveVehicle(veh->pDriver, ped, player, cop);
					if (player && cop) {
						cop->QuitEnteringCar();
						cop->SetArrestPlayer(player);
					}

					if (player != veh->pDriver) {
						veh->pDriver->SetBeingDraggedFromCar(veh, ped->m_vehDoor, true);
						if (veh->pDriver->IsGangMember())
							veh->pDriver->RegisterThreatWithGangPeds(ped);
					}
					return;
				}
			}
			if (veh->IsOpenTopCar() && !veh->pDriver && ped->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_JUMP_IN_LO_LHS);
				ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
				return;
			}
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_OPEN_DOOR_LHS);
		}
		ped->m_pVehicleAnim->SetFinishCallback(PedAnimDoorOpenCB, ped);

	} else {
		if (enterDoor != DOOR_FRONT_LEFT && enterDoor != DOOR_REAR_LEFT)
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CARDOOR_LOCKED_RHS);
		else
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CARDOOR_LOCKED_LHS);

		ped->bCancelEnteringCar = true;
		ped->m_pVehicleAnim->SetFinishCallback(PedAnimDoorOpenCB, ped);
	}
}

void
CPed::PedAnimDoorOpenCB(CAnimBlendAssociation* animAssoc, void* arg)
{
	CPed* ped = (CPed*)arg;

	CVehicle* veh = ped->m_pMyVehicle;

	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;

	if (!ped->IsNotInWreckedVehicle())
		return;

	if (!ped->EnteringCar()) {
		if(ped->m_nPedState != PED_DRIVING)
			ped->QuitEnteringCar();

		return;
	}

	eDoors door;
	CPed *pedInSeat = nil;
	switch (ped->m_vehDoor) {
		case CAR_DOOR_RF:
			door = DOOR_FRONT_RIGHT;
			pedInSeat = veh->pPassengers[0];
			if (!veh->pPassengers[0] && ped->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER)
				pedInSeat = veh->pDriver;
			break;
		case CAR_DOOR_RR:
			door = DOOR_REAR_RIGHT;
			pedInSeat = veh->pPassengers[2];
			break;
		case CAR_DOOR_LF:
			door = DOOR_FRONT_LEFT;
			pedInSeat = veh->pDriver;
			if (veh->bIsBus && ped->m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER)
				pedInSeat = nil;
			break;
		case CAR_DOOR_LR:
			door = DOOR_REAR_LEFT;
			pedInSeat = veh->pPassengers[1];
			break;
		default: assert(0);
	}

	if (ped->m_fHealth == 0.0f || CPad::GetPad(0)->ArePlayerControlsDisabled() && pedInSeat && pedInSeat->IsPlayer()) {
		ped->QuitEnteringCar();
		return;
	}

	bool isVan = veh->bIsVan;
	bool isBus = veh->bIsBus;
	bool isLow = veh->bLowVehicle;
	bool vehUpsideDown = veh->IsUpsideDown();
	if (ped->bCancelEnteringCar) {
		if (ped->IsPlayer()) {
			if (veh->pDriver) {
				if (veh->pDriver->m_nPedType == PEDTYPE_COP) {
					FindPlayerPed()->SetWantedLevelNoDrop(1);
				}
			}
		}
#ifdef CANCELLABLE_CAR_ENTER
		if (!veh->IsDoorMissing(door) && veh->CanPedOpenLocks(ped) && veh->IsCar()) {
			((CAutomobile*)veh)->Damage.SetDoorStatus(door, DOOR_STATUS_SWINGING);
		}
#endif
		ped->QuitEnteringCar();
		ped->RestorePreviousObjective();
		ped->bCancelEnteringCar = false;
		return;
	}
	if (!veh->IsDoorMissing(door) && veh->IsCar()) {
		((CAutomobile*)veh)->Damage.SetDoorStatus(door, DOOR_STATUS_SWINGING);
	}

	if (veh->m_vecMoveSpeed.Magnitude() > 0.2f ||
		veh->IsCar() && veh->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI && ((CAutomobile*)veh)->m_nWheelsOnGround == 0) {
		ped->QuitEnteringCar();
		if (ped->m_vehDoor != CAR_DOOR_LF && ped->m_vehDoor != CAR_DOOR_LR)
			ped->SetFall(1000, ANIM_STD_HIGHIMPACT_LEFT, false);
		else
			ped->SetFall(1000, ANIM_STD_HIGHIMPACT_RIGHT, false);
		
		return;
	}
	veh->ProcessOpenDoor(ped->m_vehDoor, ANIM_STD_CAR_OPEN_DOOR_LHS, 1.0f);

	if (ped->m_vehDoor == CAR_DOOR_LF || ped->m_vehDoor == CAR_DOOR_RF)
		isVan = false;

	if (ped->m_nPedState != PED_CARJACK || isBus) {

		if (ped->m_vehDoor == CAR_DOOR_LF || ped->m_vehDoor == CAR_DOOR_LR) {
			if (veh->IsBike()) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType, ANIM_BIKE_JUMPON_LHS);
			} else if (isVan) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_GET_IN_REAR_LHS);
			} else if (isBus) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_GET_IN_LHS);
			} else if (isLow) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_LHS);
			} else {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LHS);
			}
		} else {
			if (veh->IsBike()) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType, ANIM_BIKE_JUMPON_RHS);
			} else if (isVan) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_GET_IN_REAR_RHS);
			} else if (isBus) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_GET_IN_RHS);
			} else if (isLow) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_RHS);
			} else {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_RHS);
			}

			if (ped->m_vehDoor == CAR_DOOR_RF && pedInSeat && veh->IsCar())
				pedInSeat->SetObjective(OBJECTIVE_LEAVE_CAR, veh);
		}
		
		ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
	} else {
		CPed *pedToDragOut = nil;
		switch (ped->m_vehDoor) {
			case CAR_DOOR_RF: pedToDragOut = veh->pPassengers[0]; break;
			case CAR_DOOR_RR: pedToDragOut = veh->pPassengers[2]; break;
			case CAR_DOOR_LF: pedToDragOut = veh->pDriver; break;
			case CAR_DOOR_LR: pedToDragOut = veh->pPassengers[1]; break;
			default: assert(0);
		}

		if (vehUpsideDown) {
			ped->QuitEnteringCar();
			if (ped->m_nPedType == PEDTYPE_COP)
				((CCopPed*)ped)->SetArrestPlayer(ped->m_pedInObjective);
		}

		if (ped->m_vehDoor != CAR_DOOR_LF && ped->m_vehDoor != CAR_DOOR_LR) {

			if (pedToDragOut && !pedToDragOut->bDontDragMeOutCar) {
				if (pedToDragOut->m_nPedState != PED_DRIVING) {
					ped->QuitEnteringCar();
					pedToDragOut = nil;
				} else {
					if (isLow)
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_PULL_OUT_PED_LO_RHS);
					else
						ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_PULL_OUT_PED_RHS);

					ped->m_pVehicleAnim->SetFinishCallback(PedAnimPullPedOutCB, ped);
				}
			} else if (ped->m_nPedType == PEDTYPE_COP) {
				ped->QuitEnteringCar();
				if (ped->m_pedInObjective && ped->m_pedInObjective->m_nPedState == PED_DRIVING) {
					veh->SetStatus(STATUS_PLAYER_DISABLED);

					if (ped->m_pedInObjective->IsPlayer()) {
						((CCopPed*)ped)->SetArrestPlayer(ped->m_pedInObjective);
					} else {
						ped->ClearObjective();
						ped->SetWanderPath(CGeneral::GetRandomNumberInRange(0.f, 8.f));
					}

				} else if (!veh->IsDoorMissing(DOOR_FRONT_RIGHT)) {
					((CAutomobile*)veh)->Damage.SetDoorStatus(DOOR_FRONT_RIGHT, DOOR_STATUS_SWINGING);
				}
			} else {
				if (isLow)
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_RHS);
				else
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_RHS);

				ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
			}
		} else if (pedToDragOut) {

			if (pedToDragOut->m_nPedState != PED_DRIVING || pedToDragOut->bDontDragMeOutCar) {
				ped->QuitEnteringCar();
				pedToDragOut = nil;
			} else {
				if (isLow)
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_PULL_OUT_PED_LO_LHS);
				else
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_PULL_OUT_PED_LHS);
					
				ped->m_pVehicleAnim->SetFinishCallback(PedAnimPullPedOutCB, ped);
			}
		} else {
			if (isLow)
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_LHS);
			else
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LHS);

			ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
		}

		if (pedToDragOut) {
			CPlayerPed* player = nil;
			CCopPed* cop = nil;
			veh->MakeNonDraggedPedsLeaveVehicle(pedToDragOut, ped, player, cop);
			if (player && cop) {
				cop->QuitEnteringCar();
				veh->SetStatus(STATUS_PLAYER_DISABLED);
				cop->SetArrestPlayer(player);
			}

			if (player != pedToDragOut) {
				pedToDragOut->SetBeingDraggedFromCar(veh, ped->m_vehDoor, false);
				if (pedToDragOut->IsGangMember())
					pedToDragOut->RegisterThreatWithGangPeds(ped);
			}
		}
	}
	return;
}

void
CPed::PedAnimPullPedOutCB(CAnimBlendAssociation* animAssoc, void* arg)
{
	CPed* ped = (CPed*)arg;

	CVehicle* veh = ped->m_pMyVehicle;
	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;

	if (ped->EnteringCar()) {
		if (!ped->IsNotInWreckedVehicle())
			return;

#ifdef CANCELLABLE_CAR_ENTER
		if (ped->bCancelEnteringCar) {
			ped->QuitEnteringCar();
			ped->RestorePreviousObjective();
			ped->bCancelEnteringCar = false;
			return;
		}
#endif

		bool isLow = !!veh->bLowVehicle;

		int padNo;
		if (ped->IsPlayer()) {

			// BUG? This will cause crash if m_nPedType is bigger then 1, there are only 2 pads
			switch (ped->m_nPedType) {
				case PEDTYPE_PLAYER1:
					padNo = 0;
					break;
				case PEDTYPE_PLAYER2:
					padNo = 1;
					break;
				case PEDTYPE_PLAYER3:
					padNo = 2;
					break;
				case PEDTYPE_PLAYER4:
					padNo = 3;
					break;
			}
			CPad *pad = CPad::GetPad(padNo);

			if (!pad->ArePlayerControlsDisabled()) {

				if (pad->GetTarget()
					|| pad->NewState.LeftStickX
					|| pad->NewState.LeftStickY
					|| pad->NewState.DPadUp
					|| pad->NewState.DPadDown
					|| pad->NewState.DPadLeft
					|| pad->NewState.DPadRight) {
					ped->QuitEnteringCar();
					ped->RestorePreviousObjective();
					return;
				}
			}
		}

		if (ped->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER) {
			if (ped->m_vehDoor == CAR_DOOR_LF || ped->m_vehDoor == CAR_DOOR_LR) {
				if (veh->IsBike())
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType, ANIM_BIKE_JUMPON_LHS);
				else if (isLow)
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_LHS);
				else
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LHS);
			} else {
				if (veh->IsBike())
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ((CBike*)veh)->m_bikeAnimType, ANIM_BIKE_JUMPON_RHS);
				else if (isLow)
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_RHS);
				else
					ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_RHS);
			}
			ped->m_pVehicleAnim->SetFinishCallback(PedAnimGetInCB, ped);
		} else {
			ped->QuitEnteringCar();
		}
	} else if(ped->m_nPedState != PED_DRIVING) {
		ped->QuitEnteringCar();
	}
}

void
CPed::PedAnimGetInCB(CAnimBlendAssociation *animAssoc, void *arg)
{
	CPed *ped = (CPed*) arg;

	CVehicle *veh = ped->m_pMyVehicle;
	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;

	if (!ped->IsNotInWreckedVehicle() || ped->DyingOrDead())
		return;

	if (!ped->EnteringCar()) {
		if(ped->m_nPedState != PED_DRIVING)
			ped->QuitEnteringCar();
		return;
	}

	ped->RemoveWeaponWhenEnteringVehicle();
	if (ped->IsPlayer() && ped->bGonnaKillTheCarJacker && ((CPlayerPed*)ped)->m_pArrestingCop) {
		PedSetInCarCB(nil, ped);
		ped->m_nLastPedState = ped->m_nPedState;
		ped->SetPedState(PED_ARRESTED);
		ped->bGonnaKillTheCarJacker = false;
		if (veh) {
			veh->m_nNumGettingIn = 0;
			veh->m_nGettingInFlags = 0;	
			veh->bIsHandbrakeOn = true;
			veh->SetStatus(STATUS_PLAYER_DISABLED);
		}
		return;
	}
	if (ped->IsPlayer() && ped->m_vehDoor == CAR_DOOR_LF
		&& (Pads[0].GetAccelerate() >= 255.0f || Pads[0].GetBrake() >= 255.0f)
		&& veh->IsCar() && !veh->pDriver) {

		if (!animAssoc || animAssoc->animId != ANIM_STD_CAR_JUMP_IN_LO_LHS)
		if (((CAutomobile*)veh)->Damage.GetDoorStatus(DOOR_FRONT_LEFT) != DOOR_STATUS_MISSING)
			((CAutomobile*)veh)->Damage.SetDoorStatus(DOOR_FRONT_LEFT, DOOR_STATUS_SWINGING);

		PedSetInCarCB(nil, ped);
		return;
	}
	if (veh->IsBike()) {
		ped->PedSetInCarCB(nil, ped);
		return;
	}
	bool isVan = !!veh->bIsVan;
	bool isBus = !!veh->bIsBus;
	bool isLow = !!veh->bLowVehicle;
	eDoors enterDoor;
	switch (ped->m_vehDoor) {
		case CAR_DOOR_RF:
			isVan = false;
			enterDoor = DOOR_FRONT_RIGHT;
			break;
		case CAR_DOOR_RR:
			enterDoor = DOOR_REAR_RIGHT;
			break;
		case CAR_DOOR_LF:
			isVan = false;
			enterDoor = DOOR_FRONT_LEFT;
			break;
		case CAR_DOOR_LR:
			enterDoor = DOOR_REAR_LEFT;
			break;
		default:
			break;
	}
	bool doorClosed = true;
	if (veh->IsOpenTopCar() && enterDoor == DOOR_FRONT_LEFT && veh->IsDoorClosed(DOOR_FRONT_LEFT)) {
		doorClosed = false;

	} else if (!veh->IsDoorMissing(enterDoor)) {
		if (veh->IsCar())
			((CAutomobile*)veh)->Damage.SetDoorStatus(enterDoor, DOOR_STATUS_SWINGING);
	}

	CPed *driver = veh->pDriver;
	if (driver && (ped->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || ped->m_nPedState == PED_CARJACK)) {
		if (veh->bIsBus) {
			driver->SetObjective(OBJECTIVE_LEAVE_CAR, veh);
			if (driver->IsPlayer()) {
				veh->bIsHandbrakeOn = true;
				veh->SetStatus(STATUS_PLAYER_DISABLED);
			}
			driver->bBusJacked = true;
			veh->bIsBeingCarJacked = false;
			PedSetInCarCB(nil, ped);
			if (ped->m_nPedType == PEDTYPE_COP
				|| ped->m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT
				|| ped->m_objective == OBJECTIVE_KILL_CHAR_ANY_MEANS) {
				ped->SetObjective(OBJECTIVE_LEAVE_CAR, veh);
			}
			ped->m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 400;
			return;
		}
		if (driver != ped && ped->m_vehDoor != CAR_DOOR_LF) {
			if (!driver->IsPlayer()) {
				driver->bUsePedNodeSeek = true;
				driver->m_pLastPathNode = nil;
				if (driver->m_pedStats->m_temper <= driver->m_pedStats->m_fear
					|| driver->CharCreatedBy == MISSION_CHAR
					|| veh->VehicleCreatedBy == MISSION_VEHICLE) {
					driver->bFleeAfterExitingCar = true;
				} else {
					driver->bGonnaKillTheCarJacker = true;
					veh->pDriver->SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, ped);

					if (veh->pDriver->m_nPedType == PEDTYPE_COP && ped->IsPlayer()) {
						FindPlayerPed()->SetWantedLevelNoDrop(1);
					}
				}
			}
			if ((ped->m_nPedType != PEDTYPE_EMERGENCY || veh->pDriver->m_nPedType != PEDTYPE_EMERGENCY)
				&& (ped->m_nPedType != PEDTYPE_COP || veh->pDriver->m_nPedType != PEDTYPE_COP)) {
				veh->pDriver->SetObjective(OBJECTIVE_LEAVE_CAR, veh);
				veh->pDriver->Say(SOUND_PED_CAR_JACKED);
				veh->pDriver->SetRadioStation();
				if (veh->m_nDoorLock == CARLOCK_UNLOCKED)
					ped->Say(SOUND_PED_CAR_JACKING);

			} else {
				ped->m_objective = OBJECTIVE_ENTER_CAR_AS_PASSENGER;
			}
		}
	}
	if (veh->IsDoorMissing(enterDoor) || !doorClosed || isBus) {
		PedAnimDoorCloseCB(nil, ped);
	} else {
		if (enterDoor != DOOR_FRONT_LEFT && enterDoor != DOOR_REAR_LEFT) {
			if (isVan) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_CLOSE_DOOR_REAR_RHS);
			} else if (isLow) {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_DOOR_LO_RHS);
			} else {
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_DOOR_RHS);
			}
		} else if (isVan) {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_CLOSE_DOOR_REAR_LHS);
		} else if (isLow) {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_DOOR_LO_LHS);
		} else {
			ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_DOOR_LHS);
		}
		ped->m_pVehicleAnim->SetFinishCallback(PedAnimDoorCloseCB, ped);
	}
}

void
CPed::PedShuffle(void)
{
	if (m_pMyVehicle->pPassengers[0] == this) {
		CPed *driver = m_pMyVehicle->pDriver;
		if (!driver || driver->m_objective == OBJECTIVE_LEAVE_CAR) {
			m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, m_pMyVehicle->bLowVehicle ? ANIM_STD_CAR_SHUFFLE_LO_RHS : ANIM_STD_CAR_SHUFFLE_RHS);
			m_objective = OBJECTIVE_ENTER_CAR_AS_DRIVER;
			m_pMyVehicle->RemovePassenger(this);
			bInVehicle = false;
			m_pVehicleAnim->SetFinishCallback(PedSetInCarCB, this);
		}
	}
}

void
CPed::PedAnimDoorCloseCB(CAnimBlendAssociation *animAssoc, void *arg)
{
	CPed *ped = (CPed*)arg;

	CAutomobile *veh = (CAutomobile*)(ped->m_pMyVehicle);
	
	if (!ped->IsNotInWreckedVehicle() || ped->DyingOrDead())
		return;

	if (ped->EnteringCar()) {
		bool isLow = !!veh->bLowVehicle;

		if (!veh->bIsBus)
			veh->ProcessOpenDoor(ped->m_vehDoor, ANIM_STD_CAR_CLOSE_DOOR_LHS, 1.0f);

		eDoors door;
		switch (ped->m_vehDoor) {
			case CAR_DOOR_RF: door = DOOR_FRONT_RIGHT; break;
			case CAR_DOOR_RR: door = DOOR_REAR_RIGHT; break;
			case CAR_DOOR_LF: door = DOOR_FRONT_LEFT; break;
			case CAR_DOOR_LR: door = DOOR_REAR_LEFT; break;
			default: assert(0);
		}

		if (veh->Damage.GetDoorStatus(door) == DOOR_STATUS_SWINGING)
			veh->Damage.SetDoorStatus(door, DOOR_STATUS_OK);

		if (door == DOOR_FRONT_LEFT || ped->m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER || veh->bIsBus || veh->m_nNumMaxPassengers == 0) {
			PedSetInCarCB(nil, ped);
		} else if (ped->m_vehDoor == CAR_DOOR_RF
				&& (veh->m_nGettingInFlags & CAR_DOOR_FLAG_LF ||
					(veh->pDriver != nil && 
						(veh->pDriver->m_objective != OBJECTIVE_LEAVE_CAR
							&& veh->pDriver->m_objective != OBJECTIVE_LEAVE_CAR_AND_DIE
							|| !veh->IsRoomForPedToLeaveCar(CAR_DOOR_LF, nil))))) {

			if (ped->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || ped->m_nPedState == PED_CARJACK)
				veh->bIsBeingCarJacked = false;

			ped->m_objective = OBJECTIVE_ENTER_CAR_AS_PASSENGER;
			PedSetInCarCB(nil, ped);

			ped->SetObjective(OBJECTIVE_LEAVE_CAR, veh);
			if (!ped->IsPlayer())
				ped->bFleeAfterExitingCar = true;

			ped->bUsePedNodeSeek = true;
			ped->m_pNextPathNode = nil;

		} else {
			if (animAssoc)
				animAssoc->blendDelta = -1000.0f;

			if (isLow)
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SHUFFLE_LO_RHS);
			else
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SHUFFLE_RHS);

			ped->m_pVehicleAnim->SetFinishCallback(PedSetInCarCB, ped);
		}
	} else if (ped->m_nPedState != PED_DRIVING) {
		ped->QuitEnteringCar();
	}
}

void
CPed::PedAnimShuffleCB(CAnimBlendAssociation* assoc, void* arg)
{
	CPed *ped = (CPed*)arg;
	if (ped->EnteringCar()) {
		PedSetInCarCB(nil, ped);
	} else if (ped->m_nPedState != PED_DRIVING) {
		ped->QuitEnteringCar();
	}
}

void
CPed::SetFormation(eFormation type)
{
	// FIX: Formations in GetFormationPosition were in range 1-8, whereas in here it's 0-7.
	//      To not change the behaviour, range in here tweaked by 1 with the use of enum.

	switch (m_pedFormation) {
		case FORMATION_REAR:
		case FORMATION_REAR_LEFT:
		case FORMATION_REAR_RIGHT:
		case FORMATION_FRONT_LEFT:
		case FORMATION_FRONT_RIGHT:
		case FORMATION_LEFT:
		case FORMATION_RIGHT:
		case FORMATION_FRONT:
			break;
		default:
			Error("Unknown formation type, PedAI.cpp");
			break;
	}
	m_pedFormation = type;
}

CVector
CPed::GetFormationPosition(void)
{
	if (!m_pedInObjective)
		return GetPosition();

	if (m_pedInObjective->m_nPedState == PED_DEAD) {
		if (!m_pedInObjective->m_pedInObjective) {
			m_pedInObjective = nil;
			return GetPosition();
		}
		m_pedInObjective = m_pedInObjective->m_pedInObjective;
	}

	CVector formationOffset;
	float offset = CGeneral::GetRandomNumberInRange(1.f, 1.25f) * 1.75f;
	switch (m_pedFormation) {
		case FORMATION_REAR:
			formationOffset = CVector(0.0f, -offset, 0.0f);
			break;
		case FORMATION_REAR_LEFT:
			formationOffset = CVector(-offset, -offset, 0.0f);
			break;
		case FORMATION_REAR_RIGHT:
			formationOffset = CVector(offset, -offset, 0.0f);
			break;
		case FORMATION_FRONT_LEFT:
			formationOffset = CVector(-offset, offset, 0.0f);
			break;
		case FORMATION_FRONT_RIGHT:
			formationOffset = CVector(offset, offset, 0.0f);
			break;
		case FORMATION_LEFT:
			formationOffset = CVector(-offset, 0.0f, 0.0f);
			break;
		case FORMATION_RIGHT:
			formationOffset = CVector(offset, 0.0f, 0.0f);
			break;
		case FORMATION_FRONT:
			formationOffset = CVector(0.0f, offset, 0.0f);
			break;
		default:
			formationOffset = CVector(0.0f, 0.0f, 0.0f);
			break;
	}
	return m_pedInObjective->GetMatrix() * formationOffset;
}

void
CPed::PedAnimStepOutCarCB(CAnimBlendAssociation* animAssoc, void* arg)
{
	CPed* ped = (CPed*)arg;

	CVehicle* veh = ped->m_pMyVehicle;
	if (animAssoc) {
		if ((animAssoc->animId == ANIM_STD_ROLLOUT_LHS || animAssoc->animId == ANIM_STD_ROLLOUT_RHS) && ped && ped->m_nPedState == PED_FALL) {
			ped->RestoreHeadingRate();
			return;
		}
		animAssoc->blendDelta = -1000.0f;
		if (animAssoc->animId == ANIM_BIKE_GETOFF_BACK)
			ped->RestoreHeadingRate();
	}

	if (!veh) {
		PedSetOutCarCB(nil, ped);
		return;
	}
	CVector posForZ = ped->GetPosition();
	CPedPlacement::FindZCoorForPed(&posForZ);
	if (ped->GetPosition().z - 0.5f > posForZ.z) {
		PedSetOutCarCB(nil, ped);
		return;
	}

	veh->m_nStaticFrames = 0;
	veh->m_vecMoveSpeed += CVector(0.001f, 0.001f, 0.001f);
	veh->m_vecTurnSpeed += CVector(0.001f, 0.001f, 0.001f);
	if (!veh->bIsBus)
		veh->ProcessOpenDoor(ped->m_vehDoor, ANIM_STD_GETOUT_LHS, 1.0f);

	/* 
	// Duplicate and only in PC for some reason
	if (!veh) {
		PedSetOutCarCB(nil, ped);
		return;
	}
	*/
	eDoors door;
	switch (ped->m_vehDoor) {
		case CAR_DOOR_RF:
			door = DOOR_FRONT_RIGHT;
			break;
		case CAR_DOOR_RR:
			door = DOOR_REAR_RIGHT;
			break;
		case CAR_DOOR_LF:
			door = DOOR_FRONT_LEFT;
			break;
		case CAR_DOOR_LR:
			door = DOOR_REAR_LEFT;
			break;
		default:
			break;
	}
	bool closeDoor = !veh->IsDoorMissing(door);

	int padNo;
	if (ped->IsPlayer()) {

		// BUG? This will cause crash if m_nPedType is bigger then 1, there are only 2 pads
		switch (ped->m_nPedType) {
			case PEDTYPE_PLAYER1:
				padNo = 0;
				break;
			case PEDTYPE_PLAYER2:
				padNo = 1;
				break;
			case PEDTYPE_PLAYER3:
				padNo = 2;
				break;
			case PEDTYPE_PLAYER4:
				padNo = 3;
				break;
		}
		CPad* pad = CPad::GetPad(padNo);
		bool engineIsIntact = veh->IsCar() && ((CAutomobile*)veh)->Damage.GetEngineStatus() >= 225;
		if (!pad->ArePlayerControlsDisabled() && veh->m_nDoorLock != CARLOCK_FORCE_SHUT_DOORS
			&& (pad->GetTarget()
				|| pad->NewState.LeftStickX
				|| pad->NewState.LeftStickY
				|| pad->NewState.DPadUp
				|| pad->NewState.DPadDown
				|| pad->NewState.DPadLeft
				|| pad->NewState.DPadRight)
			|| veh->bIsBus
			|| veh->m_pCarFire
			|| engineIsIntact) {
			closeDoor = false;
		}
	}

	if (ped->m_objective == OBJECTIVE_LEAVE_CAR_AND_DIE)
		closeDoor = false;

	if (!closeDoor) {
		if (!veh->IsDoorMissing(door) && !veh->bIsBus) {
			((CAutomobile*)veh)->Damage.SetDoorStatus(door, DOOR_STATUS_SWINGING);
		}
		PedSetOutCarCB(nil, ped);
		return;
	}

	if (ped->bFleeAfterExitingCar || ped->bGonnaKillTheCarJacker) {
#ifdef FIX_BUGS
		if (!veh->IsDoorMissing(door))
			((CAutomobile*)veh)->Damage.SetDoorStatus(door, DOOR_STATUS_SWINGING);
		PedSetOutCarCB(nil, ped);
		return;
#else
		if (!veh->IsDoorMissing(door))
			((CAutomobile*)veh)->Damage.SetDoorStatus(DOOR_FRONT_LEFT, DOOR_STATUS_SWINGING);
#endif
	} else {
		switch (door) {
			case DOOR_FRONT_LEFT:
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_LHS);
				break;
			case DOOR_FRONT_RIGHT:
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_RHS);
				break;
			case DOOR_REAR_LEFT:
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_LHS);
				break;
			case DOOR_REAR_RIGHT:
				ped->m_pVehicleAnim = CAnimManager::AddAnimation(ped->GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_CLOSE_RHS);
				break;
			default:
				break;
		}
	}

	if (ped->m_pVehicleAnim)
		ped->m_pVehicleAnim->SetFinishCallback(PedSetOutCarCB, ped);
	return;
}

void
CPed::LineUpPedWithCar(PedLineUpPhase phase)
{
	bool vehIsUpsideDown = false;
	bool stillGettingInOut = false;
	int vehAnim;
	float seatPosMult = 0.0f;
	float currentZ;
	float adjustedTimeStep;
	CVector autoZPos;

	if (CReplay::IsPlayingBack())
		return;

	if (!bChangedSeat && phase != LINE_UP_TO_CAR_2) {
		if (m_pMyVehicle->IsBike()) {
			if (RpAnimBlendClumpGetAssociation(GetClump(), ANIM_BIKE_RIDE) ||
				RpAnimBlendClumpGetAssociation(GetClump(), ANIM_BIKE_RIDE_P)) {
				SetPedPositionInCar();
				return;
			}
		} else {
			if (RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_CAR_SIT)) {
				SetPedPositionInCar();
				return;
			}
			if (RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_CAR_SIT_LO)) {
				SetPedPositionInCar();
				return;
			}
			if (RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_CAR_SIT_P)) {
				SetPedPositionInCar();
				return;
			}
			if (RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_CAR_SIT_P_LO)) {
				SetPedPositionInCar();
				return;
			}
		}
		bChangedSeat = true;
	}
	if (phase == LINE_UP_TO_CAR_FALL) {
		SetPedPositionInCar();
		autoZPos = GetPosition();
		CPedPlacement::FindZCoorForPed(&autoZPos);
		if (m_pVehicleAnim && (m_pVehicleAnim->animId == ANIM_STD_ROLLOUT_LHS || m_pVehicleAnim->animId == ANIM_STD_ROLLOUT_RHS)
			&& autoZPos.z > GetPosition().z) {
			m_matrix.GetPosition().z = autoZPos.z;
		}
		if (m_pVehicleAnim && m_pVehicleAnim->animId == ANIM_BIKE_HIT) {
			if (autoZPos.z > GetPosition().z)
				m_matrix.GetPosition().z += m_pVehicleAnim->GetProgress() * (autoZPos.z - GetPosition().z);

		} else if (m_pVehicleAnim) {
			if (m_pVehicleAnim->animId == ANIM_BIKE_GETOFF_BACK) {
				if (autoZPos.z > GetPosition().z) {
					m_matrix.GetPosition().z += (m_pVehicleAnim->currentTime * (20.f / 7.f)) * (autoZPos.z - GetPosition().z);
				}
			}
		}
		return;
	}
	if (phase == LINE_UP_TO_CAR_START) {
		m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	}
	CVehicle *veh = m_pMyVehicle;

	// Not quite right, IsUpsideDown func. checks for <= -0.9f.
	if (veh->GetUp().z <= -0.8f)
		vehIsUpsideDown = true;

	if (m_vehDoor == CAR_DOOR_RF || m_vehDoor == CAR_DOOR_RR) {
		if (vehIsUpsideDown) {
			m_fRotationDest = -PI + veh->GetForward().Heading();
		} else if (veh->bIsBus) {
			m_fRotationDest = 0.5f * PI + veh->GetForward().Heading();
		} else {
			m_fRotationDest = veh->GetForward().Heading();
		}
	} else if (m_vehDoor == CAR_DOOR_LF || m_vehDoor == CAR_DOOR_LR) {
		if (vehIsUpsideDown) {
			m_fRotationDest = veh->GetForward().Heading();
		} else if (veh->bIsBus) {
			m_fRotationDest = -0.5f * PI + veh->GetForward().Heading();
		} else {
			m_fRotationDest = veh->GetForward().Heading();
		}
	} else {
		// I don't know will this part ever run(maybe boats?), but the game also handles that. I don't know is it intentional.

		if (vehIsUpsideDown) {
			m_fRotationDest = veh->GetForward().Heading();
		} else if (veh->bIsBus) {
			m_fRotationDest = 0.5f * PI + veh->GetForward().Heading();
		} else if (m_vehDoor == CAR_WINDSCREEN) {
			m_fRotationDest = veh->GetForward().Heading() + PI;
		} else {
			m_fRotationDest = veh->GetForward().Heading();
		}
	}

	bool multExtractedFromAnim = false;
	bool multExtractedFromAnimBus = false;
	float zBlend;
	if (m_pVehicleAnim) {
		vehAnim = m_pVehicleAnim->animId;

		switch (vehAnim) {
			case ANIM_STD_JACKEDCAR_RHS:
			case ANIM_STD_JACKEDCAR_LO_RHS:
			case ANIM_STD_JACKEDCAR_LHS:
			case ANIM_STD_JACKEDCAR_LO_LHS:
			case ANIM_STD_VAN_GET_IN_REAR_LHS:
			case ANIM_STD_VAN_GET_IN_REAR_RHS:
				multExtractedFromAnim = true;
				zBlend = Max(m_pVehicleAnim->GetProgress() - 0.3f, 0.0f) / (1.0f - 0.3f);
				// fall through

			case ANIM_STD_QUICKJACKED:
			case ANIM_STD_GETOUT_LHS:
			case ANIM_STD_GETOUT_LO_LHS:
			case ANIM_STD_GETOUT_RHS:
			case ANIM_STD_GETOUT_LO_RHS:

				if (!multExtractedFromAnim) {
					multExtractedFromAnim = true;
					zBlend = Max(m_pVehicleAnim->GetProgress() - 0.5f, 0.0f) / (1.0f - 0.5f);
				}
				// fall through

			case ANIM_STD_CRAWLOUT_LHS:
			case ANIM_STD_CRAWLOUT_RHS:
			case ANIM_STD_VAN_GET_OUT_REAR_LHS:
			case ANIM_STD_VAN_GET_OUT_REAR_RHS:
			case ANIM_BIKE_GETOFF_LHS:
			case ANIM_BIKE_GETOFF_RHS:
				seatPosMult = m_pVehicleAnim->GetProgress();
				break;
			case ANIM_STD_CAR_GET_IN_RHS:
			case ANIM_STD_CAR_GET_IN_LHS:
				if (veh && veh->IsCar() && veh->bIsBus) {
					multExtractedFromAnimBus = true;
					zBlend = Min(m_pVehicleAnim->GetProgress(), 0.5f) / 0.5f;
				}
				// fall through

			case ANIM_STD_QUICKJACK:
			case ANIM_STD_CAR_GET_IN_LO_LHS:
			case ANIM_STD_CAR_GET_IN_LO_RHS:
			case ANIM_STD_BOAT_DRIVE:
				seatPosMult = m_pVehicleAnim->GetTimeLeft() / m_pVehicleAnim->hierarchy->totalLength;
				break;
			case ANIM_STD_CAR_CLOSE_DOOR_LHS:
			case ANIM_STD_CAR_CLOSE_DOOR_LO_LHS:
			case ANIM_STD_CAR_CLOSE_DOOR_RHS:
			case ANIM_STD_CAR_CLOSE_DOOR_LO_RHS:
			case ANIM_STD_CAR_SHUFFLE_RHS:
			case ANIM_STD_CAR_SHUFFLE_LO_RHS:
				seatPosMult = 0.0f;
				break;
			case ANIM_STD_CAR_JUMP_IN_LO_LHS:
			{
				float animLength = m_pVehicleAnim->hierarchy->totalLength;
				seatPosMult = Max(0.0f, 0.5f * animLength - m_pVehicleAnim->currentTime) / animLength;
				break;
			}
			case ANIM_STD_CAR_CLOSE_LHS:
			case ANIM_STD_CAR_CLOSE_RHS:
			case ANIM_STD_COACH_OPEN_LHS:
			case ANIM_STD_COACH_OPEN_RHS:
			case ANIM_STD_COACH_GET_IN_LHS:
			case ANIM_STD_COACH_GET_IN_RHS:
			case ANIM_STD_COACH_GET_OUT_LHS:
				seatPosMult = 1.0f;
				break;
			default:
				if (veh->IsBike()) {
					seatPosMult = 0.0f;
				} else {
					if (bInVehicle)
						seatPosMult = 0.0f;
					else
						seatPosMult = 1.0f;
				}
				break;
		}
	} else {
		if (veh->IsBike()) {
			seatPosMult = 0.0f;
		} else {
			if (bInVehicle)
				seatPosMult = 0.0f;
			else
				seatPosMult = 1.0f;
		}
	}

	CVector neededPos;

	if (phase == LINE_UP_TO_CAR_2) {
		neededPos = GetPosition();
	} else {
		neededPos = GetPositionToOpenCarDoor(veh, m_vehDoor, seatPosMult);
	}

	autoZPos = neededPos;

	if (veh->bIsInWater) {
		if (veh->m_vehType == VEHICLE_TYPE_BOAT && veh->IsUpsideDown())
			autoZPos.z += 1.0f;
	} else {
		CPedPlacement::FindZCoorForPed(&autoZPos);
	}

	if (phase == LINE_UP_TO_CAR_END || phase == LINE_UP_TO_CAR_2) {
		neededPos.z = GetPosition().z;

		// Getting out
		if (!veh->bIsBus || (veh->bIsBus && vehIsUpsideDown)) {
			float nextZSpeed = m_vecMoveSpeed.z - GRAVITY * CTimer::GetTimeStep();

			// If we're not in ground at next step, apply animation
			if (neededPos.z + nextZSpeed >= autoZPos.z) {
				m_vecMoveSpeed.z = nextZSpeed;
				ApplyMoveSpeed();
				// Removing below line breaks the animation
				neededPos.z = GetPosition().z;
			} else {
				neededPos.z = autoZPos.z;
				m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
			}
		}
	}

	if (autoZPos.z > neededPos.z) {
		vehAnim = m_pVehicleAnim->animId;
		if (veh->IsBike() && (m_pVehicleAnim && vehAnim != ANIM_BIKE_KICK)) {
			float zBlend;
			if (vehAnim != ANIM_BIKE_GETOFF_LHS && vehAnim != ANIM_BIKE_GETOFF_RHS) {
				if (vehAnim != ANIM_BIKE_JUMPON_LHS && vehAnim != ANIM_BIKE_JUMPON_RHS) {
					zBlend = 0.0f;
				} else {
					float animLength = m_pVehicleAnim->hierarchy->totalLength;
					zBlend = Min(1.0f, 2.0f * m_pVehicleAnim->currentTime / animLength);
				}
			} else {
				zBlend = 1.0f - seatPosMult;
			}
			float curZ = veh->GetPosition().z + FEET_OFFSET;
			neededPos.z = ((curZ - autoZPos.z) - veh->GetHeightAboveRoad()) * zBlend + autoZPos.z;
		} else if (multExtractedFromAnim) {
			neededPos.z += (autoZPos.z - neededPos.z) * zBlend;
		} else {
			currentZ = GetPosition().z;
			if (m_pVehicleAnim && vehAnim != ANIM_STD_VAN_GET_IN_REAR_LHS && vehAnim != ANIM_STD_VAN_CLOSE_DOOR_REAR_LHS && vehAnim != ANIM_STD_VAN_CLOSE_DOOR_REAR_RHS && vehAnim != ANIM_STD_VAN_GET_IN_REAR_RHS) {
				neededPos.z = autoZPos.z;
				m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
			} else if (neededPos.z < currentZ && m_pVehicleAnim && vehAnim != ANIM_STD_VAN_CLOSE_DOOR_REAR_LHS && vehAnim != ANIM_STD_VAN_CLOSE_DOOR_REAR_RHS) {
				adjustedTimeStep = Max(m_pVehicleAnim->timeStep, 0.1f);

				// Smoothly change ped position
				neededPos.z = currentZ - (currentZ - neededPos.z) / (m_pVehicleAnim->GetTimeLeft() / adjustedTimeStep);
			}
		}
	} else {
		// We may need to raise up the ped
		if (phase == LINE_UP_TO_CAR_START) {
			currentZ = GetPosition().z;

			if (neededPos.z > currentZ) {
				if (multExtractedFromAnimBus) {
					neededPos.z = (neededPos.z - currentZ) * zBlend + currentZ;
				} else {
					if (m_pVehicleAnim &&
						(vehAnim == ANIM_STD_CAR_GET_IN_RHS || vehAnim == ANIM_STD_CAR_GET_IN_LO_RHS || vehAnim == ANIM_STD_CAR_GET_IN_LHS || vehAnim == ANIM_STD_CAR_GET_IN_LO_LHS
							|| vehAnim == ANIM_STD_QUICKJACK || vehAnim == ANIM_STD_VAN_GET_IN_REAR_LHS || vehAnim == ANIM_STD_VAN_GET_IN_REAR_RHS)) {
						adjustedTimeStep = Max(m_pVehicleAnim->timeStep, 0.1f);

						// Smoothly change ped position
						neededPos.z = (neededPos.z - currentZ) / (m_pVehicleAnim->GetTimeLeft() / adjustedTimeStep) + currentZ;
					} else if (EnteringCar() || m_nPedState == PED_DRIVING && veh->IsBike()) {
						neededPos.z = Max(currentZ, autoZPos.z);
					}
				}
			}
		}
	}

	if (CTimer::GetTimeInMilliseconds() < m_nPedStateTimer)
		stillGettingInOut = veh->m_vehType != VEHICLE_TYPE_BOAT || bOnBoat;

	if (!stillGettingInOut) {
		m_fRotationCur = m_fRotationDest;
	} else {
		float limitedDest = CGeneral::LimitRadianAngle(m_fRotationDest);
		float timeUntilStateChange = (m_nPedStateTimer - CTimer::GetTimeInMilliseconds())/600.0f;

		if (timeUntilStateChange <= 0.0f) {
			m_vecOffsetSeek.x = 0.0f;
			m_vecOffsetSeek.y = 0.0f;
		}
		m_vecOffsetSeek.z = 0.0f;

		neededPos -= timeUntilStateChange * m_vecOffsetSeek;

		if (PI + m_fRotationCur < limitedDest) {
			limitedDest -= 2 * PI;
		} else if (m_fRotationCur - PI > limitedDest) {
			limitedDest += 2 * PI;
		}
		m_fRotationCur -= (m_fRotationCur - limitedDest) * (1.0f - timeUntilStateChange);
	}

	if (seatPosMult > 0.2f || vehIsUpsideDown || veh->IsBike()) {
		SetPosition(neededPos);
		SetHeading(m_fRotationCur);
	} else {
		CMatrix vehDoorMat(veh->GetMatrix());
		vehDoorMat.GetPosition() += Multiply3x3(vehDoorMat, GetLocalPositionToOpenCarDoor(veh, m_vehDoor, 0.0f));

		if (m_vehDoor == CAR_WINDSCREEN || veh->bIsBus) {
			CMatrix correctionMat;
			if (veh->bIsBus && (m_vehDoor == CAR_DOOR_LF || m_vehDoor == CAR_DOOR_LR))
				correctionMat.SetRotateZ(-HALFPI);
			else if (veh->bIsBus && (m_vehDoor == CAR_DOOR_RF || m_vehDoor == CAR_DOOR_RR))
				correctionMat.SetRotateZ(HALFPI);
			else
				correctionMat.SetRotateZ(PI);

			vehDoorMat = vehDoorMat * correctionMat;
		}
		GetMatrix() = vehDoorMat;
	}

}

void
CPed::SetCarJack(CVehicle* car)
{
	uint8 doorFlag;
	eDoors door;
	CPed *pedInSeat = nil;

	if (car->IsBoat())
		return;

	if (car->IsBike()) {
		switch (m_vehDoor) {
			case CAR_DOOR_RF:
				doorFlag = CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_RF;
				door = DOOR_FRONT_RIGHT;
				pedInSeat = car->pDriver;
				break;
			case CAR_DOOR_RR:
				doorFlag = CAR_DOOR_FLAG_LR | CAR_DOOR_FLAG_RR;
				door = DOOR_REAR_RIGHT;
				pedInSeat = car->pPassengers[0];
				break;
			case CAR_DOOR_LF:
			case CAR_WINDSCREEN:
				doorFlag = CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_RF;
				door = DOOR_FRONT_LEFT;
				pedInSeat = car->pDriver;
				break;
			case CAR_DOOR_LR:
				doorFlag = CAR_DOOR_FLAG_LR | CAR_DOOR_FLAG_RR;
				door = DOOR_REAR_LEFT;
				pedInSeat = car->pPassengers[0];
				break;
			default:
				doorFlag = CAR_DOOR_FLAG_UNKNOWN;
				break;
		}
	} else {
		switch (m_vehDoor) {
			case CAR_DOOR_RF:
				doorFlag = CAR_DOOR_FLAG_RF;
				door = DOOR_FRONT_RIGHT;
				if (car->pPassengers[0]) {
					pedInSeat = car->pPassengers[0];
				}
				else if (m_nPedType == PEDTYPE_COP) {
					pedInSeat = car->pDriver;
				}
				break;
			case CAR_DOOR_RR:
				doorFlag = CAR_DOOR_FLAG_RR;
				door = DOOR_REAR_RIGHT;
				pedInSeat = car->pPassengers[2];
				break;
			case CAR_DOOR_LF:
				doorFlag = CAR_DOOR_FLAG_LF;
				door = DOOR_FRONT_LEFT;
				pedInSeat = car->pDriver;
				break;
			case CAR_DOOR_LR:
				doorFlag = CAR_DOOR_FLAG_LR;
				door = DOOR_REAR_LEFT;
				pedInSeat = car->pPassengers[1];
				break;
			default:
				doorFlag = CAR_DOOR_FLAG_UNKNOWN;
				break;
		}
	}

	if(car->bIsBus)
		pedInSeat = car->pDriver;

	if (m_fHealth > 0.0f && (IsPlayer() || m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT || m_objective == OBJECTIVE_KILL_CHAR_ANY_MEANS ||
					CharCreatedBy == MISSION_CHAR ||  (car->VehicleCreatedBy != MISSION_VEHICLE && car->GetModelIndex() != MI_DODO)))
		if (pedInSeat && !pedInSeat->IsPedDoingDriveByShooting() && pedInSeat->m_nPedState == PED_DRIVING)
			if (m_nPedState != PED_CARJACK && !m_pVehicleAnim)
				if ((car->IsDoorReady(door) || car->IsDoorFullyOpen(door)))
					if (!car->bIsBeingCarJacked && !(doorFlag & car->m_nGettingInFlags) && !(doorFlag & car->m_nGettingOutFlags))
						SetCarJack_AllClear(car, m_vehDoor, doorFlag);
}

void
CPed::SetCarJack_AllClear(CVehicle* car, uint32 doorNode, uint32 doorFlag)
{
	if (m_nPedState != PED_SEEK_CAR)
		SetStoredState();

	m_pSeekTarget = car;
	m_pSeekTarget->RegisterReference((CEntity**)&m_pSeekTarget);
	SetPedState(PED_CARJACK);
	car->bIsBeingCarJacked = true;
	m_pMyVehicle = (CVehicle*)m_pSeekTarget;
	m_pMyVehicle->RegisterReference((CEntity**)&m_pMyVehicle);
	((CVehicle*)m_pSeekTarget)->m_nNumGettingIn++;

	if (m_nPedType == PEDTYPE_COP)
		Say(SOUND_PED_ARREST_COP);
	else if (car->m_nDoorLock == CARLOCK_UNLOCKED)
		Say(SOUND_PED_CAR_JACKING, 1000);

	CVector carEnterPos;
	carEnterPos = GetPositionToOpenCarDoor(car, m_vehDoor);

	car->m_nGettingInFlags |= doorFlag;
	m_vecOffsetSeek = carEnterPos - GetPosition();
	m_nPedStateTimer = CTimer::GetTimeInMilliseconds() + 600;

	if(car->IsBike()){
		bUsesCollision = false;
		PedAnimAlignCB(nil, this);
	} else {
		float zDiff = Max(0.0f, carEnterPos.z - GetPosition().z);
		bUsesCollision = false;

		if (m_vehDoor == CAR_DOOR_LF || m_vehDoor == CAR_DOOR_LR)
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, zDiff > 4.4f ? ANIM_STD_CAR_ALIGNHI_DOOR_LHS : ANIM_STD_CAR_ALIGN_DOOR_LHS, 4.0f);
		else
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, zDiff > 4.4f ? ANIM_STD_CAR_ALIGNHI_DOOR_RHS : ANIM_STD_CAR_ALIGN_DOOR_RHS, 4.0f);

		m_pVehicleAnim->SetFinishCallback(PedAnimAlignCB, this);
	}
}

void
CPed::SetBeingDraggedFromCar(CVehicle *veh, uint32 vehEnterType, bool quickJack)
{
	if (m_nPedState == PED_DRAG_FROM_CAR)
		return;

	bUsesCollision = false;
	m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	m_nLastPedState = PED_IDLE;
	SetMoveState(PEDMOVE_STILL);
	m_pSeekTarget = veh;
	m_pSeekTarget->RegisterReference((CEntity **) &m_pSeekTarget);

	if (veh->IsBike()) {
		((CBike*)veh)->bIsBeingPickedUp = true;
		if (veh->pPassengers[0] != this && (vehEnterType != CAR_WINDSCREEN || veh->pPassengers[0]))
			m_vehDoor = CAR_DOOR_LF;
		else
			m_vehDoor = CAR_DOOR_LR;
	} else {
		m_vehDoor = vehEnterType;
	}

	if (m_vehDoor == CAR_DOOR_LF) {
		if (veh->pDriver && veh->pDriver->IsPlayer())
			veh->SetStatus(STATUS_PLAYER_DISABLED);
		else
			veh->SetStatus(STATUS_ABANDONED);
	}
	RemoveInCarAnims();
	SetMoveState(PEDMOVE_NONE);
	LineUpPedWithCar(veh->IsBike() ? LINE_UP_TO_CAR_FALL : LINE_UP_TO_CAR_START);
	m_pVehicleAnim = nil;
	SetPedState(PED_DRAG_FROM_CAR);
	bChangedSeat = false;
	bWillBeQuickJacked = quickJack;

	SetHeading(m_fRotationCur);

	Say(SOUND_PED_CAR_JACKED);
	SetRadioStation();

	if(veh->IsBike())
		veh->m_nGettingOutFlags |= GetBikeDoorFlagInclJumpInFromFront(m_vehDoor);
	else
		veh->m_nGettingOutFlags |= GetCarDoorFlag(m_vehDoor);
}

void
CPed::BeingDraggedFromCar(void)
{
	AnimationId enterAnim;
	bool dontRunAnim = false;

	if (!m_pVehicleAnim) {
		CAnimManager::BlendAnimation(GetClump(), m_animGroup, ANIM_STD_IDLE, 1000.0f);

		AssocGroupId assocGroup;
		if (m_pMyVehicle && m_pMyVehicle->IsBike()) {
			enterAnim = ANIM_BIKE_HIT;
			assocGroup = ((CBike*)m_pMyVehicle)->m_bikeAnimType;

		} else {
			if (m_vehDoor == CAR_DOOR_LF || m_vehDoor == CAR_DOOR_LR) {
				if (bWillBeQuickJacked && m_vehDoor == CAR_DOOR_LF) {
					enterAnim = ANIM_STD_QUICKJACKED;
				} else if (m_pMyVehicle->bLowVehicle) {
					enterAnim = ANIM_STD_JACKEDCAR_LO_LHS;
				} else {
					enterAnim = ANIM_STD_JACKEDCAR_LHS;
				}
			} else if (m_vehDoor == CAR_DOOR_RF || m_vehDoor == CAR_DOOR_RR) {
				if (m_pMyVehicle->bLowVehicle)
					enterAnim = ANIM_STD_JACKEDCAR_LO_RHS;
				else
					enterAnim = ANIM_STD_JACKEDCAR_RHS;
			} else
				dontRunAnim = true;

			assocGroup = ASSOCGRP_STD;
		}

		if (!dontRunAnim)
			m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), assocGroup, enterAnim);

		m_pVehicleAnim->SetFinishCallback(PedSetDraggedOutCarCB, this);

		if (m_pMyVehicle && m_pMyVehicle->IsBike()) {
			LineUpPedWithCar(LINE_UP_TO_CAR_FALL);
		} else {
			LineUpPedWithCar(LINE_UP_TO_CAR_START);
		}
		return;

	} else if (m_pVehicleAnim->animId == ANIM_BIKE_HIT) {
		LineUpPedWithCar(LINE_UP_TO_CAR_FALL);

	} else if (m_pVehicleAnim->currentTime <= 1.4f) {
		m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
		LineUpPedWithCar(LINE_UP_TO_CAR_START);

	} else {
		LineUpPedWithCar(LINE_UP_TO_CAR_2);
	}

	static float mult = 5.f;
	if (m_objective == OBJECTIVE_LEAVE_CAR_AND_DIE) {
		if (m_pMyVehicle) {
			m_pMyVehicle->ProcessOpenDoor(m_vehDoor, ANIM_STD_NUM, m_pVehicleAnim->currentTime * mult);
		}
	}
}

void
CPed::SetEnterCar(CVehicle *car, uint32 unused)
{
	if (CCranes::IsThisCarBeingCarriedByAnyCrane(car)) {
		RestorePreviousState();
		RestorePreviousObjective();
	} else {
		uint8 doorFlag;
		eDoors door;
		if (car->IsBike()) {
			switch (m_vehDoor) {
				case CAR_DOOR_RF:
					doorFlag = CAR_DOOR_FLAG_RF | CAR_DOOR_FLAG_LF;
					door = DOOR_FRONT_RIGHT;
					break;
				case CAR_DOOR_RR:
					doorFlag = CAR_DOOR_FLAG_RR | CAR_DOOR_FLAG_LR;
					door = DOOR_REAR_RIGHT;
					break;
				case CAR_WING_LF:
				case CAR_WING_LR:
				case CAR_BONNET:
				case CAR_BOOT:
					doorFlag = CAR_DOOR_FLAG_UNKNOWN;
					break;
				case CAR_DOOR_LF:
				case CAR_WINDSCREEN:
					doorFlag = CAR_DOOR_FLAG_RF | CAR_DOOR_FLAG_LF;
					door = DOOR_FRONT_LEFT;
					break;
				case CAR_DOOR_LR:
					doorFlag = CAR_DOOR_FLAG_RR | CAR_DOOR_FLAG_LR;
					door = DOOR_REAR_LEFT;
					break;
			}
		} else {
			switch (m_vehDoor) {
				case CAR_DOOR_RF:
					doorFlag = CAR_DOOR_FLAG_RF;
					door = DOOR_FRONT_RIGHT;
					break;
				case CAR_DOOR_RR:
					doorFlag = CAR_DOOR_FLAG_RR;
					door = DOOR_REAR_RIGHT;
					break;
				case CAR_DOOR_LF:
					if(car->m_nNumMaxPassengers != 0)
						doorFlag = CAR_DOOR_FLAG_LF;
					else
						doorFlag = CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_LR;

					door = DOOR_FRONT_LEFT;
					break;
				case CAR_DOOR_LR:
					if (car->m_nNumMaxPassengers != 0)
						doorFlag = CAR_DOOR_FLAG_LR;
					else
						doorFlag = CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_LR;

					door = DOOR_REAR_LEFT;
					break;
				default:
					doorFlag = CAR_DOOR_FLAG_UNKNOWN;
					break;
			}
		}
		if (!IsPedInControl() || m_fHealth <= 0.0f
			|| doorFlag & car->m_nGettingInFlags || doorFlag & car->m_nGettingOutFlags
			|| car->bIsBeingCarJacked || m_pVehicleAnim
			|| doorFlag && !car->IsDoorReady(door) && !car->IsDoorFullyOpen(door))
			SetMoveState(PEDMOVE_STILL);
		else
			SetEnterCar_AllClear(car, m_vehDoor, doorFlag);
	}
}

void
CPed::SetEnterCar_AllClear(CVehicle *car, uint32 doorNode, uint32 doorFlag)
{
	float zDiff = 0.0f;
	car->m_nGettingInFlags |= doorFlag;
	bVehEnterDoorIsBlocked = false;
	if (m_nPedState != PED_SEEK_CAR && m_nPedState != PED_SEEK_IN_BOAT)
		SetStoredState();

	m_pSeekTarget = car;
	m_pSeekTarget->RegisterReference((CEntity **) &m_pSeekTarget);
	m_vehDoor = doorNode;
	SetPedState(PED_ENTER_CAR);
	if (m_vehDoor == CAR_DOOR_RF && m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER && !car->IsBike()) {
		car->bIsBeingCarJacked = true;
	}

	m_pMyVehicle = (CVehicle*)m_pSeekTarget;
	m_pMyVehicle->RegisterReference((CEntity**) &m_pMyVehicle);
	((CVehicle*)m_pSeekTarget)->m_nNumGettingIn++;
	bUsesCollision = false;
	CVector doorOpenPos = GetPositionToOpenCarDoor(car, m_vehDoor);

	// Because buses have stairs
	if (!m_pMyVehicle->bIsBus)
		zDiff = Max(0.0f, doorOpenPos.z - GetPosition().z);

	m_vecOffsetSeek = doorOpenPos - GetPosition();
	m_nPedStateTimer = CTimer::GetTimeInMilliseconds() + 600;

	if (car->IsBoat()) {
		if (car->pHandling->Flags & HANDLING_SIT_IN_BOAT)
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SIT, 100.0f);
		else
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_BOAT_DRIVE, 100.0f);

		PedSetInCarCB(nil, this);
		bVehExitWillBeInstant = true;

	} else if (car->IsBike()) {
		PedAnimAlignCB(0, this);
		car->AutoPilot.m_nCruiseSpeed = 0;

	} else {
		if (m_vehDoor == CAR_DOOR_LF || m_vehDoor == CAR_DOOR_LR)
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, zDiff > 4.4f ? ANIM_STD_CAR_ALIGNHI_DOOR_RHS : ANIM_STD_CAR_ALIGN_DOOR_RHS, 4.0f);
		else
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, zDiff > 4.4f ? ANIM_STD_CAR_ALIGNHI_DOOR_LHS : ANIM_STD_CAR_ALIGN_DOOR_LHS, 4.0f);
		m_pVehicleAnim->SetFinishCallback(PedAnimAlignCB, this);
	}
}

void
CPed::EnterCar(void)
{
	if (IsNotInWreckedVehicle() && m_fHealth > 0.0f) {
		CVehicle *veh = m_pMyVehicle;

		// Not used.
		// CVector posForDoor = GetPositionToOpenCarDoor(veh, m_vehDoor);

		if (veh->CanPedOpenLocks(this)) {
			if (m_vehDoor && m_pVehicleAnim) {
				veh->ProcessOpenDoor(m_vehDoor, m_pVehicleAnim->animId, m_pVehicleAnim->currentTime);
			}
		}
		bIsInTheAir = false;
		LineUpPedWithCar(LINE_UP_TO_CAR_START);
		if (veh->IsBike()) {
			CBike *bike = (CBike*)veh;
			if (bike->GetStatus() == STATUS_ABANDONED && !bike->bIsBeingPickedUp && m_pVehicleAnim) {
				int anim = m_pVehicleAnim->animId;

				// One is pickup and other one is pullup, not same :p
				if ((anim == ANIM_STD_BIKE_PICKUP_LHS || anim == ANIM_STD_BIKE_PICKUP_RHS) && m_pVehicleAnim->currentTime > 0.4667f)
					bike->bIsBeingPickedUp = true;
				else if ((anim == ANIM_STD_BIKE_PULLUP_LHS || anim == ANIM_STD_BIKE_PULLUP_RHS) && m_pVehicleAnim->currentTime > 0.4667f)
					bike->bIsBeingPickedUp = true;
			} else if (m_nPedState == PED_CARJACK && m_pVehicleAnim) {
				if (m_pVehicleAnim->currentTime > 0.4f && m_pVehicleAnim->currentTime - m_pVehicleAnim->timeStep <= 0.4f) {
					int anim = m_pVehicleAnim->animId;
					if (anim == ANIM_BIKE_KICK) {
						DMAudio.PlayOneShot(m_audioEntityId, SOUND_187, 3.0f);
					} else if (anim == ANIM_STD_BIKE_ELBOW_LHS || anim == ANIM_STD_BIKE_ELBOW_RHS) {
						DMAudio.PlayOneShot(m_audioEntityId, SOUND_186, 3.0f);
					}
				}
			}
		}
	} else {
		QuitEnteringCar();
		SetDie();
	}
}

void
CPed::QuitEnteringCar(void)
{
	CVehicle *veh = m_pMyVehicle;
	if (m_pVehicleAnim)
		m_pVehicleAnim->blendDelta = -1000.0f;
	
	RestartNonPartialAnims();

	if (!RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_IDLE))
		CAnimManager::BlendAnimation(GetClump(), m_animGroup, ANIM_STD_IDLE, 100.0f);
	
	if (veh) {
		if (m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || m_nPedState == PED_CARJACK)
			veh->bIsBeingCarJacked = false;

		if (veh->m_nNumGettingIn != 0)
			veh->m_nNumGettingIn--;

		if (m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER)
			RestorePreviousObjective();

		if (veh->IsBike()) {
			veh->m_nGettingInFlags &= ~GetBikeDoorFlag(m_vehDoor);
			((CBike*)veh)->bIsBeingPickedUp = false;
		} else
			veh->m_nGettingInFlags &= ~GetEnterCarDoorFlag(m_vehDoor, veh->m_nNumMaxPassengers);
	}

	bUsesCollision = true;

	if (DyingOrDead()) {
		if (m_pVehicleAnim) {
			m_pVehicleAnim->blendDelta = -4.0f;
			m_pVehicleAnim->flags |= ASSOC_DELETEFADEDOUT;
			m_pVehicleAnim->flags &= ~ASSOC_RUNNING;
		}
	} else
		SetIdle();

	m_pVehicleAnim = nil;
	
	if (veh) {
		if (veh->AutoPilot.m_nCruiseSpeed == 0 && veh->VehicleCreatedBy == RANDOM_VEHICLE)
			veh->AutoPilot.m_nCruiseSpeed = 17;
	}
}

void
CPed::SetExitBoat(CVehicle *boat)
{
	SetPedState(PED_IDLE);
	CVector newPos = GetPosition();
	RemoveInCarAnims();
	CColModel* boatCol = boat->GetColModel();
	if (boat->IsUpsideDown()) {
		newPos = CVector(0.0f, 0.0f, boatCol->boundingBox.min.z);
		newPos = boat->GetMatrix() * newPos;
		newPos.z += 1.0f;
		m_vehDoor = CAR_DOOR_RF;
		PedSetOutCarCB(nil, this);
		bIsStanding = true;
		m_pCurSurface = boat;
		m_pCurSurface->RegisterReference((CEntity**)&m_pCurSurface);
		m_pCurrentPhysSurface = boat;
	} else {
		if (boat->m_modelIndex == MI_SKIMMER) {
			if (!boat->bIsInWater) {
				m_vehDoor = CAR_DOOR_RF;
				PedSetOutCarCB(nil, this);
				bIsStanding = true;
				SetMoveState(PEDMOVE_STILL);
				bTryingToReachDryLand = true;
				float upMult = 1.04f + boatCol->boundingBox.min.z;
				float rightMult = 0.6f * boatCol->boundingBox.max.x;
				newPos = upMult * boat->GetUp() + rightMult * boat->GetRight() + boat->GetPosition();
				SetPosition(newPos);
				if (m_pMyVehicle) {
					PositionPedOutOfCollision();
				} else {
					m_pMyVehicle = boat;
					PositionPedOutOfCollision();
					m_pMyVehicle = nil;
				}
				return;
			}

			newPos.z += 2.0f;
		}
		m_vehDoor = CAR_DOOR_RF;
		PedSetOutCarCB(nil, this);
		bIsStanding = true;
		m_pCurSurface = boat;
		m_pCurSurface->RegisterReference((CEntity**)&m_pCurSurface);
		m_pCurrentPhysSurface = boat;
		CColPoint foundCol;
		CEntity *foundEnt = nil;
		if (CWorld::ProcessVerticalLine(newPos, newPos.z - 1.4f, foundCol, foundEnt, false, true, false, false, false, false, nil))
			newPos.z = FEET_OFFSET + foundCol.point.z;
	}
	SetPosition(newPos);
	SetMoveState(PEDMOVE_STILL);
	m_vecMoveSpeed = boat->m_vecMoveSpeed;
}

// wantedDoorNode = 0 means that func. will determine it
void
CPed::SetExitCar(CVehicle *veh, uint32 wantedDoorNode)
{
	uint32 optedDoorNode = wantedDoorNode;
	bool teleportNeeded = false;
	bool isLow = !!veh->bLowVehicle;

	bool canJumpOut = false;
	if (!veh->CanPedExitCar(false) && !bBusJacked) {
		if (IsPlayer()) {
			canJumpOut = veh->IsBike() ? veh->CanPedJumpOffBike() : veh->CanPedJumpOutCar();
		}
		if (!canJumpOut) {
			if (veh->pDriver) {
				if (veh->pDriver->IsPlayer()) {
					if (veh->pDriver != this) {
						m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 5000;
						bHeldHostageInCar = true;
					}
				} else {
					veh->AutoPilot.m_nCruiseSpeed = 0;
					veh->AutoPilot.m_nCarMission = MISSION_NONE;
				}
			}
			return;
		}
	}

	if (m_nPedState == PED_EXIT_CAR || m_nPedState == PED_DRAG_FROM_CAR)
		return;

	m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	m_vecTurnSpeed = CVector(0.0f, 0.0f, 0.0f);
	if (wantedDoorNode == 0) {
		optedDoorNode = CAR_DOOR_LF;
		if (veh->IsBike()) {
			if (canJumpOut) {
				optedDoorNode = veh->pPassengers[0] == this ? CAR_BUMP_REAR : CAR_BOOT;
			} else if (veh->pPassengers[0] == this) {
				optedDoorNode = CAR_DOOR_LR;
			} else {
				optedDoorNode = CAR_DOOR_LF;
			}
		} else if (veh->bIsBus) {
			optedDoorNode = CAR_DOOR_LF;
		} else if (veh->pDriver == this) {
			optedDoorNode = CAR_DOOR_LF;
		} else if (veh->pPassengers[0] == this) {
			optedDoorNode = CAR_DOOR_RF;
		} else if (veh->pPassengers[1] == this) {
			optedDoorNode = CAR_DOOR_LR;
		} else if (veh->pPassengers[2] == this) {
			optedDoorNode = CAR_DOOR_RR;
		} else {
			for (int i = 3; i < veh->m_nNumMaxPassengers; ++i) {
				if (veh->pPassengers[i] == this) {
					if (i & 1)
						optedDoorNode = CAR_DOOR_RR;
					else
						optedDoorNode = CAR_DOOR_LR;

					break;
				}
			}
		}
	}
	bool someoneExitsFromOurExitDoor = false;
	bool someoneEntersFromOurExitDoor = false;
	if (veh->IsBike()) {
		switch (optedDoorNode) {
			case CAR_BUMP_REAR:
			case CAR_DOOR_RR:
			case CAR_DOOR_LR:
				if (veh->m_nGettingInFlags & (CAR_DOOR_FLAG_LR | CAR_DOOR_FLAG_RR))
					someoneEntersFromOurExitDoor = true;
				break;
			case CAR_DOOR_RF:
			case CAR_DOOR_LF:
			case CAR_BOOT:
				if (veh->m_nGettingInFlags & (CAR_DOOR_FLAG_LF | CAR_DOOR_FLAG_RF))
					someoneEntersFromOurExitDoor = true;
				break;
			default:
				break;
		}
	} else {
		switch (optedDoorNode) {
			case CAR_DOOR_RF:
				if (veh->m_nGettingInFlags & CAR_DOOR_FLAG_RF)
					someoneEntersFromOurExitDoor = true;
				if (veh->m_nGettingOutFlags & CAR_DOOR_FLAG_RF)
					someoneExitsFromOurExitDoor = true;
				break;
			case CAR_DOOR_RR:
				if (veh->m_nGettingInFlags & CAR_DOOR_FLAG_RR)
					someoneEntersFromOurExitDoor = true;
				if (veh->m_nGettingOutFlags & CAR_DOOR_FLAG_RR)
					someoneExitsFromOurExitDoor = true;
				break;
			case CAR_DOOR_LF:
				if (veh->m_nGettingInFlags & CAR_DOOR_FLAG_LF)
					someoneEntersFromOurExitDoor = true;
				if (veh->m_nGettingOutFlags & CAR_DOOR_FLAG_LF)
					someoneExitsFromOurExitDoor = true;
				break;
			case CAR_DOOR_LR:
				if (veh->m_nGettingInFlags & CAR_DOOR_FLAG_LR)
					someoneEntersFromOurExitDoor = true;
				if (veh->m_nGettingOutFlags & CAR_DOOR_FLAG_LR)
					someoneExitsFromOurExitDoor = true;
				break;
			default:
				break;
		}
	}
	if (someoneEntersFromOurExitDoor && m_objective == OBJECTIVE_LEAVE_CAR) {
		RestorePreviousObjective();
		return;
	}
	if (!someoneExitsFromOurExitDoor || m_nPedType == PEDTYPE_COP && veh->bIsBus) {
#if defined GTAVC_JP_PATCH || defined FIX_BUGS
		if (veh->pDriver == this && !IsPlayer() && veh == CGameLogic::pShortCutTaxi) {
			m_objective = OBJECTIVE_NONE;
			return;
		}
#endif
		bool thereIsRoom;
		if (canJumpOut) {
			thereIsRoom = 1;
		} else {
			// Again, unused...
			// CVector exitPos = GetPositionToOpenCarDoor(veh, optedDoorNode);
			thereIsRoom = veh->IsRoomForPedToLeaveCar(optedDoorNode, nil);
		}

		if (!thereIsRoom) {
			bool trySideSeat = false;
			CPed *pedOnSideSeat;
			int firstOptedDoor = optedDoorNode;
			if (veh->IsBike()) {
				switch (optedDoorNode) {
					case CAR_DOOR_RF:
						optedDoorNode = CAR_DOOR_LF;
						break;
					case CAR_DOOR_RR:
						optedDoorNode = CAR_DOOR_LR;
						break;
					case CAR_DOOR_LF:
						optedDoorNode = CAR_DOOR_RF;
						break;
					case CAR_DOOR_LR:
						optedDoorNode = CAR_DOOR_RR;
						break;
					default:
						break;
				}
			} else {
				switch (optedDoorNode) {
					case CAR_DOOR_RF:
						if (veh->pDriver || veh->m_nGettingInFlags & CAR_DOOR_FLAG_LF) {
							pedOnSideSeat = veh->pDriver;
							trySideSeat = true;
						} else
							optedDoorNode = CAR_DOOR_LF;

						break;
					case CAR_DOOR_RR:
						if (veh->pPassengers[1] || veh->m_nGettingInFlags & CAR_DOOR_FLAG_LR) {
							pedOnSideSeat = veh->pPassengers[1];
							trySideSeat = true;
						} else
							optedDoorNode = CAR_DOOR_LR;

						break;
					case CAR_DOOR_LF:
						if (veh->pPassengers[0] || veh->m_nGettingInFlags & CAR_DOOR_FLAG_RF) {
							pedOnSideSeat = veh->pPassengers[0];
							trySideSeat = true;
						} else
							optedDoorNode = CAR_DOOR_RF;

						break;
					case CAR_DOOR_LR:
						if (veh->pPassengers[2] || veh->m_nGettingInFlags & CAR_DOOR_FLAG_RR) {
							pedOnSideSeat = (CPed*)veh->pPassengers[2];
							trySideSeat = true;
						} else
							optedDoorNode = CAR_DOOR_RR;

						break;
					default:
						break;
				}
			}
			if (trySideSeat) {
				if (!pedOnSideSeat || !IsPlayer() && CharCreatedBy != MISSION_CHAR)
					return;

				switch (optedDoorNode) {
					case CAR_DOOR_RF:
						optedDoorNode = CAR_DOOR_LF;
						break;
					case CAR_DOOR_RR:
						optedDoorNode = CAR_DOOR_LR;
						break;
					case CAR_DOOR_LF:
						optedDoorNode = CAR_DOOR_RF;
						break;
					case CAR_DOOR_LR:
						optedDoorNode = CAR_DOOR_RR;
						break;
					default:
						break;
				}
			}
			// ...
			// CVector exitPos = GetPositionToOpenCarDoor(veh, optedDoorNode);
			if (!veh->IsRoomForPedToLeaveCar(optedDoorNode, nil)) {
				if (!IsPlayer() && CharCreatedBy != MISSION_CHAR)
					return;

				// needed for PositionPedOutOfCollision()
				optedDoorNode = firstOptedDoor;
				m_vehDoor = firstOptedDoor;
				PositionPedOutOfCollision();
				teleportNeeded = true;
			}
		}

		if (!teleportNeeded && veh->IsOnItsSide()) {
			m_vehDoor = optedDoorNode;
			PositionPedOutOfCollision();
			teleportNeeded = true;
		}

		if (m_nPedState == PED_FLEE_POS) {
			m_nLastPedState = PED_FLEE_POS;
			m_nPrevMoveState = PEDMOVE_RUN;
			SetMoveState(PEDMOVE_SPRINT);
		} else {
			m_nLastPedState = PED_IDLE;
			m_nPrevMoveState = PEDMOVE_STILL;
			SetMoveState(PEDMOVE_STILL);
		}

		bUsesCollision = false;
		m_pSeekTarget = veh;
		m_pSeekTarget->RegisterReference((CEntity**) &m_pSeekTarget);
		m_vehDoor = optedDoorNode;
		SetPedState(PED_EXIT_CAR);
		if (m_pVehicleAnim && m_pVehicleAnim->flags & ASSOC_PARTIAL)
			m_pVehicleAnim->blendDelta = -1000.0f;
		RemoveInCarAnims();
		SetMoveState(PEDMOVE_NONE);
		CAnimManager::BlendAnimation(GetClump(), m_animGroup, ANIM_STD_IDLE, 100.0f);
		veh->AutoPilot.m_nCruiseSpeed = 0;

		if (teleportNeeded) {
			PedSetOutCarCB(nil, this);
		} else {
			if (veh->GetUp().z <= -0.8f && !veh->IsBike()) {
				if (m_vehDoor == CAR_DOOR_RF || m_vehDoor == CAR_DOOR_RR) {
					m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CRAWLOUT_RHS);
				} else if (m_vehDoor == CAR_DOOR_LF || m_vehDoor == CAR_DOOR_LR) {
					m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CRAWLOUT_LHS);
				}
				m_pVehicleAnim->SetFinishCallback(PedSetOutCarCB, this);

			} else if (veh->IsBike()) {
				CBike* bike = (CBike*)veh;
				switch (m_vehDoor) {
					case CAR_BUMP_REAR:
					case CAR_BOOT:
						m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), bike->m_bikeAnimType, ANIM_BIKE_GETOFF_BACK);
						break;
					case CAR_DOOR_RF:
					case CAR_DOOR_RR:
						m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), bike->m_bikeAnimType, ANIM_BIKE_GETOFF_RHS);
						break;
					case CAR_DOOR_LF:
					case CAR_DOOR_LR:
						m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), bike->m_bikeAnimType, ANIM_BIKE_GETOFF_LHS);
						break;
					default:
						break;
				}
				int8 exitFlags = 0;

				// Bike door flags incl. passenger jump off
				switch (m_vehDoor) {
					case CAR_BUMP_REAR:
					case CAR_DOOR_RR:
					case CAR_DOOR_LR:
						exitFlags = CAR_DOOR_FLAG_RR | CAR_DOOR_FLAG_LR;
						break;
					case CAR_DOOR_RF:
					case CAR_DOOR_LF:
					case CAR_BOOT:
						exitFlags = CAR_DOOR_FLAG_RF | CAR_DOOR_FLAG_LF;
						break;
				}

				// Passenger get off
				if (m_vehDoor == CAR_BUMP_REAR || m_vehDoor == CAR_BOOT) {
					m_pVehicleAnim->SetFinishCallback(RestoreHeadingRateCB, this);
					m_headingRate = 0.0f;

				} else {
					veh->m_nGettingOutFlags |= exitFlags;
					m_pVehicleAnim->SetFinishCallback(PedAnimStepOutCarCB, this);
				}

			} else {
				switch (m_vehDoor) {
					case CAR_DOOR_RF:
						if (canJumpOut) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_ROLLOUT_RHS);
						} else if (veh->bIsBus) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_GET_OUT_LHS);
						} else {
							if (isLow)
								m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_LO_RHS);
							else
								m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_RHS);
						}
						break;
					case CAR_DOOR_RR:
						if (canJumpOut) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_ROLLOUT_RHS);
						} else if (veh->bIsVan) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_GET_OUT_REAR_RHS);
						} else if (isLow) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_LO_RHS);
						} else {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_RHS);
						}
						break;
					case CAR_DOOR_LF:
						if (canJumpOut) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_ROLLOUT_LHS);
						} else if (veh->bIsBus) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_COACH, ANIM_STD_COACH_GET_OUT_LHS);
						} else {
							if (isLow)
								m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_LO_LHS);
							else
								m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_LHS);
						}
						break;
					case CAR_DOOR_LR:
						if (canJumpOut) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_ROLLOUT_LHS);
						} else if (veh->bIsVan) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_VAN, ANIM_STD_VAN_GET_OUT_REAR_LHS);
						} else if (isLow) {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_LO_LHS);
						} else {
							m_pVehicleAnim = CAnimManager::AddAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_GETOUT_LHS);
						}
						break;
					default:
						break;
				}
				if (!bBusJacked && !canJumpOut) {
					veh->m_nGettingOutFlags |= GetCarDoorFlag(m_vehDoor);
				}
				m_pVehicleAnim->SetFinishCallback(canJumpOut ? RestoreHeadingRateCB : PedAnimStepOutCarCB, this);
			}
		}
		bChangedSeat = false;
		if (veh->bIsBus)
			bRenderPedInCar = true;

		SetRadioStation();
		if (veh->pDriver == this) {
			if (IsPlayer())
				veh->SetStatus(STATUS_PLAYER_DISABLED);
			else
				veh->SetStatus(STATUS_ABANDONED);
		}
	}
}

void
CPed::ExitCar(void)
{
	if (!m_pVehicleAnim) {
		if (InVehicle()) {
			if (m_pMyVehicle->IsBike()) {
				if (m_vehDoor == CAR_BOOT || m_vehDoor == CAR_BUMP_REAR) {
					((CBike*)m_pMyVehicle)->KnockOffRider(WEAPONTYPE_UNARMED, 0, this, false);
				}
			} else if (m_pMyVehicle->IsCar()) {
				if (RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_ROLLOUT_LHS)) {
					((CAutomobile*)m_pMyVehicle)->KnockPedOutCar(WEAPONTYPE_UNIDENTIFIED, CAR_DOOR_LF, this);
				} else if (RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_ROLLOUT_RHS)) {
					((CAutomobile*)m_pMyVehicle)->KnockPedOutCar(WEAPONTYPE_UNIDENTIFIED, CAR_DOOR_RF, this);
				}
			}
		}
		return;
	}

	AnimationId exitAnim = (AnimationId) m_pVehicleAnim->animId;
	float animTime = m_pVehicleAnim->currentTime;

	if (exitAnim == ANIM_BIKE_GETOFF_BACK) {
		if (animTime > 0.35f && m_pMyVehicle && m_pMyVehicle->IsBike())
			((CBike*)m_pMyVehicle)->KnockOffRider(WEAPONTYPE_UNARMED, 0, this, false);
		else
			LineUpPedWithCar(LINE_UP_TO_CAR_FALL);

	} else if (exitAnim == ANIM_STD_ROLLOUT_LHS || exitAnim == ANIM_STD_ROLLOUT_RHS) {
		if (animTime > 0.07f && m_pMyVehicle && m_pMyVehicle->IsCar()) {
			if (exitAnim == ANIM_STD_ROLLOUT_LHS) {
				((CAutomobile*)m_pMyVehicle)->KnockPedOutCar(WEAPONTYPE_UNIDENTIFIED, CAR_DOOR_LF, this);
			} else {
				((CAutomobile*)m_pMyVehicle)->KnockPedOutCar(WEAPONTYPE_UNIDENTIFIED, CAR_DOOR_RF, this);
			}
		} else {
			LineUpPedWithCar(LINE_UP_TO_CAR_FALL);
		}
	} else {
		m_pMyVehicle->ProcessOpenDoor(m_vehDoor, exitAnim, animTime);

		if (m_pSeekTarget) {
			// Car is upside down
			if (m_pMyVehicle->GetUp().z > -0.8f) {
				if (exitAnim == ANIM_STD_CAR_CLOSE_RHS || exitAnim == ANIM_STD_CAR_CLOSE_LHS || animTime > 0.3f)
					LineUpPedWithCar(LINE_UP_TO_CAR_END);
				else
					LineUpPedWithCar((m_pMyVehicle->GetModelIndex() == MI_DODO ? LINE_UP_TO_CAR_END : LINE_UP_TO_CAR_START));
			}
			else {
				LineUpPedWithCar(LINE_UP_TO_CAR_END);
			}
		}

		// If there is someone in front of the door, make him fall while we exit.
		if (m_nPedState == PED_EXIT_CAR) {
			CPed* foundPed = nil;
			for (int i = 0; i < m_numNearPeds; i++) {
				if ((m_nearPeds[i]->GetPosition() - GetPosition()).MagnitudeSqr2D() < SQR(0.2f)) {
					foundPed = m_nearPeds[i];
					break;
				}
			}
			if(foundPed && (!foundPed->IsPlayer() || m_nPedType == PEDTYPE_COP || m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT || m_objective == OBJECTIVE_KILL_CHAR_ANY_MEANS))
				if (animTime > 0.4f && foundPed->IsPedInControl())
					foundPed->SetFall(1000, ANIM_STD_HIGHIMPACT_FRONT, 1);
		}
	}
}

CVector
CPed::GetPositionToOpenCarDoor(CVehicle *veh, uint32 component)
{
	CVector doorPos;
	CVector vehDoorOffset;
	CVehicleModelInfo* vehModel = veh->GetModelInfo();

	if (veh->IsBike()) {
		CBike* bike = (CBike*)veh;

		if (component == CAR_WINDSCREEN) {
			doorPos = vehModel->GetFrontSeatPosn();
			return bike->GetMatrix() * (doorPos +
				CVector(-vecPedBikeKickAnimOffset.x, vecPedBikeKickAnimOffset.y, -vecPedBikeKickAnimOffset.z));
		} else {
			switch (bike->m_bikeAnimType) {
			case ASSOCGRP_BIKE_VESPA:
				vehDoorOffset = vecPedVespaBikeJumpRhsAnimOffset;
				break;
			case ASSOCGRP_BIKE_HARLEY:
				vehDoorOffset = vecPedHarleyBikeJumpRhsAnimOffset;
				break;
			case ASSOCGRP_BIKE_DIRT:
				vehDoorOffset = vecPedDirtBikeJumpRhsAnimOffset;
				break;
			default:
				vehDoorOffset = vecPedStdBikeJumpRhsAnimOffset;
				break;
			}
		}

		doorPos = vehModel->GetFrontSeatPosn();
		if (component == CAR_DOOR_LR || component == CAR_DOOR_RR) {
			doorPos = vehModel->m_positions[CAR_POS_BACKSEAT];
		}

		if (component == CAR_DOOR_LR || component == CAR_DOOR_LF) {
			vehDoorOffset.x *= -1.f;
		}

		CVector correctedPos;
		bike->GetCorrectedWorldDoorPosition(correctedPos, vehDoorOffset, doorPos);
		return correctedPos;
	} else {
		float seatOffset;
		if (veh->bIsVan && (component == CAR_DOOR_LR || component == CAR_DOOR_RR)) {
			seatOffset = 0.0f;
			vehDoorOffset = vecPedVanRearDoorAnimOffset;
		} else {
			seatOffset = veh->pHandling->fSeatOffsetDistance;
			if (veh->bLowVehicle) {
				vehDoorOffset = vecPedCarDoorLoAnimOffset;
			} else {
				vehDoorOffset = vecPedCarDoorAnimOffset;
			}
		}

		switch (component) {
		case CAR_DOOR_RF:
			doorPos = vehModel->GetFrontSeatPosn();
			doorPos.x += seatOffset;
			vehDoorOffset.x = -vehDoorOffset.x;
			break;

		case CAR_DOOR_RR:
			doorPos = vehModel->m_positions[CAR_POS_BACKSEAT];
			doorPos.x += seatOffset;
			vehDoorOffset.x = -vehDoorOffset.x;
			break;

		case CAR_DOOR_LF:
			doorPos = vehModel->GetFrontSeatPosn();
			doorPos.x += seatOffset;
			doorPos.x = -doorPos.x;
			break;

		case CAR_DOOR_LR:
			doorPos = vehModel->m_positions[CAR_POS_BACKSEAT];
			doorPos.x += seatOffset;
			doorPos.x = -doorPos.x;
			break;

		default:
			doorPos = vehModel->GetFrontSeatPosn();
			vehDoorOffset = CVector(0.0f, 0.0f, 0.0f);
			break;
		}

		CVector diffVec = doorPos - vehDoorOffset;
		return Multiply3x3(veh->GetMatrix(), diffVec) + veh->GetPosition();

		//unused
		//doorPos = Multiply3x3(veh->GetMatrix(), doorPos) + veh->GetMatrix();
	}
}

void
CPed::GetNearestDoor(CVehicle *veh, CVector &posToOpen)
{
	CVector *enterOffset = nil;
	if (veh->IsBike()) {
		if (m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER) {

			// If bike didn't fall to ground
			if (Abs(veh->GetRight().z) < 0.1f) {
				float angleDiff = (GetPosition() - veh->GetPosition()).Heading() - veh->GetForward().Heading();

				if (angleDiff > PI)
					angleDiff -= TWOPI;
				else if (angleDiff < -PI)
					angleDiff += TWOPI;

				if (Abs(angleDiff) < DEGTORAD(30.f)
					&& (IsPlayer() && ((CPlayerPed*)this)->m_fMoveSpeed > 1.5f && !m_vehDoor ||
						!IsPlayer() && m_nPedType != PEDTYPE_COP && m_nMoveState == PEDMOVE_RUN
						&& m_pedStats->m_temper > 65
						&& !m_vehDoor || m_vehDoor == CAR_WINDSCREEN)) {
					m_vehDoor = CAR_WINDSCREEN;
					posToOpen = GetPositionToOpenCarDoor(veh, CAR_WINDSCREEN);
					return;
				}
			}
		}
	} else if (m_vehDoor == CAR_DOOR_LF && veh->pDriver && !veh->bLowVehicle && !veh->bIsBus) {
		enterOffset = &vecPedQuickDraggedOutCarAnimOffset;
	}

	CVector lfPos = GetPositionToOpenCarDoor(veh, CAR_DOOR_LF);
	CVector rfPos = GetPositionToOpenCarDoor(veh, CAR_DOOR_RF);

	// Left front door is closer
	if ((lfPos - GetPosition()).MagnitudeSqr2D() < (rfPos - GetPosition()).MagnitudeSqr2D()) {

		if (veh->IsRoomForPedToLeaveCar(CAR_DOOR_LF, enterOffset)) {
			m_vehDoor = CAR_DOOR_LF;
			posToOpen = lfPos;
		} else if (veh->IsRoomForPedToLeaveCar(CAR_DOOR_RF, enterOffset)) {
			m_vehDoor = CAR_DOOR_RF;
			posToOpen = rfPos;
		}
	} else {

		if (veh->IsRoomForPedToLeaveCar(CAR_DOOR_RF, enterOffset)) {

			CPed *rfPassenger = veh->pPassengers[0];
			if (rfPassenger && !veh->IsBike()
					&& (rfPassenger->m_leader == this || rfPassenger->bDontDragMeOutCar ||
						veh->VehicleCreatedBy == MISSION_VEHICLE && m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER)
					&& veh->IsRoomForPedToLeaveCar(CAR_DOOR_LF, enterOffset)
				|| (veh->m_nGettingInFlags & CAR_DOOR_FLAG_RF) && veh->IsRoomForPedToLeaveCar(CAR_DOOR_LF, enterOffset)) {

				m_vehDoor = CAR_DOOR_LF;
				posToOpen = lfPos;
			} else {
				m_vehDoor = CAR_DOOR_RF;
				posToOpen = rfPos;
			}
		} else if (veh->IsRoomForPedToLeaveCar(CAR_DOOR_LF, enterOffset)) {
			m_vehDoor = CAR_DOOR_LF;
			posToOpen = lfPos;
		}
	}
}

bool
CPed::GetNearestPassengerDoor(CVehicle *veh, CVector &posToOpen)
{
	CVector rfPos, lrPos, rrPos;
	bool canEnter = false;

	CVehicleModelInfo *vehModel = (CVehicleModelInfo *)CModelInfo::GetModelInfo(veh->GetModelIndex());

	switch (veh->GetModelIndex()) {
		case MI_BUS:
			m_vehDoor = CAR_DOOR_RF;
			posToOpen = GetPositionToOpenCarDoor(veh, CAR_DOOR_RF);
			return true;
		case MI_RHINO:
		default:
			break;
	}

	CVector2D rfPosDist(999.0f, 999.0f);
	CVector2D lrPosDist(999.0f, 999.0f);
	CVector2D rrPosDist(999.0f, 999.0f);

	if (veh->IsBike()) {
		if (!veh->pPassengers[0]
			&& !(veh->m_nGettingInFlags & CAR_DOOR_FLAG_LR)
			&& veh->IsRoomForPedToLeaveCar(CAR_DOOR_LR, nil)) {
			lrPos = GetPositionToOpenCarDoor(veh, CAR_DOOR_LR);
			canEnter = true;
			lrPosDist = lrPos - GetPosition();
		}
		if (!veh->pPassengers[0]
			&& !(veh->m_nGettingInFlags & CAR_DOOR_FLAG_RR)
			&& veh->IsRoomForPedToLeaveCar(CAR_DOOR_RR, nil)) {
			rrPos = GetPositionToOpenCarDoor(veh, CAR_DOOR_RR);
			canEnter = true;
			rrPosDist = rrPos - GetPosition();
		}
	} else if (!veh->pPassengers[0]
		&& !(veh->m_nGettingInFlags & CAR_DOOR_FLAG_RF)
		&& veh->IsRoomForPedToLeaveCar(CAR_DOOR_RF, nil)) {

		rfPos = GetPositionToOpenCarDoor(veh, CAR_DOOR_RF);
		canEnter = true;
		rfPosDist = rfPos - GetPosition();
	}

	if (vehModel->m_numDoors == 4) {
		if (!veh->pPassengers[1]
			&& !(veh->m_nGettingInFlags & CAR_DOOR_FLAG_LR)
			&& veh->IsRoomForPedToLeaveCar(CAR_DOOR_LR, nil)) {
			lrPos = GetPositionToOpenCarDoor(veh, CAR_DOOR_LR);
			canEnter = true;
			lrPosDist = lrPos - GetPosition();
		}
		if (!veh->pPassengers[2]
			&& !(veh->m_nGettingInFlags & CAR_DOOR_FLAG_RR)
			&& veh->IsRoomForPedToLeaveCar(CAR_DOOR_RR, nil)) {
			rrPos = GetPositionToOpenCarDoor(veh, CAR_DOOR_RR);
			canEnter = true;
			rrPosDist = rrPos - GetPosition();
		}

		// When the door we should enter is blocked by some object.
		if (!canEnter)
			veh->ShufflePassengersToMakeSpace();
	}

	CVector2D nextToCompare = rfPosDist;
	posToOpen = rfPos;
	m_vehDoor = CAR_DOOR_RF;
	if (lrPosDist.MagnitudeSqr() < nextToCompare.MagnitudeSqr()) {
		m_vehDoor = CAR_DOOR_LR;
		posToOpen = lrPos;
		nextToCompare = lrPosDist;
	}

	if (rrPosDist.MagnitudeSqr() < nextToCompare.MagnitudeSqr()) {
		m_vehDoor = CAR_DOOR_RR;
		posToOpen = rrPos;
	}
	return canEnter;
}

void
CPed::GoToNearestDoor(CVehicle *veh)
{
	CVector posToOpen;
	GetNearestDoor(veh, posToOpen);
	SetSeek(posToOpen, 0.5f);
	SetMoveState(PEDMOVE_RUN);
}

// Unused
void CPed::PedSetGetInCarPositionCB(CAnimBlendAssociation* assoc, void* arg)
{
	CPed* pPed = (CPed*)arg;
	CMatrix mat(pPed->GetMatrix());
	CVehicle* pVehicle = pPed->m_pMyVehicle;
	const CVector& offset = (pVehicle->bIsVan && (pPed->m_vehDoor == CAR_DOOR_RR || pPed->m_vehDoor == CAR_DOOR_LR)) ? vecPedVanRearDoorAnimOffset : vecPedCarDoorAnimOffset;
	CVector position = Multiply3x3(mat, offset) + pPed->GetPosition();
	CPedPlacement::FindZCoorForPed(&position);
	pPed->SetMoveSpeed(0.0f, 0.0f, 0.0f);
	pPed->SetPosition(position);
}

void
CPed::SetAnimOffsetForEnterOrExitVehicle(void)
{
	// FIX_BUGS: If there were no translations on enter anims, there were overflows all over this function.

	int vanBlock = CAnimManager::GetAnimationBlockIndex("van");
	int bikesBlock = CAnimManager::GetAnimationBlockIndex("bikes");
	int bikevBlock = CAnimManager::GetAnimationBlockIndex("bikev");
	int bikehBlock = CAnimManager::GetAnimationBlockIndex("bikeh");
	int bikedBlock = CAnimManager::GetAnimationBlockIndex("biked");
	CStreaming::RequestAnim(vanBlock, STREAMFLAGS_DEPENDENCY);
	CStreaming::RequestAnim(bikesBlock, STREAMFLAGS_DEPENDENCY);
	CStreaming::RequestAnim(bikevBlock, STREAMFLAGS_DEPENDENCY);
	CStreaming::RequestAnim(bikehBlock, STREAMFLAGS_DEPENDENCY);
	CStreaming::RequestAnim(bikedBlock, STREAMFLAGS_DEPENDENCY);
	CStreaming::LoadAllRequestedModels(false);
	CAnimManager::AddAnimBlockRef(vanBlock);
	CAnimManager::AddAnimBlockRef(bikesBlock);
	CAnimManager::AddAnimBlockRef(bikevBlock);
	CAnimManager::AddAnimBlockRef(bikehBlock);
	CAnimManager::AddAnimBlockRef(bikedBlock);

	CAnimBlendHierarchy *enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_STD, ANIM_STD_JACKEDCAR_LHS)->hierarchy;
	CAnimBlendSequence *seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedDraggedOutCarAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans *lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedDraggedOutCarAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LHS)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedCarDoorAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans *lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedCarDoorAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_STD, ANIM_STD_CAR_GET_IN_LO_LHS)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedCarDoorLoAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans *lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedCarDoorLoAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_STD, ANIM_STD_QUICKJACKED)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedQuickDraggedOutCarAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans *lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedQuickDraggedOutCarAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_VAN, ANIM_STD_VAN_GET_IN_REAR_LHS)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedVanRearDoorAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans *lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedVanRearDoorAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_STD, ANIM_STD_TRAIN_GETOUT)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedTrainDoorAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans *lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedTrainDoorAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_BIKE_STANDARD, ANIM_BIKE_JUMPON_LHS)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedStdBikeJumpRhsAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans* lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedStdBikeJumpRhsAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_BIKE_VESPA, ANIM_BIKE_JUMPON_LHS)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedVespaBikeJumpRhsAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans* lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedVespaBikeJumpRhsAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_BIKE_HARLEY, ANIM_BIKE_JUMPON_LHS)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedHarleyBikeJumpRhsAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans* lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedHarleyBikeJumpRhsAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_BIKE_DIRT, ANIM_BIKE_JUMPON_LHS)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedDirtBikeJumpRhsAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans* lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedDirtBikeJumpRhsAnimOffset = lastFrame->translation;
		}
	}

	enterAssoc = CAnimManager::GetAnimAssociation(ASSOCGRP_BIKE_HARLEY, ANIM_BIKE_KICK)->hierarchy;
	seq = enterAssoc->sequences;
	CAnimManager::UncompressAnimation(enterAssoc);
	if (seq->numFrames > 0) {
		if (!seq->HasTranslation())
			vecPedBikeKickAnimOffset = CVector(0.0f, 0.0f, 0.0f);
		else {
			KeyFrameTrans* lastFrame = (KeyFrameTrans*)seq->GetKeyFrame(seq->numFrames - 1);
			vecPedBikeKickAnimOffset = lastFrame->translation;
		}
	}

	CAnimManager::RemoveAnimBlockRef(vanBlock);
	CAnimManager::RemoveAnimBlockRef(bikesBlock);
	CAnimManager::RemoveAnimBlockRef(bikevBlock);
	CAnimManager::RemoveAnimBlockRef(bikehBlock);
	CAnimManager::RemoveAnimBlockRef(bikedBlock);
}

void
CPed::PedSetQuickDraggedOutCarPositionCB(CAnimBlendAssociation *animAssoc, void *arg)
{
	CPed *ped = (CPed*)arg;

	CVehicle *veh = ped->m_pMyVehicle;

	CVector finalPos;
	CVector draggedOutOffset;

	CMatrix pedMat(ped->GetMatrix());
	ped->bUsesCollision = true;
	ped->RestartNonPartialAnims();
	draggedOutOffset = vecPedQuickDraggedOutCarAnimOffset;
	if (ped->m_vehDoor == CAR_DOOR_RF || ped->m_vehDoor == CAR_DOOR_RR)
		draggedOutOffset.x = -draggedOutOffset.x;

	finalPos = Multiply3x3(pedMat, draggedOutOffset) + ped->GetPosition();
	CPedPlacement::FindZCoorForPed(&finalPos);
	ped->m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	ped->SetPosition(finalPos);

	if (veh) {
		ped->m_fRotationDest = veh->GetForward().Heading() - HALFPI;
		ped->m_fRotationCur = ped->m_fRotationDest;
		ped->CalculateNewOrientation();

		if (!veh->IsRoomForPedToLeaveCar(ped->m_vehDoor, &vecPedQuickDraggedOutCarAnimOffset))
			ped->PositionPedOutOfCollision();
	}

	if (!ped->CanSetPedState())
		return;

	ped->SetIdle();
	if (veh) {
		if (ped->bFleeAfterExitingCar) {
			ped->bFleeAfterExitingCar = false;
			ped->SetFlee(veh->GetPosition(), 14000);

		} else if (ped->bWanderPathAfterExitingCar) {
			ped->SetWanderPath(CGeneral::GetRandomNumberInRange(0.0f, 8.0f));
			ped->bWanderPathAfterExitingCar = false;

		} else if (ped->bGonnaKillTheCarJacker) {
			ped->bGonnaKillTheCarJacker = false;
			if (ped->m_pedInObjective && CGeneral::GetRandomNumber() & 1) {
				if (ped->m_objective != OBJECTIVE_KILL_CHAR_ON_FOOT)
					ped->SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, ped->m_pedInObjective);

			} else {
				CPed *driver = veh->pDriver;
				if (!driver || driver == ped || driver->IsPlayer() && CTheScripts::IsPlayerOnAMission()) {
					ped->SetFlee(veh->GetPosition(), 14000);
				} else {
					ped->ClearObjective();
					ped->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, veh);
				}
				ped->bUsePedNodeSeek = true;
				ped->m_pNextPathNode = nil;
				ped->Say(SOUND_PED_FLEE_RUN);
			}
		} else if (ped->m_pedStats->m_temper > ped->m_pedStats->m_fear
			&& ped->CharCreatedBy != MISSION_CHAR && veh->VehicleCreatedBy != MISSION_VEHICLE
			&& veh->pDriver && veh->pDriver->IsPlayer()
			&& !CTheScripts::IsPlayerOnAMission()) {
			ped->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, veh);

		} else if (ped->m_pedStats->m_temper > ped->m_pedStats->m_fear
			&& ped->CharCreatedBy != MISSION_CHAR && veh->VehicleCreatedBy != MISSION_VEHICLE
			&& !veh->pDriver && FindPlayerPed()->m_carInObjective == veh
			&& !CTheScripts::IsPlayerOnAMission()) {
			ped->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, veh);

		} else {
			ped->SetFindPathAndFlee(veh->GetPosition(), 10000);
			if (CGeneral::GetRandomNumber() & 1 || ped->m_pedStats->m_fear > 70) {
				ped->SetMoveState(PEDMOVE_SPRINT);
				ped->Say(SOUND_PED_FLEE_SPRINT);
			} else {
				ped->Say(SOUND_PED_FLEE_RUN);
			}
		}
	}
	if (ped->m_nLastPedState == PED_IDLE)
		ped->m_nLastPedState = PED_WANDER_PATH;
}

void
CPed::PedSetDraggedOutCarPositionCB(CAnimBlendAssociation* animAssoc, void* arg)
{
	CPed *ped = (CPed*)arg;

	ped->bUsesCollision = true;
	ped->RestartNonPartialAnims();

	CMatrix pedMat(ped->GetMatrix());
	CVector draggedOutOffset;
	if (ped->m_pMyVehicle && ped->m_pMyVehicle->IsBike()) {
		AssocGroupId animGroup = ((CBike*)ped->m_pMyVehicle)->m_bikeAnimType;
		switch (animGroup) {
			case ASSOCGRP_BIKE_VESPA:
				draggedOutOffset = vecPedVespaBikeJumpRhsAnimOffset;
				break;
			case ASSOCGRP_BIKE_HARLEY:
				draggedOutOffset = vecPedHarleyBikeJumpRhsAnimOffset;
				break;
			case ASSOCGRP_BIKE_DIRT:
				draggedOutOffset = vecPedDirtBikeJumpRhsAnimOffset;
				break;
			default:
				draggedOutOffset = vecPedStdBikeJumpRhsAnimOffset;
				break;
		}
	} else {
		draggedOutOffset = CVector(vecPedDraggedOutCarAnimOffset.x, vecPedDraggedOutCarAnimOffset.y, 0.0f);
	}
	if (ped->m_vehDoor == CAR_DOOR_RF || ped->m_vehDoor == CAR_DOOR_RR)
		draggedOutOffset.x = -draggedOutOffset.x;

	CVector posAfterBeingDragged = Multiply3x3(pedMat, draggedOutOffset);
	posAfterBeingDragged += ped->GetPosition();
	CPedPlacement::FindZCoorForPed(&posAfterBeingDragged);
	ped->m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	ped->SetPosition(posAfterBeingDragged);

	if (ped->m_pMyVehicle && !ped->m_pMyVehicle->IsBike() && !ped->m_pMyVehicle->IsRoomForPedToLeaveCar(ped->m_vehDoor, &draggedOutOffset)) {
		ped->PositionPedOutOfCollision();
	}

	if (!ped->CanSetPedState())
		return;
	
	if (!ped->m_pMyVehicle) {
		ped->SetIdle();
		ped->SetGetUp();
		return;
	}

	CPed *driver = ped->m_pMyVehicle->pDriver;

	if (ped->IsPlayer()) {
		ped->SetIdle();

	} else if (ped->bFleeAfterExitingCar) {
		ped->bFleeAfterExitingCar = false;
		ped->SetFlee(ped->m_pMyVehicle->GetPosition(), 4000);

	} else if (ped->bWanderPathAfterExitingCar) {
		ped->SetWanderPath(CGeneral::GetRandomNumberInRange(0.0f, 8.0f));
		ped->bWanderPathAfterExitingCar = false;

	} else if (ped->bGonnaKillTheCarJacker) {
		// Kill objective is already set at this point.

		ped->bGonnaKillTheCarJacker = false;
		if (!ped->m_pedInObjective || !(CGeneral::GetRandomNumber() & 1)) {
			if (!driver || driver == ped || driver->IsPlayer() && CTheScripts::IsPlayerOnAMission()) {
				ped->SetPedState(PED_NONE);
				ped->m_nLastPedState = PED_NONE;
				ped->SetFlee(ped->m_pMyVehicle->GetPosition(), 4000);
			} else {
				ped->ClearObjective();
				ped->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, ped->m_pMyVehicle);
			}
		}

	} else if (ped->m_pedStats->m_temper > ped->m_pedStats->m_fear && ped->CharCreatedBy != MISSION_CHAR
		&& ped->m_pMyVehicle->VehicleCreatedBy != MISSION_VEHICLE && driver
		&& driver->IsPlayer() && !CTheScripts::IsPlayerOnAMission()) {
		ped->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, ped->m_pMyVehicle);

	} else if (ped->m_pedStats->m_temper > ped->m_pedStats->m_fear && ped->CharCreatedBy != MISSION_CHAR
		&& ped->m_pMyVehicle->VehicleCreatedBy != MISSION_VEHICLE && !driver
		&& FindPlayerPed()->m_carInObjective == ped->m_pMyVehicle && !CTheScripts::IsPlayerOnAMission())
		ped->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, ped->m_pMyVehicle);
	else {
		ped->SetPedState(PED_NONE);
		ped->m_nLastPedState = PED_NONE;
		ped->SetFindPathAndFlee(ped->m_pMyVehicle->GetPosition(), 10000);
	}
	ped->SetGetUp();
}

uint8
CPed::GetNearestTrainDoor(CVehicle *train, CVector &doorPos)
{
	GetNearestTrainPedPosition(train, doorPos);
/*
	// Not used.
	CVehicleModelInfo* trainModel = (CVehicleModelInfo*)CModelInfo::GetModelInfo(train->m_modelIndex);
	CMatrix trainMat = CMatrix(train->GetMatrix());

	doorPos = trainModel->m_positions[m_vehDoor];
	doorPos.x -= 1.5f;
	doorPos = Multiply3x3(trainMat, doorPos);
	doorPos += train->GetPosition();
*/
	return 1;
}

uint8
CPed::GetNearestTrainPedPosition(CVehicle *train, CVector &enterPos)
{
	CVector enterStepOffset;
	CVehicleModelInfo *trainModel = (CVehicleModelInfo *)CModelInfo::GetModelInfo(train->GetModelIndex());
	CMatrix trainMat = CMatrix(train->GetMatrix());
	CVector leftEntryPos, rightEntryPos, midEntryPos;
	float distLeftEntry, distRightEntry, distMidEntry;

	// enterStepOffset = vecPedCarDoorAnimOffset;
	enterStepOffset = CVector(1.5f, 0.0f, 0.0f);

	if (train->pPassengers[TRAIN_POS_LEFT_ENTRY]) {
		distLeftEntry = 999.0f;
	} else {
		leftEntryPos = trainModel->m_positions[TRAIN_POS_LEFT_ENTRY] - enterStepOffset;
		leftEntryPos = Multiply3x3(trainMat, leftEntryPos);
		leftEntryPos += train->GetPosition();
		distLeftEntry = (leftEntryPos - GetPosition()).Magnitude();
	}

	if (train->pPassengers[TRAIN_POS_MID_ENTRY]) {
		distMidEntry = 999.0f;
	} else {
		midEntryPos = trainModel->m_positions[TRAIN_POS_MID_ENTRY] - enterStepOffset;
		midEntryPos = Multiply3x3(trainMat, midEntryPos);
		midEntryPos += train->GetPosition();
		distMidEntry = (midEntryPos - GetPosition()).Magnitude();
	}

	if (train->pPassengers[TRAIN_POS_RIGHT_ENTRY]) {
		distRightEntry = 999.0f;
	} else {
		rightEntryPos = trainModel->m_positions[TRAIN_POS_RIGHT_ENTRY] - enterStepOffset;
		rightEntryPos = Multiply3x3(trainMat, rightEntryPos);
		rightEntryPos += train->GetPosition();
		distRightEntry = (rightEntryPos - GetPosition()).Magnitude();
	}

	if (distMidEntry < distLeftEntry) {
		if (distMidEntry < distRightEntry) {
			enterPos = midEntryPos;
			m_vehDoor = TRAIN_POS_MID_ENTRY;
		} else {
			enterPos = rightEntryPos;
			m_vehDoor = TRAIN_POS_RIGHT_ENTRY;
		}
	} else if (distRightEntry < distLeftEntry) {
		enterPos = rightEntryPos;
		m_vehDoor = TRAIN_POS_RIGHT_ENTRY;
	} else {
		enterPos = leftEntryPos;
		m_vehDoor = TRAIN_POS_LEFT_ENTRY;
	}

	return 1;
}

void
CPed::PedSetInTrainCB(CAnimBlendAssociation* animAssoc, void* arg)
{
	CPed *ped = (CPed*)arg;
	CTrain *veh = (CTrain*)ped->m_pMyVehicle;

	if (!veh)
		return;

	ped->bInVehicle = true;
	ped->SetPedState(PED_DRIVING);
	ped->RestorePreviousObjective();
	ped->SetMoveState(PEDMOVE_STILL);
	veh->AddPassenger(ped);
}

#ifdef GTA_TRAIN
void
CPed::SetEnterTrain(CVehicle *train, uint32 unused)
{
	if (m_nPedState == PED_ENTER_TRAIN || !((CTrain*)train)->Doors[0].IsFullyOpen())
		return;

	/*
	// Not used
	CVector enterPos;
	GetNearestTrainPedPosition(train, enterPos);
	*/
	m_fRotationCur = train->GetForward().Heading() - HALFPI;
	m_pMyVehicle = train;
	m_pMyVehicle->RegisterReference((CEntity **) &m_pMyVehicle);

	SetPedState(PED_ENTER_TRAIN);
	m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_TRAIN_GETIN, 4.0f);
	m_pVehicleAnim->SetFinishCallback(PedSetInTrainCB, this);
	bUsesCollision = false;
	LineUpPedWithTrain();
	if (IsPlayer()) {
		if (((CPlayerPed*)this)->m_bAdrenalineActive)
			((CPlayerPed*)this)->ClearAdrenaline();
	}
}

void
CPed::EnterTrain(void)
{
	LineUpPedWithTrain();
}

void
CPed::SetPedPositionInTrain(void)
{
	LineUpPedWithTrain();
}

void
CPed::LineUpPedWithTrain(void)
{
	CVector lineUpPos;
	CVehicleModelInfo *trainModel = (CVehicleModelInfo *)CModelInfo::GetModelInfo(m_pMyVehicle->GetModelIndex());
	CVector enterOffset(1.5f, 0.0f, -0.2f);

	m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	m_fRotationCur = m_pMyVehicle->GetForward().Heading() - HALFPI;
	m_fRotationDest = m_fRotationCur;

	if (!bInVehicle) {
		GetNearestTrainDoor(m_pMyVehicle, lineUpPos);
		lineUpPos.z += 0.2f;
	} else {
		if (m_pMyVehicle->pPassengers[TRAIN_POS_LEFT_ENTRY] == this) {

			lineUpPos = trainModel->m_positions[TRAIN_POS_LEFT_ENTRY] - enterOffset;

		} else if (m_pMyVehicle->pPassengers[TRAIN_POS_MID_ENTRY] == this) {

			lineUpPos = trainModel->m_positions[TRAIN_POS_MID_ENTRY] - enterOffset;

		} else if (m_pMyVehicle->pPassengers[TRAIN_POS_RIGHT_ENTRY] == this) {

			lineUpPos = trainModel->m_positions[TRAIN_POS_RIGHT_ENTRY] - enterOffset;
		}
		lineUpPos = Multiply3x3(m_pMyVehicle->GetMatrix(), lineUpPos);
		lineUpPos += m_pMyVehicle->GetPosition();
	}

	if (m_pVehicleAnim) {
		float percentageLeft = m_pVehicleAnim->GetTimeLeft() / m_pVehicleAnim->hierarchy->totalLength;
		lineUpPos += (GetPosition() - lineUpPos) * percentageLeft;
	}

	SetPosition(lineUpPos);
	SetHeading(m_fRotationCur);
}

void
CPed::SetExitTrain(CVehicle* train)
{
	if (m_nPedState == PED_EXIT_TRAIN || train->GetStatus() != STATUS_TRAIN_NOT_MOVING || !((CTrain*)train)->Doors[0].IsFullyOpen())
		return;

	/*
	// Not used
	CVector exitPos;
	GetNearestTrainPedPosition(train, exitPos);
	*/
	SetPedState(PED_EXIT_TRAIN);
	m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_TRAIN_GETOUT, 4.0f);
	m_pVehicleAnim->SetFinishCallback(PedSetOutTrainCB, this);
	bUsesCollision = false;
	LineUpPedWithTrain();
}

void
CPed::ExitTrain(void)
{
	LineUpPedWithTrain();
}

void
CPed::PedSetOutTrainCB(CAnimBlendAssociation *animAssoc, void *arg)
{
	CPed *ped = (CPed*)arg;

	CVehicle *veh = ped->m_pMyVehicle;

	if (ped->m_pVehicleAnim)
		ped->m_pVehicleAnim->blendDelta = -1000.0f;

	ped->bUsesCollision = true;
	ped->m_pVehicleAnim = nil;
	ped->bInVehicle = false;
	ped->SetPedState(PED_IDLE);
	ped->RestorePreviousObjective();
	ped->SetMoveState(PEDMOVE_STILL);

	CMatrix pedMat(ped->GetMatrix());
	ped->m_fRotationCur = HALFPI + veh->GetForward().Heading();
	ped->m_fRotationDest = ped->m_fRotationCur;
	CVector posAfterExit = Multiply3x3(pedMat, vecPedTrainDoorAnimOffset);
	posAfterExit += ped->GetPosition();
	CPedPlacement::FindZCoorForPed(&posAfterExit);
	ped->m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	ped->SetPosition(posAfterExit);
	ped->SetHeading(ped->m_fRotationCur);
	veh->RemovePassenger(ped);
}
#endif

void
CPed::RegisterThreatWithGangPeds(CEntity *attacker)
{
	CPed *attackerPed = nil;
	if ((CharCreatedBy == MISSION_CHAR && bIsPlayerFriend && (attacker == FindPlayerPed() || attacker == FindPlayerVehicle()))
		|| (attacker && m_leader == attacker)
		|| (m_nPedType == PEDTYPE_GANG7 && attacker == FindPlayerPed()))
		return;

	if (attacker) {
		if (m_objective != OBJECTIVE_KILL_CHAR_ON_FOOT && m_objective != OBJECTIVE_KILL_CHAR_ANY_MEANS) {
			if (attacker->IsPed()) {
				attackerPed = (CPed*)attacker;
			} else if (attacker->IsVehicle()) {
				attackerPed = ((CVehicle*)attacker)->pDriver;
				if (!attackerPed)
					return;
			} else
				return;

			if (attackerPed && (attackerPed->IsPlayer() || attackerPed->IsGangMember())) {
				for (int i = 0; i < m_numNearPeds; ++i) {
					CPed *nearPed = m_nearPeds[i];
					if (nearPed->IsPointerValid()) {
						if (nearPed->CharCreatedBy == RANDOM_CHAR && nearPed != this && nearPed->m_nPedType == m_nPedType)
							nearPed->m_fearFlags |= CPedType::GetFlag(attackerPed->m_nPedType);
					}
				}
			}
		}
	}

	if (attackerPed && attackerPed->IsPlayer() && (attackerPed->m_nPedState == PED_CARJACK || attackerPed->bInVehicle)) {
		if (!attackerPed->m_pMyVehicle || attackerPed->m_pMyVehicle->GetModelIndex() != MI_TOPFUN) {
			int16 lastVehicle;
			CEntity *vehicles[8];
			CWorld::FindObjectsInRange(GetPosition(), 30.0f, true, &lastVehicle, 6, vehicles, false, true, false, false, false);

			if (lastVehicle > 8)
				lastVehicle = 8;

			for (int j = 0; j < lastVehicle; ++j) {
				CVehicle *nearVeh = (CVehicle*) vehicles[j];

				if (nearVeh->VehicleCreatedBy != MISSION_VEHICLE) {
					CPed *nearVehDriver = nearVeh->pDriver;

					if (nearVehDriver && nearVehDriver != this && nearVehDriver->m_nPedType == m_nPedType && nearVehDriver->CharCreatedBy == RANDOM_CHAR) {

						if (nearVeh->IsVehicleNormal() && nearVeh->IsCar()) {
							nearVeh->AutoPilot.m_nCruiseSpeed = GAME_SPEED_TO_CARAI_SPEED * nearVeh->pHandling->Transmission.fMaxCruiseVelocity * 0.8f;
							nearVeh->AutoPilot.m_nCarMission = MISSION_RAMPLAYER_FARAWAY;
							nearVeh->SetStatus(STATUS_PHYSICS);
							nearVeh->AutoPilot.m_nTempAction = TEMPACT_NONE;
							nearVeh->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
						}
					}
				}
			}
		}
	}
}

// Some helper function which doesn't exist in og game.
inline void
SelectClosestNodeForSeek(CPed *ped, CPathNode *node, CVector2D closeDist, CVector2D farDist, CPathNode *closeNode, CPathNode *closeNode2, int runCount = 3)
{
	for (int i = 0; i < node->numLinks; i++) {

		CPathNode *testNode = &ThePaths.m_pathNodes[ThePaths.ConnectedNode(i + node->firstLink)];

		if (testNode && testNode != closeNode && testNode != closeNode2) {
			CVector2D posDiff(ped->m_vecSeekPos - testNode->GetPosition());
			float dist = posDiff.MagnitudeSqr();

			if (farDist.MagnitudeSqr() > dist) {

				if (closeDist.MagnitudeSqr() > dist) {
					ped->m_pNextPathNode = (closeNode2 ? closeNode2 : testNode);
					farDist = posDiff;
				} else {
					ped->m_pNextPathNode = closeNode;
					closeDist = posDiff;
				}
			}

			if (--runCount > 0)
				SelectClosestNodeForSeek(ped, testNode, closeDist, farDist, closeNode, (closeNode2 ? closeNode2 : testNode), runCount);
		}
	}
}

bool
CPed::FindBestCoordsFromNodes(CVector unused, CVector *bestCoords)
{
	if (m_pNextPathNode || !bUsePedNodeSeek)
		return false;

	const CVector &ourPos = GetPosition();

	int closestNodeId = ThePaths.FindNodeClosestToCoors(GetPosition(), 1, 999999.9f);

	CVector seekObjPos = m_vecSeekPos;
	seekObjPos.z += 1.0f;

	if (CWorld::GetIsLineOfSightClear(ourPos, seekObjPos, true, false, false, true, false, false, false))
		return false;

	m_pNextPathNode = nil;

	CVector2D seekPosDist (m_vecSeekPos - ourPos);

	CPathNode *closestNode = &ThePaths.m_pathNodes[closestNodeId];
	CVector2D closeDist(m_vecSeekPos - closestNode->GetPosition());

	SelectClosestNodeForSeek(this, closestNode, closeDist, seekPosDist, closestNode, nil);

	if (m_pNextPathNode) {

		// Function above decided that directly going to next node makes more sense then seeking the object.
		CVector correctedCoords = CPathFind::TakeWidthIntoAccountForWandering(m_pNextPathNode, m_randomSeed);

		if ((correctedCoords - ourPos).MagnitudeSqr2D() < seekPosDist.MagnitudeSqr()) {
			*bestCoords = CPathFind::TakeWidthIntoAccountForWandering(m_pNextPathNode, m_randomSeed);
			return true;
		}
		m_pNextPathNode = nil;
	}

	return false;
}

bool
CPed::DuckAndCover(void)
{
	if (!m_pedInObjective || CTimer::GetTimeInMilliseconds() <= m_duckAndCoverTimer)
		return false;

	if (bKindaStayInSamePlace){

		if (CTimer::GetTimeInMilliseconds() <= m_leaveCarTimer) {
			if (!m_pLookTarget || m_pLookTarget != m_pedInObjective) {
				m_pLookTarget = m_pedInObjective;
				m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
			}
			if (!bIsAimingGun)
				SetAimFlag(m_pedInObjective);

		} else {
			bKindaStayInSamePlace = false;
			if (bIsDucking)
				ClearDuck(true);

			bCrouchWhenShooting = false;
			bDuckAndCover = false;
			m_headingRate = 10.0f;
			m_duckAndCoverTimer = CTimer::GetTimeInMilliseconds() + CGeneral::GetRandomNumberInRange(20000,30000);
			if (m_pSeekTarget && m_pSeekTarget->IsVehicle())
				((CVehicle*)m_pSeekTarget)->m_numPedsUseItAsCover--;
		}
		return false;
	}
	
	int16 lastVehicle = 0;
	CEntity* vehicles[8];

	bool justDucked = false;
	CVehicle *foundVeh = nil;
	float maxDist = 225.0f;
	if (bIsDucking)
		ClearDuck(true);

	bCrouchWhenShooting = false;
	bool duckingWithoutVeh = false;
	if (CTimer::GetTimeInMilliseconds() > m_leaveCarTimer) {

		for(int i = 0; i < 6; i++) {
			CPlayerPed *player = (CPlayerPed*)m_pedInObjective;

			if (player->m_pPedAtSafePos[i] == this) {
				duckingWithoutVeh = true;
				CVector &safePos = player->m_vecSafePos[i];
				bool notRunningToSafePos = false;

				if (m_vecSeekPos.x != safePos.x && m_vecSeekPos.y != safePos.y && m_vecSeekPos.z != safePos.z)
					notRunningToSafePos = true;

				if (!notRunningToSafePos) {
					CVector target = player->m_vecSafePos[i];
					SetSeek(target, 1.0f);
					duckingWithoutVeh = true;
					m_attackTimer = CTimer::GetTimeInMilliseconds() + 6000;
					bDuckAndCover = true;
				}
				break;
			}
		}
		if (!duckingWithoutVeh) {
			for (int i = 0; i < 6; i++) {
				CPlayerPed* player = (CPlayerPed*)m_pedInObjective;
				if (!player->m_pPedAtSafePos[i] && player->m_vecSafePos[i].x != 0.0f) {
					player->m_pPedAtSafePos[i] = this;
					CVector target = player->m_vecSafePos[i];
					SetSeek(target, 1.0f);
					m_headingRate = 15.0f;
					ClearPointGunAt();
					duckingWithoutVeh = 1;
					bIsRunning = true;
					bDuckAndCover = true;
					justDucked = true;
					m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 500;
					break;
				}
			}
		}
		if (!duckingWithoutVeh) {
			CVector pos = GetPosition();
			CWorld::FindObjectsInRange(pos, CHECK_NEARBY_THINGS_MAX_DIST, true, &lastVehicle, 6, vehicles, false, true, false, false, false);
		}

		for (int i = 0; i < lastVehicle; i++) {
			CVehicle *veh = (CVehicle*) vehicles[i];
			if (veh->IsCar() && veh->m_vecMoveSpeed.Magnitude() <= 0.02f
				&& !veh->bIsBus && !veh->bIsVan && !veh->bIsBig
				&& veh->m_numPedsUseItAsCover < 3) {

				float dist = (GetPosition() - veh->GetPosition()).MagnitudeSqr();
				if (dist < maxDist) {
					maxDist = dist;
					foundVeh = veh;
				}
			}
		}
		if (foundVeh) {
			// Unused.
			// CVector lfWheelPos, rfWheelPos;
			// foundVeh->GetComponentWorldPosition(CAR_WHEEL_RF, rfWheelPos);
			// foundVeh->GetComponentWorldPosition(CAR_WHEEL_LF, lfWheelPos);
			CVector rightSide, leftSide;

			// 3 persons can use the car as cover. Found the correct position for us.
			if (foundVeh->m_numPedsUseItAsCover == 2) {
				rightSide = CVector(1.5f, -0.5f, 0.0f);
				leftSide = CVector(-1.5f, -0.5f, 0.0f);
			} else if (foundVeh->m_numPedsUseItAsCover == 1) {
				rightSide = CVector(1.5f, 0.5f, 0.0f);
				leftSide = CVector(-1.5f, 0.5f, 0.0f);
			} else if (foundVeh->m_numPedsUseItAsCover == 0) {
				rightSide = CVector(1.5f, 0.0f, 0.0f);
				leftSide = CVector(-1.5f, 0.0f, 0.0f);
			}

			CMatrix vehMatrix(foundVeh->GetMatrix());
			CVector duckAtRightSide = Multiply3x3(vehMatrix, rightSide) + foundVeh->GetPosition();

			CVector duckAtLeftSide = Multiply3x3(vehMatrix, leftSide) + foundVeh->GetPosition();

			CVector distWithPedRightSide = m_pedInObjective->GetPosition() - duckAtRightSide;
			CVector distWithPedLeftSide = m_pedInObjective->GetPosition() - duckAtLeftSide;

			CVector duckPos;
			if (distWithPedRightSide.MagnitudeSqr() <= distWithPedLeftSide.MagnitudeSqr())
				duckPos = duckAtLeftSide;
			else
				duckPos = duckAtRightSide;

			if (CWorld::TestSphereAgainstWorld(duckPos, 0.5f, nil, true, true, true, false, false, false)) {
				SetSeek(duckPos, 1.0f);
				m_headingRate = 15.0f;
				bIsRunning = true;
				bDuckAndCover = true;
				justDucked = true;
				m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 500;
				if (foundVeh->bIsLawEnforcer) {
					m_carInObjective = foundVeh;
					m_carInObjective->RegisterReference((CEntity**)&m_carInObjective);
				}
				m_pSeekTarget = foundVeh;
				m_pSeekTarget->RegisterReference((CEntity**)&m_pSeekTarget);
				ClearPointGunAt();
			} else {
				m_duckAndCoverTimer = CTimer::GetTimeInMilliseconds() + CGeneral::GetRandomNumberInRange(10000, 15000);
				bDuckAndCover = false;
			}
		} else if (!duckingWithoutVeh) {
			bDuckAndCover = false;
		}
	}

	if (!justDucked && !bDuckAndCover)
		return false;
	
	if (!Seek()) {
		if (m_nMoveState == PEDMOVE_STILL) {
			bDuckAndCover = false;
			return false;
		} else
			return true;
	}

	bKindaStayInSamePlace = true;
	bDuckAndCover = false;
	m_vecSeekPos = CVector(0.0f, 0.0f, 0.0f);
	if (m_pSeekTarget && m_pSeekTarget->IsVehicle())
		((CVehicle*)m_pSeekTarget)->m_numPedsUseItAsCover++;
	
	SetIdle();
	SetMoveState(PEDMOVE_STILL);
	SetMoveAnim();
	if (!m_pLookTarget || m_pLookTarget != m_pedInObjective) {
		m_pLookTarget = m_pedInObjective;
		m_pLookTarget->RegisterReference((CEntity **) &m_pLookTarget);
	}

	m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + CGeneral::GetRandomNumberInRange(3000, 6000);
	bCrouchWhenShooting = true;
	SetDuck(CGeneral::GetRandomNumberInRange(2000, 5000), true);
	return false;
}

CVector
CPed::GetPositionToOpenCarDoor(CVehicle *veh, uint32 component, float offset)
{	
	CVector doorPos;
	CMatrix vehMat(veh->GetMatrix());

	if (veh->IsBike()) {
		CVehicleModelInfo* vehModel = (CVehicleModelInfo*)CModelInfo::GetModelInfo(veh->GetModelIndex());
		CVector vehDoorOffset;
		CBike* bike = (CBike*)veh;
		doorPos = vehModel->GetFrontSeatPosn();

		if (component == CAR_WINDSCREEN) {
#ifdef FIX_BUGS
			return bike->GetMatrix() * (doorPos +
				CVector(-vecPedBikeKickAnimOffset.x, vecPedBikeKickAnimOffset.y, -vecPedBikeKickAnimOffset.z));
#else
			return bike->GetMatrix() * (doorPos + vecPedBikeKickAnimOffset);
#endif
		} else {
			switch (bike->m_bikeAnimType) {
			case ASSOCGRP_BIKE_VESPA:
				vehDoorOffset = vecPedVespaBikeJumpRhsAnimOffset;
				break;
			case ASSOCGRP_BIKE_HARLEY:
				vehDoorOffset = vecPedHarleyBikeJumpRhsAnimOffset;
				break;
			case ASSOCGRP_BIKE_DIRT:
				vehDoorOffset = vecPedDirtBikeJumpRhsAnimOffset;
				break;
			default:
				vehDoorOffset = vecPedStdBikeJumpRhsAnimOffset;
				break;
			}
			vehDoorOffset.x += offset * bike->pHandling->fSeatOffsetDistance;
			if (component == CAR_DOOR_LR || component == CAR_DOOR_RR) {
				doorPos = vehModel->m_positions[CAR_POS_BACKSEAT];
			}

			if (component == CAR_DOOR_LR || component == CAR_DOOR_LF)
				vehDoorOffset.x *= -1.f;

			CVector correctedPos;
			bike->GetCorrectedWorldDoorPosition(correctedPos, vehDoorOffset, doorPos);
			return correctedPos;
		}
	}
	doorPos = Multiply3x3(vehMat, GetLocalPositionToOpenCarDoor(veh, component, offset));

	return veh->GetPosition() + doorPos;
}

CVector
CPed::GetLocalPositionToOpenCarDoor(CVehicle *veh, uint32 component, float seatPosMult)
{
	CVehicleModelInfo *vehModel; 
	CVector vehDoorPos;
	CVector vehDoorOffset;
	float seatOffset;

	vehModel = (CVehicleModelInfo *)CModelInfo::GetModelInfo(veh->GetModelIndex());

	if (veh->IsBike()) {
		CBike *bike = (CBike*)veh;
		vehDoorPos = vehModel->GetFrontSeatPosn();

		if (component == CAR_WINDSCREEN) {
			return bike->GetMatrix() * (vehDoorPos + vecPedBikeKickAnimOffset);
		} else {
			switch (bike->m_bikeAnimType) {
				case ASSOCGRP_BIKE_VESPA:
					vehDoorOffset = vecPedVespaBikeJumpRhsAnimOffset;
					break;
				case ASSOCGRP_BIKE_HARLEY:
					vehDoorOffset = vecPedHarleyBikeJumpRhsAnimOffset;
					break;
				case ASSOCGRP_BIKE_DIRT:
					vehDoorOffset = vecPedDirtBikeJumpRhsAnimOffset;
					break;
				default:
					vehDoorOffset = vecPedStdBikeJumpRhsAnimOffset;
					break;
			}
			float xOffsetFromAnim = vehDoorOffset.x + seatPosMult * bike->pHandling->fSeatOffsetDistance;
			if (component == CAR_DOOR_LR || component == CAR_DOOR_RR) {
				vehDoorPos = vehModel->m_positions[CAR_POS_BACKSEAT];
			}

			if (component == CAR_DOOR_LR || component == CAR_DOOR_LF)
				xOffsetFromAnim *= -1.f;

			return bike->GetMatrix() * (vehDoorPos + CVector(xOffsetFromAnim, vehDoorOffset.y, vehDoorOffset.z));
		}
	} else {
		if (veh->bIsVan && (component == CAR_DOOR_LR || component == CAR_DOOR_RR)) {
			seatOffset = 0.0f;
			vehDoorOffset = vecPedVanRearDoorAnimOffset;
		} else {
			seatOffset = veh->pHandling->fSeatOffsetDistance * seatPosMult;
			if (veh->bLowVehicle) {
				vehDoorOffset = vecPedCarDoorLoAnimOffset;
			} else {
				vehDoorOffset = vecPedCarDoorAnimOffset;
			}
		}

		switch (component) {
			case CAR_DOOR_RF:
				vehDoorPos = vehModel->GetFrontSeatPosn();
				vehDoorPos.x += seatOffset;
				vehDoorOffset.x = -vehDoorOffset.x;
				break;

			case CAR_DOOR_RR:
				vehDoorPos = vehModel->m_positions[CAR_POS_BACKSEAT];
				vehDoorPos.x += seatOffset;
				vehDoorOffset.x = -vehDoorOffset.x;
				break;

			case CAR_DOOR_LF:
				vehDoorPos = vehModel->GetFrontSeatPosn();
				vehDoorPos.x = -(vehDoorPos.x + seatOffset);
				break;

			case CAR_DOOR_LR:
				vehDoorPos = vehModel->m_positions[CAR_POS_BACKSEAT];
				vehDoorPos.x = -(vehDoorPos.x + seatOffset);
				break;

			default:
				vehDoorPos = vehModel->GetFrontSeatPosn();
				vehDoorOffset = CVector(0.0f, 0.0f, 0.0f);
		}
		return vehDoorPos - vehDoorOffset;
	}
}

// TODO: what is this parameter for?
void
CPed::SetDuck(uint32 time, bool sth)
{
	if (bIsDucking || CTimer::GetTimeInMilliseconds() <= m_duckTimer && !sth) {
		if (sth && CTimer::GetTimeInMilliseconds() + time > m_duckTimer)
			m_duckTimer = CTimer::GetTimeInMilliseconds() + time;
		return;
	}

	CAnimBlendAssociation *duckAssoc;
	if (bCrouchWhenShooting) {
		duckAssoc = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_DUCK_WEAPON, 4.0f);
		duckAssoc->flags &= ~ASSOC_FADEOUTWHENDONE;
		bIsDucking = true;
		m_duckTimer = CTimer::GetTimeInMilliseconds() + time;
	} else {
		CAnimBlendAssociation *duckAssoc = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_DOWN);
		if (!duckAssoc || duckAssoc->blendDelta < 0.0f) {
			CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_DUCK_DOWN, 4.0f);
			bIsDucking = true;
			m_duckTimer = CTimer::GetTimeInMilliseconds() + time;
		}
	}
}

void
CPed::Duck(void)
{
	if (CTimer::GetTimeInMilliseconds() > m_duckTimer)
		ClearDuck();
	else if (bIsDucking && bCrouchWhenShooting) {
		CWeaponInfo *weapon = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);
		CAnimBlendAssociation *crouchAnim = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_WEAPON);
		if (!crouchAnim) {
			if(GetCrouchFireAnim(weapon))
				crouchAnim = RpAnimBlendClumpGetAssociation(GetClump(), GetCrouchFireAnim(weapon));
		}
		if (!crouchAnim) {
			if(GetCrouchReloadAnim(weapon))
				crouchAnim = RpAnimBlendClumpGetAssociation(GetClump(), GetCrouchReloadAnim(weapon));
		}
		if (!crouchAnim) {
			bIsDucking = false;
#if defined FIX_BUGS || defined FREE_CAM
			if (IsPlayer())
				bCrouchWhenShooting = false;
#endif
		}
	}
}

void
CPed::ClearDuck(bool clearTimer)
{
	CAnimBlendAssociation *animAssoc = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_DOWN);
	if (!animAssoc) {
		animAssoc = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_LOW);
	}
	if (!animAssoc) {
		animAssoc = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_WEAPON);
	}

	if (animAssoc) {
		animAssoc->flags |= ASSOC_DELETEFADEDOUT;
		animAssoc->blendDelta = -4.0f;
	}
	bIsDucking = false;

	if (clearTimer) {
		m_duckTimer = 0;
	}
}

void
CPed::InformMyGangOfAttack(CEntity *attacker)
{
	CPed *attackerPed;

	if (m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT || m_objective == OBJECTIVE_KILL_CHAR_ANY_MEANS)
		return;

	if (attacker->IsPed()) {
		attackerPed = (CPed*)attacker;
	} else {
		if (!attacker->IsVehicle())
			return;

		attackerPed = ((CVehicle*)attacker)->pDriver;
		if (!attackerPed)
			return;
	}

	if (attackerPed->m_nPedType == PEDTYPE_COP)
		return;

	for (int i = 0; i < m_numNearPeds; i++)	{
		CPed *nearPed = m_nearPeds[i];
		if (nearPed && nearPed != this) {
			CPed *leader = nearPed->m_leader;
			if (leader && leader == this && nearPed->m_pedStats->m_fear < nearPed->m_pedStats->m_temper) {
				nearPed->SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, attackerPed);
				nearPed->SetObjectiveTimer(30000);
			}
		}
	}
}

void
CPed::PedAnimDoorCloseRollingCB(CAnimBlendAssociation* animAssoc, void* arg)
{
	CPed* ped = (CPed*)arg;

	CAutomobile* veh = (CAutomobile*)(ped->m_pMyVehicle);

	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;

	if (veh->bLowVehicle) {
		veh->ProcessOpenDoor(CAR_DOOR_LF, ANIM_STD_CAR_CLOSE_DOOR_ROLLING_LO_LHS, 1.0f);
	} else {
		veh->ProcessOpenDoor(CAR_DOOR_LF, ANIM_STD_CAR_CLOSE_DOOR_ROLLING_LHS, 1.0f);
	}

	veh->m_nGettingOutFlags &= ~CAR_DOOR_FLAG_LF;

	if (veh->Damage.GetDoorStatus(DOOR_FRONT_LEFT) == DOOR_STATUS_SWINGING)
		veh->Damage.SetDoorStatus(DOOR_FRONT_LEFT, DOOR_STATUS_OK);
}

void
CPed::SetSeekBoatPosition(CVehicle *boat)
{
	if (m_nPedState == PED_SEEK_IN_BOAT || boat->pDriver || !IsPedInControl())
		return;

	SetStoredState();
	m_carInObjective = boat;
	m_carInObjective->RegisterReference((CEntity **) &m_carInObjective);
	m_pMyVehicle = boat;
	m_pMyVehicle->RegisterReference((CEntity **) &m_pMyVehicle);
	m_distanceToCountSeekDone = 0.5f;
	SetPedState(PED_SEEK_IN_BOAT);
}

void
CPed::SeekBoatPosition(void)
{
	if (m_carInObjective && !m_carInObjective->pDriver) {
		CVehicleModelInfo *boatModel = m_carInObjective->GetModelInfo();

		CVector enterOffset;
		enterOffset = boatModel->GetFrontSeatPosn();
		enterOffset.x = 0.0f;
		CMatrix boatMat(m_carInObjective->GetMatrix());
		SetMoveState(PEDMOVE_WALK);
		m_vecSeekPos = boatMat * enterOffset;
		if (Seek()) {
			// We arrived to the boat
			m_vehDoor = 0;
			SetEnterCar(m_carInObjective, 0);
		}
	} else
		RestorePreviousState();
}

bool
CPed::IsRoomToBeCarJacked(void)
{
	if (!m_pMyVehicle)
		return false;

	CVector offset;
	if (m_pMyVehicle->IsBike()) {
		offset = vecPedStdBikeJumpRhsAnimOffset;
	} else if (m_pMyVehicle->bLowVehicle || m_nPedType == PEDTYPE_COP) {
		offset = vecPedDraggedOutCarAnimOffset;
	} else {
		offset = vecPedQuickDraggedOutCarAnimOffset;
	}

	offset.z = 0.0f;
	if (m_pMyVehicle->IsRoomForPedToLeaveCar(CAR_DOOR_LF, &offset)) {
		return true;
	}

	return false;
}

void
CPed::AddInCarAnims(CVehicle* car, bool isDriver)
{
	if (car->IsBoat()) {
		if (car->pHandling->Flags & HANDLING_SIT_IN_BOAT) {
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SIT, 100.0f);
		} else {
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_BOAT_DRIVE, 100.0f);
		}
	} else if (car->IsBike()) {
		if (isDriver) {
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ((CBike*)car)->m_bikeAnimType, ANIM_BIKE_RIDE, 100.0f);
		} else {
			m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ((CBike*)car)->m_bikeAnimType, ANIM_BIKE_RIDE_P, 100.0f);
		}
	} else {
		if (isDriver) {
			if (car->bLowVehicle) {
				m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SIT_LO, 100.0f);
			} else {
				m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SIT, 100.0f);
			}
		} else {
			if (car->bLowVehicle) {
				m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SIT_P_LO, 100.0f);
			} else {
				m_pVehicleAnim = CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_CAR_SIT_P, 100.0f);
			}
		}
	}

	StopNonPartialAnims();
}

void
CPed::RemoveDrivebyAnims()
{
	CAnimBlendAssociation *animAssoc;

	AnimationId LeftAnim = ANIM_STD_CAR_DRIVEBY_LEFT;
	AnimationId RightAnim = ANIM_STD_CAR_DRIVEBY_RIGHT;

	if (m_pMyVehicle->pHandling->Flags & HANDLING_IS_BIKE) {
		LeftAnim = ANIM_BIKE_DRIVEBY_RHS;
		RightAnim = ANIM_BIKE_DRIVEBY_LHS;
	} else if (m_pMyVehicle->bLowVehicle) {
		LeftAnim = ANIM_STD_CAR_DRIVEBY_LEFT_LO;
		RightAnim = ANIM_STD_CAR_DRIVEBY_RIGHT_LO;
	}

	animAssoc = RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ANIM_BIKE_DRIVEBY_RHS);
	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;
	animAssoc = RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ANIM_BIKE_DRIVEBY_LHS);
	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;
	animAssoc = RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ANIM_BIKE_DRIVEBY_FORWARD);
	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;
}

void
CPed::RemoveInCarAnims(void)
{
	CAnimBlendAssociation* assoc;

	for (assoc = RpAnimBlendClumpGetFirstAssociation(GetClump(), ASSOC_DRIVING); assoc;
		assoc = RpAnimBlendGetNextAssociation(assoc, ASSOC_DRIVING)) {
		assoc->flags |= ASSOC_DELETEFADEDOUT;
		assoc->blendDelta = -1000.0f;
	}
}

bool
CPed::PositionPedOutOfCollision(void)
{
	CVehicle *veh = m_pMyVehicle;
	if (!veh)
		return false;

	if (bDonePositionOutOfCollision)
		return true;

	bool foundAPos = false;
	CColModel *vehCol = veh->GetColModel();
	CVector vehPos = veh->GetPosition();
	CVector ourPos = GetPosition();
	CVector newPos = ourPos;
	CWorld::pIgnoreEntity = veh;
	bUsesCollision = false;
	bJustCheckCollision = true;
	m_vecMoveSpeed = CVector(0.f, 0.f, 0.f);
	if (veh->IsOnItsSide()) {
		// Top of the veh.
		newPos = vehPos;
		newPos.z = FEET_OFFSET + vehCol->boundingBox.max.x + vehPos.z;
		GetMatrix().SetTranslate(newPos);
		if (!CheckCollision()) {
			if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
				foundAPos = true;
		}

	} else if (m_vehDoor != 0) {
		// Try the normal way
		CVector pos = GetPositionToOpenCarDoor(m_pMyVehicle, m_vehDoor);
		newPos = pos;
		GetMatrix().SetTranslate(newPos);
		if (!CheckCollision()) {
			if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
				foundAPos = true;
		}
	}

	float vehRelativeExitX = vehCol->boundingBox.min.x - 0.355f;
	if (m_vehDoor == CAR_DOOR_RF || m_vehDoor == CAR_DOOR_RR)
		vehRelativeExitX = 0.355f + vehCol->boundingBox.max.x;

	if (!foundAPos) {
		// Check sides of veh., respective to seat column-veh. center difference(why?)
		float exitOffset = vehRelativeExitX - DotProduct(ourPos - vehPos, veh->GetRight());
		newPos = exitOffset * veh->GetRight() + ourPos;
		GetMatrix().SetTranslate(newPos);
		if (!CheckCollision()) {
			if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
				foundAPos = true;
		}
	}
	if (!foundAPos) {
		// Iterate through sections of veh. length + static offset on X
		float minY = vehCol->boundingBox.min.y;
		float ySection = (vehCol->boundingBox.max.y - minY) / 3.f;
		for (int i = 0; i < 4; i++) {
			float fwdMult = i * ySection + minY;
			newPos = vehRelativeExitX * veh->GetRight() + fwdMult * veh->GetForward() + vehPos;
			GetMatrix().SetTranslate(newPos);
			if (!CheckCollision()) {
				if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false)) {
					foundAPos = true;
					break;
				}
			}
		}
	}
	if (!foundAPos) {
		// Back of veh.
		newPos = (vehCol->boundingBox.min.y - 0.355f) * veh->GetForward() + vehPos;
		GetMatrix().SetTranslate(newPos);
		if (!CheckCollision()) {
			if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
				foundAPos = true;
		}
	}
	if (!foundAPos) {
		// Front of veh.
		newPos = (0.355f + vehCol->boundingBox.max.y) * veh->GetForward() + vehPos;
		GetMatrix().SetTranslate(newPos);
		if (!CheckCollision()) {
			if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
				foundAPos = true;
		}
	}
	if (!foundAPos) {
		// Opposite X side + back
		newPos = vehCol->boundingBox.min.y * veh->GetForward() + vehPos - vehRelativeExitX * veh->GetRight();
		GetMatrix().SetTranslate(newPos);
		if (!CheckCollision()) {
			if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
				foundAPos = true;
		}
	}
	if (!foundAPos) {
		// Opposite X side + front
		newPos = vehCol->boundingBox.max.y * veh->GetForward() + vehPos - vehRelativeExitX * veh->GetRight();
		GetMatrix().SetTranslate(newPos);
		if (!CheckCollision()) {
			if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
				foundAPos = true;
		}
	}
	if (!foundAPos) {
		// Top of veh.
		if (veh->m_vehType == 0) {
			newPos = vehCol->boundingBox.max.z * veh->GetUp() + vehPos;
			newPos.z += FEET_OFFSET;
			GetMatrix().SetTranslate(newPos);
			if (!CheckCollision()) {
				if (CWorld::GetIsLineOfSightClear(vehPos, newPos, true, false, false, true, false, false, false))
					foundAPos = true;
			}
		}
	}
	m_vecMoveSpeed = CVector(0.f, 0.f, 0.f);
	m_vecTurnSpeed = CVector(0.f, 0.f, 0.f);
	veh->m_vecMoveSpeed = CVector(0.f, 0.f, 0.f);
	veh->m_vecTurnSpeed = CVector(0.f, 0.f, 0.f);
	CWorld::pIgnoreEntity = nil;
	bUsesCollision = true;
	bJustCheckCollision = false;
	bDonePositionOutOfCollision = true;
	if (foundAPos)
		return true;
	int foundNode = ThePaths.FindNodeClosestToCoors(vehPos, PATH_PED, 999999.9f, true, false, false, false);
	if (foundNode < 0)
		return false;
	newPos = ThePaths.m_pathNodes[foundNode].GetPosition();
	CPedPlacement::FindZCoorForPed(&newPos);
	GetMatrix().SetTranslate(newPos);
	SetHeading(m_pMyVehicle->GetForward().Heading());
	return true;
}

// "Any" means he shouldn't have to be in vehicle.
bool
CPed::PositionAnyPedOutOfCollision(void)
{
	CVehicle *veh;
	CVector posNearVeh;
	CVector posSomewhereClose;
	bool putNearVeh = false;
	bool putSomewhereClose = false;
	int smallestDistNearVeh = 999;
	int smallestDistSomewhereClose = 999;

	CVector potentialPos;
	potentialPos.y = GetPosition().y - 3.5f;
	potentialPos.z = GetPosition().z;

	for (int yTry = 0; yTry < 15; yTry++) {
		potentialPos.x = GetPosition().x - 3.5f;

		for (int xTry = 0; xTry < 15; xTry++) {
			CPedPlacement::FindZCoorForPed(&potentialPos);
			if (!CWorld::TestSphereAgainstWorld(potentialPos, 0.6f, this, true, false, false, true, false, false)) {
				float potentialChangeSqr = (potentialPos - GetPosition()).MagnitudeSqr();
				veh = (CVehicle*)CWorld::TestSphereAgainstWorld(potentialPos, 0.6f, this, false, true, false, false, false, false);
				if (veh) {
					if (potentialChangeSqr < smallestDistNearVeh) {
						posNearVeh = potentialPos;
						putNearVeh = true;
						smallestDistNearVeh = potentialChangeSqr;
					}
				} else if (potentialChangeSqr < smallestDistSomewhereClose) {
					smallestDistSomewhereClose = potentialChangeSqr;
					posSomewhereClose = potentialPos;
					putSomewhereClose = true;
				}
			}
			potentialPos.x += 0.5f;
		}
		potentialPos.y += 0.5f;
	}

	if (!putSomewhereClose && !putNearVeh)
		return false;

	// We refrain from using posNearVeh, probably because of it may be top of the vehicle.
	if (putSomewhereClose) {
		SetPosition(posSomewhereClose);
	} else {
		CVector vehSize = veh->GetModelInfo()->GetColModel()->boundingBox.max;
		posNearVeh.z += vehSize.z;
		SetPosition(posNearVeh);
	}
	return true;
}

bool
CPed::WarpPedToNearLeaderOffScreen(void)
{
	bool teleported = false;
	if (GetIsOnScreen() || m_leaveCarTimer > CTimer::GetTimeInMilliseconds())
		return false;

	CVector warpToPos = m_leader->GetPosition();
	CVector distVec = warpToPos - GetPosition();
	float halfOfDist = distVec.Magnitude() * 0.5f;
	CVector halfNormalizedDist = distVec / halfOfDist;

	CVector appropriatePos = GetPosition();
	int tryCount = Min(10, (int)halfOfDist);
	for (int i = 0; i < tryCount; ++i) {
		appropriatePos += halfNormalizedDist;
		CVector zCorrectedPos = appropriatePos;
		CPedPlacement::FindZCoorForPed(&zCorrectedPos);

		if (Abs(zCorrectedPos.z - warpToPos.z) < 3.0f || Abs(zCorrectedPos.z - appropriatePos.z) < 3.0f) {
			appropriatePos.z = zCorrectedPos.z;
			if (!TheCamera.IsSphereVisible(appropriatePos, 0.6f)
				&& CWorld::GetIsLineOfSightClear(appropriatePos, warpToPos, true, true, false, true, false, false, false)
				&& !CWorld::TestSphereAgainstWorld(appropriatePos, 0.6f, this, true, true, false, true, false, false)) {
				teleported = true;
				Teleport(appropriatePos);
			}
		}
	}
	m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 3000;
	return teleported;
}

bool
CPed::WarpPedToNearEntityOffScreen(CEntity *warpTo)
{
	bool teleported = false;
	if (GetIsOnScreen() || m_leaveCarTimer > CTimer::GetTimeInMilliseconds())
		return false;

	CVector warpToPos = warpTo->GetPosition();
	CVector distVec = warpToPos - GetPosition();
	float halfOfDist = distVec.Magnitude() * 0.5f;
	CVector halfNormalizedDist = distVec / halfOfDist;

	CVector appropriatePos = GetPosition();
	int tryCount = Min(10, (int)halfOfDist);
	for (int i = 0; i < tryCount; ++i) {
		appropriatePos += halfNormalizedDist;
		CVector zCorrectedPos = appropriatePos;
		CPedPlacement::FindZCoorForPed(&zCorrectedPos);

		if (Abs(zCorrectedPos.z - warpToPos.z) < 3.0f || Abs(zCorrectedPos.z - appropriatePos.z) < 3.0f) {
			appropriatePos.z = zCorrectedPos.z;
			if (!TheCamera.IsSphereVisible(appropriatePos, 0.6f)
				&& CWorld::GetIsLineOfSightClear(appropriatePos, warpToPos, true, true, false, true, false, false, false)
				&& !CWorld::TestSphereAgainstWorld(appropriatePos, 0.6f, this, true, true, false, true, false, false)) {
				teleported = true;
				Teleport(appropriatePos);
			}
		}
	}
	m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 3000;
	return teleported;
}

int32
CPed::KillCharOnFootArmed(CVector &ourPos, CVector &targetPos, CVector &distWithTarget)
{
	bool killPlayerInNoPoliceZone = false;
	if (m_pedInObjective->IsPlayer() && CCullZones::NoPolice())
		killPlayerInNoPoliceZone = true;

	if (!bNotAllowedToDuck || killPlayerInNoPoliceZone) {
		if (m_nPedType == PEDTYPE_COP && !m_pedInObjective->GetWeapon()->IsTypeMelee())
			bNotAllowedToDuck = true;
	} else {
		if (!m_pedInObjective->bInVehicle) {
			if (m_pedInObjective->GetWeapon()->IsTypeMelee()) {
				bNotAllowedToDuck = false;
				bCrouchWhenShooting = false;
			} else if (DuckAndCover()) {
				return CANT_ATTACK;
			}
		} else {
			bNotAllowedToDuck = false;
			bCrouchWhenShooting = false;
		}
	}
	if (m_leaveCarTimer > CTimer::GetTimeInMilliseconds() && !bKindaStayInSamePlace) {
		SetMoveState(PEDMOVE_STILL);
		return CANT_ATTACK;
	}
	if (m_pedInObjective->IsPlayer()) {
		CPlayerPed *player = FindPlayerPed();
		if (m_nPedType == PEDTYPE_COP && player->m_pWanted->m_bIgnoredByCops
			|| player->m_pWanted->m_bIgnoredByEveryone
			|| m_pedInObjective->bIsInWater
			|| m_pedInObjective->m_nPedState == PED_ARRESTED) {

			if (m_nPedState != PED_ARREST_PLAYER)
				SetIdle();

			return CANT_ATTACK;
		}
	}
	if (m_pedInObjective->IsPlayer() && m_nPedType != PEDTYPE_COP
		&& CharCreatedBy != MISSION_CHAR && FindPlayerPed()->m_pWanted->m_CurrentCops != 0/* TODO: && !bAttacksPlayerWithCops*/) {
		SetObjective(OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE);

		return CANT_ATTACK;
	}
	if (m_pedInObjective->m_fHealth <= 0.0f) {
		bObjectiveCompleted = true;
		bScriptObjectiveCompleted = true;
		return CANT_ATTACK;
	}
	CWeaponInfo *wepInfo = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);
	float wepRange = wepInfo->m_fRange;
	float wepRangeAdjusted = wepRange / 3.f;

	float distWithTargetSc = distWithTarget.Magnitude();
	if (m_pedInObjective->bInVehicle && m_pedInObjective->m_nPedState != PED_DRAG_FROM_CAR) {
		CVehicle *vehOfTarget = m_pedInObjective->m_pMyVehicle;
		if (vehOfTarget->bIsInWater || vehOfTarget->GetStatus() == STATUS_PLAYER_DISABLED
			|| m_pedInObjective->IsPlayer() && CPad::GetPad(0)->ArePlayerControlsDisabled()) {
			SetIdle();
			return WATCH_UNTIL_HE_DISAPPEARS;
		}
		SetLookFlag(vehOfTarget, false);
		if (m_nMoveState == PEDMOVE_STILL && IsPedInControl())
			TurnBody();

		if (m_nPedState != PED_CARJACK) {
			if (m_pedInObjective->m_nPedState != PED_ARRESTED) {
				if (m_attackTimer < CTimer::GetTimeInMilliseconds() && distWithTargetSc < wepRange && distWithTargetSc > 3.0f) {

					SetAttack(vehOfTarget);
					SetWeaponLockOnTarget(vehOfTarget);
					SetShootTimer(CGeneral::GetRandomNumberInRange(500, 2000));
					
					CVector2D dirVehGoing = vehOfTarget->m_vecMoveSpeed;
					if (dirVehGoing.Magnitude() > 0.2f) {
						CVector2D vehDist = GetPosition() - vehOfTarget->GetPosition();
						vehDist.Normalise();
						dirVehGoing.Normalise();
						if (DotProduct2D(vehDist, dirVehGoing) > 0.8f) {
							SetAttackTimer(CGeneral::GetRandomNumberInRange(200, 500));
							SetMoveState(PEDMOVE_STILL);
						}
						return ATTACK_IN_PROGRESS;
					}
					if (distWithTargetSc <= m_distanceToCountSeekDone) {
						SetAttackTimer(CGeneral::GetRandomNumberInRange(200, 500));
						SetMoveState(PEDMOVE_STILL);
					} else {
						SetAttackTimer(CGeneral::GetRandomNumberInRange(2000, 5000));
					}
					return ATTACK_IN_PROGRESS;
				} else if (m_nPedState != PED_ATTACK && !bKindaStayInSamePlace && !killPlayerInNoPoliceZone) {
					if (vehOfTarget) {
						if (m_nPedType == PEDTYPE_COP || vehOfTarget->bIsBus) {
							GoToNearestDoor(vehOfTarget);
						} else {
							m_vehDoor = 0;
							if (m_pedInObjective == vehOfTarget->pDriver || vehOfTarget->bIsBus) {
								m_vehDoor = CAR_DOOR_LF;
							} else if (m_pedInObjective == vehOfTarget->pPassengers[0]) {
								m_vehDoor = CAR_DOOR_RF;
							} else if (m_pedInObjective == vehOfTarget->pPassengers[1]) {
								m_vehDoor = CAR_DOOR_LR;
							} else if (m_pedInObjective == vehOfTarget->pPassengers[2]) {
								m_vehDoor = CAR_DOOR_RR;
							}
							// Unused
							// GetPositionToOpenCarDoor(vehOfTarget, m_vehDoor);
							SetSeekCar(vehOfTarget, m_vehDoor);
							SetMoveState(PEDMOVE_RUN);
						}
					}
				}
			}
		}
		return ATTACK_IN_PROGRESS;
	}
	if (m_nMoveState == PEDMOVE_STILL && IsPedInControl()) {
		SetLookFlag(m_pedInObjective, false);
		TurnBody();
	}
	if (m_nPedType == PEDTYPE_COP && m_pedInObjective->IsPlayer()) {
		float maxArrestDist = 1.5f;
		if (((CCopPed*)this)->m_bDragsPlayerFromCar) {
			if (m_nPedState == PED_FALL) {
				maxArrestDist = 3.5f;
			} else if (m_nPedState != PED_DRAG_FROM_CAR) {
				((CCopPed*)this)->m_bDragsPlayerFromCar = 0;
			}
		}

		if (distWithTargetSc < maxArrestDist) {
			if (m_pedInObjective->m_getUpTimer > CTimer::GetTimeInMilliseconds()
				|| m_pedInObjective->m_nPedState == PED_DRAG_FROM_CAR) {

				((CCopPed*)this)->SetArrestPlayer(m_pedInObjective);
				return WATCH_UNTIL_HE_DISAPPEARS;
			}
		}
	}
	/*
	if (distWithTargetSc > 0.1f) {
		junk code
	} */

	if (m_shotTime != 0 && m_ceaseAttackTimer != 0) {
		if (CTimer::GetTimeInMilliseconds() > m_ceaseAttackTimer + m_shotTime) {
			ClearLookFlag();
			bObjectiveCompleted = true;
			m_shotTime = 0;
			return CANT_ATTACK;
		}
	}

	if (!bKindaStayInSamePlace && !bStopAndShoot && m_nPedState != PED_ATTACK && !bDuckAndCover && !killPlayerInNoPoliceZone) {
		if (distWithTargetSc > wepRange
			|| m_pedInObjective->m_getUpTimer > CTimer::GetTimeInMilliseconds()
			|| m_pedInObjective->m_nPedState == PED_ARRESTED
			|| m_pedInObjective->EnteringCar() && distWithTargetSc < 3.0f) {

			if (m_pedInObjective->EnteringCar())
				wepRangeAdjusted = 2.0f;

			if (bUsePedNodeSeek) {
				CVector bestCoords(0.0f, 0.0f, 0.0f);
				m_vecSeekPos = m_pedInObjective->GetPosition();

				if (!m_pNextPathNode)
					FindBestCoordsFromNodes(m_vecSeekPos, &bestCoords);

				if (m_pNextPathNode)
					m_vecSeekPos = CPathFind::TakeWidthIntoAccountForWandering(m_pNextPathNode, m_randomSeed);

				SetSeek(m_vecSeekPos, m_distanceToCountSeekDone);
			} else {
				SetSeek(m_pedInObjective, wepRangeAdjusted);
			}
			if (m_pedInObjective->m_pCurrentPhysSurface && distWithTargetSc < 5.0f) {
				bStopAndShoot = true;
				b158_8 = true;
				SetMoveState(PEDMOVE_STILL);
			} else if (b158_8) {
				bStopAndShoot = false;
				b158_8 = false;
			}
			return ATTACK_IN_PROGRESS;
		}
	}
	if (m_attackTimer < CTimer::GetTimeInMilliseconds()
		&& distWithTargetSc < wepRange && m_pedInObjective->m_nPedState != PED_GETUP && m_pedInObjective->m_nPedState != PED_DRAG_FROM_CAR) {

		if (bIsDucking && !bCrouchWhenShooting) {
			CAnimBlendAssociation* duckAnim = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_DOWN);
			if (!duckAnim)
				duckAnim = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_LOW);
			if (!duckAnim)
				duckAnim = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_WEAPON);

			if (duckAnim) {
				duckAnim->flags |= ASSOC_DELETEFADEDOUT;
				duckAnim->blendDelta = -4.0f;
			}
			bIsDucking = false;
			return CANT_ATTACK;
		}
		bObstacleShowedUpDuringKillObjective = false;
		SetAttack(m_pedInObjective);
		SetWeaponLockOnTarget(m_pedInObjective);
		SetShootTimer(CGeneral::GetRandomNumberInRange(600.0f, 1500.0f));

		int time;
		if (distWithTargetSc <= wepRangeAdjusted)
			time = CGeneral::GetRandomNumberInRange(100.0f, 500.0f);
		else
			time = CGeneral::GetRandomNumberInRange(1500.0f, 3000.0f);

		SetAttackTimer(time);
	} else {
		if (!m_pedInObjective->m_pCurrentPhysSurface && b158_8) {
			b158_8 = false;
			bStopAndShoot = false;
		}

		if (m_nPedState != PED_ATTACK && m_nPedState != PED_FIGHT) {
			if (bNotAllowedToDuck && bKindaStayInSamePlace && !bIsDucking && bCrouchWhenShooting) {
				SetDuck(CGeneral::GetRandomNumberInRange(1000, 5000), false);
				return CANT_ATTACK;
			}
			if (bObstacleShowedUpDuringKillObjective) {
				if (m_nPedType == PEDTYPE_COP) {
					if (GetWeapon()->m_eWeaponType > WEAPONTYPE_COLT45
						|| m_fleeFrom && m_fleeFrom->IsObject()) {
						wepRangeAdjusted = 6.0f;
					} else if (m_fleeFrom && m_fleeFrom->IsVehicle()) {
						wepRangeAdjusted = 4.0f;
					} else {
						wepRangeAdjusted = 2.0f;
					}
				} else {
					wepRangeAdjusted = 2.0f;
				}
			}
			if (distWithTargetSc <= wepRangeAdjusted) {
				SetMoveState(PEDMOVE_STILL);
				bIsPointingGunAt = true;
				if (m_nPedState != PED_AIM_GUN && !bDuckAndCover) {
					m_attackTimer = CTimer::GetTimeInMilliseconds();
					SetIdle();
				}
			} else {
				if (m_nPedState != PED_SEEK_ENTITY && m_nPedState != PED_SEEK_POS
					&& !bStopAndShoot && !killPlayerInNoPoliceZone && !bKindaStayInSamePlace) {
					Say(SOUND_PED_ATTACK);
					SetSeek(m_pedInObjective, wepRangeAdjusted);
					bIsRunning = true;
					if (m_nPedType == PEDTYPE_COP && FindPlayerPed()->m_pWanted->m_CurrentCops > 1) {
						if (CGeneral::GetRandomNumber() & 1)
							Say(SOUND_PED_GUNAIMEDAT3);
						else
							Say(SOUND_PED_GUNAIMEDAT2);
					}
				}
			}
		}
	}

	if (CTimer::GetTimeInMilliseconds() > m_nPedStateTimer)
		m_fRotationDest = CGeneral::GetRadianAngleBetweenPoints(m_pedInObjective->GetPosition().x, m_pedInObjective->GetPosition().y, GetPosition().x, GetPosition().y);
				
	return ATTACK_IN_PROGRESS;
}

int32
CPed::KillCharOnFootMelee(CVector &ourPos, CVector &targetPos, CVector &distWithTarget)
{
	bool killPlayerInNoPoliceZone = false;
	float distWithTargetSc = distWithTarget.Magnitude();
	CPlayerPed *victimPlayer = nil;
	if (m_pedInObjective->IsPlayer())
		victimPlayer = (CPlayerPed*)m_pedInObjective;

	if (victimPlayer) {
		if (CCullZones::NoPolice()
			|| m_pedInObjective->m_pCurrentPhysSurface
			&& m_pedInObjective->m_pCurrentPhysSurface != m_pCurrentPhysSurface
			&& distWithTargetSc < 5.f) {

			if (victimPlayer && victimPlayer->m_bSpeedTimerFlag && (IsGangMember() || m_nPedType == PEDTYPE_COP)
				&& CharCreatedBy != MISSION_CHAR) {
				GiveWeapon(WEAPONTYPE_COLT45, 1000, 1);
				SetCurrentWeapon(WEAPONTYPE_COLT45);
				SetMoveState(PEDMOVE_STILL);
				bStopAndShoot = true;
				b158_8 = true;
				return CANT_ATTACK;
			}
			killPlayerInNoPoliceZone = true;
		}
	}
	bNotAllowedToDuck = false;
	bStopAndShoot = false;
	b158_8 = false;
	if (m_leaveCarTimer > CTimer::GetTimeInMilliseconds() && !bKindaStayInSamePlace) {
		SetMoveState(PEDMOVE_STILL);
		return CANT_ATTACK;
	}
	if (victimPlayer) {
		CPlayerPed *player = FindPlayerPed();
		if (m_nPedType == PEDTYPE_COP && player->m_pWanted->m_bIgnoredByCops
			|| player->m_pWanted->m_bIgnoredByEveryone
			|| m_pedInObjective->bIsInWater
			|| m_pedInObjective->m_nPedState == PED_ARRESTED) {

			if (m_nPedState != PED_ARREST_PLAYER)
				SetIdle();

			return CANT_ATTACK;
		}
	}
	if (victimPlayer && m_nPedType != PEDTYPE_COP && CharCreatedBy != MISSION_CHAR
		&& FindPlayerPed()->m_pWanted->m_CurrentCops != 0) {
		SetObjective(OBJECTIVE_FLEE_ON_FOOT_TILL_SAFE);

		return CANT_ATTACK;
	}
	if (m_pedInObjective->m_fHealth <= 0.0f) {
		bObjectiveCompleted = true;
		bScriptObjectiveCompleted = true;
		return ATTACK_IN_PROGRESS;
	}
	bool canReachVictim = false;
	uint32 endOfAttack = 0;
	CWeaponInfo *wepInfo = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);

	// Already calculated at the start
	// float distWithTargetSc = distWithTarget.Magnitude();
	float maxDistToKeep = 0.3f;
	float wepRange = wepInfo->m_fRange / 2.f;

	if (GetWeapon()->m_eWeaponType == WEAPONTYPE_UNARMED && !IsPlayer() && !(m_pedStats->m_flags & STAT_CAN_KICK))
		wepRange -= 0.3f;

	if (distWithTargetSc <= 5.f && victimPlayer && !victimPlayer->m_bNoPosForMeleeAttack) {
	
		if (m_pedInObjective->EnteringCar() && wepRange > 2.f) {
			m_vecSeekPos = m_pedInObjective->GetPosition();
			wepRange = 1.0f;
			maxDistToKeep = 0.5f;
		} else {
			int8 attackDir = victimPlayer->FindMeleeAttackPoint(this, distWithTarget, endOfAttack);
			if (attackDir == -1) {
				m_vecSeekPos = victimPlayer->GetPosition();
				maxDistToKeep = 4.0f;
			} else {
				victimPlayer->GetMeleeAttackCoords(m_vecSeekPos, attackDir, wepRange);
				distWithTargetSc = (m_vecSeekPos - GetPosition()).Magnitude();
				canReachVictim = true;
			}
		}
	} else {
		m_vecSeekPos = m_pedInObjective->GetPosition();
		maxDistToKeep = Max(0.8f, 0.9f * wepRange);
		wepRange *= 1.1f;
		if (victimPlayer && victimPlayer->m_bNoPosForMeleeAttack)
			victimPlayer = nil;
	}

	if (m_pedInObjective->bInVehicle && m_pedInObjective->m_nPedState != PED_DRAG_FROM_CAR) {
		CVehicle *vehOfTarget = m_pedInObjective->m_pMyVehicle;

		if (vehOfTarget){
			if (vehOfTarget->bIsInWater || vehOfTarget->GetStatus() == STATUS_PLAYER_DISABLED
				|| m_pedInObjective->IsPlayer() && CPad::GetPad(0)->ArePlayerControlsDisabled()) {
				SetIdle();
				return WATCH_UNTIL_HE_DISAPPEARS;
			}
			SetLookFlag(vehOfTarget, false);

			if (m_nPedState != PED_CARJACK) {
				if (m_pedInObjective->m_nPedState != PED_ARRESTED) {
					if (m_nPedState != PED_ATTACK && !bKindaStayInSamePlace && !killPlayerInNoPoliceZone) {

						if (m_nPedType == PEDTYPE_COP || vehOfTarget->bIsBus) {
							GoToNearestDoor(vehOfTarget);
						} else {
							m_vehDoor = 0;
							if (m_pedInObjective == vehOfTarget->pDriver || vehOfTarget->bIsBus) {
								m_vehDoor = CAR_DOOR_LF;
							} else if (m_pedInObjective == vehOfTarget->pPassengers[0]) {
								m_vehDoor = CAR_DOOR_RF;
							} else if (m_pedInObjective == vehOfTarget->pPassengers[1]) {
								m_vehDoor = CAR_DOOR_LR;
							} else if (m_pedInObjective == vehOfTarget->pPassengers[2]) {
								m_vehDoor = CAR_DOOR_RR;
							}
							// Unused
							// GetPositionToOpenCarDoor(vehOfTarget, m_vehDoor);
							SetSeekCar(vehOfTarget, m_vehDoor);
							SetMoveState(PEDMOVE_RUN);
						}
					}
				}
			}
		}
		return ATTACK_IN_PROGRESS;
	}
	if (m_nMoveState == PEDMOVE_STILL && IsPedInControl()) {
		SetLookFlag(m_pedInObjective, false);
		if(m_nPedState == PED_IDLE || m_nPedState == PED_ATTACK || m_nPedState == PED_FIGHT)
			TurnBody();
	}
	if (m_nPedType == PEDTYPE_COP && m_pedInObjective->IsPlayer()) {
		float maxArrestDist = 1.5f;
		if (((CCopPed*)this)->m_bDragsPlayerFromCar) {
			if (m_nPedState == PED_FALL) {
				maxArrestDist = 3.5f;
			} else if (m_nPedState != PED_DRAG_FROM_CAR) {
				((CCopPed*)this)->m_bDragsPlayerFromCar = 0;
			}
		}

		if (distWithTargetSc < maxArrestDist) {
			if (m_pedInObjective->m_getUpTimer > CTimer::GetTimeInMilliseconds()
				|| m_pedInObjective->m_nPedState == PED_DRAG_FROM_CAR) {

				((CCopPed*)this)->SetArrestPlayer(m_pedInObjective);
				return WATCH_UNTIL_HE_DISAPPEARS;
			}
		}
	}

	if (distWithTargetSc > maxDistToKeep && !bKindaStayInSamePlace && m_nPedState != PED_ATTACK &&
		(m_nPedState != PED_FIGHT || m_curFightMove == FIGHTMOVE_IDLE) && !killPlayerInNoPoliceZone) {

		bool goForward = false;

		if (m_nPedState == PED_FIGHT) {
			if (canReachVictim) {
				CVector attackAndVictimDist = m_vecSeekPos - m_pedInObjective->GetPosition();
				CVector victimFarness = attackAndVictimDist / wepRange;
				CVector distVec = GetPosition() - m_pedInObjective->GetPosition();
				float distSqr = distVec.MagnitudeSqr();
				if (sq(wepRange) > distSqr && distSqr > 0.05f) {
					distVec.Normalise();
					if (DotProduct2D(victimFarness, distVec) > Cos(DEGTORAD(30.f)))
						goForward = true;
				}
			}
		}
		if (goForward) {
			m_curFightMove = FIGHTMOVE_SHUFFLE_F;
			CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_STD_FIGHT_SHUFFLE_B, 16.f)->SetFinishCallback(FinishFightMoveCB,this);
			m_fightState = FIGHTSTATE_NO_MOVE;
			m_fightButtonPressure = 0;
			m_takeAStepAfterAttack = false;

		} else if (bUsePedNodeSeek && !canReachVictim) {
			CVector bestCoords(0.0f, 0.0f, 0.0f);

			if (!m_pNextPathNode)
				FindBestCoordsFromNodes(m_vecSeekPos, &bestCoords);

			if (m_pNextPathNode)
				m_vecSeekPos = CPathFind::TakeWidthIntoAccountForWandering(m_pNextPathNode, m_randomSeed);

			SetSeek(m_vecSeekPos, m_distanceToCountSeekDone);
		} else {
			if (canReachVictim)
				SetSeek(m_vecSeekPos, maxDistToKeep);
			else
				SetSeek(m_pedInObjective, maxDistToKeep);
		}
		return ATTACK_IN_PROGRESS;
	}

	if (m_attackTimer < CTimer::GetTimeInMilliseconds()
		&& distWithTargetSc < wepRange && m_pedInObjective->m_nPedState != PED_GETUP && m_pedInObjective->m_nPedState != PED_DRAG_FROM_CAR) {

		if (bIsDucking) {
			CAnimBlendAssociation* duckAnim = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_DOWN);
			if (!duckAnim)
				duckAnim = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_LOW);
			if (!duckAnim)
				duckAnim = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_STD_DUCK_WEAPON);

			if (duckAnim) {
				duckAnim->flags |= ASSOC_DELETEFADEDOUT;
				duckAnim->blendDelta = -4.0f;
			}
			bIsDucking = false;
			return CANT_ATTACK;
		}

		if (canReachVictim || !victimPlayer) {
			SetMoveState(PEDMOVE_STILL);
			SetAttack(m_pedInObjective);
			m_fRotationDest = CGeneral::GetRadianAngleBetweenPoints(
				m_pedInObjective->GetPosition().x, m_pedInObjective->GetPosition().y,
				GetPosition().x, GetPosition().y);
			SetShootTimer(CGeneral::GetRandomNumberInRange(0.f, 500.f));

			int time;
			if (endOfAttack <= CTimer::GetTimeInMilliseconds())
				time = CGeneral::GetRandomNumberInRange(100.0f, 1500.0f);
			else
				time = endOfAttack - CTimer::GetTimeInMilliseconds() + CGeneral::GetRandomNumberInRange(400.0f, 1500.0f);

			SetAttackTimer(time);
			bObstacleShowedUpDuringKillObjective = false;
		}
		return ATTACK_IN_PROGRESS;
	} else {
		if (!m_pedInObjective->m_pCurrentPhysSurface && m_pCurrentPhysSurface && b158_8) {
			b158_8 = false;
			bStopAndShoot = false;
		}

		if (m_nPedState != PED_ATTACK && m_nPedState != PED_FIGHT) {
			SetMoveState(PEDMOVE_STILL);
			if (GetWeapon()->m_eWeaponType == WEAPONTYPE_UNARMED)
				StartFightAttack(0);
		}
		return ATTACK_IN_PROGRESS;
	}
}

bool
CPed::CanBeDamagedByThisGangMember(CPed* who)
{
	return m_gangFlags & (1 << (who->m_nPedType - PEDTYPE_GANG1));
}
