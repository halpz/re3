#include "common.h"
#include "patcher.h"
#include "Cranes.h"

WRAPPER bool CCranes::IsThisCarBeingTargettedByAnyCrane(CVehicle*) { EAXJMP(0x5451E0); }
