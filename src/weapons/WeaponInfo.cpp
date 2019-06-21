#include "common.h"
#include "patcher.h"
#include "WeaponInfo.h"

CWeaponInfo (&CWeaponInfo::ms_apWeaponInfos)[14] = * (CWeaponInfo(*)[14]) * (uintptr*)0x6503EC;

CWeaponInfo*
CWeaponInfo::GetWeaponInfo(eWeaponType weaponType) {
	return &CWeaponInfo::ms_apWeaponInfos[weaponType];
}

STARTPATCHES
	InjectHook(0x564FD0, &CWeaponInfo::GetWeaponInfo, PATCH_JUMP);
ENDPATCHES