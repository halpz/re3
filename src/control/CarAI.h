#pragma once

#include "AutoPilot.h"

class CVehicle;

class CCarAI
{
public:
	static float FindSwitchDistanceClose(CVehicle*);
	static float FindSwitchDistanceFarNormalVehicle(CVehicle*);
	static float FindSwitchDistanceFar(CVehicle*);
#ifdef MIAMI
	static void BackToCruisingIfNoWantedLevel(CVehicle*);
#endif
	static void UpdateCarAI(CVehicle*);
	static void CarHasReasonToStop(CVehicle*);
	static float GetCarToGoToCoors(CVehicle*, CVector*);
#ifdef MIAMI
	static float GetCarToParkAtCoors(CVehicle*, CVector*);
#endif
	static void AddPoliceCarOccupants(CVehicle*);
	static void AddAmbulanceOccupants(CVehicle*);
	static void AddFiretruckOccupants(CVehicle*);
	static void TellOccupantsToLeaveCar(CVehicle*);
#ifdef MIAMI
	static void TellOccupantsToFleeCar(CVehicle*);
#endif
	static void TellCarToRamOtherCar(CVehicle*, CVehicle*);
	static void TellCarToBlockOtherCar(CVehicle*, CVehicle*);
	static eCarMission FindPoliceCarMissionForWantedLevel();
#ifdef MIAMI
	static eCarMission FindPoliceBoatMissionForWantedLevel();
#endif
	static int32 FindPoliceCarSpeedForWantedLevel(CVehicle*);
	static void MellowOutChaseSpeed(CVehicle*);
#ifdef MIAMI
	static void MellowOutChaseSpeedBoat(CVehicle*);
#endif
	static void MakeWayForCarWithSiren(CVehicle *veh);
};
