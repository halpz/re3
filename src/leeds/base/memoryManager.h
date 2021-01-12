#pragma once

namespace base
{
	class cMemoryManager
	{
	public:
		cMemoryManager();
		void* Allocate(uint32 size);
		void* AllocateAligned(uint32 size);
		void* Realloc(void* buf, uint32 newSize, bool unk);
		void Free(void* buf);
		bool IsFree(void* buf);
	};

	class cMainMemoryManager : public cMemoryManager
	{
		static cMainMemoryManager* m_pInstance;
		static void Init(void*, uint32);

	public:
		cMainMemoryManager();
		static cMainMemoryManager *Instance()
		{
			static cMainMemoryManager instance;
			return &instance;
		}
	};

	class cMemoryBlock
	{
		// TODO
	};
}

void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* buf) noexcept;
void operator delete[](void* buf) noexcept;