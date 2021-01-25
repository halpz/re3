#pragma once

#include "ClumpModelInfo.h"
#include "ColModel.h"
#include "PedType.h"

enum PedNode {
	PED_TORSO = 0,	// has no bone!
	PED_MID,
	PED_HEAD,
	PED_UPPERARML,
	PED_UPPERARMR,
	PED_HANDL,
	PED_HANDR,
	PED_UPPERLEGL,
	PED_UPPERLEGR,
	PED_FOOTL,
	PED_FOOTR,
	PED_LOWERLEGR,
	PED_LOWERLEGL,

	PED_FOREARML,
	PED_FOREARMR,
	PED_CLAVICLEL,
	PED_CLAVICLER,
	PED_NECK,

	PED_NODE_MAX
};

class CPedModelInfo : public CClumpModelInfo
{
public:
	uint32 m_animGroup;
	ePedType m_pedType;
	ePedStats m_pedStatType;
	uint32 m_carsCanDrive;
	CColModel *m_hitColModel;
	int8 radio1, radio2;

	static base::cRelocatableChunkClassInfo msClassInfo;
	static CPedModelInfo msClassInstance;
	static RwObjectNameIdAssocation m_pPedIds[PED_NODE_MAX];

	CPedModelInfo(void) : CClumpModelInfo(MITYPE_PED) { m_hitColModel = nil; }
	~CPedModelInfo(void) { delete m_hitColModel; }
	void DeleteRwObject(void);
	void SetClump(RpClump *);

	virtual void LoadModel(void *model, const void *chunk);
	virtual void Write(base::cRelocatableChunkWriter &writer);
	virtual void *WriteModel(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteThis(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteEmpty(base::cRelocatableChunkWriter &writer);

	bool CreateHitColModelSkinned(RpClump *clump);
	CColModel *GetHitColModel(void) { return m_hitColModel; }
	CColModel *AnimatePedColModelSkinned(RpClump *clump);
	CColModel *AnimatePedColModelSkinnedWorld(RpClump *clump);
};
