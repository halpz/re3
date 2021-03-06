#pragma once

#include "Building.h"

class CTreadable : public CBuilding
{
public:
	static void *operator new(size_t) throw();
	static void operator delete(void*, size_t) throw();

	bool GetIsATreadable(void) { return true; }
};
