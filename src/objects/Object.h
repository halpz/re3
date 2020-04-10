#pragma once

#include "Physical.h"

enum {
	GAME_OBJECT = 1,
	MISSION_OBJECT = 2,
	TEMP_OBJECT = 3,
	CUTSCENE_OBJECT = 4,
};

enum {
	COLDAMAGE_EFFECT_NONE = 0,
	COLDAMAGE_EFFECT_CHANGE_MODEL = 1,
	COLDAMAGE_EFFECT_SPLIT_MODEL = 2,
	COLDAMAGE_EFFECT_SMASH_COMPLETELY = 3,
	COLDAMAGE_EFFECT_CHANGE_THEN_SMASH = 4,
	COLDAMAGE_EFFECT_SMASH_CARDBOX_COMPLETELY = 50,
	COLDAMAGE_EFFECT_SMASH_WOODENBOX_COMPLETELY = 60,
	COLDAMAGE_EFFECT_SMASH_TRAFFICCONE_COMPLETELY = 70,
	COLDAMAGE_EFFECT_SMASH_BARPOST_COMPLETELY = 80,
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
class CDummyObject;

class CObject : public CPhysical
{
public:
	CMatrix m_objectMatrix;
	float m_fUprootLimit;
	int8 ObjectCreatedBy;
	int8 bIsPickup : 1;
	int8 m_obj_flag2 : 1;
	int8 bOutOfStock : 1;
	int8 bGlassCracked : 1;
	int8 bGlassBroken : 1;
	int8 bHasBeenDamaged : 1;
	int8 bUseVehicleColours : 1;
	int8 m_obj_flag80 : 1;
	int8 m_nBonusValue; 
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
	uint32 m_nEndOfLifeTime;
	int16 m_nRefModelIndex;
  int8 field_186;
  int8 field_187;
	CEntity *m_pCurSurface;
	CEntity *m_pCollidingEntity;
	int8 m_colour1, m_colour2;

	static int16 &nNoTempObjects;
	static int16 &nBodyCastHealth;

	static void *operator new(size_t);
	static void *operator new(size_t, int);
	static void operator delete(void*, size_t);
	static void operator delete(void*, int);

	CObject(void);
	CObject(int32, bool);
	CObject(CDummyObject*);
	~CObject(void);

	void ProcessControl(void);
	void Teleport(CVector vecPos);
	void Render(void);
	bool SetupLighting(void);
	void RemoveLighting(bool reset);

	void ObjectDamage(float amount);
	void RefModelInfo(int32 modelId);
	void Init(void);
	bool CanBeDeleted(void);

	static void DeleteAllMissionObjects();
	static void DeleteAllTempObjects();
	static void DeleteAllTempObjectInArea(CVector point, float fRadius);
};
static_assert(sizeof(CObject) == 0x198, "CObject: error");
