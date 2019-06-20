#include "common.h"
#include "patcher.h"
#include "Weapon.h"

WRAPPER bool CWeapon::Fire(CEntity*, CVector*) { EAXJMP(0x55C380); }
WRAPPER void CWeapon::AddGunshell(CEntity*, CVector const&, CVector2D const&, float) { EAXJMP(0x55F770); }