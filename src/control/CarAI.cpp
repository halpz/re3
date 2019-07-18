#include "common.h"
#include "patcher.h"
#include "CarAI.h"

WRAPPER void CCarAI::UpdateCarAI(CVehicle*) { EAXJMP(0x413E50); }
WRAPPER void CCarAI::MakeWayForCarWithSiren(CVehicle *veh) { EAXJMP(0x416280); }
