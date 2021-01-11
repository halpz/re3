#include "common.h"
#include "relocatableChunk.h"

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
#include "Messages.h"
#include "Population.h"
#include "CarCtrl.h"
#include "Timecycle.h"
#include "Rubbish.h"
#include "Text.h"
#include "Hud.h"
#include "crossplatform.h"

const struct {
	const char *szTrackName;
	int iTrackId;
} musicNameIdAssoc[] = {
	{ "BIKER", STREAMED_SOUND_CUTSCENE_BIKER },
	{ "BONEVOY", STREAMED_SOUND_CUTSCENE_BONEVOY },
	{ "CAMPAIN", STREAMED_SOUND_CUTSCENE_CAMPAIN },
	{ "CASHCHP", STREAMED_SOUND_CUTSCENE_CASHCHP },
	{ "CONTBAN", STREAMED_SOUND_CUTSCENE_CONTBAN },
	{ "CRAZY69", STREAMED_SOUND_CUTSCENE_CRAZY69 },
	{ "CUTTEST", STREAMED_SOUND_CUTSCENE_CUTTEST },
	{ "DEADLY", STREAMED_SOUND_CUTSCENE_DEADLY },
	{ "DONPROB", STREAMED_SOUND_CUTSCENE_DONPROB },
	{ "DRIVNMR", STREAMED_SOUND_CUTSCENE_DRIVNMR },
	{ "ELECTON", STREAMED_SOUND_CUTSCENE_ELECTON },
	{ "FINAL", STREAMED_SOUND_CUTSCENE_FINAL },
	{ "FINAL_2", STREAMED_SOUND_CUTSCENE_FINAL_2 },
	{ "HOMSWET", STREAMED_SOUND_CUTSCENE_HOMSWET },
	{ "HOTWHEL", STREAMED_SOUND_CUTSCENE_HOTWHEL },
	{ "KIDNAPP", STREAMED_SOUND_CUTSCENE_KIDNAPP },
	{ "LANDGRB", STREAMED_SOUND_CUTSCENE_LANDGRB },
	{ "MORGUE", STREAMED_SOUND_CUTSCENE_MORGUE },
	{ "OVERDOS", STREAMED_SOUND_CUTSCENE_OVERDOS },
	{ "RUFJUST", STREAMED_SOUND_CUTSCENE_RUFJUST },
	{ "SAYONAR", STREAMED_SOUND_CUTSCENE_SAYONAR },
	{ "SICILAN", STREAMED_SOUND_CUTSCENE_SICILAN },
	{ "THEOFER", STREAMED_SOUND_CUTSCENE_THEOFER },
	{ "INTRO", STREAMED_SOUND_CUTSCENE_INTRO },
	{ "FINALE", STREAMED_SOUND_CUTSCENE_FINALE },
	{ NULL, 0 }
};

int
FindCutsceneAudioTrackId(const char *szCutsceneName)
{
	debug("looking for cutscene music track\n");
	for (int i = 0; musicNameIdAssoc[i].szTrackName; i++) {
		if (!CGeneral::faststricmp(musicNameIdAssoc[i].szTrackName, szCutsceneName)) {
			debug("HUZZA! FOUND cutscene music track\n");
			return musicNameIdAssoc[i].iTrackId;
		}
	}
	debug("NOT FOUND cutscene music track\n");
	return -1;
}

const char *
GetNextLine(const char *buf, char *line, uint32 lineSize)
{
	while (*buf == '\n' || *buf == '\r')
		buf++;

	if (*buf == '\0')
		return nil;

	// size check never happened, eh?
	while (*buf != '\n' && *buf != '\r') {
		if (*buf == '\0')
			break;
		*(line++) = *(buf++);
	}
	*(line++) = '\0';
	return buf;
}

RpAtomic*
CalculateBoundingSphereRadiusCB(RpAtomic* atomic, void* data)
{
	float radius = RpAtomicGetBoundingSphere(atomic)->radius;
	RwV3d center = RpAtomicGetBoundingSphere(atomic)->center;

	for (RwFrame* frame = RpAtomicGetFrame(atomic); RwFrameGetParent(frame); frame = RwFrameGetParent(frame))
		RwV3dTransformPoints(&center, &center, 1, RwFrameGetMatrix(frame));

	float size = RwV3dLength(&center) + radius;
	if (size > *(float*)data)
		*(float*)data = size;
	return atomic;
}

void UpdateCutsceneObjectBoundingBox(RpClump* clump, int modelId)
{
	if (modelId >= MI_CUTOBJ01 && modelId <= MI_CUTOBJ10) {
		CColModel* pColModel = &CTempColModels::ms_colModelCutObj[modelId - MI_CUTOBJ01];
		float oldRadius = pColModel->boundingSphere.radius;
		float radius = 0.0f;
		RpClumpForAllAtomics(clump, CalculateBoundingSphereRadiusCB, &radius);
		if (oldRadius < 20.0f) oldRadius = 20.0f;
		if (oldRadius < radius) {
			debug("Limiting cutscene object radius %f\n", oldRadius);
			radius = oldRadius;
		}
		radius = oldRadius;
		pColModel->boundingSphere.radius = radius;
		pColModel->boundingBox.min = CVector(-radius, -radius, -radius);
		pColModel->boundingBox.max = CVector(radius, radius, radius);
	}
}

bool bCamLoaded;
bool bCamFading;

// yes, they've actually doubled this thing here, thus this one is unused
static bool bModelsRemovedForCutscene;
static int32 NumberOfSavedWeapons;
static eWeaponType SavedWeaponIDs[TOTAL_WEAPON_SLOTS];
static int32 SavedWeaponAmmo[TOTAL_WEAPON_SLOTS];

enum
{
	CUTMODEL_PLAYER = 1,
	CUTMODEL_SIMPLE,
	CUTMODEL_REPEATED,
};

bool CCutsceneMgr::ms_useCutsceneShadows = true;
bool CCutsceneMgr::mCutsceneSkipFading;
int CCutsceneMgr::mCutsceneSkipFadeTime;
float CCutsceneMgr::m_fPrevCarDensity;
float CCutsceneMgr::m_fPrevPedDensity;
bool CCutsceneMgr::m_PrevExtraColourOn;
uint32 CCutsceneMgr::m_PrevExtraColour;
uint32 CCutsceneMgr::ms_iNumParticleEffects;
sParticleEffect CCutsceneMgr::ms_pParticleEffects[NUM_CUTS_PARTICLE_EFFECTS];
sToHideItem CCutsceneMgr::ms_crToHideItems[NUMCUTSCENEOBJECTS];
uint32 CCutsceneMgr::ms_iNumHiddenEntities;
CEntity *CCutsceneMgr::ms_pHiddenEntities[NUMCUTSCENEOBJECTS];
int CCutsceneMgr::ms_numAttachObjectToBones;
bool CCutsceneMgr::ms_bRepeatObject[NUMCUTSCENEOBJECTS];
sAttachInfo CCutsceneMgr::ms_iAttachObjectToBone[NUMCUTSCENEOBJECTS];
uint32 CCutsceneMgr::ms_numUncompressedCutsceneAnims;
char CCutsceneMgr::ms_aUncompressedCutsceneAnims[NUM_CUTS_UNCOMPRESSED_ANIMS][NAMELENGTH];
uint32 CCutsceneMgr::ms_iTextDuration[NUM_CUTS_MAX_TEXTS];
uint32 CCutsceneMgr::ms_iTextStartTime[NUM_CUTS_MAX_TEXTS];
char CCutsceneMgr::ms_cTextOutput[NUM_CUTS_MAX_TEXTS][TEXT_KEY_SIZE];
uint32 CCutsceneMgr::ms_currTextOutput;
uint32 CCutsceneMgr::ms_numTextOutput;
uint32 CCutsceneMgr::ms_iModelIndex[NUMCUTSCENEOBJECTS];
char CCutsceneMgr::ms_cLoadAnimName[NUMCUTSCENEOBJECTS][NAMELENGTH];
char CCutsceneMgr::ms_cLoadObjectName[NUMCUTSCENEOBJECTS][NAMELENGTH];
int CCutsceneMgr::ms_numLoadObjectNames;
CCutsceneObject *CCutsceneMgr::ms_pCutsceneObjects[NUMCUTSCENEOBJECTS];
int32 CCutsceneMgr::ms_numCutsceneObjs;
CVector CCutsceneMgr::ms_cutsceneOffset;
float CCutsceneMgr::ms_cutsceneTimer;
uint32 CCutsceneMgr::ms_cutscenePlayStatus;
CAnimBlendAssocGroup CCutsceneMgr::ms_cutsceneAssociations;
char CCutsceneMgr::ms_cutsceneName[CUTSCENENAMESIZE];

CCutsceneObject *
CCutsceneMgr::CreateCutsceneObject(int modelId)
{
	CBaseModelInfo *pModelInfo;
	CColModel *pColModel;
	CCutsceneObject *pCutsceneObject;

	CStreaming::ImGonnaUseStreamingMemory();
	debug("Created cutscene object %s\n", CModelInfo::GetModelInfo(modelId)->GetModelName());
	if (modelId >= MI_CUTOBJ01 && modelId <= MI_CUTOBJ10) {
		pModelInfo = CModelInfo::GetModelInfo(modelId);
		pColModel = &CTempColModels::ms_colModelCutObj[modelId - MI_CUTOBJ01];
		pModelInfo->SetColModel(pColModel);
		UpdateCutsceneObjectBoundingBox((RpClump*)pModelInfo->GetRwObject(), modelId);
	}

	pCutsceneObject = new CCutsceneObject();
	pCutsceneObject->SetModelIndex(modelId);
	if (ms_useCutsceneShadows)
		pCutsceneObject->CreateShadow();
	ms_pCutsceneObjects[ms_numCutsceneObjs++] = pCutsceneObject;
	CStreaming::IHaveUsedStreamingMemory();
	return pCutsceneObject;
}

void
CCutsceneMgr::SetCutsceneAnim(const char *animName, CObject *pObject)
{
	CAnimBlendAssociation *pNewAnim;
	CAnimBlendClumpData *pAnimBlendClumpData;

	debug("Give cutscene anim %s\n", animName);
	/*assert(RwObjectGetType(pObject->m_rwObject) == rpCLUMP);
	debug("Give cutscene anim %s\n", animName);
	RpAnimBlendClumpRemoveAllAssociations((RpClump*)pObject->m_rwObject);

	pNewAnim = ms_cutsceneAssociations.GetAnimation(animName);
	if (!pNewAnim) {
		debug("\n\nHaven't I told you I can't find the fucking animation %s\n\n\n", animName);
		return;
	}

	if (pNewAnim->hierarchy->IsCompressed())
		pNewAnim->hierarchy->keepCompressed = true;*/

	CStreaming::ImGonnaUseStreamingMemory();
	pNewAnim = ms_cutsceneAssociations.CopyAnimation(animName);
	CStreaming::IHaveUsedStreamingMemory();

	pNewAnim->SetCurrentTime(0.0f);
	pNewAnim->flags |= ASSOC_HAS_TRANSLATION;
	pNewAnim->flags &= ~ASSOC_RUNNING;

	pAnimBlendClumpData = *RPANIMBLENDCLUMPDATA(pObject->m_rwObject);
	pAnimBlendClumpData->link.Prepend(&pNewAnim->link);

	//if (pNewAnim->hierarchy->keepCompressed)
	//	pAnimBlendClumpData->frames->flag |= AnimBlendFrameData::COMPRESSED;
}

void
CCutsceneMgr::SetCutsceneAnimToLoop(const char* animName)
{
	ms_cutsceneAssociations.GetAnimation(animName)->flags |= ASSOC_REPEAT;
}

CCutsceneHead*
CCutsceneMgr::SetHeadAnim(const char*, CObject* pObject)
{
	return nil;
}

void
CCutsceneMgr::StartCutscene()
{
	ms_cutscenePlayStatus = CUTSCENE_STARTED;
	if (bCamLoaded) {
		TheCamera.SetWideScreenOn();
		CHud::SetHelpMessage(nil, true);
	}
}

void
CCutsceneMgr::SetupCutsceneToStart(void)
{
	if (bCamLoaded) {
		TheCamera.SetCamCutSceneOffSet(ms_cutsceneOffset);
		TheCamera.TakeControlWithSpline(JUMP_CUT);
		TheCamera.SetWideScreenOn();
		CHud::SetHelpMessage(nil, true);
	}

	ms_cutsceneOffset.z += 1.0f;

	for (int i = ms_numCutsceneObjs - 1; i >= 0; i--) {
		assert(RwObjectGetType(ms_pCutsceneObjects[i]->m_rwObject) == rpCLUMP);
		if (CAnimBlendAssociation *pAnimBlendAssoc = RpAnimBlendClumpGetFirstAssociation((RpClump*)ms_pCutsceneObjects[i]->m_rwObject)) {
			assert(pAnimBlendAssoc->hierarchy->sequences[0].HasTranslation());
			if (ms_pCutsceneObjects[i]->m_pAttachTo != nil) {
				pAnimBlendAssoc->flags &= (~ASSOC_HAS_TRANSLATION);
			} else {
				if (pAnimBlendAssoc->hierarchy->IsCompressed()){
					KeyFrameTransCompressed *keyFrames = ((KeyFrameTransCompressed*)pAnimBlendAssoc->hierarchy->sequences[0].GetKeyFrameCompressed(0));
					CVector trans;
					keyFrames->GetTranslation(&trans);
					ms_pCutsceneObjects[i]->SetPosition(ms_cutsceneOffset + trans);
				}else{
					KeyFrameTrans *keyFrames = ((KeyFrameTrans*)pAnimBlendAssoc->hierarchy->sequences[0].GetKeyFrame(0));
					ms_pCutsceneObjects[i]->SetPosition(ms_cutsceneOffset + keyFrames->translation);
				}
			}
			pAnimBlendAssoc->SetRun();
		} else {
			ms_pCutsceneObjects[i]->SetPosition(ms_cutsceneOffset);
		}
		CWorld::Add(ms_pCutsceneObjects[i]);
		if (RwObjectGetType(ms_pCutsceneObjects[i]->m_rwObject) == rpCLUMP) {
			ms_pCutsceneObjects[i]->UpdateRpHAnim();
		}
	}

	CTimer::Update();
	CTimer::Update();
	ms_cutsceneTimer = 0.0f;
	ms_running = true;
	mCutsceneSkipFadeTime = 0;
	mCutsceneSkipFading = 0;
}

void
CCutsceneMgr::FinishCutscene()
{
	if (bCamLoaded) {
		ms_cutsceneTimer = TheCamera.GetCutSceneFinishTime() * 0.001f;
		TheCamera.FinishCutscene();
	}

	FindPlayerPed()->bIsVisible = true;
	CWorld::Players[CWorld::PlayerInFocus].MakePlayerSafe(false);
}

uint32
CCutsceneMgr::GetCutsceneTimeInMilleseconds(void)
{
	return 1000.0f * ms_cutsceneTimer;
}

bool CCutsceneMgr::HasCutsceneFinished(void)
{
	return !bCamLoaded || TheCamera.GetPositionAlongSpline() == 1.0f;
}

void
CCutsceneMgr::AttachObjectToBone(CObject *pObject, CObject *pAttachTo, int bone)
{
	RpHAnimHierarchy *hanim = GetAnimHierarchyFromSkinClump(pAttachTo->GetClump());
	RwInt32 id = RpHAnimIDGetIndex(hanim, bone);
	RwMatrix *matrixArray = RpHAnimHierarchyGetMatrixArray(hanim);
	((CCutsceneObject*)pObject)->m_pAttachmentObject = pAttachTo;
	((CCutsceneObject*)pObject)->m_pAttachTo = &matrixArray[id];
	//debug("Attach %s to %s\n",
	//	CModelInfo::GetModelInfo(pObject->GetModelIndex())->GetModelName(),
	//	CModelInfo::GetModelInfo(pAttachTo->GetModelIndex())->GetModelName());
}

void
CCutsceneMgr::AttachObjectToFrame(CObject *pObject, CEntity *pAttachTo, const char *frame)
{
	((CCutsceneObject*)pObject)->m_pAttachmentObject = nil;
	((CCutsceneObject*)pObject)->m_pAttachTo = RpAnimBlendClumpFindFrame(pAttachTo->GetClump(), frame)->frame;
	//debug("Attach %s to component %s of %s\n",
	//	CModelInfo::GetModelInfo(pObject->GetModelIndex())->GetModelName(),
	//	frame,
	//	CModelInfo::GetModelInfo(pAttachTo->GetModelIndex())->GetModelName());
	if (RwObjectGetType(pObject->m_rwObject) == rpCLUMP) {
		RpClump *clump = (RpClump*)pObject->m_rwObject;
		if (IsClumpSkinned(clump))
			RpAtomicGetBoundingSphere(GetFirstAtomic(clump))->radius *= 1.1f;
	}
}

void
CCutsceneMgr::AttachObjectToParent(CObject *pObject, CEntity *pAttachTo)
{
	((CCutsceneObject*)pObject)->m_pAttachmentObject = nil;
	((CCutsceneObject*)pObject)->m_pAttachTo = RpClumpGetFrame(pAttachTo->GetClump());

	//debug("Attach %s to %s\n", CModelInfo::GetModelInfo(pObject->GetModelIndex())->GetModelName(), CModelInfo::GetModelInfo(pAttachTo->GetModelIndex())->GetModelName());
}

void
CCutsceneMgr::HideRequestedObjects(void)
{
	int num = ms_iNumHiddenEntities;
	ms_iNumHiddenEntities = 0;

	for (int i = 0; i < num; i++) {
		int id;
		if (CModelInfo::GetModelInfo(ms_crToHideItems[i].name, &id)) {
			CVector pos(ms_crToHideItems[i].x, ms_crToHideItems[i].y, ms_crToHideItems[i].z);
			int16 foundEntities;
			CEntity* pEntities[32];
			CWorld::FindObjectsOfTypeInRange(id, pos, 1.5f, true, &foundEntities, 32, pEntities, true, false, false, true, true);
			for (int j = 0; i < foundEntities; j++) {
				if (pEntities[j]->bIsVisible) {
					ms_pHiddenEntities[ms_iNumHiddenEntities] = pEntities[j];
					ms_pHiddenEntities[ms_iNumHiddenEntities]->RegisterReference(&ms_pHiddenEntities[ms_iNumHiddenEntities]);
					ms_pHiddenEntities[ms_iNumHiddenEntities]->bIsVisible = false;
					ms_iNumHiddenEntities++;
				}
			}
		}
	}
}

bool
CCutsceneMgr::PresubBodge()
{
	return true;
}

void
CCutsceneMgr::LoadCutsceneData_loading()
{
	for (int i = 0; i < ms_numLoadObjectNames; i++) {
		int mi = ms_iModelIndex[i];
		if (mi >= MI_CUTOBJ01 && mi <= MI_CUTOBJ10) {
			if (CStreaming::ms_aInfoForModel[mi].m_loadState != STREAMSTATE_LOADED)
				return;
		}
	}

	if (!LoadCutsceneData_postload())
		return;

	CCutsceneObject* cutsceneObject;
	for (int i = 0; i < ms_numLoadObjectNames; i++) {
		if (!ms_bRepeatObject[i])
			cutsceneObject = CreateCutsceneObject(ms_iModelIndex[i]);
		if (ms_cLoadAnimName[i][0] != '\0')
			SetCutsceneAnim(ms_cLoadAnimName[i], cutsceneObject);
	}

	for (int i = 0; i < ms_numAttachObjectToBones; i++) {
		int objectId = ms_iAttachObjectToBone[i].objectId;
		int attachToId = ms_iAttachObjectToBone[i].attachToId;
		int bone = ms_iAttachObjectToBone[i].boneId;
		AttachObjectToBone(ms_pCutsceneObjects[objectId], ms_pCutsceneObjects[attachToId], bone);
	}
}

bool
CCutsceneMgr::LoadCutsceneData_postload(bool b)
{
	RwStream *stream = nil;
	uint32 size;
	uint32 offset;

	bool result;

	CMessages::ClearThisBigPrintNow(0);
	CPopulation::PedDensityMultiplier = 0.0f;
	CCarCtrl::CarDensityMultiplier = 0.0f;
	CStreaming::ms_disableStreaming = false;
	if (b)
	{
		sprintf(gString, "%s.IFP", ms_cutsceneName);
		result = false;
		ms_animLoaded = false;
		RwStreamClose(stream, nil); // umm...
		sprintf(gString, "%s.DAT", ms_cutsceneName);
		bCamLoaded = false;
	} else {

		stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, "ANIM\\CUTS.IMG");
		sprintf(gString, "%s.IFP", ms_cutsceneName);
		if (stream) {
			if (ms_pCutsceneDir->FindItem(gString, offset, size))
			{
				CStreaming::MakeSpaceFor(size << 11);
				CStreaming::ImGonnaUseStreamingMemory();
				RwStreamSkip(stream, offset << 11);
				CAnimManager::LoadAnimFile(stream, true, ms_aUncompressedCutsceneAnims);
				ms_cutsceneAssociations.CreateAssociations(ms_cutsceneName, ms_cLoadAnimName[0], ms_cLoadObjectName[0], NAMELENGTH);
				CStreaming::IHaveUsedStreamingMemory();
				ms_animLoaded = true;
			}
			else
			{
				ms_animLoaded = false;
			}
			RwStreamClose(stream, nil);

			int file = CFileMgr::OpenFile("ANIM\\CUTS.IMG", "rb");
			sprintf(gString, "%s.DAT", ms_cutsceneName);
			if (file) {
				if (ms_pCutsceneDir->FindItem(gString, offset, size))
				{
					CStreaming::ImGonnaUseStreamingMemory();
					CFileMgr::Seek(file, offset << 11, 0);
					TheCamera.LoadPathSplines(file);
					CStreaming::IHaveUsedStreamingMemory();
					bCamLoaded = true;
				}
				else
				{
					bCamLoaded = false;
				}
				result = true;
				CFileMgr::CloseFile(file);
			}
			else
			{
				bCamLoaded = false;
				result = true;
			}
		}
		else
		{
			result = false;
			ms_animLoaded = false;
			RwStreamClose(stream, nil);
			sprintf(gString, "%s.DAT", ms_cutsceneName);
			bCamLoaded = false;
		}
	}
	ms_cutsceneLoadStatus = CUTSCENE_LOADED;
	ms_cutsceneTimer = 0.0f;
	FindPlayerPed()->m_pWanted->ClearQdCrimes();
	return result;
}

void
CCutsceneMgr::LoadCutsceneData_overlay(const char *szCutsceneName)
{
	CTimer::Suspend();
	ms_cutsceneProcessing = true;
	ms_wasCutsceneSkipped = false;
	if (!bModelsRemovedForCutscene)
		CStreaming::RemoveCurrentZonesModels();

	ms_pCutsceneDir->numEntries = 0;
	ms_pCutsceneDir->ReadDirFile("ANIM\\CUTS.DIR");

	CStreaming::RemoveUnusedModelsInLoadedList();
	CGame::DrasticTidyUpMemory(true);

	strcpy(ms_cutsceneName, szCutsceneName);

	LoadCutsceneData_preload();
	CTimer::Resume();
}

void
CCutsceneMgr::LoadCutsceneData_preload(void)
{
	uint32 size;
	uint32 offset;
	CPlayerPed* pPlayerPed;
	if (CGeneral::faststricmp(ms_cutsceneName, "finale")) {
		DMAudio.ChangeMusicMode(MUSICMODE_CUTSCENE);
		int trackId = FindCutsceneAudioTrackId(ms_cutsceneName);
		if (trackId != -1) {
			printf("Start preload audio %s\n", ms_cutsceneName);
			DMAudio.PreloadCutSceneMusic(trackId);
			printf("End preload audio %s\n", ms_cutsceneName);
		}
	}

	for (int i = MI_CUTOBJ01; i <= MI_CUTOBJ10; i++) {
		if (CModelInfo::GetModelInfo(i)->GetNumRefs() <= 0) {
			if (CStreaming::ms_aInfoForModel[i].m_loadState == STREAMSTATE_LOADED) {
				CStreaming::RemoveModel(i);
				CModelInfo::GetModelInfo(i)->SetModelName("&*%");
			}
		}
	}

	m_PrevExtraColour = CTimeCycle::m_ExtraColour;
	m_PrevExtraColourOn = CTimeCycle::m_bExtraColourOn != 0;
	m_fPrevPedDensity = CPopulation::PedDensityMultiplier;
	m_fPrevCarDensity = CCarCtrl::CarDensityMultiplier;
	ms_cutsceneOffset = CVector(0.0f, 0.0f, 0.0f);
	ms_numTextOutput = 0;
	ms_currTextOutput = 0;
	ms_numLoadObjectNames = 0;
	ms_numUncompressedCutsceneAnims = 0;
	ms_numAttachObjectToBones = 0;
	ms_iNumHiddenEntities = 0;
	bCamFading = false;
	ms_iNumParticleEffects = 0;

	for (int i = 0; i < NUM_CUTS_UNCOMPRESSED_ANIMS; i++)
		ms_aUncompressedCutsceneAnims[i][0] = '\0';

	memset(ms_iModelIndex, 0, sizeof(ms_iModelIndex));
	CRubbish::SetVisibility(false);

	pPlayerPed = FindPlayerPed();
	pPlayerPed->m_pWanted->ClearQdCrimes();
	pPlayerPed->bIsVisible = false;
	pPlayerPed->m_fCurrentStamina = pPlayerPed->m_fMaxStamina;
	CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_CUTSCENE);
	CWorld::Players[CWorld::PlayerInFocus].MakePlayerSafe(true);

	sprintf(gString, "%s.CUT", ms_cutsceneName);
	if (!ms_pCutsceneDir->FindItem(gString, offset, size)) {
		LoadCutsceneData_postload();
		return;
	}

	size <<= 11;
	offset <<= 11;

	char *cutsBuf = new char[size];

	RwStream* stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, "ANIM\\CUTS.IMG");

	if (stream) {
		RwStreamSkip(stream, offset);
		RwStreamRead(stream, cutsBuf, size);
		RwStreamClose(stream, nil);
	}

	enum
	{
		CUT_NONE = 0,
		CUT_INFO,
		CUT_MODEL,
		CUT_TEXT,
		CUT_UNCOMPRESS,
		CUT_ATTACH,
		CUT_REMOVE,
		CUT_PARTICLE_EFFECT,
		CUT_EXTRA_COLOR,
	};

	int cutSection = CUT_NONE;
	bool bExtraColSet = false;

	char line[1024];
	const char *pCurLine = cutsBuf;

	while (true)
	{
		pCurLine = GetNextLine(pCurLine, line, sizeof(line));
		if (pCurLine) {
			if (line[0] == '\0')
				break;

			if (strcmp(line, "end") == 0) {
				cutSection = CUT_NONE;
				continue;
			}

			switch (cutSection)
			{
			case CUT_NONE:
				if (strcmp(line, "info") == 0)
					cutSection = CUT_INFO;
				if (strcmp(line, "model") == 0)
					cutSection = CUT_MODEL;
				if (strcmp(line, "text") == 0)
					cutSection = CUT_TEXT;
				if (strcmp(line, "uncompress") == 0)
					cutSection = CUT_UNCOMPRESS;
				if (strcmp(line, "attach") == 0)
					cutSection = CUT_ATTACH;
				if (strcmp(line, "remove") == 0)
					cutSection = CUT_REMOVE;
				if (strcmp(line, "peffect") == 0)
					cutSection = CUT_PARTICLE_EFFECT;
				if (strcmp(line, "extracol") == 0)
					cutSection = CUT_EXTRA_COLOR;
				break;
			case CUT_INFO:
			{
				if (strncmp(line, "offset", 6) == 0) {
					float x, y, z;
					sscanf(line+7, "%f %f %f", &x, &y, &z);
					FindPlayerPed(); // called for some sa check in here
					ms_cutsceneOffset = CVector(x, y, z);
				}
				break;
			}
			case CUT_MODEL:
			{
				char objectName[NAMELENGTH];
				char animName[NAMELENGTH];

				int num; // unused
				sscanf(strtok(line, " ,"), "%d", &num);
				strcpy(objectName, strtok(nil, " ,"));
				char* pAnimName = strtok(0, " ,"); 
				strlwr(objectName);

				bool bUsedFirstTime = true;
				if (pAnimName) {
					do {
						strcpy(animName, pAnimName);
						strlwr(animName);
						strcpy(ms_cLoadObjectName[ms_numLoadObjectNames], objectName);
						strcpy(ms_cLoadAnimName[ms_numLoadObjectNames], animName);
						if (bUsedFirstTime) {
							bUsedFirstTime = false;
							ms_iModelIndex[ms_numLoadObjectNames] = CUTMODEL_SIMPLE;
							ms_bRepeatObject[ms_numLoadObjectNames] = false;
						} else {
							ms_bRepeatObject[ms_numLoadObjectNames] = true;
							ms_iModelIndex[ms_numLoadObjectNames] = CUTMODEL_REPEATED;
						}
						ms_numLoadObjectNames++;
						pAnimName = strtok(0, " ,");
					} while (pAnimName);
				}
				break;
			}
			case CUT_TEXT:
			{
				int iTextStartTime, iTextDuration;
				char cTextOutput[8];
				sscanf(line, "%d,%d,%s", &iTextStartTime, &iTextDuration, cTextOutput);
				for (size_t i = 0; i < strlen(cTextOutput); i++)
					cTextOutput[i] = toupper(cTextOutput[i]);

				memcpy(ms_cTextOutput[ms_numTextOutput], cTextOutput, strlen(cTextOutput)+1);
				ms_iTextStartTime[ms_numTextOutput] = iTextStartTime;
				ms_iTextDuration[ms_numTextOutput] = iTextDuration;
				ms_numTextOutput++;
				break;
			}
			case CUT_UNCOMPRESS:
				LoadAnimationUncompressed(strtok(line, " ,"));
				break;
			case CUT_ATTACH:
			{
				int attachToId, objectId, bone;
				sscanf(line, "%d,%d,%d", &attachToId, &objectId, &bone);
				ms_iAttachObjectToBone[ms_numAttachObjectToBones].attachToId = attachToId;
				ms_iAttachObjectToBone[ms_numAttachObjectToBones].objectId = objectId;
				ms_iAttachObjectToBone[ms_numAttachObjectToBones].boneId = bone;
				ms_numAttachObjectToBones++;
				break;
			}
			case CUT_REMOVE:
			{
				float x, y, z;
				char name[NAMELENGTH];
				sscanf(line, "%f,%f,%f,%s", &x, &y, &z, name);
				ms_crToHideItems[ms_iNumHiddenEntities].x = x;
				ms_crToHideItems[ms_iNumHiddenEntities].y = y;
				ms_crToHideItems[ms_iNumHiddenEntities].z = z;
				strcpy(ms_crToHideItems[ms_iNumHiddenEntities].name, name);
				ms_iNumHiddenEntities++;
				break;
			}
			case CUT_PARTICLE_EFFECT:
			{
				char name[NAMELENGTH];
				char name2[NAMELENGTH];

				int iTime;
				int unk1;
				int unk2;
				float x;
				float y;
				float z;
				float unkX;
				float unkY;
				float unkZ;

				memset(name, 0, NAMELENGTH);
				memset(name2, 0, NAMELENGTH);

				strncpy(name, strtok(line, ","), NAMELENGTH-1);
				iTime = atoi(strtok(0, ","));
				unk1 = atoi(strtok(0, ","));
				unk2 = atoi(strtok(0, ","));
				strncpy(name, strtok(line, ","), NAMELENGTH-1);
				x = strtod(strtok(0, ","), nil);
				y = strtod(strtok(0, ","), nil);
				z = strtod(strtok(0, ","), nil);
				unkX = strtod(strtok(0, ","), nil);
				unkY = strtod(strtok(0, ","), nil);
				unkZ = strtod(strtok(0, ","), nil);

				ms_pParticleEffects[ms_iNumParticleEffects].bPlayed = false;
				ms_pParticleEffects[ms_iNumParticleEffects].iTime = iTime;
				ms_pParticleEffects[ms_iNumParticleEffects].unk1 = unk1;
				ms_pParticleEffects[ms_iNumParticleEffects].unk2 = unk2;
				strcpy(CCutsceneMgr::ms_pParticleEffects[ms_iNumParticleEffects].name2, name2);
				ms_pParticleEffects[ms_iNumParticleEffects].unk10 = false;
				ms_pParticleEffects[ms_iNumParticleEffects].x = x;
				ms_pParticleEffects[ms_iNumParticleEffects].y = y;
				ms_pParticleEffects[ms_iNumParticleEffects].z = z;
				ms_pParticleEffects[ms_iNumParticleEffects].unkX = unkX;
				ms_pParticleEffects[ms_iNumParticleEffects].unkY = unkY;
				ms_pParticleEffects[ms_iNumParticleEffects].unkZ = unkZ;
				ms_pParticleEffects[ms_iNumParticleEffects].unk11 = false;
				strcpy(CCutsceneMgr::ms_pParticleEffects[ms_iNumParticleEffects].name, name);
				ms_iNumParticleEffects++;
				break;
			}
			case CUT_EXTRA_COLOR:
				if (!bExtraColSet) {
					int colorId;
					sscanf(line, "%d", &colorId);
					if (colorId == 0)
						bExtraColSet = false;
					else {
						CTimeCycle::StartExtraColour(colorId - 1, false);
						bExtraColSet = true;
					}
				}
				break;
			default:
				break;
			};

		}
		else
		{
			delete[]cutsBuf;

			// add manually inserted objects
			for (int i = 0; i < ms_numAppendObjectNames; i++) {
				strcpy(ms_cLoadObjectName[ms_numLoadObjectNames], ms_cAppendObjectName[i]);
				strcpy(ms_cLoadAnimName[ms_numLoadObjectNames], ms_cAppendAnimName[i]);
				ms_iModelIndex[ms_numLoadObjectNames] = CUTMODEL_SIMPLE;
				ms_numLoadObjectNames++;
			}
			ms_numAppendObjectNames = 0;

			int specialId = 0;
			for (int i = 0; i < ms_numLoadObjectNames; i++)
			{
				if (strcasecmp(ms_cLoadObjectName[i], "csplay") == 0) {
					ms_iModelIndex[i] = CUTMODEL_PLAYER;
					continue;
				} else if (ms_iModelIndex[i] == CUTMODEL_SIMPLE) {
					int id;
					if (CModelInfo::GetModelInfo(ms_cLoadObjectName[i], &id)) {
						ms_iModelIndex[i] = id;
						CStreaming::RequestModel(id, STREAMFLAGS_SCRIPTOWNED | STREAMFLAGS_DEPENDENCY | STREAMFLAGS_PRIORITY);
					} else {
						CStreaming::RequestSpecialModel(specialId + MI_CUTOBJ01, ms_cLoadObjectName[i], STREAMFLAGS_SCRIPTOWNED | STREAMFLAGS_DEPENDENCY | STREAMFLAGS_PRIORITY);
						ms_iModelIndex[i] = specialId + MI_CUTOBJ01;
						specialId++;
						// skip if id is busy
						while (CStreaming::ms_aInfoForModel[specialId + MI_CUTOBJ01].m_loadState == STREAMSTATE_LOADED)
							specialId++;
					}
				}
				else if (ms_iModelIndex[i] == CUTMODEL_REPEATED && i != 0)
					ms_iModelIndex[i] = ms_iModelIndex[i - 1];
			}

			CStreaming::LoadAllRequestedModels(true);
			ms_cutsceneLoadStatus = CUTSCENE_LOADING;
			return;
		}
	}

	delete[]cutsBuf;
	LoadCutsceneData_postload(true);
}

void
CCutsceneMgr::DeleteCutsceneData_overlay(void)
{
	if (ms_cutsceneLoadStatus == CUTSCENE_NOT_LOADED) return;
	CTimer::Suspend();
	CPopulation::PedDensityMultiplier = m_fPrevPedDensity;
	CCarCtrl::CarDensityMultiplier = m_fPrevCarDensity;
	if (m_PrevExtraColourOn)
		CTimeCycle::StartExtraColour(m_PrevExtraColour, false);
	else
		CTimeCycle::StopExtraColour(m_PrevExtraColourOn);

	for (uint32 i = 0; i < ms_iNumHiddenEntities; i++) {
		if (ms_pHiddenEntities[i]) {
			ms_pHiddenEntities[i]->CleanUpOldReference(&ms_pHiddenEntities[i]);
			ms_pHiddenEntities[i]->bIsVisible = true;
		}
	}

	ms_iNumHiddenEntities = 0;
	ms_iNumParticleEffects = 0;
	CMessages::ClearMessages();
	CRubbish::SetVisibility(true);

	ms_cutsceneProcessing = false;
	ms_useLodMultiplier = false;
	ms_useCutsceneShadows = false;

	ms_numCutsceneObjs--;
	while (ms_numCutsceneObjs >= 0) {
		CWorld::Remove(ms_pCutsceneObjects[ms_numCutsceneObjs]);
		ms_pCutsceneObjects[ms_numCutsceneObjs]->DeleteRwObject();
		delete ms_pCutsceneObjects[ms_numCutsceneObjs];
		ms_pCutsceneObjects[ms_numCutsceneObjs] = nil;
		ms_numCutsceneObjs--;
	}
	ms_numCutsceneObjs = 0;

	if (ms_animLoaded)
		CAnimManager::RemoveLastAnimFile();

	ms_animLoaded = false;
	ms_cutsceneAssociations.DestroyAssociations();

	ms_aUncompressedCutsceneAnims[0][0] = '\0';
	ms_numUncompressedCutsceneAnims = 0;

	if (bCamLoaded) {
		TheCamera.RestoreWithJumpCut();
		TheCamera.SetWideScreenOff();
		TheCamera.DeleteCutSceneCamDataMemory();
	}
	ms_cutsceneLoadStatus = CUTSCENE_NOT_LOADED;
	ms_running = false;

	FindPlayerPed()->bIsVisible = true;
	CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_CUTSCENE);
	CWorld::Players[CWorld::PlayerInFocus].MakePlayerSafe(false);

	if (CGeneral::faststricmp(ms_cutsceneName, "finale")) {
		DMAudio.StopCutSceneMusic();
		DMAudio.ChangeMusicMode(MUSICMODE_GAME);
	}

	CStreaming::ms_disableStreaming = false;
	CWorld::bProcessCutsceneOnly = false;

	//if(bCamLoaded)
	//	CGame::DrasticTidyUpMemory(TheCamera.GetScreenFadeStatus() == FADE_2);
	
	CPad::GetPad(0)->Clear(false);

	if (bModelsRemovedForCutscene) {
		CStreaming::LoadInitialPeds();
		CStreaming::LoadInitialWeapons();
		CStreaming::LoadInitialVehicles();
		bModelsRemovedForCutscene = false;

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

	for (int i = 0; i < ms_numLoadObjectNames; i++)
		CStreaming::SetMissionDoesntRequireModel(ms_iModelIndex[i]);

	CStreaming::SetMissionDoesntRequireModel(MI_COP);
	CStreaming::StreamZoneModels(FindPlayerCoors());
	CTimer::Resume();
}

void
CCutsceneMgr::Update_overlay(void)
{
	if (ms_cutsceneLoadStatus == CUTSCENE_LOADING) {
		debug("Loading Cutscene...\n");
		CTimer::Suspend();
		LoadCutsceneData_loading();
		CTimer::Resume();
		return;
	}

	if (ms_cutsceneLoadStatus != CUTSCENE_LOADED) {
		debug("Cutscene Not Loaded!\n");
		return;
	}

	switch (ms_cutscenePlayStatus) {
	case CUTSCENE_STARTED:
		SetupCutsceneToStart();
		HideRequestedObjects();
		ms_cutscenePlayStatus++;
		break;
	case CUTSCENE_PLAYING_2:
	case CUTSCENE_PLAYING_3:
		ms_cutscenePlayStatus++;
		break;
	case CUTSCENE_PLAYING_4:
		ms_cutscenePlayStatus = CUTSCENE_PLAYING_0;
		if (CGeneral::faststricmp(ms_cutsceneName, "finale"))
			DMAudio.PlayPreloadedCutSceneMusic();
		break;
	default:
		break;
	}

	if (!ms_running) return;

	ms_cutsceneTimer += CTimer::GetTimeStepNonClippedInSeconds();
	uint32 cutsceneTimeInMS = GetCutsceneTimeInMilleseconds();

	if (ms_currTextOutput < ms_numTextOutput && cutsceneTimeInMS > ms_iTextStartTime[ms_currTextOutput]) {
		CMessages::AddMessageJumpQ(TheText.Get(ms_cTextOutput[ms_currTextOutput]), ms_iTextDuration[ms_currTextOutput], 1);
		ms_currTextOutput++;
	}

	for (int i = 0; i < ms_numCutsceneObjs; i++) {
		int modelId = ms_pCutsceneObjects[i]->GetModelIndex();
		if (modelId >= MI_CUTOBJ01 && modelId <= MI_CUTOBJ10)
			UpdateCutsceneObjectBoundingBox(ms_pCutsceneObjects[i]->GetClump(), modelId);
	}

	if (!bCamLoaded) return;

	if (CGeneral::faststricmp(ms_cutsceneName, "finale") && TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_FLYBY && ms_cutsceneLoadStatus == CUTSCENE_LOADED) {
		if (TheCamera.GetCutSceneFinishTime() < cutsceneTimeInMS + 1000) {
			if (!bCamFading) {
				bCamFading = true;
				TheCamera.Fade(1.0f, FADE_OUT);
			}
		}
		if (mCutsceneSkipFading) {
			mCutsceneSkipFadeTime -= CTimer::GetTimeStepInMilliseconds();
			if (mCutsceneSkipFadeTime < 0) {
				CHud::m_BigMessage[1][0] = '\0';
				ms_wasCutsceneSkipped = true;
				FinishCutscene();
				mCutsceneSkipFading = false;
				mCutsceneSkipFadeTime = 0;
			}
		}
		else if (IsCutsceneSkipButtonBeingPressed() && PresubBodge()){
			mCutsceneSkipFading = true;
			mCutsceneSkipFadeTime = 1000;
			TheCamera.Fade(1.0f, FADE_OUT);
		}
	}
}