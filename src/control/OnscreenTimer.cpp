#include "common.h"


#include "DMAudio.h"
#include "Hud.h"
#include "Replay.h"
#include "Timer.h"
#include "Script.h"
#include "OnscreenTimer.h"

//--MIAMI: file done

void COnscreenTimer::Init() {
	m_bDisabled = false;

	for (uint32 i = 0; i < NUMONSCREENCOUNTERENTRIES; i++) {
		m_sCounters[i].m_nOffset = 0;

		for (uint32 j = 0; j < 10; j++)
			m_sCounters[i].m_aText[j] = 0;

		m_sCounters[i].m_nType = COUNTER_DISPLAY_NUMBER;
		m_sCounters[i].m_bProcessed = false;
	}
	for (uint32 i = 0; i < NUMONSCREENTIMERENTRIES; i++) {
		m_sTimers[i].m_nOffset = 0;

		for (uint32 j = 0; j < 10; j++)
			m_sTimers[i].m_aText[j] = 0;

		m_sTimers[i].m_bProcessed = false;
		m_sTimers[i].m_bGoingDown = true;
	}
}

void COnscreenTimer::Process() {
	if(!CReplay::IsPlayingBack() && !m_bDisabled) {
		for(uint32 i = 0; i < NUMONSCREENTIMERENTRIES; i++) {
			m_sTimers[i].Process();
		}
	}
}

void COnscreenTimer::ProcessForDisplay() {
	if(CHud::m_Wants_To_Draw_Hud) {
		m_bProcessed = false;
		for(uint32 i = 0; i < NUMONSCREENTIMERENTRIES; i++) {
			if(m_sTimers[i].ProcessForDisplay()) {
				m_bProcessed = true;
			}
		}
		for (uint32 i = 0; i < NUMONSCREENCOUNTERENTRIES; i++) {
			if (m_sCounters[i].ProcessForDisplay()) {
				m_bProcessed = true;
			}
		}
	}
}

void COnscreenTimer::ClearCounter(uint32 offset) {
	for(uint32 i = 0; i < NUMONSCREENCOUNTERENTRIES; i++) {
		if(offset == m_sCounters[i].m_nOffset) {
			m_sCounters[i].m_nOffset = 0;
			m_sCounters[i].m_aText[0] = 0;
			m_sCounters[i].m_nType = COUNTER_DISPLAY_NUMBER;
			m_sCounters[i].m_bProcessed = 0;
		}
	}
}

void COnscreenTimer::ClearClock(uint32 offset) {
	for(uint32 i = 0; i < NUMONSCREENTIMERENTRIES; i++) {
		if(offset == m_sTimers[i].m_nOffset) {
			m_sTimers[i].m_nOffset = 0;
			m_sTimers[i].m_aText[0] = 0;
			m_sTimers[i].m_bProcessed = 0;
		}
	}
}

void COnscreenTimer::AddCounter(uint32 offset, uint16 type, char* text, uint16 pos) {

	m_sCounters[pos].m_nOffset = offset;
	if (m_sCounters[pos].m_aText[0] != '\0')
		return;
	if(text) {
		strncpy(m_sCounters[pos].m_aText, text, 10);
	} else {
		m_sCounters[pos].m_aText[0] = 0;
	}

	m_sCounters[pos].m_nType = type;
}

void COnscreenTimer::AddClock(uint32 offset, char* text, bool bGoingDown) {
	uint32 i = 0;
	for(uint32 i = 0; i < NUMONSCREENTIMERENTRIES; i++) {
		if(m_sTimers[i].m_nOffset == 0) {
			break;
		}
		return;
	}

	m_sTimers[i].m_nOffset = offset;
	m_sTimers[i].m_bGoingDown = bGoingDown;
	if(text) {
		strncpy(m_sTimers[i].m_aText, text, 10);
	} else {
		m_sTimers[i].m_aText[0] = 0;
	}
}

void COnscreenTimerEntry::Process() {
	if(m_nOffset == 0) {
		return;
	}

	int32* timerPtr = CTheScripts::GetPointerToScriptVariable(m_nOffset);
	int32 oldTime = *timerPtr;
	if (m_bGoingDown) {
		int32 newTime = oldTime - int32(CTimer::GetTimeStepInMilliseconds());
		if (newTime < 0) {
			*timerPtr = 0;
			m_bProcessed = 0;
			m_nOffset = 0;
			m_aText[0] = 0;
		}
		else {
			*timerPtr = newTime;
			int32 oldTimeSeconds = oldTime / 1000;
			if (oldTimeSeconds < 12 && newTime / 1000 != oldTimeSeconds) {
				DMAudio.PlayFrontEndSound(SOUND_CLOCK_TICK, newTime / 1000);
			}
		}
	}
	else
		*timerPtr = oldTime + int32(CTimer::GetTimeStepInMilliseconds());
}

bool COnscreenTimerEntry::ProcessForDisplay() {
	m_bProcessed = false;

	if(m_nOffset == 0)
		return false;

	m_bProcessed = true;
	ProcessForDisplayClock();
	return true;
}

bool COnscreenCounterEntry::ProcessForDisplay() {
	m_bProcessed = false;

	if (m_nOffset == 0)
		return false;

	m_bProcessed = true;
	ProcessForDisplayCounter();
	return true;
}

void COnscreenTimerEntry::ProcessForDisplayClock() {
	uint32 time = *CTheScripts::GetPointerToScriptVariable(m_nOffset);
	sprintf(m_bBuffer, "%02d:%02d", time / 1000 / 60,
				   time / 1000 % 60);
}

void COnscreenCounterEntry::ProcessForDisplayCounter() {
	uint32 counter = *CTheScripts::GetPointerToScriptVariable(m_nOffset);
	sprintf(m_bBuffer, "%d", counter);
}
