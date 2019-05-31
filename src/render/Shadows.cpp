#include "common.h"
#include "patcher.h"
#include "Shadows.h"

WRAPPER void CShadows::AddPermanentShadow(unsigned char ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, unsigned char nRed, unsigned char nGreen, unsigned char nBlue, float fZDistance, unsigned int nTime, float fScale) { EAXJMP(0x512FD0); }
WRAPPER void CShadows::RenderStaticShadows(void) { EAXJMP(0x5145F0); }
WRAPPER void CShadows::RenderStoredShadows(void) { EAXJMP(0x514010); }
WRAPPER void CShadows::RenderExtraPlayerShadows(void) { EAXJMP(0x516F90); }
