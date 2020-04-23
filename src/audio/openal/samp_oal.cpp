#include <al.h>
#include <alc.h>
#include <mpg123_pre.h>
//#include <mpg123.h>
#include <time.h>
#include <io.h>
#include "samp_oal.h"
#include "AudioManager.h"
#include "MusicManager.h"
#include "Frontend.h"
#include "Timer.h"

#pragma comment( lib, "libmpg123.lib" )
#pragma comment( lib, "OpenAL32.lib" )

cSampleManager SampleManager;
int32 BankStartOffset[MAX_SAMPLEBANKS];


///////////////////////////////////////////////////////////////
class MP3Stream
{
public:
	mpg123_handle *m_pMPG;
	FILE *m_fpFile;
	unsigned char *m_pBuf;
	char m_aFilename[128];
	size_t m_nBufSize;
	size_t m_nLengthInBytes;
	long m_nRate;
	int  m_nBitRate;
	int m_nChannels;
	int m_nEncoding;
	int m_nLength;
	int m_nBlockSize;
	int m_nNumBlocks;
	ALuint m_alSource;
	ALuint m_alBuffers[5];
	unsigned char *m_pBlocks;
	bool m_bIsFree;
	bool m_bIsOpened;
	bool m_bIsPaused;
	int  m_nVolume;
	
	void Initialize(void);
	bool FillBuffer(ALuint alBuffer);
	void Update(void);
	void SetPos(uint32 nPos);
	int32 FillBuffers();
	MP3Stream(char *filename, ALuint source, ALuint *buffers);
	~MP3Stream() { Delete(); }
	void Delete();

};
///////////////////////////////////////////////////////////////

char SampleBankDescFilename[] = "AUDIO\\SFX.SDT";
char SampleBankDataFilename[] = "AUDIO\\SFX.RAW";

FILE *fpSampleDescHandle;
FILE *fpSampleDataHandle;
bool  bSampleBankLoaded            [MAX_SAMPLEBANKS];
int32 nSampleBankDiscStartOffset   [MAX_SAMPLEBANKS];
int32 nSampleBankSize              [MAX_SAMPLEBANKS];
int32 nSampleBankMemoryStartAddress[MAX_SAMPLEBANKS];
int32 _nSampleDataEndOffset;

int32 nPedSlotSfx    [MAX_PEDSFX];
int32 nPedSlotSfxAddr[MAX_PEDSFX];
uint8 nCurrentPedSlot;



uint32 nStreamLength[TOTAL_STREAMED_SOUNDS];

///////////////////////////////////////////////////////////////
ALuint alChannel[MAXCHANNELS+MAX2DCHANNELS];
ALuint ALStreamSources[MAX_STREAMS];
ALuint ALStreamBuffers[MAX_STREAMS][5];
struct
{
	ALuint buffer;
	ALuint timer;
}ALBuffers[SAMPLEBANK_MAX];

ALuint pedBuffers[MAX_PEDSFX];
//bank0Buffers

uint32 nNumMP3s;

MP3Stream *mp3Stream[MAX_STREAMS];
int8 nStreamPan   [MAX_STREAMS];
int8 nStreamVolume[MAX_STREAMS];

float ChannelPitch[MAXCHANNELS+MAX2DCHANNELS];
uint8 nChannelVolume[MAXCHANNELS+MAX2DCHANNELS];
uint32 ChannelSample[MAXCHANNELS+MAX2DCHANNELS];
int32 currentChannelMaxFrontDistance[MAXCHANNELS+MAX2DCHANNELS];
int32 currentChannelFrequency[MAXCHANNELS+MAX2DCHANNELS];
int32 currentChannelVolume[MAXCHANNELS+MAX2DCHANNELS];


cSampleManager::cSampleManager(void)
{
	;
}

cSampleManager::~cSampleManager(void)
{
	ASSERT((void *)nSampleBankMemoryStartAddress[SAMPLEBANK_PED] == NULL);
	free((void *)nSampleBankMemoryStartAddress[SAMPLEBANK_PED]);
	
	if ( fpSampleDescHandle != NULL )
	{
		fclose(fpSampleDescHandle);
		fpSampleDescHandle = NULL;
	}
	
	if ( fpSampleDataHandle != NULL )
	{
		fclose(fpSampleDataHandle);
		fpSampleDataHandle = NULL;
	}
}

void cSampleManager::SetSpeakerConfig(int32 nConfig)
{

}

uint32 cSampleManager::GetMaximumSupportedChannels(void)
{
	return 20;
}

uint32 cSampleManager::GetNum3DProvidersAvailable()
{
	return 1;
}

void cSampleManager::SetNum3DProvidersAvailable(uint32 num)
{
	;
}

char *cSampleManager::Get3DProviderName(uint8 id)
{
	static char PROVIDER[256] = "OpenAL";
	return PROVIDER;
}

void cSampleManager::Set3DProviderName(uint8 id, char *name)
{
	;
}

int8 cSampleManager::GetCurrent3DProviderIndex(void)
{
	return 0;
}

int8 cSampleManager::SetCurrent3DProvider(uint8 which)
{
	return 0;
}

bool
cSampleManager::IsMP3RadioChannelAvailable(void)
{
	return nNumMP3s != 0;
}


void cSampleManager::ReleaseDigitalHandle(void)
{

}

void cSampleManager::ReacquireDigitalHandle(void)
{

}

bool
cSampleManager::Initialise(void)
{
	ALCint attr[] = {ALC_FREQUENCY,MAX_FREQ,0};
	
	m_pDevice  = alcOpenDevice(NULL);
	ASSERT(m_pDevice != NULL);
	
	m_pContext = alcCreateContext(m_pDevice, attr);
	ASSERT(m_pContext != NULL);
	
	alcMakeContextCurrent(m_pContext);
	
	mpg123_init();
	


	for ( int32 i = 0; i < TOTAL_AUDIO_SAMPLES; i++ )
	{
		m_aSamples[i].nOffset    = 0;
		m_aSamples[i].nSize      = 0;
		m_aSamples[i].nFrequency = MAX_FREQ;
		m_aSamples[i].nLoopStart = 0;
		m_aSamples[i].nLoopEnd   = -1;
	}
	
	for ( int32 i = 0; i < TOTAL_STREAMED_SOUNDS; i++ )
		nStreamLength[i] = 3600000;
	
	for ( int32 i = 0; i < MAX_STREAMS; i++ )
	{
		mp3Stream[i]     = NULL;
		nStreamVolume[i] = 100;
		nStreamPan[i]    = 63;
	}
	
	alGenSources(MAX_STREAMS,   (ALuint *)ALStreamSources);
	alGenBuffers(MAX_STREAMS*5, (ALuint *)ALStreamBuffers);
	
	m_nMonoMode = 0;
	
	m_nEffectsVolume     = MAX_VOLUME;
	m_nMusicVolume       = MAX_VOLUME;
	m_nEffectsFadeVolume = MAX_VOLUME;
	m_nMusicFadeVolume   = MAX_VOLUME;

	
	memset(alChannel,      0, sizeof(alChannel));
	memset(nChannelVolume, 0, sizeof(nChannelVolume));
	memset(ChannelSample,  0, sizeof(ChannelSample));
	
	for ( int32 i = 0; i < ARRAY_SIZE(ChannelPitch); i++ )
		ChannelPitch[i] = 1.0f;
	
	
	fpSampleDescHandle = NULL;
	fpSampleDataHandle = NULL;
	
	for ( int32 i = 0; i < MAX_SAMPLEBANKS; i++ )
	{
		bSampleBankLoaded[i]             = false;
		nSampleBankDiscStartOffset[i]    = 0;
		nSampleBankSize[i]               = 0;
		nSampleBankMemoryStartAddress[i] = 0;
	}
	
	alGenBuffers(MAX_PEDSFX, pedBuffers);
	
	for ( int32 i = 0; i < MAX_PEDSFX; i++ )
	{
		nPedSlotSfx[i]     = NO_SAMPLE;
		nPedSlotSfxAddr[i] = 0;
	}
	
	nCurrentPedSlot = 0;
	
	for ( int32 i = 0; i < SAMPLEBANK_MAX; i++ )
	{
		ALBuffers[i].buffer = 0;
		ALBuffers[i].timer  = 0;
	}
	
	alListenerf (AL_GAIN,     1.0f);
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	ALfloat orientation[6] = { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	alListenerfv(AL_ORIENTATION, orientation);
	
	if ( !InitialiseSampleBanks() )
	{
		Terminate();
		return false;
	}
	
	nSampleBankMemoryStartAddress[SAMPLEBANK_MAIN] = (int32)malloc(nSampleBankSize[SAMPLEBANK_MAIN]);
	ASSERT(nSampleBankMemoryStartAddress[SAMPLEBANK_MAIN] != NULL);
	
	if ( nSampleBankMemoryStartAddress[SAMPLEBANK_MAIN] == NULL )
	{
		Terminate();
		return false;
	}
	
	nSampleBankMemoryStartAddress[SAMPLEBANK_PED] = (int32)malloc(PED_BLOCKSIZE*MAX_PEDSFX);
	ASSERT(nSampleBankMemoryStartAddress[SAMPLEBANK_PED] != NULL);
	
	alGenSources(MAXCHANNELS, alChannel);
	for ( int32 i = 0; i < MAXCHANNELS; i++ )
	{
		if ( alChannel[i] )
			alSourcei(alChannel[i], AL_SOURCE_RELATIVE, AL_TRUE);
	}
	
	alGenSources(MAX2DCHANNELS, &alChannel[CHANNEL2D]);
	if ( alChannel[CHANNEL2D] )
	{
		alSourcei (alChannel[CHANNEL2D], AL_SOURCE_RELATIVE, AL_TRUE);
		alSource3f(alChannel[CHANNEL2D], AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcef (alChannel[CHANNEL2D], AL_GAIN, 1.0f);
	}
	
	LoadSampleBank(SAMPLEBANK_MAIN);
	
	return true;
}

void
cSampleManager::Terminate(void)
{
	mpg123_exit();
	alcMakeContextCurrent(NULL);
	alcDestroyContext(m_pContext);
	alcCloseDevice(m_pDevice);
}

void
cSampleManager::UpdateSoundBuffers(void)
{	
	for ( int32 i = 0; i < SAMPLEBANK_MAX; i++ )
	{
		if ( ALBuffers[i].timer > 0 )
		{
			ALBuffers[i].timer -= ALuint(CTimer::GetTimeStep() * 20.0f);
			
			if ( ALBuffers[i].timer <= 0 )
			{
				if ( ALBuffers[i].buffer != 0 && alIsBuffer(ALBuffers[i].buffer) )
				{
					alDeleteBuffers(1, &ALBuffers[i].buffer);
					
					if ( alGetError() == AL_NO_ERROR )
						ALBuffers[i].buffer = 0;
					else
						ALBuffers[i].buffer = 120000;
				}
			}
		}
	}
}

bool cSampleManager::CheckForAnAudioFileOnCD(void)
{
	return true;
}

char cSampleManager::GetCDAudioDriveLetter(void)
{
	return '\0';
}

void
cSampleManager::SetEffectsMasterVolume(uint8 nVolume)
{
	m_nEffectsVolume = nVolume;
}

void
cSampleManager::SetMusicMasterVolume(uint8 nVolume)
{
	m_nMusicVolume = nVolume;
}

void
cSampleManager::SetEffectsFadeVolume(uint8 nVolume)
{
	m_nEffectsFadeVolume = nVolume;
}

void
cSampleManager::SetMusicFadeVolume(uint8 nVolume)
{
	m_nMusicFadeVolume = nVolume;
}

void
cSampleManager::SetMonoMode(uint8 nMode)
{
	m_nMonoMode = nMode;
}

bool
cSampleManager::LoadSampleBank(uint8 nBank)
{
	ASSERT( nBank < MAX_SAMPLEBANKS );
	
	if ( CTimer::GetIsCodePaused() )
		return false;
	
	if ( MusicManager.IsInitialised()
		&& MusicManager.GetMusicMode() == MUSICMODE_CUTSCENE
		&& nBank != SAMPLEBANK_MAIN )
	{
		return false;
	}
	
	if ( fseek(fpSampleDataHandle, nSampleBankDiscStartOffset[nBank], SEEK_SET) != 0 )
		return false;
	
	if ( fread((void *)nSampleBankMemoryStartAddress[nBank], 1, nSampleBankSize[nBank], fpSampleDataHandle) != nSampleBankSize[nBank] )
		return false;
	
	bSampleBankLoaded[nBank] = true;
	
	return true;
}

void
cSampleManager::UnloadSampleBank(uint8 nBank)
{
	ASSERT( nBank < MAX_SAMPLEBANKS );
	
	; // NOIMP
}

bool
cSampleManager::IsSampleBankLoaded(uint8 nBank)
{
	ASSERT( nBank < MAX_SAMPLEBANKS );
	return true;
}

bool
cSampleManager::IsPedCommentLoaded(uint32 nComment)
{
	ASSERT( nComment < TOTAL_AUDIO_SAMPLES );
	
	uint8 slot;

	for ( int32 i = 0; i < _TODOCONST(3); i++ )
	{
		slot = nCurrentPedSlot - i - 1;
		if ( nComment == nPedSlotSfx[slot] )
			return true;
	}
	
	return false;
}


int32
cSampleManager::_GetPedCommentSlot(uint32 nComment)
{
	uint8 slot;

	for (int32 i = 0; i < _TODOCONST(3); i++)
	{
		slot = nCurrentPedSlot - i - 1;
		if (nComment == nPedSlotSfx[slot])
			return slot;
	}

	return -1;
}

bool
cSampleManager::LoadPedComment(uint32 nComment)
{
	ASSERT( nComment < TOTAL_AUDIO_SAMPLES );
	
	if ( CTimer::GetIsCodePaused() )
		return false;
	
	// no talking peds during cutsenes or the game end
	if ( MusicManager.IsInitialised() )
	{
		switch ( MusicManager.GetMusicMode() )
		{
			case MUSICMODE_CUTSCENE:
			{
				return false;

				break;
			}
			
			case MUSICMODE_FRONTEND:
			{
				if ( MusicManager.GetCurrentTrack() == STREAMED_SOUND_GAME_COMPLETED )
					return false;

				break;
			}
		}
	}
	
	if ( fseek(fpSampleDataHandle, m_aSamples[nComment].nOffset, SEEK_SET) != 0 )
		return false;
	
	if ( fread((void *)(nSampleBankMemoryStartAddress[SAMPLEBANK_PED] + PED_BLOCKSIZE*nCurrentPedSlot), 1, m_aSamples[nComment].nSize, fpSampleDataHandle) != m_aSamples[nComment].nSize )
		return false;
	
	nPedSlotSfx[nCurrentPedSlot] = nComment;
	
	alBufferData(pedBuffers[nCurrentPedSlot],
		AL_FORMAT_MONO16,
		(void *)(nSampleBankMemoryStartAddress[SAMPLEBANK_PED] + PED_BLOCKSIZE*nCurrentPedSlot),
		m_aSamples[nComment].nSize,
		MAX_FREQ);
	
	if ( ++nCurrentPedSlot >= MAX_PEDSFX )
		nCurrentPedSlot = 0;
	
	return true;
}

int32
cSampleManager::GetBankContainingSound(uint32 offset)
{
	if ( offset >= BankStartOffset[SAMPLEBANK_PED] )
		return SAMPLEBANK_PED;
	
	if ( offset >= BankStartOffset[SAMPLEBANK_MAIN] )
		return SAMPLEBANK_MAIN;
	
	return SAMPLEBANK_INVALID;
}

int32
cSampleManager::GetSampleBaseFrequency(uint32 nSample)
{
	ASSERT( nSample < TOTAL_AUDIO_SAMPLES );
	return m_aSamples[nSample].nFrequency;
}

int32
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
	return m_aSamples[nSample].nSize >> 1;
}

bool cSampleManager::UpdateReverb(void)
{
	return false;
}

void
cSampleManager::SetChannelReverbFlag(uint32 nChannel, uint8 nReverbFlag)
{
	; // NOIMP
}

bool
cSampleManager::InitialiseChannel(uint32 nChannel, uint32 nSfx, uint8 nBank)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	ALuint buffer;
	
	if ( nSfx < SAMPLEBANK_MAX )
	{
		int32 offset = (m_aSamples[nSfx].nLoopStart > 0) ? (m_aSamples[nSfx].nOffset  - m_aSamples[nSfx].nLoopStart) : m_aSamples[nSfx].nOffset;
		int32 size   = (m_aSamples[nSfx].nLoopStart > 0) ? (m_aSamples[nSfx].nLoopEnd - m_aSamples[nSfx].nLoopStart) : m_aSamples[nSfx].nSize;
		
		void *data = malloc(size);
		ASSERT(data != NULL);
		
		if ( fseek(fpSampleDataHandle, offset + nSampleBankDiscStartOffset[nBank], SEEK_SET) != 0 )
		{
			free(data);
			return false;
		}
		
		if ( fread(data, 1, size, fpSampleDataHandle) != size )
		{	
			free(data);
			return false;
		}
		
		ALuint buf;
		alGenBuffers(1, &buf);
		alBufferData(buf, AL_FORMAT_MONO16, data, size, MAX_FREQ);
		free(data);
		
		if ( !IsSampleBankLoaded(nBank) )
			return false;
		
		ALBuffers[nSfx].buffer = buf;
		ALBuffers[nSfx].timer  = 120000;
		
		buffer = ALBuffers[nSfx].buffer;
		
		ChannelSample[nChannel] = nSfx;
	}
	else
	{
		if ( !IsPedCommentLoaded(nSfx) )
			return false;
		
		int32 slot = _GetPedCommentSlot(nSfx);
		
		buffer = pedBuffers[slot];
	}
	
	if ( buffer == 0 )
	{
		TRACE("No buffer to play id %d", nSfx);
		return false;
	}
	
	if ( GetChannelUsedFlag(nChannel) )
	{
		TRACE("Stopping channel %d - really!!!", nChannel);
		StopChannel(nChannel);
	}
	
	alSourcei(alChannel[nChannel], AL_BUFFER, 0);
	currentChannelVolume          [nChannel] = -1;
	currentChannelFrequency       [nChannel] = -1;
	currentChannelMaxFrontDistance[nChannel] = -1;
	
	if ( alChannel[nChannel] )
	{
		alSourcei(alChannel[nChannel], AL_BUFFER, buffer);
		alSourcef(alChannel[nChannel], AL_PITCH,  1.0f);
		ChannelPitch[nChannel] = 1.0f;
		return true;
	}
	
	return false;
}

void
cSampleManager::SetChannelEmittingVolume(uint32 nChannel, uint32 nVolume)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	uint32 vol = nVolume;
	if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
	
	nChannelVolume[nChannel] = vol;
	
	// reduce the volume for JB.MP3 and S4_BDBD.MP3
	if (   MusicManager.GetMusicMode()    == MUSICMODE_CUTSCENE
		&& MusicManager.GetCurrentTrack() != STREAMED_SOUND_NEWS_INTRO
		&& MusicManager.GetCurrentTrack() != STREAMED_SOUND_CUTSCENE_SAL4_BDBD )
	{
		nChannelVolume[nChannel] >>= 2;
	}

	uint32 channelVol = m_nEffectsFadeVolume*nChannelVolume[nChannel]*m_nEffectsVolume >> 14;
	if ( ChannelSample[nChannel] >= SFX_CAR_REV_1 && SFX_CAR_REV_10 >= ChannelSample[nChannel] ) // nice hack
		channelVol >>= 1;
	
	if ( alChannel[nChannel] )
	{
		if ( currentChannelVolume[nChannel] != channelVol )
		{
			ALfloat gain = ALfloat(channelVol) / MAX_VOLUME;
			alSourcef(alChannel[nChannel], AL_GAIN, gain);
			currentChannelVolume[nChannel] = channelVol;
		}
	}
}

void
cSampleManager::SetChannel3DPosition(uint32 nChannel, float fX, float fY, float fZ)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( alChannel[nChannel] )
	{
		alSource3f(alChannel[nChannel], AL_POSITION, -fX, fY, fZ);
	}
}

void
cSampleManager::SetChannel3DDistances(uint32 nChannel, float fMax, float fMin)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( alChannel[nChannel] )
	{
		if ( float(currentChannelMaxFrontDistance[nChannel]) != fMax )
		{
			alSourcef(alChannel[nChannel], AL_MAX_DISTANCE,       fMax);
			alSourcef(alChannel[nChannel], AL_REFERENCE_DISTANCE, 5.0f);
			alSourcef(alChannel[nChannel], AL_MAX_GAIN,           1.0f);
			currentChannelMaxFrontDistance[nChannel] = int32(fMax);
		}
	}
}

void
cSampleManager::SetChannelVolume(uint32 nChannel, uint32 nVolume)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( nChannel == CHANNEL2D )
	{
		uint32 vol = nVolume;
		if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
		
		nChannelVolume[nChannel] = vol;
		
		// increase the volume for JB.MP3 and S4_BDBD.MP3
		if (   MusicManager.GetMusicMode()    == MUSICMODE_CUTSCENE
			&& MusicManager.GetCurrentTrack() != STREAMED_SOUND_NEWS_INTRO
			&& MusicManager.GetCurrentTrack() != STREAMED_SOUND_CUTSCENE_SAL4_BDBD )
		{
			nChannelVolume[nChannel] >>= 2;
		}
		
		uint32 channelVol = m_nEffectsFadeVolume*nChannelVolume[nChannel]*m_nEffectsVolume >> 14;
		if ( ChannelSample[nChannel] >= SFX_CAR_REV_1 && SFX_CAR_IDLE_10 >= ChannelSample[nChannel] ) // nice hack
			channelVol >>= 1;
	
		if ( alChannel[nChannel] )
		{
			if ( currentChannelVolume[nChannel] != channelVol )
			{
				ALfloat gain = ALfloat(channelVol) / MAX_VOLUME;
				alSourcef(alChannel[nChannel], AL_GAIN, gain);
				currentChannelVolume[nChannel] = channelVol;
			}
		}
	}
}

void
cSampleManager::SetChannelPan(uint32 nChannel, uint32 nPan)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	; // NOIMP
}

void
cSampleManager::SetChannelFrequency(uint32 nChannel, uint32 nFreq)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( alChannel[nChannel] )
	{
		if ( currentChannelFrequency[nChannel] != nFreq )
		{
			ALfloat pitch = ALfloat(nFreq) / MAX_FREQ;
			alSourcef(alChannel[nChannel], AL_PITCH, pitch);
			currentChannelFrequency[nChannel] = nFreq;
			
			if ( Abs(1.0f - pitch) < 0.01f )
				ChannelPitch[nChannel] = 1.0f;
			else
				ChannelPitch[nChannel] = pitch;
		}
	}
}

void
cSampleManager::SetChannelLoopPoints(uint32 nChannel, uint32 nLoopStart, int32 nLoopEnd)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	; // NOIMP
}

void
cSampleManager::SetChannelLoopCount(uint32 nChannel, uint32 nLoopCount)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( nLoopCount != 0 )
		alSourcei(alChannel[nChannel], AL_LOOPING, AL_FALSE);
	else
		alSourcei(alChannel[nChannel], AL_LOOPING, AL_TRUE);
}

bool
cSampleManager::GetChannelUsedFlag(uint32 nChannel)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( alChannel[nChannel] )
	{
		ALint sourceState;
		alGetSourcei(alChannel[nChannel], AL_SOURCE_STATE, &sourceState);
		return sourceState == AL_PLAYING;
	}
	
	return false;
}

void
cSampleManager::StartChannel(uint32 nChannel)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( alChannel[nChannel] )
	{
		if ( ChannelSample[nChannel] > SAMPLEBANK_END ) // PED's Bank
		{
			if ( ChannelPitch[nChannel] != 1.0f )
				ChannelPitch[nChannel] = 1.0f;
		}

		alSourcef   (alChannel[nChannel], AL_PITCH, ChannelPitch[nChannel]);
		alSourcePlay(alChannel[nChannel]);
	}
}

void
cSampleManager::StopChannel(uint32 nChannel)
{
	ASSERT( nChannel < MAXCHANNELS+MAX2DCHANNELS );
	
	if ( alChannel[nChannel] )
	{
		alSourceStop(alChannel[nChannel]);
		
		currentChannelVolume          [nChannel] = -1;
		currentChannelFrequency       [nChannel] = -1;
		currentChannelMaxFrontDistance[nChannel] = -1;
		ChannelPitch                  [nChannel] = 1.0f;
	}
}

void
cSampleManager::PreloadStreamedFile(uint8 nFile, uint8 nStream)
{
	char filename[256];
	
	ASSERT( nStream < MAX_STREAMS );

	if ( nFile < TOTAL_STREAMED_SOUNDS )
	{
		if ( mp3Stream[nStream] )
		{
			delete mp3Stream[nStream];
			mp3Stream[nStream] = NULL;
		}
		
		strcpy(filename, StreamedNameTable[nFile]);
		
		MP3Stream *stream = new MP3Stream(filename, ALStreamSources[nStream], ALStreamBuffers[nStream]);
		ASSERT(stream != NULL);
		
		mp3Stream[nStream] = stream;
		
		if ( stream->m_bIsOpened )
		{
			;
		}
		else
		{
			delete stream;
			mp3Stream[nStream] = NULL;
		}
	}
}

void
cSampleManager::PauseStream(uint8 nPauseFlag, uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	MP3Stream *stream = mp3Stream[nStream];
	
	if ( stream )
	{
		if ( nPauseFlag != 0 )
		{
			if ( !stream->m_bIsPaused )
			{
				alSourcePause(stream->m_alSource);
				stream->m_bIsPaused = true;
			}
		}
		else
		{
			if ( stream->m_bIsPaused )
			{
				alSourcef(stream->m_alSource, AL_PITCH, 1.0f);
				alSourcePlay(stream->m_alSource);
				stream->m_bIsPaused = false;
			}
		}
	}
}

void
cSampleManager::StartPreloadedStreamedFile(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	MP3Stream *stream = mp3Stream[nStream];
	
	if ( stream )
	{
		stream->Initialize();
		if ( stream->m_bIsOpened )
		{
			//NOTE: set pos here on mobile
			
			if ( stream->FillBuffers() != 0 )
			{
				alSourcef(stream->m_alSource, AL_PITCH, 1.0f);
				alSourcePlay(stream->m_alSource);
				stream->m_bIsFree = false;
			}
		}
	}
}

bool
cSampleManager::StartStreamedFile(uint8 nFile, uint32 nPos, uint8 nStream)
{
	char filename[256];
	
	ASSERT( nStream < MAX_STREAMS );
	
	if ( nFile < TOTAL_STREAMED_SOUNDS )
	{
		if ( mp3Stream[nStream] )
		{
			delete mp3Stream[nStream];
			mp3Stream[nStream] = NULL;
		}
		
		strcpy(filename, StreamedNameTable[nFile]);
		
		MP3Stream *stream = new MP3Stream(filename, ALStreamSources[nStream], ALStreamBuffers[nStream]);
		ASSERT(stream != NULL);
		
		mp3Stream[nStream] = stream;
		
		if ( stream->m_bIsOpened )
		{
			stream->Initialize();
			nStreamLength[nFile] = stream->m_nLength;
			//MusicManager.SetTrackInfoLength(nFile, stream->m_nLength);
			
			if ( stream->m_bIsOpened )
			{
				if ( nPos != 0 )
				{
					stream->SetPos(nPos);
				}
				
				if ( stream->FillBuffers() != 0 )
				{
					alSourcef(stream->m_alSource, AL_PITCH, 1.0f);
					alSourcePlay(stream->m_alSource);
					stream->m_bIsFree = false;
				}
			}
			
			return true;
		}
		else
		{
			delete stream;
			mp3Stream[nStream] = NULL;
		}
	}
	
	return false;
}

void
cSampleManager::StopStreamedFile(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );

	MP3Stream *stream = mp3Stream[nStream];
	
	if ( stream )
	{
		delete stream;
		mp3Stream[nStream] = NULL;
	}
}

int32
cSampleManager::GetStreamedFilePosition(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	MP3Stream *stream = mp3Stream[nStream];
	
	if ( stream )
	{
		return (ftell(stream->m_fpFile) * 8) / stream->m_nBitRate;
	}
	
	return 0;
}

void
cSampleManager::SetStreamedVolumeAndPan(uint8 nVolume, uint8 nPan, uint8 nEffectFlag, uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	if ( nVolume > MAX_VOLUME )
		nVolume = MAX_VOLUME;
	
	if ( nPan > MAX_VOLUME )
		nPan = MAX_VOLUME;
		
	nStreamVolume[nStream] = m_nMusicFadeVolume * nVolume;
	nStreamPan   [nStream] = nPan;
	
	MP3Stream *stream = mp3Stream[nStream];
	
	if ( stream )
	{
		uint32 vol;
		if ( nEffectFlag )
			vol = m_nEffectsFadeVolume*nVolume*m_nEffectsVolume >> 14;
		else
			vol = m_nMusicFadeVolume*nVolume*m_nMusicVolume >> 14;
		
		if ( stream->m_nVolume != vol )
		{
			if ( stream->m_bIsOpened )
			{
				ALuint source = stream->m_alSource;
				if ( source )
				{
					ALfloat gain = ALfloat(vol) / MAX_VOLUME;
					alSourcef(source, AL_GAIN, gain);
					stream = mp3Stream[nStream];
				}
			}
			
			stream->m_nVolume = vol;
		}
	}
}

int32
cSampleManager::GetStreamedFileLength(uint8 nStream)
{
	ASSERT( nStream < TOTAL_STREAMED_SOUNDS );

	return nStreamLength[nStream];
}

bool
cSampleManager::IsStreamPlaying(uint8 nStream)
{
	ASSERT( nStream < MAX_STREAMS );
	
	MP3Stream *stream = mp3Stream[nStream];
	
	if ( stream && stream->m_bIsOpened && !stream->m_bIsPaused )
	{
		ALint sourceState;
		alGetSourcei(stream->m_alSource, AL_SOURCE_STATE, &sourceState);
		if ( !stream->m_bIsFree || sourceState == AL_PLAYING )
			return true;
	}
	
	return false;
}

void
cSampleManager::Service(void)
{	
	for ( int32 i = 0; i < MAX_STREAMS; i++ )
	{
		if ( mp3Stream[i] )
			mp3Stream[i]->Update();
	}
	
	UpdateSoundBuffers();
}

bool
cSampleManager::InitialiseSampleBanks(void)
{
	int32 nBank = SAMPLEBANK_MAIN;
	
	fpSampleDescHandle = fopen(SampleBankDescFilename, "rb");
	if ( fpSampleDescHandle == NULL )
		return false;
	
	fpSampleDataHandle = fopen(SampleBankDataFilename, "rb");
	if ( fpSampleDataHandle == NULL )
	{
		fclose(fpSampleDescHandle);
		fpSampleDescHandle = NULL;
		
		return false;
	}
	
	fseek(fpSampleDataHandle, 0, SEEK_END);
	int32 _nSampleDataEndOffset = ftell(fpSampleDataHandle);
	rewind(fpSampleDataHandle);
	
	fread(m_aSamples, sizeof(tSample), TOTAL_AUDIO_SAMPLES, fpSampleDescHandle);
	
	fclose(fpSampleDescHandle);
	fpSampleDescHandle = NULL;
	
	for ( int32 i = 0; i < TOTAL_AUDIO_SAMPLES; i++ )
	{
		if ( BankStartOffset[nBank] == BankStartOffset[SAMPLEBANK_MAIN] + i )
		{
			nSampleBankDiscStartOffset[nBank] = m_aSamples[i].nOffset;
			nBank++;
		}
	}

	nSampleBankSize[SAMPLEBANK_MAIN] = nSampleBankDiscStartOffset[SAMPLEBANK_PED] - nSampleBankDiscStartOffset[SAMPLEBANK_MAIN];
	nSampleBankSize[SAMPLEBANK_PED]  = _nSampleDataEndOffset                      - nSampleBankDiscStartOffset[SAMPLEBANK_PED];
	
	return true;
}

/*
sub_1D8D40
PreloadSoundBank(tSample *,uchar)
CheckOpenALChannels(void)
*/

void MP3Stream::Initialize(void)
{
	if ( !m_bIsOpened )
		return;
	
	mpg123_format_none(m_pMPG);
	
	mpg123_format(m_pMPG, 11000, MPG123_MONO|MPG123_STEREO, MPG123_ENC_SIGNED_16);
	mpg123_format(m_pMPG, 24000, MPG123_MONO|MPG123_STEREO, MPG123_ENC_SIGNED_16);
	mpg123_format(m_pMPG, 32000, MPG123_MONO|MPG123_STEREO, MPG123_ENC_SIGNED_16);
	mpg123_format(m_pMPG, 44100, MPG123_MONO|MPG123_STEREO, MPG123_ENC_SIGNED_16);
	
	if ( mpg123_open_feed(m_pMPG) != MPG123_OK )
		return;
	
	const uint32 CHUNK_SIZE = 1024*5;
	
	if ( fread(m_pBuf, 1, CHUNK_SIZE, m_fpFile) != CHUNK_SIZE )
	{
		Delete();
		return;
	}
	
	m_nBufSize -= CHUNK_SIZE;
	
	mpg123_feed(m_pMPG, m_pBuf, CHUNK_SIZE);
	
	if ( mpg123_getformat(m_pMPG, &m_nRate, &m_nChannels, &m_nEncoding) != MPG123_OK )
	{
		Delete();
		return;
	}
	
	mpg123_frameinfo info;
	if ( mpg123_info(m_pMPG, &info) != MPG123_OK )
	{
		Delete();
		return;
	}
	
	m_nBitRate = info.bitrate;
	m_nLength = 8 * m_nLengthInBytes / info.bitrate;
	m_nBlockSize = mpg123_outblock(m_pMPG);
	m_nNumBlocks = 5;
	m_pBlocks = (unsigned char *)malloc(m_nNumBlocks * m_nBlockSize);
}

bool MP3Stream::FillBuffer(ALuint alBuffer)
{
	size_t done;
	
	uint8 *pBlockBuff = (uint8 *)m_pBlocks;
	
	bool fail = !(m_nBufSize > 1); 
	
	int err = mpg123_read(m_pMPG, m_pBlocks, m_nBlockSize, &done);
	if ( alBuffer == 0 )
	{
		if ( err == MPG123_OK )
		{
			while ( mpg123_read(m_pMPG, pBlockBuff, m_nBlockSize, &done) == MPG123_OK )
				;
		}
		
		return true;
	}
	
	int32 blocks = 0;
	for ( blocks = 0; blocks < m_nNumBlocks; blocks++ )
	{
		if ( err == MPG123_NEED_MORE )
		{
			if ( fail )
				break;
			
			size_t readSize = m_nBufSize;
			if ( readSize > 0x4000 )
			{
				if ( fread(m_pBuf, 1, 0x4000, m_fpFile) != 0x4000 )
				{
					fail = true;
					TRACE("MP3 ************* : MP3 read unsuccessful mid file, stopping queuing");
					break;
				}
				
				m_nBufSize -= 0x4000;
				mpg123_feed(m_pMPG, m_pBuf, 0x4000);
			}
			else
			{
				if ( fread(m_pBuf, 1, readSize, m_fpFile) != readSize )
				{
					fail = true;
					break;
				}
				
				m_nBufSize -= readSize;
				mpg123_feed(m_pMPG, m_pBuf, readSize);
			}
		}
		else if ( err == MPG123_OK )
		{
			pBlockBuff += m_nBlockSize;
		}
		else
		{
			fail = true;
			break;
		}
		
		err = mpg123_read(m_pMPG, pBlockBuff, m_nBlockSize, &done);
	}
	
	if ( blocks != 0 )
	{
		if ( m_nChannels == 1 )
			alBufferData(alBuffer, AL_FORMAT_MONO16,   m_pBlocks, m_nBlockSize*blocks, m_nRate);
		else
			alBufferData(alBuffer, AL_FORMAT_STEREO16, m_pBlocks, m_nBlockSize*blocks, m_nRate);
	}
	
	if ( fail && blocks < m_nNumBlocks )
		m_bIsFree = true;
	
	return blocks != 0;
}

void MP3Stream::Update(void)
{
	if ( !m_bIsOpened )
		return;
	
	if ( m_bIsFree )
		return;
	
	if ( !m_bIsPaused )
	{
		ALint sourceState;
		ALint buffersProcessed = 0;
		
		alGetSourcei(m_alSource, AL_SOURCE_STATE, &sourceState);
		alGetSourcei(m_alSource, AL_BUFFERS_PROCESSED, &buffersProcessed);
		
		ALint looping = AL_FALSE;
		alGetSourcei(m_alSource, AL_LOOPING, &looping);
		
		if ( looping == AL_TRUE )
		{
			TRACE("stream set looping");
			alSourcei(m_alSource, AL_LOOPING, AL_TRUE);
		}
		
		while( buffersProcessed-- )
		{
			ALuint buffer;
			
			alSourceUnqueueBuffers(m_alSource, 1, &buffer);
			
			if ( !m_bIsFree && FillBuffer(buffer) )
				alSourceQueueBuffers(m_alSource, 1, &buffer);
		}
		
		if ( sourceState != AL_PLAYING )
		{
			alSourcef(m_alSource, AL_PITCH, 1.0f);
			alSourcePlay(m_alSource);
		}
	}
}

void MP3Stream::SetPos(uint32 nPos)
{
	uint32 pos = nPos;
	if ( nPos > m_nLength )
		pos %= m_nLength;
	
	uint32 blockPos = m_nBitRate * pos / 8;
	if ( blockPos > m_nLengthInBytes )
		blockPos %= m_nLengthInBytes;
	
	fseek(m_fpFile, blockPos, SEEK_SET);

	size_t done;
	while ( mpg123_read(m_pMPG, m_pBlocks, m_nBlockSize, &done) == MPG123_OK )
		;
}

int32 MP3Stream::FillBuffers()
{
	int32 i = 0;
	for ( i = 0; i < ARRAY_SIZE(m_alBuffers); i++ )
	{
		if ( !FillBuffer(m_alBuffers[i]) )
			break;
		alSourceQueueBuffers(m_alSource, 1, &m_alBuffers[i]);
	}
	
	return i;
}

MP3Stream::MP3Stream(char *filename, ALuint source, ALuint *buffers)
{
	strcpy(m_aFilename, filename);
	memset(m_alBuffers, 0, sizeof(m_alBuffers));
	m_alSource = source;
	memcpy(m_alBuffers, buffers, sizeof(m_alBuffers));
	m_nVolume    = -1;
	m_pBlocks    = NULL;
	m_pBuf       = NULL;
	m_pMPG       = NULL;
	m_bIsPaused  = false;
	m_bIsOpened  = true;
	m_bIsFree    = true;
	m_fpFile     = fopen(m_aFilename, "rb");
	
	if ( m_fpFile )
	{
		m_nBufSize = filelength(fileno(m_fpFile));
		m_nLengthInBytes = m_nBufSize;
		m_pMPG = mpg123_new(NULL, NULL);
		m_pBuf = (unsigned char *)malloc(0x4000);
	}
	else
	{
		m_bIsOpened = false;
		Delete();
	}
}

void MP3Stream::Delete()
{
	if ( m_pMPG )
	{
		mpg123_delete(m_pMPG);
		m_pMPG = NULL;
	}
	
	if ( m_fpFile )
	{
		fclose(m_fpFile);
		m_fpFile = NULL;
	}
	
	if ( m_alSource )
	{
		ALint sourceState = AL_STOPPED;
		alGetSourcei(m_alSource, AL_SOURCE_STATE, &sourceState);
		if (sourceState != AL_STOPPED )
			alSourceStop(m_alSource);
		
		ALint buffersQueued;
		alGetSourcei(m_alSource, AL_BUFFERS_QUEUED, &buffersQueued);

		ALuint value;
		while (buffersQueued--)
			alSourceUnqueueBuffers(m_alSource, 1, &value);
		
		m_alSource = 0;
	}
	
	if ( m_pBlocks )
	{
		free(m_pBlocks);
		m_pBlocks = NULL;
	}
	
	if ( m_pBuf )
	{
		free(m_pBuf);
		m_pBuf = NULL;
	}
	
	m_bIsOpened = false;
}