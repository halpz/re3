#include "common.h"
#include "patcher.h"
#include "Cranes.h"

#include "Camera.h"
#include "DMAudio.h"
#include "Entity.h"
#include "ModelIndices.h"
#include "Replay.h"
#include "Object.h"
#include "World.h"

#define MAX_DISTANCE_TO_FIND_CRANE (10.0f)
#define CRANE_UPDATE_RADIUS (300.0f)
#define CRANE_MOVEMENT_PROCESSING_RADIUS (150.0f)
#define CRUSHER_Z (-0.951f)
#define MILITARY_Z (10.7862f)

void CCranes::InitCranes(void) 
{
	CarsCollectedMilitaryCrane = 0;
	NumCranes = 0;
	for (int i = 0; i < NUMSECTORS_X; i++) {
		for (int j = 0; j < NUMSECTORS_Y; j++) {
			for (CPtrNode* pNode = CWorld::GetSector(i, j)->m_lists[ENTITYLIST_BUILDINGS].first; pNode; pNode = pNode->next) {
				CEntity* pEntity = (CEntity*)pNode->item;
				if (MODELID_CRANE_1 == pEntity->GetModelIndex() ||
					MODELID_CRANE_2 == pEntity->GetModelIndex() ||
					MODELID_CRANE_3 == pEntity->GetModelIndex())
					AddThisOneCrane(pEntity);
			}
		}
	}
	for (CPtrNode* pNode = CWorld::GetBigBuildingList(LEVEL_INDUSTRIAL).first; pNode; pNode->next) {
		CEntity* pEntity = (CEntity*)pNode->item;
		if (MODELID_CRANE_1 == pEntity->GetModelIndex() ||
			MODELID_CRANE_2 == pEntity->GetModelIndex() ||
			MODELID_CRANE_3 == pEntity->GetModelIndex())
			AddThisOneCrane(pEntity);
	}
}

void CCranes::AddThisOneCrane(CEntity* pEntity)
{
	pEntity->GetMatrix().ResetOrientation();
	if (NumCranes >= NUM_CRANES)
		return;
	CCrane* pCrane = &aCranes[NumCranes];
	pCrane->Init();
	pCrane->m_pObject = pEntity;
	pCrane->m_bCraneStatus = CCrane::NONE;
	pCrane->m_fHeight = NumCranes; // lol wtf
	while (pCrane->m_fHeight > TWOPI)
		pCrane->m_fHeight -= TWOPI;
	pCrane->m_fHookOffset = 20.0f;
	pCrane->m_fHookHeight = 20.0f;
	pCrane->m_nUpdateTimer = 0;
	pCrane->m_bCraneState = CCrane::IDLE;
	pCrane->m_bWasMilitaryCrane = 0;
	pCrane->m_nAudioEntity = DMAudio.CreateEntity(AUDIOTYPE_CRANE, &aCranes[NumCranes]);
	if (pCrane->m_nAudioEntity >= 0)
		DMAudio.SetEntityStatus(pCrane->m_nAudioEntity, 1);
	pCrane->m_bIsTop = (MODELID_CRANE_1 != pEntity->GetModelIndex());
	// W T F ? ? ?
	// Is this used to avoid military crane?
	if (pCrane->m_bIsTop || pEntity->GetPosition().y > 0.0f) {
		CObject* pMagnet = new CObject(MI_MAGNET, false);
		pMagnet->ObjectCreatedBy = MISSION_OBJECT;
		pMagnet->bUsesCollision = false;
		pMagnet->bExplosionProof = true;
		pMagnet->bAffectedByGravity = false;
		pCrane->m_pMagnet = pMagnet;
		pCrane->CalcHookCoordinates(&pCrane->m_vecHookCurPos.x, &pCrane->m_vecHookCurPos.y, &pCrane->m_vecHookCurPos.z);
		pCrane->SetHookMatrix();
	}
	else
		pCrane->m_pMagnet = nil;
	NumCranes++;
}

void CCranes::ActivateCrane(float fInfX, float fSupX, float fInfY, float fSupY, float fDropOffX, float fDropOffY, float fDropOffZ, float fHeading, bool bIsCrusher, bool bIsMilitary, float fPosX, float fPosY)
{
	float fMinDistance = 99999.9f;
	float X = fPosX, Y = fPosY;
	if (X <= -10000.0f || Y <= -10000.0f) {
		X = fDropOffX;
		Y = fDropOffY;
	}
	int index = 0;
	for (int i = 0; i < NumCranes; i++) {
		float distance = (CVector2D(X, Y) - aCranes[i].m_pObject->GetPosition()).Magnitude();
		if (distance < fMinDistance && distance < MAX_DISTANCE_TO_FIND_CRANE) {
			fMinDistance = distance;
			index = i;
		}
	}
#ifdef FIX_BUGS // classic
	if (fMinDistance == 99999.9f)
		return;
#endif
	CCrane* pCrane = &aCranes[NumCranes];
	pCrane->m_fPickupX1 = fInfX;
	pCrane->m_fPickupX2 = fSupX;
	pCrane->m_fPickupY1 = fInfY;
	pCrane->m_fPickupY2 = fSupY;
	pCrane->m_vecDropoffTarget.x = fDropOffX;
	pCrane->m_vecDropoffTarget.y = fDropOffY;
	pCrane->m_vecDropoffTarget.z = fDropOffZ;
	pCrane->m_bCraneStatus = CCrane::ACTIVATED;
	pCrane->m_pVehiclePickedUp = nil;
	pCrane->m_bVehiclesCollected = 0;
	pCrane->m_bIsCrusher = bIsCrusher;
	pCrane->m_bIsMilitaryCrane = bIsMilitary;
	bool military = true;
	if (!bIsMilitary && !pCrane->m_bWasMilitaryCrane)
		military = false;
	pCrane->m_bWasMilitaryCrane = military;
	pCrane->m_nUpdateTimer = 0;
	pCrane->m_bCraneState = CCrane::IDLE;
	float Z;
	if (bIsCrusher)
		Z = CRUSHER_Z;
	else if (bIsMilitary)
		Z = MILITARY_Z;
	else
		Z = CWorld::FindGroundZForCoord((fInfX + fSupY) / 2, (fInfY + fSupY) / 2);
	pCrane->FindParametersForTarget((fInfX + fSupY) / 2, (fInfY + fSupY) / 2, Z, &pCrane->m_fPickupAngle, &pCrane->m_fPickupDistance, &pCrane->m_fAngle);
	pCrane->FindParametersForTarget(fDropOffX, fDropOffY, fDropOffZ, &pCrane->m_fDropoffAngle, &pCrane->m_fDropoffDistance, &pCrane->m_fDistance);
}

void CCranes::DeActivateCrane(float X, float Y)
{
	float fMinDistance = 99999.9f;
	int index = 0;
	for (int i = 0; i < NumCranes; i++) {
		float distance = (CVector2D(X, Y) - aCranes[i].m_pObject->GetPosition()).Magnitude();
		if (distance < fMinDistance && distance < MAX_DISTANCE_TO_FIND_CRANE) {
			fMinDistance = distance;
			index = i;
		}
	}
#ifdef FIX_BUGS // classic
	if (fMinDistance == 99999.9f)
		return;
#endif
	aCranes[index].m_bCraneStatus = CCrane::DEACTIVATED;
	aCranes[index].m_bCraneState = CCrane::IDLE;
}

bool CCranes::IsThisCarPickedUp(float X, float Y, CVehicle* pVehicle)
{
	int index = 0;
	bool result = false;
	for (int i = 0; i < NumCranes; i++) {
		float distance = (CVector2D(X, Y) - aCranes[i].m_pObject->GetPosition()).Magnitude();
		if (distance < MAX_DISTANCE_TO_FIND_CRANE && aCranes[i].m_pVehiclePickedUp == pVehicle) {
			if (aCranes[i].m_bCraneStatus == CCrane::LIFTING_TARGET || aCranes[i].m_bCraneStatus == CCrane::ROTATING_TARGET)
				result = true;
		}
	}
	return true;
}

void CCranes::UpdateCranes(void)
{
	for (int i = 0; i < NumCranes; i++) {
		if (aCranes[i].m_bIsTop || aCranes[i].m_bIsCrusher ||
			(TheCamera.GetPosition().x + CRANE_UPDATE_RADIUS > aCranes[i].m_pObject->GetPosition().x &&
				TheCamera.GetPosition().x - CRANE_UPDATE_RADIUS < aCranes[i].m_pObject->GetPosition().x &&
				TheCamera.GetPosition().y + CRANE_UPDATE_RADIUS > aCranes[i].m_pObject->GetPosition().y &&
				TheCamera.GetPosition().y + CRANE_UPDATE_RADIUS < aCranes[i].m_pObject->GetPosition().y))
			aCranes[i].Update();
	}
}

void CCrane::Update(void)
{
	if (CReplay::IsPlayingBack())
		return;
	if ((m_bCraneStatus == ACTIVATED || m_bCraneStatus == DEACTIVATED) &&
		Abs(TheCamera.GetGameCamPosition().x - m_pObject->GetPosition().x) < CRANE_MOVEMENT_PROCESSING_RADIUS &&
		Abs(TheCamera.GetGameCamPosition().y - m_pObject->GetPosition().y) < CRANE_MOVEMENT_PROCESSING_RADIUS) {
		switch (m_bCraneState) {
		case IDLE:
			if (GoTowardsTarget(m_fPickupAngle, m_fPickupDistance, 4.0f + m_fAngle + m_bIsCrusher ? 4.5f : 0.0f, 1.0f) &&
				CTimer::GetTimeInMilliseconds() > m_nUpdateTimer) {
				CWorld::AdvanceCurrentScanCode();
#ifdef FIX_BUGS
				int xstart = max(0, CWorld::GetSectorIndexX(m_fPickupX1));
				int xend = min(NUMSECTORS_X - 1, CWorld::GetSectorIndexX(m_fPickupX2));
				int ystart = max(0, CWorld::GetSectorIndexY(m_fPickupY1));
				int yend = min(NUMSECTORS_Y - 1, CWorld::GetSectorIndexY(m_fPickupY2));
#else
				int xstart = CWorld::GetSectorIndexX(m_fPickupX1);
				int xend = CWorld::GetSectorIndexX(m_fPickupX2);
				int ystart = CWorld::GetSectorIndexY(m_fPickupY1);
				int yend = CWorld::GetSectorIndexY(m_fPickupY1);
#endif
				assert(xstart <= xend);
				assert(ystart <= yend);
				for (int i = xstart; i <= xend; i++) {
					for (int j = ystart; j <= yend; j++) {
						FindCarInSectorList(&CWorld::GetSector(i, j)->m_lists[ENTITYLIST_VEHICLES]);
						FindCarInSectorList(&CWorld::GetSector(i, j)->m_lists[ENTITYLIST_VEHICLES_OVERLAP]);
					}
				}
			}
			break;
		case GOING_TOWARDS_TARGET:
			if (!m_pVehiclePickedUp) {
				m_bCraneState = IDLE;
				break;
			}
			if (m_pVehiclePickedUp->GetPosition().x < m_fPickupX1 ||
				m_pVehiclePickedUp->GetPosition().x > m_fPickupX2 ||
				m_pVehiclePickedUp->GetPosition().y > m_fPickupY1 ||
				m_pVehiclePickedUp->GetPosition().y > m_fPickupY2 ||
				m_pVehiclePickedUp->pDriver ||
				Abs(m_pVehiclePickedUp->GetMoveSpeed().x) > 0.01f ||
				Abs(m_pVehiclePickedUp->GetMoveSpeed().y) > 0.01f ||
				Abs(m_pVehiclePickedUp->GetMoveSpeed().z) > 0.01f ||
				FindPlayerPed()->GetPedState() == PED_ENTER_CAR &&
				FindPlayerPed()->m_pSeekTarget == m_pVehiclePickedUp) {
				m_pVehiclePickedUp = nil;
				m_bCraneState = IDLE;
				break;
			}
			
		}
	}
}

WRAPPER bool CCranes::IsThisCarBeingTargettedByAnyCrane(CVehicle*) { EAXJMP(0x5451E0); }
WRAPPER bool CCranes::IsThisCarBeingCarriedByAnyCrane(CVehicle*) { EAXJMP(0x545190); }
WRAPPER bool CCranes::HaveAllCarsBeenCollectedByMilitaryCrane() { EAXJMP(0x544BE0); }


WRAPPER void CCranes::Save(uint8*, uint32*) { EAXJMP(0x545210); }
WRAPPER void CranesLoad(uint8*, uint32) { EAXJMP(0x5454d0); }
