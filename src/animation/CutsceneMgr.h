#pragma once
#include "CutsceneObject.h"


class CDirectory;
class CAnimBlendAssocGroup;
class CCutsceneHead;

enum {
	CUTSCENE_NOT_LOADED = 0,
	CUTSCENE_LOADING,
	CUTSCENE_LOADED,
};

enum {
	CUTSCENE_PLAYING_0 = 0,
	CUTSCENE_STARTED,
	CUTSCENE_PLAYING_2,
	CUTSCENE_PLAYING_3,
	CUTSCENE_PLAYING_4,
};

enum
{
	NAMELENGTH = 32,
	NUM_CUTS_PARTICLE_EFFECTS = 8,
	NUM_CUTS_MAX_TEXTS = 64,
	NUM_CUTS_UNCOMPRESSED_ANIMS = 8,
	TEXT_KEY_SIZE = 8,
	CUTSCENENAMESIZE = 8
};

struct sToHideItem
{
	float x, y, z;
	char name[NAMELENGTH];
};

// TODO: figure out from SA
// this is unused in LCS anyway
struct sParticleEffect
{
	char name[NAMELENGTH];
	bool bPlayed; // ??
	int iTime;
	int unk1;
	int unk2;
	char name2[NAMELENGTH];
	float x;
	float y;
	float z;
	float unkX;
	float unkY;
	float unkZ;
	bool unk10;
	bool unk11;
};

struct sAttachInfo
{
	int attachToId, objectId, boneId;
};

class CCutsceneMgr
{

	static bool ms_running;
	static CCutsceneObject *ms_pCutsceneObjects[NUMCUTSCENEOBJECTS];
	
	static int32 ms_numCutsceneObjs;
	static bool ms_loaded;
	static bool ms_animLoaded;
	static bool ms_useLodMultiplier;

	static char ms_cutsceneName[CUTSCENENAMESIZE];
	static CAnimBlendAssocGroup ms_cutsceneAssociations;
	static CVector ms_cutsceneOffset;
	static float ms_cutsceneTimer;
	static bool ms_wasCutsceneSkipped;
	static bool ms_cutsceneProcessing;
	static bool ms_useCutsceneShadows;
	static bool ms_hasFileInfo;
	static int ms_numLoadObjectNames;

	static char ms_cAppendAnimName[NUMCUTSCENEOBJECTS][NAMELENGTH];
	static char ms_cAppendObjectName[NUMCUTSCENEOBJECTS][NAMELENGTH];
	static int ms_numAppendObjectNames;
public:
	static CDirectory *ms_pCutsceneDir;
	static uint32 ms_cutsceneLoadStatus;

	static bool mCutsceneSkipFading;
	static int mCutsceneSkipFadeTime;

	static float m_fPrevCarDensity;
	static float m_fPrevPedDensity;

	static bool m_PrevExtraColourOn;
	static uint32 m_PrevExtraColour;

	static uint32 ms_iNumParticleEffects;
	static sParticleEffect ms_pParticleEffects[NUM_CUTS_PARTICLE_EFFECTS];

	static sToHideItem ms_crToHideItems[NUMCUTSCENEOBJECTS];
	static uint32 ms_iNumHiddenEntities;
	static CEntity *ms_pHiddenEntities[NUMCUTSCENEOBJECTS];

	static int ms_numAttachObjectToBones;
	static bool ms_bRepeatObject[NUMCUTSCENEOBJECTS];

	static sAttachInfo ms_iAttachObjectToBone[NUMCUTSCENEOBJECTS];

	static uint32 ms_numUncompressedCutsceneAnims;

	static char ms_aUncompressedCutsceneAnims[NUM_CUTS_UNCOMPRESSED_ANIMS][NAMELENGTH];

	static uint32 ms_iTextDuration[NUM_CUTS_MAX_TEXTS];
	static uint32 ms_iTextStartTime[NUM_CUTS_MAX_TEXTS];
	static char ms_cTextOutput[NUM_CUTS_MAX_TEXTS][TEXT_KEY_SIZE];

	static uint32 ms_currTextOutput;
	static uint32 ms_numTextOutput;
	static uint32 ms_iModelIndex[NUMCUTSCENEOBJECTS];

	static char ms_cLoadAnimName[NUMCUTSCENEOBJECTS][NAMELENGTH];
	static char ms_cLoadObjectName[NUMCUTSCENEOBJECTS][NAMELENGTH];

	static uint32 ms_cutscenePlayStatus;

	static void StartCutscene();
	static void StartCutsceneProcessing() { ms_cutsceneProcessing = true; }
	static bool IsRunning(void) { return ms_running; }
	static bool HasLoaded(void) { return ms_loaded; }
	static bool IsCutsceneProcessing(void) { return ms_cutsceneProcessing; }
	static bool WasCutsceneSkipped(void) { return ms_wasCutsceneSkipped; }
	static bool UseLodMultiplier(void) { return ms_useLodMultiplier; }
	static CCutsceneObject* GetCutsceneObject(int id) { return ms_pCutsceneObjects[id]; }
	static uint32 GetCutsceneTimeInMilleseconds(void);
	static char *GetCutsceneName(void) { return ms_cutsceneName; }
	static void SetCutsceneOffset(const CVector& vec) { ms_cutsceneOffset = vec; }
	static bool HasCutsceneFinished(void);

	static void Initialise(void *dir = nil);
	static void Shutdown(void);
	static void LoadCutsceneData(const char *szCutsceneName);
	static void FinishCutscene(void);
	static void SetupCutsceneToStart(void);
	static void SetCutsceneAnim(const char *animName, CObject *pObject);
	static void SetCutsceneAnimToLoop(const char *animName);
	static CCutsceneHead *SetHeadAnim(const char*, CObject *pObject);
	static CCutsceneObject *CreateCutsceneObject(int modelId);
	static void DeleteCutsceneData(void);
	static void LoadAnimationUncompressed(char const*);
	static void Update(void);

	static void AttachObjectToParent(CObject *pObject, CEntity *pAttachTo);
	static void AttachObjectToFrame(CObject *pObject, CEntity *pAttachTo, const char *frame);
	static void AttachObjectToBone(CObject *pObject, CObject *pAttachTo, int frame);
	static void RemoveEverythingBecauseCutsceneDoesntFitInMemory();
	static void LoadEverythingBecauseCutsceneDeletedAllOfIt();
	static void DisableCutsceneShadows() { ms_useCutsceneShadows = false; }


	static void LoadCutsceneData_overlay(const char* szCutsceneName);
	static bool LoadCutsceneData_postload(bool b = false);
	static void Update_overlay(void);
	static void DeleteCutsceneData_overlay(void);

	static bool IsCutsceneSkipButtonBeingPressed();
	static void AppendToNextCutscene(const char *object, const char *anim);

	static void LoadCutsceneData_preload();
	static void LoadCutsceneData_loading();
	static void HideRequestedObjects();

	static bool PresubBodge();

	static void Write(base::cRelocatableChunkWriter& writer);
};
