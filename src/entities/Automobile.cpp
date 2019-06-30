#include "common.h"
#include "patcher.h"
#include "Automobile.h"

CAutomobile::CAutomobile(int mi, uint8 owner)
{
	ctor(mi, owner);
}

WRAPPER CAutomobile* CAutomobile::ctor(int, uint8) { EAXJMP(0x52C6B0); }

WRAPPER void CAutomobile::SetDoorDamage(int32, uint32, bool) { EAXJMP(0x530200); }

STARTPATCHES
InjectHook(0x52D170, &CAutomobile::dtor, PATCH_JUMP);
ENDPATCHES