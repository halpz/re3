#include "common.h"
#include "patcher.h"
#include "DMAudio.h"

cDMAudio &DMAudio = *(cDMAudio*)0x95CDBE;

WRAPPER void cDMAudio::Service(void) { EAXJMP(0x57C7A0); }
WRAPPER void cDMAudio::ReportCollision(CEntity *A, CEntity *B, uint8 surfA, uint8 surfB, float impulse, float speed) { EAXJMP(0x57CBE0); }
WRAPPER void cDMAudio::ResetTimers(UInt32 timerval) { EAXJMP(0x57CCD0); }
