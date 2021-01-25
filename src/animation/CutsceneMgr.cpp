#include "common.h"

#include "General.h"
#include "CutsceneMgr.h"
#include "Directory.h"
#include "Camera.h"
#include "Streaming.h"
#include "FileMgr.h"
#include "main.h"
#include "AnimManager.h"
#include "AnimBlendAssociation.h"
#include "AnimBlendAssocGroup.h"
#include "AnimBlendClumpData.h"
#include "Pad.h"
#include "DMAudio.h"
#include "World.h"
#include "PlayerPed.h"
#include "Wanted.h"
#include "RpAnimBlend.h"
#include "ModelIndices.h"
#include "TempColModels.h"
#include "ColStore.h"
#include "Radar.h"
#include "Pools.h"
#include "crossplatform.h"

static bool bModelsRemovedForCutscene;
static int32 NumberOfSavedWeapons;
static eWeaponType SavedWeaponIDs[TOTAL_WEAPON_SLOTS];
static int32 SavedWeaponAmmo[TOTAL_WEAPON_SLOTS];

char CCutsceneMgr::ms_cAppendAnimName[NUMCUTSCENEOBJECTS][NAMELENGTH];
char CCutsceneMgr::ms_cAppendObjectName[NUMCUTSCENEOBJECTS][NAMELENGTH];
int CCutsceneMgr::ms_numAppendObjectNames;
CDirectory *CCutsceneMgr::ms_pCutsceneDir;
bool CCutsceneMgr::ms_loaded;
bool CCutsceneMgr::ms_hasFileInfo;
bool CCutsceneMgr::ms_wasCutsceneSkipped;
bool CCutsceneMgr::ms_useLodMultiplier;
bool CCutsceneMgr::ms_cutsceneProcessing;
bool CCutsceneMgr::ms_running;
bool CCutsceneMgr::ms_animLoaded;
uint32 CCutsceneMgr::ms_cutsceneLoadStatus;

void
CCutsceneMgr::Initialise(void *dir)
{
	ms_cutsceneLoadStatus = CUTSCENE_NOT_LOADED;
	ms_running = false;
	ms_animLoaded = false;
	ms_cutsceneProcessing = false;
	ms_useLodMultiplier = false;
	ms_wasCutsceneSkipped = false;
	ms_hasFileInfo = false;
	//ms_numCutsceneObjs = 0;
	//ms_loaded = false;
	if (gMakeResources) {
		ms_pCutsceneDir = new CDirectory(CUTSCENEDIRSIZE);
		ms_pCutsceneDir->ReadDirFile("ANIM\\CUTS.DIR");
	}
	else
		ms_pCutsceneDir = (CDirectory*)dir;

	//numUncompressedAnims = 0;
	//uncompressedAnims[0][0] = '\0';
}

void CCutsceneMgr::Write(base::cRelocatableChunkWriter& writer)
{
	writer.AllocateRaw(ms_pCutsceneDir, sizeof(*ms_pCutsceneDir), 4, false, true);
	writer.AllocateRaw(ms_pCutsceneDir->entries, sizeof(CDirectory::DirectoryInfo) * ms_pCutsceneDir->numEntries, 4, false, true);
	writer.AddPatch(ms_pCutsceneDir);
}

void
CCutsceneMgr::Shutdown(void)
{
	delete ms_pCutsceneDir;
}

void
CCutsceneMgr::LoadCutsceneData(const char *szCutsceneName)
{
	LoadCutsceneData_overlay(szCutsceneName);
}

void
CCutsceneMgr::DeleteCutsceneData(void)
{
	DeleteCutsceneData_overlay();
	if (bModelsRemovedForCutscene)
		LoadEverythingBecauseCutsceneDeletedAllOfIt();
}

void
CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory()
{
	//CStreaming::ms_disableStreaming = true;
	CWorld::ClearExcitingStuffFromArea(FindPlayerCoors(), 120.0f, true);
	CColStore::RemoveAllCollision();
	CWorld::bProcessCutsceneOnly = true;
	/*ms_cutsceneProcessing = true;

	for (int i = CPools::GetPedPool()->GetSize() - 1; i >= 0; i--) {
		CPed *pPed = CPools::GetPedPool()->GetSlot(i);
		if (pPed) {
			if (!pPed->IsPlayer() && pPed->CanBeDeleted()) {
				CWorld::Remove(pPed);
				delete pPed;
			}
		}
	}

	for (int i = CPools::GetVehiclePool()->GetSize() - 1; i >= 0; i--) {
		CVehicle *pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (pVehicle) {
			if (pVehicle->CanBeDeleted()) {
				CWorld::Remove(pVehicle);
				delete pVehicle;
			}
		}
	}
	CWorld::bProcessCutsceneOnly = true;
	//bIsEverythingRemovedFromTheWorldForTheBiggestFuckoffCutsceneEver = true;*/
	CStreaming::RemoveCurrentZonesModels();
	while (CStreaming::RemoveLoadedVehicle());
	CRadar::RemoveRadarSections();
	CStreaming::SetModelIsDeletable(MI_MALE01);
	CStreaming::SetModelTxdIsDeletable(MI_MALE01);
	CStreaming::SetModelIsDeletable(MI_COLT45);
	CStreaming::SetModelTxdIsDeletable(MI_COLT45);
	CStreaming::SetModelIsDeletable(MI_NIGHTSTICK);
	CStreaming::SetModelTxdIsDeletable(MI_NIGHTSTICK);
	CStreaming::SetModelIsDeletable(MI_MISSILE);
	CStreaming::SetModelTxdIsDeletable(MI_MISSILE);

	/*for (int i = CPools::GetDummyPool()->GetSize() - 1; i >= 0; i--) {
		CDummy* pDummy = CPools::GetDummyPool()->GetSlot(i);
		if (pDummy)
			pDummy->DeleteRwObject();
	}

	for (int i = CPools::GetObjectPool()->GetSize() - 1; i >= 0; i--) {
		CObject* pObject = CPools::GetObjectPool()->GetSlot(i);
		if (pObject)
			pObject->DeleteRwObject();
	}

	for (int i = CPools::GetBuildingPool()->GetSize() - 1; i >= 0; i--) {
		CBuilding* pBuilding = CPools::GetBuildingPool()->GetSlot(i);
		if (pBuilding && pBuilding->m_rwObject != nil && pBuilding->bIsBIGBuilding && pBuilding->bStreamBIGBuilding) {
			if (pBuilding->bIsBIGBuilding)
				CStreaming::RequestModel(pBuilding->GetModelIndex(), 0);
			if (!pBuilding->bImBeingRendered)
				pBuilding->DeleteRwObject();
		}
	}*/

	CPlayerPed *pPlayerPed = FindPlayerPed();
	pPlayerPed->RemoveWeaponAnims(0, -1000.0f);
	NumberOfSavedWeapons = 0;

	for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
		if (pPlayerPed->m_weapons[i].m_eWeaponType != WEAPONTYPE_UNARMED) {
			SavedWeaponIDs[NumberOfSavedWeapons] = pPlayerPed->m_weapons[i].m_eWeaponType;
			SavedWeaponAmmo[NumberOfSavedWeapons] = pPlayerPed->m_weapons[i].m_nAmmoTotal;
			NumberOfSavedWeapons++;
		}
	}

	pPlayerPed->ClearWeapons();
	bModelsRemovedForCutscene = true;
	//CGame::DrasticTidyUpMemory(true);
}

void
CCutsceneMgr::LoadEverythingBecauseCutsceneDeletedAllOfIt()
{
	bModelsRemovedForCutscene = false;
	CStreaming::LoadInitialPeds();
	CStreaming::LoadInitialWeapons();
	//CStreaming::LoadInitialVehicles();
		
	CPlayerPed *pPlayerPed = FindPlayerPed();
	for (int i = 0; i < NumberOfSavedWeapons; i++) {
		int32 weaponModelId = CWeaponInfo::GetWeaponInfo(SavedWeaponIDs[i])->m_nModelId;
		uint8 flags = CStreaming::ms_aInfoForModel[weaponModelId].m_flags;
		CStreaming::RequestModel(weaponModelId, STREAMFLAGS_DONT_REMOVE);
		CStreaming::LoadAllRequestedModels(false);
		if (CWeaponInfo::GetWeaponInfo(SavedWeaponIDs[i])->m_nModel2Id != -1) {
			CStreaming::RequestModel(CWeaponInfo::GetWeaponInfo(SavedWeaponIDs[i])->m_nModel2Id, 0);
			CStreaming::LoadAllRequestedModels(false);
		}
		if (!(flags & STREAMFLAGS_DONT_REMOVE))
			CStreaming::SetModelIsDeletable(weaponModelId);
		pPlayerPed->GiveWeapon(SavedWeaponIDs[i], SavedWeaponAmmo[i], true);
	}
	NumberOfSavedWeapons = 0;
}

void
CCutsceneMgr::Update(void)
{
	if (ms_cutsceneLoadStatus != CUTSCENE_NOT_LOADED)
		Update_overlay();
}

void
CCutsceneMgr::LoadAnimationUncompressed(char const* name)
{
	strcpy(ms_aUncompressedCutsceneAnims[ms_numUncompressedCutsceneAnims], name);
	
	// Because that's how CAnimManager knows the end of array
	++ms_numUncompressedCutsceneAnims;
	assert(ms_numUncompressedCutsceneAnims < ARRAY_SIZE(ms_aUncompressedCutsceneAnims));
	ms_aUncompressedCutsceneAnims[ms_numUncompressedCutsceneAnims][0] = '\0';
}


bool
CCutsceneMgr::IsCutsceneSkipButtonBeingPressed()
{
	return (CPad::GetPad(0)->GetCrossJustDown()
		|| CPad::GetPad(0)->GetLeftMouseJustDown()
		|| CPad::GetPad(0)->GetEnterJustDown()
		|| CPad::GetPad(0)->GetCharJustDown(' '));
}

void
CCutsceneMgr::AppendToNextCutscene(const char *object, const char *anim)
{
	strcpy(ms_cAppendObjectName[ms_numAppendObjectNames], object);
	strlwr(ms_cAppendObjectName[ms_numAppendObjectNames]);
	strcpy(ms_cAppendAnimName[ms_numAppendObjectNames], anim);
	strlwr(ms_cAppendAnimName[ms_numAppendObjectNames]);
	ms_numAppendObjectNames++;
}