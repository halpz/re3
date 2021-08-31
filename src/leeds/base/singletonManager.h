#pragma once

#include "common.h"

namespace base
{

class cSingletonBase;

class cSingletonManager
{
	cSingletonBase* head;
	cSingletonBase* tail;

public:
	cSingletonManager() :
		head(nil),
		tail(nil)
	{}

	void Add(cSingletonBase*);
	void Purge();
	~cSingletonManager();
};

cSingletonManager& SingletonManager();

class cSingletonBase
{
	friend class cSingletonManager;

	cSingletonBase* next;

public:
	virtual ~cSingletonBase() {}
};

template<typename T>
class cSingleton : public cSingletonBase
{
	static T* mspInstance;
	static void CreateInstance()
	{
		mspInstance = new T();
		SingletonManager().Add(mspInstance);
	}

public:
	static T* Instance()
	{
		if (!mspInstance)
			CreateInstance();
		return mspInstance;
	}

	~cSingleton<T>()
	{
		mspInstance = nil;
	}
};

}