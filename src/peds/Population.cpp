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
#include "Ped.h"

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
uint32& CPopulation::m_CountDownToPedsAtStart = *(uint32*)0x95CD4F;
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

WRAPPER void CPopulation::Update(void) { EAXJMP(0x4F39A0); }
WRAPPER CPed *CPopulation::AddPedInCar(CVehicle *vehicle) { EAXJMP(0x4F5800); }
WRAPPER bool CPopulation::IsPointInSafeZone(CVector *coors) { EAXJMP(0x4F60C0); }

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

int32
CPopulation::ChoosePolicePedOccupation()
{
	CGeneral::GetRandomNumber();
	return 0;
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

STARTPATCHES
	InjectHook(0x4F3770, &CPopulation::Initialise, PATCH_JUMP);
	InjectHook(0x4F5780, &CPopulation::ChooseGangOccupation, PATCH_JUMP);
	InjectHook(0x4F6200, &CPopulation::DealWithZoneChange, PATCH_JUMP);
	InjectHook(0x4F6010, &CPopulation::FindCollisionZoneForCoors, PATCH_JUMP);
ENDPATCHES