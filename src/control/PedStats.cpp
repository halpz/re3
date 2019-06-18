#include "common.h"
#include "patcher.h"
#include "PedStats.h"

WRAPPER int32 CPedStats::GetPedStatType(char *type) { EAXJMP(0x4EF780); }
