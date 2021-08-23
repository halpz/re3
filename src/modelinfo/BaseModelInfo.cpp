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
#include "TempColModels.h"

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
	m_unk[0] = 0;
	m_unk[1] = 0;
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
	m_objectId = -1;
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
		m_2dEffectsID = CModelInfo::Get2dEffectIndex(fx);
		m_num2dEffects = 1;
	}
}

C2dEffect*
CBaseModelInfo::Get2dEffect(int n)
{
	if(m_2dEffectsID >= 0)
		return CModelInfo::Get2dEffect(m_2dEffectsID+n);
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

inline int
GetColmodelID(CColModel *model)
{
	int colModelid = 0;
	if(model == &gpTempColModels->ms_colModelBBox) colModelid = 1;
	if(model == &gpTempColModels->ms_colModelPed1) colModelid = 2;
	if(model == &gpTempColModels->ms_colModelWeapon) colModelid = 3;
	if(model == &CTempColModels::ms_colModelPed2) colModelid = 4;
	if(model == &CTempColModels::ms_colModelPedGroundHit) colModelid = 5;
	if(model == &CTempColModels::ms_colModelDoor1) colModelid = 6;
	if(model == &CTempColModels::ms_colModelBumper1) colModelid = 7;
	if(model == &CTempColModels::ms_colModelPanel1) colModelid = 8;
	if(model == &CTempColModels::ms_colModelBonnet1) colModelid = 9;
	if(model == &CTempColModels::ms_colModelBoot1) colModelid = 10;
	if(model == &CTempColModels::ms_colModelWheel1) colModelid = 11;
	if(model == &CTempColModels::ms_colModelBodyPart1) colModelid = 12;
	if(model == &CTempColModels::ms_colModelBodyPart2) colModelid = 13;
	if(model == &CTempColModels::ms_colModelCutObj[0]) colModelid = 14;
	if(model == &CTempColModels::ms_colModelCutObj[1]) colModelid = 15;
	if(model == &CTempColModels::ms_colModelCutObj[2]) colModelid = 16;
	if(model == &CTempColModels::ms_colModelCutObj[3]) colModelid = 17;
	if(model == &CTempColModels::ms_colModelCutObj[4]) colModelid = 18;
	return colModelid;
}

void
CBaseModelInfo::Write(base::cRelocatableChunkWriter &writer)
{
	m_chunk = nil;
	RcWriteThis(writer);
	if(m_colModel){
		if(m_bOwnsColModel || GetColmodelID(m_colModel) != 0)
			m_colModel->Write(writer, true);
		writer.AddPatch(&m_colModel);
	}
}
