#pragma once

enum eAspectRatio 
{
	// Make sure these work the same as FrontEndMenuManager.m_PrefsUseWideScreen
	// without widescreen support
	AR_4_3,
	AR_16_9,

	AR_AUTO,
};

class CDraw
{
private:
	static float &ms_fNearClipZ;
	static float &ms_fFarClipZ;
	static float &ms_fFOV;
	static float ms_fLODDistance;	// unused

#ifdef ASPECT_RATIO_SCALE
	// we use this variable to scale a lot of 2D elements
	// so better cache it
	static float ms_fAspectRatio;
#endif

public:
	static uint8 &FadeValue;
	static uint8 &FadeRed;
	static uint8 &FadeGreen;
	static uint8 &FadeBlue;

	static void SetNearClipZ(float nearclip) { ms_fNearClipZ = nearclip; }
	static float GetNearClipZ(void) { return ms_fNearClipZ; }
	static void SetFarClipZ(float farclip) { ms_fFarClipZ = farclip; }
	static float GetFarClipZ(void) { return ms_fFarClipZ; }

	static void SetFOV(float fov);
	static float GetFOV(void) { return ms_fFOV; }

	static float FindAspectRatio(void);
#ifdef ASPECT_RATIO_SCALE
	static float ConvertFOV(float fov);
	static float GetAspectRatio(void) { return ms_fAspectRatio; }
	static void SetAspectRatio(float ratio) { ms_fAspectRatio = ratio; }
#else
	static float GetAspectRatio(void) { return FindAspectRatio(); }
#endif
};
