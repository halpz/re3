#include "common.h"
#include <time.h>
#include "soundlist.h"
#include "MusicManager.h"
#include "AudioManager.h"
#include "ControllerConfig.h"
#include "Camera.h"
#include "Font.h"
#include "Hud.h"
#include "ModelIndices.h"
#include "Replay.h"
#include "Pad.h"
#include "Text.h"
#include "Timer.h"
#include "World.h"
#include "sampman.h"
#include "Stats.h"
#include "Script.h"
#include "ZoneCull.h"
#include "Weather.h"
#include "DMAudio.h"
#include "GenericGameStorage.h"

#if !defined FIX_BUGS && (defined RADIO_SCROLL_TO_PREV_STATION || defined RADIO_OFF_TEXT)
static_assert(false, "R*'s radio implementation is quite buggy, RADIO_SCROLL_TO_PREV_STATION and RADIO_OFF_TEXT won't work without FIX_BUGS");
#endif

cMusicManager MusicManager;
int32 gNumRetunePresses;
int32 gRetuneCounter;
bool g_bAnnouncementReadPosAlready;
uint8 RadioStaticCounter = 5;
uint32 RadioStaticTimer;

CVector vecRiotPosition(300.7f, -322.0f, 12.0f);

uint32 NewGameRadioTimers[10] =
{
	948160,
	452150,
	2438150,
	3538230,
	3513100,
	4246050,
	1418050,
	3178240,
	471210,
	0
};

cMusicManager::cMusicManager()
{
	m_bIsInitialised = false;
	m_bDisabled = false;
	m_nFrontendTrack = NO_TRACK;
	m_nPlayingTrack = NO_TRACK;
	m_nUpcomingMusicMode = MUSICMODE_DISABLED;
	m_nMusicMode = MUSICMODE_DISABLED;
	m_bSetNextStation = false;

	for (int i = 0; i < NUM_RADIOS; i++)
		aListenTimeArray[i] = 0.0f;

	m_nLastTrackServiceTime = 0.0f;
	m_nVolumeLatency = 0;
	m_nCurrentVolume = 0;
	m_nMaxVolume = 0;
	m_nAnnouncement = NO_TRACK;
	m_bAnnouncementInProgress = false;
}

void
cMusicManager::ResetMusicAfterReload()
{
	float afRadioTime[NUM_RADIOS];

	m_bRadioSetByScript = false;
	m_nRadioStationScript = WILDSTYLE;
	m_nRadioPosition = -1;
	m_nAnnouncement = NO_TRACK;
	m_bAnnouncementInProgress = false;
	m_bSetNextStation = false;
	RadioStaticTimer = 0;
	gNumRetunePresses = 0;
	gRetuneCounter = 0;
	m_nFrontendTrack = NO_TRACK;
	m_nPlayingTrack = NO_TRACK;
	m_FrontendLoopFlag = false;
	m_bTrackChangeStarted = false;
	m_nNextTrack = NO_TRACK;
	m_nNextLoopFlag = false;
	m_bVerifyNextTrackStartedToPlay = false;
	m_bGameplayAllowsRadio = false;
	m_bRadioStreamReady = false;
	nFramesSinceCutsceneEnded = -1;
	m_bUserResumedGame = false;
	m_bMusicModeChangeStarted = false;
	m_bEarlyFrontendTrack = false;
	m_nVolumeLatency = 0;
	m_nCurrentVolume = 0;
	m_nMaxVolume = 0;

	bool bRadioWasEverListened = false;

	for (int i = 0; i < NUM_RADIOS; i++) {
		afRadioTime[i] = CStats::GetFavoriteRadioStationList(i);
		if (!bRadioWasEverListened && afRadioTime[i] != 0.0f)
			bRadioWasEverListened = true;
	}

	if (!bRadioWasEverListened) return;

	for (int i = 0; i < NUM_RADIOS; i++) {
		aListenTimeArray[i] = afRadioTime[i];
		int32 trackPos = GetSavedRadioStationPosition(i);
		if (trackPos != -1) {
			if (trackPos > m_aTracks[i].m_nLength) {
				debug("Radio Track %d saved position is %d, Length is only %d\n", i, trackPos, m_aTracks[i].m_nLength);
				trackPos %= m_aTracks[i].m_nLength;
			}
			m_aTracks[i].m_nPosition = trackPos;
			m_aTracks[i].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
		}
	}
}

void
cMusicManager::SetStartingTrackPositions(uint8 isNewGameTimer)
{
	int pos;

	if (IsInitialised()) {
		time_t timevalue = time(0);
		if (timevalue == -1) {
			pos = AudioManager.GetRandomNumber(0);
		} else {
			tm* pTm = localtime(&timevalue);
			if (pTm->tm_sec == 0)
				pTm->tm_sec = AudioManager.GetRandomNumber(0);
			if (pTm->tm_min == 0)
				pTm->tm_min = AudioManager.GetRandomNumber(1);
			if (pTm->tm_hour == 0)
				pTm->tm_hour = AudioManager.GetRandomNumber(2);
			if (pTm->tm_mday == 0)
				pTm->tm_mday = AudioManager.GetRandomNumber(3);
			if (pTm->tm_mon == 0)
				pTm->tm_mon = AudioManager.GetRandomNumber(4);
			if (pTm->tm_year == 0)
				pTm->tm_year = AudioManager.GetRandomNumber(3);
			if (pTm->tm_wday == 0)
				pTm->tm_wday = AudioManager.GetRandomNumber(2);
			pos = pTm->tm_yday
				* pTm->tm_wday
				* pTm->tm_year
				* pTm->tm_mon
				* pTm->tm_mday
				* pTm->tm_hour * pTm->tm_hour
				* pTm->tm_min * pTm->tm_min
				* pTm->tm_sec * pTm->tm_sec * pTm->tm_sec * pTm->tm_sec;
		}

		for (int i = 0; i < TOTAL_STREAMED_SOUNDS; i++) {
			m_aTracks[i].m_nLength = SampleManager.GetStreamedFileLength(i);

			if (i < STREAMED_SOUND_CITY_AMBIENT && isNewGameTimer)
				m_aTracks[i].m_nPosition = NewGameRadioTimers[i];
			else if (i < STREAMED_SOUND_ANNOUNCE_BRIDGE_CLOSED)
				m_aTracks[i].m_nPosition = (pos * AudioManager.GetRandomNumber(i % 5)) % m_aTracks[i].m_nLength;
			else
				m_aTracks[i].m_nPosition = 0;
			
			m_aTracks[i].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
		}
	}
}

bool
cMusicManager::Initialise()
{
	if (!IsInitialised()) {
		m_bIsInitialised = true;
		SetStartingTrackPositions(false);
		m_bResetTimers = false;
		m_nResetTime = 0;
		m_bRadioSetByScript = false;
		m_nRadioStationScript = WILDSTYLE;
		m_nRadioPosition = -1;
		m_nRadioInCar = NO_TRACK;
		gRetuneCounter = 0;
		gNumRetunePresses = 0;
		m_nFrontendTrack = NO_TRACK;
		m_nPlayingTrack = NO_TRACK;
		m_nUpcomingMusicMode = MUSICMODE_DISABLED;
		m_nMusicMode = MUSICMODE_DISABLED;
		m_FrontendLoopFlag = false;
		m_bTrackChangeStarted = false;
		m_nNextTrack = NO_TRACK;
		m_nNextLoopFlag = false;
		m_bVerifyNextTrackStartedToPlay = false;
		m_bGameplayAllowsRadio = false;
		m_bRadioStreamReady = false;
		nFramesSinceCutsceneEnded = -1;
		m_bUserResumedGame = false;
		m_bMusicModeChangeStarted = false;
		m_nMusicModeToBeSet = MUSICMODE_DISABLED;
		m_bEarlyFrontendTrack = false;
		m_nVolumeLatency = 0;
		m_nCurrentVolume = 0;
		m_nMaxVolume = 0;
	}
	return m_bIsInitialised;
}

void
cMusicManager::Terminate()
{
	if (!IsInitialised()) return;

	if (SampleManager.IsStreamPlaying(0)) {
		SampleManager.StopStreamedFile(0);
		m_nPlayingTrack = NO_TRACK;
	}
	m_bIsInitialised = false;
}

void
cMusicManager::SetRadioChannelByScript(uint32 station, int32 pos)
{
	if (m_bIsInitialised) {
		if (station == STREAMED_SOUND_RADIO_MP3_PLAYER)
			station = STREAMED_SOUND_CITY_AMBIENT;
		if (station <= STREAMED_SOUND_RADIO_POLICE) {
			m_bRadioSetByScript = true;
			m_nRadioStationScript = station;
			m_nRadioPosition = pos == -1 ? -1 : pos % m_aTracks[station].m_nLength;
		}
	}
}

bool
cMusicManager::PlayerInCar()
{
	CVehicle *vehicle = AudioManager.FindVehicleOfPlayer();
	if(!vehicle)
		return false;

	int32 State = FindPlayerPed()->m_nPedState;

	if(State == PED_DRAG_FROM_CAR || State == PED_EXIT_CAR || State == PED_ARRESTED)
		return false;

	if (vehicle->GetStatus() == STATUS_WRECKED)
		return false;

	return true;
}

uint32
cMusicManager::GetRadioInCar(void)
{
	if (!m_bIsInitialised) return WILDSTYLE;
	if (PlayerInCar()) {
		CVehicle* veh = AudioManager.FindVehicleOfPlayer();
		if (veh != nil) {
			if (UsesPoliceRadio(veh) || UsesTaxiRadio(veh)) {
				if (m_nRadioInCar == NO_TRACK || (CReplay::IsPlayingBack() && AudioManager.m_nUserPause == 0))
					return STREAMED_SOUND_RADIO_POLICE;
				return m_nRadioInCar;
			}
			else return veh->m_nRadioStation;
		}
	}

	if (m_nRadioInCar == NO_TRACK || (CReplay::IsPlayingBack() && AudioManager.m_nUserPause == 0))
		return RADIO_OFF;
	return m_nRadioInCar;
}

void
cMusicManager::SetRadioInCar(uint32 station)
{
	if (m_bIsInitialised) {
		if (!PlayerInCar()) {
			m_nRadioInCar = station;
			return;
		}
		CVehicle* veh = AudioManager.FindVehicleOfPlayer();
		if (veh == nil) return;
		if (UsesPoliceRadio(veh) || UsesTaxiRadio(veh))
			m_nRadioInCar = station;
		else
			veh->m_nRadioStation = station;
	}
}

void
cMusicManager::RecordRadioStats()
{
	if (m_nPlayingTrack < NUM_RADIOS) {
		double time /*Rusty*/ = CTimer::GetTimeInMillisecondsPauseMode();
		if (time > m_nLastTrackServiceTime)
			aListenTimeArray[m_nPlayingTrack] += time - m_nLastTrackServiceTime;
	}
}

void
cMusicManager::ChangeMusicMode(uint8 mode)
{
	if (!IsInitialised()) return;

	switch (mode)
	{
	case MUSICMODE_FRONTEND: m_nUpcomingMusicMode = MUSICMODE_FRONTEND; break;
	case MUSICMODE_GAME: m_nUpcomingMusicMode = MUSICMODE_GAME; break;
	case MUSICMODE_CUTSCENE:
		m_nUpcomingMusicMode = MUSICMODE_CUTSCENE;
		if (SampleManager.IsStreamPlaying(0)) {
			if (m_nPlayingTrack != NO_TRACK) {
				RecordRadioStats();
				m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition(0);
				m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
			}
		}
		SampleManager.StopStreamedFile(0);
		while (SampleManager.IsStreamPlaying(0))
			SampleManager.StopStreamedFile(0);
		m_nMusicMode = m_nUpcomingMusicMode;
		m_bMusicModeChangeStarted = false;
		m_bTrackChangeStarted = false;
		m_nNextTrack = NO_TRACK;
		m_nNextLoopFlag = false;
		m_bVerifyNextTrackStartedToPlay = false;
		m_nPlayingTrack = NO_TRACK;
		m_nFrontendTrack = NO_TRACK;
		m_bAnnouncementInProgress = false;
		m_nAnnouncement = NO_TRACK;
		g_bAnnouncementReadPosAlready = false;
		break;
	case MUSICMODE_DISABLE: m_nUpcomingMusicMode = MUSICMODE_DISABLED; break;
	default: return;
	}
}

void
cMusicManager::ResetTimers(int32 time)
{
	m_bResetTimers = true;
	m_nResetTime = time;
}

void
cMusicManager::Service()
{
	if (m_bResetTimers) {
		m_bResetTimers = false;
		m_nLastTrackServiceTime = m_nResetTime;
	}

	static bool bRadioStatsRecorded = false;

	if (!m_bIsInitialised || m_bDisabled) return;

	if (!m_bMusicModeChangeStarted)
		m_nMusicModeToBeSet = m_nUpcomingMusicMode;
	if (m_nMusicModeToBeSet == m_nMusicMode) {
		if (!AudioManager.m_nUserPause || AudioManager.m_nPreviousUserPause || m_nMusicMode != MUSICMODE_FRONTEND)
		{
			switch (m_nMusicMode)
			{
			case MUSICMODE_FRONTEND: ServiceFrontEndMode(); break;
			case MUSICMODE_GAME: ServiceGameMode(); break;
			case MUSICMODE_CUTSCENE: SampleManager.SetStreamedVolumeAndPan(MAX_VOLUME, 63, 1, 0); break;
			}
		}
		else
			m_nMusicMode = MUSICMODE_DISABLED;
	} else {
		m_bMusicModeChangeStarted = true;
		if (!m_bUserResumedGame && !AudioManager.m_nUserPause && AudioManager.m_nPreviousUserPause)
			m_bUserResumedGame = true;
		if (AudioManager.m_FrameCounter % 4 == 0) {
			gNumRetunePresses = 0;
			gRetuneCounter = 0;
			m_bSetNextStation = false;
			if (SampleManager.IsStreamPlaying(0)) {
				if (m_nPlayingTrack != NO_TRACK && !bRadioStatsRecorded)
				{
					RecordRadioStats();
					m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition(0);
					m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
					bRadioStatsRecorded = true;
				}
				SampleManager.StopStreamedFile(0);
			} else {
				bRadioStatsRecorded = false;
				m_nMusicMode = m_nMusicModeToBeSet;
				m_bMusicModeChangeStarted = false;
				m_bTrackChangeStarted = false;
				m_nNextTrack = NO_TRACK;
				m_nNextLoopFlag = false;
				m_bVerifyNextTrackStartedToPlay = false;
				m_nPlayingTrack = NO_TRACK;
				if (m_bEarlyFrontendTrack)
					m_bEarlyFrontendTrack = false;
				else
					m_nFrontendTrack = NO_TRACK;
			}
		}
	}
}

void
cMusicManager::ServiceFrontEndMode()
{
	static bool bRadioStatsRecorded = false;

	if (m_bAnnouncementInProgress) {
		SampleManager.StopStreamedFile(0);
		if (SampleManager.IsStreamPlaying(0))
			return;
		g_bAnnouncementReadPosAlready = false;
		m_nAnnouncement = NO_TRACK;
		m_bAnnouncementInProgress = false;
		m_nNextTrack = NO_TRACK;
		m_nFrontendTrack = NO_TRACK;
		m_nPlayingTrack = NO_TRACK;
	}

	if (AudioManager.m_FrameCounter % 4 != 0) return;

	if (!m_bTrackChangeStarted && !m_bVerifyNextTrackStartedToPlay) {
		m_nNextTrack = m_nFrontendTrack;
		m_nNextLoopFlag = m_FrontendLoopFlag;
	}

	if (m_nNextTrack == m_nPlayingTrack) {
		if (SampleManager.IsStreamPlaying(0)) {
			if (m_nVolumeLatency > 0) m_nVolumeLatency--;
			else {
				if (m_nCurrentVolume < m_nMaxVolume)
					m_nCurrentVolume = Min(m_nMaxVolume, m_nCurrentVolume + 6);
				SampleManager.SetStreamedVolumeAndPan(m_nCurrentVolume, 63, 0, 0);
			}
		} else {
			if (m_nPlayingTrack == STREAMED_SOUND_RADIO_MP3_PLAYER)
				SampleManager.StartStreamedFile(STREAMED_SOUND_RADIO_MP3_PLAYER, 0, 0);
			else if (m_nPlayingTrack == STREAMED_SOUND_MISSION_COMPLETED && AudioManager.m_nUserPause == 0)
				ChangeMusicMode(MUSICMODE_GAME);
		}
	} else {
		m_bTrackChangeStarted = true;
		if (m_bVerifyNextTrackStartedToPlay || !SampleManager.IsStreamPlaying(0)) {
			bRadioStatsRecorded = false;
			if (SampleManager.IsStreamPlaying(0) || m_nNextTrack == NO_TRACK) {
				m_nPlayingTrack = m_nNextTrack;
				m_bVerifyNextTrackStartedToPlay = false;
				m_bTrackChangeStarted = false;
			} else {
				uint32 trackStartPos = (m_nNextTrack > STREAMED_SOUND_RADIO_POLICE) ? 0 : GetTrackStartPos(m_nNextTrack);
				if (m_nNextTrack != NO_TRACK) {
					SampleManager.SetStreamedFileLoopFlag(m_nNextLoopFlag, 0);
					SampleManager.StartStreamedFile(m_nNextTrack, trackStartPos, 0);
					m_nVolumeLatency = 3;
					m_nCurrentVolume = 0;
					m_nMaxVolume = 100;
					SampleManager.SetStreamedVolumeAndPan(m_nCurrentVolume, 63, 0, 0);
					if (m_nNextTrack < STREAMED_SOUND_CITY_AMBIENT)
						m_nLastTrackServiceTime = CTimer::GetTimeInMillisecondsPauseMode();
					m_bVerifyNextTrackStartedToPlay = true;
				}
			}
		} else {
			if (m_nPlayingTrack != NO_TRACK && !bRadioStatsRecorded) {
				m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition(0);
				m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
				RecordRadioStats();
				bRadioStatsRecorded = true;
			}
			SampleManager.SetStreamedVolumeAndPan(0, 63, 0, 0);
			SampleManager.StopStreamedFile(0);
		}
	}
}

void
cMusicManager::ServiceGameMode()
{
	CPed *ped = FindPlayerPed();
	CVehicle *vehicle = AudioManager.FindVehicleOfPlayer();
	m_bRadioStreamReady = m_bGameplayAllowsRadio;
	m_bGameplayAllowsRadio = false;

	switch (CGame::currArea)
	{
	case AREA_HOTEL:
	case AREA_MALL:
	case AREA_STRIP_CLUB:
	case AREA_DIRT:
	case AREA_BLOOD:
	case AREA_OVALRING:
	case AREA_MALIBU_CLUB:
		m_bGameplayAllowsRadio = false;
		break;
	default:
		if (SampleManager.GetMusicVolume()) {
			if (PlayerInCar())
				m_bGameplayAllowsRadio = true;
		} else
			m_bGameplayAllowsRadio = false;
		break;
	}

	if (!m_bGameplayAllowsRadio) {
		nFramesSinceCutsceneEnded = -1;
		gNumRetunePresses = 0;
		gRetuneCounter = 0;
		m_bSetNextStation = false;
	} else if (ped) {
		if(!ped->DyingOrDead() && vehicle) {
#ifdef GTA_PC
			if (SampleManager.IsMP3RadioChannelAvailable()
				&& vehicle->m_nRadioStation < USERTRACK
				&& ControlsManager.GetIsKeyboardKeyJustDown(rsF9))
			{
				if (!UsesPoliceRadio(vehicle) && !UsesTaxiRadio(vehicle)) {
					gNumRetunePresses = 0;
					gRetuneCounter = 20;
					RadioStaticCounter = 0;
					if (vehicle->m_nRadioStation < USERTRACK)
					{
						do
							++gNumRetunePresses;
						while (gNumRetunePresses + vehicle->m_nRadioStation < USERTRACK);
					}
				}
			}
#endif
			if (CPad::GetPad(0)->ChangeStationJustDown())
			{
				if (!UsesPoliceRadio(vehicle) && !UsesTaxiRadio(vehicle)) {
					gNumRetunePresses++;
					gRetuneCounter = 20;
					RadioStaticCounter = 0;
				}
			}
#ifdef RADIO_SCROLL_TO_PREV_STATION
			else if(CPad::GetPad(0)->GetMouseWheelDownJustDown() || CPad::GetPad(0)->GetMouseWheelUpJustDown()) {
				if(!UsesPoliceRadio(vehicle) && !UsesTaxiRadio(vehicle)) {
					int scrollNext = ControlsManager.GetControllerKeyAssociatedWithAction(VEHICLE_CHANGE_RADIO_STATION, MOUSE);
					int scrollPrev = scrollNext == rsMOUSEWHEELUPBUTTON ? rsMOUSEWHEELDOWNBUTTON
																		: scrollNext == rsMOUSEWHEELDOWNBUTTON ? rsMOUSEWHEELUPBUTTON : -1;

					if(scrollPrev != -1 && !ControlsManager.IsAnyVehicleActionAssignedToMouseKey(scrollPrev)) {
						gNumRetunePresses--;
						gRetuneCounter = 20;
						RadioStaticCounter = 0;
						int track = gNumRetunePresses + vehicle->m_nRadioStation;
						while(track < 0) track += NUM_RADIOS + 1;
						while(track >= NUM_RADIOS + 1) track -= NUM_RADIOS + 1;
						if(!DMAudio.IsMP3RadioChannelAvailable() && track == USERTRACK) gNumRetunePresses--;
					}
				}
			}
#endif
		}
	}

	if (m_bUserResumedGame)
	{
		m_bRadioStreamReady = false;
		m_bUserResumedGame = false;
	}
	if (m_nPlayingTrack == NO_TRACK && m_nFrontendTrack == NO_TRACK)
		m_bRadioStreamReady = false;

	if (m_bGameplayAllowsRadio)
	{
		if (!m_bRadioStreamReady)
		{
			if(vehicle == nil) {
				m_nFrontendTrack = STREAMED_SOUND_RADIO_WAVE; // huh?
				return;
			}
			if(m_bRadioSetByScript) {
				if(UsesPoliceRadio(vehicle))
					m_nFrontendTrack = STREAMED_SOUND_RADIO_POLICE;
				else if(UsesTaxiRadio(vehicle))
					m_nFrontendTrack = STREAMED_SOUND_RADIO_TAXI;
				else {
					m_nFrontendTrack = m_nRadioStationScript;
					vehicle->m_nRadioStation = m_nRadioStationScript;
				}
				if(m_nRadioPosition != -1) {
					m_aTracks[m_nFrontendTrack].m_nPosition = m_nRadioPosition;
					m_aTracks[m_nFrontendTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
				}
				m_bRadioSetByScript = false;
				return;
			}

			// This starts the radio when you enter the car.
			m_nFrontendTrack = GetCarTuning();
			return;
		}
		if (m_nAnnouncement < NO_TRACK) {
			if ((m_bAnnouncementInProgress || m_nFrontendTrack == m_nPlayingTrack) && ServiceAnnouncement()) {
				if (m_bAnnouncementInProgress) {
					m_bSetNextStation = false;
					gNumRetunePresses = 0;
					gRetuneCounter = 0;
					return;
				}
				if(m_nAnnouncement == NO_TRACK) {
					m_nNextTrack = NO_TRACK;
					m_nFrontendTrack = GetCarTuning();
					m_bSetNextStation = false;
					gRetuneCounter = 0;
					gNumRetunePresses = 0;
				}
			}
		}
		if (!m_bAnnouncementInProgress
			&& m_nAnnouncement == NO_TRACK
			&& m_nPlayingTrack == STREAMED_SOUND_RADIO_MP3_PLAYER
			&& !SampleManager.IsStreamPlaying(0))
		{
			SampleManager.StartStreamedFile(STREAMED_SOUND_RADIO_MP3_PLAYER, 0, 0);
		}

		if (!m_bRadioSetByScript)
		{
			// Because when you switch radio back and forth, gNumRetunePresses will be 0 but gRetuneCounter won't.
#ifdef RADIO_SCROLL_TO_PREV_STATION
			if(gRetuneCounter != 0) {
				if(gRetuneCounter > 1)
					gRetuneCounter--;
				else if(gRetuneCounter == 1) {
					m_bSetNextStation = true;
					gRetuneCounter = 0;
				}
			}
#else
			if (gNumRetunePresses != 0)
			{
				if (--gRetuneCounter == 0)
				{
					m_bSetNextStation = true;
					gRetuneCounter = 0;
				}
			}
#endif
			if (gRetuneCounter)
			{
				int32 station = gNumRetunePresses + vehicle->m_nRadioStation;
#ifdef RADIO_SCROLL_TO_PREV_STATION
				while (station < 0) station += NUM_RADIOS + 1;
#endif
				while (station >= NUM_RADIOS + 1) station -= NUM_RADIOS + 1;

				// Scrolling back won't hit here, so increasing isn't problem
				if (!DMAudio.IsMP3RadioChannelAvailable() && station == USERTRACK)
				{
					++gNumRetunePresses;
					station = RADIO_OFF;
				}
				if (station == RADIO_OFF)
				{
					if (gRetuneCounter == 19) // One less then what switching radio sets, so runs right after turning off radio
					{
						AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_RADIO_TURN_OFF, 0.0f);
						RadioStaticCounter = 5;
					}
				}
				else
				{
#ifdef RADIO_SCROLL_TO_PREV_STATION
					if (vehicle->m_nRadioStation == RADIO_OFF && gRetuneCounter == 19) // Right after turning on the radio
#else
					if (station == 0 && gRetuneCounter == 19) // Right after turning on the radio
#endif
						AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_RADIO_TURN_ON, 0.0f);
					AudioManager.DoPoliceRadioCrackle();
				}
			}
			if (RadioStaticCounter < 2 && CTimer::GetTimeInMilliseconds() > RadioStaticTimer + 800)
			{
				AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_RADIO_CHANGE, 0.0f);
				RadioStaticCounter++;
				RadioStaticTimer = CTimer::GetTimeInMilliseconds();
			}
			if (m_bSetNextStation)
				m_nFrontendTrack = GetNextCarTuning();
			if (m_nFrontendTrack >= STREAMED_SOUND_CITY_AMBIENT && m_nFrontendTrack <= STREAMED_SOUND_AMBSIL_AMBIENT)
				SetUpCorrectAmbienceTrack();
			ServiceTrack(vehicle, ped);
			if (m_bSetNextStation)
				m_bSetNextStation = false;
			return;
		}
		if (UsesPoliceRadio(vehicle))
			m_nFrontendTrack = STREAMED_SOUND_RADIO_POLICE;
		else if (UsesTaxiRadio(vehicle))
			m_nFrontendTrack = STREAMED_SOUND_RADIO_TAXI;
		else {
			m_nFrontendTrack = m_nRadioStationScript;
			vehicle->m_nRadioStation = m_nRadioStationScript;
		}

		if (m_nRadioPosition != -1) {
			m_aTracks[m_nFrontendTrack].m_nPosition = m_nRadioPosition;
			m_aTracks[m_nFrontendTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
		}

		gRetuneCounter = 0;
		gNumRetunePresses = 0;
		m_bSetNextStation = false;
		m_bRadioSetByScript = false;
		if (m_nFrontendTrack >= STREAMED_SOUND_CITY_AMBIENT && m_nFrontendTrack <= STREAMED_SOUND_AMBSIL_AMBIENT)
			SetUpCorrectAmbienceTrack();
		ServiceTrack(vehicle, ped);
		if (m_bSetNextStation)
			m_bSetNextStation = false;
		return;
	}

	if (m_bAnnouncementInProgress)
	{
		SampleManager.StopStreamedFile(0);
		if (SampleManager.IsStreamPlaying(0))
			return;
		g_bAnnouncementReadPosAlready = false;
		m_nAnnouncement = NO_TRACK;
		m_bAnnouncementInProgress = false;
		m_nNextTrack = NO_TRACK;
		m_nFrontendTrack = NO_TRACK;
		m_nPlayingTrack = NO_TRACK;
	}
	SetUpCorrectAmbienceTrack();
	ServiceTrack(nil, ped);
}

void
cMusicManager::SetUpCorrectAmbienceTrack()
{
	switch (CGame::currArea)
	{
	case AREA_MAIN_MAP:
	case AREA_EVERYWHERE:
		if (CTheScripts::RiotIntensity != 0 && ((TheCamera.GetPosition() - vecRiotPosition).MagnitudeSqr() < SQR(65.0f)))
			m_nFrontendTrack = STREAMED_SOUND_LAW4RIOT_AMBIENT;
		else if (TheCamera.DistanceToWater <= 90.0f) {
			if (CCullZones::bAtBeachForAudio) {
				if (CWeather::OldWeatherType != WEATHER_HURRICANE && CWeather::NewWeatherType != WEATHER_HURRICANE || CWeather::Wind <= 1.0f)
					m_nFrontendTrack = STREAMED_SOUND_BEACH_AMBIENT;
				else
					m_nFrontendTrack = STREAMED_SOUND_HAVANA_BEACH_AMBIENT;
			}
			else if (CWeather::OldWeatherType != WEATHER_HURRICANE && CWeather::NewWeatherType != WEATHER_HURRICANE || CWeather::Wind <= 1.0f)
				m_nFrontendTrack = STREAMED_SOUND_WATER_AMBIENT;
			else
				m_nFrontendTrack = STREAMED_SOUND_HAVANA_WATER_AMBIENT;
		}
		else if (CWeather::OldWeatherType != WEATHER_HURRICANE && CWeather::NewWeatherType != WEATHER_HURRICANE || CWeather::Wind <= 1.0f)
			m_nFrontendTrack = STREAMED_SOUND_CITY_AMBIENT;
		else
			m_nFrontendTrack = STREAMED_SOUND_HAVANA_CITY_AMBIENT;
		break;
	case AREA_HOTEL:
		m_nFrontendTrack = STREAMED_SOUND_HOTEL_AMBIENT;
		break;
	case AREA_MALL:
		m_nFrontendTrack = STREAMED_SOUND_MALL_AMBIENT;
		break;
	case AREA_STRIP_CLUB:
		m_nFrontendTrack = STREAMED_SOUND_STRIPCLUB_AMBIENT;
		break;
	case AREA_DIRT:
	case AREA_BLOOD:
	case AREA_OVALRING:
		m_nFrontendTrack = STREAMED_SOUND_DIRTRING_AMBIENT;
		break;
	case AREA_MALIBU_CLUB:
		m_nFrontendTrack = STREAMED_SOUND_MALIBU_AMBIENT;
		break;
	case AREA_MANSION:
	case AREA_BANK:
	case AREA_LAWYERS:
	case AREA_COFFEE_SHOP:
	case AREA_CONCERT_HALL:
	case AREA_STUDIO:
	case AREA_RIFLE_RANGE:
	case AREA_BIKER_BAR:
	case AREA_POLICE_STATION:
		m_nFrontendTrack = STREAMED_SOUND_AMBSIL_AMBIENT;
		break;
	}
}

float
GetHeightScale()
{
	if (TheCamera.GetPosition().z > 20.0f) {
		if (TheCamera.GetPosition().z < 50.0f)
			return 1.0f - (TheCamera.GetPosition().z - 20.0f) / 30.0f;
		return 0.0f;
	}
	return 1.0f;
}

void
cMusicManager::ComputeAmbienceVol(uint8 reset, uint8& outVolume)
{
	static float fVol = 0.0f;

	float fHeightScale = GetHeightScale();

	if (CTheScripts::RiotIntensity > 0) {
		float distToRiotSq = (TheCamera.GetPosition() - vecRiotPosition).MagnitudeSqr();
		if (distToRiotSq < SQR(100.0f)) {
			if (distToRiotSq >= SQR(65.0f))
				outVolume = (Sqrt(distToRiotSq) - 65.0f) / 35.0f * (127.0f * fHeightScale);
			else if (distToRiotSq >= SQR(20.0f))
				outVolume = (CTheScripts::RiotIntensity * (1.0f - (Sqrt(distToRiotSq) - 20.0f) / 45.0f) * (127.0f * fHeightScale)) / MAX_VOLUME;
			else
				outVolume = (CTheScripts::RiotIntensity * (127.0f * fHeightScale)) / MAX_VOLUME;
			return;
		}
	}

	if (reset)
		fVol = 0.0f;
	else if (fVol < 60.0f) {
		if ((m_nPlayingTrack >= STREAMED_SOUND_HAVANA_CITY_AMBIENT) && (m_nPlayingTrack <= STREAMED_SOUND_HAVANA_BEACH_AMBIENT))
			fVol += 20.0f;
		else
			fVol += 1.0f;
		fVol = Min(fVol, 60.0f);
	}

	if ((m_nPlayingTrack >= STREAMED_SOUND_MALL_AMBIENT) && (m_nPlayingTrack <= STREAMED_SOUND_AMBSIL_AMBIENT)) {
		outVolume = fVol;
		return;
	}

	if (CWeather::OldWeatherType == WEATHER_HURRICANE || CWeather::NewWeatherType == WEATHER_HURRICANE) {
		if (CWeather::Wind > 1.0f) {
			outVolume = (CWeather::Wind - 1.0f) * fVol;
			return;
		}
		fVol = (1.0f - CWeather::Wind) * fVol;
	}
	
	if (TheCamera.DistanceToWater > 140.0f) {
		outVolume = fVol;
		return;
	}

	if (TheCamera.DistanceToWater > 90.0f) {
		outVolume = ((TheCamera.DistanceToWater - 90.0f) / 50.0f * fVol * fHeightScale);
		return;
	}

	if (TheCamera.DistanceToWater > 40.0f) {
		outVolume = fVol;
		return;
	}

	outVolume = (90.0f - fHeightScale) / 50.0f * fVol;
}

bool
cMusicManager::ServiceAnnouncement()
{
	if (m_bAnnouncementInProgress) {
		if (SampleManager.IsStreamPlaying(0))
			m_nPlayingTrack = m_nNextTrack;
		else if (m_nPlayingTrack != NO_TRACK) {
			m_nAnnouncement = NO_TRACK;
			m_bAnnouncementInProgress = false;
			m_nPlayingTrack = NO_TRACK;
		}
		return true;
	} else if (SampleManager.IsStreamPlaying(0)) {
		if (m_nPlayingTrack != NO_TRACK && !g_bAnnouncementReadPosAlready) {
			RecordRadioStats();
			m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition(0);
			g_bAnnouncementReadPosAlready = true;
			m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
		}
		SampleManager.StopStreamedFile(0);
	} else {
		g_bAnnouncementReadPosAlready = false;
		m_nPlayingTrack = NO_TRACK;
		m_nNextTrack = m_nAnnouncement;
		SampleManager.SetStreamedFileLoopFlag(0, 0);
		SampleManager.StartStreamedFile(m_nNextTrack, 0, 0);
		SampleManager.SetStreamedVolumeAndPan(MAX_VOLUME, 63, 0, 0);
		m_bAnnouncementInProgress = true;
	}

	return true;
}

void
cMusicManager::ServiceTrack(CVehicle *veh, CPed *ped)
{
	static bool bRadioStatsRecorded = false;
	static bool bRadioStatsRecorded2 = false;
	uint8 volume;
	if (!m_bTrackChangeStarted)
		m_nNextTrack = m_nFrontendTrack;
	if (gRetuneCounter != 0 || m_bSetNextStation) {
		if (SampleManager.IsStreamPlaying(0)) {
			if (m_nPlayingTrack != NO_TRACK && !bRadioStatsRecorded) {
				m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition(0);
				m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
				RecordRadioStats();
				bRadioStatsRecorded = true;
			}
			SampleManager.SetStreamedVolumeAndPan(0, 63, 0, 0);
			SampleManager.StopStreamedFile(0);
		}
		return;
	}

	if (bRadioStatsRecorded) {
		bRadioStatsRecorded = false;
		m_nPlayingTrack = NO_TRACK;
	}

	if (m_nNextTrack != m_nPlayingTrack)
	{
		m_bTrackChangeStarted = true;
		SampleManager.SetStreamedVolumeAndPan(0, 63, 0, 0);
		if (!(AudioManager.m_FrameCounter & 1)) {
			if (m_bVerifyNextTrackStartedToPlay || !SampleManager.IsStreamPlaying(0)) {
				bRadioStatsRecorded2 = false;
				if (SampleManager.IsStreamPlaying(0)) {
					m_nPlayingTrack = m_nNextTrack;
					m_bVerifyNextTrackStartedToPlay = false;
					m_bTrackChangeStarted = false;
					if (veh) {
#ifdef FIX_BUGS
						if (m_nPlayingTrack >= STREAMED_SOUND_CITY_AMBIENT && m_nPlayingTrack <= STREAMED_SOUND_AMBSIL_AMBIENT)
							veh->m_nRadioStation = RADIO_OFF;
						else if (m_nPlayingTrack < STREAMED_SOUND_CITY_AMBIENT)
							veh->m_nRadioStation = m_nPlayingTrack;
#else
						if (veh->m_nRadioStation >= STREAMED_SOUND_CITY_AMBIENT && veh->m_nRadioStation <= STREAMED_SOUND_AMBSIL_AMBIENT)
							veh->m_nRadioStation = RADIO_OFF;
						else
							veh->m_nRadioStation = m_nPlayingTrack;
#endif
					}
				} else {
					uint32 pos = GetTrackStartPos(m_nNextTrack);
					if (m_nNextTrack != NO_TRACK) {
						SampleManager.SetStreamedFileLoopFlag(1, 0);
						SampleManager.StartStreamedFile(m_nNextTrack, pos, 0);
						if (m_nFrontendTrack < STREAMED_SOUND_CITY_AMBIENT || m_nFrontendTrack > STREAMED_SOUND_AMBSIL_AMBIENT)
						{
							m_nVolumeLatency = 10;
							m_nCurrentVolume = 0;
							m_nMaxVolume = 100;
							SampleManager.SetStreamedVolumeAndPan(m_nCurrentVolume, 63, 0, 0);
						}
						else
						{
							ComputeAmbienceVol(true, volume);
							SampleManager.SetStreamedVolumeAndPan(volume, 63, 1, 0);
						}
						if (m_nNextTrack < STREAMED_SOUND_CITY_AMBIENT)
							m_nLastTrackServiceTime = CTimer::GetTimeInMillisecondsPauseMode();
						m_bVerifyNextTrackStartedToPlay = true;
					}
				}
			} else {
				if (m_nPlayingTrack == NO_TRACK)
					debug("m_nPlayingTrack == NO_TRACK, yet track playing - tidying up\n");
				else if (!bRadioStatsRecorded2)
				{
					m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition(0);
					m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
					bRadioStatsRecorded2 = true;
					RecordRadioStats();
					if (m_nPlayingTrack >= STREAMED_SOUND_HAVANA_CITY_AMBIENT && m_nPlayingTrack <= STREAMED_SOUND_HAVANA_BEACH_AMBIENT)
					{
						if (m_nNextTrack >= STREAMED_SOUND_HAVANA_CITY_AMBIENT && m_nNextTrack <= STREAMED_SOUND_HAVANA_BEACH_AMBIENT)
							AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_HURRICANE, 0.0);
					}
				}
				SampleManager.SetStreamedVolumeAndPan(0, 63, 0, 0);
				SampleManager.StopStreamedFile(0);
			}
		}
		return;
	}

	if (m_nPlayingTrack >= STREAMED_SOUND_CITY_AMBIENT && m_nPlayingTrack <= STREAMED_SOUND_AMBSIL_AMBIENT)
	{
		ComputeAmbienceVol(false, volume);
		SampleManager.SetStreamedVolumeAndPan(volume, 63, 1, 0);
		return;
	}
	if (CTimer::GetIsSlowMotionActive())
	{
		if (TheCamera.pTargetEntity)
		{
			float DistToTargetSq = (TheCamera.pTargetEntity->GetPosition() - TheCamera.GetPosition()).MagnitudeSqr();
			if (DistToTargetSq >= SQR(55.0f))
			{
				SampleManager.SetStreamedVolumeAndPan(0, 63, 0, 0);
			}
			else if (DistToTargetSq >= SQR(10.0f))
			{
				volume = (45.0f - (Sqrt(DistToTargetSq) - 10.0f)) / 45.0f * m_nCurrentVolume;
				if (AudioManager.ShouldDuckMissionAudio(0) || AudioManager.ShouldDuckMissionAudio(1))
					volume /= 4;

				uint8 pan = 0;
				if (volume > 0)
				{
					CVector panVec;
					AudioManager.TranslateEntity(&TheCamera.pTargetEntity->GetPosition(), &panVec);
					pan = AudioManager.ComputePan(55.0f, &panVec);
				}
				if (gRetuneCounter != 0)
					volume = 0;
				SampleManager.SetStreamedVolumeAndPan(volume, pan, 0, 0);
			}
			else if (AudioManager.ShouldDuckMissionAudio(0) || AudioManager.ShouldDuckMissionAudio(1))
				SampleManager.SetStreamedVolumeAndPan(m_nCurrentVolume, 63, 0, 0);
			else if (gRetuneCounter != 0)
				SampleManager.SetStreamedVolumeAndPan(0, 63, 0, 0);
			else
				SampleManager.SetStreamedVolumeAndPan(m_nCurrentVolume, 63, 0, 0);
		}
	} else if (AudioManager.ShouldDuckMissionAudio(0) || AudioManager.ShouldDuckMissionAudio(1)) {
		SampleManager.SetStreamedVolumeAndPan(Min(m_nCurrentVolume, 25), 63, 0, 0);
		nFramesSinceCutsceneEnded = 0;
	} else {
		if (nFramesSinceCutsceneEnded == -1)
			volume = m_nCurrentVolume;
		else if (nFramesSinceCutsceneEnded < 20)
		{
			volume = Min(m_nCurrentVolume, 25);
			nFramesSinceCutsceneEnded++;
		}
		else if (nFramesSinceCutsceneEnded < 40)
		{
			volume = Min(m_nCurrentVolume, 3 * (nFramesSinceCutsceneEnded - 20) + 25);
			nFramesSinceCutsceneEnded++;
		}
		else
		{
			volume = m_nCurrentVolume;
			nFramesSinceCutsceneEnded = -1;
		}
		if (gRetuneCounter != 0)
			volume = 0;
		SampleManager.SetStreamedVolumeAndPan(volume, 63, 0, 0);
	}
	if (m_nVolumeLatency > 0)
		m_nVolumeLatency--;
	else if (m_nCurrentVolume < m_nMaxVolume)
		m_nCurrentVolume = Min(m_nMaxVolume, m_nCurrentVolume + 6);
}

void
cMusicManager::PreloadCutSceneMusic(uint32 track)
{
	if (IsInitialised() && !m_bDisabled && track < TOTAL_STREAMED_SOUNDS && m_nMusicMode == MUSICMODE_CUTSCENE) {
		AudioManager.ResetPoliceRadio();
		while (SampleManager.IsStreamPlaying(0))
			SampleManager.StopStreamedFile(0);
		SampleManager.PreloadStreamedFile(track, 0);
		SampleManager.SetStreamedVolumeAndPan(MAX_VOLUME, 63, 1, 0);
		m_nPlayingTrack = track;
	}
}

void
cMusicManager::PlayPreloadedCutSceneMusic(void)
{
	if (IsInitialised() && !m_bDisabled && m_nMusicMode == MUSICMODE_CUTSCENE)
		SampleManager.StartPreloadedStreamedFile(0);
}

void
cMusicManager::StopCutSceneMusic(void)
{
	if (IsInitialised() && !m_bDisabled && m_nMusicMode == MUSICMODE_CUTSCENE) {
		SampleManager.StopStreamedFile(0);
		m_nPlayingTrack = NO_TRACK;
	}
}

void
cMusicManager::PlayFrontEndTrack(uint32 track, uint8 loopFlag)
{
	if (IsInitialised() && !m_bDisabled && track < TOTAL_STREAMED_SOUNDS && (m_nUpcomingMusicMode == MUSICMODE_FRONTEND || m_nMusicMode == MUSICMODE_FRONTEND))
	{
		m_nFrontendTrack = track;
		m_FrontendLoopFlag = loopFlag;
		if (m_nMusicMode != MUSICMODE_FRONTEND)
			m_bEarlyFrontendTrack = true;
	}
}

void
cMusicManager::StopFrontEndTrack()
{
	if (m_nUpcomingMusicMode == MUSICMODE_FRONTEND || m_nMusicMode == MUSICMODE_FRONTEND)
		m_nFrontendTrack = NO_TRACK;
}

void
cMusicManager::PlayAnnouncement(uint32 announcement)
{
	if (IsInitialised() && !m_bDisabled && !m_bAnnouncementInProgress)
		m_nAnnouncement = announcement;
}

uint32
cMusicManager::GetNextCarTuning()
{
	CVehicle *veh = AudioManager.FindVehicleOfPlayer();
	if (veh == nil) return STREAMED_SOUND_CITY_AMBIENT;
	if (UsesPoliceRadio(veh)) return STREAMED_SOUND_RADIO_POLICE;
	if (UsesTaxiRadio(veh)) return STREAMED_SOUND_RADIO_TAXI;
	if (gNumRetunePresses != 0) {
#ifdef RADIO_SCROLL_TO_PREV_STATION
		// m_nRadioStation is unsigned, so...
		int station = veh->m_nRadioStation + gNumRetunePresses;
		while(station < 0) station += NUM_RADIOS + 1;
		while(station >= NUM_RADIOS + 1) station -= NUM_RADIOS + 1;
		veh->m_nRadioStation = station;
#else
		veh->m_nRadioStation += gNumRetunePresses;
		while(veh->m_nRadioStation >= NUM_RADIOS + 1)
			veh->m_nRadioStation -= NUM_RADIOS + 1;
#endif
		DMAudio.IsMP3RadioChannelAvailable(); // woof, just call and do nothing =P they manipulate gNumRetunePresses on DisplayRadioStationName in this case
		gNumRetunePresses = 0;
	}
	return veh->m_nRadioStation;
}

uint32
cMusicManager::GetCarTuning()
{
	CVehicle* veh = AudioManager.FindVehicleOfPlayer();
	if (veh == nil) return STREAMED_SOUND_CITY_AMBIENT;
	if (UsesPoliceRadio(veh)) return STREAMED_SOUND_RADIO_POLICE;
	if (UsesTaxiRadio(veh)) return STREAMED_SOUND_RADIO_TAXI;
	if (veh->m_nRadioStation == USERTRACK && !SampleManager.IsMP3RadioChannelAvailable())
		veh->m_nRadioStation = AudioManager.GetRandomNumber(2) % USERTRACK;
	return veh->m_nRadioStation;
}

float*
cMusicManager::GetListenTimeArray()
{
	return aListenTimeArray;
}

uint32
cMusicManager::GetTrackStartPos(uint32 track)
{
	if (!IsInitialised()) return 0;

	uint32 pos = m_aTracks[track].m_nPosition;
	if (CTimer::GetTimeInMillisecondsPauseMode() > m_aTracks[track].m_nLastPosCheckTimer)
		pos += Min(CTimer::GetTimeInMillisecondsPauseMode() - m_aTracks[track].m_nLastPosCheckTimer, 270000);
	else
		m_aTracks[track].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();

	if (pos > m_aTracks[track].m_nLength)
		pos %= m_aTracks[track].m_nLength;
	return pos;
}

uint32
cMusicManager::GetRadioPosition(uint32 station)
{
	if (station < NUM_RADIOS)
		return GetTrackStartPos(station);
	return 0;
}

uint32
cMusicManager::GetFavouriteRadioStation()
{
	uint32 favstation = 0;

	for (int i = 1; i < NUM_RADIOS; i++) {
		if (aListenTimeArray[i] > aListenTimeArray[favstation])
			favstation = i;
	}

	return favstation;
}

bool
cMusicManager::CheckForMusicInterruptions()
{
	return (m_nPlayingTrack == STREAMED_SOUND_MISSION_COMPLETED) || (m_nPlayingTrack == STREAMED_SOUND_CUTSCENE_FINALE);
}

void
cMusicManager::SetMalibuClubTrackPos(uint8 scriptObject)
{
	if (!IsInitialised())
		m_aTracks[STREAMED_SOUND_MALIBU_AMBIENT].m_nPosition = 8640;
	if (m_nNextTrack != STREAMED_SOUND_MALIBU_AMBIENT && m_nPlayingTrack != STREAMED_SOUND_MALIBU_AMBIENT) {
		switch (scriptObject)
		{
		case SCRIPT_SOUND_NEW_BUILDING_MALIBU_1:
			m_aTracks[STREAMED_SOUND_MALIBU_AMBIENT].m_nPosition = (AudioManager.m_anRandomTable[0] % 128) + 8640;
			break;
		case SCRIPT_SOUND_NEW_BUILDING_MALIBU_2:
			m_aTracks[STREAMED_SOUND_MALIBU_AMBIENT].m_nPosition = (AudioManager.m_anRandomTable[0] % 128) + 286720;
			break;
		case SCRIPT_SOUND_NEW_BUILDING_MALIBU_3:
			m_aTracks[STREAMED_SOUND_MALIBU_AMBIENT].m_nPosition = (AudioManager.m_anRandomTable[0] % 128) + 509120;
			break;
		}
		m_aTracks[STREAMED_SOUND_MALIBU_AMBIENT].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
	}
}

void
cMusicManager::SetStripClubTrackPos(uint8 scriptObject)
{
	if (!IsInitialised())
		m_aTracks[STREAMED_SOUND_STRIPCLUB_AMBIENT].m_nPosition = 0;
	if (m_nNextTrack != STREAMED_SOUND_STRIPCLUB_AMBIENT && m_nPlayingTrack != STREAMED_SOUND_STRIPCLUB_AMBIENT)
	{
		switch (scriptObject)
		{
		case SCRIPT_SOUND_NEW_BUILDING_STRIP_1:
			m_aTracks[STREAMED_SOUND_STRIPCLUB_AMBIENT].m_nPosition = AudioManager.m_anRandomTable[0] % 128;
			break;
		case SCRIPT_SOUND_NEW_BUILDING_STRIP_2:
			m_aTracks[STREAMED_SOUND_STRIPCLUB_AMBIENT].m_nPosition = (AudioManager.m_anRandomTable[0] % 128) + 320200;
			break;
		case SCRIPT_SOUND_NEW_BUILDING_STRIP_3:
			m_aTracks[STREAMED_SOUND_STRIPCLUB_AMBIENT].m_nPosition = (AudioManager.m_anRandomTable[0] % 128) + 672000;
			break;
		}
		m_aTracks[STREAMED_SOUND_STRIPCLUB_AMBIENT].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
	}
}

void
cMusicManager::DisplayRadioStationName()
{
	uint8 gStreamedSound;
	static wchar *pCurrentStation = nil;
	static uint8 cDisplay = 0;

	if(!CTimer::GetIsPaused() && !TheCamera.m_WideScreenOn && PlayerInCar() &&
	   !CReplay::IsPlayingBack()) {
		CVehicle *vehicle = AudioManager.FindVehicleOfPlayer();

		if (vehicle)
		{
#if defined RADIO_SCROLL_TO_PREV_STATION || defined FIX_BUGS // Because m_nFrontendTrack can have NO_TRACK
			int track;
#else
			uint8 track;
#endif
			gStreamedSound = vehicle->m_nRadioStation;
			if (gStreamedSound >= STREAMED_SOUND_CITY_AMBIENT && gStreamedSound <= STREAMED_SOUND_AMBSIL_AMBIENT)
				gStreamedSound = RADIO_OFF;
			if (gNumRetunePresses != 0)
			{
				track = gNumRetunePresses + gStreamedSound;
#ifdef RADIO_SCROLL_TO_PREV_STATION
				while (track < 0) track += NUM_RADIOS + 1;
#endif
				while (track >= NUM_RADIOS + 1) track -= NUM_RADIOS + 1;

				// We already handle this condition while scrolling back, on key press. No need to change this.
				if (!DMAudio.IsMP3RadioChannelAvailable() && track == USERTRACK)
					gNumRetunePresses++;
			}
			else
				track = m_nFrontendTrack;

			wchar* string = nil;
			switch (track) {
			case WILDSTYLE: string = TheText.Get("FEA_FM0"); break;
			case FLASH_FM: string = TheText.Get("FEA_FM1"); break;
			case KCHAT: string = TheText.Get("FEA_FM2"); break;
			case FEVER: string = TheText.Get("FEA_FM3"); break;
			case V_ROCK: string = TheText.Get("FEA_FM4"); break;
			case VCPR: string = TheText.Get("FEA_FM5"); break;
			case RADIO_ESPANTOSO: string = TheText.Get("FEA_FM6"); break;
			case EMOTION: string = TheText.Get("FEA_FM7"); break;
			case WAVE: string = TheText.Get("FEA_FM8"); break;
			case USERTRACK:
				if (!SampleManager.IsMP3RadioChannelAvailable())
					return;
				string = TheText.Get("FEA_MP3"); break;
#ifdef RADIO_OFF_TEXT
			case STREAMED_SOUND_RADIO_POLICE:
			case STREAMED_SOUND_RADIO_TAXI:
				return;
			default: {
				// Otherwise pausing-resuming game will show RADIO OFF, since radio isn't set yet
				if (m_nPlayingTrack == NO_TRACK && m_nFrontendTrack == NO_TRACK)
					return;

				extern wchar WideErrorString[];

				string = TheText.Get("FEA_NON");
				if (string == WideErrorString) {
					pCurrentStation = nil;
					return;
				}
				break;
			}
#else
			default: return;
#endif
			};

			if (pCurrentStation != string) {
				pCurrentStation = string;
				cDisplay = 60;
			}
			else {
				if (cDisplay == 0) return;
				cDisplay--;
			}

			CFont::SetJustifyOff();
			CFont::SetBackgroundOff();
			CFont::SetScale(SCREEN_SCALE_X(0.8f), SCREEN_SCALE_Y(1.35f));
			CFont::SetPropOn();
			CFont::SetFontStyle(FONT_STANDARD);
			CFont::SetCentreOn();
			CFont::SetCentreSize(SCREEN_STRETCH_X(DEFAULT_SCREEN_WIDTH));
			CFont::SetColor(CRGBA(0, 0, 0, 255));
			CFont::PrintString(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(2.0f), SCREEN_SCALE_Y(22.0f) + SCREEN_SCALE_Y(2.0f), pCurrentStation);

			if (gNumRetunePresses)
				CFont::SetColor(CRGBA(102, 133, 143, 255));
			else
				CFont::SetColor(CRGBA(147, 196, 211, 255));

			CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_SCALE_Y(22.0f), pCurrentStation);
			CFont::DrawFonts();
		}
	}
	// Always show station text after entering car. Same behaviour as III and SA.
#ifdef FIX_BUGS
	else
		pCurrentStation = nil;
#endif
}

bool
cMusicManager::UsesPoliceRadio(CVehicle *veh)
{
	switch (veh->GetModelIndex())
	{
	case MI_VCNMAV:
	case MI_POLMAV:
	case MI_COASTG:
	case MI_RHINO:
	case MI_BARRACKS:
		return true;
	case MI_MRWHOOP:
	case MI_HUNTER:
		return false;
	}
	return veh->UsesSiren();
}

bool
cMusicManager::UsesTaxiRadio(CVehicle *veh)
{
	if (veh->GetModelIndex() != MI_KAUFMAN) return false;
	return CTheScripts::bPlayerHasMetDebbieHarry;
}

void
cMusicManager::ServiceAmbience()
{
}

bool
cMusicManager::ChangeRadioChannel()
{
	return true;
}

// these two are empty
void cMusicManager::Enable() {}
void cMusicManager::Disable() {}
