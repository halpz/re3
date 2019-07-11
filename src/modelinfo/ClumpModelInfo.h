#pragma once

#include "BaseModelInfo.h"

struct RwObjectNameIdAssocation
{
	char *name;
	int32 hierId;
	uint32 flags;
};

struct RwObjectNameAssociation
{
	char *name;
	RwFrame *frame;
};

struct RwObjectIdAssociation
{
	int32 id;
	RwFrame *frame;
};

enum {
	CLUMP_FLAG_NO_HIERID = 0x1,
};


class CClumpModelInfo : public CBaseModelInfo
{
public:
	RpClump *m_clump;

	CClumpModelInfo(void) : CBaseModelInfo(MITYPE_CLUMP) {}
	CClumpModelInfo(ModeInfoType id) : CBaseModelInfo(id) {}
	~CClumpModelInfo() {}
	void DeleteRwObject(void);
	RwObject *CreateInstance(void);
	RwObject *CreateInstance(RwMatrix *);
	RwObject *GetRwObject(void) { return (RwObject*)m_clump; }

	virtual void SetClump(RpClump *);

	static RpAtomic *SetAtomicRendererCB(RpAtomic *atomic, void *data);
	void SetFrameIds(RwObjectNameIdAssocation *assocs);
	static RwFrame *FindFrameFromNameCB(RwFrame *frame, void *data);
	static RwFrame *FindFrameFromNameWithoutIdCB(RwFrame *frame, void *data);
	static RwFrame *FindFrameFromIdCB(RwFrame *frame, void *data);
	static void FillFrameArray(RpClump *clump, RwFrame **frames);
	static RwFrame *FillFrameArrayCB(RwFrame *frame, void *data);
	static RwFrame *GetFrameFromId(RpClump *clump, int32 id);
};
static_assert(sizeof(CClumpModelInfo) == 0x34, "CClumpModelInfo: error");
