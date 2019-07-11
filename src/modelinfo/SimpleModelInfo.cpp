#include "common.h"
#include "patcher.h"
#include "Camera.h"
#include "ModelInfo.h"

#define LOD_DISTANCE (300.0f)

void
CSimpleModelInfo::DeleteRwObject(void)
{
	int i;
	RwFrame *f;
	for(i = 0; i < m_numAtomics; i++)
		if(m_atomics[i]){
			f = RpAtomicGetFrame(m_atomics[i]);
			RpAtomicDestroy(m_atomics[i]);
			RwFrameDestroy(f);
			m_atomics[i] = nil;
			RemoveTexDictionaryRef();
		}
}

RwObject*
CSimpleModelInfo::CreateInstance(void)
{
	RpAtomic *atomic;
	if(m_atomics[0] == nil)
		return nil;
	atomic = RpAtomicClone(m_atomics[0]);
	RpAtomicSetFrame(atomic, RwFrameCreate());
	return (RwObject*)atomic;
}

RwObject*
CSimpleModelInfo::CreateInstance(RwMatrix *matrix)
{
	RpAtomic *atomic;
	RwFrame *frame;

	if(m_atomics[0] == nil)
		return nil;
	atomic = RpAtomicClone(m_atomics[0]);
	frame = RwFrameCreate();
	*RwFrameGetMatrix(frame) = *matrix;
	RpAtomicSetFrame(atomic, frame);
	return (RwObject*)atomic;
}

void
CSimpleModelInfo::Init(void)
{
	m_atomics[0] = nil;
	m_atomics[1] = nil;
	m_atomics[2] = nil;
	m_numAtomics = 0;
	m_firstDamaged  = 0;
	m_normalCull    = 0;
	m_isDamaged     = 0;
	m_isBigBuilding = 0;
	m_noFade        = 0;
	m_drawLast      = 0;
	m_additive      = 0;
	m_isSubway      = 0;
	m_ignoreLight   = 0;
	m_noZwrite      = 0;
}

void
CSimpleModelInfo::SetAtomic(int n, RpAtomic *atomic)
{
	AddTexDictionaryRef();
	m_atomics[n] = atomic;
	if(m_ignoreLight){
		RpGeometry *geo = RpAtomicGetGeometry(atomic);
		RpGeometrySetFlags(geo, RpGeometryGetFlags(geo) & ~rpGEOMETRYLIGHT);
	}
}

void
CSimpleModelInfo::SetLodDistances(float *dist)
{
	m_lodDistances[0] = dist[0];
	m_lodDistances[1] = dist[1];
	m_lodDistances[2] = dist[2];
}

void
CSimpleModelInfo::IncreaseAlpha(void)
{
	if(m_alpha >= 0xEF)
		m_alpha = 0xFF;
	else
		m_alpha += 0x10;
}

float
CSimpleModelInfo::GetNearDistance(void)
{
	return m_lodDistances[2] * TheCamera.LODDistMultiplier;
}

float
CSimpleModelInfo::GetLargestLodDistance(void)
{
	float d;
	if(m_firstDamaged == 0 || m_isDamaged)
		d = m_lodDistances[m_numAtomics-1];
	else
		d = m_lodDistances[m_firstDamaged-1];
	return d * TheCamera.LODDistMultiplier;
}

RpAtomic*
CSimpleModelInfo::GetAtomicFromDistance(float dist)
{
	int i;
	i = 0;
	if(m_isDamaged)
		i = m_firstDamaged;
	for(; i < m_numAtomics; i++)
		if(dist < m_lodDistances[i] *TheCamera.LODDistMultiplier)
			return m_atomics[i];
	return nil;
}

void
CSimpleModelInfo::FindRelatedModel(void)
{
	int i;
	CBaseModelInfo *mi;
	for(i = 0; i < MODELINFOSIZE; i++){
		mi = CModelInfo::GetModelInfo(i);
		if(mi && mi != this &&
		   strcmp(GetName()+3, mi->GetName()+3) == 0){
			assert(mi->IsSimple());
			this->SetRelatedModel((CSimpleModelInfo*)mi);
			return;
		}
	}
}

void
CSimpleModelInfo::SetupBigBuilding(void)
{
	CSimpleModelInfo *related;
	if(m_lodDistances[0] > LOD_DISTANCE && m_atomics[2] == nil){
		m_isBigBuilding = 1;
		FindRelatedModel();
		related = GetRelatedModel();
		if(related)
			m_lodDistances[2] = related->GetLargestLodDistance()/TheCamera.LODDistMultiplier;
		else
			m_lodDistances[2] = 100.0f;
	}
}

class CSimpleModelInfo_ : public CSimpleModelInfo
{
public:
	void DeleteRwObject_(void) { CSimpleModelInfo::DeleteRwObject(); }
	RwObject *CreateInstance_1(void) { return CSimpleModelInfo::CreateInstance(); }
	RwObject *CreateInstance_2(RwMatrix *m) { return CSimpleModelInfo::CreateInstance(m); }
	RwObject *GetRwObject_(void) { return CSimpleModelInfo::GetRwObject(); }
};

STARTPATCHES
	InjectHook(0x5179B0, &CSimpleModelInfo_::DeleteRwObject_, PATCH_JUMP);
	InjectHook(0x517B60, &CSimpleModelInfo_::CreateInstance_1, PATCH_JUMP);
	InjectHook(0x517AC0, &CSimpleModelInfo_::CreateInstance_2, PATCH_JUMP);
	InjectHook(0x4A9BA0, &CSimpleModelInfo_::GetRwObject_, PATCH_JUMP);
	InjectHook(0x517990, &CSimpleModelInfo::Init, PATCH_JUMP);
	InjectHook(0x517C60, &CSimpleModelInfo::IncreaseAlpha, PATCH_JUMP);
	InjectHook(0x517950, &CSimpleModelInfo::SetAtomic, PATCH_JUMP);
	InjectHook(0x517AA0, &CSimpleModelInfo::SetLodDistances, PATCH_JUMP);
	InjectHook(0x517A90, &CSimpleModelInfo::GetNearDistance, PATCH_JUMP);
	InjectHook(0x517A60, &CSimpleModelInfo::GetLargestLodDistance, PATCH_JUMP);
	InjectHook(0x517A00, &CSimpleModelInfo::GetAtomicFromDistance, PATCH_JUMP);
	InjectHook(0x517C00, &CSimpleModelInfo::FindRelatedModel, PATCH_JUMP);
	InjectHook(0x517B90, &CSimpleModelInfo::SetupBigBuilding, PATCH_JUMP);
ENDPATCHES
