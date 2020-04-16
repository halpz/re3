#ifndef LIBRW
#include "common.h"
#include "patcher.h"
#include "rwcore.h"
#include "rpworld.h"
#include "rpmatfx.h"
#include "rpskin.h"
#include "rphanim.h"
#include "rtbmp.h"

typedef RwV3d *(*rwVectorsMultFn) (RwV3d * pointsOut,
                                   const RwV3d * pointsIn,
                                   RwInt32 numPoints,
                                   const RwMatrix * matrix);

#ifndef RWLIBS
								   
WRAPPER void _rwObjectHasFrameSetFrame(void* object, RwFrame* frame) { EAXJMP(0x5BC950); }
WRAPPER RpAtomic* AtomicDefaultRenderCallBack(RpAtomic* atomic) { EAXJMP(0x59E690); }
WRAPPER void _rpAtomicResyncInterpolatedSphere(RpAtomic* atomic) { EAXJMP(0x59E6C0); }
WRAPPER RwSphere const* RpAtomicGetWorldBoundingSphere(RpAtomic* atomic) { EAXJMP(0x59E800); }
WRAPPER RwInt32 RpClumpGetNumAtomics(RpClump* clump) { EAXJMP(0x59ED50); }
WRAPPER RpClump* RpClumpRender(RpClump* clump) { EAXJMP(0x59ED80); }
WRAPPER RpClump* RpClumpForAllAtomics(RpClump* clump, RpAtomicCallBack callback, void* pData) { EAXJMP(0x59EDD0); }
WRAPPER RpClump* RpClumpForAllCameras(RpClump* clump, RwCameraCallBack callback, void* pData) { EAXJMP(0x59EE10); }
WRAPPER RpClump* RpClumpForAllLights(RpClump* clump, RpLightCallBack callback, void* pData) { EAXJMP(0x59EE60); }
WRAPPER RpAtomic* RpAtomicCreate() { EAXJMP(0x59EEB0); }
WRAPPER RpAtomic* RpAtomicSetGeometry(RpAtomic* atomic, RpGeometry* geometry, RwUInt32 flags) { EAXJMP(0x59EFA0); }
WRAPPER RwBool RpAtomicDestroy(RpAtomic* atomic) { EAXJMP(0x59F020); }
WRAPPER RpAtomic* RpAtomicClone(RpAtomic* atomic) { EAXJMP(0x59F0A0); }
WRAPPER RpClump* RpClumpClone(RpClump* clump) { EAXJMP(0x59F1B0); }
WRAPPER RpClump* RpClumpCreate() { EAXJMP(0x59F490); }
WRAPPER RwBool RpClumpDestroy(RpClump* clump) { EAXJMP(0x59F500); }
WRAPPER RpClump* RpClumpAddAtomic(RpClump* clump, RpAtomic* atomic) { EAXJMP(0x59F680); }
WRAPPER RpClump* RpClumpRemoveAtomic(RpClump* clump, RpAtomic* atomic) { EAXJMP(0x59F6B0); }
WRAPPER RpClump* RpClumpRemoveLight(RpClump* clump, RpLight* light) { EAXJMP(0x59F6E0); }
WRAPPER RpClump* RpClumpStreamRead(RwStream* stream) { EAXJMP(0x59FC50); }
WRAPPER RwInt32 RpAtomicRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5A0510); }
WRAPPER RwInt32 RpClumpRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5A0540); }
WRAPPER RwInt32 RpAtomicRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) { EAXJMP(0x5A0570); }
WRAPPER RwInt32 RpAtomicSetStreamAlwaysCallBack(RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) { EAXJMP(0x5A05A0); }
WRAPPER RwInt32 RpAtomicSetStreamRightsCallBack(RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) { EAXJMP(0x5A05C0); }
WRAPPER RwInt32 RpAtomicGetPluginOffset(RwUInt32 pluginID) { EAXJMP(0x5A05E0); }
WRAPPER RpAtomic* RpAtomicSetFrame(RpAtomic* atomic, RwFrame* frame) { EAXJMP(0x5A0600); }
WRAPPER RwInt32 RwEngineRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor initCB, RwPluginObjectDestructor termCB) { EAXJMP(0x5A0DC0); }
WRAPPER RwInt32 RwEngineGetPluginOffset(RwUInt32 pluginID) { EAXJMP(0x5A0DF0); }
WRAPPER RwInt32 RwEngineGetNumSubSystems() { EAXJMP(0x5A0E10); }
WRAPPER RwSubSystemInfo* RwEngineGetSubSystemInfo(RwSubSystemInfo* subSystemInfo, RwInt32 subSystemIndex) { EAXJMP(0x5A0E40); }
WRAPPER RwInt32 RwEngineGetCurrentSubSystem() { EAXJMP(0x5A0E70); }
WRAPPER RwBool RwEngineSetSubSystem(RwInt32 subSystemIndex) { EAXJMP(0x5A0EA0); }
WRAPPER RwInt32 RwEngineGetNumVideoModes() { EAXJMP(0x5A0ED0); }
WRAPPER RwVideoMode* RwEngineGetVideoModeInfo(RwVideoMode* modeinfo, RwInt32 modeIndex) { EAXJMP(0x5A0F00); }
WRAPPER RwInt32 RwEngineGetCurrentVideoMode() { EAXJMP(0x5A0F30); }
WRAPPER RwBool RwEngineSetVideoMode(RwInt32 modeIndex) { EAXJMP(0x5A0F60); }
WRAPPER RwBool RwEngineStop() { EAXJMP(0x5A0F90); }
WRAPPER RwBool RwEngineStart() { EAXJMP(0x5A0FE0); }
WRAPPER RwBool RwEngineClose() { EAXJMP(0x5A1070); }
WRAPPER RwBool RwEngineOpen(RwEngineOpenParams* initParams) { EAXJMP(0x5A10E0); }
WRAPPER RwBool RwEngineTerm() { EAXJMP(0x5A1290); }
WRAPPER RwBool RwEngineInit(RwMemoryFunctions* memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize) { EAXJMP(0x5A12D0); }
WRAPPER void* _rwFrameOpen(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5A15E0); }
WRAPPER void* _rwFrameClose(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5A1650); }
WRAPPER RwFrame* _rwFrameCloneAndLinkClones(RwFrame* root) { EAXJMP(0x5A1690); }
WRAPPER RwFrame* _rwFramePurgeClone(RwFrame* root) { EAXJMP(0x5A1880); }
WRAPPER RwBool RwFrameDirty(RwFrame const* frame) { EAXJMP(0x5A1930); }
WRAPPER void _rwFrameInit(RwFrame* frame) { EAXJMP(0x5A1950); }
WRAPPER RwFrame* RwFrameCreate() { EAXJMP(0x5A1A00); }
WRAPPER RwBool RwFrameDestroy(RwFrame* frame) { EAXJMP(0x5A1A30); }
WRAPPER RwBool RwFrameDestroyHierarchy(RwFrame* frame) { EAXJMP(0x5A1BF0); }
WRAPPER RwFrame* RwFrameUpdateObjects(RwFrame* frame) { EAXJMP(0x5A1C60); }
WRAPPER RwMatrix* RwFrameGetLTM(RwFrame* frame) { EAXJMP(0x5A1CE0); }
WRAPPER RwFrame* RwFrameAddChild(RwFrame* parent, RwFrame* child) { EAXJMP(0x5A1D00); }
WRAPPER RwFrame* RwFrameRemoveChild(RwFrame* child) { EAXJMP(0x5A1ED0); }
WRAPPER RwFrame* RwFrameForAllChildren(RwFrame* frame, RwFrameCallBack callBack, void* data) { EAXJMP(0x5A1FC0); }
WRAPPER RwFrame* RwFrameTranslate(RwFrame* frame, RwV3d const* v, RwOpCombineType combine) { EAXJMP(0x5A2000); }
WRAPPER RwFrame* RwFrameScale(RwFrame* frame, RwV3d const* v, RwOpCombineType combine) { EAXJMP(0x5A20A0); }
WRAPPER RwFrame* RwFrameTransform(RwFrame* frame, RwMatrix const* m, RwOpCombineType combine) { EAXJMP(0x5A2140); }
WRAPPER RwFrame* RwFrameRotate(RwFrame* frame, RwV3d const* axis, RwReal angle, RwOpCombineType combine) { EAXJMP(0x5A21E0); }
WRAPPER RwFrame* RwFrameSetIdentity(RwFrame* frame) { EAXJMP(0x5A2280); }
WRAPPER RwFrame* RwFrameForAllObjects(RwFrame* frame, RwObjectCallBack callBack, void* data) { EAXJMP(0x5A2340); }
WRAPPER RwInt32 RwFrameRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5A2380); }
WRAPPER RwBool _rwMatrixSetMultFn(rwMatrixMultFn multMat) { EAXJMP(0x5A23B0); }
WRAPPER RwReal _rwMatrixDeterminant(RwMatrix const* matrix) { EAXJMP(0x5A2520); }
WRAPPER RwReal _rwMatrixOrthogonalError(RwMatrix const* matrix) { EAXJMP(0x5A2570); }
WRAPPER RwReal _rwMatrixNormalError(RwMatrix const* matrix) { EAXJMP(0x5A25D0); }
WRAPPER RwReal _rwMatrixIdentityError(RwMatrix const* matrix) { EAXJMP(0x5A2660); }
WRAPPER void* _rwMatrixClose(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5A2730); }
WRAPPER void* _rwMatrixOpen(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5A2770); }
WRAPPER RwMatrix* RwMatrixOptimize(RwMatrix* matrix, RwMatrixTolerance const* tolerance) { EAXJMP(0x5A2820); }
WRAPPER RwMatrix* RwMatrixUpdate(RwMatrix* matrix) { EAXJMP(0x5A28E0); }
WRAPPER RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, RwMatrix const* MatrixIn1, RwMatrix const* matrixIn2) { EAXJMP(0x5A28F0); }
WRAPPER RwMatrix* RwMatrixRotateOneMinusCosineSine(RwMatrix* matrix, RwV3d const* unitAxis, RwReal oneMinusCosine, RwReal sine, RwOpCombineType combineOp) { EAXJMP(0x5A2960); }
WRAPPER RwMatrix* RwMatrixRotate(RwMatrix* matrix, RwV3d const* axis, RwReal angle, RwOpCombineType combineOp) { EAXJMP(0x5A2BF0); }
WRAPPER RwMatrix* RwMatrixInvert(RwMatrix* matrixOut, RwMatrix const* matrixIn) { EAXJMP(0x5A2C90); }
WRAPPER RwMatrix* RwMatrixScale(RwMatrix* matrix, RwV3d const* scale, RwOpCombineType combineOp) { EAXJMP(0x5A2EE0); }
WRAPPER RwMatrix* RwMatrixTranslate(RwMatrix* matrix, RwV3d const* translation, RwOpCombineType combineOp) { EAXJMP(0x5A3070); }
WRAPPER RwMatrix* RwMatrixTransform(RwMatrix* matrix, RwMatrix const* transform, RwOpCombineType combineOp) { EAXJMP(0x5A31C0); }
WRAPPER RwBool RwMatrixDestroy(RwMatrix* mpMat) { EAXJMP(0x5A3300); }
WRAPPER RwMatrix* RwMatrixCreate() { EAXJMP(0x5A3330); }
WRAPPER RwBool _rwVectorSetMultFn(rwVectorMultFn multPoint, rwVectorsMultFn multPoints, rwVectorMultFn multVector, rwVectorsMultFn multVectors) { EAXJMP(0x5A3450); }
WRAPPER RwReal _rwV3dNormalize(RwV3d* out, RwV3d const* in) { EAXJMP(0x5A3600); }
WRAPPER RwReal RwV3dLength(RwV3d const* in) { EAXJMP(0x5A36A0); }
WRAPPER RwReal _rwSqrt(RwReal const num) { EAXJMP(0x5A3710); }
WRAPPER RwReal _rwInvSqrt(RwReal const num) { EAXJMP(0x5A3770); }
WRAPPER RwV3d* RwV3dTransformPoints(RwV3d* pointsOut, RwV3d const* pointsIn, RwInt32 numPoints, RwMatrix const* matrix) { EAXJMP(0x5A37D0); }
WRAPPER RwV3d* RwV3dTransformVectors(RwV3d* vectorsOut, RwV3d const* vectorsIn, RwInt32 numPoints, RwMatrix const* matrix) { EAXJMP(0x5A37E0); }
WRAPPER void* _rwVectorClose(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5A37F0); }
WRAPPER void* _rwVectorOpen(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5A3860); }
WRAPPER RwUInt32 RwStreamRead(RwStream* stream, void* buffer, RwUInt32 length) { EAXJMP(0x5A3AD0); }
WRAPPER RwStream* RwStreamWrite(RwStream* stream, void const* buffer, RwUInt32 length) { EAXJMP(0x5A3C30); }
WRAPPER RwStream* RwStreamSkip(RwStream* stream, RwUInt32 offset) { EAXJMP(0x5A3DF0); }
WRAPPER RwBool RwStreamClose(RwStream* stream, void* pData) { EAXJMP(0x5A3F10); }
WRAPPER RwStream* RwStreamOpen(RwStreamType type, RwStreamAccessType accessType, void const* pData) { EAXJMP(0x5A3FE0); }
WRAPPER RwReal RwIm2DGetNearScreenZ() { EAXJMP(0x5A43A0); }
WRAPPER RwReal RwIm2DGetFarScreenZ() { EAXJMP(0x5A43B0); }
WRAPPER RwBool RwRenderStateSet(RwRenderState state, void* value) { EAXJMP(0x5A43C0); }
WRAPPER RwBool RwRenderStateGet(RwRenderState state, void* value) { EAXJMP(0x5A4410); }
WRAPPER RwBool RwIm2DRenderLine(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2) { EAXJMP(0x5A4420); }
WRAPPER RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices) { EAXJMP(0x5A4430); }
WRAPPER RwBool RwIm2DRenderIndexedPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices, RwImVertexIndex* indices, RwInt32 numIndices) { EAXJMP(0x5A4440); }
WRAPPER RwCamera* RwCameraEndUpdate(RwCamera* camera) { EAXJMP(0x5A5020); }
WRAPPER RwCamera* RwCameraBeginUpdate(RwCamera* camera) { EAXJMP(0x5A5030); }
WRAPPER RwCamera* RwCameraSetViewOffset(RwCamera* camera, RwV2d const* offset) { EAXJMP(0x5A5040); }
WRAPPER RwCamera* RwCameraSetNearClipPlane(RwCamera* camera, RwReal nearClip) { EAXJMP(0x5A5070); }
WRAPPER RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farClip) { EAXJMP(0x5A5140); }
WRAPPER RwFrustumTestResult RwCameraFrustumTestSphere(RwCamera const* camera, RwSphere const* sphere) { EAXJMP(0x5A5170); }
WRAPPER RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colour, RwInt32 clearMode) { EAXJMP(0x5A51E0); }
WRAPPER RwCamera* RwCameraShowRaster(RwCamera* camera, void* pDev, RwUInt32 flags) { EAXJMP(0x5A5210); }
WRAPPER RwCamera* RwCameraSetProjection(RwCamera* camera, RwCameraProjection projection) { EAXJMP(0x5A5240); }
WRAPPER RwCamera* RwCameraSetViewWindow(RwCamera* camera, RwV2d const* viewWindow) { EAXJMP(0x5A52B0); }
WRAPPER RwInt32 RwCameraRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5A52F0); }
WRAPPER RwBool RwCameraDestroy(RwCamera* camera) { EAXJMP(0x5A5320); }
WRAPPER RwCamera* RwCameraCreate() { EAXJMP(0x5A5360); }
WRAPPER RwBool RwTextureSetMipmapping(RwBool enable) { EAXJMP(0x5A7100); }
WRAPPER RwBool RwTextureGetMipmapping() { EAXJMP(0x5A7120); }
WRAPPER RwBool RwTextureSetAutoMipmapping(RwBool enable) { EAXJMP(0x5A7130); }
WRAPPER RwBool RwTextureGetAutoMipmapping() { EAXJMP(0x5A7150); }
WRAPPER RwTexDictionary* RwTexDictionaryCreate() { EAXJMP(0x5A7160); }
WRAPPER RwBool RwTexDictionaryDestroy(RwTexDictionary* dict) { EAXJMP(0x5A7200); }
WRAPPER RwTexDictionary const* RwTexDictionaryForAllTextures(RwTexDictionary const* dict, RwTextureCallBack fpCallBack, void* pData) { EAXJMP(0x5A7290); }
WRAPPER RwTexture* RwTextureCreate(RwRaster* raster) { EAXJMP(0x5A72D0); }
WRAPPER RwBool RwTextureDestroy(RwTexture* texture) { EAXJMP(0x5A7330); }
WRAPPER RwTexture* RwTextureSetName(RwTexture* texture, RwChar const* name) { EAXJMP(0x5A73B0); }
WRAPPER RwTexture* RwTextureSetMaskName(RwTexture* texture, RwChar const* maskName) { EAXJMP(0x5A7420); }
WRAPPER RwTexture* RwTexDictionaryAddTexture(RwTexDictionary* dict, RwTexture* texture) { EAXJMP(0x5A7490); }
WRAPPER RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* dict, RwChar const* name) { EAXJMP(0x5A74D0); }
WRAPPER RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* dict) { EAXJMP(0x5A7550); }
WRAPPER RwTexDictionary* RwTexDictionaryGetCurrent() { EAXJMP(0x5A7570); }
WRAPPER RwTexture* RwTextureRead(RwChar const* name, RwChar const* maskName) { EAXJMP(0x5A7580); }
WRAPPER RwBool RwTextureRasterGenerateMipmaps(RwRaster* raster, RwImage* image) { EAXJMP(0x5A7780); }
WRAPPER RwImage* RwImageCreate(RwInt32 width, RwInt32 height, RwInt32 depth) { EAXJMP(0x5A9120); }
WRAPPER RwBool RwImageDestroy(RwImage* image) { EAXJMP(0x5A9180); }
WRAPPER RwImage* RwImageAllocatePixels(RwImage* image) { EAXJMP(0x5A91E0); }
WRAPPER RwImage* RwImageFreePixels(RwImage* image) { EAXJMP(0x5A92A0); }
WRAPPER RwImage* RwImageMakeMask(RwImage* image) { EAXJMP(0x5A92D0); }
WRAPPER RwImage* RwImageApplyMask(RwImage* image, RwImage const* mask) { EAXJMP(0x5A93A0); }
WRAPPER RwChar const* RwImageSetPath(RwChar const* path) { EAXJMP(0x5A9750); }
WRAPPER RwImage* RwImageRead(RwChar const* imageName) { EAXJMP(0x5A9810); }
WRAPPER RwChar const* RwImageFindFileType(RwChar const* imageName) { EAXJMP(0x5A9B40); }
WRAPPER RwImage* RwImageReadMaskedImage(RwChar const* imageName, RwChar const* maskname) { EAXJMP(0x5A9C10); }
WRAPPER RwImage* RwImageCopy(RwImage* destImage, RwImage const* sourceImage) { EAXJMP(0x5A9F50); }
WRAPPER RwImage* RwImageGammaCorrect(RwImage* image) { EAXJMP(0x5AA130); }
WRAPPER RwBool RwImageSetGamma(RwReal gammaValue) { EAXJMP(0x5AA2C0); }
WRAPPER RwStream* _rwStreamWriteVersionedChunkHeader(RwStream* stream, RwInt32 type, RwInt32 size, RwUInt32 version, RwUInt32 buildNum) { EAXJMP(0x5AA4E0); }
WRAPPER RwBool RwStreamFindChunk(RwStream* stream, RwUInt32 type, RwUInt32* lengthOut, RwUInt32* versionOut) { EAXJMP(0x5AA540); }
WRAPPER void* RwMemLittleEndian32(void* mem, RwUInt32 size) { EAXJMP(0x5AA640); }
WRAPPER void* RwMemNative32(void* mem, RwUInt32 size) { EAXJMP(0x5AA650); }
WRAPPER void* RwMemFloat32ToReal(void* mem, RwUInt32 size) { EAXJMP(0x5AA660); }
WRAPPER RwStream* RwStreamWriteReal(RwStream* stream, RwReal const* reals, RwUInt32 numBytes) { EAXJMP(0x5AA680); }
WRAPPER RwStream* RwStreamWriteInt32(RwStream* stream, RwInt32 const* ints, RwUInt32 numBytes) { EAXJMP(0x5AA720); }
WRAPPER RwStream* RwStreamReadReal(RwStream* stream, RwReal* reals, RwUInt32 numBytes) { EAXJMP(0x5AA740); }
WRAPPER RwStream* RwStreamReadInt32(RwStream* stream, RwInt32* ints, RwUInt32 numBytes) { EAXJMP(0x5AA7B0); }
WRAPPER RwUInt32 RwTextureStreamGetSize(RwTexture const* texture) { EAXJMP(0x5AA800); }
WRAPPER RwTexture const* RwTextureStreamWrite(RwTexture const* texture, RwStream* stream) { EAXJMP(0x5AA870); }
WRAPPER RwTexture* RwTextureStreamRead(RwStream* stream) { EAXJMP(0x5AAA40); }
WRAPPER RwTexDictionary const* RwTexDictionaryStreamWrite(RwTexDictionary const* texDict, RwStream* stream) { EAXJMP(0x5AB020); }
WRAPPER RpMorphTarget const* RpMorphTargetCalcBoundingSphere(RpMorphTarget const* morphTarget, RwSphere* boundingSphere) { EAXJMP(0x5AC890); }
WRAPPER RwInt32 RpGeometryAddMorphTargets(RpGeometry* geometry, RwInt32 mtcount) { EAXJMP(0x5AC9A0); }
WRAPPER RpGeometry const* RpGeometryTriangleSetVertexIndices(RpGeometry const* geometry, RpTriangle* triangle, RwUInt16 vert1, RwUInt16 vert2, RwUInt16 vert3) { EAXJMP(0x5ACB60); }
WRAPPER RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* geometry, RpTriangle* triangle, RpMaterial* material) { EAXJMP(0x5ACB90); }
WRAPPER RpGeometry* RpGeometryForAllMaterials(RpGeometry* geometry, RpMaterialCallBack fpCallBack, void* pData) { EAXJMP(0x5ACBF0); }
WRAPPER RpGeometry* RpGeometryLock(RpGeometry* geometry, RwInt32 lockMode) { EAXJMP(0x5ACC30); }
WRAPPER RpGeometry* RpGeometryUnlock(RpGeometry* geometry) { EAXJMP(0x5ACC60); }
WRAPPER RpGeometry* RpGeometryCreate(RwInt32 numVert, RwInt32 numTriangles, RwUInt32 format) { EAXJMP(0x5ACD10); }
WRAPPER RpGeometry* _rpGeometryAddRef(RpGeometry* geometry) { EAXJMP(0x5ACF40); }
WRAPPER RwBool RpGeometryDestroy(RpGeometry* geometry) { EAXJMP(0x5ACF50); }
WRAPPER RwInt32 RpGeometryRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5ACFF0); }
WRAPPER RwInt32 RpGeometryRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) { EAXJMP(0x5AD020); }
WRAPPER RpGeometry* RpGeometryStreamRead(RwStream* stream) { EAXJMP(0x5AD050); }
WRAPPER RwRaster* RwRasterGetCurrentContext() { EAXJMP(0x5AD6D0); }
WRAPPER RwRaster* RwRasterUnlock(RwRaster* raster) { EAXJMP(0x5AD6F0); }
WRAPPER RwRaster* RwRasterRenderFast(RwRaster* raster, RwInt32 x, RwInt32 y) { EAXJMP(0x5AD710); }
WRAPPER RwRaster* RwRasterUnlockPalette(RwRaster* raster) { EAXJMP(0x5AD750); }
WRAPPER RwBool RwRasterDestroy(RwRaster* raster) { EAXJMP(0x5AD780); }
WRAPPER RwRaster* RwRasterPushContext(RwRaster* raster) { EAXJMP(0x5AD7C0); }
WRAPPER RwInt32 RwRasterRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5AD810); }
WRAPPER RwUInt8* RwRasterLockPalette(RwRaster* raster, RwInt32 lockMode) { EAXJMP(0x5AD840); }
WRAPPER RwRaster* RwRasterPopContext() { EAXJMP(0x5AD870); }
WRAPPER RwInt32 RwRasterGetNumLevels(RwRaster* raster) { EAXJMP(0x5AD8C0); }
WRAPPER RwRaster* RwRasterShowRaster(RwRaster* raster, void* dev, RwUInt32 flags) { EAXJMP(0x5AD900); }
WRAPPER RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags) { EAXJMP(0x5AD930); }
WRAPPER RwUInt8* RwRasterLock(RwRaster* raster, RwUInt8 level, RwInt32 lockMode) { EAXJMP(0x5AD9D0); }
WRAPPER RpMaterial* RpMaterialCreate() { EAXJMP(0x5ADC30); }
WRAPPER RwBool RpMaterialDestroy(RpMaterial* material) { EAXJMP(0x5ADCB0); }
WRAPPER RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture) { EAXJMP(0x5ADD10); }
WRAPPER RwInt32 RpMaterialRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5ADD40); }
WRAPPER RwInt32 RpMaterialRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) { EAXJMP(0x5ADD70); }
WRAPPER RpMaterial* RpMaterialStreamRead(RwStream* stream) { EAXJMP(0x5ADDA0); }
WRAPPER RpWorldSector* _rpSectorDefaultRenderCallBack(RpWorldSector* sector) { EAXJMP(0x5AE0B0); }
WRAPPER RwBool _rpWorldForAllGlobalLights(RpLightCallBack callBack, void* pData) { EAXJMP(0x5AE100); }
WRAPPER RpWorldSector* _rpWorldSectorForAllLocalLights(RpWorldSector* sector, RpLightCallBack callBack, void* pData) { EAXJMP(0x5AE150); }
WRAPPER RpWorld* RpWorldUnlock(RpWorld* world) { EAXJMP(0x5AE190); }
WRAPPER RpWorld* RpWorldSectorGetWorld(RpWorldSector const* sector) { EAXJMP(0x5AE2B0); }
WRAPPER RwBool RpWorldDestroy(RpWorld* world) { EAXJMP(0x5AE340); }
WRAPPER RpWorld* RpWorldCreate(RwBBox* boundingBox) { EAXJMP(0x5AE6A0); }
WRAPPER RwInt32 RpWorldRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5AEA40); }
WRAPPER RwInt32 RpWorldRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) { EAXJMP(0x5AEA70); }
WRAPPER RwBool RpWorldPluginAttach() { EAXJMP(0x5AEAA0); }
WRAPPER RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera) { EAXJMP(0x5AFB80); }
WRAPPER RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera) { EAXJMP(0x5AFBB0); }
WRAPPER RpWorld* RpAtomicGetWorld(RpAtomic const* atomic) { EAXJMP(0x5AFC10); }
WRAPPER RpWorld* RpWorldAddClump(RpWorld* world, RpClump* clump) { EAXJMP(0x5AFC20); }
WRAPPER RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light) { EAXJMP(0x5AFDA0); }
WRAPPER RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light) { EAXJMP(0x5AFDF0); }
WRAPPER RwImage* RtBMPImageRead(RwChar const* imageName) { EAXJMP(0x5AFE70); }
WRAPPER RwBool RpSkinPluginAttach() { EAXJMP(0x5B07D0); }
WRAPPER RpAtomic* RpSkinAtomicSetHAnimHierarchy(RpAtomic* atomic, RpHAnimHierarchy* hierarchy) { EAXJMP(0x5B1050); }
WRAPPER RpHAnimHierarchy* RpSkinAtomicGetHAnimHierarchy(RpAtomic const* atomic) { EAXJMP(0x5B1070); }
WRAPPER RpSkin* RpSkinGeometryGetSkin(RpGeometry* geometry) { EAXJMP(0x5B1080); }
WRAPPER RpGeometry* RpSkinGeometrySetSkin(RpGeometry* geometry, RpSkin* skin) { EAXJMP(0x5B1090); }
WRAPPER RwMatrix const* RpSkinGetSkinToBoneMatrices(RpSkin* skin) { EAXJMP(0x5B10D0); }
WRAPPER RpHAnimHierarchy* RpHAnimHierarchyCreate(RwInt32 numNodes, RwUInt32* nodeFlags, RwInt32* nodeIDs, RpHAnimHierarchyFlag flags, RwInt32 maxKeyFrameSize) { EAXJMP(0x5B10E0); }
WRAPPER RpHAnimHierarchy* RpHAnimFrameGetHierarchy(RwFrame* frame) { EAXJMP(0x5B11F0); }
WRAPPER RwBool RpHAnimHierarchySetCurrentAnim(RpHAnimHierarchy* hierarchy, RpHAnimAnimation* anim) { EAXJMP(0x5B1200); }
WRAPPER RwBool RpHAnimHierarchySubAnimTime(RpHAnimHierarchy* hierarchy, RwReal time) { EAXJMP(0x5B12B0); }
WRAPPER RwBool RpHAnimHierarchyAddAnimTime(RpHAnimHierarchy* hierarchy, RwReal time) { EAXJMP(0x5B1480); }
WRAPPER RwBool RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy* hierarchy) { EAXJMP(0x5B1780); }
WRAPPER RpHAnimAnimation* RpHAnimAnimationStreamRead(RwStream* stream) { EAXJMP(0x5B1C10); }
WRAPPER RwBool RpHAnimPluginAttach() { EAXJMP(0x5B1D50); }
WRAPPER RwBool RpMatFXPluginAttach() { EAXJMP(0x5B2640); }
WRAPPER RpAtomic* RpMatFXAtomicEnableEffects(RpAtomic* atomic) { EAXJMP(0x5B3750); }
WRAPPER RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* material, RpMatFXMaterialFlags flags) { EAXJMP(0x5B3780); }
WRAPPER RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* material, RwTexture* texture, RwFrame* frame, RwBool useFrameBufferAlpha, RwReal coef) { EAXJMP(0x5B38D0); }
WRAPPER RpMaterial* RpMatFXMaterialSetBumpMapTexture(RpMaterial* material, RwTexture* texture) { EAXJMP(0x5B3A40); }
WRAPPER RwBool RwD3D8SetRenderState(RwUInt32 state, RwUInt32 value) { EAXJMP(0x5B3CF0); }
WRAPPER void RwD3D8GetRenderState(RwUInt32 state, void* value) { EAXJMP(0x5B3D40); }
WRAPPER RwBool RwD3D8SetTextureStageState(RwUInt32 stage, RwUInt32 type, RwUInt32 value) { EAXJMP(0x5B3D60); }
WRAPPER RwBool RwD3D8SetTexture(RwTexture* texture, RwUInt32 stage) { EAXJMP(0x5B53A0); }
WRAPPER void* RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags) { EAXJMP(0x5B6720); }
WRAPPER RwBool RwIm3DEnd() { EAXJMP(0x5B67F0); }
WRAPPER RwBool RwIm3DRenderIndexedPrimitive(RwPrimitiveType primType, RwImVertexIndex* indices, RwInt32 numIndices) { EAXJMP(0x5B6820); }
WRAPPER RwBool RwIm3DRenderLine(RwInt32 vert1, RwInt32 vert2) { EAXJMP(0x5B6980); }
WRAPPER RxPipeline* RwIm3DSetTransformPipeline(RxPipeline* pipeline) { EAXJMP(0x5B6A50); }
WRAPPER RxPipeline* RwIm3DSetRenderPipeline(RxPipeline* pipeline, RwPrimitiveType primType) { EAXJMP(0x5B6AC0); }
WRAPPER void RwD3D8EngineSetRefreshRate(RwUInt32 refreshRate) { EAXJMP(0x5B95D0); }
WRAPPER RwBool RwD3D8CameraAttachWindow(void* camera, void* hwnd) { EAXJMP(0x5B9640); }
WRAPPER RwBool RwD3D8DeviceSupportsDXTTexture() { EAXJMP(0x5BAEB0); }
WRAPPER RwBool RwD3D8SetVertexShader(RwUInt32 handle) { EAXJMP(0x5BAF90); }
WRAPPER RwBool RwD3D8SetPixelShader(RwUInt32 handle) { EAXJMP(0x5BAFD0); }
WRAPPER RwBool RwD3D8SetStreamSource(RwUInt32 streamNumber, void* streamData, RwUInt32 stride) { EAXJMP(0x5BB010); }
WRAPPER RwBool RwD3D8SetIndices(void* indexData, RwUInt32 baseVertexIndex) { EAXJMP(0x5BB060); }
WRAPPER RwBool RwD3D8DrawIndexedPrimitive(RwUInt32 primitiveType, RwUInt32 minIndex, RwUInt32 numVertices, RwUInt32 startIndex, RwUInt32 numIndices) { EAXJMP(0x5BB0B0); }
WRAPPER RwBool RwD3D8DrawPrimitive(RwUInt32 primitiveType, RwUInt32 startVertex, RwUInt32 numVertices) { EAXJMP(0x5BB140); }
WRAPPER RwBool RwD3D8SetTransform(RwUInt32 state, void const* matrix) { EAXJMP(0x5BB1D0); }
WRAPPER void RwD3D8GetTransform(RwUInt32 state, void* matrix) { EAXJMP(0x5BB310); }
WRAPPER RwBool RwD3D8SetTransformWorld(RwMatrix const* matrix) { EAXJMP(0x5BB340); }
WRAPPER RwBool RwD3D8SetSurfaceProperties(RwRGBA const* color, RwSurfaceProperties const* surfaceProps, RwBool modulate) { EAXJMP(0x5BB490); }
WRAPPER RwBool RwD3D8SetLight(RwInt32 index, void const* light) { EAXJMP(0x5BB7A0); }
WRAPPER RwBool RwD3D8EnableLight(RwInt32 index, RwBool enable) { EAXJMP(0x5BB890); }
WRAPPER RwBool RwD3D8DynamicVertexBufferCreate(RwUInt32 fvf, RwUInt32 size, void** vertexBuffer) { EAXJMP(0x5BB9F0); }
WRAPPER void RwD3D8DynamicVertexBufferDestroy(void* vertexBuffer) { EAXJMP(0x5BBAE0); }
WRAPPER RwBool RwD3D8IndexBufferCreate(RwUInt32 numIndices, void** indexBuffer) { EAXJMP(0x5BBB10); }
WRAPPER RwBool RwD3D8CreatePixelShader(RwUInt32 const* function, RwUInt32* handle) { EAXJMP(0x5BBB40); }
WRAPPER void RwD3D8DeletePixelShader(RwUInt32 handle) { EAXJMP(0x5BBB90); }
WRAPPER RwBool RwD3D8SetPixelShaderConstant(RwUInt32 registerAddress, void const* antData, RwUInt32 antCount) { EAXJMP(0x5BBC00); }
WRAPPER void const* RwD3D8GetCaps() { EAXJMP(0x5BBC30); }
WRAPPER RwBool RwD3D8CameraIsSphereFullyInsideFrustum(void const* camera, void const* sphere) { EAXJMP(0x5BBC40); }
WRAPPER RwBool RwD3D8CameraIsBBoxFullyInsideFrustum(void const* camera, void const* boundingBox) { EAXJMP(0x5BBCA0); }
WRAPPER RwBool RwD3D8DynamicVertexBufferLock(RwUInt32 vertexSize, RwUInt32 numVertex, void** vertexBufferOut, void** vertexDataOut, RwUInt32* baseIndexOut) { EAXJMP(0x5BBD30); }
WRAPPER RwBool RwD3D8DynamicVertexBufferUnlock(void* vertexBuffer) { EAXJMP(0x5BBEB0); }
WRAPPER RwBool _rwIntelSSEsupported() { EAXJMP(0x5BBED0); }
WRAPPER RwImage* RwImageSetFromRaster(RwImage* image, RwRaster* raster) { EAXJMP(0x5BBF10); }
WRAPPER RwRaster* RwRasterSetFromImage(RwRaster* raster, RwImage* image) { EAXJMP(0x5BBF50); }
WRAPPER RwImage* RwImageFindRasterFormat(RwImage* ipImage, RwInt32 nRasterType, RwInt32* npWidth, RwInt32* npHeight, RwInt32* npDepth, RwInt32* npFormat) { EAXJMP(0x5BBF80); }
WRAPPER RwInt32 RwFrameRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) { EAXJMP(0x5BBFF0); }
WRAPPER rwFrameList* _rwFrameListDeinitialize(rwFrameList* frameList) { EAXJMP(0x5BC020); }
WRAPPER rwFrameList* _rwFrameListStreamRead(RwStream* stream, rwFrameList* fl) { EAXJMP(0x5BC050); }
WRAPPER RpLight* RpLightSetRadius(RpLight* light, RwReal radius) { EAXJMP(0x5BC300); }
WRAPPER RpLight* RpLightSetColor(RpLight* light, RwRGBAReal const* color) { EAXJMP(0x5BC320); }
WRAPPER RwReal RpLightGetConeAngle(RpLight const* light) { EAXJMP(0x5BC370); }
WRAPPER RwInt32 RpLightRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5BC5B0); }
WRAPPER RpLight* RpLightStreamRead(RwStream* stream) { EAXJMP(0x5BC5E0); }
WRAPPER RwBool RpLightDestroy(RpLight* light) { EAXJMP(0x5BC780); }
WRAPPER RpLight* RpLightCreate(RwInt32 type) { EAXJMP(0x5BC7C0); }
WRAPPER void _rwD3D8TexDictionaryEnableRasterFormatConversion(RwBool enable) { EAXJMP(0x5BE280); }
WRAPPER RwFileFunctions* RwOsGetFileInterface() { EAXJMP(0x5BF110); }
WRAPPER RwBool RwFreeListDestroy(RwFreeList* freelist) { EAXJMP(0x5C1720); }
WRAPPER RwFreeList* RwFreeListCreate(RwInt32 entrySize, RwInt32 entriesPerBlock, RwInt32 alignment) { EAXJMP(0x5C1790); }
WRAPPER RwInt32 RwFreeListPurge(RwFreeList* freelist) { EAXJMP(0x5C19F0); }
WRAPPER RwInt32 RwFreeListPurgeAllFreeLists() { EAXJMP(0x5C1B90); }
WRAPPER RwFreeList* RwFreeListForAllUsed(RwFreeList* freelist, RwFreeListCallBack fpCallBack, void* pData) { EAXJMP(0x5C1D40); }
WRAPPER RwBool _rxPipelineClose() { EAXJMP(0x5C2780); }
WRAPPER RwBool _rxPipelineOpen() { EAXJMP(0x5C27E0); }
WRAPPER RxHeap* RxHeapGetGlobalHeap() { EAXJMP(0x5C2AD0); }
WRAPPER RxPacket* RxPacketCreate(RxPipelineNode* node) { EAXJMP(0x5C2AE0); }
WRAPPER RxCluster* RxClusterSetExternalData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements) { EAXJMP(0x5C2B10); }
WRAPPER RxCluster* RxClusterSetData(RxCluster* cluster, void* data, RwInt32 stride, RwInt32 numElements) { EAXJMP(0x5C2B70); }
WRAPPER RxCluster* RxClusterInitializeData(RxCluster* cluster, RwUInt32 numElements, RwUInt16 stride) { EAXJMP(0x5C2BD0); }
WRAPPER RxCluster* RxClusterResizeData(RxCluster* CurrentCluster, RwUInt32 NumElements) { EAXJMP(0x5C2C40); }
WRAPPER RxCluster* RxClusterLockWrite(RxPacket* packet, RwUInt32 clusterIndex, RxPipelineNode* node) { EAXJMP(0x5C2C90); }
WRAPPER RxPipeline* RxPipelineExecute(RxPipeline* pipeline, void* data, RwBool heapReset) { EAXJMP(0x5C2D60); }
WRAPPER RxPipeline* RxPipelineCreate() { EAXJMP(0x5C2E00); }
WRAPPER void _rxPipelineDestroy(RxPipeline* Pipeline) { EAXJMP(0x5C2E70); }
WRAPPER RwBool RwResourcesFreeResEntry(RwResEntry* entry) { EAXJMP(0x5C3080); }
WRAPPER void _rwResourcesPurge() { EAXJMP(0x5C30F0); }
WRAPPER RwResEntry* RwResourcesAllocateResEntry(void* owner, RwResEntry** ownerRef, RwInt32 size, RwResEntryDestroyNotify destroyNotify) { EAXJMP(0x5C3170); }
WRAPPER RwBool RwResourcesEmptyArena() { EAXJMP(0x5C3360); }
WRAPPER RwBool _rwPluginRegistryOpen() { EAXJMP(0x5C3450); }
WRAPPER RwBool _rwPluginRegistryClose() { EAXJMP(0x5C3480); }
WRAPPER RwInt32 _rwPluginRegistryGetPluginOffset(RwPluginRegistry const* reg, RwUInt32 pluginID) { EAXJMP(0x5C3590); }
WRAPPER RwInt32 _rwPluginRegistryAddPlugin(RwPluginRegistry* reg, RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5C35C0); }
WRAPPER RwPluginRegistry const* _rwPluginRegistryInitObject(RwPluginRegistry const* reg, void* object) { EAXJMP(0x5C37F0); }
WRAPPER RwPluginRegistry const* _rwPluginRegistryDeInitObject(RwPluginRegistry const* reg, void* object) { EAXJMP(0x5C3850); }
WRAPPER RwPluginRegistry const* _rwPluginRegistryCopyObject(RwPluginRegistry const* reg, void* dstObject, void const* srcObject) { EAXJMP(0x5C3880); }
WRAPPER RwError* RwErrorSet(RwError* code) { EAXJMP(0x5C3910); }
WRAPPER RwInt32 _rwerror(RwInt32 code, ...) { EAXJMP(0x5C3970); }
WRAPPER RwInt32 _rwPluginRegistryAddPluginStream(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) { EAXJMP(0x5C3980); }
WRAPPER RwInt32 _rwPluginRegistryAddPlgnStrmlwysCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkAlwaysCallBack alwaysCB) { EAXJMP(0x5C39C0); }
WRAPPER RwInt32 _rwPluginRegistryAddPlgnStrmRightsCB(RwPluginRegistry* reg, RwUInt32 pluginID, RwPluginDataChunkRightsCallBack rightsCB) { EAXJMP(0x5C39F0); }
WRAPPER RwPluginRegistry const* _rwPluginRegistryReadDataChunks(RwPluginRegistry const* reg, RwStream* stream, void* object) { EAXJMP(0x5C3A20); }
WRAPPER RwPluginRegistry const* _rwPluginRegistryInvokeRights(RwPluginRegistry const* reg, RwUInt32 id, void* obj, RwUInt32 extraData) { EAXJMP(0x5C3B50); }
WRAPPER RwInt32 _rwPluginRegistryGetSize(RwPluginRegistry const* reg, void const* object) { EAXJMP(0x5C3BA0); }
WRAPPER RwPluginRegistry const* _rwPluginRegistryWriteDataChunks(RwPluginRegistry const* reg, RwStream* stream, void const* object) { EAXJMP(0x5C3BE0); }
WRAPPER RwPluginRegistry const* _rwPluginRegistrySkipDataChunks(RwPluginRegistry const* reg, RwStream* stream) { EAXJMP(0x5C3CB0); }
WRAPPER RwCamera* RwCameraStreamRead(RwStream* stream) { EAXJMP(0x5C3D30); }
WRAPPER RwBBox* RwBBoxCalculate(RwBBox* boundBox, RwV3d const* verts, RwInt32 numVerts) { EAXJMP(0x5C5570); }
WRAPPER RwImage* RwImageResample(RwImage* dstImage, RwImage const* srcImage) { EAXJMP(0x5C72B0); }
WRAPPER RwImage* RwImageCreateResample(RwImage const* srcImage, RwInt32 width, RwInt32 height) { EAXJMP(0x5C7B30); }
WRAPPER RxRenderStateVector* RxRenderStateVectorSetDefaultRenderStateVector(RxRenderStateVector* rsvp) { EAXJMP(0x5D9240); }
WRAPPER RxRenderStateVector* RxRenderStateVectorCreate(RwBool current) { EAXJMP(0x5D9340); }
WRAPPER void RxRenderStateVectorDestroy(RxRenderStateVector* rsvp) { EAXJMP(0x5D9410); }
WRAPPER RxRenderStateVector* RxRenderStateVectorLoadDriverState(RxRenderStateVector* rsvp) { EAXJMP(0x5D9460); }
WRAPPER void _rxEmbeddedPacketBetweenPipelines(RxPipeline* fromPipeline, RxPipeline* toPipeline) { EAXJMP(0x5D95D0); }
WRAPPER RxPipelineNode* _rxEmbeddedPacketBetweenNodes(RxPipeline* pipeline, RxPipelineNode* nodeFrom, RwUInt32 whichOutput) { EAXJMP(0x5D9740); }
WRAPPER void _rxPacketDestroy(RxPacket* Packet) { EAXJMP(0x5D9810); }
WRAPPER RpMaterialList* _rpMaterialListDeinitialize(RpMaterialList* matList) { EAXJMP(0x5C8B10); }
WRAPPER RpMaterialList* _rpMaterialListInitialize(RpMaterialList* matList) { EAXJMP(0x5C8B70); }
WRAPPER RpMaterial* _rpMaterialListGetMaterial(RpMaterialList const* matList, RwInt32 matIndex) { EAXJMP(0x5C8B80); }
WRAPPER RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* matList, RpMaterial* material) { EAXJMP(0x5C8B90); }
WRAPPER RwInt32 _rpMaterialListFindMaterialIndex(RpMaterialList const* matList, RpMaterial const* material) { EAXJMP(0x5C8C50); }
WRAPPER RpMaterialList* _rpMaterialListStreamRead(RwStream* stream, RpMaterialList* matList) { EAXJMP(0x5C8C80); }
WRAPPER RpMeshHeader* _rpMeshHeaderCreate(RwUInt32 size) { EAXJMP(0x5C8FE0); }
WRAPPER void* _rpMeshClose(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5C8FF0); }
WRAPPER void* _rpMeshOpen(void* instance, RwInt32 offset, RwInt32 size) { EAXJMP(0x5C9020); }
WRAPPER RpBuildMesh* _rpBuildMeshCreate(RwUInt32 bufferSize) { EAXJMP(0x5C9140); }
WRAPPER RwBool _rpBuildMeshDestroy(RpBuildMesh* mesh) { EAXJMP(0x5C9220); }
WRAPPER RwBool _rpMeshDestroy(RpMeshHeader* mesh) { EAXJMP(0x5C9260); }
WRAPPER RpBuildMesh* _rpBuildMeshAddTriangle(RpBuildMesh* mesh, RpMaterial* material, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3) { EAXJMP(0x5C92A0); }
WRAPPER RpMeshHeader* _rpMeshHeaderForAllMeshes(RpMeshHeader* meshHeader, RpMeshCallBack fpCallBack, void* pData) { EAXJMP(0x5C9380); }
WRAPPER RwStream* _rpMeshWrite(RpMeshHeader const* meshHeader, void const* object, RwStream* stream, RpMaterialList const* matList) { EAXJMP(0x5C93C0); }
WRAPPER RpMeshHeader* _rpMeshRead(RwStream* stream, void const* object, RpMaterialList const* matList) { EAXJMP(0x5C9510); }
WRAPPER RwInt32 _rpMeshSize(RpMeshHeader const* meshHeader, void const* object) { EAXJMP(0x5C96E0); }
WRAPPER RpMeshHeader* RpBuildMeshGenerateDefaultTriStrip(RpBuildMesh* buildmesh, void* data) { EAXJMP(0x5C9730); }
WRAPPER RpMeshHeader* _rpTriListMeshGenerate(RpBuildMesh* buildMesh, void* data) { EAXJMP(0x5CAE10); }
WRAPPER RpMeshHeader* _rpMeshOptimise(RpBuildMesh* buildmesh, RwUInt32 flags) { EAXJMP(0x5CB230); }
WRAPPER RwInt32 RpWorldSectorRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor ructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB) { EAXJMP(0x5CB2B0); }
WRAPPER RwInt32 RpWorldSectorRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB, RwPluginDataChunkWriteCallBack writeCB, RwPluginDataChunkGetSizeCallBack getSizeCB) { EAXJMP(0x5CB2E0); }
WRAPPER RxPipeline* RpWorldSetDefaultSectorPipeline(RxPipeline* pipeline) { EAXJMP(0x5CB630); }
WRAPPER RxPipeline* RpAtomicSetDefaultPipeline(RxPipeline* pipeline) { EAXJMP(0x5CB670); }
WRAPPER void RpHAnimStdKeyFrameToMatrix(RwMatrix* matrix, void* voidIFrame) { EAXJMP(0x5CDEE0); }
WRAPPER void RpHAnimStdKeyFrameInterpolate(void* voidOut, void* voidIn1, void* voidIn2, RwReal time) { EAXJMP(0x5CE000); }
WRAPPER void RpHAnimStdKeyFrameBlend(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha) { EAXJMP(0x5CE420); }
WRAPPER RpHAnimAnimation* RpHAnimStdKeyFrameStreamRead(RwStream* stream, RpHAnimAnimation* animation) { EAXJMP(0x5CE820); }
WRAPPER RwBool RpHAnimStdKeyFrameStreamWrite(RpHAnimAnimation* animation, RwStream* stream) { EAXJMP(0x5CE8C0); }
WRAPPER RwInt32 RpHAnimStdKeyFrameStreamGetSize(RpHAnimAnimation* animation) { EAXJMP(0x5CE930); }
WRAPPER void RpHAnimStdKeyFrameMulRecip(void* voidFrame, void* voidStart) { EAXJMP(0x5CE950); }
WRAPPER void RpHAnimStdKeyFrameAdd(void* voidOut, void* voidIn1, void* voidIn2) { EAXJMP(0x5CEAB0); }
WRAPPER void RxHeapFree(RxHeap* heap, void* block) { EAXJMP(0x5D1070); }
WRAPPER void* RxHeapAlloc(RxHeap* heap, RwUInt32 size) { EAXJMP(0x5D1260); }
WRAPPER void* RxHeapRealloc(RxHeap* heap, void* block, RwUInt32 newSize, RwBool allowCopy) { EAXJMP(0x5D14D0); }
WRAPPER RwBool _rxHeapReset(RxHeap* heap) { EAXJMP(0x5D1680); }
WRAPPER void RxHeapDestroy(RxHeap* heap) { EAXJMP(0x5D16F0); }
WRAPPER RxHeap* RxHeapCreate(RwUInt32 size) { EAXJMP(0x5D1750); }
WRAPPER RxNodeOutput RxPipelineNodeFindOutputByName(RxPipelineNode* node, RwChar const* outputname) { EAXJMP(0x5D1EC0); }
WRAPPER RxNodeInput RxPipelineNodeFindInput(RxPipelineNode* node) { EAXJMP(0x5D1F20); }
WRAPPER RxPipeline* RxPipelineNodeRequestCluster(RxPipeline* pipeline, RxPipelineNode* node, RxClusterDefinition* clusterDef) { EAXJMP(0x5D1F30); }
WRAPPER RxPipeline* RxLockedPipeUnlock(RxLockedPipe* pipeline) { EAXJMP(0x5D1FA0); }
WRAPPER RxLockedPipe* RxPipelineLock(RxPipeline* pipeline) { EAXJMP(0x5D29F0); }
WRAPPER RxPipelineNode* RxPipelineFindNodeByName(RxPipeline* pipeline, RwChar const* name, RxPipelineNode* start, RwInt32* nodeIndex) { EAXJMP(0x5D2B10); }
WRAPPER RxLockedPipe* RxLockedPipeAddFragment(RxLockedPipe *pipeline, RwUInt32 *firstIndex, RxNodeDefinition *nodeDef0, ...) { EAXJMP(0x5D2BA0); }
WRAPPER RxPipeline* RxLockedPipeAddPath(RxLockedPipe* pipeline, RxNodeOutput out, RxNodeInput in) { EAXJMP(0x5D2EE0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetImmRenderSetup() { EAXJMP(0x5D31C0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetImmMangleTriangleIndices() { EAXJMP(0x5D35C0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetCullTriangle() { EAXJMP(0x5D3C60); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetClipTriangle() { EAXJMP(0x5D4F80); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetSubmitTriangle() { EAXJMP(0x5D51C0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetImmInstance() { EAXJMP(0x5D5400); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetTransform() { EAXJMP(0x5D6000); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetImmStash() { EAXJMP(0x5D61C0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetImmMangleLineIndices() { EAXJMP(0x5D6470); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetClipLine() { EAXJMP(0x5D7230); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetSubmitLine() { EAXJMP(0x5D74C0); }
WRAPPER RwBool _rwD3D8LightsOpen() { EAXJMP(0x5D9C90); }
WRAPPER void _rwD3D8LightsClose() { EAXJMP(0x5D9EF0); }
WRAPPER RwBool _rwD3D8LightsGlobalEnable(RpLightFlag flags) { EAXJMP(0x5D9F80); }
WRAPPER RwBool _rwD3D8LightLocalEnable(RpLight* light) { EAXJMP(0x5DA210); }
WRAPPER void _rwD3D8LightsEnable(RwBool enable, RwUInt32 type) { EAXJMP(0x5DA450); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetD3D8WorldSectorAllInOne() { EAXJMP(0x5DAAC0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetD3D8AtomicAllInOne() { EAXJMP(0x5DC500); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetWorldSectorInstance() { EAXJMP(0x5DCC50); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetWorldSectorEnumerateLights() { EAXJMP(0x5DCD80); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetAtomicInstance() { EAXJMP(0x5DD800); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetAtomicEnumerateLights() { EAXJMP(0x5DD9B0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetMaterialScatter() { EAXJMP(0x5DDAA0); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetLight() { EAXJMP(0x5DF040); }
WRAPPER RxNodeDefinition* RxNodeDefinitionGetPostLight() { EAXJMP(0x5DF560); }
WRAPPER void RxD3D8AllInOneSetRenderCallBack(RxPipelineNode* node, RxD3D8AllInOneRenderCallBack callback) { EAXJMP(0x5DFC60); }

WRAPPER RwInt32 _rwD3D8FindCorrectRasterFormat(RwRasterType type, RwInt32 flags) { EAXJMP(0x59A350); }

#else

extern "C"
{
    void* _rwFrameOpen(void* instance, RwInt32 offset, RwInt32 size);
    void* _rwFrameClose(void* instance, RwInt32 offset, RwInt32 size);
    RwFrame* _rwFrameCloneAndLinkClones(RwFrame* root);
    RwFrame* _rwFramePurgeClone(RwFrame* root);
    RwBool RwFrameDirty(RwFrame const* frame);
    void _rwFrameInit(RwFrame* frame);
    RwBool _rwMatrixSetMultFn(rwMatrixMultFn multMat);
    void* _rwMatrixClose(void* instance, RwInt32 offset, RwInt32 size);
    void* _rwMatrixOpen(void* instance, RwInt32 offset, RwInt32 size);
    RwBool _rwVectorSetMultFn(rwVectorMultFn multPoint, rwVectorsMultFn multPoints, rwVectorMultFn multVector, rwVectorsMultFn multVectors);
    void* _rwVectorClose(void* instance, RwInt32 offset, RwInt32 size);
    void* _rwVectorOpen(void* instance, RwInt32 offset, RwInt32 size);
    RwBool _rwPluginRegistryOpen();
    RwBool _rwPluginRegistryClose();

    RwInt32 _rwD3D8FindCorrectRasterFormat(RwRasterType type, RwInt32 flags);
}

STARTPATCHES
InjectHook(0x5BC950, &_rwObjectHasFrameSetFrame, PATCH_JUMP);
InjectHook(0x59E690, &AtomicDefaultRenderCallBack, PATCH_JUMP);
InjectHook(0x59E6C0, &_rpAtomicResyncInterpolatedSphere, PATCH_JUMP);
InjectHook(0x59E800, &RpAtomicGetWorldBoundingSphere, PATCH_JUMP);
InjectHook(0x59ED50, &RpClumpGetNumAtomics, PATCH_JUMP);
InjectHook(0x59ED80, &RpClumpRender, PATCH_JUMP);
InjectHook(0x59EDD0, &RpClumpForAllAtomics, PATCH_JUMP);
InjectHook(0x59EE10, &RpClumpForAllCameras, PATCH_JUMP);
InjectHook(0x59EE60, &RpClumpForAllLights, PATCH_JUMP);
InjectHook(0x59EEB0, &RpAtomicCreate, PATCH_JUMP);
InjectHook(0x59EFA0, &RpAtomicSetGeometry, PATCH_JUMP);
InjectHook(0x59F020, &RpAtomicDestroy, PATCH_JUMP);
InjectHook(0x59F0A0, &RpAtomicClone, PATCH_JUMP);
InjectHook(0x59F1B0, &RpClumpClone, PATCH_JUMP);
InjectHook(0x59F490, &RpClumpCreate, PATCH_JUMP);
InjectHook(0x59F500, &RpClumpDestroy, PATCH_JUMP);
InjectHook(0x59F680, &RpClumpAddAtomic, PATCH_JUMP);
InjectHook(0x59F6B0, &RpClumpRemoveAtomic, PATCH_JUMP);
InjectHook(0x59F6E0, &RpClumpRemoveLight, PATCH_JUMP);
InjectHook(0x59FC50, &RpClumpStreamRead, PATCH_JUMP);
InjectHook(0x5A0510, &RpAtomicRegisterPlugin, PATCH_JUMP);
InjectHook(0x5A0540, &RpClumpRegisterPlugin, PATCH_JUMP);
InjectHook(0x5A0570, &RpAtomicRegisterPluginStream, PATCH_JUMP);
InjectHook(0x5A05A0, &RpAtomicSetStreamAlwaysCallBack, PATCH_JUMP);
InjectHook(0x5A05C0, &RpAtomicSetStreamRightsCallBack, PATCH_JUMP);
InjectHook(0x5A05E0, &RpAtomicGetPluginOffset, PATCH_JUMP);
InjectHook(0x5A0600, &RpAtomicSetFrame, PATCH_JUMP);
InjectHook(0x5A0DC0, &RwEngineRegisterPlugin, PATCH_JUMP);
InjectHook(0x5A0DF0, &RwEngineGetPluginOffset, PATCH_JUMP);
InjectHook(0x5A0E10, &RwEngineGetNumSubSystems, PATCH_JUMP);
InjectHook(0x5A0E40, &RwEngineGetSubSystemInfo, PATCH_JUMP);
InjectHook(0x5A0E70, &RwEngineGetCurrentSubSystem, PATCH_JUMP);
InjectHook(0x5A0EA0, &RwEngineSetSubSystem, PATCH_JUMP);
InjectHook(0x5A0ED0, &RwEngineGetNumVideoModes, PATCH_JUMP);
InjectHook(0x5A0F00, &RwEngineGetVideoModeInfo, PATCH_JUMP);
InjectHook(0x5A0F30, &RwEngineGetCurrentVideoMode, PATCH_JUMP);
InjectHook(0x5A0F60, &RwEngineSetVideoMode, PATCH_JUMP);
InjectHook(0x5A0F90, &RwEngineStop, PATCH_JUMP);
InjectHook(0x5A0FE0, &RwEngineStart, PATCH_JUMP);
InjectHook(0x5A1070, &RwEngineClose, PATCH_JUMP);
InjectHook(0x5A10E0, &RwEngineOpen, PATCH_JUMP);
InjectHook(0x5A1290, &RwEngineTerm, PATCH_JUMP);
InjectHook(0x5A12D0, &RwEngineInit, PATCH_JUMP);
InjectHook(0x5A15E0, &_rwFrameOpen, PATCH_JUMP);
InjectHook(0x5A1650, &_rwFrameClose, PATCH_JUMP);
InjectHook(0x5A1690, &_rwFrameCloneAndLinkClones, PATCH_JUMP);
InjectHook(0x5A1880, &_rwFramePurgeClone, PATCH_JUMP);
InjectHook(0x5A1930, &RwFrameDirty, PATCH_JUMP);
InjectHook(0x5A1950, &_rwFrameInit, PATCH_JUMP);
InjectHook(0x5A1A00, &RwFrameCreate, PATCH_JUMP);
InjectHook(0x5A1A30, &RwFrameDestroy, PATCH_JUMP);
InjectHook(0x5A1BF0, &RwFrameDestroyHierarchy, PATCH_JUMP);
InjectHook(0x5A1C60, &RwFrameUpdateObjects, PATCH_JUMP);
InjectHook(0x5A1CE0, &RwFrameGetLTM, PATCH_JUMP);
InjectHook(0x5A1D00, &RwFrameAddChild, PATCH_JUMP);
InjectHook(0x5A1ED0, &RwFrameRemoveChild, PATCH_JUMP);
InjectHook(0x5A1FC0, &RwFrameForAllChildren, PATCH_JUMP);
InjectHook(0x5A2000, &RwFrameTranslate, PATCH_JUMP);
InjectHook(0x5A20A0, &RwFrameScale, PATCH_JUMP);
InjectHook(0x5A2140, &RwFrameTransform, PATCH_JUMP);
InjectHook(0x5A21E0, &RwFrameRotate, PATCH_JUMP);
InjectHook(0x5A2280, &RwFrameSetIdentity, PATCH_JUMP);
InjectHook(0x5A2340, &RwFrameForAllObjects, PATCH_JUMP);
InjectHook(0x5A2380, &RwFrameRegisterPlugin, PATCH_JUMP);
InjectHook(0x5A23B0, &_rwMatrixSetMultFn, PATCH_JUMP);
InjectHook(0x5A2520, &_rwMatrixDeterminant, PATCH_JUMP);
InjectHook(0x5A2570, &_rwMatrixOrthogonalError, PATCH_JUMP);
InjectHook(0x5A25D0, &_rwMatrixNormalError, PATCH_JUMP);
InjectHook(0x5A2660, &_rwMatrixIdentityError, PATCH_JUMP);
InjectHook(0x5A2730, &_rwMatrixClose, PATCH_JUMP);
InjectHook(0x5A2770, &_rwMatrixOpen, PATCH_JUMP);
InjectHook(0x5A2820, &RwMatrixOptimize, PATCH_JUMP);
InjectHook(0x5A28E0, &RwMatrixUpdate, PATCH_JUMP);
InjectHook(0x5A28F0, &RwMatrixMultiply, PATCH_JUMP);
InjectHook(0x5A2960, &RwMatrixRotateOneMinusCosineSine, PATCH_JUMP);
InjectHook(0x5A2BF0, &RwMatrixRotate, PATCH_JUMP);
InjectHook(0x5A2C90, &RwMatrixInvert, PATCH_JUMP);
InjectHook(0x5A2EE0, &RwMatrixScale, PATCH_JUMP);
InjectHook(0x5A3070, &RwMatrixTranslate, PATCH_JUMP);
InjectHook(0x5A31C0, &RwMatrixTransform, PATCH_JUMP);
InjectHook(0x5A3300, &RwMatrixDestroy, PATCH_JUMP);
InjectHook(0x5A3330, &RwMatrixCreate, PATCH_JUMP);
InjectHook(0x5A3450, &_rwVectorSetMultFn, PATCH_JUMP);
InjectHook(0x5A3600, &_rwV3dNormalize, PATCH_JUMP);
InjectHook(0x5A36A0, &RwV3dLength, PATCH_JUMP);
InjectHook(0x5A3710, &_rwSqrt, PATCH_JUMP);
InjectHook(0x5A3770, &_rwInvSqrt, PATCH_JUMP);
InjectHook(0x5A37D0, &RwV3dTransformPoints, PATCH_JUMP);
InjectHook(0x5A37E0, &RwV3dTransformVectors, PATCH_JUMP);
InjectHook(0x5A37F0, &_rwVectorClose, PATCH_JUMP);
InjectHook(0x5A3860, &_rwVectorOpen, PATCH_JUMP);
InjectHook(0x5A3AD0, &RwStreamRead, PATCH_JUMP);
InjectHook(0x5A3C30, &RwStreamWrite, PATCH_JUMP);
InjectHook(0x5A3DF0, &RwStreamSkip, PATCH_JUMP);
InjectHook(0x5A3F10, &RwStreamClose, PATCH_JUMP);
InjectHook(0x5A3FE0, &RwStreamOpen, PATCH_JUMP);
InjectHook(0x5A43A0, &RwIm2DGetNearScreenZ, PATCH_JUMP);
InjectHook(0x5A43B0, &RwIm2DGetFarScreenZ, PATCH_JUMP);
InjectHook(0x5A43C0, &RwRenderStateSet, PATCH_JUMP);
InjectHook(0x5A4410, &RwRenderStateGet, PATCH_JUMP);
InjectHook(0x5A4420, &RwIm2DRenderLine, PATCH_JUMP);
InjectHook(0x5A4430, &RwIm2DRenderPrimitive, PATCH_JUMP);
InjectHook(0x5A4440, &RwIm2DRenderIndexedPrimitive, PATCH_JUMP);
InjectHook(0x5A5020, &RwCameraEndUpdate, PATCH_JUMP);
InjectHook(0x5A5030, &RwCameraBeginUpdate, PATCH_JUMP);
InjectHook(0x5A5040, &RwCameraSetViewOffset, PATCH_JUMP);
InjectHook(0x5A5070, &RwCameraSetNearClipPlane, PATCH_JUMP);
InjectHook(0x5A5140, &RwCameraSetFarClipPlane, PATCH_JUMP);
InjectHook(0x5A5170, &RwCameraFrustumTestSphere, PATCH_JUMP);
InjectHook(0x5A51E0, &RwCameraClear, PATCH_JUMP);
InjectHook(0x5A5210, &RwCameraShowRaster, PATCH_JUMP);
InjectHook(0x5A5240, &RwCameraSetProjection, PATCH_JUMP);
InjectHook(0x5A52B0, &RwCameraSetViewWindow, PATCH_JUMP);
InjectHook(0x5A52F0, &RwCameraRegisterPlugin, PATCH_JUMP);
InjectHook(0x5A5320, &RwCameraDestroy, PATCH_JUMP);
InjectHook(0x5A5360, &RwCameraCreate, PATCH_JUMP);
InjectHook(0x5A7100, &RwTextureSetMipmapping, PATCH_JUMP);
InjectHook(0x5A7120, &RwTextureGetMipmapping, PATCH_JUMP);
InjectHook(0x5A7130, &RwTextureSetAutoMipmapping, PATCH_JUMP);
InjectHook(0x5A7150, &RwTextureGetAutoMipmapping, PATCH_JUMP);
InjectHook(0x5A7160, &RwTexDictionaryCreate, PATCH_JUMP);
InjectHook(0x5A7200, &RwTexDictionaryDestroy, PATCH_JUMP);
InjectHook(0x5A7290, &RwTexDictionaryForAllTextures, PATCH_JUMP);
InjectHook(0x5A72D0, &RwTextureCreate, PATCH_JUMP);
InjectHook(0x5A7330, &RwTextureDestroy, PATCH_JUMP);
InjectHook(0x5A73B0, &RwTextureSetName, PATCH_JUMP);
InjectHook(0x5A7420, &RwTextureSetMaskName, PATCH_JUMP);
InjectHook(0x5A7490, &RwTexDictionaryAddTexture, PATCH_JUMP);
InjectHook(0x5A74D0, &RwTexDictionaryFindNamedTexture, PATCH_JUMP);
InjectHook(0x5A7550, &RwTexDictionarySetCurrent, PATCH_JUMP);
InjectHook(0x5A7570, &RwTexDictionaryGetCurrent, PATCH_JUMP);
InjectHook(0x5A7580, &RwTextureRead, PATCH_JUMP);
InjectHook(0x5A7780, &RwTextureRasterGenerateMipmaps, PATCH_JUMP);
InjectHook(0x5A9120, &RwImageCreate, PATCH_JUMP);
InjectHook(0x5A9180, &RwImageDestroy, PATCH_JUMP);
InjectHook(0x5A91E0, &RwImageAllocatePixels, PATCH_JUMP);
InjectHook(0x5A92A0, &RwImageFreePixels, PATCH_JUMP);
InjectHook(0x5A92D0, &RwImageMakeMask, PATCH_JUMP);
InjectHook(0x5A93A0, &RwImageApplyMask, PATCH_JUMP);
InjectHook(0x5A9750, &RwImageSetPath, PATCH_JUMP);
InjectHook(0x5A9810, &RwImageRead, PATCH_JUMP);
InjectHook(0x5A9B40, &RwImageFindFileType, PATCH_JUMP);
InjectHook(0x5A9C10, &RwImageReadMaskedImage, PATCH_JUMP);
InjectHook(0x5A9F50, &RwImageCopy, PATCH_JUMP);
InjectHook(0x5AA130, &RwImageGammaCorrect, PATCH_JUMP);
InjectHook(0x5AA2C0, &RwImageSetGamma, PATCH_JUMP);
InjectHook(0x5AA4E0, &_rwStreamWriteVersionedChunkHeader, PATCH_JUMP);
InjectHook(0x5AA540, &RwStreamFindChunk, PATCH_JUMP);
InjectHook(0x5AA640, &RwMemLittleEndian32, PATCH_JUMP);
InjectHook(0x5AA650, &RwMemNative32, PATCH_JUMP);
InjectHook(0x5AA660, &RwMemFloat32ToReal, PATCH_JUMP);
InjectHook(0x5AA680, &RwStreamWriteReal, PATCH_JUMP);
InjectHook(0x5AA720, &RwStreamWriteInt32, PATCH_JUMP);
InjectHook(0x5AA740, &RwStreamReadReal, PATCH_JUMP);
InjectHook(0x5AA7B0, &RwStreamReadInt32, PATCH_JUMP);
InjectHook(0x5AA800, &RwTextureStreamGetSize, PATCH_JUMP);
InjectHook(0x5AA870, &RwTextureStreamWrite, PATCH_JUMP);
InjectHook(0x5AAA40, &RwTextureStreamRead, PATCH_JUMP);
InjectHook(0x5AB020, &RwTexDictionaryStreamWrite, PATCH_JUMP);
InjectHook(0x5AC890, &RpMorphTargetCalcBoundingSphere, PATCH_JUMP);
InjectHook(0x5AC9A0, &RpGeometryAddMorphTargets, PATCH_JUMP);
InjectHook(0x5ACB60, &RpGeometryTriangleSetVertexIndices, PATCH_JUMP);
InjectHook(0x5ACB90, &RpGeometryTriangleSetMaterial, PATCH_JUMP);
InjectHook(0x5ACBF0, &RpGeometryForAllMaterials, PATCH_JUMP);
InjectHook(0x5ACC30, &RpGeometryLock, PATCH_JUMP);
InjectHook(0x5ACC60, &RpGeometryUnlock, PATCH_JUMP);
InjectHook(0x5ACD10, &RpGeometryCreate, PATCH_JUMP);
InjectHook(0x5ACF40, &_rpGeometryAddRef, PATCH_JUMP);
InjectHook(0x5ACF50, &RpGeometryDestroy, PATCH_JUMP);
InjectHook(0x5ACFF0, &RpGeometryRegisterPlugin, PATCH_JUMP);
InjectHook(0x5AD020, &RpGeometryRegisterPluginStream, PATCH_JUMP);
InjectHook(0x5AD050, &RpGeometryStreamRead, PATCH_JUMP);
InjectHook(0x5AD6D0, &RwRasterGetCurrentContext, PATCH_JUMP);
InjectHook(0x5AD6F0, &RwRasterUnlock, PATCH_JUMP);
InjectHook(0x5AD710, &RwRasterRenderFast, PATCH_JUMP);
InjectHook(0x5AD750, &RwRasterUnlockPalette, PATCH_JUMP);
InjectHook(0x5AD780, &RwRasterDestroy, PATCH_JUMP);
InjectHook(0x5AD7C0, &RwRasterPushContext, PATCH_JUMP);
InjectHook(0x5AD810, &RwRasterRegisterPlugin, PATCH_JUMP);
InjectHook(0x5AD840, &RwRasterLockPalette, PATCH_JUMP);
InjectHook(0x5AD870, &RwRasterPopContext, PATCH_JUMP);
InjectHook(0x5AD8C0, &RwRasterGetNumLevels, PATCH_JUMP);
InjectHook(0x5AD900, &RwRasterShowRaster, PATCH_JUMP);
InjectHook(0x5AD930, &RwRasterCreate, PATCH_JUMP);
InjectHook(0x5AD9D0, &RwRasterLock, PATCH_JUMP);
InjectHook(0x5ADC30, &RpMaterialCreate, PATCH_JUMP);
InjectHook(0x5ADCB0, &RpMaterialDestroy, PATCH_JUMP);
InjectHook(0x5ADD10, &RpMaterialSetTexture, PATCH_JUMP);
InjectHook(0x5ADD40, &RpMaterialRegisterPlugin, PATCH_JUMP);
InjectHook(0x5ADD70, &RpMaterialRegisterPluginStream, PATCH_JUMP);
InjectHook(0x5ADDA0, &RpMaterialStreamRead, PATCH_JUMP);
InjectHook(0x5AE0B0, &_rpSectorDefaultRenderCallBack, PATCH_JUMP);
InjectHook(0x5AE100, &_rpWorldForAllGlobalLights, PATCH_JUMP);
InjectHook(0x5AE150, &_rpWorldSectorForAllLocalLights, PATCH_JUMP);
InjectHook(0x5AE190, &RpWorldUnlock, PATCH_JUMP);
InjectHook(0x5AE2B0, &RpWorldSectorGetWorld, PATCH_JUMP);
InjectHook(0x5AE340, &RpWorldDestroy, PATCH_JUMP);
InjectHook(0x5AE6A0, &RpWorldCreate, PATCH_JUMP);
InjectHook(0x5AEA40, &RpWorldRegisterPlugin, PATCH_JUMP);
InjectHook(0x5AEA70, &RpWorldRegisterPluginStream, PATCH_JUMP);
InjectHook(0x5AEAA0, &RpWorldPluginAttach, PATCH_JUMP);
InjectHook(0x5AFB80, &RpWorldAddCamera, PATCH_JUMP);
InjectHook(0x5AFBB0, &RpWorldRemoveCamera, PATCH_JUMP);
InjectHook(0x5AFC10, &RpAtomicGetWorld, PATCH_JUMP);
InjectHook(0x5AFC20, &RpWorldAddClump, PATCH_JUMP);
InjectHook(0x5AFDA0, &RpWorldAddLight, PATCH_JUMP);
InjectHook(0x5AFDF0, &RpWorldRemoveLight, PATCH_JUMP);
InjectHook(0x5AFE70, &RtBMPImageRead, PATCH_JUMP);
InjectHook(0x5B07D0, &RpSkinPluginAttach, PATCH_JUMP);
InjectHook(0x5B1050, &RpSkinAtomicSetHAnimHierarchy, PATCH_JUMP);
InjectHook(0x5B1070, &RpSkinAtomicGetHAnimHierarchy, PATCH_JUMP);
InjectHook(0x5B1080, &RpSkinGeometryGetSkin, PATCH_JUMP);
InjectHook(0x5B1090, &RpSkinGeometrySetSkin, PATCH_JUMP);
InjectHook(0x5B10D0, &RpSkinGetSkinToBoneMatrices, PATCH_JUMP);
InjectHook(0x5B10E0, &RpHAnimHierarchyCreate, PATCH_JUMP);
InjectHook(0x5B11F0, &RpHAnimFrameGetHierarchy, PATCH_JUMP);
InjectHook(0x5B1200, &RpHAnimHierarchySetCurrentAnim, PATCH_JUMP);
InjectHook(0x5B12B0, &RpHAnimHierarchySubAnimTime, PATCH_JUMP);
InjectHook(0x5B1480, &RpHAnimHierarchyAddAnimTime, PATCH_JUMP);
InjectHook(0x5B1780, &RpHAnimHierarchyUpdateMatrices, PATCH_JUMP);
InjectHook(0x5B1C10, &RpHAnimAnimationStreamRead, PATCH_JUMP);
InjectHook(0x5B1D50, &RpHAnimPluginAttach, PATCH_JUMP);
InjectHook(0x5B2640, &RpMatFXPluginAttach, PATCH_JUMP);
InjectHook(0x5B3750, &RpMatFXAtomicEnableEffects, PATCH_JUMP);
InjectHook(0x5B3780, &RpMatFXMaterialSetEffects, PATCH_JUMP);
InjectHook(0x5B38D0, &RpMatFXMaterialSetupEnvMap, PATCH_JUMP);
InjectHook(0x5B3A40, &RpMatFXMaterialSetBumpMapTexture, PATCH_JUMP);
InjectHook(0x5B3CF0, &RwD3D8SetRenderState, PATCH_JUMP);
InjectHook(0x5B3D40, &RwD3D8GetRenderState, PATCH_JUMP);
InjectHook(0x5B3D60, &RwD3D8SetTextureStageState, PATCH_JUMP);
InjectHook(0x5B53A0, &RwD3D8SetTexture, PATCH_JUMP);
InjectHook(0x5B6720, &RwIm3DTransform, PATCH_JUMP);
InjectHook(0x5B67F0, &RwIm3DEnd, PATCH_JUMP);
InjectHook(0x5B6820, &RwIm3DRenderIndexedPrimitive, PATCH_JUMP);
InjectHook(0x5B6980, &RwIm3DRenderLine, PATCH_JUMP);
InjectHook(0x5B6A50, &RwIm3DSetTransformPipeline, PATCH_JUMP);
InjectHook(0x5B6AC0, &RwIm3DSetRenderPipeline, PATCH_JUMP);
InjectHook(0x5B95D0, &RwD3D8EngineSetRefreshRate, PATCH_JUMP);
InjectHook(0x5B9640, &RwD3D8CameraAttachWindow, PATCH_JUMP);
InjectHook(0x5BAEB0, &RwD3D8DeviceSupportsDXTTexture, PATCH_JUMP);
InjectHook(0x5BAF90, &RwD3D8SetVertexShader, PATCH_JUMP);
InjectHook(0x5BAFD0, &RwD3D8SetPixelShader, PATCH_JUMP);
InjectHook(0x5BB010, &RwD3D8SetStreamSource, PATCH_JUMP);
InjectHook(0x5BB060, &RwD3D8SetIndices, PATCH_JUMP);
InjectHook(0x5BB0B0, &RwD3D8DrawIndexedPrimitive, PATCH_JUMP);
InjectHook(0x5BB140, &RwD3D8DrawPrimitive, PATCH_JUMP);
InjectHook(0x5BB1D0, &RwD3D8SetTransform, PATCH_JUMP);
InjectHook(0x5BB310, &RwD3D8GetTransform, PATCH_JUMP);
InjectHook(0x5BB340, &RwD3D8SetTransformWorld, PATCH_JUMP);
InjectHook(0x5BB490, &RwD3D8SetSurfaceProperties, PATCH_JUMP);
InjectHook(0x5BB7A0, &RwD3D8SetLight, PATCH_JUMP);
InjectHook(0x5BB890, &RwD3D8EnableLight, PATCH_JUMP);
InjectHook(0x5BB9F0, &RwD3D8DynamicVertexBufferCreate, PATCH_JUMP);
InjectHook(0x5BBAE0, &RwD3D8DynamicVertexBufferDestroy, PATCH_JUMP);
InjectHook(0x5BBB10, &RwD3D8IndexBufferCreate, PATCH_JUMP);
InjectHook(0x5BBB40, &RwD3D8CreatePixelShader, PATCH_JUMP);
InjectHook(0x5BBB90, &RwD3D8DeletePixelShader, PATCH_JUMP);
InjectHook(0x5BBC00, &RwD3D8SetPixelShaderConstant, PATCH_JUMP);
InjectHook(0x5BBC30, &RwD3D8GetCaps, PATCH_JUMP);
InjectHook(0x5BBC40, &RwD3D8CameraIsSphereFullyInsideFrustum, PATCH_JUMP);
InjectHook(0x5BBCA0, &RwD3D8CameraIsBBoxFullyInsideFrustum, PATCH_JUMP);
InjectHook(0x5BBD30, &RwD3D8DynamicVertexBufferLock, PATCH_JUMP);
InjectHook(0x5BBEB0, &RwD3D8DynamicVertexBufferUnlock, PATCH_JUMP);
InjectHook(0x5BBED0, &_rwIntelSSEsupported, PATCH_JUMP);
InjectHook(0x5BBF10, &RwImageSetFromRaster, PATCH_JUMP);
InjectHook(0x5BBF50, &RwRasterSetFromImage, PATCH_JUMP);
InjectHook(0x5BBF80, &RwImageFindRasterFormat, PATCH_JUMP);
InjectHook(0x5BBFF0, &RwFrameRegisterPluginStream, PATCH_JUMP);
InjectHook(0x5BC020, &_rwFrameListDeinitialize, PATCH_JUMP);
InjectHook(0x5BC050, &_rwFrameListStreamRead, PATCH_JUMP);
InjectHook(0x5BC300, &RpLightSetRadius, PATCH_JUMP);
InjectHook(0x5BC320, &RpLightSetColor, PATCH_JUMP);
InjectHook(0x5BC370, &RpLightGetConeAngle, PATCH_JUMP);
InjectHook(0x5BC5B0, &RpLightRegisterPlugin, PATCH_JUMP);
InjectHook(0x5BC5E0, &RpLightStreamRead, PATCH_JUMP);
InjectHook(0x5BC780, &RpLightDestroy, PATCH_JUMP);
InjectHook(0x5BC7C0, &RpLightCreate, PATCH_JUMP);
InjectHook(0x5BE280, &_rwD3D8TexDictionaryEnableRasterFormatConversion, PATCH_JUMP);
InjectHook(0x5BF110, &RwOsGetFileInterface, PATCH_JUMP);
InjectHook(0x5C1720, &RwFreeListDestroy, PATCH_JUMP);
InjectHook(0x5C1790, &RwFreeListCreate, PATCH_JUMP);
InjectHook(0x5C19F0, &RwFreeListPurge, PATCH_JUMP);
InjectHook(0x5C1B90, &RwFreeListPurgeAllFreeLists, PATCH_JUMP);
InjectHook(0x5C1D40, &RwFreeListForAllUsed, PATCH_JUMP);
InjectHook(0x5C2780, &_rxPipelineClose, PATCH_JUMP);
InjectHook(0x5C27E0, &_rxPipelineOpen, PATCH_JUMP);
InjectHook(0x5C2AD0, &RxHeapGetGlobalHeap, PATCH_JUMP);
InjectHook(0x5C2AE0, &RxPacketCreate, PATCH_JUMP);
InjectHook(0x5C2B10, &RxClusterSetExternalData, PATCH_JUMP);
InjectHook(0x5C2B70, &RxClusterSetData, PATCH_JUMP);
InjectHook(0x5C2BD0, &RxClusterInitializeData, PATCH_JUMP);
InjectHook(0x5C2C40, &RxClusterResizeData, PATCH_JUMP);
InjectHook(0x5C2C90, &RxClusterLockWrite, PATCH_JUMP);
InjectHook(0x5C2D60, &RxPipelineExecute, PATCH_JUMP);
InjectHook(0x5C2E00, &RxPipelineCreate, PATCH_JUMP);
InjectHook(0x5C2E70, &_rxPipelineDestroy, PATCH_JUMP);
InjectHook(0x5C3080, &RwResourcesFreeResEntry, PATCH_JUMP);
InjectHook(0x5C30F0, &_rwResourcesPurge, PATCH_JUMP);
InjectHook(0x5C3170, &RwResourcesAllocateResEntry, PATCH_JUMP);
InjectHook(0x5C3360, &RwResourcesEmptyArena, PATCH_JUMP);
InjectHook(0x5C3450, &_rwPluginRegistryOpen, PATCH_JUMP);
InjectHook(0x5C3480, &_rwPluginRegistryClose, PATCH_JUMP);
InjectHook(0x5C3590, &_rwPluginRegistryGetPluginOffset, PATCH_JUMP);
InjectHook(0x5C35C0, &_rwPluginRegistryAddPlugin, PATCH_JUMP);
InjectHook(0x5C37F0, &_rwPluginRegistryInitObject, PATCH_JUMP);
InjectHook(0x5C3850, &_rwPluginRegistryDeInitObject, PATCH_JUMP);
InjectHook(0x5C3880, &_rwPluginRegistryCopyObject, PATCH_JUMP);
InjectHook(0x5C3910, &RwErrorSet, PATCH_JUMP);
InjectHook(0x5C3970, &_rwerror, PATCH_JUMP);
InjectHook(0x5C3980, &_rwPluginRegistryAddPluginStream, PATCH_JUMP);
InjectHook(0x5C39C0, &_rwPluginRegistryAddPlgnStrmlwysCB, PATCH_JUMP);
InjectHook(0x5C39F0, &_rwPluginRegistryAddPlgnStrmRightsCB, PATCH_JUMP);
InjectHook(0x5C3A20, & _rwPluginRegistryReadDataChunks, PATCH_JUMP);
InjectHook(0x5C3B50, & _rwPluginRegistryInvokeRights, PATCH_JUMP);
InjectHook(0x5C3BA0, &_rwPluginRegistryGetSize, PATCH_JUMP);
InjectHook(0x5C3BE0, &_rwPluginRegistryWriteDataChunks, PATCH_JUMP);
InjectHook(0x5C3CB0, &_rwPluginRegistrySkipDataChunks, PATCH_JUMP);
InjectHook(0x5C3D30, &RwCameraStreamRead, PATCH_JUMP);
InjectHook(0x5C5570, &RwBBoxCalculate, PATCH_JUMP);
InjectHook(0x5C72B0, &RwImageResample, PATCH_JUMP);
InjectHook(0x5C7B30, &RwImageCreateResample, PATCH_JUMP);
InjectHook(0x5D9240, &RxRenderStateVectorSetDefaultRenderStateVector, PATCH_JUMP);
InjectHook(0x5D9340, &RxRenderStateVectorCreate, PATCH_JUMP);
InjectHook(0x5D9410, &RxRenderStateVectorDestroy, PATCH_JUMP);
InjectHook(0x5D9460, &RxRenderStateVectorLoadDriverState, PATCH_JUMP);
InjectHook(0x5D95D0, &_rxEmbeddedPacketBetweenPipelines, PATCH_JUMP);
InjectHook(0x5D9740, &_rxEmbeddedPacketBetweenNodes, PATCH_JUMP);
InjectHook(0x5D9810, &_rxPacketDestroy, PATCH_JUMP);
InjectHook(0x5C8B10, &_rpMaterialListDeinitialize, PATCH_JUMP);
InjectHook(0x5C8B70, &_rpMaterialListInitialize, PATCH_JUMP);
InjectHook(0x5C8B80, &_rpMaterialListGetMaterial, PATCH_JUMP);
InjectHook(0x5C8B90, &_rpMaterialListAppendMaterial, PATCH_JUMP);
InjectHook(0x5C8C50, &_rpMaterialListFindMaterialIndex, PATCH_JUMP);
InjectHook(0x5C8C80, &_rpMaterialListStreamRead, PATCH_JUMP);
InjectHook(0x5C8FE0, &_rpMeshHeaderCreate, PATCH_JUMP);
InjectHook(0x5C8FF0, &_rpMeshClose, PATCH_JUMP);
InjectHook(0x5C9020, &_rpMeshOpen, PATCH_JUMP);
InjectHook(0x5C9140, &_rpBuildMeshCreate, PATCH_JUMP);
InjectHook(0x5C9220, &_rpBuildMeshDestroy, PATCH_JUMP);
InjectHook(0x5C9260, &_rpMeshDestroy, PATCH_JUMP);
InjectHook(0x5C92A0, &_rpBuildMeshAddTriangle, PATCH_JUMP);
InjectHook(0x5C9380, &_rpMeshHeaderForAllMeshes, PATCH_JUMP);
InjectHook(0x5C93C0, &_rpMeshWrite, PATCH_JUMP);
InjectHook(0x5C9510, &_rpMeshRead, PATCH_JUMP);
InjectHook(0x5C96E0, &_rpMeshSize, PATCH_JUMP);
InjectHook(0x5C9730, &RpBuildMeshGenerateDefaultTriStrip, PATCH_JUMP);
InjectHook(0x5CAE10, &_rpTriListMeshGenerate, PATCH_JUMP);
InjectHook(0x5CB230, &_rpMeshOptimise, PATCH_JUMP);
InjectHook(0x5CB2B0, &RpWorldSectorRegisterPlugin, PATCH_JUMP);
InjectHook(0x5CB2E0, &RpWorldSectorRegisterPluginStream, PATCH_JUMP);
InjectHook(0x5CB630, &RpWorldSetDefaultSectorPipeline, PATCH_JUMP);
InjectHook(0x5CB670, &RpAtomicSetDefaultPipeline, PATCH_JUMP);
InjectHook(0x5CDEE0, &RpHAnimStdKeyFrameToMatrix, PATCH_JUMP);
InjectHook(0x5CE000, &RpHAnimStdKeyFrameInterpolate, PATCH_JUMP);
InjectHook(0x5CE420, &RpHAnimStdKeyFrameBlend, PATCH_JUMP);
InjectHook(0x5CE820, &RpHAnimStdKeyFrameStreamRead, PATCH_JUMP);
InjectHook(0x5CE8C0, &RpHAnimStdKeyFrameStreamWrite, PATCH_JUMP);
InjectHook(0x5CE930, &RpHAnimStdKeyFrameStreamGetSize, PATCH_JUMP);
InjectHook(0x5CE950, &RpHAnimStdKeyFrameMulRecip, PATCH_JUMP);
InjectHook(0x5CEAB0, &RpHAnimStdKeyFrameAdd, PATCH_JUMP);
InjectHook(0x5D1070, &RxHeapFree, PATCH_JUMP);
InjectHook(0x5D1260, &RxHeapAlloc, PATCH_JUMP);
InjectHook(0x5D14D0, &RxHeapRealloc, PATCH_JUMP);
InjectHook(0x5D1680, &_rxHeapReset, PATCH_JUMP);
InjectHook(0x5D16F0, &RxHeapDestroy, PATCH_JUMP);
InjectHook(0x5D1750, &RxHeapCreate, PATCH_JUMP);
InjectHook(0x5D1EC0, &RxPipelineNodeFindOutputByName, PATCH_JUMP);
InjectHook(0x5D1F20, &RxPipelineNodeFindInput, PATCH_JUMP);
InjectHook(0x5D1F30, &RxPipelineNodeRequestCluster, PATCH_JUMP);
InjectHook(0x5D1FA0, &RxLockedPipeUnlock, PATCH_JUMP);
InjectHook(0x5D29F0, &RxPipelineLock, PATCH_JUMP);
InjectHook(0x5D2B10, &RxPipelineFindNodeByName, PATCH_JUMP);
InjectHook(0x5D2BA0, &RxLockedPipeAddFragment, PATCH_JUMP);
InjectHook(0x5D2EE0, &RxLockedPipeAddPath, PATCH_JUMP);
InjectHook(0x5D31C0, &RxNodeDefinitionGetImmRenderSetup, PATCH_JUMP);
InjectHook(0x5D35C0, &RxNodeDefinitionGetImmMangleTriangleIndices, PATCH_JUMP);
InjectHook(0x5D3C60, &RxNodeDefinitionGetCullTriangle, PATCH_JUMP);
InjectHook(0x5D4F80, &RxNodeDefinitionGetClipTriangle, PATCH_JUMP);
InjectHook(0x5D51C0, &RxNodeDefinitionGetSubmitTriangle, PATCH_JUMP);
InjectHook(0x5D5400, &RxNodeDefinitionGetImmInstance, PATCH_JUMP);
InjectHook(0x5D6000, &RxNodeDefinitionGetTransform, PATCH_JUMP);
InjectHook(0x5D61C0, &RxNodeDefinitionGetImmStash, PATCH_JUMP);
InjectHook(0x5D6470, &RxNodeDefinitionGetImmMangleLineIndices, PATCH_JUMP);
InjectHook(0x5D7230, &RxNodeDefinitionGetClipLine, PATCH_JUMP);
InjectHook(0x5D74C0, &RxNodeDefinitionGetSubmitLine, PATCH_JUMP);
InjectHook(0x5D9C90, &_rwD3D8LightsOpen, PATCH_JUMP);
InjectHook(0x5D9EF0, &_rwD3D8LightsClose, PATCH_JUMP);
InjectHook(0x5D9F80, &_rwD3D8LightsGlobalEnable, PATCH_JUMP);
InjectHook(0x5DA210, &_rwD3D8LightLocalEnable, PATCH_JUMP);
InjectHook(0x5DA450, &_rwD3D8LightsEnable, PATCH_JUMP);
InjectHook(0x5DAAC0, &RxNodeDefinitionGetD3D8WorldSectorAllInOne, PATCH_JUMP);
InjectHook(0x5DC500, &RxNodeDefinitionGetD3D8AtomicAllInOne, PATCH_JUMP);
InjectHook(0x5DCC50, &RxNodeDefinitionGetWorldSectorInstance, PATCH_JUMP);
InjectHook(0x5DCD80, &RxNodeDefinitionGetWorldSectorEnumerateLights, PATCH_JUMP);
InjectHook(0x5DD800, &RxNodeDefinitionGetAtomicInstance, PATCH_JUMP);
InjectHook(0x5DD9B0, &RxNodeDefinitionGetAtomicEnumerateLights, PATCH_JUMP);
InjectHook(0x5DDAA0, &RxNodeDefinitionGetMaterialScatter, PATCH_JUMP);
InjectHook(0x5DF040, &RxNodeDefinitionGetLight, PATCH_JUMP);
InjectHook(0x5DF560, &RxNodeDefinitionGetPostLight, PATCH_JUMP);
InjectHook(0x5DFC60, &RxD3D8AllInOneSetRenderCallBack, PATCH_JUMP);
ENDPATCHES
#endif
#endif