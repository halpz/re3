#include "common.h"
#include "patcher.h"
#include "PointLights.h"

int16 &CPointLights::NumLights = *(int16*)0x95CC3E;

WRAPPER void CPointLights::RenderFogEffect(void) { EAXJMP(0x510C30); }

void
CPointLights::InitPerFrame(void)
{
	NumLights = 0;
}
