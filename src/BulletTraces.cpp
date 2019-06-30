#include "common.h"
#include "patcher.h"
#include "BulletTraces.h"

CBulletTrace (&CBulletTraces::aTraces)[16] = *(CBulletTrace(*)[16])*(uintptr*)0x72B1B8;

WRAPPER void CBulletTraces::Init(void) { EAXJMP(0x518DE0); }
