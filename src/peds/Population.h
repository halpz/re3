#pragma once

#include "Game.h"
#include "PedType.h"

class CPed;
class CVehicle;
class CDummyObject;
class CObject;

struct PedGroup
{
	int32 models[NUMMODELSPERPEDGROUP];
};

class CPopulation
{
public:
	static PedGroup ms_pPedGroups[NUMPEDGROUPS];
	static bool ms_bGivePedsWeapons;
	static int32 m_AllRandomPedsThisType;
	static float PedDensityMultiplier;
	static uint32 ms_nTotalMissionPeds;
	static int32 MaxNumberOfPedsInUse;
	static int32 MaxNumberOfPedsInUseInterior;
	static uint32 ms_nNumCivMale;
	static uint32 ms_nNumCivFemale;
	static uint32 ms_nNumCop;
	static bool bZoneChangeHasHappened;
	static uint32 ms_nNumEmergency;
	static int8 m_CountDownToPedsAtStart;
	static uint32 ms_nNumGang1;
	static uint32 ms_nNumGang2;
	static uint32 ms_nTotalPeds;
	static uint32 ms_nNumGang3;
	static uint32 ms_nTotalGangPeds;
	static uint32 ms_nNumGang4;
	static uint32 ms_nTotalCivPeds;
	static uint32 ms_nNumGang5;
	static uint32 ms_nNumDummy;
	static uint32 ms_nNumGang6;
	static uint32 ms_nNumGang9;
	static uint32 ms_nNumGang7;
	static uint32 ms_nNumGang8;

	static uint32 ms_nTotalCarPassengerPeds;
	static uint32 NumMiamiViceCops;

	static void Initialise();
	static void Update(bool);
	static void LoadPedGroups();
	static void UpdatePedCount(ePedType, bool);
	static void DealWithZoneChange(eLevelName oldLevel, eLevelName newLevel, bool);
	static CPed *AddPedInCar(CVehicle *car, bool isDriver);
	static void RemovePed(CPed *ent);
	static int32 ChooseCivilianOccupation(int32);
	static int32 ChooseNextCivilianOccupation(int32);
	static void ChooseCivilianCoupleOccupations(int32, int32&, int32&);
	static int32 ChoosePolicePedOccupation();
	static int32 ChooseGangOccupation(int);
	static void GeneratePedsAtStartOfGame();
	static float PedCreationDistMultiplier();
	static CPed *AddPed(ePedType pedType, uint32 mi, CVector const &coors, int32 modifier = 0);
	static void AddToPopulation(float, float, float, float);
	static void ManagePopulation(void);
	static void MoveCarsAndPedsOutOfAbandonedZones(void);
	static void ConvertToRealObject(CDummyObject*);
	static void ConvertToDummyObject(CObject*);
	static void ConvertAllObjectsToDummyObjects(void);
	static bool TestRoomForDummyObject(CObject*);
	static bool TestSafeForRealObject(CDummyObject*);
	static bool IsSkateable(CVector const&);
	static bool CanJeerAtStripper(int32 model);
	static void RemovePedsIfThePoolGetsFull(void);
	static bool IsMale(int32);
	static bool IsFemale(int32);
	static bool IsSunbather(int32);
	static int32 ComputeRandomisedGangSize(void);
	static bool CanSolicitPlayerInCar(int32);
	static bool CanSolicitPlayerOnFoot(int32);
	static bool IsSecurityGuard(ePedType);
	static void PlaceGangMembers(ePedType, int32, CVector const&);
	static void PlaceGangMembersInFormation(ePedType, int32, CVector const&);
	static void PlaceGangMembersInCircle(ePedType, int32, CVector const&);
	static void PlaceCouple(ePedType, int32, ePedType, int32, CVector);
	static void PlaceMallPedsAsStationaryGroup(CVector const&, int32);
	static CPed* AddDeadPedInFrontOfCar(const CVector& pos, CVehicle* pCulprit);
};
