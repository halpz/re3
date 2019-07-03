#include "common.h"
#include "patcher.h"
#include "Game.h"
#include "Population.h"

PedGroup *CPopulation::ms_pPedGroups = (PedGroup*)0x6E9248;
bool &CPopulation::ms_bGivePedsWeapons = *(bool*)0x95CCF6;
int32 &CPopulation::m_AllRandomPedsThisType = *(int32*)0x5FA570;
float &CPopulation::PedDensityMultiplier = *(float*)0x5FA56C;

WRAPPER void CPopulation::UpdatePedCount(uint32, bool) { EAXJMP(0x4F5A60); }
WRAPPER void CPopulation::DealWithZoneChange(eLevelName oldLevel, eLevelName newLevel, bool) { EAXJMP(0x4F6200); }
