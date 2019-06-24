#include "common.h"
#include "patcher.h"
#include "ModelInfo.h"
#include "TxdStore.h"
#include "ModelIndices.h"
#include "Pools.h"
#include "Directory.h"
#include "RwHelper.h"
#include "World.h"
#include "Entity.h"
#include "FileMgr.h"
#include "FileLoader.h"
#include "CdStream.h"
#include "Streaming.h"

/*
CStreaming::ms_channelError	0x880DB8	
CStreaming::ms_lastVehicleDeleted	0x95CBF8	
*/

bool &CStreaming::ms_disableStreaming = *(bool*)0x95CD6E;
bool &CStreaming::ms_bLoadingBigModel = *(bool*)0x95CDB0;
int32 &CStreaming::ms_numModelsRequested = *(int32*)0x8E2C10;
CStreamingInfo *CStreaming::ms_aInfoForModel = (CStreamingInfo*)0x6C7088;
CStreamingInfo &CStreaming::ms_startLoadedList = *(CStreamingInfo*)0x942F60;
CStreamingInfo &CStreaming::ms_endLoadedList = *(CStreamingInfo*)0x8F1AC0;
CStreamingInfo &CStreaming::ms_startRequestedList = *(CStreamingInfo*)0x8F1B3C;
CStreamingInfo &CStreaming::ms_endRequestedList = *(CStreamingInfo*)0x940738;
int32 &CStreaming::ms_oldSectorX = *(int32*)0x8F2C84;
int32 &CStreaming::ms_oldSectorY = *(int32*)0x8F2C88;
uint32 &CStreaming::ms_streamingBufferSize = *(uint32*)0x942FB0;
uint8 **CStreaming::ms_pStreamingBuffer = (uint8**)0x87F818;
int32 &CStreaming::ms_memoryUsed = *(int32*)0x940568;
CStreamingChannel *CStreaming::ms_channel = (CStreamingChannel*)0x727EE0;
int32 &CStreaming::ms_numVehiclesLoaded = *(int32*)0x8F2C80;
int32 *CStreaming::ms_vehiclesLoaded = (int32*)0x773560;
CDirectory *&CStreaming::ms_pExtraObjectsDir = *(CDirectory**)0x95CB90;
int32 &CStreaming::ms_numPriorityRequests = *(int32*)0x8F31C4;
bool &CStreaming::ms_hasLoadedLODs = *(bool*)0x95CD47;
int32 &CStreaming::ms_currentPedGrp = *(int32*)0x8F2BBC;
int32 CStreaming::ms_currentPedLoading;
int32 CStreaming::ms_lastCullZone;
uint16 &CStreaming::ms_loadedGangs = *(uint16*)0x95CC60;
int32 *CStreaming::ms_imageOffsets = (int32*)0x6E60A0;
int32 &CStreaming::ms_lastImageRead = *(int32*)0x880E2C;
int32 &CStreaming::ms_imageSize = *(int32*)0x8F1A34;
int32 &CStreaming::ms_memoryAvailable = *(int32*)0x880F8C;

int32 &desiredNumVehiclesLoaded = *(int32*)0x5EC194;

CEntity *&pIslandLODindustEntity = *(CEntity**)0x6212DC;
CEntity *&pIslandLODcomIndEntity = *(CEntity**)0x6212E0;
CEntity *&pIslandLODcomSubEntity = *(CEntity**)0x6212E4;
CEntity *&pIslandLODsubIndEntity = *(CEntity**)0x6212E8;
CEntity *&pIslandLODsubComEntity = *(CEntity**)0x6212EC;
int32 &islandLODindust = *(int32*)0x6212C8;
int32 &islandLODcomInd = *(int32*)0x6212CC;
int32 &islandLODcomSub = *(int32*)0x6212D0;
int32 &islandLODsubInd = *(int32*)0x6212D4;
int32 &islandLODsubCom = *(int32*)0x6212D8;

WRAPPER void CStreaming::MakeSpaceFor(int32 size) { EAXJMP(0x409B70); }
WRAPPER bool CStreaming::IsTxdUsedByRequestedModels(int32 txdId) { EAXJMP(0x4094C0); }
WRAPPER bool CStreaming::AddToLoadedVehiclesList(int32 modelId) { EAXJMP(0x40B060); }


void
CStreaming::Init(void)
{
	int i;

	for(i = 0; i < NUMSTREAMINFO; i++){
		ms_aInfoForModel[i].m_loadState = STREAMSTATE_NOTLOADED;
		ms_aInfoForModel[i].m_next = nil;
		ms_aInfoForModel[i].m_prev = nil;
		ms_aInfoForModel[i].m_nextID = -1;
		ms_aInfoForModel[i].m_size = 0;
		ms_aInfoForModel[i].m_position = 0;
	}

	// init lists

	ms_startLoadedList.m_next = &ms_endLoadedList;
	ms_startLoadedList.m_prev = nil;
	ms_endLoadedList.m_prev = &ms_startLoadedList;
	ms_endLoadedList.m_next = nil;

	ms_startRequestedList.m_next = &ms_endRequestedList;
	ms_startRequestedList.m_prev = nil;
	ms_endRequestedList.m_prev = &ms_startRequestedList;
	ms_endRequestedList.m_next = nil;

	// init misc

	ms_oldSectorX = 0;
	ms_oldSectorY = 0;
	ms_streamingBufferSize = 0;
	ms_disableStreaming = false;
	ms_memoryUsed = 0;
	ms_bLoadingBigModel = false;

	// init channels

	ms_channel[0].state = CHANNELSTATE_0;
	ms_channel[1].state = CHANNELSTATE_0;
	for(i = 0; i < 4; i++){
		ms_channel[0].modelIds[i] = -1;
		ms_channel[0].offsets[i] = -1;
		ms_channel[1].modelIds[i] = -1;
		ms_channel[1].offsets[i] = -1;
	}

	// init stream info, mark things that are already loaded

	for(i = 0; i < MODELINFOSIZE; i++){
		CBaseModelInfo *mi = CModelInfo::GetModelInfo(i);
		if(mi && mi->GetRwObject()){
			ms_aInfoForModel[i + STREAM_OFFSET_MODEL].m_loadState = STREAMSTATE_LOADED;
			ms_aInfoForModel[i + STREAM_OFFSET_MODEL].m_flags = STREAMFLAGS_DONT_REMOVE;
			if(mi->IsSimple())
				((CSimpleModelInfo*)mi)->m_alpha = 255;
		}
	}

	for(i = 0; i < TXDSTORESIZE; i++)
		if(CTxdStore::GetSlot(i) && CTxdStore::GetSlot(i)->texDict)
			ms_aInfoForModel[i + STREAM_OFFSET_TXD].m_loadState = STREAMSTATE_LOADED;


	for(i = 0; i < MAXVEHICLESLOADED; i++)
		ms_vehiclesLoaded[i] = -1;
	ms_numVehiclesLoaded = 0;

	ms_pExtraObjectsDir = new CDirectory(EXTRADIRSIZE);
	ms_numPriorityRequests = 0;
	ms_hasLoadedLODs = true;
	ms_currentPedGrp = -1;
	ms_lastCullZone = -1;		// unused because RemoveModelsNotVisibleFromCullzone is gone
	ms_loadedGangs = 0;
	ms_currentPedLoading = 8;	// unused, whatever it is

	LoadCdDirectory();

	// allocate streaming buffers
	if(ms_streamingBufferSize & 1) ms_streamingBufferSize++;
	ms_pStreamingBuffer[0] = (uint8*)RwMallocAlign(ms_streamingBufferSize*CDSTREAM_SECTOR_SIZE, CDSTREAM_SECTOR_SIZE);
	ms_streamingBufferSize /= 2;
	ms_pStreamingBuffer[1] = ms_pStreamingBuffer[0] + ms_streamingBufferSize*CDSTREAM_SECTOR_SIZE;
	debug("Streaming buffer size is %d sectors", ms_streamingBufferSize);

	// PC only, figure out how much memory we got
#define MB (1024*1024)
	extern DWORD &_dwMemAvailPhys;
	ms_memoryAvailable = (_dwMemAvailPhys - 10*MB)/2;
	if(ms_memoryAvailable < 50*MB)
		ms_memoryAvailable = 50*MB;
	desiredNumVehiclesLoaded = (ms_memoryAvailable/MB - 50)/3 + 12;
	if(desiredNumVehiclesLoaded > MAXVEHICLESLOADED)
		desiredNumVehiclesLoaded = MAXVEHICLESLOADED;
	debug("Memory allocated to Streaming is %dMB", ms_memoryAvailable/MB);
#undef MB

	// find island LODs

	pIslandLODindustEntity = nil;
	pIslandLODcomIndEntity = nil;
	pIslandLODcomSubEntity = nil;
	pIslandLODsubIndEntity = nil;
	pIslandLODsubComEntity = nil;
	islandLODindust = -1;
	islandLODcomInd = -1;
	islandLODcomSub = -1;
	islandLODsubInd = -1;
	islandLODsubCom = -1;
        CModelInfo::GetModelInfo("IslandLODInd", &islandLODindust);
        CModelInfo::GetModelInfo("IslandLODcomIND", &islandLODcomInd);
        CModelInfo::GetModelInfo("IslandLODcomSUB", &islandLODcomSub);
        CModelInfo::GetModelInfo("IslandLODsubIND", &islandLODsubInd);
        CModelInfo::GetModelInfo("IslandLODsubCOM", &islandLODsubCom);

	for(i = 0; i < CPools::GetBuildingPool()->GetSize(); i++){
		CBuilding *building = CPools::GetBuildingPool()->GetSlot(i);
		if(building == nil)
			continue;
		if(building->GetModelIndex() == islandLODindust) pIslandLODindustEntity = building;
		if(building->GetModelIndex() == islandLODcomInd) pIslandLODcomIndEntity = building;
		if(building->GetModelIndex() == islandLODcomSub) pIslandLODcomSubEntity = building;
		if(building->GetModelIndex() == islandLODsubInd) pIslandLODsubIndEntity = building;
		if(building->GetModelIndex() == islandLODsubCom) pIslandLODsubComEntity = building;
	}
}

void
CStreaming::Shutdown(void)
{
	RwFreeAlign(ms_pStreamingBuffer[0]);
	ms_streamingBufferSize = 0;
	if(ms_pExtraObjectsDir)
		delete ms_pExtraObjectsDir;
}

void
CStreaming::LoadCdDirectory(void)
{
	char dirname[132];
	int i;

	// PC specific stuff
	ms_imageOffsets[0] = 0;
	for(i = 1; i < NUMCDIMAGES; i++)
		ms_imageOffsets[i] = -1;
	ms_imageSize = GetGTA3ImgSize();

	i = CdStreamGetNumImages();
	while(i-- >= 1){
		strcpy(dirname, CdStreamGetImageName(i));
		strncpy(strrchr(dirname, '.') + 1, "DIR", 3);
		LoadCdDirectory(dirname, i);
	}

	ms_lastImageRead = 0;
	ms_imageSize /= CDSTREAM_SECTOR_SIZE;
}

void
CStreaming::LoadCdDirectory(const char *dirname, int n)
{
	int fd, lastID, imgSelector;
	int modelId, txdId;
	uint32 posn, size;
	CDirectory::DirectoryInfo direntry;
	char *dot;

	lastID = -1;
	fd = CFileMgr::OpenFile(dirname, "rb");
	assert(fd > 0);

	imgSelector = n<<24;
	assert(sizeof(direntry) == 32);
	while(CFileMgr::Read(fd, (char*)&direntry, sizeof(direntry))){
		dot = strchr(direntry.name, '.');
		if(dot) *dot = '\0';
		if(direntry.size > ms_streamingBufferSize)
			ms_streamingBufferSize = direntry.size;

		if(strcmp(dot+1, "DFF") == 0 || strcmp(dot+1, "dff") == 0){
			if(CModelInfo::GetModelInfo(direntry.name, &modelId)){
				if(ms_aInfoForModel[modelId + STREAM_OFFSET_MODEL].GetCdPosnAndSize(posn, size)){
					debug("%s appears more than once in %s\n", direntry.name, dirname);
					lastID = -1;
				}else{
					direntry.offset |= imgSelector;
					ms_aInfoForModel[modelId + STREAM_OFFSET_MODEL].SetCdPosnAndSize(direntry.offset, direntry.size);
					if(lastID != -1)
						ms_aInfoForModel[lastID].m_nextID = modelId + STREAM_OFFSET_MODEL;
					lastID = modelId + STREAM_OFFSET_MODEL;
				}
			}else{
				// BUG: doesn't remember which cdimage this was in
				ms_pExtraObjectsDir->AddItem(direntry);
				lastID = -1;
			}
		}else if(strcmp(dot+1, "TXD") == 0 || strcmp(dot+1, "txd") == 0){
			txdId = CTxdStore::FindTxdSlot(direntry.name);
			if(txdId == -1)
				txdId = CTxdStore::AddTxdSlot(direntry.name);
				if(ms_aInfoForModel[txdId + STREAM_OFFSET_TXD].GetCdPosnAndSize(posn, size)){
					debug("%s appears more than once in %s\n", direntry.name, dirname);
					lastID = -1;
				}else{
					direntry.offset |= imgSelector;
					ms_aInfoForModel[txdId + STREAM_OFFSET_TXD].SetCdPosnAndSize(direntry.offset, direntry.size);
					if(lastID != -1)
						ms_aInfoForModel[lastID].m_nextID = txdId + STREAM_OFFSET_TXD;
					lastID = txdId + STREAM_OFFSET_TXD;
				}
		}else
			lastID = -1;
	}

	CFileMgr::CloseFile(fd);
}

bool
CStreaming::ConvertBufferToObject(int8 *buf, int32 streamId)
{
	RwMemory mem;
	RwStream *stream;
	int cdsize;
	uint32 startTime, endTime, timeDiff;
	CBaseModelInfo *mi;
	bool success;

	startTime = CTimer::GetCurrentTimeInCycles() / CTimer::GetCyclesPerMillisecond();

	cdsize = ms_aInfoForModel[streamId].GetCdSize();
	mem.start = (uint8*)buf;
	mem.length = cdsize * CDSTREAM_SECTOR_SIZE;
	stream = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMREAD, &mem);

	if(streamId < STREAM_OFFSET_TXD){
		// Model
		mi = CModelInfo::GetModelInfo(streamId - STREAM_OFFSET_MODEL);

		// Txd has to be loaded
		if(CTxdStore::GetSlot(mi->GetTxdSlot())->texDict == nil){
			debug("failed to load %s because TXD %s is not in memory\n", mi->GetName(), CTxdStore::GetTxdName(mi->GetTxdSlot()));
			RemoveModel(streamId);
			RemoveModel(mi->GetTxdSlot() + STREAM_OFFSET_TXD);
			// re-request
			RequestModel(streamId, ms_aInfoForModel[streamId].m_flags);
			RwStreamClose(stream, &mem);
			return false;
		}

		// Set Txd to use
		CTxdStore::AddRef(mi->GetTxdSlot());
		CTxdStore::SetCurrentTxd(mi->GetTxdSlot());

		if(mi->IsSimple()){
			success = CFileLoader::LoadAtomicFile(stream, streamId - STREAM_OFFSET_MODEL);
		}else if(mi->m_type == MITYPE_VEHICLE){
			// load vehicles in two parts
			CModelInfo::GetModelInfo(streamId - STREAM_OFFSET_MODEL)->AddRef();
			success = CFileLoader::StartLoadClumpFile(stream, streamId - STREAM_OFFSET_MODEL);
			if(success)
				ms_aInfoForModel[streamId].m_loadState = STREAMSTATE_STARTED;
		}else{
			success = CFileLoader::LoadClumpFile(stream, streamId - STREAM_OFFSET_MODEL);
		}
		UpdateMemoryUsed();

		// Txd no longer needed unless we only read part of the file
		if(ms_aInfoForModel[streamId].m_loadState != STREAMSTATE_STARTED)
			CTxdStore::RemoveRefWithoutDelete(mi->GetTxdSlot());

		if(!success){
			debug("Failed to load %s\n", CModelInfo::GetModelInfo(streamId - STREAM_OFFSET_MODEL)->GetName());
			RemoveModel(streamId);
			// re-request
			RequestModel(streamId, ms_aInfoForModel[streamId].m_flags);
			RwStreamClose(stream, &mem);
			return false;
		}
	}else{
		// Txd
		assert(streamId < NUMSTREAMINFO);
		if((ms_aInfoForModel[streamId].m_flags & STREAMFLAGS_KEEP_IN_MEMORY) == 0 &&
		   !IsTxdUsedByRequestedModels(streamId - STREAM_OFFSET_TXD)){
			RemoveModel(streamId);
			RwStreamClose(stream, &mem);
			return false;
		}

		if(ms_bLoadingBigModel || cdsize > 200){
			success = CTxdStore::StartLoadTxd(streamId - STREAM_OFFSET_TXD, stream);
			if(success)
				ms_aInfoForModel[streamId].m_loadState = STREAMSTATE_STARTED;
		}else
		        success = CTxdStore::LoadTxd(streamId - STREAM_OFFSET_TXD, stream);
		UpdateMemoryUsed();

		if(!success){
			debug("Failed to load %s.txd\n", CTxdStore::GetTxdName(streamId - STREAM_OFFSET_TXD));
			RemoveModel(streamId);
			// re-request
			RequestModel(streamId, ms_aInfoForModel[streamId].m_flags);
			RwStreamClose(stream, &mem);
			return false;
		}
	}

	RwStreamClose(stream, &mem);

	// We shouldn't even end up here unless load was successful
	if(!success){
		RequestModel(streamId, ms_aInfoForModel[streamId].m_flags);
		if(streamId < STREAM_OFFSET_TXD)
			debug("Failed to load %s.dff\n", mi->GetName());
		else
			debug("Failed to load %s.txd\n", CTxdStore::GetTxdName(streamId - STREAM_OFFSET_TXD));
		return false;
	}

	if(streamId < STREAM_OFFSET_TXD){
		// Model
		// Vehicles and Peds not in loaded list
		if(mi->m_type != MITYPE_VEHICLE && mi->m_type != MITYPE_PED){
			CSimpleModelInfo *smi = (CSimpleModelInfo*)mi;

			// Set fading for some objects
			if(mi->IsSimple() && !smi->m_isBigBuilding){
				if(ms_aInfoForModel[streamId].m_flags & STREAMFLAGS_NOFADE)
					smi->m_alpha = 255;
				else
					smi->m_alpha = 0;
			}

			if((ms_aInfoForModel[streamId].m_flags & STREAMFLAGS_NOT_IN_LIST) == 0)
				ms_aInfoForModel[streamId].AddToList(&ms_startLoadedList);
		}
	}else{
		// Txd
		if((ms_aInfoForModel[streamId].m_flags & STREAMFLAGS_NOT_IN_LIST) == 0)
			ms_aInfoForModel[streamId].AddToList(&ms_startLoadedList);
	}

	// Mark objects as loaded
	if(ms_aInfoForModel[streamId].m_loadState != STREAMSTATE_STARTED){
		ms_aInfoForModel[streamId].m_loadState = STREAMSTATE_LOADED;
		ms_memoryUsed += ms_aInfoForModel[streamId].GetCdSize() * CDSTREAM_SECTOR_SIZE;
	}

	endTime = CTimer::GetCurrentTimeInCycles() / CTimer::GetCyclesPerMillisecond();
	timeDiff = endTime - startTime;
	if(timeDiff > 5){
		if(streamId < STREAM_OFFSET_TXD)
			debug("model %s took %d ms\n", CModelInfo::GetModelInfo(streamId - STREAM_OFFSET_MODEL)->GetName(), timeDiff);
		else
			debug("txd %s took %d ms\n", CTxdStore::GetTxdName(streamId - STREAM_OFFSET_TXD), timeDiff);
	}

	return true;
}


bool
CStreaming::FinishLoadingLargeFile(int8 *buf, int32 streamId)
{
	RwMemory mem;
	RwStream *stream;
	uint32 startTime, endTime, timeDiff;
	CBaseModelInfo *mi;
	bool success;

	startTime = CTimer::GetCurrentTimeInCycles() / CTimer::GetCyclesPerMillisecond();

	if(ms_aInfoForModel[streamId].m_loadState != STREAMSTATE_STARTED){
		if(streamId < STREAM_OFFSET_TXD)
			CModelInfo::GetModelInfo(streamId - STREAM_OFFSET_MODEL)->RemoveRef();
		return false;
	}

	mem.start = (uint8*)buf;
	mem.length = ms_aInfoForModel[streamId].GetCdSize() * CDSTREAM_SECTOR_SIZE;
	stream = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMREAD, &mem);

	if(streamId < STREAM_OFFSET_TXD){
		// Model
		mi = CModelInfo::GetModelInfo(streamId - STREAM_OFFSET_MODEL);
		CTxdStore::SetCurrentTxd(mi->GetTxdSlot());
		success = CFileLoader::FinishLoadClumpFile(stream, streamId);
		if(success)
			success = AddToLoadedVehiclesList(streamId);
		mi->RemoveRef();
		CTxdStore::RemoveRefWithoutDelete(mi->GetTxdSlot());
	}else{
		// Txd
		CTxdStore::AddRef(streamId - STREAM_OFFSET_TXD);
		success = CTxdStore::FinishLoadTxd(streamId - STREAM_OFFSET_TXD, stream);
		CTxdStore::RemoveRefWithoutDelete(streamId - STREAM_OFFSET_TXD);
	}

	RwStreamClose(stream, &mem);
	ms_aInfoForModel[streamId].m_loadState = STREAMSTATE_LOADED;
	ms_memoryUsed += ms_aInfoForModel[streamId].GetCdSize() * CDSTREAM_SECTOR_SIZE;

	if(!success){
		RemoveModel(streamId);
		// re-request
		RequestModel(streamId, ms_aInfoForModel[streamId].m_flags);
		UpdateMemoryUsed();
		return false;
	}

	UpdateMemoryUsed();

	endTime = CTimer::GetCurrentTimeInCycles() / CTimer::GetCyclesPerMillisecond();
	timeDiff = endTime - startTime;
	if(timeDiff > 5){
		if(streamId < STREAM_OFFSET_TXD)
			debug("finish model %s took %d ms\n", CModelInfo::GetModelInfo(streamId - STREAM_OFFSET_MODEL)->GetName(), timeDiff);
		else
			debug("finish txd %s took %d ms\n", CTxdStore::GetTxdName(streamId - STREAM_OFFSET_TXD), timeDiff);
	}

	return true;
}

void
CStreaming::RequestModel(int32 id, int32 flags)
{
	CSimpleModelInfo *mi;

	if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_INQUEUE){
		// updgrade to priority
		if(flags & STREAMFLAGS_PRIORITY && (ms_aInfoForModel[id].m_flags & STREAMFLAGS_PRIORITY) == 0){
			ms_numPriorityRequests++;
			ms_aInfoForModel[id].m_flags |= STREAMFLAGS_PRIORITY;
		}
	}else if(ms_aInfoForModel[id].m_loadState != STREAMSTATE_NOTLOADED){
		flags &= ~STREAMFLAGS_PRIORITY;
	}
	ms_aInfoForModel[id].m_flags |= flags;

	if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_LOADED){
		// Already loaded, only check changed flags

		if(ms_aInfoForModel[id].m_flags & STREAMFLAGS_NOFADE && id < STREAM_OFFSET_TXD){
			mi = (CSimpleModelInfo*)CModelInfo::GetModelInfo(id - STREAM_OFFSET_MODEL);
			if(mi->IsSimple())
				mi->m_alpha = 255;
		}

		// reinsert into list
		if(ms_aInfoForModel[id].m_next){
			ms_aInfoForModel[id].RemoveFromList();
			if((ms_aInfoForModel[id].m_flags & STREAMFLAGS_NOT_IN_LIST) == 0)
				ms_aInfoForModel[id].AddToList(&ms_startLoadedList);
		}
	}else if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_NOTLOADED ||
	         ms_aInfoForModel[id].m_loadState == STREAMSTATE_LOADED){	// how can this be true again?

		if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_NOTLOADED){
			if(id < STREAM_OFFSET_TXD)
				RequestTxd(CModelInfo::GetModelInfo(id - STREAM_OFFSET_MODEL)->GetTxdSlot(), flags);
			ms_aInfoForModel[id].AddToList(&ms_startRequestedList);
			ms_numModelsRequested++;
			if(flags & STREAMFLAGS_PRIORITY)
				ms_numPriorityRequests++;
		}

		ms_aInfoForModel[id].m_loadState = STREAMSTATE_INQUEUE;
		ms_aInfoForModel[id].m_flags = flags;
	}
}

void
CStreaming::RequestSubway(void)
{
	RequestModel(MI_SUBWAY1, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY2, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY3, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY4, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY5, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY6, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY7, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY8, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY9, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY10, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY11, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY12, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY13, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY14, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY15, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY16, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY17, STREAMFLAGS_NOFADE);
	RequestModel(MI_SUBWAY18, STREAMFLAGS_NOFADE);

	switch(CGame::currLevel){
	case LEVEL_INDUSTRIAL:
		RequestModel(MI_SUBPLATFORM_IND, STREAMFLAGS_NOFADE);
		break;
	case LEVEL_COMMERCIAL:
		if(FindPlayerTrain()->GetPosition().y < -700.0f){
			RequestModel(MI_SUBPLATFORM_COMS, STREAMFLAGS_NOFADE);
			RequestModel(MI_SUBPLATFORM_COMS2, STREAMFLAGS_NOFADE);
		}else{
			RequestModel(MI_SUBPLATFORM_COMN, STREAMFLAGS_NOFADE);
		}
		break;
	case LEVEL_SUBURBAN:
		RequestModel(MI_SUBPLATFORM_SUB, STREAMFLAGS_NOFADE);
		RequestModel(MI_SUBPLATFORM_SUB2, STREAMFLAGS_NOFADE);
		break;
	}
}

void
CStreaming::RequestBigBuildings(eLevelName level)
{
	int i, n;
	CBuilding *b;

	n = CPools::GetBuildingPool()->GetSize();
	for(i = 0; i < n; i++){
		b = CPools::GetBuildingPool()->GetSlot(i);
		if(b && b->bIsBIGBuilding && b->m_level == level)
			RequestModel(b->GetModelIndex(), STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_PRIORITY);
	}
	RequestIslands(level);
	ms_hasLoadedLODs = false;
}

void
CStreaming::RequestIslands(eLevelName level)
{
	switch(level){
	case LEVEL_INDUSTRIAL:
		RequestModel(islandLODcomInd, STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_PRIORITY);
		RequestModel(islandLODsubInd, STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_PRIORITY);
		break;
	case LEVEL_COMMERCIAL:
		RequestModel(islandLODindust, STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_PRIORITY);
		RequestModel(islandLODsubCom, STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_PRIORITY);
		break;
	case LEVEL_SUBURBAN:
		RequestModel(islandLODindust, STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_PRIORITY);
		RequestModel(islandLODcomSub, STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_PRIORITY);
		break;
	}
}

void
CStreaming::RequestSpecialModel(int32 modelId, const char *modelName, int32 flags)
{
	CBaseModelInfo *mi;
	int txdId;
	char oldName[48];
	uint32 pos, size;

	mi = CModelInfo::GetModelInfo(modelId);
	if(strcmp(mi->GetName(), modelName) == 0){
		// Already have the correct name, just request it
		RequestModel(modelId, flags);
		return;
	}

	strcpy(oldName, mi->GetName());
	mi->SetName(modelName);

	// What exactly is going on here?
	if(CModelInfo::GetModelInfo(oldName, nil)){
		txdId = CTxdStore::FindTxdSlot(oldName);
		if(txdId != -1 && CTxdStore::GetSlot(txdId)->texDict){
			CTxdStore::AddRef(txdId);
			RemoveModel(modelId);
			CTxdStore::RemoveRefWithoutDelete(txdId);
		}else
			RemoveModel(modelId);
	}else
		RemoveModel(modelId);

	ms_pExtraObjectsDir->FindItem(modelName, pos, size);
	mi->ClearTexDictionary();
	if(CTxdStore::FindTxdSlot(modelName) == -1)
		mi->SetTexDictionary("generic");
	else
		mi->SetTexDictionary(modelName);
	ms_aInfoForModel[modelId].SetCdPosnAndSize(pos, size);
	RequestModel(modelId, flags);
}

void
CStreaming::RequestSpecialChar(int32 charId, const char *modelName, int32 flags)
{
	RequestSpecialModel(charId + MI_SPECIAL01, modelName, flags);
}

void
CStreaming::RemoveModel(int32 id)
{
	int i;

	if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_NOTLOADED)
		return;

	if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_LOADED){
		if(id < STREAM_OFFSET_TXD)
			CModelInfo::GetModelInfo(id - STREAM_OFFSET_MODEL)->DeleteRwObject();
		else
			CTxdStore::RemoveTxd(id - STREAM_OFFSET_TXD);
		ms_memoryUsed -= ms_aInfoForModel[id].GetCdSize()*CDSTREAM_SECTOR_SIZE;
	}

	if(ms_aInfoForModel[id].m_next){
		// Remove from list, model is neither loaded nor requested
		if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_INQUEUE){
			ms_numModelsRequested--;
			if(ms_aInfoForModel[id].m_flags & STREAMFLAGS_PRIORITY){
				ms_aInfoForModel[id].m_flags &= ~STREAMFLAGS_PRIORITY;
				ms_numPriorityRequests--;
			}
		}
		ms_aInfoForModel[id].RemoveFromList();
	}else if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_READING){
		for(i = 0; i < 4; i++){
			if(ms_channel[0].modelIds[i] == id - STREAM_OFFSET_MODEL)
				ms_channel[0].modelIds[i] = -1;
			if(ms_channel[1].modelIds[i] == id - STREAM_OFFSET_MODEL)
				ms_channel[1].modelIds[i] = -1;
		}
	}

	if(ms_aInfoForModel[id].m_loadState == STREAMSTATE_STARTED){
		if(id < STREAM_OFFSET_TXD)
			RpClumpGtaCancelStream();
		else
			CTxdStore::RemoveTxd(id - STREAM_OFFSET_TXD);
	}

	ms_aInfoForModel[id].m_loadState = STREAMSTATE_NOTLOADED;
}


void
CStreaming::ImGonnaUseStreamingMemory(void)
{
}

void
CStreaming::IHaveUsedStreamingMemory(void)
{
	UpdateMemoryUsed();
}

void
CStreaming::UpdateMemoryUsed(void)
{
}

WRAPPER void CStreaming::LoadScene(CVector *pos) { EAXJMP(0x40A6D0); }
WRAPPER void CStreaming::LoadAllRequestedModels(bool) { EAXJMP(0x40A440); }

bool
CStreamingInfo::GetCdPosnAndSize(uint32 &posn, uint32 &size)
{
	if(m_size == 0)
		return false;
	posn = m_position;
	size = m_size;
	return true;
}

void
CStreamingInfo::SetCdPosnAndSize(uint32 posn, uint32 size)
{
	m_position = posn;
	m_size = size;
}

void
CStreamingInfo::AddToList(CStreamingInfo *link)
{
	// Insert this after link
	m_next = link->m_next;
	m_prev = link;
	link->m_next = this;
	m_next->m_prev = this;
}

void
CStreamingInfo::RemoveFromList(void)
{
	m_next->m_prev = m_prev;
	m_prev->m_next = m_next;
	m_next = nil;
	m_prev = nil;
}

STARTPATCHES
	InjectHook(0x406430, CStreaming::Init, PATCH_JUMP);
	InjectHook(0x406C80, CStreaming::Shutdown, PATCH_JUMP);
	InjectHook(0x406CC0, (void (*)(void))CStreaming::LoadCdDirectory, PATCH_JUMP);
	InjectHook(0x406DA0, (void (*)(const char*, int))CStreaming::LoadCdDirectory, PATCH_JUMP);
	InjectHook(0x409740, CStreaming::ConvertBufferToObject, PATCH_JUMP);
	InjectHook(0x409580, CStreaming::FinishLoadingLargeFile, PATCH_JUMP);
	InjectHook(0x407EA0, CStreaming::RequestModel, PATCH_JUMP);
	InjectHook(0x407FD0, CStreaming::RequestSubway, PATCH_JUMP);
	InjectHook(0x408190, CStreaming::RequestBigBuildings, PATCH_JUMP);
	InjectHook(0x408210, CStreaming::RequestIslands, PATCH_JUMP);
	InjectHook(0x40A890, CStreaming::RequestSpecialModel, PATCH_JUMP);
	InjectHook(0x40ADA0, CStreaming::RequestSpecialChar, PATCH_JUMP);
	InjectHook(0x408830, CStreaming::RemoveModel, PATCH_JUMP);

	InjectHook(0x4063E0, &CStreamingInfo::GetCdPosnAndSize, PATCH_JUMP);
	InjectHook(0x406410, &CStreamingInfo::SetCdPosnAndSize, PATCH_JUMP);
	InjectHook(0x4063D0, &CStreamingInfo::GetCdSize, PATCH_JUMP);
	InjectHook(0x406380, &CStreamingInfo::AddToList, PATCH_JUMP);
	InjectHook(0x4063A0, &CStreamingInfo::RemoveFromList, PATCH_JUMP);
ENDPATCHES
