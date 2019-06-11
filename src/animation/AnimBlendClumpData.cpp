#include "common.h"
#include "patcher.h"
#include "AnimBlendClumpData.h"

// TODO: implement those
#define RwFreeAlign RwFree
#define RwMallocAlign(sz, algn) RwMalloc(sz)

CAnimBlendClumpData::CAnimBlendClumpData(void)
{
	numFrames = 0;
	pedPosition = nil;
	frames = nil;
	link.Init();
}

CAnimBlendClumpData::~CAnimBlendClumpData(void)
{
	link.Remove();
	if(frames)
		RwFreeAlign(frames);
}

void
CAnimBlendClumpData::SetNumberOfFrames(int n)
{
	if(frames)
		RwFreeAlign(frames);
	numFrames = n;
	frames = (AnimBlendFrameData*)RwMallocAlign(numFrames * sizeof(AnimBlendFrameData), 64);
}

void
CAnimBlendClumpData::ForAllFrames(void (*cb)(AnimBlendFrameData*, void*), void *arg)
{
	int i;
	for(i = 0; i < numFrames; i++)
		cb(&frames[i], arg);
}

STARTPATCHES
	InjectHook(0x401880, &CAnimBlendClumpData::ctor, PATCH_JUMP);
	InjectHook(0x4018B0, &CAnimBlendClumpData::dtor, PATCH_JUMP);
	InjectHook(0x4018F0, &CAnimBlendClumpData::SetNumberOfFrames, PATCH_JUMP);
	InjectHook(0x401930, &CAnimBlendClumpData::ForAllFrames, PATCH_JUMP);
ENDPATCHES
