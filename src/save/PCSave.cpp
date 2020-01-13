#include "common.h"
#include "patcher.h"
#include "FileMgr.h"
#include "GenericGameStorage.h"
#include "Messages.h"
#include "PCSave.h"
#include "Text.h"

const char* _psGetUserFilesFolder();

void
C_PcSave::SetSaveDirectory(const char *path)
{
	sprintf(DefaultPCSaveFileName, "%s\\%s", path, "GTA3sf");
}

bool
C_PcSave::DeleteSlot(int32 slot)
{
	char FileName[200];

	PcSaveHelper.nErrorCode = SAVESTATUS_SUCCESSFUL;
	sprintf(FileName, "%s%i.b", DefaultPCSaveFileName, slot + 1);
	DeleteFile(FileName);
	SlotSaveDate[slot][0] = '\0';
	return true;
}

bool
C_PcSave::SaveSlot(int32 slot)
{
	MakeValidSaveName(slot);
	PcSaveHelper.nErrorCode = SAVESTATUS_SUCCESSFUL;
	_psGetUserFilesFolder();
	int file = CFileMgr::OpenFile(ValidSaveName, "wb");
	if (file != 0) {
		DoGameSpecificStuffBeforeSave();
		if (GenericSave(file)) {
			if (CFileMgr::CloseFile(file) != 0)
				nErrorCode = SAVESTATUS_ERR_SAVE_CLOSE;
			return true;
		}

		return false;
	}
	PcSaveHelper.nErrorCode = SAVESTATUS_ERR_SAVE_CREATE;
	return false;
}

bool
C_PcSave::PcClassSaveRoutine(int32 file, uint8 *a3, uint32 a4)
{
	CFileMgr::Write(file, (const char*)&a4, 4);
	if (CFileMgr::GetErrorReadWrite(file)) {
		nErrorCode = SAVESTATUS_ERR_SAVE_WRITE;
		strncpy(SaveFileNameJustSaved, ValidSaveName, 259);
		return false;
	}

	CFileMgr::Write(file, (const char*)a3, align4bytes(a4));
	CheckSum += ((uint8*)&a4)[0];
	CheckSum += ((uint8*)&a4)[1];
	CheckSum += ((uint8*)&a4)[2];
	CheckSum += ((uint8*)&a4)[3];
	for (int i = 0; i < align4bytes(a4); i++) {
		CheckSum += *a3++;
	}
	if (CFileMgr::GetErrorReadWrite(file)) {
		nErrorCode = SAVESTATUS_ERR_SAVE_WRITE;
		strncpy(SaveFileNameJustSaved, ValidSaveName, 259);
		return false;
	}

	return true;
}

void
C_PcSave::PopulateSlotInfo()
{
	for (int i = 0; i < SLOT_COUNT; i++) {
		Slots[i + 1] = SLOT_EMPTY;
		SlotFileName[i][0] = '\0';
		SlotSaveDate[i][0] = '\0';
	}
	for (int i = 0; i < SLOT_COUNT; i++) {
		char savename[52];
		char v13[68];
		sprintf(savename, "%s%i%s", DefaultPCSaveFileName, i + 1, ".b");
		int file = CFileMgr::OpenFile(savename, "rb");
		if (file != 0) {
			CFileMgr::Read(file, v13, 68);
			if (strncmp(v13, TopLineEmptyFile, sizeof(TopLineEmptyFile)-1)) {
				Slots[i + 1] = SLOT_OK;
				memcpy(SlotFileName[i], &v13[4], 24 * sizeof(wchar));
				
				SlotFileName[i][24] = '\0';
			}
			CFileMgr::CloseFile(file);
		}
		if (Slots[i + 1] == SLOT_OK) {
			if (CheckDataNotCorrupt(i, savename)) {
				_SYSTEMTIME st = *(_SYSTEMTIME*)&v13[52];
				const char *month;
				switch (*(uint16*)&v13[54])
				{
				case 1: month = "JAN"; break;
				case 2: month = "FEB"; break;
				case 3: month = "MAR"; break;
				case 4: month = "APR"; break;
				case 5: month = "MAY"; break;
				case 6: month = "JUN"; break;
				case 7: month = "JUL"; break;
				case 8: month = "AUG"; break;
				case 9: month = "SEP"; break;
				case 10: month = "OCT"; break;
				case 11: month = "NOV"; break;
				case 12: month = "DEC"; break;
				default: assert(0);
				}
				char date[70];
				sprintf(date, "%02d %s %04d %02d:%02d:%02d", st.wDay, UnicodeToAsciiForSaveLoad(TheText.Get(month)), st.wYear, st.wHour, st.wMinute, st.wSecond);
				AsciiToUnicode(date, SlotSaveDate[i]);

			} else {
				CMessages::InsertNumberInString(TheText.Get("FEC_SLC"), i + 1, -1, -1, -1, -1, -1, SlotFileName[i]);
				Slots[i + 1] = SLOT_CORRUPTED;
			}
		}
	}
}

STARTPATCHES
	InjectHook(0x591EA0, C_PcSave::SetSaveDirectory, PATCH_JUMP);
	InjectHook(0x5922F0, &C_PcSave::DeleteSlot, PATCH_JUMP);
	InjectHook(0x591EC0, &C_PcSave::SaveSlot, PATCH_JUMP);
	InjectHook(0x591F80, &C_PcSave::PcClassSaveRoutine, PATCH_JUMP);
	InjectHook(0x592090, &C_PcSave::PopulateSlotInfo, PATCH_JUMP);
ENDPATCHES