#include "Console.h"

#include "Font.h"
#include "Timer.h"

#define CONSOLE_MESSAGE_SHOW_TIME 20000
#define CONSOLE_MESSAGE_HEIGHT 12.0f
#define CONSOLE_MESSAGE_X_OFFSET 30.0f
#define CONSOLE_MESSAGE_Y_OFFSET 10.0f
#define CONSOLE_MESSAGE_X_SHADOW_OFFSET 1.0f
#define CONSOLE_MESSAGE_Y_SHADOW_OFFSET 1.0f

CConsole& TheConsole = *(CConsole*)0x8F6498;

void CConsole::Display()
{
	CFont::SetPropOn();
	CFont::SetBackgroundOff();
	CFont::SetScale(0.6f, 0.6f);
	CFont::SetCentreOff();
	CFont::SetRightJustifyOff();
	CFont::SetBackGroundOnlyTextOff();
	CFont::SetFontStyle(0);
	CFont::SetPropOff();
	CFont::SetWrapx(RsGlobal.width);
	while (m_nActiveMessages != 0 && CTimer::GetTimeInMilliseconds() - m_anTimeStart[m_nCurrentMessage] > CONSOLE_MESSAGE_SHOW_TIME) {
		m_nActiveMessages--;
		m_nCurrentMessage = (m_nCurrentMessage + 1) % NUM_CONSOLEMESSAGES;
	}
	for (int i = 0; i < m_nActiveMessages; i++) {
		int actualIndex = (i + m_nCurrentMessage) % NUM_CONSOLEMESSAGES;
		CFont::SetColor(CRGBA(0, 0, 0, 200));
		CFont::PrintString(
			CONSOLE_MESSAGE_X_OFFSET + CONSOLE_MESSAGE_X_SHADOW_OFFSET,
			CONSOLE_MESSAGE_Y_OFFSET + CONSOLE_MESSAGE_Y_SHADOW_OFFSET + i * CONSOLE_MESSAGE_HEIGHT,
			m_asMessages[actualIndex]);
		CFont::SetColor(CRGBA(m_anColourRed[actualIndex], m_anColourGreen[actualIndex], m_anColourBlue[actualIndex], 200));
		CFont::PrintString(
			CONSOLE_MESSAGE_X_OFFSET,
			CONSOLE_MESSAGE_Y_OFFSET + i * CONSOLE_MESSAGE_HEIGHT,
			m_asMessages[actualIndex]);
	}
}