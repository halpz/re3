#include "common.h"

#include "main.h"
#include "Clock.h"
#include "Weather.h"
#include "Camera.h"
#include "Shadows.h"
#include "ZoneCull.h"
#include "CutsceneMgr.h"
#include "FileMgr.h"
#include "Timecycle.h"

uint8 CTimeCycle::m_nAmbientRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientRed_Obj[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientGreen_Obj[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientBlue_Obj[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientRed_Bl[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientGreen_Bl[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientBlue_Bl[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientRed_Obj_Bl[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientGreen_Obj_Bl[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nAmbientBlue_Obj_Bl[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nDirectionalRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nDirectionalGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nDirectionalBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSkyTopRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSkyTopGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSkyTopBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSkyBottomRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSkyBottomGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSkyBottomBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSunCoreRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSunCoreGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSunCoreBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSunCoronaRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSunCoronaGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nSunCoronaBlue[NUMHOURS][NUMWEATHERS];
int8 CTimeCycle::m_fSunSize[NUMHOURS][NUMWEATHERS];
int8 CTimeCycle::m_fSpriteSize[NUMHOURS][NUMWEATHERS];
int8 CTimeCycle::m_fSpriteBrightness[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nShadowStrength[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nLightShadowStrength[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nPoleShadowStrength[NUMHOURS][NUMWEATHERS];
int16 CTimeCycle::m_fFogStart[NUMHOURS][NUMWEATHERS];
int16 CTimeCycle::m_fFarClip[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fLightsOnGroundBrightness[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nLowCloudsRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nLowCloudsGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nLowCloudsBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nFluffyCloudsTopRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nFluffyCloudsTopGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nFluffyCloudsTopBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nFluffyCloudsBottomRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nFluffyCloudsBottomGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_nFluffyCloudsBottomBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fBlurRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fBlurGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fBlurBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fWaterRed[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fWaterGreen[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fWaterBlue[NUMHOURS][NUMWEATHERS];
uint8 CTimeCycle::m_fWaterAlpha[NUMHOURS][NUMWEATHERS];


float CTimeCycle::m_fCurrentAmbientRed;
float CTimeCycle::m_fCurrentAmbientGreen;
float CTimeCycle::m_fCurrentAmbientBlue;
float CTimeCycle::m_fCurrentAmbientRed_Obj;
float CTimeCycle::m_fCurrentAmbientGreen_Obj;
float CTimeCycle::m_fCurrentAmbientBlue_Obj;
float CTimeCycle::m_fCurrentAmbientRed_Bl;
float CTimeCycle::m_fCurrentAmbientGreen_Bl;
float CTimeCycle::m_fCurrentAmbientBlue_Bl;
float CTimeCycle::m_fCurrentAmbientRed_Obj_Bl;
float CTimeCycle::m_fCurrentAmbientGreen_Obj_Bl;
float CTimeCycle::m_fCurrentAmbientBlue_Obj_Bl;
float CTimeCycle::m_fCurrentDirectionalRed;
float CTimeCycle::m_fCurrentDirectionalGreen;
float CTimeCycle::m_fCurrentDirectionalBlue;
int32 CTimeCycle::m_nCurrentSkyTopRed;
int32 CTimeCycle::m_nCurrentSkyTopGreen;
int32 CTimeCycle::m_nCurrentSkyTopBlue;
int32 CTimeCycle::m_nCurrentSkyBottomRed;
int32 CTimeCycle::m_nCurrentSkyBottomGreen;
int32 CTimeCycle::m_nCurrentSkyBottomBlue;
int32 CTimeCycle::m_nCurrentSunCoreRed;
int32 CTimeCycle::m_nCurrentSunCoreGreen;
int32 CTimeCycle::m_nCurrentSunCoreBlue;
int32 CTimeCycle::m_nCurrentSunCoronaRed;
int32 CTimeCycle::m_nCurrentSunCoronaGreen;
int32 CTimeCycle::m_nCurrentSunCoronaBlue;
float CTimeCycle::m_fCurrentSunSize;
float CTimeCycle::m_fCurrentSpriteSize;
float CTimeCycle::m_fCurrentSpriteBrightness;
int32 CTimeCycle::m_nCurrentShadowStrength;
int32 CTimeCycle::m_nCurrentLightShadowStrength;
int32 CTimeCycle::m_nCurrentPoleShadowStrength;
float CTimeCycle::m_fCurrentFogStart;
float CTimeCycle::m_fCurrentFarClip;
float CTimeCycle::m_fCurrentLightsOnGroundBrightness;
int32 CTimeCycle::m_nCurrentLowCloudsRed;
int32 CTimeCycle::m_nCurrentLowCloudsGreen;
int32 CTimeCycle::m_nCurrentLowCloudsBlue;
int32 CTimeCycle::m_nCurrentFluffyCloudsTopRed;
int32 CTimeCycle::m_nCurrentFluffyCloudsTopGreen;
int32 CTimeCycle::m_nCurrentFluffyCloudsTopBlue;
int32 CTimeCycle::m_nCurrentFluffyCloudsBottomRed;
int32 CTimeCycle::m_nCurrentFluffyCloudsBottomGreen;
int32 CTimeCycle::m_nCurrentFluffyCloudsBottomBlue;
float CTimeCycle::m_fCurrentBlurRed;
float CTimeCycle::m_fCurrentBlurGreen;
float CTimeCycle::m_fCurrentBlurBlue;
float CTimeCycle::m_fCurrentWaterRed;
float CTimeCycle::m_fCurrentWaterGreen;
float CTimeCycle::m_fCurrentWaterBlue;
float CTimeCycle::m_fCurrentWaterAlpha;
int32 CTimeCycle::m_nCurrentFogColourRed;
int32 CTimeCycle::m_nCurrentFogColourGreen;
int32 CTimeCycle::m_nCurrentFogColourBlue;

int32 CTimeCycle::m_FogReduction;
int32 CTimeCycle::m_bExtraColourOn;
int32 CTimeCycle::m_ExtraColour;
float CTimeCycle::m_ExtraColourInter;

int32 CTimeCycle::m_CurrentStoredValue;
CVector CTimeCycle::m_VectorToSun[16];
float CTimeCycle::m_fShadowFrontX[16];
float CTimeCycle::m_fShadowFrontY[16];
float CTimeCycle::m_fShadowSideX[16];
float CTimeCycle::m_fShadowSideY[16];
float CTimeCycle::m_fShadowDisplacementX[16];
float CTimeCycle::m_fShadowDisplacementY[16];



static float tmp_nAmbientRed[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientBlue[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientRed_Obj[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientGreen_Obj[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientBlue_Obj[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientRed_Bl[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientGreen_Bl[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientBlue_Bl[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientRed_Obj_Bl[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientGreen_Obj_Bl[NUMHOURS][NUMWEATHERS];
static float tmp_nAmbientBlue_Obj_Bl[NUMHOURS][NUMWEATHERS];
static float tmp_nDirectionalRed[NUMHOURS][NUMWEATHERS];
static float tmp_nDirectionalGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nDirectionalBlue[NUMHOURS][NUMWEATHERS];
static float tmp_nSkyTopRed[NUMHOURS][NUMWEATHERS];
static float tmp_nSkyTopGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nSkyTopBlue[NUMHOURS][NUMWEATHERS];
static float tmp_nSkyBottomRed[NUMHOURS][NUMWEATHERS];
static float tmp_nSkyBottomGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nSkyBottomBlue[NUMHOURS][NUMWEATHERS];
static float tmp_nSunCoreRed[NUMHOURS][NUMWEATHERS];
static float tmp_nSunCoreGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nSunCoreBlue[NUMHOURS][NUMWEATHERS];
static float tmp_nSunCoronaRed[NUMHOURS][NUMWEATHERS];
static float tmp_nSunCoronaGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nSunCoronaBlue[NUMHOURS][NUMWEATHERS];
static float tmp_fSunSize[NUMHOURS][NUMWEATHERS];
static float tmp_fSpriteSize[NUMHOURS][NUMWEATHERS];
static float tmp_fSpriteBrightness[NUMHOURS][NUMWEATHERS];
static float tmp_nShadowStrength[NUMHOURS][NUMWEATHERS];
static float tmp_nLightShadowStrength[NUMHOURS][NUMWEATHERS];
static float tmp_nPoleShadowStrength[NUMHOURS][NUMWEATHERS];
static float tmp_fFogStart[NUMHOURS][NUMWEATHERS];
static float tmp_fFarClip[NUMHOURS][NUMWEATHERS];
static float tmp_fLightsOnGroundBrightness[NUMHOURS][NUMWEATHERS];
static float tmp_nLowCloudsRed[NUMHOURS][NUMWEATHERS];
static float tmp_nLowCloudsGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nLowCloudsBlue[NUMHOURS][NUMWEATHERS];
static float tmp_nFluffyCloudsTopRed[NUMHOURS][NUMWEATHERS];
static float tmp_nFluffyCloudsTopGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nFluffyCloudsTopBlue[NUMHOURS][NUMWEATHERS];
static float tmp_nFluffyCloudsBottomRed[NUMHOURS][NUMWEATHERS];
static float tmp_nFluffyCloudsBottomGreen[NUMHOURS][NUMWEATHERS];
static float tmp_nFluffyCloudsBottomBlue[NUMHOURS][NUMWEATHERS];
static float tmp_fBlurRed[NUMHOURS][NUMWEATHERS];
static float tmp_fBlurGreen[NUMHOURS][NUMWEATHERS];
static float tmp_fBlurBlue[NUMHOURS][NUMWEATHERS];
static float tmp_fWaterRed[NUMHOURS][NUMWEATHERS];
static float tmp_fWaterGreen[NUMHOURS][NUMWEATHERS];
static float tmp_fWaterBlue[NUMHOURS][NUMWEATHERS];
static float tmp_fWaterAlpha[NUMHOURS][NUMWEATHERS];

void
CTimeCycle::Initialise(void)
{
	int w, h;
	int li, bi;
	char line[1040];

	int ambR, ambG, ambB;
	int ambobjR, ambobjG, ambobjB;
	int ambblR, ambblG, ambblB;
	int ambobjblR, ambobjblG, ambobjblB;
	int dirR, dirG, dirB;
	int skyTopR, skyTopG, skyTopB;
	int skyBotR, skyBotG, skyBotB;
	int sunCoreR, sunCoreG, sunCoreB;
	int sunCoronaR, sunCoronaG, sunCoronaB;
	float sunSz, sprSz, sprBght;
	int shad, lightShad, poleShad;
	float farClp, fogSt, lightGnd;
	int cloudR, cloudG, cloudB;
	int fluffyTopR, fluffyTopG, fluffyTopB;
	int fluffyBotR, fluffyBotG, fluffyBotB;
	float blurR, blurG, blurB;
	float waterR, waterG, waterB, waterA;

	debug("Intialising CTimeCycle...\n");

	CFileMgr::SetDir("DATA");
	CFileMgr::LoadFile("TIMECYC.DAT", work_buff, sizeof(work_buff), "rb");
	CFileMgr::SetDir("");

	line[0] = '\0';
	bi = 0;
	for(w = 0; w < NUMWEATHERS; w++)
		for(h = 0; h < NUMHOURS; h++){
			li = 0;
			while(work_buff[bi] == '/' || work_buff[bi] == '\n' ||
			      work_buff[bi] == '\0' || work_buff[bi] == '\r'){
				while(work_buff[bi] != '\n' && work_buff[bi] != '\0' && work_buff[bi] != '\r')
					bi++;
				bi++;
			}
			while(work_buff[bi] != '\n'
#ifdef FIX_BUGS
			&& work_buff[bi] != '\0'
#endif
			)
				line[li++] = work_buff[bi++];
			line[li] = '\0';
			bi++;

			sscanf(line, "%d %d %d  %d %d %d  %d %d %d  %d %d %d "
			             "%d %d %d  %d %d %d  %d %d %d "
			             "%d %d %d  %d %d %d  %f %f %f %d %d %d %f %f %f "
			             "%d %d %d  %d %d %d  %d %d %d  %f %f %f  %f %f %f %f",
				&ambR, &ambG, &ambB,
				 &ambobjR, &ambobjG, &ambobjB,
				 &ambblR, &ambblG, &ambblB,
				 &ambobjblR, &ambobjblG, &ambobjblB,
				&dirR, &dirG, &dirB,
				 &skyTopR, &skyTopG, &skyTopB,
				 &skyBotR, &skyBotG, &skyBotB,
				&sunCoreR, &sunCoreG, &sunCoreB,
				 &sunCoronaR, &sunCoronaG, &sunCoronaB,
				 &sunSz, &sprSz, &sprBght,
				 &shad, &lightShad, &poleShad,
				 &farClp, &fogSt, &lightGnd,
				&cloudR, &cloudG, &cloudB,
				 &fluffyTopR, &fluffyTopG, &fluffyTopB,
				 &fluffyBotR, &fluffyBotG, &fluffyBotB,
				 &blurR, &blurG, &blurB,
				 &waterR, &waterG, &waterB, &waterA);

			tmp_nAmbientRed[h][w] = ambR;
			tmp_nAmbientGreen[h][w] = ambG;
			tmp_nAmbientBlue[h][w] = ambB;
			tmp_nAmbientRed_Obj[h][w] = ambobjR;
			tmp_nAmbientGreen_Obj[h][w] = ambobjG;
			tmp_nAmbientBlue_Obj[h][w] = ambobjB;
			tmp_nAmbientRed_Bl[h][w] = ambblR;
			tmp_nAmbientGreen_Bl[h][w] = ambblG;
			tmp_nAmbientBlue_Bl[h][w] = ambblB;
			tmp_nAmbientRed_Obj_Bl[h][w] = ambobjblR;
			tmp_nAmbientGreen_Obj_Bl[h][w] = ambobjblG;
			tmp_nAmbientBlue_Obj_Bl[h][w] = ambobjblB;
			tmp_nDirectionalRed[h][w] = dirR;
			tmp_nDirectionalGreen[h][w] = dirG;
			tmp_nDirectionalBlue[h][w] = dirB;
			tmp_nSkyTopRed[h][w] = skyTopR;
			tmp_nSkyTopGreen[h][w] = skyTopG;
			tmp_nSkyTopBlue[h][w] = skyTopB;
			tmp_nSkyBottomRed[h][w] = skyBotR;
			tmp_nSkyBottomGreen[h][w] = skyBotG;
			tmp_nSkyBottomBlue[h][w] = skyBotB;
			tmp_nSunCoreRed[h][w] = sunCoreR;
			tmp_nSunCoreGreen[h][w] = sunCoreG;
			tmp_nSunCoreBlue[h][w] = sunCoreB;
			tmp_nSunCoronaRed[h][w] = sunCoronaR;
			tmp_nSunCoronaGreen[h][w] = sunCoronaG;
			tmp_nSunCoronaBlue[h][w] = sunCoronaB;
			if(sunSz == -1)
				tmp_fSunSize[h][w] = -1;
			else
				tmp_fSunSize[h][w] = sunSz * 10.0f;
			if(sprSz == -1)
				tmp_fSpriteSize[h][w] = -1;
			else
				tmp_fSpriteSize[h][w] = sprSz * 10.0f;
			if(sprBght == -1)
				tmp_fSpriteBrightness[h][w] = -1;
			else
				tmp_fSpriteBrightness[h][w] = sprBght * 10.0f;
			tmp_nShadowStrength[h][w] = shad;
			tmp_nLightShadowStrength[h][w] = lightShad;
			tmp_nPoleShadowStrength[h][w] = poleShad;
			tmp_fFarClip[h][w] = farClp;
			tmp_fFogStart[h][w] = fogSt;
			if(lightGnd == -1)
				tmp_fLightsOnGroundBrightness[h][w] = -1;
			else
				tmp_fLightsOnGroundBrightness[h][w] = lightGnd * 10.0f;
			tmp_nLowCloudsRed[h][w] = cloudR;
			tmp_nLowCloudsGreen[h][w] = cloudG;
			tmp_nLowCloudsBlue[h][w] = cloudB;
			tmp_nFluffyCloudsTopRed[h][w] = fluffyTopR;
			tmp_nFluffyCloudsTopGreen[h][w] = fluffyTopG;
			tmp_nFluffyCloudsTopBlue[h][w] = fluffyTopB;
			tmp_nFluffyCloudsBottomRed[h][w] = fluffyBotR;
			tmp_nFluffyCloudsBottomGreen[h][w] = fluffyBotG;
			tmp_nFluffyCloudsBottomBlue[h][w] = fluffyBotB;
			tmp_fBlurRed[h][w] = blurR;
			tmp_fBlurGreen[h][w] = blurG;
			tmp_fBlurBlue[h][w] = blurB;
			tmp_fWaterRed[h][w] = waterR;
			tmp_fWaterGreen[h][w] = waterG;
			tmp_fWaterBlue[h][w] = waterB;
			tmp_fWaterAlpha[h][w] = waterA;
		}

	UpdateArrays();

	m_FogReduction = 0;

	debug("CTimeCycle ready\n");
}

template<typename T> void
FillGaps(T (*out)[NUMWEATHERS], float (*in)[NUMWEATHERS])
{
	int w;
	for(w = 0; w < NUMWEATHERS; w++){
		for(int h = 0; h < NUMHOURS; h++)
			out[h][w] = in[h][w];

#define NEXT(h) (((h)+1)%NUMHOURS)
#define PREV(h) (((h)+NUMHOURS-1)%NUMHOURS)
		int hend, h1, h2;
		for(hend = 0; hend < NUMHOURS; hend++)
			if(in[hend][w] != -1.0f)
				goto foundstart;
		return;	// this should never happen
foundstart:
		// Found the start of a block of filled in entries
		for(h1 = NEXT(hend); h1 != hend; h1 = h2){
			// Skip filled in entries
			for(; h1 != hend; h1 = NEXT(h1))
				if(in[h1][w] == -1.0f)
					goto foundfirst;
			break;	// all filled in already
foundfirst:
			// h1 is now the first -1 after n filled in values
			for(h2 = NEXT(h1); ; h2 = NEXT(h2))
				if(in[h2][w] != -1.0f)
					goto foundlast;
			break;
foundlast:
			// h2 is now the first entry after a row of -1s
			h1 = PREV(h1);	// make h1 the first before a row of -1s
			int n = (h2-h1 + NUMHOURS) % NUMHOURS;
			if(n == 0) n = NUMHOURS;	// can't happen
			float step = (in[h2][w] - in[h1][w])/n;

			for(int i = 1; i < n; i++){
				float f = (float)i/n;
				out[(h1+i)%NUMHOURS][w] = in[h2][w]*f + in[h1][w]*(1.0f-f);
			}
		}
	}
}

void
CTimeCycle::UpdateArrays(void)
{
	FillGaps(m_nAmbientRed, tmp_nAmbientRed);
	FillGaps(m_nAmbientGreen, tmp_nAmbientGreen);
	FillGaps(m_nAmbientBlue, tmp_nAmbientBlue);
	FillGaps(m_nAmbientRed_Obj, tmp_nAmbientRed_Obj);
	FillGaps(m_nAmbientGreen_Obj, tmp_nAmbientGreen_Obj);
	FillGaps(m_nAmbientBlue_Obj, tmp_nAmbientBlue_Obj);
	FillGaps(m_nAmbientRed_Bl, tmp_nAmbientRed_Bl);
	FillGaps(m_nAmbientGreen_Bl, tmp_nAmbientGreen_Bl);
	FillGaps(m_nAmbientBlue_Bl, tmp_nAmbientBlue_Bl);
	FillGaps(m_nAmbientRed_Obj_Bl, tmp_nAmbientRed_Obj_Bl);
	FillGaps(m_nAmbientGreen_Obj_Bl, tmp_nAmbientGreen_Obj_Bl);
	FillGaps(m_nAmbientBlue_Obj_Bl, tmp_nAmbientBlue_Obj_Bl);
	FillGaps(m_nDirectionalRed, tmp_nDirectionalRed);
	FillGaps(m_nDirectionalGreen, tmp_nDirectionalGreen);
	FillGaps(m_nDirectionalBlue, tmp_nDirectionalBlue);
	FillGaps(m_nSkyTopRed, tmp_nSkyTopRed);
	FillGaps(m_nSkyTopGreen, tmp_nSkyTopGreen);
	FillGaps(m_nSkyTopBlue, tmp_nSkyTopBlue);
	FillGaps(m_nSkyBottomRed, tmp_nSkyBottomRed);
	FillGaps(m_nSkyBottomGreen, tmp_nSkyBottomGreen);
	FillGaps(m_nSkyBottomBlue, tmp_nSkyBottomBlue);
	FillGaps(m_nSunCoreRed, tmp_nSunCoreRed);
	FillGaps(m_nSunCoreGreen, tmp_nSunCoreGreen);
	FillGaps(m_nSunCoreBlue, tmp_nSunCoreBlue);
	FillGaps(m_nSunCoronaRed, tmp_nSunCoronaRed);
	FillGaps(m_nSunCoronaGreen, tmp_nSunCoronaGreen);
	FillGaps(m_nSunCoronaBlue, tmp_nSunCoronaBlue);
	FillGaps(m_fSunSize, tmp_fSunSize);
	FillGaps(m_fSpriteSize, tmp_fSpriteSize);
	FillGaps(m_fSpriteBrightness, tmp_fSpriteBrightness);
	FillGaps(m_nShadowStrength, tmp_nShadowStrength);
	FillGaps(m_nLightShadowStrength, tmp_nLightShadowStrength);
	FillGaps(m_nPoleShadowStrength, tmp_nPoleShadowStrength);
	FillGaps(m_fFogStart, tmp_fFogStart);
	FillGaps(m_fFarClip, tmp_fFarClip);
	FillGaps(m_fLightsOnGroundBrightness, tmp_fLightsOnGroundBrightness);
	FillGaps(m_nLowCloudsRed, tmp_nLowCloudsRed);
	FillGaps(m_nLowCloudsGreen, tmp_nLowCloudsGreen);
	FillGaps(m_nLowCloudsBlue, tmp_nLowCloudsBlue);
	FillGaps(m_nFluffyCloudsTopRed, tmp_nFluffyCloudsTopRed);
	FillGaps(m_nFluffyCloudsTopGreen, tmp_nFluffyCloudsTopGreen);
	FillGaps(m_nFluffyCloudsTopBlue, tmp_nFluffyCloudsTopBlue);
	FillGaps(m_nFluffyCloudsBottomRed, tmp_nFluffyCloudsBottomRed);
	FillGaps(m_nFluffyCloudsBottomGreen, tmp_nFluffyCloudsBottomGreen);
	FillGaps(m_nFluffyCloudsBottomBlue, tmp_nFluffyCloudsBottomBlue);
	FillGaps(m_fBlurRed, tmp_fBlurRed);
	FillGaps(m_fBlurGreen, tmp_fBlurGreen);
	FillGaps(m_fBlurBlue, tmp_fBlurBlue);
	FillGaps(m_fWaterRed, tmp_fWaterRed);
	FillGaps(m_fWaterGreen, tmp_fWaterGreen);
	FillGaps(m_fWaterBlue, tmp_fWaterBlue);
	FillGaps(m_fWaterAlpha, tmp_fWaterAlpha);
}

static float interp_c0, interp_c1, interp_c2, interp_c3;

float CTimeCycle::Interpolate(int8 *a, int8 *b)
{
	return a[CWeather::OldWeatherType] * interp_c0 +
		b[CWeather::OldWeatherType] * interp_c1 +
		a[CWeather::NewWeatherType] * interp_c2 +
		b[CWeather::NewWeatherType] * interp_c3;
}

float CTimeCycle::Interpolate(uint8 *a, uint8 *b)
{
	return a[CWeather::OldWeatherType] * interp_c0 +
		b[CWeather::OldWeatherType] * interp_c1 +
		a[CWeather::NewWeatherType] * interp_c2 +
		b[CWeather::NewWeatherType] * interp_c3;
}

float CTimeCycle::Interpolate(int16 *a, int16 *b)
{
	return a[CWeather::OldWeatherType] * interp_c0 +
		b[CWeather::OldWeatherType] * interp_c1 +
		a[CWeather::NewWeatherType] * interp_c2 +
		b[CWeather::NewWeatherType] * interp_c3;
}

void
CTimeCycle::StartExtraColour(int32 c, bool fade)
{
	m_bExtraColourOn = true;
	m_ExtraColour = c;
	if(fade)
		m_ExtraColourInter = 0.0f;
	else
		m_ExtraColourInter = 1.0f;
}

void
CTimeCycle::StopExtraColour(bool fade)
{
	m_bExtraColourOn = false;
	if(!fade)
		m_ExtraColourInter = 0.0f;
}

void
CTimeCycle::Update(void)
{
	int h1 = CClock::GetHours();
	int h2 = (h1+1)%24;
	int w1 = CWeather::OldWeatherType;
	int w2 = CWeather::NewWeatherType;
	float timeInterp = (CClock::GetMinutes() + CClock::GetSeconds()/60.0f)/60.0f;
	// coefficients for a bilinear interpolation
	interp_c0 = (1.0f-timeInterp) * (1.0f-CWeather::InterpolationValue);
	interp_c1 = timeInterp * (1.0f-CWeather::InterpolationValue);
	interp_c2 = (1.0f-timeInterp) * CWeather::InterpolationValue;
	interp_c3 = timeInterp * CWeather::InterpolationValue;

#define INTERP(v) Interpolate(v[h1], v[h2])

	m_nCurrentSkyTopRed = INTERP(m_nSkyTopRed);
	m_nCurrentSkyTopGreen = INTERP(m_nSkyTopGreen);
	m_nCurrentSkyTopBlue = INTERP(m_nSkyTopBlue);

	m_nCurrentSkyBottomRed = INTERP(m_nSkyBottomRed);
	m_nCurrentSkyBottomGreen = INTERP(m_nSkyBottomGreen);
	m_nCurrentSkyBottomBlue = INTERP(m_nSkyBottomBlue);

	m_fCurrentAmbientRed = INTERP(m_nAmbientRed);
	m_fCurrentAmbientGreen = INTERP(m_nAmbientGreen);
	m_fCurrentAmbientBlue = INTERP(m_nAmbientBlue);

	m_fCurrentAmbientRed_Obj = INTERP(m_nAmbientRed_Obj);
	m_fCurrentAmbientGreen_Obj = INTERP(m_nAmbientGreen_Obj);
	m_fCurrentAmbientBlue_Obj = INTERP(m_nAmbientBlue_Obj);

	m_fCurrentAmbientRed_Bl = INTERP(m_nAmbientRed_Bl);
	m_fCurrentAmbientGreen_Bl = INTERP(m_nAmbientGreen_Bl);
	m_fCurrentAmbientBlue_Bl = INTERP(m_nAmbientBlue_Bl);

	m_fCurrentAmbientRed_Obj_Bl = INTERP(m_nAmbientRed_Obj_Bl);
	m_fCurrentAmbientGreen_Obj_Bl = INTERP(m_nAmbientGreen_Obj_Bl);
	m_fCurrentAmbientBlue_Obj_Bl = INTERP(m_nAmbientBlue_Obj_Bl);

	m_fCurrentDirectionalRed = INTERP(m_nDirectionalRed);
	m_fCurrentDirectionalGreen = INTERP(m_nDirectionalGreen);
	m_fCurrentDirectionalBlue = INTERP(m_nDirectionalBlue);

	m_nCurrentSunCoreRed = INTERP(m_nSunCoreRed);
	m_nCurrentSunCoreGreen = INTERP(m_nSunCoreGreen);
	m_nCurrentSunCoreBlue = INTERP(m_nSunCoreBlue);

	m_nCurrentSunCoronaRed = INTERP(m_nSunCoronaRed);
	m_nCurrentSunCoronaGreen = INTERP(m_nSunCoronaGreen);
	m_nCurrentSunCoronaBlue = INTERP(m_nSunCoronaBlue);

	m_fCurrentSunSize = INTERP(m_fSunSize)/10.0f;
	m_fCurrentSpriteSize = INTERP(m_fSpriteSize)/10.0f;
	m_fCurrentSpriteBrightness = INTERP(m_fSpriteBrightness)/10.0f;
	m_nCurrentShadowStrength = INTERP(m_nShadowStrength);
	m_nCurrentLightShadowStrength = INTERP(m_nLightShadowStrength);
	m_nCurrentPoleShadowStrength = INTERP(m_nPoleShadowStrength);
	m_fCurrentFarClip = INTERP(m_fFarClip);
	m_fCurrentFogStart = INTERP(m_fFogStart);
	m_fCurrentLightsOnGroundBrightness = INTERP(m_fLightsOnGroundBrightness)/10.0f;

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

	m_fCurrentWaterRed = INTERP(m_fWaterRed);
	m_fCurrentWaterGreen = INTERP(m_fWaterGreen);
	m_fCurrentWaterBlue = INTERP(m_fWaterBlue);
	m_fCurrentWaterAlpha = INTERP(m_fWaterAlpha);
#undef INTERP

	if(m_FogReduction != 0)
		m_fCurrentFarClip = Max(m_fCurrentFarClip, m_FogReduction/64.0f * 650.0f);

	m_CurrentStoredValue = (m_CurrentStoredValue+1)&0xF;

	float sunAngle = 2*PI*(CClock::GetSeconds()/60.0f + CClock::GetMinutes() + CClock::GetHours()*60)/(24*60);
	CVector &sunPos = GetSunDirection();
	sunPos.x = Sin(sunAngle);
	sunPos.y = 1.0f;
	sunPos.z = 0.2f - Cos(sunAngle);
	sunPos.Normalise();

	if(m_bExtraColourOn)
		m_ExtraColourInter = Min(1.0f, m_ExtraColourInter + CTimer::GetTimeStep()/120.0f);
	else
		m_ExtraColourInter = Max(-.0f, m_ExtraColourInter - CTimer::GetTimeStep()/120.0f);
	if(m_ExtraColourInter > 0.0f){
#define INTERP(extra,cur) (m_ExtraColourInter*extra[m_ExtraColour][WEATHER_EXTRACOLOURS] + (1.0f-m_ExtraColourInter)*cur)
#define INTERPscl(extra,scl,cur) (m_ExtraColourInter*extra[m_ExtraColour][WEATHER_EXTRACOLOURS]/scl + (1.0f-m_ExtraColourInter)*cur)
		if(m_nSkyTopRed[m_ExtraColour][WEATHER_EXTRACOLOURS] != 0 ||
		   m_nSkyTopGreen[m_ExtraColour][WEATHER_EXTRACOLOURS] != 0 ||
		   m_nSkyTopBlue[m_ExtraColour][WEATHER_EXTRACOLOURS] != 0){
			m_nCurrentSkyTopRed = INTERP(m_nSkyTopRed,m_nCurrentSkyTopRed);
			m_nCurrentSkyTopGreen = INTERP(m_nSkyTopGreen,m_nCurrentSkyTopGreen);
			m_nCurrentSkyTopBlue = INTERP(m_nSkyTopBlue,m_nCurrentSkyTopBlue);

			m_nCurrentSkyBottomRed = INTERP(m_nSkyBottomRed,m_nCurrentSkyBottomRed);
			m_nCurrentSkyBottomGreen = INTERP(m_nSkyBottomGreen,m_nCurrentSkyBottomGreen);
			m_nCurrentSkyBottomBlue = INTERP(m_nSkyBottomBlue,m_nCurrentSkyBottomBlue);

			m_nCurrentSunCoreRed = INTERP(m_nSunCoreRed,m_nCurrentSunCoreRed);
			m_nCurrentSunCoreGreen = INTERP(m_nSunCoreGreen,m_nCurrentSunCoreGreen);
			m_nCurrentSunCoreBlue = INTERP(m_nSunCoreBlue,m_nCurrentSunCoreBlue);

			m_nCurrentSunCoronaRed = INTERP(m_nSunCoronaRed,m_nCurrentSunCoronaRed);
			m_nCurrentSunCoronaGreen = INTERP(m_nSunCoronaGreen,m_nCurrentSunCoronaGreen);
			m_nCurrentSunCoronaBlue = INTERP(m_nSunCoronaBlue,m_nCurrentSunCoronaBlue);

			m_fCurrentSunSize = INTERPscl(m_fSunSize,10.0f,m_fCurrentSunSize);

			m_nCurrentLowCloudsRed = INTERP(m_nLowCloudsRed,m_nCurrentLowCloudsRed);
			m_nCurrentLowCloudsGreen = INTERP(m_nLowCloudsGreen,m_nCurrentLowCloudsGreen);
			m_nCurrentLowCloudsBlue = INTERP(m_nLowCloudsBlue,m_nCurrentLowCloudsBlue);

			m_nCurrentFluffyCloudsTopRed = INTERP(m_nFluffyCloudsTopRed,m_nCurrentFluffyCloudsTopRed);
			m_nCurrentFluffyCloudsTopGreen = INTERP(m_nFluffyCloudsTopGreen,m_nCurrentFluffyCloudsTopGreen);
			m_nCurrentFluffyCloudsTopBlue = INTERP(m_nFluffyCloudsTopBlue,m_nCurrentFluffyCloudsTopBlue);

			m_nCurrentFluffyCloudsBottomRed = INTERP(m_nFluffyCloudsBottomRed,m_nCurrentFluffyCloudsBottomRed);
			m_nCurrentFluffyCloudsBottomGreen = INTERP(m_nFluffyCloudsBottomGreen,m_nCurrentFluffyCloudsBottomGreen);
			m_nCurrentFluffyCloudsBottomBlue = INTERP(m_nFluffyCloudsBottomBlue,m_nCurrentFluffyCloudsBottomBlue);

			m_fCurrentWaterRed = INTERP(m_fWaterRed,m_fCurrentWaterRed);
			m_fCurrentWaterGreen = INTERP(m_fWaterGreen,m_fCurrentWaterGreen);
			m_fCurrentWaterBlue = INTERP(m_fWaterBlue,m_fCurrentWaterBlue);
			m_fCurrentWaterAlpha = INTERP(m_fWaterAlpha,m_fCurrentWaterAlpha);
		}

		m_fCurrentAmbientRed = INTERP(m_nAmbientRed,m_fCurrentAmbientRed);
		m_fCurrentAmbientGreen = INTERP(m_nAmbientGreen,m_fCurrentAmbientGreen);
		m_fCurrentAmbientBlue = INTERP(m_nAmbientBlue,m_fCurrentAmbientBlue);

		m_fCurrentAmbientRed_Obj = INTERP(m_nAmbientRed_Obj,m_fCurrentAmbientRed_Obj);
		m_fCurrentAmbientGreen_Obj = INTERP(m_nAmbientGreen_Obj,m_fCurrentAmbientGreen_Obj);
		m_fCurrentAmbientBlue_Obj = INTERP(m_nAmbientBlue_Obj,m_fCurrentAmbientBlue_Obj);

		m_fCurrentAmbientRed_Bl = INTERP(m_nAmbientRed_Bl,m_fCurrentAmbientRed_Bl);
		m_fCurrentAmbientGreen_Bl = INTERP(m_nAmbientGreen_Bl,m_fCurrentAmbientGreen_Bl);
		m_fCurrentAmbientBlue_Bl = INTERP(m_nAmbientBlue_Bl,m_fCurrentAmbientBlue_Bl);

		m_fCurrentAmbientRed_Obj_Bl = INTERP(m_nAmbientRed_Obj_Bl,m_fCurrentAmbientRed_Obj_Bl);
		m_fCurrentAmbientGreen_Obj_Bl = INTERP(m_nAmbientGreen_Obj_Bl,m_fCurrentAmbientGreen_Obj_Bl);
		m_fCurrentAmbientBlue_Obj_Bl = INTERP(m_nAmbientBlue_Obj_Bl,m_fCurrentAmbientBlue_Obj_Bl);

		m_fCurrentDirectionalRed = INTERP(m_nDirectionalRed,m_fCurrentDirectionalRed);
		m_fCurrentDirectionalGreen = INTERP(m_nDirectionalGreen,m_fCurrentDirectionalGreen);
		m_fCurrentDirectionalBlue = INTERP(m_nDirectionalBlue,m_fCurrentDirectionalBlue);

		m_fCurrentSpriteSize = INTERPscl(m_fSpriteSize,10.0f,m_fCurrentSpriteSize);
		m_fCurrentSpriteBrightness = INTERPscl(m_fSpriteBrightness,10.0f,m_fCurrentSpriteBrightness);
		m_nCurrentShadowStrength = INTERP(m_nShadowStrength,m_nCurrentShadowStrength);
		m_nCurrentLightShadowStrength = INTERP(m_nLightShadowStrength,m_nCurrentLightShadowStrength);
		m_nCurrentPoleShadowStrength = INTERP(m_nPoleShadowStrength,m_nCurrentPoleShadowStrength);
		m_fCurrentFarClip = INTERP(m_fFarClip,m_fCurrentFarClip);
		m_fCurrentFogStart = INTERP(m_fFogStart,m_fCurrentFogStart);
		m_fCurrentLightsOnGroundBrightness = INTERPscl(m_fLightsOnGroundBrightness,10.0f,m_fCurrentLightsOnGroundBrightness);

		m_fCurrentBlurRed = INTERP(m_fBlurRed,m_fCurrentBlurRed);
		m_fCurrentBlurGreen = INTERP(m_fBlurGreen,m_fCurrentBlurGreen);
		m_fCurrentBlurBlue = INTERP(m_fBlurBlue,m_fCurrentBlurBlue);

#undef INTERP
#undef INTERPscl
	}

	if(TheCamera.m_BlurType == MOTION_BLUR_NONE || TheCamera.m_BlurType == MOTION_BLUR_LIGHT_SCENE)
		TheCamera.SetMotionBlur(m_fCurrentBlurRed, m_fCurrentBlurGreen, m_fCurrentBlurBlue, 5, MOTION_BLUR_LIGHT_SCENE);

	m_nCurrentFogColourRed = (m_nCurrentSkyTopRed + 2*m_nCurrentSkyBottomRed) / 3;
	m_nCurrentFogColourGreen = (m_nCurrentSkyTopGreen + 2*m_nCurrentSkyBottomGreen) / 3;
	m_nCurrentFogColourBlue = (m_nCurrentSkyTopBlue + 2*m_nCurrentSkyBottomBlue) / 3;

	m_fCurrentAmbientRed /= 255.0f;
	m_fCurrentAmbientGreen /= 255.0f;
	m_fCurrentAmbientBlue /= 255.0f;
	m_fCurrentAmbientRed_Obj /= 255.0f;
	m_fCurrentAmbientGreen_Obj /= 255.0f;
	m_fCurrentAmbientBlue_Obj /= 255.0f;
	m_fCurrentAmbientRed_Bl /= 255.0f;
	m_fCurrentAmbientGreen_Bl /= 255.0f;
	m_fCurrentAmbientBlue_Bl /= 255.0f;
	m_fCurrentAmbientRed_Obj_Bl /= 255.0f;
	m_fCurrentAmbientGreen_Obj_Bl /= 255.0f;
	m_fCurrentAmbientBlue_Obj_Bl /= 255.0f;
	m_fCurrentDirectionalRed /= 255.0f;
	m_fCurrentDirectionalGreen /= 255.0f;
	m_fCurrentDirectionalBlue /= 255.0f;

	CShadows::CalcPedShadowValues(sunPos, 
		&m_fShadowFrontX[m_CurrentStoredValue], &m_fShadowFrontY[m_CurrentStoredValue],
		&m_fShadowSideX[m_CurrentStoredValue], &m_fShadowSideY[m_CurrentStoredValue],
		&m_fShadowDisplacementX[m_CurrentStoredValue], &m_fShadowDisplacementY[m_CurrentStoredValue]);

	if(TheCamera.GetForward().z < -0.9f ||
	   !CWeather::bScriptsForceRain && (CCullZones::PlayerNoRain() || CCullZones::CamNoRain() || CCutsceneMgr::IsRunning()))
		m_FogReduction = Min(m_FogReduction+1, 64);
	else
		m_FogReduction = Max(m_FogReduction-1, 0);
}
