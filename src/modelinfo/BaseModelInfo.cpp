#include "common.h"

#include "templates.h"
#include "main.h"
#include "TxdStore.h"
#include "2dEffect.h"
#include "BaseModelInfo.h"
#include "ModelInfo.h"
#include "KeyGen.h"
#include "Streaming.h"
#include "smallHeap.h"

// LCS: file done except for TODO

CBaseModelInfo::CBaseModelInfo(ModelInfoType type)
{
	m_colModel = nil;
	m_2dEffectsID = -1;
	m_objectId = -1;
	m_refCount = 0;
	m_txdSlot = -1;
	m_type = type;
	m_num2dEffects = 0;
	m_bOwnsColModel = false;
	m_nameKey = 0;
	m_unk1 = 0;
	m_unk2 = 0;
	m_name = new char[MAX_MODEL_NAME];
	*(int32*)m_name = 0;
}

void
CBaseModelInfo::Shutdown(void)
{
	DeleteCollisionModel();
	DeleteRwObject();
	DeleteChunk();
	m_2dEffectsID = -1;
	m_num2dEffects = 0;
	m_txdSlot = -1;
}

void
CBaseModelInfo::DeleteCollisionModel(void)
{
	if(!gUseChunkFiles && m_colModel && m_bOwnsColModel){
		if(m_colModel)
			delete m_colModel;
	}
	m_colModel = nil;
}

void
CBaseModelInfo::AddRef(void)
{
	m_refCount++;
	AddTexDictionaryRef();
}

void
CBaseModelInfo::RemoveRef(void)
{
	if(m_refCount > 0){
		m_refCount--;
		RemoveTexDictionaryRef();
	}
}

void
CBaseModelInfo::SetTexDictionary(const char *name)
{
	int slot = CTxdStore::FindTxdSlot(name);
	if(slot == -1)
		slot = CTxdStore::AddTxdSlot(name);
	m_txdSlot = slot;
}

void
CBaseModelInfo::AddTexDictionaryRef(void)
{
	CTxdStore::AddRef(m_txdSlot);
}

void
CBaseModelInfo::AddTexDictionaryRefGu(void)
{
	CTxdStore::AddRefGu(m_txdSlot);
}

void
CBaseModelInfo::RemoveTexDictionaryRef(void)
{
	CTxdStore::RemoveRef(m_txdSlot);
}

void
CBaseModelInfo::RemoveTexDictionaryRefGu(void)
{
	CTxdStore::RemoveRefGu(m_txdSlot);
}

void
CBaseModelInfo::Init2dEffects(void)
{
	m_2dEffectsID = -1;
	m_num2dEffects = 0;
}

void
CBaseModelInfo::Add2dEffect(C2dEffect *fx)
{
	if(m_2dEffectsID >= 0)
		m_num2dEffects++;
	else{
		m_2dEffectsID = CModelInfo::Get2dEffectStore().GetIndex(fx);
		m_num2dEffects = 1;
	}
}

C2dEffect*
CBaseModelInfo::Get2dEffect(int n)
{
	if(m_2dEffectsID >= 0)
		return CModelInfo::Get2dEffectStore().GetItem(m_2dEffectsID+n);
	else
		return nil;
}


void
CBaseModelInfo::SetModelName(const char *name)
{
	m_nameKey = CKeyGen::GetUppercaseKey(name);
	if (!gUseChunkFiles)
		strcpy(m_name, name);
}

void
CBaseModelInfo::DeleteChunk(void)
{
	// BUG? what if we're not using chunks?
	if(m_chunk){
		CStreaming::UnregisterPointer(&m_chunk, 2);
		cSmallHeap::msInstance.Free(m_chunk);
		m_chunk = nil;
	}
}

void
CBaseModelInfo::Write(base::cRelocatableChunkWriter &writer)
{
	m_chunk = nil;
	RcWriteThis(writer);
	if(m_colModel){
		assert(0 && "TODO");
	}
}
