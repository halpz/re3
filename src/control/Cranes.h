#pragma once
#include "common.h"

#include "World.h"

class CVehicle;
class CEntity;
class CObject;

class CCrane
{
public:
	enum CraneState : uint8 {
		IDLE = 0,
		GOING_TOWARDS_TARGET = 1,
		LIFTING_TARGET = 2,
		GOING_TOWARDS_HEIGHT_TARGET = 3,
		ROTATING_TARGET = 4,
		DROPPING_TARGET = 5
	};
	enum CraneStatus : uint8 {
		NONE = 0,
		ACTIVATED = 1,
		DEACTIVATED = 2
	};
	CEntity *m_pObject;
	CObject *m_pMagnet;
	int32 m_nAudioEntity;
	float m_fPickupX1;
	float m_fPickupX2;
	float m_fPickupY1;
	float m_fPickupY2;
	CVector m_vecDropoffTarget;
	float m_fDropoffHeading;
	float m_fPickupAngle;
	float m_fDropoffAngle;
	float m_fPickupDistance;
	float m_fDropoffDistance;
	float m_fAngle;
	float m_fDistance;
	float m_fHeight;
	float m_fHookOffset;
	float m_fHookHeight;
	CVector m_vecHookInitPos;
	CVector m_vecHookCurPos;
	float m_fHookVelocityX;
	float m_fHookVelocityY;
	CVehicle *m_pVehiclePickedUp;
	uint32 m_nUpdateTimer;
	CraneStatus m_bCraneStatus;
	CraneState m_bCraneState;
	uint8 m_bVehiclesCollected;
	bool m_bIsCrusher;
	bool m_bIsMilitaryCrane;
	bool m_bWasMilitaryCrane;
	bool m_bIsTop;

	void Init(void) { memset(this, 0, sizeof(*this)); }
	void Update(void);
	bool RotateCarriedCarProperly();
	void FindCarInSectorList(CPtrList*);
	bool DoesCranePickUpThisCarType(uint32);
	bool GoTowardsTarget(float, float, float, float);
	bool GoTowardsHeightTarget(float, float);
	void FindParametersForTarget(float, float, float, float*, float*, float*);
	void CalcHookCoordinates(float*, float*, float*);
	void SetHookMatrix();
};

static_assert(sizeof(CCrane) == 128, "CCrane: error");

class CCranes
{
public:
	static void InitCranes(void);
	static void AddThisOneCrane(CEntity*);
	static void ActivateCrane(float, float, float, float, float, float, float, float, bool, bool, float, float);
	static void DeActivateCrane(float, float);
	static bool IsThisCarPickedUp(float, float, CVehicle*);
	static void UpdateCranes(void);
	static bool DoesMilitaryCraneHaveThisOneAlready(uint32);
	static void RegisterCarForMilitaryCrane(uint32);
	static bool HaveAllCarsBeenCollectedByMilitaryCrane();
	static bool IsThisCarBeingCarriedByAnyCrane(CVehicle*);
	static bool IsThisCarBeingTargettedByAnyCrane(CVehicle*);
	static void Save(uint8*, uint32*);

	static int32& CarsCollectedMilitaryCrane;
	static int32& NumCranes;
	static CCrane(&aCranes)[NUM_CRANES];
};

void CranesLoad(uint8*, uint32);	// is this really outside CCranes?
