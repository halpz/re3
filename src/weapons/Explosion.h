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
	bool m_bIsMakeSound;
	float m_fStartTime;
	uint32 m_nParticlesExpireTime;
	float m_fPower;
	float m_fZshift;
public:
	static void Initialise();
	static void ClearAllExplosions();
	static void Shutdown();
	static int8 GetExplosionActiveCounter(uint8 id);
	static void ResetExplosionActiveCounter(uint8 id);
	static uint8 GetExplosionType(uint8 id);
	static CVector *GetExplosionPosition(uint8 id);
	static bool DoesExplosionMakeSound(uint8 id); //done
	static bool AddExplosion(CEntity *explodingEntity, CEntity *culprit, eExplosionType type, const CVector &pos, uint32 lifetime, bool isMakeSound = true); //done(new parametr in android ver is fix for one mission)
	static void Update();
	static bool TestForExplosionInArea(eExplosionType type, float x1, float x2, float y1, float y2, float z1, float z2);
	static void RemoveAllExplosionsInArea(CVector pos, float radius);
};

extern CExplosion gaExplosion[NUM_EXPLOSIONS];