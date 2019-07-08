#include "SampleManager.h"
#include "common.h"
#include "patcher.h"

CSampleManager &cSampleManager = *(CSampleManager *)0x7341E0;

uint32 &nNumOfMp3Files = *(uint32 *)0x95CC00;
uint8 &num3DProvidersAvailable = *(uint8 *)0x734237;
uint32 *asName3DProviders = (uint32 *)0x734238;

bool
CSampleManager::IsMP3RadioChannelAvailable()
{
	return nNumOfMp3Files != 0;
}

WRAPPER
bool
CSampleManager::CheckForAnAudioFileOnCD()
{
	EAXJMP(0x566EA0);
}

WRAPPER
int32 CSampleManager::GetSampleBaseFrequency(int32) { EAXJMP(0x5672A0); }

WRAPPER
int32 CSampleManager::GetSampleLoopStartOffset(int32) { EAXJMP(0x5672C0); }

WRAPPER
int32 CSampleManager::GetSampleLoopEndOffset(int32) { EAXJMP(0x5672E0); }

WRAPPER
bool CSampleManager::IsSampleBankLoaded(uint8) { EAXJMP(0x567130); }

WRAPPER
void CSampleManager::UnloadSampleBank(uint8) { EAXJMP(0x567110); }

WRAPPER
void
CSampleManager::Terminate()
{
	EAXJMP(0x566DC0);
}

WRAPPER
bool
CSampleManager::Initialise()
{
	EAXJMP(0x566530);
}

WRAPPER
int32
CSampleManager::GetActiveSamples()
{
	EAXJMP(0x565970);
}

WRAPPER void
CSampleManager::ReleaseDigitalHandle()
{
	EAXJMP(0x5664B0);
}

WRAPPER
void
CSampleManager::RequireDigitalHandle()
{
	EAXJMP(0x5664F0);
}

WRAPPER
char
CSampleManager::AutoDetect3DProviders()
{
	EAXJMP(0x565990);
}

WRAPPER
uint8
CSampleManager::GetCDAudioDriveLetter()
{
	EAXJMP(0x566F20);
}

WRAPPER
void
CSampleManager::SetEffectsMasterVolume(uint8 volume)
{
	EAXJMP(0x567010);
}

WRAPPER
void
CSampleManager::SetMusicMasterVolume(uint8 volume)
{
	EAXJMP(0x567020);
}

WRAPPER
void
CSampleManager::SetEffectsFadeVol(uint8 volume)
{
	EAXJMP(0x567030);
}

WRAPPER
void
CSampleManager::SetMusicFadeVol(uint8 volume)
{
	EAXJMP(0x567040);
}

WRAPPER
void
CSampleManager::SetSpeakerConfig(uint32 config)
{
	EAXJMP(0x565900);
}

WRAPPER
bool
CSampleManager::GetChannelUsedFlag(int32 id)
{
	EAXJMP(0x567B00);
}

WRAPPER
void
CSampleManager::StopChannel(int32 id)
{
	EAXJMP(0x567BE0);
}

STARTPATCHES
InjectHook(0x566490, CSampleManager::IsMP3RadioChannelAvailable, PATCH_JUMP);
ENDPATCHES