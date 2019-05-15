#include "common.h"
#include "patcher.h"
#include "Draw.h"
#include "Camera.h"

CCamera &TheCamera = *(CCamera*)0x6FACF8;

bool
CCamera::IsSphereVisible(const CVector &center, float radius, const CMatrix *mat)
{
	RwV3d c;
	c = *(RwV3d*)&center;
	RwV3dTransformPoints(&c, &c, 1, &mat->m_matrix);
	if(c.y + radius < CDraw::GetNearClipZ()) return false;
	if(c.y - radius > CDraw::GetFarClipZ()) return false;
	if(c.x*m_vecFrustumNormals[0].x + c.y*m_vecFrustumNormals[0].y > radius) return false;
	if(c.x*m_vecFrustumNormals[1].x + c.y*m_vecFrustumNormals[1].y > radius) return false;
	if(c.y*m_vecFrustumNormals[2].y + c.z*m_vecFrustumNormals[2].z > radius) return false;
	if(c.y*m_vecFrustumNormals[3].y + c.z*m_vecFrustumNormals[3].z > radius) return false;
	return true;
}

bool
CCamera::IsPointVisible(const CVector &center, const CMatrix *mat)
{
	RwV3d c;
	c = *(RwV3d*)&center;
	RwV3dTransformPoints(&c, &c, 1, &mat->m_matrix);
	if(c.y < CDraw::GetNearClipZ()) return false;
	if(c.y > CDraw::GetFarClipZ()) return false;
	if(c.x*m_vecFrustumNormals[0].x + c.y*m_vecFrustumNormals[0].y > 0.0f) return false;
	if(c.x*m_vecFrustumNormals[1].x + c.y*m_vecFrustumNormals[1].y > 0.0f) return false;
	if(c.y*m_vecFrustumNormals[2].y + c.z*m_vecFrustumNormals[2].z > 0.0f) return false;
	if(c.y*m_vecFrustumNormals[3].y + c.z*m_vecFrustumNormals[3].z > 0.0f) return false;
	return true;
}

bool
CCamera::IsBoxVisible(RwV3d *box, const CMatrix *mat)
{
	int i;
	int frustumTests[6] = { 0 };
	RwV3dTransformPoints(box, box, 8, &mat->m_matrix);

	for(i = 0; i < 8; i++){
		if(box[i].y < CDraw::GetNearClipZ()) frustumTests[0]++;
		if(box[i].y > CDraw::GetFarClipZ()) frustumTests[1]++;
		if(box[i].x*m_vecFrustumNormals[0].x + box[i].y*m_vecFrustumNormals[0].y > 0.0f) frustumTests[2]++;
		if(box[i].x*m_vecFrustumNormals[1].x + box[i].y*m_vecFrustumNormals[1].y > 0.0f) frustumTests[3]++;
//	Why not test z?
//		if(box[i].y*m_vecFrustumNormals[2].y + box[i].z*m_vecFrustumNormals[2].z > 0.0f) frustumTests[4]++;
//		if(box[i].y*m_vecFrustumNormals[3].y + box[i].z*m_vecFrustumNormals[3].z > 0.0f) frustumTests[5]++;
	}
	for(i = 0; i < 6; i++)
		if(frustumTests[i] == 8)
			return false;		// Box is completely outside of one plane
	return true;
}


STARTPATCHES
	InjectHook(0x42C760, &CCamera::IsSphereVisible, PATCH_JUMP);
ENDPATCHES
