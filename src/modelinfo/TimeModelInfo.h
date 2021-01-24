#pragma once

#include "SimpleModelInfo.h"

class CTimeModelInfo : public CSimpleModelInfo
{
	int32 m_timeOn;
	int32 m_timeOff;
	int32 m_otherTimeModelID;

	static base::cRelocatableChunkClassInfo msClassInfo;
	static CTimeModelInfo msClassInstance;

public:
	CTimeModelInfo(void) : CSimpleModelInfo(MITYPE_TIME) { m_otherTimeModelID = -1; }

	virtual void RcWriteThis(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteEmpty(base::cRelocatableChunkWriter &writer);

	int32 GetTimeOn(void) { return m_timeOn; }
	int32 GetTimeOff(void) { return m_timeOff; }
	void SetTimes(int32 on, int32 off) { m_timeOn = on; m_timeOff = off; }
	int32 GetOtherTimeModel(void) { return m_otherTimeModelID; }
	void SetOtherTimeModel(int32 other) { m_otherTimeModelID = other; }
	CTimeModelInfo *FindOtherTimeModel(const char *name);
};
//static_assert(sizeof(CTimeModelInfo) == 0x58, "CTimeModelInfo: error");
