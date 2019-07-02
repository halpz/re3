#pragma once

#define HUD_SCALE 0.8f
#define DEFAULT_SCALE 1.0f

class CDraw
{
private:
	static float &ms_fNearClipZ;
	static float &ms_fFarClipZ;
	static float &ms_fFOV;
	static float ms_fAspectRatio;
	static float ms_fScreenMultiplier;

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

	static void CalculateAspectRatio();
	static float GetAspectRatio(void) { return ms_fAspectRatio; }
	static void SetScreenMult(float mult) { ms_fScreenMultiplier = mult; };
	static float GetScreenMult(void) { return ms_fScreenMultiplier; };
};
