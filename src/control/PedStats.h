#pragma once

struct PedStat
{
	uint32 m_id;
	char m_name[24];
	int32 m_fleeDistance;
	int32 m_headingChangeRate;
	int8 m_fear;
	int8 m_temper;
	int8 m_lawfulness;
	int8 m_sexiness;
	int32 m_attackStrength;
	int32 m_defendWeakness;
	int16 m_flags;
};
static_assert(sizeof(PedStat) == 0x34, "PedStat: error");

class CPedStats
{
public:
	static int32 GetPedStatType(char *type);
};
