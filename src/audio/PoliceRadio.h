#pragma once

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

static_assert(sizeof(cAMCrime) == 20, "cAMCrime: error ");

class cPoliceRadioQueue
{
public:
	int32 crimesSamples[60];
	uint8 policeChannelTimer;
	uint8 policeChannelTimerSeconds;
	uint8 policeChannelCounterSeconds;
	cAMCrime crimes[10];

	cPoliceRadioQueue()
	{
		policeChannelTimerSeconds = 0;
		policeChannelCounterSeconds = 0;
		policeChannelTimer = 0;
	}

	void Add(uint32 sample)
	{
		if (policeChannelTimer != 60) {
			crimesSamples[policeChannelTimerSeconds] = sample;
			policeChannelTimer++;
			policeChannelTimerSeconds = (policeChannelTimerSeconds + 1) % 60;
		}
	}
};

static_assert(sizeof(cPoliceRadioQueue) == 444, "cPoliceRadioQueue: error ");