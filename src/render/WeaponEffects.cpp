#include "common.h"
#include "patcher.h"
#include "WeaponEffects.h"

WRAPPER void CWeaponEffects::Render(void) { EAXJMP(0x564D70); }
