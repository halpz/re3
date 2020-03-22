#pragma once

void *RwMallocAlign(RwUInt32 size, RwUInt32 align);
void RwFreeAlign(void *mem);

void DefinedState(void);
RwFrame *GetFirstChild(RwFrame *frame);
RwObject *GetFirstObject(RwFrame *frame);
RpAtomic *GetFirstAtomic(RpClump *clump);
RwTexture *GetFirstTexture(RwTexDictionary *txd);

RwTexDictionary *RwTexDictionaryGtaStreamRead(RwStream *stream);
RwTexDictionary *RwTexDictionaryGtaStreamRead1(RwStream *stream);
RwTexDictionary *RwTexDictionaryGtaStreamRead2(RwStream *stream, RwTexDictionary *texDict);
void ReadVideoCardCapsFile(uint32&, uint32&, uint32&, uint32&);
bool CheckVideoCardCaps(void);
void WriteVideoCardCapsFile(void);
void ConvertingTexturesScreen(uint32, uint32, const char*);
void DealWithTxdWriteError(uint32, uint32, const char*);
bool ConvertTextures(); // not a real name

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
