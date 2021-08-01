#pragma once

#include "ClumpModelInfo.h"

class CMloModelInfo : public CClumpModelInfo
{
public:
	float drawDist;
	int firstInstance;
	int lastInstance;
public:
	CMloModelInfo(void) : CClumpModelInfo(MITYPE_MLO) {}
	void ConstructClump();
};