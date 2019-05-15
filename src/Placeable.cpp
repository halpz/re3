#include "common.h"
#include "Placeable.h"
#include "patcher.h"

CPlaceable::CPlaceable(void)
{
	m_matrix.SetScale(1.0f);
}

CPlaceable::~CPlaceable(void) { }

void
CPlaceable::SetHeading(float angle)
{
	CVector pos = GetPosition();
	m_matrix.SetRotateZ(angle);
	GetPosition() += pos;
}

bool
CPlaceable::IsWithinArea(float x1, float y1, float x2, float y2)
{
	float x, xmin, xmax;
	float y, ymin, ymax;
	xmin = x1;
	xmax = x2;
	ymin = y1;
	ymax = y2;
	if(x2 > x1){
		xmin = x2;
		xmax = x1;
	}
	if(y2 > y1){
		ymin = y2;
		ymax = y1;
	}
	x = GetPosition().x;
	y = GetPosition().y;
	return xmin <= x && x <= xmax &&
	       ymin <= y && y <= ymax;
}

bool
CPlaceable::IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float x, xmin, xmax;
	float y, ymin, ymax;
	float z, zmin, zmax;
	xmin = x1;
	xmax = x2;
	ymin = y1;
	ymax = y2;
	zmin = z1;
	zmax = z2;
	if(x2 > x1){
		xmin = x2;
		xmax = x1;
	}
	if(y2 > y1){
		ymin = y2;
		ymax = y1;
	}
	if(z2 > z1){
		zmin = z2;
		zmax = z1;
	}
	x = GetPosition().x;
	y = GetPosition().y;
	z = GetPosition().z;
	return xmin <= x && x <= xmax &&
	       ymin <= y && y <= ymax &&
	       zmin <= z && z <= zmax;
}

STARTPATCHES
	InjectHook(0x49F9A0, &CPlaceable::ctor, PATCH_JUMP);
	InjectHook(0x49F9E0, &CPlaceable::dtor, PATCH_JUMP);
	InjectHook(0x49FA00, &CPlaceable::SetHeading, PATCH_JUMP);
	InjectHook(0x49FA50, (bool (CPlaceable::*)(float, float, float, float))&CPlaceable::IsWithinArea, PATCH_JUMP);
	InjectHook(0x49FAF0, (bool (CPlaceable::*)(float, float, float, float, float, float))&CPlaceable::IsWithinArea, PATCH_JUMP);
ENDPATCHES
