#pragma once

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

	void Process();
	void ProcessForDisplayClock();
};

VALIDATE_SIZE(COnscreenTimerEntry, 0x3C);

class COnscreenCounterEntry
{
public:
	uint32 m_nCounterOffset;
	char m_aCounterText[10];
	uint16 m_nType;
	char m_aCounterBuffer[40];
	bool m_bCounterProcessed;

	void ProcessForDisplayCounter();
};

VALIDATE_SIZE(COnscreenCounterEntry, 0x3C);

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

	void AddCounter(uint32 offset, uint16 type, char* text, uint16 pos);
	void AddClock(uint32 offset, char* text, bool bGoingDown);
};

VALIDATE_SIZE(COnscreenTimer, 0xF4);
