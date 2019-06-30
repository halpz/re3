#pragma once

#include "BulletTrace.h"

class CBulletTraces
{
public:
	static CBulletTrace(&aTraces)[16];

	static void Init(void);
};
