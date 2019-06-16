#pragma once

class CReplay
{
public:
	enum {
		MODE_1 = 1
	};

	static uint8 &Mode;
	static bool &bPlayingBackFromFile;

	static void Display(void);
};
