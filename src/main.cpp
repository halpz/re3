#include <direct.h>
#include <Windows.h>
#include "common.h"
#include "patcher.h"
#include "Renderer.h"
#include "debugmenu_public.h"

void **rwengine = *(void***)0x5A10E1;

RsGlobalType &RsGlobal = *(RsGlobalType*)0x8F4360;

GlobalScene &Scene = *(GlobalScene*)0x726768;

DebugMenuAPI gDebugMenuAPI;

WRAPPER void *gtanew(uint32 sz) { EAXJMP(0x5A0690); }
WRAPPER void gtadelete(void *p) { EAXJMP(0x5A07E0); }

// overload our own new/delete with GTA's functions
void *operator new(size_t sz) { return gtanew(sz); }
void operator delete(void *ptr) noexcept { gtadelete(ptr); }

// Use our own implementation of rand, stolen from PS2

unsigned __int64 myrand_seed = 1;

int
myrand(void)
{
	myrand_seed = 0x5851F42D4C957F2D * myrand_seed + 1;
	return ((myrand_seed >> 32) & 0x7FFFFFFF);
}

void
mysrand(unsigned int seed)
{
	myrand_seed = seed;
}

// platform stuff
char*
GetUserDirectory(void)
{
	static char path[MAX_PATH];
	strcpy(path, "userfiles");
	mkdir(path);
	return path;
}


int (*open_script_orig)(const char *path, const char *mode);
int
open_script(const char *path, const char *mode)
{
	if(GetAsyncKeyState('D') & 0x8000)
		return open_script_orig("main_d.scm", mode);
//	if(GetAsyncKeyState('R') & 0x8000)
		return open_script_orig("main_freeroam.scm", mode);
	return open_script_orig(path, mode);
}

int gDbgSurf;

int (*RsEventHandler_orig)(int a, int b);
int
delayedPatches10(int a, int b)
{
	if(DebugMenuLoad()){
		DebugMenuAddVarBool8("Debug", "Show Ped Road Groups", (int8*)&gbShowPedRoadGroups, nil);
		DebugMenuAddVarBool8("Debug", "Show Car Road Groups", (int8*)&gbShowCarRoadGroups, nil);
		DebugMenuAddVarBool8("Debug", "Show Collision Polys", (int8*)&gbShowCollisionPolys, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Buildings", (int8*)&gbDontRenderBuildings, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Big Buildings", (int8*)&gbDontRenderBigBuildings, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Peds", (int8*)&gbDontRenderPeds, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Objects", (int8*)&gbDontRenderObjects, nil);
		DebugMenuAddVar("Debug", "Dbg Surface", &gDbgSurf, nil, 1, 0, 34, nil);
	}

	return RsEventHandler_orig(a, b);
}

void
patch()
{
	StaticPatcher::Apply();

	Patch<float>(0x46BC61+6, 1.0f);	// car distance
	InjectHook(0x59E460, printf, PATCH_JUMP);

	InterceptCall(&open_script_orig, open_script, 0x438869);

	InterceptCall(&RsEventHandler_orig, delayedPatches10, 0x58275E);
}

BOOL WINAPI
DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if(reason == DLL_PROCESS_ATTACH){

		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		if (*(DWORD*)0x5C1E75 == 0xB85548EC)	// 1.0
			patch();
		else
			return FALSE;
	}

	return TRUE;
}
