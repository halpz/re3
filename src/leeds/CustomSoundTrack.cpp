#include "common.h"

#include "CustomSoundTrack.h"

// TODO - implement

template<>
cCustomSoundTrack* base::cSingleton<cCustomSoundTrack>::mspInstance = nil;

cCustomSoundTrack::cCustomSoundTrack() :
	m_bIsPlaying(false)
{}
