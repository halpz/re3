#pragma once

class CPed;
class CVehicle;
enum eLevelName;

struct PedGroup
{
	int32 models[8];
};

class CPopulation
{
public:
	static PedGroup *ms_pPedGroups;	//[31]
	static bool &ms_bGivePedsWeapons;
	static int32 &m_AllRandomPedsThisType;
	static float &PedDensityMultiplier;
	static uint32 &ms_nTotalMissionPeds;
	static int32 &MaxNumberOfPedsInUse;

	static void UpdatePedCount(uint32, bool);
	static void DealWithZoneChange(eLevelName oldLevel, eLevelName newLevel, bool);
	static CPed *AddPedInCar(CVehicle *vehicle);
	static bool IsPointInSafeZone(CVector *coors);
};
