#pragma once

#include "Ped.h"

class CPlayerPed : public CPed
{
public:
	// 0x53C
	uint8 stuff[180];
};
static_assert(sizeof(CPlayerPed) == 0x5F0, "CPlayerPed: error");
