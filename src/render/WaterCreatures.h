#pragma once
#include "Object.h"

enum eFishSlotState {
	WATER_CREATURE_ALLOCATED = 0,
	WATER_CREATURE_ACTIVE,
	WATER_CREATURE_UPDATE,
	WATER_CREATURE_TO_REMOVE,
	WATER_CREATURE_DISABLED
};

class CWaterCreature {
public:
	CObject *m_pObj;
	float m_fRightMult;
	float m_fZTurnSpeed;
	int32 m_alpha;
	float m_fWaterDepth;
	int32 m_state;

	CWaterCreature();
	~CWaterCreature();
	void Allocate(CObject *pObj, float fRightMult, float fZTurnSpeed, float fWaterDepth, uint32 alpha, eFishSlotState state);
	void Free();
	void Initialise(CObject *pObj, float fRightMult, float fZTurnSpeed, float fWaterDepth, uint32 alpha, eFishSlotState state);
};

class CWaterCreatures {

public:
	static CWaterCreature aWaterCreatures[NUM_WATER_CREATURES];
	static int32 nNumActiveSeaLifeForms;
	static CObject *CreateSeaLifeForm(CVector const& pos, int16 modelID, int32 zRotAngle);
	static void CreateOne(CVector const& pos, int32 modelID);
	static void UpdateAll();
	static void FreeFishStructSlot(CWaterCreature *wc);
	static bool IsSpaceForMoreWaterCreatures();
	static float CalculateFishHeading(CVector const& pos1, CVector const& pos2);
	static void RemoveAll();
	static CWaterCreature* GetFishStructSlot();
};

struct WaterCreatureProperties {
	int16 *modelID;
	float fRightMult;
	float fLevel;
	float fUnknown; //unused
	float fWaterDepth;
};