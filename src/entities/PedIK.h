#pragma once
#include "common.h"
#include "PedModelInfo.h"

struct LimbOrientation
{
	float phi;
	float theta;
};

class CPed;

class CPedIK
{
public:
	// TODO
	enum {
		FLAG_1 = 1,
		FLAG_2 = 2,	// related to looking somewhere
		FLAG_4 = 4,	// aims with arm
	};

	CPed *m_ped;
	LimbOrientation m_headOrient;
	LimbOrientation m_torsoOrient;
	LimbOrientation m_upperArmOrient;
	LimbOrientation m_lowerArmOrient;
	int32 m_flags;

	CPedIK(CPed *ped);
	bool PointGunInDirection(float phi, float theta);
	bool PointGunAtPosition(CVector *position);
	void GetComponentPosition(RwV3d *pos, PedNode node);
	static RwMatrix *GetWorldMatrix(RwFrame *source, RwMatrix *destination);
};
static_assert(sizeof(CPedIK) == 0x28, "CPedIK: error");
