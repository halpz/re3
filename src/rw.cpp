#include "common.h"
#include "patcher.h"
#include <rwcore.h>
#include <rpworld.h>
#include <rpmatfx.h>

//
 // ADDRESS
//

int gtaversion = -1;

WRAPPER RwTexDictionary *RwTexDictionaryCreate(void) { EAXJMP(0x5A7160); }
WRAPPER RwBool RwTexDictionaryDestroy(RwTexDictionary*) { EAXJMP(0x5A7200); }
static uint32_t RwTexDictionaryFindNamedTexture_A = AddressByVersion<uint32_t>(0x5A74D0, 0, 0, 0x64E060, 0, 0);
WRAPPER RwTexture *RwTexDictionaryFindNamedTexture(RwTexDictionary*, const RwChar*) { VARJMP(RwTexDictionaryFindNamedTexture_A); }
static uint32_t RwTextureRead_A = AddressByVersion<uint32_t>(0x5A7580, 0x5A7840, 0x5A8E00, 0x64E110, 0, 0);
WRAPPER RwTexture *RwTextureRead(const RwChar*, const RwChar*) { VARJMP(RwTextureRead_A); }
static uint32_t RwTexDictionaryGetCurrent_A = AddressByVersion<uint32_t>(0x5A7570, 0x5A7830, 0x5A8DA0, 0x64E100, 0, 0);
WRAPPER RwTexDictionary *RwTexDictionaryGetCurrent(void) { VARJMP(RwTexDictionaryGetCurrent_A); }
static uint32_t RwTexDictionarySetCurrent_A = AddressByVersion<uint32_t>(0x5A7550, 0x5A7810, 0x5A8D80, 0x64E0E0, 0, 0);
WRAPPER RwTexDictionary *RwTexDictionarySetCurrent(RwTexDictionary * dict) { VARJMP(RwTexDictionarySetCurrent_A); }
static uint32_t RwTexDictionaryForAllTextures_A = AddressByVersion<uint32_t>(0, 0, 0, 0x64DE20, 0, 0);
WRAPPER const RwTexDictionary *RwTexDictionaryForAllTextures(const RwTexDictionary*, RwTextureCallBack, void*) { VARJMP(RwTexDictionaryForAllTextures_A); }

static uint32_t RwV3dLength_A = AddressByVersion<uint32_t>(0x5A36A0, 0, 0, 0x647030, 0, 0);
WRAPPER RwReal RwV3dLength(const RwV3d*) { VARJMP(RwV3dLength_A); }
WRAPPER RwV3d *RwV3dTransformPoints(RwV3d*, const RwV3d*, RwInt32, const RwMatrix*) { EAXJMP(0x5A37D0); }

static uint32_t D3D8AtomicDefaultInstanceCallback_A = AddressByVersion<uint32_t>(0x5DB450, 0x5DB710, 0x5EC520, 0x67BAE0, 0, 0);
WRAPPER RwBool D3D8AtomicDefaultInstanceCallback(void*, RxD3D8InstanceData*, RwBool) { VARJMP(D3D8AtomicDefaultInstanceCallback_A); }
static uint32_t D3D8AtomicDefaultReinstanceCallback_A = AddressByVersion<uint32_t>(0x5DBFB0, 0, 0, 0x67C640, 0, 0);
WRAPPER RwBool D3D8AtomicDefaultReinstanceCallback(void*, RwResEntry*, const RpMeshHeader*, RxD3D8AllInOneInstanceCallBack) { VARJMP(D3D8AtomicDefaultReinstanceCallback_A); }

static uint32_t rwD3D8RWGetRasterStage_A = AddressByVersion<uint32_t>(0x5B5390, 0x5B5650, 0x5BA2C0, 0x659840, 0x659890, 0x6587F0);
WRAPPER int rwD3D8RWGetRasterStage(int) { VARJMP(rwD3D8RWGetRasterStage_A); }

static uint32_t RpWorldAddCamera_A = AddressByVersion<uint32_t>(0x5AFB80, 0, 0, 0x654460, 0, 0);
WRAPPER RpWorld *RpWorldAddCamera(RpWorld*, RwCamera*) { VARJMP(RpWorldAddCamera_A); }

static uint32_t RpMaterialRegisterPlugin_A = AddressByVersion<uint32_t>(0x5ADD40, 0, 0, 0x6558C0, 0, 0);
WRAPPER RwInt32 RpMaterialRegisterPlugin(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy) { VARJMP(RpMaterialRegisterPlugin_A); }
WRAPPER RpMaterial *RpMaterialSetTexture(RpMaterial*, RwTexture*) { EAXJMP(0x5ADD10); }

//
 //
//

static uint32_t RwMatrixCreate_A = AddressByVersion<uint32_t>(0x5A3330, 0x5A35F0, 0x5A3FA0, 0x644620, 0x644670, 0x6435D0);
WRAPPER RwMatrix *RwMatrixCreate(void) { VARJMP(RwMatrixCreate_A); }
static uint32_t RwMatrixDestroy_A = AddressByVersion<uint32_t>(0x5A3300, 0x5A35C0, 0x5A3F70, 0x6445F0, 0x644640, 0x6435A0);
WRAPPER RwBool RwMatrixDestroy(RwMatrix*) { VARJMP(RwMatrixDestroy_A); }
static uint32_t RwMatrixMultiply_A = AddressByVersion<uint32_t>(0x5A28F0, 0x5A2BB0, 0x5A2E10, 0x6437C0, 0x643810, 0x642770);
WRAPPER RwMatrix *RwMatrixMultiply(RwMatrix*, const RwMatrix*, const RwMatrix*) { VARJMP(RwMatrixMultiply_A); }
static uint32_t RwMatrixInvert_A = AddressByVersion<uint32_t>(0x5A2C90, 0x5A2F50, 0x5A35A0, 0x643F40, 0x643F90, 0x642EF0);
WRAPPER RwMatrix *RwMatrixInvert(RwMatrix*, const RwMatrix*) { VARJMP(RwMatrixInvert_A); }
static uint32_t RwMatrixUpdate_A = AddressByVersion<uint32_t>(0x5A28E0, 0x5A2BA0, 0x5A2DF0, 0x6437B0, 0x643800, 0x642760);
WRAPPER RwMatrix *RwMatrixUpdate(RwMatrix*) { VARJMP(RwMatrixUpdate_A); }
static uint32_t RwMatrixRotate_A = AddressByVersion<uint32_t>(0x5A2BF0, 0x5A2EB0, 0x5A3510, 0x643EA0, 0x643EF0, 0x642E50);
WRAPPER RwMatrix *RwMatrixRotate(RwMatrix*, const RwV3d*, RwReal, RwOpCombineType) { VARJMP(RwMatrixRotate_A); }
static uint32_t RwMatrixOptimize_A = AddressByVersion<uint32_t>(0x5A2820, 0, 0, 0x6436F0, 0, 0);
WRAPPER RwMatrix *RwMatrixOptimize(RwMatrix *matrix, const RwMatrixTolerance *tolerance) { VARJMP(RwMatrixOptimize_A); }
WRAPPER RwMatrix *RwMatrixTransform(RwMatrix*, const RwMatrix*, RwOpCombineType) { EAXJMP(0x5A31C0); }
WRAPPER RwFrame *RwFrameForAllObjects(RwFrame*, RwObjectCallBack, void*) { EAXJMP(0x5A2340); }

static uint32_t RwFrameCreate_A = AddressByVersion<uint32_t>(0x5A1A00, 0x5A1CC0, 0x5A2270, 0x644AA0, 0x644AF0, 0x643A50);
WRAPPER RwFrame *RwFrameCreate(void) { VARJMP(RwFrameCreate_A); }
static uint32_t RwFrameUpdateObjects_A = AddressByVersion<uint32_t>(0x5A1C60, 0x5A1F20, 0x5A23B4, 0x644D00, 0x644D50, 0x643CB0);
WRAPPER RwFrame *RwFrameUpdateObjects(RwFrame* a1)
{
	if (gtaversion != III_STEAM)
		VARJMP(RwFrameUpdateObjects_A);

	__asm
	{
		mov eax, a1
		jmp RwFrameUpdateObjects_A
	}
}
static uint32_t RwFrameGetLTM_A = AddressByVersion<uint32_t>(0x5A1CE0, 0x5A1FA0, 0x5A2430, 0x644D80, 0x644DD0, 0x643D30);
WRAPPER RwMatrix *RwFrameGetLTM(RwFrame*) { VARJMP(RwFrameGetLTM_A); }
static uint32_t RwFrameTransform_A = AddressByVersion<uint32_t>(0x5A2140, 0x5A2400, 0x5A26E0, 0x6451E0, 0x645230, 0x644190);
WRAPPER RwFrame *RwFrameTransform(RwFrame*, const RwMatrix*, RwOpCombineType) { VARJMP(RwFrameTransform_A); }
WRAPPER RwBool RwFrameDestroy(RwFrame*) { EAXJMP(0x5A1A30); }
WRAPPER RwInt32 RwFrameRegisterPlugin(RwInt32, RwUInt32,RwPluginObjectConstructor,RwPluginObjectDestructor, RwPluginObjectCopy) { EAXJMP(0x5A2380); }
WRAPPER RwFrame *RwFrameForAllChildren(RwFrame*, RwFrameCallBack, void*) { EAXJMP(0x5A1FC0); }
WRAPPER RwFrame *RwFrameAddChild(RwFrame*, RwFrame*) { EAXJMP(0x5A1D00); }
WRAPPER RwFrame *RwFrameRemoveChild(RwFrame*) { EAXJMP(0x5A1ED0); }
WRAPPER RwFrame *RwFrameScale(RwFrame*, const RwV3d*, RwOpCombineType) { EAXJMP(0x5A20A0); }

static uint32_t RwCameraCreate_A = AddressByVersion<uint32_t>(0x5A5360, 0x5A5620, 0x5A74E0, 0x64AB50, 0x64ABA0, 0x649B00);
WRAPPER RwCamera *RwCameraCreate(void) { VARJMP(RwCameraCreate_A); }
static uint32_t RwCameraBeginUpdate_A = AddressByVersion<uint32_t>(0x5A5030, 0x5A52F0, 0x5A7220, 0x64A820, 0x64A870, 0x6497D0);
WRAPPER RwCamera *RwCameraBeginUpdate(RwCamera*) { VARJMP(RwCameraBeginUpdate_A); }
static uint32_t RwCameraEndUpdate_A = AddressByVersion<uint32_t>(0x5A5020, 0x5A52E0, 0x5A7200, 0x64A810, 0x64A860, 0x6497C0);
WRAPPER RwCamera *RwCameraEndUpdate(RwCamera*) { VARJMP(RwCameraEndUpdate_A); }
static uint32_t RwCameraSetNearClipPlane_A = AddressByVersion<uint32_t>(0x5A5070, 0x5A5330, 0x5A7270, 0x64A860, 0x64A8B0, 0x649810);
WRAPPER RwCamera *RwCameraSetNearClipPlane(RwCamera*, RwReal) { VARJMP(RwCameraSetNearClipPlane_A); }
static uint32_t RwCameraSetFarClipPlane_A = AddressByVersion<uint32_t>(0x5A5140, 0x5A5400, 0x5A72A0, 0x64A930, 0x64A980, 0x6498E0);
WRAPPER RwCamera *RwCameraSetFarClipPlane(RwCamera*, RwReal) { VARJMP(RwCameraSetFarClipPlane_A); }
static uint32_t RwCameraSetViewWindow_A = AddressByVersion<uint32_t>(0x5A52B0, 0x5A5570, 0x5A7440, 0x64AAA0, 0x64AAF0, 0x649A50);
WRAPPER RwCamera *RwCameraSetViewWindow(RwCamera*, const RwV2d*) { VARJMP(RwCameraSetViewWindow_A); }
static uint32_t RwCameraClear_A = AddressByVersion<uint32_t>(0x5A51E0, 0x5A54A0, 0x5A7350, 0x64A9D0, 0x64AA20, 0x649980);
WRAPPER RwCamera *RwCameraClear(RwCamera*, RwRGBA*, RwInt32) { VARJMP(RwCameraClear_A); }

static uint32_t RwRasterCreate_A = AddressByVersion<uint32_t>(0x5AD930, 0x5ADBF0, 0x5B0580, 0x655490, 0x6554E0, 0x654440);
WRAPPER RwRaster *RwRasterCreate(RwInt32, RwInt32, RwInt32, RwInt32) { VARJMP(RwRasterCreate_A); }
// ADDRESS
static uint32_t RwRasterDestroy_A = AddressByVersion<uint32_t>(0x5AD780, 0, 0, 0x6552E0, 0, 0);
WRAPPER RwBool RwRasterDestroy(RwRaster*) { VARJMP(RwRasterDestroy_A); }
static uint32_t RwRasterSetFromImage_A = AddressByVersion<uint32_t>(0x5BBF50, 0x5BC210, 0x5C0BF0, 0x6602B0, 0x660300, 0x65F260);
WRAPPER RwRaster *RwRasterSetFromImage(RwRaster*, RwImage*) { VARJMP(RwRasterSetFromImage_A); }
static uint32_t RwRasterPushContext_A = AddressByVersion<uint32_t>(0x5AD7C0, 0x5ADA80, 0x5B03C0, 0x655320, 0x655370, 0x6542D0);
WRAPPER RwRaster *RwRasterPushContext(RwRaster*) { VARJMP(RwRasterPushContext_A); }
static uint32_t RwRasterPopContext_A = AddressByVersion<uint32_t>(0x5AD870, 0x5ADB30, 0x5B0460, 0x6553D0, 0x655420, 0x654380);
WRAPPER RwRaster *RwRasterPopContext(void) { VARJMP(RwRasterPopContext_A); }
static uint32_t RwRasterRenderFast_A = AddressByVersion<uint32_t>(0x5AD710, 0x5AD9D0, 0x5B0800, 0x655270, 0x6552C0, 0x654220);
WRAPPER RwRaster *RwRasterRenderFast(RwRaster*, RwInt32, RwInt32) { VARJMP(RwRasterRenderFast_A); }
//RwRaster *RwRasterRenderScaled(RwRaster *raster, RwRect *rect)
//{
//	((RwGlobals*)RwEngineInst)->stdFunc[rwSTANDARDRASTERRENDERSCALED](raster, rect, 0);
//	return raster;
//}

static uint32_t RwTextureCreate_A = AddressByVersion<uint32_t>(0x5A72D0, 0x5A7590, 0x5A8AC0, 0x64DE60, 0x64DEB0, 0x64CE10);
WRAPPER RwTexture *RwTextureCreate(RwRaster*) { VARJMP(RwTextureCreate_A); }
WRAPPER RwBool RwTextureDestroy(RwTexture*) { EAXJMP(0x5A7330); }

static uint32_t RwRenderStateGet_A = AddressByVersion<uint32_t>(0x5A4410, 0x5A46D0, 0x5A53B0, 0x649BF0, 0x649C40, 0x648BA0);
WRAPPER RwBool RwRenderStateGet(RwRenderState, void*) { VARJMP(RwRenderStateGet_A); }
static uint32_t RwRenderStateSet_A = AddressByVersion<uint32_t>(0x5A43C0, 0x5A4680, 0x5A5360, 0x649BA0, 0x649BF0, 0x648B50);
WRAPPER RwBool RwRenderStateSet(RwRenderState, void*) { VARJMP(RwRenderStateSet_A); }

static uint32_t RwD3D8SetTexture_A = AddressByVersion<uint32_t>(0x5B53A0, 0x5B5660, 0x5BA2D0, 0x659850, 0x6598A0, 0x658800);
WRAPPER RwBool RwD3D8SetTexture(RwTexture*, RwUInt32) { VARJMP(RwD3D8SetTexture_A); }
static uint32_t RwD3D8SetRenderState_A = AddressByVersion<uint32_t>(0x5B3CF0, 0x5B3FB0, 0x5B84B0, 0x6582A0, 0x6582F0, 0x657250);
WRAPPER RwBool RwD3D8SetRenderState(RwUInt32, RwUInt32) { VARJMP(RwD3D8SetRenderState_A); }
static uint32_t RwD3D8GetRenderState_A = AddressByVersion<uint32_t>(0x5B3D40, 0x5B4000, 0x5B8510, 0x6582F0, 0x658340, 0x6572A0);
WRAPPER void RwD3D8GetRenderState(RwUInt32, void*) { VARJMP(RwD3D8GetRenderState_A); }
static uint32_t RwD3D8SetTextureStageState_A = AddressByVersion<uint32_t>(0x5B3D60, 0x5B4020, 0x5B8530, 0x658310, 0x658360, 0x6572C0);
WRAPPER RwBool RwD3D8SetTextureStageState(RwUInt32, RwUInt32, RwUInt32) { VARJMP(RwD3D8SetTextureStageState_A); }
static uint32_t RwD3D8SetVertexShader_A = AddressByVersion<uint32_t>(0x5BAF90, 0x5BB250, 0x5BF440, 0x65F2F0, 0x65F340, 0x65E2A0);
WRAPPER RwBool RwD3D8SetVertexShader(RwUInt32) { VARJMP(RwD3D8SetVertexShader_A); }
static uint32_t RwD3D8SetPixelShader_A = AddressByVersion<uint32_t>(0x5BAFD0, 0x5BB290, 0x5BF4A0, 0x65F330, 0x65F380, 0x65E2E0);
WRAPPER RwBool RwD3D8SetPixelShader(RwUInt32 handle) { VARJMP(RwD3D8SetPixelShader_A); }
static uint32_t RwD3D8SetStreamSource_A = AddressByVersion<uint32_t>(0x5BB010, 0x5BB2D0, 0x5BF500, 0x65F370, 0x65F3C0, 0x65E320);
WRAPPER RwBool RwD3D8SetStreamSource(RwUInt32, void*, RwUInt32) { VARJMP(RwD3D8SetStreamSource_A); }
static uint32_t RwD3D8SetIndices_A = AddressByVersion<uint32_t>(0x5BB060, 0x5BB320, 0x5BF590, 0x65F3C0, 0x65F410, 0x65E370);
WRAPPER RwBool RwD3D8SetIndices(void*, RwUInt32) { VARJMP(RwD3D8SetIndices_A); }
static uint32_t RwD3D8DrawIndexedPrimitive_A = AddressByVersion<uint32_t>(0x5BB0B0, 0x5BB370, 0x5BF610, 0x65F410, 0x65F460, 0x65E3C0);
WRAPPER RwBool RwD3D8DrawIndexedPrimitive(RwUInt32, RwUInt32, RwUInt32, RwUInt32, RwUInt32) { VARJMP(RwD3D8DrawIndexedPrimitive_A); }
static uint32_t RwD3D8DrawPrimitive_A = AddressByVersion<uint32_t>(0x5BB140, 0x5BB400, 0x5BF6C0, 0x65F4A0, 0x65F4F0, 0x65E450);
WRAPPER RwBool RwD3D8DrawPrimitive(RwUInt32, RwUInt32, RwUInt32) { VARJMP(RwD3D8DrawPrimitive_A); }
static uint32_t RwD3D8SetSurfaceProperties_A = AddressByVersion<uint32_t>(0x5BB490, 0x5BB750, 0x5BFB30, 0x65F7F0, 0x65F840, 0x65E7A0);
WRAPPER RwBool RwD3D8SetSurfaceProperties(const RwRGBA*, const RwSurfaceProperties*, RwBool) { VARJMP(RwD3D8SetSurfaceProperties_A); }
static uint32_t RwD3D8SetTransform_A = AddressByVersion<uint32_t>(0x5BB1D0, 0x5BB490, 0x5BF768, 0x65F530, 0x65F580, 0x65E4E0);
WRAPPER RwBool RwD3D8SetTransform(RwUInt32 a1, const void* a2)
{
	if (gtaversion != III_STEAM)
		VARJMP(RwD3D8SetTransform_A);

	__asm
	{
		mov edx, [esp+8]
		mov eax, [esp+4]
		jmp RwD3D8SetTransform_A
	}
}
static uint32_t RwD3D8GetTransform_A = AddressByVersion<uint32_t>(0x5BB310, 0x5BB5D0, 0x5BF930, 0x65F670, 0x65F6C0, 0x65E620);
WRAPPER void RwD3D8GetTransform(RwUInt32, void*) { VARJMP(RwD3D8GetTransform_A); }

//WRAPPER RwBool RwD3D8SetLight(RwInt32, const void*) { EAXJMP(0x65FB20); }
//WRAPPER RwBool RwD3D8EnableLight(RwInt32, RwBool) { EAXJMP(0x65FC10); }

static uint32_t rwD3D8RenderStateIsVertexAlphaEnable_A = AddressByVersion<uint32_t>(0x5B5A50, 0x5B5D10, 0x5BA970, 0x659F60, 0x659FB0, 0x658F10);
WRAPPER RwBool rwD3D8RenderStateIsVertexAlphaEnable(void) { VARJMP(rwD3D8RenderStateIsVertexAlphaEnable_A); };
static uint32_t rwD3D8RenderStateVertexAlphaEnable_A = AddressByVersion<uint32_t>(0x5B57E0, 0x5B5AA0, 0x5BA840, 0x659CF0, 0x659D40, 0x658CA0);
WRAPPER void rwD3D8RenderStateVertexAlphaEnable(RwBool x) { VARJMP(rwD3D8RenderStateVertexAlphaEnable_A); };
static uint32_t RpAtomicGetWorldBoundingSphere_A = AddressByVersion<uint32_t>(0x59E800, 0x59EAC0, 0x59EB20, 0x640710, 0x640760, 0x63F6C0);
WRAPPER const RwSphere *RpAtomicGetWorldBoundingSphere(RpAtomic*) { VARJMP(RpAtomicGetWorldBoundingSphere_A); };
static uint32_t RwD3D8CameraIsSphereFullyInsideFrustum_A = AddressByVersion<uint32_t>(0x5BBC40, 0x5BBF00, 0x5C0450, 0x65FFB0, 0x660000, 0x65EF60);
WRAPPER RwBool RwD3D8CameraIsSphereFullyInsideFrustum(const void*, const void*) { VARJMP(RwD3D8CameraIsSphereFullyInsideFrustum_A); };
static uint32_t RwD3D8CameraIsBBoxFullyInsideFrustum_A = AddressByVersion<uint32_t>(0x5BBCA0, 0x5BBF60, 0x5C04B0, 0x660010, 0x660060, 0x65EFC0);
WRAPPER RwBool RwD3D8CameraIsBBoxFullyInsideFrustum(const void*, const void*) { VARJMP(RwD3D8CameraIsBBoxFullyInsideFrustum_A); };

static uint32_t RtBMPImageRead_A = AddressByVersion<uint32_t>(0x5AFE70, 0x5B0130, 0x5B3390, 0x657870, 0x6578C0, 0x656820);
WRAPPER RwImage *RtBMPImageRead(const RwChar*) { VARJMP(RtBMPImageRead_A); }
static uint32_t RwImageFindRasterFormat_A = AddressByVersion<uint32_t>(0x5BBF80, 0x5BC240, 0x5C0C40, 0x6602E0, 0x660330, 0x65F290);
WRAPPER RwImage *RwImageFindRasterFormat(RwImage*, RwInt32, RwInt32*, RwInt32*, RwInt32*, RwInt32*) { VARJMP(RwImageFindRasterFormat_A); }
static uint32_t RwImageDestroy_A = AddressByVersion<uint32_t>(0x5A9180, 0x5A9440, 0x5AB6A0, 0x6512B0, 0x651300, 0x650260);
WRAPPER RwBool RwImageDestroy(RwImage*) { VARJMP(RwImageDestroy_A); }

// ADDRESS
static uint32_t RwImageCreate_A = AddressByVersion<uint32_t>(0x5A9120, 0, 0, 0x651250, 0, 0);
WRAPPER RwImage *RwImageCreate(RwInt32, RwInt32, RwInt32) { VARJMP(RwImageCreate_A); }
static uint32_t RwImageAllocatePixels_A = AddressByVersion<uint32_t>(0x5A91E0, 0, 0, 0x651310, 0, 0);
WRAPPER RwImage *RwImageAllocatePixels(RwImage *) { VARJMP(RwImageAllocatePixels_A); }
static uint32_t RwStreamOpen_A = AddressByVersion<uint32_t>(0x5A3FE0, 0, 0, 0x6459C0, 0, 0);
WRAPPER RwStream *RwStreamOpen(RwStreamType, RwStreamAccessType, const void*) { VARJMP(RwStreamOpen_A); }
static uint32_t RwStreamClose_A = AddressByVersion<uint32_t>(0x5A3F10, 0, 0, 0x6458F0, 0, 0);
WRAPPER RwBool RwStreamClose(RwStream*, void*) { VARJMP(RwStreamClose_A); }
static uint32_t RwStreamRead_A = AddressByVersion<uint32_t>(0x5A3AD0, 0, 0, 0x6454B0, 0, 0);
WRAPPER RwUInt32 RwStreamRead(RwStream*, void*, RwUInt32) { VARJMP(RwStreamRead_A); }
static uint32_t RwStreamSkip_A = AddressByVersion<uint32_t>(0x5A3DF0, 0, 0, 0x6457D0, 0, 0);
WRAPPER RwStream *RwStreamSkip(RwStream*, RwUInt32) { VARJMP(RwStreamSkip_A); }
static uint32_t RwStreamFindChunk_A = AddressByVersion<uint32_t>(0x5AA540, 0, 0, 0x64FAC0, 0, 0);
WRAPPER RwBool RwStreamFindChunk(RwStream*, RwUInt32, RwUInt32*, RwUInt32*) { VARJMP(RwStreamFindChunk_A); }
static uint32_t RwTexDictionaryStreamRead_A = AddressByVersion<uint32_t>(0x5924A0, 0, 0, 0x61E710, 0, 0);
WRAPPER RwTexDictionary *RwTexDictionaryStreamRead(RwStream*) { VARJMP(RwTexDictionaryStreamRead_A); }
WRAPPER void _rwD3D8TexDictionaryEnableRasterFormatConversion(RwBool enable) { EAXJMP(0x5BE280); }

static uint32_t RpGeometryLock_A = AddressByVersion<uint32_t>(0, 0, 0, 0x64CCD0, 0, 0);
static uint32_t RpGeometryUnlock_A = AddressByVersion<uint32_t>(0, 0, 0, 0x64CD00, 0, 0);
WRAPPER RpGeometry *RpGeometryLock(RpGeometry*, RwInt32) { VARJMP(RpGeometryLock_A); }
WRAPPER RpGeometry *RpGeometryUnlock(RpGeometry*) { VARJMP(RpGeometryUnlock_A); }
WRAPPER RpGeometry *RpGeometryForAllMaterials(RpGeometry*, RpMaterialCallBack, void*) { EAXJMP(0x5ACBF0); }

static uint32_t RwIm2DGetNearScreenZ_A = AddressByVersion<uint32_t>(0x5A43A0, 0x5A4660, 0x5A5340, 0x649B80, 0x649BD0, 0x648B30);
WRAPPER RwReal RwIm2DGetNearScreenZ(void) { VARJMP(RwIm2DGetNearScreenZ_A); }
// ADDRESS
static uint32_t RwIm2DGetFarScreenZ_A = AddressByVersion<uint32_t>(0x5A43B0, 0, 0, 0x649B90, 0, 0);
WRAPPER RwReal RwIm2DGetFarScreenZ(void) { VARJMP(RwIm2DGetFarScreenZ_A); }
WRAPPER RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex *vertices, RwInt32 numVertices) { EAXJMP(0x5A4430); }
static uint32_t RwIm2DRenderIndexedPrimitive_A = AddressByVersion<uint32_t>(0x5A4440, 0x5A4700, 0x5A5440, 0x649C20, 0x649C70, 0x648BD0);
WRAPPER RwBool RwIm2DRenderIndexedPrimitive(RwPrimitiveType, RwIm2DVertex*, RwInt32, RwImVertexIndex*, RwInt32) { VARJMP(RwIm2DRenderIndexedPrimitive_A); }

WRAPPER RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, RwImVertexIndex *indices, RwInt32 numIndices) { EAXJMP(0x5B6820); }
WRAPPER void  *RwIm3DTransform(RwIm3DVertex *pVerts, RwUInt32 numVerts, RwMatrix *ltm, RwUInt32 flags) { EAXJMP(0x5B6720); }
WRAPPER RwBool RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2) { EAXJMP(0x5B6980); }
WRAPPER RwBool RwIm3DEnd(void) { EAXJMP(0x5B67F0); }

static uint32_t _rwObjectHasFrameSetFrame_A = AddressByVersion<uint32_t>(0x5BC950, 0x5BCC10, 0x5C1820, 0x660CC0, 0x660D10, 0x65FC70);
WRAPPER void _rwObjectHasFrameSetFrame(void*, RwFrame*) { VARJMP(_rwObjectHasFrameSetFrame_A); }

static uint32_t RxPipelineCreate_A = AddressByVersion<uint32_t>(0x5C2E00, 0x5C30C0, 0x5C8FC0, 0x668FC0, 0x669010, 0x667F70);
WRAPPER RxPipeline *RxPipelineCreate(void) { VARJMP(RxPipelineCreate_A); }
static uint32_t RxPipelineLock_A = AddressByVersion<uint32_t>(0x5D29F0, 0x5D2CB0, 0x5DDBF0, 0x67AC50, 0x67ACA0, 0x679C00);
WRAPPER RxLockedPipe *RxPipelineLock(RxPipeline*) { VARJMP(RxPipelineLock_A); }
static uint32_t RxLockedPipeUnlock_A = AddressByVersion<uint32_t>(0x5D1FA0, 0x5D2260, 0x5DD0C0, 0x67A200, 0x67A250, 0x6791B0);
WRAPPER RxPipeline *RxLockedPipeUnlock(RxLockedPipe*) { VARJMP(RxLockedPipeUnlock_A); }
static uint32_t RxNodeDefinitionGetD3D8AtomicAllInOne_A = AddressByVersion<uint32_t>(0x5DC500, 0x5DC7C0, 0x5EC470, 0x67CB90, 0x67CBE0, 0x67BB40);
WRAPPER RxNodeDefinition *RxNodeDefinitionGetD3D8AtomicAllInOne(void) { VARJMP(RxNodeDefinitionGetD3D8AtomicAllInOne_A); }
static uint32_t RxLockedPipeAddFragment_A = AddressByVersion<uint32_t>(0x5D2BA0, 0x5D2E60, 0x5DE000, 0x67AE00, 0x67AE50, 0x679DB0);
WRAPPER RxLockedPipe *RxLockedPipeAddFragment(RxLockedPipe*, RwUInt32*, RxNodeDefinition*, ...) { VARJMP(RxLockedPipeAddFragment_A); }
static uint32_t _rxPipelineDestroy_A = AddressByVersion<uint32_t>(0x5C2E70, 0x5C3130, 0x5C9030, 0x669030, 0x669080, 0x667FE0);
WRAPPER void _rxPipelineDestroy(RxPipeline*) { VARJMP(_rxPipelineDestroy_A); }
static uint32_t RxPipelineFindNodeByName_A = AddressByVersion<uint32_t>(0x5D2B10, 0x5D2DD0, 0x5DDF40, 0x67AD70, 0x67ADC0, 0x679D20);
WRAPPER RxPipelineNode *RxPipelineFindNodeByName(RxPipeline*, const RwChar*, RxPipelineNode*, RwInt32*) { VARJMP(RxPipelineFindNodeByName_A); }
static uint32_t RxD3D8AllInOneSetRenderCallBack_A = AddressByVersion<uint32_t>(0x5DFC60, 0x5DFF20, 0x5EE330, 0x678E30, 0x678E80, 0x677DE0);
WRAPPER void RxD3D8AllInOneSetRenderCallBack(RxPipelineNode*, RxD3D8AllInOneRenderCallBack) { VARJMP(RxD3D8AllInOneSetRenderCallBack_A); }
RxD3D8AllInOneRenderCallBack RxD3D8AllInOneGetRenderCallBack(RxPipelineNode *node)
{
	return *(RxD3D8AllInOneRenderCallBack*)((uint8*)node->privateData + 12);
}
void RxD3D8AllInOneSetInstanceCallBack(RxPipelineNode *node, RxD3D8AllInOneInstanceCallBack callback)
{
	*(RxD3D8AllInOneInstanceCallBack*)node->privateData = callback;
}

static uint32_t rxD3D8DefaultRenderCallback_A = AddressByVersion<uint32_t>(0x5DF960, 0x5DFC20, 0x5EE350, 0x678B30, 0x678B80, 0x677AE0);
WRAPPER void rxD3D8DefaultRenderCallback(RwResEntry*, void*, RwUInt8, RwUInt32) { VARJMP(rxD3D8DefaultRenderCallback_A); }
static uint32_t rwD3D8AtomicMatFXRenderCallback_A = AddressByVersion<uint32_t>(0x5D0B80, 0x5D0E40, 0x5D8B20, 0x676460, 0x6764B0, 0x675410);

WRAPPER RpMaterial *RpMatFXMaterialSetEffects(RpMaterial*, RpMatFXMaterialFlags) { EAXJMP(0x5B3780); }
WRAPPER RpMaterial *RpMatFXMaterialSetupEnvMap(RpMaterial*, RwTexture*, RwFrame*, RwBool, RwReal) { EAXJMP(0x5B38D0); }
WRAPPER void rwD3D8AtomicMatFXRenderCallback(RwResEntry*, void*, RwUInt8, RwUInt32) { VARJMP(rwD3D8AtomicMatFXRenderCallback_A); }
WRAPPER RpAtomic *RpMatFXAtomicEnableEffects(RpAtomic*) { EAXJMP(0x5B3750); }

WRAPPER RpAtomic *RpAtomicSetFrame(RpAtomic*, RwFrame*) { EAXJMP(0x5A0600); }
WRAPPER RwBool RpAtomicDestroy(RpAtomic*) { EAXJMP(0x59F020); }
WRAPPER RpAtomic *RpAtomicClone(RpAtomic*) { EAXJMP(0x59F0A0); }
WRAPPER RpAtomic *RpAtomicSetGeometry(RpAtomic*, RpGeometry*, RwUInt32) { EAXJMP(0x59EFA0); }
WRAPPER RwInt32 RpAtomicRegisterPlugin(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy) { EAXJMP(0x5A0510); }
WRAPPER void _rpAtomicResyncInterpolatedSphere(RpAtomic*) { EAXJMP(0x59E6C0); }

WRAPPER RpAtomic *AtomicDefaultRenderCallBack(RpAtomic*) { EAXJMP(0x59E690); }

static uint32_t RpClumpForAllAtomics_A = AddressByVersion<uint32_t>(0x59EDD0, 0x59F090, 0x59EFC0, 0x640D00, 0x640D50, 0x63FCB0);
WRAPPER RpClump *RpClumpForAllAtomics(RpClump*, RpAtomicCallBack, void*) { VARJMP(RpClumpForAllAtomics_A); }
WRAPPER RpClump *RpClumpRender(RpClump *) { EAXJMP(0x59ED80); }
WRAPPER RpClump *RpClumpClone(RpClump *) { EAXJMP(0x59F1B0); }
WRAPPER RwBool RpClumpDestroy(RpClump * clump) { EAXJMP(0x59F500); }
WRAPPER RwInt32 RpClumpRegisterPlugin(RwInt32, RwUInt32, RwPluginObjectConstructor, RwPluginObjectDestructor, RwPluginObjectCopy) { EAXJMP(0x5A0540); }
WRAPPER RpClump *RpClumpRemoveAtomic(RpClump*, RpAtomic*) { EAXJMP(0x59F6B0); }
WRAPPER RpClump *RpClumpAddAtomic(RpClump*, RpAtomic*) { EAXJMP(0x59F680); }

WRAPPER RpLight *RpLightSetColor(RpLight *light, const RwRGBAReal *color) { EAXJMP(0x5BC320); }