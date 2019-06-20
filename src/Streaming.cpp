#include "common.h"
#include "patcher.h"
#include "ModelInfo.h"
#include "TxdStore.h"
#include "Pools.h"
#include "Directory.h"
#include "RwHelper.h"
#include "Entity.h"
#include "FileMgr.h"
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


WRAPPER void CStreaming::RemoveModel(int32 id) { EAXJMP(0x408830); }
WRAPPER void CStreaming::RequestModel(int32 model, int32 flags) { EAXJMP(0x407EA0); }

WRAPPER void CStreaming::MakeSpaceFor(int32 size) { EAXJMP(0x409B70); }

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

	InjectHook(0x4063E0, &CStreamingInfo::GetCdPosnAndSize, PATCH_JUMP);
	InjectHook(0x406410, &CStreamingInfo::SetCdPosnAndSize, PATCH_JUMP);
	InjectHook(0x4063D0, &CStreamingInfo::GetCdSize, PATCH_JUMP);
	InjectHook(0x406380, &CStreamingInfo::AddToList, PATCH_JUMP);
	InjectHook(0x4063A0, &CStreamingInfo::RemoveFromList, PATCH_JUMP);
ENDPATCHES
