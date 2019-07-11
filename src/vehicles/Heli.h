#pragma once

#include "Vehicle.h"

class CHeli : public CVehicle
{
public:
	// 0x288
	uint8 stuff[180];

	CHeli(int, uint8);
	CHeli* ctor(int, uint8);

	static void SpecialHeliPreRender(void);
};
static_assert(sizeof(CHeli) == 0x33C, "CHeli: error");
