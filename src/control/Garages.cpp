#include "common.h"
#include "patcher.h"
#include "Garages.h"
#include "main.h"

#include "General.h"
#include "Font.h"
#include "Hud.h"
#include "Messages.h"
#include "ModelIndices.h"
#include "Particle.h"
#include "PlayerPed.h"
#include "Replay.h"
#include "Stats.h"
#include "Text.h"
#include "Timer.h"
#include "Vehicle.h"
#include "World.h"

#define CRUSHER_GARAGE_X1 (1135.5f)
#define CRUSHER_GARAGE_Y1 (7.0f)
#define CRUSHER_GARAGE_Z1 (-1.0f)
#define CRUSHER_GARAGE_X2 (1149.5f)
#define CRUSHER_GARAGE_Y2 (63.7f)
#define CRUSHER_GARAGE_Z2 (3.5f)

#define ROTATED_DOOR_OPEN_SPEED (0.015f)
#define ROTATED_DOOR_CLOSE_SPEED (0.02f)
#define DEFAULT_DOOR_OPEN_SPEED (0.035f)
#define DEFAULT_DOOR_CLOSE_SPEED (0.04f)

#define BOMB_PRICE 1000
#define RESPRAY_PRICE 1000

#define DISTANCE_TO_CALL_OFF_CHASE 10.0f
#define DISTANCE_FOR_MRWHOOP_HACK 4.0f
#define DISTANCE_TO_ACTIVATE_GARAGE 8.0f
#define DISTANCE_TO_CLOSE_MISSION_GARAGE 30.0f
#define DISTANCE_TO_CLOSE_COLLECTCARS_GARAGE 25.0

#define TIME_TO_RESPRAY 2000

#define FREE_RESPRAY_HEALTH_THRESHOLD 970.0f
#define NUM_PARTICLES_IN_RESPRAY 200

#define KGS_OF_EXPLOSIVES_IN_BOMB 10

#define REWARD_FOR_FIRST_POLICE_CAR 5000
#define REWARD_FOR_FIRST_BANK_VAN 5000
#define MAX_POLICE_CARS_TO_COLLECT 10
#define MAX_BANK_VANS_TO_COLLECT 10

int32 &CGarages::BankVansCollected = *(int32 *)0x8F1B34;
bool &CGarages::BombsAreFree = *(bool *)0x95CD7A;
bool &CGarages::RespraysAreFree = *(bool *)0x95CD1D;
int32 &CGarages::CarsCollected = *(int32 *)0x880E18;
int32 (&CGarages::CarTypesCollected)[TOTAL_COLLECTCARS_GARAGES] = *(int32 (*)[TOTAL_COLLECTCARS_GARAGES])*(uintptr*)0x8E286C;
int32 &CGarages::CrushedCarId = *(int32 *)0x943060;
uint32 &CGarages::LastTimeHelpMessage = *(uint32 *)0x8F1B58;
int32 &CGarages::MessageNumberInString = *(int32 *)0x885BA8;
const char *CGarages::MessageIDString = (const char *)0x878358;
int32 &CGarages::MessageNumberInString2 = *(int32 *)0x8E2C14;
uint32 &CGarages::MessageStartTime = *(uint32 *)0x8F2530;
uint32 &CGarages::MessageEndTime = *(uint32 *)0x8F597C;
uint32 &CGarages::NumGarages = *(uint32 *)0x8F29F4;
bool &CGarages::PlayerInGarage = *(bool *)0x95CD83;
int32 &CGarages::PoliceCarsCollected = *(int32 *)0x941444;
uint32 &CGarages::GarageToBeTidied = *(uint32 *)0x623570;
CStoredCar(&CGarages::aCarsInSafeHouse1)[NUM_GARAGE_STORED_CARS] = *(CStoredCar(*)[NUM_GARAGE_STORED_CARS])*(uintptr*)0x6FA210;
CStoredCar(&CGarages::aCarsInSafeHouse2)[NUM_GARAGE_STORED_CARS] = *(CStoredCar(*)[NUM_GARAGE_STORED_CARS])*(uintptr*)0x6FA300;
CStoredCar(&CGarages::aCarsInSafeHouse3)[NUM_GARAGE_STORED_CARS] = *(CStoredCar(*)[NUM_GARAGE_STORED_CARS])*(uintptr*)0x6FA3F0;
int32& CGarages::AudioEntity = *(int32*)0x5ECEA8;
CGarage(&CGarages::aGarages)[NUM_GARAGES] = *(CGarage(*)[NUM_GARAGES])*(uintptr*)0x72BCD0;
bool& CGarages::bCamShouldBeOutisde = *(bool*)0x95CDB2;

void CGarages::Init(void)
{
	CrushedCarId = -1;
	NumGarages = 0;
	MessageEndTime = 0;
	MessageStartTime = 0;
	PlayerInGarage = false;
	BombsAreFree = false;
	CarsCollected = 0;
	BankVansCollected = 0;
	PoliceCarsCollected = 0;
	for (int i = 0; i < TOTAL_COLLECTCARS_GARAGES; i++)
		CarTypesCollected[i] = 0;
	LastTimeHelpMessage = 0;
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++)
		aCarsInSafeHouse1[i].Init();
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++)
		aCarsInSafeHouse2[i].Init();
	for (int i = 0; i < NUM_GARAGE_STORED_CARS; i++)
		aCarsInSafeHouse3[i].Init();
	AudioEntity = DMAudio.CreateEntity(AUDIOTYPE_GARAGE, (void*)1);
	if (AudioEntity >= 0)
		DMAudio.SetEntityStatus(AudioEntity, 1);
	AddOne(
		CRUSHER_GARAGE_X1, CRUSHER_GARAGE_Y1, CRUSHER_GARAGE_Z1,
		CRUSHER_GARAGE_X2, CRUSHER_GARAGE_Y2, CRUSHER_GARAGE_Z2,
		GARAGE_CRUSHER, 0);
}

#ifndef PS2
void CGarages::Shutdown(void)
{
	NumGarages = 0;
	if (AudioEntity < 0)
		return;
	DMAudio.DestroyEntity(AudioEntity);
	AudioEntity = AEHANDLE_NONE;
}
#endif

void CGarages::Update(void)
{
	static int GarageToBeTidied = 0;
#ifndef PS2
	if (CReplay::IsPlayingBack())
		return;
#endif
	bCamShouldBeOutisde = false;
	TheCamera.pToGarageWeAreIn = nil;
	TheCamera.pToGarageWeAreInForHackAvoidFirstPerson = nil;
	for (int i = 0; i < NUM_GARAGES; i++) {
		if (aGarages[i].IsUsed())
			aGarages[i].Update();
	}
	if ((CTimer::GetFrameCounter() & 0xF) != 0xC)
		return;
	if (++GarageToBeTidied >= 32)
		GarageToBeTidied = 0;
	if (!aGarages[GarageToBeTidied].IsUsed())
		return;
	if (aGarages[GarageToBeTidied].IsClose())
		aGarages[GarageToBeTidied].TidyUpGarageClose();
	else
		aGarages[GarageToBeTidied].TidyUpGarage();
}

int16 CGarages::AddOne(float X1, float Y1, float Z1, float X2, float Y2, float Z2, eGarageType type, int32 targetId)
{
	if (NumGarages >= NUM_GARAGES) {
		assert(0);
		return NumGarages++;
	}
	CGarage* pGarage = &aGarages[NumGarages];
	pGarage->m_fX1 = min(X1, X2);
	pGarage->m_fX2 = max(X1, X2);
	pGarage->m_fY1 = min(Y1, Y2);
	pGarage->m_fY2 = max(Y1, Y2);
	pGarage->m_fZ1 = min(Z1, Z2);
	pGarage->m_fZ2 = max(Z1, Z2);
	pGarage->m_pDoor1 = nil;
	pGarage->m_pDoor2 = nil;
	pGarage->m_fDoor1Z = Z1;
	pGarage->m_fDoor2Z = Z1;
	pGarage->m_eGarageType = type;
	pGarage->field_24 = 0;
	pGarage->m_bRotatedDoor = false;
	pGarage->m_bCameraFollowsPlayer = false;
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
	pGarage->m_nTimeToStartAction = 0;
	pGarage->field_2 = 0;
	pGarage->m_nTargetModelIndex = targetId;
	pGarage->field_96 = 0;
	pGarage->m_bCollectedCarsState = 0;
	pGarage->m_bDeactivated = false;
	pGarage->m_bResprayHappened = false;
	switch (type) {
	case GARAGE_MISSION:
	case GARAGE_COLLECTORSITEMS:
	case GARAGE_COLLECTSPECIFICCARS:
	case GARAGE_COLLECTCARS_1:
	case GARAGE_COLLECTCARS_2:
	case GARAGE_COLLECTCARS_3:
	case GARAGE_FORCARTOCOMEOUTOF:
	case GARAGE_60SECONDS:
	case GARAGE_MISSION_KEEPCAR:
	case GARAGE_FOR_SCRIPT_TO_OPEN:
	case GARAGE_HIDEOUT_ONE:
	case GARAGE_HIDEOUT_TWO:
	case GARAGE_HIDEOUT_THREE:
	case GARAGE_FOR_SCRIPT_TO_OPEN_AND_CLOSE:
	case GARAGE_KEEPS_OPENING_FOR_SPECIFIC_CAR:
	case GARAGE_MISSION_KEEPCAR_REMAINCLOSED:
		pGarage->m_eGarageState = GS_FULLYCLOSED;
		pGarage->m_fDoorPos = 0.0f;
		break;
	case GARAGE_BOMBSHOP1:
	case GARAGE_BOMBSHOP2:
	case GARAGE_BOMBSHOP3:
	case GARAGE_RESPRAY:
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
	return NumGarages++;
}

void CGarages::ChangeGarageType(int16 garage, eGarageType type, int32 mi)
{
	CGarage* pGarage = &aGarages[garage];
	pGarage->m_eGarageType = type;
	pGarage->m_nTargetModelIndex = mi;
	pGarage->m_eGarageState = GS_FULLYCLOSED;
}

void CGarage::Update()
{
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
				if (pVehicle && IsEntityEntirelyOutside(pVehicle, 0.0f))
					TheCamera.pToGarageWeAreInForHackAvoidFirstPerson = this;
				if (pVehicle->GetModelIndex() == MI_MRWHOOP) {
					if (pVehicle->IsWithinArea(
						m_fX1 - DISTANCE_FOR_MRWHOOP_HACK,
						m_fX2 + DISTANCE_FOR_MRWHOOP_HACK,
						m_fY1 - DISTANCE_FOR_MRWHOOP_HACK,
						m_fY2 + DISTANCE_FOR_MRWHOOP_HACK)) {
						TheCamera.pToGarageWeAreIn = this;
						CGarages::bCamShouldBeOutisde = true;
					}
				}
			}
		}
	}
	if (m_bDeactivated && m_eGarageState == GS_FULLYCLOSED)
		return;
	switch (m_eGarageType) {
	case GARAGE_RESPRAY:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (IsStaticPlayerCarEntirelyInside() && !IsAnyOtherCarTouchingGarage(FindPlayerVehicle())) {
				if (IsCarSprayable()) {
					if (CWorld::Players[CWorld::PlayerInFocus].m_nMoney >= RESPRAY_PRICE || CGarages::RespraysAreFree) {
						m_eGarageState = GS_CLOSING;
						CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
						FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
					} else {
						CGarages::TriggerMessage("GA_3", -1, 4000, -1); // No more freebies. $1000 to respray!
						m_eGarageState = GS_OPENEDCONTAINSCAR;
						DMAudio.PlayFrontEndSound(SOUND_GARAGE_NO_MONEY, 1);
					}
				} else {
					CGarages::TriggerMessage("GA_1", -1, 4000, -1); // Whoa! I don't touch nothing THAT hot!
					m_eGarageState = GS_OPENEDCONTAINSCAR;
					DMAudio.PlayFrontEndSound(SOUND_GARAGE_BAD_VEHICLE, 1);
				}
			}
			if (FindPlayerVehicle()) {
				if (CalcDistToGarageRectangleSquared(FindPlayerVehicle()->GetPosition().x, FindPlayerVehicle()->GetPosition().y) < SQR(DISTANCE_TO_ACTIVATE_GARAGE))
					CWorld::CallOffChaseForArea(
						m_fX1 - DISTANCE_TO_CALL_OFF_CHASE,
						m_fY1 - DISTANCE_TO_CALL_OFF_CHASE,
						m_fX2 + DISTANCE_TO_CALL_OFF_CHASE,
						m_fY2 + DISTANCE_TO_CALL_OFF_CHASE);
			}
			break;
		case GS_CLOSING:
			m_fDoorPos = max(0.0f, m_fDoorPos - m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : ROTATED_DOOR_CLOSE_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				m_nTimeToStartAction = CTimer::GetTimeInMilliseconds() + TIME_TO_RESPRAY;
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				CStats::CheckPointReachedSuccessfully();
			}
			UpdateDoorsHeight();
#ifdef FIX_BUGS
			if (FindPlayerVehicle() && FindPlayerVehicle()->IsCar())
#else
			if (FindPlayerVehicle())
#endif
				((CAutomobile*)(FindPlayerVehicle()))->m_fFireBlowUpTimer = 0.0f;
			CWorld::CallOffChaseForArea(
				m_fX1 - DISTANCE_TO_CALL_OFF_CHASE,
				m_fY1 - DISTANCE_TO_CALL_OFF_CHASE,
				m_fX2 + DISTANCE_TO_CALL_OFF_CHASE,
				m_fY2 + DISTANCE_TO_CALL_OFF_CHASE);
			break;
		case GS_FULLYCLOSED:
			if (CTimer::GetTimeInMilliseconds() > m_nTimeToStartAction) {
				m_eGarageState = GS_OPENING;
				DMAudio.PlayFrontEndSound(SOUND_GARAGE_OPENING, 1);
				bool bTakeMoney = false;
				if (FindPlayerPed()->m_pWanted->m_nWantedLevel != 0)
					bTakeMoney = true;
				FindPlayerPed()->m_pWanted->Reset();
				CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
				FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
#ifdef FIX_BUGS
				bool bChangedColour = false;
#else
				bool bChangedColour;
#endif
				if (FindPlayerVehicle() && FindPlayerVehicle()->IsCar()) {
					if (FindPlayerVehicle()->m_fHealth < FREE_RESPRAY_HEALTH_THRESHOLD)
						bTakeMoney = true;
					FindPlayerVehicle()->m_fHealth = 1000.0f;
					((CAutomobile*)(FindPlayerVehicle()))->m_fFireBlowUpTimer = 0.0f;
					((CAutomobile*)(FindPlayerVehicle()))->Fix();
					if (FindPlayerVehicle()->GetUp().z < 0.0f) {
						FindPlayerVehicle()->GetUp() = -FindPlayerVehicle()->GetUp();
						FindPlayerVehicle()->GetRight() = -FindPlayerVehicle()->GetRight();
					}
					bChangedColour = false;
					if (!((CAutomobile*)(FindPlayerVehicle()))->bFixedColour) {
						uint8 colour1, colour2;
						uint16 attempt;
						((CVehicleModelInfo*)CModelInfo::GetModelInfo(FindPlayerVehicle()->GetModelIndex()))->ChooseVehicleColour(colour1, colour2);
						for (attempt = 0; attempt < 10; attempt++) {
							if (colour1 != FindPlayerVehicle()->m_currentColour1 || colour2 != FindPlayerVehicle()->m_currentColour2)
								break;
							((CVehicleModelInfo*)CModelInfo::GetModelInfo(FindPlayerVehicle()->GetModelIndex()))->ChooseVehicleColour(colour1, colour2);
						}
						bChangedColour = (attempt < 10);
						FindPlayerVehicle()->m_currentColour1 = colour1;
						FindPlayerVehicle()->m_currentColour2 = colour2;
						if (bChangedColour) {
							for (int i = 0; i < NUM_PARTICLES_IN_RESPRAY; i++) {
								CVector pos;
#ifdef FIX_BUGS
								pos.x = CGeneral::GetRandomNumberInRange(m_fX1 + 0.5f, m_fX2 - 0.5f);
								pos.y = CGeneral::GetRandomNumberInRange(m_fY1 + 0.5f, m_fY2 - 0.5f);
								pos.z = CGeneral::GetRandomNumberInRange(m_fDoor1Z - 3.0f, m_fDoor1Z + 1.0f);
#else
								// wtf is this
								pos.x = m_fX1 + 0.5f + (uint8)(CGeneral::GetRandomNumber()) / 256.0f * (m_fX2 - m_fX1 - 1.0f);
								pos.y = m_fY1 + 0.5f + (uint8)(CGeneral::GetRandomNumber()) / 256.0f * (m_fY2 - m_fY1 - 1.0f);
								pos.z = m_fDoor1Z - 3.0f + (uint8)(CGeneral::GetRandomNumber()) / 256.0f * 4.0f;
#endif
								CParticle::AddParticle(PARTICLE_GARAGEPAINT_SPRAY, pos, CVector(0.0f, 0.0f, 0.0f), nil, 0.0f, CVehicleModelInfo::ms_vehicleColourTable[colour1]);
							}
						}
					}
					CenterCarInGarage(FindPlayerVehicle());
				}
				if (bTakeMoney) {
					if (!CGarages::RespraysAreFree)
						CWorld::Players[CWorld::PlayerInFocus].m_nMoney = max(0, CWorld::Players[CWorld::PlayerInFocus].m_nMoney - RESPRAY_PRICE);
					CGarages::TriggerMessage("GA_2", -1, 4000, -1); // New engine and paint job. The cops won't recognize you!
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
				m_fX1 - DISTANCE_TO_CALL_OFF_CHASE,
				m_fY1 - DISTANCE_TO_CALL_OFF_CHASE,
				m_fX2 + DISTANCE_TO_CALL_OFF_CHASE,
				m_fY2 + DISTANCE_TO_CALL_OFF_CHASE);
			break;
		case GS_OPENING:
			m_fDoorPos = min(m_fDoorHeight, m_fDoorPos + m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : ROTATED_DOOR_OPEN_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_OPENEDCONTAINSCAR:
			if (IsPlayerOutsideGarage())
				m_eGarageState = GS_OPENED;
			break;
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
		}
		break;
	case GARAGE_BOMBSHOP1:
	case GARAGE_BOMBSHOP2:
	case GARAGE_BOMBSHOP3:
		switch (m_eGarageState) {
		case GS_OPENED:
			if (IsStaticPlayerCarEntirelyInside() && !IsAnyOtherCarTouchingGarage(FindPlayerVehicle())) {
#ifdef FIX_BUGS // FindPlayerVehicle() can never be NULL here because IsStaticPlayerCarEntirelyInside() is true, and there is no IsCar() check
				if (FindPlayerVehicle()->IsCar() && ((CAutomobile*)FindPlayerVehicle())->m_bombType) {
#else
				if (!FindPlayerVehicle() || ((CAutomobile*)FindPlayerVehicle())->m_bombType) {
#endif
					CGarages::TriggerMessage("GA_5", -1, 4000, -1); //"Your car is already fitted with a bomb"
					m_eGarageState = GS_OPENEDCONTAINSCAR;
					DMAudio.PlayFrontEndSound(SOUND_GARAGE_DENIED, 1);
					break;
				}
				if (!CGarages::BombsAreFree && CWorld::Players[CWorld::PlayerInFocus].m_nMoney >= BOMB_PRICE) {
					CGarages::TriggerMessage("GA_4", -1, 4000, -1); // "Car bombs are $1000 each"
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
			m_fDoorPos = max(0.0f, m_fDoorPos - m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : ROTATED_DOOR_CLOSE_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				m_eGarageState = GS_FULLYCLOSED;
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
			if (CTimer::GetTimeInMilliseconds() > m_nTimeToStartAction) {
				switch (m_eGarageType) {
				case GARAGE_BOMBSHOP1: DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB1_SET, 1); break;
				case GARAGE_BOMBSHOP2: DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB2_SET, 1); break;
				case GARAGE_BOMBSHOP3: DMAudio.PlayFrontEndSound(SOUND_GARAGE_BOMB3_SET, 1); break;
				}
				m_eGarageState = GS_OPENING;
				if (!CGarages::BombsAreFree)
					CWorld::Players[CWorld::PlayerInFocus].m_nMoney = max(0, CWorld::Players[CWorld::PlayerInFocus].m_nMoney - BOMB_PRICE);
				if (FindPlayerVehicle() && FindPlayerVehicle()->IsCar()) {
					((CAutomobile*)(FindPlayerVehicle()))->m_bombType = CGarages::GetBombTypeForGarageType(m_eGarageType);
					((CAutomobile*)(FindPlayerVehicle()))->m_pBombRigger = FindPlayerPed();
					if (m_eGarageType == GARAGE_BOMBSHOP3)
						CGarages::GivePlayerDetonator();
					CStats::KgOfExplosivesUsed += KGS_OF_EXPLOSIVES_IN_BOMB;
				}
				switch (m_eGarageType) {
				case GARAGE_BOMBSHOP1:
					switch (CPad::GetPad(0)->Mode) {
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
					switch (CPad::GetPad(0)->Mode) {
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
				CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
				FindPlayerPed()->m_pWanted->m_bIgnoredByCops = false;
			break;
			}
		case GS_OPENING:
			m_fDoorPos = min(m_fDoorHeight, m_fDoorPos + m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : ROTATED_DOOR_OPEN_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			UpdateDoorsHeight();
			break;
		case GS_OPENEDCONTAINSCAR:
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
				if (!FindPlayerVehicle() && m_pTarget && IsEntityEntirelyInside3D(m_pTarget, 0.0f) && !IsAnyOtherCarTouchingGarage(m_pTarget)) {
					CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
					FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
					m_eGarageState = GS_CLOSING;
					m_bClosingWithoutTargetCar = false;
				}
			}
			else if ((CTimer::GetFrameCounter() & 0x1F) == 0 && IsAnyOtherCarTouchingGarage(nil)) {
				m_eGarageState = GS_CLOSING;
				m_bClosingWithoutTargetCar = true;
			}
			break;
		case GS_CLOSING:
			m_fDoorPos = max(0.0f, m_fDoorPos - m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : ROTATED_DOOR_CLOSE_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
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
			m_fDoorPos = min(m_fDoorHeight, m_fDoorPos + m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : ROTATED_DOOR_OPEN_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_OPENED, 1.0f);
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
		switch (m_eGarageState) {
		case GS_OPENED:
			if (FindPlayerVehicle() && m_nTargetModelIndex == FindPlayerVehicle()->GetModelIndex()) {
				m_pTarget = FindPlayerVehicle();
				m_pTarget->RegisterReference((CEntity**)&m_pTarget);
			}
			if (!FindPlayerVehicle()) {
				if (m_pTarget && IsEntityEntirelyInside3D(m_pTarget, 0.0f) && !IsAnyOtherCarTouchingGarage(m_pTarget)) {
					if (IsEntityEntirelyOutside(FindPlayerPed(), 2.0f)) {
						CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_GARAGE);
						FindPlayerPed()->m_pWanted->m_bIgnoredByCops = true;
						m_eGarageState = GS_CLOSING;
					}
				}
				else if (Abs(FindPlayerCoors().x - GetGarageCenterX()) > DISTANCE_TO_CLOSE_COLLECTCARS_GARAGE ||
					Abs(FindPlayerCoors().y - GetGarageCenterY()) > DISTANCE_TO_CLOSE_COLLECTCARS_GARAGE) {
					m_eGarageState = GS_CLOSING;
					m_pTarget = nil;
				}
			}
			break;
		case GS_CLOSING:
			m_fDoorPos = max(0.0f, m_fDoorPos - m_bRotatedDoor ? ROTATED_DOOR_CLOSE_SPEED : ROTATED_DOOR_CLOSE_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == 0.0f) {
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_CLOSED, 1.0f);
				if (m_pTarget) {
					DestroyVehicleAndDriverAndPassengers(m_pTarget);
					m_pTarget = nil;
					CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_GARAGE);
					FindPlayerPed()->m_pWanted->m_bIgnoredByCops = false;
					int16 reward;
					switch (m_nTargetModelIndex) {
					case MI_POLICE:
						reward = REWARD_FOR_FIRST_POLICE_CAR * (MAX_POLICE_CARS_TO_COLLECT - CGarages::PoliceCarsCollected++) / MAX_POLICE_CARS_TO_COLLECT;
						break;
					case MI_SECURICA:
						reward = REWARD_FOR_FIRST_BANK_VAN * (MAX_BANK_VANS_TO_COLLECT - CGarages::BankVansCollected++) / MAX_BANK_VANS_TO_COLLECT;
						break;
#ifdef FIX_BUGS // not possible though
					default:
						reward = 0;
						break;
#endif
					}
					if (reward > 0) {
						CWorld::Players[CWorld::PlayerInFocus].m_nMoney += reward;
						CGarages::TriggerMessage("GA_10", reward, 4000, -1); // Nice one. Here's your $~1~
						DMAudio.PlayFrontEndSound(SOUND_GARAGE_VEHICLE_ACCEPTED, 1);
					}
					else {
						CGarages::TriggerMessage("GA_11", -1, 4000, -1); // We got these wheels already. It's worthless to us!
						DMAudio.PlayFrontEndSound(SOUND_GARAGE_VEHICLE_DECLINED, 1);
					}
				}
			}
			UpdateDoorsHeight();
			break;
		case GS_FULLYCLOSED:
			if (FindPlayerVehicle() && m_nTargetModelIndex == FindPlayerVehicle()->GetModelIndex()) {
				if (CalcDistToGarageRectangleSquared(FindPlayerVehicle()->GetPosition().x, FindPlayerVehicle()->GetPosition().y) < SQR(DISTANCE_TO_ACTIVATE_GARAGE))
					m_eGarageState = GS_OPENING;
			}
			break;
		case GS_OPENING:
			if (FindPlayerVehicle() && m_nTargetModelIndex == FindPlayerVehicle()->GetModelIndex()) {
				m_pTarget = FindPlayerVehicle();
				m_pTarget->RegisterReference((CEntity**)&m_pTarget);
			}
			m_fDoorPos = min(m_fDoorHeight, m_fDoorPos + m_bRotatedDoor ? ROTATED_DOOR_OPEN_SPEED : ROTATED_DOOR_OPEN_SPEED * CTimer::GetTimeStep());
			if (m_fDoorPos == m_fDoorHeight) {
				m_eGarageState = GS_OPENED;
				DMAudio.PlayOneShot(CGarages::AudioEntity, SOUND_GARAGE_DOOR_OPENED, 1.0f);
			}
			break;
		//case GS_OPENEDCONTAINSCAR:
		//case GS_CLOSEDCONTAINSCAR:
		//case GS_AFTERDROPOFF:
		default:
		}
		break;
	case GARAGE_COLLECTORSITEMS:
	case GARAGE_COLLECTCARS_1:
	case GARAGE_COLLECTCARS_2:
	case GARAGE_COLLECTCARS_3:
	case GARAGE_FORCARTOCOMEOUTOF:
	case GARAGE_60SECONDS:
	case GARAGE_CRUSHER:
	case GARAGE_MISSION_KEEPCAR:
	case GARAGE_FOR_SCRIPT_TO_OPEN:
	case GARAGE_HIDEOUT_ONE:
	case GARAGE_HIDEOUT_TWO:
	case GARAGE_HIDEOUT_THREE:
	case GARAGE_FOR_SCRIPT_TO_OPEN_AND_CLOSE:
	case GARAGE_KEEPS_OPENING_FOR_SPECIFIC_CAR:
	case GARAGE_MISSION_KEEPCAR_REMAINCLOSED:
		switch (m_eGarageState) {
		case GS_FULLYCLOSED:
		case GS_OPENING:
		case GS_OPENED:
		case GS_CLOSING:
		case GS_OPENEDCONTAINSCAR:
		case GS_CLOSEDCONTAINSCAR:
		case GS_AFTERDROPOFF:
		default:
		}
		break;
	default:
		break;
	}
	
}

WRAPPER void CGarages::Load(uint8* buf, uint32 size) { EAXJMP(0x428940); }
WRAPPER void CGarages::Save(uint8* buf, uint32 *size) { EAXJMP(0x4284E0); }

WRAPPER void CGarage::TidyUpGarageClose() { EAXJMP(0x427D90); }
WRAPPER void CGarage::TidyUpGarage() { EAXJMP(0x427C30); }
WRAPPER void CGarage::RefreshDoorPointers(bool) { EAXJMP(0x426980); }
WRAPPER void CGarage::UpdateCrusherAngle() { EAXJMP(0x4268A0); }
WRAPPER void CGarage::UpdateDoorsHeight() { EAXJMP(0x426730); }
WRAPPER float CGarages::FindDoorHeightForMI(int32) { EAXJMP(0x427C10); }

bool
CGarages::IsModelIndexADoor(uint32 id)
{
	return id == MI_GARAGEDOOR1 ||
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
		id == MI_GARAGEDOOR17 ||
		id == MI_GARAGEDOOR18 ||
		id == MI_GARAGEDOOR19 ||
		id == MI_GARAGEDOOR20 ||
		id == MI_GARAGEDOOR21 ||
		id == MI_GARAGEDOOR22 ||
		id == MI_GARAGEDOOR23 ||
		id == MI_GARAGEDOOR24 ||
		id == MI_GARAGEDOOR25 ||
		id == MI_GARAGEDOOR26 ||
		id == MI_GARAGEDOOR27 ||
		id == MI_GARAGEDOOR28 ||
		id == MI_GARAGEDOOR29 ||
		id == MI_GARAGEDOOR30 ||
		id == MI_GARAGEDOOR31 ||
		id == MI_GARAGEDOOR32 ||
		id == MI_CRUSHERBODY ||
		id == MI_CRUSHERLID;
}

bool CGarages::HasCarBeenCrushed(int32 handle)
{
	return CrushedCarId == handle;
}

WRAPPER void CGarages::TriggerMessage(const char *text, int16, uint16 time, int16) { EAXJMP(0x426B20); }
WRAPPER bool CGarages::IsPointWithinHideOutGarage(CVector&) { EAXJMP(0x428260); }
WRAPPER bool CGarages::IsPointWithinAnyGarage(CVector&) { EAXJMP(0x428320); }
WRAPPER void CGarages::PlayerArrestedOrDied() { EAXJMP(0x427F60); }
WRAPPER void CGarages::SetTargetCarForMissonGarage(int16, CVehicle*) { EAXJMP(0x426BD0); }
WRAPPER bool CGarages::HasCarBeenDroppedOffYet(int16) { EAXJMP(0x426C20); }
WRAPPER void CGarages::DeActivateGarage(int16) { EAXJMP(0x426C40); }
WRAPPER void CGarages::ActivateGarage(int16) { EAXJMP(0x426C60); }

int32 CGarages::QueryCarsCollected(int16 garage)
{
	return 0;
}

void CGarages::GivePlayerDetonator()
{
	FindPlayerPed()->GiveWeapon(WEAPONTYPE_DETONATOR, 1);
	FindPlayerPed()->GetWeapon(FindPlayerPed()->GetWeaponSlot(WEAPONTYPE_DETONATOR)).m_eWeaponState = WEAPONSTATE_READY;
}

WRAPPER bool CGarages::HasThisCarBeenCollected(int16 garage, uint8 id) { EAXJMP(0x426D50); }
WRAPPER bool CGarages::HasResprayHappened(int16 garage) { EAXJMP(0x4274F0); }
WRAPPER bool CGarages::IsThisCarWithinGarageArea(int16 garage, CEntity* pCar) { EAXJMP(0x427570); }

void CGarage::OpenThisGarage()
{
	if (m_eGarageState == GS_FULLYCLOSED || m_eGarageState == GS_CLOSING || m_eGarageState == GS_CLOSEDCONTAINSCAR)
		m_eGarageState = GS_OPENING;
}

bool CGarages::IsGarageOpen(int16 garage)
{
	return aGarages[garage].IsOpen();
}

bool CGarages::IsGarageClosed(int16 garage)
{
	return aGarages[garage].IsClosed();
}

void CGarage::CloseThisGarage()
{
	if (m_eGarageState == GS_OPENED || m_eGarageState == GS_OPENING)
		m_eGarageState = GS_CLOSING;
}

void CGarages::SetGarageDoorToRotate(int16 garage)
{
	if (aGarages[garage].m_bRotatedDoor)
		return;
	aGarages[garage].m_bRotatedDoor = true;
	aGarages[garage].m_fDoorHeight /= 2.0f;
	aGarages[garage].m_fDoorHeight -= 0.1f;
}

bool CGarages::HasImportExportGarageCollectedThisCar(int16 garage, int8 car)
{
	return CarTypesCollected[GetCarsCollectedIndexForGarageType(aGarages[garage].m_eGarageType)] & (1 << car);
}

void CGarages::SetLeaveCameraForThisGarage(int16 garage)
{
	aGarages[garage].m_bCameraFollowsPlayer = true;
}

#if 0
WRAPPER void CGarages::PrintMessages(void) { EAXJMP(0x426310); }
#else
void CGarages::PrintMessages()
{
	if (CTimer::GetTimeInMilliseconds() > MessageStartTime && CTimer::GetTimeInMilliseconds() < MessageEndTime) {
		CFont::SetScale(SCREEN_SCALE_X(1.2f), SCREEN_SCALE_Y(1.5f)); // BUG: game doesn't use macro here.
		CFont::SetPropOn();
		CFont::SetJustifyOff();
		CFont::SetBackgroundOff();
		CFont::SetCentreSize(SCREEN_SCALE_FROM_RIGHT(50.0f));
		CFont::SetCentreOn();
		CFont::SetFontStyle(FONT_BANK);
		CFont::SetColor(CRGBA(0, 0, 0, 255));

		float y_offset = SCREEN_HEIGHT / 3; // THIS is PS2 calculation
		// y_offset = SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(84.0f); // This is PC and results in text being written over some HUD elements

		if (MessageNumberInString2 < 0) {
			if (MessageNumberInString < 0) {
				CFont::PrintString(SCREEN_WIDTH / 2 - SCREEN_SCALE_X(2.0f), y_offset - SCREEN_SCALE_Y(2.0f), TheText.Get(MessageIDString));

				CFont::SetColor(CRGBA(89, 115, 150, 255));
				CFont::PrintString(SCREEN_WIDTH / 2, y_offset, TheText.Get(MessageIDString));
			}
			else {
				CMessages::InsertNumberInString(TheText.Get(MessageIDString), MessageNumberInString, -1, -1, -1, -1, -1, gUString);

				CFont::PrintString(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(2.0f), y_offset - SCREEN_SCALE_Y(40.0f) + SCREEN_SCALE_Y(2.0f), gUString);

				CFont::SetColor(CRGBA(89, 115, 150, 255));
				CFont::PrintString(SCREEN_WIDTH / 2, y_offset - SCREEN_SCALE_Y(40.0f), gUString);
			}
		}
		else {
			CMessages::InsertNumberInString(TheText.Get(MessageIDString), MessageNumberInString, MessageNumberInString2, -1, -1, -1, -1, gUString);
			CFont::PrintString(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(2.0f), y_offset - SCREEN_SCALE_Y(40.0f) + SCREEN_SCALE_Y(2.0f), gUString);

			CFont::SetColor(CRGBA(89, 115, 150, 255));
			CFont::PrintString(SCREEN_WIDTH / 2, y_offset - SCREEN_SCALE_Y(40.0f), gUString);
		}
	}
}
#endif

STARTPATCHES
	InjectHook(0x421C60, CGarages::Init, PATCH_JUMP);
#ifndef PS2
	InjectHook(0x421E10, CGarages::Shutdown, PATCH_JUMP);
#endif
ENDPATCHES