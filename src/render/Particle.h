#pragma once
#include "ParticleMgr.h"


class CEntity;

class CParticle
{
	enum
	{
		RAND_TABLE_SIZE    = 20,
		SIN_COS_TABLE_SIZE = 1024
	};
	
public:
	CVector   m_vecPosition;
	CVector   m_vecVelocity;
	CVector   m_vecScreenPosition;
	UInt32     m_nTimeWhenWillBeDestroyed;
	UInt32     m_nTimeWhenColorWillBeChanged;
	Float     m_fZGround;
	CVector   m_vecParticleMovementOffset;
	Int16     m_nCurrentZRotation;
	UInt16     m_nZRotationTimer;
	Float     m_fCurrentZRadius;
	UInt16     m_nZRadiusTimer;
	char _pad0[2];
	Float     m_fSize;
	Float     m_fExpansionRate;
	UInt16     m_nFadeToBlackTimer;
	UInt16     m_nFadeAlphaTimer;
	UInt8     m_nColorIntensity;
	UInt8     m_nAlpha;
	UInt16    m_nCurrentFrame;
	Int16     m_nAnimationSpeedTimer;
	Int16     m_nRotationStep;
	Int16     m_nRotation;
	RwRGBA    m_Color;
	char _pad1[2];
	CParticle *m_pNext;
	
	CParticle()
	{
		;
	}
	
	~CParticle()
	{
		;
	}

	//static Float      ms_afRandTable[RAND_TABLE_SIZE];
	static Float      (&ms_afRandTable)[RAND_TABLE_SIZE];
	static CParticle *m_pUnusedListHead;
	
	/*
	static Float      m_SinTable[SIN_COS_TABLE_SIZE];
	static Float      m_CosTable[SIN_COS_TABLE_SIZE];
	*/
	static Float      (&m_SinTable)[SIN_COS_TABLE_SIZE];
	static Float      (&m_CosTable)[SIN_COS_TABLE_SIZE];
	
	
	static void ReloadConfig();
	static void Initialise();
	static void Shutdown();
	
	static CParticle *AddParticle(tParticleType type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity = NULL, Float fSize = 0.0f, Int32 nRotationSpeed = 0, Int32 nRotation = 0, Int32 nCurFrame = 0, Int32 nLifeSpan = 0);
	static CParticle *AddParticle(tParticleType type, CVector const &vecPos, CVector const &vecDir, CEntity *pEntity, Float fSize, RwRGBA const &color, Int32 nRotationSpeed = 0, Int32 nRotation = 0, Int32 nCurFrame = 0, Int32 nLifeSpan = 0);

	static void Update();
	static void Render();

	static void RemovePSystem(tParticleType type);
	static void RemoveParticle(CParticle *pParticle, CParticle *pPrevParticle, tParticleSystemData *pPSystemData);
	
	static inline void _Next(CParticle *&pParticle, CParticle *&pPrevParticle, tParticleSystemData *pPSystemData, Bool bRemoveParticle)
	{
		if ( bRemoveParticle )
		{
			RemoveParticle(pParticle, pPrevParticle, pPSystemData);
					
			if ( pPrevParticle )
				pParticle = pPrevParticle->m_pNext;
			else
				pParticle = pPSystemData->m_pParticles;
		}
		else
		{
			pPrevParticle = pParticle;
			pParticle = pParticle->m_pNext;
		}
	}

	static void AddJetExplosion(CVector const &vecPos, Float fPower, Float fSize);
	static void AddYardieDoorSmoke(CVector const &vecPos, CMatrix const &matMatrix);

};
/*
class CParticle
{
public:
	static void AddParticle(tParticleType, const CVector &pos, const CVector &velocity, CEntity *ent = nil,
		float size = 0.0, int32 rotationStep = 0, int32 rotation = 0, int startFrame = 0, int lifeSpan = 0);
};
*/