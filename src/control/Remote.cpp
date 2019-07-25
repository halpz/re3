#include "common.h"
#include "patcher.h"
#include "Remote.h"

WRAPPER void CRemote::GivePlayerRemoteControlledCar(float, float, float, float) { EAXJMP(0x435C30); }
WRAPPER void CRemote::TakeRemoteControlledCarFromPlayer(void) { EAXJMP(0x435DA0); }
