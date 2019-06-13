#pragma once

class CCutsceneMgr
{
	static bool &ms_running;
	static bool &ms_cutsceneProcessing;
	
public:
	static bool IsRunning(void) { return ms_running; }
	static bool IsCutsceneProcessing(void) { return ms_cutsceneProcessing; }
	
	static Bool &ms_running;
};
