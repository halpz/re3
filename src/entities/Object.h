#pragma once

#include "Physical.h"

enum {
	GAME_OBJECT = 1,
	MISSION_OBJECT = 2,
	TEMP_OBJECT = 3,
	CUTSCENE_OBJECT = 4,
};

enum {
	COLLRESPONSE_NONE,
	COLLRESPONSE_CHANGE_MODEL,
	COLLRESPONSE_SPLIT_MODEL,
	COLLRESPONSE_SMASH_COMPLETELY,
	COLLRESPONSE_CHANGE_THEN_SMASH,
	COLLRESPONSE_UNKNOWN5,

	COLLRESPONSE_SMASH_CARDBOARD_COMPLETELY = 50,
	COLLRESPONSE_SMASH_WOODENBOX_COMPLETELY = 60,
	COLLRESPONSE_SMASH_TRAFFICCONE_COMPLETELY = 70,
	COLLRESPONSE_SMASH_BARPOST_COMPLETELY = 80,

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
	int8 bUseVehicleColours : 1;
	int8 m_obj_flag80 : 1;
  int8 field_172;
  int8 field_173;
	float m_fCollisionDamageMultiplier;
	uint8 m_nCollisionDamageEffect;
	uint8 m_nSpecialCollisionResponseCases;
	bool m_bCameraToAvoidThisObject;
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

	static int16 &nNoTempObjects;

	static void *operator new(size_t);
	static void operator delete(void*, size_t);

	CObject(void);
	~CObject(void);

	void Render(void);

	void ObjectDamage(float amount);

	static void DeleteAllTempObjectInArea(CVector, float);

	void dtor(void) { this->CObject::~CObject(); }
	void Render_(void) { CObject::Render(); }
};
static_assert(sizeof(CObject) == 0x198, "CObject: error");
