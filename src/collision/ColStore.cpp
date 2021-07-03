#include "common.h"

#include "main.h"
#include "smallHeap.h"
#include "templates.h"
#include "General.h"
#include "ModelInfo.h"
#include "Streaming.h"
#include "FileLoader.h"
#include "Script.h"
#include "Timer.h"
#include "Camera.h"
#include "World.h"
#include "Zones.h"
#include "Garages.h"
#include "Frontend.h"
#include "Physical.h"
#include "ColStore.h"
#include "VarConsole.h"
#include "Pools.h"

CPool<ColDef,ColDef> *CColStore::ms_pColPool;
bool CColStore::m_onlyBB;
#ifndef MASTER
bool bDispColInMem;
#endif

// LCS: file done except unused:
// CColStore::LoadCol(int,char const*)
// CColStore::LoadAllBoundingBoxes(void)
// CColStore::Write(base::cRelocatableChunkWriter &)

const CVector&
LevelPos(eLevelName level)
{
	static CVector pos[4] = {
		CVector(1060.0f, -800.0f, 0.0f),
		CVector(1060.0f, -800.0f, 0.0f),
		CVector(350.0f, -624.0f, 0.0f),
		CVector(-670.0f, -511.0f, 0.0f)
	};
	return pos[level];
};

static eLevelName
PosLevel(const CVector &pos)
{
	static eLevelName lastPlayerLevel = LEVEL_INDUSTRIAL;
	static eLevelName lastOtherLevel = LEVEL_INDUSTRIAL;

	if(Abs(FindPlayerCoors().x - pos.x) < 5.0f &&
	   Abs(FindPlayerCoors().y - pos.y) < 5.0f &&
	   Abs(FindPlayerCoors().z - pos.z) < 5.0f){
		if(CGame::currLevel != LEVEL_GENERIC)
			lastPlayerLevel = CGame::currLevel;
		return lastPlayerLevel;
	}else{
		eLevelName lvl = CTheZones::GetLevelFromPosition(&pos);
		if(lvl != LEVEL_GENERIC)
			lastOtherLevel = lvl;
		return lastOtherLevel;
	}
}

void
CColStore::Initialise(void)
{
	if(ms_pColPool == nil){
		ms_pColPool = new CPool<ColDef,ColDef>(COLSTORESIZE, "CollisionFiles");
		AddColSlot("generic");	// slot 0. not streamed
	}
#ifndef MASTER
	VarConsole.Add("Display collision in memory", &bDispColInMem, true);
#endif
}

void
CColStore::Shutdown(void)
{
	int i;
	for(i = 0; i < COLSTORESIZE; i++)
		RemoveColSlot(i);
	if(ms_pColPool)
		delete ms_pColPool;
#ifdef FIX_BUGS
	ms_pColPool = nil;
#endif
}

int
CColStore::AddColSlot(const char *name)
{
	ColDef *def = ms_pColPool->New();
	assert(def);
	def->isLoaded = false;
	def->unused = 0;
	def->bounds.left = 1000000.0f;
	def->bounds.top = 1000000.0f;
	def->bounds.right = -1000000.0f;
	def->bounds.bottom = -1000000.0f;
	def->minIndex = INT16_MAX;
	def->maxIndex = INT16_MIN;
	strcpy(def->name, name);
	return ms_pColPool->GetJustIndex(def);
}

void
CColStore::RemoveColSlot(int slot)
{
	if(GetSlot(slot)){
		if(GetSlot(slot)->isLoaded)
			RemoveCol(slot);
		ms_pColPool->Delete(GetSlot(slot));
	}
}

int
CColStore::FindColSlot(const char *name)
{
	ColDef *def;
	int size = ms_pColPool->GetSize();
	for(int i = 0; i < size; i++){
		def = GetSlot(i);
		if(def && !CGeneral::faststricmp(def->name, name))
			return i;
	}
	return -1;
}

char*
CColStore::GetColName(int32 slot)
{
	return GetSlot(slot)->name;
}

CRect&
CColStore::GetBoundingBox(int32 slot)
{
	return GetSlot(slot)->bounds;
}

void
CColStore::IncludeModelIndex(int32 slot, int32 modelIndex)
{
	ColDef *def = GetSlot(slot);
	if(modelIndex < def->minIndex)
		def->minIndex = modelIndex;
	if(modelIndex > def->maxIndex)
		def->maxIndex = modelIndex;
}

bool
CColStore::LoadCol(int32 slot, uint8 *buffer, int32 bufsize)
{
	bool success;
	ColDef *def = GetSlot(slot);
	if(def->minIndex > def->maxIndex)
		success = CFileLoader::LoadCollisionFileFirstTime(buffer, bufsize, slot);
	else
		success = CFileLoader::LoadCollisionFile(buffer, bufsize, slot);
	if(success)
		def->isLoaded = true;
	else
		debug("Failed to load Collision\n");
	return success;
}

struct ColChunkEntry
{
	int32 modelId;	// -1 marks end
	CColModel *colModel;
};

void
CColStore::LoadColCHK(int32 slot, void *data, void *chunk)
{
	ColDef *def = GetSlot(slot);
	def->chunk = chunk;
	CStreaming::RegisterPointer(&def->chunk, 1, true);
	for(ColChunkEntry *entry = (ColChunkEntry*)data; entry->modelId != -1; entry++){
		CBaseModelInfo *mi = CModelInfo::GetModelInfo(entry->modelId);
		mi->SetColModel(entry->colModel, true);	// we own this? can that work?
		CStreaming::RegisterPointer(&mi->m_colModel, 1, true);
	}
	def->isLoaded = true;
}

CColModel nullCollision;

void
CColStore::RemoveCol(int32 slot)
{
	int id;
	ColDef *def = GetSlot(slot);
	def->isLoaded = false;
	for(id = 0; id < MODELINFOSIZE; id++){
		CBaseModelInfo *mi = CModelInfo::GetModelInfo(id);
		if(mi){
			CColModel *col = mi->GetColModel();
			if(col && col->level == slot)
				col->RemoveCollisionVolumes();
		}
	}
	if(gUseChunkFiles){
		for(id = 0; id < MODELINFOSIZE; id++){
			CBaseModelInfo *mi = CModelInfo::GetModelInfo(id);
			if(mi){
				CColModel *col = mi->GetColModel();
				if(col && col->level == slot){
					mi->SetColModel(&nullCollision);
					CStreaming::UnregisterPointer(&mi->m_colModel, 1);
				}
			}
		}
		if(def->chunk){
			CStreaming::UnregisterPointer(&def->chunk, 1);
			cSmallHeap::msInstance.Free(def->chunk);
			def->chunk = nil;
		}
	}
}

void
CColStore::LoadAllCollision(void)
{
	int i;
	for(i = 1; i < COLSTORESIZE; i++)
		if(GetSlot(i))
			CStreaming::RequestCol(i, 0);

	CStreaming::LoadAllRequestedModels(false);
}

void
CColStore::RemoveAllCollision(void)
{
	int i;
	for(i = 1; i < COLSTORESIZE; i++)
		if(GetSlot(i))
			if(CStreaming::CanRemoveCol(i))
				CStreaming::RemoveCol(i);
}

static bool bLoadAtSecondPosition;
static CVector secondPosition;

void
CColStore::AddCollisionNeededAtPosn(const CVector &pos)
{
	bLoadAtSecondPosition = true;
	secondPosition = pos;
}

void
CColStore::LoadCollision(const CVector &pos, eLevelName level)
{
	int i;

	if(CStreaming::ms_disableStreaming)
		return;

	if(level == LEVEL_GENERIC)
		level = PosLevel(pos);

	eLevelName allowedLevel = (eLevelName)CTheScripts::AllowedCollision[0];
	if(allowedLevel == LEVEL_GENERIC)
		allowedLevel = (eLevelName)CTheScripts::AllowedCollision[1];

	bool requestedSomething = false;

	for(i = 1; i < COLSTORESIZE; i++){
		if(GetSlot(i) == nil || !DoScriptsWantThisIn(i))
			continue;

		bool wantThisOne = false;

		if(strcmp(GetColName(i), "indust") == 0){
			if(allowedLevel != LEVEL_GENERIC && level != LEVEL_INDUSTRIAL)
				wantThisOne = allowedLevel == LEVEL_INDUSTRIAL;
			else
				wantThisOne = level == LEVEL_INDUSTRIAL;
		}else if(GetBoundingBox(i).IsPointInside(LevelPos(level)))
			wantThisOne = true;
		else if(allowedLevel != LEVEL_GENERIC && GetBoundingBox(i).IsPointInside(LevelPos(allowedLevel)))
			wantThisOne = true;

/*		// LCS: removed
		if(GetBoundingBox(i).IsPointInside(pos) ||
		   bLoadAtSecondPosition && GetBoundingBox(i).IsPointInside(secondPosition, -119.0f) ||
		   strcmp(GetColName(i), "yacht") == 0){
			wantThisOne = true;
		}else{
			for (int j = 0; j < MAX_CLEANUP; j++) {
				CPhysical* pEntity = nil;
				cleanup_entity_struct* pCleanup = &CTheScripts::MissionCleanUp.m_sEntities[j];
				if (pCleanup->type == CLEANUP_CAR) {
					pEntity = CPools::GetVehiclePool()->GetAt(pCleanup->id);
					if (!pEntity || pEntity->GetStatus() == STATUS_WRECKED)
						continue;
				}
				else if (pCleanup->type == CLEANUP_CHAR) {
					pEntity = CPools::GetPedPool()->GetAt(pCleanup->id);
					if (!pEntity || ((CPed*)pEntity)->DyingOrDead())
						continue;
				}
				if (pEntity && !pEntity->bDontLoadCollision && !pEntity->bIsFrozen) {
					if (GetBoundingBox(i).IsPointInside(pEntity->GetPosition(), -80.0f))
						wantThisOne = true;
				}
			}
		}
*/

		if(wantThisOne){
			CStreaming::RequestCol(i, STREAMFLAGS_PRIORITY);
			requestedSomething = true;
		}else
			CStreaming::RemoveCol(i);
	}
	if(requestedSomething){
		CTimer::Suspend();
		// BUG? request was done with priority but now loading non-priority?
		CStreaming::LoadAllRequestedModels(false);
		CGarages::SetupAnyGaragesForThisIsland();
		CTimer::Resume();
	}
	bLoadAtSecondPosition = false;
}

void
CColStore::RequestCollision(const CVector &pos)
{
	int i;

	for(i = 1; i < COLSTORESIZE; i++)
		if(GetSlot(i) && DoScriptsWantThisIn(i) && GetBoundingBox(i).IsPointInside(LevelPos(PosLevel(pos)), -115.0f))
			CStreaming::RequestCol(i, STREAMFLAGS_PRIORITY);
}

void
CColStore::EnsureCollisionIsInMemory(const CVector &pos)
{
/*	// LCS: removed
	int i;

	if(CStreaming::ms_disableStreaming)
		return;

	for(i = 1; i < COLSTORESIZE; i++)
		if(GetSlot(i) && GetBoundingBox(i).IsPointInside(pos, -110.0f) &&
		   !CStreaming::HasColLoaded(i)){
			CStreaming::RequestCol(i, 0);
			if(TheCamera.GetScreenFadeStatus() == FADE_0)
				FrontEndMenuManager.MessageScreen("LOADCOL", false);
			CTimer::Suspend();
			CStreaming::LoadAllRequestedModels(false);
			CTimer::Resume();
		}
*/
}

bool
CColStore::DoScriptsWantThisIn(int32 slot)
{
	if(slot == 0)
		return false;
	ColDef *coldef = GetSlot(slot);
	if(coldef == nil)
		return false;
	if(strcmp(coldef->name, "fortstaunton") == 0)
		return !CTheScripts::IsFortStauntonDestroyed();
	if(strcmp(coldef->name, "fortdestroyed") == 0)
		return CTheScripts::IsFortStauntonDestroyed();
	return true;
}

bool
CColStore::HasCollisionLoaded(eLevelName level)
{
	int i;

	const CVector &pos = LevelPos(level);
	for(i = 1; i < COLSTORESIZE; i++)
		if(GetSlot(i) && DoScriptsWantThisIn(i) &&
		   (!CGeneral::faststricmp(GetColName(i), "indust") && level == LEVEL_INDUSTRIAL ||
		    GetBoundingBox(i).IsPointInside(pos)) &&
		   !GetSlot(i)->isLoaded)
			return false;
	return true;
}

bool
CColStore::HasCollisionLoaded(const CVector &pos)
{
	return HasCollisionLoaded(PosLevel(pos));
}

void
CColStore::Load(bool onlyBB, CPool<ColDef> *pool)
{
	ms_pColPool = pool;
	m_onlyBB = onlyBB;
}
