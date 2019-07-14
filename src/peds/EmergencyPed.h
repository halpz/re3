#pragma once

#include "Fire.h"
#include "Ped.h"

class CEmergencyPed : public CPed
{
public:
	// 0x53C
	CPed* m_pRevivedPed;
	int32 m_nEmergencyPedState; // looks like flags
	void* m_pAttendedAccident; //TODO: CAccident*
	CFire* m_pAttendedFire;
	int8 field_1356;
	int32 field_1360;

	CEmergencyPed(uint32);
	void ProcessControl(void);
};
static_assert(sizeof(CEmergencyPed) == 0x554, "CEmergencyPed: error");
