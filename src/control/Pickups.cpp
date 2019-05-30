#include "common.h"
#include "patcher.h"
#include "Pickups.h"

WRAPPER void CPickups::RenderPickUpText(void) { EAXJMP(0x432440); }

WRAPPER void CPacManPickups::Render(void) { EAXJMP(0x432F60); }
