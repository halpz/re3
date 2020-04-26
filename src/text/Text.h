#pragma once

void AsciiToUnicode(const char *src, wchar *dst);
char *UnicodeToAscii(wchar *src);
char *UnicodeToAsciiForSaveLoad(wchar *src);
void UnicodeStrcpy(wchar *dst, const wchar *src);
int UnicodeStrlen(const wchar *str);
void TextCopy(wchar *dst, const wchar *src);

struct CKeyEntry
{
	wchar *value;
	char key[8];
};
// If this fails, CKeyArray::Load will have to be fixed
static_assert(sizeof(CKeyEntry) == 12, "CKeyEntry: error");

class CKeyArray
{
public:
	CKeyEntry *entries;
	int numEntries;

	CKeyArray(void) : entries(nil), numEntries(0) {}
	~CKeyArray(void) { Unload(); }
	void Load(uint32 length, uint8 *data, int *offset);
	void Unload(void);
	void Update(wchar *chars);
	CKeyEntry *BinarySearch(const char *key, CKeyEntry *entries, int16 low, int16 high);
	wchar *Search(const char *key);
};

class CData
{
public:
	wchar *chars;
	int numChars;

	CData(void) : chars(nil), numChars(0) {}
	~CData(void) { Unload(); }
	void Load(uint32 length, uint8 *data, int *offset);
	void Unload(void);
};

class CText
{
	CKeyArray keyArray;
	CData data;
	char encoding;
public:
	CText(void);
	void Load(void);
	void Unload(void);
	wchar *Get(const char *key);
	wchar GetUpperCase(wchar c);
	void UpperCase(wchar *s);
};

extern CText TheText;
