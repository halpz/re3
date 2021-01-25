#include "common.h"

#include "main.h"
#include "RwHelper.h"
#include "General.h"
#include "Bones.h"
#include "SurfaceTable.h"
#include "Ped.h"
#include "NodeName.h"
#include "VisibilityPlugins.h"
#include "ModelInfo.h"
#include "custompipes.h"
#include "Streaming.h"
#include "Leeds.h"
#include "TempColModels.h"

base::cRelocatableChunkClassInfo CPedModelInfo::msClassInfo("CPedModelInfo", VTABLE_ADDR(&msClassInstance), sizeof(msClassInstance));
CPedModelInfo CPedModelInfo::msClassInstance;

void
CPedModelInfo::DeleteRwObject(void)
{
	CStreaming::UnregisterPointer(&m_hitColModel, 2);
	CClumpModelInfo::DeleteRwObject();
	if(!gUseChunkFiles && m_hitColModel)
		delete m_hitColModel;
	m_hitColModel = nil;
}

// leftover...
RwObjectNameIdAssocation CPedModelInfo::m_pPedIds[PED_NODE_MAX] = {
	{ "Smid",	PED_MID, 0, },	// that is strange...
	{ "Shead",	PED_HEAD, 0, },
	{ "Supperarml",	PED_UPPERARML, 0, },
	{ "Supperarmr",	PED_UPPERARMR, 0, },
	{ "SLhand",	PED_HANDL, 0, },
	{ "SRhand",	PED_HANDR, 0, },
	{ "Supperlegl",	PED_UPPERLEGL, 0, },
	{ "Supperlegr",	PED_UPPERLEGR, 0, },
	{ "Sfootl",	PED_FOOTL, 0, },
	{ "Sfootr",	PED_FOOTR, 0, },
	{ "Slowerlegr",	PED_LOWERLEGR, 0, },
	{ nil,	0, 0, },
};

void
CPedModelInfo::SetClump(RpClump *clump)
{
#ifdef EXTENDED_PIPELINES
	CustomPipes::AttachRimPipe(clump);
#endif
	if(!IsClumpSkinned(clump))
		return;
	CClumpModelInfo::SetClump(clump);
	SetFrameIds(m_pPedIds);	// not needed in VC actually
	if(m_hitColModel == nil)
		CreateHitColModelSkinned(clump);
	RpClumpForAllAtomics(m_clump, SetAtomicRendererCB, (void*)CVisibilityPlugins::RenderPedCB);
	//if(strcmp(GetModelName(), "player") == 0)
	//	RpClumpForAllAtomics(m_clump, SetAtomicRendererCB, (void*)CVisibilityPlugins::RenderPlayerCB);
}

struct ColNodeInfo
{
	Const char *name;
	int pedNode;
	int pieceType;
	float x, z;
	float radius;
};

#define NUMPEDINFONODES 10
ColNodeInfo m_pColNodeInfos[NUMPEDINFONODES] = {
	{ nil, PED_HEAD,	PEDPIECE_HEAD,	0.0f,   0.05f, 0.15f },
	{ nil, PED_MID,		PEDPIECE_TORSO,	0.0f,   0.15f, 0.2f },
	{ nil, PED_MID,		PEDPIECE_TORSO,	0.0f,  -0.05f, 0.25f },
	{ nil, PED_MID,		PEDPIECE_MID,	0.0f,  -0.25f, 0.25f },
	{ nil, PED_UPPERARML,	PEDPIECE_LEFTARM,	0.03f, -0.05f,  0.16f },
	{ nil, PED_UPPERARMR,	PEDPIECE_RIGHTARM,	-0.03f, -0.05f,  0.16f },
	{ nil, PED_LOWERLEGL,	PEDPIECE_LEFTLEG,	0.0f,   0.15f, 0.2f },
	{ nil, PED_LOWERLEGR,	PEDPIECE_RIGHTLEG,	0.0f,   0.15f, 0.2f },
	{ nil, PED_FOOTL,	PEDPIECE_LEFTLEG,	0.0f,   0.15f, 0.15f },
	{ nil, PED_FOOTR,	PEDPIECE_RIGHTLEG,	0.0f,   0.15f, 0.15f },
};

bool
CPedModelInfo::CreateHitColModelSkinned(RpClump *clump)
{
	CColModel *colmodel = new CColModel;
	CColSphere *spheres = (CColSphere*)RwMalloc(NUMPEDINFONODES*sizeof(CColSphere));

	for(int i = 0; i < NUMPEDINFONODES; i++){
		spheres[i].center.x = 0.0f;
		spheres[i].center.y = 0.0f;
		spheres[i].center.z = 0.0f;
		spheres[i].radius = m_pColNodeInfos[i].radius;
		spheres[i].surface = SURFACE_PED;
		spheres[i].piece = m_pColNodeInfos[i].pieceType;
	}
	colmodel->spheres = spheres;
	colmodel->numSpheres = NUMPEDINFONODES;
	colmodel->boundingSphere.Set(2.0f, CVector(0.0f, 0.0f, 0.0f));
	colmodel->boundingBox.Set(CVector(-0.5f, -0.5f, -1.2f), CVector(0.5f, 0.5f, 1.2f));
	colmodel->level = LEVEL_GENERIC;
	m_hitColModel = colmodel;
	return true;
}

CColModel*
CPedModelInfo::AnimatePedColModelSkinned(RpClump *clump)
{
	if(m_hitColModel == nil){
		CreateHitColModelSkinned(clump);
#ifndef FIX_BUGS
		return m_hitColModel;
#endif
		// we should really animate this now
	}
	RwMatrix invmat, mat;
	CColSphere *spheres = m_hitColModel->spheres;
	RpHAnimHierarchy *hier = GetAnimHierarchyFromSkinClump(clump);
	RwMatrixInvert(&invmat, RwFrameGetMatrix(RpClumpGetFrame(clump)));

	for(int i = 0; i < NUMPEDINFONODES; i++){
		mat = invmat;
		int id = ConvertPedNode2BoneTag(m_pColNodeInfos[i].pedNode);
		int idx = RpHAnimIDGetIndex(hier, id);

		RwMatrixTransform(&mat, &RpHAnimHierarchyGetMatrixArray(hier)[idx], rwCOMBINEPRECONCAT);
		RwV3d pos = { 0.0f, 0.0f, 0.0f };	// actually CVector
		RwV3dTransformPoints(&pos, &pos, 1, &mat);

		spheres[i].center = pos + CVector(m_pColNodeInfos[i].x, 0.0f, m_pColNodeInfos[i].z);
	}
	return m_hitColModel;
}

CColModel*
CPedModelInfo::AnimatePedColModelSkinnedWorld(RpClump *clump)
{
	if(m_hitColModel == nil)
		CreateHitColModelSkinned(clump);
	CColSphere *spheres = m_hitColModel->spheres;
	RpHAnimHierarchy *hier = GetAnimHierarchyFromSkinClump(clump);
	RwMatrix *mat;

	for(int i = 0; i < NUMPEDINFONODES; i++){
		int id = ConvertPedNode2BoneTag(m_pColNodeInfos[i].pedNode);
		int idx = RpHAnimIDGetIndex(hier, id);

		mat = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
		RwV3d pos = { 0.0f, 0.0f, 0.0f };	// actually CVector
		RwV3dTransformPoints(&pos, &pos, 1, mat);

		spheres[i].center = pos + CVector(m_pColNodeInfos[i].x, 0.0f, m_pColNodeInfos[i].z);
	}
	return m_hitColModel;
}


struct PedChunk
{
	CColModel *colmodel;
	RpClump *clump;
};

void
CPedModelInfo::LoadModel(void *data, const void *chunk)
{
	PedChunk *chk = (PedChunk*)data;
	m_hitColModel = chk->colmodel;
	CStreaming::RegisterPointer(&m_hitColModel, 2, true);
	CClumpModelInfo::LoadModel(chk->clump, chunk);
}

void
CPedModelInfo::Write(base::cRelocatableChunkWriter &writer)
{
	SetColModel(&gpTempColModels->ms_colModelPed1);
	CClumpModelInfo::Write(writer);
	if(m_hitColModel){
		writer.AddPatch(&m_hitColModel);
		m_hitColModel->Write(writer, true);
	}
}

void*
CPedModelInfo::WriteModel(base::cRelocatableChunkWriter &writer)
{
	PedChunk *chunk = new PedChunk;	// LEAK
	chunk->colmodel = nil;
	chunk->clump = nil;
	writer.AllocateRaw(chunk, sizeof(*chunk), sizeof(void*), false, true);

	chunk->clump = (RpClump*)CClumpModelInfo::WriteModel(writer);
	if(chunk->clump)
		writer.AddPatch(&chunk->clump);

	chunk->colmodel = m_hitColModel;
	if(chunk->colmodel){
		writer.AddPatch(&chunk->colmodel);
		chunk->colmodel->Write(writer, true);
	}
	return nil;
}

void
CPedModelInfo::RcWriteThis(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), sizeof(void*), false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}

void
CPedModelInfo::RcWriteEmpty(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), sizeof(void*), false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}
