#pragma once

#include "templates.h"
#include "Lists.h"
#include "Treadable.h"
#include "Object.h"
#include "CutsceneHead.h"

typedef CPool<CPtrNode> CCPtrNodePool;
typedef CPool<CEntryInfoNode> CEntryInfoNodePool;
typedef CPool<CBuilding> CBuildingPool;
typedef CPool<CTreadable> CTreadablePool;
typedef CPool<CObject, CCutsceneHead> CObjectPool;

class CPools
{
	static CCPtrNodePool *&ms_pPtrNodePool;
	static CEntryInfoNodePool *&ms_pEntryInfoNodePool;
	// ms_pPedPool
	// ms_pVehiclePool
	static CBuildingPool *&ms_pBuildingPool;
	static CTreadablePool *&ms_pTreadablePool;
	static CObjectPool *&ms_pObjectPool;
	// ms_pDummyPool
	// ms_pAudioScriptObjectPool
public:
	static CCPtrNodePool *GetPtrNodePool(void) { return ms_pPtrNodePool; }
	static CEntryInfoNodePool *GetEntryInfoNodePool(void) { return ms_pEntryInfoNodePool; }
	static CBuildingPool *GetBuildingPool(void) { return ms_pBuildingPool; }
	static CTreadablePool *GetTreadablePool(void) { return ms_pTreadablePool; }
	static CObjectPool *GetObjectPool(void) { return ms_pObjectPool; }

	static void Initialise(void);
};
