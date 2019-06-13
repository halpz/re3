#include "common.h"
#include "patcher.h"
#include "Radar.h"

WRAPPER void CRadar::ClearBlipForEntity(eBlipType type, int32 id) { EAXJMP(0x4A56C0); }
