#pragma once
#include "AudioSamples.h"
#include "audio_enums.h"

#define MAX_VOLUME 127
#define MAX_FREQ DIGITALRATE

struct tSample {
	uint32 nOffset;
	uint32 nSize;
	uint32 nFrequency;
	uint32 nLoopStart;
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
#define MISSION_AUDIO_BLOCKSIZE    160000

#define MAXPROVIDERS               64

#ifdef EXTERNAL_3D_SOUND
#define MAXCHANNELS                (NUM_CHANNELS_GENERIC+1)
#define MAXCHANNELS_SURROUND       (MAXCHANNELS-4)
#define MAX2DCHANNELS              3
#else
#define MAXCHANNELS                0
#define MAXCHANNELS_SURROUND       0
#define MAX2DCHANNELS              NUM_CHANNELS
#endif

#define MAX_STREAMS                1

#define DIGITALRATE                32000
#define DIGITALBITS                16
#define DIGITALCHANNELS            2

#ifdef FIX_BUGS
#define MAX_DIGITAL_MIXER_CHANNELS (MAXCHANNELS+MAX_STREAMS*2+MAX2DCHANNELS)
#else
#define MAX_DIGITAL_MIXER_CHANNELS (MAXCHANNELS+MAX_STREAMS*2)
#endif 

static_assert( NUM_CHANNELS == MAXCHANNELS + MAX2DCHANNELS, "The number of channels doesn't match with an enum" );

extern int gBankStartOffset[67];

class cSampleManager
{
	uint8   m_nEffectsVolume;
	uint8   m_nMusicVolume;
	uint8   m_nMP3BoostVolume;
	uint8   m_nEffectsFadeVolume;
	uint8   m_nMusicFadeVolume;
	bool8   m_nMonoMode;
	char    m_szCDRomRootPath[80];
	bool8   m_bInitialised;
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

#ifdef EXTERNAL_3D_SOUND
	void SetSpeakerConfig(int32 nConfig);
	uint32 GetMaximumSupportedChannels(void);
	
	uint32 GetNum3DProvidersAvailable(void);
	void SetNum3DProvidersAvailable(uint32 num);
	
	char *Get3DProviderName(uint8 id);
	void Set3DProviderName(uint8 id, char *name);
	
	int8 GetCurrent3DProviderIndex(void);
	int8 SetCurrent3DProvider(uint8 which);

	int8 AutoDetect3DProviders();
#endif

	bool8 IsMP3RadioChannelAvailable(void);
	
	void ReleaseDigitalHandle  (void);
	void ReacquireDigitalHandle(void);
	
	bool8 Initialise(void);
	void  Terminate (void);
		
	bool8 CheckForAnAudioFileOnCD(void);
	char  GetCDAudioDriveLetter  (void);
	
	void UpdateEffectsVolume(void);

	void SetEffectsMasterVolume(uint8 nVolume);
	void SetMusicMasterVolume  (uint8 nVolume);
	void SetMP3BoostVolume     (uint8 nVolume);
	void SetEffectsFadeVolume  (uint8 nVolume);
	void SetMusicFadeVolume    (uint8 nVolume);
	void SetMonoMode           (bool8 nMode);
	
	bool8 LoadSampleBank    (uint8 nBank);
	void  UnloadSampleBank  (uint8 nBank);
	int8  IsSampleBankLoaded(uint8 nBank);

	uint8 IsMissionAudioLoaded(uint8 nSlot, uint32 nSample);
	bool8 LoadMissionAudio    (uint8 nSlot, uint32 nSample);
	
	uint8 IsPedCommentLoaded(uint32 nComment);
	bool8 LoadPedComment    (uint32 nComment);
	int32 GetBankContainingSound(uint32 offset);

	int32 _GetPedCommentSlot(uint32 nComment);
	
	uint32 GetSampleBaseFrequency  (uint32 nSample);
	uint32 GetSampleLoopStartOffset(uint32 nSample);
	int32  GetSampleLoopEndOffset  (uint32 nSample);
	uint32 GetSampleLength         (uint32 nSample);
	
	bool8  UpdateReverb(void);
	
	void  SetChannelReverbFlag    (uint32 nChannel, bool8 nReverbFlag);
	bool8 InitialiseChannel       (uint32 nChannel, uint32 nSfx, uint8 nBank);
#ifdef EXTERNAL_3D_SOUND
	void  SetChannelEmittingVolume(uint32 nChannel, uint32 nVolume);
	void  SetChannel3DPosition    (uint32 nChannel, float fX, float fY, float fZ);
	void  SetChannel3DDistances   (uint32 nChannel, float fMax, float fMin);
#endif
	void  SetChannelVolume        (uint32 nChannel, uint32 nVolume);
	void  SetChannelPan           (uint32 nChannel, uint32 nPan);
	void  SetChannelFrequency     (uint32 nChannel, uint32 nFreq);
	void  SetChannelLoopPoints    (uint32 nChannel, uint32 nLoopStart, int32 nLoopEnd);
	void  SetChannelLoopCount     (uint32 nChannel, uint32 nLoopCount);
	bool8 GetChannelUsedFlag      (uint32 nChannel);
	void  StartChannel            (uint32 nChannel);
	void  StopChannel             (uint32 nChannel);
	
	void  PreloadStreamedFile                                    (uint32 nFile, uint8 nStream = 0);
	void  PauseStream                                        (bool8 nPauseFlag, uint8 nStream = 0);
	void  StartPreloadedStreamedFile                                           (uint8 nStream = 0);
	bool8 StartStreamedFile                         (uint32 nFile, uint32 nPos, uint8 nStream = 0);
	void  StopStreamedFile                                                     (uint8 nStream = 0);
	int32 GetStreamedFilePosition                                              (uint8 nStream = 0);
	void  SetStreamedVolumeAndPan(uint8 nVolume, uint8 nPan, bool8 nEffectFlag, uint8 nStream = 0);
	int32 GetStreamedFileLength                                                (uint8 nStream = 0);
	bool8 IsStreamPlaying                                                      (uint8 nStream = 0);
	void  SetStreamedFileLoopFlag                             (bool8 nLoopFlag, uint8 nStream = 0);
#ifdef AUDIO_OAL
	void  Service(void);
#endif
	bool8 InitialiseSampleBanks(void);

	uint8 GetMusicVolume() const { return m_nMusicVolume;  }
	uint8 GetMusicFadeVolume() const { return m_nMusicFadeVolume;  }
};

extern cSampleManager SampleManager;
extern uint32 BankStartOffset[MAX_SFX_BANKS];

static char StreamedNameTable[][40] = {
	"AUDIO\\MUSIC\\HEAD",
	"AUDIO\\MUSIC\\DOUBLE",
	"AUDIO\\MUSIC\\KJAH",
	"AUDIO\\MUSIC\\RISE",
	"AUDIO\\MUSIC\\LIPS",
	"AUDIO\\MUSIC\\MUNDO",
	"AUDIO\\MUSIC\\MSX",
	"AUDIO\\MUSIC\\FLASH",
	"AUDIO\\MUSIC\\LCJ",
	"AUDIO\\MUSIC\\LCFR",
	"AUDIO\\MUSIC\\MISCOM2",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\WATER",
	"AUDIO\\MUSIC\\SAWMILL",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\WATER",
	"AUDIO\\MUSIC\\WATER",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\CITY",
	"AUDIO\\MUSIC\\POLICE",
	"AUDIO\\MUSIC\\TAXI",
	"AUDIO\\NEWS\\NEWS_A",
	"AUDIO\\NEWS\\NEWS_B",
	"AUDIO\\NEWS\\NEWS_C",
	"AUDIO\\NEWS\\NEWS_D",
	"AUDIO\\NEWS\\NEWS_E",
	"AUDIO\\NEWS\\NEWS_F",
	"AUDIO\\NEWS\\NEWS_G",
	"AUDIO\\NEWS\\NEWS_H",
	"AUDIO\\NEWS\\NEWS_I",
	"AUDIO\\NEWS\\NEWS_J",
	"AUDIO\\NEWS\\NEWS_K",
	"AUDIO\\NEWS\\NEWS_L",
	"AUDIO\\NEWS\\NEWS_M",
	"AUDIO\\NEWS\\NEWS_N",
	"AUDIO\\CUTSCENE\\BIKER",
	"AUDIO\\CUTSCENE\\BONEVOY",
	"AUDIO\\CUTSCENE\\CAMPAIN",
	"AUDIO\\CUTSCENE\\CASHCHP",
	"AUDIO\\CUTSCENE\\CONTBAN",
	"AUDIO\\CUTSCENE\\CRAZY69",
	"AUDIO\\CUTSCENE\\CRAZY69",
	"AUDIO\\CUTSCENE\\DEADLY",
	"AUDIO\\CUTSCENE\\DONPROB",
	"AUDIO\\CUTSCENE\\DRIVNMR",
	"AUDIO\\CUTSCENE\\ELECTON",
	"AUDIO\\CUTSCENE\\FINAL",
	"AUDIO\\CUTSCENE\\FINAL_2",
	"AUDIO\\CUTSCENE\\HOMSWET",
	"AUDIO\\CUTSCENE\\HOTWHEL",
	"AUDIO\\CUTSCENE\\KIDNAPP",
	"AUDIO\\CUTSCENE\\LANDGRB",
	"AUDIO\\CUTSCENE\\MORGUE",
	"AUDIO\\CUTSCENE\\OVERDOS",
	"AUDIO\\CUTSCENE\\RUFJUST",
	"AUDIO\\CUTSCENE\\SAYONAR",
	"AUDIO\\CUTSCENE\\SICILAN",
	"AUDIO\\CUTSCENE\\THEOFER",
	"AUDIO\\CUTSCENE\\INTRO",
	"AUDIO\\MUSIC\\FINALE",
	"AUDIO\\MUSIC\\MISCOM2"
};