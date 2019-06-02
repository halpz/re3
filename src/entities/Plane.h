#pragma once

#include "Vehicle.h"

class CPlane : public CVehicle
{
public:
	// 0x288
	uint8 stuff[20];
};
static_assert(sizeof(CPlane) == 0x29C, "CPlane: error");
