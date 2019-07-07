#include "common.h"
#include "patcher.h"
#include "Boat.h"

CBoat::CBoat(int mi, uint8 owner)
{
	ctor(mi, owner);
}

WRAPPER CBoat* CBoat::ctor(int, uint8) { EAXJMP(0x53E3E0); }

STARTPATCHES
InjectHook(0x53E790, &CBoat::dtor, PATCH_JUMP);
ENDPATCHES