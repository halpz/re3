#include "common.h"
#include "patcher.h"
#include "Vehicle.h"
#include "Pools.h"

Bool &CVehicle::bWheelsOnlyCheat = *(Bool *)0x95CD78;
Bool &CVehicle::bAllDodosCheat = *(Bool *)0x95CD75;
Bool &CVehicle::bCheat3 = *(Bool *)0x95CD66;
Bool &CVehicle::bCheat4 = *(Bool *)0x95CD65;
Bool &CVehicle::bCheat5 = *(Bool *)0x95CD64;
	
void *CVehicle::operator new(size_t sz) { return CPools::GetVehiclePool()->New();  }
void CVehicle::operator delete(void *p, size_t sz) { CPools::GetVehiclePool()->Delete((CVehicle*)p); }
