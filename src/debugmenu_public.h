
extern "C" {

typedef void (*TriggerFunc)(void);

struct DebugMenuEntry;

typedef DebugMenuEntry *(*DebugMenuAddInt8_TYPE)(const char *path, const char *name, int8_t *ptr, TriggerFunc triggerFunc, int8_t step, int8_t lowerBound, int8_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddInt16_TYPE)(const char *path, const char *name, int16_t *ptr, TriggerFunc triggerFunc, int16_t step, int16_t lowerBound, int16_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddInt32_TYPE)(const char *path, const char *name, int32_t *ptr, TriggerFunc triggerFunc, int32_t step, int32_t lowerBound, int32_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddInt64_TYPE)(const char *path, const char *name, int64_t *ptr, TriggerFunc triggerFunc, int64_t step, int64_t lowerBound, int64_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddUInt8_TYPE)(const char *path, const char *name, uint8_t *ptr, TriggerFunc triggerFunc, uint8_t step, uint8_t lowerBound, uint8_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddUInt16_TYPE)(const char *path, const char *name, uint16_t *ptr, TriggerFunc triggerFunc, uint16_t step, uint16_t lowerBound, uint16_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddUInt32_TYPE)(const char *path, const char *name, uint32_t *ptr, TriggerFunc triggerFunc, uint32_t step, uint32_t lowerBound, uint32_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddUInt64_TYPE)(const char *path, const char *name, uint64_t *ptr, TriggerFunc triggerFunc, uint64_t step, uint64_t lowerBound, uint64_t upperBound, const char **strings);
typedef DebugMenuEntry *(*DebugMenuAddFloat32_TYPE)(const char *path, const char *name, float *ptr, TriggerFunc triggerFunc, float step, float lowerBound, float upperBound);
typedef DebugMenuEntry *(*DebugMenuAddFloat64_TYPE)(const char *path, const char *name, double *ptr, TriggerFunc triggerFunc, double step, double lowerBound, double upperBound);
typedef DebugMenuEntry *(*DebugMenuAddCmd_TYPE)(const char *path, const char *name, TriggerFunc triggerFunc);
typedef void (*DebugMenuEntrySetWrap_TYPE)(DebugMenuEntry *e, bool wrap);
typedef void (*DebugMenuEntrySetStrings_TYPE)(DebugMenuEntry *e, const char **strings);
typedef void (*DebugMenuEntrySetAddress_TYPE)(DebugMenuEntry *e, void *addr);

struct DebugMenuAPI
{
	bool isLoaded;
	HMODULE module;
	DebugMenuAddInt8_TYPE addint8;
	DebugMenuAddInt16_TYPE addint16;
	DebugMenuAddInt32_TYPE addint32;
	DebugMenuAddInt64_TYPE addint64;
	DebugMenuAddUInt8_TYPE adduint8;
	DebugMenuAddUInt16_TYPE adduint16;
	DebugMenuAddUInt32_TYPE adduint32;
	DebugMenuAddUInt64_TYPE adduint64;
	DebugMenuAddFloat32_TYPE addfloat32;
	DebugMenuAddFloat64_TYPE addfloat64;
	DebugMenuAddCmd_TYPE addcmd;
	DebugMenuEntrySetWrap_TYPE setwrap;
	DebugMenuEntrySetStrings_TYPE setstrings;
	DebugMenuEntrySetAddress_TYPE setaddress;
};
extern DebugMenuAPI gDebugMenuAPI;

inline DebugMenuEntry *DebugMenuAddInt8(const char *path, const char *name, int8_t *ptr, TriggerFunc triggerFunc, int8_t step, int8_t lowerBound, int8_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint8(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddInt16(const char *path, const char *name, int16_t *ptr, TriggerFunc triggerFunc, int16_t step, int16_t lowerBound, int16_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint16(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddInt32(const char *path, const char *name, int32_t *ptr, TriggerFunc triggerFunc, int32_t step, int32_t lowerBound, int32_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint32(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddInt64(const char *path, const char *name, int64_t *ptr, TriggerFunc triggerFunc, int64_t step, int64_t lowerBound, int64_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint64(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddUInt8(const char *path, const char *name, uint8_t *ptr, TriggerFunc triggerFunc, uint8_t step, uint8_t lowerBound, uint8_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint8(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddUInt16(const char *path, const char *name, uint16_t *ptr, TriggerFunc triggerFunc, uint16_t step, uint16_t lowerBound, uint16_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint16(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddUInt32(const char *path, const char *name, uint32_t *ptr, TriggerFunc triggerFunc, uint32_t step, uint32_t lowerBound, uint32_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint32(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddUInt64(const char *path, const char *name, uint64_t *ptr, TriggerFunc triggerFunc, uint64_t step, uint64_t lowerBound, uint64_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint64(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddFloat32(const char *path, const char *name, float *ptr, TriggerFunc triggerFunc, float step, float lowerBound, float upperBound)
{ return gDebugMenuAPI.addfloat32(path, name, ptr, triggerFunc, step, lowerBound, upperBound); }
inline DebugMenuEntry *DebugMenuAddFloat64(const char *path, const char *name, double *ptr, TriggerFunc triggerFunc, double step, double lowerBound, double upperBound)
{ return gDebugMenuAPI.addfloat64(path, name, ptr, triggerFunc, step, lowerBound, upperBound); }
inline DebugMenuEntry *DebugMenuAddCmd(const char *path, const char *name, TriggerFunc triggerFunc)
{ return gDebugMenuAPI.addcmd(path, name, triggerFunc); }
inline void DebugMenuEntrySetWrap(DebugMenuEntry *e, bool wrap)
{ gDebugMenuAPI.setwrap(e, wrap); }
inline void DebugMenuEntrySetStrings(DebugMenuEntry *e, const char **strings)
{ gDebugMenuAPI.setstrings(e, strings); }
inline void DebugMenuEntrySetAddress(DebugMenuEntry *e, void *addr)
{ gDebugMenuAPI.setaddress(e, addr); }

inline bool DebugMenuLoad(void)
{
	if(gDebugMenuAPI.isLoaded)
		return true;
	HMODULE mod = LoadLibraryA("debugmenu");
	if(mod == 0){
		char modulePath[MAX_PATH];
		HMODULE dllModule;
		GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)&gDebugMenuAPI, &dllModule);
		GetModuleFileNameA(dllModule, modulePath, MAX_PATH);
		char *p = strchr(modulePath, '\\');
		if(p) p[1] = '\0';
		strcat(modulePath, "debugmenu");
		mod = LoadLibraryA(modulePath);
	}
	if(mod == 0)
		return false;
	gDebugMenuAPI.addint8 = (DebugMenuAddInt8_TYPE)GetProcAddress(mod, "DebugMenuAddInt8");
	gDebugMenuAPI.addint16 = (DebugMenuAddInt16_TYPE)GetProcAddress(mod, "DebugMenuAddInt16");
	gDebugMenuAPI.addint32 = (DebugMenuAddInt32_TYPE)GetProcAddress(mod, "DebugMenuAddInt32");
	gDebugMenuAPI.addint64 = (DebugMenuAddInt64_TYPE)GetProcAddress(mod, "DebugMenuAddInt64");
	gDebugMenuAPI.adduint8 = (DebugMenuAddUInt8_TYPE)GetProcAddress(mod, "DebugMenuAddUInt8");
	gDebugMenuAPI.adduint16 = (DebugMenuAddUInt16_TYPE)GetProcAddress(mod, "DebugMenuAddUInt16");
	gDebugMenuAPI.adduint32 = (DebugMenuAddUInt32_TYPE)GetProcAddress(mod, "DebugMenuAddUInt32");
	gDebugMenuAPI.adduint64 = (DebugMenuAddUInt64_TYPE)GetProcAddress(mod, "DebugMenuAddUInt64");
	gDebugMenuAPI.addfloat32 = (DebugMenuAddFloat32_TYPE)GetProcAddress(mod, "DebugMenuAddFloat32");
	gDebugMenuAPI.addfloat64 = (DebugMenuAddFloat64_TYPE)GetProcAddress(mod, "DebugMenuAddFloat64");
	gDebugMenuAPI.addcmd = (DebugMenuAddCmd_TYPE)GetProcAddress(mod, "DebugMenuAddCmd");
	gDebugMenuAPI.setwrap = (DebugMenuEntrySetWrap_TYPE)GetProcAddress(mod, "DebugMenuEntrySetWrap");
	gDebugMenuAPI.setstrings = (DebugMenuEntrySetStrings_TYPE)GetProcAddress(mod, "DebugMenuEntrySetStrings");
	gDebugMenuAPI.setaddress = (DebugMenuEntrySetAddress_TYPE)GetProcAddress(mod, "DebugMenuEntrySetAddress");
	gDebugMenuAPI.isLoaded = true;
	gDebugMenuAPI.module = mod;
	return true;
}

}

// Also overload them for simplicity

inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, int8_t *ptr, TriggerFunc triggerFunc, int8_t step, int8_t lowerBound, int8_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint8(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, int16_t *ptr, TriggerFunc triggerFunc, int16_t step, int16_t lowerBound, int16_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint16(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, int32_t *ptr, TriggerFunc triggerFunc, int32_t step, int32_t lowerBound, int32_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint32(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, int64_t *ptr, TriggerFunc triggerFunc, int64_t step, int64_t lowerBound, int64_t upperBound, const char **strings)
{ return gDebugMenuAPI.addint64(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, uint8_t *ptr, TriggerFunc triggerFunc, uint8_t step, uint8_t lowerBound, uint8_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint8(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, uint16_t *ptr, TriggerFunc triggerFunc, uint16_t step, uint16_t lowerBound, uint16_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint16(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, uint32_t *ptr, TriggerFunc triggerFunc, uint32_t step, uint32_t lowerBound, uint32_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint32(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, uint64_t *ptr, TriggerFunc triggerFunc, uint64_t step, uint64_t lowerBound, uint64_t upperBound, const char **strings)
{ return gDebugMenuAPI.adduint64(path, name, ptr, triggerFunc, step, lowerBound, upperBound, strings); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, float *ptr, TriggerFunc triggerFunc, float step, float lowerBound, float upperBound)
{ return gDebugMenuAPI.addfloat32(path, name, ptr, triggerFunc, step, lowerBound, upperBound); }
inline DebugMenuEntry *DebugMenuAddVar(const char *path, const char *name, double *ptr, TriggerFunc triggerFunc, double step, double lowerBound, double upperBound)
{ return gDebugMenuAPI.addfloat64(path, name, ptr, triggerFunc, step, lowerBound, upperBound); }

inline DebugMenuEntry *DebugMenuAddVarBool32(const char *path, const char *name, int32_t *ptr, TriggerFunc triggerFunc)
{
	static const char *boolstr[] = { "Off", "On" };
	DebugMenuEntry *e = DebugMenuAddVar(path, name, ptr, triggerFunc, 1, 0, 1, boolstr);
	DebugMenuEntrySetWrap(e, true);
	return e;
}
inline DebugMenuEntry *DebugMenuAddVarBool16(const char *path, const char *name, int16_t *ptr, TriggerFunc triggerFunc)
{
	static const char *boolstr[] = { "Off", "On" };
	DebugMenuEntry *e = DebugMenuAddVar(path, name, ptr, triggerFunc, 1, 0, 1, boolstr);
	DebugMenuEntrySetWrap(e, true);
	return e;
}
inline DebugMenuEntry *DebugMenuAddVarBool8(const char *path, const char *name, int8_t *ptr, TriggerFunc triggerFunc)
{
	static const char *boolstr[] = { "Off", "On" };
	DebugMenuEntry *e = DebugMenuAddVar(path, name, ptr, triggerFunc, 1, 0, 1, boolstr);
	DebugMenuEntrySetWrap(e, true);
	return e;
}
