#pragma once

#include "common.h"
#include "Vehicle.h"

class CPlane : public CVehicle
{
public:
	// 0x288
	int16 m_wIndex;
	int16 field_650;
	int16 m_wNextPathNode;
	char field_654;
	char field_655;
	float field_656;
	int m_nFrameWhenHit;
	char m_bHasBeenHit;
	char m_bIsIncomingCesna;
	char m_bIsDropoffCesna;
	char field_667;

	CPlane(int, uint8);
	~CPlane(void);
	CPlane* ctor(int, uint8);
	void FlagToDestroyWhenNextProcessed() { bRemoveFromWorld = true; }
};
static_assert(sizeof(CPlane) == 0x29C, "CPlane: error");
