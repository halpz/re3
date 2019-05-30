#include "common.h"
#include "patcher.h"
#include "User.h"

CPlaceName &CUserDisplay::PlaceName = *(CPlaceName*)0x8F29BC;
COnscreenTimer &CUserDisplay::OnscnTimer = *(COnscreenTimer*)0x862238;
CPager &CUserDisplay::Pager = *(CPager*)0x8F2744;
CCurrentVehicle &CUserDisplay::CurrentVehicle = *(CCurrentVehicle*)0x8F5FE8;

WRAPPER void COnscreenTimer::ProcessForDisplay(void) { EAXJMP(0x4292E0); }
