#include "common.h"
#include "patcher.h"
#include "Replay.h"

uint8 &CReplay::Mode = *(uint8*)0x95CD5B;

WRAPPER void CReplay::Display(void) { EAXJMP(0x595EE0); }
