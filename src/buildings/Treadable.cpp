#include "common.h"

#include "rpworld.h"
#include "Treadable.h"
#include "Pools.h"

void *CTreadable::operator new(size_t sz) throw() { return CPools::GetTreadablePool()->New();  }
void CTreadable::operator delete(void *p, size_t sz) throw() { CPools::GetTreadablePool()->Delete((CTreadable*)p); }
