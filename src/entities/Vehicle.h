#pragma once

#include "Physical.h"

class CPed;
class CFire;
struct tHandlingData;

enum {
	GETTING_IN_OUT_FL = 1,
	GETTING_IN_OUT_RL = 2,
	GETTING_IN_OUT_FR = 4,
	GETTING_IN_OUT_RR = 8
};

enum eCarLock : uint8 {
	CARLOCK_NOT_USED,
	CARLOCK_UNLOCKED,
	CARLOCK_LOCKED,
	CARLOCK_LOCKOUT_PLAYER_ONLY,
	CARLOCK_LOCKED_PLAYER_INSIDE,
	CARLOCK_COP_CAR,
	CARLOCK_FORCE_SHUT_DOORS,
	CARLOCK_SKIP_SHUT_DOORS
};

enum eVehicleModel : int32
{
  LANDSTAL = 0x0,
  IDAHO = 0x1,
  STINGER = 0x2,
  LINERUN = 0x3,
  PEREN = 0x4,
  SENTINEL = 0x5,
  PATRIOT = 0x6,
  FIRETRUK = 0x7,
  TRASH = 0x8,
  STRETCH = 0x9,
  MANANA = 0xA,
  INFERNUS = 0xB,
  BLISTA = 0xC,
  PONY = 0xD,
  MULE = 0xE,
  CHEETAH = 0xF,
  AMBULAN = 0x10,
  FBICAR = 0x11,
  MOONBEAM = 0x12,
  ESPERANT = 0x13,
  TAXI = 0x14,
  KURUMA = 0x15,
  BOBCAT = 0x16,
  MRWHOOP = 0x17,
  BFINJECT = 0x18,
  CORPSE = 0x19,
  POLICE = 0x1A,
  ENFORCER = 0x1B,
  SECURICA = 0x1C,
  BANSHEE = 0x1D,
  PREDATOR = 0x1E,
  BUS = 0x1F,
  RHINO = 0x20,
  BARRACKS = 0x21,
  TRAIN = 0x22,
  CHOPPER = 0x23,
  DODO = 0x24,
  COACH = 0x25,
  CABBIE = 0x26,
  STALLION = 0x27,
  RUMPO = 0x28,
  RCBANDIT = 0x29,
  BELLYUP = 0x2A,
  MRWONGS = 0x2B,
  MAFIA = 0x2C,
  YARDIE = 0x2D,
  YAKUZA = 0x2E,
  DIABLOS = 0x2F,
  COLUMB = 0x30,
  HOODS = 0x31,
  AIRTRAIN = 0x32,
  DEADDODO = 0x33,
  SPEEDER = 0x34,
  REEFER = 0x35,
  PANLANT = 0x36,
  FLATBED = 0x37,
  YANKEE = 0x38,
  ESCAPE = 0x39,
  BORGNINE = 0x3A,
  TOYZ = 0x3B,
  GHOST = 0x3C,
  CAR151 = 0x3D,
  CAR152 = 0x3E,
  CAR153 = 0x3F,
  CAR154 = 0x40,
  CAR155 = 0x41,
  CAR156 = 0x42,
  CAR157 = 0x43,
  CAR158 = 0x44,
  CAR159 = 0x45,
};

class CVehicle : public CPhysical
{
public:
	// 0x128
	tHandlingData *m_handling;
	uint8 stuff1[112];
	uint8 m_currentColour1;
	uint8 m_currentColour2;
	uint8 m_anExtras[2];
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
	uint8 m_nCreatedBy;        // eVehicleCreatedBy
	uint8 bIsLawEnforcer : 1;
	uint8 bIsAmbulanceOnDuty : 1;
	uint8 bIsFiretruckOnDuty : 1;
	uint8 m_veh_flagA8 : 1;
	uint8 m_veh_flagA10 : 1;
	uint8 m_veh_flagA20 : 1;
	uint8 m_veh_flagA40 : 1;
	uint8 m_veh_flagA80 : 1;
	uint8 bIsVan : 1;
	uint8 bIsBus : 1;
	uint8 bIsBig : 1;
	uint8 bIsLow : 1;
	uint8 m_veh_flagB10 : 1;
	uint8 m_veh_flagB20 : 1;
	uint8 m_veh_flagB40 : 1;
	uint8 m_veh_flagB80 : 1;
	uint8 m_veh_flagC1 : 1;
	uint8 m_veh_flagC2 : 1;
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
	uint8 m_nAmmoInClip[1];    // Used to make the guns on boat do a reload (20 by default)
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
	CStoredCollPoly m_frontCollPoly;     // poly which is under front part of car
	CStoredCollPoly m_rearCollPoly;      // poly which is under rear part of car
	float m_fSteerRatio;
	eVehicleType m_vehType;

	static void *operator new(size_t);
	static void *operator new(size_t sz, int slot);
	static void operator delete(void*, size_t);
	static void operator delete(void*, int);

	~CVehicle(void);

	void dtor(void) { this->CVehicle::~CVehicle(); }

	bool IsCar(void) { return m_vehType == VEHICLE_TYPE_CAR; }
	bool IsBoat(void) { return m_vehType == VEHICLE_TYPE_BOAT; }
	bool IsTrain(void) { return m_vehType == VEHICLE_TYPE_TRAIN; }
	bool IsHeli(void) { return m_vehType == VEHICLE_TYPE_HELI; }
	bool IsPlane(void) { return m_vehType == VEHICLE_TYPE_PLANE; }
	bool IsLawEnforcementVehicle(void);
	void ChangeLawEnforcerState(bool enable);
	void RemovePassenger(CPed *);
	void RemoveDriver(void);
	bool IsUpsideDown(void);
	
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
