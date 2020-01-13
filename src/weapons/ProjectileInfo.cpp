#include "common.h"
#include "patcher.h"
#include "Camera.h"
#include "General.h"
#include "Heli.h"
#include "ModelIndices.h"
#include "Particle.h"
#include "Ped.h"
#include "Plane.h"
#include "ProjectileInfo.h"
#include "Projectile.h"
#include "Explosion.h"
#include "Weapon.h"
#include "World.h"

CProjectileInfo (&gaProjectileInfo)[NUM_PROJECTILES] = *(CProjectileInfo(*)[NUM_PROJECTILES])*(uintptr*)0x64ED50;
CProjectile* (&CProjectileInfo::ms_apProjectile)[NUM_PROJECTILES] = *(CProjectile*(*)[NUM_PROJECTILES])*(uintptr*)0x87C748;

void
CProjectileInfo::Initialise()
{
	debug("Initialising CProjectileInfo...\n");

	for (int i = 0; i < ARRAY_SIZE(ms_apProjectile); i++) {
		ms_apProjectile[i] = nil;
		gaProjectileInfo[i].m_eWeaponType = WEAPONTYPE_GRENADE;
		gaProjectileInfo[i].m_pSource = nil;
		gaProjectileInfo[i].m_nExplosionTime = 0;
		gaProjectileInfo[i].m_bInUse = false;
	}

	debug("CProjectileInfo ready\n");
}

void
CProjectileInfo::Shutdown()
{
	debug("Shutting down CProjectileInfo...\n");
	debug("CProjectileInfo shut down\n");
}

CProjectileInfo*
CProjectileInfo::GetProjectileInfo(int32 id)
{
	return &gaProjectileInfo[id];
}

bool
CProjectileInfo::AddProjectile(CEntity *entity, eWeaponType weapon, CVector pos, float speed)
{
	int8 SpecialCollisionResponseCase = COLLRESPONSE_NONE;
	bool gravity = true;
	CMatrix matrix;
	float elasticity = 0.75f;
	CPed* ped = (CPed*)entity;
	int time;
	CVector velocity;

	switch (weapon)
	{
	case WEAPONTYPE_ROCKETLAUNCHER:
	{
		float vy = 1.25f;
		time = CTimer::GetTimeInMilliseconds() + 1400;
		if (ped->IsPlayer()) {
			matrix.GetForward() = TheCamera.Cams[TheCamera.ActiveCam].Front;
			matrix.GetUp() = TheCamera.Cams[TheCamera.ActiveCam].Up;
			matrix.GetRight() = CrossProduct(TheCamera.Cams[TheCamera.ActiveCam].Up, TheCamera.Cams[TheCamera.ActiveCam].Front);
			matrix.GetPosition() = pos;
		} else if (ped->m_pSeekTarget != nil) {
				float ry = CGeneral::GetRadianAngleBetweenPoints(1.0f, ped->m_pSeekTarget->GetPosition().z, 1.0f, pos.z);
				float rz = Atan2(-ped->GetForward().x, ped->GetForward().y);
				vy = 0.35f * speed + 0.15f;
				matrix.SetTranslate(0.0f, 1.0f, 1.0f);
				matrix.Rotate(0.0f, ry, rz);
				matrix.GetPosition() += pos;
		} else {
			matrix = ped->GetMatrix();
		}
		velocity = Multiply3x3(matrix, CVector(0.0f, vy, 0.0f));
		gravity = false;
		break;
	}
	case WEAPONTYPE_FLAMETHROWER:
		Error("Undefined projectile type, AddProjectile, ProjectileInfo.cpp");
		break;
	case WEAPONTYPE_MOLOTOV:
	{
		time = CTimer::GetTimeInMilliseconds() + 2000;
		float scale = 0.22f * speed + 0.15f;
		if (scale < 0.2f)
			scale = 0.2f;
		float angle = Atan2(-ped->GetForward().x, ped->GetForward().y);
		matrix.SetTranslate(0.0f, 0.0f, 0.0f);
		matrix.RotateZ(angle);
		matrix.GetPosition() += pos;
		velocity.x = -1.0f * scale * Sin(angle);
		velocity.y = scale * Cos(angle);
		velocity.z = (0.2f * speed + 0.4f) * scale;
		break;
	}
	case WEAPONTYPE_GRENADE:
	{
		time = CTimer::GetTimeInMilliseconds() + 2000;
		float scale = 0.0f;
		if (speed != 0.0f)
			scale = 0.22f * speed + 0.15f;
		float angle = Atan2(-ped->GetForward().x, ped->GetForward().y);
		matrix.SetTranslate(0.0f, 0.0f, 0.0f);
		matrix.RotateZ(angle);
		matrix.GetPosition() += pos;
		SpecialCollisionResponseCase = COLLRESPONSE_UNKNOWN5;
		velocity.x = -1.0f * scale * Sin(angle);
		velocity.y = scale * Cos(angle);
		velocity.z = (0.4f * speed + 0.4f) * scale;
		elasticity = 0.5f;
		break;
	}
	}

	int i = 0;
	while (gaProjectileInfo[i].m_bInUse && i < ARRAY_SIZE(gaProjectileInfo)) i++;

	if (i == ARRAY_SIZE(gaProjectileInfo))
		return false;

	switch (weapon)
	{
	case WEAPONTYPE_ROCKETLAUNCHER:
		ms_apProjectile[i] = new CProjectile(MI_MISSILE);
		break;
	case WEAPONTYPE_FLAMETHROWER:
		break;
	case WEAPONTYPE_MOLOTOV:
		ms_apProjectile[i] = new CProjectile(MI_MOLOTOV);
		break;
	case WEAPONTYPE_GRENADE:
		ms_apProjectile[i] = new CProjectile(MI_GRENADE);
		break;
	}

	if (ms_apProjectile[i] == nil)
		return false;

	gaProjectileInfo[i].m_eWeaponType = weapon;
	gaProjectileInfo[i].m_pSource = ped;
	ms_apProjectile[i]->GetMatrix() = matrix;
	ms_apProjectile[i]->SetMoveSpeed(velocity);
	ms_apProjectile[i]->bAffectedByGravity = gravity;

	gaProjectileInfo[i].m_nExplosionTime = time;
	ms_apProjectile[i]->m_fElasticity = elasticity;
	ms_apProjectile[i]->m_nSpecialCollisionResponseCases = SpecialCollisionResponseCase;

	gaProjectileInfo[i].m_bInUse = true;
	CWorld::Add(ms_apProjectile[i]);

	gaProjectileInfo[i].m_vecPos = ms_apProjectile[i]->GetPosition();
	return true;
}

void
CProjectileInfo::RemoveProjectile(CProjectileInfo *info, CProjectile *projectile)
{
	RemoveNotAdd(info->m_pSource, info->m_eWeaponType, projectile->GetPosition());

	info->m_bInUse = false;
	CWorld::Remove(projectile);
	delete projectile;
}

void
CProjectileInfo::RemoveNotAdd(CEntity *entity, eWeaponType weaponType, CVector pos)
{
	switch (weaponType)
	{
	case WEAPONTYPE_GRENADE:
		CExplosion::AddExplosion(nil, entity, EXPLOSION_GRENADE, pos, 0);
		break;
	case WEAPONTYPE_MOLOTOV:
		CExplosion::AddExplosion(nil, entity, EXPLOSION_MOLOTOV, pos, 0);
		break;
	case WEAPONTYPE_ROCKETLAUNCHER:
		CExplosion::AddExplosion(nil, entity, EXPLOSION_ROCKET, pos, 0);
		break;
	}
}

void
CProjectileInfo::Update()
{
	for (int i = 0; i < ARRAY_SIZE(gaProjectileInfo); i++) {
		if (!gaProjectileInfo[i].m_bInUse) continue;

		CPed *ped = (CPed*)gaProjectileInfo[i].m_pSource;
		if (ped != nil && ped->m_type == ENTITY_TYPE_PED && !ped->IsPointerValid())
			gaProjectileInfo[i].m_pSource = nil;

		if (ms_apProjectile[i] == nil) {
			gaProjectileInfo[i].m_bInUse = false;
			continue;
		}

		if (gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_ROCKETLAUNCHER) {
			CParticle::AddParticle(PARTICLE_SMOKE, ms_apProjectile[i]->GetPosition(), CVector(0.0f, 0.0f, 0.0f));
		}

		if (CTimer::GetTimeInMilliseconds() <= gaProjectileInfo[i].m_nExplosionTime) {
			if (gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_ROCKETLAUNCHER) {
				CVector pos = ms_apProjectile[i]->GetPosition();
				CWorld::pIgnoreEntity = ms_apProjectile[i];
				if (ms_apProjectile[i]->bHasCollided
					|| !CWorld::GetIsLineOfSightClear(gaProjectileInfo[i].m_vecPos, pos, true, true, true, true, false, false)
					|| gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_ROCKETLAUNCHER && (CHeli::TestRocketCollision(&pos) || CPlane::TestRocketCollision(&pos))) {
					RemoveProjectile(&gaProjectileInfo[i], ms_apProjectile[i]);
				}
				CWorld::pIgnoreEntity = nil;
			} else if (gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_MOLOTOV) {
				CVector pos = ms_apProjectile[i]->GetPosition();
				CWorld::pIgnoreEntity = ms_apProjectile[i];

				if (gaProjectileInfo[i].m_pSource == nil 
					|| ((gaProjectileInfo[i].m_vecPos - gaProjectileInfo[i].m_pSource->GetPosition()).MagnitudeSqr() >= 2.0f))
				{
					if (ms_apProjectile[i]->bHasCollided
						|| !CWorld::GetIsLineOfSightClear(gaProjectileInfo[i].m_vecPos, pos, true, true, true, true, false, false)
						|| gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_ROCKETLAUNCHER && (CHeli::TestRocketCollision(&pos) || CPlane::TestRocketCollision(&pos))) {
						RemoveProjectile(&gaProjectileInfo[i], ms_apProjectile[i]);
					}
				}
				CWorld::pIgnoreEntity = nil;
			}
		} else {
			RemoveProjectile(&gaProjectileInfo[i], ms_apProjectile[i]);
		}

		gaProjectileInfo[i].m_vecPos = ms_apProjectile[i]->GetPosition();
	}
}

bool
CProjectileInfo::IsProjectileInRange(float x1, float x2, float y1, float y2, float z1, float z2, bool remove)
{
	bool result = false;
	for (int i = 0; i < ARRAY_SIZE(ms_apProjectile); i++) {
		if (gaProjectileInfo[i].m_bInUse) {
			if (gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_ROCKETLAUNCHER || gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_MOLOTOV || gaProjectileInfo[i].m_eWeaponType == WEAPONTYPE_GRENADE) {
				CVector &pos = ms_apProjectile[i]->GetPosition();
				if (pos.x >= x1 && pos.x <= x2 && pos.y >= y1 && pos.y <= y2 && pos.z >= z1 && pos.z <= z2) {
					result = true;
					if (remove) {
						gaProjectileInfo[i].m_bInUse = false;
						CWorld::Remove(ms_apProjectile[i]);
						delete ms_apProjectile[i];
					}
				}
			}
		}
	}
	return result;
}

void
CProjectileInfo::RemoveAllProjectiles()
{
	for (int i = 0; i < ARRAY_SIZE(ms_apProjectile); i++) {
		if (gaProjectileInfo[i].m_bInUse) {
			gaProjectileInfo[i].m_bInUse = false;
			CWorld::Remove(ms_apProjectile[i]);
			delete ms_apProjectile[i];
		}
	}
}

bool
CProjectileInfo::RemoveIfThisIsAProjectile(CObject *object)
{
	int i = 0;
	while (ms_apProjectile[i++] != object) {
		if (i >= ARRAY_SIZE(ms_apProjectile))
			return false;
	}

	gaProjectileInfo[i].m_bInUse = false;
	CWorld::Remove(ms_apProjectile[i]);
	delete ms_apProjectile[i];
	ms_apProjectile[i] = nil;
	return true;
}

STARTPATCHES
	InjectHook(0x55ADF0, CProjectileInfo::Initialise, PATCH_JUMP);
	InjectHook(0x55AFF0, CProjectileInfo::Shutdown, PATCH_JUMP);
	InjectHook(0x55B010, CProjectileInfo::GetProjectileInfo, PATCH_JUMP);
	InjectHook(0x55B030, CProjectileInfo::AddProjectile, PATCH_JUMP);
	InjectHook(0x55B700, CProjectileInfo::RemoveProjectile, PATCH_JUMP);
	InjectHook(0x55B770, CProjectileInfo::RemoveNotAdd, PATCH_JUMP);
	InjectHook(0x55B7C0, CProjectileInfo::Update, PATCH_JUMP);
	InjectHook(0x55BA50, CProjectileInfo::IsProjectileInRange, PATCH_JUMP);
	InjectHook(0x55BB80, CProjectileInfo::RemoveAllProjectiles, PATCH_JUMP);
	InjectHook(0x55BBD0, CProjectileInfo::RemoveIfThisIsAProjectile, PATCH_JUMP);
ENDPATCHES
