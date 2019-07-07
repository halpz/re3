#include "common.h"
#include "patcher.h"
#include "EmergencyPed.h"

STARTPATCHES
InjectHook(0x4C2EF0, &CEmergencyPed::dtor, PATCH_JUMP);
ENDPATCHES