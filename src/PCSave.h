#pragma once

class C_PcSave
{
public:
	static void SetSaveDirectory(const char *path);
};

extern wchar *GetNameOfSavedGame(int counter);
extern wchar *GetSavedGameDateAndTime(int counter);

extern int *Slots;
extern int *SlotFileName;
extern int *SlotSaveDate;
