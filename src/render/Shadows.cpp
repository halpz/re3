#include "common.h"
#include "patcher.h"
#include "Shadows.h"

WRAPPER void CShadows::AddPermanentShadow(uint8 ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, uint8 nRed, uint8 nGreen, uint8 nBlue, float fZDistance, uint32 nTime, float fScale) { EAXJMP(0x512FD0); }
WRAPPER void CShadows::RenderStaticShadows(void) { EAXJMP(0x5145F0); }
WRAPPER void CShadows::RenderStoredShadows(void) { EAXJMP(0x514010); }
WRAPPER void CShadows::RenderExtraPlayerShadows(void) { EAXJMP(0x516F90); }
WRAPPER void CShadows::CalcPedShadowValues(CVector light, float *frontX, float *frontY, float *sideX, float *sideY, float *dispX, float *dispY) { EAXJMP(0x516EB0); }
WRAPPER void CShadows::StoreShadowForPole(CEntity *ent, float offsetX, float offsetY, float offsetZ, float poleHeight, float poleWidth, uint32 subId) { EAXJMP(0x513E10); }
WRAPPER void CShadows::StoreShadowForPedObject(CEntity *ent, float dispX, float dispY, float frontX, float frontY, float sideX, float sideY) { EAXJMP(0x513CB0); }
WRAPPER void CShadows::StoreStaticShadow(uint32 id, uint8 type, RwTexture *texture, CVector *coors, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, float drawDistance, bool temporaryShadow, float upDistance) { EAXJMP(0x5130A0); }
WRAPPER void CShadows::StoreShadowToBeRendered(uint8 type, RwTexture *texture, CVector *coors, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, bool drawOnWater, float upDistance) { EAXJMP(0x513750); }

RwTexture *&gpBloodPoolTex = *(RwTexture**)0x9415F8;
RwTexture *&gpShadowExplosionTex = *(RwTexture**)0x8F2A00;

void
CShadows::StoreShadowForTree(CEntity *ent)
{
	// empty
}
