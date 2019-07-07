#include "common.h"
#include "patcher.h"
#include "CopPed.h"

CCopPed::~CCopPed()
{
	ClearPursuit();
}

WRAPPER void CCopPed::ClearPursuit(void) { EAXJMP(0x4C28C0); }

STARTPATCHES
	InjectHook(0x4C13E0, &CCopPed::dtor, PATCH_JUMP);
ENDPATCHES