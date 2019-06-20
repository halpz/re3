#include "common.h"
#include "patcher.h"
#include "MusicManager.h"
#include "Font.h"
#include "Hud.h"
#include "Text.h"
#include "Timer.h"
#include "Camera.h"
#include "World.h"
#include "ModelIndices.h"
#include "SampleManager.h"
#include "Replay.h"

cMusicManager &MusicManager = *(cMusicManager*)0x8F3964;
int32 &gNumRetunePresses = *(int32*)0x650B80;
wchar *pCurrentStation = (wchar*)0x650B9C;
uint8 &cDisplay = *(uint8*)0x650BA1;

bool cMusicManager::PlayerInCar()
{
	if (!FindPlayerVehicle())
		return false;
	else {
		int32 State = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nPedState;

		if (State == PED_DRAG_FROM_CAR || State == PED_EXIT_CAR || State == PED_ARRESTED)
			return false;

		switch (FindPlayerVehicle()->m_modelIndex) {
		case MI_FIRETRUCK:
		case MI_AMBULAN:
		case MI_MRWHOOP:
		case MI_PREDATOR:
		case MI_TRAIN:
		case MI_SPEEDER:
		case MI_REEFER:
		case MI_GHOST:
			return false;
		default:
			return true;
		}
	}
}

#if 0
WRAPPER void cMusicManager::DisplayRadioStationName(void) { EAXJMP(0x57E6D0); }
#else
void cMusicManager::DisplayRadioStationName()
{
	int8 pRetune;
	int8 gStreamedSound;
	int8 gRetuneCounter;

	if (!CTimer::GetIsPaused() && !TheCamera.m_WideScreenOn && cMusicManager::PlayerInCar() && CReplay::Mode != 1) {
		if (MusicManager.m_bPlayerInCar && !MusicManager.m_bPreviousPlayerInCar)
			pCurrentStation = nullptr;

		if (cSampleManager.IsMP3RadioChannelAvailable()) {
			gStreamedSound = MusicManager.m_nCurrentStreamedSound;

			if (gStreamedSound != STREAMED_SOUND_CITY_AMBIENT && gStreamedSound != STREAMED_SOUND_WATER_AMBIENT) {
				if (gStreamedSound > STREAMED_SOUND_RADIO_MP3_PLAYER)
					return;
			}
			else {
				gStreamedSound = STREAMED_SOUND_RADIO_POLICE;
			}

			pRetune = gNumRetunePresses + gStreamedSound;

			if (pRetune == POLICE_RADIO) {
				pRetune = RADIO_OFF;
			}
			else if (pRetune > POLICE_RADIO) {
				pRetune = pRetune - 11;
			}
		}
		else {
			gStreamedSound = MusicManager.m_nCurrentStreamedSound;
			pRetune = gNumRetunePresses + gStreamedSound;

			if (pRetune >= USERTRACK) {
				gRetuneCounter = gNumRetunePresses;
				pRetune = MusicManager.m_nCurrentStreamedSound;

				if (gStreamedSound == STREAMED_SOUND_WATER_AMBIENT)
					pRetune = RADIO_OFF;

				while (gRetuneCounter) {
					if (pRetune == RADIO_OFF) {
						pRetune = HEAD_RADIO;
					}
					else if (pRetune < USERTRACK) {
						pRetune = pRetune + 1;
					}
					if (pRetune == USERTRACK)
						pRetune = RADIO_OFF;

					--gRetuneCounter;
				}
			}
		}

		wchar *string = nullptr;

		switch (pRetune) {
		case HEAD_RADIO:
			string = TheText.Get("FEA_FM0");
			break;
		case DOUBLE_CLEF:
			string = TheText.Get("FEA_FM1");
			break;
		case JAH_RADIO:
			string = TheText.Get("FEA_FM2");
			break;
		case RISE_FM:
			string = TheText.Get("FEA_FM3");
			break;
		case LIPS_106:
			string = TheText.Get("FEA_FM4");
			break;
		case GAME_FM:
			string = TheText.Get("FEA_FM5");
			break;
		case MSX_FM:
			string = TheText.Get("FEA_FM6");
			break;
		case FLASHBACK:
			string = TheText.Get("FEA_FM7");
			break;
		case CHATTERBOX:
			string = TheText.Get("FEA_FM8");
			break;
		case USERTRACK:
			string = TheText.Get("FEA_FM9");
			break;
		default:
			return;
		};

		if (pRetune > CHATTERBOX && !CSampleManager::IsMP3RadioChannelAvailable()) {
			return;
		}

		if (string && pCurrentStation != string || MusicManager.m_nCurrentStreamedSound == STREAMED_SOUND_RADIO_MP3_PLAYER && MusicManager.m_nPreviousStreamedSound != STREAMED_SOUND_RADIO_MP3_PLAYER) {
			pCurrentStation = string;
			cDisplay = 60;
		}
		else {
			if (!cDisplay)
				return;
			--cDisplay;
		}

		CFont::SetJustifyOff();
		CFont::SetBackgroundOff();
		CFont::SetScale(SCREEN_SCALE_X(0.8f), SCREEN_SCALE_Y(1.35f));
		CFont::SetPropOn();
		CFont::SetFontStyle(FONT_HEADING);
		CFont::SetCentreOn();
		CFont::SetCentreSize(SCREEN_SCALE_X(640.0f));
		CFont::SetColor(CRGBA(0, 0, 0, 255));
		CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_SCALE_Y(23.0f), pCurrentStation);

		if (gNumRetunePresses)
			CFont::SetColor(CRGBA(102, 133, 143, 255));
		else
			CFont::SetColor(CRGBA(147, 196, 211, 255));

		CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_SCALE_Y(22.0f), pCurrentStation);
		CFont::DrawFonts();
	}
}
#endif
