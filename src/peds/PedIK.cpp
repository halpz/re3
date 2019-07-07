#include "common.h"
#include "patcher.h"
#include "PedIK.h"
#include "Ped.h"

WRAPPER bool CPedIK::PointGunInDirection(float phi, float theta) { EAXJMP(0x4ED9B0); }
WRAPPER bool CPedIK::PointGunAtPosition(CVector *position) { EAXJMP(0x4ED920); }
WRAPPER void CPedIK::ExtractYawAndPitchLocal(RwMatrixTag*, float*, float*) { EAXJMP(0x4ED2C0); }
WRAPPER void CPedIK::ExtractYawAndPitchWorld(RwMatrixTag*, float*, float*) { EAXJMP(0x4ED140); }

CPedIK::CPedIK(CPed *ped)
{
	m_ped = ped;
	m_flags = 0;
	m_headOrient.phi = 0.0f;
	m_headOrient.theta = 0.0f;
	m_torsoOrient.phi = 0.0f;
	m_torsoOrient.theta = 0.0f;
	m_upperArmOrient.phi = 0.0f;
	m_upperArmOrient.theta = 0.0f;
	m_lowerArmOrient.phi = 0.0f;
	m_lowerArmOrient.theta = 0.0f;
}

void
CPedIK::RotateTorso(AnimBlendFrameData *animBlend, LimbOrientation *limb, bool changeRoll)
{
	RwFrame *f = animBlend->frame;
	RwMatrix *mat = CPedIK::GetWorldMatrix(RwFrameGetParent(f), RwMatrixCreate());

	RwV3d upVector = { mat->right.z, mat->up.z, mat->at.z };
	RwV3d rightVector;
	RwV3d pos = RwFrameGetMatrix(f)->pos;

	// rotation == 0 -> looking in y direction
	// left? vector
	float c = cos(m_ped->m_fRotationCur);
	float s = sin(m_ped->m_fRotationCur);
	rightVector.x = -(c*mat->right.x + s*mat->right.y);
	rightVector.y = -(c*mat->up.x + s*mat->up.y);
	rightVector.z = -(c*mat->at.x + s*mat->at.y);

	if(changeRoll){
		// Used when aiming only involves over the legs.(canAimWithArm)
		// Automatically changes roll(forward rotation) axis of the parts above upper legs while moving, based on position of upper legs.
		// Not noticeable in normal conditions...

		RwV3d forwardVector;
		CVector inversedForward = CrossProduct(CVector(0.0f, 0.0f, 1.0f), mat->up);
		inversedForward.Normalise();
		float dotProduct = DotProduct(mat->at, inversedForward);
		if(dotProduct > 1.0f) dotProduct = 1.0f;
		if(dotProduct < -1.0f) dotProduct = -1.0f;
		float alpha = acos(dotProduct);

		if(mat->at.z < 0.0f)
			alpha = -alpha;

		forwardVector.x = s * mat->right.x - c * mat->right.y;
		forwardVector.y = s * mat->up.x - c * mat->up.y;
		forwardVector.z = s * mat->at.x - c * mat->at.y;

		float curYaw, curPitch;
		CPedIK::ExtractYawAndPitchWorld(mat, &curYaw, &curPitch);
		RwMatrixRotate(RwFrameGetMatrix(f), &rightVector, RADTODEG(limb->theta), rwCOMBINEPOSTCONCAT);
		RwMatrixRotate(RwFrameGetMatrix(f), &upVector, RADTODEG(limb->phi - (curYaw - m_ped->m_fRotationCur)), rwCOMBINEPOSTCONCAT);
		RwMatrixRotate(RwFrameGetMatrix(f), &forwardVector, RADTODEG(alpha), rwCOMBINEPOSTCONCAT);
	}else{
		// pitch
		RwMatrixRotate(RwFrameGetMatrix(f), &rightVector, RADTODEG(limb->theta), rwCOMBINEPOSTCONCAT);
		// yaw
		RwMatrixRotate(RwFrameGetMatrix(f), &upVector, RADTODEG(limb->phi), rwCOMBINEPOSTCONCAT);
	}
	RwFrameGetMatrix(f)->pos = pos;
	RwMatrixDestroy(mat);
}

void
CPedIK::GetComponentPosition(RwV3d *pos, PedNode node)
{
	RwFrame *f;
	RwMatrix *mat;

	f = m_ped->GetNodeFrame(node);
	mat = RwFrameGetMatrix(f);
	*pos = mat->pos;

	for (f = RwFrameGetParent(f); f; f = RwFrameGetParent(f))
		RwV3dTransformPoints(pos, pos, 1, RwFrameGetMatrix(f));
}

RwMatrix*
CPedIK::GetWorldMatrix(RwFrame *source, RwMatrix *destination)
{
	RwFrame *i;

	*destination = *RwFrameGetMatrix(source);

	for (i = RwFrameGetParent(source); i; i = RwFrameGetParent(i))
		RwMatrixTransform(destination, RwFrameGetMatrix(i), rwCOMBINEPOSTCONCAT);

	return destination;
}

STARTPATCHES
	InjectHook(0x4ED0F0, &CPedIK::GetComponentPosition, PATCH_JUMP);
	InjectHook(0x4ED060, &CPedIK::GetWorldMatrix, PATCH_JUMP);
	InjectHook(0x4EDDB0, &CPedIK::RotateTorso, PATCH_JUMP);
ENDPATCHES