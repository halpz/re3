#pragma once

#include "AnimBlendHierarchy.h"
#include "AnimationId.h"

enum AssocGroupId
{
	ASSOCGRP_STD,
	ASSOCGRP_PLAYER,
	ASSOCGRP_PLAYERROCKET,
	ASSOCGRP_PLAYER1ARMED,
	ASSOCGRP_PLAYER2ARMED,
	ASSOCGRP_PLAYERBBBAT,
	ASSOCGRP_SHUFFLE,
	ASSOCGRP_OLD,
	ASSOCGRP_GANG1,
	ASSOCGRP_GANG2,
	ASSOCGRP_FAT,
	ASSOCGRP_OLDFAT,
	ASSOCGRP_WOMAN,
	ASSOCGRP_WOMANSHOP,
	ASSOCGRP_BUSYWOMAN,
	ASSOCGRP_SEXYWOMAN,
	ASSOCGRP_OLDWOMAN,
	ASSOCGRP_FATWOMAN,
	ASSOCGRP_PANICCHUNKY,
	ASSOCGRP_PLAYERBACK,
	ASSOCGRP_PLAYERLEFT,
	ASSOCGRP_PLAYERRIGHT,
	ASSOCGRP_ROCKETBACK,
	ASSOCGRP_ROCKETLEFT,
	ASSOCGRP_ROCKETRIGHT,

	NUM_ANIM_ASSOC_GROUPS	// should be 61 in the end
};

class CAnimBlendAssociation;
class CAnimBlendAssocGroup;

#define MAX_ANIMBLOCK_NAME 20

// A block of hierarchies
struct CAnimBlock
{
	char name[MAX_ANIMBLOCK_NAME];
	bool isLoaded;
	int16 refCount;
	int32 firstIndex;	// first animtion in ms_aAnimations
	int32 numAnims;
};

struct AnimAssocDesc
{
	int32 animId;
	int32 flags;
};

struct AnimAssocDefinition
{
	char const *name;
	char const *blockName;
	int32 modelIndex;
	int32 numAnims;
	char const **animNames;
	AnimAssocDesc *animDescs;
};

class CAnimManager
{
	static const AnimAssocDefinition ms_aAnimAssocDefinitions[NUM_ANIM_ASSOC_GROUPS];
	static CAnimBlock ms_aAnimBlocks[NUMANIMBLOCKS];
	static CAnimBlendHierarchy ms_aAnimations[NUMANIMATIONS];
	static int32 ms_numAnimBlocks;
	static int32 ms_numAnimations;
	static CAnimBlendAssocGroup *ms_aAnimAssocGroups;
	static CLinkList<CAnimBlendHierarchy*> ms_animCache;
public:

	static void Initialise(void);
	static void Shutdown(void);
	static void UncompressAnimation(CAnimBlendHierarchy *anim);
	static void RemoveFromUncompressedCache(CAnimBlendHierarchy *hier);
	static CAnimBlock *GetAnimationBlock(int32 block) { return &ms_aAnimBlocks[block]; }
	static CAnimBlock *GetAnimationBlock(const char *name);
	static int32 GetAnimationBlockIndex(const char *name);
	static int32 RegisterAnimBlock(const char *name);
	static int32 GetNumRefsToAnimBlock(int32 block);
	static void AddAnimBlockRef(int32 block);
	static void RemoveAnimBlockRefWithoutDelete(int32 block);
	static void RemoveAnimBlockRef(int32 block);
	static void RemoveAnimBlock(int32 block);
	static CAnimBlendHierarchy *GetAnimation(const char *name, CAnimBlock *animBlock);
	static CAnimBlendHierarchy *GetAnimation(int32 n) { return &ms_aAnimations[n]; }
	static const char *GetAnimGroupName(AssocGroupId groupId);
	static CAnimBlendAssociation *CreateAnimAssociation(AssocGroupId groupId, AnimationId animId);
	static CAnimBlendAssociation *GetAnimAssociation(AssocGroupId groupId, AnimationId animId);
	static CAnimBlendAssociation *GetAnimAssociation(AssocGroupId groupId, const char *name);
	static CAnimBlendAssociation *AddAnimation(RpClump *clump, AssocGroupId groupId, AnimationId animId);
	static CAnimBlendAssociation *AddAnimationAndSync(RpClump *clump, CAnimBlendAssociation *syncanim, AssocGroupId groupId, AnimationId animId);
	static CAnimBlendAssociation *BlendAnimation(RpClump *clump, AssocGroupId groupId, AnimationId animId, float delta);
	static void LoadAnimFiles(void);
	static void LoadAnimFile(const char *filename);
	static void LoadAnimFile(RwStream *stream, bool compress, char (*somename)[32] = nil);
	static void CreateAnimAssocGroups(void);
	static void RemoveLastAnimFile(void);
};
