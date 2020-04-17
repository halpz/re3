#include "common.h"

#include "General.h"
#include "Ped.h"
#include "NodeName.h"
#include "VisibilityPlugins.h"
#include "ModelInfo.h"

void
CPedModelInfo::DeleteRwObject(void)
{
	CClumpModelInfo::DeleteRwObject();
	if(m_hitColModel)
		delete m_hitColModel;
	m_hitColModel = nil;
}

RwObjectNameIdAssocation CPedModelInfo::m_pPedIds[12] = {
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
	CClumpModelInfo::SetClump(clump);
	SetFrameIds(m_pPedIds);
	if(m_hitColModel == nil)
		CreateHitColModel();
	if(strncmp(GetName(), "player", 7) == 0)
		RpClumpForAllAtomics(m_clump, SetAtomicRendererCB, (void*)CVisibilityPlugins::RenderPlayerCB);
}

RpAtomic*
CountAtomicsCB(RpAtomic *atomic, void *data)
{
	(*(int32*)data)++;
	return atomic;
}

RpAtomic*
GetAtomicListCB(RpAtomic *atomic, void *data)
{
	**(RpAtomic***)data = atomic;
	(*(RpAtomic***)data)++;
	return atomic;
}

RwFrame*
FindPedFrameFromNameCB(RwFrame *frame, void *data)
{
	RwObjectNameAssociation *assoc = (RwObjectNameAssociation*)data;

	if(CGeneral::faststricmp(GetFrameNodeName(frame)+1, assoc->name+1)){
		RwFrameForAllChildren(frame, FindPedFrameFromNameCB, assoc);
		return assoc->frame ? nil : frame;
	}else{
		assoc->frame = frame;
		return nil;
	}
}

void
CPedModelInfo::SetLowDetailClump(RpClump *lodclump)
{
	RpAtomic *atomics[16];
	RpAtomic **pAtm;
	int32 numAtm, numLodAtm;
	int i;
	RwObjectNameAssociation assoc;

	numAtm = 0;
	numLodAtm = 0;
	RpClumpForAllAtomics(m_clump, CountAtomicsCB, &numAtm);		// actually unused
	RpClumpForAllAtomics(lodclump, CountAtomicsCB, &numLodAtm);

	RpClumpForAllAtomics(m_clump, SetAtomicRendererCB, (void*)CVisibilityPlugins::RenderPedHiDetailCB);
	RpClumpForAllAtomics(lodclump, SetAtomicRendererCB, (void*)CVisibilityPlugins::RenderPedLowDetailCB);

	pAtm = atomics;
	RpClumpForAllAtomics(lodclump, GetAtomicListCB, &pAtm);

	for(i = 0; i < numLodAtm; i++){
		assoc.name = GetFrameNodeName(RpAtomicGetFrame(atomics[i]));
		assoc.frame = nil;
		RwFrameForAllChildren(RpClumpGetFrame(m_clump), FindPedFrameFromNameCB, &assoc);
		if(assoc.frame){
			RpAtomicSetFrame(atomics[i], assoc.frame);
			RpClumpRemoveAtomic(lodclump, atomics[i]);
			RpClumpAddAtomic(m_clump, atomics[i]);
		}
	}
}

struct ColNodeInfo
{
	char *name;
	int pedNode;
	int pieceType;
	float x, z;
	float radius;
};

#define NUMPEDINFONODES 8
ColNodeInfo m_pColNodeInfos[NUMPEDINFONODES] = {
	{ nil,          PED_HEAD,		PEDPIECE_HEAD,  0.0f,   0.05f, 0.2f },
	{ "Storso",     0,				PEDPIECE_TORSO,  0.0f,   0.15f, 0.2f },
	{ "Storso",     0,				PEDPIECE_TORSO,  0.0f,  -0.05f, 0.3f },
	{ nil,          PED_MID,		PEDPIECE_MID,  0.0f,  -0.07f, 0.3f },
	{ nil,          PED_UPPERARML,	PEDPIECE_LEFTARM,  0.07f, -0.1f,  0.2f },
	{ nil,          PED_UPPERARMR,	PEDPIECE_RIGHTARM, -0.07f, -0.1f,  0.2f },
	{ "Slowerlegl", 0,				PEDPIECE_LEFTLEG,  0.0f,   0.07f, 0.25f },
	{ nil,          PED_LOWERLEGR,	PEDPIECE_RIGHTLEG,  0.0f,   0.07f, 0.25f },
};

RwObject*
FindHeadRadiusCB(RwObject *object, void *data)
{
	RpAtomic *atomic = (RpAtomic*)object;
	*(float*)data = RpAtomicGetBoundingSphere(atomic)->radius;
	return nil;
}

void
CPedModelInfo::CreateHitColModel(void)
{
	RwObjectNameAssociation nameAssoc;
	RwObjectIdAssociation idAssoc;
	CVector center;
	RwFrame *nodeFrame;
	CColModel *colmodel = new CColModel;
	CColSphere *spheres = (CColSphere*)RwMalloc(NUMPEDINFONODES*sizeof(CColSphere));
	RwFrame *root = RpClumpGetFrame(m_clump);
	RwMatrix *mat = RwMatrixCreate();
	for(int i = 0; i < NUMPEDINFONODES; i++){
		nodeFrame = nil;
		if(m_pColNodeInfos[i].name){
			nameAssoc.name = m_pColNodeInfos[i].name;
			nameAssoc.frame = nil;
			RwFrameForAllChildren(root, FindFrameFromNameCB, &nameAssoc);
			nodeFrame = nameAssoc.frame;
		}else{
			idAssoc.id = m_pColNodeInfos[i].pedNode;
			idAssoc.frame = nil;
			RwFrameForAllChildren(root, FindFrameFromIdCB, &idAssoc);
			nodeFrame = idAssoc.frame;
		}
		if(nodeFrame){
			float radius = m_pColNodeInfos[i].radius;
			if(m_pColNodeInfos[i].pieceType == 6)
				RwFrameForAllObjects(nodeFrame, FindHeadRadiusCB, &radius);
			RwMatrixTransform(mat, RwFrameGetMatrix(nodeFrame), rwCOMBINEREPLACE);
			const char *name = GetFrameNodeName(nodeFrame);
			for(nodeFrame = RwFrameGetParent(nodeFrame);
			    nodeFrame; 
			    nodeFrame = RwFrameGetParent(nodeFrame)){
				name = GetFrameNodeName(nodeFrame);
				RwMatrixTransform(mat, RwFrameGetMatrix(nodeFrame), rwCOMBINEPOSTCONCAT);
				if(RwFrameGetParent(nodeFrame) == root)
					break;
			}
			center.x = mat->pos.x + m_pColNodeInfos[i].x;
			center.y = mat->pos.y + 0.0f;
			center.z = mat->pos.z + m_pColNodeInfos[i].z;
			spheres[i].Set(radius, center, 17, m_pColNodeInfos[i].pieceType);
		}
	}
	RwMatrixDestroy(mat);
	colmodel->spheres = spheres;
	colmodel->numSpheres = NUMPEDINFONODES;
	center.x = center.y = center.z = 0.0f;
	colmodel->boundingSphere.Set(2.0f, center, 0, 0);
	CVector min, max;
	min.x = min.y = -0.5f;
	min.z = -1.2f;
	max.x = max.y = 0.5f;
	max.z = 1.2f;
	colmodel->boundingBox.Set(min, max, 0, 0);
	colmodel->level = 0;
	m_hitColModel = colmodel;
}

CColModel*
CPedModelInfo::AnimatePedColModel(CColModel* colmodel, RwFrame* frame)
{
	RwObjectNameAssociation nameAssoc;
	RwObjectIdAssociation idAssoc;
	RwMatrix* mat = RwMatrixCreate();
	CColSphere* spheres = colmodel->spheres;

	for (int i = 0; i < NUMPEDINFONODES; i++) {
		RwFrame* f = nil;
		if (m_pColNodeInfos[i].name) {
			nameAssoc.name = m_pColNodeInfos[i].name;
			nameAssoc.frame = nil;
			RwFrameForAllChildren(frame, FindFrameFromNameCB, &nameAssoc);
			f = nameAssoc.frame;
		}
		else {
			idAssoc.id = m_pColNodeInfos[i].pedNode;
			idAssoc.frame = nil;
			RwFrameForAllChildren(frame, FindFrameFromIdCB, &idAssoc);
			f = idAssoc.frame;
		}
		if (f) {
			RwMatrixCopy(mat, RwFrameGetMatrix(f));

			for (f = RwFrameGetParent(f); f; f = RwFrameGetParent(f)) {
				RwMatrixTransform(mat, RwFrameGetMatrix(f), rwCOMBINEPOSTCONCAT);
				if (RwFrameGetParent(f) == frame)
					break;
			}

			spheres[i].center.x = mat->pos.x + m_pColNodeInfos[i].x;
			spheres[i].center.y = mat->pos.y + 0.0f;
			spheres[i].center.z = mat->pos.z + m_pColNodeInfos[i].z;
		}
	}

	return colmodel;
}
