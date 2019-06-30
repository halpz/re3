#include "common.h"
#include "SampleManager.h"

CSampleManager &cSampleManager = *(CSampleManager *)0x7341E0;
uint32 &CSampleManager::nNumOfMp3Files = *(uint32*)0x95CC00;

bool CSampleManager::IsMP3RadioChannelAvailable() {
	return nNumOfMp3Files != 0;
}

WRAPPER void
CSampleManager::ReleaseDigitalHandle()
{
	EAXJMP(0x5664B0);
}
