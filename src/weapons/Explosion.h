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
	EXPLOSION_HELI,
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
	bool m_bActive;
	int8 m_bActiveCounter;
	int32 m_nStartTime;
	uint32 m_nParticlesExpireTime;
	float m_fPower;
	int32 field_34;
	int32 field_38;
public:
	static void Initialise();
	static void Shutdown();
	static void AddExplosion(CEntity *explodingEntity, CEntity *culprit, eExplosionType type,
	                         const CVector &pos, uint32);

	static int8 GetExplosionActiveCounter(uint8 id);
	static CVector *GetExplosionPosition(uint8 id);
	static uint8 GetExplosionType(uint8 id);
	static void ResetExplosionActiveCounter(uint8 id);
	static void RemoveAllExplosionsInArea(CVector, float);
	static bool TestForExplosionInArea(eExplosionType, float, float, float, float, float, float);
};

extern CExplosion (&gaExplosion)[48];