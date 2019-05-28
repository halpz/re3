#pragma once

#include "Lists.h"
#include "Timer.h"
#include "Entity.h"
#include "Treadable.h"

enum {
	PHYSICAL_MAX_COLLISIONRECORDS = 6
};

class CPhysical : public CEntity
{
public:
	// The not properly indented fields haven't been checked properly yet

  int uAudioEntityId;
  float unk1;
	CTreadable *m_carTreadable;
	CTreadable *m_pedTreadable;
	uint32 m_nLastTimeCollided;
	CVector m_vecMoveSpeed;		// velocity
	CVector m_vecTurnSpeed;		// angular velocity
	CVector m_vecMoveFriction;
	CVector m_vecTurnFriction;
	CVector m_vecMoveSpeedAvg;
	CVector m_vecTurnSpeedAvg;
	float m_fMass;
	float m_fTurnMass;	// moment of inertia
  float fForceMultiplier;
	float m_fAirResistance;
	float m_fElasticity;
  float fPercentSubmerged;
	CVector m_vecCentreOfMass;
	CEntryInfoList m_entryInfoList;
	CPtrNode *m_movingListNode;

  char field_EC;
	uint8 m_nStaticFrames;
	uint8 m_nCollisionRecords;
	bool field_EF;
	CEntity *m_aCollisionRecords[PHYSICAL_MAX_COLLISIONRECORDS];

	float m_fDistanceTravelled;

	// damaged piece
	float m_fDamageImpulse;
	CEntity *m_pDamageEntity;
	CVector m_vecDamageNormal;
	int16 m_nDamagePieceType;

	uint8 m_phy_flagA1 : 1;
	uint8 bAffectedByGravity : 1;
	uint8 bInfiniteMass : 1;
	uint8 m_phy_flagA8 : 1;
	uint8 m_phy_flagA10 : 1;
	uint8 m_phy_flagA20 : 1;
	uint8 m_phy_flagA40 : 1;
	uint8 m_phy_flagA80 : 1;

  uint8 m_nLastCollType;
  uint8 m_nZoneLevel;
  uint8 pad[3];


	// from CEntity
	void Add(void);
	void Remove(void);
	CRect GetBoundRect(void);
	void ProcessControl(void);

	virtual int32 ProcessEntityCollision(CEntity *ent, CColPoint *point);

	void RemoveAndAdd(void);
	void AddToMovingList(void);
	void RemoveFromMovingList(void);
	void SetDamagedPieceRecord(uint16 piece, float impulse, CEntity *entity, CVector dir);
	void AddCollisionRecord(CEntity *ent);
	void AddCollisionRecord_Treadable(CEntity *ent);
	bool GetHasCollidedWith(CEntity *ent);
	void RemoveRefsToEntity(CEntity *ent);

	float GetDistanceSq(void) { return m_vecMoveSpeed.MagnitudeSqr() * sq(CTimer::GetTimeStep()); }
	// get speed of point p relative to entity center
	CVector GetSpeed(const CVector &r);
	CVector GetSpeed(void) { return GetSpeed(CVector(0.0f, 0.0f, 0.0f)); }
	float GetMass(const CVector &pos, const CVector &dir) {
		return 1.0f / (CrossProduct(pos, dir).MagnitudeSqr()/m_fTurnMass +
		               1.0f/m_fMass);
	}
	float GetMassTime(const CVector &pos, const CVector &dir, float t) {
		return 1.0f / (CrossProduct(pos, dir).MagnitudeSqr()/(m_fTurnMass*t) +
		               1.0f/(m_fMass*t));
	}
	void UnsetIsInSafePosition(void) {
		m_vecMoveSpeed *= -1.0f;
		m_vecTurnSpeed *= -1.0f;
		ApplyTurnSpeed();
		ApplyMoveSpeed();
		m_vecMoveSpeed *= -1.0f;
		m_vecTurnSpeed *= -1.0f;
		bIsInSafePosition = false;	
	}

	void ApplyMoveSpeed(void);
	void ApplyTurnSpeed(void);
	// Force actually means Impulse here
	void ApplyMoveForce(float jx, float jy, float jz);
	void ApplyMoveForce(const CVector &j) { ApplyMoveForce(j.x, j.y, j.z); }
	// v(x,y,z) is direction of force, p(x,y,z) is point relative to model center where force is applied
	void ApplyTurnForce(float jx, float jy, float jz, float rx, float ry, float rz);
	// v is direction of force, p is point relative to model center where force is applied
	void ApplyTurnForce(const CVector &j, const CVector &p) { ApplyTurnForce(j.x, j.y, j.z, p.x, p.y, p.z); }
	void ApplyFrictionMoveForce(float jx, float jy, float jz);
	void ApplyFrictionMoveForce(const CVector &j) { ApplyFrictionMoveForce(j.x, j.y, j.z); }
	void ApplyFrictionTurnForce(float jx, float jy, float jz, float rx, float ry, float rz);
	void ApplyFrictionTurnForce(const CVector &j, const CVector &p) { ApplyFrictionTurnForce(j.x, j.y, j.z, p.x, p.y, p.z); }
	void ApplySpringCollision(float f1, CVector &v, CVector &p, float f2, float f3);
	void ApplyGravity(void);
	void ApplyFriction(void);
	void ApplyAirResistance(void);
	bool ApplyCollision(CPhysical *B, CColPoint &colpoint, float &impulseA, float &impulseB);
	bool ApplyCollisionAlt(CEntity *B, CColPoint &colpoint, float &impulse, CVector &moveSpeed, CVector &turnSpeed);
	bool ApplyFriction(CPhysical *B, float adhesiveLimit, CColPoint &colpoint);
	bool ApplyFriction(float adhesiveLimit, CColPoint &colpoint);

	bool ProcessShiftSectorList(CPtrList *ptrlists);
	bool ProcessCollisionSectorList_SimpleCar(CPtrList *lists);
	bool ProcessCollisionSectorList(CPtrList *lists);
	bool CheckCollision(void);
	bool CheckCollision_SimpleCar(void);
	void ProcessShift(void);
	void ProcessCollision(void);

	// to make patching virtual functions possible
	void Add_(void) { CPhysical::Add(); }
	void Remove_(void) { CPhysical::Remove(); }
	CRect GetBoundRect_(void) { return CPhysical::GetBoundRect(); }
	void ProcessControl_(void) { CPhysical::ProcessControl(); }
	void ProcessShift_(void) { CPhysical::ProcessShift(); }
	void ProcessCollision_(void) { CPhysical::ProcessCollision(); }
	int32 ProcessEntityCollision_(CEntity *ent, CColPoint *point) { return CPhysical::ProcessEntityCollision(ent, point); }
};
static_assert(sizeof(CPhysical) == 0x128, "CPhysical: error");
