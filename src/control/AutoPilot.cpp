#include "common.h"
#include "patcher.h"
#include "AutoPilot.h"

WRAPPER void CAutoPilot::RemoveOnePathNode() { EAXJMP(0x413A00); }
WRAPPER void CAutoPilot::ModifySpeed(float) { EAXJMP(0x4137B0); }
