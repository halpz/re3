#include <csignal>
#define WITHWINDOWS
#include "common.h"
#include "crossplatform.h"
#include "Renderer.h"
#include "Credits.h"
#include "Camera.h"
#include "Weather.h"
#include "Clock.h"
#include "World.h"
#include "Vehicle.h"
#include "ModelIndices.h"
#include "Streaming.h"
#include "PathFind.h"
#include "Boat.h"
#include "Heli.h"
#include "Automobile.h"
#include "Ped.h"
#include "Particle.h"
#include "Console.h"
#include "Debug.h"
#include "Hud.h"
#include "SceneEdit.h"
#include "Pad.h"
#include "PlayerPed.h"
#include "Radar.h"
#include "debugmenu.h"
#include "Frontend.h"
#include "Text.h"
#include "WaterLevel.h"
#include "main.h"
#include "MBlur.h"
#include "postfx.h"
#include "custompipes.h"

#ifndef _WIN32
#include "assert.h"
#include <stdarg.h>
#endif

#include <list>

#ifdef RWLIBS
extern "C" int vsprintf(char* const _Buffer, char const* const _Format, va_list  _ArgList);
#endif


#ifdef USE_PS2_RAND
unsigned long long myrand_seed = 1;
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

#ifdef CUSTOM_FRONTEND_OPTIONS
#include "frontendoption.h"
#include "platform.h"
#include "Font.h"

void ReloadFrontendOptions(void)
{
	CustomFrontendOptionsPopulate();
}

void RestoreDefGraphics(int8 action) {
	if (action != FEOPTION_ACTION_SELECT)
		return;

	#ifdef PS2_ALPHA_TEST
		gPS2alphaTest = false;
	#endif
	#ifdef MULTISAMPLING
		FrontEndMenuManager.m_nPrefsMSAALevel = FrontEndMenuManager.m_nDisplayMSAALevel = 0;
	#endif
	#ifdef GRAPHICS_MENU_OPTIONS // otherwise Frontend will handle those
		CMenuManager::m_PrefsFrameLimiter = true;
		CMenuManager::m_PrefsVsyncDisp = true;
		CMenuManager::m_PrefsVsync = true;
		CMenuManager::m_PrefsUseWideScreen = false;
		FrontEndMenuManager.m_nDisplayVideoMode = FrontEndMenuManager.m_nPrefsVideoMode;
		#ifdef GTA3_1_1_PATCH
			if (_dwOperatingSystemVersion == OS_WIN98) {
				CMBlur::BlurOn = false;
				CMBlur::MotionBlurClose();
			} else {
				CMBlur::BlurOn = true;
				CMBlur::MotionBlurOpen(Scene.camera);
			}
		#else
			CMBlur::BlurOn = true;
		#endif
		FrontEndMenuManager.SaveSettings();
	#endif
}

void RestoreDefDisplay(int8 action) {
	if (action != FEOPTION_ACTION_SELECT)
		return;

	#ifdef CUTSCENE_BORDERS_SWITCH
		CMenuManager::m_PrefsCutsceneBorders = true;
	#endif
	#ifdef FREE_CAM
		TheCamera.bFreeCam = false;
	#endif
	#ifdef GRAPHICS_MENU_OPTIONS // otherwise Frontend will handle those
		CMenuManager::m_PrefsBrightness = 256;
		CMenuManager::m_PrefsLOD = 1.2f;
		CRenderer::ms_lodDistScale = 1.2f;
		CMenuManager::m_PrefsShowSubtitles = true;
		FrontEndMenuManager.SaveSettings();
	#endif
}

#ifdef MULTISAMPLING
void MultiSamplingGoBack() {
	FrontEndMenuManager.m_nDisplayMSAALevel = FrontEndMenuManager.m_nPrefsMSAALevel;
}

void MultiSamplingButtonPress(int8 action) {
	if (action == FEOPTION_ACTION_SELECT) {
		if (FrontEndMenuManager.m_nDisplayMSAALevel != FrontEndMenuManager.m_nPrefsMSAALevel) {
			FrontEndMenuManager.m_nPrefsMSAALevel = FrontEndMenuManager.m_nDisplayMSAALevel;
			_psSelectScreenVM(FrontEndMenuManager.m_nPrefsVideoMode);
			FrontEndMenuManager.SetHelperText(0);
			FrontEndMenuManager.SaveSettings();
		}
	} else if (action == FEOPTION_ACTION_LEFT || action == FEOPTION_ACTION_RIGHT) {
		if (FrontEndMenuManager.m_bGameNotLoaded) {
			FrontEndMenuManager.m_nDisplayMSAALevel += (action == FEOPTION_ACTION_RIGHT ? 1 : -1);

			int i = 0;
			int maxAA = RwD3D8EngineGetMaxMultiSamplingLevels();
			while (maxAA != 1) {
				i++;
				maxAA >>= 1;
			}

			if (FrontEndMenuManager.m_nDisplayMSAALevel < 0)
				FrontEndMenuManager.m_nDisplayMSAALevel = i;
			else if (FrontEndMenuManager.m_nDisplayMSAALevel > i)
				FrontEndMenuManager.m_nDisplayMSAALevel = 0;
		}
	} else if (action == FEOPTION_ACTION_FOCUSLOSS) {
		if (FrontEndMenuManager.m_nDisplayMSAALevel != FrontEndMenuManager.m_nPrefsMSAALevel) {
			FrontEndMenuManager.m_nDisplayMSAALevel = FrontEndMenuManager.m_nPrefsMSAALevel;
			FrontEndMenuManager.SetHelperText(3);
		}
	}
}

wchar* MultiSamplingDraw(bool *disabled, bool userHovering) {
	static wchar unicodeTemp[64];
	if (userHovering) {
		if (FrontEndMenuManager.m_nDisplayMSAALevel == FrontEndMenuManager.m_nPrefsMSAALevel) {
			if (FrontEndMenuManager.m_nHelperTextMsgId == 1) // Press enter to apply
				FrontEndMenuManager.ResetHelperText();
		} else {
			FrontEndMenuManager.SetHelperText(1);
		}
	} else {
		if (FrontEndMenuManager.m_nDisplayMSAALevel != FrontEndMenuManager.m_nPrefsMSAALevel) {
			FrontEndMenuManager.m_nDisplayMSAALevel = FrontEndMenuManager.m_nPrefsMSAALevel;
		}
	}

	if (!FrontEndMenuManager.m_bGameNotLoaded)
		*disabled = true;

	switch (FrontEndMenuManager.m_nDisplayMSAALevel) {
		case 0:
			return TheText.Get("FEM_OFF");
		default:
			sprintf(gString, "%iX", 1 << (FrontEndMenuManager.m_nDisplayMSAALevel));
			AsciiToUnicode(gString, unicodeTemp);
			return unicodeTemp;
	}
}
#endif

#ifdef MORE_LANGUAGES
void LangPolSelect(int8 action)
{
	if (action == FEOPTION_ACTION_SELECT) {
		FrontEndMenuManager.m_PrefsLanguage = CMenuManager::LANGUAGE_POLISH;
		FrontEndMenuManager.m_bFrontEnd_ReloadObrTxtGxt = true;
		FrontEndMenuManager.InitialiseChangedLanguageSettings();
		FrontEndMenuManager.SaveSettings();
	}
}

void LangRusSelect(int8 action)
{
	if (action == FEOPTION_ACTION_SELECT) {
		FrontEndMenuManager.m_PrefsLanguage = CMenuManager::LANGUAGE_RUSSIAN;
		FrontEndMenuManager.m_bFrontEnd_ReloadObrTxtGxt = true;
		FrontEndMenuManager.InitialiseChangedLanguageSettings();
		FrontEndMenuManager.SaveSettings();
	}
}

void LangJapSelect(int8 action)
{
	if (action == FEOPTION_ACTION_SELECT) {
		FrontEndMenuManager.m_PrefsLanguage = CMenuManager::LANGUAGE_JAPANESE;
		FrontEndMenuManager.m_bFrontEnd_ReloadObrTxtGxt = true;
		FrontEndMenuManager.InitialiseChangedLanguageSettings();
		FrontEndMenuManager.SaveSettings();
	}
}
#endif

#ifdef IMPROVED_VIDEOMODE
void ScreenModeChange(int8 displayedValue)
{
	if (displayedValue != FrontEndMenuManager.m_nPrefsWindowed) {
		FrontEndMenuManager.m_nPrefsWindowed = displayedValue;
		_psSelectScreenVM(FrontEndMenuManager.m_nPrefsVideoMode); // apply same resolution
		FrontEndMenuManager.SetHelperText(0);
		FrontEndMenuManager.SaveSettings();
	}
}
#endif

#ifdef FREE_CAM
void FreeCamChange(int8 displayedValue)
{
	TheCamera.bFreeCam = !!displayedValue;
	FrontEndMenuManager.SaveSettings();
}
#endif

#ifdef CUTSCENE_BORDERS_SWITCH
void BorderModeChange(int8 displayedValue)
{
	CMenuManager::m_PrefsCutsceneBorders = !!displayedValue;
	FrontEndMenuManager.SaveSettings();
}
#endif

#ifdef PS2_ALPHA_TEST
void PS2AlphaTestChange(int8 displayedValue)
{
	gPS2alphaTest = !!displayedValue;
	FrontEndMenuManager.SaveSettings();
}
#endif


// Important: Make sure to read the warnings/informations in frontendoption.h!!
void
CustomFrontendOptionsPopulate(void)
{
	RemoveCustomFrontendOptions(); // if exist

	// -- Graphics/display seperation preperation starts - don't add options in here!
#ifdef GRAPHICS_MENU_OPTIONS
	int graphicsMenu = FrontendScreenAdd("FET_GRA", MENUSPRITE_MAINMENU, MENUPAGE_OPTIONS, 50, 0, 20,
		FONT_HEADING, MEDIUMTEXT_X_SCALE, MEDIUMTEXT_Y_SCALE, FESCREEN_LEFT_ALIGN, true);

	int newDisplayMenu = FrontendScreenAdd("FET_DIS", MENUSPRITE_MAINMENU, MENUPAGE_OPTIONS, 50, 0, 20,
		FONT_HEADING, MEDIUMTEXT_X_SCALE, MEDIUMTEXT_Y_SCALE, FESCREEN_LEFT_ALIGN, true);

	FrontendOptionSetCursor(MENUPAGE_OPTIONS, 2, true);
	FrontendOptionAddRedirect(TheText.Get("FET_DIS"), newDisplayMenu, 0);
	FrontendOptionSetCursor(MENUPAGE_OPTIONS, 3);
	FrontendOptionAddRedirect(TheText.Get("FET_GRA"), graphicsMenu, 0);

#define SWITCH_TO_GRAPHICS_MENU FrontendOptionSetCursor(graphicsMenu, -1);
#define SWITCH_TO_DISPLAY_MENU FrontendOptionSetCursor(newDisplayMenu, -1);
#define CLONE_OPTION(a, b, c, d) FrontendOptionAddBuiltinAction(a, b, c, d);
#define ADD_BACK FrontendOptionAddBackButton(TheText.Get("FEDS_TB"));
#define ADD_RESTORE_DEFAULTS(a) FrontendOptionAddDynamic(TheText.Get("FET_DEF"), nil, nil, a, nil);
#else
	int advancedDisplayMenu = FrontendScreenAdd("FET_ADV", MENUSPRITE_MAINMENU, MENUPAGE_DISPLAY_SETTINGS, 50, 0, 20,
		FONT_HEADING, MEDIUMTEXT_X_SCALE, MEDIUMTEXT_Y_SCALE, FESCREEN_LEFT_ALIGN, true);
	bool movedToAdvMenu = false;

#define SWITCH_TO_GRAPHICS_MENU \
	if (GetNumberOfMenuOptions(MENUPAGE_DISPLAY_SETTINGS) >= 12) { \
		FrontendOptionSetCursor(advancedDisplayMenu, -1); \
		movedToAdvMenu = true; \
	} else { \
		FrontendOptionSetCursor(MENUPAGE_DISPLAY_SETTINGS, -3); \
	}

#define SWITCH_TO_DISPLAY_MENU SWITCH_TO_GRAPHICS_MENU
#define CLONE_OPTION(a, b, c, d)
#define ADD_BACK
#define ADD_RESTORE_DEFAULTS(a)
#endif
	// -- Graphics/display seperation preperation end

	const wchar* off_on[] = { TheText.Get("FEM_OFF"), TheText.Get("FEM_ON") };

#ifdef MORE_LANGUAGES
	FrontendOptionSetCursor(MENUPAGE_LANGUAGE_SETTINGS, -2);
	FrontendOptionAddDynamic(TheText.Get("FEL_POL"), nil, nil, LangPolSelect, nil);
	FrontendOptionAddDynamic(TheText.Get("FEL_RUS"), nil, nil, LangRusSelect, nil);
	FrontendOptionAddDynamic(TheText.Get("FEL_JAP"), nil, nil, LangJapSelect, nil);
#endif

#ifdef MENU_MAP
	FrontendOptionSetCursor(MENUPAGE_PAUSE_MENU, 2);
	FrontendOptionAddRedirect(TheText.Get("FEG_MAP"), MENUPAGE_MAP);
#endif

	// -- Start of graphics menu - add options in display order!

	SWITCH_TO_GRAPHICS_MENU
	CLONE_OPTION(TheText.Get("FED_RES"), MENUACTION_SCREENRES, nil, nil);
	CLONE_OPTION(TheText.Get("FED_WIS"), MENUACTION_WIDESCREEN, nil, nil)

#ifdef IMPROVED_VIDEOMODE
	const wchar* screenModes[] = { TheText.Get("FED_FLS"), TheText.Get("FED_WND") };
	// Storing isn't enabled because it's handled in Frontend
	FrontendOptionAddSelect(TheText.Get("FEM_SCF"), screenModes, 2, (int8*)&FrontEndMenuManager.m_nPrefsWindowed, true, ScreenModeChange, nil);
#endif

	CLONE_OPTION(TheText.Get("FEM_VSC"), MENUACTION_FRAMESYNC, nil, nil);
	CLONE_OPTION(TheText.Get("FEM_FRM"), MENUACTION_FRAMELIMIT, nil, nil);

#ifdef MULTISAMPLING
	SWITCH_TO_GRAPHICS_MENU
	FrontendOptionAddDynamic(TheText.Get("FED_AAS"), MultiSamplingDraw, (int8*)&FrontEndMenuManager.m_nPrefsMSAALevel, MultiSamplingButtonPress, MultiSamplingGoBack, true);
#endif

	CLONE_OPTION(TheText.Get("FED_TRA"), MENUACTION_TRAILS, nil, nil);

#ifdef PS2_ALPHA_TEST
	SWITCH_TO_GRAPHICS_MENU
	FrontendOptionAddSelect(TheText.Get("FEM_2PR"), off_on, 2, (int8*)&gPS2alphaTest, false, PS2AlphaTestChange, nil, true);
#endif

	ADD_RESTORE_DEFAULTS(RestoreDefGraphics)
	ADD_BACK

	// ---- End of Graphics Menu ----

	// -- Start of Display menu - add options in display order!

	SWITCH_TO_DISPLAY_MENU
	CLONE_OPTION(TheText.Get("FED_BRI"), MENUACTION_BRIGHTNESS, nil, nil);
	CLONE_OPTION(TheText.Get("FEM_LOD"), MENUACTION_DRAWDIST, nil, nil);

#ifdef CUTSCENE_BORDERS_SWITCH
	SWITCH_TO_DISPLAY_MENU
	FrontendOptionAddSelect(TheText.Get("FEM_CSB"), off_on, 2, (int8 *)&CMenuManager::m_PrefsCutsceneBorders, false, BorderModeChange, nil, true);
#endif

#ifdef FREE_CAM
	SWITCH_TO_DISPLAY_MENU
	static const wchar* text = (wchar*)L"FREE CAM";
	FrontendOptionAddSelect(text, off_on, 2, (int8*)&TheCamera.bFreeCam, false, FreeCamChange, nil, true);
#endif

	CLONE_OPTION(TheText.Get("FED_SUB"), MENUACTION_SUBTITLES, nil, nil);

	// Add link to advanced graphics menu if it's filled.
#ifndef GRAPHICS_MENU_OPTIONS
	if (movedToAdvMenu) {
		FrontendOptionSetCursor(MENUPAGE_DISPLAY_SETTINGS, -3);
		FrontendOptionAddRedirect(TheText.Get("FET_ADV"), advancedDisplayMenu, 0);

		FrontendOptionSetCursor(advancedDisplayMenu, -1);
		FrontendOptionAddBackButton(TheText.Get("FEDS_TB"));
	}
#endif

	ADD_RESTORE_DEFAULTS(RestoreDefDisplay)
	ADD_BACK
}
#endif

#ifdef DEBUGMENU
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

DebugMenuEntry *carCol1;
DebugMenuEntry *carCol2;

void
SpawnCar(int id)
{
	CVector playerpos;
	CStreaming::RequestModel(id, 0);
	CStreaming::LoadAllRequestedModels(false);
	if(CStreaming::HasModelLoaded(id)){
		playerpos = FindPlayerCoors();
		int node;
		if(!CModelInfo::IsBoatModel(id)){
			node = ThePaths.FindNodeClosestToCoors(playerpos, 0, 100.0f, false, false);
			if(node < 0)
				return;
		}

		CVehicle *v;
		if(CModelInfo::IsBoatModel(id))
			v = new CBoat(id, RANDOM_VEHICLE);
		else
			v = new CAutomobile(id, RANDOM_VEHICLE);

		v->bHasBeenOwnedByPlayer = true;
		if(carCol1)
			DebugMenuEntrySetAddress(carCol1, &v->m_currentColour1);
		if(carCol2)
			DebugMenuEntrySetAddress(carCol2, &v->m_currentColour2);

		if(CModelInfo::IsBoatModel(id))
			v->SetPosition(TheCamera.GetPosition() + TheCamera.GetForward()*15.0f);
		else
			v->SetPosition(ThePaths.m_pathNodes[node].GetPosition());

		v->GetMatrix().GetPosition().z += 4.0f;
		v->SetOrientation(0.0f, 0.0f, 3.49f);
		v->SetStatus(STATUS_ABANDONED);
		v->m_nDoorLock = CARLOCK_UNLOCKED;
		CWorld::Add(v);
	}
}

static void
FixCar(void)
{
	CVehicle *veh = FindPlayerVehicle();
	if(veh == nil)
		return;
	veh->m_fHealth = 1000.0f;
	if(!veh->IsCar())
		return;
	((CAutomobile*)veh)->Damage.SetEngineStatus(0);
	((CAutomobile*)veh)->Fix();
}

#ifdef MENU_MAP
static void
TeleportToWaypoint(void)
{
	if (FindPlayerVehicle()) {
		if (CRadar::TargetMarkerId != -1)
			FindPlayerVehicle()->Teleport(CRadar::TargetMarkerPos + CVector(0.0f, 0.0f, FindPlayerVehicle()->GetColModel()->boundingSphere.center.z));
	} else
		if(CRadar::TargetMarkerId != -1)
			FindPlayerPed()->Teleport(CRadar::TargetMarkerPos + CVector(0.0f, 0.0f, FEET_OFFSET));
}
#endif

static void
SwitchCarCollision(void)
{
	if (FindPlayerVehicle() && FindPlayerVehicle()->IsCar())
		FindPlayerVehicle()->bUsesCollision = !FindPlayerVehicle()->bUsesCollision;
}

static int engineStatus;
static void
SetEngineStatus(void)
{
	CVehicle *veh = FindPlayerVehicle();
	if(veh == nil)
		return;
	if(!veh->IsCar())
		return;
	((CAutomobile*)veh)->Damage.SetEngineStatus(engineStatus);
}

static void
ToggleComedy(void)
{
	CVehicle *veh = FindPlayerVehicle();
	if(veh == nil)
		return;
	veh->bComedyControls = !veh->bComedyControls;
}

static void
PlaceOnRoad(void)
{
	CVehicle *veh = FindPlayerVehicle();
	if(veh == nil)
		return;

	if(veh->IsCar())
		((CAutomobile*)veh)->PlaceOnRoadProperly();
}

static void
ResetCamStatics(void)
{
	TheCamera.Cams[TheCamera.ActiveCam].ResetStatics = true;
}

static const char *carnames[] = {
	"landstal", "idaho", "stinger", "linerun", "peren", "sentinel", "patriot", "firetruk", "trash", "stretch", "manana", "infernus", "blista", "pony",
	"mule", "cheetah", "ambulan", "fbicar", "moonbeam", "esperant", "taxi", "kuruma", "bobcat", "mrwhoop", "bfinject", "corpse", "police", "enforcer",
	"securica", "banshee", "predator", "bus", "rhino", "barracks", "train", "chopper", "dodo", "coach", "cabbie", "stallion", "rumpo", "rcbandit",
	"bellyup", "mrwongs", "mafia", "yardie", "yakuza", "diablos", "columb", "hoods", "airtrain", "deaddodo", "speeder", "reefer", "panlant", "flatbed",
	"yankee", "escape", "borgnine", "toyz", "ghost",
};

static CTweakVar** TweakVarsList;
static int TweakVarsListSize = -1;
static bool bAddTweakVarsNow = false;
static const char *pTweakVarsDefaultPath = NULL;

void CTweakVars::Add(CTweakVar *var)
{
	if(TweakVarsListSize == -1) {
		TweakVarsList = (CTweakVar**)malloc(64 * sizeof(CTweakVar*));
		TweakVarsListSize = 0;
	}
	if(TweakVarsListSize > 63)
		TweakVarsList = (CTweakVar**) realloc(TweakVarsList, (TweakVarsListSize + 1) * sizeof(var));

	TweakVarsList[TweakVarsListSize++] = var;
//	TweakVarsList.push_back(var);
	
	if ( bAddTweakVarsNow )
		var->AddDBG(pTweakVarsDefaultPath);
}

void CTweakVars::AddDBG(const char *path)
{
	pTweakVarsDefaultPath = path;

	for(int i = 0; i < TweakVarsListSize; ++i)
		TweakVarsList[i]->AddDBG(pTweakVarsDefaultPath);
	
	bAddTweakVarsNow = true;
}

void CTweakSwitch::AddDBG(const char *path)
{		
	DebugMenuEntry *e = DebugMenuAddVar(m_pPath == NULL ? path : m_pPath, m_pVarName, (int32_t *)m_pIntVar, m_pFunc, 1, m_nMin, m_nMax, m_aStr);
	DebugMenuEntrySetWrap(e, true);
}
	
void CTweakFunc::AddDBG  (const char *path) { DebugMenuAddCmd     (m_pPath == NULL ? path : m_pPath, m_pVarName, m_pFunc); }
void CTweakBool::AddDBG  (const char *path) { DebugMenuAddVarBool8(m_pPath == NULL ? path : m_pPath, m_pVarName, (int8_t *)m_pBoolVar,  NULL); }
void CTweakInt8::AddDBG  (const char *path) { DebugMenuAddVar     (m_pPath == NULL ? path : m_pPath, m_pVarName, (int8_t *)m_pIntVar,   NULL, m_nStep, m_nLoawerBound, m_nUpperBound, NULL); }
void CTweakUInt8::AddDBG (const char *path) { DebugMenuAddVar     (m_pPath == NULL ? path : m_pPath, m_pVarName, (uint8_t *)m_pIntVar,  NULL, m_nStep, m_nLoawerBound, m_nUpperBound, NULL); }
void CTweakInt16::AddDBG (const char *path) { DebugMenuAddVar     (m_pPath == NULL ? path : m_pPath, m_pVarName, (int16_t *)m_pIntVar,  NULL, m_nStep, m_nLoawerBound, m_nUpperBound, NULL); }
void CTweakUInt16::AddDBG(const char *path) { DebugMenuAddVar     (m_pPath == NULL ? path : m_pPath, m_pVarName, (uint16_t *)m_pIntVar, NULL, m_nStep, m_nLoawerBound, m_nUpperBound, NULL); }
void CTweakInt32::AddDBG (const char *path) { DebugMenuAddVar     (m_pPath == NULL ? path : m_pPath, m_pVarName, (int32_t *)m_pIntVar,  NULL, m_nStep, m_nLoawerBound, m_nUpperBound, NULL); }
void CTweakUInt32::AddDBG(const char *path) { DebugMenuAddVar     (m_pPath == NULL ? path : m_pPath, m_pVarName, (uint32_t *)m_pIntVar, NULL, m_nStep, m_nLoawerBound, m_nUpperBound, NULL); }
void CTweakFloat::AddDBG (const char *path) { DebugMenuAddVar     (m_pPath == NULL ? path : m_pPath, m_pVarName, (float *)m_pIntVar,    NULL, m_nStep, m_nLoawerBound, m_nUpperBound); }

/*
static const char *wt[] = {
			"Sunny", "Cloudy", "Rainy", "Foggy"
		};

SETTWEAKPATH("TEST");		
TWEAKSWITCH(CWeather::NewWeatherType, 0, 3, wt, NULL);
*/

void
DebugMenuPopulate(void)
{
	if(1){
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
		DebugMenuAddVar("Time & Weather", "Wind", (float*)&CWeather::Wind, nil, 0.1f, 0.0f, 1.0f);
		DebugMenuAddVar("Time & Weather", "Time scale", (float*)&CTimer::GetTimeScale(), nil, 0.1f, 0.0f, 10.0f);

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

		static int spawnCarId = MI_LANDSTAL;
		e = DebugMenuAddVar("Spawn", "Spawn Car ID", &spawnCarId, nil, 1, MI_LANDSTAL, MI_GHOST, carnames);
		DebugMenuEntrySetWrap(e, true);
		DebugMenuAddCmd("Spawn", "Spawn Car", [](){
			if(spawnCarId == MI_TRAIN ||
			   spawnCarId == MI_CHOPPER ||
			   spawnCarId == MI_AIRTRAIN ||
			   spawnCarId == MI_DEADDODO ||
			   spawnCarId == MI_ESCAPE)
				return;
			SpawnCar(spawnCarId);
		});
		static uint8 dummy;
		carCol1 = DebugMenuAddVar("Spawn", "First colour", &dummy, nil, 1, 0, 255, nil);
		carCol2 = DebugMenuAddVar("Spawn", "Second colour", &dummy, nil, 1, 0, 255, nil);
		DebugMenuAddCmd("Spawn", "Spawn Stinger", [](){ SpawnCar(MI_STINGER); });
		DebugMenuAddCmd("Spawn", "Spawn Infernus", [](){ SpawnCar(MI_INFERNUS); });
		DebugMenuAddCmd("Spawn", "Spawn Cheetah", [](){ SpawnCar(MI_CHEETAH); });
		DebugMenuAddCmd("Spawn", "Spawn Esperanto", [](){ SpawnCar(MI_ESPERANT); });
		DebugMenuAddCmd("Spawn", "Spawn Stallion", [](){ SpawnCar(MI_STALLION); });
		DebugMenuAddCmd("Spawn", "Spawn Kuruma", [](){ SpawnCar(MI_KURUMA); });
		DebugMenuAddCmd("Spawn", "Spawn Taxi", [](){ SpawnCar(MI_TAXI); });
		DebugMenuAddCmd("Spawn", "Spawn Police", [](){ SpawnCar(MI_POLICE); });
		DebugMenuAddCmd("Spawn", "Spawn Enforcer", [](){ SpawnCar(MI_ENFORCER); });
		DebugMenuAddCmd("Spawn", "Spawn Banshee", [](){ SpawnCar(MI_BANSHEE); });
		DebugMenuAddCmd("Spawn", "Spawn Yakuza", [](){ SpawnCar(MI_YAKUZA); });
		DebugMenuAddCmd("Spawn", "Spawn Yardie", [](){ SpawnCar(MI_YARDIE); });
		DebugMenuAddCmd("Spawn", "Spawn Dodo", [](){ SpawnCar(MI_DODO); });
		DebugMenuAddCmd("Spawn", "Spawn Rhino", [](){ SpawnCar(MI_RHINO); });
		DebugMenuAddCmd("Spawn", "Spawn Firetruck", [](){ SpawnCar(MI_FIRETRUCK); });
		DebugMenuAddCmd("Spawn", "Spawn Predator", [](){ SpawnCar(MI_PREDATOR); });

		DebugMenuAddVarBool8("Render", "Draw hud", &CHud::m_Wants_To_Draw_Hud, nil);
		DebugMenuAddVarBool8("Render", "PS2 Alpha test Emu", &gPS2alphaTest, nil);
		DebugMenuAddVarBool8("Render", "Frame limiter", &FrontEndMenuManager.m_PrefsFrameLimiter, nil);
		DebugMenuAddVarBool8("Render", "VSynch", &FrontEndMenuManager.m_PrefsVsync, nil);
		DebugMenuAddVar("Render", "Max FPS", &RsGlobal.maxFPS, nil, 1, 1, 1000, nil);
#ifdef EXTENDED_COLOURFILTER
		static const char *filternames[] = { "None", "Simple", "Normal", "Mobile" };
		e = DebugMenuAddVar("Render", "Colourfilter", &CPostFX::EffectSwitch, nil, 1, CPostFX::POSTFX_OFF, CPostFX::POSTFX_MOBILE, filternames);
		DebugMenuEntrySetWrap(e, true);
		DebugMenuAddVar("Render", "Intensity", &CPostFX::Intensity, nil, 0.05f, 0, 10.0f);
		DebugMenuAddVarBool8("Render", "Motion Blur", &CPostFX::MotionBlurOn, nil);
#endif
#ifdef EXTENDED_PIPELINES
		static const char *vehpipenames[] = { "MatFX", "Neo" };
		e = DebugMenuAddVar("Render", "Vehicle Pipeline", &CustomPipes::VehiclePipeSwitch, nil,
			1, CustomPipes::VEHICLEPIPE_MATFX, CustomPipes::VEHICLEPIPE_NEO, vehpipenames);
		DebugMenuEntrySetWrap(e, true);
		DebugMenuAddVar("Render", "Neo Vehicle Shininess", &CustomPipes::VehicleShininess, nil, 0.1f, 0, 1.0f);
		DebugMenuAddVar("Render", "Neo Vehicle Specularity", &CustomPipes::VehicleSpecularity, nil, 0.1f, 0, 1.0f);
		DebugMenuAddVar("Render", "Neo Ped Rim light", &CustomPipes::RimlightMult, nil, 0.1f, 0, 1.0f);
		DebugMenuAddVar("Render", "Neo World Lightmaps", &CustomPipes::LightmapMult, nil, 0.1f, 0, 1.0f);
		DebugMenuAddVar("Render", "Neo Road Gloss", &CustomPipes::GlossMult, nil, 0.1f, 0, 1.0f);
#endif
		DebugMenuAddVarBool8("Render", "Show Ped Paths", &gbShowPedPaths, nil);
		DebugMenuAddVarBool8("Render", "Show Car Paths", &gbShowCarPaths, nil);
		DebugMenuAddVarBool8("Render", "Show Car Path Links", &gbShowCarPathsLinks, nil);
		DebugMenuAddVarBool8("Render", "Show Ped Road Groups", &gbShowPedRoadGroups, nil);
		DebugMenuAddVarBool8("Render", "Show Car Road Groups", &gbShowCarRoadGroups, nil);
		DebugMenuAddVarBool8("Render", "Show Collision Lines", &gbShowCollisionLines, nil);
		DebugMenuAddVarBool8("Render", "Show Collision Polys", &gbShowCollisionPolys, nil);
		DebugMenuAddVarBool8("Render", "Don't render Buildings", &gbDontRenderBuildings, nil);
		DebugMenuAddVarBool8("Render", "Don't render Big Buildings", &gbDontRenderBigBuildings, nil);
		DebugMenuAddVarBool8("Render", "Don't render Peds", &gbDontRenderPeds, nil);
		DebugMenuAddVarBool8("Render", "Don't render Vehicles", &gbDontRenderVehicles, nil);
		DebugMenuAddVarBool8("Render", "Don't render Objects", &gbDontRenderObjects, nil);
		DebugMenuAddVarBool8("Render", "Don't Render Water", &gbDontRenderWater, nil);

		DebugMenuAddVarBool8("Debug", "pad 1 -> pad 2", &CPad::m_bMapPadOneToPadTwo, nil);
		DebugMenuAddVarBool8("Debug", "Edit on", &CSceneEdit::m_bEditOn, nil);
#ifdef MENU_MAP
		DebugMenuAddCmd("Debug", "Teleport to map waypoint", TeleportToWaypoint);
#endif
		DebugMenuAddCmd("Debug", "Switch car collision", SwitchCarCollision);
		DebugMenuAddVar("Debug", "Engine Status", &engineStatus, nil, 1, 0, 226, nil);
		DebugMenuAddCmd("Debug", "Set Engine Status", SetEngineStatus);
		DebugMenuAddCmd("Debug", "Fix Car", FixCar);
		DebugMenuAddCmd("Debug", "Toggle Comedy Controls", ToggleComedy);
		DebugMenuAddCmd("Debug", "Place Car on Road", PlaceOnRoad);

		DebugMenuAddVarBool8("Debug", "Catalina Heli On", &CHeli::CatalinaHeliOn, nil);
		DebugMenuAddCmd("Debug", "Catalina Fly By", CHeli::StartCatalinaFlyBy);
		DebugMenuAddCmd("Debug", "Catalina Take Off", CHeli::CatalinaTakeOff);
		DebugMenuAddCmd("Debug", "Catalina Fly Away", CHeli::MakeCatalinaHeliFlyAway);
		DebugMenuAddVarBool8("Debug", "Script Heli On", &CHeli::ScriptHeliOn, nil);

#ifdef CUSTOM_FRONTEND_OPTIONS
		DebugMenuAddCmd("Debug", "Reload custom frontend options", ReloadFrontendOptions);
#endif
		DebugMenuAddVarBool8("Debug", "Toggle popping heads on headshot", &CPed::bPopHeadsOnHeadshot, nil);
		DebugMenuAddCmd("Debug", "Start Credits", CCredits::Start);
		DebugMenuAddCmd("Debug", "Stop Credits", CCredits::Stop);

		DebugMenuAddVarBool8("Debug", "Show DebugStuffInRelease", &gbDebugStuffInRelease, nil);
#ifdef TIMEBARS
		DebugMenuAddVarBool8("Debug", "Show Timebars", &gbShowTimebars, nil);
#endif

		extern bool PrintDebugCode;
		extern int16 DebugCamMode;
		DebugMenuAddVarBool8("Cam", "Use mouse Cam", &CCamera::m_bUseMouse3rdPerson, nil);
#ifdef FREE_CAM
		DebugMenuAddVarBool8("Cam", "Free Cam", &CCamera::bFreeCam, nil);
#endif
		DebugMenuAddVarBool8("Cam", "Print Debug Code", &PrintDebugCode, nil);
		DebugMenuAddVar("Cam", "Cam Mode", &DebugCamMode, nil, 1, 0, CCam::MODE_EDITOR, nil);
		DebugMenuAddCmd("Cam", "Normal", []() { DebugCamMode = 0; });
		DebugMenuAddCmd("Cam", "Follow Ped With Bind", []() { DebugCamMode = CCam::MODE_FOLLOW_PED_WITH_BIND; });
		DebugMenuAddCmd("Cam", "Reaction", []() { DebugCamMode = CCam::MODE_REACTION; });
		DebugMenuAddCmd("Cam", "Chris", []() { DebugCamMode = CCam::MODE_CHRIS; });
		DebugMenuAddCmd("Cam", "Reset Statics", ResetCamStatics);

		CTweakVars::AddDBG("Debug");
	}
}
#endif

const int   re3_buffsize = 1024;
static char re3_buff[re3_buffsize];

void re3_assert(const char *expr, const char *filename, unsigned int lineno, const char *func)
{
#ifdef _WIN32
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


	nCode = ::MessageBoxA(nil, re3_buff, "RE3 Assertion Failed!",
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
#else
	// TODO
	printf("\nRE3 ASSERT FAILED\n\tFile: %s\n\tLine: %d\n\tFunction: %s\n\tExpression: %s\n",filename,lineno,func,expr);
	assert(false);
#endif
}

void re3_debug(const char *format, ...)
{
	va_list va;
	va_start(va, format);
#ifdef _WIN32
	vsprintf_s(re3_buff, re3_buffsize, format, va);
#else
	vsprintf(re3_buff, format, va);
#endif
	va_end(va);

	printf("%s", re3_buff);
	CDebug::DebugAddText(re3_buff);
}

void re3_trace(const char *filename, unsigned int lineno, const char *func, const char *format, ...)
{
	char buff[re3_buffsize *2];
	va_list va;
	va_start(va, format);
#ifdef _WIN32
	vsprintf_s(re3_buff, re3_buffsize, format, va);
	va_end(va);
	
	sprintf_s(buff, re3_buffsize * 2, "[%s.%s:%d]: %s", filename, func, lineno, re3_buff);
#else
	vsprintf(re3_buff, format, va);
	va_end(va);
	
	sprintf(buff, "[%s.%s:%d]: %s", filename, func, lineno, re3_buff);
#endif

	OutputDebugString(buff);
}

void re3_usererror(const char *format, ...)
{
	va_list va;
	va_start(va, format);
#ifdef _WIN32
	vsprintf_s(re3_buff, re3_buffsize, format, va);
	va_end(va);
	
	::MessageBoxA(nil, re3_buff, "RE3 Error!",
		MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL);

	raise(SIGABRT);
	_exit(3);
#else
	vsprintf(re3_buff, format, va);
	printf("\nRE3 Error!\n\t%s\n",re3_buff);
	assert(false);
#endif
}

#ifdef VALIDATE_SAVE_SIZE
int32 _saveBufCount;
#endif
