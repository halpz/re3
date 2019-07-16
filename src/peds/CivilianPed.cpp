#include "common.h"
#include "patcher.h"
#include "CivilianPed.h"
#include "Phones.h"

WRAPPER void CCivilianPed::ProcessControl(void) { EAXJMP(0x4BFFE0); }

CCivilianPed::CCivilianPed(int pedtype, int mi) : CPed(pedtype)
{
	SetModelIndex(mi);
	for (int i = 0; i < 10; i++)
	{
		m_nearPeds[i] = nil;
	}
}

bool
CCivilianPed::ProcessNearestFreePhone(int unused)
{
	if (m_nPedState == PED_SEEK_POS)
		return false;

	int phoneId = gPhoneInfo.FindNearestFreePhone(&GetPosition());

	if (phoneId == -1)
		return false;

	if (gPhoneInfo.m_aPhones[phoneId].m_nState != PHONE_STATE_FREE)
		return false;

	field_31C = 1;
	SetMoveState(PEDMOVE_RUN);
	SetSeek(gPhoneInfo.m_aPhones[phoneId].m_vecPos, 0.3f);
	m_phoneId = phoneId;
	m_lookingForPhone = unused;
	return true;
}

class CCivilianPed_ : public CCivilianPed
{
public:
	CCivilianPed *ctor(int pedtype, int mi) { return ::new (this) CCivilianPed(pedtype, mi); };
	void dtor(void) { CCivilianPed::~CCivilianPed(); }
};

STARTPATCHES
	InjectHook(0x4BFF30, &CCivilianPed_::ctor, PATCH_JUMP);
	InjectHook(0x4BFFC0, &CCivilianPed_::dtor, PATCH_JUMP);
	InjectHook(0x4C10C0, &CCivilianPed::ProcessNearestFreePhone, PATCH_JUMP);
ENDPATCHES
