#include "common.h"
#include "patcher.h"
#include "PedIK.h"
#include "Ped.h"

WRAPPER bool CPedIK::PointGunInDirection(float phi, float theta) { EAXJMP(0x4ED9B0); }
WRAPPER bool CPedIK::PointGunAtPosition(CVector *position) { EAXJMP(0x4ED920); }

void
CPedIK::GetComponentPosition(RwV3d *pos, PedNode node)
{
	RwFrame *f;
	RwMatrix *mat;

	f = m_ped->GetNodeFrame(node);
	mat = &f->modelling;
	*pos = mat->pos;

	for (f = RwFrameGetParent(f); f; f = RwFrameGetParent(f))
		RwV3dTransformPoints(pos, pos, 1, &f->modelling);
}

RwMatrix*
CPedIK::GetWorldMatrix(RwFrame *source, RwMatrix *destination)
{
	RwFrame *i;

	*destination = source->modelling;

	for (i = RwFrameGetParent(source); i; i = RwFrameGetParent(i))
		RwMatrixTransform(destination, &i->modelling, rwCOMBINEPOSTCONCAT);

	return destination;
}

STARTPATCHES
	InjectHook(0x4ED0F0, &CPedIK::GetComponentPosition, PATCH_JUMP);
	InjectHook(0x4ED060, &CPedIK::GetWorldMatrix, PATCH_JUMP);
ENDPATCHES