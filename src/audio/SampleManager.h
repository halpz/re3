#pragma once

class CSampleManager {
public:
	static uint32 &nNumOfMp3Files;

public:
	void ReleaseDigitalHandle();
	void RequireDigitalHandle();
	static bool IsMP3RadioChannelAvailable();
};

extern CSampleManager &cSampleManager;