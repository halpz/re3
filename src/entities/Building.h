#pragma once

#include "Entity.h"

class CBuilding : public CEntity
{
public:
	// TODO: ReplaceWithNewModel
	CBuilding(void) {
		m_type = ENTITY_TYPE_BUILDING;
		bUsesCollision = true;
	}
	static void *operator new(size_t);
	static void operator delete(void*, size_t);

	virtual bool GetIsATreadable(void) { return false; }
};
static_assert(sizeof(CBuilding) == 0x64, "CBuilding: error");
