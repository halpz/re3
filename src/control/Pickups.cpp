#include "common.h"

#include "main.h"

#include "Camera.h"
#include "Coronas.h"
#include "Darkel.h"
#include "Entity.h"
#include "Explosion.h"
#include "Font.h"
#include "Garages.h"
#include "General.h"
#include "ModelIndices.h"
#include "Object.h"
#include "Pad.h"
#include "Pickups.h"
#include "PlayerPed.h"
#include "Wanted.h"
#include "DMAudio.h"
#include "Fire.h"
#include "PointLights.h"
#include "Pools.h"
#ifdef FIX_BUGS
#include "Replay.h"
#endif
#include "Script.h"
#include "Shadows.h"
#include "SpecialFX.h"
#include "Sprite.h"
#include "Timer.h"
#include "WaterLevel.h"
#include "World.h"
#include "Hud.h"
#include "Messages.h"

CPickup CPickups::aPickUps[NUMPICKUPS];
int16 CPickups::NumMessages;
int32 CPickups::aPickUpsCollected[NUMCOLLECTEDPICKUPS];
int16 CPickups::CollectedPickUpIndex;

int32 CPickups::PlayerOnWeaponPickup;
int32 CPickups::CollectPickupBuffer;

// unused
bool CPickups::bPickUpcamActivated;
CVehicle *CPickups::pPlayerVehicle;
CVector CPickups::StaticCamCoors;
uint32 CPickups::StaticCamStartTime;

tPickupMessage CPickups::aMessages[NUMPICKUPMESSAGES];

// TODO(Miami)
uint16 AmmoForWeapon[20] = { 0, 1, 45, 125, 25, 150, 300, 25, 5, 250, 5, 5, 0, 500, 0, 100, 0, 0, 0, 0 };

// --MIAMI: Done
uint16 AmmoForWeapon_OnStreet[WEAPONTYPE_TOTALWEAPONS] = {
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 34,
	12, 16, 14, 10, 100, 60, 60, 60, 60, 60, 20, 14,
	4, 150, 100, 500, 1, 400, 36, 0,
};
uint16 CostOfWeapon[20] = { 0, 10, 250, 800, 1500, 3000, 5000, 10000, 25000, 25000, 2000, 2000, 0, 50000, 0, 3000, 0, 0, 0, 0 };

// TODO(Miami): Those are all placeholders!!
uint8 aWeaponReds[] = { 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 0, 128, 255, 255, 0, 255, 0, 128, 128, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 128, 0, 255, 0 };
uint8 aWeaponGreens[] = { 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
0, 255, 128, 255, 0, 255, 128, 255, 0, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
0, 255, 0, 255, 0 };
uint8 aWeaponBlues[] = { 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
0, 0, 255, 0, 255, 255, 0, 128, 255, 0, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
0, 128, 255, 0, 0 };

void
ModifyStringLabelForControlSetting(char *str)
{
	int len = (int)strlen(str);
	if (len <= 2)
		return;

	if (str[len - 2] != '_')
		return;

	switch (CPad::GetPad(0)->Mode) {
		case 0:
		case 1:
			str[len - 1] = 'L';
			break;
		case 2:
			str[len - 1] = 'T';
			break;
		case 3:
			str[len - 1] = 'C';
			break;
		default:
			return;
	}
}

void
CPickup::RemoveKeepType()
{
	CWorld::Remove(m_pObject);
	delete m_pObject;

	m_bRemoved = true;
	m_pObject = nil;
}

void
CPickup::Remove()
{
	RemoveKeepType();
	m_eType = PICKUP_NONE;
}

// --MIAMI: Done
CObject *
CPickup::GiveUsAPickUpObject(CObject **ppObject, CObject **ppExtraObject, int32 handle, int32 extraHandle)
{
	CObject *&object = *ppObject;
	CObject *&extraObject = *ppExtraObject;

	object = extraObject = nil;

	int32 modelId = -1;
	if (CModelInfo::GetModelInfo(m_eModelIndex)->GetModelType() == MITYPE_WEAPON) {
		CWeaponInfo *weaponInfo = CWeaponInfo::GetWeaponInfo(((CWeaponModelInfo*)CModelInfo::GetModelInfo(m_eModelIndex))->GetWeaponInfo());
		modelId = weaponInfo->m_nModelId;
		if (modelId == m_eModelIndex)
			modelId = weaponInfo->m_nModel2Id;
	}

	if (handle >= 0) {
		CPools::MakeSureSlotInObjectPoolIsEmpty(handle);
		if (extraHandle >= 0)
			CPools::MakeSureSlotInObjectPoolIsEmpty(extraHandle);
		if (object == nil)
			object = new(handle) CObject(m_eModelIndex, false);

		if (extraHandle >= 0 && modelId != -1 && extraObject == nil)
			extraObject = new(extraHandle) CObject(modelId, false);
	} else {
		object = new CObject(m_eModelIndex, false);
		if (modelId != -1)
			extraObject = new CObject(modelId, false);
	}

	if (object == nil) return nil;
	object->ObjectCreatedBy = MISSION_OBJECT;
	object->SetPosition(m_vecPos);
	object->SetOrientation(0.0f, 0.0f, -HALFPI);
	object->GetMatrix().UpdateRW();
	object->UpdateRwFrame();

	object->bAffectedByGravity = false;
	object->bExplosionProof = true;
	object->bUsesCollision = false;
	object->bIsPickup = true;
	object->obj_flag_02 = m_effects;
	object->bHasPreRenderEffects = true;

	if (extraObject) {
		extraObject->ObjectCreatedBy = MISSION_OBJECT;
		extraObject->SetPosition(m_vecPos);
		extraObject->SetOrientation(0.0f, 0.0f, -HALFPI);
		extraObject->GetMatrix().UpdateRW();
		extraObject->UpdateRwFrame();

		extraObject->bAffectedByGravity = false;
		extraObject->bExplosionProof = true;
		extraObject->bUsesCollision = false;
		extraObject->bIsPickup = true;
		extraObject->obj_flag_02 = true;
		extraObject->bHasPreRenderEffects = true;
		extraObject->m_nBonusValue = 0;
		extraObject->bPickupObjWithMessage = false;
		extraObject->bOutOfStock = false;
	}

	object->m_nBonusValue = (m_eModelIndex == MI_PICKUP_BONUS || m_eModelIndex == MI_PICKUP_CLOTHES) ? m_nQuantity : 0;

	switch (m_eType)
	{
	case PICKUP_IN_SHOP:
		object->bPickupObjWithMessage = true;
		object->bOutOfStock = false;
		if (m_eModelIndex == MI_PICKUP_HEALTH || m_eModelIndex == MI_PICKUP_ADRENALINE)
			object->m_nCostValue = 0;
		else
			object->m_nCostValue = CostOfWeapon[CPickups::WeaponForModel(m_eModelIndex)];
		break;
	case PICKUP_ON_STREET:
	case PICKUP_ONCE:
	case PICKUP_ONCE_TIMEOUT:
	case PICKUP_COLLECTABLE1:
	case PICKUP_MONEY:
	case PICKUP_MINE_INACTIVE:
	case PICKUP_MINE_ARMED:
	case PICKUP_NAUTICAL_MINE_INACTIVE:
	case PICKUP_NAUTICAL_MINE_ARMED:
	case PICKUP_FLOATINGPACKAGE:
	case PICKUP_ON_STREET_SLOW:
		object->bPickupObjWithMessage = false;
		object->bOutOfStock = false;
		break;
	case PICKUP_IN_SHOP_OUT_OF_STOCK:
		object->bPickupObjWithMessage = false;
		object->bOutOfStock = true;
		object->bRenderScorched = true;
		break;
	case PICKUP_FLOATINGPACKAGE_FLOATING:
	default:
		break;
	}
	return object;
}

bool
CPickup::CanBePickedUp(CPlayerPed *player, int playerId)
{
	assert(m_pObject != nil);
	bool cannotBePickedUp =
		(m_pObject->GetModelIndex() == MI_PICKUP_BODYARMOUR && player->m_fArmour > CWorld::Players[playerId].m_nMaxArmour - 0.5f)
		|| (m_pObject->GetModelIndex() == MI_PICKUP_HEALTH && player->m_fHealth > CWorld::Players[playerId].m_nMaxHealth - 0.5f)
		|| (m_pObject->GetModelIndex() == MI_PICKUP_BRIBE && player->m_pWanted->m_nWantedLevel == 0)
		|| (m_pObject->GetModelIndex() == MI_PICKUP_KILLFRENZY && (CTheScripts::IsPlayerOnAMission() || CDarkel::FrenzyOnGoing() || !CGame::nastyGame));
	return !cannotBePickedUp;
}

bool
CPickup::Update(CPlayerPed *player, CVehicle *vehicle, int playerId)
{
	float waterLevel;

	if (m_pObject) {
		m_pObject->GetMatrix().GetPosition() = m_vecPos;
		if (m_pExtraObject)
			m_pExtraObject->GetMatrix().GetPosition() = m_vecPos;
	}
	if (m_eType == PICKUP_ASSET_REVENUE) {
		uint32 timePassed = CTimer::GetTimeInMilliseconds() - m_nTimer;
		m_nTimer = CTimer::GetTimeInMilliseconds();

		if (Distance(FindPlayerCoors(), m_vecPos) > 10.0f)
			m_fRevenue += float(timePassed * m_nMoneySpeed) / SQR(1200.0f);

		m_fRevenue = Min(m_fRevenue, m_nQuantity);

		m_pObject->m_nCostValue = m_fRevenue < 10 ? 0 : m_fRevenue;
	}

	if (m_bRemoved) {
		if (CTimer::GetTimeInMilliseconds() > m_nTimer) {
			// respawn pickup if we're far enough
			float dist = (FindPlayerCoors().x - m_vecPos.x) * (FindPlayerCoors().x - m_vecPos.x) + (FindPlayerCoors().y - m_vecPos.y) * (FindPlayerCoors().y - m_vecPos.y);
			if (dist > 100.0f || m_eType == PICKUP_IN_SHOP && dist > 2.4f) {
				m_pObject = GiveUsAPickUpObject(&m_pObject, &m_pExtraObject, -1, -1);
				if (m_pObject) {
					CWorld::Add(m_pObject);
					m_bRemoved = false;
				}
			}
		}
		return false;
	}

	if (!m_pObject) {
		GiveUsAPickUpObject(&m_pObject, &m_pExtraObject, -1, -1);
		if (m_pObject)
			CWorld::Add(m_pObject);
		if (m_pExtraObject)
			CWorld::Add(m_pExtraObject);
	}

	if (!m_pObject) return false;

	if (!IsMine()) {
		// let's check if we touched the pickup
		bool isPickupTouched = false;
		if (m_pObject->GetModelIndex() == MI_PICKUP_BRIBE) {
			if (vehicle != nil) {
				if (vehicle->IsSphereTouchingVehicle(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z, 2.0f))
					isPickupTouched = true;
			}
			else {
				if (Abs(player->GetPosition().z - m_pObject->GetPosition().z) < 2.0f) {
					if ((player->GetPosition().x - m_pObject->GetPosition().x) * (player->GetPosition().x - m_pObject->GetPosition().x) +
						(player->GetPosition().y - m_pObject->GetPosition().y) * (player->GetPosition().y - m_pObject->GetPosition().y) < 1.8f)
						isPickupTouched = true;
				}
			}
		} else if (m_pObject->GetModelIndex() == MI_PICKUP_CAMERA) {
			if (vehicle != nil && vehicle->IsSphereTouchingVehicle(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z, 2.0f)) {
				isPickupTouched = true;
			}
		} else if (vehicle == nil) {
			if (Abs(player->GetPosition().z - m_pObject->GetPosition().z) < 2.0f) {
				if ((player->GetPosition().x - m_pObject->GetPosition().x) * (player->GetPosition().x - m_pObject->GetPosition().x) +
					(player->GetPosition().y - m_pObject->GetPosition().y) * (player->GetPosition().y - m_pObject->GetPosition().y) < 1.8f)
					isPickupTouched = true;
			}
		}

		// MIAMI code here

		// ...

		// if we didn't then we've got nothing to do
		if (isPickupTouched && CanBePickedUp(player, playerId)) {
			CPad::GetPad(0)->StartShake(120, 100);
			switch (m_eType)
			{
			case PICKUP_IN_SHOP:
				if (CWorld::Players[playerId].m_nMoney < CostOfWeapon[CPickups::WeaponForModel(m_pObject->GetModelIndex())]) {
					CGarages::TriggerMessage("PU_MONY", -1, 6000, -1);
				} else {
					CWorld::Players[playerId].m_nMoney -= CostOfWeapon[CPickups::WeaponForModel(m_pObject->GetModelIndex())];
					if (!CPickups::GivePlayerGoodiesWithPickUpMI(m_pObject->GetModelIndex(), playerId)) {
						player->GiveWeapon(CPickups::WeaponForModel(m_pObject->GetModelIndex()), AmmoForWeapon[CPickups::WeaponForModel(m_pObject->GetModelIndex())]);
						player->m_nSelectedWepSlot = player->GetWeaponSlot(CPickups::WeaponForModel(m_pObject->GetModelIndex()));
						DMAudio.PlayFrontEndSound(SOUND_PICKUP_WEAPON_BOUGHT, m_pObject->GetModelIndex() - MI_GRENADE);
					}
					RemoveKeepType();
					m_nTimer = CTimer::GetTimeInMilliseconds() + 5000;
					return true;
				}
				break;
			case PICKUP_ON_STREET:
			case PICKUP_ON_STREET_SLOW:
				if (!CPickups::GivePlayerGoodiesWithPickUpMI(m_pObject->GetModelIndex(), playerId)) {
					if (CPickups::WeaponForModel(m_pObject->GetModelIndex())) {
						player->GiveWeapon(CPickups::WeaponForModel(m_pObject->GetModelIndex()), m_nQuantity != 0 ? m_nQuantity : AmmoForWeapon_OnStreet[CPickups::WeaponForModel(m_pObject->GetModelIndex())]);
						if (player->m_nSelectedWepSlot == player->GetWeaponSlot(WEAPONTYPE_UNARMED)) {
							player->m_nSelectedWepSlot = player->GetWeaponSlot(CPickups::WeaponForModel(m_pObject->GetModelIndex()));
						}
						DMAudio.PlayFrontEndSound(SOUND_PICKUP_WEAPON, m_pObject->GetModelIndex() - MI_GRENADE);
					} else if (m_pObject->GetModelIndex() == MI_PICKUP_CAMERA && vehicle != nil) {
						DMAudio.PlayFrontEndSound(SOUND_PICKUP_BONUS, 0);
						CPickups::bPickUpcamActivated = true;
						CPickups::pPlayerVehicle = FindPlayerVehicle();
						CPickups::StaticCamCoors = m_pObject->GetPosition();
						CPickups::StaticCamStartTime = CTimer::GetTimeInMilliseconds();
					}
				}
				if (m_eType == PICKUP_ON_STREET) {
					m_nTimer = CTimer::GetTimeInMilliseconds() + 30000;
				} else if (m_eType == PICKUP_ON_STREET_SLOW) {
					if (MI_PICKUP_BRIBE == m_pObject->GetModelIndex())
						m_nTimer = CTimer::GetTimeInMilliseconds() + 300000;
					else
						m_nTimer = CTimer::GetTimeInMilliseconds() + 720000;
				}

				RemoveKeepType();
				return true;
			case PICKUP_ONCE:
			case PICKUP_ONCE_TIMEOUT:
				if (!CPickups::GivePlayerGoodiesWithPickUpMI(m_pObject->GetModelIndex(), playerId)) {
					if (CPickups::WeaponForModel(m_pObject->GetModelIndex())) {
						player->GiveWeapon(CPickups::WeaponForModel(m_pObject->GetModelIndex()), m_nQuantity != 0 ? m_nQuantity : AmmoForWeapon[CPickups::WeaponForModel(m_pObject->GetModelIndex())]);
						if (player->m_nSelectedWepSlot == player->GetWeaponSlot(WEAPONTYPE_UNARMED))
							player->m_nSelectedWepSlot = player->GetWeaponSlot(CPickups::WeaponForModel(m_pObject->GetModelIndex()));
					}
					DMAudio.PlayFrontEndSound(SOUND_PICKUP_WEAPON, m_pObject->GetModelIndex() - MI_GRENADE);
				}
				Remove();
				return true;
			case PICKUP_COLLECTABLE1:
				CWorld::Players[playerId].m_nCollectedPackages++;
				CWorld::Players[playerId].m_nMoney += 100;

				if (CWorld::Players[playerId].m_nCollectedPackages == CWorld::Players[playerId].m_nTotalPackages) {
					printf("All collectables have been picked up\n");
					CGarages::TriggerMessage("CO_ALL", -1, 5000, -1);
					CWorld::Players[CWorld::PlayerInFocus].m_nMoney += 100000;
				} else
					CGarages::TriggerMessage("CO_ONE", CWorld::Players[CWorld::PlayerInFocus].m_nCollectedPackages, 5000, CWorld::Players[CWorld::PlayerInFocus].m_nTotalPackages);

				Remove();
				DMAudio.PlayFrontEndSound(SOUND_PICKUP_HIDDEN_PACKAGE, 0);
				return true;
			case PICKUP_MONEY:
				CWorld::Players[playerId].m_nMoney += m_nQuantity;
				sprintf(gString, "$%d", m_nQuantity);
#ifdef MONEY_MESSAGES
				CMoneyMessages::RegisterOne(m_vecPos + CVector(0.0f, 0.0f, 1.0f), gString, 0, 255, 0, 0.5f, 0.5f);
#endif
				Remove();
				DMAudio.PlayFrontEndSound(SOUND_PICKUP_MONEY, 0);
				return true;
			case PICKUP_ASSET_REVENUE:
				CWorld::Players[CWorld::PlayerInFocus].m_nMoney += m_fRevenue;
				m_fRevenue = 0;
				DMAudio.PlayFrontEndSound(SOUND_PICKUP_MONEY, 0);
				return false;
			// TODO(Miami): Control flow
			case PICKUP_PROPERTY_FORSALE:
				ModifyStringLabelForControlSetting(m_sTextKey);
				CMessages::InsertNumberInString(TheText.Get(m_sTextKey), m_nQuantity,
					0, 0, 0, 0, 0, gUString);
				if (!CHud::IsHelpMessageBeingDisplayed())
					CHud::SetHelpMessage(gUString, false); // 0, 0, 0);
				if (CPickups::CollectPickupBuffer == 0)
					return false;
				if (CTheScripts::IsPlayerOnAMission()) {
					CHud::SetHelpMessage(TheText.Get("PROP_2"), true); // , false);
				} else {
					if (CWorld::Players[CWorld::PlayerInFocus].m_nMoney >= m_nQuantity) {
						CWorld::Players[CWorld::PlayerInFocus].m_nMoney -= m_nQuantity;
						CHud::SetHelpMessage(nil, true); //, false);
						Remove();
						return true;
					}
					CHud::SetHelpMessage(TheText.Get("PROP_1"), true); //, false);
				}
				return false;
			default:
				break;
			}
		}
	} else {
		switch (m_eType)
		{
		case PICKUP_MINE_INACTIVE:
			if (vehicle != nil && !vehicle->IsSphereTouchingVehicle(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z, 2.0f)) {
				m_eType = PICKUP_MINE_ARMED;
				m_nTimer = CTimer::GetTimeInMilliseconds() + 10000;
			}
			break;
		case PICKUP_NAUTICAL_MINE_INACTIVE:
		{
			if (CWaterLevel::GetWaterLevel(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z + 5.0f, &waterLevel, false))
				m_pObject->GetMatrix().GetPosition().z = waterLevel + 0.6f;

			m_pObject->GetMatrix().UpdateRW();
			m_pObject->UpdateRwFrame();

			bool touched = false;
			for (int32 i = CPools::GetVehiclePool()->GetSize()-1; i >= 0; i--) {
				CVehicle *vehicle = CPools::GetVehiclePool()->GetSlot(i);
				if (vehicle != nil && vehicle->IsSphereTouchingVehicle(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z, 1.5f)) {
					touched = true;
					break; // added break here
				}
			}

			if (!touched) {
				m_eType = PICKUP_NAUTICAL_MINE_ARMED;
				m_nTimer = CTimer::GetTimeInMilliseconds() + 10000;
			}
			break;
		}
		case PICKUP_NAUTICAL_MINE_ARMED:
			if (CWaterLevel::GetWaterLevel(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z + 5.0f, &waterLevel, false))
				m_pObject->GetMatrix().GetPosition().z = waterLevel + 0.6f;

			m_pObject->GetMatrix().UpdateRW();
			m_pObject->UpdateRwFrame();
			// no break here
		case PICKUP_MINE_ARMED:
		{
			bool explode = false;
			if (CTimer::GetTimeInMilliseconds() > m_nTimer)
				explode = true;
			else {// added else here since vehicle lookup is useless
				for (int32 i = CPools::GetVehiclePool()->GetSize()-1; i >= 0; i--) {
					CVehicle *vehicle = CPools::GetVehiclePool()->GetSlot(i);
					if (vehicle != nil && vehicle->IsSphereTouchingVehicle(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z, 1.5f)) {
						explode = true;
						break; // added break here
					}
				}
			}
			if (explode) {
				CExplosion::AddExplosion(nil, nil, EXPLOSION_MINE, m_pObject->GetPosition(), 0);
				Remove();
			}
			break;
		}
		case PICKUP_FLOATINGPACKAGE:
			m_pObject->m_vecMoveSpeed.z -= 0.01f * CTimer::GetTimeStep();
			m_pObject->GetMatrix().GetPosition() += m_pObject->GetMoveSpeed() * CTimer::GetTimeStep();

			m_pObject->GetMatrix().UpdateRW();
			m_pObject->UpdateRwFrame();
			if (CWaterLevel::GetWaterLevel(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z + 5.0f, &waterLevel, 0) && waterLevel >= m_pObject->GetPosition().z)
				m_eType = PICKUP_FLOATINGPACKAGE_FLOATING;
			break;
		case PICKUP_FLOATINGPACKAGE_FLOATING:
			if (CWaterLevel::GetWaterLevel(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z + 5.0f, &waterLevel, 0))
				m_pObject->GetMatrix().GetPosition().z = waterLevel;

			m_pObject->GetMatrix().UpdateRW();
			m_pObject->UpdateRwFrame();
			if (vehicle != nil && vehicle->IsSphereTouchingVehicle(m_pObject->GetPosition().x, m_pObject->GetPosition().y, m_pObject->GetPosition().z, 2.0f)) {
				Remove();
				DMAudio.PlayFrontEndSound(SOUND_PICKUP_FLOAT_PACKAGE, 0);
				return true;
			}
			break;
		default: break;
		}
	}
	if (!m_bRemoved && (m_eType == PICKUP_ONCE_TIMEOUT || m_eType == PICKUP_MONEY) && CTimer::GetTimeInMilliseconds() > m_nTimer)
		Remove();
	return false;
}

// --MIAMI: Done
void
CPickup::GetRidOfObjects()
{
	if (m_pObject) {
		CWorld::Remove(m_pObject);
		delete m_pObject;
		m_pObject = nil;
	}
	if (m_pExtraObject) {
		CWorld::Remove(m_pExtraObject);
		delete m_pExtraObject;
		m_pExtraObject = nil;
	}
}

// --MIAMI: Done
void
CPickups::Init(void)
{
	NumMessages = 0;
	for (int i = 0; i < NUMPICKUPS; i++) {
		aPickUps[i].m_eType = PICKUP_NONE;
		aPickUps[i].m_nIndex = 1;
		aPickUps[i].m_pObject = nil;
		aPickUps[i].m_pExtraObject = nil;
	}

	for (int i = 0; i < NUMCOLLECTEDPICKUPS; i++)
		aPickUpsCollected[i] = 0;

	CollectedPickUpIndex = 0;
}

// --MIAMI: Done
bool
CPickups::TestForPickupsInBubble(CVector pos, float range)
{
	for (int i = 0; i < NUMPICKUPS; i++) {
		if ((aPickUps[i].m_vecPos - pos).Magnitude() < range)
			return true;
	}
	return false;
}

// --MIAMI: Done
bool
CPickups::TryToMerge_WeaponType(CVector pos, eWeaponType weapon, uint8 type, uint32 quantity, bool unused) {
	for (int i = 0; i < NUMPICKUPS; i++) {
		if (aPickUps[i].m_eType == type && aPickUps[i].m_eModelIndex == ModelForWeapon(weapon))
			if ((aPickUps[i].m_vecPos - pos).Magnitude() < 7.5f) {
				aPickUps[i].m_nQuantity += quantity;
				return true;
			}
	}
	return false;
}

// --MIAMI: Done
bool
CPickups::IsPickUpPickedUp(int32 pickupId)
{
	for (int i = 0; i < NUMCOLLECTEDPICKUPS; i++) {
		if (pickupId == aPickUpsCollected[i]) {
			aPickUpsCollected[i] = 0;
			return true;
		}
	}
	return false;
}

// --MIAMI: Done
void
CPickups::PassTime(uint32 time)
{
	for (int i = 0; i < NUMPICKUPS; i++) {
		if (aPickUps[i].m_eType != PICKUP_NONE && aPickUps[i].m_eType != PICKUP_ASSET_REVENUE) {
			if (aPickUps[i].m_nTimer <= time)
				aPickUps[i].m_nTimer = 0;
			else
				aPickUps[i].m_nTimer -= time;
		}
	}
}

// --MIAMI: Done
int32
CPickups::GetActualPickupIndex(int32 index)
{
	if (index == -1) return -1;

	// doesn't look nice
	if ((uint16)((index & 0xFFFF0000) >> 16) != aPickUps[(uint16)index].m_nIndex) return -1;
	return (uint16)index;
}

// --MIAMI: Done
bool
CPickups::GivePlayerGoodiesWithPickUpMI(int16 modelIndex, int playerIndex)
{
	CPlayerPed *player;

	if (playerIndex <= 0) player = CWorld::Players[CWorld::PlayerInFocus].m_pPed;
	else player = CWorld::Players[playerIndex].m_pPed;

	if (modelIndex == MI_PICKUP_ADRENALINE) {
		player->m_bAdrenalineActive = true;
		player->m_nAdrenalineTime = CTimer::GetTimeInMilliseconds() + 20000;
		player->m_fCurrentStamina = player->m_fMaxStamina;
		DMAudio.PlayFrontEndSound(SOUND_PICKUP_ADRENALINE, 0);
		return true;
	} else if (modelIndex == MI_PICKUP_BODYARMOUR) {
		player->m_fArmour = CWorld::Players[playerIndex].m_nMaxArmour;
		DMAudio.PlayFrontEndSound(SOUND_PICKUP_ARMOUR, 0);
		return true;
	} else if (modelIndex == MI_PICKUP_INFO) {
		DMAudio.PlayFrontEndSound(SOUND_PICKUP_BONUS, 0);
		return true;
	} else if (modelIndex == MI_PICKUP_HEALTH) {
		player->m_fHealth = CWorld::Players[playerIndex].m_nMaxHealth;
		DMAudio.PlayFrontEndSound(SOUND_PICKUP_HEALTH, 0);
		return true;
	} else if (modelIndex == MI_PICKUP_BONUS) {
		DMAudio.PlayFrontEndSound(SOUND_PICKUP_BONUS, 0);
		return true;
	} else if (modelIndex == MI_PICKUP_BRIBE) {
		int32 level = Max(FindPlayerPed()->m_pWanted->m_nWantedLevel - 1, 0);
		player->SetWantedLevel(level);
		DMAudio.PlayFrontEndSound(SOUND_PICKUP_BONUS, 0);
		return true;
	} else if (modelIndex == MI_PICKUP_KILLFRENZY) {
		DMAudio.PlayFrontEndSound(SOUND_PICKUP_BONUS, 0);
		return true;
	}
	return false;
}

// --MIAMI: Todo
void
CPickups::RemoveAllFloatingPickups()
{
	for (int i = 0; i < NUMPICKUPS; i++) {
		if (aPickUps[i].m_eType == PICKUP_FLOATINGPACKAGE || aPickUps[i].m_eType == PICKUP_FLOATINGPACKAGE_FLOATING) {
			if (aPickUps[i].m_pObject) {
				CWorld::Remove(aPickUps[i].m_pObject);
				delete aPickUps[i].m_pObject;
				aPickUps[i].m_pObject = nil;
			}
		}
	}
}

// --MIAMI: Done
void
CPickups::RemovePickUp(int32 pickupIndex)
{
	int32 index = CPickups::GetActualPickupIndex(pickupIndex);
	if (index == -1) return;

	if (aPickUps[index].m_pObject) {
		CWorld::Remove(aPickUps[index].m_pObject);
		delete aPickUps[index].m_pObject;
		aPickUps[index].m_pObject = nil;
	}
	if (aPickUps[index].m_pExtraObject) {
		CWorld::Remove(aPickUps[index].m_pExtraObject);
		delete aPickUps[index].m_pExtraObject;
		aPickUps[index].m_pExtraObject = nil;
	}
	aPickUps[index].m_eType = PICKUP_NONE;
	aPickUps[index].m_bRemoved = true;
}

// --MIAMI: Done
int32
CPickups::GenerateNewOne(CVector pos, uint32 modelIndex, uint8 type, uint32 quantity, uint32 rate, bool highPriority, char* pText)
{
	bool bFreeFound = false;
	int32 slot = 0;

	if (type == PICKUP_FLOATINGPACKAGE || type == PICKUP_NAUTICAL_MINE_INACTIVE || highPriority) {
		for (slot = NUMPICKUPS-1; slot >= 0; slot--) {
			if (aPickUps[slot].m_eType == PICKUP_NONE) {
				bFreeFound = true;
				break;
			}
		}
	}
	if (!bFreeFound) {
		for (slot = 0; slot < NUMGENERALPICKUPS; slot++) {
			if (aPickUps[slot].m_eType == PICKUP_NONE) {
				bFreeFound = true;
				break;
			}
		}
	}

	if (!bFreeFound) {
		for (slot = 0; slot < NUMGENERALPICKUPS; slot++) {
			if (aPickUps[slot].m_eType == PICKUP_MONEY) break;
		}

		if (slot >= NUMGENERALPICKUPS) {
			for (slot = 0; slot < NUMGENERALPICKUPS; slot++) {
				if (aPickUps[slot].m_eType == PICKUP_ONCE_TIMEOUT || aPickUps[slot].m_eType == PICKUP_ONCE_TIMEOUT_SLOW) break;
			}

			if (slot >= NUMGENERALPICKUPS) return -1;
			aPickUps[slot].GetRidOfObjects();
		}
	}

	if (slot >= NUMPICKUPS) return -1;

	aPickUps[slot].m_eType = (ePickupType)type;
	aPickUps[slot].m_bRemoved = false;
	aPickUps[slot].m_nQuantity = quantity;
	aPickUps[slot].m_nMoneySpeed = rate;
	aPickUps[slot].m_fRevenue = 0.0f;
	aPickUps[slot].m_nTimer = CTimer::GetTimeInMilliseconds();
	aPickUps[slot].m_effects = highPriority;
	aPickUps[slot].m_effects2 = false;
	if (type == PICKUP_ONCE_TIMEOUT)
		aPickUps[slot].m_nTimer = CTimer::GetTimeInMilliseconds() + 20000;
	else if (type == PICKUP_ONCE_TIMEOUT_SLOW)
		aPickUps[slot].m_nTimer = CTimer::GetTimeInMilliseconds() + 120000;
	else if (type == PICKUP_MONEY)
		aPickUps[slot].m_nTimer = CTimer::GetTimeInMilliseconds() + 30000;
	else if (type == PICKUP_MINE_INACTIVE || type == PICKUP_MINE_ARMED) {
		aPickUps[slot].m_eType = PICKUP_MINE_INACTIVE;
		aPickUps[slot].m_nTimer = CTimer::GetTimeInMilliseconds() + 1500;
	} else if (type == PICKUP_NAUTICAL_MINE_INACTIVE || type == PICKUP_NAUTICAL_MINE_ARMED) {
		aPickUps[slot].m_eType = PICKUP_NAUTICAL_MINE_INACTIVE;
		aPickUps[slot].m_nTimer = CTimer::GetTimeInMilliseconds() + 1500;
	}
	aPickUps[slot].m_eModelIndex = modelIndex;
	if (pText)
		strncpy(aPickUps[slot].m_sTextKey, pText, 8);
	else
		aPickUps[slot].m_sTextKey[0] = '\0';

	aPickUps[slot].m_vecPos = pos;
	aPickUps[slot].m_pObject = aPickUps[slot].GiveUsAPickUpObject(&aPickUps[slot].m_pObject, &aPickUps[slot].m_pExtraObject, -1, -1);
	if (aPickUps[slot].m_pObject)
		CWorld::Add(aPickUps[slot].m_pObject);
	if (aPickUps[slot].m_pExtraObject)
		CWorld::Add(aPickUps[slot].m_pExtraObject);
	return GetNewUniquePickupIndex(slot);
}

// --MIAMI: Done
int32
CPickups::GenerateNewOne_WeaponType(CVector pos, eWeaponType weaponType, uint8 type, uint32 quantity)
{
	return GenerateNewOne(pos, ModelForWeapon(weaponType), type, quantity);
}

// --MIAMI: Done
int32
CPickups::GetNewUniquePickupIndex(int32 slot)
{
	if (aPickUps[slot].m_nIndex >= 0xFFFE)
		aPickUps[slot].m_nIndex = 1;
	else
		aPickUps[slot].m_nIndex++;
	return slot | (aPickUps[slot].m_nIndex << 16);
}

// --MIAMI: Done
int32
CPickups::ModelForWeapon(eWeaponType weaponType)
{
	return CWeaponInfo::GetWeaponInfo(weaponType)->m_nModelId;
}

// --MIAMI: Done
eWeaponType
CPickups::WeaponForModel(int32 model)
{
	if (model == MI_PICKUP_BODYARMOUR) return WEAPONTYPE_ARMOUR;
	if (model == MI_PICKUP_HEALTH) return WEAPONTYPE_HEALTH;
	if (model == MI_PICKUP_ADRENALINE) return WEAPONTYPE_ARMOUR;
	if (model == -1) return WEAPONTYPE_UNARMED;
	return (eWeaponType)((CWeaponModelInfo*)CModelInfo::GetModelInfo(model))->GetWeaponInfo();
}

// --MIAMI: Done
void
CPickups::AddToCollectedPickupsArray(int32 index)
{
	aPickUpsCollected[CollectedPickUpIndex++] = index | (aPickUps[index].m_nIndex << 16);
	if (CollectedPickUpIndex >= NUMCOLLECTEDPICKUPS)
		CollectedPickUpIndex = 0;
}

void
CPickups::Update()
{
#ifdef FIX_BUGS // RIP speedrunning (solution from SA)
	if (CReplay::IsPlayingBack())
		return;
#endif
#ifdef CAMERA_PICKUP
	if ( bPickUpcamActivated ) // taken from PS2
	{
		float dist = (FindPlayerCoors() - StaticCamCoors).Magnitude2D();
		float mult;
		if ( dist < 10.0f )
			mult = 1.0f - (dist / 10.0f );
		else
			mult = 0.0f;

		CVector pos = StaticCamCoors;
		pos.z += (pPlayerVehicle->GetColModel()->boundingBox.GetSize().z + 2.0f) * mult;

		if ( (CTimer::GetTimeInMilliseconds() - StaticCamStartTime) > 750 )
		{
			TheCamera.SetCamPositionForFixedMode(pos, CVector(0.0f, 0.0f, 0.0f));
			TheCamera.TakeControl(FindPlayerVehicle(), CCam::MODE_FIXED, JUMP_CUT, CAMCONTROL_SCRIPT);
		}

		if ( FindPlayerVehicle() != pPlayerVehicle
			|| (FindPlayerCoors() - StaticCamCoors).Magnitude() > 40.0f
			|| ((CTimer::GetTimeInMilliseconds() - StaticCamStartTime) > 60000) )
		{
			TheCamera.RestoreWithJumpCut();
			bPickUpcamActivated = false;
		}
	}
#endif
	if (CPad::GetPad(0)->CollectPickupJustDown())
		CollectPickupBuffer = 6;
	else
		CollectPickupBuffer = Max(0, CollectPickupBuffer - 1);

	if (PlayerOnWeaponPickup)
		PlayerOnWeaponPickup = Max(0, PlayerOnWeaponPickup - 1);

#define PICKUPS_FRAME_SPAN (6)
#ifdef FIX_BUGS
	for (uint32 i = NUMGENERALPICKUPS * (CTimer::GetFrameCounter() % PICKUPS_FRAME_SPAN) / PICKUPS_FRAME_SPAN; i < NUMGENERALPICKUPS * (CTimer::GetFrameCounter() % PICKUPS_FRAME_SPAN + 1) / PICKUPS_FRAME_SPAN; i++) {
#else // BUG: this code can only reach 318 out of 320 pickups
	for (uint32 i = NUMGENERALPICKUPS / PICKUPS_FRAME_SPAN * (CTimer::GetFrameCounter() % PICKUPS_FRAME_SPAN); i < NUMGENERALPICKUPS / PICKUPS_FRAME_SPAN * (CTimer::GetFrameCounter() % PICKUPS_FRAME_SPAN + 1); i++) {
#endif
		if (aPickUps[i].m_eType != PICKUP_NONE && aPickUps[i].Update(FindPlayerPed(), FindPlayerVehicle(), CWorld::PlayerInFocus)) {
			AddToCollectedPickupsArray(i);
		}
	}
#undef PICKUPS_FRAME_SPAN
	for (uint32 i = NUMGENERALPICKUPS; i < NUMPICKUPS; i++) {
		if (aPickUps[i].m_eType != PICKUP_NONE && aPickUps[i].Update(FindPlayerPed(), FindPlayerVehicle(), CWorld::PlayerInFocus)) {
			AddToCollectedPickupsArray(i);
		}
	}
}

void
CPickups::DoPickUpEffects(CEntity *entity)
{
	if (entity->GetModelIndex() == MI_PICKUP_KILLFRENZY)
		entity->bDoNotRender = CTheScripts::IsPlayerOnAMission() || CDarkel::FrenzyOnGoing() || !CGame::nastyGame;

	if (!entity->bDoNotRender) {
		float s = Sin((float)((CTimer::GetTimeInMilliseconds() + (uintptr)entity) & 0x7FF) * DEGTORAD(360.0f / 0x800));
		float modifiedSin = 0.3f * (s + 1.0f);


		int16 colorId;
		bool doInnerGlow = false;
		bool doOuterGlow = true;

		if (entity->GetModelIndex() == MI_PICKUP_ADRENALINE || entity->GetModelIndex() == MI_PICKUP_CAMERA) {
			colorId = WEAPONTYPE_TOTALWEAPONS;
			doInnerGlow = true;
			doOuterGlow = false;
		} else if (entity->GetModelIndex() == MI_PICKUP_BODYARMOUR) {
			colorId = WEAPONTYPE_TOTALWEAPONS + 1;
		} else if (entity->GetModelIndex() == MI_PICKUP_BRIBE) {
			doInnerGlow = true;
			doOuterGlow = false;
		} else if (entity->GetModelIndex() == MI_PICKUP_INFO || entity->GetModelIndex() == MI_PICKUP_KILLFRENZY) {
			colorId = WEAPONTYPE_TOTALWEAPONS + 2;
			doInnerGlow = true;
			doOuterGlow = false;
		} else if (entity->GetModelIndex() == MI_PICKUP_HEALTH || entity->GetModelIndex() == MI_PICKUP_BONUS) {
			colorId = WEAPONTYPE_TOTALWEAPONS;
			doInnerGlow = true;
			doOuterGlow = false;
		} else
			colorId = WeaponForModel(entity->GetModelIndex());

		const CVector& pos = entity->GetPosition();
		if (doOuterGlow) {
			float colorModifier = ((CGeneral::GetRandomNumber() & 0x1F) * 0.015f + 1.0f) * modifiedSin * 0.15f;
			CShadows::StoreStaticShadow((uintptr)entity, SHADOWTYPE_ADDITIVE, gpShadowExplosionTex, &pos, 2.0f, 0.0f, 0.0f, -2.0f, 0,
		                            aWeaponReds[colorId] * colorModifier, aWeaponGreens[colorId] * colorModifier, aWeaponBlues[colorId] * colorModifier, 4.0f,
		                            1.0f, 40.0f, false, 0.0f);

			float radius = (CGeneral::GetRandomNumber() & 0xF) * 0.1f + 3.0f;
			CPointLights::AddLight(CPointLights::LIGHT_POINT, pos, CVector(0.0f, 0.0f, 0.0f), radius, aWeaponReds[colorId] * modifiedSin / 256.0f, aWeaponGreens[colorId] * modifiedSin / 256.0f, aWeaponBlues[colorId] * modifiedSin / 256.0f, CPointLights::FOG_NONE, true);
			float size = (CGeneral::GetRandomNumber() & 0xF) * 0.0005f + 0.6f;
			CCoronas::RegisterCorona((uintptr)entity,
				aWeaponReds[colorId] * modifiedSin / 2.0f, aWeaponGreens[colorId] * modifiedSin / 2.0f, aWeaponBlues[colorId] * modifiedSin / 2.0f,
				255,
				pos,
				size, 65.0f, CCoronas::TYPE_RING, CCoronas::FLARE_NONE, CCoronas::REFLECTION_OFF, CCoronas::LOSCHECK_OFF, CCoronas::STREAK_OFF, 0.0f);
		}

		CObject *object = (CObject*)entity;
		if (object->bPickupObjWithMessage || object->bOutOfStock || object->m_nBonusValue) {
			float dist = (TheCamera.GetPosition() - pos).Magnitude();
			const float MAXDIST = 12.0f;

			if (dist < MAXDIST && NumMessages < NUMPICKUPMESSAGES) {
				RwV3d vecOut;
				float fDistX, fDistY;
				if (CSprite::CalcScreenCoors(entity->GetPosition() + CVector(0.0f, 0.0f, 0.7f), &vecOut, &fDistX, &fDistY, true)) {
					aMessages[NumMessages].m_pos.x = vecOut.x;
					aMessages[NumMessages].m_pos.y = vecOut.y;
					aMessages[NumMessages].m_dist.x = fDistX;
					aMessages[NumMessages].m_dist.y = fDistY;
					aMessages[NumMessages].m_weaponType = WeaponForModel(entity->GetModelIndex());
					aMessages[NumMessages].m_color.red = aWeaponReds[colorId];
					aMessages[NumMessages].m_color.green = aWeaponGreens[colorId];
					aMessages[NumMessages].m_color.blue = aWeaponBlues[colorId];
					aMessages[NumMessages].m_color.alpha = (1.0f - dist / MAXDIST) * 128.0f;
					aMessages[NumMessages].m_bOutOfStock = object->bOutOfStock;
					aMessages[NumMessages].m_quantity = object->m_nBonusValue;
					NumMessages++;
				}
			}
		}

		uint32 model = entity->GetModelIndex();
		CColModel* colModel = entity->GetColModel();
		CVector colLength = colModel->boundingBox.max - colModel->boundingBox.min;

		float scale = (Max(1.f, 1.2f / Max(colLength.x, Max(colLength.y, colLength.z))) - 1.0f) * 0.6f + 1.0f;
		if (model == MI_MINIGUN || model == MI_MINIGUN2)
			scale = 1.2f;

		entity->GetMatrix().SetRotateZOnlyScaled((float)(CTimer::GetTimeInMilliseconds() & 0x7FF) * DEGTORAD(360.0f / 0x800), scale);

		if (doInnerGlow)
			CCoronas::RegisterCorona((uintptr)entity + 1, 126, 69, 121, 255, entity->GetPosition(), 1.2f, 50.0f,
				CCoronas::TYPE_STAR, CCoronas::FLARE_NONE, CCoronas::REFLECTION_ON, CCoronas::LOSCHECK_OFF, CCoronas::STREAK_ON, 0.f, false);
	}
}

void
CPickups::DoMineEffects(CEntity *entity)
{
	const CVector &pos = entity->GetPosition();
	float dist = (TheCamera.GetPosition() - pos).Magnitude();
	const float MAXDIST = 20.0f;

	if (dist < MAXDIST) {
		float s = Sin((float)((CTimer::GetTimeInMilliseconds() + (uintptr)entity) & 0x1FF) * DEGTORAD(360.0f / 0x200));

		int32 red = (MAXDIST - dist) * (0.5f * s + 0.5f) / MAXDIST * 64.0f;
		CShadows::StoreStaticShadow((uintptr)entity, SHADOWTYPE_ADDITIVE, gpShadowExplosionTex, &pos, 2.0f, 0.0f, 0.0f, -2.0f, 0, red, 0, 0, 4.0f, 1.0f, 40.0f,
		                            false, 0.0f);
		CCoronas::RegisterCorona((uintptr)entity, red, 0, 0, 255, pos, 0.6f, 60.0f, CCoronas::TYPE_RING, CCoronas::FLARE_NONE, CCoronas::REFLECTION_OFF, CCoronas::LOSCHECK_OFF, CCoronas::STREAK_OFF, 0.0f);
	}

	entity->GetMatrix().SetRotateZOnly((float)(CTimer::GetTimeInMilliseconds() & 0x3FF) * DEGTORAD(360.0f / 0x400));
}

void
CPickups::DoMoneyEffects(CEntity *entity)
{
	const CVector &pos = entity->GetPosition();
	float dist = (TheCamera.GetPosition() - pos).Magnitude();
	const float MAXDIST = 20.0f;

	if (dist < MAXDIST) {
		float s = Sin((float)((CTimer::GetTimeInMilliseconds() + (uintptr)entity) & 0x3FF) * DEGTORAD(360.0f / 0x400));

		int32 green = (MAXDIST - dist) * (0.2f * s + 0.3f) / MAXDIST * 64.0f;
		CShadows::StoreStaticShadow((uintptr)entity, SHADOWTYPE_ADDITIVE, gpShadowExplosionTex, &pos, 2.0f, 0.0f, 0.0f, -2.0f, 0, 0, green, 0, 4.0f, 1.0f,
		                            40.0f, false, 0.0f);
		CCoronas::RegisterCorona((uintptr)entity, 0, green, 0, 255, pos, 0.4f, 40.0f, CCoronas::TYPE_RING, CCoronas::FLARE_NONE, CCoronas::REFLECTION_OFF, CCoronas::LOSCHECK_OFF, CCoronas::STREAK_OFF, 0.0f);
	}

	entity->GetMatrix().SetRotateZOnly((float)(CTimer::GetTimeInMilliseconds() & 0x7FF) * DEGTORAD(360.0f / 0x800));
}

void
CPickups::DoCollectableEffects(CEntity *entity)
{
	const CVector &pos = entity->GetPosition();
	float dist = (TheCamera.GetPosition() - pos).Magnitude();
	const float MAXDIST = 14.0f;

	if (dist < MAXDIST) {
		float s = Sin((float)((CTimer::GetTimeInMilliseconds() + (uintptr)entity) & 0x7FF) * DEGTORAD(360.0f / 0x800));

		int32 color = (MAXDIST - dist) * (0.5f * s + 0.5f) / MAXDIST * 255.0f;
		CShadows::StoreStaticShadow((uintptr)entity, SHADOWTYPE_ADDITIVE, gpShadowExplosionTex, &pos, 2.0f, 0.0f, 0.0f, -2.0f, 0, color, color, color, 4.0f,
		                            1.0f, 40.0f, false, 0.0f);
		CCoronas::RegisterCorona((uintptr)entity, color, color, color, 255, pos, 0.6f, 40.0f, CCoronas::TYPE_RING, CCoronas::FLARE_NONE, CCoronas::REFLECTION_OFF, CCoronas::LOSCHECK_OFF, CCoronas::STREAK_OFF, 0.0f);
	}

	entity->GetMatrix().SetRotateZOnly((float)(CTimer::GetTimeInMilliseconds() & 0xFFF) * DEGTORAD(360.0f / 0x1000));
}

void
CPickups::RenderPickUpText()
{
	wchar *strToPrint;
	for (int32 i = 0; i < NumMessages; i++) {
		if (aMessages[i].m_quantity <= 39) {
			switch (aMessages[i].m_quantity) // could use some enum maybe
			{
			case 0:
				if (aMessages[i].m_weaponType == WEAPONTYPE_TOTALWEAPONS) { // unreachable code?
					// what is this??
					sprintf(gString, "%d/%d", CWorld::Players[CWorld::PlayerInFocus].m_nCollectedPackages, 2903);
					strToPrint = nil;
				} else {
					if (aMessages[i].m_bOutOfStock)
						strToPrint = TheText.Get("STOCK");
					else {
						sprintf(gString, "$%d", CostOfWeapon[aMessages[i].m_weaponType]);
						AsciiToUnicode(gString, gUString);
						strToPrint = gUString;
					}
				}
				break;
			case 1:
				strToPrint = TheText.Get("SECURI");
				break;
			case 2:
				strToPrint = TheText.Get("MOONBM");
				break;
			case 3:
				strToPrint = TheText.Get("COACH");
				break;
			case 4:
				strToPrint = TheText.Get("FLATBED");
				break;
			case 5:
				strToPrint = TheText.Get("LINERUN");
				break;
			case 6:
				strToPrint = TheText.Get("TRASHM");
				break;
			case 7:
				strToPrint = TheText.Get("PATRIOT");
				break;
			case 8:
				strToPrint = TheText.Get("WHOOPEE");
				break;
			case 9:
				strToPrint = TheText.Get("BLISTA");
				break;
			case 10:
				strToPrint = TheText.Get("MULE");
				break;
			case 11:
				strToPrint = TheText.Get("YANKEE");
				break;
			case 12:
				strToPrint = TheText.Get("BOBCAT");
				break;
			case 13:
				strToPrint = TheText.Get("DODO");
				break;
			case 14:
				strToPrint = TheText.Get("BUS");
				break;
			case 15:
				strToPrint = TheText.Get("RUMPO");
				break;
			case 16:
				strToPrint = TheText.Get("PONY");
				break;
			case 17:
				strToPrint = TheText.Get("SENTINL");
				break;
			case 18:
				strToPrint = TheText.Get("CHEETAH");
				break;
			case 19:
				strToPrint = TheText.Get("BANSHEE");
				break;
			case 20:
				strToPrint = TheText.Get("IDAHO");
				break;
			case 21:
				strToPrint = TheText.Get("INFERNS");
				break;
			case 22:
				strToPrint = TheText.Get("TAXI");
				break;
			case 23:
				strToPrint = TheText.Get("KURUMA");
				break;
			case 24:
				strToPrint = TheText.Get("STRETCH");
				break;
			case 25:
				strToPrint = TheText.Get("PEREN");
				break;
			case 26:
				strToPrint = TheText.Get("STINGER");
				break;
			case 27:
				strToPrint = TheText.Get("MANANA");
				break;
			case 28:
				strToPrint = TheText.Get("LANDSTK");
				break;
			case 29:
				strToPrint = TheText.Get("STALION");
				break;
			case 30:
				strToPrint = TheText.Get("BFINJC");
				break;
			case 31:
				strToPrint = TheText.Get("CABBIE");
				break;
			case 32:
				strToPrint = TheText.Get("ESPERAN");
				break;
			case 33:
				strToPrint = TheText.Get("FIRETRK");
				break;
			case 34:
				strToPrint = TheText.Get("AMBULAN");
				break;
			case 35:
				strToPrint = TheText.Get("ENFORCR");
				break;
			case 36:
				strToPrint = TheText.Get("FBICAR");
				break;
			case 37:
				strToPrint = TheText.Get("RHINO");
				break;
			case 38:
				strToPrint = TheText.Get("BARRCKS");
				break;
			case 39:
				strToPrint = TheText.Get("POLICAR");
				break;
			default:
				break;
			}
		}
		if (strToPrint == nil)
			continue;
		CFont::SetPropOn();
		CFont::SetBackgroundOff();

		const float MAX_SCALE = 1.0f;

		float fScaleY = aMessages[i].m_dist.y / 100.0f;
		if (fScaleY > MAX_SCALE) fScaleY = MAX_SCALE;

		float fScaleX = aMessages[i].m_dist.x / 100.0f;
		if (fScaleX > MAX_SCALE) fScaleX = MAX_SCALE;

		CFont::SetScale(fScaleX, fScaleY);
		CFont::SetCentreOn();
		CFont::SetCentreSize(SCREEN_WIDTH);
		CFont::SetJustifyOff();

		CFont::SetColor(CRGBA(aMessages[i].m_color.red, aMessages[i].m_color.green, aMessages[i].m_color.blue, aMessages[i].m_color.alpha));
		CFont::SetBackGroundOnlyTextOff();
		CFont::SetFontStyle(FONT_STANDARD);
		CFont::PrintString(aMessages[i].m_pos.x, aMessages[i].m_pos.y, strToPrint);
	}
	NumMessages = 0;
}

// --MIAMI: Done
void
CPickups::CreateSomeMoney(CVector pos, int money)
{
	bool found;

	int pickupCount = Min(money / 20 + 1, 7);
	int moneyPerPickup = money / pickupCount;

	for (int i = 0; i < pickupCount; i++) {
		// (CGeneral::GetRandomNumber() % 256) * PI / 128 gives a float up to something TWOPI-ish.
		pos.x += 1.5f * Sin((CGeneral::GetRandomNumber() % 256) * PI / 128);
		pos.y += 1.5f * Cos((CGeneral::GetRandomNumber() % 256) * PI / 128);
		pos.z = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &found) + 0.5f;
		if (found) {
			CPickups::GenerateNewOne(CVector(pos.x, pos.y, pos.z), MI_MONEY, PICKUP_MONEY, moneyPerPickup + (CGeneral::GetRandomNumber() & 3));
		}
	}
}

// --MIAMI: Done
void
CPickups::RemoveAllPickupsOfACertainWeaponGroupWithNoAmmo(eWeaponType weaponType)
{
	uint32 weaponSlot = CWeaponInfo::GetWeaponInfo(weaponType)->m_nWeaponSlot;
	if (weaponSlot >= WEAPONSLOT_SHOTGUN && weaponSlot <= WEAPONSLOT_RIFLE) {
		for (int slot = 0; slot < NUMPICKUPS; slot++) {
			if (aPickUps[slot].m_eType == PICKUP_ONCE || aPickUps[slot].m_eType == PICKUP_ONCE_TIMEOUT || aPickUps[slot].m_eType == PICKUP_ONCE_TIMEOUT_SLOW) {
				if (aPickUps[slot].m_pObject) {
					if (CWeaponInfo::GetWeaponInfo(WeaponForModel(aPickUps[slot].m_pObject->GetModelIndex()))->m_nWeaponSlot == weaponSlot &&
						aPickUps[slot].m_nQuantity == 0) {
						CWorld::Remove(aPickUps[slot].m_pObject);
						delete aPickUps[slot].m_pObject;
						aPickUps[slot].m_bRemoved = true;
						aPickUps[slot].m_pObject = nil;
						aPickUps[slot].m_eType = PICKUP_NONE;
					}
				}
			}
		}
	}
}

void
CPickups::Load(uint8 *buf, uint32 size)
{
INITSAVEBUF

	for (int32 i = 0; i < NUMPICKUPS; i++) {
		aPickUps[i] = ReadSaveBuf<CPickup>(buf);

		if (aPickUps[i].m_eType != PICKUP_NONE && aPickUps[i].m_pObject != nil)
			aPickUps[i].m_pObject = CPools::GetObjectPool()->GetSlot((uintptr)aPickUps[i].m_pObject - 1);
	}

	CollectedPickUpIndex = ReadSaveBuf<uint16>(buf);
	ReadSaveBuf<uint16>(buf);
	NumMessages = 0;

	for (uint16 i = 0; i < NUMCOLLECTEDPICKUPS; i++)
		aPickUpsCollected[i] = ReadSaveBuf<int32>(buf);

VALIDATESAVEBUF(size)
}

void
CPickups::Save(uint8 *buf, uint32 *size)
{
	*size = sizeof(aPickUps) + sizeof(uint16) + sizeof(uint16) + sizeof(aPickUpsCollected);

INITSAVEBUF

	for (int32 i = 0; i < NUMPICKUPS; i++) {
		CPickup *buf_pickup = WriteSaveBuf(buf, aPickUps[i]);
		if (buf_pickup->m_eType != PICKUP_NONE && buf_pickup->m_pObject != nil)
			buf_pickup->m_pObject = (CObject*)(CPools::GetObjectPool()->GetJustIndex(buf_pickup->m_pObject) + 1);
	}

	WriteSaveBuf(buf, CollectedPickUpIndex);
	WriteSaveBuf(buf, (uint16)0); // possibly was NumMessages

	for (uint16 i = 0; i < NUMCOLLECTEDPICKUPS; i++)
		WriteSaveBuf(buf, aPickUpsCollected[i]);

VALIDATESAVEBUF(*size)
}

void
CPacManPickup::Update()
{
}

int32 CollectGameState;
int16 ThingsToCollect;

CPacManPickup CPacManPickups::aPMPickUps[NUMPACMANPICKUPS];
CVector CPacManPickups::LastPickUpCoors;
int32 CPacManPickups::PillsEatenInRace;
bool CPacManPickups::bPMActive;

void
CPacManPickups::Init()
{
}

void
CPacManPickups::Update()
{
}

void
CPacManPickups::GeneratePMPickUps(CVector pos, float scrambleMult, int16 count, uint8 type)
{
}

void
CPacManPickups::GeneratePMPickUpsForRace(int32 race)
{
}

void
CPacManPickups::GenerateOnePMPickUp(CVector pos)
{
}

void
CPacManPickups::Render()
{
}

void
CPacManPickups::ClearPMPickUps()
{
}

void
CPacManPickups::StartPacManRace(int32 race)
{
}

void
CPacManPickups::StartPacManRecord()
{
}

uint32
CPacManPickups::QueryPowerPillsEatenInRace()
{
	return 0;
}

void
CPacManPickups::ResetPowerPillsEatenInRace()
{
}

void
CPacManPickups::CleanUpPacManStuff()
{
}

void
CPacManPickups::StartPacManScramble(CVector pos, float scrambleMult, int16 count)
{
}

uint32
CPacManPickups::QueryPowerPillsCarriedByPlayer()
{
	return 0;
}

void
CPacManPickups::ResetPowerPillsCarriedByPlayer()
{
}
