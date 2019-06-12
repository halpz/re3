#pragma once

class CTimeCycle
{
	static int   (*m_nAmbientRed)[NUMWEATHERS];
	static int   (*m_nAmbientGreen)[NUMWEATHERS];
	static int   (*m_nAmbientBlue)[NUMWEATHERS];
	static int   (*m_nDirectionalRed)[NUMWEATHERS];
	static int   (*m_nDirectionalGreen)[NUMWEATHERS];
	static int   (*m_nDirectionalBlue)[NUMWEATHERS];
	static int   (*m_nSkyTopRed)[NUMWEATHERS];
	static int   (*m_nSkyTopGreen)[NUMWEATHERS];
	static int   (*m_nSkyTopBlue)[NUMWEATHERS];
	static int   (*m_nSkyBottomRed)[NUMWEATHERS];
	static int   (*m_nSkyBottomGreen)[NUMWEATHERS];
	static int   (*m_nSkyBottomBlue)[NUMWEATHERS];
	static int   (*m_nSunCoreRed)[NUMWEATHERS];
	static int   (*m_nSunCoreGreen)[NUMWEATHERS];
	static int   (*m_nSunCoreBlue)[NUMWEATHERS];
	static int   (*m_nSunCoronaRed)[NUMWEATHERS];
	static int   (*m_nSunCoronaGreen)[NUMWEATHERS];
	static int   (*m_nSunCoronaBlue)[NUMWEATHERS];
	static float (*m_fSunSize)[NUMWEATHERS];
	static float (*m_fSpriteSize)[NUMWEATHERS];
	static float (*m_fSpriteBrightness)[NUMWEATHERS];
	static short (*m_nShadowStrength)[NUMWEATHERS];
	static short (*m_nLightShadowStrength)[NUMWEATHERS];
	static short (*m_nTreeShadowStrength)[NUMWEATHERS];
	static float (*m_fFogStart)[NUMWEATHERS];
	static float (*m_fFarClip)[NUMWEATHERS];
	static float (*m_fLightsOnGroundBrightness)[NUMWEATHERS];
	static int   (*m_nLowCloudsRed)[NUMWEATHERS];
	static int   (*m_nLowCloudsGreen)[NUMWEATHERS];
	static int   (*m_nLowCloudsBlue)[NUMWEATHERS];
	static int   (*m_nFluffyCloudsTopRed)[NUMWEATHERS];
	static int   (*m_nFluffyCloudsTopGreen)[NUMWEATHERS];
	static int   (*m_nFluffyCloudsTopBlue)[NUMWEATHERS];
	static int   (*m_nFluffyCloudsBottomRed)[NUMWEATHERS];
	static int   (*m_nFluffyCloudsBottomGreen)[NUMWEATHERS];
	static int   (*m_nFluffyCloudsBottomBlue)[NUMWEATHERS];
	static float (*m_fBlurRed)[NUMWEATHERS];
	static float (*m_fBlurGreen)[NUMWEATHERS];
	static float (*m_fBlurBlue)[NUMWEATHERS];
	static float (*m_fBlurAlpha)[NUMWEATHERS];

	static float &m_fCurrentAmbientRed;
	static float &m_fCurrentAmbientGreen;
	static float &m_fCurrentAmbientBlue;
	static float &m_fCurrentDirectionalRed;
	static float &m_fCurrentDirectionalGreen;
	static float &m_fCurrentDirectionalBlue;
	static int   &m_nCurrentSkyTopRed;
	static int   &m_nCurrentSkyTopGreen;
	static int   &m_nCurrentSkyTopBlue;
	static int   &m_nCurrentSkyBottomRed;
	static int   &m_nCurrentSkyBottomGreen;
	static int   &m_nCurrentSkyBottomBlue;
	static int   &m_nCurrentSunCoreRed;
	static int   &m_nCurrentSunCoreGreen;
	static int   &m_nCurrentSunCoreBlue;
	static int   &m_nCurrentSunCoronaRed;
	static int   &m_nCurrentSunCoronaGreen;
	static int   &m_nCurrentSunCoronaBlue;
	static float &m_fCurrentSunSize;
	static float &m_fCurrentSpriteSize;
	static float &m_fCurrentSpriteBrightness;
	static int   &m_nCurrentShadowStrength;
	static int   &m_nCurrentLightShadowStrength;
	static int   &m_nCurrentTreeShadowStrength;
	static float &m_fCurrentFogStart;
	static float &m_fCurrentFarClip;
	static float &m_fCurrentLightsOnGroundBrightness;
	static int   &m_nCurrentLowCloudsRed;
	static int   &m_nCurrentLowCloudsGreen;
	static int   &m_nCurrentLowCloudsBlue;
	static int   &m_nCurrentFluffyCloudsTopRed;
	static int   &m_nCurrentFluffyCloudsTopGreen;
	static int   &m_nCurrentFluffyCloudsTopBlue;
	static int   &m_nCurrentFluffyCloudsBottomRed;
	static int   &m_nCurrentFluffyCloudsBottomGreen;
	static int   &m_nCurrentFluffyCloudsBottomBlue;
	static float &m_fCurrentBlurRed;
	static float &m_fCurrentBlurGreen;
	static float &m_fCurrentBlurBlue;
	static float &m_fCurrentBlurAlpha;
	static int   &m_nCurrentFogColourRed;
	static int   &m_nCurrentFogColourGreen;
	static int   &m_nCurrentFogColourBlue;

	static int   &m_FogReduction;

public:
	static int   &m_CurrentStoredValue;
	static CVector *m_VectorToSun;	// [16]
	static float *m_fShadowFrontX;	// [16]
	static float *m_fShadowFrontY;	// [16]
	static float *m_fShadowSideX;	// [16]
	static float *m_fShadowSideY;	// [16]
	static float *m_fShadowDisplacementX;	// [16]
	static float *m_fShadowDisplacementY;	// [16]

	static float GetAmbientRed(void) { return m_fCurrentAmbientRed; }
	static float GetAmbientGreen(void) { return m_fCurrentAmbientGreen; }
	static float GetAmbientBlue(void) { return m_fCurrentAmbientBlue; }
	static float GetDirectionalRed(void) { return m_fCurrentDirectionalRed; }
	static float GetDirectionalGreen(void) { return m_fCurrentDirectionalGreen; }
	static float GetDirectionalBlue(void) { return m_fCurrentDirectionalBlue; }
	static int GetSkyTopRed(void) { return m_nCurrentSkyTopRed; }
	static int GetSkyTopGreen(void) { return m_nCurrentSkyTopGreen; }
	static int GetSkyTopBlue(void) { return m_nCurrentSkyTopBlue; }
	static int GetSkyBottomRed(void) { return m_nCurrentSkyBottomRed; }
	static int GetSkyBottomGreen(void) { return m_nCurrentSkyBottomGreen; }
	static int GetSkyBottomBlue(void) { return m_nCurrentSkyBottomBlue; }
	static int GetSunCoreRed(void) { return m_nCurrentSunCoreRed; }
	static int GetSunCoreGreen(void) { return m_nCurrentSunCoreGreen; }
	static int GetSunCoreBlue(void) { return m_nCurrentSunCoreBlue; }
	static int GetSunCoronaRed(void) { return m_nCurrentSunCoronaRed; }
	static int GetSunCoronaGreen(void) { return m_nCurrentSunCoronaGreen; }
	static int GetSunCoronaBlue(void) { return m_nCurrentSunCoronaBlue; }
	static float GetSunSize(void) { return m_fCurrentSunSize; }
	static float GetFarClip(void) { return m_fCurrentFarClip; }
	static float GetFogStart(void) { return m_fCurrentFogStart; }

	static int GetLowCloudsRed(void) { return m_nCurrentLowCloudsRed; }
	static int GetLowCloudsGreen(void) { return m_nCurrentLowCloudsGreen; }
	static int GetLowCloudsBlue(void) { return m_nCurrentLowCloudsBlue; }
	static int GetFluffyCloudsTopRed(void) { return m_nCurrentFluffyCloudsTopRed; }
	static int GetFluffyCloudsTopGreen(void) { return m_nCurrentFluffyCloudsTopGreen; }
	static int GetFluffyCloudsTopBlue(void) { return m_nCurrentFluffyCloudsTopBlue; }
	static int GetFluffyCloudsBottomRed(void) { return m_nCurrentFluffyCloudsBottomRed; }
	static int GetFluffyCloudsBottomGreen(void) { return m_nCurrentFluffyCloudsBottomGreen; }
	static int GetFluffyCloudsBottomBlue(void) { return m_nCurrentFluffyCloudsBottomBlue; }
	static int GetFogRed(void) { return m_nCurrentFogColourRed; }
	static int GetFogGreen(void) { return m_nCurrentFogColourGreen; }
	static int GetFogBlue(void) { return m_nCurrentFogColourBlue; }

	static void Initialise(void);
	static void Update(void);
	static CVector &GetSunPosition(void) { return m_VectorToSun[m_CurrentStoredValue]; }
};
