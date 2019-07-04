#include "common.h"
#include "patcher.h"
#include "Wanted.h"

int32 &CWanted::MaximumWantedLevel = *(int32*)0x5F7714;

bool CWanted::AreSwatRequired()
{
	return m_nWantedLevel >= 4;
}

bool CWanted::AreFbiRequired()
{
	return m_nWantedLevel >= 5;
}

bool CWanted::AreArmyRequired()
{
	return m_nWantedLevel >= 6;
}

int CWanted::NumOfHelisRequired()
{
	if (m_IsIgnoredByCops)
		return 0;

	// Return value is number of helicopters, no need to name them.
	switch (m_nWantedLevel) {
	case WANTEDLEVEL_3:
	case WANTEDLEVEL_4:
		return 1;
	case WANTEDLEVEL_5:
	case WANTEDLEVEL_6:
		return 2;
	default:
		return 0;
	};
}

void CWanted::SetWantedLevel(int32 level)
{
	ClearQdCrimes();
	switch (level) {
	case NOTWANTED:
		m_nChaos = 0;
		break;
	case WANTEDLEVEL_1:
		m_nChaos = 60;
		break;
	case WANTEDLEVEL_2:
		m_nChaos = 220;
		break;
	case WANTEDLEVEL_3:
		m_nChaos = 420;
		break;
	case WANTEDLEVEL_4:
		m_nChaos = 820;
		break;
	case WANTEDLEVEL_5:
		m_nChaos = 1620;
		break;
	case WANTEDLEVEL_6:
		m_nChaos = 3220;
		break;
	default:
		if (level > MaximumWantedLevel)
			m_nChaos = MaximumWantedLevel;
		break;
	}
	UpdateWantedLevel();
}

void CWanted::ClearQdCrimes()
{
	for (int i = 0; i < 16; i++) {
		m_sCrimes[i].m_eCrimeType = CRIME_NONE;
	};
}

void CWanted::UpdateWantedLevel()
{
	int32 CurrWantedLevel = m_nWantedLevel;

	if (m_nChaos >= 0 && m_nChaos < 40) {
		m_nWantedLevel = NOTWANTED;
		m_MaximumLawEnforcerVehicles = 0;
		m_MaxCops = 0;
		m_RoadblockDensity = 0;
	}
	else if (m_nChaos >= 40 && m_nChaos < 200) {
		m_nWantedLevel = WANTEDLEVEL_1;
		m_MaximumLawEnforcerVehicles = 1;
		m_MaxCops = 1;
		m_RoadblockDensity = 0;
	}
	else if (m_nChaos >= 200 && m_nChaos < 400) {
		m_nWantedLevel = WANTEDLEVEL_2;
		m_MaximumLawEnforcerVehicles = 2;
		m_MaxCops = 3;
		m_RoadblockDensity = 0;
	}
	else if (m_nChaos >= 400 && m_nChaos < 800) {
		m_nWantedLevel = WANTEDLEVEL_3;
		m_MaximumLawEnforcerVehicles = 2;
		m_MaxCops = 4;
		m_RoadblockDensity = 4;
	}
	else if (m_nChaos >= 800 && m_nChaos < 1600) {
		m_nWantedLevel = WANTEDLEVEL_4;
		m_MaximumLawEnforcerVehicles = 2;
		m_MaxCops = 6;
		m_RoadblockDensity = 8;
	}
	else if (m_nChaos >= 1600 && m_nChaos < 3200) {
		m_nWantedLevel = WANTEDLEVEL_5;
		m_MaximumLawEnforcerVehicles = 3;
		m_MaxCops = 8;
		m_RoadblockDensity = 10;
	}
	else if (m_nChaos >= 3200) {
		m_nWantedLevel = WANTEDLEVEL_6;
		m_MaximumLawEnforcerVehicles = 3;
		m_MaxCops = 10;
		m_RoadblockDensity = 12;
	}

	if (CurrWantedLevel != m_nWantedLevel)
		m_nLastWantedLevelChange = CTimer::GetTimeInMilliseconds();
}