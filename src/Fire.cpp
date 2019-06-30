#include "common.h"
#include "patcher.h"
#include "Fire.h"

WRAPPER void CFire::Extinguish(void) { EAXJMP(0x479D40); }