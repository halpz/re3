#pragma once

#include "Physical.h"

class CPed;

class CVehicle : public CPhysical
{
public:
	// 0x128
	uint8 stuff1[116];
	uint8 m_currentColour1;
	uint8 m_currentColour2;
uint8 m_extra1;
uint8 m_extra2;
	int16 m_nAlarmState;
	CPed *pDriver;
	CPed *pPassengers[8];
	uint8 stuff2[24];
	CEntity *m_pCurSurface;
	uint8 stuff3[17];
	uint8 m_veh_flagA1 : 1;
	uint8 m_veh_flagA2 : 1;
	uint8 m_veh_flagA4 : 1;
	uint8 m_veh_flagA8 : 1;
	uint8 m_veh_flagA10 : 1;
	uint8 m_veh_flagA20 : 1;
	uint8 m_veh_flagA40 : 1;
	uint8 m_veh_flagA80 : 1;
	uint8 m_veh_flagB1 : 1;
	uint8 m_veh_flagB2 : 1;
	uint8 m_veh_flagB4 : 1;
	uint8 m_veh_flagB8 : 1;
	uint8 m_veh_flagB10 : 1;
	uint8 m_veh_flagB20 : 1;
	uint8 m_veh_flagB40 : 1;
	uint8 m_veh_flagB80 : 1;
	uint8 m_veh_flagC1 : 1;
	uint8 m_veh_flagC2 : 1;
	uint8 m_veh_flagC4 : 1;
	uint8 m_veh_flagC8 : 1;
	uint8 m_veh_flagC10 : 1;
	uint8 m_veh_flagC20 : 1;
	uint8 m_veh_flagC40 : 1;
	uint8 m_veh_flagC80 : 1;
	uint8 m_veh_flagD1 : 1;
	uint8 m_veh_flagD2 : 1;
	uint8 m_veh_flagD4 : 1;
	uint8 m_veh_flagD8 : 1;
	uint8 m_veh_flagD10 : 1;
	uint8 m_veh_flagD20 : 1;
	uint8 m_veh_flagD40 : 1;
	uint8 m_veh_flagD80 : 1;
	uint8 stuff4[139];
	int32 m_vehType;

	static void *operator new(size_t);
	static void operator delete(void*, size_t);

	bool IsCar(void) { return m_vehType == VEHICLE_TYPE_CAR; }
	bool IsBoat(void) { return m_vehType == VEHICLE_TYPE_BOAT; }
	bool IsTrain(void) { return m_vehType == VEHICLE_TYPE_TRAIN; }
	bool IsHeli(void) { return m_vehType == VEHICLE_TYPE_HELI; }
	bool IsPlane(void) { return m_vehType == VEHICLE_TYPE_PLANE; }
	
	static Bool &bWheelsOnlyCheat;
	static Bool &bAllDodosCheat;
	static Bool &bCheat3;
	static Bool &bCheat4;
	static Bool &bCheat5;
};
static_assert(sizeof(CVehicle) == 0x288, "CVehicle: error");
static_assert(offsetof(CVehicle, m_pCurSurface) == 0x1E0, "CVehicle: error");
