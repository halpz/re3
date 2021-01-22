#pragma once

#include "memoryManager.h"

class cSmallHeap : public base::cMemoryManager
{
	bool bLocked;
	bool bUnk;
public:
	cSmallHeap();
	void Lock();
	void Unlock();

	bool IsLocked() const { return bLocked; }

	static cSmallHeap msInstance;
};