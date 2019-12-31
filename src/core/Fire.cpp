#include "common.h"
#include "patcher.h"
#include "Fire.h"

CFireManager &gFireManager = *(CFireManager*)0x8F31D0;

WRAPPER void CFire::Extinguish(void) { EAXJMP(0x479D40); }

uint32 CFireManager::GetTotalActiveFires() const
{
	return m_nTotalFires;
}

WRAPPER void CFireManager::Update(void) { EAXJMP(0x479310); }

CFire* CFireManager::FindNearestFire(CVector vecPos, float* pDistance)
{
	for (int i = 0; i < MAX_FIREMEN_ATTENDING; i++) {
		int fireId = -1;
		float minDistance = 999999;
		for (int j = 0; j < NUM_FIRES; j++) {
			if (!m_aFires[j].m_bIsOngoing)
				continue;
			if (m_aFires[j].m_bIsScriptFire)
				continue;
			if (m_aFires[j].m_nFiremenPuttingOut != i)
				continue;
			float distance = (m_aFires[j].m_vecPos - vecPos).Magnitude2D();
			if (distance < minDistance) {
				minDistance = distance;
				fireId = j;
			}
		}
		*pDistance = minDistance;
		if (fireId != -1)
			return &m_aFires[fireId];
	}
	return nil;
}

WRAPPER CFire *CFireManager::FindFurthestFire_NeverMindFireMen(CVector coors, float, float) { EAXJMP(0x479430); }
WRAPPER void CFireManager::StartFire(CEntity *entityOnFire, CEntity *culprit, float, uint32) { EAXJMP(0x479590); }
WRAPPER void CFireManager::StartFire(CVector, float, uint8) { EAXJMP(0x479500); }
WRAPPER void CFireManager::ExtinguishPoint(CVector, float) { EAXJMP(0x479DB0); }
WRAPPER int32 CFireManager::StartScriptFire(const CVector& pos, CEntity* culprit, float, uint8) { EAXJMP(0x479E60); }
WRAPPER bool CFireManager::IsScriptFireExtinguish(int16) { EAXJMP(0x479FC0); }
WRAPPER void CFireManager::RemoveScriptFire(int16) { EAXJMP(0x479FE0); }
WRAPPER void CFireManager::RemoveAllScriptFires(void) { EAXJMP(0x47A000); }
WRAPPER void CFireManager::SetScriptFireAudio(int16, bool) { EAXJMP(0x47A040); }
