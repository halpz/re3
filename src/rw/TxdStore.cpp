#include "common.h"

#include "main.h"
#include "smallHeap.h"
#include "templates.h"
#include "General.h"
#include "Streaming.h"
#include "RwHelper.h"
#include "TxdStore.h"

CPool<TxdDef,TxdDef> *CTxdStore::ms_pTxdPool;
RwTexDictionary *CTxdStore::ms_pStoredTxd;

// LCS: file done except unused:
// CTexListStore::RemoveTexListChunk(int)
// CTexListStore::validateRefs(void)
// CTexListStore::Write(base::cRelocatableChunkWriter &)

void
CTxdStore::Initialise(void)
{
	if(gMakeResources && ms_pTxdPool == nil)
		ms_pTxdPool = new CPool<TxdDef,TxdDef>(TXDSTORESIZE, "TexDictionary");
}

// removed in LCS but we should probably keep it
void
CTxdStore::Shutdown(void)
{
	if(ms_pTxdPool)
		delete ms_pTxdPool;
}

// removed in LCS but we should probably keep it
void
CTxdStore::GameShutdown(void)
{
	int i;

	for(i = 0; i < TXDSTORESIZE; i++){
		TxdDef *def = GetSlot(i);
		if(def && GetNumRefs(i) == 0)
			RemoveTxdSlot(i);
	}
}

int
CTxdStore::AddTxdSlot(const char *name)
{
	TxdDef *def = ms_pTxdPool->New();
	assert(def);
	def->texDict = nil;
	def->refCount = 0;
	def->refCountGu = 0;
	strcpy(def->name, name);
	return ms_pTxdPool->GetJustIndex(def);
}

void
CTxdStore::RemoveTxdSlot(int slot)
{
	TxdDef *def = GetSlot(slot);
	if(def->texDict)
		RwTexDictionaryDestroy(def->texDict);
	ms_pTxdPool->Delete(def);
}

int
CTxdStore::FindTxdSlot(const char *name)
{
	int size = ms_pTxdPool->GetSize();
	for(int i = 0; i < size; i++){
		TxdDef *def = GetSlot(i);
		if(def && !CGeneral::faststricmp(def->name, name))
			return i;
	}
	return -1;
}

char*
CTxdStore::GetTxdName(int slot)
{
	return GetSlot(slot)->name;
}

void
CTxdStore::PushCurrentTxd(void)
{
	ms_pStoredTxd = RwTexDictionaryGetCurrent();
}

void
CTxdStore::PopCurrentTxd(void)
{
	RwTexDictionarySetCurrent(ms_pStoredTxd);
	ms_pStoredTxd = nil;
}

void
CTxdStore::SetCurrentTxd(int slot)
{
	RwTexDictionarySetCurrent(GetSlot(slot)->texDict);
}

void
CTxdStore::Create(int slot)
{
	TxdDef *def = GetSlot(slot);
	def->texDict = RwTexDictionaryCreate();
	// LCS: mobile sets the txd name here, but txds don't really have names
	def->refCount = 0;
	def->refCountGu = 0;
}

int
CTxdStore::GetNumRefs(int slot)
{
	return GetSlot(slot)->refCount;
}

void
CTxdStore::AddRef(int slot)
{
	GetSlot(slot)->refCount++;
}

void
CTxdStore::AddRefEvenIfNotInMemory(int slot)
{
	GetSlot(slot)->refCount++;
}

void
CTxdStore::AddRefGu(int slot)
{
	TxdDef *def = GetSlot(slot);
	def->refCount++;
	def->refCountGu++;
}

void
CTxdStore::RemoveRef(int slot)
{
	if(--GetSlot(slot)->refCount <= 0)
		CStreaming::RemoveTxd(slot);
}

void
CTxdStore::RemoveRefGu(int slot)
{
	TxdDef *def = GetSlot(slot);
	def->refCount--;
	if(gUseChunkFiles)
		def->refCountGu--;
}

void
CTxdStore::RemoveRefWithoutDelete(int slot)
{
	GetSlot(slot)->refCount--;
}

bool
CTxdStore::LoadTxd(int slot, RwStream *stream)
{
	TxdDef *def = GetSlot(slot);

	if(stream){
		if(RwStreamFindChunk(stream, rwID_TEXDICTIONARY, nil, nil)){
			def->texDict = RwTexDictionaryGtaStreamRead(stream);
			return def->texDict != nil;
		}
	}else{
		// TODO(LCS)? fall back reading from file
	}
	printf("Failed to load TXD\n");
	return false;
}

bool
CTxdStore::LoadTxd(int slot, void *data, void *chunk)
{
	TxdDef *def = GetSlot(slot);
	def->texDict = (RwTexDictionary*)data;
	if(strncasecmp(def->name, "radar", 5) == 0){
		def->refCount = 0;
		def->refCountGu = 0;
	}
	CStreaming::RegisterPointer(&def->texDict, 3, true);
	return def->texDict != nil;
}

bool
CTxdStore::LoadTxd(int slot, const char *filename)
{
	RwStream *stream;
	bool ret;

	ret = false;
	_rwD3D8TexDictionaryEnableRasterFormatConversion(true);
	do
		stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, filename);
	while(stream == nil);
	ret = LoadTxd(slot, stream);
	RwStreamClose(stream, nil);
	return ret;
}

// removed in LCS but we should probably keep it
bool
CTxdStore::StartLoadTxd(int slot, RwStream *stream)
{
	TxdDef *def = GetSlot(slot);
	if(RwStreamFindChunk(stream, rwID_TEXDICTIONARY, nil, nil)){
		def->texDict = RwTexDictionaryGtaStreamRead1(stream);
		return def->texDict != nil;
	}else{
		printf("Failed to load TXD\n");
		return false;
	}
}

// removed in LCS but we should probably keep it
bool
CTxdStore::FinishLoadTxd(int slot, RwStream *stream)
{
	TxdDef *def = GetSlot(slot);
	def->texDict = RwTexDictionaryGtaStreamRead2(stream, def->texDict);
	return def->texDict != nil;
}

void
CTxdStore::RemoveTxd(int slot, bool notChunk)
{
	TxdDef *def = GetSlot(slot);
	if(def->texDict){
		if(!gUseChunkFiles || notChunk)
			RwTexDictionaryDestroy(def->texDict);
		else{
			// TODO? Rsl3D specific: RslTextureDestroyDispList for all textures
			CStreaming::UnregisterPointer(&def->texDict, 3);
			cSmallHeap::msInstance.Free(def->texDict);
		}
	}
	def->texDict = nil;
	def->refCount = 0;
	def->refCountGu = 0;
}

void
CTxdStore::Load(RwTexDictionary *stored, CPool<TxdDef> *pool)
{
	ms_pTxdPool = pool;
	ms_pStoredTxd = stored;
	for(int i = 0; i < TXDSTORESIZE; i++){
		TxdDef *def = GetSlot(i);
		if(def)
			def->refCount = def->texDict != nil;
	}
}
