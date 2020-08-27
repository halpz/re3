#include "common.h"

#include "WeaponEffects.h"
#include "TxdStore.h"
#include "Sprite.h"
#include "PlayerPed.h"
#include "World.h"
#include "WeaponType.h"

RwTexture *gpCrossHairTex;
RwRaster *gpCrossHairRaster;

CWeaponEffects gCrossHair;

CWeaponEffects::CWeaponEffects()
{
	
}

CWeaponEffects::~CWeaponEffects()
{
	
}

void
CWeaponEffects::Init(void)
{
	gCrossHair.m_bActive = false;
	gCrossHair.m_vecPos = CVector(0.0f, 0.0f, 0.0f);
	gCrossHair.m_nRed = 255;
	gCrossHair.m_nGreen = 0;
	gCrossHair.m_nBlue = 0;
	gCrossHair.m_nAlpha = 127;
	gCrossHair.m_fSize = 1.0f;
	gCrossHair.m_fRotation = 0.0f;
	
	
	CTxdStore::PushCurrentTxd();
	int32 slot = CTxdStore::FindTxdSlot("particle");
	CTxdStore::SetCurrentTxd(slot);
	
	gpCrossHairTex    = RwTextureRead("target256", "target256m");
	gpCrossHairRaster = RwTextureGetRaster(gpCrossHairTex);
	
	CTxdStore::PopCurrentTxd();
}

void
CWeaponEffects::Shutdown(void)
{
	RwTextureDestroy(gpCrossHairTex);
	gpCrossHairTex = nil;
}

void
CWeaponEffects::MarkTarget(CVector pos, uint8 red, uint8 green, uint8 blue, uint8 alpha, float size)
{
	gCrossHair.m_bActive = true;
	gCrossHair.m_vecPos = pos;
	gCrossHair.m_fSize = size;
}

void
CWeaponEffects::ClearCrossHair(void)
{
	gCrossHair.m_bActive = false;
}

void
CWeaponEffects::Render(void)
{
	static float aCrossHairSize[WEAPONTYPE_TOTALWEAPONS] =
	{
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.4f, 0.4f,
		0.5f,
		0.3f,
		0.9f, 0.9f, 0.9f,
		0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
		0.1f, 0.1f,
		1.0f,
		0.6f,
		0.7f,
		0.0f, 0.0f
	};



	if ( gCrossHair.m_bActive )
	{
		float size = aCrossHairSize[FindPlayerPed()->GetWeapon()->m_eWeaponType];
		
		RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void *)FALSE);
		RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       (void *)FALSE);
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
		RwRenderStateSet(rwRENDERSTATESRCBLEND,          (void *)rwBLENDSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND,         (void *)rwBLENDINVDESTALPHA);
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     (void *)gpCrossHairRaster);

		RwV3d pos;
		float w, h;
		if ( CSprite::CalcScreenCoors(gCrossHair.m_vecPos, &pos, &w, &h, true) )
		{
			float recipz = 1.0f / pos.z;
			CSprite::RenderOneXLUSprite_Rotate_Aspect(pos.x, pos.y, pos.z,
				w, h,
				255, 88, 100, 158,
				recipz, gCrossHair.m_fRotation, gCrossHair.m_nAlpha);
				
			float recipz2 = 1.0f / pos.z;
			
			CSprite::RenderOneXLUSprite_Rotate_Aspect(pos.x, pos.y, pos.z,
				size*w, size*h,
				107, 134, 247, 158,
				recipz2, TWOPI - gCrossHair.m_fRotation, gCrossHair.m_nAlpha);
						
			gCrossHair.m_fRotation += 0.02f;
			if ( gCrossHair.m_fRotation > TWOPI )
				gCrossHair.m_fRotation = 0.0;
		}
			
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
		RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void *)TRUE);
		RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       (void *)TRUE);
	}
}