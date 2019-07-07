#include "common.h"
#include "patcher.h"
#include "PlayerPed.h"
#include "Camera.h"
#include "WeaponEffects.h"

CPlayerPed::~CPlayerPed()
{
	delete m_pWanted;
}

WRAPPER void CPlayerPed::ReApplyMoveAnims(void) { EAXJMP(0x4F07C0); }

void CPlayerPed::ClearWeaponTarget()
{
	if (!m_nPedType) {
		m_pPointGunAt = 0;
		TheCamera.ClearPlayerWeaponMode();
		CWeaponEffects::ClearCrosshair();
	}
	ClearPointGunAt();
}

STARTPATCHES
InjectHook(0x4EFB30, &CPlayerPed::dtor, PATCH_JUMP);
InjectHook(0x4F28A0, &CPlayerPed::ClearWeaponTarget, PATCH_JUMP);

ENDPATCHES