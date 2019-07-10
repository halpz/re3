#include "common.h"
#include "patcher.h"
#include "Explosion.h"

WRAPPER void CExplosion::AddExplosion(CEntity *explodingEntity, CEntity *culprit, eExplosionType type, const CVector &pos, uint32) { EAXJMP(0x5591C0); }
