#pragma once

#include "ClumpModelInfo.h"

class CXtraCompsModelInfo : public CClumpModelInfo
{
	int field_34;
public:
	CXtraCompsModelInfo(void) : CClumpModelInfo(MITYPE_XTRACOMPS) { field_34 = 0; }
	void Shutdown(void) {};
	RwObject *CreateInstance(void) { return nil; }
	void SetClump(RpClump*) {};
};