#pragma once

enum
{
	COUNTER_DISPLAY_NUMBER,
	COUNTER_DISPLAY_BAR,
};

class COnscreenTimerEntry
{
public:
	uint32 m_nOffset;
	char m_aText[10];
	char m_bBuffer[42];
	bool m_bProcessed;
	bool m_bGoingDown;


	void Process();
	bool ProcessForDisplay();

	void ProcessForDisplayClock();
};

class COnscreenCounterEntry
{
public:
	uint32 m_nOffset;
	char m_aText[10];
	uint16 m_nType;
	char m_bBuffer[42];
	bool m_bProcessed;

	bool ProcessForDisplay();
	void ProcessForDisplayCounter();
};

class COnscreenTimer
{
public:
	COnscreenTimerEntry m_sTimers[NUMONSCREENTIMERENTRIES];
	COnscreenCounterEntry m_sCounters[NUMONSCREENCOUNTERENTRIES];
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

VALIDATE_SIZE(COnscreenTimer, 0x78);
