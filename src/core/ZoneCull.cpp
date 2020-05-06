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

int32     CCullZones::NumAttributeZones;
CAttributeZone CCullZones::aAttributeZones[NUMATTRIBZONES];

int32 CCullZones::CurrentWantedLevelDrop_Player;
int32 CCullZones::CurrentFlags_Camera;
int32 CCullZones::CurrentFlags_Player;
bool CCullZones::bCurrentSubwayIsInvisible;

void
CCullZones::Init(void)
{
	NumAttributeZones = 0;
	CurrentWantedLevelDrop_Player = 0;
	CurrentFlags_Camera = 0;
	CurrentFlags_Player = 0;
	bCurrentSubwayIsInvisible = false;
}

void
CCullZones::Update(void)
{
	bool invisible;

	switch(CTimer::GetFrameCounter() & 7){
	case 0:
	case 4:
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
	CAttributeZone *attrib;

	assert(NumAttributeZones < NUMATTRIBZONES);
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
