#include "common.h"
#include "patcher.h"
#include "Game.h"

int &CGame::currLevel = *(int*)0x941514;
bool &CGame::bDemoMode = *(bool*)0x5F4DD0;
bool &CGame::nastyGame = *(bool*)0x5F4DD4;
bool &CGame::frenchGame = *(bool*)0x95CDCB;
bool &CGame::germanGame = *(bool*)0x95CD1E;
bool &CGame::noProstitutes = *(bool*)0x95CDCF;

WRAPPER void CGame::Process(void) { EAXJMP(0x48C850); }
WRAPPER Bool CGame::InitialiseOnceBeforeRW(void) { EAXJMP(0x48BB80); }
WRAPPER Bool CGame::InitialiseRenderWare(void) { EAXJMP(0x48BBA0); }
WRAPPER void CGame::ShutdownRenderWare(void) { EAXJMP(0x48BCB0); }
WRAPPER void CGame::FinalShutdown(void) { EAXJMP(0x48BEC0); }
WRAPPER void CGame::ShutDown(void) { EAXJMP(0x48C3A0); }
WRAPPER void CGame::ShutDownForRestart(void) { EAXJMP(0x48C6B0); }
WRAPPER void CGame::InitialiseWhenRestarting(void) { EAXJMP(0x48C740); }
WRAPPER Bool CGame::InitialiseOnceAfterRW(void) { EAXJMP(0x48BD50); }
