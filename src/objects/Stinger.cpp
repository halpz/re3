#include "common.h"
#include "Stinger.h"
#include "CopPed.h"
#include "ModelIndices.h"
#include "RpAnimBlend.h"
#include "World.h"
#include "Automobile.h"
#include "Bike.h"
#include "Particle.h"
#include "AnimBlendAssociation.h"
#include "General.h"

uint32 NumOfStingerSegments;

/* --  CStingerSegment  -- */

CStingerSegment::CStingerSegment()
{
	m_fMass = 1.0f;
	m_fTurnMass = 1.0f;
	m_fAirResistance = 0.99999f;
	m_fElasticity = 0.75f;
	m_fBuoyancy = GRAVITY * m_fMass * 0.1f;
	bExplosionProof = true;
	SetModelIndex(MI_PLC_STINGER);
	ObjectCreatedBy = CONTROLLED_SUB_OBJECT;
	NumOfStingerSegments++;
}

CStingerSegment::~CStingerSegment()
{
	NumOfStingerSegments--;
}

/* --  CStinger  -- */

CStinger::CStinger()
{
	bIsDeployed = false;
}

void
CStinger::Init(CPed *pPed)
{
	int32 i;

	pOwner = pPed;
	for (i = 0; i < NUM_STINGER_SEGMENTS; i++) {
		pSpikes[i] = new CStingerSegment();
#ifdef FIX_BUGS
		if (!pSpikes[i]) {
			// Abort!! Pool is full
			Remove();
			return;
		}
#endif
		pSpikes[i]->bUsesCollision = false;
	}
	bIsDeployed = true;
	m_vPos = pPed->GetPosition();
	m_vPos.z -= 1.0f;
	m_fMax_Z = Atan2(-pPed->GetForward().x, pPed->GetForward().y) + HALFPI;

	for (i = 0; i < NUM_STINGER_SEGMENTS; i++) {
		pSpikes[i]->SetOrientation(0.0f, 0.0f, Atan2(-pPed->GetForward().x, pPed->GetForward().y));
		pSpikes[i]->SetPosition(m_vPos);
	}

	CVector2D fwd2d(pPed->GetForward().x, pPed->GetForward().y);

	for (i = 0; i < ARRAY_SIZE(m_vPositions); i++)
		m_vPositions[i] = fwd2d * 1.8f * Sin(DEGTORAD(i));

	m_nSpikeState = STINGERSTATE_NONE;
	m_nTimeOfDeploy = CTimer::GetTimeInMilliseconds();
}

void
CStinger::Remove()
{
	if (!bIsDeployed) return;

	for (int32 i = 0; i < NUM_STINGER_SEGMENTS; i++) {
		CStingerSegment *spikeSegment = pSpikes[i];

#ifdef FIX_BUGS
		if (spikeSegment) {
			CWorld::Remove(spikeSegment);
			delete spikeSegment;
			pSpikes[i] = nil;
		}
#else
		if (spikeSegment->m_entryInfoList.first != nil)
			spikeSegment->bRemoveFromWorld = true;
		else
			delete spikeSegment;
#endif
	}
	bIsDeployed = false;
}

void
CStinger::Deploy(CPed *pPed)
{
	// So total number of stingers allowed at the same time is 2, each by different CCopPed.
	if (NumOfStingerSegments < NUM_STINGER_SEGMENTS*2 && !pPed->bInVehicle && pPed->IsPedInControl()) {
		if (!bIsDeployed && RpAnimBlendClumpGetAssociation(pPed->GetClump(), ANIM_STD_THROW_UNDER) == nil) {
			Init(pPed);
#ifdef FIX_BUGS
			// Above call won't set it to true no more when object pool is full
			if (!bIsDeployed)
				return;
#endif
			pPed->SetPedState(PED_DEPLOY_STINGER);
			CAnimManager::AddAnimation(pPed->GetClump(), ASSOCGRP_STD, ANIM_STD_THROW_UNDER);
		}
	}
}

void
CStinger::CheckForBurstTyres()
{
	CVector firstPos = pSpikes[0]->GetPosition();
	firstPos.z += 0.2f;
	CVector lastPos = pSpikes[NUM_STINGER_SEGMENTS - 1]->GetPosition();
	lastPos.z += 0.2f;
	float dist = (lastPos - firstPos).Magnitude();
	if (dist < 0.1f) return;

	CVehicle *vehsInRange[16];
	int16 numObjects;
	CEntity entity;

	CWorld::FindObjectsInRange((lastPos + firstPos) / 2.0f,
		dist, true, &numObjects, 15, (CEntity**)vehsInRange,
		false, true, false, false, false);

	for (int32 i = 0; i < numObjects; i++) {
		CAutomobile *pAutomobile = nil;
		CBike *pBike = nil;

		if (vehsInRange[i]->IsCar())
			pAutomobile = (CAutomobile*)vehsInRange[i];
		else if (vehsInRange[i]->IsBike())
			pBike = (CBike*)vehsInRange[i];

		if (pAutomobile == nil && pBike == nil) continue;
		
		float maxWheelDistToSpike = sq(((CVehicleModelInfo*)CModelInfo::GetModelInfo(vehsInRange[i]->GetModelIndex()))->m_wheelScale + 0.1f);

		for (int wheelId = 0; wheelId < 4; wheelId++) {
			if ((pAutomobile != nil && pAutomobile->m_aSuspensionSpringRatioPrev[wheelId] < 1.0f) ||
				(pBike != nil && pBike->m_aSuspensionSpringRatioPrev[wheelId] < 1.0f)) {
				CVector vecWheelPos;
				if (pAutomobile != nil)
					vecWheelPos = pAutomobile->m_aWheelColPoints[wheelId].point;
				else if (pBike != nil)
					vecWheelPos = pBike->m_aWheelColPoints[wheelId].point;

				for (int32 spike = 0; spike < NUM_STINGER_SEGMENTS; spike++) {
					if ((pSpikes[spike]->GetPosition() - vecWheelPos).Magnitude() < maxWheelDistToSpike) {
						if (pBike) {
							if (wheelId < 2)
								vehsInRange[i]->BurstTyre(CAR_PIECE_WHEEL_LF, true);
							else
								vehsInRange[i]->BurstTyre(CAR_PIECE_WHEEL_LR, true);
						}
						else {
							switch (wheelId) {
							case 0: vehsInRange[i]->BurstTyre(CAR_PIECE_WHEEL_LF, true); break;
							case 1: vehsInRange[i]->BurstTyre(CAR_PIECE_WHEEL_LR, true); break;
							case 2: vehsInRange[i]->BurstTyre(CAR_PIECE_WHEEL_RF, true); break;
							case 3: vehsInRange[i]->BurstTyre(CAR_PIECE_WHEEL_RR, true); break;
							}
						}
						vecWheelPos.z += 0.15f;
						for (int j = 0; j < 4; j++)
							CParticle::AddParticle(PARTICLE_BULLETHIT_SMOKE, vecWheelPos, vehsInRange[i]->GetRight() * 0.1f);
					}
				}
			}
		}
	}
}

// Only called when bIsDeployed
void
CStinger::Process()
{
	switch (m_nSpikeState)
	{
	case STINGERSTATE_NONE:
		if (pOwner != nil
			&& !pOwner->bInVehicle
			&& pOwner->GetPedState() == PED_DEPLOY_STINGER
			&& RpAnimBlendClumpGetAssociation(pOwner->GetClump(), ANIM_STD_THROW_UNDER)->currentTime > 0.39f)
		{
			m_nSpikeState = STINGERSTATE_DEPLOYING;
			for (int i = 0; i < NUM_STINGER_SEGMENTS; i++)
				CWorld::Add(pSpikes[i]);
			pOwner->SetIdle();
		}
		break;
	case STINGERSTATE_DEPLOYED:
		if (pOwner != nil && pOwner->m_nPedType == PEDTYPE_COP)
			((CCopPed*)pOwner)->m_bThrowsSpikeTrap = false;
		break;
	case STINGERSTATE_UNDEPLOYING:
		if (CTimer::GetTimeInMilliseconds() > m_nTimeOfDeploy + 2500)
			m_nSpikeState = STINGERSTATE_REMOVE;
		// no break
	case STINGERSTATE_DEPLOYING:
		if (m_nSpikeState == STINGERSTATE_DEPLOYING && CTimer::GetTimeInMilliseconds() > m_nTimeOfDeploy + 2500)
			m_nSpikeState = STINGERSTATE_DEPLOYED;
		else {
			float progress = (CTimer::GetTimeInMilliseconds() - m_nTimeOfDeploy) / 2500.0f;
			if (m_nSpikeState != STINGERSTATE_DEPLOYING)
				progress = 1.0f - progress;

			float degangle = progress * ARRAY_SIZE(m_vPositions);
			float angle1 = m_fMax_Z + DEGTORAD(degangle);
			float angle2 = m_fMax_Z - DEGTORAD(degangle);
			int pos = Clamp(degangle, 0, ARRAY_SIZE(m_vPositions)-1);

			CVector2D pos2d = m_vPositions[pos];
			CVector pos3d = m_vPos;
			CColPoint colPoint;
			CEntity *pEntity;
			if (CWorld::ProcessVerticalLine(CVector(pos3d.x, pos3d.y, pos3d.z - 10.0f), pos3d.z, colPoint, pEntity, true, false, false, false, true, false, nil))
				pos3d.z = colPoint.point.z + 0.15f;

			angle1 = CGeneral::LimitRadianAngle(angle1);
			angle2 = CGeneral::LimitRadianAngle(angle2);

			for (int spike = 0; spike < NUM_STINGER_SEGMENTS; spike++) {
				if (CWorld::TestSphereAgainstWorld(pos3d + CVector(pos2d.x, pos2d.y, 0.6f), 0.3f, nil, true, false, false, true, false, false))
					pos2d = CVector2D(0.0f, 0.0f);

				if (spike % 2 == 0) {
					pSpikes[spike]->SetOrientation(0.0f, 0.0f, angle1);
					pos3d.x += pos2d.x;
					pos3d.y += pos2d.y;
				} else {
					pSpikes[spike]->SetOrientation(0.0f, 0.0f, angle2);
				}
				pSpikes[spike]->SetPosition(pos3d);
			}
		}
		break;
	case STINGERSTATE_REMOVE:
		Remove();
#ifdef FIX_BUGS
		return;
#else
		break;
#endif
	}
	CheckForBurstTyres();
}