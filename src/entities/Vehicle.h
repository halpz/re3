#pragma once

#include "Physical.h"

class CPed;

class CVehicle : public CPhysical
{
public:
	// 0x128
	uint8 stuff1[120];
	int16 m_nAlarmState;
	CPed *pDriver;
	CPed *pPassengers[8];
	uint8 stuff2[24];
	CEntity *m_pCurSurface;
	uint8 stuff3[160];
	int32 m_vehType;
};
static_assert(sizeof(CVehicle) == 0x288, "CVehicle: error");
static_assert(offsetof(CVehicle, m_pCurSurface) == 0x1E0, "CVehicle: error");
