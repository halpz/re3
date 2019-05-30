#include "common.h"
#include "patcher.h"
#include "Darkel.h"

WRAPPER void CDarkel::DrawMessages(void) { EAXJMP(0x420920); }
