#include "common.h"
#include "patcher.h"
#include "Restart.h"
#include "Zones.h"
#include "PathFind.h"

uint8 &CRestart::OverrideHospitalLevel = *(uint8*)0x95CD4C;
uint8 &CRestart::OverridePoliceStationLevel = *(uint8*)0x95CD50;
bool &CRestart::bFadeInAfterNextArrest = *(bool*)0x95CD69;
bool &CRestart::bFadeInAfterNextDeath = *(bool*)0x95CD9D;

bool &CRestart::bOverrideRestart = *(bool*)0x95CD5D;
CVector &CRestart::OverridePosition = *(CVector*)0x8E2C00;
float &CRestart::OverrideHeading = *(float*)0x8F2A18;

CVector(&CRestart::HospitalRestartPoints)[NUM_RESTART_POINTS] = *(CVector(*)[NUM_RESTART_POINTS])*(uintptr*)0x87F9B0;
float(&CRestart::HospitalRestartHeadings)[NUM_RESTART_POINTS] = *(float(*)[NUM_RESTART_POINTS])*(uintptr*)0x6F1D40;
uint16 &CRestart::NumberOfHospitalRestarts = *(uint16*)0x95CC46;

CVector(&CRestart::PoliceRestartPoints)[NUM_RESTART_POINTS] = *(CVector(*)[NUM_RESTART_POINTS])*(uintptr*)0x846228;
float(&CRestart::PoliceRestartHeadings)[NUM_RESTART_POINTS] = *(float(*)[NUM_RESTART_POINTS])*(uintptr*)0x6F1D20;
uint16 &CRestart::NumberOfPoliceRestarts = *(uint16*)0x95CC44;

void
CRestart::Initialise()
{
	OverridePoliceStationLevel = LEVEL_NONE;
	OverrideHospitalLevel = LEVEL_NONE;
	bFadeInAfterNextArrest = true;
	bFadeInAfterNextDeath = true;
	OverrideHeading = 0.0f;
	OverridePosition = CVector(0.0f, 0.0f, 0.0f);
	bOverrideRestart = false;
	NumberOfPoliceRestarts = 0;
	NumberOfHospitalRestarts = 0;

	for (int i = 0; i < NUM_RESTART_POINTS; i++) {
		HospitalRestartPoints[i] = CVector(0.0f, 0.0f, 0.0f);
		HospitalRestartHeadings[0] = 0.0f;
		PoliceRestartPoints[i] = CVector(0.0f, 0.0f, 0.0f);
		PoliceRestartHeadings[0] = 0.0f;
	}
}

void
CRestart::AddHospitalRestartPoint(const CVector &pos, float heading)
{
	HospitalRestartPoints[NumberOfHospitalRestarts] = pos;
	HospitalRestartHeadings[NumberOfHospitalRestarts++] = heading;
}

void
CRestart::AddPoliceRestartPoint(const CVector &pos, float heading)
{
	PoliceRestartPoints[NumberOfPoliceRestarts] = pos;
	PoliceRestartHeadings[NumberOfPoliceRestarts++] = heading;
}

void
CRestart::OverrideNextRestart(const CVector &pos, float heading)
{
	bOverrideRestart = true;
	OverridePosition = pos;
	OverrideHeading = heading;
}

void
CRestart::CancelOverrideRestart()
{
	bOverrideRestart = false;
}

void
CRestart::FindClosestHospitalRestartPoint(const CVector &pos, CVector *outPos, float *outHeading)
{
	if (bOverrideRestart) {
		*outPos = OverridePosition;
		*outHeading = OverrideHeading;
		CancelOverrideRestart();
		return;
	}

	eLevelName curlevel = CTheZones::FindZoneForPoint(pos);
	float fMinDist = 16000000.0f;
	int closestPoint = NUM_RESTART_POINTS;

	// find closest point on this level
	for (int i = 0; i < NumberOfHospitalRestarts; i++) {
		if (CTheZones::FindZoneForPoint(HospitalRestartPoints[i]) == (OverrideHospitalLevel != LEVEL_NONE ? OverrideHospitalLevel : curlevel)) {
			float dist = (pos - HospitalRestartPoints[i]).MagnitudeSqr();
			if (fMinDist >= dist) {
				fMinDist = dist;
				closestPoint = i;
			}
		}
	}

	// if we didn't find anything, find closest point on any level
	if (closestPoint == NUM_RESTART_POINTS) {
		for (int i = 0; i < NumberOfHospitalRestarts; i++) {
			float dist = (pos - HospitalRestartPoints[i]).MagnitudeSqr();
			if (fMinDist >= dist) {
				fMinDist = dist;
				closestPoint = i;
			}
		}
	}

	// if we still didn't find anything, find closest path node
	if (closestPoint == NUM_RESTART_POINTS) {
		*outPos = ThePaths.m_pathNodes[ThePaths.FindNodeClosestToCoors(pos, PATH_PED, 999999.9f)].pos;
		*outHeading = 0.0f;
		printf("Couldn't find a hospital restart zone near the player %f %f %f->%f %f %f\n", pos.x, pos.y, pos.z, outPos->x, outPos->y, outPos->z);
	} else {
		*outPos = HospitalRestartPoints[closestPoint];
		*outHeading = HospitalRestartHeadings[closestPoint];
	}
}

void
CRestart::FindClosestPoliceRestartPoint(const CVector &pos, CVector *outPos, float *outHeading)
{
	if (bOverrideRestart) {
		*outPos = OverridePosition;
		*outHeading = OverrideHeading;
		CancelOverrideRestart();
		return;
	}

	eLevelName curlevel = CTheZones::FindZoneForPoint(pos);
	float fMinDist = 16000000.0f;
	int closestPoint = NUM_RESTART_POINTS;

	// find closest point on this level
	for (int i = 0; i < NumberOfPoliceRestarts; i++) {
		if (CTheZones::FindZoneForPoint(PoliceRestartPoints[i]) == (OverridePoliceStationLevel != LEVEL_NONE ? OverridePoliceStationLevel : curlevel)) {
			float dist = (pos - PoliceRestartPoints[i]).MagnitudeSqr();
			if (fMinDist >= dist) {
				fMinDist = dist;
				closestPoint = i;
			}
		}
	}

	// if we didn't find anything, find closest point on any level
	if (closestPoint == NUM_RESTART_POINTS) {
		for (int i = 0; i < NumberOfPoliceRestarts; i++) {
			float dist = (pos - PoliceRestartPoints[i]).MagnitudeSqr();
			if (fMinDist >= dist) {
				fMinDist = dist;
				closestPoint = i;
			}
		}
	}

	// if we still didn't find anything, find closest path node
	if (closestPoint == NUM_RESTART_POINTS) {
		printf("Couldn't find a police restart zone near the player\n");
		*outPos = ThePaths.m_pathNodes[ThePaths.FindNodeClosestToCoors(pos, PATH_PED, 999999.9f)].pos;
		*outHeading = 0.0f;
	} else {
		*outPos = PoliceRestartPoints[closestPoint];
		*outHeading = PoliceRestartHeadings[closestPoint];
	}
}

void
CRestart::LoadAllRestartPoints(uint8 *buf, uint32 size)
{
	Initialise();

INITSAVEBUF
	CheckSaveHeader(buf, 'R','S','T','\0', size - SAVE_HEADER_SIZE);

	for (int i = 0; i < NUM_RESTART_POINTS; i++) {
		HospitalRestartPoints[i] = ReadSaveBuf<CVector>(buf);
		HospitalRestartHeadings[i] = ReadSaveBuf<float>(buf);
	}

	for (int i = 0; i < NUM_RESTART_POINTS; i++) {
		PoliceRestartPoints[i] = ReadSaveBuf<CVector>(buf);
		PoliceRestartHeadings[i] = ReadSaveBuf<float>(buf);
	}

	NumberOfHospitalRestarts = ReadSaveBuf<uint16>(buf);
	NumberOfPoliceRestarts = ReadSaveBuf<uint16>(buf);
	bOverrideRestart = ReadSaveBuf<bool>(buf);

	// skip something unused
	ReadSaveBuf<uint8>(buf);
	ReadSaveBuf<uint16>(buf);

	OverridePosition = ReadSaveBuf<CVector>(buf);
	OverrideHeading = ReadSaveBuf<float>(buf);
	bFadeInAfterNextDeath = ReadSaveBuf<bool>(buf);
	bFadeInAfterNextArrest = ReadSaveBuf<bool>(buf);
	OverrideHospitalLevel = ReadSaveBuf<uint8>(buf);
	OverridePoliceStationLevel = ReadSaveBuf<uint8>(buf);
VALIDATESAVEBUF(size);
}

void
CRestart::SaveAllRestartPoints(uint8 *buf, uint32 *size)
{
	*size = SAVE_HEADER_SIZE
		+ sizeof(HospitalRestartPoints)
		+ sizeof(HospitalRestartHeadings)
		+ sizeof(PoliceRestartPoints)
		+ sizeof(PoliceRestartHeadings)
		+ sizeof(NumberOfHospitalRestarts)
		+ sizeof(NumberOfPoliceRestarts)
		+ sizeof(bOverrideRestart)
		+ sizeof(uint8)
		+ sizeof(uint16)
		+ sizeof(OverridePosition)
		+ sizeof(OverrideHeading)
		+ sizeof(bFadeInAfterNextDeath)
		+ sizeof(bFadeInAfterNextArrest)
		+ sizeof(OverrideHospitalLevel)
		+ sizeof(OverridePoliceStationLevel); // == 292

INITSAVEBUF
	WriteSaveHeader(buf, 'R','S','T','\0', *size - SAVE_HEADER_SIZE);

	for (int i = 0; i < NUM_RESTART_POINTS; i++) {
		WriteSaveBuf(buf, HospitalRestartPoints[i]);
		WriteSaveBuf(buf, HospitalRestartHeadings[i]);
	}

	for (int i = 0; i < NUM_RESTART_POINTS; i++) {
		WriteSaveBuf(buf, PoliceRestartPoints[i]);
		WriteSaveBuf(buf, PoliceRestartHeadings[i]);
	}

	WriteSaveBuf(buf, NumberOfHospitalRestarts);
	WriteSaveBuf(buf, NumberOfPoliceRestarts);
	WriteSaveBuf(buf, bOverrideRestart);

	WriteSaveBuf(buf, (uint8)0);
	WriteSaveBuf(buf, (uint16)0);

	WriteSaveBuf(buf, OverridePosition);
	WriteSaveBuf(buf, OverrideHeading);
	WriteSaveBuf(buf, bFadeInAfterNextDeath);
	WriteSaveBuf(buf, bFadeInAfterNextArrest);
	WriteSaveBuf(buf, OverrideHospitalLevel);
	WriteSaveBuf(buf, OverridePoliceStationLevel);
VALIDATESAVEBUF(*size);
}


STARTPATCHES
	InjectHook(0x435E20, &CRestart::Initialise, PATCH_JUMP);
	InjectHook(0x436100, &CRestart::AddHospitalRestartPoint, PATCH_JUMP);
	InjectHook(0x436150, &CRestart::AddPoliceRestartPoint, PATCH_JUMP);
	InjectHook(0x4366C0, &CRestart::OverrideNextRestart, PATCH_JUMP);
	InjectHook(0x4366F0, &CRestart::CancelOverrideRestart, PATCH_JUMP);
	InjectHook(0x4361A0, &CRestart::FindClosestHospitalRestartPoint, PATCH_JUMP);
	InjectHook(0x436450, &CRestart::FindClosestPoliceRestartPoint, PATCH_JUMP);
	InjectHook(0x436B20, &CRestart::LoadAllRestartPoints, PATCH_JUMP);
	InjectHook(0x436700, &CRestart::SaveAllRestartPoints, PATCH_JUMP);
ENDPATCHES