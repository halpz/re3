#include "common.h"
#include "patcher.h"
#include "PointLights.h"

WRAPPER void CPointLights::RenderFogEffect(void) { EAXJMP(0x510C30); }
