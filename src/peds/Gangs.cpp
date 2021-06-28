#include "common.h"

#include "ModelIndices.h"
#include "Gangs.h"
#include "General.h"
#include "Streaming.h"
#include "Weapon.h"
#include "SaveBuf.h"

CGangInfo CGangs::Gang[NUM_GANGS];
bool CGangs::GangAttackWithCops[NUM_GANGS];

CGangInfo::CGangInfo() :
	m_nVehicleMI(-1),
	m_nPedModel1MI(-1),
	m_nPedModel2MI(-1),
	m_nPedModelOverride(-1),
	m_Weapon1(WEAPONTYPE_UNARMED),
	m_Weapon2(WEAPONTYPE_UNARMED)
{}

void CGangs::Initialise(void)
{
	SetGangPedModels(GANG_MAFIA, MI_GANG01, MI_GANG02);
	SetGangPedModels(GANG_TRIAD, MI_GANG03, MI_GANG04);
	SetGangPedModels(GANG_DIABLOS, MI_GANG05, MI_GANG06);
	SetGangPedModels(GANG_YAKUZA, MI_GANG07, MI_GANG08);
	SetGangPedModels(GANG_YARDIE, MI_GANG09, MI_GANG10);
	SetGangPedModels(GANG_COLUMB, MI_GANG11, MI_GANG12);
	SetGangPedModels(GANG_HOODS, MI_GANG13, MI_GANG14);
	SetGangPedModels(GANG_FORELLI, MI_GANG15, MI_GANG16);
	SetGangPedModels(GANG_SINDACCO, MI_GANG17, MI_GANG18);
	SetGangVehicleModel(GANG_MAFIA, MI_MAFIA);
	SetGangVehicleModel(GANG_TRIAD, MI_BELLYUP);
	SetGangVehicleModel(GANG_DIABLOS, MI_DIABLOS);
	SetGangVehicleModel(GANG_YAKUZA, MI_YAKUZA);
	SetGangVehicleModel(GANG_YARDIE, MI_YARDIE);
	SetGangVehicleModel(GANG_COLUMB, MI_COLUMB);
	SetGangVehicleModel(GANG_HOODS, MI_HOODS);
	SetGangVehicleModel(GANG_FORELLI, MI_FORELLI_CAR);
	SetGangVehicleModel(GANG_SINDACCO, MI_SINDACCO_CAR);
#ifdef FIX_BUGS
	for (int i = 0; i < NUM_GANGS; i++)
		SetGangPedModelOverride(i, -1);
#endif
}

bool CGangs::HaveGangModelsLoaded(int16 gang)
{
	CGangInfo* pGangInfo = GetGangInfo(gang);
	return CStreaming::HasModelLoaded(pGangInfo->m_nPedModel1MI) && CStreaming::HasModelLoaded(pGangInfo->m_nPedModel2MI);
}

void CGangs::SetGangPedModels(int16 gang, int32 mi1, int32 mi2)
{
	GetGangInfo(gang)->m_nPedModel1MI = mi1;
	GetGangInfo(gang)->m_nPedModel2MI = mi2;
}

void CGangs::SetWillAttackPlayerWithCops(ePedType type, bool will)
{
	if (type >= PEDTYPE_GANG1 && type <= PEDTYPE_GANG9)
		GangAttackWithCops[type - PEDTYPE_GANG1] = will;
}

bool CGangs::GetWillAttackPlayerWithCops(ePedType type)
{
	if (type >= PEDTYPE_GANG1 && type <= PEDTYPE_GANG9)
		return GangAttackWithCops[type - PEDTYPE_GANG1];
	return false;
}

int32 CGangs::ChooseGangPedModel(int16 gang)
{
	CGangInfo* pGangInfo = GetGangInfo(gang);
	if (pGangInfo->m_nPedModelOverride != -1 || CGeneral::GetRandomTrueFalse())
		return pGangInfo->m_nPedModel1MI;
	else
		return pGangInfo->m_nPedModel2MI;
}

void CGangs::SetGangVehicleModel(int16 gang, int32 model)
{
	GetGangInfo(gang)->m_nVehicleMI = model;
}

void CGangs::SetGangWeapons(int16 gang, int32 weapon1, int32 weapon2)
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

void CGangs::SaveAllGangData(uint8 *buf, uint32 *size)
{
INITSAVEBUF

	*size = SAVE_HEADER_SIZE + sizeof(Gang);
	WriteSaveHeader(buf, 'G','N','G','\0', *size - SAVE_HEADER_SIZE);
	for (int i = 0; i < NUM_GANGS; i++)
		WriteSaveBuf(buf, Gang[i]);

VALIDATESAVEBUF(*size);
}

void CGangs::LoadAllGangData(uint8 *buf, uint32 size)
{
	Initialise();

INITSAVEBUF
	CheckSaveHeader(buf, 'G','N','G','\0', size - SAVE_HEADER_SIZE);

	for (int i = 0; i < NUM_GANGS; i++)
		ReadSaveBuf(&Gang[i], buf);
VALIDATESAVEBUF(size);
}
