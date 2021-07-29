#include "common.h"
#include "relocatableChunk.h"

namespace base
{
	// TODO(LCS): add actual code (all of these are stubs)

	void* cRelocatableChunk::Load(void* data, bool bShrink) { return nil; }
	void* cRelocatableChunk::Load(const char* name, bool bShrink) { return nil; }
	void cRelocatableChunk::Fixup(const sChunkHeader& header, void* data) {}
	void cRelocatableChunk::Fixup(void* data) {}
	void* cRelocatableChunk::Shrink(const sChunkHeader& header, void* data) { return nil; }
	void* cRelocatableChunk::Shrink(void* data) { return nil; }

	cRelocatableChunkClassInfo::cRelocatableChunkClassInfo(const char* class_name, const void* pVmt, int size) {}

	cRelocatableChunkWriter::cRelocatableChunkWriter() {}
	cRelocatableChunkWriter::~cRelocatableChunkWriter() {}

	void cRelocatableChunkWriter::AddPatch(void* addr) {}
	void cRelocatableChunkWriter::AddPatchWithInfo(const char* str, int unk, void* addr) {}
	void cRelocatableChunkWriter::AllocateRaw(void* addr, uint32 size, uint32 align, bool a5, bool a6) {}

	void cRelocatableChunkWriter::Clear() {}
	void cRelocatableChunkWriter::Class(void* ptr, const cRelocatableChunkClassInfo& classInfo) {}
	void cRelocatableChunkWriter::DebugFileLine(void*) {}

	void cRelocatableChunkWriter::PatchFunc(void* ptr) {}

	bool cRelocatableChunkWriter::IsAllocated(void* addr) { return false; }

	void cRelocatableChunkWriter::Reserve(int, int) {}

	void cRelocatableChunkWriter::Save(const char* filename, uint32 a3, uint32 a4, bool a5) {}
	void cRelocatableChunkWriter::Save(void* file, uint32 a3, uint32 a4, bool a5, sChunkHeader* pHeader) {}

	void RegisterRelocatableChunkFunc(const void *func) {}
};