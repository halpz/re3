#include "common.h"

#include "main.h"
#include "General.h"
#include "Renderer.h"
#include "Camera.h"
#include "Renderer.h"
#include "ModelInfo.h"
#include "AnimManager.h"
#include "custompipes.h"
#include "Streaming.h"
#include "smallHeap.h"
#include "Leeds.h"

TempIdeData m_sTempIdeData[800];

base::cRelocatableChunkClassInfo CSimpleModelInfo::msClassInfo("CSimpleModelInfo", VTABLE_ADDR(&msClassInstance), sizeof(msClassInstance));
CSimpleModelInfo CSimpleModelInfo::msClassInstance;

void
CSimpleModelInfo::DeleteRwObject(void)
{
	int i;
	RwFrame *f;
	if(m_atomics == nil)
		return;
	if(!gUseChunkFiles){
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
	}else if(m_chunk){
		CStreaming::UnregisterPointer(&m_atomics, 2);
		for(i = 0; i < m_numAtomics; i++)
			CStreaming::UnregisterAtomic(m_atomics[i], nil);
		DeleteChunk();
		RemoveTexDictionaryRef();
		if(GetAnimFileIndex() != -1)
			CAnimManager::RemoveAnimBlockRef(GetAnimFileIndex());
	}
	m_atomics = nil;
}

RwObject*
CSimpleModelInfo::CreateInstance(void)
{
	RpAtomic *atomic;
	if(m_atomics == nil || m_atomics[0] == nil)
		return nil;
	atomic = RpAtomicClone(m_atomics[0]);
	RpAtomicSetFrame(atomic, RwFrameCreate());
	CStreaming::RegisterInstance(atomic, nil);
	return (RwObject*)atomic;
}

RwObject*
CSimpleModelInfo::CreateInstance(RwMatrix *matrix)
{
	RpAtomic *atomic;
	RwFrame *frame;

	if(m_atomics == nil || m_atomics[0] == nil)
		return nil;
	atomic = RpAtomicClone(m_atomics[0]);
	frame = RwFrameCreate();
	*RwFrameGetMatrix(frame) = *matrix;
	RpAtomicSetFrame(atomic, frame);
	CStreaming::RegisterInstance(atomic, nil);
	return (RwObject*)atomic;
}

void
CSimpleModelInfo::Init(void)
{
	m_atomics = new RpAtomic*[3];
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
	m_relatedModel = nil;
}

void
CSimpleModelInfo::SetAtomic(int n, RpAtomic *atomic)
{
	if(m_atomics == nil){
		m_atomics = new RpAtomic*[3];
		m_atomics[0] = nil;
		m_atomics[1] = nil;
		m_atomics[2] = nil;
	}
	m_atomics[n] = atomic;
	AddTexDictionaryRef();
	if(GetAnimFileIndex() != -1)
		CAnimManager::AddAnimBlockRef(GetAnimFileIndex());
	RpGeometry *geo = RpAtomicGetGeometry(atomic);
	if(m_ignoreLight)
		RpGeometrySetFlags(geo, RpGeometryGetFlags(geo) & ~rpGEOMETRYLIGHT);
/*
	if(RpGeometryGetFlags(geo) & rpGEOMETRYNORMALS &&
	   RpGeometryGetNumTriangles(geo) > 200)
		debug("%s has %d polys\n", m_name, RpGeometryGetNumTriangles(geo));
*/

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
CSimpleModelInfo::GetLodAtomic(int n)
{
	if(m_atomics == nil || n >= m_numAtomics)
		return nil;
	return m_atomics[n];
}

RpAtomic*
CSimpleModelInfo::GetLastAtomic(void)
{
	if(m_atomics == nil)
		return nil;
	if(m_firstDamaged == 0 || m_isDamaged)
		return m_atomics[m_numAtomics-1];
	else
		return m_atomics[m_firstDamaged-1];
}

RpAtomic*
CSimpleModelInfo::GetLastAtomic(float dist)
{
	int n;
	if(m_atomics == nil)
		return nil;
	if(m_firstDamaged == 0 || m_isDamaged)
		n = m_numAtomics-1;
	else
		n = m_firstDamaged-1;
	if(dist < m_lodDistances[n] * TheCamera.LODDistMultiplier)
		return m_atomics[n];
	return nil;
}

RpAtomic*
CSimpleModelInfo::GetAtomicFromDistance(float dist)
{
	int i;
	i = 0;
	if(m_atomics == nil)
		return nil;
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
	if(m_atomics == nil)
		return nil;
	if(dist < m_lodDistances[0] * TheCamera.LODDistMultiplier)
		return m_atomics[0];
	return nil;
}

void
CSimpleModelInfo::FindRelatedModel(void)
{
	CBaseModelInfo *mi;
	int thisIndex, otherIndex;

	// find our own index in temp data
	for(thisIndex = 0; thisIndex < ARRAY_SIZE(m_sTempIdeData); thisIndex++){
		if(m_sTempIdeData[thisIndex].id == -1)
			break;
		if(this == CModelInfo::GetModelInfo(m_sTempIdeData[thisIndex].id))
			goto found;
	}
	thisIndex = -1;
found:
#ifdef FIX_BUGS
	if(thisIndex == -1)
		return;
#endif

	for(otherIndex = 0; otherIndex < ARRAY_SIZE(m_sTempIdeData); otherIndex++){
		if(m_sTempIdeData[otherIndex].id == -1)
			break;

		mi = CModelInfo::GetModelInfo(m_sTempIdeData[otherIndex].id);
		if(mi && mi != this &&
		   !CGeneral::faststrcmp(m_sTempIdeData[thisIndex].name+3, m_sTempIdeData[otherIndex].name+3)){
			assert(mi->IsSimple());
			this->SetRelatedModel((CSimpleModelInfo*)mi);
			return;
		}
	}
}

#define NEAR_DRAW_DIST 100.0f	// 0.0f in vice city

void
CSimpleModelInfo::SetupBigBuilding(void)
{
	CSimpleModelInfo *related;
	if(m_lodDistances[0] < 0.0f)
		m_lodDistances[0] = -m_lodDistances[0];	// what?
	else if(m_lodDistances[0] > LOD_DISTANCE && GetRelatedModel() == nil){
		m_isBigBuilding = 1;
		FindRelatedModel();
		related = GetRelatedModel();
		if(related){
			m_lodDistances[2] = related->GetLargestLodDistance()/TheCamera.LODDistMultiplier;
			if(m_drawLast){
				m_drawLast = false;
				debug("%s was draw last\n", GetModelName());
			}
		}else
			m_lodDistances[2] = NEAR_DRAW_DIST;
	}
}


void
CSimpleModelInfo::LoadModel(void *atomics, const void *chunk)
{
	int i;
	m_chunk = (void*)chunk;
	m_atomics = (RpAtomic**)atomics;
	CStreaming::RegisterPointer(m_chunk, 2, true);
	CStreaming::RegisterPointer(m_atomics, 2, true);
	for(i = 0; i < m_numAtomics; i++){
		LoadResource(m_atomics[i]);
		CStreaming::RegisterAtomic(m_atomics[i], nil);
	}
}

void
CSimpleModelInfo::Write(base::cRelocatableChunkWriter &writer)
{
	CBaseModelInfo::Write(writer);
	if(WriteModel(writer))
		writer.AddPatch(&m_atomics);
	else
		m_atomics = nil;
	if(m_isBigBuilding)
		writer.AddPatch(&m_relatedModel);
}

void*
CSimpleModelInfo::WriteModel(base::cRelocatableChunkWriter &writer)
{
	int i;
	if(m_atomics == nil || m_atomics[0] == nil)
		return nil;

	// remove empty atomics
	int numAtomics = 0;
	for(i = 0; i < m_numAtomics; i++)
		if(m_atomics[i]){
			m_atomics[numAtomics] = m_atomics[i];
#ifdef FIX_BUGS
			m_lodDistances[numAtomics] = m_lodDistances[i];
#endif
			numAtomics++;
		}
	if(m_firstDamaged){
		int firstDam = m_firstDamaged - m_numAtomics + numAtomics;
		if(firstDam < numAtomics)
			m_firstDamaged = firstDam;
		else
			m_firstDamaged = 0;
	}
	m_numAtomics = numAtomics;

	// write the actual models
	writer.AllocateRaw(m_atomics, m_numAtomics*sizeof(void*), sizeof(void*), false, true);
	for(i = 0; m_numAtomics; i++){
		writer.AddPatch(&m_atomics[i]);
		SaveResource(m_atomics[i], writer);
	}
	return m_atomics;
}

void
CSimpleModelInfo::RcWriteThis(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), 0x10, false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}

void
CSimpleModelInfo::RcWriteEmpty(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), 0x10, false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}
