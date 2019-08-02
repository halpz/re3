#include "common.h"
#include "patcher.h"
#include "Pickups.h"

CPickup(&CPickups::aPickUps)[NUMPICKUPS] = *(CPickup(*)[NUMPICKUPS])*(uintptr*)0x878C98;

// 20 ?! Some Miami leftover? (Originally at 0x5ED8D4)
uint16 CPickups::ms_maxAmmosForWeapons[20] = { 0, 1, 45, 125, 25, 150, 300, 25, 5, 250, 5, 5, 0, 500, 0, 100, 0, 0, 0, 0 };

WRAPPER void CPickups::RenderPickUpText(void) { EAXJMP(0x432440); }
WRAPPER void CPickups::DoCollectableEffects(CEntity *ent) { EAXJMP(0x431C30); }
WRAPPER void CPickups::DoMoneyEffects(CEntity *ent) { EAXJMP(0x431F40); }
WRAPPER void CPickups::DoMineEffects(CEntity *ent) { EAXJMP(0x4321C0); }
WRAPPER void CPickups::DoPickUpEffects(CEntity *ent) { EAXJMP(0x431520); }
WRAPPER void CPickups::RemoveAllFloatingPickups() { EAXJMP(0x430800); }
WRAPPER int32 CPickups::GenerateNewOne(CVector, uint32, uint8, uint32) { EAXJMP(0x4304B0); }
WRAPPER int32 CPickups::GenerateNewOne_WeaponType(CVector, eWeaponType, uint8, uint32) { EAXJMP(0x430660); }

WRAPPER void CPacManPickups::Render(void) { EAXJMP(0x432F60); }
