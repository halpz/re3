#include "common.h"
#include "patcher.h"
#include "Draw.h"
#include "Frontend.h"
#include "Camera.h"

#ifdef ASPECT_RATIO_SCALE
float CDraw::ms_fAspectRatio = DEFAULT_ASPECT_RATIO;
#endif

float &CDraw::ms_fNearClipZ = *(float*)0x8E2DC4;
float &CDraw::ms_fFarClipZ = *(float*)0x9434F0;
float &CDraw::ms_fFOV = *(float*)0x5FBC6C;

uint8 &CDraw::FadeValue = *(uint8*)0x95CD68;
uint8 &CDraw::FadeRed = *(uint8*)0x95CD90;
uint8 &CDraw::FadeGreen = *(uint8*)0x95CD71;
uint8 &CDraw::FadeBlue = *(uint8*)0x95CD53;

float
CDraw::FindAspectRatio(void)
{
#ifndef ASPECT_RATIO_SCALE
	if(FrontEndMenuManager.m_PrefsUseWideScreen)	
		return 16.0f/9.0f;
	else
		return 4.0f/3.0f;
#else
	switch (FrontEndMenuManager.m_PrefsUseWideScreen) {
	case AR_AUTO:
		return SCREEN_WIDTH / SCREEN_HEIGHT;
	case AR_4_3:
		return 4.0f / 3.0f;
	case AR_16_9:
		return 16.0f / 9.0f;
	};
#endif
}

#ifdef ASPECT_RATIO_SCALE
// convert a 4:3 hFOV to vFOV,
// then convert that vFOV to hFOV for our aspect ratio,
// i.e. HOR+
float
CDraw::ConvertFOV(float hfov)
{
	// => tan(hFOV/2) = tan(vFOV/2)*aspectRatio
	// => tan(vFOV/2) = tan(hFOV/2)/aspectRatio
	float ar1 = DEFAULT_ASPECT_RATIO;
	float ar2 = GetAspectRatio();
	hfov = DEGTORAD(hfov);
	float vfov = atan(tan(hfov/2) / ar1) *2;
	hfov = atan(tan(vfov/2) * ar2) *2;
	return RADTODEG(hfov);
}
#endif

void
CDraw::SetFOV(float fov)
{
#ifdef ASPECT_RATIO_SCALE
	ms_fFOV = ConvertFOV(fov);
#else
	ms_fFOV = fov;
#endif
}

STARTPATCHES
	InjectHook(0x4FE7B0, CDraw::SetFOV, PATCH_JUMP);

	Nop(0x46B618, 2);
	Patch<float>(0x5F0A64, 1.3333334f);
ENDPATCHES
