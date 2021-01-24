#include "common.h"

#include "General.h"
#include "ModelIndices.h"
#include "main.h"

CModelIndices *gpModelIndices;

/*#define X(name, var) int16 var = -1;
	MODELINDICES
#undef X*/

void
InitModelIndices(void)
{
/*#define X(name, var) var = -1;
	MODELINDICES
#undef X*/
	if (gMakeResources)
	{
		gpModelIndices = new CModelIndices;
		memset(gpModelIndices, -1, sizeof(CModelIndices));
	}
}

void
MatchModelString(const char *modelname, int16 id)
{
#define X(name, var) \
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
