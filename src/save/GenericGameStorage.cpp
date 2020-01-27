#include "common.h"
#include "main.h"
#include "patcher.h"
#include "Camera.h"
#include "Clock.h"
#include "Date.h"
#include "FileMgr.h"
#include "GameLogic.h"
#include "Garages.h"
#include "GenericGameStorage.h"
#include "PCSave.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "Script.h"
#include "Streaming.h"
#include "World.h"


char (&DefaultPCSaveFileName)[260] = *(char(*)[260])*(uintptr*)0x8E28C0;
char (&ValidSaveName)[260] = *(char(*)[260])*(uintptr*)0x8E2CBC;
char (&LoadFileName)[256] = *(char(*)[256])*(uintptr*)0x9403C4;
wchar (&SlotFileName)[SLOT_COUNT][260] = *(wchar(*)[SLOT_COUNT][260])*(uintptr*)0x6F07C8;
wchar (&SlotSaveDate)[SLOT_COUNT][70] = *(wchar(*)[SLOT_COUNT][70])*(uintptr*)0x72B858;
int &CheckSum = *(int*)0x8E2BE0;
eLevelName &m_LevelToLoad = *(eLevelName*)0x8E29CC;
char SaveFileNameJustSaved[260];
int (&Slots)[SLOT_COUNT+1] = *(int(*)[SLOT_COUNT+1])*(uintptr*)0x72803C;
CDate &CompileDateAndTime = *(CDate*)0x72BCB8;

C_PcSave &PcSaveHelper = *(C_PcSave*)0x8E2C60;

WRAPPER bool GenericSave(int file) { EAXJMP(0x58F8D0); }
WRAPPER bool GenericLoad() { EAXJMP(0x590A00); }

bool
ReadInSizeofSaveFileBuffer(int32 &file, uint32 &size)
{
	file = CFileMgr::OpenFile(LoadFileName, "rb");
	if (file == 0) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_OPEN;
		return false;
	}
	CFileMgr::Read(file, (const char*)&size, 4);
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
	buf += 4;
	postsize = buf;
}

void
CopySizeAndPreparePointer(uint8 *&buf, uint8 *&postbuf, uint8 *&postbuf2, uint32 &unused, uint32 &size)
{
	*(uint32*)buf = size;
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
	char filename[100];

	int32 blocknum = 0;
	eLevelName level = LEVEL_NONE;
	CheckSum = 0;
	uint32 bytes_pocessed = 0;
	sprintf(filename, "%s%i%s", DefaultPCSaveFileName, slot + 1, ".b");
	int file = CFileMgr::OpenFile(filename, "rb");
	if (file == 0)
		return false;
	strcpy(name, filename);
	while (201729 - bytes_pocessed > 4 && blocknum < 40) {
		int32 blocksize;
		if (!ReadDataFromFile(file, (uint8*)&blocksize, 4)) {
			CloseFile(file);
			return false;
		}
		if (blocksize > align4bytes(sizeof(work_buff)))
			blocksize = sizeof(work_buff) - 4;
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
			bytes_pocessed++;
		}

		if (blocknum == 0)
			level = *(eLevelName*)&work_buff[4];
		blocknum++;
	}
	int32 _checkSum;
	if (ReadDataFromFile(file, (uint8*)&_checkSum, 4)) {
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
	ReadDataFromFile(file, buf, 999);
	if (CFileMgr::GetErrorReadWrite(file)) {
		PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_READ;
		if (!CloseFile(file))
			PcSaveHelper.nErrorCode = SAVESTATUS_ERR_LOAD_CLOSE;
		return false;
	} else {
		CGame::currLevel = *(eLevelName*)&buf[72];
		TheCamera.GetPosition() = *(CVector*)&buf[76];
		CStreaming::RemoveUnusedBigBuildings(*(eLevelName*)&buf[72]);
		CStreaming::RemoveUnusedBuildings(CGame::currLevel);
		CCollision::SortOutCollisionAfterLoad();
		CStreaming::RequestBigBuildings(CGame::currLevel);
		CStreaming::LoadAllRequestedModels(false);
		CStreaming::HaveAllBigBuildingsLoaded(CGame::currLevel);
		CGame::TidyUpMemory(true, false);

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

STARTPATCHES
	//InjectHook(0x58F8D0, GenericSave, PATCH_JUMP);
	//InjectHook(0x590A00, GenericLoad, PATCH_JUMP);
	InjectHook(0x591910, ReadInSizeofSaveFileBuffer, PATCH_JUMP);
	InjectHook(0x591990, ReadDataFromFile, PATCH_JUMP);
	InjectHook(0x591A00, CloseFile, PATCH_JUMP);
	InjectHook(0x591A20, DoGameSpecificStuffAfterSucessLoad, PATCH_JUMP);
	InjectHook(0x591A40, CheckSlotDataValid, PATCH_JUMP);
	InjectHook(0x591A80, MakeSpaceForSizeInBufferPointer, PATCH_JUMP);
	InjectHook(0x591AA0, CopySizeAndPreparePointer, PATCH_JUMP);
	InjectHook(0x591AE0, DoGameSpecificStuffBeforeSave, PATCH_JUMP);
	InjectHook(0x591B10, MakeValidSaveName, PATCH_JUMP);
	InjectHook(0x591B50, GetSavedGameDateAndTime, PATCH_JUMP);
	InjectHook(0x591B60, GetNameOfSavedGame, PATCH_JUMP);
	InjectHook(0x591B70, CheckDataNotCorrupt, PATCH_JUMP);
	InjectHook(0x591D60, RestoreForStartLoad, PATCH_JUMP);
	InjectHook(0x591E80, align4bytes, PATCH_JUMP);
ENDPATCHES