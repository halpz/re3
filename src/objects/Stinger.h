#pragma once

#include "Object.h"

class CStingerSegment : public CObject
{
public:
	CStingerSegment();
	~CStingerSegment();
};

#define NUM_STINGER_SEGMENTS (12)

class CStinger
{
	// TODO: better names
	enum {
		STINGERSTATE_NONE = 0,
		STINGERSTATE_STATE1,
		STINGERSTATE_STATE2,
		STINGERSTATE_STATE3,
		STINGERSTATE_REMOVE,
	};

	bool bIsDeployed;
	uint32 m_nTimeOfDeploy;
	CVector m_vPos;
	float m_fMax_Z;
	float m_fMin_Z;
	CVector2D m_vPositions[60];
	CStingerSegment *pSpikes[NUM_STINGER_SEGMENTS];
	class CPed *pOwner;
	uint8 m_nSpikeState;
public:
	CStinger();
	void Init(CPed *pPed);
	void Remove();
	void Deploy(CPed *pPed);
	void CheckForBurstTyres();
	void Process();
};