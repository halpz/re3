#include "common.h"
#include "patcher.h"
#include "PedType.h"

CPedType *(&CPedType::ms_apPedType)[NUM_PEDTYPES] = *(CPedType *(*)[NUM_PEDTYPES]) *(int*)0x941594;

WRAPPER void CPedType::LoadPedData(void) { EAXJMP(0x4EE8D0); }
WRAPPER int32 CPedType::FindPedType(char *type) { EAXJMP(0x4EEC10); }

void
CPedType::Initialise(void)
{
	int i;

	debug("Initialising CPedType...\n");
	for(i = 0; i < NUM_PEDTYPES; i++){
		ms_apPedType[i] = new CPedType;
		ms_apPedType[i]->m_flag = PED_FLAG_PLAYER1;
		ms_apPedType[i]->field_4 = 0;
		ms_apPedType[i]->field_8 = 0;
		// Why field_C not initialized?
		ms_apPedType[i]->field_10 = 0;
		ms_apPedType[i]->field_14 = 0;
		ms_apPedType[i]->m_threats = 0;
		ms_apPedType[i]->m_avoid = 0;
	}
	debug("Loading ped data...\n");
	LoadPedData();
	debug("CPedType ready\n");
}

STARTPATCHES
	InjectHook(0x4EE7E0, &CPedType::Initialise, PATCH_JUMP);
ENDPATCHES
