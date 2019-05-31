#include "common.h"
#include "patcher.h"
#include "ControllerConfig.h"

CControllerConfigManager &ControlsManager = *(CControllerConfigManager*)0x8F43A4;

WRAPPER void CControllerConfigManager::UpdateJoyButtonState(int padnumber) { EAXJMP(0x58F5B0); }
WRAPPER void CControllerConfigManager::UpdateJoyInConfigMenus_ButtonDown(int button, int padnumber) { EAXJMP(0x58C5E0); }
WRAPPER void CControllerConfigManager::AffectControllerStateOn_ButtonDown(int button, eControllerType type) { EAXJMP(0x58C730); }
WRAPPER void CControllerConfigManager::UpdateJoyInConfigMenus_ButtonUp(int button, int padnumber) { EAXJMP(0x58CE80); }
WRAPPER void CControllerConfigManager::AffectControllerStateOn_ButtonUp(int button, int padnumber) { EAXJMP(0x58CFD0); }