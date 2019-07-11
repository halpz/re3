#pragma once

#include "common.h"
#include "Vehicle.h"

class CPlane : public CVehicle
{
public:
	// 0x288
	uint8 stuff[20];

	CPlane(int, uint8);
	~CPlane(void);
	CPlane* ctor(int, uint8);
	void FlagToDestroyWhenNextProcessed() { bRemoveFromWorld = true; }
};
static_assert(sizeof(CPlane) == 0x29C, "CPlane: error");
