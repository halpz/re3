#pragma once

#include "2dEffect.h"
#include "BaseModelInfo.h"
#include "SimpleModelInfo.h"
#include "TimeModelInfo.h"
#include "ClumpModelInfo.h"
#include "PedModelInfo.h"
#include "VehicleModelInfo.h"
#include "Instance.h"

class CModelInfo
{
	static CBaseModelInfo *ms_modelInfoPtrs[MODELINFOSIZE];
	static CStore<CSimpleModelInfo, SIMPLEMODELSIZE> ms_simpleModelStore;
	static CStore<CTimeModelInfo, TIMEMODELSIZE> ms_timeModelStore;
	static CStore<CClumpModelInfo, CLUMPMODELSIZE> ms_clumpModelStore;
	static CStore<CPedModelInfo, PEDMODELSIZE> ms_pedModelStore;
	static CStore<CVehicleModelInfo, VEHICLEMODELSIZE> ms_vehicleModelStore;
	static CStore<C2dEffect, TWODFXSIZE> ms_2dEffectStore;

public:
	static void Initialise(void);
	static void ShutDown(void);

	static CSimpleModelInfo *AddSimpleModel(int id);
	static CTimeModelInfo *AddTimeModel(int id);
	static CClumpModelInfo *AddClumpModel(int id);
	static CPedModelInfo *AddPedModel(int id);
	static CVehicleModelInfo *AddVehicleModel(int id);

	static CStore<C2dEffect, TWODFXSIZE> &Get2dEffectStore(void) { return ms_2dEffectStore; }

	static CBaseModelInfo *GetModelInfo(const char *name, int *id);
	static CBaseModelInfo *GetModelInfo(int id){
		return ms_modelInfoPtrs[id];
	}
	static CBaseModelInfo *GetModelInfo(const char *name, int minIndex, int maxIndex);

	static bool IsBoatModel(int32 id);
	static bool IsBikeModel(int32 id);
	static bool IsCarModel(int32 id);
	static void ReInit2dEffects();
};
