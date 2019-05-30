#include "common.h"
#include "patcher.h"
#include "Hud.h"

WRAPPER void CHud::Draw(void) { EAXJMP(0x5052A0); }
WRAPPER void CHud::DrawAfterFade(void) { EAXJMP(0x509030); }
