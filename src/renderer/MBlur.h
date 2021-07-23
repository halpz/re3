#pragma once

enum FxType
{
	FXTYPE_WATER1,
	FXTYPE_WATER2,
	FXTYPE_BLOOD1,
	FXTYPE_BLOOD2,
	FXTYPE_HEATHAZE,
	FXTYPE_SPLASH1,
	FXTYPE_SPLASH2,
	FXTYPE_SPLASH3
};

class CMBlur
{
public:
	static RwRaster *pFrontBuffer;
	static bool ms_bJustInitialised;
	static bool ms_bScaledBlur;
	static bool BlurOn;
	static float Drunkness;

	static int32 pBufVertCount;

public:
	static RwBool MotionBlurOpen(RwCamera *cam);
	static RwBool MotionBlurClose(void);
	static void CreateImmediateModeData(RwCamera *cam, RwRect *rect);
	static void CreateImmediateModeData(RwCamera *cam, RwRect *rect, RwIm2DVertex *verts, RwRGBA color, float u1Off, float v1Off, float u2Off, float v2Off, float z, int fullTexture);
	static void MotionBlurRender(RwCamera *cam, uint32 red, uint32 green, uint32 blue, uint32 blur, int32 type, uint32 bluralpha);
	static void OverlayRender(RwCamera *cam, RwRaster *raster, RwRGBA color, int32 type, int32 bluralpha);
	static void SetDrunkBlur(float drunkness);
	static void ClearDrunkBlur();
	
	static bool PosInside(RwRect *rect, float x1, float y1, float x2, float y2);
	static bool AddRenderFx(RwCamera *cam, RwRect *rect, float z, FxType type);
	static void OverlayRenderFx(RwCamera *cam, RwRaster *frontBuf);
};
