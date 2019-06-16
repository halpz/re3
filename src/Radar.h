#pragma once
#include "Sprite2d.h"

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
	static float &m_RadarRange;
	static CVector2D &vec2DRadarOrigin;

public:
	static void ClearBlipForEntity(eBlipType type, int32 id);
	static void Draw3dMarkers();
	static void DrawMap();
	static void TransformRadarPointToScreenSpace(CVector2D * out, CVector2D * in);
	static void DrawBlips();
	static void DrawRadarMap();
};
