#pragma once

#define NUMAUDIOCOLLISIONS 10

class CEntity;

class cAudioCollision
{
public:
	CEntity *m_pEntity1;
	CEntity *m_pEntity2;
	uint8 m_bSurface1;
	uint8 m_bSurface2;
	float m_fIntensity1;
	float m_fIntensity2;
	CVector m_vecPosition;
	float m_fDistance;
	int32 m_nBaseVolume;

	cAudioCollision() { Reset(); }

	void Reset()
	{
		m_pEntity1 = nil;
		m_pEntity2 = nil;
		m_bSurface1 = 0;
		m_bSurface2 = 0;
		m_fIntensity1 = m_fIntensity2 = 0.0f;
		m_vecPosition = CVector(0.0f, 0.0f, 0.0f);
		m_fDistance = 0.0f;
	}
};

VALIDATE_SIZE(cAudioCollision, 40);

class cAudioCollisionManager
{
public:
	cAudioCollision m_asCollisions1[NUMAUDIOCOLLISIONS];
	cAudioCollision m_asCollisions2[NUMAUDIOCOLLISIONS];
	uint8 m_bIndicesTable[NUMAUDIOCOLLISIONS];
	uint8 m_bCollisionsInQueue;
	cAudioCollision m_sQueue;

	cAudioCollisionManager()
	{
		m_sQueue.Reset();

		for(int i = 0; i < NUMAUDIOCOLLISIONS; i++)
			m_bIndicesTable[i] = NUMAUDIOCOLLISIONS;

		m_bCollisionsInQueue = 0;
	}
	void AddCollisionToRequestedQueue();
};

VALIDATE_SIZE(cAudioCollisionManager, 852);
