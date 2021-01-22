#include "common.h"

#include "RwHelper.h"
#include "General.h"
#include "NodeName.h"
#include "VisibilityPlugins.h"
#include "Bones.h"
#include "AnimBlendClumpData.h"
#include "AnimBlendHierarchy.h"
#include "AnimBlendAssociation.h"
#include "AnimManager.h"
#include "RpAnimBlend.h"
#include "PedModelInfo.h"

RwInt32 ClumpOffset;

enum
{
	ID_RPANIMBLEND = MAKECHUNKID(rwVENDORID_ROCKSTAR, 0xFD),
};

void*
AnimBlendClumpCreate(void *object, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
	*RWPLUGINOFFSET(CAnimBlendClumpData*, object, offsetInObject) = nil;
	return object;
}

void*
AnimBlendClumpDestroy(void *object, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
	CAnimBlendClumpData *data;
	data = *RPANIMBLENDCLUMPDATA(object);
	if(data){
		RpAnimBlendClumpRemoveAllAssociations((RpClump*)object);
		delete data;
		*RPANIMBLENDCLUMPDATA(object) = nil;
	}
	return object;
}

void *AnimBlendClumpCopy(void *dstObject, const void *srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject) { return nil; }

bool
RpAnimBlendPluginAttach(void)
{
	ClumpOffset = RpClumpRegisterPlugin(sizeof(CAnimBlendClumpData*), ID_RPANIMBLEND,
		AnimBlendClumpCreate, AnimBlendClumpDestroy, AnimBlendClumpCopy);
	return ClumpOffset >= 0;
}

CAnimBlendAssociation*
RpAnimBlendGetNextAssociation(CAnimBlendAssociation *assoc)
{
	if(assoc->link.next)
		return CAnimBlendAssociation::FromLink(assoc->link.next);
	return nil;
}

CAnimBlendAssociation*
RpAnimBlendGetNextAssociation(CAnimBlendAssociation *assoc, uint32 mask)
{
	CAnimBlendLink *link;
	for(link = assoc->link.next; link; link = link->next){
		assoc = CAnimBlendAssociation::FromLink(link);
		if(assoc->flags & mask)
			return assoc;
	}
	return nil;
}

void
RpAnimBlendAllocateData(RpClump *clump)
{
	*RPANIMBLENDCLUMPDATA(clump) = new CAnimBlendClumpData;
}


void
RpAnimBlendClumpSetBlendDeltas(RpClump *clump, uint32 mask, float delta)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	for(CAnimBlendLink *link = clumpData->link.next; link; link = link->next){
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);
		if(mask == 0 || (assoc->flags & mask))
			assoc->blendDelta = delta;
	}
}

void
RpAnimBlendClumpRemoveAllAssociations(RpClump *clump)
{
	RpAnimBlendClumpRemoveAssociations(clump, 0);
}

void
RpAnimBlendClumpRemoveAssociations(RpClump *clump, uint32 mask)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	CAnimBlendLink *next;
	for(CAnimBlendLink *link = clumpData->link.next; link; link = next){
		next = link->next;
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);
		if(mask == 0 || (assoc->flags & mask))
			if(assoc)
				delete assoc;
	}
}

RwFrame*
FrameForAllChildrenCountCallBack(RwFrame *frame, void *data)
{
	int *numFrames = (int*)data;
	(*numFrames)++;
	RwFrameForAllChildren(frame, FrameForAllChildrenCountCallBack, data);
	return frame;
}

RwFrame*
FrameForAllChildrenFillFrameArrayCallBack(RwFrame *frame, void *data)
{
	AnimBlendFrameData **frames = (AnimBlendFrameData**)data;
	(*frames)->frame = frame;
	(*frames)++;
	RwFrameForAllChildren(frame, FrameForAllChildrenFillFrameArrayCallBack, frames);
	return frame;
}

// FrameInitCallBack on PS2
void
FrameInitCBnonskin(AnimBlendFrameData *frameData, void*)
{
	frameData->flag = 0;
	frameData->resetPos = *RwMatrixGetPos(RwFrameGetMatrix(frameData->frame));
}

void
FrameInitCBskin(AnimBlendFrameData *frameData, void*)
{
	frameData->flag = 0;
}

void
RpAnimBlendClumpInitSkinned(RpClump *clump)
{
	int i;
	RwV3d boneTab[64];
	CAnimBlendClumpData *clumpData;
	RpAtomic *atomic;
	RpSkin *skin;
	RpHAnimHierarchy *hier;
	int numBones;

	RpAnimBlendAllocateData(clump);
	clumpData = *RPANIMBLENDCLUMPDATA(clump);
	atomic = GetFirstAtomic(clump);
	assert(atomic);
	skin = RpSkinGeometryGetSkin(RpAtomicGetGeometry(atomic));
	assert(skin);
	numBones = RpSkinGetNumBones(skin);
	clumpData->SetNumberOfBones(numBones);
	hier = GetAnimHierarchyFromSkinClump(clump);
	assert(hier);
	memset(boneTab, 0, sizeof(boneTab));
	SkinGetBonePositionsToTable(clump, boneTab);

	AnimBlendFrameData *frames = clumpData->frames;
	for(i = 0; i < numBones; i++){
		frames[i].nodeID = HIERNODEID(hier, i);
		frames[i].resetPos = boneTab[i];
#ifdef LIBRW
		frames[i].hanimFrame = (RpHAnimStdInterpFrame*)rpHANIMHIERARCHYGETINTERPFRAME(hier, i);
#else
		frames[i].hanimFrame = (RpHAnimStdInterpFrame*)rtANIMGETINTERPFRAME(hier->currentAnim, i);
#endif
	}
	clumpData->ForAllFrames(FrameInitCBskin, nil);
	clumpData->frames[0].flag |= AnimBlendFrameData::VELOCITY_EXTRACTION;
}

void
RpAnimBlendClumpInitNotSkinned(RpClump *clump)
{
	int numFrames = 0;
	CAnimBlendClumpData *clumpData;
	RwFrame *root;
	AnimBlendFrameData *frames;

	RpAnimBlendAllocateData(clump);
	clumpData = *RPANIMBLENDCLUMPDATA(clump);
	root = RpClumpGetFrame(clump);
	RwFrameForAllChildren(root, FrameForAllChildrenCountCallBack, &numFrames);
	clumpData->SetNumberOfFrames(numFrames);
	frames = clumpData->frames;
	RwFrameForAllChildren(root, FrameForAllChildrenFillFrameArrayCallBack, &frames);
	clumpData->ForAllFrames(FrameInitCBnonskin, nil);
	clumpData->frames[0].flag |= AnimBlendFrameData::VELOCITY_EXTRACTION;
}

void
RpAnimBlendClumpInit(RpClump *clump)
{
	if(IsClumpSkinned(clump))
		RpAnimBlendClumpInitSkinned(clump);
	else
		RpAnimBlendClumpInitNotSkinned(clump);
}

bool
RpAnimBlendClumpIsInitialized(RpClump *clump)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	return clumpData && clumpData->numFrames != 0;
}

CAnimBlendAssociation*
RpAnimBlendClumpGetAssociation(RpClump *clump, uint32 id)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);

	if(clumpData == nil) return nil;

	for(CAnimBlendLink *link = clumpData->link.next; link; link = link->next){
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);
		if(assoc->animId == id)
			return assoc;
	}
	return nil;
}

CAnimBlendAssociation*
RpAnimBlendClumpGetMainAssociation(RpClump *clump, CAnimBlendAssociation **assocRet, float *blendRet)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);

	if(clumpData == nil) return nil;

	CAnimBlendAssociation *mainAssoc = nil;
	CAnimBlendAssociation *secondAssoc = nil;
	float mainBlend = 0.0f;
	float secondBlend = 0.0f;
	for(CAnimBlendLink *link = clumpData->link.next; link; link = link->next){
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);

		if(assoc->IsPartial())
			continue;

		if(assoc->blendAmount > mainBlend){
			secondBlend = mainBlend;
			mainBlend = assoc->blendAmount;

			secondAssoc = mainAssoc;
			mainAssoc = assoc;
		}else if(assoc->blendAmount > secondBlend){
			secondBlend = assoc->blendAmount;
			secondAssoc = assoc;
		}
	}
	if(assocRet) *assocRet = secondAssoc;
	if(blendRet) *blendRet = secondBlend;
	return mainAssoc;
}

CAnimBlendAssociation*
RpAnimBlendClumpGetMainPartialAssociation(RpClump *clump)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);

	if(clumpData == nil) return nil;

	CAnimBlendAssociation *mainAssoc = nil;
	float mainBlend = 0.0f;
	for(CAnimBlendLink *link = clumpData->link.next; link; link = link->next){
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);

		if(!assoc->IsPartial())
			continue;

		if(assoc->blendAmount > mainBlend){
			mainBlend = assoc->blendAmount;
			mainAssoc = assoc;
		}
	}
	return mainAssoc;
}

CAnimBlendAssociation*
RpAnimBlendClumpGetMainAssociation_N(RpClump *clump, int n)
{
	int i;
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);

	if(clumpData == nil) return nil;

	i = 0;
	for(CAnimBlendLink *link = clumpData->link.next; link; link = link->next){
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);

		if(assoc->IsPartial())
			continue;

		if(i == n)
			return assoc;
		i++;
	}
	return nil;
}

CAnimBlendAssociation*
RpAnimBlendClumpGetMainPartialAssociation_N(RpClump *clump, int n)
{
	int i;
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);

	if(clumpData == nil) return nil;

	i = 0;
	for(CAnimBlendLink *link = clumpData->link.next; link; link = link->next){
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);

		if(!assoc->IsPartial())
			continue;

		if(i == n)
			return assoc;
		i++;
	}
	return nil;
}

CAnimBlendAssociation*
RpAnimBlendClumpGetFirstAssociation(RpClump *clump, uint32 mask)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);

	if(clumpData == nil) return nil;

	for(CAnimBlendLink *link = clumpData->link.next; link; link = link->next){
		CAnimBlendAssociation *assoc = CAnimBlendAssociation::FromLink(link);
		if(assoc->flags & mask)
			return assoc;
	}
	return nil;
}

CAnimBlendAssociation*
RpAnimBlendClumpGetFirstAssociation(RpClump *clump)
{
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	if(!RpAnimBlendClumpIsInitialized(clump))
		return nil;
	if(clumpData->link.next)
		return CAnimBlendAssociation::FromLink(clumpData->link.next);
	return nil;
}

// FillFrameArrayCallBack on PS2
void
FillFrameArrayCBnonskin(AnimBlendFrameData *frame, void *arg)
{
	AnimBlendFrameData **frames = (AnimBlendFrameData**)arg;
	frames[CVisibilityPlugins::GetFrameHierarchyId(frame->frame)] = frame;
}

void
RpAnimBlendClumpFillFrameArraySkin(RpClump *clump, AnimBlendFrameData **frames)
{
	int i;
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	RpHAnimHierarchy *hier = GetAnimHierarchyFromSkinClump(clump);
	for(i = PED_MID; i < PED_NODE_MAX; i++)
		frames[i] = &clumpData->frames[RpHAnimIDGetIndex(hier, ConvertPedNode2BoneTag(i))];
}

void
RpAnimBlendClumpFillFrameArray(RpClump *clump, AnimBlendFrameData **frames)
{
	if(IsClumpSkinned(clump))
		RpAnimBlendClumpFillFrameArraySkin(clump, frames);
	else
		(*RPANIMBLENDCLUMPDATA(clump))->ForAllFrames(FillFrameArrayCBnonskin, frames);
}

AnimBlendFrameData *pFrameDataFound;

void
FrameFindByNameCBnonskin(AnimBlendFrameData *frame, void *arg)
{
	char *nodename = GetFrameNodeName(frame->frame);
	if(!CGeneral::faststricmp(nodename, (char*)arg))
		pFrameDataFound = frame;
}

void
FrameFindByNameCBskin(AnimBlendFrameData *frame, void *arg)
{
	const char *name = ConvertBoneTag2BoneName(frame->nodeID);
	if(name && CGeneral::faststricmp(name, (char*)arg) == 0)
		pFrameDataFound = frame;
}

void
FrameFindByBoneCB(AnimBlendFrameData *frame, void *arg)
{
	if(frame->nodeID == (int32)(uintptr)arg)
		pFrameDataFound = frame;
}

AnimBlendFrameData*
RpAnimBlendClumpFindFrame(RpClump *clump, const char *name)
{
	pFrameDataFound = nil;
	if(IsClumpSkinned(clump))
		(*RPANIMBLENDCLUMPDATA(clump))->ForAllFrames(FrameFindByNameCBskin, (void*)name);
	else
		(*RPANIMBLENDCLUMPDATA(clump))->ForAllFrames(FrameFindByNameCBnonskin, (void*)name);
	return pFrameDataFound;
}

AnimBlendFrameData*
RpAnimBlendClumpFindBone(RpClump *clump, uint32 boneTag)
{
	pFrameDataFound = nil;
	(*RPANIMBLENDCLUMPDATA(clump))->ForAllFrames(FrameFindByBoneCB, (void*)boneTag);
	return pFrameDataFound;
}

void
RpAnimBlendNodeUpdateKeyframes(AnimBlendFrameData *frames, AnimBlendFrameUpdateData *updateData, int32 numNodes)
{
	CAnimBlendNode **node;
	int i;

	for(node = updateData->nodes; *node; node++){
		CAnimBlendAssociation *a = (*node)->association;
		for(i = 0; i < numNodes; i++)
			if((frames[i].flag & AnimBlendFrameData::VELOCITY_EXTRACTION) == 0 ||
			   gpAnimBlendClump->velocity2d == nil){
				if((*node)[i].sequence)
					(*node)[i].FindKeyFrame(a->currentTime - a->timeStep);
			}
	}
}

// TODO:
// CAnimBlendClumpData::LoadFramesIntoSPR
// CAnimBlendClumpData::ForAllFramesInSPR
void
RpAnimBlendClumpUpdateAnimations(RpClump *clump, float timeDelta, bool doRender)
{
	int i;
	CAnimBlendAssociation *assoc;
	AnimBlendFrameUpdateData updateData;
	float totalLength = 0.0f;
	float totalBlend = 0.0f;
	CAnimBlendLink *link, *next;
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	gpAnimBlendClump = clumpData;

	if(clumpData->link.next == nil)
		return;

	// Update blend and get node array
	i = 0;
	updateData.foobar = 0;
	for(link = clumpData->link.next; link; link = next){
		next = link->next;
		assoc = CAnimBlendAssociation::FromLink(link);
		if(assoc->UpdateBlend(timeDelta)){
			if(assoc->hierarchy->sequences){
				CAnimManager::UncompressAnimation(assoc->hierarchy);
				if(i < 11)
					updateData.nodes[i++] = assoc->GetNode(0);
				if(assoc->flags & ASSOC_MOVEMENT){
					totalLength += assoc->hierarchy->totalLength/assoc->speed * assoc->blendAmount;
					totalBlend += assoc->blendAmount;
				}else
					updateData.foobar = 1;
			}else
				debug("anim %s is not loaded\n", assoc->hierarchy->name);
		}
	}

	for(link = clumpData->link.next; link; link = link->next){
		assoc = CAnimBlendAssociation::FromLink(link);
		assoc->UpdateTimeStep(timeDelta, totalLength == 0.0f ? 1.0f : totalBlend/totalLength);
	}

	updateData.nodes[i] = nil;

#ifdef ANIM_COMPRESSION
	if(clumpData->frames[0].flag & AnimBlendFrameData::COMPRESSED){
		if(IsClumpSkinned(clump))
			clumpData->ForAllFrames(FrameUpdateCallBackSkinnedCompressed, &updateData);
		else
			clumpData->ForAllFrames(FrameUpdateCallBackNonSkinnedCompressed, &updateData);
	}else
#endif
	if(doRender){
		if(clumpData->frames[0].flag & AnimBlendFrameData::UPDATE_KEYFRAMES)
			RpAnimBlendNodeUpdateKeyframes(clumpData->frames, &updateData, clumpData->numFrames);
		if(IsClumpSkinned(clump))
			clumpData->ForAllFrames(FrameUpdateCallBackSkinned, &updateData);
		else
			clumpData->ForAllFrames(FrameUpdateCallBackNonSkinned, &updateData);
		clumpData->frames[0].flag &= ~AnimBlendFrameData::UPDATE_KEYFRAMES;
	}else{
		clumpData->ForAllFrames(FrameUpdateCallBackOffscreen, &updateData);
		clumpData->frames[0].flag |= AnimBlendFrameData::UPDATE_KEYFRAMES;
	}

	for(link = clumpData->link.next; link; link = link->next){
		assoc = CAnimBlendAssociation::FromLink(link);
		assoc->UpdateTime(timeDelta, totalLength == 0.0f ? 1.0f : totalBlend/totalLength);
	}
	RwFrameUpdateObjects(RpClumpGetFrame(clump));
}
