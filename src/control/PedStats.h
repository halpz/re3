#pragma once

enum ePedStats
{
	PEDSTAT_PLAYER,
	PEDSTAT_COP,
	PEDSTAT_MEDIC,
	PEDSTAT_FIREMAN,
	PEDSTAT_GANG1,
	PEDSTAT_GANG2,
	PEDSTAT_GANG3,
	PEDSTAT_GANG4,
	PEDSTAT_GANG5,
	PEDSTAT_GANG6,
	PEDSTAT_GANG7,
	PEDSTAT_STREET_GUY,
	PEDSTAT_SUIT_GUY,
	PEDSTAT_SENSIBLE_GUY,
	PEDSTAT_GEEK_GUY,
	PEDSTAT_OLD_GUY,
	PEDSTAT_TOUGH_GUY,
	PEDSTAT_STREET_GIRL,
	PEDSTAT_SUIT_GIRL,
	PEDSTAT_SENSIBLE_GIRL,
	PEDSTAT_GEEK_GIRL,
	PEDSTAT_OLD_GIRL,
	PEDSTAT_TOUGH_GIRL,
	PEDSTAT_TRAMP_MALE,
	PEDSTAT_TRAMP_FEMALE,
	PEDSTAT_TOURIST,
	PEDSTAT_PROSTITUTE,
	PEDSTAT_CRIMINAL,
	PEDSTAT_BUSKER,
	PEDSTAT_TAXIDRIVER,
	PEDSTAT_PSYCHO,
	PEDSTAT_STEWARD,
	PEDSTAT_SPORTSFAN,
	PEDSTAT_SHOPPER,
	PEDSTAT_OLDSHOPPER,

	NUM_PEDSTATS
};

// flags
enum
{
	STAT_PUNCH_ONLY = 1,
	STAT_CAN_KNEE_HEAD = 2,
	STAT_CAN_KICK = 4,
	STAT_CAN_ROUNDHOUSE = 8,
	STAT_NO_DIVE = 0x10,
	STAT_ONE_HIT_KNOCKDOWN = 0x20,
	STAT_SHOPPING_BAGS = 0x40,
	STAT_GUN_PANIC = 0x80
};

class CPedStats
{
	static CPedStats *(&ms_apPedStats)[NUM_PEDSTATS];

public:
	ePedStats m_type;
	char m_name[24];
	float m_fleeDistance;
	float m_headingChangeRate;
	int8 m_fear;
	int8 m_temper;
	int8 m_lawfulness;
	int8 m_sexiness;
	float m_attackStrength;
	float m_defendWeakness;
	int16 m_flags;

	static void Initialise(void);
	static void Shutdown(void);
	static void LoadPedStats(void);
	static int32 GetPedStatType(char *name);
};
static_assert(sizeof(CPedStats) == 0x34, "CPedStats: error");
