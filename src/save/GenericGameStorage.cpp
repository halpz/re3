#define WITHWINDOWS
#include "common.h"
#include "crossplatform.h"
#include "main.h"

#include "DMAudio.h"
#include "AudioScriptObject.h"
#include "Camera.h"
#include "CarGen.h"
#include "Cranes.h"
#include "Clock.h"
#include "Date.h"
#include "FileMgr.h"
#include "Font.h"
#include "Frontend.h"
#include "GameLogic.h"
#include "Gangs.h"
#include "Garages.h"
#include "GenericGameStorage.h"
#include "Pad.h"
#include "Particle.h"
#include "ParticleObject.h"
#include "PathFind.h"
#include "PCSave.h"
#include "Phones.h"
#include "Pickups.h"
#include "PlayerPed.h"
#include "ProjectileInfo.h"
#include "Pools.h"
#include "Radar.h"
#include "Restart.h"
#include "Script.h"
#include "Stats.h"
#include "Streaming.h"
#include "Timer.h"
#include "TimeStep.h"
#include "Weather.h"
#include "World.h"
#include "Zones.h"

#define BLOCK_COUNT 20
#define SIZE_OF_SIMPLEVARS 0xBC

const uint32 SIZE_OF_ONE_GAME_IN_BYTES = 201729;

#ifdef MISSION_REPLAY
int8 IsQuickSave;
const int PAUSE_SAVE_SLOT = SLOT_COUNT;
#endif

char DefaultPCSaveFileName[260];
char ValidSaveName[260];
char LoadFileName[256];
wchar SlotFileName[SLOT_COUNT][260];
wchar SlotSaveDate[SLOT_COUNT][70];
int CheckSum;
eLevelName m_LevelToLoad;
char SaveFileNameJustSaved[260];
int Slots[SLOT_COUNT+1];
CDate CompileDateAndTime;

bool b_FoundRecentSavedGameWantToLoad;
bool JustLoadedDontFadeInYet;
bool StillToFadeOut;
uint32 TimeStartedCountingForFade;
uint32 TimeToStayFadedBeforeFadeOut = 1750;

#define ReadDataFromBufferPointer(buf, to) memcpy(&to, buf, sizeof(to)); buf += align4bytes(sizeof(to));
#define WriteDataToBufferPointer(buf, from) memcpy(buf, &from, sizeof(from)); buf += align4bytes(sizeof(from));

#define LoadSaveDataBlock()\
do {\
	if (!ReadDataFromFile(file, (uint8 *) &size, 4))\
		return false;\
	size = align4bytes(size);\
	if (!ReadDataFromFile(file, work_buff, size))\
		return false;\
	buf = work_buff;\
} while (0)

#define ReadDataFromBlock(msg,load_func)\
do {\
	debug(msg);\
	ReadDataFromBufferPointer(buf, size);\
	load_func(buf, size);\
	size = align4bytes(size);\
	buf += size;\
} while (0)

#define WriteSaveDataBlock(save_func)\
do {\
	buf = work_buff;\
	reserved = 0;\
	MakeSpaceForSizeInBufferPointer(presize, buf, postsize);\
	save_func(buf, &size);\
	CopySizeAndPreparePointer(presize, buf, postsize, reserved, size);\
	if (!PcSaveHelper.PcClassSaveRoutine(file, work_buff, buf - work_buff))\
		return false;\
	totalSize += buf - work_buff;\
} while (0)

bool
GenericSave(int file)
{
	uint8 *buf, *presize, *postsize;
	uint32 size;
	uint32 reserved;

	uint32 totalSize;
	
	wchar *lastMissionPassed;
	wchar suffix[6];
	wchar saveName[24];
	SYSTEMTIME saveTime;
	CPad *currPad;

	CheckSum = 0;
	buf = work_buff;
	reserved = 0;

	// Save simple vars
	lastMissionPassed = TheText.Get(CStats::LastMissionPassedName);
	if (lastMissionPassed[0] != '\0') {
		AsciiToUnicode("...'", suffix);
#ifdef FIX_BUGS
		// fix buffer overflow
		int len = UnicodeStrlen(lastMissionPassed);
		if (len > ARRAY_SIZE(saveName)-1)
			len = ARRAY_SIZE(saveName)-1;
		memcpy(saveName, lastMissionPassed, sizeof(wchar) * len);
#else
		TextCopy(saveName, lastMissionPassed);
		int len = UnicodeStrlen(saveName);
#endif
		saveName[len] = '\0';
		if (len > ARRAY_SIZE(saveName)-2)
			TextCopy(&saveName[ARRAY_SIZE(saveName)-ARRAY_SIZE(suffix)], suffix);
		saveName[ARRAY_SIZE(saveName)-1] = '\0';
	}
	WriteDataToBufferPointer(buf, saveName);
	GetLocalTime(&saveTime);
	WriteDataToBufferPointer(buf, saveTime);
#ifdef MISSION_REPLAY
	int32 data = IsQuickSave << 24 | SIZE_OF_ONE_GAME_IN_BYTES;
	WriteDataToBufferPointer(buf, data);
#else
	WriteDataToBufferPointer(buf, SIZE_OF_ONE_GAME_IN_BYTES);
#endif
	WriteDataToBufferPointer(buf, CGame::currLevel);
	WriteDataToBufferPointer(buf, TheCamera.GetPosition().x);
	WriteDataToBufferPointer(buf, TheCamera.GetPosition().y);
	WriteDataToBufferPointer(buf, TheCamera.GetPosition().z);
	WriteDataToBufferPointer(buf, CClock::ms_nMillisecondsPerGameMinute);
	WriteDataToBufferPointer(buf, CClock::ms_nLastClockTick);
	WriteDataToBufferPointer(buf, CClock::ms_nGameClockHours);
	WriteDataToBufferPointer(buf, CClock::ms_nGameClockMinutes);
	currPad = CPad::GetPad(0);
	WriteDataToBufferPointer(buf, currPad->Mode);
	WriteDataToBufferPointer(buf, CTimer::m_snTimeInMilliseconds);
	WriteDataToBufferPointer(buf, CTimer::ms_fTimeScale);
	WriteDataToBufferPointer(buf, CTimer::ms_fTimeStep);
	WriteDataToBufferPointer(buf, CTimer::ms_fTimeStepNonClipped);
	WriteDataToBufferPointer(buf, CTimer::m_FrameCounter);
	WriteDataToBufferPointer(buf, CTimeStep::ms_fTimeStep);
	WriteDataToBufferPointer(buf, CTimeStep::ms_fFramesPerUpdate);
	WriteDataToBufferPointer(buf, CTimeStep::ms_fTimeScale);
	WriteDataToBufferPointer(buf, CWeather::OldWeatherType);
	WriteDataToBufferPointer(buf, CWeather::NewWeatherType);
	WriteDataToBufferPointer(buf, CWeather::ForcedWeatherType);
	WriteDataToBufferPointer(buf, CWeather::InterpolationValue);
	WriteDataToBufferPointer(buf, CompileDateAndTime.m_nSecond);
	WriteDataToBufferPointer(buf, CompileDateAndTime.m_nMinute);
	WriteDataToBufferPointer(buf, CompileDateAndTime.m_nHour);
	WriteDataToBufferPointer(buf, CompileDateAndTime.m_nDay);
	WriteDataToBufferPointer(buf, CompileDateAndTime.m_nMonth);
	WriteDataToBufferPointer(buf, CompileDateAndTime.m_nYear);
	WriteDataToBufferPointer(buf, CWeather::WeatherTypeInList);
#ifdef COMPATIBLE_SAVES
	// converted to float for compatibility with original format
	// TODO: maybe remove this? not really gonna break anything vital
	float f = TheCamera.CarZoomIndicator;
	WriteDataToBufferPointer(buf, f);
	f = TheCamera.PedZoomIndicator;
	WriteDataToBufferPointer(buf, f);
#else
	WriteDataToBufferPointer(buf, TheCamera.CarZoomIndicator);
	WriteDataToBufferPointer(buf, TheCamera.PedZoomIndicator);
#endif
	assert(buf - work_buff == SIZE_OF_SIMPLEVARS);

	// Save scripts, block is nested within the same block as simple vars for some reason
	presize = buf;
	buf += 4;
	postsize = buf;
	CTheScripts::SaveAllScripts(buf, &size);
	CopySizeAndPreparePointer(presize, buf, postsize, reserved, size);
	if (!PcSaveHelper.PcClassSaveRoutine(file, work_buff, buf - work_buff))
		return false;

	totalSize = buf - work_buff;

	// Save the rest
	WriteSaveDataBlock(CPools::SavePedPool);
	WriteSaveDataBlock(CGarages::Save);
	WriteSaveDataBlock(CPools::SaveVehiclePool);
	WriteSaveDataBlock(CPools::SaveObjectPool);
	WriteSaveDataBlock(ThePaths.Save);
	WriteSaveDataBlock(CCranes::Save);
	WriteSaveDataBlock(CPickups::Save);
	WriteSaveDataBlock(gPhoneInfo.Save);
	WriteSaveDataBlock(CRestart::SaveAllRestartPoints);
	WriteSaveDataBlock(CRadar::SaveAllRadarBlips);
	WriteSaveDataBlock(CTheZones::SaveAllZones);
	WriteSaveDataBlock(CGangs::SaveAllGangData);
	WriteSaveDataBlock(CTheCarGenerators::SaveAllCarGenerators);
	WriteSaveDataBlock(CParticleObject::SaveParticle);
	WriteSaveDataBlock(cAudioScriptObject::SaveAllAudioScriptObjects);
	WriteSaveDataBlock(CWorld::Players[CWorld::PlayerInFocus].SavePlayerInfo);
	WriteSaveDataBlock(CStats::SaveStats);
	WriteSaveDataBlock(CStreaming::MemoryCardSave);
	WriteSaveDataBlock(CPedType::Save);

	// sure just write garbage data repeatedly ...
#ifndef THIS_IS_STUPID
	memset(work_buff, 0, sizeof(work_buff));
#endif

	// Write padding
	for (int i = 0; i < 4; i++) {
		size = align4bytes(SIZE_OF_ONE_GAME_IN_BYTES - totalSize - 4);
		if (size > sizeof(work_buff))
			size = sizeof(work_buff);
		if (size > 4) {
			if (!PcSaveHelper.PcClassSaveRoutine(file, work_buff, size))
				return false;
			totalSize += size;
		}
	}
	
	// Write checksum and close
	CFileMgr::Write(file, (const char *) &CheckSum, sizeof(CheckSum));
	if (CFileMgr::GetErrorReadWrite(file)) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_SAVE_WRITE;
		if (!CloseFile(file))
			PcSaveHelper.nErrorCode = SAVESTATUS_ERR_SAVE_CLOSE;

		return false;
	}
	
	return true;
}

bool
GenericLoad()
{
	uint8 *buf;
	int32 file;
	uint32 size;
#ifdef MISSION_REPLAY
	int8 qs;
#endif

	int32 saveSize;
	CPad *currPad;

	// Load SimpleVars and Scripts
	CheckSum = 0;
	CDate dummy; // unused
	CPad::ResetCheats();
	if (!ReadInSizeofSaveFileBuffer(file, size))
		return false;
	size = align4bytes(size);
	ReadDataFromFile(file, work_buff, size);
	buf = (work_buff + 0x40);
	ReadDataFromBufferPointer(buf, saveSize);
#ifdef MISSION_REPLAY // a hack to keep compatibility but get new data from save
	qs = saveSize >> 24;
#endif
	ReadDataFromBufferPointer(buf, CGame::currLevel);
	ReadDataFromBufferPointer(buf, TheCamera.GetMatrix().GetPosition().x);
	ReadDataFromBufferPointer(buf, TheCamera.GetMatrix().GetPosition().y);
	ReadDataFromBufferPointer(buf, TheCamera.GetMatrix().GetPosition().z);
	ReadDataFromBufferPointer(buf, CClock::ms_nMillisecondsPerGameMinute);
	ReadDataFromBufferPointer(buf, CClock::ms_nLastClockTick);
	ReadDataFromBufferPointer(buf, CClock::ms_nGameClockHours);
	ReadDataFromBufferPointer(buf, CClock::ms_nGameClockMinutes);
	currPad = CPad::GetPad(0);
	ReadDataFromBufferPointer(buf, currPad->Mode);
	ReadDataFromBufferPointer(buf, CTimer::m_snTimeInMilliseconds);
	ReadDataFromBufferPointer(buf, CTimer::ms_fTimeScale);
	ReadDataFromBufferPointer(buf, CTimer::ms_fTimeStep);
	ReadDataFromBufferPointer(buf, CTimer::ms_fTimeStepNonClipped);
	ReadDataFromBufferPointer(buf, CTimer::m_FrameCounter);
	ReadDataFromBufferPointer(buf, CTimeStep::ms_fTimeStep);
	ReadDataFromBufferPointer(buf, CTimeStep::ms_fFramesPerUpdate);
	ReadDataFromBufferPointer(buf, CTimeStep::ms_fTimeScale);
	ReadDataFromBufferPointer(buf, CWeather::OldWeatherType);
	ReadDataFromBufferPointer(buf, CWeather::NewWeatherType);
	ReadDataFromBufferPointer(buf, CWeather::ForcedWeatherType);
	ReadDataFromBufferPointer(buf, CWeather::InterpolationValue);
	ReadDataFromBufferPointer(buf, CompileDateAndTime.m_nSecond);
	ReadDataFromBufferPointer(buf, CompileDateAndTime.m_nMinute);
	ReadDataFromBufferPointer(buf, CompileDateAndTime.m_nHour);
	ReadDataFromBufferPointer(buf, CompileDateAndTime.m_nDay);
	ReadDataFromBufferPointer(buf, CompileDateAndTime.m_nMonth);
	ReadDataFromBufferPointer(buf, CompileDateAndTime.m_nYear);
	ReadDataFromBufferPointer(buf, CWeather::WeatherTypeInList);
#ifdef COMPATIBLE_SAVES
	// converted to float for compatibility with original format
	// TODO: maybe remove this? not really gonna break anything vital
	float f;
	ReadDataFromBufferPointer(buf, f);
	TheCamera.CarZoomIndicator = f;
	ReadDataFromBufferPointer(buf, f);
	TheCamera.PedZoomIndicator = f;
#else
	ReadDataFromBufferPointer(buf, TheCamera.CarZoomIndicator);
	ReadDataFromBufferPointer(buf, TheCamera.PedZoomIndicator);
#endif
	assert(buf - work_buff == SIZE_OF_SIMPLEVARS);
#ifdef MISSION_REPLAY
	WaitForSave = 0;
	if (FrontEndMenuManager.m_nCurrSaveSlot == PAUSE_SAVE_SLOT && qs == 3)
		WaitForMissionActivate = CTimer::GetTimeInMilliseconds() + 2000;
#endif
	ReadDataFromBlock("Loading Scripts \n", CTheScripts::LoadAllScripts);

	// Load the rest
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading PedPool \n", CPools::LoadPedPool);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Garages \n", CGarages::Load);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Vehicles \n", CPools::LoadVehiclePool);
	LoadSaveDataBlock();
	CProjectileInfo::RemoveAllProjectiles();
	CObject::DeleteAllTempObjects();
	ReadDataFromBlock("Loading Objects \n", CPools::LoadObjectPool);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Paths \n", ThePaths.Load);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Cranes \n", CCranes::Load);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Pickups \n", CPickups::Load);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Phoneinfo \n", gPhoneInfo.Load);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Restart \n", CRestart::LoadAllRestartPoints);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Radar Blips \n", CRadar::LoadAllRadarBlips);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Zones \n", CTheZones::LoadAllZones);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Gang Data \n", CGangs::LoadAllGangData);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Car Generators \n", CTheCarGenerators::LoadAllCarGenerators);
	CParticle::ReloadConfig();
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Particles \n", CParticleObject::LoadParticle);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading AudioScript Objects \n", cAudioScriptObject::LoadAllAudioScriptObjects);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Player Info \n", CWorld::Players[CWorld::PlayerInFocus].LoadPlayerInfo);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Stats \n", CStats::LoadStats);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading Streaming Stuff \n", CStreaming::MemoryCardLoad);
	LoadSaveDataBlock();
	ReadDataFromBlock("Loading PedType Stuff \n", CPedType::Load);

	DMAudio.SetMusicMasterVolume(CMenuManager::m_PrefsMusicVolume);
	DMAudio.SetEffectsMasterVolume(CMenuManager::m_PrefsSfxVolume);
	if (!CloseFile(file)) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_CLOSE;
		return false;
	}

	DoGameSpecificStuffAfterSucessLoad();
	debug("Game successfully loaded \n");
	return true;
}

bool
ReadInSizeofSaveFileBuffer(int32 &file, uint32 &size)
{
	file = CFileMgr::OpenFile(LoadFileName, "rb");
	if (file == 0) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_OPEN;
		return false;
	}
	CFileMgr::Read(file, (const char*)&size, sizeof(size));
	if (CFileMgr::GetErrorReadWrite(file)) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_READ;
		if (!CloseFile(file))
			PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_CLOSE;
		return false;
	}
	return true;
}

bool
ReadDataFromFile(int32 file, uint8 *buf, uint32 size)
{
	if (file == 0) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_OPEN;
		return false;
	}
	size_t read_size = CFileMgr::Read(file, (const char*)buf, size);
	if (CFileMgr::GetErrorReadWrite(file) || read_size != size) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_READ;
		if (!CloseFile(file))
			PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_CLOSE;
		return false;
	}
	return true;
}

bool
CloseFile(int32 file)
{
	return CFileMgr::CloseFile(file) == 0;
}

void
DoGameSpecificStuffAfterSucessLoad()
{
	StillToFadeOut = true;
	JustLoadedDontFadeInYet = true;
	CTheScripts::Process();
}

bool
CheckSlotDataValid(int32 slot)
{
	PcSaveHelper.nErrorCode = SAVESTATUS_SUCCESSFUL;
	if (CheckDataNotCorrupt(slot, LoadFileName)) {
		CStreaming::DeleteAllRwObjects();
		return true;
	}

	PcSaveHelper.nErrorCode = SAVESTATUS_ERR_DATA_INVALID;
	return false;
}

void
MakeSpaceForSizeInBufferPointer(uint8 *&presize, uint8 *&buf, uint8 *&postsize)
{
	presize = buf;
	buf += sizeof(uint32);
	postsize = buf;
}

void
CopySizeAndPreparePointer(uint8 *&buf, uint8 *&postbuf, uint8 *&postbuf2, uint32 &unused, uint32 &size)
{
	memcpy(buf, &size, sizeof(size));
	size = align4bytes(size);
	postbuf2 += size;
	postbuf = postbuf2;
}

void
DoGameSpecificStuffBeforeSave()
{
	CGameLogic::PassTime(360);
	CPlayerPed *ped = FindPlayerPed();
	ped->m_fCurrentStamina = ped->m_fMaxStamina;
	CGame::TidyUpMemory(true, false);
}


void
MakeValidSaveName(int32 slot)
{
	ValidSaveName[0] = '\0';
	sprintf(ValidSaveName, "%s%i", DefaultPCSaveFileName, slot + 1);
	strncat(ValidSaveName, ".b", 5);
}

wchar *
GetSavedGameDateAndTime(int32 slot)
{
	return SlotSaveDate[slot];
}

wchar *
GetNameOfSavedGame(int32 slot)
{
	return SlotFileName[slot];
}

bool
CheckDataNotCorrupt(int32 slot, char *name)
{
#ifdef FIX_BUGS
	char filename[MAX_PATH];
#else
	char filename[100];
#endif

	int32 blocknum = 0;
	eLevelName level = LEVEL_GENERIC;
	CheckSum = 0;
	uint32 bytes_processed = 0;
	sprintf(filename, "%s%i%s", DefaultPCSaveFileName, slot + 1, ".b");
	int file = CFileMgr::OpenFile(filename, "rb");
	if (file == 0)
		return false;
	strcpy(name, filename);
	while (SIZE_OF_ONE_GAME_IN_BYTES - sizeof(uint32) > bytes_processed && blocknum < 40) {
		int32 blocksize;
		if (!ReadDataFromFile(file, (uint8*)&blocksize, sizeof(blocksize))) {
			CloseFile(file);
			return false;
		}
		if (blocksize > align4bytes(sizeof(work_buff)))
			blocksize = sizeof(work_buff) - sizeof(uint32);
		if (!ReadDataFromFile(file, work_buff, align4bytes(blocksize))) {
			CloseFile(file);
			return false;
		}

		CheckSum += ((uint8*)&blocksize)[0];
		CheckSum += ((uint8*)&blocksize)[1];
		CheckSum += ((uint8*)&blocksize)[2];
		CheckSum += ((uint8*)&blocksize)[3];
		uint8 *_work_buf = work_buff;
		for (int i = 0; i < align4bytes(blocksize); i++) {
			CheckSum += *_work_buf++;
			bytes_processed++;
		}

		if (blocknum == 0)
			memcpy(&level, work_buff+4, sizeof(level));
		blocknum++;
	}
	int32 _checkSum;
	if (ReadDataFromFile(file, (uint8*)&_checkSum, sizeof(_checkSum))) {
		if (CloseFile(file)) {
			if (CheckSum == _checkSum) {
				m_LevelToLoad = level;
				return true;
			}
			return false;
		}
		return false;
	}

	CloseFile(file);
	return false;
}

bool
RestoreForStartLoad()
{
	uint8 buf[999];

	int file = CFileMgr::OpenFile(LoadFileName, "rb");
	if (file == 0) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_OPEN;
		return false;
	}
	ReadDataFromFile(file, buf, sizeof(buf));
	if (CFileMgr::GetErrorReadWrite(file)) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_READ;
		if (!CloseFile(file))
			PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_CLOSE;
		return false;
	} else {
		uint8 *_buf = buf + sizeof(int32) + sizeof(wchar[24]) + sizeof(SYSTEMTIME) + sizeof(SIZE_OF_ONE_GAME_IN_BYTES);
		ReadDataFromBufferPointer(_buf, CGame::currLevel);
		ReadDataFromBufferPointer(_buf, TheCamera.GetMatrix().GetPosition().x);
		ReadDataFromBufferPointer(_buf, TheCamera.GetMatrix().GetPosition().y);
		ReadDataFromBufferPointer(_buf, TheCamera.GetMatrix().GetPosition().z);
		ISLAND_LOADING_IS(LOW)
		{
			CStreaming::RemoveUnusedBigBuildings(CGame::currLevel);
			CStreaming::RemoveUnusedBuildings(CGame::currLevel);
		}
		CCollision::SortOutCollisionAfterLoad();
		ISLAND_LOADING_IS(LOW)
		{
			CStreaming::RequestBigBuildings(CGame::currLevel);
			CStreaming::LoadAllRequestedModels(false);
			CStreaming::HaveAllBigBuildingsLoaded(CGame::currLevel);
			CGame::TidyUpMemory(true, false);
		}
		if (CloseFile(file)) {
			return true;
		} else {
			PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_CLOSE;
			return false;
		}
	}
}

int
align4bytes(int32 size)
{
	return (size + 3) & 0xFFFFFFFC;
}

#ifdef FIX_INCOMPATIBLE_SAVES
#define LoadSaveDataBlockNoCheck(buf, file, size) \
do { \
	CFileMgr::Read(file, (const char *)&size, sizeof(size)); \
	size = align4bytes(size); \
	CFileMgr::Read(file, (const char *)work_buff, size); \
	buf = work_buff; \
} while(0)

#define WriteSavaDataBlockNoFunc(buf, file, size) \
do { \
	if (!PcSaveHelper.PcClassSaveRoutine(file, buf, size)) \
		goto fail; \
	totalSize += size; \
} while(0)

#define FixSaveDataBlock(fix_func, file, size) \
do { \
	ReadDataFromBufferPointer(buf, size); \
	memset(work_buff2, 0, sizeof(work_buff2)); \
	buf2 = work_buff2; \
	reserved = 0; \
	MakeSpaceForSizeInBufferPointer(presize, buf2, postsize); \
	fix_func(save_type, buf, buf2, &size); \
	CopySizeAndPreparePointer(presize, buf2, postsize, reserved, size); \
	if (!PcSaveHelper.PcClassSaveRoutine(file, work_buff2, buf2 - work_buff2)) \
		goto fail; \
	totalSize += buf2 - work_buff2; \
} while(0)

#define ReadDataFromBufferPointerWithSize(buf, to, size) memcpy(&to, buf, size); buf += align4bytes(size)

#define ReadBuf(buf, to) memcpy(&to, buf, sizeof(to)); buf += sizeof(to)
#define WriteBuf(buf, from) memcpy(buf, &from, sizeof(from)); buf += sizeof(from)
#define CopyBuf(from, to, size) memcpy(to, from, size); to += (size); from += (size)
#define CopyPtr(from, to) memcpy(to, from, 4); to += 4; from += 8
#define SkipBuf(buf, size) buf += (size)
#define SkipBoth(from, to, size) to += (size); from += (size)
#define SkipPtr(from, to) to += 4; from += 8

// unfortunately we need a 2nd buffer of the same size to store the fixed output ...
static uint8 work_buff2[sizeof(work_buff)];

enum
{
	SAVE_TYPE_NONE = 0,
	SAVE_TYPE_32_BIT = 1,
	SAVE_TYPE_64_BIT = 2,
	SAVE_TYPE_MSVC = 4,
	SAVE_TYPE_GCC = 8,
};

uint8
GetSaveType(char *savename)
{
	uint8 save_type = SAVE_TYPE_NONE;
	int file = CFileMgr::OpenFile(savename, "rb");

	uint32 size;
	CFileMgr::Read(file, (const char *)&size, sizeof(size));

	uint8 *buf = work_buff;
	CFileMgr::Read(file, (const char *)work_buff, size); // simple vars + scripts

	LoadSaveDataBlockNoCheck(buf, file, size); // ped pool

	LoadSaveDataBlockNoCheck(buf, file, size); // garages
	ReadDataFromBufferPointer(buf, size);

	// store for later after we know how much data we need to skip
	ReadDataFromBufferPointerWithSize(buf, work_buff2, size);

	LoadSaveDataBlockNoCheck(buf, file, size); // vehicle pool
	LoadSaveDataBlockNoCheck(buf, file, size); // object pool
	LoadSaveDataBlockNoCheck(buf, file, size); // paths

	LoadSaveDataBlockNoCheck(buf, file, size); // cranes

	CFileMgr::CloseFile(file);

	ReadDataFromBufferPointer(buf, size);

	if (size == 1032)
		save_type |= SAVE_TYPE_32_BIT;
	else if (size == 1160)
		save_type |= SAVE_TYPE_64_BIT;
	else
		assert(0); // this should never happen

	buf = work_buff2;

	buf += 760; // skip everything before the first garage
	buf += save_type & SAVE_TYPE_32_BIT ? 28 : 40; // skip first garage up to m_fX1

	// now the values we want to verify
	float fX1, fX2, fY1, fY2, fZ1, fZ2;

	ReadBuf(buf, fX1);
	ReadBuf(buf, fX2);
	ReadBuf(buf, fY1);
	ReadBuf(buf, fY2);
	ReadBuf(buf, fZ1);
	ReadBuf(buf, fZ2);

	if (fX1 == CRUSHER_GARAGE_X1 && fX2 == CRUSHER_GARAGE_X2 &&
		fY1 == CRUSHER_GARAGE_Y1 && fY2 == CRUSHER_GARAGE_Y2 &&
		fZ1 == CRUSHER_GARAGE_Z1 && fZ2 == CRUSHER_GARAGE_Z2)
		save_type |= SAVE_TYPE_MSVC;
	else
		save_type |= SAVE_TYPE_GCC;

	return save_type;
}

static void
FixGarages(uint8 save_type, uint8 *buf, uint8 *buf2, uint32 *size)
{
	// hardcoded: 5484
	// x86 msvc: 5240
	// x86 gcc: 5040
	// amd64 msvc: 5880
	// amd64 gcc: 5808

	uint8 *buf_start = buf;
	uint8 *buf2_start = buf2;
	uint32 read;
	uint32 written = 5240;

	if (save_type & SAVE_TYPE_32_BIT && save_type & SAVE_TYPE_GCC)
		read = 5040;
	else if (save_type & SAVE_TYPE_64_BIT && save_type & SAVE_TYPE_GCC)
		read = 5808;
	else
		read = 5880;

	uint32 ptrsize = save_type & SAVE_TYPE_32_BIT ? 4 : 8;

	CopyBuf(buf, buf2, 4 * 6);
	CopyBuf(buf, buf2, 4 * TOTAL_COLLECTCARS_GARAGES);
	CopyBuf(buf, buf2, 4);

	if (save_type & SAVE_TYPE_GCC)
	{
		for (int32 i = 0; i < NUM_GARAGE_STORED_CARS; i++)
		{
#define FixStoredCar(buf, buf2) \
do { \
	CopyBuf(buf, buf2, 4 + sizeof(CVector) + sizeof(CVector)); \
	uint8 nFlags8; \
	ReadBuf(buf, nFlags8); \
	int32 nFlags32 = nFlags8; \
	WriteBuf(buf2, nFlags32); \
	CopyBuf(buf, buf2, 1 * 6); \
	SkipBuf(buf, 1); \
	SkipBuf(buf2, 2); \
} while(0)

			FixStoredCar(buf, buf2);
			FixStoredCar(buf, buf2);
			FixStoredCar(buf, buf2);

#undef FixStoredCar
		}
	}
	else
	{
		CopyBuf(buf, buf2, sizeof(CStoredCar) * NUM_GARAGE_STORED_CARS);
		CopyBuf(buf, buf2, sizeof(CStoredCar) * NUM_GARAGE_STORED_CARS);
		CopyBuf(buf, buf2, sizeof(CStoredCar) * NUM_GARAGE_STORED_CARS);
	}

	for (int32 i = 0; i < NUM_GARAGES; i++)
	{
		// skip the last 5 garages in 64bit builds without FIX_GARAGE_SIZE since they weren't actually saved and are unused
		if (save_type & SAVE_TYPE_64_BIT && *size == 5484 && i >= NUM_GARAGES - 5)
		{
			SkipBuf(buf, 160); // sizeof(CGarage) on x64
			SkipBuf(buf2, 140); // sizeof(CGarage) on x86
		}
		else
		{
			CopyBuf(buf, buf2, 1 * 6);
			SkipBoth(buf, buf2, 2);
			CopyBuf(buf, buf2, 4);
			SkipBuf(buf, ptrsize - 4); // write 4 bytes padding if 8 byte pointer, if not, write 0
			SkipBuf(buf, ptrsize * 2);
			SkipBuf(buf2, 4 * 2);
			CopyBuf(buf, buf2, 1 * 7);
			SkipBoth(buf, buf2, 1);
			CopyBuf(buf, buf2, 4 * 15 + 1);
			SkipBoth(buf, buf2, 3);
			SkipBuf(buf, ptrsize * 2);
			SkipBuf(buf2, 4 * 2);

			if (save_type & SAVE_TYPE_GCC)
				SkipBuf(buf, save_type & SAVE_TYPE_64_BIT ? 36 + 4 : 36); // sizeof(CStoredCar) on gcc 64/32 before fix
			else
				SkipBuf(buf, sizeof(CStoredCar));

			SkipBuf(buf2, sizeof(CStoredCar));
		}
	}

	*size = 0;

	assert(buf - buf_start == read);
	assert(buf2 - buf2_start == written);

#ifdef FIX_GARAGE_SIZE
	*size = (6 * sizeof(uint32) + TOTAL_COLLECTCARS_GARAGES * sizeof(*CGarages::CarTypesCollected) + sizeof(uint32) + 3 * NUM_GARAGE_STORED_CARS * sizeof(CStoredCar) + NUM_GARAGES * sizeof(CGarage));
#else
	*size = 5484;
#endif
}

static void
FixCranes(uint8 save_type, uint8 *buf, uint8 *buf2, uint32 *size)
{
	uint8 *buf_start = buf;
	uint8 *buf2_start = buf2;
	uint32 read = 2 * sizeof(uint32) + 0x480; // sizeof(aCranes)
	uint32 written = 2 * sizeof(uint32) + 0x400; // see CRANES_SAVE_SIZE

	CopyBuf(buf, buf2, 4 + 4);

	for (int32 i = 0; i < NUM_CRANES; i++)
	{
		CopyPtr(buf, buf2);
		CopyPtr(buf, buf2);
		CopyBuf(buf, buf2, 15 * 4 + sizeof(CVector) * 3 + sizeof(CVector2D));
		CopyPtr(buf, buf2);
		CopyBuf(buf, buf2, 4 + 7 * 1);
		SkipBuf(buf, 5);
		SkipBuf(buf2, 1);
	}

	*size = 0;

	assert(buf - buf_start == read);
	assert(buf2 - buf2_start == written);

	*size = written;
}

static void
FixPickups(uint8 save_type, uint8 *buf, uint8 *buf2, uint32 *size)
{
	uint8 *buf_start = buf;
	uint8 *buf2_start = buf2;
	uint32 read = 0x3480 + sizeof(uint16) + sizeof(uint16) + sizeof(int32) * NUMCOLLECTEDPICKUPS; // sizeof(aPickUps)
	uint32 written = 0x24C0 + sizeof(uint16) + sizeof(uint16) + sizeof(int32) * NUMCOLLECTEDPICKUPS; // see PICKUPS_SAVE_SIZE

	for (int32 i = 0; i < NUMPICKUPS; i++)
	{
		CopyBuf(buf, buf2, 1 + 1 + 2);
		SkipBuf(buf, 4);
		CopyPtr(buf, buf2);
		CopyBuf(buf, buf2, 4 + 2 + 2 + sizeof(CVector));
		SkipBuf(buf, 4);
	}

	CopyBuf(buf, buf2, 2);
	SkipBoth(buf, buf2, 2);

	CopyBuf(buf, buf2, NUMCOLLECTEDPICKUPS * 4);

	*size = 0;

	assert(buf - buf_start == read);
	assert(buf2 - buf2_start == written);

	*size = written;
}

static void
FixPhoneInfo(uint8 save_type, uint8 *buf, uint8 *buf2, uint32 *size)
{
	uint8 *buf_start = buf;
	uint8 *buf2_start = buf2;
	uint32 read = 0x1138; // sizeof(CPhoneInfo)
	uint32 written = 0xA30; // see PHONEINFO_SAVE_SIZE

	CopyBuf(buf, buf2, 4 + 4);

	for (int32 i = 0; i < NUMPHONES; i++)
	{
		CopyBuf(buf, buf2, sizeof(CVector));
		SkipBuf(buf, 4);
		SkipPtr(buf, buf2);
		SkipPtr(buf, buf2);
		SkipPtr(buf, buf2);
		SkipPtr(buf, buf2);
		SkipPtr(buf, buf2);
		SkipPtr(buf, buf2);
		CopyBuf(buf, buf2, 4);
		SkipBuf(buf, 4);
		CopyPtr(buf, buf2);
		CopyBuf(buf, buf2, 4 + 1);
		SkipBoth(buf, buf2, 3);
	}

	*size = 0;

	assert(buf - buf_start == read);
	assert(buf2 - buf2_start == written);

	*size = written;
}

static void
FixZones(uint8 save_type, uint8 *buf, uint8 *buf2, uint32 *size)
{
	uint8 *buf_start = buf;
	uint8 *buf2_start = buf2;
	uint32 read = 11300; // see SaveAllZones
	uint32 written = 10100; // see SaveAllZones

	CopyBuf(buf, buf2, 1 * 4);

	SkipBuf(buf, 4);
	uint32 hdr_size = 10100 - (1 * 4 + 4); // see SaveAllZones
	WriteBuf(buf2, hdr_size);

	CopyBuf(buf, buf2, 4 * 2 + 2);
	SkipBoth(buf, buf2, 2);

#define FixOneZone(buf, buf2) \
do { \
	CopyBuf(buf, buf2, 8 + 8 * 4 + 2 * 2); \
	SkipBuf(buf, 4); \
	CopyPtr(buf, buf2); \
	CopyPtr(buf, buf2); \
	CopyPtr(buf, buf2); \
} while(0)

	for (int32 i = 0; i < NUMZONES; i++)
		FixOneZone(buf, buf2);

	CopyBuf(buf, buf2, sizeof(CZoneInfo) * NUMZONES * 2);
	CopyBuf(buf, buf2, 2 + 2);

	for (int32 i = 0; i < NUMMAPZONES; i++)
		FixOneZone(buf, buf2);

	CopyBuf(buf, buf2, 2 * NUMAUDIOZONES);
	CopyBuf(buf, buf2, 2 + 2);

#undef FixOneZone

	*size = 0;

	assert(buf - buf_start == read);
	assert(buf2 - buf2_start == written);

	*size = written;
}

static void
FixParticles(uint8 save_type, uint8 *buf, uint8 *buf2, uint32 *size)
{
	uint8 *buf_start = buf;
	uint8 *buf2_start = buf2;

	int32 numObjects;
	ReadBuf(buf, numObjects);
	WriteBuf(buf2, numObjects);

	uint32 read = 0xA0 * (numObjects + 1) + 4; // sizeof(CParticleObject)
	uint32 written = 0x88 * (numObjects + 1) + 4; // see PARTICLE_OBJECT_SIZEOF

	for (int32 i = 0; i < numObjects; i++)
	{
		// CPlaceable
		SkipPtr(buf, buf2);
		CopyBuf(buf, buf2, 4 * 4 * 4);
		SkipPtr(buf, buf2);
		CopyBuf(buf, buf2, 1);
		SkipBuf(buf, 7);
		SkipBuf(buf2, 3);

		// CParticleObject
		SkipPtr(buf, buf2);
		SkipPtr(buf, buf2);
		SkipPtr(buf, buf2);
		CopyBuf(buf, buf2, 4 * 3 + 2 * 1 + 2 * 2);
		SkipBoth(buf, buf2, 2);
		CopyBuf(buf, buf2, sizeof(CVector) + 2 * 4 + sizeof(CRGBA) + 2 * 1);
		SkipBoth(buf, buf2, 2);
	}

	SkipBuf(buf, 0xA0); // sizeof(CParticleObject)
	SkipBuf(buf2, 0x88); // see PARTICLE_OBJECT_SIZEOF

	*size = 0;

	assert(buf - buf_start == read);
	assert(buf2 - buf2_start == written);

	*size = written;
}

bool
FixSave(int32 slot, uint8 save_type)
{
	if (save_type & SAVE_TYPE_32_BIT && save_type & SAVE_TYPE_MSVC)
		return true;

	bool success = false;

	uint8 *buf, *presize, *postsize, *buf2;
	uint32 size;
	uint32 reserved;

	uint32 totalSize;

	char savename[MAX_PATH];
	char savename_bak[MAX_PATH];

	sprintf(savename, "%s%i%s", DefaultPCSaveFileName, slot + 1, ".b");
	sprintf(savename_bak, "%s%i%s.%lld.bak", DefaultPCSaveFileName, slot + 1, ".b", time(nil));

	assert(caserename(savename, savename_bak) == 0);

	int file_in = CFileMgr::OpenFile(savename_bak, "rb");
	int file_out = CFileMgr::OpenFileForWriting(savename);

	CheckSum = 0;
	totalSize = 0;

	CFileMgr::Read(file_in, (const char *)&size, sizeof(size));
	size = align4bytes(size);

	buf = work_buff;
	CFileMgr::Read(file_in, (const char *)work_buff, size); // simple vars + scripts

	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // ped pool
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // garages
	FixSaveDataBlock(FixGarages, file_out, size); // garages need to be fixed in either case

	LoadSaveDataBlockNoCheck(buf, file_in, size); // vehicle pool
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // object pool
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // paths
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // cranes
	if (save_type & SAVE_TYPE_64_BIT)
		FixSaveDataBlock(FixCranes, file_out, size);
	else
		WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // pickups
	if (save_type & SAVE_TYPE_64_BIT)
		FixSaveDataBlock(FixPickups, file_out, size);
	else
		WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // phoneinfo
	if (save_type & SAVE_TYPE_64_BIT)
		FixSaveDataBlock(FixPhoneInfo, file_out, size);
	else
		WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // restart
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // radar blips
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // zones
	if (save_type & SAVE_TYPE_64_BIT)
		FixSaveDataBlock(FixZones, file_out, size);
	else
		WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // gang data
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // car generators
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // particles
	if (save_type & SAVE_TYPE_64_BIT)
		FixSaveDataBlock(FixParticles, file_out, size);
	else
		WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // audio script objects
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // player info
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // stats
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // streaming
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	LoadSaveDataBlockNoCheck(buf, file_in, size); // ped type
	WriteSavaDataBlockNoFunc(buf, file_out, size);

	memset(work_buff, 0, sizeof(work_buff));

	for (int i = 0; i < 4; i++) {
		size = align4bytes(SIZE_OF_ONE_GAME_IN_BYTES - totalSize - 4);
		if (size > sizeof(work_buff))
			size = sizeof(work_buff);
		if (size > 4) {
			if (!PcSaveHelper.PcClassSaveRoutine(file_out, work_buff, size))
				goto fail;
			totalSize += size;
		}
	}

	if (!CFileMgr::Write(file_out, (const char *)&CheckSum, sizeof(CheckSum)))
		goto fail;

	success = true;

fail:;
	CFileMgr::CloseFile(file_in);
	CFileMgr::CloseFile(file_out);

	return success;
}

#undef LoadSaveDataBlockNoCheck
#undef WriteSavaDataBlockNoFunc
#undef FixSaveDataBlock
#undef ReadDataFromBufferPointerWithSize
#undef ReadBuf
#undef WriteBuf
#undef CopyBuf
#undef CopyPtr
#undef SkipBuf
#undef SkipBoth
#undef SkipPtr
#endif

#ifdef MISSION_REPLAY

void DisplaySaveResult(int unk, char* name)
{}

bool SaveGameForPause(int type)
{
	if (AllowMissionReplay != MISSION_RETRY_STAGE_NORMAL)
		return false;
	if (type != SAVE_TYPE_QUICKSAVE_FOR_MISSION_REPLAY && WaitForSave > CTimer::GetTimeInMilliseconds())
		return false;
	WaitForSave = 0;
	if (gGameState != GS_PLAYING_GAME || CTheScripts::IsPlayerOnAMission() || CStats::LastMissionPassedName[0] == '\0') {
		DisplaySaveResult(3, CStats::LastMissionPassedName);
		return false;
	}
	IsQuickSave = type;
	MissionStartTime = 0;
	int res = PcSaveHelper.SaveSlot(PAUSE_SAVE_SLOT);
	PcSaveHelper.PopulateSlotInfo();
	IsQuickSave = 0;
	DisplaySaveResult(res, CStats::LastMissionPassedName);
	return true;
}
#endif
