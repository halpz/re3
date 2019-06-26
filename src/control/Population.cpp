#include "common.h"
#include "patcher.h"
#include "Population.h"

bool &CPopulation::ms_bGivePedsWeapons = *(bool*)0x95CCF6;

WRAPPER void CPopulation::UpdatePedCount(uint32, bool) { EAXJMP(0x4F5A60); }