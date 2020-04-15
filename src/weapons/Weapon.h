#pragma once

#define DRIVEBYAUTOAIMING_MAXDIST (2.5f)
#define DOOMAUTOAIMING_MAXDIST    (9000.0f)

enum eWeaponType
{
	WEAPONTYPE_UNARMED,
	WEAPONTYPE_BASEBALLBAT,
	WEAPONTYPE_COLT45,
	WEAPONTYPE_UZI,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_AK47,
	WEAPONTYPE_M16,
	WEAPONTYPE_SNIPERRIFLE,
	WEAPONTYPE_ROCKETLAUNCHER,
	WEAPONTYPE_FLAMETHROWER,
	WEAPONTYPE_MOLOTOV,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_DETONATOR,
	WEAPONTYPE_HELICANNON,
	WEAPONTYPE_LAST_WEAPONTYPE,
	WEAPONTYPE_ARMOUR,
	WEAPONTYPE_RAMMEDBYCAR,
	WEAPONTYPE_RUNOVERBYCAR,
	WEAPONTYPE_EXPLOSION,
	WEAPONTYPE_UZI_DRIVEBY,
	WEAPONTYPE_DROWNING,
	WEAPONTYPE_FALL,
	WEAPONTYPE_UNIDENTIFIED,
	
	WEAPONTYPE_TOTALWEAPONS = WEAPONTYPE_LAST_WEAPONTYPE,
	WEAPONTYPE_TOTAL_INVENTORY_WEAPONS = 13,
};

enum eWeaponFire {
	WEAPON_FIRE_MELEE,
	WEAPON_FIRE_INSTANT_HIT,
	WEAPON_FIRE_PROJECTILE,
	WEAPON_FIRE_AREA_EFFECT,
	WEAPON_FIRE_USE
};

// Taken from MTA SA, seems it's unchanged
enum eWeaponState
{
	WEAPONSTATE_READY,
	WEAPONSTATE_FIRING,
	WEAPONSTATE_RELOADING,
	WEAPONSTATE_OUT_OF_AMMO,
	WEAPONSTATE_MELEE_MADECONTACT
};

class CEntity;
class CPhysical;
class CAutomobile;
struct CColPoint;
class CWeaponInfo;

class CWeapon
{
public:
	eWeaponType m_eWeaponType;
	eWeaponState m_eWeaponState;
	uint32 m_nAmmoInClip;
	uint32 m_nAmmoTotal;
	uint32 m_nTimer;
	bool m_bAddRotOffset;

	CWeapon() {
		m_bAddRotOffset = false;
	}
	
	CWeaponInfo *GetInfo();

	static void InitialiseWeapons(void);
	static void ShutdownWeapons  (void);
	static void UpdateWeapons    (void);
	
	void Initialise(eWeaponType type, int32 ammo);
	
	bool Fire          (CEntity *shooter, CVector *fireSource);
	bool FireFromCar   (CAutomobile *shooter, bool left);
	bool FireMelee     (CEntity *shooter, CVector &fireSource);
	bool FireInstantHit(CEntity *shooter, CVector *fireSource);
	
	void AddGunshell   (CEntity *shooter, CVector const &source, CVector2D const &direction, float size);
	void DoBulletImpact(CEntity *shooter, CEntity *victim, CVector *source, CVector *target, CColPoint *point, CVector2D ahead);
	
	bool FireShotgun   (CEntity *shooter, CVector *fireSource);
	bool FireProjectile(CEntity *shooter, CVector *fireSource, float power);
	
	static void GenerateFlameThrowerParticles(CVector pos, CVector dir);
	
	bool FireAreaEffect       (CEntity *shooter, CVector *fireSource);
	bool FireSniper           (CEntity *shooter);
	bool FireM16_1stPerson    (CEntity *shooter);
	bool FireInstantHitFromCar(CAutomobile *shooter, bool left);
	
	static void DoDoomAiming       (CEntity *shooter, CVector *source, CVector *target);
	static void DoTankDoomAiming   (CEntity *shooter, CEntity *driver, CVector *source, CVector *target);
	static void DoDriveByAutoAiming(CEntity *shooter, CVector *source, CVector *target);
	
	void Reload(void);
	void Update(int32 audioEntity);
	bool IsTypeMelee  (void);
	bool IsType2Handed(void);
	
	static void MakePedsJumpAtShot(CPhysical *shooter, CVector *source, CVector *target);
	
	bool HitsGround(CEntity *holder, CVector *fireSource, CEntity *aimingTo);
	static void BlowUpExplosiveThings(CEntity *thing);
	bool HasWeaponAmmoToBeUsed(void);
	
	static bool ProcessLineOfSight(CVector const &point1, CVector const &point2, CColPoint &point, CEntity *&entity, eWeaponType type, CEntity *shooter, bool checkBuildings, bool checkVehicles, bool checkPeds, bool checkObjects, bool checkDummies, bool ignoreSeeThrough, bool ignoreSomeObjects);
};
VALIDATE_SIZE(CWeapon, 0x18);

void FireOneInstantHitRound(CVector *source, CVector *target, int32 damage);