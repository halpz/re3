#pragma once
#include "CutsceneObject.h"

class CDirectory;

class CCutsceneMgr
{
	static bool &ms_running;
	static bool &ms_cutsceneProcessing;
	static CCutsceneObject *(&ms_pCutsceneObjects)[NUMCUTSCENEOBJECTS];
	
public:
	static CDirectory *&ms_pCutsceneDir;

	static bool IsRunning(void) { return ms_running; }
	static bool IsCutsceneProcessing(void) { return ms_cutsceneProcessing; }
	static CCutsceneObject* GetCutsceneObject(int id) { return ms_pCutsceneObjects[id]; }
};
