#pragma once

class CEntity;

enum {
	PED_LIGHTS_WALK,
	PED_LIGHTS_WALK_BLINK,
	PED_LIGHTS_DONT_WALK,
};

class CTrafficLights
{
public:
	static void DisplayActualLight(CEntity *ent);
	static uint8 LightForPeds(void);
};
