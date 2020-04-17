#include "common.h"

#include "General.h"
#include "ModelIndices.h"

#define X(name, var, addr) int16 var;
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
	if(!CGeneral::faststrcmp(name, modelname)){ \
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
