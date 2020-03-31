#include "common.h"
#include "patcher.h"
#include "FileMgr.h"
#include "Frontend.h"
#include "Messages.h"
#include "Text.h"

static wchar WideErrorString[25];

CText &TheText = *(CText*)0x941520;

CText::CText(void)
{
	encoding = 'e';
	memset(WideErrorString, 0, sizeof(WideErrorString));
}

void
CText::Load(void)
{
	uint8 *filedata;
	char filename[32], type[4];
	int length;
	int offset, sectlen;

	Unload();
	filedata = new uint8[0x40000];

	CFileMgr::SetDir("TEXT");
	switch(CMenuManager::m_PrefsLanguage){
	case LANGUAGE_AMERICAN:
		sprintf(filename, "AMERICAN.GXT");
		break;
	case LANGUAGE_FRENCH:
		sprintf(filename, "FRENCH.GXT");
		break;
	case LANGUAGE_GERMAN:
		sprintf(filename, "GERMAN.GXT");
		break;
	case LANGUAGE_ITALIAN:
		sprintf(filename, "ITALIAN.GXT");
		break;
	case LANGUAGE_SPANISH:
		sprintf(filename, "SPANISH.GXT");
		break;
#ifdef MORE_LANGUAGES
	case LANGUAGE_RUSSIAN:
		sprintf(filename, "RUSSIAN.GXT");
		break;
	case LANGUAGE_JAPANESE:
		sprintf(filename, "JAPANESE.GXT");
		break;
#endif
	}

	length = CFileMgr::LoadFile(filename, filedata, 0x40000, "rb");
	CFileMgr::SetDir("");

	offset = 0;
	while(offset < length){
		type[0] = filedata[offset++];
		type[1] = filedata[offset++];
		type[2] = filedata[offset++];
		type[3] = filedata[offset++];
		sectlen = (int)filedata[offset+3]<<24 | (int)filedata[offset+2]<<16 |
			(int)filedata[offset+1]<<8 | (int)filedata[offset+0];
		offset += 4;
		if(sectlen != 0){
			if(strncmp(type, "TKEY", 4) == 0)
				keyArray.Load(sectlen, filedata, &offset);
			else if(strncmp(type, "TDAT", 4) == 0)
				data.Load(sectlen, filedata, &offset);
			else
				offset += sectlen;
		}
	}

	keyArray.Update(data.chars);

	delete[] filedata;
}

void
CText::Unload(void)
{
	CMessages::ClearAllMessagesDisplayedByGame();
	data.Unload();
	keyArray.Unload();
}

wchar*
CText::Get(const char *key)
{
	return keyArray.Search(key);
}

wchar UpperCaseTable[128] = {
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138,
	139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
	150, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137,
	138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148,
	149, 173, 173, 175, 176, 177, 178, 179, 180, 181, 182,
	183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193,
	194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204,
	205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215,
	216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226,
	227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237,
	238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248,
	249, 250, 251, 252, 253, 254, 255
};

wchar FrenchUpperCaseTable[128] = {
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138,
	139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
	150, 65, 65, 65, 65, 132, 133, 69, 69, 69, 69, 73, 73,
	73, 73, 79, 79, 79, 79, 85, 85, 85, 85, 173, 173, 175,
	176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
	187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197,
	198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
	209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
	220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230,
	231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241,
	242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252,
	253, 254, 255
};

wchar
CText::GetUpperCase(wchar c)
{
	switch (encoding)
	{
	case 'e':
		if (c >= 'a' && c <= 'z')
			return c - 32;
		break;
	case 'f':
		if (c >= 'a' && c <= 'z')
			return c - 32;

		if (c >= 128 && c <= 255)
			return FrenchUpperCaseTable[c-128];
		break;
	case 'g':
	case 'i':
	case 's':
		if (c >= 'a' && c <= 'z')
			return c - 32;

		if (c >= 128 && c <= 255)
			return UpperCaseTable[c-128];
		break;
	default:
		break;
	}
	return c;
}

void
CText::UpperCase(wchar *s)
{
	while(*s){
		*s = GetUpperCase(*s);
		s++;
	}
}


void
CKeyArray::Load(uint32 length, uint8 *data, int *offset)
{
	uint32 i;
	uint8 *rawbytes;

	numEntries = length / sizeof(CKeyEntry);
	entries = new CKeyEntry[numEntries];
	rawbytes = (uint8*)entries;

	for(i = 0; i < length; i++)
		rawbytes[i] = data[(*offset)++];
}

void
CKeyArray::Unload(void)
{
	delete[] entries;
	entries = nil;
	numEntries = 0;
}

void
CKeyArray::Update(wchar *chars)
{
	int i;
	for(i = 0; i < numEntries; i++)
		entries[i].value = (wchar*)((uint8*)chars + (uintptr)entries[i].value);
}

CKeyEntry*
CKeyArray::BinarySearch(const char *key, CKeyEntry *entries, int16 low, int16 high)
{
	int mid;
	int diff;

	if(low > high)
		return nil;

	mid = (low + high)/2;
	diff = strcmp(key, entries[mid].key);
	if(diff == 0)
		return &entries[mid];
	if(diff < 0)
		return BinarySearch(key, entries, low, mid-1);
	if(diff > 0)
		return BinarySearch(key, entries, mid+1, high);
	return nil;
}

wchar*
CKeyArray::Search(const char *key)
{
	CKeyEntry *found;
	char errstr[25];
	int i;

	found = BinarySearch(key, entries, 0, numEntries-1);
	if(found)
		return found->value;
	sprintf(errstr, "%s missing", key);
	for(i = 0; i < 25; i++)
		WideErrorString[i] = errstr[i];
	return WideErrorString;
}


void
CData::Load(uint32 length, uint8 *data, int *offset)
{
	uint32 i;
	uint8 *rawbytes;

	numChars = length / sizeof(wchar);
	chars = new wchar[numChars];
	rawbytes = (uint8*)chars;

	for(i = 0; i < length; i++)
		rawbytes[i] = data[(*offset)++];
}

void
CData::Unload(void)
{
	delete[] chars;
	chars = nil;
	numChars = 0;
}

void
AsciiToUnicode(const char *src, wchar *dst)
{
	while((*dst++ = *src++) != '\0');
}

#include "Game.h"

char*
UnicodeToAscii(wchar *src)
{
	static char aStr[256];
	int len;
	for(len = 0; *src != '\0' && len < 256-1; len++, src++)
		if(*src < 128 || (CGame::russianGame && *src < 256))
			aStr[len] = *src;
		else
			aStr[len] = '#';
	aStr[len] = '\0';
	return aStr;
}

char*
UnicodeToAsciiForSaveLoad(wchar *src)
{
	static char aStr[256];
	int len;
	for(len = 0; *src != '\0' && len < 256-1; len++, src++)
		if(*src < 256)
			aStr[len] = *src;
		else
			aStr[len] = '#';
	aStr[len] = '\0';
	return aStr;
}

void
UnicodeStrcpy(wchar *dst, const wchar *src)
{
	while((*dst++ = *src++) != '\0');
}

int
UnicodeStrlen(const wchar *str)
{
	int len;
	for(len = 0; *str != '\0'; len++, str++);
	return len;
}

void
TextCopy(wchar *dst, const wchar *src)
{
	while((*dst++ = *src++) != '\0');
}


STARTPATCHES
	InjectHook(0x52C3C0, &CText::Load, PATCH_JUMP);
	InjectHook(0x52C580, &CText::Unload, PATCH_JUMP);
	InjectHook(0x52C5A0, &CText::Get, PATCH_JUMP);
	InjectHook(0x52C220, &CText::GetUpperCase, PATCH_JUMP);
	InjectHook(0x52C2C0, &CText::UpperCase, PATCH_JUMP);

	InjectHook(0x52BE70, &CKeyArray::Load, PATCH_JUMP);
	InjectHook(0x52BF60, &CKeyArray::Unload, PATCH_JUMP);
	InjectHook(0x52BF80, &CKeyArray::Update, PATCH_JUMP);
	InjectHook(0x52C060, &CKeyArray::BinarySearch, PATCH_JUMP);
	InjectHook(0x52BFB0, &CKeyArray::Search, PATCH_JUMP);

	InjectHook(0x52C120, &CData::Load, PATCH_JUMP);
	InjectHook(0x52C200, &CData::Unload, PATCH_JUMP);

	InjectHook(0x52C2F0, &UnicodeToAscii, PATCH_JUMP);
ENDPATCHES
