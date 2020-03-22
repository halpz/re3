#define WITHD3D
#include "common.h"
#include "patcher.h"
#include "Timecycle.h"
#include "skeleton.h"

void *
RwMallocAlign(RwUInt32 size, RwUInt32 align)
{
	void *mem = (void *)malloc(size + align);
	
	ASSERT(mem != nil);
	
	void *addr = (void *)((((RwUInt32)mem) + align) & ~(align - 1));
	
	ASSERT(addr != nil);
	
	*(((void **)addr) - 1) = mem;
	
	return addr;
}

void
RwFreeAlign(void *mem)
{
	ASSERT(mem != nil);
	
	void *addr = *(((void **)mem) - 1);
	
	ASSERT(addr != nil);
	
	free(addr);
}

void
DefinedState(void)
{
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)rwTEXTUREADDRESSWRAP);
	RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEALPHAPRIMITIVEBUFFER, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEBORDERCOLOR, (void*)RWRGBALONG(0, 0, 0, 255));
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEFOGCOLOR,
		(void*)RWRGBALONG(CTimeCycle::GetFogRed(), CTimeCycle::GetFogGreen(), CTimeCycle::GetFogBlue(), 255));
	RwRenderStateSet(rwRENDERSTATEFOGTYPE, (void*)rwFOGTYPELINEAR);
	RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);

	// D3D stuff
	RwD3D8SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	RwD3D8SetRenderState(D3DRS_ALPHAREF, 2);
}

RwFrame*
GetFirstFrameCallback(RwFrame *child, void *data)
{
	*(RwFrame**)data = child;
	return nil;
}

RwFrame*
GetFirstChild(RwFrame *frame)
{
	RwFrame *child;

	child = nil;
	RwFrameForAllChildren(frame, GetFirstFrameCallback, &child);
	return child;
}

RwObject*
GetFirstObjectCallback(RwObject *object, void *data)
{
	*(RwObject**)data = object;
	return nil;
}

RwObject*
GetFirstObject(RwFrame *frame)
{
	RwObject *obj;

	obj = nil;
	RwFrameForAllObjects(frame, GetFirstObjectCallback, &obj);
	return obj;
}

RpAtomic*
GetFirstAtomicCallback(RpAtomic *atm, void *data)
{
	*(RpAtomic**)data = atm;
	return nil;
}

RpAtomic*
GetFirstAtomic(RpClump *clump)
{
	RpAtomic *atm;

	atm = nil;
	RpClumpForAllAtomics(clump, GetFirstAtomicCallback, &atm);
	return atm;
}

RwTexture*
GetFirstTextureCallback(RwTexture *tex, void *data)
{
	*(RwTexture**)data = tex;
	return nil;
}

RwTexture*
GetFirstTexture(RwTexDictionary *txd)
{
	RwTexture *tex;

	tex = nil;
	RwTexDictionaryForAllTextures(txd, GetFirstTextureCallback, &tex);
	return tex;
}

void
CameraSize(RwCamera * camera, RwRect * rect,
		   RwReal viewWindow, RwReal aspectRatio)
{
	if (camera)
	{
		RwVideoMode         videoMode;
		RwRect              r;
		RwRect              origSize = { 0, 0, 0, 0 };	// FIX just to make the compier happy
		RwV2d               vw;

		RwEngineGetVideoModeInfo(&videoMode,
								 RwEngineGetCurrentVideoMode());
								 
		origSize.w  = RwRasterGetWidth(RwCameraGetRaster(camera));
		origSize.h = RwRasterGetHeight(RwCameraGetRaster(camera));

		if (!rect)
		{
			if (videoMode.flags & rwVIDEOMODEEXCLUSIVE)
			{
				/* For full screen applications, resizing the camera just doesn't
				 * make sense, use the video mode size.
				 */
			 
				r.x = r.y = 0;
				r.w = videoMode.width;
				r.h = videoMode.height;
				rect = &r;
			}
			else
			{
				/*
				rect not specified - reuse current values
				*/
				r.w = RwRasterGetWidth(RwCameraGetRaster(camera));
				r.h = RwRasterGetHeight(RwCameraGetRaster(camera));
				r.x = r.y = 0;
				rect = &r;
			}
		}

		if (( origSize.w != rect->w ) && ( origSize.h != rect->h ))
		{
			RwRaster           *raster;
			RwRaster           *zRaster;
			
			/*
			 * Destroy rasters...
			 */
			 
			raster = RwCameraGetRaster(camera);
			if( raster )
			{
				RwRasterDestroy(raster);
			}

			zRaster = RwCameraGetZRaster(camera);
			if( zRaster )
			{
				RwRasterDestroy(zRaster);
			}
			
			/*
			 * Create new rasters... 
			 */

			raster = RwRasterCreate(rect->w, rect->h, 0, rwRASTERTYPECAMERA);
			zRaster = RwRasterCreate(rect->w, rect->h, 0, rwRASTERTYPEZBUFFER);
			
			if( raster && zRaster )
			{
				RwCameraSetRaster(camera, raster);
				RwCameraSetZRaster(camera, zRaster);
			}
			else
			{
				if( raster )
				{
					RwRasterDestroy(raster);
				}

				if( zRaster )
				{
					RwRasterDestroy(zRaster);
				}

				rect->x = origSize.x;
				rect->y = origSize.y;
				rect->w = origSize.w;
				rect->h = origSize.h;

				/* 
				 * Use default values... 
				 */
				raster =
					RwRasterCreate(rect->w, rect->h, 0, rwRASTERTYPECAMERA);

				zRaster =
					RwRasterCreate(rect->w, rect->h, 0, rwRASTERTYPEZBUFFER);

				RwCameraSetRaster(camera, raster);
				RwCameraSetZRaster(camera, zRaster);
			}
		}

		/* Figure out the view window */
		if (videoMode.flags & rwVIDEOMODEEXCLUSIVE)
		{
			/* derive ratio from aspect ratio */
			vw.x = viewWindow;
			vw.y = viewWindow / aspectRatio;
		}
		else
		{
			/* derive from pixel ratios */
			if (rect->w > rect->h)
			{
				vw.x = viewWindow;
				vw.y = (rect->h * viewWindow) / rect->w;
			}
			else
			{
				vw.x = (rect->w * viewWindow) / rect->h;
				vw.y = viewWindow;
			}
		}
		
		RwCameraSetViewWindow(camera, &vw);
		
		RsGlobal.width  = rect->w;
		RsGlobal.height = rect->h;
	}

	return;
}

void
CameraDestroy(RwCamera *camera)
{
	RwRaster    *raster, *tmpRaster;
	RwFrame     *frame;

	if (camera)
	{
		frame = RwCameraGetFrame(camera);
		if (frame)
		{
			RwFrameDestroy(frame);
		}

		raster = RwCameraGetRaster(camera);
		if (raster)
		{
			tmpRaster = RwRasterGetParent(raster);

			RwRasterDestroy(raster);

			if ((tmpRaster != nil) && (tmpRaster != raster))
			{
				RwRasterDestroy(tmpRaster);
			}
		}

		raster = RwCameraGetZRaster(camera);
		if (raster)
		{
			tmpRaster = RwRasterGetParent(raster);

			RwRasterDestroy(raster);

			if ((tmpRaster != nil) && (tmpRaster != raster))
			{
				RwRasterDestroy(tmpRaster);
			}
		}

		RwCameraDestroy(camera);
	}

	return;
}

RwCamera           *
CameraCreate(RwInt32 width, RwInt32 height, RwBool zBuffer)
{
	RwCamera           *camera;

	camera = RwCameraCreate();

	if (camera)
	{
		RwCameraSetFrame(camera, RwFrameCreate());
		RwCameraSetRaster(camera,
						  RwRasterCreate(0, 0, 0, rwRASTERTYPECAMERA));

		if (zBuffer)
		{
			RwCameraSetZRaster(camera,
							   RwRasterCreate(0, 0, 0,
											  rwRASTERTYPEZBUFFER));
		}

		/* now check that everything is valid */
		if (RwCameraGetFrame(camera) &&
			RwCameraGetRaster(camera) &&
			RwRasterGetParent(RwCameraGetRaster(camera)) &&
			(!zBuffer || (RwCameraGetZRaster(camera) &&
						  RwRasterGetParent(RwCameraGetZRaster
											(camera)))))
		{
			/* everything OK */
			return (camera);
		}
	}

	/* if we're here then an error must have occurred so clean up */

	CameraDestroy(camera);
	return (nil);
}

WRAPPER void ReadVideoCardCapsFile(uint32&, uint32&, uint32&, uint32&) { EAXJMP(0x5926C0); }
WRAPPER bool CheckVideoCardCaps(void) { EAXJMP(0x592740); }
WRAPPER void WriteVideoCardCapsFile(void) { EAXJMP(0x5927D0); }
WRAPPER void ConvertingTexturesScreen(uint32, uint32, const char*) { EAXJMP(0x592880); }
WRAPPER void DealWithTxdWriteError(uint32, uint32, const char*) { EAXJMP(0x592BF0); }
WRAPPER bool ConvertTextures() { EAXJMP(0x592C70); }

STARTPATCHES
	//InjectHook(0x526450, GetFirstObjectCallback, PATCH_JUMP);
	InjectHook(0x526460, GetFirstObject, PATCH_JUMP);
	InjectHook(0x527170, CameraSize, PATCH_JUMP);
	InjectHook(0x527340, CameraDestroy, PATCH_JUMP);
	InjectHook(0x5273B0, CameraCreate, PATCH_JUMP);
ENDPATCHES
