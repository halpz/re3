#include "common.h"
#include "patcher.h"
#include "Skidmarks.h"

WRAPPER void CSkidmarks::Render(void) { EAXJMP(0x5182E0); }
