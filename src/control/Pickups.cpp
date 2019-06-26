#include "common.h"
#include "patcher.h"
#include "Pickups.h"

CPickup(&CPickups::aPickUps)[NUMPICKUPS] = *(CPickup(*)[NUMPICKUPS])*(uintptr*)0x878C98;

WRAPPER void CPickups::RenderPickUpText(void) { EAXJMP(0x432440); }

WRAPPER void CPacManPickups::Render(void) { EAXJMP(0x432F60); }
