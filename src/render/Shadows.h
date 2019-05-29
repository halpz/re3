#pragma once

struct RwTexture;

class CShadows
{
public:
	static void AddPermanentShadow(unsigned char ShadowType, RwTexture* pTexture, CVector* pPosn, float fX1, float fY1, float fX2, float fY2, short nTransparency, unsigned char nRed, unsigned char nGreen, unsigned char nBlue, float fZDistance, unsigned int nTime, float fScale);
};