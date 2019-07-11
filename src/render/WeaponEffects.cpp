#include "common.h"
#include "patcher.h"
#include "WeaponEffects.h"

WRAPPER void CWeaponEffects::Render(void) { EAXJMP(0x564D70); }

CWeaponEffects &gCrossHair = *(CWeaponEffects*)0x6503BC;

void CWeaponEffects::ClearCrosshair()
{
	gCrossHair.m_bCrosshair = false;
}
