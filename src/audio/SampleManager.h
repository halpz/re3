#pragma once

class CSampleManager {
public:
	static uint32 &nNumOfMp3Files;

public:
	void ReleaseDigitalHandle();
	static bool IsMP3RadioChannelAvailable();
};

extern CSampleManager &cSampleManager;