#pragma once

#include "common.h"

class COnscreenTimerEntry
{
public:
	uint32 m_nTimerOffset;
	uint32 m_nCounterOffset;
	uint8 m_aTimerText[10];
	uint8 m_aCounterText[10];
	uint16 m_nType;
	char m_bCounterBuffer[42];
	char m_bTimerBuffer[42];
	bool m_bTimerProcessed;
	bool m_bCounterProcessed;

	void Process();
	bool ProcessForDisplay();

	int ProcessForDisplayTimer();
	int ProcessForDisplayCounter();
};

static_assert(sizeof(COnscreenTimerEntry) == 0x74, "COnscreenTimerEntry: error");

class CTheScripts{
public:
	static char *ScriptSpace;//[163840]
};

class COnscreenTimer
{
public:
	COnscreenTimerEntry m_sEntries[1];
	bool m_bProcessed;
	bool m_bDisabled;
	char field_119[2];

	int Init();
	void Process();
	void ProcessForDisplay();

	void ClearCounter(uint32 offset);
	void ClearClock(uint32 offset);

	void AddCounter(uint32 offset, uint16 type, char* text);
	void AddClock(uint32 offset, char* text);
};

static_assert(sizeof(COnscreenTimer) == 0x78, "COnscreenTimer: error");

class CPlaceName
{
};

class CCurrentVehicle
{
};

class CPager
{
};

class CUserDisplay
{
public:
	static CPlaceName &PlaceName;
	static COnscreenTimer &OnscnTimer;
	static CPager &Pager;
	static CCurrentVehicle &CurrentVehicle;
};
