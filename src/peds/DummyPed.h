#pragma once

#include "Dummy.h"

// actually unused
class CDummyPed : CDummy
{
	int32 pedType;
	int32 unknown;
};

#ifdef CHECK_STRUCT_SIZES 
static_assert(sizeof(CDummyPed) == 0x70, "CDummyPed: error");
#endif