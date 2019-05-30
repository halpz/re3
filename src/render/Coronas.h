#pragma once

extern RwTexture **gpCoronaTexture;	//[9]

class CCoronas
{
public:
	static float &LightsMult;
	static float &SunScreenY;
	static float &SunScreenX;
	static bool &bSmallMoon;
	static bool &SunBlockedByClouds;

	static void Render(void);
	static void RenderReflections(void);
};
