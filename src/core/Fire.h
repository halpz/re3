#pragma once
#include "common.h"
#include "Entity.h"

class CFire
{
	char m_bIsOngoing;
	char m_bExists;
	char m_bPropogationFlag;
	char m_bAudioSet;
	CVector m_vecPos;
	CEntity *m_pEntity;
	CEntity *m_pSource;
	int m_nExtinguishTime;
	int m_nStartTime;
	int field_20;
	int field_24;
	int field_28;
	float field_2C;

public:
	void Extinguish(void);
};