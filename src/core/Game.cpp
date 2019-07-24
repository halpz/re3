#include "common.h"
#include "patcher.h"
#include "Game.h"
#include "Main.h"
#include "CdStream.h"
#include "FileMgr.h"

eLevelName &CGame::currLevel = *(eLevelName*)0x941514;
bool &CGame::bDemoMode = *(bool*)0x5F4DD0;
bool &CGame::nastyGame = *(bool*)0x5F4DD4;
bool &CGame::frenchGame = *(bool*)0x95CDCB;
bool &CGame::germanGame = *(bool*)0x95CD1E;
bool &CGame::noProstitutes = *(bool*)0x95CDCF;
bool &CGame::playingIntro = *(bool*)0x95CDC2;
char *CGame::aDatFile = (char*)0x773A48;


bool
CGame::InitialiseOnceBeforeRW(void)
{
	CFileMgr::Initialise();
	CdStreamInit(MAX_CDCHANNELS);
	ValidateVersion();
	return true;
}

WRAPPER void CGame::Initialise(const char *datFile) { EAXJMP(0x48BED0); }
WRAPPER void CGame::Process(void) { EAXJMP(0x48C850); }



WRAPPER bool CGame::InitialiseRenderWare(void) { EAXJMP(0x48BBA0); }
WRAPPER void CGame::ShutdownRenderWare(void) { EAXJMP(0x48BCB0); }
WRAPPER void CGame::FinalShutdown(void) { EAXJMP(0x48BEC0); }
WRAPPER void CGame::ShutDown(void) { EAXJMP(0x48C3A0); }
WRAPPER void CGame::ShutDownForRestart(void) { EAXJMP(0x48C6B0); }
WRAPPER void CGame::InitialiseWhenRestarting(void) { EAXJMP(0x48C740); }
WRAPPER bool CGame::InitialiseOnceAfterRW(void) { EAXJMP(0x48BD50); }
