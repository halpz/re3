#pragma once

#include "Ped.h"

class CCivilianPed : public CPed
{
public:
	CCivilianPed(int, int);
	CCivilianPed* ctor(int, int);
	void dtor(void) { this->CCivilianPed::~CCivilianPed(); }
};
static_assert(sizeof(CCivilianPed) == 0x53C, "CCivilianPed: error");
