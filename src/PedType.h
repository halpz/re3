#pragma once

#include "common.h"
#include "templates.h"
#include "Lists.h"

class CPedType {
public:
	union tPedTypeFlags
	{
		uint32 IntValue;
		struct
		{
			uint8 bPlayer1 : 1;
			uint8 bPlayer2 : 1;
			uint8 bPlayer3 : 1;
			uint8 bPlayer4 : 1;
			uint8 bCivmale : 1;
			uint8 bCivfemale : 1;
			uint8 bCop : 1;
			uint8 bGang1 : 1;

			uint8 bGang2 : 1;
			uint8 bGang3 : 1;
			uint8 bGang4 : 1;
			uint8 bGang5 : 1;
			uint8 bGang6 : 1;
			uint8 bGang7 : 1;
			uint8 bGang8 : 1;
			uint8 bGang9 : 1;

			uint8 bEmergency : 1;
			uint8 bProstitute : 1;
			uint8 bCriminal : 1;
			uint8 bSpecial : 1;
			uint8 bGun : 1;
			uint8 bCop_car : 1;
			uint8 bFast_car : 1;
			uint8 bExplosion : 1;

			uint8 bFireman : 1;
			uint8 bDeadpeds : 1;
		};
	};

	tPedTypeFlags m_Type;
	float field_4;
	float field_8;
	float field_C;
	float field_10;
	float field_14;
	tPedTypeFlags m_Threat;
	tPedTypeFlags m_Avoid;

	static CPedType* (&ms_apPedType)[23];

	static void Initialise();
	static void LoadPedData();
};

static_assert(sizeof(CPedType) == 0x20, "CPedType: error");