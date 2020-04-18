#pragma once
#include "Ped.h"

enum eCopType
{
	COP_STREET = 0,
	COP_FBI = 1,
	COP_SWAT = 2,
	COP_ARMY = 3,
};

class CCopPed : public CPed
{
public:
	int16 m_wRoadblockNode;
	float m_fDistanceToTarget;
	bool m_bIsInPursuit;
	bool m_bIsDisabledCop;
	int8 field_1350;
	bool m_bBeatingSuspect;
	bool m_bStopAndShootDisabledZone;
	bool m_bZoneDisabled;
	int32 field_1356;
	eCopType m_nCopType;
	int8 field_1364;
	int8 field_1365;
	int8 field_1366;
	int8 field_1367;

	CCopPed(eCopType);
	~CCopPed();

	void ClearPursuit(void);
	void ProcessControl(void);
	void SetArrestPlayer(CPed*);
	void SetPursuit(bool);
	void ArrestPlayer(void);
	void ScanForCrimes(void);
	void CopAI(void);
};

static_assert(sizeof(CCopPed) == 0x558, "CCopPed: error");
