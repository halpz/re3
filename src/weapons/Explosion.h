#pragma once

class CEntity;
class CVector;

enum eExplosionType
{
	EXPLOSION_GRENADE,
	EXPLOSION_MOLOTOV,
	EXPLOSION_ROCKET,
	EXPLOSION_CAR,
	EXPLOSION_CAR_QUICK,
	EXPLOSION_BOAT,
	EXPLOSION_HELI,
	EXPLOSION_HELI2,
	EXPLOSION_MINE,
	EXPLOSION_BARREL,
	EXPLOSION_TANK_GRENADE,
	EXPLOSION_HELI_BOMB
};

class CExplosion
{
	eExplosionType m_ExplosionType;
	CVector m_vecPosition;
	float m_fRadius;
	float m_fPropagationRate;
	CEntity *m_pCreatorEntity;
	CEntity *m_pVictimEntity;
	float m_fStopTime;
	uint8 m_nIteration;
	uint8 m_nActiveCounter;
	bool m_bIsBoat;
	bool m_bMakeSound;
	float m_fStartTime;
	uint32 m_nParticlesExpireTime;
	float m_fPower;
	float m_fZshift;
public:
#ifdef SIMPLER_MISSIONS
	static bool AddExplosion(CEntity *explodingEntity, CEntity *culprit, eExplosionType type, const CVector &pos, uint32 lifetime, bool makeSound = true, float radius = -1.0f);
#else
	static bool AddExplosion(CEntity* explodingEntity, CEntity* culprit, eExplosionType type, const CVector& pos, uint32 lifetime, bool makeSound = true);
#endif
	static void ClearAllExplosions(); //done
	static bool DoesExplosionMakeSound(uint8 id); //done
	static int8 GetExplosionActiveCounter(uint8 id); //done
	static CVector *GetExplosionPosition(uint8 id); //done
	static uint8 GetExplosionType(uint8 id); //done, mb need change type to tExplosionType
	static void Initialise(); //done
	static void RemoveAllExplosionsInArea(CVector pos, float radius); //done
	static void ResetExplosionActiveCounter(uint8 id); //done
	static void Shutdown(); //done
	static void Update(); //done
	static bool TestForExplosionInArea(eExplosionType type, float x1, float x2, float y1, float y2, float z1, float z2); //done, not used
};

extern CExplosion gaExplosion[NUM_EXPLOSIONS];