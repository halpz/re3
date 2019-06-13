#include "common.h"
#include "patcher.h"
#include "AudioManager.h"

cAudioManager &AudioManager = *(cAudioManager*)0x880FC0;

void
cAudioManager::PlayerJustLeftCar(void)
{
	// UNUSED: This is a perfectly empty function.
}

void
cAudioManager::GetPhrase(eAudioSamples *phrase, eAudioSamples *prevPhrase,
                         eAudioSamples sample, uint32 maxOffset)
{
	*phrase = eAudioSamples(
	    sample +
	    (uint32)m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] %
	        maxOffset);
	if(*phrase == *prevPhrase &&
	   ++*(uint32 *)phrase >= (uint32)sample + maxOffset)
		*phrase = sample;
	*prevPhrase = *phrase;
}

static bool &bUsedPlayerTalkSfx = *(bool *)0x6508f4;
static eAudioSamples &lastPlayerTalkSfx = *(eAudioSamples *)0x6508f0;

uint32
cAudioManager::GetPlayerTalkSfx(eSound sound)
{
	eAudioSamples sfx;

	if(!bUsedPlayerTalkSfx) {
		bUsedPlayerTalkSfx = true;
		lastPlayerTalkSfx = NO_SAMPLE;
	}
	switch(sound) {
	case SOUND_PED_DAMAGE:
		cAudioManager::GetPhrase(&sfx, &lastPlayerTalkSfx,
		                         AUDIO_SAMPLE_PED_DAMAGE_REACTION_1,
		                         11u);
		break;

	case SOUND_PED_HIT:
		cAudioManager::GetPhrase(&sfx, &lastPlayerTalkSfx,
		                         AUDIO_SAMPLE_PED_HIT_REACTION_1, 10u);
		break;

	case SOUND_PED_LAND:
		cAudioManager::GetPhrase(&sfx, &lastPlayerTalkSfx,
		                         AUDIO_SAMPLE_PED_FALL_REACTION_1, 6u);
		break;

	default: sfx = NO_SAMPLE; break;
	}
	return sfx;
}

static bool &bUsedGenericMaleTalkSfx = *(bool *)0x650B0C;
static eAudioSamples &lastGenericMaleTalkSfx = *(eAudioSamples *)0x650B08;

uint32
cAudioManager::GetGenericMaleTalkSfx(eSound sample)
{
	eAudioSamples sfx;

	if(!bUsedGenericMaleTalkSfx) {
		bUsedGenericMaleTalkSfx = 1;
		lastGenericMaleTalkSfx = NO_SAMPLE;
	}
	switch(sample) {
	case SOUND_PED_DEATH:
		cAudioManager::GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		                         AUDIO_SAMPLE_PED_MALE_DEATH_1, 8u);
		break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND:
		cAudioManager::GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		                         AUDIO_SAMPLE_INJURED_PED_MALE_OUCH_1,
		                         15u);
		break;
	case SOUND_PED_BURNING:
		cAudioManager::GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		                         AUDIO_SAMPLE_PED_MALE_BURNING_1, 8u);
		break;
	case SOUND_PED_FLEE_SPRINT:
		cAudioManager::GetPhrase(&sfx, &lastGenericMaleTalkSfx,
		                         AUDIO_SAMPLE_PED_MALE_FLEE_SPRINT_1,
		                         6u);
		break;
	default: return NO_SAMPLE;
	}
	return sfx;
}

WRAPPER void cAudioManager::Service() { EAXJMP(0x57A2A0); }

STARTPATCHES
InjectHook(0x56AD20, &cAudioManager::PlayerJustLeftCar, PATCH_JUMP);
InjectHook(0x570DB0, &cAudioManager::GetPhrase, PATCH_JUMP);
InjectHook(0x570E00, &cAudioManager::GetPlayerTalkSfx, PATCH_JUMP);
InjectHook(0x575460, &cAudioManager::GetGenericMaleTalkSfx, PATCH_JUMP);
ENDPATCHES
