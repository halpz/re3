#include "common.h"

#include "VisibilityPlugins.h"
#include "ModelInfo.h"

base::cRelocatableChunkClassInfo CXtraCompsModelInfo::msClassInfo("CXtraCompsModelInfo", VTABLE_ADDR(&msClassInstance), sizeof(msClassInstance));
CXtraCompsModelInfo CXtraCompsModelInfo::msClassInstance;

void
CXtraCompsModelInfo::RcWriteThis(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), sizeof(void*), false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}

void
CXtraCompsModelInfo::RcWriteEmpty(base::cRelocatableChunkWriter &writer)
{
	writer.AllocateRaw(this, sizeof(*this), sizeof(void*), false, true);
	writer.Class(VTABLE_ADDR(this), msClassInfo);
}
