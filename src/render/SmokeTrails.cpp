#include "common.h"
#include "SmokeTrails.h"
#include "Camera.h"
#include "World.h"
#include "CutsceneMgr.h"
#include "PlayerPed.h"
#include "Entity.h"
#include "rpworld.h"
#include "Bones.h"
#include "Timer.h"
#include "Weather.h"

bool CSmokeTrails::CigOn = false;
CSmokeTrail CSmokeTrails::aSmoke[3];

extern RwImVertexIndex SmokeTrailIndices[32] = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8,
9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16 };

float RandomSmoke[16] = { 10.0f, 5.0f, -1.0f, -9.0f, -7.0f, -1.0f, 0.0f, 3.0f, 6.0f, 7.0f, 4.0f, 2.0f,
5.0f, 7.0f };


void
CSmokeTrail::RegisterPoint(CVector regPosition, float opacity) {
	bool bShifted = false;

	if (m_time[0] && CTimer::GetTimeInMilliseconds() - m_time[0] > 150) {
		bShifted = true;
		for (int32 i = 15; i > 0; i--) {
			m_pos[i] = m_pos[i - 1];
			m_time[i] = m_time[i - 1];
			m_density[i] = m_density[i - 1];
		}
		++m_seed;
	}
	m_pos[0] = regPosition;

	if (bShifted || !m_time[0]) {
		m_time[0] = CTimer::GetTimeInMilliseconds();
		float currentDensity = 0.1f / (m_pos[1] - m_pos[2]).Magnitude();
		m_density[1] = opacity * Min(currentDensity, 1.0f);
	}
	m_density[0] = 0.0f;
}

void
CSmokeTrail::Init(int num) {
	for (int32 i = 0; i < 16; i++) 
		m_time[i] = 0;
	m_seed = num * 2;
}

void
CSmokeTrails::Init(void) {
	for(int32 i = 0; i < 3; i++)
		aSmoke[i].Init(i);
}

void
CSmokeTrails::Render(void) {
	for (int32 i = 0; i < 3; i++)
		aSmoke[i].Render();
}

void 
CSmokeTrail::Render(void) {
	int numVerts = 0;
	RwIm3DVertex TempVertexBuffer[16];

	if (TheCamera.IsSphereVisible(m_pos[0], 10.0f)) {
		for (int32 i = 0; i < 16; i++) {
			int timeSinceSpawned = CTimer::GetTimeInMilliseconds() - m_time[i];
			
			if (timeSinceSpawned > 2250)
				m_time[i] = 0;
			
			if (m_time[i]) {
				int alpha = (1.0f - timeSinceSpawned / 2250.0f) * 110.0f * m_density[i];
				float offset = timeSinceSpawned * CWeather::Wind * 0.000099f;
				float currentX = (m_pos[i].x + timeSinceSpawned * RandomSmoke[(i - m_seed) & 0xF] * 0.0000099f) - offset;
				float currentY = (m_pos[i].y + timeSinceSpawned * RandomSmoke[(i - m_seed + 5) & 0xF] * 0.0000099f) - offset;
				float currentZ = m_pos[i].z + timeSinceSpawned * 0.00039f;
				RwIm3DVertexSetRGBA(&TempVertexBuffer[i], 200, 200, 200, alpha);
				RwIm3DVertexSetPos(&TempVertexBuffer[i], currentX, currentY, currentZ);
				numVerts++;
			}
		}
	}
	
	if (numVerts > 1) {
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
		RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);

		if (RwIm3DTransform(TempVertexBuffer, numVerts, nil, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA)) {
			RwIm3DRenderIndexedPrimitive(rwPRIMTYPEPOLYLINE, SmokeTrailIndices, 2*(numVerts - 1));
			RwIm3DEnd();
		}
	}
}

void
CSmokeTrails::Update(void) {

	if (!CSmokeTrails::CigOn || TheCamera.Using1stPersonWeaponMode() || !FindPlayerPed() ||
		FindPlayerVehicle() || CCutsceneMgr::IsRunning() || !FindPlayerPed()->GetClump())
		return;

	RwV3d startPos = {0.026f, 0.15f, 0.02f};
	RwV3d endPos = {0.026f, 0.05f, 0.02f};

	RpHAnimHierarchy *hier = GetAnimHierarchyFromSkinClump(FindPlayerPed()->GetClump());
	int32 idx = RpHAnimIDGetIndex(hier, ConvertPedNode2BoneTag(PED_HEAD));
	RwMatrix *head = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
	RwV3dTransformPoints(&startPos, &startPos, 1, head);
	RwV3dTransformPoints(&endPos, &endPos, 1, head);

	aSmoke[0].RegisterPoint(startPos, 1.0f);
	aSmoke[1].RegisterPoint(startPos, 0.75f);
	aSmoke[2].RegisterPoint(startPos, 0.5f); 

	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);

	int32 color = 255;
	RwIm3DVertex TempVertexBuffer[2];
	RwIm3DVertexSetRGBA(&TempVertexBuffer[0], color, color, color, color);
	RwIm3DVertexSetPos(&TempVertexBuffer[0], startPos.x, startPos.y, startPos.z);
	RwIm3DVertexSetRGBA(&TempVertexBuffer[1], color, color, color, color);
	RwIm3DVertexSetPos(&TempVertexBuffer[1], endPos.x, endPos.y, endPos.z);

	if (RwIm3DTransform(TempVertexBuffer, 2, nil, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA)) {
		RwIm3DRenderIndexedPrimitive(rwPRIMTYPEPOLYLINE, SmokeTrailIndices, 2);
		RwIm3DEnd();
	}
}
