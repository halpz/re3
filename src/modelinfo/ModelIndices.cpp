#include "common.h"
#include "patcher.h"
#include "ModelIndices.h"

#define X(name, var, addr) int16 &var = *(int16*)addr;
	MODELINDICES
#undef X

void
InitModelIndices(void)
{
#define X(name, var, addr) var = -1;
	MODELINDICES
#undef X
}

void
MatchModelString(const char *modelname, int16 id)
{
#define X(name, var, addr) \
	if(strcmp(name, modelname) == 0){ \
		var = id; \
		return; \
	}
	MODELINDICES
#undef X
}

void
TestModelIndices(void)
{
	;
}

STARTPATCHES
	InjectHook(0x48EB60, InitModelIndices, PATCH_JUMP);
	InjectHook(0x48F030, MatchModelString, PATCH_JUMP);
ENDPATCHES
