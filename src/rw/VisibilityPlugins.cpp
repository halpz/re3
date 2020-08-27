#include "common.h"

#include "templates.h"
#include "Entity.h"
#include "ModelInfo.h"
#include "Lights.h"
#include "RwHelper.h"
#include "Renderer.h"
#include "Camera.h"
#include "VisibilityPlugins.h"
#include "World.h"
#include "custompipes.h"

//--MIAMI: file done

#define FADE_DISTANCE 20.0f

CLinkList<CVisibilityPlugins::AlphaObjectInfo> CVisibilityPlugins::m_alphaList;
CLinkList<CVisibilityPlugins::AlphaObjectInfo> CVisibilityPlugins::m_alphaBoatAtomicList;
CLinkList<CVisibilityPlugins::AlphaObjectInfo> CVisibilityPlugins::m_alphaEntityList;
CLinkList<CVisibilityPlugins::AlphaObjectInfo> CVisibilityPlugins::m_alphaUnderwaterEntityList;

int32 CVisibilityPlugins::ms_atomicPluginOffset = -1;
int32 CVisibilityPlugins::ms_framePluginOffset = -1;
int32 CVisibilityPlugins::ms_clumpPluginOffset = -1;

RwCamera *CVisibilityPlugins::ms_pCamera;
RwV3d *CVisibilityPlugins::ms_pCameraPosn;
float CVisibilityPlugins::ms_cullCompsDist;
float CVisibilityPlugins::ms_vehicleLod0Dist;
float CVisibilityPlugins::ms_vehicleLod1Dist;
float CVisibilityPlugins::ms_vehicleFadeDist;
float CVisibilityPlugins::ms_bigVehicleLod0Dist;
float CVisibilityPlugins::ms_bigVehicleLod1Dist;
float CVisibilityPlugins::ms_pedLod1Dist;
float CVisibilityPlugins::ms_pedFadeDist;

void
CVisibilityPlugins::Initialise(void)
{
	m_alphaList.Init(NUMALPHALIST);
	m_alphaList.head.item.sort = 0.0f;
	m_alphaList.tail.item.sort = 100000000.0f;

	m_alphaBoatAtomicList.Init(NUMBOATALPHALIST);
	m_alphaBoatAtomicList.head.item.sort = 0.0f;
	m_alphaBoatAtomicList.tail.item.sort = 100000000.0f;

#ifdef ASPECT_RATIO_SCALE
	// default 150 if not enough for bigger FOVs
	m_alphaEntityList.Init(NUMALPHAENTITYLIST * 3);
#else
	m_alphaEntityList.Init(NUMALPHAENTITYLIST);
#endif // ASPECT_RATIO_SCALE
	m_alphaEntityList.head.item.sort = 0.0f;
	m_alphaEntityList.tail.item.sort = 100000000.0f;

	m_alphaUnderwaterEntityList.Init(NUMALPHAUNTERWATERENTITYLIST);
	m_alphaUnderwaterEntityList.head.item.sort = 0.0f;
	m_alphaUnderwaterEntityList.tail.item.sort = 100000000.0f;

}

void
CVisibilityPlugins::Shutdown(void)
{
	m_alphaList.Shutdown();
	m_alphaBoatAtomicList.Shutdown();
	m_alphaEntityList.Shutdown();
	m_alphaUnderwaterEntityList.Shutdown();
}

void
CVisibilityPlugins::InitAlphaEntityList(void)
{
	m_alphaEntityList.Clear();
	m_alphaBoatAtomicList.Clear();
	m_alphaUnderwaterEntityList.Clear();
}

bool
CVisibilityPlugins::InsertEntityIntoSortedList(CEntity *e, float dist)
{
	AlphaObjectInfo item;
	item.entity = e;
	item.sort = dist;
	if(e->bUnderwater && m_alphaUnderwaterEntityList.InsertSorted(item))
		return true;
	return !!m_alphaEntityList.InsertSorted(item);
}

void
CVisibilityPlugins::InitAlphaAtomicList(void)
{
	m_alphaList.Clear();
}

bool
CVisibilityPlugins::InsertAtomicIntoSortedList(RpAtomic *a, float dist)
{
	AlphaObjectInfo item;
	item.atomic = a;
	item.sort = dist;
	return !!m_alphaList.InsertSorted(item);
}

bool
CVisibilityPlugins::InsertAtomicIntoBoatSortedList(RpAtomic *a, float dist)
{
	AlphaObjectInfo item;
	item.atomic = a;
	item.sort = dist;
	return !!m_alphaBoatAtomicList.InsertSorted(item);
}

void
CVisibilityPlugins::SetRenderWareCamera(RwCamera *camera)
{
	ms_pCamera = camera;
	ms_pCameraPosn = RwMatrixGetPos(RwFrameGetMatrix(RwCameraGetFrame(camera)));

	if(TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_TOPDOWN ||
	   TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_TOP_DOWN_PED)
		ms_cullCompsDist = 1000000.0f;
	else
		ms_cullCompsDist = sq(TheCamera.LODDistMultiplier * 20.0f);

        ms_vehicleLod0Dist = sq(70.0f * TheCamera.GenerationDistMultiplier);
        ms_vehicleLod1Dist = sq(90.0f * TheCamera.GenerationDistMultiplier);
        ms_vehicleFadeDist = sq(100.0f * TheCamera.GenerationDistMultiplier);
        ms_bigVehicleLod0Dist = sq(60.0f * TheCamera.GenerationDistMultiplier);
        ms_bigVehicleLod1Dist = sq(150.0f * TheCamera.GenerationDistMultiplier);
        ms_pedLod1Dist = sq(60.0f * TheCamera.LODDistMultiplier);
        ms_pedFadeDist = sq(70.0f * TheCamera.LODDistMultiplier);
}

static float DistToCameraSq;
static float PitchToCamera;

void
CVisibilityPlugins::SetupVehicleVariables(RpClump *vehicle)
{
	if (RwObjectGetType((RwObject*)vehicle) != rpCLUMP)
		return;
	DistToCameraSq = GetDistanceSquaredFromCamera(RpClumpGetFrame(vehicle));
	RwV3d distToCam;
	RwV3dSub(&distToCam, ms_pCameraPosn, &RwFrameGetMatrix(RpClumpGetFrame(vehicle))->pos);
	float dist2d = Sqrt(SQR(distToCam.x) + SQR(distToCam.y));
	PitchToCamera = Atan2(distToCam.z, dist2d);
}

RpMaterial*
SetAlphaCB(RpMaterial *material, void *data)
{
	((RwRGBA*)RpMaterialGetColor(material))->alpha = (uint8)(uintptr)data;
	return material;
}

RpMaterial*
SetTextureCB(RpMaterial *material, void *data)
{
	RpMaterialSetTexture(material, (RwTexture*)data);
	return material;
}

void
CVisibilityPlugins::RenderAtomicList(CLinkList<AlphaObjectInfo> &list)
{
	CLink<AlphaObjectInfo> *node;
	for(node = list.tail.prev; node != &list.head; node = node->prev)
		AtomicDefaultRenderCallBack(node->item.atomic);
}

void
CVisibilityPlugins::RenderAlphaAtomics(void)
{
	RenderAtomicList(m_alphaList);
}

void
CVisibilityPlugins::RenderBoatAlphaAtomics(void)
{
	SetCullMode(rwCULLMODECULLNONE);
	RenderAtomicList(m_alphaBoatAtomicList);
	SetCullMode(rwCULLMODECULLBACK);
}

void
CVisibilityPlugins::RenderFadingEntities(CLinkList<AlphaObjectInfo> &list)
{
	CLink<AlphaObjectInfo> *node;
	CSimpleModelInfo *mi;
	for(node = list.tail.prev; node != &list.head; node = node->prev){
		CEntity *e = node->item.entity;
		if(e->m_rwObject == nil)
			continue;
#ifdef EXTENDED_PIPELINES
		if(CustomPipes::bRenderingEnvMap && (e->IsPed() || e->IsVehicle()))
			continue;
#endif
		mi = (CSimpleModelInfo *)CModelInfo::GetModelInfo(e->GetModelIndex());
		if(mi->GetModelType() == MITYPE_SIMPLE && mi->m_noZwrite)
			RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, FALSE);

		if(e->bDistanceFade){
			DeActivateDirectional();
			SetAmbientColours();
			e->bImBeingRendered = true;
			RenderFadingAtomic((RpAtomic*)e->m_rwObject, node->item.sort);
			e->bImBeingRendered = false;
		}else
			CRenderer::RenderOneNonRoad(e);

		if(mi->GetModelType() == MITYPE_SIMPLE && mi->m_noZwrite)
			RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	}
}

void
CVisibilityPlugins::RenderFadingEntities(void)
{
	RenderFadingEntities(m_alphaEntityList);
	RenderBoatAlphaAtomics();
}

void
CVisibilityPlugins::RenderFadingUnderwaterEntities(void)
{
	RenderFadingEntities(m_alphaUnderwaterEntityList);
}

RpAtomic*
CVisibilityPlugins::RenderWheelAtomicCB(RpAtomic *atomic)
{
	RpAtomic *lodatm;
	float len;
	CSimpleModelInfo *mi;

	mi = GetAtomicModelInfo(atomic);
	len = Sqrt(DistToCameraSq);
	lodatm = mi->GetAtomicFromDistance(len * TheCamera.LODDistMultiplier / TheCamera.GenerationDistMultiplier);
	if(lodatm){
		if(RpAtomicGetGeometry(lodatm) != RpAtomicGetGeometry(atomic))
			RpAtomicSetGeometry(atomic, RpAtomicGetGeometry(lodatm), rpATOMICSAMEBOUNDINGSPHERE);
		AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderObjNormalAtomic(RpAtomic *atomic)
{
	RwMatrix *m;
	RwV3d view;
	float len;

	m = RwFrameGetLTM(RpAtomicGetFrame(atomic));
	RwV3dSub(&view, RwMatrixGetPos(m), ms_pCameraPosn);
	len = RwV3dLength(&view);
	if(RwV3dDotProduct(&view, RwMatrixGetUp(m)) < -0.3f*len && len > 8.0f)
		return atomic;
	AtomicDefaultRenderCallBack(atomic);
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderAlphaAtomic(RpAtomic *atomic, int alpha)
{
	RpGeometry *geo;
	uint32 flags;

	geo = RpAtomicGetGeometry(atomic);
	flags = RpGeometryGetFlags(geo);
	RpGeometrySetFlags(geo, flags | rpGEOMETRYMODULATEMATERIALCOLOR);
	RpGeometryForAllMaterials(geo, SetAlphaCB, (void*)alpha);
	AtomicDefaultRenderCallBack(atomic);
	RpGeometryForAllMaterials(geo, SetAlphaCB, (void*)255);
	RpGeometrySetFlags(geo, flags);
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderWeaponCB(RpAtomic *atomic)
{
	RwMatrix *m;
	RwV3d view;
	float maxdist, distsq;
	CSimpleModelInfo *mi;

	mi = GetAtomicModelInfo(atomic);
	m = RwFrameGetLTM(RpAtomicGetFrame(atomic));
	RwV3dSub(&view, RwMatrixGetPos(m), ms_pCameraPosn);
	maxdist = mi->GetLodDistance(0);
	distsq = RwV3dDotProduct(&view, &view);
	if(distsq < maxdist*maxdist)
		AtomicDefaultRenderCallBack(atomic);
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderFadingAtomic(RpAtomic *atomic, float camdist)
{
	RpAtomic *lodatm;
	float fadefactor;
	uint32 alpha;
	CSimpleModelInfo *mi;

	mi = GetAtomicModelInfo(atomic);
	lodatm = mi->GetAtomicFromDistance(camdist - FADE_DISTANCE);
	if(mi->m_additive)
		AtomicDefaultRenderCallBack(atomic);

	fadefactor = (mi->GetLargestLodDistance() - (camdist - FADE_DISTANCE))/FADE_DISTANCE;
	if(fadefactor > 1.0f)
		fadefactor = 1.0f;
	alpha = mi->m_alpha * fadefactor;
	if(alpha == 255)
		AtomicDefaultRenderCallBack(atomic);
	else{
		RpGeometry *geo = RpAtomicGetGeometry(lodatm);
		uint32 flags = RpGeometryGetFlags(geo);
		RpGeometrySetFlags(geo, flags | rpGEOMETRYMODULATEMATERIALCOLOR);
		RpGeometryForAllMaterials(geo, SetAlphaCB, (void*)alpha);
		if(geo != RpAtomicGetGeometry(atomic))
			RpAtomicSetGeometry(atomic, geo, rpATOMICSAMEBOUNDINGSPHERE); // originally 5 (mistake?)
		AtomicDefaultRenderCallBack(atomic);
		RpGeometryForAllMaterials(geo, SetAlphaCB, (void*)255);
		RpGeometrySetFlags(geo, flags);
	}

	if(mi->m_additive)
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);

	return atomic;
}



RpAtomic*
CVisibilityPlugins::RenderVehicleHiDetailCB(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq < ms_vehicleLod0Dist){
		flags = GetAtomicId(atomic);
		if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f){
			dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
				RwFrameGetLTM(clumpframe), flags);
			if(dot > 0.0f && ((flags & ATOMIC_FLAG_ANGLECULL) || 0.1f*DistToCameraSq < dot*dot))
				return atomic;
		}
		AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleHiDetailAlphaCB(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq < ms_vehicleLod0Dist){
		flags = GetAtomicId(atomic);
		dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
			RwFrameGetLTM(clumpframe), flags);
		if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f)
			if(dot > 0.0f && ((flags & ATOMIC_FLAG_ANGLECULL) || 0.1f*DistToCameraSq < dot*dot))
				return atomic;

		if(flags & ATOMIC_FLAG_DRAWLAST){
			// sort before clump
			if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq - 0.0001f))
				AtomicDefaultRenderCallBack(atomic);
		}else{
			if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq + dot))
				AtomicDefaultRenderCallBack(atomic);
		}
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq < ms_bigVehicleLod0Dist){
		flags = GetAtomicId(atomic);
		if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f){
			dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
				RwFrameGetLTM(clumpframe), flags);
			if(dot > 0.0f)
				return atomic;
		}
		AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq < ms_bigVehicleLod0Dist){
		flags = GetAtomicId(atomic);
		dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
			RwFrameGetLTM(clumpframe), flags);
		if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f)
			if(dot > 0.0f && ((flags & ATOMIC_FLAG_ANGLECULL) || 0.1f*DistToCameraSq < dot*dot))
				return atomic;

		if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq + dot))
			AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleHiDetailCB_Boat(RpAtomic *atomic)
{
	if(DistToCameraSq < ms_bigVehicleLod1Dist)
		AtomicDefaultRenderCallBack(atomic);
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat(RpAtomic *atomic)
{
	if(DistToCameraSq < ms_vehicleLod0Dist){
		if(GetAtomicId(atomic) & ATOMIC_FLAG_DRAWLAST){
			if(!InsertAtomicIntoBoatSortedList(atomic, DistToCameraSq))
				AtomicDefaultRenderCallBack(atomic);
		}else
			AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleLowDetailCB_BigVehicle(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq >= ms_bigVehicleLod0Dist &&
	   DistToCameraSq < ms_bigVehicleLod1Dist){
		flags = GetAtomicId(atomic);
		if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f){
			dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
				RwFrameGetLTM(clumpframe), flags);
			if(dot > 0.0f)
				return atomic;
		}
		AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleLowDetailAlphaCB_BigVehicle(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq >= ms_bigVehicleLod0Dist &&
	   DistToCameraSq < ms_bigVehicleLod1Dist){
		flags = GetAtomicId(atomic);
		dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
			RwFrameGetLTM(clumpframe), flags);
		if(dot > 0.0f)
			if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f)
				return atomic;

		if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq + dot))
			AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleReallyLowDetailCB(RpAtomic *atomic)
{
	RpClump *clump;
	int32 alpha;

	clump = RpAtomicGetClump(atomic);
	if(DistToCameraSq >= ms_vehicleLod0Dist){
		alpha = GetClumpAlpha(clump);
		if(alpha == 255)
			AtomicDefaultRenderCallBack(atomic);
		else
			RenderAlphaAtomic(atomic, alpha);
	}
	return atomic;

}

RpAtomic*
CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle(RpAtomic *atomic)
{
	if(DistToCameraSq >= ms_bigVehicleLod1Dist)
		AtomicDefaultRenderCallBack(atomic);
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderTrainHiDetailCB(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq < ms_bigVehicleLod1Dist){
		flags = GetAtomicId(atomic);
		if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f){
			dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
				RwFrameGetLTM(clumpframe), flags);
			if(dot > 0.0f && ((flags & ATOMIC_FLAG_ANGLECULL) || 0.1f*DistToCameraSq < dot*dot))
				return atomic;
		}
		AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderTrainHiDetailAlphaCB(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	uint32 flags;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq < ms_bigVehicleLod1Dist){
		flags = GetAtomicId(atomic);
		dot = GetDotProductWithCameraVector(RwFrameGetLTM(RpAtomicGetFrame(atomic)),
			RwFrameGetLTM(clumpframe), flags);
		if(DistToCameraSq > ms_cullCompsDist && (flags & ATOMIC_FLAG_NOCULL) == 0 && PitchToCamera < 0.2f)
			if(dot > 0.0f && ((flags & ATOMIC_FLAG_ANGLECULL) || 0.1f*DistToCameraSq < dot*dot))
				return atomic;

		if(flags & ATOMIC_FLAG_DRAWLAST){
			// sort before clump
			if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq - 0.0001f))
				AtomicDefaultRenderCallBack(atomic);
		}else{
			if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq + dot))
				AtomicDefaultRenderCallBack(atomic);
		}
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleRotorAlphaCB(RpAtomic *atomic)
{
	RwFrame *clumpframe;
	float dot;
	RwV3d cam2atm;

	clumpframe = RpClumpGetFrame(RpAtomicGetClump(atomic));
	if(DistToCameraSq < ms_bigVehicleLod1Dist){
		RwV3dSub(&cam2atm, &RwFrameGetLTM(RpAtomicGetFrame(atomic))->pos, ms_pCameraPosn);
		dot = RwV3dDotProduct(&cam2atm, &RwFrameGetLTM(clumpframe)->at);
		if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq + dot*20.0f))
			AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderVehicleTailRotorAlphaCB(RpAtomic *atomic)
{
	RwMatrix *clumpMat, *atmMat;
	float dot;
	RwV3d cam2atm;

	if(DistToCameraSq < ms_bigVehicleLod0Dist){
		atmMat = RwFrameGetLTM(RpAtomicGetFrame(atomic));
		clumpMat = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
		RwV3dSub(&cam2atm, &atmMat->pos, ms_pCameraPosn);
		dot = RwV3dDotProduct(&cam2atm, &clumpMat->up) + RwV3dDotProduct(&cam2atm, &clumpMat->right);
		if(!InsertAtomicIntoSortedList(atomic, DistToCameraSq - dot))
			AtomicDefaultRenderCallBack(atomic);
	}
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderPlayerCB(RpAtomic *atomic)
{
	if(CWorld::Players[0].m_pSkinTexture)
		RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), SetTextureCB, CWorld::Players[0].m_pSkinTexture);
	AtomicDefaultRenderCallBack(atomic);
	return atomic;
}

RpAtomic*
CVisibilityPlugins::RenderPedCB(RpAtomic *atomic)
{
	int32 alpha;
	RwV3d cam2atm;

	RwV3dSub(&cam2atm, &RwFrameGetLTM(RpAtomicGetFrame(atomic))->pos, ms_pCameraPosn);
	if(RwV3dDotProduct(&cam2atm, &cam2atm) < ms_pedLod1Dist){
		alpha = GetClumpAlpha(RpAtomicGetClump(atomic));
		if(alpha == 255)
			AtomicDefaultRenderCallBack(atomic);
		else
			RenderAlphaAtomic(atomic, alpha);
	}
	return atomic;
}

float
CVisibilityPlugins::GetDistanceSquaredFromCamera(RwV3d *pos)
{
	RwV3d dist;
	RwV3dSub(&dist, pos, ms_pCameraPosn);
	return RwV3dDotProduct(&dist, &dist);
}

float
CVisibilityPlugins::GetDistanceSquaredFromCamera(RwFrame *frame)
{
	RwMatrix *m;
	RwV3d dist;
	m = RwFrameGetLTM(frame);
	RwV3dSub(&dist, RwMatrixGetPos(m), ms_pCameraPosn);
	return RwV3dDotProduct(&dist, &dist);
}

float
CVisibilityPlugins::GetDotProductWithCameraVector(RwMatrix *atomicMat, RwMatrix *clumpMat, uint32 flags)
{
	RwV3d dist;
	float dot, dotdoor;

	// Vehicle forward is the y axis (RwMatrix.up)
	// Vehicle right is the x axis (RwMatrix.right)

	RwV3dSub(&dist, RwMatrixGetPos(atomicMat), ms_pCameraPosn);
	// forward/backward facing
	if(flags & (ATOMIC_FLAG_FRONT | ATOMIC_FLAG_REAR))
		dot = RwV3dDotProduct(&dist, RwMatrixGetUp(clumpMat));
	// left/right facing
	else if(flags & (ATOMIC_FLAG_LEFT | ATOMIC_FLAG_RIGHT))
		dot = RwV3dDotProduct(&dist, RwMatrixGetRight(clumpMat));
	else
		dot = 0.0f;
	if(flags & (ATOMIC_FLAG_LEFT | ATOMIC_FLAG_REAR))
		dot = -dot;

	if(flags & (ATOMIC_FLAG_REARDOOR | ATOMIC_FLAG_FRONTDOOR)){
		if(flags & ATOMIC_FLAG_REARDOOR)
			dotdoor = -RwV3dDotProduct(&dist, RwMatrixGetUp(clumpMat));
		else if(flags & ATOMIC_FLAG_FRONTDOOR)
			dotdoor = RwV3dDotProduct(&dist, RwMatrixGetUp(clumpMat));
		else
			dotdoor = 0.0f;

		if(dot < 0.0f && dotdoor < 0.0f)
			dot += dotdoor;
		if(dot > 0.0f && dotdoor > 0.0f)
			dot += dotdoor;
	}

	return dot;
}

/* These are all unused */

bool
CVisibilityPlugins::DefaultVisibilityCB(RpClump *clump)
{
	return true;
}

bool
CVisibilityPlugins::FrustumSphereCB(RpClump *clump)
{
	RwSphere sphere;
	RwFrame *frame = RpClumpGetFrame(clump);

	CClumpModelInfo *modelInfo = (CClumpModelInfo*)GetFrameHierarchyId(frame);
	sphere.radius = modelInfo->GetColModel()->boundingSphere.radius;
	sphere.center.x = modelInfo->GetColModel()->boundingSphere.center.x;
	sphere.center.y = modelInfo->GetColModel()->boundingSphere.center.y;
	sphere.center.z = modelInfo->GetColModel()->boundingSphere.center.z;
	RwV3dTransformPoints(&sphere.center, &sphere.center, 1, RwFrameGetLTM(frame));
	return RwCameraFrustumTestSphere(ms_pCamera, &sphere) != rwSPHEREOUTSIDE;
}

bool
CVisibilityPlugins::VehicleVisibilityCB(RpClump *clump)
{
	if (GetDistanceSquaredFromCamera(RpClumpGetFrame(clump)) <= ms_vehicleLod1Dist)
		return FrustumSphereCB(clump);
	return false;
}

bool
CVisibilityPlugins::VehicleVisibilityCB_BigVehicle(RpClump *clump)
{
	return FrustumSphereCB(clump);
}




//
// RW Plugins
//

enum
{
	ID_VISIBILITYATOMIC = MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x00),
	ID_VISIBILITYCLUMP  = MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x01),
	ID_VISIBILITYFRAME  = MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x02),
};

bool
CVisibilityPlugins::PluginAttach(void)
{
	ms_atomicPluginOffset = RpAtomicRegisterPlugin(sizeof(AtomicExt),
		ID_VISIBILITYATOMIC,
		AtomicConstructor, AtomicDestructor, AtomicCopyConstructor);

	ms_framePluginOffset = RwFrameRegisterPlugin(sizeof(FrameExt),
		ID_VISIBILITYFRAME,
		FrameConstructor, FrameDestructor, FrameCopyConstructor);

	ms_clumpPluginOffset = RpClumpRegisterPlugin(sizeof(ClumpExt),
		ID_VISIBILITYCLUMP,
		ClumpConstructor, ClumpDestructor, ClumpCopyConstructor);
	return ms_atomicPluginOffset != -1 && ms_clumpPluginOffset != -1;
}

#define ATOMICEXT(o) (RWPLUGINOFFSET(AtomicExt, o, ms_atomicPluginOffset))
#define FRAMEEXT(o) (RWPLUGINOFFSET(FrameExt, o, ms_framePluginOffset))
#define CLUMPEXT(o) (RWPLUGINOFFSET(ClumpExt, o, ms_clumpPluginOffset))

//
// Atomic
//

void*
CVisibilityPlugins::AtomicConstructor(void *object, int32, int32)
{
	ATOMICEXT(object)->modelInfo = nil;
	return object;
}

void*
CVisibilityPlugins::AtomicDestructor(void *object, int32, int32)
{
	return object;
}

void*
CVisibilityPlugins::AtomicCopyConstructor(void *dst, const void *src, int32, int32)
{
	*ATOMICEXT(dst) = *ATOMICEXT(src);
	return dst;
}

void
CVisibilityPlugins::SetAtomicModelInfo(RpAtomic *atomic,
                                       CSimpleModelInfo *modelInfo)
{
	AtomicExt *ext = ATOMICEXT(atomic);
	ext->modelInfo = modelInfo;
}

CSimpleModelInfo*
CVisibilityPlugins::GetAtomicModelInfo(RpAtomic *atomic)
{
	return ATOMICEXT(atomic)->modelInfo;
}

void
CVisibilityPlugins::SetAtomicFlag(RpAtomic *atomic, int f)
{
	ATOMICEXT(atomic)->flags |= f;
}

void
CVisibilityPlugins::ClearAtomicFlag(RpAtomic *atomic, int f)
{
	ATOMICEXT(atomic)->flags &= ~f;
}

int
CVisibilityPlugins::GetAtomicId(RpAtomic *atomic)
{
	return ATOMICEXT(atomic)->flags;
}

// This is rather useless, but whatever
void
CVisibilityPlugins::SetAtomicRenderCallback(RpAtomic *atomic, RpAtomicCallBackRender cb)
{
	if(cb == nil)
		cb = AtomicDefaultRenderCallBack;	// not necessary
	RpAtomicSetRenderCallBack(atomic, cb);
}

//
// Frame
//

void*
CVisibilityPlugins::FrameConstructor(void *object, int32, int32)
{
	FRAMEEXT(object)->id = 0;
	return object;
}

void*
CVisibilityPlugins::FrameDestructor(void *object, int32, int32)
{
	return object;
}

void*
CVisibilityPlugins::FrameCopyConstructor(void *dst, const void *src, int32, int32)
{
	*FRAMEEXT(dst) = *FRAMEEXT(src);
	return dst;
}

void
CVisibilityPlugins::SetFrameHierarchyId(RwFrame *frame, uintptr id)
{
	FRAMEEXT(frame)->id = id;
}

uintptr
CVisibilityPlugins::GetFrameHierarchyId(RwFrame *frame)
{
	return FRAMEEXT(frame)->id;
}


//
// Clump
//

void*
CVisibilityPlugins::ClumpConstructor(void *object, int32, int32)
{
	ClumpExt *ext = CLUMPEXT(object);
	ext->visibilityCB = DefaultVisibilityCB;
	ext->alpha = 0xFF;
	return object;
}

void*
CVisibilityPlugins::ClumpDestructor(void *object, int32, int32)
{
	return object;
}

void*
CVisibilityPlugins::ClumpCopyConstructor(void *dst, const void *src, int32, int32)
{
	CLUMPEXT(dst)->visibilityCB = CLUMPEXT(src)->visibilityCB;
	return dst;
}

void
CVisibilityPlugins::SetClumpModelInfo(RpClump *clump, CClumpModelInfo *modelInfo)
{
	CVehicleModelInfo *vmi;
	SetFrameHierarchyId(RpClumpGetFrame(clump), (uintptr)modelInfo);

	// Unused
	switch (modelInfo->GetModelType()) {
	// ignore MLO
	case MITYPE_VEHICLE:
		vmi = (CVehicleModelInfo*)modelInfo;
		if(vmi->m_vehicleType == VEHICLE_TYPE_TRAIN ||
		   vmi->m_vehicleType == VEHICLE_TYPE_HELI ||
		   vmi->m_vehicleType == VEHICLE_TYPE_PLANE)
			CLUMPEXT(clump)->visibilityCB = VehicleVisibilityCB_BigVehicle;
		else
			CLUMPEXT(clump)->visibilityCB = VehicleVisibilityCB;
		break;
	default: break;
	}
}

void
CVisibilityPlugins::SetClumpAlpha(RpClump *clump, int alpha)
{
	CLUMPEXT(clump)->alpha = alpha;
}

int
CVisibilityPlugins::GetClumpAlpha(RpClump *clump)
{
	return CLUMPEXT(clump)->alpha;
}
