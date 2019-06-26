#include "common.h"
#include "patcher.h"
#include "Gangs.h"

CGangInfo(&CGangs::Gang)[TOTAL_GANGS] = *(CGangInfo(*)[9])*(uintptr*)0x6EDF78;

void CGangs::Initialize(void)
{
	Gang[GANG_MAFIA].m_nVehicleMI = MI_MAFIA;
	Gang[GANG_TRIAD].m_nVehicleMI = MI_BELLYUP;
	Gang[GANG_DIABLOS].m_nVehicleMI = MI_DIABLOS;
	Gang[GANG_YAKUZA].m_nVehicleMI = MI_YAKUZA;
	Gang[GANG_YARDIE].m_nVehicleMI = MI_YARDIE;
	Gang[GANG_COLUMB].m_nVehicleMI = MI_COLUMB;
	Gang[GANG_HOODS].m_nVehicleMI = MI_HOODS;
	Gang[GANG_7].m_nVehicleMI = -1;
	Gang[GANG_8].m_nVehicleMI = -1;
}

void CGangs::SetGangVehicleModel(int16 gang, int model)
{
	GetGangInfo(gang)->m_nVehicleMI = model;
}

void CGangs::SetGangWeapons(int16 gang, eWeaponType weapon1, eWeaponType weapon2)
{
	CGangInfo *gi = GetGangInfo(gang);
	gi->m_Weapon1 = weapon1;
	gi->m_Weapon2 = weapon2;
}

void CGangs::SetGangPedModelOverride(int16 gang, int8 ovrd)
{
	GetGangInfo(gang)->m_nPedModelOverride = ovrd;
}

int8 CGangs::GetGangPedModelOverride(int16 gang)
{
	return GetGangInfo(gang)->m_nPedModelOverride;
}

void CGangs::SaveAllGangData(uint8 *buffer, uint32 *size)
{
	tGangSaveData *data = (tGangSaveData*)buffer;
	data->tag[0] = 'G';
	data->tag[1] = 'N';
	data->tag[2] = 'G';
	data->tag[3] = '\0';
	data->size = *size = sizeof(tGangSaveData);
	for (int i = 0; i < TOTAL_GANGS; i++)
		data->gangs[i] = *GetGangInfo(i);
	buffer += sizeof(tGangSaveData);
}

void CGangs::LoadAllGangData(uint8 *buffer, uint32 size)
{
	Initialize();
	tGangSaveData* data = (tGangSaveData*)buffer;
	for (int i = 0; i < TOTAL_GANGS; i++)
		*GetGangInfo(i) = data->gangs[i];
}

STARTPATCHES
InjectHook(0x4C3FB0, CGangs::Initialize, PATCH_JUMP);
InjectHook(0x4C4010, CGangs::SetGangVehicleModel, PATCH_JUMP);
InjectHook(0x4C4030, CGangs::SetGangWeapons, PATCH_JUMP);
InjectHook(0x4C4050, CGangs::SetGangPedModelOverride, PATCH_JUMP);
InjectHook(0x4C4070, CGangs::GetGangPedModelOverride, PATCH_JUMP);
InjectHook(0x4C4080, CGangs::SaveAllGangData, PATCH_JUMP);
InjectHook(0x4C4100, CGangs::LoadAllGangData, PATCH_JUMP);
ENDPATCHES
