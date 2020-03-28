#pragma once

#include "AnimBlendList.h"
#include "AnimBlendNode.h"
#include "AnimBlendHierarchy.h"

enum {
	// TODO
	ASSOC_RUNNING = 1,
	ASSOC_REPEAT = 2,
	ASSOC_DELETEFADEDOUT = 4,
	ASSOC_FADEOUTWHENDONE = 8,
	ASSOC_PARTIAL = 0x10,
	ASSOC_MOVEMENT = 0x20,	// ???
	ASSOC_HAS_TRANSLATION = 0x40,
	ASSOC_FLAG80 = 0x80, // used for footstep sound calculation
	ASSOC_FLAG100 = 0x100,
	ASSOC_FLAG200 = 0x200,
	ASSOC_FLAG400 = 0x400,	// unused, blending it with move anims makes them stop. 0x800 in VC
	ASSOC_FLAG800 = 0x800, // anims that we fall to front. 0x1000 in VC
	ASSOC_HAS_X_TRANSLATION = 0x1000,
	// 0x2000 is vehicle anims in VC
};

// Anim hierarchy associated with a clump
// Holds the interpolated state of all nodes.
// Also used as template for other clumps.
class CAnimBlendAssociation
{
public:
	enum {
		// callbackType
		CB_NONE,
		CB_FINISH,
		CB_DELETE
	};

	CAnimBlendLink link;

	int numNodes;			// taken from CAnimBlendClumpData::numFrames
	// NB: Order of these depends on order of nodes in Clump this was built from
	CAnimBlendNode *nodes;
	CAnimBlendHierarchy *hierarchy;
	float blendAmount;
	float blendDelta;	// how much blendAmount changes over time
	float currentTime;
	float speed;
	float timeStep;
	int32 animId;
	int32 flags;
	int32 callbackType;
	void (*callback)(CAnimBlendAssociation*, void*);
	void *callbackArg;

	bool IsRunning(void) { return !!(flags & ASSOC_RUNNING); }
	bool IsRepeating(void) { return !!(flags & ASSOC_REPEAT); }
	bool IsPartial(void) { return !!(flags & ASSOC_PARTIAL); }
	bool IsMovement(void) { return !!(flags & ASSOC_MOVEMENT); }
	bool HasTranslation(void) { return !!(flags & ASSOC_HAS_TRANSLATION); }
	bool HasXTranslation(void) { return !!(flags & ASSOC_HAS_X_TRANSLATION); }

	float GetBlendAmount(float weight) { return IsPartial() ? blendAmount : blendAmount*weight; }
	CAnimBlendNode *GetNode(int i) { return &nodes[i]; }

	CAnimBlendAssociation(void);
	CAnimBlendAssociation(CAnimBlendAssociation &other);
	virtual ~CAnimBlendAssociation(void);
	void AllocateAnimBlendNodeArray(int n);
	void FreeAnimBlendNodeArray(void);
	void Init(RpClump *clump, CAnimBlendHierarchy *hier);
	void Init(CAnimBlendAssociation &assoc);
	void SetBlend(float amount, float delta);
	void SetFinishCallback(void (*callback)(CAnimBlendAssociation*, void*), void *arg);
	void SetDeleteCallback(void (*callback)(CAnimBlendAssociation*, void*), void *arg);
	void SetCurrentTime(float time);
	void SyncAnimation(CAnimBlendAssociation *other);
	void Start(float time);
	void UpdateTime(float timeDelta, float relSpeed);
	bool UpdateBlend(float timeDelta);

	void SetRun(void) { flags |= ASSOC_RUNNING; }

	inline float GetTimeLeft() { return hierarchy->totalLength - currentTime; }

	static CAnimBlendAssociation *FromLink(CAnimBlendLink *l) {
		return (CAnimBlendAssociation*)((uint8*)l - offsetof(CAnimBlendAssociation, link));
	}
};
static_assert(sizeof(CAnimBlendAssociation) == 0x40, "CAnimBlendAssociation: error");
