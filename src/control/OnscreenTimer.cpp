#include "common.h"


#include "DMAudio.h"
#include "Hud.h"
#include "Replay.h"
#include "Timer.h"
#include "Script.h"
#include "OnscreenTimer.h"
#include "Camera.h"

CRGBA gbColour(255, 255, 255, 255);
CRGBA gbColour2(255, 255, 255, 255);

void
COnscreenTimer::Init()
{
	m_bDisabled = false;
	for(uint32 i = 0; i < NUMONSCREENCOUNTERS; i++) {
		m_sCounters[i].m_nCounterOffset = 0;
		m_sCounters[i].m_nTotal = -1;

		for (uint32 j = 0; j < ARRAY_SIZE(m_sCounters[0].m_aCounterText1); j++) {
			m_sCounters[i].m_aCounterText1[j] = '\0';
		}

		for (uint32 j = 0; j < ARRAY_SIZE(m_sCounters[0].m_aCounterText2); j++) {
			m_sCounters[i].m_aCounterText2[j] = '\0';
		}

		m_sCounters[i].m_nType = COUNTER_DISPLAY_NUMBER;
		m_sCounters[i].m_nTypeOfTotal = 0;
		m_sCounters[i].m_bCounterProcessed = false;
		m_sCounters[i].m_colour1 = CRGBA(112, 132, 157, 255);
		m_sCounters[i].m_colour2 = CRGBA(42, 58, 81, 255);

	}
	for(uint32 i = 0; i < NUMONSCREENCLOCKS; i++) {
		m_sClocks[i].m_nClockOffset = 0;

		for(uint32 j = 0; j < ARRAY_SIZE(m_sClocks[0].m_aClockText); j++)
			m_sClocks[i].m_aClockText[j] = '\0';

		m_sClocks[i].m_bClockProcessed = false;
		m_sClocks[i].m_bClockGoingDown = true;
		m_sClocks[i].m_aClockColour = CRGBA(244, 225, 91, 255);
		m_sClocks[i].m_bClockTickThisFrame = false;
	}
}

void
COnscreenTimer::Process()
{
	if(!CReplay::IsPlayingBack() && !m_bDisabled)
		for(uint32 i = 0; i < NUMONSCREENCLOCKS; i++)
			m_sClocks[i].Process();
}

void
COnscreenTimer::ProcessForDisplay()
{
#ifdef GTA_NETWORK
	if (gIsMultiplayerGame)
		return;
#endif
	if(CHud::m_Wants_To_Draw_Hud) {
		m_bProcessed = false;
		for(uint32 i = 0; i < NUMONSCREENCLOCKS; i++) {
			m_sClocks[i].m_bClockProcessed = false;
			if (m_sClocks[i].m_nClockOffset != 0) {
				m_sClocks[i].ProcessForDisplayClock();
				m_sClocks[i].m_bClockProcessed = true;
				m_bProcessed = true;
			}
		}
		for(uint32 i = 0; i < NUMONSCREENCOUNTERS; i++) {
			m_sCounters[i].m_bCounterProcessed = false;
			if (m_sCounters[i].m_nCounterOffset != 0) {
				m_sCounters[i].ProcessForDisplayCounter();
				m_sCounters[i].m_bCounterProcessed = true;
				m_bProcessed = true;
			}
		}
	}
}

void
COnscreenTimer::ClearCounter(uint32 offset)
{
	for(uint32 i = 0; i < NUMONSCREENCOUNTERS; i++) {
		if(offset == m_sCounters[i].m_nCounterOffset) {
			m_sCounters[i].m_nCounterOffset = 0;
			m_sCounters[i].m_aCounterText1[0] = '\0';
			m_sCounters[i].m_aCounterText2[0] = '\0';
			m_sCounters[i].m_nTypeOfTotal = 0;
			m_sCounters[i].m_nType = COUNTER_DISPLAY_NUMBER;
			m_sCounters[i].m_bCounterProcessed = false;
			m_sCounters[i].m_bAddDollarPrefix = false;
		}
	}
}

void
COnscreenTimer::ClearClock(uint32 offset)
{
	for(uint32 i = 0; i < NUMONSCREENCLOCKS; i++)
		if(offset == m_sClocks[i].m_nClockOffset) {
			m_sClocks[i].m_nClockOffset = 0;
			m_sClocks[i].m_aClockText[0] = '\0';
			m_sClocks[i].m_bClockProcessed = false;
			m_sClocks[i].m_bClockGoingDown = true;
			m_sClocks[i].m_bClockTickThisFrame = false;
		}
}

void
COnscreenTimer::AddCounter(uint32 offset, uint16 type, char* text1, uint16 pos, int32 total, char* text2, uint16 totalType)
{
	if (m_sCounters[pos].m_nCounterOffset)
		return;

	m_sCounters[pos].m_nCounterOffset = offset;
	m_sCounters[pos].m_nTotal = total;
	if(text1)
		strncpy(m_sCounters[pos].m_aCounterText1, text1, ARRAY_SIZE(m_sCounters[0].m_aCounterText1));
	else
		m_sCounters[pos].m_aCounterText1[0] = '\0';

	if (text2)
		strncpy(m_sCounters[pos].m_aCounterText2, text2, ARRAY_SIZE(m_sCounters[0].m_aCounterText2));
	else
		m_sCounters[pos].m_aCounterText2[0] = '\0';

	m_sCounters[pos].m_nTypeOfTotal = totalType;
	m_sCounters[pos].m_nType = type;
	m_sCounters[pos].m_bAddDollarPrefix = 0;

	if (gbColour == CRGBA(255, 255, 255, 255))
		m_sCounters[pos].m_colour1 = CRGBA(112, 132, 157, 255);
	else {
		m_sCounters[pos].m_colour1 = gbColour;
		gbColour = CRGBA(255, 255, 255, 255);
	}
		
	if (gbColour == CRGBA(255, 255, 255, 255))
		m_sCounters[pos].m_colour2 = CRGBA(42, 58, 81, 255);
	else {
		m_sCounters[pos].m_colour2 = gbColour;
		gbColour = CRGBA(255, 255, 255, 255);
	}
}

void
COnscreenTimer::AddClock(uint32 offset, char* text, bool bGoingDown)
{
	for(uint32 i = 0; i < NUMONSCREENCLOCKS; i++) {
		if(m_sClocks[i].m_nClockOffset == 0) {
			m_sClocks[i].m_nClockOffset = offset;
			m_sClocks[i].m_bClockGoingDown = bGoingDown;
			m_sClocks[i].m_bClockTickThisFrame = false;
			if (gbColour == CRGBA(255, 255, 255, 255))
				m_sClocks[i].m_aClockColour = CRGBA(244, 225, 91, 255);
			else {
				m_sClocks[i].m_aClockColour = gbColour;
				gbColour = CRGBA(255, 255, 255, 255);
			}
			if(text)
				strncpy(m_sClocks[i].m_aClockText, text, ARRAY_SIZE(m_sClocks[0].m_aClockText));
			else
				m_sClocks[i].m_aClockText[0] = '\0';
			break;
		}
	}
}

void
COnscreenTimerEntry::Process()
{
	if(m_nClockOffset == 0)
		return;

	int32* timerPtr = CTheScripts::GetPointerToScriptVariable(m_nClockOffset);
	int32 oldTime = *timerPtr;
	if (m_bClockGoingDown) {
		int32 newTime = oldTime - int32(CTimer::GetTimeStepInMilliseconds());
		*timerPtr = newTime;
		if (newTime < 0) {
			*timerPtr = 0;
			m_bClockProcessed = 0;
			m_nClockOffset = 0;
			m_aClockText[0] = 0;
		}
		else {
			int32 oldTimeSeconds = oldTime / 1000;
			if (oldTimeSeconds < 12) {
				m_bClockTickThisFrame = false;
				if (newTime / 1000 != oldTimeSeconds) {
					m_bClockTickThisFrame = true;
					DMAudio.PlayFrontEndSound(SOUND_CLOCK_TICK, newTime / 1000);
				}
			}
		}
	}
	else
		*timerPtr = oldTime + int32(CTimer::GetTimeStepInMilliseconds());
}

void
COnscreenTimerEntry::ProcessForDisplayClock()
{
	uint32 time = *CTheScripts::GetPointerToScriptVariable(m_nClockOffset);
	sprintf(m_aClockBuffer, "%d:%02d", time / 1000 / 60 % 100,
				   time / 1000 % 60);
}

void
COnscreenCounterEntry::ProcessForDisplayCounter()
{
	uint32 counter = *CTheScripts::GetPointerToScriptVariable(m_nCounterOffset);
	char prefix[2] = { '\0' };
	if (m_bAddDollarPrefix)
		sprintf(prefix, "$");
#ifdef FIX_BUGS
	char suffix[4] = { '\0' };
#else
	char suffix[2] = { '\0' };
#endif
	if (m_nTotal != -1) {
		m_nTotal = Min(99, m_nTotal);
		sprintf(suffix, "/%d", m_nTotal);
	}
	sprintf(m_aCounterBuffer, "%s%d%s", prefix, counter, suffix);
}

void
COnscreenTimer::ChangeCounterPrefix(uint32 offset, bool bChange)
{
	for (uint32 i = 0; i < NUMONSCREENCOUNTERS; i++) {
		if (offset == m_sCounters[i].m_nCounterOffset) {
			m_sCounters[i].m_bAddDollarPrefix = bChange;
			return;
		}
	}
}
