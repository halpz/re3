#pragma once

class CCutsceneMgr
{
	static bool &ms_cutsceneProcessing;
public:
	static bool IsCutsceneProcessing(void) { return ms_cutsceneProcessing; }
};
