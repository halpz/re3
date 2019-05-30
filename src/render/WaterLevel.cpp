#include "common.h"
#include "patcher.h"
#include "WaterLevel.h"

WRAPPER void CWaterLevel::RenderWater(void) { EAXJMP(0x5554E0); }
