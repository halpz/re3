#pragma once

enum eBlipType
{
	BLIP_NONE,
	BLIP_CAR,
	BLIP_CHAR,
	BLIP_OBJECT,
	BLIP_COORD,
	BLIP_CONTACT_POINT
};

class CRadar
{
public:
	static void ClearBlipForEntity(eBlipType type, int32 id);
};
