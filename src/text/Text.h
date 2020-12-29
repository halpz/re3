#pragma once

char *UnicodeToAscii(wchar *src);
char *UnicodeToAsciiForSaveLoad(wchar *src);
char *UnicodeToAsciiForMemoryCard(wchar *src);
void TextCopy(wchar *dst, const wchar *src);

struct CKeyEntry
{
#ifdef FIX_BUGS
	uint32 valueOffset;
#else
	wchar *value;
#endif
	char key[8];
};

// If this fails, CKeyArray::Load will have to be fixed
VALIDATE_SIZE(CKeyEntry, 12);

class CKeyArray
{
public:
	CKeyEntry *entries;
	int numEntries;	// You can make this size_t if you want to exceed 32-bit boundaries, everything else should be ready.

	CKeyArray(void) : entries(nil), numEntries(0) {}
	~CKeyArray(void) { Unload(); }
	void Load(size_t length, uint8 *data, ssize_t *offset);
	void Unload(void);
	void Update(wchar *chars);
	CKeyEntry *BinarySearch(const char *key, CKeyEntry *entries, int16 low, int16 high);
#ifdef FIX_BUGS
	wchar *Search(const char *key, wchar *data);
#else
	wchar *Search(const char *key);
#endif
};

class CData
{
public:
	wchar *chars;
	int numChars; // You can make this size_t if you want to exceed 32-bit boundaries, everything else should be ready.

	CData(void) : chars(nil), numChars(0) {}
	~CData(void) { Unload(); }
	void Load(size_t length, uint8 *data, ssize_t *offset);
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
