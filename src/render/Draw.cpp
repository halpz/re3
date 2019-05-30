#include "common.h"
#include "patcher.h"
#include "Draw.h"

float &CDraw::ms_fNearClipZ = *(float*)0x8E2DC4;
float &CDraw::ms_fFarClipZ = *(float*)0x9434F0;
float &CDraw::ms_fFOV = *(float*)0x5FBC6C;

static float hFov2vFov(float hfov)
{
	float w = SCREENW;
	float h = SCREENH;

	// => tan(hFOV/2) = tan(vFOV/2)*aspectRatio
	// => tan(vFOV/2) = tan(hFOV/2)/aspectRatio
	float ar1 = 4.0/3.0;
	float ar2 = w/h;
	hfov = DEGTORAD(hfov);
	float vfov = atan(tan(hfov/2) / ar1) *2;
	hfov = atan(tan(vfov/2) * ar2) *2;
	return RADTODEG(hfov);
}

void
CDraw::SetFOV(float fov)
{
// TODO: fix FOV here or somewhere else?
//	ms_fFOV = hFov2vFov(fov);
	ms_fFOV = fov;
}

STARTPATCHES
	InjectHook(0x4FE7B0, CDraw::SetFOV, PATCH_JUMP);
ENDPATCHES
