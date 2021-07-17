#pragma once

enum eAspectRatio 
{
	// Make sure these work the same as FrontEndMenuManager.m_PrefsUseWideScreen
	// without widescreen support
	AR_AUTO,
	AR_4_3,
	AR_5_4,
	AR_16_10,
	AR_16_9,
	AR_21_9,

	AR_MAX,
};

class CDraw
{
private:
	static float ms_fNearClipZ;
	static float ms_fFarClipZ;
	static float ms_fFOV;
	// we use this variable to scale a lot of 2D elements
	// so better cache it
	static float ms_fAspectRatio;
#ifdef ASPECT_RATIO_SCALE
	// similar thing for 3D rendering
	static float ms_fScaledFOV;
#endif
public:
	static float ms_fLODDistance;	// set but unused?

	static uint8 FadeValue;
	static uint8 FadeRed;
	static uint8 FadeGreen;
	static uint8 FadeBlue;
	
#ifdef PROPER_SCALING	
	static bool ms_bProperScaling;
#endif
#ifdef FIX_RADAR
	static bool ms_bFixRadar;	
#endif
#ifdef FIX_SPRITES
	static bool ms_bFixSprites;	
#endif

	static void SetNearClipZ(float nearclip) { ms_fNearClipZ = nearclip; }
	static float GetNearClipZ(void) { return ms_fNearClipZ; }
	static void SetFarClipZ(float farclip) { ms_fFarClipZ = farclip; }
	static float GetFarClipZ(void) { return ms_fFarClipZ; }

	static void SetFOV(float fov);
	static float GetFOV(void) { return ms_fFOV; }
#ifdef ASPECT_RATIO_SCALE
	static float GetScaledFOV(void) { return ms_fScaledFOV; }
#else
	static float GetScaledFOV(void) { return ms_fFOV; }
#endif

	static float CalculateAspectRatio(void);
#ifdef ASPECT_RATIO_SCALE
	static float ConvertFOV(float fov);
#endif
	static float GetAspectRatio(void) { return ms_fAspectRatio; }
	static void SetAspectRatio(float ratio) { ms_fAspectRatio = ratio; }
#ifdef PROPER_SCALING	
	static float ScaleY(float y);
#endif 
};
