#pragma once

#include "Vehicle.h"

enum
{
	TRAIN_DOOR_STATE2 = 2
};

class CTrain : public CVehicle
{
public:
	// 0x288
	uint8 stuff1[20];
	uint8 m_trackId;
	uint8 stuff2[7];
	int16 m_doorState;
	uint8 stuff3[62];
};
static_assert(sizeof(CTrain) == 0x2E4, "CTrain: error");
