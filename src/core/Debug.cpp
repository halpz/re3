#include "common.h"
#include "Debug.h"
#include "Font.h"
#include "main.h"
#include "Text.h"

bool gbDebugStuffInRelease = false;

#define DEBUG_X_POS (300)
#define DEBUG_Y_POS (41)
#define DEBUG_LINE_HEIGHT (22)

int16 CDebug::ms_nCurrentTextLine;
char CDebug::ms_aTextBuffer[MAX_LINES][MAX_STR_LEN];

void
CDebug::DebugInitTextBuffer()
{
	ms_nCurrentTextLine = 0;
}

void
CDebug::DebugAddText(const char *str)
{
	int32 i = 0;
	if (*str != '\0') {
		while (i < MAX_STR_LEN) {
			ms_aTextBuffer[ms_nCurrentTextLine][i++] = *(str++);
			if (*str == '\0')
				break;
		}
	}

	ms_aTextBuffer[ms_nCurrentTextLine++][i] = '\0';
	if (ms_nCurrentTextLine >= MAX_LINES)
		ms_nCurrentTextLine = 0;
}

void
CDebug::DebugDisplayTextBuffer()
{
#ifndef MASTER
	if (gbDebugStuffInRelease)
	{
		int32 i = 0;
		int32 y = DEBUG_Y_POS;
#ifdef FIX_BUGS
		CFont::SetPropOn();
		CFont::SetBackgroundOff();
		CFont::SetScale(1.0f, 1.0f);
		CFont::SetCentreOff();
		CFont::SetRightJustifyOff();
		CFont::SetJustifyOn();
		CFont::SetRightJustifyWrap(0.0f);
		CFont::SetBackGroundOnlyTextOff();
		CFont::SetFontStyle(FONT_BANK);
#else
		// this is not even readable
		CFont::SetPropOff();
		CFont::SetBackgroundOff();
		CFont::SetScale(1.0f, 1.0f);
		CFont::SetCentreOff();
		CFont::SetRightJustifyOn();
		CFont::SetRightJustifyWrap(0.0f);
		CFont::SetBackGroundOnlyTextOff();
		CFont::SetFontStyle(FONT_BANK);
		CFont::SetPropOff();
#endif
		do {
			char *line;
			while (true) {
				line = ms_aTextBuffer[(ms_nCurrentTextLine + i++) % MAX_LINES];
				if (*line != '\0')
					break;
				y += DEBUG_LINE_HEIGHT;
				if (i == MAX_LINES) {
					CFont::DrawFonts();
					return;
				}
			}
			AsciiToUnicode(line, gUString);
			CFont::SetColor(CRGBA(0, 0, 0, 255));
			CFont::PrintString(DEBUG_X_POS, y-1, gUString);
			CFont::SetColor(CRGBA(255, 128, 128, 255));
			CFont::PrintString(DEBUG_X_POS+1, y, gUString);
			y += DEBUG_LINE_HEIGHT;
		} while (i != MAX_LINES);
		CFont::DrawFonts();
	}
#endif
}
