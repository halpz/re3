#pragma once

#include "Building.h"

class CTreadable : public CBuilding
{
public:
	static void *operator new(size_t);
	static void operator delete(void*, size_t);

	bool GetIsATreadable(void) { return true; }
};
