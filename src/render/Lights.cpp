#include "common.h"
#include <rwcore.h>
#include <rpworld.h>
#include "patcher.h"
#include "Lights.h"
#include "Timecycle.h"
#include "Coronas.h"
#include "Weather.h"
#include "CullZones.h"
#include "Frontend.h"

RpLight *&pAmbient = *(RpLight**)0x885B6C;
RpLight *&pDirect = *(RpLight**)0x880F7C;

RwRGBAReal &AmbientLightColourForFrame = *(RwRGBAReal*)0x6F46F8;
RwRGBAReal &AmbientLightColourForFrame_PedsCarsAndObjects = *(RwRGBAReal*)0x6F1D10;
RwRGBAReal &DirectionalLightColourForFrame = *(RwRGBAReal*)0x87C6B8;

RwRGBAReal &AmbientLightColour = *(RwRGBAReal*)0x86B0F8;
RwRGBAReal &DirectionalLightColour = *(RwRGBAReal*)0x72E308;

void
SetLightsWithTimeOfDayColour(RpWorld *)
{
	CVector vec1, vec2, vecsun;
	RwMatrix mat;

	if(pAmbient){
		AmbientLightColourForFrame.red = CTimeCycle::GetAmbientRed() * CCoronas::LightsMult;
		AmbientLightColourForFrame.green = CTimeCycle::GetAmbientGreen() * CCoronas::LightsMult;
		AmbientLightColourForFrame.blue = CTimeCycle::GetAmbientBlue() * CCoronas::LightsMult;
		if(CWeather::LightningFlash && !CCullZones::CamNoRain()){
			AmbientLightColourForFrame.red = 1.0f;
			AmbientLightColourForFrame.green = 1.0f;
			AmbientLightColourForFrame.blue = 1.0f;
		}
		AmbientLightColourForFrame_PedsCarsAndObjects.red = min(1.0f, AmbientLightColourForFrame.red*1.3f);
		AmbientLightColourForFrame_PedsCarsAndObjects.green = min(1.0f, AmbientLightColourForFrame.green*1.3f);
		AmbientLightColourForFrame_PedsCarsAndObjects.blue = min(1.0f, AmbientLightColourForFrame.blue*1.3f);
		RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
	}

	if(pDirect){
		DirectionalLightColourForFrame.red = CTimeCycle::GetDirectionalRed() * CCoronas::LightsMult;
		DirectionalLightColourForFrame.green = CTimeCycle::GetDirectionalGreen() * CCoronas::LightsMult;
		DirectionalLightColourForFrame.blue = CTimeCycle::GetDirectionalBlue() * CCoronas::LightsMult;
		RpLightSetColor(pDirect, &DirectionalLightColourForFrame);

		vecsun = CTimeCycle::m_VectorToSun[CTimeCycle::m_CurrentStoredValue];
		vec1 = CVector(0.0f, 0.0f, 1.0f);
		vec2 = CrossProduct(vec1, vecsun);
		vec2.Normalise();
		vec1 = CrossProduct(vec2, vecsun);
		mat.at.x = -vecsun.x;
		mat.at.y = -vecsun.y;
		mat.at.z = -vecsun.z;
		mat.right.x = vec1.x;
		mat.right.y = vec1.y;
		mat.right.z = vec1.z;
		mat.up.x = vec2.x;
		mat.up.y = vec2.y;
		mat.up.z = vec2.z;
		RwFrameTransform(RpLightGetFrame(pDirect), &mat, rwCOMBINEREPLACE);
	}

	if(CMenuManager::m_PrefsBrightness > 256){
		float f1 = 2.0f * (CMenuManager::m_PrefsBrightness/256.0f - 1.0f) * 0.6f + 1.0f;
		float f2 = 3.0f * (CMenuManager::m_PrefsBrightness/256.0f - 1.0f) * 0.6f + 1.0f;

		AmbientLightColourForFrame.red = min(1.0f, AmbientLightColourForFrame.red * f2);
		AmbientLightColourForFrame.green = min(1.0f, AmbientLightColourForFrame.green * f2);
		AmbientLightColourForFrame.blue = min(1.0f, AmbientLightColourForFrame.blue * f2);
		AmbientLightColourForFrame_PedsCarsAndObjects.red = min(1.0f, AmbientLightColourForFrame_PedsCarsAndObjects.red * f1);
		AmbientLightColourForFrame_PedsCarsAndObjects.green = min(1.0f, AmbientLightColourForFrame_PedsCarsAndObjects.green * f1);
		AmbientLightColourForFrame_PedsCarsAndObjects.blue = min(1.0f, AmbientLightColourForFrame_PedsCarsAndObjects.blue * f1);
#ifdef FIX_BUGS
		DirectionalLightColourForFrame.red = min(1.0f, DirectionalLightColourForFrame.red * f1);
		DirectionalLightColourForFrame.green = min(1.0f, DirectionalLightColourForFrame.green * f1);
		DirectionalLightColourForFrame.blue = min(1.0f, DirectionalLightColourForFrame.blue * f1);
#else
		DirectionalLightColourForFrame.red = min(1.0f, AmbientLightColourForFrame.red * f1);
		DirectionalLightColourForFrame.green = min(1.0f, AmbientLightColourForFrame.green * f1);
		DirectionalLightColourForFrame.blue = min(1.0f, AmbientLightColourForFrame.blue * f1);
#endif
	}
}

void
SetAmbientAndDirectionalColours(float f)
{
	AmbientLightColour.red = AmbientLightColourForFrame.red * f;
	AmbientLightColour.green = AmbientLightColourForFrame.green * f;
	AmbientLightColour.blue = AmbientLightColourForFrame.blue * f;

	DirectionalLightColour.red = DirectionalLightColourForFrame.red * f;
	DirectionalLightColour.green = DirectionalLightColourForFrame.green * f;
	DirectionalLightColour.blue = DirectionalLightColourForFrame.blue * f;

	RpLightSetColor(pAmbient, &AmbientLightColour);
	RpLightSetColor(pDirect, &DirectionalLightColour);
}

void
SetBrightMarkerColours(float f)
{
	AmbientLightColour.red = 0.6f;
	AmbientLightColour.green = 0.6f;
	AmbientLightColour.blue = 0.6f;

	DirectionalLightColour.red = (1.0f - DirectionalLightColourForFrame.red) * 0.4f + DirectionalLightColourForFrame.red;
	DirectionalLightColour.green = (1.0f - DirectionalLightColourForFrame.green) * 0.4f + DirectionalLightColourForFrame.green;
	DirectionalLightColour.blue = (1.0f - DirectionalLightColourForFrame.blue) * 0.4f + DirectionalLightColourForFrame.blue;

	RpLightSetColor(pAmbient, &AmbientLightColour);
	RpLightSetColor(pDirect, &DirectionalLightColour);
}

void
ReSetAmbientAndDirectionalColours(void)
{
	RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
	RpLightSetColor(pDirect, &DirectionalLightColourForFrame);
}

void
DeActivateDirectional(void)
{
	RpLightSetFlags(pDirect, 0);
}

void
ActivateDirectional(void)
{
	RpLightSetFlags(pDirect, rpLIGHTLIGHTATOMICS);
}

void
SetAmbientColours(void)
{
	RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
}

void
SetAmbientColoursForPedsCarsAndObjects(void)
{
	RpLightSetColor(pAmbient, &AmbientLightColourForFrame_PedsCarsAndObjects);
}

uint8 IndicateR[] = { 0, 255, 0, 0, 255, 255, 0 };
uint8 IndicateG[] = { 0, 0, 255, 0, 255, 0, 255 };
uint8 IndicateB[] = { 0, 0, 0, 255, 0, 255, 255 };

void
SetAmbientColoursToIndicateRoadGroup(int i)
{
	AmbientLightColour.red   = IndicateR[i%7]/255.0f;
	AmbientLightColour.green = IndicateG[i%7]/255.0f;
	AmbientLightColour.blue  = IndicateB[i%7]/255.0f;
	RpLightSetColor(pAmbient, &AmbientLightColour);
}

STARTPATCHES
	InjectHook(0x526510, SetLightsWithTimeOfDayColour, PATCH_JUMP);
	InjectHook(0x526DE0, SetAmbientAndDirectionalColours, PATCH_JUMP);
	InjectHook(0x526E60, SetBrightMarkerColours, PATCH_JUMP);
	InjectHook(0x526F10, ReSetAmbientAndDirectionalColours, PATCH_JUMP);
	InjectHook(0x526F40, DeActivateDirectional, PATCH_JUMP);
	InjectHook(0x526F50, ActivateDirectional, PATCH_JUMP);
	InjectHook(0x526F60, SetAmbientColours, PATCH_JUMP);
	InjectHook(0x526F80, SetAmbientColoursForPedsCarsAndObjects, PATCH_JUMP);
ENDPATCHES
