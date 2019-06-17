#include "common.h"
#include "patcher.h"
#include "PedType.h"

WRAPPER int32 CPedType::FindPedType(char *type) { EAXJMP(0x4EEC10); }
