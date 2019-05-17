#pragma once

#include "Physical.h"

enum PedAction
{
	PED_PASSENGER = 44,
};

class CVehicle;

class CPed : public CPhysical
{
public:
	// 0x128
	uint8 stuff1[252];
	int32 m_nPedState;
	uint8 stuff2[196];
	CEntity *m_pCurrentPhysSurface;
	CVector m_vecOffsetFromPhysSurface;
	CEntity *m_pCurSurface;
	uint8 stuff3[16];
	CVehicle *m_pMyVehicle;
	bool bInVehicle;
	uint8 stuff4[23];
	int32 m_nPedType;

	uint8 stuff5[28];
	CVehicle *m_pCollidingVehicle;
	uint8 stuff6[496];

	bool IsPlayer(void) { return m_nPedType == 0 || m_nPedType== 1 || m_nPedType == 2 || m_nPedType == 3; }
};
static_assert(offsetof(CPed, m_nPedState) == 0x224, "CPed: error");
static_assert(offsetof(CPed, m_pCurSurface) == 0x2FC, "CPed: error");
static_assert(offsetof(CPed, m_pMyVehicle) == 0x310, "CPed: error");
static_assert(offsetof(CPed, m_nPedType) == 0x32C, "CPed: error");
static_assert(offsetof(CPed, m_pCollidingVehicle) == 0x34C, "CPed: error");
static_assert(sizeof(CPed) == 0x540, "CPed: error");
