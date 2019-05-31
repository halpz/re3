#pragma once

class CPointLights
{
	static int16 &NumLights;
public:
	static void InitPerFrame(void);
	static void RenderFogEffect(void);
};
