#include "AudioManager.h"
#include "DMAudio.h"
#include "Ped.h"
#include "PlayerPed.h"
#include "World.h"
#include "common.h"
#include "patcher.h"

cAudioManager &AudioManager = *(cAudioManager *)0x880FC0;

void
cAudioManager::PlayerJustLeftCar(void)
{
	// UNUSED: This is a perfectly empty function.
}

void
cAudioManager::GetPhrase(uint32 *phrase, uint32 *prevPhrase, uint32 sample,
                         uint32 maxOffset)
{
	*phrase = sample + m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] %
	                       maxOffset;

	// check if the same sfx like last time, if yes, then try use next one,
	// if exceeded range, then choose first available sample
	if(*phrase == *prevPhrase && ++*phrase >= sample + maxOffset)
		*phrase = sample;
	*prevPhrase = *phrase;
}

uint32
cAudioManager::GetPlayerTalkSfx(int16 sound)
{
	uint32 sfx;
	static bool &bUsedPlayerTalkSfx = *(bool *)0x6508f4;
	static uint32 &lastPlayerTalkSfx = *(uint32 *)0x6508f0;

	if(!bUsedPlayerTalkSfx) {
		bUsedPlayerTalkSfx = true;
		lastPlayerTalkSfx = NO_SAMPLE;
	}
	switch(sound) {
	case SOUND_PED_DAMAGE:
		GetPhrase(&sfx, &lastPlayerTalkSfx,
		          AUDIO_SAMPLE_PED_DAMAGE_REACTION_1, 11u);
		break;

	case SOUND_PED_HIT:
		GetPhrase(&sfx, &lastPlayerTalkSfx,
		          AUDIO_SAMPLE_PED_HIT_REACTION_1, 10u);
		break;

	case SOUND_PED_LAND:
		GetPhrase(&sfx, &lastPlayerTalkSfx,
		          AUDIO_SAMPLE_PED_FALL_REACTION_1, 6u);
		break;

	default: sfx = NO_SAMPLE; break;
	}
	return sfx;
}

uint32
cAudioManager::GetCopTalkSfx(int16 sample)
{
	uint32 sfx;
	PedState pedState;
	static bool &bUsedCopTalkSfx = *(bool *)0x6508FC;
	static uint32 &lastCopTalkSfx = *(uint32 *)0x6508F8;

	if(!bUsedCopTalkSfx) {
		bUsedCopTalkSfx = 1;
		lastCopTalkSfx = NO_SAMPLE;
	}

	if(sample == SOUND_PED_ARREST_COP) {
		GetPhrase(&sfx, &lastCopTalkSfx,
		          AUDIO_SAMPLE_POLICE_COP_1_ARREST_1, 6u);
	} else {
		if(sample != SOUND_PED_PURSUIT_COP) {
			return cAudioManager::GetGenericMaleTalkSfx(sample);
		}

		pedState = FindPlayerPed()->m_nPedState;
		if(pedState == PED_ARRESTED || pedState == PED_DEAD ||
		   pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(&sfx, &lastCopTalkSfx,
		          AUDIO_SAMPLE_POLICE_COP_1_PURSUIT_1, 7u);
	}

	return 13 * (m_sQueueSample.m_nEntityIndex % 5) + sfx;
}

uint32
cAudioManager::GetSwatTalkSfx(int16 sample)
{
	uint32 sfx;
	PedState pedState;
	static bool &bUsedSwatTalkSfx = *(bool *)0x650904;
	static uint32 &lastSwatTalkSfx = *(uint32 *)0x650900;

	if(!bUsedSwatTalkSfx) {
		bUsedSwatTalkSfx = 1;
		lastSwatTalkSfx = NO_SAMPLE;
	}

	if(sample == SOUND_PED_ARREST_SWAT) {
		GetPhrase(&sfx, &lastSwatTalkSfx,
		          AUDIO_SAMPLE_POLICE_SWAT_1_PURSUIT_ARREST_1, 6u);
	} else {
		if(sample != SOUND_PED_PURSUIT_SWAT) {
			return cAudioManager::GetGenericMaleTalkSfx(sample);
		}

		pedState = FindPlayerPed()->m_nPedState;
		if(pedState == PED_ARRESTED || pedState == PED_DEAD ||
		   pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(&sfx, &lastSwatTalkSfx,
		          AUDIO_SAMPLE_POLICE_SWAT_1_PURSUIT_ARREST_1, 6u);
	}

	return 6 * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetFBITalkSfx(int16 sample)
{
	uint32 sfx;
	PedState pedState;
	static bool &bUsedFBITalkSfx = *(bool *)0x65090C;
	static uint32 &lastFBITalkSfx = *(uint32 *)0x650908;

	if(!bUsedFBITalkSfx) {
		bUsedFBITalkSfx = 1;
		lastFBITalkSfx = NO_SAMPLE;
	}

	if(sample == SOUND_PED_ARREST_FBI) {
		GetPhrase(&sfx, &lastFBITalkSfx,
		          AUDIO_SAMPLE_POLICE_FBI_1_PURSUIT_ARREST_1, 6u);
	} else {
		if(sample != SOUND_PED_PURSUIT_FBI) {
			return cAudioManager::GetGenericMaleTalkSfx(sample);
		}

		pedState = FindPlayerPed()->m_nPedState;
		if(pedState == PED_ARRESTED || pedState == PED_DEAD ||
		   pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(&sfx, &lastFBITalkSfx,
		          AUDIO_SAMPLE_POLICE_FBI_1_PURSUIT_ARREST_1, 6u);
	}

	return 6 * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetArmyTalkSfx(int16 sample)
{
	uint32 sfx;
	PedState pedState;
	static bool &bUsedArmyTalkSfx = *(bool *)0x650914;
	static uint32 &lastArmyTalkSfx = *(uint32 *)0x650910;

	if(!bUsedArmyTalkSfx) {
		bUsedArmyTalkSfx = 1;
		lastArmyTalkSfx = NO_SAMPLE;
	}

	if(sample != SOUND_PED_PURSUIT_ARMY) {
		return cAudioManager::GetGenericMaleTalkSfx(sample);
	}

	pedState = FindPlayerPed()->m_nPedState;
	if(pedState == PED_ARRESTED || pedState == PED_DEAD ||
	   pedState == PED_DIE)
		return NO_SAMPLE;
	GetPhrase(&sfx, &lastArmyTalkSfx, AUDIO_SAMPLE_POLICE_ARMY_1_PURSUIT_1,
	          15u);

	return 15 * (m_sQueueSample.m_nEntityIndex % 1) + sfx;
}

uint32
cAudioManager::GetMedicTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedMedicTalkSfx = *(bool *)0x65091C;
	static uint32 &lastMedicTalkSfx = *(uint32 *)0x650918;

	if(!bUsedMedicTalkSfx) {
		bUsedMedicTalkSfx = true;
		lastMedicTalkSfx = NO_SAMPLE;
	}
	switch(sample) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastMedicTalkSfx,
		          AUDIO_SAMPLE_PED_MEDIC_1_HANDS_COWER_1, 5u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastMedicTalkSfx,
		          AUDIO_SAMPLE_PED_MEDIC_1_CAR_JACKED_1, 5u);
		break;
	case SOUND_PED_HEALING:
		GetPhrase(&sfx, &lastMedicTalkSfx,
		          AUDIO_SAMPLE_PED_MEDIC_1_HEALING_1, 12u);
		break;
	case SOUND_PED_LEAVE_VEHICLE:
		GetPhrase(&sfx, &lastMedicTalkSfx,
		          AUDIO_SAMPLE_PED_MEDIC_1_LEAVE_VEHICLE_1, 9u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastMedicTalkSfx,
		          AUDIO_SAMPLE_PED_MEDIC_1_FLEE_RUN_1, 6u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return 37 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetFiremanTalkSfx(int16 sample)
{
	return cAudioManager::GetGenericMaleTalkSfx(sample);
}

uint32
cAudioManager::GetNormalMaleTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedNormalMaleTalkSfx = *(bool *)0x650B04;
	static uint32 &lastNormalMaleTalkSfx = *(uint32 *)0x650B00;

	if(!bUsedNormalMaleTalkSfx) {
		bUsedNormalMaleTalkSfx = 1;
		lastNormalMaleTalkSfx = NO_SAMPLE;
	}
	switch(sample) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_HANDS_COWER_1, 7u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_CAR_JACKED_1, 7u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_EVADE_1, 9u);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_FLEE_RUN_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_CAR_COLLISION_1, 12u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_CHAT_SEXY_1, 8u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_CHAT_EVENT_1, 0xAu);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastNormalMaleTalkSfx,
		          AUDIO_SAMPLE_PED_NORMAL_MALE_CHAT_1, 25u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return sfx;
}

uint32
cAudioManager::GetTaxiDriverTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedTaxiDriverTalkSfx = *(bool *)0x650AF4;
	static uint32 &lastTaxiDriverTalkSfx = *(uint32 *)0x650AF0;

	if(!bUsedTaxiDriverTalkSfx) {
		bUsedTaxiDriverTalkSfx = 1;
		lastTaxiDriverTalkSfx = NO_SAMPLE;
	}

	if(sample == SOUND_PED_CAR_JACKED) {
		GetPhrase(&sfx, &lastTaxiDriverTalkSfx,
		          AUDIO_SAMPLE_PED_TAXI_DRIVER_1_CAR_JACKED_1, 7u);
	} else {
		if(sample != SOUND_PED_CAR_COLLISION)
			return cAudioManager::GetGenericMaleTalkSfx(sample);
		GetPhrase(&sfx, &lastTaxiDriverTalkSfx,
		          AUDIO_SAMPLE_PED_TAXI_DRIVER_1_CAR_COLLISION_1, 6u);
	}
	return 13 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetPimpTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedPimpTalkSfx = *(bool *)0x650AFC;
	static uint32 &lastPimpTalkSfx = *(uint32 *)0x650AF8;

	if(!bUsedPimpTalkSfx) {
		bUsedPimpTalkSfx = 1;
		lastPimpTalkSfx = NO_SAMPLE;
	}

	switch(sample) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastPimpTalkSfx,
		          AUDIO_SAMPLE_PED_PIMP_HANDS_UP_1, 7u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastPimpTalkSfx,
		          AUDIO_SAMPLE_PED_PIMP_CAR_JACKED_1, 4u);
		break;
	case SOUND_PED_DEFEND:
		GetPhrase(&sfx, &lastPimpTalkSfx,
		          AUDIO_SAMPLE_PED_PIMP_DEFEND_1, 9u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastPimpTalkSfx, AUDIO_SAMPLE_PED_PIMP_EVADE_1,
		          6u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastPimpTalkSfx,
		          AUDIO_SAMPLE_PED_PIMP_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(&sfx, &lastPimpTalkSfx,
		          AUDIO_SAMPLE_PED_PIMP_CHAT_EVENT_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastPimpTalkSfx, AUDIO_SAMPLE_PED_PIMP_CHAT_1,
		          17u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return sfx;
}

uint32
cAudioManager::GetMafiaTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedMafiaTalkSfx = *(bool *)0x650934;
	static uint32 &lastMafiaTalkSfx = *(uint32 *)0x650930;

	if(!bUsedMafiaTalkSfx) {
		bUsedMafiaTalkSfx = 1;
		lastMafiaTalkSfx = NO_SAMPLE;
	}

	switch(sample) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastMafiaTalkSfx,
		          AUDIO_SAMPLE_PED_MAFIA_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastMafiaTalkSfx,
		          AUDIO_SAMPLE_PED_MAFIA_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastMafiaTalkSfx,
		          AUDIO_SAMPLE_PED_MAFIA_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastMafiaTalkSfx,
		          AUDIO_SAMPLE_PED_MAFIA_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastMafiaTalkSfx,
		          AUDIO_SAMPLE_PED_MAFIA_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastMafiaTalkSfx,
		          AUDIO_SAMPLE_PED_MAFIA_1_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastMafiaTalkSfx,
		          AUDIO_SAMPLE_PED_MAFIA_1_CHAT_1, 7u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return 30 * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetTriadTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedTriadTalkSfx = *(bool *)0x65093C;
	static uint32 &lastTriadTalkSfx = *(uint32 *)0x650938;

	if(!bUsedTriadTalkSfx) {
		bUsedTriadTalkSfx = 1;
		lastTriadTalkSfx = NO_SAMPLE;
	}

	switch(sample) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_HANDS_UP_1, 3u);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_CAR_COLLISION_1, 7u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_CHAT_SEXY_1, 3u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastTriadTalkSfx,
		          AUDIO_SAMPLE_PED_TRIAD_1_CHAT_1, 8u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return sfx;
}

uint32
cAudioManager::GetDiabloTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedDiabloTalkSfx = *(bool *)0x650944;
	static uint32 &lastDiabloTalkSfx = *(uint32 *)0x650940;

	if(!bUsedDiabloTalkSfx) {
		bUsedDiabloTalkSfx = 1;
		lastDiabloTalkSfx = NO_SAMPLE;
	}

	switch(sample) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_HANDS_UP_1, 4u);
		break;
	case SOUND_PED_HANDS_COWER:
		sample = SOUND_PED_FLEE_SPRINT;
		return cAudioManager::GetGenericMaleTalkSfx(sample);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_ATTACK_1, 4u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_CAR_COLLISION_1, 5u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_CHAT_SEXY_1, 4u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastDiabloTalkSfx,
		          AUDIO_SAMPLE_PED_DIABLO_1_CHAT_1, 5u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return 30 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetYakuzaTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedYakuzaTalkSfx = *(bool *)0x65094C;
	static uint32 &lastYakuzaTalkSfx = *(uint32 *)0x650948;

	if(!bUsedYakuzaTalkSfx) {
		bUsedYakuzaTalkSfx = 1;
		lastYakuzaTalkSfx = NO_SAMPLE;
	}

	switch(sample) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastYakuzaTalkSfx,
		          AUDIO_SAMPLE_PED_YAKUZA_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(&sfx, &lastYakuzaTalkSfx,
		          AUDIO_SAMPLE_PED_YAKUZA_1_CAR_JACKED_1, 2u);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastYakuzaTalkSfx,
		          AUDIO_SAMPLE_PED_YAKUZA_1_ATTACK_1, 5u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastYakuzaTalkSfx,
		          AUDIO_SAMPLE_PED_YAKUZA_1_EVADE_1, 4u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastYakuzaTalkSfx,
		          AUDIO_SAMPLE_PED_YAKUZA_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastYakuzaTalkSfx,
		          AUDIO_SAMPLE_PED_YAKUZA_1_CHAT_1, 5u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return 24 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetYardieTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedYardieTalkSfx = *(bool *)0x650954;
	static uint32 &lastYardieTalkSfx = *(uint32 *)0x650950;

	if(!bUsedYardieTalkSfx) {
		bUsedYardieTalkSfx = 1;
		lastYardieTalkSfx = NO_SAMPLE;
	}

	switch(sample) {
	case SOUND_PED_HANDS_UP:
		sfx = AUDIO_SAMPLE_PED_YARDIE_1_HANDS_UP_1;
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(&sfx, &lastYardieTalkSfx,
		          AUDIO_SAMPLE_PED_YARDIE_1_CAR_JACKING_1, 2u);
		break;
	case SOUND_PED_CAR_JACKED:
		sfx = AUDIO_SAMPLE_PED_YARDIE_1_CAR_JACKED_1;
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(&sfx, &lastYardieTalkSfx,
		          AUDIO_SAMPLE_PED_YARDIE_1_ATTACK_1, 6u);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(&sfx, &lastYardieTalkSfx,
		          AUDIO_SAMPLE_PED_YARDIE_1_EVADE_1, 5u);
		break;
	case SOUND_PED_CAR_COLLISION:
		GetPhrase(&sfx, &lastYardieTalkSfx,
		          AUDIO_SAMPLE_PED_YARDIE_1_CAR_COLLISION_1, 6u);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(&sfx, &lastYardieTalkSfx,
		          AUDIO_SAMPLE_PED_YARDIE_1_CHAT_SEXY_1, 2u);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(&sfx, &lastYardieTalkSfx,
		          AUDIO_SAMPLE_PED_YARDIE_1_CHAT_1, 8u);
		break;
	default: return cAudioManager::GetGenericMaleTalkSfx(sample);
	}
	return 31 * (m_sQueueSample.m_nEntityIndex & 1) + sfx;
}

uint32
cAudioManager::GetGenericMaleTalkSfx(int16 sample)
{
	uint32 sfx;
	static bool &bUsedGenericMaleTalkSfx = *(bool *)0x650B0C;
	static uint32 &lastGenericMaleTalkSfx = *(uint32 *)0x650B08;

	if(!bUsedGenericMaleTalkSfx) {
		bUsedGenericMaleTalkSfx = 1;
		lastGenericMaleTalkSfx = NO_SAMPLE;
	}
	switch(sample) {
	case SOUND_PED_DEATH:
		GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		          AUDIO_SAMPLE_PED_MALE_DEATH_1, 8u);
		break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND:
		GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		          AUDIO_SAMPLE_INJURED_PED_MALE_OUCH_1, 15u);
		break;
	case SOUND_PED_BURNING:
		GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		          AUDIO_SAMPLE_PED_MALE_BURNING_1, 8u);
		break;
	case SOUND_PED_FLEE_SPRINT:
		GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		          AUDIO_SAMPLE_PED_MALE_FLEE_SPRINT_1, 6u);
		break;
	default: return NO_SAMPLE;
	}
	return sfx;
}

WRAPPER void
cAudioManager::Service()
{
	EAXJMP(0x57A2A0);
}

STARTPATCHES
InjectHook(0x56AD20, &cAudioManager::PlayerJustLeftCar, PATCH_JUMP);
InjectHook(0x570DB0, &cAudioManager::GetPhrase, PATCH_JUMP);
InjectHook(0x570E00, &cAudioManager::GetPlayerTalkSfx, PATCH_JUMP);
InjectHook(0x570EA0, &cAudioManager::GetCopTalkSfx, PATCH_JUMP);
InjectHook(0x570F80, &cAudioManager::GetSwatTalkSfx, PATCH_JUMP);
InjectHook(0x571040, &cAudioManager::GetFBITalkSfx, PATCH_JUMP);
InjectHook(0x571110, &cAudioManager::GetArmyTalkSfx, PATCH_JUMP);
InjectHook(0x5711C0, &cAudioManager::GetMedicTalkSfx, PATCH_JUMP);
InjectHook(0x5712B0, &cAudioManager::GetFiremanTalkSfx, PATCH_JUMP);
InjectHook(0x575340, &cAudioManager::GetNormalMaleTalkSfx, PATCH_JUMP);
InjectHook(0x575190, &cAudioManager::GetTaxiDriverTalkSfx, PATCH_JUMP);
InjectHook(0x575240, &cAudioManager::GetPimpTalkSfx, PATCH_JUMP);
InjectHook(0x571510, &cAudioManager::GetMafiaTalkSfx, PATCH_JUMP);
InjectHook(0x571650, &cAudioManager::GetTriadTalkSfx, PATCH_JUMP);
InjectHook(0x571770, &cAudioManager::GetDiabloTalkSfx, PATCH_JUMP);
InjectHook(0x5718D0, &cAudioManager::GetYakuzaTalkSfx, PATCH_JUMP);
InjectHook(0x5719E0, &cAudioManager::GetYardieTalkSfx, PATCH_JUMP);
InjectHook(0x575460, &cAudioManager::GetGenericMaleTalkSfx, PATCH_JUMP);
ENDPATCHES
