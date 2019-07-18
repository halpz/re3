#include "common.h"
#include "patcher.h"
#include "main.h"
#include "Darkel.h"
#include "Timer.h"
#include "DMAudio.h"
#include "Population.h"
#include "Weapon.h"
#include "World.h"
#include "PlayerPed.h"
#include "Stats.h"
#include "Font.h"
#include "Text.h"

int32 &CDarkel::TimeLimit = *(int32*)0x885BAC;
int32 &CDarkel::PreviousTime = *(int32*)0x885B00;
int32 &CDarkel::TimeOfFrenzyStart = *(int32*)0x9430D8;
int32 &CDarkel::WeaponType = *(int32*)0x9430F0;
int32 &CDarkel::AmmoInterruptedWeapon = *(int32*)0x8E29C8;
int32 &CDarkel::KillsNeeded = *(int32*)0x8F1AB8;
int8 &CDarkel::InterruptedWeapon = *(int8*)0x95CD60;
int8 &CDarkel::bStandardSoundAndMessages = *(int8*)0x95CDB6;
int8 &CDarkel::bNeedHeadShot = *(int8*)0x95CDCA;
int8 &CDarkel::bProperKillFrenzy = *(int8*)0x95CD98;
eKillFrenzyStatus &CDarkel::Status = *(eKillFrenzyStatus*)0x95CCB4;
int16 *CDarkel::RegisteredKills = (int16*)0x6EDBE0;
int32 &CDarkel::ModelToKill = *(int32*)0x8F2C78;
int32 &CDarkel::ModelToKill2 = *(int32*)0x885B40;
int32 &CDarkel::ModelToKill3 = *(int32*)0x885B3C;
int32 &CDarkel::ModelToKill4 = *(int32*)0x885B34;
wchar *CDarkel::pStartMessage = (wchar*)0x8F2C08;

int32 CDarkel::CalcFade(uint32 time, int32 start, uint32 end) {
	if (time >= start && time <= end) {
		if (time >= start + 500) {
			if (time <= end - 500)
				return 255;
			else
				return 255 * (end - time) / 500;
		}
		else
			return 255 * (time - start) / 500;
	}
	else
		return 0;
}

// This function has been cleaned up from unused stuff.
#if 0
WRAPPER void CDarkel::DrawMessages(void) { EAXJMP(0x420920); }
#else
void CDarkel::DrawMessages()
{
	bool DisplayTimers = false;

	switch (Status) {
	case KILLFRENZY_ONGOING:
		assert(pStartMessage != nil);
		DisplayTimers = true;
		break;
	case KILLFRENZY_PASSED:
	case KILLFRENZY_FAILED:
		DisplayTimers = false;
		break;
	};

	if (DisplayTimers) {
		CFont::SetPropOn();
		CFont::SetBackgroundOff();
		CFont::SetBackGroundOnlyTextOn();
		CFont::SetAlignment(ALIGN_RIGHT);
		CFont::SetRightJustifyWrap(-SCREEN_WIDTH);
		CFont::SetFontStyle(FONT_HEADING);
		CFont::SetScale(SCREEN_SCALE_X(0.8f), SCREEN_SCALE_Y(1.35f));

		float AlignToHUD = SCREEN_SCALE_X(-10.0f);
		int32 a = (TimeLimit - (CTimer::GetTimeInMilliseconds() - TimeOfFrenzyStart));
		if (CTimer::GetFrameCounter() & 8 || a > 4000) {
			sprintf(gString, "%d:%02d", a / 60000, a % 60000 / 1000);
			AsciiToUnicode(gString, gUString);
			CFont::SetColor(CRGBA(0, 0, 0, 255));
			CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(25.0f) + AlignToHUD, SCREEN_SCALE_Y(112.0f), gUString);

			CFont::SetColor(CRGBA(150, 100, 255, 255));
			CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(27.0f) + AlignToHUD, SCREEN_SCALE_Y(110.0f), gUString);
		}

		if (KillsNeeded <= 0)
			KillsNeeded = 0;

		sprintf((char *)gString, "%d", KillsNeeded);
		AsciiToUnicode(gString, gUString);

		CFont::SetColor(CRGBA(0, 0, 0, 255));
		CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(25.0f) + AlignToHUD, SCREEN_SCALE_Y(134.0f), gUString);

		CFont::SetColor(CRGBA(255, 128, 128, 255));
		CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(27.0f) + AlignToHUD, SCREEN_SCALE_Y(132.0f), gUString);
	}
}
#endif

void CDarkel::Init()
{
	Status = KILLFRENZY_NONE;
}

int16 CDarkel::QueryModelsKilledByPlayer(int32 modelId)
{
	return RegisteredKills[modelId];
}


bool CDarkel::FrenzyOnGoing()
{
	return Status == KILLFRENZY_ONGOING;
}


eKillFrenzyStatus CDarkel::ReadStatus()
{
	return Status;
}

#if 1
WRAPPER void CDarkel::RegisterCarBlownUpByPlayer(CVehicle *vehicle) { EAXJMP(0x421070); }
#else
int32 CDarkel::RegisterCarBlownUpByPlayer(CVehicle *vehicle)
{
	return 0;
}
#endif

#if 1
WRAPPER void CDarkel::RegisterKillByPlayer(CPed *victim, eWeaponType weapontype, bool headshot) { EAXJMP(0x420F60); }
#else
void CDarkel::RegisterKillByPlayer(CPed *victim, eWeaponType weapontype, bool headshot)
{

	
}
#endif

void CDarkel::RegisterKillNotByPlayer(CPed* victim, eWeaponType weapontype)
{
	++CStats::NumberKillFrenziesPassed;
}

void CDarkel::ResetModelsKilledByPlayer()
{
	for (int i = 0; i < 200; i++)
		RegisteredKills[i] = 0;
}

#if 0
WRAPPER void CDarkel::ResetOnPlayerDeath() { EAXJMP(0x420E70); }
#else
void CDarkel::ResetOnPlayerDeath()
{
	if (Status != KILLFRENZY_ONGOING)
		return;

	CPopulation::m_AllRandomPedsThisType = -1;
	Status = KILLFRENZY_FAILED;
	TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

	if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
		WeaponType = WEAPONTYPE_UZI;

	if (WeaponType < WEAPONTYPE_TOTALWEAPONS) {
		FindPlayerPed()->m_bWeaponSlot = InterruptedWeapon;
		CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal = AmmoInterruptedWeapon;
	}

	if (FindPlayerVehicle()) {
		FindPlayerPed()->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(FindPlayerPed()->GetWeapon()->m_eWeaponType)->m_nModelId);
		FindPlayerPed()->m_currentWeapon = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
		FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_currentWeapon);
	}


	CPopulation::m_AllRandomPedsThisType = -1;
	Status = KILLFRENZY_FAILED;
	TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

	if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
		WeaponType = WEAPONTYPE_UZI;

	if (WeaponType < WEAPONTYPE_TOTALWEAPONS) {
		FindPlayerPed()->m_bWeaponSlot = InterruptedWeapon;
		CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal = AmmoInterruptedWeapon;
	}

	if (FindPlayerVehicle()) {
		FindPlayerPed()->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(FindPlayerPed()->GetWeapon()->m_eWeaponType)->m_nModelId);
		FindPlayerPed()->m_currentWeapon = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
		FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_currentWeapon);
	}
}
#endif

#if 0
WRAPPER void CDarkel::StartFrenzy(eWeaponType weaponType, int32 time, int16 kill, int32 modelId0, wchar *text, int32 modelId2, int32 modelId3, int32 modelId4, bool standardSound, bool needHeadShot) { EAXJMP(0x4210E0); }
#else
void CDarkel::StartFrenzy(eWeaponType weaponType, int32 time, int16 kill, int32 modelId0, wchar *text, int32 modelId2, int32 modelId3, int32 modelId4, bool standardSound, bool needHeadShot)
{
	if (weaponType == WEAPONTYPE_UZI_DRIVEBY)
		weaponType = WEAPONTYPE_UZI;

	WeaponType = weaponType;
	Status = KILLFRENZY_ONGOING;
	KillsNeeded = kill;
	ModelToKill = modelId0;
	ModelToKill2 = modelId2;
	ModelToKill3 = modelId3;
	ModelToKill4 = modelId4;
	pStartMessage = text;

	if (text == TheText.Get("PAGE_00")) {
		CDarkel::bProperKillFrenzy = 1;
		CDarkel::pStartMessage = 0;
	}
	else
		bProperKillFrenzy = 0;
	
	bStandardSoundAndMessages = standardSound;
	bNeedHeadShot = needHeadShot;
	TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();
	TimeLimit = time;
	PreviousTime = time / 1000;

	if (weaponType < WEAPONTYPE_TOTALWEAPONS) {
		InterruptedWeapon = FindPlayerPed()->m_currentWeapon;
		FindPlayerPed()->GiveWeapon(weaponType, 0);
		AmmoInterruptedWeapon = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal;
		FindPlayerPed()->GiveWeapon(weaponType, 30000);
		FindPlayerPed()->m_bWeaponSlot = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
		FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_bWeaponSlot);

		if (FindPlayerVehicle()) {
			FindPlayerPed()->m_currentWeapon = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
			if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal <= CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoInClip)
				CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoInClip = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal;

			FindPlayerPed()->ClearWeaponTarget();
		}
	}
	if (CDarkel::bStandardSoundAndMessages)
		DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_START, 0);
}
#endif

void CDarkel::Update()
{
	if (Status != KILLFRENZY_ONGOING)
		return;

	int32 FrameTime = TimeLimit - (CTimer::GetTimeInMilliseconds() - TimeOfFrenzyStart);
	if ((TimeLimit - (CTimer::GetTimeInMilliseconds() - TimeOfFrenzyStart)) > 0 || TimeLimit < 0) {
		DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_ONGOING, FrameTime);

		int32 PrevTime = FrameTime / 1000;

		if (PrevTime != PreviousTime) {
			if (PreviousTime < 12)
				DMAudio.PlayFrontEndSound(SOUND_CLOCK_TICK, PrevTime);
			PreviousTime = PrevTime;
		}

	}
	else {
		CPopulation::m_AllRandomPedsThisType = -1;
		Status = KILLFRENZY_FAILED;
		TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

		if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
			WeaponType = WEAPONTYPE_UZI;

		if (WeaponType < WEAPONTYPE_TOTALWEAPONS) {
			FindPlayerPed()->m_bWeaponSlot = InterruptedWeapon;
			CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal = AmmoInterruptedWeapon;
		}

		if (FindPlayerVehicle()) {
			FindPlayerPed()->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(FindPlayerPed()->GetWeapon()->m_eWeaponType)->m_nModelId);
			FindPlayerPed()->m_currentWeapon = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
			FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_currentWeapon);
		}

		if (bStandardSoundAndMessages)
			DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_FAILED, 0);
	}

	if (KillsNeeded <= 0) {
		CPopulation::m_AllRandomPedsThisType = -1;
		Status = KILLFRENZY_PASSED;

		if (bProperKillFrenzy)
			CStats::AnotherKillFrenzyPassed();

		TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

		FindPlayerPed()->m_pWanted->SetWantedLevel(0);

		if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
			WeaponType = WEAPONTYPE_UZI;

		if (WeaponType < WEAPONTYPE_TOTALWEAPONS) {
			FindPlayerPed()->m_bWeaponSlot = InterruptedWeapon;
			CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal = AmmoInterruptedWeapon;
		}

		if (FindPlayerVehicle()) {
			FindPlayerPed()->RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(FindPlayerPed()->GetWeapon()->m_eWeaponType)->m_nModelId);
			FindPlayerPed()->m_currentWeapon = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
			FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_currentWeapon);
		}

		if (bStandardSoundAndMessages)
			DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_PASSED, 0);
	}
}

STARTPATCHES
	/*InjectHook(0x421380, CDarkel::CalcFade, PATCH_JUMP);
	InjectHook(0x420920, CDarkel::DrawMessages, PATCH_JUMP);
	InjectHook(0x420E60, CDarkel::FrenzyOnGoing, PATCH_JUMP);
	InjectHook(0x420650, CDarkel::Init, PATCH_JUMP);
	InjectHook(0x421370, CDarkel::QueryModelsKilledByPlayer, PATCH_JUMP);
	InjectHook(0x420E50, CDarkel::ReadStatus, PATCH_JUMP);
	InjectHook(0x421070, CDarkel::RegisterCarBlownUpByPlayer, PATCH_JUMP);
	InjectHook(0x420F60, CDarkel::RegisterKillByPlayer, PATCH_JUMP);
	InjectHook(0x421060, CDarkel::RegisterKillNotByPlayer, PATCH_JUMP);
	InjectHook(0x421310, CDarkel::ResetModelsKilledByPlayer, PATCH_JUMP);
	InjectHook(0x420E70, CDarkel::ResetOnPlayerDeath, PATCH_JUMP);
	InjectHook(0x4210E0, CDarkel::StartFrenzy, PATCH_JUMP);
	InjectHook(0x420660, CDarkel::Update, PATCH_JUMP);*/
ENDPATCHES