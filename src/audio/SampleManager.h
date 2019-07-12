#pragma once

#include "common.h"

struct tSample {
	int m_nOffset;
	unsigned int m_nSize;
	int m_nFrequency;
	int m_nLoopStart;
	int m_nLoopEnd;
};

class CSampleManager
{
public:
	void SetChannelFrequency(int32, int32);
	void SetChannelEmittingVolume(int32, uint32);
	void SetChannel3DPosition(int32, float, float, float);
	void SetChannelLoopCount(int32, int32);

	void SetChannel3DDistances(int32, int32, int32);
	void SetChannelReverbFlag(int32, uint8);

	int32 GetSampleLength(int32);

	bool InitialiseChannel(int32, int32, uint32, uint32 something = 0);

	void SetChannelLoopPoints(int32, int32, int32);

	bool CheckForAnAudioFileOnCD();

	int32 GetSampleBaseFrequency(int32);
	int32 GetSampleLoopStartOffset(int32);
	int32 GetSampleLoopEndOffset(int32);

	bool IsSampleBankLoaded(uint8);
	void UnloadSampleBank(uint8);
	void Terminate();

	bool Initialise();
	int32 GetActiveSamples();

	void ReleaseDigitalHandle();
	void RequireDigitalHandle();

	char AutoDetect3DProviders();
	uint8 GetCDAudioDriveLetter();

	void SetEffectsMasterVolume(uint8 volume);
	void SetMusicMasterVolume(uint8 volume);
	void SetEffectsFadeVol(uint8 volume);
	void SetMusicFadeVol(uint8 volume);

	void SetSpeakerConfig(uint32 config);

	bool GetChannelUsedFlag(int32 id);

	void StartChannel(int32 id);
	void StopChannel(int32 id);

	static bool IsMP3RadioChannelAvailable();
};

extern uint32 &nNumOfMp3Files;
extern uint8 &num3DProvidersAvailable;
extern uint32 *asName3DProviders;

extern CSampleManager &cSampleManager;