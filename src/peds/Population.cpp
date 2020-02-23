#include "common.h"
#include "patcher.h"
#include "Game.h"
#include "General.h"
#include "World.h"
#include "Population.h"
#include "FileMgr.h"
#include "Gangs.h"
#include "ModelIndices.h"
#include "Zones.h"
#include "CivilianPed.h"
#include "EmergencyPed.h"
#include "Replay.h"
#include "CutsceneMgr.h"
#include "CarCtrl.h"
#include "IniFile.h"
#include "VisibilityPlugins.h"
#include "PedPlacement.h"
#include "DummyObject.h"

#define CREATION_DIST_MULT_TO_DIST 40.0f
#define CREATION_RANGE 10.0f // Being added over the CREATION_DIST_MULT_TO_DIST.
#define OFFSCREEN_CREATION_MULT 0.5f
// Also there are some hardcoded values in GeneratePedsAtStartOfGame.

// TO-DO: These are hard-coded, reverse them.
// More clearly they're transition areas between zones.
RegenerationPoint (&aSafeZones)[8] = *(RegenerationPoint(*)[8]) * (uintptr*)0x5FA578;

PedGroup (&CPopulation::ms_pPedGroups)[NUMPEDGROUPS] = *(PedGroup(*)[NUMPEDGROUPS]) * (uintptr*)0x6E9248;
bool &CPopulation::ms_bGivePedsWeapons = *(bool*)0x95CCF6;
int32 &CPopulation::m_AllRandomPedsThisType = *(int32*)0x5FA570;
float &CPopulation::PedDensityMultiplier = *(float*)0x5FA56C;
uint32 &CPopulation::ms_nTotalMissionPeds = *(uint32*)0x8F5F70;
int32 &CPopulation::MaxNumberOfPedsInUse = *(int32*)0x5FA574;
uint32& CPopulation::ms_nNumCivMale = *(uint32*)0x8F2548;
uint32& CPopulation::ms_nNumCivFemale = *(uint32*)0x8F5F44;
uint32& CPopulation::ms_nNumCop = *(uint32*)0x885AFC;
bool& CPopulation::bZoneChangeHasHappened = *(bool*)0x95CD79;
uint32& CPopulation::ms_nNumEmergency = *(uint32*)0x94071C;
int8& CPopulation::m_CountDownToPedsAtStart = *(int8*)0x95CD4F;
uint32& CPopulation::ms_nNumGang1 = *(uint32*)0x8F1B1C;
uint32& CPopulation::ms_nNumGang2 = *(uint32*)0x8F1B14;
uint32& CPopulation::ms_nTotalPeds = *(uint32*)0x95CB50;
uint32& CPopulation::ms_nNumGang3 = *(uint32*)0x8F2548;
uint32& CPopulation::ms_nTotalGangPeds = *(uint32*)0x885AF0;
uint32& CPopulation::ms_nNumGang4 = *(uint32*)0x8F1B2C;
uint32& CPopulation::ms_nTotalCivPeds = *(uint32*)0x8F2C3C;
uint32& CPopulation::ms_nNumGang5 = *(uint32*)0x8F1B30;
uint32& CPopulation::ms_nNumDummy = *(uint32*)0x8F1A98;
uint32& CPopulation::ms_nNumGang6 = *(uint32*)0x8F1B20;
uint32& CPopulation::ms_nNumGang9 = *(uint32*)0x8F1B10;
uint32& CPopulation::ms_nNumGang7 = *(uint32*)0x8F1B28;
uint32& CPopulation::ms_nNumGang8 = *(uint32*)0x8F1B0C;
CVector &CPopulation::RegenerationPoint_a = *(CVector*)0x8E2AA4;
CVector &CPopulation::RegenerationPoint_b = *(CVector*)0x8E2A98;
CVector &CPopulation::RegenerationForward = *(CVector*)0x8F1AD4;

WRAPPER CPed *CPopulation::AddPedInCar(CVehicle *vehicle) { EAXJMP(0x4F5800); }
WRAPPER void CPopulation::ManagePopulation(void) { EAXJMP(0x4F3B90); }
WRAPPER void CPopulation::MoveCarsAndPedsOutOfAbandonedZones(void) { EAXJMP(0x4F5BE0); }
WRAPPER void CPopulation::ConvertToRealObject(CDummyObject* obj) { EAXJMP(0x4F45A0); }

void
CPopulation::Initialise()
{
	debug("Initialising CPopulation...\n");

	ms_nNumCivMale = 0;
	ms_nNumCivFemale = 0;
	ms_nNumCop = 0;
	ms_nNumEmergency = 0;
	ms_nNumGang1 = 0;
	ms_nNumGang2 = 0;
	ms_nNumGang3 = 0;
	ms_nNumGang4 = 0;
	ms_nNumGang5 = 0;
	ms_nNumGang6 = 0;
	ms_nNumGang7 = 0;
	ms_nNumGang8 = 0;
	ms_nNumGang9 = 0;
	ms_nNumDummy = 0;

	m_AllRandomPedsThisType = -1;
	PedDensityMultiplier = 1.0;
	bZoneChangeHasHappened = false;
	m_CountDownToPedsAtStart = 2;
	
	ms_nTotalMissionPeds = 0;
	ms_nTotalPeds = 0;
	ms_nTotalGangPeds = 0;
	ms_nTotalCivPeds = 0;

	LoadPedGroups();
	DealWithZoneChange(LEVEL_COMMERCIAL, LEVEL_INDUSTRIAL, true);

	debug("CPopulation ready\n");
}

void
CPopulation::RemovePed(CPed *ent)
{
	// CPed dtor already does that
	// CWorld::Remove((CEntity*)ent);
	delete ent;
}

int32
CPopulation::ChooseCivilianOccupation(int32 group)
{
	return ms_pPedGroups[group].models[CGeneral::GetRandomNumberInRange(0, NUMMODELSPERPEDGROUP)];
}

eCopType
CPopulation::ChoosePolicePedOccupation()
{
	CGeneral::GetRandomNumber();
	return COP_STREET;
}

void
CPopulation::LoadPedGroups()
{
	int fd;
	char line[1024];
	int nextPedGroup = 0;
	// char unused[16]; // non-existence of that in mobile kinda verifies that
	char modelName[256];

	CFileMgr::ChangeDir("\\DATA\\");
	fd = CFileMgr::OpenFile("PEDGRP.DAT", "r");
	CFileMgr::ChangeDir("\\");
	while (CFileMgr::ReadLine(fd, line, sizeof(line))) {
		int end;
		// find end of line
		for (end = 0; ; end++) {
			if (line[end] == '\n')
				break;
			if (line[end] == ',' || line[end] == '\r')
				line[end] = ' ';
		}
		line[end] = '\0';
		int cursor = 0;
		int i;
		for (i = 0; i < NUMMODELSPERPEDGROUP; i++) {
			while (line[cursor] <= ' ' && line[cursor] != '\0')
				++cursor;

			if (line[cursor] == '#')
				break;

			// find next whitespace
			int nextWhitespace;
			for (nextWhitespace = cursor; line[nextWhitespace] > ' '; ++nextWhitespace)
				;

			if (cursor == nextWhitespace)
				break;
			
			// read until next whitespace
			strncpy(modelName, &line[cursor], nextWhitespace - cursor);
			modelName[nextWhitespace - cursor] = '\0';
			CModelInfo::GetModelInfo(modelName, &ms_pPedGroups[nextPedGroup].models[i]);
			cursor = nextWhitespace;
		}
		if (i == NUMMODELSPERPEDGROUP)
			nextPedGroup++;
	}
	CFileMgr::CloseFile(fd);
}

void
CPopulation::UpdatePedCount(ePedType pedType, bool decrease)
{
	if (decrease) {
		switch (pedType) {
			case PEDTYPE_PLAYER1:
			case PEDTYPE_PLAYER2:
			case PEDTYPE_PLAYER3:
			case PEDTYPE_PLAYER4:
			case PEDTYPE_UNUSED1:
			case PEDTYPE_SPECIAL:
				return;
			case PEDTYPE_CIVMALE:
				--ms_nNumCivMale;
				break;
			case PEDTYPE_CIVFEMALE:
				--ms_nNumCivFemale;
				break;
			case PEDTYPE_COP:
				--ms_nNumCop;
				break;
			case PEDTYPE_GANG1:
				--ms_nNumGang1;
				break;
			case PEDTYPE_GANG2:
				--ms_nNumGang2;
				break;
			case PEDTYPE_GANG3:
				--ms_nNumGang3;
				break;
			case PEDTYPE_GANG4:
				--ms_nNumGang4;
				break;
			case PEDTYPE_GANG5:
				--ms_nNumGang5;
				break;
			case PEDTYPE_GANG6:
				--ms_nNumGang6;
				break;
			case PEDTYPE_GANG7:
				--ms_nNumGang7;
				break;
			case PEDTYPE_GANG8:
				--ms_nNumGang8;
				break;
			case PEDTYPE_GANG9:
				--ms_nNumGang9;
				break;
			case PEDTYPE_EMERGENCY:
			case PEDTYPE_FIREMAN:
				--ms_nNumEmergency;
				break;
			case PEDTYPE_CRIMINAL:
				--ms_nNumCivMale;
				break;
			case PEDTYPE_PROSTITUTE:
				--ms_nNumCivFemale;
				break;
			case PEDTYPE_UNUSED2:
				--ms_nNumDummy;
				break;
			default:
				Error("Unknown ped type, UpdatePedCount, Population.cpp");
				break;
		}
	} else {
		switch (pedType) {
			case PEDTYPE_PLAYER1:
			case PEDTYPE_PLAYER2:
			case PEDTYPE_PLAYER3:
			case PEDTYPE_PLAYER4:
			case PEDTYPE_UNUSED1:
			case PEDTYPE_SPECIAL:
				return;
			case PEDTYPE_CIVMALE:
				++ms_nNumCivMale;
				break;
			case PEDTYPE_CIVFEMALE:
				++ms_nNumCivFemale;
				break;
			case PEDTYPE_COP:
				++ms_nNumCop;
				break;
			case PEDTYPE_GANG1:
				++ms_nNumGang1;
				break;
			case PEDTYPE_GANG2:
				++ms_nNumGang2;
				break;
			case PEDTYPE_GANG3:
				++ms_nNumGang3;
				break;
			case PEDTYPE_GANG4:
				++ms_nNumGang4;
				break;
			case PEDTYPE_GANG5:
				++ms_nNumGang5;
				break;
			case PEDTYPE_GANG6:
				++ms_nNumGang6;
				break;
			case PEDTYPE_GANG7:
				++ms_nNumGang7;
				break;
			case PEDTYPE_GANG8:
				++ms_nNumGang8;
				break;
			case PEDTYPE_GANG9:
				++ms_nNumGang9;
				break;
			case PEDTYPE_EMERGENCY:
			case PEDTYPE_FIREMAN:
				++ms_nNumEmergency;
				break;
			case PEDTYPE_CRIMINAL:
				++ms_nNumCivMale;
				break;
			case PEDTYPE_PROSTITUTE:
				++ms_nNumCivFemale;
				break;
			case PEDTYPE_UNUSED2:
				++ms_nNumDummy;
				break;
			default:
				Error("Unknown ped type, UpdatePedCount, Population.cpp");
				break;
		}
	}
}

int
CPopulation::ChooseGangOccupation(int gangId)
{
	int8 modelOverride = CGangs::GetGangPedModelOverride(gangId);

	// All gangs have 2 models
	int firstGangModel = 2 * gangId + MI_GANG01;

	// GetRandomNumberInRange never returns max. value
	if (modelOverride == -1)
		return CGeneral::GetRandomNumberInRange(firstGangModel, firstGangModel + 2);

	if (modelOverride != 0)
		return firstGangModel + 1;
	else
		return firstGangModel;
}

void
CPopulation::DealWithZoneChange(eLevelName oldLevel, eLevelName newLevel, bool forceIndustrialZone)
{
	bZoneChangeHasHappened = true;

	CVector findSafeZoneAround;
	int safeZone;

	if (forceIndustrialZone) {
		// Commercial to industrial transition area on Callahan Bridge
		findSafeZoneAround.x = 690.0f;
		findSafeZoneAround.y = -920.0f;
		findSafeZoneAround.z = 42.0f;
	} else {
		findSafeZoneAround = FindPlayerCoors();
	}
	eLevelName level;
	FindCollisionZoneForCoors(&findSafeZoneAround, &safeZone, &level);

	// We aren't in a "safe zone", find closest one
	if (safeZone < 0)
		FindClosestZoneForCoors(&findSafeZoneAround, &safeZone, oldLevel, newLevel);

	// No, there should be one!
	if (safeZone < 0) {
		if (newLevel == LEVEL_INDUSTRIAL) {
			safeZone = 0;
		} else if (newLevel == LEVEL_SUBURBAN) {
			safeZone = 4;
		}
	}

	if (aSafeZones[safeZone].srcLevel == newLevel) {
		CPopulation::RegenerationPoint_a = aSafeZones[safeZone].srcPosA;
		CPopulation::RegenerationPoint_b = aSafeZones[safeZone].srcPosB;
		CPopulation::RegenerationForward = aSafeZones[safeZone].destPosA - aSafeZones[safeZone].srcPosA;
		RegenerationForward.Normalise();
	} else if (aSafeZones[safeZone].destLevel == newLevel) {
		CPopulation::RegenerationPoint_a = aSafeZones[safeZone].destPosA;
		CPopulation::RegenerationPoint_b = aSafeZones[safeZone].destPosB;
		CPopulation::RegenerationForward = aSafeZones[safeZone].srcPosA - aSafeZones[safeZone].destPosA;
		RegenerationForward.Normalise();
	}
}

void
CPopulation::FindCollisionZoneForCoors(CVector *coors, int *safeZoneOut, eLevelName *levelOut)
{
	*safeZoneOut = -1;
	for (int i = 0; i < ARRAY_SIZE(aSafeZones); i++) {
		if (coors->x > aSafeZones[i].x1 && coors->x < aSafeZones[i].x2) {
			if (coors->y > aSafeZones[i].y1 && coors->y < aSafeZones[i].y2) {
				if (coors->z > aSafeZones[i].z1 && coors->z < aSafeZones[i].z2)
					*safeZoneOut = i;
			}
		}
	}
	// Then it's transition area
	if (*safeZoneOut >= 0)
		*levelOut = LEVEL_NONE;
	else
		*levelOut = CTheZones::GetLevelFromPosition(*coors);
}

void
CPopulation::FindClosestZoneForCoors(CVector *coors, int *safeZoneOut, eLevelName level1, eLevelName level2)
{
	float minDist = 10000000.0f;
	int closestSafeZone = -1;
	for (int i = 0; i < ARRAY_SIZE(aSafeZones); i++) {
		if ((level1 == aSafeZones[i].srcLevel || level1 == aSafeZones[i].destLevel) && (level2 == aSafeZones[i].srcLevel || level2 == aSafeZones[i].destLevel)) {
			CVector2D safeZoneDistVec(coors->x - (aSafeZones[i].x1 + aSafeZones[i].x2) * 0.5f, coors->y - (aSafeZones[i].y1 + aSafeZones[i].y2) * 0.5f);
			float safeZoneDist = safeZoneDistVec.Magnitude();
			if (safeZoneDist < minDist) {
				minDist = safeZoneDist;
				closestSafeZone = i;
			}
		}
	}
	*safeZoneOut = closestSafeZone;
}

void
CPopulation::Update()
{
	if (!CReplay::IsPlayingBack()) {
		ManagePopulation();
		MoveCarsAndPedsOutOfAbandonedZones();
		if (m_CountDownToPedsAtStart != 0) {
			if (--m_CountDownToPedsAtStart == 0)
				GeneratePedsAtStartOfGame();
		} else {
			ms_nTotalCivPeds = ms_nNumCivFemale + ms_nNumCivMale;
			ms_nTotalGangPeds = ms_nNumGang9 + ms_nNumGang8 + ms_nNumGang7
				+ ms_nNumGang6 + ms_nNumGang5 + ms_nNumGang4 + ms_nNumGang3
				+ ms_nNumGang2 + ms_nNumGang1;
			ms_nTotalPeds = ms_nNumDummy + ms_nNumEmergency + ms_nNumCop
				+ ms_nTotalGangPeds + ms_nNumCivFemale + ms_nNumCivMale;
			if (!CCutsceneMgr::IsRunning()) {
				float pcdm = PedCreationDistMultiplier();
				AddToPopulation(pcdm * (CREATION_DIST_MULT_TO_DIST * TheCamera.GenerationDistMultiplier),
					pcdm * ((CREATION_DIST_MULT_TO_DIST + CREATION_RANGE) * TheCamera.GenerationDistMultiplier),
					pcdm * (CREATION_DIST_MULT_TO_DIST + CREATION_RANGE) * OFFSCREEN_CREATION_MULT - CREATION_RANGE,
					pcdm * (CREATION_DIST_MULT_TO_DIST + CREATION_RANGE) * OFFSCREEN_CREATION_MULT);
			}
		}
	}
}

void
CPopulation::GeneratePedsAtStartOfGame()
{
	for (int i = 0; i < 50; i++) {
		ms_nTotalCivPeds = ms_nNumCivFemale + ms_nNumCivMale;
		ms_nTotalGangPeds = ms_nNumGang9 + ms_nNumGang8 + ms_nNumGang7
			+ ms_nNumGang6 + ms_nNumGang5 + ms_nNumGang4
			+ ms_nNumGang3 + ms_nNumGang2 + ms_nNumGang1;
		ms_nTotalPeds = ms_nNumDummy + ms_nNumEmergency + ms_nNumCop
			+ ms_nTotalGangPeds + ms_nNumCivFemale + ms_nNumCivMale;

		// Min dist is 10.0f only for start of the game (naturally)
		AddToPopulation(10.0f, PedCreationDistMultiplier() * (CREATION_DIST_MULT_TO_DIST + CREATION_RANGE),
			10.0f, PedCreationDistMultiplier() * (CREATION_DIST_MULT_TO_DIST + CREATION_RANGE));
	}
}

bool
CPopulation::IsPointInSafeZone(CVector *coors)
{
	for (int i = 0; i < ARRAY_SIZE(aSafeZones); i++) {
		if (coors->x > aSafeZones[i].x1 && coors->x < aSafeZones[i].x2) {
			if (coors->y > aSafeZones[i].y1 && coors->y < aSafeZones[i].y2) {
				if (coors->z > aSafeZones[i].z1 && coors->z < aSafeZones[i].z2)
					return true;
			}
		}
	}
	return false;
}

// More speed = wider area to spawn peds
float
CPopulation::PedCreationDistMultiplier()
{
	CVehicle *veh = FindPlayerVehicle();
	if (!veh)
		return 1.0f;

	float vehSpeed = veh->m_vecMoveSpeed.Magnitude2D();
	return clamp(vehSpeed - 0.1f + 1.0f, 1.0f, 1.5f);
}

CPed*
CPopulation::AddPed(ePedType pedType, uint32 mi, CVector const &coors)
{
	switch (pedType) {
		case PEDTYPE_CIVMALE:
		case PEDTYPE_CIVFEMALE:
		{
			CCivilianPed *ped = new CCivilianPed(pedType, mi);
			ped->GetPosition() = coors;
			ped->SetOrientation(0.0f, 0.0f, 0.0f);
			CWorld::Add(ped);
			if (ms_bGivePedsWeapons) {
				eWeaponType weapon = (eWeaponType)CGeneral::GetRandomNumberInRange(WEAPONTYPE_UNARMED, WEAPONTYPE_DETONATOR);
				if (weapon != WEAPONTYPE_UNARMED) {
					ped->SetCurrentWeapon(ped->GiveWeapon(weapon, 25001));
				}
			}
			return ped;
		}
		case PEDTYPE_COP:
		{
			CCopPed *ped = new CCopPed((eCopType)mi);
			ped->GetPosition() = coors;
			ped->SetOrientation(0.0f, 0.0f, 0.0f);
			CWorld::Add(ped);
			return ped;
		}
		case PEDTYPE_GANG1:
		case PEDTYPE_GANG2:
		case PEDTYPE_GANG3:
		case PEDTYPE_GANG4:
		case PEDTYPE_GANG5:
		case PEDTYPE_GANG6:
		case PEDTYPE_GANG7:
		case PEDTYPE_GANG8:
		case PEDTYPE_GANG9:
		{
			CCivilianPed *ped = new CCivilianPed(pedType, mi);
			ped->GetPosition() = coors;
			ped->SetOrientation(0.0f, 0.0f, 0.0f);
			CWorld::Add(ped);

			uint32 weapon;
			if (CGeneral::GetRandomNumberInRange(0, 100) >= 50)
				weapon = ped->GiveWeapon(CGangs::GetGangWeapon2(pedType - PEDTYPE_GANG1), 25001);
			else
				weapon = ped->GiveWeapon(CGangs::GetGangWeapon1(pedType - PEDTYPE_GANG1), 25001);
			ped->SetCurrentWeapon(weapon);
			return ped;
		}
		case PEDTYPE_EMERGENCY:
		{
			CEmergencyPed *ped = new CEmergencyPed(PEDTYPE_EMERGENCY);
			ped->GetPosition() = coors;
			ped->SetOrientation(0.0f, 0.0f, 0.0f);
			CWorld::Add(ped);
			return ped;
		}
		case PEDTYPE_FIREMAN:
		{
			CEmergencyPed *ped = new CEmergencyPed(PEDTYPE_FIREMAN);
			ped->GetPosition() = coors;
			ped->SetOrientation(0.0f, 0.0f, 0.0f);
			CWorld::Add(ped);
			return ped;
		}
		case PEDTYPE_CRIMINAL:
		case PEDTYPE_PROSTITUTE:
		{
			CCivilianPed *ped = new CCivilianPed(pedType, mi);
			ped->GetPosition() = coors;
			ped->SetOrientation(0.0f, 0.0f, 0.0f);
			CWorld::Add(ped);
			return ped;
		}
		default:
			Error("Unknown ped type, AddPed, Population.cpp");
			return nil;
	}
}

void
CPopulation::AddToPopulation(float minDist, float maxDist, float minDistOffScreen, float maxDistOffScreen)
{
	uint32 pedTypeToAdd;
	int32 modelToAdd;
	int pedAmount;

	CZoneInfo zoneInfo;
	CPed *gangLeader = nil;
	bool addCop = false;
	CPlayerInfo *playerInfo = &CWorld::Players[CWorld::PlayerInFocus];
	CVector playerCentreOfWorld = FindPlayerCentreOfWorld(CWorld::PlayerInFocus);
	CTheZones::GetZoneInfoForTimeOfDay(&playerCentreOfWorld, &zoneInfo);
	CWanted *wantedInfo = playerInfo->m_pPed->m_pWanted;
	if (wantedInfo->m_nWantedLevel > 2) {
		if (ms_nNumCop < wantedInfo->m_MaxCops && !playerInfo->m_pPed->bInVehicle
			&& (CCarCtrl::NumLawEnforcerCars >= wantedInfo->m_MaximumLawEnforcerVehicles
				|| CCarCtrl::NumRandomCars >= playerInfo->m_nTrafficMultiplier * CCarCtrl::CarDensityMultiplier
				|| CCarCtrl::NumFiretrucksOnDuty + CCarCtrl::NumAmbulancesOnDuty + CCarCtrl::NumParkedCars
				+ CCarCtrl::NumMissionCars + CCarCtrl::NumLawEnforcerCars + CCarCtrl::NumRandomCars >= CCarCtrl::MaxNumberOfCarsInUse)) {
			addCop = true;
			minDist = PedCreationDistMultiplier() * CREATION_DIST_MULT_TO_DIST;
			maxDist = PedCreationDistMultiplier() * (CREATION_DIST_MULT_TO_DIST + CREATION_RANGE);
		}
	}
	// Yeah, float
	float maxPossiblePedsForArea = (zoneInfo.pedDensity + zoneInfo.carDensity) * playerInfo->m_fRoadDensity * PedDensityMultiplier * CIniFile::PedNumberMultiplier;
	maxPossiblePedsForArea = min(maxPossiblePedsForArea, MaxNumberOfPedsInUse);

	if (ms_nTotalPeds < maxPossiblePedsForArea || addCop) {
		int decisionThreshold = CGeneral::GetRandomNumberInRange(0, 1000);
		if (decisionThreshold < zoneInfo.copDensity || addCop) {
			pedTypeToAdd = PEDTYPE_COP;
			modelToAdd = ChoosePolicePedOccupation();
		} else {
			int16 density = zoneInfo.copDensity;
			for (int i = 0; i < NUM_GANGS; i++) {
				density += zoneInfo.gangDensity[i];
				if (decisionThreshold < density) {
					pedTypeToAdd = PEDTYPE_GANG1 + i;
					break;
				}

				if (i == NUM_GANGS - 1) {
					modelToAdd = ChooseCivilianOccupation(zoneInfo.pedGroup);
					if (modelToAdd == -1)
						return;
					pedTypeToAdd = ((CPedModelInfo*)CModelInfo::GetModelInfo(modelToAdd))->m_pedType;
				}

			}
		}
		if (!addCop && m_AllRandomPedsThisType > PEDTYPE_PLAYER1)
			pedTypeToAdd = m_AllRandomPedsThisType;

		if (pedTypeToAdd >= PEDTYPE_GANG1 && pedTypeToAdd <= PEDTYPE_GANG9) {
			int randVal = CGeneral::GetRandomNumber() % 100;
			if (randVal < 50)
				return;

			if (randVal < 57) {
				pedAmount = 1;
			} else if (randVal >= 74) {
				if (randVal >= 85)
					pedAmount = 4;
				else
					pedAmount = 3;
			} else {
				pedAmount = 2;
			}
		} else
			pedAmount = 1;

		CVector generatedCoors;
		int node1, node2;
		float randomPos;
		bool foundCoors = !!ThePaths.GeneratePedCreationCoors(playerCentreOfWorld.x, playerCentreOfWorld.y, minDist, maxDist, minDistOffScreen, maxDistOffScreen,
			&generatedCoors, &node1, &node2, &randomPos, nil);

		if (!foundCoors)
			return;

		for (int i = 0; i < pedAmount; ++i) {
			if (pedTypeToAdd >= PEDTYPE_GANG1 && pedTypeToAdd <= PEDTYPE_GANG9)
				modelToAdd = ChooseGangOccupation(pedTypeToAdd - PEDTYPE_GANG1);

			if (pedTypeToAdd == PEDTYPE_COP) {
				// Unused code, ChoosePolicePedOccupation returns COP_STREET. Spawning FBI/SWAT/Army done in somewhere else.
				if (modelToAdd != COP_STREET) {
					if (modelToAdd == COP_FBI) {
						if (!CModelInfo::GetModelInfo(MI_FBI)->GetRwObject())
							return;

					} else if (modelToAdd == COP_SWAT) {
						if (!CModelInfo::GetModelInfo(MI_SWAT)->GetRwObject())
							return;

					} else if (modelToAdd == COP_ARMY && !CModelInfo::GetModelInfo(MI_ARMY)->GetRwObject()) {
						return;
					}
				} else if (!CModelInfo::GetModelInfo(MI_COP)->GetRwObject()) {
					return;
				}
			} else if (!CModelInfo::GetModelInfo(modelToAdd)->GetRwObject()) {
				return;
			}
			generatedCoors.z += 0.7f;

			// What? How can this not be met?
			if (i < pedAmount) {
				//rand()
				if (gangLeader) {
					// Align gang members in formation. (btw i can't be 0 in here)
					float offsetMin = i * 0.75f;
					float offsetMax = (i + 1.0f) * 0.75f - offsetMin;
					float xOffset = CGeneral::GetRandomNumberInRange(offsetMin, offsetMin + offsetMax);
					float yOffset = CGeneral::GetRandomNumberInRange(offsetMin, offsetMin + offsetMax);
					if (CGeneral::GetRandomNumber() & 1)
						xOffset = -xOffset;
					if (CGeneral::GetRandomNumber() & 1)
						yOffset = -yOffset;
					generatedCoors.x = xOffset + gangLeader->GetPosition().x;
					generatedCoors.y = yOffset + gangLeader->GetPosition().y;
				}
			}
			if (!CPedPlacement::IsPositionClearForPed(&generatedCoors))
				break;

			// Why no love for last gang member?!
			if (i + 1 < pedAmount) {
				bool foundGround;
				float groundZ = CWorld::FindGroundZFor3DCoord(generatedCoors.x, generatedCoors.y, 2.0f + generatedCoors.z, &foundGround) + 0.7f;
				if (!foundGround)
					return;

				generatedCoors.z = max(generatedCoors.z, groundZ);
			}
			bool farEnoughToAdd = true;
			CMatrix mat(TheCamera.GetCameraMatrix());
			if (TheCamera.IsSphereVisible(generatedCoors, 2.0f, &mat)) {
				if (PedCreationDistMultiplier() * CREATION_DIST_MULT_TO_DIST > (generatedCoors - playerCentreOfWorld).Magnitude2D())
					farEnoughToAdd = false;
			}
			if (!farEnoughToAdd)
				break;
			CPed *newPed = AddPed((ePedType)pedTypeToAdd, modelToAdd, generatedCoors);
			newPed->SetWanderPath(CGeneral::GetRandomNumberInRange(0, 8));

			if (i != 0) {
				// Gang member
				newPed->SetLeader(gangLeader);
				newPed->m_nPedState = PED_UNKNOWN;
				gangLeader->m_nPedState = PED_UNKNOWN;
				newPed->m_fRotationCur = CGeneral::GetRadianAngleBetweenPoints(
					gangLeader->GetPosition().x, gangLeader->GetPosition().y,
					newPed->GetPosition().x, newPed->GetPosition().y);
				newPed->m_fRotationDest = newPed->m_fRotationCur;
			} else {
				gangLeader = newPed;
			}
			CVisibilityPlugins::SetClumpAlpha(newPed->GetClump(), 0);
			/*
			// Pointless, this is already a for loop
			if (i + 1 > pedAmount)
				break;
			if (pedAmount <= 1)
				break; */
		}
	}
}

STARTPATCHES
	InjectHook(0x4F3770, &CPopulation::Initialise, PATCH_JUMP);
	InjectHook(0x4F5780, &CPopulation::ChooseGangOccupation, PATCH_JUMP);
	InjectHook(0x4F6200, &CPopulation::DealWithZoneChange, PATCH_JUMP);
	InjectHook(0x4F6010, &CPopulation::FindCollisionZoneForCoors, PATCH_JUMP);
	InjectHook(0x4F6410, &CPopulation::PedCreationDistMultiplier, PATCH_JUMP);
	InjectHook(0x4F5280, &CPopulation::AddPed, PATCH_JUMP);
ENDPATCHES