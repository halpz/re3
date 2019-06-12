#pragma once

#include "CutsceneObject.h"

class CCutsceneHead : public CCutsceneObject
{
public:
	RwFrame *m_pHeadNode;

	CCutsceneHead(CObject *obj);

	void CreateRwObject(void);
	void DeleteRwObject(void);
	void ProcessControl(void);
	void Render(void);

	void PlayAnimation(const char *animName);

	void CreateRwObject_(void) { CCutsceneHead::CreateRwObject(); }
	void DeleteRwObject_(void) { CCutsceneHead::DeleteRwObject(); }
	void ProcessControl_(void) { CCutsceneHead::ProcessControl(); }
	void Render_(void) { CCutsceneHead::Render(); }
};
static_assert(sizeof(CCutsceneHead) == 0x19C, "CCutsceneHead: error");
