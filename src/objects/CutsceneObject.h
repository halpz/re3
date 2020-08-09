#pragma once

#include "Object.h"

class CCutsceneShadow;

class CCutsceneObject : public CObject
{
public:
	CCutsceneShadow *m_pShadow;
	void     *m_pAttachTo;
	CObject  *m_pAttachmentObject;
  
	CCutsceneObject(void);
	~CCutsceneObject(void);

	void SetModelIndex(uint32 id);
	void CreateShadow(void);
	void ProcessControl(void);
	void PreRender(void);
	void Render(void);
	bool SetupLighting(void);
	void RemoveLighting(bool reset);
};
