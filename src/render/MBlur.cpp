#include "common.h"
#include "patcher.h"
#include "RwHelper.h"
#include "Camera.h"
#include "MBlur.h"

RwRaster *&CMBlur::pFrontBuffer = *(RwRaster**)0x8E2C48;
bool &CMBlur::ms_bJustInitialised = *(bool*)0x95CDAB;
bool &CMBlur::BlurOn = *(bool*)0x95CDAD;

static RwIm2DVertex Vertex[4];
//static RwIm2DVertex *Vertex = (RwIm2DVertex*)0x62F780;
static RwImVertexIndex Index[6] = { 0, 1, 2, 0, 2, 3 };

void
CMBlur::MotionBlurOpen(RwCamera *cam)
{
	// TODO. this is simplified

	RwRect rect = { 0, 0, 0, 0 };

	if(pFrontBuffer)
		MotionBlurClose();

	if(BlurOn){
		for(rect.w = 1; rect.w < RwRasterGetWidth(RwCameraGetRaster(cam)); rect.w *= 2);
		for(rect.h = 1; rect.h < RwRasterGetHeight(RwCameraGetRaster(cam)); rect.h *= 2);
		pFrontBuffer = RwRasterCreate(rect.w, rect.h, RwRasterGetDepth(RwCameraGetRaster(cam)), rwRASTERTYPECAMERATEXTURE);
		if(pFrontBuffer)
			ms_bJustInitialised = true;
		else{
			debug("MBlurOpen can't create raster.");
			BlurOn = false;
			rect.w = RwRasterGetWidth(RwCameraGetRaster(cam));
			rect.h = RwRasterGetHeight(RwCameraGetRaster(cam));
		}
		CreateImmediateModeData(cam, &rect);
	}else{
		rect.w = RwRasterGetWidth(RwCameraGetRaster(cam));
		rect.h = RwRasterGetHeight(RwCameraGetRaster(cam));
		CreateImmediateModeData(cam, &rect);
	}
}

void
CMBlur::MotionBlurClose(void)
{
	if(pFrontBuffer){
		RwRasterDestroy(pFrontBuffer);
		pFrontBuffer = nil;
	}
}

void
CMBlur::CreateImmediateModeData(RwCamera *cam, RwRect *rect)
{
	float zero, xmax, ymax;

	if(RwRasterGetDepth(RwCameraGetRaster(cam)) == 16){
		zero = 0.5f;
		xmax = rect->w + 0.5f;
		ymax = rect->h + 0.5f;
	}else{
		zero = -0.5f;
		xmax = rect->w - 0.5f;
		ymax = rect->h - 0.5f;
	}

	RwIm2DVertexSetScreenX(&Vertex[0], zero);
	RwIm2DVertexSetScreenY(&Vertex[0], zero);
	RwIm2DVertexSetScreenZ(&Vertex[0], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex[0], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex[0], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex[0], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex[0], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex[0], 255, 255, 255, 255);

	RwIm2DVertexSetScreenX(&Vertex[1], zero);
	RwIm2DVertexSetScreenY(&Vertex[1], ymax);
	RwIm2DVertexSetScreenZ(&Vertex[1], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex[1], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex[1], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex[1], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex[1], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex[1], 255, 255, 255, 255);

	RwIm2DVertexSetScreenX(&Vertex[2], xmax);
	RwIm2DVertexSetScreenY(&Vertex[2], ymax);
	RwIm2DVertexSetScreenZ(&Vertex[2], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex[2], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex[2], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex[2], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex[2], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex[2], 255, 255, 255, 255);

	RwIm2DVertexSetScreenX(&Vertex[3], xmax);
	RwIm2DVertexSetScreenY(&Vertex[3], zero);
	RwIm2DVertexSetScreenZ(&Vertex[3], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex[3], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex[3], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex[3], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex[3], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex[3], 255, 255, 255, 255);

}

void
CMBlur::MotionBlurRender(RwCamera *cam, uint32 red, uint32 green, uint32 blue, uint32 blur, int32 type, uint32 addalpha)
{
	RwRGBA color = { (RwUInt8)red, (RwUInt8)green, (RwUInt8)blue, (RwUInt8)blur };
	if(BlurOn){
		if(pFrontBuffer){
			if(ms_bJustInitialised)
				ms_bJustInitialised = false;
			else
				OverlayRender(cam, pFrontBuffer, color, type, addalpha);
		}
		RwRasterPushContext(pFrontBuffer);
		RwRasterRenderFast(RwCameraGetRaster(cam), 0, 0);
		RwRasterPopContext();
	}else{
		OverlayRender(cam, nil, color, type, addalpha);
	}
}

void
CMBlur::OverlayRender(RwCamera *cam, RwRaster *raster, RwRGBA color, int32 type, uint32 addalpha)
{
	int r, g, b, a;

	r = color.red;
	g = color.green;
	b = color.blue;
	a = color.alpha;

	DefinedState();

	switch(type){
	case MBLUR_INTRO1:
		r = 0;
		g = 255;
		b = 0;
		a = 128;
		break;
	case MBLUR_INTRO3:
		r = 100;
		g = 220;
		b = 230;
		a = 158;
		break;
	case MBLUR_INTRO4:
		r = 80;
		g = 255;
		b = 230;
		a = 138;
		break;
	case MBLUR_INTRO6:
		r = 255;
		g = 60;
		b = 60;
		a = 200;
		break;
	case MBLUR_UNUSED:
		r = 255;
		g = 180;
		b = 180;
		a = 128;
		break;
	}

	if(!BlurOn){
		r *= 0.6f;
		g *= 0.6f;
		b *= 0.6f;
		if(type != 1)
			a *= 0.6f;
		// game clamps to 255 here, but why?
	}
	RwIm2DVertexSetIntRGBA(&Vertex[0], r, g, b, a);
	RwIm2DVertexSetIntRGBA(&Vertex[1], r, g, b, a);
	RwIm2DVertexSetIntRGBA(&Vertex[2], r, g, b, a);
	RwIm2DVertexSetIntRGBA(&Vertex[3], r, g, b, a);

	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERNEAREST);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);

	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, BlurOn ? raster : nil);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, Vertex, 4, Index, 6);

	a = addalpha/2;
	if(a < 30)
		a = 30;

	if(BlurOn && a != 0){	// the second condition should always be true
		RwIm2DVertexSetIntRGBA(&Vertex[0], 255, 255, 255, a);
		RwIm2DVertexSetIntRGBA(&Vertex[1], 255, 255, 255, a);
		RwIm2DVertexSetIntRGBA(&Vertex[2], 255, 255, 255, a);
		RwIm2DVertexSetIntRGBA(&Vertex[3], 255, 255, 255, a);
		RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, Vertex, 4, Index, 6);
	}

	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

STARTPATCHES
	InjectHook(0x50AE40, CMBlur::MotionBlurOpen, PATCH_JUMP);
	InjectHook(0x50B170, CMBlur::MotionBlurClose, PATCH_JUMP);
	InjectHook(0x50A800, CMBlur::CreateImmediateModeData, PATCH_JUMP);
	InjectHook(0x50AD70, CMBlur::MotionBlurRender, PATCH_JUMP);
	InjectHook(0x50A9C0, CMBlur::OverlayRender, PATCH_JUMP);
ENDPATCHES
