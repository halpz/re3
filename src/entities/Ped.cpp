#include "common.h"
#include "patcher.h"
#include "Ped.h"
#include "Pools.h"

//void *CPed::operator new(size_t sz) { return CPools::GetPedPool()->New();  }
//void CPed::operator delete(void *p, size_t sz) { CPools::GetPedPool()->Delete((CPed*)p); }

WRAPPER void CPed::KillPedWithCar(CVehicle *veh, float impulse) { EAXJMP(0x4EC430); }
