#include "common.h"
#include "patcher.h"
#include "Automobile.h"

WRAPPER void CAutomobile::SetDoorDamage(int32, uint32, bool) { EAXJMP(0x530200); }