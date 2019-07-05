#pragma once

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
	void StopChannel(int32 id);

	static bool IsMP3RadioChannelAvailable();
};

extern uint32 &nNumOfMp3Files;
extern uint8 &num3DProvidersAvailable;
extern uint32* asName3DProviders;

extern CSampleManager &cSampleManager;