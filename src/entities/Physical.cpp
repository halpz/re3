#include "common.h"
#include "patcher.h"
#include "World.h"
#include "Timer.h"
#include "ModelIndices.h"
#include "Vehicle.h"
#include "Ped.h"
#include "Object.h"
#include "Glass.h"
#include "ParticleObject.h"
#include "Particle.h"
#include "SurfaceTable.h"
#include "Physical.h"

void
CPhysical::Add(void)
{
	int x, xstart, xmid, xend;
	int y, ystart, ymid, yend;
	CSector *s;
	CPtrList *list;

	CRect bounds = GetBoundRect();
	xstart = CWorld::GetSectorIndexX(bounds.left);
	xend   = CWorld::GetSectorIndexX(bounds.right);
	xmid   = CWorld::GetSectorIndexX((bounds.left + bounds.right)/2.0f);
	ystart = CWorld::GetSectorIndexY(bounds.bottom);
	yend   = CWorld::GetSectorIndexY(bounds.top);
	ymid   = CWorld::GetSectorIndexY((bounds.bottom + bounds.top)/2.0f);
	assert(xstart >= 0);
	assert(xend < NUMSECTORS_X);
	assert(ystart >= 0);
	assert(yend < NUMSECTORS_Y);

	for(y = ystart; y <= yend; y++)
		for(x = xstart; x <= xend; x++){
			s = CWorld::GetSector(x, y);
			if(x == xmid && y == ymid) switch(m_type){
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS];
				break;
			default:
				assert(0);
			}else switch(m_type){
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES_OVERLAP];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS_OVERLAP];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS_OVERLAP];
				break;
			default:
				assert(0);
			}
			CPtrNode *node = list->InsertItem(this);
			assert(node);
			m_entryInfoList.InsertItem(list, node, s);
		}
}

void
CPhysical::Remove(void)
{
	CEntryInfoNode *node, *next;
	for(node = m_entryInfoList.first; node; node = next){
		next = node->next;
		node->list->DeleteNode(node->listnode);
		m_entryInfoList.DeleteNode(node);
	}
}

void
CPhysical::RemoveAndAdd(void)
{
	int x, xstart, xmid, xend;
	int y, ystart, ymid, yend;
	CSector *s;
	CPtrList *list;

	CRect bounds = GetBoundRect();
	xstart = CWorld::GetSectorIndexX(bounds.left);
	xend   = CWorld::GetSectorIndexX(bounds.right);
	xmid   = CWorld::GetSectorIndexX((bounds.left + bounds.right)/2.0f);
	ystart = CWorld::GetSectorIndexY(bounds.bottom);
	yend   = CWorld::GetSectorIndexY(bounds.top);
	ymid   = CWorld::GetSectorIndexY((bounds.bottom + bounds.top)/2.0f);
	assert(xstart >= 0);
	assert(xend < NUMSECTORS_X);
	assert(ystart >= 0);
	assert(yend < NUMSECTORS_Y);

	// we'll try to recycle nodes from here
	CEntryInfoNode *next = m_entryInfoList.first;

	for(y = ystart; y <= yend; y++)
		for(x = xstart; x <= xend; x++){
			s = CWorld::GetSector(x, y);
			if(x == xmid && y == ymid) switch(m_type){
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS];
				break;
			}else switch(m_type){
			case ENTITY_TYPE_VEHICLE:
				list = &s->m_lists[ENTITYLIST_VEHICLES_OVERLAP];
				break;
			case ENTITY_TYPE_PED:
				list = &s->m_lists[ENTITYLIST_PEDS_OVERLAP];
				break;
			case ENTITY_TYPE_OBJECT:
				list = &s->m_lists[ENTITYLIST_OBJECTS_OVERLAP];
				break;
			}
			if(next){
				// If we still have old nodes, use them
				next->list->RemoveNode(next->listnode);
				list->InsertNode(next->listnode);
				next->list = list;
				next->sector = s;
				next = next->next;
			}else{
				CPtrNode *node = list->InsertItem(this);
				m_entryInfoList.InsertItem(list, node, s);
			}
		}

	// Remove old nodes we no longer need
	CEntryInfoNode *node;
	for(node = next; node; node = next){
		next = node->next;
		node->list->DeleteNode(node->listnode);
		m_entryInfoList.DeleteNode(node);
	}
}

CRect
CPhysical::GetBoundRect(void)
{
	CVector center;
	float radius;
	GetBoundCentre(center);
	radius = GetBoundRadius();
	return CRect(center.x-radius, center.y-radius, center.x+radius, center.y+radius);
}

void
CPhysical::AddToMovingList(void)
{
	m_movingListNode = CWorld::GetMovingEntityList().InsertItem(this);
}

void
CPhysical::RemoveFromMovingList(void)
{
	if(m_movingListNode){
		CWorld::GetMovingEntityList().DeleteNode(m_movingListNode);
		m_movingListNode = nil;
	}
}


/*
 * Some quantities (german in parens):
 *
 * acceleration: distance/time^2: a
 * velocity: distance/time: v	(GTA: speed)
 * momentum (impuls): velocity*mass: p
 * impulse (kraftstoss): delta momentum, force*time: J
 *
 * angular equivalents:
 * velocity -> angular velocity	(GTA: turn speed)
 * momentum -> angular momentum (drehimpuls): L = r cross p
 * force -> torque (drehmoment): tau = r cross F
 * mass -> moment of inertia, angular mass (drehmoment, drehmasse): I = L/omega	(GTA: turn mass)
 */

CVector
CPhysical::GetSpeed(const CVector &r)
{
	return m_vecMoveSpeed + m_vecMoveFriction + CrossProduct(m_vecTurnFriction + m_vecTurnSpeed, r);
}

void
CPhysical::ApplyMoveSpeed(void)
{
	GetPosition() += m_vecMoveSpeed * CTimer::GetTimeStep();
}

void
CPhysical::ApplyTurnSpeed(void)
{
	// Move the coordinate axes by their speed
	// Note that this denormalizes the matrix
	CVector turnvec = m_vecTurnSpeed*CTimer::GetTimeStep();
	GetRight() += CrossProduct(turnvec, GetRight());
	GetForward() += CrossProduct(turnvec, GetForward());
	GetUp() += CrossProduct(turnvec, GetUp());
}

void
CPhysical::ApplyMoveForce(float jx, float jy, float jz)
{
	m_vecMoveSpeed += CVector(jx, jy, jz)*(1.0f/m_fMass);
}

void
CPhysical::ApplyTurnForce(float jx, float jy, float jz, float px, float py, float pz)
{
	CVector com = Multiply3x3(m_matrix, m_vecCentreOfMass);
	CVector turnimpulse = CrossProduct(CVector(px, py, pz)-com, CVector(jx, jy, jz));
	m_vecTurnSpeed += turnimpulse*(1.0f/m_fTurnMass);
}

void
CPhysical::ApplyFrictionMoveForce(float jx, float jy, float jz)
{
	m_vecMoveFriction += CVector(jx, jy, jz)*(1.0f/m_fMass);
}

void
CPhysical::ApplyFrictionTurnForce(float jx, float jy, float jz, float px, float py, float pz)
{
	CVector com = Multiply3x3(m_matrix, m_vecCentreOfMass);
	CVector turnimpulse = CrossProduct(CVector(px, py, pz)-com, CVector(jx, jy, jz));
	m_vecTurnFriction += turnimpulse*(1.0f/m_fTurnMass);
}

void
CPhysical::ApplySpringCollision(float f1, CVector &v, CVector &p, float f2, float f3)
{
	if(1.0f - f2 <= 0.0f)
		return;
	float step = min(CTimer::GetTimeStep(), 3.0f);
	float strength = -0.008f*m_fMass*2.0f*step * f1 * (1.0f-f2) * f3;
	ApplyMoveForce(v.x*strength, v.y*strength, v.z*strength);
	ApplyTurnForce(v.x*strength, v.y*strength, v.z*strength, p.x, p.y, p.z);
}

void
CPhysical::ApplyGravity(void)
{
	if(bAffectedByGravity)
		m_vecMoveSpeed.z -= 0.008f * CTimer::GetTimeStep();
}

void
CPhysical::ApplyFriction(void)
{
	m_vecMoveSpeed += m_vecMoveFriction;
	m_vecTurnSpeed += m_vecTurnFriction;
	m_vecMoveFriction = CVector(0.0f, 0.0f, 0.0f);
	m_vecTurnFriction = CVector(0.0f, 0.0f, 0.0f);
}

void
CPhysical::ApplyAirResistance(void)
{
	if(m_fAirResistance > 0.1f){
		float f = powf(m_fAirResistance, CTimer::GetTimeStep());
		m_vecMoveSpeed *= f;
		m_vecTurnSpeed *= f;
	}else{
		float f = powf(1.0f/(m_fAirResistance*0.5f*m_vecMoveSpeed.MagnitudeSqr() + 1.0f), CTimer::GetTimeStep());
		m_vecMoveSpeed *= f;
		m_vecTurnSpeed *= 0.99f;
	}
}


bool
CPhysical::ApplyCollision(CPhysical *B, CColPoint &colpoint, float &impulseA, float &impulseB)
{
	float eA, eB;
	CPhysical *A = this;
	CObject *Bobj = (CObject*)B;

	bool ispedcontactA = false;
	bool ispedcontactB = false;

	float timestepA;
	if(B->bPedPhysics){
		timestepA = 10.0f;
		if(B->IsPed() && ((CPed*)B)->m_pCurrentPhysSurface == A)
			ispedcontactA = true;
	}else
		timestepA = A->m_phy_flagA1 ? 2.0f : 1.0f;

	float timestepB;
	if(A->bPedPhysics){
		if(A->IsPed() && ((CPed*)A)->IsPlayer() && B->IsVehicle() &&
		   (B->m_status == STATUS_ABANDONED || B->m_status == STATUS_WRECKED || A->bHasHitWall))
			timestepB = 2200.0f / B->m_fMass;
		else
			timestepB = 10.0f;

		if(A->IsPed() && ((CPed*)A)->m_pCurrentPhysSurface == B)
			ispedcontactB = true;
	}else
		timestepB = B->m_phy_flagA1 ? 2.0f : 1.0f;

	float speedA, speedB;
	if(B->bIsStatic){
		if(A->bPedPhysics){
			speedA = DotProduct(A->m_vecMoveSpeed, colpoint.normal);
			if(speedA < 0.0f){
				if(B->IsObject()){
					impulseA = -speedA * A->m_fMass;
					impulseB = impulseA;
					if(impulseA > Bobj->m_fUprootLimit){
						if(IsGlass(B->GetModelIndex()))
							CGlass::WindowRespondsToCollision(B, impulseA, A->m_vecMoveSpeed, colpoint.point, false);
						else if(!B->bInfiniteMass)
							B->bIsStatic = false;
					}else{
						if(IsGlass(B->GetModelIndex()))
							CGlass::WindowRespondsToSoftCollision(B, impulseA);
						if(!A->bInfiniteMass)
							A->ApplyMoveForce(colpoint.normal*(1.0f + A->m_fElasticity)*impulseA);
						return true;
					}
				}else if(!B->bInfiniteMass)
					B->bIsStatic = false;
	
				if(B->bInfiniteMass){
					impulseA = -speedA * A->m_fMass;
					impulseB = 0.0f;
					if(!A->bInfiniteMass)
						A->ApplyMoveForce(colpoint.normal*(1.0f + A->m_fElasticity)*impulseA);
					return true;
				}
			}
		}else{
			CVector pointposA = colpoint.point - A->GetPosition();
			speedA = DotProduct(A->GetSpeed(pointposA), colpoint.normal);
			if(speedA < 0.0f){
				if(B->IsObject()){
					if(A->bHasHitWall)
						eA = -1.0f;
					else
						eA = -(1.0f + A->m_fElasticity);
					impulseA = eA * speedA * A->GetMass(pointposA, colpoint.normal);
					impulseB = impulseA;

					if(Bobj->m_nCollisionDamageEffect && impulseA > 20.0f){
						Bobj->ObjectDamage(impulseA);
						if(!B->bUsesCollision){
							if(!A->bInfiniteMass){
								A->ApplyMoveForce(colpoint.normal*0.2f*impulseA);
								A->ApplyTurnForce(colpoint.normal*0.2f*impulseA, pointposA);
							}
							return false;
						}
					}

					if((impulseA > Bobj->m_fUprootLimit || A->bIsStuck) &&
					   !B->bInfiniteMass){
						if(IsGlass(B->GetModelIndex()))
							CGlass::WindowRespondsToCollision(B, impulseA, A->m_vecMoveSpeed, colpoint.point, false);
						else
							B->bIsStatic = false;
						int16 model = B->GetModelIndex();
						if(model == MI_FIRE_HYDRANT && !Bobj->bHasBeenDamaged){
							CParticleObject::AddObject(POBJECT_FIRE_HYDRANT, B->GetPosition() - CVector(0.0f, 0.0f, 0.5f), true);
							Bobj->bHasBeenDamaged = true;
						}else if(B->IsObject() && model != MI_EXPLODINGBARREL && model != MI_PETROLPUMP)
							Bobj->bHasBeenDamaged = true;
					}else{
						if(IsGlass(B->GetModelIndex()))
							CGlass::WindowRespondsToSoftCollision(B, impulseA);
						CVector f = colpoint.normal * impulseA;
						if(A->IsVehicle() && colpoint.normal.z < 0.7f)
							f.z *= 0.3f;
						if(!A->bInfiniteMass){
							A->ApplyMoveForce(f);
							if(!A->IsVehicle() || !CWorld::bNoMoreCollisionTorque)
								A->ApplyTurnForce(f, pointposA);
						}
						return true;
					}
				}else if(!B->bInfiniteMass)
					B->bIsStatic = false;
			}
		}
	
		if(B->bIsStatic)
			return false;
		if(!B->bInfiniteMass)
			B->AddToMovingList();
	}

	// B is not static

	if(A->bPedPhysics && B->bPedPhysics){
		// negative if A is moving towards B
		speedA = DotProduct(A->m_vecMoveSpeed, colpoint.normal);
		// positive if B is moving towards A
		// not interested in how much B moves into A apparently?
		// only interested in cases where A collided into B
		speedB = max(0.0f, DotProduct(B->m_vecMoveSpeed, colpoint.normal));
		// A has moved into B
		if(speedA < speedB){
			if(!A->bHasHitWall)
				speedB -= (speedA - speedB) * (A->m_fElasticity+B->m_fElasticity)/2.0f;
			impulseA = (speedB-speedA) * A->m_fMass * timestepA;
			if(!A->bInfiniteMass)
				A->ApplyMoveForce(colpoint.normal*(impulseA/timestepA));
			return true;
		}
	}else if(A->bPedPhysics){
		CVector pointposB = colpoint.point - B->GetPosition();
		speedA = DotProduct(A->m_vecMoveSpeed, colpoint.normal);
		speedB = DotProduct(B->GetSpeed(pointposB), colpoint.normal);

		float a = A->m_fMass*timestepA;
		float b = B->GetMassTime(pointposB, colpoint.normal, timestepB);
		float speedSum = (b*speedB + a*speedA)/(a + b);
		if(speedA < speedSum){
			if(A->bHasHitWall)
				eA = speedSum;
			else
				eA = speedSum - (speedA - speedSum) * (A->m_fElasticity+B->m_fElasticity)/2.0f;
			if(B->bHasHitWall)
				eB = speedSum;
			else
				eB = speedSum - (speedB - speedSum) * (A->m_fElasticity+B->m_fElasticity)/2.0f;
			impulseA = (eA - speedA) * a;
			impulseB = -(eB - speedB) * b;
			CVector fA = colpoint.normal*(impulseA/timestepA);
			CVector fB = colpoint.normal*(-impulseB/timestepB);
			if(!A->bInfiniteMass){
				if(fA.z < 0.0f) fA.z = 0.0f;
				if(ispedcontactB){
					fA.x *= 2.0f;
					fA.y *= 2.0f;
				}
				A->ApplyMoveForce(fA);
			}
			if(!B->bInfiniteMass && !ispedcontactB){
				B->ApplyMoveForce(fB);
				B->ApplyTurnForce(fB, pointposB);
			}
			return true;
		}
	}else if(B->bPedPhysics){
		CVector pointposA = colpoint.point - A->GetPosition();
		speedA = DotProduct(A->GetSpeed(pointposA), colpoint.normal);
		speedB = DotProduct(B->m_vecMoveSpeed, colpoint.normal);

		float a = A->GetMassTime(pointposA, colpoint.normal, timestepA);
		float b = B->m_fMass*timestepB;
		float speedSum = (b*speedB + a*speedA)/(a + b);
		if(speedA < speedSum){
			if(A->bHasHitWall)
				eA = speedSum;
			else
				eA = speedSum - (speedA - speedSum) * (A->m_fElasticity+B->m_fElasticity)/2.0f;
			if(B->bHasHitWall)
				eB = speedSum;
			else
				eB = speedSum - (speedB - speedSum) * (A->m_fElasticity+B->m_fElasticity)/2.0f;
			impulseA = (eA - speedA) * a;
			impulseB = -(eB - speedB) * b;
			CVector fA = colpoint.normal*(impulseA/timestepA);
			CVector fB = colpoint.normal*(-impulseB/timestepB);
			if(!A->bInfiniteMass && !ispedcontactA){
				if(fA.z < 0.0f) fA.z = 0.0f;
				A->ApplyMoveForce(fA);
				A->ApplyTurnForce(fA, pointposA);
			}
			if(!B->bInfiniteMass){
				if(fB.z < 0.0f){
					fB.z = 0.0f;
					if(fabs(speedA) < 0.01f)
						fB *= 0.5f;
				}
				if(ispedcontactA){
					fB.x *= 2.0f;
					fB.y *= 2.0f;
				}
				B->ApplyMoveForce(fB);
			}
			return true;
		}
	}else{
		CVector pointposA = colpoint.point - A->GetPosition();
		CVector pointposB = colpoint.point - B->GetPosition();
		speedA = DotProduct(A->GetSpeed(pointposA), colpoint.normal);
		speedB = DotProduct(B->GetSpeed(pointposB), colpoint.normal);
		float a = A->GetMassTime(pointposA, colpoint.normal, timestepA);
		float b = B->GetMassTime(pointposB, colpoint.normal, timestepB);
		float speedSum = (b*speedB + a*speedA)/(a + b);
		if(speedA < speedSum){
			if(A->bHasHitWall)
				eA = speedSum;
			else
				eA = speedSum - (speedA - speedSum) * (A->m_fElasticity+B->m_fElasticity)/2.0f;
			if(B->bHasHitWall)
				eB = speedSum;
			else
				eB = speedSum - (speedB - speedSum) * (A->m_fElasticity+B->m_fElasticity)/2.0f;
			impulseA = (eA - speedA) * a;
			impulseB = -(eB - speedB) * b;
			CVector fA = colpoint.normal*(impulseA/timestepA);
			CVector fB = colpoint.normal*(-impulseB/timestepB);
			if(A->IsVehicle() && !A->bHasHitWall){
				fA.x *= 1.4f;
				fA.y *= 1.4f;
				if(colpoint.normal.z < 0.7f)
					fA.z *= 0.3f;
				if(A->m_status == STATUS_PLAYER)
					pointposA *= 0.8f;
				if(CWorld::bNoMoreCollisionTorque){
					A->ApplyFrictionMoveForce(fA*-0.3f);
					A->ApplyFrictionTurnForce(fA*-0.3f, pointposA);
				}
			}
			if(B->IsVehicle() && !B->bHasHitWall){
				fB.x *= 1.4f;
				fB.y *= 1.4f;
				if(colpoint.normal.z < 0.7f)
					fB.z *= 0.3f;
				if(B->m_status == STATUS_PLAYER)
					pointposB *= 0.8f;
				if(CWorld::bNoMoreCollisionTorque){
					// BUG: the game actually uses A here, but this can't be right
					B->ApplyFrictionMoveForce(fB*-0.3f);
					B->ApplyFrictionTurnForce(fB*-0.3f, pointposB);
				}
			}
			if(!A->bInfiniteMass){
				A->ApplyMoveForce(fA);
				A->ApplyTurnForce(fA, pointposA);
			}
			if(!B->bInfiniteMass){
				if(B->bIsInSafePosition)
					B->UnsetIsInSafePosition();
				B->ApplyMoveForce(fB);
				B->ApplyTurnForce(fB, pointposB);
			}
			return true;
		}
	}
	return false;
}

bool
CPhysical::ApplyCollisionAlt(CEntity *B, CColPoint &colpoint, float &impulse, CVector &moveSpeed, CVector &turnSpeed)
{
	float normalSpeed;
	float e;
	CVector speed;
	CVector vImpulse;

	if(bPedPhysics){
		normalSpeed = DotProduct(m_vecMoveSpeed, colpoint.normal);
		if(normalSpeed < 0.0f){
			impulse = -normalSpeed * m_fMass;
			ApplyMoveForce(colpoint.normal * impulse);
			return true;
		}
	}else{
		CVector pointpos = colpoint.point - GetPosition();
		speed = GetSpeed(pointpos);
		normalSpeed = DotProduct(speed, colpoint.normal);
		if(normalSpeed < 0.0f){
			float minspeed = 0.0104f * CTimer::GetTimeStep();
			if((IsObject() || IsVehicle() && GetUp().z < -0.3f) &&
			   !bHasContacted &&
			   fabs(m_vecMoveSpeed.x) < minspeed &&
			   fabs(m_vecMoveSpeed.y) < minspeed &&
			   fabs(m_vecMoveSpeed.z) < minspeed*2.0f)
				e = -1.0f;
			else
				e = -(m_fElasticity + 1.0f);
			impulse = normalSpeed * e * GetMass(pointpos, colpoint.normal);

			// ApplyMoveForce
			vImpulse = colpoint.normal*impulse;
			if(IsVehicle() &&
			   (!bHasHitWall ||
			    !(m_vecMoveSpeed.MagnitudeSqr() > 0.1 || !(B->IsBuilding() || ((CPhysical*)B)->bInfiniteMass))))
				moveSpeed += vImpulse * 1.2f * (1.0f/m_fMass);
			else
				moveSpeed += vImpulse * (1.0f/m_fMass);

			// ApplyTurnForce
			CVector com = Multiply3x3(m_matrix, m_vecCentreOfMass);
			CVector turnimpulse = CrossProduct(pointpos-com, vImpulse);
			turnSpeed += turnimpulse*(1.0f/m_fTurnMass);

			return true;
		}
	}
	return false;
}

bool
CPhysical::ApplyFriction(CPhysical *B, float adhesiveLimit, CColPoint &colpoint)
{
	CVector speedA, speedB;
	float normalSpeedA, normalSpeedB;
	CVector vOtherSpeedA, vOtherSpeedB;
	float fOtherSpeedA, fOtherSpeedB;
	float speedSum;
	CVector frictionDir;
	float impulseA, impulseB;
	float impulseLimit;
	CPhysical *A = this;

	if(A->bPedPhysics && B->bPedPhysics){
		normalSpeedA = DotProduct(A->m_vecMoveSpeed, colpoint.normal);
		normalSpeedB = DotProduct(B->m_vecMoveSpeed, colpoint.normal);
		vOtherSpeedA = A->m_vecMoveSpeed - colpoint.normal*normalSpeedA;
		vOtherSpeedB = B->m_vecMoveSpeed - colpoint.normal*normalSpeedB;

		fOtherSpeedA = vOtherSpeedA.Magnitude();
		fOtherSpeedB = vOtherSpeedB.Magnitude();

		frictionDir = vOtherSpeedA * (1.0f/fOtherSpeedA);
		speedSum = (B->m_fMass*fOtherSpeedB + A->m_fMass*fOtherSpeedA)/(B->m_fMass + A->m_fMass);
		if(fOtherSpeedA > speedSum){
			impulseA = (speedSum - fOtherSpeedA) * A->m_fMass;
			impulseB = (speedSum - fOtherSpeedB) * B->m_fMass;
			impulseLimit = adhesiveLimit*CTimer::GetTimeStep();
			if(impulseA < -impulseLimit) impulseA = -impulseLimit;
			if(impulseB > impulseLimit) impulseB = impulseLimit;		// BUG: game has A's clamp again here, but this can't be right
			A->ApplyFrictionMoveForce(frictionDir*impulseA);
			B->ApplyFrictionMoveForce(frictionDir*impulseB);
			return true;
		}
	}else if(A->bPedPhysics){
		if(B->IsVehicle())
			return false;
		CVector pointposB = colpoint.point - B->GetPosition();
		speedB = B->GetSpeed(pointposB);

		normalSpeedA = DotProduct(A->m_vecMoveSpeed, colpoint.normal);
		normalSpeedB = DotProduct(speedB, colpoint.normal);
		vOtherSpeedA = A->m_vecMoveSpeed - colpoint.normal*normalSpeedA;
		vOtherSpeedB = speedB - colpoint.normal*normalSpeedB;

		fOtherSpeedA = vOtherSpeedA.Magnitude();
		fOtherSpeedB = vOtherSpeedB.Magnitude();

		frictionDir = vOtherSpeedA * (1.0f/fOtherSpeedA);
		float massB = B->GetMass(pointposB, frictionDir);
		speedSum = (massB*fOtherSpeedB + A->m_fMass*fOtherSpeedA)/(massB + A->m_fMass);
		if(fOtherSpeedA > speedSum){
			impulseA = (speedSum - fOtherSpeedA) * A->m_fMass;
			impulseB = (speedSum - fOtherSpeedB) * massB;
			impulseLimit = adhesiveLimit*CTimer::GetTimeStep();
			if(impulseA < -impulseLimit) impulseA = -impulseLimit;
			if(impulseB > impulseLimit) impulseB = impulseLimit;
			A->ApplyFrictionMoveForce(frictionDir*impulseA);
			B->ApplyFrictionMoveForce(frictionDir*impulseB);
			B->ApplyFrictionTurnForce(frictionDir*impulseB, pointposB);
			return true;
		}
	}else if(B->bPedPhysics){
		if(A->IsVehicle())
			return false;
		CVector pointposA = colpoint.point - A->GetPosition();
		speedA = A->GetSpeed(pointposA);

		normalSpeedA = DotProduct(speedA, colpoint.normal);
		normalSpeedB = DotProduct(B->m_vecMoveSpeed, colpoint.normal);
		vOtherSpeedA = speedA - colpoint.normal*normalSpeedA;
		vOtherSpeedB = B->m_vecMoveSpeed - colpoint.normal*normalSpeedB;

		fOtherSpeedA = vOtherSpeedA.Magnitude();
		fOtherSpeedB = vOtherSpeedB.Magnitude();

		frictionDir = vOtherSpeedA * (1.0f/fOtherSpeedA);
		float massA = A->GetMass(pointposA, frictionDir);
		speedSum = (B->m_fMass*fOtherSpeedB + massA*fOtherSpeedA)/(B->m_fMass + massA);
		if(fOtherSpeedA > speedSum){
			impulseA = (speedSum - fOtherSpeedA) * massA;
			impulseB = (speedSum - fOtherSpeedB) * B->m_fMass;
			impulseLimit = adhesiveLimit*CTimer::GetTimeStep();
			if(impulseA < -impulseLimit) impulseA = -impulseLimit;
			if(impulseB > impulseLimit) impulseB = impulseLimit;
			A->ApplyFrictionMoveForce(frictionDir*impulseA);
			A->ApplyFrictionTurnForce(frictionDir*impulseA, pointposA);
			B->ApplyFrictionMoveForce(frictionDir*impulseB);
			return true;
		}
	}else{
		CVector pointposA = colpoint.point - A->GetPosition();
		CVector pointposB = colpoint.point - B->GetPosition();
		speedA = A->GetSpeed(pointposA);
		speedB = B->GetSpeed(pointposB);

		normalSpeedA = DotProduct(speedA, colpoint.normal);
		normalSpeedB = DotProduct(speedB, colpoint.normal);
		vOtherSpeedA = speedA - colpoint.normal*normalSpeedA;
		vOtherSpeedB = speedB - colpoint.normal*normalSpeedB;

		fOtherSpeedA = vOtherSpeedA.Magnitude();
		fOtherSpeedB = vOtherSpeedB.Magnitude();

		frictionDir = vOtherSpeedA * (1.0f/fOtherSpeedA);
		float massA = A->GetMass(pointposA, frictionDir);
		float massB = B->GetMass(pointposB, frictionDir);
		speedSum = (massB*fOtherSpeedB + massA*fOtherSpeedA)/(massB + massA);
		if(fOtherSpeedA > speedSum){
			impulseA = (speedSum - fOtherSpeedA) * massA;
			impulseB = (speedSum - fOtherSpeedB) * massB;
			impulseLimit = adhesiveLimit*CTimer::GetTimeStep();
			if(impulseA < -impulseLimit) impulseA = -impulseLimit;
			if(impulseB > impulseLimit) impulseB = impulseLimit;
			A->ApplyFrictionMoveForce(frictionDir*impulseA);
			A->ApplyFrictionTurnForce(frictionDir*impulseA, pointposA);
			B->ApplyFrictionMoveForce(frictionDir*impulseB);
			B->ApplyFrictionTurnForce(frictionDir*impulseB, pointposB);
			return true;
		}
	}
	return false;
}

bool
CPhysical::ApplyFriction(float adhesiveLimit, CColPoint &colpoint)
{
	CVector speed;
	float normalSpeed;
	CVector vOtherSpeed;
	float fOtherSpeed;
	CVector frictionDir;
	float fImpulse;
	float impulseLimit;

	if(bPedPhysics){
		normalSpeed = DotProduct(m_vecMoveSpeed, colpoint.normal);
		vOtherSpeed = m_vecMoveSpeed - colpoint.normal*normalSpeed;

		fOtherSpeed = vOtherSpeed.Magnitude();
		if(fOtherSpeed > 0.0f){
			frictionDir = vOtherSpeed * (1.0f/fOtherSpeed);
			// not really impulse but speed
			// maybe use ApplyFrictionMoveForce instead?
			fImpulse = -fOtherSpeed;
			impulseLimit = adhesiveLimit*CTimer::GetTimeStep() / m_fMass;
			if(fImpulse < -impulseLimit) fImpulse = -impulseLimit;
			CVector vImpulse = frictionDir*fImpulse;
			m_vecMoveFriction += CVector(vImpulse.x, vImpulse.y, 0.0f);
			return true;
		}
	}else{
		CVector pointpos = colpoint.point - GetPosition();
		speed = GetSpeed(pointpos);
		normalSpeed = DotProduct(speed, colpoint.normal);
		vOtherSpeed = speed - colpoint.normal*normalSpeed;

		fOtherSpeed = vOtherSpeed.Magnitude();
		if(fOtherSpeed > 0.0f){
			frictionDir = vOtherSpeed * (1.0f/fOtherSpeed);
			fImpulse = -fOtherSpeed * m_fMass;
			impulseLimit = adhesiveLimit*CTimer::GetTimeStep() * 1.5f;
			if(fImpulse < -impulseLimit) fImpulse = -impulseLimit;
			ApplyFrictionMoveForce(frictionDir*fImpulse);
			ApplyFrictionTurnForce(frictionDir*fImpulse, pointpos);

			if(fOtherSpeed > 0.1f &&
			   colpoint.surfaceB != SURFACE_2 && colpoint.surfaceB != SURFACE_4 &&
			   CSurfaceTable::GetAdhesionGroup(colpoint.surfaceA) == ADHESIVE_HARD){
				CVector v = frictionDir * fOtherSpeed * 0.25f;
				for(int i = 0; i < 4; i++)
					CParticle::AddParticle(PARTICLE_SPARK_SMALL, colpoint.point, v);
			}
			return true;
		}
	}
	return false;
}


void
CPhysical::AddCollisionRecord(CEntity *ent)
{
	AddCollisionRecord_Treadable(ent);
	this->bHasCollided = true;
	ent->bHasCollided = true;
	if(IsVehicle() && ent->IsVehicle()){
		if(((CVehicle*)this)->m_nAlarmState == -1)
			((CVehicle*)this)->m_nAlarmState = 15000;
		if(((CVehicle*)ent)->m_nAlarmState == -1)
			((CVehicle*)ent)->m_nAlarmState = 15000;
	}
	if(bUseCollisionRecords){
		int i;
		for(i = 0; i < m_nCollisionRecords; i++)
			if(m_aCollisionRecords[i] == ent)
				return;
		if(m_nCollisionRecords < PHYSICAL_MAX_COLLISIONRECORDS)
			m_aCollisionRecords[m_nCollisionRecords++] = ent;
		m_nLastTimeCollided = CTimer::GetTimeInMilliseconds();
	}
}

void
CPhysical::AddCollisionRecord_Treadable(CEntity *ent)
{
	if(ent->IsBuilding() && ((CBuilding*)ent)->GetIsATreadable()){
		CTreadable *t = (CTreadable*)ent;
		if(t->m_nodeIndicesPeds[0] >= 0 ||
		   t->m_nodeIndicesPeds[1] >= 0 ||
		   t->m_nodeIndicesPeds[2] >= 0 ||
		   t->m_nodeIndicesPeds[3] >= 0)
			m_pedTreadable = t;
		if(t->m_nodeIndicesCars[0] >= 0 ||
		   t->m_nodeIndicesCars[1] >= 0 ||
		   t->m_nodeIndicesCars[2] >= 0 ||
		   t->m_nodeIndicesCars[3] >= 0)
			m_carTreadable = t;
	}
}

bool
CPhysical::GetHasCollidedWith(CEntity *ent)
{
	int i;
	if(bUseCollisionRecords)
		for(i = 0; i < m_nCollisionRecords; i++)
			if(m_aCollisionRecords[i] == ent)
				return true;
	return false;
}

void
CPhysical::ProcessControl(void)
{
	if(!IsPed())
		m_phy_flagA8 = false;
	bHasContacted = false;
	bIsInSafePosition = false;
	bWasPostponed = false;
	bHasHitWall = false;

	if(m_status == STATUS_SIMPLE)
		return;

	m_nCollisionRecords = 0;
	bHasCollided = false;
	m_nCollisionPieceType = 0;
	m_fCollisionImpulse = 0.0f;
	m_pCollidingEntity = nil;

	if(!bIsStuck){
		if(IsObject() ||
		   IsPed() && !bPedPhysics){
			m_vecMoveSpeedAvg = (m_vecMoveSpeedAvg + m_vecMoveSpeed)/2.0f;
			m_vecTurnSpeedAvg = (m_vecTurnSpeedAvg + m_vecTurnSpeed)/2.0f;
			float step = CTimer::GetTimeStep() * 0.003;
			if(m_vecMoveSpeedAvg.MagnitudeSqr() < step*step &&
			   m_vecTurnSpeedAvg.MagnitudeSqr() < step*step){
				m_nStaticFrames++;
				if(m_nStaticFrames > 10){
					m_nStaticFrames = 10;
					bIsStatic = true;
					m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
					m_vecTurnSpeed = CVector(0.0f, 0.0f, 0.0f);
					m_vecMoveFriction = m_vecMoveSpeed;
					m_vecTurnFriction = m_vecTurnSpeed;
					return;
				}
			}else 
				m_nStaticFrames = 0;
		}
	}
	ApplyGravity();
	ApplyFriction();
	ApplyAirResistance();
}

STARTPATCHES
	InjectHook(0x4951F0, &CPhysical::Add_, PATCH_JUMP);
	InjectHook(0x4954B0, &CPhysical::Remove_, PATCH_JUMP);
	InjectHook(0x495540, &CPhysical::RemoveAndAdd, PATCH_JUMP);
	InjectHook(0x495F10, &CPhysical::ProcessControl_, PATCH_JUMP);
	InjectHook(0x4958F0, &CPhysical::AddToMovingList, PATCH_JUMP);
	InjectHook(0x495940, &CPhysical::RemoveFromMovingList, PATCH_JUMP);

	InjectHook(0x497180, &CPhysical::AddCollisionRecord, PATCH_JUMP);
	InjectHook(0x4970C0, &CPhysical::AddCollisionRecord_Treadable, PATCH_JUMP);
	InjectHook(0x497240, &CPhysical::GetHasCollidedWith, PATCH_JUMP);

#define F3 float, float, float
	InjectHook(0x495B10, &CPhysical::ApplyMoveSpeed, PATCH_JUMP);
	InjectHook(0x497280, &CPhysical::ApplyTurnSpeed, PATCH_JUMP);
	InjectHook(0x4959A0, (void (CPhysical::*)(F3))&CPhysical::ApplyMoveForce, PATCH_JUMP);
	InjectHook(0x495A10, (void (CPhysical::*)(F3, F3))&CPhysical::ApplyTurnForce, PATCH_JUMP);
	InjectHook(0x495D90, (void (CPhysical::*)(F3))&CPhysical::ApplyFrictionMoveForce, PATCH_JUMP);
	InjectHook(0x495E10, (void (CPhysical::*)(F3, F3))&CPhysical::ApplyFrictionTurnForce, PATCH_JUMP);
	InjectHook(0x499890, &CPhysical::ApplySpringCollision, PATCH_JUMP);
	InjectHook(0x495B50, &CPhysical::ApplyGravity, PATCH_JUMP);
	InjectHook(0x495B80, (void (CPhysical::*)(void))&CPhysical::ApplyFriction, PATCH_JUMP);
	InjectHook(0x495C20, &CPhysical::ApplyAirResistance, PATCH_JUMP);

	InjectHook(0x4973A0, &CPhysical::ApplyCollision, PATCH_JUMP);
	InjectHook(0x4992A0, &CPhysical::ApplyCollisionAlt, PATCH_JUMP);
	InjectHook(0x499BE0, (bool (CPhysical::*)(float, CColPoint&))&CPhysical::ApplyFriction, PATCH_JUMP);
	InjectHook(0x49A180, (bool (CPhysical::*)(CPhysical*, float, CColPoint&))&CPhysical::ApplyFriction, PATCH_JUMP);
ENDPATCHES
