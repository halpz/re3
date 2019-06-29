#include "common.h"
#include "patcher.h"
#include "PlayerPed.h"

WRAPPER void CPlayerPed::ReApplyMoveAnims(void) { EAXJMP(0x4F07C0); }
