#include "common.h"
#include "patcher.h"
#include "WeaponEffects.h"

#include "TxdStore.h"

WRAPPER void CWeaponEffects::Render(void) { EAXJMP(0x564D70); }

CWeaponEffects &gCrossHair = *(CWeaponEffects*)0x6503BC;

void
CWeaponEffects::ClearCrossHair()
{
	gCrossHair.m_bCrosshair = false;
}

void
CWeaponEffects::MarkTarget(CVector pos, uint8 red, uint8 green, uint8 blue, uint8 alpha, float size)
{
    gCrossHair.m_bCrosshair = true;
    gCrossHair.m_vecPos = pos;
    gCrossHair.m_red = red;
    gCrossHair.m_green = green;
    gCrossHair.m_blue = blue;
    gCrossHair.m_alpha = alpha;
    gCrossHair.m_size = size;
}

void
CWeaponEffects::Init()
{
    gCrossHair.m_bCrosshair = false;
    gCrossHair.m_vecPos = CVector(0.0f, 0.0f, 0.0f);
    gCrossHair.m_red = 0;
    gCrossHair.m_green = 0;
    gCrossHair.m_blue = 0;
    gCrossHair.m_alpha = 255;
    gCrossHair.m_size = 1.0f;
    gCrossHair.field_24 = 0;
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("particle"));
    gCrossHair.m_pTexture = RwTextureRead("crosshair", nil);
    gCrossHair.m_pRaster = gCrossHair.m_pTexture->raster;
    CTxdStore::PopCurrentTxd();
}
