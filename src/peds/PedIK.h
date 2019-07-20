#pragma once
#include "common.h"
#include "PedModelInfo.h"
#include "AnimBlendClumpData.h"

struct LimbOrientation
{
	float phi;
	float theta;
};

struct LimbMovementInfo {
	float maxYaw;
	float minYaw;
	float yawD;
	float maxPitch;
	float minPitch;
	float pitchD;
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

	static LimbMovementInfo &ms_torsoInfo;

	CPedIK(CPed *ped);
	bool PointGunInDirection(float phi, float theta);
	bool PointGunAtPosition(CVector *position);
	void GetComponentPosition(RwV3d *pos, PedNode node);
	static RwMatrix *GetWorldMatrix(RwFrame *source, RwMatrix *destination);
	void RotateTorso(AnimBlendFrameData* animBlend, LimbOrientation* limb, bool changeRoll);
	void ExtractYawAndPitchLocal(RwMatrixTag*, float*, float*);
	void ExtractYawAndPitchWorld(RwMatrixTag*, float*, float*);
	int8 MoveLimb(LimbOrientation &a1, float a2, float a3, LimbMovementInfo &a4);
	bool RestoreGunPosn(void);
};
static_assert(sizeof(CPedIK) == 0x28, "CPedIK: error");
