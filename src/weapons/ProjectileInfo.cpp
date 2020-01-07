#include "common.h"
#include "patcher.h"
#include "ProjectileInfo.h"
#include "Projectile.h"

CProjectileInfo* gaProjectileInfo = (CProjectileInfo*)0x64ED50;
CProjectile* (&CProjectileInfo::ms_apProjectile)[32] = *(CProjectile*(*)[32])*(uintptr*)0x87C748;

WRAPPER void CProjectileInfo::RemoveAllProjectiles(void) { EAXJMP(0x55BB80); }
WRAPPER bool CProjectileInfo::RemoveIfThisIsAProjectile(CObject *pObject) { EAXJMP(0x55BBD0); }
WRAPPER bool CProjectileInfo::IsProjectileInRange(float x1, float x2, float y1, float y2, float z1, float z2, bool remove) { EAXJMP(0x55BA50); }

CProjectileInfo*
CProjectileInfo::GetProjectileInfo(int32 id)
{
	return &gaProjectileInfo[id];
}
