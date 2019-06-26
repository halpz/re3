#pragma once

#include "common.h"
#include "Weapon.h"
#include "ModelIndices.h"

struct CGangInfo
{
	int32 m_nVehicleMI;
	int8 m_nPedModelOverride;
	int8 field_5;
	int16 field_6;
	eWeaponType m_Weapon1;
	eWeaponType m_Weapon2;

	CGangInfo() :
		m_nVehicleMI(MI_BUS),
		m_nPedModelOverride(-1),
		m_Weapon1(WEAPONTYPE_UNARMED),
		m_Weapon2(WEAPONTYPE_UNARMED)
	{}
};

static_assert(sizeof(CGangInfo) == 0x10, "CGangInfo: error");

class CGangs
{
public:
	enum {
		GANG_MAFIA = 0,
		GANG_TRIAD,
		GANG_DIABLOS,
		GANG_YAKUZA,
		GANG_YARDIE,
		GANG_COLUMB,
		GANG_HOODS,
		GANG_7,
		GANG_8,
		TOTAL_GANGS
	};
	static void Initialize(void);
	static void SetGangVehicleModel(int16, int);
	static void SetGangWeapons(int16, eWeaponType, eWeaponType);
	static void SetGangPedModelOverride(int16, int8);
	static int8 GetGangPedModelOverride(int16);
	static void SaveAllGangData(uint8 *, uint32 *);
	static void LoadAllGangData(uint8 *, uint32);

private:
	static CGangInfo* GetGangInfo(int16 gang) { return &Gang[gang]; }

	static CGangInfo(&Gang)[TOTAL_GANGS];
};

struct tGangSaveData
{
	char tag[4];
	int32 size;
	CGangInfo gangs[CGangs::TOTAL_GANGS];
};

static_assert(sizeof(tGangSaveData) == 0x98, "tGangSaveData: error");
