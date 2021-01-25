#include "common.h"

#include "Camera.h"
#include "ModelInfo.h"
#include "General.h"
#include "KeyGen.h"

base::cRelocatableChunkClassInfo CTimeModelInfo::msClassInfo("CTimeModelInfo", VTABLE_ADDR(&msClassInstance), sizeof(msClassInstance));
CTimeModelInfo CTimeModelInfo::msClassInstance;


CTimeModelInfo*
CTimeModelInfo::FindOtherTimeModel(const char *modelname)
{
	char name[40];
	char *p;
	int i;

	strcpy(name, modelname);
	// change _nt to _dy
	if(p = strstr(name, "_nt"))
		strncpy(p, "_dy", 4);
	// change _dy to _nt
	else if(p = strstr(name, "_dy"))
		strncpy(p, "_nt", 4);
	else
		return nil;

	uint32 nameKey = CKeyGen::GetUppercaseKey(name);

	for(i = 0; i < MODELINFOSIZE; i++){
		CBaseModelInfo *mi = CModelInfo::GetModelInfo(i);
		if (mi && mi->GetModelType() == MITYPE_TIME && nameKey == mi->GetNameHashKey()){
			m_otherTimeModelID = i;
			return (CTimeModelInfo*)mi;
		}
	}
	return nil;
}


void
CTimeModelInfo::RcWriteThis(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), sizeof(void*), false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}

void
CTimeModelInfo::RcWriteEmpty(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), sizeof(void*), false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}
