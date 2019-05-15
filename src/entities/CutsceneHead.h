#pragma once

#include "CutsceneObject.h"

class CCutsceneHead : public CCutsceneObject
{
public:
	RwFrame *m_pHeadNode;
};
static_assert(sizeof(CCutsceneHead) == 0x19C, "CCutsceneHead: error");
