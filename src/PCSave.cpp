#include "common.h"
#include "patcher.h"
#include "Frontend.h"
#include "PCSave.h"

WRAPPER void C_PcSave::SetSaveDirectory(const char *path) { EAXJMP(0x591EA0); }
WRAPPER wchar *GetNameOfSavedGame(int counter) { EAXJMP(0x591B60); }
WRAPPER wchar *GetSavedGameDateAndTime(int counter) { EAXJMP(0x591B50); }

int *Slots = (int*)0x728040;
int *SlotFileName = (int*)0x6F07C8;
int *SlotSaveDate = (int*)0x72B858;
