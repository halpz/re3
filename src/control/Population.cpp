#include "common.h"
#include "patcher.h"
#include "Game.h"
#include "World.h"
#include "Entity.h"
#include "Population.h"

PedGroup *CPopulation::ms_pPedGroups = (PedGroup*)0x6E9248;
bool &CPopulation::ms_bGivePedsWeapons = *(bool*)0x95CCF6;
int32 &CPopulation::m_AllRandomPedsThisType = *(int32*)0x5FA570;
float &CPopulation::PedDensityMultiplier = *(float*)0x5FA56C;
uint32 &CPopulation::ms_nTotalMissionPeds = *(uint32*)0x8F5F70;
int32 &CPopulation::MaxNumberOfPedsInUse = *(int32*)0x5FA574;

WRAPPER void CPopulation::UpdatePedCount(uint32, bool) { EAXJMP(0x4F5A60); }
WRAPPER void CPopulation::DealWithZoneChange(eLevelName oldLevel, eLevelName newLevel, bool) { EAXJMP(0x4F6200); }
WRAPPER CPed *CPopulation::AddPedInCar(CVehicle *vehicle) { EAXJMP(0x4F5800); }
WRAPPER bool CPopulation::IsPointInSafeZone(CVector *coors) { EAXJMP(0x4F60C0); }

void
CPopulation::RemovePed(CEntity* ent)
{
	CWorld::Remove(ent);
	delete ent;
}
