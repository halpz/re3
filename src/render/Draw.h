#pragma once

class CDraw
{
private:
	static float &ms_fNearClipZ;
	static float &ms_fFarClipZ;
	static float &ms_fFOV;
public:
	static void SetNearClipZ(float nearclip) { ms_fNearClipZ = nearclip; }
	static float GetNearClipZ(void) { return ms_fNearClipZ; }
	static void SetFarClipZ(float farclip) { ms_fFarClipZ = farclip; }
	static float GetFarClipZ(void) { return ms_fFarClipZ; }
	static void SetFOV(float fov);
	static float GetFOV(void) { return ms_fFOV; }
};
