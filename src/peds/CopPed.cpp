#include "common.h"
#include "patcher.h"
#include "CopPed.h"
#include "ModelIndices.h"

CCopPed::CCopPed(eCopType copType) : CPed(PEDTYPE_COP)
{
	m_nCopType = copType;
	switch (copType) {
	case COP_STREET:
		SetModelIndex(MI_COP);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		m_currentWeapon = WEAPONTYPE_UNARMED;
		m_fArmour = 0.0f;
		m_wepSkills = 208; /* TODO: what is this? seems unused */
		m_wepAccuracy = 60;
		break;
	case COP_FBI:
		SetModelIndex(MI_FBI);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		GiveWeapon(WEAPONTYPE_AK47, 1000);
		SetCurrentWeapon(WEAPONTYPE_AK47);
		m_fArmour = 100.0f;
		m_wepSkills = 176; /* TODO: what is this? seems unused */
		m_wepAccuracy = 76;
		break;
	case COP_SWAT:
		SetModelIndex(MI_SWAT);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		GiveWeapon(WEAPONTYPE_UZI, 1000);
		SetCurrentWeapon(WEAPONTYPE_UZI);
		m_fArmour = 50.0f;
		m_wepSkills = 32; /* TODO: what is this? seems unused */
		m_wepAccuracy = 64;
		break;
	case COP_ARMY:
		SetModelIndex(MI_ARMY);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		GiveWeapon(WEAPONTYPE_M16, 1000);
		GiveWeapon(WEAPONTYPE_GRENADE, 10);
		SetCurrentWeapon(WEAPONTYPE_M16);
		m_fArmour = 100.0f;
		m_wepSkills = 32; /* TODO: what is this? seems unused */
		m_wepAccuracy = 84;
		break;
	default:
		break;
	}
	m_bIsInPursuit = false;
	field_1350 = 1;
	m_bIsDisabledCop = false;
	field_1356 = 0;
	m_attackTimer = 0;
	field_1351 = 0;
	m_bZoneDisabledButClose = false;
	m_bZoneDisabled = false;
	field_1364 = -1;
	m_pPointGunAt = nil;
}

CCopPed::~CCopPed()
{
	ClearPursuit();
}

WRAPPER void CCopPed::ClearPursuit(void) { EAXJMP(0x4C28C0); }

class CCopPed_ : public CCopPed
{
public:
	CCopPed *ctor(eCopType type) { return ::new (this) CCopPed(type); };
	void dtor(void) { CCopPed::~CCopPed(); }
};

STARTPATCHES
	InjectHook(0x4C11B0, &CCopPed_::ctor, PATCH_JUMP);
	InjectHook(0x4C13E0, &CCopPed_::dtor, PATCH_JUMP);
ENDPATCHES
