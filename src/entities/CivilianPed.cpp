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

STARTPATCHES
	InjectHook(0x4BFF30, &CCivilianPed::ctor, PATCH_JUMP);
	InjectHook(0x4BFFC0, &CCivilianPed::dtor, PATCH_JUMP);
ENDPATCHES