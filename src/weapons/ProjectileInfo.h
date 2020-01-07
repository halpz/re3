#pragma once

class CEntity;
class CObject;
class CProjectile;
enum eWeaponType;

class CProjectileInfo
{
public:
	eWeaponType m_eWeaponType;
	CEntity* m_pSource;
	int m_nExplosionTime;
	char m_bInUse;
	char field_13;
	char field_14;
	char field_15;
	CVector m_vecPos;

public:
	static CProjectileInfo* GetProjectileInfo(int32 id);
	static CProjectile* (&ms_apProjectile)[32];

	static bool RemoveIfThisIsAProjectile(CObject *pObject);
	static void RemoveAllProjectiles(void);
	static bool IsProjectileInRange(float x1, float x2, float y1, float y2, float z1, float z2, bool remove);
};

extern CProjectileInfo* gaProjectileInfo;