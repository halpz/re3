#pragma once

#include "PedType.h"

class CPopulation
{
public:
	static bool &ms_bGivePedsWeapons;

	static void UpdatePedCount(uint32, bool);
};