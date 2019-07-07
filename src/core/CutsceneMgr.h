#pragma once

class CDirectory;

class CCutsceneMgr
{
	static bool &ms_running;
	static bool &ms_cutsceneProcessing;
	
public:
	static CDirectory *&ms_pCutsceneDir;

	static bool IsRunning(void) { return ms_running; }
	static bool IsCutsceneProcessing(void) { return ms_cutsceneProcessing; }
};
