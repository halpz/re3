#include "common.h"
#include "patcher.h"
#include "AudioManager.h"

cAudioManager &AudioManager = *(cAudioManager*)0x880FC0;

void
cAudioManager::PlayerJustLeftCar(void)
{
	// UNUSED: This is a perfectly empty function.
}

WRAPPER void cAudioManager::Service() { EAXJMP(0x57A2A0); }

STARTPATCHES
	InjectHook(0x56AD20, &cAudioManager::PlayerJustLeftCar, PATCH_JUMP);
ENDPATCHES