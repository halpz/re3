#pragma once

enum eVarConsoleEntryType
{
	VCE_TYPE_INT8,
	VCE_TYPE_INT16,
	VCE_TYPE_INT32,
	VCE_TYPE_INT64,
	VCE_TYPE_UINT8,
	VCE_TYPE_UINT16,
	VCE_TYPE_UINT32,
	VCE_TYPE_UINT64,
	VCE_TYPE_FLOAT,
	VCE_TYPE_BOOL,
	VCE_TYPE_BOOL8,
	VCE_TYPE_BOOL16,
	VCE_TYPE_BOOL32,
	VCE_TYPE_FUNCTION,
};

struct CVarConsoleEntry
{
	char *text;
	int8 *pInt8Value;
	int16 *pInt16Value;
	int32 *pInt32Value;
	int64 *pInt64Value;
	uint8 *pUint8Value;
	uint16 *pUint16Value;
	uint32 *pUint32Value;
	uint64 *pUint64Value;
	float *pFloatValue;
	bool *pBoolValue;
	void (*pCallback)(void);
	int8 I8_step, I8_max, I8_min;
	int16 I16_step, I16_max, I16_min;
	int32 I32_step, I32_max, I32_min;
	int64 I64_step, I64_max, I64_min;
	float F_step, F_max, F_min;
	bool8 bAllowExceedBounds;
	uint8 VarType;
};


class CVarConsole
{
	int32 m_nCountEntries;
	bool8 m_bIsOpen;
	int32 m_nCurEntry;
	int32 m_nFirstEntryOnPage;
	int32 m_nCurPage;
	int32 m_nNumPages;
	CVarConsoleEntry m_aEntries[91];
public:
#ifdef FIX_BUGS
	CVarConsole() { Initialise(); }
#endif
	void Initialise();
	void Add(char *text, int8 *pVal, uint8 step, int8 min, int8 max, bool8 isVar);
	void Add(char *text, int16 *pVal, uint16 step, int16 min, int16 max, bool8 isVar);
	void Add(char *text, int32 *pVal, uint32 step, int32 min, int32 max, bool8 isVar);
	void Add(char *text, int64 *pVal, uint64 step, int64 min, int64 max, bool8 isVar);
	void Add(char *text, uint8 *pVal, uint8 step, int8 min, int8 max, bool8 isVar);
	void Add(char *text, uint16 *pVal, uint16 step, int16 min, int16 max, bool8 isVar);
	void Add(char *text, uint32 *pVal, uint32 step, int32 min, int32 max, bool8 isVar);
	void Add(char *text, uint64 *pVal, uint64 step, int64 min, int64 max, bool8 isVar);
	void Add(char *text, float *pVal, float step, float min, float max, bool8 isVar);
	void Add(char *text, bool *pVal, bool8 isVar);
	void Add(char *text, bool8 *pVal, bool8 isVar);
	void Add(char *text, bool16 *pVal, bool8 isVar);
	void Add(char *text, bool32 *pVal, bool8 isVar);
	void Add(char *text, void (*pVar)(void));

	void Remove(char *text);

	void SortPages();
	void Display();

	void ModifyLeft();
	void ModifyRight();

	void Enter();
	void Exit();

	void Input();
	void Process();

	bool8 Open();
	void Check();
};

extern CVarConsole VarConsole;