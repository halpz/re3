#include "stream.h"
#include "common.h"

#ifdef AUDIO_OAL

void CStream::Initialise()
{
	//mpg123_init();
}

void CStream::Terminate()
{
	//mpg123_exit();
}

CStream::CStream(char *filename, ALuint &source, ALuint (&buffers)[NUM_STREAMBUFFERS]) :
	m_alSource(source),
	m_alBuffers(buffers),
	m_nBitRate(0), 
	m_nFormat(0),
	m_nFreq(0),
	m_nLength(0), 
	m_nLengthMS(0), 
	m_nBufferSize(0),
	m_pBuffer(NULL),
	m_bIsOpened(false),
	m_bPaused(true)
	
{
	strcpy(m_aFilename, filename);
		
	//DEV("Stream %s\n", m_aFilename);

	/*
	if ( true )
	{				
		m_nBitRate     = (wBitsPerSample * nChannels * wfex.nSamplesPerSec)/1000;
		m_nLength      = ulDataSize;
		m_nLengthMS    = m_nLength*8 / m_nBitRate;
		m_nBufferSize  = nAvgBytesPerSec >> 2;
		m_nBufferSize -= (m_nLength % wfex.nBlockAlign);
		m_pBuffer      = malloc(m_nBufferSize);
		m_bIsOpened = true;
		return;
	}*/
}

CStream::~CStream()
{
	Delete();
}

void CStream::Delete()
{	
	if ( m_pBuffer )
	{
		free(m_pBuffer);
		m_pBuffer = NULL;
	}
}

bool CStream::IsOpened()
{
	return m_bIsOpened;
}

bool CStream::IsPlaying()
{
	return false;
}

void CStream::SetPause(bool bPause)
{
}

void CStream::SetVolume(uint32 nVol)
{
	
}

void CStream::SetPan(uint8 nPan)
{
}

void CStream::SetPos(uint32 nPos)
{
}

uint32 CStream::GetPos()
{
	return 0;
}

uint32 CStream::GetLength()
{
	return m_nLengthMS;
}

bool CStream::Setup()
{
	if ( !IsOpened() )
		return false;
		
	return IsOpened();
}

void CStream::Start()
{

}

void CStream::Update()
{
	if ( !IsOpened() )
		return;
}

#endif