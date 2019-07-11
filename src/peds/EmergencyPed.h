#pragma once

#include "Ped.h"

class CEmergencyPed : public CPed
{
public:
	// 0x53C
	uint8 stuff[24];
};
static_assert(sizeof(CEmergencyPed) == 0x554, "CEmergencyPed: error");
