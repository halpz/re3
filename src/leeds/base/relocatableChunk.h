#pragma once

namespace base
{
	// TODO(LCS): add actual struct fields

	struct sChunkHeader;
	struct sDataBlock;
	struct sFileLine;

	class cRelocatableChunk
	{
	public:
		void* Load(void* data, bool bShrink);
		void* Load(const char* name, bool bShrink);
		void Fixup(const sChunkHeader& header, void* data);
		void Fixup(void* data);
		void* Shrink(const sChunkHeader& header, void* data);
		void* Shrink(void* data);
	};

#define VTABLE_ADDR(obj) ((void*)obj)	// TODO: make this portable

	class cRelocatableChunkClassInfo
	{
	public:
		cRelocatableChunkClassInfo(const char* class_name, const void* pVmt, int size);
	};

	class cRelocatableChunkWriter
	{
	public:
		cRelocatableChunkWriter();
		~cRelocatableChunkWriter();

		void AddPatch(void* addr);
		void AddPatchWithInfo(const char* str, int unk, void* addr);
		void AllocateRaw(void* addr, uint32 size, uint32 align, bool a5 = false, bool a6 = false);

		void Clear();
		void Class(void* ptr, const cRelocatableChunkClassInfo& classInfo);
		void DebugFileLine(void*);

		void PatchFunc(void* ptr);

		bool IsAllocated(void* addr);

		void Reserve(int, int);

		void Save(const char* filename, uint32 a3, uint32 a4, bool a5);
		void Save(void* file, uint32 a3, uint32 a4, bool a5, sChunkHeader* pHeader);
	};

	void RegisterRelocatableChunkFunc(const void *func);
};