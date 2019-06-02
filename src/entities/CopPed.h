#pragma once

#include "Ped.h"

class CCopPed : public CPed
{
public:
	// 0x53C
	uint8 stuff[28];
};
static_assert(sizeof(CCopPed) == 0x558, "CCopPed: error");
