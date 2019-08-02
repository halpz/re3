#pragma once
#include "Weapon.h"

enum ePickupType
{
	PICKUP_NONE = 0,
	PICKUP_IN_SHOP = 1,
	PICKUP_ON_STREET = 2,
	PICKUP_ONCE = 3,
	PICKUP_ONCE_TIMEOUT = 4,
	PICKUP_COLLECTABLE1 = 5,
	PICKUP_IN_SHOP_OUT_OF_STOCK = 6,
	PICKUP_MONEY = 7,
	PICKUP_MINE_INACTIVE = 8,
	PICKUP_MINE_ARMED = 9,
	PICKUP_NAUTICAL_MINE_INACTIVE = 10,
	PICKUP_NAUTICAL_MINE_ARMED = 11,
	PICKUP_FLOATINGPACKAGE = 12,
	PICKUP_FLOATINGPACKAGE_FLOATING = 13,
	PICKUP_ON_STREET_SLOW = 14,
};

class CEntity;
class CObject;

class CPickup
{
	ePickupType m_eType;
	uint16 m_wQuantity;
	CObject *m_pObject;
	uint32 m_nTimer;
	int16 m_eModelIndex;
	int16 m_wIndex;
	CVector m_vecPos;
};

class CPickups
{
public:
	static void RenderPickUpText(void);
	static void DoCollectableEffects(CEntity *ent);
	static void DoMoneyEffects(CEntity *ent);
	static void DoMineEffects(CEntity *ent);
	static void DoPickUpEffects(CEntity *ent);
	static void RemoveAllFloatingPickups();
	static int32 GenerateNewOne(CVector, uint32, uint8, uint32);
	static int32 GenerateNewOne_WeaponType(CVector, eWeaponType, uint8, uint32);

	static CPickup (&aPickUps)[NUMPICKUPS];
	static uint16 ms_maxAmmosForWeapons[20];
};

class CPacManPickups
{
public:
	static void Render(void);
};
