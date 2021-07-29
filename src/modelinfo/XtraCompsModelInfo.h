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

	virtual void RcWriteThis(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteEmpty(base::cRelocatableChunkWriter &writer);

	static base::cRelocatableChunkClassInfo msClassInfo;
	static CXtraCompsModelInfo msClassInstance;
};