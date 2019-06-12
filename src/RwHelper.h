#pragma once

void DefinedState(void);
RwObject *GetFirstObject(RwFrame *frame);

extern void CameraSize(RwCamera *camera,
                       RwRect *rect,
                       RwReal viewWindow,
                       RwReal aspectRatio);
extern void CameraDestroy(RwCamera *camera);
extern RwCamera *CameraCreate(RwInt32 width,
                              RwInt32 height,
                              RwBool zBuffer);