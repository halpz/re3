#include "common.h"
#include "patcher.h"
#include "Vehicle.h"
#include "Pools.h"

void *CVehicle::operator new(size_t sz) { return CPools::GetVehiclePool()->New();  }
void CVehicle::operator delete(void *p, size_t sz) { CPools::GetVehiclePool()->Delete((CVehicle*)p); }
