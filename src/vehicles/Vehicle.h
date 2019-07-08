#pragma once

#include "Physical.h"
#include "AutoPilot.h"

class CPed;
class CFire;
struct tHandlingData;

enum {
	RANDOM_VEHICLE = 1,
	MISSION_VEHICLE = 2,
	PARKED_VEHICLE = 3,
	PERMANENT_VEHICLE = 4,
};

enum eCarLock {
	CARLOCK_NOT_USED,
	CARLOCK_UNLOCKED,
	CARLOCK_LOCKED,
	CARLOCK_LOCKOUT_PLAYER_ONLY,
	CARLOCK_LOCKED_PLAYER_INSIDE,
	CARLOCK_COP_CAR,
	CARLOCK_FORCE_SHUT_DOORS,
	CARLOCK_SKIP_SHUT_DOORS
};


enum eCarNodes
{
	CAR_WHEEL_RF = 1,
	CAR_WHEEL_RM,
	CAR_WHEEL_RB,
	CAR_WHEEL_LF,
	CAR_WHEEL_LM,
	CAR_WHEEL_LB,
	CAR_BUMP_FRONT,
	CAR_BUMP_REAR,
	CAR_WING_RF,
	CAR_WING_RR,
	CAR_DOOR_RF,
	CAR_DOOR_RR,
	CAR_WING_LF,
	CAR_WING_LR,
	CAR_DOOR_LF,
	CAR_DOOR_LR,
	CAR_BONNET,
	CAR_BOOT,
	CAR_WINDSCREEN,
	NUM_CAR_NODES,
};

enum
{
	CAR_POS_HEADLIGHTS,
	CAR_POS_TAILLIGHTS,
	CAR_POS_FRONTSEAT,
	CAR_POS_BACKSEAT,
	CAR_POS_EXHAUST		= 9,
};

enum eDoors
{
	DOOR_BONNET = 0,
	DOOR_BOOT,
	DOOR_FRONT_LEFT,
	DOOR_FRONT_RIGHT,
	DOOR_REAR_LEFT,
	DOOR_REAR_RIGHT
};

enum ePanels
{
	VEHPANEL_FRONT_LEFT,
	VEHPANEL_FRONT_RIGHT,
	VEHPANEL_REAR_LEFT,
	VEHPANEL_REAR_RIGHT,
	VEHPANEL_WINDSCREEN,
	VEHBUMPER_FRONT,
	VEHBUMPER_REAR,
};

enum eLights
{
	VEHLIGHT_FRONT_LEFT,
	VEHLIGHT_FRONT_RIGHT,
	VEHLIGHT_REAR_LEFT,
	VEHLIGHT_REAR_RIGHT,
};

enum eWheels
{
	VEHWHEEL_FRONT_LEFT,
	VEHWHEEL_FRONT_RIGHT,
	VEHWHEEL_REAR_LEFT,
	VEHWHEEL_REAR_RIGHT,
};

enum
{
	CAR_PIECE_WHEEL_LF = 13,
	CAR_PIECE_WHEEL_LR,
	CAR_PIECE_WHEEL_RF,
	CAR_PIECE_WHEEL_RR,
};

class CVehicle : public CPhysical
{
public:
	// 0x128
	tHandlingData *m_handling;
	CAutoPilot m_autoPilot;
	uint8 m_currentColour1;
	uint8 m_currentColour2;
	uint8 m_aExtras[2];
	int16 m_nAlarmState; // m_nWantedStarsOnEnter on DK22
	int16 m_nMissionValue;
	CPed *pDriver;
	CPed *pPassengers[8];
	uint8 m_nNumPassengers;
	int8 m_nNumGettingIn;
	int8 m_nGettingInFlags;
	int8 m_nGettingOutFlags;
	uint8 m_nNumMaxPassengers;
	char field_1CD[19];
	CEntity *m_pCurSurface;
	CFire *m_pCarFire;
	float m_fSteerAngle;
	float m_fGasPedal;
	float m_fBreakPedal;
	uint8 VehicleCreatedBy;

	// cf. https://github.com/DK22Pac/plugin-sdk/blob/master/plugin_sa/game_sa/CVehicle.h from R*
	uint8 bIsLawEnforcer: 1; // Is this guy chasing the player at the moment
	uint8 bIsAmbulanceOnDuty: 1; // Ambulance trying to get to an accident
	uint8 bIsFireTruckOnDuty: 1; // Firetruck trying to get to a fire
	uint8 bIsLocked: 1; // Is this guy locked by the script (cannot be removed)
	uint8 bEngineOn: 1; // For sound purposes. Parked cars have their engines switched off (so do destroyed cars)
	uint8 bIsHandbrakeOn: 1; // How's the handbrake doing ?
	uint8 bLightsOn: 1; // Are the lights switched on ?
	uint8 bFreebies: 1; // Any freebies left in this vehicle ?

	uint8 bIsVan: 1; // Is this vehicle a van (doors at back of vehicle)
	uint8 bIsBus: 1; // Is this vehicle a bus
	uint8 bIsBig: 1; // Is this vehicle a bus
	uint8 bLowVehicle: 1; // Need this for sporty type cars to use low getting-in/out anims
	uint8 m_veh_flagB10 : 1;
	uint8 m_veh_flagB20 : 1;
	uint8 m_veh_flagB40 : 1;
	uint8 m_veh_flagB80 : 1;

	uint8 m_veh_flagC1 : 1;
	uint8 bIsDamaged : 1;
	uint8 m_veh_flagC4 : 1;
	uint8 m_veh_flagC8 : 1;
	uint8 m_veh_flagC10 : 1;
	uint8 m_veh_flagC20 : 1;
	uint8 m_veh_flagC40 : 1;
	uint8 m_veh_flagC80 : 1;

	uint8 m_veh_flagD1 : 1;
	uint8 m_veh_flagD2 : 1;
	uint8 m_veh_flagD4 : 1;
	uint8 m_veh_flagD8 : 1;
	uint8 bRecordedForReplay : 1;
	uint8 m_veh_flagD20 : 1;
	uint8 m_veh_flagD40 : 1;
	uint8 m_veh_flagD80 : 1;

	int8 field_1F9;
	uint8 m_nAmmoInClip;    // Used to make the guns on boat do a reload (20 by default)
	int8 field_1FB;
	int8 field_1FC[4];
	float m_fHealth;           // 1000.0f = full health. 0 -> explode
	uint8 m_nCurrentGear;
	int8 field_205[3];
	int field_208;
	uint32 m_nGunFiringTime;    // last time when gun on vehicle was fired (used on boats)
	uint32 m_nTimeOfDeath;
	int16 field_214;
	int16 m_nBombTimer;        // goes down with each frame
	CPed *m_pWhoDetonatedMe;
	float field_21C;
	float field_220;
	eCarLock m_nDoorLock;
	int8 m_nLastWeaponDamage; // see eWeaponType, -1 if no damage
	int8 m_nRadioStation;
	int8 field_22A;
	int8 field_22B;
	uint8 m_nCarHornTimer;
	int8 field_22D;
	uint8 m_nSirenOrAlarm;
	int8 field_22F;
	// TODO: this is an array
	CStoredCollPoly m_frontCollPoly;     // poly which is under front part of car
	CStoredCollPoly m_rearCollPoly;      // poly which is under rear part of car
	float m_fSteerRatio;
	eVehicleType m_vehType;

	static void *operator new(size_t);
	static void *operator new(size_t sz, int slot);
	static void operator delete(void*, size_t);
	static void operator delete(void*, int);

	~CVehicle(void);
	// from CEntity
	void SetModelIndex(uint32 id);
	bool SetupLighting(void);
	void RemoveLighting(bool);
	void FlagToDestroyWhenNextProcessed(void) {}

	virtual void ProcessControlInputs(uint8) {}
	virtual void GetComponentWorldPosition(int32 component, CVector &pos) {}
	virtual bool IsComponentPresent(int32 component) { return false; }
	virtual void SetComponentRotation(int32 component, CVector rotation) {}
	virtual void OpenDoor(int32, eDoors door, float) {}
	virtual void ProcessOpenDoor(uint32, uint32, float) {}
	virtual bool IsDoorReady(eDoors door) { return false; }
	virtual bool IsDoorFullyOpen(eDoors door) { return false; }
	virtual bool IsDoorClosed(eDoors door) { return false; }
	virtual bool IsDoorMissing(eDoors door) { return false; }
	virtual void RemoveRefsToVehicle(CEntity *ent) {}
	virtual void BlowUpCar(CEntity *ent) {}
	virtual bool SetUpWheelColModel(CColModel *colModel) { return false; }
	virtual void BurstTyre(uint8 tyre) {}
	virtual bool IsRoomForPedToLeaveCar(uint32, CVector *) { return false;}
	virtual float GetHeightAboveRoad(void);
	virtual void PlayCarHorn(void) {}

	bool IsCar(void) { return m_vehType == VEHICLE_TYPE_CAR; }
	bool IsBoat(void) { return m_vehType == VEHICLE_TYPE_BOAT; }
	bool IsTrain(void) { return m_vehType == VEHICLE_TYPE_TRAIN; }
	bool IsHeli(void) { return m_vehType == VEHICLE_TYPE_HELI; }
	bool IsPlane(void) { return m_vehType == VEHICLE_TYPE_PLANE; }
	bool IsLawEnforcementVehicle(void);
	void ChangeLawEnforcerState(uint8 enable);
	bool UsesSiren(uint32 id);
	bool IsVehicleNormal(void);
	bool CarHasRoof(void);
	bool IsUpsideDown(void);
	bool IsOnItsSide(void);
	bool CanBeDeleted(void);
	bool CanPedOpenLocks(CPed *ped);
	bool CanPedEnterCar(void);
	bool CanPedExitCar(void);
	// do these two actually return something?
	CPed *SetUpDriver(void);
	CPed *SetupPassenger(int n);
	void SetDriver(CPed *driver);
	bool AddPassenger(CPed *passenger);
	bool AddPassenger(CPed *passenger, uint8 n);
	void RemovePassenger(CPed *passenger);
	void RemoveDriver(void);
	void ProcessCarAlarm(void);
	bool IsSphereTouchingVehicle(float sx, float sy, float sz, float radius);
	
	static bool &bWheelsOnlyCheat;
	static bool &bAllDodosCheat;
	static bool &bCheat3;
	static bool &bCheat4;
	static bool &bCheat5;
	static bool &m_bDisableMouseSteering;
};

static_assert(sizeof(CVehicle) == 0x288, "CVehicle: error");
static_assert(offsetof(CVehicle, m_pCurSurface) == 0x1E0, "CVehicle: error");
static_assert(offsetof(CVehicle, m_nAlarmState) == 0x1A0, "CVehicle: error");
static_assert(offsetof(CVehicle, m_nLastWeaponDamage) == 0x228, "CVehicle: error");

inline uint8 GetVehDoorFlag(int32 carnode) {
	switch (carnode) {
	case CAR_DOOR_LF:
		return 1;
	case CAR_DOOR_LR:
		return 2;
	case CAR_DOOR_RF:
		return 4;
	case CAR_DOOR_RR:
		return 8;
	default:
		return 0;
	}
}
