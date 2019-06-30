#pragma once

#include "AudioSamples.h"
#include "DMAudio.h"
#include "common.h"

class tActiveSample
{
public:
	int m_nEntityIndex;
	int field_4;
	int m_nSampleIndex;
	char m_bBankIndex;
	char m_bIsDistant;
	char field_14;
	char field_15;
	int field_16;
	int m_nFrequency;
	uint8 m_bVolume;
	char field_25;
	char field_26;
	char field_27;
	float m_fDistance;
	int m_nLoopCount;
	int m_nLoopStart;
	int m_nLoopEnd;
	uint8 m_bEmittingVolume;
	char field_45;
	char field_46;
	char field_47;
	float field_48;
	float m_fSoundIntensity;
	char field_56;
	char field_57;
	char field_58;
	char field_59;
	CVector m_vecPos;
	char m_bReverbFlag;
	char m_bLoopsRemaining;
	char m_bRequireReflection;
	uint8 m_bOffset;
	int field_76;
	char m_bIsProcessed;
	char m_bLoopEnded;
	char field_82;
	char field_83;
	int field_84;
	char field_88;
	char field_89;
	char field_90;
	char field_91;
};

static_assert(sizeof(tActiveSample) == 0x5c, "tActiveSample: error");

enum eAudioType : int32 {
	AUDIOTYPE_PHYSICAL = 0,
	AUDIOTYPE_EXPLOSION = 1,
	AUDIOTYPE_FIRE = 2,
	AUDIOTYPE_WEATHER = 3,
	AUDIOTYPE_CRANE = 4,
	AUDIOTYPE_ONE_SHOT = 5,
	AUDIOTYPE_BRIDGE = 6,
	AUDIOTYPE_COLLISION = 7,
	AUDIOTYPE_FRONTEND = 8,
	AUDIOTYPE_PROJECTILE = 9,
	AUDIOTYPE_GARAGE = 10,
	AUDIOTYPE_HYDRANT = 11,
	AUDIOTYPE_WATER_CANNON = 12,
	AUDIOTYPE_D = 13,
	TOTAL_AUDIO_TYPES = 14,
};

class tAudioEntity
{
public:
	eAudioType m_nType;
	void *m_pEntity;
	char m_bIsUsed;
	char m_bStatus;
	int16 m_awAudioEvent[4];
	char gap_18[2];
	float m_afVolume[4];
	char field_24;
	char field_25[3];
};

static_assert(sizeof(tAudioEntity) == 0x28, "tAudioEntity: error");

class tPedComment
{
public:
	int m_nSampleIndex;
	int field_4;
	CVector m_vecPos;
	float m_fDistance;
	char m_bVolume;
	char field_25;
	char gap_26[2];
};

static_assert(sizeof(tPedComment) == 0x1c, "tPedComment: error");

class cPedComments
{
public:
	tPedComment m_asPedComments[40];
	char field_1120[40];
	char field_1160[2];
	char field_1162;
	char gap_1163[1];
};

static_assert(sizeof(cPedComments) == 0x48c, "cPedComments: error");

class CEntity;

class cAudioCollision
{
public:
	CEntity *m_pEntity1;
	CEntity *m_pEntity2;
	char m_bSurface1;
	char m_bSurface2;
	char field_10;
	char field_11;
	float m_fIntensity1;
	float m_fIntensity2;
	CVector m_vecPosition;
	float m_fDistance;
	int m_nBaseVolume;
};

static_assert(sizeof(cAudioCollision) == 0x28, "cAudioCollision: error");

class cAudioCollisionManager
{
public:
	cAudioCollision m_asCollisions1[10];
	cAudioCollision m_asCollisions2[10];
	char m_bIndicesTable[10];
	char m_bCollisionsInQueue;
	char gap_811;
	cAudioCollision m_sQueue;
};

static_assert(sizeof(cAudioCollisionManager) == 0x354,
              "cAudioCollisionManager: error");

class cMissionAudio
{
public:
	CVector m_vecPos;
	char field_12;
	char gap_13[3];
	int m_nSampleIndex;
	char m_bLoadingStatus;
	char m_bPlayStatus;
	char field_22;
	char field_23;
	int field_24;
	char m_bIsPlayed;
	char field_29;
	char field_30;
	char field_31;
};

static_assert(sizeof(cMissionAudio) == 0x20, "cMissionAudio: error");

class cAudioManager
{
public:
	bool m_bIsInitialised;
	char field_1;
	char field_2;
	char m_bActiveSamples;
	char field_4;
	bool m_bDynamicAcousticModelingStatus;
	char field_6;
	char field_7;
	float field_8;
	bool m_bTimerJustReset;
	char field_13;
	char field_14;
	char field_15;
	int m_nTimer;
	tActiveSample m_sQueueSample;
	char m_bActiveSampleQueue;
	char gap_109[3];
	tActiveSample m_asSamples[54];
	char m_abSampleQueueIndexTable[54];
	char m_bSampleRequestQueuesStatus[2];
	tActiveSample m_asActiveSamples[27];
	tAudioEntity m_asAudioEntities[200];
	int m_anAudioEntityIndices[200];
	int m_nAudioEntitiesTotal;
	CVector m_avecReflectionsPos[5];
	float m_afReflectionsDistances[5];
	int m_anScriptObjectEntityIndices[40];
	int m_nScriptObjectEntityTotal;
	cPedComments m_sPedComments;
	int m_nFireAudioEntity;
	int m_nWaterCannonEntity;
	int m_nPoliceChannelEntity;
	char gap45B8[444];
	int m_nFrontEndEntity;
	int m_nCollisionEntity;
	cAudioCollisionManager m_sCollisionManager;
	int m_nProjectileEntity;
	int m_nBridgeEntity;
	cMissionAudio m_sMissionAudio;
	int m_anRandomTable[5];
	char field_19192;
	char m_bUserPause;
	char m_bPreviousUserPause;
	char field_19195;
	int m_nTimeOfRecentCrime;

	bool IsAudioInitialised() const;
	void SetDynamicAcousticModelingStatus(bool status);
	void GenerateIntegerRandomNumberTable();

	void PlayerJustLeftCar(void);
	void Service();
	void GetPhrase(uint32 *phrase, uint32 *prevPhrase, uint32 sample,
	               uint32 maxOffset);

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
};

static_assert(sizeof(cAudioManager) == 0x4B14, "cAudioManager: error");

extern cAudioManager &AudioManager;
extern cAudioManager &Players;
