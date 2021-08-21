#pragma once

#include "Crime.h"
#include "AudioSamples.h"

struct cAMCrime {
	int32 type;
	CVector position;
	uint16 timer;

	cAMCrime()
	{
		type = CRIME_NONE;
		position = CVector(0.0f, 0.0f, 0.0f);
		timer = 0;
	}
};

VALIDATE_SIZE(cAMCrime, 20);

#define POLICE_RADIO_QUEUE_MAX_SAMPLES 60

class cPoliceRadioQueue
{
public:
	uint32 m_aSamples[POLICE_RADIO_QUEUE_MAX_SAMPLES];
	uint8 m_nSamplesInQueue;
	uint8 m_nAddOffset;
	uint8 m_nRemoveOffset;

	cPoliceRadioQueue()
	{
		Reset();
	}

	void Reset()
	{
		m_nAddOffset = 0;
		m_nRemoveOffset = 0;
		m_nSamplesInQueue = 0;
	}

	bool8 Add(uint32 sample)
	{
		if (m_nSamplesInQueue != POLICE_RADIO_QUEUE_MAX_SAMPLES) {
			m_aSamples[m_nAddOffset] = sample;
			m_nSamplesInQueue++;
			m_nAddOffset = (m_nAddOffset + 1) % POLICE_RADIO_QUEUE_MAX_SAMPLES;
			return TRUE;
		}
		return FALSE;
	}
	
	uint32 Remove()
	{
		if (m_nSamplesInQueue != 0) {
			uint32 sample = m_aSamples[m_nRemoveOffset];
			m_nSamplesInQueue--;
			m_nRemoveOffset = (m_nRemoveOffset + 1) % POLICE_RADIO_QUEUE_MAX_SAMPLES;
			return sample;
		}
		return NO_SAMPLE;
	}

};

VALIDATE_SIZE(cPoliceRadioQueue, 244);
