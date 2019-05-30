#include "common.h"
#include "patcher.h"
#include "Fluff.h"

WRAPPER void CMovingThings::Render(void) { EAXJMP(0x4FF210); }
