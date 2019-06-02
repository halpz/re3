#pragma once

#include "Vehicle.h"

class CTrain : public CVehicle
{
public:
	// 0x288
	uint8 stuff[92];
};
static_assert(sizeof(CTrain) == 0x2E4, "CTrain: error");
