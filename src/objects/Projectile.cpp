#include "common.h"
#include "patcher.h"
#include "Projectile.h"

class CProjectile_ : public CProjectile
{
public:
	void dtor(void) { CProjectile::~CProjectile(); }
};

STARTPATCHES
	InjectHook(0x4BFED0, &CProjectile_::dtor, PATCH_JUMP);
ENDPATCHES
