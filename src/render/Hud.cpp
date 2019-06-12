#include "common.h"
#include "patcher.h"
#include "Hud.h"

bool &CHud::m_Wants_To_Draw_Hud = *(bool*)0x95CD89;

WRAPPER void CHud::Draw(void) { EAXJMP(0x5052A0); }
WRAPPER void CHud::DrawAfterFade(void) { EAXJMP(0x509030); }
