#ifndef LIBRW
#include "common.h"

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
#endif
#endif