#include <direct.h>
#include <csignal>
#include <Windows.h>
#include "common.h"
#include "patcher.h"
#include "Renderer.h"
#include "Credits.h"
#include "Camera.h"
#include "Weather.h"
#include "Clock.h"
#include "World.h"
#include "Vehicle.h"
#include "Streaming.h"
#include "PathFind.h"
#include "Boat.h"
#include "Automobile.h"
#include "debugmenu_public.h"

void **rwengine = *(void***)0x5A10E1;

DebugMenuAPI gDebugMenuAPI;

WRAPPER void *gtanew(uint32 sz) { EAXJMP(0x5A0690); }
WRAPPER void gtadelete(void *p) { EAXJMP(0x5A07E0); }

// overload our own new/delete with GTA's functions
void *operator new(size_t sz) { return gtanew(sz); }
void operator delete(void *ptr) noexcept { gtadelete(ptr); }

#ifdef USE_PS2_RAND
unsigned __int64 myrand_seed = 1;
#else
unsigned long int myrand_seed = 1;
#endif

int
myrand(void)
{
#ifdef USE_PS2_RAND
	// Use our own implementation of rand, stolen from PS2
	myrand_seed = 0x5851F42D4C957F2D * myrand_seed + 1;
	return ((myrand_seed >> 32) & 0x7FFFFFFF);
#else
	// or original codewarrior rand
	myrand_seed = myrand_seed * 1103515245 + 12345;
	return((myrand_seed >> 16) & 0x7FFF);
#endif
}

void
mysrand(unsigned int seed)
{
	myrand_seed = seed;
}

int (*open_script_orig)(const char *path, const char *mode);
int
open_script(const char *path, const char *mode)
{
	static int scriptToLoad = 1;

	if(GetAsyncKeyState('G') & 0x8000)
		scriptToLoad = 0;
	if(GetAsyncKeyState('R') & 0x8000)
		scriptToLoad = 1;
	if(GetAsyncKeyState('D') & 0x8000)
		scriptToLoad = 2;

	switch(scriptToLoad){
	case 0: return open_script_orig(path, mode);
	case 1: return open_script_orig("main_freeroam.scm", mode);
	case 2: return open_script_orig("main_d.scm", mode);
	}
	return open_script_orig(path, mode);
}

int gDbgSurf;

void (*DebugMenuProcess)(void);
void (*DebugMenuRender)(void);
static void stub(void) { }

void
DebugMenuInit(void)
{
	if(DebugMenuLoad()){
		DebugMenuProcess = (void(*)(void))GetProcAddress(gDebugMenuAPI.module, "DebugMenuProcess");
		DebugMenuRender = (void(*)(void))GetProcAddress(gDebugMenuAPI.module, "DebugMenuRender");
	}
	if(DebugMenuProcess == nil || DebugMenuRender == nil){
		DebugMenuProcess = stub;
		DebugMenuRender = stub;
	}

}

void WeaponCheat();
void HealthCheat();
void TankCheat();
void BlowUpCarsCheat();
void ChangePlayerCheat();
void MayhemCheat();
void EverybodyAttacksPlayerCheat();
void WeaponsForAllCheat();
void FastTimeCheat();
void SlowTimeCheat();
void MoneyCheat();
void ArmourCheat();
void WantedLevelUpCheat();
void WantedLevelDownCheat();
void SunnyWeatherCheat();
void CloudyWeatherCheat();
void RainyWeatherCheat();
void FoggyWeatherCheat();
void FastWeatherCheat();
void OnlyRenderWheelsCheat();
void ChittyChittyBangBangCheat();
void StrongGripCheat();
void NastyLimbsCheat();

// needs too much stuff for now
#if 0
void
spawnCar(int id)
{
	CVector playerpos;
	CStreaming::RequestModel(id, 0);
	CStreaming::LoadAllRequestedModels(false);
	if(CStreaming::HasModelLoaded(id)){
		FindPlayerCoors(playerpos);
		int node = ThePaths.FindNodeClosestToCoors(playerpos, 0, 100.0f, false, false);
		if(node < 0)
			return;

		CVehicle *v;
		if(CModelInfo::IsBoatModel(id)){
//			CBoat* boat = (CBoat*)CVehicle__new(0x484);
//			boat = boat->ctor(id, 1);
//			v = (CVehicle*)(boat);
		}else{
//			CAutomobile *au = (CAutomobile*)CVehicle__new(0x5A8);
//			au = au->ctor(id, 1);
//			v = (CVehicle*)au;
		}
/*
		// unlock doors
		FIELD(int, v, 0x224) = 1;
		// set player owned
		FIELD(uint8, v, 0x1F7) |= 4;

		DebugMenuEntrySetAddress(carCol1, &FIELD(uchar, v, 0x19C));
		DebugMenuEntrySetAddress(carCol2, &FIELD(uchar, v, 0x19D));
		//if(id == MODELID_ESPERANTO)
		//	FIELD(uchar, v, 0x19C) = 54;

		v->matrix.matrix.pos.x = ThePaths.nodes[node].x;
		v->matrix.matrix.pos.y = ThePaths.nodes[node].y;
		v->matrix.matrix.pos.z = ThePaths.nodes[node].z + 4.0f;
		float x = v->matrix.matrix.pos.x;
		float y = v->matrix.matrix.pos.y;
		float z = v->matrix.matrix.pos.z;
		v->matrix.SetRotate(0.0f, 0.0f, 3.49f);
		v->matrix.matrix.pos.x += x;
		v->matrix.matrix.pos.y += y;
		v->matrix.matrix.pos.z += z;
		v->bfTypeStatus = v->bfTypeStatus & 7 | 0x20;
		FIELD(int, v, 0x224) = 1;
*/
		CWorld::Add(v);
	}
}
#endif

void
DebugMenuPopulate(void)
{
	if(DebugMenuLoad()){
		static const char *weathers[] = {
			"Sunny", "Cloudy", "Rainy", "Foggy"
		};
		DebugMenuEntry *e;
		e = DebugMenuAddVar("Time & Weather", "Current Hour", &CClock::GetHoursRef(), nil, 1, 0, 23, nil);
		DebugMenuEntrySetWrap(e, true);
		e = DebugMenuAddVar("Time & Weather", "Current Minute", &CClock::GetMinutesRef(),
			[](){ CWeather::InterpolationValue = CClock::GetMinutes()/60.0f; }, 1, 0, 59, nil);
			DebugMenuEntrySetWrap(e, true);
		e = DebugMenuAddVar("Time & Weather", "Old Weather", (int16*)&CWeather::OldWeatherType, nil, 1, 0, 3, weathers);
		DebugMenuEntrySetWrap(e, true);
		e = DebugMenuAddVar("Time & Weather", "New Weather", (int16*)&CWeather::NewWeatherType, nil, 1, 0, 3, weathers);
		DebugMenuEntrySetWrap(e, true);
		DebugMenuAddVar("Time & Weather", "Time scale", (float*)0x8F2C20, nil, 0.1f, 0.0f, 10.0f);

		DebugMenuAddCmd("Cheats", "Weapons", WeaponCheat);
		DebugMenuAddCmd("Cheats", "Money", MoneyCheat);
		DebugMenuAddCmd("Cheats", "Health", HealthCheat);
		DebugMenuAddCmd("Cheats", "Wanted level up", WantedLevelUpCheat);
		DebugMenuAddCmd("Cheats", "Wanted level down", WantedLevelDownCheat);
		DebugMenuAddCmd("Cheats", "Tank", TankCheat);
		DebugMenuAddCmd("Cheats", "Blow up cars", BlowUpCarsCheat);
		DebugMenuAddCmd("Cheats", "Change player", ChangePlayerCheat);
		DebugMenuAddCmd("Cheats", "Mayhem", MayhemCheat);
		DebugMenuAddCmd("Cheats", "Everybody attacks player", EverybodyAttacksPlayerCheat);
		DebugMenuAddCmd("Cheats", "Weapons for all", WeaponsForAllCheat);
		DebugMenuAddCmd("Cheats", "Fast time", FastTimeCheat);
		DebugMenuAddCmd("Cheats", "Slow time", SlowTimeCheat);
		DebugMenuAddCmd("Cheats", "Armour", ArmourCheat);
		DebugMenuAddCmd("Cheats", "Sunny weather", SunnyWeatherCheat);
		DebugMenuAddCmd("Cheats", "Cloudy weather", CloudyWeatherCheat);
		DebugMenuAddCmd("Cheats", "Rainy weather", RainyWeatherCheat);
		DebugMenuAddCmd("Cheats", "Foggy weather", FoggyWeatherCheat);
		DebugMenuAddCmd("Cheats", "Fast weather", FastWeatherCheat);
		DebugMenuAddCmd("Cheats", "Only render wheels", OnlyRenderWheelsCheat);
		DebugMenuAddCmd("Cheats", "Chitty chitty bang bang", ChittyChittyBangBangCheat);
		DebugMenuAddCmd("Cheats", "Strong grip", StrongGripCheat);
		DebugMenuAddCmd("Cheats", "Nasty limbs", NastyLimbsCheat);

		DebugMenuAddVarBool8("Debug", "Show Ped Road Groups", (int8*)&gbShowPedRoadGroups, nil);
		DebugMenuAddVarBool8("Debug", "Show Car Road Groups", (int8*)&gbShowCarRoadGroups, nil);
		DebugMenuAddVarBool8("Debug", "Show Collision Polys", (int8*)&gbShowCollisionPolys, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Buildings", (int8*)&gbDontRenderBuildings, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Big Buildings", (int8*)&gbDontRenderBigBuildings, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Peds", (int8*)&gbDontRenderPeds, nil);
		DebugMenuAddVarBool8("Debug", "Don't render Objects", (int8*)&gbDontRenderObjects, nil);
		DebugMenuAddVar("Debug", "Dbg Surface", &gDbgSurf, nil, 1, 0, 34, nil);

		DebugMenuAddCmd("Debug", "Start Credits", CCredits::Start);
		DebugMenuAddCmd("Debug", "Stop Credits", CCredits::Stop);
	}
}

/*
int (*RsEventHandler_orig)(int a, int b);
int
delayedPatches10(int a, int b)
{
	DebugMenuInit();
	DebugMenuPopulate();

	return RsEventHandler_orig(a, b);
}
*/

void __declspec(naked) HeadlightsFix()
{
	static const float		fMinusOne = -1.0f;
	_asm
	{
		fld		[esp+708h-690h]
		fcomp	fMinusOne
		fnstsw	ax
		and		ah, 5
		cmp		ah, 1
		jnz		HeadlightsFix_DontLimit
		fld		fMinusOne
		fstp	[esp+708h-690h]

HeadlightsFix_DontLimit:
		fld		[esp+708h-690h]
		fabs
		fld		st
		push		0x5382F2
		retn
	}
}

const int   re3_buffsize = 1024;
static char re3_buff[re3_buffsize];

void re3_assert(const char *expr, const char *filename, unsigned int lineno, const char *func)
{
	int nCode;

	strcpy_s(re3_buff, re3_buffsize, "Assertion failed!" );
	strcat_s(re3_buff, re3_buffsize, "\n" );	
	
	strcat_s(re3_buff, re3_buffsize, "File: ");
	strcat_s(re3_buff, re3_buffsize, filename );
	strcat_s(re3_buff, re3_buffsize, "\n" );	

	strcat_s(re3_buff, re3_buffsize, "Line: " );
	_itoa_s( lineno, re3_buff + strlen(re3_buff), re3_buffsize - strlen(re3_buff), 10 );
	strcat_s(re3_buff, re3_buffsize, "\n");
	
	strcat_s(re3_buff, re3_buffsize, "Function: ");
	strcat_s(re3_buff, re3_buffsize, func );
	strcat_s(re3_buff, re3_buffsize, "\n" );	
	
	strcat_s(re3_buff, re3_buffsize, "Expression: ");
	strcat_s(re3_buff, re3_buffsize, expr);
	strcat_s(re3_buff, re3_buffsize, "\n");

	strcat_s(re3_buff, re3_buffsize, "\n" );
	strcat_s(re3_buff, re3_buffsize, "(Press Retry to debug the application)");


	nCode = ::MessageBoxA(NULL, re3_buff, "RE3 Assertion Failed!",
		MB_ABORTRETRYIGNORE|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL);

	if (nCode == IDABORT)
	{
		raise(SIGABRT);
		_exit(3);
	}

	if (nCode == IDRETRY)
	{
		__debugbreak();
		return;
	}

	if (nCode == IDIGNORE)
		return;

	abort();
}

void re3_debug(char *format, ...)
{
	va_list va;
	va_start(va, format);
	vsprintf_s(re3_buff, re3_buffsize, format, va);
	va_end(va);

	printf("%s", re3_buff);
}

void re3_trace(const char *filename, unsigned int lineno, const char *func, char *format, ...)
{
	char buff[re3_buffsize *2];
	va_list va;
	va_start(va, format);
	vsprintf_s(re3_buff, re3_buffsize, format, va);
	va_end(va);
	
	sprintf_s(buff, re3_buffsize * 2, "[%s.%s:%d]: %s", filename, func, lineno, re3_buff);
	
	OutputDebugStringA(buff);
}

void
patch()
{
	StaticPatcher::Apply();

//	Patch<float>(0x46BC61+6, 1.0f);	// car distance
	InjectHook(0x59E460, printf, PATCH_JUMP);
	InjectHook(0x475E00, printf, PATCH_JUMP);	// _Error


	// stolen from silentpatch (sorry)
	Patch<WORD>(0x5382BF, 0x0EEB);
	InjectHook(0x5382EC, HeadlightsFix, PATCH_JUMP);

	InterceptCall(&open_script_orig, open_script, 0x438869);

//	InterceptCall(&RsEventHandler_orig, delayedPatches10, 0x58275E);
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
