#include "common.h"
#include "patcher.h"
#include "PlayerPed.h"
#include "PlayerInfo.h"
#include "Frontend.h"
#include "Vehicle.h"
#include "PlayerSkin.h"

WRAPPER void CPlayerInfo::MakePlayerSafe(bool) { EAXJMP(0x4A1400); }
WRAPPER void CPlayerInfo::AwardMoneyForExplosion(CVehicle *vehicle) { EAXJMP(0x4A15F0); }
WRAPPER void CPlayerInfo::Process(void) { EAXJMP(0x49FD30); }

void CPlayerInfo::SetPlayerSkin(char *skin)
{
	strncpy(m_aSkinName, skin, 32);
	LoadPlayerSkin();
}

CVector& CPlayerInfo::GetPos()
{
	if (m_pPed->bInVehicle && m_pPed->m_pMyVehicle)
		return m_pPed->m_pMyVehicle->GetPosition();
	return m_pPed->GetPosition();
}

void CPlayerInfo::LoadPlayerSkin()
{
	DeletePlayerSkin();

	m_pSkinTexture = CPlayerSkin::GetSkinTexture(m_aSkinName);
	if (!m_pSkinTexture)
		m_pSkinTexture = CPlayerSkin::GetSkinTexture(DEFAULT_SKIN_NAME);
}

void CPlayerInfo::DeletePlayerSkin()
{
	if (m_pSkinTexture) {
		RwTextureDestroy(m_pSkinTexture);
		m_pSkinTexture = NULL;
	}
}

STARTPATCHES
InjectHook(0x4A1700, &CPlayerInfo::LoadPlayerSkin, PATCH_JUMP);
InjectHook(0x4A1750, &CPlayerInfo::DeletePlayerSkin, PATCH_JUMP);
ENDPATCHES
