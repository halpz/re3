#include "common.h"
#include "patcher.h"
#include "General.h"
#include "NodeName.h"
#include "VisibilityPlugins.h"
#include "ModelInfo.h"

void
CClumpModelInfo::DeleteRwObject(void)
{
	if(m_clump){
		RpClumpDestroy(m_clump);
		m_clump = nil;
		RemoveTexDictionaryRef();
	}
}

RwObject*
CClumpModelInfo::CreateInstance(void)
{
	if(m_clump)
		return (RwObject*)RpClumpClone(m_clump);
	return nil;
}

RwObject*
CClumpModelInfo::CreateInstance(RwMatrix *m)
{
	if(m_clump){
		RpClump *clump = (RpClump*)CreateInstance();
		*RwFrameGetMatrix(RpClumpGetFrame(clump)) = *m;
		return (RwObject*)clump;
	}
	return nil;
}

RpAtomic*
CClumpModelInfo::SetAtomicRendererCB(RpAtomic *atomic, void *data)
{
	CVisibilityPlugins::SetAtomicRenderCallback(atomic, (RpAtomicCallBackRender)data);
	return atomic;
}

void
CClumpModelInfo::SetClump(RpClump *clump)
{
	m_clump = clump;
	CVisibilityPlugins::SetClumpModelInfo(m_clump, this);
	AddTexDictionaryRef();
	RpClumpForAllAtomics(clump, SetAtomicRendererCB, nil);
	if(strncmp(GetName(), "playerh", 8) == 0)
		RpClumpForAllAtomics(clump, SetAtomicRendererCB, (void*)CVisibilityPlugins::RenderPlayerCB);
}

void
CClumpModelInfo::SetFrameIds(RwObjectNameIdAssocation *assocs)
{
	int32 i;
	RwObjectNameAssociation objname;

	for(i = 0; assocs[i].name; i++)
		if((assocs[i].flags & CLUMP_FLAG_NO_HIERID) == 0){
			objname.frame = nil;
			objname.name = assocs[i].name;
			RwFrameForAllChildren(RpClumpGetFrame(m_clump), FindFrameFromNameWithoutIdCB, &objname);
			if(objname.frame)
				CVisibilityPlugins::SetFrameHierarchyId(objname.frame, assocs[i].hierId);
		}
}

RwFrame*
CClumpModelInfo::FindFrameFromIdCB(RwFrame *frame, void *data)
{
	RwObjectIdAssociation *assoc = (RwObjectIdAssociation*)data;

	if(CVisibilityPlugins::GetFrameHierarchyId(frame) != assoc->id){
		RwFrameForAllChildren(frame, FindFrameFromIdCB, assoc);
		return assoc->frame ? nil : frame;
	}else{
		assoc->frame = frame;
		return nil;
	}
}

RwFrame*
CClumpModelInfo::FindFrameFromNameCB(RwFrame *frame, void *data)
{
	RwObjectNameAssociation *assoc = (RwObjectNameAssociation*)data;

	if(CGeneral::faststricmp(GetFrameNodeName(frame), assoc->name)){
		RwFrameForAllChildren(frame, FindFrameFromNameCB, assoc);
		return assoc->frame ? nil : frame;
	}else{
		assoc->frame = frame;
		return nil;
	}
}

RwFrame*
CClumpModelInfo::FindFrameFromNameWithoutIdCB(RwFrame *frame, void *data)
{
	RwObjectNameAssociation *assoc = (RwObjectNameAssociation*)data;

	if(CVisibilityPlugins::GetFrameHierarchyId(frame) ||
		CGeneral::faststricmp(GetFrameNodeName(frame), assoc->name)){
		RwFrameForAllChildren(frame, FindFrameFromNameWithoutIdCB, assoc);
		return assoc->frame ? nil : frame;
	}else{
		assoc->frame = frame;
		return nil;
	}
}

RwFrame*
CClumpModelInfo::FillFrameArrayCB(RwFrame *frame, void *data)
{
	int32 id;
	RwFrame **frames = (RwFrame**)data;
	id = CVisibilityPlugins::GetFrameHierarchyId(frame);
	if(id > 0)
		frames[id] = frame;
	RwFrameForAllChildren(frame, FillFrameArrayCB, data);
	return frame;
}

void
CClumpModelInfo::FillFrameArray(RpClump *clump, RwFrame **frames)
{
	RwFrameForAllChildren(RpClumpGetFrame(clump), FillFrameArrayCB, frames);
}

RwFrame*
CClumpModelInfo::GetFrameFromId(RpClump *clump, int32 id)
{
	RwObjectIdAssociation assoc;
	assoc.id = id;
	assoc.frame = nil;
	RwFrameForAllChildren(RpClumpGetFrame(clump), FindFrameFromIdCB, &assoc);
	return assoc.frame;
}


class CClumpModelInfo_ : public CClumpModelInfo
{
public:
	void DeleteRwObject_(void) { this->CClumpModelInfo::DeleteRwObject(); }
	RwObject *CreateInstance_1(void) { return CClumpModelInfo::CreateInstance(); }
	RwObject *CreateInstance_2(RwMatrix *m) { return CClumpModelInfo::CreateInstance(m); }
	RwObject *GetRwObject_(void) { return CClumpModelInfo::GetRwObject(); }
	void SetClump_(RpClump *clump) { CClumpModelInfo::SetClump(clump); }
};

STARTPATCHES
	InjectHook(0x4F8800, &CClumpModelInfo_::DeleteRwObject_, PATCH_JUMP);
	InjectHook(0x4F8920, &CClumpModelInfo_::CreateInstance_1, PATCH_JUMP);
	InjectHook(0x4F88A0, &CClumpModelInfo_::CreateInstance_2, PATCH_JUMP);
	InjectHook(0x50C1C0, &CClumpModelInfo_::GetRwObject_, PATCH_JUMP);
	InjectHook(0x4F8830, &CClumpModelInfo_::SetClump_, PATCH_JUMP);
	InjectHook(0x4F8940, &CClumpModelInfo::SetAtomicRendererCB, PATCH_JUMP);
	InjectHook(0x4F8960, &CClumpModelInfo::FindFrameFromNameCB, PATCH_JUMP);
	InjectHook(0x4F8A10, &CClumpModelInfo::FindFrameFromNameWithoutIdCB, PATCH_JUMP);
	InjectHook(0x4F8AD0, &CClumpModelInfo::FindFrameFromIdCB, PATCH_JUMP);
	InjectHook(0x4F8BB0, &CClumpModelInfo::SetFrameIds, PATCH_JUMP);
	InjectHook(0x4F8B20, &CClumpModelInfo::FillFrameArrayCB, PATCH_JUMP);
	InjectHook(0x4F8B90, &CClumpModelInfo::FillFrameArray, PATCH_JUMP);
	InjectHook(0x4F8B50, &CClumpModelInfo::GetFrameFromId, PATCH_JUMP);
ENDPATCHES
