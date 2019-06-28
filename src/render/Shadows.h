#pragma once

struct RwTexture;
class CEntity;

class CShadows
{
public:
	static void AddPermanentShadow(uint8 ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, uint8 nRed, uint8 nGreen, uint8 nBlue, float fZDistance, uint32 nTime, float fScale);
	static void RenderStaticShadows(void);
	static void RenderStoredShadows(void);
	static void RenderExtraPlayerShadows(void);
	static void CalcPedShadowValues(CVector light, float *frontX, float *frontY, float *sideX, float *sideY, float *dispX, float *dispY);
	static void StoreShadowForPedObject(CEntity *ent, float dispX, float dispY, float frontX, float frontY, float sideX, float sideY);
};

extern RwTexture*& gpBloodPoolTex;
