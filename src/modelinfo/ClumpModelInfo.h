#pragma once

#include "BaseModelInfo.h"

struct RwObjectNameIdAssocation
{
	const char *name;
	int32 hierId;
	uint32 flags;
};

struct RwObjectNameAssociation
{
	const char *name;
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
	union {
		int32 m_animFileIndex;
		char *m_animFileName;
	};

	static base::cRelocatableChunkClassInfo msClassInfo;
	static CClumpModelInfo msClassInstance;

	CClumpModelInfo(void) : CBaseModelInfo(MITYPE_CLUMP) { m_animFileIndex = -1; }
	CClumpModelInfo(ModelInfoType id) : CBaseModelInfo(id) { m_animFileIndex = -1; }
	~CClumpModelInfo() {}
	void DeleteRwObject(void);
	RwObject *CreateInstance(void);
	RwObject *CreateInstance(RwMatrix *);
	RwObject *GetRwObject(void) { return (RwObject*)m_clump; }

	virtual void SetClump(RpClump *);
	virtual void SetAnimFile(const char *file);
	virtual void ConvertAnimFileIndex(void);
	virtual int GetAnimFileIndex(void) { return m_animFileIndex; }

	virtual void LoadModel(void *model, const void *chunk);
	virtual void Write(base::cRelocatableChunkWriter &writer);
	virtual void *WriteModel(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteThis(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteEmpty(base::cRelocatableChunkWriter &writer);

	static RpAtomic *SetAtomicRendererCB(RpAtomic *atomic, void *data);
	void SetFrameIds(RwObjectNameIdAssocation *assocs);
	static RwFrame *FindFrameFromNameCB(RwFrame *frame, void *data);
	static RwFrame *FindFrameFromNameWithoutIdCB(RwFrame *frame, void *data);
	static RwFrame *FindFrameFromIdCB(RwFrame *frame, void *data);
	static void FillFrameArray(RpClump *clump, RwFrame **frames);
	static RwFrame *FillFrameArrayCB(RwFrame *frame, void *data);
	static RwFrame *GetFrameFromId(RpClump *clump, int32 id);
};
//static_assert(sizeof(CClumpModelInfo) == 0x34, "CClumpModelInfo: error");
