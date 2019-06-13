#include "common.h"
#include "patcher.h"
#include "CutsceneMgr.h"

bool &CCutsceneMgr::ms_cutsceneProcessing = *(bool*)0x95CD9F;
Bool &CCutsceneMgr::ms_running = *(Bool*)0x95CCF5;
