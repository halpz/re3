#pragma once
#include "PathFind.h"
#include "Vehicle.h"

class CZoneInfo;

enum{
	MAX_CARS_TO_KEEP = 2,
	MAX_CAR_MODELS_IN_ARRAY = 256,
};

#define LANE_WIDTH 5.0f

#ifdef FIX_BUGS
#define FIX_PATHFIND_BUG
#endif

#undef FIX_PATHFIND_BUG

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
	static void RemoveDistantCars(void);
	static void PossiblyRemoveVehicle(CVehicle*);
	static bool IsThisVehicleInteresting(CVehicle*);
	static int32 CountCarsOfType(int32 mi);
	static void SlowCarOnRailsDownForTrafficAndLights(CVehicle*);
	static bool PickNextNodeAccordingStrategy(CVehicle*);
	static void DragCarToPoint(CVehicle*, CVector*);
	static float FindMaximumSpeedForThisCarInTraffic(CVehicle*);
	static void SlowCarDownForCarsSectorList(CPtrList&, CVehicle*, float, float, float, float, float*, float);
	static void SlowCarDownForPedsSectorList(CPtrList&, CVehicle*, float, float, float, float, float*, float);
	static void Init(void);
	static void SlowCarDownForOtherCar(CEntity*, CVehicle*, float*, float);
	static float TestCollisionBetween2MovingRects(CVehicle*, CVehicle*, float, float, CVector*, CVector*, uint8);
	static float FindAngleToWeaveThroughTraffic(CVehicle*, CPhysical*, float, float);
	static void WeaveThroughCarsSectorList(CPtrList&, CVehicle*, CPhysical*, float, float, float, float, float*, float*);
	static void WeaveForOtherCar(CEntity*, CVehicle*, float*, float*);
	static void WeaveThroughPedsSectorList(CPtrList&, CVehicle*, CPhysical*, float, float, float, float, float*, float*);
	static void WeaveForPed(CEntity*, CVehicle*, float*, float*);
	static void WeaveThroughObjectsSectorList(CPtrList&, CVehicle*, float, float, float, float, float*, float*);
	static void WeaveForObject(CEntity*, CVehicle*, float*, float*);
#ifdef FIX_PATHFIND_BUG
	static void PickNextNodeToChaseCar(CVehicle*, float, float, float, CVehicle*);
#else
	static void PickNextNodeToChaseCar(CVehicle*, float, float, CVehicle*);
#endif
	static bool PickNextNodeToFollowPath(CVehicle*);
	static void PickNextNodeRandomly(CVehicle*);
	static uint8 FindPathDirection(int32, int32, int32);

	static float GetOffsetOfLaneFromCenterOfRoad(int8 lane, CCarPathLink* pLink)
	{
		return (lane + ((pLink->numLeftLanes == 0) ? (0.5f - 0.5f * pLink->numRightLanes) :
			((pLink->numRightLanes == 0) ? (0.5f - 0.5f * pLink->numLeftLanes) : 0.5f))) * LANE_WIDTH;
	}

	static float GetPositionAlongCurrentCurve(CVehicle* pVehicle)
	{
		uint32 timeInCurve = CTimer::GetTimeInMilliseconds() - pVehicle->AutoPilot.m_nTimeEnteredCurve;
		return (float)timeInCurve / pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve;
	}

	static float LimitRadianAngle(float angle)
	{
		while (angle < -PI)
			angle += TWOPI;
		while (angle > PI)
			angle -= TWOPI;
		return angle;
	}

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
	static int32 (&CarArrays)[7][MAX_CAR_MODELS_IN_ARRAY];
};

extern CVehicle* (&apCarsToKeep)[MAX_CARS_TO_KEEP];