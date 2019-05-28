#pragma once

#include "Physical.h"

enum {
	GAME_OBJECT = 1,
	MISSION_OBJECT = 2,
	TEMP_OBJECT = 3,
};

class CVehicle;

class CObject : public CPhysical
{
public:
	CMatrix m_objectMatrix;
	float m_fUprootLimit;
	int8 ObjectCreatedBy;
	int8 m_obj_flag1 : 1;
	int8 m_obj_flag2 : 1;
	int8 m_obj_flag4 : 1;
	int8 m_obj_flag8 : 1;
	int8 m_obj_flag10 : 1;
	int8 bHasBeenDamaged : 1;
	int8 m_obj_flag40 : 1;
	int8 m_obj_flag80 : 1;
  int8 field_172;
  int8 field_173;
	float m_fCollisionDamageMultiplier;
	int8 m_nCollisionDamageEffect;
	int8 m_bSpecialCollisionResponseCases;
	int8 m_bCameraToAvoidThisObject;
  int8 field_17B;
  int8 field_17C;
  int8 field_17D;
  int8 field_17E;
  int8 field_17F;
	int32 m_nEndOfLifeTime;
	int16 m_nRefModelIndex;
  int8 field_186;
  int8 field_187;
	CEntity *m_pCurSurface;
	CEntity *m_pCollidingEntity;
	int8 m_colour1, m_colour2;

	static void *operator new(size_t);
	static void operator delete(void*, size_t);

	void ObjectDamage(float amount);
};
static_assert(sizeof(CObject) == 0x198, "CObject: error");
