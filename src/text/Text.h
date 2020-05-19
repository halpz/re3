#pragma once

void AsciiToUnicode(const char *src, wchar *dst);
char *UnicodeToAscii(wchar *src);
char *UnicodeToAsciiForSaveLoad(wchar *src);
void UnicodeStrcpy(wchar *dst, const wchar *src);
int UnicodeStrlen(const wchar *str);
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
	int numEntries;

	CKeyArray(void) : entries(nil), numEntries(0) {}
	~CKeyArray(void) { Unload(); }
	void Load(uint32 length, int file, uint32 *offset);
	void Unload(void);
	void Update(wchar *chars);
	CKeyEntry *BinarySearch(const char *key, CKeyEntry *entries, int16 low, int16 high);
#ifdef FIX_BUGS
	wchar *Search(const char *key, wchar *data, uint8 *result);
#else
	wchar *Search(const char *key, uint8* result);
#endif
};

class CData
{
public:
	wchar *chars;
	int numChars;

	CData(void) : chars(nil), numChars(0) {}
	~CData(void) { Unload(); }
	void Load(uint32 length, int file, uint32 *offset);
	void Unload(void);
};

class CMissionTextOffsets
{
public:
	struct Entry
	{
		char szMissionName[8];
		uint32 offset;
	};

	enum {MAX_MISSION_TEXTS = 90}; // beware that LCS has more

	Entry data[MAX_MISSION_TEXTS];
	uint16 size;

	CMissionTextOffsets(void) : size(0) {}
	void Load(uint32 table_size, int file, uint32* bytes_read, int);
};

struct ChunkHeader
{
	char magic[4];
	int size;
};

class CText
{
	CKeyArray keyArray;
	CData data;
	CKeyArray mission_keyArray;
	CData mission_data;
	char encoding;
	bool bHasMissionTextOffsets;
	bool bIsMissionTextLoaded;
	char szMissionTableName[8];
	CMissionTextOffsets MissionTextOffsets;
public:
	CText(void);
	void Load(void);
	void Unload(void);
	wchar *Get(const char *key);
	wchar GetUpperCase(wchar c);
	void UpperCase(wchar *s);
	void GetNameOfLoadedMissionText(char *outName);
	void ReadChunkHeader(ChunkHeader *buf, int32 file, uint32 *bytes_read);
	void LoadMissionText(char *MissionTableName);
};

extern CText TheText;
