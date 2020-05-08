#include "common.h"

#include "AnimBlendSequence.h"

//--MIAMI: file done

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
	if(keyFramesCompressed)
		RwFree(keyFramesCompressed);
}

void
CAnimBlendSequence::SetName(char *name)
{
	strncpy(this->name, name, 24);
}

void
CAnimBlendSequence::SetNumFrames(int numFrames, bool translation, bool compressed)
{
	if(translation){
		type |= KF_ROT | KF_TRANS;
		if(compressed)
			keyFramesCompressed = RwMalloc(sizeof(KeyFrameTrans) * numFrames);
		else
			keyFrames = RwMalloc(sizeof(KeyFrameTrans) * numFrames);
	}else{
		type |= KF_ROT;
		if(compressed)
			keyFramesCompressed = RwMalloc(sizeof(KeyFrame) * numFrames);
		else
			keyFrames = RwMalloc(sizeof(KeyFrame) * numFrames);
	}
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
