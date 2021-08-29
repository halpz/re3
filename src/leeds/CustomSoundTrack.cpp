#include "common.h"

#include "CustomSoundTrack.h"

// TODO - implement

cCustomSoundTrack* base::cSingleton<cCustomSoundTrack>::mspInstance = nil;

cCustomSoundTrack::cCustomSoundTrack() :
	m_bIsPlaying(false)
{}
