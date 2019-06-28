#include "common.h"
#include "patcher.h"
#include "ModelIndices.h"
#include "Gangs.h"

CGangInfo(&CGangs::Gang)[NUM_GANGS] = *(CGangInfo(*)[9])*(uintptr*)0x6EDF78;

CGangInfo::CGangInfo() :
	m_nVehicleMI(MI_BUS),
	m_nPedModelOverride(-1),
	m_Weapon1(WEAPONTYPE_UNARMED),
	m_Weapon2(WEAPONTYPE_UNARMED)
{}

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
	buffer[0] = 'G';
	buffer[1] = 'N';
	buffer[2] = 'G';
	buffer[3] = '\0';
	*size = 8 + NUM_GANGS * 16;
	*(uint32*)(buffer + 4) = *size - 8;
	buffer += 8;
	for (int i = 0; i < NUM_GANGS; i++) {
		*(uint32*)(buffer) = GetGangInfo(i)->m_nVehicleMI;
		*(int8*)(buffer + 4) = GetGangInfo(i)->m_nPedModelOverride;
		*(int8*)(buffer + 5) = GetGangInfo(i)->field_5;
		*(int16*)(buffer + 6) = GetGangInfo(i)->field_6;
		*(eWeaponType*)(buffer + 8) = GetGangInfo(i)->m_Weapon1;
		*(eWeaponType*)(buffer + 12) = GetGangInfo(i)->m_Weapon2;
		buffer += 16;
	}
}

void CGangs::LoadAllGangData(uint8 *buffer, uint32 size)
{
	Initialize();
	assert(size == 8 + NUM_GANGS * 16);
	assert(buffer[0] == 'G');
	assert(buffer[1] == 'N');
	assert(buffer[2] == 'G');
	assert(buffer[3] == '\0');
	assert(*(uint32*)(buffer + 4) == size - 8);
	buffer += 8;
	for (int i = 0; i < NUM_GANGS; i++){
		GetGangInfo(i)->m_nVehicleMI = *(uint32*)(buffer);
		GetGangInfo(i)->m_nPedModelOverride = *(int8*)(buffer + 4);
		GetGangInfo(i)->field_5 = *(int8*)(buffer + 5);
		GetGangInfo(i)->field_6 = *(int16*)(buffer + 6);
		GetGangInfo(i)->m_Weapon1 = *(eWeaponType*)(buffer + 8);
		GetGangInfo(i)->m_Weapon2 = *(eWeaponType*)(buffer + 12);
		buffer += 16;
	}
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
