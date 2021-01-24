#pragma once

#include "BaseModelInfo.h"

// For linking up models by name
struct TempIdeData
{
	char name[24];
	int16 id;
};
extern TempIdeData m_sTempIdeData[800];

class CSimpleModelInfo : public CBaseModelInfo
{
public:
	RpAtomic **m_atomics;
	// m_lodDistances[2] holds the near distance for LODs
	float  m_lodDistances[3];
	uint8  m_numAtomics;
	uint8  m_alpha;
	uint16 m_firstDamaged   : 2; // 0: no damage model
	                         // 1: 1 and 2 are damage models
	                         // 2: 2 is damage model
	uint16  m_wetRoadReflection    : 1;
	uint16  m_isDamaged     : 1;

	uint16  m_isBigBuilding : 1;
	uint16  m_noFade        : 1;
	uint16  m_drawLast      : 1;
	uint16  m_additive      : 1;

	uint16  m_isSubway      : 1;
	uint16  m_ignoreLight   : 1;
	uint16  m_noZwrite      : 1;
	uint16  m_noShadows     : 1;

	uint16  m_ignoreDrawDist   : 1;
	uint16  m_isCodeGlass      : 1;
	uint16  m_isArtistGlass    : 1;

	CSimpleModelInfo *m_relatedModel;

	static base::cRelocatableChunkClassInfo msClassInfo;
	static CSimpleModelInfo msClassInstance;

	CSimpleModelInfo(void) : CBaseModelInfo(MITYPE_SIMPLE) {}
	CSimpleModelInfo(ModelInfoType id) : CBaseModelInfo(id) {}
	~CSimpleModelInfo() {}
	void DeleteRwObject(void);
	RwObject *CreateInstance(void);
	RwObject *CreateInstance(RwMatrix *);
	RwObject *GetRwObject(void) { return m_atomics ? (RwObject*)m_atomics[0] : nil; }

	virtual void LoadModel(void *atomics, const void *chunk);
	virtual void Write(base::cRelocatableChunkWriter &writer);
	virtual void *WriteModel(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteThis(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteEmpty(base::cRelocatableChunkWriter &writer);

	/*virtual*/ void SetAtomic(int n, RpAtomic *atomic);

	void Init(void);
	void IncreaseAlpha(void);
	void SetLodDistances(float *dist);
	float GetLodDistance(int i);
	float GetNearDistance(void);
	float GetLargestLodDistance(void);
	RpAtomic *GetLodAtomic(int n);
	RpAtomic *GetLastAtomic(void);
	RpAtomic *GetLastAtomic(float dist);
	RpAtomic *GetAtomicFromDistance(float dist);
	RpAtomic *GetFirstAtomicFromDistance(float dist);
	void FindRelatedModel(void);
	void SetupBigBuilding(void);

	void SetNumAtomics(int n) { m_numAtomics = n; }
	CSimpleModelInfo *GetRelatedModel(void){
		return m_relatedModel; }
	void SetRelatedModel(CSimpleModelInfo *m){
		m_relatedModel = m; }
};
//static_assert(sizeof(CSimpleModelInfo) == 0x4C, "CSimpleModelInfo: error");
