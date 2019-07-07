#include "common.h"
#include "patcher.h"
#include "Projectile.h"

STARTPATCHES
	InjectHook(0x4BFED0, &CProjectile::dtor, PATCH_JUMP);
ENDPATCHES