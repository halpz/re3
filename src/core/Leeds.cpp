#include "common.h"
#include "Leeds.h"

void LoadResource(RpAtomic *atomic) {}
void LoadResource(RpClump *clump) {}


void SaveResource(RwTexture *tex, base::cRelocatableChunkWriter &writer) {}
void SaveResource(RwTexDictionary *txd, base::cRelocatableChunkWriter &writer) {}
void SaveResource(RpMaterial *mat, base::cRelocatableChunkWriter &writer) {}
void SaveResource(RpMaterialList *matlist, base::cRelocatableChunkWriter &writer) {}
void SaveResource(RpGeometry *geo, base::cRelocatableChunkWriter &writer) {}
void SaveResource(RpAtomic *atomic, base::cRelocatableChunkWriter &writer) {}
void SaveResource(RpClump *clump, base::cRelocatableChunkWriter &writer) {}
