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
	static void AddAmbulanceOccupants(CVehicle*);
	static void AddFiretruckOccupants(CVehicle*);
	static void CarHasReasonToStop(CVehicle*);
	static void TellOccupantsToLeaveCar(CVehicle*);
	static float GetCarToGoToCoors(CVehicle*, CVector*);
};
