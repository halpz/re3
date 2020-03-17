#include "common.h"
#include "patcher.h"
#include "Cranes.h"

WRAPPER bool CCranes::IsThisCarBeingTargettedByAnyCrane(CVehicle*) { EAXJMP(0x5451E0); }
WRAPPER bool CCranes::IsThisCarBeingCarriedByAnyCrane(CVehicle*) { EAXJMP(0x545190); }
WRAPPER bool CCranes::IsThisCarPickedUp(float, float, CVehicle*) { EAXJMP(0x543940); }
WRAPPER bool CCranes::HaveAllCarsBeenCollectedByMilitaryCrane() { EAXJMP(0x544BE0); }
WRAPPER void CCranes::ActivateCrane(float, float, float, float, float, float, float, float, bool, bool, float, float) { EAXJMP(0x543650); }
WRAPPER void CCranes::DeActivateCrane(float, float) { EAXJMP(0x543890); }
WRAPPER void CCranes::InitCranes(void) { EAXJMP(0x543360); }
WRAPPER void CCranes::UpdateCranes(void) { EAXJMP(0x5439E0); }
WRAPPER void CCranes::Save(uint8*, uint32*) { EAXJMP(0x545210); }
WRAPPER void CranesLoad(uint8*, uint32) { EAXJMP(0x5454d0); }
