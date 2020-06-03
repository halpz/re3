#include "common.h"
#include "Range3D.h"
#include "General.h"

CRange3D::CRange3D(CVector _min, CVector _max) : min(_min), max(_max) {}

bool
CRange3D::IsInRange(CVector vec)
{
	return min.x < vec.x && max.x > vec.x && min.y < vec.y && max.y > vec.y && min.z < vec.z && max.z > vec.z;
}

void
CRange3D::DebugShowRange(float, int)
{
}

CVector
CRange3D::GetRandomPointInRange()
{
	return CVector(CGeneral::GetRandomNumberInRange(min.x, max.x), CGeneral::GetRandomNumberInRange(min.y, max.y),
	               CGeneral::GetRandomNumberInRange(min.z, max.z));
}
