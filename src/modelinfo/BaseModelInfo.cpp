#include "common.h"
#include "patcher.h"
#include "templates.h"
#include "TxdStore.h"
#include "2dEffect.h"
#include "BaseModelInfo.h"


CBaseModelInfo::CBaseModelInfo(ModeInfoType type)
{
	m_colModel = nil;
	m_twodEffects = nil;
	m_objectId = -1;
	m_refCount = 0;
	m_txdSlot = -1;
	m_type = type;
	m_num2dEffects = 0;
	m_freeCol = false;
}

void
CBaseModelInfo::Shutdown(void)
{
	DeleteCollisionModel();
	DeleteRwObject();
	m_twodEffects = nil;
	m_num2dEffects = 0;
	m_txdSlot = -1;
}

void
CBaseModelInfo::DeleteCollisionModel(void)
{
	if(m_colModel && m_freeCol){
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
	if(slot < 0)
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
	m_twodEffects = nil;
	m_num2dEffects = 0;
}

void
CBaseModelInfo::Add2dEffect(C2dEffect *fx)
{
	if(m_twodEffects)
		m_num2dEffects++;
	else{
		m_twodEffects = fx;
		m_num2dEffects = 1;
	}
}

C2dEffect*
CBaseModelInfo::Get2dEffect(int n)
{
	if(m_twodEffects)
		return &m_twodEffects[n];
	else
		return nil;
}


class CBaseModelInfo_ : public CBaseModelInfo
{
public:
	void Shutdown_(void) { CBaseModelInfo::Shutdown(); }
};
STARTPATCHES
	// can't easily replace ctor at 4F6A50
	InjectHook(0x4F6A90, &CBaseModelInfo_::Shutdown_, PATCH_JUMP);

	InjectHook(0x4F6AC0, &CBaseModelInfo::DeleteCollisionModel, PATCH_JUMP);
	InjectHook(0x4F6B70, &CBaseModelInfo::ClearTexDictionary, PATCH_JUMP);
	InjectHook(0x4F6BA0, &CBaseModelInfo::AddRef, PATCH_JUMP);
	InjectHook(0x4F6BB0, &CBaseModelInfo::RemoveRef, PATCH_JUMP);
	InjectHook(0x4F6B40, &CBaseModelInfo::SetTexDictionary, PATCH_JUMP);
	InjectHook(0x4F6B80, &CBaseModelInfo::AddTexDictionaryRef, PATCH_JUMP);
	InjectHook(0x4F6B90, &CBaseModelInfo::RemoveTexDictionaryRef, PATCH_JUMP);
	InjectHook(0x4F6B20, &CBaseModelInfo::Add2dEffect, PATCH_JUMP);
	InjectHook(0x4F6AF0, &CBaseModelInfo::Init2dEffects, PATCH_JUMP);
	InjectHook(0x4F6B00, &CBaseModelInfo::Get2dEffect, PATCH_JUMP);
ENDPATCHES
