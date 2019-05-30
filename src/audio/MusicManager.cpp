#include "common.h"
#include "patcher.h"
#include "MusicManager.h"

cMusicManager &MusicManager = *(cMusicManager*)0x8F3964;

WRAPPER void cMusicManager::DisplayRadioStationName(void) { EAXJMP(0x57E6D0); }
