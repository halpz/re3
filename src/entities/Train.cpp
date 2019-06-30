#include "common.h"
#include "patcher.h"
#include "Train.h"

CTrain::CTrain(int mi, uint8 owner)
{
	ctor(mi, owner);
}

WRAPPER CTrain* CTrain::ctor(int, uint8) { EAXJMP(0x54E2A0); }

STARTPATCHES
InjectHook(0x54E450, &CTrain::dtor, PATCH_JUMP);
ENDPATCHES