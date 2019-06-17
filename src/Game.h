#pragma once

enum eLevelName
{
	LEVEL_NONE = 0,
	LEVEL_INDUSTRIAL,
	LEVEL_COMMERCIAL,
	LEVEL_SUBURBAN
};

class CGame
{
public:
	static int &currLevel;
	static bool &bDemoMode;
	static bool &nastyGame;
	static bool &frenchGame;
	static bool &germanGame;
	static bool &noProstitutes;
	static bool &playingIntro;
	static char *aDatFile;	//[32];

	static void Process(void);
	static bool InitialiseOnceBeforeRW(void);
	static bool InitialiseRenderWare(void);
	static void ShutdownRenderWare(void);
	static void FinalShutdown(void);
	static void ShutDown(void);
	static void ShutDownForRestart(void);
	static void InitialiseWhenRestarting(void);
	static bool InitialiseOnceAfterRW(void);
};
