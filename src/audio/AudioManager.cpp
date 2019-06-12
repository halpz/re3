#include "common.h"
#include "patcher.h"
#include "AudioManager.h"

cAudioManager &AudioManager = *(cAudioManager*)0x880FC0;

void
cAudioManager::PlayerJustLeftCar(void)
{
	// UNUSED: This is a perfectly empty function.
}

void
cAudioManager::GetPhrase(uint32 *phrase, uint32 *prevPhrase,
                         eAudioSamples sample, uint32 maxOffset)
{
	*phrase = (uint32)sample +
	          (uint32)m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] %
	              maxOffset;
	if(*phrase == *prevPhrase && ++*phrase >= (uint32)sample + maxOffset)
		*phrase = (uint32)sample;
	*prevPhrase = *phrase;
}

WRAPPER void cAudioManager::Service() { EAXJMP(0x57A2A0); }

STARTPATCHES
	InjectHook(0x56AD20, &cAudioManager::PlayerJustLeftCar, PATCH_JUMP);
	InjectHook(0x570DB0, &cAudioManager::GetPhrase, PATCH_JUMP);
ENDPATCHES
