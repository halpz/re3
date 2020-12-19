#include "common.h"

#include "AnimBlendSequence.h"
#include "MemoryHeap.h"

//--MIAMI: file done

CAnimBlendSequence::CAnimBlendSequence(void)
{
	type = 0;
	numFrames = 0;
	keyFrames = nil;
	keyFramesCompressed = nil;
	boneTag = -1;
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

#ifdef USE_CUSTOM_ALLOCATOR
bool
CAnimBlendSequence::MoveMemory(void)
{
	if(keyFrames){
		void *newaddr = gMainHeap.MoveMemory(keyFrames);
		if(newaddr != keyFrames){
			keyFrames = newaddr;
			return true;
		}
	}else if(keyFramesCompressed){
		void *newaddr = gMainHeap.MoveMemory(keyFramesCompressed);
		if(newaddr != keyFramesCompressed){
			keyFramesCompressed = newaddr;
			return true;
		}
	}
	return false;
}
#endif

