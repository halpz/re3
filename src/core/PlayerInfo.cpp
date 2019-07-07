#include "common.h"
#include "patcher.h"
#include "PlayerInfo.h"

WRAPPER void CPlayerInfo::MakePlayerSafe(bool) { EAXJMP(0x4A1400); }