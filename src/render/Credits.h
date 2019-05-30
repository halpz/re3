#pragma once

class CCredits
{
	static bool &bCreditsGoing;
	static uint32 &CreditsStartTime;
public:
	static void Init(void);
	static void Start(void);
	static void Stop(void);
	static bool AreCreditsDone(void) { return bCreditsGoing; }
	static void Render(void);
	static void PrintCreditSpace(float space, uint32 &line);
	static void PrintCreditText(float scaleX, float scaleY, wchar_t *text, uint32 &lineoffset, float scrolloffset);
};
