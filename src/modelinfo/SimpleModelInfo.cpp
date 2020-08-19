#include "common.h"

#include "General.h"
#include "Camera.h"
#include "ModelInfo.h"
#include "AnimManager.h"
#include "custompipes.h"

//--MIAMI: file done

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
			if(GetAnimFileIndex() != -1)
				CAnimManager::RemoveAnimBlockRef(GetAnimFileIndex());
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
	m_wetRoadReflection    = 0;
	m_isDamaged     = 0;
	m_isBigBuilding = 0;
	m_noFade        = 0;
	m_drawLast      = 0;
	m_additive      = 0;
	m_isSubway      = 0;
	m_ignoreLight   = 0;
	m_noZwrite      = 0;
	m_noShadows     = 0;
	m_ignoreDrawDist  = 0;
	m_isCodeGlass     = 0;
	m_isArtistGlass   = 0;
}

void
CSimpleModelInfo::SetAtomic(int n, RpAtomic *atomic)
{
	AddTexDictionaryRef();
	m_atomics[n] = atomic;
	if(GetAnimFileIndex() != -1)
		CAnimManager::AddAnimBlockRef(GetAnimFileIndex());
	RpGeometry *geo = RpAtomicGetGeometry(atomic);
	if(m_ignoreLight)
		RpGeometrySetFlags(geo, RpGeometryGetFlags(geo) & ~rpGEOMETRYLIGHT);
	if(RpGeometryGetFlags(geo) & rpGEOMETRYNORMALS &&
	   RpGeometryGetNumTriangles(geo) > 200)
		debug("%s has %d polys\n", m_name, RpGeometryGetNumTriangles(geo));

#ifdef EXTENDED_PIPELINES
	if(m_wetRoadReflection)
		CustomPipes::AttachGlossPipe(atomic);
	else
		CustomPipes::AttachWorldPipe(atomic);
#endif
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
CSimpleModelInfo::GetLodDistance(int i)
{
	return m_lodDistances[i] * TheCamera.LODDistMultiplier;
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
		if(dist < m_lodDistances[i] * TheCamera.LODDistMultiplier)
			return m_atomics[i];
	return nil;
}

RpAtomic*
CSimpleModelInfo::GetFirstAtomicFromDistance(float dist)
{
	if(dist < m_lodDistances[0] * TheCamera.LODDistMultiplier)
		return m_atomics[0];
	return nil;
}

void
CSimpleModelInfo::FindRelatedModel(int32 minID, int32 maxID)
{
	int i;
	CBaseModelInfo *mi;
	for(i = minID; i <= maxID; i++){
		mi = CModelInfo::GetModelInfo(i);
		if(mi && mi != this &&
		   !CGeneral::faststrcmp(GetName()+3, mi->GetName()+3)){
			assert(mi->IsSimple());
			this->SetRelatedModel((CSimpleModelInfo*)mi);
			return;
		}
	}
}

#define NEAR_DRAW_DIST 0.0f	// 100.0f in liberty city

void
CSimpleModelInfo::SetupBigBuilding(int32 minID, int32 maxID)
{
	CSimpleModelInfo *related;
	if(m_lodDistances[0] > LOD_DISTANCE && GetRelatedModel() == nil){
		m_isBigBuilding = 1;
		FindRelatedModel(minID, maxID);
		related = GetRelatedModel();
		if(related){
			m_lodDistances[2] = related->GetLargestLodDistance()/TheCamera.LODDistMultiplier;
			if(m_drawLast){
				m_drawLast = false;
				debug("%s was draw last\n", GetName());
			}
		}else
			m_lodDistances[2] = NEAR_DRAW_DIST;
	}
}
