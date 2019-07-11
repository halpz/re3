#include "common.h"
#include "patcher.h"
#include "PlayerInfo.h"
#include "Frontend.h"

WRAPPER void CPlayerInfo::MakePlayerSafe(bool) { EAXJMP(0x4A1400); }
WRAPPER void CPlayerInfo::LoadPlayerSkin() { EAXJMP(0x4A1700); }
WRAPPER void CPlayerInfo::AwardMoneyForExplosion(CVehicle *vehicle) { EAXJMP(0x4A15F0); }

void CPlayerInfo::SetPlayerSkin(char *skin)
{
	strncpy(m_aSkinName, skin, 32);
	LoadPlayerSkin();
}
