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


	void SetModelIndex_(uint32 id) { CCutsceneObject::SetModelIndex(id); }
	void ProcessControl_(void) { CCutsceneObject::ProcessControl(); }
	void PreRender_(void) { CCutsceneObject::PreRender(); }
	void Render_(void) { CCutsceneObject::Render(); }
	bool SetupLighting_(void) { return CCutsceneObject::SetupLighting(); }
	void RemoveLighting_(bool reset) { CCutsceneObject::RemoveLighting(reset); }
};
static_assert(sizeof(CCutsceneObject) == 0x198, "CCutsceneObject: error");
