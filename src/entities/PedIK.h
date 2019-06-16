#pragma once
#include "common.h"

struct LimbOrientation
{
	float phi;
	float theta;
};

class CPed;

class CPedIK
{
public:
	CPed* m_ped;
	LimbOrientation m_headOrient;
	LimbOrientation m_torsoOrient;
	LimbOrientation m_upperArmOrient;
	LimbOrientation m_lowerArmOrient;
	int32 m_flags;

	void GetComponentPosition(RwV3d* pos, int id);
	bool PointGunInDirection(float phi, float theta);
	bool PointGunAtPosition(CVector* position);
};
static_assert(sizeof(CPedIK) == 0x28, "CPedIK: error");
