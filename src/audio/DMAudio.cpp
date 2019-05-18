#include "common.h"
#include "patcher.h"
#include "DMAudio.h"

WRAPPER void cDMAudio::ReportCollision(CEntity *A, CEntity *B, uint8 surfA, uint8 surfB, float impulse, float speed) { EAXJMP(0x161684); }
