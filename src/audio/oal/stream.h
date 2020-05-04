#pragma once
#include "common.h"

#ifdef AUDIO_OAL
#include <AL/al.h>

#define NUM_STREAMBUFFERS 5
#define STREAMBUFFER_SIZE 0x4000

class CStream
{
	char     m_aFilename[128];
	ALuint  &m_alSource;
	ALuint (&m_alBuffers)[NUM_STREAMBUFFERS];
	
	bool     m_bIsOpened;
	bool     m_bPaused;
		
	uint32   m_nLength;
	uint32   m_nLengthMS;
	uint32   m_nBitRate;
	
	unsigned long   m_nFormat;
	unsigned long   m_nFreq;
	
	uint32   m_nBufferSize;
	void    *m_pBuffer;
	
	ALint iTotalBuffersProcessed;
	
	bool   FillBuffer(ALuint alBuffer);
	int32  FillBuffers();
public:
	static void Initialise();
	static void Terminate();
	
	CStream(char *filename, ALuint &source, ALuint (&buffers)[NUM_STREAMBUFFERS]);
	~CStream();
	
	void   Delete();
	
	bool   IsOpened();
	bool   IsPlaying();
	void   SetPause (bool bPause);
	void   SetVolume(uint32 nVol);
	void   SetPan   (uint8 nPan);
	void   SetPos   (uint32 nPos); 

	uint32 GetPos();
	uint32 GetLength();
	
	bool Setup();
	void Start();
	void Update(void);
};

#endif