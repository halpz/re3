#pragma once

#include "Game.h"

enum {
	STREAM_OFFSET_TXD = MODELINFOSIZE,
	STREAM_OFFSET_COL = STREAM_OFFSET_TXD+TXDSTORESIZE,
	STREAM_OFFSET_ANIM = STREAM_OFFSET_COL+COLSTORESIZE,
	NUMSTREAMINFO = STREAM_OFFSET_ANIM+NUMANIMBLOCKS
};

enum StreamFlags
{
	STREAMFLAGS_DONT_REMOVE = 0x01,
	STREAMFLAGS_SCRIPTOWNED = 0x02,
	STREAMFLAGS_DEPENDENCY  = 0x04,	// Is this right?
	STREAMFLAGS_PRIORITY    = 0x08,
	STREAMFLAGS_NOFADE      = 0x10,
	STREAMFLAGS_20          = 0x20,	// TODO(MIAMI): what's this
	STREAMFLAGS_40          = 0x40, // TODO(LCS): what's this
	STREAMFLAGS_AMBIENT_SCRIPT_OWNED = 0x80,

	STREAMFLAGS_CANT_REMOVE = STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_SCRIPTOWNED|STREAMFLAGS_AMBIENT_SCRIPT_OWNED,
	STREAMFLAGS_KEEP_IN_MEMORY = STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_SCRIPTOWNED|STREAMFLAGS_DEPENDENCY |STREAMFLAGS_AMBIENT_SCRIPT_OWNED,
};

enum StreamLoadState
{
	STREAMSTATE_NOTLOADED = 0,
	STREAMSTATE_LOADED    = 1,
	STREAMSTATE_INQUEUE   = 2,
	STREAMSTATE_READING   = 3,	// channel is reading
	STREAMSTATE_STARTED   = 4,	// first part loaded
};

enum ChannelState
{
	CHANNELSTATE_IDLE = 0,
	CHANNELSTATE_READING = 1,
	CHANNELSTATE_STARTED = 2,
	CHANNELSTATE_ERROR = 3,
};

class CStreamingInfo
{
public:
	CStreamingInfo *m_next;
	CStreamingInfo *m_prev;
	uint8 m_loadState;
	uint8 m_flags;

	int16  m_nextID;
	uint32 m_position;
	uint32 m_size;

	bool GetCdPosnAndSize(uint32 &posn, uint32 &size);
	void SetCdPosnAndSize(uint32 posn, uint32 size);
	void AddToList(CStreamingInfo *link);
	void RemoveFromList(void);
	uint32 GetCdSize(void) { return m_size; }
	bool IsPriority(void) { return !!(m_flags & STREAMFLAGS_PRIORITY); }
};

struct CStreamingChannel
{
	int32 streamIds[4];
	int32 offsets[4];
	int32 state;
	int32 field24;
	int32 position;
	int32 size;
	int32 numTries;
	int32 status;	// from CdStream
};

class CDirectory;
class CPtrList;

class CStreaming
{
public:
	static bool ms_disableStreaming;
	static bool ms_bLoadingBigModel;
	static int32 ms_numModelsRequested;
	static CStreamingInfo ms_aInfoForModel[NUMSTREAMINFO];
	static CStreamingInfo ms_startLoadedList;
	static CStreamingInfo ms_endLoadedList;
	static CStreamingInfo ms_startRequestedList;
	static CStreamingInfo ms_endRequestedList;
	static int32 ms_oldSectorX;
	static int32 ms_oldSectorY;
	static int32 ms_streamingBufferSize;
#ifndef ONE_THREAD_PER_CHANNEL
	static int8 *ms_pStreamingBuffer[2];
#else
	static int8 *ms_pStreamingBuffer[4];
#endif
	static size_t ms_memoryUsed;
	static CStreamingChannel ms_channel[2];
	static int32 ms_channelError;
	static int32 ms_numVehiclesLoaded;
	static int32 ms_numPedsLoaded;
	static int32 ms_vehiclesLoaded[MAXVEHICLESLOADED];
	static int32 ms_lastVehicleDeleted;
	static bool ms_bIsPedFromPedGroupLoaded[NUMMODELSPERPEDGROUP];
	static CDirectory *ms_pExtraObjectsDir;
	static int32 ms_numPriorityRequests;
	static int32 ms_currentPedGrp;
	static int32 ms_lastCullZone;
	static uint16 ms_loadedGangs;
	static uint16 ms_loadedGangCars;
	static int32 ms_currentPedLoading;
	static int32 ms_imageOffsets[NUMCDIMAGES];
	static int32 ms_lastImageRead;
	static int32 ms_imageSize;
	static size_t ms_memoryAvailable;

	static void Init(void);
	static void Init2(void);
	static void ReInit(void);
	static void Shutdown(void);
	static void Update(void);
	static void LoadCdDirectory(void);
	static void LoadCdDirectory(const char *dirname, int32 n);
	static bool ConvertBufferToObject(int8 *buf, int32 streamId);
	static bool FinishLoadingLargeFile(int8 *buf, int32 streamId);
	static bool HasModelLoaded(int32 id) { return ms_aInfoForModel[id].m_loadState == STREAMSTATE_LOADED; }
	static bool HasTxdLoaded(int32 id) { return HasModelLoaded(id+STREAM_OFFSET_TXD); }
	static bool HasColLoaded(int32 id) { return HasModelLoaded(id+STREAM_OFFSET_COL); }
	static bool HasAnimLoaded(int32 id) { return HasModelLoaded(id+STREAM_OFFSET_ANIM); }
	static bool CanRemoveModel(int32 id) { return (ms_aInfoForModel[id].m_flags & STREAMFLAGS_CANT_REMOVE) == 0; }
	static bool IsScriptOwnedModel(int32 id) { return (ms_aInfoForModel[id].m_flags & STREAMFLAGS_SCRIPTOWNED); }
	static bool CanRemoveTxd(int32 id) { return CanRemoveModel(id+STREAM_OFFSET_TXD); }
	static bool CanRemoveCol(int32 id) { return CanRemoveModel(id+STREAM_OFFSET_COL); }
	static bool CanRemoveAnim(int32 id) { return CanRemoveModel(id+STREAM_OFFSET_ANIM); }
	static void RequestModel(int32 model, int32 flags);
	static void ReRequestModel(int32 model) { RequestModel(model, ms_aInfoForModel[model].m_flags); }
	static void RequestTxd(int32 txd, int32 flags) { RequestModel(txd + STREAM_OFFSET_TXD, flags); }
	static void ReRequestTxd(int32 txd) { ReRequestModel(txd + STREAM_OFFSET_TXD); }
	static void RequestCol(int32 col, int32 flags) { RequestModel(col + STREAM_OFFSET_COL, flags); }
	static void ReRequestCol(int32 col) { ReRequestModel(col + STREAM_OFFSET_COL); }
	static void RequestAnim(int32 col, int32 flags) { RequestModel(col + STREAM_OFFSET_ANIM, flags); }
	static void ReRequestAnim(int32 col) { ReRequestModel(col + STREAM_OFFSET_ANIM); }
	static void RequestBigBuildings(eLevelName level);
	static void RequestBigBuildings(eLevelName level, const CVector &pos);
	static void InstanceBigBuildings(eLevelName level, const CVector &pos);
	static void InstanceLoadedModelsInSectorList(CPtrList &list);
	static void InstanceLoadedModels(const CVector &pos);
	static void RequestIslands(eLevelName level);
	static void RequestSpecialModel(int32 modelId, const char *modelName, int32 flags);
	static void RequestSpecialChar(int32 charId, const char *modelName, int32 flags);
	static bool HasSpecialCharLoaded(int32 id);
	static void SetMissionDoesntRequireSpecialChar(int32 id);
	static void SetAmbientMissionDoesntRequireSpecialChar(int32 id);
	static void DecrementRef(int32 id);
	static void RemoveModel(int32 id);
	static void RemoveTxd(int32 id) { RemoveModel(id + STREAM_OFFSET_TXD); }
	static void RemoveCol(int32 id) { RemoveModel(id + STREAM_OFFSET_COL); }
	static void RemoveAnim(int32 id) { RemoveModel(id + STREAM_OFFSET_ANIM); }
	static void RemoveUnusedBuildings(eLevelName level);
	static void RemoveBuildings(eLevelName level);
	static void RemoveBuildingsNotInArea(int32 area);
	static void RemoveUnusedBigBuildings(eLevelName level);
	static void RemoveIslandsNotUsed(eLevelName level);
	static void RemoveBigBuildings(eLevelName level);
	static bool RemoveLoadedVehicle(void);
	static bool RemoveLeastUsedModel(uint32 excludeMask);
	static void RemoveAllUnusedModels(void);
	static void RemoveUnusedModelsInLoadedList(void);
	static bool RemoveLoadedZoneModel(void);
	static int32 GetAvailableVehicleSlot(void);
	static bool IsTxdUsedByRequestedModels(int32 txdId);
	static bool AreAnimsUsedByRequestedModels(int32 animId);
	static bool AddToLoadedVehiclesList(int32 modelId);
	static bool IsObjectInCdImage(int32 id);
	static void SetModelIsDeletable(int32 id);
	static void SetModelTxdIsDeletable(int32 id);
	static void SetMissionDoesntRequireModel(int32 id);
	static void SetAmbientMissionDoesntRequireModel(int32 id);
	static void LoadInitialPeds(void);
	static void LoadInitialWeapons(void);
	static void LoadInitialVehicles(void);
	static void StreamVehiclesAndPeds(void);
	static void StreamZoneModels(const CVector &pos);
	static void RemoveCurrentZonesModels(void);
	static void LoadBigBuildingsWhenNeeded(void);

	static int32 GetCdImageOffset(int32 lastPosn);
	static int32 GetNextFileOnCd(int32 position, bool priority);
	static void RequestModelStream(int32 ch);
	static bool ProcessLoadingChannel(int32 ch);
	static void RetryLoadFile(int32 ch);
	static void LoadRequestedModels(void);
	static void LoadAllRequestedModels(bool priority);
	static void FlushChannels(void);
	static void FlushRequestList(void);

	static void MakeSpaceFor(int32 size);
	static void ImGonnaUseStreamingMemory(void);
	static void IHaveUsedStreamingMemory(void);
	static void UpdateMemoryUsed(void);

	static void AddModelsToRequestList(const CVector &pos, int32 flags);
	static void ProcessEntitiesInSectorList(CPtrList &list, float x, float y, float xmin, float ymin, float xmax, float ymax, int32 flags);
	static void ProcessEntitiesInSectorList(CPtrList &list, int32 flags);
	static void DeleteFarAwayRwObjects(const CVector &pos);
	static void DeleteAllRwObjects(void);
	static void DeleteRwObjectsAfterDeath(const CVector &pos);
	static void DeleteRwObjectsBehindCamera(size_t mem); // originally signed
	static void DeleteRwObjectsInSectorList(CPtrList &list);
	static void DeleteRwObjectsInOverlapSectorList(CPtrList &list, int32 x, int32 y);
	static bool DeleteRwObjectsBehindCameraInSectorList(CPtrList &list, size_t mem); // originally signed
	static bool DeleteRwObjectsNotInFrustumInSectorList(CPtrList &list, size_t mem); // originally signed

	static void LoadScene(const CVector &pos);
	static void LoadSceneCollision(const CVector &pos);

	static void RegisterPointer(void *ptr, int, bool);
	static RpAtomic *RegisterAtomic(RpAtomic *atomic, void *);
	static void RegisterClump(RpClump *clump);
	static RpAtomic *RegisterInstance(RpAtomic *atomic, void *);
	static void RegisterInstance(RpClump *clump);
	static void UnregisterPointer(void *ptr, int);
	static RpAtomic *UnregisterAtomic(RpAtomic *atomic, void *);
	static void UnregisterClump(RpClump *clump);
	static RpAtomic *UnregisterInstance(RpAtomic *atomic, void *);
	static void UnregisterInstance(RpClump *clump);

	static void MemoryCardSave(uint8 *buffer, uint32 *length);
	static void MemoryCardLoad(uint8 *buffer, uint32 length);

	static void UpdateForAnimViewer(void);

	static void PrintStreamingBufferState();
};

// LCS(TODO): put them into CStreaming::mspInst
extern int32 islandLODindust;
extern int32 islandLODcomInd;
extern int32 islandLODcomSub;
extern int32 islandLODsubInd;
extern int32 islandLODsubCom;
