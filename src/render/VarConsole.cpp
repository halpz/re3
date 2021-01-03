#include "common.h"
#include "VarConsole.h"
#include "Font.h"
#include "Pad.h"

#define VAR_CONSOLE_PAD 1

CVarConsole VarConsole;

void
CVarConsole::Initialise()
{
	m_nCountEntries = 0;
	m_nCurPage = 1;
	m_bIsOpen = false;
	m_nCurEntry = 0;
	m_nFirstEntryOnPage = 0;
}

void
CVarConsole::Add(char *text, int8 *pVal, uint8 step, int8 min, int8 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pInt8Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_INT8;
	m_aEntries[i].I8_step = step;
	m_aEntries[i].I8_min = min;
	m_aEntries[i].I8_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, int16 *pVal, uint16 step, int16 min, int16 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pInt16Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_INT16;
	m_aEntries[i].I16_step = step;
	m_aEntries[i].I16_min = min;
	m_aEntries[i].I16_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, int32 *pVal, uint32 step, int32 min, int32 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pInt32Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_INT32;
	m_aEntries[i].I32_step = step;
	m_aEntries[i].I32_min = min;
	m_aEntries[i].I32_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, int64 *pVal, uint64 step, int64 min, int64 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pInt64Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_INT64;
	m_aEntries[i].I64_step = step;
	m_aEntries[i].I64_min = min;
	m_aEntries[i].I64_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, uint8 *pVal, uint8 step, int8 min, int8 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pUint8Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_UINT8;
	m_aEntries[i].I8_step = step;
	m_aEntries[i].I8_min = min;
	m_aEntries[i].I8_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, uint16 *pVal, uint16 step, int16 min, int16 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pUint16Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_UINT16;
	m_aEntries[i].I16_step = step;
	m_aEntries[i].I16_min = min;
	m_aEntries[i].I16_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, uint32 *pVal, uint32 step, int32 min, int32 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pUint32Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_UINT32;
	m_aEntries[i].I32_step = step;
	m_aEntries[i].I32_min = min;
	m_aEntries[i].I32_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, uint64 *pVal, uint64 step, int64 min, int64 max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pUint64Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_UINT64;
	m_aEntries[i].I64_step = step;
	m_aEntries[i].I64_min = min;
	m_aEntries[i].I64_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, float *pVal, float step, float min, float max, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pFloatValue = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_FLOAT;
	m_aEntries[i].F_step = step;
	m_aEntries[i].F_min = min;
	m_aEntries[i].F_max = max;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, bool *pVal, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pBoolValue = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_BOOL;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, bool8 *pVal, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pUint8Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_BOOL8;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, bool16 *pVal, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pUint16Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_BOOL16;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, bool32 *pVal, bool8 isVar)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pUint32Value = pVal;
	m_aEntries[i].bAllowExceedBounds = isVar;
	m_aEntries[i].VarType = VCE_TYPE_BOOL32;
	m_nCountEntries++;
}

void
CVarConsole::Add(char *text, void (*pCallback)(void))
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
			return;
	}

	m_aEntries[i].text = text;
	m_aEntries[i].pCallback = pCallback;
	m_aEntries[i].VarType = VCE_TYPE_FUNCTION;
	m_nCountEntries++;
}

void
CVarConsole::Remove(char *text)
{
	int i;
	for (i = 0; i < m_nCountEntries; i++) {
		if (m_aEntries[i].text == text)
		{
			for (int j = i; j < m_nCountEntries-1; j++)
				m_aEntries[j] = m_aEntries[j+1];
			m_nCountEntries--;
			return;
		}
	}
}

void
CVarConsole::SortPages()
{
	m_nNumPages = m_nCountEntries / 30 + 1;
}

void
CVarConsole::Display()
{
	char s[256];
	wchar ws[256];

	CFont::SetColor(CRGBA(200, 200, 200, 255));
	CFont::SetFontStyle(FONT_STANDARD);
	CFont::SetScale(SCREEN_SCALE_X(0.5f), SCREEN_SCALE_Y(0.6f));
	CFont::SetDropShadowPosition(2);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetPropOn();
	CFont::SetWrapx(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH));
	CFont::SetRightJustifyWrap(0.0f);
	sprintf(s, "PAGE %d", m_nCurPage);
	AsciiToUnicode(s, ws);
	CFont::SetRightJustifyOn();
	CFont::PrintString(SCREEN_SCALE_X(310.0f), SCREEN_SCALE_Y(30.0f), ws);
	CFont::SetRightJustifyOff();
	int y = 45;
	for (int i = m_nFirstEntryOnPage; i < m_nCountEntries && i < m_nFirstEntryOnPage + 30; i++)
	{
		switch (m_aEntries[i].VarType)
		{
		case VCE_TYPE_INT8:
			sprintf(s, "(%d) %s:I8:%d", i + 1, m_aEntries[i].text, *m_aEntries[i].pInt8Value);
			break;
		case VCE_TYPE_INT16:
			sprintf(s, "(%d) %s:I16:%d", i + 1, m_aEntries[i].text, *m_aEntries[i].pInt16Value);
			break;
		case VCE_TYPE_INT32:
			sprintf(s, "(%d) %s:I32:%d", i + 1, m_aEntries[i].text, *m_aEntries[i].pInt32Value);
			break;
		case VCE_TYPE_INT64:
#ifdef FIX_BUGS  
			sprintf(s, "(%d) %s:I64:%lld", i + 1, m_aEntries[i].text, *m_aEntries[i].pInt64Value);
#else
			sprintf(s, "(%d) %s:I64:%d", i + 1, m_aEntries[i].text, (int32)*m_aEntries[i].pInt64Value);
#endif
			break;
		case VCE_TYPE_UINT8:
			sprintf(s, "(%d) %s:U8:%d", i + 1, m_aEntries[i].text, *m_aEntries[i].pUint8Value);
			break;
		case VCE_TYPE_UINT16:
			sprintf(s, "(%d) %s:U6:%d", i + 1, m_aEntries[i].text, *m_aEntries[i].pUint16Value);
			break;
		case VCE_TYPE_UINT32:
			sprintf(s, "(%d) %s:U32:%d", i + 1, m_aEntries[i].text, *m_aEntries[i].pUint32Value);
			break;
		case VCE_TYPE_UINT64:
#ifdef FIX_BUGS
			sprintf(s, "(%d) %s:U64:%llu", i + 1, m_aEntries[i].text, *m_aEntries[i].pUint64Value);
#else
			sprintf(s, "(%d) %s:U64:%d", i + 1, m_aEntries[i].text, (uint32)*m_aEntries[i].pUint64Value);
#endif
			break;
		case VCE_TYPE_FLOAT:
			sprintf(s, "(%d) %s:F:%f", i + 1, m_aEntries[i].text, *m_aEntries[i].pFloatValue);
			break;
		case VCE_TYPE_BOOL:
			if (*m_aEntries[i].pBoolValue)
				sprintf(s, "(%d) %s:B:TRUE", i + 1, m_aEntries[i].text);
			else
				sprintf(s, "(%d) %s:B : FALSE", i + 1, m_aEntries[i].text);
			break;
		case VCE_TYPE_BOOL8:
			if (*m_aEntries[i].pUint8Value == FALSE)
				sprintf(s, "(%d) %s:B8:FALSE", i + 1, m_aEntries[i].text);
			else
				sprintf(s, "(%d) %s:B8:TRUE", i + 1, m_aEntries[i].text);
			break;
		case VCE_TYPE_BOOL16:
			if (*m_aEntries[i].pUint16Value == FALSE)
				sprintf(s, "(%d) %s:B16:FALSE", i + 1, m_aEntries[i].text);
			else
				sprintf(s, "(%d) %s:B16:TRUE", i + 1, m_aEntries[i].text);
			break;
		case VCE_TYPE_BOOL32:
			if (*m_aEntries[i].pUint32Value == FALSE)
				sprintf(s, "(%d) %s:B32:FALSE", i + 1, m_aEntries[i].text);
			else
				sprintf(s, "(%d) %s:B32:TRUE", i + 1, m_aEntries[i].text);
			break;
		case VCE_TYPE_FUNCTION:
			sprintf(s, "(%d) %s:FUNCTION:call this function?", i + 1, m_aEntries[i].text);
			break;
		}
		AsciiToUnicode(s, ws);
		if (m_nCurEntry == i) {
			CFont::SetBackgroundOn();
#ifdef FIX_BUGS
			CFont::SetBackgroundColor(CRGBA(128, 128, 128, 128));
#endif
		}
#ifdef FIX_BUGS
		else
			CFont::SetBackgroundColor(CRGBA(128, 128, 128, 0));
#endif

		CFont::SetColor(CRGBA(200, 200, 200, 255));
		CFont::PrintString(SCREEN_SCALE_X(30.0f), SCREEN_SCALE_Y(y), ws);
		if (m_nCurEntry == i)
			CFont::SetBackgroundOff();
		y += 12;
	}
}

void
CVarConsole::ModifyLeft()
{
	CVarConsoleEntry &entry = m_aEntries[m_nCurEntry];
	switch (entry.VarType)
	{
	case VCE_TYPE_INT8:
		*entry.pInt8Value -= entry.I8_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt8Value < entry.I8_min)
				*entry.pInt8Value = entry.I8_max;
		} else {
			if (*entry.pInt8Value < entry.I8_min)
				*entry.pInt8Value = entry.I8_min;
		}
		break;
	case VCE_TYPE_INT16:
		*entry.pInt16Value -= entry.I16_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt16Value < entry.I16_min)
				*entry.pInt16Value = entry.I16_max;
		}
		else {
			if (*entry.pInt16Value < entry.I16_min)
				*entry.pInt16Value = entry.I16_min;
		}
		break;
	case VCE_TYPE_INT32:
		*entry.pInt32Value -= entry.I32_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt32Value < entry.I32_min)
				*entry.pInt32Value = entry.I32_max;
		}
		else {
			if (*entry.pInt32Value < entry.I32_min)
				*entry.pInt32Value = entry.I32_min;
		}
		break;
	case VCE_TYPE_INT64:
		*entry.pInt64Value -= entry.I64_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt64Value < entry.I64_min)
				*entry.pInt64Value = entry.I64_max;
		}
		else {
			if (*entry.pInt64Value < entry.I64_min)
				*entry.pInt64Value = entry.I64_min;
		}
		break;
	case VCE_TYPE_UINT8:
		*entry.pUint8Value -= entry.I8_step;
		if (entry.bAllowExceedBounds) {
			if (*(int8*)entry.pUint8Value < entry.I8_min)
				*entry.pUint8Value = entry.I8_max;
		}
		else {
			if (*(int8*)entry.pUint8Value < entry.I8_min)
				*entry.pUint8Value = entry.I8_min;
		}
		break;
	case VCE_TYPE_UINT16:
		*entry.pUint16Value -= entry.I16_step;
		if (entry.bAllowExceedBounds) {
			if (*(int16*)entry.pUint16Value < entry.I16_min)
				*entry.pUint16Value = entry.I16_max;
		}
		else {
			if (*(int16*)entry.pUint16Value < entry.I16_min)
				*entry.pUint16Value = entry.I16_min;
		}
		break;
	case VCE_TYPE_UINT32:
		*entry.pUint32Value -= entry.I32_step;
		if (entry.bAllowExceedBounds) {
			if (*(int32*)entry.pUint32Value < entry.I32_min)
				*entry.pUint32Value = entry.I32_max;
		}
		else {
			if (*(int32*)entry.pUint32Value < entry.I32_min)
				*entry.pUint32Value = entry.I32_min;
		}
		break;
	case VCE_TYPE_UINT64:
		*entry.pUint64Value -= entry.I64_step;
		if (entry.bAllowExceedBounds) {
			if (*(int64*)entry.pUint64Value < entry.I64_min)
				*entry.pUint64Value = entry.I64_max;
		}
		else {
			if (*(int64*)entry.pUint64Value < entry.I64_min)
				*entry.pUint64Value = entry.I64_min;
		}
		break;
	case VCE_TYPE_FLOAT:
		*entry.pFloatValue -= entry.F_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pFloatValue < entry.F_min)
				*entry.pFloatValue = entry.F_max;
		}
		else {
			if (*entry.pFloatValue < entry.F_min)
				*entry.pFloatValue = entry.F_min;
		}
		break;
	case VCE_TYPE_BOOL:
		if (entry.bAllowExceedBounds)
			*entry.pBoolValue ^= true;
		else
			*entry.pBoolValue = false;
		break;
	case VCE_TYPE_BOOL8:
		if (entry.bAllowExceedBounds)
			*entry.pUint8Value = *entry.pUint8Value == false;
		else
			*entry.pUint8Value = false;
		break;
	case VCE_TYPE_BOOL16:
		if (entry.bAllowExceedBounds)
			*entry.pUint16Value = *entry.pUint16Value == false;
		else
			*entry.pUint16Value = false;
		break;
	case VCE_TYPE_BOOL32:
		if (entry.bAllowExceedBounds)
			*entry.pUint32Value = *entry.pUint32Value == false;
		else
			*entry.pUint32Value = false;
		break;
	case VCE_TYPE_FUNCTION:
		entry.pCallback();
		break;
	default:
		return;
	}
}

void
CVarConsole::ModifyRight()
{
	CVarConsoleEntry &entry = m_aEntries[m_nCurEntry];
	switch (entry.VarType)
	{
	case VCE_TYPE_INT8:
		*entry.pInt8Value += entry.I8_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt8Value > entry.I8_max)
				*entry.pInt8Value = entry.I8_min;
		}
		else {
			if (*entry.pInt8Value > entry.I8_max)
				*entry.pInt8Value = entry.I8_max;
		}
		break;
	case VCE_TYPE_INT16:
		*entry.pInt16Value += entry.I16_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt16Value > entry.I16_max)
				*entry.pInt16Value = entry.I16_min;
		}
		else {
			if (*entry.pInt16Value > entry.I16_max)
				*entry.pInt16Value = entry.I16_max;
		}
		break;
	case VCE_TYPE_INT32:
		*entry.pInt32Value += entry.I32_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt32Value > entry.I32_max)
				*entry.pInt32Value = entry.I32_min;
		}
		else {
			if (*entry.pInt32Value > entry.I32_max)
				*entry.pInt32Value = entry.I32_max;
		}
		break;
	case VCE_TYPE_INT64:
		*entry.pInt64Value += entry.I64_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pInt64Value > entry.I64_max)
				*entry.pInt64Value = entry.I64_min;
		}
		else {
			if (*entry.pInt64Value > entry.I64_max)
				*entry.pInt64Value = entry.I64_max;
		}
		break;
	case VCE_TYPE_UINT8:
		*entry.pUint8Value += entry.I8_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pUint8Value > (uint8)entry.I8_max)
				*entry.pUint8Value = entry.I8_min;
		}
		else {
			if (*entry.pUint8Value > (uint8)entry.I8_max)
				*entry.pUint8Value = entry.I8_max;
		}
		break;
	case VCE_TYPE_UINT16:
		*entry.pUint16Value += entry.I16_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pUint16Value > (uint16)entry.I16_max)
				*entry.pUint16Value = entry.I16_min;
		}
		else {
			if (*entry.pUint16Value > (uint16)entry.I16_max)
				*entry.pUint16Value = entry.I16_max;
		}
		break;
	case VCE_TYPE_UINT32:
		*entry.pUint32Value += entry.I32_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pUint32Value > (uint32)entry.I32_max)
				*entry.pUint32Value = entry.I32_min;
		}
		else {
			if (*entry.pUint32Value > (uint32)entry.I32_max)
				*entry.pUint32Value = entry.I32_max;
		}
		break;
	case VCE_TYPE_UINT64:
		*entry.pUint64Value += entry.I64_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pUint64Value > (uint64)entry.I64_max)
				*entry.pUint64Value = entry.I64_min;
		}
		else {
			if (*entry.pUint64Value > (uint64)entry.I64_max)
				*entry.pUint64Value = entry.I64_max;
		}
		break;
	case VCE_TYPE_FLOAT:
		*entry.pFloatValue += entry.F_step;
		if (entry.bAllowExceedBounds) {
			if (*entry.pFloatValue > entry.F_max)
				*entry.pFloatValue = entry.F_min;
		}
		else {
			if (*entry.pFloatValue > entry.F_max)
				*entry.pFloatValue = entry.F_max;
		}
		break;
	case VCE_TYPE_BOOL:
		if (entry.bAllowExceedBounds)
			*entry.pBoolValue ^= true;
		else
			*entry.pBoolValue = true;
		break;
	case VCE_TYPE_BOOL8:
		if (entry.bAllowExceedBounds)
			*entry.pUint8Value = *entry.pUint8Value == false;
		else
			*entry.pUint8Value = true;
		break;
	case VCE_TYPE_BOOL16:
		if (entry.bAllowExceedBounds)
			*entry.pUint16Value = *entry.pUint16Value == false;
		else
			*entry.pUint16Value = true;
		break;
	case VCE_TYPE_BOOL32:
		if (entry.bAllowExceedBounds)
			*entry.pUint32Value = *entry.pUint32Value == false;
		else
			*entry.pUint32Value = true;
		break;
	case VCE_TYPE_FUNCTION:
		entry.pCallback();
		break;
	default:
		return;
	}
}

void
CVarConsole::Enter()
{
	m_bIsOpen = true;
}

void
CVarConsole::Exit()
{
	m_bIsOpen = false;
}

void
CVarConsole::Input()
{
	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetDPadDownJustDown() || CPad::GetPad(VAR_CONSOLE_PAD)->GetAnaloguePadDown())
	{
		m_nCurEntry++;
		if (m_nCurEntry < m_nCountEntries)
		{
			if (m_nCurEntry > m_nFirstEntryOnPage + 29)
			{
				m_nFirstEntryOnPage = m_nCurEntry;
				++m_nCurPage;
			}
		}
		else
		{
			m_nCurEntry = m_nCountEntries - 1;
		}
	}

	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetDPadUpJustDown() || CPad::GetPad(VAR_CONSOLE_PAD)->GetAnaloguePadUp())
	{
		m_nCurEntry--;
		if (m_nCurEntry < m_nFirstEntryOnPage)
		{
			m_nFirstEntryOnPage = m_nCurEntry - 29;
			--m_nCurPage;
		}
		if (m_nFirstEntryOnPage < 0)
		{
			m_nCurEntry = 0;
			m_nFirstEntryOnPage = 0;
			m_nCurPage = 1;
		}
	}
	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetSquare())
		ModifyLeft();
	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetTriangle())
		ModifyRight();

	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetDPadLeftJustDown() || CPad::GetPad(VAR_CONSOLE_PAD)->GetAnaloguePadLeft())
		ModifyLeft();

	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetDPadRightJustDown() || CPad::GetPad(VAR_CONSOLE_PAD)->GetAnaloguePadRight())
		ModifyRight();

	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetLeftShoulder2JustDown())
	{
		if (m_nCurPage > 1)
		{
			m_nCurPage--;
			m_nFirstEntryOnPage -= 30;
			m_nCurEntry = m_nFirstEntryOnPage;
			if (m_nFirstEntryOnPage < 0)
			{
				m_nFirstEntryOnPage = 0;
				m_nCurEntry = m_nFirstEntryOnPage;
				m_nCurPage = 1;
			}
		}
	}

	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetRightShoulder2JustDown())
	{
		if (m_nCurPage < m_nNumPages)
		{
			m_nCurPage++;
			m_nFirstEntryOnPage += 30;
			m_nCurEntry = m_nFirstEntryOnPage;
			if (m_nFirstEntryOnPage >= m_nCountEntries)
			{
				m_nFirstEntryOnPage -= 30;
				m_nCurEntry = m_nFirstEntryOnPage;
				m_nCurPage--;
			}
		}
	}

	if (CPad::GetPad(VAR_CONSOLE_PAD)->GetRightShoulder1JustDown() && CPad::GetPad(VAR_CONSOLE_PAD)->GetLeftShoulder1JustDown())
		Exit();
}

void
CVarConsole::Process()
{
	Input();
	SortPages();
	Display();
}

bool8 
CVarConsole::Open()
{
	return m_bIsOpen;
}

void
CVarConsole::Check()
{
	if (Open())
		Process();
	else if (CPad::GetPad(VAR_CONSOLE_PAD)->GetRightShoulder1JustDown() && CPad::GetPad(VAR_CONSOLE_PAD)->GetLeftShoulder1JustDown())
		Enter();
}