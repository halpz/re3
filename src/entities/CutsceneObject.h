#pragma once

#include "Object.h"

class CCutsceneObject : public CObject
{
public:
	CCutsceneObject(void);
};
static_assert(sizeof(CCutsceneObject) == 0x198, "CCutsceneObject: error");
