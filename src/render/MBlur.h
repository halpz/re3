#pragma once

enum FxType
{
	FXTYPE_0 = 0,
	FXTYPE_1,
	FXTYPE_2,
	FXTYPE_3,
	FXTYPE_4,
	FXTYPE_5,
};

class CMBlur
{
public:
	static RwRaster *pFrontBuffer;
	static bool ms_bJustInitialised;
	static bool ms_bScaledBlur;
	static bool BlurOn;
	static float Drunkness;

public:
	static RwBool MotionBlurOpen(RwCamera *cam);
	static RwBool MotionBlurClose(void);
	static void CreateImmediateModeData(RwCamera *cam, RwRect *rect);
	static void MotionBlurRender(RwCamera *cam, uint32 red, uint32 green, uint32 blue, uint32 blur, int32 type, uint32 bluralpha);
	static void OverlayRender(RwCamera *cam, RwRaster *raster, RwRGBA color, int32 type, int32 bluralpha);
	static void SetDrunkBlur(float drunkness);
	static void ClearDrunkBlur();
	
	//TODO
	static void AddRenderFx(RwCamera *,RwRect *,float,FxType)
	{}
};
