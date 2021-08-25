#pragma once

#include "common.h"

enum
{
	COUNTER_DISPLAY_NUMBER,
	COUNTER_DISPLAY_BAR,
};

class COnscreenTimerEntry
{
public:
	uint32 m_nClockOffset;
	char m_aClockText[10];
	char m_aClockBuffer[40];
	bool m_bClockProcessed;
	bool m_bClockGoingDown;
	CRGBA m_aClockColour;
	bool m_bClockTickThisFrame;

	void Process();
	void ProcessForDisplayClock();
};

class COnscreenCounterEntry
{
public:
	uint32 m_nCounterOffset;
	int32 m_nTotal;
	char m_aCounterText1[10];
	char m_aCounterText2[10];
	uint16 m_nTypeOfTotal;
	uint16 m_nType;
	char m_aCounterBuffer[40];
	bool m_bCounterProcessed;
	CRGBA m_colour1;
	CRGBA m_colour2;
	bool m_bAddDollarPrefix;

	void ProcessForDisplayCounter();
};

class COnscreenTimer
{
public:
	COnscreenTimerEntry m_sClocks[NUMONSCREENCLOCKS];
	COnscreenCounterEntry m_sCounters[NUMONSCREENCOUNTERS];
	bool m_bProcessed;
	bool m_bDisabled;

	void Init();
	void Process();
	void ProcessForDisplay();

	void ClearCounter(uint32 offset);
	void ClearClock(uint32 offset);

	void AddCounter(uint32 offset, uint16 type, char* text, uint16 pos, int32, char*, uint16);
	void AddClock(uint32 offset, char* text, bool bGoingDown);

	void ChangeCounterPrefix(uint32 offset, bool bChange);
};

extern CRGBA gbColour;
extern CRGBA gbColour2;

