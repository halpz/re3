#include "common.h"
#include "patcher.h"
#include "RoadBlocks.h"

WRAPPER void CRoadBlocks::GenerateRoadBlockCopsForCar(CVehicle*, int32, int16) { EAXJMP(0x4376A0); }
