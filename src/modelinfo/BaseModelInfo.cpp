#include "common.h"

#include "templates.h"
#include "TxdStore.h"
#include "2dEffect.h"
#include "BaseModelInfo.h"
#include "ModelInfo.h"
#include "ColModel.h"

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
}

void
CBaseModelInfo::Shutdown(void)
{
	DeleteCollisionModel();
	DeleteRwObject();
	m_2dEffectsID = -1;
	m_num2dEffects = 0;
	m_txdSlot = -1;
	m_objectId = -1;
}

void
CBaseModelInfo::DeleteCollisionModel(void)
{
	if(m_colModel && m_bOwnsColModel){
		if(m_colModel)
			delete m_colModel;
		m_colModel = nil;
	}
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
	m_refCount--;
	RemoveTexDictionaryRef();
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
CBaseModelInfo::RemoveTexDictionaryRef(void)
{
	CTxdStore::RemoveRef(m_txdSlot);
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
