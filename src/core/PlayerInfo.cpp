#include "common.h"
#include "patcher.h"
#include "PlayerPed.h"
#include "PlayerInfo.h"
#include "Frontend.h"
#include "PlayerSkin.h"
#include "Darkel.h"
#include "Messages.h"
#include "Text.h"
#include "Stats.h"
#include "Remote.h"
#include "World.h"
#include "Replay.h"
#include "Pad.h"
#include "ProjectileInfo.h"
#include "Explosion.h"
#include "Script.h"
#include "Vehicle.h"
#include "HandlingMgr.h"
#include "General.h"
#include "main.h"
#include "SpecialFX.h"

WRAPPER void CPlayerInfo::Process(void) { EAXJMP(0x49FD30); }

void
CPlayerInfo::SetPlayerSkin(char *skin)
{
	strncpy(m_aSkinName, skin, 32);
	LoadPlayerSkin();
}

CVector&
CPlayerInfo::GetPos()
{
	if (m_pPed->InVehicle())
		return m_pPed->m_pMyVehicle->GetPosition();
	return m_pPed->GetPosition();
}

void
CPlayerInfo::LoadPlayerSkin()
{
	DeletePlayerSkin();

	m_pSkinTexture = CPlayerSkin::GetSkinTexture(m_aSkinName);
	if (!m_pSkinTexture)
		m_pSkinTexture = CPlayerSkin::GetSkinTexture(DEFAULT_SKIN_NAME);
}

void
CPlayerInfo::DeletePlayerSkin()
{
	if (m_pSkinTexture) {
		RwTextureDestroy(m_pSkinTexture);
		m_pSkinTexture = nil;
	}
}

void
CPlayerInfo::KillPlayer()
{
	if (m_WBState != WBSTATE_PLAYING) return;

	m_WBState = WBSTATE_WASTED;
	m_nWBTime = CTimer::GetTimeInMilliseconds();
	CDarkel::ResetOnPlayerDeath();
	CMessages::AddBigMessage(TheText.Get("DEAD"), 4000, 2);
	CStats::TimesDied++;
}

void
CPlayerInfo::ArrestPlayer()
{
	if (m_WBState != WBSTATE_PLAYING) return;

	m_WBState = WBSTATE_BUSTED;
	m_nWBTime = CTimer::GetTimeInMilliseconds();
	CDarkel::ResetOnPlayerDeath();
	CMessages::AddBigMessage(TheText.Get("BUSTED"), 5000, 2);
	CStats::TimesArrested++;
}

bool
CPlayerInfo::IsPlayerInRemoteMode()
{
	return m_pRemoteVehicle || m_bInRemoteMode;
}

void
CPlayerInfo::PlayerFailedCriticalMission()
{
	if (m_WBState != WBSTATE_PLAYING)
		return;
	m_WBState = WBSTATE_FAILED_CRITICAL_MISSION;
	m_nWBTime = CTimer::GetTimeInMilliseconds();
	CDarkel::ResetOnPlayerDeath();
}

void
CPlayerInfo::Clear(void)
{
	m_pPed = nil;
	m_pRemoteVehicle = nil;
	if (m_pVehicleEx) {
		m_pVehicleEx->bUsingSpecialColModel = false;
		m_pVehicleEx = nil;
	}
	m_nVisibleMoney = 0;
	m_nMoney = m_nVisibleMoney;
	m_WBState = WBSTATE_PLAYING;
	m_nWBTime = 0;
	m_nTrafficMultiplier = 0;
	m_fRoadDensity = 1.0f;
	m_bInRemoteMode = false;
	m_bSwitchTaxi = false;
	m_nSwitchTaxiTime = 0;
	m_nCollectedPackages = 0;
	m_nTotalPackages = 3;
	m_nTimeLastHealthLoss = 0;
	m_nTimeLastArmourLoss = 0;
	m_nNextSexFrequencyUpdateTime = 0;
	m_nNextSexMoneyUpdateTime = 0;
	m_nSexFrequency = 0;
	m_pHooker = nil;
	m_nTimeTankShotGun = 0;
	field_248 = 0;
	m_nUpsideDownCounter = 0;
	m_bInfiniteSprint = false;
	m_bFastReload = false;
	m_bGetOutOfJailFree = false;
	m_bGetOutOfHospitalFree = false;
	m_nPreviousTimeRewardedForExplosion = 0;
	m_nExplosionsSinceLastReward = 0;
}

void
CPlayerInfo::BlowUpRCBuggy(void)
{
	if (!m_pRemoteVehicle || m_pRemoteVehicle->bRemoveFromWorld)
		return;

	CRemote::TakeRemoteControlledCarFromPlayer();
	m_pRemoteVehicle->BlowUpCar(FindPlayerPed());
}

void
CPlayerInfo::CancelPlayerEnteringCars(CVehicle *car)
{
	if (!car || car == m_pPed->m_pMyVehicle) {
		if (m_pPed->m_nPedState == PED_CARJACK || m_pPed->m_nPedState == PED_ENTER_CAR)
			m_pPed->QuitEnteringCar();
	}
	if (m_pPed->m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER || m_pPed->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER)
		m_pPed->ClearObjective();
}

void
CPlayerInfo::MakePlayerSafe(bool toggle)
{
	if (toggle) {
		CTheScripts::CountdownToMakePlayerUnsafe = 0;
		m_pPed->m_pWanted->m_bIgnoredByEveryone = true;
		CWorld::StopAllLawEnforcersInTheirTracks();
		CPad::GetPad(0)->DisablePlayerControls |= PLAYERCONTROL_DISABLED_20;
		CPad::StopPadsShaking();
		m_pPed->bBulletProof = true;
		m_pPed->bFireProof = true;
		m_pPed->bCollisionProof = true;
		m_pPed->bMeleeProof = true;
		m_pPed->bOnlyDamagedByPlayer = true;
		m_pPed->bExplosionProof = true;
		m_pPed->m_bCanBeDamaged = false;
		((CPlayerPed*)m_pPed)->ClearAdrenaline();
		CancelPlayerEnteringCars(false);
		gFireManager.ExtinguishPoint(GetPos(), 4000.0f);
		CExplosion::RemoveAllExplosionsInArea(GetPos(), 4000.0f);
		CProjectileInfo::RemoveAllProjectiles();
		CWorld::SetAllCarsCanBeDamaged(false);
		CWorld::ExtinguishAllCarFiresInArea(GetPos(), 4000.0f);
		CReplay::DisableReplays();

	} else if (!CGame::playingIntro && !CTheScripts::CountdownToMakePlayerUnsafe) {
		m_pPed->m_pWanted->m_bIgnoredByEveryone = false;
		CPad::GetPad(0)->DisablePlayerControls &= ~PLAYERCONTROL_DISABLED_20;
		m_pPed->bBulletProof = false;
		m_pPed->bFireProof = false;
		m_pPed->bCollisionProof = false;
		m_pPed->bMeleeProof = false;
		m_pPed->bOnlyDamagedByPlayer = false;
		m_pPed->bExplosionProof = false;
		m_pPed->m_bCanBeDamaged = true;
		CWorld::SetAllCarsCanBeDamaged(true);
		CReplay::EnableReplays();
	}
}

bool
CPlayerInfo::IsRestartingAfterDeath()
{
	return m_WBState == WBSTATE_WASTED;
}

bool
CPlayerInfo::IsRestartingAfterArrest()
{
	return m_WBState == WBSTATE_BUSTED;
}

// lastClosestness is passed to other calls of this function
void
CPlayerInfo::EvaluateCarPosition(CEntity *carToTest, CPed *player, float carBoundCentrePedDist, float *lastClosestness, CVehicle **closestCarOutput)
{
	// This dist used for determining the angle to face
	CVector2D dist(carToTest->GetPosition() - player->GetPosition());
	float neededTurn = CGeneral::GetATanOfXY(player->GetForward().x, player->GetForward().y) - CGeneral::GetATanOfXY(dist.x, dist.y);
	while (neededTurn >= PI) {
		neededTurn -= 2 * PI;
	}

	while (neededTurn < -PI) {
		neededTurn += 2 * PI;
	}

	// This dist used for evaluating cars' distances, weird...
	// Accounts inverted needed turn (or needed turn in long way) and car dist.
	float closestness = (1.0f - Abs(neededTurn) / TWOPI) * (10.0f - carBoundCentrePedDist);
	if (closestness > *lastClosestness) {
		*lastClosestness = closestness;
		*closestCarOutput = (CVehicle*)carToTest;
	}
}

// There is something unfinished in here... Sadly all IDBs we have have it unfinished.
void
CPlayerInfo::AwardMoneyForExplosion(CVehicle *wreckedCar)
{
	if (CTimer::GetTimeInMilliseconds() - m_nPreviousTimeRewardedForExplosion < 6000)
		++m_nExplosionsSinceLastReward;
	else
		m_nExplosionsSinceLastReward = 1;

	m_nPreviousTimeRewardedForExplosion = CTimer::GetTimeInMilliseconds();
	int award = wreckedCar->pHandling->nMonetaryValue * 0.002f;
	sprintf(gString, "$%d", award);
#ifdef MONEY_MESSAGES
	// This line is a leftover from PS2, I don't know what it was meant to be.
	// CVector sth(TheCamera.GetPosition() * 4.0f);

	CMoneyMessages::RegisterOne(wreckedCar->GetPosition() + CVector(0.0f, 0.0f, 2.0f), gString, 0, 255, 0, 2.0f, 0.5f);
#endif
	CWorld::Players[CWorld::PlayerInFocus].m_nMoney += award;

	for (int i = m_nExplosionsSinceLastReward; i > 1; --i) {
		CGeneral::GetRandomNumber();
		CWorld::Players[CWorld::PlayerInFocus].m_nMoney += award;
	}
}

void
CPlayerInfo::SavePlayerInfo(uint8 *buf, uint32 *size)
{
	// Interesting
	*size = sizeof(CPlayerInfo);

INITSAVEBUF
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nMoney);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_WBState);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nWBTime);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nTrafficMultiplier);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_fRoadDensity);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nVisibleMoney);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nCollectedPackages);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nTotalPackages);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bInfiniteSprint);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bFastReload);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfJailFree);
	WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfHospitalFree);
	for (int i = 0; i < sizeof(CWorld::Players[CWorld::PlayerInFocus].m_aPlayerName); i++) {
		WriteSaveBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_aPlayerName[i]);
	}
// Save struct is different
// VALIDATESAVEBUF(*size)
}

void
CPlayerInfo::LoadPlayerInfo(uint8 *buf, uint32 size)
{
INITSAVEBUF
	CWorld::Players[CWorld::PlayerInFocus].m_nMoney = ReadSaveBuf<uint32>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_WBState = ReadSaveBuf<int8>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_nWBTime = ReadSaveBuf<uint32>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_nTrafficMultiplier = ReadSaveBuf<int16>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_fRoadDensity = ReadSaveBuf<float>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_nVisibleMoney = ReadSaveBuf<int32>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_nCollectedPackages = ReadSaveBuf<int32>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_nTotalPackages = ReadSaveBuf<int32>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_bInfiniteSprint = ReadSaveBuf<bool>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_bFastReload = ReadSaveBuf<bool>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfJailFree = ReadSaveBuf<bool>(buf);
	CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfHospitalFree = ReadSaveBuf<bool>(buf);
	for (int i = 0; i < sizeof(CWorld::Players[CWorld::PlayerInFocus].m_aPlayerName); i++) {
		CWorld::Players[CWorld::PlayerInFocus].m_aPlayerName[i] = ReadSaveBuf<char>(buf);
	}
// Save struct is different
// VALIDATESAVEBUF(size)
}

STARTPATCHES
	InjectHook(0x4B5DC0, &CPlayerInfo::dtor, PATCH_JUMP);
	InjectHook(0x4A1700, &CPlayerInfo::LoadPlayerSkin, PATCH_JUMP);
	InjectHook(0x4A1750, &CPlayerInfo::DeletePlayerSkin, PATCH_JUMP);
	InjectHook(0x4A12E0, &CPlayerInfo::KillPlayer, PATCH_JUMP);
	InjectHook(0x4A1330, &CPlayerInfo::ArrestPlayer, PATCH_JUMP);
	InjectHook(0x49FC10, &CPlayerInfo::Clear, PATCH_JUMP);
	InjectHook(0x4A15C0, &CPlayerInfo::BlowUpRCBuggy, PATCH_JUMP);
	InjectHook(0x4A13B0, &CPlayerInfo::CancelPlayerEnteringCars, PATCH_JUMP);
	InjectHook(0x4A1400, &CPlayerInfo::MakePlayerSafe, PATCH_JUMP);
	InjectHook(0x4A0EC0, &CPlayerInfo::EvaluateCarPosition, PATCH_JUMP);
	InjectHook(0x4A15F0, &CPlayerInfo::AwardMoneyForExplosion, PATCH_JUMP);
	InjectHook(0x4A0B20, &CPlayerInfo::LoadPlayerInfo, PATCH_JUMP);
	InjectHook(0x4A0960, &CPlayerInfo::SavePlayerInfo, PATCH_JUMP);
ENDPATCHES
