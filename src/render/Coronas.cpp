#include "common.h"
#include "patcher.h"
#include "Coronas.h"

RwTexture **gpCoronaTexture = (RwTexture**)0x5FAF44;	//[9]

float &CCoronas::LightsMult = *(float*)0x5FB088;	// 1.0
float &CCoronas::SunScreenX = *(float*)0x8F4358;
float &CCoronas::SunScreenY = *(float*)0x8F4354;
bool &CCoronas::bSmallMoon = *(bool*)0x95CD49;
bool &CCoronas::SunBlockedByClouds = *(bool*)0x95CD73;

WRAPPER void CCoronas::Render(void) { EAXJMP(0x4F8FB0); }
WRAPPER void CCoronas::RenderReflections(void) { EAXJMP(0x4F9B40); }
