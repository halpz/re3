#pragma once

#include "Ped.h"

class CCivilianPed : public CPed
{
	bool m_bAttractorUnk;
	int32 m_nAttractorCycleState;
public:
	CCivilianPed(ePedType, uint32);
	~CCivilianPed(void) { }

	void CivilianAI(void);
	void ProcessControl(void);
	void UseNearbyAttractors(void);
	bool IsAttractedTo(int8);
};
#ifndef PED_SKIN
VALIDATE_SIZE(CCivilianPed, 0x53C);
#endif
