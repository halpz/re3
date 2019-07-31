#include "common.h"
#include "patcher.h"

#include "AudioManager.h"

#include "Automobile.h"
#include "Camera.h"
#include "DMAudio.h"
#include "Explosion.h"
#include "Garages.h"
#include "ModelIndices.h"
#include "MusicManager.h"
#include "Ped.h"
#include "Physical.h"
#include "Plane.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "sampman.h"
#include "Stats.h"
#include "SurfaceTable.h"
#include "Vehicle.h"
#include "Plane.h"
#include "World.h"

uint32 *audioLogicTimers = (uint32 *)0x6508A0;

// TODO: where is this used? Is this the right file?
enum eVehicleModel {
	LANDSTAL,
	IDAHO,
	STINGER,
	LINERUN,
	PEREN,
	SENTINEL,
	PATRIOT,
	FIRETRUK,
	TRASH,
	STRETCH,
	MANANA,
	INFERNUS,
	BLISTA,
	PONY,
	MULE,
	CHEETAH,
	AMBULAN,
	FBICAR,
	MOONBEAM,
	ESPERANT,
	TAXI,
	KURUMA,
	BOBCAT,
	MRWHOOP,
	BFINJECT,
	CORPSE,
	POLICE,
	ENFORCER,
	SECURICA,
	BANSHEE,
	PREDATOR,
	BUS,
	RHINO,
	BARRACKS,
	TRAIN,
	CHOPPER,
	DODO,
	COACH,
	CABBIE,
	STALLION,
	RUMPO,
	RCBANDIT,
	BELLYUP,
	MRWONGS,
	MAFIA,
	YARDIE,
	YAKUZA,
	DIABLOS,
	COLUMB,
	HOODS,
	AIRTRAIN,
	DEADDODO,
	SPEEDER,
	REEFER,
	PANLANT,
	FLATBED,
	YANKEE,
	ESCAPE,
	BORGNINE,
	TOYZ,
	GHOST,
	CAR151,
	CAR152,
	CAR153,
	CAR154,
	CAR155,
	CAR156,
	CAR157,
	CAR158,
	CAR159,
};

void
cPedComments::Add(tPedComment *com)
{
	uint8 index;

	if(nrOfCommentsInBank[activeBank] >= 20u) {
		index = field_1120[activeBank][19];
		if(m_asPedComments[activeBank][index].m_bVolume > com->m_bVolume) return;
	} else {
		index = nrOfCommentsInBank[activeBank]++;
	}
	m_asPedComments[activeBank][index] = *com;

	uint32 i = 0;
	if(index != 0) {
		for(i = 0; i < index; i++) {
			if(m_asPedComments[activeBank][field_1120[activeBank][i]].m_bVolume <
			   m_asPedComments[activeBank][index].m_bVolume) {
				memmove(&field_1120[activeBank][i + 1], &field_1120[activeBank][i],
				        19 - i);
				break;
			}
		}
	}

	field_1120[activeBank][i] = index;
}

void *
cAudioScriptObject::operator new(size_t sz)
{
	return CPools::GetAudioScriptObjectPool()->New();
}
void *
cAudioScriptObject::operator new(size_t sz, int handle)
{
	return CPools::GetAudioScriptObjectPool()->New(handle);
}
void
cAudioScriptObject::operator delete(void *p, size_t sz)
{
	CPools::GetAudioScriptObjectPool()->Delete((cAudioScriptObject *)p);
}
void
cAudioScriptObject::operator delete(void *p, int handle)
{
	CPools::GetAudioScriptObjectPool()->Delete((cAudioScriptObject *)p);
}

cAudioManager &AudioManager = *(cAudioManager *)0x880FC0;

constexpr int totalAudioEntitiesSlots = 200;
constexpr int maxVolume = 127;

char &g_nMissionAudioPlayingStatus = *(char *)0x60ED88;

void
cAudioManager::AddDetailsToRequestedOrderList(uint8 sample)
{
	uint32 i = 0;
	if(sample != 0) {
		for(; i < sample; i++) {
			if(m_asSamples[m_bActiveSampleQueue]
			              [m_abSampleQueueIndexTable[m_bActiveSampleQueue][i]]
			                  .calculatedVolume >
			   m_asSamples[m_bActiveSampleQueue][sample].calculatedVolume)
				break;
		}
		if(i < sample) {
			memmove(&m_abSampleQueueIndexTable[m_bActiveSampleQueue][i + 1],
			        &m_abSampleQueueIndexTable[m_bActiveSampleQueue][i],
			        m_bActiveSamples - i - 1);
		}
	}
	m_abSampleQueueIndexTable[m_bActiveSampleQueue][i] = sample;
}

void
cAudioManager::AddPlayerCarSample(uint8 emittingVolume, int32 freq, uint32 sample, uint8 unk1,
                                  uint8 unk2, bool notLooping)
{
	m_sQueueSample.m_bVolume = ComputeVolume(emittingVolume, 50.f, m_sQueueSample.m_fDistance);
	if(m_sQueueSample.m_bVolume) {
		m_sQueueSample.field_4 = unk2;
		m_sQueueSample.m_nSampleIndex = sample;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.field_16 = 0;
		m_sQueueSample.m_nFrequency = freq;
		if(notLooping) {
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.field_76 = 8;
		} else {
			m_sQueueSample.m_nLoopCount = 1;
		}
		m_sQueueSample.m_bEmittingVolume = emittingVolume;
		m_sQueueSample.m_nLoopStart =
		    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nLoopEnd =
		    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.field_48 = 6.0f;
		m_sQueueSample.m_fSoundIntensity = 50.0f;
		m_sQueueSample.field_56 = 0;
		m_sQueueSample.m_bReverbFlag = 1;
		m_sQueueSample.m_bRequireReflection = 0;
		AddSampleToRequestedQueue();
	}
}

void
cAudioManager::AddReflectionsToRequestedQueue()
{
	float reflectionDistance;
	int32 noise;
	uint8 emittingVolume = emittingVolume =
	    (m_sQueueSample.m_bVolume >> 1) + (m_sQueueSample.m_bVolume >> 3);

	for(uint32 i = 0; i < 5u; i++) {
		reflectionDistance = m_afReflectionsDistances[i];
		if(reflectionDistance > 0.0f && reflectionDistance < 100.f &&
		   reflectionDistance < m_sQueueSample.m_fSoundIntensity) {
			m_sQueueSample.m_bLoopsRemaining = (reflectionDistance * 500.f / 1029.f);
			if(m_sQueueSample.m_bLoopsRemaining > 5u) {
				m_sQueueSample.m_fDistance = m_afReflectionsDistances[i];
				m_sQueueSample.m_bEmittingVolume = emittingVolume;
				m_sQueueSample.m_bVolume =
				    ComputeVolume(emittingVolume, m_sQueueSample.m_fSoundIntensity,
				                  m_sQueueSample.m_fDistance);
				if(m_sQueueSample.m_bVolume > emittingVolume >> 4) {
					m_sQueueSample.field_4 += ((i + 1) << 8);
					if(m_sQueueSample.m_nLoopCount) {
						noise = RandomDisplacement(
						    m_sQueueSample.m_nFrequency >> 5);
						if(noise <= 0)
							m_sQueueSample.m_nFrequency += noise;
						else
							m_sQueueSample.m_nFrequency -= noise;
					}
					m_sQueueSample.field_16 += 20;
					m_sQueueSample.m_vecPos.x = m_avecReflectionsPos[i].x;
					m_sQueueSample.m_vecPos.y = m_avecReflectionsPos[i].y;
					m_sQueueSample.m_vecPos.z = m_avecReflectionsPos[i].z;
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

#if 1
WRAPPER void
cAudioManager::AddReleasingSounds()
{
	EAXJMP(0x57B8D0);
}
#else
void
cAudioManager::AddReleasingSounds()
{
	bool isFirstSampleQueue;
	int32 calculatedIndex;
	tActiveSample *sample;
	uint8 field_76;
	uint8 field_88;
	int sampleQueue;
	bool toProcess[44];
	isFirstSampleQueue = m_bActiveSampleQueue == 0;

	cAudioManager *s = (this + 2484 * isFirstSampleQueue); // wtf

	for(uint32 i = 0; i < m_bSampleRequestQueuesStatus[isFirstSampleQueue]; i++) {
		calculatedIndex = i + 27 * isFirstSampleQueue;
		sample = &s->m_asSamples[m_abSampleQueueIndexTable[calculatedIndex]];
		if(!s->m_asSamples[m_abSampleQueueIndexTable[calculatedIndex]].m_bLoopEnded) {
			toProcess[i] = 0;
			sampleQueue = m_bActiveSampleQueue;
			for(uint8 j = 0; j < m_bSampleRequestQueuesStatus[m_bActiveSampleQueue];
			    j++) {
				if(sample->m_nEntityIndex ==
				       m_asSamples[27 * sampleQueue +
				                   m_abSampleQueueIndexTable[27 * sampleQueue + j]]
				           .m_nEntityIndex &&
				   sample->field_4 ==
				       m_asSamples[27 * sampleQueue +
				                   m_abSampleQueueIndexTable[27 * sampleQueue + j]]
				           .field_4) {
					toProcess[i] = 1;
					break;
				}
			}
			if(!toProcess[i]) {
				if(sample->field_4 <= 255u || !sample->m_bLoopsRemaining) {
					field_76 = sample->field_76;
					if(!field_76) continue;
					if(!sample->m_nLoopCount) {
						uint8 &vol = sample->m_bVolume;
						if(sample->field_88 == -1) {
							sample->field_88 = vol / field_76;
							if(sample->field_88 <= 0)
								sample->field_88 = 1;
						}
						field_88 = sample->field_88;
						if(vol <= field_88) {
							sample->field_76 = 0;
							continue;
						}
						vol -= field_88;
					}
					--sample->field_76;
					if(field_2) {
						if(sample->field_16 < 20u) ++sample->field_16;
					}
					sample->field_56 = 0;
				}
				memcpy(&m_sQueueSample, sample, 92);
				AddSampleToRequestedQueue();
			}
		}
	}
}
#endif

void
cAudioManager::AddSampleToRequestedQueue()
{
	int32 calculatedVolume;
	tActiveSample *sample;
	uint8 sampleIndex;
	bool bReflections;

	if(m_sQueueSample.m_nSampleIndex < TOTAL_AUDIO_SAMPLES) {
		calculatedVolume = m_sQueueSample.field_16 * (maxVolume - m_sQueueSample.m_bVolume);
		sampleIndex = m_bSampleRequestQueuesStatus[m_bActiveSampleQueue];
		if(sampleIndex >= m_bActiveSamples) {
			sampleIndex =
			    m_abSampleQueueIndexTable[m_bActiveSampleQueue][m_bActiveSamples - 1];
			if(m_asSamples[m_bActiveSampleQueue][sampleIndex].calculatedVolume <=
			   calculatedVolume)
				return;
		} else {
			++m_bSampleRequestQueuesStatus[m_bActiveSampleQueue];
		}
		m_sQueueSample.calculatedVolume = calculatedVolume;
		m_sQueueSample.m_bLoopEnded = 0;
		if(m_sQueueSample.m_bIsDistant) {
			m_sQueueSample.m_bRequireReflection = 0;
			m_sQueueSample.m_bLoopsRemaining = 0;
		}
		if(m_bDynamicAcousticModelingStatus && m_sQueueSample.m_nLoopCount) {
			bReflections = m_sQueueSample.m_bRequireReflection;
		} else {
			bReflections = false;
			m_sQueueSample.m_bLoopsRemaining = 0;
		}
		m_sQueueSample.m_bRequireReflection = 0;

		if(!m_bDynamicAcousticModelingStatus) m_sQueueSample.m_bReverbFlag = 0;

		sample = &m_asSamples[m_bActiveSampleQueue][sampleIndex];
		sample->m_nEntityIndex = m_sQueueSample.m_nEntityIndex;
		sample->field_4 = m_sQueueSample.field_4;
		sample->m_nSampleIndex = m_sQueueSample.m_nSampleIndex;
		sample->m_bBankIndex = m_sQueueSample.m_bBankIndex;
		sample->m_bIsDistant = m_sQueueSample.m_bIsDistant;
		sample->field_16 = m_sQueueSample.field_16;
		sample->m_nFrequency = m_sQueueSample.m_nFrequency;
		sample->m_bVolume = m_sQueueSample.m_bVolume;
		sample->m_fDistance = m_sQueueSample.m_fDistance;
		sample->m_nLoopCount = m_sQueueSample.m_nLoopCount;
		sample->m_nLoopStart = m_sQueueSample.m_nLoopStart;
		sample->m_nLoopEnd = m_sQueueSample.m_nLoopEnd;
		sample->m_bEmittingVolume = m_sQueueSample.m_bEmittingVolume;
		sample->field_48 = m_sQueueSample.field_48;
		sample->m_fSoundIntensity = m_sQueueSample.m_fSoundIntensity;
		sample->field_56 = m_sQueueSample.field_56;
		sample->m_vecPos = m_sQueueSample.m_vecPos;
		sample->m_bReverbFlag = m_sQueueSample.m_bReverbFlag;
		sample->m_bLoopsRemaining = m_sQueueSample.m_bLoopsRemaining;
		sample->m_bRequireReflection = m_sQueueSample.m_bRequireReflection;
		sample->m_bOffset = m_sQueueSample.m_bOffset;
		sample->field_76 = m_sQueueSample.field_76;
		sample->m_bIsProcessed = m_sQueueSample.m_bIsProcessed;
		sample->m_bLoopEnded = m_sQueueSample.m_bLoopEnded;
		sample->calculatedVolume = m_sQueueSample.calculatedVolume;
		sample->field_88 = m_sQueueSample.field_88;

		AddDetailsToRequestedOrderList(sampleIndex);
		if(bReflections) AddReflectionsToRequestedQueue();
	}
}

WRAPPER
void
cAudioManager::AgeCrimes()
{
	EAXJMP(0x580AF0);
}

int8
cAudioManager::GetCurrent3DProviderIndex()
{
	if(m_bIsInitialised) return SampleManager.GetCurrent3DProviderIndex();

	return -1;
}

void
cAudioManager::CalculateDistance(bool *ptr, float dist)
{
	if(*ptr == false) {
		m_sQueueSample.m_fDistance = sqrt(dist);
		*ptr = true;
	}
}

bool
cAudioManager::CheckForAnAudioFileOnCD()
{
	return SampleManager.CheckForAnAudioFileOnCD();
}

void
cAudioManager::ClearMissionAudio()
{
	if(m_bIsInitialised) {
		m_sMissionAudio.m_nSampleIndex = NO_SAMPLE;
		m_sMissionAudio.m_bLoadingStatus = 0;
		m_sMissionAudio.m_bPlayStatus = 0;
		m_sMissionAudio.field_22 = 0;
		m_sMissionAudio.m_bIsPlayed = false;
		m_sMissionAudio.field_12 = 1;
		m_sMissionAudio.field_24 = 0;
	}
}

void
cAudioManager::ClearRequestedQueue()
{
	for(int32 i = 0; i < m_bActiveSamples; i++) {
		m_abSampleQueueIndexTable[m_bActiveSampleQueue][i] = m_bActiveSamples;
	}
	m_bSampleRequestQueuesStatus[m_bActiveSampleQueue] = 0;
}

int32
cAudioManager::ComputeDopplerEffectedFrequency(uint32 oldFreq, float position1, float position2,
                                               float speedMultiplier)
{
	uint32 newFreq = oldFreq;
	if(!TheCamera.Get_Just_Switched_Status() && speedMultiplier != 0.0f) {
		float dist = position2 - position1;
		if(dist != 0.0f) {
			float speedOfSource = (dist / field_19195) * speedMultiplier;
			if(speedOfSound > fabsf(speedOfSource)) {
				if(speedOfSource < 0.0f) {
					speedOfSource = Max(speedOfSource, -1.5f);
				} else {
					speedOfSource = Min(speedOfSource, 1.5f);
				}
				newFreq = (oldFreq * speedOfSound) / (speedOfSource + speedOfSound);
			}
		}
	}
	return newFreq;
}

WRAPPER
int32
cAudioManager::ComputePan(float, CVector *)
{
	EAXJMP(0x57AD20);
}

uint32
cAudioManager::ComputeVolume(int emittingVolume, float soundIntensity, float distance)
{
	float newSoundIntensity;
	if(soundIntensity <= 0.0f) return 0;
	if((soundIntensity * 0.2f) <= distance) {
		newSoundIntensity = soundIntensity * 0.2f;
		emittingVolume =
		    sq((soundIntensity - distance) / (soundIntensity - newSoundIntensity)) *
		    emittingVolume;
	}
	return emittingVolume;
}

int32
cAudioManager::CreateEntity(int32 type, void *entity)
{
	if(!m_bIsInitialised) return -4;
	if(!entity) return -2;
	if(type >= TOTAL_AUDIO_TYPES) return -1;
	for(uint32 i = 0; i < 200; i++) {
		if(!m_asAudioEntities[i].m_bIsUsed) {
			m_asAudioEntities[i].m_bIsUsed = true;
			m_asAudioEntities[i].m_bStatus = 0;
			m_asAudioEntities[i].m_nType = (eAudioType)type;
			m_asAudioEntities[i].m_pEntity = entity;
			m_asAudioEntities[i].m_awAudioEvent[0] = SOUND_TOTAL_PED_SOUNDS;
			m_asAudioEntities[i].m_awAudioEvent[1] = SOUND_TOTAL_PED_SOUNDS;
			m_asAudioEntities[i].m_awAudioEvent[2] = SOUND_TOTAL_PED_SOUNDS;
			m_asAudioEntities[i].m_awAudioEvent[3] = SOUND_TOTAL_PED_SOUNDS;
			m_asAudioEntities[i].field_24 = 0;
			m_anAudioEntityIndices[m_nAudioEntitiesTotal++] = i;
			return i;
		}
	}
	return -3;
}

void
cAudioManager::DestroyAllGameCreatedEntities()
{
	cAudioScriptObject *entity;

	if(m_bIsInitialised) {
		for(uint32 i = 0; i < 200; i++) {
			if(m_asAudioEntities[i].m_bIsUsed) {
				switch(m_asAudioEntities[i].m_nType) {
				case AUDIOTYPE_PHYSICAL:
				case AUDIOTYPE_EXPLOSION:
				case AUDIOTYPE_WEATHER:
				case AUDIOTYPE_CRANE:
				case AUDIOTYPE_GARAGE:
				case AUDIOTYPE_FIREHYDRANT: cAudioManager::DestroyEntity(i); break;
				case AUDIOTYPE_SCRIPTOBJECT:
					entity =
					    (cAudioScriptObject *)m_asAudioEntities[i].m_pEntity;
					if(entity) { delete entity; }
					DestroyEntity(i);
					break;
				default: break;
				}
			}
		}
		m_nScriptObjectEntityTotal = 0;
	}
}

void
cAudioManager::DestroyEntity(int32 id)
{
	if(m_bIsInitialised && id >= 0 && id < totalAudioEntitiesSlots &&
	   m_asAudioEntities[id].m_bIsUsed) {
		m_asAudioEntities[id].m_bIsUsed = 0;
		for(int32 i = 0; i < m_nAudioEntitiesTotal; ++i) {
			if(id == m_anAudioEntityIndices[i]) {
				if(i < totalAudioEntitiesSlots - 1)
					memmove(&m_anAudioEntityIndices[i],
					        &m_anAudioEntityIndices[i + 1],
					        4 * (m_nAudioEntitiesTotal - (i + 1)));
				m_anAudioEntityIndices[--m_nAudioEntitiesTotal] =
				    totalAudioEntitiesSlots;
				return;
			}
		}
	}
}

void
cAudioManager::DoPoliceRadioCrackle()
{
	m_sQueueSample.m_nEntityIndex = m_nPoliceChannelEntity;
	m_sQueueSample.field_4 = 0;
	m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_POLICE_SCANNER_CRACKLE;
	m_sQueueSample.m_bBankIndex = 0;
	m_sQueueSample.m_bIsDistant = 1;
	m_sQueueSample.field_16 = 10;
	m_sQueueSample.m_nFrequency =
	    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_POLICE_SCANNER_CRACKLE);
	m_sQueueSample.m_bVolume = m_anRandomTable[2] % 20u + 15;
	m_sQueueSample.m_nLoopCount = 0;
	m_sQueueSample.m_bEmittingVolume = m_sQueueSample.m_bVolume;
	m_sQueueSample.m_nLoopStart = SampleManager.GetSampleLoopStartOffset(188);
	m_sQueueSample.m_nLoopEnd = SampleManager.GetSampleLoopEndOffset(188);
	m_sQueueSample.field_56 = 0;
	m_sQueueSample.m_bReverbFlag = 0;
	m_sQueueSample.m_bOffset = 63;
	m_sQueueSample.field_76 = 3;
	m_sQueueSample.m_bRequireReflection = 0;
	AddSampleToRequestedQueue();
}

void
cAudioManager::GenerateIntegerRandomNumberTable()
{
	for(int32 i = 0; i < 5; i++) { m_anRandomTable[i] = rand(); }
}

float
cAudioManager::GetDistanceSquared(CVector *v)
{
	const CVector &c = TheCamera.GetPosition();
	return sq(v->x - c.x) + sq(v->y - c.y) + sq((v->z - c.z) * 0.2f);
}

void
cAudioManager::TranslateEntity(CVector *v1, CVector *v2)
{
	const RwMatrix &cM = TheCamera.GetMatrix().m_matrix;
	const CVector &cV = TheCamera.GetPosition();

	float a = v1->z - cV.z;
	float b = v1->y - cV.y;
	float c = v1->x - cV.x;

	v2->x = cM.right.y * b + cM.right.x * c + cM.right.z * a;
	v2->y = cM.up.y * b + cM.up.x * c + cM.up.z * a;
	v2->z = cM.at.y * b + cM.at.x * c + cM.at.z * a;
}

void
cAudioManager::Initialise()
{
	if(!m_bIsInitialised) {
		PreInitialiseGameSpecificSetup();
		m_bIsInitialised = SampleManager.Initialise();
		if(m_bIsInitialised) {
			m_bActiveSamples = SampleManager.GetMaximumSupportedChannels();
			if(m_bActiveSamples <= 1u) {
				Terminate();
			} else {
				--m_bActiveSamples;
				PostInitialiseGameSpecificSetup();
				InitialisePoliceRadioZones();
				InitialisePoliceRadio();
				MusicManager.Initialise();
			}
		}
	}
}

void
cAudioManager::PostInitialiseGameSpecificSetup()
{
	m_nFireAudioEntity =
	    CreateEntity(AUDIOTYPE_FIRE,
	                 (CPhysical *)0x8F31D0); // last is addr of firemanager @todo change
	if(m_nFireAudioEntity >= 0) SetEntityStatus(m_nFireAudioEntity, 1);

	m_nCollisionEntity = CreateEntity(AUDIOTYPE_COLLISION, (CPhysical *)1);
	if(m_nCollisionEntity >= 0) SetEntityStatus(m_nCollisionEntity, 1);

	m_nFrontEndEntity = CreateEntity(AUDIOTYPE_FRONTEND, (CPhysical *)1);
	if(m_nFrontEndEntity >= 0) SetEntityStatus(m_nFrontEndEntity, 1);

	m_nProjectileEntity = CreateEntity(AUDIOTYPE_PROJECTILE, (CPhysical *)1);
	if(m_nProjectileEntity >= 0) SetEntityStatus(m_nProjectileEntity, 1);

	m_nWaterCannonEntity = CreateEntity(AUDIOTYPE_WATERCANNON, (CPhysical *)1);
	if(m_nWaterCannonEntity >= 0) SetEntityStatus(m_nWaterCannonEntity, 1);

	m_nPoliceChannelEntity = CreateEntity(AUDIOTYPE_POLICERADIO, (CPhysical *)1);
	if(m_nPoliceChannelEntity >= 0) SetEntityStatus(m_nPoliceChannelEntity, 1);

	m_nBridgeEntity = CreateEntity(AUDIOTYPE_BRIDGE, (CPhysical *)1);
	if(m_nBridgeEntity >= 0) SetEntityStatus(m_nBridgeEntity, 1);

	m_sMissionAudio.m_nSampleIndex = NO_SAMPLE;
	m_sMissionAudio.m_bLoadingStatus = 0;
	m_sMissionAudio.m_bPlayStatus = 0;
	m_sMissionAudio.field_22 = 0;
	m_sMissionAudio.m_bIsPlayed = 0;
	m_sMissionAudio.field_12 = 1;
	m_sMissionAudio.field_24 = 0;
	ResetAudioLogicTimers((int32)CTimer::GetTimeInMilliseconds);
}

WRAPPER
void
cAudioManager::InitialisePoliceRadioZones()
{
	EAXJMP(0x57EAC0);
}

WRAPPER
void
cAudioManager::ResetAudioLogicTimers(int32 timer)
{
	EAXJMP(0x569650);
}

void
cAudioManager::Terminate()
{
	if(m_bIsInitialised) {
		MusicManager.Terminate();

		for(uint32 i = 0; i < totalAudioEntitiesSlots; i++) {
			m_asAudioEntities[i].m_bIsUsed = 0;
			m_anAudioEntityIndices[i] = 200;
		}

		m_nAudioEntitiesTotal = 0;
		m_nScriptObjectEntityTotal = 0;
		PreTerminateGameSpecificShutdown();

		for(uint32 i = 0; i < 2; i++) {
			if(SampleManager.IsSampleBankLoaded(i)) SampleManager.UnloadSampleBank(i);
		}

		SampleManager.Terminate();

		m_bIsInitialised = 0;
		PostTerminateGameSpecificShutdown();
	}
}

char
cAudioManager::GetMissionScriptPoliceAudioPlayingStatus()
{
	return g_nMissionAudioPlayingStatus;
}

bool
cAudioManager::GetMissionAudioLoadingStatus()
{
	if(m_bIsInitialised) return m_sMissionAudio.m_bLoadingStatus;

	return true;
}

uint8
cAudioManager::GetNum3DProvidersAvailable()
{
	if(m_bIsInitialised) return SampleManager.GetNum3DProvidersAvailable();
	return 0;
}

bool
cAudioManager::IsMP3RadioChannelAvailable()
{
	if(m_bIsInitialised) return SampleManager.IsMP3RadioChannelAvailable();

	return 0;
}

uint8
cAudioManager::GetCDAudioDriveLetter()
{
	if(m_bIsInitialised) return SampleManager.GetCDAudioDriveLetter();

	return 0;
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
cAudioManager::SetEffectsFadeVolume(uint8 volume)
{
	SampleManager.SetEffectsFadeVolume(volume);
}

void
cAudioManager::SetMusicFadeVolume(uint8 volume)
{
	SampleManager.SetMusicFadeVolume(volume);
}

void
cAudioManager::SetSpeakerConfig(int32 conf)
{
	SampleManager.SetSpeakerConfig(conf);
}

WRAPPER
bool cAudioManager::SetupJumboEngineSound(uint8, int32) { EAXJMP(0x56F140); }

int32 *BankStartOffset = (int32 *)0x6FAB70; //[2]

void
cAudioManager::PreInitialiseGameSpecificSetup()
{
	BankStartOffset[0] = AUDIO_SAMPLE_VEHICLE_HORN_0;
	BankStartOffset[1] = AUDIO_SAMPLE_POLICE_COP_1_ARREST_1;
}

int32 &g_nMissionAudioSfx = *(int32 *)0x60ED84;

void
cAudioManager::SetMissionScriptPoliceAudio(int32 sfx)
{
	if(m_bIsInitialised) {
		if(g_nMissionAudioPlayingStatus != 1) {
			g_nMissionAudioPlayingStatus = 0;
			g_nMissionAudioSfx = sfx;
		}
	}
}

bool
cAudioManager::UsesSiren(int32 model)
{
	switch(model) {
	case FIRETRUK:
	case AMBULAN:
	case FBICAR:
	case POLICE:
	case ENFORCER:
	case PREDATOR: return true;
	default: return false;
	}
}

bool
cAudioManager::UsesSirenSwitching(int32 model)
{
	switch(model) {
	case AMBULAN:
	case POLICE:
	case ENFORCER:
	case PREDATOR: return true;
	default: return false;
	}
}

bool
cAudioManager::MissionScriptAudioUsesPoliceChannel(int32 soundMission)
{
	switch(soundMission) {
	case STREAMED_SOUND_MISSION_J6_D:
	case STREAMED_SOUND_MISSION_T4_A:
	case STREAMED_SOUND_MISSION_S1_H:
	case STREAMED_SOUND_MISSION_S3_B:
	case STREAMED_SOUND_MISSION_EL3_A:
	case STREAMED_SOUND_MISSION_A3_A:
	case STREAMED_SOUND_MISSION_A5_A:
	case STREAMED_SOUND_MISSION_K1_A:
	case STREAMED_SOUND_MISSION_R1_A:
	case STREAMED_SOUND_MISSION_R5_A:
	case STREAMED_SOUND_MISSION_LO2_A:
	case STREAMED_SOUND_MISSION_LO6_A: return true;
	default: return false;
	}
}

char *
cAudioManager::Get3DProviderName(uint8 id)
{
	if(!m_bIsInitialised) return 0;
	if(id >= SampleManager.GetNum3DProvidersAvailable()) return 0;
	return SampleManager.Get3DProviderName(id);
}

bool
cAudioManager::SetupJumboFlySound(uint8 emittingVol)
{
	int32 vol;

	if(m_sQueueSample.m_fDistance >= 440.0) return 0;

	vol = ComputeVolume(emittingVol, 440.0f, m_sQueueSample.m_fDistance);
	m_sQueueSample.m_bVolume = vol;
	if(m_sQueueSample.m_bVolume) {
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_JUMBO_FLY_SOUND;
		m_sQueueSample.field_4 = 0;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.field_16 = 1;
		m_sQueueSample.m_bEmittingVolume = emittingVol;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_JUMBO_FLY_SOUND);
		m_sQueueSample.m_nLoopStart =
		    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_fSoundIntensity = 440.0f;
		m_sQueueSample.field_56 = 0;
		m_sQueueSample.field_48 = 4.0f;
		m_sQueueSample.m_bReverbFlag = 1;
		m_sQueueSample.field_76 = 5;
		m_sQueueSample.m_nLoopEnd =
		    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
		AddSampleToRequestedQueue();
	}
	return 1;
}

bool
cAudioManager::SetupJumboRumbleSound(uint8 emittingVol)
{
	if(m_sQueueSample.m_fDistance >= 240.f) return 0;

	m_sQueueSample.m_bVolume = ComputeVolume(emittingVol, 240.f, m_sQueueSample.m_fDistance);

	if(m_sQueueSample.m_bVolume) {
		m_sQueueSample.field_4 = 5;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_JUMBO_RUMBLE_SOUND;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_bIsDistant = 1;
		m_sQueueSample.field_16 = 1;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_JUMBO_RUMBLE_SOUND);
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_bEmittingVolume = emittingVol;
		m_sQueueSample.m_nLoopStart =
		    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nLoopEnd =
		    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.field_48 = 4.0f;
		m_sQueueSample.m_fSoundIntensity = 240.0f;
		m_sQueueSample.field_56 = 0;
		m_sQueueSample.field_76 = 12;
		m_sQueueSample.m_bOffset = 0;
		m_sQueueSample.m_bReverbFlag = 1;
		m_sQueueSample.m_bRequireReflection = 0;
		AddSampleToRequestedQueue();
		m_sQueueSample.field_4 = 6;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_JUMBO_RUMBLE_SOUND;
		m_sQueueSample.m_nFrequency += 200;
		m_sQueueSample.m_bOffset = 127;
		AddSampleToRequestedQueue();
	}
	return 1;
}

uint8 &gJumboVolOffsetPercentage = *(uint8 *)0x6508ED;

bool
cAudioManager::SetupJumboTaxiSound(uint8 vol)
{
	uint8 emittingVol;

	if(m_sQueueSample.m_fDistance >= 180.f) return 0;

	emittingVol = (vol >> 1) + ((vol >> 1) * m_sQueueSample.m_fDistance * 0.0055556f);

	if(m_sQueueSample.m_fDistance * 0.0055556f < 0.7f)
		emittingVol -= emittingVol * gJumboVolOffsetPercentage / 100;
	m_sQueueSample.m_bVolume = ComputeVolume(emittingVol, 180.f, m_sQueueSample.m_fDistance);

	if(m_sQueueSample.m_bVolume) {
		m_sQueueSample.field_4 = 1;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_JUMBO_TAXI_SOUND;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.field_16 = 1;
		m_sQueueSample.m_nFrequency = GetJumboTaxiFreq();
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_bEmittingVolume = emittingVol;
		m_sQueueSample.m_nLoopStart =
		    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nLoopEnd =
		    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.field_48 = 4.0f;
		m_sQueueSample.m_fSoundIntensity = 180.0f;
		m_sQueueSample.field_56 = 0;
		m_sQueueSample.field_76 = 4;
		m_sQueueSample.m_bReverbFlag = 1;
		m_sQueueSample.m_bRequireReflection = 0;
		AddSampleToRequestedQueue();
	}
	return 1;
}

bool
cAudioManager::SetupJumboWhineSound(uint8 emittingVol, int32 freq)
{
	if(m_sQueueSample.m_fDistance >= 170.f) return 0;

	m_sQueueSample.m_bVolume = ComputeVolume(emittingVol, 170.f, m_sQueueSample.m_fDistance);

	if(m_sQueueSample.m_bVolume) {
		m_sQueueSample.field_4 = 2;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_JUMBO_WHINE_SOUND;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.field_16 = 1;
		m_sQueueSample.m_nFrequency = freq;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_bEmittingVolume = emittingVol;
		m_sQueueSample.m_nLoopStart =
		    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nLoopEnd =
		    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.field_48 = 4.0f;
		m_sQueueSample.m_fSoundIntensity = 170.0f;
		m_sQueueSample.field_56 = 0;
		m_sQueueSample.field_76 = 4;
		m_sQueueSample.m_bReverbFlag = 1;
		m_sQueueSample.m_bRequireReflection = 0;
		AddSampleToRequestedQueue();
	}
	return 1;
}

void
cAudioManager::PlayLoadedMissionAudio()
{
	if(m_bIsInitialised && m_sMissionAudio.m_nSampleIndex != NO_SAMPLE &&
	   m_sMissionAudio.m_bLoadingStatus == 1 && !m_sMissionAudio.m_bPlayStatus) {
		m_sMissionAudio.m_bIsPlayed = true;
	}
}

void
cAudioManager::SetMissionAudioLocation(float x, float y, float z)
{
	if(m_bIsInitialised) {
		m_sMissionAudio.field_12 = 0;
		m_sMissionAudio.m_vecPos.x = x;
		m_sMissionAudio.m_vecPos.y = y;
		m_sMissionAudio.m_vecPos.z = z;
	}
}

void
cAudioManager::ResetPoliceRadio()
{
	if(m_bIsInitialised) {
		if(SampleManager.GetChannelUsedFlag(28)) SampleManager.StopChannel(28);
		InitialisePoliceRadio();
	}
}

void
cAudioManager::InterrogateAudioEntities()
{
	for(int32 i = 0; i < m_nAudioEntitiesTotal; i++) {
		ProcessEntity(m_anAudioEntityIndices[i]);
		m_asAudioEntities[m_anAudioEntityIndices[i]].field_24 = 0;
	}
}

bool
cAudioManager::UsesReverseWarning(int32 model)
{
	return model == LINERUN || model == FIRETRUK || model == TRASH || model == BUS ||
	       model == COACH; // fix
}

bool
cAudioManager::HasAirBrakes(int32 model)
{
	return model == LINERUN || model == FIRETRUK || model == TRASH || model == BUS ||
	       model == COACH; // fix
}

int32
cAudioManager::GetJumboTaxiFreq()
{
	return (60.833f * m_sQueueSample.m_fDistance) + 22050;
}

bool
cAudioManager::IsMissionAudioSampleFinished()
{
	if(m_bIsInitialised) return m_sMissionAudio.m_bPlayStatus == 2;

	static int32 cPretendFrame = 1;

	return (cPretendFrame++ & 63) == 0;
}

WRAPPER
void
cAudioManager::InitialisePoliceRadio()
{
	EAXJMP(0x57EEC0);
}

int32
cAudioManager::RandomDisplacement(uint32 seed)
{
	int32 value;

	static bool bIsEven = true;
	static uint32 base = 0;

	if(!seed) return 0;

	value = m_anRandomTable[(base + seed) % 5] % seed;
	base += value;

	if(value % 2) { bIsEven = !bIsEven; }
	if(!bIsEven) value = -value;
	return value;
}

void
cAudioManager::ReleaseDigitalHandle()
{
	if(m_bIsInitialised) { SampleManager.ReleaseDigitalHandle(); }
}

void
cAudioManager::ReacquireDigitalHandle()
{
	if(m_bIsInitialised) { SampleManager.ReacquireDigitalHandle(); }
}

void
cAudioManager::SetDynamicAcousticModelingStatus(bool status)
{
	m_bDynamicAcousticModelingStatus = status;
}

bool
cAudioManager::IsAudioInitialised() const
{
	return m_bIsInitialised;
}

void
cAudioManager::SetEntityStatus(int32 id, bool status)
{
	if(m_bIsInitialised && id >= 0 && id < totalAudioEntitiesSlots) {
		if(m_asAudioEntities[id].m_bIsUsed) { m_asAudioEntities[id].m_bStatus = status; }
	}
}

void
cAudioManager::PreTerminateGameSpecificShutdown()
{
	if(m_nBridgeEntity >= 0) {
		DestroyEntity(m_nBridgeEntity);
		m_nBridgeEntity = -5;
	}
	if(m_nPoliceChannelEntity >= 0) {
		DestroyEntity(m_nPoliceChannelEntity);
		m_nPoliceChannelEntity = -5;
	}
	if(m_nWaterCannonEntity >= 0) {
		DestroyEntity(m_nWaterCannonEntity);
		m_nWaterCannonEntity = -5;
	}
	if(m_nFireAudioEntity >= 0) {
		DestroyEntity(m_nFireAudioEntity);
		m_nFireAudioEntity = -5;
	}
	if(m_nCollisionEntity >= 0) {
		DestroyEntity(m_nCollisionEntity);
		m_nCollisionEntity = -5;
	}
	if(m_nFrontEndEntity >= 0) {
		DestroyEntity(m_nFrontEndEntity);
		m_nFrontEndEntity = -5;
	}
	if(m_nProjectileEntity >= 0) {
		DestroyEntity(m_nProjectileEntity);
		m_nProjectileEntity = -5;
	}
}

void
cAudioManager::PostTerminateGameSpecificShutdown()
{
	;
}

bool &bPlayerJustEnteredCar = *(bool *)0x6508C4;

void
cAudioManager::PlayerJustGotInCar()
{
	if(m_bIsInitialised) { bPlayerJustEnteredCar = true; }
}

void
cAudioManager::PlayerJustLeftCar(void)
{
	// UNUSED: This is a perfectly empty function.
}

void
cAudioManager::GetPhrase(uint32 *phrase, uint32 *prevPhrase, uint32 sample, uint32 maxOffset)
{
	*phrase = sample + m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] % maxOffset;

	// check if the same sfx like last time, if yes, then try use next one,
	// if exceeded range, then choose first available sample
	if(*phrase == *prevPhrase && ++*phrase >= sample + maxOffset) *phrase = sample;
	*prevPhrase = *phrase;
}

uint8 &jumboVolOffset = *(uint8 *)0x6508ED;

void
cAudioManager::DoJumboVolOffset()
{
	if(!(m_FrameCounter % (m_anRandomTable[0] % 6u + 3)))
		jumboVolOffset = m_anRandomTable[1] % 60u;
}

int32
cAudioManager::GetPedCommentSfx(CPed *ped, int32 sound)
{
	if(ped->IsPlayer()) return GetPlayerTalkSfx(sound);

	switch(ped->m_modelIndex) {
	case MI_COP: return GetCopTalkSfx(sound);
	case MI_SWAT: return GetSwatTalkSfx(sound);
	case MI_FBI: return GetFBITalkSfx(sound);
	case MI_ARMY: return GetArmyTalkSfx(sound);
	case MI_MEDIC: return GetMedicTalkSfx(sound);
	case MI_FIREMAN: return GetFiremanTalkSfx(sound);
	case MI_MALE01: return GetNormalMaleTalkSfx(sound);
	case MI_TAXI_D: return GetTaxiDriverTalkSfx(sound);
	case MI_PIMP: return GetPimpTalkSfx(sound);
	case MI_GANG01:
	case MI_GANG02: return GetMafiaTalkSfx(sound);
	case MI_GANG03:
	case MI_GANG04: return GetTriadTalkSfx(sound);
	case MI_GANG05:
	case MI_GANG06: return GetDiabloTalkSfx(sound);
	case MI_GANG07:
	case MI_GANG08: return GetYakuzaTalkSfx(sound);
	case MI_GANG09:
	case MI_GANG10: return GetYardieTalkSfx(sound);
	case MI_GANG11:
	case MI_GANG12: return GetColumbianTalkSfx(sound);
	case MI_GANG13:
	case MI_GANG14: return GetHoodTalkSfx(sound);
	case MI_CRIMINAL01: return GetBlackCriminalTalkSfx(sound);
	case MI_CRIMINAL02: return GetWhiteCriminalTalkSfx(sound);
	case MI_SPECIAL01:
	case MI_SPECIAL02:
	case MI_SPECIAL03:
	case MI_SPECIAL04: return GetSpecialCharacterTalkSfx(ped->m_modelIndex, sound);
	case MI_MALE02: return GetMaleNo2TalkSfx(sound);
	case MI_MALE03:
	case MI_P_MAN1:
	case MI_P_MAN2: return GetBlackProjectMaleTalkSfx(sound, ped->m_modelIndex);
	case MI_FATMALE01: return GetWhiteFatMaleTalkSfx(sound);
	case MI_FATMALE02: return GetBlackFatMaleTalkSfx(sound);
	case MI_FEMALE01: return GetBlackCasualFemaleTalkSfx(sound);
	case MI_FEMALE02:
	case MI_CAS_WOM: return GetWhiteCasualFemaleTalkSfx(sound);
	case MI_FEMALE03: return GetFemaleNo3TalkSfx(sound);
	case MI_FATFEMALE01: return GetBlackFatFemaleTalkSfx(sound);
	case MI_FATFEMALE02: return GetWhiteFatFemaleTalkSfx(sound);
	case MI_PROSTITUTE: return GetBlackFemaleProstituteTalkSfx(sound);
	case MI_PROSTITUTE2: return GetWhiteFemaleProstituteTalkSfx(sound);
	case MI_P_WOM1: return GetBlackProjectFemaleOldTalkSfx(sound);
	case MI_P_WOM2: return GetBlackProjectFemaleYoungTalkSfx(sound);
	case MI_CT_MAN1: return GetChinatownMaleOldTalkSfx(sound);
	case MI_CT_MAN2: return GetChinatownMaleYoungTalkSfx(sound);
	case MI_CT_WOM1: return GetChinatownFemaleOldTalkSfx(sound);
	case MI_CT_WOM2: return GetChinatownFemaleYoungTalkSfx(sound);
	case MI_LI_MAN1:
	case MI_LI_MAN2: return GetLittleItalyMaleTalkSfx(sound);
	case MI_LI_WOM1: return GetLittleItalyFemaleOldTalkSfx(sound);
	case MI_LI_WOM2: return GetLittleItalyFemaleYoungTalkSfx(sound);
	case MI_DOCKER1: return GetWhiteDockerMaleTalkSfx(sound);
	case MI_DOCKER2: return GetBlackDockerMaleTalkSfx(sound);
	case MI_SCUM_MAN: return GetScumMaleTalkSfx(sound);
	case MI_SCUM_WOM: return GetScumFemaleTalkSfx(sound);
	case MI_WORKER1: return GetWhiteWorkerMaleTalkSfx(sound);
	case MI_WORKER2: return GetBlackWorkerMaleTalkSfx(sound);
	case MI_B_MAN1:
	case MI_B_MAN3: return GetBusinessMaleYoungTalkSfx(sound, ped->m_modelIndex);
	case MI_B_MAN2: return GetBusinessMaleOldTalkSfx(sound);
	case MI_B_WOM1:
	case MI_B_WOM2: return GetWhiteBusinessFemaleTalkSfx(sound, ped->m_modelIndex);
	case MI_B_WOM3: return GetBlackBusinessFemaleTalkSfx(sound);
	case MI_MOD_MAN: return GetSupermodelMaleTalkSfx(sound);
	case MI_MOD_WOM: return GetSupermodelFemaleTalkSfx(sound);
	case MI_ST_MAN: return GetStewardMaleTalkSfx(sound);
	case MI_ST_WOM: return GetStewardFemaleTalkSfx(sound);
	case MI_FAN_MAN1:
	case MI_FAN_MAN2: return GetFanMaleTalkSfx(sound, ped->m_modelIndex);
	case MI_FAN_WOM: return GetFanFemaleTalkSfx(sound);
	case MI_HOS_MAN: return GetHospitalMaleTalkSfx(sound);
	case MI_HOS_WOM: return GetHospitalFemaleTalkSfx(sound);
	case MI_CONST1: return GetWhiteConstructionWorkerTalkSfx(sound);
	case MI_CONST2: return GetBlackConstructionWorkerTalkSfx(sound);
	case MI_SHOPPER1:
	case MI_SHOPPER2:
	case MI_SHOPPER3: return GetShopperFemaleTalkSfx(sound, ped->m_modelIndex);
	case MI_STUD_MAN: return GetStudentMaleTalkSfx(sound);
	case MI_STUD_WOM: return GetStudentFemaleTalkSfx(sound);
	case MI_CAS_MAN: return GetCasualMaleOldTalkSfx(sound);
	default: return GetGenericMaleTalkSfx(sound);
	}
}

uint32
cAudioManager::GetPlayerTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_DAMAGE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DAMAGE_REACTION_1, 11u);
		break;

	case SOUND_PED_HIT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HIT_REACTION_1, 10u); break;

	case SOUND_PED_LAND: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FALL_REACTION_1, 6u); break;

	default: sfx = NO_SAMPLE; break;
	}
	return sfx;
}

uint32
cAudioManager::GetCopTalkSfx(int16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	if(sound == SOUND_PED_ARREST_COP) {
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_POLICE_COP_1_ARREST_1, 6u);
	} else {
		if(sound != SOUND_PED_PURSUIT_COP) {
			return cAudioManager::GetGenericMaleTalkSfx(sound);
		}

		pedState = FindPlayerPed()->m_nPedState;
		if(pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_POLICE_COP_1_PURSUIT_1, 7u);
	}

	return 13 * (m_sQueueSample.m_nEntityIndex % 5) + sfx;
}

uint32
cAudioManager::GetSwatTalkSfx(int16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	if(sound == SOUND_PED_ARREST_SWAT) {
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_POLICE_SWAT_1_PURSUIT_ARREST_1, 6u);
	} else {
		if(sound != SOUND_PED_PURSUIT_SWAT) {
			return cAudioManager::GetGenericMaleTalkSfx(sound);
		}

		pedState = FindPlayerPed()->m_nPedState;
		if(pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_POLICE_SWAT_1_PURSUIT_ARREST_1, 6u);
	}

	return 6 * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetFBITalkSfx(int16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	if(sound == SOUND_PED_ARREST_FBI) {
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_POLICE_FBI_1_PURSUIT_ARREST_1, 6u);
	} else {
		if(sound != SOUND_PED_PURSUIT_FBI) {
			return cAudioManager::GetGenericMaleTalkSfx(sound);
		}

		pedState = FindPlayerPed()->m_nPedState;
		if(pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_POLICE_FBI_1_PURSUIT_ARREST_1, 6u);
	}

	return 6 * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetArmyTalkSfx(int16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	if(sound != SOUND_PED_PURSUIT_ARMY) { return cAudioManager::GetGenericMaleTalkSfx(sound); }

	pedState = FindPlayerPed()->m_nPedState;
	if(pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE)
		return NO_SAMPLE;
	GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_POLICE_ARMY_1_PURSUIT_1, 15u);

	return 15 * (m_sQueueSample.m_nEntityIndex % 1) + sfx;
}

uint32
cAudioManager::GetMedicTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MEDIC_1_HANDS_COWER_1, 5u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MEDIC_1_CAR_JACKED_1, 5u);
		break;
	case SOUND_PED_HEALING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MEDIC_1_HEALING_1, 12u);
		break;
	case SOUND_PED_LEAVE_VEHICLE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MEDIC_1_LEAVE_VEHICLE_1, 9u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MEDIC_1_FLEE_RUN_1, 6u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return 37 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetFiremanTalkSfx(int16 sound)
{
	return cAudioManager::GetGenericMaleTalkSfx(sound);
}

uint32
cAudioManager::GetNormalMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_HANDS_COWER_1, 7u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_CAR_JACKED_1, 7u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_EVADE_1, 9u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_FLEE_RUN_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_CAR_COLLISION_1, 12u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_CHAT_SEXY_1, 8u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_CHAT_EVENT_1, 0xAu);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_NORMAL_MALE_CHAT_1, 25u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetTaxiDriverTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	if(sound == SOUND_PED_CAR_JACKED) {
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TAXI_DRIVER_1_CAR_JACKED_1, 7u);
	} else {
		if(sound != SOUND_PED_CAR_COLLISION)
			return cAudioManager::GetGenericMaleTalkSfx(sound);
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TAXI_DRIVER_1_CAR_COLLISION_1, 6u);
	}
	return 13 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetPimpTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_PIMP_HANDS_UP_1, 7u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_PIMP_CAR_JACKED_1, 4u);
		break;
	case SOUND_PED_DEFEND: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_PIMP_DEFEND_1, 9u); break;
	case SOUND_PED_EVADE: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_PIMP_EVADE_1, 6u); break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_PIMP_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_PIMP_CHAT_EVENT_1, 2u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_PIMP_CHAT_1, 17u); break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetMafiaTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MAFIA_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MAFIA_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MAFIA_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MAFIA_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MAFIA_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MAFIA_1_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MAFIA_1_CHAT_1, 7u); break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return 30 * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetTriadTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_HANDS_UP_1, 3u);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_CAR_COLLISION_1, 7u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_TRIAD_1_CHAT_1, 8u); break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetDiabloTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_HANDS_UP_1, 4u);
		break;
	case SOUND_PED_HANDS_COWER:
		sound = SOUND_PED_FLEE_SPRINT;
		return cAudioManager::GetGenericMaleTalkSfx(sound);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_CHAT_SEXY_1, 4u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_DIABLO_1_CHAT_1, 5u); break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return 30 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetYakuzaTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YAKUZA_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YAKUZA_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YAKUZA_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YAKUZA_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YAKUZA_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YAKUZA_1_CHAT_1, 5u); break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return 24 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetYardieTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP: sfx = AUDIO_SAMPLE_PED_YARDIE_1_HANDS_UP_1; break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YARDIE_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED: sfx = AUDIO_SAMPLE_PED_YARDIE_1_CAR_JACKED_1; break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YARDIE_1_ATTACK_1, 6u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YARDIE_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YARDIE_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YARDIE_1_CHAT_SEXY_1, 2u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_YARDIE_1_CHAT_1, 8u); break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return 31 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetColumbianTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_COLUMB_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_COLUMB_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_COLUMB_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_COLUMB_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_COLUMB_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_COLUMB_1_CHAT_SEXY_1, 2u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_COLUMB_1_CHAT_1, 5u); break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return 27 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetHoodTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_HANDS_UP_1, 5u);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_ATTACK_1, 6u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_CAR_COLLISION_1, 7u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_CHAT_SEXY_1, 2u);
		break;
	case SOUND_PED_CHAT: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOODS_1_CHAT_1, 6u); break;

	default: return cAudioManager::GetGenericMaleTalkSfx(sound); break;
	}
	return 35 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetBlackCriminalTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CRIMINAL_1_HANDS_UP_1, 4u);
		break;
	case SOUND_PED_CAR_JACKING: sfx = AUDIO_SAMPLE_PED_BLACK_CRIMINAL_1_CAR_JACKING_1; break;
	case SOUND_PED_MUGGING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CRIMINAL_1_MUGGING_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CRIMINAL_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CRIMINAL_1_EVADE_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CRIMINAL_1_CAR_COLLISION_1, 5u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound); break;
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteCriminalTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CRIMINAL_1_HANDS_UP_1, 3u);
		break;
	case SOUND_PED_CAR_JACKING: sfx = AUDIO_SAMPLE_PED_WHITE_CRIMINAL_1_CAR_JACKING_1; break;
	case SOUND_PED_MUGGING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CRIMINAL_1_MUGGING_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CRIMINAL_1_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CRIMINAL_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CRIMINAL_1_CAR_COLLISION_1, 4u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound); break;
	}
	return sfx;
}

uint32
cAudioManager::GetMaleNo2TalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_NO_2_CAR_JACKED_1,
		                         3u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_NO_2_ROBBED_1, 4u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_NO_2_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_NO_2_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_NO_2_CAR_COLLISION_1,
		                         7u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_NO_2_CHAT_SEXY_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_NO_2_CHAT_1, 7u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackProjectMaleTalkSfx(int16 sound, int32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_HANDS_UP_1, 3u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_ATTACK_1, 6u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_CAR_COLLISION_1,
		          7u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_MALE_1_CHAT_1, 6u);
	default: return GetGenericMaleTalkSfx(sound);
	}

	if(model == MI_P_MAN2) sfx += 34;
	return sfx;
}

uint32
cAudioManager::GetWhiteFatMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_MALE_1_CAR_JACKED_1, 3u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_MALE_1_ROBBED_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_MALE_1_EVADE_1, 9u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_MALE_1_CAR_COLLISION_1, 9u);
		break;
	case SOUND_PED_WAIT_DOUBLEBACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_MALE_1_WAIT_DOUBLEBACK_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_MALE_1_CHAT_1, 9u);
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackFatMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_MALE_1_CAR_JACKED_1, 4u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_MALE_1_ROBBED_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_MALE_1_EVADE_1, 7u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_MALE_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_WAIT_DOUBLEBACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_MALE_1_WAIT_DOUBLEBACK_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_MALE_1_CHAT_1, 8u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackCasualFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_HANDS_COWER_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_ROBBED_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_EVADE_1, 6u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_FLEE_RUN_1, 2u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_CAR_COLLISION_1,
		          7u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_CHAT_EVENT_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CASUAL_FEMALE_1_CHAT_1, 8u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteCasualFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_HANDS_COWER_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED: sfx = AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_ROBBED_1; break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_EVADE_1, 3u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_FLEE_RUN_1, 2u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_CAR_COLLISION_1,
		          8u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_CHAT_EVENT_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CASUAL_FEMALE_1_CHAT_1, 4u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetFemaleNo3TalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_HANDS_COWER_1, 5u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_CAR_JACKED_1, 3u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_ROBBED_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_EVADE_1, 6u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_FLEE_RUN_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_CHAT_EVENT_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_NO_3_CHAT_1, 5u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackFatFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_FEMALE_1_HANDS_COWER_1, 4u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_FEMALE_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_FEMALE_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_FEMALE_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_FEMALE_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_FEMALE_1_CHAT_EVENT_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FAT_FEMALE_1_CHAT_1, 7u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteFatFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_FEMALE_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_FEMALE_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_FEMALE_1_EVADE_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_FEMALE_1_CAR_COLLISION_1, 8u);
		break;
	case SOUND_PED_WAIT_DOUBLEBACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_FEMALE_1_WAIT_DOUBLEBACK_1,
		          2u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_FEMALE_1_CHAT_EVENT_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FAT_FEMALE_1_CHAT_1, 8u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackFemaleProstituteTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FEMALE_PROSTITUTE_1_HANDS_UP_1,
		          4u);
		break;
	case SOUND_PED_ROBBED: sfx = AUDIO_SAMPLE_PED_BLACK_FEMALE_PROSTITUTE_1_ROBBED_1; break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FEMALE_PROSTITUTE_1_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FEMALE_PROSTITUTE_1_EVADE_1, 3u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx,
		          AUDIO_SAMPLE_PED_BLACK_FEMALE_PROSTITUTE_1_CAR_COLLISION_1, 4u);
		break;
	case SOUND_PED_SOLICIT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FEMALE_PROSTITUTE_1_SOLICIT_1, 8u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_FEMALE_PROSTITUTE_1_CHAT_1, 4u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return 28 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetWhiteFemaleProstituteTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FEMALE_PROSTITUTE_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FEMALE_PROSTITUTE_1_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FEMALE_PROSTITUTE_1_EVADE_1, 3u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx,
		          AUDIO_SAMPLE_PED_WHITE_FEMALE_PROSTITUTE_1_CAR_COLLISION_1, 4u);
		break;
	case SOUND_PED_SOLICIT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FEMALE_PROSTITUTE_1_SOLICIT_1, 8u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_FEMALE_PROSTITUTE_1_CHAT_1, 4u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return 25 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetBlackProjectFemaleOldTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_OLD_1_CAR_JACKED_1,
		          6u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_OLD_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_OLD_1_EVADE_1, 10u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_OLD_1_FLEE_RUN_1,
		          6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		cAudioManager::GetPhrase(
		    &sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_OLD_1_CAR_COLLISION_1,
		    7u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_OLD_1_CHAT_EVENT_1,
		          2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_OLD_1_CHAT_1, 10u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackProjectFemaleYoungTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		cAudioManager::GetPhrase(
		    &sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_YOUNG_1_HANDS_COWER_1,
		    4u);
		break;
	case SOUND_PED_CAR_JACKED:
		sfx = AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_YOUNG_1_CAR_JACKED_1;
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_YOUNG_1_ROBBED_1,
		          2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_YOUNG_1_EVADE_1,
		          5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		cAudioManager::GetPhrase(
		    &sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_YOUNG_1_CAR_COLLISION_1,
		    6u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx,
		          AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_YOUNG_1_CHAT_EVENT_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_PROJECT_FEMALE_YOUNG_1_CHAT_1, 7u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownMaleOldTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_OLD_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_OLD_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_OLD_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_OLD_EVADE_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_OLD_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_OLD_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_OLD_CHAT_1, 7u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownMaleYoungTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_YOUNG_HANDS_COWER_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_YOUNG_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_YOUNG_ATTACK_1, 6u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_YOUNG_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_YOUNG_CAR_COLLISION_1,
		          6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_YOUNG_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_MALE_YOUNG_CHAT_1, 6u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownFemaleOldTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_OLD_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_OLD_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_OLD_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_OLD_CAR_COLLISION_1,
		          5u);
		break;
	case SOUND_PED_CHAT_EVENT: sfx = AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_OLD_CHAT_EVENT_1; break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_OLD_CHAT_1, 6u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownFemaleYoungTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_YOUNG_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_YOUNG_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_YOUNG_EVADE_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_YOUNG_CAR_COLLISION_1,
		          7u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_YOUNG_CHAT_EVENT_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHINATOWN_FEMALE_YOUNG_CHAT_1, 7u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetLittleItalyMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_MALE_1_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_MALE_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_MALE_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_MALE_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_MALE_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_MALE_1_CAR_COLLISION_1, 7u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_MALE_1_CHAT_1, 6u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return 30 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetLittleItalyFemaleOldTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_OLD_CAR_JACKED_1,
		          2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_OLD_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_OLD_EVADE_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_OLD_CAR_COLLISION_1,
		          7u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_OLD_CHAT_EVENT_1,
		          4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_OLD_CHAT_1, 7u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetLittleItalyFemaleYoungTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_YOUNG_CAR_JACKED_1,
		          2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_YOUNG_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_YOUNG_EVADE_1, 7u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx,
		          AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_YOUNG_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_YOUNG_CHAT_EVENT_1,
		          4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_LITTLE_ITALY_FEMALE_YOUNG_CHAT_1, 6u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteDockerMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_DOCKER_MALE_HANDS_COWER_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_DOCKER_MALE_ATTACK_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_DOCKER_MALE_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_DOCKER_MALE_CAR_COLLISION_1, 4u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_DOCKER_MALE_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_DOCKER_MALE_CHAT_1, 5u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackDockerMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_DOCKER_MALE_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_DOCKER_MALE_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_DOCKER_MALE_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_DOCKER_MALE_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_DOCKER_MALE_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_DOCKER_MALE_CHAT_1, 5u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetScumMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_MALE_HANDS_COWER_1, 5u);
		break;
	case SOUND_PED_ROBBED: sfx = AUDIO_SAMPLE_PED_SCUM_MALE_ROBBED_1; break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_MALE_ATTACK_1, 0xAu);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_MALE_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_MALE_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_WAIT_DOUBLEBACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_MALE_WAIT_DOUBLEBACK_1, 3u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_MALE_CHAT_SEXY_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_MALE_CHAT_1, 9u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetScumFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_FEMALE_HANDS_COWER_1, 4u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_FEMALE_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_FEMALE_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_FEMALE_EVADE_1, 8u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_FEMALE_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SCUM_FEMALE_CHAT_1, 13u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteWorkerMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_WORKER_MALE_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_WORKER_MALE_ATTACK_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_WORKER_MALE_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_WORKER_MALE_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_WORKER_MALE_CHAT_SEXY_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_WORKER_MALE_CHAT_1, 6u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackWorkerMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_WORKER_MALE_HANDS_COWER_1, 4u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_WORKER_MALE_ATTACK_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_WORKER_MALE_EVADE_1, 3u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_WORKER_MALE_CAR_COLLISION_1, 4u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_WORKER_MALE_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_WORKER_MALE_CHAT_1, 4u);

		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBusinessMaleYoungTalkSfx(int16 sound, int32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_EVADE_1, 4u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_FLEE_RUN_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_CAR_COLLISION_1,
		          6u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_YOUNG_1_CHAT_1, 6u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}

	if(model == 61) sfx += 32;
	return sfx;
}

uint32
cAudioManager::GetBusinessMaleOldTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_EVADE_1, 4u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_FLEE_RUN_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_MALE_OLD_1_CHAT_1, 5u);

		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteBusinessFemaleTalkSfx(int16 sound, int32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_HANDS_COWER_1, 4u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_EVADE_1, 6u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_FLEE_RUN_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_CHAT_EVENT_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BUSINESS_WOMAN_1_CHAT_1, 7u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}

	if(model == MI_B_WOM2) sfx += 34;
	return sfx;
}

uint32
cAudioManager::GetBlackBusinessFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_HANDS_COWER_1, 5u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_CAR_JACKED_1, 4u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_ROBBED_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_EVADE_1, 6u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_FLEE_RUN_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_CAR_COLLISION_1,
		          7u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_CHAT_EVENT_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_BUSINESS_FEMALE_CHAT_1, 7u);

		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetSupermodelMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_MALE_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_MALE_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_MALE_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_MALE_EVADE_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_MALE_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_MALE_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_MALE_CHAT_1, 6u);

		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetSupermodelFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_FEMALE_HANDS_COWER_1, 4u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_FEMALE_ROBBED_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_FEMALE_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_FEMALE_CAR_COLLISION_1, 7u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_FEMALE_CHAT_EVENT_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SUPERMODEL_FEMALE_CHAT_1, 8u);

		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetStewardMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_MALE_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_MALE_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_MALE_EVADE_1, 3u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_MALE_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_MALE_CHAT_1, 4u);

		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetStewardFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_FEMALE_1_HANDS_COWER_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_FEMALE_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_FEMALE_1_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STEWARD_FEMALE_1_CHAT_1, 5u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return 18 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetFanMaleTalkSfx(int16 sound, int32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_MALE_1_ATTACK_1, 3u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_MALE_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_MALE_1_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_MALE_1_CHAT_EVENT_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_MALE_1_CHAT_1, 6u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}

	if(model == MI_FAN_MAN2) sfx += 20;
	return sfx;
}

uint32
cAudioManager::GetFanFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_ROBBED: sfx = AUDIO_SAMPLE_PED_FAN_FEMALE_1_ROBBED_1; break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_FEMALE_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_FEMALE_1_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_FEMALE_1_CHAT_EVENT_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FAN_FEMALE_1_CHAT_1, 6u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return 18 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetHospitalMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_MALE_HANDS_COWER_1, 4u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_MALE_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_MALE_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_MALE_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_MALE_CHAT_1, 5u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHospitalFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_FEMALE_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_FEMALE_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_HOSPITAL_FEMALE_CHAT_1, 6u);

		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteConstructionWorkerTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CONSTRUCTION_WORKER_HANDS_COWER_1,
		          3u);
		break;
	case SOUND_PED_CAR_JACKED:
		sfx = AUDIO_SAMPLE_PED_WHITE_CONSTRUCTION_WORKER_CAR_JACKED_1;
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CONSTRUCTION_WORKER_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CONSTRUCTION_WORKER_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx,
		          AUDIO_SAMPLE_PED_WHITE_CONSTRUCTION_WORKER_CAR_COLLISION_1, 4u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CONSTRUCTION_WORKER_CHAT_SEXY_1,
		          3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_WHITE_CONSTRUCTION_WORKER_CHAT_1, 7u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackConstructionWorkerTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CONSTRUCTION_WORKER_HANDS_COWER_1,
		          3u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CONSTRUCTION_WORKER_CAR_JACKED_1,
		          2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CONSTRUCTION_WORKER_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CONSTRUCTION_WORKER_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx,
		          AUDIO_SAMPLE_PED_BLACK_CONSTRUCTION_WORKER_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CONSTRUCTION_WORKER_CHAT_SEXY_1,
		          4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BLACK_CONSTRUCTION_WORKER_CHAT_1, 4u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetShopperFemaleTalkSfx(int16 sound, int32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SHOPPER_FEMALE_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SHOPPER_FEMALE_1_ROBBED_1, 2u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SHOPPER_FEMALE_1_EVADE_1, 6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SHOPPER_FEMALE_1_CAR_COLLISION_1, 7u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SHOPPER_FEMALE_1_CHAT_EVENT_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SHOPPER_FEMALE_1_CHAT_1, 7u);
		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}

	if(model == MI_SHOPPER2) {
		sfx += 28;
	} else if(model == MI_SHOPPER3) {
		sfx += 56;
	}
	return sfx;
}

uint32
cAudioManager::GetStudentMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_MALE_HANDS_COWER_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_MALE_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_MALE_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_MALE_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_MALE_CAR_COLLISION_1, 4u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_MALE_CHAT_EVENT_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_MALE_CHAT_1, 5u);

		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetStudentFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_FEMALE_HANDS_COWER_1, 4u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_FEMALE_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_FEMALE_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_FEMALE_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_FEMALE_CAR_COLLISION_1, 4u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_FEMALE_CHAT_EVENT_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_STUDENT_FEMALE_CHAT_1, 4u);

		break;
	default: return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetCasualMaleOldTalkSfx(int16 sound)
{
	return GetGenericMaleTalkSfx(sound);
}

uint32
cAudioManager::GetSpecialCharacterTalkSfx(int32 modelIndex, int32 sound)
{
	char *modelName = CModelInfo::GetModelInfo(modelIndex)->GetName();
	if(strcmp(modelName, "eight") == 0 || strcmp(modelName, "eight2") == 0) {
		return GetEightTalkSfx(sound);
	}
	if(strcmp(modelName, "frankie") == 0) { return GetFrankieTalkSfx(sound); }
	if(strcmp(modelName, "misty") == 0) { return GetMistyTalkSfx(sound); }
	if(strcmp(modelName, "ojg") == 0 || strcmp(modelName, "ojg_p") == 0) {
		return GetOJGTalkSfx(sound);
	}
	if(strcmp(modelName, "cat") == 0) { return GetCatatalinaTalkSfx(sound); }
	if(strcmp(modelName, "bomber") == 0) { return GetBomberTalkSfx(sound); }
	if(strcmp(modelName, "s_guard") == 0) { return GetSecurityGuardTalkSfx(sound); }
	if(strcmp(modelName, "chunky") == 0) { return GetChunkyTalkSfx(sound); }
	if(strcmp(modelName, "asuka") == 0) { return GetGenericFemaleTalkSfx(sound); }
	if(strcmp(modelName, "maria") == 0) { return GetGenericFemaleTalkSfx(sound); }

	return GetGenericMaleTalkSfx(sound);
}
uint32
cAudioManager::GetEightTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_EIGHT_HANDS_UP_1, 2u);
		break;
	case SOUND_PED_ROBBED:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_EIGHT_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_EIGHT_ATTACK_1, 6u);
		break;
	case SOUND_PED_EVADE:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_EIGHT_EVADE_1, 7u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetFrankieTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FRANKIE_HANDS_UP_1, 4u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FRANKIE_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FRANKIE_ATTACK_1, 6u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FRANKIE_EVADE_1, 3u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetMistyTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MISTY_HANDS_UP_1, 5u);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MISTY_ROBBED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MISTY_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MISTY_EVADE_1, 5u); break;
	case SOUND_PED_TAXI_CALL:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MISTY_THUMB_LIFT_1, 4u);
		break;
	default: return GetGenericFemaleTalkSfx(sound); break;
	}
	return sfx;
}

uint32
cAudioManager::GetOJGTalkSfx(int16 sound)
{
	return GetGenericMaleTalkSfx(sound);
}

uint32
cAudioManager::GetCatatalinaTalkSfx(int16 sound)
{
	return GetGenericFemaleTalkSfx(sound);
}

uint32
cAudioManager::GetBomberTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	if(sound != SOUND_PED_BOMBER) return GetGenericMaleTalkSfx(sound);

	GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_BOMBER_THREAT_1, 7u);
	return sfx;
}

uint32
cAudioManager::GetSecurityGuardTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SECURITY_GUARD_HANDS_UP_1, 2u);
		break;
	case SOUND_PED_HANDS_COWER: sfx = AUDIO_SAMPLE_PED_SECURITY_GUARD_HANDS_COWER_1; break;
	case SOUND_PED_CAR_JACKED:
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SECURITY_GUARD_CAR_EVENT_1, 6u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SECURITY_GUARD_ATTACK_1, 2u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_SECURITY_GUARD_CAR_EVENT_1, 12u);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChunkyTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	if(sound == SOUND_PED_DEATH) return AUDIO_SAMPLE_PED_CHUNKY_DEATH_1;

	if(sound != SOUND_PED_FLEE_RUN) return GetGenericMaleTalkSfx(sound);

	GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_CHUNKY_FLEE_RUN_1, 5u);
	return sfx;
}

uint32
cAudioManager::GetGenericMaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_DEATH: GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_DEATH_1, 8u); break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_INJURED_PED_MALE_OUCH_1, 15u);
		break;
	case SOUND_PED_BURNING:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_BURNING_1, 8u);
		break;
	case SOUND_PED_FLEE_SPRINT:
		GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_MALE_FLEE_SPRINT_1, 6u);
		break;
	default: return NO_SAMPLE;
	}
	return sfx;
}

uint32
cAudioManager::GetGenericFemaleTalkSfx(int16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_DEATH:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_DEATH_1, 10u);
		break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_INJURED_PED_FEMALE_OUCH_1,
		                         11u);
		break;
	case SOUND_PED_BURNING:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_BURNING_1, 9u);
		break;
	case SOUND_PED_FLEE_SPRINT:
		cAudioManager::GetPhrase(&sfx, &lastSfx, AUDIO_SAMPLE_PED_FEMALE_FLEE_SPRINT_1, 8u);
		break;
	default: return NO_SAMPLE;
	}
	return sfx;
}

#if 1

WRAPPER
void
cAudioManager::ProcessActiveQueues()
{
	EAXJMP(0x57BA60);
}

#else
void
cAudioManager::ProcessActiveQueues()
{
	int v3;               // ecx
	cAudioManager *v4;    // edx
	tActiveSample *v5;    // ebx
	cAudioManager *v6;    // edi
	tActiveSample *v7;    // esi
	char v8;              // al
	unsigned __int8 v9;   // dl
	double v10;           // st7
	double v11;           // st6
	float a4;             // ST08_4
	float a3;             // ST04_4
	int activeSampleFreq; // ecx
	int freq;             // edi
	int newFreq;          // ecx
	int v17;              // eax
	char v18;             // al
	unsigned __int8 v19;  // al
	float v20;            // ST0C_4
	int v21;              // edx
	unsigned __int8 v22;  // bl
	cAudioManager *v23;   // ebp
	int v24;              // ecx
	cAudioManager *v25;   // edx
	tActiveSample *v26;   // ebx
	cAudioManager *v27;   // ebp
	unsigned int v28;     // edi
	unsigned int v29;     // eax
	unsigned __int8 v30;  // cl
	double v31;           // st4
	double v32;           // st7
	double v33;           // st6
	double v34;           // st5
	float v35;            // ST0C_4
	float v36;            // ST08_4
	float v37;            // ST04_4
	float v38;            // ST0C_4
	int v39;              // edx
	int v40;              // [esp+Ch] [ebp-58h]
	int v41;              // [esp+Ch] [ebp-58h]
	unsigned int v42;     // [esp+10h] [ebp-54h]
	int v43;              // [esp+10h] [ebp-54h]
	char v44;             // [esp+14h] [ebp-50h]
	unsigned __int8 v45;  // [esp+14h] [ebp-50h]
	unsigned __int8 l;    // [esp+24h] [ebp-40h]
	unsigned __int8 j;    // [esp+28h] [ebp-3Ch]
	unsigned __int8 k;    // [esp+34h] [ebp-30h]
	unsigned __int8 i;    // [esp+38h] [ebp-2Ch]
	CVector a2;           // [esp+48h] [ebp-1Ch]

	for(uint32 i = 0; i < m_bActiveSamples; i++) {
		m_asSamples[m_bActiveSampleQueue][i].m_bIsProcessed = 0;
		m_asActiveSamples[i].m_bIsProcessed = 0;
	}

	for(i = 0;; ++i) {
		v21 = m_bActiveSampleQueue;
		if(i >= m_bSampleRequestQueuesStatus[v21]) break;
		v3 = i + 27 * v21;
		v4 = (this + 2484 * v21);
		v5 = &v4->m_asSamples[m_abSampleQueueIndexTable[v3]];
		if(v4->m_asSamples[m_abSampleQueueIndexTable[v3]].m_nSampleIndex != NO_SAMPLE) {
			v6 = this;
			for(j = 0;; ++j) {
				if(j >= m_bActiveSamples) goto LABEL_58;
				v7 = m_asActiveSamples;
				if(v5->m_nEntityIndex == m_asActiveSamples[0].m_nEntityIndex &&
				   v5->field_4 == m_asActiveSamples[0].field_4 &&
				   v5->m_nSampleIndex == m_asActiveSamples[0].m_nSampleIndex) {
					break;
				}
			LABEL_56:
				v6 = (v6 + 92);
			}
			if(v5->m_nLoopCount) {
				if(m_FrameCounter & 1) {
					if(!(j & 1)) {
						v8 = 0;
						goto LABEL_17;
					}
				LABEL_16:
					v8 = 1;
				} else {
					if(!(j & 1)) goto LABEL_16;
					v8 = 0;
				}
			LABEL_17:
				if(v8 && !SampleManager.GetChannelUsedFlag(j)) {
					v5->m_bLoopEnded = 1;
					m_asActiveSamples[0].m_bLoopEnded = 1;
					m_asActiveSamples[0].m_nSampleIndex = NO_SAMPLE;
					v7->m_nEntityIndex = -5;
					goto LABEL_56;
				}
			}
			v5->m_bIsProcessed = 1;
			m_asActiveSamples[0].m_bIsProcessed = 1;
			v5->field_88 = -1;
			if(!v5->field_56) {
				if(v5->m_bIsDistant) {
					if(field_4) {
						v9 = v5->m_bEmittingVolume;
						if(v9 >= 63u)
							v42 = 63;
						else
							v42 = v9;
						v43 = 2 * v42;
					} else {
						v43 = v5->m_bEmittingVolume;
					}
					SampleManager.SetChannelFrequency(j, v5->m_nFrequency);
					SampleManager.SetChannelEmittingVolume(j, v43);
				} else {
					v10 = m_asActiveSamples[0].m_fDistance;
					v11 = v5->m_fDistance;
					m_asActiveSamples[0].m_fDistance = v5->m_fDistance;
					a4 = v11;
					a3 = v10;
					v5->m_nFrequency = ComputeDopplerEffectedFrequency(
					    v5->m_nFrequency, a3, a4, v5->field_48);
					activeSampleFreq = m_asActiveSamples[0].m_nFrequency;
					freq = v5->m_nFrequency;
					if(freq != activeSampleFreq) {
						if(freq <= activeSampleFreq) {
							if(activeSampleFreq - 6000 > freq)
								freq = activeSampleFreq - 6000;
							newFreq = freq;
						} else if(activeSampleFreq + 6000 >= freq) {
							newFreq = v5->m_nFrequency;
						} else {
							newFreq = activeSampleFreq + 6000;
						}
						v7->m_nFrequency = newFreq;
						SampleManager.SetChannelFrequency(j, newFreq);
					}
					v40 = v7->m_bEmittingVolume;
					v17 = v5->m_bEmittingVolume;
					if(v17 != v40) {
						if(v17 <= v40) {
							if(v40 - 10 > v17) v17 = v40 - 10;
							v41 = v17;
						} else if(v40 + 10 >= v17) {
							v41 = v5->m_bEmittingVolume;
						} else {
							v41 = v40 + 10;
						}
						if(field_4) {
							if(v41 >= 63)
								v18 = 63;
							else
								v18 = v41;
							v19 = 2 * v18;
						} else {
							v19 = v41;
						}
						SampleManager.SetChannelEmittingVolume(j, v19);
						v7->m_bEmittingVolume = v41;
					}
					TranslateEntity(&v5->m_vecPos, &a2);
					SampleManager.SetChannel3DPosition(j, a2.x, a2.y, a2.z);
					v20 = 0.25f * v5->m_fSoundIntensity;
					SampleManager.SetChannel3DDistances(
					    j, v5->m_fSoundIntensity, v20);
				}
				SampleManager.SetChannelReverbFlag(j, v5->m_bReverbFlag);
				continue;
			}
			v5->m_bIsProcessed = 0;
			m_asActiveSamples[0].m_bIsProcessed = 0;
			goto LABEL_56;
		}
	LABEL_58:;
	}
	v22 = 0;
	v23 = this;
	for(uint32 i = 0; v22 < m_bActiveSamples; i++) {
		if(v23->m_asActiveSamples[0].m_nSampleIndex != NO_SAMPLE &&
		   !v23->m_asActiveSamples[0].m_bIsProcessed) {
			SampleManager.StopChannel(i);
			v23->m_asActiveSamples[0].m_nSampleIndex = NO_SAMPLE;
			v23->m_asActiveSamples[0].m_nEntityIndex = -5;
		}
		v23 = (v23 + 92);
	}
	for(k = 0; k < m_bSampleRequestQueuesStatus[m_bActiveSampleQueue]; ++k) {
		v24 = k + 27 * v39;
		v25 = (this + 2484 * v39);
		v26 = &v25->m_asSamples[m_abSampleQueueIndexTable[v24]];
		if(!v25->m_asSamples[m_abSampleQueueIndexTable[v24]].m_bIsProcessed &&
		   !v25->m_asSamples[m_abSampleQueueIndexTable[v24]].m_bLoopEnded &&
		   m_asAudioEntities[v26->m_nEntityIndex].m_bIsUsed &&
		   v25->m_asSamples[m_abSampleQueueIndexTable[v24]].m_nSampleIndex < NO_SAMPLE) {
			if(v25->m_asSamples[m_abSampleQueueIndexTable[v24]].field_4 > 255u &&
			   v25->m_asSamples[m_abSampleQueueIndexTable[v24]].m_nLoopCount &&
			   v25->m_asSamples[m_abSampleQueueIndexTable[v24]].m_bLoopsRemaining) {
				--v25->m_asSamples[m_abSampleQueueIndexTable[v24]]
				      .m_bLoopsRemaining;
				v26->field_76 = 1;
			} else {
				v27 = this;
				for(l = 0; l < m_bActiveSamples; ++l) {
					if(!v27->m_asActiveSamples[0].m_bIsProcessed) {
						if(!v26->m_nLoopCount) goto LABEL_80;
						v28 = v26->m_nFrequency / field_19192;
						v29 = v26->m_nLoopCount *
						      SampleManager.GetSampleLength(
						          v26->m_nSampleIndex);
						if(v28) {
							v26->field_76 = v29 / v28 + 1;
						LABEL_80:
							memcpy(v27->m_asActiveSamples, v26, 92);
							if(!v27->m_asActiveSamples[0].m_bIsDistant)
								TranslateEntity(
								    &v27->m_asActiveSamples[0]
								         .m_vecPos,
								    &a2);
							if(field_4) {
								if(v27->m_asActiveSamples[0]
								       .m_bEmittingVolume >= 63u)
									v44 = 63;
								else
									v44 =
									    v27
									        ->m_asActiveSamples
									            [0]
									        .m_bEmittingVolume;
								v45 = 2 * v44;
							} else {
								v45 = v27->m_asActiveSamples[0]
								          .m_bEmittingVolume;
							}
							if(SampleManager.InitialiseChannel(
							       l,
							       v27->m_asActiveSamples[0]
							           .m_nSampleIndex,
							       v27->m_asActiveSamples[0]
							           .m_bBankIndex)) {
								SampleManager.SetChannelFrequency(
								    l, v27->m_asActiveSamples[0]
								           .m_nFrequency);
								cSampleManager
								    .SetChannelEmittingVolume(l,
								                              v45);
								SampleManager.SetChannelLoopPoints(
								    l,
								    v27->m_asActiveSamples[0]
								        .m_nLoopStart,
								    v27->m_asActiveSamples[0]
								        .m_nLoopEnd);
								SampleManager.SetChannelLoopCount(
								    l, v27->m_asActiveSamples[0]
								           .m_nLoopCount);
								SampleManager.SetChannelReverbFlag(
								    l, v27->m_asActiveSamples[0]
								           .m_bReverbFlag);
								if(v27->m_asActiveSamples[0]
								       .m_bIsDistant) {
									v30 = v27->m_asActiveSamples
									          [0]
									              .m_bOffset;
									if(v30 == 63) {
										v31 = 0.0f;
									} else if(v30 >= 63u) {
										v31 = (v30 - 63) *
										      15.873f;
									} else {
										v31 = -((63 - v30) *
										        15.873f);
									}
									v32 = v31;
									v33 = 0.0f;
									v34 = 0.0f;
									v27->m_asActiveSamples[0]
									    .m_fSoundIntensity =
									    100000.0f;
								} else {
									v32 = a2.x;
									v33 = a2.y;
									v34 = a2.z;
								}
								v35 = v34;
								v36 = v33;
								v37 = v32;
								SampleManager.SetChannel3DPosition(
								    l, v37, v36, v35);
								v38 = 0.25f *
								      v27->m_asActiveSamples[0]
								          .m_fSoundIntensity;
								cSampleManager
								    .SetChannel3DDistances(
								        l,
								        v27->m_asActiveSamples[0]
								            .m_fSoundIntensity,
								        v38);
								SampleManager.StartChannel(l);
							}
							v27->m_asActiveSamples[0].m_bIsProcessed =
							    1;
							v26->m_bIsProcessed = 1;
							v26->field_88 = -1;
							break;
						}
					}
					v27 = (v27 + 92);
				}
			}
		}
	}
}
#endif

bool
cAudioManager::ProcessAirBrakes(cVehicleParams *params)
{
	CAutomobile *automobile;
	uint8 rand;

	if(params->m_fDistance > 900.0f) return 0;
	automobile = (CAutomobile *)params->m_pVehicle;
	if(!automobile->bEngineOn) return 1;

	if((automobile->m_fVelocityChangeForAudio < 0.025f ||
	    params->m_fVelocityChange >= 0.025f) &&
	   (automobile->m_fVelocityChangeForAudio > -0.025f || params->m_fVelocityChange <= 0.025f))
		return 1;

	CalculateDistance((bool *)params, params->m_fDistance);
	rand = m_anRandomTable[0] % 10u + 70;
	m_sQueueSample.m_bVolume = ComputeVolume(rand, 30.0f, m_sQueueSample.m_fDistance);
	if(m_sQueueSample.m_bVolume) {
		m_sQueueSample.field_4 = 13;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_VEHICLE_AIR_BRAKES;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_VEHICLE_AIR_BRAKES);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.field_16 = 10;
		m_sQueueSample.m_nLoopCount = 1;
		m_sQueueSample.m_bEmittingVolume = rand;
		m_sQueueSample.m_nLoopStart = 0;
		m_sQueueSample.m_nLoopEnd = -1;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.field_56 = 1;
		m_sQueueSample.m_bReverbFlag = 1;
		m_sQueueSample.m_bRequireReflection = 0;
		AddSampleToRequestedQueue();
	}

	return 1;
}

void
cAudioManager::ProcessAirportScriptObject(uint8 sound)
{
	float dist;
	float distSquared;
	float maxDist;

	static uint8 counter = 0;

	uint32 time = CTimer::GetTimeInMilliseconds();
	if(time > audioLogicTimers[3]) {
		switch(sound) {
		case SCRIPT_SOUND_AIRPORT_LOOP_S:
			maxDist = 900.f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			break;
		case SCRIPT_SOUND_AIRPORT_LOOP_L:
			maxDist = 6400.f;
			m_sQueueSample.m_fSoundIntensity = 80.0f;
			break;
		default: break;
		}
		distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
		if(distSquared < maxDist) {
			dist = sqrt(distSquared);
			m_sQueueSample.m_fDistance = dist;
			m_sQueueSample.m_bVolume = ComputeVolume(
			    110u, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				m_sQueueSample.m_nSampleIndex =
				    (m_anRandomTable[1] & 3) + AUDIO_SAMPLE_AIRPORT_1;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.field_4 = counter++;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 2.0f;
				m_sQueueSample.m_bEmittingVolume = 110;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
				audioLogicTimers[3] = time + 10000 + m_anRandomTable[3] % 20000u;
			}
		}
	}
}

WRAPPER
bool
cAudioManager::ProcessBoatEngine(cVehicleParams *params)
{
	EAXJMP(0x56DE80);
}

WRAPPER
bool
cAudioManager::ProcessBoatMovingOverWater(cVehicleParams *params)
{
	EAXJMP(0x56E500);
}

WRAPPER
void
cAudioManager::ProcessBridge()
{
	EAXJMP(0x5790D0);
}

void
cAudioManager::ProcessBridgeMotor()
{
	if(m_sQueueSample.m_fDistance < 400.f) {
		m_sQueueSample.m_bVolume = ComputeVolume(127, 400.f, m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.field_4 = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_MOTOR;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_16 = 1;
			m_sQueueSample.m_nFrequency = 5500;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bEmittingVolume = 127;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_fSoundIntensity = 400.0f;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_76 = 3;
			m_sQueueSample.m_bReverbFlag = 0;
			AddSampleToRequestedQueue();
		}
	}
}

WRAPPER
void
cAudioManager::ProcessBridgeOneShots()
{
	EAXJMP(0x579310);
}

void
cAudioManager::ProcessBridgeWarning()
{
	if(CStats::CommercialPassed && m_sQueueSample.m_fDistance < 450.f) {
		m_sQueueSample.m_bVolume = ComputeVolume(100u, 450.f, m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.field_4 = 0;
			m_sQueueSample.m_nSampleIndex = 457;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_16 = 1;
			m_sQueueSample.m_nFrequency =
			    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_BRIDGE_WARNING);
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bEmittingVolume = 100;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_fSoundIntensity = 450.0f;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_76 = 8;
			m_sQueueSample.m_bReverbFlag = 0;
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
	}
}

WRAPPER
bool
cAudioManager::ProcessCarBombTick(void *)
{
	EAXJMP(0x56CC20);
}

WRAPPER
void
cAudioManager::ProcessCesna(void *)
{
	EAXJMP(0x56ADF0);
}

void
cAudioManager::ProcessCinemaScriptObject(uint8 sound)
{
	uint8 rand;
	float distSquared;
	float maxDist;

	static uint8 counter = 0;

	uint32 time = CTimer::GetTimeInMilliseconds();
	if(time > audioLogicTimers[4]) {
		switch(sound) {
		case SCRIPT_SOUND_CINEMA_LOOP_S:
			maxDist = 900.f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			break;
		case SCRIPT_SOUND_CINEMA_LOOP_L:
			maxDist = 6400.f;
			m_sQueueSample.m_fSoundIntensity = 80.0f;
			break;
		default: break;
		}
		distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
		if(distSquared < maxDist) {
			m_sQueueSample.m_fDistance = sqrt(distSquared);
			rand = m_anRandomTable[0] % 90u + 30;
			m_sQueueSample.m_bVolume = ComputeVolume(
			    rand, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				m_sQueueSample.m_nSampleIndex = counter % 3 + AUDIO_SAMPLE_CINEMA_1;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 2);
				m_sQueueSample.field_4 = counter++;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 2.0f;
				m_sQueueSample.m_bEmittingVolume = rand;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
				audioLogicTimers[4] = time + 1000 + m_anRandomTable[3] % 4000u;
			}
		}
	}
}

WRAPPER
void
cAudioManager::ProcessCrane()
{
	EAXJMP(0x578910);
}

void
cAudioManager::ProcessDocksScriptObject(uint8 sound)
{
	uint32 time;
	uint8 rand;
	float distSquared;
	float maxDist;

	static uint32 counter = 0;

	time = CTimer::GetTimeInMilliseconds();
	if(time > audioLogicTimers[5]) {
		switch(sound) {
		case SCRIPT_SOUND_DOCKS_LOOP_S:
			maxDist = 900.f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			break;
		case SCRIPT_SOUND_DOCKS_LOOP_L:
			maxDist = 6400.f;
			m_sQueueSample.m_fSoundIntensity = 80.0f;
			break;
		default: break;
		}
		distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
		if(distSquared < maxDist) {
			m_sQueueSample.m_fDistance = sqrt(distSquared);
			rand = m_anRandomTable[0] % 60u + 40;
			m_sQueueSample.m_bVolume = ComputeVolume(
			    rand, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_DOCKS;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.m_nFrequency =
				    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_DOCKS);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 3);
				m_sQueueSample.field_4 = counter++;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 2.0f;
				m_sQueueSample.m_bEmittingVolume = rand;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
				audioLogicTimers[5] = time + 10000 + m_anRandomTable[3] % 40000u;
			}
		}
	}
}

void
cAudioManager::ProcessEntity(int32 id)
{
	if(m_asAudioEntities[id].m_bStatus) {
		m_sQueueSample.m_nEntityIndex = id;
		switch(m_asAudioEntities[id].m_nType) {
		case AUDIOTYPE_PHYSICAL:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessPhysical(id);
			}
			break;
		case AUDIOTYPE_EXPLOSION:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessExplosions(id);
			}
			break;
		case AUDIOTYPE_FIRE:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessFires(id);
			}
			break;
		case AUDIOTYPE_WEATHER:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessWeather(id);
			}
			break;
		case AUDIOTYPE_CRANE:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessCrane();
			}
			break;
		case AUDIOTYPE_SCRIPTOBJECT:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessScriptObject(id);
			}
			break;
		case AUDIOTYPE_BRIDGE:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessBridge();
			}
			break;
		case AUDIOTYPE_FRONTEND:
			m_sQueueSample.m_bReverbFlag = 0;
			ProcessFrontEnd();
			break;
		case AUDIOTYPE_PROJECTILE:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessProjectiles();
			}
			break;
		case AUDIOTYPE_GARAGE:
			if(!m_bUserPause) ProcessGarages();
			break;
		case AUDIOTYPE_FIREHYDRANT:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessFireHydrant();
			}
			break;
		case AUDIOTYPE_WATERCANNON:
			if(!m_bUserPause) {
				m_sQueueSample.m_bReverbFlag = 1;
				ProcessWaterCannon(id);
			}
			break;
		default: return;
		}
	}
}

void
cAudioManager::ProcessExplosions(int32 explosion)
{
	uint8 type;
	CVector *pos;
	float maxDist;
	float distSquared;

	for(uint8 i = 0; i < 48u; i++) {
		if(CExplosion::GetExplosionActiveCounter(i) == 1) {
			CExplosion::ResetExplosionActiveCounter(i);
			type = CExplosion::GetExplosionType(i);
			switch(type) {
			case EXPLOSION_GRENADE:
			case EXPLOSION_ROCKET:
			case EXPLOSION_BARREL:
			case EXPLOSION_TANK_GRENADE:
				maxDist = 160000.f;
				m_sQueueSample.m_fSoundIntensity = 400.0f;
				m_sQueueSample.m_nSampleIndex =
				    AUDIO_SAMPLE_WEAPON_GRENADE_EXPLOSION;
				m_sQueueSample.m_nFrequency = RandomDisplacement(2000u) + 38000;
				m_sQueueSample.field_16 = 0;
				m_sQueueSample.m_bBankIndex = 0;
				break;
			case EXPLOSION_MOLOTOV:
				maxDist = 40000.f;
				m_sQueueSample.m_fSoundIntensity = 200.0f;
				m_sQueueSample.m_nSampleIndex =
				    AUDIO_SAMPLE_WEAPON_MOLOTOV_EXPLOSION;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000u) + 19000;
				m_sQueueSample.field_16 = 0;
				m_sQueueSample.m_bBankIndex = 0;
				break;
			case EXPLOSION_MINE:
			case EXPLOSION_HELI_BOMB:
				maxDist = 90000.f;
				m_sQueueSample.m_fSoundIntensity = 300.0f;
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_ROCKET_SHOT;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000u) + 12347;
				m_sQueueSample.field_16 = 0;
				m_sQueueSample.m_bBankIndex = 0;
				break;
			default:
				maxDist = 160000.f;
				m_sQueueSample.m_fSoundIntensity = 400.0f;
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_EXPLOSION_CAR;
				m_sQueueSample.m_nFrequency = RandomDisplacement(2000u) + 38000;
				if(type == EXPLOSION_HELI)
					m_sQueueSample.m_nFrequency =
					    8 * m_sQueueSample.m_nFrequency / 10u;
				m_sQueueSample.field_16 = 0;
				m_sQueueSample.m_bBankIndex = 0;
				break;
			}
			pos = CExplosion::GetExplosionPosition(i);
			m_sQueueSample.m_vecPos.x = pos->x;
			m_sQueueSample.m_vecPos.y = pos->y;
			m_sQueueSample.m_vecPos.z = pos->z;
			distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
			if(distSquared < maxDist) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_bVolume =
				    ComputeVolume(maxVolume, m_sQueueSample.m_fSoundIntensity,
				                  m_sQueueSample.m_fDistance);
				if(m_sQueueSample.m_bVolume) {
					m_sQueueSample.field_4 = i;
					m_sQueueSample.field_48 = 2.0f;
					m_sQueueSample.m_bIsDistant = 0;
					m_sQueueSample.m_nLoopCount = 1;
					m_sQueueSample.field_56 = 1;
					m_sQueueSample.m_bReverbFlag = 1;
					m_sQueueSample.m_bEmittingVolume = maxVolume;
					m_sQueueSample.m_nLoopStart = 0;
					m_sQueueSample.m_nLoopEnd = -1;
					m_sQueueSample.m_bReverbFlag = 1;
					m_sQueueSample.m_bRequireReflection = 1;
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::ProcessFireHydrant()
{
	float distSquared;
	bool something = false;

	m_sQueueSample.m_vecPos =
	    *(CVector *)((size_t)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity + 52);
	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < 1225.f) {
		CalculateDistance(&something, distSquared);
		m_sQueueSample.m_bVolume = ComputeVolume(40u, 35.f, m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.field_4 = 0;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_JUMBO_TAXI_SOUND;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_16 = 4;
			m_sQueueSample.m_nFrequency = 15591;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bEmittingVolume = 40;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_fSoundIntensity = 35.0f;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_76 = 3;
			m_sQueueSample.m_bReverbFlag = 1;
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
	}
}

WRAPPER
void
cAudioManager::ProcessFires(int32 entity)
{
	EAXJMP(0x575CD0);
}

void
cAudioManager::ProcessFrontEnd()
{
	bool processed;
	int16 sample;

	static uint32 counter = 0;

	for(uint32 i = 0; i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].field_24; i++) {
		processed = 0;
		switch(
		    m_asAudioEntities[0].m_awAudioEvent[i + 20 * m_sQueueSample.m_nEntityIndex]) {
		case SOUND_WEAPON_SNIPER_SHOT_NO_ZOOM:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_SNIPER_NO_ZOOM;
			break;
		case SOUND_WEAPON_ROCKET_SHOT_NO_ZOOM:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_ROCKET_NO_ZOOM;
			break;
		case SOUND_GARAGE_NO_MONEY:
		case SOUND_GARAGE_BAD_VEHICLE:
		case SOUND_3C:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PICKUP_FAIL_1;
			processed = 1;
			break;
		case SOUND_GARAGE_OPENING:
		case SOUND_GARAGE_BOMB1_SET:
		case SOUND_GARAGE_BOMB2_SET:
		case SOUND_GARAGE_BOMB3_SET:
		case SOUND_41:
		case SOUND_GARAGE_VEHICLE_DECLINED:
		case SOUND_GARAGE_VEHICLE_ACCEPTED:
		case SOUND_PICKUP_HEALTH:
		case SOUND_4B:
		case SOUND_PICKUP_ADRENALINE:
		case SOUND_PICKUP_ARMOUR:
		case SOUND_EVIDENCE_PICKUP:
		case SOUND_UNLOAD_GOLD:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PICKUP_SUCCESS_1;
			processed = 1;
			break;
		case SOUND_PICKUP_WEAPON_BOUGHT:
		case SOUND_PICKUP_WEAPON:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PICKUP_NEUTRAL_1;
			processed = 1;
			break;
		case SOUND_4A:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PICKUP_FAIL_1;
			processed = 1;
			break;
		case SOUND_PICKUP_BONUS:
		case SOUND_PICKUP_MONEY:
		case SOUND_PICKUP_HIDDEN_PACKAGE:
		case SOUND_PICKUP_PACMAN_PILL:
		case SOUND_PICKUP_PACMAN_PACKAGE:
		case SOUND_PICKUP_FLOAT_PACKAGE:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PICKUP_SUCCESS_3;
			processed = 1;
			break;
		case SOUND_PAGER: m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PAGER; break;
		case SOUND_RACE_START_3:
		case SOUND_RACE_START_2:
		case SOUND_RACE_START_1:
		case SOUND_CLOCK_TICK:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_CLOCK_TICK;
			break;
		case SOUND_RACE_START_GO:
			m_sQueueSample.m_nSampleIndex =
			    AUDIO_SAMPLE_FRONTEND_PART_MISSION_COMPLETED;
			break;
		case SOUND_PART_MISSION_COMPLETE:
			m_sQueueSample.m_nSampleIndex =
			    AUDIO_SAMPLE_FRONTEND_PART_MISSION_COMPLETED;
			break;
		case SOUND_FRONTEND_MENU_STARTING:
			processed = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_MENU_STARTING_1;
			break;
		case SOUND_FRONTEND_MENU_COMPLETED:
			processed = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_MENU_COMPLETED_1;
			break;
		case SOUND_FRONTEND_MENU_DENIED:
			processed = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_MENU_DENIED_1;
			break;
		case SOUND_FRONTEND_MENU_SUCCESS:
			processed = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_MENU_SUCCESS_1;
			break;
		case SOUND_FRONTEND_EXIT:
			processed = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_MENU_EXIT_1;
			break;
		case SOUND_9A:
			processed = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_380;
			break;
		case SOUND_9B: m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_382; break;
		case SOUND_FRONTEND_AUDIO_TEST:
			m_sQueueSample.m_nSampleIndex =
			    m_anRandomTable[0] % 3u + AUDIO_SAMPLE_FRONTEND_MENU_AUDIO_TEST_1;
			break;
		case SOUND_FRONTEND_FAIL:
			processed = 1;
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_MENU_FAIL_1;
			break;
		case SOUND_FRONTEND_NO_RADIO:
		case SOUND_FRONTEND_RADIO_CHANGE:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_GAMEPLAY_FAIL;
			break;
		case SOUND_A0:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRONTEND_GAMEPLAY_SUCCESS;
			break;
		default: continue;
		}

		sample =
		    m_asAudioEntities[0].m_awAudioEvent[i + 20 * m_sQueueSample.m_nEntityIndex];
		if(sample == AUDIO_SAMPLE_COLLISION_LOOPING_GRASS) {
			m_sQueueSample.m_nFrequency = 28509;
		} else if(sample == AUDIO_SAMPLE_PICKUP_NEUTRAL_1) {
			if(1.f ==
			   m_asAudioEntities[0].m_afVolume[i + 10 * m_sQueueSample.m_nEntityIndex])
				m_sQueueSample.m_nFrequency = 32000;
			else
				m_sQueueSample.m_nFrequency = 48000;
		} else {
			m_sQueueSample.m_nFrequency =
			    SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		}
		m_sQueueSample.m_bVolume = 110;
		m_sQueueSample.field_4 = counter++;
		m_sQueueSample.m_nLoopCount = 1;
		m_sQueueSample.field_56 = 1;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.field_16 = 0;
		m_sQueueSample.m_bIsDistant = 1;
		m_sQueueSample.m_bEmittingVolume = m_sQueueSample.m_bVolume;
		m_sQueueSample.m_nLoopStart = 0;
		m_sQueueSample.m_nLoopEnd = -1;
		if(processed)
			m_sQueueSample.m_bOffset = m_anRandomTable[0] & 0x1F;
		else
			m_sQueueSample.m_bOffset = 63;
		m_sQueueSample.m_bReverbFlag = 0;
		m_sQueueSample.m_bRequireReflection = 0;
		AddSampleToRequestedQueue();
		if(processed) {
			++m_sQueueSample.m_nSampleIndex;
			m_sQueueSample.field_4 = counter++;
			m_sQueueSample.m_bOffset = 127 - m_sQueueSample.m_bOffset;
			AddSampleToRequestedQueue();
		}
	}
}

WRAPPER
void
cAudioManager::ProcessGarages()
{
	EAXJMP(0x578C20);
}

void
cAudioManager::ProcessHomeScriptObject(uint8 sound)
{
	uint32 time;
	uint8 rand;
	float dist;
	float maxDist;

	static uint8 counter = 0;

	time = CTimer::GetTimeInMilliseconds();
	if(time > audioLogicTimers[6]) {
		switch(sound) {
		case SCRIPT_SOUND_HOME_LOOP_S:
			maxDist = 900.f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			break;
		case SCRIPT_SOUND_HOME_LOOP_L:
			maxDist = 6400.f;
			m_sQueueSample.m_fSoundIntensity = 80.0f;
			break;
		default: break;
		}
		dist = GetDistanceSquared(&m_sQueueSample.m_vecPos);
		if(dist < maxDist) {
			m_sQueueSample.m_fDistance = sqrt(dist);
			rand = m_anRandomTable[0] % 30u + 40;
			m_sQueueSample.m_bVolume = ComputeVolume(
			    rand, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				m_sQueueSample.m_nSampleIndex =
				    m_anRandomTable[0] % 5u + AUDIO_SAMPLE_HOME_1;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
				m_sQueueSample.field_4 = counter++;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_bEmittingVolume = rand;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 1;
				AddSampleToRequestedQueue();
				audioLogicTimers[6] = time + 1000 + m_anRandomTable[3] % 4000u;
			}
		}
	}
}

void
cAudioManager::ProcessJumbo(cVehicleParams *params)
{
	CPlane *plane;
	float position;

	if(params->m_fDistance < 193600.0f) {
		CalculateDistance((bool *)params, params->m_fDistance);
		plane = (CPlane *)params->m_pVehicle;
		DoJumboVolOffset();
		position = PlanePathPosition[plane->m_nPlaneId];
		if(position <= TakeOffPoint) {
			if(plane->m_fSpeed <= 0.10334f) {
				ProcessJumboTaxi();
				return;
			}

			ProcessJumboAccel(plane);
		} else if(300.0f + TakeOffPoint >= position) {
			ProcessJumboTakeOff(plane);
		} else if(LandingPoint - 350.0f >= position) {
			ProcessJumboFlying();
		} else {
			if(position > LandingPoint) {
				if(plane->m_fSpeed > 0.10334f) {
					ProcessJumboDecel(plane);
					return;
				}
				ProcessJumboTaxi();
				return;
			}
			ProcessJumboLanding(plane);
		}
	}
}

void
cAudioManager::ProcessJumboAccel(CPlane *plane)
{
	int32 engineFreq;
	int32 vol;
	float whineSoundFreq;
	float modificator;

	if(SetupJumboFlySound(20u)) {
		modificator = (plane->m_fSpeed - 0.10334f) * 1.676f;
		if(modificator > 1.0f) modificator = 1.0f;
		if(cAudioManager::SetupJumboRumbleSound(maxVolume * modificator) &&
		   SetupJumboTaxiSound((1.0f - modificator) * 75.f)) {
			if(modificator < 0.2f) {
				whineSoundFreq = modificator * 5.f * 14600.0f + 29500;
				vol = modificator * 5.f * maxVolume;
				engineFreq = modificator * 5.f * 6050.f + 16000;
			} else {
				whineSoundFreq = 44100;
				engineFreq = 22050;
				vol = maxVolume;
			}
			SetupJumboEngineSound(vol, engineFreq);
			SetupJumboWhineSound(18u, whineSoundFreq);
		}
	}
}

void
cAudioManager::ProcessJumboDecel(CPlane *plane)
{
	float modificator;

	if(SetupJumboFlySound(20u) && SetupJumboTaxiSound(75u)) {
		modificator = (plane->m_fSpeed - 0.10334f) * 1.676f;
		if(modificator > 1.0f) modificator = 1.0f;
		SetupJumboEngineSound(maxVolume * modificator, 6050.f * modificator + 16000);
		SetupJumboWhineSound(18u, 29500);
	}
}

void
cAudioManager::ProcessJumboFlying()
{
	if(SetupJumboFlySound(127u)) SetupJumboEngineSound(63u, 22050);
}

void
cAudioManager::ProcessJumboLanding(CPlane *plane)
{
	float modificator = (LandingPoint - PlanePathPosition[plane->m_nPlaneId]) * 0.0028571f;
	if(SetupJumboFlySound(107.f * modificator + 20)) {
		if(SetupJumboTaxiSound(75.f * (1.f - modificator))) {
			SetupJumboEngineSound(maxVolume, 22050);
			SetupJumboWhineSound(18.f * (1.f - modificator),
			                     14600.f * modificator + 29500);
		}
	}
}

void
cAudioManager::ProcessJumboTakeOff(CPlane *plane)
{
	double modificator = (PlanePathPosition[plane->m_nPlaneId] - TakeOffPoint) * 0.0033333f;

	if(cAudioManager::SetupJumboFlySound((107.f * modificator) + 20) &&
	   cAudioManager::SetupJumboRumbleSound(maxVolume * (1.f - modificator))) {
		if(cAudioManager::SetupJumboEngineSound(127u, 22050))
			cAudioManager::SetupJumboWhineSound(18.f * (1.f - modificator), 44100);
	}
}

void
cAudioManager::ProcessJumboTaxi()
{
	if(SetupJumboFlySound(20u)) {
		if(SetupJumboTaxiSound(75u)) SetupJumboWhineSound(18u, 29500);
	}
}

void
cAudioManager::ProcessLaunderetteScriptObject(uint8 sound)
{
	float maxDist;
	float distSquared;

	switch(sound) {
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_S:
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_L:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		break;
	default: break;
	}
	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < maxDist) {
		m_sQueueSample.m_fDistance = sqrt(distSquared);
		m_sQueueSample.m_bVolume = ComputeVolume(45u, m_sQueueSample.m_fSoundIntensity,
		                                         m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_LAUNDERETTE_1;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_nFrequency =
			    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_LAUNDERETTE_1);
			m_sQueueSample.field_4 = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_16 = 5;
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_bEmittingVolume = 45;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_bReverbFlag = 1;
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
		m_sQueueSample.m_bVolume = ComputeVolume(110u, m_sQueueSample.m_fSoundIntensity,
		                                         m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_LAUNDERETTE_2;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_nFrequency =
			    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_LAUNDERETTE_2);
			m_sQueueSample.field_4 = 1;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_16 = 3;
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_bEmittingVolume = 110;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_bReverbFlag = 1;
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessLoopingScriptObject(uint8 sound)
{
	uint8 emittingVolume;
	float maxDist;
	float distSquared;

	switch(sound) {
	case SCRIPT_SOUND_PARTY_1_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_1;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_1);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_1_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_1;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_1);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_2_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_2;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_2);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_2_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_2;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_2);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_3_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_3;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_3);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_3_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_3;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_3);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_4_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_4;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_4);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_4_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_4;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_4);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_5_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_5;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_5);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_5_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_5;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_5);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_6_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_6;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_6);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_6_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_6;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_6);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_7_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_7;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_7);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_7_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_7;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_7);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_8_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_8;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_8);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_8_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_8;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_8);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_9_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_9;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_9);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_9_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_9;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_9);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_10_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_10;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_10);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_10_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_10;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_10);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_11_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_11;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_11);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_11_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_11;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_11);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_12_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_12;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_12);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_12_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_12;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_12);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_13_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_13;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_13);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_13_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_13;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_13);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_1_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_STRIP_CLUB_1;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_STRIP_CLUB_1);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_1_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_STRIP_CLUB_1;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_STRIP_CLUB_1);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_2_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_STRIP_CLUB_2;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_STRIP_CLUB_2);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_2_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_STRIP_CLUB_2;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_STRIP_CLUB_2);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_WORK_SHOP_LOOP_S:
	case SCRIPT_SOUND_WORK_SHOP_LOOP_L:
		cAudioManager::ProcessWorkShopScriptObject(sound);
		return;
	case SCRIPT_SOUND_SAWMILL_LOOP_S:
	case SCRIPT_SOUND_SAWMILL_LOOP_L: cAudioManager::ProcessSawMillScriptObject(sound); return;
	case SCRIPT_SOUND_38:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_409;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_409);
		m_sQueueSample.field_16 = 6;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_39:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_409;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_409);
		m_sQueueSample.field_16 = 6;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_S:
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_L: ProcessLaunderetteScriptObject(sound); return;
	case SCRIPT_SOUND_CHINATOWN_RESTAURANT_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_CHINATOWN_RESTAURANT;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_CHINATOWN_RESTAURANT);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_CHINATOWN_RESTAURANT_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_CHINATOWN_RESTAURANT;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_CHINATOWN_RESTAURANT);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_CIPRIANI_RESAURANT_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_CIPRIANI_RESTAURANT;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_CIPRIANI_RESTAURANT);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_CIPRIANI_RESAURANT_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_CIPRIANI_RESTAURANT;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_CIPRIANI_RESTAURANT);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_46:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_414;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_414);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_47:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_414;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_414);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_MARCO_BISTRO_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_MARCO_BISTRO;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_MARCO_BISTRO);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_MARCO_BISTRO_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_MARCO_BISTRO;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 110;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_MARCO_BISTRO);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_AIRPORT_LOOP_S:
	case SCRIPT_SOUND_AIRPORT_LOOP_L: ProcessAirportScriptObject(sound); return;
	case SCRIPT_SOUND_SHOP_LOOP_S:
	case SCRIPT_SOUND_SHOP_LOOP_L: ProcessShopScriptObject(sound); return;
	case SCRIPT_SOUND_CINEMA_LOOP_S:
	case SCRIPT_SOUND_CINEMA_LOOP_L: ProcessCinemaScriptObject(sound); return;
	case SCRIPT_SOUND_DOCKS_LOOP_S:
	case SCRIPT_SOUND_DOCKS_LOOP_L: cAudioManager::ProcessDocksScriptObject(sound); return;
	case SCRIPT_SOUND_HOME_LOOP_S:
	case SCRIPT_SOUND_HOME_LOOP_L: cAudioManager::ProcessHomeScriptObject(sound); return;
	case SCRIPT_SOUND_FRANKIE_PIANO:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FRANKIE_PIANO;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_FRANKIE_PIANO);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_1_LOOP:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PARTY_1;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PARTY_1);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_1_S:
	case SCRIPT_SOUND_PORN_CINEMA_1_L:
	case SCRIPT_SOUND_PORN_CINEMA_2_S:
	case SCRIPT_SOUND_PORN_CINEMA_2_L:
	case SCRIPT_SOUND_PORN_CINEMA_3_S:
	case SCRIPT_SOUND_PORN_CINEMA_3_L:
	case SCRIPT_SOUND_MISTY_SEX_S:
	case SCRIPT_SOUND_MISTY_SEX_L: ProcessPornCinema(sound); return;
	case SCRIPT_SOUND_BANK_ALARM_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_BANK_ALARM;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 90;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_BANK_ALARM);
		m_sQueueSample.field_16 = 2;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_BANK_ALARM_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_BANK_ALARM;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 90;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_BANK_ALARM);
		m_sQueueSample.field_16 = 2;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_POLICE_BALL_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_POLICE_BALL;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_POLICE_BALL);
		m_sQueueSample.field_16 = 2;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_POLICE_BALL_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_POLICE_BALL;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_POLICE_BALL);
		m_sQueueSample.field_16 = 2;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_LOOP_INDUSTRIAL_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_RAVE_INDUSTRIAL;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_RAVE_INDUSTRIAL);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_LOOP_INDUSTRIAL_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_RAVE_INDUSTRIAL;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_RAVE_INDUSTRIAL);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_POLICE_CELL_BEATING_LOOP_S:
	case SCRIPT_SOUND_POLICE_CELL_BEATING_LOOP_L:
		cAudioManager::ProcessPoliceCellBeatingScriptObject(sound);
		return;
	case SCRIPT_SOUND_RAVE_1_LOOP_S:
	case SCRIPT_SOUND_RAVE_2_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_RAVE_1;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_1_LOOP_L:
	case SCRIPT_SOUND_RAVE_2_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_RAVE_1;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_3_LOOP_S:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_RAVE_2;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_RAVE_2);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_3_LOOP_L:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_RAVE_2;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_RAVE_2);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_76 = 3;
		m_sQueueSample.field_48 = 2.0f;
		break;
	case SCRIPT_SOUND_PRETEND_FIRE_LOOP:
		maxDist = 2500.f;
		m_sQueueSample.m_fSoundIntensity = 50.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_FIRE_ENTITY;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 80;
		m_sQueueSample.m_nFrequency =
		    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_FIRE_ENTITY);
		m_sQueueSample.field_16 = 8;
		m_sQueueSample.field_76 = 10;
		m_sQueueSample.field_48 = 2.0f;
		break;
	default: return;
	}

	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < maxDist) {
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_bVolume = ComputeVolume(
		    emittingVolume, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.field_4 = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.m_bReverbFlag = 1;
			m_sQueueSample.m_bEmittingVolume = emittingVolume;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessOneShotScriptObject(uint8 sound)
{
	CPlayerPed *playerPed;
	uint8 emittingVolume;
	float maxDist;
	float distSquared;

	cPedParams male;
	cPedParams female;

	static uint8 iSound = 0;

	switch(sound) {
	case SCRIPT_SOUND_INJURED_PED_MALE_OUCH_S:
	case SCRIPT_SOUND_INJURED_PED_MALE_OUCH_L:
		male.m_pPed = nil;
		male.m_bDistanceCalculated = 0;
		male.m_fDistance = GetDistanceSquared(&m_sQueueSample.m_vecPos);
		cAudioManager::SetupPedComments(&male, SOUND_INJURED_PED_MALE_OUCH);
		return;
	case SCRIPT_SOUND_INJURED_PED_FEMALE_OUCH_S:
	case SCRIPT_SOUND_INJURED_PED_FEMALE_OUCH_L:
		female.m_pPed = nil;
		female.m_bDistanceCalculated = 0;
		female.m_fDistance = GetDistanceSquared(&m_sQueueSample.m_vecPos);
		cAudioManager::SetupPedComments(&female, SOUND_INJURED_PED_FEMALE);
		return;
	case SCRIPT_SOUND_GATE_START_CLUNK:
	case SCRIPT_SOUND_GATE_STOP_CLUNK:
		maxDist = 1600.f;
		m_sQueueSample.m_fSoundIntensity = 40.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_COLLISION_GATE;
		m_sQueueSample.m_bBankIndex = 0;
		if(sound == SCRIPT_SOUND_GATE_START_CLUNK)
			m_sQueueSample.m_nFrequency = 10600;
		else
			m_sQueueSample.m_nFrequency = 9000;
		m_sQueueSample.field_16 = 1;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.m_bRequireReflection = 1;
		emittingVolume = RandomDisplacement(10u) + 50;
		break;
	case SCRIPT_SOUND_BULLET_HIT_GROUND_1:
	case SCRIPT_SOUND_BULLET_HIT_GROUND_2:
	case SCRIPT_SOUND_BULLET_HIT_GROUND_3:
		maxDist = 2500.f;
		m_sQueueSample.m_fSoundIntensity = 50.0f;
		m_sQueueSample.m_nSampleIndex =
		    m_anRandomTable[iSound % 5] % 3u + AUDIO_SAMPLE_BULLET_HIT_GROUND_1;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
		m_sQueueSample.field_16 = 9;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		emittingVolume = m_anRandomTable[2] % 20 + 90;
		break;
	case SCRIPT_SOUND_110:
	case SCRIPT_SOUND_111:
		if(cSampleManager.IsSampleBankLoaded(0) != 1) return;
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_389;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_389);
		m_sQueueSample.field_16 = 0;
		m_sQueueSample.field_48 = 2.0f;
		m_sQueueSample.m_bIsDistant = 0;
		break;
	case SCRIPT_SOUND_PAYPHONE_RINGING:
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PAYPHONE_RINGING;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 80;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_PAYPHONE_RINGING);
		m_sQueueSample.field_16 = 1;
		m_sQueueSample.field_48 = 2.0f;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.m_bRequireReflection = 0;
		break;
	case SCRIPT_SOUND_GLASS_BREAK_L:
		maxDist = 3600.f;
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_GLASS_GENERIC_BREAK;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 70;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_GLASS_GENERIC_BREAK);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		break;
	case SCRIPT_SOUND_GLASS_BREAK_S:
		maxDist = 3600.f;
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_GLASS_GENERIC_BREAK;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 60;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_GLASS_GENERIC_BREAK);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		break;
	case SCRIPT_SOUND_GLASS_CRACK:
		maxDist = 3600.f;
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_GLASS_WINDSHIELD_CRACK;
		m_sQueueSample.m_bBankIndex = 0;
		emittingVolume = 70;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_GLASS_WINDSHIELD_CRACK);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.m_bRequireReflection = 1;
		break;
	case SCRIPT_SOUND_GLASS_LIGHT_BREAK:
		maxDist = 3025.f;
		m_sQueueSample.m_fSoundIntensity = 55.0f;
		m_sQueueSample.m_nSampleIndex =
		    (m_anRandomTable[4] & 3) + AUDIO_SAMPLE_GLASS_LIGHT_BREAK_1;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(2000u) + 19000;
		m_sQueueSample.field_16 = 9;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		emittingVolume = RandomDisplacement(11u) + 25;
		break;
	case SCRIPT_SOUND_BOX_DESTROYED_1:
		maxDist = 3600.f;
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_BOX_DESTROYED_1;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(1500u) + 18600;
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.m_bRequireReflection = 1;
		emittingVolume = m_anRandomTable[2] % 20 + 80;
		break;
	case SCRIPT_SOUND_BOX_DESTROYED_2:
		maxDist = 3600.f;
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_BOX_DESTROYED_2;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(1500u) + 18600;
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.m_bRequireReflection = 1;
		emittingVolume = m_anRandomTable[2] % 20 + 80;
		break;
	case SCRIPT_SOUND_METAL_COLLISION:
		maxDist = 3600.f;
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex =
		    m_anRandomTable[3] % 5u + AUDIO_SAMPLE_COLLISION_METAL;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.m_bRequireReflection = 1;
		emittingVolume = m_anRandomTable[2] % 30 + 70;
		break;
	case SCRIPT_SOUND_TIRE_COLLISION:
		maxDist = 3600.f;
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_COLLISION_RUBBER;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.m_nFrequency =
		    cSampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
		m_sQueueSample.field_16 = 3;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		m_sQueueSample.m_bRequireReflection = 1;
		emittingVolume = m_anRandomTable[2] % 30 + 60;
		break;
	case SCRIPT_SOUND_GUNSHELL_DROP:
		playerPed = FindPlayerPed();
		if(playerPed) {
			switch(playerPed->m_nSurfaceTouched) {
			case SURFACE_GRASS:
			case SURFACE_DIRT:
			case SURFACE_DIRTTRACK:
			case SURFACE_SCAFFOLD:
			case SURFACE_FLESH:
			case SURFACE_SAND:
			case SURFACE_TIRE:
			case SURFACE_HEDGE:
				m_sQueueSample.m_nSampleIndex =
				    AUDIO_SAMPLE_BULLET_GUNSHELL_SOFT_DROP;
				m_sQueueSample.m_nFrequency = RandomDisplacement(500u) + 11000;
				m_sQueueSample.field_16 = 18;
				maxDist = 400.f;
				m_sQueueSample.m_fSoundIntensity = 20.0f;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_bIsDistant = 0;
				emittingVolume = m_anRandomTable[2] % 20 + 30;
				distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
				if(distSquared < maxDist) {
					m_sQueueSample.m_fDistance = Sqrt(distSquared);
					m_sQueueSample.m_bVolume = ComputeVolume(
					    emittingVolume, m_sQueueSample.m_fSoundIntensity,
					    m_sQueueSample.m_fDistance);
					if(m_sQueueSample.m_bVolume) {
						m_sQueueSample.field_4 = iSound++;
						m_sQueueSample.m_nLoopCount = 1;
						m_sQueueSample.field_56 = 1;
						m_sQueueSample.m_bEmittingVolume = emittingVolume;
						m_sQueueSample.m_nLoopStart = 0;
						m_sQueueSample.m_nLoopEnd = -1;
						m_sQueueSample.m_bReverbFlag = 1;
						AddSampleToRequestedQueue();
					}
				}
				return;
			case SURFACE_PUDDLE: return;
			default: break;
			}
		}
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_BULLET_GUNSHELL_HARD_DROP;
		m_sQueueSample.m_nFrequency = RandomDisplacement(750u) + 18000;
		m_sQueueSample.field_16 = 15;
		maxDist = 400.f;
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		emittingVolume = m_anRandomTable[2] % 20 + 30;
		break;
	case SCRIPT_SOUND_GUNSHELL_DROP_SOFT:
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_BULLET_GUNSHELL_SOFT_DROP;
		m_sQueueSample.m_nFrequency = RandomDisplacement(500u) + 11000;
		m_sQueueSample.field_16 = 18;
		maxDist = 400.f;
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		m_sQueueSample.m_bBankIndex = 0;
		m_sQueueSample.field_48 = 0.0f;
		m_sQueueSample.m_bIsDistant = 0;
		emittingVolume = m_anRandomTable[2] % 20 + 30;
		break;
	default: return;
	}

	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < maxDist) {
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_bVolume = ComputeVolume(
		    emittingVolume, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.field_4 = iSound++;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.field_56 = 1;
			m_sQueueSample.m_bEmittingVolume = emittingVolume;
			m_sQueueSample.m_nLoopStart = 0;
			m_sQueueSample.m_nLoopEnd = -1;
			m_sQueueSample.m_bReverbFlag = 1;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessPed(CPhysical *ped)
{
	cPedParams params;

	params.m_pPed = 0;
	params.m_bDistanceCalculated = 0;
	params.m_fDistance = 0.0f;

	m_sQueueSample.m_vecPos = ped->GetPosition();

	params.m_bDistanceCalculated = 0;
	params.m_pPed = (CPed *)ped;
	params.m_fDistance = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(ped->m_modelIndex == MI_FATMALE02) ProcessPedHeadphones(&params);
	ProcessPedOneShots(&params);
}

void
cAudioManager::ProcessPedHeadphones(cPedParams *params)
{
	CPed *ped;
	CVehicle *veh;
	uint8 emittingVol;

	if(params->m_fDistance < 49.f) {
		ped = params->m_pPed;
		if(!(ped->m_ped_flagA20) || ped->m_bodyPartBleeding != 2) {
			CalculateDistance((bool *)params, params->m_fDistance);
			if(ped->bInVehicle && ped->m_nPedState == PED_DRIVING) {
				emittingVol = 10;
				veh = ped->m_pMyVehicle;
				if(veh && veh->m_type == 0) {
					for(int32 i = 2; i < 6; i++) {
						if(!veh->IsDoorClosed((eDoors)i) ||
						   veh->IsDoorMissing((eDoors)i)) {
							emittingVol = 42;
							break;
						}
					}
				}
			} else {
				emittingVol = 42;
			}

			m_sQueueSample.m_bVolume =
			    ComputeVolume(emittingVol, 7.f, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				m_sQueueSample.field_4 = 64;
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HEADPHONES;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_16 = 5;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_PED_HEADPHONES);
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_nLoopStart =
				    cSampleManager.GetSampleLoopStartOffset(
				        m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nLoopEnd = cSampleManager.GetSampleLoopEndOffset(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.field_48 = 4.0f;
				m_sQueueSample.m_fSoundIntensity = 7.0f;
				m_sQueueSample.field_56 = 0;
				m_sQueueSample.field_76 = 5;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
			}
			return;
		}
	}
}

void
cAudioManager::ProcessPedOneShots(cPedParams *params)
{
	uint8 emittingVol;
	int32 sampleIndex;

	CPed *ped = params->m_pPed;

	char processed;
	int16 sound;
	char noReflection;
	CWeapon *weapon;
	uint16 i;
	float maxDist;

	static uint8 iSound = 21;

	i = 0;
	weapon = nil;
	while(i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].field_24) {
		noReflection = 0;
		processed = 0;
		m_sQueueSample.m_bRequireReflection = 0;
		sound = m_asAudioEntities[0].m_awAudioEvent[i + 20 * m_sQueueSample.m_nEntityIndex];
		switch(sound) {
		case SOUND_STEP_START:
		case SOUND_STEP_END:
			if(!params->m_pPed->bIsLooking) {
				emittingVol = m_anRandomTable[3] % 15u + 45;
				if(FindPlayerPed() !=
				   m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity)
					emittingVol >>= 1;
				maxDist = 400.f;
				switch(params->m_pPed->m_nSurfaceTouched) {
				case SURFACE_GRASS:
					sampleIndex =
					    m_anRandomTable[1] % 5u + AUDIO_SAMPLE_PED_FALL_GRASS_1;
					break;
				case SURFACE_DIRT:
				case SURFACE_DIRTTRACK:
					sampleIndex =
					    m_anRandomTable[4] % 5u + AUDIO_SAMPLE_PED_FALL_DIRT_1;
					break;
				case SURFACE_METAL6:
				case SURFACE_METAL_DOOR:
				case SURFACE_BILLBOARD:
				case SURFACE_STEEL:
				case SURFACE_METAL_POLE:
				case SURFACE_STREET_LIGHT:
				case SURFACE_METAL14:
				case SURFACE_METAL15:
				case SURFACE_METAL_FENCE:
				case SURFACE_METAL27:
				case SURFACE_METAL28:
					sampleIndex =
					    m_anRandomTable[0] % 5u + AUDIO_SAMPLE_PED_FALL_METAL_1;
					break;
				case SURFACE_SAND:
					sampleIndex =
					    (m_anRandomTable[4] & 3) + AUDIO_SAMPLE_PED_FALL_SAND_1;
					break;
				case SURFACE_PUDDLE:
					sampleIndex = (m_anRandomTable[3] & 3) +
					              AUDIO_SAMPLE_PED_FALL_IN_WATER_1;
					break;
				case SURFACE_WOOD:
				case SURFACE_WOOD_BOX:
				case SURFACE_WOOD_PLANK:
					sampleIndex =
					    m_anRandomTable[2] % 5u + AUDIO_SAMPLE_PED_FALL_WOOD_1;
					break;
				case SURFACE_HEDGE:
					sampleIndex =
					    m_anRandomTable[2] % 5u + AUDIO_SAMPLE_COLLISION_HEDGE;
					break;
				default:
					sampleIndex = m_anRandomTable[2] % 5u +
					              AUDIO_SAMPLE_PED_FALL_PAVEMENT_1;
					break;
				}
				m_sQueueSample.m_nSampleIndex = sampleIndex;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 =
				    m_asAudioEntities[0]
				        .m_awAudioEvent[i + 20 * m_sQueueSample.m_nEntityIndex] -
				    28;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency / 17u);
				switch(params->m_pPed->m_nMoveState) {
				case 2:
					emittingVol >>= 2;
					m_sQueueSample.m_nFrequency =
					    9 * m_sQueueSample.m_nFrequency / 10u;
					break;
				case 3:
					emittingVol >>= 1;
					m_sQueueSample.m_nFrequency =
					    11 * m_sQueueSample.m_nFrequency / 10u;
					break;
				case 4:
					m_sQueueSample.m_nFrequency =
					    12 * m_sQueueSample.m_nFrequency / 10u;
					break;
				default: break;
				}
				m_sQueueSample.field_16 = 5;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 20.0f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.m_bRequireReflection = 1;
				goto LABEL_84;
			}
			break;
		case SOUND_FALL_LAND:
		case SOUND_FALL_COLLAPSE:
			if(!ped->bIsLooking) {
				maxDist = 900.f;
				emittingVol = m_anRandomTable[3] % 20 + 80;
				if(ped->m_nSurfaceTouched == SURFACE_PUDDLE) {
					m_sQueueSample.m_nSampleIndex =
					    (m_anRandomTable[3] & 3) +
					    AUDIO_SAMPLE_PED_FALL_IN_WATER_1;
				} else if(sound == SOUND_FALL_LAND) {
					m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_FALL_LAND;
				} else {
					m_sQueueSample.m_nSampleIndex =
					    AUDIO_SAMPLE_PED_FALL_COLLAPSE;
				}
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency / 17u);
				m_sQueueSample.field_16 = 2;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 30.0f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.m_bRequireReflection = 1;
				goto LABEL_84;
			}
			break;
		case SOUND_21:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_1;
			m_sQueueSample.m_nFrequency = 18000;
			goto LABEL_81;
		case SOUND_22:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_1;
			m_sQueueSample.m_nFrequency = 16500;
			goto LABEL_81;
		case SOUND_23:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_1;
			goto LABEL_80;
		case SOUND_24:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_2;
			m_sQueueSample.m_nFrequency = 18000;
			goto LABEL_81;
		case SOUND_25:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_2;
			m_sQueueSample.m_nFrequency = 16500;
			goto LABEL_81;
		case SOUND_26:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_2;
			goto LABEL_80;
		case SOUND_WEAPON_PUNCH_ATTACK:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_3;
			m_sQueueSample.m_nFrequency = 18000;
			goto LABEL_81;
		case SOUND_28:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_3;
			m_sQueueSample.m_nFrequency = 16500;
			goto LABEL_81;
		case SOUND_29:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_3;
			goto LABEL_80;
		case SOUND_2A:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_4;
			m_sQueueSample.m_nFrequency = 18000;
			goto LABEL_81;
		case SOUND_2B:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_4;
			m_sQueueSample.m_nFrequency = 16500;
			goto LABEL_81;
		case SOUND_2C:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_4;
		LABEL_80:
			m_sQueueSample.m_nFrequency = 20000;
		LABEL_81:
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.field_4 = iSound;
			processed = 1;
			++iSound;
			m_sQueueSample.field_16 = 3;
			m_sQueueSample.field_48 = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			maxDist = 900.f;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nLoopStart = 0;
			emittingVol = m_anRandomTable[3] % 26 + 100;
			m_sQueueSample.m_nLoopEnd = -1;
			m_sQueueSample.m_bEmittingVolume = emittingVol;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_56 = 1;
			m_sQueueSample.m_bRequireReflection = 1;
			goto LABEL_84;
		case SOUND_WEAPON_BAT_ATTACK:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PED_HIT_BY_BAT;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.field_4 = iSound++;
			processed = 1;
			m_sQueueSample.m_nFrequency = RandomDisplacement(2000u) + 22000;
			m_sQueueSample.field_16 = 3;
			m_sQueueSample.field_48 = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			maxDist = 900.f;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nLoopStart = 0;
			m_sQueueSample.m_nLoopEnd = -1;
			emittingVol = m_anRandomTable[2] % 20 + 100;
			m_sQueueSample.m_bEmittingVolume = emittingVol;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_56 = 1;
			if(m_bDynamicAcousticModelingStatus)
				m_sQueueSample.m_bRequireReflection = 1;
			else
				noReflection = 1;
			goto LABEL_84;
		case SOUND_WEAPON_SHOT_FIRED:
			weapon = &ped->m_weapons[ped->m_currentWeapon];
			switch(weapon->m_eWeaponType) {
			case WEAPONTYPE_COLT45:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_PISTOL_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_PISTOL_SHOT);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 50.0f;
				maxDist = 2500.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				emittingVol = m_anRandomTable[1] % 10 + 90;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				if(m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bRequireReflection = 1;
				else
					noReflection = 1;
				goto LABEL_84;
			case WEAPONTYPE_UZI:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_UZI_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_UZI_SHOT);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 80.0f;
				maxDist = 6400.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				emittingVol = m_anRandomTable[3] % 15 + 70;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				goto LABEL_84;
			case WEAPONTYPE_SHOTGUN:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_SHOTGUN_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_SHOTGUN_SHOT);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 60.0f;
				maxDist = 3600.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				emittingVol = m_anRandomTable[2] % 10 + 100;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				if(m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bRequireReflection = 1;
				else
					noReflection = 1;
				goto LABEL_84;
			case WEAPONTYPE_AK47:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_CHAINGUN_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_CHAINGUN_SHOT);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 80.0f;
				maxDist = 6400.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				emittingVol = m_anRandomTable[1] % 15 + 70;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				goto LABEL_84;
			case WEAPONTYPE_M16:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_M16_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_M16_SHOT);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 80.0f;
				maxDist = 6400.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				emittingVol = m_anRandomTable[4] % 15 + 70;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				goto LABEL_84;
			case WEAPONTYPE_SNIPERRIFLE:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_SNIPER_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_SNIPER_SHOT);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 60.0f;
				maxDist = 3600.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				emittingVol = m_anRandomTable[4] % 10 + 110;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				if(m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bRequireReflection = 1;
				else
					noReflection = 1;
				goto LABEL_84;
			case WEAPONTYPE_ROCKETLAUNCHER:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_ROCKET_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_ROCKET_SHOT);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.field_16 = 1;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 90.0f;
				maxDist = 8100.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				emittingVol = m_anRandomTable[0] % 20 + 80;
				m_sQueueSample.m_bEmittingVolume = emittingVol;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				if(m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bRequireReflection = 1;
				else
					noReflection = 1;
				goto LABEL_84;
			case WEAPONTYPE_FLAMETHROWER:
				m_sQueueSample.m_nSampleIndex =
				    AUDIO_SAMPLE_WEAPON_FLAMETHROWER_SHOT;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_4 = 9;
				emittingVol = 90;
				m_sQueueSample.m_nFrequency =
				    (10 * m_sQueueSample.m_nEntityIndex & 2047) +
				    cSampleManager.GetSampleBaseFrequency(
				        AUDIO_SAMPLE_WEAPON_FLAMETHROWER_SHOT);
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 4.0f;
				m_sQueueSample.m_fSoundIntensity = 60.0f;
				maxDist = 3600.f;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nLoopStart =
				    cSampleManager.GetSampleLoopStartOffset(
				        m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nLoopEnd = cSampleManager.GetSampleLoopEndOffset(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_bEmittingVolume = 90;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 0;
				m_sQueueSample.field_76 = 6;
				if(m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bRequireReflection = 1;
				else
					noReflection = 1;
				goto LABEL_84;
			default: goto LABEL_100;
			}

			break;
		case SOUND_WEAPON_RELOAD:
			weapon = &ped->m_weapons[ped->m_currentWeapon];
			switch(weapon->m_eWeaponType) {
			case WEAPONTYPE_COLT45:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_PISTOL_RELOAD;
				emittingVol = 75;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency =
				    cSampleManager.GetSampleBaseFrequency(
				        AUDIO_SAMPLE_WEAPON_PISTOL_RELOAD) +
				    RandomDisplacement(300u);
				goto LABEL_63;
			case WEAPONTYPE_UZI:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_UZI_RELOAD;
				emittingVol = 75;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = 39243;
				goto LABEL_63;
			case WEAPONTYPE_SHOTGUN:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_CHAINGUN_RELOAD;
				emittingVol = 75;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = 30290;
				goto LABEL_63;
			case WEAPONTYPE_AK47:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_CHAINGUN_RELOAD;
				emittingVol = 75;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_CHAINGUN_RELOAD);
				goto LABEL_62;
			case WEAPONTYPE_M16:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_UZI_RELOAD;
				emittingVol = 75;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_UZI_RELOAD);
				goto LABEL_62;
			case WEAPONTYPE_SNIPERRIFLE:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_SNIPER_RELOAD;
				emittingVol = 75;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_SNIPER_RELOAD);
				goto LABEL_62;
			case WEAPONTYPE_ROCKETLAUNCHER:
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_ROCKET_RELOAD;
				emittingVol = 75;
				m_sQueueSample.field_4 = iSound++;
				processed = 1;
				m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
				    AUDIO_SAMPLE_WEAPON_ROCKET_RELOAD);
			LABEL_62:
			LABEL_63:
				m_sQueueSample.m_nFrequency += RandomDisplacement(300u);
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.field_16 = 5;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 30.0f;
				maxDist = 900.f;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bEmittingVolume = 75;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.m_bRequireReflection = 1;
				goto LABEL_84;
			default: goto LABEL_100;
			}

			break;
		case SOUND_WEAPON_AK47_BULLET_ECHO:
		case SOUND_WEAPON_UZI_BULLET_ECHO:
		case SOUND_WEAPON_M16_BULLET_ECHO:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_75;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.field_4 = iSound++;
			processed = 1;
			m_sQueueSample.m_nFrequency =
			    cSampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_75);
			m_sQueueSample.m_nFrequency +=
			    RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
			m_sQueueSample.field_16 = 3;
			m_sQueueSample.field_48 = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 80.0f;
			maxDist = 6400.f;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nLoopStart = 0;
			m_sQueueSample.m_nLoopEnd = -1;
			emittingVol = m_anRandomTable[4] % 10 + 40;
			m_sQueueSample.m_bEmittingVolume = emittingVol;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_56 = 1;
			if(m_bDynamicAcousticModelingStatus)
				m_sQueueSample.m_bRequireReflection = 1;
			else
				noReflection = 1;
			goto LABEL_84;
		case SOUND_WEAPON_FLAMETHROWER_FIRE:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WEAPON_FLAMETHROWER_FIRE;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.field_4 = iSound++;
			m_sQueueSample.m_nFrequency = cSampleManager.GetSampleBaseFrequency(
			    AUDIO_SAMPLE_WEAPON_FLAMETHROWER_FIRE);
			m_sQueueSample.m_nFrequency +=
			    RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
			m_sQueueSample.field_16 = 3;
			m_sQueueSample.field_48 = 4.0f;
			m_sQueueSample.m_fSoundIntensity = 60.0f;
			maxDist = 3600.f;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nLoopStart = 0;
			m_sQueueSample.m_nLoopEnd = -1;
			emittingVol = 70;
			m_sQueueSample.m_bEmittingVolume = 70;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_56 = 1;
			goto LABEL_84;
		case SOUND_WEAPON_HIT_PED:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_BULLET_HIT_PED;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.field_4 = iSound++;
			processed = 1;
			m_sQueueSample.m_nFrequency =
			    cSampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_BULLET_HIT_PED);
			m_sQueueSample.m_nFrequency +=
			    RandomDisplacement(m_sQueueSample.m_nFrequency >> 3);
			m_sQueueSample.field_16 = 7;
			m_sQueueSample.field_48 = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			maxDist = 900.f;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nLoopStart = 0;
			emittingVol = m_anRandomTable[0] % 20 + 90;
			m_sQueueSample.m_nLoopEnd = -1;
			m_sQueueSample.m_bEmittingVolume = emittingVol;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_56 = 1;
			goto LABEL_84;
		case SOUND_SPLASH:
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_COLLISION_WATER;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.field_4 = iSound++;
			processed = 1;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1400u) + 20000;
			m_sQueueSample.field_16 = 1;
			m_sQueueSample.field_48 = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 40.0f;
			maxDist = 1600.f;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nLoopStart = 0;
			emittingVol = m_anRandomTable[2] % 30 + 70;
			m_sQueueSample.m_nLoopEnd = -1;
			m_sQueueSample.m_bEmittingVolume = emittingVol;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.field_56 = 1;
			m_sQueueSample.m_bRequireReflection = 1;
		LABEL_84:
			if(processed && iSound > 60u) iSound = 21;
			if(params->m_fDistance < maxDist) {
				CalculateDistance((bool *)params, params->m_fDistance);
				m_sQueueSample.m_bVolume =
				    ComputeVolume(emittingVol, m_sQueueSample.m_fSoundIntensity,
				                  m_sQueueSample.m_fDistance);
				if(m_sQueueSample.m_bVolume) {
					if(noReflection) {
						if(0.2f * m_sQueueSample.m_fSoundIntensity >
						   m_sQueueSample.m_fDistance) {
							noReflection = 0;
						} else {
							m_sQueueSample.m_bIsDistant = 1;
							m_sQueueSample.m_bOffset = 0;
						}
					}
					m_sQueueSample.m_bReverbFlag = 1;
					AddSampleToRequestedQueue();
					if(noReflection) {
						m_sQueueSample.m_bOffset = 127;
						++m_sQueueSample.m_nSampleIndex;
						if(m_asAudioEntities[0].m_awAudioEvent
						           [i +
						            20 * m_sQueueSample.m_nEntityIndex] !=
						       47 ||
						   weapon->m_eWeaponType !=
						       WEAPONTYPE_FLAMETHROWER) {
							m_sQueueSample.field_4 = iSound++;
							if(iSound > 60u) iSound = 21;
						} else {
							++m_sQueueSample.field_4;
						}
						AddSampleToRequestedQueue();
					}
				}
			}
			break;
		default: SetupPedComments(params, sound); break;
		}
	LABEL_100:
		++i;
	}
}

void
cAudioManager::ProcessPhysical(int32 id)
{
	CPhysical *entity = (CPhysical *)m_asAudioEntities[id].m_pEntity;
	if(entity) {
		switch(entity->m_type & 7) {
		case ENTITY_TYPE_VEHICLE:
			ProcessVehicle((CVehicle *)m_asAudioEntities[id].m_pEntity);
			break;
		case ENTITY_TYPE_PED:
			ProcessPed((CPhysical *)m_asAudioEntities[id].m_pEntity);
			break;
		default: return;
		}
	}
}

WRAPPER
void
cAudioManager::ProcessPlane(void *ptr)
{
	EAXJMP(0x56E860);
}

WRAPPER
void
cAudioManager::ProcessPoliceCellBeatingScriptObject(uint8 sound)
{
	EAXJMP(0x578190);
}

void
cAudioManager::ProcessPornCinema(uint8 sound)
{

	eAudioSamples sample;
	uint32 time;
	int32 rand;
	float distSquared;
	float maxDist;

	switch(sound) {
	case SCRIPT_SOUND_PORN_CINEMA_1_S:
	case SCRIPT_SOUND_MISTY_SEX_S:
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PORN_CINEMA_1_BACKGROUND_1;
		m_sQueueSample.m_bBankIndex = 0;
		maxDist = 400.f;
		sample = AUDIO_SAMPLE_PORN_CINEMA_1_SEX_1;
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_1_L:
	case SCRIPT_SOUND_MISTY_SEX_L:
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PORN_CINEMA_1_BACKGROUND_1;
		m_sQueueSample.m_bBankIndex = 0;
		maxDist = 6400.f;
		sample = AUDIO_SAMPLE_PORN_CINEMA_1_SEX_1;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_2_S:
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PORN_CINEMA_2_BACKGROUND_2;
		m_sQueueSample.m_bBankIndex = 0;
		maxDist = 400.f;
		sample = AUDIO_SAMPLE_PORN_CINEMA_2_SEX_1;
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_2_L:
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PORN_CINEMA_2_BACKGROUND_2;
		m_sQueueSample.m_bBankIndex = 0;
		maxDist = 6400.f;
		sample = AUDIO_SAMPLE_PORN_CINEMA_2_SEX_1;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_3_S:
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PORN_CINEMA_3_BACKGROUND_3;
		m_sQueueSample.m_bBankIndex = 0;
		maxDist = 400.f;
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		sample = AUDIO_SAMPLE_PORN_CINEMA_3_SEX_1;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_3_L:
		m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_PORN_CINEMA_3_BACKGROUND_3;
		m_sQueueSample.m_bBankIndex = 0;
		maxDist = 6400.f;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		sample = AUDIO_SAMPLE_PORN_CINEMA_3_SEX_1;
		break;
	default: break;
	}
	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < maxDist) {
		m_sQueueSample.m_fDistance = sqrt(distSquared);
		if(sound != SCRIPT_SOUND_MISTY_SEX_S && sound != SCRIPT_SOUND_MISTY_SEX_L) {
			m_sQueueSample.m_bVolume =
			    ComputeVolume(maxVolume, m_sQueueSample.m_fSoundIntensity,
			                  m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.field_4 = 0;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.field_56 = 0;
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 2.0f;
				m_sQueueSample.m_bEmittingVolume = maxVolume;
				m_sQueueSample.m_nLoopStart =
				    SampleManager.GetSampleLoopStartOffset(
				        m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nLoopEnd = SampleManager.GetSampleLoopEndOffset(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
			}
		}

		time = CTimer::GetTimeInMilliseconds();
		if(time > audioLogicTimers[0]) {
			m_sQueueSample.m_bVolume = ComputeVolume(
			    90u, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				rand = m_anRandomTable[1] & 1;
				m_sQueueSample.m_nSampleIndex = rand + sample;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency +=
				    RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
				m_sQueueSample.field_4 = rand + 1;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.field_16 = 6;
				m_sQueueSample.field_48 = 0.0f;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
				audioLogicTimers[0] = time + 2000 + m_anRandomTable[3] % 6000u;
			}
		}
	}
}

WRAPPER
void
cAudioManager::ProcessProjectiles()
{
	EAXJMP(0x578A80);
}

void
cAudioManager::ProcessSawMillScriptObject(uint8 sound)
{
	uint32 time;
	float distSquared;
	float maxDist;

	switch(sound) {
	case SCRIPT_SOUND_SAWMILL_LOOP_S:
	case SCRIPT_SOUND_SAWMILL_LOOP_L:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		break;
	default: break;
	}
	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < maxDist) {
		m_sQueueSample.m_fDistance = sqrt(distSquared);
		m_sQueueSample.m_bVolume = ComputeVolume(30u, m_sQueueSample.m_fSoundIntensity,
		                                         m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_SAWMILL_1;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_nFrequency =
			    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_SAWMILL_1);
			m_sQueueSample.field_4 = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_16 = 5;
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_bEmittingVolume = 30;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_bReverbFlag = 1;
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
		time = CTimer::GetTimeInMilliseconds();
		if(time > audioLogicTimers[1]) {
			m_sQueueSample.m_bVolume = ComputeVolume(
			    70u, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_SAWMILL_2;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.field_4 = 1;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 2.0f;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
				audioLogicTimers[1] = time + 2000 + m_anRandomTable[3] % 4000u;
			}
		}
	}
}

void
cAudioManager::ProcessScriptObject(int32 id)
{
	cAudioScriptObject *entity = (cAudioScriptObject *)m_asAudioEntities[id].m_pEntity;
	if(entity) {
		m_sQueueSample.m_vecPos.x = entity->m_vecPos.x;
		m_sQueueSample.m_vecPos.y = entity->m_vecPos.y;
		m_sQueueSample.m_vecPos.z = entity->m_vecPos.z;
		if(m_asAudioEntities[id].field_24 == 1)
			ProcessOneShotScriptObject(m_asAudioEntities[id].m_awAudioEvent[0]);
		else
			ProcessLoopingScriptObject(entity->m_wSound);
	}
}

void
cAudioManager::ProcessShopScriptObject(uint8 sound)
{
	uint32 time;
	int32 rand;
	float distSquared;
	float maxDist;

	switch(sound) {
	case SCRIPT_SOUND_SHOP_LOOP_S:
	case SCRIPT_SOUND_SHOP_LOOP_L:
		maxDist = 900.f;
		m_sQueueSample.m_fSoundIntensity = 30.0f;
		break;
	default: break;
	}
	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < maxDist) {
		m_sQueueSample.m_fDistance = sqrt(distSquared);
		m_sQueueSample.m_bVolume = ComputeVolume(30u, m_sQueueSample.m_fSoundIntensity,
		                                         m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_SHOP_1;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_nFrequency =
			    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_SHOP_1);
			m_sQueueSample.field_4 = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_16 = 5;
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_bEmittingVolume = 30;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_bReverbFlag = 1;
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
		time = CTimer::GetTimeInMilliseconds();
		if(time > audioLogicTimers[2]) {
			m_sQueueSample.m_bVolume = ComputeVolume(
			    70u, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_bVolume) {
				rand = m_anRandomTable[1] & 1;
				m_sQueueSample.m_nSampleIndex = rand + AUDIO_SAMPLE_SHOP_2;
				m_sQueueSample.m_bBankIndex = 0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(
				    m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.field_4 = rand + 1;
				m_sQueueSample.m_bIsDistant = 0;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.field_56 = 1;
				m_sQueueSample.field_16 = 3;
				m_sQueueSample.field_48 = 2.0f;
				m_sQueueSample.m_bEmittingVolume = 70;
				m_sQueueSample.m_nLoopStart = 0;
				m_sQueueSample.m_nLoopEnd = -1;
				m_sQueueSample.m_bReverbFlag = 1;
				m_sQueueSample.m_bRequireReflection = 0;
				AddSampleToRequestedQueue();
				audioLogicTimers[2] = time + 3000 + m_anRandomTable[3] % 7000u;
			}
		}
	}
}

void
cAudioManager::ProcessSpecial()
{
	if(m_bUserPause) {
		if(!m_bPreviousUserPause) {
			MusicManager.ChangeMusicMode(0);
			SampleManager.SetEffectsFadeVolume(maxVolume);
			SampleManager.SetMusicFadeVolume(maxVolume);
		}
	} else {
		if(m_bPreviousUserPause) {
			MusicManager.StopFrontEndTrack();
			MusicManager.ChangeMusicMode(1u);
		}
		CPlayerPed *playerPed = FindPlayerPed();
		if(playerPed) {
			const PedState &state = playerPed->m_nPedState;
			if(state != PED_ENTER_CAR && state != PED_STEAL_CAR &&
			   !playerPed->bInVehicle)
				SampleManager.StopChannel(m_bActiveSamples);
		}
	}
}

#if 1
WRAPPER
void
cAudioManager::ProcessVehicle(CVehicle *)
{
	EAXJMP(0x569A00);
}
#else
void
cAudioManager::ProcessVehicle(CVehicle *)
{
	EAXJMP(0x569A00);
}
#endif

WRAPPER
void cAudioManager::ProcessWaterCannon(int32) { EAXJMP(0x575F30); }

WRAPPER
void
cAudioManager::ProcessWeather(int32 id)
{
	EAXJMP(0x578370);
}

void
cAudioManager::ProcessWorkShopScriptObject(uint8 sound)
{
	float distSquared;
	float maxDist;

	switch(sound) {
	case SCRIPT_SOUND_WORK_SHOP_LOOP_S:
	case SCRIPT_SOUND_WORK_SHOP_LOOP_L:
		maxDist = 400.f;
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		break;
	default: break;
	}
	distSquared = GetDistanceSquared(&m_sQueueSample.m_vecPos);
	if(distSquared < maxDist) {
		m_sQueueSample.m_fDistance = sqrt(distSquared);
		m_sQueueSample.m_bVolume = ComputeVolume(30u, m_sQueueSample.m_fSoundIntensity,
		                                         m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_bVolume) {
			m_sQueueSample.m_nSampleIndex = AUDIO_SAMPLE_WORK_SHOP;
			m_sQueueSample.m_bBankIndex = 0;
			m_sQueueSample.m_nFrequency =
			    SampleManager.GetSampleBaseFrequency(AUDIO_SAMPLE_WORK_SHOP);
			m_sQueueSample.field_4 = 0;
			m_sQueueSample.m_bIsDistant = 0;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.field_56 = 0;
			m_sQueueSample.field_16 = 5;
			m_sQueueSample.field_48 = 2.0f;
			m_sQueueSample.m_bEmittingVolume = 30;
			m_sQueueSample.m_nLoopStart =
			    SampleManager.GetSampleLoopStartOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopEnd =
			    SampleManager.GetSampleLoopEndOffset(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_bReverbFlag = 1;
			m_sQueueSample.m_bRequireReflection = 0;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::SetupPedComments(cPedParams *params, uint32 sound)
{
	CPed *ped = params->m_pPed;
	uint8 emittingVol;
	float maxDist;
	float soundIntensity;
	tPedComment pedComment;

	if(ped) {
		switch(sound) {
		case SOUND_AMMUNATION_WELCOME_1:
			pedComment.m_nSampleIndex = AUDIO_SAMPLE_AMMUNATION_WELCOME_1;
			break;
		case SOUND_AMMUNATION_WELCOME_2:
			pedComment.m_nSampleIndex = AUDIO_SAMPLE_AMMUNATION_WELCOME_2;
			break;
		case SOUND_AMMUNATION_WELCOME_3:
			pedComment.m_nSampleIndex = AUDIO_SAMPLE_AMMUNATION_WELCOME_3;
			break;
		default:
			pedComment.m_nSampleIndex = GetPedCommentSfx(ped, sound);
			if(pedComment.m_nSampleIndex == NO_SAMPLE) return;
			break;
		}

		maxDist = 2500.f;
		soundIntensity = 50.f;

		if(params->m_fDistance < maxDist) {
			CalculateDistance((bool *)params, params->m_fDistance);
			if(sound != SOUND_PAGER) {
				switch(sound) {
				case SOUND_AMMUNATION_WELCOME_1:
				case SOUND_AMMUNATION_WELCOME_2:
				case SOUND_AMMUNATION_WELCOME_3: emittingVol = maxVolume; break;
				default:
					if(CWorld::GetIsLineOfSightClear(
					       TheCamera.GetGameCamPosition(),
					       m_sQueueSample.m_vecPos, 1, 0, 0, 0, 0, 0, 0)) {
						emittingVol = maxVolume;
					} else {
						emittingVol = 31;
					}
					break;
				}
				m_sQueueSample.m_bVolume = ComputeVolume(
				    emittingVol, soundIntensity, m_sQueueSample.m_fDistance);
				pedComment.field_25 = 10;
				if(m_sQueueSample.m_bVolume) {
					pedComment.field_4 = m_sQueueSample.m_nEntityIndex;
					pedComment.m_vecPos.x = m_sQueueSample.m_vecPos.x;
					pedComment.m_vecPos.y = m_sQueueSample.m_vecPos.y;
					pedComment.m_vecPos.z = m_sQueueSample.m_vecPos.z;
					pedComment.m_fDistance = m_sQueueSample.m_fDistance;
					pedComment.m_bVolume = m_sQueueSample.m_bVolume;
					m_sPedComments.Add(&pedComment);
				}
			}
		}
	} else {
		switch(sound) {
		case SOUND_PED_HELI_PLAYER_FOUND:
			maxDist = 160000.f;
			soundIntensity = 400.f;
			pedComment.m_nSampleIndex =
			    m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] % 29u +
			    AUDIO_SAMPLE_POLICE_HELI_FOUND_PLAYER_1;
			break;
		case SOUND_PED_BODYCAST_HIT:
			if(CTimer::GetTimeInMilliseconds() <= audioLogicTimers[8]) return;
			maxDist = 2500.f;
			soundIntensity = 50.f;
			audioLogicTimers[8] = CTimer::GetTimeInMilliseconds() + 500;
			pedComment.m_nSampleIndex =
			    (m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] & 3) +
			    AUDIO_SAMPLE_PED_BODYCAST_HIT_1;
			break;
		case SOUND_INJURED_PED_MALE_OUCH:
		case SOUND_8A:
			maxDist = 2500.f;
			soundIntensity = 50.f;
			pedComment.m_nSampleIndex =
			    m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] % 15u +
			    AUDIO_SAMPLE_INJURED_PED_MALE_OUCH_1;
			break;
		case SOUND_INJURED_PED_FEMALE:
			maxDist = 2500.f;
			soundIntensity = 50.f;
			pedComment.m_nSampleIndex =
			    m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] % 11u +
			    AUDIO_SAMPLE_INJURED_PED_FEMALE_OUCH_1;
			break;
		default: return;
		}

		if(params->m_fDistance < maxDist) {
			CalculateDistance((bool *)params, params->m_fDistance);
			if(sound != SOUND_PAGER) {
				switch(sound) {
				case SOUND_AMMUNATION_WELCOME_1:
				case SOUND_AMMUNATION_WELCOME_2:
				case SOUND_AMMUNATION_WELCOME_3: emittingVol = maxVolume; break;
				default:
					if(CWorld::GetIsLineOfSightClear(
					       TheCamera.GetGameCamPosition(),
					       m_sQueueSample.m_vecPos, 1, 0, 0, 0, 0, 0, 0)) {
						emittingVol = maxVolume;
					} else {
						emittingVol = 31;
					}
					break;
				}
				m_sQueueSample.m_bVolume = ComputeVolume(
				    emittingVol, soundIntensity, m_sQueueSample.m_fDistance);
				pedComment.field_25 = 10;
				if(m_sQueueSample.m_bVolume) {
					pedComment.field_4 = m_sQueueSample.m_nEntityIndex;
					pedComment.m_vecPos.x = m_sQueueSample.m_vecPos.x;
					pedComment.m_vecPos.y = m_sQueueSample.m_vecPos.y;
					pedComment.m_vecPos.z = m_sQueueSample.m_vecPos.z;
					pedComment.m_fDistance = m_sQueueSample.m_fDistance;
					pedComment.m_bVolume = m_sQueueSample.m_bVolume;
					m_sPedComments.Add(&pedComment);
				}
			}
		}
	}
}

WRAPPER void
cAudioManager::Service()
{
	EAXJMP(0x57A2A0);
}

WRAPPER void cAudioManager::PlayOneShot(int, unsigned short, float)
{
	EAXJMP(0x57A500);
}

WRAPPER void cAudioManager::SetEffectsFadeVol(unsigned char)
{
	EAXJMP(0x57A770);
}

WRAPPER void cAudioManager::SetMusicFadeVol(unsigned char)
{
	EAXJMP(0x57A790);
}

WRAPPER int8 cAudioManager::SetCurrent3DProvider(unsigned char)
{
	EAXJMP(0x57A910);
}

WRAPPER void cAudioManager::ReportCrime(eCrimeType, CVector const &)
{
	EAXJMP(0x5803D0);
}

WRAPPER void cAudioManager::PlaySuspectLastSeen(float, float, float)
{
	EAXJMP(0x580500);
}

WRAPPER void cAudioManager::ReportCollision(CEntity *, CEntity *, unsigned char, unsigned char, float, float)
{
	EAXJMP(0x568410);
}

WRAPPER void cAudioManager::ResetTimers(unsigned int)
{
	EAXJMP(0x57A7B0);
}

WRAPPER void cAudioManager::PreloadMissionAudio(char *)
{
	EAXJMP(0x579550);
}

STARTPATCHES
InjectHook(0x5755C0, &cPedComments::Add, PATCH_JUMP);

InjectHook(0x57B210, &cAudioManager::AddDetailsToRequestedOrderList, PATCH_JUMP);
InjectHook(0x56AD30, &cAudioManager::AddPlayerCarSample, PATCH_JUMP);
InjectHook(0x57B300, &cAudioManager::AddReflectionsToRequestedQueue, PATCH_JUMP);
// InjectHook(0x57B8D0, &cAudioManager::AddReleasingSounds, PATCH_JUMP);
InjectHook(0x57B070, &cAudioManager::AddSampleToRequestedQueue, PATCH_JUMP);
InjectHook(0x57A8F0, &cAudioManager::GetCurrent3DProviderIndex, PATCH_JUMP);
// InjectHook(0x580AF0, &cAudioManager::AgeCrimes, PATCH_JUMP);

InjectHook(0x5697A0, &cAudioManager::CalculateDistance, PATCH_JUMP);
InjectHook(0x57AA10, &cAudioManager::CheckForAnAudioFileOnCD, PATCH_JUMP);
InjectHook(0x5796A0, &cAudioManager::ClearMissionAudio, PATCH_JUMP);
InjectHook(0x57C120, &cAudioManager::ClearRequestedQueue, PATCH_JUMP);
InjectHook(0x57AE00, &cAudioManager::ComputeDopplerEffectedFrequency, PATCH_JUMP);
InjectHook(0x57ABB0, &cAudioManager::ComputeVolume, PATCH_JUMP);
InjectHook(0x57A310, &cAudioManager::CreateEntity, PATCH_JUMP);

InjectHook(0x57A830, &cAudioManager::DestroyAllGameCreatedEntities, PATCH_JUMP);
InjectHook(0x57A400, &cAudioManager::DestroyEntity, PATCH_JUMP);
InjectHook(0x57F060, &cAudioManager::DoPoliceRadioCrackle, PATCH_JUMP);

InjectHook(0x57C290, &cAudioManager::GenerateIntegerRandomNumberTable, PATCH_JUMP);
InjectHook(0x569750, &cAudioManager::GetDistanceSquared, PATCH_JUMP);
InjectHook(0x57AC60, &cAudioManager::TranslateEntity, PATCH_JUMP);

InjectHook(0x57A0E0, &cAudioManager::Initialise, PATCH_JUMP);
InjectHook(0x569420, &cAudioManager::PostInitialiseGameSpecificSetup, PATCH_JUMP);
// InjectHook(0x57EAC0, &cAudioManager::InitialisePoliceRadioZones, PATCH_JUMP);
// InjectHook(0x569650, &cAudioManager::ResetAudioLogicTimers, PATCH_JUMP);
InjectHook(0x57A150, &cAudioManager::Terminate, PATCH_JUMP);

InjectHook(0x57F050, &cAudioManager::GetMissionScriptPoliceAudioPlayingStatus, PATCH_JUMP);
InjectHook(0x5795D0, &cAudioManager::GetMissionAudioLoadingStatus, PATCH_JUMP);

InjectHook(0x57A8A0, &cAudioManager::GetNum3DProvidersAvailable, PATCH_JUMP);
InjectHook(0x57A9C0, &cAudioManager::IsMP3RadioChannelAvailable, PATCH_JUMP);
InjectHook(0x57AA30, &cAudioManager::GetCDAudioDriveLetter, PATCH_JUMP);

InjectHook(0x57A730, &cAudioManager::SetEffectsMasterVolume, PATCH_JUMP);
InjectHook(0x57A750, &cAudioManager::SetMusicMasterVolume, PATCH_JUMP);
InjectHook(0x57A770, &cAudioManager::SetEffectsFadeVolume, PATCH_JUMP);
InjectHook(0x57A790, &cAudioManager::SetMusicFadeVolume, PATCH_JUMP);

InjectHook(0x57A9A0, &cAudioManager::SetSpeakerConfig, PATCH_JUMP);

InjectHook(0x569400, &cAudioManager::PreInitialiseGameSpecificSetup, PATCH_JUMP);

InjectHook(0x57F020, &cAudioManager::SetMissionScriptPoliceAudio, PATCH_JUMP);

InjectHook(0x56C3C0, &cAudioManager::UsesSiren, PATCH_JUMP);
InjectHook(0x56C3F0, &cAudioManager::UsesSirenSwitching, PATCH_JUMP);

InjectHook(0x579520, &cAudioManager::MissionScriptAudioUsesPoliceChannel, PATCH_JUMP);

InjectHook(0x57A8C0, &cAudioManager::Get3DProviderName, PATCH_JUMP);
InjectHook(0x56F230, &cAudioManager::SetupJumboFlySound, PATCH_JUMP);
InjectHook(0x56F310, &cAudioManager::SetupJumboRumbleSound, PATCH_JUMP);
InjectHook(0x56EF20, &cAudioManager::SetupJumboTaxiSound, PATCH_JUMP);
InjectHook(0x56F070, &cAudioManager::SetupJumboWhineSound, PATCH_JUMP);

InjectHook(0x579620, &cAudioManager::PlayLoadedMissionAudio, PATCH_JUMP);

InjectHook(0x5795F0, &cAudioManager::SetMissionAudioLocation, PATCH_JUMP);

InjectHook(0x57EFF0, &cAudioManager::ResetPoliceRadio, PATCH_JUMP);

InjectHook(0x57B030, &cAudioManager::InterrogateAudioEntities, PATCH_JUMP);

InjectHook(0x56C600, &cAudioManager::UsesReverseWarning, PATCH_JUMP);
InjectHook(0x56CAB0, &cAudioManager::HasAirBrakes, PATCH_JUMP);

InjectHook(0x56F410, &cAudioManager::GetJumboTaxiFreq, PATCH_JUMP);

InjectHook(0x579650, &cAudioManager::IsMissionAudioSampleFinished, PATCH_JUMP);
InjectHook(0x57AF90, &cAudioManager::RandomDisplacement, PATCH_JUMP);

InjectHook(0x57A9E0, &cAudioManager::ReleaseDigitalHandle, PATCH_JUMP);
InjectHook(0x57A9F0, &cAudioManager::ReacquireDigitalHandle, PATCH_JUMP);
InjectHook(0x57AA00, &cAudioManager::SetDynamicAcousticModelingStatus, PATCH_JUMP);

InjectHook(0x57AA50, &cAudioManager::IsAudioInitialised, PATCH_JUMP);

InjectHook(0x57A4C0, &cAudioManager::SetEntityStatus, PATCH_JUMP);

InjectHook(0x569570, &cAudioManager::PreTerminateGameSpecificShutdown, PATCH_JUMP);
InjectHook(0x569640, &cAudioManager::PostTerminateGameSpecificShutdown, PATCH_JUMP);

InjectHook(0x56AD10, &cAudioManager::PlayerJustGotInCar, PATCH_JUMP);
InjectHook(0x56AD20, &cAudioManager::PlayerJustLeftCar, PATCH_JUMP);
InjectHook(0x570DB0, &cAudioManager::GetPhrase, PATCH_JUMP);

// Get ped sfx stuff
InjectHook(0x570960, &cAudioManager::GetPedCommentSfx, PATCH_JUMP);

InjectHook(0x570E00, &cAudioManager::GetPlayerTalkSfx, PATCH_JUMP);
InjectHook(0x570EA0, &cAudioManager::GetCopTalkSfx, PATCH_JUMP);
InjectHook(0x570F80, &cAudioManager::GetSwatTalkSfx, PATCH_JUMP);
InjectHook(0x571040, &cAudioManager::GetFBITalkSfx, PATCH_JUMP);
InjectHook(0x571110, &cAudioManager::GetArmyTalkSfx, PATCH_JUMP);
InjectHook(0x5711C0, &cAudioManager::GetMedicTalkSfx, PATCH_JUMP);
InjectHook(0x5712B0, &cAudioManager::GetFiremanTalkSfx, PATCH_JUMP);
InjectHook(0x575340, &cAudioManager::GetNormalMaleTalkSfx, PATCH_JUMP);
InjectHook(0x575190, &cAudioManager::GetTaxiDriverTalkSfx, PATCH_JUMP);
InjectHook(0x575240, &cAudioManager::GetPimpTalkSfx, PATCH_JUMP);
InjectHook(0x571510, &cAudioManager::GetMafiaTalkSfx, PATCH_JUMP);
InjectHook(0x571650, &cAudioManager::GetTriadTalkSfx, PATCH_JUMP);
InjectHook(0x571770, &cAudioManager::GetDiabloTalkSfx, PATCH_JUMP);
InjectHook(0x5718D0, &cAudioManager::GetYakuzaTalkSfx, PATCH_JUMP);
InjectHook(0x5719E0, &cAudioManager::GetYardieTalkSfx, PATCH_JUMP);
InjectHook(0x571B00, &cAudioManager::GetColumbianTalkSfx, PATCH_JUMP);
InjectHook(0x571C30, &cAudioManager::GetHoodTalkSfx, PATCH_JUMP);
InjectHook(0x571D80, &cAudioManager::GetBlackCriminalTalkSfx, PATCH_JUMP);
InjectHook(0x571E60, &cAudioManager::GetWhiteCriminalTalkSfx, PATCH_JUMP);
InjectHook(0x571F40, &cAudioManager::GetMaleNo2TalkSfx, PATCH_JUMP);
InjectHook(0x572AF0, &cAudioManager::GetBlackProjectMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5725D0, &cAudioManager::GetWhiteFatMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5726C0, &cAudioManager::GetBlackFatMaleTalkSfx, PATCH_JUMP);
InjectHook(0x572050, &cAudioManager::GetBlackCasualFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x572170, &cAudioManager::GetWhiteCasualFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x572280, &cAudioManager::GetFemaleNo3TalkSfx, PATCH_JUMP);
InjectHook(0x5724D0, &cAudioManager::GetBlackFatFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x5727B0, &cAudioManager::GetWhiteFatFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x5728B0, &cAudioManager::GetBlackFemaleProstituteTalkSfx, PATCH_JUMP);
InjectHook(0x5729D0, &cAudioManager::GetWhiteFemaleProstituteTalkSfx, PATCH_JUMP);
InjectHook(0x572C20, &cAudioManager::GetBlackProjectFemaleOldTalkSfx, PATCH_JUMP);
InjectHook(0x572D20, &cAudioManager::GetBlackProjectFemaleYoungTalkSfx, PATCH_JUMP);
InjectHook(0x572E10, &cAudioManager::GetChinatownMaleOldTalkSfx, PATCH_JUMP);
InjectHook(0x572F10, &cAudioManager::GetChinatownMaleYoungTalkSfx, PATCH_JUMP);
InjectHook(0x573010, &cAudioManager::GetChinatownFemaleOldTalkSfx, PATCH_JUMP);
InjectHook(0x5730F0, &cAudioManager::GetChinatownFemaleYoungTalkSfx, PATCH_JUMP);
InjectHook(0x5731E0, &cAudioManager::GetLittleItalyMaleTalkSfx, PATCH_JUMP);
InjectHook(0x573310, &cAudioManager::GetLittleItalyFemaleOldTalkSfx, PATCH_JUMP);
InjectHook(0x573400, &cAudioManager::GetLittleItalyFemaleYoungTalkSfx, PATCH_JUMP);
InjectHook(0x5734F0, &cAudioManager::GetWhiteDockerMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5735E0, &cAudioManager::GetBlackDockerMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5736D0, &cAudioManager::GetScumMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5737E0, &cAudioManager::GetScumFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x5738D0, &cAudioManager::GetWhiteWorkerMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5739C0, &cAudioManager::GetBlackWorkerMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5713E0, &cAudioManager::GetBusinessMaleYoungTalkSfx, PATCH_JUMP);
InjectHook(0x5712C0, &cAudioManager::GetBusinessMaleOldTalkSfx, PATCH_JUMP);
InjectHook(0x5723A0, &cAudioManager::GetWhiteBusinessFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x573AB0, &cAudioManager::GetBlackBusinessFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x573BD0, &cAudioManager::GetSupermodelMaleTalkSfx, PATCH_JUMP);
InjectHook(0x573CD0, &cAudioManager::GetSupermodelFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x573DC0, &cAudioManager::GetStewardMaleTalkSfx, PATCH_JUMP);
InjectHook(0x573E90, &cAudioManager::GetStewardFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x573F60, &cAudioManager::GetFanMaleTalkSfx, PATCH_JUMP);
InjectHook(0x574040, &cAudioManager::GetFanFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x574120, &cAudioManager::GetHospitalMaleTalkSfx, PATCH_JUMP);
InjectHook(0x5741F0, &cAudioManager::GetHospitalFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x574290, &cAudioManager::GetWhiteConstructionWorkerTalkSfx, PATCH_JUMP);
InjectHook(0x574380, &cAudioManager::GetBlackConstructionWorkerTalkSfx, PATCH_JUMP);
InjectHook(0x574480, &cAudioManager::GetShopperFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x574590, &cAudioManager::GetStudentMaleTalkSfx, PATCH_JUMP);
InjectHook(0x574690, &cAudioManager::GetStudentFemaleTalkSfx, PATCH_JUMP);
InjectHook(0x572040, &cAudioManager::GetCasualMaleOldTalkSfx, PATCH_JUMP);

InjectHook(0x574790, &cAudioManager::GetSpecialCharacterTalkSfx, PATCH_JUMP);
InjectHook(0x574DA0, &cAudioManager::GetEightTalkSfx, PATCH_JUMP);
InjectHook(0x574E50, &cAudioManager::GetFrankieTalkSfx, PATCH_JUMP);
InjectHook(0x574F00, &cAudioManager::GetMistyTalkSfx, PATCH_JUMP);
InjectHook(0x574FD0, &cAudioManager::GetOJGTalkSfx, PATCH_JUMP);
InjectHook(0x574FE0, &cAudioManager::GetCatatalinaTalkSfx, PATCH_JUMP);
InjectHook(0x574FF0, &cAudioManager::GetBomberTalkSfx, PATCH_JUMP);
InjectHook(0x575060, &cAudioManager::GetSecurityGuardTalkSfx, PATCH_JUMP);
InjectHook(0x575120, &cAudioManager::GetChunkyTalkSfx, PATCH_JUMP);

InjectHook(0x575460, &cAudioManager::GetGenericMaleTalkSfx, PATCH_JUMP);
InjectHook(0x575510, &cAudioManager::GetGenericFemaleTalkSfx, PATCH_JUMP);

// Process stuff
// InjectHook(0x57BA60, &cAudioManager::ProcessActiveQueues, PATCH_JUMP);
InjectHook(0x56C940, &cAudioManager::ProcessAirBrakes, PATCH_JUMP);
InjectHook(0x577B30, &cAudioManager::ProcessAirportScriptObject, PATCH_JUMP);
InjectHook(0x579250, &cAudioManager::ProcessBridgeMotor, PATCH_JUMP);
InjectHook(0x579170, &cAudioManager::ProcessBridgeWarning, PATCH_JUMP);
InjectHook(0x577CA0, &cAudioManager::ProcessCinemaScriptObject, PATCH_JUMP);
InjectHook(0x577E50, &cAudioManager::ProcessDocksScriptObject, PATCH_JUMP);
InjectHook(0x569870, &cAudioManager::ProcessEntity, PATCH_JUMP);
InjectHook(0x575AC0, &cAudioManager::ProcessExplosions, PATCH_JUMP);
InjectHook(0x578FD0, &cAudioManager::ProcessFireHydrant, PATCH_JUMP);
InjectHook(0x5785E0, &cAudioManager::ProcessFrontEnd, PATCH_JUMP);
InjectHook(0x577FE0, &cAudioManager::ProcessHomeScriptObject, PATCH_JUMP);
InjectHook(0x56E8F0, &cAudioManager::ProcessJumbo, PATCH_JUMP);
InjectHook(0x56EA40, &cAudioManager::ProcessJumboAccel, PATCH_JUMP);
InjectHook(0x56EE40, &cAudioManager::ProcessJumboDecel, PATCH_JUMP);
InjectHook(0x56ECF0, &cAudioManager::ProcessJumboFlying, PATCH_JUMP);
InjectHook(0x56ED10, &cAudioManager::ProcessJumboLanding, PATCH_JUMP);
InjectHook(0x56EC00, &cAudioManager::ProcessJumboTakeOff, PATCH_JUMP);
InjectHook(0x56EA10, &cAudioManager::ProcessJumboTaxi, PATCH_JUMP);
InjectHook(0x5777E0, &cAudioManager::ProcessLaunderetteScriptObject, PATCH_JUMP);
InjectHook(0x576770, &cAudioManager::ProcessLoopingScriptObject, PATCH_JUMP);
InjectHook(0x5760C0, &cAudioManager::ProcessOneShotScriptObject, PATCH_JUMP);
InjectHook(0x56F450, &cAudioManager::ProcessPed, PATCH_JUMP);
InjectHook(0x56F4D0, &cAudioManager::ProcessPedHeadphones, PATCH_JUMP);
InjectHook(0x56F650, &cAudioManager::ProcessPedOneShots, PATCH_JUMP);
InjectHook(0x5699C0, &cAudioManager::ProcessPhysical, PATCH_JUMP);
InjectHook(0x577280, &cAudioManager::ProcessPornCinema, PATCH_JUMP);
InjectHook(0x577630, &cAudioManager::ProcessSawMillScriptObject, PATCH_JUMP);
InjectHook(0x576070, &cAudioManager::ProcessScriptObject, PATCH_JUMP);
InjectHook(0x577970, &cAudioManager::ProcessShopScriptObject, PATCH_JUMP);
InjectHook(0x5697D0, &cAudioManager::ProcessSpecial, PATCH_JUMP);
InjectHook(0x577530, &cAudioManager::ProcessWorkShopScriptObject, PATCH_JUMP);
InjectHook(0x570690, &cAudioManager::SetupPedComments, PATCH_JUMP);
ENDPATCHES
