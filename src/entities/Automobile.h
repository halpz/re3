#pragma once

#include "DamageManager.h"
#include "Door.h"
#include "RwHelper.h"
#include "Vehicle.h"

class CAutomobile : public CVehicle
{
public:
	// 0x288
	CDamageManager m_DamageManager;
	CDoor m_aDoors[6];
	RwFrame *m_apModelNodes[20];
	uint8 stuff1[160];
	float m_afWheelSuspDist[4];
	uint8 stuff2[44];
	float m_afWheelRotation[4];
	uint8 stuff3[200];
	float m_fCarGunLR;
	uint8 stuff4[36];

	void SetDoorDamage(int32, uint32, bool); /* TODO: eDoors */
};
static_assert(sizeof(CAutomobile) == 0x5A8, "CAutomobile: error");
static_assert(offsetof(CAutomobile, m_afWheelSuspDist) == 0x46C, "CAutomobile: error");
