#pragma once

#include "AnimBlendSequence.h"

class CAnimBlendAssociation;

// The interpolated state between two key frames in a sequence
class CAnimBlendNode
{
public:
	// for slerp
	float theta;		// angle between quaternions
	float invSin;		// 1/sin(theta)
	// indices into array in sequence
	int32 frameA;		// next key frame
	int32 frameB;		// previous key frame
	float remainingTime;	// time until frames have to advance
	CAnimBlendSequence *sequence;
	CAnimBlendAssociation *association;

	void Init(void);
	bool Update(CVector &trans, CQuaternion &rot, float weight);
	bool NextKeyFrame(void);
	bool FindKeyFrame(float t);
	void CalcDeltas(void);
	void GetCurrentTranslation(CVector &trans, float weight);
	void GetEndTranslation(CVector &trans, float weight);
};
static_assert(sizeof(CAnimBlendNode) == 0x1C, "CAnimBlendNode: error");
