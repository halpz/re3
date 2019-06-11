#include "common.h"
#include "patcher.h"
#include "AnimBlendSequence.h"

CAnimBlendSequence::CAnimBlendSequence(void)
{
	type = 0;
	numFrames = 0;
	keyFrames = nil;
	keyFramesCompressed = nil;
#ifdef PED_SKIN
	boneTag = -1;
#endif
}

CAnimBlendSequence::~CAnimBlendSequence(void)
{
	if(keyFrames)
		RwFree(keyFrames);
}

void
CAnimBlendSequence::SetName(char *name)
{
	strncpy(this->name, name, 24);
}

void
CAnimBlendSequence::SetNumFrames(int numFrames, bool translation)
{
	int sz;

	if(translation){
		sz = sizeof(KeyFrameTrans);
		type |= KF_ROT | KF_TRANS;
	}else{
		sz = sizeof(KeyFrame);
		type |= KF_ROT;
	}
	keyFrames = RwMalloc(sz * numFrames);
	this->numFrames = numFrames;
}

void
CAnimBlendSequence::RemoveQuaternionFlips(void)
{
	int i;
	CQuaternion last;
	KeyFrame *frame;

	if(numFrames < 2)
		return;

	frame = GetKeyFrame(0);
	last = frame->rotation;
	for(i = 1; i < numFrames; i++){
		frame = GetKeyFrame(i);
		if(DotProduct(last, frame->rotation) < 0.0f)
			frame->rotation = -frame->rotation;
		last = frame->rotation;
	}
}

STARTPATCHES
	InjectHook(0x402330, &CAnimBlendSequence::SetName, PATCH_JUMP);
	InjectHook(0x402350, &CAnimBlendSequence::SetNumFrames, PATCH_JUMP);
	InjectHook(0x4023A0, &CAnimBlendSequence::RemoveQuaternionFlips, PATCH_JUMP);
ENDPATCHES
