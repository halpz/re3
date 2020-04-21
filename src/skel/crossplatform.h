#include <time.h>

#ifndef MAX_PATH
    #if !defined _WIN32 || defined __MINGW32__
    #define MAX_PATH PATH_MAX
    #else
    #define MAX_PATH 260
    #endif
#endif

// Mostly wrappers around Windows functions

// TODO: Remove USEALTERNATIVEWINFUNCS and don't use it anywhere when re3 becomes fully cross-platform, this is for testing
// Codes compatible with Windows and Linux
#if defined USEALTERNATIVEWINFUNCS || !defined _WIN32 || defined __MINGW32__
#define DeleteFile unlink

// Needed for save games
struct SYSTEMTIME {
    uint16 wYear;
    uint16 wMonth;
    uint16 wDayOfWeek;
    uint16 wDay;
    uint16 wHour;
    uint16 wMinute;
    uint16 wSecond;
    uint16 wMilliseconds;
};

#define GetLocalTime GetLocalTime_CP
#else
#include <Windows.h>
#endif

void GetLocalTime_CP(SYSTEMTIME* out);


// Only runs on GNU/POSIX/etc.
#if !defined _WIN32 || defined __MINGW32__
#define OutputDebugString(s) re3_debug("[DBG-2]: " s "\n")

#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <langinfo.h>

typedef DIR* HANDLE;
#define INVALID_HANDLE_VALUE NULL
#define FindClose closedir
#define LOCALE_USER_DEFAULT 0
#define DATE_SHORTDATE 0

struct WIN32_FIND_DATA {
    char extension[32]; // for searching
    char folder[32];	// for searching
    char cFileName[256]; // because tSkinInfo has it 256
    time_t ftLastWriteTime;
};

HANDLE FindFirstFile(char*, WIN32_FIND_DATA*);
bool FindNextFile(HANDLE, WIN32_FIND_DATA*);
void FileTimeToSystemTime(time_t*, SYSTEMTIME*);
void GetDateFormat(int, int, SYSTEMTIME*, int, char*, int);
#endif