#include "common.h"
#include "patcher.h"
#include "CivilianPed.h"

WRAPPER void CCivilianPed::ProcessControl(void) { EAXJMP(0x4BFFE0); }

CCivilianPed::CCivilianPed(int pedtype, int mi) : CPed(pedtype)
{
	CPed::SetModelIndex(mi);
	for (int i = 0; i < 10; i++)
	{
		m_nearPeds[i] = nil;
	}
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
ENDPATCHES
