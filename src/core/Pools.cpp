#include "common.h"
#include "Pools.h"

CCPtrNodePool *&CPools::ms_pPtrNodePool = *(CCPtrNodePool**)0x943044;
CEntryInfoNodePool *&CPools::ms_pEntryInfoNodePool = *(CEntryInfoNodePool**)0x941448;
CPedPool *&CPools::ms_pPedPool = *(CPedPool**)0x8F2C60;
CVehiclePool *&CPools::ms_pVehiclePool = *(CVehiclePool**)0x9430DC;
CBuildingPool *&CPools::ms_pBuildingPool = *(CBuildingPool**)0x8F2C04;
CTreadablePool *&CPools::ms_pTreadablePool = *(CTreadablePool**)0x8F2568;
CObjectPool *&CPools::ms_pObjectPool = *(CObjectPool**)0x880E28;
CDummyPool *&CPools::ms_pDummyPool = *(CDummyPool**)0x8F2C18;
CAudioScriptObjectPool *&CPools::ms_pAudioScriptObjectPool = *(CAudioScriptObjectPool**)0x8F1B6C;

void
CPools::Initialise(void)
{
	// TODO: unused right now
	assert(0);
	ms_pPtrNodePool = new CCPtrNodePool(NUMPTRNODES);
	ms_pEntryInfoNodePool = new CEntryInfoNodePool(NUMENTRYINFOS);
	ms_pPedPool = new CPedPool(NUMPEDS);
	ms_pVehiclePool = new CVehiclePool(NUMVEHICLES);
	ms_pBuildingPool = new CBuildingPool(NUMBUILDINGS);
	ms_pTreadablePool = new CTreadablePool(NUMTREADABLES);
	ms_pObjectPool = new CObjectPool(NUMOBJECTS);
	ms_pDummyPool = new CDummyPool(NUMDUMMIES);
	ms_pAudioScriptObjectPool = new CAudioScriptObjectPool(NUMAUDIOSCRIPTOBJECTS);
}

int32 CPools::GetPedRef(CPed *ped) { return ms_pPedPool->GetIndex(ped); }
CPed *CPools::GetPed(int32 handle) { return ms_pPedPool->GetAt(handle); }
int32 CPools::GetVehicleRef(CVehicle *vehicle) { return ms_pVehiclePool->GetIndex(vehicle); }
CVehicle *CPools::GetVehicle(int32 handle) { return ms_pVehiclePool->GetAt(handle); }
int32 CPools::GetObjectRef(CObject *object) { return ms_pObjectPool->GetIndex(object); }
CObject *CPools::GetObject(int32 handle) { return ms_pObjectPool->GetAt(handle); }
