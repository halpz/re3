#include "common.h"
#include "patcher.h"
#include "ProjectileInfo.h"
#include "Projectile.h"

WRAPPER void CProjectileInfo::RemoveAllProjectiles(void) { EAXJMP(0x55BB80); }
WRAPPER bool CProjectileInfo::RemoveIfThisIsAProjectile(CObject *pObject) { EAXJMP(0x55BBD0); }