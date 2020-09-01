#pragma once

#include "Object.h"

class CStingerSegment : public CObject
{
public:
	CStingerSegment();
	~CStingerSegment();
};

#define NUM_STINGER_SEGMENTS (12)

enum {
	STINGERSTATE_NONE = 0,
	STINGERSTATE_DEPLOYING,
	STINGERSTATE_DEPLOYED,
	STINGERSTATE_UNDEPLOYING,
	STINGERSTATE_REMOVE,
};

class CStinger
{
public:
	bool bIsDeployed;
	uint32 m_nTimeOfDeploy;
	CVector m_vPos;
	float m_fMax_Z;
	float m_fMin_Z;
	CVector2D m_vPositions[60];
	CStingerSegment *pSpikes[NUM_STINGER_SEGMENTS];
	class CPed *pOwner;
	uint8 m_nSpikeState;
	CStinger();
	void Init(CPed *pPed);
	void Remove();
	void Deploy(CPed *pPed);
	void CheckForBurstTyres();
	void Process();
};