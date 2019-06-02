#pragma once

#include "ModelInfo.h"
#include "Placeable.h"

struct CReference;

enum eEntityType
{
	ENTITY_TYPE_NOTHING = 0,
	ENTITY_TYPE_BUILDING,
	ENTITY_TYPE_VEHICLE,
	ENTITY_TYPE_PED,
	ENTITY_TYPE_OBJECT,
	ENTITY_TYPE_DUMMY,
	ENTITY_TYPE_6,
	ENTITY_TYPE_7,
};

enum eEntityStatus
{
	// from SA MTA! let's hope they didn't change from III
	STATUS_PLAYER = 0,
	STATUS_PLAYER_PLAYBACKFROMBUFFER,
	STATUS_SIMPLE,
	STATUS_PHYSICS,
	STATUS_ABANDONED,
	STATUS_WRECKED,
	STATUS_TRAIN_MOVING,
	STATUS_TRAIN_NOT_MOVING,
	STATUS_HELI,
	STATUS_PLANE,
	STATUS_PLAYER_REMOTE,
	STATUS_PLAYER_DISABLED,
	//STATUS_TRAILER,
	//STATUS_SIMPLE_TRAILER
};

class CEntity : public CPlaceable
{
public:
	RwObject *m_rwObject;
	uint32 m_type : 3;
	uint32 m_status : 5;

	// flagsA
	uint32 bUsesCollision : 1;
	uint32 bCollisionProcessed : 1;
	uint32 bIsStatic : 1;
	uint32 bHasContacted : 1;
	uint32 bPedPhysics : 1;
	uint32 bIsStuck : 1;
	uint32 bIsInSafePosition : 1;
	uint32 bUseCollisionRecords : 1;

	// flagsB
	uint32 bWasPostponed : 1;
	uint32 m_flagB2 : 1;	// explosion proof?
	uint32 bIsVisible : 1;
	uint32 bHasCollided : 1;	//
	uint32 bRenderScorched : 1;
	uint32 m_flagB20 : 1;	// bFlashing?
	uint32 bIsBIGBuilding : 1;
	// VC inserts one more flag here: if drawdist <= 2000
	uint32 bRenderDamaged : 1;

	// flagsC
	uint32 m_flagC1 : 1;	// bullet proof?
	uint32 m_flagC2 : 1;	// fire proof?
	uint32 m_flagC4 : 1;	// collision proof?
	uint32 m_flagC8 : 1;	// melee proof?
	uint32 m_flagC10 : 1;	// bOnlyDamagedByPlayer?
	uint32 m_flagC20 : 1;
	uint32 m_bZoneCulled : 1;
	uint32 m_bZoneCulled2 : 1;	// only treadables+10m

	// flagsD
	uint32 bRemoveFromWorld : 1;
	uint32 bHasHitWall : 1;
	uint32 bImBeingRendered : 1;
	uint32 m_flagD8 : 1;
	uint32 m_flagD10 : 1;
	uint32 bDrawLast : 1;
	uint32 m_flagD40 : 1;
	uint32 m_flagD80 : 1;

	// flagsE
	uint32 bDistanceFade : 1;
	uint32 m_flagE2 : 1;

	uint16 m_scanCode;
	int16 m_randomSeed;
	int16 m_modelIndex;
	uint16 m_level;	// int16
	CReference *m_pFirstReference;

	CEntity(void);
	~CEntity(void);

	virtual void Add(void);
	virtual void Remove(void);
	virtual void SetModelIndex(uint32 i) { m_modelIndex = i; CreateRwObject(); }
	virtual void SetModelIndexNoCreate(uint32 i) { m_modelIndex = i; }
	virtual void CreateRwObject(void);
	virtual void DeleteRwObject(void);
	virtual CRect GetBoundRect(void);
	virtual void ProcessControl(void) {}
	virtual void ProcessCollision(void) {}
	virtual void ProcessShift(void) {}
	virtual void Teleport(CVector v) {}
	virtual void PreRender(void);
	virtual void Render(void);
	virtual bool SetupLighting(void);
	virtual void RemoveLighting(bool) {}
	virtual void FlagToDestroyWhenNextProcessed(void) {}

	bool IsBuilding(void) { return m_type == ENTITY_TYPE_BUILDING; }
	bool IsVehicle(void) { return m_type == ENTITY_TYPE_VEHICLE; }
	bool IsPed(void) { return m_type == ENTITY_TYPE_PED; }
	bool IsObject(void) { return m_type == ENTITY_TYPE_OBJECT; }
	bool IsDummy(void) { return m_type == ENTITY_TYPE_DUMMY; }

	void GetBoundCentre(CVector &out);
	CVector GetBoundCentre(void) { CVector v; GetBoundCentre(v); return v; }
	float GetBoundRadius(void) { return CModelInfo::GetModelInfo(m_modelIndex)->GetColModel()->boundingSphere.radius; }
	float GetDistanceFromCentreOfMassToBaseOfModel(void) { return -CModelInfo::GetModelInfo(m_modelIndex)->GetColModel()->boundingBox.min.z; }
	bool GetIsTouching(CVector const &center, float r);
	bool GetIsOnScreen(void);
	bool GetIsOnScreenComplex(void);
	bool IsVisible(void) { return m_rwObject && bIsVisible && GetIsOnScreen(); }
	bool IsVisibleComplex(void) { return m_rwObject && bIsVisible && GetIsOnScreenComplex(); }
	int GetModelIndex(void) { return m_modelIndex; }
	void UpdateRwFrame(void);
	void SetupBigBuilding(void);

	void AttachToRwObject(RwObject *obj);
	void DetachFromRwObject(void);

	void RegisterReference(CEntity **pent);
	void ResolveReferences(void);
	void PruneReferences(void);


	// to make patching virtual functions possible
	void Add_(void) { CEntity::Add(); }
	void Remove_(void) { CEntity::Remove(); }
	void CreateRwObject_(void) { CEntity::CreateRwObject(); }
	void DeleteRwObject_(void) { CEntity::DeleteRwObject(); }
	CRect GetBoundRect_(void) { return CEntity::GetBoundRect(); }
	void Render_(void) { CEntity::Render(); }
	bool SetupLighting_(void) { return CEntity::SetupLighting(); }
};
static_assert(sizeof(CEntity) == 0x64, "CEntity: error");
