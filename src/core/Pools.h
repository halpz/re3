#pragma once

#include "templates.h"
#include "Lists.h"
#include "Treadable.h"
#include "Object.h"
#include "CutsceneHead.h"
#include "PlayerPed.h"
#include "Automobile.h"
#include "DummyPed.h"
#include "AudioScriptObject.h"

typedef CPool<CPtrNode> CCPtrNodePool;
typedef CPool<CEntryInfoNode> CEntryInfoNodePool;
typedef CPool<CPed,CPlayerPed> CPedPool;
typedef CPool<CVehicle,CAutomobile> CVehiclePool;
typedef CPool<CBuilding> CBuildingPool;
typedef CPool<CTreadable> CTreadablePool;
typedef CPool<CObject, CCutsceneHead> CObjectPool;
typedef CPool<CDummy, CDummyPed> CDummyPool;
typedef CPool<cAudioScriptObject> CAudioScriptObjectPool;

class CPools
{
	static CCPtrNodePool *ms_pPtrNodePool;
	static CEntryInfoNodePool *ms_pEntryInfoNodePool;
	static CPedPool *ms_pPedPool;
	static CVehiclePool *ms_pVehiclePool;
	static CBuildingPool *ms_pBuildingPool;
	static CTreadablePool *ms_pTreadablePool;
	static CObjectPool *ms_pObjectPool;
	static CDummyPool *ms_pDummyPool;
	static CAudioScriptObjectPool *ms_pAudioScriptObjectPool;
public:
	static CCPtrNodePool *GetPtrNodePool(void) { return ms_pPtrNodePool; }
	static CEntryInfoNodePool *GetEntryInfoNodePool(void) { return ms_pEntryInfoNodePool; }
	static CPedPool *GetPedPool(void) { return ms_pPedPool; }
	static CVehiclePool *GetVehiclePool(void) { return ms_pVehiclePool; }
	static CBuildingPool *GetBuildingPool(void) { return ms_pBuildingPool; }
	static CTreadablePool *GetTreadablePool(void) { return ms_pTreadablePool; }
	static CObjectPool *GetObjectPool(void) { return ms_pObjectPool; }
	static CDummyPool *GetDummyPool(void) { return ms_pDummyPool; }
	static CAudioScriptObjectPool *GetAudioScriptObjectPool(void) { return ms_pAudioScriptObjectPool; }

	static void Initialise(void);
	static void ShutDown(void);
	static int32 GetPedRef(CPed *ped);
	static CPed *GetPed(int32 handle);
	static int32 GetVehicleRef(CVehicle *vehicle);
	static CVehicle *GetVehicle(int32 handle);
	static int32 GetObjectRef(CObject *object);
	static CObject *GetObject(int32 handle);
	static void CheckPoolsEmpty();
	static void MakeSureSlotInObjectPoolIsEmpty(int32 slot);
	static void LoadObjectPool(uint8 *buf, uint32 size);
	static void LoadPedPool(uint8 *buf, uint32 size);
	static void LoadVehiclePool(uint8 *buf, uint32 size);
	static void SaveObjectPool(uint8 *buf, uint32 *size);
	static void SavePedPool(uint8 *buf, uint32 *size);
	static void SaveVehiclePool(uint8 *buf, uint32 *size);
};

#ifdef COMPATIBLE_SAVES

// Following stuff allows changing structures like CPed, CAutomobile and CBoat without breaking compatibility with original saves.

// For saving we have to assume that sizeof(void*) == 4, so we use int32 everywhere.
// It will break some pointers, but saving them makes no sense anyway.

struct CEntityProperties
{
	// these properties are defined exactly as in original game

	uint32 m_type : 3;
	uint32 m_status : 5;

	// flagsA
	uint32 bUsesCollision : 1;			// does entity use collision
	uint32 bCollisionProcessed : 1;		// has object been processed by a ProcessEntityCollision function
	uint32 bIsStatic : 1;				// is entity static
	uint32 bHasContacted : 1;			// has entity processed some contact forces
	uint32 bPedPhysics : 1;
	uint32 bIsStuck : 1;				// is entity stuck
	uint32 bIsInSafePosition : 1;		// is entity in a collision free safe position
	uint32 bUseCollisionRecords : 1;

	// flagsB
	uint32 bWasPostponed : 1;			// was entity control processing postponed
	uint32 bExplosionProof : 1;
	uint32 bIsVisible : 1;				//is the entity visible
	uint32 bHasCollided : 1;
	uint32 bRenderScorched : 1;
	uint32 bHasBlip : 1;
	uint32 bIsBIGBuilding : 1;			// Set if this entity is a big building
	// VC inserts one more flag here: if drawdist <= 2000
	uint32 bRenderDamaged : 1;			// use damaged LOD models for objects with applicable damage

	// flagsC
	uint32 bBulletProof : 1;
	uint32 bFireProof : 1;
	uint32 bCollisionProof : 1;
	uint32 bMeleeProof : 1;
	uint32 bOnlyDamagedByPlayer : 1;
	uint32 bStreamingDontDelete : 1;	// Dont let the streaming remove this 
	uint32 bZoneCulled : 1;
	uint32 bZoneCulled2 : 1;    // only treadables+10m

	// flagsD
	uint32 bRemoveFromWorld : 1;		// remove this entity next time it should be processed
	uint32 bHasHitWall : 1;				// has collided with a building (changes subsequent collisions)
	uint32 bImBeingRendered : 1;		// don't delete me because I'm being rendered
	uint32 bTouchingWater : 1;	// used by cBuoyancy::ProcessBuoyancy
	uint32 bIsSubway : 1;	// set when subway, but maybe different meaning?
	uint32 bDrawLast : 1;				// draw object last
	uint32 bNoBrightHeadLights : 1;
	uint32 bDoNotRender : 1;

	// flagsE
	uint32 bDistanceFade : 1;			// Fade entity because it is far away
	uint32 m_flagE2 : 1;

	void Store(CEntity* pEntity)
	{
		m_type = pEntity->GetType();
		m_status = pEntity->GetStatus();
		bUsesCollision = pEntity->bUsesCollision;
		bCollisionProcessed = pEntity->bCollisionProcessed;
		bIsStatic = pEntity->bIsStatic;
		bHasContacted = pEntity->bHasContacted;
		bPedPhysics = pEntity->bPedPhysics;
		bIsStuck = pEntity->bIsStuck;
		bIsInSafePosition = pEntity->bIsInSafePosition;
		bUseCollisionRecords = pEntity->bUseCollisionRecords;
		bWasPostponed = pEntity->bWasPostponed;
		bExplosionProof = pEntity->bExplosionProof;
		bIsVisible = pEntity->bIsVisible;
		bHasCollided = pEntity->bHasCollided;
		bRenderScorched = pEntity->bRenderScorched;
		bHasBlip = pEntity->bHasBlip;
		bIsBIGBuilding = pEntity->bIsBIGBuilding;
		bRenderDamaged = pEntity->bRenderDamaged;
		bBulletProof = pEntity->bBulletProof;
		bFireProof = pEntity->bFireProof;
		bCollisionProof = pEntity->bCollisionProof;
		bMeleeProof = pEntity->bMeleeProof;
		bOnlyDamagedByPlayer = pEntity->bOnlyDamagedByPlayer;
		bStreamingDontDelete = pEntity->bStreamingDontDelete;
		bZoneCulled = pEntity->bZoneCulled;
		bZoneCulled2 = pEntity->bZoneCulled2;
		bRemoveFromWorld = pEntity->bRemoveFromWorld;
		bHasHitWall = pEntity->bHasHitWall;
		bImBeingRendered = pEntity->bImBeingRendered;
		bTouchingWater = pEntity->bTouchingWater;
		bIsSubway = pEntity->bIsSubway;
		bDrawLast = pEntity->bDrawLast;
		bNoBrightHeadLights = pEntity->bNoBrightHeadLights;
		bDoNotRender = pEntity->bDoNotRender;
		bDistanceFade = pEntity->bDistanceFade;
		m_flagE2 = pEntity->m_flagE2;
	}

	void Restore(CEntity* pEntity)
	{
		pEntity->SetType((eEntityType)m_type);
		pEntity->SetStatus((eEntityStatus)m_status);
		pEntity->bUsesCollision = bUsesCollision;
		pEntity->bCollisionProcessed = bCollisionProcessed;
		pEntity->bIsStatic = bIsStatic;
		pEntity->bHasContacted = bHasContacted;
		pEntity->bPedPhysics = bPedPhysics;
		pEntity->bIsStuck = bIsStuck;
		pEntity->bIsInSafePosition = bIsInSafePosition;
		pEntity->bUseCollisionRecords = bUseCollisionRecords;
		pEntity->bWasPostponed = bWasPostponed;
		pEntity->bExplosionProof = bExplosionProof;
		pEntity->bIsVisible = bIsVisible;
		pEntity->bHasCollided = bHasCollided;
		pEntity->bRenderScorched = bRenderScorched;
		pEntity->bHasBlip = bHasBlip;
		pEntity->bIsBIGBuilding = bIsBIGBuilding;
		pEntity->bRenderDamaged = bRenderDamaged;
		pEntity->bBulletProof = bBulletProof;
		pEntity->bFireProof = bFireProof;
		pEntity->bCollisionProof = bCollisionProof;
		pEntity->bMeleeProof = bMeleeProof;
		pEntity->bOnlyDamagedByPlayer = bOnlyDamagedByPlayer;
		pEntity->bStreamingDontDelete = bStreamingDontDelete;
		pEntity->bZoneCulled = bZoneCulled;
		pEntity->bZoneCulled2 = bZoneCulled2;
		pEntity->bRemoveFromWorld = bRemoveFromWorld;
		pEntity->bHasHitWall = bHasHitWall;
		pEntity->bImBeingRendered = bImBeingRendered;
		pEntity->bTouchingWater = bTouchingWater;
		pEntity->bIsSubway = bIsSubway;
		pEntity->bDrawLast = bDrawLast;
		pEntity->bNoBrightHeadLights = bNoBrightHeadLights;
		pEntity->bDoNotRender = bDoNotRender;
		pEntity->bDistanceFade = bDistanceFade;
		pEntity->m_flagE2 = m_flagE2;
	}
};

VALIDATE_SIZE(CEntityProperties, 8);

struct CAutoPilot_FS
{
	int32 m_nCurrentRouteNode;
	int32 m_nNextRouteNode;
	int32 m_nPrevRouteNode;
	uint32 m_nTimeEnteredCurve;
	uint32 m_nTimeToSpendOnCurrentCurve;
	uint32 m_nCurrentPathNodeInfo;
	uint32 m_nNextPathNodeInfo;
	uint32 m_nPreviousPathNodeInfo;
	uint32 m_nAntiReverseTimer;
	uint32 m_nTimeToStartMission;
	int8 m_nPreviousDirection;
	int8 m_nCurrentDirection;
	int8 m_nNextDirection;
	int8 m_nCurrentLane;
	int8 m_nNextLane;
	uint8 m_nDrivingStyle;
	uint8 m_nCarMission;
	uint8 m_nTempAction;
	uint32 m_nTimeTempAction;
	float m_fMaxTrafficSpeed;
	uint8 m_nCruiseSpeed;
	uint8 m_bSlowedDownBecauseOfCars : 1;
	uint8 m_bSlowedDownBecauseOfPeds : 1;
	uint8 m_bStayInCurrentLevel : 1;
	uint8 m_bStayInFastLane : 1;
	uint8 m_bIgnorePathfinding : 1;
	float m_vecDestinationCoors[3];
	int32 m_aPathFindNodesInfo[8]; // CPathNode* [NUM_PATH_NODES_IN_AUTOPILOT]
	int16 m_nPathFindNodesCount;
	int32 m_pTargetCar;
	
	void Store(CAutoPilot* pAutoPilot)
	{
		m_nCurrentRouteNode = pAutoPilot->m_nCurrentRouteNode;
		m_nNextRouteNode = pAutoPilot->m_nNextRouteNode;
		m_nPrevRouteNode = pAutoPilot->m_nPrevRouteNode;
		m_nTimeEnteredCurve = pAutoPilot->m_nTimeEnteredCurve;
		m_nTimeToSpendOnCurrentCurve = pAutoPilot->m_nTimeToSpendOnCurrentCurve;
		m_nCurrentPathNodeInfo = pAutoPilot->m_nCurrentPathNodeInfo;
		m_nNextPathNodeInfo = pAutoPilot->m_nNextPathNodeInfo;
		m_nPreviousPathNodeInfo = pAutoPilot->m_nPreviousPathNodeInfo;
		m_nAntiReverseTimer = pAutoPilot->m_nAntiReverseTimer;
		m_nTimeToStartMission = pAutoPilot->m_nTimeToStartMission;
		m_nPreviousDirection = pAutoPilot->m_nPreviousDirection;
		m_nCurrentDirection = pAutoPilot->m_nCurrentDirection;
		m_nNextDirection = pAutoPilot->m_nNextDirection;
		m_nCurrentLane = pAutoPilot->m_nCurrentLane;
		m_nNextLane = pAutoPilot->m_nNextLane;
		m_nDrivingStyle = pAutoPilot->m_nDrivingStyle;
		m_nCarMission = pAutoPilot->m_nCarMission;
		m_nTempAction = pAutoPilot->m_nTempAction;
		m_nTimeTempAction = pAutoPilot->m_nTimeTempAction;
		m_fMaxTrafficSpeed = pAutoPilot->m_fMaxTrafficSpeed;
		m_nCruiseSpeed = pAutoPilot->m_nCruiseSpeed;
		m_bSlowedDownBecauseOfCars = pAutoPilot->m_bSlowedDownBecauseOfCars;
		m_bSlowedDownBecauseOfPeds = pAutoPilot->m_bSlowedDownBecauseOfPeds;
		m_bStayInCurrentLevel = pAutoPilot->m_bStayInCurrentLevel;
		m_bStayInFastLane = pAutoPilot->m_bStayInFastLane;
		m_bIgnorePathfinding  = pAutoPilot->m_bIgnorePathfinding;
		m_vecDestinationCoors[0] = pAutoPilot->m_vecDestinationCoors.x;
		m_vecDestinationCoors[1] = pAutoPilot->m_vecDestinationCoors.y;
		m_vecDestinationCoors[2] = pAutoPilot->m_vecDestinationCoors.z;
		for (int i = 0; i < 8; i++)
			m_aPathFindNodesInfo[i] = 0;
		m_nPathFindNodesCount = pAutoPilot->m_nPathFindNodesCount;
		m_pTargetCar = 0;
	}

	void Restore(CAutoPilot* pAutoPilot)
	{
		pAutoPilot->m_nCurrentRouteNode = m_nCurrentRouteNode;
		pAutoPilot->m_nNextRouteNode = m_nNextRouteNode;
		pAutoPilot->m_nPrevRouteNode = m_nPrevRouteNode;
		pAutoPilot->m_nTimeEnteredCurve = m_nTimeEnteredCurve;
		pAutoPilot->m_nTimeToSpendOnCurrentCurve = m_nTimeToSpendOnCurrentCurve;
		pAutoPilot->m_nCurrentPathNodeInfo = m_nCurrentPathNodeInfo;
		pAutoPilot->m_nNextPathNodeInfo = m_nNextPathNodeInfo;
		pAutoPilot->m_nPreviousPathNodeInfo = m_nPreviousPathNodeInfo;
		pAutoPilot->m_nAntiReverseTimer = m_nAntiReverseTimer;
		pAutoPilot->m_nTimeToStartMission = m_nTimeToStartMission;
		pAutoPilot->m_nPreviousDirection = m_nPreviousDirection;
		pAutoPilot->m_nCurrentDirection = m_nCurrentDirection;
		pAutoPilot->m_nNextDirection = m_nNextDirection;
		pAutoPilot->m_nCurrentLane = m_nCurrentLane;
		pAutoPilot->m_nNextLane = m_nNextLane;
		pAutoPilot->m_nDrivingStyle = (eCarDrivingStyle)m_nDrivingStyle;
		pAutoPilot->m_nCarMission = (eCarMission)m_nCarMission;
		pAutoPilot->m_nTempAction = (eCarTempAction)m_nTempAction;
		pAutoPilot->m_nTimeTempAction = m_nTimeTempAction;
		pAutoPilot->m_fMaxTrafficSpeed = m_fMaxTrafficSpeed;
		pAutoPilot->m_nCruiseSpeed = m_nCruiseSpeed;
		pAutoPilot->m_bSlowedDownBecauseOfCars = m_bSlowedDownBecauseOfCars;
		pAutoPilot->m_bSlowedDownBecauseOfPeds = m_bSlowedDownBecauseOfPeds;
		pAutoPilot->m_bStayInCurrentLevel = m_bStayInCurrentLevel;
		pAutoPilot->m_bStayInFastLane = m_bStayInFastLane;
		pAutoPilot->m_bIgnorePathfinding = m_bIgnorePathfinding;
		pAutoPilot->m_vecDestinationCoors.x = m_vecDestinationCoors[0];
		pAutoPilot->m_vecDestinationCoors.y = m_vecDestinationCoors[1];
		pAutoPilot->m_vecDestinationCoors.z = m_vecDestinationCoors[2];
		for (int i = 0; i < NUM_PATH_NODES_IN_AUTOPILOT; i++)
			pAutoPilot->m_aPathFindNodesInfo[i] = nil;
		pAutoPilot->m_nPathFindNodesCount = m_nPathFindNodesCount;
		pAutoPilot->m_pTargetCar = nil;
	}
};

struct CMatrix_FS
{
	float right[3];
	uint8 gap1[4];
	float forward[3];
	uint8 gap2[4];
	float up[3];
	uint8 gap3[4];
	float pos[3];
	uint8 gap4[12];

	void Store(CMatrix* pMatrix)
	{
		right[0] = pMatrix->GetRight().x;
		right[1] = pMatrix->GetRight().y;
		right[2] = pMatrix->GetRight().z;
		forward[0] = pMatrix->GetForward().x;
		forward[1] = pMatrix->GetForward().y;
		forward[2] = pMatrix->GetForward().z;
		up[0] = pMatrix->GetUp().x;
		up[1] = pMatrix->GetUp().y;
		up[2] = pMatrix->GetUp().z;
		pos[0] = pMatrix->GetPosition().x;
		pos[1] = pMatrix->GetPosition().y;
		pos[2] = pMatrix->GetPosition().z;
	}

	void Restore(CMatrix* pMatrix)
	{
		CMatrix tmp;
		tmp.GetRight().x = right[0];
		tmp.GetRight().y = right[1];
		tmp.GetRight().z = right[2];
		tmp.GetForward().x = forward[0];
		tmp.GetForward().y = forward[1];
		tmp.GetForward().z = forward[2];
		tmp.GetUp().x = up[0];
		tmp.GetUp().y = up[1];
		tmp.GetUp().z = up[2];
		tmp.GetPosition().x = pos[0];
		tmp.GetPosition().y = pos[1];
		tmp.GetPosition().z = pos[2];
		*pMatrix = tmp;
	}
};

VALIDATE_SIZE(CMatrix_FS, 72);

struct CVehicle_FS
{
	uint32 vtable;
	CMatrix_FS matrix;
	uint8 gap1[4];
	CEntityProperties properties;
	uint8 gap2[212];
	CAutoPilot_FS AutoPilot;
	uint8 m_currentColour1;
	uint8 m_currentColour2;
	uint8 gap3[2];
	int16 m_nAlarmState;
	int8 gap4[43];
	uint8 m_nNumMaxPassengers;
	float field_1D0[4];
	uint8 gap5[8];
	float m_fSteerAngle;
	float m_fGasPedal;
	float m_fBrakePedal;
	uint8 VehicleCreatedBy;

	// cf. https://github.com/DK22Pac/plugin-sdk/blob/master/plugin_sa/game_sa/CVehicle.h from R*
	uint8 bIsLawEnforcer : 1; // Is this guy chasing the player at the moment
	uint8 gap_b1 : 1;
	uint8 gap_b2 : 1;
	uint8 bIsLocked : 1; // Is this guy locked by the script (cannot be removed)
	uint8 bEngineOn : 1; // For sound purposes. Parked cars have their engines switched off (so do destroyed cars)
	uint8 bIsHandbrakeOn : 1; // How's the handbrake doing ?
	uint8 bLightsOn : 1; // Are the lights switched on ?
	uint8 bFreebies : 1; // Any freebies left in this vehicle ?

	uint8 gap6[3];

	uint8 gap7[6];
	float m_fHealth;           // 1000.0f = full health. 250.0f = fire. 0 -> explode
	uint8 m_nCurrentGear;
	float m_fChangeGearTime;
	uint8 gap8[4];
	uint32 m_nTimeOfDeath;
	uint8 gap9[2];
	int16 m_nBombTimer;
	uint8 gap10[12];
	int8 m_nDoorLock;
	uint8 gap11[96];

	void Store(CVehicle* pVehicle)
	{
		matrix.Store(&pVehicle->GetMatrix());
		VehicleCreatedBy = pVehicle->VehicleCreatedBy;
		m_currentColour1 = pVehicle->m_currentColour1;
		m_currentColour2 = pVehicle->m_currentColour2;
		m_nAlarmState = pVehicle->m_nAlarmState;
		m_nNumMaxPassengers = pVehicle->m_nNumMaxPassengers;
		field_1D0[0] = pVehicle->field_1D0[0];
		field_1D0[1] = pVehicle->field_1D0[1];
		field_1D0[2] = pVehicle->field_1D0[2];
		field_1D0[3] = pVehicle->field_1D0[3];
		m_fSteerAngle = pVehicle->m_fSteerAngle;
		m_fGasPedal = pVehicle->m_fGasPedal;
		m_fBrakePedal = pVehicle->m_fBrakePedal;
		bIsLawEnforcer = pVehicle->bIsLawEnforcer;
		bIsLocked = pVehicle->bIsLocked;
		bEngineOn = pVehicle->bEngineOn;
		bIsHandbrakeOn = pVehicle->bIsHandbrakeOn;
		bLightsOn = pVehicle->bLightsOn;
		bFreebies = pVehicle->bFreebies;
		m_fHealth = pVehicle->m_fHealth;
		m_nCurrentGear = pVehicle->m_nCurrentGear;
		m_fChangeGearTime = pVehicle->m_fChangeGearTime;
		m_nTimeOfDeath = pVehicle->m_nTimeOfDeath;
#ifdef FIX_BUGS //must be copypaste
		m_nBombTimer = pVehicle->m_nBombTimer;
#else
		m_nTimeOfDeath = pVehicle->m_nTimeOfDeath;
#endif
		m_nDoorLock = pVehicle->m_nDoorLock;
		properties.Store(pVehicle);
		AutoPilot.Store(&pVehicle->AutoPilot);
	}
	
	void Restore(CVehicle* pVehicle)
	{
		matrix.Restore(&pVehicle->GetMatrix());
		pVehicle->VehicleCreatedBy = VehicleCreatedBy;
		pVehicle->m_currentColour1 = m_currentColour1;
		pVehicle->m_currentColour2 = m_currentColour2;
		pVehicle->m_nAlarmState = m_nAlarmState;
		pVehicle->m_nNumMaxPassengers = m_nNumMaxPassengers;
		pVehicle->field_1D0[0] = field_1D0[0];
		pVehicle->field_1D0[1] = field_1D0[1];
		pVehicle->field_1D0[2] = field_1D0[2];
		pVehicle->field_1D0[3] = field_1D0[3];
		pVehicle->m_fSteerAngle = m_fSteerAngle;
		pVehicle->m_fGasPedal = m_fGasPedal;
		pVehicle->m_fBrakePedal = m_fBrakePedal;
		pVehicle->bIsLawEnforcer = bIsLawEnforcer;
		pVehicle->bIsLocked = bIsLocked;
		pVehicle->bEngineOn = bEngineOn;
		pVehicle->bIsHandbrakeOn = bIsHandbrakeOn;
		pVehicle->bLightsOn = bLightsOn;
		pVehicle->bFreebies = bFreebies;
		pVehicle->m_fHealth = m_fHealth;
		pVehicle->m_nCurrentGear = m_nCurrentGear;
		pVehicle->m_fChangeGearTime = m_fChangeGearTime;
		pVehicle->m_nTimeOfDeath = m_nTimeOfDeath;
#ifdef FIX_BUGS //must be copypaste
		pVehicle->m_nBombTimer = m_nBombTimer;
#else
		pVehicle->m_nTimeOfDeath = m_nTimeOfDeath;
#endif
		pVehicle->m_nDoorLock = (eCarLock)m_nDoorLock;
		properties.Restore(pVehicle);
		AutoPilot.Restore(&pVehicle->AutoPilot);
	}
};

VALIDATE_SIZE(CVehicle_FS, 648);

static_assert(sizeof(CDamageManager) < 1448 - sizeof(CVehicle_FS), "CDamageManager size too big to keep saves compatible");

struct CAutomobile_FS
{
	CVehicle_FS vehicle;
	CDamageManager Damage;
	char gap[1448 - sizeof(CVehicle_FS) - sizeof(CDamageManager)]; // even allows increasing size of CDamageManager
};

struct CBoat_FS
{
	CVehicle_FS vehicle;
	char gap[1156 - sizeof(CVehicle_FS)];
};

VALIDATE_SIZE(CAutomobile_FS, 1448);
VALIDATE_SIZE(CBoat_FS, 1156);

struct CWeapon_FS
{
	int32 m_eWeaponType;
	int32 m_eWeaponState;
	uint32 m_nAmmoInClip;
	uint32 m_nAmmoTotal;
	uint32 m_nTimer;
	bool m_bAddRotOffset;

	void Store(CWeapon* pWeapon)
	{
		m_eWeaponType = pWeapon->m_eWeaponType;
		m_eWeaponState = pWeapon->m_eWeaponState;
		m_nAmmoInClip = pWeapon->m_nAmmoInClip;
		m_nAmmoTotal = pWeapon->m_nAmmoTotal;
		m_nTimer = pWeapon->m_nTimer;
		m_bAddRotOffset = pWeapon->m_bAddRotOffset;
	}

	void Restore(CWeapon* pWeapon)
	{
		pWeapon->m_eWeaponType = (eWeaponType)m_eWeaponType;
		pWeapon->m_eWeaponState = (eWeaponState)m_eWeaponState;
		pWeapon->m_nAmmoInClip = m_nAmmoInClip;
		pWeapon->m_nAmmoTotal = m_nAmmoTotal;
		pWeapon->m_nTimer = m_nTimer;
		pWeapon->m_bAddRotOffset = m_bAddRotOffset;
	}
};

static_assert(WEAPONTYPE_TOTAL_INVENTORY_WEAPONS == 13,
	"Saving struct needs to be changed by adding new weapons to existing space; or COMPATIBLE_SAVES needs to be undefined");

struct CPlayerPed_FS
{
	int32 vtable;
	int8 gap[48];
	float pos[3];
	uint8 gap_2[288];
	uint8 CharCreatedBy;
	uint8 gap_3[351];
	float m_fHealth;
	float m_fArmour;
	uint8 gap_4[148];

	CWeapon_FS m_weapons[13];
	int32 m_storedWeapon;
	uint8 m_currentWeapon;
	uint8 m_maxWeaponTypeAllowed;
	uint8 gap_5[178];
	float m_fMaxStamina;
	uint8 gap_6[28];
	int32 m_nTargettableObjects[4];
	uint8 gap_7[116];

	void StorePlayerPed(CPlayerPed* pPlayerPed)
	{
		for (int i = 0; i < 4; i++)
			m_nTargettableObjects[i] = pPlayerPed->m_nTargettableObjects[i];
		m_fMaxStamina = pPlayerPed->m_fMaxStamina;
	}

	void StorePed(CPed* pPed)
	{
		pos[0] = pPed->GetPosition().x;
		pos[1] = pPed->GetPosition().y;
		pos[2] = pPed->GetPosition().z;
		m_fHealth = pPed->m_fHealth;
		m_fArmour = pPed->m_fArmour;
		CharCreatedBy = pPed->CharCreatedBy;
		m_maxWeaponTypeAllowed = pPed->m_maxWeaponTypeAllowed;
		for (int i = 0; i < 13; i++)
			m_weapons[i].Store(&pPed->m_weapons[i]);
	}

	void RestorePlayerPed(CPlayerPed* pPlayerPed)
	{
		for (int i = 0; i < 4; i++)
			pPlayerPed->m_nTargettableObjects[i] = m_nTargettableObjects[i];
		pPlayerPed->m_fMaxStamina = m_fMaxStamina;
	}

	void RestorePed(CPed* pPed)
	{
		pPed->GetPosition().x = pos[0];
		pPed->GetPosition().y = pos[1];
		pPed->GetPosition().z = pos[2];
		pPed->m_fHealth = m_fHealth;
		pPed->m_fArmour = m_fArmour;
		pPed->CharCreatedBy = CharCreatedBy;
		pPed->m_maxWeaponTypeAllowed = m_maxWeaponTypeAllowed;
		for (int i = 0; i < 13; i++)
			 m_weapons[i].Restore(&pPed->m_weapons[i]);
	}
};

VALIDATE_SIZE(CPlayerPed_FS, 1520);

#endif
