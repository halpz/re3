#pragma once
#include "AudioSamples.h"

#define MAX_VOLUME 127
#define MAX_FREQ DIGITALRATE

struct tSample {
	int32 nOffset;
	uint32 nSize;
	int32 nFrequency;
	int32 nLoopStart;
	int32 nLoopEnd;
};

#ifdef GTA_PS2
#define PS2BANK(e) e
#else
#define PS2BANK(e) e = SFX_BANK_0
#endif // GTA_PS2


enum
{
	SFX_BANK_0,
#ifdef GTA_PS2
	SFX_BANK_GENERIC_EXTRA,
	SFX_BANK_PED_COMMENTS,
	SFX_BANK_FRONT_END_MENU,
#else
	SFX_BANK_GENERIC_EXTRA = SFX_BANK_0,
	SFX_BANK_FRONT_END_MENU = SFX_BANK_0,

	SFX_BANK_PED_COMMENTS,
	MAX_SFX_BANKS,
	INVALID_SFX_BANK,
#endif

	CAR_SFX_BANKS_OFFSET,
	SFX_BANK_PONTIAC = CAR_SFX_BANKS_OFFSET,
	SFX_BANK_PORSCHE,
	SFX_BANK_SPIDER,
	SFX_BANK_MERC,
	SFX_BANK_TRUCK,
	SFX_BANK_HOTROD,
	SFX_BANK_COBRA,
	SFX_BANK_PONTIAC_SLOW,
	SFX_BANK_CADILLAC,
	SFX_BANK_PATHFINDER,
	SFX_BANK_PACARD,
	SFX_BANK_GOLF_CART,
	SFX_BANK_CAR_CHAINSAW,
	SFX_BANK_RC,
	SFX_BANK_RC_HELI,
	SFX_BANK_CAR_UNUSED_4,

	// bikes
	SFX_BANK_VTWIN,
	SFX_BANK_MOPED,
	SFX_BANK_HONDA250,
	SFX_BANK_SPORTS_BIKE,
	SFX_BANK_BIKE_UNUSED_1,
	SFX_BANK_BIKE_UNUSED_2,
	SFX_BANK_BIKE_UNUSED_3,
	SFX_BANK_BIKE_UNUSED_4,
	SFX_BANK_BIKE_UNUSED_5,
	SFX_BANK_BIKE_UNUSED_6,

	// heli
	SFX_BANK_HELI_APACHE,
	SFX_BANK_HELI_UNUSED_1,
	SFX_BANK_HELI_UNUSED_2,
	SFX_BANK_HELI_UNUSED_3,
	SFX_BANK_HELI_UNUSED_4,

	// plane
	SFX_BANK_PLANE_SEAPLANE,
	SFX_BANK_PLANE_UNUSED_1,
	SFX_BANK_PLANE_UNUSED_2,
	SFX_BANK_PLANE_UNUSED_3,
	SFX_BANK_PLANE_UNUSED_4,
	PS2BANK(SFX_BANK_BUILDING_BANK_ALARM),
	PS2BANK(SFX_BANK_BUILDING_SNORING),
	PS2BANK(SFX_BANK_BUILDING_BAR_1),
	PS2BANK(SFX_BANK_BUILDING_BAR_2),
	PS2BANK(SFX_BANK_BUILDING_BAR_3),
	PS2BANK(SFX_BANK_BUILDING_BAR_4),
	PS2BANK(SFX_BANK_BUILDING_MALIBU_1),
	PS2BANK(SFX_BANK_BUILDING_MALIBU_2),
	PS2BANK(SFX_BANK_BUILDING_MALIBU_3),
	PS2BANK(SFX_BANK_BUILDING_STRIP_1),
	PS2BANK(SFX_BANK_BUILDING_STRIP_2),
	PS2BANK(SFX_BANK_BUILDING_STRIP_3),
	PS2BANK(SFX_BANK_BUILDING_CHURCH),
	PS2BANK(SFX_BANK_BUILDING_FAN_1),
	PS2BANK(SFX_BANK_BUILDING_FAN_2),
	PS2BANK(SFX_BANK_BUILDING_INSECT_1),
	PS2BANK(SFX_BANK_BUILDING_INSECT_2),
	PS2BANK(SFX_BANK_BUILDING_18),
	PS2BANK(SFX_BANK_BUILDING_19),
	PS2BANK(SFX_BANK_BUILDING_20),
	PS2BANK(SFX_BANK_BUILDING_21),
	PS2BANK(SFX_BANK_FOOTSTEPS_GRASS),
	PS2BANK(SFX_BANK_FOOTSTEPS_GRAVEL),
	PS2BANK(SFX_BANK_FOOTSTEPS_WOOD),
	PS2BANK(SFX_BANK_FOOTSTEPS_METAL),
	PS2BANK(SFX_BANK_FOOTSTEPS_WATER),
	PS2BANK(SFX_BANK_FOOTSTEPS_SAND),
#ifdef GTA_PS2
	MAX_SFX_BANKS,
	INVALID_SFX_BANK
#endif
};
#define MAX_PEDSFX                 7
#define PED_BLOCKSIZE              79000

#define MAXPROVIDERS               64

#define MAXCHANNELS                28
#define MAXCHANNELS_SURROUND       24
#define MAX2DCHANNELS              1
#define CHANNEL2D                  MAXCHANNELS

#define MAX_STREAMS                3

#define DIGITALRATE                32000
#define DIGITALBITS                16
#define DIGITALCHANNELS            2

#define MAX_DIGITAL_MIXER_CHANNELS 32

class cSampleManager
{
	uint8   m_nEffectsVolume;
	uint8   m_nMusicVolume;
	uint8   m_nMP3BoostVolume;
	uint8   m_nEffectsFadeVolume;
	uint8   m_nMusicFadeVolume;
	uint8   m_nMonoMode;
	char    m_szCDRomRootPath[80];
	bool    m_bInitialised;
	uint8   m_nNumberOfProviders;
	char   *m_aAudioProviders[MAXPROVIDERS];
	tSample m_aSamples[TOTAL_AUDIO_SAMPLES];
	char    m_MiscomPath[260];
	char    m_WavFilesPath[260];
	char    m_MP3FilesPath[188];
	void   *m_aChannels[18];

public:
	
	

	cSampleManager(void);
	~cSampleManager(void);
	
	void SetSpeakerConfig(int32 nConfig);
	uint32 GetMaximumSupportedChannels(void);
	
	uint32 GetNum3DProvidersAvailable(void);
	void SetNum3DProvidersAvailable(uint32 num);
	
	char *Get3DProviderName(uint8 id);
	void Set3DProviderName(uint8 id, char *name);
	
	int8 GetCurrent3DProviderIndex(void);
	int8 SetCurrent3DProvider(uint8 which);

	int8 AutoDetect3DProviders();
	
	bool IsMP3RadioChannelAvailable(void);
	
	void ReleaseDigitalHandle  (void);
	void ReacquireDigitalHandle(void);
	
	bool Initialise(void);
	void Terminate (void);
		
	bool CheckForAnAudioFileOnCD(void);
	char GetCDAudioDriveLetter  (void);
	
	void UpdateEffectsVolume(void);

	void SetEffectsMasterVolume(uint8 nVolume);
	void SetMusicMasterVolume  (uint8 nVolume);
	void SetMP3BoostVolume     (uint8 nVolume);
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
	
	void  PreloadStreamedFile                                    (uint32 nFile, uint8 nStream);
	void  PauseStream                                        (uint8 nPauseFlag, uint8 nStream);
	void  StartPreloadedStreamedFile                                           (uint8 nStream);
	bool  StartStreamedFile                         (uint32 nFile, uint32 nPos, uint8 nStream);
	void  StopStreamedFile                                                     (uint8 nStream);
	int32 GetStreamedFilePosition                                              (uint8 nStream);
	void  SetStreamedVolumeAndPan(uint8 nVolume, uint8 nPan, uint8 nEffectFlag, uint8 nStream);
	int32 GetStreamedFileLength                                                (uint8 nStream);
	bool  IsStreamPlaying                                                      (uint8 nStream);
#ifdef AUDIO_OAL
	void  Service(void);
#endif
	bool  InitialiseSampleBanks(void);

	uint8 GetMusicVolume() const { return m_nMusicVolume;  }
	void SetStreamedFileLoopFlag(uint8 nLoopFlag, uint8 nStream);
};

extern cSampleManager SampleManager;
extern uint32 BankStartOffset[MAX_SFX_BANKS];

#if defined(OPUS_AUDIO_PATHS)
static char StreamedNameTable[][25] = {
    "AUDIO\\HEAD.OPUS",    "AUDIO\\CLASS.OPUS",   "AUDIO\\KJAH.OPUS",    "AUDIO\\RISE.OPUS",    "AUDIO\\LIPS.OPUS",    "AUDIO\\GAME.OPUS",
    "AUDIO\\MSX.OPUS",     "AUDIO\\FLASH.OPUS",   "AUDIO\\CHAT.OPUS",    "AUDIO\\HEAD.OPUS",    "AUDIO\\POLICE.OPUS",  "AUDIO\\CITY.OPUS",
    "AUDIO\\WATER.OPUS",   "AUDIO\\COMOPEN.OPUS", "AUDIO\\SUBOPEN.OPUS", "AUDIO\\JB.OPUS",      "AUDIO\\BET.OPUS",     "AUDIO\\L1_LG.OPUS",
    "AUDIO\\L2_DSB.OPUS",  "AUDIO\\L3_DM.OPUS",   "AUDIO\\L4_PAP.OPUS",  "AUDIO\\L5_TFB.OPUS",  "AUDIO\\J0_DM2.OPUS",  "AUDIO\\J1_LFL.OPUS",
    "AUDIO\\J2_KCL.OPUS",  "AUDIO\\J3_VH.OPUS",   "AUDIO\\J4_ETH.OPUS",  "AUDIO\\J5_DST.OPUS",  "AUDIO\\J6_TBJ.OPUS",  "AUDIO\\T1_TOL.OPUS",
    "AUDIO\\T2_TPU.OPUS",  "AUDIO\\T3_MAS.OPUS",  "AUDIO\\T4_TAT.OPUS",  "AUDIO\\T5_BF.OPUS",   "AUDIO\\S0_MAS.OPUS",  "AUDIO\\S1_PF.OPUS",
    "AUDIO\\S2_CTG.OPUS",  "AUDIO\\S3_RTC.OPUS",  "AUDIO\\S5_LRQ.OPUS",  "AUDIO\\S4_BDBA.OPUS", "AUDIO\\S4_BDBB.OPUS", "AUDIO\\S2_CTG2.OPUS",
    "AUDIO\\S4_BDBD.OPUS", "AUDIO\\S5_LRQB.OPUS", "AUDIO\\S5_LRQC.OPUS", "AUDIO\\A1_SSO.OPUS",  "AUDIO\\A2_PP.OPUS",   "AUDIO\\A3_SS.OPUS",
    "AUDIO\\A4_PDR.OPUS",  "AUDIO\\A5_K2FT.OPUS", "AUDIO\\K1_KBO.OPUS",  "AUDIO\\K2_GIS.OPUS",  "AUDIO\\K3_DS.OPUS",   "AUDIO\\K4_SHI.OPUS",
    "AUDIO\\K5_SD.OPUS",   "AUDIO\\R0_PDR2.OPUS", "AUDIO\\R1_SW.OPUS",   "AUDIO\\R2_AP.OPUS",   "AUDIO\\R3_ED.OPUS",   "AUDIO\\R4_GF.OPUS",
    "AUDIO\\R5_PB.OPUS",   "AUDIO\\R6_MM.OPUS",   "AUDIO\\D1_STOG.OPUS", "AUDIO\\D2_KK.OPUS",   "AUDIO\\D3_ADO.OPUS",  "AUDIO\\D5_ES.OPUS",
    "AUDIO\\D7_MLD.OPUS",  "AUDIO\\D4_GTA.OPUS",  "AUDIO\\D4_GTA2.OPUS", "AUDIO\\D6_STS.OPUS",  "AUDIO\\A6_BAIT.OPUS", "AUDIO\\A7_ETG.OPUS",
    "AUDIO\\A8_PS.OPUS",   "AUDIO\\A9_ASD.OPUS",  "AUDIO\\K4_SHI2.OPUS", "AUDIO\\C1_TEX.OPUS",  "AUDIO\\EL_PH1.OPUS",  "AUDIO\\EL_PH2.OPUS",
    "AUDIO\\EL_PH3.OPUS",  "AUDIO\\EL_PH4.OPUS",  "AUDIO\\YD_PH1.OPUS",  "AUDIO\\YD_PH2.OPUS",  "AUDIO\\YD_PH3.OPUS",  "AUDIO\\YD_PH4.OPUS",
    "AUDIO\\HD_PH1.OPUS",  "AUDIO\\HD_PH2.OPUS",  "AUDIO\\HD_PH3.OPUS",  "AUDIO\\HD_PH4.OPUS",  "AUDIO\\HD_PH5.OPUS",  "AUDIO\\MT_PH1.OPUS",
    "AUDIO\\MT_PH2.OPUS",  "AUDIO\\MT_PH3.OPUS",  "AUDIO\\MT_PH4.OPUS",  "AUDIO\\MISCOM.OPUS",  "AUDIO\\END.OPUS",     "AUDIO\\lib_a1.OPUS",
    "AUDIO\\lib_a2.OPUS",  "AUDIO\\lib_a.OPUS",   "AUDIO\\lib_b.OPUS",   "AUDIO\\lib_c.OPUS",   "AUDIO\\lib_d.OPUS",   "AUDIO\\l2_a.OPUS",
    "AUDIO\\j4t_1.OPUS",   "AUDIO\\j4t_2.OPUS",   "AUDIO\\j4t_3.OPUS",   "AUDIO\\j4t_4.OPUS",   "AUDIO\\j4_a.OPUS",    "AUDIO\\j4_b.OPUS",
    "AUDIO\\j4_c.OPUS",    "AUDIO\\j4_d.OPUS",    "AUDIO\\j4_e.OPUS",    "AUDIO\\j4_f.OPUS",    "AUDIO\\j6_1.OPUS",    "AUDIO\\j6_a.OPUS",
    "AUDIO\\j6_b.OPUS",    "AUDIO\\j6_c.OPUS",    "AUDIO\\j6_d.OPUS",    "AUDIO\\t4_a.OPUS",    "AUDIO\\s1_a.OPUS",    "AUDIO\\s1_a1.OPUS",
    "AUDIO\\s1_b.OPUS",    "AUDIO\\s1_c.OPUS",    "AUDIO\\s1_c1.OPUS",   "AUDIO\\s1_d.OPUS",    "AUDIO\\s1_e.OPUS",    "AUDIO\\s1_f.OPUS",
    "AUDIO\\s1_g.OPUS",    "AUDIO\\s1_h.OPUS",    "AUDIO\\s1_i.OPUS",    "AUDIO\\s1_j.OPUS",    "AUDIO\\s1_k.OPUS",    "AUDIO\\s1_l.OPUS",
    "AUDIO\\s3_a.OPUS",    "AUDIO\\s3_b.OPUS",    "AUDIO\\el3_a.OPUS",   "AUDIO\\mf1_a.OPUS",   "AUDIO\\mf2_a.OPUS",   "AUDIO\\mf3_a.OPUS",
    "AUDIO\\mf3_b.OPUS",   "AUDIO\\mf3_b1.OPUS",  "AUDIO\\mf3_c.OPUS",   "AUDIO\\mf4_a.OPUS",   "AUDIO\\mf4_b.OPUS",   "AUDIO\\mf4_c.OPUS",
    "AUDIO\\a1_a.OPUS",    "AUDIO\\a3_a.OPUS",    "AUDIO\\a5_a.OPUS",    "AUDIO\\a4_a.OPUS",    "AUDIO\\a4_b.OPUS",    "AUDIO\\a4_c.OPUS",
    "AUDIO\\a4_d.OPUS",    "AUDIO\\k1_a.OPUS",    "AUDIO\\k3_a.OPUS",    "AUDIO\\r1_a.OPUS",    "AUDIO\\r2_a.OPUS",    "AUDIO\\r2_b.OPUS",
    "AUDIO\\r2_c.OPUS",    "AUDIO\\r2_d.OPUS",    "AUDIO\\r2_e.OPUS",    "AUDIO\\r2_f.OPUS",    "AUDIO\\r2_g.OPUS",    "AUDIO\\r2_h.OPUS",
    "AUDIO\\r5_a.OPUS",    "AUDIO\\r6_a.OPUS",    "AUDIO\\r6_a1.OPUS",   "AUDIO\\r6_b.OPUS",    "AUDIO\\lo2_a.OPUS",   "AUDIO\\lo6_a.OPUS",
    "AUDIO\\yd2_a.OPUS",   "AUDIO\\yd2_b.OPUS",   "AUDIO\\yd2_c.OPUS",   "AUDIO\\yd2_c1.OPUS",  "AUDIO\\yd2_d.OPUS",   "AUDIO\\yd2_e.OPUS",
    "AUDIO\\yd2_f.OPUS",   "AUDIO\\yd2_g.OPUS",   "AUDIO\\yd2_h.OPUS",   "AUDIO\\yd2_ass.OPUS", "AUDIO\\yd2_ok.OPUS",  "AUDIO\\h5_a.OPUS",
    "AUDIO\\h5_b.OPUS",    "AUDIO\\h5_c.OPUS",    "AUDIO\\ammu_a.OPUS",  "AUDIO\\ammu_b.OPUS",  "AUDIO\\ammu_c.OPUS",  "AUDIO\\door_1.OPUS",
    "AUDIO\\door_2.OPUS",  "AUDIO\\door_3.OPUS",  "AUDIO\\door_4.OPUS",  "AUDIO\\door_5.OPUS",  "AUDIO\\door_6.OPUS",  "AUDIO\\t3_a.OPUS",
    "AUDIO\\t3_b.OPUS",    "AUDIO\\t3_c.OPUS",    "AUDIO\\k1_b.OPUS",    "AUDIO\\cat1.OPUS"};
#elif defined(PS2_AUDIO_PATHS)
static char StreamedNameTable[][40] =
{
	"AUDIO\\MUSIC\\HEAD.VB",
	"AUDIO\\MUSIC\\DOUBLE.VB",
	"AUDIO\\MUSIC\\KJAH.VB",
	"AUDIO\\MUSIC\\RISE.VB",
	"AUDIO\\MUSIC\\LIPS.VB",
	"AUDIO\\MUSIC\\MUNDO.VB",
	"AUDIO\\MUSIC\\MSX.VB",
	"AUDIO\\MUSIC\\FLASH.VB",
	"AUDIO\\MUSIC\\LCJ.VB",
	"AUDIO\\MUSIC\\LCFR.VB",
	"AUDIO\\MUSIC\\MISCOM2.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\WATER.VB",
	"AUDIO\\MUSIC\\SAWMILL.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\WATER.VB",
	"AUDIO\\MUSIC\\WATER.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\CITY.VB",
	"AUDIO\\MUSIC\\POLICE.VB",
	"AUDIO\\MUSIC\\TAXI.VB",
	"AUDIO\\NEWS\\NEWS_A.VB",
	"AUDIO\\NEWS\\NEWS_B.VB",
	"AUDIO\\NEWS\\NEWS_C.VB",
	"AUDIO\\NEWS\\NEWS_D.VB",
	"AUDIO\\NEWS\\NEWS_E.VB",
	"AUDIO\\NEWS\\NEWS_F.VB",
	"AUDIO\\NEWS\\NEWS_G.VB",
	"AUDIO\\NEWS\\NEWS_H.VB",
	"AUDIO\\NEWS\\NEWS_I.VB",
	"AUDIO\\NEWS\\NEWS_J.VB",
	"AUDIO\\NEWS\\NEWS_K.VB",
	"AUDIO\\NEWS\\NEWS_L.VB",
	"AUDIO\\NEWS\\NEWS_M.VB",
	"AUDIO\\NEWS\\NEWS_N.VB",
	"AUDIO\\CUTSCENE\\BIKER.VB",
	"AUDIO\\CUTSCENE\\BONEVOY.VB",
	"AUDIO\\CUTSCENE\\CAMPAIN.VB",
	"AUDIO\\CUTSCENE\\CASHCHP.VB",
	"AUDIO\\CUTSCENE\\CONTBAN.VB",
	"AUDIO\\CUTSCENE\\CRAZY69.VB",
	"AUDIO\\CUTSCENE\\CRAZY69.VB",
	"AUDIO\\CUTSCENE\\DEADLY.VB",
	"AUDIO\\CUTSCENE\\DONPROB.VB",
	"AUDIO\\CUTSCENE\\DRIVNMR.VB",
	"AUDIO\\CUTSCENE\\ELECTON.VB",
	"AUDIO\\CUTSCENE\\FINAL.VB",
	"AUDIO\\CUTSCENE\\FINAL_2.VB",
	"AUDIO\\CUTSCENE\\HOMSWET.VB",
	"AUDIO\\CUTSCENE\\HOTWHEL.VB",
	"AUDIO\\CUTSCENE\\KIDNAPP.VB",
	"AUDIO\\CUTSCENE\\LANDGRB.VB",
	"AUDIO\\CUTSCENE\\MORGUE.VB",
	"AUDIO\\CUTSCENE\\OVERDOS.VB",
	"AUDIO\\CUTSCENE\\RUFJUST.VB",
	"AUDIO\\CUTSCENE\\SAYONAR.VB",
	"AUDIO\\CUTSCENE\\SICILAN.VB",
	"AUDIO\\CUTSCENE\\THEOFER.VB",
	"AUDIO\\CUTSCENE\\INTRO.VB",
	"AUDIO\\MUSIC\\FINALE.VB",
	"AUDIO\\MUSIC\\MISCOM2.VB"
#else
static char StreamedNameTable[][25] =
{
	"AUDIO\\WILD.ADF",
	"AUDIO\\FLASH.ADF",
	"AUDIO\\KCHAT.ADF",
	"AUDIO\\FEVER.ADF",
	"AUDIO\\VROCK.ADF",
	"AUDIO\\VCPR.ADF",
	"AUDIO\\ESPANT.ADF",
	"AUDIO\\EMOTION.ADF",
	"AUDIO\\WAVE.ADF",
	"AUDIO\\MISCOM.MP3",
	"AUDIO\\CITY.MP3",
	"AUDIO\\WATER.MP3",
	"AUDIO\\BEACHAMB.MP3",
	"AUDIO\\HCITY.MP3",
	"AUDIO\\HWATER.MP3",
	"AUDIO\\HBEACH.MP3",
	"AUDIO\\MALLAMB.MP3",
	"AUDIO\\STRIP.MP3",
	"AUDIO\\MALIBU.MP3",
	"AUDIO\\HOTEL.MP3",
	"AUDIO\\DIRTRING.MP3",
	"AUDIO\\LAW4RIOT.MP3",
	"AUDIO\\AMBSIL.MP3",
	"AUDIO\\POLICE.MP3",
	"AUDIO\\TAXI.MP3",
	"AUDIO\\BCLOSED.MP3",
	"AUDIO\\BOPEN.MP3",
	"AUDIO\\ASS_1.MP3",
	"AUDIO\\ASS_2.MP3",
	"AUDIO\\BANK_1.MP3",
	"AUDIO\\BANK_2A.MP3",
	"AUDIO\\BANK_2B.MP3",
	"AUDIO\\BANK_3A.MP3",
	"AUDIO\\BANK_3B.MP3",
	"AUDIO\\BANK_4.MP3",
	"AUDIO\\BIKE_1.MP3",
	"AUDIO\\BIKE_2.MP3",
	"AUDIO\\BIKE_3.MP3",
	"AUDIO\\BUD_1.MP3",
	"AUDIO\\BUD_2.MP3",
	"AUDIO\\BUD_3.MP3",
	"AUDIO\\CAP_1.MP3",
	"AUDIO\\CAR_1.MP3",
	"AUDIO\\CNT_1A.MP3",
	"AUDIO\\CNT_1B.MP3",
	"AUDIO\\CNT_2.MP3",
	"AUDIO\\COK_1.MP3",
	"AUDIO\\COK_2A.MP3",
	"AUDIO\\COK_2B.MP3",
	"AUDIO\\COK_3.MP3",
	"AUDIO\\COK_4A.MP3",
	"AUDIO\\COK_4A2.MP3",
	"AUDIO\\COK_4B.MP3",
	"AUDIO\\COL_1.MP3",
	"AUDIO\\COL_2.MP3",
	"AUDIO\\COL_3A.MP3",
	"AUDIO\\COL_4A.MP3",
	"AUDIO\\COL_5A.MP3",
	"AUDIO\\COL_5B.MP3",
	"AUDIO\\CUB_1.MP3",
	"AUDIO\\CUB_2.MP3",
	"AUDIO\\CUB_3.MP3",
	"AUDIO\\CUB_4.MP3",
	"AUDIO\\DRUG_1.MP3",
	"AUDIO\\FIN.MP3",
	"AUDIO\\FIN2.MP3",
	"AUDIO\\FINALE.MP3",
	"AUDIO\\HAT_1.MP3",
	"AUDIO\\HAT_2.MP3",
	"AUDIO\\HAT_3.MP3",
	"AUDIO\\ICE_1.MP3",
	"AUDIO\\INT_A.MP3",
	"AUDIO\\INT_B.MP3",
	"AUDIO\\INT_D.MP3",
	"AUDIO\\INT_M.MP3",
	"AUDIO\\LAW_1A.MP3",
	"AUDIO\\LAW_1B.MP3",
	"AUDIO\\LAW_2A.MP3",
	"AUDIO\\LAW_2B.MP3",
	"AUDIO\\LAW_2C.MP3",
	"AUDIO\\LAW_3.MP3",
	"AUDIO\\LAW_4.MP3",
	"AUDIO\\PHIL_1.MP3",
	"AUDIO\\PHIL_2.MP3",
	"AUDIO\\PORN_1.MP3",
	"AUDIO\\PORN_2.MP3",
	"AUDIO\\PORN_3.MP3",
	"AUDIO\\PORN_4.MP3",
	"AUDIO\\RESC_1A.MP3",
	"AUDIO\\ROK_1.MP3",
	"AUDIO\\ROK_2.MP3",
	"AUDIO\\ROK_3A.MP3",
	"AUDIO\\STRIPA.MP3",
	"AUDIO\\TAX_1.MP3",
	"AUDIO\\TEX_1.MP3",
	"AUDIO\\TEX_2.MP3",
	"AUDIO\\TEX_3.MP3",
	"AUDIO\\GLIGHT.MP3",
	"AUDIO\\FIST.MP3",
	"AUDIO\\MISCOM.MP3",
	"AUDIO\\MISCOM.MP3",
	"AUDIO\\MISCOM.MP3",
	"AUDIO\\MISCOM.MP3",
#endif

};