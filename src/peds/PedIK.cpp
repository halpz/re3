#include "common.h"

#include "Camera.h"
#include "PedIK.h"
#include "Ped.h"
#include "General.h"
#include "RwHelper.h"

LimbMovementInfo CPedIK::ms_torsoInfo = { DEGTORAD(50.0f), DEGTORAD(-50.0f), DEGTORAD(15.0f), DEGTORAD(45.0f), DEGTORAD(-45.0f), DEGTORAD(7.0f) };
LimbMovementInfo CPedIK::ms_headInfo = { DEGTORAD(90.0f), DEGTORAD(-90.0f), DEGTORAD(10.0f), DEGTORAD(45.0f), DEGTORAD(-45.0f), DEGTORAD(5.0f) };
LimbMovementInfo CPedIK::ms_headRestoreInfo = { DEGTORAD(90.0f), DEGTORAD(-90.0f), DEGTORAD(10.0f), DEGTORAD(45.0f), DEGTORAD(-45.0f), DEGTORAD(5.0f) };
LimbMovementInfo CPedIK::ms_upperArmInfo = { DEGTORAD(20.0f), DEGTORAD(-100.0f), DEGTORAD(20.0f), DEGTORAD(70.0f), DEGTORAD(-70.0f), DEGTORAD(10.0f) };
LimbMovementInfo CPedIK::ms_lowerArmInfo = { DEGTORAD(80.0f), DEGTORAD(0.0f), DEGTORAD(20.0f), DEGTORAD(90.0f), DEGTORAD(-90.0f), DEGTORAD(5.0f) };

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
	float c = Cos(m_ped->m_fRotationCur);
	float s = Sin(m_ped->m_fRotationCur);
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
		float alpha = Acos(dotProduct);

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
CPedIK::GetComponentPosition(RwV3d *pos, uint32 node)
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

LimbMoveStatus
CPedIK::MoveLimb(LimbOrientation &limb, float approxPhi, float approxTheta, LimbMovementInfo &moveInfo)
{
	LimbMoveStatus result = ONE_ANGLE_COULDNT_BE_SET_EXACTLY;

	// phi

	if (limb.phi > approxPhi) {
		limb.phi -= moveInfo.yawD;
	} else if (limb.phi < approxPhi) {
		limb.phi += moveInfo.yawD;
	}

	if (Abs(limb.phi - approxPhi) < moveInfo.yawD) {
		limb.phi = approxPhi;
		result = ANGLES_SET_EXACTLY;
	}

	if (limb.phi > moveInfo.maxYaw || limb.phi < moveInfo.minYaw) {
		limb.phi = clamp(limb.phi, moveInfo.minYaw, moveInfo.maxYaw);
		result = ANGLES_SET_TO_MAX;
	}

	// theta

	if (limb.theta > approxTheta) {
		limb.theta -= moveInfo.pitchD;
	} else if (limb.theta < approxTheta) {
		limb.theta += moveInfo.pitchD;
	}

	if (Abs(limb.theta - approxTheta) < moveInfo.pitchD)
		limb.theta = approxTheta;
	else
		result = ONE_ANGLE_COULDNT_BE_SET_EXACTLY;

	if (limb.theta > moveInfo.maxPitch || limb.theta < moveInfo.minPitch) {
		limb.theta = clamp(limb.theta, moveInfo.minPitch, moveInfo.maxPitch);
		result = ANGLES_SET_TO_MAX;
	}
	return result;
}

bool
CPedIK::RestoreGunPosn(void)
{
	LimbMoveStatus limbStatus = MoveLimb(m_torsoOrient, 0.0f, 0.0f, ms_torsoInfo);
	RotateTorso(m_ped->m_pFrames[PED_MID], &m_torsoOrient, false);
	return limbStatus == ANGLES_SET_EXACTLY;
}

bool
CPedIK::LookInDirection(float phi, float theta)
{
	bool success = true;
	RwFrame *frame = m_ped->GetNodeFrame(PED_HEAD);
	RwMatrix *frameMat = RwFrameGetMatrix(frame);

	if (!(m_ped->m_pFrames[PED_HEAD]->flag & AnimBlendFrameData::IGNORE_ROTATION)) {
		m_ped->m_pFrames[PED_HEAD]->flag |= AnimBlendFrameData::IGNORE_ROTATION;
		CPedIK::ExtractYawAndPitchLocal(frameMat, &m_headOrient.phi, &m_headOrient.theta);
	}

	RwMatrix *worldMat = RwMatrixCreate();
	worldMat = CPedIK::GetWorldMatrix(RwFrameGetParent(frame), worldMat);

	float alpha, beta;
	CPedIK::ExtractYawAndPitchWorld(worldMat, &alpha, &beta);
	RwMatrixDestroy(worldMat);

	alpha += m_torsoOrient.phi;
	float neededPhiTurn = CGeneral::LimitRadianAngle(phi - alpha);
	beta *= cos(neededPhiTurn);

	float neededThetaTurn = CGeneral::LimitRadianAngle(theta - beta);
	LimbMoveStatus headStatus = CPedIK::MoveLimb(m_headOrient, neededPhiTurn, neededThetaTurn, ms_headInfo);
	if (headStatus == ANGLES_SET_TO_MAX)
		success = false;

	if (headStatus != ANGLES_SET_EXACTLY && !(m_flags & LOOKAROUND_HEAD_ONLY)) {
		float remainingTurn = CGeneral::LimitRadianAngle(phi - m_ped->m_fRotationCur);
		if (CPedIK::MoveLimb(m_torsoOrient, remainingTurn, theta, ms_torsoInfo))
			success = true;
	}
	CMatrix nextFrame = CMatrix(frameMat);
	CVector framePos = nextFrame.GetPosition();

	nextFrame.SetRotateZ(m_headOrient.theta);
	nextFrame.RotateX(m_headOrient.phi);
	nextFrame.GetPosition() += framePos;
	nextFrame.UpdateRW();

	if (!(m_flags & LOOKAROUND_HEAD_ONLY))
		RotateTorso(m_ped->m_pFrames[PED_MID], &m_torsoOrient, false);

	return success;
}

bool
CPedIK::LookAtPosition(CVector const &pos)
{
	float phiToFace = CGeneral::GetRadianAngleBetweenPoints(
		pos.x, pos.y,
		m_ped->GetPosition().x, m_ped->GetPosition().y);

	float thetaToFace = CGeneral::GetRadianAngleBetweenPoints(
		pos.z, (m_ped->GetPosition() - pos).Magnitude2D(),
		m_ped->GetPosition().z, 0.0f);

	return LookInDirection(phiToFace, thetaToFace);
}

bool
CPedIK::PointGunInDirection(float phi, float theta)
{
	bool result = true;
	bool armPointedToGun = false;
	float angle = CGeneral::LimitRadianAngle(phi - m_ped->m_fRotationCur);
	m_flags &= (~GUN_POINTED_SUCCESSFULLY);
	m_flags |= LOOKAROUND_HEAD_ONLY;
	if (m_flags & AIMS_WITH_ARM) {
		armPointedToGun = PointGunInDirectionUsingArm(angle, theta);
		angle = CGeneral::LimitRadianAngle(angle - m_upperArmOrient.phi);
	}
	if (armPointedToGun) {
		if (m_flags & AIMS_WITH_ARM && m_torsoOrient.phi * m_upperArmOrient.phi < 0.0f)
			MoveLimb(m_torsoOrient, 0.0f, m_torsoOrient.theta, ms_torsoInfo);
	} else {
		RwMatrix *matrix = GetWorldMatrix(RwFrameGetParent(m_ped->GetNodeFrame(PED_UPPERARMR)), RwMatrixCreate());
		float yaw, pitch;
		ExtractYawAndPitchWorld(matrix, &yaw, &pitch);
		RwMatrixDestroy(matrix);
		LimbMoveStatus status = MoveLimb(m_torsoOrient, angle, theta, ms_torsoInfo);
		if (status == ANGLES_SET_TO_MAX)
			result = false;
		else if (status == ANGLES_SET_EXACTLY)
			m_flags |= GUN_POINTED_SUCCESSFULLY;
	}
	if (TheCamera.Cams[TheCamera.ActiveCam].Using3rdPersonMouseCam() && m_flags & AIMS_WITH_ARM)
		RotateTorso(m_ped->m_pFrames[PED_MID], &m_torsoOrient, true);
	else
		RotateTorso(m_ped->m_pFrames[PED_MID], &m_torsoOrient, false);
	return result;
}

bool
CPedIK::PointGunInDirectionUsingArm(float phi, float theta)
{
	bool result = false;
	RwFrame *frame = m_ped->GetNodeFrame(PED_UPPERARMR);
	RwMatrix *matrix = GetWorldMatrix(RwFrameGetParent(frame), RwMatrixCreate());

	RwV3d upVector = { matrix->right.z, matrix->up.z, matrix->at.z };

	float yaw, pitch;
	ExtractYawAndPitchWorld(matrix, &yaw, &pitch);
	RwMatrixDestroy(matrix);

	RwV3d rightVector = { 0.0f, 0.0f, 1.0f };
	RwV3d forwardVector = { 1.0f, 0.0f, 0.0f };

	float uaPhi = phi - m_torsoOrient.phi - DEGTORAD(15.0f);
	LimbMoveStatus uaStatus = MoveLimb(m_upperArmOrient, uaPhi, CGeneral::LimitRadianAngle(theta - pitch), ms_upperArmInfo);
	if (uaStatus == ANGLES_SET_EXACTLY) {
		m_flags |= GUN_POINTED_SUCCESSFULLY;
		result = true;
	}
	if (uaStatus == ANGLES_SET_TO_MAX) {
		float laPhi = uaPhi - m_upperArmOrient.phi;

		LimbMoveStatus laStatus;
		if (laPhi > 0.0f)
			laStatus = MoveLimb(m_lowerArmOrient, laPhi, -DEGTORAD(45.0f), ms_lowerArmInfo);
		else
			laStatus = MoveLimb(m_lowerArmOrient, laPhi, 0.0f, ms_lowerArmInfo);

		if (laStatus == ANGLES_SET_EXACTLY) {
			m_flags |= GUN_POINTED_SUCCESSFULLY;
			result = true;
		}
		RwFrame *child = GetFirstChild(frame);
		RwV3d pos = RwFrameGetMatrix(child)->pos;
		RwMatrixRotate(RwFrameGetMatrix(child), &forwardVector, RADTODEG(m_lowerArmOrient.theta), rwCOMBINEPOSTCONCAT);
		RwMatrixRotate(RwFrameGetMatrix(child), &rightVector, RADTODEG(-m_lowerArmOrient.phi), rwCOMBINEPOSTCONCAT);
		RwFrameGetMatrix(child)->pos = pos;
	}

	RwV3d pos = RwFrameGetMatrix(frame)->pos;
	RwMatrixRotate(RwFrameGetMatrix(frame), &rightVector, RADTODEG(m_upperArmOrient.theta), rwCOMBINEPOSTCONCAT);
	RwMatrixRotate(RwFrameGetMatrix(frame), &upVector, RADTODEG(m_upperArmOrient.phi), rwCOMBINEPOSTCONCAT);
	RwFrameGetMatrix(frame)->pos = pos;
	return result;
}

bool
CPedIK::PointGunAtPosition(CVector const& position)
{
	return PointGunInDirection(
		CGeneral::GetRadianAngleBetweenPoints(position.x, position.y, m_ped->GetPosition().x, m_ped->GetPosition().y),
		CGeneral::GetRadianAngleBetweenPoints(position.z, Distance2D(m_ped->GetPosition(), position.x, position.y),
		m_ped->GetPosition().z,
		0.0f));
}

bool
CPedIK::RestoreLookAt(void)
{
	bool result = false;
	RwMatrix *mat = RwFrameGetMatrix(m_ped->GetNodeFrame(PED_HEAD));
	if (m_ped->m_pFrames[PED_HEAD]->flag & AnimBlendFrameData::IGNORE_ROTATION) {
		m_ped->m_pFrames[PED_HEAD]->flag &= (~AnimBlendFrameData::IGNORE_ROTATION);
	} else {
		float yaw, pitch;
		ExtractYawAndPitchLocal(mat, &yaw, &pitch);
		if (MoveLimb(m_headOrient, yaw, pitch, ms_headRestoreInfo) == ANGLES_SET_EXACTLY)
			result = true;
	}

	CMatrix matrix(mat);
	CVector pos = matrix.GetPosition();
	matrix.SetRotateZ(m_headOrient.theta);
	matrix.RotateX(m_headOrient.phi);
	matrix.Translate(pos);
	matrix.UpdateRW();

	if (!(m_flags & LOOKAROUND_HEAD_ONLY))
		MoveLimb(m_torsoOrient, 0.0f, 0.0f, ms_torsoInfo);
	if (!(m_flags & LOOKAROUND_HEAD_ONLY))
		RotateTorso(m_ped->m_pFrames[PED_MID], &m_torsoOrient, false);

	return result;
}

void
CPedIK::ExtractYawAndPitchWorld(RwMatrix *mat, float *yaw, float *pitch)
{
	float f = clamp(DotProduct(mat->up, CVector(0.0f, 1.0f, 0.0f)), -1.0f, 1.0f);
	*yaw = Acos(f);
	if (mat->up.x > 0.0f) *yaw = -*yaw;

	f = clamp(DotProduct(mat->right, CVector(0.0f, 0.0f, 1.0f)), -1.0f, 1.0f);
	*pitch = Acos(f);
	if (mat->up.z > 0.0f) *pitch = -*pitch;
}

void
CPedIK::ExtractYawAndPitchLocal(RwMatrix *mat, float *yaw, float *pitch)
{
	float f = clamp(DotProduct(mat->at, CVector(0.0f, 0.0f, 1.0f)), -1.0f, 1.0f);
	*yaw = Acos(f);
	if (mat->at.y > 0.0f) *yaw = -*yaw;

	f = clamp(DotProduct(mat->right, CVector(1.0f, 0.0f, 0.0f)), -1.0f, 1.0f);
	*pitch = Acos(f);
	if (mat->up.x > 0.0f) *pitch = -*pitch;
}
