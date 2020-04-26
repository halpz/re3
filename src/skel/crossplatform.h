#include <time.h>

// This is the common include for platform/renderer specific skeletons(glfw, win etc.) and cross platform things (like Windows directories wrapper, platform specific global arrays etc.) 

// This only has <windef.h> as Win header.
#ifdef _WIN32
#include "win.h"
#endif

#ifdef RW_GL3
typedef struct
{
    GLFWwindow* window;
    RwBool		fullScreen;
    RwV2d		lastMousePos;
    double      mouseWheel; // glfw doesn't cache it
    int8        joy1id;
    int8        joy2id;
}
psGlobalType;

#define PSGLOBAL(var) (((psGlobalType *)(RsGlobal.ps))->var)

void CapturePad(RwInt32 padID);
void joysChangeCB(int jid, int event);
#endif

enum eGameState
{
    GS_START_UP = 0,
    GS_INIT_LOGO_MPEG,
    GS_LOGO_MPEG,
    GS_INIT_INTRO_MPEG,
    GS_INTRO_MPEG,
    GS_INIT_ONCE,
    GS_INIT_FRONTEND,
    GS_FRONTEND,
    GS_INIT_PLAYING_GAME,
    GS_PLAYING_GAME,
#ifndef MASTER
    GS_ANIMVIEWER,
#endif
};
extern RwUInt32 gGameState;

RwBool IsForegroundApp();
void InitialiseLanguage();
RwBool _psSetVideoMode(RwInt32 subSystem, RwInt32 videoMode);

RwChar** _psGetVideoModeList();
RwInt32 _psGetNumVideModes();

void _psSelectScreenVM(RwInt32 videoMode);
void HandleExit();
void _InputTranslateShiftKeyUpDown(RsKeyCodes* rs);

// Mostly wrappers around Windows functions

#ifndef MAX_PATH
    #if !defined _WIN32 || defined __MINGW32__
    #define MAX_PATH PATH_MAX
    #else
    #define MAX_PATH 260
    #endif
#endif

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

void GetLocalTime_CP(SYSTEMTIME* out);
#define GetLocalTime GetLocalTime_CP
#define OutputDebugString(s) re3_debug("[DBG-2]: " s "\n")
#endif

// Only runs on GNU/POSIX/etc.
#if !defined _WIN32 || defined __MINGW32__
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