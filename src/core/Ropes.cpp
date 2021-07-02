#include "common.h"

#include "main.h"
#include "Timer.h"
#include "ModelIndices.h"
#include "Streaming.h"
#include "CopPed.h"
#include "Population.h"
#include "RenderBuffer.h"
#include "Camera.h"
#include "Ropes.h"

CRope CRopes::aRopes[8];

RwImVertexIndex RopeIndices[64] = {
	0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7,
	7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15,
	15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23,
	23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
	31, 32	// unused
};

void
CRope::Update(void)
{
	int i;
	float step = Pow(0.85f, CTimer::GetTimeStep());
	if(!m_bWasRegistered && CTimer::GetTimeInMilliseconds() > m_updateTimer){
		m_speed[0].z -= 0.0015f*CTimer::GetTimeStep();
		m_pos[0] += m_speed[0]*CTimer::GetTimeStep();
	}
	for(i = 1; i < ARRAY_SIZE(m_pos); i++){
		CVector prevPos = m_pos[i];
		m_pos[i] += m_speed[i]*step*CTimer::GetTimeStep();
		m_pos[i].z -= 0.05f*CTimer::GetTimeStep();
		CVector dist = m_pos[i] - m_pos[i-1];
		m_pos[i] = m_pos[i-1] + (0.625f/dist.Magnitude())*dist;
		m_speed[i] = (m_pos[i] - prevPos)/CTimer::GetTimeStep();
	}
	if(!m_bWasRegistered && m_pos[0].z < 0.0f)
		m_bActive = false;
	m_bWasRegistered = false;
}

void
CRope::Render(void)
{
	int i;
	int numVerts = 0;
	if(!TheCamera.IsSphereVisible(m_pos[16], 20.0f))
		return;

	for(i = 0; i < ARRAY_SIZE(m_pos); i++){
		RwIm3DVertexSetRGBA(&TempBufferRenderVertices[i], 128, 128, 128, 100);
		RwIm3DVertexSetPos(&TempBufferRenderVertices[i], m_pos[i].x, m_pos[i].y, m_pos[i].z);
	}

	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);

	if(RwIm3DTransform(TempBufferRenderVertices, ARRAY_SIZE(m_pos), nil, rwIM3D_VERTEXXYZ|rwIM3D_VERTEXRGBA)){
#ifdef FIX_BUGS
		RwIm3DRenderIndexedPrimitive(rwPRIMTYPELINELIST, RopeIndices, 2*(ARRAY_SIZE(m_pos)-1));
#else
		RwIm3DRenderIndexedPrimitive(rwPRIMTYPEPOLYLINE, RopeIndices, 2*(ARRAY_SIZE(m_pos)-1));
#endif
		RwIm3DEnd();
	}
}


void
CRopes::Init(void)
{
	int i;
	for(i = 0; i < ARRAY_SIZE(aRopes); i++)
		aRopes[i].m_bActive = false;
}

void
CRopes::Update(void)
{
	int i;
	for(i = 0; i < ARRAY_SIZE(aRopes); i++)
		if(aRopes[i].m_bActive)
			aRopes[i].Update();
}

void
CRopes::Render(void)
{
	int i;
	PUSH_RENDERGROUP("CRopes::Render");
	for(i = 0; i < ARRAY_SIZE(aRopes); i++)
		if(aRopes[i].m_bActive)
			aRopes[i].Render();
	POP_RENDERGROUP();
}

bool
CRopes::RegisterRope(uintptr id, CVector pos, bool setUpdateTimer)
{
	int i, j;
	for(i = 0; i < ARRAY_SIZE(aRopes); i++){
		if(aRopes[i].m_bActive && aRopes[i].m_id == id){
			aRopes[i].m_pos[0] = pos;
			aRopes[i].m_speed[0] = CVector(0.0f, 0.0f, 0.0f);
			aRopes[i].m_bWasRegistered = true;
			return true;
		}
	}
	for(i = 0; i < ARRAY_SIZE(aRopes); i++)
		if(!aRopes[i].m_bActive){
			aRopes[i].m_id = id;
			aRopes[i].m_pos[0] = pos;
			aRopes[i].m_speed[0] = CVector(0.0f, 0.0f, 0.0f);
			aRopes[i].m_unk = false;
			aRopes[i].m_bWasRegistered = true;
			aRopes[i].m_updateTimer = setUpdateTimer ? CTimer::GetTimeInMilliseconds() + 20000 : 0;
			for(j = 1; j < ARRAY_SIZE(aRopes[0].m_pos); j++){
				if(j & 1)
					aRopes[i].m_pos[j] = aRopes[i].m_pos[j-1] + CVector(0.0f, 0.0f, 0.625f);
				else
					aRopes[i].m_pos[j] = aRopes[i].m_pos[j-1] - CVector(0.0f, 0.0f, 0.625f);
				aRopes[i].m_speed[j] = CVector(0.0f, 0.0f, 0.0f);
			}
			aRopes[i].m_bActive = true;
			return true;
		}
	return false;
}

void
CRopes::SetSpeedOfTopNode(uintptr id, CVector speed)
{
	int i;
	for(i = 0; i < ARRAY_SIZE(aRopes); i++)
		if(aRopes[i].m_bActive && aRopes[i].m_id == id){
			aRopes[i].m_speed[0] = speed;
			return;
		}
}

bool
CRopes::FindCoorsAlongRope(uintptr id, float t, CVector *coors)
{
	int i, j;
	float f;
	for(i = 0; i < ARRAY_SIZE(aRopes); i++)
		if(aRopes[i].m_bActive && aRopes[i].m_id == id){
			t = (ARRAY_SIZE(aRopes[0].m_pos)-1)*Clamp(t, 0.0f, 0.999f);
			j = t;
			f = t - j; 
			*coors = (1.0f-f)*aRopes[i].m_pos[j] + f*aRopes[i].m_pos[j+1];
			return true;
		}
	return false;
}

bool
CRopes::CreateRopeWithSwatComingDown(CVector pos)
{
	static uint32 ropeId = 0;

	if(!CStreaming::HasModelLoaded(MI_SWAT) || !RegisterRope(ropeId+100, pos, true))
		return false;
	CCopPed *swat = (CCopPed*)CPopulation::AddPed(PEDTYPE_COP, COP_HELI_SWAT, pos);
	swat->bUsesCollision = false;
	swat->m_pRopeEntity = (CEntity*)1;
	swat->m_nRopeID = 100 + ropeId;
	CAnimManager::BlendAnimation(swat->GetClump(), ASSOCGRP_STD, ANIM_STD_ABSEIL, 4.0f);
	ropeId++;
	return true;
}
