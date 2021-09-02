//#define JUICY_OAL

#ifdef AUDIO_OAL
#include <time.h>

#include "eax.h"
#include "eax-util.h"

#ifdef _WIN32
#include <io.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>
#include <AL/efx-presets.h>

// for user MP3s
#include <direct.h>
#include <shlobj.h>
#include <shlguid.h>
#else
#define _getcwd getcwd
#endif

#if defined _MSC_VER && !defined CMAKE_NO_AUTOLINK
#pragma comment( lib, "OpenAL32.lib" )
#endif

#include "common.h"
#include "crossplatform.h"

#include "sampman.h"

#include "oal/oal_utils.h"
#include "oal/aldlist.h"
#include "oal/channel.h"

#include <utility>
#ifdef MULTITHREADED_AUDIO
#include <mutex>
#include <queue>
#include <condition_variable>
#endif
#include "oal/stream.h"

#include "AudioManager.h"
#include "MusicManager.h"
#include "Frontend.h"
#include "Timer.h"
#ifdef AUDIO_OAL_USE_OPUS
#include <opusfile.h>
#endif

//TODO: fix eax3 reverb

cSampleManager SampleManager;
bool8 _bSampmanInitialised = FALSE;

uint32 BankStartOffset[MAX_SFX_BANKS];

int           prevprovider=-1;
int           curprovider=-1;
int           usingEAX=0;
int           usingEAX3=0;
//int         speaker_type=0;
ALCdevice    *ALDevice = NULL;
ALCcontext   *ALContext = NULL;
unsigned int _maxSamples;
float        _fPrevEaxRatioDestination; 
bool         _effectsSupported = false;
bool         _usingEFX;
float        _fEffectsLevel;
ALuint       ALEffect = AL_EFFECT_NULL;
ALuint       ALEffectSlot = AL_EFFECTSLOT_NULL;
struct
{ 
	const char *id;
	char name[256];
	int sources;
	bool bSupportsFx;
}providers[MAXPROVIDERS];

int defaultProvider;


char SampleBankDescFilename[] = "audio/sfx.SDT";
char SampleBankDataFilename[] = "audio/sfx.RAW";

FILE *fpSampleDescHandle;
#ifdef OPUS_SFX
OggOpusFile *fpSampleDataHandle;
#else
FILE *fpSampleDataHandle;
#endif
int8  gBankLoaded                  [MAX_SFX_BANKS];
int32 nSampleBankDiscStartOffset   [MAX_SFX_BANKS];
int32 nSampleBankSize              [MAX_SFX_BANKS];
uintptr nSampleBankMemoryStartAddress[MAX_SFX_BANKS];
int32 _nSampleDataEndOffset;

int32 nPedSlotSfx    [MAX_PEDSFX];
int32 nPedSlotSfxAddr[MAX_PEDSFX];
uint8 nCurrentPedSlot;

uint32 nMissionSlotSfx[MISSION_AUDIO_SLOTS] = { UINT32_MAX, UINT32_MAX };
uintptr nMissionSlotSfxStartAddress;

uint32 gPlayerTalkSfx = UINT32_MAX;
void *gPlayerTalkData = 0;

CChannel aChannel[NUM_CHANNELS];
uint8 nChannelVolume[NUM_CHANNELS];

uint32 nStreamLength[TOTAL_STREAMED_SOUNDS];
ALuint ALStreamSources[MAX_STREAMS][2];
ALuint ALStreamBuffers[MAX_STREAMS][NUM_STREAMBUFFERS];

struct tMP3Entry
{
	char aFilename[MAX_PATH];

	uint32 nTrackLength;
	uint32 nTrackStreamPos;

	tMP3Entry* pNext;
	char* pLinkPath;
};

uint32 nNumMP3s;
tMP3Entry* _pMP3List;
char _mp3DirectoryPath[MAX_PATH]; 
CStream    *aStream[MAX_STREAMS];
uint8      nStreamPan   [MAX_STREAMS];
uint8      nStreamVolume[MAX_STREAMS];
bool8      nStreamLoopedFlag[MAX_STREAMS];
uint32 _CurMP3Index;
int32 _CurMP3Pos;
bool8 _bIsMp3Active;
///////////////////////////////////////////////////////////////
//	Env		Size	Diffus	Room	RoomHF	RoomLF	DecTm	DcHF	DcLF	Refl	RefDel	Ref Pan				Revb	RevDel		Rev Pan				EchTm	EchDp	ModTm	ModDp	AirAbs	HFRef		LFRef	RRlOff	FLAGS
EAXLISTENERPROPERTIES StartEAX3 =
	{26,	1.7f,	0.8f,	-1000,	-1000,	-100,	4.42f,	0.14f,	1.00f,	429,	0.014f,	0.00f,0.00f,0.00f,	1023,	0.021f,		0.00f,0.00f,0.00f,	0.250f,	0.000f,	0.250f,	0.000f,	-5.0f,	2727.1f,	250.0f,	0.00f,	0x3f };

EAXLISTENERPROPERTIES FinishEAX3 =
	{26,	100.0f,	1.0f,	0,		-1000,	-2200,	20.0f,	1.39f,	1.00f,	1000,	0.069f,	0.00f,0.00f,0.00f,	400,	0.100f,		0.00f,0.00f,0.00f,	0.250f,	1.000f,	3.982f,	0.000f,	-18.0f,	3530.8f,	417.9f,	6.70f,	0x3f };

EAXLISTENERPROPERTIES EAX3Params;


bool IsFXSupported()
{
	return _effectsSupported; // usingEAX || usingEAX3 || _usingEFX;
}

void EAX_SetAll(const EAXLISTENERPROPERTIES *allparameters)
{
	if ( usingEAX || usingEAX3 )
		EAX3_Set(ALEffect, allparameters);
	else
		EFX_Set(ALEffect, allparameters);
}

static void
add_providers()
{
	SampleManager.SetNum3DProvidersAvailable(0);

	static ALDeviceList DeviceList;
	ALDeviceList *pDeviceList = &DeviceList;

	if ((pDeviceList) && (pDeviceList->GetNumDevices()))
	{
		const int devNumber = Min(pDeviceList->GetNumDevices(), MAXPROVIDERS);
		int n = 0;
		
		//for (int i = 0; i < devNumber; i++) 
		int i = pDeviceList->GetDefaultDevice();
		{
			if ( n < MAXPROVIDERS )
			{ 
				providers[n].id = pDeviceList->GetDeviceName(i);
				strcpy(providers[n].name, "OPENAL SOFT");
				providers[n].sources = pDeviceList->GetMaxNumSources(i);
				SampleManager.Set3DProviderName(n, providers[n].name);
				n++;
			}

			if ( alGetEnumValue("AL_EFFECT_EAXREVERB") != 0
				|| pDeviceList->IsExtensionSupported(i, ADEXT_EAX2)
				|| pDeviceList->IsExtensionSupported(i, ADEXT_EAX3) 
				|| pDeviceList->IsExtensionSupported(i, ADEXT_EAX4)
				|| pDeviceList->IsExtensionSupported(i, ADEXT_EAX5) )
			{ 
				providers[n - 1].bSupportsFx = true;
				if ( n < MAXPROVIDERS )
				{ 
					providers[n].id = pDeviceList->GetDeviceName(i);
					strcpy(providers[n].name, "OPENAL SOFT EAX");
					providers[n].sources = pDeviceList->GetMaxNumSources(i);
					providers[n].bSupportsFx = true;
					SampleManager.Set3DProviderName(n, providers[n].name);
					n++;
				}
				
				if ( n < MAXPROVIDERS )
				{ 
					providers[n].id = pDeviceList->GetDeviceName(i);
					strcpy(providers[n].name, "OPENAL SOFT EAX3");
					providers[n].sources = pDeviceList->GetMaxNumSources(i);
					providers[n].bSupportsFx = true;
					SampleManager.Set3DProviderName(n, providers[n].name);
					n++;
				}
			}
		}
		SampleManager.SetNum3DProvidersAvailable(n);
	
		for(int j=n;j<MAXPROVIDERS;j++)
			SampleManager.Set3DProviderName(j, NULL);

		// devices are gone now
		//defaultProvider = pDeviceList->GetDefaultDevice();
		//if ( defaultProvider > MAXPROVIDERS )
		defaultProvider = 0;
	}
}

static void
release_existing()
{
	if ( IsFXSupported() )
	{
		if ( alIsEffect(ALEffect) )
		{
			alEffecti(ALEffect, AL_EFFECT_TYPE, AL_EFFECT_NULL);
		}
		
		if (alIsAuxiliaryEffectSlot(ALEffectSlot))
		{
			alAuxiliaryEffectSloti(ALEffectSlot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
		}
	}

	DEV("release_existing()\n");
}

static bool8
set_new_provider(int index)
{
	if ( curprovider == index )
		return TRUE;
	
	curprovider = index;
	
	release_existing();
	
	if ( curprovider != -1 )
	{
		DEV("set_new_provider()\n");
		
		usingEAX = 0;
		usingEAX3 = 0;
		_usingEFX = false;
		
		if ( !strcmp(&providers[index].name[strlen(providers[index].name) - strlen(" EAX3")], " EAX3") 
				&& alcIsExtensionPresent(ALDevice, (ALCchar*)ALC_EXT_EFX_NAME) )
		{
			
			usingEAX = 1;
			usingEAX3 = 1;
			alAuxiliaryEffectSloti(ALEffectSlot, AL_EFFECTSLOT_EFFECT, ALEffect);
			EAX_SetAll(&FinishEAX3);

			DEV("EAX3\n");
		}
		else if ( alcIsExtensionPresent(ALDevice, (ALCchar*)ALC_EXT_EFX_NAME) )
		{
			
			if ( !strcmp(&providers[index].name[strlen(providers[index].name) - strlen(" EAX")], " EAX"))
			{
				usingEAX = 1;
				DEV("EAX1\n");
			}
			else
			{
				_usingEFX = true;
				DEV("EFX\n");
			}
			alAuxiliaryEffectSloti(ALEffectSlot, AL_EFFECTSLOT_EFFECT, ALEffect);
			EAX_SetAll(&EAX30_ORIGINAL_PRESETS[EAX_ENVIRONMENT_CAVE]);
		}
		
		//SampleManager.SetSpeakerConfig(speaker_type);
		
		if ( IsFXSupported() )
		{
			for ( int32 i = 0; i < MAXCHANNELS; i++ )
				aChannel[i].SetReverbMix(ALEffectSlot, 0.0f);
		}
		
		return TRUE;
	}
	
	return FALSE;
}

static bool8
IsThisTrackAt16KHz(uint32 track)
{
	return false;// track == STREAMED_SOUND_RADIO_KCHAT || track == STREAMED_SOUND_RADIO_VCPR || track == STREAMED_SOUND_RADIO_POLICE;
}

cSampleManager::cSampleManager(void)
{
	;
}

cSampleManager::~cSampleManager(void)
{
	
}

int gBankStartOffset[67];

void
SetUpDebugBanksInfo()
{
	gBankStartOffset[3] = SFX_FE_BACK;
	gBankStartOffset[4] = SFX_CAR_ACCEL_1;
	gBankStartOffset[5] = SFX_CAR_ACCEL_2;
	gBankStartOffset[9] = SFX_CAR_ACCEL_6;
	gBankStartOffset[10] = SFX_CAR_ACCEL_7;
	gBankStartOffset[1] = SFX_EMPTY;
	gBankStartOffset[11] = SFX_CAR_ACCEL_8;
	gBankStartOffset[7] = SFX_CAR_ACCEL_4;
	gBankStartOffset[15] = SFX_CAR_ACCEL_12;
	gBankStartOffset[13] = SFX_CAR_ACCEL_10;
	gBankStartOffset[16] = SFX_CAR_CHAINSAW_IDLE;
	gBankStartOffset[0] = SFX_AIR_BRAKES;
	gBankStartOffset[17] = SFX_RC_IDLE;
	gBankStartOffset[6] = SFX_CAR_ACCEL_3;
	gBankStartOffset[19] = SFX_CAR_ACCEL_16;
	gBankStartOffset[12] = SFX_CAR_ACCEL_9;
	gBankStartOffset[2] = SFX_AMBULAN_VOICE_1_VAN_1;
	gBankStartOffset[21] = SFX_CAR_ACCEL_18;
	gBankStartOffset[22] = SFX_CAR_ACCEL_19;
	gBankStartOffset[8] = SFX_CAR_ACCEL_5;
	gBankStartOffset[23] = SFX_CAR_ACCEL_20;
	gBankStartOffset[14] = SFX_CAR_ACCEL_11;
	gBankStartOffset[20] = SFX_CAR_ACCEL_17;
	gBankStartOffset[18] = SFX_CAR_RC_HELI;
	gBankStartOffset[25] = SFX_CAR_AFTER_ACCEL_21;
	gBankStartOffset[26] = SFX_CAR_FINGER_OFF_ACCEL_21;
	gBankStartOffset[27] = SFX_CAR_ACCEL_22;
	gBankStartOffset[28] = SFX_CAR_AFTER_ACCEL_22;
	gBankStartOffset[29] = SFX_CAR_FINGER_OFF_ACCEL_22;
	gBankStartOffset[24] = SFX_CAR_ACCEL_21;
	gBankStartOffset[30] = SFX_HELI_APACHE_1;
	gBankStartOffset[31] = SFX_HELI_UNUSED_1;
	gBankStartOffset[32] = SFX_HELI_UNUSED_2;
	gBankStartOffset[33] = SFX_HELI_UNUSED_3;
	gBankStartOffset[34] = SFX_HELI_UNUSED_4;
	gBankStartOffset[35] = SFX_SEAPLANE_LOW;
	gBankStartOffset[37] = SFX_PLANE_UNUSED_2;
	gBankStartOffset[38] = SFX_PLANE_UNUSED_3;
	gBankStartOffset[39] = SFX_PLANE_UNUSED_4;
	gBankStartOffset[40] = SFX_BUILDINGS_BANK_ALARM;
	gBankStartOffset[41] = SFX_BUILDING_SNORE;
	gBankStartOffset[36] = SFX_PLANE_UNUSED_1;
	gBankStartOffset[43] = SFX_BUILDING_BAR_2;
	gBankStartOffset[44] = SFX_BUILDING_BAR_3;
	gBankStartOffset[45] = SFX_BUILDING_BAR_4;
	gBankStartOffset[46] = SFX_BUILDING_MALIBU_1;
	gBankStartOffset[47] = SFX_BUILDING_MALIBU_2;
	gBankStartOffset[42] = SFX_BUILDING_BAR_1;
	gBankStartOffset[49] = SFX_BUILDING_STRIP_1;
	gBankStartOffset[50] = SFX_BUILDING_STRIP_2;
	gBankStartOffset[51] = SFX_BUILDING_STRIP_3;
	gBankStartOffset[52] = SFX_BUILDING_CHURCH;
	gBankStartOffset[53] = SFX_BUILDING_FAN_1;
	gBankStartOffset[48] = SFX_BUILDING_MALIBU_3;
	gBankStartOffset[55] = SFX_BUILDING_INSECTS_1;
	gBankStartOffset[56] = SFX_BUILDING_INSECTS_2;
	gBankStartOffset[54] = SFX_BUILDING_FAN_2;
	gBankStartOffset[57] = SFX_CLUB_1;
	gBankStartOffset[58] = SFX_CLUB_2;
	gBankStartOffset[59] = SFX_CLUB_3;
	gBankStartOffset[60] = SFX_CLUB_4;
	gBankStartOffset[61] = SFX_FOOTSTEP_GRASS_1;
	gBankStartOffset[62] = SFX_FOOTSTEP_GRAVEL_1;
	gBankStartOffset[63] = SFX_FOOTSTEP_WOOD_1;
	gBankStartOffset[64] = SFX_FOOTSTEP_METAL_1;
	gBankStartOffset[65] = SFX_FOOTSTEP_WATER_1;
	gBankStartOffset[66] = SFX_FOOTSTEP_SAND_1;
}

void cSampleManager::SetSpeakerConfig(int32 nConfig)
{

}

uint32 cSampleManager::GetMaximumSupportedChannels(void)
{
	if ( _maxSamples > MAXCHANNELS )
		return MAXCHANNELS;
	
	return _maxSamples;
}

uint32 cSampleManager::GetNum3DProvidersAvailable()
{
	return m_nNumberOfProviders;
}

void cSampleManager::SetNum3DProvidersAvailable(uint32 num)
{
	m_nNumberOfProviders = num;
}

char *cSampleManager::Get3DProviderName(uint8 id)
{
	return m_aAudioProviders[id];
}

void cSampleManager::Set3DProviderName(uint8 id, char *name)
{
	m_aAudioProviders[id] = name;
}

int8 cSampleManager::GetCurrent3DProviderIndex(void)
{
	return curprovider;
}

int8 cSampleManager::SetCurrent3DProvider(uint8 nProvider)
{
	int savedprovider = curprovider;

	nProvider = Clamp(nProvider, 0, m_nNumberOfProviders - 1);

	if ( set_new_provider(nProvider) )
		return curprovider;
	else if ( savedprovider != -1 && savedprovider < m_nNumberOfProviders && set_new_provider(savedprovider) )
		return curprovider;
	else
		return curprovider;
}

int8
cSampleManager::AutoDetect3DProviders()
{
	if (!AudioManager.IsAudioInitialised())
		return -1;

	if (defaultProvider >= 0 && defaultProvider < m_nNumberOfProviders) {
		if (set_new_provider(defaultProvider))
			return defaultProvider;
	}

	for (uint32 i = 0; i < GetNum3DProvidersAvailable(); i++)
	{
		char* providername = Get3DProviderName(i);

		if (!strcasecmp(providername, "OPENAL SOFT")) {
			SetCurrent3DProvider(i);
			if (GetCurrent3DProviderIndex() == i)
				return i;
		}
	}

	return -1;
}

static bool8
_ResolveLink(char const *path, char *out)
{
#ifdef _WIN32
	size_t len = strlen(path);
	if (len < 4 || strcmp(&path[len - 4], ".lnk") != 0)
		return FALSE;
		
	IShellLink* psl;
	WIN32_FIND_DATA fd;
	char filepath[MAX_PATH];
	
	CoInitialize(NULL);
									   
	if (SUCCEEDED( CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl ) ))
	{
		IPersistFile *ppf;

		if (SUCCEEDED(psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf)))
		{
			WCHAR wpath[MAX_PATH];
			
			MultiByteToWideChar(CP_ACP, 0, path, -1, wpath, MAX_PATH);
			
			if (SUCCEEDED(ppf->Load(wpath, STGM_READ)))
			{
				/* Resolve the link */
				if (SUCCEEDED(psl->Resolve(NULL, SLR_ANY_MATCH|SLR_NO_UI|SLR_NOSEARCH)))
				{
					strcpy(filepath, path);
					
					if (SUCCEEDED(psl->GetPath(filepath, MAX_PATH, &fd, SLGP_UNCPRIORITY)))
					{
						OutputDebugString(fd.cFileName);
						
						strcpy(out, filepath);
						// FIX: Release the objects. Taken from SA.
#ifdef FIX_BUGS
						ppf->Release();
						psl->Release();
#endif
						return TRUE;
					}
				}
			}
			
			ppf->Release();
		}
		psl->Release();
	}
	
	return FALSE;
#else
	struct stat sb;

	if (lstat(path, &sb) == -1) {
		perror("lstat: ");
		return FALSE;
	}

	if (S_ISLNK(sb.st_mode)) {
		char* linkname = (char*)alloca(sb.st_size + 1);
		if (linkname == NULL) {
			fprintf(stderr, "insufficient memory\n");
			return FALSE;
		}

		if (readlink(path, linkname, sb.st_size + 1) < 0) {
			perror("readlink: ");
			return FALSE;
		}
		linkname[sb.st_size] = '\0';
		strcpy(out, linkname);
		return TRUE;
	} else {
		return FALSE;
	}
#endif
}

static void
_FindMP3s(void)
{
	tMP3Entry *pList;
	bool8 bShortcut;	
	bool8 bInitFirstEntry;	
	HANDLE hFind;
	char path[MAX_PATH];
	int total_ms;
	WIN32_FIND_DATA fd;
	char filepath[MAX_PATH + sizeof(fd.cFileName)];
	
	if (getcwd(_mp3DirectoryPath, MAX_PATH) == NULL) {
		perror("getcwd: ");
		return;
	}

	if (strlen(_mp3DirectoryPath) + 1 > MAX_PATH - 10) {
		// This is not gonna end well
		printf("MP3 folder path is too long, no place left for file names. MP3 finding aborted.\n");
		return;
	}
	
	OutputDebugString("Finding MP3s...");
	strcpy(path, _mp3DirectoryPath);
	strcat(path, "\\MP3\\");

#if !defined(_WIN32)
	char *actualPath = casepath(path);
	if (actualPath) {
		strcpy(path, actualPath);
		free(actualPath);
	}
#endif
	
	strcpy(_mp3DirectoryPath, path);
	OutputDebugString(_mp3DirectoryPath);
	
	strcat(path, "*");
	
	hFind = FindFirstFile(path, &fd);
	
	if ( hFind == INVALID_HANDLE_VALUE ) 
	{
		return;
	}

	bShortcut = FALSE;
	bInitFirstEntry = TRUE;

	do
	{	
		strcpy(filepath, _mp3DirectoryPath);
		strcat(filepath, fd.cFileName);
			
		if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
			continue;

		size_t filepathlen = strlen(filepath);

		if ( bInitFirstEntry )
		{
			if (filepathlen > 0)
			{
				if (_ResolveLink(filepath, filepath))
				{
					OutputDebugString("Resolving Link");
					OutputDebugString(filepath);
					bShortcut = TRUE;
				}
				else
				{
					bShortcut = FALSE;
					if (filepathlen > MAX_PATH) {
						continue;
					}
				}
				if (aStream[0] && aStream[0]->Open(filepath))
				{
					total_ms = aStream[0]->GetLengthMS();
					aStream[0]->Close();
					
					OutputDebugString(fd.cFileName);

					_pMP3List = new tMP3Entry;

					if (_pMP3List == NULL)
						break;

					nNumMP3s = 1;

					strcpy(_pMP3List->aFilename, fd.cFileName);

					_pMP3List->nTrackLength = total_ms;
					_pMP3List->pNext = NULL;

					if (bShortcut)
					{
						_pMP3List->pLinkPath = new char[MAX_PATH + sizeof(fd.cFileName)];
						strcpy(_pMP3List->pLinkPath, filepath);
					}
					else
					{
						_pMP3List->pLinkPath = NULL;
					}

					pList = _pMP3List;

					bInitFirstEntry = FALSE;
				}
				else
				{
					strcat(filepath, " - NOT A VALID MP3");
					OutputDebugString(filepath);
				}
			}
			else
				break;
		}
		else
		{
			if ( filepathlen > 0 )
			{
				if ( _ResolveLink(filepath, filepath) )
				{
					OutputDebugString("Resolving Link");
					OutputDebugString(filepath);
					bShortcut = TRUE;
				}
				else
					bShortcut = FALSE;
				
				if (aStream[0] && aStream[0]->Open(filepath))
				{
					total_ms = aStream[0]->GetLengthMS();
					aStream[0]->Close();

					OutputDebugString(fd.cFileName);
					
					pList->pNext = new tMP3Entry;
					
					tMP3Entry *e = pList->pNext;
					
					if ( e == NULL )
						break;
					
					pList = pList->pNext;
					
					strcpy(e->aFilename, fd.cFileName);
					e->nTrackLength = total_ms;
					e->pNext = NULL;
					
					if ( bShortcut )
					{
						e->pLinkPath = new char [MAX_PATH + sizeof(fd.cFileName)];
						strcpy(e->pLinkPath, filepath);
					}
					else
					{
						e->pLinkPath = NULL;
					}
					
					nNumMP3s++;
					
					OutputDebugString(fd.cFileName);
				}
				else
				{
					strcat(filepath, " - NOT A VALID MP3");
					OutputDebugString(filepath);
				}
			}
		}
	} while (FindNextFile(hFind, &fd));

	FindClose(hFind);
}

static void
_DeleteMP3Entries(void)
{
	tMP3Entry *e = _pMP3List;

	while ( e != NULL )
	{
		tMP3Entry *next = e->pNext;
		
		if ( next == NULL )
			next = NULL;
		
		if ( e->pLinkPath != NULL )
		{
#ifndef FIX_BUGS
			delete   e->pLinkPath; // BUG: should be delete []
#else
			delete[] e->pLinkPath;
#endif
			e->pLinkPath = NULL;
		}
		
		delete e;
		
		if ( next )
			e = next;
		else
			e = NULL;
		
		nNumMP3s--;
	}
	
	
	if ( nNumMP3s != 0 )
	{
		OutputDebugString("Not all MP3 entries were deleted");
		nNumMP3s = 0;
	}
	
	_pMP3List = NULL;
}

static tMP3Entry *
_GetMP3EntryByIndex(uint32 idx)
{
	uint32 n = ( idx < nNumMP3s ) ? idx : 0;
	
	if ( _pMP3List != NULL )
	{
		tMP3Entry *e = _pMP3List;
		
		for ( uint32 i = 0; i < n; i++ )
			e = e->pNext;
		
		return e;
			
	}
	
	return NULL;
}

static inline bool8
_GetMP3PosFromStreamPos(uint32 *pPosition, tMP3Entry **pEntry)
{
	_CurMP3Index = 0;
	
	for ( *pEntry = _pMP3List; *pEntry != NULL; *pEntry = (*pEntry)->pNext )
	{
		if (   *pPosition >= (*pEntry)->nTrackStreamPos
			&& *pPosition <  (*pEntry)->nTrackLength + (*pEntry)->nTrackStreamPos )
		{
			*pPosition -= (*pEntry)->nTrackStreamPos;
			_CurMP3Pos = *pPosition;
			
			return TRUE;
		}
		
		_CurMP3Index++;
	}
				
	*pPosition = 0;
	*pEntry = _pMP3List;
	_CurMP3Pos = 0;
	_CurMP3Index = 0;
	
	return FALSE;
}

bool8
cSampleManager::IsMP3RadioChannelAvailable(void)
{
	return nNumMP3s != 0;
}


void cSampleManager::ReleaseDigitalHandle(void)
{
	// TODO? alcSuspendContext
}

void cSampleManager::ReacquireDigitalHandle(void)
{
	// TODO? alcProcessContext
}

bool8
cSampleManager::Initialise(void)
{
	if ( _bSampmanInitialised )
		return TRUE;
	SetUpDebugBanksInfo();
	EFXInit();

	for(int i = 0; i < MAX_STREAMS; i++)
		aStream[i] = new CStream(ALStreamSources[i], ALStreamBuffers[i]);

	CStream::Initialise();

	{
		for ( int32 i = 0; i < TOTAL_AUDIO_SAMPLES; i++ )
		{
			m_aSamples[i].nOffset    = 0;
			m_aSamples[i].nSize      = 0;
			m_aSamples[i].nFrequency = 22050;
			m_aSamples[i].nLoopStart = 0;
			m_aSamples[i].nLoopEnd   = -1;
		}
		
		m_nEffectsVolume     = MAX_VOLUME;
		m_nMusicVolume       = MAX_VOLUME;
		m_nEffectsFadeVolume = MAX_VOLUME;
		m_nMusicFadeVolume   = MAX_VOLUME;
	
		m_nMonoMode = 0;
	}
	
	{
		curprovider = -1;
		prevprovider = -1;
			
		_usingEFX = false;
		usingEAX =0;
		usingEAX3=0;
			
		_fEffectsLevel = 0.0f;
			
		_maxSamples = 0;
		
		ALDevice = NULL;
		ALContext = NULL;
	}
	
	{
		fpSampleDescHandle = NULL;
		fpSampleDataHandle = NULL;
		
		for ( int32 i = 0; i < MAX_SFX_BANKS; i++ )
		{
			gBankLoaded[i]                   = LOADING_STATUS_NOT_LOADED;
			nSampleBankDiscStartOffset[i]    = 0;
			nSampleBankSize[i]               = 0;
			nSampleBankMemoryStartAddress[i] = 0;
		}
	}
	
	{
		for ( int32 i = 0; i < MAX_PEDSFX; i++ )
		{
			nPedSlotSfx[i]     = NO_SAMPLE;
			nPedSlotSfxAddr[i] = 0;
		}
		
		nCurrentPedSlot = 0;
	}
	
	{
		for ( int32 i = 0; i < NUM_CHANNELS; i++ )
			nChannelVolume[i] = 0;
	}

	add_providers();

	{
		int index = 0;
		_maxSamples = Min(MAXCHANNELS, providers[index].sources);
		
		ALCint attr[] = {ALC_FREQUENCY,MAX_FREQ,
						ALC_MONO_SOURCES, MAX_DIGITAL_MIXER_CHANNELS - MAX2DCHANNELS,
						ALC_STEREO_SOURCES, MAX2DCHANNELS,
						0,
						};
		
		ALDevice  = alcOpenDevice(providers[index].id);
		ASSERT(ALDevice != NULL);
		
		ALContext = alcCreateContext(ALDevice, attr);
		ASSERT(ALContext != NULL);
		
		alcMakeContextCurrent(ALContext);
	
		const char* ext=(const char*)alGetString(AL_EXTENSIONS);
		ASSERT(strstr(ext,"AL_SOFT_loop_points")!=NULL);
		if ( strstr(ext,"AL_SOFT_loop_points")==NULL )
		{
			Terminate();
			return FALSE;
		}
		
		alListenerf (AL_GAIN,     1.0f);
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
		ALfloat orientation[6] = { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		alListenerfv(AL_ORIENTATION, orientation);
		
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
		
		if ( alcIsExtensionPresent(ALDevice, (ALCchar*)ALC_EXT_EFX_NAME) )
		{ 
			_effectsSupported = providers[index].bSupportsFx;
			alGenAuxiliaryEffectSlots(1, &ALEffectSlot);
			alGenEffects(1, &ALEffect);
		}

		alGenSources(MAX_STREAMS*2, ALStreamSources[0]);
		for ( int32 i = 0; i < MAX_STREAMS; i++ )
		{
			alGenBuffers(NUM_STREAMBUFFERS, ALStreamBuffers[i]);
			alSourcei(ALStreamSources[i][0], AL_SOURCE_RELATIVE, AL_TRUE);
			alSource3f(ALStreamSources[i][0], AL_POSITION, 0.0f, 0.0f, 0.0f);
			alSourcef(ALStreamSources[i][0], AL_GAIN, 1.0f);
			alSourcei(ALStreamSources[i][1], AL_SOURCE_RELATIVE, AL_TRUE);
			alSource3f(ALStreamSources[i][1], AL_POSITION, 0.0f, 0.0f, 0.0f);
			alSourcef(ALStreamSources[i][1], AL_GAIN, 1.0f);
		} 
		
		CChannel::InitChannels();

		for ( int32 i = 0; i < MAXCHANNELS; i++ )
			aChannel[i].Init(i);
		for ( int32 i = 0; i < MAX2DCHANNELS; i++ )
			aChannel[MAXCHANNELS+i].Init(MAXCHANNELS+i, true);
		
		if ( IsFXSupported() )
		{
			/**/
			alAuxiliaryEffectSloti(ALEffectSlot, AL_EFFECTSLOT_EFFECT, ALEffect);
			/**/
			
			for ( int32 i = 0; i < MAXCHANNELS; i++ )
				aChannel[i].SetReverbMix(ALEffectSlot, 0.0f);
		}
	}

	{	
		for ( int32 i = 0; i < TOTAL_STREAMED_SOUNDS; i++ )
			nStreamLength[i] = 0;
	}

#ifdef AUDIO_CACHE
	FILE *cacheFile = fcaseopen("audio\\sound.cache", "rb");
	if (cacheFile) {
		debug("Loadind audio cache (If game crashes around here, then your cache is corrupted, remove audio/sound.cache)\n");
		fread(nStreamLength, sizeof(uint32), TOTAL_STREAMED_SOUNDS, cacheFile);
		fclose(cacheFile);
	} else
	{
		debug("Cannot load audio cache\n");
#endif

		for ( int32 i = 0; i < TOTAL_STREAMED_SOUNDS; i++ )
		{	
			bool opened = false;
			char filename[MAX_PATH];
			sprintf(filename, "%s.VB", StreamedNameTable[i]);
			if ( aStream[0] )
				opened = aStream[0]->Open(filename, IsThisTrackAt16KHz(i) ? 16000 : 32000);
			
			if ( !opened )
			{
				sprintf(filename, "%s.MP3", StreamedNameTable[i]);
				if ( aStream[0] )
				{
					opened = aStream[0]->Open(filename, IsThisTrackAt16KHz(i) ? 16000 : 32000);
				}
			}
			if ( opened )
			{
				uint32 tatalms = aStream[0]->GetLengthMS();
				aStream[0]->Close();
				
				nStreamLength[i] = tatalms;
			} else
				USERERROR("Can't open '%s'\n", StreamedNameTable[i]);
		}
#ifdef AUDIO_CACHE
		cacheFile = fcaseopen("audio\\sound.cache", "wb");
		if(cacheFile) {
			debug("Saving audio cache\n");
			fwrite(nStreamLength, sizeof(uint32), TOTAL_STREAMED_SOUNDS, cacheFile);
			fclose(cacheFile);
		} else {
			debug("Cannot save audio cache\n");
		}
	}
#endif

	{
		if ( !InitialiseSampleBanks() )
		{
			Terminate();
			return FALSE;
		}
		
		nSampleBankMemoryStartAddress[SFX_BANK_0] = (uintptr)malloc(nSampleBankSize[SFX_BANK_0]);
		ASSERT(nSampleBankMemoryStartAddress[SFX_BANK_0] != 0);
		
		if ( nSampleBankMemoryStartAddress[SFX_BANK_0] == 0 )
		{
			Terminate();
			return FALSE;
		}
		
		nSampleBankMemoryStartAddress[SFX_BANK_PED_COMMENTS] = (uintptr)malloc(PED_BLOCKSIZE*MAX_PEDSFX);
		ASSERT(nSampleBankMemoryStartAddress[SFX_BANK_PED_COMMENTS] != 0);

		nMissionSlotSfxStartAddress = (uintptr)malloc(MISSION_AUDIO_BLOCKSIZE*MISSION_AUDIO_SLOTS);
		ASSERT(nMissionSlotSfxStartAddress != 0);

		// Find biggest player comment
		uint32 nMaxPedSize = 0;
		for (uint32 i = PLAYER_COMMENTS_START; i <= PLAYER_COMMENTS_END; i++)
			nMaxPedSize = Max(nMaxPedSize, m_aSamples[i].nSize);

		gPlayerTalkData = malloc(nMaxPedSize);
		ASSERT(gPlayerTalkData != 0);

		LoadSampleBank(SFX_BANK_0);
	}
	
	{
		for ( int32 i = 0; i < MAX_STREAMS; i++ )
		{
			aStream[i]->Close();

			nStreamVolume[i] = 100;
			nStreamPan[i]    = 63;
		}
	}

	{
		_bSampmanInitialised = TRUE;
		
		if ( defaultProvider >= 0 && defaultProvider < m_nNumberOfProviders )
		{
			set_new_provider(defaultProvider);
		}
		else
		{
			Terminate();
			return FALSE;
		}
	}

	{
		nNumMP3s = 0;
		
		_pMP3List = NULL;
		
		_FindMP3s();
		
		if ( nNumMP3s != 0 )
		{
			nStreamLength[STREAMED_SOUND_RADIO_MP3_PLAYER] = 0;
			
			for ( tMP3Entry *e = _pMP3List; e != NULL; e = e->pNext )
			{
				e->nTrackStreamPos = nStreamLength[STREAMED_SOUND_RADIO_MP3_PLAYER];
				nStreamLength[STREAMED_SOUND_RADIO_MP3_PLAYER] += e->nTrackLength;
			}
			
			time_t t = time(NULL);
			tm *localtm;
			bool8 bUseRandomTable;
			
			if ( t == -1 )
				bUseRandomTable = TRUE;
			else
			{
				bUseRandomTable = FALSE;
				localtm = localtime(&t);
			}
			
			int32 randval;
			if ( bUseRandomTable )
				randval = AudioManager.m_anRandomTable[1];
			else
				randval = localtm->tm_sec * localtm->tm_min;
			
			_CurMP3Index = randval % nNumMP3s;
			
			tMP3Entry *randmp3 = _pMP3List;
			for ( int32 i = randval % nNumMP3s; i > 0; --i)
				randmp3 = randmp3->pNext;
			
			if ( bUseRandomTable )
				_CurMP3Pos = AudioManager.m_anRandomTable[0]     % randmp3->nTrackLength;
			else
			{
				if ( localtm->tm_sec > 0 )
				{
					int32 s = localtm->tm_sec;
					_CurMP3Pos = s*s*s*s*s*s*s*s                 % randmp3->nTrackLength;
				}
				else
					_CurMP3Pos = AudioManager.m_anRandomTable[0] % randmp3->nTrackLength;
			}
		}
		else
			_CurMP3Pos = 0;
		
		_bIsMp3Active = FALSE;
	}
	
	return TRUE;
}

void
cSampleManager::Terminate(void)
{
	for (int32 i = 0; i < MAX_STREAMS; i++)
		aStream[i]->Close();

	for ( int32 i = 0; i < NUM_CHANNELS; i++ )
		aChannel[i].Term();

	if ( IsFXSupported() )
	{
		if ( alIsEffect(ALEffect) )
		{
			alEffecti(ALEffect, AL_EFFECT_TYPE, AL_EFFECT_NULL);
			alDeleteEffects(1, &ALEffect);
			ALEffect = AL_EFFECT_NULL;
		}
		
		if (alIsAuxiliaryEffectSlot(ALEffectSlot))
		{
			alAuxiliaryEffectSloti(ALEffectSlot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
			
			alDeleteAuxiliaryEffectSlots(1, &ALEffectSlot);
			ALEffectSlot = AL_EFFECTSLOT_NULL;
		}
	}

	for ( int32 i = 0; i < MAX_STREAMS; i++ )
	{
		alDeleteBuffers(NUM_STREAMBUFFERS, ALStreamBuffers[i]);
	}
	alDeleteSources(MAX_STREAMS*2, ALStreamSources[0]);
	
	CChannel::DestroyChannels();
	
	if ( ALContext )
	{
		alcMakeContextCurrent(NULL);
		alcSuspendContext(ALContext);
		alcDestroyContext(ALContext);
	}
	if ( ALDevice )
		alcCloseDevice(ALDevice);
	
	ALDevice = NULL;
	ALContext = NULL;
	
	_fPrevEaxRatioDestination = 0.0f;
	_usingEFX                 = false;
	_fEffectsLevel            = 0.0f;
	
	_DeleteMP3Entries();

	CStream::Terminate();

	for(int32 i = 0; i < MAX_STREAMS; i++)
		delete aStream[i];

	if ( nSampleBankMemoryStartAddress[SFX_BANK_0] != 0 )
	{
		free((void *)nSampleBankMemoryStartAddress[SFX_BANK_0]);
		nSampleBankMemoryStartAddress[SFX_BANK_0] = 0;
	}

	if ( nSampleBankMemoryStartAddress[SFX_BANK_PED_COMMENTS] != 0 )
	{
		free((void *)nSampleBankMemoryStartAddress[SFX_BANK_PED_COMMENTS]);
		nSampleBankMemoryStartAddress[SFX_BANK_PED_COMMENTS] = 0;
	}

	if ( nMissionSlotSfxStartAddress != 0 )
	{
		free((void*)nMissionSlotSfxStartAddress);
		nMissionSlotSfxStartAddress = 0;

		for ( uint32 i = 0; i < MISSION_AUDIO_SLOTS; i++ )
			nMissionSlotSfx[i] = UINT32_MAX;
	}

	if ( gPlayerTalkData != 0 )
	{
		free(gPlayerTalkData);
		gPlayerTalkData = 0;
	}
	
	_bSampmanInitialised = FALSE;
}

bool8 cSampleManager::CheckForAnAudioFileOnCD(void)
{
	return TRUE;
}

char cSampleManager::GetCDAudioDriveLetter(void)
{
	return '\0';
}

void
cSampleManager::UpdateEffectsVolume(void)
{
	if ( _bSampmanInitialised )
	{
		for ( int32 i = 0; i < NUM_CHANNELS; i++ )
		{
			if ( GetChannelUsedFlag(i) )
			{
				if ( nChannelVolume[i] != 0 )
					aChannel[i].SetVolume(m_nEffectsFadeVolume*nChannelVolume[i]*m_nEffectsVolume >> 14);
			}
		}
	}
}

void
cSampleManager::SetEffectsMasterVolume(uint8 nVolume)
{
	m_nEffectsVolume = nVolume;
	UpdateEffectsVolume();
}

void
cSampleManager::SetMusicMasterVolume(uint8 nVolume)
{
	m_nMusicVolume = nVolume;
}

void
cSampleManager::SetMP3BoostVolume(uint8 nVolume)
{
	m_nMP3BoostVolume = nVolume;
}

void
cSampleManager::SetEffectsFadeVolume(uint8 nVolume)
{
	m_nEffectsFadeVolume = nVolume;
	UpdateEffectsVolume();
}

void
cSampleManager::SetMusicFadeVolume(uint8 nVolume)
{
	m_nMusicFadeVolume = nVolume;
}

void
cSampleManager::SetMonoMode(bool8 nMode)
{
	m_nMonoMode = nMode;
}

bool8
cSampleManager::LoadSampleBank(uint8 nBank)
{
	ASSERT( nBank < MAX_SFX_BANKS);
	
	if ( CTimer::GetIsCodePaused() )
		return FALSE;
	
	if ( MusicManager.IsInitialised()
		&& MusicManager.GetMusicMode() == MUSICMODE_CUTSCENE
		&& nBank != SFX_BANK_0 )
	{
		return FALSE;
	}
	
#ifdef OPUS_SFX
	int samplesRead = 0;
	int samplesSize = nSampleBankSize[nBank] / 2;
	op_pcm_seek(fpSampleDataHandle, 0);
	while (samplesSize > 0) {
		int size = op_read(fpSampleDataHandle, (opus_int16 *)(nSampleBankMemoryStartAddress[nBank] + samplesRead), samplesSize, NULL);
		if (size <= 0) {
			// huh?
			//assert(0);
			break;
		}
		samplesRead += size*2;
		samplesSize -= size;
	}
#else
	if ( fseek(fpSampleDataHandle, nSampleBankDiscStartOffset[nBank], SEEK_SET) != 0 )
		return FALSE;
	
	if ( fread((void *)nSampleBankMemoryStartAddress[nBank], 1, nSampleBankSize[nBank], fpSampleDataHandle) != nSampleBankSize[nBank] )
		return FALSE;
#endif
	gBankLoaded[nBank] = LOADING_STATUS_LOADED;
	
	return TRUE;
}

void
cSampleManager::UnloadSampleBank(uint8 nBank)
{
	ASSERT( nBank < MAX_SFX_BANKS);
	
	gBankLoaded[nBank] = LOADING_STATUS_NOT_LOADED;
}

int8
cSampleManager::IsSampleBankLoaded(uint8 nBank)
{
	ASSERT( nBank < MAX_SFX_BANKS);
	
	return gBankLoaded[nBank];
}

uint8
cSampleManager::IsMissionAudioLoaded(uint8 nSlot, uint32 nSample)
{
	ASSERT(nSlot != MISSION_AUDIO_POLRADIO_CRIME_OR_COLOR && nSlot != MISSION_AUDIO_POLRADIO_AREA_OR_CAR); // these are not used in LCS

	switch (nSlot)
	{
	case MISSION_AUDIO_SLOT_1:
	case MISSION_AUDIO_SLOT_2:
		return nMissionSlotSfx[nSlot] == nSample ? LOADING_STATUS_LOADED : LOADING_STATUS_NOT_LOADED;
	case MISSION_AUDIO_PLAYER_COMMENT:
		return nSample == gPlayerTalkSfx ? LOADING_STATUS_LOADED : LOADING_STATUS_NOT_LOADED;
	}
	return FALSE;
}

bool8
cSampleManager::LoadMissionAudio(uint8 nSlot, uint32 nSample)
{
	ASSERT(nSlot != MISSION_AUDIO_POLRADIO_CRIME_OR_COLOR && nSlot != MISSION_AUDIO_POLRADIO_AREA_OR_CAR); // these are not used in LCS
	ASSERT(nSample < TOTAL_AUDIO_SAMPLES);
	
	if (fseek(fpSampleDataHandle, m_aSamples[nSample].nOffset, SEEK_SET) != 0)
		return FALSE;

	switch (nSlot)
	{
	case MISSION_AUDIO_SLOT_1:
	case MISSION_AUDIO_SLOT_2:
		if (fread((void*)(nMissionSlotSfxStartAddress + nSlot*MISSION_AUDIO_BLOCKSIZE), 1, m_aSamples[nSample].nSize, fpSampleDataHandle) != m_aSamples[nSample].nSize)
			return FALSE;

		nMissionSlotSfx[nSlot] = nSample;
		break;
	case MISSION_AUDIO_PLAYER_COMMENT:
		if (fread(gPlayerTalkData, 1, m_aSamples[nSample].nSize, fpSampleDataHandle) != m_aSamples[nSample].nSize)
			return FALSE;

		gPlayerTalkSfx = nSample;
		break;
	}

	return TRUE;
}

uint8
cSampleManager::IsPedCommentLoaded(uint32 nComment)
{
	ASSERT( nComment < TOTAL_AUDIO_SAMPLES );
	
	for ( int32 i = 0; i < _TODOCONST(3); i++ )
	{
#ifdef FIX_BUGS
		int8 slot = (int8)nCurrentPedSlot - i - 1;
		if (slot < 0)
			slot += ARRAY_SIZE(nPedSlotSfx);
#else
		uint8 slot = nCurrentPedSlot - i - 1;
#endif
		if ( nComment == nPedSlotSfx[slot] )
			return LOADING_STATUS_LOADED;
	}
	
	return LOADING_STATUS_NOT_LOADED;
}


int32
cSampleManager::_GetPedCommentSlot(uint32 nComment)
{
	for (int32 i = 0; i < _TODOCONST(3); i++)
	{
#ifdef FIX_BUGS
		int8 slot = (int8)nCurrentPedSlot - i - 1;
		if (slot < 0)
			slot += ARRAY_SIZE(nPedSlotSfx);
#else
		uint8 slot = nCurrentPedSlot - i - 1;
#endif
		if (nComment == nPedSlotSfx[slot])
			return slot;
	}

	return -1;
}

bool8
cSampleManager::LoadPedComment(uint32 nComment)
{
	ASSERT( nComment < TOTAL_AUDIO_SAMPLES );
	
	if ( CTimer::GetIsCodePaused() )
		return FALSE;
	
	// no talking peds during cutsenes or the game end
	if ( MusicManager.IsInitialised() )
	{
		switch ( MusicManager.GetMusicMode() )
		{
			case MUSICMODE_CUTSCENE:
			{
				return FALSE;

				break;
			}
		}
	}

#ifdef OPUS_SFX
	int samplesRead = 0;
	int samplesSize = m_aSamples[nComment].nSize / 2;
	op_pcm_seek(fpSampleDataHandle, m_aSamples[nComment].nOffset / 2);
	while (samplesSize > 0) {
		int size = op_read(fpSampleDataHandle, (opus_int16 *)(nSampleBankMemoryStartAddress[SAMPLEBANK_PED] + PED_BLOCKSIZE * nCurrentPedSlot + samplesRead),
		                   samplesSize, NULL);
		if (size <= 0) {
			return FALSE;
		}
		samplesRead += size * 2;
		samplesSize -= size;
	}
#else
	if ( fseek(fpSampleDataHandle, m_aSamples[nComment].nOffset, SEEK_SET) != 0 )
		return FALSE;
	
	if ( fread((void *)(nSampleBankMemoryStartAddress[SFX_BANK_PED_COMMENTS] + PED_BLOCKSIZE*nCurrentPedSlot), 1, m_aSamples[nComment].nSize, fpSampleDataHandle) != m_aSamples[nComment].nSize )
		return FALSE;

#endif
	nPedSlotSfx[nCurrentPedSlot] = nComment;
		
	if ( ++nCurrentPedSlot >= MAX_PEDSFX )
		nCurrentPedSlot = 0;
	
	return TRUE;
}

int32
cSampleManager::GetBankContainingSound(uint32 offset)
{
	if ( offset >= BankStartOffset[SFX_BANK_PED_COMMENTS] )
		return SFX_BANK_PED_COMMENTS;
	
	if ( offset >= BankStartOffset[SFX_BANK_0] )
		return SFX_BANK_0;
	
	return INVALID_SFX_BANK;
}

uint32
cSampleManager::GetSampleBaseFrequency(uint32 nSample)
{
	ASSERT( nSample < TOTAL_AUDIO_SAMPLES );
	return m_aSamples[nSample].nFrequency;
}

uint32
cSampleManager::GetSampleLoopStartOffset(uint32 nSample)
{
	ASSERT( nSample < TOTAL_AUDIO_SAMPLES );
	return m_aSamples[nSample].nLoopStart;
}

int32
cSampleManager::GetSampleLoopEndOffset(uint32 nSample)
{
	ASSERT( nSample < TOTAL_AUDIO_SAMPLES );
	return m_aSamples[nSample].nLoopEnd;
}

uint32
cSampleManager::GetSampleLength(uint32 nSample)
{
	ASSERT( nSample < TOTAL_AUDIO_SAMPLES );
	return m_aSamples[nSample].nSize / sizeof(uint16);
}

bool8 cSampleManager::UpdateReverb(void)
{
	if ( !usingEAX && !_usingEFX )
		return FALSE;

	if ( AudioManager.m_FrameCounter & 15 )
		return FALSE;

	float fRatio = 0.0f;

#ifdef AUDIO_REFLECTIONS
#define MIN_DIST 0.5f
#define CALCULATE_RATIO(value, maxDist, maxRatio) (value > MIN_DIST && value < maxDist ? value / maxDist * maxRatio : 0)

	fRatio += CALCULATE_RATIO(AudioManager.m_afReflectionsDistances[REFLECTION_CEIL_NORTH], 10.0f, 1/2.f);
	fRatio += CALCULATE_RATIO(AudioManager.m_afReflectionsDistances[REFLECTION_CEIL_SOUTH], 10.0f, 1/2.f);
	fRatio += CALCULATE_RATIO(AudioManager.m_afReflectionsDistances[REFLECTION_CEIL_WEST], 10.0f, 1/2.f);
	fRatio += CALCULATE_RATIO(AudioManager.m_afReflectionsDistances[REFLECTION_CEIL_EAST], 10.0f, 1/2.f);

	fRatio += CALCULATE_RATIO((AudioManager.m_afReflectionsDistances[REFLECTION_NORTH] + AudioManager.m_afReflectionsDistances[REFLECTION_SOUTH]) / 2.f, 4.0f, 1/3.f);
	fRatio += CALCULATE_RATIO((AudioManager.m_afReflectionsDistances[REFLECTION_WEST] + AudioManager.m_afReflectionsDistances[REFLECTION_EAST]) / 2.f, 4.0f, 1/3.f);

#undef CALCULATE_RATIO
#undef MIN_DIST
#endif
	
	fRatio = Clamp(fRatio, 0.0f, 0.6f);
	
	if ( fRatio == _fPrevEaxRatioDestination )
		return FALSE;
	
#ifdef JUICY_OAL
	if ( usingEAX3 || _usingEFX )
#else
	if ( usingEAX3 )
#endif
	{
		fRatio = Min(fRatio * 1.67f, 1.0f);
		if ( EAX3ListenerInterpolate(&StartEAX3, &FinishEAX3, fRatio, &EAX3Params, false) )
		{
			EAX_SetAll(&EAX3Params);
			
			/*
			if ( IsFXSupported() )
			{
				alAuxiliaryEffectSloti(ALEffectSlot, AL_EFFECTSLOT_EFFECT, ALEffect);
			
				for ( int32 i = 0; i < MAXCHANNELS; i++ )
					aChannel[i].UpdateReverb(ALEffectSlot);
			}
			*/
			
			_fEffectsLevel = fRatio * 0.75f;
		}
	}
	else
	{
		if ( _usingEFX )
			_fEffectsLevel = fRatio * 0.8f;
		else
			_fEffectsLevel = fRatio * 0.22f;
	}
	_fEffectsLevel = Min(_fEffectsLevel, 1.0f);

	_fPrevEaxRatioDestination = fRatio;
	
	return TRUE;
}

void
cSampleManager::SetChannelReverbFlag(uint32 nChannel, bool8 nReverbFlag)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	if ( usingEAX || _usingEFX )
	{
		if ( IsFXSupported() )
		{
			alAuxiliaryEffectSloti(ALEffectSlot, AL_EFFECTSLOT_EFFECT, ALEffect);
			
			if ( nReverbFlag != FALSE )
				aChannel[nChannel].SetReverbMix(ALEffectSlot, _fEffectsLevel);
			else
				aChannel[nChannel].SetReverbMix(ALEffectSlot, 0.0f);
		}
	}
}

bool8
cSampleManager::InitialiseChannel(uint32 nChannel, uint32 nSfx, uint8 nBank)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	uintptr addr;
	
	if ( nSfx < SAMPLEBANK_MAX )
	{
		if ( !IsSampleBankLoaded(nBank) )
			return FALSE;
		
		addr = nSampleBankMemoryStartAddress[nBank] + m_aSamples[nSfx].nOffset - m_aSamples[BankStartOffset[nBank]].nOffset;
	}
	else if ( nSfx >= PLAYER_COMMENTS_START && nSfx <= PLAYER_COMMENTS_END )
	{
		if ( !IsMissionAudioLoaded(MISSION_AUDIO_PLAYER_COMMENT, nSfx) )
			return FALSE;

		addr = (uintptr)gPlayerTalkData;
	}
	else
	{
		for ( uint32 i = 0; i < MISSION_AUDIO_SLOTS; i++ ) {
			if ( IsMissionAudioLoaded(i, nSfx) ) {
				addr = nMissionSlotSfxStartAddress + i * MISSION_AUDIO_BLOCKSIZE;
				goto MissionAudioFound;
			}
		}

		int32 i;
		for ( i = 0; i < _TODOCONST(3); i++ )
		{
			int32 slot = nCurrentPedSlot - i - 1;
#ifdef FIX_BUGS
			if (slot < 0)
				slot += ARRAY_SIZE(nPedSlotSfx);
#endif
			if ( nSfx == nPedSlotSfx[slot] )
			{
				addr = (nSampleBankMemoryStartAddress[SFX_BANK_PED_COMMENTS] + PED_BLOCKSIZE * slot);
				break;
			}
		}

		if (i == _TODOCONST(3))
			return FALSE;
	}

MissionAudioFound:
	if ( GetChannelUsedFlag(nChannel) )
	{
		TRACE("Stopping channel %d - really!!!", nChannel);
		StopChannel(nChannel);
	}
	
	aChannel[nChannel].Reset();
	if ( aChannel[nChannel].HasSource() )
	{	
		aChannel[nChannel].SetSampleData   ((void*)addr, m_aSamples[nSfx].nSize, m_aSamples[nSfx].nFrequency);
		aChannel[nChannel].SetLoopPoints   (0, -1);
		aChannel[nChannel].SetPitch        (1.0f);
		return TRUE;
	}
	
	return FALSE;
}

void
cSampleManager::SetChannelEmittingVolume(uint32 nChannel, uint32 nVolume)
{
	ASSERT( nChannel < MAXCHANNELS );
	
	uint32 vol = nVolume;
	if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
	
	nChannelVolume[nChannel] = vol;
	
	if (MusicManager.GetMusicMode() == MUSICMODE_CUTSCENE ) {
		if (MusicManager.GetCurrentTrack() == STREAMED_SOUND_CUTSCENE_FINALE)
			nChannelVolume[nChannel] = 0;
		else
			nChannelVolume[nChannel] >>= 2;
	}

	// no idea, does this one looks like a bug or it's SetChannelVolume ?
	aChannel[nChannel].SetVolume(m_nEffectsFadeVolume*nChannelVolume[nChannel]*m_nEffectsVolume >> 14);
}

void
cSampleManager::SetChannel3DPosition(uint32 nChannel, float fX, float fY, float fZ)
{
	ASSERT( nChannel < MAXCHANNELS );
	
	aChannel[nChannel].SetPosition(-fX, fY, fZ);
}

void
cSampleManager::SetChannel3DDistances(uint32 nChannel, float fMax, float fMin)
{
	ASSERT( nChannel < MAXCHANNELS );
	aChannel[nChannel].SetDistances(fMax, fMin);
}

void
cSampleManager::SetChannelVolume(uint32 nChannel, uint32 nVolume)
{
	ASSERT( nChannel >= MAXCHANNELS );
	ASSERT( nChannel < NUM_CHANNELS );
	
	if( nChannel >= CHANNEL_POLICE_RADIO )
	{
		uint32 vol = nVolume;
		if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
		
		nChannelVolume[nChannel] = vol;
		
		// increase the volume for JB.MP3 and S4_BDBD.MP3
		if (MusicManager.GetMusicMode() == MUSICMODE_CUTSCENE ) {
			if (MusicManager.GetCurrentTrack() == STREAMED_SOUND_CUTSCENE_FINALE)
				nChannelVolume[nChannel] = 0;
			else
				nChannelVolume[nChannel] >>= 2;
		}

		aChannel[nChannel].SetVolume(m_nEffectsFadeVolume*vol*m_nEffectsVolume >> 14);
	}
}

void
cSampleManager::SetChannelPan(uint32 nChannel, uint32 nPan)
{
	ASSERT( nChannel >= MAXCHANNELS );
	ASSERT( nChannel < NUM_CHANNELS );
	
	if ( nChannel >= CHANNEL_POLICE_RADIO )
	{
		aChannel[nChannel].SetPan(nPan);
	}
}

void
cSampleManager::SetChannelFrequency(uint32 nChannel, uint32 nFreq)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	aChannel[nChannel].SetCurrentFreq(nFreq);
}

void
cSampleManager::SetChannelLoopPoints(uint32 nChannel, uint32 nLoopStart, int32 nLoopEnd)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	aChannel[nChannel].SetLoopPoints(nLoopStart / (DIGITALBITS / 8), nLoopEnd / (DIGITALBITS / 8));
}

void
cSampleManager::SetChannelLoopCount(uint32 nChannel, uint32 nLoopCount)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	aChannel[nChannel].SetLoopCount(nLoopCount);
}

bool8
cSampleManager::GetChannelUsedFlag(uint32 nChannel)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	return aChannel[nChannel].IsUsed();
}

void
cSampleManager::StartChannel(uint32 nChannel)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	aChannel[nChannel].Start();
}

void
cSampleManager::StopChannel(uint32 nChannel)
{
	ASSERT( nChannel < NUM_CHANNELS );
	
	aChannel[nChannel].Stop();
}

void
cSampleManager::PreloadStreamedFile(uint32 nFile, uint8 nStream)
{
	char filename[MAX_PATH];
	
	ASSERT( nStream < MAX_STREAMS );

	if ( nFile < TOTAL_STREAMED_SOUNDS )
	{
		CStream *stream = aStream[nStream];

		stream->Close();
		sprintf(filename, "%s.VB", StreamedNameTable[nFile]);
		bool opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
		if ( !opened )
		{
			sprintf(filename, "%s.MP3", StreamedNameTable[nFile]);
			opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
		}
		
		if ( opened && !stream->Setup() )
		{
			stream->Close();
		}
	}
}

void
cSampleManager::PauseStream(bool8 nPauseFlag, uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	CStream *stream = aStream[nStream];
	
	if ( stream->IsOpened() )
	{
		stream->SetPause(nPauseFlag != FALSE);
	}
}

void
cSampleManager::StartPreloadedStreamedFile(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	CStream *stream = aStream[nStream];
	
	if ( stream->IsOpened() )
	{
		stream->Start();
	}
}

bool8
cSampleManager::StartStreamedFile(uint32 nFile, uint32 nPos, uint8 nStream)
{
	uint32 i = 0;
	uint32 position = nPos;
	char filename[MAX_PATH];
	
	if ( nFile >= TOTAL_STREAMED_SOUNDS )
		return FALSE;

	aStream[nStream]->Close();

	if ( nFile == STREAMED_SOUND_RADIO_MP3_PLAYER )
	{
		do
		{
			// Just switched to MP3 player
			if ( !_bIsMp3Active && i == 0 )
			{
				if ( nPos > nStreamLength[STREAMED_SOUND_RADIO_MP3_PLAYER] )
					position = 0;
				tMP3Entry *e = _pMP3List;

				// Try to continue from previous song, if already started
				if(!_GetMP3PosFromStreamPos(&position, &e) && !e) {
					nFile = 0;

					sprintf(filename, "%s.VB", StreamedNameTable[nFile]);

					CStream *stream = aStream[nStream];
					bool opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
					
					if ( !opened )
					{
						sprintf(filename, "%s.MP3", StreamedNameTable[nFile]);
						opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
					}
					
					if ( opened && stream->Setup() ) {
						stream->SetLoopCount(nStreamLoopedFlag[nStream] ? 0 : 1);
						nStreamLoopedFlag[nStream] = TRUE;
						if (position != 0)
							stream->SetPosMS(position);

						stream->Start();

						return TRUE;
					} else {
						stream->Close();
					}
					return FALSE;

				} else {

					if (e->pLinkPath != NULL)
						aStream[nStream]->Open(e->pLinkPath, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
					else {
						strcpy(filename, _mp3DirectoryPath);
						strcat(filename, e->aFilename);

						aStream[nStream]->Open(filename);
					}

					if (aStream[nStream]->Setup()) {
						if (position != 0)
							aStream[nStream]->SetPosMS(position);

						aStream[nStream]->Start();

						_bIsMp3Active = TRUE;
						return TRUE;
					} else {
						aStream[nStream]->Close();
					}
					// fall through, start playing from another song
				}
			} else {
				if(++_CurMP3Index >= nNumMP3s) _CurMP3Index = 0;

				_CurMP3Pos = 0;

				tMP3Entry *mp3 = _GetMP3EntryByIndex(_CurMP3Index);
				if ( !mp3 )
				{
					mp3 = _pMP3List;
					if ( !_pMP3List )
					{
						nFile = 0;
						_bIsMp3Active = FALSE;
						sprintf(filename, "%s.VB", StreamedNameTable[nFile]);

						CStream* stream = aStream[nStream];
						bool opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);

						if ( !opened )
						{
							sprintf(filename, "%s.MP3", StreamedNameTable[nFile]);
							opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
						}
						
						if (opened && stream->Setup()) {
							stream->SetLoopCount(nStreamLoopedFlag[nStream] ? 0 : 1);
							nStreamLoopedFlag[nStream] = TRUE;
							if (position != 0)
								stream->SetPosMS(position);

							stream->Start();

							return TRUE;
						} else {
							stream->Close();
						}
						return FALSE;
					}
				}
				if (mp3->pLinkPath != NULL)
					aStream[nStream]->Open(mp3->pLinkPath, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
				else {
					strcpy(filename, _mp3DirectoryPath);
					strcat(filename, mp3->aFilename);

					aStream[nStream]->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
				}

				if (aStream[nStream]->Setup()) {
					aStream[nStream]->Start();
#ifdef FIX_BUGS
					_bIsMp3Active = TRUE;
#endif
					return TRUE;
				} else {
					aStream[nStream]->Close();
				}

			}
			_bIsMp3Active = FALSE;
		}
		while ( ++i < nNumMP3s );
		position = 0;
		nFile = 0;
	}
	sprintf(filename, "%s.VB", StreamedNameTable[nFile]);

	CStream *stream = aStream[nStream];
	
	bool opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);

	if ( !opened )
	{
		sprintf(filename, "%s.MP3", StreamedNameTable[nFile]);
		opened = stream->Open(filename, IsThisTrackAt16KHz(nFile) ? 16000 : 32000);
	}
	
	if ( opened && stream->Setup() ) {
		stream->SetLoopCount(nStreamLoopedFlag[nStream] ? 0 : 1);
		nStreamLoopedFlag[nStream] = TRUE;
		if (position != 0)
			stream->SetPosMS(position);	

		stream->Start();
		
		return TRUE;
	} else {
		stream->Close();
	}
	return FALSE;
}

void
cSampleManager::StopStreamedFile(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );

	CStream *stream = aStream[nStream];
	
	stream->Close();

	if ( nStream == 0 )
		_bIsMp3Active = FALSE;
}

int32
cSampleManager::GetStreamedFilePosition(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	CStream *stream = aStream[nStream];
	
	if ( stream->IsOpened() )
	{
		if ( _bIsMp3Active )
		{
			tMP3Entry *mp3 = _GetMP3EntryByIndex(_CurMP3Index);
			
			if ( mp3 != NULL )
			{
				return stream->GetPosMS() + mp3->nTrackStreamPos;
			}
			else
				return 0;
		}
		else
		{
			return stream->GetPosMS();
		}
	}
	
	return 0;
}

void
cSampleManager::SetStreamedVolumeAndPan(uint8 nVolume, uint8 nPan, bool8 nEffectFlag, uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	float boostMult = 0.0f;

	if ( nVolume > MAX_VOLUME )
		nVolume = MAX_VOLUME;
	
	if ( nPan > MAX_VOLUME )
		nPan = MAX_VOLUME;

	if ( MusicManager.GetRadioInCar() == USERTRACK && !MusicManager.CheckForMusicInterruptions() )
			boostMult = m_nMP3BoostVolume / 64.f;
		
	nStreamVolume[nStream] = nVolume;
	nStreamPan   [nStream] = nPan;
	
	CStream *stream = aStream[nStream];
	
	if ( stream->IsOpened() )
	{
		if ( nEffectFlag ) {
			if ( nStream == 1 || nStream == 2 )
				stream->SetVolume(128*nVolume*m_nEffectsVolume >> 14);
			else
				stream->SetVolume(m_nEffectsFadeVolume*nVolume*m_nEffectsVolume >> 14);
		}
		else
			stream->SetVolume((m_nMusicFadeVolume*nVolume*(uint32)(m_nMusicVolume * boostMult + m_nMusicVolume)) >> 14);
		
		stream->SetPan(nPan);
	}
}

int32
cSampleManager::GetStreamedFileLength(uint8 nStream)
{
	ASSERT( nStream < TOTAL_STREAMED_SOUNDS );

	return nStreamLength[nStream];
}

bool8
cSampleManager::IsStreamPlaying(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	CStream *stream = aStream[nStream];
	
	if ( stream->IsOpened() )
	{
		if ( stream->IsPlaying() )
			return TRUE;
	}
	
	return FALSE;
}

void
cSampleManager::Service(void)
{
	for ( int32 i = 0; i < MAX_STREAMS; i++ )
	{
		CStream *stream = aStream[i];
		
		if ( stream->IsOpened() )
			stream->Update();
	}
	int refCount = CChannel::channelsThatNeedService;
	for ( int32 i = 0; refCount && i < NUM_CHANNELS; i++ )
	{
		if ( aChannel[i].Update() )
			refCount--;
	}
}

bool8
cSampleManager::InitialiseSampleBanks(void)
{
	int32 nBank = SFX_BANK_0;
	
	fpSampleDescHandle = fcaseopen(SampleBankDescFilename, "rb");
	if ( fpSampleDescHandle == NULL )
		return FALSE;
#ifndef OPUS_SFX
	fpSampleDataHandle = fcaseopen(SampleBankDataFilename, "rb");
	if ( fpSampleDataHandle == NULL )
	{
		fclose(fpSampleDescHandle);
		fpSampleDescHandle = NULL;
		
		return FALSE;
	}
	
	fseek(fpSampleDataHandle, 0, SEEK_END);
	int32 _nSampleDataEndOffset = ftell(fpSampleDataHandle);
	rewind(fpSampleDataHandle);
#else
	int e;
	fpSampleDataHandle = op_open_file(SampleBankDataFilename, &e);
#endif
	fread(m_aSamples, sizeof(tSample), TOTAL_AUDIO_SAMPLES, fpSampleDescHandle);
#ifdef OPUS_SFX
	int32 _nSampleDataEndOffset = m_aSamples[TOTAL_AUDIO_SAMPLES - 1].nOffset + m_aSamples[TOTAL_AUDIO_SAMPLES - 1].nSize;
#endif
	fclose(fpSampleDescHandle);
	fpSampleDescHandle = NULL;
	
	for ( uint32 i = 0; i < TOTAL_AUDIO_SAMPLES; i++ )
	{
#ifdef FIX_BUGS
		if (nBank >= MAX_SFX_BANKS) break;
#endif
		if ( BankStartOffset[nBank] == BankStartOffset[SFX_BANK_0] + i )
		{
			nSampleBankDiscStartOffset[nBank] = m_aSamples[i].nOffset;
			nBank++;
		}
	}

	nSampleBankSize[SFX_BANK_0] = nSampleBankDiscStartOffset[SFX_BANK_PED_COMMENTS] - nSampleBankDiscStartOffset[SFX_BANK_0];
	nSampleBankSize[SFX_BANK_PED_COMMENTS]  = _nSampleDataEndOffset                      - nSampleBankDiscStartOffset[SFX_BANK_PED_COMMENTS];

	return TRUE;
}

void
cSampleManager::SetStreamedFileLoopFlag(bool8 nLoopFlag, uint8 nChannel)
{
	nStreamLoopedFlag[nChannel] = nLoopFlag;
}

#endif
