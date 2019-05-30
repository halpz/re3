#include "common.h"
#include "patcher.h"
#include "SpecialFX.h"

WRAPPER void CSpecialFX::Render(void) { EAXJMP(0x518DC0); }
