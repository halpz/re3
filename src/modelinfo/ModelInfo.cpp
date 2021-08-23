#include "common.h"

#include "General.h"
#include "TempColModels.h"
#include "ModelIndices.h"
#include "ModelInfo.h"
#include "KeyGen.h"

CBaseModelInfo **CModelInfo::ms_modelInfoPtrs;
int32 CModelInfo::msNumModelInfos;

CStore<CSimpleModelInfo, SIMPLEMODELSIZE> CModelInfo::ms_simpleModelStore;
CStore<CTimeModelInfo, TIMEMODELSIZE> CModelInfo::ms_timeModelStore;
CStore<CWeaponModelInfo, WEAPONMODELSIZE> CModelInfo::ms_weaponModelStore;
CStore<CClumpModelInfo, CLUMPMODELSIZE> CModelInfo::ms_clumpModelStore;
CStore<CPedModelInfo, PEDMODELSIZE> CModelInfo::ms_pedModelStore;
CStore<CVehicleModelInfo, VEHICLEMODELSIZE> CModelInfo::ms_vehicleModelStore;
CStore<C2dEffect, TWODFXSIZE> CModelInfo::ms_2dEffectStore;

C2dEffect *gp2dEffects;

void
CModelInfo::Initialise(void)
{
	int i;
	CSimpleModelInfo *m;

	debug("sizeof SimpleModelStore %d\n", sizeof(ms_simpleModelStore));
	debug("sizeof TimeModelStore %d\n", sizeof(ms_timeModelStore));
	debug("sizeof WeaponModelStore %d\n", sizeof(ms_weaponModelStore));
	debug("sizeof ClumpModelStore %d\n", sizeof(ms_clumpModelStore));
	debug("sizeof VehicleModelStore %d\n", sizeof(ms_vehicleModelStore));
	debug("sizeof PedModelStore %d\n", sizeof(ms_pedModelStore));
	debug("sizeof 2deffectsModelStore %d\n", sizeof(ms_2dEffectStore));

	ms_modelInfoPtrs = new CBaseModelInfo*[MODELINFOSIZE];
	msNumModelInfos = MODELINFOSIZE;
	for(i = 0; i < MODELINFOSIZE; i++)
		ms_modelInfoPtrs[i] = nil;
	ms_2dEffectStore.Clear();
	gp2dEffects = ms_2dEffectStore.store;
	ms_simpleModelStore.Clear();
	ms_timeModelStore.Clear();
	ms_weaponModelStore.Clear();
	ms_clumpModelStore.Clear();
	ms_pedModelStore.Clear();
	ms_vehicleModelStore.Clear();

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
	for(i = 0; i < ms_weaponModelStore.allocPtr; i++)
		ms_weaponModelStore.store[i].Shutdown();
	for(i = 0; i < ms_clumpModelStore.allocPtr; i++)
		ms_clumpModelStore.store[i].Shutdown();
	for(i = 0; i < ms_vehicleModelStore.allocPtr; i++)
		ms_vehicleModelStore.store[i].Shutdown();
	for(i = 0; i < ms_pedModelStore.allocPtr; i++)
		ms_pedModelStore.store[i].Shutdown();
	for(i = 0; i < ms_2dEffectStore.allocPtr; i++)
		ms_2dEffectStore.store[i].Shutdown();

	ms_simpleModelStore.Clear();
	ms_timeModelStore.Clear();
	ms_weaponModelStore.Clear();
	ms_clumpModelStore.Clear();
	ms_vehicleModelStore.Clear();
	ms_pedModelStore.Clear();
	ms_2dEffectStore.Clear();
}

CSimpleModelInfo*
CModelInfo::AddSimpleModel(int id)
{
	CSimpleModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_simpleModelStore.Alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->Init();
	return modelinfo;
}

CTimeModelInfo*
CModelInfo::AddTimeModel(int id)
{
	CTimeModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_timeModelStore.Alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->Init();
	return modelinfo;
}

CWeaponModelInfo*
CModelInfo::AddWeaponModel(int id)
{
	CWeaponModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_weaponModelStore.Alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->Init();
	return modelinfo;
}

CClumpModelInfo*
CModelInfo::AddClumpModel(int id)
{
	CClumpModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_clumpModelStore.Alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->m_clump = nil;
	return modelinfo;
}

CPedModelInfo*
CModelInfo::AddPedModel(int id)
{
	CPedModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_pedModelStore.Alloc();
	CModelInfo::ms_modelInfoPtrs[id] = modelinfo;
	modelinfo->m_clump = nil;
	return modelinfo;
}

CVehicleModelInfo*
CModelInfo::AddVehicleModel(int id)
{
	CVehicleModelInfo *modelinfo;
	modelinfo = CModelInfo::ms_vehicleModelStore.Alloc();
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
	uint32 hashKey = CKeyGen::GetUppercaseKey(name);
	CBaseModelInfo *modelinfo;
	for(int i = 0; i < msNumModelInfos; i++){
		modelinfo = CModelInfo::ms_modelInfoPtrs[i];
	 	if(modelinfo && hashKey == modelinfo->GetNameHashKey()){
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
	uint32 hashKey = CKeyGen::GetUppercaseKey(name);
	if (minIndex > maxIndex)
		return 0;

	CBaseModelInfo *modelinfo;
	for(int i = minIndex; i <= maxIndex; i++){
		modelinfo = CModelInfo::ms_modelInfoPtrs[i];
	 	if(modelinfo && hashKey == modelinfo->GetNameHashKey())
			return modelinfo;
	}
	return nil;
}

CBaseModelInfo*
CModelInfo::GetModelInfoFromHashKey(uint32 hashKey, int *id)
{
	CBaseModelInfo *modelinfo;
	for(int i = 0; i < msNumModelInfos; i++){
		modelinfo = CModelInfo::ms_modelInfoPtrs[i];
	 	if(modelinfo && hashKey == modelinfo->GetNameHashKey()){
			if(id)
				*id = i;
			return modelinfo;
		}
	}
	return nil;
}

bool
CModelInfo::IsBoatModel(int32 id)
{
	CBaseModelInfo *mi = GetModelInfo(id);
	return mi && mi->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)mi)->m_vehicleType == VEHICLE_TYPE_BOAT;
}

bool
CModelInfo::IsBikeModel(int32 id)
{
	CBaseModelInfo *mi = GetModelInfo(id);
	return mi && mi->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)mi)->m_vehicleType == VEHICLE_TYPE_BIKE;
}

bool
CModelInfo::IsCarModel(int32 id)
{
	CBaseModelInfo *mi = GetModelInfo(id);
	return mi && mi->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)mi)->m_vehicleType == VEHICLE_TYPE_CAR;
}

bool
CModelInfo::IsTrainModel(int32 id)
{
	CBaseModelInfo *mi = GetModelInfo(id);
	return mi && mi->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)mi)->m_vehicleType == VEHICLE_TYPE_TRAIN;
}

bool
CModelInfo::IsHeliModel(int32 id)
{
	CBaseModelInfo *mi = GetModelInfo(id);
	return mi && mi->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)mi)->m_vehicleType == VEHICLE_TYPE_HELI;
}

bool
CModelInfo::IsPlaneModel(int32 id)
{
	CBaseModelInfo *mi = GetModelInfo(id);
	return mi && mi->GetModelType() == MITYPE_VEHICLE &&
		((CVehicleModelInfo*)mi)->m_vehicleType == VEHICLE_TYPE_PLANE;
}

void
CModelInfo::ReInit2dEffects()
{
	ms_2dEffectStore.Clear();

	for (int i = 0; i < msNumModelInfos; i++) {
		if (ms_modelInfoPtrs[i])
			ms_modelInfoPtrs[i]->Init2dEffects();
	}
}

void
CModelInfo::Load(uint32 numModelInfos, CBaseModelInfo **modelInfos)
{
	int i;

	msNumModelInfos = numModelInfos;
	ms_modelInfoPtrs = modelInfos;
	for(i = 0; i < msNumModelInfos; i++)
		if(ms_modelInfoPtrs[i] && ms_modelInfoPtrs[i]->GetModelType() == MITYPE_VEHICLE &&
		   ms_modelInfoPtrs[i]->GetRwObject())
			((CVehicleModelInfo*)ms_modelInfoPtrs[i])->SetAtomicRenderCallbacks();
}

void
CModelInfo::Load2dEffects(uint32 numEffects, C2dEffect *effects)
{
	ms_2dEffectStore.allocPtr = numEffects;
	gp2dEffects = effects;
}

CModelInfo*
CModelInfo::Write(base::cRelocatableChunkWriter &writer)
{
	uint32 i;
	uint32 numModelInfos;

	for(numModelInfos = msNumModelInfos; ms_modelInfoPtrs[numModelInfos-1] == nil; numModelInfos--);
	writer.AllocateRaw(ms_modelInfoPtrs, sizeof(void*)*numModelInfos, sizeof(void*), false, true);
	for(i = 0; i < numModelInfos; i++)
		if(ms_modelInfoPtrs[i]){
			writer.AddPatch(ms_modelInfoPtrs[i]);
			ms_modelInfoPtrs[i]->Write(writer);
		}

	resNumModelInfos = numModelInfos;
	resModelInfoPtrs = ms_modelInfoPtrs;

	return this;
}
