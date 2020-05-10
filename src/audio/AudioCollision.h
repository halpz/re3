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

	// no methods
};

#ifdef CHECK_STRUCT_SIZES 
static_assert(sizeof(cAudioCollision) == 40, "cAudioCollision: error");
#endif

class cAudioCollisionManager
{
public:
	cAudioCollision m_asCollisions1[NUMAUDIOCOLLISIONS];
	cAudioCollision m_asCollisions2[NUMAUDIOCOLLISIONS];
	uint8 m_bIndicesTable[NUMAUDIOCOLLISIONS];
	uint8 m_bCollisionsInQueue;
	cAudioCollision m_sQueue;

	cAudioCollisionManager();
	void AddCollisionToRequestedQueue();
};

#ifdef CHECK_STRUCT_SIZES 
static_assert(sizeof(cAudioCollisionManager) == 852, "cAudioCollisionManager: error");
#endif