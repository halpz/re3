#pragma once

#include "AudioSamples.h"
#include "DMAudio.h"
#include "common.h"

class tActiveSample
{
public:
	int32 m_nEntityIndex;
	int32 field_4;
	int32 m_nSampleIndex;
	uint8 m_bBankIndex;
	uint8 m_bIsDistant;
	uint8 field_14;
	uint8 field_15;
	int32 field_16;
	int32 m_nFrequency;
	uint8 m_bVolume;
	uint8 field_25;
	uint8 field_26;
	uint8 field_27;
	float m_fDistance;
	int32 m_nLoopCount;
	int32 m_nLoopStart;
	int32 m_nLoopEnd;
	uint8 m_bEmittingVolume;
	uint8 field_45;
	uint8 field_46;
	uint8 field_47;
	float field_48;
	float m_fSoundIntensity;
	uint8 field_56;
	uint8 field_57;
	uint8 field_58;
	uint8 field_59;
	CVector m_vecPos;
	uint8 m_bReverbFlag;
	uint8 m_bLoopsRemaining;
	uint8 m_bRequireReflection;
	uint8 m_bOffset;
	int32 field_76;
	uint8 m_bIsProcessed;
	uint8 m_bLoopEnded;
	uint8 field_82;
	uint8 field_83;
	int32 calculatedVolume;
	uint8 field_88;
	uint8 field_89;
	uint8 field_90;
	uint8 field_91;
};

static_assert(sizeof(tActiveSample) == 92, "tActiveSample: error");

enum eAudioType : int32 {
	AUDIOTYPE_PHYSICAL = 0,
	AUDIOTYPE_EXPLOSION = 1,
	AUDIOTYPE_FIRE = 2,
	AUDIOTYPE_WEATHER = 3,
	AUDIOTYPE_CRANE = 4,
	AUDIOTYPE_SCRIPTOBJECT = 5,
	AUDIOTYPE_BRIDGE = 6,
	AUDIOTYPE_COLLISION = 7,
	AUDIOTYPE_FRONTEND = 8,
	AUDIOTYPE_PROJECTILE = 9,
	AUDIOTYPE_GARAGE = 10,
	AUDIOTYPE_FIREHYDRANT = 11,
	AUDIOTYPE_WATERCANNON = 12,
	AUDIOTYPE_POLICERADIO = 13,
	TOTAL_AUDIO_TYPES = 14,
};

class CPhysical;
class CAutomobile;

class tAudioEntity
{
public:
	eAudioType m_nType;
	void *m_pEntity;
	bool m_bIsUsed;
	uint8 m_bStatus;
	int16 m_awAudioEvent[4];
	uint8 gap_18[2];
	float m_afVolume[4];
	uint8 field_24; // is looping
	uint8 field_25[3];
};

static_assert(sizeof(tAudioEntity) == 40, "tAudioEntity: error");

class tPedComment
{
public:
	int m_nSampleIndex;
	int field_4;
	CVector m_vecPos;
	float m_fDistance;
	uint8 m_bVolume;
	uint8 field_25;
	uint8 gap_26[2];
};

static_assert(sizeof(tPedComment) == 28, "tPedComment: error");

class cPedComments
{
public:
	tPedComment m_asPedComments[2][20];
	uint8 field_1120[2][20];
	uint8 nrOfCommentsInBank[2];
	uint8 activeBank;
	uint8 gap_1163[1];

	void Add(tPedComment *com); /// ok
};

static_assert(sizeof(cPedComments) == 1164, "cPedComments: error");

class CEntity;

class cAudioCollision
{
public:
	CEntity *m_pEntity1;
	CEntity *m_pEntity2;
	uint8 m_bSurface1;
	uint8 m_bSurface2;
	uint8 field_10;
	uint8 field_11;
	float m_fIntensity1;
	float m_fIntensity2;
	CVector m_vecPosition;
	float m_fDistance;
	int32 m_nBaseVolume;
};

static_assert(sizeof(cAudioCollision) == 40, "cAudioCollision: error");

class cAudioCollisionManager
{
public:
	cAudioCollision m_asCollisions1[10];
	cAudioCollision m_asCollisions2[10];
	uint8 m_bIndicesTable[10];
	uint8 m_bCollisionsInQueue;
	uint8 gap_811;
	cAudioCollision m_sQueue;
};

static_assert(sizeof(cAudioCollisionManager) == 852, "cAudioCollisionManager: error");

class cMissionAudio
{
public:
	CVector m_vecPos;
	uint8 field_12;
	uint8 gap_13[3];
	int m_nSampleIndex;
	uint8 m_bLoadingStatus;
	uint8 m_bPlayStatus;
	uint8 field_22;
	uint8 field_23;
	int field_24;
	bool m_bIsPlayed;
	uint8 field_29;
	uint8 field_30;
	uint8 field_31;
};

static_assert(sizeof(cMissionAudio) == 32, "cMissionAudio: error");

class cVehicleParams;
class CPlane;
class CVehicle;
class CPed;
class cPedParams;

class cAudioScriptObject {
public:
	int16 AudioId;
	char _pad0[2];
	CVector Posn;
	int32 AudioEntity;

	static void *operator new(size_t);
	static void *operator new(size_t, int);
	static void operator delete(void *, size_t);
	static void operator delete(void *, int);
};

static_assert(sizeof(cAudioScriptObject) == 20, "cAudioScriptObject: error");

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

<<<<<<< HEAD
enum AudioEntityHandle
{
	AEHANDLE_NONE               = -5,
	AEHANDLE_ERROR_NOAUDIOSYS   = -4,
	AEHANDLE_ERROR_NOFREESLOT   = -3,
	AEHANDLE_ERROR_NOENTITY     = -2,
	AEHANDLE_ERROR_BADAUDIOTYPE = -1,
};

#define AEHANDLE_IS_FAILED(h) ((h)<0)
#define AEHANDLE_IS_OK(h)     ((h)>=0)

	
=======
>>>>>>> Cleanup
class cAudioManager
{
public:
	bool m_bIsInitialised;
	uint8 field_1;
	uint8 field_2;
	uint8 m_bActiveSamples;
	uint8 field_4;
	bool m_bDynamicAcousticModelingStatus;
	uint8 field_6;
	uint8 field_7;
	float speedOfSound;
	bool m_bTimerJustReset;
	uint8 field_13;
	uint8 field_14;
	uint8 field_15;
	int32 m_nTimer;
	tActiveSample m_sQueueSample;
	uint8 m_bActiveSampleQueue;
	uint8 gap_109[3];
	tActiveSample m_asSamples[2][27];
	uint8 m_abSampleQueueIndexTable[2][27];
	uint8 m_bSampleRequestQueuesStatus[2];
	tActiveSample m_asActiveSamples[27];
	tAudioEntity m_asAudioEntities[200];
	int32 m_anAudioEntityIndices[200];
	int32 m_nAudioEntitiesTotal;
	CVector m_avecReflectionsPos[5];
	float m_afReflectionsDistances[5];
	int32 m_anScriptObjectEntityIndices[40];
	int32 m_nScriptObjectEntityTotal;
	cPedComments m_sPedComments;
	int32 m_nFireAudioEntity;
	int32 m_nWaterCannonEntity;
	int32 m_nPoliceChannelEntity;
	uint8 gap45B8[444];
	int32 m_nFrontEndEntity;
	int32 m_nCollisionEntity;
	cAudioCollisionManager m_sCollisionManager;
	int32 m_nProjectileEntity;
	int32 m_nBridgeEntity;
	cMissionAudio m_sMissionAudio;
	int32 m_anRandomTable[5];
	uint8 field_19192;
	uint8 m_bUserPause;
	uint8 m_bPreviousUserPause;
	uint8 field_19195;
	uint32 m_FrameCounter;

	inline uint32 GetFrameCounter(void) { return m_FrameCounter; }
	float GetReflectionsDistance(int32 idx) { return m_afReflectionsDistances[idx]; }
<<<<<<< HEAD
	int32 GetRandomNumber(int32 idx) { return m_anRandomTable[idx]; }
=======
	int32 GetRandomTabe(int32 idx) { return m_anRandomTable[idx]; }

>>>>>>> Cleanup
	//

	void AddDetailsToRequestedOrderList(uint8 sample); /// ok
	void AddPlayerCarSample(uint8 emittingVolume, int32 freq, uint32 sample, uint8 unk1,
	                        uint8 unk2, bool notLooping); /// ok
	void AddReflectionsToRequestedQueue();                /// ok (check value)
	void AddReleasingSounds();                            // todo (difficult)
	void AddSampleToRequestedQueue();                     /// ok
	void AgeCrimes();                                     // todo
	int8 GetCurrent3DProviderIndex();                     /// ok

	void CalculateDistance(bool *ptr, float dist); /// ok
	bool CheckForAnAudioFileOnCD();                /// ok
	void ClearMissionAudio();                      /// ok
	void ClearRequestedQueue();                    /// ok
	int32 ComputeDopplerEffectedFrequency(uint32 oldFreq, float position1, float position2,
	                                      float speedMultiplier);                   /// ok
	int32 ComputePan(float, CVector *);                                             // todo
	uint32 ComputeVolume(int emittingVolume, float soundIntensity, float distance); /// ok
	int32 CreateEntity(int32 type, void *entity);                              /// ok

	void DestroyAllGameCreatedEntities(); /// ok
	void DestroyEntity(int32 id);         /// ok
	void DoPoliceRadioCrackle();          /// ok

	void GenerateIntegerRandomNumberTable(); /// ok

	float GetDistanceSquared(CVector *v); /// ok

	void TranslateEntity(CVector *v1, CVector *v2); /// ok

	// done

	void Initialise();
	void PostInitialiseGameSpecificSetup();
	void InitialisePoliceRadioZones();       // todo
	void ResetAudioLogicTimers(int32 timer); // todo

	void Terminate();

	char GetMissionScriptPoliceAudioPlayingStatus();
	bool GetMissionAudioLoadingStatus();

	uint8 GetNum3DProvidersAvailable();
	bool IsMP3RadioChannelAvailable();
	uint8 GetCDAudioDriveLetter();

	void SetEffectsMasterVolume(uint8 volume);
	void SetMusicMasterVolume(uint8 volume);
	void SetEffectsFadeVolume(uint8 volume);
	void SetMusicFadeVolume(uint8 volume);

	void SetSpeakerConfig(int32 conf);

	bool SetupJumboEngineSound(uint8, int32); // todo
	void PreInitialiseGameSpecificSetup();
	void SetMissionScriptPoliceAudio(int32 sfx);

	bool UsesSiren(int32 model);
	bool UsesSirenSwitching(int32 model);

	bool MissionScriptAudioUsesPoliceChannel(int32 soundMission);

	char *Get3DProviderName(uint8 id);

	bool SetupJumboFlySound(uint8 emittingVol);               /// ok
	bool SetupJumboRumbleSound(uint8 emittingVol);            /// ok
	bool SetupJumboTaxiSound(uint8 vol);                      /// ok
	bool SetupJumboWhineSound(uint8 emittingVol, int32 freq); /// ok

	void PlayLoadedMissionAudio();

	void SetMissionAudioLocation(float x, float y, float z);

	void ResetPoliceRadio();

	void InterrogateAudioEntities();

	bool UsesReverseWarning(int32 model);
	bool HasAirBrakes(int32 model);

	int32 GetJumboTaxiFreq();

	bool IsMissionAudioSampleFinished();

	void InitialisePoliceRadio(); // todo

	int32 RandomDisplacement(uint32 seed);

	void ReleaseDigitalHandle();
	void ReacquireDigitalHandle();
	void SetDynamicAcousticModelingStatus(bool status);

	bool IsAudioInitialised() const;

	void SetEntityStatus(int32 id, bool status);

	void PreTerminateGameSpecificShutdown();
	void PostTerminateGameSpecificShutdown();

	void PlayerJustGotInCar();
	void PlayerJustLeftCar();

	void Service();
	void GetPhrase(uint32 *phrase, uint32 *prevPhrase, uint32 sample, uint32 maxOffset);

	void DoJumboVolOffset();

	int32 GetPedCommentSfx(CPed *ped, int32 sound);

	uint32 GetPlayerTalkSfx(int16 sound);
	uint32 GetCopTalkSfx(int16 sound);
	uint32 GetSwatTalkSfx(int16 sound);
	uint32 GetFBITalkSfx(int16 sound);
	uint32 GetArmyTalkSfx(int16 sound);
	uint32 GetMedicTalkSfx(int16 sound);
	uint32 GetFiremanTalkSfx(int16 sound);
	uint32 GetNormalMaleTalkSfx(int16 sound);
	uint32 GetTaxiDriverTalkSfx(int16 sound);
	uint32 GetPimpTalkSfx(int16 sound);
	uint32 GetMafiaTalkSfx(int16 sound);
	uint32 GetTriadTalkSfx(int16 sound);
	uint32 GetDiabloTalkSfx(int16 sound);
	uint32 GetYakuzaTalkSfx(int16 sound);
	uint32 GetYardieTalkSfx(int16 sound);
	uint32 GetColumbianTalkSfx(int16 sound);
	uint32 GetHoodTalkSfx(int16 sound);
	uint32 GetBlackCriminalTalkSfx(int16 sound);
	uint32 GetWhiteCriminalTalkSfx(int16 sound);
	uint32 GetMaleNo2TalkSfx(int16 sound);
	uint32 GetBlackProjectMaleTalkSfx(int16 sound, int32 model);
	uint32 GetWhiteFatMaleTalkSfx(int16 sound);
	uint32 GetBlackFatMaleTalkSfx(int16 sound);
	uint32 GetBlackCasualFemaleTalkSfx(int16 sound);
	uint32 GetWhiteCasualFemaleTalkSfx(int16 sound);
	uint32 GetFemaleNo3TalkSfx(int16 sound);
	uint32 GetBlackFatFemaleTalkSfx(int16 sound);
	uint32 GetWhiteFatFemaleTalkSfx(int16 sound);
	uint32 GetBlackFemaleProstituteTalkSfx(int16 sound);
	uint32 GetWhiteFemaleProstituteTalkSfx(int16 sound);
	uint32 GetBlackProjectFemaleOldTalkSfx(int16 sound);
	uint32 GetBlackProjectFemaleYoungTalkSfx(int16 sound);
	uint32 GetChinatownMaleOldTalkSfx(int16 sound);
	uint32 GetChinatownMaleYoungTalkSfx(int16 sound);
	uint32 GetChinatownFemaleOldTalkSfx(int16 sound);
	uint32 GetChinatownFemaleYoungTalkSfx(int16 sound);
	uint32 GetLittleItalyMaleTalkSfx(int16 sound);
	uint32 GetLittleItalyFemaleOldTalkSfx(int16 sound);
	uint32 GetLittleItalyFemaleYoungTalkSfx(int16 sound);
	uint32 GetWhiteDockerMaleTalkSfx(int16 sound);
	uint32 GetBlackDockerMaleTalkSfx(int16 sound);
	uint32 GetScumMaleTalkSfx(int16 sound);
	uint32 GetScumFemaleTalkSfx(int16 sound);
	uint32 GetWhiteWorkerMaleTalkSfx(int16 sound);
	uint32 GetBlackWorkerMaleTalkSfx(int16 sound);
	uint32 GetBusinessMaleYoungTalkSfx(int16 sound, int32 model);
	uint32 GetBusinessMaleOldTalkSfx(int16 sound);
	uint32 GetWhiteBusinessFemaleTalkSfx(int16 sound, int32 model);
	uint32 GetBlackBusinessFemaleTalkSfx(int16 sound);
	uint32 GetSupermodelMaleTalkSfx(int16 sound);
	uint32 GetSupermodelFemaleTalkSfx(int16 sound);
	uint32 GetStewardMaleTalkSfx(int16 sound);
	uint32 GetStewardFemaleTalkSfx(int16 sound);
	uint32 GetFanMaleTalkSfx(int16 sound, int32 model);
	uint32 GetFanFemaleTalkSfx(int16 sound);
	uint32 GetHospitalMaleTalkSfx(int16 sound);
	uint32 GetHospitalFemaleTalkSfx(int16 sound);
	uint32 GetWhiteConstructionWorkerTalkSfx(int16 sound);
	uint32 GetBlackConstructionWorkerTalkSfx(int16 sound);
	uint32 GetShopperFemaleTalkSfx(int16 sound, int32 model);
	uint32 GetStudentMaleTalkSfx(int16 sound);
	uint32 GetStudentFemaleTalkSfx(int16 sound);
	uint32 GetCasualMaleOldTalkSfx(int16 sound);

	uint32 GetSpecialCharacterTalkSfx(int32 modelIndex, int32 sound);
	uint32 GetEightTalkSfx(int16 sound);
	uint32 GetFrankieTalkSfx(int16 sound);
	uint32 GetMistyTalkSfx(int16 sound);
	uint32 GetOJGTalkSfx(int16 sound);
	uint32 GetCatatalinaTalkSfx(int16 sound);
	uint32 GetBomberTalkSfx(int16 sound);
	uint32 GetSecurityGuardTalkSfx(int16 sound);
	uint32 GetChunkyTalkSfx(int16 sound);

	uint32 GetGenericMaleTalkSfx(int16 sound);
	uint32 GetGenericFemaleTalkSfx(int16 sound);

	void PlayOneShot(int32 index, int16 sound, float vol); // todo

	void ProcessActiveQueues();                              // todo
	bool ProcessAirBrakes(cVehicleParams *params);           /// ok
	void ProcessAirportScriptObject(uint8 sound);            /// ok
	bool ProcessBoatEngine(cVehicleParams *params);          /// ok
	bool ProcessBoatMovingOverWater(cVehicleParams *params); /// ok
	void ProcessBridge();                                    /// ok
	void ProcessBridgeMotor();                               /// ok
	void ProcessBridgeOneShots();                            /// ok
	void ProcessBridgeWarning();                             /// ok
	bool ProcessCarBombTick(cVehicleParams *params);         /// ok
	void ProcessCesna(void *);                               // todo requires CPlane
	void ProcessCinemaScriptObject(uint8 sound);             /// ok
	void ProcessCrane();                                     // todo requires CCrane
	void ProcessDocksScriptObject(uint8 sound);              /// ok
	bool ProcessEngineDamage(cVehicleParams *params);        /// ok
	void ProcessEntity(int32 sound);                         /// ok
	void ProcessExplosions(int32 explosion);                 /// ok
	void ProcessFireHydrant();                               /// ok
	void ProcessFires(int32 entity);                         // todo requires gFireManager
	void ProcessFrontEnd();                                  /// ok
	void ProcessGarages();                                   // todo requires CGarages::aGarages
	bool ProcessHelicopter(cVehicleParams *params);          /// ok
	void ProcessHomeScriptObject(uint8 sound);               /// ok
	void ProcessJumbo(cVehicleParams *);                     /// ok
	void ProcessJumboAccel(CPlane *plane);                   /// ok
	void ProcessJumboDecel(CPlane *plane);                   /// ok
	void ProcessJumboFlying();                               /// ok
	void ProcessJumboLanding(CPlane *plane);                 /// ok
	void ProcessJumboTakeOff(CPlane *plane);                 /// ok
	void ProcessJumboTaxi();                                 /// ok
	void ProcessLaunderetteScriptObject(uint8 sound);        /// ok
	void ProcessLoopingScriptObject(uint8 sound);            /// ok
	//	void ProcessMissionAudio();
	void ProcessModelCarEngine(cVehicleParams *params); ///  (check float comparisons)
	void ProcessOneShotScriptObject(uint8 sound);       /// ok
	void ProcessPed(CPhysical *ped);                    /// ok
	void ProcessPedHeadphones(cPedParams *params);      /// ok
	void ProcessPedOneShots(cPedParams *params);        /// ok
	void ProcessPhysical(int32 id);                     /// ok
	void ProcessPlane(cVehicleParams *params);          /// ok
	void ProcessPlayersVehicleEngine(cVehicleParams *params,
	                                 CAutomobile *automobile); /// ok (check float comparisons)
	void ProcessPoliceCellBeatingScriptObject(uint8 sound);    // todo
	void ProcessPornCinema(uint8 sound);                       /// ok
	void ProcessProjectiles();                                 // todo requires CProjectileInfo
	void ProcessRainOnVehicle(cVehicleParams *params);         /// ok
	//	void ProcessReverb();
	//	bool ProcessReverseGear(void *);
	void ProcessSawMillScriptObject(uint8 sound); /// ok
	void ProcessScriptObject(int32 id);           /// ok
	void ProcessShopScriptObject(uint8 sound);    /// ok
	void ProcessSpecial();                        /// ok
	//	bool ProcessTrainNoise(void *);
	void ProcessVehicle(CVehicle *); // todo
	//	bool ProcessVehicleDoors(void *);
	//	bool ProcessVehicleEngine(void *);
	//	void ProcessVehicleHorn(void *);
	//	void ProcessVehicleOneShots(void *);
	//	bool ProcessVehicleReverseWarning(void *);
	//	bool ProcessVehicleRoadNoise(void *);
	//	void ProcessVehicleSirenOrAlarm(void *);
	//	void ProcessVehicleSkidding(void *);
	void ProcessWaterCannon(int32); // todo
	void ProcessWeather(int32 id);  // todo
	//	bool ProcessWetRoadNoise(void *);
	void ProcessWorkShopScriptObject(uint8 sound); /// ok

	void SetupPedComments(cPedParams *params, uint32 sound); /// ok
};

static_assert(sizeof(cAudioManager) == 19220, "cAudioManager: error");

extern cAudioManager &AudioManager;
