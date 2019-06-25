#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "common.h"
#include "patcher.h"
#include "win.h"
#include "Frontend.h"
#include "Font.h"
#include "Pad.h"
#include "Text.h"
#include "main.h"
#include "Timer.h"
#include "Game.h"
#include "DMAudio.h"
#include "MusicManager.h"
#include "FileMgr.h"
#include "Streaming.h"
#include "TxdStore.h"
#include "General.h"
#include "PCSave.h"
#include "Script.h"
#include "Camera.h"

int32 &CMenuManager::OS_Language = *(int32*)0x5F2F78;
int8 &CMenuManager::m_PrefsUseVibration = *(int8*)0x95CD92;
int8 &CMenuManager::m_DisplayControllerOnFoot = *(int8*)0x95CD8D;
int8 &CMenuManager::m_PrefsVsync = *(int8*)0x5F2E58;
int8 &CMenuManager::m_PrefsVsyncDisp = *(int8*)0x5F2E5C;
int8 &CMenuManager::m_PrefsFrameLimiter = *(int8*)0x5F2E60;
int8 &CMenuManager::BlurOn = *(int8*)0x95CDAD;
int8 &CMenuManager::m_PrefsShowSubtitles = *(int8*)0x5F2E54;
int8 &CMenuManager::m_PrefsSpeakers = *(int8*)0x95CD7E;
int8 &CMenuManager::m_ControlMethod = *(int8*)0x8F5F7C;
int8 &CMenuManager::m_PrefsDMA = *(int8*)0x5F2F74;
int8 &CMenuManager::m_PrefsLanguage = *(int8*)0x941238;

bool &CMenuManager::m_PrefsAllowNastyGame = *(bool*)0x5F2E64;
bool &CMenuManager::m_bStartUpFrontEndRequested = *(bool*)0x95CCF4;
bool &CMenuManager::m_bShutDownFrontEndRequested = *(bool*)0x95CD6A;

int8 &CMenuManager::m_PrefsUseWideScreen = *(int8*)0x95CD23;
int8 &CMenuManager::m_PrefsRadioStation = *(int8*)0x95CDA4;
int8 &CMenuManager::m_bDisableMouseSteering = *(int8*)0x60252C;
int32 &CMenuManager::m_PrefsBrightness = *(int32*)0x5F2E50;
float &CMenuManager::m_PrefsLOD = *(float*)0x8F42C4;
int8 &CMenuManager::m_bFrontEnd_ReloadObrTxtGxt = *(int8*)0x628CFC;
int32 &CMenuManager::m_PrefsMusicVolume = *(int32*)0x5F2E4C;
int32 &CMenuManager::m_PrefsSfxVolume = *(int32*)0x5F2E48;

CMenuManager &FrontEndMenuManager = *(CMenuManager*)0x8F59D8;

// TODO: replace magic numbers with enums
const CMenuScreen aScreens[] = {
	// MENU_PAGE_NONE = 0
	{ "", -1, -1, 1, 0, 0, },

	// MENU_PAGE_STATS = 1
	{ "FET_STA", 0, 0, 0, 5, 2,
		2, "FEDS_TB",  0, 0,
	},

	// MENU_PAGE_NEW_GAME = 2
	{ "FET_SGA", 0, 0, 0, 0, 1,
		 2, "FES_SNG", 0, 10,
		22, "GMLOAD",  0,  8,
		 2, "FES_DGA", 0,  9,
		 2, "FEDS_TB", 0, 0,
	},

	// MENU_PAGE_BRIEFS = 3
	{ "FET_BRE", 0, 0, 0, 6, 3,
		2, "FEDS_TB", 0, 0,
	},

	// MENU_CONTROLLER_SETTINGS = 4
	{ "FET_CON", 41, 41, 41, 0, 0,

	},

	// MENU_PAGE_SOUND_SETTINGS = 5
	{ "FET_AUD", 41, 41, 41, 1, 1,
		13, "FEA_MUS", 0, 5,
		14, "FEA_SFX", 0, 5,
		95, "FEA_3DH", 0, 5,
		96, "FEA_SPK", 0, 5,
		100, "FET_DAM", 0, 5,
		16, "FEA_RSS", 0, 5,
		98, "FET_DEF", 0, 5,
		2, "FEDS_TB", 0, 0,
	},

	// MENU_PAGE_GRAPHICS_SETTINGS = 6
	{ "FET_DIS", 41, 41, 41, 2, 2,
		11, "FED_BRI", 0, 6,
		12, "FEM_LOD", 0, 6,
		 6, "FEM_VSC", 0, 6,
		 7, "FEM_FRM", 0, 6,
		 8, "FED_TRA", 0, 6,
		 9, "FED_SUB", 0, 6,
		10, "FED_WIS", 0, 6,
		94, "FED_RES", 0, 6,
		98, "FET_DEF", 0, 6,
		2, "FEDS_TB", 0, 0,
	},

	// MENU_PAGE_LANGUAGE_SETTINGS = 7
	{ "FET_LAN", 41, 41, 41, 3, 3,
		17, "FEL_ENG", 0, 7,
		18, "FEL_FRE", 0, 7,
		19, "FEL_GER", 0, 7,
		20, "FEL_ITA", 0, 7,
		21, "FEL_SPA", 0, 7,
		 2, "FEDS_TB", 0, 0,
	},

	// MENU_PAGE_CHOOSE_LOAD_SLOT = 8
	{ "FET_LG", 2, 2, 2, 1, 1,
		 2, "FESZ_CA", 0, 2,
		23, "FEM_SL1", 2, 11,
		23, "FEM_SL2", 3, 11,
		23, "FEM_SL3", 4, 11,
		23, "FEM_SL4", 5, 11,
		23, "FEM_SL5", 6, 11,
		23, "FEM_SL6", 7, 11,
		23, "FEM_SL7", 8, 11,
		23, "FEM_SL8", 9, 11,
	},

	// MENU_PAGE_CHOOSE_DELETE_SLOT = 9
	{ "FET_DG", 2, 2, 2, 2, 2,
		2, "FESZ_CA", 0, 2,
		2, "FEM_SL1", 2, 12,
		2, "FEM_SL2", 3, 12,
		2, "FEM_SL3", 4, 12,
		2, "FEM_SL4", 5, 12,
		2, "FEM_SL5", 6, 12,
		2, "FEM_SL6", 7, 12,
		2, "FEM_SL7", 8, 12,
		2, "FEM_SL8", 9, 12,
	},

	// MENU_PAGE_NEW_GAME_RELOAD = 10
	{ "FET_NG", 2, 2, 2, 0, 0,
		 1, "FESZ_QR", 0,  0,
		 2, "FEM_NO",  0,  2,
		25, "FEM_YES", 0, 10,
	},

	// MENU_PAGE_LOAD_SLOT_CONFIRM = 11
	{ "FET_LG", 8, 8, 8, 0, 0,
		 1, "FESZ_QL", 0,  0,
		 2, "FEM_NO",  0,  8,
		 2, "FEM_YES", 0, 14,
	},

	// MENU_PAGE_DELETE_SLOT_CONFIRM = 12
	{ "FET_DG", 9, 9, 9, 0, 0,
		 1, "FESZ_QD", 0,  0,
		 2, "FEM_NO",  0,  9,
		 2, "FEM_YES", 0, 45,
	},

	// MENU_PAGE_13 = 13
	{ "FES_NOC", -1, -1, -1, 0, 0,

	},

	// MENU_PAGE_LOADING_IN_PROGRESS = 14
	{ "FET_LG", -1, -1, -1, 0, 0,
		1, "FED_LDW", 0, 11,
	},

	// MENU_PAGE_DELETING_IN_PROGRESS = 15
	{ "FET_DG", -1, -1, -1, 0, 0,
		1, "FEDL_WR", 0, 0,
	},

	// MENU_PAGE_16 = 16
	{ "FET_LG", -1, -1, -1, 0, 0,
		1, "FES_LOE", 0, 0,
	},

	// MENU_PAGE_DELETE_FAILED = 17
	{ "FET_DG", -1, -1, -1, 0, 0,
		1, "FES_DEE", 0, 0,
		2, "FEC_OKK", 0, 9,
	},

	// MENU_PAGE_DEBUG_MENU = 18
	{ "FED_DBG", -1, -1, -1, 0, 0,

	},

	// MENU_PAGE_MEMORY_CARD_1 = 19
	{ "FEM_MCM", -1, -1, -1, 0, 0,

	},

	// MENU_PAGE_MEMORY_CARD_2 = 20
	{ "FEM_MC2", -1, -1, -1, 0, 0,

	},

	// MENU_PAGE_MULTIPLAYER_MAIN = 21
	{ "FET_MP", -1, -1, -1, 0, 0,

	},

	// MENU_PAGE_SAVE_FAILED_1 = 22
	{ "MCDNSP", -1, -1, -1, 0, 0,
		48, "JAILB_U", 0, 0,
	},

	// MENU_PAGE_SAVE_FAILED_2 = 23
	{ "MCGNSP", -1, -1, -1, 0, 0,
		48, "JAILB_U", 0, 0,
	},

	// MENU_PAGE_SAVE = 24
	{ "FET_SG", -1, -1, -1, 0, 0,
		1, "FES_SCG",  0,  0,
	   22, "GMSAVE",   0, 26,
	   49, "FESZ_CA",  0,  0,
	},

	// MENU_PAGE_NO_MEMORY_CARD = 25
	{ "FES_NOC", -1, -1, -1, 0, 0,

	},

	// MENU_PAGE_CHOOSE_SAVE_SLOT = 26
	{ "FET_SG", -1, -1, -1, 0, 0,
		49, "FESZ_CA", 0, 0,
		 2, "FEM_SL1", 2, 27,
		 2, "FEM_SL2", 3, 27,
		 2, "FEM_SL3", 4, 27,
		 2, "FEM_SL4", 5, 27,
		 2, "FEM_SL5", 6, 27,
		 2, "FEM_SL6", 7, 27,
		 2, "FEM_SL7", 8, 27,
		 2, "FEM_SL8", 9, 27,
	},

	// MENU_PAGE_SAVE_OVERWRITE_CONFIRM = 27
	{ "FET_SG", 26, 26, 26, 0, 0,
		1, "FESZ_QO", 0,  0,
		2, "FEM_YES", 0, 43,
		2, "FEM_NO",  0, 26,
	},

	// MENU_PAGE_MULTIPLAYER_MAP = 28
	{ "FET_MAP", -1, -1, -1, 0, 0,

	},

	// MENU_PAGE_MULTIPLAYER_CONNECTION = 29
	{ "FET_CON", -1, -1, -1, 0, 0,

	},
	
	// MENU_PAGE_MULTIPLAYER_FIND_GAME = 30
	{ "FET_FG", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_MULTIPLAYER_MODE = 31
	{ "FET_GT", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_MULTIPLAYER_CREATE = 32
	{ "FET_HG", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_MULTIPLAYER_START = 33
	{ "FEN_STA", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_SKIN_SELECT_OLD = 34
	{ "FET_PS", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_CONTROLLER_PC = 35
	{ "FET_CTL", 41, 41, 41, 0, 0,
		99, "FET_CME", 0, 35,
		72, "FET_RDK", 0, 55,
		 2, "FET_AMS", 0, 56,
		98, "FET_DEF", 0, 35,
		 2, "FEDS_TB", 0,  0,
	},
	
	// MENU_PAGE_CONTROLLER_PC_OLD1 = 36
	{ "FET_CTL", 35, 35, 35, 0, 0,
	
	},
	
	// MENU_PAGE_CONTROLLER_PC_OLD2 = 37
	{ "FET_CTL", -1, -1, -1, 0, 0,
	
	},
	
	 // MENU_PAGE_CONTROLLER_PC_OLD3 = 38
	{ "FET_CTL", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_CONTROLLER_PC_OLD4 = 39
	{ "FET_CTL", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_CONTROLLER_DEBUG = 40
	{ "FEC_DBG", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_OPTIONS = 41
	{ "FET_OPT", 0, 0, 0, 1, 4,
		   2, "FET_CTL", 0, 35,
		 101, "FET_AUD", 0,  5,
		   2, "FET_DIS", 0,   6,
		   2, "FET_LAN", 0,   7,
		  97, "FET_PSU", 0,  54,
		   2, "FEDS_TB", 0,   0,
	},
	
	// MENU_PAGE_EXIT = 42
	{ "FET_QG", 0, 0, 0, 2, 5,
		1,  "FEQ_SRE", 0, 0,
		93, "FEM_NO",  0, 0,
		82, "FEM_YES", 0, 0,	
	},
	
	// MENU_PAGE_SAVING_IN_PROGRESS = 43
	{ "", 26, 26, 26, 0, 0,
		1, "FES_WAR", 0, 0,
	},
	
	// MENU_PAGE_SAVE_SUCCESSFUL = 44
	{ "FET_SG", 26, 26, 26, 0, 0,
		 1, "FES_SSC", 36,  0,
		49, "FEC_OKK",  0, 26,
	},
	
	// MENU_PAGE_DELETING = 45
	{ "FET_DG", 9, 9, 9, 0, 0,
		1, "FED_DLW",  0, 0,
	},
	
	// MENU_PAGE_DELETE_SUCCESS = 46
	{ "FET_DG", 9, 9, 9, 0, 0,
		 1, "DEL_FNM", 0,  0,
		 2, "FEC_OKK", 0,  9,
	},
	
	// MENU_PAGE_SAVE_FAILED = 47
	{ "FET_SG", 26, 26, 26, 0, 0,
		 1, "FEC_SVU", 0,  0,
		 2, "FEC_OKK", 0,  26,
	},
	
	// MENU_PAGE_LOAD_FAILED = 48
	{ "FET_SG", 26, 26, 26, 0, 0,
		 1, "FEC_SVU", 0,  0,
	},
	
	// MENU_PAGE_LOAD_FAILED_2 = 49
	{ "FET_LG", 26, 26, 26, 0, 0,
		 1, "FEC_LUN", 0,  0,
		 2, "FEDS_TB", 0,  8,
	},
	
	// MENU_PAGE_FILTER_GAME = 50
	{ "FIL_FLT", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_START_MENU = 51
	{ "FEM_MM", -1, -1, -1, 0, 0,
		  2, "FEN_STA", 0,  2,
		  2, "FET_OPT", 0, 41,
		  2, "FEM_QT",  0, 42
	},
	
	// MENU_PAGE_PAUSE_MENU = 52
	{ "FET_PAU", -1, -1, -1, 0, 0,
		92, "FEM_RES", 0, 0,
		 2, "FEN_STA", 0, 2,
		 2, "FEP_STA", 0, 1,
		 2, "FEP_BRI", 0, 3,
		 2, "FET_OPT", 0, 41,
		 2, "FEM_QT",  0, 42,
	},
	
	// MENU_PAGE_CHOOSE_MODE = 53
	{ "FEN_STA", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_SKIN_SELECT = 54
	{ "FET_PSU", 41, 41, 41, 4, 4,
		 35, "FEDS_TB", 0, 21,
	},
	
	// MENU_PAGE_KEYBOARD_CONTROLS = 55
	{ "FET_STI", 35, 35, 35, 1, 1,
		 35, "FEDS_TB", 0, 35,
	},
	
	// MENU_PAGE_MOUSE_CONTROLS = 56
	{ "FET_MTI", 35, 35, 35, 2, 2,
		 84, "FEC_MSH",  0, 35,
		 81, "FEC_IVV",  0, 35,
		102, "FET_MST",  0, 35,
		 2 , "FEDS_TB",  0,  0,
	},
	
	// MENU_PAGE_57 = 57
	{ "", -1, -1, -1, 0, 0,
	
	},
	
	// MENU_PAGE_58 = 58
	{ "", -1, -1, -1, 0, 0,
	
	},
};

char *FrontendFilenames[] = {
	"fe2_mainpanel_ul",
	"fe2_mainpanel_ur",
	"fe2_mainpanel_dl",
	"fe2_mainpanel_dr",
	"fe2_mainpanel_dr2",
	"fe2_tabactive",
	"fe_iconbrief",
	"fe_iconstats",
	"fe_iconcontrols",
	"fe_iconsave",
	"fe_iconaudio",
	"fe_icondisplay",
	"fe_iconlanguage",
	"fe_controller",
	"fe_controllersh",
	"fe_arrows1",
	"fe_arrows2",
	"fe_arrows3",
	"fe_arrows4",
	"fe_radio1", // HEAD_RADIO
	"fe_radio2", // DOUBLE_CLEF
	"fe_radio5", // JAH_RADIO
	"fe_radio7", // RISE_FM
	"fe_radio8", // LIPS_106
	"fe_radio3", // GAME_FM
	"fe_radio4", // MSX_FM
	"fe_radio6", // FLASHBACK
	"fe_radio9", // CHATTERBOX
};					

char *MenuFilenames[] = {
	"connection24",	"",
	"findgame24",	"",
	"hostgame24",	"",
	"mainmenu24",	"",
	"Playersetup24",	"",
	"singleplayer24",	"",
	"multiplayer24",	"",
	"dmalogo128",	"dmalogo128m",
	"gtaLogo128",	"gtaLogo128",
	"rockstarLogo128",	"rockstarlogo128m",
	"gamespy256",	"gamespy256a",
	"mouse",	"mousetimera",
	"mousetimer",	"mousetimera",
	"mp3logo",	"mp3logoA",
	"downOFF",	"buttonA",
	"downON",	"buttonA",
	"upOFF",	"buttonA",
	"upON",	"buttonA",
	"gta3logo256",	"gta3logo256m",
	nil, nil
};

#if 1
WRAPPER void CMenuManager::BuildStatLine(char *, void *, uint16, void *) { EAXJMP(0x483870); }
#else
void CMenuManager::BuildStatLine(char *, void *, uint16, void *)
{

}
#endif

#if 0
WRAPPER void CMenuManager::CentreMousePointer() { EAXJMP(0x48ACE0); }
#else
void CMenuManager::CentreMousePointer()
{
	tagPOINT Point;

	if (SCREENW * 0.5f == 0.0f && 0.0f == SCREENH * 0.5f) {
		Point.x = SCREEN_WIDTH / 2;
		Point.y = SCREEN_HEIGHT / 2;
		ClientToScreen(PSGLOBAL(window), &Point);
		SetCursorPos(Point.x, Point.y);

		PSGLOBAL(lastMousePos.x) = SCREEN_WIDTH / 2;
		PSGLOBAL(lastMousePos.y) = SCREEN_HEIGHT / 2;
	}
}
#endif

#if 1
WRAPPER void CMenuManager::CheckCodesForControls(int, int) { EAXJMP(0x48A950); }
#else
void CMenuManager::CheckCodesForControls()
{

}
#endif

#if 0
WRAPPER bool CMenuManager::CheckHover(int, int, int, int) { EAXJMP(0x48ACA0); }
#else
bool CMenuManager::CheckHover(int x1, int x2, int y1, int y2)
{
	return m_nMousePosX > x1 && m_nMousePosX < x2 &&
	       m_nMousePosY > y1 && m_nMousePosY < y2;
}
#endif

#if 1
WRAPPER int CMenuManager::CostructStatLine(int) { EAXJMP(0x482800); }
#else
int CMenuManager::CostructStatLine(int)
{

}
#endif

#if 0
WRAPPER void CMenuManager::DisplayHelperText() { EAXJMP(0x48B490); }
#else
void CMenuManager::DisplayHelperText()
{
	wchar *str = nil;
	switch (m_nHelperTextMsgId) {
	case 0:
		str = TheText.Get("FET_MIG");
		break;
	case 1:
		str = TheText.Get("FET_APP");
		break;
	case 2:
		str = TheText.Get("FET_HRD");
		break;
	case 3:
		str = TheText.Get("FET_RSO");
		break;
	case 4:
		str = TheText.Get("FET_RSC");
		break;
	default:
		break;
	};

	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetScale(SCREEN_SCALE_X(0.4f), SCREEN_SCALE_Y(0.6f));
	CFont::SetFontStyle(FONT_HEADING);
	CFont::SetDropColor(CRGBA(0, 0, 0, DROP_COLOR_A));
	CFont::SetDropShadowPosition(DROP_COLOR_SIZE);

	CFont::SetColor(CRGBA(255, 255, 255, 255));
	CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_SCALE_FROM_BOTTOM(120.0f), str);
}
#endif

#if 0
WRAPPER float CMenuManager::DisplaySlider(float, float, float, float, float, float) { EAXJMP(0x488420); }
#else
float CMenuManager::DisplaySlider(float x, float y, float leftSize, float rightSize, float rectSize, float progress) 
{
	CRGBA color;
	float sizeRange;

	float input = 0.0f;
	for (int i = 0; i < 16; i++) {
		input = i * rectSize/16.0f + x;

		if (i/16.0f + 1/32.0f < progress)
			color = CRGBA(255, 217, 106, FadeIn(255));
		else
			color = CRGBA(185, 120, 0, FadeIn(255));

		sizeRange = max(leftSize, rightSize);

		float _x = i * rectSize/16.0f + x;
		float _y = y + sizeRange - ((16 - i) * leftSize + i * rightSize)/16.0f;
		float _w = SCREEN_SCALE_X(10.0f) + i * rectSize/16.0f + x;
		float _h = y + sizeRange;
		float _s = SCREEN_SCALE_X(2.0f);
		CSprite2d::DrawRect(CRect(_x + _s, _y + _s, _w + _s, _h + _s), CRGBA(0, 0, 0, FadeIn(255))); // Shadow
		CSprite2d::DrawRect(CRect(i * rectSize/16.0f + x, y + sizeRange - ((16 - i) * leftSize + i * rightSize)/16.0f, SCREEN_SCALE_X(10.0f) + i * rectSize/16.0f + x, y + sizeRange), color);
	};
	return input;
}
#endif

#if 1
WRAPPER void CMenuManager::DoSettingsBeforeStartingAGame() { EAXJMP(0x48AB40); }
#else
WRAPPER void CMenuManager::DoSettingsBeforeStartingAGame()
{

}
#endif

#if 0
WRAPPER void CMenuManager::Draw() { EAXJMP(0x47AE00); }
#else
void CMenuManager::Draw()
{
	CFont::SetBackgroundOff();
	CFont::SetPropOn();
	CFont::SetCentreOff();
	CFont::SetJustifyOn();
	CFont::SetBackGroundOnlyTextOn();
	CFont::SetWrapx(SCREEN_SCALE_FROM_RIGHT(40.0f));
	CFont::SetRightJustifyWrap(0.0f);
	CFont::SetDropColor(CRGBA(0, 0, 0, FadeIn(DROP_COLOR_A)));

	switch (m_nCurrScreen) {
	case MENU_STATS:
		PrintStats();
		break;
	case MENU_BRIEFS:
		PrintBriefs();
		break;
	case MENU_CONTROLLER_DEBUG:
		DrawControllerScreenExtraText(0, 350, 20);
		break;
	}

	// Header.
	if (aScreens[m_nCurrScreen].m_ScreenName[0]) {
		CFont::SetDropShadowPosition(0);
		CFont::SetColor(CRGBA(0, 0, 0, FadeIn(255)));
		CFont::SetRightJustifyOn();
		CFont::SetFontStyle(FONT_HEADING);
		CFont::SetScale(SCREEN_SCALE_X(HEADER_WIDTH), SCREEN_SCALE_Y(HEADER_HEIGHT));
		CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(HEADER_POS_X), SCREEN_SCALE_FROM_BOTTOM(HEADER_POS_Y), TheText.Get(aScreens[m_nCurrScreen].m_ScreenName));
	}

	// Action text.
	wchar *str;
	if (aScreens[m_nCurrScreen].m_aEntries[0].m_Action == 1) {
		switch (m_nCurrScreen) {
		case MENU_LOAD_SLOT_CONFIRM:
			if (m_bGameNotLoaded)
				str = TheText.Get("FES_LCG");
			else
				str = TheText.Get(aScreens[m_nCurrScreen].m_aEntries[0].m_EntryName);
			break;
		case MENU_SAVE_OVERWRITE_CONFIRM:
			if (Slots[m_nCurrSaveSlot] == 1)
				str = TheText.Get("FESZ_QZ");
			else
				str = TheText.Get(aScreens[m_nCurrScreen].m_aEntries[0].m_EntryName);
			break;
		case MENU_EXIT:
			if (m_bGameNotLoaded)
				str = TheText.Get("FEQ_SRW");
			else
				str = TheText.Get(aScreens[m_nCurrScreen].m_aEntries[0].m_EntryName);
			break;
		default:
			str = TheText.Get(aScreens[m_nCurrScreen].m_aEntries[0].m_EntryName);
			break;
		};

		CFont::SetDropShadowPosition(DROP_COLOR_SIZE);
		CFont::SetDropColor(CRGBA(0, 0, 0, FadeIn(DROP_COLOR_A)));
		CFont::SetFontStyle(FONT_BANK);
		CFont::SetScale(SCREEN_SCALE_X(ACTION_WIDTH), SCREEN_SCALE_Y(ACTION_HEIGHT));
		CFont::SetAlignment(ALIGN_LEFT);
		CFont::SetColor(CRGBA(235, 170, 50, FadeIn(255)));
		CFont::PrintString(SCREEN_SCALE_X(ACTION_POS_X), SCREEN_SCALE_Y(ACTION_POS_Y), str);
	}

	for (int i = 0; i < 18; ++i) {
		if (aScreens[m_nCurrScreen].m_aEntries[i].m_Action != MENUACTION_LABEL && aScreens[m_nCurrScreen].m_aEntries[i].m_EntryName[0]) {
			wchar *columnToPrint[COLUMNS] = { nil, nil };

			if (aScreens[m_nCurrScreen].m_aEntries[i].m_ActionSlot >= MENU_ACTION_SAVE_1 && aScreens[m_nCurrScreen].m_aEntries[i].m_ActionSlot <= MENU_ACTION_SAVE_8) {
				columnToPrint[L] = GetNameOfSavedGame(i - 1);
				columnToPrint[R] = GetSavedGameDateAndTime(i - 1);

				if (!columnToPrint[L][0]) {
					sprintf(gString, "FEM_SL%d", i);
					columnToPrint[L] = TheText.Get(gString);
				}
			}
			else {
				columnToPrint[L] = TheText.Get(aScreens[m_nCurrScreen].m_aEntries[i].m_EntryName);
			}

			switch (aScreens[m_nCurrScreen].m_aEntries[i].m_Action) {
			case MENUACTION_CTRLVIBRATION:
				break;
			case MENUACTION_CTRLCONFIG:
				switch (CPad::GetPad(0)->Mode) {
				case 0:
					columnToPrint[R] = TheText.Get("FEC_CF1");
					break;
				case 1:
					columnToPrint[R] = TheText.Get("FEC_CF2");
					break;
				case 2:
					columnToPrint[R] = TheText.Get("FEC_CF3");
					break;
				case 3:
					columnToPrint[R] = TheText.Get("FEC_CF4");
					break;
				};
				break;
			case MENUACTION_CTRLDISPLAY:
				break;
			case MENUACTION_FRAMESYNC:
				columnToPrint[R] = TheText.Get(m_PrefsVsyncDisp ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_FRAMELIMIT:
				columnToPrint[R] = TheText.Get(m_PrefsFrameLimiter ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_TRAILS:
				columnToPrint[R] = TheText.Get(BlurOn ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_SUBTITLES:
				columnToPrint[R] = TheText.Get(m_PrefsShowSubtitles ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_WIDESCREEN:
				columnToPrint[R] = TheText.Get(m_PrefsUseWideScreen ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_RADIO:
				sprintf(gString, "FEA_FM%d", m_PrefsRadioStation);
				columnToPrint[R] = TheText.Get(gString);
				break;
			case MENUACTION_SETDBGFLAG:
				columnToPrint[R] = TheText.Get(CTheScripts::DbgFlag ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_SWITCHBIGWHITEDEBUGLIGHT:
				columnToPrint[R] = TheText.Get(CTheScripts::DbgFlag ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_INVVERT:
				columnToPrint[R] = TheText.Get(MousePointerStateHelper.bInvertVertically ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_SCREENRES:
			{
				char *res = _psGetVideoModeList()[m_nDisplayVideoMode];

				if (!res)
					res = "";

				AsciiToUnicode(res, gUString);
				columnToPrint[R] = gUString;
			}
			break;
			case MENUACTION_AUDIOHW:
				if (FrontEndMenuManager.m_nPrefsAudio3DProviderIndex == -1)
					columnToPrint[R] = TheText.Get("FEA_NAH");
				else {
					char *provider = MusicManager.Get3DProviderName(FrontEndMenuManager.m_nPrefsAudio3DProviderIndex);
					AsciiToUnicode(provider, gUString);
					columnToPrint[R] = gUString;
				}
				break;
			case MENUACTION_SPEAKERCONF:
				if (FrontEndMenuManager.m_nPrefsAudio3DProviderIndex == -1)
					columnToPrint[R] = TheText.Get("FEA_NAH");
				else {
					switch (m_PrefsSpeakers) {
					case 0:
						columnToPrint[R] = TheText.Get("FEA_2SP");
						break;
					case 1:
						columnToPrint[R] = TheText.Get("FEA_EAR");
						break;
					case 2:
						columnToPrint[R] = TheText.Get("FEA_4SP");
						break;
					};
				}
				break;
			case MENUACTION_CTRLMETHOD:
				switch (m_ControlMethod) {
				case 0:
					columnToPrint[L] = TheText.Get("FET_SCN");
					break;
				case 1:
					columnToPrint[L] = TheText.Get("FET_CCN");
					break;
				};
				break;
			case MENUACTION_DYNAMICACOUSTIC:
				columnToPrint[R] = TheText.Get(m_PrefsDMA ? "FEM_ON" : "FEM_OFF");
				break;
			case MENUACTION_MOUSESTEER:
				columnToPrint[R] = TheText.Get(m_bDisableMouseSteering ? "FEM_ON" : "FEM_OFF");
				break;
			};

			CFont::SetDropShadowPosition(DROP_COLOR_SIZE);
			CFont::SetDropColor(CRGBA(0, 0, 0, FadeIn(DROP_COLOR_A)));
			CFont::SetCentreSize(SCREEN_WIDTH);
			CFont::SetWrapx(SCREEN_WIDTH);
			CFont::SetRightJustifyWrap(-SCREEN_WIDTH);

			// Set alignment.
			CVector2D vecPositions = { 0.0f, 0.0f };
			float fVerticalSpacing;
			float fBarSize;

			int SavePageSlot =
				m_nCurrScreen == MENU_CHOOSE_LOAD_SLOT ||
				m_nCurrScreen == MENU_CHOOSE_DELETE_SLOT ||
				m_nCurrScreen == MENU_CHOOSE_SAVE_SLOT;

			if (SavePageSlot) {
				CFont::SetFontStyle(FONT_BANK);
				CFont::SetAlignment(ALIGN_LEFT);
				CFont::SetScale(SCREEN_SCALE_X(0.45f), SCREEN_SCALE_Y(0.7f));
				fVerticalSpacing = COLUMN_SPACING_MIN;
				fBarSize = SELECT_BOX_MIN;

				vecPositions.x = SCREEN_SCALE_X(COLUMN_SAVE_X);
				vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_SAVE_Y);
			}
			else {
				CFont::SetFontStyle(FONT_HEADING);

				int LeftColumn =
					m_nCurrScreen == MENU_SOUND_SETTINGS ||
					m_nCurrScreen == MENU_GRAPHICS_SETTINGS ||
					m_nCurrScreen == MENU_MOUSE_CONTROLS;

				if (LeftColumn) {
					CFont::SetAlignment(ALIGN_LEFT);
					CFont::SetScale(SCREEN_SCALE_X(0.55f), SCREEN_SCALE_Y(0.8f));
					fVerticalSpacing = COLUMN_SPACING_MIN;
					fBarSize = SELECT_BOX_MIN;
				}
				else {
					CFont::SetAlignment(ALIGN_CENTER);
					CFont::SetScale(SCREEN_SCALE_X(0.75f), SCREEN_SCALE_Y(0.9f));
					fVerticalSpacing = COLUMN_SPACING_MAX;
					fBarSize = SELECT_BOX_MAX;
				}

				// Set positions.
				if (CFont::GetDetails().centre)
					vecPositions.x = SCREEN_WIDTH / 2;
				else
					vecPositions.x = SCREEN_SCALE_X(COLUMN_POS_X);

				switch (m_nCurrScreen) {
				case MENU_BRIEFS:
				case MENU_STATS:
					vecPositions.y = SCREEN_SCALE_FROM_BOTTOM(COLUMN_FEDS);
					break;
				case MENU_SOUND_SETTINGS:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_MAX_Y);

					if (i > 5)
						vecPositions.y += SCREEN_SCALE_Y(FE_RADIO_ICON_H * 1.16f);
					break;
				case MENU_LANGUAGE_SETTINGS:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_MIN_Y);
					break;
				case MENU_GRAPHICS_SETTINGS:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_MAX_Y);
					break;
				case MENU_OPTIONS:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_MID_Y);
					break;
				case MENU_PAUSE_MENU:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_PAUSE_Y);
					break;
				case MENU_NEW_GAME:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_MID_Y);
					break;
				case MENU_START_MENU:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_START_Y);
					break;
				default:
					vecPositions.y = (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(COLUMN_MID_Y);
					break;
				};
			}

			if (i > 0)
				vecPositions.y += SCREEN_SCALE_Y(fVerticalSpacing * i);

			// Set color and draw selection bar.
			if (i == m_nCurrOption && m_nMenuFadeAlpha >= 255) {
				CFont::SetColor(CRGBA(255, 217, 106, FadeIn(255)));
				CSprite2d::DrawRect(CRect(SCREEN_STRETCH_X(11.0f), vecPositions.y - SCREEN_STRETCH_Y(fBarSize * 0.13f), SCREEN_STRETCH_FROM_RIGHT(11.0f), vecPositions.y + SCREEN_STRETCH_Y(fBarSize)), CRGBA(100, 200, 50, 50));
			}
			else
				CFont::SetColor(CRGBA(235, 170, 50, FadeIn(255)));

			// Draw
			if (columnToPrint[L])
				CFont::PrintString(vecPositions.x, vecPositions.y, columnToPrint[L]);

			if (columnToPrint[R]) {
				CFont::SetAlignment(ALIGN_RIGHT);
				CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(SavePageSlot ? COLUMN_SAVE_X : COLUMN_POS_X), vecPositions.y, columnToPrint[R]);
			}

			// Mouse support.
			bool bIsMouseInPosition = false;
			if (m_nMenuFadeAlpha >= 255) {
				CVector2D vecInputSize = { SCREEN_SCALE_X(20.0f), SCREEN_SCALE_FROM_RIGHT(20.0f) };
				if (m_bShowMouse &&
					((CheckHover(vecInputSize.x, vecInputSize.y, vecPositions.y, vecPositions.y + SCREEN_STRETCH_Y(20.0f)))))
					bIsMouseInPosition = true;
				else
					bIsMouseInPosition = false;

				if (bIsMouseInPosition) {
					if (m_nCurrOption != i) {
						m_nCurrOption = i;
						DMAudio.PlayFrontEndSound(SOUND_FRONTEND_MENU_DENIED, 0);
					}

					m_nCurrentInput = m_nCurrOption;

					if (CPad::GetPad(0)->NewMouseControllerState.LMB && !CPad::GetPad(0)->OldMouseControllerState.LMB)
						m_nHoverOption = IGNORE_OPTION;
					else
						m_nHoverOption = ACTIVATE_OPTION;
				}
			}

			// Sliders 
			// TODO: CheckHover
			switch (aScreens[m_nCurrScreen].m_aEntries[i].m_Action) {
			case MENUACTION_BRIGHTNESS:
				DisplaySlider(SCREEN_SCALE_FROM_RIGHT(SLIDER_X), vecPositions.y - SCREEN_SCALE_Y(3.0f), SCREEN_SCALE_Y(2.0f), SCREEN_SCALE_Y(18.0f), SCREEN_SCALE_X(256.0f), m_PrefsBrightness/512.0f);
				break;
			case MENUACTION_DRAWDIST:
				DisplaySlider(SCREEN_SCALE_FROM_RIGHT(SLIDER_X), vecPositions.y - SCREEN_SCALE_Y(3.0f), SCREEN_SCALE_Y(2.0f), SCREEN_SCALE_Y(18.0f), SCREEN_SCALE_X(256.0f), (m_PrefsLOD - 0.8f) * 1.0f);
				break;
			case MENUACTION_MUSICVOLUME:
				DisplaySlider(SCREEN_SCALE_FROM_RIGHT(SLIDER_X), vecPositions.y - SCREEN_SCALE_Y(3.0f), SCREEN_SCALE_Y(2.0f), SCREEN_SCALE_Y(18.0f), SCREEN_SCALE_X(256.0f), m_PrefsMusicVolume/128.0f);
				break;
			case MENUACTION_SFXVOLUME:
				DisplaySlider(SCREEN_SCALE_FROM_RIGHT(SLIDER_X), vecPositions.y - SCREEN_SCALE_Y(3.0f), SCREEN_SCALE_Y(2.0f), SCREEN_SCALE_Y(18.0f), SCREEN_SCALE_X(256.0f), m_PrefsSfxVolume/128.0f);
				break;
			case MENUACTION_MOUSESENS:
				DisplaySlider(SCREEN_SCALE_FROM_RIGHT(SLIDER_X), vecPositions.y - SCREEN_SCALE_Y(3.0f), SCREEN_SCALE_Y(2.0f), SCREEN_SCALE_Y(18.0f), SCREEN_SCALE_X(256.0f), TheCamera.m_fMouseAccelHorzntl * 200.0f);
				break;
			};

			// Radio icons.
			float fIconSpacing = 59.52f;
			if (m_nCurrScreen == MENU_SOUND_SETTINGS) {
				for (int i = 0; i < POLICE_RADIO; i++) {

					if (i == MSX_FM)
						fIconSpacing -= 1.5f;

					if (i < USERTRACK)
						m_aFrontEndSprites[i + FE_RADIO1].Draw(SCREEN_STRETCH_X(FE_RADIO_ICON_X + fIconSpacing * i), (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(FE_RADIO_ICON_Y), SCREEN_SCALE_X(FE_RADIO_ICON_W), SCREEN_SCALE_Y(FE_RADIO_ICON_H), i == m_PrefsRadioStation ? CRGBA(255, 255, 255, 255) : CRGBA(225, 0, 0, 170));
					if (i > CHATTERBOX)
						m_aMenuSprites[MENU_MP3LOGO].Draw(SCREEN_STRETCH_X(FE_RADIO_ICON_X + fIconSpacing * i), (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(FE_RADIO_ICON_Y), SCREEN_SCALE_X(FE_RADIO_ICON_W), SCREEN_SCALE_Y(FE_RADIO_ICON_H), i == m_PrefsRadioStation ? CRGBA(255, 255, 255, 255) : CRGBA(225, 0, 0, DMAudio.IsMP3RadioChannelAvailable() ? 170 : 25));
				}
			}

			// Helpers
			if (!strcmp(aScreens[m_nCurrScreen].m_aEntries[m_nCurrOption].m_EntryName, "FED_RES")) {
				if (m_nDisplayVideoMode == m_nPrefsVideoMode) {
					if (m_nHelperTextMsgId == 1)
						ResetHelperText();
				}
				else
					SetHelperText(1);
			}
			else {
				if (m_nDisplayVideoMode != m_nPrefsVideoMode) {
					m_nDisplayVideoMode = m_nPrefsVideoMode;
					SetHelperText(3);
				}
			}

			switch (m_nCurrScreen) {
			case MENU_CONTROLLER_SETTINGS:
			case MENU_SOUND_SETTINGS:
			case MENU_GRAPHICS_SETTINGS:
			case MENU_SKIN_SELECT:
			case MENU_CONTROLLER_PC:
			case MENU_MOUSE_CONTROLS:
				DisplayHelperText();
				break;
			};
		}
	};
}
#endif

#if 1
WRAPPER void CMenuManager::DrawControllerBound(int, int, int, uint8) { EAXJMP(0x489710); }
#else
void CMenuManager::DrawControllerBound(int, int, int, uint8)
{ 

}
#endif

#if 1
WRAPPER void CMenuManager::DrawControllerScreenExtraText(int, int, int) { EAXJMP(0x4892F0); }
#else
void CMenuManager::DrawControllerScreenExtraText(int, int, int)
{

}
#endif

#if 1
WRAPPER void CMenuManager::DrawControllerSetupScreen() { EAXJMP(0x481210); }
#else
void CMenuManager::DrawControllerSetupScreen()
{

}
#endif

#if 0
WRAPPER void CMenuManager::DrawFrontEnd(void) { EAXJMP(0x47A540); }
#else
void CMenuManager::DrawFrontEnd()
{
	CFont::SetAlphaFade(255.0f);

	if (m_nCurrScreen == MENU_NONE) {
		if (m_bGameNotLoaded)
			m_nCurrScreen = MENU_START_MENU;
		else
			m_nCurrScreen = MENU_PAUSE_MENU;
	}

	if (!m_nCurrOption && aScreens[m_nCurrScreen].m_aEntries[0].m_Action == MENUACTION_LABEL)
		m_nCurrOption = 1;

	CMenuManager::DrawFrontEndNormal();
	CMenuManager::PrintErrorMessage();
}
#endif

#if 0
WRAPPER void CMenuManager::DrawFrontEndNormal(void) { EAXJMP(0x47A5B0); }
#else
void CMenuManager::DrawFrontEndNormal()
{
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSCLAMP);

	CSprite2d::InitPerFrame();
	CFont::InitPerFrame();

	eMenuSprites currentSprite = MENU_MAINMENU;
	switch (m_nPrevScreen) {
	case MENU_STATS:
	case MENU_START_MENU:
	case MENU_PAUSE_MENU:
		currentSprite = MENU_MAINMENU;
		break;
	case MENU_NEW_GAME:
	case MENU_CHOOSE_LOAD_SLOT:
	case MENU_CHOOSE_DELETE_SLOT:
	case MENU_NEW_GAME_RELOAD:
	case MENU_LOAD_SLOT_CONFIRM:
	case MENU_DELETE_SLOT_CONFIRM:
	case MENU_EXIT:
		currentSprite = MENU_SINGLEPLAYER;
		break;
	case MENU_MULTIPLAYER_MAIN:
		currentSprite = MENU_MULTIPLAYER;
		break;
	case MENU_MULTIPLAYER_MAP:
	case MENU_MULTIPLAYER_FIND_GAME:
	case MENU_SKIN_SELECT:
	case MENU_KEYBOARD_CONTROLS:
	case MENU_MOUSE_CONTROLS:
		currentSprite = MENU_FINDGAME;
		break;
	case MENU_MULTIPLAYER_CONNECTION:
	case MENU_MULTIPLAYER_MODE:
		currentSprite = MENU_CONNECTION;
		break;
	case MENU_MULTIPLAYER_CREATE:
		currentSprite = MENU_HOSTGAME;
		break;
	case MENU_SKIN_SELECT_OLD:
	case MENU_OPTIONS:
		currentSprite = MENU_PLAYERSET;
		break;
	};

	//CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREENW, SCREENH), CRGBA(0, 0, 0, 255));

	uint32 savedShade;
	uint32 savedAlpha;
	RwRenderStateGet(rwRENDERSTATESHADEMODE, &savedShade);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(rwSHADEMODEGOURAUD));
	RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
	if (m_nMenuFadeAlpha >= 255)
		m_aMenuSprites[currentSprite].Draw(CRect(0.0f, 0.0f, SCREENW, SCREENH), CRGBA(255, 255, 255, 255));
	else {
		if (m_nMenuFadeAlpha != 255)
			m_nMenuFadeAlpha += 0.1f * 255.0f;

		m_aMenuSprites[currentSprite].Draw(CRect(0.0f, 0.0f, SCREENW, SCREENH), CRGBA(255, 255, 255, m_nMenuFadeAlpha));
	}

	// GTA LOGO
	if (m_nCurrScreen == MENU_START_MENU || m_nCurrScreen == MENU_PAUSE_MENU) {
		if (CGame::frenchGame || CGame::germanGame || !CGame::nastyGame)
			m_aMenuSprites[MENU_GTA3LOGO].Draw(CRect((SCREEN_WIDTH / 2) - SCREEN_SCALE_X(115.0f), SCREEN_SCALE_Y(70.0f), (SCREEN_WIDTH / 2) + SCREEN_SCALE_X(115.0f), SCREEN_SCALE_Y(180.0f)), CRGBA(255, 255, 255, FadeIn(255)));
		else
			m_aMenuSprites[MENU_GTALOGO].Draw(CRect((SCREEN_WIDTH / 2) - SCREEN_SCALE_X(95.0f), SCREEN_SCALE_Y(40.0f), (SCREEN_WIDTH / 2) + SCREEN_SCALE_X(95.0f), SCREEN_SCALE_Y(210.0f)), CRGBA(255, 255, 255, FadeIn(255)));
	}
	RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void *>(savedShade));
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));

	switch (m_nCurrScreen) {
	case MENU_SKIN_SELECT:
		CMenuManager::DrawPlayerSetupScreen();
		break;
	case MENU_KEYBOARD_CONTROLS:
		CMenuManager::DrawControllerSetupScreen();
		break;
	default:
		CMenuManager::Draw();
		break;
	};

	CFont::DrawFonts();

	// Draw mouse
	if (m_bShowMouse)
		m_aMenuSprites[MENU_MOUSE].Draw(m_nMousePosX, m_nMousePosY, SCREEN_SCALE_X(60.0f), SCREEN_SCALE_Y(60.0f), CRGBA(255, 255, 255, 255));
}
#endif

#if 1
WRAPPER void CMenuManager::DrawPlayerSetupScreen() { EAXJMP(0x47F2B0); }
#else
void CMenuManager::DrawPlayerSetupScreen()
{

}
#endif

#if 0
WRAPPER int CMenuManager::FadeIn(int alpha) { EAXJMP(0x48AC60); }
#else
int CMenuManager::FadeIn(int alpha)
{
	if (m_nCurrScreen == MENU_LOADING_IN_PROGRESS ||
		m_nCurrScreen == MENU_SAVING_IN_PROGRESS ||
		m_nCurrScreen == MENU_DELETING)
		return alpha;

	if (m_nMenuFadeAlpha >= alpha)
		return alpha;

	return m_nMenuFadeAlpha;
}
#endif

#if 1
WRAPPER void CMenuManager::FilterOutColorMarkersFromString(uint16, CRGBA &) { EAXJMP(0x4889C0); }
#else
void CMenuManager::FilterOutColorMarkersFromString(uint16, CRGBA &)
{

}
#endif

#if 1
WRAPPER int CMenuManager::GetStartOptionsCntrlConfigScreens() { EAXJMP(0x489270); }
#else
int CMenuManager::GetStartOptionsCntrlConfigScreens()
{

}
#endif

#if 1
WRAPPER void CMenuManager::InitialiseChangedLanguageSettings() { EAXJMP(0x47A4D0); }
#else
void CMenuManager::InitialiseChangedLanguageSettings()
{

}
#endif

#if 0
WRAPPER void CMenuManager::LoadAllTextures() { EAXJMP(0x47A230); }
#else
void CMenuManager::LoadAllTextures()
{
	if (!m_bSpritesLoaded) {
		CMenuManager::CentreMousePointer();
		DMAudio.ChangeMusicMode(0);
		DMAudio.PlayFrontEndSound(SOUND_FRONTEND_MENU_STARTING, 0);
		m_nCurrOption = 0;
		m_PrefsRadioStation = DMAudio.GetRadioInCar();

		if (DMAudio.IsMP3RadioChannelAvailable()) {
			if (CMenuManager::m_PrefsRadioStation > USERTRACK)
				CMenuManager::m_PrefsRadioStation = CGeneral::GetRandomNumber() % 10;
		}
		else if (CMenuManager::m_PrefsRadioStation > CHATTERBOX)
			CMenuManager::m_PrefsRadioStation = CGeneral::GetRandomNumber() % 9;
	
		CFileMgr::SetDir("");
		CTimer::Stop();
		CStreaming::MakeSpaceFor(716800);
		CStreaming::ImGonnaUseStreamingMemory();
		CTxdStore::PushCurrentTxd();

		int frontend = CTxdStore::AddTxdSlot("frontend");
		CTxdStore::LoadTxd(frontend, "MODELS/FRONTEND.TXD");
		CTxdStore::AddRef(frontend);
		CTxdStore::SetCurrentTxd(frontend);
		CStreaming::IHaveUsedStreamingMemory();
		CTimer::Update();

		debug("LOAD frontend\n");
		for (int i = 0; i < ARRAY_SIZE(FrontendFilenames); i++) {
			m_aFrontEndSprites[i].SetTexture(FrontendFilenames[i]);
			m_aFrontEndSprites[i].SetAddressing(rwTEXTUREADDRESSBORDER);
		};

		CTxdStore::PopCurrentTxd();

		int menu = CTxdStore::AddTxdSlot("menu");
		CTxdStore::LoadTxd(menu, "MODELS/MENU.TXD");
		CTxdStore::AddRef(menu);
		CTxdStore::SetCurrentTxd(menu);

		debug("LOAD sprite\n");
		for (int i = 0; i < ARRAY_SIZE(MenuFilenames)/2; i++) {
			m_aMenuSprites[i].SetTexture(MenuFilenames[i*2], MenuFilenames[i*2+1]);
			m_aMenuSprites[i].SetAddressing(rwTEXTUREADDRESSBORDER);
		};

		CTxdStore::PopCurrentTxd();

		m_bSpritesLoaded = true;
	}
}
#endif

#if 1
WRAPPER void CMenuManager::LoadSettings() { EAXJMP(0x488EE0); }
#else
void CMenuManager::LoadSettings()
{

}
#endif

#if 1
WRAPPER void CMenuManager::MessageScreen(char *) { EAXJMP(0x48B7E0); }
#else
void CMenuManager::MessageScreen(char *)
{

}
#endif

#if 1
WRAPPER void CMenuManager::PickNewPlayerColour() { EAXJMP(0x488C40); }
#else
void CMenuManager::PickNewPlayerColour()
{

}
#endif

#if 1
WRAPPER void CMenuManager::PrintBriefs() { EAXJMP(0x484D60); }
#else
void CMenuManager::PrintBriefs()
{

}
#endif

#if 0
WRAPPER void CMenuManager::PrintErrorMessage() { EAXJMP(0x484F70); }
#else
void CMenuManager::PrintErrorMessage()
{
	if (!CPad::bDisplayNoControllerMessage && !CPad::bObsoleteControllerMessage)
		return;

	CSprite2d::DrawRect(CRect(SCREEN_SCALE_X(20.0f), SCREEN_SCALE_Y(140.0f), SCREEN_WIDTH - SCREEN_SCALE_X(20.0f), SCREEN_HEIGHT - SCREEN_SCALE_Y(140.0f)), CRGBA(64, 16, 16, 224));
	CFont::SetFontStyle(FONT_BANK);
	CFont::SetBackgroundOff();
	CFont::SetPropOn();
	CFont::SetCentreOff();
	CFont::SetJustifyOn();
	CFont::SetRightJustifyOff();
	CFont::SetBackGroundOnlyTextOn();
	CFont::SetWrapx(SCREEN_WIDTH - 40.0f);
	CFont::SetColor(CRGBA(165, 165, 165, 255));
	CFont::SetScale(SCREEN_SCALE_X(0.9f), SCREEN_SCALE_Y(0.9f));
	CFont::PrintString(SCREEN_SCALE_X(40.0f), (SCREEN_HEIGHT / 2) - SCREEN_SCALE_Y(60.0f), TheText.Get(CPad::bDisplayNoControllerMessage ? "NOCONT" : "WRCONT"));
	CFont::DrawFonts();
}
#endif

#if 1
WRAPPER void CMenuManager::PrintStats() { EAXJMP(0x482100); }
#else
void CMenuManager::PrintStats()
{

}
#endif


#if 1
WRAPPER void CMenuManager::Process(void) { EAXJMP(0x485100); }
#else
void CMenuManager::Process(void)
{

}
#endif

#if 1
WRAPPER void CMenuManager::ProcessButtonPresses() { EAXJMP(0x4856F0); }
#else
void CMenuManager::ProcessButtonPresses()
{

}
#endif

#if 1
WRAPPER void CMenuManager::ProcessOnOffMenuOptions() { EAXJMP(0x48AE60); }
#else
void CMenuManager::ProcessOnOffMenuOptions()
{

}
#endif

#if 0
WRAPPER void CMenuManager::RequestFrontEndShutdown() { EAXJMP(0x488750); }
#else
void CMenuManager::RequestFrontEndShutdown()
{
	m_bShutDownFrontEndRequested = true;
	DMAudio.ChangeMusicMode(1);
}
#endif

#if 0
WRAPPER void CMenuManager::RequestFrontEndStartUp() { EAXJMP(0x488770); }
#else
void CMenuManager::RequestFrontEndStartUp()
{
	m_bStartUpFrontEndRequested = 1;
}
#endif

#if 0
WRAPPER void CMenuManager::ResetHelperText() { EAXJMP(0x48B470); }
#else
void CMenuManager::ResetHelperText() 
{
	m_nHelperTextMsgId = 0;
	m_nHelperTextAlpha = 300;
}
#endif

#if 1
WRAPPER void CMenuManager::SaveLoadFileError_SetUpErrorScreen() { EAXJMP(0x488930); }
#else
void CMenuManager::SaveLoadFileError_SetUpErrorScreen()
{

}
#endif

#if 0
WRAPPER void CMenuManager::SetHelperText() { EAXJMP(0x48B450); }
#else
void CMenuManager::SetHelperText(int text)
{
	m_nHelperTextMsgId = text;
	m_nHelperTextAlpha = 300;
}
#endif

#if 1
WRAPPER void CMenuManager::SaveSettings() { EAXJMP(0x488CC0); }
#else
void CMenuManager::SaveSettings()
{

}
#endif

#if 0
WRAPPER void CMenuManager::ShutdownJustMenu() { EAXJMP(0x488920); }
#else
void CMenuManager::ShutdownJustMenu()
{
	m_bMenuActive = false;
	CTimer::EndUserPause();
}
#endif

#if 0
WRAPPER float CMenuManager::StretchX(float) { EAXJMP(0x48ABE0); }
#else
float CMenuManager::StretchX(float x)
{
	if (SCREENW == 640)
		return x;
	else
		return SCREENW * x * 0.0015625f;
}
#endif

#if 0
WRAPPER float CMenuManager::StretchY(float) { EAXJMP(0x48AC20); }
#else
float CMenuManager::StretchY(float y)
{
	if (SCREENH == 448)
		return y;
	else
		return SCREENH * y * 0.002232143f;
}
#endif

#if 0
WRAPPER void CMenuManager::SwitchMenuOnAndOff() { EAXJMP(0x488790); }
#else
void CMenuManager::SwitchMenuOnAndOff()
{

}
#endif

#if 0
WRAPPER void CMenuManager::UnloadTextures() { EAXJMP(0x47A440); }
#else
void CMenuManager::UnloadTextures()
{
	if (m_bSpritesLoaded) {
		debug("Remove frontend\n");
		for (int i = 0; i < ARRAY_SIZE(FrontendFilenames); ++i)
			m_aFrontEndSprites[i].Delete();

		int frontend = CTxdStore::FindTxdSlot("frontend");
		CTxdStore::RemoveTxdSlot(frontend);

		debug("Remove menu textures\n");
		for (int i = 0; i < ARRAY_SIZE(MenuFilenames)/2; ++i)
			m_aMenuSprites[i].Delete();

		int menu = CTxdStore::FindTxdSlot("menu");
		CTxdStore::RemoveTxdSlot(menu);

		m_bSpritesLoaded = false;
	}
}
#endif

#if 1
WRAPPER void CMenuManager::WaitForUserCD(void) { EAXJMP(0x48ADD0); }
#else
void CMenuManager::WaitForUserCD()
{

}
#endif

STARTPATCHES
	InjectHook(0x47A230, &CMenuManager::LoadAllTextures, PATCH_JUMP);
	InjectHook(0x47A440, &CMenuManager::UnloadTextures, PATCH_JUMP);

	for (int i = 1; i < ARRAY_SIZE(aScreens); i++)
		Patch(0x611930 + sizeof(CMenuScreen) * i, aScreens[i]);
ENDPATCHES