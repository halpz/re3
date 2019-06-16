#pragma

#include "Sprite2d.h"

enum {
	LANGUAGE_AMERICAN,
	LANGUAGE_FRENCH,
	LANGUAGE_GERMAN,
	LANGUAGE_ITALIAN,
	LANGUAGE_SPANISH,
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

struct tSkinInfo
{
	int field_0;
	char skinName[256];
	char currSkinName[256];
	char date[256];
	int field_304;
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
 int field_544;
	int m_nCurrScreen;
	int m_nCurrOption;
 int field_550;
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

	static bool &m_PrefsAllowNastyGame;
	static bool &m_bStartUpFrontEndRequested;

	void Process(void);
	void DrawFrontEnd(void);
	void UnloadTextures(void);
	void LoadAllTextures(void);
	void LoadSettings(void);
	void WaitForUserCD(void);
	int FadeIn(int alpha);
};

static_assert(sizeof(CMenuManager) == 0x564, "CMenuManager: error");

extern CMenuManager &FrontEndMenuManager;
