#include "common.h"
#include "Range2D.h"
#include "General.h"

CRange2D::CRange2D(CVector2D _min, CVector2D _max) : min(_min), max(_max) {}

bool
CRange2D::IsInRange(CVector2D vec)
{
	return min.x < vec.x && max.x > vec.x && min.y < vec.y && max.y > vec.y;
}

void
CRange2D::DebugShowRange(float, int)
{
}

CVector2D
CRange2D::GetRandomPointInRange()
{
	return CVector2D(CGeneral::GetRandomNumberInRange(min.x, max.x), CGeneral::GetRandomNumberInRange(min.y, max.y));
}
