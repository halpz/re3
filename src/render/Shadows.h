#pragma once

struct RwTexture;
class CEntity;

enum
{
	SHADOWTYPE_2 = 2
};

class CShadows
{
public:
	static void AddPermanentShadow(uint8 ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, uint8 nRed, uint8 nGreen, uint8 nBlue, float fZDistance, uint32 nTime, float fScale);
	static void RenderStaticShadows(void);
	static void RenderStoredShadows(void);
	static void RenderExtraPlayerShadows(void);
	static void CalcPedShadowValues(CVector light, float *frontX, float *frontY, float *sideX, float *sideY, float *dispX, float *dispY);
	static void StoreShadowForTree(CEntity *ent);
	static void StoreShadowForPole(CEntity *ent, float offsetX, float offsetY, float offsetZ, float poleHeight, float poleWidth, uint32 subId);
	static void StoreShadowForPedObject(CEntity *ent, float dispX, float dispY, float frontX, float frontY, float sideX, float sideY);
	static void StoreStaticShadow(uint32 id, uint8 type, RwTexture *texture, CVector *coors, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, float scale, float drawDistance, bool temporaryShadow, float upDistance);;
	static void StoreShadowToBeRendered(uint8 type, RwTexture *texture, CVector *coors, float frontX, float frontY, float sideX, float sideY, int16 intensity, uint8 red, uint8 green, uint8 blue, float zDistance, bool drawOnWater, float upDistance);
};

extern RwTexture *&gpBloodPoolTex;
extern RwTexture *&gpShadowExplosionTex;
