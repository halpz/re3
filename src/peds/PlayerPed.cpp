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

void
CPlayerPed::SetWantedLevel(int32 level)
{
	m_pWanted->SetWantedLevel(level);
}

void
CPlayerPed::SetWantedLevelNoDrop(int32 level)
{
	m_pWanted->SetWantedLevelNoDrop(level);
}


class CPlayerPed_ : public CPlayerPed
{
public:
	void dtor(void) { CPlayerPed::~CPlayerPed(); }
};

STARTPATCHES
	InjectHook(0x4EFB30, &CPlayerPed_::dtor, PATCH_JUMP);
	InjectHook(0x4F28A0, &CPlayerPed::ClearWeaponTarget, PATCH_JUMP);
ENDPATCHES
