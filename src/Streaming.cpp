#include "common.h"
#include "patcher.h"
#include "Streaming.h"

bool &CStreaming::ms_disableStreaming = *(bool*)0x95CD6E;
int32 &CStreaming::ms_numModelsRequested = *(int32*)0x8E2C10;
CStreamingInfo *CStreaming::ms_aInfoForModel = (CStreamingInfo*)0x6C7088;

WRAPPER void CStreaming::RemoveModel(int32 id) { EAXJMP(0x408830); }
WRAPPER void CStreaming::RequestModel(int32 model, int32 flags) { EAXJMP(0x407EA0); }

WRAPPER void CStreaming::MakeSpaceFor(int32 size) { EAXJMP(0x409B70); }

void
CStreaming::ImGonnaUseStreamingMemory(void)
{
}

void
CStreaming::IHaveUsedStreamingMemory(void)
{
	UpdateMemoryUsed();
}

void
CStreaming::UpdateMemoryUsed(void)
{
}
