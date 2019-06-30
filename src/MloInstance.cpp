#include "common.h"
#include "patcher.h"
#include "MloInstance.h"

STARTPATCHES
InjectHook(0x50BE90, &CMloInstance::dtor, PATCH_JUMP);
ENDPATCHES