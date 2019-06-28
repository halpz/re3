#include "common.h"
#include "patcher.h"
#include "CarCtrl.h"

int &CCarCtrl::NumLawEnforcerCars = *(int*)0x8F1B38;

WRAPPER void CCarCtrl::SwitchVehicleToRealPhysics(CVehicle*) { EAXJMP(0x41F7F0); }
WRAPPER void CCarCtrl::AddToCarArray(int32 id, int32 vehclass) { EAXJMP(0x4182F0); }
WRAPPER void CCarCtrl::UpdateCarCount(CVehicle*, bool) { EAXJMP(0x4202E0); }
WRAPPER int32 CCarCtrl::ChooseCarModel(int32 vehclass) { EAXJMP(0x418110); }
