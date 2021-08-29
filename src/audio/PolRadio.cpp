#include "common.h"

#include "DMAudio.h"

#include "AudioManager.h"

#include "AudioSamples.h"
#include "MusicManager.h"
#include "PlayerPed.h"
#include "PolRadio.h"
#include "Replay.h"
#include "Vehicle.h"
#include "World.h"
#include "Zones.h"
#include "sampman.h"
#include "Wanted.h"

struct tPoliceRadioZone {
	char m_aName[8];
	uint32 m_nSampleIndex;
	int32 field_12;
};

tPoliceRadioZone ZoneSfx[NUMAUDIOZONES];

uint32 g_nMissionAudioSfx = TOTAL_AUDIO_SAMPLES;
int8 g_nMissionAudioPlayingStatus = PLAY_STATUS_FINISHED;
bool8 gSpecialSuspectLastSeenReport;
uint32 gMinTimeToNextReport[NUM_CRIME_TYPES];

void
cAudioManager::InitialisePoliceRadioZones()
{
	for (int32 i = 0; i < NUMAUDIOZONES; i++)
		memset(ZoneSfx[i].m_aName, 0, 8);

#define SETZONESFX(i, name, sample) \
	strcpy(ZoneSfx[i].m_aName, name); \
	ZoneSfx[i].m_nSampleIndex = sample;

	SETZONESFX(0, "VICE_C", SFX_POLICE_RADIO_VICE_CITY);
	SETZONESFX(1, "IND_ZON", SFX_POLICE_RADIO_VICE_CITY_BEACH);
	SETZONESFX(2, "COM_ZON", SFX_POLICE_RADIO_VICE_CITY_MAINLAND);
	SETZONESFX(3, "BEACH1", SFX_POLICE_RADIO_OCEAN_BEACH);
	SETZONESFX(4, "BEACH2", SFX_POLICE_RADIO_WASHINGTON_BEACH);
	SETZONESFX(5, "BEACH3", SFX_POLICE_RADIO_VICE_POINT);
	SETZONESFX(6, "GOLFC", SFX_POLICE_RADIO_LEAF_LINKS);
	SETZONESFX(7, "STARI", SFX_POLICE_RADIO_STARFISH_ISLAND);
	SETZONESFX(8, "DOCKS", SFX_POLICE_RADIO_VICEPORT);
	SETZONESFX(9, "HAVANA", SFX_POLICE_RADIO_LITTLE_HAVANA);
	SETZONESFX(10, "HAITI", SFX_POLICE_RADIO_LITTLE_HAITI);
	SETZONESFX(11, "PORNI", SFX_POLICE_RADIO_PRAWN_ISLAND);
	SETZONESFX(12, "DTOWN", SFX_POLICE_RADIO_DOWNTOWN);
	SETZONESFX(13, "A_PORT", SFX_POLICE_RADIO_ESCOBAR_INTERNATIONAL);

#undef SETZONESFX
}

void
cAudioManager::InitialisePoliceRadio()
{
	m_sPoliceRadioQueue.Reset();
	for (int32 i = 0; i < ARRAY_SIZE(m_aCrimes); i++)
		m_aCrimes[i].type = CRIME_NONE;
#if !defined(GTA_PS2) || defined(AUDIO_REVERB)
	SampleManager.SetChannelReverbFlag(CHANNEL_POLICE_RADIO, FALSE);
#endif
	gSpecialSuspectLastSeenReport = FALSE;
	for (int32 i = 0; i < ARRAY_SIZE(gMinTimeToNextReport); i++)
		gMinTimeToNextReport[i] = m_FrameCounter;
}

void
cAudioManager::ResetPoliceRadio()
{
	if (!m_bIsInitialised) return;
	if (SampleManager.GetChannelUsedFlag(CHANNEL_POLICE_RADIO)) SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
	InitialisePoliceRadio();
}

void
cAudioManager::SetMissionScriptPoliceAudio(uint32 sfx)
{
	if (!m_bIsInitialised) return;
	if (g_nMissionAudioPlayingStatus != PLAY_STATUS_PLAYING) {
		g_nMissionAudioPlayingStatus = PLAY_STATUS_STOPPED;
		g_nMissionAudioSfx = sfx;
	}
}

int8
cAudioManager::GetMissionScriptPoliceAudioPlayingStatus()
{
	return g_nMissionAudioPlayingStatus;
}

void
cAudioManager::DoPoliceRadioCrackle()
{
	m_sQueueSample.m_nEntityIndex = m_nPoliceChannelEntity;
	m_sQueueSample.m_nCounter = 0;
	m_sQueueSample.m_nSampleIndex = SFX_POLICE_RADIO_CRACKLE;
	m_sQueueSample.m_nBankIndex = SFX_BANK_0;
	m_sQueueSample.m_bIs2D = TRUE;
	m_sQueueSample.m_nPriority = 10;
	m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_POLICE_RADIO_CRACKLE);
	m_sQueueSample.m_nVolume = m_anRandomTable[2] % 20 + 15;
	m_sQueueSample.m_nLoopCount = 0;
	SET_EMITTING_VOLUME(m_sQueueSample.m_nVolume);
	SET_LOOP_OFFSETS(SFX_POLICE_RADIO_CRACKLE)
	m_sQueueSample.m_bStatic = FALSE;
	SET_SOUND_REVERB(FALSE);
	m_sQueueSample.m_nPan = 63;
	m_sQueueSample.m_nFramesToPlay = 3;
	SET_SOUND_REFLECTION(FALSE);
	AddSampleToRequestedQueue();
}

void
cAudioManager::ServicePoliceRadio()
{
	int32 wantedLevel = 0; // uninitialized variable
	static uint32 nLastSeen = 300;

	if(!m_bIsInitialised) return;

	if(!m_bIsPaused) {
		bool8 crimeReport = SetupCrimeReport();
#ifdef FIX_BUGS // Crash at 0x5fe6ef
		if(CReplay::IsPlayingBack() || !FindPlayerPed() || !FindPlayerPed()->m_pWanted)
			return;
#endif
		CPlayerPed *playerPed = FindPlayerPed();
		if (playerPed) {
			wantedLevel = playerPed->m_pWanted->GetWantedLevel();
			if (!crimeReport) {
				if (wantedLevel != 0) {
					if (nLastSeen != 0)
#ifdef FIX_BUGS
						nLastSeen -= CTimer::GetLogicalFramesPassed();
#else
						nLastSeen--;
#endif
					else {
						nLastSeen = m_anRandomTable[1] % 1000 + 2000;
						SetupSuspectLastSeenReport();
					}
				}
			}
		}
	}
	ServicePoliceRadioChannel(wantedLevel);
}

void
cAudioManager::ServicePoliceRadioChannel(uint8 wantedLevel)
{
	bool8 processed = FALSE;
	uint32 sample;
	uint32 freq;

	static int cWait = 0;
	static bool8 bChannelOpen = FALSE;
	static uint8 bMissionAudioPhysicalPlayingStatus = PLAY_STATUS_STOPPED;
	static uint32 PoliceChannelFreq = 22050;

	if (!m_bIsInitialised) return;

	if (m_bIsPaused) {
		if (SampleManager.GetChannelUsedFlag(CHANNEL_POLICE_RADIO)) SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
		if (g_nMissionAudioSfx != NO_SAMPLE && bMissionAudioPhysicalPlayingStatus == PLAY_STATUS_PLAYING &&
			SampleManager.IsStreamPlaying(1)) {
			SampleManager.PauseStream(TRUE, 1);
		}
	} else {
		if (m_bWasPaused && g_nMissionAudioSfx != NO_SAMPLE &&
			bMissionAudioPhysicalPlayingStatus == PLAY_STATUS_PLAYING) {
			SampleManager.PauseStream(FALSE, 1);
		}
		if (m_sPoliceRadioQueue.m_nSamplesInQueue == 0) bChannelOpen = FALSE;
		if (cWait) {
#ifdef FIX_BUGS
			cWait -= CTimer::GetLogicalFramesPassed();
#else
			--cWait;
#endif
			return;
		}
		if (g_nMissionAudioSfx != NO_SAMPLE && !bChannelOpen) {
			if (g_nMissionAudioPlayingStatus != PLAY_STATUS_STOPPED) {
				if (g_nMissionAudioPlayingStatus == PLAY_STATUS_PLAYING && bMissionAudioPhysicalPlayingStatus == PLAY_STATUS_STOPPED &&
					SampleManager.IsStreamPlaying(1)) {
					bMissionAudioPhysicalPlayingStatus = PLAY_STATUS_PLAYING;
				}
				if (bMissionAudioPhysicalPlayingStatus == PLAY_STATUS_PLAYING) {
					if (SampleManager.IsStreamPlaying(1)) {
						DoPoliceRadioCrackle();
					} else {
						bMissionAudioPhysicalPlayingStatus = PLAY_STATUS_FINISHED;
						g_nMissionAudioPlayingStatus = PLAY_STATUS_FINISHED;
						g_nMissionAudioSfx = NO_SAMPLE;
						cWait = 30;
					}
					return;
				}
			} else if (!SampleManager.GetChannelUsedFlag(CHANNEL_POLICE_RADIO)) {
				SampleManager.PreloadStreamedFile(g_nMissionAudioSfx, 1);
				SampleManager.SetStreamedVolumeAndPan(MAX_VOLUME, 63, TRUE, 1);
				SampleManager.StartPreloadedStreamedFile(1);
				g_nMissionAudioPlayingStatus = PLAY_STATUS_PLAYING;
				bMissionAudioPhysicalPlayingStatus = PLAY_STATUS_STOPPED;
				return;
			}
		}
		if (bChannelOpen) DoPoliceRadioCrackle();
		if ((g_nMissionAudioSfx == NO_SAMPLE || g_nMissionAudioPlayingStatus != PLAY_STATUS_PLAYING) &&
			!SampleManager.GetChannelUsedFlag(CHANNEL_POLICE_RADIO) && m_sPoliceRadioQueue.m_nSamplesInQueue != 0) {
			sample = m_sPoliceRadioQueue.Remove();
			if (wantedLevel == 0) {
				if (gSpecialSuspectLastSeenReport) {
					gSpecialSuspectLastSeenReport = FALSE;
				} else if (sample == SFX_POLICE_RADIO_MESSAGE_NOISE_1) {
					bChannelOpen = FALSE;
					processed = TRUE;
				}
			}
			if (sample == NO_SAMPLE) {
				if (!processed) cWait = 30;
			} else {
				SampleManager.InitialiseChannel(CHANNEL_POLICE_RADIO, sample, SFX_BANK_0);
				switch (sample) {
				case SFX_POLICE_RADIO_MESSAGE_NOISE_1:
					freq = m_anRandomTable[4] % 2000 + 10025;
					bChannelOpen = bChannelOpen == FALSE;
					break;
				default: freq = SampleManager.GetSampleBaseFrequency(sample); break;
				}
				PoliceChannelFreq = freq;
#ifdef USE_TIME_SCALE_FOR_AUDIO
				SampleManager.SetChannelFrequency(CHANNEL_POLICE_RADIO, freq * CTimer::GetTimeScale());
#else
				SampleManager.SetChannelFrequency(CHANNEL_POLICE_RADIO, freq);
#endif
				SampleManager.SetChannelVolume(CHANNEL_POLICE_RADIO, 100);
				SampleManager.SetChannelPan(CHANNEL_POLICE_RADIO, 63);
				SampleManager.SetChannelLoopCount(CHANNEL_POLICE_RADIO, 1);
#ifndef GTA_PS2
				SampleManager.SetChannelLoopPoints(CHANNEL_POLICE_RADIO, 0, -1);
#endif
				SampleManager.StartChannel(CHANNEL_POLICE_RADIO);
			}
			if (processed) ResetPoliceRadio();
		}
	}
}

bool8
cAudioManager::SetupCrimeReport()
{
	int16 audioZoneId;
	CZone *zone;
	float rangeX;
	float rangeY;
	float halfX;
	float halfY;
	float quarterX;
	float quarterY;
	int i;
	uint32 sampleIndex;
	bool8 processed = FALSE;

	if (MusicManager.m_nMusicMode == MUSICMODE_CUTSCENE) return FALSE;

	if (POLICE_RADIO_QUEUE_MAX_SAMPLES - m_sPoliceRadioQueue.m_nSamplesInQueue <= 9) {
		AgeCrimes();
		return TRUE;
	}

	for (i = 0; i < ARRAY_SIZE(m_aCrimes); i++) {
		if (m_aCrimes[i].type != CRIME_NONE)
			break;
	}

	if (i == ARRAY_SIZE(m_aCrimes)) return FALSE;
	audioZoneId = CTheZones::FindAudioZone(&m_aCrimes[i].position);
	if (audioZoneId >= 0 && audioZoneId < NUMAUDIOZONES) {
		zone = CTheZones::GetAudioZone(audioZoneId);
		for (int j = 0; j < NUMAUDIOZONES; j++) {
			if (strcmp(zone->name, ZoneSfx[j].m_aName) == 0) {
				sampleIndex = ZoneSfx[j].m_nSampleIndex;
				m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
				m_sPoliceRadioQueue.Add(m_anRandomTable[0] % 3 + SFX_WEVE_GOT);
				m_sPoliceRadioQueue.Add(SFX_A_10);
				switch (m_aCrimes[i].type) {
				case CRIME_PED_BURNED:
				case CRIME_HIT_PED_NASTYWEAPON:
					m_aCrimes[i].type = CRIME_HIT_PED;
					break;
				case CRIME_COP_BURNED:
				case CRIME_HIT_COP_NASTYWEAPON:
					m_aCrimes[i].type = CRIME_HIT_COP;
					break;
				case CRIME_VEHICLE_BURNED: m_aCrimes[i].type = CRIME_STEAL_CAR; break;
				case CRIME_DESTROYED_CESSNA: m_aCrimes[i].type = CRIME_SHOOT_HELI; break;
				case CRIME_EXPLOSION: m_aCrimes[i].type = CRIME_STEAL_CAR; break; // huh?
				default: break;
				}
#ifdef FIX_BUGS
				m_sPoliceRadioQueue.Add(m_aCrimes[i].type + SFX_CRIME_1 - 1);
#else
				m_sPoliceRadioQueue.Add(m_aCrimes[i].type + SFX_CRIME_1);
#endif
				m_sPoliceRadioQueue.Add(SFX_IN);
				rangeX = zone->maxx - zone->minx;
				rangeY = zone->maxy - zone->miny;
				halfX = 0.5f * rangeX + zone->minx;
				halfY = 0.5f * rangeY + zone->miny;
				quarterX = 0.25f * rangeX;
				quarterY = 0.25f * rangeY;

				if (m_aCrimes[i].position.y > halfY + quarterY) {
					m_sPoliceRadioQueue.Add(SFX_NORTH);
					processed = TRUE;
				} else if (m_aCrimes[i].position.y < halfY - quarterY) {
					m_sPoliceRadioQueue.Add(SFX_SOUTH);
					processed = TRUE;
				}

				if (m_aCrimes[i].position.x > halfX + quarterX)
					m_sPoliceRadioQueue.Add(SFX_EAST);
				else if (m_aCrimes[i].position.x < halfX - quarterX)
					m_sPoliceRadioQueue.Add(SFX_WEST);
				else if (!processed)
					m_sPoliceRadioQueue.Add(SFX_CENTRAL);

				m_sPoliceRadioQueue.Add(sampleIndex);
				m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
				m_sPoliceRadioQueue.Add(NO_SAMPLE);
				break;
			}
		}
	}
	m_aCrimes[i].type = CRIME_NONE;
	AgeCrimes();
	return TRUE;
}

Const uint32 gCarColourTable[][3] = {
	{NO_SAMPLE, SFX_POLICE_RADIO_BLACK, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_WHITE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_PURPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_YELLOW, NO_SAMPLE},
	{SFX_POLICE_RADIO_BRIGHT, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, SFX_POLICE_RADIO_BLUE, SFX_POLICE_RADIO_GREY},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_RED, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_ORANGE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_ORANGE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_ORANGE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_ORANGE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_ORANGE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_ORANGE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_YELLOW, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_YELLOW, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_YELLOW, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_YELLOW, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_YELLOW, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_YELLOW, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_GREEN, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_GREEN, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_GREEN, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_GREEN, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_GREEN, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_GREEN, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_BLUE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_PURPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_PURPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_PURPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_PURPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_PURPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_PURPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_SILVER, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_SILVER, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_SILVER, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_SILVER, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_SILVER, NO_SAMPLE},
	{NO_SAMPLE, SFX_POLICE_RADIO_SILVER, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_LIGHT, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE},
	{SFX_POLICE_RADIO_DARK, NO_SAMPLE, NO_SAMPLE}
};

void
cAudioManager::SetupSuspectLastSeenReport()
{
	CVehicle *veh;
	uint8 color1;
	uint32 main_color;
	uint32 sample;

	uint32 color_pre_modifier;
	uint32 color_post_modifier;

	if (MusicManager.m_nMusicMode != MUSICMODE_CUTSCENE) {
		veh = FindVehicleOfPlayer();
		if (veh != nil) {
			if (POLICE_RADIO_QUEUE_MAX_SAMPLES - m_sPoliceRadioQueue.m_nSamplesInQueue > 9) {
				color1 = veh->m_currentColour1;
				if (color1 >= ARRAY_SIZE(gCarColourTable)) {
					debug("\n *** UNKNOWN CAR COLOUR %d *** ", color1);
				} else {
					main_color = gCarColourTable[color1][1];
					color_pre_modifier = gCarColourTable[color1][0];
					color_post_modifier = gCarColourTable[color1][2];
					switch (veh->GetModelIndex()) {
					case MI_LANDSTAL:
					case MI_PATRIOT:
					case MI_RANCHER:
					case MI_FBIRANCH:
					case MI_SANDKING:
						sample = SFX_POLICE_RADIO_OFFROAD;
						break;
					case MI_IDAHO:
					case MI_MANANA:
					case MI_ESPERANT:
					case MI_CUBAN:
					case MI_STALLION:
					case MI_SABRE:
					case MI_SABRETUR:
					case MI_VIRGO:
					case MI_BLISTAC:
							sample = SFX_POLICE_RADIO_TUDOOR;
							break;
					case MI_STINGER:
					case MI_INFERNUS:
					case MI_CHEETAH:
					case MI_BANSHEE:
					case MI_PHEONIX:
					case MI_COMET:
					case MI_DELUXO:
					case MI_HOTRING:
						sample = SFX_POLICE_RADIO_SPORTS_CAR;
						break;
					case MI_LINERUN:
						sample = SFX_POLICE_RADIO_RIG;
						break;
					case MI_PEREN:
					case MI_REGINA:
						sample = SFX_POLICE_RADIO_STATION_WAGON;
						break;
					case MI_SENTINEL:
					case MI_FBICAR:
					case MI_WASHING:
					case MI_SENTXS:
					case MI_ADMIRAL:
					case MI_GLENDALE:
					case MI_OCEANIC:
					case MI_HERMES:
					case MI_GREENWOO:
						sample = SFX_POLICE_RADIO_SEDAN;
						break;
					case MI_RIO:
						sample = SFX_POLICE_RADIO_CRUISER;
						break;
					case MI_FIRETRUCK:
						sample = SFX_POLICE_RADIO_FIRE_TRUCK;
						break;
					case MI_TRASH:
						sample = SFX_POLICE_RADIO_GARBAGE_TRUCK;
						break;
					case MI_STRETCH:
					case MI_LOVEFIST:
						sample = SFX_POLICE_RADIO_STRETCH;
						break;
					case MI_VOODOO:
						sample = SFX_POLICE_RADIO_LOWRIDER;
						break;
					case MI_PONY:
					case MI_MOONBEAM:
					case MI_SECURICA:
					case MI_RUMPO:
					case MI_GANGBUR:
					case MI_YANKEE:
					case MI_TOPFUN:
					case MI_BURRITO:
					case MI_SPAND:
						sample = SFX_POLICE_RADIO_VAN;
						break;
					case MI_MULE:
					case MI_BARRACKS:
					case MI_PACKER:
					case MI_FLATBED:
						sample = SFX_POLICE_RADIO_TRUCK;
						break;
					case MI_AMBULAN:
						sample = SFX_POLICE_RADIO_AMBULANCE;
						break;
					case MI_TAXI:
					case MI_CABBIE:
					case MI_ZEBRA:
					case MI_KAUFMAN:
						sample = SFX_POLICE_RADIO_TAXI;
						break;
					case MI_BOBCAT:
					case MI_WALTON:
						sample = SFX_POLICE_RADIO_PICKUP;
						break;
					case MI_MRWHOOP:
						sample = SFX_POLICE_RADIO_ICE_CREAM_VAN;
						break;
					case MI_BFINJECT:
						sample = SFX_POLICE_RADIO_BUGGY;
						break;
					case MI_HUNTER:
					case MI_CHOPPER:
					case MI_SEASPAR:
					case MI_SPARROW:
					case MI_MAVERICK:
					case MI_VCNMAV:
					case MI_POLMAV:
						sample = SFX_POLICE_RADIO_HELICOPTER;
						break;
					case MI_POLICE:
						sample = SFX_POLICE_RADIO_POLICE_CAR;
						break;
					case MI_ENFORCER:
						sample = SFX_POLICE_RADIO_SWAT_VAN;
						break;
					case MI_PREDATOR:
					case MI_SQUALO:
					case MI_SPEEDER:
						sample = SFX_POLICE_RADIO_SPEEDBOAT;
						break;
					case MI_BUS:
						sample = SFX_POLICE_RADIO_BUS;
						break;
					case MI_RHINO:
						sample = SFX_POLICE_RADIO_TANK;
						break;
					case MI_ANGEL:
					case MI_PCJ600:
					case MI_FREEWAY:
					case MI_SANCHEZ:
						sample = SFX_POLICE_RADIO_MOTOBIKE;
						break;
					case MI_COACH:
						sample = SFX_POLICE_RADIO_COACH;
						break;
					case MI_ROMERO:
						sample = SFX_POLICE_RADIO_HEARSE;
						break;
					case MI_PIZZABOY:
					case MI_FAGGIO:
						sample = SFX_POLICE_RADIO_MOPED;
						break;
					case MI_DEADDODO:
					case MI_SKIMMER:
						sample = SFX_POLICE_RADIO_PLANE;
						break;
					case MI_REEFER:
					case MI_TROPIC:
					case MI_COASTG:
					case MI_MARQUIS:
					case MI_JETMAX:
						sample = SFX_POLICE_RADIO_BOAT;
						break;
					case MI_CADDY:
						sample = SFX_POLICE_RADIO_GOLF_CART;
						break;
					case MI_DINGHY:
						sample = SFX_POLICE_RADIO_DINGHY;
						break;
					default:
						//debug("\n *** UNKNOWN CAR MODEL INDEX %d *** ", veh->GetModelIndex());
						return;
					}
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_SUSPECT);
					if (m_anRandomTable[3] % 2) 
						m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_LAST_SEEN);
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_IN_A);
					if (color_pre_modifier != NO_SAMPLE)
						m_sPoliceRadioQueue.Add(color_pre_modifier);
					if (main_color != NO_SAMPLE)
						m_sPoliceRadioQueue.Add(main_color);
					if (color_post_modifier != NO_SAMPLE)
						m_sPoliceRadioQueue.Add(color_post_modifier);
					m_sPoliceRadioQueue.Add(sample);
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
					m_sPoliceRadioQueue.Add(NO_SAMPLE);
				}
			}
		} else if (POLICE_RADIO_QUEUE_MAX_SAMPLES - m_sPoliceRadioQueue.m_nSamplesInQueue > 4) {
			m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
			m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_SUSPECT);
			m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_ON_FOOT);
			m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
			m_sPoliceRadioQueue.Add(NO_SAMPLE);
		}
	}
}

void
cAudioManager::ReportCrime(eCrimeType type, const CVector &pos)
{
	int32 lastCrime = ARRAY_SIZE(m_aCrimes);
	if (m_bIsInitialised && MusicManager.m_nMusicMode != MUSICMODE_CUTSCENE && FindPlayerPed()->m_pWanted->GetWantedLevel() > 0 &&
		(type > CRIME_NONE || type < NUM_CRIME_TYPES) && m_FrameCounter >= gMinTimeToNextReport[type]) {
		for (int32 i = 0; i < ARRAY_SIZE(m_aCrimes); i++) {
			if (m_aCrimes[i].type != CRIME_NONE) {
				if (m_aCrimes[i].type == type) {
					m_aCrimes[i].position = pos;
					m_aCrimes[i].timer = 0;
					return;
				}
			} else
				lastCrime = i;
		}

		if (lastCrime < ARRAY_SIZE(m_aCrimes)) {
			m_aCrimes[lastCrime].type = type;
			m_aCrimes[lastCrime].position = pos;
			m_aCrimes[lastCrime].timer = 0;
			gMinTimeToNextReport[type] = m_FrameCounter + 500;
		}
	}
}

void
cAudioManager::PlaySuspectLastSeen(float x, float y, float z)
{
	int16 audioZone;
	CZone *zone;
	float rangeX;
	float rangeY;
	float halfX;
	float halfY;
	float quarterX;
	float quarterY;
	uint32 sample;
	bool8 processed = FALSE;
	CVector vec = CVector(x, y, z);

	if (!m_bIsInitialised) return;

	if (MusicManager.m_nMusicMode != MUSICMODE_CUTSCENE && POLICE_RADIO_QUEUE_MAX_SAMPLES - m_sPoliceRadioQueue.m_nSamplesInQueue > 9) {
		audioZone = CTheZones::FindAudioZone(&vec);
		if (audioZone >= 0 && audioZone < NUMAUDIOZONES) {
			zone = CTheZones::GetAudioZone(audioZone);
			for (int i = 0; i < NUMAUDIOZONES; i++) {
				if (strcmp(zone->name, ZoneSfx[i].m_aName) == 0) {
					sample = ZoneSfx[i].m_nSampleIndex;
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_SUSPECT);
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_LAST_SEEN);
					m_sPoliceRadioQueue.Add(SFX_IN);
					rangeX = zone->maxx - zone->minx;
					rangeY = zone->maxy - zone->miny;
					halfX = 0.5f * rangeX + zone->minx;
					halfY = 0.5f * rangeY + zone->miny;
					quarterX = 0.25f * rangeX;
					quarterY = 0.25f * rangeY;

					if (vec.y > halfY + quarterY) {
						m_sPoliceRadioQueue.Add(SFX_NORTH);
						processed = TRUE;
					} else if (vec.y < halfY - quarterY) {
						m_sPoliceRadioQueue.Add(SFX_SOUTH);
						processed = TRUE;
					}

					if (vec.x > halfX + quarterX)
						m_sPoliceRadioQueue.Add(SFX_EAST);
					else if (vec.x < halfX - quarterX)
						m_sPoliceRadioQueue.Add(SFX_WEST);
					else if (!processed)
						m_sPoliceRadioQueue.Add(SFX_CENTRAL);
					m_sPoliceRadioQueue.Add(sample);
					m_sPoliceRadioQueue.Add(SFX_POLICE_RADIO_MESSAGE_NOISE_1);
					m_sPoliceRadioQueue.Add(NO_SAMPLE);
					gSpecialSuspectLastSeenReport = TRUE;
					break;
				}
			}
		}
	}
}

void
cAudioManager::AgeCrimes()
{
	for (uint8 i = 0; i < ARRAY_SIZE(m_aCrimes); i++) {
		if (m_aCrimes[i].type != CRIME_NONE) {
			if (++m_aCrimes[i].timer > 1200) m_aCrimes[i].type = CRIME_NONE;
		}
	}
}
