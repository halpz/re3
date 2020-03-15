#include "common.h"
#include "patcher.h"
#include "World.h"
#include "PlayerPed.h"
#include "CopPed.h"
#include "ModelIndices.h"
#include "Vehicle.h"
#include "RpAnimBlend.h"
#include "General.h"

WRAPPER void CCopPed::ProcessControl() { EAXJMP(0x4C1400);  }

CCopPed::CCopPed(eCopType copType) : CPed(PEDTYPE_COP)
{
	m_nCopType = copType;
	switch (copType) {
	case COP_STREET:
		SetModelIndex(MI_COP);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		m_currentWeapon = WEAPONTYPE_UNARMED;
		m_fArmour = 0.0f;
		m_wepSkills = 208; /* TODO: what is this? seems unused */
		m_wepAccuracy = 60;
		break;
	case COP_FBI:
		SetModelIndex(MI_FBI);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		GiveWeapon(WEAPONTYPE_AK47, 1000);
		SetCurrentWeapon(WEAPONTYPE_AK47);
		m_fArmour = 100.0f;
		m_wepSkills = 176; /* TODO: what is this? seems unused */
		m_wepAccuracy = 76;
		break;
	case COP_SWAT:
		SetModelIndex(MI_SWAT);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		GiveWeapon(WEAPONTYPE_UZI, 1000);
		SetCurrentWeapon(WEAPONTYPE_UZI);
		m_fArmour = 50.0f;
		m_wepSkills = 32; /* TODO: what is this? seems unused */
		m_wepAccuracy = 64;
		break;
	case COP_ARMY:
		SetModelIndex(MI_ARMY);
		GiveWeapon(WEAPONTYPE_COLT45, 1000);
		GiveWeapon(WEAPONTYPE_M16, 1000);
		GiveWeapon(WEAPONTYPE_GRENADE, 10);
		SetCurrentWeapon(WEAPONTYPE_M16);
		m_fArmour = 100.0f;
		m_wepSkills = 32; /* TODO: what is this? seems unused */
		m_wepAccuracy = 84;
		break;
	default:
		break;
	}
	m_bIsInPursuit = false;
	field_1350 = 1;
	m_bIsDisabledCop = false;
	field_1356 = 0;
	m_attackTimer = 0;
	field_1351 = 0;
	m_bZoneDisabledButClose = false;
	m_bZoneDisabled = false;
	field_1364 = -1;
	m_pPointGunAt = nil;
}

CCopPed::~CCopPed()
{
	ClearPursuit();
}

// Parameter should always be CPlayerPed, but it seems they considered making civilians arrestable at some point
void
CCopPed::SetArrestPlayer(CPed *player)
{
	if (!IsPedInControl() || !player)
		return;

	switch (m_nCopType) {
		case COP_FBI:
			Say(SOUND_PED_ARREST_FBI);
			break;
		case COP_SWAT:
			Say(SOUND_PED_ARREST_SWAT);
			break;
		default:
			Say(SOUND_PED_ARREST_COP);
			break;
	}
	if (player->EnteringCar()) {
		if (CTimer::GetTimeInMilliseconds() > m_nPedStateTimer)
			return;

		// why?
		player->bGonnaKillTheCarJacker = true;

		// Genius
		FindPlayerPed()->m_bCanBeDamaged = false;
		((CPlayerPed*)player)->m_pArrestingCop = this;
		this->RegisterReference((CEntity**) &((CPlayerPed*)player)->m_pArrestingCop);

	} else if (player->m_nPedState != PED_DIE && player->m_nPedState != PED_DEAD && player->m_nPedState != PED_ARRESTED) {
		player->m_nLastPedState = player->m_nPedState;
		player->m_nPedState = PED_ARRESTED;

		FindPlayerPed()->m_bCanBeDamaged = false;
		((CPlayerPed*)player)->m_pArrestingCop = this;
		this->RegisterReference((CEntity**) &((CPlayerPed*)player)->m_pArrestingCop);
	}

	m_nPedState = PED_ARREST_PLAYER;
	SetObjective(OBJECTIVE_NONE);
	m_prevObjective = OBJECTIVE_NONE;
	bIsPointingGunAt = false;
	m_pSeekTarget = player;
	m_pSeekTarget->RegisterReference((CEntity**) &m_pSeekTarget);
	SetCurrentWeapon(WEAPONTYPE_COLT45);
	if (player->InVehicle()) {
		player->m_pMyVehicle->m_nNumGettingIn = 0;
		player->m_pMyVehicle->m_nGettingInFlags = 0;
		player->m_pMyVehicle->bIsHandbrakeOn = true;
		player->m_pMyVehicle->m_status = STATUS_PLAYER_DISABLED;
	}
	if (GetWeapon()->m_eWeaponType == WEAPONTYPE_UNARMED)
		SetCurrentWeapon(WEAPONTYPE_COLT45);
}

void
CCopPed::ClearPursuit(void)
{
	CPlayerPed *player = FindPlayerPed();
	if (!player)
		return;

	CWanted *wanted = player->m_pWanted;
	int ourCopId = 0;
	bool foundMyself = false;
	int biggestCopId = 0;
	if (!m_bIsInPursuit)
		return;

	m_bIsInPursuit = false;
	for (int i = 0; i < max(wanted->m_MaxCops, wanted->m_CurrentCops); ++i)  {
		if (!foundMyself && wanted->m_pCops[i] == this) {
			wanted->m_pCops[i] = nil;
			--wanted->m_CurrentCops;
			foundMyself = true;
			ourCopId = i;
			biggestCopId = i;
		} else {
			if (wanted->m_pCops[i])
				biggestCopId = i;
		}
	}
	if (foundMyself && biggestCopId > ourCopId) {
		wanted->m_pCops[ourCopId] = wanted->m_pCops[biggestCopId];
		wanted->m_pCops[biggestCopId] = nil;
	}
	m_objective = OBJECTIVE_NONE;
	m_prevObjective = OBJECTIVE_NONE;
	m_nLastPedState = PED_NONE;
	bIsRunning = false;
	bNotAllowedToDuck = false;
	bKindaStayInSamePlace = false;
	m_bZoneDisabledButClose = false;
	m_bZoneDisabled = false;
	ClearObjective();
	if (IsPedInControl()) {
		if (!m_pMyVehicle || wanted->m_nWantedLevel != 0)  {
			if (m_pMyVehicle && (m_pMyVehicle->GetPosition() - GetPosition()).MagnitudeSqr() < sq(5.0f)) {
				m_nLastPedState = PED_IDLE;
				SetSeek((CEntity*)m_pMyVehicle, 2.5f);
			} else {
				m_nLastPedState = PED_WANDER_PATH;
				SetFindPathAndFlee(FindPlayerPed()->GetPosition(), 10000, true);
			}
		} else {
			SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, m_pMyVehicle);
		}
	}
}

// TO-DO: m_MaxCops in for loop may be a bug, check it out after CopAI
void
CCopPed::SetPursuit(bool iMayAlreadyBeInPursuit)
{
	CWanted *wanted = FindPlayerPed()->m_pWanted;
	if (m_bIsInPursuit || !IsPedInControl())
		return;

	if (wanted->m_CurrentCops < wanted->m_MaxCops || iMayAlreadyBeInPursuit) {
		for (int i = 0; i < wanted->m_MaxCops; ++i) {
			if (!wanted->m_pCops[i]) {
				m_bIsInPursuit = true;
				++wanted->m_CurrentCops;
				wanted->m_pCops[i] = this;
				break;
			}
		}
		if (m_bIsInPursuit) {
			ClearObjective();
			m_prevObjective = OBJECTIVE_NONE;
			SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, FindPlayerPed());
			SetObjectiveTimer(0);
			bNotAllowedToDuck = true;
			bIsRunning = true;
			m_bZoneDisabledButClose = false;
		}
	}
}

void
CCopPed::ArrestPlayer(void)
{
	m_pVehicleAnim = nil;
	CPed *suspect = (CPed*)m_pSeekTarget;
	if (suspect) {
		if (suspect->CanSetPedState())
			suspect->m_nPedState = PED_ARRESTED;

		if (suspect->bInVehicle && m_pMyVehicle && suspect->m_pMyVehicle == m_pMyVehicle) {

			// BUG? I will never understand why they used LINE_UP_TO_CAR_2...
			LineUpPedWithCar(LINE_UP_TO_CAR_2);
		}

		if (suspect && (suspect->m_nPedState == PED_ARRESTED || suspect->DyingOrDead() || suspect->EnteringCar())) {

			CAnimBlendAssociation *arrestAssoc = RpAnimBlendClumpGetAssociation(GetClump(), ANIM_ARREST_GUN);
			if (!arrestAssoc || arrestAssoc->blendDelta < 0.0f)
				CAnimManager::BlendAnimation(GetClump(), ASSOCGRP_STD, ANIM_ARREST_GUN, 4.0f);

			CVector suspMidPos;
			suspect->m_pedIK.GetComponentPosition((RwV3d*)suspMidPos, PED_MID);
			m_fRotationDest = CGeneral::GetRadianAngleBetweenPoints(suspMidPos.x, suspMidPos.y,
				GetPosition().x, GetPosition().y);

			m_fRotationCur = m_fRotationDest;
			SetOrientation(0.0f, 0.0f, m_fRotationCur);
		} else {
			ClearPursuit();
		}
	} else {
		ClearPursuit();
	}
}

void
CCopPed::ScanForCrimes(void)
{
	CVehicle *playerVeh = FindPlayerVehicle();

	// Look for car alarms
	if (playerVeh && playerVeh->IsCar()) {
		if (playerVeh->IsAlarmOn()) {
			if ((playerVeh->GetPosition() - GetPosition()).MagnitudeSqr() < sq(20.0f))
				FindPlayerPed()->SetWantedLevelNoDrop(1);
		}
	}

	// Look for stolen cop cars (it was broken until now)
	if (!m_bIsInPursuit) {
		CPlayerPed *player = FindPlayerPed();
#ifdef FIX_BUGS
		if ((player->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || player->m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER)
#else
		if ((m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER)
#endif
			&& player->m_pWanted->m_nWantedLevel == 0 && player->m_pMyVehicle) {

			if (player->m_pMyVehicle->bIsLawEnforcer)
				player->SetWantedLevelNoDrop(1);
		}
	}
}

class CCopPed_ : public CCopPed
{
public:
	CCopPed *ctor(eCopType type) { return ::new (this) CCopPed(type); };
	void dtor(void) { CCopPed::~CCopPed(); }
};

STARTPATCHES
	InjectHook(0x4C11B0, &CCopPed_::ctor, PATCH_JUMP);
	InjectHook(0x4C13E0, &CCopPed_::dtor, PATCH_JUMP);
	InjectHook(0x4C28C0, &CCopPed::ClearPursuit, PATCH_JUMP);
	InjectHook(0x4C2B00, &CCopPed::SetArrestPlayer, PATCH_JUMP);
	InjectHook(0x4C27D0, &CCopPed::SetPursuit, PATCH_JUMP);
	InjectHook(0x4C2C90, &CCopPed::ArrestPlayer, PATCH_JUMP);
	InjectHook(0x4C26A0, &CCopPed::ScanForCrimes, PATCH_JUMP);
ENDPATCHES
