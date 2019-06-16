#include "common.h"
#include "patcher.h"
#include "Ped.h"
#include "Pools.h"
#include "Particle.h"
#include "Stats.h"
#include "World.h"

Bool &CPed::bNastyLimbsCheat = *(Bool*)0x95CD44;
Bool &CPed::bPedCheat2 = *(Bool*)0x95CD5A;
Bool &CPed::bPedCheat3 = *(Bool*)0x95CD59;

void *CPed::operator new(size_t sz) { return CPools::GetPedPool()->New();  }
void CPed::operator delete(void *p, size_t sz) { CPools::GetPedPool()->Delete((CPed*)p); }

WRAPPER void CPed::KillPedWithCar(CVehicle *veh, float impulse) { EAXJMP(0x4EC430); }
WRAPPER void CPed::Say(eSound audio) { EAXJMP(0x4E5A10); }
WRAPPER void CPed::SetDie(AnimationId anim, float arg1, float arg2) { EAXJMP(0x4D37D0); }
WRAPPER void CPed::SpawnFlyingComponent(int, signed char) { EAXJMP(0x4EB060); }

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

bool
CPed::UseGroundColModel(void)
{
	return m_nPedState == PED_FALL ||
		m_nPedState == PED_DIVE_AWAY ||
		m_nPedState == PED_DIE ||
		m_nPedState == PED_DEAD;
}

void
CPed::AddWeaponModel(int id)
{
	RpAtomic* atm;

	if (id != -1) {
		atm = (RpAtomic*)CModelInfo::GetModelInfo(id)->CreateInstance();
		RwFrameDestroy(RpAtomicGetFrame(atm));
		RpAtomicSetFrame(atm, GetNodeFrame(PED_HANDR));
		RpClumpAddAtomic((RpClump*)m_rwObject, atm);
		m_wepModelID = id;
	}
}

void
CPed::AimGun()
{
	RwV3d pos;
	CVector vector;

	if (m_pSeekTarget) {
		if (m_pSeekTarget->m_status == STATUS_PHYSICS) {
			m_pSeekTarget->m_pedIK.GetComponentPosition(&pos, 1);
			vector.x = pos.x;
			vector.y = pos.y;
			vector.z = pos.z;
		} else {
			vector = *(m_pSeekTarget->GetPosition());
		}
		CPed::Say(SOUND_PED_ATTACK);

		m_ped_flagB2 = m_pedIK.PointGunAtPosition(&vector);
		if (m_pPedFight != m_pSeekTarget) {
			CPed::SetLookFlag(m_pSeekTarget, 1);
		}

	} else {
		if (CPed::IsPlayer()) {
			m_ped_flagB2 = m_pedIK.PointGunInDirection(m_fLookDirection, ((CPlayerPed*)this)->m_fFPSMoveHeading);
		} else {
			m_ped_flagB2 = m_pedIK.PointGunInDirection(m_fLookDirection, 0.0f);
		}
	}
}


// After I finished this I realized it's only for SCM opcode...
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

		m_ped_flagC20 = 1;
		m_nPedStateTimer = CTimer::GetTimeInMilliseconds() + 150;

		CParticle::AddParticle(PARTICLE_TEST, pos2,
								CVector(
									0.0f,
									0.0f,
									0.0f
								), NULL, 0.2f, 0, 0, 0, 0);

		if (CEntity::GetIsOnScreen()) {
			for(int i=0; i < 32; i++) {
				CParticle::AddParticle(PARTICLE_BLOOD_SMALL,
										pos2,
										CVector(
											0.0f,
											0.0f,
											0.03f
										), NULL, 0.0f, 0, 0, 0, 0);
			}

			for (int i = 0; i < 16; i++) {
				CParticle::AddParticle(PARTICLE_DEBRIS2,
										pos2,
										CVector(
											0.0f,
											0.0f,
											0.01f
										), NULL, 0.0f, 0, 0, 0, 0);
			}
		}
	}
}

void
CPed::RemoveBodyPart(PedNode nodeId, char arg4)
{
	RwFrame *frame;
	RwFrame *fp;
	RwV3d zero;

	frame = GetNodeFrame(nodeId);
	if (frame) {
		if (CGame::nastyGame) {
			if (nodeId != PED_HEAD)
				CPed::SpawnFlyingComponent(nodeId, arg4);

			RecurseFrameChildrenVisibilityCB(frame, 0);
			zero.x = 0.0f;
			zero.z = 0.0f;
			zero.y = 0.0f;
			for (fp = RwFrameGetParent(frame); fp; fp = RwFrameGetParent(frame))
				RwV3dTransformPoints(&zero, &zero, 1, &fp->modelling);

			if (CEntity::GetIsOnScreen()) {
				CParticle::AddParticle(PARTICLE_TEST, zero,
					CVector(
						0.0f,
						0.0f,
						0.0f
					), NULL, 0.2f, 0, 0, 0, 0);

				for (int i = 0; i < 16; i++) {
					CParticle::AddParticle(PARTICLE_BLOOD_SMALL,
						zero,
						CVector(
							0.0f,
							0.0f,
							0.03f
						), NULL, 0.0f, 0, 0, 0, 0);
				}
			}
			m_ped_flagC20 = 1;
			m_bodyPartBleeding = nodeId;
		}
	} else {
		printf("Trying to remove ped component");
	}
}

RwObject*
CPed::SetPedAtomicVisibilityCB(RwObject *object, void *data)
{
	RwObject *result = object;
	if (!data)
		RpAtomicSetFlags(object, 0);

	return result;
}

RwFrame*
CPed::RecurseFrameChildrenVisibilityCB(RwFrame *frame, void *data)
{
	RwFrameForAllObjects(frame, SetPedAtomicVisibilityCB, data);
	RwFrameForAllChildren(frame, RecurseFrameChildrenVisibilityCB, 0);
	return frame;
}

void
CPed::SetLookFlag(CPed *to, bool set)
{
	if (m_lookTimer < CTimer::GetTimeInMilliseconds()) {
		m_ped_flagA10 = 1;
		m_ped_flagA40 = 0;
		m_pPedFight = to;
		m_pPedFight->RegisterReference((CEntity**)&m_pPedFight);
		m_fLookDirection = 999999.0f;
		m_lookTimer = 0;
		m_ped_flagA20_look = set;
		if (m_nPedState != PED_DRIVING) {
			m_pedIK.m_flags &= ~(1 << 2);
		}
	}
}

void
CPed::SetLookFlag(float angle, bool set)
{
	if (m_lookTimer < CTimer::GetTimeInMilliseconds()) {
		m_ped_flagA10 = 1;
		m_ped_flagA40 = 0;
		m_pPedFight = 0;
		m_fLookDirection = angle;
		m_lookTimer = 0;
		m_ped_flagA20_look = set;
		if (m_nPedState != PED_DRIVING) {
			m_pedIK.m_flags &= ~(1 << 2);
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
CPed::OurPedCanSeeThisOne(CEntity* who)
{
	float xDiff;
	float yDiff;
	float distance;
	CColPoint colpoint;
	CEntity* ent;
	CVector ourPos;
	CVector itsPos;

	ourPos = this->GetPosition();
	itsPos = who->GetPosition();

	xDiff = itsPos.x - ourPos.x;
	yDiff = itsPos.y - ourPos.y;

	if ((yDiff * this->GetUp().y) + (xDiff * this->GetUp().x) < 0.0f)
		return 0;

	distance = sqrt(yDiff * yDiff + xDiff * xDiff);

	if (distance < 40.0f)
		return 0;

	ourPos.z += 1.0f;
	return CWorld::ProcessLineOfSight(ourPos, itsPos, colpoint, ent, 1, 0, 0, 0, 0, 0, 0) == 0;
}

STARTPATCHES
	InjectHook(0x4CF8F0, &CPed::AddWeaponModel, PATCH_JUMP);
	InjectHook(0x4C6AA0, &CPed::AimGun, PATCH_JUMP);
	InjectHook(0x4EB470, &CPed::ApplyHeadShot, PATCH_JUMP);
	InjectHook(0x4EAEE0, &CPed::RemoveBodyPart, PATCH_JUMP);
	InjectHook(0x4C6460, (void (CPed::*)(CPed*, bool)) &CPed::SetLookFlag, PATCH_JUMP);
	InjectHook(0x4C63E0, (void (CPed::*)(float, bool)) &CPed::SetLookFlag, PATCH_JUMP);
	InjectHook(0x4D12E0, &CPed::SetLookTimer, PATCH_JUMP);
	InjectHook(0x4C5700, &CPed::OurPedCanSeeThisOne, PATCH_JUMP);
ENDPATCHES
