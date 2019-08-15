#include "common.h"
#include "patcher.h"
#include "CarAI.h"

#include "AutoPilot.h"
#include "Timer.h"
#include "Vehicle.h"

WRAPPER void CCarAI::UpdateCarAI(CVehicle*) { EAXJMP(0x413E50); }
WRAPPER void CCarAI::MakeWayForCarWithSiren(CVehicle *veh) { EAXJMP(0x416280); }
WRAPPER eCarMission CCarAI::FindPoliceCarMissionForWantedLevel() { EAXJMP(0x415E30); }
WRAPPER int32 CCarAI::FindPoliceCarSpeedForWantedLevel(CVehicle*) { EAXJMP(0x415EB0); }
WRAPPER void CCarAI::AddPoliceOccupants(CVehicle*) { EAXJMP(0x415C60); }

void CCarAI::CarHasReasonToStop(CVehicle* pVehicle)
{
	pVehicle->AutoPilot.m_nAntiReverseTimer = CTimer::GetTimeInMilliseconds();
}

STARTPATCHES
InjectHook(0x415B00, &CCarAI::CarHasReasonToStop, PATCH_JUMP);
ENDPATCHES