#include "common.h"
#include "patcher.h"
#include "Frontend.h"

int &CMenuManager::m_PrefsBrightness = *(int*)0x5F2E50;
int &CMenuManager::m_PrefsLanguage = *(int*)0x941238;
CMenuManager &FrontEndMenuManager = *(CMenuManager*)0x8F59D8;

WRAPPER void CMenuManager::DrawFrontEnd(void) { EAXJMP(0x47A540); }
