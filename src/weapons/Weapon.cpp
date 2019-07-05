#include "common.h"
#include "patcher.h"
#include "Weapon.h"
#include "Timer.h"
#include "WeaponInfo.h"

WRAPPER bool CWeapon::Fire(CEntity*, CVector*) { EAXJMP(0x55C380); }
WRAPPER void CWeapon::AddGunshell(CEntity*, CVector const&, CVector2D const&, float) { EAXJMP(0x55F770); }

void
CWeapon::Initialise(eWeaponType type, int ammo)
{
	m_eWeaponType = type;
	m_eWeaponState = WEAPONSTATE_READY;
	if (ammo > 99999)
		m_nAmmoTotal = 99999;
	else
		m_nAmmoTotal = ammo;
	m_nAmmoInClip = 0;
	Reload();
	m_nTimer = 0;
}

void
CWeapon::Reload(void)
{
	if (m_nAmmoTotal == 0)
		return;

	CWeaponInfo *info = CWeaponInfo::GetWeaponInfo(m_eWeaponType);

	if (m_nAmmoTotal >= info->m_nAmountofAmmunition)
		m_nAmmoInClip = info->m_nAmountofAmmunition;
	else
		m_nAmmoInClip = m_nAmmoTotal;
}

bool
CWeapon::IsTypeMelee(void)
{
	return m_eWeaponType == WEAPONTYPE_UNARMED || m_eWeaponType == WEAPONTYPE_BASEBALLBAT;
}

STARTPATCHES
	InjectHook(0x55C330, &CWeapon::Initialise, PATCH_JUMP);
	InjectHook(0x5639D0, &CWeapon::Reload, PATCH_JUMP);
ENDPATCHES