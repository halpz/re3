#include "common.h"
#include "patcher.h"
#include "ParticleObject.h"

void CParticleObject::AddObject(uint16, const CVector &pos, bool remove) { EAXJMP(0x4BC4D0); }
