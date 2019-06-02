#include "common.h"
#include "patcher.h"
#include "Frontend.h"
#include "PCSave.h"

WRAPPER void C_PcSave::SetSaveDirectory(const Char *path) { EAXJMP(0x591EA0); }

