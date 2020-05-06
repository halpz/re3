#include "common.h"

#include <ctype.h>

#include "Zones.h"

#include "Clock.h"
#include "Text.h"
#include "World.h"

eLevelName CTheZones::m_CurrLevel;
int16 CTheZones::FindIndex;

uint16 CTheZones::NumberOfAudioZones;
int16 CTheZones::AudioZoneArray[NUMAUDIOZONES];
uint16 CTheZones::TotalNumberOfMapZones;
uint16 CTheZones::TotalNumberOfInfoZones;
uint16 CTheZones::TotalNumberOfNavigationZones;
CZone CTheZones::InfoZoneArray[NUMINFOZONES];
CZone CTheZones::MapZoneArray[NUMMAPZONES];
CZone CTheZones::NavigationZoneArray[NUMNAVIGZONES];
uint16 CTheZones::TotalNumberOfZoneInfos;
CZoneInfo CTheZones::ZoneInfoArray[2*NUMINFOZONES];


#define SWAPF(a, b) { float t; t = a; a = b; b = t; }

static void
CheckZoneInfo(CZoneInfo *info)
{
	assert(info->carThreshold[0] >= 0);
	assert(info->carThreshold[0] <= info->carThreshold[1]);
	assert(info->carThreshold[1] <= info->carThreshold[2]);
	assert(info->carThreshold[2] <= info->carThreshold[3]);
	assert(info->carThreshold[3] <= info->carThreshold[4]);
	assert(info->carThreshold[4] <= info->carThreshold[5]);
	assert(info->carThreshold[5] <= info->copThreshold);
	assert(info->copThreshold <= info->gangThreshold[0]);
	assert(info->gangThreshold[0] <= info->gangThreshold[1]);
	assert(info->gangThreshold[1] <= info->gangThreshold[2]);
	assert(info->gangThreshold[2] <= info->gangThreshold[3]);
	assert(info->gangThreshold[3] <= info->gangThreshold[4]);
	assert(info->gangThreshold[4] <= info->gangThreshold[5]);
	assert(info->gangThreshold[5] <= info->gangThreshold[6]);
	assert(info->gangThreshold[6] <= info->gangThreshold[7]);
	assert(info->gangThreshold[7] <= info->gangThreshold[8]);
}

//--MIAMI: done
wchar*
CZone::GetTranslatedName(void)
{
	return TheText.Get(name);
}

//--MIAMI: check out zoneinfo
void
CTheZones::Init(void)
{
	int i;
	for(i = 0; i < NUMAUDIOZONES; i++)
		AudioZoneArray[i] = -1;
	NumberOfAudioZones = 0;

	for(i = 0; i < NUMNAVIGZONES; i++)
		memset(&NavigationZoneArray[i], 0, sizeof(CZone));

	for(i = 0; i < NUMINFOZONES; i++)
		memset(&InfoZoneArray[i], 0, sizeof(CZone));

	CZoneInfo *zonei;
	int x = 1000/6;
	for(i = 0; i < 2*NUMINFOZONES; i++){
		zonei = &ZoneInfoArray[i];
		zonei->carDensity = 10;
		zonei->carThreshold[0] = x;
		zonei->carThreshold[1] = zonei->carThreshold[0] + x;
		zonei->carThreshold[2] = zonei->carThreshold[1] + x;
		zonei->carThreshold[3] = zonei->carThreshold[2] + x;
		zonei->carThreshold[4] = zonei->carThreshold[3];
		zonei->carThreshold[5] = zonei->carThreshold[4];
		zonei->copThreshold = zonei->carThreshold[5] + x;
		zonei->gangThreshold[0] = zonei->copThreshold;
		zonei->gangThreshold[1] = zonei->gangThreshold[0];
		zonei->gangThreshold[2] = zonei->gangThreshold[1];
		zonei->gangThreshold[3] = zonei->gangThreshold[2];
		zonei->gangThreshold[4] = zonei->gangThreshold[3];
		zonei->gangThreshold[5] = zonei->gangThreshold[4];
		zonei->gangThreshold[6] = zonei->gangThreshold[5];
		zonei->gangThreshold[7] = zonei->gangThreshold[6];
		zonei->gangThreshold[8] = zonei->gangThreshold[7];
		CheckZoneInfo(zonei);
	}

	TotalNumberOfZoneInfos = 1;	// why 1?
	TotalNumberOfNavigationZones = 1;
	TotalNumberOfInfoZones = 1;

	strcpy(InfoZoneArray[0].name, "CITYINF");
	InfoZoneArray[0].minx = -2400.0f;
	InfoZoneArray[0].miny = -2000.0f;
	InfoZoneArray[0].minz = -500.0f;
	InfoZoneArray[0].maxx =  1600.0f;
	InfoZoneArray[0].maxy =  2000.0f;
	InfoZoneArray[0].maxz =  500.0f;
	InfoZoneArray[0].level = LEVEL_NONE;
	InfoZoneArray[0].type = ZONE_INFO;

	strcpy(NavigationZoneArray[0].name, "VICE_C");
	NavigationZoneArray[0].minx = -2400.0f;
	NavigationZoneArray[0].miny = -2000.0f;
	NavigationZoneArray[0].minz = -500.0f;
	NavigationZoneArray[0].maxx =  1600.0f;
	NavigationZoneArray[0].maxy =  2000.0f;
	NavigationZoneArray[0].maxz =  500.0f;
	NavigationZoneArray[0].level = LEVEL_NONE;
	NavigationZoneArray[0].type = ZONE_NAVIG;

	m_CurrLevel = LEVEL_NONE;

	for(i = 0; i < NUMMAPZONES; i++){
		memset(&MapZoneArray[i], 0, sizeof(CZone));
		MapZoneArray[i].type = ZONE_MAPZONE;
	}
	strcpy(MapZoneArray[0].name, "THEMAP");
	MapZoneArray[0].minx = -2400.0f;
	MapZoneArray[0].miny = -2000.0f;
	MapZoneArray[0].minz = -500.0f;
	MapZoneArray[0].maxx =  1600.0f;
	MapZoneArray[0].maxy =  2000.0f;
	MapZoneArray[0].maxz =  500.0f;
	MapZoneArray[0].level = LEVEL_NONE;
}

//--MIAMI: done
void
CTheZones::Update(void)
{
	CVector pos;
	pos = FindPlayerCoors();
	m_CurrLevel = GetLevelFromPosition(&pos);
}

//--MIAMI: done
void
CTheZones::CreateZone(char *name, eZoneType type,
	              float minx, float miny, float minz,
	              float maxx, float maxy, float maxz,
	              eLevelName level)
{
	char tmpname[24];
	char *p;

	if(minx > maxx) SWAPF(minx, maxx);
	if(miny > maxy) SWAPF(miny, maxy);
	if(minz > maxz) SWAPF(minz, maxz);

	// make upper case
	for(p = name; *p; p++) if(islower(*p)) *p = toupper(*p);

	strncpy(tmpname, name, 7);
	tmpname[7] = '\0';

	// add zone
	switch(type){
	case ZONE_DEFAULT:
	case ZONE_NAVIG:
		assert(TotalNumberOfNavigationZones < NUMNAVIGZONES);
		strcpy(NavigationZoneArray[TotalNumberOfNavigationZones].name, tmpname);
		NavigationZoneArray[TotalNumberOfNavigationZones].type = type;
		NavigationZoneArray[TotalNumberOfNavigationZones].minx = minx;
		NavigationZoneArray[TotalNumberOfNavigationZones].miny = miny;
		NavigationZoneArray[TotalNumberOfNavigationZones].minz = minz;
		NavigationZoneArray[TotalNumberOfNavigationZones].maxx = maxx;
		NavigationZoneArray[TotalNumberOfNavigationZones].maxy = maxy;
		NavigationZoneArray[TotalNumberOfNavigationZones].maxz = maxz;
		NavigationZoneArray[TotalNumberOfNavigationZones].level = level;
		TotalNumberOfNavigationZones++;
		break;
	case ZONE_INFO:
		assert(TotalNumberOfInfoZones < NUMINFOZONES);
		strcpy(InfoZoneArray[TotalNumberOfInfoZones].name, tmpname);
		InfoZoneArray[TotalNumberOfInfoZones].type = type;
		InfoZoneArray[TotalNumberOfInfoZones].minx = minx;
		InfoZoneArray[TotalNumberOfInfoZones].miny = miny;
		InfoZoneArray[TotalNumberOfInfoZones].minz = minz;
		InfoZoneArray[TotalNumberOfInfoZones].maxx = maxx;
		InfoZoneArray[TotalNumberOfInfoZones].maxy = maxy;
		InfoZoneArray[TotalNumberOfInfoZones].maxz = maxz;
		InfoZoneArray[TotalNumberOfInfoZones].level = level;
		InfoZoneArray[TotalNumberOfInfoZones].zoneinfoDay = TotalNumberOfZoneInfos++;
		InfoZoneArray[TotalNumberOfInfoZones].zoneinfoNight = TotalNumberOfZoneInfos++;
		TotalNumberOfInfoZones++;
		break;
	case ZONE_MAPZONE:
		assert(TotalNumberOfMapZones < NUMMAPZONES);
		strcpy(MapZoneArray[TotalNumberOfMapZones].name, tmpname);
		MapZoneArray[TotalNumberOfMapZones].type = type;
		MapZoneArray[TotalNumberOfMapZones].minx = minx;
		MapZoneArray[TotalNumberOfMapZones].miny = miny;
		MapZoneArray[TotalNumberOfMapZones].minz = minz;
		MapZoneArray[TotalNumberOfMapZones].maxx = maxx;
		MapZoneArray[TotalNumberOfMapZones].maxy = maxy;
		MapZoneArray[TotalNumberOfMapZones].maxz = maxz;
		MapZoneArray[TotalNumberOfMapZones].level = level;
		TotalNumberOfMapZones++;
		break;
	}
}

//--MIAMI: done
void
CTheZones::PostZoneCreation(void)
{
	int i;
	for(i = 1; i < TotalNumberOfNavigationZones; i++)
		InsertZoneIntoZoneHierarchy(&NavigationZoneArray[i]);
	InitialiseAudioZoneArray();
}

//--MIAMI: done, but does nothing
void
CTheZones::CheckZonesForOverlap(void)
{
	int i, j;
	char str[116];

	for(i = 1; i < TotalNumberOfInfoZones; i++){
		ZoneIsEntirelyContainedWithinOtherZone(&InfoZoneArray[i], &InfoZoneArray[0]);
		
		for(j = 1; j < TotalNumberOfInfoZones; j++)
			if(i != j && ZoneIsEntirelyContainedWithinOtherZone(&InfoZoneArray[i], &InfoZoneArray[j]))
				sprintf(str, "Info zone %s contains %s\n",
						&InfoZoneArray[j].name, &InfoZoneArray[i].name);
	}
}

//--MIAMI: done
void
CTheZones::InsertZoneIntoZoneHierarchy(CZone *zone)
{
	zone->child = nil;
	zone->parent = nil;
	zone->next = nil;
	InsertZoneIntoZoneHierRecursive(zone, &NavigationZoneArray[0]);
}

//--MIAMI: done
bool
CTheZones::InsertZoneIntoZoneHierRecursive(CZone *inner, CZone *outer)
{
	int n;
	CZone *child, *next, *insert;

	// return false if inner was not inserted into outer
	if(outer == nil ||
	   !ZoneIsEntirelyContainedWithinOtherZone(inner, outer))
		return false;

	// try to insert inner into children of outer
	for(child = outer->child; child; child = child->next)
		if(InsertZoneIntoZoneHierRecursive(inner, child))
			return true;

	// insert inner as child of outer
	// count number of outer's children contained within inner
	n = 0;
	for(child = outer->child; child; child = child->next)
		if(ZoneIsEntirelyContainedWithinOtherZone(child, inner))
			n++;
	inner->next = outer->child;
	inner->parent = outer;
	outer->child = inner;
	// move children from outer to inner
	if(n){
		insert = inner;
		for(child = inner->next; child; child = next){
			next = child->next;
			if(ZoneIsEntirelyContainedWithinOtherZone(child,inner)){
				insert->next = child->next;
				child->parent = inner;
				child->next = inner->child;
				inner->child = child;
			}else
				insert = child;
		}
	}

	return true;
}

//--MIAMI: done
bool
CTheZones::ZoneIsEntirelyContainedWithinOtherZone(CZone *inner, CZone *outer)
{
	char tmp[100];

	if(inner->minx < outer->minx ||
	   inner->maxx > outer->maxx ||
	   inner->miny < outer->miny ||
	   inner->maxy > outer->maxy ||
	   inner->minz < outer->minz ||
	   inner->maxz > outer->maxz){
		CVector vmin(inner->minx, inner->miny, inner->minz);
		if(PointLiesWithinZone(&vmin, outer))
			sprintf(tmp, "Overlapping zones %s and %s\n",
			      inner->name, outer->name);
		CVector vmax(inner->maxx, inner->maxy, inner->maxz);
		if(PointLiesWithinZone(&vmax, outer))
			sprintf(tmp, "Overlapping zones %s and %s\n",
			      inner->name, outer->name);
		return false;
	}
	return true;
}

//--MIAMI: done
bool
CTheZones::PointLiesWithinZone(const CVector *v, CZone *zone)
{
	return zone->minx <= v->x && v->x <= zone->maxx &&
	       zone->miny <= v->y && v->y <= zone->maxy &&
	       zone->minz <= v->z && v->z <= zone->maxz;
}

//--MIAMI: done
eLevelName
CTheZones::GetLevelFromPosition(const CVector *v)
{
	int i;
//	char tmp[116];
//	if(!PointLiesWithinZone(v, &MapZoneArray[0]))
//		sprintf(tmp, "x = %.3f y= %.3f z = %.3f\n", v.x, v.y, v.z);
	for(i = 1; i < TotalNumberOfMapZones; i++)
		if(PointLiesWithinZone(v, &MapZoneArray[i]))
			return MapZoneArray[i].level;
	return MapZoneArray[0].level;
}

//--MIAMI: done
CZone*
CTheZones::FindInformationZoneForPosition(const CVector *v)
{
	int i;
//	char tmp[116];
//	if(!PointLiesWithinZone(v, &InfoZoneArray[0]))
//		sprintf(tmp, "x = %.3f y= %.3f z = %.3f\n", v.x, v.y, v.z);
	for(i = 1; i < TotalNumberOfInfoZones; i++)
		if(PointLiesWithinZone(v, &InfoZoneArray[i]))
			return &InfoZoneArray[i];
	return &InfoZoneArray[0];
}

//--MIAMI: done
CZone*
CTheZones::FindSmallestNavigationZoneForPosition(const CVector *v, bool findDefault, bool findNavig)
{
	CZone *best = nil;
	if(findDefault && NavigationZoneArray[0].type == ZONE_DEFAULT ||
	   findNavig && NavigationZoneArray[0].type == ZONE_NAVIG)
		best = &NavigationZoneArray[0];
	// zone to test next
	CZone *zone = NavigationZoneArray[0].child;
	while(zone)
		// if in zone, descent into children
		if(PointLiesWithinZone(v, zone)){
			if(findDefault && zone->type == ZONE_DEFAULT ||
			   findNavig && zone->type == ZONE_NAVIG)
				best = zone;
			zone = zone->child;
		// otherwise try next zone
		}else
			zone = zone->next;
	return best;
}

//--MIAMI: done
int16
CTheZones::FindZoneByLabelAndReturnIndex(char *name, eZoneType type)
{
	char str[8];
	memset(str, 0, 8);
	strncpy(str, name, 8);
	switch(type){
	case ZONE_DEFAULT:
	case ZONE_NAVIG:
		for(FindIndex = 0; FindIndex < TotalNumberOfNavigationZones; FindIndex++)
			if(strcmp(GetNavigationZone(FindIndex)->name, name) == 0)
				return FindIndex;
		break;

	case ZONE_INFO:
		for(FindIndex = 0; FindIndex < TotalNumberOfInfoZones; FindIndex++)
			if(strcmp(GetInfoZone(FindIndex)->name, name) == 0)
				return FindIndex;
		break;

	case ZONE_MAPZONE:
		for(FindIndex = 0; FindIndex < TotalNumberOfMapZones; FindIndex++)
			if(strcmp(GetMapZone(FindIndex)->name, name) == 0)
				return FindIndex;
		break;
	}
	return -1;
}

//--MIAMI: done
int16
CTheZones::FindNextZoneByLabelAndReturnIndex(char *name, eZoneType type)
{
	char str[8];
	memset(str, 0, 8);
	strncpy(str, name, 8);
	switch(type){
	case ZONE_DEFAULT:
	case ZONE_NAVIG:
		for(; FindIndex < TotalNumberOfNavigationZones; FindIndex++)
			if(strcmp(GetNavigationZone(FindIndex)->name, name) == 0)
				return FindIndex;
		break;

	case ZONE_INFO:
		for(; FindIndex < TotalNumberOfInfoZones; FindIndex++)
			if(strcmp(GetInfoZone(FindIndex)->name, name) == 0)
				return FindIndex;
		break;

	case ZONE_MAPZONE:
		for(; FindIndex < TotalNumberOfMapZones; FindIndex++)
			if(strcmp(GetMapZone(FindIndex)->name, name) == 0)
				return FindIndex;
		break;
	}
	return -1;
}

//--MIAMI: done
CZoneInfo*
CTheZones::GetZoneInfo(const CVector *v, uint8 day)
{
	CZone *zone;
	zone = FindInformationZoneForPosition(v);
	if(zone == nil)
		return &ZoneInfoArray[0];
	return &ZoneInfoArray[day ? zone->zoneinfoDay : zone->zoneinfoNight];
}

void
CTheZones::GetZoneInfoForTimeOfDay(const CVector *pos, CZoneInfo *info)
{
	CZoneInfo *day, *night;
	float d, n;

	day = GetZoneInfo(pos, 1);
	night = GetZoneInfo(pos, 0);

	if(CClock::GetIsTimeInRange(8, 19))
		*info = *day;
	else if(CClock::GetIsTimeInRange(22, 5))
		*info = *night;
	else{
		if(CClock::GetIsTimeInRange(19, 22)){
			n = (CClock::GetHours() - 19) / 3.0f;
			assert(n >= 0.0f && n <= 1.0f);
			d = 1.0f - n;
		}else{
			d = (CClock::GetHours() - 5) / 3.0f;
			assert(d >= 0.0f && d <= 1.0f);
			n = 1.0f - d;
		}
		info->carDensity = day->carDensity * d + night->carDensity * n;
		info->carThreshold[0] = day->carThreshold[0] * d + night->carThreshold[0] * n;
		info->carThreshold[1] = day->carThreshold[1] * d + night->carThreshold[1] * n;
		info->carThreshold[2] = day->carThreshold[2] * d + night->carThreshold[2] * n;
		info->carThreshold[3] = day->carThreshold[3] * d + night->carThreshold[3] * n;
		info->carThreshold[4] = day->carThreshold[4] * d + night->carThreshold[4] * n;
		info->carThreshold[5] = day->carThreshold[5] * d + night->carThreshold[5] * n;
		info->copThreshold = day->copThreshold * d + night->copThreshold * n;
		info->gangThreshold[0] = day->gangThreshold[0] * d + night->gangThreshold[0] * n;
		info->gangThreshold[1] = day->gangThreshold[1] * d + night->gangThreshold[1] * n;
		info->gangThreshold[2] = day->gangThreshold[2] * d + night->gangThreshold[2] * n;
		info->gangThreshold[3] = day->gangThreshold[3] * d + night->gangThreshold[3] * n;
		info->gangThreshold[4] = day->gangThreshold[4] * d + night->gangThreshold[4] * n;
		info->gangThreshold[5] = day->gangThreshold[5] * d + night->gangThreshold[5] * n;
		info->gangThreshold[6] = day->gangThreshold[6] * d + night->gangThreshold[6] * n;
		info->gangThreshold[7] = day->gangThreshold[7] * d + night->gangThreshold[7] * n;
		info->gangThreshold[8] = day->gangThreshold[8] * d + night->gangThreshold[8] * n;

		info->pedDensity = day->pedDensity * d + night->pedDensity * n;
		info->copDensity = day->copDensity * d + night->copDensity * n;
		info->gangDensity[0] = day->gangDensity[0] * d + night->gangDensity[0] * n;
		info->gangDensity[1] = day->gangDensity[1] * d + night->gangDensity[1] * n;
		info->gangDensity[2] = day->gangDensity[2] * d + night->gangDensity[2] * n;
		info->gangDensity[3] = day->gangDensity[3] * d + night->gangDensity[3] * n;
		info->gangDensity[4] = day->gangDensity[4] * d + night->gangDensity[4] * n;
		info->gangDensity[5] = day->gangDensity[5] * d + night->gangDensity[5] * n;
		info->gangDensity[6] = day->gangDensity[6] * d + night->gangDensity[6] * n;
		info->gangDensity[7] = day->gangDensity[7] * d + night->gangDensity[7] * n;
		info->gangDensity[8] = day->gangDensity[8] * d + night->gangDensity[8] * n;
	}
	if(CClock::GetIsTimeInRange(5, 19))
		info->pedGroup = day->pedGroup;
	else
		info->pedGroup = night->pedGroup;

	CheckZoneInfo(info);
}

void
CTheZones::SetZoneCarInfo(uint16 zoneid, uint8 day, int16 carDensity,
	int16 gang0Num, int16 gang1Num, int16 gang2Num,
	int16 gang3Num, int16 gang4Num, int16 gang5Num,
	int16 gang6Num, int16 gang7Num, int16 gang8Num,
	int16 copNum,
	int16 car0Num, int16 car1Num, int16 car2Num,
	int16 car3Num, int16 car4Num, int16 car5Num)
{
	CZone *zone;
	CZoneInfo *info;
	zone = GetInfoZone(zoneid);
	info = &ZoneInfoArray[day ? zone->zoneinfoDay : zone->zoneinfoNight];

	CheckZoneInfo(info);

	if(carDensity != -1) info->carDensity = carDensity;
	int16 oldCar1Num = info->carThreshold[1] - info->carThreshold[0];
	int16 oldCar2Num = info->carThreshold[2] - info->carThreshold[1];
	int16 oldCar3Num = info->carThreshold[3] - info->carThreshold[2];
	int16 oldCar4Num = info->carThreshold[4] - info->carThreshold[3];
	int16 oldCar5Num = info->carThreshold[5] - info->carThreshold[4];
	int16 oldCopNum = info->copThreshold - info->carThreshold[5];
	int16 oldGang0Num = info->gangThreshold[0] - info->copThreshold;
	int16 oldGang1Num = info->gangThreshold[1] - info->gangThreshold[0];
	int16 oldGang2Num = info->gangThreshold[2] - info->gangThreshold[1];
	int16 oldGang3Num = info->gangThreshold[3] - info->gangThreshold[2];
	int16 oldGang4Num = info->gangThreshold[4] - info->gangThreshold[3];
	int16 oldGang5Num = info->gangThreshold[5] - info->gangThreshold[4];
	int16 oldGang6Num = info->gangThreshold[6] - info->gangThreshold[5];
	int16 oldGang7Num = info->gangThreshold[7] - info->gangThreshold[6];
	int16 oldGang8Num = info->gangThreshold[8] - info->gangThreshold[7];

	if(car0Num != -1) info->carThreshold[0] = car0Num;
	if(car1Num != -1) info->carThreshold[1] = info->carThreshold[0] + car1Num;
	else              info->carThreshold[1] = info->carThreshold[0] + oldCar1Num;
	if(car2Num != -1) info->carThreshold[2] = info->carThreshold[1] + car2Num;
	else              info->carThreshold[2] = info->carThreshold[1] + oldCar2Num;
	if(car3Num != -1) info->carThreshold[3] = info->carThreshold[2] + car3Num;
	else              info->carThreshold[3] = info->carThreshold[2] + oldCar3Num;
	if(car4Num != -1) info->carThreshold[4] = info->carThreshold[3] + car4Num;
	else              info->carThreshold[4] = info->carThreshold[3] + oldCar4Num;
	if(car5Num != -1) info->carThreshold[5] = info->carThreshold[4] + car5Num;
	else              info->carThreshold[5] = info->carThreshold[4] + oldCar5Num;
	if(copNum != -1) info->copThreshold = info->carThreshold[5] + copNum;
	else             info->copThreshold = info->carThreshold[5] + oldCopNum;
	if(gang0Num != -1) info->gangThreshold[0] = info->copThreshold + gang0Num;
	else               info->gangThreshold[0] = info->copThreshold + oldGang0Num;
	if(gang1Num != -1) info->gangThreshold[1] = info->gangThreshold[0] + gang1Num;
	else               info->gangThreshold[1] = info->gangThreshold[0] + oldGang1Num;
	if(gang2Num != -1) info->gangThreshold[2] = info->gangThreshold[1] + gang2Num;
	else               info->gangThreshold[2] = info->gangThreshold[1] + oldGang2Num;
	if(gang3Num != -1) info->gangThreshold[3] = info->gangThreshold[2] + gang3Num;
	else               info->gangThreshold[3] = info->gangThreshold[2] + oldGang3Num;
	if(gang4Num != -1) info->gangThreshold[4] = info->gangThreshold[3] + gang4Num;
	else               info->gangThreshold[4] = info->gangThreshold[3] + oldGang4Num;
	if(gang5Num != -1) info->gangThreshold[5] = info->gangThreshold[4] + gang5Num;
	else               info->gangThreshold[5] = info->gangThreshold[4] + oldGang5Num;
	if(gang6Num != -1) info->gangThreshold[6] = info->gangThreshold[5] + gang6Num;
	else               info->gangThreshold[6] = info->gangThreshold[5] + oldGang6Num;
	if(gang7Num != -1) info->gangThreshold[7] = info->gangThreshold[6] + gang7Num;
	else               info->gangThreshold[7] = info->gangThreshold[6] + oldGang7Num;
	if(gang8Num != -1) info->gangThreshold[8] = info->gangThreshold[7] + gang8Num;
	else               info->gangThreshold[8] = info->gangThreshold[7] + oldGang8Num;

	CheckZoneInfo(info);
}

void
CTheZones::SetZonePedInfo(uint16 zoneid, uint8 day, int16 pedDensity,
	int16 gang0Density, int16 gang1Density, int16 gang2Density, int16 gang3Density,
	int16 gang4Density, int16 gang5Density, int16 gang6Density, int16 gang7Density,
	int16 gang8Density, int16 copDensity)
{
	CZone *zone;
	CZoneInfo *info;
	zone = GetInfoZone(zoneid);
	info = &ZoneInfoArray[day ? zone->zoneinfoDay : zone->zoneinfoNight];
	if(pedDensity != -1) info->pedDensity = pedDensity;
	if(copDensity != -1) info->copDensity = copDensity;
	if(gang0Density != -1) info->gangDensity[0] = gang0Density;
	if(gang1Density != -1) info->gangDensity[1] = gang1Density;
	if(gang2Density != -1) info->gangDensity[2] = gang2Density;
	if(gang3Density != -1) info->gangDensity[3] = gang3Density;
	if(gang4Density != -1) info->gangDensity[4] = gang4Density;
	if(gang5Density != -1) info->gangDensity[5] = gang5Density;
	if(gang6Density != -1) info->gangDensity[6] = gang6Density;
	if(gang7Density != -1) info->gangDensity[7] = gang7Density;
	if(gang8Density != -1) info->gangDensity[8] = gang8Density;
}

//--MIAMI: done, unused
void
CTheZones::SetCarDensity(uint16 zoneid, uint8 day, uint16 cardensity)
{
	CZone *zone;
	zone = GetInfoZone(zoneid);
	ZoneInfoArray[day ? zone->zoneinfoDay : zone->zoneinfoNight].carDensity = cardensity;
}

//--MIAMI: done, unused
void
CTheZones::SetPedDensity(uint16 zoneid, uint8 day, uint16 peddensity)
{
	CZone *zone;
	zone = GetInfoZone(zoneid);
	ZoneInfoArray[day ? zone->zoneinfoDay : zone->zoneinfoNight].pedDensity = peddensity;
}

//--MIAMI: done
void
CTheZones::SetPedGroup(uint16 zoneid, uint8 day, uint16 pedgroup)
{
	CZone *zone;
	zone = GetInfoZone(zoneid);
	ZoneInfoArray[day ? zone->zoneinfoDay : zone->zoneinfoNight].pedGroup = pedgroup;
}

//--MIAMI: done
int16
CTheZones::FindAudioZone(CVector *pos)
{
	int i;

	for(i = 0; i < NumberOfAudioZones; i++)
		if(PointLiesWithinZone(pos, GetAudioZone(i)))
			return i;
	return -1;
}

//--MIAMI: done
void
CTheZones::AddZoneToAudioZoneArray(CZone *zone)
{
	int i, z;

	if(zone->type != ZONE_DEFAULT)
		return;

	/* This is a bit stupid */
	z = -1;
	for(i = 0; i < NUMNAVIGZONES; i++)
		if(&NavigationZoneArray[i] == zone)
			z = i;
	assert(NumberOfAudioZones < NUMAUDIOZONES);
	AudioZoneArray[NumberOfAudioZones++] = z;
}

//--MIAMI: done
void
CTheZones::InitialiseAudioZoneArray(void)
{
	bool gonext;
	CZone *zone;

	gonext = false;
	zone = &NavigationZoneArray[0];
	// Go deep first,
	// set gonext when backing up a level to visit the next child
	while(zone)
		if(gonext){
			AddZoneToAudioZoneArray(zone);
			if(zone->next){
				gonext = false;
				zone = zone->next;
			}else
				zone = zone->parent;
		}else if(zone->child)
			zone = zone->child;
		else{
			AddZoneToAudioZoneArray(zone);
			if(zone->next)
				zone = zone->next;
			else{
				gonext = true;
				zone = zone->parent;
			}
		}
}

//--MIAMI: TODO
void
CTheZones::SaveAllZones(uint8 *buffer, uint32 *size)
{
	INITSAVEBUF
	int i;

	*size = SAVE_HEADER_SIZE
		+ sizeof(m_CurrLevel) + sizeof(FindIndex)
		+ sizeof(int16) // padding
		+ sizeof(NavigationZoneArray) + sizeof(InfoZoneArray) + sizeof(ZoneInfoArray)
		+ sizeof(TotalNumberOfNavigationZones) + sizeof(TotalNumberOfInfoZones) + sizeof(TotalNumberOfZoneInfos)
		+ sizeof(MapZoneArray) + sizeof(AudioZoneArray)
		+ sizeof(TotalNumberOfMapZones) + sizeof(NumberOfAudioZones);

	WriteSaveHeader(buffer, 'Z', 'N', 'S', '\0', *size - SAVE_HEADER_SIZE);

	WriteSaveBuf(buffer, m_CurrLevel);
	WriteSaveBuf(buffer, FindIndex);
	WriteSaveBuf(buffer, (int16)0); // padding

// TODO(MIAMI): implement SaveOneZone
	for(i = 0; i < ARRAY_SIZE(NavigationZoneArray); i++){
		CZone *zone = WriteSaveBuf(buffer, NavigationZoneArray[i]);
		zone->child = (CZone*)GetIndexForZonePointer(NavigationZoneArray[i].child);
		zone->parent = (CZone*)GetIndexForZonePointer(NavigationZoneArray[i].parent);
		zone->next = (CZone*)GetIndexForZonePointer(NavigationZoneArray[i].next);
	}

	for(i = 0; i < ARRAY_SIZE(InfoZoneArray); i++){
		CZone *zone = WriteSaveBuf(buffer, InfoZoneArray[i]);
		zone->child = (CZone*)GetIndexForZonePointer(InfoZoneArray[i].child);
		zone->parent = (CZone*)GetIndexForZonePointer(InfoZoneArray[i].parent);
		zone->next = (CZone*)GetIndexForZonePointer(InfoZoneArray[i].next);
	}

	for(i = 0; i < ARRAY_SIZE(ZoneInfoArray); i++)
		WriteSaveBuf(buffer, ZoneInfoArray[i]);

	WriteSaveBuf(buffer, TotalNumberOfNavigationZones);
	WriteSaveBuf(buffer, TotalNumberOfInfoZones);
	WriteSaveBuf(buffer, TotalNumberOfZoneInfos);

	for(i = 0; i < ARRAY_SIZE(MapZoneArray); i++) {
		CZone* zone = WriteSaveBuf(buffer, MapZoneArray[i]);

		/*
		The call of GetIndexForZonePointer is wrong, as it is
		meant for a different array, but the game doesn't brake
		if those fields are nil. Let's make sure they are.
		*/
		assert(MapZoneArray[i].child == nil);
		assert(MapZoneArray[i].parent == nil);
		assert(MapZoneArray[i].next == nil);
		zone->child = (CZone*)GetIndexForZonePointer(MapZoneArray[i].child);
		zone->parent = (CZone*)GetIndexForZonePointer(MapZoneArray[i].parent);
		zone->next = (CZone*)GetIndexForZonePointer(MapZoneArray[i].next);
	}

	for(i = 0; i < ARRAY_SIZE(AudioZoneArray); i++)
		WriteSaveBuf(buffer, AudioZoneArray[i]);

	WriteSaveBuf(buffer, TotalNumberOfMapZones);
	WriteSaveBuf(buffer, NumberOfAudioZones);

	VALIDATESAVEBUF(*size)
}

//--MIAMI: TODO
void
CTheZones::LoadAllZones(uint8 *buffer, uint32 size)
{
	INITSAVEBUF
	int i;

	CheckSaveHeader(buffer, 'Z', 'N', 'S', '\0', size - SAVE_HEADER_SIZE);

	m_CurrLevel = ReadSaveBuf<eLevelName>(buffer);
	FindIndex = ReadSaveBuf<int16>(buffer);
	ReadSaveBuf<int16>(buffer);

// TODO(MIAMI): implement LoadOneZone
	for(i = 0; i < ARRAY_SIZE(NavigationZoneArray); i++){
		NavigationZoneArray[i] = ReadSaveBuf<CZone>(buffer);

		NavigationZoneArray[i].child = GetPointerForZoneIndex((int32)NavigationZoneArray[i].child);
		NavigationZoneArray[i].parent = GetPointerForZoneIndex((int32)NavigationZoneArray[i].parent);
		NavigationZoneArray[i].next = GetPointerForZoneIndex((int32)NavigationZoneArray[i].next);
	}

	for(i = 0; i < ARRAY_SIZE(InfoZoneArray); i++){
		InfoZoneArray[i] = ReadSaveBuf<CZone>(buffer);

		InfoZoneArray[i].child = GetPointerForZoneIndex((int32)InfoZoneArray[i].child);
		InfoZoneArray[i].parent = GetPointerForZoneIndex((int32)InfoZoneArray[i].parent);
		InfoZoneArray[i].next = GetPointerForZoneIndex((int32)InfoZoneArray[i].next);
	}

	for(i = 0; i < ARRAY_SIZE(ZoneInfoArray); i++)
		ZoneInfoArray[i] = ReadSaveBuf<CZoneInfo>(buffer);

	TotalNumberOfNavigationZones = ReadSaveBuf<int16>(buffer);
	TotalNumberOfInfoZones = ReadSaveBuf<int16>(buffer);
	TotalNumberOfZoneInfos = ReadSaveBuf<int16>(buffer);

	for(i = 0; i < ARRAY_SIZE(MapZoneArray); i++){
		MapZoneArray[i] = ReadSaveBuf<CZone>(buffer);

		/*
		The call of GetPointerForZoneIndex is wrong, as it is
		meant for a different array, but the game doesn't brake
		if save data stored is -1.
		*/
		MapZoneArray[i].child = GetPointerForZoneIndex((int32)MapZoneArray[i].child);
		MapZoneArray[i].parent = GetPointerForZoneIndex((int32)MapZoneArray[i].parent);
		MapZoneArray[i].next = GetPointerForZoneIndex((int32)MapZoneArray[i].next);
		assert(MapZoneArray[i].child == nil);
		assert(MapZoneArray[i].parent == nil);
		assert(MapZoneArray[i].next == nil);
	}

	for(i = 0; i < ARRAY_SIZE(AudioZoneArray); i++)
		AudioZoneArray[i] = ReadSaveBuf<int16>(buffer);

	TotalNumberOfMapZones = ReadSaveBuf<uint16>(buffer);
	NumberOfAudioZones = ReadSaveBuf<uint16>(buffer);

	VALIDATESAVEBUF(size)
}
