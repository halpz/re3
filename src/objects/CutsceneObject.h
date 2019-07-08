#pragma once

#include "Object.h"

class CCutsceneObject : public CObject
{
public:
	CCutsceneObject(void);

	void SetModelIndex(uint32 id);
	void ProcessControl(void);
	void PreRender(void);
	void Render(void);
	bool SetupLighting(void);
	void RemoveLighting(bool reset);
};
static_assert(sizeof(CCutsceneObject) == 0x198, "CCutsceneObject: error");
