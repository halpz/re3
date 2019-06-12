#pragma once

void DefinedState(void);
RwFrame *GetFirstChild(RwFrame *frame);
RwObject *GetFirstObject(RwFrame *frame);
RpAtomic *GetFirstAtomic(RpClump *clump);

void CameraSize(RwCamera *camera,
                RwRect *rect,
                RwReal viewWindow,
                RwReal aspectRatio);
void CameraDestroy(RwCamera *camera);
RwCamera *CameraCreate(RwInt32 width,
                       RwInt32 height,
                       RwBool zBuffer);
