#define _WIN32_WINDOWS 0x0410
#define WINVER 0x0500
#define DIRECTINPUT_VERSION 0x0800
#define WM_GRAPHNOTIFY  WM_USER+13

#include <windows.h>
#include <mmsystem.h>
#include <shellapi.h>

#include <windowsx.h>
#include <basetsd.h>

#include <regstr.h>
#include <shlobj.h>

#include <dbt.h>

#pragma warning( push )
#pragma warning( disable : 4005)
#include <ddraw.h>
#include <dinput.h>
#include <DShow.h>
//#include <dmusici.h>
#pragma warning( pop ) 

#pragma comment( lib, "Winmm.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "strmiids.lib" )

#if (defined(_MSC_VER))
#include <tchar.h>
#endif /* (defined(_MSC_VER)) */
#include <stdio.h>
#include "rwcore.h"
#include "resource.h"
#include "skeleton.h"
#include "platform.h"
#include "win.h"

#define MAX_SUBSYSTEMS      (16)


static RwBool       ForegroundApp = TRUE;
static RwBool       RwInitialised = FALSE;
static RwSubSystemInfo GsubSysInfo[MAX_SUBSYSTEMS];
static RwInt32      GnumSubSystems = 0;
static RwInt32      GcurSel = 0, GcurSelVM = 0;

static RwBool startupDeactivate;
static RwBool useDefault;
static RwBool defaultFullscreenRes = TRUE;

/* Class name for the MS Window's window class. */

static const RwChar *AppClassName = RWSTRING("Grand theft auto 3");


/* platform specfic global data */

typedef struct
{
	HWND        window;
	HINSTANCE   instance;
	RwBool      fullScreen;
	RwV2d       lastMousePos;
	
	DWORD field_14;

	LPDIRECTINPUT8       diInterface;
	LPDIRECTINPUTDEVICE8 diMouse;
	LPDIRECTINPUTDEVICE8 diDevice1;
	LPDIRECTINPUTDEVICE8 diDevice2;
}
psGlobalType;

static psGlobalType PsGlobal;

#define PSGLOBAL(var) (((psGlobalType *)(RsGlobal.ps))->var)

#undef MAKEPOINTS
#define MAKEPOINTS(l)       (*((POINTS /*FAR*/ *)&(l)))

#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }
#define JIF(x) if (FAILED(hr=(x))) \
	{debug(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n"), hr); return hr;}
	
 

#include "common.h"
#include "patcher.h"
#include "FileMgr.h"
#include "Text.h"
#include "Pad.h"
#include "Timer.h"
#include "DMAudio.h"
#include "ControllerConfig.h"
#include "Frontend.h"
#include "Game.h"
#include "PCSave.h"
#include "Sprite2D.h"

// DirectShow interfaces
IGraphBuilder *pGB = NULL;
IMediaControl *pMC = NULL;
IMediaEventEx *pME = NULL;
IVideoWindow  *pVW = NULL;
IMediaSeeking *pMS = NULL;

/**/


DWORD dwDXVersion;
DWORD _dwMemTotalPhys;
DWORD &_dwMemAvailPhys = *(DWORD*)0x70F29C;
DWORD _dwMemTotalVirtual;
DWORD _dwMemAvailVirtual;
DWORD &_dwMemTotalVideo = *(DWORD*)0x70F2A8;
DWORD _dwMemAvailVideo;
DWORD &_dwOperatingSystemVersion = *(DWORD*)0x70F290;

RwUInt32 &gGameState = *(RwUInt32*)0x8F5838;

//
WRAPPER RwUInt32 GetBestRefreshRate(RwUInt32 width, RwUInt32 height, RwUInt32 depth) { EAXJMP(0x581CB0); }
WRAPPER HRESULT _GetVideoMemInfo(DWORD *total, DWORD *avaible) { EAXJMP(0x580F30); }

WRAPPER BOOL _InputTranslateKey(RsKeyCodes *rs, DWORD flag, UINT key) { EAXJMP(0x583A20); }
WRAPPER void _InputTranslateShiftKeyUpDown(RsKeyCodes *rs) { EAXJMP(0x583DC0); }
WRAPPER HRESULT _InputInitialise() { EAXJMP(0x5830D0); }
WRAPPER void _InputShutdown() { EAXJMP(0x583910); }
WRAPPER HRESULT _InputInitialiseMouse() { EAXJMP(0x583110); }
WRAPPER void _InputInitialiseJoys() { EAXJMP(0x583580); }
WRAPPER void LoadingScreen(char const *msg1, char const *msg2, char const *screen) { EAXJMP(0x48D770); }
WRAPPER Bool InitialiseGame(void) { EAXJMP(0x48E7E0); }
WRAPPER const Char *GetLevelSplashScreen(Int32 number) { EAXJMP(0x48D750); }
WRAPPER CSprite2d *LoadSplash(const char *name) { EAXJMP(0x48D550); }
//

void InitialiseLanguage();
RwBool _psSetVideoMode(RwInt32 subSystem, RwInt32 videoMode);
HRESULT CenterVideo(void);
void CloseClip(void);

/**/

_TODO("")
//CJoySticks::CJoySticks((void))	00580B30
//CJoySticks::ClearJoyInfo((int))	00580B50

/*
 *****************************************************************************
 */
void _psCreateFolder(LPCSTR path)
{
	HANDLE hfle = CreateFile(path, GENERIC_READ, 
									FILE_SHARE_READ,
									NULL,
									OPEN_EXISTING,
									FILE_FLAG_BACKUP_SEMANTICS | FILE_ATTRIBUTE_NORMAL,
									NULL);

	if ( hfle == INVALID_HANDLE_VALUE )
		CreateDirectory(path, NULL);
	else
		CloseHandle(hfle);
}

/*
 *****************************************************************************
 */
const char *_psGetUserFilesFolder()
{
	HKEY hKey = NULL;

	static CHAR szUserFiles[256];

	if ( RegOpenKeyEx(HKEY_CURRENT_USER,
						REGSTR_PATH_SPECIAL_FOLDERS,
						REG_OPTION_RESERVED,
						KEY_READ,
						&hKey) == ERROR_SUCCESS )
	{
		DWORD KeyType;
		DWORD KeycbData = sizeof(szUserFiles);
		if ( RegQueryValueEx(hKey,
							"Personal",
							NULL,
							&KeyType,
							(LPBYTE)szUserFiles,
							&KeycbData) == ERROR_SUCCESS )
		{
			RegCloseKey(hKey);
			strcat(szUserFiles, "\\GTA3 User Files");
			_psCreateFolder(szUserFiles);
			return szUserFiles;
		}	

		RegCloseKey(hKey);		
	}
	
	strcpy(szUserFiles, "data");
	return szUserFiles;
}

/*
 *****************************************************************************
 */
RwBool
psCameraBeginUpdate(RwCamera *camera)
{
	if ( !RwCameraBeginUpdate(Scene.camera) )
	{
		ForegroundApp = FALSE;
		RsEventHandler(rsACTIVATE, (void *)FALSE);
		return FALSE;
	}
	
	return TRUE;
}

/*
 *****************************************************************************
 */
void
psCameraShowRaster(RwCamera *camera)
{
	if (CMenuManager::m_PrefsVsync)
		RwCameraShowRaster(camera, PSGLOBAL(window), rwRASTERFLIPWAITVSYNC);
	else
		RwCameraShowRaster(camera, PSGLOBAL(window), rwRASTERFLIPDONTWAIT);

	return;
}


/*
 *****************************************************************************
 */
RwUInt32
psTimer(void)
{
	RwUInt32 time;

	TIMECAPS TimeCaps;
	
	timeGetDevCaps(&TimeCaps, sizeof(TIMECAPS));
	
	timeBeginPeriod(TimeCaps.wPeriodMin);
	
	time = (RwUInt32) timeGetTime();

	timeEndPeriod(TimeCaps.wPeriodMin);
	
	return time;
}

/*
 *****************************************************************************
 */
void
psMouseSetPos(RwV2d *pos)
{
	POINT point;

	point.x = (RwInt32) pos->x;
	point.y = (RwInt32) pos->y;

	ClientToScreen(PSGLOBAL(window), &point);

	SetCursorPos(point.x, point.y);
	
	PSGLOBAL(lastMousePos.x) = (RwInt32)pos->x;

	PSGLOBAL(lastMousePos.y) = (RwInt32)pos->y;

	return;
}

/*
 *****************************************************************************
 */
RwMemoryFunctions*
psGetMemoryFunctions(void)
{
	return 0;
}

/*
 *****************************************************************************
 */
RwBool
psInstallFileSystem(void)
{
	return (TRUE);
}


/*
 *****************************************************************************
 */
RwBool
psNativeTextureSupport(void)
{
	return RwD3D8DeviceSupportsDXTTexture();
}

/*
 *****************************************************************************
 */
static BOOL
InitApplication(HANDLE instance)
{
	/*
	 * Perform any necessary MS Windows application initialization. Basically,
	 * this means registering the window class for this application.
	 */

	WNDCLASS windowClass;

	windowClass.style = CS_BYTEALIGNWINDOW;
	windowClass.lpfnWndProc = (WNDPROC) MainWndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = (HINSTANCE)instance;
	windowClass.hIcon = NULL;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = AppClassName;

	return RegisterClass(&windowClass);
}


/*
 *****************************************************************************
 */
static HWND
InitInstance(HANDLE instance)
{
	/*
	 * Perform any necessary initialization for this instance of the 
	 * application.
	 *
	 * Create the MS Window's window instance for this application. The
	 * initial window size is given by the defined camera size. The window 
	 * is not given a title as we set it during Init3D() with information 
	 * about the version of RenderWare being used.
	 */

	RECT rect;

	rect.left = rect.top = 0;
	rect.right = RsGlobal.maximumWidth;
	rect.bottom = RsGlobal.maximumHeight;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	return CreateWindow(AppClassName, RsGlobal.appName,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT,
						rect.right - rect.left, rect.bottom - rect.top,
						(HWND)NULL, (HMENU)NULL, (HINSTANCE)instance, NULL);
}

_TODO("")
//_GetVideoMemInfo	0x580F30

/*
 *****************************************************************************
 */
typedef HRESULT(WINAPI * DIRECTDRAWCREATEEX)( GUID*, VOID**, REFIID, IUnknown* );


//-----------------------------------------------------------------------------
// Name: GetDXVersion()
// Desc: This function returns the DirectX version number as follows:
//          0x0000 = No DirectX installed
//          0x0700 = At least DirectX 7 installed.
//          0x0800 = At least DirectX 8 installed.
// 
//       Please note that this code is intended as a general guideline. Your
//       app will probably be able to simply query for functionality (via
//       QueryInterface) for one or two components.
//
//       Please also note:
//          "if( dwDXVersion != 0x500 ) return FALSE;" is VERY BAD. 
//          "if( dwDXVersion <  0x500 ) return FALSE;" is MUCH BETTER.
//       to ensure your app will run on future releases of DirectX.
//-----------------------------------------------------------------------------
DWORD GetDXVersion()
{
	DIRECTDRAWCREATEEX   DirectDrawCreateEx = NULL;
	HINSTANCE            hDDrawDLL          = NULL;
	HINSTANCE            hD3D8DLL           = NULL;
	HINSTANCE            hDPNHPASTDLL       = NULL;
	DWORD                dwDXVersion        = 0;
	//HRESULT              hr;

	// First see if DDRAW.DLL even exists.
	hDDrawDLL = LoadLibrary( "DDRAW.DLL" );
	if( hDDrawDLL == NULL )
	{
		dwDXVersion = 0;
		OutputDebugString( "Couldn't LoadLibrary DDraw\r\n" );
		return dwDXVersion;
	}


	//-------------------------------------------------------------------------
	// DirectX 7.0 Checks
	//-------------------------------------------------------------------------

	// Check for DirectX 7 by creating a DDraw7 object
	LPDIRECTDRAW7 pDD7;
	DirectDrawCreateEx = (DIRECTDRAWCREATEEX)GetProcAddress( hDDrawDLL,
													   "DirectDrawCreateEx" );
	if( NULL == DirectDrawCreateEx )
	{
		FreeLibrary( hDDrawDLL );
		OutputDebugString( "Couldn't GetProcAddress DirectDrawCreateEx\r\n" );
		return dwDXVersion;
	}

	if( FAILED( DirectDrawCreateEx( NULL, (VOID**)&pDD7, IID_IDirectDraw7,
									NULL ) ) )
	{
		FreeLibrary( hDDrawDLL );
		OutputDebugString( "Couldn't DirectDrawCreateEx\r\n" );
		return dwDXVersion;
	}

	// DDraw7 was created successfully. We must be at least DX7.0
	dwDXVersion = 0x700;
	pDD7->Release();


	//-------------------------------------------------------------------------
	// DirectX 8.0 Checks
	//-------------------------------------------------------------------------

	// Simply see if D3D8.dll exists.
	hD3D8DLL = LoadLibrary( "D3D8.DLL" );
	if( hD3D8DLL == NULL )
	{
	    FreeLibrary( hDDrawDLL );
		OutputDebugString( "Couldn't LoadLibrary D3D8.DLL\r\n" );
		return dwDXVersion;
	}

	// D3D8.dll exists. We must be at least DX8.0
	dwDXVersion = 0x800;


	//-------------------------------------------------------------------------
	// DirectX 8.1 Checks
	//-------------------------------------------------------------------------

	// Simply see if dpnhpast.dll exists.
	hDPNHPASTDLL = LoadLibrary( "dpnhpast.dll" );
	if( hDPNHPASTDLL == NULL )
	{
	    FreeLibrary( hDPNHPASTDLL );
		OutputDebugString( "Couldn't LoadLibrary dpnhpast.dll\r\n" );
		return dwDXVersion;
	}

	// dpnhpast.dll exists. We must be at least DX8.1
	dwDXVersion = 0x801;


	//-------------------------------------------------------------------------
	// End of checking for versions of DirectX 
	//-------------------------------------------------------------------------

	// Close open libraries and return
	FreeLibrary( hDDrawDLL );
	FreeLibrary( hD3D8DLL );
	
	return dwDXVersion;
}

/*
 *****************************************************************************
 */
static char cpuvendor[16] = "UnknownVendr";
__declspec(naked)  const char * _psGetCpuVendr()
{
	__asm
	{
		push    ebx
		xor     eax, eax
		cpuid
		mov     dword ptr [cpuvendor+0], ebx
		mov     dword ptr [cpuvendor+4], edx
		mov     dword ptr [cpuvendor+8], ecx
		mov     eax, offset cpuvendor
		pop     ebx
		retn
	}
}

/*
 *****************************************************************************
 */
__declspec(naked) RwUInt32 _psGetCpuFeatures()
{
	__asm
	{
		mov     eax, 1
		cpuid
		mov     eax, edx
		retn
	}
}

/*
 *****************************************************************************
 */
__declspec(naked) RwUInt32 _psGetCpuFeaturesEx()
{
	__asm
	{
		mov     eax, 80000000h
		cpuid

		cmp     eax, 80000000h
		jbe     short _NOEX

		mov     eax, 80000001h
		cpuid

		mov     eax, edx
		jmp     short _RETEX

_NOEX:
		xor     eax, eax
		mov     eax, eax
		
_RETEX:
		retn   
	}
}

void _psPrintCpuInfo()
{
	RwUInt32 features   = _psGetCpuFeatures();
	RwUInt32 FeaturesEx = _psGetCpuFeaturesEx();

	debug("Running on a %s", _psGetCpuVendr());

	if ( features & 0x800000 )
		debug("with MMX");
	if ( features & 0x2000000 )
		debug("with SSE");
	if ( FeaturesEx & 0x80000000 )
		debug("with 3DNow");
}

/*
 *****************************************************************************
 */
#ifdef UNDER_CE
#define CMDSTR  LPWSTR
#else
#define CMDSTR  LPSTR
#endif

/*
 *****************************************************************************
 */
RwBool
psInitialise(void)
{
	PsGlobal.lastMousePos.x = PsGlobal.lastMousePos.y = 0.0;

	PsGlobal.fullScreen = FALSE;

	RsGlobal.ps = &PsGlobal;
	
	PsGlobal.fullScreen = FALSE;
	
	PsGlobal.diInterface = NULL;
	PsGlobal.diMouse     = NULL;
	PsGlobal.diDevice1   = NULL;
	PsGlobal.diDevice2   = NULL;

	CFileMgr::Initialise();
	
	C_PcSave::SetSaveDirectory(_psGetUserFilesFolder());
	
	InitialiseLanguage();
	
	FrontEndMenuManager.LoadSettings();
	
	gGameState = GS_START_UP;
	
	_psPrintCpuInfo();
	
	OSVERSIONINFO verInfo;
	verInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	GetVersionEx(&verInfo);
	
	_dwOperatingSystemVersion = 0;
	
	if ( verInfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
	{
		if ( verInfo.dwMajorVersion == 4 )
		{
			debug("Operating System is WinNT\n");
			_dwOperatingSystemVersion = oS_WINNT;
		}
		else if ( verInfo.dwMajorVersion == 5 )
		{
			debug("Operating System is Win2000\n");
			_dwOperatingSystemVersion = OS_WIN2000;
		}
		else if ( verInfo.dwMajorVersion > 5 )
		{
			debug("Operating System is WinXP or greater\n");
			_dwOperatingSystemVersion = OS_WINXP;
		}
	}
	else if ( verInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
	{
		if ( verInfo.dwMajorVersion > 4 || verInfo.dwMajorVersion == 4 && verInfo.dwMinorVersion == 1 )
		{
			debug("Operating System is Win98\n");
			_dwOperatingSystemVersion = OS_WIN98;
		}
		else
		{
			debug("Operating System is Win95\n");
			_dwOperatingSystemVersion = OS_WIN95;
		}
	}
	
	dwDXVersion = GetDXVersion();
	debug("DirectX version 0x%x\n", dwDXVersion);
	
	if ( _dwOperatingSystemVersion == OS_WIN95 )
	{
		MessageBoxW(NULL,
					(LPCWSTR)TheText.Get("WIN_95"),  // Grand Theft Auto III cannot run on Windows 95
					(LPCWSTR)TheText.Get("WIN_TTL"), // Grand Theft Auto III
					MB_OK);

		return FALSE;
	}
	
	if ( dwDXVersion < 0x801 )
	{
		MessageBoxW(NULL,
					(LPCWSTR)TheText.Get("WIN_DX"),  // Grand Theft Auto III requires at least DirectX version 8.1
					(LPCWSTR)TheText.Get("WIN_TTL"), // Grand Theft Auto III
					MB_OK);

		return FALSE;
	}
	
	MEMORYSTATUS memstats;
	GlobalMemoryStatus(&memstats);
	
	_dwMemTotalPhys    = memstats.dwTotalPhys;
	_dwMemAvailPhys    = memstats.dwAvailPhys;
	_dwMemTotalVirtual = memstats.dwTotalVirtual;
	_dwMemAvailVirtual = memstats.dwAvailVirtual;
	
	_GetVideoMemInfo(&_dwMemTotalVideo, &_dwMemAvailVideo);
	
	debug("Physical memory size %d\n", _dwMemTotalPhys);
	debug("Available physical memory %d\n", _dwMemAvailPhys);
	debug("Video memory size %d\n", _dwMemTotalVideo);
	debug("Available video memory %d\n", _dwMemAvailVideo);
	
	if ( _dwMemAvailVideo < (12 * 1024 * 1024) /*12 MB*/ )
	{
        MessageBoxW(NULL,
					(LPCWSTR)TheText.Get("WIN_VDM"), // Grand Theft Auto III requires at least 12MB of available video memory
					(LPCWSTR)TheText.Get("WIN_TTL"), // Grand Theft Auto III
					MB_OK);

		return FALSE;
	}
	
	TheText.Unload();

	return TRUE;
}


/*
 *****************************************************************************
 */
void
psTerminate(void)
{
	return;
}

/*
 *****************************************************************************
 */
static RwChar **_VMList;

RwInt32 _psGetNumVideModes()
{
	return RwEngineGetNumVideoModes();
}

/*
 *****************************************************************************
 */
RwBool _psFreeVideoModeList()
{
	RwInt32 numModes;
	RwInt32 i;
	
	numModes = _psGetNumVideModes();
	
	if ( _VMList == NULL )
		return TRUE;
	
	for ( i = 0; i < numModes; i++ )
	{
		RwFree(_VMList[i]);
	}
	
	RwFree(_VMList);
	
	_VMList = NULL;
	
	return TRUE;
}
							
/*
 *****************************************************************************
 */							
RwChar **_psGetVideoModeList()
{
	RwInt32 numModes;
	RwInt32 i;
	
	if ( _VMList != NULL )
	{
		return _VMList;
	}
	
	numModes = RwEngineGetNumVideoModes();
	
	_VMList = (RwChar **)RwCalloc(numModes, sizeof(RwChar*));
	
	for ( i = 0; i < numModes; i++  )
	{
		RwVideoMode         vm;
		
		RwEngineGetVideoModeInfo(&vm, i);
		
		if ( vm.flags & rwVIDEOMODEEXCLUSIVE )
		{
			if (   vm.width >= 640
				&& vm.height >= 480
				&& (vm.width == 640
				&& vm.height == 480) 
				|| !(vm.flags & rwVIDEOMODEEXCLUSIVE)
				|| (_dwMemTotalVideo - vm.depth * vm.height * vm.width / 8) > (12 * 1024 * 1024)/*12 MB*/ )
			{
				_VMList[i] = (RwChar*)RwCalloc(100, sizeof(RwChar));
				rwsprintf(_VMList[i],"%lu X %lu X %lu", vm.width, vm.height, vm.depth);
			}
			else
				_VMList[i] = NULL;
		}
		else
			_VMList[i] = NULL;
	}
	
	return _VMList;
}

/*
 *****************************************************************************
 */
void _psSelectScreenVM(RwInt32 videoMode)
{
	RwTexDictionarySetCurrent( NULL );
	
	FrontEndMenuManager.UnloadTextures();
	
	if ( !_psSetVideoMode(RwEngineGetCurrentSubSystem(), videoMode) )
	{
		RsGlobal.quit = TRUE;
		
		ShowWindow(PSGLOBAL(window), SW_HIDE);

		MessageBoxW(NULL,
			(LPCWSTR)TheText.Get("WIN_RSZ"), // Failed to select new screen resolution
			(LPCWSTR)TheText.Get("WIN_TTL"), // Grand Theft Auto III
			MB_OK);		
	}
	else
		FrontEndMenuManager.LoadAllTextures();
}

/*
 *****************************************************************************
 */
HRESULT WaitForState(FILTER_STATE State)
{
	HRESULT hr;
	
	// Make sure we have switched to the required state
	LONG   lfs;
	do
	{
		hr = pMC->GetState(10, &lfs);
	} while (State != lfs);
	
	return hr;
}

/*
 *****************************************************************************
 */
HRESULT HandleGraphEvent(void)
{
	LONG evCode, evParam1, evParam2;
	HRESULT hr=S_OK;

	// Process all queued events
	while(SUCCEEDED(pME->GetEvent(&evCode, (LONG_PTR *) &evParam1,
					(LONG_PTR *) &evParam2, 0)))
	{
		// Free memory associated with callback, since we're not using it
		hr = pME->FreeEventParams(evCode, evParam1, evParam2);

		// If this is the end of the clip, reset to beginning
		if(EC_COMPLETE == evCode)
		{
			switch ( gGameState )
			{
				case GS_LOGO_MPEG:
					gGameState = GS_INIT_INTRO_MPEG;
					break;
				case GS_INTRO_MPEG:
					gGameState = GS_INIT_ONCE;
					break;
				default:
					break;
			}

			pME->SetNotifyWindow((OAHWND)NULL, 0, 0);
		}
	}

	return hr;
}

/*
 *****************************************************************************
 */
 
LRESULT CALLBACK
MainWndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINTS points;
	static BOOL noMemory = FALSE;

	
	switch( message )
	{
		case WM_SETCURSOR:
		{
			ShowCursor(FALSE);
			
			SetCursor(NULL);
			
			break; // is this correct ?
		}
		
		case WM_SIZE:
		{
			RwRect r;

			r.x = 0;
			r.y = 0;
			r.w = LOWORD(lParam);
			r.h = HIWORD(lParam);

			if (RwInitialised && r.h > 0 && r.w > 0)
			{
				RsEventHandler(rsCAMERASIZE, &r);

				if (r.w != LOWORD(lParam) && r.h != HIWORD(lParam))
				{
					WINDOWPLACEMENT     wp;

					/* failed to create window of required size */
					noMemory = TRUE;

					/* stop re-sizing */
					ReleaseCapture();

					/* handle maximised window */
					GetWindowPlacement(window, &wp);
					if (wp.showCmd == SW_SHOWMAXIMIZED)
					{
						SendMessage(window, WM_WINDOWPOSCHANGED, 0, 0);
					}
				}
				else
				{
					noMemory = FALSE;
				}

			}

			return 0L;
		}

		case WM_SIZING:
		{
			/* 
			 * Handle event to ensure window contents are displayed during re-size
			 * as this can be disabled by the user, then if there is not enough 
			 * memory things don't work.
			 */
			RECT               *newPos = (LPRECT) lParam;
			RECT                rect;

			/* redraw window */
			if (RwInitialised && gGameState == GS_PLAYING_GAME)
			{
				RsEventHandler(rsIDLE, (void *)TRUE);
			}

			/* Manually resize window */
			rect.left = rect.top = 0;
			rect.bottom = newPos->bottom - newPos->top;
			rect.right = newPos->right - newPos->left;

			SetWindowPos(window, HWND_TOP, rect.left, rect.top,
						 (rect.right - rect.left),
						 (rect.bottom - rect.top), SWP_NOMOVE);

			return 0L;
		}

		case WM_LBUTTONDOWN:
		{
			SetCapture(window);

			return 0L;
		}

		case WM_RBUTTONDOWN:
		{
			SetCapture(window);

			return 0L;
		}
		
		case WM_MBUTTONDOWN:
		{
			SetCapture(window);

			return 0L;
		}

		case WM_MOUSEWHEEL:
		{
			return 0L;
		}

		case WM_MOUSEMOVE:
		{
			points = MAKEPOINTS(lParam);

			FrontEndMenuManager.m_nMouseTempPosX = points.x;
			FrontEndMenuManager.m_nMouseTempPosY = points.y;

			return 0L;
		}

		case WM_LBUTTONUP:
		{
			ReleaseCapture();

			return 0L;
		}

		case WM_RBUTTONUP:
		{
			ReleaseCapture();

			return 0L;
		}
		
		case WM_MBUTTONUP:
		{
			ReleaseCapture();

			return 0L;
		}

		case WM_KEYDOWN:
		{
			RsKeyCodes ks;
			
			if ( _InputTranslateKey(&ks, lParam, wParam) )
				RsKeyboardEventHandler(rsKEYDOWN, &ks);

			if ( wParam == VK_SHIFT )
				_InputTranslateShiftKeyUpDown(&ks);

			return 0L;
		}

		case WM_KEYUP:
		{
			RsKeyCodes ks;

			if ( _InputTranslateKey(&ks, lParam, wParam) )
				RsKeyboardEventHandler(rsKEYUP, &ks);

			if ( wParam == VK_SHIFT )
				_InputTranslateShiftKeyUpDown(&ks);

			return 0L;
		}

		case WM_SYSKEYDOWN:
		{
			RsKeyCodes ks;
			
			if ( _InputTranslateKey(&ks, lParam, wParam) )
				RsKeyboardEventHandler(rsKEYDOWN, &ks);

			if ( wParam == VK_SHIFT )
				_InputTranslateShiftKeyUpDown(&ks);

			return 0L;
		}

		case WM_SYSKEYUP:
		{
			RsKeyCodes ks;

			if ( _InputTranslateKey(&ks, lParam, wParam) )
				RsKeyboardEventHandler(rsKEYUP, &ks);

			if ( wParam == VK_SHIFT )
				_InputTranslateShiftKeyUpDown(&ks);

			return 0L;
		}

		case WM_ACTIVATEAPP:
		{
			switch ( gGameState )
			{
				case GS_LOGO_MPEG:
				case GS_INTRO_MPEG:
				{
					LONG state;
					pMC->GetState(10, &state);
					
					if ( !(BOOL)wParam ) // losing activation
					{
						if ( state == State_Running && pMC != NULL )
						{
							HRESULT hr = pMC->Pause();

							if (hr == S_FALSE)
								OutputDebugString("Failed to pause the MPEG");
							else
								WaitForState(State_Paused);
						}
					}
					else
					{
						CenterVideo();
						
						if ( state != State_Running && pMC != NULL )
						{
							HRESULT hr = pMC->Run();

							if ( hr == S_FALSE )
								OutputDebugString("Failed to run the MPEG");
							else
							{
								WaitForState(State_Running);
								SetFocus(PSGLOBAL(window));
							}
						}
					}
					
					break;
				}
				
				case GS_START_UP:
				{
					if ( !(BOOL)wParam && PSGLOBAL(fullScreen) ) // losing activation
						startupDeactivate = TRUE;
					
					break;
				}
			}
			
			CPad::GetPad(0)->Clear(false);
			CPad::GetPad(1)->Clear(false);
			
			return 0L;
		}
		
		case WM_TIMER:
		{
			return 0L;
		}
		
		case WM_GRAPHNOTIFY:
		{
			if (gGameState == GS_INTRO_MPEG || gGameState == GS_LOGO_MPEG)
				HandleGraphEvent();

			break;
		}

		case WM_CLOSE:
		case WM_DESTROY:
		{
			/*
			 * Quit message handling.
			 */
			ClipCursor(NULL);
			
			_InputShutdown();

			PostQuitMessage(0);

			return 0L;
		}
		
		case WM_DEVICECHANGE:
		{
			if( wParam == DBT_DEVICEREMOVECOMPLETE )
			{
				PDEV_BROADCAST_HDR pDev = (PDEV_BROADCAST_HDR)lParam;
				
				if (pDev->dbch_devicetype != DBT_DEVTYP_VOLUME)
					break;

				if ( DMAudio.IsAudioInitialised() )
				{
					PDEV_BROADCAST_VOLUME pVol = (PDEV_BROADCAST_VOLUME)pDev;
					if ( pVol->dbcv_flags & DBTF_MEDIA )
					{
						Char c = DMAudio.GetCDAudioDriveLetter();
						
						if ( c >= 'A' && pVol->dbcv_unitmask & (1 << (c - 'A')) )
						{
							OutputDebugString("About to check CD drive...");
							
							while ( true )
							{
								FrontEndMenuManager.WaitForUserCD();
								
								if ( !FrontEndMenuManager.m_bQuitGameNoCD )
								{
									if ( DMAudio.CheckForAnAudioFileOnCD() )
									{
										OutputDebugString("GTA3 Audio CD has been inserted");
										break;
									}
								}
								else
								{
									OutputDebugString("Exiting game as Audio CD was not inserted");
									break;
								}
							}
						}
					}
				}
			}
			
			break;
		}

	}

	/*
	 * Let Windows handle all other messages.
	 */
	return DefWindowProc(window, message, wParam, lParam);
}


/*
 *****************************************************************************
 */

RwBool IsForegroundApp()
{
	return !!ForegroundApp;
}

_TODO("")
//GetBestRefreshRate(uint,uint,uint) 00581CB0


/*
 *****************************************************************************
 */
RwBool
psSelectDevice()
{
	RwVideoMode         vm;
	RwInt32             subSysNum;
	RwInt32             AutoRenderer = 0;
	

	RwBool modeFound = FALSE;
	
	if ( !useDefault )
	{
		GnumSubSystems = RwEngineGetNumSubSystems();
		if ( !GnumSubSystems )
		{
			 return FALSE;
		}
		
		/* Just to be sure ... */
		GnumSubSystems = (GnumSubSystems > MAX_SUBSYSTEMS) ? MAX_SUBSYSTEMS : GnumSubSystems;
		
		/* Get the names of all the sub systems */
		for (subSysNum = 0; subSysNum < GnumSubSystems; subSysNum++)
		{
			RwEngineGetSubSystemInfo(&GsubSysInfo[subSysNum], subSysNum);
		}
		
		/* Get the default selection */
		GcurSel = RwEngineGetCurrentSubSystem();
	}
	
	/* Set the driver to use the correct sub system */
	if (!RwEngineSetSubSystem(GcurSel))
	{
		return FALSE;
	}
	
	
	if ( !useDefault )
	{
		if ( _psGetVideoModeList()[FrontEndMenuManager.m_nDisplayVideoMode] && FrontEndMenuManager.m_nDisplayVideoMode )
		{
			FrontEndMenuManager.m_nPrefsVideoMode = FrontEndMenuManager.m_nDisplayVideoMode;
			GcurSelVM = FrontEndMenuManager.m_nDisplayVideoMode;
		}
		else
		{
			while ( !modeFound && GcurSelVM < RwEngineGetNumVideoModes() )
			{
				RwEngineGetVideoModeInfo(&vm, GcurSelVM);
				if ( defaultFullscreenRes   && vm.width  != 640 
											|| vm.height != 480
											|| vm.depth  != 16
											|| !(vm.flags & rwVIDEOMODEEXCLUSIVE) )
					++GcurSelVM;
				else
					modeFound = TRUE;
			}
			
			if ( !modeFound )
			{
				MessageBox(NULL, "Cannot find 640x480 video mode", "GTA3", MB_OK);
				return FALSE;
			}
		}
	}
	
	RwEngineGetVideoModeInfo(&vm, GcurSelVM);
	
	FrontEndMenuManager.m_nCurrOption = 0;
	
	/* Set up the video mode and set the apps window
	* dimensions to match */
	if (!RwEngineSetVideoMode(GcurSelVM))
	{
		return FALSE;
	}
	
	if (vm.flags & rwVIDEOMODEEXCLUSIVE)
	{
		debug("%dx%dx%d", vm.width, vm.height, vm.depth);
		
		RwUInt32 refresh = GetBestRefreshRate(vm.width, vm.height, vm.depth);
		
		if ( refresh != (RwUInt32)-1 )
		{
			debug("refresh %d", refresh);
			RwD3D8EngineSetRefreshRate(refresh);
		}
	}
	
	if (vm.flags & rwVIDEOMODEEXCLUSIVE)
	{
		RsGlobal.maximumWidth = vm.width;
		RsGlobal.maximumHeight = vm.height;
		RsGlobal.width = vm.width;
		RsGlobal.height = vm.height;
		
		PSGLOBAL(fullScreen) = TRUE;
	}
	
	return TRUE;
}

/*
 *****************************************************************************
 */
RwBool _psSetVideoMode(RwInt32 subSystem, RwInt32 videoMode)
{
	RwInitialised = FALSE;
	
	RsEventHandler(rsRWTERMINATE, NULL);
	
	GcurSel = subSystem;
	GcurSelVM = videoMode;
	
	useDefault = TRUE;
	
	if ( RsEventHandler(rsRWINITIALISE, PSGLOBAL(window)) == rsEVENTERROR )
		return FALSE;
	
	RwInitialised = TRUE;
	useDefault = FALSE;
	
	RwRect r;
	
	r.x = 0;
	r.y = 0;
	r.w = RsGlobal.maximumWidth;
	r.h = RsGlobal.maximumHeight;

	RsEventHandler(rsCAMERASIZE, &r);
	
	return TRUE;
}
 
 
/*
 *****************************************************************************
 */
static RwChar **
CommandLineToArgv(RwChar *cmdLine, RwInt32 *argCount)
{
	RwInt32 numArgs = 0;
	RwBool inArg, inString;
	RwInt32 i, len;
	RwChar *res, *str, **aptr;

	len = strlen(cmdLine);

	/* 
	 * Count the number of arguments...
	 */
	inString = FALSE;
	inArg = FALSE;

	for(i=0; i<=len; i++)
	{
		if( cmdLine[i] == '"' )
		{
			inString = !inString;
		}

		if( (cmdLine[i] <= ' ' && !inString) || i == len )
		{
			if( inArg ) 
			{
				inArg = FALSE;
				
				numArgs++;
			}
		} 
		else if( !inArg )
		{
			inArg = TRUE;
		}
	}

	/* 
	 * Allocate memory for result...
	 */
	res = (RwChar *)malloc(sizeof(RwChar *) * numArgs + len + 1);
	str = res + sizeof(RwChar *) * numArgs;
	aptr = (RwChar **)res;

	strcpy(str, cmdLine);

	/*
	 * Walk through cmdLine again this time setting pointer to each arg...
	 */
	inArg = FALSE;
	inString = FALSE;

	for(i=0; i<=len; i++)
	{
		if( cmdLine[i] == '"' )
		{
			inString = !inString;
		}

		if( (cmdLine[i] <= ' ' && !inString) || i == len )
		{
			if( inArg ) 
			{
				if( str[i-1] == '"' )
				{
					str[i-1] = '\0';
				}
				else
				{
					str[i] = '\0';
				}
				
				inArg = FALSE;
			}
		} 
		else if( !inArg && cmdLine[i] != '"' )
		{
			inArg = TRUE; 
			
			*aptr++ = &str[i];
		}
	}

	*argCount = numArgs;

	return (RwChar **)res;
}

/*
 *****************************************************************************
 */
void InitialiseLanguage()
{
#pragma warning( push )
#pragma warning( disable : 4302)
	WORD primUserLCID   = PRIMARYLANGID(GetSystemDefaultLCID());
	WORD primSystemLCID = PRIMARYLANGID(GetUserDefaultLCID());
	WORD primLayout     = PRIMARYLANGID(GetKeyboardLayout(0));
	
	WORD subUserLCID    = SUBLANGID(GetSystemDefaultLCID());
	WORD subSystemLCID  = SUBLANGID(GetUserDefaultLCID());
	WORD subLayout      = SUBLANGID(GetKeyboardLayout(0));
#pragma warning( pop ) 
	
	if (   primUserLCID   == LANG_GERMAN
		|| primSystemLCID == LANG_GERMAN
		|| primLayout     == LANG_GERMAN )
	{
		CGame::nastyGame = false;
		CMenuManager::m_PrefsAllowNastyGame = false;
		CGame::germanGame = true;
	}
	
	if (   primUserLCID   == LANG_FRENCH
		|| primSystemLCID == LANG_FRENCH
		|| primLayout     == LANG_FRENCH )
	{
		CGame::nastyGame = false;
		CMenuManager::m_PrefsAllowNastyGame = false;
		CGame::frenchGame = true;
	}
	
	if (   subUserLCID   == SUBLANG_ENGLISH_AUS
		|| subSystemLCID == SUBLANG_ENGLISH_AUS
		|| subLayout     == SUBLANG_ENGLISH_AUS )
		CGame::noProstitutes = true;
	
	Int32 lang;
	
	switch ( primSystemLCID )
	{
		case LANG_GERMAN:
		{
			lang = LANG_GERMAN;
			break;
		}
		case LANG_FRENCH:
		{
			lang = LANG_FRENCH;
			break;
		}
		case LANG_SPANISH:
		{
			lang = LANG_SPANISH;
			break;
		}
		case LANG_ITALIAN:
		{
			lang = LANG_ITALIAN;
			break;
		}
		default:
		{
			lang = ( subSystemLCID == SUBLANG_ENGLISH_AUS ) ? -99 : LANG_ENGLISH;
			break;
		}
	}
	
	CMenuManager::OS_Language = primUserLCID;

	switch ( lang )
	{
		case LANG_GERMAN:
		{
			CMenuManager::m_PrefsLanguage = LANGUAGE_GERMAN;
			break;
		}
		case LANG_SPANISH:
		{
			CMenuManager::m_PrefsLanguage = LANGUAGE_SPANISH;
			break;
		}
		case LANG_FRENCH:
		{
			CMenuManager::m_PrefsLanguage = LANGUAGE_FRENCH;
			break;
		}
		case LANG_ITALIAN:
		{
			CMenuManager::m_PrefsLanguage = LANGUAGE_ITALIAN;
			break;
		}
		default:
		{
			CMenuManager::m_PrefsLanguage = LANGUAGE_AMERICAN;
			break;
		}
	}

	TheText.Unload();
	TheText.Load();
}

/*
 *****************************************************************************
 */
HRESULT CenterVideo(void)
{
	HRESULT hr = S_OK;
	RECT rect;

	GetClientRect(PSGLOBAL(window), &rect);

	JIF(pVW->SetWindowPosition(rect.left, rect.top, rect.right, rect.bottom));

	JIF(pVW->put_MessageDrain((OAHWND) PSGLOBAL(window)));

	SetFocus(PSGLOBAL(window));

	return hr;
}

/*
 *****************************************************************************
 */
HRESULT PlayMovieInWindow(int cmdShow, LPTSTR szFile)
{
	WCHAR wFileName[256];
	HRESULT hr;

	// Clear open dialog remnants before calling RenderFile()
	UpdateWindow(PSGLOBAL(window));

	// Convert filename to wide character string
	MultiByteToWideChar(CP_ACP, 0, szFile, -1, wFileName, sizeof(wFileName) - 1);

	// Initialize COM
	JIF(CoInitialize(NULL));

	// Get the interface for DirectShow's GraphBuilder
	JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, 
						 IID_IGraphBuilder, (void **)&pGB));

	if(SUCCEEDED(hr))
	{
		// Have the graph builder construct its the appropriate graph automatically
		JIF(pGB->RenderFile(&wFileName[0], NULL));

		// QueryInterface for DirectShow interfaces
		JIF(pGB->QueryInterface(IID_IMediaControl, (void **)&pMC));
		JIF(pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME));
		JIF(pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS));

		// Query for video interfaces, which may not be relevant for audio files
		JIF(pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW));

		JIF(pVW->put_Owner((OAHWND) PSGLOBAL(window)));
		JIF(pVW->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN));

		// Have the graph signal event via window callbacks for performance
		JIF(pME->SetNotifyWindow((OAHWND)PSGLOBAL(window), WM_GRAPHNOTIFY, 0));

		CenterVideo();

		// Run the graph to play the media file
		JIF(pMC->Run());

		SetFocus(PSGLOBAL(window));
	}

	if(FAILED(hr))
		CloseClip();

	return hr;
}

/*
 *****************************************************************************
 */
void CloseInterfaces(void)
{
	// Release and zero DirectShow interfaces
	SAFE_RELEASE(pME);
	SAFE_RELEASE(pMS);
	SAFE_RELEASE(pMC);
	SAFE_RELEASE(pVW);
	SAFE_RELEASE(pGB);
}

/*
 *****************************************************************************
 */
void CloseClip(void)
{
	HRESULT hr;

	// Stop playback
	if(pMC)
		hr = pMC->Stop();

	// Free DirectShow interfaces
	CloseInterfaces();
}

/*
 *****************************************************************************
 */
void HandleExit()
{
	MSG message;
	while ( PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE|PM_NOYIELD) )
	{
		if( message.message == WM_QUIT )
		{
			RsGlobal.quit = TRUE;
		}
		else
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
}
 
/*
 *****************************************************************************
 */
int PASCAL
_WinMain(HINSTANCE instance, 
		HINSTANCE prevInstance  __RWUNUSED__, 
		CMDSTR cmdLine, 
		int cmdShow)
{
	MSG message;
	RwV2d pos;
	RwInt32 argc, i;
	RwChar **argv;

	SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, NULL, SPIF_SENDCHANGE);

	/* 
	 * Initialize the platform independent data.
	 * This will in turn initialize the platform specific data...
	 */
	if( RsEventHandler(rsINITIALISE, NULL) == rsEVENTERROR )
	{
		return FALSE;
	}

	/*
	 * Register the window class...
	 */
	if( !InitApplication(instance) )
	{
		return FALSE;
	}

	/*
	 * Get proper command line params, cmdLine passed to us does not
	 * work properly under all circumstances...
	 */
	cmdLine = GetCommandLine();

	/*
	 * Parse command line into standard (argv, argc) parameters...
	 */
	argv = CommandLineToArgv(cmdLine, &argc);


	/* 
	 * Parse command line parameters (except program name) one at 
	 * a time BEFORE RenderWare initialization...
	 */
	for(i=1; i<argc; i++)
	{
		RsEventHandler(rsPREINITCOMMANDLINE, argv[i]);
	}

	/*
	 * Create the window...
	 */
	PSGLOBAL(window) = InitInstance(instance);
	if( PSGLOBAL(window) == NULL )
	{
		return FALSE;
	}

	PSGLOBAL(instance) = instance;
	
	ControlsManager.MakeControllerActionsBlank();
	ControlsManager.InitDefaultControlConfiguration();
	
	if ( _InputInitialise() == S_OK )
	{
		_InputInitialiseMouse();
		_InputInitialiseJoys();
	}
	
	ControlsManager.InitDefaultControlConfigMouse(MousePointerStateHelper.GetMouseSetUp());
	
	SetWindowLong(PSGLOBAL(window), GWL_STYLE, WS_POPUP);
	SetWindowPos(PSGLOBAL(window), 0, 0, 0, 0, 0,
				SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|
				SWP_FRAMECHANGED);

	/* 
	 * Initialize the 3D (RenderWare) components of the app...
	 */
	if( rsEVENTERROR == RsEventHandler(rsRWINITIALISE, PSGLOBAL(window)) )
	{
		DestroyWindow(PSGLOBAL(window));

		RsEventHandler(rsTERMINATE, NULL);

		return FALSE;
	}

	/* 
	 * Parse command line parameters (except program name) one at 
	 * a time AFTER RenderWare initialization...
	 */
	for(i=1; i<argc; i++)
	{
		RsEventHandler(rsCOMMANDLINE, argv[i]);
	}

	/* 
	 * Force a camera resize event...
	 */
	{
		RwRect r;

		r.x = 0;
		r.y = 0;
		r.w = RsGlobal.maximumWidth;
		r.h = RsGlobal.maximumHeight;

		RsEventHandler(rsCAMERASIZE, &r);
	}
	
	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, FALSE, NULL, SPIF_SENDCHANGE);
	SystemParametersInfo(SPI_SETPOWEROFFACTIVE, FALSE, NULL, SPIF_SENDCHANGE);
	SystemParametersInfo(SPI_SETLOWPOWERACTIVE, FALSE, NULL, SPIF_SENDCHANGE);
	

	STICKYKEYS SavedStickyKeys;
	SavedStickyKeys.cbSize = sizeof(STICKYKEYS);
	
	SystemParametersInfo(SPI_GETSTICKYKEYS, sizeof(STICKYKEYS), &SavedStickyKeys, SPIF_SENDCHANGE);
	
	STICKYKEYS NewStickyKeys;
	NewStickyKeys.cbSize = sizeof(STICKYKEYS);
	NewStickyKeys.dwFlags = SKF_TWOKEYSOFF;
	
	SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &NewStickyKeys, SPIF_SENDCHANGE);
	

	/*
	 * Show the window, and refresh it...
	 */
	ShowWindow(PSGLOBAL(window), cmdShow);
	UpdateWindow(PSGLOBAL(window));
	
	{
		CFileMgr::SetDirMyDocuments();
		
		Int32 gta3set = CFileMgr::OpenFile("gta3.set", "r");
		
		if ( gta3set )
		{
			ControlsManager.LoadSettings(gta3set);
			CFileMgr::CloseFile(gta3set);
		}
		
		CFileMgr::SetDir("");
	}
	
	SetErrorMode(SEM_FAILCRITICALERRORS);
	
	while ( TRUE )
	{
		RwInitialised = TRUE;
		
		/* 
		* Set the initial mouse position...
		*/
		pos.x = RsGlobal.maximumWidth * 0.5f;
		pos.y = RsGlobal.maximumHeight * 0.5f;

		RsMouseSetPos(&pos);
		
		WINDOWPLACEMENT     wp;
		wp.length = sizeof(WINDOWPLACEMENT);

		/*
		* Enter the message processing loop...
		*/

		while( !RsGlobal.quit && !FrontEndMenuManager.m_bStartGameLoading )
		{
			if( PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE|PM_NOYIELD) )
			{
				if( message.message == WM_QUIT )
				{
					break;
				}
				else
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
			else if( ForegroundApp )
			{				
				switch ( gGameState )
				{
					case GS_START_UP:
					{
						gGameState = GS_INIT_LOGO_MPEG;
						break;
					}
					
					case GS_INIT_LOGO_MPEG:
					{
						if ( !startupDeactivate )
							PlayMovieInWindow(cmdShow, "movies\\Logo.mpg");
						gGameState = GS_LOGO_MPEG;
						break;
					}
					
					case GS_LOGO_MPEG:
					{
						CPad::UpdatePads();
						if ( startupDeactivate || ControlsManager.GetJoyButtonJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetLeftMouseJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetEnterJustDown() || CPad::GetPad(0)->GetExtEnterJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetCharJustDown(' ') )
							++gGameState;
						else if ( CPad::GetPad(0)->GetLeftAltJustDown() || CPad::GetPad(0)->GetRightAltJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetTabJustDown() )
							++gGameState;
					}
					
					case GS_INIT_INTRO_MPEG:
					{
						CloseClip();
						
						CoUninitialize();
						
						if ( CMenuManager::OS_Language == LANG_FRENCH || CMenuManager::OS_Language == LANG_GERMAN )
							PlayMovieInWindow(cmdShow, "movies\\GTAtitlesGER.mpg");
						else
							PlayMovieInWindow(cmdShow, "movies\\GTAtitles.mpg");
						
						gGameState = GS_INTRO_MPEG;
						break;
					}
					
					case GS_INTRO_MPEG:
					{
						CPad::UpdatePads();
						if ( startupDeactivate || ControlsManager.GetJoyButtonJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetLeftMouseJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetEnterJustDown() || CPad::GetPad(0)->GetExtEnterJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetCharJustDown(' ') )
							++gGameState;
						else if ( CPad::GetPad(0)->GetLeftAltJustDown() || CPad::GetPad(0)->GetRightAltJustDown() )
							++gGameState;
						else if ( CPad::GetPad(0)->GetTabJustDown() )
							++gGameState;
					}
					
					case GS_INIT_ONCE:
					{
						CloseClip();
						CoUninitialize();
						
						LoadingScreen(NULL, NULL, "loadsc0");
						
						if ( !CGame::InitialiseOnceAfterRW() )
							RsGlobal.quit = TRUE;
						
						gGameState = GS_INIT_FRONTEND;
						break;
					}
					
					case GS_INIT_FRONTEND:
					{
						LoadingScreen(NULL, NULL, "loadsc0");
						
						FrontEndMenuManager.m_bGameNotLoaded = true;
						
						CMenuManager::m_bStartUpFrontEndRequested = true;
						
						if ( defaultFullscreenRes )
						{
							defaultFullscreenRes = 0;
							FrontEndMenuManager.m_nPrefsVideoMode = GcurSelVM;
							FrontEndMenuManager.m_nDisplayVideoMode = GcurSelVM;
						}
						
						gGameState = GS_FRONTEND;
						break;
					}
					
					case GS_FRONTEND:
					{
						GetWindowPlacement(PSGLOBAL(window), &wp);
						
						if ( wp.showCmd != SW_SHOWMINIMIZED )
							RsEventHandler(rsFRONTENDIDLE, NULL);

						if ( !FrontEndMenuManager.m_bMenuActive || FrontEndMenuManager.m_bLoadingSavedGame )
							gGameState = GS_INIT_PLAYING_GAME;

						if ( FrontEndMenuManager.m_bLoadingSavedGame )
						{
							InitialiseGame();
							FrontEndMenuManager.m_bGameNotLoaded = false;
							gGameState = GS_PLAYING_GAME;
						}
						break;
					}
					
					case GS_INIT_PLAYING_GAME:
					{
						InitialiseGame();
						FrontEndMenuManager.m_bGameNotLoaded = false;
						gGameState = GS_PLAYING_GAME;
						break;
					}
					
					case GS_PLAYING_GAME:
					{
						Float ms = (Float)CTimer::GetCurrentTimeInCycles() / (Float)CTimer::GetCyclesPerMillisecond();
						if ( RwInitialised )
						{
							if (!CMenuManager::m_PrefsFrameLimiter || (1000.0f / (Float)RsGlobal.maxFPS) < ms)
								RsEventHandler(rsIDLE, (void *)TRUE);
						}
						break;
					}
				}
			}
			else
			{
				if ( RwCameraBeginUpdate(Scene.camera) )
				{
					RwCameraEndUpdate(Scene.camera);
					ForegroundApp = TRUE;
					RsEventHandler(rsACTIVATE, (void *)TRUE);
				}
				
				WaitMessage();
			}
		}

		
		/* 
		* About to shut down - block resize events again...
		*/
		RwInitialised = FALSE;
		
		FrontEndMenuManager.UnloadTextures();
		if ( !FrontEndMenuManager.m_bStartGameLoading )
			break;
		
		CPad::ResetCheats();
		CPad::StopPadsShaking();
		
		DMAudio.ChangeMusicMode(_TODOCONST(3));
		
		CTimer::Stop();
		
		if ( FrontEndMenuManager.m_bLoadingSavedGame )
		{
			CGame::ShutDownForRestart();
			CGame::InitialiseWhenRestarting();
			DMAudio.ChangeMusicMode(_TODOCONST(1));
			LoadSplash(GetLevelSplashScreen(CGame::currLevel));
			FrontEndMenuManager.m_bLoadingSavedGame = false;
		}
		else
		{
			if ( gGameState == GS_PLAYING_GAME )
				CGame::ShutDown();
			
			CTimer::Stop();
			
			if ( FrontEndMenuManager.m_bFirstTime == true )
				gGameState = GS_INIT_FRONTEND;
			else
				gGameState = GS_INIT_PLAYING_GAME;
		}
		
		FrontEndMenuManager.m_bFirstTime = false;
		FrontEndMenuManager.m_bStartGameLoading = false;
	}
	

	if ( gGameState == GS_PLAYING_GAME )
		CGame::ShutDown();

	DMAudio.Terminate();
	
	_psFreeVideoModeList();


	/*
	 * Tidy up the 3D (RenderWare) components of the application...
	 */
	RsEventHandler(rsRWTERMINATE, NULL);

	/*
	 * Kill the window...
	 */
	DestroyWindow(PSGLOBAL(window));

	/*
	 * Free the platform dependent data...
	 */
	RsEventHandler(rsTERMINATE, NULL);

	/* 
	 * Free the argv strings...
	 */
	free(argv);
	
	ShowCursor(TRUE);
	
	SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &SavedStickyKeys, SPIF_SENDCHANGE);
	SystemParametersInfo(SPI_SETPOWEROFFACTIVE, TRUE, NULL, SPIF_SENDCHANGE);
	SystemParametersInfo(SPI_SETLOWPOWERACTIVE, TRUE, NULL, SPIF_SENDCHANGE);
	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, NULL, SPIF_SENDCHANGE);

	SetErrorMode(0);

	return message.wParam;
}

/*
 *****************************************************************************
 */

_TODO("");
// _InputInitialise	.text	005830D0	00000033	00000000	00000000	R	.	.	.	.	.	.
//_InputInitialiseMouse	.text	00583110	00000073	00000004	00000000	R	.	.	.	.	.	.
//CapturePad(int)	.text	00583190	000003E7	00000128	00000004	R	.	.	.	.	.	.
//_InputInitialiseJoys	.text	00583580	000000EA	00000044	00000000	R	.	.	.	.	.	.
//_InputAddJoyStick	.text	00583670	00000197	00000164	00000008	R	.	.	.	.	.	.
//_InputAddJoys	.text	00583810	0000005B	00000004	00000000	R	.	.	.	.	.	.
//_InputGetMouseState	.text	00583870	00000095	00000008	00000004	R	.	.	.	.	T	.
//_InputShutdown	.text	00583910	00000021	00000004	00000000	R	.	.	.	.	.	.
//_InputEnumDevicesCallback	.text	00583940	000000DB	00000008	00000004	R	.	.	.	.	.	.
//_InputTranslateKey	.text	00583A20	0000039C	00000008	0000000C	R	.	.	.	.	T	.
//_InputTranslateShiftKeyUpDown	.text	00583DC0	00000088	00000004	00000004	R	.	.	.	.	T	.
//_InputTranslateShiftKey	.text	00583E50	00000085	00000008	00000009	R	.	.	.	.	T	.
//_InputIsExtended	.text	00583EE0	00000013	00000000	00000004	R	.	.	.	.	.	.


STARTPATCHES	
	InjectHook(0x580B70, _psCreateFolder, PATCH_JUMP);
	InjectHook(0x580BB0, _psGetUserFilesFolder, PATCH_JUMP);
	InjectHook(0x580C70, psCameraBeginUpdate, PATCH_JUMP);
	InjectHook(0x580CA0, psCameraShowRaster, PATCH_JUMP);
	InjectHook(0x580CE0, psTimer, PATCH_JUMP);
	InjectHook(0x580D20, psMouseSetPos, PATCH_JUMP);
	InjectHook(0x580E10, psGetMemoryFunctions, PATCH_JUMP);
	InjectHook(0x580E20, psInstallFileSystem, PATCH_JUMP);
	InjectHook(0x580E30, psNativeTextureSupport, PATCH_JUMP);
	InjectHook(0x580E40, InitApplication, PATCH_JUMP);
	InjectHook(0x580EB0, InitInstance, PATCH_JUMP);
	InjectHook(0x580FA0, GetDXVersion, PATCH_JUMP);
	InjectHook(0x5810C0, _psGetCpuVendr, PATCH_JUMP);
	InjectHook(0x5810E0, _psGetCpuFeatures, PATCH_JUMP);
	InjectHook(0x5810F0, _psGetCpuFeaturesEx, PATCH_JUMP);
	InjectHook(0x581120, _psPrintCpuInfo, PATCH_JUMP);
	InjectHook(0x581180, psInitialise, PATCH_JUMP);
	InjectHook(0x581460, psTerminate, PATCH_JUMP);
	InjectHook(0x581470, _psGetNumVideModes, PATCH_JUMP);
	InjectHook(0x581480, _psFreeVideoModeList, PATCH_JUMP);
	InjectHook(0x5814F0, _psGetVideoModeList, PATCH_JUMP);
	InjectHook(0x581630, _psSelectScreenVM, PATCH_JUMP);
	InjectHook(0x5816B0, WaitForState, PATCH_JUMP);
	InjectHook(0x5816E0, HandleGraphEvent, PATCH_JUMP);
	InjectHook(0x581790, MainWndProc, PATCH_JUMP);
	InjectHook(0x581C90, IsForegroundApp, PATCH_JUMP);
	InjectHook(0x581D80, psSelectDevice, PATCH_JUMP);
	InjectHook(0x581F90, _psSetVideoMode, PATCH_JUMP);
	InjectHook(0x582030, CommandLineToArgv, PATCH_JUMP);
	InjectHook(0x582160, InitialiseLanguage, PATCH_JUMP);
	InjectHook(0x5822F0, CenterVideo, PATCH_JUMP);
	InjectHook(0x582380, PlayMovieInWindow, PATCH_JUMP);
	InjectHook(0x5825E0, CloseInterfaces, PATCH_JUMP);
	InjectHook(0x582680, CloseClip, PATCH_JUMP);
	InjectHook(0x5826A0, HandleExit, PATCH_JUMP);
	InjectHook(0x582710, _WinMain, PATCH_JUMP);

ENDPATCHES