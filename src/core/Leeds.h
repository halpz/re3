#pragma once

/*
PatchElementModelInfo(RslElement *,void *)
ChunkName(char const*)
DestroyAndFreeResourceImage(void)
WriteOrder(char const*)
UnpatchTextures(void)
IsChunked(int)
SaveResourceImage(void)
LoadResourceImage(void)
SaveResource(RslNode *,base::cRelocatableChunkWriter &)
SaveResource(RslTAnimTree *,base::cRelocatableChunkWriter &)
SaveResource(RslSkin *,base::cRelocatableChunkWriter &)
SaveResource(CAnimBlendTree *,base::cRelocatableChunkWriter &)
PatchElementTextures(RslElement *)
PatchElementGroupTextures(RslElementGroup *)
*/

void LoadResource(RpAtomic *atomic);
void LoadResource(RpClump *clump);

/*
cRelocatableChunkWriterGTA::Save(char const*,uint,uint,bool)
cRelocatableChunkGTA::cRelocatableChunkGTA(char const*,uint,uint,bool)
SaveAnimBlock(int)
SaveModel(int,bool)
*/

void SaveResource(RwTexture *tex, base::cRelocatableChunkWriter &writer);
void SaveResource(RwTexDictionary *txd, base::cRelocatableChunkWriter &writer);
void SaveResource(RpMaterial *mat, base::cRelocatableChunkWriter &writer);
void SaveResource(RpMaterialList *matlist, base::cRelocatableChunkWriter &writer);
void SaveResource(RpGeometry *geo, base::cRelocatableChunkWriter &writer);
void SaveResource(RpAtomic *atomic, base::cRelocatableChunkWriter &writer);
void SaveResource(RpClump *clump, base::cRelocatableChunkWriter &writer);
