#include "common.h"

#include "General.h"
#include "TempColModels.h"
#include "ModelIndices.h"
#include "ModelInfo.h"

CBaseModelInfo *CModelInfo::ms_modelInfoPtrs[MODELINFOSIZE];

CStore<CSimpleModelInfo, SIMPLEMODELSIZE> CModelInfo::ms_simpleModelStore;
CStore<CTimeModelInfo, TIMEMODELSIZE> CModelInfo::ms_timeModelStore;
CStore<CClumpModelInfo, CLUMPMODELSIZE> CModelInfo::ms_clumpModelStore;
CStore<CPedModelInfo, PEDMODELSIZE> CModelInfo::ms_pedModelStore;
CStore<CVehicleModelInfo, VEHICLEMODELSIZE> CModelInfo::ms_vehicleModelStore;
CStore<C2dEffect, TWODFXSIZE> CModelInfo::ms_2dEffectStore;

void
CModelInfo::Initialise(void)
{
	int i;
	CSimpleModelInfo *m;

	for(i = 0; i < MODELINFOSIZE; i++)
		ms_modelInfoPtrs[i] = nil;
	ms_2dEffectStore.clear();
	ms_simpleModelStore.clear();
	ms_timeModelStore.clear();
	ms_clumpModelStore.clear();
	ms_pedModelStore.clear();
	ms_vehicleModelStore.clear();

	m = AddSimpleModel(MI_CAR_DOOR);
	m->SetColModel(&CTempColModels::ms_colModelDoor1);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;

	m = AddSimpleModel(MI_CAR_BUMPER);
	m->SetColModel(&CTempColModels::ms_colModelBumper1);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;

	m = AddSimpleModel(MI_CAR_PANEL);
	m->SetColModel(&CTempColModels::ms_colModelPanel1);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;

	m = AddSimpleModel(MI_CAR_BONNET);
	m->SetColModel(&CTempColModels::ms_colModelBonnet1);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;

	m = AddSimpleModel(MI_CAR_BOOT);
	m->SetColModel(&CTempColModels::ms_colModelBoot1);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;

	m = AddSimpleModel(MI_CAR_WHEEL);
	m->SetColModel(&CTempColModels::ms_colModelWheel1);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;

	m = AddSimpleModel(MI_BODYPARTA);
	m->SetColModel(&CTempColModels::ms_colModelBodyPart1);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;

	m = AddSimpleModel(MI_BODYPARTB);
	m->SetColModel(&CTempColModels::ms_colModelBodyPart2);
	m->SetTexDictionary("generic");
	m->SetNumAtomics(1);
	m->m_lodDistances[0] = 80.0f;
}

void
CModelInfo::ShutDown(void)
{
	int i;
	for(i = 0; i < ms_simpleModelStore.allocPtr; i++)
		ms_simpleModelStore.store[i].Shutdown();
	for(i = 0; i < ms_timeModelStore.allocPtr; i++)
		ms_timeModelStore.store[i].Shutdown();
	for(i = 0; i < ms_clumpModelStore.allocPtr; i++)
		ms_clumpModelStore.store[i].Shutdown();
	for(i = 0; i < ms_vehicleModelStore.allocPtr; i++)
		ms_vehicleModelStore.store[i].Shutdown();
	for(i = 0; i < ms_pedModelStore.allocPtr; i++)
		ms_pedModelStore.store[i].Shutdown();
	for(i = 0; i < ms_2dEffectStore.allocPtr; i++)
		ms_2dEffectStore.store[i].Shutdown();

	ms_2dEffectStore.clear();
	ms_simpleModelStore.clear();
	ms_timeModelStore.clear();
	ms_pedModelStore.clear();
	ms_clumpModelStore.clear();
	ms_vehicleModelStore.clear();
}

CSimpleModelInfo*
CModelInfo::AddSimpleModel(int id)
{
	CSimpleModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_simpleModelStore.alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->Init();
	return modelinfo;
}

CTimeModelInfo*
CModelInfo::AddTimeModel(int id)
{
	CTimeModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_timeModelStore.alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->Init();
	return modelinfo;
}

CClumpModelInfo*
CModelInfo::AddClumpModel(int id)
{
	CClumpModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_clumpModelStore.alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->m_clump = nil;
	return modelinfo;
}

CPedModelInfo*
CModelInfo::AddPedModel(int id)
{
	CPedModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_pedModelStore.alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->m_clump = nil;
	return modelinfo;
}

CVehicleModelInfo*
CModelInfo::AddVehicleModel(int id)
{
	CVehicleModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_vehicleModelStore.alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->m_clump = nil;
	modelinfo->m_vehicleType = -1;
	modelinfo->m_wheelId = -1;
	modelinfo->m_materials1[0] = nil;
	modelinfo->m_materials2[0] = nil;
	modelinfo->m_bikeSteerAngle = 999.99f;
	return modelinfo;
}

CBaseModelInfo*
CModelInfo::GetModelInfo(const char *name, int *id)
{
	CBaseModelInfo *modelinfo;
	for(int i = 0; i < MODELINFOSIZE; i++){
		modelinfo = CModelInfo::ms_modelInfoPtrs[i];
	 	if(modelinfo && !CGeneral::faststricmp(modelinfo->GetName(), name)){
			if(id)
				*id = i;
			return modelinfo;
		}
	}
	return nil;
}

CBaseModelInfo*
CModelInfo::GetModelInfo(const char *name, int minIndex, int maxIndex)
{
	CBaseModelInfo *modelinfo;
	for(int i = minIndex; i <= maxIndex; i++){
		modelinfo = CModelInfo::ms_modelInfoPtrs[i];
	 	if(modelinfo && !CGeneral::faststricmp(modelinfo->GetName(), name))
			return modelinfo;
	}
	return nil;
}

bool
CModelInfo::IsBoatModel(int32 id)
{
	return GetModelInfo(id)->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)GetModelInfo(id))->m_vehicleType == VEHICLE_TYPE_BOAT;
}

bool
CModelInfo::IsBikeModel(int32 id)
{
	return GetModelInfo(id)->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)GetModelInfo(id))->m_vehicleType == VEHICLE_TYPE_BIKE;
}

bool
CModelInfo::IsCarModel(int32 id)
{
	return GetModelInfo(id)->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)GetModelInfo(id))->m_vehicleType == VEHICLE_TYPE_CAR;
}

void
CModelInfo::ReInit2dEffects()
{
	ms_2dEffectStore.clear();

	for (int i = 0; i < MODELINFOSIZE; i++) {
		if (ms_modelInfoPtrs[i])
			ms_modelInfoPtrs[i]->Init2dEffects();
	}
}
