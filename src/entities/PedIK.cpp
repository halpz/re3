#include "common.h"
#include "patcher.h"
#include "PedIK.h"
#include "Ped.h"

WRAPPER bool CPedIK::PointGunInDirection(float phi, float theta) { EAXJMP(0x4ED9B0); }
WRAPPER bool CPedIK::PointGunAtPosition(CVector *position) { EAXJMP(0x4ED920); }

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
ENDPATCHES