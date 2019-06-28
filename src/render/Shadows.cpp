#include "common.h"
#include "patcher.h"
#include "Shadows.h"

WRAPPER void CShadows::AddPermanentShadow(uint8 ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, uint8 nRed, uint8 nGreen, uint8 nBlue, float fZDistance, uint32 nTime, float fScale) { EAXJMP(0x512FD0); }
WRAPPER void CShadows::RenderStaticShadows(void) { EAXJMP(0x5145F0); }
WRAPPER void CShadows::RenderStoredShadows(void) { EAXJMP(0x514010); }
WRAPPER void CShadows::RenderExtraPlayerShadows(void) { EAXJMP(0x516F90); }
WRAPPER void CShadows::CalcPedShadowValues(CVector light, float *frontX, float *frontY, float *sideX, float *sideY, float *dispX, float *dispY) { EAXJMP(0x516EB0); }
WRAPPER void CShadows::StoreShadowForPedObject(CEntity *ent, float dispX, float dispY, float frontX, float frontY, float sideX, float sideY) { EAXJMP(0x513CB0); }

RwTexture*& gpBloodPoolTex = *(RwTexture * *)0x9415F8;