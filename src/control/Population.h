#pragma once

#include "PedType.h"

struct PedGroup
{
	int32 models[8];
};

class CPopulation
{
public:
	static PedGroup *ms_pPedGroups;	//[31]
	static bool &ms_bGivePedsWeapons;

	static void UpdatePedCount(uint32, bool);
	static void DealWithZoneChange(eLevelName oldLevel, eLevelName newLevel, bool);
};
