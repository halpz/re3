#pragma once

#include "Building.h"

class CTreadable : public CBuilding
{
public:
	static void *operator new(size_t);
	static void operator delete(void*, size_t);

	int16 m_nodeIndicesCars[12];
	int16 m_nodeIndicesPeds[12];

	bool GetIsATreadable(void) { return true; }
};
static_assert(sizeof(CTreadable) == 0x94, "CTreadable: error");
