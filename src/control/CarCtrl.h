#pragma once

class CVehicle;
class CZoneInfo;

class CCarCtrl
{
	enum eCarClass {
		POOR = 0,
		RICH,
		EXEC,
		WORKER,
		SPECIAL,
		BIG,
		TAXI,
		CLASS7,
		MAFIA,
		TRIAD,
		DIABLO,
		YAKUZA,
		YARDIE,
		COLOMB,
		NINES,
		GANG8,
		GANG9,
		COPS
	};
public:
	static void SwitchVehicleToRealPhysics(CVehicle*);
	static void AddToCarArray(int32 id, int32 vehclass);
	static void UpdateCarCount(CVehicle*, bool);
	static int32 ChooseCarModel(int32 vehclass);
	static bool JoinCarWithRoadSystemGotoCoors(CVehicle*, CVector, bool);
	static void JoinCarWithRoadSystem(CVehicle*);
	static void SteerAICarWithPhysics(CVehicle*);
	static void UpdateCarOnRails(CVehicle*);
	static bool MapCouldMoveInThisArea(float x, float y);
	static void ScanForPedDanger(CVehicle *veh);
	static void RemoveFromInterestingVehicleList(CVehicle*);
	static void GenerateRandomCars(void);
	static void GenerateOneRandomCar(void);
	static void GenerateEmergencyServicesCar(void);
	static int32 ChooseModel(CZoneInfo*, CVector*, int*);
	static int32 ChoosePoliceCarModel(void);
	static int32 ChooseGangCarModel(int32 gang);

	static int32 &NumLawEnforcerCars;
	static int32 &NumAmbulancesOnDuty;
	static int32 &NumFiretrucksOnDuty;
	static int32 &NumRandomCars;
	static int32 &NumMissionCars;
	static int32 &NumParkedCars;
	static bool &bCarsGeneratedAroundCamera;
	static float &CarDensityMultiplier;
	static int8 &CountDownToCarsAtStart;
	static int32 &MaxNumberOfCarsInUse;
	static uint32 &LastTimeLawEnforcerCreated;
	static int32 (&TotalNumOfCarsOfRating)[7];
	static int32 (&NextCarOfRating)[7];
	static int32 (&CarArrays)[7][256];
};
