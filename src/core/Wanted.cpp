#include "common.h"
#include "patcher.h"
#include "Wanted.h"

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