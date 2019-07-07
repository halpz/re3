#pragma once

#include "Ped.h"

class CCivilianPed : public CPed
{
public:
	CCivilianPed(int, int);
	virtual ~CCivilianPed(void) { }

	virtual void ProcessControl(void);

	CCivilianPed *ctor(int pedtype, int mi) { return ::new (this) CCivilianPed(pedtype, mi); };
	void dtor(void) { this->CCivilianPed::~CCivilianPed(); }
};
static_assert(sizeof(CCivilianPed) == 0x53C, "CCivilianPed: error");
