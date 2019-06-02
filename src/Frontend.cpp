#include "common.h"
#include "patcher.h"
#include "Frontend.h"

int &CMenuManager::OS_Language = *(int*)0x5F2F78;
int &CMenuManager::m_PrefsBrightness = *(int*)0x5F2E50;
int &CMenuManager::m_PrefsLanguage = *(int*)0x941238;
bool &CMenuManager::m_PrefsUseWideScreen = *(bool*)0x95CD23;
Bool &CMenuManager::m_PrefsVsync = *(Bool*)0x5F2E58;
Bool &CMenuManager::m_PrefsAllowNastyGame = *(Bool*)0x5F2E64;
Bool &CMenuManager::m_bStartUpFrontEndRequested = *(Bool*)0x95CCF4;
Bool &CMenuManager::m_PrefsFrameLimiter = *(Bool*)0x5F2E60;

CMenuManager &FrontEndMenuManager = *(CMenuManager*)0x8F59D8;

WRAPPER void CMenuManager::Process(void) { EAXJMP(0x485100); }
WRAPPER void CMenuManager::DrawFrontEnd(void) { EAXJMP(0x47A540); }
WRAPPER void CMenuManager::UnloadTextures(void) { EAXJMP(0x47A440); }
WRAPPER void CMenuManager::LoadAllTextures(void) { EAXJMP(0x47A230); }
WRAPPER void CMenuManager::LoadSettings(void) { EAXJMP(0x488EE0); }
WRAPPER void CMenuManager::WaitForUserCD(void) { EAXJMP(0x48ADD0); }
