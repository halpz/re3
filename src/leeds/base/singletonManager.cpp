#include "common.h"

#include "singletonManager.h"

namespace base
{

cSingletonManager& SingletonManager()
{
	static cSingletonManager manager;
	return manager;
}

cSingletonManager::~cSingletonManager()
{
	Purge();
}

void cSingletonManager::Add(cSingletonBase* node)
{
	node->next = head;
	if (!head)
		tail = node;
	head = node;
}

void cSingletonManager::Purge()
{
	for (cSingletonBase* node = tail; node; node = tail) {
		tail = node->next;
		delete node;
	}
}


}