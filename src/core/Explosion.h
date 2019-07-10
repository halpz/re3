#pragma once

class CEntity;

enum eExplosionType
{
	EXPLOSION_3 = 3,
	EXPLOSION_4
};

class CExplosion
{
public:
	static void AddExplosion(CEntity *explodingEntity, CEntity *culprit, eExplosionType type, const CVector &pos, uint32);
};
