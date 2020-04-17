#ifndef LIBRW

#define WITHD3D
#include "common.h"
#ifdef RWLIBS
#include "patcher.h"
#endif

struct MatFXNothing { int pad[5]; int effect; };

struct MatFXBump
{
	RwFrame *bumpFrame;
	RwTexture *bumpedTex;
	RwTexture *bumpTex;
	float negBumpCoefficient;
	int pad;
	int effect;
};

struct MatFXEnv
{
	RwFrame *envFrame;
	RwTexture *envTex;
	float envCoeff;
	int envFBalpha;
	int pad;
	int effect;
};

struct MatFXDual
{
	RwTexture *dualTex;
	RwInt32 srcBlend;
	RwInt32 dstBlend;
};


struct MatFX
{
	union {
		MatFXNothing n;
		MatFXBump b;
		MatFXEnv e;
		MatFXDual d;
	} fx[2];
	int effects;
};

#ifdef RWLIBS
extern "C" {
	extern int MatFXMaterialDataOffset;
	extern int MatFXAtomicDataOffset;
	void _rpMatFXD3D8AtomicMatFXEnvRender(RxD3D8InstanceData* inst, int flags, int sel, RwTexture* texture, RwTexture* envMap);
}
#else
int &MatFXMaterialDataOffset = *(int*)0x66188C;
int &MatFXAtomicDataOffset = *(int*)0x66189C;
#endif

#ifdef PS2_MATFX

void
_rpMatFXD3D8AtomicMatFXDefaultRender(RxD3D8InstanceData *inst, int flags, RwTexture *texture)
{
	if(flags & (rpGEOMETRYTEXTURED|rpGEOMETRYTEXTURED2) && texture)
		RwD3D8SetTexture(texture, 0);
	else
		RwD3D8SetTexture(nil, 0);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)(inst->vertexAlpha || inst->material->color.alpha != 0xFF));
	RwD3D8SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, inst->vertexAlpha != 0);
	RwD3D8SetPixelShader(0);
	RwD3D8SetVertexShader(inst->vertexShader);
	RwD3D8SetStreamSource(0, inst->vertexBuffer, inst->stride);

	if(inst->indexBuffer){
		RwD3D8SetIndices(inst->indexBuffer, inst->baseIndex);
		RwD3D8DrawIndexedPrimitive(inst->primType, 0, inst->numVertices, 0, inst->numIndices);
	}else
		RwD3D8DrawPrimitive(inst->primType, inst->baseIndex, inst->numVertices);
}

// map [-1; -1] -> [0; 1], flip V
static RwMatrix scalenormal = {
	{ 0.5f, 0.0f, 0.0f }, 0,
	{ 0.0f, -0.5f, 0.0f }, 0,
	{ 0.0f, 0.0f, 1.0f }, 0,
	{ 0.5f, 0.5f, 0.0f }, 0,
	
};

// flipped U for PS2
static RwMatrix scalenormal_flipU = {
	{ -0.5f, 0.0f, 0.0f }, 0,
	{ 0.0f, -0.5f, 0.0f }, 0,
	{ 0.0f, 0.0f, 1.0f }, 0,
	{ 0.5f, 0.5f, 0.0f }, 0,
	
};

void
ApplyEnvMapTextureMatrix(RwTexture *tex, int n, RwFrame *frame)
{
	RwD3D8SetTexture(tex, n);
	RwD3D8SetTextureStageState(n, D3DRS_ALPHAREF, 2);
	RwD3D8SetTextureStageState(n, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACENORMAL);
	if(frame){
		RwMatrix *envframemat = RwMatrixCreate();
		RwMatrix *tmpmat = RwMatrixCreate();
		RwMatrix *envmat = RwMatrixCreate();

		RwMatrixInvert(envframemat, RwFrameGetLTM(frame));
		// PS2
		// can this be simplified?
		*tmpmat = *RwFrameGetLTM(RwCameraGetFrame((RwCamera*)RWSRCGLOBAL(curCamera)));
		RwV3dNegate(&tmpmat->right, &tmpmat->right);
		tmpmat->flags = 0;
		tmpmat->pos.x = 0.0f;
		tmpmat->pos.y = 0.0f;
		tmpmat->pos.z = 0.0f;
		RwMatrixMultiply(envmat, tmpmat, envframemat);
		*tmpmat = *envmat;
		// important because envframemat can have a translation that we don't like
		tmpmat->pos.x = 0.0f;
		tmpmat->pos.y = 0.0f;
		tmpmat->pos.z = 0.0f;
		// for some reason we flip in U as well
		RwMatrixMultiply(envmat, tmpmat, &scalenormal_flipU);

		RwD3D8SetTransform(D3DTS_TEXTURE0+n, envmat);

		RwMatrixDestroy(envmat);
		RwMatrixDestroy(tmpmat);
		RwMatrixDestroy(envframemat);
	}else
		RwD3D8SetTransform(D3DTS_TEXTURE0+n, &scalenormal);
}

void
_rpMatFXD3D8AtomicMatFXEnvRender_ps2(RxD3D8InstanceData *inst, int flags, int sel, RwTexture *texture, RwTexture *envMap)
{
	MatFX *matfx = *RWPLUGINOFFSET(MatFX*, inst->material, MatFXMaterialDataOffset);
	MatFXEnv *env = &matfx->fx[sel].e;

	uint8 intens = (uint8)(env->envCoeff*255.0f);

	if(intens == 0 || envMap == nil){
		if(sel == 0)
			_rpMatFXD3D8AtomicMatFXDefaultRender(inst, flags, texture);
		return;
	}

	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)(inst->vertexAlpha || inst->material->color.alpha != 0xFF));
	if(flags & (rpGEOMETRYTEXTURED|rpGEOMETRYTEXTURED2) && texture)
		RwD3D8SetTexture(texture, 0);
	else
		RwD3D8SetTexture(nil, 0);
	RwD3D8SetPixelShader(0);
	RwD3D8SetVertexShader(inst->vertexShader);
	RwD3D8SetStreamSource(0, inst->vertexBuffer, inst->stride);
	RwD3D8SetIndices(inst->indexBuffer, inst->baseIndex);
	if(inst->indexBuffer)
		RwD3D8DrawIndexedPrimitive(inst->primType, 0, inst->numVertices, 0, inst->numIndices);
	else
		RwD3D8DrawPrimitive(inst->primType, inst->baseIndex, inst->numVertices);

	// Effect pass
	
	ApplyEnvMapTextureMatrix(envMap, 0, env->envFrame);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwUInt32 src, dst, lighting, zwrite, fog, fogcol;
	RwRenderStateGet(rwRENDERSTATESRCBLEND, &src);
	RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dst);

	// This is of course not using framebuffer alpha,
	// but if the diffuse texture had no alpha, the result should actually be rather the same
	if(env->envFBalpha)
		RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	else
		RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
	RwD3D8GetRenderState(D3DRS_LIGHTING, &lighting);
	RwD3D8GetRenderState(D3DRS_ZWRITEENABLE, &zwrite);
	RwD3D8GetRenderState(D3DRS_FOGENABLE, &fog);
	RwD3D8SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	if(fog){
		RwD3D8GetRenderState(D3DRS_FOGCOLOR, &fogcol);
		RwD3D8SetRenderState(D3DRS_FOGCOLOR, 0);
	}

	D3DCOLOR texfactor = D3DCOLOR_RGBA(intens, intens, intens, intens);
	RwD3D8SetRenderState(D3DRS_TEXTUREFACTOR, texfactor);
	RwD3D8SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	RwD3D8SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	RwD3D8SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TFACTOR);
	// alpha unused
	//RwD3D8SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//RwD3D8SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	//RwD3D8SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

	if(inst->indexBuffer)
		RwD3D8DrawIndexedPrimitive(inst->primType, 0, inst->numVertices, 0, inst->numIndices);
	else
		RwD3D8DrawPrimitive(inst->primType, inst->baseIndex, inst->numVertices);

	// Reset states

	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)src);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)dst);
	RwD3D8SetRenderState(D3DRS_LIGHTING, lighting);
	RwD3D8SetRenderState(D3DRS_ZWRITEENABLE, zwrite);
	if(fog)
		RwD3D8SetRenderState(D3DRS_FOGCOLOR, fogcol);
	RwD3D8SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	RwD3D8SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	RwD3D8SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
	RwD3D8SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
}

#ifdef RWLIBS
STARTPATCHES
	InjectHook((uintptr)&_rpMatFXD3D8AtomicMatFXEnvRender, _rpMatFXD3D8AtomicMatFXEnvRender_ps2, PATCH_JUMP);
ENDPATCHES
#endif

#endif

#endif
