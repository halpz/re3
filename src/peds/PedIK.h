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

enum LimbMoveStatus {
	ANGLES_SET_TO_MAX, // because given angles were unreachable
	ONE_ANGLE_COULDNT_BE_SET_EXACTLY, // because it can't be reached in a jiffy
	ANGLES_SET_EXACTLY
};

class CPed;

class CPedIK
{
public:
	enum {
		FLAG_1 = 1,
		LOOKING = 2,
		AIMS_WITH_ARM = 4,
	};

	CPed *m_ped;
	LimbOrientation m_headOrient;
	LimbOrientation m_torsoOrient;
	LimbOrientation m_upperArmOrient;
	LimbOrientation m_lowerArmOrient;
	int32 m_flags;

	static LimbMovementInfo &ms_torsoInfo;
	static LimbMovementInfo &ms_headInfo;

	CPedIK(CPed *ped);
	bool PointGunInDirection(float phi, float theta);
	bool PointGunAtPosition(CVector *position);
	void GetComponentPosition(RwV3d *pos, PedNode node);
	static RwMatrix *GetWorldMatrix(RwFrame *source, RwMatrix *destination);
	void RotateTorso(AnimBlendFrameData* animBlend, LimbOrientation* limb, bool changeRoll);
	void ExtractYawAndPitchLocal(RwMatrixTag*, float*, float*);
	void ExtractYawAndPitchWorld(RwMatrixTag*, float*, float*);
	LimbMoveStatus MoveLimb(LimbOrientation &a1, float a2, float a3, LimbMovementInfo &a4);
	bool RestoreGunPosn(void);
	bool LookInDirection(float phi, float theta);
	bool LookAtPosition(CVector const& pos);
};
static_assert(sizeof(CPedIK) == 0x28, "CPedIK: error");
