#include "common.h"

#ifdef AUDIO_OAL
#include "stream.h"
#include "sampman.h"

#ifdef AUDIO_OPUS
#include <opusfile.h>
#else
#ifdef _WIN32
#pragma comment( lib, "libsndfile-1.lib" )
#pragma comment( lib, "libmpg123-0.lib" )
#endif
#include <sndfile.h>
#include <mpg123.h>
#endif

#ifndef _WIN32
#include "crossplatform.h"
#endif

/*
As we ran onto an issue of having different volume levels for mono streams
and stereo streams we are now handling all the stereo panning ourselves.
Each stream now has two sources - one panned to the left and one to the right,
and uses two separate buffers to store data for each individual channel.
For that we also have to reshuffle all decoded PCM stereo data from LRLRLRLR to
LLLLRRRR (handled by CSortStereoBuffer).
*/

class CSortStereoBuffer
{
	uint16* PcmBuf;
	size_t BufSize;
public:
	CSortStereoBuffer() : PcmBuf(nil), BufSize(0) {}
	~CSortStereoBuffer()
	{
		if (PcmBuf)
			free(PcmBuf);
	}

	uint16* GetBuffer(size_t size)
	{
		if (size == 0) return nil;
		if (!PcmBuf)
		{
			BufSize = size;
			PcmBuf = (uint16*)malloc(BufSize);
		}
		else if (BufSize < size)
		{
			BufSize = size;
			PcmBuf = (uint16*)realloc(PcmBuf, size);
		}
		return PcmBuf;
	}

	void SortStereo(void* buf, size_t size)
	{
		uint16* InBuf = (uint16*)buf;
		uint16* OutBuf = GetBuffer(size);

		if (!OutBuf) return;

		size_t rightStart = size / 4;
		for (size_t i = 0; i < size / 4; i++)
		{
			OutBuf[i] = InBuf[i*2];
			OutBuf[i+rightStart] = InBuf[i*2+1];
		}

		memcpy(InBuf, OutBuf, size);
	}

};

CSortStereoBuffer SortStereoBuffer;

#ifndef AUDIO_OPUS
class CSndFile : public IDecoder
{
	SNDFILE *m_pfSound;
	SF_INFO m_soundInfo;
public:
	CSndFile(const char *path) :
		m_pfSound(nil)
	{
		memset(&m_soundInfo, 0, sizeof(m_soundInfo));
		m_pfSound = sf_open(path, SFM_READ, &m_soundInfo);
	}
	
	~CSndFile()
	{
		if ( m_pfSound )
		{
			sf_close(m_pfSound);
			m_pfSound = nil;
		}
	}
	
	bool IsOpened()
	{
		return m_pfSound != nil;
	}
	
	uint32 GetSampleSize()
	{
		return sizeof(uint16);
	}
	
	uint32 GetSampleCount()
	{
		return m_soundInfo.frames;
	}
	
	uint32 GetSampleRate()
	{
		return m_soundInfo.samplerate;
	}
	
	uint32 GetChannels()
	{
		return m_soundInfo.channels;
	}
	
	void Seek(uint32 milliseconds)
	{
		if ( !IsOpened() ) return;
		sf_seek(m_pfSound, ms2samples(milliseconds), SF_SEEK_SET);
	}
	
	uint32 Tell()
	{
		if ( !IsOpened() ) return 0;
		return samples2ms(sf_seek(m_pfSound, 0, SF_SEEK_CUR));
	}
	
	uint32 Decode(void *buffer)
	{
		if ( !IsOpened() ) return 0;

		size_t size = sf_read_short(m_pfSound, (short*)buffer, GetBufferSamples()) * GetSampleSize();
		if (GetChannels()==2)
			SortStereoBuffer.SortStereo(buffer, size);
		return size;
	}
};

class CMP3File : public IDecoder
{
	mpg123_handle *m_pMH;
	bool m_bOpened;
	uint32 m_nRate;
	uint32 m_nChannels;
public:
	CMP3File(const char *path) :
		m_pMH(nil),
		m_bOpened(false),
		m_nRate(0),
		m_nChannels(0)
	{
		m_pMH = mpg123_new(nil, nil);
		if ( m_pMH )
		{
			mpg123_param(m_pMH, MPG123_FLAGS, MPG123_FUZZY | MPG123_SEEKBUFFER | MPG123_GAPLESS, 0.0);

			long rate = 0;
			int channels = 0;
			int encoding = 0;
			
			m_bOpened = mpg123_open(m_pMH, path) == MPG123_OK
				&& mpg123_getformat(m_pMH, &rate, &channels, &encoding) == MPG123_OK;
			m_nRate = rate;
			m_nChannels = channels;
			
			if ( IsOpened() )
			{
				mpg123_format_none(m_pMH);
				mpg123_format(m_pMH, rate, channels, encoding);
			}
		}
	}
	
	~CMP3File()
	{
		if ( m_pMH )
		{
			mpg123_close(m_pMH);
			mpg123_delete(m_pMH);
			m_pMH = nil;
		}
	}
	
	bool IsOpened()
	{
		return m_bOpened;
	}
	
	uint32 GetSampleSize()
	{
		return sizeof(uint16);
	}
	
	uint32 GetSampleCount()
	{
		if ( !IsOpened() ) return 0;
		return mpg123_length(m_pMH);
	}
	
	uint32 GetSampleRate()
	{
		return m_nRate;
	}
	
	uint32 GetChannels()
	{
		return m_nChannels;
	}
	
	void Seek(uint32 milliseconds)
	{
		if ( !IsOpened() ) return;
		mpg123_seek(m_pMH, ms2samples(milliseconds), SEEK_SET);
	}
	
	uint32 Tell()
	{
		if ( !IsOpened() ) return 0;
		return samples2ms(mpg123_tell(m_pMH));
	}
	
	uint32 Decode(void *buffer)
	{
		if ( !IsOpened() ) return 0;
		
		size_t size;
		int err = mpg123_read(m_pMH, (unsigned char *)buffer, GetBufferSize(), &size);
#if defined(__LP64__) || defined(_WIN64)
		assert("We can't handle audio files more then 2 GB yet :shrug:" && (size < UINT32_MAX));
#endif
		if (err != MPG123_OK && err != MPG123_DONE) return 0;
		if (GetChannels() == 2)
			SortStereoBuffer.SortStereo(buffer, size);
		return (uint32)size;
	}
};
#else
class COpusFile : public IDecoder
{
	OggOpusFile *m_FileH;
	bool m_bOpened;
	uint32 m_nRate;
	uint32 m_nChannels;
public:
	COpusFile(const char *path) : m_FileH(nil),
		m_bOpened(false),
		m_nRate(0),
		m_nChannels(0)
	{
		int ret;
		m_FileH = op_open_file(path, &ret);

		if (m_FileH) {
			m_nChannels = op_head(m_FileH, 0)->channel_count;
			m_nRate = 48000;
			const OpusTags *tags = op_tags(m_FileH, 0);
			for (int i = 0; i < tags->comments; i++) {
				if (strncmp(tags->user_comments[i], "SAMPLERATE", sizeof("SAMPLERATE")-1) == 0)
				{
					sscanf(tags->user_comments[i], "SAMPLERATE=%i", &m_nRate);
					break;
				}
			}
			
			m_bOpened = true;
		}
	}
	
	~COpusFile()
	{
		if (m_FileH)
		{
			op_free(m_FileH);
			m_FileH = nil;
		}
	}
	
	bool IsOpened()
	{
		return m_bOpened;
	}
	
	uint32 GetSampleSize()
	{
		return sizeof(uint16);
	}
	
	uint32 GetSampleCount()
	{
		if ( !IsOpened() ) return 0;
		return op_pcm_total(m_FileH, 0);
	}
	
	uint32 GetSampleRate()
	{
		return m_nRate;
	}
	
	uint32 GetChannels()
	{
		return m_nChannels;
	}
	
	void Seek(uint32 milliseconds)
	{
		if ( !IsOpened() ) return;
		op_pcm_seek(m_FileH, ms2samples(milliseconds) / GetChannels());
	}
	
	uint32 Tell()
	{
		if ( !IsOpened() ) return 0;
		return samples2ms(op_pcm_tell(m_FileH) * GetChannels());
	}
	
	uint32 Decode(void *buffer)
	{
		if ( !IsOpened() ) return 0;

		int size = op_read(m_FileH, (opus_int16 *)buffer, GetBufferSamples(), NULL);

		if (size < 0)
			return 0;

		if (GetChannels() == 2)
			SortStereoBuffer.SortStereo(buffer, size * m_nChannels * GetSampleSize());

		return size * m_nChannels * GetSampleSize();
	}
};
#endif

void CStream::Initialise()
{
#ifndef AUDIO_OPUS
	mpg123_init();
#endif
}

void CStream::Terminate()
{
#ifndef AUDIO_OPUS
	mpg123_exit();
#endif
}

CStream::CStream(char *filename, ALuint *sources, ALuint (&buffers)[NUM_STREAMBUFFERS]) :
	m_pAlSources(sources),
	m_alBuffers(buffers),
	m_pBuffer(nil),
	m_bPaused(false),
	m_bActive(false),
	m_pSoundFile(nil),
	m_bReset(false),
	m_nVolume(0),
	m_nPan(0),
	m_nPosBeforeReset(0)
	
{
// Be case-insensitive on linux (from https://github.com/OneSadCookie/fcaseopen/)
#if !defined(_WIN32)
	char *real = casepath(filename);
	if (real) {
		strcpy(m_aFilename, real);
		free(real);
	} else {
#else
	{
#endif
		strcpy(m_aFilename, filename);
	}
		
	DEV("Stream %s\n", m_aFilename);

#ifndef AUDIO_OPUS
	if (!strcasecmp(&m_aFilename[strlen(m_aFilename) - strlen(".mp3")], ".mp3"))
		m_pSoundFile = new CMP3File(m_aFilename);
	else if (!strcasecmp(&m_aFilename[strlen(m_aFilename) - strlen(".wav")], ".wav"))
		m_pSoundFile = new CSndFile(m_aFilename);
#else
	if (!strcasecmp(&m_aFilename[strlen(m_aFilename) - strlen(".opus")], ".opus"))
		m_pSoundFile = new COpusFile(m_aFilename);
#endif
	else 
		m_pSoundFile = nil;

	if ( IsOpened() )
	{
		m_pBuffer            = malloc(m_pSoundFile->GetBufferSize());
		ASSERT(m_pBuffer!=nil);
		
		DEV("AvgSamplesPerSec: %d\n", m_pSoundFile->GetAvgSamplesPerSec());
		DEV("SampleCount: %d\n",      m_pSoundFile->GetSampleCount());
		DEV("SampleRate: %d\n",       m_pSoundFile->GetSampleRate());
		DEV("Channels: %d\n",         m_pSoundFile->GetChannels());
		DEV("Buffer Samples: %d\n",   m_pSoundFile->GetBufferSamples());
		DEV("Buffer sec: %f\n",       (float(m_pSoundFile->GetBufferSamples()) / float(m_pSoundFile->GetChannels())/ float(m_pSoundFile->GetSampleRate())));
		DEV("Length MS: %02d:%02d\n", (m_pSoundFile->GetLength() / 1000) / 60, (m_pSoundFile->GetLength() / 1000) % 60);
		
		return;
	}
}

CStream::~CStream()
{
	Delete();
}

void CStream::Delete()
{
	Stop();
	ClearBuffers();
	
	if ( m_pSoundFile )
	{
		delete m_pSoundFile;
		m_pSoundFile = nil;
	}
	
	if ( m_pBuffer )
	{
		free(m_pBuffer);
		m_pBuffer = nil;
	}
}

bool CStream::HasSource()
{
	return (m_pAlSources[0] != AL_NONE) && (m_pAlSources[1] != AL_NONE);
}

bool CStream::IsOpened()
{
	return m_pSoundFile && m_pSoundFile->IsOpened();
}

bool CStream::IsPlaying()
{
	if ( !HasSource() || !IsOpened() ) return false;
	
	if ( !m_bPaused )
	{
		ALint sourceState[2];
		alGetSourcei(m_pAlSources[0], AL_SOURCE_STATE, &sourceState[0]);
		alGetSourcei(m_pAlSources[1], AL_SOURCE_STATE, &sourceState[1]);
		if ( m_bActive || sourceState[0] == AL_PLAYING || sourceState[1] == AL_PLAYING)
			return true;
	}
	
	return false;
}

void CStream::Pause()
{
	if ( !HasSource() ) return;
	ALint sourceState = AL_PAUSED;
	alGetSourcei(m_pAlSources[0], AL_SOURCE_STATE, &sourceState);
	if (sourceState != AL_PAUSED )
		alSourcePause(m_pAlSources[0]);
	alGetSourcei(m_pAlSources[1], AL_SOURCE_STATE, &sourceState);
	if (sourceState != AL_PAUSED)
		alSourcePause(m_pAlSources[1]);
}

void CStream::SetPause(bool bPause)
{
	if ( !HasSource() ) return;
	if ( bPause )
	{
		Pause();
		m_bPaused = true;
	}
	else
	{
		if (m_bPaused)
			SetPlay(true);
		m_bPaused = false;
	}
}

void CStream::SetPitch(float pitch)
{
	if ( !HasSource() ) return;
	alSourcef(m_pAlSources[0], AL_PITCH, pitch);
	alSourcef(m_pAlSources[1], AL_PITCH, pitch);
}

void CStream::SetGain(float gain)
{
	if ( !HasSource() ) return;
	alSourcef(m_pAlSources[0], AL_GAIN, gain);
	alSourcef(m_pAlSources[1], AL_GAIN, gain);
}

void CStream::SetPosition(int i, float x, float y, float z)
{
	if ( !HasSource() ) return;
	alSource3f(m_pAlSources[i], AL_POSITION, x, y, z);
}

void CStream::SetVolume(uint32 nVol)
{
	m_nVolume = nVol;
	SetGain(ALfloat(nVol) / MAX_VOLUME);
}

void CStream::SetPan(uint8 nPan)
{
	m_nPan = clamp((int8)nPan - 63, 0, 63);
	SetPosition(0, (m_nPan - 63) / 64.0f, 0.0f, Sqrt(1.0f - SQR((m_nPan - 63) / 64.0f)));

	m_nPan = clamp((int8)nPan + 64, 64, 127);
	SetPosition(1, (m_nPan - 63) / 64.0f, 0.0f, Sqrt(1.0f - SQR((m_nPan - 63) / 64.0f)));

	m_nPan = nPan;
}

void CStream::SetPosMS(uint32 nPos)
{
	if ( !IsOpened() ) return;
	m_pSoundFile->Seek(nPos);
	ClearBuffers();
}

uint32 CStream::GetPosMS()
{
	if ( !HasSource() ) return 0;
	if ( !IsOpened() ) return 0;
	
	ALint offset;
	//alGetSourcei(m_alSource, AL_SAMPLE_OFFSET, &offset);
	alGetSourcei(m_pAlSources[0], AL_BYTE_OFFSET, &offset);

	return m_pSoundFile->Tell()
		- m_pSoundFile->samples2ms(m_pSoundFile->GetBufferSamples() * (NUM_STREAMBUFFERS/2-1)) / m_pSoundFile->GetChannels()
		+ m_pSoundFile->samples2ms(offset/m_pSoundFile->GetSampleSize()) / m_pSoundFile->GetChannels();
}

uint32 CStream::GetLengthMS()
{
	if ( !IsOpened() ) return 0;
	return m_pSoundFile->GetLength();
}

bool CStream::FillBuffer(ALuint *alBuffer)
{
	if ( !HasSource() )
		return false;
	if ( !IsOpened() )
		return false;
	if ( !(alBuffer[0] != AL_NONE && alIsBuffer(alBuffer[0])) )
		return false;
	if ( !(alBuffer[1] != AL_NONE && alIsBuffer(alBuffer[1])) )
		return false;
	
	uint32 size = m_pSoundFile->Decode(m_pBuffer);
	if( size == 0 )
		return false;

	uint32 channelSize = size / m_pSoundFile->GetChannels();
	
	alBufferData(alBuffer[0], AL_FORMAT_MONO16, m_pBuffer, channelSize, m_pSoundFile->GetSampleRate());
	// TODO: use just one buffer if we play mono
	if (m_pSoundFile->GetChannels() == 1)
		alBufferData(alBuffer[1], AL_FORMAT_MONO16, m_pBuffer, channelSize, m_pSoundFile->GetSampleRate());
	else
		alBufferData(alBuffer[1], AL_FORMAT_MONO16, (uint8*)m_pBuffer + channelSize, channelSize, m_pSoundFile->GetSampleRate());
	return true;
}

int32 CStream::FillBuffers()
{
	int32 i = 0;
	for ( i = 0; i < NUM_STREAMBUFFERS/2; i++ )
	{
		if ( !FillBuffer(&m_alBuffers[i*2]) )
			break;
		alSourceQueueBuffers(m_pAlSources[0], 1, &m_alBuffers[i*2]);
		alSourceQueueBuffers(m_pAlSources[1], 1, &m_alBuffers[i*2+1]);
	}
	
	return i;
}

void CStream::ClearBuffers()
{
	if ( !HasSource() ) return;

	ALint buffersQueued[2];
	alGetSourcei(m_pAlSources[0], AL_BUFFERS_QUEUED, &buffersQueued[0]);
	alGetSourcei(m_pAlSources[1], AL_BUFFERS_QUEUED, &buffersQueued[1]);

	ALuint value;
	while (buffersQueued[0]--)
		alSourceUnqueueBuffers(m_pAlSources[0], 1, &value);
	while (buffersQueued[1]--)
		alSourceUnqueueBuffers(m_pAlSources[1], 1, &value);
}

bool CStream::Setup()
{
	if ( IsOpened() )
	{
		m_pSoundFile->Seek(0);
		//SetPosition(0.0f, 0.0f, 0.0f);
		SetPitch(1.0f);
		//SetPan(m_nPan);
		//SetVolume(100);
	}
	
	return IsOpened();
}

void CStream::SetPlay(bool state)
{
	if ( !HasSource() ) return;
	if ( state )
	{
		ALint sourceState = AL_PLAYING;
		alGetSourcei(m_pAlSources[0], AL_SOURCE_STATE, &sourceState);
		if (sourceState != AL_PLAYING )
			alSourcePlay(m_pAlSources[0]);

		sourceState = AL_PLAYING;
		alGetSourcei(m_pAlSources[1], AL_SOURCE_STATE, &sourceState);
		if (sourceState != AL_PLAYING)
			alSourcePlay(m_pAlSources[1]);

		m_bActive = true;
	}
	else
	{
		ALint sourceState = AL_STOPPED;
		alGetSourcei(m_pAlSources[0], AL_SOURCE_STATE, &sourceState);
		if (sourceState != AL_STOPPED)
			alSourceStop(m_pAlSources[0]);

		sourceState = AL_STOPPED;
		alGetSourcei(m_pAlSources[1], AL_SOURCE_STATE, &sourceState);
		if (sourceState != AL_STOPPED)
			alSourceStop(m_pAlSources[1]);

		m_bActive = false;
	}
}

void CStream::Start()
{
	if ( !HasSource() ) return;
	if ( FillBuffers() != 0 )
		SetPlay(true);
}

void CStream::Stop()
{
	if ( !HasSource() ) return;
	SetPlay(false);
}

void CStream::Update()
{
	if ( !IsOpened() )
		return;
	
	if ( !HasSource() )
		return;
	
	if ( m_bReset )
		return;
	
	if ( !m_bPaused )
	{
		ALint sourceState[2];
		ALint buffersProcessed[2] = { 0, 0 };
		
		// Relying a lot on left buffer states in here

		//alSourcef(m_pAlSources[0], AL_ROLLOFF_FACTOR, 0.0f);
		alGetSourcei(m_pAlSources[0], AL_SOURCE_STATE, &sourceState[0]);
		alGetSourcei(m_pAlSources[0], AL_BUFFERS_PROCESSED, &buffersProcessed[0]);
		//alSourcef(m_pAlSources[1], AL_ROLLOFF_FACTOR, 0.0f);
		alGetSourcei(m_pAlSources[1], AL_SOURCE_STATE, &sourceState[1]);
		alGetSourcei(m_pAlSources[1], AL_BUFFERS_PROCESSED, &buffersProcessed[1]);
		
		ALint looping = AL_FALSE;
		alGetSourcei(m_pAlSources[0], AL_LOOPING, &looping);
		
		if ( looping == AL_TRUE )
		{
			TRACE("stream set looping");
			alSourcei(m_pAlSources[0], AL_LOOPING, AL_TRUE);
			alSourcei(m_pAlSources[1], AL_LOOPING, AL_TRUE);
		}

		assert(buffersProcessed[0] == buffersProcessed[1]);
		
		while( buffersProcessed[0]-- )
		{
			ALuint buffer[2];
			
			alSourceUnqueueBuffers(m_pAlSources[0], 1, &buffer[0]);
			alSourceUnqueueBuffers(m_pAlSources[1], 1, &buffer[1]);
			
			if (m_bActive && FillBuffer(buffer))
			{
				alSourceQueueBuffers(m_pAlSources[0], 1, &buffer[0]);
				alSourceQueueBuffers(m_pAlSources[1], 1, &buffer[1]);
			}
		}
		
		if ( sourceState[0] != AL_PLAYING )
		{
			alGetSourcei(m_pAlSources[0], AL_BUFFERS_PROCESSED, &buffersProcessed[0]);
			SetPlay(buffersProcessed[0]!=0);
		}
	}
}

void CStream::ProviderInit()
{
	if ( m_bReset )
	{
		if ( Setup() )
		{
			SetPan(m_nPan);
			SetVolume(m_nVolume);
			SetPosMS(m_nPosBeforeReset);
			if (m_bActive)
				FillBuffers();
			SetPlay(m_bActive);
			if ( m_bPaused )
				Pause();
		}
	
		m_bReset = false;
	}
}

void CStream::ProviderTerm()
{
	m_bReset = true;
	m_nPosBeforeReset = GetPosMS();
	
	ClearBuffers();
}
	
#endif
