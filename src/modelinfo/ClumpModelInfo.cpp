#include "common.h"

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
