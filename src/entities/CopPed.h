#pragma once
#include "Ped.h"

enum eCrimeType
{
	CRIME_NONE,
	CRIME_POSSESSION_GUN,
	CRIME_HIT_PED,
	CRIME_HIT_COP,
	CRIME_SHOOT_PED,
	CRIME_SHOOT_COP,
	CRIME_STEAL_CAR,
	CRIME_RUN_REDLIGHT,
	CRIME_RECKLESS_DRIVING,
	CRIME_SPEEDING,
	CRIME_RUNOVER_PED,
	CRIME_RUNOVER_COP,
	CRIME_SHOOT_HELI,
	CRIME_PED_BURNED,
	CRIME_COP_BURNED,
	CRIME_VEHICLE_BURNED,
	CRIME_DESTROYED_CESSNA,
};

enum eCopType
{
	COP_STREET = 0,
	COP_FBI = 1,
	COP_SWAT = 2,
	COP_ARMY = 3,
};

class CCrime
{
public:
	eCrimeType m_eCrimeType;
	CEntity *m_pVictim;
	int32 m_nCrimeTime;
	CVector m_vecCrimePos;
	int8 m_bReported;
	int8 m_bMultiplier;
	int8 pad_20[2];
};

class CCopPed : public CPed
{
public:
	int16 m_wRoadblockNode;
	int8 field_1342;
	int8 field_1343;
	float m_fDistanceToTarget;
	int8 m_bIsInPursuit;
	int8 m_bIsDisabledCop;
	int8 field_1350;
	int8 field_1351;
	int8 m_bZoneDisabledButClose;
	int8 m_bZoneDisabled;
	int8 field_1354;
	int8 field_1355;
	int32 field_1356;
	eCopType m_nCopType;
	int8 field_1364;
	int8 field_1365;
	int8 field_1366;
	int8 field_1367;
};

static_assert(sizeof(CCopPed) == 0x558, "CCopPed: error");
