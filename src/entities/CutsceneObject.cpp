#include "common.h"
#include "CutsceneObject.h"

CCutsceneObject::CCutsceneObject(void)
{
	m_status = STATUS_SIMPLE;
	bUsesCollision = false;
	m_flagC20 = true;
	ObjectCreatedBy = CUTSCENE_OBJECT;
	m_fMass = 1.0f;
	m_fTurnMass = 1.0f;
}
