#pragma once

#include "Quaternion.h"

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
#ifdef PED_SKIN
	int16 boneTag;
#endif
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
	// TODO? these are unused
//	void Uncompress(void);
//	void CompressKeyframes(void);
//	void RemoveUncompressedData(void);

#ifdef PED_SKIN
	void SetBoneTag(int tag) { boneTag = tag; }
#endif
};
#ifndef PED_SKIN
VALIDATE_SIZE(CAnimBlendSequence, 0x2C);
#endif
