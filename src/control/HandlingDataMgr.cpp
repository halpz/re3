#include "common.h"
#include "patcher.h"
#include "HandlingDatamgr.h"

cHandlingDataMgr &mod_HandlingManager = *(cHandlingDataMgr*)0x728060;

WRAPPER int32 cHandlingDataMgr::GetHandlingId(const char *name){ EAXJMP(0x546B70); }
