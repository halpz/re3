#include "common.h"
#include "patcher.h"
#include "BulletInfo.h"

WRAPPER void CBulletInfo::Initialise(void) { EAXJMP(0x558220); }
WRAPPER void CBulletInfo::Shutdown(void) { EAXJMP(0x558450); }
WRAPPER void CBulletInfo::AddBullet(CEntity *firingEntity, eWeaponType type, CVector pos, CVector velocity) { EAXJMP(0x558470); }
WRAPPER void CBulletInfo::Update(void) { EAXJMP(0x558550); }
WRAPPER bool CBulletInfo::TestForSniperBullet(float x1, float x2, float y1, float y2, float z1, float z2) { EAXJMP(0x558D40); }
