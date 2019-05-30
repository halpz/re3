#include "common.h"
#include "patcher.h"
#include "Messages.h"

WRAPPER void CMessages::Display(void) { EAXJMP(0x529800); }
WRAPPER void CMessages::ClearAllMessagesDisplayedByGame(void) { EAXJMP(0x52B670); }
