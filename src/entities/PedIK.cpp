#include "common.h"
#include "patcher.h"
#include "Ped.h"

WRAPPER void CPedIK::GetComponentPosition(RwV3d* pos, int id) { EAXJMP(0x4ED0F0); }
WRAPPER bool CPedIK::PointGunInDirection(float phi, float theta) { EAXJMP(0x4ED9B0); }
WRAPPER bool CPedIK::PointGunAtPosition(CVector* position) { EAXJMP(0x4ED920); }