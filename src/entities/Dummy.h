#pragma once

#include "Lists.h"
#include "Entity.h"

class CDummy : public CEntity
{
public:
	CEntryInfoList m_entryInfoList;

	static void *operator new(size_t);
	static void operator delete(void*, size_t);
};
static_assert(sizeof(CDummy) == 0x68, "CDummy: error");
