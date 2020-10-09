#include "WaterCreatures.h"
#include "ModelIndices.h"
#include "World.h"
#include "WaterLevel.h"
#include "Camera.h"
#include "PlayerPed.h"
#include "config.h"
#include "General.h"

int CWaterCreatures::nNumActiveSeaLifeForms;
CWaterCreature CWaterCreatures::aWaterCreatures[NUM_WATER_CREATURES];

struct WaterCreatureProperties aProperties[65] = {
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_JELLYFISH,	0.01f, 2.2f, 0.0005f, 3.5f },
	{ &MI_JELLYFISH01,	0.01f, 2.2f, 0.0005f, 3.5f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_TURTLE,		0.01f, 2.0f, 0.0005f, 4.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_DOLPHIN,		0.03f, 1.5f, 0.0005f, 4.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_SHARK,		0.03f, 0.4f, 0.0005f, 4.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH1SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH2SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH2S,		0.04f, 1.5f, 0.0008f, 3.0f },
	{ &MI_FISH3SINGLE,	0.04f, 3.0f, 0.0008f, 3.0f },
	{ &MI_FISH3S,		0.04f, 1.5f, 0.0008f, 3.0f },
};

CWaterCreature::CWaterCreature() {
	Free();
}

CWaterCreature::~CWaterCreature() {
	//looks like unused
}

void CWaterCreature::Initialise(CObject *pObj, float fRightMult, float fZTurnSpeed, float fWaterDepth, uint32 alpha, eFishSlotState state) {
	this->m_pObj = pObj;
	this->m_fRightMult = fRightMult;
	this->m_fZTurnSpeed = fZTurnSpeed;
	this->m_fWaterDepth = fWaterDepth;
	this->m_alpha = alpha;
	this->m_state = state;
}

void CWaterCreature::Allocate(CObject *pObj, float fRightMult, float fZTurnSpeed, float fWaterDepth, uint32 alpha, eFishSlotState state) {
	CWaterCreature::Initialise(pObj, fRightMult, fZTurnSpeed, fWaterDepth, alpha, state);
}

void CWaterCreature::Free() {
	CWaterCreature::Initialise(nil, 0.0f, 0.0f, 0.0f, 0, WATER_CREATURE_DISABLED);
}

CWaterCreature *CWaterCreatures::GetFishStructSlot() {
	for (int i = 0; i < NUM_WATER_CREATURES; i++)
		if (aWaterCreatures[i].m_state == WATER_CREATURE_DISABLED)
			return &aWaterCreatures[i];
	
	return nil;
}

CObject *CWaterCreatures::CreateSeaLifeForm(CVector const& pos, int16 modelID, int32 zRotAngle) {
	if (CObject::nNoTempObjects >= 40)
		return nil;

	CObject *pObj = new CObject(modelID, true);

	if (!pObj) return nil;
	
	pObj->GetMatrix().GetPosition() = pos;
	pObj->GetMatrix().UpdateRW();
	pObj->m_vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
	pObj->m_vecTurnSpeed = CVector(0.0f, 0.0f, 0.0f);
	pObj->GetMatrix().SetRotateZOnly(DEGTORAD(zRotAngle));
	pObj->GetMatrix().UpdateRW();
	pObj->ObjectCreatedBy = CONTROLLED_SUB_OBJECT;
	pObj->bIsStatic = false;

	if (pObj->ObjectCreatedBy == TEMP_OBJECT) {
		CObject::nNoTempObjects++;
		pObj->m_nEndOfLifeTime = CTimer::GetTimeInMilliseconds() + 60000;
	}

	pObj->bTouchingWater = true;
	pObj->bUnderwater = true;
	CWorld::Add(pObj);

	return pObj;
}

bool CWaterCreatures::IsSpaceForMoreWaterCreatures() {
	return nNumActiveSeaLifeForms < NUM_WATER_CREATURES;
}

float CWaterCreatures::CalculateFishHeading(CVector const& pos1, CVector const& pos2) {
	CVector delta = pos1 - pos2;
	delta.Normalise();

	return Atan2(-delta.x, delta.y);
}

void CWaterCreatures::CreateOne(CVector const& pos, int32 modelID) {
	if (!IsSpaceForMoreWaterCreatures())
		return;

	CVector storedPos = pos;
	float fDepth, fLevelNoWaves;
	if (!TheCamera.IsSphereVisible(storedPos, 3.0f)
		&& CWaterLevel::GetWaterDepth(storedPos, &fDepth, &fLevelNoWaves, nil) && fDepth > 4.5f) {
		
		if (modelID == -1 || modelID < 0 || modelID > 64)
			modelID = CGeneral::GetRandomNumberInRange(0, 64);

		WaterCreatureProperties *creature = &aProperties[modelID];
		storedPos.z = fLevelNoWaves - creature->fLevel;
		float fRightMult = CGeneral::GetRandomNumberInRange(0.0f, creature->fRightMult) + 0.01f;
		float angle = CWaterCreatures::CalculateFishHeading(FindPlayerPed()->GetPosition(), storedPos);
		
		CObject *fish = CreateSeaLifeForm(storedPos, *(int16*)creature->modelID, angle);
		if (!fish) return;

		fish->SetRwObjectAlpha(255); 
		CWaterCreature *wc = GetFishStructSlot();
		wc->Allocate(fish, fRightMult, 0.0f, creature->fWaterDepth, 255, WATER_CREATURE_ALLOCATED);
		nNumActiveSeaLifeForms++;
	}
}

void CWaterCreatures::FreeFishStructSlot(CWaterCreature *wc) {
	wc->Free();
}

void CWaterCreatures::UpdateAll() {
	if (nNumActiveSeaLifeForms == 0)
		return;

	CVector playerPos = FindPlayerPed()->GetPosition();
	for (int i = 0; i < NUM_WATER_CREATURES; i++) {
		switch (aWaterCreatures[i].m_state) {
		case WATER_CREATURE_ACTIVE: 
			aWaterCreatures[i].m_pObj->m_nEndOfLifeTime = CTimer::GetTimeInMilliseconds() + 40000;
			if (!aWaterCreatures[i].m_pObj->GetIsOnScreen()) {
				aWaterCreatures[i].m_pObj->SetRwObjectAlpha(0);
				aWaterCreatures[i].m_state = WATER_CREATURE_TO_REMOVE;
				break;
			}
		case WATER_CREATURE_ALLOCATED: {
			if ((playerPos - aWaterCreatures[i].m_pObj->GetPosition()).Magnitude() < SQR(75.0f)) {
				if (aWaterCreatures[i].m_alpha < 255)
					aWaterCreatures[i].m_alpha = Min(aWaterCreatures[i].m_alpha + 4, 255);
				aWaterCreatures[i].m_pObj->SetRwObjectAlpha(aWaterCreatures[i].m_alpha);
				CVector newRight = aWaterCreatures[i].m_pObj->GetRight();
				newRight.Normalise();
				aWaterCreatures[i].m_pObj->m_vecMoveSpeed = newRight * aWaterCreatures[i].m_fRightMult;
				aWaterCreatures[i].m_pObj->m_vecTurnSpeed = CVector(0.0f, 0.0f, aWaterCreatures[i].m_fZTurnSpeed);
				aWaterCreatures[i].m_pObj->bIsStatic = false;
				float fDepth = 0.0;
				CWaterLevel::GetWaterDepth(aWaterCreatures[i].m_pObj->GetPosition(), &fDepth, nil, nil);
				if (aWaterCreatures[i].m_fWaterDepth < fDepth) {
					if (aWaterCreatures[i].m_pObj->m_nEndOfLifeTime - 40000 <= CTimer::GetTimeInMilliseconds())
						aWaterCreatures[i].m_state = WATER_CREATURE_ACTIVE;
				}
				else {
					aWaterCreatures[i].m_state = WATER_CREATURE_UPDATE;
				}

			}
			else {
				aWaterCreatures[i].m_state = WATER_CREATURE_TO_REMOVE;
			}
			break;
		}
		case WATER_CREATURE_UPDATE: {
			aWaterCreatures[i].m_pObj->m_nEndOfLifeTime = CTimer::GetTimeInMilliseconds() + 40000;
			if (aWaterCreatures[i].m_alpha <= 0) {
				aWaterCreatures[i].m_state = WATER_CREATURE_TO_REMOVE;
			}
			else {
				aWaterCreatures[i].m_alpha = Max(aWaterCreatures[i].m_alpha - 6, 0);
				aWaterCreatures[i].m_pObj->SetRwObjectAlpha(aWaterCreatures[i].m_alpha);
				CVector newRight = aWaterCreatures[i].m_pObj->GetRight();
				newRight.Normalise();
				newRight.x *= aWaterCreatures[i].m_fRightMult;
				newRight.y *= aWaterCreatures[i].m_fRightMult;
				newRight.z -= 0.015f;
				aWaterCreatures[i].m_pObj->m_vecMoveSpeed = newRight;

				if (!aWaterCreatures[i].m_pObj->GetIsOnScreen())
					aWaterCreatures[i].m_state = WATER_CREATURE_TO_REMOVE;
			}
			break;
		}
		case WATER_CREATURE_TO_REMOVE: 
			if (aWaterCreatures[i].m_pObj)
				CWorld::Remove(aWaterCreatures[i].m_pObj);
			FreeFishStructSlot(&aWaterCreatures[i]);
			nNumActiveSeaLifeForms--;
			aWaterCreatures[i].m_state = WATER_CREATURE_DISABLED;
			break;
		default:
			break;
		}
	}
}

void CWaterCreatures::RemoveAll() {
	for (int i = 0; i < NUM_WATER_CREATURES; i++) {
		if (aWaterCreatures[i].m_state != WATER_CREATURE_DISABLED) {
			CWorld::Remove(aWaterCreatures[i].m_pObj);
			FreeFishStructSlot(&aWaterCreatures[i]);
			aWaterCreatures[i].m_state = WATER_CREATURE_DISABLED;
			nNumActiveSeaLifeForms--;
		}
	}
}