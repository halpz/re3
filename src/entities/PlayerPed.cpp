#include "common.h"
#include "patcher.h"
#include "PlayerPed.h"

CPlayerPed::~CPlayerPed()
{
	delete m_pWanted;
}

WRAPPER void CPlayerPed::ReApplyMoveAnims(void) { EAXJMP(0x4F07C0); }

STARTPATCHES
	InjectHook(0x4EFB30, &CPlayerPed::dtor, PATCH_JUMP);
ENDPATCHES