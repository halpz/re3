#include "common.h"
#include "patcher.h"
#include "Object.h"
#include "Pools.h"

void *CObject::operator new(size_t sz) { return CPools::GetObjectPool()->New();  }
void CObject::operator delete(void *p, size_t sz) { CPools::GetObjectPool()->Delete((CObject*)p); }

WRAPPER void CObject::ObjectDamage(float amount) { EAXJMP(0x4BB240); }
