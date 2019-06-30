#include "common.h"
#include "patcher.h"
#include "CivilianPed.h"

CCivilianPed::CCivilianPed(int pedtype, int mi)
{
	ctor(pedtype, mi);
}

WRAPPER CCivilianPed* CCivilianPed::ctor(int pedtype, int mi) { EAXJMP(0x4BFF30); }

STARTPATCHES
	InjectHook(0x4BFFC0, &CCivilianPed::dtor, PATCH_JUMP);
ENDPATCHES