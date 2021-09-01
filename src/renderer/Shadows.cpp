#include "common.h"

#include "main.h"
#include "TxdStore.h"
#include "Timer.h"
#include "Camera.h"
#include "Timecycle.h"
#include "CutsceneMgr.h"
#include "Automobile.h"
#include "Bike.h"
#include "Ped.h"
#include "PlayerPed.h"
#include "World.h"
#include "Weather.h"
#include "ModelIndices.h"
#include "RenderBuffer.h"
#ifdef FIX_BUGS
#include "Replay.h"
#endif
#include "PointLights.h"
#include "SpecialFX.h"
#include "Script.h"
#include "TimeStep.h"
#include "Shadows.h"
#include "CutsceneObject.h"
#include "CutsceneShadow.h"
#include "Clock.h"
#include "VarConsole.h"

#ifdef DEBUGMENU
//SETTWEAKPATH("Shadows");
//TWEAKBOOL(gbPrintShite);
#endif

RwImVertexIndex ShadowIndexList[24];

RwTexture *gpShadowCarTex;
RwTexture *gpShadowPedTex;
RwTexture *gpShadowHeliTex;
RwTexture *gpShadowBikeTex;
RwTexture *gpShadowBaronTex;
RwTexture *gpShadowExplosionTex;
RwTexture *gpShadowHeadLightsTex;
RwTexture *gpOutline1Tex;
RwTexture *gpOutline2Tex;
RwTexture *gpOutline3Tex;
RwTexture *gpBloodPoolTex;
RwTexture *gpReflectionTex;
RwTexture *gpWalkDontTex;
RwTexture *gpCrackedGlassTex;
RwTexture *gpPostShadowTex;
RwTexture *gpGoalTex;

int16            CShadows::ShadowsStoredToBeRendered;
CStoredShadow    CShadows::asShadowsStored  [MAX_STOREDSHADOWS];
CPolyBunch       CShadows::aPolyBunches     [MAX_POLYBUNCHES];
CStaticShadow    CShadows::aStaticShadows   [MAX_STATICSHADOWS];
CPolyBunch      *CShadows::pEmptyBunchList;
CPermanentShadow CShadows::aPermanentShadows[MAX_PERMAMENTSHADOWS];

#ifndef MASTER
bool gbCountPolysInShadow;
#endif

void
CShadows::Init(void)
{
	CTxdStore::PushCurrentTxd();

	int32 slut = CTxdStore::FindTxdSlot("particle");
	CTxdStore::SetCurrentTxd(slut);

	gpShadowCarTex        = RwTextureRead("shad_car",     nil);
	gpShadowPedTex        = RwTextureRead("shad_ped",     nil);
	gpShadowHeliTex       = RwTextureRead("shad_heli",    nil);
	gpShadowBikeTex       = RwTextureRead("shad_bike",    nil);
	gpShadowBaronTex      = RwTextureRead("shad_rcbaron", nil);
	gpShadowExplosionTex  = RwTextureRead("shad_exp",     nil);
	gpShadowHeadLightsTex = RwTextureRead("headlight_single",    nil);
	gpOutline1Tex         = RwTextureRead("outline_64",   nil);
	gpOutline2Tex         = RwTextureRead("outline2_64",  nil);
	gpOutline3Tex         = RwTextureRead("outline3_64",  nil);
	gpBloodPoolTex        = RwTextureRead("bloodpool_64", nil);
	//gpReflectionTex       = RwTextureRead("reflection01", nil);
	gpWalkDontTex         = RwTextureRead("walk_dont",    nil);
	//gpCrackedGlassTex     = RwTextureRead("wincrack_32",  nil);
	gpPostShadowTex       = RwTextureRead("lamp_shad_64", nil);

	CTxdStore::PopCurrentTxd();

	ASSERT(gpShadowCarTex != nil);
	ASSERT(gpShadowPedTex != nil);
	ASSERT(gpShadowHeliTex != nil);
	ASSERT(gpShadowBikeTex != nil);
	ASSERT(gpShadowBaronTex != nil);
	ASSERT(gpShadowExplosionTex != nil);
	ASSERT(gpShadowHeadLightsTex != nil);
	ASSERT(gpOutline1Tex != nil);
	ASSERT(gpOutline2Tex != nil);
	ASSERT(gpOutline3Tex != nil);
	ASSERT(gpBloodPoolTex != nil);
	//ASSERT(gpReflectionTex != nil);
	ASSERT(gpWalkDontTex != nil);
	//ASSERT(gpCrackedGlassTex != nil);
	ASSERT(gpPostShadowTex != nil);


	ShadowIndexList[0] = 0;
	ShadowIndexList[1] = 2;
	ShadowIndexList[2] = 1;

	ShadowIndexList[3] = 0;
	ShadowIndexList[4] = 3;
	ShadowIndexList[5] = 2;

	ShadowIndexList[6] = 0;
	ShadowIndexList[7] = 4;
	ShadowIndexList[8] = 3;

	ShadowIndexList[9] = 0;
	ShadowIndexList[10] = 5;
	ShadowIndexList[11] = 4;

	ShadowIndexList[12] = 0;
	ShadowIndexList[13] = 6;
	ShadowIndexList[14] = 5;

	ShadowIndexList[15] = 0;
	ShadowIndexList[16] = 7;
	ShadowIndexList[17] = 6;

	ShadowIndexList[18] = 0;
	ShadowIndexList[19] = 8;
	ShadowIndexList[20] = 7;

	ShadowIndexList[21] = 0;
	ShadowIndexList[22] = 9;
	ShadowIndexList[23] = 8;


	for ( int32 i = 0; i < MAX_STATICSHADOWS; i++ )
	{
		aStaticShadows[i].m_nId = 0;
		aStaticShadows[i].m_pPolyBunch = nil;
	}

	pEmptyBunchList = &aPolyBunches[0];

	for ( int32 i = 0; i < MAX_POLYBUNCHES; i++ )
	{
		if ( i == MAX_POLYBUNCHES - 1 )
			aPolyBunches[i].m_pNext = nil;
		else
			aPolyBunches[i].m_pNext = &aPolyBunches[i + 1];
	}

	for ( int32 i = 0; i < MAX_PERMAMENTSHADOWS; i++ )
	{
		aPermanentShadows[i].m_nType = SHADOWTYPE_NONE;
	}

#ifndef MASTER
	VarConsole.Add("Count polys in shadow", &gbCountPolysInShadow, true);
#endif
}

void
CShadows::Shutdown(void)
{
	ASSERT(gpShadowCarTex != nil);
	ASSERT(gpShadowPedTex != nil);
	ASSERT(gpShadowHeliTex != nil);
	ASSERT(gpShadowBikeTex != nil);
	ASSERT(gpShadowBaronTex != nil);
	ASSERT(gpShadowExplosionTex != nil);
	ASSERT(gpShadowHeadLightsTex != nil);
	ASSERT(gpOutline1Tex != nil);
	ASSERT(gpOutline2Tex != nil);
	ASSERT(gpOutline3Tex != nil);
	ASSERT(gpBloodPoolTex != nil);
	//ASSERT(gpReflectionTex != nil);
	ASSERT(gpWalkDontTex != nil);
	//ASSERT(gpCrackedGlassTex != nil);
	ASSERT(gpPostShadowTex != nil);

	RwTextureDestroy(gpShadowCarTex);
	RwTextureDestroy(gpShadowPedTex);
	RwTextureDestroy(gpShadowHeliTex);
	RwTextureDestroy(gpShadowBikeTex);
	RwTextureDestroy(gpShadowBaronTex);
	RwTextureDestroy(gpShadowExplosionTex);
	RwTextureDestroy(gpShadowHeadLightsTex);
	RwTextureDestroy(gpOutline1Tex);
	RwTextureDestroy(gpOutline2Tex);
	RwTextureDestroy(gpOutline3Tex);
	RwTextureDestroy(gpBloodPoolTex);
	//RwTextureDestroy(gpReflectionTex);
	RwTextureDestroy(gpWalkDontTex);
	//RwTextureDestroy(gpCrackedGlassTex);
	RwTextureDestroy(gpPostShadowTex);
}

void
CShadows::AddPermanentShadow(uint8 ShadowType, RwTexture *pTexture, CVector *pPosn,
							float fFrontX, float fFrontY, float fSideX, float fSideY,
							int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
							float fZDistance, uint32 nTime, float fScale)
{
	ASSERT(pTexture != nil);
	ASSERT(pPosn != nil);


	// find free slot
	int32 nSlot = 0;
	while ( nSlot < MAX_PERMAMENTSHADOWS && aPermanentShadows[nSlot].m_nType != SHADOWTYPE_NONE )
		nSlot++;

	if ( nSlot < MAX_PERMAMENTSHADOWS )
	{
		aPermanentShadows[nSlot].m_nType        = ShadowType;
		aPermanentShadows[nSlot].m_pTexture     = pTexture;
		aPermanentShadows[nSlot].m_vecPos       = *pPosn;
		aPermanentShadows[nSlot].m_vecFront.x   = fFrontX;
		aPermanentShadows[nSlot].m_vecFront.y   = fFrontY;
		aPermanentShadows[nSlot].m_vecSide.x    = fSideX;
		aPermanentShadows[nSlot].m_vecSide.y    = fSideY;
		aPermanentShadows[nSlot].m_nIntensity   = nIntensity;
		aPermanentShadows[nSlot].m_nRed         = nRed;
		aPermanentShadows[nSlot].m_nGreen       = nGreen;
		aPermanentShadows[nSlot].m_nBlue        = nBlue;
		aPermanentShadows[nSlot].m_fZDistance   = fZDistance;
		aPermanentShadows[nSlot].m_nLifeTime    = nTime;
		aPermanentShadows[nSlot].m_nTimeCreated = CTimer::GetTimeInMilliseconds();
	}
}

bool
CShadows::StoreStaticShadow(uint32 nID, uint8 ShadowType, RwTexture *pTexture, Const CVector *pPosn,
							float fFrontX, float fFrontY, float fSideX, float fSideY,
							int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
							float fZDistance, float fScale, float fDrawDistance, bool bTempShadow, float fUpDistance)
{
	ASSERT(pPosn != nil);

	float fDistToCamSqr = (*pPosn - TheCamera.GetPosition()).MagnitudeSqr2D();

	if ( SQR(fDrawDistance) > fDistToCamSqr || fDrawDistance == 0.0f )
	{
		if ( fDrawDistance != 0.0f )
		{
			float fDistToCam = Sqrt(fDistToCamSqr);

			if ( fDistToCam >= (fDrawDistance*(1.0f-(1.0f/4.0f))) )
			{
				//fDistToCam == 0             -> 4
				//fDistToCam == fDrawDistance -> 0
				float fMult = 1.0f - (4.0f / fDrawDistance) * (fDistToCam - (fDrawDistance*(1.0f-(1.0f/4.0f))));

				nIntensity = (int32)(nIntensity * fMult);
				nRed       = (int32)(nRed       * fMult);
				nGreen     = (int32)(nGreen     * fMult);
				nBlue      = (int32)(nBlue      * fMult);
			}
		}

		int32 nSlot;

		nSlot = 0;
		while ( nSlot < MAX_STATICSHADOWS && !(nID == aStaticShadows[nSlot].m_nId && aStaticShadows[nSlot].m_pPolyBunch != nil) )
			nSlot++;

		if ( nSlot < MAX_STATICSHADOWS )
		{
			if (   Abs(pPosn->x - aStaticShadows[nSlot].m_vecPosn.x) < fUpDistance
				&& Abs(pPosn->y - aStaticShadows[nSlot].m_vecPosn.y) < fUpDistance )
			{
				aStaticShadows[nSlot].m_bJustCreated     = true;
				aStaticShadows[nSlot].m_nType            = ShadowType;
				aStaticShadows[nSlot].m_pTexture         = pTexture;
				aStaticShadows[nSlot].m_nIntensity       = nIntensity;
				aStaticShadows[nSlot].m_nRed             = nRed;
				aStaticShadows[nSlot].m_nGreen           = nGreen;
				aStaticShadows[nSlot].m_nBlue            = nBlue;
				aStaticShadows[nSlot].m_fZDistance       = fZDistance;
				aStaticShadows[nSlot].m_fScale           = fScale;
				aStaticShadows[nSlot].m_bTemp            = bTempShadow;
				aStaticShadows[nSlot].m_nTimeCreated     = CTimer::GetTimeInMilliseconds();
				
				return true;
			}
			else if (  Abs(pPosn->x - aStaticShadows[nSlot].m_vecPosn.x) < 0.05f
					&& Abs(pPosn->y - aStaticShadows[nSlot].m_vecPosn.y) < 0.05f
					&& Abs(pPosn->z - aStaticShadows[nSlot].m_vecPosn.z) < 2.0f

					&& fFrontX == aStaticShadows[nSlot].m_vecFront.x
					&& fFrontY == aStaticShadows[nSlot].m_vecFront.y
					&& fSideX  == aStaticShadows[nSlot].m_vecSide.x
					&& fSideY  == aStaticShadows[nSlot].m_vecSide.y )
			{
				aStaticShadows[nSlot].m_bJustCreated     = true;
				aStaticShadows[nSlot].m_nType            = ShadowType;
				aStaticShadows[nSlot].m_pTexture         = pTexture;
				aStaticShadows[nSlot].m_nIntensity       = nIntensity;
				aStaticShadows[nSlot].m_nRed             = nRed;
				aStaticShadows[nSlot].m_nGreen           = nGreen;
				aStaticShadows[nSlot].m_nBlue            = nBlue;
				aStaticShadows[nSlot].m_fZDistance       = fZDistance;
				aStaticShadows[nSlot].m_fScale           = fScale;
				aStaticShadows[nSlot].m_bTemp            = bTempShadow;
				aStaticShadows[nSlot].m_nTimeCreated     = CTimer::GetTimeInMilliseconds();
				
				return true;
			}
			else
			{
				aStaticShadows[nSlot].Free();

				aStaticShadows[nSlot].m_nId              = nID;
				aStaticShadows[nSlot].m_nType            = ShadowType;
				aStaticShadows[nSlot].m_pTexture         = pTexture;
				aStaticShadows[nSlot].m_nIntensity       = nIntensity;
				aStaticShadows[nSlot].m_nRed             = nRed;
				aStaticShadows[nSlot].m_nGreen           = nGreen;
				aStaticShadows[nSlot].m_nBlue            = nBlue;
				aStaticShadows[nSlot].m_fZDistance       = fZDistance;
				aStaticShadows[nSlot].m_fScale           = fScale;
				aStaticShadows[nSlot].m_vecPosn          = *pPosn;
				aStaticShadows[nSlot].m_vecFront.x       = fFrontX;
				aStaticShadows[nSlot].m_vecFront.y       = fFrontY;
				aStaticShadows[nSlot].m_vecSide.x        = fSideX;
				aStaticShadows[nSlot].m_vecSide.y        = fSideY;
				aStaticShadows[nSlot].m_bJustCreated     = true;
				aStaticShadows[nSlot].m_bTemp            = bTempShadow;
				aStaticShadows[nSlot].m_nTimeCreated     = CTimer::GetTimeInMilliseconds();

				GeneratePolysForStaticShadow(nSlot);
				
				return aStaticShadows[nSlot].m_pPolyBunch != nil;
			}
		}
		else
		{
			nSlot = 0;
			while ( nSlot < MAX_STATICSHADOWS && aStaticShadows[nSlot].m_pPolyBunch != nil )
				nSlot++;

			if ( nSlot != MAX_STATICSHADOWS )
			{
				aStaticShadows[nSlot].m_nId              = nID;
				aStaticShadows[nSlot].m_nType            = ShadowType;
				aStaticShadows[nSlot].m_pTexture         = pTexture;
				aStaticShadows[nSlot].m_nIntensity       = nIntensity;
				aStaticShadows[nSlot].m_nRed             = nRed;
				aStaticShadows[nSlot].m_nGreen           = nGreen;
				aStaticShadows[nSlot].m_nBlue            = nBlue;
				aStaticShadows[nSlot].m_fZDistance       = fZDistance;
				aStaticShadows[nSlot].m_fScale           = fScale;
				aStaticShadows[nSlot].m_vecPosn          = *pPosn;
				aStaticShadows[nSlot].m_vecFront.x       = fFrontX;
				aStaticShadows[nSlot].m_vecFront.y       = fFrontY;
				aStaticShadows[nSlot].m_vecSide.x        = fSideX;
				aStaticShadows[nSlot].m_vecSide.y        = fSideY;
				aStaticShadows[nSlot].m_bJustCreated     = true;
				aStaticShadows[nSlot].m_bTemp            = bTempShadow;
				aStaticShadows[nSlot].m_nTimeCreated     = CTimer::GetTimeInMilliseconds();

				GeneratePolysForStaticShadow(nSlot);
				
				return aStaticShadows[nSlot].m_pPolyBunch != nil;
			}
		}
	}
	
	return true;
}

void
CShadows::StoreShadowToBeRendered(uint8 ShadowTexture, CVector *pPosn,
								float fFrontX, float fFrontY, float fSideX, float fSideY,
								int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue)
{
	ASSERT(pPosn != nil);

	switch ( ShadowTexture )
	{
		case SHADOWTEX_NONE:
		{
			break;
		}

		case SHADOWTEX_CAR:
		{
			StoreShadowToBeRendered(SHADOWTYPE_DARK, gpShadowCarTex, pPosn,
					fFrontX, fFrontY, fSideX, fSideY,
					nIntensity, nRed, nGreen, nBlue,
					15.0f, false, 1.0f, nil, false);

			break;
		}

		case SHADOWTEX_PED:
		{
			StoreShadowToBeRendered(SHADOWTYPE_DARK, gpShadowPedTex, pPosn,
					fFrontX, fFrontY, fSideX, fSideY,
					nIntensity, nRed, nGreen, nBlue,
					15.0f, false, 1.0f, nil, false);

			break;
		}

		case SHADOWTEX_EXPLOSION:
		{
			StoreShadowToBeRendered(SHADOWTYPE_ADDITIVE, gpShadowExplosionTex, pPosn,
					fFrontX, fFrontY, fSideX, fSideY,
					nIntensity, nRed, nGreen, nBlue,
					15.0f, false, 1.0f, nil, false);

			break;
		}

		case SHADOWTEX_HELI:
		{
			StoreShadowToBeRendered(SHADOWTYPE_DARK, gpShadowHeliTex, pPosn,
					fFrontX, fFrontY, fSideX, fSideY,
					nIntensity, nRed, nGreen, nBlue,
					15.0f, false, 1.0f, nil, false);

			break;
		}

		case SHADOWTEX_HEADLIGHTS:
		{
			StoreShadowToBeRendered(SHADOWTYPE_ADDITIVE, gpShadowHeadLightsTex, pPosn,
					fFrontX, fFrontY, fSideX, fSideY,
					nIntensity, nRed, nGreen, nBlue,
					15.0f, false, 1.0f, nil, false);

			break;
		}

		case SHADOWTEX_BLOOD:
		{
			StoreShadowToBeRendered(SHADOWTYPE_DARK, gpBloodPoolTex, pPosn,
					fFrontX, fFrontY, fSideX, fSideY,
					nIntensity, nRed, 150, 0,
					15.0f, false, 1.0f, nil, false);

			break;
		}
	}

	//ASSERT(false);
}

void
CShadows::StoreShadowToBeRendered(uint8 ShadowType, RwTexture *pTexture, CVector *pPosn,
								float fFrontX, float fFrontY, float fSideX, float fSideY,
								int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
								float fZDistance, bool bDrawOnWater, float fScale, CCutsceneShadow *pShadow, bool bDrawOnBuildings)
{
	ASSERT(pTexture != nil);
	ASSERT(pPosn != nil);

	if ( ShadowsStoredToBeRendered < MAX_STOREDSHADOWS )
	{
		asShadowsStored[ShadowsStoredToBeRendered].m_ShadowType              = ShadowType;
		asShadowsStored[ShadowsStoredToBeRendered].m_pTexture                = pTexture;
		asShadowsStored[ShadowsStoredToBeRendered].m_vecPos                  = *pPosn;
		asShadowsStored[ShadowsStoredToBeRendered].m_vecFront.x              = fFrontX;
		asShadowsStored[ShadowsStoredToBeRendered].m_vecFront.y              = fFrontY;
		asShadowsStored[ShadowsStoredToBeRendered].m_vecSide.x               = fSideX;
		asShadowsStored[ShadowsStoredToBeRendered].m_vecSide.y               = fSideY;
		asShadowsStored[ShadowsStoredToBeRendered].m_nIntensity              = nIntensity;
		asShadowsStored[ShadowsStoredToBeRendered].m_nRed                    = nRed;
		asShadowsStored[ShadowsStoredToBeRendered].m_nGreen                  = nGreen;
		asShadowsStored[ShadowsStoredToBeRendered].m_nBlue                   = nBlue;
		asShadowsStored[ShadowsStoredToBeRendered].m_fZDistance              = fZDistance;
		asShadowsStored[ShadowsStoredToBeRendered].m_nFlags.bDrawOnWater     = bDrawOnWater;
		asShadowsStored[ShadowsStoredToBeRendered].m_nFlags.bDrawOnBuildings = bDrawOnBuildings;
		asShadowsStored[ShadowsStoredToBeRendered].m_fScale                  = fScale;
		asShadowsStored[ShadowsStoredToBeRendered].m_pCutsceneShadow         = pShadow;

		ShadowsStoredToBeRendered++;
	}
}


void
CShadows::StoreShadowForVehicle(CVehicle *pCar, VEH_SHD_TYPE type)
{
	ASSERT(pCar != nil);

	if ( CTimeCycle::GetShadowStrength() != 0 )
	{
		CVector CarPos = pCar->GetPosition();
		float fDistToCamSqr = (CarPos - TheCamera.GetPosition()).MagnitudeSqr2D();

		if ( CCutsceneMgr::IsRunning() )
			fDistToCamSqr /= SQR(TheCamera.LODDistMultiplier) * 4.0f;

		float fDrawDistance;
		switch ( type )
		{
			case VEH_SHD_TYPE_SEAPLANE:
			case VEH_SHD_TYPE_RCPLANE:
				fDrawDistance = 144.0f;
				break;
				
			case VEH_SHD_TYPE_HELI:
				fDrawDistance = 144.0f;
				break;
				
			default:
				fDrawDistance = 18.0f;
				break;
		}

		if ( fDistToCamSqr < SQR(fDrawDistance) )
		{
			float fDistToCam = Sqrt(fDistToCamSqr);
			
			//fDistToCam == 0             -> 4
			//fDistToCam == fDrawDistance -> 0
			float fMult = 1.0f - (fDistToCam - (fDrawDistance*(1.0f-(1.0f/4.0f)))) / (fDrawDistance*(1.0f/4.0f));

			int32 nColorStrength;

			if ( fDistToCam >= (fDrawDistance*(1.0f-(1.0f/4.0f))) )
				nColorStrength = (int32)(fMult * CTimeCycle::GetShadowStrength());
			else
				nColorStrength = CTimeCycle::GetShadowStrength();
			
			
			float fVehicleHeight  = pCar->GetColModel()->boundingBox.GetSize().y;
			float fVehicleWidth   = pCar->GetColModel()->boundingBox.GetSize().x;
			
			float size = 1.0f;
			
			switch ( pCar->GetModelIndex() )
			{
				case MI_PIZZABOY:
				case MI_PCJ600:
				case MI_FAGGIO:
				{
					fVehicleHeight *= 1.2f;
					size = 0.05f;
					break;
				}

				case MI_ANGEL:
				case MI_FREEWAY:
				case MI_SANCHEZ:
				{
					fVehicleHeight *= 1.5f;
					size *= 0.03f;
					break;
				}

				case MI_HUNTER:
				case MI_SEASPAR:
				case MI_SPARROW:
				case MI_MAVERICK:
				case MI_VCNMAV:
				case MI_POLMAV:
				{
					fVehicleWidth *= 3.0f;
					fVehicleHeight *= 1.4f;
					size *= 0.5f;
					break;
				}

				case MI_RCGOBLIN:
				case MI_RCRAIDER:
				{
					fVehicleHeight *= 1.5f;
					fVehicleWidth *= 2.0f;
					size *= 0.2f;
					break;
				}

				case MI_DODO:
				{
					fVehicleHeight *= 0.9f;
					fVehicleWidth *= 0.4f;
					break;
				}
			}

			
			CarPos.x -= pCar->GetForward().x * (((fVehicleHeight/2) - pCar->GetColModel()->boundingBox.max.y)*size);
			CarPos.y -= pCar->GetForward().y * (((fVehicleHeight/2) - pCar->GetColModel()->boundingBox.max.y)*size);
			
			RwTexture *tex = gpShadowCarTex;
			switch ( type )
			{
				case VEH_SHD_TYPE_BIKE:
				{
					float wheelZ = Abs(((CBike*)pCar)->m_fLeanLRAngle);
					float mul = 5.092958f * wheelZ + 1.0f;
					if (pCar->GetStatus() == STATUS_PHYSICS)
					{
						float z = pCar->GetRight().z;
						if (z > 0.6f)
							mul += 4.0f * z;
					}
					fVehicleWidth *= mul;
					tex = gpShadowBikeTex;
					break;
				}
				
				case VEH_SHD_TYPE_HELI:
					tex = gpShadowHeliTex;
					break;
				
				case VEH_SHD_TYPE_SEAPLANE:
					nColorStrength = CTimeCycle::GetShadowStrength();
					tex = gpShadowBaronTex;
					break;
				
				case VEH_SHD_TYPE_RCPLANE:
					tex = gpShadowBaronTex;
					fVehicleHeight *= 1.5f;
					fVehicleWidth  *= 2.2f;
					break;
				
				case VEH_SHD_TYPE_CAR:
					tex = gpShadowCarTex;
					break;
			}
			
			float frontx = pCar->GetForward().x;
			float fronty = pCar->GetForward().y;
			float sidex  = pCar->GetRight().x;
			float sidey  = pCar->GetRight().y;
			
			switch ( type )
			{
				case VEH_SHD_TYPE_BIKE:
					if ( Abs(pCar->GetRight().z) > 0.6f )
					{
						sidex = pCar->GetUp().x;
						sidey = pCar->GetUp().y;
					}
					break;
					
				case VEH_SHD_TYPE_HELI:
					if ( Abs(pCar->GetRight().z) > 0.57f )
					{
						sidex = pCar->GetUp().x;
						sidey = pCar->GetUp().y;
					}
					if ( Abs(pCar->GetForward().z) > 0.57f )
					{
						frontx = pCar->GetUp().x;
						fronty = pCar->GetUp().y;
					}
					break;
			}

			bool bDrawOnBuildings = false;
			if (   pCar->GetModelIndex() == MI_RCBANDIT
				|| pCar->GetModelIndex() == MI_RCBARON
				|| pCar->GetModelIndex() == MI_RCRAIDER
				|| pCar->GetModelIndex() == MI_RCGOBLIN
				|| pCar == FindPlayerVehicle() )
			{
				bDrawOnBuildings = true;
			}
			
			if ( pCar->m_vecMoveSpeed.Magnitude() * CTimeStep::ms_fTimeStep > 0.1f || bDrawOnBuildings )
			{
				if ( pCar->GetUp().z > 0.0f )
				{
					StoreShadowToBeRendered(SHADOWTYPE_DARK, tex, &CarPos,
						frontx * (fVehicleHeight / 2),
						fronty * (fVehicleHeight / 2),
						sidex  * (fVehicleWidth  / 2),
						sidey  * (fVehicleWidth  / 2),
						nColorStrength, nColorStrength, nColorStrength, nColorStrength,
						4.5f, false, 1.0f, nil, bDrawOnBuildings);
				}
				else
				{
					StoreShadowToBeRendered(SHADOWTYPE_DARK, tex, &CarPos,
						frontx * (fVehicleHeight / 2),
						fronty * (fVehicleHeight / 2),
						-sidex * (fVehicleWidth  / 2),
						-sidey * (fVehicleWidth  / 2),
						nColorStrength, nColorStrength, nColorStrength, nColorStrength,
						4.5f, false, 1.0f, nil, bDrawOnBuildings);
				}
			}
			else
			{
				if ( pCar->GetUp().z > 0.0f )
				{
					StoreStaticShadow((uintptr)pCar + 1, SHADOWTYPE_DARK, tex, &CarPos,
						frontx * (fVehicleHeight / 2),
						fronty * (fVehicleHeight / 2),
						sidex  * (fVehicleWidth  / 2),
						sidey  * (fVehicleWidth  / 2),
						nColorStrength, nColorStrength, nColorStrength, nColorStrength,
						4.5f, 1.0f, 0.0f, false, 0.1f);
				}
				else
				{
					StoreStaticShadow((uintptr)pCar + 1, SHADOWTYPE_DARK, tex, &CarPos,
						frontx * (fVehicleHeight / 2),
						fronty * (fVehicleHeight / 2),
						-sidex * (fVehicleWidth  / 2),
						-sidey * (fVehicleWidth  / 2),
						nColorStrength, nColorStrength, nColorStrength, nColorStrength,
						4.5f, 1.0f, 0.0f, false, 0.1f);
				}
			}
		}
	}
}

void
CShadows::StoreCarLightShadow(CVehicle *pCar, int32 nID, RwTexture *pTexture, CVector *pPosn,
							float fFrontX, float fFrontY, float fSideX, float fSideY, uint8 nRed, uint8 nGreen, uint8 nBlue,
							float fMaxViewAngle, bool arg1, float arg2, float arg3)
{
	ASSERT(pCar != nil);
	ASSERT(pPosn != nil);

	float fDistToCamSqr = (*pPosn - TheCamera.GetPosition()).MagnitudeSqr2D();

	bool bSpecialCam =     TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_TOPDOWN
						|| TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_TOP_DOWN_PED
						|| CCutsceneMgr::IsRunning();

	float fDrawDistance = 27.0f;

	if ( fDistToCamSqr < SQR(fDrawDistance) || bSpecialCam )
	{
		if ( bSpecialCam || DotProduct2D(CVector2D(TheCamera.CamFrontXNorm, TheCamera.CamFrontYNorm),
											*pPosn - TheCamera.GetPosition() ) > -fMaxViewAngle )
		{
			float fDistToCam = Sqrt(fDistToCamSqr);

			if ( fDistToCam >= (fDrawDistance*(1.0f-(1.0f/4.0f))) && !bSpecialCam ) // BUG? must be 3.0?
			{
				//fDistToCam == 0             -> 3
				//fDistToCam == fDrawDistance -> 0
				float fMult = 1.0f - (3.0f / fDrawDistance) * (fDistToCam - (fDrawDistance*(1.0f-(1.0f/3.0f))) );

				nRed   = (int32)(nRed   * fMult);
				nGreen = (int32)(nGreen * fMult);
				nBlue  = (int32)(nBlue  * fMult);
			}

			if ( pCar->m_vecMoveSpeed.Magnitude() * CTimeStep::ms_fTimeStep > 0.4f || pCar == FindPlayerVehicle() )
			{
				StoreShadowToBeRendered(SHADOWTYPE_ADDITIVE, pTexture, pPosn,
						fFrontX, fFrontY,
						fSideX, fSideY,
						128, nRed, nGreen, nBlue,
						6.0f, false, 1.0f,
						nil, pCar == FindPlayerVehicle());
			}
			else
			{
				StoreStaticShadow((uintptr)pCar + nID, SHADOWTYPE_ADDITIVE, pTexture, pPosn,
						fFrontX, fFrontY,
						fSideX, fSideY,
						128, nRed, nGreen, nBlue,
						6.0f, 1.0f, 27.0f,
						false, 0.4f);
			}
		}
	}
}


#ifdef USE_CUTSCENE_SHADOW_FOR_PED
void
StoreShadowForCutscenePedObject(CPed *pObject, float fDisplacementX, float fDisplacementY,
								float fFrontX, float fFrontY, float fSideX, float fSideY)
{
	ASSERT(pObject != nil);
	
	CCutsceneShadow *shadow = pObject->m_pRTShadow;
	
	if ( shadow == nil )
		return;
	
	if ( !shadow->IsInitialized() )
		return;
	
	CVector pos = pObject->GetPosition();
	
	float fDistToCamSqr = (pos - TheCamera.GetPosition()).MagnitudeSqr2D();
	
	float fDrawDistance = 100.0f;
	
	if ( fDistToCamSqr < SQR(fDrawDistance*0.5f) )
	{
		if ( (CEntity*)pObject == FindPlayerPed() || TheCamera.IsSphereVisible(pos, 2.0f) )
		{
			float fDistToCam = Sqrt(fDistToCamSqr);
			
			float fMult = 1.0f - (4.0f / fDrawDistance) * (fDistToCam - (fDrawDistance*(1.0f/4.0f)));
			int32 nColorStrength;

			if ( fDistToCam >= (fDrawDistance*(1.0f/4.0f)) )
				nColorStrength = (int32)(CTimeCycle::GetShadowStrength() * fMult);
			else
				nColorStrength = CTimeCycle::GetShadowStrength();

			int32 color = int32(nColorStrength * 0.8f);
			
			pos.x += fDisplacementX;
			pos.y += fDisplacementY;
			
			RwTexture *texture = shadow->GetShadowRwTexture();
			ASSERT(texture);
			RwRGBA bordercolor = {0, 0, 0, 0};
			shadow->DrawBorderAroundTexture(bordercolor);
			
			pos.x -= fDisplacementX;
			pos.y -= fDisplacementY;
			
			float angleY = 360.0f - RADTODEG((CClock::ms_nGameClockMinutes
					+60*CClock::ms_nGameClockHours+CClock::ms_nGameClockSeconds/60)*(HALFPI/360.0f));
			 
			RwFrame *frame = shadow->SetLightProperties(angleY, -85.0f, true);
			ASSERT(frame);
			CVector at(RwFrameGetMatrix(frame)->at);
			at.Normalise();
			
			CShadows::CalcPedShadowValues(at, &fFrontX, &fFrontY, &fSideX, &fSideY, &fDisplacementX, &fDisplacementY);
			
			pos.x -= 2.5f * fDisplacementX;
			pos.y -= 2.5f * fDisplacementY;
			
			CShadows::StoreShadowToBeRendered(SHADOWTYPE_INVCOLOR, texture, &pos,
				fFrontX * 1.5f, fFrontY * 1.5f,
				fSideX  * 1.5f, fSideY  * 1.5f,
				color, color, color, color,
				4.0f, false, 1.0f, shadow, false);
		}
	}
}
#endif


void
CShadows::StoreShadowForPed(CPed *pPed, float fDisplacementX, float fDisplacementY,
							float fFrontX, float fFrontY, float fSideX, float fSideY)
{
	ASSERT(pPed != nil);

	if ( pPed->bIsVisible )
	{
		if ( !(pPed->bInVehicle && pPed->m_nPedState != PED_DRAG_FROM_CAR && pPed->m_nPedState != PED_EXIT_CAR) )
		{
			if ( CTimeCycle::GetShadowStrength() != 0 )
			{
#ifdef USE_CUTSCENE_SHADOW_FOR_PED
					CCutsceneShadow *pShadow = pPed->m_pRTShadow;
				
					if (pShadow)
					{
						if (pShadow->IsInitialized())
							pShadow->UpdateForCutscene();
						::StoreShadowForCutscenePedObject(pPed, fDisplacementX, fDisplacementY, fFrontX, fFrontY, fSideX, fSideY);
					}
					
					return;
#endif

				StoreShadowForPedObject(pPed,
					fDisplacementX, fDisplacementY,
					fFrontX, fFrontY,
					fSideX, fSideY);
			}
		}
	}
}

void
CShadows::StoreShadowForPedObject(CEntity *pPedObject, float fDisplacementX, float fDisplacementY,
								float fFrontX, float fFrontY, float fSideX, float fSideY)
{	
	ASSERT(pPedObject != nil);

	CVector PedPos = pPedObject->GetPosition();

	float fDistToCamSqr = (PedPos - TheCamera.GetPosition()).MagnitudeSqr2D();

	float fDrawDistance = 26.0f;

	if ( fDistToCamSqr < SQR(fDrawDistance*0.5f) )
	{
		if ( pPedObject == FindPlayerPed() || TheCamera.IsSphereVisible(PedPos, 2.0f) != false )
		{
			float fDistToCam = Sqrt(fDistToCamSqr);

			//fDistToCam == 0             ->  2
			//fDistToCam == fDrawDistance -> -2
			float fMult = 1.0f - (4.0f / fDrawDistance) * (fDistToCam - (fDrawDistance*(1.0f/4.0f))); // BUG ? negative
			int32 nColorStrength;

			if ( fDistToCam >= (fDrawDistance*(1.0f/4.0f)) ) // BUG ? negative
				nColorStrength = (int32)(CTimeCycle::GetShadowStrength() * fMult);
			else
				nColorStrength = CTimeCycle::GetShadowStrength();

			PedPos.x += fDisplacementX;
			PedPos.y += fDisplacementY;

			StoreShadowToBeRendered(SHADOWTYPE_DARK, gpShadowPedTex, &PedPos,
					fFrontX, fFrontY,
					fSideX, fSideY,
					nColorStrength, nColorStrength, nColorStrength, nColorStrength,
					4.0f, false, 1.0f, nil, pPedObject == FindPlayerPed());
		}
	}
}


void
CShadows::StoreShadowForCutscenePedObject(CCutsceneObject *pObject, float fDisplacementX, float fDisplacementY,
								float fFrontX, float fFrontY, float fSideX, float fSideY)
{
#ifdef DISABLE_CUTSCENE_SHADOWS
	return;
#endif
	ASSERT(pObject != nil);
	
	CCutsceneShadow *shadow = pObject->m_pShadow;
	
	if ( shadow == nil )
		return;
	
	if ( !shadow->IsInitialized() )
		return;
	
	CVector pos = pObject->GetPosition();
	
	float fDistToCamSqr = (pos - TheCamera.GetPosition()).MagnitudeSqr2D();
	
	float fDrawDistance = 100.0f;
	
	if ( fDistToCamSqr < SQR(fDrawDistance*0.5f) )
	{
		if ( (CEntity*)pObject == FindPlayerPed() || TheCamera.IsSphereVisible(pos, 2.0f) )
		{
			float fDistToCam = Sqrt(fDistToCamSqr);
			
			float fMult = 1.0f - (4.0f / fDrawDistance) * (fDistToCam - (fDrawDistance*(1.0f/4.0f)));
			int32 nColorStrength;

			if ( fDistToCam >= (fDrawDistance*(1.0f/4.0f)) )
				nColorStrength = (int32)(CTimeCycle::GetShadowStrength() * fMult);
			else
				nColorStrength = CTimeCycle::GetShadowStrength();

			int32 color = int32(nColorStrength * 0.8f);
			
			pos.x += fDisplacementX;
			pos.y += fDisplacementY;
			
			RwTexture *texture = shadow->GetShadowRwTexture();
			ASSERT(texture);
			RwRGBA bordercolor = {0, 0, 0, 0};
			shadow->DrawBorderAroundTexture(bordercolor);
			
			pos.x -= fDisplacementX;
			pos.y -= fDisplacementY;
			
			float angleY = 360.0f - RADTODEG((CClock::ms_nGameClockMinutes+60*
					CClock::ms_nGameClockHours+CClock::ms_nGameClockSeconds/60)*(HALFPI/360.0f));
			 
			RwFrame *frame = shadow->SetLightProperties(angleY, -85.0f, true);
			ASSERT(frame);
			CVector at(RwFrameGetMatrix(frame)->at);
			at.Normalise();
			
			CalcPedShadowValues(at, &fFrontX, &fFrontY, &fSideX, &fSideY, &fDisplacementX, &fDisplacementY);
			
			pos.x -= 2.5f * fDisplacementX;
			pos.y -= 2.5f * fDisplacementY;
			
			StoreShadowToBeRendered(SHADOWTYPE_INVCOLOR, texture, &pos,
				fFrontX * 1.5f, fFrontY * 1.5f,
				fSideX  * 1.5f, fSideY  * 1.5f,
				color, color, color, color,
				4.0f, false, 1.0f, shadow, false);
		}
	}
}

void
CShadows::StoreShadowForTree(CEntity *pTree)
{
	ASSERT(pTree != nil);
}


void
CShadows::StoreShadowForPole(CEntity *pPole, float fOffsetX, float fOffsetY, float fOffsetZ,
								float fPoleHeight, float fPoleWidth, uint32 nID)
{
	ASSERT(pPole != nil);

	if ( CTimeCycle::GetShadowStrength() != 0 )
	{
		if ( pPole->GetUp().z < 0.5f )
			return;

		CVector PolePos = pPole->GetPosition();

		PolePos.x += fOffsetX * pPole->GetRight().x + fOffsetY * pPole->GetForward().x;
		PolePos.y += fOffsetX * pPole->GetRight().y + fOffsetY * pPole->GetForward().y;
		PolePos.z += fOffsetZ;

		PolePos.x += -CTimeCycle::GetSunDirection().x * (fPoleHeight / 2);
		PolePos.y += -CTimeCycle::GetSunDirection().y * (fPoleHeight / 2);

		StoreStaticShadow((uintptr)pPole + nID + _TODOCONST(51), SHADOWTYPE_DARK, gpPostShadowTex, &PolePos,
				-CTimeCycle::GetSunDirection().x * (fPoleHeight / 2),
				-CTimeCycle::GetSunDirection().y * (fPoleHeight / 2),
				CTimeCycle::GetShadowSideX()    * fPoleWidth,
				CTimeCycle::GetShadowSideY()    * fPoleWidth,
				2 * (int32)((pPole->GetUp().z - 0.5f) * CTimeCycle::GetShadowStrength() * 2.0f) / 3,
				0, 0, 0,
				15.0f, 1.0f, 40.0f, false, 0.0f);
	}
}

void
CShadows::SetRenderModeForShadowType(uint8 ShadowType)
{
	switch ( ShadowType )
	{
		case SHADOWTYPE_DARK:
		{
			RwRenderStateSet(rwRENDERSTATESRCBLEND,  (void *)rwBLENDSRCALPHA);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
			break;
		}

		case SHADOWTYPE_ADDITIVE:
		{
			RwRenderStateSet(rwRENDERSTATESRCBLEND,  (void *)rwBLENDONE);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDONE);
			break;
		}

		case SHADOWTYPE_INVCOLOR:
		{
			RwRenderStateSet(rwRENDERSTATESRCBLEND,  (void *)rwBLENDZERO);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCCOLOR);
			break;
		}
	}
}


void
CShadows::RenderStoredShadows(void)
{
	PUSH_RENDERGROUP("CShadows::RenderStoredShadows");

	RenderBuffer::ClearRenderBuffer();

	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,    (void *)rwTEXTUREADDRESSCLAMP);


	for ( int32 i = 0; i < ShadowsStoredToBeRendered; i++ )
		asShadowsStored[i].m_nFlags.bRendered = false;


	for ( int32 i = 0; i < ShadowsStoredToBeRendered; i++ )
	{
		if ( !asShadowsStored[i].m_nFlags.bRendered )
		{
			SetRenderModeForShadowType(asShadowsStored[i].m_ShadowType);

			ASSERT(asShadowsStored[i].m_pTexture != nil);

			RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(asShadowsStored[i].m_pTexture));

			for ( int32 j = i; j < ShadowsStoredToBeRendered; j++ )
			{
				if ( asShadowsStored[i].m_ShadowType   == asShadowsStored[j].m_ShadowType
					&& asShadowsStored[i].m_pTexture == asShadowsStored[j].m_pTexture )
				{
					float fWidth  = Abs(asShadowsStored[j].m_vecFront.x) + Abs(asShadowsStored[j].m_vecSide.x);
					float fHeight = Abs(asShadowsStored[j].m_vecFront.y) + Abs(asShadowsStored[j].m_vecSide.y);

					CVector shadowPos = asShadowsStored[j].m_vecPos;

					float fStartX = shadowPos.x - fWidth;
					float fEndX   = shadowPos.x + fWidth;
					float fStartY = shadowPos.y - fHeight;
					float fEndY   = shadowPos.y + fHeight;

					int32 nStartX = Max(CWorld::GetSectorIndexX(fStartX), 0);
					int32 nStartY = Max(CWorld::GetSectorIndexY(fStartY), 0);
					int32 nEndX   = Min(CWorld::GetSectorIndexX(fEndX), NUMSECTORS_X-1);
					int32 nEndY   = Min(CWorld::GetSectorIndexY(fEndY), NUMSECTORS_Y-1);

					CWorld::AdvanceCurrentScanCode();

					for ( int32 y = nStartY; y <= nEndY; y++ )
					{
						for ( int32 x = nStartX; x <= nEndX; x++ )
						{
							CSector *pCurSector = CWorld::GetSector(x, y);

							ASSERT(pCurSector != nil);
							
							if ( asShadowsStored[j].m_pCutsceneShadow )
							{
								CastCutsceneShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS],
										fStartX, fStartY,
										fEndX, fEndY,
										&shadowPos,
										asShadowsStored[j].m_vecFront.x,
										asShadowsStored[j].m_vecFront.y,
										asShadowsStored[j].m_vecSide.x,
										asShadowsStored[j].m_vecSide.y,
										asShadowsStored[j].m_nIntensity,
										asShadowsStored[j].m_nRed,
										asShadowsStored[j].m_nGreen,
										asShadowsStored[j].m_nBlue,
										asShadowsStored[j].m_fZDistance,
										asShadowsStored[j].m_fScale,
										nil,
										asShadowsStored[j].m_pCutsceneShadow);
	
								CastCutsceneShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS_OVERLAP],
										fStartX, fStartY,
										fEndX, fEndY,
										&shadowPos,
										asShadowsStored[j].m_vecFront.x,
										asShadowsStored[j].m_vecFront.y,
										asShadowsStored[j].m_vecSide.x,
										asShadowsStored[j].m_vecSide.y,
										asShadowsStored[j].m_nIntensity,
										asShadowsStored[j].m_nRed,
										asShadowsStored[j].m_nGreen,
										asShadowsStored[j].m_nBlue,
										asShadowsStored[j].m_fZDistance,
										asShadowsStored[j].m_fScale,
										nil,
										asShadowsStored[j].m_pCutsceneShadow);
							}
							else if ( asShadowsStored[j].m_nFlags.bDrawOnBuildings )
							{
								CastPlayerShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS],
										fStartX, fStartY,
										fEndX, fEndY,
										&shadowPos,
										asShadowsStored[j].m_vecFront.x,
										asShadowsStored[j].m_vecFront.y,
										asShadowsStored[j].m_vecSide.x,
										asShadowsStored[j].m_vecSide.y,
										asShadowsStored[j].m_nIntensity,
										asShadowsStored[j].m_nRed,
										asShadowsStored[j].m_nGreen,
										asShadowsStored[j].m_nBlue,
										asShadowsStored[j].m_fZDistance,
										asShadowsStored[j].m_fScale,
										nil);
	
								CastPlayerShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS_OVERLAP],
										fStartX, fStartY,
										fEndX, fEndY,
										&shadowPos,
										asShadowsStored[j].m_vecFront.x,
										asShadowsStored[j].m_vecFront.y,
										asShadowsStored[j].m_vecSide.x,
										asShadowsStored[j].m_vecSide.y,
										asShadowsStored[j].m_nIntensity,
										asShadowsStored[j].m_nRed,
										asShadowsStored[j].m_nGreen,
										asShadowsStored[j].m_nBlue,
										asShadowsStored[j].m_fZDistance,
										asShadowsStored[j].m_fScale,
										nil);
							}
							else
							{
								CastShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS],
										fStartX, fStartY,
										fEndX, fEndY,
										&shadowPos,
										asShadowsStored[j].m_vecFront.x,
										asShadowsStored[j].m_vecFront.y,
										asShadowsStored[j].m_vecSide.x,
										asShadowsStored[j].m_vecSide.y,
										asShadowsStored[j].m_nIntensity,
										asShadowsStored[j].m_nRed,
										asShadowsStored[j].m_nGreen,
										asShadowsStored[j].m_nBlue,
										asShadowsStored[j].m_fZDistance,
										asShadowsStored[j].m_fScale,
										nil);
	
								CastShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS_OVERLAP],
										fStartX, fStartY,
										fEndX, fEndY,
										&shadowPos,
										asShadowsStored[j].m_vecFront.x,
										asShadowsStored[j].m_vecFront.y,
										asShadowsStored[j].m_vecSide.x,
										asShadowsStored[j].m_vecSide.y,
										asShadowsStored[j].m_nIntensity,
										asShadowsStored[j].m_nRed,
										asShadowsStored[j].m_nGreen,
										asShadowsStored[j].m_nBlue,
										asShadowsStored[j].m_fZDistance,
										asShadowsStored[j].m_fScale,
										nil);
							}
						}
					}

					asShadowsStored[j].m_nFlags.bRendered = true;
				}
			}

			RenderBuffer::RenderStuffInBuffer();
		}
	}

	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,    (void *)rwTEXTUREADDRESSWRAP);

	ShadowsStoredToBeRendered = 0;

	POP_RENDERGROUP();
}


void
CShadows::RenderStaticShadows(void)
{
	PUSH_RENDERGROUP("CShadows::RenderStaticShadows");

	RenderBuffer::ClearRenderBuffer();

	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE,         (void *)FALSE);

	SetAlphaTest(0);

	for ( int32 i = 0; i < MAX_STATICSHADOWS; i++ )
		aStaticShadows[i].m_bRendered = false;

	for ( int32 i = 0; i < MAX_STATICSHADOWS; i++ )
	{
		if ( aStaticShadows[i].m_pPolyBunch && !aStaticShadows[i].m_bRendered )
		{
			SetRenderModeForShadowType(aStaticShadows[i].m_nType);
			RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(aStaticShadows[i].m_pTexture));

			// optimization trick, render all shadows with same renderstate and texture
			for ( int32 j = i; j < MAX_STATICSHADOWS; j++ )
			{
				if ( aStaticShadows[j].m_pPolyBunch != nil
						&& aStaticShadows[i].m_nType    == aStaticShadows[j].m_nType
						&& aStaticShadows[i].m_pTexture == aStaticShadows[j].m_pTexture )
				{
					for ( CPolyBunch *bunch = aStaticShadows[j].m_pPolyBunch; bunch != nil; bunch = bunch->m_pNext )
					{
						RwImVertexIndex *pIndexes;
						RwIm3DVertex *pVerts;

						RenderBuffer::StartStoring(3 * (bunch->m_nNumVerts - 2), bunch->m_nNumVerts, &pIndexes, &pVerts);

						ASSERT(pIndexes != nil);
						ASSERT(pVerts != nil);

						for ( int32 k = 0; k < bunch->m_nNumVerts; k++ )
						{
							RwIm3DVertexSetRGBA(&pVerts[k],
									aStaticShadows[j].m_nRed,
									aStaticShadows[j].m_nGreen,
									aStaticShadows[j].m_nBlue,
									(int32)(aStaticShadows[j].m_nIntensity * (1.0f - CWeather::Foggyness * 0.5f)));

							RwIm3DVertexSetU  (&pVerts[k], bunch->m_aU[k] / 200.0f);
							RwIm3DVertexSetV  (&pVerts[k], bunch->m_aV[k] / 200.0f);
							RwIm3DVertexSetPos(&pVerts[k], bunch->m_aVerts[k].x, bunch->m_aVerts[k].y,  bunch->m_aVerts[k].z + 0.03f);
						}

						for ( int32 k = 0; k < 3 * (bunch->m_nNumVerts - 2); k++ )
							pIndexes[k] = ShadowIndexList[k];

						RenderBuffer::StopStoring();
					}

					aStaticShadows[j].m_bRendered = true;
				}
			}

			RenderBuffer::RenderStuffInBuffer();
		}
	}
	RestoreAlphaTest();

	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      (void *)TRUE);

	POP_RENDERGROUP();
}


void
CShadows::GeneratePolysForStaticShadow(int16 nStaticShadowID)
{
	float fWidth  = Abs(aStaticShadows[nStaticShadowID].m_vecFront.x) + Abs(aStaticShadows[nStaticShadowID].m_vecSide.x);
	float fHeight = Abs(aStaticShadows[nStaticShadowID].m_vecFront.y) + Abs(aStaticShadows[nStaticShadowID].m_vecSide.y);

	CVector shadowPos = aStaticShadows[nStaticShadowID].m_vecPosn;

	float fStartX = shadowPos.x - fWidth;
	float fEndX   = shadowPos.x + fWidth;
	float fStartY = shadowPos.y - fHeight;
	float fEndY   = shadowPos.y + fHeight;

	int32 nStartX = Max(CWorld::GetSectorIndexX(fStartX), 0);
	int32 nStartY = Max(CWorld::GetSectorIndexY(fStartY), 0);
	int32 nEndX   = Min(CWorld::GetSectorIndexX(fEndX), NUMSECTORS_X-1);
	int32 nEndY   = Min(CWorld::GetSectorIndexY(fEndY), NUMSECTORS_Y-1);

	CWorld::AdvanceCurrentScanCode();

	for ( int32 y = nStartY; y <= nEndY; y++ )
	{
		for ( int32 x = nStartX; x <= nEndX; x++ )
		{
			CSector *pCurSector = CWorld::GetSector(x, y);

			ASSERT(pCurSector != nil);

			CastShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS],
					fStartX, fStartY,
					fEndX, fEndY,
					&shadowPos,
					aStaticShadows[nStaticShadowID].m_vecFront.x,
					aStaticShadows[nStaticShadowID].m_vecFront.y,
					aStaticShadows[nStaticShadowID].m_vecSide.x,
					aStaticShadows[nStaticShadowID].m_vecSide.y,
					0, 0, 0, 0,
					aStaticShadows[nStaticShadowID].m_fZDistance,
					aStaticShadows[nStaticShadowID].m_fScale,
					&aStaticShadows[nStaticShadowID].m_pPolyBunch);

			CastShadowSectorList(pCurSector->m_lists[ENTITYLIST_BUILDINGS_OVERLAP],
					fStartX, fStartY,
					fEndX, fEndY,
					&shadowPos,
					aStaticShadows[nStaticShadowID].m_vecFront.x,
					aStaticShadows[nStaticShadowID].m_vecFront.y,
					aStaticShadows[nStaticShadowID].m_vecSide.x,
					aStaticShadows[nStaticShadowID].m_vecSide.y,
					0, 0, 0, 0,
					aStaticShadows[nStaticShadowID].m_fZDistance,
					aStaticShadows[nStaticShadowID].m_fScale,
					&aStaticShadows[nStaticShadowID].m_pPolyBunch);
		}
	}
}


void
CShadows::CastShadowSectorList(CPtrList &PtrList, float fStartX, float fStartY, float fEndX, float fEndY, CVector *pPosn,
								float fFrontX, float fFrontY, float fSideX, float fSideY,
								int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
								float fZDistance, float fScale, CPolyBunch **ppPolyBunch)
{
	ASSERT(pPosn != nil);

	CPtrNode *pNode = PtrList.first;

	CRect Bound;

	while ( pNode != nil )
	{
		CEntity *pEntity = (CEntity *)pNode->item;
		uint16 nScanCode = pEntity->m_scanCode;
		pNode = pNode->next;

		ASSERT( pEntity != nil );

		if ( nScanCode != CWorld::GetCurrentScanCode() )
		{
			pEntity->m_scanCode = CWorld::GetCurrentScanCode();
			
			if ( pEntity->bUsesCollision && !pEntity->bDontCastShadowsOn)
			{
				if ( IsAreaVisible(pEntity->m_area) )
				{
					Bound = pEntity->GetBoundRect();
	
					if ( fStartX < Bound.right
						&& fEndX > Bound.left
						&& fStartY < Bound.bottom
						&& fEndY > Bound.top )
					{
						if ( pPosn->z - fZDistance < pEntity->GetPosition().z + pEntity->GetColModel()->boundingBox.max.z
							&& pEntity->GetPosition().z + pEntity->GetColModel()->boundingBox.min.z < pPosn->z )
						{
							CastShadowEntityXY(pEntity,
								fStartX, fStartY,
								fEndX, fEndY,
								pPosn,
								fFrontX, fFrontY,
								fSideX, fSideY,
								nIntensity, nRed, nGreen, nBlue,
								fZDistance, fScale, ppPolyBunch);
						}
					}
				}
			}
		}
	}
}


void
CShadows::CastPlayerShadowSectorList(CPtrList &PtrList, float fStartX, float fStartY, float fEndX, float fEndY, CVector *pPosn,
								float fFrontX, float fFrontY, float fSideX, float fSideY,
								int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
								float fZDistance, float fScale, CPolyBunch **ppPolyBunch)
{
	ASSERT(pPosn != nil);

	CPtrNode *pNode = PtrList.first;

	CRect Bound;

	while ( pNode != nil )
	{
		CEntity *pEntity = (CEntity *)pNode->item;
		uint16 nScanCode = pEntity->m_scanCode;
		pNode = pNode->next;

		ASSERT( pEntity != nil );

		if ( nScanCode != CWorld::GetCurrentScanCode() )
		{
			pEntity->m_scanCode = CWorld::GetCurrentScanCode();
			
			if ( pEntity->bUsesCollision )
			{
				if ( IsAreaVisible(pEntity->m_area) )
				{
					Bound = pEntity->GetBoundRect();
	
					if ( fStartX < Bound.right
						&& fEndX > Bound.left
						&& fStartY < Bound.bottom
						&& fEndY > Bound.top )
					{
						if ( pPosn->z - fZDistance < pEntity->GetPosition().z + pEntity->GetColModel()->boundingBox.max.z
							&& pEntity->GetPosition().z + pEntity->GetColModel()->boundingBox.min.z < pPosn->z )
						{
							CastShadowEntityXY(pEntity,
								fStartX, fStartY,
								fEndX, fEndY,
								pPosn,
								fFrontX, fFrontY,
								fSideX, fSideY,
								nIntensity, nRed, nGreen, nBlue,
								fZDistance, fScale, ppPolyBunch);
						}
					}
				}
			}
		}
	}
}


void
CShadows::CastCutsceneShadowSectorList(CPtrList &PtrList, float fStartX, float fStartY, float fEndX, float fEndY, CVector *pPosn,
								float fFrontX, float fFrontY, float fSideX, float fSideY,
								int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
								float fZDistance, float fScale, CPolyBunch **ppPolyBunch, CCutsceneShadow *pShadow)
{
	ASSERT(pPosn != nil);
	ASSERT(pShadow != nil);
	
	CPtrNode *pNode = PtrList.first;

	CRect Bound;

	while ( pNode != nil )
	{
		CEntity *pEntity = (CEntity *)pNode->item;
		uint16 nScanCode = pEntity->m_scanCode;
		pNode = pNode->next;

		ASSERT( pEntity != nil );

		if ( nScanCode != CWorld::GetCurrentScanCode() )
		{
			pEntity->m_scanCode = CWorld::GetCurrentScanCode();
			
			if ( pEntity->bUsesCollision )
			{
				if ( IsAreaVisible(pEntity->m_area) )
				{
					Bound = pEntity->GetBoundRect();
	
					if ( fStartX < Bound.right
						&& fEndX > Bound.left
						&& fStartY < Bound.bottom
						&& fEndY > Bound.top )
					{
						if ( pPosn->z - fZDistance < pEntity->GetPosition().z + pEntity->GetColModel()->boundingBox.max.z
							&& pEntity->GetPosition().z + pEntity->GetColModel()->boundingBox.min.z < pPosn->z )
						{
							CastShadowEntityXYZ(pEntity, pPosn,
								fFrontX, fFrontY,
								fSideX, fSideY,
								nIntensity, nRed, nGreen, nBlue,
								fZDistance, fScale, ppPolyBunch, pShadow);
						}
					}
				}
			}
		}
	}
}

void
CShadows::CastShadowEntityXY(CEntity *pEntity,  float fStartX, float fStartY, float fEndX, float fEndY, CVector *pPosn,
							float fFrontX, float fFrontY, float fSideX, float fSideY,
							int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
							float fZDistance, float fScale, CPolyBunch **ppPolyBunch)
{
	ASSERT(pEntity != nil);
	ASSERT(pPosn != nil);

	static CVector List   [20];
	static CVector Texture[20];
	static CVector Points [4];

	CColModel *pCol = pEntity->GetColModel();
	ASSERT(pCol != nil);

#ifndef MASTER
	if ( gbPrintShite )
		printf("MI:%d Triangles:%d Coors:%f %f BBoxXY:%f %f\n",
			pEntity->GetModelIndex(),
			pCol->numTriangles,
			pEntity->GetPosition().x,
			pEntity->GetPosition().y,
			pCol->boundingBox.GetSize().x,
			pCol->boundingBox.GetSize().y);
#endif
	
	CCollision::CalculateTrianglePlanes(pCol);

	float fFrontRight    = DotProduct2D(CVector2D(fFrontX, fFrontY),     pEntity->GetRight());
	float fFrontForward  = DotProduct2D(CVector2D(fFrontX, fFrontY),     pEntity->GetForward());
	float fSideRight     = DotProduct2D(CVector2D(fSideX, fSideY),       pEntity->GetRight());
	float fSideForward   = DotProduct2D(CVector2D(fSideX, fSideY),       pEntity->GetForward());
	float fLengthRight   = DotProduct2D(*pPosn - pEntity->GetPosition(), pEntity->GetRight());
	float fLengthForward = DotProduct2D(*pPosn - pEntity->GetPosition(), pEntity->GetForward());

	Points[0].x = (fLengthRight   + fFrontRight  )  - fSideRight;
	Points[0].y = (fLengthForward + fFrontForward)  - fSideForward;

	Points[1].x = fSideRight      + (fLengthRight   + fFrontRight);
	Points[1].y = fSideForward    + (fLengthForward + fFrontForward);
                                  
	Points[2].x = fSideRight      + (fLengthRight   - fFrontRight);
	Points[2].y = fSideForward    + (fLengthForward - fFrontForward);

	Points[3].x = (fLengthRight   - fFrontRight)    - fSideRight;
	Points[3].y = (fLengthForward - fFrontForward)  - fSideForward;

	float MinX = Min(Min(Points[0].x, Points[1].x), Min(Points[2].x, Points[3].x));
	float MaxX = Max(Max(Points[0].x, Points[1].x), Max(Points[2].x, Points[3].x));

	float MinY = Min(Min(Points[0].y, Points[1].y), Min(Points[2].y, Points[3].y));
	float MaxY = Max(Max(Points[0].y, Points[1].y), Max(Points[2].y, Points[3].y));

	float MaxZ = pPosn->z - pEntity->GetPosition().z;
	float MinZ = MaxZ - fZDistance;

	for ( int32 i = 0; i < pCol->numTriangles; i++ )
	{
		CColTrianglePlane *pColTriPlanes = pCol->trianglePlanes;
		ASSERT(pColTriPlanes != nil);

		CVector normal;
		pColTriPlanes[i].GetNormal(normal);
		if ( Abs(normal.z) > 0.1f )
		{
			CColTriangle *pColTri = pCol->triangles;
			ASSERT(pColTri != nil);

			CVector PointA, PointB, PointC;

			pCol->GetTrianglePoint(PointA, pColTri[i].a);
			pCol->GetTrianglePoint(PointB, pColTri[i].b);
			pCol->GetTrianglePoint(PointC, pColTri[i].c);

			if (   (PointA.x > MinX || PointB.x > MinX || PointC.x > MinX)
				&& (PointA.x < MaxX || PointB.x < MaxX || PointC.x < MaxX)
				&& (PointA.y > MinY || PointB.y > MinY || PointC.y > MinY)
				&& (PointA.y < MaxY || PointB.y < MaxY || PointC.y < MaxY)
				&& (PointA.z < MaxZ || PointB.z < MaxZ || PointC.z < MaxZ)
				&& (PointA.z > MinZ || PointB.z > MinZ || PointC.z > MinZ) )

			{
				List[0].x = Points[0].x;
				List[0].y = Points[0].y;

				List[1].x = Points[1].x;
				List[1].y = Points[1].y;

				List[2].x = Points[2].x;
				List[2].y = Points[2].y;

				List[3].x = Points[3].x;
				List[3].y = Points[3].y;

				Texture[0].x = 0.0f;
				Texture[0].y = 0.0f;

				Texture[1].x = 1.0f;
				Texture[1].y = 0.0f;

				Texture[2].x = 1.0f;
				Texture[2].y = 1.0f;

				Texture[3].x = 0.0f;
				Texture[3].y = 1.0f;


				CVector2D start;
				CVector2D dist;

				int32 numVerts1 = 0;
				int16 vertType1 = 0;
				{						
					for ( int32 j = 0; j < 4; j++ )
					{
						start = PointA;
						dist  = PointB - PointA;
						
						int32 in = j;
						
						float cp = CrossProduct2D(CVector2D(List[in]) - start, dist);

						if ( cp > 0.0f )
						{
							switch ( vertType1 )
							{
								case 0:
								{
									int32 out = numVerts1++ + 10;

									Texture[out].x = Texture[in].x;
									Texture[out].y = Texture[in].y;
									List[out].x    = List[in].x;
									List[out].y    = List[in].y;

									break;
								}

								case 1:
								{
									int32 out = numVerts1++ + 10;

									Texture[out].x = Texture[in].x;
									Texture[out].y = Texture[in].y;
									List[out].x    = List[in].x;
									List[out].y    = List[in].y;

									break;
								}

								case 2:
								{
									float prevcp = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

									float Scale = Abs(prevcp) / (Abs(prevcp) + Abs(cp));
									float Compl = 1.0f - Scale;

									int32 out1 = numVerts1++ + 10;
									int32 out2 = numVerts1++ + 10;

									Texture[out1].x = Compl*Texture[in-1].x + Scale*Texture[in].x;
									Texture[out1].y = Compl*Texture[in-1].y + Scale*Texture[in].y;
									List[out1].x    = Compl*List[in-1].x    + Scale*List[in].x;
									List[out1].y    = Compl*List[in-1].y    + Scale*List[in].y;

									Texture[out2].x = Texture[in].x;
									Texture[out2].y = Texture[in].y;
									List[out2].x    = List[in].x;
									List[out2].y    = List[in].y;

									break;
								}
							}

							vertType1 = 1;
						}
						else
						{
							switch ( vertType1 )
							{
								case 1:
								{
									float prevcp = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

									float Scale = Abs(prevcp) / (Abs(prevcp) + Abs(cp));
									float Compl = 1.0f - Scale;

									int32 out = numVerts1++ + 10;

									Texture[out].x = Compl*Texture[in-1].x + Scale*Texture[in].x;
									Texture[out].y = Compl*Texture[in-1].y + Scale*Texture[in].y;
									List[out].x    = Compl*List[in-1].x    + Scale*List[in].x;
									List[out].y    = Compl*List[in-1].y    + Scale*List[in].y;
									
									break;
								}
							}

							vertType1 = 2;
						}
					}

					float cp1 = CrossProduct2D(CVector2D(List[0]) - start, dist);
					if ( cp1 > 0.0f && vertType1 == 2 || cp1 <= 0.0f && vertType1 == 1 )
					{
						float cp2 = CrossProduct2D(CVector2D(List[3]) - start, dist);

						float Scale = Abs(cp2) / (Abs(cp2) + Abs(cp1));
						float Compl = 1.0f - Scale;

						int32 out = numVerts1++ + 10;

						Texture[out].x = Compl*Texture[3].x + Scale*Texture[0].x;
						Texture[out].y = Compl*Texture[3].y + Scale*Texture[0].y;
						List[out].x    = Compl*List[3].x    + Scale*List[0].x;
						List[out].y    = Compl*List[3].y    + Scale*List[0].y;
					}
				}

				int32 numVerts2 = 0;
				int16 vertType2 = 0;
				{						
					for ( int32 j = 0; j < numVerts1; j++ )
					{
						start = PointB;
						dist  = PointC - PointB;
					
						int32 in = j + 10;
						float cp = CrossProduct2D(CVector2D(List[in]) - start, dist);

						if ( cp > 0.0f )
						{
							switch ( vertType2 )
							{
								case 0:
								{
									int32 out = numVerts2++;

									Texture[out].x = Texture[in].x;
									Texture[out].y = Texture[in].y;
									List[out].x    = List[in].x;
									List[out].y    = List[in].y;
									
									break;
								}

								case 1:
								{
									int32 out = numVerts2++;

									Texture[out].x = Texture[in].x;
									Texture[out].y = Texture[in].y;
									List[out].x    = List[in].x;
									List[out].y    = List[in].y;
									
									break;
								}

								case 2:
								{
									float prevcp = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

									float Scale = Abs(prevcp) / (Abs(prevcp) + Abs(cp));
									float Compl = 1.0f - Scale;

									int32 out1 = numVerts2++;
									int32 out2 = numVerts2++;

									Texture[out1].x = Compl*Texture[in-1].x + Scale*Texture[in].x;
									Texture[out1].y = Compl*Texture[in-1].y + Scale*Texture[in].y;
									List[out1].x    = Compl*List[in-1].x    + Scale*List[in].x;
									List[out1].y    = Compl*List[in-1].y    + Scale*List[in].y;

									Texture[out2].x = Texture[in].x;
									Texture[out2].y = Texture[in].y;
									List[out2].x    = List[in].x;
									List[out2].y    = List[in].y;
									
									break;
								}
							}

							vertType2 = 1;
						}
						else
						{
							switch ( vertType2 )
							{
								case 1:
								{
									float prevcp = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

									float Scale = Abs(prevcp) / (Abs(prevcp) + Abs(cp));
									float Compl = 1.0f - Scale;

									int32 out = numVerts2++;

									Texture[out].x = Compl*Texture[in-1].x + Scale*Texture[in].x;
									Texture[out].y = Compl*Texture[in-1].y + Scale*Texture[in].y;
									List[out].x    = Compl*List[in-1].x    + Scale*List[in].x;
									List[out].y    = Compl*List[in-1].y    + Scale*List[in].y;
									
									break;
								}
							}

							vertType2 = 2;
						}
					}

					float cp1 = CrossProduct2D(CVector2D(List[10]) - start, dist);
					if ( cp1 > 0.0f && vertType2 == 2 || cp1 <= 0.0f && vertType2 == 1 )
					{
						int32 in = numVerts1 + 10;

						float cp2 = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

						float Scale = Abs(cp2) / (Abs(cp2) + Abs(cp1));
						float Compl = 1.0f - Scale;

						int32 out = numVerts2++;

						Texture[out].x = Compl*Texture[in-1].x + Scale*Texture[10].x;
						Texture[out].y = Compl*Texture[in-1].y + Scale*Texture[10].y;
						List[out].x    = Compl*List[in-1].x    + Scale*List[10].x;
						List[out].y    = Compl*List[in-1].y    + Scale*List[10].y;
					}
				}

				int32 numVerts3 = 0;
				int16 vertType3 = 0;
				{					
					for ( int32 j = 0; j < numVerts2; j++ )
					{
						start = PointC;
						dist  = PointA - PointC;
					
						int32 in = j;
						float cp = CrossProduct2D(CVector2D(List[in]) - start, dist);

						if ( cp > 0.0f )
						{
							switch ( vertType3 )
							{
								case 0:
								{
									int32 out = numVerts3++ + 10;

									Texture[out].x = Texture[in].x;
									Texture[out].y = Texture[in].y;
									List[out].x    = List[in].x;
									List[out].y    = List[in].y;
									
									break;
								}

								case 1:
								{
									int32 out = numVerts3++ + 10;

									Texture[out].x = Texture[in].x;
									Texture[out].y = Texture[in].y;
									List[out].x    = List[in].x;
									List[out].y    = List[in].y;
									
									break;
								}

								case 2:
								{
									float prevcp = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

									float Scale = Abs(prevcp) / (Abs(prevcp) + Abs(cp));
									float Compl = 1.0f - Scale;

									int32 out1 = numVerts3++ + 10;
									int32 out2 = numVerts3++ + 10;

									Texture[out1].x = Compl*Texture[in-1].x + Scale*Texture[in].x;
									Texture[out1].y = Compl*Texture[in-1].y + Scale*Texture[in].y;
									List[out1].x    = Compl*List[in-1].x    + Scale*List[in].x;
									List[out1].y    = Compl*List[in-1].y    + Scale*List[in].y;

									Texture[out2].x = Texture[in].x;
									Texture[out2].y = Texture[in].y;
									List[out2].x    = List[in].x;
									List[out2].y    = List[in].y;
									
									break;
								}
							}

							vertType3 = 1;
						}
						else
						{
							switch ( vertType3 )
							{
								case 1:
								{
									float prevcp = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

									float Scale = Abs(prevcp) / (Abs(prevcp) + Abs(cp));
									float Compl = 1.0f - Scale;

									int32 out = numVerts3++ + 10;

									Texture[out].x = Compl*Texture[in-1].x + Scale*Texture[in].x;
									Texture[out].y = Compl*Texture[in-1].y + Scale*Texture[in].y;
									List[out].x    = Compl*List[in-1].x    + Scale*List[in].x;
									List[out].y    = Compl*List[in-1].y    + Scale*List[in].y;
									
									break;
								}
							}

							vertType3 = 2;
						}
					}

					float cp1 = CrossProduct2D(CVector2D(List[0]) - start, dist);
					if ( cp1 > 0.0f && vertType3 == 2 || cp1 <= 0.0f && vertType3 == 1 )
					{
						int32 in = numVerts2;

						float cp2 = CrossProduct2D(CVector2D(List[in-1]) - start, dist);

						float Scale = Abs(cp2) / (Abs(cp2) + Abs(cp1));
						float Compl = 1.0f - Scale;

						int32 out = numVerts3++ + 10;

						Texture[out].x = Compl*Texture[in-1].x + Scale*Texture[0].x;
						Texture[out].y = Compl*Texture[in-1].y + Scale*Texture[0].y;
						List[out].x    = Compl*List[in-1].x    + Scale*List[0].x;
						List[out].y    = Compl*List[in-1].y    + Scale*List[0].y;
					}
				}
					
				if ( numVerts3 >= 3 )
				{
					CVector norm;

					pColTriPlanes[i].GetNormal(norm);

					float dot = DotProduct(norm, PointA);

					for ( int32 j = 0; j < numVerts3; j++ )
					{
						int32 idx = j + 10;

						List[idx].z = -(DotProduct2D(norm, List[idx]) - dot) / norm.z;
					}

					for ( int32 j = 0; j < numVerts3; j++ )
					{
						int32 idx = j + 10;

						CVector p = List[idx];
						
						List[idx].x = p.y * pEntity->GetForward().x + p.x * pEntity->GetRight().x + pEntity->GetPosition().x;
						List[idx].y = p.y * pEntity->GetForward().y + p.x * pEntity->GetRight().y + pEntity->GetPosition().y;
						List[idx].z = p.z + pEntity->GetPosition().z;
					}

					
					if ( ppPolyBunch != nil )
					{
						if ( pEmptyBunchList != nil )
						{
							CPolyBunch *pBunch = pEmptyBunchList;
							ASSERT(pBunch != nil);
							pEmptyBunchList = pEmptyBunchList->m_pNext;
							pBunch->m_pNext = *ppPolyBunch;
							*ppPolyBunch = pBunch;
	
							pBunch->m_nNumVerts = numVerts3;
	
							for ( int32 j = 0; j < numVerts3; j++ )
							{
								int32 in = j + 10;
	
								pBunch->m_aVerts[j] = List[in];
	
								pBunch->m_aU[j] = (int32)(Texture[in].x * 200.0f);
								pBunch->m_aV[j] = (int32)(Texture[in].y * 200.0f);
							}
						}
					}
					else
					{
						RwImVertexIndex *pIndexes;
						RwIm3DVertex *pVerts;

						RenderBuffer::StartStoring(3 * (numVerts3 - 2), numVerts3, &pIndexes, &pVerts);

						ASSERT(pIndexes != nil);
						ASSERT(pVerts != nil);


						for ( int32 j = 0; j < numVerts3; j++ )
						{
							int32 in = j + 10;

							RwIm3DVertexSetRGBA(&pVerts[j], nRed, nGreen, nBlue, nIntensity);
							RwIm3DVertexSetU   (&pVerts[j], Texture[in].x*fScale);
							RwIm3DVertexSetV   (&pVerts[j], Texture[in].y*fScale);
							RwIm3DVertexSetPos (&pVerts[j], List[in].x, List[in].y, List[in].z + 0.03f);
						}

						for ( int32 j = 0; j < 3*(numVerts3 - 2); j++ )
							pIndexes[j] = ShadowIndexList[j];

						RenderBuffer::StopStoring();
					}
				}
			}
		}
	}
}


typedef struct _ProjectionParam
{
	RwV3d               at;     /* Camera at vector */
	RwMatrix            invMatrix; /* Transforms to shadow camera space */
	RwUInt8             shadowValue; /* Shadow opacity value */
	RwBool              fade;   /* Shadow fades with distance */
	RwUInt32            numIm3DBatch; /* Number of buffer flushes */
	RwMatrix            entityMatrix;
}
ProjectionParam;

RwV3d *ShadowRenderTriangleCB(RwV3d *points, RwV3d *normal, ProjectionParam *param)
{
	RwV3d vIn[3];
	RwV3d vShad[3];
	
	RwV3dTransformPoints(&vIn[0], points, 3, &param->entityMatrix);
	
	/*
	 *  Reject backfacing triangles
	 *  This reject the triangles parallel to the light as well 
	 */
	if (RwV3dDotProduct(normal, &param->at) > 0.0f)
	{
		return points;
	}
	
	RwV3dTransformPoints(&vShad[0], &vIn[0], 3, &param->invMatrix);
	
	/*
	 *  Reject triangles behind the camera (z test). Note that any world 
	 *  triangles lying in front of the camera but before the object may 
	 *  have a shadow applied. To minimize such artefacts, this test could 
	 *  be modified to use a specific value rather than 0.0f, perhaps
	 *  to reject triangles behind the center plane of the object.
	 *
	 *  Reject triangles that lie entirely outside the shadow texture range
	 *  (x,y test).
	 */
	if (((vShad[0].z < 0.0f) && (vShad[1].z < 0.0f)
		&& (vShad[2].z < 0.0f)) || ((vShad[0].x < 0.0f)
									&& (vShad[1].x < 0.0f)
									&& (vShad[2].x < 0.0f))
		|| ((vShad[0].x > 1.0f) && (vShad[1].x > 1.0f)
			&& (vShad[2].x > 1.0f)) || ((vShad[0].y < 0.0f)
										&& (vShad[1].y < 0.0f)
										&& (vShad[2].y < 0.0f))
		|| ((vShad[0].y > 1.0f) && (vShad[1].y > 1.0f)
			&& (vShad[2].y > 1.0f)))
	{
		return points;
	}
	
	RwIm3DVertex *imv = nil;
	RwImVertexIndex *imi = nil;
	
	RenderBuffer::StartStoring(3, 3, &imi, &imv);
	
	/*
	 *  Set the immediate mode vertices for this triangle
	 */
	
	RwIm3DVertexSetPos(imv, vIn[0].x, vIn[0].y, vIn[0].z);
	RwIm3DVertexSetPos(imv + 1, vIn[1].x, vIn[1].y, vIn[1].z);
	RwIm3DVertexSetPos(imv + 2, vIn[2].x, vIn[2].y, vIn[2].z);
	
	RwIm3DVertexSetU(imv, vShad[0].x);
	RwIm3DVertexSetU(imv + 1, vShad[1].x);
	RwIm3DVertexSetU(imv + 2, vShad[2].x);
	
	RwIm3DVertexSetV(imv, vShad[0].y);
	RwIm3DVertexSetV(imv + 1, vShad[1].y);
	RwIm3DVertexSetV(imv + 2, vShad[2].y);
	
	/*
	 *  Do we fade out the shadow with distance?
	 */
	if (param->fade)
	{
		RwReal              fadeVal;
		RwUInt8             val;
		
		fadeVal = 1.0f - vShad[0].z * vShad[0].z;
		val =
			(fadeVal <
			0.0f) ? 0 : (RwUInt8) (fadeVal * param->shadowValue);
		RwIm3DVertexSetRGBA(imv, val, val, val, val);
		
		fadeVal = 1.0f - vShad[1].z * vShad[1].z;
		val =
			(fadeVal <
			0.0f) ? 0 : (RwUInt8) (fadeVal * param->shadowValue);
		RwIm3DVertexSetRGBA(imv + 1, val, val, val, val);
		
		fadeVal = 1.0f - vShad[2].z * vShad[2].z;
		val =
			(fadeVal <
			0.0f) ? 0 : (RwUInt8) (fadeVal * param->shadowValue);
		RwIm3DVertexSetRGBA(imv + 2, val, val, val, val);
	}
	else
	{
		RwUInt8             val = param->shadowValue;
		
		RwIm3DVertexSetRGBA(imv, val, val, val, val);
		RwIm3DVertexSetRGBA(imv + 1, val, val, val, val);
		RwIm3DVertexSetRGBA(imv + 2, val, val, val, val);
	}

	/*
	 *  Update buffer position 
	 */
	imi[0] = 0;
	imi[1] = 1;
	imi[2] = 2;
	
	RenderBuffer::StopStoring();
	
	return points;
}

void
CShadows::CastShadowEntityXYZ(CEntity *pEntity, CVector *pPosn,
								float fFrontX, float fFrontY, float fSideX, float fSideY,
								int16 nIntensity, uint8 nRed, uint8 nGreen, uint8 nBlue,
								float fZDistance, float fScale, CPolyBunch **ppPolyBunch, CCutsceneShadow *pShadow)
{
	ASSERT(pEntity != nil);
	ASSERT(pPosn != nil);
	
	if ( pShadow )
	{
		ProjectionParam proj;
		RwV3d scl;
		RwV3d tr;
		
		CShadowCamera *shadow = pShadow->GetShadowCamera();
		CColModel *collision  = pEntity->GetColModel();
		
		CCollision::CalculateTrianglePlanes(collision);
		
		RwMatrix mat;
		mat = *RwFrameGetMatrix(RwCameraGetFrame(shadow->GetRwCamera()));
		
		RwV3d        Xaxis = { 1.0f, 0.0f, 0.0f };

		RwMatrixRotate(&mat, &Xaxis, -45.0f, rwCOMBINEPRECONCAT);
		
		proj.at = mat.at;
		pEntity->GetMatrix().CopyToRwMatrix(&proj.entityMatrix);

		RwMatrixInvert(&proj.invMatrix, &mat);		
		RwReal radius = RwCameraGetViewWindow(shadow->GetRwCamera())->x;
		
		scl.x = scl.y = -0.5f / (radius*0.9f);
		scl.z = 1.0f / (radius*0.8f);
		RwMatrixScale(&proj.invMatrix, &scl, rwCOMBINEPOSTCONCAT);
		
		tr.x = 0.5f;
		tr.y = tr.z = 0.0f;
		RwMatrixTranslate(&proj.invMatrix, &tr, rwCOMBINEPOSTCONCAT);
		
		proj.shadowValue = nIntensity;
		proj.fade = 0;
		
		RwMatrix matrix;
		pEntity->GetMatrix().CopyToRwMatrix(&matrix);
		RwMatrix invMatrix;
		RwMatrixInvert(&invMatrix, &matrix);
		

		CVector center(pShadow->GetBaseSphere().center);
		center += CVector(-fFrontX * 1.1f, -fFrontY * 1.1f, -0.5f);
		
		CSphere sphere;
		sphere.Set(2.0f, center);

		RwV3d point;
		RwV3dTransformPoints(&point, &center, 1, &invMatrix);
		
		CColSphere colSphere;
		colSphere.Set(2.0f, CVector(point), 0, 0);
		
		int i = 0;
		while ( i < collision->numTriangles )
        {
			CVector p[3];

			collision->GetTrianglePoint(p[0], collision->triangles[i].a);
			collision->GetTrianglePoint(p[1], collision->triangles[i].b);
			collision->GetTrianglePoint(p[2], collision->triangles[i].c);
			
			if ( CCollision::TestSphereTriangle(colSphere, collision->vertices, collision->triangles[i], collision->trianglePlanes[i]) )
			{
				CVector n(collision->trianglePlanes[i].GetNormalX(), collision->trianglePlanes[i].GetNormalY(), collision->trianglePlanes[i].GetNormalZ());
				CVector offset = n * 0.028f;
				
				p[0] += offset;
				p[1] += offset;
				p[2] += offset;

				if ( !ShadowRenderTriangleCB(p, &n, &proj) )
					break;
			}
			i++;
		}
	}
}

void
CShadows::UpdateStaticShadows(void)
{
	for ( int32 i = 0; i < MAX_STATICSHADOWS; i++ )
	{
		if ( aStaticShadows[i].m_pPolyBunch != nil && !aStaticShadows[i].m_bJustCreated
			&& (!aStaticShadows[i].m_bTemp || CTimer::GetTimeInMilliseconds() > aStaticShadows[i].m_nTimeCreated + 5000) )
		{
			aStaticShadows[i].Free();
		}

		aStaticShadows[i].m_bJustCreated = false;
	}
}

void
CShadows::UpdatePermanentShadows(void)
{
	for ( int32 i = 0; i < MAX_PERMAMENTSHADOWS; i++ )
	{
		if ( aPermanentShadows[i].m_nType != SHADOWTYPE_NONE )
		{
			uint32 timePassed = CTimer::GetTimeInMilliseconds() - aPermanentShadows[i].m_nTimeCreated;

			if ( timePassed >= aPermanentShadows[i].m_nLifeTime )
				aPermanentShadows[i].m_nType = SHADOWTYPE_NONE;
			else
			{
				bool bOk;
				if ( timePassed >= (aPermanentShadows[i].m_nLifeTime * 3 / 4) )
				{
					// timePassed == 0                                -> 4
					// timePassed == aPermanentShadows[i].m_nLifeTime -> 0
					float fMult = 1.0f - float(timePassed - (aPermanentShadows[i].m_nLifeTime * 3 / 4)) / (aPermanentShadows[i].m_nLifeTime / 4);

					bOk = StoreStaticShadow((uintptr)&aPermanentShadows[i],
						aPermanentShadows[i].m_nType,
						aPermanentShadows[i].m_pTexture,
						&aPermanentShadows[i].m_vecPos,
						aPermanentShadows[i].m_vecFront.x,
						aPermanentShadows[i].m_vecFront.y,
						aPermanentShadows[i].m_vecSide.x,
						aPermanentShadows[i].m_vecSide.y,
						(int32)(aPermanentShadows[i].m_nIntensity * fMult),
						(int32)(aPermanentShadows[i].m_nRed       * fMult),
						(int32)(aPermanentShadows[i].m_nGreen     * fMult),
						(int32)(aPermanentShadows[i].m_nBlue      * fMult),
						aPermanentShadows[i].m_fZDistance,
						1.0f, 40.0f, false, 0.0f);
				}
				else
				{
					bOk = StoreStaticShadow((uintptr)&aPermanentShadows[i],
						aPermanentShadows[i].m_nType,
						aPermanentShadows[i].m_pTexture,
						&aPermanentShadows[i].m_vecPos,
						aPermanentShadows[i].m_vecFront.x,
						aPermanentShadows[i].m_vecFront.y,
						aPermanentShadows[i].m_vecSide.x,
						aPermanentShadows[i].m_vecSide.y,
						aPermanentShadows[i].m_nIntensity,
						aPermanentShadows[i].m_nRed,
						aPermanentShadows[i].m_nGreen,
						aPermanentShadows[i].m_nBlue,
						aPermanentShadows[i].m_fZDistance,
						1.0f, 40.0f, false, 0.0f);
				}
				
				if ( !bOk )
					aPermanentShadows[i].m_nType = SHADOWTYPE_NONE;
			}
		}
	}
}

void
CStaticShadow::Free(void)
{
	if ( m_pPolyBunch != nil )
	{
		CPolyBunch *pFree = CShadows::pEmptyBunchList;
		CShadows::pEmptyBunchList = m_pPolyBunch;

		CPolyBunch *pUsed = m_pPolyBunch;
		while (pUsed->m_pNext != nil)
			pUsed = pUsed->m_pNext;

			pUsed->m_pNext = pFree;
	}

	m_pPolyBunch = nil;

	m_nId = 0;
}

void
CShadows::CalcPedShadowValues(CVector vecLightDir,
							float *pfFrontX, float *pfFrontY,
							float *pfSideX, float *pfSideY,
							float *pfDisplacementX, float *pfDisplacementY)
{
	ASSERT(pfFrontX != nil);
	ASSERT(pfFrontY != nil);
	ASSERT(pfSideX != nil);
	ASSERT(pfSideY != nil);
	ASSERT(pfDisplacementX != nil);
	ASSERT(pfDisplacementY != nil);

	*pfFrontX = -vecLightDir.x;
	*pfFrontY = -vecLightDir.y;

	float fDist = Sqrt(*pfFrontY * *pfFrontY + *pfFrontX * *pfFrontX);
	float fMult = (fDist + 1.0f) / fDist;

	*pfFrontX *= fMult;
	*pfFrontY *= fMult;

	*pfSideX = -vecLightDir.y / fDist;
	*pfSideY =  vecLightDir.x / fDist;

	*pfDisplacementX = -vecLightDir.x;
	*pfDisplacementY = -vecLightDir.y;

	*pfFrontX /= 2;
	*pfFrontY /= 2;

	*pfSideX /= 2;
	*pfSideY /= 2;

	*pfDisplacementX /= 2;
	*pfDisplacementY /= 2;
	
}


void
CShadows::RenderExtraPlayerShadows(void)
{
#ifdef FIX_BUGS
	if (CReplay::IsPlayingBack())
		return;
#endif
	if ( CTimeCycle::GetLightShadowStrength() != 0 )
	{
		CVehicle *pCar = FindPlayerVehicle();
		if ( pCar == nil )
			; // R* cut it out for playerped
		else
		{
			if ( pCar->GetModelIndex() != MI_RCBANDIT 
				&& pCar->GetVehicleAppearance() != VEHICLE_APPEARANCE_BIKE
				&& !pCar->IsBike() && !pCar->IsPlane() && !pCar->IsBoat() )
			{
				for ( int32 i = 0; i < CPointLights::NumLights; i++ )
				{
					if (  CPointLights::aLights[i].type == CPointLights::LIGHT_POINT
						&& CPointLights::aLights[i].castExtraShadows
						&&(0.0f != CPointLights::aLights[i].red
						|| 0.0f != CPointLights::aLights[i].green
						|| 0.0f != CPointLights::aLights[i].blue) )
					{
						CVector vecLight = CPointLights::aLights[i].coors - FindPlayerCoors();
						float fLightDist = vecLight.Magnitude();
						float fRadius = CPointLights::aLights[i].radius;

						if ( fLightDist < fRadius )
						{
							// fLightDist == 0       -> 2.0f
							// fLightDist == fRadius -> 0.0f
							float fMult = (1.0f - (2.0f * fLightDist - fRadius) / fRadius);

							int32 nColorStrength;
							if ( fLightDist < fRadius*0.5f )
								nColorStrength = (5*CTimeCycle::GetLightShadowStrength()/8);
							else
								nColorStrength = int32((5*CTimeCycle::GetLightShadowStrength()/8) * fMult);

							float fInv = 1.0f / fLightDist;
							vecLight.x *= fInv;
							vecLight.y *= fInv;
							vecLight.z *= fInv;

							CVector shadowPos = pCar->GetPosition();

							shadowPos.x -= vecLight.x * 1.2f;
							shadowPos.y -= vecLight.y * 1.2f;

							float fVehicleWidth   = pCar->GetColModel()->boundingBox.GetSize().x;
							float fVehicleHeight  = pCar->GetColModel()->boundingBox.GetSize().y;

							shadowPos.x -= ((fVehicleHeight/2) - pCar->GetColModel()->boundingBox.max.y)
											* pCar->GetForward().x;

							shadowPos.y -= ((fVehicleHeight/2) - pCar->GetColModel()->boundingBox.max.y)
											* pCar->GetForward().y;

							if ( pCar->GetUp().z > 0.0f )
							{
								StoreShadowToBeRendered(SHADOWTYPE_DARK, gpShadowCarTex, &shadowPos,
									pCar->GetForward().x * (fVehicleHeight/2),
									pCar->GetForward().y * (fVehicleHeight/2),
									pCar->GetRight().x   * (fVehicleWidth/3),
									pCar->GetRight().y   * (fVehicleWidth/3),
									nColorStrength, 0, 0, 0,
									4.5f, false, 1.0f, nil, false);
							}
							else
							{
								StoreShadowToBeRendered(SHADOWTYPE_DARK, gpShadowCarTex, &shadowPos,
									pCar->GetForward().x * (fVehicleHeight/2),
									pCar->GetForward().y * (fVehicleHeight/2),
									-pCar->GetRight().x  * (fVehicleWidth/2),
									-pCar->GetRight().y  * (fVehicleWidth/2),
									nColorStrength, 0, 0, 0,
									4.5f, false, 1.0f, nil, false);
							}
						}
					}
				}
			}
		}
	}
}

void
CShadows::TidyUpShadows(void)
{
	for ( int32 i = 0; i < MAX_PERMAMENTSHADOWS; i++ )
		aPermanentShadows[i].m_nType = SHADOWTYPE_NONE;
}

void
CShadows::RenderIndicatorShadow(uint32 nID, uint8 ShadowType, RwTexture *pTexture,  CVector *pPosn,
								float fFrontX, float fFrontY, float fSideX, float fSideY,
								int16 nIntensity)
{
	ASSERT(pPosn != nil);

	C3dMarkers::PlaceMarkerSet(nID, MARKERTYPE_CYLINDER, *pPosn, Max(fFrontX, -fSideY),
		SPHERE_MARKER_R, SPHERE_MARKER_G, SPHERE_MARKER_B,
		SPHERE_MARKER_A, SPHERE_MARKER_PULSE_PERIOD, 0.2f, 0);
}
