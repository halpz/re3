#pragma once

class CRegisteredPointLight
{
public:
	CVector coors;
	CVector dir;
	float radius;
	float red;
	float green;
	float blue;
	int8 type;
	int8 fogType;
	bool castExtraShadows;
};
static_assert(sizeof(CRegisteredPointLight) == 0x2C, "CRegisteredPointLight: error");

class CPointLights
{
	// Probably have to make this public for shadows later
	static int16 &NumLights;
	static CRegisteredPointLight *aLights;	//[NUMPOINTLIGHTS]
public:
	enum {
		LIGHT_POINT,
		LIGHT_DIRECTIONAL,
		LIGHT_DARKEN,	// no effects at all
		// these have only fog, otherwise no difference?
		// only used by CEntity::ProcessLightsForEntity it seems
		// and there used together with fog type
		LIGHT_FOGONLY_ALWAYS,
		LIGHT_FOGONLY,
	};
	enum {
		FOG_NONE,
		FOG_NORMAL,	// taken from Foggyness
		FOG_ALWAYS
	};

	static void InitPerFrame(void);
	static void AddLight(uint8 type, CVector coors, CVector dir, float radius, float red, float green, float blue, uint8 fogType, bool castExtraShadows);
	static float GenerateLightsAffectingObject(CVector *objCoors);
	static void RemoveLightsAffectingObject(void);
	static void RenderFogEffect(void);
};
