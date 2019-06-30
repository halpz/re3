#include "common.h"
#include "patcher.h"
#include "Pickups.h"

CPickup(&CPickups::aPickUps)[NUMPICKUPS] = *(CPickup(*)[NUMPICKUPS])*(uintptr*)0x878C98;

WRAPPER void CPickups::RenderPickUpText(void) { EAXJMP(0x432440); }
WRAPPER void CPickups::DoCollectableEffects(CEntity *ent) { EAXJMP(0x431C30); }
WRAPPER void CPickups::DoMoneyEffects(CEntity *ent) { EAXJMP(0x431F40); }
WRAPPER void CPickups::DoMineEffects(CEntity *ent) { EAXJMP(0x4321C0); }
WRAPPER void CPickups::DoPickUpEffects(CEntity *ent) { EAXJMP(0x431520); }

WRAPPER void CPacManPickups::Render(void) { EAXJMP(0x432F60); }
