#include "common.h"
#include "patcher.h"
#include "AnimBlendClumpData.h"
#include "RwHelper.h"


CAnimBlendClumpData::CAnimBlendClumpData(void)
{
	numFrames = 0;
	velocity = nil;
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

#include <new>

class CAnimBlendClumpData_ : public CAnimBlendClumpData
{
public:
	CAnimBlendClumpData *ctor(void) { return ::new (this) CAnimBlendClumpData(); }
	void dtor(void) { this->CAnimBlendClumpData::~CAnimBlendClumpData(); }
};


STARTPATCHES
	InjectHook(0x401880, &CAnimBlendClumpData_::ctor, PATCH_JUMP);
	InjectHook(0x4018B0, &CAnimBlendClumpData_::dtor, PATCH_JUMP);
	InjectHook(0x4018F0, &CAnimBlendClumpData::SetNumberOfFrames, PATCH_JUMP);
	InjectHook(0x401930, &CAnimBlendClumpData::ForAllFrames, PATCH_JUMP);
ENDPATCHES
