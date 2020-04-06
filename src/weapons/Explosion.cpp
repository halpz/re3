#include "common.h"
#include "patcher.h"
#include "DMAudio.h"
#include "Explosion.h"

CExplosion(&gaExplosion)[48] = *(CExplosion(*)[48])*(uintptr*)0x64E208;

WRAPPER void CExplosion::AddExplosion(CEntity *explodingEntity, CEntity *culprit, eExplosionType type, const CVector &pos, uint32) { EAXJMP(0x5591C0); }

int AudioHandle = AEHANDLE_NONE;

void
CExplosion::Initialise()
{
	debug("Initialising CExplosion...\n");
	for (int i = 0; i < ARRAY_SIZE(gaExplosion); i++) {
		gaExplosion[i].m_ExplosionType = EXPLOSION_GRENADE;
		gaExplosion[i].m_vecPosition.x = 0.0f;
		gaExplosion[i].m_vecPosition.y = 0.0f;
		gaExplosion[i].m_vecPosition.z = 0.0f;
		gaExplosion[i].m_fRadius = 1.0f;
		gaExplosion[i].m_fPropagationRate = 0.0f;
		gaExplosion[i].field_38 = 0;
		gaExplosion[i].m_pCreatorEntity = nil;
		gaExplosion[i].m_pVictimEntity = nil;
		gaExplosion[i].m_fStopTime = 0.0f;
		gaExplosion[i].m_bActive = false;
		gaExplosion[i].m_nStartTime = 0;
		gaExplosion[i].field_34 = 0;
	}
	AudioHandle = DMAudio.CreateEntity(AUDIOTYPE_EXPLOSION, (void*)1);
	if (AudioHandle >= 0)
		DMAudio.SetEntityStatus(AudioHandle, 1);
	debug("CExplosion ready\n");
}

void CExplosion::Shutdown()
{
	debug("Shutting down CExplosion...\n");
	if (AudioHandle >= 0) {
		DMAudio.DestroyEntity(AudioHandle);
		AudioHandle = AEHANDLE_NONE;
	}
	debug("CExplosion shut down\n");
}

void
CExplosion::RemoveAllExplosionsInArea(CVector pos, float radius)
{
	for (int i = 0; i < ARRAY_SIZE(gaExplosion); i++) {
		if (gaExplosion[i].m_bActive) {
			if ((pos - gaExplosion[i].m_vecPosition).MagnitudeSqr() < SQR(radius))
				gaExplosion[i].m_bActive = false;
		}
	}
}

int8
CExplosion::GetExplosionActiveCounter(uint8 id)
{
	return gaExplosion[id].m_bActiveCounter;
}

CVector *
CExplosion::GetExplosionPosition(uint8 id)
{
	return &gaExplosion[id].m_vecPosition;
}

uint8
CExplosion::GetExplosionType(uint8 id)
{
	return gaExplosion[id].m_ExplosionType;
}

void
CExplosion::ResetExplosionActiveCounter(uint8 id)
{
	gaExplosion[id].m_bActiveCounter = 0;
}

bool
CExplosion::TestForExplosionInArea(eExplosionType a1, float x1, float x2, float y1, float y2, float z1, float z2)
{
	for (int i = 0; i < ARRAY_SIZE(gaExplosion); i++) {
		if (gaExplosion[i].m_bActive) {
			if (a1 == gaExplosion[i].m_ExplosionType) {
				if (gaExplosion[i].m_vecPosition.x >= x1 && gaExplosion[i].m_vecPosition.x <= x2) {
					if (gaExplosion[i].m_vecPosition.y >= y1 && gaExplosion[i].m_vecPosition.y <= y2) {
						if (gaExplosion[i].m_vecPosition.z >= z1 && gaExplosion[i].m_vecPosition.z <= z2)
							return true;
					}
				}
			}
		}
	}
	return false;
}

STARTPATCHES
	InjectHook(0x559030, &CExplosion::Initialise, PATCH_JUMP);
	InjectHook(0x559100, &CExplosion::Shutdown, PATCH_JUMP);
	InjectHook(0x55AD40, &CExplosion::RemoveAllExplosionsInArea, PATCH_JUMP);
	InjectHook(0x559140, &CExplosion::GetExplosionActiveCounter, PATCH_JUMP);
	InjectHook(0x5591A0, &CExplosion::GetExplosionPosition, PATCH_JUMP);
	InjectHook(0x559180, &CExplosion::GetExplosionType, PATCH_JUMP);
	InjectHook(0x559160, &CExplosion::ResetExplosionActiveCounter, PATCH_JUMP);
	InjectHook(0x55AC80, &CExplosion::TestForExplosionInArea, PATCH_JUMP);
ENDPATCHES