#include "common.h"

#include "AudioManager.h"
#include "audio_enums.h"

#include "AudioScriptObject.h"
#include "MusicManager.h"
#include "Timer.h"
#include "DMAudio.h"
#include "sampman.h"
#include "Camera.h"
#include "World.h"
#include "ZoneCull.h"

cAudioManager AudioManager;

#define SPEED_OF_SOUND 343.f
#define TIME_SPENT 40

cAudioManager::cAudioManager()
{
	m_bIsInitialised = FALSE;
	m_bIsSurround = TRUE;
	m_nChannelOffset = 0;
	m_fSpeedOfSound = SPEED_OF_SOUND / TIME_SPENT;
	m_nTimeSpent = TIME_SPENT;
	m_nActiveSamples = NUM_CHANNELS_GENERIC;
	m_nActiveQueue = 1;
	ClearRequestedQueue();
	m_nActiveQueue = 0;
	ClearRequestedQueue();
	ClearActiveSamples();
	GenerateIntegerRandomNumberTable();
	m_bDoubleVolume = FALSE;
#ifdef AUDIO_REFLECTIONS
	m_bDynamicAcousticModelingStatus = TRUE;
#endif

	for (uint32 i = 0; i < NUM_AUDIOENTITIES; i++) {
		m_asAudioEntities[i].m_bIsUsed = FALSE;
		m_aAudioEntityOrderList[i] = NUM_AUDIOENTITIES;
	}
	m_nAudioEntitiesCount = 0;
	m_FrameCounter = 0;
	m_bReduceReleasingPriority = FALSE;
	m_bTimerJustReset = FALSE;
	m_nTimer = 0;
}

cAudioManager::~cAudioManager()
{
	if (m_bIsInitialised)
		Terminate();
}

void
cAudioManager::Initialise()
{
	if (!m_bIsInitialised) {
		PreInitialiseGameSpecificSetup();
		m_bIsInitialised = SampleManager.Initialise();
		if (m_bIsInitialised) {
#ifdef EXTERNAL_3D_SOUND
			m_nActiveSamples = SampleManager.GetMaximumSupportedChannels();
			if (m_nActiveSamples <= 1) {
				Terminate();
			} else {
				m_nActiveSamples--;
#else
			{
				m_nActiveSamples = NUM_CHANNELS_GENERIC;
#endif
				PostInitialiseGameSpecificSetup();
				InitialisePoliceRadioZones();
				InitialisePoliceRadio();
				MusicManager.Initialise();
			}
		}
	}
}

void
cAudioManager::Terminate()
{
	if (m_bIsInitialised) {
		MusicManager.Terminate();

		for (uint32 i = 0; i < NUM_AUDIOENTITIES; i++) {
			m_asAudioEntities[i].m_bIsUsed = FALSE;
			m_aAudioEntityOrderList[i] = ARRAY_SIZE(m_aAudioEntityOrderList);
		}

		m_nAudioEntitiesCount = 0;
		m_sAudioScriptObjectManager.m_nScriptObjectEntityTotal = 0;
		PreTerminateGameSpecificShutdown();

		for (uint32 i = 0; i < MAX_SFX_BANKS; i++) {
			if (SampleManager.IsSampleBankLoaded(i))
				SampleManager.UnloadSampleBank(i);
		}

		SampleManager.Terminate();

		m_bIsInitialised = FALSE;
		PostTerminateGameSpecificShutdown();
	}
}

void
cAudioManager::Service()
{
	GenerateIntegerRandomNumberTable();
	if (m_bTimerJustReset) {
		ResetAudioLogicTimers(m_nTimer);
		MusicManager.ResetTimers(m_nTimer);
		m_bTimerJustReset = FALSE;
	}
	if (m_bIsInitialised) {
		m_bWasPaused = m_bIsPaused;
		m_bIsPaused = CTimer::GetIsUserPaused();
#ifdef AUDIO_REFLECTIONS
		UpdateReflections();
#endif
		ServiceSoundEffects();
		MusicManager.Service();
	}
}

int32
cAudioManager::CreateEntity(eAudioType type, void *entity)
{
	if (!m_bIsInitialised)
		return AEHANDLE_ERROR_NOAUDIOSYS;
	if (!entity)
		return AEHANDLE_ERROR_NOENTITY;
	if (type >= TOTAL_AUDIO_TYPES)
		return AEHANDLE_ERROR_BADAUDIOTYPE;

#ifdef FIX_BUGS
	// since sound could still play after entity deletion let's make sure we don't override one that is in use
	// find all the free entity IDs that are being used by queued samples
	int32 stillUsedEntities[NUM_CHANNELS_GENERIC * NUM_SOUND_QUEUES];
	uint32 stillUsedEntitiesCount = 0;

	for (uint8 i = 0; i < NUM_SOUND_QUEUES; i++)
		for (uint8 j = 0; j < m_nRequestedCount[i]; j++) {
			tSound &sound = m_aRequestedQueue[i][m_aRequestedOrderList[i][j]];
			if (sound.m_nEntityIndex < 0) continue;
			if (!m_asAudioEntities[sound.m_nEntityIndex].m_bIsUsed) {
				bool found = false;
				for (uint8 k = 0; k < stillUsedEntitiesCount; k++) {
					if (stillUsedEntities[k] == sound.m_nEntityIndex) {
						found = true;
						break;
					}
				}
				if (!found)
					stillUsedEntities[stillUsedEntitiesCount++] = sound.m_nEntityIndex;
			}
		}
#endif

	for (uint32 i = 0; i < NUM_AUDIOENTITIES; i++) {
		if (!m_asAudioEntities[i].m_bIsUsed) {
#ifdef FIX_BUGS
			// skip if ID is still used by queued sample
			bool skip = false;
			for (uint8 j = 0; j < stillUsedEntitiesCount; j++) {
				if (stillUsedEntities[j] == i) {
					//debug("audio entity %i still used, skipping\n", i);
					skip = true;
					break;
				}
			}
			if (skip)
				continue;
#endif

			m_asAudioEntities[i].m_bIsUsed = TRUE;
			m_asAudioEntities[i].m_bStatus = FALSE;
			m_asAudioEntities[i].m_nType = type;
			m_asAudioEntities[i].m_pEntity = entity;
			m_asAudioEntities[i].m_awAudioEvent[0] = SOUND_NO_SOUND;
			m_asAudioEntities[i].m_awAudioEvent[1] = SOUND_NO_SOUND;
			m_asAudioEntities[i].m_awAudioEvent[2] = SOUND_NO_SOUND;
			m_asAudioEntities[i].m_awAudioEvent[3] = SOUND_NO_SOUND;
			m_asAudioEntities[i].m_AudioEvents = 0;
			m_aAudioEntityOrderList[m_nAudioEntitiesCount++] = i;
			return i;
		}
	}
	return AEHANDLE_ERROR_NOFREESLOT;
}

void
cAudioManager::DestroyEntity(int32 id)
{
	if (m_bIsInitialised && id >= 0 && id < NUM_AUDIOENTITIES && m_asAudioEntities[id].m_bIsUsed) {
		m_asAudioEntities[id].m_bIsUsed = FALSE;
		for (uint32 i = 0; i < m_nAudioEntitiesCount; ++i) {
			if (id == m_aAudioEntityOrderList[i]) {
				if (i < NUM_AUDIOENTITIES - 1)
					memmove(&m_aAudioEntityOrderList[i], &m_aAudioEntityOrderList[i + 1], sizeof(uint32) * (m_nAudioEntitiesCount - (i + 1)));
				m_aAudioEntityOrderList[--m_nAudioEntitiesCount] = NUM_AUDIOENTITIES;
				return;
			}
		}
	}
}

bool8
cAudioManager::GetEntityStatus(int32 id)
{
	if (m_bIsInitialised && id >= 0 && id < NUM_AUDIOENTITIES && m_asAudioEntities[id].m_bIsUsed)
		return m_asAudioEntities[id].m_bStatus;
	return FALSE;
}

void
cAudioManager::SetEntityStatus(int32 id, bool8 status)
{
	if (m_bIsInitialised && id >= 0 && id < NUM_AUDIOENTITIES && m_asAudioEntities[id].m_bIsUsed)
		m_asAudioEntities[id].m_bStatus = status;
}

void *
cAudioManager::GetEntityPointer(int32 id)
{
	if (m_bIsInitialised && id >= 0 && id < NUM_AUDIOENTITIES && m_asAudioEntities[id].m_bIsUsed)
		return m_asAudioEntities[id].m_pEntity;
	return NULL;
}

static Const uint8 OneShotPriority[] = {
										3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 4, 2, 5, 5, 3, 5, 2, 2, 1, 1, 3, 1, 3, 3, 1, 1, 1, 1, 4, 4, 4, 3, 1, 1, 1, 1, 1,
										1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 3, 4, 2, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 3, 1, 1, 1, 9, 0, 0, 0, 1, 2, 2, 0, 0, 2, 3, 3, 3, 5, 1, 1,
										1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 7, 1, 4, 3, 4, 2, 2, 2, 3, 1, 2, 1, 3, 5, 3, 4, 6, 4, 6, 3, 0, 0, 0, 0, 0,
										0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 3, 3, 1, 0
										};

void
cAudioManager::PlayOneShot(int32 index, uint16 sound, float vol)
{

	if (m_bIsInitialised) {
		if (index >= 0 && index < NUM_AUDIOENTITIES) {
			tAudioEntity &entity = m_asAudioEntities[index];
			if (entity.m_bIsUsed) {
				if (sound < SOUND_TOTAL_SOUNDS) {
					if (entity.m_nType == AUDIOTYPE_SCRIPTOBJECT) {
						if (m_sAudioScriptObjectManager.m_nScriptObjectEntityTotal < ARRAY_SIZE(m_sAudioScriptObjectManager.m_anScriptObjectEntityIndices)) {
							entity.m_awAudioEvent[0] = sound;
							entity.m_AudioEvents = 1;
							m_sAudioScriptObjectManager.m_anScriptObjectEntityIndices[m_sAudioScriptObjectManager.m_nScriptObjectEntityTotal++] = index;
						}
					} else {
						int32 i = 0;
						while (TRUE) {
							if (i >= entity.m_AudioEvents) {
								if (entity.m_AudioEvents < NUM_AUDIOENTITY_EVENTS) {
									entity.m_awAudioEvent[i] = sound;
									entity.m_afVolume[i] = vol;
									entity.m_AudioEvents++;
								}
								return;
							}
							if (OneShotPriority[entity.m_awAudioEvent[i]] > OneShotPriority[sound])
								break;
							i++;
						}
						if (i < NUM_AUDIOENTITY_EVENTS - 1) {
							memmove(&entity.m_awAudioEvent[i + 1], &entity.m_awAudioEvent[i], (NUM_AUDIOENTITY_EVENTS - 1 - i) * sizeof(int16));
							memmove(&entity.m_afVolume[i + 1], &entity.m_afVolume[i], (NUM_AUDIOENTITY_EVENTS - 1 - i) * sizeof(float));
						}
						entity.m_awAudioEvent[i] = sound;
						entity.m_afVolume[i] = vol;
						if (entity.m_AudioEvents < NUM_AUDIOENTITY_EVENTS)
							entity.m_AudioEvents++;
					}
				}
			}
		}
	}
}

void
cAudioManager::SetEffectsMasterVolume(uint8 volume)
{
	SampleManager.SetEffectsMasterVolume(volume);
}

void
cAudioManager::SetMusicMasterVolume(uint8 volume)
{
	SampleManager.SetMusicMasterVolume(volume);
}

void
cAudioManager::SetMP3BoostVolume(uint8 volume)
{
	SampleManager.SetMP3BoostVolume(volume);
}

void
cAudioManager::SetEffectsFadeVol(uint8 volume)
{
	SampleManager.SetEffectsFadeVolume(volume);
}

void
cAudioManager::SetMusicFadeVol(uint8 volume)
{
	SampleManager.SetMusicFadeVolume(volume);
}

void
cAudioManager::SetOutputMode(bool8 surround)
{
	// on ps2 this calls another method of cAudioManager to set DTS mode on or off
}

void
cAudioManager::ResetTimers(uint32 time)
{
	if (m_bIsInitialised) {
		m_bTimerJustReset = TRUE;
		m_nTimer = time;
		ClearRequestedQueue();
		if (m_nActiveQueue) {
			m_nActiveQueue = 0;
			ClearRequestedQueue();
			m_nActiveQueue = 1;
		} else {
			m_nActiveQueue = 1;
			ClearRequestedQueue();
			m_nActiveQueue = 0;
		}
		ClearActiveSamples();
		ClearMissionAudio(0);
		ClearMissionAudio(1);
		SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
		SampleManager.SetEffectsFadeVolume(0);
		SampleManager.SetMusicFadeVolume(0);
		MusicManager.ResetMusicAfterReload();
		m_bIsPlayerShutUp = FALSE;
#ifdef AUDIO_OAL
		SampleManager.Service();
#endif
	}
}

void
cAudioManager::DestroyAllGameCreatedEntities()
{
	cAudioScriptObject *entity;

	if (m_bIsInitialised) {
		for (uint32 i = 0; i < NUM_AUDIOENTITIES; i++) {
			if (m_asAudioEntities[i].m_bIsUsed) {
				switch (m_asAudioEntities[i].m_nType) {
				case AUDIOTYPE_PHYSICAL:
				case AUDIOTYPE_EXPLOSION:
				case AUDIOTYPE_WEATHER:
				//case AUDIOTYPE_CRANE:
				case AUDIOTYPE_GARAGE:
				case AUDIOTYPE_FIREHYDRANT:
					DestroyEntity(i);
					break;
				case AUDIOTYPE_SCRIPTOBJECT:
					entity = (cAudioScriptObject *)m_asAudioEntities[i].m_pEntity;
					if (entity) {
						delete entity;
						m_asAudioEntities[i].m_pEntity = nil;
					}
					DestroyEntity(i);
					break;
				default:
					break;
				}
			}
		}
		m_sAudioScriptObjectManager.m_nScriptObjectEntityTotal = 0;
	}
}

#ifdef GTA_PC

uint8
cAudioManager::GetNum3DProvidersAvailable()
{
#ifdef EXTERNAL_3D_SOUND
	if (m_bIsInitialised)
		return SampleManager.GetNum3DProvidersAvailable();
#endif
	return 0;
}

char *
cAudioManager::Get3DProviderName(uint8 id)
{
#ifndef EXTERNAL_3D_SOUND
	return nil;
#else
	if (!m_bIsInitialised)
		return nil;
#ifdef AUDIO_OAL
	id = Clamp(id, 0, SampleManager.GetNum3DProvidersAvailable() - 1);
#else
	// We don't want that either since it will crash the game, but skipping for now
	if (id >= SampleManager.GetNum3DProvidersAvailable())
		return nil;
#endif
	return SampleManager.Get3DProviderName(id);
#endif
}

int8
cAudioManager::GetCurrent3DProviderIndex()
{
#ifdef EXTERNAL_3D_SOUND
	if (m_bIsInitialised)
		return SampleManager.GetCurrent3DProviderIndex();
#endif

	return -1;
}

int8
cAudioManager::AutoDetect3DProviders()
{
#ifdef EXTERNAL_3D_SOUND
	if (m_bIsInitialised)
		return SampleManager.AutoDetect3DProviders();
#endif

	return -1;
}

int8
cAudioManager::SetCurrent3DProvider(uint8 which)
{
#ifndef EXTERNAL_3D_SOUND
	return -1;
#else
	if (!m_bIsInitialised)
		return -1;
	for (uint8 i = 0; i < m_nActiveSamples + 1; i++)
		SampleManager.StopChannel(i);
	ClearRequestedQueue();
	if (m_nActiveQueue == 0)
		m_nActiveQueue = 1;
	else
		m_nActiveQueue = 0;
	ClearRequestedQueue();
	ClearActiveSamples();
	int8 current = SampleManager.SetCurrent3DProvider(which);
	if (current > 0) {
		m_nActiveSamples = SampleManager.GetMaximumSupportedChannels();
		if (m_nActiveSamples > 1)
			m_nActiveSamples--;
	}
	return current;
#endif
}

void
cAudioManager::SetSpeakerConfig(int32 conf)
{
#ifdef EXTERNAL_3D_SOUND
	SampleManager.SetSpeakerConfig(conf);
#endif
}

bool8
cAudioManager::IsMP3RadioChannelAvailable()
{
	if (m_bIsInitialised)
		return SampleManager.IsMP3RadioChannelAvailable();

	return FALSE;
}

void
cAudioManager::ReleaseDigitalHandle()
{
	if (m_bIsInitialised)
		SampleManager.ReleaseDigitalHandle();
}

void
cAudioManager::ReacquireDigitalHandle()
{
	if (m_bIsInitialised)
		SampleManager.ReacquireDigitalHandle();
}

#ifdef AUDIO_REFLECTIONS
void
cAudioManager::SetDynamicAcousticModelingStatus(bool8 status)
{
	m_bDynamicAcousticModelingStatus = status;
}
#endif

bool8
cAudioManager::CheckForAnAudioFileOnCD()
{
	return SampleManager.CheckForAnAudioFileOnCD();
}

char
cAudioManager::GetCDAudioDriveLetter()
{
	if (m_bIsInitialised)
		return SampleManager.GetCDAudioDriveLetter();
	return '\0';
}

bool8
cAudioManager::IsAudioInitialised()
{
	return m_bIsInitialised;
}

#endif // GTA_PC

void
cAudioManager::ServiceSoundEffects()
{
#ifdef FIX_BUGS
	if(CTimer::GetLogicalFramesPassed() != 0)
#endif
	m_bReduceReleasingPriority = (m_FrameCounter++ % 5) == 0;
	if (m_bIsPaused && !m_bWasPaused) {
#ifdef GTA_PS2
		if (m_bIsSurround) {
			for (uint32 i = 0; i < NUM_CHANNELS_DTS_GENERIC; i++)
				SampleManager.StopChannel(i);

			SampleManager.SetChannelFrequency(CHANNEL_DTS_POLICE_RADIO, 0);
			SampleManager.SetChannelFrequency(CHANNEL_DTS_MISSION_AUDIO_1, 0);
			SampleManager.SetChannelFrequency(CHANNEL_DTS_MISSION_AUDIO_2, 0);
			SampleManager.SetChannelFrequency(CHANNEL_DTS_PLAYER_VEHICLE_ENGINE, 0);
		} else {
			for (uint32 i = 0; i < NUM_CHANNELS_GENERIC; i++)
				SampleManager.StopChannel(i);

			SampleManager.SetChannelFrequency(CHANNEL_POLICE_RADIO, 0);
			SampleManager.SetChannelFrequency(CHANNEL_MISSION_AUDIO_1, 0);
			SampleManager.SetChannelFrequency(CHANNEL_MISSION_AUDIO_2, 0);
			SampleManager.SetChannelFrequency(CHANNEL_PLAYER_VEHICLE_ENGINE, 0);
		}
#else
		for (uint32 i = 0; i < NUM_CHANNELS; i++)
			SampleManager.StopChannel(i);
#endif
		ClearRequestedQueue();
		if (m_nActiveQueue) {
			m_nActiveQueue = 0;
			ClearRequestedQueue();
			m_nActiveQueue = 1;
		} else {
			m_nActiveQueue = 1;
			ClearRequestedQueue();
			m_nActiveQueue = 0;
		}
		ClearActiveSamples();
	}
	m_nActiveQueue = m_nActiveQueue == 1 ? 0 : 1;
#ifdef AUDIO_REVERB
	if(m_bIsSurround) ProcessReverb();
#endif
	ProcessSpecial();
	ClearRequestedQueue();
	InterrogateAudioEntities();
	m_sPedComments.Process();
	ServicePoliceRadio();
	ServiceCollisions();
	AddReleasingSounds();
	ProcessMissionAudio();
#ifdef EXTERNAL_3D_SOUND
	AdjustSamplesVolume();
#endif
	ProcessActiveQueues();
#ifdef AUDIO_OAL
	SampleManager.Service();
#endif
	for (int32 i = 0; i < m_sAudioScriptObjectManager.m_nScriptObjectEntityTotal; i++) {
		cAudioScriptObject *object = (cAudioScriptObject *)m_asAudioEntities[m_sAudioScriptObjectManager.m_anScriptObjectEntityIndices[i]].m_pEntity;
		delete object;
		m_asAudioEntities[m_sAudioScriptObjectManager.m_anScriptObjectEntityIndices[i]].m_pEntity = nil;
		DestroyEntity(m_sAudioScriptObjectManager.m_anScriptObjectEntityIndices[i]);
	}
	m_sAudioScriptObjectManager.m_nScriptObjectEntityTotal = 0;
}

uint8
cAudioManager::ComputeVolume(uint8 emittingVolume, float maxDistance, float distance)
{
	float minDistance;
	uint8 newEmittingVolume;

	if (maxDistance <= 0.0f)
		return 0;

	minDistance = maxDistance / 5.0f;
	if (minDistance > distance)
		return emittingVolume;

	newEmittingVolume = emittingVolume * SQR((maxDistance - minDistance - (distance - minDistance))
		/ (maxDistance - minDistance));
	return Min(127, newEmittingVolume);
}

void
cAudioManager::TranslateEntity(Const CVector *in, CVector *out)
{
	*out = MultiplyInverse(TheCamera.GetMatrix(), *in);
}

Const static uint8 PanTable[64] = { 0,  3,  8, 12, 16, 19, 22, 24, 26, 28, 30, 31, 33, 34, 36, 37, 39, 40, 41, 42, 44, 45, 46, 47, 48, 49, 49, 50, 51, 52, 53, 53,
								   54, 55, 55, 56, 56, 57, 57, 58, 58, 58, 59, 59, 59, 60, 60, 61, 61, 61, 61, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63};

int32
cAudioManager::ComputeFrontRearMix(float dist, CVector *vec)
{
	int32 index = vec->y / (dist / 64.0f);
	index = Min(63, ABS(index));

	if (vec->y > 0.0f)
		return Max(0, 63 - (int8)PanTable[index]);
	return Min(127, PanTable[index] + 63);
}

int32
cAudioManager::ComputePan(float dist, CVector *vec)
{
	int32 index = vec->x / (dist / 64.0f);
	index = Min(63, ABS(index));

	if (vec->x > 0.0f)
		return Max(20, 63 - (int8)PanTable[index]);
	return Min(107, PanTable[index] + 63);
}

uint32
cAudioManager::ComputeDopplerEffectedFrequency(uint32 oldFreq, float position1, float position2, float speedMultiplier)
{
	uint32 newFreq = oldFreq;
	if (!TheCamera.Get_Just_Switched_Status() && speedMultiplier != 0.0f) {
		float dist = position2 - position1;
		if (dist != 0.0f) {
			float speedOfSource = (dist / m_nTimeSpent) * speedMultiplier;
			if (m_fSpeedOfSound > Abs(speedOfSource)) {
				speedOfSource = Clamp2(speedOfSource, 0.0f, 1.5f);
				newFreq = (oldFreq * m_fSpeedOfSound) / (speedOfSource + m_fSpeedOfSound);
			}
		}
	}
	return newFreq;
}

int32
cAudioManager::RandomDisplacement(uint32 seed)
{
	int32 value;

	static bool8 bPos = TRUE;
	static uint32 Adjustment = 0;

	if (seed == 0)
		return 0;

	value = m_anRandomTable[(Adjustment + seed) % 5] % seed;
	Adjustment += value;

	if (value % 2)
		bPos = !bPos;

	if (!bPos)
		value = -value;
	return value;
}

void
cAudioManager::InterrogateAudioEntities()
{
	for (uint32 i = 0; i < m_nAudioEntitiesCount; i++) {
		ProcessEntity(m_aAudioEntityOrderList[i]);
		m_asAudioEntities[m_aAudioEntityOrderList[i]].m_AudioEvents = 0;
	}
}

void
cAudioManager::AddSampleToRequestedQueue()
{
	uint32 finalPriority;
	uint8 sampleIndex;
#ifdef AUDIO_REFLECTIONS
	bool8 bReflections;
#endif

	if (m_sQueueSample.m_nSampleIndex < TOTAL_AUDIO_SAMPLES) {
		finalPriority = m_sQueueSample.m_nPriority * (MAX_VOLUME - m_sQueueSample.m_nVolume);
		sampleIndex = m_nRequestedCount[m_nActiveQueue];
		if (sampleIndex >= m_nActiveSamples) {
			sampleIndex = m_aRequestedOrderList[m_nActiveQueue][m_nActiveSamples - 1];
			if (m_aRequestedQueue[m_nActiveQueue][sampleIndex].m_nFinalPriority <= finalPriority)
				return;
		} else
			m_nRequestedCount[m_nActiveQueue]++;
		m_sQueueSample.m_nFinalPriority = finalPriority;
		m_sQueueSample.m_bIsPlayingFinished = FALSE;
#ifdef AUDIO_REFLECTIONS
		if (m_sQueueSample.m_bIs2D || CCullZones::InRoomForAudio()) {
			m_sQueueSample.m_bReflections = FALSE;
			m_sQueueSample.m_nReflectionDelay = 0;
		}
		if (m_bDynamicAcousticModelingStatus && m_sQueueSample.m_nLoopCount > 0) {
			bReflections = m_sQueueSample.m_bReflections;
		} else {
			bReflections = FALSE;
			m_sQueueSample.m_nReflectionDelay = 0;
		}
		m_sQueueSample.m_bReflections = FALSE;

		if ( m_bIsSurround && m_sQueueSample.m_bIs2D )
			m_sQueueSample.m_nFrontRearPan = 30;
#ifdef AUDIO_REVERB
		if (!m_bDynamicAcousticModelingStatus)
			m_sQueueSample.m_bReverb = FALSE;
#endif
#endif

		m_aRequestedQueue[m_nActiveQueue][sampleIndex] = m_sQueueSample;

		AddDetailsToRequestedOrderList(sampleIndex);
#ifdef AUDIO_REFLECTIONS
		if (bReflections)
			AddReflectionsToRequestedQueue();
#endif
	}
}

void
cAudioManager::AddDetailsToRequestedOrderList(uint8 sample)
{
	uint32 i = 0;
	if (sample > 0) {
		for (; i < sample; i++) {
			if (m_aRequestedQueue[m_nActiveQueue][m_aRequestedOrderList[m_nActiveQueue][i]].m_nFinalPriority >
			    m_aRequestedQueue[m_nActiveQueue][sample].m_nFinalPriority)
				break;
		}
		if (i < sample) 
			memmove(&m_aRequestedOrderList[m_nActiveQueue][i + 1], &m_aRequestedOrderList[m_nActiveQueue][i], m_nActiveSamples - i - 1);
	}
	m_aRequestedOrderList[m_nActiveQueue][i] = sample;
}

#ifdef AUDIO_REFLECTIONS
void
cAudioManager::AddReflectionsToRequestedQueue()
{
#ifdef FIX_BUGS
  	uint32 oldFreq = 0;
#else
  	uint32 oldFreq;
#endif
	float reflectionDistance;
	int32 noise;
	uint8 emittingVolume;

	uint32 oldCounter = m_sQueueSample.m_nCounter;
	float oldDist = m_sQueueSample.m_fDistance;
	CVector oldPos = m_sQueueSample.m_vecPos;
#ifndef USE_TIME_SCALE_FOR_AUDIO
	if ( CTimer::GetIsSlowMotionActive() ) {
		emittingVolume = m_sQueueSample.m_nVolume;
		oldFreq = m_sQueueSample.m_nFrequency;
	} else
#endif
		emittingVolume = (9 * m_sQueueSample.m_nVolume) >> 4;
	m_sQueueSample.m_MaxDistance /= 2.0f;

	uint32 halfOldFreq = oldFreq >> 1;

	for (uint32 i = 0; i < ARRAY_SIZE(m_afReflectionsDistances); i++) {
#ifndef USE_TIME_SCALE_FOR_AUDIO
		if ( CTimer::GetIsSlowMotionActive() )
			m_afReflectionsDistances[i] = (m_anRandomTable[i % 4] % 3) * 100.0f / 8.0f;
#endif

		reflectionDistance = m_afReflectionsDistances[i];
		if (reflectionDistance > 0.0f && reflectionDistance < 100.0f && reflectionDistance < m_sQueueSample.m_MaxDistance) {
#ifndef USE_TIME_SCALE_FOR_AUDIO
			m_sQueueSample.m_nReflectionDelay = CTimer::GetIsSlowMotionActive() ? (reflectionDistance * 800.0f / 1029.0f) : (reflectionDistance * 500.0f / 1029.0f);
#else
			m_sQueueSample.m_nReflectionDelay = reflectionDistance * 500.0f / 1029.0f;
#endif
			if (m_sQueueSample.m_nReflectionDelay > 3) {
				m_sQueueSample.m_fDistance = m_afReflectionsDistances[i];
				SET_EMITTING_VOLUME(emittingVolume);
				m_sQueueSample.m_nVolume = ComputeVolume(emittingVolume, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);

				if (m_sQueueSample.m_nVolume > emittingVolume >> 4) {
					m_sQueueSample.m_nCounter = oldCounter + ((i + 1) << 8);
					if (m_sQueueSample.m_nLoopCount > 0) {
#ifndef USE_TIME_SCALE_FOR_AUDIO
						if ( CTimer::GetIsSlowMotionActive() ) {
							m_sQueueSample.m_nFrequency = halfOldFreq + ((halfOldFreq * i) / ARRAY_SIZE(m_afReflectionsDistances));
						} else
#endif
						{
							noise = RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
							if (noise > 0)
								m_sQueueSample.m_nFrequency -= noise;
							else
								m_sQueueSample.m_nFrequency += noise;
						}
					}
					m_sQueueSample.m_nPriority += 20;
					m_sQueueSample.m_vecPos = m_avecReflectionsPos[i];
					AddSampleToRequestedQueue();
				}
			}
		}
	}
	m_sQueueSample.m_vecPos = oldPos;
	m_sQueueSample.m_fDistance = oldDist;
}

void
cAudioManager::UpdateReflections()
{
	CVector camPos;
	CColPoint colpoint;
	CEntity *ent;

#if GTA_VERSION < GTAVC_PC_10
	if (m_FrameCounter % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[0] = camPos;
		m_avecReflectionsPos[0].y += 50.0f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[0], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[0] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[0] = 50.0f;
	} else if ((m_FrameCounter + 1) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[1] = camPos;
		m_avecReflectionsPos[1].y -= 50.0f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[1], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[1] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[1] = 50.0f;
	} else if ((m_FrameCounter + 2) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[2] = camPos;
		m_avecReflectionsPos[2].x -= 50.0f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[2], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[2] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[2] = 50.0f;
	} else if ((m_FrameCounter + 3) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[3] = camPos;
		m_avecReflectionsPos[3].x += 50.0f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[3], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[3] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[3] = 50.0f;
	} else if ((m_FrameCounter + 4) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[4] = camPos;
		m_avecReflectionsPos[4].z += 50.0f;
		if (CWorld::ProcessVerticalLine(camPos, m_avecReflectionsPos[4].z, colpoint, ent, true, false, false, false, true, false, nil))
			m_afReflectionsDistances[4] = colpoint.point.z - camPos.z;
		else
			m_afReflectionsDistances[4] = 50.0f;
	}
#else
	if (m_FrameCounter % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[0] = camPos;
		m_avecReflectionsPos[0].y += 100.f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[0], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[0] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[0] = 100.0f;
	} else if ((m_FrameCounter + 1) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[1] = camPos;
		m_avecReflectionsPos[1].y -= 100.0f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[1], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[1] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[1] = 100.0f;
	} else if ((m_FrameCounter + 2) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[2] = camPos;
		m_avecReflectionsPos[2].x -= 100.0f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[2], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[2] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[2] = 100.0f;
	} else if ((m_FrameCounter + 3) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		m_avecReflectionsPos[3] = camPos;
		m_avecReflectionsPos[3].x += 100.0f;
		if (CWorld::ProcessLineOfSight(camPos, m_avecReflectionsPos[3], colpoint, ent, true, false, false, true, false, true, true))
			m_afReflectionsDistances[3] = Distance(camPos, colpoint.point);
		else
			m_afReflectionsDistances[3] = 100.0f;
	} else if ((m_FrameCounter + 4) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		camPos.y += 1.0f;
		m_avecReflectionsPos[4] = camPos;
		m_avecReflectionsPos[4].z += 100.0f;
		if (CWorld::ProcessVerticalLine(camPos, m_avecReflectionsPos[4].z, colpoint, ent, true, false, false, false, true, false, nil))
			m_afReflectionsDistances[4] = colpoint.point.z - camPos.z;
		else
			m_afReflectionsDistances[4] = 100.0f;
	} else if ((m_FrameCounter + 5) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		camPos.y -= 1.0f;
		m_avecReflectionsPos[5] = camPos;
		m_avecReflectionsPos[5].z += 100.0f;
		if (CWorld::ProcessVerticalLine(camPos, m_avecReflectionsPos[5].z, colpoint, ent, true, false, false, false, true, false, nil))
			m_afReflectionsDistances[5] = colpoint.point.z - camPos.z;
		else
			m_afReflectionsDistances[5] = 100.0f;
	} else if ((m_FrameCounter + 6) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		camPos.x -= 1.0f;
		m_avecReflectionsPos[6] = camPos;
		m_avecReflectionsPos[6].z += 100.0f;
		if (CWorld::ProcessVerticalLine(camPos, m_avecReflectionsPos[6].z, colpoint, ent, true, false, false, false, true, false, nil))
			m_afReflectionsDistances[6] = colpoint.point.z - camPos.z;
		else
			m_afReflectionsDistances[6] = 100.0f;
	} else if ((m_FrameCounter + 7) % 8 == 0) {
		camPos = TheCamera.GetPosition();
		camPos.x += 1.0f;
		m_avecReflectionsPos[7] = camPos;
		m_avecReflectionsPos[7].z += 100.0f;
		if (CWorld::ProcessVerticalLine(camPos, m_avecReflectionsPos[7].z, colpoint, ent, true, false, false, false, true, false, nil))
			m_afReflectionsDistances[7] = colpoint.point.z - camPos.z;
		else
			m_afReflectionsDistances[7] = 100.0f;
	}
#endif
}
#endif // AUDIO_REFLECTIONS

void
cAudioManager::AddReleasingSounds()
{
	// in case someone would want to increase it
#ifdef FIX_BUGS
	bool8 toProcess[NUM_CHANNELS_GENERIC];
#else
	bool8 toProcess[44];
#endif

	uint8 queue = m_nActiveQueue == 0 ? 1 : 0;

	for (uint8 i = 0; i < m_nRequestedCount[queue]; i++) {
		tSound &sample = m_aRequestedQueue[queue][m_aRequestedOrderList[queue][i]];
		if (sample.m_bIsPlayingFinished)
			continue;

		toProcess[i] = FALSE;
		for (uint8 j = 0; j < m_nRequestedCount[m_nActiveQueue]; j++) {
			if (sample.m_nEntityIndex == m_aRequestedQueue[m_nActiveQueue][m_aRequestedOrderList[m_nActiveQueue][j]].m_nEntityIndex &&
			    sample.m_nCounter == m_aRequestedQueue[m_nActiveQueue][m_aRequestedOrderList[m_nActiveQueue][j]].m_nCounter) {
				toProcess[i] = TRUE;
				break;
			}
		}
		if(!toProcess[i]) {
#ifdef AUDIO_REFLECTIONS
			if(sample.m_nCounter <= 255 || sample.m_nReflectionDelay == 0) // check if not delayed reflection
#endif
			{
#ifdef ATTACH_RELEASING_SOUNDS_TO_ENTITIES
				if (sample.m_nCounter <= 255 && !sample.m_bIs2D) { // check if not reflection and is a 3D sound
					CEntity* entity = (CEntity*)GetEntityPointer(sample.m_nEntityIndex);
					if (entity && m_asAudioEntities[sample.m_nEntityIndex].m_nType == AUDIOTYPE_PHYSICAL) {
						sample.m_vecPos = entity->GetPosition();
						float oldDistance = sample.m_fDistance;
						sample.m_fDistance = Sqrt(GetDistanceSquared(sample.m_vecPos));
						if (sample.m_nSampleIndex >= SAMPLEBANK_PED_START && sample.m_nSampleIndex <= SAMPLEBANK_PED_END) { // check if it's ped comment
							uint8 vol;
							if (CWorld::GetIsLineOfSightClear(TheCamera.GetPosition(), sample.m_vecPos, true, false, false, false, false, false))
								vol = PED_COMMENT_VOLUME;
							else
								vol = PED_COMMENT_VOLUME_BEHIND_WALL;
#ifdef EXTERNAL_3D_SOUND
							sample.m_nEmittingVolume = vol;
#endif
							sample.m_nVolume = ComputeVolume(vol, sample.m_MaxDistance, sample.m_fDistance);
						} else {
							// calculate new volume with changed distance
							float volumeDiff = sq((sample.m_MaxDistance - sample.m_fDistance) / (sample.m_MaxDistance - oldDistance));
							if (volumeDiff > 0.0f) {
								uint8 newVolume = volumeDiff * sample.m_nVolume;
								if (sample.m_nVolumeChange > 0)
									sample.m_nVolumeChange = volumeDiff * sample.m_nVolumeChange;
#if defined(FIX_BUGS) && defined(EXTERNAL_3D_SOUND)
								if (sample.m_nEmittingVolumeChange > 0)
									sample.m_nEmittingVolumeChange = volumeDiff * sample.m_nEmittingVolumeChange;
#endif
								sample.m_nVolume = Min(MAX_VOLUME, newVolume);
							}
						}
						if (sample.m_nVolume == 0)
							sample.m_nFramesToPlay = 0;
					}
				}
#endif
#ifdef FIX_BUGS
				if (sample.m_nFramesToPlay <= 0)
					continue;
				if (sample.m_nLoopCount == 0) {
					if (sample.m_nVolumeChange == -1) {
						sample.m_nVolumeChange = sample.m_nVolume / sample.m_nFramesToPlay;
						if (sample.m_nVolumeChange <= 0)
							sample.m_nVolumeChange = 1;
#ifdef EXTERNAL_3D_SOUND
						sample.m_nEmittingVolumeChange = sample.m_nEmittingVolume / sample.m_nFramesToPlay;
						if (sample.m_nEmittingVolumeChange <= 0)
							sample.m_nEmittingVolumeChange = 1;
#endif
					}
					if (sample.m_nVolume <= sample.m_nVolumeChange * CTimer::GetTimeStepFix()) {
						sample.m_nFramesToPlay = 0;
						continue;
					}
					sample.m_nVolume -= sample.m_nVolumeChange * CTimer::GetTimeStepFix();
#ifdef EXTERNAL_3D_SOUND
					if (sample.m_nEmittingVolume <= sample.m_nEmittingVolumeChange * CTimer::GetTimeStepFix()) {
						sample.m_nFramesToPlay = 0;
						continue;
					}
					sample.m_nEmittingVolume -= sample.m_nEmittingVolumeChange * CTimer::GetTimeStepFix();
#endif
				}
				sample.m_nFramesToPlay -= CTimer::GetTimeStepFix();
				if (sample.m_nFramesToPlay < 0)
					sample.m_nFramesToPlay = 0;
#else
				if (sample.m_nFramesToPlay == 0)
					continue;
				if (sample.m_nLoopCount == 0) {
					if (sample.m_nVolumeChange == -1) {
						sample.m_nVolumeChange = sample.m_nVolume / sample.m_nFramesToPlay;
						if (sample.m_nVolumeChange <= 0)
							sample.m_nVolumeChange = 1;
					}
					if (sample.m_nVolume <= sample.m_nVolumeChange) {
						sample.m_nFramesToPlay = 0;
						continue;
					}
					sample.m_nVolume -= sample.m_nVolumeChange;
				}
				sample.m_nFramesToPlay--;
#endif
				if (m_bReduceReleasingPriority) {
					if (sample.m_nPriority < 20)
						sample.m_nPriority++;
				}
				sample.m_bStatic = FALSE;
			}
			memcpy(&m_sQueueSample, &sample, sizeof(tSound));
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessActiveQueues()
{
	bool8 flag;
	float position2;
	float position1;

	uint32 samplesPerFrame;
	uint32 samplesToPlay;

#ifdef EXTERNAL_3D_SOUND
	float x;
	float usedX;
	float usedY;
	float usedZ;
#endif

	uint8 vol;
	uint8 emittingVol;
	CVector position;

	bool8 isPhoneCall;
	uint8 channelOffset = 0;

#ifdef EXTERNAL_3D_SOUND
	#define WORKING_VOLUME_FIELD m_nEmittingVolume
#else
	#define WORKING_VOLUME_FIELD m_nVolume
#endif 

#ifdef USE_TIME_SCALE_FOR_AUDIO
	float timeScale = m_bIsPaused ? 1.0f : CTimer::GetTimeScale();
#endif

	for (uint8 i = 0; i < m_nActiveSamples; i++) {
		m_aRequestedQueue[m_nActiveQueue][i].m_bIsBeingPlayed = FALSE;
		m_asActiveSamples[i].m_bIsBeingPlayed = FALSE;
	}

	for (uint8 i = 0; i < m_nRequestedCount[m_nActiveQueue]; i++) {
		tSound &sample = m_aRequestedQueue[m_nActiveQueue][m_aRequestedOrderList[m_nActiveQueue][i]];
		if (sample.m_nSampleIndex != NO_SAMPLE) {
			for (uint8 j = 0; j < m_nActiveSamples; j++) {
				if (sample.m_nEntityIndex == m_asActiveSamples[j].m_nEntityIndex && sample.m_nCounter == m_asActiveSamples[j].m_nCounter &&
					sample.m_nSampleIndex == m_asActiveSamples[j].m_nSampleIndex) {
					if (sample.m_nLoopCount > 0) {
						if (m_FrameCounter & 1)
							flag = !!(j & 1);
						else
							flag = !(j & 1);

						if (flag && !SampleManager.GetChannelUsedFlag(j)) {
							sample.m_bIsPlayingFinished = TRUE;
							m_asActiveSamples[j].m_bIsPlayingFinished = TRUE;
							m_asActiveSamples[j].m_nSampleIndex = NO_SAMPLE;
							m_asActiveSamples[j].m_nEntityIndex = AEHANDLE_NONE;
							continue;
						}
						if (sample.m_nFramesToPlay == 0)
							sample.m_nFramesToPlay = 1;
					}
					sample.m_bIsBeingPlayed = TRUE;
					m_asActiveSamples[j].m_bIsBeingPlayed = TRUE;
					sample.m_nVolumeChange = -1;
					if (!sample.m_bStatic) {
						if (sample.m_bIs2D) {
							emittingVol = m_bDoubleVolume ? 2 * Min(63, sample.WORKING_VOLUME_FIELD) : sample.WORKING_VOLUME_FIELD;
#ifdef USE_TIME_SCALE_FOR_AUDIO
							SampleManager.SetChannelFrequency(j, sample.m_nFrequency * timeScale);
#else
							SampleManager.SetChannelFrequency(j, sample.m_nFrequency);
#endif
#ifdef EXTERNAL_3D_SOUND
							SampleManager.SetChannelEmittingVolume(j, emittingVol);
#else
							SampleManager.SetChannelPan(j, sample.m_nPan);
							SampleManager.SetChannelVolume(j, emittingVol);
#endif
						} else {
							position2 = sample.m_fDistance;
							position1 = m_asActiveSamples[j].m_fDistance;
							m_asActiveSamples[j].m_fDistance = sample.m_fDistance;
							sample.m_nFrequency = ComputeDopplerEffectedFrequency(sample.m_nFrequency, position1, position2, sample.m_fSpeedMultiplier);
							if (sample.m_nFrequency != m_asActiveSamples[j].m_nFrequency) {
								uint32 freq = Clamp2((int32)sample.m_nFrequency, (int32)m_asActiveSamples[j].m_nFrequency, 6000);
								m_asActiveSamples[j].m_nFrequency = freq;
#ifdef USE_TIME_SCALE_FOR_AUDIO
								SampleManager.SetChannelFrequency(j, freq * timeScale);
#else
								SampleManager.SetChannelFrequency(j, freq);
#endif
							}
#ifdef EXTERNAL_3D_SOUND
							if (sample.m_nEmittingVolume != m_asActiveSamples[j].m_nEmittingVolume) {
								vol = Clamp2((int8)sample.m_nEmittingVolume, (int8)m_asActiveSamples[j].m_nEmittingVolume, 10);
#else
							if (sample.m_nVolume != m_asActiveSamples[j].m_nVolume) {
								vol = Clamp2((int8)sample.m_nVolume, (int8)m_asActiveSamples[j].m_nVolume, 10);
#endif
								emittingVol = m_bDoubleVolume ? 2 * Min(63, vol) : vol;

								isPhoneCall = FALSE;
								for (int32 k = 0; k < MISSION_AUDIO_SLOTS; k++) {
									if (m_bIsMissionAudioPhoneCall[k]) {
										isPhoneCall = TRUE;
										break;
									}
								}
								if (isPhoneCall) {
									emittingVol = (emittingVol * m_nGlobalSfxVolumeMultiplier) / 127;
								} else {
									if (m_nGlobalSfxVolumeMultiplier < 127)
										emittingVol = (emittingVol * m_nGlobalSfxVolumeMultiplier) / 127;
								}

#ifdef EXTERNAL_3D_SOUND
								SampleManager.SetChannelEmittingVolume(j, emittingVol);
								m_asActiveSamples[j].m_nEmittingVolume = vol;
#else
								SampleManager.SetChannelVolume(j, emittingVol);
								m_asActiveSamples[j].m_nVolume = vol;
#endif
							}
							TranslateEntity(&sample.m_vecPos, &position);
#ifdef EXTERNAL_3D_SOUND
							SampleManager.SetChannel3DPosition(j, position.x, position.y, position.z);
							SampleManager.SetChannel3DDistances(j, sample.m_MaxDistance, 0.25f * sample.m_MaxDistance);
#else
							sample.m_nPan = ComputePan(sample.m_fDistance, &position);
							SampleManager.SetChannelPan(j, sample.m_nPan);
#endif
						}
#if !defined(GTA_PS2) || defined(AUDIO_REVERB)
						SampleManager.SetChannelReverbFlag(j, sample.m_bReverb);
#endif
						break; //continue for i
					}
					sample.m_bIsBeingPlayed = FALSE;
					m_asActiveSamples[j].m_bIsBeingPlayed = FALSE;
					//continue for j
				}
			}
		}
	}
	for (uint8 i = 0; i < m_nActiveSamples; i++) {
		if (m_asActiveSamples[i].m_nSampleIndex != NO_SAMPLE && !m_asActiveSamples[i].m_bIsBeingPlayed) {
			SampleManager.StopChannel(i);
			m_asActiveSamples[i].m_nSampleIndex = NO_SAMPLE;
			m_asActiveSamples[i].m_nEntityIndex = AEHANDLE_NONE;
		}
	}
	for (uint8 i = 0; i < m_nRequestedCount[m_nActiveQueue]; i++) {
		tSound &sample = m_aRequestedQueue[m_nActiveQueue][m_aRequestedOrderList[m_nActiveQueue][i]];
		if (!sample.m_bIsBeingPlayed && !sample.m_bIsPlayingFinished && m_asAudioEntities[sample.m_nEntityIndex].m_bIsUsed && sample.m_nSampleIndex < NO_SAMPLE) {
#ifdef AUDIO_REFLECTIONS
			if (sample.m_nCounter > 255 && sample.m_nLoopCount > 0 && sample.m_nReflectionDelay > 0) { // check if reflection
				sample.m_nReflectionDelay--;
				sample.m_nFramesToPlay = 1;
			} else
#endif
			{
				for (uint8 j = 0; j < m_nActiveSamples; j++) {
					uint8 k = (j + m_nChannelOffset) % m_nActiveSamples;
					if (!m_asActiveSamples[k].m_bIsBeingPlayed) {
						if (sample.m_nLoopCount > 0) {
							samplesPerFrame = sample.m_nFrequency / m_nTimeSpent;
							samplesToPlay = sample.m_nLoopCount * SampleManager.GetSampleLength(sample.m_nSampleIndex);
							if (samplesPerFrame == 0)
								continue;
							sample.m_nFramesToPlay = samplesToPlay / samplesPerFrame + 1;
						}
						memcpy(&m_asActiveSamples[k], &sample, sizeof(tSound));
						if (!m_asActiveSamples[k].m_bIs2D) {
							TranslateEntity(&m_asActiveSamples[k].m_vecPos, &position);
#ifndef EXTERNAL_3D_SOUND
							m_asActiveSamples[j].m_nPan = ComputePan(m_asActiveSamples[j].m_fDistance, &position);
#endif
						}
						emittingVol = m_bDoubleVolume ? 2 * Min(63, m_asActiveSamples[j].WORKING_VOLUME_FIELD) : m_asActiveSamples[j].WORKING_VOLUME_FIELD;
#ifdef GTA_PS2
						{
							SampleManager.InitialiseChannel(k, m_asActiveSamples[k].m_nSampleIndex, m_asActiveSamples[k].m_nBankIndex);
#else
						if (SampleManager.InitialiseChannel(k, m_asActiveSamples[k].m_nSampleIndex, m_asActiveSamples[k].m_nBankIndex)) {
#endif
#ifdef USE_TIME_SCALE_FOR_AUDIO
							SampleManager.SetChannelFrequency(k, m_asActiveSamples[k].m_nFrequency * timeScale);
#else
							SampleManager.SetChannelFrequency(k, m_asActiveSamples[k].m_nFrequency);
#endif
							isPhoneCall = FALSE;
							for (int32 l = 0; l < MISSION_AUDIO_SLOTS; l++) {
								if (m_bIsMissionAudioPhoneCall[l]) {
									isPhoneCall = TRUE;
									break;
								}
							}
							if (!isPhoneCall || m_asActiveSamples[k].m_bIs2D) {
								if (m_nGlobalSfxVolumeMultiplier < 127)
									emittingVol = (emittingVol * m_nGlobalSfxVolumeMultiplier) / 127;
								vol = emittingVol;
							} else {
								vol = (emittingVol * m_nGlobalSfxVolumeMultiplier) / 127;
							}
#ifdef EXTERNAL_3D_SOUND
							SampleManager.SetChannelEmittingVolume(k, vol);
#else
							SampleManager.SetChannelVolume(j, emittingVol);
							SampleManager.SetChannelPan(j, m_asActiveSamples[j].m_nPan);
#endif
#ifndef GTA_PS2
							SampleManager.SetChannelLoopPoints(k, m_asActiveSamples[k].m_nLoopStart, m_asActiveSamples[k].m_nLoopEnd);
#endif
							SampleManager.SetChannelLoopCount(k, m_asActiveSamples[k].m_nLoopCount);
#if !defined(GTA_PS2) || defined(AUDIO_REVERB)
							SampleManager.SetChannelReverbFlag(k, m_asActiveSamples[k].m_bReverb);
#endif
#ifdef EXTERNAL_3D_SOUND
							if (m_asActiveSamples[k].m_bIs2D) {
								uint8 offset = m_asActiveSamples[k].m_nPan;
								if (offset == 63)
									x = 0.0f;
								else if (offset >= 63)
									x = (offset - 63) * 1000.0f / 63;
								else
									x = -(63 - offset) * 1000.0f / 63; //same like line below
								usedX = x;
								usedY = 0.0f;
								usedZ = 0.0f;
								m_asActiveSamples[k].m_MaxDistance = 100000.0f;
							} else {
								usedX = position.x;
								usedY = position.y;
								usedZ = position.z;
							}
							SampleManager.SetChannel3DPosition(k, usedX, usedY, usedZ);
							SampleManager.SetChannel3DDistances(k, m_asActiveSamples[k].m_MaxDistance, 0.25f * m_asActiveSamples[k].m_MaxDistance);
#endif
							SampleManager.StartChannel(k);
						}
						m_asActiveSamples[k].m_bIsBeingPlayed = TRUE;
						channelOffset++;
						sample.m_bIsBeingPlayed = TRUE;
						sample.m_nVolumeChange = -1;
						break;
					}
				}
			}
		}
	}

#ifdef GTA_PS2
	m_nChannelOffset += channelOffset;
#endif
	m_nChannelOffset %= m_nActiveSamples;

#ifdef USE_TIME_SCALE_FOR_AUDIO
	for (uint8 i = 0; i < m_nActiveSamples; i++) {
		if (m_asActiveSamples[i].m_nSampleIndex != NO_SAMPLE && m_asActiveSamples[i].m_bIsBeingPlayed)
			SampleManager.SetChannelFrequency(i, m_asActiveSamples[i].m_nFrequency * timeScale);
	}
#endif

#undef WORKING_VOLUME_FIELD
}

void
cAudioManager::ClearRequestedQueue()
{
	for (uint8 i = 0; i < m_nActiveSamples; i++)
		m_aRequestedOrderList[m_nActiveQueue][i] = m_nActiveSamples;
	m_nRequestedCount[m_nActiveQueue] = 0;
}

void
cAudioManager::ClearActiveSamples()
{
	for (uint8 i = 0; i < m_nActiveSamples; i++) {
		m_asActiveSamples[i].m_nEntityIndex = AEHANDLE_NONE;
		m_asActiveSamples[i].m_nCounter = 0;
		m_asActiveSamples[i].m_nSampleIndex = NO_SAMPLE;
		m_asActiveSamples[i].m_nBankIndex = INVALID_SFX_BANK;
		m_asActiveSamples[i].m_bIs2D = FALSE;
		m_asActiveSamples[i].m_nPriority = 5;
		m_asActiveSamples[i].m_nFrequency = 0;
		m_asActiveSamples[i].m_nVolume = 0;
#ifdef EXTERNAL_3D_SOUND
		m_asActiveSamples[i].m_nEmittingVolume = 0;
#endif
		m_asActiveSamples[i].m_fDistance = 0.0f;
		m_asActiveSamples[i].m_bIsBeingPlayed = FALSE;
		m_asActiveSamples[i].m_bIsPlayingFinished = FALSE;
		m_asActiveSamples[i].m_nLoopCount = 1;
#ifndef GTA_PS2
		m_asActiveSamples[i].m_nLoopStart = 0;
		m_asActiveSamples[i].m_nLoopEnd = -1;
#endif
		m_asActiveSamples[i].m_fSpeedMultiplier = 0.0f;
		m_asActiveSamples[i].m_MaxDistance = 200.0f;
		m_asActiveSamples[i].m_nPan = 63;
		m_asActiveSamples[i].m_bStatic = FALSE;
		m_asActiveSamples[i].m_nFinalPriority = 0;
		m_asActiveSamples[i].m_nFramesToPlay = 0;
		m_asActiveSamples[i].m_nVolumeChange = -1;
		m_asActiveSamples[i].m_vecPos = CVector(0.0f, 0.0f, 0.0f);
#ifdef AUDIO_REVERB
		m_asActiveSamples[i].m_bReverb = FALSE;
#endif // AUDIO_REVERB
#ifdef AUDIO_REFLECTIONS
		m_asActiveSamples[i].m_nReflectionDelay = 0;
		m_asActiveSamples[i].m_bReflections = FALSE;
#endif // AUDIO_REFLECTIONS
	}
}

void
cAudioManager::GenerateIntegerRandomNumberTable()
{
	for (uint32 i = 0; i < ARRAY_SIZE(m_anRandomTable); i++)
		m_anRandomTable[i] = myrand();
}

#ifdef GTA_PS2
void
cAudioManager::LoadBankIfNecessary(uint8 bank)
{
	if(!SampleManager.IsSampleBankLoaded(bank))
		SampleManager.LoadSampleBank(bank);
}
#endif

#ifdef EXTERNAL_3D_SOUND
void
cAudioManager::AdjustSamplesVolume()
{
	for (uint8 i = 0; i < m_nRequestedCount[m_nActiveQueue]; i++) {
		tSound *pSample = &m_aRequestedQueue[m_nActiveQueue][m_aRequestedOrderList[m_nActiveQueue][i]];

		if (!pSample->m_bIs2D)
			pSample->m_nEmittingVolume = ComputeEmittingVolume(pSample->m_nEmittingVolume, pSample->m_MaxDistance, pSample->m_fDistance);
	}
}

uint8
cAudioManager::ComputeEmittingVolume(uint8 emittingVolume, float maxDistance, float distance)
{
	float minDistance = maxDistance / 4.0f;
	float diffDistance = maxDistance - minDistance;
	if (distance > diffDistance)
		return (minDistance - (distance - diffDistance)) * (float)emittingVolume / minDistance;
	return emittingVolume;
}
#endif
