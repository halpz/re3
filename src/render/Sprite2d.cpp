#include "common.h"

#include "main.h"
#include "Draw.h"
#include "Camera.h"
#include "Sprite2d.h"
#include "Font.h"
#include "RenderBuffer.h"

float CSprite2d::RecipNearClip;
float CSprite2d::NearScreenZ;
float CSprite2d::NearCamZ;
int CSprite2d::nextBufferVertex;
int CSprite2d::nextBufferIndex;
RwIm2DVertex CSprite2d::maVertices[8];

void
CSprite2d::SetRecipNearClip(void)
{
	// Used but empty in VC, instead they set in InitPerFrame. Isn't that great?
}

void
CSprite2d::InitPerFrame(void)
{
	nextBufferVertex = 0;
	nextBufferIndex = 0;
	RecipNearClip = 1.0f / RwCameraGetNearClipPlane(Scene.camera);
	NearScreenZ = RwIm2DGetNearScreenZ();
	// not original but you're supposed to set camera z too
	// wrapping all this in FIX_BUGS is too ugly
	NearCamZ = RwCameraGetNearClipPlane(Scene.camera);
}
void
CSprite2d::Delete(void)
{
	if(m_pTexture){
		RwTextureDestroy(m_pTexture);
		m_pTexture = nil;
	}
}

void
CSprite2d::SetTexture(const char *name)
{
	Delete();
	if(name)
		m_pTexture = RwTextureRead(name, nil);
}

void
CSprite2d::SetTexture(const char *name, const char *mask)
{
	Delete();
	if(name)
		m_pTexture = RwTextureRead(name, mask);
}

void
CSprite2d::SetAddressing(RwTextureAddressMode addr)
{
	if(m_pTexture)
		RwTextureSetAddressing(m_pTexture, addr);
}

void
CSprite2d::SetRenderState(void)
{
	if(m_pTexture)
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(m_pTexture));
	else
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);
}

void
CSprite2d::Draw(float x, float y, float w, float h, const CRGBA &col)
{
	SetVertices(CRect(x, y, x + w, y + h), col, col, col, col);
	SetRenderState();
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
}

void
CSprite2d::Draw(const CRect &rect, const CRGBA &col)
{
	SetVertices(rect, col, col, col, col);
	SetRenderState();
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
}

void
CSprite2d::Draw(const CRect &rect, const CRGBA &col,
	float u0, float v0, float u1, float v1, float u3, float v3, float u2, float v2)
{
	SetVertices(rect, col, col, col, col, u0, v0, u1, v1, u3, v3, u2, v2);
	SetRenderState();
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
}

void
CSprite2d::Draw(const CRect &rect, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3)
{
	SetVertices(rect, c0, c1, c2, c3);
	SetRenderState();
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
}

void
CSprite2d::Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA &col)
{
	SetVertices(x1, y1, x2, y2, x3, y3, x4, y4, col, col, col, col);
	SetRenderState();
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
}

// Arguments:
// 2---3
// |   |
// 0---1
void
CSprite2d::SetVertices(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3)
{
	// This is what we draw:
	// 0---1
	// | / |
	// 3---2
	RwIm2DVertexSetScreenX(&maVertices[0], r.left);
	RwIm2DVertexSetScreenY(&maVertices[0], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[0], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[0], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[0], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[0], c2.r, c2.g, c2.b, c2.a);
	RwIm2DVertexSetU(&maVertices[0], 0.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[0], 0.0f, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[1], r.right);
	RwIm2DVertexSetScreenY(&maVertices[1], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[1], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[1], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[1], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[1], c3.r, c3.g, c3.b, c3.a);
	RwIm2DVertexSetU(&maVertices[1], 1.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[1], 0.0f, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[2], r.right);
	RwIm2DVertexSetScreenY(&maVertices[2], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[2], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[2], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[2], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[2], c1.r, c1.g, c1.b, c1.a);
	RwIm2DVertexSetU(&maVertices[2], 1.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[2], 1.0f, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[3], r.left);
	RwIm2DVertexSetScreenY(&maVertices[3], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[3], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[3], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[3], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[3], c0.r, c0.g, c0.b, c0.a);
	RwIm2DVertexSetU(&maVertices[3], 0.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[3], 1.0f, RecipNearClip);
}

void
CSprite2d::SetVertices(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3,
	float u0, float v0, float u1, float v1, float u3, float v3, float u2, float v2)
{
	// This is what we draw:
	// 0---1
	// | / |
	// 3---2
	RwIm2DVertexSetScreenX(&maVertices[0], r.left);
	RwIm2DVertexSetScreenY(&maVertices[0], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[0], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[0], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[0], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[0], c2.r, c2.g, c2.b, c2.a);
	RwIm2DVertexSetU(&maVertices[0], u0, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[0], v0, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[1], r.right);
	RwIm2DVertexSetScreenY(&maVertices[1], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[1], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[1], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[1], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[1], c3.r, c3.g, c3.b, c3.a);
	RwIm2DVertexSetU(&maVertices[1], u1, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[1], v1, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[2], r.right);
	RwIm2DVertexSetScreenY(&maVertices[2], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[2], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[2], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[2], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[2], c1.r, c1.g, c1.b, c1.a);
	RwIm2DVertexSetU(&maVertices[2], u2, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[2], v2, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[3], r.left);
	RwIm2DVertexSetScreenY(&maVertices[3], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[3], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[3], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[3], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[3], c0.r, c0.g, c0.b, c0.a);
	RwIm2DVertexSetU(&maVertices[3], u3, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[3], v3, RecipNearClip);
}

void
CSprite2d::SetVertices(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
		const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3)
{
	RwIm2DVertexSetScreenX(&maVertices[0], x3);
	RwIm2DVertexSetScreenY(&maVertices[0], y3);
	RwIm2DVertexSetScreenZ(&maVertices[0], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[0], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[0], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[0], c2.r, c2.g, c2.b, c2.a);
	RwIm2DVertexSetU(&maVertices[0], 0.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[0], 0.0f, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[1], x4);
	RwIm2DVertexSetScreenY(&maVertices[1], y4);
	RwIm2DVertexSetScreenZ(&maVertices[1], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[1], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[1], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[1], c3.r, c3.g, c3.b, c3.a);
	RwIm2DVertexSetU(&maVertices[1], 1.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[1], 0.0f, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[2], x2);
	RwIm2DVertexSetScreenY(&maVertices[2], y2);
	RwIm2DVertexSetScreenZ(&maVertices[2], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[2], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[2], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[2], c1.r, c1.g, c1.b, c1.a);
	RwIm2DVertexSetU(&maVertices[2], 1.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[2], 1.0f, RecipNearClip);

	RwIm2DVertexSetScreenX(&maVertices[3], x1);
	RwIm2DVertexSetScreenY(&maVertices[3], y1);
	RwIm2DVertexSetScreenZ(&maVertices[3], NearScreenZ);
	RwIm2DVertexSetCameraZ(&maVertices[3], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&maVertices[3], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&maVertices[3], c0.r, c0.g, c0.b, c0.a);
	RwIm2DVertexSetU(&maVertices[3], 0.0f, RecipNearClip);
	RwIm2DVertexSetV(&maVertices[3], 1.0f, RecipNearClip);
}

void
CSprite2d::SetVertices(int n, float *positions, float *uvs, const CRGBA &col)
{
	int i;

	for(i = 0; i < n; i++){
		RwIm2DVertexSetScreenX(&maVertices[i], positions[i*2 + 0]);
		RwIm2DVertexSetScreenY(&maVertices[i], positions[i*2 + 1]);
		RwIm2DVertexSetScreenZ(&maVertices[i], NearScreenZ + 0.0001f);
		RwIm2DVertexSetCameraZ(&maVertices[i], NearCamZ);
		RwIm2DVertexSetRecipCameraZ(&maVertices[i], RecipNearClip);
		RwIm2DVertexSetIntRGBA(&maVertices[i], col.r, col.g, col.b, col.a);
		RwIm2DVertexSetU(&maVertices[i], uvs[i*2 + 0], RecipNearClip);
		RwIm2DVertexSetV(&maVertices[i], uvs[i*2 + 1], RecipNearClip);
	}
}

void
CSprite2d::SetMaskVertices(int n, float *positions)
{
	int i;

	for(i = 0; i < n; i++){
		RwIm2DVertexSetScreenX(&maVertices[i], positions[i*2 + 0]);
		RwIm2DVertexSetScreenY(&maVertices[i], positions[i*2 + 1]);
		RwIm2DVertexSetScreenZ(&maVertices[i], NearScreenZ);
		RwIm2DVertexSetCameraZ(&maVertices[i], NearCamZ);
		RwIm2DVertexSetRecipCameraZ(&maVertices[i], RecipNearClip);
		RwIm2DVertexSetIntRGBA(&maVertices[i], 255, 255, 255, 255);	// 0, 0, 0, 0 on PC
	}
}

void
CSprite2d::SetVertices(RwIm2DVertex *verts, const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3,
		float u0, float v0, float u1, float v1, float u3, float v3, float u2, float v2)
{
	RwIm2DVertexSetScreenX(&verts[0], r.left);
	RwIm2DVertexSetScreenY(&verts[0], r.top);
	RwIm2DVertexSetScreenZ(&verts[0], NearScreenZ);
	RwIm2DVertexSetCameraZ(&verts[0], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&verts[0], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&verts[0], c2.r, c2.g, c2.b, c2.a);
	RwIm2DVertexSetU(&verts[0], u0, RecipNearClip);
	RwIm2DVertexSetV(&verts[0], v0, RecipNearClip);

	RwIm2DVertexSetScreenX(&verts[1], r.right);
	RwIm2DVertexSetScreenY(&verts[1], r.top);
	RwIm2DVertexSetScreenZ(&verts[1], NearScreenZ);
	RwIm2DVertexSetCameraZ(&verts[1], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&verts[1], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&verts[1], c3.r, c3.g, c3.b, c3.a);
	RwIm2DVertexSetU(&verts[1], u1, RecipNearClip);
	RwIm2DVertexSetV(&verts[1], v1, RecipNearClip);

	RwIm2DVertexSetScreenX(&verts[2], r.right);
	RwIm2DVertexSetScreenY(&verts[2], r.bottom);
	RwIm2DVertexSetScreenZ(&verts[2], NearScreenZ);
	RwIm2DVertexSetCameraZ(&verts[2], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&verts[2], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&verts[2], c1.r, c1.g, c1.b, c1.a);
	RwIm2DVertexSetU(&verts[2], u2, RecipNearClip);
	RwIm2DVertexSetV(&verts[2], v2, RecipNearClip);

	RwIm2DVertexSetScreenX(&verts[3], r.left);
	RwIm2DVertexSetScreenY(&verts[3], r.bottom);
	RwIm2DVertexSetScreenZ(&verts[3], NearScreenZ);
	RwIm2DVertexSetCameraZ(&verts[3], NearCamZ);
	RwIm2DVertexSetRecipCameraZ(&verts[3], RecipNearClip);
	RwIm2DVertexSetIntRGBA(&verts[3], c0.r, c0.g, c0.b, c0.a);
	RwIm2DVertexSetU(&verts[3], u3, RecipNearClip);
	RwIm2DVertexSetV(&verts[3], v3, RecipNearClip);
}

void
CSprite2d::DrawRect(const CRect &r, const CRGBA &col)
{
	SetVertices(r, col, col, col, col);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEFLAT);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)(col.a != 255));
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
}

void
CSprite2d::DrawRect(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3)
{
	SetVertices(r, c0, c1, c2, c3);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
}

void
CSprite2d::DrawRectXLU(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3)
{
	SetVertices(r, c0, c1, c2, c3);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
}

void
CSprite2d::DrawAnyRect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
		const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3)
{
	SetVertices(x1, y1, x2, y2, x3, y3, x4, y4, c0, c1, c2, c3);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nil);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)(c0.alpha != 255 || c1.alpha != 255 || c2.alpha != 255 || c3.alpha != 255));
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
}

void CSprite2d::Draw2DPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA &color)
{
	SetVertices(x1, y1, x2, y2, x3, y3, x4, y4, color, color, color, color);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, 0);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEFLAT);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)(color.a != 255));
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
}

void
CSprite2d::AddToBuffer(const CRect &r, const CRGBA &c, float u0, float v0, float u1, float v1, float u3, float v3, float u2, float v2)
{
	SetVertices(&TempVertexBuffer.im2d[nextBufferVertex], r, c, c, c, c, u0, v0, u1, v1, u3, v3, u2, v2);
	RwImVertexIndex *pIndexList = &TempBufferRenderIndexList[nextBufferIndex];
	pIndexList[0] = nextBufferVertex;
	pIndexList[1] = nextBufferVertex + 1;
	pIndexList[2] = nextBufferVertex + 2;
	pIndexList[3] = nextBufferVertex + 3;
	pIndexList[4] = nextBufferVertex;
	pIndexList[5] = nextBufferVertex + 2;
	nextBufferIndex += 6;
	nextBufferVertex += 4;
	if (IsVertexBufferFull())
		RenderVertexBuffer();
}

bool
CSprite2d::IsVertexBufferFull()
{
	return (nextBufferVertex > TEMPBUFFERVERTSIZE-128-4 || nextBufferIndex > ARRAY_SIZE(TempBufferRenderIndexList)-6);
}

void
CSprite2d::RenderVertexBuffer()
{
	if (nextBufferVertex > 0) {
		RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
		RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, TempVertexBuffer.im2d, nextBufferVertex, TempBufferRenderIndexList, nextBufferIndex);
		nextBufferVertex = 0;
		nextBufferIndex = 0;
	}
}