#include "common.h"
#include "patcher.h"
#include "Game.h"

int &CGame::currLevel = *(int*)0x941514;
bool &CGame::bDemoMode = *(bool*)0x5F4DD0;
bool &CGame::nastyGame = *(bool*)0x5F4DD4;

WRAPPER void CGame::Process(void) { EAXJMP(0x48C850); }
