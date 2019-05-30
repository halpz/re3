#include "common.h"
#include "patcher.h"
#include "Replay.h"

WRAPPER void CReplay::Display(void) { EAXJMP(0x595EE0); }