#include "common.h"
#include "patcher.h"
#include "Dummy.h"
#include "Pools.h"

void *CDummy::operator new(size_t sz) { return CPools::GetDummyPool()->New();  }
void CDummy::operator delete(void *p, size_t sz) { CPools::GetDummyPool()->Delete((CDummy*)p); }
