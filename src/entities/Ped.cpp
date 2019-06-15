#include "common.h"
#include "patcher.h"
#include "Ped.h"
#include "Pools.h"
#include <render\Particle.h>
#include <render\ParticleMgr.h>
#include <Stats.h>

Bool &CPed::bNastyLimbsCheat = *(Bool*)0x95CD44;
Bool &CPed::bPedCheat2 = *(Bool*)0x95CD5A;
Bool &CPed::bPedCheat3 = *(Bool*)0x95CD59;

void *CPed::operator new(size_t sz) { return CPools::GetPedPool()->New();  }
void CPed::operator delete(void *p, size_t sz) { CPools::GetPedPool()->Delete((CPed*)p); }

WRAPPER void CPed::KillPedWithCar(CVehicle *veh, float impulse) { EAXJMP(0x4EC430); }
WRAPPER void CPed::Say(uint16 audio) { EAXJMP(0x4E5A10); }
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
	uint8 newFlag;

	if (m_pSeekTarget) {
		if (m_pSeekTarget->m_status == STATUS_PHYSICS) {
			m_pSeekTarget->m_pedIK.GetComponentPosition(&pos, 1);
			vector.x = pos.x;
			vector.y = pos.y;
			vector.z = pos.z;
		} else {
			vector = *(m_pSeekTarget->GetMatrix().GetPosition());
		}
		CPed::Say(0x74);

		m_ped_flagB2 = m_pedIK.PointGunAtPosition(&vector);
		if (m_pPedFight != m_pSeekTarget) {
			CPed::SetLookFlag(m_pSeekTarget, 1);
		}

	} else {
		if (CPed::IsPlayer()) {
			newFlag = m_pedIK.PointGunInDirection(m_fLookDirection, m_vecMoveSpeedAvg.y);
		} else {
			newFlag = m_pedIK.PointGunInDirection(m_fLookDirection, 0.0);
		}

		m_ped_flagB2 = newFlag;
	}
}


// After I finished this I realized it's only for SCM opcode...
void
CPed::ApplyHeadShot(eWeaponType weaponType, CVector pos, bool evenOnPlayer)
{
	CVector pos2 = CVector(
		pos.x,
		pos.y,
		pos.z + 0.1
	);

	if (!CPed::IsPlayer() || evenOnPlayer)
	{
		++CStats::HeadShots;

		// yes. decompiled by hand.
		if (m_nPedState != PED_PASSENGER || m_nPedState != PED_TAXI_PASSENGER) {
			CPed::SetDie(ANIM_KO_SHOT_FRONT1, 4.0, 0.0);
		}

		m_ped_flagC20 = 1;
		m_nPedStateTimer = CTimer::GetTimeInMilliseconds() + 150;

		CParticle::AddParticle(PARTICLE_TEST, pos2,
								CVector(
									0.0,
									0.0,
									0.0
								), NULL, 0.2f, 0, 0, 0, 0);

		if (CEntity::GetIsOnScreen())
		{
			for(int i=0; i<0x20; i++) {
				CParticle::AddParticle(PARTICLE_BLOOD_SMALL,
										pos2,
										CVector(
											0.0,
											0.0,
											0.03
										), NULL, 0.0f, 0, 0, 0, 0);
			}

			for (int i = 0; i < 0x10; i++) {
				CParticle::AddParticle(PARTICLE_DEBRIS2,
										pos2,
										CVector(
											0.0,
											0.0,
											0.0099999998
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
	if (frame)
	{
		if (CGame::nastyGame)
		{
			if (nodeId != PED_HEAD)
				CPed::SpawnFlyingComponent(nodeId, arg4);

			RecurseFrameChildrenVisibilityCB(frame, 0);
			zero.x = 0.0;
			zero.z = 0.0;
			zero.y = 0.0;
			for (fp = RwFrameGetParent(frame); fp; fp = RwFrameGetParent(frame))
				RwV3dTransformPoints(&zero, &zero, 1, &fp->modelling);

			if (CEntity::GetIsOnScreen())
			{
				CParticle::AddParticle(PARTICLE_TEST, zero,
					CVector(
						0.0,
						0.0,
						0.0
					), NULL, 0.2f, 0, 0, 0, 0);

				for (int i = 0; i < 0x10; i++) {
					CParticle::AddParticle(PARTICLE_BLOOD_SMALL,
						zero,
						CVector(
							0.0,
							0.0,
							0.03
						), NULL, 0.0f, 0, 0, 0, 0);
				}
			}
			m_ped_flagC20 = 1;
			m_bodyPartBleeding = nodeId;
		}
	}
	else
	{
		printf("Trying to remove ped component");
	}
}

RwObject*
CPed::SetPedAtomicVisibilityCB(RwObject *object, void *data)
{
	RwObject *result = object;
	if (!data)
		object->flags = 0;

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
	if (m_lookTimer < CTimer::GetTimeInMilliseconds())
	{
		m_ped_flagA10 = 1;
		m_ped_flagA40 = 0;
		m_pPedFight = to;
		m_pPedFight->RegisterReference((CEntity**)&m_pPedFight);
		m_fLookDirection = 999999;
		m_lookTimer = 0;
		m_ped_flagA20_look = set;
		if (m_nPedState != PED_DRIVING) {
			// Resets second right most bit
			m_pedIK.m_flags &= 0xFFFFFFFD;
		}
	}
}

void
CPed::SetLookFlag(float angle, bool set)
{
	if (m_lookTimer < CTimer::GetTimeInMilliseconds())
	{
		m_ped_flagA10 = 1;
		m_ped_flagA40 = 0;
		m_pPedFight = 0;
		m_fLookDirection = angle;
		m_lookTimer = 0;
		m_ped_flagA20_look = set;
		if (m_nPedState != PED_DRIVING) {
			// Resets second right most bit
			m_pedIK.m_flags &= 0xFFFFFFFD;
		}
	}
}


STARTPATCHES
	InjectHook(0x4CF8F0, &CPed::AddWeaponModel, PATCH_JUMP);
	InjectHook(0x4C6AA0, &CPed::AimGun, PATCH_JUMP);
	InjectHook(0x4EB470, &CPed::ApplyHeadShot, PATCH_JUMP);
	InjectHook(0x4EAEE0, &CPed::RemoveBodyPart, PATCH_JUMP);
	InjectHook(0x4C6460, (void (CPed::*)(CPed*, bool)) &CPed::SetLookFlag, PATCH_JUMP);
	InjectHook(0x4C63E0, (void (CPed::*)(float, bool)) &CPed::SetLookFlag, PATCH_JUMP);
ENDPATCHES