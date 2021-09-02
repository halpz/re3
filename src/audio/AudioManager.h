#pragma once

#include "audio_enums.h"
#include "AudioCollision.h"
#include "PolRadio.h"
#include "VehicleModelInfo.h"
#include "Vehicle.h"

class tSound
{
public:
	int32 m_nEntityIndex;		// audio entity index
	uint32 m_nCounter;			// I'm not sure what this is but it looks like a virtual counter to determine the same sound in queue
								// Values higher than 255 are used by reflections
	uint32 m_nSampleIndex;		// An index of sample from AudioSamples.h
	uint8 m_nBankIndex;			// A sound bank index. IDK what's the point of it here since samples are hardcoded anyway
	bool8 m_bIs2D;				// If TRUE then sound is played in 2D space (such as frontend or police radio)
	uint32 m_nPriority;			// The multiplier for the sound priority (see m_nFinalPriority below). Lesser value means higher priority
	uint32 m_nFrequency;		// Sound frequency, plain and simple
	uint8 m_nVolume;			// Sound volume (0..127), only used as an actual volume without EXTERNAL_3D_SOUND (see m_nEmittingVolume)
	float m_fDistance;			// Distance to camera (useless if m_bIs2D == TRUE)
	uint32 m_nLoopCount;		// 0 - always loop, 1 - don't loop, other values never seen
#ifndef GTA_PS2
	// Loop offsets
	uint32 m_nLoopStart;
	int32 m_nLoopEnd;
#endif
#ifdef EXTERNAL_3D_SOUND
	uint8 m_nEmittingVolume;	// The volume in 3D space, provided to 3D audio engine
#endif
	float m_fSpeedMultiplier;	// Used for doppler effect. 0.0f - unaffected by doppler
	float m_MaxDistance;		// The maximum distance at which sound could be heard. Minimum distance = MaxDistance / 5 or MaxDistance / 4 in case of emitting volume (useless if m_bIs2D == TRUE)
	bool8 m_bStatic;			// If TRUE then sound parameters cannot be changed during playback (frequency, position, etc.)
	CVector m_vecPos;			// Position of sound in 3D space. Unused if m_bIs2D == TRUE
#if !defined(GTA_PS2) || defined(AUDIO_REVERB) // GTA_PS2 because this field exists on mobile but not on PS2
	bool8 m_bReverb;			// Toggles reverb effect
#endif
#ifdef AUDIO_REFLECTIONS
	uint8 m_nReflectionDelay;	// Number of frames before reflection could be played. This is calculated internally by AudioManager and shouldn't be set by queued sample
	bool8 m_bReflections;		// Add sound reflections
#endif
	uint8 m_nPan;				// Sound panning (0-127). Controls the volume of the playback coming from left and right speaker. Calculated internally unless m_bIs2D==TRUE.
								// 0 =   L 100%  R 0%
								// 63 =  L 100%  R 100%
								// 127 = L 0%    R 100%
	uint8 m_nFrontRearPan;		// Used on PS2 for surround panning
#ifndef FIX_BUGS
	uint32 m_nFramesToPlay;		// Number of frames the sound would be played (if it stops being queued).
								// This one is being set by queued sample for looping sounds, otherwise calculated inside AudioManager
#else
	float m_nFramesToPlay;		// Made into float for high fps fix
#endif

	// all fields below are internal to AudioManager calculations and aren't set by queued sample
	bool8 m_bIsBeingPlayed;		// Set to TRUE when the sound was added or changed on current frame to avoid it being overwritten
	bool8 m_bIsPlayingFinished;	// Not sure about the name. Set to TRUE when sampman channel becomes free
	uint32 m_nFinalPriority;	// Actual value used to compare priority, calculated using volume and m_nPriority. Lesser value means higher priority
	int8 m_nVolumeChange;		// How much m_nVolume should reduce per each frame.
#if defined(FIX_BUGS) && defined(EXTERNAL_3D_SOUND)
	int8 m_nEmittingVolumeChange; // same as above but for m_nEmittingVolume
#endif
	uint8 field_51_lcs;
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
	bool8 m_bStatus;
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
	uint8 m_nVolume;
	int8 m_nLoadingTimeout; // how many iterations we gonna wait until dropping the sample if it's still not loaded (only useful on PS2)
#if defined(EXTERNAL_3D_SOUND) && defined(FIX_BUGS)
	uint8 m_nEmittingVolume;
#endif
};

VALIDATE_SIZE(tPedComment, 28);

class cPedComments
{
public:
	tPedComment m_aPedCommentQueue[NUM_SOUND_QUEUES][NUM_PED_COMMENTS_SLOTS];
	uint8 m_aPedCommentOrderList[NUM_SOUND_QUEUES][NUM_PED_COMMENTS_SLOTS];
	uint8 m_nPedCommentCount[NUM_SOUND_QUEUES];
	uint8 m_nActiveQueue;
#ifdef GTA_PC
	bool8 m_bDelay;
	uint32 m_nDelayTimer;
#endif

	cPedComments()
	{
		for (int i = 0; i < NUM_PED_COMMENTS_SLOTS; i++)
			for (int j = 0; j < NUM_SOUND_QUEUES; j++) {
				m_aPedCommentQueue[j][i].m_nLoadingTimeout = -1;
				m_aPedCommentOrderList[j][i] = NUM_PED_COMMENTS_SLOTS;
			}

		for (int i = 0; i < NUM_SOUND_QUEUES; i++)
			m_nPedCommentCount[i] = 0;
		m_nActiveQueue = 0;
	}
	void Add(tPedComment *com);
	void Process();
};

VALIDATE_SIZE(cPedComments, 0x490);

#ifdef FIX_BUGS // LCS extends the number of mission slots but not audio channels, the game would crash on ClearMissionAudio trying to stop channels that don't exist
#define MISSION_AUDIO_SLOTS (2)
#else
#define MISSION_AUDIO_SLOTS (5)
#endif

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
class CEntity;
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
	uint32 m_nIndex;
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

#if GTA_VERSION < GTAVC_PC_10
enum {
	/*
	REFLECTION_YMAX = 0, top
	REFLECTION_YMIN = 1, bottom
	REFLECTION_XMIN = 2, left
	REFLECTION_XMAX = 3, right
	REFLECTION_ZMAX = 4,
	*/

	REFLECTION_TOP = 0,
	REFLECTION_BOTTOM,
	REFLECTION_LEFT,
	REFLECTION_RIGHT,
	REFLECTION_UP,
	MAX_REFLECTIONS,
};
#else
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
#endif

enum PLAY_STATUS { PLAY_STATUS_STOPPED = 0, PLAY_STATUS_PLAYING, PLAY_STATUS_FINISHED };
enum LOADING_STATUS { LOADING_STATUS_NOT_LOADED = 0, LOADING_STATUS_LOADED, LOADING_STATUS_LOADING };

class cAudioManager
{
public:
	bool8 m_bIsInitialised;
	bool8 m_bIsSurround; // used on PS2
	bool8 m_bReduceReleasingPriority;
	uint8 m_nActiveSamples;
	bool8 m_bDoubleVolume; // unused
	bool8 m_bDynamicAcousticModelingStatus;
	uint8 m_nChannelOffset;
	float m_fSpeedOfSound;
	bool8 m_bTimerJustReset;
	uint32 m_nTimer;
	tSound m_sQueueSample;
	uint8 m_nActiveQueue;
	tSound m_aRequestedQueue[NUM_SOUND_QUEUES][NUM_CHANNELS_GENERIC];
	uint8 m_aRequestedOrderList[NUM_SOUND_QUEUES][NUM_CHANNELS_GENERIC];
	uint8 m_nRequestedCount[NUM_SOUND_QUEUES];
	tSound m_asActiveSamples[NUM_CHANNELS_GENERIC];
	tAudioEntity m_asAudioEntities[NUM_AUDIOENTITIES];
	uint32 m_aAudioEntityOrderList[NUM_AUDIOENTITIES];
	uint32 m_nAudioEntitiesCount;
#ifdef AUDIO_REFLECTIONS
	CVector m_avecReflectionsPos[MAX_REFLECTIONS];
	float m_afReflectionsDistances[MAX_REFLECTIONS];
#endif
	cAudioScriptObjectManager m_sAudioScriptObjectManager;

	bool8 field_4348_lcs;
	// miami
	bool8 m_bIsPlayerShutUp;
	uint8 m_nPlayerMood;
	uint32 m_nPlayerMoodTimer;
	uint32 field_4B38_vc;
	bool8 m_bGenericSfx;

	cPedComments m_sPedComments;
	int32 m_nFireAudioEntity;
	int32 m_nWaterCannonEntity;
	int32 m_nPoliceChannelEntity;
	cPoliceRadioQueue m_sPoliceRadioQueue;
	cAMCrime m_aCrimes[10];
	int32 m_nFrontEndEntity;
	int32 m_nCollisionEntity;
	cAudioCollisionManager m_sCollisionManager;
	int32 m_nProjectileEntity;
	int32 m_nEscalatorEntity;
	int32 m_nExtraSoundsEntity;
#ifdef GTA_BRIDGE
	int32 m_nBridgeEntity;
#endif

	// Mission audio stuff
	// So instead of making an array of struct they've added [MISSION_AUDIO_SLOTS] to every field...
	// Only someone with a VERY EXTRAORDINARY mind could have come up with that
	CVector m_vecMissionAudioPosition[MISSION_AUDIO_SLOTS];
	bool8 m_bIsMissionAudio2D[MISSION_AUDIO_SLOTS];
	uint32 m_nMissionAudioSampleIndex[MISSION_AUDIO_SLOTS];
	uint8 m_nMissionAudioLoadingStatus[MISSION_AUDIO_SLOTS];
	uint8 m_nMissionAudioPlayStatus[MISSION_AUDIO_SLOTS];
	bool8 m_bIsMissionAudioPlaying[MISSION_AUDIO_SLOTS];
	int32 m_nMissionAudioFramesToPlay[MISSION_AUDIO_SLOTS]; // possibly unsigned
	bool8 m_bIsMissionAudioAllowedToPlay[MISSION_AUDIO_SLOTS];
	bool8 m_bIsMissionAudioPhoneCall[MISSION_AUDIO_SLOTS];
	uint8 m_nGlobalSfxVolumeMultiplier; // used to lower sfx volume during phone calls

	int32 m_anRandomTable[5];
	uint8 m_nTimeSpent;
	bool8 m_bIsPaused;
	bool8 m_bWasPaused;
	uint32 m_FrameCounter;

	uint32 field_5644_lcs;
	uint32 field_5648_lcs;
	uint8 field_564C_lcs;

	cAudioManager();
	~cAudioManager();

	void Initialise();
	void Terminate();
	void Service();
	int32 CreateEntity(eAudioType type, void *entity);
	void DestroyEntity(int32 id); // inlined in vc
	bool8 GetEntityStatus(int32 id);
	void SetEntityStatus(int32 id, bool8 status);
	void *GetEntityPointer(int32 id);
	void PlayOneShot(int32 index, uint16 sound, float vol);
	void SetEffectsMasterVolume(uint8 volume);
	void SetMusicMasterVolume(uint8 volume);
	void SetMP3BoostVolume(uint8 volume);
	void SetEffectsFadeVol(uint8 volume);
	void SetMusicFadeVol(uint8 volume);
	void SetOutputMode(bool8 surround);
	void ResetTimers(uint32 time);
	void DestroyAllGameCreatedEntities();
	
#ifdef GTA_PC
	uint8 GetNum3DProvidersAvailable();
	char *Get3DProviderName(uint8 id);
	int8 GetCurrent3DProviderIndex();
	int8 AutoDetect3DProviders();
	int8 SetCurrent3DProvider(uint8 which);
	void SetSpeakerConfig(int32 conf);
	bool8 IsMP3RadioChannelAvailable();
	void ReleaseDigitalHandle();
	void ReacquireDigitalHandle();
#ifdef AUDIO_REFLECTIONS
	void SetDynamicAcousticModelingStatus(bool8 status);
#endif
	bool8 CheckForAnAudioFileOnCD();
	char GetCDAudioDriveLetter();
	bool8 IsAudioInitialised();
#endif

	void ServiceSoundEffects();
	uint8 ComputeVolume(uint8 emittingVolume, float maxDistance, float distance);
	void TranslateEntity(Const CVector *v1, CVector *v2);
	int32 ComputeFrontRearMix(float, CVector *);
	int32 ComputePan(float, CVector *);
	uint32 ComputeDopplerEffectedFrequency(uint32 oldFreq, float position1, float position2, float speedMultiplier);
	int32 RandomDisplacement(uint32 seed);
	void InterrogateAudioEntities(); // inlined
	void AddSampleToRequestedQueue(uint8 unk_lcs = 0);
	void AddDetailsToRequestedOrderList(uint8 sample); // inlined in vc
#ifdef AUDIO_REFLECTIONS
	void AddReflectionsToRequestedQueue();
	void UpdateReflections();
#endif
	void AddReleasingSounds();
	void ProcessActiveQueues();
	void ClearRequestedQueue(); // inlined in vc
	void ClearActiveSamples();
	void GenerateIntegerRandomNumberTable();
#ifdef GTA_PS2
	void LoadBankIfNecessary(uint8 bank); // this is used only on PS2 but technically not a platform code
#endif
	void DirectlyEnqueueSample(uint32 sample, uint8 bank, uint32 counter, uint32 priority, uint32 freq, uint8 volume, uint8 framesToPlay, uint32 notStereo = 0);

#ifdef EXTERNAL_3D_SOUND // actually must have been && AUDIO_MSS as well
	void AdjustSamplesVolume(); // inlined
	uint8 ComputeEmittingVolume(uint8 emittingVolume, float maxDistance, float distance); // inlined
#endif

	// audio logic
	void PreInitialiseGameSpecificSetup();
	void PostInitialiseGameSpecificSetup();
	void PreTerminateGameSpecificShutdown();
	void PostTerminateGameSpecificShutdown();
	void ResetAudioLogicTimers(uint32 timer);
	void ProcessReverb();
	float GetDistanceSquared(const CVector &v); // inlined in vc
	void CalculateDistance(bool8 &condition, float dist);
	CVehicle *FindVehicleOfPlayer();
	void ProcessSpecial();
	void ProcessEntity(int32 sound);
	void ProcessPhysical(int32 id);

	// vehicles
	void ProcessVehicle(CVehicle *vehicle);
	bool8 ProcessCarHeli(cVehicleParams &params);
	void ProcessRainOnVehicle(cVehicleParams &params);
	bool8 ProcessReverseGear(cVehicleParams &params);
	void ProcessModelHeliVehicle(cVehicleParams &params);
	void ProcessModelVehicle(cVehicleParams &params);
	bool8 ProcessVehicleFlatTyre(cVehicleParams &params);
	bool8 ProcessVehicleRoadNoise(cVehicleParams &params);
	bool8 ProcessWetRoadNoise(cVehicleParams &params);
	bool8 ProcessVehicleEngine(cVehicleParams &params);
	void UpdateGasPedalAudio(CVehicle *veh, int vehType);
	void PlayerJustGotInCar();
	void PlayerJustLeftCar();
	void AddPlayerCarSample(uint8 emittingVolume, uint32 freq, uint32 sample, uint8 bank, uint8 counter, bool8 notLooping);
	void ProcessCesna(cVehicleParams &params);
	void ProcessPlayersVehicleEngine(cVehicleParams &params, CVehicle *veh);
	bool8 ProcessVehicleSkidding(cVehicleParams &params);
	float GetVehicleDriveWheelSkidValue(CVehicle *veh, tWheelState wheelState, float gasPedalAudio, cTransmission *transmission, float velocityChange);
	float GetVehicleNonDriveWheelSkidValue(CVehicle *veh, tWheelState wheelState, cTransmission *transmission, float velocityChange);
	bool8 ProcessVehicleHorn(cVehicleParams &params);
	bool8 UsesSiren(cVehicleParams &params);
	bool8 UsesSirenSwitching(cVehicleParams &params);
	bool8 ProcessVehicleSirenOrAlarm(cVehicleParams &params);
	bool8 UsesReverseWarning(uint32 model);
	bool8 ProcessVehicleReverseWarning(cVehicleParams &params);
	bool8 ProcessVehicleDoors(cVehicleParams &params);
	bool8 ProcessAirBrakes(cVehicleParams &params);
	bool8 HasAirBrakes(uint32 model);
	bool8 ProcessEngineDamage(cVehicleParams &params);
	bool8 ProcessCarBombTick(cVehicleParams &params);
	void ProcessVehicleOneShots(cVehicleParams &params);
#ifdef GTA_TRAIN
	bool8 ProcessTrainNoise(cVehicleParams &params);
#endif
	bool8 ProcessFerryNoise(cVehicleParams &params);
	bool8 ProcessBoatEngine(cVehicleParams &params);
	bool8 ProcessBoatMovingOverWater(cVehicleParams &params);
	void ProcessPlane(cVehicleParams &params);
	void ProcessJumbo(cVehicleParams &params);
	void ProcessJumboTaxi();
	void ProcessJumboAccel(CPlane *plane);
	void ProcessJumboTakeOff(CPlane *plane);
	void ProcessJumboFlying();
	void ProcessJumboLanding(CPlane *plane);
	void ProcessJumboDecel(CPlane *plane);
	bool8 SetupJumboTaxiSound(uint8 vol);
	bool8 SetupJumboWhineSound(uint8 emittingVol, uint32 freq);
	bool8 SetupJumboEngineSound(uint8 vol, uint32 freq);
	bool8 SetupJumboFlySound(uint8 emittingVol);
	bool8 SetupJumboRumbleSound(uint8 emittingVol);
	int32 GetJumboTaxiFreq(); // inlined in vc

	// peds
	void ProcessPed(CPhysical *ped);
	void ProcessPedOneShots(cPedParams &params);
	void SetPedTalkingStatus(CPed *ped, bool8 status);
	void SetPlayersMood(uint8 mood, uint32 time);
	void ProcessPlayerMood();

	// ped comments
	void SetupPedComments(cPedParams &params, uint16 sound);
	uint32 GetPedCommentSfx(CPed *ped, uint16 sound);
	void GetPhrase(uint32 &phrase, uint32 &prevPhrase, uint32 sample, uint32 maxOffset);
	uint32 GetPlayerTalkSfx(CPed *ped, uint16 sound);
	uint32 GetMariaTalkSfx(CPed *ped, uint16 sound);
	uint32 GetDonaldLoveTalkSfx(CPed *ped, uint16 sound);
	uint32 GetJdOtooleTalkSfx(CPed *ped, uint16 sound);
	uint32 GetleonMcaffreyTalkSfx(CPed *ped, uint16 sound);
	uint32 GetSalvatoreTalkSfx(CPed *ped, uint16 sound);
	uint32 GetToshikoTalkSfx(CPed *ped, uint16 sound);
	uint32 GetMickeyHamfistsTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBiker1TalkSfx(CPed *ped, uint16 sound);
	uint32 GetBiker2TalkSfx(CPed *ped, uint16 sound);
	uint32 GetGrdAng1TalkSfx(CPed *ped, uint16 sound);
	uint32 GetGrdAng2TalkSfx(CPed *ped, uint16 sound);
	uint32 GetGenericMaleTalkSfx(CPed *ped, uint16 sound);   // inlined in vc
	uint32 GetGenericFemaleTalkSfx(CPed *ped, uint16 sound); // inlined in vc
	uint32 GetDefaultTalkSfx(CPed *ped, uint16 sound);
	uint32 GetCopTalkSfx(CPed *ped, uint16 sound);
	uint32 GetSwatTalkSfx(CPed *ped, uint16 sound);
	uint32 GetFBITalkSfx(CPed *ped, uint16 sound);
	uint32 GetArmyTalkSfx(CPed *ped, uint16 sound);
	uint32 GetMedicTalkSfx(CPed *ped, uint16 sound);
	uint32 GetFiremanTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYG1TalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYG2TalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFYSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFOSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMYSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMOSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFYRITalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFORITalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMYRITalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMORITalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFYBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFOBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMYBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMOBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFYBUTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFYMDTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFYCGTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFYPRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHFOTRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMOTRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMOCATalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMYCRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFYSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFOSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMYSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMOSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFYRITalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFORITalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMYRITalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFYBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMYBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFOBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMOBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMYBUTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFYPRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBFOTRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMOTRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMYPITalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMYBBTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYCRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYSKTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYSKTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFOSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMOSTTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYRITalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFORITalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYRITalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMORITalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFOBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMOBETalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYCWTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYGOTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFOGOTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMOGOTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYLGTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYLGTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYBUTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYBUTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMOBUTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYPRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFOTRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMOTRTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYPITalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMOCATalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYSHTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFOSHTalkSfx(CPed *ped, uint16 sound);
	uint32 GetJFOTOTalkSfx(CPed *ped, uint16 sound);
	uint32 GetJMOTOTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHNTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBKTalkSfx(CPed *ped, uint16 sound);
	uint32 GetCBTalkSfx(CPed *ped, uint16 sound);
	uint32 GetSGTalkSfx(CPed *ped, uint16 sound);
	uint32 GetCLTalkSfx(CPed *ped, uint16 sound);
	uint32 GetGDTalkSfx(CPed *ped, uint16 sound);
	uint32 GetPGTalkSfx(CPed *ped, uint16 sound);
	uint32 GetViceWhiteTalkSfx(CPed *ped, uint16 sound);
	uint32 GetViceBlackTalkSfx(CPed *ped, uint16 sound);
	uint32 GetBMODKTalkSfx(CPed *ped, uint16 sound);
	uint32 GetHMYAPTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWFYJGTalkSfx(CPed *ped, uint16 sound);
	uint32 GetWMYJGTalkSfx(CPed *ped, uint16 sound);
	uint32 GetSpecialCharacterTalkSfx(CPed *ped, int32 model, uint16 sound);

	void DebugPlayPedComment(int32 sound);

	// particles
	void ProcessExplosions(int32 explosion);
	void ProcessFires(int32 entity);
	void ProcessWaterCannon(int32);

	// script objects
	void ProcessScriptObject(int32 id);
	void ProcessOneShotScriptObject(uint8 sound);
	void ProcessLoopingScriptObject(uint8 sound);

	// misc
	void ProcessWeather(int32 id);
	void ProcessFrontEnd();
	//void ProcessCrane();
	void ProcessProjectiles();
	void ProcessEscalators();
	void ProcessExtraSounds();
	void ProcessGarages();
	void ProcessFireHydrant();

#ifdef GTA_BRIDGE
	void ProcessBridge();
#endif

	// mission audio
	const char *GetMissionAudioLoadedLabel(uint8 slot);
	bool8 MissionScriptAudioUsesPoliceChannel(uint32 soundMission);
	void PreloadMissionAudio(uint8 slot, Const char *name);
	uint8 GetMissionAudioLoadingStatus(uint8 slot);
	void SetMissionAudioLocation(uint8 slot, float x, float y, float z);
	void PlayLoadedMissionAudio(uint8 slot);
	bool8 ShouldDuckMissionAudio(uint8 slot);
	bool8 IsMissionAudioSamplePlaying(uint8 slot);
	bool8 IsMissionAudioSampleFinished(uint8 slot);
	void ClearMissionAudio(uint8 slot); // inlined in vc
	void ProcessMissionAudioSlot(uint8 slot);
	void ProcessMissionAudio();

	// police radio
	void InitialisePoliceRadioZones();
	void InitialisePoliceRadio();
	void ResetPoliceRadio();
	void SetMissionScriptPoliceAudio(uint32 sfx); // inlined and optimized
	int8 GetMissionScriptPoliceAudioPlayingStatus();
	void DoPoliceRadioCrackle();
	void ServicePoliceRadio();
	void ServicePoliceRadioChannel(uint8 wantedLevel);
	bool8 SetupCrimeReport();
	void SetupSuspectLastSeenReport();
	void ReportCrime(eCrimeType crime, const CVector &pos);
	void PlaySuspectLastSeen(float x, float y, float z);
	void AgeCrimes(); // inlined in vc
		
	// collision stuff
	void ReportCollision(CEntity *entity1, CEntity *entity2, uint8 surface1, uint8 surface2, float collisionPower, float intensity2);
	void ServiceCollisions();
	void SetUpOneShotCollisionSound(const cAudioCollision &col);
	void SetUpLoopingCollisionSound(const cAudioCollision &col, uint8 counter);
	uint32 SetLoopingCollisionRequestedSfxFreqAndGetVol(const cAudioCollision &audioCollision);
	float GetCollisionOneShotRatio(uint32 a, float b);
	float GetCollisionLoopingRatio(uint32 a, uint32 b, float c); // not used
	float GetCollisionRatio(float a, float b, float c, float d); // inlined in vc

	float Sqrt(float v) const { return v <= 0.0f ? 0.0f : ::Sqrt(v); }
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
#ifdef EXTERNAL_3D_SOUND
#define SET_EMITTING_VOLUME(vol) m_sQueueSample.m_nEmittingVolume = vol
#else
#define SET_EMITTING_VOLUME(vol)
#endif
#ifdef AUDIO_REFLECTIONS
#define SET_SOUND_REFLECTION(b) m_sQueueSample.m_bReflections = b
#else
#define SET_SOUND_REFLECTION(b)
#endif
#ifdef AUDIO_REVERB
#define SET_SOUND_REVERB(b) m_sQueueSample.m_bReverb = b
#else
#define SET_SOUND_REVERB(b)
#endif

#ifndef GTA_PS2
#define CHANNEL_PLAYER_VEHICLE_ENGINE m_nActiveSamples
#endif

//#if defined(AUDIO_MSS) && !defined(PS2_AUDIO_CHANNELS)
//static_assert(sizeof(cAudioManager) == 0x5558, "cAudioManager: error");
//#endif


extern cAudioManager AudioManager;

enum
{
	PED_COMMENT_VOLUME = 127,
	PED_COMMENT_VOLUME_BEHIND_WALL = 31,
	COLLISION_MAX_DIST = 60,
};
