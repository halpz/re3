#pragma once
#include "common.h"

class CConsole
{
	enum {
		MAX_MESSAGE_LENGTH = 40
	};
	uint8 m_nActiveMessages;
	uint8 m_nCurrentMessage;
	wchar m_asMessages[NUM_CONSOLEMESSAGES][MAX_MESSAGE_LENGTH];
	uint32 m_anTimeStart[NUM_CONSOLEMESSAGES];
	uint8 m_anColourRed[NUM_CONSOLEMESSAGES];
	uint8 m_anColourGreen[NUM_CONSOLEMESSAGES];
	uint8 m_anColourBlue[NUM_CONSOLEMESSAGES];

public:
	void Init() { m_nCurrentMessage = 0; m_nActiveMessages = 0; }
	void Display();
};

extern CConsole& TheConsole;

static_assert(sizeof(CConsole) == 0x2BC, "CConsole: error");