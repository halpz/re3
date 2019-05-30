#pragma once

struct CKeyEntry
{
	wchar_t *value;
	char key[8];
};
// If this fails, CKeyArray::Load will have to be fixed
static_assert(sizeof(CKeyEntry) == 12, "CKeyEntry: error");

class CKeyArray
{
public:
	CKeyEntry *entries;
	int numEntries;

	void Load(uint32 length, uint8 *data, int *offset);
	void Unload(void);
	void Update(wchar_t *chars);
	CKeyEntry *BinarySearch(const char *key, CKeyEntry *entries, int16 low, int16 high);
	wchar_t *Search(const char *key);
};

class CData
{
public:
	wchar_t *chars;
	int numChars;

	void Load(uint32 length, uint8 *data, int *offset);
	void Unload(void);
};

class CText
{
	CKeyArray keyArray;
	CData data;
	int8 unknown;
public:
	CText(void);
	~CText(void);
	void Load(void);
	void Unload(void);
	wchar_t *Get(const char *key);
};

extern CText &TheText;
