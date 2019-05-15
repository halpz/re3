#include "common.h"
#include "patcher.h"
#include "Draw.h"
#include "Camera.h"
#include "Sprite.h"

// Get rid of bullshit windows definitions, we're not running on an 8086
#ifdef far
#undef far
#undef near
#endif

RwIm2DVertex *CSprite2d::maVertices = (RwIm2DVertex*)0x6E9168;
float &CSprite2d::RecipNearClip = *(float*)0x880DB4;

// Arguments:
// 2---3
// |   |
// 0---1
void
CSprite2d::SetVertices(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3, uint32 far)
{
	float screenz, z, recipz;

	if(far){
		screenz = RwIm2DGetFarScreenZ();
		z = RwCameraGetFarClipPlane(Scene.camera);
	}else{
		screenz = RwIm2DGetNearScreenZ();
		z = 1.0f/RecipNearClip;
	}
	recipz = 1.0f/z;

	// This is what we draw:
	// 0---1
	// | / |
	// 3---2
	RwIm2DVertexSetScreenX(&maVertices[0], r.left);
	RwIm2DVertexSetScreenY(&maVertices[0], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[0], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[0], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[0], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[0], c2.r, c2.g, c2.b, c2.a);
	RwIm2DVertexSetU(&maVertices[0], 0.0f, recipz);
	RwIm2DVertexSetV(&maVertices[0], 0.0f, recipz);

	RwIm2DVertexSetScreenX(&maVertices[1], r.right);
	RwIm2DVertexSetScreenY(&maVertices[1], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[1], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[1], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[1], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[1], c3.r, c3.g, c3.b, c3.a);
	RwIm2DVertexSetU(&maVertices[1], 1.0f, recipz);
	RwIm2DVertexSetV(&maVertices[1], 0.0f, recipz);

	RwIm2DVertexSetScreenX(&maVertices[2], r.right);
	RwIm2DVertexSetScreenY(&maVertices[2], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[2], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[2], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[2], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[2], c1.r, c1.g, c1.b, c1.a);
	RwIm2DVertexSetU(&maVertices[2], 1.0f, recipz);
	RwIm2DVertexSetV(&maVertices[2], 1.0f, recipz);

	RwIm2DVertexSetScreenX(&maVertices[3], r.left);
	RwIm2DVertexSetScreenY(&maVertices[3], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[3], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[3], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[3], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[3], c0.r, c0.g, c0.b, c0.a);
	RwIm2DVertexSetU(&maVertices[3], 0.0f, recipz);
	RwIm2DVertexSetV(&maVertices[3], 1.0f, recipz);
}

void
CSprite2d::SetVertices(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3,
	float u0, float v0, float u1, float v1, float u3, float v3, float u2, float v2)
{
	float screenz, z, recipz;

	screenz = RwIm2DGetNearScreenZ();
	z = 1.0f/RecipNearClip;
	recipz = 1.0f/z;

	// This is what we draw:
	// 0---1
	// | / |
	// 3---2
	RwIm2DVertexSetScreenX(&maVertices[0], r.left);
	RwIm2DVertexSetScreenY(&maVertices[0], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[0], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[0], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[0], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[0], c2.r, c2.g, c2.b, c2.a);
	RwIm2DVertexSetU(&maVertices[0], u0, recipz);
	RwIm2DVertexSetV(&maVertices[0], v0, recipz);

	RwIm2DVertexSetScreenX(&maVertices[1], r.right);
	RwIm2DVertexSetScreenY(&maVertices[1], r.bottom);
	RwIm2DVertexSetScreenZ(&maVertices[1], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[1], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[1], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[1], c3.r, c3.g, c3.b, c3.a);
	RwIm2DVertexSetU(&maVertices[1], u1, recipz);
	RwIm2DVertexSetV(&maVertices[1], v1, recipz);

	RwIm2DVertexSetScreenX(&maVertices[2], r.right);
	RwIm2DVertexSetScreenY(&maVertices[2], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[2], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[2], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[2], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[2], c1.r, c1.g, c1.b, c1.a);
	RwIm2DVertexSetU(&maVertices[2], u2, recipz);
	RwIm2DVertexSetV(&maVertices[2], v2, recipz);

	RwIm2DVertexSetScreenX(&maVertices[3], r.left);
	RwIm2DVertexSetScreenY(&maVertices[3], r.top);
	RwIm2DVertexSetScreenZ(&maVertices[3], screenz);
	RwIm2DVertexSetCameraZ(&maVertices[3], z);
	RwIm2DVertexSetRecipCameraZ(&maVertices[3], recipz);
	RwIm2DVertexSetIntRGBA(&maVertices[3], c0.r, c0.g, c0.b, c0.a);
	RwIm2DVertexSetU(&maVertices[3], u3, recipz);
	RwIm2DVertexSetV(&maVertices[3], v3, recipz);
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
CSprite2d::DrawRect(const CRect &r, const CRGBA &col)
{
	SetVertices(r, col, col, col, col, false);
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
	SetVertices(r, c0, c1, c2, c3, false);
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
	SetVertices(r, c0, c1, c2, c3, false);
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



float &CSprite::m_f2DNearScreenZ = *(float*)0x8F1ABC;
float &CSprite::m_f2DFarScreenZ = *(float*)0x8F2C94;
int32 &CSprite::m_bFlushSpriteBufferSwitchZTest = *(int32*)0x8F5FB0;

float 
CSprite::CalcHorizonCoors(void)
{
	CVector p = TheCamera.GetPosition() + CVector(TheCamera.CamFrontXNorm, TheCamera.CamFrontYNorm, 0.0f)*3000.0f;
	p.z = 0.0f;
	p = TheCamera.m_viewMatrix * p;
	return p.y * RsGlobal.maximumHeight / p.z;
}

bool 
CSprite::CalcScreenCoors(const RwV3d &in, RwV3d *out, float *outw, float *outh, bool farclip)
{
	CVector viewvec = TheCamera.m_viewMatrix * *(CVector*)&in;
	*out = *(RwV3d*)&viewvec;
	if(out->z <= CDraw::GetNearClipZ() + 1.0f) return false;
	if(out->z >= CDraw::GetFarClipZ() && farclip) return false;
	float recip = 1.0f/out->z;
	out->x *= RsGlobal.maximumWidth * recip;
	out->y *= RsGlobal.maximumHeight * recip;
	// What is this? size?
	*outw = 70.0f/CDraw::GetFOV();
	*outh = 70.0f/CDraw::GetFOV();
	*outw *= RsGlobal.maximumWidth * recip;
	*outh *= RsGlobal.maximumHeight * recip;
	return true;
}

#define SPRITEBUFFERSIZE 64
static int32 &nSpriteBufferIndex = *(int32*)0x649A80;
static RwIm2DVertex *SpriteBufferVerts = (RwIm2DVertex*)0x649A84;	//[SPRITEBUFFERSIZE*6];
static RwIm2DVertex *verts = (RwIm2DVertex*)0x64C484;	//[4];

void
CSprite::InitSpriteBuffer(void)
{
	m_f2DNearScreenZ = RwIm2DGetNearScreenZ();
	m_f2DFarScreenZ = RwIm2DGetFarScreenZ();
}

void
CSprite::FlushSpriteBuffer(void)
{
	if(nSpriteBufferIndex > 0){
		if(m_bFlushSpriteBufferSwitchZTest){
			RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
			RwIm2DRenderPrimitive(rwPRIMTYPETRILIST, SpriteBufferVerts, nSpriteBufferIndex*6);
			RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
		}else
			RwIm2DRenderPrimitive(rwPRIMTYPETRILIST, SpriteBufferVerts, nSpriteBufferIndex*6);
		nSpriteBufferIndex = 0;
	}
}

void
CSprite::RenderOneXLUSprite(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, uint8 a)
{
	static short indices[] = { 0, 1, 2, 3 };
	// 0---3
	// |   |
	// 1---2
	float xs[4];
	float ys[4];
	float us[4];
	float vs[4];
	int i;

	xs[0] = x-w;	us[0] = 0.0f;
	xs[1] = x-w;	us[1] = 0.0f;
	xs[2] = x+w;	us[2] = 1.0f;
	xs[3] = x+w;	us[3] = 1.0f;

	ys[0] = y-h;	vs[0] = 0.0f;
	ys[1] = y+h;	vs[1] = 1.0f;
	ys[2] = y+h;	vs[2] = 1.0f;
	ys[3] = y-h;	vs[3] = 0.0f;

	// clip
	for(i = 0; i < 4; i++){
		if(xs[i] < 0.0f){
			us[i] = -xs[i] / (2.0f*w);
			xs[i] = 0.0f;
		}
		if(xs[i] > RsGlobal.maximumWidth){
			us[i] = 1.0f - (xs[i]-RsGlobal.maximumWidth) / (2.0f*w);
			xs[i] = RsGlobal.maximumWidth;
		}
		if(ys[i] < 0.0f){
			vs[i] = -ys[i] / (2.0f*h);
			ys[i] = 0.0f;
		}
		if(ys[i] > RsGlobal.maximumHeight){
			vs[i] = 1.0f - (ys[i]-RsGlobal.maximumHeight) / (2.0f*h);
			ys[i] = RsGlobal.maximumHeight;
		}
	}

	// (DrawZ - DrawNear)/(DrawFar - DrawNear) = (SpriteZ-SpriteNear)/(SpriteFar-SpriteNear)
	// So to calculate SpriteZ:
	float screenz = m_f2DNearScreenZ +
		(z-CDraw::GetNearClipZ())*(m_f2DFarScreenZ-m_f2DNearScreenZ)*CDraw::GetFarClipZ() /
		((CDraw::GetFarClipZ()-CDraw::GetNearClipZ())*z);

	for(i = 0; i < 4; i++){
		RwIm2DVertexSetScreenX(&verts[i], xs[i]);
		RwIm2DVertexSetScreenY(&verts[i], ys[i]);
		RwIm2DVertexSetScreenZ(&verts[i], screenz);
		RwIm2DVertexSetCameraZ(&verts[i], z);
		RwIm2DVertexSetRecipCameraZ(&verts[i], recipz);
		RwIm2DVertexSetIntRGBA(&verts[i], r*intens>>8, g*intens>>8, b*intens>>8, a);
		RwIm2DVertexSetU(&verts[i], us[i], recipz);
		RwIm2DVertexSetV(&verts[i], vs[i], recipz);
	}
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, verts, 4);
}

void
CSprite::RenderBufferedOneXLUSprite(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, uint8 a)
{
	m_bFlushSpriteBufferSwitchZTest = 0;

	// 0---3
	// |   |
	// 1---2
	float xs[4];
	float ys[4];
	float us[4];
	float vs[4];
	int i;

	xs[0] = x-w;	us[0] = 0.0f;
	xs[1] = x-w;	us[1] = 0.0f;
	xs[2] = x+w;	us[2] = 1.0f;
	xs[3] = x+w;	us[3] = 1.0f;

	ys[0] = y-h;	vs[0] = 0.0f;
	ys[1] = y+h;	vs[1] = 1.0f;
	ys[2] = y+h;	vs[2] = 1.0f;
	ys[3] = y-h;	vs[3] = 0.0f;

	// clip
	for(i = 0; i < 4; i++){
		if(xs[i] < 0.0f){
			us[i] = -xs[i] / (2.0f*w);
			xs[i] = 0.0f;
		}
		if(xs[i] > RsGlobal.maximumWidth){
			us[i] = 1.0f - (xs[i]-RsGlobal.maximumWidth) / (2.0f*w);
			xs[i] = RsGlobal.maximumWidth;
		}
		if(ys[i] < 0.0f){
			vs[i] = -ys[i] / (2.0f*h);
			ys[i] = 0.0f;
		}
		if(ys[i] > RsGlobal.maximumHeight){
			vs[i] = 1.0f - (ys[i]-RsGlobal.maximumHeight) / (2.0f*h);
			ys[i] = RsGlobal.maximumHeight;
		}
	}

	float screenz = m_f2DNearScreenZ +
		(z-CDraw::GetNearClipZ())*(m_f2DFarScreenZ-m_f2DNearScreenZ)*CDraw::GetFarClipZ() /
		((CDraw::GetFarClipZ()-CDraw::GetNearClipZ())*z);

	RwIm2DVertex *vert = &SpriteBufferVerts[nSpriteBufferIndex*6];
	static int indices[6] = { 0, 1, 2, 3, 0, 2 };
	for(i = 0; i < 6; i++){
		RwIm2DVertexSetScreenX(&vert[i], xs[indices[i]]);
		RwIm2DVertexSetScreenY(&vert[i], ys[indices[i]]);
		RwIm2DVertexSetScreenZ(&vert[i], screenz);
		RwIm2DVertexSetCameraZ(&vert[i], z);
		RwIm2DVertexSetRecipCameraZ(&vert[i], recipz);
		RwIm2DVertexSetIntRGBA(&vert[i], r*intens>>8, g*intens>>8, b*intens>>8, a);
		RwIm2DVertexSetU(&vert[i], us[indices[i]], recipz);
		RwIm2DVertexSetV(&vert[i], vs[indices[i]], recipz);
	}
	nSpriteBufferIndex++;
	if(nSpriteBufferIndex >= SPRITEBUFFERSIZE)
		FlushSpriteBuffer();
}

void
CSprite::RenderBufferedOneXLUSprite_Rotate_Dimension(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, float rotation, uint8 a)
{
	m_bFlushSpriteBufferSwitchZTest = 0;
	// TODO: replace with lookup
	float c = cos(DEGTORAD(rotation));
	float s = sin(DEGTORAD(rotation));

	float xs[4];
	float ys[4];
	float us[4];
	float vs[4];
	int i;

	xs[0] = x - c*w - s*h;	us[0] = 0.0f;
	xs[1] = x - c*w + s*h;	us[1] = 0.0f;
	xs[2] = x + c*w + s*h;	us[2] = 1.0f;
	xs[3] = x + c*w - s*h;	us[3] = 1.0f;

	ys[0] = y - c*h + s*w;	vs[0] = 0.0f;
	ys[1] = y + c*h + s*w;	vs[1] = 1.0f;
	ys[2] = y + c*h - s*w;	vs[2] = 1.0f;
	ys[3] = y - c*h - s*w;	vs[3] = 0.0f;

	// No clipping, just culling
	if(xs[0] < 0.0f && xs[1] < 0.0f && xs[2] < 0.0f && xs[3] < 0.0f) return;
	if(ys[0] < 0.0f && ys[1] < 0.0f && ys[2] < 0.0f && ys[3] < 0.0f) return;
	if(xs[0] > RsGlobal.maximumWidth && xs[1] > RsGlobal.maximumWidth &&
	   xs[2] > RsGlobal.maximumWidth && xs[3] > RsGlobal.maximumWidth) return;
	if(ys[0] > RsGlobal.maximumHeight && ys[1] > RsGlobal.maximumHeight &&
	   ys[2] > RsGlobal.maximumHeight && ys[3] > RsGlobal.maximumHeight) return;

	float screenz = m_f2DNearScreenZ +
		(z-CDraw::GetNearClipZ())*(m_f2DFarScreenZ-m_f2DNearScreenZ)*CDraw::GetFarClipZ() /
		((CDraw::GetFarClipZ()-CDraw::GetNearClipZ())*z);

	RwIm2DVertex *vert = &SpriteBufferVerts[nSpriteBufferIndex*6];
	static int indices[6] = { 0, 1, 2, 3, 0, 2 };
	for(i = 0; i < 6; i++){
		RwIm2DVertexSetScreenX(&vert[i], xs[indices[i]]);
		RwIm2DVertexSetScreenY(&vert[i], ys[indices[i]]);
		RwIm2DVertexSetScreenZ(&vert[i], screenz);
		RwIm2DVertexSetCameraZ(&vert[i], z);
		RwIm2DVertexSetRecipCameraZ(&vert[i], recipz);
		RwIm2DVertexSetIntRGBA(&vert[i], r*intens>>8, g*intens>>8, b*intens>>8, a);
		RwIm2DVertexSetU(&vert[i], us[indices[i]], recipz);
		RwIm2DVertexSetV(&vert[i], vs[indices[i]], recipz);
	}
	nSpriteBufferIndex++;
	if(nSpriteBufferIndex >= SPRITEBUFFERSIZE)
		FlushSpriteBuffer();
}

void
CSprite::RenderBufferedOneXLUSprite_Rotate_Aspect(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, float rotation, uint8 a)
{
	m_bFlushSpriteBufferSwitchZTest = 0;
	float c = cos(DEGTORAD(rotation));
	float s = sin(DEGTORAD(rotation));

	float xs[4];
	float ys[4];
	float us[4];
	float vs[4];
	int i;

	xs[0] = x + w*(-c-s);	us[0] = 0.0f;
	xs[1] = x + w*(-c+s);	us[1] = 0.0f;
	xs[2] = x + w*(+c+s);	us[2] = 1.0f;
	xs[3] = x + w*(+c-s);	us[3] = 1.0f;

	ys[0] = y + h*(-c+s);	vs[0] = 0.0f;
	ys[1] = y + h*(+c+s);	vs[1] = 1.0f;
	ys[2] = y + h*(+c-s);	vs[2] = 1.0f;
	ys[3] = y + h*(-c-s);	vs[3] = 0.0f;

	// No clipping, just culling
	if(xs[0] < 0.0f && xs[1] < 0.0f && xs[2] < 0.0f && xs[3] < 0.0f) return;
	if(ys[0] < 0.0f && ys[1] < 0.0f && ys[2] < 0.0f && ys[3] < 0.0f) return;
	if(xs[0] > RsGlobal.maximumWidth && xs[1] > RsGlobal.maximumWidth &&
	   xs[2] > RsGlobal.maximumWidth && xs[3] > RsGlobal.maximumWidth) return;
	if(ys[0] > RsGlobal.maximumHeight && ys[1] > RsGlobal.maximumHeight &&
	   ys[2] > RsGlobal.maximumHeight && ys[3] > RsGlobal.maximumHeight) return;

	float screenz = m_f2DNearScreenZ +
		(z-CDraw::GetNearClipZ())*(m_f2DFarScreenZ-m_f2DNearScreenZ)*CDraw::GetFarClipZ() /
		((CDraw::GetFarClipZ()-CDraw::GetNearClipZ())*z);

	RwIm2DVertex *vert = &SpriteBufferVerts[nSpriteBufferIndex*6];
	static int indices[6] = { 0, 1, 2, 3, 0, 2 };
	for(i = 0; i < 6; i++){
		RwIm2DVertexSetScreenX(&vert[i], xs[indices[i]]);
		RwIm2DVertexSetScreenY(&vert[i], ys[indices[i]]);
		RwIm2DVertexSetScreenZ(&vert[i], screenz);
		RwIm2DVertexSetCameraZ(&vert[i], z);
		RwIm2DVertexSetRecipCameraZ(&vert[i], recipz);
		RwIm2DVertexSetIntRGBA(&vert[i], r*intens>>8, g*intens>>8, b*intens>>8, a);
		RwIm2DVertexSetU(&vert[i], us[indices[i]], recipz);
		RwIm2DVertexSetV(&vert[i], vs[indices[i]], recipz);
	}
	nSpriteBufferIndex++;
	if(nSpriteBufferIndex >= SPRITEBUFFERSIZE)
		FlushSpriteBuffer();
}

void
CSprite::RenderBufferedOneXLUSprite_Rotate_2Colours(float x, float y, float z, float w, float h, uint8 r1, uint8 g1, uint8 b1, uint8 r2, uint8 g2, uint8 b2, float cx, float cy, float recipz, float rotation, uint8 a)
{
	m_bFlushSpriteBufferSwitchZTest = 0;
	float c = cos(DEGTORAD(rotation));
	float s = sin(DEGTORAD(rotation));

	float xs[4];
	float ys[4];
	float us[4];
	float vs[4];
	float cf[4];
	int i;

	xs[0] = x + w*(-c-s);	us[0] = 0.0f;
	xs[1] = x + w*(-c+s);	us[1] = 0.0f;
	xs[2] = x + w*(+c+s);	us[2] = 1.0f;
	xs[3] = x + w*(+c-s);	us[3] = 1.0f;

	ys[0] = y + h*(-c+s);	vs[0] = 0.0f;
	ys[1] = y + h*(+c+s);	vs[1] = 1.0f;
	ys[2] = y + h*(+c-s);	vs[2] = 1.0f;
	ys[3] = y + h*(-c-s);	vs[3] = 0.0f;

	// No clipping, just culling
	if(xs[0] < 0.0f && xs[1] < 0.0f && xs[2] < 0.0f && xs[3] < 0.0f) return;
	if(ys[0] < 0.0f && ys[1] < 0.0f && ys[2] < 0.0f && ys[3] < 0.0f) return;
	if(xs[0] > RsGlobal.maximumWidth && xs[1] > RsGlobal.maximumWidth &&
	   xs[2] > RsGlobal.maximumWidth && xs[3] > RsGlobal.maximumWidth) return;
	if(ys[0] > RsGlobal.maximumHeight && ys[1] > RsGlobal.maximumHeight &&
	   ys[2] > RsGlobal.maximumHeight && ys[3] > RsGlobal.maximumHeight) return;

	// Colour factors, cx/y is the direction in which colours change from rgb1 to rgb2
	cf[0] = (cx*(-c-s) + cy*(-c+s))*0.5f + 0.5f;
	cf[0] = clamp(cf[0], 0.0f, 1.0f);
	cf[1] = (cx*(-c-s) + cy*(-c+s))*0.5f + 0.5f;
	cf[1] = clamp(cf[1], 0.0f, 1.0f);
	cf[2] = (cx*(-c-s) + cy*(-c+s))*0.5f + 0.5f;
	cf[2] = clamp(cf[2], 0.0f, 1.0f);
	cf[3] = (cx*(-c-s) + cy*(-c+s))*0.5f + 0.5f;
	cf[3] = clamp(cf[3], 0.0f, 1.0f);

	float screenz = m_f2DNearScreenZ +
		(z-CDraw::GetNearClipZ())*(m_f2DFarScreenZ-m_f2DNearScreenZ)*CDraw::GetFarClipZ() /
		((CDraw::GetFarClipZ()-CDraw::GetNearClipZ())*z);

	RwIm2DVertex *vert = &SpriteBufferVerts[nSpriteBufferIndex*6];
	static int indices[6] = { 0, 1, 2, 3, 0, 2 };
	for(i = 0; i < 6; i++){
		RwIm2DVertexSetScreenX(&vert[i], xs[indices[i]]);
		RwIm2DVertexSetScreenY(&vert[i], ys[indices[i]]);
		RwIm2DVertexSetScreenZ(&vert[i], screenz);
		RwIm2DVertexSetCameraZ(&vert[i], z);
		RwIm2DVertexSetRecipCameraZ(&vert[i], recipz);
		RwIm2DVertexSetIntRGBA(&vert[i],
			r1*cf[indices[i]] + r2*(1.0f - cf[indices[i]]),
			g1*cf[indices[i]] + g2*(1.0f - cf[indices[i]]),
			b1*cf[indices[i]] + b2*(1.0f - cf[indices[i]]),
			a);
		RwIm2DVertexSetU(&vert[i], us[indices[i]], recipz);
		RwIm2DVertexSetV(&vert[i], vs[indices[i]], recipz);
	}
	nSpriteBufferIndex++;
	if(nSpriteBufferIndex >= SPRITEBUFFERSIZE)
		FlushSpriteBuffer();
}

STARTPATCHES
	InjectHook(0x51EE90, (void (*)(const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&, uint32))CSprite2d::SetVertices, PATCH_JUMP);
	InjectHook(0x51F220, (void (*)(const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&,
		float, float, float, float, float, float, float, float))CSprite2d::SetVertices, PATCH_JUMP);
	InjectHook(0x51F970, (void (*)(const CRect&, const CRGBA&))CSprite2d::DrawRect, PATCH_JUMP);
	InjectHook(0x51FA00, (void (*)(const CRect&, const CRGBA&, const CRGBA&, const CRGBA&, const CRGBA&))CSprite2d::DrawRect, PATCH_JUMP);
	InjectHook(0x51FA80, CSprite2d::DrawRectXLU, PATCH_JUMP);

	InjectHook(0x51C4A0, CSprite::CalcHorizonCoors, PATCH_JUMP);
	InjectHook(0x51C3A0, CSprite::CalcScreenCoors, PATCH_JUMP);
	InjectHook(0x51C590, CSprite::InitSpriteBuffer, PATCH_JUMP);
	InjectHook(0x51C520, CSprite::FlushSpriteBuffer, PATCH_JUMP);
	InjectHook(0x51C960, CSprite::RenderOneXLUSprite, PATCH_JUMP);
	InjectHook(0x51C5D0, CSprite::RenderBufferedOneXLUSprite, PATCH_JUMP);
	InjectHook(0x51D5B0, CSprite::RenderBufferedOneXLUSprite_Rotate_Dimension, PATCH_JUMP);
	InjectHook(0x51CCD0, CSprite::RenderBufferedOneXLUSprite_Rotate_Aspect, PATCH_JUMP);
	InjectHook(0x51D9E0, CSprite::RenderBufferedOneXLUSprite_Rotate_2Colours, PATCH_JUMP);
ENDPATCHES
