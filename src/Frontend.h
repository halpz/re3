#pragma

#include "Sprite2d.h"

#define HEADER_POS_X 35.0f
#define HEADER_POS_Y 93.0f
#define HEADER_WIDTH 0.84f
#define HEADER_HEIGHT 1.6f

#define ACTION_POS_X 20.0f
#define ACTION_POS_Y 37.5f
#define ACTION_WIDTH 0.675f
#define ACTION_HEIGHT 0.81f

#define COLUMN_POS_X HEADER_POS_X + 16.0f
#define COLUMN_MAX_Y 149.0f
#define COLUMN_MID_Y 100.0f
#define COLUMN_MIN_Y 110.0f
#define COLUMN_PAUSE_Y 25.0f
#define COLUMN_START_Y 9.0f
#define COLUMN_FEDS 139.0f

#define COLUMN_SAVE_X 121.0f
#define COLUMN_SAVE_Y 111.0f

#define COLUMN_SPACING_MAX 24.0f
#define COLUMN_SPACING_MIN 20.0f

#define SELECT_BOX_MAX 20.5f
#define SELECT_BOX_MIN 17.0f

#define FE_RADIO_ICON_X 31.5f
#define FE_RADIO_ICON_Y 29.5f
#define FE_RADIO_ICON_W 60.0f
#define FE_RADIO_ICON_H 60.0f

#define DROP_COLOR_A 150
#define DROP_COLOR_SIZE -1

#define SLIDER_X 306.0f

enum {
	LANGUAGE_AMERICAN,
	LANGUAGE_FRENCH,
	LANGUAGE_GERMAN,
	LANGUAGE_ITALIAN,
	LANGUAGE_SPANISH,
};

enum eFrontendSprites {
	FE2_MAINPANEL_UL,
	FE2_MAINPANEL_UR,
	FE2_MAINPANEL_DL,
	FE2_MAINPANEL_DR,
	FE2_MAINPANEL_DR2,
	FE2_TABACTIVE,
	FE_ICONBRIEF,
	FE_ICONSTATS,
	FE_ICONCONTROLS,
	FE_ICONSAVE,
	FE_ICONAUDIO,
	FE_ICONDISPLAY,
	FE_ICONLANGUAGE,
	FE_CONTROLLER,
	FE_CONTROLLERSH,
	FE_ARROWS1,
	FE_ARROWS2,
	FE_ARROWS3,
	FE_ARROWS4,
	FE_RADIO1,
	FE_RADIO2,
	FE_RADIO3,
	FE_RADIO4,
	FE_RADIO5,
	FE_RADIO6,
	FE_RADIO7,
	FE_RADIO8,
	FE_RADIO9,
};

enum eMenuSprites {
	MENU_CONNECTION,
	MENU_FINDGAME,
	MENU_HOSTGAME,
	MENU_MAINMENU,
	MENU_PLAYERSET,
	MENU_SINGLEPLAYER,
	MENU_MULTIPLAYER,
	MENU_DMALOGO,
	MENU_GTALOGO,
	MENU_RSTARLOGO,
	MENU_GAMESPY,
	MENU_MOUSE,
	MENU_MOUSET,
	MENU_MP3LOGO,
	MENU_DOWNOFF,
	MENU_DOWNON,
	MENU_UPOFF,
	MENU_UPON,
	MENU_GTA3LOGO,
};

enum eMenuActions {
	MENU_ACTION_SAVE_1 = 1,
	MENU_ACTION_SAVE_2,
	MENU_ACTION_SAVE_3,
	MENU_ACTION_SAVE_4,
	MENU_ACTION_SAVE_5,
	MENU_ACTION_SAVE_6,
	MENU_ACTION_SAVE_7,
	MENU_ACTION_SAVE_8,
};

enum eMenuScreen {
	MENU_NONE = 0,
	MENU_STATS = 1,
	MENU_NEW_GAME = 2,
	MENU_BRIEFS = 3,
	MENU_CONTROLLER_SETTINGS = 4,
	MENU_SOUND_SETTINGS = 5,
	MENU_GRAPHICS_SETTINGS = 6,
	MENU_LANGUAGE_SETTINGS = 7,
	MENU_CHOOSE_LOAD_SLOT = 8,
	MENU_CHOOSE_DELETE_SLOT = 9,
	MENU_NEW_GAME_RELOAD = 10,
	MENU_LOAD_SLOT_CONFIRM = 11,
	MENU_DELETE_SLOT_CONFIRM = 12,
	MENU_13 = 13,
	MENU_LOADING_IN_PROGRESS = 14,
	MENU_DELETING_IN_PROGRESS = 15,
	MENU_16 = 16,
	MENU_DELETE_FAILED = 17,
	MENU_DEBUG_MENU = 18,
	MENU_MEMORY_CARD_1 = 19,
	MENU_MEMORY_CARD_2 = 20,
	MENU_MULTIPLAYER_MAIN = 21,
	MENU_SAVE_FAILED_1 = 22,
	MENU_SAVE_FAILED_2 = 23,
	MENU_SAVE = 24,
	MENU_NO_MEMORY_CARD = 25,
	MENU_CHOOSE_SAVE_SLOT = 26,
	MENU_SAVE_OVERWRITE_CONFIRM = 27,
	MENU_MULTIPLAYER_MAP = 28,
	MENU_MULTIPLAYER_CONNECTION = 29,
	MENU_MULTIPLAYER_FIND_GAME = 30,
	MENU_MULTIPLAYER_MODE = 31,
	MENU_MULTIPLAYER_CREATE = 32,
	MENU_MULTIPLAYER_START = 33,
	MENU_SKIN_SELECT_OLD = 34,
	MENU_CONTROLLER_PC = 35,
	MENU_CONTROLLER_PC_OLD1 = 36,
	MENU_CONTROLLER_PC_OLD2 = 37,
	MENU_CONTROLLER_PC_OLD3 = 38,
	MENU_CONTROLLER_PC_OLD4 = 39,
	MENU_CONTROLLER_DEBUG = 40,
	MENU_OPTIONS = 41,
	MENU_EXIT = 42,
	MENU_SAVING_IN_PROGRESS = 43,
	MENU_SAVE_SUCCESSFUL = 44,
	MENU_DELETING = 45,
	MENU_DELETE_SUCCESS = 46,
	MENU_SAVE_FAILED = 47,
	MENU_LOAD_FAILED = 48,
	MENU_LOAD_FAILED_2 = 49,
	MENU_FILTER_GAME = 50,
	MENU_START_MENU = 51,
	MENU_PAUSE_MENU = 52,
	MENU_CHOOSE_MODE = 53,
	MENU_SKIN_SELECT = 54,
	MENU_KEYBOARD_CONTROLS = 55,
	MENU_MOUSE_CONTROLS = 56,
	MENU_57 = 57,
	MENU_58 = 58,
};

enum eMenuAction {
	MENUACTION_NOTHING,
	MENUACTION_LABEL,
	MENUACTION_CHANGEMENU,
	MENUACTION_CTRLVIBRATION,
	MENUACTION_CTRLCONFIG,
	MENUACTION_CTRLDISPLAY,
	MENUACTION_FRAMESYNC,
	MENUACTION_FRAMELIMIT,
	MENUACTION_TRAILS,
	MENUACTION_SUBTITLES,
	MENUACTION_WIDESCREEN,
	MENUACTION_BRIGHTNESS,
	MENUACTION_DRAWDIST,
	MENUACTION_MUSICVOLUME,
	MENUACTION_SFXVOLUME,
	MENUACTION_UNK15,
	MENUACTION_RADIO,
	MENUACTION_LANG_ENG,
	MENUACTION_LANG_FRE,
	MENUACTION_LANG_GER,
	MENUACTION_LANG_IT,
	MENUACTION_LANG_SPA,
	MENUACTION_UPDATESAVE,
	MENUACTION_CHECKSAVE,
	MENUACTION_UNK24,
	MENUACTION_NEWGAME,
	MENUACTION_RELOADIDE,
	MENUACTION_RELOADIPL,
	MENUACTION_SETDBGFLAG,
	MENUACTION_SWITCHBIGWHITEDEBUGLIGHT,
	MENUACTION_PEDROADGROUPS,
	MENUACTION_CARROADGROUPS,
	MENUACTION_COLLISIONPOLYS,
	MENUACTION_REGMEMCARD1,
	MENUACTION_TESTFORMATMEMCARD1,
	MENUACTION_TESTUNFORMATMEMCARD1,
	MENUACTION_CREATEROOTDIR,
	MENUACTION_CREATELOADICONS,
	MENUACTION_FILLWITHGUFF,
	MENUACTION_SAVEONLYTHEGAME,
	MENUACTION_SAVEGAME,
	MENUACTION_SAVEGAMEUNDERGTA,
	MENUACTION_CREATECOPYPROTECTED,
	MENUACTION_TESTSAVE,
	MENUACTION_TESTLOAD,
	MENUACTION_TESTDELETE,
	MENUACTION_PARSEHEAP,
	MENUACTION_SHOWCULL,
	MENUACTION_MEMCARDSAVECONFIRM,
	MENUACTION_UPDATEMEMCARDSAVE,
	MENUACTION_UNK50,
	MENUACTION_DEBUGSTREAM,
	MENUACTION_MPMAP_LIBERTY,
	MENUACTION_MPMAP_REDLIGHT,
	MENUACTION_MPMAP_CHINATOWN,
	MENUACTION_MPMAP_TOWER,
	MENUACTION_MPMAP_SEWER,
	MENUACTION_MPMAP_INDUSTPARK,
	MENUACTION_MPMAP_DOCKS,
	MENUACTION_MPMAP_STAUNTON,
	MENUACTION_MPMAP_DEATHMATCH1,
	MENUACTION_MPMAP_DEATHMATCH2,
	MENUACTION_MPMAP_TEAMDEATH1,
	MENUACTION_MPMAP_TEAMDEATH2,
	MENUACTION_MPMAP_STASH,
	MENUACTION_MPMAP_CAPTURE,
	MENUACTION_MPMAP_RATRACE,
	MENUACTION_MPMAP_DOMINATION,
	MENUACTION_STARTMP,
	MENUACTION_UNK69,
	MENUACTION_UNK70,
	MENUACTION_FINDMP,
	MENUACTION_REDEFCTRL,
	MENUACTION_UNK73,
	MENUACTION_INITMP,
	MENUACTION_MP_PLAYERCOLOR,
	MENUACTION_MP_PLAYERNAME,
	MENUACTION_MP_GAMENAME,
	MENUACTION_GETKEY,
	MENUACTION_SHOWHEADBOB,
	MENUACTION_UNK80,
	MENUACTION_INVVERT,
	MENUACTION_CANCLEGAME,
	MENUACTION_MP_PLAYERNUMBER,
	MENUACTION_MOUSESENS,
	MENUACTION_CHECKMPGAMES,
	MENUACTION_CHECKMPPING,
	MENUACTION_MP_SERVER,
	MENUACTION_MP_MAP,
	MENUACTION_MP_GAMETYPE,
	MENUACTION_MP_LAN,
	MENUACTION_MP_INTERNET,
	MENUACTION_RESUME,
	MENUACTION_DONTCANCLE,
	MENUACTION_SCREENRES,
	MENUACTION_AUDIOHW,
	MENUACTION_SPEAKERCONF,
	MENUACTION_PLAYERSETUP,
	MENUACTION_RESTOREDEF,
	MENUACTION_CTRLMETHOD,
	MENUACTION_DYNAMICACOUSTIC,
	MENUACTION_LOADRADIO,
	MENUACTION_MOUSESTEER,
	MENUACTION_UNK103,
	MENUACTION_UNK104,
	MENUACTION_UNK105,
	MENUACTION_UNK106,
	MENUACTION_UNK107,
	MENUACTION_UNK108,
	MENUACTION_UNK109,
	MENUACTION_UNK110,
};

enum eCheckHover {
	ACTIVATE_OPTION = 2,
	IGNORE_OPTION = 42,
};

struct tSkinInfo
{
	int field_0;
	char skinName[256];
	char currSkinName[256];
	char date[256];
	int field_304;
};

struct CMenuScreen {
	char m_ScreenName[8];
	int32 m_PreviousPage[3]; //
	int32 m_ParentEntry[2];

	struct CMenuEntry
	{
		int32 m_Action;
		char m_EntryName[8];
		int32 m_ActionSlot;
		int32 m_TargetMenu;
	} m_aEntries[18];
};

class CMenuManager
{
public:
	int32 m_nPrefsVideoMode;
	int32 m_nDisplayVideoMode;
	int8 m_nPrefsAudio3DProviderIndex;
	bool m_bKeyChangeNotProcessed;
	char m_aSkinName[256];
	int32 m_nHelperTextMsgId;
	bool m_bLanguageLoaded;
	bool m_bMenuActive;
 char field_112;
 char field_113;
	bool m_bStartGameLoading;
	bool m_bFirstTime;
	bool m_bGameNotLoaded;
	int32 m_nMousePosX;
	int32 m_nMousePosY;
	int32 m_nMouseTempPosX;
	int32 m_nMouseTempPosY;
	bool m_bShowMouse;
 tSkinInfo field_12C;
	tSkinInfo *m_pSelectedSkin;
 tSkinInfo *field_438;
 float field_43C;
 int field_440;
	int m_nSkinsTotal;
 char _unk0[4];
 int field_44C;
	bool m_bSkinsFound;
	bool m_bQuitGameNoCD;
 char field_452;
	bool m_bSaveMenuActive;
	bool m_bLoadingSavedGame;
 char field_455;
 char field_456;
	bool m_bSpritesLoaded;
	CSprite2d m_aFrontEndSprites[28];
	CSprite2d m_aMenuSprites[20];
 int field_518;
	int m_nMenuFadeAlpha;
 char field_520;
 char field_521;
 char field_522;
 char field_523;
 char field_524;
	int m_CurrCntrlAction;
 char _unk1[4];
 int field_530;
 char field_534;
 char field_535;
 int8 field_536;
	int m_nHelperTextAlpha;
	int m_nMouseOldPosX;
	int m_nMouseOldPosY;
	int m_nHoverOption;
	int m_nCurrScreen;
	int m_nCurrOption;
	int m_nCurrentInput;
	int m_nPrevScreen;
 int field_558;
	int m_nCurrSaveSlot;
	int m_nScreenChangeDelayTimer;

	static int32 &OS_Language;
	static int8 &m_PrefsUseVibration;
	static int8 &m_DisplayControllerOnFoot;
	static int8 &m_PrefsUseWideScreen;
	static int8 &m_PrefsRadioStation;
	static int8 &m_PrefsVsync;
	static int8 &m_PrefsVsyncDisp;
	static int8 &m_PrefsFrameLimiter;
	static int8 &BlurOn;
	static int8 &m_PrefsShowSubtitles;
	static int8 &m_PrefsSpeakers;
	static int8 &m_ControlMethod;
	static int8 &m_PrefsDMA;
	static int8 &m_PrefsLanguage;
	static int8 &m_bDisableMouseSteering;
	static int32 &m_PrefsBrightness;
	static float &m_PrefsLOD;
	static int8 &m_bFrontEnd_ReloadObrTxtGxt;
	static int32 &m_PrefsMusicVolume;
	static int32 &m_PrefsSfxVolume;
	static bool &m_bStartUpFrontEndRequested;
	static bool &m_bShutDownFrontEndRequested;

	static bool &m_PrefsAllowNastyGame;

private:
	enum eColumns { L, R, COLUMNS, };

public:
	void BuildStatLine(char *, void *, uint16, void *);
	static void CentreMousePointer();
	void CheckCodesForControls(int, int);
	bool CheckHover(int x1, int x2, int y1, int y2);
	int CostructStatLine(int);
	void DisplayHelperText();
	float DisplaySlider(float, float, float, float, float, float);
	void DoSettingsBeforeStartingAGame();
	void Draw();
	void DrawControllerBound(int, int, int, uint8);
	void DrawControllerScreenExtraText(int, int, int);
	void DrawControllerSetupScreen();
	void DrawFrontEnd();
	void DrawFrontEndNormal();
	void DrawPlayerSetupScreen();
	int FadeIn(int alpha);
	void FilterOutColorMarkersFromString(uint16, CRGBA &);
	int GetStartOptionsCntrlConfigScreens();
	static void InitialiseChangedLanguageSettings();
	void LoadAllTextures();
	void LoadSettings();
	static void MessageScreen(char *);
	static void PickNewPlayerColour();
	void PrintBriefs();
	static void PrintErrorMessage();
	void PrintStats();
	void Process();
	void ProcessButtonPresses();
	void ProcessOnOffMenuOptions();
	static void RequestFrontEndShutdown();
	static void RequestFrontEndStartUp();
	void ResetHelperText();
	void SaveLoadFileError_SetUpErrorScreen();
	void SaveSettings();
	void SetHelperText(int text);
	void ShutdownJustMenu();
	static float StretchX(float);
	static float StretchY(float );
	void SwitchMenuOnAndOff();
	void UnloadTextures();
	void WaitForUserCD();
};

static_assert(sizeof(CMenuManager) == 0x564, "CMenuManager: error");

extern CMenuManager &FrontEndMenuManager;
