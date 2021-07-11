#pragma once

#include "audio_enums.h"
#include "AudioCollision.h"
#include "PolRadio.h"
#include "VehicleModelInfo.h"
#include "Vehicle.h"

class tSound
{
public:
	int32 m_nEntityIndex;
	int32 m_nCounter;
	int32 m_nSampleIndex;
	uint8 m_nBankIndex;
	bool8 m_bIs2D;
	int32 m_nReleasingVolumeModificator;
	uint32 m_nFrequency;
	uint8 m_nVolume;
	float m_fDistance;
	int32 m_nLoopCount;
#ifndef GTA_PS2
	int32 m_nLoopStart;
	int32 m_nLoopEnd;
#endif
	uint8 m_nEmittingVolume;
	float m_fSpeedMultiplier;
	float m_fSoundIntensity;
	bool8 m_bReleasingSoundFlag;
	CVector m_vecPos;
	bool8 m_bReverbFlag;
	uint8 m_nLoopsRemaining;
	bool8 m_bRequireReflection; // Used for oneshots
	uint8 m_nOffset;
	uint8 field_4C;
	int32 m_nReleasingVolumeDivider;
	bool8 m_bIsProcessed;
	bool8 m_bLoopEnded;
	int32 m_nCalculatedVolume;
	int8 m_nVolumeChange;
};

VALIDATE_SIZE(tSound, 96);

class CPhysical;
class CAutomobile;

class tAudioEntity
{
public:
	eAudioType m_nType;
	void *m_pEntity;
	bool8 m_bIsUsed;
	uint8 m_bStatus;
	int16 m_awAudioEvent[NUM_AUDIOENTITY_EVENTS];
	float m_afVolume[NUM_AUDIOENTITY_EVENTS];
	uint8 m_AudioEvents;
};

VALIDATE_SIZE(tAudioEntity, 40);

class tPedComment
{
public:
	uint32 m_nSampleIndex;
	int32 m_nEntityIndex;
	CVector m_vecPos;
	float m_fDistance;
	uint8 m_bVolume;
	int8 m_nProcess;
};

VALIDATE_SIZE(tPedComment, 28);

class cPedComments
{
public:
	tPedComment m_asPedComments[NUM_PED_COMMENTS_BANKS][NUM_PED_COMMENTS_SLOTS];
	uint8 m_nIndexMap[NUM_PED_COMMENTS_BANKS][NUM_PED_COMMENTS_SLOTS];
	uint8 m_nCommentsInBank[NUM_PED_COMMENTS_BANKS];
	uint8 m_nActiveBank;
#ifdef GTA_PC
	bool8 m_bDelay;
	uint32 m_nDelayTimer;
#endif

	cPedComments()
	{
		for (int i = 0; i < NUM_PED_COMMENTS_SLOTS; i++)
			for (int j = 0; j < NUM_PED_COMMENTS_BANKS; j++) {
				m_asPedComments[j][i].m_nProcess = -1;
				m_nIndexMap[j][i] = NUM_PED_COMMENTS_SLOTS;
			}

		for (int i = 0; i < NUM_PED_COMMENTS_BANKS; i++)
			m_nCommentsInBank[i] = 0;
		m_nActiveBank = 0;
	}
	void Add(tPedComment *com);
	void Process();
};

VALIDATE_SIZE(cPedComments, 0x490);

class CEntity;

#define MISSION_AUDIO_SLOTS (2)

// So instead of doing cMissionAudio [2] they've added [2] to every field of the struct...
// Only someone with a VERY EXTRAORDINARY mind could have come up with that
class cMissionAudio
{
public:
	CVector m_vecPos[MISSION_AUDIO_SLOTS];
	bool8 m_bPredefinedProperties[MISSION_AUDIO_SLOTS];
	int32 m_nSampleIndex[MISSION_AUDIO_SLOTS];
	uint8 m_nLoadingStatus[MISSION_AUDIO_SLOTS];
	uint8 m_nPlayStatus[MISSION_AUDIO_SLOTS];
	bool8 m_bIsPlaying[MISSION_AUDIO_SLOTS];
	int32 m_nMissionAudioCounter[MISSION_AUDIO_SLOTS];
	bool8 m_bIsPlayed[MISSION_AUDIO_SLOTS];
	bool8 m_bIsMobile[MISSION_AUDIO_SLOTS];
};
VALIDATE_SIZE(cMissionAudio, 0x38);

// name made up
class cAudioScriptObjectManager
{
public:
	int32 m_anScriptObjectEntityIndices[NUM_SCRIPT_MAX_ENTITIES];
	int32 m_nScriptObjectEntityTotal;

	cAudioScriptObjectManager() { m_nScriptObjectEntityTotal = 0; }
	~cAudioScriptObjectManager() { m_nScriptObjectEntityTotal = 0; }
};


class cTransmission;
class CPlane;
class CVehicle;
class CPed;

class cPedParams
{
public:
	bool8 m_bDistanceCalculated;
	float m_fDistance;
	CPed *m_pPed;

	cPedParams()
	{
		m_bDistanceCalculated = false;
		m_fDistance = 0.0f;
		m_pPed = nil;
	}
};

class cVehicleParams
{
public:
	int32 m_VehicleType;
	bool8 m_bDistanceCalculated;
	float m_fDistance;
	CVehicle *m_pVehicle;
	cTransmission *m_pTransmission;
	int32 m_nIndex;
	float m_fVelocityChange;

	cVehicleParams()
	{
		m_VehicleType = -1;
		m_bDistanceCalculated = false;
		m_fDistance = 0.0f;
		m_pVehicle = nil;
		m_pTransmission = nil;
		m_nIndex = 0;
		m_fVelocityChange = 0.0f;
	}
};

VALIDATE_SIZE(cVehicleParams, 0x1C);

enum {
	REFLECTION_NORTH = 0,
	REFLECTION_SOUTH,
	REFLECTION_WEST,
	REFLECTION_EAST,
	REFLECTION_CEIL_NORTH,
	REFLECTION_CEIL_SOUTH,
	REFLECTION_CEIL_WEST,
	REFLECTION_CEIL_EAST,
	MAX_REFLECTIONS,
};

class cAudioManager
{
public:
	bool8 m_bIsInitialised;
	uint8 m_bReverb; // unused
	bool8 m_bFifthFrameFlag;
	uint8 m_nActiveSamples;
	uint8 field_4; // unused
	bool8 m_bDynamicAcousticModelingStatus;
	int8 field_6;
	float m_fSpeedOfSound;
	bool8 m_bTimerJustReset;
	int32 m_nTimer;
	tSound m_sQueueSample;
	uint8 m_nActiveSampleQueue;
	tSound m_asSamples[NUM_SOUNDS_SAMPLES_BANKS][NUM_CHANNELS_GENERIC];
	uint8 m_abSampleQueueIndexTable[NUM_SOUNDS_SAMPLES_BANKS][NUM_CHANNELS_GENERIC];
	uint8 m_SampleRequestQueuesStatus[NUM_SOUNDS_SAMPLES_BANKS];
	tSound m_asActiveSamples[NUM_CHANNELS_GENERIC];
	tAudioEntity m_asAudioEntities[NUM_AUDIOENTITIES];
	int32 m_anAudioEntityIndices[NUM_AUDIOENTITIES];
	int32 m_nAudioEntitiesTotal;
	CVector m_avecReflectionsPos[NUM_AUDIO_REFLECTIONS];
	float m_afReflectionsDistances[NUM_AUDIO_REFLECTIONS];
	cAudioScriptObjectManager m_sAudioScriptObjectManager;

	// miami
	bool8 m_bIsPlayerShutUp;
	uint8 m_nPlayerMood;
	uint32 m_nPlayerMoodTimer;
	uint8 field_rest[4];
	bool8 m_bGenericSfx;

	cPedComments m_sPedComments;
	int32 m_nFireAudioEntity;
	int32 m_nWaterCannonEntity;
	int32 m_nPoliceChannelEntity;
	cPoliceRadioQueue m_sPoliceRadioQueue;
	int32 m_nFrontEndEntity;
	int32 m_nCollisionEntity;
	cAudioCollisionManager m_sCollisionManager;
	int32 m_nProjectileEntity;
#ifdef GTA_BRIDGE
	int32 m_nBridgeEntity;
#endif
	int32 m_nEscalatorEntity;
	int32 m_nExtraSoundsEntity;
	cMissionAudio m_sMissionAudio;
	uint8 field_5538; // something related to phone dialogues
	int32 m_anRandomTable[5];
	uint8 m_nTimeSpent;
	uint8 m_nUserPause;
	uint8 m_nPreviousUserPause;
	uint32 m_FrameCounter;

	cAudioManager();
	~cAudioManager();

	// getters
	uint32 GetFrameCounter() const { return m_FrameCounter; }
	float GetReflectionsDistance(int32 idx) const { return m_afReflectionsDistances[idx]; }
	int32 GetRandomNumber(int32 idx) const { return m_anRandomTable[idx]; }
	int32 GetRandomNumberInRange(int32 idx, int32 low, int32 high) const { return (m_anRandomTable[idx] % (high - low + 1)) + low; }
	bool8 IsMissionAudioSamplePlaying(uint8 slot) const; // { return m_sMissionAudio.m_nPlayStatus == 1; }
	bool8 ShouldDuckMissionAudio(uint8 slot) const;

	// "Should" be in alphabetic order, except "getXTalkSfx"
	void AddDetailsToRequestedOrderList(uint8 sample); // inlined in vc
	void AddPlayerCarSample(uint8 emittingVolume, int32 freq, uint32 sample, uint8 bank, uint8 counter, bool8 notLooping);
	void AddReflectionsToRequestedQueue();
	void AddReleasingSounds();
	void AddSampleToRequestedQueue();
	void AgeCrimes(); // inlined in vc

	void CalculateDistance(bool8 &condition, float dist);
	bool8 CheckForAnAudioFileOnCD() const;
	void ClearActiveSamples();
	void ClearMissionAudio(uint8 slot); // inlined in vc
	void ClearRequestedQueue(); // inlined in vc
	uint32 ComputeDopplerEffectedFrequency(uint32 oldFreq, float position1, float position2, float speedMultiplier) const;
	int32 ComputePan(float, CVector *);
	uint8 ComputeVolume(uint8 emittingVolume, float soundIntensity, float distance) const;
	int32 CreateEntity(eAudioType type, void *entity);

	void DestroyAllGameCreatedEntities();
	void DestroyEntity(int32 id); // inlined in vc
	void DoPoliceRadioCrackle();

	// functions returning talk sfx,
	// order from GetPedCommentSfx
	uint32 GetPlayerTalkSfx(CPed *ped, int16 sound);
	uint32 GetCopTalkSfx(CPed *ped, int16 sound);
	uint32 GetSwatTalkSfx(CPed *ped, int16 sound);
	uint32 GetFBITalkSfx(CPed *ped, int16 sound);
	uint32 GetArmyTalkSfx(CPed *ped, int16 sound);
	uint32 GetMedicTalkSfx(CPed *ped, int16 sound);
	uint32 GetFiremanTalkSfx(CPed *ped, int16 sound);
	uint32 GetDefaultTalkSfx(CPed *ped, int16 sound);
	uint32 GetHFYSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetHFOSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetHMYSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetHMOSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetHFYRITalkSfx(CPed *ped, int16 sound);
	uint32 GetHFORITalkSfx(CPed *ped, int16 sound);
	uint32 GetHMYRITalkSfx(CPed *ped, int16 sound);
	uint32 GetHMORITalkSfx(CPed *ped, int16 sound);
	uint32 GetHFYBETalkSfx(CPed *ped, int16 sound);
	uint32 GetHFOBETalkSfx(CPed *ped, int16 sound);
	uint32 GetHMYBETalkSfx(CPed *ped, int16 sound);
	uint32 GetHMOBETalkSfx(CPed *ped, int16 sound);
	uint32 GetHFYBUTalkSfx(CPed *ped, int16 sound);
	uint32 GetHFYMDTalkSfx(CPed *ped, int16 sound);
	uint32 GetHFYCGTalkSfx(CPed *ped, int16 sound);
	uint32 GetHFYPRTalkSfx(CPed *ped, int16 sound);
	uint32 GetHFOTRTalkSfx(CPed *ped, int16 sound);
	uint32 GetHMOTRTalkSfx(CPed *ped, int16 sound);
	uint32 GetHMYAPTalkSfx(CPed *ped, int16 sound);
	uint32 GetHMOCATalkSfx(CPed *ped, int16 sound);
	uint32 GetBMODKTalkSfx(CPed *ped, int16 sound);
	uint32 GetBMYCRTalkSfx(CPed *ped, int16 sound);
	uint32 GetBFYSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetBFOSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetBMYSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetBMOSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetBFYRITalkSfx(CPed *ped, int16 sound);
	uint32 GetBFORITalkSfx(CPed *ped, int16 sound);
	uint32 GetBMYRITalkSfx(CPed *ped, int16 sound);
	uint32 GetBFYBETalkSfx(CPed *ped, int16 sound);
	uint32 GetBMYBETalkSfx(CPed *ped, int16 sound);
	uint32 GetBFOBETalkSfx(CPed *ped, int16 sound);
	uint32 GetBMOBETalkSfx(CPed *ped, int16 sound);
	uint32 GetBMYBUTalkSfx(CPed *ped, int16 sound);
	uint32 GetBFYPRTalkSfx(CPed *ped, int16 sound);
	uint32 GetBFOTRTalkSfx(CPed *ped, int16 sound);
	uint32 GetBMOTRTalkSfx(CPed *ped, int16 sound);
	uint32 GetBMYPITalkSfx(CPed *ped, int16 sound);
	uint32 GetBMYBBTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYCRTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFOSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMOSTTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYRITalkSfx(CPed *ped, int16 sound);
	uint32 GetWFORITalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYRITalkSfx(CPed *ped, int16 sound);
	uint32 GetWMORITalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYBETalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYBETalkSfx(CPed *ped, int16 sound);
	uint32 GetWFOBETalkSfx(CPed *ped, int16 sound);
	uint32 GetWMOBETalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYCWTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYGOTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFOGOTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMOGOTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYLGTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYLGTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYBUTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYBUTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMOBUTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYPRTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFOTRTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMOTRTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYPITalkSfx(CPed *ped, int16 sound);
	uint32 GetWMOCATalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYJGTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYJGTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYSKTalkSfx(CPed *ped, int16 sound);
	uint32 GetWMYSKTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYSHTalkSfx(CPed *ped, int16 sound);
	uint32 GetWFOSHTalkSfx(CPed *ped, int16 sound);
	uint32 GetJFOTOTalkSfx(CPed *ped, int16 sound);
	uint32 GetJMOTOTalkSfx(CPed *ped, int16 sound);
	uint32 GetCBTalkSfx(CPed *ped, int16 sound);
	uint32 GetHNTalkSfx(CPed *ped, int16 sound);
	uint32 GetSGTalkSfx(CPed *ped, int16 sound);
	uint32 GetCLTalkSfx(CPed *ped, int16 sound);
	uint32 GetGDTalkSfx(CPed *ped, int16 sound);
	uint32 GetBKTalkSfx(CPed *ped, int16 sound);
	uint32 GetPGTalkSfx(CPed *ped, int16 sound);
	uint32 GetVICETalkSfx(CPed *ped, int16 sound, int16 model);
	uint32 GetWFYG1TalkSfx(CPed *ped, int16 sound);
	uint32 GetWFYG2TalkSfx(CPed *ped, int16 sound);

	uint32 GetGenericMaleTalkSfx(CPed *ped, int16 sound);   // todo names (inlined in vc)
	uint32 GetGenericFemaleTalkSfx(CPed *ped, int16 sound); // todo names (inlined in vc)
	// end of functions returning talk sfx

	void GenerateIntegerRandomNumberTable();
	char *Get3DProviderName(uint8 id) const;
	char GetCDAudioDriveLetter() const;
	int8 GetCurrent3DProviderIndex() const;
	int8 AutoDetect3DProviders() const;
	float GetCollisionLoopingRatio(uint32 a, uint32 b, float c) const; // not used
	float GetCollisionOneShotRatio(int32 a, float b) const;
	float GetCollisionRatio(float a, float b, float c, float d) const; // inlined in vc
	float GetDistanceSquared(const CVector &v) const; // inlined in vc
	int32 GetJumboTaxiFreq() const; // inlined in vc
	uint8 GetMissionAudioLoadingStatus(uint8 slot) const;
	int8 GetMissionScriptPoliceAudioPlayingStatus() const;
	uint8 GetNum3DProvidersAvailable() const;
	uint32 GetPedCommentSfx(CPed *ped, int32 sound);
	void GetPhrase(uint32 &phrase, uint32 &prevPhrase, uint32 sample, uint32 maxOffset) const;
	float GetVehicleDriveWheelSkidValue(CVehicle *veh, tWheelState wheelState, float gasPedalAudio, cTransmission *transmission,
	                                    float velocityChange);
	float GetVehicleNonDriveWheelSkidValue(CVehicle *veh, tWheelState wheelState, cTransmission *transmission, float velocityChange);

	bool8 HasAirBrakes(int32 model) const;

	void Initialise();
	void InitialisePoliceRadio();
	void InitialisePoliceRadioZones();
	void InterrogateAudioEntities(); // inlined
	bool8 IsAudioInitialised() const;
	bool8 IsMissionAudioSampleFinished(uint8 slot);
	bool8 IsMP3RadioChannelAvailable() const;

	bool8 MissionScriptAudioUsesPoliceChannel(int32 soundMission) const;

	void PlayLoadedMissionAudio(uint8 slot);
	void PlayOneShot(int32 index, uint16 sound, float vol);
	void PlaySuspectLastSeen(float x, float y, float z);
	void PlayerJustGotInCar() const;
	void PlayerJustLeftCar() const;
	void PostInitialiseGameSpecificSetup();
	void PostTerminateGameSpecificShutdown();
	void PreInitialiseGameSpecificSetup() const;
	void PreloadMissionAudio(uint8 slot, Const char *name);
	void PreTerminateGameSpecificShutdown();
	/// processX - main logic of adding new sounds
	void ProcessActiveQueues();
	bool8 ProcessAirBrakes(cVehicleParams& params);
	bool8 ProcessBoatEngine(cVehicleParams& params);          
	bool8 ProcessBoatMovingOverWater(cVehicleParams& params);
#ifdef GTA_BRIDGE
	void ProcessBridge();
	void ProcessBridgeMotor();
	void ProcessBridgeOneShots();
	void ProcessBridgeWarning();
#endif
	bool8 ProcessCarBombTick(cVehicleParams& params);
	void ProcessCarHeli(cVehicleParams& params);
	void ProcessCesna(cVehicleParams& params);
	//void ProcessCrane();
	bool8 ProcessEngineDamage(cVehicleParams& params);
	void ProcessEntity(int32 sound);
	void ProcessExplosions(int32 explosion);
	void ProcessFireHydrant();
	void ProcessFires(int32 entity);
	void ProcessFrontEnd();
	void ProcessGarages();
	void ProcessJumbo(cVehicleParams& params);
	void ProcessJumboAccel(CPlane *plane);
	void ProcessJumboDecel(CPlane *plane);
	void ProcessJumboFlying();
	void ProcessJumboLanding(CPlane *plane);
	void ProcessJumboTakeOff(CPlane *plane);
	void ProcessJumboTaxi();
	void ProcessLoopingScriptObject(uint8 sound);
	void ProcessMissionAudio();
	void ProcessMissionAudioSlot(uint8 slot);
	void ProcessModelHeliVehicle(cVehicleParams& params);
	void ProcessModelVehicle(cVehicleParams& params);
	void ProcessOneShotScriptObject(uint8 sound);
	void ProcessPed(CPhysical *ped);
	void ProcessPedOneShots(cPedParams &params);
	void ProcessPhysical(int32 id);
	void ProcessPlane(cVehicleParams& params);
	void ProcessPlayerMood();
	void ProcessPlayersVehicleEngine(cVehicleParams& params, CVehicle* veh);
	void ProcessProjectiles();
	void ProcessRainOnVehicle(cVehicleParams& params);
	void ProcessReverb() const;
	bool8 ProcessReverseGear(cVehicleParams& params);
	void ProcessScriptObject(int32 id);
	void ProcessSpecial();
#ifdef GTA_TRAIN
	bool8 ProcessTrainNoise(cVehicleParams *params);
#endif
	void ProcessVehicle(CVehicle *vehicle);
	bool8 ProcessVehicleDoors(cVehicleParams &params);
	void ProcessVehicleEngine(cVehicleParams &params);
	void ProcessVehicleFlatTyre(cVehicleParams &params);
	bool8 ProcessVehicleHorn(cVehicleParams &params);
	void ProcessVehicleOneShots(cVehicleParams &params);
	bool8 ProcessVehicleReverseWarning(cVehicleParams &params);
	bool8 ProcessVehicleRoadNoise(cVehicleParams &params);
	bool8 ProcessVehicleSirenOrAlarm(cVehicleParams &params);
	bool8 ProcessVehicleSkidding(cVehicleParams &params);
	void ProcessWaterCannon(int32);
	void ProcessWeather(int32 id);
	bool8 ProcessWetRoadNoise(cVehicleParams& params);
	void ProcessEscalators();
	void ProcessExtraSounds();

	int32 RandomDisplacement(uint32 seed) const;
	void ReacquireDigitalHandle() const;
	void ReleaseDigitalHandle() const;
	void ReportCollision(CEntity *entity1, CEntity *entity2, uint8 surface1, uint8 surface2, float collisionPower, float intensity2);
	void ReportCrime(eCrimeType crime, const CVector &pos);
	void ResetAudioLogicTimers(uint32 timer);
	void ResetPoliceRadio();
	void ResetTimers(uint32 time);

	void Service();
	void ServiceCollisions();
	void ServicePoliceRadio();
	void ServicePoliceRadioChannel(uint8 wantedLevel);
	void ServiceSoundEffects();
	int8 SetCurrent3DProvider(uint8 which);
	void SetDynamicAcousticModelingStatus(bool8 status);
	void SetEffectsFadeVol(uint8 volume) const;
	void SetEffectsMasterVolume(uint8 volume) const;
	void SetMP3BoostVolume(uint8 volume) const;
	void SetEntityStatus(int32 id, bool8 status);
	uint32 SetLoopingCollisionRequestedSfxFreqAndGetVol(const cAudioCollision &audioCollision);
	void SetMissionAudioLocation(uint8 slot, float x, float y, float z);
	void SetMissionScriptPoliceAudio(int32 sfx) const; // inlined and optimized
	void SetMonoMode(bool8 mono);
	void SetMusicFadeVol(uint8 volume) const;
	void SetMusicMasterVolume(uint8 volume) const;
	void SetSpeakerConfig(int32 conf) const;
	void SetUpLoopingCollisionSound(const cAudioCollision &col, uint8 counter);
	void SetUpOneShotCollisionSound(const cAudioCollision &col);
	bool8 SetupCrimeReport();
	bool8 SetupJumboEngineSound(uint8 vol, uint32 freq);
	bool8 SetupJumboFlySound(uint8 emittingVol);
	bool8 SetupJumboRumbleSound(uint8 emittingVol);
	bool8 SetupJumboTaxiSound(uint8 vol);
	bool8 SetupJumboWhineSound(uint8 emittingVol, uint32 freq);
	void SetupPedComments(cPedParams &params, uint16 sound);
	void SetupSuspectLastSeenReport();

	void Terminate();
	void TranslateEntity(Const CVector *v1, CVector *v2) const;

	void UpdateGasPedalAudio(CVehicle *veh, int vehType);
	void UpdateReflections();
	bool8 UsesReverseWarning(int32 model) const;
	bool8 UsesSiren(cVehicleParams &params) const;
	bool8 UsesSirenSwitching(cVehicleParams &params) const;

	CVehicle *FindVehicleOfPlayer();
	void SetPedTalkingStatus(CPed *ped, bool8 status);
	void SetPlayersMood(uint8 mood, uint32 time);

	float Sqrt(float v) const { return v <= 0.0f ? 0.0f : ::Sqrt(v); }

#ifdef GTA_PC
	// only used in pc
	void AdjustSamplesVolume(); // inlined
	uint8 ComputeEmittingVolume(uint8 emittingVolume, float intensity, float dist); // inlined
#endif
};

/*
   Manual loop points are not on PS2 so let's have these macros to avoid massive ifndefs.
   Setting these manually was pointless anyway since they never change from sdt values.
   What were they thinking?
*/
#ifndef GTA_PS2
#define RESET_LOOP_OFFSETS \
	m_sQueueSample.m_nLoopStart = 0; \
	m_sQueueSample.m_nLoopEnd = -1;
#define SET_LOOP_OFFSETS(sample) \
	m_sQueueSample.m_nLoopStart = SampleManager.GetSampleLoopStartOffset(sample); \
	m_sQueueSample.m_nLoopEnd = SampleManager.GetSampleLoopEndOffset(sample);
#else
#define RESET_LOOP_OFFSETS
#define SET_LOOP_OFFSETS(sample)
#endif

#if defined(AUDIO_MSS) && !defined(PS2_AUDIO_CHANNELS)
static_assert(sizeof(cAudioManager) == 0x5558, "cAudioManager: error");
#endif

extern cAudioManager AudioManager;
