#include "common.h"

#include "Bridge.h"
#include "Pools.h"
#include "ModelIndices.h"
#include "PathFind.h"
#include "Stats.h"

//--LCS: file done except TODO

CEntity *CBridge::pLiftRoad;
CEntity *CBridge::pLiftPart;
CEntity *CBridge::pWeight;

int CBridge::State;
int CBridge::OldState;

float CBridge::DefaultZLiftPart;
float CBridge::DefaultZLiftRoad;
float CBridge::DefaultZLiftWeight;

float CBridge::OldLift;

uint32 CBridge::TimeOfBridgeBecomingOperational;

void CBridge::Init()
{
#ifdef GTA_BRIDGE
	FindBridgeEntities();
	State = STATE_BRIDGE_LOCKED;
	OldLift = -1.0f;
	if (pLiftPart && pWeight)
	{
		DefaultZLiftPart   = pLiftPart->GetPosition().z;
		if (pLiftRoad)
			DefaultZLiftRoad = pLiftRoad->GetPosition().z;
		DefaultZLiftWeight = pWeight->GetPosition().z;

		ThePaths.SetLinksBridgeLights(-330.0, -230.0, -700.0, -588.0, true);
	}
#endif
}

void CBridge::Update()
{
#ifdef GTA_BRIDGE
	if (!pLiftPart || !pWeight)
		return;

	OldState = State;

	float liftHeight;

	if (State == STATE_BRIDGE_LOCKED) {
		liftHeight = 25.0f;
		TimeOfBridgeBecomingOperational = 0;
	}
	else if (State == STATE_BRIDGE_ALWAYS_UNLOCKED) {
		liftHeight = 0.0f;
		TimeOfBridgeBecomingOperational = CTimer::GetTimeInMilliseconds() - 20001;
	}
	else {
		if (TimeOfBridgeBecomingOperational == 0)
			TimeOfBridgeBecomingOperational = CTimer::GetTimeInMilliseconds();

		// Time remaining for bridge to become operational
		// this time cycle duration is 0x20000, so ~2:11
		uint32 timeElapsed = (CTimer::GetTimeInMilliseconds() - TimeOfBridgeBecomingOperational) % 0x20000;

		// Calculate lift part height and bridge state
		if (timeElapsed < 20000)
		{
			State = STATE_LIFT_PART_MOVING_DOWN;
			liftHeight = 25.0f - timeElapsed / 20000.0f * 25.0f;
		}
		else if (timeElapsed < 80000)
		{
			liftHeight = 0.0f;
			State = STATE_LIFT_PART_IS_DOWN;
		}
		else if (timeElapsed < 90000)
		{
			liftHeight = 0.0f;
			State = STATE_LIFT_PART_ABOUT_TO_MOVE_UP;
		}
		else if (timeElapsed < 110000)
		{
			State = STATE_LIFT_PART_MOVING_UP;
			liftHeight = (timeElapsed - 90000) / 20000.0f * 25.0f;
		}
		else
		{
			liftHeight = 25.0f;
			State = STATE_LIFT_PART_IS_UP;
		}
	}


	// Move bridge part
	if (liftHeight != OldLift)
	{
		pLiftPart->GetMatrix().GetPosition().z = DefaultZLiftPart + liftHeight;
		pLiftPart->GetMatrix().UpdateRW();
		pLiftPart->UpdateRwFrame();
		if (pLiftRoad)
		{
			pLiftRoad->GetMatrix().GetPosition().z = DefaultZLiftRoad + liftHeight;
			pLiftRoad->GetMatrix().UpdateRW();
			pLiftRoad->UpdateRwFrame();
		}
		pWeight->GetMatrix().GetPosition().z = DefaultZLiftWeight - liftHeight;
		pWeight->GetMatrix().UpdateRW();
		pWeight->UpdateRwFrame();

		OldLift = liftHeight;
	}

	// TODO(LCS): cWorldStream

	if (State == STATE_LIFT_PART_ABOUT_TO_MOVE_UP && OldState == STATE_LIFT_PART_IS_DOWN)
		ThePaths.SetLinksBridgeLights(-330.0, -230.0, -700.0, -588.0, true);
	else if (State == STATE_LIFT_PART_IS_DOWN && OldState == STATE_LIFT_PART_MOVING_DOWN)
		ThePaths.SetLinksBridgeLights(-330.0, -230.0, -700.0, -588.0, false);
#endif
}

bool CBridge::ShouldLightsBeFlashing()
{
#ifdef GTA_BRIDGE
	return State != STATE_LIFT_PART_IS_DOWN;
#else
	return false;
#endif
}

void CBridge::FindBridgeEntities()
{
#ifdef GTA_BRIDGE
	pWeight   = nil;
	pLiftRoad = nil;
	pLiftPart = nil;

	for (int i = CPools::GetBuildingPool()->GetSize()-1; i >= 0; i--) {
		CBuilding* entry = CPools::GetBuildingPool()->GetSlot(i);
		if (entry)
		{
			if (entry->GetModelIndex() == MI_BRIDGELIFT)
				pLiftPart = entry;
			else if (entry->GetModelIndex() == MI_BRIDGEROADSEGMENT)
				pLiftRoad = entry;
			else if (entry->GetModelIndex() == MI_BRIDGEWEIGHT)
				pWeight = entry;
		}
	}
#endif
}

bool CBridge::ThisIsABridgeObjectMovingUp(int index)
{
#ifdef GTA_BRIDGE
	if (index != MI_BRIDGEROADSEGMENT && index != MI_BRIDGELIFT)
		return false;

	return State == STATE_LIFT_PART_ABOUT_TO_MOVE_UP || State == STATE_LIFT_PART_MOVING_UP;
#else
	return false;
#endif
}

void CBridge::ForceBridgeState(uint8 state)
{
#ifdef GTA_BRIDGE
	State = state;
	switch (state)
	{
	case STATE_BRIDGE_LOCKED:
	case STATE_LIFT_PART_MOVING_DOWN:
	case STATE_LIFT_PART_ABOUT_TO_MOVE_UP:
		ThePaths.SetLinksBridgeLights(-330.0f, -230.0f, -700.0f, -588.0f, true);
		break;
	case STATE_BRIDGE_ALWAYS_UNLOCKED:
		ThePaths.SetLinksBridgeLights(-330.0f, -230.0f, -700.0f, -588.0f, false);
		break;
	default:
		break;
	}
#endif
}