#pragma once

class CEntity;
enum eWeaponType;

class CBulletInfo
{
public:
	static void Initialise(void);
	static void Shutdown(void);
	static void AddBullet(CEntity *firingEntity, eWeaponType type, CVector pos, CVector velocity);
	static void Update(void);
	static bool TestForSniperBullet(float x1, float x2, float y1, float y2, float z1, float z2);
};