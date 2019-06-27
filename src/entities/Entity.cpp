#include "common.h"
#include "rpworld.h"
#include "Placeable.h"
#include "Entity.h"
#include "Lights.h"
#include "World.h"
#include "Camera.h"
#include "References.h"
#include "TxdStore.h"
#include "Zones.h"
#include "patcher.h"

int gBuildings;

CEntity::CEntity(void)
{
	m_type = ENTITY_TYPE_NOTHING;
	m_status = STATUS_ABANDONED;

	bUsesCollision = false;
	bCollisionProcessed = false;
	bIsStatic = false;
	bHasContacted = false;
	bPedPhysics = false;
	bIsStuck = false;
	bIsInSafePosition = false;
	bUseCollisionRecords = false;

	bWasPostponed = false;
	m_flagB2 = false;
	bIsVisible = true;
	bHasCollided = false;
	bRenderScorched = false;
	bHasBlip = false;
	bIsBIGBuilding = false;
	bRenderDamaged = false;

	bBulletProof = false;
	bFireProof = false;
	bCollisionProof = false;
	bMeleeProof = false;
	bOnlyDamagedByPlayer = false;
	bStreamingDontDelete = false;
	bZoneCulled = false;
	bZoneCulled2 = false;

	bRemoveFromWorld = false;
	bHasHitWall = false;
	bImBeingRendered = false;
	m_flagD8 = false;
	bIsSubway = false;
	bDrawLast = false;
	m_flagD40 = false;
	m_flagD80 = false;

	bDistanceFade = false;
	m_flagE2 = false;

	m_scanCode = 0;
	m_modelIndex = -1;
	m_rwObject = nil;
	m_randomSeed = rand();
	m_pFirstReference = nil;
}

CEntity::~CEntity(void)
{
	DeleteRwObject();
	ResolveReferences();
}

void
CEntity::GetBoundCentre(CVector &out)
{
	out = m_matrix * CModelInfo::GetModelInfo(m_modelIndex)->GetColModel()->boundingSphere.center;
};

bool
CEntity::GetIsTouching(CVector const &center, float radius)
{
	return sq(GetBoundRadius()+radius) > (GetBoundCentre()-center).MagnitudeSqr();
}

bool
CEntity::GetIsOnScreen(void)
{
	return TheCamera.IsSphereVisible(GetBoundCentre(), GetBoundRadius(),
		&TheCamera.GetCameraMatrix());
}

bool
CEntity::GetIsOnScreenComplex(void)
{
	RwV3d boundBox[8];

	if(TheCamera.IsPointVisible(GetBoundCentre(), &TheCamera.GetCameraMatrix()))
		return true;

	CRect rect = GetBoundRect();
	CColModel *colmodel = CModelInfo::GetModelInfo(m_modelIndex)->GetColModel();
	float z = GetPosition().z;
	float minz = z + colmodel->boundingBox.min.z;
	float maxz = z + colmodel->boundingBox.max.z;
	boundBox[0].x = rect.left;
	boundBox[0].y = rect.bottom;
	boundBox[0].z = minz;
	boundBox[1].x = rect.left;
	boundBox[1].y = rect.top;
	boundBox[1].z = minz;
	boundBox[2].x = rect.right;
	boundBox[2].y = rect.bottom;
	boundBox[2].z = minz;
	boundBox[3].x = rect.right;
	boundBox[3].y = rect.top;
	boundBox[3].z = minz;
	boundBox[4].x = rect.left;
	boundBox[4].y = rect.bottom;
	boundBox[4].z = maxz;
	boundBox[5].x = rect.left;
	boundBox[5].y = rect.top;
	boundBox[5].z = maxz;
	boundBox[6].x = rect.right;
	boundBox[6].y = rect.bottom;
	boundBox[6].z = maxz;
	boundBox[7].x = rect.right;
	boundBox[7].y = rect.top;
	boundBox[7].z = maxz;

	return TheCamera.IsBoxVisible(boundBox, &TheCamera.GetCameraMatrix());
}

void
CEntity::Add(void)
{
	int x, xstart, xmid, xend;
	int y, ystart, ymid, yend;
	CSector *s;
	CPtrList *list;

	CRect bounds = GetBoundRect();
	xstart = CWorld::GetSectorIndexX(bounds.left);
	xend   = CWorld::GetSectorIndexX(bounds.right);
	xmid   = CWorld::GetSectorIndexX((bounds.left + bounds.right)/2.0f);
	ystart = CWorld::GetSectorIndexY(bounds.top);
	yend   = CWorld::GetSectorIndexY(bounds.bottom);
	ymid   = CWorld::GetSectorIndexY((bounds.top + bounds.bottom)/2.0f);
	assert(xstart >= 0);
	assert(xend < NUMSECTORS_X);
	assert(ystart >= 0);
	assert(yend < NUMSECTORS_Y);

	for(y = ystart; y <= yend; y++)
		for(x = xstart; x <= xend; x++){
			s = CWorld::GetSector(x, y);
			if(x == xmid && y == ymid) switch(m_type){
			case ENTITY_TYPE_BUILDING:
				list = &s->m_lists[ENTITYLIST_BUILDINGS];
				break;
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS];
				break;
			case ENTITY_TYPE_DUMMY:
				list = &s->m_lists[ENTITYLIST_DUMMIES];
				break;
			}else switch(m_type){
			case ENTITY_TYPE_BUILDING:
				list = &s->m_lists[ENTITYLIST_BUILDINGS_OVERLAP];
				break;
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES_OVERLAP];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS_OVERLAP];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS_OVERLAP];
				break;
			case ENTITY_TYPE_DUMMY:
				list = &s->m_lists[ENTITYLIST_DUMMIES_OVERLAP];
				break;
			}
			list->InsertItem(this);
		}
}

void
CEntity::Remove(void)
{
	int x, xstart, xmid, xend;
	int y, ystart, ymid, yend;
	CSector *s;
	CPtrList *list;

	CRect bounds = GetBoundRect();
	xstart = CWorld::GetSectorIndexX(bounds.left);
	xend   = CWorld::GetSectorIndexX(bounds.right);
	xmid   = CWorld::GetSectorIndexX((bounds.left + bounds.right)/2.0f);
	ystart = CWorld::GetSectorIndexY(bounds.top);
	yend   = CWorld::GetSectorIndexY(bounds.bottom);
	ymid   = CWorld::GetSectorIndexY((bounds.top + bounds.bottom)/2.0f);
	assert(xstart >= 0);
	assert(xend < NUMSECTORS_X);
	assert(ystart >= 0);
	assert(yend < NUMSECTORS_Y);

	for(y = ystart; y <= yend; y++)
		for(x = xstart; x <= xend; x++){
			s = CWorld::GetSector(x, y);
			if(x == xmid && y == ymid) switch(m_type){
			case ENTITY_TYPE_BUILDING:
				list = &s->m_lists[ENTITYLIST_BUILDINGS];
				break;
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS];
				break;
			case ENTITY_TYPE_DUMMY:
				list = &s->m_lists[ENTITYLIST_DUMMIES];
				break;
			}else switch(m_type){
			case ENTITY_TYPE_BUILDING:
				list = &s->m_lists[ENTITYLIST_BUILDINGS_OVERLAP];
				break;
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES_OVERLAP];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS_OVERLAP];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS_OVERLAP];
				break;
			case ENTITY_TYPE_DUMMY:
				list = &s->m_lists[ENTITYLIST_DUMMIES_OVERLAP];
				break;
			}
			list->RemoveItem(this);
		}
}

void
CEntity::CreateRwObject(void)
{
	CBaseModelInfo *mi;

	mi = CModelInfo::GetModelInfo(m_modelIndex);
	m_rwObject = mi->CreateInstance();
	if(m_rwObject){
		if(IsBuilding())
			gBuildings++;
		if(RwObjectGetType(m_rwObject) == rpATOMIC)
			m_matrix.AttachRW(RwFrameGetMatrix(RpAtomicGetFrame(m_rwObject)), false);
		else if(RwObjectGetType(m_rwObject) == rpCLUMP)
			m_matrix.AttachRW(RwFrameGetMatrix(RpClumpGetFrame(m_rwObject)), false);
		mi->AddRef();
	}
}

void
CEntity::DeleteRwObject(void)
{
	RwFrame *f;

	m_matrix.Detach();
	if(m_rwObject){
		if(RwObjectGetType(m_rwObject) == rpATOMIC){
			f = RpAtomicGetFrame(m_rwObject);
			RpAtomicDestroy((RpAtomic*)m_rwObject);
			RwFrameDestroy(f);
		}else if(RwObjectGetType(m_rwObject) == rpCLUMP)
			RpClumpDestroy((RpClump*)m_rwObject);
		m_rwObject = nil;
		CModelInfo::GetModelInfo(m_modelIndex)->RemoveRef();
		if(IsBuilding())
			gBuildings--;
	}
}

void
CEntity::UpdateRwFrame(void)
{
	if(m_rwObject){
		if(RwObjectGetType(m_rwObject) == rpATOMIC)
			RwFrameUpdateObjects(RpAtomicGetFrame(m_rwObject));
		else if(RwObjectGetType(m_rwObject) == rpCLUMP)
			RwFrameUpdateObjects(RpClumpGetFrame(m_rwObject));
	}
}

void
CEntity::SetupBigBuilding(void)
{
	CSimpleModelInfo *mi;

	mi = (CSimpleModelInfo*)CModelInfo::GetModelInfo(m_modelIndex);
	bIsBIGBuilding = true;
	bStreamingDontDelete = true;
	bUsesCollision = false;
	m_level = CTheZones::GetLevelFromPosition(GetPosition());
	if(m_level == LEVEL_NONE){
		if(mi->GetTxdSlot() != CTxdStore::FindTxdSlot("generic")){
			mi->SetTexDictionary("generic");
			printf("%d:%s txd has been set to generic\n", m_modelIndex, mi->GetName());
		}
	}
	if(mi->m_lodDistances[0] > 2000.0f)
		m_level = LEVEL_NONE;
}

CRect
CEntity::GetBoundRect(void)
{
	CRect rect;
	CVector v;
	CColModel *col = CModelInfo::GetModelInfo(m_modelIndex)->GetColModel();

	rect.ContainPoint(m_matrix * col->boundingBox.min);
	rect.ContainPoint(m_matrix * col->boundingBox.max);

	v = col->boundingBox.min;
	v.x = col->boundingBox.max.x;
	rect.ContainPoint(m_matrix * v);

	v = col->boundingBox.max;
	v.x = col->boundingBox.min.x;
	rect.ContainPoint(m_matrix * v);

	return rect;
}

WRAPPER void
CEntity::PreRender(void)
{ EAXJMP(0x474350);
}

void
CEntity::Render(void)
{
	if(m_rwObject){
		bImBeingRendered = true;
		if(RwObjectGetType(m_rwObject) == rpATOMIC)
			RpAtomicRender((RpAtomic*)m_rwObject);
		else
			RpClumpRender((RpClump*)m_rwObject);
		bImBeingRendered = false;
	}
}

bool
CEntity::SetupLighting(void)
{
	DeActivateDirectional();
	SetAmbientColours();
	return false;
}

void
CEntity::AttachToRwObject(RwObject *obj)
{
	m_rwObject = obj;
	if(m_rwObject){
		if(RwObjectGetType(m_rwObject) == rpATOMIC)
			m_matrix.Attach(RwFrameGetMatrix(RpAtomicGetFrame(m_rwObject)), false);
		else if(RwObjectGetType(m_rwObject) == rpCLUMP)
			m_matrix.Attach(RwFrameGetMatrix(RpClumpGetFrame(m_rwObject)), false);
		CModelInfo::GetModelInfo(m_modelIndex)->AddRef();
	}
}

void
CEntity::DetachFromRwObject(void)
{
	if(m_rwObject)
		CModelInfo::GetModelInfo(m_modelIndex)->RemoveRef();
	m_rwObject = nil;
	m_matrix.Detach();
}

void
CEntity::RegisterReference(CEntity **pent)
{
	if(IsBuilding())
		return;
	CReference *ref;
	// check if already registered
	for(ref = m_pFirstReference; ref; ref = ref->next)
		if(ref->pentity == pent)
			return;
	// have to allocate new reference
	ref = CReferences::pEmptyList;
	if(ref){
		CReferences::pEmptyList = ref->next;

		ref->pentity = pent;
		ref->next = m_pFirstReference;
		m_pFirstReference = ref;
		return;
	}
	return;
}

// Clear all references to this entity
void
CEntity::ResolveReferences(void)
{
	CReference *ref;
	// clear pointers to this entity
	for(ref = m_pFirstReference; ref; ref = ref->next)
		if(*ref->pentity == this)
			*ref->pentity = nil;
	// free list
	if(m_pFirstReference){
		for(ref = m_pFirstReference; ref->next; ref = ref->next)
			;
		ref->next = CReferences::pEmptyList;
		CReferences::pEmptyList = ref;
		m_pFirstReference = nil;
	}
}

// Free all references that no longer point to this entity
void
CEntity::PruneReferences(void)
{
	CReference *ref, *next, **lastnextp;
	lastnextp = &m_pFirstReference;
	for(ref = m_pFirstReference; ref; ref = next){
		next = ref->next;
		if(*ref->pentity == this)
			lastnextp = &ref->next;
		else{
			*lastnextp = ref->next;
			ref->next = CReferences::pEmptyList;
			CReferences::pEmptyList = ref;
		}
	}
}

STARTPATCHES
	InjectHook(0x473C30, &CEntity::ctor, PATCH_JUMP);
	InjectHook(0x4742C0, (void (CEntity::*)(CVector&))&CEntity::GetBoundCentre, PATCH_JUMP);
	InjectHook(0x474310, &CEntity::GetBoundRadius, PATCH_JUMP);
	InjectHook(0x474C10, &CEntity::GetIsTouching, PATCH_JUMP);
	InjectHook(0x474CC0, &CEntity::GetIsOnScreen, PATCH_JUMP);
	InjectHook(0x474D20, &CEntity::GetIsOnScreenComplex, PATCH_JUMP);
	InjectHook(0x474CA0, &CEntity::IsVisible, PATCH_JUMP);
	InjectHook(0x474330, &CEntity::UpdateRwFrame, PATCH_JUMP);
	InjectHook(0x4755E0, &CEntity::SetupBigBuilding, PATCH_JUMP);
	InjectHook(0x4A7480, &CEntity::RegisterReference, PATCH_JUMP);
	InjectHook(0x4A74E0, &CEntity::ResolveReferences, PATCH_JUMP);
	InjectHook(0x4A7530, &CEntity::PruneReferences, PATCH_JUMP);

	InjectHook(0x473F10, &CEntity::AttachToRwObject, PATCH_JUMP);
	InjectHook(0x473F60, &CEntity::DetachFromRwObject, PATCH_JUMP);

	InjectHook(0x475080, &CEntity::Add_, PATCH_JUMP);
	InjectHook(0x475310, &CEntity::Remove_, PATCH_JUMP);
	InjectHook(0x473EA0, &CEntity::CreateRwObject_, PATCH_JUMP);
	InjectHook(0x473F90, &CEntity::DeleteRwObject_, PATCH_JUMP);
	InjectHook(0x474000, &CEntity::GetBoundRect_, PATCH_JUMP);
	InjectHook(0x474BD0, &CEntity::Render_, PATCH_JUMP);
	InjectHook(0x4A7C60, &CEntity::SetupLighting_, PATCH_JUMP);
ENDPATCHES
