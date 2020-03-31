#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

#include "common.h"
#include "patcher.h"
#include "Messages.h"
#include "RwHelper.h"
#include "Hud.h"
#include "User.h"
#include "Timer.h"
#include "Text.h"

#include "ControllerConfig.h"

#include "Font.h"

tMessage(&CMessages::BriefMessages)[NUMBRIEFMESSAGES] = *(tMessage(*)[NUMBRIEFMESSAGES])*(uintptr*)0x8786E0;
tPreviousBrief(&CMessages::PreviousBriefs)[NUMPREVIOUSBRIEFS] = *(tPreviousBrief(*)[NUMPREVIOUSBRIEFS])*(uintptr*)0x713C08;
tBigMessage(&CMessages::BIGMessages)[NUMBIGMESSAGES] = *(tBigMessage(*)[NUMBIGMESSAGES])*(uintptr*)0x773628;
char CMessages::PreviousMissionTitle[16]; // unused

void
CMessages::Init()
{
	ClearMessages();

	for (int32 i = 0; i < NUMPREVIOUSBRIEFS; i++) {
		PreviousBriefs[i].m_pText = nil;
		PreviousBriefs[i].m_pString = nil;
	}
}

uint16
CMessages::GetWideStringLength(wchar *src)
{
	uint16 length = 0;
	while (*(src++)) length++;
	return length;
}

void
CMessages::WideStringCopy(wchar *dst, wchar *src, uint16 size)
{
	int32 i = 0;
	if (src) {
		while (i < size - 1) {
			if (!src[i]) break;
			dst[i] = src[i];
			i++;
		}
	} else {
		while (i < size - 1)
			dst[i++] = '\0';
	}
	dst[i] = '\0';
}

wchar jappy(wchar c)
{
	if (CFont::LanguageSet == FONT_LANGSET_JAPANESE)
		return c & 0x7fff;
	return c;
}

bool
CMessages::WideStringCompare(wchar *str1, wchar *str2, uint16 size)
{
	uint16 len1 = GetWideStringLength(str1);
	uint16 len2 = GetWideStringLength(str2);
	if (len1 != len2 && (len1 < size || len2 < size))
		return false;

	for (int32 i = 0; i < size; i++) {
		if (!jappy(str1[i]))
			break;

		if (jappy(str1[i]) != jappy(str2[i]))
			return false;
	}
	return true;
}

void
CMessages::Process()
{
	for (int32 style = 0; style < 6; style++) {
		if (BIGMessages[style].m_Stack[0].m_pText != nil && CTimer::GetTimeInMilliseconds() > BIGMessages[style].m_Stack[0].m_nTime + BIGMessages[style].m_Stack[0].m_nStartTime) {
			BIGMessages[style].m_Stack[0].m_pText = nil;

			int32 i = 0;
			while (i < 3) {
				if (BIGMessages[style].m_Stack[i + 1].m_pText == nil) break;
				BIGMessages[style].m_Stack[i] = BIGMessages[style].m_Stack[i + 1];
				i++;
			}

			BIGMessages[style].m_Stack[i].m_pText = nil;
			BIGMessages[style].m_Stack[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
		}
	}

	if (BriefMessages[0].m_pText != nil && CTimer::GetTimeInMilliseconds() > BriefMessages[0].m_nTime + BriefMessages[0].m_nStartTime) {
		BriefMessages[0].m_pText = nil;
		int32 i = 0;
		while (i < NUMBRIEFMESSAGES-1) {
			if (BriefMessages[i + 1].m_pText == nil)
				break;

			BriefMessages[i] = BriefMessages[i + 1];
			i++;
		}
		CMessages::BriefMessages[i].m_pText = nil;
		CMessages::BriefMessages[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
		if (BriefMessages[0].m_pText != nil)
			AddToPreviousBriefArray(
				BriefMessages[0].m_pText,
				BriefMessages[0].m_nNumber[0],
				BriefMessages[0].m_nNumber[1],
				BriefMessages[0].m_nNumber[2],
				BriefMessages[0].m_nNumber[3],
				BriefMessages[0].m_nNumber[4],
				BriefMessages[0].m_nNumber[5],
				BriefMessages[0].m_pString);
	}
}

void
CMessages::Display()
{
	wchar outstr[256];

	DefinedState();

	for (int32 i = 0; i < NUMBIGMESSAGES; i++) {
		InsertNumberInString(
			BIGMessages[i].m_Stack[0].m_pText,
			BIGMessages[i].m_Stack[0].m_nNumber[0],
			BIGMessages[i].m_Stack[0].m_nNumber[1],
			BIGMessages[i].m_Stack[0].m_nNumber[2],
			BIGMessages[i].m_Stack[0].m_nNumber[3],
			BIGMessages[i].m_Stack[0].m_nNumber[4],
			BIGMessages[i].m_Stack[0].m_nNumber[5],
			outstr);
		InsertStringInString(outstr, BIGMessages[i].m_Stack[0].m_pString);
		InsertPlayerControlKeysInString(outstr);
		CHud::SetBigMessage(outstr, i);
	}

	InsertNumberInString(
		BriefMessages[0].m_pText,
		BriefMessages[0].m_nNumber[0],
		BriefMessages[0].m_nNumber[1],
		BriefMessages[0].m_nNumber[2],
		BriefMessages[0].m_nNumber[3],
		BriefMessages[0].m_nNumber[4],
		BriefMessages[0].m_nNumber[5],
		outstr);
	InsertStringInString(outstr, BriefMessages[0].m_pString);
	InsertPlayerControlKeysInString(outstr);
	CHud::SetMessage(outstr);
}

void
CMessages::AddMessage(wchar *msg, uint32 time, uint16 flag)
{
	wchar outstr[512]; // unused
	WideStringCopy(outstr, msg, 256);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	int32 i = 0;
	while (i < NUMBRIEFMESSAGES && BriefMessages[i].m_pText != nil)
		i++;
	if (i >= NUMBRIEFMESSAGES) return;

	BriefMessages[i].m_pText = msg;
	BriefMessages[i].m_nFlag = flag;
	BriefMessages[i].m_nTime = time;
	BriefMessages[i].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BriefMessages[i].m_nNumber[0] = -1;
	BriefMessages[i].m_nNumber[1] = -1;
	BriefMessages[i].m_nNumber[2] = -1;
	BriefMessages[i].m_nNumber[3] = -1;
	BriefMessages[i].m_nNumber[4] = -1;
	BriefMessages[i].m_nNumber[5] = -1;
	BriefMessages[i].m_pString = nil;
	if (i == 0)
		AddToPreviousBriefArray(
			BriefMessages[0].m_pText,
			BriefMessages[0].m_nNumber[0],
			BriefMessages[0].m_nNumber[1],
			BriefMessages[0].m_nNumber[2],
			BriefMessages[0].m_nNumber[3],
			BriefMessages[0].m_nNumber[4],
			BriefMessages[0].m_nNumber[5],
			BriefMessages[0].m_pString);
}

void
CMessages::AddMessageJumpQ(wchar *msg, uint32 time, uint16 flag)
{
	wchar outstr[512]; // unused
	WideStringCopy(outstr, msg, 256);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	BriefMessages[0].m_pText = msg;
	BriefMessages[0].m_nFlag = flag;
	BriefMessages[0].m_nTime = time;
	BriefMessages[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BriefMessages[0].m_nNumber[0] = -1;
	BriefMessages[0].m_nNumber[1] = -1;
	BriefMessages[0].m_nNumber[2] = -1;
	BriefMessages[0].m_nNumber[3] = -1;
	BriefMessages[0].m_nNumber[4] = -1;
	BriefMessages[0].m_nNumber[5] = -1;
	BriefMessages[0].m_pString = nil;
	AddToPreviousBriefArray(msg, -1, -1, -1, -1, -1, -1, 0);
}

void
CMessages::AddMessageSoon(wchar *msg, uint32 time, uint16 flag)
{
	wchar outstr[512]; // unused
	WideStringCopy(outstr, msg, 256);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	if (BriefMessages[0].m_pText != nil) {
		for (int i = NUMBRIEFMESSAGES-1; i > 1; i--)
			BriefMessages[i] = BriefMessages[i-1];

		BriefMessages[1].m_pText = msg;
		BriefMessages[1].m_nFlag = flag;
		BriefMessages[1].m_nTime = time;
		BriefMessages[1].m_nStartTime = CTimer::GetTimeInMilliseconds();
		BriefMessages[1].m_nNumber[0] = -1;
		BriefMessages[1].m_nNumber[1] = -1;
		BriefMessages[1].m_nNumber[2] = -1;
		BriefMessages[1].m_nNumber[3] = -1;
		BriefMessages[1].m_nNumber[4] = -1;
		BriefMessages[1].m_nNumber[5] = -1;
		BriefMessages[1].m_pString = nil;
	}else{
		BriefMessages[0].m_pText = msg;
		BriefMessages[0].m_nFlag = flag;
		BriefMessages[0].m_nTime = time;
		BriefMessages[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
		BriefMessages[0].m_nNumber[0] = -1;
		BriefMessages[0].m_nNumber[1] = -1;
		BriefMessages[0].m_nNumber[2] = -1;
		BriefMessages[0].m_nNumber[3] = -1;
		BriefMessages[0].m_nNumber[4] = -1;
		BriefMessages[0].m_nNumber[5] = -1;
		BriefMessages[0].m_pString = nil;
		AddToPreviousBriefArray(msg, -1, -1, -1, -1, -1, -1, nil);
	}
}

void
CMessages::ClearMessages()
{
	for (int32 i = 0; i < NUMBIGMESSAGES; i++) {
		for (int32 j = 0; j < 4; j++) {
			BIGMessages[i].m_Stack[j].m_pText = nil;
			BIGMessages[i].m_Stack[j].m_pString = nil;
		}
	}
	ClearSmallMessagesOnly();
}

void
CMessages::ClearSmallMessagesOnly()
{
	for (int32 i = 0; i < NUMBRIEFMESSAGES; i++) {
		BriefMessages[i].m_pText = nil;
		BriefMessages[i].m_pString = nil;
	}
}

void
CMessages::AddBigMessage(wchar *msg, uint32 time, uint16 style)
{
	wchar outstr[512]; // unused
	WideStringCopy(outstr, msg, 256);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	BIGMessages[style].m_Stack[0].m_pText = msg;
	BIGMessages[style].m_Stack[0].m_nFlag = 0;
	BIGMessages[style].m_Stack[0].m_nTime = time;
	BIGMessages[style].m_Stack[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BIGMessages[style].m_Stack[0].m_nNumber[0] = -1;
	BIGMessages[style].m_Stack[0].m_nNumber[1] = -1;
	BIGMessages[style].m_Stack[0].m_nNumber[2] = -1;
	BIGMessages[style].m_Stack[0].m_nNumber[3] = -1;
	BIGMessages[style].m_Stack[0].m_nNumber[4] = -1;
	BIGMessages[style].m_Stack[0].m_nNumber[5] = -1;
	BIGMessages[style].m_Stack[0].m_pString = nil;
}
void
CMessages::AddBigMessageQ(wchar *msg, uint32 time, uint16 style)
{
	wchar outstr[512]; // unused
	WideStringCopy(outstr, msg, 256);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	int32 i = 0;
	while (i < 4 && BIGMessages[style].m_Stack[i].m_pText != nil)
		i++;

	if (i >= 4) return;

	BIGMessages[style].m_Stack[i].m_pText = msg;
	BIGMessages[style].m_Stack[i].m_nFlag = 0;
	BIGMessages[style].m_Stack[i].m_nTime = time;
	BIGMessages[style].m_Stack[i].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BIGMessages[style].m_Stack[i].m_nNumber[0] = -1;
	BIGMessages[style].m_Stack[i].m_nNumber[1] = -1;
	BIGMessages[style].m_Stack[i].m_nNumber[2] = -1;
	BIGMessages[style].m_Stack[i].m_nNumber[3] = -1;
	BIGMessages[style].m_Stack[i].m_nNumber[4] = -1;
	BIGMessages[style].m_Stack[i].m_nNumber[5] = -1;
	BIGMessages[style].m_Stack[i].m_pString = nil;
}

void
CMessages::AddToPreviousBriefArray(wchar *text, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, wchar *string)
{
	int32 i = 0;
	while (i < NUMPREVIOUSBRIEFS) {
		if (PreviousBriefs[i].m_pText == nil)
			break;
		if (PreviousBriefs[i].m_nNumber[0] == n1
			&& PreviousBriefs[i].m_nNumber[1] == n2
			&& PreviousBriefs[i].m_nNumber[2] == n3
			&& PreviousBriefs[i].m_nNumber[3] == n4
			&& PreviousBriefs[i].m_nNumber[4] == n5
			&& PreviousBriefs[i].m_nNumber[5] == n6
			&& PreviousBriefs[i].m_pText == text
			&& PreviousBriefs[i].m_pString == string)
			return;

		i++;
	}

	if (i != 0) {
		if (i == NUMPREVIOUSBRIEFS) i -= 2;
		else i--;

		while (i >= 0) {
			PreviousBriefs[i + 1] = PreviousBriefs[i];
			i--;
		}
	}
	PreviousBriefs[0].m_pText = text;
	PreviousBriefs[0].m_nNumber[0] = n1;
	PreviousBriefs[0].m_nNumber[1] = n2;
	PreviousBriefs[0].m_nNumber[2] = n3;
	PreviousBriefs[0].m_nNumber[3] = n4;
	PreviousBriefs[0].m_nNumber[4] = n5;
	PreviousBriefs[0].m_nNumber[5] = n6;
	PreviousBriefs[0].m_pString = string;
}

void
CMessages::InsertNumberInString(wchar *str, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6, wchar *outstr)
{
	char numStr[10];
	wchar wNumStr[10];

	if (str == nil) {
		*outstr = '\0';
		return;
	}

	int32 size = GetWideStringLength(str);

	int32 i = 0;

	for (int32 c = 0; c < size;) {
		if ((CFont::LanguageSet == FONT_LANGSET_JAPANESE && str[c] == (0x8000 | '~') && str[c + 1] == (0x8000 | '1') && str[c + 2] == (0x8000 | '~')) ||
			(CFont::LanguageSet != FONT_LANGSET_JAPANESE && str[c] == '~' && str[c + 1] == '1' && str[c + 2] == '~'))
		{
			//if (str[c] == '~' && str[c + 1] == '1' && str[c + 2] == '~') {
			switch (i) {
			case 0: sprintf(numStr, "%d", n1); break;
			case 1: sprintf(numStr, "%d", n2); break;
			case 2: sprintf(numStr, "%d", n3); break;
			case 3: sprintf(numStr, "%d", n4); break;
			case 4: sprintf(numStr, "%d", n5); break;
			case 5: sprintf(numStr, "%d", n6); break;
			}
			i++;
			AsciiToUnicode(numStr, wNumStr);

			int j = 0;
			while (wNumStr[j] != '\0')
				*(outstr++) = wNumStr[j++];
				
			c += 3;
		} else {
			*(outstr++) = str[c++];
		}
	}
	*outstr = '\0';
}

void
CMessages::InsertStringInString(wchar *str1, wchar *str2)
{
	wchar tempstr[256];

	if (!str1 || !str2) return;

	int32 str1_size = GetWideStringLength(str1);
	int32 str2_size = GetWideStringLength(str2);
	int32 total_size = str1_size + str2_size;
	
	wchar *_str1 = str1;
	uint16 i;
	for (i = 0; i < total_size; ) {
		if ((CFont::LanguageSet == FONT_LANGSET_JAPANESE && *_str1 == (0x8000 | '~') && *(_str1 + 1) == (0x8000 | 'a') && *(_str1 + 2) == (0x8000 | '~'))
			|| (CFont::LanguageSet != FONT_LANGSET_JAPANESE && *_str1 == '~' && *(_str1 + 1) == 'a' && *(_str1 + 2) == '~'))
		{
			//if (*_str1 == '~' && *(_str1 + 1) == 'a' && *(_str1 + 2) == '~') {
			_str1 += 3;
			for (int j = 0; j < str2_size; j++) {
				tempstr[i++] = str2[j];
			}
		} else {
			tempstr[i++] = *(_str1++);
		}
	}
	tempstr[i] = '\0';

	for (i = 0; i < total_size; i++)
		str1[i] = tempstr[i];

	while (i < 256)
		str1[i++] = '\0';
}

void
CMessages::InsertPlayerControlKeysInString(wchar *str)
{
	uint16 i;
	wchar outstr[256];
	wchar keybuf[256];

	if (!str) return;
	uint16 strSize = GetWideStringLength(str);
	memset(keybuf, 0, 256*sizeof(wchar));

	wchar *_outstr = outstr;
	for (i = 0; i < strSize;) {
		if ((CFont::LanguageSet == FONT_LANGSET_JAPANESE && str[i] == (0x8000 | '~') && str[i + 1] == (0x8000 | 'k') && str[i + 2] == (0x8000 | '~')) ||
			(CFont::LanguageSet != FONT_LANGSET_JAPANESE && str[i] == '~' && str[i + 1] == 'k' && str[i + 2] == '~')) {
			i += 4;
			for (int32 cont = 0; cont < MAX_CONTROLLERACTIONS; cont++) {
				uint16 contSize = GetWideStringLength(ControlsManager.m_aActionNames[cont]);
				if (contSize != 0) {
					if (WideStringCompare(&str[i], ControlsManager.m_aActionNames[cont], contSize)) {
						ControlsManager.GetWideStringOfCommandKeys(cont, keybuf, 256);
						uint16 keybuf_size = GetWideStringLength(keybuf);
						for (uint16 j = 0; j < keybuf_size; j++) {
							*(_outstr++) = keybuf[j];
							keybuf[j] = '\0';
						}
						i += contSize + 1;
					}
				}
			}
		} else {
			*(_outstr++) = str[i++];
		}
	}
	*_outstr = '\0';

	for (i = 0; i < GetWideStringLength(outstr); i++)
		str[i] = outstr[i];

	while (i < 256)
		str[i++] = '\0';
}

void
CMessages::AddMessageWithNumber(wchar *str, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6)
{
	wchar outstr[512]; // unused
	InsertNumberInString(str, n1, n2, n3, n4, n5, n6, outstr);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	uint16 i = 0;
	while (i < NUMBRIEFMESSAGES && BriefMessages[i].m_pText)
		i++;

	if (i >= NUMBRIEFMESSAGES) return;

	BriefMessages[i].m_pText = str;
	BriefMessages[i].m_nFlag = flag;
	BriefMessages[i].m_nTime = time;
	BriefMessages[i].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BriefMessages[i].m_nNumber[0] = n1;
	BriefMessages[i].m_nNumber[1] = n2;
	BriefMessages[i].m_nNumber[2] = n3;
	BriefMessages[i].m_nNumber[3] = n4;
	BriefMessages[i].m_nNumber[4] = n5;
	BriefMessages[i].m_nNumber[5] = n6;
	BriefMessages[i].m_pString = nil;
	if (i == 0)
		AddToPreviousBriefArray(
			BriefMessages[0].m_pText,
			BriefMessages[0].m_nNumber[0],
			BriefMessages[0].m_nNumber[1],
			BriefMessages[0].m_nNumber[2],
			BriefMessages[0].m_nNumber[3],
			BriefMessages[0].m_nNumber[4],
			BriefMessages[0].m_nNumber[5],
			BriefMessages[0].m_pString);
}

void 
CMessages::AddMessageJumpQWithNumber(wchar *str, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6)
{
	wchar outstr[512]; // unused
	InsertNumberInString(str, n1, n2, n3, n4, n5, n6, outstr);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	BriefMessages[0].m_pText = str;
	BriefMessages[0].m_nFlag = flag;
	BriefMessages[0].m_nTime = time;
	BriefMessages[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BriefMessages[0].m_nNumber[0] = n1;
	BriefMessages[0].m_nNumber[1] = n2;
	BriefMessages[0].m_nNumber[2] = n3;
	BriefMessages[0].m_nNumber[3] = n4;
	BriefMessages[0].m_nNumber[4] = n5;
	BriefMessages[0].m_nNumber[5] = n6;
	BriefMessages[0].m_pString = nil;
	AddToPreviousBriefArray(str, n1, n2, n3, n4, n5, n6, nil);
}

void
CMessages::AddMessageSoonWithNumber(wchar *str, uint32 time, uint16 flag, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6)
{
	wchar outstr[512]; // unused
	InsertNumberInString(str, n1, n2, n3, n4, n5, n6, outstr);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	if (BriefMessages[0].m_pText != nil) {
		for (int32 i = NUMBRIEFMESSAGES-1; i > 1; i--)
			BriefMessages[i] = BriefMessages[i-1];

		BriefMessages[1].m_pText = str;
		BriefMessages[1].m_nFlag = flag;
		BriefMessages[1].m_nTime = time;
		BriefMessages[1].m_nStartTime = CTimer::GetTimeInMilliseconds();
		BriefMessages[1].m_nNumber[0] = n1;
		BriefMessages[1].m_nNumber[1] = n2;
		BriefMessages[1].m_nNumber[2] = n3;
		BriefMessages[1].m_nNumber[3] = n4;
		BriefMessages[1].m_nNumber[4] = n5;
		BriefMessages[1].m_nNumber[5] = n6;
		BriefMessages[1].m_pString = nil;
	} else {
		BriefMessages[0].m_pText = str;
		BriefMessages[0].m_nFlag = flag;
		BriefMessages[0].m_nTime = time;
		BriefMessages[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
		BriefMessages[0].m_nNumber[0] = n1;
		BriefMessages[0].m_nNumber[1] = n2;
		BriefMessages[0].m_nNumber[2] = n3;
		BriefMessages[0].m_nNumber[3] = n4;
		BriefMessages[0].m_nNumber[4] = n5;
		BriefMessages[0].m_nNumber[5] = n6;
		BriefMessages[0].m_pString = nil;
		AddToPreviousBriefArray(str, n1, n2, n3, n4, n5, n6, nil);
	}
}

void
CMessages::AddBigMessageWithNumber(wchar *str, uint32 time, uint16 style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6)
{
	wchar outstr[512]; // unused
	InsertNumberInString(str, n1, n2, n3, n4, n5, n6, outstr);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	BIGMessages[style].m_Stack[0].m_pText = str;
	BIGMessages[style].m_Stack[0].m_nFlag = 0;
	BIGMessages[style].m_Stack[0].m_nTime = time;
	BIGMessages[style].m_Stack[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BIGMessages[style].m_Stack[0].m_nNumber[0] = n1;
	BIGMessages[style].m_Stack[0].m_nNumber[1] = n2;
	BIGMessages[style].m_Stack[0].m_nNumber[2] = n3;
	BIGMessages[style].m_Stack[0].m_nNumber[3] = n4;
	BIGMessages[style].m_Stack[0].m_nNumber[4] = n5;
	BIGMessages[style].m_Stack[0].m_nNumber[5] = n6;
	BIGMessages[style].m_Stack[0].m_pString = nil;
}

void
CMessages::AddBigMessageWithNumberQ(wchar *str, uint32 time, uint16 style, int32 n1, int32 n2, int32 n3, int32 n4, int32 n5, int32 n6)
{
	wchar outstr[512]; // unused
	InsertNumberInString(str, n1, n2, n3, n4, n5, n6, outstr);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	int32 i = 0;

	while (i < 4 && BIGMessages[style].m_Stack[i].m_pText != nil)
		i++;

	if (i >= 4) return;

	BIGMessages[style].m_Stack[i].m_pText = str;
	BIGMessages[style].m_Stack[i].m_nFlag = 0;
	BIGMessages[style].m_Stack[i].m_nTime = time;
	BIGMessages[style].m_Stack[i].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BIGMessages[style].m_Stack[i].m_nNumber[0] = n1;
	BIGMessages[style].m_Stack[i].m_nNumber[1] = n2;
	BIGMessages[style].m_Stack[i].m_nNumber[2] = n3;
	BIGMessages[style].m_Stack[i].m_nNumber[3] = n4;
	BIGMessages[style].m_Stack[i].m_nNumber[4] = n5;
	BIGMessages[style].m_Stack[i].m_nNumber[5] = n6;
	BIGMessages[style].m_Stack[i].m_pString = nil;
}

void
CMessages::AddMessageWithString(wchar *text, uint32 time, uint16 flag, wchar *str)
{
	wchar outstr[512]; // unused
	WideStringCopy(outstr, text, 256);
	InsertStringInString(outstr, str);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	int32 i = 0;
	while (i < NUMBRIEFMESSAGES && BriefMessages[i].m_pText != nil)
		i++;

	if (i >= NUMBRIEFMESSAGES) return;

	BriefMessages[i].m_pText = text;
	BriefMessages[i].m_nFlag = flag;
	BriefMessages[i].m_nTime = time;
	BriefMessages[i].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BriefMessages[i].m_nNumber[0] = -1;
	BriefMessages[i].m_nNumber[1] = -1;
	BriefMessages[i].m_nNumber[2] = -1;
	BriefMessages[i].m_nNumber[3] = -1;
	BriefMessages[i].m_nNumber[4] = -1;
	BriefMessages[i].m_nNumber[5] = -1;
	BriefMessages[i].m_pString = str;
	if (i == 0)
		AddToPreviousBriefArray(
			BriefMessages[0].m_pText,
			BriefMessages[0].m_nNumber[0],
			BriefMessages[0].m_nNumber[1],
			BriefMessages[0].m_nNumber[2],
			BriefMessages[0].m_nNumber[3],
			BriefMessages[0].m_nNumber[4],
			BriefMessages[0].m_nNumber[5],
			BriefMessages[0].m_pString);
}

void
CMessages::AddMessageJumpQWithString(wchar *text, uint32 time, uint16 flag, wchar *str)
{
	wchar outstr[512]; // unused
	WideStringCopy(outstr, text, 256);
	InsertStringInString(outstr, str);
	InsertPlayerControlKeysInString(outstr);
	GetWideStringLength(outstr);

	BriefMessages[0].m_pText = text;
	BriefMessages[0].m_nFlag = flag;
	BriefMessages[0].m_nTime = time;
	BriefMessages[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
	BriefMessages[0].m_nNumber[0] = -1;
	BriefMessages[0].m_nNumber[1] = -1;
	BriefMessages[0].m_nNumber[2] = -1;
	BriefMessages[0].m_nNumber[3] = -1;
	BriefMessages[0].m_nNumber[4] = -1;
	BriefMessages[0].m_nNumber[5] = -1;
	BriefMessages[0].m_pString = str;
	AddToPreviousBriefArray(text, -1, -1, -1, -1, -1, -1, str);
}

inline bool
FastWideStringComparison(wchar *str1, wchar *str2)
{
	while (*str1 == *str2) {
		++str1;
		++str2;
		if (!*str1 && !*str2) return true;
	}
	return false;
}

void
CMessages::ClearThisPrint(wchar *str)
{
	bool equal;

	do {
		equal = false;
		uint16 i = 0;
		while (i < NUMBRIEFMESSAGES) {
			if (BriefMessages[i].m_pText == nil)
				break;
			
			equal = FastWideStringComparison(str, BriefMessages[i].m_pText);

			if (equal) break;
			i++;
		}

		if (equal) {
			if (i != 0) {
				BriefMessages[i].m_pText = nil;
				while (i < NUMBRIEFMESSAGES-1) {
					if (BriefMessages[i + 1].m_pText == nil)
						break;

					BriefMessages[i] = BriefMessages[i + 1];
					i++;
				}
				BriefMessages[i].m_pText = nil;
			} else {
				BriefMessages[0].m_pText = nil;
				while (i < NUMBRIEFMESSAGES-1) {
					if (BriefMessages[i + 1].m_pText == nil)
						break;
					BriefMessages[i] = BriefMessages[i + 1];
					i++;
				}
				BriefMessages[i].m_pText = nil;
				BriefMessages[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
				if (BriefMessages[0].m_pText == nil)
					AddToPreviousBriefArray(
						BriefMessages[0].m_pText,
						BriefMessages[0].m_nNumber[0],
						BriefMessages[0].m_nNumber[1],
						BriefMessages[0].m_nNumber[2],
						BriefMessages[0].m_nNumber[3],
						BriefMessages[0].m_nNumber[4],
						BriefMessages[0].m_nNumber[5],
						BriefMessages[0].m_pString);
			}
		}
	} while (equal);
}

void
CMessages::ClearThisBigPrint(wchar *str)
{
	bool equal;

	do {
		uint16 i = 0;
		equal = false;
		uint16 style = 0;
		while (style < NUMBIGMESSAGES)
		{
			if (i >= 4)
				break;

			if (CMessages::BIGMessages[style].m_Stack[i].m_pText == nil || equal)
				break;

			equal = FastWideStringComparison(str, BIGMessages[style].m_Stack[i].m_pText);

			if (!equal && ++i == 4) {
				i = 0;
				style++;
			}
		}
		if (equal) {
			if (i != 0) {
				BIGMessages[style].m_Stack[i].m_pText = nil;
				while (i < 3) {
					if (BIGMessages[style].m_Stack[i + 1].m_pText == nil)
						break;
					BIGMessages[style].m_Stack[i] = BIGMessages[style].m_Stack[i + 1];
					i++;
				}
				BIGMessages[style].m_Stack[i].m_pText = nil;
			} else {
				BIGMessages[style].m_Stack[0].m_pText = 0;
				i = 0;
				while (i < 3) {
					if (BIGMessages[style].m_Stack[i + 1].m_pText == nil)
						break;
					BIGMessages[style].m_Stack[i] = BIGMessages[style].m_Stack[i + 1];
					i++;
				}
				BIGMessages[style].m_Stack[i].m_pText = nil;
				BIGMessages[style].m_Stack[0].m_nStartTime = CTimer::GetTimeInMilliseconds();
			}
		}
	} while (equal);
}

void
CMessages::ClearAllMessagesDisplayedByGame()
{
	ClearMessages();
	for (int32 i = 0; i < NUMPREVIOUSBRIEFS; i++) {
		PreviousBriefs[i].m_pText = nil;
		PreviousBriefs[i].m_pString = nil;
	}
	CHud::GetRidOfAllHudMessages();
	CUserDisplay::Pager.ClearMessages();
}

STARTPATCHES
	InjectHook(0x529310, CMessages::Init, PATCH_JUMP);
	InjectHook(0x529490, CMessages::GetWideStringLength, PATCH_JUMP);
	InjectHook(0x5294B0, CMessages::WideStringCopy, PATCH_JUMP);
	InjectHook(0x529510, CMessages::WideStringCompare, PATCH_JUMP);
	InjectHook(0x529580, CMessages::Process, PATCH_JUMP);
	InjectHook(0x529800, CMessages::Display, PATCH_JUMP);
	InjectHook(0x529900, CMessages::AddMessage, PATCH_JUMP);
	InjectHook(0x529A10, CMessages::AddMessageJumpQ, PATCH_JUMP);
	InjectHook(0x529AF0, CMessages::AddMessageSoon, PATCH_JUMP);
	InjectHook(0x529CE0, CMessages::ClearMessages, PATCH_JUMP);
	InjectHook(0x529E00, CMessages::ClearSmallMessagesOnly, PATCH_JUMP);
	InjectHook(0x529EB0, CMessages::AddBigMessage, PATCH_JUMP);
	InjectHook(0x529F60, CMessages::AddBigMessageQ, PATCH_JUMP);
	InjectHook(0x52A040, CMessages::AddToPreviousBriefArray, PATCH_JUMP);
	InjectHook(0x52A1A0, CMessages::InsertNumberInString, PATCH_JUMP);
	InjectHook(0x52A300, CMessages::InsertStringInString, PATCH_JUMP);
	InjectHook(0x52A490, CMessages::InsertPlayerControlKeysInString, PATCH_JUMP);
	InjectHook(0x52A850, CMessages::AddMessageWithNumber, PATCH_JUMP);
	InjectHook(0x52A9A0, CMessages::AddMessageJumpQWithNumber, PATCH_JUMP);
	InjectHook(0x52AAC0, CMessages::AddMessageSoonWithNumber, PATCH_JUMP);
	InjectHook(0x52AD10, CMessages::AddBigMessageWithNumber, PATCH_JUMP);
	InjectHook(0x52AE00, CMessages::AddBigMessageWithNumberQ, PATCH_JUMP);
	InjectHook(0x52AF30, CMessages::AddMessageWithString, PATCH_JUMP);
	InjectHook(0x52B050, CMessages::AddMessageJumpQWithString, PATCH_JUMP);
	InjectHook(0x52B140, CMessages::ClearThisPrint, PATCH_JUMP);
	InjectHook(0x52B3C0, CMessages::ClearThisBigPrint, PATCH_JUMP);
	InjectHook(0x52B670, CMessages::ClearAllMessagesDisplayedByGame, PATCH_JUMP);
ENDPATCHES
