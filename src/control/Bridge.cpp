#include "common.h"
#include "patcher.h"
#include "Bridge.h"

WRAPPER  bool CBridge::ShouldLightsBeFlashing(void) { EAXJMP(0x413D10); }
