#pragma once

class CDebug
{
	enum
	{
		MAX_LINES = 15,
		MAX_STR_LEN = 80,
	};

	static int16 ms_nCurrentTextLine;
	static char ms_aTextBuffer[MAX_LINES][MAX_STR_LEN];

public:
	static void DebugInitTextBuffer();
	static void DebugDisplayTextBuffer();
	static void DebugAddText(const char *str);
};

extern bool gbDebugStuffInRelease;
