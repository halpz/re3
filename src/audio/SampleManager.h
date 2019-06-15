#pragma once

class CSampleManager {
public:
	static uint32 &nNumOfMp3Files;

public:
	bool IsMP3RadioChannelAvailable();
};

extern CSampleManager &cSampleManager;