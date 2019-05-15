#include "common.h"
#include "patcher.h"
#include "References.h"

CReference *CReferences::aRefs = (CReference*)0x70BBE0; //[NUMREFERENCES];
CReference *&CReferences::pEmptyList = *(CReference**)0x8F1AF8;

void
CReferences::Init(void)
{
	int i;
	pEmptyList = &aRefs[0];
	for(i = 0; i < NUMREFERENCES; i++){
		aRefs[i].pentity = nil;
		aRefs[i].next = &aRefs[i+1];
	}
	aRefs[NUMREFERENCES-1].next = nil;
}

STARTPATCHES
	InjectHook(0x4A7350, CReferences::Init, PATCH_JUMP);
ENDPATCHES
