#include "common.h"
#include "patcher.h"
#include "Heli.h"

WRAPPER void CHeli::SpecialHeliPreRender(void) { EAXJMP(0x54AE10); }
