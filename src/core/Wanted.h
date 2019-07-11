#pragma once
#include "Entity.h"
#include "math/Vector.h"
#include "CopPed.h"

enum eWantedLevel {
	NOTWANTED,
	WANTEDLEVEL_1,
	WANTEDLEVEL_2,
	WANTEDLEVEL_3,
	WANTEDLEVEL_4,
	WANTEDLEVEL_5,
	WANTEDLEVEL_6,
};

class CWanted
{
public:
	int32 m_nChaos;
	int32 m_nLastUpdateTime;
	int32 m_nLastWantedLevelChange;
	float m_fCrimeSensitivity;
	uint8 m_CurrentCops;
	uint8 m_MaxCops;
	uint8 m_MaximumLawEnforcerVehicles;
	int8 field_19;
	int16 m_RoadblockDensity;
	uint8 m_IsIgnoredByCops : 1;
	uint8 m_IsIgnoredByEveryOne : 1;
	uint8 m_IsSwatRequired : 1;
	uint8 m_IsFbiRequired : 1;
	uint8 m_IdArmyRequired : 1;
	int8 field_23;
	int32 m_nWantedLevel;
	CCrime m_sCrimes[16];
	CCopPed *m_pCops[10];
	static int32 &MaximumWantedLevel;

public:
	bool AreSwatRequired();
	bool AreFbiRequired();
	bool AreArmyRequired();
	int NumOfHelisRequired();
	void SetWantedLevel(int32);
	void SetWantedLevelNoDrop(int32 level);
	void ClearQdCrimes();
	void UpdateWantedLevel();
};

static_assert(sizeof(CWanted) == 0x204, "CWanted: error");
