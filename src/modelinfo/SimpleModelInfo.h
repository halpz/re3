#pragma once

#include "BaseModelInfo.h"

class CSimpleModelInfo : public CBaseModelInfo
{
public:
	// atomics[2] is often a pointer to the non-LOD modelinfo
	RpAtomic *m_atomics[3];
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

	CSimpleModelInfo(void) : CBaseModelInfo(MITYPE_SIMPLE) {}
	CSimpleModelInfo(ModelInfoType id) : CBaseModelInfo(id) {}
	~CSimpleModelInfo() {}
	void DeleteRwObject(void);
	RwObject *CreateInstance(void);
	RwObject *CreateInstance(RwMatrix *);
	RwObject *GetRwObject(void) { return (RwObject*)m_atomics[0]; }

	virtual void SetAtomic(int n, RpAtomic *atomic);

	void Init(void);
	void IncreaseAlpha(void);
	void SetLodDistances(float *dist);
	float GetLodDistance(int i);
	float GetNearDistance(void);
	float GetLargestLodDistance(void);
	RpAtomic *GetAtomicFromDistance(float dist);
	RpAtomic *GetFirstAtomicFromDistance(float dist);
	void FindRelatedModel(int32 minID, int32 maxID);
	void SetupBigBuilding(int32 minID, int32 maxID);

	void SetNumAtomics(int n) { m_numAtomics = n; }
	CSimpleModelInfo *GetRelatedModel(void){
		return (CSimpleModelInfo*)m_atomics[2]; }
	void SetRelatedModel(CSimpleModelInfo *m){
		m_atomics[2] = (RpAtomic*)m; }
};
//static_assert(sizeof(CSimpleModelInfo) == 0x4C, "CSimpleModelInfo: error");
