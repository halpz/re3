#include "common.h"
#include "memoryManager.h"

namespace base
{
	cMemoryManager::cMemoryManager()
	{

	}

	void* cMemoryManager::Allocate(uint32 size)
	{
		void* buf = malloc(size);
		memset(buf, 0, size);
		return buf;
	}

	void* cMemoryManager::AllocateAligned(uint32 size)
	{
		void* buf = malloc(size);
		memset(buf, 0, size);
		return buf;
	}

	void* cMemoryManager::Realloc(void* buf, uint32 newSize, bool unk)
	{
		return realloc(buf, newSize);
	}

	void cMemoryManager::Free(void* buf)
	{
		if (buf)
			free(buf);
	}

	bool cMemoryManager::IsFree(void* buf)
	{
		return buf == nil;
	}


	cMainMemoryManager* cMainMemoryManager::m_pInstance = nil;

	cMainMemoryManager::cMainMemoryManager()
	{
		assert(m_pInstance == nil);
		m_pInstance = this;
		Init(nil, 0);
	}

	void cMainMemoryManager::Init(void*, uint32)
	{

	}
};

void* operator new(size_t size)
{
	return base::cMainMemoryManager::Instance()->Allocate(size);
}

void* operator new[](size_t size)
{
	return base::cMainMemoryManager::Instance()->Allocate(size);
}

void operator delete(void* buf) noexcept
{
	base::cMainMemoryManager::Instance()->Free(buf);
}

void operator delete[](void* buf) noexcept
{
	base::cMainMemoryManager::Instance()->Free(buf);
}