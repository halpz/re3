#include "common.h"
#include "patcher.h"
#include "Replay.h"

uint8 &CReplay::Mode = *(uint8*)0x95CD5B;
Bool &CReplay::bPlayingBackFromFile = *(Bool*)0x95CD58;

WRAPPER void CReplay::Display(void) { EAXJMP(0x595EE0); }
