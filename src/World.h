#pragma once

#include "Game.h"
#include "Lists.h"

/* Sectors span from -2000 to 2000 in x and y.
 * With 100x100 sectors, each is 40x40 units. */

#define NUMSECTORS_X 100
#define NUMSECTORS_Y 100

enum
{
	ENTITYLIST_BUILDINGS,
	ENTITYLIST_BUILDINGS_OVERLAP,
	ENTITYLIST_OBJECTS,
	ENTITYLIST_OBJECTS_OVERLAP,
	ENTITYLIST_VEHICLES,
	ENTITYLIST_VEHICLES_OVERLAP,
	ENTITYLIST_PEDS,
	ENTITYLIST_PEDS_OVERLAP,
	ENTITYLIST_DUMMIES,
	ENTITYLIST_DUMMIES_OVERLAP,

	NUMSECTORENTITYLISTS
};

class CSector
{
public:
	CPtrList m_lists[NUMSECTORENTITYLISTS];
};
static_assert(sizeof(CSector) == 0x28, "CSector: error");

class CEntity;

class CWorld
{
	static CPtrList *ms_bigBuildingsList;	// [4];
	static CPtrList &ms_listMovingEntityPtrs;
	static CSector (*ms_aSectors)[NUMSECTORS_X];	// [NUMSECTORS_Y][NUMSECTORS_X];
	static uint16 &ms_nCurrentScanCode;

public:
	static CEntity *&pIgnoreEntity;
	static bool &bNoMoreCollisionTorque;
	static bool &bSecondShift;
	static bool &bForceProcessControl;
	static bool &bProcessCutsceneOnly;


	static CSector *GetSector(int x, int y) { return &ms_aSectors[y][x]; }
	static CPtrList &GetBigBuildingList(eLevelName i) { return ms_bigBuildingsList[i]; }
	static CPtrList &GetMovingEntityList(void) { return ms_listMovingEntityPtrs; }
	static uint16 GetCurrentScanCode(void) { return ms_nCurrentScanCode; }
	static void AdvanceCurrentScanCode(void){
		if(++CWorld::ms_nCurrentScanCode == 0){
			CWorld::ClearScanCodes();
			CWorld::ms_nCurrentScanCode = 1;
		}
	}
	static void ClearScanCodes(void);

	static float GetSectorX(float f) { return ((f + 2000.0f)/40.0f); }
	static float GetSectorY(float f) { return ((f + 2000.0f)/40.0f); }
	static int GetSectorIndexX(float f) { return (int)GetSectorX(f); }
	static int GetSectorIndexY(float f) { return (int)GetSectorY(f); }
};

CVector &FindPlayerCoors(CVector &v);
class CVehicle;
CVehicle *FindPlayerVehicle(void);
CVehicle *FindPlayerTrain(void);
