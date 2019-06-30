#include "common.h"
#include "patcher.h"
#include "SpecialFX.h"

WRAPPER void CSpecialFX::Render(void) { EAXJMP(0x518DC0); }

WRAPPER void CMotionBlurStreaks::RegisterStreak(int32 id, uint8 r, uint8 g, uint8 b, CVector p1, CVector p2) { EAXJMP(0x519460); }
