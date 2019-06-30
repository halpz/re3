#include "common.h"
#include "patcher.h"
#include "TrafficLights.h"

WRAPPER void CTrafficLights::DisplayActualLight(CEntity *ent) { EAXJMP(0x455800); }
