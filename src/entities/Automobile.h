#pragma once

#include "Vehicle.h"

class CAutomobile : public CVehicle
{
public:
	// 0x288
	uint8 stuff1[484];
	float m_afWheelSuspDist[4];
	uint8 stuff2[300];
};
static_assert(sizeof(CAutomobile) == 0x5A8, "CAutomobile: error");
static_assert(offsetof(CAutomobile, m_afWheelSuspDist) == 0x46C, "CAutomobile: error");
