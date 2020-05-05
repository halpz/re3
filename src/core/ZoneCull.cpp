#include "common.h"

#include "Building.h"
#include "Treadable.h"
#include "Train.h"
#include "Pools.h"
#include "Timer.h"
#include "Camera.h"
#include "World.h"
#include "FileMgr.h"
#include "ZoneCull.h"
#include "Zones.h"

int32     CCullZones::NumCullZones;
CCullZone CCullZones::aZones[NUMCULLZONES];
int32     CCullZones::NumAttributeZones;
CAttributeZone CCullZones::aAttributeZones[NUMATTRIBZONES];
uint16    CCullZones::aIndices[NUMZONEINDICES];
int16     CCullZones::aPointersToBigBuildingsForBuildings[NUMBUILDINGS];
int16     CCullZones::aPointersToBigBuildingsForTreadables[NUMTREADABLES];

int32 CCullZones::CurrentWantedLevelDrop_Player;
int32 CCullZones::CurrentFlags_Camera;
int32 CCullZones::CurrentFlags_Player;
int32 CCullZones::OldCullZone;
int32 CCullZones::EntityIndicesUsed;
bool CCullZones::bCurrentSubwayIsInvisible;
bool CCullZones::bCullZonesDisabled;


void
CCullZones::Init(void)
{
	int i;

	NumAttributeZones = 0;
	CurrentWantedLevelDrop_Player = 0;
	CurrentFlags_Camera = 0;
	CurrentFlags_Player = 0;
	bCurrentSubwayIsInvisible = false;
	NumCullZones = 0;
	OldCullZone = -1;
	EntityIndicesUsed = 0;

	for(i = 0; i < NUMBUILDINGS; i++)
		aPointersToBigBuildingsForBuildings[i] = -1;
	for(i = 0; i < NUMTREADABLES; i++)
		aPointersToBigBuildingsForTreadables[i] = -1;
}

bool CCullZone::TestLine(CVector vec1, CVector vec2)
{
	CColPoint colPoint;
	CEntity *entity;

	if (CWorld::ProcessLineOfSight(vec1, vec2, colPoint, entity, true, false, false, false, false, true, false))
		return true;
	if (CWorld::ProcessLineOfSight(CVector(vec1.x + 0.05f, vec1.y, vec1.z), CVector(vec2.x + 0.05f, vec2.y, vec2.z), colPoint, entity, true, false, false, false, false, true, false))
		return true;
	if (CWorld::ProcessLineOfSight(CVector(vec1.x - 0.05f, vec1.y, vec1.z), CVector(vec2.x - 0.05f, vec2.y, vec2.z), colPoint, entity, true, false, false, false, false, true, false))
		return true;
	if (CWorld::ProcessLineOfSight(CVector(vec1.x, vec1.y + 0.05f, vec1.z), CVector(vec2.x, vec2.y + 0.05f, vec2.z), colPoint, entity, true, false, false, false, false, true, false))
		return true;
	if (CWorld::ProcessLineOfSight(CVector(vec1.x, vec1.y - 0.05f, vec1.z), CVector(vec2.x, vec2.y - 0.05f, vec2.z), colPoint, entity, true, false, false, false, false, true, false))
		return true;
	if (CWorld::ProcessLineOfSight(CVector(vec1.x, vec1.y, vec1.z + 0.05f), CVector(vec2.x, vec2.y, vec2.z + 0.05f), colPoint, entity, true, false, false, false, false, true, false))
		return true;
	return CWorld::ProcessLineOfSight(CVector(vec1.x, vec1.y, vec1.z - 0.05f), CVector(vec2.x, vec2.y, vec2.z - 0.05f), colPoint, entity, true, false, false, false, false, true, false);
}


uint16* pTempArrayIndices;
int TempEntityIndicesUsed;

void
CCullZones::ResolveVisibilities(void)
{
	int fd;

	CFileMgr::SetDir("");
	fd = CFileMgr::OpenFile("DATA\\cullzone.dat", "rb");
	if(fd > 0){
		CFileMgr::Read(fd, (char*)&NumCullZones, sizeof(NumCullZones));
		CFileMgr::Read(fd, (char*)aZones, sizeof(aZones));
		CFileMgr::Read(fd, (char*)&NumAttributeZones, sizeof(NumAttributeZones));
		CFileMgr::Read(fd, (char*)aAttributeZones, sizeof(aAttributeZones));
		CFileMgr::Read(fd, (char*)aIndices, sizeof(aIndices));
		CFileMgr::Read(fd, (char*)aPointersToBigBuildingsForBuildings, sizeof(aPointersToBigBuildingsForBuildings));
		CFileMgr::Read(fd, (char*)aPointersToBigBuildingsForTreadables, sizeof(aPointersToBigBuildingsForTreadables));
		CFileMgr::CloseFile(fd);
	}else{
#if 0
		// TODO: implement code from mobile to generate data here
		EntityIndicesUsed = 0;
		BuildListForBigBuildings();
		pTempArrayIndices = new uint16[140000];
		TempEntityIndicesUsed = 0;

		for (int i = 0; i < NumCullZones; i++) {
			DoVisibilityTestCullZone(i, true);
		}

		CompressIndicesArray();
		delete[] pTempArrayIndices;

		fd = CFileMgr::OpenFileForWriting("data\\cullzone.dat");
		if (fd != 0) {
			CFileMgr::Write(fd, (char*)&NumCullZones, sizeof(NumCullZones));
			CFileMgr::Write(fd, (char*)aZones, sizeof(aZones));
			CFileMgr::Write(fd, (char*)&NumAttributeZones, sizeof(NumAttributeZones));
			CFileMgr::Write(fd, (char*)&aAttributeZones, sizeof(aAttributeZones));
			CFileMgr::Write(fd, (char*)&aIndices, sizeof(aIndices));
			CFileMgr::Write(fd, (char*)&aPointersToBigBuildingsForBuildings, sizeof(aPointersToBigBuildingsForBuildings));
			CFileMgr::Write(fd, (char*)&aPointersToBigBuildingsForTreadables, sizeof(aPointersToBigBuildingsForTreadables));
			CFileMgr::CloseFile(fd);
		}
#endif
	}
}

void
CCullZones::BuildListForBigBuildings()
{
	for (int i = CPools::GetBuildingPool()->GetSize()-1; i >= 0; i--) {
		CBuilding *building = CPools::GetBuildingPool()->GetSlot(i);
		if (building == nil || !building->bIsBIGBuilding) continue;
		CSimpleModelInfo *nonlod = (CSimpleModelInfo*)((CSimpleModelInfo *)CModelInfo::GetModelInfo(building->GetModelIndex()))->m_atomics[2];
		if (nonlod == nil) continue;

		for (int j = i; j >= 0; j--) {
			CBuilding *building2 = CPools::GetBuildingPool()->GetSlot(j);
			if (building2 == nil || building2->bIsBIGBuilding) continue;
			if (CModelInfo::GetModelInfo(building2->GetModelIndex()) == nonlod) {
				if ((building2->GetPosition() - building->GetPosition()).Magnitude() < 5.0f) {
					aPointersToBigBuildingsForBuildings[j] = i;
				}
			}
		}

		for (int j = CPools::GetTreadablePool()->GetSize()-1; j >= 0; j--) {
			CTreadable *treadable = CPools::GetTreadablePool()->GetSlot(j);
			if (treadable == nil || treadable->bIsBIGBuilding) continue;
			if (CModelInfo::GetModelInfo(treadable->GetModelIndex()) == nonlod) {
				if ((treadable->GetPosition() - building->GetPosition()).Magnitude() < 5.0f) {
					aPointersToBigBuildingsForTreadables[j] = i;
				}
			}
		}
	}
}

void
CCullZones::DoVisibilityTestCullZone(int zoneId, bool doIt)
{
	aZones[zoneId].m_groupIndexCount[0] = 0;
	aZones[zoneId].m_groupIndexCount[1] = 0;
	aZones[zoneId].m_groupIndexCount[2] = 0;
	aZones[zoneId].m_indexStart = TempEntityIndicesUsed;
	aZones[zoneId].FindTestPoints();

	if (!doIt) return;

	for (int i = CPools::GetBuildingPool()->GetSize() - 1; i >= 0; i--) {
		CBuilding *building = CPools::GetBuildingPool()->GetSlot(i);
		if (building != nil && !building->bIsBIGBuilding && aZones[zoneId].IsEntityCloseEnoughToZone(building, aPointersToBigBuildingsForBuildings[i] != -1)) {
			CBuilding *building2 = nil;
			if (aPointersToBigBuildingsForBuildings[i] != -1)
				building2 = CPools::GetBuildingPool()->GetSlot(aPointersToBigBuildingsForBuildings[i]);

			if (!aZones[zoneId].TestEntityVisibilityFromCullZone(building, 0.0f, building2)) {
				pTempArrayIndices[TempEntityIndicesUsed++] = i;
				aZones[zoneId].m_groupIndexCount[0]++;
			}
		}
	}

	for (int i = CPools::GetTreadablePool()->GetSize() - 1; i >= 0; i--) {
		CTreadable* building = CPools::GetTreadablePool()->GetSlot(i);
		if (building != nil && aZones[zoneId].IsEntityCloseEnoughToZone(building, aPointersToBigBuildingsForTreadables[i] != -1)) {
			CTreadable* building2 = nil;
			if (aPointersToBigBuildingsForTreadables[i] != -1)
				building2 = CPools::GetTreadablePool()->GetSlot(aPointersToBigBuildingsForTreadables[i]);

			if (!aZones[zoneId].TestEntityVisibilityFromCullZone(building, 10.0f, building2)) {
				pTempArrayIndices[TempEntityIndicesUsed++] = i;
				aZones[zoneId].m_groupIndexCount[1]++;
			}
		}
	}

	for (int i = CPools::GetTreadablePool()->GetSize() - 1; i >= 0; i--) {
		CTreadable *building = CPools::GetTreadablePool()->GetSlot(i);
		if (building != nil && aZones[zoneId].CalcDistToCullZoneSquared(building->GetPosition().x, building->GetPosition().y) < 40000.0f) {
			int start = aZones[zoneId].m_groupIndexCount[0] + aZones[zoneId].m_indexStart;
			int end = aZones[zoneId].m_groupIndexCount[1] + start;

			bool alreadyAdded = false;

			for (int k = start; k < end; k++) {
				if (aIndices[k] == i)
					alreadyAdded = true;
			}

			if (!alreadyAdded) {
				CBuilding *building2 = nil;
				if (aPointersToBigBuildingsForTreadables[i] != -1)
					building2 = CPools::GetBuildingPool()->GetSlot(aPointersToBigBuildingsForTreadables[i]);
				if (!aZones[zoneId].TestEntityVisibilityFromCullZone(building, 0.0f, building2)) {
					pTempArrayIndices[TempEntityIndicesUsed++] = i;
					aZones[zoneId].m_groupIndexCount[2]++;
				}
			}
		}
	}
}

void
CCullZones::Update(void)
{
	bool invisible;

	if(bCullZonesDisabled)
		return;

	switch(CTimer::GetFrameCounter() & 7){
	case 0:
	case 4:
		/* Update Cull zone */
		ForceCullZoneCoors(TheCamera.GetGameCamPosition());
		break;

	case 2:
		/* Update camera attributes */
		CurrentFlags_Camera = FindAttributesForCoors(TheCamera.GetGameCamPosition(), nil);
		invisible = (CurrentFlags_Camera & ATTRZONE_SUBWAYVISIBLE) == 0;
		if(invisible != bCurrentSubwayIsInvisible){
			MarkSubwayAsInvisible(!invisible);
			bCurrentSubwayIsInvisible = invisible;
		}
		break;

	case 6:
		/* Update player attributes */
		CurrentFlags_Player = FindAttributesForCoors(FindPlayerCoors(),
			&CurrentWantedLevelDrop_Player);
		break;
	}
}

void
CCullZones::ForceCullZoneCoors(CVector coors)
{
	int32 z;
	z = FindCullZoneForCoors(coors);
	if(z != OldCullZone){
		if(OldCullZone >= 0)
			aZones[OldCullZone].DoStuffLeavingZone();
		if(z >= 0)
			aZones[z].DoStuffEnteringZone();
		OldCullZone = z;
	}
}

int32
CCullZones::FindCullZoneForCoors(CVector coors)
{
	int i;

	for(i = 0; i < NumCullZones; i++)
		if(coors.x >= aZones[i].minx && coors.x <= aZones[i].maxx &&
		   coors.y >= aZones[i].miny && coors.y <= aZones[i].maxy &&
		   coors.z >= aZones[i].minz && coors.z <= aZones[i].maxz)
			return i;
	return -1;
}

int32
CCullZones::FindAttributesForCoors(CVector coors, int32 *wantedLevel)
{
	int i;
	int32 attribs;

	if (wantedLevel)
		*wantedLevel = 0;
	attribs = 0;
	for(i = 0; i < NumAttributeZones; i++)
		if(coors.x >= aAttributeZones[i].minx && coors.x <= aAttributeZones[i].maxx &&
		   coors.y >= aAttributeZones[i].miny && coors.y <= aAttributeZones[i].maxy &&
		   coors.z >= aAttributeZones[i].minz && coors.z <= aAttributeZones[i].maxz){
			attribs |= aAttributeZones[i].attributes;
			if(wantedLevel)
				*wantedLevel = Max(*wantedLevel, aAttributeZones[i].wantedLevel);
		}
	return attribs;
}

CAttributeZone*
CCullZones::FindZoneWithStairsAttributeForPlayer(void)
{
	int i;
	CVector coors;

	coors = FindPlayerCoors();
	for(i = 0; i < NumAttributeZones; i++)
		if(aAttributeZones[i].attributes & ATTRZONE_STAIRS &&
		   coors.x >= aAttributeZones[i].minx && coors.x <= aAttributeZones[i].maxx &&
		   coors.y >= aAttributeZones[i].miny && coors.y <= aAttributeZones[i].maxy &&
		   coors.z >= aAttributeZones[i].minz && coors.z <= aAttributeZones[i].maxz)
			return &aAttributeZones[i];
	return nil;
}

void
CCullZones::MarkSubwayAsInvisible(bool visible)
{
	int i, n;
	CEntity *e;
	CVehicle *v;

	n = CPools::GetBuildingPool()->GetSize()-1;
	for(i = n; i >= 0; i--){
		e = CPools::GetBuildingPool()->GetSlot(i);
		if(e && e->bIsSubway)
			e->bIsVisible = visible;
	}

	n = CPools::GetTreadablePool()->GetSize()-1;
	for(i = n; i >= 0; i--){
		e = CPools::GetTreadablePool()->GetSlot(i);
		if(e && e->bIsSubway)
			e->bIsVisible = visible;
	}

	n = CPools::GetVehiclePool()->GetSize()-1;
	for(i = n; i >= 0; i--){
		v = CPools::GetVehiclePool()->GetSlot(i);
		if(v && v->IsTrain() && ((CTrain*)v)->m_nTrackId != TRACK_ELTRAIN)
			v->bIsVisible = visible;
	}
}

void
CCullZones::AddCullZone(CVector const &position,
                        float minx, float maxx,
                        float miny, float maxy,
                        float minz, float maxz,
                        uint16 flag, int16 wantedLevel)
{
	CCullZone *cull;
	CAttributeZone *attrib;

	CVector v;
	if((flag & ATTRZONE_NOTCULLZONE) == 0){
		cull = &aZones[NumCullZones++];
		v = position;
		// WTF is this?
		if((v-CVector(1032.14f, -624.255f, 24.93f)).Magnitude() < 1.0f)
			v = CVector(1061.7f, -613.0f, 19.0f);
		if((v-CVector(1029.48f, -495.757f, 21.98f)).Magnitude() < 1.0f)
			v = CVector(1061.4f, -506.0f, 18.5f);
		cull->position.x = clamp(v.x, minx, maxx);
		cull->position.y = clamp(v.y, miny, maxy);
		cull->position.z = clamp(v.z, minz, maxz);
		cull->minx = minx;
		cull->maxx = maxx;
		cull->miny = miny;
		cull->maxy = maxy;
		cull->minz = minz;
		cull->maxz = maxz;
		cull->m_groupIndexCount[0] = 0;
		cull->m_groupIndexCount[1] = 0;
		cull->m_groupIndexCount[2] = 0;
		cull->m_indexStart = 0;
	}
	if(flag & ~ATTRZONE_NOTCULLZONE){
		attrib = &aAttributeZones[NumAttributeZones++];
		attrib->minx = minx;
		attrib->maxx = maxx;
		attrib->miny = miny;
		attrib->maxy = maxy;
		attrib->minz = minz;
		attrib->maxz = maxz;
		attrib->attributes = flag;
		attrib->wantedLevel = wantedLevel;
	}
}


void
CCullZone::DoStuffLeavingZone(void)
{
	int i;

	for(i = 0; i < m_numBuildings; i++)
		DoStuffLeavingZone_OneBuilding(CCullZones::aIndices[m_indexStart + i]);
	for(; i < m_numBuildings + m_numTreadablesPlus10m + m_numTreadables ; i++)
		DoStuffLeavingZone_OneTreadableBoth(CCullZones::aIndices[m_indexStart + i]);
}

void
CCullZone::DoStuffLeavingZone_OneBuilding(uint16 i)
{
	int16 bb;
	int j;

	if(i < 6000){
		CPools::GetBuildingPool()->GetSlot(i)->bZoneCulled = false;
		bb = CCullZones::aPointersToBigBuildingsForBuildings[i];
		if(bb != -1)
			CPools::GetBuildingPool()->GetSlot(bb)->bZoneCulled = false;
	}else{
		i -= 6000;
		for(j = 0; j < 3; j++)
			DoStuffLeavingZone_OneBuilding(CCullZones::aIndices[i+j]);
	}
}

void
CCullZone::DoStuffLeavingZone_OneTreadableBoth(uint16 i)
{
	int16 bb;
	int j;

	if(i < 6000){
		CPools::GetTreadablePool()->GetSlot(i)->bZoneCulled = false;
		CPools::GetTreadablePool()->GetSlot(i)->bZoneCulled2 = false;
		bb = CCullZones::aPointersToBigBuildingsForTreadables[i];
		if(bb != -1)
			CPools::GetBuildingPool()->GetSlot(bb)->bZoneCulled = false;
	}else{
		i -= 6000;
		for(j = 0; j < 3; j++)
			DoStuffLeavingZone_OneTreadableBoth(CCullZones::aIndices[i+j]);
	}
}

void
CCullZone::DoStuffEnteringZone(void)
{
	int i;

	for(i = 0; i < m_numBuildings; i++)
		DoStuffEnteringZone_OneBuilding(CCullZones::aIndices[m_indexStart + i]);
	for(; i < m_numBuildings + m_numTreadablesPlus10m; i++)
		DoStuffEnteringZone_OneTreadablePlus10m(CCullZones::aIndices[m_indexStart + i]);
	for(; i < m_numBuildings + m_numTreadablesPlus10m + m_numTreadables; i++)
		DoStuffEnteringZone_OneTreadable(CCullZones::aIndices[m_indexStart + i]);
}

void
CCullZone::DoStuffEnteringZone_OneBuilding(uint16 i)
{
	int16 bb;
	int j;

	if(i < 6000){
		CPools::GetBuildingPool()->GetSlot(i)->bZoneCulled = true;
		bb = CCullZones::aPointersToBigBuildingsForBuildings[i];
		if(bb != -1)
			CPools::GetBuildingPool()->GetSlot(bb)->bZoneCulled = true;
	}else{
		i -= 6000;
		for(j = 0; j < 3; j++)
			DoStuffEnteringZone_OneBuilding(CCullZones::aIndices[i+j]);
	}
}

void
CCullZone::DoStuffEnteringZone_OneTreadablePlus10m(uint16 i)
{
	int16 bb;
	int j;

	if(i < 6000){
		CPools::GetTreadablePool()->GetSlot(i)->bZoneCulled = true;
		CPools::GetTreadablePool()->GetSlot(i)->bZoneCulled2 = true;
		bb = CCullZones::aPointersToBigBuildingsForTreadables[i];
		if(bb != -1)
			CPools::GetBuildingPool()->GetSlot(bb)->bZoneCulled = true;
	}else{
		i -= 6000;
		for(j = 0; j < 3; j++)
			DoStuffEnteringZone_OneTreadablePlus10m(CCullZones::aIndices[i+j]);
	}
}

void
CCullZone::DoStuffEnteringZone_OneTreadable(uint16 i)
{
	int16 bb;
	int j;

	if(i < 6000){
		CPools::GetTreadablePool()->GetSlot(i)->bZoneCulled = true;
		bb = CCullZones::aPointersToBigBuildingsForTreadables[i];
		if(bb != -1)
			CPools::GetBuildingPool()->GetSlot(bb)->bZoneCulled = true;
	}else{
		i -= 6000;
		for(j = 0; j < 3; j++)
			DoStuffEnteringZone_OneTreadable(CCullZones::aIndices[i+j]);
	}
}

float
CCullZone::CalcDistToCullZoneSquared(float x, float y)
{
	float rx, ry;

	if (x < minx) rx = sq(x - minx);
	else if (x > maxx) rx = sq(x - maxx);
	else rx = 0.0f;

	if (y < miny) ry = sq(y - miny);
	else if (y > maxy) ry = sq(y - maxy);
	else ry = 0.0f;

	return rx + ry;
}

bool
CCullZone::IsEntityCloseEnoughToZone(CEntity *entity, bool checkLevel)
{
	const CVector &pos = entity->GetPosition();

	CSimpleModelInfo *minfo = (CSimpleModelInfo*)CModelInfo::GetModelInfo(entity->GetModelIndex());
	float distToZone = CalcDistToCullZone(pos.x, pos.y);
	float lodDist;
	if (minfo->m_isSubway)
		lodDist = minfo->GetLargestLodDistance() + 30.0f;
	else
		lodDist = minfo->GetLargestLodDistance() + 50.0f;

	if (lodDist > distToZone) return true;
	if (!checkLevel) return false;
	return CTheZones::GetLevelFromPosition(pos) == CTheZones::GetLevelFromPosition(CVector(minx, miny, minz));
}

bool
CCullZones::DoWeHaveMoreThanXOccurencesOfSet(int32 count, uint16 *set)
{
	int32 curCount;
	int32 start;
	int32 size;

	for (int i = 0; i < NumCullZones; i++) {
		curCount = 0;
		for (int group = 0; group < 3; group++) {
			aZones[i].GetGroupStartAndSize(group, start, size);

			int unk = 0; // TODO: figure out
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < 3; k++) {
					if (set[k] == pTempArrayIndices[start+j])
						unk++;
				}
			}
			if (unk == 3 && ++curCount >= count)
				return true;
		}
	}
	return false;
}