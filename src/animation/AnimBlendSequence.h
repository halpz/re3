#pragma once

#include "Quaternion.h"

#ifdef MoveMemory
#undef MoveMemory	// windows shit
#endif

// TODO: put them somewhere else?
struct KeyFrame {
	CQuaternion rotation;
	float deltaTime;	// relative to previous key frame
};

struct KeyFrameTrans : KeyFrame {
	CVector translation;
};


// The sequence of key frames of one animated node
class CAnimBlendSequence
{
public:
	enum {
		KF_ROT = 1,
		KF_TRANS = 2
	};
	int32 type;
	char name[24];
	int32 numFrames;
	int16 boneTag;
	void *keyFrames;
	void *keyFramesCompressed;

	CAnimBlendSequence(void);
	virtual ~CAnimBlendSequence(void);
	void SetName(char *name);
	void SetNumFrames(int numFrames, bool translation, bool compressed);
	void RemoveQuaternionFlips(void);
	KeyFrame *GetKeyFrame(int n) {
		return type & KF_TRANS ?
			&((KeyFrameTrans*)keyFrames)[n] :
			&((KeyFrame*)keyFrames)[n];
	}
	KeyFrame *GetKeyFrameCompressed(int n) {
		return type & KF_TRANS ?
			&((KeyFrameTrans*)keyFramesCompressed)[n] :
			&((KeyFrame*)keyFramesCompressed)[n];
	}
	bool HasTranslation(void) { return !!(type & KF_TRANS); }
	bool MoveMemory(void);

	void SetBoneTag(int tag) { boneTag = tag; }
};
VALIDATE_SIZE(CAnimBlendSequence, 0x30);
