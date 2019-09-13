#include "common.h"
#include "patcher.h"
#include "CarCtrl.h"

#include "Automobile.h"
#include "Camera.h"
#include "CarAI.h"
#include "CarGen.h"
#include "Cranes.h"
#include "Curves.h"
#include "CutsceneMgr.h"
#include "Gangs.h"
#include "Garages.h"
#include "General.h"
#include "IniFile.h"
#include "ModelIndices.h"
#include "PathFind.h"
#include "Ped.h"
#include "PlayerInfo.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "Renderer.h"
#include "RoadBlocks.h"
#include "Timer.h"
#include "TrafficLights.h"
#include "Streaming.h"
#include "VisibilityPlugins.h"
#include "Vehicle.h"
#include "Wanted.h"
#include "World.h"
#include "Zones.h"

#define GAME_SPEED_TO_METERS_PER_SECOND 50.0f
#define GAME_SPEED_TO_CARAI_SPEED 60.0f

#define DISTANCE_TO_SPAWN_ROADBLOCK_PEDS 51.0f
#define DISTANCE_TO_SCAN_FOR_DANGER 11.0f
#define SAFE_DISTANCE_TO_PED 3.0f
#define INFINITE_Z 1000000000.0f

#define VEHICLE_HEIGHT_DIFF_TO_CONSIDER_WEAVING 4.0f
#define PED_HEIGHT_DIFF_TO_CONSIDER_WEAVING 4.0f
#define OBJECT_HEIGHT_DIFF_TO_CONSIDER_WEAVING 8.0f
#define WIDTH_COEF_TO_WEAVE_SAFELY 1.2f
#define OBJECT_WIDTH_TO_WEAVE 0.3f
#define PED_WIDTH_TO_WEAVE 0.8f

#define PATH_DIRECTION_NONE 0
#define PATH_DIRECTION_STRAIGHT 1
#define PATH_DIRECTION_RIGHT 2
#define PATH_DIRECTION_LEFT 4

#define ATTEMPTS_TO_FIND_NEXT_NODE 15

int &CCarCtrl::NumLawEnforcerCars = *(int*)0x8F1B38;
int &CCarCtrl::NumAmbulancesOnDuty = *(int*)0x885BB0;
int &CCarCtrl::NumFiretrucksOnDuty = *(int*)0x9411F0;
bool &CCarCtrl::bCarsGeneratedAroundCamera = *(bool*)0x95CD8A;
float& CCarCtrl::CarDensityMultiplier = *(float*)0x5EC8B4;
int32 &CCarCtrl::NumMissionCars = *(int32*)0x8F1B54;
int32 &CCarCtrl::NumRandomCars = *(int32*)0x943118;
int32 &CCarCtrl::NumParkedCars = *(int32*)0x8F29E0;
int8 &CCarCtrl::CountDownToCarsAtStart = *(int8*)0x95CD63;
int32 &CCarCtrl::MaxNumberOfCarsInUse = *(int32*)0x5EC8B8;
uint32 &CCarCtrl::LastTimeLawEnforcerCreated = *(uint32*)0x8F5FF0;
int32 (&CCarCtrl::TotalNumOfCarsOfRating)[7] = *(int32(*)[7])*(uintptr*)0x8F1A60;
int32 (&CCarCtrl::NextCarOfRating)[7] = *(int32(*)[7])*(uintptr*)0x9412AC;
int32 (&CCarCtrl::CarArrays)[7][MAX_CAR_MODELS_IN_ARRAY] = *(int32(*)[7][MAX_CAR_MODELS_IN_ARRAY])*(uintptr*)0x6EB860;
CVehicle* (&apCarsToKeep)[MAX_CARS_TO_KEEP] = *(CVehicle*(*)[MAX_CARS_TO_KEEP])*(uintptr*)0x70D830;
uint32 (&aCarsToKeepTime)[MAX_CARS_TO_KEEP] = *(uint32(*)[MAX_CARS_TO_KEEP])*(uintptr*)0x87F9A8;

WRAPPER void CCarCtrl::SwitchVehicleToRealPhysics(CVehicle*) { EAXJMP(0x41F7F0); }
WRAPPER void CCarCtrl::UpdateCarCount(CVehicle*, bool) { EAXJMP(0x4202E0); }
WRAPPER bool CCarCtrl::JoinCarWithRoadSystemGotoCoors(CVehicle*, CVector, bool) { EAXJMP(0x41FA00); }
WRAPPER void CCarCtrl::JoinCarWithRoadSystem(CVehicle*) { EAXJMP(0x41F820); }
WRAPPER void CCarCtrl::SteerAICarWithPhysics(CVehicle*) { EAXJMP(0x41DA60); }
WRAPPER void CCarCtrl::RemoveFromInterestingVehicleList(CVehicle* v) { EAXJMP(0x41F7A0); }
WRAPPER void CCarCtrl::GenerateEmergencyServicesCar(void) { EAXJMP(0x41FC50); }
WRAPPER void CCarCtrl::DragCarToPoint(CVehicle*, CVector*) { EAXJMP(0x41D450); }
WRAPPER void CCarCtrl::Init(void) { EAXJMP(0x41D280); }

void
CCarCtrl::GenerateRandomCars()
{
	if (CCutsceneMgr::IsCutsceneProcessing())
		return;
	if (NumRandomCars < 30){
		if (CountDownToCarsAtStart == 0){
			GenerateOneRandomCar();
		}
		else if (--CountDownToCarsAtStart == 0) {
			for (int i = 0; i < 50; i++)
				GenerateOneRandomCar();
			CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter = 20;
		}
	}
	/* Approximately once per 4 seconds. */
	if ((CTimer::GetTimeInMilliseconds() & 0xFFFFF000) != (CTimer::GetPreviousTimeInMilliseconds() & 0xFFFFF000))
		GenerateEmergencyServicesCar();
}

void
CCarCtrl::GenerateOneRandomCar()
{
	static int32 unk = 0;
	CPlayerInfo* pPlayer = &CWorld::Players[CWorld::PlayerInFocus];
	CVector vecTargetPos = FindPlayerCentreOfWorld(CWorld::PlayerInFocus);
	CVector2D vecPlayerSpeed = FindPlayerSpeed();
	CZoneInfo zone;
	CTheZones::GetZoneInfoForTimeOfDay(&vecTargetPos, &zone);
	pPlayer->m_nTrafficMultiplier = pPlayer->m_fRoadDensity * zone.carDensity;
	if (NumRandomCars >= pPlayer->m_nTrafficMultiplier * CarDensityMultiplier * CIniFile::CarNumberMultiplier)
		return;
	if (NumFiretrucksOnDuty + NumAmbulancesOnDuty + NumParkedCars + NumMissionCars + NumLawEnforcerCars + NumRandomCars >= MaxNumberOfCarsInUse)
		return;
	CWanted* pWanted = pPlayer->m_pPed->m_pWanted;
	int carClass;
	int carModel;
	if (pWanted->m_nWantedLevel > 1 && NumLawEnforcerCars < pWanted->m_MaximumLawEnforcerVehicles &&
		pWanted->m_CurrentCops < pWanted->m_MaxCops && (
			pWanted->m_nWantedLevel > 3 ||
			pWanted->m_nWantedLevel > 2 && CTimer::GetTimeInMilliseconds() > LastTimeLawEnforcerCreated + 5000 ||
			pWanted->m_nWantedLevel > 1 && CTimer::GetTimeInMilliseconds() > LastTimeLawEnforcerCreated + 8000)) {
		/* Last pWanted->m_nWantedLevel > 1 is unnecessary but I added it for better readability. */
		/* Wouldn't be surprised it was there originally but was optimized out. */
		carClass = COPS;
		carModel = ChoosePoliceCarModel();
	}else{
		carModel = ChooseModel(&zone, &vecTargetPos, &carClass);
		if (carClass == COPS && pWanted->m_nWantedLevel >= 1)
			/* All cop spawns with wanted level are handled by condition above. */
			/* In particular it means that cop cars never spawn if player has wanted level of 1. */
			return;
	}
	float frontX, frontY;
	float preferredDistance, angleLimit;
	bool invertAngleLimitTest;
	CVector spawnPosition;
	int32 curNodeId, nextNodeId;
	float positionBetweenNodes;
	bool testForCollision;
	CVehicle* pPlayerVehicle = FindPlayerVehicle();
	CVector2D vecPlayerVehicleSpeed;
	float fPlayerVehicleSpeed;
	if (pPlayerVehicle) {
		vecPlayerVehicleSpeed = FindPlayerVehicle()->GetMoveSpeed();
		fPlayerVehicleSpeed = vecPlayerVehicleSpeed.Magnitude();
	}
	if (TheCamera.GetForward().z < -0.9f){
		/* Player uses topdown camera. */
		/* Spawn essentially anywhere. */
		frontX = frontY = 0.707f; /* 45 degrees */
		angleLimit = -1.0f;
		invertAngleLimitTest = true;
		preferredDistance = 40.0f;
		/* BUG: testForCollision not initialized in original game. */
		testForCollision = false;
	}else if (!pPlayerVehicle){
		/* Player is not in vehicle. */
		testForCollision = true;
		frontX = TheCamera.CamFrontXNorm;
		frontY = TheCamera.CamFrontYNorm;
		switch (CTimer::GetFrameCounter() & 1) {
		case 0:
			/* Spawn a vehicle relatively far away from player. */
			/* Forward to his current direction (camera direction). */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = true;
			preferredDistance = 120.0f * TheCamera.GenerationDistMultiplier;
			break;
		case 1:
			/* Spawn a vehicle close to player to his side. */
			/* Kinda not within camera angle. */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = false;
			preferredDistance = 40.0f;
			break;
		}
	}else if (fPlayerVehicleSpeed > 0.4f){ /* 72 km/h */
		/* Player is moving fast in vehicle */
		/* Prefer spawning vehicles very far away from him. */
		frontX = vecPlayerVehicleSpeed.x / fPlayerVehicleSpeed;
		frontY = vecPlayerVehicleSpeed.y / fPlayerVehicleSpeed;
		testForCollision = false;
		switch (CTimer::GetFrameCounter() & 3) {
		case 0:
		case 1:
			/* Spawn a vehicle in a very narrow gap in front of a player */
			angleLimit = 0.85f; /* approx 30 degrees */
			invertAngleLimitTest = true;
			preferredDistance = 120.0f * TheCamera.GenerationDistMultiplier;
			break;
		case 2:
			/* Spawn a vehicle relatively far away from player. */
			/* Forward to his current direction (camera direction). */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = true;
			preferredDistance = 120.0f * TheCamera.GenerationDistMultiplier;
			break;
		case 3:
			/* Spawn a vehicle close to player to his side. */
			/* Kinda not within camera angle. */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = false;
			preferredDistance = 40.0f;
			break;
		}
	}else if (fPlayerVehicleSpeed > 0.1f){ /* 18 km/h */
		/* Player is moving moderately fast in vehicle */
		/* Spawn more vehicles to player's side. */
		frontX = vecPlayerVehicleSpeed.x / fPlayerVehicleSpeed;
		frontY = vecPlayerVehicleSpeed.y / fPlayerVehicleSpeed;
		testForCollision = false;
		switch (CTimer::GetFrameCounter() & 3) {
		case 0:
			/* Spawn a vehicle in a very narrow gap in front of a player */
			angleLimit = 0.85f; /* approx 30 degrees */
			invertAngleLimitTest = true;
			preferredDistance = 120.0f * TheCamera.GenerationDistMultiplier;
			break;
		case 1:
			/* Spawn a vehicle relatively far away from player. */
			/* Forward to his current direction (camera direction). */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = true;
			preferredDistance = 120.0f * TheCamera.GenerationDistMultiplier;
			break;
		case 2:
		case 3:
			/* Spawn a vehicle close to player to his side. */
			/* Kinda not within camera angle. */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = false;
			preferredDistance = 40.0f;
			break;
		}
	}else{
		/* Player is in vehicle but moving very slow. */
		/* Then use camera direction instead of vehicle direction. */
		testForCollision = true;
		frontX = TheCamera.CamFrontXNorm;
		frontY = TheCamera.CamFrontYNorm;
		switch (CTimer::GetFrameCounter() & 1) {
		case 0:
			/* Spawn a vehicle relatively far away from player. */
			/* Forward to his current direction (camera direction). */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = true;
			preferredDistance = 120.0f * TheCamera.GenerationDistMultiplier;
			break;
		case 1:
			/* Spawn a vehicle close to player to his side. */
			/* Kinda not within camera angle. */
			angleLimit = 0.707f; /* 45 degrees */
			invertAngleLimitTest = false;
			preferredDistance = 40.0f;
			break;
		}
	}
	if (!ThePaths.NewGenerateCarCreationCoors(vecTargetPos.x, vecTargetPos.y, frontX, frontY,
		preferredDistance, angleLimit, invertAngleLimitTest, &spawnPosition, &curNodeId, &nextNodeId,
		&positionBetweenNodes, carClass == COPS && pWanted->m_nWantedLevel >= 1))
		return;
	int16 colliding;
	CWorld::FindObjectsKindaColliding(spawnPosition, 10.0f, true, &colliding, 2, nil, false, true, true, false, false);
	if (colliding)
		/* If something is already present in spawn position, do not create vehicle*/
		return;
	if (!ThePaths.TestCoorsCloseness(vecTargetPos, false, spawnPosition))
		/* Testing if spawn position can reach target position via valid path. */
		return;
	int16 idInNode = 0;
	CPathNode* pCurNode = &ThePaths.m_pathNodes[curNodeId];
	CPathNode* pNextNode = &ThePaths.m_pathNodes[nextNodeId];
	while (idInNode < pCurNode->numLinks &&
		ThePaths.m_connections[idInNode + pCurNode->firstLink] != nextNodeId)
		idInNode++;
	int16 connectionId = ThePaths.m_carPathConnections[idInNode + pCurNode->firstLink];
	CCarPathLink* pPathLink = &ThePaths.m_carPathLinks[connectionId];
	int16 lanesOnCurrentRoad = pPathLink->pathNodeIndex == nextNodeId ? pPathLink->numLeftLanes : pPathLink->numRightLanes;
	CVehicleModelInfo* pModelInfo = (CVehicleModelInfo*)CModelInfo::GetModelInfo(carModel);
	if (lanesOnCurrentRoad == 0 || pModelInfo->m_vehicleType == VEHICLE_TYPE_BIKE)
		/* Not spawning vehicle if road is one way and intended direction is opposide to that way. */
		/* Also not spawning bikes but they don't exist in final game. */
		return;
	CAutomobile* pCar = new CAutomobile(carModel, RANDOM_VEHICLE);
	pCar->AutoPilot.m_nPrevRouteNode = 0;
	pCar->AutoPilot.m_nCurrentRouteNode = curNodeId;
	pCar->AutoPilot.m_nNextRouteNode = nextNodeId;
	switch (carClass) {
	case POOR:
	case RICH:
	case EXEC:
	case WORKER:
	case SPECIAL:
	case BIG:
	case TAXI:
	case MAFIA:
	case TRIAD:
	case DIABLO:
	case YAKUZA:
	case YARDIE:
	case COLOMB:
	case NINES:
	case GANG8:
	case GANG9:
	{
		pCar->AutoPilot.m_nCruiseSpeed = CGeneral::GetRandomNumberInRange(9, 14);
		if (carClass == EXEC)
			pCar->AutoPilot.m_nCruiseSpeed = CGeneral::GetRandomNumberInRange(12, 18);
		else if (carClass == POOR || carClass == SPECIAL)
			pCar->AutoPilot.m_nCruiseSpeed = CGeneral::GetRandomNumberInRange(7, 10);
		CVehicleModelInfo* pVehicleInfo = pCar->GetModelInfo();
		if (pVehicleInfo->GetColModel()->boundingBox.max.y - pCar->GetModelInfo()->GetColModel()->boundingBox.min.y > 10.0f || carClass == BIG) {
			pCar->AutoPilot.m_nCruiseSpeed *= 3;
			pCar->AutoPilot.m_nCruiseSpeed /= 4;
		}
		pCar->AutoPilot.m_fMaxTrafficSpeed = pCar->AutoPilot.m_nCruiseSpeed;
		pCar->AutoPilot.m_nCarMission = MISSION_CRUISE;
		pCar->AutoPilot.m_nTempAction = TEMPACT_NONE;
		pCar->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_STOP_FOR_CARS;
		break;
	}
	case COPS:
		pCar->AutoPilot.m_nTempAction = TEMPACT_NONE;
		if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pWanted->m_nWantedLevel != 0){
			pCar->AutoPilot.m_nCruiseSpeed = CCarAI::FindPoliceCarSpeedForWantedLevel(pCar);
			pCar->AutoPilot.m_fMaxTrafficSpeed = pCar->AutoPilot.m_nCruiseSpeed / 2;
			pCar->AutoPilot.m_nCarMission = CCarAI::FindPoliceCarMissionForWantedLevel();
			pCar->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
		}else{
			pCar->AutoPilot.m_nCruiseSpeed = CGeneral::GetRandomNumberInRange(12, 16);
			pCar->AutoPilot.m_fMaxTrafficSpeed = pCar->AutoPilot.m_nCruiseSpeed;
			pCar->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_STOP_FOR_CARS;
			pCar->AutoPilot.m_nCarMission = MISSION_CRUISE;
		}
		if (carModel == MI_FBICAR){
			pCar->m_currentColour1 = 0;
			pCar->m_currentColour2 = 0;
			/* FBI cars are gray in carcols, but we want them black if they going after player. */
		}
	default:
		break;
	}
	if (pCar && pCar->GetModelIndex() == MI_MRWHOOP)
		pCar->m_bSirenOrAlarm = true;
	pCar->AutoPilot.m_nNextPathNodeInfo = connectionId;
	pCar->AutoPilot.m_nNextLane = pCar->AutoPilot.m_nCurrentLane = CGeneral::GetRandomNumber() % lanesOnCurrentRoad;
	CColBox* boundingBox = &CModelInfo::GetModelInfo(pCar->GetModelIndex())->GetColModel()->boundingBox;
	float carLength = 1.0f + (boundingBox->max.y - boundingBox->min.y) / 2;
	float distanceBetweenNodes = (pCurNode->pos - pNextNode->pos).Magnitude2D();
	/* If car is so long that it doesn't fit between two car nodes, place it directly in the middle. */
	/* Otherwise put it at least in a way that full vehicle length fits between two nodes. */
	if (distanceBetweenNodes / 2 < carLength)
		positionBetweenNodes = 0.5f;
	else
		positionBetweenNodes = min(1.0f - carLength / distanceBetweenNodes, max(carLength / distanceBetweenNodes, positionBetweenNodes));
	pCar->AutoPilot.m_nNextDirection = (curNodeId >= nextNodeId) ? 1 : -1;
	if (pCurNode->numLinks == 1){
		/* Do not create vehicle if there is nowhere to go. */
		delete pCar;
		return;
	}
	int16 nextConnection = pCar->AutoPilot.m_nNextPathNodeInfo;
	int16 newLink;
	while (nextConnection == pCar->AutoPilot.m_nNextPathNodeInfo){
		newLink = CGeneral::GetRandomNumber() % pCurNode->numLinks;
		nextConnection = ThePaths.m_carPathConnections[newLink + pCurNode->firstLink];
	}
	pCar->AutoPilot.m_nCurrentPathNodeInfo = nextConnection;
	pCar->AutoPilot.m_nCurrentDirection = (ThePaths.m_connections[newLink + pCurNode->firstLink] >= curNodeId) ? 1 : -1;
	CVector2D vecBetweenNodes = pNextNode->pos - pCurNode->pos;
	float forwardX, forwardY;
	float distBetweenNodes = vecBetweenNodes.Magnitude();
	if (distanceBetweenNodes == 0.0f){
		forwardX = 1.0f;
		forwardY = 0.0f;
	}else{
		forwardX = vecBetweenNodes.x / distBetweenNodes;
		forwardY = vecBetweenNodes.y / distBetweenNodes;
	}
	/* I think the following might be some form of SetRotateZOnly. */
	/* Setting up direction between two car nodes. */
	pCar->GetForward() = CVector(forwardX, forwardY, 0.0f);
	pCar->GetRight() = CVector(forwardY, -forwardX, 0.0f);
	pCar->GetUp() = CVector(0.0f, 0.0f, 1.0f);

	float currentPathLinkForwardX = pCar->AutoPilot.m_nCurrentDirection * ThePaths.m_carPathLinks[pCar->AutoPilot.m_nCurrentPathNodeInfo].dirX;
	float currentPathLinkForwardY = pCar->AutoPilot.m_nCurrentDirection * ThePaths.m_carPathLinks[pCar->AutoPilot.m_nCurrentPathNodeInfo].dirY;
	float nextPathLinkForwardX = pCar->AutoPilot.m_nNextDirection * ThePaths.m_carPathLinks[pCar->AutoPilot.m_nNextPathNodeInfo].dirX;
	float nextPathLinkForwardY = pCar->AutoPilot.m_nNextDirection * ThePaths.m_carPathLinks[pCar->AutoPilot.m_nNextPathNodeInfo].dirY;

	CCarPathLink* pCurrentLink = &ThePaths.m_carPathLinks[pCar->AutoPilot.m_nCurrentPathNodeInfo];
	CCarPathLink* pNextLink = &ThePaths.m_carPathLinks[pCar->AutoPilot.m_nNextPathNodeInfo];
	CVector positionOnCurrentLinkIncludingLane(
		pCurrentLink->posX + GetOffsetOfLaneFromCenterOfRoad(pCar->AutoPilot.m_nCurrentLane, pCurrentLink) * currentPathLinkForwardY,
		pCurrentLink->posY - GetOffsetOfLaneFromCenterOfRoad(pCar->AutoPilot.m_nCurrentLane, pCurrentLink) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->posX + GetOffsetOfLaneFromCenterOfRoad(pCar->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardY,
		pNextLink->posY - GetOffsetOfLaneFromCenterOfRoad(pCar->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardX,
		0.0f);
	float directionCurrentLinkX = pCurrentLink->dirX * pCar->AutoPilot.m_nCurrentDirection;
	float directionCurrentLinkY = pCurrentLink->dirY * pCar->AutoPilot.m_nCurrentDirection;
	float directionNextLinkX = pNextLink->dirX * pCar->AutoPilot.m_nNextDirection;
	float directionNextLinkY = pNextLink->dirY * pCar->AutoPilot.m_nNextDirection;
	/* We want to make a path between two links that may not have the same forward directions a curve. */
	pCar->AutoPilot.m_nTimeToSpendOnCurrentCurve = CCurves::CalcSpeedScaleFactor(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		directionCurrentLinkX, directionCurrentLinkY,
		directionNextLinkX, directionNextLinkY
	) * (1000.0f / pCar->AutoPilot.m_fMaxTrafficSpeed);
#ifdef FIX_BUGS
	/* Casting timer to float is very unwanted. In this case it's not awful */
	/* but in CAutoPilot::ModifySpeed it can even cause crashes (see SilentPatch). */
	pCar->AutoPilot.m_nTimeEnteredCurve = CTimer::GetTimeInMilliseconds() -
		(uint32)((0.5f + positionBetweenNodes) * pCar->AutoPilot.m_nTimeToSpendOnCurrentCurve);
#else
	pCar->AutoPilot.m_nTotalSpeedScaleFactor = CTimer::GetTimeInMilliseconds() -
		(0.5f + positionBetweenNodes) * pCar->AutoPilot.m_nSpeedScaleFactor;
#endif
	CVector directionCurrentLink(directionCurrentLinkX, directionCurrentLinkY, 0.0f);
	CVector directionNextLink(directionNextLinkX, directionNextLinkY, 0.0f);
	CVector positionIncludingCurve;
	CVector directionIncludingCurve;
	CCurves::CalcCurvePoint(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		&directionCurrentLink,
		&directionNextLink,
		GetPositionAlongCurrentCurve(pCar),
		pCar->AutoPilot.m_nTimeToSpendOnCurrentCurve,
		&positionIncludingCurve,
		&directionIncludingCurve
	);
	CVector vectorBetweenNodes = pCurNode->pos - pNextNode->pos;
	CVector finalPosition = positionIncludingCurve + vectorBetweenNodes * 2.0f / vectorBetweenNodes.Magnitude();
	finalPosition.z = positionBetweenNodes * pNextNode->pos.z +
		(1.0f - positionBetweenNodes) * pCurNode->pos.z;
	float groundZ = INFINITE_Z;
	CColPoint colPoint;
	CEntity* pEntity;
	if (CWorld::ProcessVerticalLine(finalPosition, 1000.0f, colPoint, pEntity, true, false, false, false, true, false, nil))
		groundZ = colPoint.point.z;
	if (CWorld::ProcessVerticalLine(finalPosition, -1000.0f, colPoint, pEntity, true, false, false, false, true, false, nil)){
		if (ABS(colPoint.point.z - finalPosition.z) < ABS(groundZ - finalPosition.z))
			groundZ = colPoint.point.z;
	}
	if (groundZ == INFINITE_Z || ABS(groundZ - finalPosition.z) > 7.0f) {
		/* Failed to find ground or too far from expected position. */
		delete pCar;
		return;
	}
	finalPosition.z = groundZ + pCar->GetHeightAboveRoad();
	pCar->GetPosition() = finalPosition;
	pCar->SetMoveSpeed(directionIncludingCurve / GAME_SPEED_TO_CARAI_SPEED);
	CVector2D speedDifferenceWithTarget = (CVector2D)pCar->GetMoveSpeed() - vecPlayerSpeed;
	CVector2D distanceToTarget = positionIncludingCurve - vecTargetPos;
	switch (carClass) {
	case POOR:
	case RICH:
	case EXEC:
	case WORKER:
	case SPECIAL:
	case BIG:
	case TAXI:
	case MAFIA:
	case TRIAD:
	case DIABLO:
	case YAKUZA:
	case YARDIE:
	case COLOMB:
	case NINES:
	case GANG8:
	case GANG9:
		pCar->m_status = STATUS_SIMPLE;
		break;
	case COPS:
		pCar->m_status = (pCar->AutoPilot.m_nCarMission == MISSION_CRUISE) ? STATUS_SIMPLE : STATUS_PHYSICS;
		pCar->ChangeLawEnforcerState(1);
		break;
	default:
		break;
	}
	CVisibilityPlugins::SetClumpAlpha(pCar->GetClump(), 0);
	if (!pCar->GetIsOnScreen()){
		if ((vecTargetPos - pCar->GetPosition()).Magnitude2D() > 50.0f) {
			/* Too far away cars that are not visible aren't needed. */
			delete pCar;
			return;
		}
	}else if((vecTargetPos - pCar->GetPosition()).Magnitude2D() > TheCamera.GenerationDistMultiplier * 130.0f ||
		(vecTargetPos - pCar->GetPosition()).Magnitude2D() < TheCamera.GenerationDistMultiplier * 110.0f){
		delete pCar;
		return;
	}else if((TheCamera.GetPosition() - pCar->GetPosition()).Magnitude2D() < 90.0f * TheCamera.GenerationDistMultiplier){
		delete pCar;
		return;
	}
	CVehicleModelInfo* pVehicleModel = pCar->GetModelInfo();
	float radiusToTest = pVehicleModel->GetColModel()->boundingSphere.radius;
	if (testForCollision){
		CWorld::FindObjectsKindaColliding(pCar->GetPosition(), radiusToTest + 20.0f, true, &colliding, 2, nil, false, true, false, false, false);
		if (colliding){
			delete pCar;
			return;
		}
	}
	CWorld::FindObjectsKindaColliding(pCar->GetPosition(), radiusToTest, true, &colliding, 2, nil, false, true, false, false, false);
	if (colliding){
		delete pCar;
		return;
	}
	if (speedDifferenceWithTarget.x * distanceToTarget.x +
		speedDifferenceWithTarget.y * distanceToTarget.y >= 0.0f){
		delete pCar;
		return;
	}
	pVehicleModel->AvoidSameVehicleColour(&pCar->m_currentColour1, &pCar->m_currentColour2);
	CWorld::Add(pCar);
	if (carClass == COPS)
		CCarAI::AddPoliceOccupants(pCar);
	else
		pCar->SetUpDriver();
	if ((CGeneral::GetRandomNumber() & 0x3F) == 0){ /* 1/64 probability */
		pCar->m_status = STATUS_PHYSICS;
		pCar->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
		pCar->AutoPilot.m_nCruiseSpeed += 10;
	}
	if (carClass == COPS)
		LastTimeLawEnforcerCreated = CTimer::GetTimeInMilliseconds();
}

int32
CCarCtrl::ChooseModel(CZoneInfo* pZone, CVector* pPos, int* pClass) {
	int32 model = -1;;
	while (model == -1 || !CStreaming::HasModelLoaded(model)){
		int rnd = CGeneral::GetRandomNumberInRange(0, 1000);
		if (rnd < pZone->carThreshold[0])
			model = CCarCtrl::ChooseCarModel((*pClass = POOR));
		else if (rnd < pZone->carThreshold[1])
			model = CCarCtrl::ChooseCarModel((*pClass = RICH));
		else if (rnd < pZone->carThreshold[2])
			model = CCarCtrl::ChooseCarModel((*pClass = EXEC));
		else if (rnd < pZone->carThreshold[3])
			model = CCarCtrl::ChooseCarModel((*pClass = WORKER));
		else if (rnd < pZone->carThreshold[4])
			model = CCarCtrl::ChooseCarModel((*pClass = SPECIAL));
		else if (rnd < pZone->carThreshold[5])
			model = CCarCtrl::ChooseCarModel((*pClass = BIG));
		else if (rnd < pZone->copThreshold)
			*pClass = COPS, model = CCarCtrl::ChoosePoliceCarModel();
		else if (rnd < pZone->gangThreshold[0])
			model = CCarCtrl::ChooseGangCarModel((*pClass = MAFIA) - MAFIA);
		else if (rnd < pZone->gangThreshold[1])
			model = CCarCtrl::ChooseGangCarModel((*pClass = TRIAD) - MAFIA);
		else if (rnd < pZone->gangThreshold[2])
			model = CCarCtrl::ChooseGangCarModel((*pClass = DIABLO) - MAFIA);
		else if (rnd < pZone->gangThreshold[3])
			model = CCarCtrl::ChooseGangCarModel((*pClass = YAKUZA) - MAFIA);
		else if (rnd < pZone->gangThreshold[4])
			model = CCarCtrl::ChooseGangCarModel((*pClass = YARDIE) - MAFIA);
		else if (rnd < pZone->gangThreshold[5])
			model = CCarCtrl::ChooseGangCarModel((*pClass = COLOMB) - MAFIA);
		else if (rnd < pZone->gangThreshold[6])
			model = CCarCtrl::ChooseGangCarModel((*pClass = NINES) - MAFIA);
		else if (rnd < pZone->gangThreshold[7])
			model = CCarCtrl::ChooseGangCarModel((*pClass = GANG8) - MAFIA);
		else if (rnd < pZone->gangThreshold[8])
			model = CCarCtrl::ChooseGangCarModel((*pClass = GANG9) - MAFIA);
		else
			model = CCarCtrl::ChooseCarModel((*pClass = TAXI));
	}
	return model;
}

int32
CCarCtrl::ChooseCarModel(int32 vehclass)
{
	int32 model = -1;
	switch (vehclass) {
	case POOR:
	case RICH:
	case EXEC:
	case WORKER:
	case SPECIAL:
	case BIG:
	case TAXI:
	{
		if (TotalNumOfCarsOfRating[vehclass] == 0)
			debug("ChooseCarModel : No cars of type %d have been declared\n");
		model = CarArrays[vehclass][NextCarOfRating[vehclass]];
		int32 total = TotalNumOfCarsOfRating[vehclass];
		NextCarOfRating[vehclass] += 1 + CGeneral::GetRandomNumberInRange(0, total - 1);
		while (NextCarOfRating[vehclass] >= total)
			NextCarOfRating[vehclass] -= total;
		//NextCarOfRating[vehclass] %= total;
		TotalNumOfCarsOfRating[vehclass] = total; /* why... */
	}
	default:
		break;
	}
	return model;
}

int32
CCarCtrl::ChoosePoliceCarModel(void)
{
	if (FindPlayerPed()->m_pWanted->AreSwatRequired() &&
		CStreaming::HasModelLoaded(MI_ENFORCER) &&
		CStreaming::HasModelLoaded(MI_POLICE))
		return ((CGeneral::GetRandomNumber() & 0xF) == 0) ? MI_ENFORCER : MI_POLICE;
	if (FindPlayerPed()->m_pWanted->AreFbiRequired() &&
		CStreaming::HasModelLoaded(MI_FBICAR) &&
		CStreaming::HasModelLoaded(MI_FBI))
		return MI_FBICAR;
	if (FindPlayerPed()->m_pWanted->AreArmyRequired() &&
		CStreaming::HasModelLoaded(MI_RHINO) &&
		CStreaming::HasModelLoaded(MI_BARRACKS) &&
		CStreaming::HasModelLoaded(MI_RHINO))
		return CGeneral::GetRandomTrueFalse() ? MI_BARRACKS : MI_RHINO;
	return MI_POLICE;
}

int32
CCarCtrl::ChooseGangCarModel(int32 gang)
{
	if (CStreaming::HasModelLoaded(MI_GANG01 + 2 * gang) &&
		CStreaming::HasModelLoaded(MI_GANG02 + 2 * gang))
		return CGangs::GetGangVehicleModel(gang);
	return -1;
}

void
CCarCtrl::AddToCarArray(int32 id, int32 vehclass)
{
	CarArrays[vehclass][TotalNumOfCarsOfRating[vehclass]++] = id;
}

void
CCarCtrl::RemoveDistantCars()
{
	uint32 i = CPools::GetVehiclePool()->GetSize();
	while (--i){
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle)
			continue;
		PossiblyRemoveVehicle(pVehicle);
		if (pVehicle->bCreateRoadBlockPeds){
			if ((pVehicle->GetPosition() - FindPlayerCentreOfWorld(CWorld::PlayerInFocus)).Magnitude2D() < DISTANCE_TO_SPAWN_ROADBLOCK_PEDS) {
				CRoadBlocks::GenerateRoadBlockCopsForCar(pVehicle, pVehicle->m_nRoadblockType, pVehicle->m_nRoadblockNode);
				pVehicle->bCreateRoadBlockPeds = false;
			}
		}
	}
}

void
CCarCtrl::PossiblyRemoveVehicle(CVehicle* pVehicle)
{
	CVector vecPlayerPos = FindPlayerCentreOfWorld(CWorld::PlayerInFocus);
	/* BUG: this variable is initialized only in if-block below but can be used outside of it. */
	if (!IsThisVehicleInteresting(pVehicle) && !pVehicle->bIsLocked &&
		pVehicle->CanBeDeleted() && !CCranes::IsThisCarBeingTargettedByAnyCrane(pVehicle)){
		if (pVehicle->bFadeOut && CVisibilityPlugins::GetClumpAlpha(pVehicle->GetClump()) == 0){
			CWorld::Remove(pVehicle);
			delete pVehicle;
			return;
		}
		float distanceToPlayer = (pVehicle->GetPosition() - vecPlayerPos).Magnitude2D();
		float threshold = 50.0f;
		if (pVehicle->GetIsOnScreen() ||
			TheCamera.Cams[TheCamera.ActiveCam].LookingLeft ||
			TheCamera.Cams[TheCamera.ActiveCam].LookingRight ||
			TheCamera.Cams[TheCamera.ActiveCam].LookingBehind ||
			TheCamera.GetLookDirection() == 0 ||
			pVehicle->VehicleCreatedBy == PARKED_VEHICLE ||
			pVehicle->GetModelIndex() == MI_AMBULAN ||
			pVehicle->GetModelIndex() == MI_FIRETRUCK ||
			pVehicle->bIsLawEnforcer ||
			pVehicle->bIsCarParkVehicle
			){
			threshold = 130.0f * TheCamera.GenerationDistMultiplier;
		}
		if (pVehicle->bExtendedRange)
			threshold *= 1.5f;
		if (distanceToPlayer > threshold && !CGarages::IsPointWithinHideOutGarage(&pVehicle->GetPosition())){
			if (pVehicle->GetIsOnScreen() && CRenderer::IsEntityCullZoneVisible(pVehicle)){
				pVehicle->bFadeOut = true;
			}else{
				CWorld::Remove(pVehicle);
				delete pVehicle;
			}
			return;
		}
	}
	if ((pVehicle->m_status == STATUS_SIMPLE || pVehicle->m_status == STATUS_PHYSICS && pVehicle->AutoPilot.m_nDrivingStyle == DRIVINGSTYLE_STOP_FOR_CARS) &&
		CTimer::GetTimeInMilliseconds() - pVehicle->AutoPilot.m_nTimeToStartMission > 5000 &&
		!pVehicle->GetIsOnScreen() &&
		(pVehicle->GetPosition() - vecPlayerPos).Magnitude2D() > 25.0f &&
		!IsThisVehicleInteresting(pVehicle) &&
		!pVehicle->bIsLocked &&
		!CTrafficLights::ShouldCarStopForLight(pVehicle, true) &&
		!CTrafficLights::ShouldCarStopForBridge(pVehicle) &&
		!CGarages::IsPointWithinHideOutGarage(&pVehicle->GetPosition())){
		CWorld::Remove(pVehicle);
		delete pVehicle;
		return;
	}
	if (pVehicle->m_status != STATUS_WRECKED || pVehicle->m_nTimeOfDeath == 0)
		return;
	if (CTimer::GetTimeInMilliseconds() > pVehicle->m_nTimeOfDeath + 60000 &&
		(!pVehicle->GetIsOnScreen() || !CRenderer::IsEntityCullZoneVisible(pVehicle))){
		if ((pVehicle->GetPosition() - vecPlayerPos).MagnitudeSqr() > SQR(7.5f)){
			if (!CGarages::IsPointWithinHideOutGarage(&pVehicle->GetPosition())){
				CWorld::Remove(pVehicle);
				delete pVehicle;
			}
		}
	}
}

int32
CCarCtrl::CountCarsOfType(int32 mi)
{
	int32 total = 0;
	uint32 i = CPools::GetVehiclePool()->GetSize();
	while (i--){
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle)
			continue;
		if (pVehicle->GetModelIndex() == mi)
			total++;
	}
	return total;
}

bool
CCarCtrl::IsThisVehicleInteresting(CVehicle* pVehicle)
{
	for (int i = 0; i < MAX_CARS_TO_KEEP; i++) {
		if (apCarsToKeep[i] == pVehicle)
			return true;
	}
	return false;
}

void
CCarCtrl::RegisterVehicleOfInterest(CVehicle* pVehicle)
{
	for(int i = 0; i < MAX_CARS_TO_KEEP; i++) {
		if (apCarsToKeep[i] == pVehicle) {
			aCarsToKeepTime[i] = CTimer::GetTimeInMilliseconds();
			return;
		}
	}
	for (int i = 0; i < MAX_CARS_TO_KEEP; i++) {
		if (!apCarsToKeep[i]) {
			apCarsToKeep[i] = pVehicle;
			aCarsToKeepTime[i] = CTimer::GetTimeInMilliseconds();
			return;
		}
	}
	uint32 oldestCarWeKeepTime = UINT_MAX;
	int oldestCarWeKeepIndex = 0;
	for (int i = 0; i < MAX_CARS_TO_KEEP; i++) {
		if (apCarsToKeep[i] && aCarsToKeepTime[i] < oldestCarWeKeepTime) {
			oldestCarWeKeepTime = aCarsToKeepTime[i];
			oldestCarWeKeepIndex = i;
		}
	}
	apCarsToKeep[oldestCarWeKeepIndex] = pVehicle;
	aCarsToKeepTime[oldestCarWeKeepIndex] = CTimer::GetTimeInMilliseconds();
}

void
CCarCtrl::UpdateCarOnRails(CVehicle* pVehicle)
{
	if (pVehicle->AutoPilot.m_nTempAction == TEMPACT_WAIT){
		pVehicle->SetMoveSpeed(0.0f, 0.0f, 0.0f);
		pVehicle->AutoPilot.ModifySpeed(0.0f);
		if (CTimer::GetTimeInMilliseconds() > pVehicle->AutoPilot.m_nTempAction){
			pVehicle->AutoPilot.m_nTempAction = TEMPACT_NONE;
			pVehicle->AutoPilot.m_nAntiReverseTimer = 0;
			pVehicle->AutoPilot.m_nTimeToStartMission = 0;
		}
		return;
	}
	SlowCarOnRailsDownForTrafficAndLights(pVehicle);
	if (pVehicle->AutoPilot.m_nTimeEnteredCurve + pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve <= CTimer::GetTimeInMilliseconds())
		PickNextNodeAccordingStrategy(pVehicle);
	if (pVehicle->m_status == STATUS_PHYSICS)
		return;
	CCarPathLink* pCurrentLink = &ThePaths.m_carPathLinks[pVehicle->AutoPilot.m_nCurrentPathNodeInfo];
	CCarPathLink* pNextLink = &ThePaths.m_carPathLinks[pVehicle->AutoPilot.m_nNextPathNodeInfo];
	float currentPathLinkForwardX = pCurrentLink->dirX * pVehicle->AutoPilot.m_nCurrentDirection;
	float currentPathLinkForwardY = pCurrentLink->dirY * pVehicle->AutoPilot.m_nCurrentDirection;
	float nextPathLinkForwardX = pNextLink->dirX * pVehicle->AutoPilot.m_nNextDirection;
	float nextPathLinkForwardY = pNextLink->dirY * pVehicle->AutoPilot.m_nNextDirection;
	CVector positionOnCurrentLinkIncludingLane(
		pCurrentLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurrentLink) * currentPathLinkForwardY,
		pCurrentLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurrentLink) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardY,
		pNextLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardX,
		0.0f);
	CVector directionCurrentLink(currentPathLinkForwardX, currentPathLinkForwardY, 0.0f);
	CVector directionNextLink(nextPathLinkForwardX, nextPathLinkForwardY, 0.0f);
	CVector positionIncludingCurve;
	CVector directionIncludingCurve;
	CCurves::CalcCurvePoint(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		&directionCurrentLink,
		&directionNextLink,
		GetPositionAlongCurrentCurve(pVehicle),
		pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve,
		&positionIncludingCurve,
		&directionIncludingCurve
	);
	positionIncludingCurve.z = 15.0f;
	DragCarToPoint(pVehicle, &positionIncludingCurve);
	pVehicle->SetMoveSpeed(directionIncludingCurve / GAME_SPEED_TO_CARAI_SPEED);
}

float
CCarCtrl::FindMaximumSpeedForThisCarInTraffic(CVehicle* pVehicle)
{
	if (pVehicle->AutoPilot.m_nCarMission == MISSION_RAMPLAYER_FARAWAY ||
		pVehicle->AutoPilot.m_nCarMission == MISSION_RAMPLAYER_CLOSE)
		return pVehicle->AutoPilot.m_nCruiseSpeed;
	float left = pVehicle->GetPosition().x - DISTANCE_TO_SCAN_FOR_DANGER;
	float right = pVehicle->GetPosition().x + DISTANCE_TO_SCAN_FOR_DANGER;
	float top = pVehicle->GetPosition().y - DISTANCE_TO_SCAN_FOR_DANGER;
	float bottom = pVehicle->GetPosition().y + DISTANCE_TO_SCAN_FOR_DANGER;
	int xstart = max(0, CWorld::GetSectorIndexX(left));
	int xend = min(NUMSECTORS_X - 1, CWorld::GetSectorIndexX(right));
	int ystart = max(0, CWorld::GetSectorIndexY(top));
	int yend = min(NUMSECTORS_Y - 1, CWorld::GetSectorIndexY(bottom));
	assert(xstart <= xend);
	assert(ystart <= yend);

	float maxSpeed = pVehicle->AutoPilot.m_nCruiseSpeed;

	CWorld::AdvanceCurrentScanCode();

	for (int y = ystart; y <= yend; y++){
		for (int x = xstart; x <= xend; x++){
			CSector* s = CWorld::GetSector(x, y);
			SlowCarDownForCarsSectorList(s->m_lists[ENTITYLIST_VEHICLES], pVehicle, left, top, right, bottom, &maxSpeed, pVehicle->AutoPilot.m_nCruiseSpeed);
			SlowCarDownForCarsSectorList(s->m_lists[ENTITYLIST_VEHICLES_OVERLAP], pVehicle, left, top, right, bottom, &maxSpeed, pVehicle->AutoPilot.m_nCruiseSpeed);
			SlowCarDownForPedsSectorList(s->m_lists[ENTITYLIST_PEDS], pVehicle, left, top, right, bottom, &maxSpeed, pVehicle->AutoPilot.m_nCruiseSpeed);
			SlowCarDownForPedsSectorList(s->m_lists[ENTITYLIST_PEDS_OVERLAP], pVehicle, left, top, right, bottom, &maxSpeed, pVehicle->AutoPilot.m_nCruiseSpeed);
		}
	}
	pVehicle->bWarnedPeds = true;
	if (pVehicle->AutoPilot.m_nDrivingStyle == DRIVINGSTYLE_STOP_FOR_CARS)
		return maxSpeed;
	return (maxSpeed + pVehicle->AutoPilot.m_nDrivingStyle) / 2;
}

void
CCarCtrl::ScanForPedDanger(CVehicle* pVehicle)
{
	bool storedSlowDownFlag = pVehicle->AutoPilot.m_bSlowedDownBecauseOfPeds;
	float left = pVehicle->GetPosition().x - DISTANCE_TO_SCAN_FOR_DANGER;
	float right = pVehicle->GetPosition().x + DISTANCE_TO_SCAN_FOR_DANGER;
	float top = pVehicle->GetPosition().y - DISTANCE_TO_SCAN_FOR_DANGER;
	float bottom = pVehicle->GetPosition().y + DISTANCE_TO_SCAN_FOR_DANGER;
	int xstart = max(0, CWorld::GetSectorIndexX(left));
	int xend = min(NUMSECTORS_X - 1, CWorld::GetSectorIndexX(right));
	int ystart = max(0, CWorld::GetSectorIndexY(top));
	int yend = min(NUMSECTORS_Y - 1, CWorld::GetSectorIndexY(bottom));
	assert(xstart <= xend);
	assert(ystart <= yend);

	float maxSpeed = pVehicle->AutoPilot.m_nCruiseSpeed;

	CWorld::AdvanceCurrentScanCode();

	for (int y = ystart; y <= yend; y++) {
		for (int x = xstart; x <= xend; x++) {
			CSector* s = CWorld::GetSector(x, y);
			SlowCarDownForPedsSectorList(s->m_lists[ENTITYLIST_PEDS], pVehicle, left, top, right, bottom, &maxSpeed, pVehicle->AutoPilot.m_nCruiseSpeed);
			SlowCarDownForPedsSectorList(s->m_lists[ENTITYLIST_PEDS_OVERLAP], pVehicle, left, top, right, bottom, &maxSpeed, pVehicle->AutoPilot.m_nCruiseSpeed);
		}
	}
	pVehicle->bWarnedPeds = true;
	pVehicle->AutoPilot.m_bSlowedDownBecauseOfPeds = storedSlowDownFlag;
}

void
CCarCtrl::SlowCarOnRailsDownForTrafficAndLights(CVehicle* pVehicle)
{
	float maxSpeed;
	if (CTrafficLights::ShouldCarStopForLight(pVehicle, false) || CTrafficLights::ShouldCarStopForBridge(pVehicle)){
		CCarAI::CarHasReasonToStop(pVehicle);
		maxSpeed = 0.0f;
	}else{
		maxSpeed = FindMaximumSpeedForThisCarInTraffic(pVehicle);
	}
	float curSpeed = pVehicle->AutoPilot.m_fMaxTrafficSpeed;
	if (maxSpeed >= curSpeed){
		if (maxSpeed > curSpeed)
			pVehicle->AutoPilot.ModifySpeed(min(maxSpeed, curSpeed + 0.05f * CTimer::GetTimeStep()));
	}else{
		if (curSpeed == 0.0f)
			return;
		if (curSpeed >= 0.1f)
			pVehicle->AutoPilot.ModifySpeed(max(maxSpeed, curSpeed - 0.5f * CTimer::GetTimeStep()));
		else if (curSpeed != 0.0f) /* no need to check */
			pVehicle->AutoPilot.ModifySpeed(0.0f);
	}
}
#if 0
WRAPPER void CCarCtrl::SlowCarDownForPedsSectorList(CPtrList&, CVehicle*, float, float, float, float, float*, float) { EAXJMP(0x419300); }
#else
void CCarCtrl::SlowCarDownForPedsSectorList(CPtrList& lst, CVehicle* pVehicle, float x_inf, float y_inf, float x_sup, float y_sup, float* pSpeed, float curSpeed)
{
	float frontOffset = pVehicle->GetModelInfo()->GetColModel()->boundingBox.max.y;
	float frontSafe = frontOffset + SAFE_DISTANCE_TO_PED;
	for (CPtrNode* pNode = lst.first; pNode != nil; pNode = pNode->next){
		CPed* pPed = (CPed*)pNode->item;
		if (pPed->m_scanCode == CWorld::GetCurrentScanCode())
			continue;
		if (!pPed->bUsesCollision)
			continue;
		pPed->m_scanCode = CWorld::GetCurrentScanCode();
		CVector vecPedPos = pPed->GetPosition();
		if (vecPedPos.x < x_inf || vecPedPos.x > x_sup)
			continue;
		if (vecPedPos.y < y_inf || vecPedPos.y > y_sup)
			continue;
		if (ABS(vecPedPos.z - pVehicle->GetPosition().z) >= 4.0f)
			continue;
		CVector vecToPed = vecPedPos - pVehicle->GetPosition();
		float dotDirection = DotProduct(pVehicle->GetForward(), vecToPed);
		float dotVelocity = DotProduct(pVehicle->GetForward(), pVehicle->GetMoveSpeed());
		if (dotDirection <= frontOffset) /* If already run him over, don't care */
			continue;
		float distanceUntilHit = dotDirection - frontOffset;
		float movementTowardsPedPerSecond = GAME_SPEED_TO_METERS_PER_SECOND * dotVelocity;
		if (4 * movementTowardsPedPerSecond <= distanceUntilHit)
			/* If car isn't projected to hit a ped in 4 seconds, don't care */
			continue;
		float sidewaysDistance = ABS(DotProduct(pVehicle->GetRight(), vecToPed));
		float sideLength = pVehicle->GetModelInfo()->GetColModel()->boundingBox.max.x;
		if (pVehicle->m_vehType == VEHICLE_TYPE_BIKE)
			sideLength *= 1.6f;
		if (sideLength + 0.5f < sidewaysDistance)
			/* If car is far enough taking side into account, don't care */
			continue;
		if (pPed->m_type == ENTITY_TYPE_PED){ /* ...how can it not be? */
			if (pPed->GetPedState() != PED_STEP_AWAY && pPed->GetPedState() != PED_DIVE_AWAY){
				if (distanceUntilHit < movementTowardsPedPerSecond){
					/* Very close. Time to evade. */
					if (pVehicle->GetModelIndex() == MI_RCBANDIT){
						if (dotVelocity * GAME_SPEED_TO_METERS_PER_SECOND / 2 > distanceUntilHit)
							pPed->SetEvasiveStep(pVehicle, 0);
					}else if (dotVelocity > 0.3f){
						if (sideLength - 0.5f < sidewaysDistance)
							pPed->SetEvasiveStep(pVehicle, 0);
						else
							pPed->SetEvasiveDive(pVehicle, 0);
					}else{
						if (sideLength + 0.1f < sidewaysDistance)
							pPed->SetEvasiveStep(pVehicle, 0);
						else
							pPed->SetEvasiveDive(pVehicle, 0);
					}
				}else{
					/* Relatively safe but annoying. */
					if (pVehicle->m_status == STATUS_PLAYER &&
					  pPed->GetPedState() != PED_FLEE_ENTITY &&
					  pPed->CharCreatedBy == RANDOM_CHAR){
						float angleCarToPed = CGeneral::GetRadianAngleBetweenPoints(
							pVehicle->GetPosition().x, pVehicle->GetPosition().y,
							pPed->GetPosition().x, pPed->GetPosition().y
						);
						angleCarToPed = CGeneral::LimitRadianAngle(angleCarToPed);
						pPed->m_headingRate = CGeneral::LimitRadianAngle(pPed->m_headingRate);
						float visibilityAngle = ABS(angleCarToPed - pPed->m_headingRate);
						if (visibilityAngle > PI)
							visibilityAngle = TWOPI - visibilityAngle;
						if (visibilityAngle < HALFPI || pVehicle->m_nCarHornTimer){
							/* if ped sees the danger of if car horn is on */
							pPed->SetFlee(pVehicle, 2000);
							pPed->bUsePedNodeSeek = false;
							pPed->SetMoveState(PEDMOVE_RUN);
						}
					}else{
						CPlayerPed* pPlayerPed = (CPlayerPed*)pPed;
						if (pPlayerPed->IsPlayer() && dotDirection < frontSafe &&
						  pPlayerPed->IsPedInControl() &&
						  pPlayerPed->m_fMoveSpeed < 0.1f && pPlayerPed->bIsLooking &&
						  CTimer::GetTimeInMilliseconds() > pPlayerPed->m_lookTimer) {
							pPlayerPed->AnnoyPlayerPed(false);
							pPlayerPed->SetLookFlag(pVehicle, true);
							pPlayerPed->SetLookTimer(1500);
							if (pPlayerPed->GetWeapon()->m_eWeaponType == WEAPONTYPE_UNARMED ||
								pPlayerPed->GetWeapon()->m_eWeaponType == WEAPONTYPE_BASEBALLBAT ||
								pPlayerPed->GetWeapon()->m_eWeaponType == WEAPONTYPE_COLT45 ||
								pPlayerPed->GetWeapon()->m_eWeaponType == WEAPONTYPE_UZI) {
								pPlayerPed->bShakeFist = true;
							}
						}
					}
				}
			}
		}
		/* Ped stuff done. Now vehicle stuff. */
		if (distanceUntilHit < 10.0f){
			if (pVehicle->AutoPilot.m_nDrivingStyle == DRIVINGSTYLE_STOP_FOR_CARS ||
			  pVehicle->AutoPilot.m_nDrivingStyle == DRIVINGSTYLE_SLOW_DOWN_FOR_CARS){
				*pSpeed = min(*pSpeed, ABS(distanceUntilHit - 1.0f) * 0.1f * curSpeed);
				pVehicle->AutoPilot.m_bSlowedDownBecauseOfPeds = true;
				if (distanceUntilHit < 2.0f){
					pVehicle->AutoPilot.m_nTempAction = TEMPACT_WAIT;
					pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 3000;
				}
			}
		}
	}
}
#endif

void CCarCtrl::SlowCarDownForCarsSectorList(CPtrList& lst, CVehicle* pVehicle, float x_inf, float y_inf, float x_sup, float y_sup, float* pSpeed, float curSpeed)
{
	for (CPtrNode* pNode = lst.first; pNode != nil; pNode = pNode->next){
		CVehicle* pTestVehicle = (CVehicle*)pNode->item;
		if (pVehicle == pTestVehicle)
			continue;
		if (pTestVehicle->m_scanCode == CWorld::GetCurrentScanCode())
			continue;
		if (!pTestVehicle->bUsesCollision)
			continue;
		pTestVehicle->m_scanCode = CWorld::GetCurrentScanCode();
		CVector boundCenter = pTestVehicle->GetBoundCentre();
		if (boundCenter.x < x_inf || boundCenter.x > x_sup)
			continue;
		if (boundCenter.y < y_inf || boundCenter.y > y_sup)
			continue;
		if (Abs(boundCenter.z - pVehicle->GetPosition().z) < 5.0f)
			SlowCarDownForOtherCar(pTestVehicle, pVehicle, pSpeed, curSpeed);
	}
}

void CCarCtrl::SlowCarDownForOtherCar(CEntity* pOtherEntity, CVehicle* pVehicle, float* pSpeed, float curSpeed)
{
	CVector forwardA = pVehicle->GetForward();
	((CVector2D)forwardA).Normalise();
	if (DotProduct2D(pOtherEntity->GetPosition() - pVehicle->GetPosition(), forwardA) < 0.0f)
		return;
	CVector forwardB = pOtherEntity->GetForward();
	((CVector2D)forwardB).Normalise();
	forwardA.z = forwardB.z = 0.0f;
	CVehicle* pOtherVehicle = (CVehicle*)pOtherEntity;
	/* why is the argument CEntity if it's always CVehicle anyway and is casted? */
	float speedOtherX = GAME_SPEED_TO_CARAI_SPEED * pOtherVehicle->GetMoveSpeed().x;
	float speedOtherY = GAME_SPEED_TO_CARAI_SPEED * pOtherVehicle->GetMoveSpeed().y;
	float projectionX = speedOtherX - forwardA.x * curSpeed;
	float projectionY = speedOtherY - forwardA.y * curSpeed;
	float proximityA = TestCollisionBetween2MovingRects(pOtherVehicle, pVehicle, projectionX, projectionY, &forwardA, &forwardB, 0);
	float proximityB = TestCollisionBetween2MovingRects(pVehicle, pOtherVehicle, -projectionX, -projectionY, &forwardB, &forwardA, 1);
	float minProximity = min(proximityA, proximityB);
	if (minProximity >= 0.0f && minProximity < 1.0f){
		minProximity = max(0.0f, (minProximity - 0.2f) * 1.25f);
		pVehicle->AutoPilot.m_bSlowedDownBecauseOfCars = true;
		*pSpeed = min(*pSpeed, minProximity * curSpeed);
	}
	if (minProximity >= 0.0f && minProximity < 0.5f && pOtherEntity->IsVehicle() &&
	  CTimer::GetTimeInMilliseconds() - pVehicle->AutoPilot.m_nTimeToStartMission > 15000 &&
	  CTimer::GetTimeInMilliseconds() - pOtherVehicle->AutoPilot.m_nTimeToStartMission > 15000){
		/* If cars are standing for 15 seconds, annoy one of them and make avoid cars. */
		if (pOtherEntity != FindPlayerVehicle() &&
		  DotProduct2D(pVehicle->GetForward(), pOtherVehicle->GetForward()) < 0.5f &&
		  pVehicle < pOtherVehicle){ /* that comparasion though... */
			*pSpeed = max(curSpeed / 5, *pSpeed);
			if (pVehicle->m_status == STATUS_SIMPLE){
				pVehicle->m_status = STATUS_PHYSICS;
				SwitchVehicleToRealPhysics(pVehicle);
			}
			pVehicle->AutoPilot.m_nDrivingStyle = DRIVINGSTYLE_AVOID_CARS;
			pVehicle->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 1000;
		}
	}
}

#if 0
WRAPPER float CCarCtrl::TestCollisionBetween2MovingRects(CVehicle* pVehicleA, CVehicle* pVehicleB, float projectionX, float projectionY, CVector* pForwardA, CVector* pForwardB, uint8 id) { EAXJMP(0x41A020); }
#else
float CCarCtrl::TestCollisionBetween2MovingRects(CVehicle* pVehicleA, CVehicle* pVehicleB, float projectionX, float projectionY, CVector* pForwardA, CVector* pForwardB, uint8 id)
{
	CVector2D vecBToA = pVehicleA->GetPosition() - pVehicleB->GetPosition();
	float lenB = pVehicleB->GetModelInfo()->GetColModel()->boundingBox.max.y;
	float widthB = pVehicleB->GetModelInfo()->GetColModel()->boundingBox.max.x;
	float backLenB = -pVehicleB->GetModelInfo()->GetColModel()->boundingBox.min.y;
	float lenA = pVehicleA->GetModelInfo()->GetColModel()->boundingBox.max.y;
	float widthA = pVehicleA->GetModelInfo()->GetColModel()->boundingBox.max.x;
	float backLenA = -pVehicleA->GetModelInfo()->GetColModel()->boundingBox.min.y;
	float proximity = 1.0f;
	float fullWidthB = 2.0f * widthB;
	float fullLenB = lenB + backLenB;
	for (int i = 0; i < 4; i++){
		float testedOffsetX;
		float testedOffsetY;
		switch (i) {
		case 0: /* Front right corner */
			testedOffsetX = vecBToA.x + widthA * pForwardB->y + lenA * pForwardB->x;
			testedOffsetY = vecBToA.y + lenA * pForwardB->y - widthA * pForwardB->x;
			break;
		case 1: /* Front left corner */
			testedOffsetX = vecBToA.x + -widthA * pForwardB->x + lenA * pForwardB->x;
			testedOffsetY = vecBToA.y + lenA * pForwardB->y + widthA * pForwardB->x;
			break;
		case 2: /* Rear right corner */
			testedOffsetX = vecBToA.x + widthA * pForwardB->y - backLenA * pForwardB->x;
			testedOffsetY = vecBToA.y - backLenA * pForwardB->y - widthA * pForwardB->x;
			break;
		case 3: /* Rear left corner */
			testedOffsetX = vecBToA.x - widthA * pForwardB->y - backLenA * pForwardB->x;
			testedOffsetY = vecBToA.y - backLenA * pForwardB->y + widthA * pForwardB->x;
			break;
		default:
			break;
		}
		/* Testing width collision */
		float baseWidthProximity = 0.0f;
		float fullWidthProximity = 1.0f;
		float widthDistance = testedOffsetX * pForwardA->y - testedOffsetY * pForwardA->x;
		float widthProjection = projectionX * pForwardA->y - projectionY * pForwardA->x;
		if (widthDistance > widthB){
			if (widthProjection < 0.0f){
				float proximityWidth = -(widthDistance - widthB) / widthProjection;
				if (proximityWidth < 1.0f){
					baseWidthProximity = proximityWidth;
					fullWidthProximity = min(1.0f, proximityWidth - fullWidthB / widthProjection);
				}else{
					baseWidthProximity = 1.0f;
				}
			}else{
				baseWidthProximity = 1.0f;
				fullWidthProximity = 1.0f;
			}
		}else if (widthDistance < -widthB){
			if (widthProjection > 0.0f) {
				float proximityWidth = -(widthDistance + widthB) / widthProjection;
				if (proximityWidth < 1.0f) {
					baseWidthProximity = proximityWidth;
					fullWidthProximity = min(1.0f, proximityWidth + fullWidthB / widthProjection);
				}
				else {
					baseWidthProximity = 1.0f;
				}
			}
			else {
				baseWidthProximity = 1.0f;
				fullWidthProximity = 1.0f;
			}
		}else if (widthProjection > 0.0f){
			fullWidthProximity = (widthB - widthDistance) / widthProjection;
		}else if (widthProjection < 0.0f){
			fullWidthProximity = -(widthB + widthDistance) / widthProjection;
		}
		/* Testing length collision */
		float baseLengthProximity = 0.0f;
		float fullLengthProximity = 1.0f;
		float lenDistance = testedOffsetX * pForwardA->x + testedOffsetY * pForwardA->y;
		float lenProjection = projectionX * pForwardA->x + projectionY * pForwardA->y;
		if (lenDistance > lenB) {
			if (lenProjection < 0.0f) {
				float proximityLength = -(lenDistance - lenB) / lenProjection;
				if (proximityLength < 1.0f) {
					baseLengthProximity = proximityLength;
					fullLengthProximity = min(1.0f, proximityLength - fullLenB / lenProjection);
				}
				else {
					baseLengthProximity = 1.0f;
				}
			}
			else {
				baseLengthProximity = 1.0f;
				fullLengthProximity = 1.0f;
			}
		}
		else if (lenDistance < -backLenB) {
			if (lenProjection > 0.0f) {
				float proximityLength = -(lenDistance + backLenB) / lenProjection;
				if (proximityLength < 1.0f) {
					baseLengthProximity = proximityLength;
					fullLengthProximity = min(1.0f, proximityLength + fullLenB / lenProjection);
				}
				else {
					baseLengthProximity = 1.0f;
				}
			}
			else {
				baseLengthProximity = 1.0f;
				fullLengthProximity = 1.0f;
			}
		}
		else if (lenProjection > 0.0f) {
			fullLengthProximity = (lenB - lenDistance) / lenProjection;
		}
		else if (lenProjection < 0.0f) {
			fullLengthProximity = -(backLenB + lenDistance) / lenProjection;
		}
		float baseProximity = max(baseWidthProximity, baseLengthProximity);
		if (baseProximity < fullWidthProximity && baseProximity < fullLengthProximity)
			proximity = min(proximity, baseProximity);
	}
	return proximity;
}
#endif

float CCarCtrl::FindAngleToWeaveThroughTraffic(CVehicle* pVehicle, CPhysical* pTarget, float angleToTarget, float angleForward)
{
	float distanceToTest = min(2.0f, pVehicle->GetMoveSpeed().Magnitude2D() * 2.5f + 1.0f) * 12.0f;
	float left = pVehicle->GetPosition().x - distanceToTest;
	float right = pVehicle->GetPosition().x + distanceToTest;
	float top = pVehicle->GetPosition().y - distanceToTest;
	float bottom = pVehicle->GetPosition().y + distanceToTest;
	int xstart = max(0, CWorld::GetSectorIndexX(left));
	int xend = min(NUMSECTORS_X - 1, CWorld::GetSectorIndexX(right));
	int ystart = max(0, CWorld::GetSectorIndexY(top));
	int yend = min(NUMSECTORS_Y - 1, CWorld::GetSectorIndexY(bottom));
	assert(xstart <= xend);
	assert(ystart <= yend);

	float angleToWeaveLeft = angleToTarget;
	float angleToWeaveRight = angleToTarget;

	CWorld::AdvanceCurrentScanCode();

	float angleToWeaveLeftLastIteration = -9999.9f;
	float angleToWeaveRightLastIteration = -9999.9f;

	while (angleToWeaveLeft != angleToWeaveLeftLastIteration ||
		   angleToWeaveRight != angleToWeaveRightLastIteration){
		angleToWeaveLeftLastIteration = angleToWeaveLeft;
		angleToWeaveRightLastIteration = angleToWeaveRight;
		for (int y = ystart; y <= yend; y++) {
			for (int x = xstart; x <= xend; x++) {
				CSector* s = CWorld::GetSector(x, y);
				WeaveThroughCarsSectorList(s->m_lists[ENTITYLIST_VEHICLES], pVehicle, pTarget,
					left, top, right, bottom, &angleToWeaveLeft, &angleToWeaveRight);
				WeaveThroughCarsSectorList(s->m_lists[ENTITYLIST_VEHICLES_OVERLAP], pVehicle, pTarget,
					left, top, right, bottom, &angleToWeaveLeft, &angleToWeaveRight);
				WeaveThroughPedsSectorList(s->m_lists[ENTITYLIST_PEDS], pVehicle, pTarget,
					left, top, right, bottom, &angleToWeaveLeft, &angleToWeaveRight);
				WeaveThroughPedsSectorList(s->m_lists[ENTITYLIST_PEDS_OVERLAP], pVehicle, pTarget,
					left, top, right, bottom, &angleToWeaveLeft, &angleToWeaveRight);
				WeaveThroughObjectsSectorList(s->m_lists[ENTITYLIST_OBJECTS], pVehicle,
					left, top, right, bottom, &angleToWeaveLeft, &angleToWeaveRight);
				WeaveThroughObjectsSectorList(s->m_lists[ENTITYLIST_OBJECTS_OVERLAP], pVehicle,
					left, top, right, bottom, &angleToWeaveLeft, &angleToWeaveRight);
			}
		}
	}
	float angleDiffFromActualToTarget = LimitRadianAngle(angleForward - angleToTarget);
	float angleToBisectActualToTarget = LimitRadianAngle(angleToTarget + angleDiffFromActualToTarget / 2);
	float angleDiffLeft = LimitRadianAngle(angleToWeaveLeft - angleToBisectActualToTarget);
	angleDiffLeft = ABS(angleDiffLeft);
	float angleDiffRight = LimitRadianAngle(angleToWeaveRight - angleToBisectActualToTarget);
	angleDiffRight = ABS(angleDiffRight);
	if (angleDiffLeft > HALFPI && angleDiffRight > HALFPI)
		return angleToBisectActualToTarget;
	if (ABS(angleDiffLeft - angleDiffRight) < 0.08f)
		return angleToWeaveRight;
	return angleDiffLeft < angleDiffRight ? angleToWeaveLeft : angleToWeaveRight;
}

void CCarCtrl::WeaveThroughCarsSectorList(CPtrList& lst, CVehicle* pVehicle, CPhysical* pTarget, float x_inf, float y_inf, float x_sup, float y_sup, float* pAngleToWeaveLeft, float* pAngleToWeaveRight)
{
	for (CPtrNode* pNode = lst.first; pNode != nil; pNode = pNode->next) {
		CVehicle* pTestVehicle = (CVehicle*)pNode->item;
		if (pTestVehicle->m_scanCode == CWorld::GetCurrentScanCode())
			continue;
		if (!pTestVehicle->bUsesCollision)
			continue;
		if (pTestVehicle == pTarget)
			continue;
		pTestVehicle->m_scanCode = CWorld::GetCurrentScanCode();
		if (pTestVehicle->GetBoundCentre().x < x_inf || pTestVehicle->GetBoundCentre().x > x_sup)
			continue;
		if (pTestVehicle->GetBoundCentre().y < y_inf || pTestVehicle->GetBoundCentre().y > y_sup)
			continue;
		if (Abs(pTestVehicle->GetPosition().z - pVehicle->GetPosition().z) >= VEHICLE_HEIGHT_DIFF_TO_CONSIDER_WEAVING)
			continue;
		if (pTestVehicle != pVehicle)
			WeaveForOtherCar(pTestVehicle, pVehicle, pAngleToWeaveLeft, pAngleToWeaveRight);
	}
}

void CCarCtrl::WeaveForOtherCar(CEntity* pOtherEntity, CVehicle* pVehicle, float* pAngleToWeaveLeft, float* pAngleToWeaveRight)
{
	if (pVehicle->AutoPilot.m_nCarMission == MISSION_RAMPLAYER_CLOSE && pOtherEntity == FindPlayerVehicle())
		return;
	if (pVehicle->AutoPilot.m_nCarMission == MISSION_RAMCAR_CLOSE && pOtherEntity == pVehicle->AutoPilot.m_pTargetCar)
		return;
	CVehicle* pOtherCar = (CVehicle*)pOtherEntity;
	CVector2D vecDiff = pOtherCar->GetPosition() - pVehicle->GetPosition();
	float angleBetweenVehicles = CGeneral::GetATanOfXY(vecDiff.x, vecDiff.y);
	float distance = vecDiff.Magnitude();
	if (distance < 1.0f)
		return;
	if (DotProduct2D(pVehicle->GetMoveSpeed() - pOtherCar->GetMoveSpeed(), vecDiff) * 110.0f -
	  pOtherCar->GetModelInfo()->GetColModel()->boundingSphere.radius -
	  pVehicle->GetModelInfo()->GetColModel()->boundingSphere.radius < distance)
		return;
	CVector2D forward = pVehicle->GetForward();
	forward.Normalise();
	float forwardAngle = CGeneral::GetATanOfXY(forward.x, forward.y);
	float angleDiff = angleBetweenVehicles - forwardAngle;
	float lenProjection = ABS(pOtherCar->GetColModel()->boundingBox.max.y * sin(angleDiff));
	float widthProjection = ABS(pOtherCar->GetColModel()->boundingBox.max.x * cos(angleDiff));
	float lengthToEvade = (2 * (lenProjection + widthProjection) + WIDTH_COEF_TO_WEAVE_SAFELY * 2 * pVehicle->GetColModel()->boundingBox.max.x) / distance;
	float diffToLeftAngle = LimitRadianAngle(angleBetweenVehicles - *pAngleToWeaveLeft);
	diffToLeftAngle = ABS(diffToLeftAngle);
	float angleToWeave = lengthToEvade / 2;
	if (diffToLeftAngle < angleToWeave){
		*pAngleToWeaveLeft = angleBetweenVehicles - angleToWeave;
		while (*pAngleToWeaveLeft < -PI)
			*pAngleToWeaveLeft += TWOPI;
	}
	float diffToRightAngle = LimitRadianAngle(angleBetweenVehicles - *pAngleToWeaveRight);
	diffToRightAngle = ABS(diffToRightAngle);
	if (diffToRightAngle < angleToWeave){
		*pAngleToWeaveRight = angleBetweenVehicles + angleToWeave;
		while (*pAngleToWeaveRight > PI)
			*pAngleToWeaveRight -= TWOPI;
	}
}

void CCarCtrl::WeaveThroughPedsSectorList(CPtrList& lst, CVehicle* pVehicle, CPhysical* pTarget, float x_inf, float y_inf, float x_sup, float y_sup, float* pAngleToWeaveLeft, float* pAngleToWeaveRight)
{
	for (CPtrNode* pNode = lst.first; pNode != nil; pNode = pNode->next) {
		CPed* pPed = (CPed*)pNode->item;
		if (pPed->m_scanCode == CWorld::GetCurrentScanCode())
			continue;
		if (!pPed->bUsesCollision)
			continue;
		if (pPed == pTarget)
			continue;
		pPed->m_scanCode = CWorld::GetCurrentScanCode();
		if (pPed->GetPosition().x < x_inf || pPed->GetPosition().x > x_sup)
			continue;
		if (pPed->GetPosition().y < y_inf || pPed->GetPosition().y > y_sup)
			continue;
		if (Abs(pPed->GetPosition().z - pPed->GetPosition().z) >= PED_HEIGHT_DIFF_TO_CONSIDER_WEAVING)
			continue;
		if (pPed->m_pCurSurface != pVehicle)
			WeaveForPed(pPed, pVehicle, pAngleToWeaveLeft, pAngleToWeaveRight);
	}

}
void CCarCtrl::WeaveForPed(CEntity* pOtherEntity, CVehicle* pVehicle, float* pAngleToWeaveLeft, float* pAngleToWeaveRight)
{
	if (pVehicle->AutoPilot.m_nCarMission == MISSION_RAMPLAYER_CLOSE && pOtherEntity == FindPlayerPed())
		return;
	CPed* pPed = (CPed*)pOtherEntity;
	CVector2D vecDiff = pPed->GetPosition() - pVehicle->GetPosition();
	float angleBetweenVehicleAndPed = CGeneral::GetATanOfXY(vecDiff.x, vecDiff.y);
	float distance = vecDiff.Magnitude();
	float lengthToEvade = (WIDTH_COEF_TO_WEAVE_SAFELY * 2 * pVehicle->GetColModel()->boundingBox.max.x + PED_WIDTH_TO_WEAVE) / distance;
	float diffToLeftAngle = LimitRadianAngle(angleBetweenVehicleAndPed - *pAngleToWeaveLeft);
	diffToLeftAngle = ABS(diffToLeftAngle);
	float angleToWeave = lengthToEvade / 2;
	if (diffToLeftAngle < angleToWeave) {
		*pAngleToWeaveLeft = angleBetweenVehicleAndPed - angleToWeave;
		while (*pAngleToWeaveLeft < -PI)
			*pAngleToWeaveLeft += TWOPI;
	}
	float diffToRightAngle = LimitRadianAngle(angleBetweenVehicleAndPed - *pAngleToWeaveRight);
	diffToRightAngle = ABS(diffToRightAngle);
	if (diffToRightAngle < angleToWeave) {
		*pAngleToWeaveRight = angleBetweenVehicleAndPed + angleToWeave;
		while (*pAngleToWeaveRight > PI)
			*pAngleToWeaveRight -= TWOPI;
	}
}

void CCarCtrl::WeaveThroughObjectsSectorList(CPtrList& lst, CVehicle* pVehicle, float x_inf, float y_inf, float x_sup, float y_sup, float* pAngleToWeaveLeft, float* pAngleToWeaveRight)
{
	for (CPtrNode* pNode = lst.first; pNode != nil; pNode = pNode->next) {
		CObject* pObject = (CObject*)pNode->item;
		if (pObject->m_scanCode == CWorld::GetCurrentScanCode())
			continue;
		if (!pObject->bUsesCollision)
			continue;
		pObject->m_scanCode = CWorld::GetCurrentScanCode();
		if (pObject->GetPosition().x < x_inf || pObject->GetPosition().x > x_sup)
			continue;
		if (pObject->GetPosition().y < y_inf || pObject->GetPosition().y > y_sup)
			continue;
		if (Abs(pObject->GetPosition().z - pVehicle->GetPosition().z) >= OBJECT_HEIGHT_DIFF_TO_CONSIDER_WEAVING)
			continue;
		if (pObject->GetUp().z > 0.9f)
			WeaveForObject(pObject, pVehicle, pAngleToWeaveLeft, pAngleToWeaveRight);
	}
}

void CCarCtrl::WeaveForObject(CEntity* pOtherEntity, CVehicle* pVehicle, float* pAngleToWeaveLeft, float* pAngleToWeaveRight)
{
	float rightCoef;
	float forwardCoef;
	if (pOtherEntity->GetModelIndex() == MI_TRAFFICLIGHTS){
		rightCoef = 2.957f;
		forwardCoef = 0.147f;
	}else if (pOtherEntity->GetModelIndex() == MI_SINGLESTREETLIGHTS1){
		rightCoef = 0.744f;
		forwardCoef = 0.0f;
	}else if (pOtherEntity->GetModelIndex() == MI_SINGLESTREETLIGHTS2){
		rightCoef = 0.043f;
		forwardCoef = 0.0f;
	}else if (pOtherEntity->GetModelIndex() == MI_SINGLESTREETLIGHTS3){
		rightCoef = 1.143f;
		forwardCoef = 0.145f;
	}else if (pOtherEntity->GetModelIndex() == MI_DOUBLESTREETLIGHTS){
		rightCoef = 0.0f;
		forwardCoef = -0.048f;
	}else if (IsTreeModel(pOtherEntity->GetModelIndex())){
		rightCoef = 0.0f;
		forwardCoef = 0.0f;
	}else if (pOtherEntity->GetModelIndex() == MI_STREETLAMP1 || pOtherEntity->GetModelIndex() == MI_STREETLAMP2){
		rightCoef = 0.0f;
		forwardCoef = 0.0f;
	}else
		return;
	CObject* pObject = (CObject*)pOtherEntity;
	CVector2D vecDiff = pObject->GetPosition() +
		rightCoef * pObject->GetRight() +
		forwardCoef * pObject->GetForward() -
		pVehicle->GetPosition();
	float angleBetweenVehicleAndObject = CGeneral::GetATanOfXY(vecDiff.x, vecDiff.y);
	float distance = vecDiff.Magnitude();
	float lengthToEvade = (WIDTH_COEF_TO_WEAVE_SAFELY * 2 * pVehicle->GetColModel()->boundingBox.max.x + OBJECT_WIDTH_TO_WEAVE) / distance;
	float diffToLeftAngle = LimitRadianAngle(angleBetweenVehicleAndObject - *pAngleToWeaveLeft);
	diffToLeftAngle = ABS(diffToLeftAngle);
	float angleToWeave = lengthToEvade / 2;
	if (diffToLeftAngle < angleToWeave) {
		*pAngleToWeaveLeft = angleBetweenVehicleAndObject - angleToWeave;
		while (*pAngleToWeaveLeft < -PI)
			*pAngleToWeaveLeft += TWOPI;
	}
	float diffToRightAngle = LimitRadianAngle(angleBetweenVehicleAndObject - *pAngleToWeaveRight);
	diffToRightAngle = ABS(diffToRightAngle);
	if (diffToRightAngle < angleToWeave) {
		*pAngleToWeaveRight = angleBetweenVehicleAndObject + angleToWeave;
		while (*pAngleToWeaveRight > PI)
			*pAngleToWeaveRight -= TWOPI;
	}
}

bool CCarCtrl::PickNextNodeAccordingStrategy(CVehicle* pVehicle)
{
	switch (pVehicle->AutoPilot.m_nCarMission){
	case MISSION_RAMPLAYER_FARAWAY:
	case MISSION_BLOCKPLAYER_FARAWAY:
		PickNextNodeToChaseCar(pVehicle,
			FindPlayerCoors().x,
			FindPlayerCoors().y,
#ifdef FIX_PATHFIND_BUG
			FindPlayerCoors().z,
#endif
			FindPlayerVehicle());
		return false;
	case MISSION_GOTOCOORDS:
	case MISSION_GOTOCOORDS_ACCURATE:
		return PickNextNodeToFollowPath(pVehicle);
	case MISSION_RAMCAR_FARAWAY:
	case MISSION_BLOCKCAR_FARAWAY:
		PickNextNodeToChaseCar(pVehicle,
			pVehicle->AutoPilot.m_pTargetCar->GetPosition().x,
			pVehicle->AutoPilot.m_pTargetCar->GetPosition().y,
#ifdef FIX_PATHFIND_BUG
			pVehicle->AutoPilot.m_pTargetCar->GetPosition().z,
#endif
			pVehicle->AutoPilot.m_pTargetCar);
		return false;
	default:
		PickNextNodeRandomly(pVehicle);
		return false;
	}
}

void CCarCtrl::PickNextNodeRandomly(CVehicle* pVehicle)
{
	int32 prevNode = pVehicle->AutoPilot.m_nCurrentRouteNode;
	int32 curNode = pVehicle->AutoPilot.m_nNextRouteNode;
	uint8 totalLinks = ThePaths.m_pathNodes[curNode].numLinks;
	CCarPathLink* pCurLink = &ThePaths.m_carPathLinks[pVehicle->AutoPilot.m_nNextPathNodeInfo];
	uint8 lanesOnCurrentPath = pCurLink->pathNodeIndex == curNode ?
		pCurLink->numRightLanes : pCurLink->numLeftLanes;
	uint8 allowedDirections = PATH_DIRECTION_NONE;
	uint8 nextLane = pVehicle->AutoPilot.m_nNextLane;
	if (nextLane == 0)
		/* We are always allowed to turn left from  leftmost lane */
		allowedDirections |= PATH_DIRECTION_LEFT;
	if (nextLane == lanesOnCurrentPath - 1)
		/* We are always allowed to turn right from rightmost lane */
		allowedDirections |= PATH_DIRECTION_RIGHT;
	if (lanesOnCurrentPath < 3 || allowedDirections == PATH_DIRECTION_NONE)
		/* We are always allowed to go straight on one/two-laned road */
		/* or if we are in one of middle lanes of the road */
		allowedDirections |= PATH_DIRECTION_STRAIGHT;
	int attempt;
	pVehicle->AutoPilot.m_nPrevRouteNode = pVehicle->AutoPilot.m_nCurrentRouteNode;
	pVehicle->AutoPilot.m_nCurrentRouteNode = pVehicle->AutoPilot.m_nNextRouteNode;
	CPathNode* pPrevPathNode = &ThePaths.m_pathNodes[prevNode];
	CPathNode* pCurPathNode = &ThePaths.m_pathNodes[curNode];
	int16 nextLink;
	CCarPathLink* pNextLink;
	CPathNode* pNextPathNode;
	bool goingAgainstOneWayRoad;
	uint8 direction;
	for(attempt = 0; attempt < ATTEMPTS_TO_FIND_NEXT_NODE; attempt++){
		if (attempt != 0){
			if (pVehicle->AutoPilot.m_nNextRouteNode != prevNode){
				if (direction & allowedDirections){
					pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
					if ((!pNextPathNode->bDeadEnd || pPrevPathNode->bDeadEnd) &&
						(!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
						(!pNextPathNode->bBetweenLevels || pPrevPathNode->bBetweenLevels || !pVehicle->AutoPilot.m_bStayInCurrentLevel) &&
						!goingAgainstOneWayRoad)
						break;
				}
			}
		}
		nextLink = CGeneral::GetRandomNumber() % totalLinks;
		pVehicle->AutoPilot.m_nNextRouteNode = ThePaths.m_connections[nextLink + pCurPathNode->firstLink];
		direction = FindPathDirection(prevNode, curNode, pVehicle->AutoPilot.m_nNextRouteNode);
		pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
		goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
	}
	if (attempt >= ATTEMPTS_TO_FIND_NEXT_NODE) {
		/* If we failed 15 times, then remove dead end and current lane limitations */
		for (attempt = 0; attempt < ATTEMPTS_TO_FIND_NEXT_NODE; attempt++) {
			if (attempt != 0) {
				if (pVehicle->AutoPilot.m_nNextRouteNode != prevNode) {
					pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
					if ((!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
						(!pNextPathNode->bBetweenLevels || pNextPathNode->bBetweenLevels || !pVehicle->AutoPilot.m_bStayInCurrentLevel) &&
						!goingAgainstOneWayRoad)
						break;
				}
			}
			nextLink = CGeneral::GetRandomNumber() % totalLinks;
			pVehicle->AutoPilot.m_nNextRouteNode = ThePaths.m_connections[nextLink + pCurPathNode->firstLink];
			pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
			goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
		}
	}
	if (attempt >= ATTEMPTS_TO_FIND_NEXT_NODE) {
		/* If we failed again, remove no U-turn limitation and remove randomness */
		for (nextLink = 0; nextLink < totalLinks; nextLink++) {
			pVehicle->AutoPilot.m_nNextRouteNode = ThePaths.m_connections[nextLink + pCurPathNode->firstLink];
			pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
			goingAgainstOneWayRoad = pNextLink->pathNodeIndex == curNode ? pNextLink->numRightLanes == 0 : pNextLink->numLeftLanes == 0;
			if (!goingAgainstOneWayRoad) {
				pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
				if ((!pNextPathNode->bDisabled || pPrevPathNode->bDisabled) &&
					(!pNextPathNode->bBetweenLevels || pNextPathNode->bBetweenLevels || !pVehicle->AutoPilot.m_bStayInCurrentLevel))
					/* Nice way to exit loop but this will fail because this is used for indexing! */
					nextLink = 1000;
			}
		}
		if (nextLink < 999)
			/* If everything else failed, turn vehicle around */
			pVehicle->AutoPilot.m_nNextRouteNode = prevNode;
	}
	pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
	pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink]];
	if (prevNode == pVehicle->AutoPilot.m_nNextRouteNode){
		/* We can no longer shift vehicle without physics if we have to turn it around. */
		pVehicle->m_status = STATUS_PHYSICS;
		SwitchVehicleToRealPhysics(pVehicle);
	}
	pVehicle->AutoPilot.m_nTimeEnteredCurve += pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve;
	pVehicle->AutoPilot.m_nPreviousPathNodeInfo = pVehicle->AutoPilot.m_nCurrentPathNodeInfo;
	pVehicle->AutoPilot.m_nCurrentPathNodeInfo = pVehicle->AutoPilot.m_nNextPathNodeInfo;
	pVehicle->AutoPilot.m_nPreviousDirection = pVehicle->AutoPilot.m_nCurrentDirection;
	pVehicle->AutoPilot.m_nCurrentDirection = pVehicle->AutoPilot.m_nNextDirection;
	pVehicle->AutoPilot.m_nCurrentLane = pVehicle->AutoPilot.m_nNextLane;
	pVehicle->AutoPilot.m_nNextPathNodeInfo = ThePaths.m_carPathConnections[nextLink + pCurPathNode->firstLink];
	uint8 lanesOnNextNode;
	if (curNode >= pVehicle->AutoPilot.m_nNextRouteNode){
		pVehicle->AutoPilot.m_nNextDirection = 1;
		lanesOnNextNode = pNextLink->numLeftLanes;
	}else{
		pVehicle->AutoPilot.m_nNextDirection = -1;
		lanesOnNextNode = pNextLink->numRightLanes;
	}
	float currentPathLinkForwardX = pVehicle->AutoPilot.m_nCurrentDirection * pCurLink->dirX;
	float nextPathLinkForwardX = pVehicle->AutoPilot.m_nNextDirection * pNextLink->dirX;
	if (lanesOnNextNode >= 0){
		if ((CGeneral::GetRandomNumber() & 0x600) == 0){
			/* 25% chance vehicle will try to switch lane */
			CVector2D dist = pNextPathNode->pos - pCurPathNode->pos;
			if (dist.MagnitudeSqr() >= SQR(14.0f)){
				if (CGeneral::GetRandomTrueFalse())
					pVehicle->AutoPilot.m_nNextLane += 1;
				else
					pVehicle->AutoPilot.m_nNextLane -= 1;
			}
		}
		pVehicle->AutoPilot.m_nNextLane = min(lanesOnNextNode - 1, pVehicle->AutoPilot.m_nNextLane);
		pVehicle->AutoPilot.m_nNextLane = max(0, pVehicle->AutoPilot.m_nNextLane);
	}else{
		pVehicle->AutoPilot.m_nNextLane = pVehicle->AutoPilot.m_nCurrentLane;
	}
	if (pVehicle->AutoPilot.m_bStayInFastLane)
		pVehicle->AutoPilot.m_nNextLane = 0;
	CVector positionOnCurrentLinkIncludingLane(
		pCurLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurLink), /* ...what about Y? */
		pCurLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurLink) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink),
		pNextLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardX,
		0.0f);
	float directionCurrentLinkX = pCurLink->dirX * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionCurrentLinkY = pCurLink->dirY * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionNextLinkX = pNextLink->dirX * pVehicle->AutoPilot.m_nNextDirection;
	float directionNextLinkY = pNextLink->dirY * pVehicle->AutoPilot.m_nNextDirection;
	/* We want to make a path between two links that may not have the same forward directions a curve. */
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = CCurves::CalcSpeedScaleFactor(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		directionCurrentLinkX, directionCurrentLinkY,
		directionNextLinkX, directionNextLinkY
	) * (1000.0f / pVehicle->AutoPilot.m_fMaxTrafficSpeed);
	if (pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve < 10)
		/* Oh hey there Obbe */
		debug("fout\n");
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = max(10, pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve);
}

uint8 CCarCtrl::FindPathDirection(int32 prevNode, int32 curNode, int32 nextNode)
{
	CVector2D prevToCur = ThePaths.m_pathNodes[curNode].pos - ThePaths.m_pathNodes[prevNode].pos;
	CVector2D curToNext = ThePaths.m_pathNodes[nextNode].pos - ThePaths.m_pathNodes[curNode].pos;
	float distPrevToCur = prevToCur.Magnitude();
	if (distPrevToCur == 0.0f)
		return PATH_DIRECTION_NONE;
	/* We are trying to determine angle between prevToCur and curToNext. */
	/* To find it, we consider a to be an angle between y axis and prevToCur */
	/* and b to be an angle between x axis and curToNext */
	/* Then the angle we are looking for is (pi/2 + a + b). */
	float sin_a = prevToCur.x / distPrevToCur;
	float cos_a = prevToCur.y / distPrevToCur;
	float distCurToNext = curToNext.Magnitude();
	if (distCurToNext == 0.0f)
		return PATH_DIRECTION_NONE;
	float sin_b = curToNext.y / distCurToNext;
	float cos_b = curToNext.x / distCurToNext;
	/* sin(a) * sin(b) - cos(a) * cos(b) = -cos(a+b) = sin(pi/2+a+b) */
	float sin_direction = sin_a * sin_b - cos_a * cos_b;
	if (sin_direction > 0.77f) /* Roughly between -50 and -130 degrees */
		return PATH_DIRECTION_LEFT;
	if (sin_direction < -0.77f) /* Roughly between 50 and 130 degrees */
		return PATH_DIRECTION_RIGHT;
	return PATH_DIRECTION_STRAIGHT;
}

#ifdef FIX_PATHFIND_BUG
void CCarCtrl::PickNextNodeToChaseCar(CVehicle* pVehicle, float targetX, float targetY, float targetZ, CVehicle* pTarget)
#else
void CCarCtrl::PickNextNodeToChaseCar(CVehicle* pVehicle, float targetX, float targetY, CVehicle* pTarget)
#endif
{
	int prevNode = pVehicle->AutoPilot.m_nCurrentRouteNode;
	int curNode = pVehicle->AutoPilot.m_nNextRouteNode;
	CPathNode* pPrevNode = &ThePaths.m_pathNodes[prevNode];
	CPathNode* pCurNode = &ThePaths.m_pathNodes[curNode];
	CPathNode* pTargetNode;
	int16 numNodes;
	float distanceToTargetNode;
#ifndef REMOVE_TREADABLE_PATHFIND
	if (pTarget && pTarget->m_pCurGroundEntity->m_type == ENTITY_TYPE_BUILDING &&
	  ((CBuilding*)pTarget->m_pCurGroundEntity)->GetIsATreadable() &&
	  ((CTreadable*)pTarget->m_pCurGroundEntity)->m_nodeIndices[0][0] >= 0){
		CTreadable* pCurrentMapObject = (CTreadable*)pTarget->m_pCurGroundEntity;
		int closestNode = -1;
		float minDist = 100000.0f;
		for (int i = 0; i < 12; i++){
			int node = pCurrentMapObject->m_nodeIndices[0][i];
			if (node < 0)
				break;
			float dist = (ThePaths.m_pathNodes[node].pos - pTarget->GetPosition()).Magnitude();
			if (dist < minDist){
				minDist = dist;
				closestNode = node;
			}
		}
		ThePaths.DoPathSearch(0, pCurNode->pos, curNode,
#ifdef FIX_PATHFIND_BUG
			CVector(targetX, targetY, targetZ),
#else
			CVector(targetX, targetY, 0.0f),
#endif
			&pTargetNode, &numNodes, 1, pVehicle, &distanceToTargetNode, 999999.9f, closestNode);
	}else{
#endif
		ThePaths.DoPathSearch(0, pCurNode->pos, curNode,
#ifdef FIX_PATHFIND_BUG
			CVector(targetX, targetY, targetZ),
#else
			CVector(targetX, targetY, 0.0f),
#endif
			&pTargetNode, &numNodes, 1, pVehicle, &distanceToTargetNode, 999999.9f, -1);
#ifndef REMOVE_TREADABLE_PATHFIND
	}
#endif
	int newNextNode;
	int nextLink;
	if (numNodes != 1 || pTargetNode == pCurNode){
		float currentAngle = CGeneral::GetATanOfXY(targetX - pVehicle->GetPosition().x, targetY - pVehicle->GetPosition().y);
		nextLink = 0;
		float lowestAngleChange = 10.0f;
		int numLinks = pCurNode->numLinks;
		newNextNode = 0;
		for (int i = 0; i < numLinks; i++){
			int conNode = ThePaths.m_connections[i + pCurNode->firstLink];
			if (conNode == prevNode && i > 1)
				continue;
			CPathNode* pTestNode = &ThePaths.m_pathNodes[conNode];
			float angle = CGeneral::GetATanOfXY(pTestNode->pos.x - pCurNode->pos.x, pTestNode->pos.y - pCurNode->pos.y);
			angle = LimitRadianAngle(angle - currentAngle);
			angle = ABS(angle);
			if (angle < lowestAngleChange){
				lowestAngleChange = angle;
				newNextNode = conNode;
				nextLink = i;
			}
		}
	}else{
		nextLink = 0;
		newNextNode = pTargetNode - ThePaths.m_pathNodes;
		for (int i = pCurNode->firstLink; ThePaths.m_connections[i] != newNextNode; i++, nextLink++)
			;
	}
	CPathNode* pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
	CCarPathLink* pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurNode->firstLink]];
	CCarPathLink* pCurLink = &ThePaths.m_carPathLinks[pVehicle->AutoPilot.m_nNextPathNodeInfo];
	pVehicle->AutoPilot.m_nPrevRouteNode = pVehicle->AutoPilot.m_nCurrentRouteNode;
	pVehicle->AutoPilot.m_nCurrentRouteNode = pVehicle->AutoPilot.m_nNextRouteNode;
	pVehicle->AutoPilot.m_nNextRouteNode = newNextNode;
	pVehicle->AutoPilot.m_nTimeEnteredCurve += pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve;
	pVehicle->AutoPilot.m_nPreviousPathNodeInfo = pVehicle->AutoPilot.m_nCurrentPathNodeInfo;
	pVehicle->AutoPilot.m_nCurrentPathNodeInfo = pVehicle->AutoPilot.m_nNextPathNodeInfo;
	pVehicle->AutoPilot.m_nPreviousDirection = pVehicle->AutoPilot.m_nCurrentDirection;
	pVehicle->AutoPilot.m_nCurrentDirection = pVehicle->AutoPilot.m_nNextDirection;
	pVehicle->AutoPilot.m_nCurrentLane = pVehicle->AutoPilot.m_nNextLane;
	pVehicle->AutoPilot.m_nNextPathNodeInfo = ThePaths.m_carPathConnections[nextLink + pCurNode->firstLink];
	uint8 lanesOnNextNode;
	if (curNode >= pVehicle->AutoPilot.m_nNextRouteNode) {
		pVehicle->AutoPilot.m_nNextDirection = 1;
		lanesOnNextNode = pNextLink->numLeftLanes;
	}
	else {
		pVehicle->AutoPilot.m_nNextDirection = -1;
		lanesOnNextNode = pNextLink->numRightLanes;
	}
	float currentPathLinkForwardX = pVehicle->AutoPilot.m_nCurrentDirection * pCurLink->dirX;
	float currentPathLinkForwardY = pVehicle->AutoPilot.m_nCurrentDirection * pCurLink->dirY;
	float nextPathLinkForwardX = pVehicle->AutoPilot.m_nNextDirection * pNextLink->dirX;
	float nextPathLinkForwardY = pVehicle->AutoPilot.m_nNextDirection * pNextLink->dirY;
	if (lanesOnNextNode >= 0) {
		CVector2D dist = pNextPathNode->pos - pCurNode->pos;
		if (dist.MagnitudeSqr() >= SQR(7.0f)){
			/* 25% chance vehicle will try to switch lane */
			/* No lane switching if following car from far away */
			/* ...although it's always one of those. */
			if ((CGeneral::GetRandomNumber() & 0x600) == 0 &&
			  pVehicle->AutoPilot.m_nCarMission != MISSION_RAMPLAYER_FARAWAY &&
			  pVehicle->AutoPilot.m_nCarMission != MISSION_BLOCKPLAYER_FARAWAY &&
			  pVehicle->AutoPilot.m_nCarMission != MISSION_RAMCAR_FARAWAY &&
			  pVehicle->AutoPilot.m_nCarMission != MISSION_BLOCKCAR_FARAWAY){
				if (CGeneral::GetRandomTrueFalse())
					pVehicle->AutoPilot.m_nNextLane += 1;
				else
					pVehicle->AutoPilot.m_nNextLane -= 1;
			}
		}
		pVehicle->AutoPilot.m_nNextLane = min(lanesOnNextNode - 1, pVehicle->AutoPilot.m_nNextLane);
		pVehicle->AutoPilot.m_nNextLane = max(0, pVehicle->AutoPilot.m_nNextLane);
	}
	else {
		pVehicle->AutoPilot.m_nNextLane = pVehicle->AutoPilot.m_nCurrentLane;
	}
	if (pVehicle->AutoPilot.m_bStayInFastLane)
		pVehicle->AutoPilot.m_nNextLane = 0;
	CVector positionOnCurrentLinkIncludingLane(
		pCurLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurLink) * currentPathLinkForwardY,
		pCurLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurLink) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardY,
		pNextLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardX,
		0.0f);
	float directionCurrentLinkX = pCurLink->dirX * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionCurrentLinkY = pCurLink->dirY * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionNextLinkX = pNextLink->dirX * pVehicle->AutoPilot.m_nNextDirection;
	float directionNextLinkY = pNextLink->dirY * pVehicle->AutoPilot.m_nNextDirection;
	/* We want to make a path between two links that may not have the same forward directions a curve. */
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = CCurves::CalcSpeedScaleFactor(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		directionCurrentLinkX, directionCurrentLinkY,
		directionNextLinkX, directionNextLinkY
	) * (1000.0f / pVehicle->AutoPilot.m_fMaxTrafficSpeed);
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = max(10, pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve);
}

bool CCarCtrl::PickNextNodeToFollowPath(CVehicle* pVehicle)
{
	int curNode = pVehicle->AutoPilot.m_nNextRouteNode;
	CPathNode* pCurNode = &ThePaths.m_pathNodes[curNode];
	CPathNode* pTargetNode;
	int16 numNodes;
	float distanceToTargetNode;
	if (pVehicle->AutoPilot.m_nPathFindNodesCount == 0){
		ThePaths.DoPathSearch(0, pVehicle->GetPosition(), curNode,
			pVehicle->AutoPilot.m_vecDestinationCoors, pVehicle->AutoPilot.m_aPathFindNodesInfo,
			&pVehicle->AutoPilot.m_nPathFindNodesCount, NUM_PATH_NODES_IN_AUTOPILOT,
			pVehicle, nil, 999999.9f, -1);
		if (pVehicle->AutoPilot.m_nPathFindNodesCount < 1)
			return true;
	}
	CPathNode* pNextPathNode = &ThePaths.m_pathNodes[pVehicle->AutoPilot.m_nNextRouteNode];
	CCarPathLink* pCurLink = &ThePaths.m_carPathLinks[pVehicle->AutoPilot.m_nNextPathNodeInfo];
	pVehicle->AutoPilot.m_nPrevRouteNode = pVehicle->AutoPilot.m_nCurrentRouteNode;
	pVehicle->AutoPilot.m_nCurrentRouteNode = pVehicle->AutoPilot.m_nNextRouteNode;
	pVehicle->AutoPilot.m_nNextRouteNode = pVehicle->AutoPilot.m_aPathFindNodesInfo[0] - ThePaths.m_pathNodes;
	pVehicle->AutoPilot.RemoveOnePathNode();
	pVehicle->AutoPilot.m_nTimeEnteredCurve += pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve;
	pVehicle->AutoPilot.m_nPreviousPathNodeInfo = pVehicle->AutoPilot.m_nCurrentPathNodeInfo;
	pVehicle->AutoPilot.m_nCurrentPathNodeInfo = pVehicle->AutoPilot.m_nNextPathNodeInfo;
	pVehicle->AutoPilot.m_nPreviousDirection = pVehicle->AutoPilot.m_nCurrentDirection;
	pVehicle->AutoPilot.m_nCurrentDirection = pVehicle->AutoPilot.m_nNextDirection;
	pVehicle->AutoPilot.m_nCurrentLane = pVehicle->AutoPilot.m_nNextLane;
	int nextLink = 0;
	for (int i = pCurNode->firstLink; ThePaths.m_connections[i] != pVehicle->AutoPilot.m_nNextRouteNode; i++, nextLink++)
		;
	CCarPathLink* pNextLink = &ThePaths.m_carPathLinks[ThePaths.m_carPathConnections[nextLink + pCurNode->firstLink]];
	pVehicle->AutoPilot.m_nNextPathNodeInfo = ThePaths.m_carPathConnections[nextLink + pCurNode->firstLink];
	uint8 lanesOnNextNode;
	if (curNode >= pVehicle->AutoPilot.m_nNextRouteNode) {
		pVehicle->AutoPilot.m_nNextDirection = 1;
		lanesOnNextNode = pNextLink->numLeftLanes;
	}
	else {
		pVehicle->AutoPilot.m_nNextDirection = -1;
		lanesOnNextNode = pNextLink->numRightLanes;
	}
	float currentPathLinkForwardX = pVehicle->AutoPilot.m_nCurrentDirection * pCurLink->dirX;
	float currentPathLinkForwardY = pVehicle->AutoPilot.m_nCurrentDirection * pCurLink->dirY;
	float nextPathLinkForwardX = pVehicle->AutoPilot.m_nNextDirection * pNextLink->dirX;
	float nextPathLinkForwardY = pVehicle->AutoPilot.m_nNextDirection * pNextLink->dirY;
	if (lanesOnNextNode >= 0) {
		CVector2D dist = pNextPathNode->pos - pCurNode->pos;
		if (dist.MagnitudeSqr() >= SQR(7.0f) && (CGeneral::GetRandomNumber() & 0x600) == 0) {
			if (CGeneral::GetRandomTrueFalse())
				pVehicle->AutoPilot.m_nNextLane += 1;
			else
				pVehicle->AutoPilot.m_nNextLane -= 1;
		}
		pVehicle->AutoPilot.m_nNextLane = min(lanesOnNextNode - 1, pVehicle->AutoPilot.m_nNextLane);
		pVehicle->AutoPilot.m_nNextLane = max(0, pVehicle->AutoPilot.m_nNextLane);
	}
	else {
		pVehicle->AutoPilot.m_nNextLane = pVehicle->AutoPilot.m_nCurrentLane;
	}
	if (pVehicle->AutoPilot.m_bStayInFastLane)
		pVehicle->AutoPilot.m_nNextLane = 0;
	CVector positionOnCurrentLinkIncludingLane(
		pCurLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurLink) * currentPathLinkForwardY,
		pCurLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nCurrentLane, pCurLink) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->posX + GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardY,
		pNextLink->posY - GetOffsetOfLaneFromCenterOfRoad(pVehicle->AutoPilot.m_nNextLane, pNextLink) * nextPathLinkForwardX,
		0.0f);
	float directionCurrentLinkX = pCurLink->dirX * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionCurrentLinkY = pCurLink->dirY * pVehicle->AutoPilot.m_nCurrentDirection;
	float directionNextLinkX = pNextLink->dirX * pVehicle->AutoPilot.m_nNextDirection;
	float directionNextLinkY = pNextLink->dirY * pVehicle->AutoPilot.m_nNextDirection;
	/* We want to make a path between two links that may not have the same forward directions a curve. */
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = CCurves::CalcSpeedScaleFactor(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		directionCurrentLinkX, directionCurrentLinkY,
		directionNextLinkX, directionNextLinkY
	) * (1000.0f / pVehicle->AutoPilot.m_fMaxTrafficSpeed);
	pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve = max(10, pVehicle->AutoPilot.m_nTimeToSpendOnCurrentCurve);
	return false;
}

bool
CCarCtrl::MapCouldMoveInThisArea(float x, float y)
{
	// bridge moves up and down
	return x > -342.0f && x < -219.0f &&
		y > -677.0f && y < -580.0f;
}

STARTPATCHES
InjectHook(0x416580, &CCarCtrl::GenerateRandomCars, PATCH_JUMP);
InjectHook(0x417EC0, &CCarCtrl::ChooseModel, PATCH_JUMP);
InjectHook(0x418320, &CCarCtrl::RemoveDistantCars, PATCH_JUMP);
InjectHook(0x418430, &CCarCtrl::PossiblyRemoveVehicle, PATCH_JUMP);
InjectHook(0x418C10, &CCarCtrl::FindMaximumSpeedForThisCarInTraffic, PATCH_JUMP);
InjectHook(0x41A590, &CCarCtrl::FindAngleToWeaveThroughTraffic, PATCH_JUMP);
InjectHook(0x41BA50, &CCarCtrl::PickNextNodeAccordingStrategy, PATCH_JUMP);
ENDPATCHES
