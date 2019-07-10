#include "common.h"
#include "patcher.h"
#include "main.h"
#include "Pools.h"
#include "Particle.h"
#include "Stats.h"
#include "World.h"
#include "DMAudio.h"
#include "RpAnimBlend.h"
#include "Ped.h"
#include "PlayerPed.h"
#include "General.h"
#include "SurfaceTable.h"
#include "VisibilityPlugins.h"
#include "AudioManager.h"
#include "HandlingMgr.h"
#include "Replay.h"
#include "PedPlacement.h"
#include "Shadows.h"
#include "Weather.h"
#include "ZoneCull.h"
#include "Population.h"
#include "Renderer.h"
#include "Lights.h"
#include "PointLights.h"
#include "Pad.h"
#include "Phones.h"

WRAPPER void CPed::KillPedWithCar(CVehicle *veh, float impulse) { EAXJMP(0x4EC430); }
WRAPPER void CPed::Say(uint16 audio) { EAXJMP(0x4E5A10); }
WRAPPER void CPed::SetDie(AnimationId anim, float arg1, float arg2) { EAXJMP(0x4D37D0); }
WRAPPER void CPed::SetDead(void) { EAXJMP(0x4D3970); }
WRAPPER void CPed::SpawnFlyingComponent(int, int8) { EAXJMP(0x4EB060); }
WRAPPER void CPed::RestorePreviousState(void) { EAXJMP(0x4C5E30); }
WRAPPER void CPed::ClearAttack(void) { EAXJMP(0x4E6790); }
WRAPPER void CPed::PedSetQuickDraggedOutCarPositionCB(CAnimBlendAssociation *dragAssoc, void *arg) { EAXJMP(0x4E2480); }
WRAPPER void CPed::PedSetDraggedOutCarPositionCB(CAnimBlendAssociation *dragAssoc, void *arg) { EAXJMP(0x4E2920); }
WRAPPER void CPed::SetPedPositionInCar(void) { EAXJMP(0x4D4970); }
WRAPPER void CPed::ProcessControl(void) { EAXJMP(0x4C8910); }
WRAPPER void CPed::PreRender(void) { EAXJMP(0x4CFDD0); }
WRAPPER void CPed::Render(void) { EAXJMP(0x4D03F0); }
WRAPPER int32 CPed::ProcessEntityCollision(CEntity*, CColPoint*) { EAXJMP(0x4CBB30); }
WRAPPER void CPed::SetMoveAnim(void) { EAXJMP(0x4C5A40); }
WRAPPER void CPed::SetFollowRoute(int16, int16) { EAXJMP(0x4DD690); }
WRAPPER void CPed::SetDuck(uint32) { EAXJMP(0x4E4920); }
WRAPPER void CPed::RegisterThreatWithGangPeds(CEntity*) { EAXJMP(0x4E3870); }
WRAPPER void CPed::MakeChangesForNewWeapon(int8) { EAXJMP(0x4F2560); }
WRAPPER bool CPed::Seek(void) { EAXJMP(0x4D1640); }

bool &CPed::bNastyLimbsCheat = *(bool*)0x95CD44;
bool &CPed::bPedCheat2 = *(bool*)0x95CD5A;
bool &CPed::bPedCheat3 = *(bool*)0x95CD59;

uint16 &CPed::distanceMultToCountPedNear = *(uint16*)0x5F8C98;

CVector &CPed::offsetToOpenRegularCarDoor = *(CVector*)0x62E030;
CVector &CPed::offsetToOpenLowCarDoor = *(CVector*)0x62E03C;
CVector &CPed::offsetToOpenVanDoor = *(CVector*)0x62E048;

void *CPed::operator new(size_t sz) { return CPools::GetPedPool()->New();  }
void *CPed::operator new(size_t sz, int handle) { return CPools::GetPedPool()->New(handle); }
void CPed::operator delete(void *p, size_t sz) { CPools::GetPedPool()->Delete((CPed*)p); }
void CPed::operator delete(void *p, int handle) { CPools::GetPedPool()->Delete((CPed*)p); }

CPed::~CPed(void)
{
	CWorld::Remove(this);
	CRadar::ClearBlipForEntity(BLIP_CHAR, CPools::GetPedPool()->GetIndex(this));
	if (bInVehicle && m_pMyVehicle){
		uint8 door_flag = GetVehDoorFlag(m_vehEnterType);
		if (m_pMyVehicle->pDriver == this)
			m_pMyVehicle->pDriver = nil;
		else {
			for (int i = 0; i < m_pMyVehicle->m_nNumMaxPassengers; i++) {
				if (m_pMyVehicle->pPassengers[i] == this)
					m_pMyVehicle->pPassengers[i] = nil;
			}
		}
		if (m_nPedState == PED_EXIT_CAR || m_nPedState == PED_DRAG_FROM_CAR)
			m_pMyVehicle->m_nGettingOutFlags &= ~door_flag;
		bInVehicle = false;
		m_pMyVehicle = nil;
	}else if (m_nPedState == PED_ENTER_CAR || m_nPedState == PED_CARJACK){
		QuitEnteringCar();
	}
	if (m_pFire)
		m_pFire->Extinguish();
	CPopulation::UpdatePedCount(m_nPedType, true);
	DMAudio.DestroyEntity(m_audioEntityId);
}

void
CPed::FlagToDestroyWhenNextProcessed(void)
{
	bRemoveFromWorld = true;
	if (!bInVehicle || !m_pMyVehicle)
		return;
	if (m_pMyVehicle->pDriver == this){
		m_pMyVehicle->pDriver = nil;
		if (IsPlayer() && m_pMyVehicle->m_status != STATUS_WRECKED)
			m_pMyVehicle->m_status = STATUS_ABANDONED;
	}else{
		m_pMyVehicle->RemovePassenger(this);
	}
	bInVehicle = false;
	m_pMyVehicle = nil;
	if (CharCreatedBy == MISSION_CHAR)
		m_nPedState = PED_DEAD;
	else
		m_nPedState = PED_NONE;
	m_pVehicleAnim = nil;
}

static char ObjectiveText[34][28] = {
	"No Obj",
	"Wait on Foot",
	"Flee on Foot Till Safe",
	"Guard Spot",
	"Guard Area",
	"Wait in Car",
	"Wait in Car then Getout",
	"Kill Char on Foot",
	"Kill Char Any Means",
	"Flee Char on Foot Till Safe",
	"Flee Char on Foot Always",
	"GoTo Char on Foot",
	"Follow Char in Formation",
	"Leave Car",
	"Enter Car as Passenger",
	"Enter Car as Driver",
	"Follow Car in Car",
	"Fire at Obj from Vehicle",
	"Destroy Obj",
	"Destroy Car",
	"GoTo Area Any Means",
	"GoTo Area on Foot",
	"Run to Area",
	"GoTo Area in Car",
	"Follow Car on Foot Woffset",
	"Guard Attack",
	"Set Leader",
	"Follow Route",
	"Solicit",
	"Take Taxi",
	"Catch Train",
	"Buy IceCream",
	"Steal Any Car",
	"Mug Char",
};

static char StateText[56][18] = {
	"None",	// 1
	"Idle",
	"Look Entity",
	"Look Heading",
	"Wander Range",
	"Wander Path",
	"Seek Pos",
	"Seek Entity",
	"Flee Pos",
	"Flee Entity",
	"Pursue",
	"Follow Path",
	"Sniper Mode",
	"Rocket Mode",
	"Dummy",
	"Pause",
	"Attack",
	"Fight",
	"Face Phone",
	"Make Call",
	"Chat",
	"Mug",
	"AimGun",
	"AI Control",
	"Seek Car",
	"Seek InBoat",
	"Follow Route",
	"C.P.R.",
	"Solicit",
	"Buy IceCream",
	"Investigate",
	"Step away",
	"STATES_NO_AI",
	"On Fire",
	"Jump",
	"Fall",
	"GetUp",
	"Stagger",
	"Dive away",
	"STATES_NO_ST",
	"Enter Train",
	"Exit Train",
	"Arrest Plyr",
	"Driving",
	"Passenger",
	"Taxi Passngr",
	"Open Door",
	"Die",
	"Dead",
	"CarJack",
	"Drag fm Car",
	"Enter Car",
	"Steal Car",
	"Exit Car",
	"Hands Up",
	"Arrested",
};

static char PersonalityTypeText[32][18] = {
	"Player",
	"Cop",
	"Medic",
	"Fireman",
	"Gang 1",
	"Gang 2",
	"Gang 3",
	"Gang 4",
	"Gang 5",
	"Gang 6",
	"Gang 7",
	"Street Guy",
	"Suit Guy",
	"Sensible Guy",
	"Geek Guy",
	"Old Guy",
	"Tough Guy",
	"Street Girl",
	"Suit Girl",
	"Sensible Girl",
	"Geek Girl",
	"Old Girl",
	"Tough Girl",
	"Tramp",
	"Tourist",
	"Prostitute",
	"Criminal",
	"Busker",
	"Taxi Driver",
	"Psycho",
	"Steward",
	"Sports Fan",
};

static char WaitStateText[21][16] = {
	"No Wait",
	"Traffic Lights",
	"Pause CrossRoad",
	"Look CrossRoad",
	"Look Ped",
	"Look Shop",
	"Look Accident",
	"FaceOff Gang",
	"Double Back",
	"Hit Wall",
	"Turn 180deg",
	"Surprised",
	"Ped Stuck",
	"Look About",
	"Play Duck",
	"Play Cower",
	"Play Taxi",
	"Play HandsUp",
	"Play HandsCower",
	"Play Chat",
	"Finish Flee",
};

CPed::CPed(uint32 pedType) : m_pedIK(this)
{
	m_type = ENTITY_TYPE_PED;
	bPedPhysics = true;
	bUseCollisionRecords = true;

	m_vecAnimMoveDelta.x = 0.0;
	m_vecAnimMoveDelta.y = 0.0;
	m_fHealth = 100.0f;
	m_fArmour = 0.0f;
	m_nPedType = pedType;
	field_520 = 0;
	m_talkTimer = 0;
	m_talkTypeLast = 167;
	m_talkType = 167;
	m_objective = OBJECTIVE_NONE;
	m_prevObjective = OBJECTIVE_NONE;
	CharCreatedBy = RANDOM_CHAR;
	m_leader = nil;
	m_pedInObjective = nil;
	m_carInObjective = nil;
	bInVehicle = 0;
	m_pMyVehicle = nil;
	m_pVehicleAnim = nil;
	m_vecOffsetSeek.x = 0.0;
	m_vecOffsetSeek.y = 0.0;
	m_vecOffsetSeek.z = 0.0;
	m_pedFormation = 0;
	m_lastThreatTimer = 0;
	m_nPedStateTimer = 0;
	m_actionX = 0;
	m_actionY = 0;
	m_phoneTalkTimer = 0;
	m_stateUnused = 0;
	m_leaveCarTimer = 0;
	m_getUpTimer = 0;
	m_attackTimer = 0;
	m_timerUnused = 0;
	m_lookTimer = 0;
	m_standardTimer = 0;
	m_lastHitTime = 0;
	m_hitRecoverTimer = 0;
	field_4E8 = 0;
	m_moved = CVector2D(0.0f, 0.0f);
	m_fRotationCur = 0.0f;
	m_headingRate = 15.0f;
	m_fRotationDest = 0.0f;
	m_vehEnterType = CAR_DOOR_LF;
	m_walkAroundType = 0;
	m_pCurrentPhysSurface = nil;
	m_vecOffsetFromPhysSurface = CVector(0.0f, 0.0f, 0.0f);
	m_pSeekTarget = nil;
	m_vecSeekVehicle = CVector(0.0f, 0.0f, 0.0f);
	m_wepSkills = 0;
	field_318 = 1.0f;
	field_31C = 0;
	m_phoneId = -1;
	m_lastAccident = 0;
	m_fleeFrom = nil;
	m_fleeFromPosX = 0;
	m_fleeFromPosY = 0;
	m_fleeTimer = 0;
	m_vecSeekPosEx = CVector(0.0f, 0.0f, 0.0f);
	m_seekExAngle = 0.0f;
	m_nWaitState = WAITSTATE_FALSE;
	m_nWaitTimer = 0;
	m_pCollidingEntity = nil;
	m_nPedState = PED_IDLE;
	m_nLastPedState = PED_NONE;
	m_nMoveState = PEDMOVE_STILL;
	m_nStoredActionState = 0;
	m_pFire = nil;
	m_pPointGunAt = nil;
	m_pLookTarget = nil;
	m_fLookDirection = 0.0f;
	m_pCurSurface = nil;
	m_targetUnused = nil;
	m_nPathNodes = 0;
	m_nCurPathNode = 0;
	m_nPathState = 0;
	m_pNextPathNode = nil;
	m_pLastPathNode = nil;
	m_routeLastPoint = -1;
	m_routePoints = 0;
	m_routePos = 0;
	m_routeType = 0;
	m_bodyPartBleeding = -1;

	m_fMass = 70.0f;
	m_fTurnMass = 100.0f;
	m_fAirResistance = 0.4f / m_fMass;
	m_fElasticity = 0.05f;

	bIsStanding = false;
	m_ped_flagA2 = false;
	m_ped_flagA4 = false;
	bIsPointingGunAt = false;
	bIsLooking = false;
	m_ped_flagA20 = false;
	bIsRestoringLook = false;
	bIsAimingGun = false;

	bIsRestoringGun = false;
	bCanPointGunAtTarget = false;
	bIsTalking = false;
	bIsInTheAir = false;
	bIsLanding = false;
	m_ped_flagB20 = false;
	m_ped_flagB40 = false;
	m_ped_flagB80 = false;

	m_ped_flagC1 = false;
	bRespondsToThreats = true;
	m_ped_flagC4 = true;
	m_ped_flagC8 = false;
	m_ped_flagC10 = false;
	m_ped_flagC20 = false;
	m_ped_flagC40 = false;
	m_ped_flagC80 = false;

	m_ped_flagD1 = false;
	m_ped_flagD2 = false;
	m_ped_flagD4 = false;
	m_ped_flagD8 = false;
	m_ped_flagD10 = false;
	m_ped_flagD20 = false;
	m_ped_flagD40 = false;
	m_ped_flagD80 = false;

	m_ped_flagE1 = false;
	m_ped_flagE2 = false;
	bNotAllowedToDuck = false;
	bCrouchWhenShooting = false;
	bIsDucking = false;
	m_ped_flagE20 = false;
	bDoBloodyFootprints = false;
	m_ped_flagE80 = false;

	m_ped_flagF1 = false;
	m_ped_flagF2 = false;
	m_ped_flagF4 = false;
	m_ped_flagF8 = false;
	m_ped_flagF10 = false;
	m_ped_flagF20 = false;
	m_ped_flagF40 = false;
	m_ped_flagF80 = false;

	m_ped_flagG1 = false;
	m_ped_flagG2 = true;
	m_ped_flagG4 = false;
	m_ped_flagG8 = false;
	m_ped_flagG10 = false;
	m_ped_flagG20 = false;
	m_ped_flagG40 = false;
	m_ped_flagG80 = false;

	m_ped_flagH1 = false;
	m_ped_flagH2 = false;
	m_ped_flagH4 = false;
	m_ped_flagH8 = false;
	m_ped_flagH10 = false;
	m_ped_flagH20 = false;
	m_ped_flagH40 = false;
	m_ped_flagH80 = false;

	m_ped_flagI1 = false;
	m_ped_flagI2 = false;
	m_ped_flagI4 = false;
	bHasAlreadyBeenRecorded = false;
	m_ped_flagI10 = false;
#ifdef KANGAROO_CHEAT
	m_ped_flagI80 = false;
#endif

	if ((CGeneral::GetRandomNumber() & 3) == 0)
		m_ped_flagD1 = true;

	m_audioEntityId = DMAudio.CreateEntity(0, this);
	DMAudio.SetEntityStatus(m_audioEntityId, 1);
	m_fearFlags = CPedType::GetThreats(m_nPedType);
	m_threatEntity = nil;
	m_eventOrThread = CVector2D(0.0f, 0.0f);
	m_pEventEntity = nil;
	m_fAngleToEvent = 0.0f;
	m_numNearPeds = 0;

	for (int i = 0; i < 10; i++)
	{
		m_nearPeds[i] = nil;
		if (i < 8) {
			m_pPathNodesStates[i] = nil;
		}
	}
	m_maxWeaponTypeAllowed = 0;
	m_currentWeapon = 0;
	m_storedWeapon = WEAPONTYPE_UNIDENTIFIED;

	for(int i = 0; i < WEAPONTYPE_TOTAL_INVENTORY_WEAPONS; i++)
	{
		CWeapon &weapon = GetWeapon(i);
		weapon.m_eWeaponType = WEAPONTYPE_UNARMED;
		weapon.m_eWeaponState = WEAPONSTATE_READY;
		weapon.m_nAmmoInClip = 0;
		weapon.m_nAmmoTotal = 0;
		weapon.m_nTimer = 0;
	}

	m_lastHitState = 0;
	GiveWeapon(WEAPONTYPE_UNARMED, 0);
	m_wepAccuracy = 60;
	m_lastWepDam = -1;
	m_collPoly.valid = false;
	m_fCollisionSpeed = 0.0f;
	m_wepModelID = -1;
	CPopulation::UpdatePedCount(m_nPedType, false);
}

uint32
CPed::GiveWeapon(eWeaponType weaponType, uint32 ammo)
{
	CWeapon &weapon = GetWeapon(weaponType);

	if (HasWeapon(weaponType)) {
		if (weapon.m_nAmmoTotal + ammo > 99999)
			weapon.m_nAmmoTotal = 99999;
		else
			weapon.m_nAmmoTotal += ammo;

		weapon.Reload();	
	} else {
		weapon.Initialise(weaponType, ammo);
		// TODO: It seems game uses this as both weapon count and max WeaponType we have, which is ofcourse erroneous.
		m_maxWeaponTypeAllowed++;
	}
	if (weapon.m_eWeaponState == WEAPONSTATE_OUT_OF_AMMO)
		weapon.m_eWeaponState = WEAPONSTATE_READY;

	return weaponType;
}

static RwObject*
RemoveAllModelCB(RwObject *object, void *data)
{
	RpAtomic *atomic = (RpAtomic*)object;
	if (CVisibilityPlugins::GetAtomicModelInfo(atomic)) {
		RpClumpRemoveAtomic(atomic->clump, atomic);
		RpAtomicDestroy(atomic);
	}
	return object;
}

static PedOnGroundState
CheckForPedsOnGroundToAttack(CPlayerPed *player, CPed **pedOnGround)
{
	PedOnGroundState stateToReturn;
	float angleToFace;
	CPed *currentPed = nil;
	PedState currentPedState;
	CPed *pedOnTheFloor = nil;
	CPed *deadPed = nil;
	CPed *pedBelow = nil;
	bool foundDead = false;
	bool foundOnTheFloor = false;
	bool foundBelow = false;
	float angleDiff;
	float distance;

	if (!CGame::nastyGame)
		return NO_PED;

	for (int currentPedId = 0; currentPedId < player->m_numNearPeds; currentPedId++) {

		currentPed = player->m_nearPeds[currentPedId];

		CVector posDifference = currentPed->GetPosition() - player->GetPosition();
		distance = posDifference.Magnitude();

		if (distance < 2.0f) {
			angleToFace = CGeneral::GetRadianAngleBetweenPoints(
				currentPed->GetPosition().x, currentPed->GetPosition().y,
				player->GetPosition().x, player->GetPosition().y);

			angleToFace = CGeneral::LimitRadianAngle(angleToFace);
			player->m_fRotationCur = CGeneral::LimitRadianAngle(player->m_fRotationCur);

			angleDiff = Abs(angleToFace - player->m_fRotationCur);

			if (angleDiff > PI)
				angleDiff = 2 * PI - angleDiff;

			currentPedState = currentPed->m_nPedState;

			if (currentPedState == PED_FALL || currentPedState == PED_GETUP || currentPedState == PED_DIE || currentPedState == PED_DEAD) {
				if (distance < 2.0f && angleDiff < DEGTORAD(65.0f)) {
					if (currentPedState == PED_DEAD) {
						foundDead = 1;
						if (!deadPed)
							deadPed = currentPed;
					} else if (!currentPed->IsPedHeadAbovePos(-0.6f)) {
						foundOnTheFloor = 1;
						if (!pedOnTheFloor)
							pedOnTheFloor = currentPed;
					}
				}
			} else if ((distance >= 0.8f || angleDiff >= DEGTORAD(75.0f))
						&& (distance >= 1.3f || angleDiff >= DEGTORAD(55.0f))
						&& (distance >= 1.7f || angleDiff >= DEGTORAD(35.0f))
						&& (distance >= 2.0f || angleDiff >= DEGTORAD(30.0f))) {

				if (angleDiff < DEGTORAD(75.0f)) {
					foundBelow = 1;
					if (!pedBelow)
						pedBelow = currentPed;
				}
			} else {
				foundBelow = 1;
				pedBelow = currentPed;
				break;
			}
		}
	}

	if (foundOnTheFloor) {
		currentPed = pedOnTheFloor;
		stateToReturn = PED_ON_THE_FLOOR;
	} else if (foundDead) {
		currentPed = deadPed;
		stateToReturn = PED_DEAD_ON_THE_FLOOR;
	} else if (foundBelow) {
		currentPed = pedBelow;
		stateToReturn = PED_BELOW_PLAYER;
	} else {
		currentPed = nil;
		stateToReturn = NO_PED;
	}

	if (pedOnGround)
		* pedOnGround = currentPed;

	return stateToReturn;
}

bool
CPed::IsPlayer(void)
{
	return m_nPedType == PEDTYPE_PLAYER1 || m_nPedType== PEDTYPE_PLAYER2 ||
		m_nPedType == PEDTYPE_PLAYER3 || m_nPedType == PEDTYPE_PLAYER4;
}

bool
CPed::UseGroundColModel(void)
{
	return m_nPedState == PED_FALL ||
		m_nPedState == PED_DIVE_AWAY ||
		m_nPedState == PED_DIE ||
		m_nPedState == PED_DEAD;
}

bool
CPed::CanSetPedState(void)
{
	return m_nPedState != PED_DIE && m_nPedState != PED_ARRESTED &&
		m_nPedState != PED_ENTER_CAR && m_nPedState != PED_DEAD && m_nPedState != PED_CARJACK && m_nPedState != PED_STEAL_CAR;
}

bool
CPed::IsPedInControl(void)
{
	return m_nPedState <= PED_STATES_NO_AI
		&& !bIsInTheAir && !bIsLanding
		&& m_fHealth > 0.0f;
}

bool
CPed::CanStrafeOrMouseControl(void)
{
	return m_nPedState == PED_NONE || m_nPedState == PED_IDLE || m_nPedState == PED_FLEE_POS || m_nPedState == PED_FLEE_ENTITY ||
		m_nPedState == PED_ATTACK || m_nPedState == PED_FIGHT || m_nPedState == PED_AIM_GUN || m_nPedState == PED_JUMP;
}

void
CPed::AddWeaponModel(int id)
{
	RpAtomic *atm;

	if (id != -1) {
		atm = (RpAtomic*)CModelInfo::GetModelInfo(id)->CreateInstance();
		RwFrameDestroy(RpAtomicGetFrame(atm));
		RpAtomicSetFrame(atm, GetNodeFrame(PED_HANDR));
		RpClumpAddAtomic((RpClump*)m_rwObject, atm);
		m_wepModelID = id;
	}
}

void
CPed::AimGun(void)
{
	RwV3d pos;
	CVector vector;

	if (m_pSeekTarget) {
		if (m_pSeekTarget->IsPed()) {
			((CPed*)m_pSeekTarget)->m_pedIK.GetComponentPosition(&pos, PED_TORSO);
			vector.x = pos.x;
			vector.y = pos.y;
			vector.z = pos.z;
		} else {
			vector = m_pSeekTarget->GetPosition();
		}
		Say(SOUND_PED_ATTACK);

		bCanPointGunAtTarget = m_pedIK.PointGunAtPosition(&vector);
		if (m_pLookTarget != m_pSeekTarget) {
			SetLookFlag(m_pSeekTarget, 1);
		}

	} else {
		if (IsPlayer()) {
			bCanPointGunAtTarget = m_pedIK.PointGunInDirection(m_fLookDirection, ((CPlayerPed*)this)->m_fFPSMoveHeading);
		} else {
			bCanPointGunAtTarget = m_pedIK.PointGunInDirection(m_fLookDirection, 0.0f);
		}
	}
}

void
CPed::ApplyHeadShot(eWeaponType weaponType, CVector pos, bool evenOnPlayer)
{
	CVector pos2 = CVector(
		pos.x,
		pos.y,
		pos.z + 0.1f
	);

	if (!CPed::IsPlayer() || evenOnPlayer) {
		++CStats::HeadShots;

		// BUG: This condition will always return true.
		if (m_nPedState != PED_PASSENGER || m_nPedState != PED_TAXI_PASSENGER) {
			CPed::SetDie(ANIM_KO_SHOT_FRONT1, 4.0f, 0.0f);
		}

		m_ped_flagC20 = true;
		m_nPedStateTimer = CTimer::GetTimeInMilliseconds() + 150;

		CParticle::AddParticle(PARTICLE_TEST, pos2,
			CVector(0.0f, 0.0f, 0.0f), nil, 0.2f, 0, 0, 0, 0);

		if (CEntity::GetIsOnScreen()) {
			for(int i=0; i < 32; i++) {
				CParticle::AddParticle(PARTICLE_BLOOD_SMALL,
					pos2, CVector(0.0f, 0.0f, 0.03f),
					nil, 0.0f, 0, 0, 0, 0);
			}

			for (int i = 0; i < 16; i++) {
				CParticle::AddParticle(PARTICLE_DEBRIS2,
					pos2,
					CVector(0.0f, 0.0f, 0.01f),
					nil, 0.0f, 0, 0, 0, 0);
			}
		}
	}
}

void
CPed::RemoveBodyPart(PedNode nodeId, int8 unk)
{
	RwFrame *frame;
	RwV3d pos;

	frame = GetNodeFrame(nodeId);
	if (frame) {
		if (CGame::nastyGame) {
			if (nodeId != PED_HEAD)
				CPed::SpawnFlyingComponent(nodeId, unk);

			RecurseFrameChildrenVisibilityCB(frame, nil);
			pos.x = 0.0f;
			pos.y = 0.0f;
			pos.z = 0.0f;

			for (frame = RwFrameGetParent(frame); frame; frame = RwFrameGetParent(frame))
				RwV3dTransformPoints(&pos, &pos, 1, RwFrameGetMatrix(frame));

			if (CEntity::GetIsOnScreen()) {
				CParticle::AddParticle(PARTICLE_TEST, pos,
					CVector(0.0f, 0.0f, 0.0f),
					nil, 0.2f, 0, 0, 0, 0);

				for (int i = 0; i < 16; i++) {
					CParticle::AddParticle(PARTICLE_BLOOD_SMALL,
						pos,
						CVector(0.0f, 0.0f, 0.03f),
						nil, 0.0f, 0, 0, 0, 0);
				}
			}
			m_ped_flagC20 = true;
			m_bodyPartBleeding = nodeId;
		}
	} else {
		printf("Trying to remove ped component");
	}
}

RwObject*
CPed::SetPedAtomicVisibilityCB(RwObject *object, void *data)
{
	if (data == nil)
		RpAtomicSetFlags(object, 0);
	return object;
}

RwFrame*
CPed::RecurseFrameChildrenVisibilityCB(RwFrame *frame, void *data)
{
	RwFrameForAllObjects(frame, SetPedAtomicVisibilityCB, data);
	RwFrameForAllChildren(frame, RecurseFrameChildrenVisibilityCB, nil);
	return frame;
}

void
CPed::SetLookFlag(CEntity *target, bool unknown)
{
	if (m_lookTimer < CTimer::GetTimeInMilliseconds()) {
		bIsLooking = true;
		bIsRestoringLook = false;
		m_pLookTarget = target;
		m_pLookTarget->RegisterReference((CEntity**)&m_pLookTarget);
		m_fLookDirection = 999999.0f;
		m_lookTimer = 0;
		m_ped_flagA20 = unknown;
		if (m_nPedState != PED_DRIVING) {
			m_pedIK.m_flags &= ~CPedIK::FLAG_2;
		}
	}
}

void
CPed::SetLookFlag(float direction, bool unknown)
{
	if (m_lookTimer < CTimer::GetTimeInMilliseconds()) {
		bIsLooking = true;
		bIsRestoringLook = false;
		m_pLookTarget = nil;
		m_fLookDirection = direction;
		m_lookTimer = 0;
		m_ped_flagA20 = unknown;
		if (m_nPedState != PED_DRIVING) {
			m_pedIK.m_flags &= ~CPedIK::FLAG_2;
		}
	}
}

void
CPed::SetLookTimer(int time)
{
	if (CTimer::GetTimeInMilliseconds() > m_lookTimer) {
		m_lookTimer = CTimer::GetTimeInMilliseconds() + time;
	}
}

bool
CPed::OurPedCanSeeThisOne(CEntity *target)
{
	CColPoint colpoint;
	CEntity *ent;

	CVector2D dist = CVector2D(target->GetPosition()) - CVector2D(this->GetPosition());

	// Check if target is behind ped
	if (DotProduct2D(dist, CVector2D(this->GetForward())) < 0.0f)
		return false;

	// Check if target is too far away
	if (dist.Magnitude() >= 40.0f)
		return false;

	// Check line of sight from head
	CVector headPos = this->GetPosition();
	headPos.z += 1.0f;
	return !CWorld::ProcessLineOfSight(headPos, target->GetPosition(), colpoint, ent, true, false, false, false, false, false);
}

void
CPed::Avoid(void)
{
	CPed *nearestPed;

	if(m_pedStats->m_temper > m_pedStats->m_fear && m_pedStats->m_temper > 50)
		return;

	if (CTimer::GetTimeInMilliseconds() > m_nPedStateTimer) {

		if (m_nMoveState != PEDMOVE_NONE && m_nMoveState != PEDMOVE_STILL) {
			nearestPed = m_nearPeds[0];

			if (nearestPed && nearestPed->m_nPedState != PED_DEAD && nearestPed != m_pSeekTarget && nearestPed != m_pedInObjective) {

				// Check if this ped wants to avoid the nearest one
				if (CPedType::GetAvoid(this->m_nPedType) & CPedType::GetFlag(nearestPed->m_nPedType)) {

					// Further codes checks whether the distance between us and ped will be equal or below 1.0, if we walk up to him by 1.25 meters.
					// If so, we want to avoid it, so we turn our body 45 degree and look to somewhere else.

					// Game converts from radians to degress and back again here, doesn't make much sense
					CVector2D forward(-Sin(m_fRotationCur), Cos(m_fRotationCur));
					forward.Normalise();	// this is kinda pointless

					// Move forward 1.25 meters
					CVector2D testPosition = CVector2D(GetPosition()) + forward*1.25f;

					// Get distance to ped we want to avoid
					CVector2D distToPed = CVector2D(nearestPed->GetPosition()) - testPosition;

					if (distToPed.Magnitude() <= 1.0f && CPed::OurPedCanSeeThisOne((CEntity*)nearestPed)) {
						m_nPedStateTimer = CTimer::GetTimeInMilliseconds()
							+ 500 + (m_randomSeed + 3 * CTimer::GetFrameCounter())
							% 1000 / 5;

						m_fRotationDest += DEGTORAD(45.0f);
						if (!bIsLooking) {
							CPed::SetLookFlag(nearestPed, 0);
							CPed::SetLookTimer(CGeneral::GetRandomNumberInRange(500, 800));
						}
					}
				}
			}
		}
	}
}

void
CPed::ClearAimFlag(void)
{
	if (bIsAimingGun) {
		bIsAimingGun = false;
		bIsRestoringGun = true;
		m_pedIK.m_flags &= ~CPedIK:: FLAG_4;
	}

	if (CPed::IsPlayer())
		((CPlayerPed*)this)->m_fFPSMoveHeading = 0.0;
}

void
CPed::ClearLookFlag(void) {
	if (bIsLooking) {
		bIsLooking = false;
		bIsRestoringLook = true;
		m_ped_flagI1 = false;

		m_pedIK.m_flags &= ~CPedIK::FLAG_2;
		if (CPed::IsPlayer())
			m_lookTimer = CTimer::GetTimeInMilliseconds() + 2000;
		else
			m_lookTimer = CTimer::GetTimeInMilliseconds() + 4000;

		if (m_nPedState == PED_LOOK_HEADING || m_nPedState == PED_LOOK_ENTITY) {
			CPed::RestorePreviousState();
			CPed::ClearLookFlag();
		}
	}
}

bool
CPed::IsPedHeadAbovePos(float zOffset)
{
	RwMatrix mat;
	
	CPedIK::GetWorldMatrix(GetNodeFrame(PED_HEAD), &mat);
	return zOffset + GetPosition().z < RwMatrixGetPos(&mat)->z;
}

void
CPed::FinishedAttackCB(CAnimBlendAssociation *attackAssoc, void *arg)
{
	CWeaponInfo *currentWeapon;
	CAnimBlendAssociation *newAnim;
	CPed *ped = (CPed*)arg;

	if (attackAssoc) {
		switch (attackAssoc->animId) {
			case ANIM_WEAPON_START_THROW:
				if ((!ped->IsPlayer() || ((CPlayerPed*)ped)->field_1380) && ped->IsPlayer()) {
					attackAssoc->blendDelta = -1000.0f;
					newAnim = CAnimManager::AddAnimation((RpClump*)ped->m_rwObject, ASSOCGRP_STD, ANIM_WEAPON_THROWU);
				} else {
					attackAssoc->blendDelta = -1000.0f;
					newAnim = CAnimManager::AddAnimation((RpClump*)ped->m_rwObject, ASSOCGRP_STD, ANIM_WEAPON_THROW);
				}

				newAnim->SetFinishCallback(FinishedAttackCB, ped);
				return;

			case ANIM_FIGHT_PPUNCH:
				attackAssoc->blendDelta = -8.0f;
				attackAssoc->flags |= ASSOC_DELETEFADEDOUT;
				ped->ClearAttack();
				return;

			case ANIM_WEAPON_THROW:
			case ANIM_WEAPON_THROWU:
				if (ped->GetWeapon()->m_nAmmoTotal > 0) {
					currentWeapon = CWeaponInfo::GetWeaponInfo(ped->GetWeapon()->m_eWeaponType);
					ped->AddWeaponModel(currentWeapon->m_nModelId);
				}
				break;
			default:
				break;
		}
	}
	
	if (!ped->m_ped_flagA4)
		ped->ClearAttack();
}

void
CPed::Attack(void)
{
	CAnimBlendAssociation *weaponAnimAssoc;
	int32 weaponAnim;
	float animStart;
	RwFrame *frame;
	eWeaponType ourWeaponType;
	float weaponAnimTime;
	eWeaponFire ourWeaponFire;
	float animLoopEnd;
	CWeaponInfo *ourWeapon;
	bool lastReloadWasInFuture;
	AnimationId reloadAnim;
	CAnimBlendAssociation *reloadAnimAssoc;
	float delayBetweenAnimAndFire;
	CVector firePos;

	ourWeaponType = GetWeapon()->m_eWeaponType;
	ourWeapon = CWeaponInfo::GetWeaponInfo(ourWeaponType);
	ourWeaponFire = ourWeapon->m_eWeaponFire;
	weaponAnimAssoc = RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ourWeapon->m_AnimToPlay);
	lastReloadWasInFuture = m_ped_flagA4;
	reloadAnimAssoc = nil;
	reloadAnim = NUM_ANIMS;
	delayBetweenAnimAndFire = ourWeapon->m_fAnimFrameFire;
	weaponAnim = ourWeapon->m_AnimToPlay;

	if (weaponAnim == ANIM_WEAPON_HGUN_BODY)
		reloadAnim = ANIM_HGUN_RELOAD;
	else if (weaponAnim == ANIM_WEAPON_AK_BODY)
		reloadAnim = ANIM_AK_RELOAD;

	if (reloadAnim != NUM_ANIMS)
		reloadAnimAssoc = RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, reloadAnim);

	if (bIsDucking)
		return;

	if (reloadAnimAssoc) {
		if (!CPed::IsPlayer() || ((CPlayerPed*)this)->field_1380)
			ClearAttack();

		return;
	}

	// BUG: We currently don't know any situation this cond. could be true.
	if (CTimer::GetTimeInMilliseconds() < m_lastHitTime)
		lastReloadWasInFuture = true;

	if (!weaponAnimAssoc) {
		weaponAnimAssoc = RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ourWeapon->m_Anim2ToPlay);
		delayBetweenAnimAndFire = ourWeapon->m_fAnim2FrameFire;

		// Long throw granade, molotov
		if (!weaponAnimAssoc && ourWeapon->m_bThrow) {
			weaponAnimAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_WEAPON_THROWU);
			delayBetweenAnimAndFire = 0.2f;
		}
	}
	if (weaponAnimAssoc) {
		animStart = ourWeapon->m_fAnimLoopStart;
		weaponAnimTime = weaponAnimAssoc->currentTime;
		if (weaponAnimTime > animStart && weaponAnimTime - weaponAnimAssoc->timeStep <= animStart) {
			if (ourWeapon->m_bCanAimWithArm)
				m_pedIK.m_flags |= CPedIK::FLAG_4;
			else
				m_pedIK.m_flags &= ~CPedIK::FLAG_4;
		}

		if (weaponAnimTime <= delayBetweenAnimAndFire || weaponAnimTime - weaponAnimAssoc->timeStep > delayBetweenAnimAndFire || !weaponAnimAssoc->IsRunning()) {
			if (weaponAnimAssoc->speed < 1.0f)
				weaponAnimAssoc->speed = 1.0f;

		} else {
			firePos = ourWeapon->m_vecFireOffset;
			if (ourWeaponType == WEAPONTYPE_BASEBALLBAT) {
				if (weaponAnimAssoc->animId == ourWeapon->m_Anim2ToPlay)
					firePos.z = 0.7f * ourWeapon->m_fRadius - 1.0f;

				firePos = GetMatrix() * firePos;
			} else if (ourWeaponType != WEAPONTYPE_UNARMED) {
				if (weaponAnimAssoc->animId == ANIM_KICK_FLOOR)
					frame = GetNodeFrame(PED_FOOTR);
				else
					frame = GetNodeFrame(PED_HANDR);

				for (; frame; frame = RwFrameGetParent(frame))
					RwV3dTransformPoints((RwV3d*)firePos, (RwV3d*)firePos, 1, RwFrameGetMatrix(frame));
			} else {
				firePos = GetMatrix() * firePos;
			}
			
			GetWeapon()->Fire(this, &firePos);

			if (ourWeaponType == WEAPONTYPE_MOLOTOV || ourWeaponType == WEAPONTYPE_GRENADE) {
				RemoveWeaponModel(ourWeapon->m_nModelId);
			}
			if (!GetWeapon()->m_nAmmoTotal && ourWeaponFire != WEAPON_FIRE_MELEE && FindPlayerPed() != this) {
				SelectGunIfArmed();
			}

			if (GetWeapon()->m_eWeaponState != WEAPONSTATE_MELEE_MADECONTACT) {
				// If reloading just began, start the animation
				if (GetWeapon()->m_eWeaponState == WEAPONSTATE_RELOADING && reloadAnim != NUM_ANIMS && !reloadAnimAssoc) {
					CAnimManager::BlendAnimation((RpClump*) m_rwObject, ASSOCGRP_STD, reloadAnim, 8.0f);
					ClearLookFlag();
					ClearAimFlag();
					m_ped_flagA4 = false;
					bIsPointingGunAt = false;
					m_lastHitTime = CTimer::GetTimeInMilliseconds();
					return;
				}
			} else {
				if (weaponAnimAssoc->animId == ANIM_WEAPON_BAT_V || weaponAnimAssoc->animId == ANIM_WEAPON_BAT_H) {
					DMAudio.PlayOneShot(m_audioEntityId, SOUND_WEAPON_BAT_ATTACK, 1.0f);
				} else if (weaponAnimAssoc->animId == ANIM_FIGHT_PPUNCH) {
					DMAudio.PlayOneShot(m_audioEntityId, SOUND_WEAPON_PUNCH_ATTACK, 0.0f);
				}

				weaponAnimAssoc->speed = 0.5f;

				// BUG: We currently don't know any situation this cond. could be true.
				if (m_ped_flagA4 || CTimer::GetTimeInMilliseconds() < m_lastHitTime) {
					weaponAnimAssoc->callbackType = 0;
				}
			}

			lastReloadWasInFuture = false;
		}

		if (ourWeaponType == WEAPONTYPE_SHOTGUN) {
			weaponAnimTime = weaponAnimAssoc->currentTime;
			firePos = ourWeapon->m_vecFireOffset;

			if (weaponAnimTime > 1.0f && weaponAnimTime - weaponAnimAssoc->timeStep <= 1.0f && weaponAnimAssoc->IsRunning()) {
				for (frame = GetNodeFrame(PED_HANDR); frame; frame = RwFrameGetParent(frame))
					RwV3dTransformPoints((RwV3d*)firePos, (RwV3d*)firePos, 1, RwFrameGetMatrix(frame));

				CVector gunshellPos(
					firePos.x - 0.6f * GetForward().x,
					firePos.y - 0.6f * GetForward().y,
					firePos.z - 0.15f * GetUp().z
				);

				CVector2D gunshellRot(
					GetRight().x,
					GetRight().y
				);

				gunshellRot.Normalise();
				GetWeapon()->AddGunshell(this, gunshellPos, gunshellRot, 0.025f);
			}
		}
		animLoopEnd = ourWeapon->m_fAnimLoopEnd;
		if (ourWeaponFire == WEAPON_FIRE_MELEE && weaponAnimAssoc->animId == ourWeapon->m_Anim2ToPlay)
			animLoopEnd = 3.4f/6.0f;

		weaponAnimTime = weaponAnimAssoc->currentTime;

		// Anim loop end, either start the loop again or finish the attack
		if (weaponAnimTime > animLoopEnd || !weaponAnimAssoc->IsRunning() && ourWeaponFire != WEAPON_FIRE_PROJECTILE) {

			if (weaponAnimTime - 2.0f * weaponAnimAssoc->timeStep <= animLoopEnd
				&& (m_ped_flagA4 || CTimer::GetTimeInMilliseconds() < m_lastHitTime)
				&& GetWeapon()->m_eWeaponState != WEAPONSTATE_RELOADING) {

				weaponAnim = weaponAnimAssoc->animId;
				if (ourWeaponFire != WEAPON_FIRE_MELEE || CheckForPedsOnGroundToAttack(((CPlayerPed*)this), nil) < PED_ON_THE_FLOOR) {
					if (weaponAnim != ourWeapon->m_Anim2ToPlay || weaponAnim == ANIM_RBLOCK_CSHOOT) {
						weaponAnimAssoc->Start(ourWeapon->m_fAnimLoopStart);
					} else {
						CAnimManager::BlendAnimation((RpClump*) m_rwObject, ASSOCGRP_STD, ourWeapon->m_AnimToPlay, 8.0f);
					}
				} else {
					if (weaponAnim == ourWeapon->m_Anim2ToPlay)
						weaponAnimAssoc->SetCurrentTime(0.1f);
					else
						CAnimManager::BlendAnimation((RpClump*) m_rwObject, ASSOCGRP_STD, ourWeapon->m_Anim2ToPlay, 8.0f);
				}
			} else {
				ClearAimFlag();

				// Echoes of bullets, at the end of the attack. (Bug: doesn't play while reloading)
				if (weaponAnimAssoc->currentTime - weaponAnimAssoc->timeStep <= ourWeapon->m_fAnimLoopEnd) {
					switch (ourWeaponType) {
						case WEAPONTYPE_UZI:
							DMAudio.PlayOneShot(m_audioEntityId, SOUND_WEAPON_UZI_BULLET_ECHO, 0.0f);
							break;
						case WEAPONTYPE_AK47:
							DMAudio.PlayOneShot(m_audioEntityId, SOUND_WEAPON_AK47_BULLET_ECHO, 0.0f);
							break;
						case WEAPONTYPE_M16:
							DMAudio.PlayOneShot(m_audioEntityId, SOUND_WEAPON_M16_BULLET_ECHO, 0.0f);
							break;
						default:
							break;
					}
				}

				// Fun fact: removing this part leds to reloading flamethrower
				if (ourWeaponType == WEAPONTYPE_FLAMETHROWER && weaponAnimAssoc->IsRunning()) {
					weaponAnimAssoc->flags |= ASSOC_DELETEFADEDOUT;
					weaponAnimAssoc->flags &= ~ASSOC_RUNNING;
					weaponAnimAssoc->blendDelta = -4.0f;
				}
			}
		}
		if (weaponAnimAssoc->currentTime > delayBetweenAnimAndFire)
			lastReloadWasInFuture = false;

		m_ped_flagA4 = lastReloadWasInFuture;
		return;
	}

	if (lastReloadWasInFuture) {
		if (ourWeaponFire != WEAPON_FIRE_PROJECTILE || !CPed::IsPlayer() || ((CPlayerPed*)this)->field_1380) {
			if (!CGame::nastyGame || ourWeaponFire != WEAPON_FIRE_MELEE || CheckForPedsOnGroundToAttack(((CPlayerPed*)this), nil) < PED_ON_THE_FLOOR) {
				weaponAnimAssoc = CAnimManager::BlendAnimation((RpClump*)m_rwObject, ASSOCGRP_STD, ourWeapon->m_AnimToPlay, 8.0f);
			} else {
				weaponAnimAssoc = CAnimManager::BlendAnimation((RpClump*)m_rwObject, ASSOCGRP_STD, ourWeapon->m_Anim2ToPlay, 8.0f);
			}

			weaponAnimAssoc->SetFinishCallback(CPed::FinishedAttackCB, this);
			weaponAnimAssoc->flags |= ASSOC_RUNNING;

			if (weaponAnimAssoc->currentTime == weaponAnimAssoc->hierarchy->totalLength)
				weaponAnimAssoc->SetCurrentTime(0.0f);

			if (CPed::IsPlayer()) {
				((CPlayerPed*)this)->field_1376 = 0.0f;
				((CPlayerPed*)this)->field_1380 = false;
			}
		}
	}
	else
		CPed::FinishedAttackCB(nil, this);
}

void
CPed::RemoveWeaponModel(int modelId)
{
	// modelId is not used!! This function just removes the current weapon.
	RwFrameForAllObjects(GetNodeFrame(PED_HANDR),RemoveAllModelCB,nil);
	m_wepModelID = -1;
}

void
CPed::SetCurrentWeapon(uint32 weaponType)
{
	CWeaponInfo *weaponInfo;
	if (HasWeapon(weaponType)) {
		weaponInfo = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);
		RemoveWeaponModel(weaponInfo->m_nModelId);

		m_currentWeapon = weaponType;

		weaponInfo = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);
		AddWeaponModel(weaponInfo->m_nModelId);
	}
}

// Only used while deciding which gun ped should switch to, if no ammo left.
bool
CPed::SelectGunIfArmed(void)
{
	for (int i = 0; i < m_maxWeaponTypeAllowed; i++) {
		if (GetWeapon(i).m_nAmmoTotal > 0) {
			eWeaponType weaponType = GetWeapon(i).m_eWeaponType;
			if (weaponType >= WEAPONTYPE_COLT45 && weaponType != WEAPONTYPE_M16 && weaponType <= WEAPONTYPE_FLAMETHROWER) {
				SetCurrentWeapon(i);
				return true;
			}
		}
	}
	SetCurrentWeapon(WEAPONTYPE_UNARMED);
	return false;
}

void
CPed::Duck(void)
{
	if (CTimer::GetTimeInMilliseconds() > m_duckTimer)
		ClearDuck();
}

void
CPed::ClearDuck(void)
{
	CAnimBlendAssociation *animAssoc;

	animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_DUCK_DOWN);
	if (!animAssoc)
		animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_DUCK_LOW);

	if (animAssoc) {

		if (bCrouchWhenShooting) {

			if (m_nPedState == PED_ATTACK || m_nPedState == PED_AIM_GUN) {
				animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_RBLOCK_CSHOOT);
				if (!animAssoc || animAssoc->blendDelta < 0.0f) {
					CAnimManager::BlendAnimation((RpClump*) m_rwObject, ASSOCGRP_STD, ANIM_RBLOCK_CSHOOT, 4.0f);
				}
			}
		}
	} else
		bIsDucking = false;
}

void
CPed::ClearPointGunAt(void)
{
	CAnimBlendAssociation *animAssoc;
	CWeaponInfo *weaponInfo;

	ClearLookFlag();
	ClearAimFlag();
	bIsPointingGunAt = false;
	if (m_nPedState == PED_AIM_GUN) {
		RestorePreviousState();
		weaponInfo = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);
		animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, weaponInfo->m_AnimToPlay);
		if (!animAssoc || animAssoc->blendDelta < 0.0f) {
			animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, weaponInfo->m_Anim2ToPlay);
		}
		if (animAssoc) {
			animAssoc->flags |= ASSOC_DELETEFADEDOUT;
			animAssoc->blendDelta = -4.0;
		}
	}
}

void
CPed::BeingDraggedFromCar(void)
{
	CAnimBlendAssociation *animAssoc;
	AnimationId enterAnim;
	bool dontRunAnim = false;
	PedLineUpPhase lineUpType;

	if (!m_pVehicleAnim) {
		CAnimManager::BlendAnimation((RpClump*) m_rwObject, m_animGroup, ANIM_IDLE_STANCE, 100.0f);
		animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_CAR_SIT);
		if (!animAssoc) {
			animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_CAR_LSIT);
			if (!animAssoc) {
				animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_CAR_SITP);
				if (!animAssoc)
					animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_CAR_SITPLO);
			}
		}
		if (animAssoc)
			animAssoc->blendDelta = -1000.0f;

		if (m_vehEnterType == CAR_DOOR_LF || m_vehEnterType == CAR_DOOR_LR) {
			if (m_ped_flagF10) {
				enterAnim = ANIM_CAR_QJACKED;
			} else if (m_pMyVehicle->bLowVehicle) {
				enterAnim = ANIM_CAR_LJACKED_LHS;
			} else {
				enterAnim = ANIM_CAR_JACKED_LHS;
			}
		} else if (m_vehEnterType == CAR_DOOR_RF || m_vehEnterType == CAR_DOOR_RR) {
			if (m_pMyVehicle->bLowVehicle)
				enterAnim = ANIM_CAR_LJACKED_RHS;
			else
				enterAnim = ANIM_CAR_JACKED_RHS;
		} else
			dontRunAnim = true;


		if (!dontRunAnim)
			m_pVehicleAnim = CAnimManager::AddAnimation((RpClump*) m_rwObject, ASSOCGRP_STD, enterAnim);

		m_pVehicleAnim->SetFinishCallback(PedSetDraggedOutCarCB, this);
		lineUpType = LINE_UP_TO_CAR_START;
	} else if (m_pVehicleAnim->currentTime <= 1.4f) {
		m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
		lineUpType = LINE_UP_TO_CAR_START;
	} else {
		lineUpType = LINE_UP_TO_CAR_2;
	}
	
	LineUpPedWithCar(lineUpType);
}

void
CPed::RestartNonPartialAnims(void)
{
	CAnimBlendAssociation *assoc;

	for (assoc = RpAnimBlendClumpGetFirstAssociation((RpClump*)m_rwObject); assoc; assoc = RpAnimBlendGetNextAssociation(assoc)) {
		if (!assoc->IsPartial())
			assoc->flags |= ASSOC_RUNNING;
	}
}

void
CPed::PedSetDraggedOutCarCB(CAnimBlendAssociation *dragAssoc, void *arg)
{
	CAnimBlendAssociation *quickJackedAssoc;
	CVehicle *vehicle; 
	CPed *ped = (CPed*)arg;
	eWeaponType weaponType = ped->GetWeapon()->m_eWeaponType;

	quickJackedAssoc = RpAnimBlendClumpGetAssociation((RpClump*) ped->m_rwObject, ANIM_CAR_QJACKED);
	if (ped->m_nPedState != PED_ARRESTED) {
		ped->m_nLastPedState = PED_NONE;
		if (dragAssoc)
			dragAssoc->blendDelta = -1000.0f;
	}
	ped->RestartNonPartialAnims();
	ped->m_pVehicleAnim = nil;
	ped->m_pSeekTarget = nil;
	vehicle = ped->m_pMyVehicle;

	vehicle->m_nGettingOutFlags &= ~GetVehDoorFlag(ped->m_vehEnterType);

	if (vehicle->pDriver == ped) {
		vehicle->RemoveDriver();
		if (vehicle->m_nDoorLock == CARLOCK_COP_CAR)
			vehicle->m_nDoorLock = CARLOCK_UNLOCKED;

		if (ped->m_nPedType == PEDTYPE_COP && vehicle->IsLawEnforcementVehicle())
			vehicle->ChangeLawEnforcerState(false);
	} else {
		for (int i = 0; i < vehicle->m_nNumMaxPassengers; i++) {
			if (vehicle->pPassengers[i] == ped) {
				vehicle->pPassengers[i] = nil;
				vehicle->m_nNumPassengers--;
			}
		}
	}

	ped->bInVehicle = false;
	if (ped->IsPlayer())
		AudioManager.PlayerJustLeftCar();

	if (quickJackedAssoc) {
		dragAssoc->SetDeleteCallback(PedSetQuickDraggedOutCarPositionCB, ped);
	} else {
		dragAssoc->SetDeleteCallback(PedSetDraggedOutCarPositionCB, ped);
		if (ped->CanSetPedState())
			CAnimManager::BlendAnimation((RpClump*) ped->m_rwObject, ASSOCGRP_STD, ANIM_GETUP1, 1000.0f);
	}

	// Only uzi can be used on cars, so previous weapon was stored
	if (ped->IsPlayer() && weaponType == WEAPONTYPE_UZI) {
		if (ped->m_storedWeapon != WEAPONTYPE_UNIDENTIFIED) {
			ped->SetCurrentWeapon(ped->m_storedWeapon);
			ped->m_storedWeapon = WEAPONTYPE_UNIDENTIFIED;
		}
	} else {
		ped->AddWeaponModel(CWeaponInfo::GetWeaponInfo(weaponType)->m_nModelId);
	}
	ped->m_nStoredActionState = 0;
	ped->m_ped_flagI4 = false;
}

void
CPed::GetLocalPositionToOpenCarDoor(CVector *output, CVehicle *veh, uint32 enterType, float seatPosMult)
{
	CVehicleModelInfo *vehModel; 
	CVector vehDoorPos;
	CVector vehDoorOffset;
	float seatOffset;

	vehModel = (CVehicleModelInfo*) CModelInfo::GetModelInfo(veh->m_modelIndex);
	if (veh->bIsVan && (enterType == CAR_DOOR_LR || enterType == CAR_DOOR_RR)) {
		seatOffset = 0.0f;
		vehDoorOffset = offsetToOpenVanDoor;
	} else {
		seatOffset = veh->m_handling->fSeatOffsetDistance * seatPosMult;
		if (veh->bLowVehicle) {
			vehDoorOffset = offsetToOpenLowCarDoor;
		} else {
			vehDoorOffset = offsetToOpenRegularCarDoor;
		}
	}

	switch (enterType) {
		case CAR_DOOR_RF:
			if (vehModel->m_vehicleType == VEHICLE_TYPE_BOAT)
				vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_BOAT_RUDDER];
			else
				vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_FRONT_SEATS];

			vehDoorPos.x += seatOffset;
			vehDoorOffset.x = -vehDoorOffset.x;
			break;

		case CAR_DOOR_RR:
			vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_REAR_SEATS];
			vehDoorPos.x += seatOffset;
			vehDoorOffset.x = -vehDoorOffset.x;
			break;

		case CAR_DOOR_LF:
			if (vehModel->m_vehicleType == VEHICLE_TYPE_BOAT)
				vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_BOAT_RUDDER];
			else
				vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_FRONT_SEATS];

			vehDoorPos.x = -(vehDoorPos.x + seatOffset);
			break;

		case CAR_DOOR_LR:
			vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_REAR_SEATS];
			vehDoorPos.x = -(vehDoorPos.x + seatOffset);
			break;

		default:
			if (vehModel->m_vehicleType == VEHICLE_TYPE_BOAT)
				vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_BOAT_RUDDER];
			else
				vehDoorPos = vehModel->m_positions[VEHICLE_DUMMY_FRONT_SEATS];

			vehDoorOffset = CVector(0.0f, 0.0f, 0.0f);
	}
	*output = vehDoorPos - vehDoorOffset;
}

// This function was mostly duplicate of GetLocalPositionToOpenCarDoor, so I've used it.
void
CPed::GetPositionToOpenCarDoor(CVector *output, CVehicle *veh, uint32 enterType)
{
	CVector localPos;
	CVector vehDoorPos;

	GetLocalPositionToOpenCarDoor(&localPos, veh, enterType, 1.0f);
	vehDoorPos = Multiply3x3(veh->GetMatrix(), localPos) + veh->GetPosition();

/*
	// Not used.
	CVector localVehDoorOffset;

	if (veh->bIsVan && (enterType == VEHICLE_ENTER_REAR_LEFT || enterType == VEHICLE_ENTER_REAR_RIGHT)) {
		localVehDoorOffset = offsetToOpenVanDoor;
	} else {
		if (veh->bIsLow) {
			localVehDoorOffset = offsetToOpenLowCarDoor;
		} else {
			localVehDoorOffset = offsetToOpenRegularCarDoor;
		}
	}

	vehDoorPosWithoutOffset = Multiply3x3(veh->GetMatrix(), localPos + localVehDoorOffset) + veh->GetPosition();
*/
	*output = vehDoorPos;
}

void
CPed::GetPositionToOpenCarDoor(CVector *output, CVehicle *veh, uint32 enterType, float offset)
{	
	CVector doorPos;
	CMatrix vehMat(veh->GetMatrix());

	GetLocalPositionToOpenCarDoor(output, veh, enterType, offset);
	doorPos = Multiply3x3(vehMat, *output);

	*output = veh->GetPosition() + doorPos;
}

void
CPed::LineUpPedWithCar(PedLineUpPhase phase)
{
	bool vehIsUpsideDown = false;
	int vehAnim;
	float seatPosMult = 0.0f;
	float currentZ;
	float adjustedTimeStep;

	if (CReplay::IsPlayingBack())
		return;

	if (!m_ped_flagC8 && phase != LINE_UP_TO_CAR_2) {
		if (RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ANIM_CAR_SIT)) {
			SetPedPositionInCar();
			return;
		}
		if (RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ANIM_CAR_LSIT)) {
			SetPedPositionInCar();
			return;
		}
		if (RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ANIM_CAR_SITP)) {
			SetPedPositionInCar();
			return;
		}
		if (RpAnimBlendClumpGetAssociation((RpClump*)m_rwObject, ANIM_CAR_SITPLO)) {
			SetPedPositionInCar();
			return;
		}
		m_ped_flagC8 = 1;
	}
	if (phase == LINE_UP_TO_CAR_START) {
		m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	}
	CVehicle *veh = m_pMyVehicle;

	// Not quite right, IsUpsideDown func. checks for <= -0.9f.
	// Since that function is also used in this file, doesn't this variable indicate upsidedownness?!
	if (veh->GetUp().z <= -0.8f)
		vehIsUpsideDown = true;

	if (m_vehEnterType == CAR_DOOR_RF || m_vehEnterType == CAR_DOOR_RR) {
		if (vehIsUpsideDown) {
			m_fRotationDest = -PI + veh->GetForward().Heading();
		} else if (veh->bIsBus) {
			m_fRotationDest = 0.5 * PI + veh->GetForward().Heading();
		} else {
			m_fRotationDest = veh->GetForward().Heading();
		}
	} else if (m_vehEnterType == CAR_DOOR_LF || m_vehEnterType == CAR_DOOR_LR) {
		if (vehIsUpsideDown) {
			m_fRotationDest = veh->GetForward().Heading();
		} else if (veh->bIsBus) {
			m_fRotationDest = -0.5 * PI + veh->GetForward().Heading();
		} else {
			m_fRotationDest = veh->GetForward().Heading();
		}
	}

	if (!bInVehicle)
		seatPosMult = 1.0f;

	if (m_pVehicleAnim) {
		vehAnim = m_pVehicleAnim->animId;

		switch (vehAnim) {
			case ANIM_CAR_JACKED_RHS:
			case ANIM_CAR_LJACKED_RHS:
			case ANIM_CAR_JACKED_LHS:
			case ANIM_CAR_LJACKED_LHS:
			case ANIM_CAR_QJACKED:
			case ANIM_CAR_GETOUT_LHS:
			case ANIM_CAR_GETOUT_LOW_LHS:
			case ANIM_CAR_GETOUT_RHS:
			case ANIM_CAR_GETOUT_LOW_RHS:
			case ANIM_CAR_CRAWLOUT_RHS:
			case ANIM_CAR_CRAWLOUT_RHS2:
			case ANIM_VAN_GETIN_L:
			case ANIM_VAN_GETOUT_L:
			case ANIM_VAN_GETIN:
			case ANIM_VAN_GETOUT:
				seatPosMult = m_pVehicleAnim->currentTime / m_pVehicleAnim->hierarchy->totalLength;
				break;
			case ANIM_CAR_QJACK:
			case ANIM_CAR_GETIN_LHS:
			case ANIM_CAR_GETIN_LOW_LHS:
			case ANIM_CAR_GETIN_RHS:
			case ANIM_CAR_GETIN_LOW_RHS:
			case ANIM_DRIVE_BOAT:
				seatPosMult = m_pVehicleAnim->GetTimeLeft() / m_pVehicleAnim->hierarchy->totalLength;
				break;
			case ANIM_CAR_CLOSEDOOR_LHS:
			case ANIM_CAR_CLOSEDOOR_LOW_LHS:
			case ANIM_CAR_CLOSEDOOR_RHS:
			case ANIM_CAR_CLOSEDOOR_LOW_RHS:
			case ANIM_CAR_SHUFFLE_RHS:
			case ANIM_CAR_LSHUFFLE_RHS:
				seatPosMult = 0.0f;
				break;
			case ANIM_CAR_CLOSE_LHS:
			case ANIM_CAR_CLOSE_RHS:
			case ANIM_COACH_OPEN_L:
			case ANIM_COACH_OPEN_R:
			case ANIM_COACH_IN_L:
			case ANIM_COACH_IN_R:
			case ANIM_COACH_OUT_L:
				seatPosMult = 1.0f;
				break;
			default:
				break;
		}
	}

	CVector neededPos;

	if (phase == LINE_UP_TO_CAR_2) {
		neededPos = GetPosition();
	} else {
		GetPositionToOpenCarDoor(&neededPos, veh, m_vehEnterType, seatPosMult);
	}

	CVector autoZPos = neededPos;

	if (veh->bIsInWater) {
		if (veh->m_vehType == VEHICLE_TYPE_BOAT && veh->IsUpsideDown())
			autoZPos.z += 1.0f;
	} else {
		CPedPlacement::FindZCoorForPed(&autoZPos);
	}

	if (phase == LINE_UP_TO_CAR_END || phase == LINE_UP_TO_CAR_2) {
		neededPos.z = GetPosition().z;

		// Getting out
		if (!veh->bIsBus || (veh->bIsBus && vehIsUpsideDown)) {
			float pedZSpeedOnExit = m_vecMoveSpeed.z - 0.008f * CTimer::GetTimeStep();

			// If we're not in ground at next step, apply animation
			if (neededPos.z + pedZSpeedOnExit >= autoZPos.z) {
				m_vecMoveSpeed.z = pedZSpeedOnExit;
				ApplyMoveSpeed();
				// Removing below line breaks the animation
				neededPos.z = GetPosition().z;
			} else {
				neededPos.z = autoZPos.z;
				m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
			}
		}
	}

	if (autoZPos.z > neededPos.z) {
		currentZ = GetPosition().z;
		if (m_pVehicleAnim && vehAnim != ANIM_VAN_GETIN_L && vehAnim != ANIM_VAN_CLOSE_L && vehAnim != ANIM_VAN_CLOSE && vehAnim != ANIM_VAN_GETIN) {
			neededPos.z = autoZPos.z;
			m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
		} else if (neededPos.z <= currentZ && m_pVehicleAnim && vehAnim != ANIM_VAN_CLOSE_L && vehAnim != ANIM_VAN_CLOSE) {
			adjustedTimeStep = min(m_pVehicleAnim->timeStep, 0.1f);

			// Smoothly change ped position
			neededPos.z = currentZ - (currentZ - neededPos.z) / (m_pVehicleAnim->GetTimeLeft() / adjustedTimeStep);
		}
	} else {
		// We may need to raise up the ped
		if (phase == LINE_UP_TO_CAR_START) {
			currentZ = GetPosition().z;

			if (neededPos.z > currentZ) {

				if (m_pVehicleAnim &&
					(vehAnim == ANIM_CAR_GETIN_RHS || vehAnim == ANIM_CAR_GETIN_LOW_RHS || vehAnim == ANIM_CAR_GETIN_LHS || vehAnim == ANIM_CAR_GETIN_LOW_LHS
						|| vehAnim == ANIM_CAR_QJACK || vehAnim == ANIM_VAN_GETIN_L || vehAnim == ANIM_VAN_GETIN)) {
					adjustedTimeStep = min(m_pVehicleAnim->timeStep, 0.1f);

					// Smoothly change ped position
					neededPos.z = (neededPos.z - currentZ) / (m_pVehicleAnim->GetTimeLeft() / adjustedTimeStep) + currentZ;
				} else if (m_nPedState == PED_ENTER_CAR || m_nPedState == PED_CARJACK) {
					neededPos.z = max(currentZ, autoZPos.z);
				}
			}
		}
	}

	bool stillGettingInOut = false;
	if (CTimer::GetTimeInMilliseconds() < m_nPedStateTimer)
		stillGettingInOut = veh->m_vehType != VEHICLE_TYPE_BOAT || m_ped_flagG10;

	if (!stillGettingInOut) {
		m_fRotationCur = m_fRotationDest;
	} else {
		float limitedAngle = CGeneral::LimitRadianAngle(m_fRotationDest);
		float timeUntilStateChange = (m_nPedStateTimer - CTimer::GetTimeInMilliseconds())/600.0f;

		m_vecOffsetSeek.z = 0.0;
		if (timeUntilStateChange <= 0.0f) {
			m_vecOffsetSeek.x = 0.0;
			m_vecOffsetSeek.y = 0.0;
		} else {
			neededPos -= timeUntilStateChange * m_vecOffsetSeek;
		}

		if (limitedAngle > PI + m_fRotationCur) {
			limitedAngle -= 2 * PI;
		} else if (limitedAngle < m_fRotationCur - PI) {
			limitedAngle += 2 * PI;
		}
		m_fRotationCur -= (m_fRotationCur - limitedAngle) * (1.0f - timeUntilStateChange);
	}

	if (seatPosMult > 0.2f || vehIsUpsideDown) {
		GetPosition() = neededPos;

		GetMatrix().SetRotate(0.0f, 0.0f, m_fRotationCur);

		// It will be all 0 after rotate.
		GetPosition() = neededPos;
	} else {
		CVector output;
		CMatrix vehDoorMat(veh->GetMatrix());

		GetLocalPositionToOpenCarDoor(&output, veh, m_vehEnterType, 0.0f);
		vehDoorMat.GetPosition() += Multiply3x3(vehDoorMat, output);
		GetMatrix() = vehDoorMat;
	}

}

static void
particleProduceFootDust(CPed *ped, CVector *pos, float size, int times)
{
	switch (ped->m_nSurfaceTouched)
	{
		case SURFACE_TARMAC:
		case SURFACE_DIRT:
		case SURFACE_PAVEMENT:
		case SURFACE_SAND:
			for (int i = 0; i < times; ++i) {
				CVector adjustedPos = *pos;
				adjustedPos.x += CGeneral::GetRandomNumberInRange(-0.1f, 0.1f);
				adjustedPos.y += CGeneral::GetRandomNumberInRange(-0.1f, 0.1f);
				CParticle::AddParticle(PARTICLE_PEDFOOT_DUST, adjustedPos, CVector(0.0f, 0.0f, 0.0f), nil, size, CRGBA(0, 0, 0, 0), 0, 0, 0, 0);
			}
			break;
		default:
			break;
	}
}

static void
particleProduceFootSplash(CPed *ped, CVector *pos, float size, int times)
{
	for (int i = 0; i < times; i++) {
		CVector adjustedPos = *pos;
		adjustedPos.x += CGeneral::GetRandomNumberInRange(-0.1f, 0.1f);
		adjustedPos.y += CGeneral::GetRandomNumberInRange(-0.1f, 0.1f);

		CVector direction = ped->GetForward() * -0.05f;
		CParticle::AddParticle(PARTICLE_RAIN_SPLASHUP, adjustedPos, direction, nil, size, CRGBA(32, 32, 32, 32), 0, 0, CGeneral::GetRandomNumberInRange(0, 1), 200);
	}
}

void
CPed::PlayFootSteps(void)
{
	if (bDoBloodyFootprints) {
		if (m_bloodyFootprintCount > 0 && m_bloodyFootprintCount < 300) {
			m_bloodyFootprintCount--;

			if (m_bloodyFootprintCount == 0)
				bDoBloodyFootprints = false;
		}
	}

	if (!bIsStanding)
		return;

	CAnimBlendAssociation *assoc = RpAnimBlendClumpGetFirstAssociation((RpClump*)m_rwObject);
	CAnimBlendAssociation *walkRunAssoc = nil;
	float walkRunAssocBlend = 0.0f, idleAssocBlend = 0.0f;

	for (; assoc; assoc = RpAnimBlendGetNextAssociation(assoc)) {
		if (assoc->flags & ASSOC_FLAG80) {
			walkRunAssoc = assoc;
			walkRunAssocBlend += assoc->blendAmount;
		} else if ((assoc->flags & ASSOC_FLAG200) == 0) {
			idleAssocBlend += assoc->blendAmount;
		}
	}

	if (walkRunAssoc && walkRunAssocBlend > 0.5f && idleAssocBlend < 1.0f) {
		float stepStart = 1 / 15.0f;
		float stepEnd = walkRunAssoc->hierarchy->totalLength / 2.0f + stepStart;
		float currentTime = walkRunAssoc->currentTime;
		int stepPart = 0;

		if (currentTime >= stepStart && currentTime - walkRunAssoc->timeStep < stepStart)
			stepPart = 1;
		else if (currentTime >= stepEnd && currentTime - walkRunAssoc->timeStep < stepEnd)
			stepPart = 2;

		if (stepPart != 0) {
			DMAudio.PlayOneShot(m_audioEntityId, stepPart == 1 ? SOUND_STEP_START : SOUND_STEP_END, 1.0f);
			CVector footPos(0.0f, 0.0f, 0.0f);

			for (RwFrame *frame = GetNodeFrame(stepPart == 1 ? PED_FOOTL : PED_FOOTR); frame; frame = RwFrameGetParent(frame))
				RwV3dTransformPoints(footPos, footPos, 1, RwFrameGetMatrix(frame));

			CVector forward = GetForward();

			footPos.z -= 0.1f;
			footPos += 0.2f * forward;

			if (bDoBloodyFootprints) {
				CVector2D top(forward * 0.26f);
				CVector2D right(GetRight() * 0.14f);

				CShadows::AddPermanentShadow(1, gpBloodPoolTex, &footPos,
					top.x, top.y,
					right.x, right.y,
					255, 255, 0, 0, 4.0f, 3000.0f, 1.0f);

				if (m_bloodyFootprintCount <= 20) {
					m_bloodyFootprintCount = 0;
					bDoBloodyFootprints = false;
				} else {
					m_bloodyFootprintCount -= 20;
				}
			}
			if (CWeather::Rain <= 0.1f || CCullZones::CamNoRain() || CCullZones::PlayerNoRain()) {
				if(IsPlayer())
					particleProduceFootDust(this, &footPos, 0.0f, 4);
			} else if(stepPart == 2) {
				particleProduceFootSplash(this, &footPos, 0.15f, 4);
			}
		}
	}

	if (m_nSurfaceTouched == SURFACE_PUDDLE) {
		float pedSpeed = CVector2D(m_vecMoveSpeed).Magnitude();
		if (pedSpeed > 0.03f && CTimer::GetFrameCounter() % 2 == 0 && pedSpeed > 0.13f) {
			float particleSize = pedSpeed * 2.0f;

			if (particleSize < 0.25f)
				particleSize = 0.25f;

			if (particleSize > 0.75f)
				particleSize = 0.75f;

			CVector particlePos = GetPosition() + GetForward() * 0.3f;
			particlePos.z -= 1.2f;

			CVector particleDir = m_vecMoveSpeed * 0.75f;

			particleDir.z = CGeneral::GetRandomNumberInRange(0.01f, 0.03f);
			CParticle::AddParticle(PARTICLE_PED_SPLASH, particlePos, particleDir, nil, 0.8f * particleSize, CRGBA(155,155,185,128), 0, 0, 0, 0);

			particleDir.z = CGeneral::GetRandomNumberInRange(0.03f, 0.05f);
			CParticle::AddParticle(PARTICLE_RUBBER_SMOKE, particlePos, particleDir, nil, particleSize, CRGBA(255,255,255,255), 0, 0, 0, 0);
		}
	}
}

bool
CPed::IsPointerValid(void)
{
	int8 pedIndex = CPools::GetPedPool()->GetIndex(this) >> 8;
	if (pedIndex < 0 || pedIndex >= NUMPEDS)
		return false;

	if (m_entryInfoList.first || FindPlayerPed() == this)
		return true;

	return false;
}

// Some kind of binary sort
void
CPed::SortPeds(CPed **list, int min, int max)
{
	if (min >= max)
		return;

	CVector leftDiff, rightDiff;
	CVector middleDiff = GetPosition() - list[(max + min) / 2]->GetPosition();
	float middleDist = middleDiff.Magnitude();

	int left = max;
	int right;
	for(right = min; right <= left; ){
		// Those 1.0s are to make sure loop always run for first time.
		for (float rightDist = middleDist-1.0f; middleDist > rightDist; right++) {
			rightDiff = GetPosition() - list[right]->GetPosition();
			rightDist = rightDiff.Magnitude();
		}
		right--;

		for (float leftDist = middleDist+1.0f; middleDist < leftDist; left--) {
			leftDiff = GetPosition() - list[left]->GetPosition();
			leftDist = leftDiff.Magnitude();
		}
		left++;

		if (right <= left) {
			CPed *ped = list[right];
			list[right] = list[left];
			list[left] = ped;
			right++;
			left--;
		}
	}
	SortPeds(list, min, left);
	SortPeds(list, right, max);
}

void
CPed::BuildPedLists(void)
{
	static CPed *unsortedNearPeds[10];
	uint16 nextNearPedSlot = 0;

	if ((CTimer::GetFrameCounter() + m_randomSeed) & 15) {

		for(int i = 0; i < 10; ) {
			if (m_nearPeds[i]) {
				if (m_nearPeds[i]->IsPointerValid()) {
					float distSqr = (GetPosition() - m_nearPeds[i]->GetPosition()).MagnitudeSqr2D();
					if (distSqr < 900.0f) {
						i++;
						continue;
					}
				}

				// If we arrive here, the ped we're checking isn't "near", so we should remove it.
				for (int j = i; j < 9; j++) {
					m_nearPeds[j] = m_nearPeds[j + 1];
					m_nearPeds[j + 1] = nil;
				}
				// Above loop won't work when it's 9, so we need to empty slot 9.
				m_nearPeds[9] = nil;
				m_numNearPeds--;
			} else
				i++;
		}
	} else {
		CVector centre = CEntity::GetBoundCentre();
		CRect rect(
			(centre.x - 20.0f) * 0.025f + 50.0f,
			(centre.y - 20.0f) * 0.025f + 50.0f,
			(centre.x + 20.0f) * 0.025f + 50.0f,
			(centre.y + 20.0f) * 0.025f + 50.0f);

		for(int y = rect.top; y <= rect.bottom; y++) {
			for(int x = rect.left; x <= rect.right; x++) {
				for (CPtrNode *pedPtrNode = CWorld::GetSector(x,y)->m_lists[ENTITYLIST_PEDS].first; pedPtrNode; pedPtrNode = pedPtrNode->next) {
					CPed *ped = (CPed*)pedPtrNode->item;
					if (ped != this && !ped->bInVehicle) {
						float dist = (ped->GetPosition() - GetPosition()).Magnitude2D();
						if (distanceMultToCountPedNear * 30.0f > dist)
						{
							unsortedNearPeds[nextNearPedSlot] = ped;
							nextNearPedSlot++;
						}
					}
				}
			}
		}
		unsortedNearPeds[nextNearPedSlot] = nil;
		SortPeds(unsortedNearPeds, 0, nextNearPedSlot - 1);
		for (m_numNearPeds = 0; m_numNearPeds < 10; m_numNearPeds++) {
			CPed *ped = unsortedNearPeds[m_numNearPeds];
			if (!ped)
				break;

			m_nearPeds[m_numNearPeds] = ped;
		}
		for (int pedToClear = m_numNearPeds; pedToClear < 10; pedToClear++)
			m_nearPeds[pedToClear] = nil;
	}
}

void
CPed::SetPedStats(ePedStats pedStat)
{
	m_pedStats = CPedStats::ms_apPedStats[pedStat];
}

void
CPed::SetModelIndex(uint32 mi)
{
	CEntity::SetModelIndex(mi);
	RpAnimBlendClumpInit((RpClump*) m_rwObject);
	RpAnimBlendClumpFillFrameArray((RpClump*) m_rwObject, m_pFrames);
	CPedModelInfo *modelInfo = (CPedModelInfo*)CModelInfo::GetModelInfo(m_modelIndex);
	SetPedStats((ePedStats) modelInfo->m_pedStatType);
	m_headingRate = m_pedStats->m_headingChangeRate;
	m_animGroup = (AssocGroupId) modelInfo->m_animGroup;
	CAnimManager::AddAnimation((RpClump*) m_rwObject, m_animGroup, ANIM_IDLE_STANCE);

	// This is a mistake by R*, velocity is CVector, whereas m_vecAnimMoveDelta is CVector2D. 
	(*RPANIMBLENDCLUMPDATA(m_rwObject))->velocity = (CVector*) &m_vecAnimMoveDelta;
}

void
CPed::RemoveLighting(bool reset)
{
	CRenderer::RemoveVehiclePedLights(this, reset);
}

bool
CPed::SetupLighting(void)
{
	ActivateDirectional();
	SetAmbientColoursForPedsCarsAndObjects();

	if (bRenderScorched) {
		WorldReplaceNormalLightsWithScorched(Scene.world, 0.1f);
	} else {
		// Note that this lightMult is only affected by LIGHT_DARKEN. If there's no LIGHT_DARKEN, it will be 1.0.
		float lightMult = CPointLights::GenerateLightsAffectingObject(&GetPosition());
		if (!bHasBlip && lightMult != 1.0f) {
			SetAmbientAndDirectionalColours(lightMult);
			return true;
		}
	}
	return false;
}

void
CPed::Teleport(CVector pos)
{
	CWorld::Remove(this);
	GetPosition() = pos;
	bIsStanding = false;
	m_nPedStateTimer = 0;
	m_actionX = 0.0f;
	m_actionY = 0.0f;
	m_pDamageEntity = nil;
	CWorld::Add(this);
}

void
CPed::CalculateNewOrientation(void)
{
	if (CReplay::IsPlayingBack() || !IsPedInControl())
		return;

	CVector pos = GetPosition();

	GetMatrix().SetRotate(0.0f, 0.0f, m_fRotationCur);
	
	// Because SetRotate makes pos. all 0
	GetPosition() = pos;
}

float
CPed::WorkOutHeadingForMovingFirstPerson(float offset)
{
	if (!IsPlayer())
		return 0.0f;

	CPad *pad0 = CPad::GetPad(0);
	float leftRight = pad0->GetPedWalkLeftRight();
	float upDown = pad0->GetPedWalkUpDown();
	float &angle = ((CPlayerPed*)this)->m_fWalkAngle;

	if (upDown != 0.0f) {
		angle = CGeneral::GetRadianAngleBetweenPoints(0.0f, 0.0f, -leftRight, upDown);
	} else {
		if (leftRight < 0.0f)
			angle = 0.5 * PI;
		else if (leftRight > 0.0f)
			angle = -0.5 * PI;
	}

	return CGeneral::LimitRadianAngle(offset + angle);
}

void
CPed::CalculateNewVelocity(void)
{
	if (IsPedInControl()) {
		float headAmount = DEGTORAD(m_headingRate) * CTimer::GetTimeStep();
		m_fRotationCur = CGeneral::LimitRadianAngle(m_fRotationCur);
		float limitedRotDest = CGeneral::LimitRadianAngle(m_fRotationDest);

		if (m_fRotationCur - PI > limitedRotDest) {
				limitedRotDest += 2 * PI;
		} else if(PI + m_fRotationCur < limitedRotDest) {
			limitedRotDest -= 2 * PI;
		}

		if (IsPlayer() && m_nPedState == PED_ATTACK)
			headAmount /= 4.0f;

		float neededTurn = limitedRotDest - m_fRotationCur;
		if (neededTurn <= headAmount) {
			if (neededTurn > (-headAmount))
				m_fRotationCur += neededTurn;
			else
				m_fRotationCur -= headAmount;
		} else {
			m_fRotationCur += headAmount;
		}
	}

	CVector2D forward(Sin(m_fRotationCur), Cos(m_fRotationCur));

	m_moved.x = CrossProduct2D(m_vecAnimMoveDelta, forward); // (m_vecAnimMoveDelta.x * Cos(m_fRotationCur)) + -Sin(m_fRotationCur) * m_vecAnimMoveDelta.y;
	m_moved.y = DotProduct2D(m_vecAnimMoveDelta, forward);  // m_vecAnimMoveDelta.y* Cos(m_fRotationCur) + (m_vecAnimMoveDelta.x * Sin(m_fRotationCur));

	if (CTimer::GetTimeStep() >= 0.01f) {
		m_moved = m_moved * (1 / CTimer::GetTimeStep());
	} else {
		m_moved = m_moved * (1 / 100.0f);
	}

	if ((!TheCamera.Cams[TheCamera.ActiveCam].GetWeaponFirstPersonOn() && !TheCamera.Cams[0].Using3rdPersonMouseCam())
		|| FindPlayerPed() != this || !CanStrafeOrMouseControl())
		return;

	float walkAngle = WorkOutHeadingForMovingFirstPerson(m_fRotationCur);
	float pedSpeed = m_moved.Magnitude();
	float localWalkAngle = CGeneral::LimitRadianAngle(walkAngle - m_fRotationCur);

	if (localWalkAngle < -0.5 * PI) {
		localWalkAngle += PI;
	} else if (localWalkAngle > 0.5 * PI) {
		localWalkAngle -= PI;
	}

	// Interestingly this part is responsible for diagonal walking.
	if (localWalkAngle > -DEGTORAD(50.0f) && localWalkAngle < DEGTORAD(50.0f)) {
		TheCamera.Cams[TheCamera.ActiveCam].m_fPlayerVelocity = pedSpeed;
		m_moved = CVector2D(-Sin(walkAngle), Cos(walkAngle)) * pedSpeed;
	}

	CAnimBlendAssociation *idleAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_IDLE_STANCE);
	CAnimBlendAssociation* fightAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_FIGHT_IDLE);

	if ((!idleAssoc || idleAssoc->blendAmount < 0.5f) && !fightAssoc) {
		LimbOrientation newUpperLegs;
		newUpperLegs.phi = localWalkAngle;

		if (newUpperLegs.phi < -DEGTORAD(100.0f)) {
			newUpperLegs.phi += PI;
		} else if (newUpperLegs.phi > DEGTORAD(100.0f)) {
			newUpperLegs.phi -= PI;
		}

		if (newUpperLegs.phi > -DEGTORAD(50.0f) && newUpperLegs.phi < DEGTORAD(50.0f)) {
			newUpperLegs.theta = 0.0f;
			m_pedIK.RotateTorso(m_pFrames[PED_UPPERLEGL], &newUpperLegs, false);
			m_pedIK.RotateTorso(m_pFrames[PED_UPPERLEGR], &newUpperLegs, false);
		}
	}
}

bool
CPed::CanBeDeleted(void)
{
	if (this->bInVehicle)
		return false;

	switch (CharCreatedBy) {
		case RANDOM_CHAR:
			return true;
		case MISSION_CHAR:
			return false;
		default:
			return true;
	}
}

bool
CPed::CanPedDriveOff(void)
{
	if (m_nPedState != PED_DRIVING || m_lookTimer > CTimer::GetTimeInMilliseconds())
		return false;

	for (int i = 0; i < m_numNearPeds; i++) {
		CPed *ped = m_nearPeds[i];
		if (ped->m_nPedType == m_nPedType && ped->m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER && ped->m_carInObjective == m_carInObjective) {
			m_lookTimer = CTimer::GetTimeInMilliseconds() + 1000;
			return false;
		}
	}
	return true;
}

// I couldn't find where it is used.
bool
CPed::CanPedJumpThis(int32 unused)
{
	CVector2D forward(-Sin(m_fRotationCur), Cos(m_fRotationCur));
	CVector pos = GetPosition();
	// wat?
	CVector forwardPos(
		forward.x + pos.x,
		forward.y + pos.y,
		pos.z);
	return CWorld::GetIsLineOfSightClear(pos, forwardPos, true, false, false, true, false, false, false);
}

bool
CPed::CanPedReturnToState(void)
{
	return m_nPedState <= PED_STATES_NO_AI && m_nPedState != PED_AIM_GUN && m_nPedState != PED_ATTACK &&
		m_nPedState != PED_FIGHT && m_nPedState != PED_STEP_AWAY && m_nPedState != PED_SNIPER_MODE && m_nPedState != PED_LOOK_ENTITY;
}

bool
CPed::CanSeeEntity(CEntity *entity, float threshold)
{
	float neededAngle = CGeneral::GetRadianAngleBetweenPoints(
		entity->GetPosition().x,
		entity->GetPosition().x,
		GetPosition().x,
		GetPosition().y);

	if (neededAngle < 0.0f)
		neededAngle += 2 * PI;
	else if (neededAngle > 2 * PI)
		neededAngle -= 2 * PI;

	float ourAngle = m_fRotationCur;
	if (ourAngle < 0.0f)
		ourAngle += 2 * PI;
	else if (ourAngle > 2 * PI)
		ourAngle -= 2 * PI;

	float neededTurn = Abs(neededAngle - ourAngle);

	return neededTurn < threshold || 2 * PI - threshold < neededTurn;
}

bool
CPed::IsTemporaryObjective(eObjective objective)
{
	return objective == OBJECTIVE_LEAVE_VEHICLE || objective == OBJECTIVE_SET_LEADER ||
		objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER;
}

void
CPed::SetMoveState(eMoveState state)
{
	m_nMoveState = state;
}

void
CPed::SetObjectiveTimer(int time)
{
	if (time == 0) {
		m_objectiveTimer = 0;
	} else if (CTimer::GetTimeInMilliseconds() > m_objectiveTimer) {
		m_objectiveTimer = CTimer::GetTimeInMilliseconds() + time;
	}
}

void
CPed::ForceStoredObjective(eObjective objective)
{
	if (objective != OBJECTIVE_ENTER_CAR_AS_DRIVER && objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER) {
		m_prevObjective = m_objective;
		return;
	}

	switch (m_objective)
	{
		case OBJECTIVE_FLEE_TILL_SAFE:
		case OBJECTIVE_KILL_CHAR_ON_FOOT:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT:
		case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
		case OBJECTIVE_ENTER_CAR_AS_DRIVER:
		case OBJECTIVE_GOTO_AREA_ON_FOOT:
		case OBJECTIVE_RUN_TO_AREA:
			return;
		default:
			m_prevObjective = m_objective;
	}
}

void
CPed::SetStoredObjective(void)
{
	if (m_objective == m_prevObjective)
		return;

	switch (m_objective)
	{
		case OBJECTIVE_FLEE_TILL_SAFE:
		case OBJECTIVE_KILL_CHAR_ON_FOOT:
		case OBJECTIVE_KILL_CHAR_ANY_MEANS:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT:
		case OBJECTIVE_FOLLOW_PED_IN_FORMATION:
		case OBJECTIVE_LEAVE_VEHICLE:
		case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
		case OBJECTIVE_ENTER_CAR_AS_DRIVER:
		case OBJECTIVE_GOTO_AREA_ON_FOOT:
		case OBJECTIVE_RUN_TO_AREA:
			return;
		default:
			m_prevObjective = m_objective;
	}
}

void
CPed::RestorePreviousObjective(void)
{
	if (m_objective == OBJECTIVE_NONE)
		return;

	if (m_objective != OBJECTIVE_LEAVE_VEHICLE && m_objective != OBJECTIVE_ENTER_CAR_AS_PASSENGER && m_objective != OBJECTIVE_ENTER_CAR_AS_DRIVER)
		m_pedInObjective = nil;

	if (m_objective == OBJECTIVE_WAIT_IN_CAR_THEN_GETOUT) {
		m_objective = OBJECTIVE_NONE;
		if (m_pMyVehicle)
			SetObjective(OBJECTIVE_LEAVE_VEHICLE, m_pMyVehicle);

	} else {
		m_objective = m_prevObjective;
		m_prevObjective = OBJECTIVE_NONE;
	}
	m_ped_flagD40 = false;
}

void
CPed::SetLeader(CEntity *leader)
{
	m_leader = (CPed*)leader;

	if(m_leader)
		m_leader->RegisterReference((CEntity **)&m_leader);
}

void
CPed::SetObjective(eObjective newObj, void *entity)
{
	if (m_nPedState == PED_DIE || m_nPedState == PED_DEAD)
		return;

	if (m_prevObjective == newObj) {
		// Why?
		if (m_prevObjective != OBJECTIVE_NONE)
			return;
	}

	if (entity == this)
		return;

	SetObjectiveTimer(0);
	if (m_objective == newObj) {
		switch (newObj) {
			case OBJECTIVE_KILL_CHAR_ON_FOOT:
			case OBJECTIVE_KILL_CHAR_ANY_MEANS:
			case OBJECTIVE_GOTO_CHAR_ON_FOOT:
			case OBJECTIVE_FOLLOW_PED_IN_FORMATION:
			case OBJECTIVE_GOTO_AREA_ANY_MEANS:
			case OBJECTIVE_FIGHT_CHAR:
				if (m_pedInObjective == entity)
					return;

				break;
			case OBJECTIVE_LEAVE_VEHICLE:
			case OBJECTIVE_FLEE_CAR:
				return;
			case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
			case OBJECTIVE_ENTER_CAR_AS_DRIVER:
			case OBJECTIVE_DESTROY_CAR:
			case OBJECTIVE_SOLICIT:
			case OBJECTIVE_BUY_ICE_CREAM:
				if (m_carInObjective == entity)
					return;

				break;
			case OBJECTIVE_SET_LEADER:
				if (m_leader == entity)
					return;

				break;
			default:
				break;
		}
	} else {
		if (newObj == OBJECTIVE_LEAVE_VEHICLE && !bInVehicle)
			return;
	}

	m_ped_flagD40 = false;
	if (!IsTemporaryObjective(m_objective) || IsTemporaryObjective(newObj)) {
		if (m_objective != newObj) {
			if (IsTemporaryObjective(newObj))
				ForceStoredObjective(newObj);
			else
				SetStoredObjective();
		}
		m_objective = newObj;
	} else {
		m_prevObjective = newObj;
	}

	switch (newObj) {
		case OBJECTIVE_WAIT_IN_CAR_THEN_GETOUT:

			// In this special case, entity parameter isn't CEntity, but int.
			SetObjectiveTimer((int)entity);
			return;
		case OBJECTIVE_KILL_CHAR_ON_FOOT:
		case OBJECTIVE_KILL_CHAR_ANY_MEANS:
		case OBJECTIVE_MUG_CHAR:
			m_pLastPathNode = nil;
			m_ped_flagD20 = false;
			m_vecSeekVehicle = CVector(0.0f, 0.0f, 0.0f);
			m_pedInObjective = (CPed*)entity;
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			m_pLookTarget = (CEntity*)entity;
			m_pLookTarget->RegisterReference((CEntity**)&m_pLookTarget);
			return;
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE:
		case OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS:
		case OBJECTIVE_GOTO_CHAR_ON_FOOT:
		case OBJECTIVE_FIGHT_CHAR:
			m_vecSeekVehicle = CVector(0.0f, 0.0f, 0.0f);
			m_pedInObjective = (CPed*)entity;
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			return;
		case OBJECTIVE_FOLLOW_PED_IN_FORMATION:
			m_pedInObjective = (CPed*)entity;
			m_pedInObjective->RegisterReference((CEntity**)&m_pedInObjective);
			m_pedFormation = 1;
			return;
		case OBJECTIVE_LEAVE_VEHICLE:
		case OBJECTIVE_FLEE_CAR:
			m_carInObjective = (CVehicle*)entity;
			m_carInObjective->RegisterReference((CEntity **)&m_carInObjective);
			if (!m_carInObjective->bIsBus || m_leaveCarTimer)
				return;
			break;
		case OBJECTIVE_ENTER_CAR_AS_PASSENGER:
		case OBJECTIVE_ENTER_CAR_AS_DRIVER:
			if (m_nMoveState == PEDMOVE_STILL)
				SetMoveState(PEDMOVE_RUN);

			if (((CVehicle*)entity)->m_vehType == VEHICLE_TYPE_BOAT && !IsPlayer()) {
				RestorePreviousObjective();
				return;
			}
			// fall through
		case OBJECTIVE_DESTROY_CAR:
		case OBJECTIVE_SOLICIT:
		case OBJECTIVE_BUY_ICE_CREAM:
			m_carInObjective = (CVehicle*)entity;
			m_carInObjective->RegisterReference((CEntity**)&m_carInObjective);
			m_pSeekTarget = m_carInObjective;
			m_pSeekTarget->RegisterReference((CEntity**)&m_pSeekTarget);
			m_vecSeekVehicle = CVector(0.0f, 0.0f, 0.0f);
			if (newObj == OBJECTIVE_SOLICIT) {
				m_objectiveTimer = CTimer::GetTimeInMilliseconds() + 10000;
			} else if (m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER && CharCreatedBy == MISSION_CHAR &&
					(m_carInObjective->m_status == STATUS_PLAYER_DISABLED || CPad::GetPad(CWorld::PlayerInFocus)->DisablePlayerControls)) {
				SetObjectiveTimer(14000);
			} else {
				m_objectiveTimer = 0;
			}
			return;
		case OBJECTIVE_SET_LEADER:
			SetLeader((CEntity*)entity);
			RestorePreviousObjective();
			return;
		default:
			return;
	}
	for (int i=0; i < m_carInObjective->m_nNumMaxPassengers; i++) {
		if (m_carInObjective->pPassengers[i] == this) {
			m_leaveCarTimer = CTimer::GetTimeInMilliseconds() + 1200 * i;
			return;
		}
	}
}

void
CPed::SetIdle(void)
{
	if (m_nPedState != PED_IDLE && m_nPedState != PED_MUG && m_nPedState != PED_FLEE_ENTITY) {
		m_nPedState = PED_IDLE;
		SetMoveState(PEDMOVE_STILL);
	}
	if (m_nWaitState == WAITSTATE_FALSE) {
		m_nWaitTimer = CTimer::GetTimeInMilliseconds() + CGeneral::GetRandomNumberInRange(2000, 4000);
	}
}

void
CPed::SetObjective(eObjective newObj)
{
	if (m_nPedState == PED_DIE || m_nPedState == PED_DEAD)
		return;

	if (newObj == OBJECTIVE_NONE) {
		if ((m_objective == OBJECTIVE_LEAVE_VEHICLE || m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER || m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER)
			&& IsPedInControl()) {

			m_ped_flagG8 = true;
			return;
		}
		// Unused code from assembly...
		/*
		else if(m_objective == OBJECTIVE_FLEE_CAR) {

		} else {

		}
		*/
		m_objective = newObj;
		m_prevObjective = OBJECTIVE_NONE;
	} else if (m_prevObjective != newObj || m_prevObjective == OBJECTIVE_NONE) {
		SetObjectiveTimer(0);

		if (m_objective == newObj)
			return;

		if (IsTemporaryObjective(m_objective)) {
			m_prevObjective = newObj;
		} else {
			if (m_objective != newObj)
				SetStoredObjective();

			m_objective = newObj;
		}
		m_ped_flagD40 = false;

		switch (newObj) {
			case OBJECTIVE_NONE:
				m_prevObjective = OBJECTIVE_NONE;
				break;
			case OBJECTIVE_HAIL_TAXI:
				m_nWaitTimer = 0;
				SetIdle();
				SetMoveState(PEDMOVE_STILL);
				break;
			default:
				break;
		}
	}
}

// Only used in 01E1: SET_CHAR_OBJ_FOLLOW_ROUTE opcode
// IDA fails very badly in here, puts a fake loop and ignores SetFollowRoute call...
void
CPed::SetObjective(eObjective newObj, int16 routePoint, int16 routeType)
{
	if (m_nPedState == PED_DIE || m_nPedState == PED_DEAD)
		return;

	if (m_prevObjective == newObj && m_prevObjective != OBJECTIVE_NONE)
		return;

	SetObjectiveTimer(0);

	if (m_objective == newObj && newObj == OBJECTIVE_FOLLOW_ROUTE && m_routeLastPoint == routePoint && m_routeType == routeType)
		return;

	m_ped_flagD40 = false;
	if (IsTemporaryObjective(m_objective)) {
		m_prevObjective = newObj;
	} else {
		if (m_objective != newObj)
			SetStoredObjective();

		m_objective = newObj;
	}

	if (newObj == OBJECTIVE_FOLLOW_ROUTE) {
		SetFollowRoute(routePoint, routeType);
	}
}

void
CPed::ClearChat(void)
{
	CAnimBlendAssociation *animAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_IDLE_CHAT);
	if (animAssoc) {
		animAssoc->blendDelta = -8.0f;
		animAssoc->flags |= ASSOC_DELETEFADEDOUT;
	}
	bIsTalking = false;
	ClearLookFlag();
	RestorePreviousState();
}

bool
CPed::IsGangMember(void)
{
	return m_nPedType >= PEDTYPE_GANG1 && m_nPedType <= PEDTYPE_GANG9;
}

void
CPed::InformMyGangOfAttack(CEntity *attacker)
{
	CPed *attackerPed;

	if (m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT || m_objective == OBJECTIVE_KILL_CHAR_ANY_MEANS)
		return;

	if (attacker->IsPed()) {
		attackerPed = (CPed*)attacker;
	} else {
		if (!attacker->IsVehicle())
			return;

		attackerPed = ((CVehicle*)attacker)->pDriver;
		if (!attackerPed)
			return;
	}

	if (attackerPed->m_nPedType == PEDTYPE_COP)
		return;

	for (int i = 0; i < m_numNearPeds; i++)	{
		CPed *nearPed = m_nearPeds[i];
		if (nearPed && nearPed != this) {
			CPed *leader = nearPed->m_leader;
			if (leader && leader == this && nearPed->m_pedStats->m_fear < nearPed->m_pedStats->m_temper)
			{
				nearPed->SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, attackerPed);
				nearPed->SetObjectiveTimer(30000);
			}
		}
	}
}

void
CPed::QuitEnteringCar(void)
{
	CAnimBlendAssociation *animAssoc = m_pVehicleAnim;
	CVehicle *veh = m_pMyVehicle;
	if (animAssoc)
		animAssoc->blendDelta = -1000.0f;
	
	RestartNonPartialAnims();

	if (!RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_IDLE_STANCE))
		CAnimManager::BlendAnimation((RpClump*) m_rwObject, m_animGroup, ANIM_IDLE_STANCE, 100.0f);
	
	if (veh) {
		if (m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER || m_nPedState == PED_CARJACK)
			veh->m_veh_flagC10 = false;

		if (veh->m_nNumGettingIn != 0)
			veh->m_nNumGettingIn--;

		veh->m_nGettingInFlags = ~GetVehDoorFlag(m_vehEnterType);
	}

	bUsesCollision = true;

	if (IsPlayer() && GetWeapon()->m_eWeaponType == WEAPONTYPE_UZI) {
		if (IsPlayer() && m_storedWeapon != WEAPONTYPE_UNIDENTIFIED) {
			SetCurrentWeapon(m_storedWeapon);
			m_storedWeapon = WEAPONTYPE_UNIDENTIFIED;
		}
	} else {
		CWeaponInfo *curWeapon = CWeaponInfo::GetWeaponInfo(GetWeapon()->m_eWeaponType);
		AddWeaponModel(curWeapon->m_nModelId);
	}
	if (m_nPedState == PED_DIE || m_nPedState == PED_DEAD) {
		animAssoc = m_pVehicleAnim;
		if (animAssoc) {
			animAssoc->blendDelta = -4.0;
			animAssoc->flags |= ASSOC_FADEOUTWHENDONE;
			animAssoc = m_pVehicleAnim;
			animAssoc->flags &= ~ASSOC_RUNNING;
		}
	} else
		SetIdle();

	m_pVehicleAnim = nil;
	
	if (veh) {
		if (veh->m_autoPilot.m_nCruiseSpeed == 0)
			veh->m_autoPilot.m_nCruiseSpeed = 17;
	}
}

void
CPed::ReactToAttack(CEntity *attacker)
{
	if (IsPlayer() && attacker->IsPed()) {
		InformMyGangOfAttack(attacker);
		SetLookFlag(attacker, 1);
		SetLookTimer(700);
		return;
	}
	
	if (IsPedInControl() && (CharCreatedBy != MISSION_CHAR || bRespondsToThreats)) {
		CPed *ourLeader = m_leader;
		if (ourLeader != attacker && (!ourLeader || FindPlayerPed() != ourLeader)
			&& attacker->IsPed()) {

			CPed *attackerPed = (CPed*)attacker; 
			if (bNotAllowedToDuck) {
				if (!attackerPed->GetWeapon()->IsTypeMelee()) {
					field_4E8 = CTimer::GetTimeInMilliseconds();
					return;
				}
			} else if (bCrouchWhenShooting || m_ped_flagE1) {
				SetDuck(CGeneral::GetRandomNumberInRange(1000,3000));
				return;
			}

			if (m_pedStats->m_fear <= 100 - attackerPed->m_pedStats->m_temper) {
				if (m_pedStats != attackerPed->m_pedStats) {
					if (IsGangMember() || m_nPedType == PEDTYPE_EMERGENCY || m_nPedType == PEDTYPE_FIREMAN) {
						RegisterThreatWithGangPeds(attackerPed);
					}
					if (!attackerPed->GetWeapon()->IsTypeMelee() && GetWeapon()->IsTypeMelee()) {
						SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, attacker);
						SetMoveState(PEDMOVE_RUN);
					} else {
						SetObjective(OBJECTIVE_KILL_CHAR_ON_FOOT, attacker);
						SetObjectiveTimer(20000);
					}
				}
			} else {
				SetObjective(OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE, attackerPed);
				SetMoveState(PEDMOVE_RUN);
				if (attackerPed->GetWeapon()->IsTypeMelee())
					Say(SOUND_PED_FLEE_RUN);
			}
		}
	}
}

bool
CPed::TurnBody(void)
{
	float lookDir;
	bool doneSmoothly = true;

	if (m_pLookTarget) {
		CVector &lookPos = m_pLookTarget->GetPosition();

		lookDir = CGeneral::GetRadianAngleBetweenPoints(
					lookPos.x,
					lookPos.y,
					GetPosition().x,
					GetPosition().y);
	} else
		lookDir = m_fLookDirection;

	float limitedLookDir = CGeneral::LimitRadianAngle(lookDir);
	float currentRot = m_fRotationCur;

	if (currentRot - PI > limitedLookDir)
		limitedLookDir += 2 * PI;
	else if (PI + currentRot < limitedLookDir)
		limitedLookDir -= 2 * PI;

	float neededTurn = currentRot - limitedLookDir;
	m_fRotationDest = limitedLookDir;

	if (Abs(neededTurn) > 0.05f) {
		doneSmoothly = false;
		currentRot -= neededTurn * 0.2f;
	}

	m_fRotationCur = currentRot;
	m_fLookDirection = limitedLookDir;
	return doneSmoothly;
}

void
CPed::Chat(void)
{
	if (bIsLooking && TurnBody())
		ClearLookFlag();

	if (!m_pLookTarget || !m_pLookTarget->IsPed()) {
		ClearChat();
		return;
	}

	CPed *partner = (CPed*) m_pLookTarget;

	if (partner->m_nPedState != PED_CHAT) {
		ClearChat();
		if (partner->m_pedInObjective) {
			if (partner->m_objective == OBJECTIVE_KILL_CHAR_ON_FOOT ||
				partner->m_objective == OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE)
				ReactToAttack(partner->m_pedInObjective);
		}
		return;
	}
	if (bIsTalking) {
		if (CGeneral::GetRandomNumber() < 512) {
			CAnimBlendAssociation *chatAssoc = RpAnimBlendClumpGetAssociation((RpClump*) m_rwObject, ANIM_IDLE_CHAT);
			if (chatAssoc) {
				chatAssoc->blendDelta = -4.0f;
				chatAssoc->flags |= ASSOC_FADEOUTWHENDONE;
			}
			bIsTalking = false;
		} else
			Say(SOUND_PED_CHAT);

	} else if (!RpAnimBlendClumpGetFirstAssociation((RpClump*)m_rwObject, ASSOC_FLAG100)) {

		if (CGeneral::GetRandomNumber() < 20) {
			CAnimManager::BlendAnimation((RpClump*) m_rwObject, ASSOCGRP_STD, ANIM_XPRESS_SCRATCH, 4.0f);
		}
		if (!bIsTalking) {
			CAnimBlendAssociation *chatAssoc = CAnimManager::BlendAnimation((RpClump*) m_rwObject, ASSOCGRP_STD, ANIM_IDLE_CHAT, 4.0f);
			float chatTime = CGeneral::GetRandomNumberInRange(0.0f, 3.0f);
			chatAssoc->SetCurrentTime(chatTime);

			bIsTalking = true;
			Say(SOUND_PED_CHAT);
		}
	}
	if (m_standardTimer && CTimer::GetTimeInMilliseconds() > m_standardTimer) {
		ClearChat();
		m_standardTimer = CTimer::GetTimeInMilliseconds() + 30000;
	}
}

void
CPed::CheckAroundForPossibleCollisions(void)
{
	CVector ourCentre, objCentre;
	CEntity *objects[8];
	int16 maxObject;

	if (CTimer::GetTimeInMilliseconds() <= m_nPedStateTimer)
		return;

	GetBoundCentre(ourCentre);

	CWorld::FindObjectsInRange(ourCentre, 10.0f, true, &maxObject, 6, objects, false, true, false, true, false);
	for (int i = 0; i < maxObject; i++) {
		CEntity *object = objects[i];
		if (field_31C) {
			if (gPhoneInfo.PhoneAtThisPosition(object->GetPosition()))
				break;
		}
		object->GetBoundCentre(objCentre);
		float radius = object->GetBoundRadius();
		if (radius > 4.5f || radius < 1.0f)
			radius = 1.0f;

		// According to code, developers gave up calculating Z diff. later.
		float diff = CVector(ourCentre - objCentre).MagnitudeSqr2D();

		if (sq(radius + 1.0f) > diff)
			m_fRotationDest += DEGTORAD(22.5f);
	}
}

WRAPPER void CPed::PedGetupCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4CE810); }
WRAPPER void CPed::PedStaggerCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4CE8D0); }
WRAPPER void CPed::PedEvadeCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4D36E0); }
WRAPPER void CPed::FinishDieAnimCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4D3950); }
WRAPPER void CPed::FinishedWaitCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4D6520); }
WRAPPER void CPed::FinishLaunchCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4D7490); }
WRAPPER void CPed::FinishHitHeadCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4D7A80); }
WRAPPER void CPed::PedAnimGetInCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4DEC80); }
WRAPPER void CPed::PedAnimDoorOpenCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4DE500); }
WRAPPER void CPed::PedAnimPullPedOutCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4DEAF0); }
WRAPPER void CPed::PedAnimDoorCloseCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4DF1B0); }
WRAPPER void CPed::SetInCarCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4CF220); }
WRAPPER void CPed::PedSetOutCarCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4CE8F0); }
WRAPPER void CPed::PedAnimAlignCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4DE130); }
WRAPPER void CPed::PedAnimStepOutCarCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4DF5C0); }
WRAPPER void CPed::PedSetInTrainCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4E3290); }
WRAPPER void CPed::PedSetOutTrainCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4E36E0); }
WRAPPER void CPed::FinishFightMoveCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4E9830); }
WRAPPER void CPed::PedAnimDoorCloseRollingCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4E4B90); }
WRAPPER void CPed::FinishJumpCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4D7A50); }
WRAPPER void CPed::PedLandCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4CE8A0); }
WRAPPER void FinishFuckUCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4C6580); }
WRAPPER void CPed::RestoreHeadingRateCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x4D6550); }

class CPed_ : public CPed
{
public:
	CPed* ctor(uint32 pedType) { return ::new (this) CPed(pedType); }
	void dtor(void) { CPed::~CPed(); }

	void SetModelIndex_(uint32 mi) { CPed::SetModelIndex(mi); }
	void FlagToDestroyWhenNextProcessed_(void) { CPed::FlagToDestroyWhenNextProcessed(); }
	bool SetupLighting_(void) { return CPed::SetupLighting(); }
	void RemoveLighting_(bool reset) { CPed::RemoveLighting(reset); }
	void Teleport_(CVector pos) { CPed::Teleport(pos); }
};

STARTPATCHES
	InjectHook(0x4C41C0, &CPed_::ctor, PATCH_JUMP);
	InjectHook(0x4C50D0, &CPed_::dtor, PATCH_JUMP);
	InjectHook(0x4C52A0, &CPed_::SetModelIndex_, PATCH_JUMP);
	InjectHook(0x4D6570, &CPed_::FlagToDestroyWhenNextProcessed_, PATCH_JUMP);
	InjectHook(0x4A7D30, &CPed_::SetupLighting_, PATCH_JUMP);
	InjectHook(0x4A7DC0, &CPed_::RemoveLighting_, PATCH_JUMP);
	InjectHook(0x4D3E70, &CPed_::Teleport_, PATCH_JUMP);

	InjectHook(0x4CF8F0, &CPed::AddWeaponModel, PATCH_JUMP);
	InjectHook(0x4C6AA0, &CPed::AimGun, PATCH_JUMP);
	InjectHook(0x4EB470, &CPed::ApplyHeadShot, PATCH_JUMP);
	InjectHook(0x4EAEE0, &CPed::RemoveBodyPart, PATCH_JUMP);
	InjectHook(0x4C6460, (void (CPed::*)(CEntity*, bool)) &CPed::SetLookFlag, PATCH_JUMP);
	InjectHook(0x4C63E0, (void (CPed::*)(float, bool)) &CPed::SetLookFlag, PATCH_JUMP);
	InjectHook(0x4D12E0, &CPed::SetLookTimer, PATCH_JUMP);
	InjectHook(0x4C5700, &CPed::OurPedCanSeeThisOne, PATCH_JUMP);
	InjectHook(0x4D2BB0, &CPed::Avoid, PATCH_JUMP);
	InjectHook(0x4C6A50, &CPed::ClearAimFlag, PATCH_JUMP);
	InjectHook(0x4C64F0, &CPed::ClearLookFlag, PATCH_JUMP);
	InjectHook(0x4EB670, &CPed::IsPedHeadAbovePos, PATCH_JUMP);
	InjectHook(0x4E68A0, &CPed::FinishedAttackCB, PATCH_JUMP);
	InjectHook(0x4E5BD0, &CheckForPedsOnGroundToAttack, PATCH_JUMP);
	InjectHook(0x4E6BA0, &CPed::Attack, PATCH_JUMP);
	InjectHook(0x4CF980, &CPed::RemoveWeaponModel, PATCH_JUMP);
	InjectHook(0x4CFA60, &CPed::SetCurrentWeapon, PATCH_JUMP);
	InjectHook(0x4E4A10, &CPed::Duck, PATCH_JUMP);
	InjectHook(0x4E4A30, &CPed::ClearDuck, PATCH_JUMP);
	InjectHook(0x4E6180, &CPed::ClearPointGunAt, PATCH_JUMP);
	InjectHook(0x4E07D0, &CPed::BeingDraggedFromCar, PATCH_JUMP);
	InjectHook(0x4CF000, &CPed::PedSetDraggedOutCarCB, PATCH_JUMP);
	InjectHook(0x4C5D80, &CPed::RestartNonPartialAnims, PATCH_JUMP);
	InjectHook(0x4E4730, &CPed::GetLocalPositionToOpenCarDoor, PATCH_JUMP);
	InjectHook(0x4E4660, (void (*)(CVector*, CVehicle*, uint32, float)) CPed::GetPositionToOpenCarDoor, PATCH_JUMP);
	InjectHook(0x4E1A30, (void (*)(CVector*, CVehicle*, uint32)) CPed::GetPositionToOpenCarDoor, PATCH_JUMP);
	InjectHook(0x4DF940, &CPed::LineUpPedWithCar, PATCH_JUMP);
	InjectHook(0x4CC6C0, &CPed::PlayFootSteps, PATCH_JUMP);
	InjectHook(0x4C5350, &CPed::BuildPedLists, PATCH_JUMP);
	InjectHook(0x4CF9B0, &CPed::GiveWeapon, PATCH_JUMP);
	InjectHook(0x4C7EA0, &CPed::CalculateNewOrientation, PATCH_JUMP);
	InjectHook(0x4C78F0, &CPed::WorkOutHeadingForMovingFirstPerson, PATCH_JUMP);
	InjectHook(0x4C73F0, &CPed::CalculateNewVelocity, PATCH_JUMP);
	InjectHook(0x4D72F0, &CPed::CanPedJumpThis, PATCH_JUMP);
	InjectHook(0x4DD820, &CPed::CanSeeEntity, PATCH_JUMP);
	InjectHook(0x4D9460, &CPed::RestorePreviousObjective, PATCH_JUMP);
	InjectHook(0x4D82C0, (void (CPed::*)(eObjective)) &CPed::SetObjective, PATCH_JUMP);
	InjectHook(0x4D83E0, (void (CPed::*)(eObjective, void*)) &CPed::SetObjective, PATCH_JUMP);
	InjectHook(0x4D89A0, (void (CPed::*)(eObjective, int16, int16)) &CPed::SetObjective, PATCH_JUMP);
	InjectHook(0x4DDEC0, &CPed::ReactToAttack, PATCH_JUMP);
	InjectHook(0x4D0600, &CPed::SetIdle, PATCH_JUMP);
	InjectHook(0x4E0E00, &CPed::QuitEnteringCar, PATCH_JUMP);
	InjectHook(0x4E4AD0, &CPed::InformMyGangOfAttack, PATCH_JUMP);
	InjectHook(0x4D3C80, &CPed::ClearChat, PATCH_JUMP);
	InjectHook(0x4D1390, &CPed::TurnBody, PATCH_JUMP);
	InjectHook(0x4D3AC0, &CPed::Chat, PATCH_JUMP);
	InjectHook(0x4D0490, &CPed::CheckAroundForPossibleCollisions, PATCH_JUMP);
ENDPATCHES
