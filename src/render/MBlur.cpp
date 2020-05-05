#include "common.h"

#include "RwHelper.h"
#include "Camera.h"
#include "MBlur.h"

// Originally taken from RW example 'mblur'

RwRaster *CMBlur::pFrontBuffer;
bool CMBlur::ms_bJustInitialised;
bool CMBlur::BlurOn;

static RwIm2DVertex Vertex[4];
static RwIm2DVertex Vertex2[4];
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
		zero = HALFPX;
		xmax = rect->w + HALFPX;
		ymax = rect->h + HALFPX;
	}else{
		zero = -HALFPX;
		xmax = rect->w - HALFPX;
		ymax = rect->h - HALFPX;
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


	RwIm2DVertexSetScreenX(&Vertex2[0], zero);
	RwIm2DVertexSetScreenY(&Vertex2[0], zero);
	RwIm2DVertexSetScreenZ(&Vertex2[0], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex2[0], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex2[0], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex2[0], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex2[0], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex2[0], 255, 255, 255, 255);

	RwIm2DVertexSetScreenX(&Vertex2[1], zero);
	RwIm2DVertexSetScreenY(&Vertex2[1], ymax);
	RwIm2DVertexSetScreenZ(&Vertex2[1], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex2[1], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex2[1], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex2[1], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex2[1], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex2[1], 255, 255, 255, 255);

	RwIm2DVertexSetScreenX(&Vertex2[2], xmax);
	RwIm2DVertexSetScreenY(&Vertex2[2], ymax);
	RwIm2DVertexSetScreenZ(&Vertex2[2], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex2[2], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex2[2], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex2[2], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex2[2], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex2[2], 255, 255, 255, 255);

	RwIm2DVertexSetScreenX(&Vertex2[3], xmax);
	RwIm2DVertexSetScreenY(&Vertex2[3], zero);
	RwIm2DVertexSetScreenZ(&Vertex2[3], RwIm2DGetNearScreenZ());
	RwIm2DVertexSetCameraZ(&Vertex2[3], RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetRecipCameraZ(&Vertex2[3], 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetU(&Vertex2[3], 1.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetV(&Vertex2[3], 0.0f, 1.0f/RwCameraGetNearClipPlane(cam));
	RwIm2DVertexSetIntRGBA(&Vertex2[3], 255, 255, 255, 255);

}

void
CMBlur::MotionBlurRender(RwCamera *cam, uint32 red, uint32 green, uint32 blue, uint32 blur, int32 type)
{
	RwRGBA color = { (RwUInt8)red, (RwUInt8)green, (RwUInt8)blue, (RwUInt8)blur };
	if(ms_bJustInitialised)
		ms_bJustInitialised = false;
	else
		OverlayRender(cam, pFrontBuffer, color, type);
	if(BlurOn){
		RwRasterPushContext(pFrontBuffer);
		RwRasterRenderFast(RwCameraGetRaster(cam), 0, 0);
		RwRasterPopContext();
	}
}

void
CMBlur::OverlayRender(RwCamera *cam, RwRaster *raster, RwRGBA color, int32 type)
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
		// gta clamps these to 255 (probably a macro or inlined function)
		int ovR = r * 0.6f;
		int ovG = g * 0.6f;
		int ovB = b * 0.6f;
		int ovA = type == MBLUR_SNIPER ? a : a*0.6f;
		RwIm2DVertexSetIntRGBA(&Vertex[0], ovR, ovG, ovB, ovA);
		RwIm2DVertexSetIntRGBA(&Vertex[1], ovR, ovG, ovB, ovA);
		RwIm2DVertexSetIntRGBA(&Vertex[2], ovR, ovG, ovB, ovA);
		RwIm2DVertexSetIntRGBA(&Vertex[3], ovR, ovG, ovB, ovA);
	}else{
		RwIm2DVertexSetIntRGBA(&Vertex2[0], r, g, b, a);
		RwIm2DVertexSetIntRGBA(&Vertex[0], r, g, b, a);
		RwIm2DVertexSetIntRGBA(&Vertex2[1], r, g, b, a);
		RwIm2DVertexSetIntRGBA(&Vertex[1], r, g, b, a);
		RwIm2DVertexSetIntRGBA(&Vertex2[2], r, g, b, a);
		RwIm2DVertexSetIntRGBA(&Vertex[2], r, g, b, a);
		RwIm2DVertexSetIntRGBA(&Vertex2[3], r, g, b, a);
		RwIm2DVertexSetIntRGBA(&Vertex[3], r, g, b, a);
	}

	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERNEAREST);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);

	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, raster);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);

	if(BlurOn){
		if(type == MBLUR_SNIPER){
			RwIm2DVertexSetIntRGBA(&Vertex2[0], r, g, b, 80);
			RwIm2DVertexSetIntRGBA(&Vertex2[1], r, g, b, 80);
			RwIm2DVertexSetIntRGBA(&Vertex2[2], r, g, b, 80);
			RwIm2DVertexSetIntRGBA(&Vertex2[3], r, g, b, 80);
			RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
			// TODO(MIAMI): pBufVertCount = 0;
		}else{
			RwIm2DVertexSetIntRGBA(&Vertex2[0], r*2, g*2, b*2, 30);
			RwIm2DVertexSetIntRGBA(&Vertex2[1], r*2, g*2, b*2, 30);
			RwIm2DVertexSetIntRGBA(&Vertex2[2], r*2, g*2, b*2, 30);
			RwIm2DVertexSetIntRGBA(&Vertex2[3], r*2, g*2, b*2, 30);
			RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);

			RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, Vertex2, 4, Index, 6);

			RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);

			RwIm2DVertexSetIntRGBA(&Vertex2[0], r, g, b, a);
			RwIm2DVertexSetIntRGBA(&Vertex[0], r, g, b, a);
			RwIm2DVertexSetIntRGBA(&Vertex2[1], r, g, b, a);
			RwIm2DVertexSetIntRGBA(&Vertex[1], r, g, b, a);
			RwIm2DVertexSetIntRGBA(&Vertex2[2], r, g, b, a);
			RwIm2DVertexSetIntRGBA(&Vertex[2], r, g, b, a);
			RwIm2DVertexSetIntRGBA(&Vertex2[3], r, g, b, a);
			RwIm2DVertexSetIntRGBA(&Vertex[3], r, g, b, a);
			RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, Vertex, 4, Index, 6);
			RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, Vertex2, 4, Index, 6);
		}
	}

	// TODO(MIAMI): drunkness

	// TODO(MIAMI): OverlayRenderFx

	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}
