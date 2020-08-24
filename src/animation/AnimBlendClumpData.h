#pragma once

#include "AnimBlendList.h"


// TODO: put somewhere else
struct AnimBlendFrameData
{
	enum {
		IGNORE_ROTATION = 2,
		IGNORE_TRANSLATION = 4,
		VELOCITY_EXTRACTION = 8,
		VELOCITY_EXTRACTION_3D = 0x10,
		UPDATE_KEYFRAMES = 0x20,
		UNK_COMPRESSED = 0x40,
	};

	uint8 flag;
	RwV3d resetPos;
#ifdef PED_SKIN
	union {
		RwFrame *frame;
		RpHAnimStdInterpFrame *hanimFrame;
	};
	int32 nodeID;
#else
	RwFrame *frame;
#endif
};
#ifndef PED_SKIN
VALIDATE_SIZE(AnimBlendFrameData, 0x14);
#endif


class CAnimBlendClumpData
{
public:
	CAnimBlendLink link;
	int32 numFrames;
	CVector *velocity;
	// order of frames is determined by RW hierarchy
	AnimBlendFrameData *frames;

	CAnimBlendClumpData(void);
	~CAnimBlendClumpData(void);
	void SetNumberOfFrames(int n);
#ifdef PED_SKIN
	void SetNumberOfBones(int n) { SetNumberOfFrames(n); }
#endif
	void ForAllFrames(void (*cb)(AnimBlendFrameData*, void*), void *arg);
};
