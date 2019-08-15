#pragma once

#include "AutoPilot.h"

class CVehicle;

class CCarAI
{
public:
	static void UpdateCarAI(CVehicle*);
	static void MakeWayForCarWithSiren(CVehicle *veh);
	static int32 FindPoliceCarSpeedForWantedLevel(CVehicle*);
	static eCarMission FindPoliceCarMissionForWantedLevel();
	static void AddPoliceOccupants(CVehicle*);
	static void CarHasReasonToStop(CVehicle*);
};
