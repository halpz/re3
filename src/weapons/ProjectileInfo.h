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
	uint32 m_nExplosionTime;
	bool m_bInUse;
	CVector m_vecPos;

public:
	static CProjectileInfo* GetProjectileInfo(int32 id);
	static CProjectile* (&ms_apProjectile)[32];

	static void Initialise();
	static void Shutdown();
	static bool AddProjectile(CEntity *ped, eWeaponType weapon, CVector pos, float a4);
	static void RemoveProjectile(CProjectileInfo*, CProjectile*);
	static void RemoveNotAdd(CEntity *entity, eWeaponType weaponType, CVector pos);
	static bool RemoveIfThisIsAProjectile(CObject *pObject);
	static void RemoveAllProjectiles(void);
	static void Update();
	static bool IsProjectileInRange(float x1, float x2, float y1, float y2, float z1, float z2, bool remove);
};

extern CProjectileInfo (&gaProjectileInfo)[32];