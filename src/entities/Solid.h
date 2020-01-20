#pragma once

#include "Entity.h"

class CSolid : public CEntity
{
public:
	CSolid(void) {
		bRemoveFromWorld = true;
		bHasHitWall = false;
		bImBeingRendered = false;
		m_flagE2 = true;
	}
};