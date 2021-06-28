#include "common.h"

#include "main.h"
#include "Lights.h"
#include "Pools.h"
#include "Radar.h"
#include "Object.h"
#include "DummyObject.h"
#include "Particle.h"
#include "General.h"
#include "ObjectData.h"
#include "World.h"
#include "Floater.h"
#include "soundlist.h"
#include "WaterLevel.h"
#include "Timecycle.h"
#include "Stats.h"
#include "SpecialFX.h"

#define BEACHBALL_MAX_SCORE 250
// the proportion of the ball speed compared to the player speed when it hits the player
#define BEACHBALL_SPEED_PROPORTION 0.4f

int16 CObject::nNoTempObjects;
//int16 CObject::nBodyCastHealth = 1000;
float CObject::fDistToNearestTree;

// Object pools tends to be full sometimes, let's free a temp. object in this case.
#ifdef FIX_BUGS
void *CObject::operator new(size_t sz) throw() {
	CObject *obj = CPools::GetObjectPool()->New();
	if (!obj) {
		CObjectPool *objectPool = CPools::GetObjectPool();
		for (int32 i = 0; i < objectPool->GetSize(); i++) {
			CObject *existing = objectPool->GetSlot(i);
			if (existing && existing->ObjectCreatedBy == TEMP_OBJECT) {
				int32 handle = objectPool->GetIndex(existing);
				CWorld::Remove(existing);
				delete existing;
				obj = objectPool->New(handle);
				break;
			}
		}
	}
	return obj;
}
#else
void *CObject::operator new(size_t sz) throw() { return CPools::GetObjectPool()->New(); }
#endif
void *CObject::operator new(size_t sz, int handle) throw() { return CPools::GetObjectPool()->New(handle); };

void CObject::operator delete(void *p, size_t sz) throw() { CPools::GetObjectPool()->Delete((CObject*)p); }
void CObject::operator delete(void *p, int handle) throw() { CPools::GetObjectPool()->Delete((CObject*)p); }

CObject::CObject(void)
{
	m_type = ENTITY_TYPE_OBJECT;
	m_fUprootLimit = 0.0f;
	m_nCollisionDamageEffect = 0;
	m_nSpecialCollisionResponseCases = COLLRESPONSE_NONE;
	m_bCameraToAvoidThisObject = false;
	ObjectCreatedBy = UNKNOWN_OBJECT;
	m_nEndOfLifeTime = 0;
	//	m_nRefModelIndex = -1;	// duplicate
	//	bUseVehicleColours = false;	// duplicate
	m_colour2 = 0;
	m_colour1 = m_colour2;
	m_nBonusValue = 0;
	m_nCostValue = 0;
	bIsPickup = false;
	bPickupObjWithMessage = false;
	bOutOfStock = false;
	bGlassCracked = false;
	bGlassBroken = false;
	bHasBeenDamaged = false;
	m_nRefModelIndex = -1;
	bUseVehicleColours = false;
	//	bIsStreetLight = false;		// duplicate
	m_pCurSurface = nil;
	m_pCollidingEntity = nil;
	m_nBeachballBounces = 0;
	bIsStreetLight = false;
	m_area = AREA_EVERYWHERE;
}

CObject::CObject(int32 mi, bool createRW)
{
	if (createRW)
		SetModelIndex(mi);
	else
		SetModelIndexNoCreate(mi);
	Init();
}

CObject::CObject(CDummyObject *dummy)
{
	SetModelIndexNoCreate(dummy->GetModelIndex());

	if (dummy->m_rwObject)
		AttachToRwObject(dummy->m_rwObject);
	else
		SetMatrix(dummy->GetMatrix());

	m_objectMatrix = dummy->GetMatrix();
	dummy->DetachFromRwObject();
	Init();
	m_level = dummy->m_level;
	m_area = dummy->m_area;
}

CObject::~CObject(void)
{
	CRadar::ClearBlipForEntity(BLIP_OBJECT, CPools::GetObjectPool()->GetIndex(this));

	if (m_nRefModelIndex != -1)
		CModelInfo::GetModelInfo(m_nRefModelIndex)->RemoveRef();

	if (ObjectCreatedBy == TEMP_OBJECT && nNoTempObjects != 0)
		nNoTempObjects--;
}

void
CObject::ProcessControl(void)
{
	CVector point, impulse;
	if (m_nCollisionDamageEffect)
		ObjectDamage(m_fDamageImpulse);
	CPhysical::ProcessControl();
	if (mod_Buoyancy.ProcessBuoyancy(this, m_fBuoyancy, &point, &impulse)) {
		bIsInWater = true;
		SetIsStatic(false);
		ApplyMoveForce(impulse);
		ApplyTurnForce(impulse, point);
		float fTimeStep = Pow(0.97f, CTimer::GetTimeStep());
		m_vecMoveSpeed *= fTimeStep;
		m_vecTurnSpeed *= fTimeStep;
	}
	int16 mi = GetModelIndex();
	if ((mi == MI_EXPLODINGBARREL || mi == MI_PETROLPUMP || mi == MI_PETROLPUMP2) && bHasBeenDamaged && bIsVisible
		&& (CGeneral::GetRandomNumber() & 0x1F) == 10) {
		bExplosionProof = true;
		bIsVisible = false;
		bUsesCollision = false;
		bAffectedByGravity = false;
		m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	}
	if (mi == MI_RCBOMB) {
		float fTurnForce = -(m_fTurnMass / 20.0f);
		CPhysical::ApplyTurnForce(m_vecMoveSpeed * fTurnForce, -GetForward());
		float fScalar = 1.0f - m_vecMoveSpeed.MagnitudeSqr() / 5.0f;
		float fScalarTimed = Pow(fScalar, CTimer::GetTimeStep());
		m_vecMoveSpeed *= fScalarTimed;
	}
	if (mi == MI_BEACHBALL) {
		float fTimeStep = Pow(0.95f, CTimer::GetTimeStep());
		float fPreviousVecSpeedMag = m_vecMoveSpeed.Magnitude2D();
		m_vecMoveSpeed.x *= fTimeStep;
		m_vecMoveSpeed.y *= fTimeStep;
		m_vecMoveSpeed.z += fPreviousVecSpeedMag - m_vecMoveSpeed.Magnitude2D();
		if (!FindPlayerVehicle()) {
			CVector distance;
			distance.x = FindPlayerCoors().x - GetPosition().x;
			distance.y = FindPlayerCoors().y - GetPosition().y;
			distance.z = FindPlayerCoors().z - GetPosition().z;
			if (distance.z > 0.0 && distance.z < 1.5f && distance.Magnitude2D() < 1.0f) {
				CVector playerSpeed = FindPlayerSpeed();
				if (fPreviousVecSpeedMag < 0.05f && playerSpeed.Magnitude() > 0.1f) {
					playerSpeed.z = 0.0f;
					playerSpeed.Normalise();
					playerSpeed.z = 0.3f;
					m_vecMoveSpeed = CVector(
						playerSpeed.x * BEACHBALL_SPEED_PROPORTION,
						playerSpeed.y * BEACHBALL_SPEED_PROPORTION,
						0.3f          * BEACHBALL_SPEED_PROPORTION
					);
					PlayOneShotScriptObject(SCRIPT_SOUND_HIT_BALL, GetPosition());
					m_vecTurnSpeed += CVector(
						((CGeneral::GetRandomNumber() % 16) - 7) / 10.0f,
						((CGeneral::GetRandomNumber() % 16) - 7) / 10.0f,
						0.0f);
					if (m_nBeachballBounces > 0) {
						m_nBeachballBounces++;
					}
					if (m_nBeachballBounces > 0) {
						sprintf(gString, "%d", m_nBeachballBounces);
						CMoneyMessages::RegisterOne(GetPosition(), gString, 255, 50, 0, 0.6f, 0.5f);
						CStats::RegisterHighestScore(3, m_nBeachballBounces);
					}
				}
			}
			if (distance.z > -1.05 && distance.z < -0.6 && m_vecMoveSpeed.z < 0.0f && distance.Magnitude2D() < 0.9f) {
				m_vecMoveSpeed.x += (CGeneral::GetRandomNumber() % 8 - 3) / 100.0f;
				m_vecMoveSpeed.y += (CGeneral::GetRandomNumber() % 8 - 3) / 100.0f;
				m_vecMoveSpeed.z = Max(m_vecMoveSpeed.z + 0.3f, 0.2f);
				PlayOneShotScriptObject(SCRIPT_SOUND_HIT_BALL, GetPosition());
				m_vecTurnSpeed.x += (CGeneral::GetRandomNumber() % 16 - 7) / 10.0f;
				m_vecTurnSpeed.y += (CGeneral::GetRandomNumber() % 16 - 7) / 10.0f;
				m_nBeachballBounces++;
				m_nBeachballBounces = Min(m_nBeachballBounces, BEACHBALL_MAX_SCORE);
				sprintf(gString, "%d", m_nBeachballBounces);
				CMoneyMessages::RegisterOne(GetPosition(), gString, 255, 50, 0, 0.6f, 0.5f);
				CStats::RegisterHighestScore(3, m_nBeachballBounces);
			}
		}
	}
	if (bIsBIGBuilding) {
		bIsInSafePosition = true;
	}
}

void
CObject::Teleport(CVector vecPos)
{
	CWorld::Remove(this);
	GetMatrix().GetPosition() = vecPos;
	GetMatrix().UpdateRW();
	UpdateRwFrame();
	CWorld::Add(this);
}

void
CObject::Render(void)
{
	if (bDoNotRender)
		return;

	if (m_nRefModelIndex != -1 && ObjectCreatedBy == TEMP_OBJECT && bUseVehicleColours) {
		CVehicleModelInfo *mi = (CVehicleModelInfo*)CModelInfo::GetModelInfo(m_nRefModelIndex);
		assert(mi->GetModelType() == MITYPE_VEHICLE);
		mi->SetVehicleColour(m_colour1, m_colour2);
	}

	float red = (0.8f * CTimeCycle::GetDirectionalRed() + CTimeCycle::GetAmbientRed_Obj()) * 165.75f;
	float green = (0.8f * CTimeCycle::GetDirectionalGreen() + CTimeCycle::GetAmbientGreen_Obj()) * 165.75f;
	float blue = (0.8f * CTimeCycle::GetDirectionalBlue() + CTimeCycle::GetAmbientBlue_Obj()) * 165.75f;

	red = Clamp(red, 0.0f, 255.0f);
	green = Clamp(green, 0.0f, 255.0f);
	blue = Clamp(blue, 0.0f, 255.0f);

	int alpha = CGeneral::GetRandomNumberInRange(196, 225);

	RwRGBA color = { (uint8)red, (uint8)green, (uint8)blue, (uint8)alpha };

	if (this->GetModelIndex() == MI_YT_MAIN_BODY) {
		float moveSpeedMagnitude = this->GetMoveSpeed().Magnitude();
		if (moveSpeedMagnitude > 0.0f) {
			float scaleMax = GetColModel()->boundingBox.max.y * 0.85f;

			CVector dir = this->GetMoveSpeed() + 0.3f * this->GetRight() - 0.5f * this->GetForward();
			dir.z += 0.05f * moveSpeedMagnitude;

			CVector pos = scaleMax * this->GetForward() + 2.25f * this->GetRight() + this->GetPosition();

			float fWaterLevel;
			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &fWaterLevel, true);
			pos.z = fWaterLevel + 0.75f;

			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, pos, dir, nil, 1.2f * moveSpeedMagnitude, color,
				CGeneral::GetRandomNumberInRange(0.0f, 0.4f), CGeneral::GetRandomNumberInRange(0.0f, 45.0f), 0, 0);

			float scaleMin = GetColModel()->boundingBox.min.y;

			dir = this->GetMoveSpeed() - 0.5f * this->GetForward();
			dir.z += 0.05f * moveSpeedMagnitude;

			pos = scaleMin * this->GetForward() + 4.5f * this->GetRight() + this->GetPosition();

			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &fWaterLevel, true);
			pos.z = fWaterLevel + 0.55f;

			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, pos, dir, nil, 0.9f, color,
				CGeneral::GetRandomNumberInRange(0.0f, 0.4f), CGeneral::GetRandomNumberInRange(0.0f, 45.0f), 0, 0);

			pos = scaleMin * 1.1f * this->GetForward() + 2.25f * this->GetRight() + this->GetPosition();

			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &fWaterLevel, true);
			pos.z = fWaterLevel + 0.55f;

			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, pos, dir, nil, 0.9f, color,
				CGeneral::GetRandomNumberInRange(0.0f, 0.4f), CGeneral::GetRandomNumberInRange(0.0f, 45.0f), 0, 0);

			pos = scaleMin * 1.1f * this->GetForward() - 0.05f * this->GetRight() + this->GetPosition();

			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &fWaterLevel, true);
			pos.z = fWaterLevel + 0.55f;

			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, pos, dir, nil, 0.9f, color,
				CGeneral::GetRandomNumberInRange(0.0f, 0.4f), CGeneral::GetRandomNumberInRange(0.0f, 45.0f), 0, 0);
		}
	}

	if (this->GetModelIndex() == MI_YT_MAIN_BODY2) {
		float moveSpeedMagnitude = this->GetMoveSpeed().Magnitude();
		if (moveSpeedMagnitude > 0.0f) {
			float scaleMax = GetColModel()->boundingBox.max.y * 0.85f;

			CVector dir = this->GetMoveSpeed() - 0.3f * this->GetRight() - 0.5f * this->GetForward();
			dir.z += 0.05f * moveSpeedMagnitude;

			CVector pos = scaleMax * this->GetForward() - 2.25f * this->GetRight() + this->GetPosition();

			float fWaterLevel;
			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &fWaterLevel, true);
			pos.z = fWaterLevel + 0.75f;

			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, pos, dir, nil, 1.2f * moveSpeedMagnitude, color,
				CGeneral::GetRandomNumberInRange(0.0f, 0.4f), CGeneral::GetRandomNumberInRange(0.0f, 45.0f), 0, 0);

			float scaleMin = GetColModel()->boundingBox.min.y;

			dir = this->GetMoveSpeed() - 0.5f * this->GetForward();
			dir.z += 0.05f * moveSpeedMagnitude;

			pos = scaleMin * this->GetForward() - 4.5f * this->GetRight() + this->GetPosition();

			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &fWaterLevel, true);
			pos.z = fWaterLevel + 0.55f;

			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, pos, dir, nil, 0.9f, color,
				CGeneral::GetRandomNumberInRange(0.0f, 0.4f), CGeneral::GetRandomNumberInRange(0.0f, 45.0f), 0, 0);

			pos = scaleMin * 1.1f * this->GetForward() - 2.25f * this->GetRight() + this->GetPosition();

			CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &fWaterLevel, true);
			pos.z = fWaterLevel + 0.55f;

			CParticle::AddParticle(PARTICLE_BOAT_SPLASH, pos, dir, nil, 0.9f, color,
				CGeneral::GetRandomNumberInRange(0.0f, 0.4f), CGeneral::GetRandomNumberInRange(0.0f, 45.0f), 0, 0);
		}
	}

	CEntity::Render();
}

bool
CObject::SetupLighting(void)
{
	if (bRenderScorched) {
		WorldReplaceNormalLightsWithScorched(Scene.world, 0.1f);
		return true;
	} else if (bIsPickup) {
		SetFullAmbient();
		return true;
	} else if (bIsWeapon) {
		ActivateDirectional();
		SetAmbientColoursForPedsCarsAndObjects();
		return true;
	}
	return false;
}

void
CObject::RemoveLighting(bool reset)
{
	if (reset) {
		SetAmbientColours();
		DeActivateDirectional();
	}
}

void
CObject::ObjectDamage(float amount)
{
	if (!m_nCollisionDamageEffect || !bUsesCollision)
		return;
	static int8 nFrameGen = 0;
	bool bBodyCastDamageEffect = false;
#if 0
	if (GetModelIndex() == MI_BODYCAST) {
		if (amount > 50.0f)
			nBodyCastHealth = (int16)(nBodyCastHealth - 0.5f * amount);
		if (nBodyCastHealth < 0)
			nBodyCastHealth = 0;
		if (nBodyCastHealth < 200)
			bBodyCastDamageEffect = true;
		amount = 0.0f;
	}
#endif
	if ((amount * m_fCollisionDamageMultiplier > 150.0f || bBodyCastDamageEffect) && m_nCollisionDamageEffect) {
		const CVector& vecPos = GetMatrix().GetPosition();
		const float fDirectionZ = 0.0002f * amount;
		switch (m_nCollisionDamageEffect) {
			case DAMAGE_EFFECT_CHANGE_MODEL:
				bRenderDamaged = true;
				return;
			case DAMAGE_EFFECT_SPLIT_MODEL:
				return;
			case DAMAGE_EFFECT_SMASH_AND_DAMAGE_TRAFFICLIGHTS:
			{
				static RwRGBA debrisColor = { 0xc8,0xc8,0xc8,0xff };
				if (bRenderDamaged) {
					break;
				}
				bRenderDamaged = true;
				CVector min = 0.85f * GetColModel()->boundingBox.min;
				CVector max = 0.85f * GetColModel()->boundingBox.max;
				min.z = max.z;
				min = GetMatrix() * min;
				max = GetMatrix() * max;
				CVector temp = (max - min) * 0.02f;
				for (int32 i = 0; i < 50; i++) {
					CVector vecDir = CVector(
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(0.10f, 0.25f)
					);
					++nFrameGen;
					int32 currentFrame = nFrameGen & 3;
					CVector pos = min + temp * (float)i;
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					float fColorFactor = CGeneral::GetRandomNumberInRange(0.6f, 1.2f);
					RwRGBA color = debrisColor;
					color.red *= fColorFactor;
					color.green *= fColorFactor;
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-0.40f, 0.40f);
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, pos, vecDir, nil, fSize, color, nRotationSpeed, 0, currentFrame, 0);
				}
				PlayOneShotScriptObject(SCRIPT_SOUND_METAL_COLLISION, min);
				break;
			}
			case DAMAGE_EFFECT_CHANGE_THEN_SMASH: {
				if (!bRenderDamaged) {
					bRenderDamaged = true;
					return;
				}
				// fall through
			}
			case DAMAGE_EFFECT_SMASH_COMPLETELY: {
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				break;
			}
			case DAMAGE_EFFECT_SMASH_CARDBOARD_COMPLETELY:
			case DAMAGE_EFFECT_SMASH_YELLOW_TARGET_COMPLETELY:
			{
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				const RwRGBA color = { 96, 48, 0, 255 };
				for (int32 i = 0; i < 25; i++) {
					CVector vecDir = CVector(
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(0.10f, 0.25f) + fDirectionZ
					);
					++nFrameGen;
					int32 currentFrame = nFrameGen & 3;
					RwRGBA randomColor = color;
					switch (m_nCollisionDamageEffect) {
						case DAMAGE_EFFECT_SMASH_CARDBOARD_COMPLETELY: {
							float fRandom = CGeneral::GetRandomNumberInRange(0.01f, 1.0f);
							randomColor.red *= fRandom;
							randomColor.green *= fRandom;
							randomColor.blue *= fRandom;
							break;
						}
						case DAMAGE_EFFECT_SMASH_YELLOW_TARGET_COMPLETELY: {
							randomColor.red = 0xff;
							randomColor.green = 0xfc;
							break;
						}
					}
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, vecPos, vecDir, nil, fSize, randomColor, nRotationSpeed, 0, currentFrame, 0);
				}
				PlayOneShotScriptObject(SCRIPT_SOUND_BOX_DESTROYED_2, vecPos);
				break;
			}
			case DAMAGE_EFFECT_SMASH_WOODENBOX_COMPLETELY:
			{
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				static const RwRGBA color = { 128, 128, 128, 255 };
				CVector position = GetPosition();
				for (int32 i = 0; i < 45; i++) {
					CVector vecDir = CVector(
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(0.10f, 0.25f) + fDirectionZ
					);
					++nFrameGen;
					int32 currentFrame = nFrameGen & 3;
					float fRandom = CGeneral::GetRandomNumberInRange(0.5f, 1.0f);
					RwRGBA randomColor = { uint8(color.red * fRandom), uint8(color.green * fRandom), uint8(color.blue * fRandom), color.alpha };
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, vecPos, vecDir, nil, fSize, randomColor, nRotationSpeed, 0, currentFrame, 0);
				}
				PlayOneShotScriptObject(SCRIPT_SOUND_BOX_DESTROYED_1, vecPos);
				break;
			}
			case DAMAGE_EFFECT_SMASH_TRAFFICCONE_COMPLETELY:
			case DAMAGE_EFFECT_BURST_BEACHBALL:
			{
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				const RwRGBA color1 = { 200, 0, 0, 255 };
				const RwRGBA color2 = { 200, 200, 200, 255 };
				for (int32 i = 0; i < 10; i++) {
					CVector vecDir = CVector(
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(0.10f, 0.25f) + fDirectionZ
					);
					++nFrameGen;
					int32 currentFrame = nFrameGen & 3;
					RwRGBA color = color2;
					if (nFrameGen & 1)
						color = color1;
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, vecPos, vecDir, nil, fSize, color, nRotationSpeed, 0, currentFrame, 0);
				}
				if (m_nCollisionDamageEffect == DAMAGE_EFFECT_BURST_BEACHBALL) {
					PlayOneShotScriptObject(SCRIPT_SOUND_HIT_BALL, vecPos);
				} else {
					PlayOneShotScriptObject(SCRIPT_SOUND_TIRE_COLLISION, vecPos);
				}
				break;
			}
			case DAMAGE_EFFECT_SMASH_BARPOST_COMPLETELY:
			{
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				const RwRGBA color1 = { 200, 0, 0, 255 };
				const RwRGBA color2 = { 200, 200, 200, 255 };
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				for (int32 i = 0; i < 32; i++) {
					CVector vecDir = CVector(
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(0.10f, 0.25f) + fDirectionZ
					);
					++nFrameGen;
					int32 currentFrame = nFrameGen & 3;
					const RwRGBA &color = nFrameGen & 1 ? color1 : color2;
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, vecPos, vecDir, nil, fSize, color, nRotationSpeed, 0, currentFrame, 0);
				}
				PlayOneShotScriptObject(SCRIPT_SOUND_METAL_COLLISION, vecPos);
				break;
			}
			case DAMAGE_EFFECT_SMASH_NEWSTANDNEW1:
			case DAMAGE_EFFECT_SMASH_NEWSTANDNEW2:
			case DAMAGE_EFFECT_SMASH_NEWSTANDNEW3:
			case DAMAGE_EFFECT_SMASH_NEWSTANDNEW4:
			case DAMAGE_EFFECT_SMASH_NEWSTANDNEW5:
			{
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				CRGBA possibleColor1;
				CRGBA possibleColor2;
				switch (m_nCollisionDamageEffect) {
					case DAMAGE_EFFECT_SMASH_NEWSTANDNEW1:
						possibleColor1 = CRGBA(0xC0, 0x3E, 0xC, 0xFF);
						possibleColor2 = possibleColor1;
						break;
					case DAMAGE_EFFECT_SMASH_NEWSTANDNEW2:
						possibleColor1 = CRGBA(0xA3, 0x36, 0x21, 0xFF);
						possibleColor2 = possibleColor1;
						break;
					case DAMAGE_EFFECT_SMASH_NEWSTANDNEW3:
						possibleColor1 = CRGBA(0x12, 0x31, 0x24, 0xFF);
						possibleColor2 = possibleColor1;
						break;
					case DAMAGE_EFFECT_SMASH_NEWSTANDNEW4:
						possibleColor1 = CRGBA(0xC0, 0xC8, 0xBE, 0xFF);
						possibleColor2 = CRGBA(0x10, 0x57, 0x85, 0xFF);
						break;
					case DAMAGE_EFFECT_SMASH_NEWSTANDNEW5:
						possibleColor1 = CRGBA(0xD0, 0x94, 0x1B, 0xFF);
						possibleColor2 = possibleColor1;
						break;
				}
				for (int32 i = 0; i < 16; i++) {
					CVector vecDir(
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(0.10f, 0.15f) + fDirectionZ
					);
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
					++nFrameGen;
					int32 nCurFrame = nFrameGen & 0x3;
					CRGBA &selectedColor = nFrameGen & 0x1 ? possibleColor1 : possibleColor2;
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, vecPos, vecDir, nil, fSize, selectedColor, nRotationSpeed, 0, nCurFrame, 0);
					if (!(i % 7)) {
						static CRGBA secondParticleColors[4] = {
							CRGBA(0xA0, 0x60, 0x60, 0xFF),
							CRGBA(0x60, 0xA0, 0x60, 0xFF),
							CRGBA(0x60, 0x60, 0xA0, 0xFF),
							CRGBA(0xA0, 0xA0, 0xA0, 0xFF)
						};
						vecDir *= 0.5f;
						CRGBA &secondParticleColor = secondParticleColors[nFrameGen & 3];
						int32 nSecondRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
						CParticle::AddParticle(PARTICLE_DEBRIS, vecPos, vecDir, nil, 0.1f, secondParticleColor, nSecondRotationSpeed, 0, 1, 0);
					}
				}
				PlayOneShotScriptObject(SCRIPT_SOUND_METAL_COLLISION, vecPos);
				break;
			}
			case DAMAGE_EFFECT_SMASH_VEGPALM:
			{
				static RwRGBA primaryColor1 = { 0x39, 0x4D, 0x29, 0xff };
				static RwRGBA primaryColor2 = { 0x94, 0x7D, 0x73, 0xff };
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				float fRadius = GetColModel()->boundingSphere.radius;
				for (int32 i = 0; i < 32; i++) {
					CVector particleDir = CVector(
						CGeneral::GetRandomNumberInRange(-0.25f, 0.25f),
						CGeneral::GetRandomNumberInRange(-0.25f, 0.25f),
						CGeneral::GetRandomNumberInRange(-0.05f, 0.05f) + fDirectionZ
					);
					CVector particlePos = vecPos;
					particlePos.z += CGeneral::GetRandomNumberInRange(0.0f, 1.0f) * fRadius;
					++nFrameGen;
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
					int32 nCurFrame = nFrameGen & 0x3;
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					RwRGBA& particleColor = nFrameGen & 1 ? primaryColor1 : primaryColor2;
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, particlePos, particleDir, nil, fSize, particleColor, nRotationSpeed, 0, nCurFrame, 0);
					if ((i % 7) == 0) {
						static RwRGBA secondaryColor = { 0x9A, 0x99, 0x99, 0x3E };
						CParticle::AddParticle(PARTICLE_DEBRIS, particlePos, particleDir, nil, 0.3f, secondaryColor, nRotationSpeed);
					}
				}
				PlayOneShotScriptObject(SCRIPT_SOUND_BOX_DESTROYED_2, vecPos);
				break;
			}
			case DAMAGE_EFFECT_SMASH_BLACKBAG:
			case DAMAGE_EFFECT_SMASH_BEACHLOUNGE_WOOD:
			case DAMAGE_EFFECT_SMASH_BEACHLOUNGE_TOWEL:
			{
				bIsVisible = false;
				bUsesCollision = false;
				if (!GetIsStatic()) {
					RemoveFromMovingList();
				}
				SetIsStatic(true);
				bExplosionProof = true;
				SetMoveSpeed(0.0f, 0.0f, 0.0f);
				SetTurnSpeed(0.0f, 0.0f, 0.0f);
				CRGBA possibleColor1;
				CRGBA possibleColor2;
				switch (m_nCollisionDamageEffect) {
					case DAMAGE_EFFECT_SMASH_BLACKBAG:
						possibleColor1 = CRGBA(0, 0, 0, 0xFF);
						possibleColor2 = possibleColor1;
						break;
					case DAMAGE_EFFECT_SMASH_BEACHLOUNGE_WOOD:
						possibleColor1 = CRGBA(0x8F, 0x8A, 0x8C, 0xFF);
						possibleColor2 = CRGBA(0x73, 0x75, 0x7B, 0xFF);
						break;
					case DAMAGE_EFFECT_SMASH_BEACHLOUNGE_TOWEL:
						possibleColor1 = CRGBA(0x52, 0x92, 0x4A, 0xFF);
						possibleColor2 = CRGBA(0xCE, 0xCF, 0xCE, 0xFF);
						break;
				}
				for (int32 i = 0; i < 16; i++) {
					CVector vecDir(
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(-0.35f, 0.35f),
						CGeneral::GetRandomNumberInRange(0.10f, 0.25f) + fDirectionZ
					);
					++nFrameGen;
					int32 nCurFrame = nFrameGen & 0x3;
					CRGBA &selectedColor = nFrameGen & 0x1 ? possibleColor1 : possibleColor2;
					float fSize = CGeneral::GetRandomNumberInRange(0.02f, 0.20f);
					int32 nRotationSpeed = CGeneral::GetRandomNumberInRange(-40, 40);
					CParticle::AddParticle(PARTICLE_CAR_DEBRIS, vecPos, vecDir, nil, fSize, selectedColor, nRotationSpeed, 0, nCurFrame, 0);
				}
				if (m_nCollisionDamageEffect == DAMAGE_EFFECT_SMASH_BLACKBAG) {
					PlayOneShotScriptObject(SCRIPT_SOUND_BOX_DESTROYED_2, vecPos);
				} else if (m_nCollisionDamageEffect == DAMAGE_EFFECT_SMASH_BEACHLOUNGE_WOOD) {
					PlayOneShotScriptObject(SCRIPT_SOUND_METAL_COLLISION, vecPos);
				}
				break;
			}
			default:
				DEV("Unhandled collision damage effect id: %d\n", m_nCollisionDamageEffect);
				return;
		}
	}
}

void
CObject::RefModelInfo(int32 modelId)
{
	m_nRefModelIndex = modelId;
	CModelInfo::GetModelInfo(modelId)->AddRef();
}

void
CObject::Init(void)
{
	m_type = ENTITY_TYPE_OBJECT;
	CObjectData::SetObjectData(GetModelIndex(), *this);
	m_nEndOfLifeTime = 0;
	ObjectCreatedBy = GAME_OBJECT;
	SetIsStatic(true);
	bIsPickup = false;
	bPickupObjWithMessage = false;
	bOutOfStock = false;
	bGlassCracked = false;
	bGlassBroken = false;
	bHasBeenDamaged = false;
	bUseVehicleColours = false;
	m_nRefModelIndex = -1;
	m_colour1 = 0;
	m_colour2 = 0;
	m_nBonusValue = 0;
	bIsWeapon = false;
	m_nCostValue = 0;
	m_pCollidingEntity = nil;
	CColPoint point;
	CEntity *outEntity = nil;
	const CVector& vecPos = GetMatrix().GetPosition();
	if (CWorld::ProcessVerticalLine(vecPos, vecPos.z - 10.0f, point, outEntity, true, false, false, false, false, false, nil))
		m_pCurSurface = outEntity;
	else
		m_pCurSurface = nil;

	if (GetModelIndex() == MI_BUOY)
		bTouchingWater = true;

	if (CModelInfo::GetModelInfo(GetModelIndex())->GetModelType() == MITYPE_WEAPON)
		bIsWeapon = true;
	bIsStreetLight = IsLightObject(GetModelIndex());

	m_area = AREA_EVERYWHERE;
}

bool
CObject::CanBeDeleted(void)
{
	switch (ObjectCreatedBy) {
		case GAME_OBJECT:
			return true;
		case MISSION_OBJECT:
			return false;
		case TEMP_OBJECT:
			return true;
		case CUTSCENE_OBJECT:
			return false;
		case CONTROLLED_SUB_OBJECT:
			return false;
		default:
			return true;
	}
}

void
CObject::DeleteAllMissionObjects()
{
	CObjectPool *objectPool = CPools::GetObjectPool();
	for (int32 i = 0; i < objectPool->GetSize(); i++) {
		CObject *pObject = objectPool->GetSlot(i);
		if (pObject && pObject->ObjectCreatedBy == MISSION_OBJECT) {
			CWorld::Remove(pObject);
			delete pObject;
		}
	}
}

void
CObject::DeleteAllTempObjects()
{
	CObjectPool *objectPool = CPools::GetObjectPool();
	for (int32 i = 0; i < objectPool->GetSize(); i++) {
		CObject *pObject = objectPool->GetSlot(i);
		if (pObject && pObject->ObjectCreatedBy == TEMP_OBJECT) {
			CWorld::Remove(pObject);
			delete pObject;
		}
	}
}

void
CObject::DeleteAllTempObjectsInArea(CVector point, float fRadius)
{
	CObjectPool *objectPool = CPools::GetObjectPool();
	for (int32 i = 0; i < objectPool->GetSize(); i++) {
		CObject *pObject = objectPool->GetSlot(i);
		if (pObject && pObject->ObjectCreatedBy == TEMP_OBJECT && (point - pObject->GetPosition()).MagnitudeSqr() < SQR(fRadius)) {
			CWorld::Remove(pObject);
			delete pObject;
		}
	}
}

bool
IsObjectPointerValid(CObject *pObject)
{
	if (!pObject)
		return false;
	int index = CPools::GetObjectPool()->GetJustIndex_NoFreeAssert(pObject);
#ifdef FIX_BUGS
	if (index < 0 || index >= CPools::GetObjectPool()->GetSize())
#else
	if (index < 0 || index > CPools::GetObjectPool()->GetSize())
#endif
		return false;
	return pObject->bIsBIGBuilding || pObject->m_entryInfoList.first;
}
