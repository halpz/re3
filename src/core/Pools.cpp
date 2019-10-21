#include "common.h"
#include "patcher.h"
#include "Pools.h"
#include "World.h"
#include "ProjectileInfo.h"

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

void
CPools::ShutDown(void)
{
	debug("PtrNodes left %d\n", ms_pPtrNodePool->GetNoOfUsedSpaces());
	debug("EntryInfoNodes left %d\n", ms_pEntryInfoNodePool->GetNoOfUsedSpaces());
	debug("Peds left %d\n", ms_pPedPool->GetNoOfUsedSpaces());
	debug("Vehicles left %d\n", ms_pVehiclePool->GetNoOfUsedSpaces());
	debug("Buildings left %d\n", ms_pBuildingPool->GetNoOfUsedSpaces());
	debug("Treadables left %d\n", ms_pTreadablePool->GetNoOfUsedSpaces());
	debug("Objects left %d\n", ms_pObjectPool->GetNoOfUsedSpaces());
	debug("Dummys left %d\n", ms_pDummyPool->GetNoOfUsedSpaces());
	debug("AudioScriptObjects left %d\n", ms_pAudioScriptObjectPool->GetNoOfUsedSpaces());
	printf("Shutdown pool started\n");

	delete ms_pPtrNodePool;
	delete ms_pEntryInfoNodePool;
	delete ms_pPedPool;
	delete ms_pVehiclePool;
	delete ms_pBuildingPool;
	delete ms_pTreadablePool;
	delete ms_pObjectPool;
	delete ms_pDummyPool;
	delete ms_pAudioScriptObjectPool;

	printf("Shutdown pool done\n");
}

int32 CPools::GetPedRef(CPed *ped) { return ms_pPedPool->GetIndex(ped); }
CPed *CPools::GetPed(int32 handle) { return ms_pPedPool->GetAt(handle); }
int32 CPools::GetVehicleRef(CVehicle *vehicle) { return ms_pVehiclePool->GetIndex(vehicle); }
CVehicle *CPools::GetVehicle(int32 handle) { return ms_pVehiclePool->GetAt(handle); }
int32 CPools::GetObjectRef(CObject *object) { return ms_pObjectPool->GetIndex(object); }
CObject *CPools::GetObject(int32 handle) { return ms_pObjectPool->GetAt(handle); }

void
CPools::CheckPoolsEmpty()
{
	assert(ms_pPedPool->GetNoOfUsedSpaces() == 0);
	assert(ms_pVehiclePool->GetNoOfUsedSpaces() == 0);
	printf("pools have beem cleared \n");
}


void
CPools::MakeSureSlotInObjectPoolIsEmpty(int32 slot)
{
	if (ms_pObjectPool->IsFreeSlot(slot)) return;

	CObject *object = ms_pObjectPool->GetSlot(slot);
	if (object->ObjectCreatedBy == TEMP_OBJECT) {
		CWorld::Remove(object);
		delete object;
	} else if (!CProjectileInfo::RemoveIfThisIsAProjectile(object)) {
		// relocate to another slot??
		CObject *newObject = new CObject();
		CWorld::Remove(object);
		memcpy(newObject, object, ms_pObjectPool->GetMaxEntrySize());
		CWorld::Add(newObject);
		object->m_rwObject = nil;
		delete object;
		newObject->m_pFirstReference = nil;
	}
}


STARTPATCHES
	InjectHook(0x4A1770, CPools::Initialise, PATCH_JUMP);
	InjectHook(0x4A1880, CPools::ShutDown, PATCH_JUMP);
	InjectHook(0x4A1A50, CPools::CheckPoolsEmpty, PATCH_JUMP);
	InjectHook(0x4A1A80, CPools::GetPedRef, PATCH_JUMP);
	InjectHook(0x4A1AA0, CPools::GetPed, PATCH_JUMP);
	InjectHook(0x4A1AC0, CPools::GetVehicleRef, PATCH_JUMP);
	InjectHook(0x4A1AE0, CPools::GetVehicle, PATCH_JUMP);
	InjectHook(0x4A1B00, CPools::GetObjectRef, PATCH_JUMP);
	InjectHook(0x4A1B20, CPools::GetObject, PATCH_JUMP);
	InjectHook(0x4A2DB0, CPools::MakeSureSlotInObjectPoolIsEmpty, PATCH_JUMP);
ENDPATCHES
