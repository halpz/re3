#include "common.h"
#include "patcher.h"
#include "CarCtrl.h"

WRAPPER void CCarCtrl::SwitchVehicleToRealPhysics(CVehicle*) { EAXJMP(0x41F7F0); }