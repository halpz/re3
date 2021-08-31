#pragma once

#include "common.h"
#include "singletonManager.h"

class cCustomSoundTrack : public base::cSingleton<cCustomSoundTrack>
{
public:
	bool m_bIsPlaying;

	cCustomSoundTrack();
	bool IsPlaying()
	{
#ifdef CUSTOM_SOUND_TRACK
		return m_bIsPlaying;
#else
		return false;
#endif
	}
};