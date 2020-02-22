#pragma once

#include "Ped.h"

class CCivilianPed : public CPed
{
public:
	CCivilianPed(ePedType, uint32);
	~CCivilianPed(void) { }

	void CivilianAI(void);
	void ProcessControl(void);
};
static_assert(sizeof(CCivilianPed) == 0x53C, "CCivilianPed: error");
