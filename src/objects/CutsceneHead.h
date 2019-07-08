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
};
static_assert(sizeof(CCutsceneHead) == 0x19C, "CCutsceneHead: error");
