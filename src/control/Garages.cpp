#include "common.h"

#include "Garages.h"
#include "main.h"

#include "Bike.h"
#include "Boat.h"
#include "DMAudio.h"
#include "General.h"
#include "Font.h"
#include "Frontend.h"
#include "HandlingMgr.h"
#include "Hud.h"
#include "Messages.h"
#include "ModelIndices.h"
#include "Pad.h"
#include "Particle.h"
#include "PlayerPed.h"
#include "Radar.h"
#include "Replay.h"
#include "Script.h"
#include "Stats.h"
#include "Streaming.h"
#include "Text.h"
#include "Timer.h"
#include "Vehicle.h"
#include "Wanted.h"
#include "World.h"
#include "VarConsole.h"
#include "SaveBuf.h"

//--LCS: file done except TODO

#define ROTATED_DOOR_OPEN_SPEED (0.015f)
#define ROTATED_DOOR_CLOSE_SPEED (0.02f)
#define DEFAULT_DOOR_OPEN_SPEED (0.035f)
#define DEFAULT_DOOR_CLOSE_SPEED (0.04f)
#define CRUSHER_CRANE_SPEED (0.005f)

// Prices
#define BOMB_PRICE (500)
#define RESPRAY_PRICE (100)

// Distances
#define DISTANCE_TO_CALL_OFF_CHASE (50.0f)
#define DISTANCE_FOR_MRWHOOP_HACK (0.5f)
#define DISTANCE_TO_ACTIVATE_GARAGE (8.0f)
#define DISTANCE_TO_ACTIVATE_KEEPCAR_GARAGE (17.0f)
#define DISTANCE_TO_CLOSE_MISSION_GARAGE (30.0f)
#define DISTANCE_TO_CLOSE_COLLECTSPECIFICCARS_GARAGE (25.0f)
#define DISTANCE_TO_CLOSE_COLLECTCARS_GARAGE (40.0f)
#define DISTANCE_TO_CLOSE_HIDEOUT_GARAGE_ON_FOOT (3.2f)
#define DISTANCE_TO_CLOSE_HIDEOUT_GARAGE_IN_CAR (15.0f)
#define DISTANCE_TO_FORCE_CLOSE_HIDEOUT_GARAGE (70.0f)
#define DISTANCE_TO_OPEN_HIDEOUT_GARAGE_ON_FOOT (2.8f)
#define DISTANCE_TO_OPEN_HIDEOUT_GARAGE_IN_CAR (10.0f)
#define DISTANCE_TO_SHOW_HIDEOUT_MESSAGE (5.0f)

#define DISTANCE_TO_CONSIDER_DOOR_FOR_GARAGE (20.0f)

// Time
#define TIME_TO_RESPRAY (2000)
#define TIME_TO_SETUP_BOMB (2000)
#define TIME_TO_CRUSH_CAR (3000)
#define TIME_TO_PROCESS_KEEPCAR_GARAGE (2000)

// Respray stuff
#define FREE_RESPRAY_HEALTH_THRESHOLD (970.0f)
#define NUM_PARTICLES_IN_RESPRAY (200)
#define RESPRAY_CENTERING_COEFFICIENT (0.4f)

// Bomb stuff
#define KGS_OF_EXPLOSIVES_IN_BOMB (10)

// Collect specific cars stuff
#define REWARD_FOR_FIRST_POLICE_CAR (5000)
#define REWARD_FOR_FIRST_BANK_VAN (5000)
#define MAX_POLICE_CARS_TO_COLLECT (10)
#define MAX_BANK_VANS_TO_COLLECT (10)

// Collect cars stuff
#define MAX_SPEED_TO_SHOW_COLLECTED_MESSAGE (0.03f)
#define IMPORT_REWARD (500)
#define IMPORT_ALLCARS_REWARD (20500)

// Crusher stuff
#define CRUSHER_VEHICLE_TEST_SPAN (8)
#define CRUSHER_MIN_REWARD (25)
#define CRUSHER_MAX_REWARD (125)
#define CRUSHER_REWARD_COEFFICIENT (1.0f/500000)

// Hideout stuff
#define HIDEOUT_DOOR_SPEED_COEFFICIENT (1.7f)
#define TIME_BETWEEN_HIDEOUT_MESSAGES (18000)

// Camera stuff
#define MARGIN_FOR_CAMERA_COLLECTCARS (0.5f)
#define MARGIN_FOR_CAMERA_DEFAULT (0.5f)

const int32 gaCarsToCollectInCraigsGarages[TOTAL_COLLECTCARS_GARAGES][TOTAL_COLLECTCARS_CARS] =
{
	{ MI_HEARSE, MI_FAGGIO, MI_FREEWAY, MI_SPIDER, MI_MANANA, MI_SHELBY, MI_PONTIAC, MI_ESPRIT, MI_HOTROD, MI_PCJ600, MI_SENTINEL, MI_INFERNUS, MI_BANSHEE, MI_PATRIOT, MI_BFINJECT, MI_LANDSTAL },
	{ MI_HEARSE, MI_FAGGIO, MI_FREEWAY, MI_SPIDER, MI_MANANA, MI_SHELBY, MI_PONTIAC, MI_ESPRIT, MI_HOTROD, MI_PCJ600, MI_SENTINEL, MI_INFERNUS, MI_BANSHEE, MI_PATRIOT, MI_BFINJECT, MI_LANDSTAL },
	{ MI_HEARSE, MI_FAGGIO, MI_FREEWAY, MI_SPIDER, MI_MANANA, MI_SHELBY, MI_PONTIAC, MI_ESPRIT, MI_HOTROD, MI_PCJ600, MI_SENTINEL, MI_INFERNUS, MI_BANSHEE, MI_PATRIOT, MI_BFINJECT, MI_LANDSTAL },
	{ MI_HEARSE, MI_FAGGIO, MI_FREEWAY, MI_SPIDER, MI_MANANA, MI_SHELBY, MI_PONTIAC, MI_ESPRIT, MI_HOTROD, MI_PCJ600, MI_SENTINEL, MI_INFERNUS, MI_BANSHEE, MI_PATRIOT, MI_BFINJECT, MI_LANDSTAL },
};

const int32 gaCarsToCollectIn60Seconds[] = { MI_CHEETAH, MI_TAXI, MI_ESPERANT, MI_SENTINEL, MI_IDAHO };

int32 CGarages::BankVansCollected;
bool CGarages::BombsAreFree;
bool CGarages::RespraysAreFree;
int32 CGarages::CarsCollected;
int32 CGarages::CarTypesCollected[TOTAL_COLLECTCARS_GARAGES];
int32 CGarages::CrushedCarId;
uint32 CGarages::LastTimeHelpMessage;
int32 CGarages::MessageNumberInString;
char CGarages::MessageIDString[MESSAGE_LENGTH];
int32 CGarages::MessageNumberInString2;
uint32 CGarages::MessageStartTime;
uint32 CGarages::MessageEndTime;
uint32 CGarages::NumGarages;
bool CGarages::PlayerInGarage;
int32 CGarages::PoliceCarsCollected;
CStoredCar CGarages::aCarsInSafeHouses[TOTAL_HIDEOUT_GARAGES][NUM_GARAGE_STORED_CARS];
int32 hGarages = AEHANDLE_NONE;
CGarage CGarages::aGarages[NUM_GARAGES];
bool CGarages::bCamShouldBeOutisde;
uint8 CGarages::CrusherRewardMultiplier;

#ifndef MASTER
bool bPrintNearestObject;
#endif

void CGarages::Init(void)
{
#ifndef MASTER
	VarConsole.Add("Print nearest object", &bPrintNearestObject, true);
#endif
	CrusherRewardMultiplier = 1;
	CrushedCarId = -1;
	NumGarages = 0;
	MessageEndTime = 0;
	MessageStartTime = 0;
	PlayerInGarage = false;
	BombsAreFree = false;
#ifdef FIX_BUGS
	RespraysAreFree = false;
#endif
	CarsCollected = 0;
	BankVansCollected = 0;
	PoliceCarsCollected = 0;
	for (int i = 0; i < TOTAL_COLLECTCARS_GARAGES; i++)
		CarTypesCollected[i] = 0;
	LastTimeHelpMessage = 0;
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++) {
		for (int j = 0; j < TOTAL_HIDEOUT_GARAGES; j++)
			aCarsInSafeHouses[j][i].Init();
	}
	hGarages = DMAudio.CreateEntity(AUDIOTYPE_GARAGE, (void*)1);
	if (hGarages >= 0)
		DMAudio.SetEntityStatus(hGarages, TRUE);
}

void CGarages::Shutdown(void)
{
	NumGarages = 0;
	if (hGarages < 0)
		return;
	DMAudio.DestroyEntity(hGarages);
	hGarages = AEHANDLE_NONE;
}

void CGarages::Update(void)
{
	static uint32 GarageToBeTidied = 0;
	if (CReplay::IsPlayingBack())
		return;
#ifdef SECUROM
	extern uint8 gameProcessPirateCheck;
	if (gameProcessPirateCheck == 2) return;
#endif
	bCamShouldBeOutisde = false;
	TheCamera.pToGarageWeAreIn = nil;
	TheCamera.pToGarageWeAreInForHackAvoidFirstPerson = nil;
#ifdef FIX_BUGS
	for (uint32 i = 0; i < NumGarages; i++) {
#else
	for (int i = 0; i < NUM_GARAGES; i++) {
#endif
		if (aGarages[i].IsUsed())
			aGarages[i].Update();
	}
	if ((CTimer::GetFrameCounter() & 0xF) != 0xC)
		return;
#ifdef FIX_BUGS
	if (++GarageToBeTidied >= NumGarages)
#else
	if (++GarageToBeTidied >= NUM_GARAGES)
#endif
		GarageToBeTidied = 0;
	if (!aGarages[GarageToBeTidied].IsUsed())
		return;
	if (!aGarages[GarageToBeTidied].IsFar())
		aGarages[GarageToBeTidied].TidyUpGarageClose();
	else
		aGarages[GarageToBeTidied].TidyUpGarage();
}

int16 CGarages::AddOne(float X1, float Y1, float Z1, float X2, float Y2, float X3, float Y3, float Z2, uint8 type, int32 targetId)
{
	if (NumGarages >= NUM_GARAGES) {
		assert(0);
		return NumGarages++;
	}
	CGarage* pGarage = &aGarages[NumGarages];
	pGarage->m_fInfX = Min(Min(Min(X1, X2), X3), X2 + X3 - X1);
	pGarage->m_fSupX = Max(Max(X1, X2), X3);
	pGarage->m_fInfY = Min(Min(Min(Y1, Y2), Y3), Y2 + Y3 - Y1);
	pGarage->m_fSupY = Max(Max(Y1, Y2), Y3);
	pGarage->m_vecCorner1 = CVector2D(X1, Y1);
	pGarage->m_fInfZ = Z1;
	pGarage->m_vDir1 = CVector2D(X2 - X1, Y2 - Y1);
	pGarage->m_vDir2 = CVector2D(X3 - X1, Y3 - Y1);
	pGarage->m_fSupZ = Z2;
	pGarage->m_nMaxStoredCars = NUM_GARAGE_STORED_CARS;
	pGarage->m_fDir1Len = pGarage->m_vDir1.Magnitude();
	pGarage->m_fDir2Len = pGarage->m_vDir2.Magnitude();
	pGarage->m_vDir1 /= pGarage->m_fDir1Len;
	pGarage->m_vDir2 /= pGarage->m_fDir2Len;
	pGarage->m_pDoor1 = nil;
	pGarage->m_pDoor2 = nil;
	pGarage->m_fDoor1Z = Z1;
	pGarage->m_fDoor2Z = Z1;
	pGarage->m_eGarageType = type;
	pGarage->m_bRecreateDoorOnNextRefresh = false;
	pGarage->m_bRotatedDoor = false;
	pGarage->m_bCameraFollowsPlayer = false;
	pGarage->m_nTimeToStartAction = 0;
	pGarage->field_2 = false;
	pGarage->m_nTargetModelIndex = targetId;
	pGarage->m_bCollectedCarsState = 0;
	pGarage->m_bDeactivated = false;
	pGarage->m_bResprayHappened = false;
	pGarage->m_bInitialized = false;
	pGarage->m_bSSGarageAcceptedVehicle = false;
	pGarage->m_bSSGarageStateChanging = false;
	pGarage->m_bInitialized = InitDoorGubbins(NumGarages, type);
	return NumGarages++;
}

bool CGarages::InitDoorGubbins(uint32 id, uint8 type)
{
	CGarage* pGarage = &aGarages[id];
	pGarage->RefreshDoorPointers(true);
	if (pGarage->m_pDoor1) {
		pGarage->m_fDoor1Z = pGarage->m_pDoor1->GetPosition().z;
		pGarage->m_fDoor1X = pGarage->m_pDoor1->GetPosition().x;
		pGarage->m_fDoor1Y = pGarage->m_pDoor1->GetPosition().y;
	}
	if (pGarage->m_pDoor2) {
		pGarage->m_fDoor2Z = pGarage->m_pDoor2->GetPosition().z;
		pGarage->m_fDoor2X = pGarage->m_pDoor2->GetPosition().x;
		pGarage->m_fDoor2Y = pGarage->m_pDoor2->GetPosition().y;
	}
	pGarage->m_fDoorHeight = pGarage->m_pDoor1 ? FindDoorHeightForMI(pGarage->m_pDoor1->GetModelIndex()) : 4.0f;
	pGarage->m_fDoorPos = 0.0f;
	pGarage->m_eGarageState = GS_FULLYCLOSED;
	switch (type) {
	case GARAGE_MISSION:
	case GARAGE_COLLECTORSITEMS:
	case GARAGE_COLLECTSPECIFICCARS:
	case GARAGE_COLLECTCARS_1:
	case GARAGE_COLLECTCARS_2:
	case GARAGE_COLLECTCARS_3:
	case GARAGE_FORCARTOCOMEOUTOF:
	case GARAGE_MISSION_KEEPCAR:
	case GARAGE_FOR_SCRIPT_TO_OPEN:
	case GARAGE_HIDEOUT_ONE:
	case GARAGE_HIDEOUT_TWO:
	case GARAGE_HIDEOUT_THREE:
	case GARAGE_FOR_SCRIPT_TO_OPEN_AND_CLOSE:
	case GARAGE_KEEPS_OPENING_FOR_SPECIFIC_CAR:
	case GARAGE_MISSION_KEEPCAR_REMAINCLOSED:
	case GARAGE_COLLECTCARS_4:
	case GARAGE_FOR_SCRIPT_TO_OPEN_FOR_CAR:
	case GARAGE_HIDEOUT_FOUR:
	case GARAGE_HIDEOUT_FIVE:
	case GARAGE_HIDEOUT_SIX:
	case GARAGE_HIDEOUT_SEVEN:
	case GARAGE_HIDEOUT_EIGHT:
	case GARAGE_HIDEOUT_NINE:
	case GARAGE_HIDEOUT_TEN:
	case GARAGE_HIDEOUT_ELEVEN:
	case GARAGE_HIDEOUT_TWELVE:
		pGarage->m_eGarageState = GS_FULLYCLOSED;
		pGarage->m_fDoorPos = 0.0f;
		break;
	case GARAGE_BOMBSHOP1:
	case GARAGE_BOMBSHOP2:
	case GARAGE_BOMBSHOP3:
	case GARAGE_RESPRAY:
	case GARAGE_CRATE_GARAGE:
		pGarage->m_eGarageState = GS_OPENED;
		pGarage->m_fDoorPos = pGarage->m_fDoorHeight;
		break;
	case GARAGE_CRUSHER:
		pGarage->m_eGarageState = GS_OPENED;
		pGarage->m_fDoorPos = HALFPI;
		break;
	default:
		assert(false);
	}
	if (type == GARAGE_CRUSHER)
		pGarage->UpdateCrusherAngle();
	else
		pGarage->UpdateDoorsHeight();
	return pGarage->m_fDoorHeight > 0.0f;
}

void CGarages::SetupAnyGaragesForThisIsland(void)
{
	for (uint32 i = 0; i < NumGarages; i++) {
		CGarage* pGarage = &aGarages[i];
		if (!pGarage->m_bInitialized)
			pGarage->m_bInitialized = InitDoorGubbins(i, pGarage->m_eGarageType);
	}
}

void CGarages::ChangeGarageType(int16 garage, uint8 type, int32 mi)
{
	CGarage* pGarage = &aGarages[garage];
	pGarage->m_eGarageType = type;
	pGarage->m_nTargetModelIndex = mi;
	pGarage->m_eGarageState = GS_FULLYCLOSED;
}

void CGarages::LockGarage(int16 garage, bool state)
{
	CGarage* pGarage = &aGarages[garage];
	pGarage->m_bLocked = state;
	if (pGarage->m_bLocked) {
		pGarage->m_fDoorPos = 0.0f;
		pGarage->m_eGarageState = GS_FULLYCLOSED;
		pGarage->m_nTimeToStartAction = CTimer::GetTimeInMilliseconds() + 2000;
		pGarage->UpdateDoorsHeight();
	}
	else {
		pGarage->m_eGarageState = GS_OPENING;
	}
}

void CGarage::Update()
{
#ifdef GTA_NETWORK
	if (/* gIsMultiplayerGame && */m_eGarageType != GARAGE_CRATE_GARAGE) // TODO(multiplayer)
		return;
#endif
	if (m_eGarageType != GARAGE_CRUSHER) {
		switch (m_eGarageState) {
		case GS_FULLYCLOSED:
		case GS_OPENED:
		case GS_CLOSING:
		case GS_OPENING:
		case GS_OPENEDCONTAINSCAR:
		case GS_CLOSEDCONTAINSCAR:
			if (FindPlayerPed() && !m_bCameraFollowsPlayer) {
				CVehicle* pVehicle = FindPlayerVehicle();
				if (IsEntityEntirelyInside3D(FindPlayerPed(), 0.25f)) {
					TheCamera.pToGarageWeAreIn = this;
					CGarages::bCamShouldBeOutisde = true;
				}
				if (pVehicle) {
					if (!IsEntityEntirelyOutside(pVehicle, 0.0f))
						TheCamera.pToGarageWeAreInForHackAvoidFirstPerson = this;
					if (pVehicle->GetModelIndex() == MI_MRWHOOP) {
						if (pVehicle->IsWithinArea(
							m_fInfX - DISTANCE_FOR_MRWHOOP_HACK,
							m_fInfY - DISTANCE_FOR_MRWHOOP_HACK,
							m_fSupX + DISTANCE_FOR_MRWHOOP_HACK,
							m_fSupY + DISTANCE_FOR_MRWHOOP_HACK)) {
							TheCamera.pToGarageWeAreIn = this;
							CGarages::bCamShouldBeOutisde = true;
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}
	if (m_bDeactivated && m_eGarageState == GS_FULLYCLOSED)
		return;
	if (m_bRotatedDoor) {
#if defined GTA_PS2 || defined GTA_PSP
		if (m_eGarageState == GS_OPENING) {
			if (m_pDoor1) {
				if (FindPlayerPed()->m_pCurrentPhysSurface == m_pDoor1)
					m_pDoor1->bUsesCollision = false;
			}
			if (m_pDoor2) {
				if (FindPlayerPed()->m_pCurrentPhysSurface == m_pDoor2)
					m_pDoor2->bUsesCollision = false;
			}
		}
		else if (m_eGarageState == GS_OPENED) {
			if (m_pDoor1)
				m_pDoor1->bUsesCollision = true;
			if (m_pDoor2)
				m_pDoor2->bUsesCollision = true;
		}
#else
		if (m_eGarageState == GS_OPENING || m_eGarageState == GS_OPENED) {
			if (m_pDoor1) {
				if (FindPlayerPed()->m_pCurrentPhysSurface == m_pDoor1 || FindPlayerPed()->GetPedState() == PED_JUMP || FindPlayerPed()->GetPedState() == PED_FALL || !FindPlayerPed()->bIsStanding)
					m_pDoor1->bUsesCollision = false;
			}
			if (m_pDoor2) {
				if (FindPlayerPed()->m_pCurrentPhysSurface == m_pDoor2 || FindPlayerPed()->GetPedState() == PED_JUMP || FindPlayerPed()->GetPedState() == PED_FALL || !FindPlayerPed()->bIsStanding)
					m_pDoor2->bUsesCollision = false;
			}
		}
		else {
			if (m_pDoor1)
				m_pDoor1->bUsesCollision = true;
			if (m_pDoor2)
				m_pDoor2->bUsesCollision = true;
		}
#endif
	}
	switch (m_eGarageType) {
	case GARAGE_RESPRAY:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (IsStaticPlayerCarEntirelyInside()) {
				if (CGarages::IsCarSprayable(FindPlayerVehicle())) {
					if (CWorld::Players[CWorld::PlayerInFocus].m_nMoney >= RESPRAY_PRICE || CGarages::RespraysAreFree) {
						m_eGarageState = GS_CLOSING;
						CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
						FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
					}
					else {
						CGarages::TriggerMessage("GA_3", -1, 4000, -1); // No more freebies. $100 to respray!
						m_eGarageState = GS_OPENEDCONTAINSCAR;
						DMAudio.PlayFrontEndSound(SOUND_GARAGE_NO_MONEY, 1);
					}
				}
				else {
					CGarages::TriggerMessage("GA_1", -1, 4000, -1); // Whoa! I don't touch nothing THAT hot!
					m_eGarageState = GS_OPENEDCONTAINSCAR;
					DMAudio.PlayFrontEndSound(SOUND_GARAGE_BAD_VEHICLE, 1);
				}
			}
			if (FindPlayerVehicle()) {
				if (CalcDistToGarageRectangleSquared(FindPlayerVehicle()->GetPosition().x, FindPlayerVehicle()->GetPosition().y) < SQR(DISTANCE_TO_ACTIVATE_GARAGE))
					CWorld::CallOffChaseForArea(
						m_fInfX - DISTANCE_TO_CALL_OFF_CHASE,
						m_fInfY - DISTANCE_TO_CALL_OFF_CHASE,
						m_fSupX + DISTANCE_TO_CALL_OFF_CHASE,
						m_fSupY + DISTANCE_TO_CALL_OFF_CHASE);
			}
			break;
		case GS_CLOSING:
			if (FindPlayerVehicle())
				ThrowCarsNearDoorOutOfGarage(FindPlayerVehicle());
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				m_nTimeToStartAction = CTimer::GetTimeInMilliseconds() + TIME_TO_RESPRAY;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				CStats::CheckPointReachedSuccessfully();
			}
			UpdateDoorsHeight();
#ifdef FIX_BUGS
			if (FindPlayerVehicle() && FindPlayerVehicle()->IsCar())
#else
			if (FindPlayerVehicle())
#endif
			{
				((CAutomobile*)(FindPlayerVehicle()))->m_fFireBlowUpTimer = 0.0f;
				FindPlayerVehicle()->m_bGarageTurnedLightsOff = true;
			}
			CWorld::CallOffChaseForArea(
				m_fInfX - DISTANCE_TO_CALL_OFF_CHASE,
				m_fInfY - DISTANCE_TO_CALL_OFF_CHASE,
				m_fSupX + DISTANCE_TO_CALL_OFF_CHASE,
				m_fSupY + DISTANCE_TO_CALL_OFF_CHASE);
			break;
		case GS_FULLYCLOSED:
			m_fDoorPos = 0.0f;
			if (CTimer::GetTimeInMilliseconds() > m_nTimeToStartAction) {
				m_eGarageState = GS_OPENING;
				DMAudio.PlayFrontEndSound(SOUND_GARAGE_OPENING, 1);
				bool bTakeMoney = false;
				if (FindPlayerPed()->m_pWanted->GetWantedLevel() != 0) {
					bTakeMoney = true;
					FindPlayerPed()->m_pWanted->Suspend();
				}
				CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
				FindPlayerPed()->m_pWanted->m_bIgnoredByCops = false;
#ifdef FIX_BUGS
				bool bChangedColour = false;
#else
				bool bChangedColour;
#endif
				if (FindPlayerVehicle() && (FindPlayerVehicle()->IsCar() || FindPlayerVehicle()->IsBike())) {
					if (FindPlayerVehicle()->m_fHealth < FREE_RESPRAY_HEALTH_THRESHOLD)
						bTakeMoney = true;
					FindPlayerVehicle()->m_fHealth = 1000.0f;
					if (FindPlayerVehicle()->IsCar()) {
						((CAutomobile*)(FindPlayerVehicle()))->m_fFireBlowUpTimer = 0.0f;
						((CAutomobile*)(FindPlayerVehicle()))->Fix();
					}
					else {
						((CBike*)(FindPlayerVehicle()))->m_fFireBlowUpTimer = 0.0f;
						((CBike*)(FindPlayerVehicle()))->Fix();
					}
					FindPlayerVehicle()->m_nDoorLock = CARLOCK_UNLOCKED;
					++CStats::Sprayings;
					if (FindPlayerVehicle()->GetUp().z < 0.0f) {
						FindPlayerVehicle()->GetUp() = -FindPlayerVehicle()->GetUp();
						FindPlayerVehicle()->GetRight() = -FindPlayerVehicle()->GetRight();
					}
					bChangedColour = false;
					if ((!FindPlayerVehicle()->IsCar() || !((CAutomobile*)(FindPlayerVehicle()))->bFixedColour) &&
						(!FindPlayerVehicle()->IsBike() || !((CBike*)(FindPlayerVehicle()))->bFixedColour)) {
						uint8 colour1, colour2;
						uint16 attempt;
						FindPlayerVehicle()->GetModelInfo()->ChooseVehicleColour(colour1, colour2);
						for (attempt = 0; attempt < 10; attempt++) {
							if (colour1 != FindPlayerVehicle()->m_currentColour1 || colour2 != FindPlayerVehicle()->m_currentColour2)
								break;
							FindPlayerVehicle()->GetModelInfo()->ChooseVehicleColour(colour1, colour2);
						}
						bChangedColour = (attempt < 10);
						FindPlayerVehicle()->m_currentColour1 = colour1;
						FindPlayerVehicle()->m_currentColour2 = colour2;
						if (bChangedColour) {
							CVector vCorners[] = {
								CVector(m_fInfX, m_fInfY, 0.0f), CVector(m_fInfX, m_fSupY, 0.0f),
								CVector(m_fSupX, m_fInfY, 0.0f), CVector(m_fSupX, m_fSupY, 0.0f)
							};
							CVector vMiddles[] = {
								CVector(m_fInfX + (m_fSupX - m_fInfX) / 2, m_fInfY, 0.0f), CVector(m_fInfX, m_fInfY + (m_fSupY - m_fInfY) / 2, 0.0f),
								CVector(m_fInfX + (m_fSupX - m_fInfX) / 2, m_fSupY, 0.0f), CVector(m_fSupX, m_fInfY + (m_fSupY - m_fInfY) / 2, 0.0f),
							};
							int nClosestCornerToCamera = 0;
							int nClosestMiddleToCamera = 0;
							for (int i = 1; i < 4; i++) {
								if ((vCorners[nClosestCornerToCamera] - TheCamera.GetPosition()).Magnitude() >
									(vCorners[i] - TheCamera.GetPosition()).Magnitude())
									nClosestCornerToCamera = i;
								if ((vMiddles[nClosestMiddleToCamera] - TheCamera.GetPosition()).Magnitude() >
									(vMiddles[i] - TheCamera.GetPosition()).Magnitude())
									nClosestMiddleToCamera = i;
							}
							CVector vDirectionCenterToMiddle = vMiddles[nClosestMiddleToCamera] - CVector(GetGarageCenterX(), GetGarageCenterY(), 0.0f);
							vDirectionCenterToMiddle.Normalise();

							for (int i = 0; i < NUM_PARTICLES_IN_RESPRAY; i++) {
								CVector pos(vMiddles[nClosestMiddleToCamera] - vDirectionCenterToMiddle * 0.5f);
								CVector dir(CrossProduct(vDirectionCenterToMiddle, CVector(0.0f, 0.0f, 1.0f)));
								float fDirMultiplier = (vCorners[nClosestCornerToCamera] - vMiddles[nClosestMiddleToCamera]).Magnitude();
								pos += dir * CGeneral::GetRandomNumberInRange(-1.0f, 1.0f) * fDirMultiplier; // TODO: base::RandomReal?
								pos += vDirectionCenterToMiddle * CGeneral::GetRandomNumberInRange(-6.0f, 0.4f);
								dir = vDirectionCenterToMiddle * 0.04f;
								pos.z = m_fInfZ + CGeneral::GetRandomNumberInRange(-0.4f, 0.0f);
								CParticle::AddParticle(PARTICLE_GARAGEPAINT_SPRAY, pos, dir, nil, 0.0f, CVehicleModelInfo::mspInfo->ms_vehicleColourTable[colour1]);
							}
						}
					}
					CenterCarInGarage(FindPlayerVehicle());
				}
				if (bTakeMoney) {
					if (!CGarages::RespraysAreFree) {
						CWorld::Players[CWorld::PlayerInFocus].m_nMoney = Max(0, CWorld::Players[CWorld::PlayerInFocus].m_nMoney - RESPRAY_PRICE);
						CStats::AutoPaintingBudget += RESPRAY_PRICE;
						CGarages::TriggerMessage("GA_2", -1, 4000, -1); // New engine and paint job. The cops won't recognize you!
					}
					else {
						CGarages::TriggerMessage("GA_17", -1, 4000, -1);
					}
				}
				else if (bChangedColour) {
					if (CGeneral::GetRandomTrueFalse())
						CGarages::TriggerMessage("GA_15", -1, 4000, -1); // Hope you like the new color.
					else
						CGarages::TriggerMessage("GA_16", -1, 4000, -1); // Respray is complementary.
				}
				m_bResprayHappened = true;
			}
			CWorld::CallOffChaseForArea(
				m_fInfX - DISTANCE_TO_CALL_OFF_CHASE,
				m_fInfY - DISTANCE_TO_CALL_OFF_CHASE,
				m_fSupX + DISTANCE_TO_CALL_OFF_CHASE,
				m_fSupY + DISTANCE_TO_CALL_OFF_CHASE);
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENEDCONTAINSCAR;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_OPENEDCONTAINSCAR:
			if (FindPlayerVehicle())
				FindPlayerVehicle()->m_bGarageTurnedLightsOff = false;
			if (IsPlayerOutsideGarage())
				m_eGarageState = GS_OPENED;
			break;
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_BOMBSHOP1:
	case GARAGE_BOMBSHOP2:
	case GARAGE_BOMBSHOP3:
		if (m_bLocked) {
			UpdateDoorsHeight();
			break;
		}
		switch (m_eGarageState) {
		case GS_OPENED:
			UpdateDoorsHeight();
			if (IsStaticPlayerCarEntirelyInside()) {
#ifndef BOMBS_ON_BIKES
				if (FindPlayerVehicle()->GetVehicleAppearance() == VEHICLE_APPEARANCE_BIKE) {
					CGarages::TriggerMessage("GA_22", -1, 4000, -1);
					m_eGarageState = GS_OPENEDCONTAINSCAR;
					DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB_ALREADY_SET, 1);
					break;
				}
#endif
				if (!FindPlayerVehicle()
#ifdef FIX_BUGS
					|| (FindPlayerVehicle()->IsCar() && ((CAutomobile*)FindPlayerVehicle())->m_bombType)
#else
					|| ((CAutomobile*)FindPlayerVehicle())->m_bombType
#endif
#ifdef BOMBS_ON_BIKES
					|| (FindPlayerVehicle()->IsBike() && ((CBike*)FindPlayerVehicle())->m_bombType)
#endif
					) {
					CGarages::TriggerMessage("GA_5", -1, 4000, -1); //"Your car is already fitted with a bomb"
					m_eGarageState = GS_OPENEDCONTAINSCAR;
					DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB_ALREADY_SET, 1);
					break;
				}
				if (!CGarages::BombsAreFree && CWorld::Players[CWorld::PlayerInFocus].m_nMoney < BOMB_PRICE) {
					CGarages::TriggerMessage("GA_4", -1, 4000, -1); // "Car bombs are $1000 each" - weird that the price is hardcoded in message
					m_eGarageState = GS_OPENEDCONTAINSCAR;
					DMAudio.PlayFrontEndSound(SOUND_GARAGE_NO_MONEY, 1);
					break;
				}
				m_eGarageState = GS_CLOSING;
				CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
				FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
				}
			break;
		case GS_CLOSING:
			if (FindPlayerVehicle())
				ThrowCarsNearDoorOutOfGarage(FindPlayerVehicle());
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				m_nTimeToStartAction = CTimer::GetTimeInMilliseconds() + TIME_TO_SETUP_BOMB;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
			}
			if (FindPlayerVehicle())
				FindPlayerVehicle()->m_bGarageTurnedLightsOff = true;
			UpdateDoorsHeight();
			if (m_eGarageType == GARAGE_BOMBSHOP3)
				CStreaming::RequestModel(MI_BOMB, STREAMFLAGS_DONT_REMOVE);
			break;
		case GS_FULLYCLOSED:
			if (CTimer::GetTimeInMilliseconds() > m_nTimeToStartAction) {
				if (m_eGarageType != GARAGE_BOMBSHOP3 || CStreaming::HasModelLoaded(MI_BOMB)) {
					switch (m_eGarageType) {
					case GARAGE_BOMBSHOP1: DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB1_SET, 1); break;
					case GARAGE_BOMBSHOP2: DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB2_SET, 1); break;
					case GARAGE_BOMBSHOP3: DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB3_SET, 1); break;
					}
					m_eGarageState = GS_OPENING;
					if (!CGarages::BombsAreFree)
						CWorld::Players[CWorld::PlayerInFocus].m_nMoney = Max(0, CWorld::Players[CWorld::PlayerInFocus].m_nMoney - BOMB_PRICE);
					if (FindPlayerVehicle() && (FindPlayerVehicle()->IsCar() || FindPlayerVehicle()->IsBike())) {
#ifdef BOMBS_ON_BIKES
						if (FindPlayerVehicle()->IsCar()) {
							((CAutomobile*)(FindPlayerVehicle()))->m_bombType = CGarages::GetBombTypeForGarageType(m_eGarageType);
							((CAutomobile*)(FindPlayerVehicle()))->m_pBombRigger = FindPlayerPed();
						}
						else {
							((CBike*)(FindPlayerVehicle()))->m_bombType = CGarages::GetBombTypeForGarageType(m_eGarageType);
							((CBike*)(FindPlayerVehicle()))->m_pBombRigger = FindPlayerPed();
						}
#else
						((CAutomobile*)(FindPlayerVehicle()))->m_bombType = CGarages::GetBombTypeForGarageType(m_eGarageType);
						((CAutomobile*)(FindPlayerVehicle()))->m_pBombRigger = FindPlayerPed();
#endif
						// what is this
						uint32 i = CPools::GetVehiclePool()->GetSize();
						while (i--) {
							CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
							if (pVehicle) {
								if (pVehicle->IsCar() && pVehicle->GetStatus() == STATUS_WRECKED) {
									CAutomobile* pCar = (CAutomobile*)pVehicle;
									pCar->m_pBombRigger = nil;
									pCar->m_pBlowUpEntity = nil;
								}
#ifdef BOMBS_ON_BIKES
								if (pVehicle->IsBike() && pVehicle->GetStatus() == STATUS_WRECKED) {
									CBike* pBike = (CBike*)pVehicle;
									pBike->m_pBombRigger = nil;
									pBike->m_pBlowUpEntity = nil;
								}
#endif
							}
						}
						if (m_eGarageType == GARAGE_BOMBSHOP3)
							CGarages::GivePlayerDetonator();
						CStats::KgsOfExplosivesUsed += KGS_OF_EXPLOSIVES_IN_BOMB;
					}
#ifdef DETECT_PAD_INPUT_SWITCH
					int16 Mode = CPad::IsAffectedByController ? CPad::GetPad(0)->Mode : 0;
#else
					int16 Mode = CPad::GetPad(0)->Mode;
#endif
					switch (m_eGarageType) {
					case GARAGE_BOMBSHOP1:
						switch (Mode) {
						case 0:
						case 1:
						case 2:
							CHud::SetHelpMessage(TheText.Get("GA_6"), false); // Arm with ~h~~k~~PED_FIREWEAPON~ button~w~. Bomb will go off when engine is started.
							break;
						case 3:
							CHud::SetHelpMessage(TheText.Get("GA_6B"), false); // Arm with ~h~~k~~PED_FIREWEAPON~ button~w~. Bomb will go off when engine is started.
							break;
						}
						break;
					case GARAGE_BOMBSHOP2:
						switch (Mode) {
						case 0:
						case 1:
						case 2:
							CHud::SetHelpMessage(TheText.Get("GA_7"), false); // Park it, prime it by pressing the ~h~~k~~PED_FIREWEAPON~ button~w~ and LEG IT!
							break;
						case 3:
							CHud::SetHelpMessage(TheText.Get("GA_7B"), false); // Park it, prime it by pressing the ~h~~k~~PED_FIREWEAPON~ button~w~ and LEG IT!
							break;
						}
						break;
					case GARAGE_BOMBSHOP3:
						CHud::SetHelpMessage(TheText.Get("GA_8"), false); // Use the detonator to activate the bomb.
						break;
					}
					CGarages::TriggerMessage(CGarages::BombsAreFree ? "GA_24" : "GA_23", -1, 4000, -1);
					CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
					FindPlayerPed()->m_pWanted->m_bIgnoredByCops = false;
				}
				else {
					CStreaming::RequestModel(MI_BOMB, STREAMFLAGS_DONT_REMOVE);
				}
			}
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENEDCONTAINSCAR;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_OPENEDCONTAINSCAR:
			if (FindPlayerVehicle())
				FindPlayerVehicle()->m_bGarageTurnedLightsOff = false;
			if (IsPlayerOutsideGarage())
				m_eGarageState = GS_OPENED;
			break;
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
			}
		break;
	case GARAGE_MISSION:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (((CVector2D)FindPlayerCoors() - CVector2D(GetGarageCenterX(), GetGarageCenterY())).MagnitudeSqr() > SQR(DISTANCE_TO_CLOSE_MISSION_GARAGE)) {
				if ((CTimer::GetFrameCounter() & 0x1F) == 0 && !IsAnyOtherCarTouchingGarage(nil)) {
					m_eGarageState = GS_CLOSING;
					m_bClosingWithoutTargetCar = true;
				}
			}
			else if (m_pTarget && IsEntityEntirelyInside3D(m_pTarget, 0.0f) &&
				IsEntityEntirelyOutside(FindPlayerVehicle() ? (CEntity*)FindPlayerVehicle() : (CEntity*)FindPlayerPed(), 2.0f)) {
				CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
				FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
				m_eGarageState = GS_CLOSING;
				m_bClosingWithoutTargetCar = false;
			}
			break;
		case GS_CLOSING:
			if (m_pTarget)
				ThrowCarsNearDoorOutOfGarage(m_pTarget);
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (!IsEntityEntirelyOutside(FindPlayerPed(), 1.0f)) {
				printf("FIX FOR IE GARAGE TRAPPING PLAYER\n");
				m_eGarageState = GS_OPENING;
			}
			else if (m_fDoorPos == 0.0f) {
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				if (m_bClosingWithoutTargetCar)
					m_eGarageState = GS_FULLYCLOSED;
				else {
					if (m_pTarget) {
						m_eGarageState = GS_CLOSEDCONTAINSCAR;
						DestroyVehicleAndDriverAndPassengers(m_pTarget);
						m_pTarget = nil;
					}
					else {
						m_eGarageState = GS_FULLYCLOSED;
					}
					CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
					FindPlayerPed()->m_pWanted->m_bIgnoredByCops = false;
				}
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
			if (FindPlayerVehicle() == m_pTarget && m_pTarget) {
				if (CalcDistToGarageRectangleSquared(
					FindPlayerVehicle()->GetPosition().x,
					FindPlayerVehicle()->GetPosition().y) < SQR(DISTANCE_TO_ACTIVATE_GARAGE))
					m_eGarageState = GS_OPENING;
			}
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_COLLECTSPECIFICCARS:
	case GARAGE_COLLECTCARS_1:
	case GARAGE_COLLECTCARS_2:
	case GARAGE_COLLECTCARS_3:
	case GARAGE_COLLECTCARS_4:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (FindPlayerVehicle() && DoesCraigNeedThisCar(FindPlayerVehicle()->GetModelIndex())) {
				m_pTarget = FindPlayerVehicle();
				m_pTarget->RegisterReference((CEntity**)&m_pTarget);
			}
			if (Abs(FindPlayerCoors().x - GetGarageCenterX()) > DISTANCE_TO_CLOSE_COLLECTCARS_GARAGE ||
				Abs(FindPlayerCoors().y - GetGarageCenterY()) > DISTANCE_TO_CLOSE_COLLECTCARS_GARAGE) {
				m_eGarageState = GS_CLOSING;
				m_pTarget = nil;
				break;
			}
			if (m_pTarget && !FindPlayerVehicle() && IsEntityEntirelyInside3D(m_pTarget, 0.0f) &&
				!IsAnyOtherCarTouchingGarage(m_pTarget) && IsEntityEntirelyOutside(FindPlayerPed(), 2.0f)) {
#ifdef FIX_BUGS
				if (!m_pTarget->IsCar() ||
					((CAutomobile*)(m_pTarget))->Damage.GetEngineStatus() <= ENGINE_STATUS_ON_FIRE &&
					((CAutomobile*)(m_pTarget))->m_fFireBlowUpTimer == 0.0f) {
#else
				if (((CAutomobile*)(m_pTarget))->Damage.GetEngineStatus() <= ENGINE_STATUS_ON_FIRE &&
					((CAutomobile*)(m_pTarget))->m_fFireBlowUpTimer == 0.0f) {
#endif
					if (m_pTarget->GetStatus() != STATUS_WRECKED) {
						CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
						FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
						m_eGarageState = GS_CLOSING;
						TheCamera.SetCameraDirectlyBehindForFollowPed_CamOnAString();
					}
				}
			}
			break;
		case GS_CLOSING:
			if (m_pTarget)
				ThrowCarsNearDoorOutOfGarage(m_pTarget);
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				if (m_pTarget) {
					MarkThisCarAsCollectedForCraig(m_pTarget->GetModelIndex());
					DestroyVehicleAndDriverAndPassengers(m_pTarget);
					m_pTarget = nil;
					CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
					FindPlayerPed()->m_pWanted->m_bIgnoredByCops = false;
				}
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
			if (CTheScripts::IsPlayerOnAMission()) {
				m_pTarget = nil;
				break;
			}
			if (!IsEntityEntirelyOutside(FindPlayerPed(), 0.0f)) {
				printf("FIX FOR IE GARAGE TRAPPING PLAYER\n");
				m_eGarageState = GS_OPENING;
			}
			if (FindPlayerVehicle() &&
				CalcSmallestDistToGarageDoorSquared(
					FindPlayerVehicle()->GetPosition().x,
					FindPlayerVehicle()->GetPosition().y
					) < SQR(DISTANCE_TO_ACTIVATE_GARAGE)) {
				if (DoesCraigNeedThisCar(FindPlayerVehicle()->GetModelIndex())) {
					m_eGarageState = GS_OPENING;
				}
			}
			m_pTarget = nil;
			break;
		case GS_OPENING:
			if (FindPlayerVehicle() && DoesCraigNeedThisCar(FindPlayerVehicle()->GetModelIndex())) {
				m_pTarget = FindPlayerVehicle();
				m_pTarget->RegisterReference((CEntity**)&m_pTarget);
			}
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_FORCARTOCOMEOUTOF:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (IsGarageEmpty())
				m_eGarageState = GS_CLOSING;
			break;
		case GS_CLOSING:
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
			}
			UpdateDoorsHeight();
			if (!IsGarageEmpty())
				m_eGarageState = GS_OPENING;
			break;
		case GS_FULLYCLOSED:
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_CRATE_GARAGE:
#ifdef GTA_NETWORK
	{
		switch (m_eGarageState) {
		case GS_OPENED:
			if (m_pSSVehicle) {
				// if (m_pSSVehicle->GetVehiclePointer() && IsEntityEntirelyInside3D(m_pSSVehicle->GetVehiclePointer())
				{
					if (m_pSSTargetCar)
						m_pSSTargetCar->CleanUpOldReference((CEntity**)&m_pSSTargetCar);
					// m_pSSTargetCar = m_pSSVehicle->GetVehiclePointer();
					m_pSSTargetCar->RegisterReference((CEntity**)&m_pSSTargetCar);
				}
				// else
				{
					if (m_pSSTargetCar)
						m_pSSTargetCar->CleanUpOldReference((CEntity**)&m_pSSTargetCar);
					m_pSSTargetCar = nil;
				}
				if (m_pSSTargetCar) {
					if (!FindPlayerVehicle()/* && m_pSSTargetCar == m_pSSVehicle->GetVehiclePointer() */)
					{
						if (IsEntityEntirelyOutside(FindPlayerPed(), 6.0f)) {
							if (FindPlayerPed()->m_fHealth > 0.0f) {
								CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
								m_eGarageState = GS_CLOSING;
								m_bSSGarageStateChanging = true;
							}
						}
					}
				}
			}
			break;
		case GS_CLOSING:
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				// if (? == m_nSSGarageState)
				{
					if (m_pSSTargetCar) {
						// if (m_pSSVehicle->GetVehiclePointer())
						{
							if (IsEntityEntirelyInside3D(/* m_pSSVehicle->GetVehiclePointer() */nil, 0.0f)) {
								if (m_pSSTargetCar)
									m_pSSTargetCar->CleanUpOldReference((CEntity**)&m_pSSTargetCar);
								CWorld::Remove(m_pSSTargetCar);
								delete m_pSSTargetCar;
								m_pSSTargetCar = nil;
								m_pSSVehicle = nil;
								m_bSSGarageAcceptedVehicle = true;
								printf("Destroying Car Inside Crate....\n");
							}
						}
					}
				}
				// TODO: some loop :(
				CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
				m_eGarageState = GS_FULLYCLOSED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
			}
			UpdateDoorsHeight();
			if (!IsGarageEmpty())
				m_eGarageState = GS_OPENING;
			break;
		case GS_FULLYCLOSED:
		{
			// if (? == m_nSSGarageState)
			{
				if (CalcDistToGarageRectangleSquared(FindPlayerPed()->GetPosition().x, FindPlayerPed()->GetPosition().y) > SQR(10.0f))
					m_eGarageState = GS_OPENING;
			}
			break;
		}
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_bSSGarageStateChanging = false;
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		}
		break;
	}
#endif
	case GARAGE_CRUSHER:
	{
		switch (m_eGarageState) {
		case GS_OPENED:
		{
			int i = CPools::GetVehiclePool()->GetSize() * (CTimer::GetFrameCounter() % CRUSHER_VEHICLE_TEST_SPAN) / CRUSHER_VEHICLE_TEST_SPAN;
			int end = CPools::GetVehiclePool()->GetSize() * (CTimer::GetFrameCounter() % CRUSHER_VEHICLE_TEST_SPAN + 1) / CRUSHER_VEHICLE_TEST_SPAN;
			for (; i < end; i++) {
				CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
				if (!pVehicle)
					continue;
				if ((pVehicle->IsCar() || pVehicle->IsBike()) && IsEntityEntirelyInside3D(pVehicle, 0.0f)) {
					m_eGarageState = GS_WAITINGFORCAR;
					m_pTarget = pVehicle;
					m_nTimeCrusherCraneActivated = CTimer::GetTimeInMilliseconds();
					m_pTarget->RegisterReference((CEntity**)&m_pTarget);
				}
			}
			break;
		}
		case GS_CLOSING:
			if (m_pTarget) {
				m_fDoorPos = Max(0.0f, m_fDoorPos - CRUSHER_CRANE_SPEED * CTimer::GetTimeStep());
				if (m_fDoorPos < TWOPI / 5) {
					m_pTarget->bUsesCollision = false;
					m_pTarget->bAffectedByGravity = false;
					m_pTarget->SetMoveSpeed(0.0f, 0.0f, 0.0f);
				}
				else {
					m_pTarget->SetMoveSpeed(m_pTarget->GetMoveSpeed() * Pow(0.8f, CTimer::GetTimeStep()));
				}
				if (m_fDoorPos == 0.0f) {
					CGarages::CrushedCarId = CPools::GetVehiclePool()->GetIndex(m_pTarget);
					float reward = Min(CRUSHER_MAX_REWARD, CRUSHER_MIN_REWARD + m_pTarget->pHandling->nMonetaryValue * m_pTarget->m_fHealth * CRUSHER_REWARD_COEFFICIENT);
					CWorld::Players[CWorld::PlayerInFocus].m_nMoney += reward * CGarages::CrusherRewardMultiplier;
					CMessages::AddMessageWithNumber(TheText.Get("CRUSHED"), 5000, 1, reward* CGarages::CrusherRewardMultiplier, -1, -1, -1, -1, -1);
					DestroyVehicleAndDriverAndPassengers(m_pTarget);
					//++CStats::CarsCrushed; // TODO
					m_pTarget = nil;
					m_eGarageState = GS_AFTERDROPOFF;
					m_nTimeToStartAction = CTimer::GetTimeInMilliseconds() + TIME_TO_CRUSH_CAR;
					DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				}
			}
			else
				m_eGarageState = GS_OPENING;
			UpdateCrusherAngle();
			break;
		case GS_AFTERDROPOFF:
			if (CTimer::GetTimeInMilliseconds() <= m_nTimeToStartAction) {
				UpdateCrusherShake((myrand() & 0xFF - 128) * 0.0002f, (myrand() & 0xFF - 128) * 0.0002f);
			}
			else {
				UpdateCrusherShake(0.0f, 0.0f);
				m_eGarageState = GS_OPENING;
			}
			break;
		case GS_OPENING:
			m_fDoorPos = Min(HALFPI, m_fDoorPos + CTimer::GetTimeStep() * CRUSHER_CRANE_SPEED);
			if (m_fDoorPos == HALFPI) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateCrusherAngle();
			break;
		case GS_WAITINGFORCAR:
			if (m_pTarget) {
				if (CTimer::GetTimeInMilliseconds() - m_nTimeCrusherCraneActivated > 3000)
					m_eGarageState = GS_CLOSING;
			}
			break;
		default:
			break;
		}
		if (!FindPlayerVehicle() && (CTimer::GetFrameCounter() & 0x1F) == 0x17 && IsEntityEntirelyInside3D(FindPlayerPed(), 0.0f))
			FindPlayerPed()->InflictDamage(nil, WEAPONTYPE_RAMMEDBYCAR, 300.0f, PEDPIECE_TORSO, 0);
		break;
	}
	case GARAGE_MISSION_KEEPCAR:
	case GARAGE_MISSION_KEEPCAR_REMAINCLOSED:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (((CVector2D)FindPlayerCoors() - CVector2D(GetGarageCenterX(), GetGarageCenterY())).MagnitudeSqr() > SQR(DISTANCE_TO_CLOSE_MISSION_GARAGE) &&
				!IsAnyOtherCarTouchingGarage(nil)) {
				m_eGarageState = GS_CLOSING;
				m_bClosingWithoutTargetCar = true;
			}
			else if (m_pTarget && m_pTarget == FindPlayerVehicle() && IsStaticPlayerCarEntirelyInside() && !IsAnyCarBlockingDoor()) {
				CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
				FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
				m_eGarageState = GS_CLOSING;
				m_bClosingWithoutTargetCar = false;
			}
			break;
		case GS_CLOSING:
			if (m_pTarget)
				ThrowCarsNearDoorOutOfGarage(m_pTarget);
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				if (m_bClosingWithoutTargetCar)
					m_eGarageState = GS_FULLYCLOSED;
				else {
					if (m_pTarget) {
						m_eGarageState = GS_CLOSEDCONTAINSCAR;
						m_nTimeToStartAction = CTimer::GetTimeInMilliseconds() + TIME_TO_PROCESS_KEEPCAR_GARAGE;
						m_pTarget = nil;
					}
					else
						m_eGarageState = GS_FULLYCLOSED;
					CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
					FindPlayerPed()->m_pWanted->m_bIgnoredByCops = false;
				}
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
			if (FindPlayerVehicle() == m_pTarget && m_pTarget &&
				CalcDistToGarageRectangleSquared(
					FindPlayerVehicle()->GetPosition().x,
					FindPlayerVehicle()->GetPosition().y
					) < SQR(DISTANCE_TO_ACTIVATE_KEEPCAR_GARAGE))
				m_eGarageState = GS_OPENING;
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_CLOSEDCONTAINSCAR:
			if (m_eGarageType == GARAGE_MISSION_KEEPCAR && CTimer::GetTimeInMilliseconds() > m_nTimeToStartAction)
				m_eGarageState = GS_OPENING;
			break;
		//case GS_OPENEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_FOR_SCRIPT_TO_OPEN:
		switch (m_eGarageState) {
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		//case GS_OPENED:
		//case GS_CLOSING:
		//case GS_FULLYCLOSED:
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_FOR_SCRIPT_TO_OPEN_AND_CLOSE:
		switch (m_eGarageState) {
		case GS_CLOSING:
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		//case GS_OPENED:
		//case GS_FULLYCLOSED:
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_HIDEOUT_ONE:
	case GARAGE_HIDEOUT_TWO:
	case GARAGE_HIDEOUT_THREE:
	case GARAGE_HIDEOUT_FOUR:
	case GARAGE_HIDEOUT_FIVE:
	case GARAGE_HIDEOUT_SIX:
	case GARAGE_HIDEOUT_SEVEN:
	case GARAGE_HIDEOUT_EIGHT:
	case GARAGE_HIDEOUT_NINE:
	case GARAGE_HIDEOUT_TEN:
	case GARAGE_HIDEOUT_ELEVEN:
	case GARAGE_HIDEOUT_TWELVE:
		switch (m_eGarageState) {
		case GS_OPENED:
		{
			float distance = CalcDistToGarageRectangleSquared(FindPlayerCoors().x, FindPlayerCoors().y);
			// Close car doors either if player is far, or if he is in vehicle and garage is full,
			// or if player is very very far so that we can remove whatever is blocking garage door without him noticing
			if ((distance > SQR(DISTANCE_TO_CLOSE_HIDEOUT_GARAGE_IN_CAR) ||
				!FindPlayerVehicle() && distance > SQR(DISTANCE_TO_CLOSE_HIDEOUT_GARAGE_ON_FOOT)) &&
				!IsAnyCarBlockingDoor())
				m_eGarageState = GS_CLOSING;
			else if (FindPlayerVehicle() &&
				CountCarsWithCenterPointWithinGarage(FindPlayerVehicle()) >=
				FindMaxNumStoredCarsForGarage()) {
				m_eGarageState = GS_CLOSING;
			}
			else if (distance > SQR(DISTANCE_TO_FORCE_CLOSE_HIDEOUT_GARAGE)) {
				m_eGarageState = GS_CLOSING;
				RemoveCarsBlockingDoorNotInside();
			}
			break;
		}
		case GS_CLOSING:
			m_fDoorPos = Max(0.0f, m_fDoorPos - HIDEOUT_DOOR_SPEED_COEFFICIENT * (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (!IsPlayerOutsideGarage())
				m_eGarageState = GS_OPENING;
			else if (m_fDoorPos == 0.0f) {
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				m_eGarageState = GS_FULLYCLOSED;
				StoreAndRemoveCarsForThisHideout(CGarages::aCarsInSafeHouses[CGarages::FindSafeHouseIndexForGarageType(m_eGarageType)], NUM_GARAGE_STORED_CARS);
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
		{
			float distance = INFINITY;
			if (CWorld::Players[CWorld::PlayerInFocus].m_pPed) {
				distance = CalcDistToGarageRectangleSquared(FindPlayerCoors().x, FindPlayerCoors().y);
			}
			if (distance < SQR(DISTANCE_TO_OPEN_HIDEOUT_GARAGE_ON_FOOT) ||
				distance < SQR(DISTANCE_TO_OPEN_HIDEOUT_GARAGE_IN_CAR) && FindPlayerVehicle()) {
				if (FindPlayerVehicle() && CGarages::CountCarsInHideoutGarage(m_eGarageType) >= FindMaxNumStoredCarsForGarage()) {
					if (m_pDoor1) {
						if (((CVector2D)FindPlayerVehicle()->GetPosition() - (CVector2D)m_pDoor1->GetPosition()).MagnitudeSqr() < SQR(DISTANCE_TO_SHOW_HIDEOUT_MESSAGE) &&
							CTimer::GetTimeInMilliseconds() - CGarages::LastTimeHelpMessage > TIME_BETWEEN_HIDEOUT_MESSAGES) {
							if (FindPlayerVehicle()->GetVehicleAppearance() != VEHICLE_APPEARANCE_HELI && FindPlayerVehicle()->GetVehicleAppearance() != VEHICLE_APPEARANCE_PLANE) {
								CHud::SetHelpMessage(TheText.Get("GA_21"), false); // You cannot store any more cars in this garage.
								CGarages::LastTimeHelpMessage = CTimer::GetTimeInMilliseconds();
							}
						}
					}
				}
				else if (RestoreCarsForThisHideout(CGarages::aCarsInSafeHouses[CGarages::FindSafeHouseIndexForGarageType(m_eGarageType)]))
					m_eGarageState = GS_OPENING;
			}
			break;
		}
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + HIDEOUT_DOOR_SPEED_COEFFICIENT * (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	case GARAGE_KEEPS_OPENING_FOR_SPECIFIC_CAR:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (((CVector2D)FindPlayerCoors() - CVector2D(GetGarageCenterX(), GetGarageCenterY())).MagnitudeSqr() > SQR(DISTANCE_TO_CLOSE_MISSION_GARAGE)) {
				if (m_pTarget && IsEntityEntirelyOutside(m_pTarget, 0.0f) && !IsAnyOtherCarTouchingGarage(nil)) {
					m_eGarageState = GS_CLOSING;
					m_bClosingWithoutTargetCar = true;
				}
			}
			break;
		case GS_CLOSING:
			if (m_pTarget)
				ThrowCarsNearDoorOutOfGarage(m_pTarget);
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
			if (FindPlayerVehicle() == m_pTarget && m_pTarget &&
				CalcDistToGarageRectangleSquared(
					FindPlayerVehicle()->GetPosition().x,
					FindPlayerVehicle()->GetPosition().y
					) < SQR(DISTANCE_TO_ACTIVATE_GARAGE))
				m_eGarageState = GS_OPENING;
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
			break;
		}
		break;
	//case GARAGE_COLLECTORSITEMS:
	//case GARAGE_60SECONDS:
	case GARAGE_FOR_SCRIPT_TO_OPEN_FOR_CAR:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (m_pTarget && IsEntityEntirelyInside3D(m_pTarget, 0.0f) && !IsAnyCarBlockingDoor() && IsPlayerOutsideGarage()) {
				CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
				m_eGarageState = GS_CLOSING;
				m_bClosingWithoutTargetCar = false;
			}
			break;
		case GS_CLOSING:
			m_fDoorPos = Max(0.0f, m_fDoorPos - (m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : DEFAULT_DOOR_CLOSE_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
			break;
		case GS_OPENING:
			m_fDoorPos = Min(m_fDoorHeight, m_fDoorPos + (m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : DEFAULT_DOOR_OPEN_SPEED) * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(hGarages, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
			//case GS_OPENEDCONTAINSCAR:
			//case GS_CLOSEDCONTAINSCAR:
			//case GS_AFTERDROPOFF:
		default:
			break;
		}
	default:
		break;
	}
}

bool CGarage::IsStaticPlayerCarEntirelyInside()
{
	if (!FindPlayerVehicle())
		return false;
	if (!FindPlayerVehicle()->IsCar() && !FindPlayerVehicle()->IsBike())
		return false;
	if (FindPlayerPed()->GetPedState() != PED_DRIVING)
		return false;
	if (FindPlayerPed()->m_objective == OBJECTIVE_LEAVE_CAR)
		return false;
	CVehicle* pVehicle = FindPlayerVehicle();
	if (pVehicle->GetPosition().x < m_fInfX || pVehicle->GetPosition().x > m_fSupX ||
		pVehicle->GetPosition().y < m_fInfY || pVehicle->GetPosition().y > m_fSupY)
		return false;
	if (Abs(pVehicle->GetSpeed().x) > 0.01f ||
		Abs(pVehicle->GetSpeed().y) > 0.01f ||
		Abs(pVehicle->GetSpeed().z) > 0.01f)
		return false;
	if (pVehicle->GetSpeed().MagnitudeSqr() > SQR(0.01f))
		return false;
	return IsEntityEntirelyInside3D(pVehicle, 0.0f);
}

bool CGarage::IsPointInsideGarage(CVector pos)
{
	// is it IsPointInsideGarage(pos, 0.0f)?
	if (pos.z < m_fInfZ)
		return false;
	if (pos.z > m_fSupZ)
		return false;
	CVector2D vecToTarget((CVector2D)pos - m_vecCorner1);
	float dp = DotProduct2D(m_vDir1, vecToTarget);
	if (dp < 0.0f)
		return false;
	if (m_fDir1Len < dp)
		return false;
	dp = DotProduct2D(m_vDir2, vecToTarget);
	if (dp < 0.0f)
		return false;
	if (m_fDir2Len < dp)
		return false;
	return true;
}

bool CGarage::IsPointInsideGarage(CVector pos, float m_fMargin)
{
	if (pos.z < m_fInfZ - m_fMargin)
		return false;
	if (pos.z > m_fSupZ + m_fMargin)
		return false;
	CVector2D vecToTarget((CVector2D)pos - m_vecCorner1);
	float dp = DotProduct2D(m_vDir1, vecToTarget);
	if (dp < -m_fMargin)
		return false;
	if (m_fDir1Len + m_fMargin < dp)
		return false;
	dp = DotProduct2D(m_vDir2, vecToTarget);
	if (dp < -m_fMargin)
		return false;
	if (m_fDir2Len + m_fMargin < dp)
		return false;
	return true;
}

bool CGarage::IsEntityEntirelyInside3D(CEntity* pEntity, float fMargin)
{
	if (pEntity->GetPosition().x < m_fInfX - fMargin || pEntity->GetPosition().x > m_fSupX + fMargin ||
		pEntity->GetPosition().y < m_fInfY - fMargin || pEntity->GetPosition().y > m_fSupY + fMargin ||
		pEntity->GetPosition().z < m_fInfZ - fMargin || pEntity->GetPosition().z > m_fSupZ + fMargin)
		return false;
	CColModel* pColModel = pEntity->GetColModel();
	for (int i = 0; i < pColModel->numSpheres; i++) {
		CVector pos = pEntity->GetMatrix() * pColModel->spheres[i].center;
		float radius = pColModel->spheres[i].radius;
		if (m_eGarageType == GARAGE_CRATE_GARAGE) {
			if (pos.x + radius < m_fInfX - fMargin || pos.x - radius > m_fSupX + fMargin ||
				pos.y + radius < m_fInfY - fMargin || pos.y - radius > m_fSupX + fMargin)
				return false;
		}
		else {
			if (!IsPointInsideGarage(pos, fMargin - radius))
				return false;
		}
	}
	return true;
}

bool CGarage::IsEntityEntirelyOutside(CEntity * pEntity, float fMargin)
{
	if (pEntity->GetPosition().x > m_fInfX - fMargin && pEntity->GetPosition().x < m_fSupX + fMargin &&
		pEntity->GetPosition().y > m_fInfY - fMargin && pEntity->GetPosition().y < m_fSupY + fMargin)
		return false;
	CColModel* pColModel = pEntity->GetColModel();
	for (int i = 0; i < pColModel->numSpheres; i++) {
		CVector pos = pEntity->GetMatrix() * pColModel->spheres[i].center;
		float radius = pColModel->spheres[i].radius;
		if (m_eGarageType == GARAGE_CRATE_GARAGE) {
			if (pos.x + radius > m_fInfX - fMargin && pos.x - radius < m_fSupX + fMargin &&
				pos.y + radius > m_fInfY - fMargin && pos.y - radius < m_fSupX + fMargin)
				return false;
		}
		else {
			if (IsPointInsideGarage(pos, fMargin + radius))
				return false;
		}
	}
	return true;
}

#ifdef GTA_NETWORK
// some CGarage method (0x134E7C)
#endif

bool CGarage::IsGarageEmpty()
{
	int16 num;
	CEntity* pEntities[16];
	CWorld::FindObjectsIntersectingCube(CVector(m_fInfX, m_fInfY, m_fInfZ), CVector(m_fSupX, m_fSupY, m_fSupZ), &num, 16, pEntities, false, true, true, false, false);
	if (num <= 0)
		return true;
	for (int i = 0; i < 16; i++) {
		if (IsEntityTouching3D(pEntities[i]))
			return false;
	}
	return true;
}

bool CGarage::IsPlayerOutsideGarage()
{
	if (FindPlayerVehicle())
		return IsEntityEntirelyOutside(FindPlayerVehicle(), 0.0f);
	return IsEntityEntirelyOutside(FindPlayerPed(), 0.0f);
}

bool CGarage::IsEntityTouching3D(CEntity* pEntity)
{
	float radius = pEntity->GetBoundRadius();
	if (m_fInfX - radius > pEntity->GetPosition().x || m_fSupX + radius < pEntity->GetPosition().x ||
		m_fInfY - radius > pEntity->GetPosition().y || m_fSupY + radius < pEntity->GetPosition().y ||
		m_fInfZ - radius > pEntity->GetPosition().z || m_fSupZ + radius < pEntity->GetPosition().z)
		return false;
	CColModel* pColModel = pEntity->GetColModel();
	for (int i = 0; i < pColModel->numSpheres; i++) {
		CVector pos = pEntity->GetMatrix() * pColModel->spheres[i].center;
		radius = pColModel->spheres[i].radius;
		if (IsPointInsideGarage(pos, radius))
			return true;
	}
	return false;
}

bool CGarage::EntityHasASphereWayOutsideGarage(CEntity * pEntity, float fMargin)
{
	CColModel* pColModel = pEntity->GetColModel();
	for (int i = 0; i < pColModel->numSpheres; i++) {
		CVector pos = pEntity->GetMatrix() * pColModel->spheres[i].center;
		float radius = pColModel->spheres[i].radius;
		if (!IsPointInsideGarage(pos, fMargin + radius))
			return true;
	}
	return false;
}

bool CGarage::IsAnyOtherCarTouchingGarage(CVehicle * pException)
{
	uint32 i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle || pVehicle == pException || pVehicle->GetStatus() == STATUS_WRECKED)
			continue;
		if (!IsEntityTouching3D(pVehicle))
			continue;
		CColModel* pColModel = pVehicle->GetColModel();
		for (int i = 0; i < pColModel->numSpheres; i++) {
			CVector pos = pVehicle->GetMatrix() * pColModel->spheres[i].center;
			float radius = pColModel->spheres[i].radius;
			if (IsPointInsideGarage(pos, radius))
				return true;
		}
	}
	return false;
}

void CGarage::ThrowCarsNearDoorOutOfGarage(CVehicle* pException)
{
	uint32 i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle || pVehicle == pException)
			continue;
		if (!IsEntityTouching3D(pVehicle))
			continue;
		CColModel* pColModel = pVehicle->GetColModel();
		for (int i = 0; i < pColModel->numSpheres; i++) {
			CVector pos = pVehicle->GetMatrix() * pColModel->spheres[i].center;
			float radius = pColModel->spheres[i].radius;
			if (!IsPointInsideGarage(pos, 0.0f)) {
				CVector vecDirectionAway(pVehicle->GetPosition().x - GetGarageCenterX(), pVehicle->GetPosition().y - GetGarageCenterY(), 0.0f);
				vecDirectionAway.Normalise();
				pVehicle->AddToMoveSpeed(vecDirectionAway * CTimer::GetTimeStepInSeconds());
			}
		}
	}
}

bool CGarage::IsAnyOtherPedTouchingGarage(CPed * pException)
{
	uint32 i = CPools::GetPedPool()->GetSize();
	while (i--) {
		CPed* pPed = CPools::GetPedPool()->GetSlot(i);
		if (!pPed || pPed == pException)
			continue;
		if (!IsEntityTouching3D(pPed))
			continue;
		CColModel* pColModel = pException->GetColModel();
		for (int i = 0; i < pColModel->numSpheres; i++) {
			CVector pos = pPed->GetMatrix() * pColModel->spheres[i].center;
			float radius = pColModel->spheres[i].radius;
			if (IsPointInsideGarage(pos, radius))
				return true;
		}
	}
	return false;
}

bool CGarage::IsAnyCarBlockingDoor()
{
	uint32 i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle)
			continue;
		if (!IsEntityTouching3D(pVehicle))
			continue;
		CColModel* pColModel = pVehicle->GetColModel();
		for (int i = 0; i < pColModel->numSpheres; i++) {
			CVector pos = pVehicle->GetMatrix() * pColModel->spheres[i].center;
			float radius = pColModel->spheres[i].radius;
			if (!IsPointInsideGarage(pos, radius))
				return true;
		}
	}
	return false;
}

int32 CGarage::CountCarsWithCenterPointWithinGarage(CEntity * pException)
{
	int32 total = 0;
	uint32 i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle || pVehicle == pException)
			continue;
		if (IsPointInsideGarage(pVehicle->GetPosition()))
			total++;
	}
	return total;
}

void CGarage::RemoveCarsBlockingDoorNotInside()
{
	uint32 i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle)
			continue;
		if (!IsEntityTouching3D(pVehicle))
			continue;
		if (!IsPointInsideGarage(pVehicle->GetPosition())) {
			if (!pVehicle->bIsLocked && pVehicle->CanBeDeleted()) {
				CWorld::Remove(pVehicle);
				delete pVehicle;
#ifndef FIX_BUGS
				return;
#endif
			}
		}
	}
}

void CGarages::PrintMessages()
{
	if (CTimer::GetTimeInMilliseconds() > MessageStartTime && CTimer::GetTimeInMilliseconds() < MessageEndTime) {
		// CRadar::m_FadeDownRadar = true; // TODO
		CFont::DrawFonts();
		float x_scale = FrontEndMenuManager.m_PrefsUseWideScreen ? 0.34506f : 0.3834f;
		CFont::SetScale(PSP_SCREEN_SCALE_X(x_scale), PSP_SCREEN_SCALE_Y(0.71f));
		CFont::SetPropOn();
		CFont::SetJustifyOff();
		CFont::SetBackgroundOff();
		CFont::SetCentreOn();
		CFont::SetFontStyle(FONT_LOCALE(FONT_STANDARD));
		CFont::SetColor(CRGBA(27, 89, 130, 255));
		CFont::SetDropShadowPosition(2);
		CFont::SetDropColor(CRGBA(0, 0, 0, 255));
		CFont::SetCentreSize(PSP_SCREEN_SCALE_X(454.0f));
		float y_offset = PSP_SCREEN_SCALE_Y(170.0f);

		if (MessageNumberInString2 >= 0) {
			CMessages::InsertNumberInString(TheText.Get(MessageIDString), MessageNumberInString, MessageNumberInString2, -1, -1, -1, -1, gUString);
			CFont::PrintString(SCREEN_WIDTH / 2, y_offset - SCREEN_SCALE_Y(30.0f), gUString);
		}
		else if (MessageNumberInString >= 0) {
			CMessages::InsertNumberInString(TheText.Get(MessageIDString), MessageNumberInString, -1, -1, -1, -1, -1, gUString);
			CFont::PrintString(SCREEN_WIDTH / 2, y_offset - SCREEN_SCALE_Y(30.0f), gUString);
		}
		else {
			CFont::PrintString(SCREEN_WIDTH / 2, y_offset, TheText.Get(MessageIDString));
		}
	}
}

bool CGarages::IsCarSprayable(CVehicle * pVehicle)
{
	switch (pVehicle->GetModelIndex()) {
	case MI_FIRETRUCK:
	case MI_AMBULAN:
	case MI_FBICAR:
	case MI_POLICE:
	case MI_ENFORCER:
	case MI_BUS:
	case MI_RHINO:
	case MI_BARRACKS:
	case MI_DODO:
	case MI_COACH:
		return false;
	default:
		break;
	}
	return true;
}

void CGarage::UpdateDoorsHeight()
{
	RefreshDoorPointers(false);
	if (m_pDoor1) {
		m_pDoor1->GetMatrix().GetPosition().z = m_fDoorPos + m_fDoor1Z;
		if (m_bRotatedDoor) {
			CVector pos;
			pos.x = m_fDoor1X + m_fDoorPos * m_pDoor1->GetForward().y * 5.0f / 6.0f;
			pos.y = m_fDoor1Y - m_fDoorPos * m_pDoor1->GetForward().x * 5.0f / 6.0f;
			pos.z = m_pDoor1->GetPosition().z;
			m_pDoor1->SetPosition(pos);
			BuildRotatedDoorMatrix(m_pDoor1, m_fDoorPos / m_fDoorHeight);
		}
		m_pDoor1->GetMatrix().UpdateRW();
		m_pDoor1->UpdateRwFrame();
	}
	if (m_pDoor2) {
		m_pDoor2->GetMatrix().GetPosition().z = m_fDoorPos + m_fDoor2Z;
		if (m_bRotatedDoor) {
			CVector pos;
			pos.x = m_fDoor2X + m_fDoorPos * m_pDoor2->GetForward().y * 5.0f / 6.0f;
			pos.y = m_fDoor2Y - m_fDoorPos * m_pDoor2->GetForward().x * 5.0f / 6.0f;
			pos.z = m_pDoor2->GetPosition().z;
			m_pDoor2->SetPosition(pos);
			BuildRotatedDoorMatrix(m_pDoor2, m_fDoorPos / m_fDoorHeight);
		}
		m_pDoor2->GetMatrix().UpdateRW();
		m_pDoor2->UpdateRwFrame();
	}
}

void CGarage::BuildRotatedDoorMatrix(CEntity * pDoor, float fPosition)
{
	float fAngle = -fPosition * HALFPI;
	CVector up(-Sin(fAngle) * pDoor->GetForward().y, Sin(fAngle) * pDoor->GetForward().x, Cos(fAngle));
	pDoor->GetRight() = CrossProduct(up, pDoor->GetForward());
	pDoor->GetUp() = up;
}

void CGarage::UpdateCrusherAngle()
{
	RefreshDoorPointers(false);
	m_pDoor2->GetMatrix().SetRotateXOnly(TWOPI - m_fDoorPos);
	m_pDoor2->GetMatrix().UpdateRW();
	m_pDoor2->UpdateRwFrame();
}

void CGarage::UpdateCrusherShake(float X, float Y)
{
	/*
	RefreshDoorPointers(false);
	m_pDoor1->GetMatrix().GetPosition().x += X;
	m_pDoor1->GetMatrix().GetPosition().y += Y;
	m_pDoor1->GetMatrix().UpdateRW();
	m_pDoor1->UpdateRwFrame();
	m_pDoor1->GetMatrix().GetPosition().x -= X;
	m_pDoor1->GetMatrix().GetPosition().y -= Y;
	m_pDoor2->GetMatrix().GetPosition().x += X;
	m_pDoor2->GetMatrix().GetPosition().y += Y;
	m_pDoor2->GetMatrix().UpdateRW();
	m_pDoor2->UpdateRwFrame();
	m_pDoor2->GetMatrix().GetPosition().x -= X;
	m_pDoor2->GetMatrix().GetPosition().y -= Y;
	*/
}

void CGarage::RefreshDoorPointers(bool bCreate)
{
	bool bNeedToFindDoorEntities = bCreate || m_bRecreateDoorOnNextRefresh;
	m_bRecreateDoorOnNextRefresh = false;
	if (m_pDoor1) {
		if (m_bDoor1IsDummy) {
			if (CPools::GetDummyPool()->GetIsFree(CPools::GetDummyPool()->GetJustIndex_NoFreeAssert((CDummy*)m_pDoor1)))
				bNeedToFindDoorEntities = true;
			else {
				if (m_bDoor1PoolIndex != (CPools::GetDummyPool()->GetIndex((CDummy*)m_pDoor1) & 0x7F))
					bNeedToFindDoorEntities = true;
				if (!CGarages::IsModelIndexADoor(m_pDoor1->GetModelIndex()))
					bNeedToFindDoorEntities = true;
			}
		}
		else {
			if (CPools::GetObjectPool()->GetIsFree(CPools::GetObjectPool()->GetJustIndex_NoFreeAssert((CObject*)m_pDoor1)))
				bNeedToFindDoorEntities = true;
			else {
				if (m_bDoor1PoolIndex != (CPools::GetObjectPool()->GetIndex((CObject*)m_pDoor1) & 0x7F))
					bNeedToFindDoorEntities = true;
				if (!CGarages::IsModelIndexADoor(m_pDoor1->GetModelIndex()))
					bNeedToFindDoorEntities = true;
			}
		}
	}
	if (m_pDoor2) {
		if (m_bDoor2IsDummy) {
			if (CPools::GetDummyPool()->GetIsFree(CPools::GetDummyPool()->GetJustIndex_NoFreeAssert((CDummy*)m_pDoor2)))
				bNeedToFindDoorEntities = true;
			else {
				if (m_bDoor2PoolIndex != (CPools::GetDummyPool()->GetIndex((CDummy*)m_pDoor2) & 0x7F))
					bNeedToFindDoorEntities = true;
				if (!CGarages::IsModelIndexADoor(m_pDoor2->GetModelIndex()))
					bNeedToFindDoorEntities = true;
			}
		}
		else {
			if (CPools::GetObjectPool()->GetIsFree(CPools::GetObjectPool()->GetJustIndex_NoFreeAssert((CObject*)m_pDoor2)))
				bNeedToFindDoorEntities = true;
			else {
				if (m_bDoor2PoolIndex != (CPools::GetObjectPool()->GetIndex((CObject*)m_pDoor2) & 0x7F))
					bNeedToFindDoorEntities = true;
				if (!CGarages::IsModelIndexADoor(m_pDoor2->GetModelIndex()))
					bNeedToFindDoorEntities = true;
			}
		}
	}
	if (bNeedToFindDoorEntities)
		FindDoorsEntities();
}

void CGarages::TriggerMessage(const char* text, int16 num1, uint16 time, int16 num2)
{
	if (strcmp(text, MessageIDString) == 0 &&
		CTimer::GetTimeInMilliseconds() >= MessageStartTime &&
		CTimer::GetTimeInMilliseconds() <= MessageEndTime) {
		if (CTimer::GetTimeInMilliseconds() - MessageStartTime <= 500)
			return;
		MessageStartTime = CTimer::GetTimeInMilliseconds() - 500;
		MessageEndTime = CTimer::GetTimeInMilliseconds() - 500 + time;
	}
	else {
		CMessages::AddToPreviousBriefArray(TheText.Get(text), -1, -1, -1, -1, -1, -1, nil);
		strcpy(MessageIDString, text);
		MessageStartTime = CTimer::GetTimeInMilliseconds();
		MessageEndTime = CTimer::GetTimeInMilliseconds() + time;
	}
	MessageNumberInString = num1;
	MessageNumberInString2 = num2;
}

void CGarages::SetTargetCarForMissonGarage(int16 garage, CVehicle* pVehicle)
{
	assert(garage >= 0 && garage < NUM_GARAGES);
	if (pVehicle) {
		aGarages[garage].m_pTarget = pVehicle;
		aGarages[garage].m_pTarget->RegisterReference((CEntity**)&aGarages[garage].m_pTarget);
		if (aGarages[garage].m_eGarageState == GS_CLOSEDCONTAINSCAR)
			aGarages[garage].m_eGarageState = GS_FULLYCLOSED;
	}
	else
		aGarages[garage].m_pTarget = nil;
}

bool CGarages::HasCarBeenDroppedOffYet(int16 garage)
{
	return aGarages[garage].m_eGarageState == GS_CLOSEDCONTAINSCAR;
}

void CGarages::DeActivateGarage(int16 garage)
{
	aGarages[garage].m_bDeactivated = true;
}

void CGarages::ActivateGarage(int16 garage)
{
	aGarages[garage].m_bDeactivated = false;
	if (aGarages[garage].m_eGarageType == GARAGE_FORCARTOCOMEOUTOF && aGarages[garage].m_eGarageState == GS_FULLYCLOSED)
		aGarages[garage].m_eGarageState = GS_OPENING;
}

int32 CGarages::QueryCarsCollected(int16 garage)
{
	return 0;
}

bool CGarages::HasImportExportGarageCollectedThisCar(int16 garage, int8 car)
{
	uint32 total;
	return CarTypesCollected[GetCarsCollectedIndexForGarageType(aGarages[garage].m_eGarageType, total)] & (BIT(car));
}

bool CGarages::IsGarageOpen(int16 garage)
{
	return aGarages[garage].IsOpen();
}

bool CGarages::IsGarageClosed(int16 garage)
{
	return aGarages[garage].IsClosed();
}

bool CGarages::HasThisCarBeenCollected(int16 garage, uint8 id)
{
	return aGarages[garage].m_bCollectedCarsState & BIT(id);
}

bool CGarage::DoesCraigNeedThisCar(int32 mi)
{
	uint32 total;
	int ct = CGarages::GetCarsCollectedIndexForGarageType(m_eGarageType, total);
	for (int i = 0; i < total; i++) {
		if (mi == gaCarsToCollectInCraigsGarages[ct][i] || (gaCarsToCollectInCraigsGarages[ct][i] == MI_CHEETAH && mi == MI_VICECHEE))
			return (CGarages::CarTypesCollected[ct] & BIT(i)) == 0;
	}
	return false;
}

bool CGarage::HasCraigCollectedThisCar(int32 mi)
{
	uint32 total;
	int ct = CGarages::GetCarsCollectedIndexForGarageType(m_eGarageType, total);
	for (int i = 0; i < total; i++) {
		if (mi == gaCarsToCollectInCraigsGarages[ct][i])
			return CGarages::CarTypesCollected[ct] & BIT(i);
	}
	return false;
}

bool CGarage::MarkThisCarAsCollectedForCraig(int32 mi)
{
	uint32 total;
	int ct = CGarages::GetCarsCollectedIndexForGarageType(m_eGarageType, total);
	int index;
	for (index = 0; index < total; index++) {
		if (mi == gaCarsToCollectInCraigsGarages[ct][index])
			break;
	}
	if (index >= total)
		return false;
	CGarages::CarTypesCollected[ct] |= BIT(index);
	for (int i = 0; i < total; i++) {
		if ((CGarages::CarTypesCollected[ct] & BIT(i)) == 0) {
			return false;
		}
	}
	return true;
}

void CGarage::OpenThisGarage()
{
	if (m_eGarageState == GS_FULLYCLOSED || m_eGarageState == GS_CLOSING || m_eGarageState == GS_CLOSEDCONTAINSCAR)
		m_eGarageState = GS_OPENING;
}

void CGarage::CloseThisGarage()
{
	if (m_eGarageState == GS_OPENED || m_eGarageState == GS_OPENING)
		m_eGarageState = GS_CLOSING;
}

float CGarage::CalcDistToGarageRectangleSquared(float X, float Y)
{
	float distX, distY;
	if (X < m_fInfX)
		distX = m_fInfX - X;
	else if (X > m_fSupX)
		distX = X - m_fSupX;
	else
		distX = 0.0f;
	if (Y < m_fInfY)
		distY = m_fInfY - Y;
	else if (Y > m_fSupY)
		distY = Y - m_fSupY;
	else
		distY = 0.0f;
	return SQR(distX) + SQR(distY);
}

float CGarage::CalcSmallestDistToGarageDoorSquared(float X, float Y)
{
	float dist1 = 10000000.0f;
	float dist2 = 10000000.0f;
	if (m_pDoor1)
		dist1 = SQR(m_fDoor1X - X) + SQR(m_fDoor1Y - Y);
	if (m_pDoor2)
		dist2 = SQR(m_fDoor2X - X) + SQR(m_fDoor2Y - Y);
	return Min(dist1, dist2);
}

void CGarage::FindDoorsEntities()
{
	m_pDoor1 = nil;
	m_pDoor2 = nil;
	int xstart = Max(0, CWorld::GetSectorIndexX(GetGarageCenterX() - 100.0f));
	int xend = Min(NUMSECTORS_X - 1, CWorld::GetSectorIndexX(GetGarageCenterX() + 100.0f));
	int ystart = Max(0, CWorld::GetSectorIndexY(GetGarageCenterY() - 100.0f));
	int yend = Min(NUMSECTORS_Y - 1, CWorld::GetSectorIndexY(GetGarageCenterY() + 100.0f));
	assert(xstart <= xend);
	assert(ystart <= yend);

	CWorld::AdvanceCurrentScanCode();

	for (int y = ystart; y <= yend; y++) {
		for (int x = xstart; x <= xend; x++) {
			CSector* s = CWorld::GetSector(x, y);
			FindDoorsEntitiesSectorList(s->m_lists[ENTITYLIST_OBJECTS], false);
			FindDoorsEntitiesSectorList(s->m_lists[ENTITYLIST_OBJECTS_OVERLAP], false);
			FindDoorsEntitiesSectorList(s->m_lists[ENTITYLIST_DUMMIES], true);
			FindDoorsEntitiesSectorList(s->m_lists[ENTITYLIST_DUMMIES_OVERLAP], true);
		}
	}
	if (m_pDoor1 && m_pDoor2) {
		if (m_pDoor1->GetModelIndex() != MI_CRUSHERBODY && m_pDoor1->GetModelIndex() != MI_CRUSHERLID) {
			CVector2D vecDoor1ToGarage(m_pDoor1->GetPosition().x - GetGarageCenterX(), m_pDoor1->GetPosition().y - GetGarageCenterY());
			CVector2D vecDoor2ToGarage(m_pDoor2->GetPosition().x - GetGarageCenterX(), m_pDoor2->GetPosition().y - GetGarageCenterY());
			if (DotProduct2D(vecDoor1ToGarage, vecDoor2ToGarage) > 0.0f) {
				if (vecDoor1ToGarage.MagnitudeSqr() >= vecDoor2ToGarage.MagnitudeSqr()) {
					m_pDoor1 = m_pDoor2;
					m_bDoor1IsDummy = m_bDoor2IsDummy;
				}
				m_pDoor2 = nil;
				m_bDoor2IsDummy = false;
			}
		}
	}
	if (m_pDoor1)
		m_pDoor1->bUsesCollision = true;
	if (m_pDoor2)
		m_pDoor2->bUsesCollision = true;
}

void CGarage::FindDoorsEntitiesSectorList(CPtrList& list, bool dummy)
{
	CPtrNode* node;
	for (node = list.first; node; node = node->next) {
		CEntity* pEntity = (CEntity*)node->item;
		if (pEntity->m_scanCode == CWorld::GetCurrentScanCode())
			continue;
		pEntity->m_scanCode = CWorld::GetCurrentScanCode();
		if (!pEntity || !CGarages::IsModelIndexADoor(pEntity->GetModelIndex()))
			continue;
		if (Abs(pEntity->GetPosition().x - GetGarageCenterX()) >= 20.0f ||
			Abs(pEntity->GetPosition().y - GetGarageCenterY()) >= 20.0f)
			continue;
		if (pEntity->GetModelIndex() == MI_CRUSHERBODY) {
			m_pDoor1 = pEntity;
			m_bDoor1IsDummy = dummy;
			if (dummy)
				m_bDoor1PoolIndex = (CPools::GetDummyPool()->GetIndex((CDummy*)pEntity)) & 0x7F;
			else
				m_bDoor1PoolIndex = (CPools::GetObjectPool()->GetIndex((CObject*)pEntity)) & 0x7F;
			continue;
		}
		if (pEntity->GetModelIndex() == MI_CRUSHERLID) {
			m_pDoor2 = pEntity;
			m_bDoor2IsDummy = dummy;
			if (dummy)
				m_bDoor2PoolIndex = (CPools::GetDummyPool()->GetIndex((CDummy*)pEntity)) & 0x7F;
			else
				m_bDoor2PoolIndex = (CPools::GetObjectPool()->GetIndex((CObject*)pEntity)) & 0x7F;
			continue;
		}
		if (!m_pDoor1) {
			m_pDoor1 = pEntity;
			m_bDoor1IsDummy = dummy;
			if (dummy)
				m_bDoor1PoolIndex = (CPools::GetDummyPool()->GetIndex((CDummy*)pEntity)) & 0x7F;
			else
				m_bDoor1PoolIndex = (CPools::GetObjectPool()->GetIndex((CObject*)pEntity)) & 0x7F;
			continue;
		}
		else {
			m_pDoor2 = pEntity;
			m_bDoor2IsDummy = dummy;
			if (dummy)
				m_bDoor2PoolIndex = (CPools::GetDummyPool()->GetIndex((CDummy*)pEntity)) & 0x7F;
			else
				m_bDoor2PoolIndex = (CPools::GetObjectPool()->GetIndex((CObject*)pEntity)) & 0x7F;
		}
	}
}

bool CGarages::HasResprayHappened(int16 garage)
{
	bool result = aGarages[garage].m_bResprayHappened;
	aGarages[garage].m_bResprayHappened = false;
	return result;
}

void CGarages::SetGarageDoorToRotate(int16 garage)
{
	if (aGarages[garage].m_bRotatedDoor)
		return;
	aGarages[garage].m_bRotatedDoor = true;
	aGarages[garage].m_fDoorHeight /= 2.0f;
	aGarages[garage].m_fDoorHeight -= 0.1f;
	aGarages[garage].m_fDoorPos = Min(aGarages[garage].m_fDoorHeight, aGarages[garage].m_fDoorPos);
	aGarages[garage].UpdateDoorsHeight();
}

void CGarages::SetLeaveCameraForThisGarage(int16 garage)
{
	aGarages[garage].m_bCameraFollowsPlayer = true;
}

bool CGarages::IsThisCarWithinGarageArea(int16 garage, CEntity * pCar)
{
	return aGarages[garage].IsEntityEntirelyInside3D(pCar, 0.0f);
}

bool CGarages::HasCarBeenCrushed(int32 handle)
{
	return CrushedCarId == handle;
}

void CStoredCar::StoreCar(CVehicle* pVehicle)
{
	m_nModelIndex = pVehicle->GetModelIndex();
	m_fPosX = pVehicle->GetPosition().x;
	m_fPosY = pVehicle->GetPosition().y;
	m_fPosZ = pVehicle->GetPosition().z;
	m_fForwardX = pVehicle->GetForward().x;
	m_fForwardY = pVehicle->GetForward().y;
	m_fForwardZ = pVehicle->GetForward().z;
	m_fTractionMultiplier = 1.0f;
	m_nPrimaryColor = pVehicle->m_currentColour1;
	m_nSecondaryColor = pVehicle->m_currentColour2;
	m_nRadioStation = pVehicle->m_nRadioStation;
	m_nVariationA = pVehicle->m_aExtras[0];
	m_nVariationB = pVehicle->m_aExtras[1];
	m_nFlags = 0;
	if (pVehicle->bRewardVehicle) m_nFlags |= FLAG_REWARD_VEHICLE;
	if (pVehicle->bBulletProof) m_nFlags |= FLAG_BULLETPROOF;
	if (pVehicle->bFireProof) m_nFlags |= FLAG_FIREPROOF;
	if (pVehicle->bExplosionProof) m_nFlags |= FLAG_EXPLOSIONPROOF;
	if (pVehicle->bCollisionProof) m_nFlags |= FLAG_COLLISIONPROOF;
	if (pVehicle->bMeleeProof) m_nFlags |= FLAG_MELEEPROOF;
	if (pVehicle->bTyresDontBurst) m_nFlags |= FLAG_TIRES_INVULNERABLE;
	if (pVehicle->bTakeLessDamage) m_nFlags |= FLAG_STRONG;
	if (pVehicle->bIsHeavy) m_nFlags |= FLAG_HEAVY;
	if (pVehicle->IsCar()) {
		CAutomobile* pAutomobile = (CAutomobile*)pVehicle;
		if (pAutomobile->bFixedColour) m_nFlags |= FLAG_PERMANENT_COLOUR;
		if (pAutomobile->m_bombType) m_nFlags |= FLAG_BOMB;
		if (pAutomobile->bNotDamagedUpsideDown) m_nFlags |= FLAG_NOT_DAMAGED_UPSIDEDOWN;
		m_fTractionMultiplier = pAutomobile->m_fTraction;
	}
	else if (pVehicle->IsBike()) {
		CBike* pBike = (CBike*)pVehicle;
		if (pBike->bFixedColour) m_nFlags |= FLAG_PERMANENT_COLOUR;
		m_fTractionMultiplier = pBike->m_fTraction;
	}
}

CVehicle* CStoredCar::RestoreCar()
{
	CStreaming::RequestModel(m_nModelIndex, STREAMFLAGS_DEPENDENCY);
	uint8 owner = RANDOM_VEHICLE;
	if (m_nFlags & FLAG_REWARD_VEHICLE)
		owner = MISSION_VEHICLE;
	if (!CStreaming::HasModelLoaded(m_nModelIndex))
		return nil;
#ifdef FIX_BUGS
	CVehicleModelInfo* pModelInfo = (CVehicleModelInfo*)CModelInfo::GetModelInfo(m_nModelIndex);
	assert(pModelInfo);
	if (pModelInfo->m_numComps != 0)
#endif
	{
		CVehicleModelInfo::SetComponentsToUse(m_nVariationA, m_nVariationB);
	}
	CVehicle* pVehicle;
	if (CModelInfo::IsBoatModel(m_nModelIndex))
		pVehicle = new CBoat(m_nModelIndex, owner);
	else if (CModelInfo::IsBikeModel(m_nModelIndex))
	{
		CBike* pBike = new CBike(m_nModelIndex, owner);
		pBike->bIsStanding = true;
		pVehicle = pBike;
	}
	else
		pVehicle = new CAutomobile(m_nModelIndex, owner);
	pVehicle->SetPosition(m_fPosX, m_fPosY, m_fPosZ);
	pVehicle->SetStatus(STATUS_ABANDONED);
	pVehicle->GetForward() = CVector(m_fForwardX, m_fForwardY, m_fForwardZ);
	pVehicle->GetRight() = CVector(m_fForwardY, -m_fForwardX, 0.0f);
	pVehicle->GetUp() = CVector(0.0f, 0.0f, 1.0f);
	pVehicle->pDriver = nil;
	pVehicle->m_currentColour1 = m_nPrimaryColor;
	pVehicle->m_currentColour2 = m_nSecondaryColor;
	pVehicle->m_nRadioStation = m_nRadioStation;
	pVehicle->bFreebies = false;
	if (pVehicle->IsCar())
	{
		((CAutomobile*)pVehicle)->m_bombType = m_nCarBombType;
#ifdef FIX_BUGS
		if (m_nCarBombType != CARBOMB_NONE)
			((CAutomobile*)pVehicle)->m_pBombRigger = FindPlayerPed();
#endif
	}
	pVehicle->bHasBeenOwnedByPlayer = true;
	pVehicle->m_nDoorLock = CARLOCK_UNLOCKED;
	if (m_nFlags & FLAG_REWARD_VEHICLE) pVehicle->bRewardVehicle = true;
	if (m_nFlags & FLAG_BULLETPROOF) pVehicle->bBulletProof = true;
	if (m_nFlags & FLAG_FIREPROOF) pVehicle->bFireProof = true;
	if (m_nFlags & FLAG_EXPLOSIONPROOF) pVehicle->bExplosionProof = true;
	if (m_nFlags & FLAG_COLLISIONPROOF) pVehicle->bCollisionProof = true;
	if (m_nFlags & FLAG_MELEEPROOF) pVehicle->bMeleeProof = true;
	if (m_nFlags & FLAG_TIRES_INVULNERABLE) pVehicle->bTyresDontBurst = true;
	if (m_nFlags & FLAG_STRONG) pVehicle->bTakeLessDamage = true;
	if (m_nFlags & FLAG_HEAVY) {
		pVehicle->bIsHeavy = true;
		pVehicle->m_fMass = pVehicle->pHandling->GetMass();
		pVehicle->m_fTurnMass = pVehicle->pHandling->GetTurnMass();
	}
	else {
		pVehicle->bIsHeavy = false;
		pVehicle->m_fMass = pVehicle->pHandling->GetMass() * 3.0f;
		pVehicle->m_fTurnMass = pVehicle->pHandling->GetTurnMass() * 5.0f;
	}
	if (pVehicle->IsCar()) {
		CAutomobile* pAutomobile = (CAutomobile*)pVehicle;
		if (m_nFlags & FLAG_PERMANENT_COLOUR) pAutomobile->bFixedColour = true;
		if (m_nFlags & FLAG_BOMB) pAutomobile->m_bombType = CARBOMB_TIMED;
		if (m_nFlags & FLAG_NOT_DAMAGED_UPSIDEDOWN) pAutomobile->bNotDamagedUpsideDown = true;
		m_fTractionMultiplier = pAutomobile->m_fTraction;
	}
	else if (pVehicle->IsBike()) {
		CBike* pBike = (CBike*)pVehicle;
		if (m_nFlags & FLAG_PERMANENT_COLOUR) pBike->bFixedColour = true;
		m_fTractionMultiplier = pBike->m_fTraction;
	}
	return pVehicle;
}

void CGarage::StoreAndRemoveCarsForThisHideout(CStoredCar* aCars, int32 nMax)
{
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++)
		aCars[i].Clear();
	int i = CPools::GetVehiclePool()->GetSize();
	int index = 0;
	while (i--) {
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle)
			continue;
		if (IsPointInsideGarage(pVehicle->GetPosition())) {
#if defined GTA_PS2 || defined GTA_MOBILE
			if (pVehicle->GetStatus() == STATUS_WRECKED) {
				CWorld::Players[CWorld::PlayerInFocus].CancelPlayerEnteringCars(pVehicle);
				CWorld::Remove(pVehicle);
				delete pVehicle;
			}
			else if (pVehicle->m_bombType == CARBOMB_NONE || pVehicle->bRewardVehicle) // <- probably condition looked different
#endif
			{
				if (pVehicle->VehicleCreatedBy != MISSION_VEHICLE || pVehicle->bRewardVehicle) {
					if (index < Max(NUM_GARAGE_STORED_CARS, nMax) && !EntityHasASphereWayOutsideGarage(pVehicle, 1.0f))
						aCars[index++].StoreCar(pVehicle);
					CWorld::Players[CWorld::PlayerInFocus].CancelPlayerEnteringCars(pVehicle);
					CWorld::Remove(pVehicle);
					delete pVehicle;
				}
			}
		}
	}
	// why?
	for (i = index; i < NUM_GARAGE_STORED_CARS; i++)
		aCars[i].Clear();
}

bool CGarage::RestoreCarsForThisHideout(CStoredCar* aCars)
{
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++) {
		if (aCars[i].HasCar()) {
			CVehicle* pVehicle = aCars[i].RestoreCar();
			if (pVehicle) {
				CWorld::Add(pVehicle);
				aCars[i].Clear();
			}
		}
	}
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++) {
		if (aCars[i].HasCar())
			return false;
	}
	return true;
}

bool CGarages::IsPointInAGarageCameraZone(CVector point)
{
#ifdef FIX_BUGS
	for (uint32 i = 0; i < NumGarages; i++) {
#else
	for (int i = 0; i < NUM_GARAGES; i++) {
#endif
		switch (aGarages[i].m_eGarageType) {
		case GARAGE_NONE:
			break;
		case GARAGE_COLLECTCARS_1:
		case GARAGE_COLLECTCARS_2:
		case GARAGE_COLLECTCARS_3:
		case GARAGE_COLLECTCARS_4:
			if (aGarages[i].IsPointInsideGarage(point, MARGIN_FOR_CAMERA_COLLECTCARS))
				return true;
			break;
		default:
			if (aGarages[i].IsPointInsideGarage(point, MARGIN_FOR_CAMERA_DEFAULT))
				return true;
			break;
		}
	}
	return false;
}

bool CGarages::CameraShouldBeOutside()
{
	return bCamShouldBeOutisde;
}

void CGarages::GivePlayerDetonator()
{
	CPlayerPed* pPed = FindPlayerPed();
	int slot = CWeaponInfo::GetWeaponInfo(WEAPONTYPE_DETONATOR)->m_nWeaponSlot;
	pPed->GiveWeapon(WEAPONTYPE_DETONATOR, 1);
	pPed->GetWeapon(pPed->GetWeaponSlot(WEAPONTYPE_DETONATOR)).m_eWeaponState = WEAPONSTATE_READY;
	pPed->m_nSelectedWepSlot = slot;
	if (pPed->m_storedWeapon != WEAPONTYPE_UNIDENTIFIED)
		pPed->m_storedWeapon = WEAPONTYPE_DETONATOR;
}

float CGarages::FindDoorHeightForMI(int32 mi)
{
	return CModelInfo::GetColModel(mi)->boundingBox.max.z - CModelInfo::GetColModel(mi)->boundingBox.min.z - 0.1f;
}

void CGarage::TidyUpGarage()
{
	uint32 i = CPools::GetVehiclePool()->GetSize();
#ifdef FIX_BUGS
	while (i--) {
#else
	while (--i) {
#endif
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (pVehicle && (pVehicle->IsCar() || pVehicle->IsBike())) {
			if (IsPointInsideGarage(pVehicle->GetPosition())) {
				if (pVehicle->GetStatus() == STATUS_WRECKED || pVehicle->GetUp().z < 0.5f) {
					CWorld::Remove(pVehicle);
					delete pVehicle;
				}
			}
		}
	}
}

void CGarage::TidyUpGarageClose()
{
	uint32 i = CPools::GetVehiclePool()->GetSize();
#ifdef FIX_BUGS
	while (i--) {
#else
	while (--i) {
#endif
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle)
			continue;
		if ((!pVehicle->IsCar() && !pVehicle->IsBike()) || pVehicle->GetStatus() != STATUS_WRECKED || !IsEntityTouching3D(pVehicle))
			continue;
		bool bRemove = false;
		if (m_eGarageState != GS_FULLYCLOSED) {
			CColModel* pColModel = pVehicle->GetColModel();
			for (int i = 0; i < pColModel->numSpheres; i++) {
				CVector pos = pVehicle->GetMatrix() * pColModel->spheres[i].center;
				float radius = pColModel->spheres[i].radius;
				if (!IsPointInsideGarage(pos, radius))
					bRemove = true;
			}
		}
		else
			bRemove = true;
		if (bRemove) {
			// no MISSION_VEHICLE check???
			CWorld::Remove(pVehicle);
			delete pVehicle;
		}
	}
}

void CGarages::PlayerArrestedOrDied()
{
	static int GarageToBeTidied = 0; // lol
#ifdef FIX_BUGS
	for (uint32 i = 0; i < NumGarages; i++) {
#else
	for (int i = 0; i < NUM_GARAGES; i++) {
#endif
		if (aGarages[i].m_eGarageType != GARAGE_NONE)
			aGarages[i].PlayerArrestedOrDied();
	}
	MessageEndTime = 0;
	MessageStartTime = 0;
}

void CGarage::PlayerArrestedOrDied()
{
	switch (m_eGarageType) {
	case GARAGE_MISSION:
	case GARAGE_COLLECTORSITEMS:
	case GARAGE_COLLECTSPECIFICCARS:
	case GARAGE_COLLECTCARS_1:
	case GARAGE_COLLECTCARS_2:
	case GARAGE_COLLECTCARS_3:
	case GARAGE_FORCARTOCOMEOUTOF:
	case GARAGE_CRATE_GARAGE:
	case GARAGE_MISSION_KEEPCAR:
	case GARAGE_FOR_SCRIPT_TO_OPEN:
	case GARAGE_HIDEOUT_ONE:
	case GARAGE_HIDEOUT_TWO:
	case GARAGE_HIDEOUT_THREE:
	case GARAGE_FOR_SCRIPT_TO_OPEN_AND_CLOSE:
	case GARAGE_KEEPS_OPENING_FOR_SPECIFIC_CAR:
	case GARAGE_MISSION_KEEPCAR_REMAINCLOSED:
	case GARAGE_COLLECTCARS_4:
	case GARAGE_FOR_SCRIPT_TO_OPEN_FOR_CAR:
	case GARAGE_HIDEOUT_FOUR:
	case GARAGE_HIDEOUT_FIVE:
	case GARAGE_HIDEOUT_SIX:
	case GARAGE_HIDEOUT_SEVEN:
	case GARAGE_HIDEOUT_EIGHT:
	case GARAGE_HIDEOUT_NINE:
	case GARAGE_HIDEOUT_TEN:
	case GARAGE_HIDEOUT_ELEVEN:
	case GARAGE_HIDEOUT_TWELVE:
		switch (m_eGarageState) {
		case GS_OPENED:
		case GS_CLOSING:
		case GS_OPENING:
			m_eGarageState = GS_CLOSING;
			break;
		default:
			break;
		}
		break;
	case GARAGE_BOMBSHOP1:
	case GARAGE_BOMBSHOP2:
	case GARAGE_BOMBSHOP3:
	case GARAGE_RESPRAY:
	case GARAGE_CRUSHER:
		switch (m_eGarageState) {
		case GS_FULLYCLOSED:
		case GS_CLOSING:
		case GS_OPENING:
			m_eGarageState = GS_OPENING;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CGarage::CenterCarInGarage(CVehicle* pVehicle)
{
	if (IsAnyOtherCarTouchingGarage(FindPlayerVehicle()))
		return;
	if (IsAnyOtherPedTouchingGarage(FindPlayerPed()))
		return;
	CVector pos = pVehicle->GetPosition();
	float garageX = GetGarageCenterX();
	float garageY = GetGarageCenterY();
	float offsetX = garageX - pos.x;
	float offsetY = garageY - pos.y;
	float offsetZ = pos.z - pos.z;
	float distance = CVector(offsetX, offsetY, offsetZ).Magnitude();
	if (distance < RESPRAY_CENTERING_COEFFICIENT) {
		pVehicle->GetMatrix().GetPosition().x = GetGarageCenterX();
		pVehicle->GetMatrix().GetPosition().y = GetGarageCenterY();
	}
	else {
		pVehicle->GetMatrix().GetPosition().x += offsetX * RESPRAY_CENTERING_COEFFICIENT / distance;
		pVehicle->GetMatrix().GetPosition().y += offsetY * RESPRAY_CENTERING_COEFFICIENT / distance;
	}
	if (!IsEntityEntirelyInside3D(pVehicle, 0.3f))
		pVehicle->SetPosition(pos);
}

void CGarages::CloseHideOutGaragesBeforeSave()
{
#ifdef FIX_BUGS
	for (uint32 i = 0; i < NumGarages; i++) {
#else
	for (int i = 0; i < NUM_GARAGES; i++) {
#endif
		if (!IsThisGarageTypeSafehouse(aGarages[i].m_eGarageType))
			continue;
		if (aGarages[i].m_eGarageState != GS_FULLYCLOSED) {
			aGarages[i].m_eGarageState = GS_FULLYCLOSED;
			aGarages[i].StoreAndRemoveCarsForThisHideout(aCarsInSafeHouses[FindSafeHouseIndexForGarageType(aGarages[i].m_eGarageType)], NUM_GARAGE_STORED_CARS);
			aGarages[i].RemoveCarsBlockingDoorNotInside();
			aGarages[i].m_fDoorPos = 0.0f;
			aGarages[i].UpdateDoorsHeight();
		}
	}
}

int32 CGarages::CountCarsInHideoutGarage(uint8 type)
{
	int32 total = 0;
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++) {
		total += aCarsInSafeHouses[FindSafeHouseIndexForGarageType(type)][i].HasCar();
	}
	return total;
}

bool CGarages::IsPointWithinHideOutGarage(Const CVector& point)
{
#ifdef FIX_BUGS
	for (uint32 i = 0; i < NumGarages; i++) {
#else
	for (int i = 0; i < NUM_GARAGES; i++) {
#endif
		switch (aGarages[i].m_eGarageType) {
		case GARAGE_HIDEOUT_ONE:
		case GARAGE_HIDEOUT_TWO:
		case GARAGE_HIDEOUT_THREE:
		case GARAGE_HIDEOUT_FOUR:
		case GARAGE_HIDEOUT_FIVE:
		case GARAGE_HIDEOUT_SIX:
		case GARAGE_HIDEOUT_SEVEN:
		case GARAGE_HIDEOUT_EIGHT:
		case GARAGE_HIDEOUT_NINE:
		case GARAGE_HIDEOUT_TEN:
		case GARAGE_HIDEOUT_ELEVEN:
		case GARAGE_HIDEOUT_TWELVE:
			if (aGarages[i].IsPointInsideGarage(point))
				return true;
		default: break;
		}
	}
	return false;
}

bool CGarages::IsPointWithinAnyGarage(Const CVector& point)
{
#ifdef FIX_BUGS
	for (uint32 i = 0; i < NumGarages; i++) {
#else
	for (int i = 0; i < NUM_GARAGES; i++) {
#endif
		switch (aGarages[i].m_eGarageType) {
		case GARAGE_NONE:
			continue;
		default:
			if (aGarages[i].IsPointInsideGarage(point))
				return true;
		}
	}
	return false;
}

void CGarages::SetAllDoorsBackToOriginalHeight()
{
#ifdef FIX_BUGS
	for (uint32 i = 0; i < NumGarages; i++) {
#else
	for (int i = 0; i < NUM_GARAGES; i++) {
#endif
		switch (aGarages[i].m_eGarageType) {
		case GARAGE_NONE:
			continue;
		default:
			aGarages[i].RefreshDoorPointers(true);
			if (aGarages[i].m_pDoor1) {
				aGarages[i].m_pDoor1->GetMatrix().GetPosition().x = aGarages[i].m_fDoor1X;
				aGarages[i].m_pDoor1->GetMatrix().GetPosition().y = aGarages[i].m_fDoor1Y;
				aGarages[i].m_pDoor1->GetMatrix().GetPosition().z = aGarages[i].m_fDoor1Z;
				if (aGarages[i].m_pDoor1->IsObject())
					((CObject*)aGarages[i].m_pDoor1)->m_objectMatrix.GetPosition().z = aGarages[i].m_fDoor1Z;
				if (aGarages[i].m_bRotatedDoor)
					aGarages[i].BuildRotatedDoorMatrix(aGarages[i].m_pDoor1, 0.0f);
				aGarages[i].m_pDoor1->GetMatrix().UpdateRW();
				aGarages[i].m_pDoor1->UpdateRwFrame();
			}
			if (aGarages[i].m_pDoor2) {
				aGarages[i].m_pDoor2->GetMatrix().GetPosition().x = aGarages[i].m_fDoor2X;
				aGarages[i].m_pDoor2->GetMatrix().GetPosition().y = aGarages[i].m_fDoor2Y;
				aGarages[i].m_pDoor2->GetMatrix().GetPosition().z = aGarages[i].m_fDoor2Z;
				if (aGarages[i].m_pDoor2->IsObject())
					((CObject*)aGarages[i].m_pDoor2)->m_objectMatrix.GetPosition().z = aGarages[i].m_fDoor2Z;
				if (aGarages[i].m_bRotatedDoor)
					aGarages[i].BuildRotatedDoorMatrix(aGarages[i].m_pDoor2, 0.0f);
				aGarages[i].m_pDoor2->GetMatrix().UpdateRW();
				aGarages[i].m_pDoor2->UpdateRwFrame();
			}
		}
	}
}

#define GARAGE_SIZE 208

void CGarages::Save(uint8 * buf, uint32 * size)
{
INITSAVEBUF
	*size = (6 * sizeof(uint32) + TOTAL_COLLECTCARS_GARAGES * sizeof(*CarTypesCollected) + sizeof(uint32) + TOTAL_HIDEOUT_GARAGES * NUM_GARAGE_STORED_CARS * sizeof(CStoredCar) + NUM_GARAGES * GARAGE_SIZE);
	CloseHideOutGaragesBeforeSave();
	WriteSaveBuf(buf, NumGarages);
	WriteSaveBuf(buf, (uint32)BombsAreFree);
	WriteSaveBuf(buf, (uint32)RespraysAreFree);
	WriteSaveBuf(buf, CarsCollected);
	WriteSaveBuf(buf, BankVansCollected);
	WriteSaveBuf(buf, PoliceCarsCollected);
	for (int i = 0; i < TOTAL_COLLECTCARS_GARAGES; i++)
		WriteSaveBuf(buf, CarTypesCollected[i]);
	WriteSaveBuf(buf, LastTimeHelpMessage);
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++) {
		for (int j = 0; j < TOTAL_HIDEOUT_GARAGES; j++) {
			WriteSaveBuf(buf, aCarsInSafeHouses[j][i]);
		}
	}
	for (int i = 0; i < NUM_GARAGES; i++) {
#ifdef COMPATIBLE_SAVES
		WriteSaveBuf(buf, aGarages[i].m_eGarageType);
		WriteSaveBuf(buf, aGarages[i].m_eGarageState);
		WriteSaveBuf(buf, aGarages[i].m_nMaxStoredCars);
		WriteSaveBuf(buf, aGarages[i].field_2);
		WriteSaveBuf(buf, aGarages[i].m_bClosingWithoutTargetCar);
		WriteSaveBuf(buf, aGarages[i].m_bDeactivated);
		WriteSaveBuf(buf, aGarages[i].m_bResprayHappened);
		ZeroSaveBuf(buf, 1);
		WriteSaveBuf(buf, aGarages[i].m_nTargetModelIndex);
		ZeroSaveBuf(buf, 4 + 4);
		WriteSaveBuf(buf, aGarages[i].m_bDoor1PoolIndex);
		WriteSaveBuf(buf, aGarages[i].m_bDoor2PoolIndex);
		WriteSaveBuf(buf, aGarages[i].m_bDoor1IsDummy);
		WriteSaveBuf(buf, aGarages[i].m_bDoor2IsDummy);
		WriteSaveBuf(buf, aGarages[i].m_bRecreateDoorOnNextRefresh);
		WriteSaveBuf(buf, aGarages[i].m_bRotatedDoor);
		WriteSaveBuf(buf, aGarages[i].m_bCameraFollowsPlayer);
		ZeroSaveBuf(buf, 1);
		WriteSaveBuf(buf, aGarages[i].m_vecCorner1);
		WriteSaveBuf(buf, aGarages[i].m_fInfZ);
		WriteSaveBuf(buf, aGarages[i].m_vDir1);
		WriteSaveBuf(buf, aGarages[i].m_vDir2);
		WriteSaveBuf(buf, aGarages[i].m_fSupZ);
		WriteSaveBuf(buf, aGarages[i].m_vecSSGaragePos);
		WriteSaveBuf(buf, aGarages[i].m_fSSGarageAngle);
		WriteSaveBuf(buf, aGarages[i].m_fDir1Len);
		WriteSaveBuf(buf, aGarages[i].m_fDir2Len);
		WriteSaveBuf(buf, aGarages[i].m_fInfX);
		WriteSaveBuf(buf, aGarages[i].m_fSupX);
		WriteSaveBuf(buf, aGarages[i].m_fInfY);
		WriteSaveBuf(buf, aGarages[i].m_fSupY);
		WriteSaveBuf(buf, aGarages[i].m_nTimeCrusherCraneActivated);
		ZeroSaveBuf(buf, 4);
		WriteSaveBuf(buf, aGarages[i].m_fDoorPos);
		WriteSaveBuf(buf, aGarages[i].m_fDoorHeight);
		WriteSaveBuf(buf, aGarages[i].m_fDoor1X);
		WriteSaveBuf(buf, aGarages[i].m_fDoor1Y);
		WriteSaveBuf(buf, aGarages[i].m_fDoor2X);
		WriteSaveBuf(buf, aGarages[i].m_fDoor2Y);
		WriteSaveBuf(buf, aGarages[i].m_fDoor1Z);
		WriteSaveBuf(buf, aGarages[i].m_fDoor2Z);
		WriteSaveBuf(buf, aGarages[i].m_nTimeToStartAction);
		WriteSaveBuf(buf, aGarages[i].m_bCollectedCarsState);
		ZeroSaveBuf(buf, 3 + 4);
		ZeroSaveBuf(buf, sizeof(aGarages[i].m_sStoredCar));
		WriteSaveBuf(buf, aGarages[i].m_bInitialized);
		ZeroSaveBuf(buf, 3);
#ifdef GTA_NETWORK
		ZeroSaveBuf(buf, 4);
#endif
		WriteSaveBuf(buf, aGarages[i].m_bSSGarageAcceptedVehicle);
		WriteSaveBuf(buf, aGarages[i].m_bLocked);
		WriteSaveBuf(buf, aGarages[i].m_nSSGarageState);
		WriteSaveBuf(buf, aGarages[i].m_bSSGarageStateChanging);
#else
		WriteSaveBuf(buf, aGarages[i]);
#endif
	}
VALIDATESAVEBUF(*size);
}

void CGarages::Load(uint8* buf, uint32 size)
{
INITSAVEBUF
	assert(size == (6 * sizeof(uint32) + TOTAL_COLLECTCARS_GARAGES * sizeof(*CarTypesCollected) + sizeof(uint32) + TOTAL_HIDEOUT_GARAGES * NUM_GARAGE_STORED_CARS * sizeof(CStoredCar) + NUM_GARAGES * GARAGE_SIZE));
	CloseHideOutGaragesBeforeSave();
	ReadSaveBuf(&NumGarages, buf);
	int32 tempInt;
	ReadSaveBuf(&tempInt, buf);
	BombsAreFree = tempInt ? true : false;
	ReadSaveBuf(&tempInt, buf);
	RespraysAreFree = tempInt ? true : false;
	ReadSaveBuf(&CarsCollected, buf);
	ReadSaveBuf(&BankVansCollected, buf);
	ReadSaveBuf(&PoliceCarsCollected, buf);
	for (int i = 0; i < TOTAL_COLLECTCARS_GARAGES; i++)
		ReadSaveBuf(&CarTypesCollected[i], buf);
	ReadSaveBuf(&LastTimeHelpMessage, buf);
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++) {
		for (int j = 0; j < TOTAL_HIDEOUT_GARAGES; j++) {
			ReadSaveBuf(&aCarsInSafeHouses[j][i], buf);
		}
	}
	for (int i = 0; i < NUM_GARAGES; i++) {
#ifdef COMPATIBLE_SAVES
		ReadSaveBuf(&aGarages[i].m_eGarageType, buf);
		ReadSaveBuf(&aGarages[i].m_eGarageState, buf);
		ReadSaveBuf(&aGarages[i].m_nMaxStoredCars, buf);
		ReadSaveBuf(&aGarages[i].field_2, buf);
		ReadSaveBuf(&aGarages[i].m_bClosingWithoutTargetCar, buf);
		ReadSaveBuf(&aGarages[i].m_bDeactivated, buf);
		ReadSaveBuf(&aGarages[i].m_bResprayHappened, buf);
		SkipSaveBuf(buf, 1);
		ReadSaveBuf(&aGarages[i].m_nTargetModelIndex, buf);
		SkipSaveBuf(buf, 4 + 4);
		ReadSaveBuf(&aGarages[i].m_bDoor1PoolIndex, buf);
		ReadSaveBuf(&aGarages[i].m_bDoor2PoolIndex, buf);
		ReadSaveBuf(&aGarages[i].m_bDoor1IsDummy, buf);
		ReadSaveBuf(&aGarages[i].m_bDoor2IsDummy, buf);
		ReadSaveBuf(&aGarages[i].m_bRecreateDoorOnNextRefresh, buf);
		ReadSaveBuf(&aGarages[i].m_bRotatedDoor, buf);
		ReadSaveBuf(&aGarages[i].m_bCameraFollowsPlayer, buf);
		SkipSaveBuf(buf, 1);
		ReadSaveBuf(&aGarages[i].m_vecCorner1, buf);
		ReadSaveBuf(&aGarages[i].m_fInfZ, buf);
		ReadSaveBuf(&aGarages[i].m_vDir1, buf);
		ReadSaveBuf(&aGarages[i].m_vDir2, buf);
		ReadSaveBuf(&aGarages[i].m_fSupZ, buf);
		ReadSaveBuf(&aGarages[i].m_vecSSGaragePos, buf);
		ReadSaveBuf(&aGarages[i].m_fSSGarageAngle, buf);
		ReadSaveBuf(&aGarages[i].m_fDir1Len, buf);
		ReadSaveBuf(&aGarages[i].m_fDir2Len, buf);
		ReadSaveBuf(&aGarages[i].m_fInfX, buf);
		ReadSaveBuf(&aGarages[i].m_fSupX, buf);
		ReadSaveBuf(&aGarages[i].m_fInfY, buf);
		ReadSaveBuf(&aGarages[i].m_fSupY, buf);
		ReadSaveBuf(&aGarages[i].m_nTimeCrusherCraneActivated, buf);
		SkipSaveBuf(buf, 4);
		ReadSaveBuf(&aGarages[i].m_fDoorPos, buf);
		ReadSaveBuf(&aGarages[i].m_fDoorHeight, buf);
		ReadSaveBuf(&aGarages[i].m_fDoor1X, buf);
		ReadSaveBuf(&aGarages[i].m_fDoor1Y, buf);
		ReadSaveBuf(&aGarages[i].m_fDoor2X, buf);
		ReadSaveBuf(&aGarages[i].m_fDoor2Y, buf);
		ReadSaveBuf(&aGarages[i].m_fDoor1Z, buf);
		ReadSaveBuf(&aGarages[i].m_fDoor2Z, buf);
		ReadSaveBuf(&aGarages[i].m_nTimeToStartAction, buf);
		ReadSaveBuf(&aGarages[i].m_bCollectedCarsState, buf);
		SkipSaveBuf(buf, 3 + 4);
		SkipSaveBuf(buf, sizeof(aGarages[i].m_sStoredCar));
		ReadSaveBuf(&aGarages[i].m_bInitialized, buf);
		SkipSaveBuf(buf, 3);
#ifdef GTA_NETWORK
		SkipSaveBuf(buf, 4);
#endif
		ReadSaveBuf(&aGarages[i].m_bSSGarageAcceptedVehicle, buf);
		ReadSaveBuf(&aGarages[i].m_bLocked, buf);
		ReadSaveBuf(&aGarages[i].m_nSSGarageState, buf);
		ReadSaveBuf(&aGarages[i].m_bSSGarageStateChanging, buf);
#else
		ReadSaveBuf(&aGarages[i], buf);
#endif
		aGarages[i].m_pDoor1 = nil;
		aGarages[i].m_pDoor2 = nil;
		aGarages[i].m_pTarget = nil;
		aGarages[i].m_bRecreateDoorOnNextRefresh = true;
		aGarages[i].RefreshDoorPointers(true);
		if (aGarages[i].m_eGarageType == GARAGE_CRUSHER)
			aGarages[i].UpdateCrusherAngle();
		else
			aGarages[i].UpdateDoorsHeight();
	}
VALIDATESAVEBUF(size);

	MessageEndTime = 0;
	bCamShouldBeOutisde = false;
	MessageStartTime = 0;
	hGarages = DMAudio.CreateEntity(AUDIOTYPE_GARAGE, (void*)1);
	if (hGarages >= 0)
		DMAudio.SetEntityStatus(hGarages, TRUE);
}

bool
CGarages::IsModelIndexADoor(uint32 id)
{
	return id == MI_GARAGEDOOR1 ||
		id == MI_GARAGEDOOR17 ||
		id == MI_GARAGEDOOR27 ||
		id == MI_GARAGEDOOR28 ||
		id == MI_GARAGEDOOR29 ||
		id == MI_GARAGEDOOR30 ||
		id == MI_GARAGEDOOR31 ||
		id == MI_GARAGEDOOR32 ||
		id == MI_GARAGEDOOR33 ||
		id == MI_GARAGEDOOR34 ||
		id == MI_GARAGEDOOR35 ||
		id == MI_GARAGEDOOR36 ||
		id == MI_GARAGEDOOR37 ||
		id == MI_GARAGEDOOR38 ||
		id == MI_GARAGEDOOR39 ||
		id == MI_CRUSHERBODY ||
		id == MI_CRUSHERLID ||
		id == MI_GARAGEDOOR2 ||
		id == MI_GARAGEDOOR3 ||
		id == MI_GARAGEDOOR4 ||
		id == MI_GARAGEDOOR5 ||
		id == MI_GARAGEDOOR6 ||
		id == MI_GARAGEDOOR7 ||
		id == MI_GARAGEDOOR9 ||
		id == MI_GARAGEDOOR10 ||
		id == MI_GARAGEDOOR11 ||
		id == MI_GARAGEDOOR12 ||
		id == MI_GARAGEDOOR13 ||
		id == MI_GARAGEDOOR14 ||
		id == MI_GARAGEDOOR15 ||
		id == MI_GARAGEDOOR16 ||
		id == MI_GARAGEDOOR18 ||
		id == MI_GARAGEDOOR19 ||
		id == MI_GARAGEDOOR20 ||
		id == MI_GARAGEDOOR21 ||
		id == MI_GARAGEDOOR22 ||
		id == MI_GARAGEDOOR23 ||
		id == MI_GARAGEDOOR24 ||
		id == MI_GARAGEDOOR25 ||
		id == MI_GARAGEDOOR26 ||
		id == MI_DOOR2_SJL;
}

void CGarages::StopCarFromBlowingUp(CAutomobile* pCar)
{
	pCar->m_fFireBlowUpTimer = 0.0f;
	pCar->m_fHealth = Max(pCar->m_fHealth, 300.0f);
	pCar->Damage.SetEngineStatus(Max(pCar->Damage.GetEngineStatus(), 275));
}

bool CGarage::Does60SecondsNeedThisCarAtAll(int mi)
{
	for (int i = 0; i < ARRAY_SIZE(gaCarsToCollectIn60Seconds); i++) {
		if (gaCarsToCollectIn60Seconds[i] == mi)
			return true;
	}
	return false;
}

bool CGarage::Does60SecondsNeedThisCar(int mi)
{
	for (int i = 0; i < ARRAY_SIZE(gaCarsToCollectIn60Seconds); i++) {
		if (gaCarsToCollectIn60Seconds[i] == mi)
			return m_bCollectedCarsState & BIT(i);
	}
	return false;
}

void CGarage::MarkThisCarAsCollectedFor60Seconds(int mi)
{
	for (int i = 0; i < ARRAY_SIZE(gaCarsToCollectIn60Seconds); i++) {
		if (gaCarsToCollectIn60Seconds[i] == mi)
			m_bCollectedCarsState |= BIT(i);
	}
}

bool CGarage::IsPlayerEntirelyInsideGarage()
{
	return IsEntityEntirelyInside3D(FindPlayerVehicle() ? (CEntity*)FindPlayerVehicle() : (CEntity*)FindPlayerPed(), 0.0f);
}

int16 CGarages::AddCrateGarage(CVector pos, float angle)
{
	CMatrix matrix;
	matrix.SetUnity();
	matrix.SetRotateZOnly(DEGTORAD(angle));
	CStreaming::RequestModel(MI_CRATE_SJL, STREAMFLAGS_DEPENDENCY);
#ifdef FIX_BUGS
	CStreaming::LoadAllRequestedModels(false);
#endif
	CObject* pCrate = new CObject(MI_CRATE_SJL, false);
	pCrate->ObjectCreatedBy = MISSION_OBJECT;
	pCrate->SetPosition(pos);
	pCrate->SetOrientation(0.0f, 0.0f, DEGTORAD(angle));
	pCrate->GetMatrix().UpdateRW();
	pCrate->UpdateRwFrame();
	pCrate->bAffectedByGravity = false;
	pCrate->m_phy_flagA08 = true;
	pCrate->bExplosionProof = true;
	pCrate->bIsStatic = false;

	CStreaming::RequestModel(MI_DOOR1_SJL, STREAMFLAGS_DEPENDENCY);
#ifdef FIX_BUGS
	CStreaming::LoadAllRequestedModels(false);
#endif
	CObject* pDoor1 = new CObject(MI_DOOR1_SJL, false);
	pDoor1->ObjectCreatedBy = MISSION_OBJECT;
	CVector vDoor1Pos = matrix * CVector(0.0f, 5.64f, 5.168f);
	pDoor1->SetPosition(vDoor1Pos);
	pDoor1->SetOrientation(0.0f, 0.0f, DEGTORAD(angle));
	pDoor1->GetMatrix().UpdateRW();
	pDoor1->UpdateRwFrame();
	pDoor1->bAffectedByGravity = false;
	pDoor1->m_phy_flagA08 = true;
	pDoor1->bExplosionProof = true;
	pDoor1->bIsStatic = false;

	CStreaming::RequestModel(MI_DOOR2_SJL, STREAMFLAGS_DEPENDENCY);
#ifdef FIX_BUGS
	CStreaming::LoadAllRequestedModels(false);
#endif
	CObject* pDoor2 = new CObject(MI_DOOR2_SJL, false);
	pDoor2->ObjectCreatedBy = MISSION_OBJECT;
	CVector vDoor2Pos = matrix * CVector(0.0f, -5.64f, 5.168f);
	pDoor2->SetPosition(vDoor2Pos);
	pDoor2->SetOrientation(0.0f, 0.0f, DEGTORAD(angle));
	pDoor2->GetMatrix().UpdateRW();
	pDoor2->UpdateRwFrame();
	pDoor2->bAffectedByGravity = false;
	pDoor2->m_phy_flagA08 = true;
	pDoor2->bExplosionProof = true;
	pDoor2->bIsStatic = false;

	CWorld::Add(pCrate);
	CWorld::Add(pDoor1);
	CWorld::Add(pDoor2);

	CVector corner = matrix * CVector(-3.0f, -3.5f, -0.5f) + pos;
	CVector xplane = matrix * CVector(0.0f, 2.0f, 0.0f) + pos;
	CVector yplane = matrix * CVector(0.0f, 0.0f, 0.0f) + pos;

	printf("Posttrans Corner[%f][%f][%f] XPlane[%f][%f][%f] YPlane[%f][%f][%f]",
		corner.x, corner.y, corner.z, xplane.x, xplane.y, xplane.z, yplane.x, yplane.y, yplane.z);
	int16 index = AddOne(corner.x, corner.y, corner.z, xplane.x, xplane.y, yplane.x, yplane.y, pos.z + 4.0f, GARAGE_CRATE_GARAGE, 0);
	SetLeaveCameraForThisGarage(index);
	CGarage* pGarage = &aGarages[index];
	pGarage->m_bSSGarageAcceptedVehicle = false;
	pGarage->m_bSSGarageStateChanging = false;
	pGarage->m_vecSSGaragePos = pos;
	pGarage->m_fSSGarageAngle = angle;
	return index;
}

#ifdef GTA_NETWORK
void CGarages::RemoveAllCrateGarages()
{
	for (uint32 i = 0; i < NUM_GARAGES; i++) {
		CGarage* pGarage = &aGarages[i];
		if (pGarage->m_eGarageType == GARAGE_CRATE_GARAGE) {
			pGarage->m_eGarageType = GARAGE_NONE;
			pGarage->m_bSSGarageStateChanging = false;
			pGarage->m_bSSGarageAcceptedVehicle = false;
			pGarage->m_pSSVehicle = nil;
			--NumGarages;
		}
	}
}

bool CGarages::HasSSGarageAcceptedVehicle(int16 garage)
{
	return aGarages[garage].m_bSSGarageAcceptedVehicle;
}

void CGarages::SetVehicleForSSGarage(bool state, int16 garage, void* pVehicle)
{
	CGarage* pGarage = &aGarages[garage];
	pGarage->m_pSSVehicle = pVehicle;
	pGarage->m_nSSGarageState = state;
	pGarage->m_bSSGarageAcceptedVehicle = false;
	if (!pVehicle) {
		if (pGarage->m_pSSTargetCar)
			pGarage->m_pSSTargetCar->CleanUpOldReference((CEntity**)pGarage->m_pSSTargetCar);
		pGarage->m_pSSTargetCar = nil;
	}
}
#endif
