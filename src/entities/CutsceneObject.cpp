#include "common.h"
#include "patcher.h"
#include "main.h"
#include "Lights.h"
#include "PointLights.h"
#include "RpAnimBlend.h"
#include "AnimBlendClumpData.h"
#include "Renderer.h"
#include "ModelIndices.h"
#include "Shadows.h"
#include "Timecycle.h"
#include "CutsceneObject.h"

CCutsceneObject::CCutsceneObject(void)
{
	m_status = STATUS_SIMPLE;
	bUsesCollision = false;
	bStreamingDontDelete = true;
	ObjectCreatedBy = CUTSCENE_OBJECT;
	m_fMass = 1.0f;
	m_fTurnMass = 1.0f;
}

void
CCutsceneObject::SetModelIndex(uint32 id)
{
	CEntity::SetModelIndex(id);
	assert(RwObjectGetType(m_rwObject) == rpCLUMP);
	RpAnimBlendClumpInit((RpClump*)m_rwObject);
	(*RPANIMBLENDCLUMPDATA(m_rwObject))->velocity = &m_vecMoveSpeed;
	(*RPANIMBLENDCLUMPDATA(m_rwObject))->frames[0].flag |= AnimBlendFrameData::VELOCITY_EXTRACTION_3D;
}

void
CCutsceneObject::ProcessControl(void)
{
	CPhysical::ProcessControl();

	if(CTimer::GetTimeStep() < 1/100.0f)
		m_vecMoveSpeed *= 100.0f;
	else
		m_vecMoveSpeed *= 1.0f/CTimer::GetTimeStep();

	ApplyMoveSpeed();
}

void
CCutsceneObject::PreRender(void)
{
	if(IsPedModel(GetModelIndex()))
		CShadows::StoreShadowForPedObject(this,
			CTimeCycle::m_fShadowDisplacementX[CTimeCycle::m_CurrentStoredValue],
			CTimeCycle::m_fShadowDisplacementY[CTimeCycle::m_CurrentStoredValue],
			CTimeCycle::m_fShadowFrontX[CTimeCycle::m_CurrentStoredValue],
			CTimeCycle::m_fShadowFrontY[CTimeCycle::m_CurrentStoredValue],
			CTimeCycle::m_fShadowSideX[CTimeCycle::m_CurrentStoredValue],
			CTimeCycle::m_fShadowSideY[CTimeCycle::m_CurrentStoredValue]);
}

void
CCutsceneObject::Render(void)
{
	CObject::Render();
}

bool
CCutsceneObject::SetupLighting(void)
{
	ActivateDirectional();
	SetAmbientColoursForPedsCarsAndObjects();

	if(bRenderScorched){
		WorldReplaceNormalLightsWithScorched(Scene.world, 0.1f);
	}else{
		CVector coors = GetPosition();
		float lighting = CPointLights::GenerateLightsAffectingObject(&coors);
		if(!bHasBlip && lighting != 1.0f){
			SetAmbientAndDirectionalColours(lighting);
			return true;
		}
	}

	return false;
}

void
CCutsceneObject::RemoveLighting(bool reset)
{
	CRenderer::RemoveVehiclePedLights(this, reset);
}

STARTPATCHES
	InjectHook(0x4BA980, &CCutsceneObject::SetModelIndex_, PATCH_JUMP);
	InjectHook(0x4BA9C0, &CCutsceneObject::ProcessControl_, PATCH_JUMP);
	InjectHook(0x4BAA40, &CCutsceneObject::PreRender_, PATCH_JUMP);
	InjectHook(0x4BAAA0, &CCutsceneObject::Render_, PATCH_JUMP);
	InjectHook(0x4A7E70, &CCutsceneObject::SetupLighting_, PATCH_JUMP);
	InjectHook(0x4A7F00, &CCutsceneObject::RemoveLighting_, PATCH_JUMP);
ENDPATCHES
