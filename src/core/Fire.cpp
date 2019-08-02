#include "common.h"
#include "patcher.h"
#include "Fire.h"

CFireManager &gFireManager = *(CFireManager*)0x8F31D0;

WRAPPER void CFire::Extinguish(void) { EAXJMP(0x479D40); }

WRAPPER void CFireManager::StartFire(CEntity *entityOnFire, CEntity *culprit, float, uint32) { EAXJMP(0x479590); }
WRAPPER CFire *CFireManager::FindFurthestFire_NeverMindFireMen(CVector coors, float, float) { EAXJMP(0x479430); }
