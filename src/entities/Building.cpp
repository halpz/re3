#include "common.h"
#include "rpworld.h"
#include "Building.h"
#include "Pools.h"

void *CBuilding::operator new(size_t sz) { return CPools::GetBuildingPool()->New();  }
void CBuilding::operator delete(void *p, size_t sz) { CPools::GetBuildingPool()->Delete((CBuilding*)p); }
