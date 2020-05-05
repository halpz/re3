#pragma once

#include "Building.h"

class CTreadable : public CBuilding
{
public:
	static void *operator new(size_t);
	static void operator delete(void*, size_t);

#ifndef MIAMI
	int16 m_nodeIndices[2][12];	// first car, then ped
#endif

	bool GetIsATreadable(void) { return true; }
};
#ifndef MIAMI
static_assert(sizeof(CTreadable) == 0x94, "CTreadable: error");
#endif
