#pragma once

class CReplay
{
public:
	static void Display(void);
	enum {
		MODE_1 = 1
	};

	static uint8 &Mode;
	static Bool &bPlayingBackFromFile;
};
