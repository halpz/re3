#include "common.h"
#include "patcher.h"
#include "Remote.h"

WRAPPER void CRemote::TakeRemoteControlledCarFromPlayer(void) { EAXJMP(0x435DA0); }
