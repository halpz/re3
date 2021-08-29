#include "common.h"

#include "DMAudio.h"
#include "Entity.h"
#include "AudioCollision.h"
#include "AudioManager.h"
#include "AudioSamples.h"
#include "SurfaceTable.h"
#include "sampman.h"

void
cAudioManager::ReportCollision(CEntity *entity1, CEntity *entity2, uint8 surface1, uint8 surface2, float collisionPower,
                               float velocity)
{
	float distSquared;
	CVector v1;
	CVector v2;

	if(!m_bIsInitialised || m_nCollisionEntity < 0 || m_bIsPaused ||
	   (velocity < 0.0016f && collisionPower < 0.01f))
		return;

	if(entity1->IsBuilding()) {
		v1 = v2 = entity2->GetPosition();
	} else if(entity2->IsBuilding()) {
		v1 = v2 = entity1->GetPosition();
	} else {
		v1 = entity1->GetPosition();
		v2 = entity2->GetPosition();
	}
	CVector pos = (v1 + v2) * 0.5f;
	distSquared = GetDistanceSquared(pos);
	if(distSquared < SQR(COLLISION_MAX_DIST)) {
		m_sCollisionManager.m_sQueue.m_pEntity1 = entity1;
		m_sCollisionManager.m_sQueue.m_pEntity2 = entity2;
		m_sCollisionManager.m_sQueue.m_bSurface1 = surface1;
		m_sCollisionManager.m_sQueue.m_bSurface2 = surface2;
		m_sCollisionManager.m_sQueue.m_fIntensity1 = collisionPower;
		m_sCollisionManager.m_sQueue.m_fIntensity2 = velocity;
		m_sCollisionManager.m_sQueue.m_vecPosition = pos;
		m_sCollisionManager.m_sQueue.m_fDistance = distSquared;
		m_sCollisionManager.AddCollisionToRequestedQueue();
	}
}

void
cAudioCollisionManager::AddCollisionToRequestedQueue()
{
	uint32 collisionsIndex;
	uint32 i;


	if (m_bCollisionsInQueue < NUMAUDIOCOLLISIONS)
		collisionsIndex = m_bCollisionsInQueue++;
	else {
		collisionsIndex = m_bIndicesTable[NUMAUDIOCOLLISIONS - 1];
		if (m_sQueue.m_fDistance >= m_asCollisions1[collisionsIndex].m_fDistance) return;
	}

	m_asCollisions1[collisionsIndex] = m_sQueue;

	i = 0;
	if(collisionsIndex) {
		while(m_asCollisions1[m_bIndicesTable[i]].m_fDistance <= m_asCollisions1[collisionsIndex].m_fDistance) {
			if(++i >= collisionsIndex) {
				m_bIndicesTable[i] = collisionsIndex;
				return;
			}
		}
		memmove(&m_bIndicesTable[i + 1], &m_bIndicesTable[i], NUMAUDIOCOLLISIONS - 1 - i);
	}
	m_bIndicesTable[i] = collisionsIndex;
}

void
cAudioManager::ServiceCollisions()
{
	int i, j;
	bool8 abRepeatedCollision1[NUMAUDIOCOLLISIONS];
	bool8 abRepeatedCollision2[NUMAUDIOCOLLISIONS];

	m_sQueueSample.m_nEntityIndex = m_nCollisionEntity;

	for (int i = 0; i < NUMAUDIOCOLLISIONS; i++)
		abRepeatedCollision1[i] = abRepeatedCollision2[i] = FALSE;

	for (i = 0; i < m_sCollisionManager.m_bCollisionsInQueue; i++) {
		for (j = 0; j < NUMAUDIOCOLLISIONS; j++) {
			int index = m_sCollisionManager.m_bIndicesTable[i];
			if ((m_sCollisionManager.m_asCollisions1[index].m_pEntity1 == m_sCollisionManager.m_asCollisions2[j].m_pEntity1)
				&& (m_sCollisionManager.m_asCollisions1[index].m_pEntity2 == m_sCollisionManager.m_asCollisions2[j].m_pEntity2)
				&& (m_sCollisionManager.m_asCollisions1[index].m_bSurface1 == m_sCollisionManager.m_asCollisions2[j].m_bSurface1)
				&& (m_sCollisionManager.m_asCollisions1[index].m_bSurface2 == m_sCollisionManager.m_asCollisions2[j].m_bSurface2)
				) {
				abRepeatedCollision1[index] = TRUE;
				abRepeatedCollision2[j] = TRUE;
				m_sCollisionManager.m_asCollisions1[index].m_nBaseVolume = ++m_sCollisionManager.m_asCollisions2[j].m_nBaseVolume;
				SetUpLoopingCollisionSound(m_sCollisionManager.m_asCollisions1[index], j);
				break;
			}
		}
	}

	for (i = 0; i < NUMAUDIOCOLLISIONS; i++) {
		if (!abRepeatedCollision2[i]) {
			m_sCollisionManager.m_asCollisions2[i].m_pEntity1 = nil;
			m_sCollisionManager.m_asCollisions2[i].m_pEntity2 = nil;
			m_sCollisionManager.m_asCollisions2[i].m_bSurface1 = SURFACE_DEFAULT;
			m_sCollisionManager.m_asCollisions2[i].m_bSurface2 = SURFACE_DEFAULT;
			m_sCollisionManager.m_asCollisions2[i].m_fIntensity2 = 0.0f;
			m_sCollisionManager.m_asCollisions2[i].m_fIntensity1 = 0.0f;
			m_sCollisionManager.m_asCollisions2[i].m_vecPosition = CVector(0.0f, 0.0f, 0.0f);
			m_sCollisionManager.m_asCollisions2[i].m_fDistance = 0.0f;
		}
	}

	for (i = 0; i < m_sCollisionManager.m_bCollisionsInQueue; i++) {
		int index = m_sCollisionManager.m_bIndicesTable[i];
		if (!abRepeatedCollision1[index]) {
			for (j = 0; j < NUMAUDIOCOLLISIONS; j++) {
				if (!abRepeatedCollision2[j]) {
					m_sCollisionManager.m_asCollisions2[j].m_nBaseVolume = 1;
					m_sCollisionManager.m_asCollisions2[j].m_pEntity1 = m_sCollisionManager.m_asCollisions1[index].m_pEntity1;
					m_sCollisionManager.m_asCollisions2[j].m_pEntity2 = m_sCollisionManager.m_asCollisions1[index].m_pEntity2;
					m_sCollisionManager.m_asCollisions2[j].m_bSurface1 = m_sCollisionManager.m_asCollisions1[index].m_bSurface1;
					m_sCollisionManager.m_asCollisions2[j].m_bSurface2 = m_sCollisionManager.m_asCollisions1[index].m_bSurface2;
					break;
				}
			}
			SetUpOneShotCollisionSound(m_sCollisionManager.m_asCollisions1[index]);
			SetUpLoopingCollisionSound(m_sCollisionManager.m_asCollisions1[index], j);
		}
	}

	for (int i = 0; i < NUMAUDIOCOLLISIONS; i++)
		m_sCollisionManager.m_bIndicesTable[i] = NUMAUDIOCOLLISIONS;
	m_sCollisionManager.m_bCollisionsInQueue = 0;
}

static const uint32 gOneShotCol[] = {SFX_COL_TARMAC_1,
                                    SFX_COL_TARMAC_1,
                                    SFX_COL_GRASS_1,
                                    SFX_COL_GRAVEL_1,
                                    SFX_COL_MUD_1,
                                    SFX_COL_TARMAC_1,
                                    SFX_COL_CAR_1,
                                    SFX_COL_GRASS_1,
                                    SFX_COL_SCAFFOLD_POLE_1,
                                    SFX_COL_GARAGE_DOOR_1,
                                    SFX_COL_CAR_PANEL_1,
                                    SFX_COL_THICK_METAL_PLATE_1,
                                    SFX_COL_SCAFFOLD_POLE_1,
                                    SFX_COL_LAMP_POST_1,
                                    SFX_COL_HYDRANT_1,
                                    SFX_COL_HYDRANT_1,
                                    SFX_COL_METAL_CHAIN_FENCE_1,
                                    SFX_COL_PED_1,
                                    SFX_COL_SAND_1,
                                    SFX_SPLASH_1,
                                    SFX_COL_WOOD_CRATES_1,
                                    SFX_COL_WOOD_BENCH_1,
                                    SFX_COL_WOOD_SOLID_1,
                                    SFX_COL_GRASS_1,
                                    SFX_COL_GRASS_1,
                                    SFX_COL_VEG_1,
                                    SFX_COL_TARMAC_1,
                                    SFX_COL_CONTAINER_1,
                                    SFX_COL_NEWS_VENDOR_1,
                                    SFX_TYRE_BUMP,
                                    SFX_COL_CARDBOARD_1,
                                    SFX_COL_TARMAC_1,
                                    SFX_COL_GATE,
                                    SFX_COL_SAND_1,
                                    SFX_COL_TARMAC_1 };

void
cAudioManager::SetUpOneShotCollisionSound(const cAudioCollision &col)
{
	uint16 s1;
	uint16 s2;

	uint32 emittingVol;
	float ratio;

	static uint16 counter = 28;

	for(int32 i = 0; i < 2; i++) {
		if(i) {
			s1 = col.m_bSurface2;
			s2 = col.m_bSurface1;
		} else {
			s1 = col.m_bSurface1;
			s2 = col.m_bSurface2;
		}
		ratio = GetCollisionOneShotRatio(s1, col.m_fIntensity1);
		if(s1 == SURFACE_CAR && s2 == SURFACE_PED) ratio /= 4.0f;
		if(s1 == SURFACE_CAR && ratio < 0.6f) {
			s1 = SURFACE_CAR_PANEL;
			ratio = Min(1.f, 2.f * ratio);
		}
		emittingVol = 40 * ratio;
		if(emittingVol) {
			m_sQueueSample.m_fDistance = Sqrt(col.m_fDistance);
			m_sQueueSample.m_nVolume =
			    ComputeVolume(emittingVol, COLLISION_MAX_DIST, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nSampleIndex = gOneShotCol[s1];
				switch(m_sQueueSample.m_nSampleIndex) {
				case SFX_COL_TARMAC_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[3] % 5;
					break;
				case SFX_COL_CAR_PANEL_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[0] % 6;
					break;
				case SFX_COL_LAMP_POST_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[1] % 2;
					break;
				case SFX_COL_METAL_CHAIN_FENCE_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[3] % 4;
					break;
				case SFX_COL_PED_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[4] % 2;
					break;
				case SFX_COL_WOOD_CRATES_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[4] % 4;
					break;
				case SFX_COL_WOOD_BENCH_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[1] % 4;
					break;
				case SFX_COL_VEG_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[2] % 5;
					break;
				case SFX_COL_NEWS_VENDOR_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[2] % 3;
					break;
				case SFX_COL_CAR_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[1] % 5;
					break;
				case SFX_COL_CARDBOARD_1:
					m_sQueueSample.m_nSampleIndex += m_anRandomTable[3] % 2;
					break;
				default: break;
				}
				switch(s1) {
				case SURFACE_GLASS: m_sQueueSample.m_nFrequency = 13500; break;
				case SURFACE_GIRDER: m_sQueueSample.m_nFrequency = 8819; break;
				case SURFACE_WATER:
					m_sQueueSample.m_nFrequency =
					    2 * SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
					break;
				case SURFACE_RUBBER: m_sQueueSample.m_nFrequency = 6000; break;
				case SURFACE_PLASTIC: m_sQueueSample.m_nFrequency = 8000; break;
				default:
					m_sQueueSample.m_nFrequency =
					    SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
					break;
				}
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
				m_sQueueSample.m_nCounter = counter++;
				if(counter >= 255) counter = 28;
				m_sQueueSample.m_vecPos = col.m_vecPosition;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 11;
				m_sQueueSample.m_nLoopCount = 1;
				SET_EMITTING_VOLUME(emittingVol);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_fSpeedMultiplier = 4.0f;
				m_sQueueSample.m_MaxDistance = COLLISION_MAX_DIST;
				m_sQueueSample.m_bStatic = TRUE;
				SET_SOUND_REVERB(TRUE);
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
	}
}

void
cAudioManager::SetUpLoopingCollisionSound(const cAudioCollision &col, uint8 counter)
{
    bool8 distCalculated = FALSE;
	if(col.m_fIntensity2 > 0.0016f) {
		uint8 emittingVol = SetLoopingCollisionRequestedSfxFreqAndGetVol(col);
		if(emittingVol) {
			CalculateDistance(distCalculated, m_sQueueSample.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, COLLISION_MAX_DIST, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = counter;
				m_sQueueSample.m_vecPos = col.m_vecPosition;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 7;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(emittingVol);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 4.0f;
				m_sQueueSample.m_MaxDistance = COLLISION_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 5;
				SET_SOUND_REVERB(TRUE);
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
	}
}

uint32
cAudioManager::SetLoopingCollisionRequestedSfxFreqAndGetVol(const cAudioCollision &audioCollision)
{
	uint8 surface1 = audioCollision.m_bSurface1;
	uint8 surface2 = audioCollision.m_bSurface2;
	int32 vol;
	float ratio;

	if(surface1 == SURFACE_GRASS || surface2 == SURFACE_GRASS || surface1 == SURFACE_HEDGE ||
	   surface2 == SURFACE_HEDGE) {
		ratio = GetCollisionRatio(audioCollision.m_fIntensity2, 0.0001f, 0.09f, 0.0899f);
		m_sQueueSample.m_nSampleIndex = SFX_RAIN;
		m_sQueueSample.m_nFrequency = 13000.f * ratio + 35000;
		vol = 50.f * ratio;
	} else if(surface1 == SURFACE_WATER || surface2 == SURFACE_WATER) {
		ratio = GetCollisionRatio(audioCollision.m_fIntensity2, 0.0001f, 0.09f, 0.0899f);
		m_sQueueSample.m_nSampleIndex = SFX_BOAT_WATER_LOOP;
		m_sQueueSample.m_nFrequency = 6050.f * ratio + 16000;
		vol = 30.f * ratio;
	} else if(surface1 == SURFACE_GRAVEL || surface2 == SURFACE_GRAVEL || surface1 == SURFACE_MUD_DRY || surface2 == SURFACE_MUD_DRY ||
	          surface1 == SURFACE_SAND || surface2 == SURFACE_SAND || surface1 == SURFACE_SAND_BEACH || surface2 == SURFACE_SAND_BEACH) {
		ratio = GetCollisionRatio(audioCollision.m_fIntensity2, 0.0001f, 0.09f, 0.0899f);
		m_sQueueSample.m_nSampleIndex = SFX_GRAVEL_SKID;
		m_sQueueSample.m_nFrequency = 6000.f * ratio + 10000;
		vol = 50.f * ratio;
	} else if(surface1 == SURFACE_PED || surface2 == SURFACE_PED) {
		return 0;
	} else {
		ratio = GetCollisionRatio(audioCollision.m_fIntensity2, 0.0001f, 0.09f, 0.0899f);
		m_sQueueSample.m_nSampleIndex = SFX_SCRAPE_CAR_1;
		m_sQueueSample.m_nFrequency = 10000.f * ratio + 10000;
		vol = 40.f * ratio;
	}
	if(audioCollision.m_nBaseVolume < 2) vol = audioCollision.m_nBaseVolume * vol / 2;
	return vol;
}

float
cAudioManager::GetCollisionOneShotRatio(uint32 a, float b)
{
	switch(a) {
	case SURFACE_DEFAULT:
	case SURFACE_TARMAC:
	case SURFACE_PAVEMENT:
	case SURFACE_STEEP_CLIFF:
	case SURFACE_TRANSPARENT_STONE:
	case SURFACE_CONCRETE_BEACH: return GetCollisionRatio(b, 10.f, 60.f, 50.f);
	case SURFACE_GRASS:
	case SURFACE_GRAVEL:
	case SURFACE_MUD_DRY:
	case SURFACE_CARDBOARDBOX: return GetCollisionRatio(b, 0.f, 2.f, 2.f);
	case SURFACE_CAR: return GetCollisionRatio(b, 6.f, 50.f, 44.f);
	case SURFACE_GLASS:
	case SURFACE_METAL_CHAIN_FENCE: return GetCollisionRatio(b, 0.1f, 10.f, 9.9f);
	case SURFACE_TRANSPARENT_CLOTH:
	case SURFACE_THICK_METAL_PLATE: return GetCollisionRatio(b, 30.f, 130.f, 100.f);
	case SURFACE_GARAGE_DOOR: return GetCollisionRatio(b, 20.f, 100.f, 80.f);
	case SURFACE_CAR_PANEL: return GetCollisionRatio(b, 0.f, 4.f, 4.f);
	case SURFACE_SCAFFOLD_POLE:
	case SURFACE_METAL_GATE: 
	case SURFACE_LAMP_POST: return GetCollisionRatio(b, 1.f, 10.f, 9.f);
	case SURFACE_FIRE_HYDRANT: return GetCollisionRatio(b, 1.f, 15.f, 14.f);
	case SURFACE_GIRDER: return GetCollisionRatio(b, 8.f, 50.f, 42.f);
	case SURFACE_PED: return GetCollisionRatio(b, 0.f, 20.f, 20.f);
	case SURFACE_SAND:
	case SURFACE_WATER:
	case SURFACE_RUBBER:
	case SURFACE_WHEELBASE:
	case SURFACE_SAND_BEACH: return GetCollisionRatio(b, 0.f, 10.f, 10.f);
	case SURFACE_WOOD_CRATES: return GetCollisionRatio(b, 1.f, 4.f, 3.f);
	case SURFACE_WOOD_BENCH: return GetCollisionRatio(b, 0.1f, 5.f, 4.9f);
	case SURFACE_WOOD_SOLID: return GetCollisionRatio(b, 0.1f, 40.f, 39.9f);
	case SURFACE_PLASTIC: return GetCollisionRatio(b, 0.1f, 4.f, 3.9f);
	case SURFACE_HEDGE: return GetCollisionRatio(b, 0.f, 0.5f, 0.5f);
	case SURFACE_CONTAINER: return GetCollisionRatio(b, 4.f, 40.f, 36.f);
	case SURFACE_NEWS_VENDOR: return GetCollisionRatio(b, 0.f, 5.f, 5.f);
	default: break;
	}

	return 0.f;
}

float
cAudioManager::GetCollisionLoopingRatio(uint32 a, uint32 b, float c)
{
	return GetCollisionRatio(c, 0.0f, 0.02f, 0.02f);
}

float
cAudioManager::GetCollisionRatio(float a, float b, float c, float d)
{
	float e;
	e = a;
	if(a <= b) return 0.0f;
	if(c <= a) e = c;
	return (e - b) / d;
}
