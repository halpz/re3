#pragma once

#include "2dEffect.h"
#include "SimpleModelInfo.h"
#include "MloModelInfo.h"
#include "TimeModelInfo.h"
#include "WeaponModelInfo.h"
#include "ClumpModelInfo.h"
#include "PedModelInfo.h"
#include "VehicleModelInfo.h"
#include "XtraCompsModelInfo.h"
#include "templates.h"

extern C2dEffect *gp2dEffects;

class CModelInfo
{
	static CBaseModelInfo **ms_modelInfoPtrs;
	static int32 msNumModelInfos;
	static CStore<CSimpleModelInfo, SIMPLEMODELSIZE> ms_simpleModelStore;
	static CStore<CTimeModelInfo, TIMEMODELSIZE> ms_timeModelStore;
	static CStore<CWeaponModelInfo, WEAPONMODELSIZE> ms_weaponModelStore;
	static CStore<CClumpModelInfo, CLUMPMODELSIZE> ms_clumpModelStore;
	static CStore<CPedModelInfo, PEDMODELSIZE> ms_pedModelStore;
	static CStore<CVehicleModelInfo, VEHICLEMODELSIZE> ms_vehicleModelStore;
	static CStore<C2dEffect, TWODFXSIZE> ms_2dEffectStore;

public:
	// these fields are in the resource image
	int32 resNumModelInfos;
	CBaseModelInfo **resModelInfoPtrs;

	static void Initialise(void);
	static void ShutDown(void);

	static CSimpleModelInfo *AddSimpleModel(int id);
	static CTimeModelInfo *AddTimeModel(int id);
	static CWeaponModelInfo *AddWeaponModel(int id);
	static CClumpModelInfo *AddClumpModel(int id);
	static CPedModelInfo *AddPedModel(int id);
	static CVehicleModelInfo *AddVehicleModel(int id);

	static CStore<C2dEffect, TWODFXSIZE> &Get2dEffectStore(void) { return ms_2dEffectStore; }
	static C2dEffect *Get2dEffect(int32 id) { return &gp2dEffects[id]; }
	static int32 Get2dEffectIndex(C2dEffect *effect) { return effect - gp2dEffects; }

	static int32 GetNumModelInfos(void) { return msNumModelInfos; }
	static CBaseModelInfo *GetModelInfo(const char *name, int *id);
	static CBaseModelInfo *GetModelInfo(int id){
		if(id < 0 || id >= msNumModelInfos)
			return nil;
		return ms_modelInfoPtrs[id];
	}
	static CBaseModelInfo *GetModelInfo(const char *name, int minIndex, int maxIndex);
	static CBaseModelInfo *GetModelInfoFromHashKey(uint32 hashKey, int *id);
	static CColModel *GetColModel(int id){
		return ms_modelInfoPtrs[id]->GetColModel();
	}

	static bool IsBoatModel(int32 id);
	static bool IsBikeModel(int32 id);
	static bool IsCarModel(int32 id);
	static bool IsTrainModel(int32 id);
	static bool IsHeliModel(int32 id);
	static bool IsPlaneModel(int32 id);
	static void ReInit2dEffects();

	static void Load(uint32 numModelInfos, CBaseModelInfo **modelInfos);
	static void Load2dEffects(uint32 numEffects, C2dEffect *effects);
	CModelInfo *Write(base::cRelocatableChunkWriter &writer);
};
