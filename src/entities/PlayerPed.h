#pragma once

#include "Ped.h"

class CPlayerPed : public CPed
{
public:
	// All credits goes to DK22Pac
	// 0x53C
	int *m_pWanted;			//	CWanted *
	int *m_pArrestingCop;	//	CCopPed *m_pArrestingCop;
	float m_fMoveSpeed;
	float m_fCurrentStamina;
	float m_fMaxStamina;
	float m_fStaminaProgress;
	char m_bWeaponSlot;
	uint8 m_bSpeedTimerFlag;
	bool m_bShouldEvade;
	char field_1367;
	uint32 m_nSpeedTimer;
	uint32 m_nShotDelay;
	float field_1376;
	char field_1380;
	char field_1381;
	char field_1382;
	char field_1383;
	CEntity *m_pEvadingFrom;
	int m_nTargettableObjects[4];
	bool m_bAdrenalineActive;
	bool m_bHasLockOnTarget;
	char field_1406;
	char field_1407;
	uint32 m_bAdrenalineTime;
	bool m_bCanBeDamaged;
	char field_1413;
	char field_1414;
	char field_1415;
	CVector field_1416[6];
	int field_1488[6];
	float field_1512;
	float m_fFPSMoveHeading;
};
static_assert(sizeof(CPlayerPed) == 0x5F0, "CPlayerPed: error");
