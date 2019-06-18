#include "common.h"
#include "patcher.h"
#include "ObjectData.h"

WRAPPER void CObjectData::Initialise(const char *filename) { EAXJMP(0x4BC0E0); }
