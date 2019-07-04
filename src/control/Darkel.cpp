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

int32 CDarkel::CalcFade(uint32 time, int32 min, uint32 max) {
	if (time >= min && time <= max) {
		if (time >= min + 500) {
			if (time <= max - 500)
				return -1;
			else
				return 255 * (max - time) / 500;
		}
		else
			return 255 * (time - min) / 500;
	}
	else
		return 0;
}


#if 0
WRAPPER void CDarkel::DrawMessages(void) { EAXJMP(0x420920); }
#else
void CDarkel::DrawMessages()
{
	bool DisplayTimers = false;

	switch (Status) {
	case KILLFRENZY_ONGOING:
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
	Status = KILLFRENZY_INIT;
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

int32 CDarkel::RegisterCarBlownUpByPlayer(eKillFrenzyStatus status)
{
	return 0;
}

void CDarkel::RegisterKillByPlayer(int32 modelid, eWeaponType weapontype, bool flag)
{

	
}

void CDarkel::RegisterKillNotByPlayer()
{
	++CStats::NumberKillFrenziesPassed;
}

void CDarkel::ResetModelsKilledByPlayer()
{
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 8; j++)
			RegisteredKills[i + j] = 0;
	};
}

void CDarkel::ResetOnPlayerDeath()
{
	eWeaponType &EWeaponType = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
	int32 &CurrentWeapon = CWeaponInfo::GetWeaponInfo(FindPlayerPed()->GetWeapon()->m_eWeaponType)->m_nModelId;
	int32 &CurrentDarkelWeapon = CDarkel::WeaponType;
	uint32 &TotalAmmo = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal;

	if (Status == KILLFRENZY_ONGOING) {
		CPopulation::m_AllRandomPedsThisType = -1;
		Status = KILLFRENZY_FAILED;
		TimeOfFrenzyStart = CTimer::GetTimeInMilliseconds();

		if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
			CurrentDarkelWeapon = WEAPONTYPE_UZI;

		if (CurrentDarkelWeapon < WEAPONTYPE_TOTALWEAPONS) {
			FindPlayerPed()->m_bWeaponSlot = InterruptedWeapon;
			TotalAmmo = AmmoInterruptedWeapon;
		}

		if (FindPlayerVehicle()) {
			FindPlayerPed()->RemoveWeaponModel(CurrentWeapon);
			FindPlayerPed()->m_currentWeapon = EWeaponType;
			FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_currentWeapon);
		}
	}
}

#if 0
WRAPPER void CDarkel::StartFrenzy(eWeaponType weaponType, int32 time, int16 kill, int32 modelId0, wchar *text, int32 modelId2, int32 modelId3, int32 modelId4, bool standardSound, bool needHeadShot) { EAXJMP(0x4210E0); }
#else
void CDarkel::StartFrenzy(eWeaponType weaponType, int32 time, int16 kill, int32 modelId0, wchar *text, int32 modelId2, int32 modelId3, int32 modelId4, bool standardSound, bool needHeadShot)
{
	eWeaponType &EWeaponType = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
	uint32 &TotalAmmo = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal;
	uint32 &AmmoInClip = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoInClip;

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
		AmmoInterruptedWeapon = TotalAmmo;
		FindPlayerPed()->GiveWeapon(weaponType, 30000);
		FindPlayerPed()->m_bWeaponSlot = EWeaponType;
		FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_bWeaponSlot);

		if (FindPlayerVehicle()) {
			FindPlayerPed()->m_currentWeapon = EWeaponType;
			if (TotalAmmo <= AmmoInClip)
				AmmoInClip = TotalAmmo;

			FindPlayerPed()->ClearWeaponTarget();
		}
	}
	if (CDarkel::bStandardSoundAndMessages)
		DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_START, 0);
}
#endif

void CDarkel::Update()
{
	eWeaponType &EWeaponType = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_eWeaponType;
	int32 &CurrentWeapon = CWeaponInfo::GetWeaponInfo(FindPlayerPed()->GetWeapon()->m_eWeaponType)->m_nModelId;
	int32 &CurrentDarkelWeapon = CDarkel::WeaponType;
	uint32 &TotalAmmo = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_weapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_currentWeapon].m_nAmmoTotal;

	if (Status == KILLFRENZY_ONGOING) {
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
				CurrentDarkelWeapon = WEAPONTYPE_UZI;

			if (CurrentDarkelWeapon < WEAPONTYPE_TOTALWEAPONS) {
				FindPlayerPed()->m_bWeaponSlot = InterruptedWeapon;
				TotalAmmo = AmmoInterruptedWeapon;
			}

			if (FindPlayerVehicle()) {
				FindPlayerPed()->RemoveWeaponModel(CurrentWeapon);
				FindPlayerPed()->m_currentWeapon = EWeaponType;
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

			FindPlayerPed()->m_pWanted->SetWantedLevel(NOTWANTED);

			if (WeaponType == WEAPONTYPE_UZI_DRIVEBY)
				CurrentDarkelWeapon = WEAPONTYPE_UZI;

			if (CurrentDarkelWeapon < WEAPONTYPE_TOTALWEAPONS) {
				FindPlayerPed()->m_bWeaponSlot = InterruptedWeapon;
				TotalAmmo = AmmoInterruptedWeapon;
			}

			if (FindPlayerVehicle()) {
				FindPlayerPed()->RemoveWeaponModel(CurrentWeapon);
				FindPlayerPed()->m_currentWeapon = EWeaponType;
				FindPlayerPed()->MakeChangesForNewWeapon(FindPlayerPed()->m_currentWeapon);
			}

			if (bStandardSoundAndMessages)
				DMAudio.PlayFrontEndSound(SOUND_RAMPAGE_PASSED, 0);
		}
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