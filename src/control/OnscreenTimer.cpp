#include "common.h"


#include "DMAudio.h"
#include "Hud.h"
#include "Replay.h"
#include "Timer.h"
#include "Script.h"
#include "OnscreenTimer.h"
#include "Camera.h"

void
COnscreenTimer::Init()
{
	m_bDisabled = false;
	for(uint32 i = 0; i < NUMONSCREENCOUNTERS; i++) {
		m_sCounters[i].m_nCounterOffset = 0;

		for(uint32 j = 0; j < ARRAY_SIZE(m_sCounters[0].m_aCounterText); j++)
			m_sCounters[i].m_aCounterText[j] = '\0';

		m_sCounters[i].m_nType = COUNTER_DISPLAY_NUMBER;
		m_sCounters[i].m_bCounterProcessed = false;
	}
	for(uint32 i = 0; i < NUMONSCREENCLOCKS; i++) {
		m_sClocks[i].m_nClockOffset = 0;

		for(uint32 j = 0; j < ARRAY_SIZE(m_sClocks[0].m_aClockText); j++)
			m_sClocks[i].m_aClockText[j] = '\0';

		m_sClocks[i].m_bClockProcessed = false;
		m_sClocks[i].m_bClockGoingDown = true;
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
			m_sCounters[i].m_aCounterText[0] = '\0';
			m_sCounters[i].m_nType = COUNTER_DISPLAY_NUMBER;
			m_sCounters[i].m_bCounterProcessed = false;
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
		}
}

void
COnscreenTimer::AddCounter(uint32 offset, uint16 type, char* text, uint16 pos)
{
	if (m_sCounters[pos].m_aCounterText[0] != '\0')
		return;

	m_sCounters[pos].m_nCounterOffset = offset;
	if(text)
		strncpy(m_sCounters[pos].m_aCounterText, text, ARRAY_SIZE(m_sCounters[0].m_aCounterText));
	else
		m_sCounters[pos].m_aCounterText[0] = '\0';

	m_sCounters[pos].m_nType = type;
}

void
COnscreenTimer::AddClock(uint32 offset, char* text, bool bGoingDown)
{
	for(uint32 i = 0; i < NUMONSCREENCLOCKS; i++) {
		if(m_sClocks[i].m_nClockOffset == 0) {
			m_sClocks[i].m_nClockOffset = offset;
			m_sClocks[i].m_bClockGoingDown = bGoingDown;
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
			if (oldTimeSeconds < 12 && newTime / 1000 != oldTimeSeconds && !TheCamera.m_WideScreenOn) {
				DMAudio.PlayFrontEndSound(SOUND_CLOCK_TICK, newTime / 1000);
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
	sprintf(m_aClockBuffer, "%02d:%02d", time / 1000 / 60 % 100,
				   time / 1000 % 60);
}

void
COnscreenCounterEntry::ProcessForDisplayCounter()
{
	uint32 counter = *CTheScripts::GetPointerToScriptVariable(m_nCounterOffset);
	sprintf(m_aCounterBuffer, "%d", counter);
}
