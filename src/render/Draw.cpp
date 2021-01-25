#include "common.h"

#include "Draw.h"
#include "Frontend.h"
#include "Camera.h"
#include "CutsceneMgr.h"

float CDraw::ms_fAspectRatio = DEFAULT_ASPECT_RATIO;
#ifdef ASPECT_RATIO_SCALE
float CDraw::ms_fScaledFOV = 45.0f;
#endif

float CDraw::ms_fNearClipZ;
float CDraw::ms_fFarClipZ;
float CDraw::ms_fFOV = 45.0f;
float CDraw::ms_fLODDistance;

uint8 CDraw::FadeValue;
uint8 CDraw::FadeRed;
uint8 CDraw::FadeGreen;
uint8 CDraw::FadeBlue;

#ifdef PROPER_SCALING	
bool CDraw::ms_bProperScaling = true;
#endif
#ifdef  FIX_RADAR
bool CDraw::ms_bFixRadar = true;	
#endif
#ifdef FIX_SPRITES
bool CDraw::ms_bFixSprites = true;	
#endif

float
CDraw::CalculateAspectRatio(void)
{
	if (FrontEndMenuManager.m_PrefsUseWideScreen) {
#ifdef ASPECT_RATIO_SCALE
		if (TheCamera.m_WideScreenOn)
			CDraw::ms_fAspectRatio = FrontEndMenuManager.m_PrefsUseWideScreen == AR_AUTO ?
				(5.f / 3.f) * (SCREEN_WIDTH / SCREEN_HEIGHT) / (16.f / 9.f) :
				5.f / 3.f; // It's used on theatrical showings according to Wiki
		else
			CDraw::ms_fAspectRatio = FrontEndMenuManager.m_PrefsUseWideScreen == AR_AUTO ? SCREEN_WIDTH / SCREEN_HEIGHT : 16.f / 9.f;
#else
		if (TheCamera.m_WideScreenOn)
			CDraw::ms_fAspectRatio = 5.f / 3.f; // It's used on theatrical showings according to Wiki
		else
			CDraw::ms_fAspectRatio = 16.f / 9.f;
#endif
	} else if (TheCamera.m_WideScreenOn) {
		CDraw::ms_fAspectRatio = 5.f/4.f;
	} else {
		CDraw::ms_fAspectRatio = 4.f/3.f;
	}
	return CDraw::ms_fAspectRatio;
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
	float vfov = Atan(tan(hfov/2) / ar1) *2;
	hfov = Atan(tan(vfov/2) * ar2) *2;
	return RADTODEG(hfov);
}
#endif

void
CDraw::SetFOV(float fov)
{
#ifdef ASPECT_RATIO_SCALE
	if (!CCutsceneMgr::IsRunning())
		ms_fScaledFOV = ConvertFOV(fov);
	else
		ms_fScaledFOV = fov;
#endif
	ms_fFOV = fov;
}

#ifdef PROPER_SCALING	
float CDraw::ScaleY(float y)
{
	return ms_bProperScaling ? y : y * ((float)DEFAULT_SCREEN_HEIGHT/SCREEN_HEIGHT_NTSC);
}
#endif