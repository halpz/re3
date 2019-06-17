#include "common.h"
#include "patcher.h"
#include "main.h"
#include "Clock.h"
#include "Weather.h"
#include "Camera.h"
#include "Shadows.h"
#include "CullZones.h"
#include "CutsceneMgr.h"
#include "FileMgr.h"
#include "Timecycle.h"

int   (*CTimeCycle::m_nAmbientRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x86AF78;
int   (*CTimeCycle::m_nAmbientGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x665308;
int   (*CTimeCycle::m_nAmbientBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x72CF88;
int   (*CTimeCycle::m_nDirectionalRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6FAB78;
int   (*CTimeCycle::m_nDirectionalGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6F4528;
int   (*CTimeCycle::m_nDirectionalBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x83CE58;
int   (*CTimeCycle::m_nSkyTopRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x87FB90;
int   (*CTimeCycle::m_nSkyTopGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x8460A8;
int   (*CTimeCycle::m_nSkyTopBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x87B158;
int   (*CTimeCycle::m_nSkyBottomRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6FA960;
int   (*CTimeCycle::m_nSkyBottomGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x70D6A8;
int   (*CTimeCycle::m_nSkyBottomBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x83D288;
int   (*CTimeCycle::m_nSunCoreRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x878360;
int   (*CTimeCycle::m_nSunCoreGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6EE088;
int   (*CTimeCycle::m_nSunCoreBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x773A68;
int   (*CTimeCycle::m_nSunCoronaRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x664B60;
int   (*CTimeCycle::m_nSunCoronaGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6F01E0;
int   (*CTimeCycle::m_nSunCoronaBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6E6340;
float (*CTimeCycle::m_fSunSize)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x733510;
float (*CTimeCycle::m_fSpriteSize)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x87F820;
float (*CTimeCycle::m_fSpriteBrightness)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x6E96F0;
short (*CTimeCycle::m_nShadowStrength)[NUMWEATHERS] = (short(*)[NUMWEATHERS])0x83CFD8;
short (*CTimeCycle::m_nLightShadowStrength)[NUMWEATHERS] = (short(*)[NUMWEATHERS])0x72B0F8;
short (*CTimeCycle::m_nTreeShadowStrength)[NUMWEATHERS] = (short(*)[NUMWEATHERS])0x733450;
float (*CTimeCycle::m_fFogStart)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x8806C8;
float (*CTimeCycle::m_fFarClip)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x8804E0;
float (*CTimeCycle::m_fLightsOnGroundBrightness)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x83D108;
int   (*CTimeCycle::m_nLowCloudsRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x726770;
int   (*CTimeCycle::m_nLowCloudsGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x87BF08;
int   (*CTimeCycle::m_nLowCloudsBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x87FA10;
int   (*CTimeCycle::m_nFluffyCloudsTopRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x70F2B0;
int   (*CTimeCycle::m_nFluffyCloudsTopGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x72D288;
int   (*CTimeCycle::m_nFluffyCloudsTopBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x86B108;
int   (*CTimeCycle::m_nFluffyCloudsBottomRed)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6E8DA8;
int   (*CTimeCycle::m_nFluffyCloudsBottomGreen)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x715AA8;
int   (*CTimeCycle::m_nFluffyCloudsBottomBlue)[NUMWEATHERS] = (int(*)[NUMWEATHERS])0x6EE2D0;
float (*CTimeCycle::m_fBlurRed)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x87C7E0;
float (*CTimeCycle::m_fBlurGreen)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x774C10;
float (*CTimeCycle::m_fBlurBlue)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x8784E0;
float (*CTimeCycle::m_fBlurAlpha)[NUMWEATHERS] = (float(*)[NUMWEATHERS])0x733690;

float &CTimeCycle::m_fCurrentAmbientRed = *(float*)0x8F29B4;
float &CTimeCycle::m_fCurrentAmbientGreen = *(float*)0x94144C;
float &CTimeCycle::m_fCurrentAmbientBlue = *(float*)0x942FC0;
float &CTimeCycle::m_fCurrentDirectionalRed = *(float*)0x8F29D8;
float &CTimeCycle::m_fCurrentDirectionalGreen = *(float*)0x940594;
float &CTimeCycle::m_fCurrentDirectionalBlue = *(float*)0x942FAC;
int   &CTimeCycle::m_nCurrentSkyTopRed = *(int*)0x9403C0;
int   &CTimeCycle::m_nCurrentSkyTopGreen = *(int*)0x943074;
int   &CTimeCycle::m_nCurrentSkyTopBlue = *(int*)0x8F29B8;
int   &CTimeCycle::m_nCurrentSkyBottomRed = *(int*)0x9414D0;
int   &CTimeCycle::m_nCurrentSkyBottomGreen = *(int*)0x8F2BD0;
int   &CTimeCycle::m_nCurrentSkyBottomBlue = *(int*)0x8F625C;
int   &CTimeCycle::m_nCurrentSunCoreRed = *(int*)0x8F2534;
int   &CTimeCycle::m_nCurrentSunCoreGreen = *(int*)0x8F6264;
int   &CTimeCycle::m_nCurrentSunCoreBlue = *(int*)0x94149C;
int   &CTimeCycle::m_nCurrentSunCoronaRed = *(int*)0x8F2C1C;
int   &CTimeCycle::m_nCurrentSunCoronaGreen = *(int*)0x885B54;
int   &CTimeCycle::m_nCurrentSunCoronaBlue = *(int*)0x880F60;
float &CTimeCycle::m_fCurrentSunSize = *(float*)0x940588;
float &CTimeCycle::m_fCurrentSpriteSize = *(float*)0x8F1AA8;
float &CTimeCycle::m_fCurrentSpriteBrightness = *(float*)0x8F5FDC;
int   &CTimeCycle::m_nCurrentShadowStrength = *(int*)0x95CC76;
int   &CTimeCycle::m_nCurrentLightShadowStrength = *(int*)0x95CC66;
int   &CTimeCycle::m_nCurrentTreeShadowStrength = *(int*)0x95CC86;
float &CTimeCycle::m_fCurrentFogStart = *(float*)0x8F1AE0;
float &CTimeCycle::m_fCurrentFarClip = *(float*)0x8F5FD8;
float &CTimeCycle::m_fCurrentLightsOnGroundBrightness = *(float*)0x8F1B60;
int   &CTimeCycle::m_nCurrentLowCloudsRed = *(int*)0x95CB54;
int   &CTimeCycle::m_nCurrentLowCloudsGreen = *(int*)0x95CB48;
int   &CTimeCycle::m_nCurrentLowCloudsBlue = *(int*)0x95CC1C;
int   &CTimeCycle::m_nCurrentFluffyCloudsTopRed = *(int*)0x8F2550;
int   &CTimeCycle::m_nCurrentFluffyCloudsTopGreen = *(int*)0x8F59CC;
int   &CTimeCycle::m_nCurrentFluffyCloudsTopBlue = *(int*)0x941434;
int   &CTimeCycle::m_nCurrentFluffyCloudsBottomRed = *(int*)0x8F1A38;
int   &CTimeCycle::m_nCurrentFluffyCloudsBottomGreen = *(int*)0x8E28B8;
int   &CTimeCycle::m_nCurrentFluffyCloudsBottomBlue = *(int*)0x8F3960;
float &CTimeCycle::m_fCurrentBlurRed = *(float*)0x8F6000;
float &CTimeCycle::m_fCurrentBlurGreen = *(float*)0x9405A0;
float &CTimeCycle::m_fCurrentBlurBlue = *(float*)0x8F250C;
float &CTimeCycle::m_fCurrentBlurAlpha = *(float*)0x940728;
int   &CTimeCycle::m_nCurrentFogColourRed = *(int*)0x940714;
int   &CTimeCycle::m_nCurrentFogColourGreen = *(int*)0x8E2A60;
int   &CTimeCycle::m_nCurrentFogColourBlue = *(int*)0x8F57EC;

int   &CTimeCycle::m_FogReduction = *(int*)0x880FB8;

int   &CTimeCycle::m_CurrentStoredValue = *(int*)0x94057C;
CVector *CTimeCycle::m_VectorToSun = (CVector*)0x665548;	// [16]
float *CTimeCycle::m_fShadowFrontX = (float*)0x72CE90;
float *CTimeCycle::m_fShadowFrontY = (float*)0x72CE50;
float *CTimeCycle::m_fShadowSideX = (float*)0x87C708;
float *CTimeCycle::m_fShadowSideY = (float*)0x87C6C8;
float *CTimeCycle::m_fShadowDisplacementX = (float*)0x6F0748;
float *CTimeCycle::m_fShadowDisplacementY = (float*)0x6F0788;


void
CTimeCycle::Initialise(void)
{
	int w, h;
	int li, bi;
	char line[1040];

	int ambR, ambG, ambB;
	int dirR, dirG, dirB;
	int skyTopR, skyTopG, skyTopB;
	int skyBotR, skyBotG, skyBotB;
	int sunCoreR, sunCoreG, sunCoreB;
	int sunCoronaR, sunCoronaG, sunCoronaB;
	float sunSz, sprSz, sprBght;
	int shad, lightShad, treeShad;
	float farClp, fogSt, lightGnd;
	int cloudR, cloudG, cloudB;
	int fluffyTopR, fluffyTopG, fluffyTopB;
	int fluffyBotR, fluffyBotG, fluffyBotB;
	float blurR, blurG, blurB, blurA;

	debug("Intialising CTimeCycle...\n");

	CFileMgr::SetDir("DATA");
	CFileMgr::LoadFile("TIMECYC.DAT", work_buff, sizeof(work_buff), "rb");
	CFileMgr::SetDir("");

	line[0] = '\0';
	bi = 0;
	for(w = 0; w < NUMWEATHERS; w++)
		for(h = 0; h < NUMHOURS; h++){
			li = 0;
			while(work_buff[bi] == '/'){
				while(work_buff[bi] != '\n')
					bi++;
				bi++;
			}
			while(work_buff[bi] != '\n')
				line[li++] = work_buff[bi++];
			line[li] = '\0';
			bi++;

			sscanf(line, "%d %d %d  %d %d %d  %d %d %d  %d %d %d "
			             "%d %d %d  %d %d %d  %f %f %f %d %d %d %f %f %f "
			             "%d %d %d  %d %d %d  %d %d %d  %f %f %f %f",
				&ambR, &ambG, &ambB,
				 &dirR, &dirG, &dirB,
				 &skyTopR, &skyTopG, &skyTopB,
				 &skyBotR, &skyBotG, &skyBotB,
				&sunCoreR, &sunCoreG, &sunCoreB,
				 &sunCoronaR, &sunCoronaG, &sunCoronaB,
				 &sunSz, &sprSz, &sprBght,
				 &shad, &lightShad, &treeShad,
				 &farClp, &fogSt, &lightGnd,
				&cloudR, &cloudG, &cloudB,
				 &fluffyTopR, &fluffyTopG, &fluffyTopB,
				 &fluffyBotR, &fluffyBotG, &fluffyBotB,
				 &blurR, &blurG, &blurB, &blurA);

			m_nAmbientRed[h][w] = ambR;
			m_nAmbientGreen[h][w] = ambG;
			m_nAmbientBlue[h][w] = ambB;
			m_nDirectionalRed[h][w] = dirR;
			m_nDirectionalGreen[h][w] = dirG;
			m_nDirectionalBlue[h][w] = dirB;
			m_nSkyTopRed[h][w] = skyTopR;
			m_nSkyTopGreen[h][w] = skyTopG;
			m_nSkyTopBlue[h][w] = skyTopB;
			m_nSkyBottomRed[h][w] = skyBotR;
			m_nSkyBottomGreen[h][w] = skyBotG;
			m_nSkyBottomBlue[h][w] = skyBotB;
			m_nSunCoreRed[h][w] = sunCoreR;
			m_nSunCoreGreen[h][w] = sunCoreG;
			m_nSunCoreBlue[h][w] = sunCoreB;
			m_nSunCoronaRed[h][w] = sunCoronaR;
			m_nSunCoronaGreen[h][w] = sunCoronaG;
			m_nSunCoronaBlue[h][w] = sunCoronaB;
			m_fSunSize[h][w] = sunSz;
			m_fSpriteSize[h][w] = sprSz;
			m_fSpriteBrightness[h][w] = sprBght;
			m_nShadowStrength[h][w] = shad;
			m_nLightShadowStrength[h][w] = lightShad;
			m_nTreeShadowStrength[h][w] = treeShad;
			m_fFarClip[h][w] = farClp;
			m_fFogStart[h][w] = fogSt;
			m_fLightsOnGroundBrightness[h][w] = lightGnd;
			m_nLowCloudsRed[h][w] = cloudR;
			m_nLowCloudsGreen[h][w] = cloudG;
			m_nLowCloudsBlue[h][w] = cloudB;
			m_nFluffyCloudsTopRed[h][w] = fluffyTopR;
			m_nFluffyCloudsTopGreen[h][w] = fluffyTopG;
			m_nFluffyCloudsTopBlue[h][w] = fluffyTopB;
			m_nFluffyCloudsBottomRed[h][w] = fluffyBotR;
			m_nFluffyCloudsBottomGreen[h][w] = fluffyBotG;
			m_nFluffyCloudsBottomBlue[h][w] = fluffyBotB;
			m_fBlurRed[h][w] = blurR;
			m_fBlurGreen[h][w] = blurG;
			m_fBlurBlue[h][w] = blurB;
			m_fBlurAlpha[h][w] = blurA;
		}

	m_FogReduction = 0;

	debug("CTimeCycle ready\n");
}

void
CTimeCycle::Update(void)
{
	int h1 = CClock::GetHours();
	int h2 = (h1+1)%24;
	int w1 = CWeather::OldWeatherType;
	int w2 = CWeather::NewWeatherType;
	float timeInterp = CClock::GetMinutes()/60.0f;
	// coefficients for a bilinear interpolation
	float c0 = (1.0f-timeInterp) * (1.0f-CWeather::InterpolationValue);
	float c1 = timeInterp * (1.0f-CWeather::InterpolationValue);
	float c2 = (1.0f-timeInterp) * CWeather::InterpolationValue;
	float c3 = timeInterp * CWeather::InterpolationValue;

#define INTERP(v) v[h1][w1]*c0 + v[h2][w1]*c1 + v[h1][w2]*c2 + v[h2][w2]*c3;

	m_nCurrentSkyTopRed = INTERP(m_nSkyTopRed);
	m_nCurrentSkyTopGreen = INTERP(m_nSkyTopGreen);
	m_nCurrentSkyTopBlue = INTERP(m_nSkyTopBlue);

	m_nCurrentSkyBottomRed = INTERP(m_nSkyBottomRed);
	m_nCurrentSkyBottomGreen = INTERP(m_nSkyBottomGreen);
	m_nCurrentSkyBottomBlue = INTERP(m_nSkyBottomBlue);

	m_fCurrentAmbientRed = INTERP(m_nAmbientRed);
	m_fCurrentAmbientGreen = INTERP(m_nAmbientGreen);
	m_fCurrentAmbientBlue = INTERP(m_nAmbientBlue);
	m_fCurrentAmbientRed /= 255.0f;
	m_fCurrentAmbientGreen /= 255.0f;
	m_fCurrentAmbientBlue /= 255.0f;

	m_fCurrentDirectionalRed = INTERP(m_nDirectionalRed);
	m_fCurrentDirectionalGreen = INTERP(m_nDirectionalGreen);
	m_fCurrentDirectionalBlue = INTERP(m_nDirectionalBlue);
	m_fCurrentDirectionalRed /= 255.0f;
	m_fCurrentDirectionalGreen /= 255.0f;
	m_fCurrentDirectionalBlue /= 255.0f;

	m_nCurrentSunCoreRed = INTERP(m_nSunCoreRed);
	m_nCurrentSunCoreGreen = INTERP(m_nSunCoreGreen);
	m_nCurrentSunCoreBlue = INTERP(m_nSunCoreBlue);

	m_nCurrentSunCoronaRed = INTERP(m_nSunCoronaRed);
	m_nCurrentSunCoronaGreen = INTERP(m_nSunCoronaGreen);
	m_nCurrentSunCoronaBlue = INTERP(m_nSunCoronaBlue);

	m_fCurrentSunSize = INTERP(m_fSunSize);
	m_fCurrentSpriteSize = INTERP(m_fSpriteSize);
	m_fCurrentSpriteBrightness = INTERP(m_fSpriteBrightness);
	m_nCurrentShadowStrength = INTERP(m_nShadowStrength);
	m_nCurrentLightShadowStrength = INTERP(m_nLightShadowStrength);
	m_nCurrentTreeShadowStrength = INTERP(m_nTreeShadowStrength);
	m_fCurrentFarClip = INTERP(m_fFarClip);
	m_fCurrentFogStart = INTERP(m_fFogStart);
	m_fCurrentLightsOnGroundBrightness = INTERP(m_fLightsOnGroundBrightness);

	m_nCurrentLowCloudsRed = INTERP(m_nLowCloudsRed);
	m_nCurrentLowCloudsGreen = INTERP(m_nLowCloudsGreen);
	m_nCurrentLowCloudsBlue = INTERP(m_nLowCloudsBlue);

	m_nCurrentFluffyCloudsTopRed = INTERP(m_nFluffyCloudsTopRed);
	m_nCurrentFluffyCloudsTopGreen = INTERP(m_nFluffyCloudsTopGreen);
	m_nCurrentFluffyCloudsTopBlue = INTERP(m_nFluffyCloudsTopBlue);

	m_nCurrentFluffyCloudsBottomRed = INTERP(m_nFluffyCloudsBottomRed);
	m_nCurrentFluffyCloudsBottomGreen = INTERP(m_nFluffyCloudsBottomGreen);
	m_nCurrentFluffyCloudsBottomBlue = INTERP(m_nFluffyCloudsBottomBlue);

	m_fCurrentBlurRed = INTERP(m_fBlurRed);
	m_fCurrentBlurGreen = INTERP(m_fBlurGreen);
	m_fCurrentBlurBlue = INTERP(m_fBlurBlue);
	m_fCurrentBlurAlpha = INTERP(m_fBlurAlpha);

	if(TheCamera.m_BlurType == MBLUR_NONE || TheCamera.m_BlurType == MBLUR_NORMAL)
		TheCamera.SetMotionBlur(m_fCurrentBlurRed, m_fCurrentBlurGreen, m_fCurrentBlurBlue, m_fCurrentBlurAlpha, MBLUR_NORMAL);

	if(m_FogReduction != 0)
		m_fCurrentFarClip = max(m_fCurrentFarClip, m_FogReduction/64.0f * 650.0f);
	m_nCurrentFogColourRed = (m_nCurrentSkyTopRed + 2*m_nCurrentSkyBottomRed) / 3;
	m_nCurrentFogColourGreen = (m_nCurrentSkyTopGreen + 2*m_nCurrentSkyBottomGreen) / 3;
	m_nCurrentFogColourBlue = (m_nCurrentSkyTopBlue + 2*m_nCurrentSkyBottomBlue) / 3;

	m_CurrentStoredValue = (m_CurrentStoredValue+1)&0xF;

	float sunAngle = 2*PI*(CClock::GetMinutes() + CClock::GetHours()*60)/(24*60);
	CVector &sunPos = GetSunPosition();
	sunPos.x = sinf(sunAngle);
	sunPos.y = 1.0f;
	sunPos.z = 0.2f - cosf(sunAngle);
	sunPos.Normalise();

	CShadows::CalcPedShadowValues(sunPos, 
		&m_fShadowFrontX[m_CurrentStoredValue], &m_fShadowFrontY[m_CurrentStoredValue],
		&m_fShadowSideX[m_CurrentStoredValue], &m_fShadowSideY[m_CurrentStoredValue],
		&m_fShadowDisplacementX[m_CurrentStoredValue], &m_fShadowDisplacementY[m_CurrentStoredValue]);

	if(TheCamera.GetForward().z < -0.9f ||
	   !CWeather::bScriptsForceRain && (CCullZones::PlayerNoRain() || CCullZones::CamNoRain() || CCutsceneMgr::IsRunning()))
		m_FogReduction = min(m_FogReduction+1, 64);
	else
		m_FogReduction = max(m_FogReduction-1, 0);
}

STARTPATCHES
	InjectHook(0x4ABAE0, CTimeCycle::Initialise, PATCH_JUMP);
	InjectHook(0x4ABF40, CTimeCycle::Update, PATCH_JUMP);
ENDPATCHES
