#pragma once
#include "common.h"
#include "AudioSamples.h"

#define MAX_VOLUME 127
//#define MAX_FREQ                22050
#define MAX_FREQ                32000

struct tSample {
	int32 nOffset;
	uint32 nSize;
	int32 nFrequency;
	int32 nLoopStart;
	int32 nLoopEnd;
};

enum
{
	SAMPLEBANK_MAIN,
	SAMPLEBANK_PED,
	MAX_SAMPLEBANKS,
	SAMPLEBANK_INVALID
};

#define MAX_PEDSFX                 7
#define PED_BLOCKSIZE              79000


//#define MAXCHANNELS                21 android
#define MAXCHANNELS                28
#define MAX2DCHANNELS              1
#define CHANNEL2D                  MAXCHANNELS

#define MAX_STREAMS             2

struct ALCdevice_struct;
struct ALCcontext_struct;
typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;

class cSampleManager
{
	int field_0;
	ALCdevice  *m_pDevice;
	ALCcontext *m_pContext;
  
	uint8   m_nEffectsVolume;
	uint8   m_nMusicVolume;
	uint8   m_nEffectsFadeVolume;
	uint8   m_nMusicFadeVolume;
	uint8   m_nMonoMode;
	char _pad0[3];
	tSample m_aSamples[TOTAL_AUDIO_SAMPLES];

public:
	
	

	cSampleManager(void);
	~cSampleManager(void);
	
	void SetSpeakerConfig(int32 nConfig);
	uint32 GetMaximumSupportedChannels(void);
	
	uint32 GetNum3DProvidersAvailable();
	void SetNum3DProvidersAvailable(uint32 num);
	
	char *Get3DProviderName(uint8 id);
	void Set3DProviderName(uint8 id, char *name);
	
	int8 GetCurrent3DProviderIndex(void);
	int8 SetCurrent3DProvider(uint8 which);
	
	bool IsMP3RadioChannelAvailable(void);
	
	void ReleaseDigitalHandle  (void);
	void ReacquireDigitalHandle(void);
	
	bool Initialise(void);
	void Terminate (void);
	
	void UpdateSoundBuffers(void);
	
	bool CheckForAnAudioFileOnCD(void);
	char GetCDAudioDriveLetter  (void);
	
	void UpdateEffectsVolume(void);

	void SetEffectsMasterVolume(uint8 nVolume);
	void SetMusicMasterVolume  (uint8 nVolume);
	void SetEffectsFadeVolume  (uint8 nVolume);
	void SetMusicFadeVolume    (uint8 nVolume);
	void SetMonoMode           (uint8 nMode);
	
	bool LoadSampleBank    (uint8 nBank);
	void UnloadSampleBank  (uint8 nBank);
	bool IsSampleBankLoaded(uint8 nBank);
	
	bool IsPedCommentLoaded(uint32 nComment);
	bool LoadPedComment    (uint32 nComment);
	int32 GetBankContainingSound(uint32 offset);

	int32 _GetPedCommentSlot(uint32 nComment);
	
	int32  GetSampleBaseFrequency  (uint32 nSample);
	int32  GetSampleLoopStartOffset(uint32 nSample);
	int32  GetSampleLoopEndOffset  (uint32 nSample);
	uint32 GetSampleLength         (uint32 nSample);
	
	bool  UpdateReverb(void);
	
	void  SetChannelReverbFlag    (uint32 nChannel, uint8 nReverbFlag);
	bool  InitialiseChannel       (uint32 nChannel, uint32 nSfx, uint8 nBank);
	void  SetChannelEmittingVolume(uint32 nChannel, uint32 nVolume);
	void  SetChannel3DPosition    (uint32 nChannel, float fX, float fY, float fZ);
	void  SetChannel3DDistances   (uint32 nChannel, float fMax, float fMin);
	void  SetChannelVolume        (uint32 nChannel, uint32 nVolume);
	void  SetChannelPan           (uint32 nChannel, uint32 nPan);
	void  SetChannelFrequency     (uint32 nChannel, uint32 nFreq);
	void  SetChannelLoopPoints    (uint32 nChannel, uint32 nLoopStart, int32 nLoopEnd);
	void  SetChannelLoopCount     (uint32 nChannel, uint32 nLoopCount);
	bool  GetChannelUsedFlag      (uint32 nChannel);
	void  StartChannel            (uint32 nChannel);
	void  StopChannel             (uint32 nChannel);
	
	void  PreloadStreamedFile                                     (uint8 nFile, uint8 nStream);
	void  PauseStream                                        (uint8 nPauseFlag, uint8 nStream);
	void  StartPreloadedStreamedFile                                           (uint8 nStream);
	bool  StartStreamedFile                          (uint8 nFile, uint32 nPos, uint8 nStream);
	void  StopStreamedFile                                                     (uint8 nStream);
	int32 GetStreamedFilePosition                                              (uint8 nStream);
	void  SetStreamedVolumeAndPan(uint8 nVolume, uint8 nPan, uint8 nEffectFlag, uint8 nStream);
	int32 GetStreamedFileLength                                                (uint8 nStream);
	bool  IsStreamPlaying                                                      (uint8 nStream);
	void  Service(void);
	bool  InitialiseSampleBanks(void);
};

extern cSampleManager SampleManager;
extern int32 BankStartOffset[MAX_SAMPLEBANKS];

static char StreamedNameTable[][25]=
{
	"AUDIO\\HEAD.MP3",
	"AUDIO\\CLASS.MP3",
	"AUDIO\\KJAH.MP3",
	"AUDIO\\RISE.MP3",
	"AUDIO\\LIPS.MP3",
	"AUDIO\\GAME.MP3",
	"AUDIO\\MSX.MP3",
	"AUDIO\\FLASH.MP3",
	"AUDIO\\CHAT.MP3",
	"AUDIO\\HEAD.MP3",
	"AUDIO\\POLICE.MP3",
	"AUDIO\\CITY.MP3",
	"AUDIO\\WATER.MP3",
	"AUDIO\\COMOPEN.MP3",
	"AUDIO\\SUBOPEN.MP3",
	"AUDIO\\JB.MP3",
	"AUDIO\\BET.MP3",
	"AUDIO\\L1_LG.MP3",
	"AUDIO\\L2_DSB.MP3",
	"AUDIO\\L3_DM.MP3",
	"AUDIO\\L4_PAP.MP3",
	"AUDIO\\L5_TFB.MP3",
	"AUDIO\\J0_DM2.MP3",
	"AUDIO\\J1_LFL.MP3",
	"AUDIO\\J2_KCL.MP3",
	"AUDIO\\J3_VH.MP3",
	"AUDIO\\J4_ETH.MP3",
	"AUDIO\\J5_DST.MP3",
	"AUDIO\\J6_TBJ.MP3",
	"AUDIO\\T1_TOL.MP3",
	"AUDIO\\T2_TPU.MP3",
	"AUDIO\\T3_MAS.MP3",
	"AUDIO\\T4_TAT.MP3",
	"AUDIO\\T5_BF.MP3",
	"AUDIO\\S0_MAS.MP3",
	"AUDIO\\S1_PF.MP3",
	"AUDIO\\S2_CTG.MP3",
	"AUDIO\\S3_RTC.MP3",
	"AUDIO\\S5_LRQ.MP3",
	"AUDIO\\S4_BDBA.MP3",
	"AUDIO\\S4_BDBB.MP3",
	"AUDIO\\S2_CTG2.MP3",
	"AUDIO\\S4_BDBD.MP3",
	"AUDIO\\S5_LRQB.MP3",
	"AUDIO\\S5_LRQC.MP3",
	"AUDIO\\A1_SSO.MP3",
	"AUDIO\\A2_PP.MP3",
	"AUDIO\\A3_SS.MP3",
	"AUDIO\\A4_PDR.MP3",
	"AUDIO\\A5_K2FT.MP3",
	"AUDIO\\K1_KBO.MP3",
	"AUDIO\\K2_GIS.MP3",
	"AUDIO\\K3_DS.MP3",
	"AUDIO\\K4_SHI.MP3",
	"AUDIO\\K5_SD.MP3",
	"AUDIO\\R0_PDR2.MP3",
	"AUDIO\\R1_SW.MP3",
	"AUDIO\\R2_AP.MP3",
	"AUDIO\\R3_ED.MP3",
	"AUDIO\\R4_GF.MP3",
	"AUDIO\\R5_PB.MP3",
	"AUDIO\\R6_MM.MP3",
	"AUDIO\\D1_STOG.MP3",
	"AUDIO\\D2_KK.MP3",
	"AUDIO\\D3_ADO.MP3",
	"AUDIO\\D5_ES.MP3",
	"AUDIO\\D7_MLD.MP3",
	"AUDIO\\D4_GTA.MP3",
	"AUDIO\\D4_GTA2.MP3",
	"AUDIO\\D6_STS.MP3",
	"AUDIO\\A6_BAIT.MP3",
	"AUDIO\\A7_ETG.MP3",
	"AUDIO\\A8_PS.MP3",
	"AUDIO\\A9_ASD.MP3",
	"AUDIO\\K4_SHI2.MP3",
	"AUDIO\\C1_TEX.MP3",
	"AUDIO\\EL_PH1.MP3",
	"AUDIO\\EL_PH2.MP3",
	"AUDIO\\EL_PH3.MP3",
	"AUDIO\\EL_PH4.MP3",
	"AUDIO\\YD_PH1.MP3",
	"AUDIO\\YD_PH2.MP3",
	"AUDIO\\YD_PH3.MP3",
	"AUDIO\\YD_PH4.MP3",
	"AUDIO\\HD_PH1.MP3",
	"AUDIO\\HD_PH2.MP3",
	"AUDIO\\HD_PH3.MP3",
	"AUDIO\\HD_PH4.MP3",
	"AUDIO\\HD_PH5.MP3",
	"AUDIO\\MT_PH1.MP3",
	"AUDIO\\MT_PH2.MP3",
	"AUDIO\\MT_PH3.MP3",
	"AUDIO\\MT_PH4.MP3",
	"AUDIO\\MISCOM.MP3",
	"AUDIO\\END.MP3",
	"AUDIO\\lib_a1.MP3",
	"AUDIO\\lib_a2.MP3",
	"AUDIO\\lib_a.MP3",
	"AUDIO\\lib_b.MP3",
	"AUDIO\\lib_c.MP3",
	"AUDIO\\lib_d.MP3",
	"AUDIO\\l2_a.MP3",
	"AUDIO\\j4t_1.MP3",
	"AUDIO\\j4t_2.MP3",
	"AUDIO\\j4t_3.MP3",
	"AUDIO\\j4t_4.MP3",
	"AUDIO\\j4_a.MP3",
	"AUDIO\\j4_b.MP3",
	"AUDIO\\j4_c.MP3",
	"AUDIO\\j4_d.MP3",
	"AUDIO\\j4_e.MP3",
	"AUDIO\\j4_f.MP3",
	"AUDIO\\j6_1.MP3",
	"AUDIO\\j6_a.MP3",
	"AUDIO\\j6_b.MP3",
	"AUDIO\\j6_c.MP3",
	"AUDIO\\j6_d.MP3",
	"AUDIO\\t4_a.MP3",
	"AUDIO\\s1_a.MP3",
	"AUDIO\\s1_a1.MP3",
	"AUDIO\\s1_b.MP3",
	"AUDIO\\s1_c.MP3",
	"AUDIO\\s1_c1.MP3",
	"AUDIO\\s1_d.MP3",
	"AUDIO\\s1_e.MP3",
	"AUDIO\\s1_f.MP3",
	"AUDIO\\s1_g.MP3",
	"AUDIO\\s1_h.MP3",
	"AUDIO\\s1_i.MP3",
	"AUDIO\\s1_j.MP3",
	"AUDIO\\s1_k.MP3",
	"AUDIO\\s1_l.MP3",
	"AUDIO\\s3_a.MP3",
	"AUDIO\\s3_b.MP3",
	"AUDIO\\el3_a.MP3",
	"AUDIO\\mf1_a.MP3",
	"AUDIO\\mf2_a.MP3",
	"AUDIO\\mf3_a.MP3",
	"AUDIO\\mf3_b.MP3",
	"AUDIO\\mf3_b1.MP3",
	"AUDIO\\mf3_c.MP3",
	"AUDIO\\mf4_a.MP3",
	"AUDIO\\mf4_b.MP3",
	"AUDIO\\mf4_c.MP3",
	"AUDIO\\a1_a.MP3",
	"AUDIO\\a3_a.MP3",
	"AUDIO\\a5_a.MP3",
	"AUDIO\\a4_a.MP3",
	"AUDIO\\a4_b.MP3",
	"AUDIO\\a4_c.MP3",
	"AUDIO\\a4_d.MP3",
	"AUDIO\\k1_a.MP3",
	"AUDIO\\k3_a.MP3",
	"AUDIO\\r1_a.MP3",
	"AUDIO\\r2_a.MP3",
	"AUDIO\\r2_b.MP3",
	"AUDIO\\r2_c.MP3",
	"AUDIO\\r2_d.MP3",
	"AUDIO\\r2_e.MP3",
	"AUDIO\\r2_f.MP3",
	"AUDIO\\r2_g.MP3",
	"AUDIO\\r2_h.MP3",
	"AUDIO\\r5_a.MP3",
	"AUDIO\\r6_a.MP3",
	"AUDIO\\r6_a1.MP3",
	"AUDIO\\r6_b.MP3",
	"AUDIO\\lo2_a.MP3",
	"AUDIO\\lo6_a.MP3",
	"AUDIO\\yd2_a.MP3",
	"AUDIO\\yd2_b.MP3",
	"AUDIO\\yd2_c.MP3",
	"AUDIO\\yd2_c1.MP3",
	"AUDIO\\yd2_d.MP3",
	"AUDIO\\yd2_e.MP3",
	"AUDIO\\yd2_f.MP3",
	"AUDIO\\yd2_g.MP3",
	"AUDIO\\yd2_h.MP3",
	"AUDIO\\yd2_ass.MP3",
	"AUDIO\\yd2_ok.MP3",
	"AUDIO\\h5_a.MP3",
	"AUDIO\\h5_b.MP3",
	"AUDIO\\h5_c.MP3",
	"AUDIO\\ammu_a.MP3",
	"AUDIO\\ammu_b.MP3",
	"AUDIO\\ammu_c.MP3",
	"AUDIO\\door_1.MP3",
	"AUDIO\\door_2.MP3",
	"AUDIO\\door_3.MP3",
	"AUDIO\\door_4.MP3",
	"AUDIO\\door_5.MP3",
	"AUDIO\\door_6.MP3",
	"AUDIO\\t3_a.MP3",
	"AUDIO\\t3_b.MP3",
	"AUDIO\\t3_c.MP3",
	"AUDIO\\k1_b.MP3",
	"AUDIO\\cat1.MP3"
};
