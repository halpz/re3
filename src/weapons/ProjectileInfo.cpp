#include "common.h"
#include "patcher.h"
#include "ProjectileInfo.h"
#include "Projectile.h"


WRAPPER bool CProjectileInfo::RemoveIfThisIsAProjectile(CObject *pObject) { EAXJMP(0x55BBD0); }