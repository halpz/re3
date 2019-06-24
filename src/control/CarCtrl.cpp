#include "common.h"
#include "patcher.h"
#include "CarCtrl.h"

int &CCarCtrl::NumLawEnforcerCars = *(int*)0x8F1B38;

WRAPPER void CCarCtrl::SwitchVehicleToRealPhysics(CVehicle*) { EAXJMP(0x41F7F0); }
WRAPPER void CCarCtrl::AddToCarArray(int id, int vehclass) { EAXJMP(0x4182F0); }
