#include "common.h"
#include "patcher.h"
#include "AudioManager.h"

cAudioManager &AudioManager = *(cAudioManager*)0x880FC0;

void
cAudioManager::PlayerJustLeftCar(void)
{
	// UNUSED: This is a perfectly empty function.
}

STARTPATCHES
	InjectHook(0x56AD20, &cAudioManager::PlayerJustLeftCar, PATCH_JUMP);
ENDPATCHES