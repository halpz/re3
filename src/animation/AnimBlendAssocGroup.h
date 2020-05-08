#pragma once

class CAnimBlendAssociation;
struct CAnimBlock;

class CAnimBlendAssocGroup
{
public:
	CAnimBlock *animBlock;
	CAnimBlendAssociation *assocList;
	int32 numAssociations;
	int32 firstAnimId;
	int32 groupId;	// id of self in ms_aAnimAssocGroups

	CAnimBlendAssocGroup(void);
	~CAnimBlendAssocGroup(void);
	void DestroyAssociations(void);
	CAnimBlendAssociation *GetAnimation(uint32 id);
	CAnimBlendAssociation *GetAnimation(const char *name);
	CAnimBlendAssociation *CopyAnimation(uint32 id);
	CAnimBlendAssociation *CopyAnimation(const char *name);
	void CreateAssociations(const char *name);
	void CreateAssociations(const char *blockName, RpClump *clump, const char **animNames, int numAssocs);
};
