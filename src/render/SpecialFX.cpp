#include "common.h"
#include "patcher.h"
#include "SpecialFX.h"

WRAPPER void CSpecialFX::Render(void) { EAXJMP(0x518DC0); }

WRAPPER void CMotionBlurStreaks::RegisterStreak(int32 id, uint8 r, uint8 g, uint8 b, CVector p1, CVector p2) { EAXJMP(0x519460); }


CBulletTrace (&CBulletTraces::aTraces)[16] = *(CBulletTrace(*)[16])*(uintptr*)0x72B1B8;

WRAPPER void CBulletTraces::Init(void) { EAXJMP(0x518DE0); }


WRAPPER void C3dMarkers::PlaceMarkerSet(uint32 id, uint16 type, CVector& pos, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate)  { EAXJMP(0x51BB80); }