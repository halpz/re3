#pragma once

void DefinedState(void);
RwFrame *GetFirstChild(RwFrame *frame);
RwObject *GetFirstObject(RwFrame *frame);
RpAtomic *GetFirstAtomic(RpClump *clump);

RwTexDictionary *RwTexDictionaryGtaStreamRead(RwStream *stream);
bool RpClumpGtaStreamRead1(RwStream *stream);
RpClump *RpClumpGtaStreamRead2(RwStream *stream);
void RpClumpGtaCancelStream(void);

void CameraSize(RwCamera *camera,
                RwRect *rect,
                RwReal viewWindow,
                RwReal aspectRatio);
void CameraDestroy(RwCamera *camera);
RwCamera *CameraCreate(RwInt32 width,
                       RwInt32 height,
                       RwBool zBuffer);
