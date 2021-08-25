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

#if !defined FIX_BUGS && (defined RADIO_SCROLL_TO_PREV_STATION || defined RADIO_OFF_TEXT)
static_assert(false, "RADIO_SCROLL_TO_PREV_STATION and RADIO_OFF_TEXT won't work correctly without FIX_BUGS");
#endif

cMusicManager MusicManager;
int32 gNumRetunePresses;
int32 gRetuneCounter;
bool8 bHasStarted;

cMusicManager::cMusicManager()
{
	m_bIsInitialised = FALSE;
	m_bDisabled = FALSE;
	m_nMusicMode = MUSICMODE_DISABLED;
	m_nNextTrack = NO_TRACK;
	m_nPlayingTrack = NO_TRACK;
	m_bFrontendTrackFinished = FALSE;
	m_bPlayInFrontend = FALSE;
	m_bSetNextStation = FALSE;
	m_nAnnouncement = NO_TRACK;
	m_bPreviousPlayerInCar = FALSE;
	m_bPlayerInCar = FALSE;
	m_bAnnouncementInProgress = FALSE;
	m_bVerifyAmbienceTrackStartedToPlay = FALSE;
	bHasStarted = FALSE;
}

bool8
cMusicManager::PlayerInCar()
{
	if(!FindPlayerVehicle())
		return FALSE;

	int32 State = FindPlayerPed()->m_nPedState;

	if(State == PED_DRAG_FROM_CAR || State == PED_EXIT_CAR || State == PED_ARRESTED)
		return FALSE;

	if (!FindPlayerVehicle())
		return TRUE;

	if (FindPlayerVehicle()->GetStatus() == STATUS_WRECKED)
		return FALSE;

	switch (FindPlayerVehicle()->GetModelIndex()) {
	case MI_FIRETRUCK:
	case MI_AMBULAN:
	case MI_MRWHOOP:
	case MI_PREDATOR:
	case MI_TRAIN:
	case MI_SPEEDER:
	case MI_REEFER:
	case MI_GHOST: return FALSE;
	default: return TRUE;
	}
}

void
cMusicManager::DisplayRadioStationName()
{
	int8 pRetune;
	int8 gStreamedSound;
	int8 gRetuneCounter;
	static wchar *pCurrentStation = nil;
	static uint8 cDisplay = 0;

	if(!CTimer::GetIsPaused() && !TheCamera.m_WideScreenOn && PlayerInCar() &&
	   !CReplay::IsPlayingBack()) {
		if(m_bPlayerInCar && !m_bPreviousPlayerInCar)
			pCurrentStation = nil;

#ifdef FIX_BUGS
		const int curRadio = GetCarTuning();
#else
		const int curRadio = m_nNextTrack;
#endif

#ifdef RADIO_SCROLL_TO_PREV_STATION
		if(gNumRetunePresses < 0) {
			gStreamedSound = curRadio;

			gRetuneCounter = gNumRetunePresses;
			pRetune = gStreamedSound;

			while(gRetuneCounter < 0) {
				if(pRetune == HEAD_RADIO) {
					pRetune = RADIO_OFF;
				} else if(pRetune == RADIO_OFF || pRetune == NUM_RADIOS) {
					pRetune =  SampleManager.IsMP3RadioChannelAvailable() ? USERTRACK : USERTRACK - 1;
				} else
					pRetune--;

				++gRetuneCounter;
			}
		} else
#endif
		if(SampleManager.IsMP3RadioChannelAvailable()) {
			gStreamedSound = curRadio;

			if(gStreamedSound == STREAMED_SOUND_CITY_AMBIENT ||
			   gStreamedSound == STREAMED_SOUND_WATER_AMBIENT) { // which means OFF
				gStreamedSound = NUM_RADIOS;
			} else if(gStreamedSound > STREAMED_SOUND_RADIO_MP3_PLAYER)
				return;

			pRetune = gNumRetunePresses + gStreamedSound;

#ifdef FIX_BUGS
			while(pRetune > NUM_RADIOS)
				pRetune -= (NUM_RADIOS + 1);
#endif
			if(pRetune == NUM_RADIOS) {
				pRetune = RADIO_OFF;
			}
#ifndef FIX_BUGS
			else if(pRetune > NUM_RADIOS) {
				pRetune = pRetune - (NUM_RADIOS + 1);
			}
#endif
		} else {
			gStreamedSound = curRadio;
			pRetune = gNumRetunePresses + gStreamedSound;

			if(pRetune >= USERTRACK) {
				gRetuneCounter = gNumRetunePresses;
				pRetune = curRadio;

				if(gStreamedSound == STREAMED_SOUND_WATER_AMBIENT)
					pRetune = STREAMED_SOUND_CITY_AMBIENT; // which is RADIO_OFF

				while(gRetuneCounter) {
					if(pRetune == RADIO_OFF) {
						pRetune = HEAD_RADIO;
					} else if(pRetune < USERTRACK) {
						pRetune = pRetune + 1;
					}
					if(pRetune == USERTRACK) pRetune = RADIO_OFF;

					--gRetuneCounter;
				}
			}
		}

		wchar *string;

		switch(pRetune) {
		case HEAD_RADIO: string = TheText.Get("FEA_FM0"); break;
		case DOUBLE_CLEF: string = TheText.Get("FEA_FM1"); break;
		case JAH_RADIO: string = TheText.Get("FEA_FM2"); break;
		case RISE_FM: string = TheText.Get("FEA_FM3"); break;
		case LIPS_106: string = TheText.Get("FEA_FM4"); break;
		case GAME_FM: string = TheText.Get("FEA_FM5"); break;
		case MSX_FM: string = TheText.Get("FEA_FM6"); break;
		case FLASHBACK: string = TheText.Get("FEA_FM7"); break;
		case CHATTERBOX: string = TheText.Get("FEA_FM8"); break;
		case USERTRACK:
			if (!SampleManager.IsMP3RadioChannelAvailable())
				return;
			string = TheText.Get("FEA_FM9"); break;
#ifdef RADIO_OFF_TEXT
		case RADIO_OFF: {
			extern wchar WideErrorString[];

			string = TheText.Get("FEA_FMN");
			if(string == WideErrorString) {
				pCurrentStation = nil;
				return;
			}
			break;
		}
#endif
		default: return;
		};

		if(pCurrentStation != string ||
			m_nNextTrack == STREAMED_SOUND_RADIO_MP3_PLAYER && m_nPlayingTrack != STREAMED_SOUND_RADIO_MP3_PLAYER) {
			pCurrentStation = string;
			cDisplay = 60;
		} else {
			if(cDisplay == 0) return;
#ifdef FIX_BUGS
			cDisplay -= CTimer::GetLogicalFramesPassed();
#else
			cDisplay--;
#endif
		}

		CFont::SetJustifyOff();
		CFont::SetBackgroundOff();
		CFont::SetScale(SCREEN_SCALE_X(0.8f), SCREEN_SCALE_Y(1.35f));
		CFont::SetPropOn();
		CFont::SetFontStyle(FONT_HEADING);
		CFont::SetCentreOn();
		// Reminder: Game doesn't have "scaling" at all, it just stretches, and it's team's decision here to not let centered text occupy all the screen.
		//				Disable ASPECT_RATIO_SCALE and it'll go back to default behaviour; stretching.
		CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH));
		CFont::SetColor(CRGBA(0, 0, 0, 255));
#ifdef FIX_BUGS
		CFont::PrintString(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(2.0f), SCREEN_SCALE_Y(22.0f) + SCREEN_SCALE_Y(2.0f), pCurrentStation);
#else
		CFont::PrintString(SCREEN_WIDTH / 2 + 2.0f, SCREEN_SCALE_Y(22.0f) + 2.0f, pCurrentStation);
#endif

		if(gNumRetunePresses)
			CFont::SetColor(CRGBA(102, 133, 143, 255));
		else
			CFont::SetColor(CRGBA(147, 196, 211, 255));

		CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_SCALE_Y(22.0f), pCurrentStation);
		CFont::DrawFonts();
	}
}

bool8
cMusicManager::Initialise()
{
	int pos;

	if (!IsInitialised()) {
		time_t timevalue = time(0);
		if (timevalue == -1) {
			pos = AudioManager.m_anRandomTable[0];
		} else {
			tm *pTm = localtime(&timevalue);
			if (pTm->tm_sec == 0)
				pTm->tm_sec = AudioManager.m_anRandomTable[0];
			if (pTm->tm_min == 0)
				pTm->tm_min = AudioManager.m_anRandomTable[1];
			if (pTm->tm_hour == 0)
				pTm->tm_hour = AudioManager.m_anRandomTable[2];
			if (pTm->tm_mday == 0)
				pTm->tm_mday = AudioManager.m_anRandomTable[3];
			if (pTm->tm_mon == 0)
				pTm->tm_mon = AudioManager.m_anRandomTable[4];
			if (pTm->tm_year == 0)
				pTm->tm_year = AudioManager.m_anRandomTable[3];
			if (pTm->tm_wday == 0)
				pTm->tm_wday = AudioManager.m_anRandomTable[2];
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
			m_aTracks[i].m_nPosition = pos * AudioManager.m_anRandomTable[i % 5] % m_aTracks[i].m_nLength;
			m_aTracks[i].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
		}

		m_bResetTimers = FALSE;
		m_nResetTime = 0;
		m_nTimer = m_nLastTrackServiceTime = CTimer::GetTimeInMillisecondsPauseMode();
		m_bDoTrackService = FALSE;
		m_bIgnoreTimeDelay = FALSE;
		m_bRadioSetByScript = FALSE;
		m_nRadioStationScript = HEAD_RADIO;
		m_nRadioPosition = -1;
		m_nRadioInCar = NO_TRACK;
		gNumRetunePresses = 0;
		gRetuneCounter = 0;
		m_bIsInitialised = TRUE;
	}
	return m_bIsInitialised;
}

void
cMusicManager::Terminate()
{
	if (!IsInitialised()) return;

	if (SampleManager.IsStreamPlaying()) {
		SampleManager.StopStreamedFile();
		m_nNextTrack = NO_TRACK;
		m_nPlayingTrack = NO_TRACK;
	}
	m_bIsInitialised = FALSE;
}

void
cMusicManager::ChangeMusicMode(uint8 mode)
{
	if (!IsInitialised()) return;

	uint8 mode2;
	switch (mode)
	{
	case MUSICMODE_FRONTEND:
		mode2 = MUSICMODE_FRONTEND;
#ifdef PAUSE_RADIO_IN_FRONTEND
		// rewind those streams we weren't listening right now
		for (uint32 i = STREAMED_SOUND_RADIO_HEAD; i < STREAMED_SOUND_CUTSCENE_LUIGI1_LG; i++) {
			m_aTracks[i].m_nPosition = GetTrackStartPos(i);
			m_aTracks[i].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
		}
#endif
		break;
	case MUSICMODE_GAME: mode2 = MUSICMODE_GAME; break;
	case MUSICMODE_CUTSCENE: mode2 = MUSICMODE_CUTSCENE; break;
	case MUSICMODE_DISABLE: mode2 = MUSICMODE_DISABLED; break;
	default: return;
	}

	if (mode2 != m_nMusicMode || mode == MUSICMODE_FRONTEND && mode2 == MUSICMODE_FRONTEND) {
		switch (mode)
		{
		case MUSICMODE_FRONTEND:
		case MUSICMODE_GAME:
		case MUSICMODE_CUTSCENE:
		case MUSICMODE_DISABLED:
			if (SampleManager.IsStreamPlaying()) {
				if (m_nNextTrack < TOTAL_STREAMED_SOUNDS) {
					m_aTracks[m_nNextTrack].m_nPosition = SampleManager.GetStreamedFilePosition();
					m_aTracks[m_nNextTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
				}
				SampleManager.StopStreamedFile();
			}
			m_nNextTrack = NO_TRACK;
			m_nPlayingTrack = NO_TRACK;
			m_bFrontendTrackFinished = FALSE;
			m_bPlayInFrontend = FALSE;
			m_bSetNextStation = FALSE;
			m_bPreviousPlayerInCar = FALSE;
			m_bPlayerInCar = FALSE;
			m_bAnnouncementInProgress = FALSE;
			m_nTimer = m_nLastTrackServiceTime = CTimer::GetTimeInMillisecondsPauseMode();
			m_bDoTrackService = FALSE;
			m_bIgnoreTimeDelay = TRUE;
			m_bVerifyAmbienceTrackStartedToPlay = FALSE;
			m_nMusicMode = mode2;
			break;
		default: return;
		}
	}
}

uint8
cMusicManager::GetRadioInCar(void)
{
	if (!m_bIsInitialised) return HEAD_RADIO;
	if (PlayerInCar()) {
		CVehicle *veh = FindPlayerVehicle();
		if (veh != nil){
			if (UsesPoliceRadio(veh)) {
				if (m_nRadioInCar == NO_TRACK || (CReplay::IsPlayingBack() && !AudioManager.m_bIsPaused))
					return POLICE_RADIO;
				return m_nRadioInCar;
			} else return veh->m_nRadioStation;
		}
	}

	if (m_nRadioInCar == NO_TRACK || (CReplay::IsPlayingBack() && !AudioManager.m_bIsPaused))
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
		CVehicle *veh = FindPlayerVehicle();
		if (veh == nil) return;
		if (UsesPoliceRadio(veh))
			m_nRadioInCar = station;
		else
			veh->m_nRadioStation = station;
	}
}

void
cMusicManager::SetRadioChannelByScript(uint8 station, int32 pos)
{
	if (m_bIsInitialised && station < RADIO_OFF) {
		m_bRadioSetByScript = TRUE;
		m_nRadioStationScript = station;
		m_nRadioPosition = pos == -1 ? -1 : pos % m_aTracks[station].m_nLength;
	}
}


void
cMusicManager::ResetMusicAfterReload()
{
	m_bRadioSetByScript = FALSE;
	m_nRadioStationScript = 0;
	m_nRadioPosition = -1;
	m_nAnnouncement = NO_TRACK;
	m_bAnnouncementInProgress = FALSE;
	m_bSetNextStation = FALSE;
	gRetuneCounter = 0;
	gNumRetunePresses = 0;
}


void
cMusicManager::ResetTimers(uint32 time)
{
	m_bResetTimers = TRUE;
	m_nResetTime = time;
}

void
cMusicManager::Service()
{
	if (m_bResetTimers) {
		m_bResetTimers = FALSE;
		m_nLastTrackServiceTime = m_nResetTime;
	}

	if (!m_bIsInitialised || m_bDisabled) return;

	if (m_nMusicMode == MUSICMODE_CUTSCENE) {
		SampleManager.SetStreamedVolumeAndPan(MAX_VOLUME, 63, TRUE);
		return;
	}

	m_nTimer = CTimer::GetTimeInMillisecondsPauseMode();
	if (m_nTimer > (m_nLastTrackServiceTime + 2000) || m_bIgnoreTimeDelay) {
		m_bIgnoreTimeDelay = FALSE;
		m_bDoTrackService = TRUE;
		m_nLastTrackServiceTime = m_nTimer;
	} else m_bDoTrackService = FALSE;

	if (m_nNextTrack == NO_TRACK && SampleManager.IsStreamPlaying())
		SampleManager.StopStreamedFile();
	else switch (m_nMusicMode) {
		case MUSICMODE_FRONTEND: ServiceFrontEndMode(); break;
		case MUSICMODE_GAME: ServiceGameMode(); break;
		}
}

void
cMusicManager::ServiceFrontEndMode()
{
#ifdef PAUSE_RADIO_IN_FRONTEND
	// pause radio
	for (uint32 i = STREAMED_SOUND_RADIO_HEAD; i < STREAMED_SOUND_CUTSCENE_LUIGI1_LG; i++)
		m_aTracks[i].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
#endif

	if (m_nNextTrack < TOTAL_STREAMED_SOUNDS) {
		if (m_bFrontendTrackFinished) {
			if (!SampleManager.IsStreamPlaying()) {
				switch (m_nNextTrack)
				{
				case STREAMED_SOUND_MISSION_COMPLETED:
					if (!AudioManager.m_bIsPaused)
						ChangeMusicMode(MUSICMODE_GAME);
					break;
				case STREAMED_SOUND_GAME_COMPLETED:
					ChangeMusicMode(MUSICMODE_GAME);
					break;
				default:
					break;
				}
				m_nNextTrack = NO_TRACK;
				m_nPlayingTrack = NO_TRACK;
			}
		} else if (bHasStarted) {
			if (!SampleManager.IsStreamPlaying())
				SampleManager.StartStreamedFile(m_nNextTrack, 0);
		} else {
			SampleManager.SetStreamedVolumeAndPan(0, 63, FALSE);
			if (!SampleManager.StartStreamedFile(m_nNextTrack, m_nNextTrack < NUM_RADIOS ? GetTrackStartPos(m_nNextTrack) : 0))
				return;
			SampleManager.SetStreamedVolumeAndPan(100, 63, FALSE);
			if (m_bPlayInFrontend) bHasStarted = TRUE;
			else m_bFrontendTrackFinished = TRUE;
		}
	}
	if (SampleManager.IsStreamPlaying())
		SampleManager.SetStreamedVolumeAndPan((CPad::GetPad(0)->bDisplayNoControllerMessage || CPad::GetPad(0)->bObsoleteControllerMessage) ? 0 : 100, 63, FALSE);
}

void
cMusicManager::ServiceGameMode()
{
	bool8 bRadioOff = FALSE;
	static int8 nFramesSinceCutsceneEnded = -1;
	uint8 volume;

	m_bPreviousPlayerInCar = m_bPlayerInCar;
	m_bPlayerInCar = PlayerInCar();
	m_nPlayingTrack = m_nNextTrack;
	if (m_bPlayerInCar) {
		if (FindPlayerPed() != nil
			&& !FindPlayerPed()->DyingOrDead()
			&& !CReplay::IsPlayingBack()
			&& FindPlayerVehicle() != nil
			&& !UsesPoliceRadio(FindPlayerVehicle())) {

				if (CPad::GetPad(0)->ChangeStationJustDown()) {
					gRetuneCounter = 30;
					gNumRetunePresses++;
					AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_RADIO_CHANGE, 1.0f);
					// This needs loop, and this is not the right place. Now done elsewhere.
#ifndef FIX_BUGS
					if (SampleManager.IsMP3RadioChannelAvailable()) {
						if (gNumRetunePresses > RADIO_OFF)
							gNumRetunePresses -= RADIO_OFF;
					}
#endif
				}
#ifdef RADIO_SCROLL_TO_PREV_STATION
				else if(!CPad::GetPad(0)->ArePlayerControlsDisabled() && (CPad::GetPad(0)->GetMouseWheelDownJustDown() || CPad::GetPad(0)->GetMouseWheelUpJustDown())) {
					int scrollNext = ControlsManager.GetControllerKeyAssociatedWithAction(VEHICLE_CHANGE_RADIO_STATION, MOUSE);
					int scrollPrev = scrollNext == rsMOUSEWHEELUPBUTTON ? rsMOUSEWHEELDOWNBUTTON : scrollNext == rsMOUSEWHEELDOWNBUTTON ? rsMOUSEWHEELUPBUTTON : -1;

					if (scrollPrev != -1 && !ControlsManager.IsAnyVehicleActionAssignedToMouseKey(scrollPrev)) {
						gRetuneCounter = 30;
						gNumRetunePresses--;
						AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_RADIO_CHANGE, 1.0f);
					}
				}
#endif
		}
	} else {
		nFramesSinceCutsceneEnded = -1;
	}

	if (AudioManager.m_bWasPaused)
		m_bPreviousPlayerInCar = FALSE;
	if (!m_bPlayerInCar) {
		if (m_bPreviousPlayerInCar) {
			if (m_nNextTrack != STREAMED_SOUND_RADIO_POLICE)
				m_nRadioInCar = m_nNextTrack;
		}
		ServiceAmbience();
		return;
	}

	if (m_bPreviousPlayerInCar) {
		if (m_nAnnouncement < TOTAL_STREAMED_SOUNDS
			&& (m_nNextTrack < RADIO_OFF || m_bAnnouncementInProgress)
			&& ServiceAnnouncement())
		{
			if (m_bAnnouncementInProgress) {
				m_bSetNextStation = FALSE;
				return;
			}
			m_nPlayingTrack = m_nNextTrack;
			m_nNextTrack = GetCarTuning();
		}
		if (SampleManager.IsMP3RadioChannelAvailable()
			&& m_nNextTrack != STREAMED_SOUND_RADIO_MP3_PLAYER
			&& ControlsManager.GetIsKeyboardKeyJustDown(rsF9))
		{
			m_nPlayingTrack = m_nNextTrack;
			m_nNextTrack = STREAMED_SOUND_RADIO_MP3_PLAYER;
			if (FindPlayerVehicle() != nil)
				FindPlayerVehicle()->m_nRadioStation = STREAMED_SOUND_RADIO_MP3_PLAYER;
			AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_RADIO_CHANGE, 1.0f);
			gRetuneCounter = 0;
			gNumRetunePresses = 0;
			m_bSetNextStation = FALSE;
		}
		// Because when you switch radio back and forth, gNumRetunePresses will be 0 but gRetuneCounter won't.
#ifdef RADIO_SCROLL_TO_PREV_STATION
		if (gRetuneCounter != 0) {
			if (gRetuneCounter > 1) gRetuneCounter--;
			else if (gRetuneCounter == 1) gRetuneCounter = -1;
			else if (gRetuneCounter == -1) {
				m_bSetNextStation = TRUE;
				gRetuneCounter = 0;
			}
		}
#else
		if (gNumRetunePresses) {
			if (gRetuneCounter != 0) gRetuneCounter--;
			else m_bSetNextStation = TRUE;
		}
#endif
		if (gRetuneCounter)
			AudioManager.DoPoliceRadioCrackle();
		if (m_bSetNextStation) {
			m_bSetNextStation = FALSE;
			m_nPlayingTrack = m_nNextTrack;
			m_nNextTrack = GetNextCarTuning();
			if (m_nNextTrack == STREAMED_SOUND_CITY_AMBIENT || m_nNextTrack == STREAMED_SOUND_WATER_AMBIENT)
				bRadioOff = TRUE;

			if (m_nPlayingTrack == STREAMED_SOUND_CITY_AMBIENT || m_nPlayingTrack == STREAMED_SOUND_WATER_AMBIENT)
				AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_RADIO_CHANGE, 0.0f);
		}
		if (m_nNextTrack < RADIO_OFF) {
			if (ChangeRadioChannel()) {
				ServiceTrack();
			} else {
				m_bPlayerInCar = FALSE;
				if (FindPlayerVehicle())
					FindPlayerVehicle()->m_nRadioStation = m_nNextTrack;
				m_nNextTrack = NO_TRACK;
			}
			if (CTimer::GetIsSlowMotionActive()) {
				if (TheCamera.pTargetEntity != nil) {
					float DistToTargetSq = (TheCamera.pTargetEntity->GetPosition() - TheCamera.GetPosition()).MagnitudeSqr();
					if (DistToTargetSq >= SQR(55.0f)) {
						SampleManager.SetStreamedVolumeAndPan(0, 63, FALSE);
					} else if (DistToTargetSq >= SQR(10.0f)) {
						volume = ((45.0f - (Sqrt(DistToTargetSq) - 10.0f)) / 45.0f * 100.0f);
						uint8 pan;
						if (AudioManager.ShouldDuckMissionAudio())
							volume /= 4;
						if (volume > 0) {
							CVector panVec;
							AudioManager.TranslateEntity(&TheCamera.pTargetEntity->GetPosition(), &panVec);
							pan = AudioManager.ComputePan(55.0f, &panVec);
						} else {
							pan = 0;
						}
						if (gRetuneCounter)
							volume /= 4;
						SampleManager.SetStreamedVolumeAndPan(volume, pan, FALSE);
					} else if (AudioManager.ShouldDuckMissionAudio()) {
						SampleManager.SetStreamedVolumeAndPan(25, 63, FALSE);
					} else if (gRetuneCounter) {
						SampleManager.SetStreamedVolumeAndPan(25, 63, FALSE);
					} else {
						SampleManager.SetStreamedVolumeAndPan(100, 63, FALSE);
					}
				}
			} else if (AudioManager.ShouldDuckMissionAudio()) {
				SampleManager.SetStreamedVolumeAndPan(25, 63, FALSE);
				nFramesSinceCutsceneEnded = 0;
			} else {
				if (nFramesSinceCutsceneEnded == -1) {
					volume = 100;
				} else if (nFramesSinceCutsceneEnded < 20) {
					nFramesSinceCutsceneEnded++;
					volume = 25;
				} else if (nFramesSinceCutsceneEnded < 40) {
					volume = 3 * (nFramesSinceCutsceneEnded - 20) + 25;
					nFramesSinceCutsceneEnded++;
				} else {
					nFramesSinceCutsceneEnded = -1;
					volume = 100;
				}
				if (gRetuneCounter != 0)
					volume /= 4;
				SampleManager.SetStreamedVolumeAndPan(volume, 63, FALSE);
			}
			return;
		}
		if (bRadioOff) {
			m_nNextTrack = m_nPlayingTrack;
			if (FindPlayerVehicle() != nil)
				FindPlayerVehicle()->m_nRadioStation = RADIO_OFF;
			AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, SOUND_FRONTEND_RADIO_TURN_OFF, 0.0f);
		}
		ServiceAmbience();
		return;
	}
	if (m_bRadioSetByScript) {
		if (UsesPoliceRadio(FindPlayerVehicle())) {
			m_nNextTrack = STREAMED_SOUND_RADIO_POLICE;
		} else {
			m_nNextTrack = m_nRadioStationScript;
			if (FindPlayerVehicle()->m_nRadioStation == m_nNextTrack) {
				m_nPlayingTrack = NO_TRACK;
				SampleManager.SetStreamedVolumeAndPan(0, 63, FALSE);
				SampleManager.StopStreamedFile();
			}
			if (m_nRadioPosition != -1) {
				m_aTracks[m_nNextTrack].m_nPosition = m_nRadioPosition;
				m_aTracks[m_nNextTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
			}
		}
	} else {
		m_nNextTrack = GetCarTuning();
	}
	if (m_nNextTrack >= RADIO_OFF) {
		ServiceAmbience();
		return;
	}
	if (ChangeRadioChannel()) {
		if (m_bRadioSetByScript) {
			m_bRadioSetByScript = FALSE;
			FindPlayerVehicle()->m_nRadioStation = m_nNextTrack;
		}
	} else {
		m_bPlayerInCar = FALSE;
		m_nNextTrack = NO_TRACK;
	}
}

void
cMusicManager::StopFrontEndTrack()
{
	if (IsInitialised() && !m_bDisabled && m_nMusicMode == MUSICMODE_FRONTEND && m_nNextTrack != NO_TRACK) {
		m_aTracks[m_nNextTrack].m_nPosition = SampleManager.GetStreamedFilePosition();
		m_aTracks[m_nNextTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
		SampleManager.StopStreamedFile();
		m_nPlayingTrack = NO_TRACK;
		m_nNextTrack = NO_TRACK;
	}
}

void
cMusicManager::PlayAnnouncement(uint8 announcement)
{
	if (IsInitialised() && !m_bDisabled && !m_bAnnouncementInProgress)
		m_nAnnouncement = announcement;
}

void
cMusicManager::PlayFrontEndTrack(uint8 track, bool8 bPlayInFrontend)
{
	if (IsInitialised() && !m_bDisabled && track < TOTAL_STREAMED_SOUNDS) {
		if (m_nMusicMode == MUSICMODE_GAME) {
			if (m_nNextTrack != NO_TRACK) {
				if (m_bAnnouncementInProgress) {
					m_nAnnouncement = NO_TRACK;
					m_bAnnouncementInProgress = FALSE;
				}
				m_aTracks[m_nNextTrack].m_nPosition = SampleManager.GetStreamedFilePosition();
				m_aTracks[m_nNextTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
			}
			SampleManager.StopStreamedFile();
		} else if (m_nMusicMode == MUSICMODE_FRONTEND) {
			if (m_nNextTrack != NO_TRACK) {
				m_aTracks[m_nNextTrack].m_nPosition = SampleManager.GetStreamedFilePosition();
				m_aTracks[m_nNextTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
			}
			SampleManager.StopStreamedFile();
		}

		m_nPlayingTrack = m_nNextTrack;
		m_nNextTrack = track;
		m_bPlayInFrontend = bPlayInFrontend;
		m_bFrontendTrackFinished = FALSE;
		m_bDoTrackService = TRUE;
		bHasStarted = FALSE;
		if (m_nNextTrack < NUM_RADIOS) {
			gRetuneCounter = 0;
			gNumRetunePresses = 0;
		}
	}
}

void
cMusicManager::PreloadCutSceneMusic(uint8 track)
{
	if (IsInitialised() && !m_bDisabled && track < TOTAL_STREAMED_SOUNDS && m_nMusicMode == MUSICMODE_CUTSCENE) {
		AudioManager.ResetPoliceRadio();
		while (SampleManager.IsStreamPlaying())
			SampleManager.StopStreamedFile();
		SampleManager.PreloadStreamedFile(track);
		SampleManager.SetStreamedVolumeAndPan(MAX_VOLUME, 63, TRUE);
		m_nNextTrack = track;
	}
}

void
cMusicManager::PlayPreloadedCutSceneMusic(void)
{
	if (IsInitialised() && !m_bDisabled && m_nMusicMode == MUSICMODE_CUTSCENE)
		SampleManager.StartPreloadedStreamedFile();
}

void
cMusicManager::StopCutSceneMusic(void)
{
	if (IsInitialised() && !m_bDisabled && m_nMusicMode == MUSICMODE_CUTSCENE) {
		SampleManager.StopStreamedFile();
		m_nNextTrack = NO_TRACK;
	}
}

uint32
cMusicManager::GetTrackStartPos(uint8 track)
{
	uint32 pos = m_aTracks[track].m_nPosition;
	if (CTimer::GetTimeInMillisecondsPauseMode() > m_aTracks[track].m_nLastPosCheckTimer)
		pos += Min(CTimer::GetTimeInMillisecondsPauseMode() - m_aTracks[track].m_nLastPosCheckTimer, 90000);
	else
		m_aTracks[track].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();

	if (pos > m_aTracks[track].m_nLength)
		pos %= m_aTracks[track].m_nLength;
	return pos;
}


bool8
cMusicManager::UsesPoliceRadio(CVehicle *veh)
{
	switch (veh->GetModelIndex())
	{
	case MI_FBICAR:
	case MI_POLICE:
	case MI_ENFORCER:
	case MI_PREDATOR:
	case MI_RHINO:
	case MI_BARRACKS:
		return TRUE;
	}
	return FALSE;
}

void
cMusicManager::ServiceAmbience()
{
	uint8 volume;

	if (m_bAnnouncementInProgress) {
		m_nAnnouncement = NO_TRACK;
		m_bAnnouncementInProgress = FALSE;
	}
	if (m_nNextTrack < RADIO_OFF) {
		if (SampleManager.IsStreamPlaying()) {
			m_aTracks[m_nNextTrack].m_nPosition = SampleManager.GetStreamedFilePosition();
			m_aTracks[m_nNextTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
			SampleManager.StopStreamedFile();
			m_nNextTrack = NO_TRACK;
			return;
		}
		m_nNextTrack = RADIO_OFF;
	}
	if (CWorld::Players[CWorld::PlayerInFocus].m_WBState != WBSTATE_PLAYING && !SampleManager.IsStreamPlaying()) {
		m_nNextTrack = NO_TRACK;
		return;
	}

	m_nPlayingTrack = m_nNextTrack;
	m_nNextTrack = TheCamera.DistanceToWater <= 45.0f ? STREAMED_SOUND_WATER_AMBIENT : STREAMED_SOUND_CITY_AMBIENT;

	if (m_nNextTrack == m_nPlayingTrack) {
		ComputeAmbienceVol(FALSE, volume);
		SampleManager.SetStreamedVolumeAndPan(volume, 63, TRUE);
		if (m_bVerifyAmbienceTrackStartedToPlay) {
			if (SampleManager.IsStreamPlaying())
				m_bVerifyAmbienceTrackStartedToPlay = FALSE;
		} else ServiceTrack();
	} else {
		if (m_nPlayingTrack < TOTAL_STREAMED_SOUNDS) {
			m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition();
			m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
			SampleManager.StopStreamedFile();
		}
		uint32 pos = GetTrackStartPos(m_nNextTrack);
		SampleManager.SetStreamedVolumeAndPan(0, 63, TRUE);
		if (SampleManager.StartStreamedFile(m_nNextTrack, pos)) {
			ComputeAmbienceVol(TRUE, volume);
			SampleManager.SetStreamedVolumeAndPan(volume, 63, TRUE);
			m_bVerifyAmbienceTrackStartedToPlay = TRUE;
		} else
			m_nNextTrack = NO_TRACK;
	}
}

void
cMusicManager::ComputeAmbienceVol(bool8 reset, uint8 &outVolume)
{
	static float fVol = 0.0f;

	if (reset)
		fVol = 0.0f;
	else if (fVol < 60.0f)
		fVol += 1.0f;

	if (TheCamera.DistanceToWater > 70.0f)
		outVolume = fVol;
	else if (TheCamera.DistanceToWater > 45.0f)
		outVolume = (TheCamera.DistanceToWater - 45.0f) / 25.0f * fVol;
	else if (TheCamera.DistanceToWater > 20.0f)
		outVolume = (45.0f - TheCamera.DistanceToWater) / 25.0f * fVol;
	else
		outVolume = fVol;
}

void
cMusicManager::ServiceTrack()
{
	if (m_bDoTrackService) {
		if (!SampleManager.IsStreamPlaying())
			SampleManager.StartStreamedFile(m_nNextTrack, 0);
	}
}

bool8
cMusicManager::ServiceAnnouncement()
{
	static int8 cCheck = 0;
	if (m_bAnnouncementInProgress) {
		if (!SampleManager.IsStreamPlaying()) {
			m_nAnnouncement = NO_TRACK;
			m_bAnnouncementInProgress = FALSE;
		}
		return TRUE;
	}

	if (++cCheck >= 30) {
		cCheck = 0;
		int pos = SampleManager.GetStreamedFilePosition();
		if (SampleManager.IsStreamPlaying()) {
			if (m_nNextTrack != NO_TRACK) {
				m_aTracks[m_nNextTrack].m_nPosition = pos;
				m_aTracks[m_nNextTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
				SampleManager.StopStreamedFile();
			}
		}

		SampleManager.SetStreamedVolumeAndPan(0, 63, FALSE);
		if (SampleManager.StartStreamedFile(m_nAnnouncement, 0)) {
			SampleManager.SetStreamedVolumeAndPan(AudioManager.ShouldDuckMissionAudio() ? 25 : 100, 63, FALSE);
			m_bAnnouncementInProgress = TRUE;
			m_nPlayingTrack = m_nNextTrack;
			m_nNextTrack = m_nAnnouncement;
			return TRUE;
		}

		if (cCheck != 0) cCheck--;
		else cCheck = 30;
		return FALSE;
	}

	return FALSE;
}

uint8
cMusicManager::GetCarTuning()
{
	CVehicle *veh = FindPlayerVehicle();
	if (veh == nil) return RADIO_OFF;
	if (UsesPoliceRadio(veh)) return POLICE_RADIO;
	if (veh->m_nRadioStation == USERTRACK && !SampleManager.IsMP3RadioChannelAvailable())
		veh->m_nRadioStation = AudioManager.m_anRandomTable[2] % USERTRACK;
	return veh->m_nRadioStation;
}

uint8
cMusicManager::GetNextCarTuning()
{
	CVehicle *veh = FindPlayerVehicle();
	if (veh == nil) return RADIO_OFF;
	if (UsesPoliceRadio(veh)) return POLICE_RADIO;
	if (gNumRetunePresses != 0) {
#ifdef RADIO_SCROLL_TO_PREV_STATION
		if (gNumRetunePresses < 0) {
			while (gNumRetunePresses < 0) {
				if(veh->m_nRadioStation == HEAD_RADIO) {
					veh->m_nRadioStation = RADIO_OFF;
				} else if(veh->m_nRadioStation == RADIO_OFF || veh->m_nRadioStation == NUM_RADIOS) {
					veh->m_nRadioStation = SampleManager.IsMP3RadioChannelAvailable() ? USERTRACK : USERTRACK - 1;
				} else
					veh->m_nRadioStation--;

				++gNumRetunePresses;
			}
		} else
#endif
		if (SampleManager.IsMP3RadioChannelAvailable()) {
			if (veh->m_nRadioStation == RADIO_OFF)
				veh->m_nRadioStation = NUM_RADIOS;
			veh->m_nRadioStation += gNumRetunePresses;
#ifdef FIX_BUGS
			while (veh->m_nRadioStation > NUM_RADIOS)
				veh->m_nRadioStation -= (NUM_RADIOS + 1);
#endif
			if (veh->m_nRadioStation == NUM_RADIOS)
				veh->m_nRadioStation = RADIO_OFF;
#ifndef FIX_BUGS
			else if (veh->m_nRadioStation > NUM_RADIOS)
				veh->m_nRadioStation -= (NUM_RADIOS + 1);
#endif
		} else if (gNumRetunePresses + veh->m_nRadioStation >= USERTRACK) {
			while (gNumRetunePresses) {
				if (veh->m_nRadioStation == RADIO_OFF)
					veh->m_nRadioStation = HEAD_RADIO;
				else if (veh->m_nRadioStation < USERTRACK)
					++veh->m_nRadioStation;

				if (veh->m_nRadioStation == USERTRACK)
					veh->m_nRadioStation = RADIO_OFF;
				--gNumRetunePresses;
			}
		} else
			veh->m_nRadioStation += gNumRetunePresses;
		gNumRetunePresses = 0;
	}
	return veh->m_nRadioStation;
}

bool8
cMusicManager::ChangeRadioChannel()
{
	if (m_nNextTrack != m_nPlayingTrack) {
		if (m_nPlayingTrack < TOTAL_STREAMED_SOUNDS) {
			m_aTracks[m_nPlayingTrack].m_nPosition = SampleManager.GetStreamedFilePosition();
			m_aTracks[m_nPlayingTrack].m_nLastPosCheckTimer = CTimer::GetTimeInMillisecondsPauseMode();
			SampleManager.SetStreamedVolumeAndPan(0, 63, FALSE);
			SampleManager.StopStreamedFile();
		}
		if (SampleManager.IsStreamPlaying())
			return FALSE;
		if (!SampleManager.StartStreamedFile(m_nNextTrack, GetTrackStartPos(m_nNextTrack)))
			return FALSE;
		SampleManager.SetStreamedVolumeAndPan(AudioManager.ShouldDuckMissionAudio() ? 25 : 100, 63, FALSE);
	}
	return TRUE;
}
