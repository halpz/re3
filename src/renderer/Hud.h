#pragma once
#include "Sprite2d.h"

#define HELP_MSG_LENGTH 256

#define HUD_TEXT_SCALE_X 0.7f
#define HUD_TEXT_SCALE_Y 1.25f

enum eItems
{
	ITEM_NONE = -1,
	ITEM_ARMOUR = 3,
	ITEM_HEALTH = 4,
	ITEM_RADAR = 8
};

// Thanks for vague name, R*
enum DRAW_FADE_STATE
{
	HUD_WANTED_FADING = 0,
	HUD_ENERGY_FADING,
	HUD_SCORE_FADING,
	HUD_WEAPON_FADING,
};

// My name
enum eFadeOperation
{
	FADED_OUT = 0,
	START_FADE_OUT,
	FADING_IN,
	FADING_OUT,
	FADE_DISABLED = 5,
};

enum eSprites 
{
	HUD_FIST,
	HUD_SITEROCKET = 41,
	HUD_RADARDISC = 50,
	HUD_BAR_INSIDE1DARK = 57,
	HUD_BAR_INSIDE2DARK,
	HUD_HUDNUMBERS,
	HUD_BAR_INSIDE1,
	HUD_BAR_INSIDE2,
	HUD_BAR_OUTLINE,
	HUD_SITESNIPER,
	HUD_SITEM16,
	HUD_SITELASER,
	HUD_LASERDOT,
	HUD_VIEWFINDER,
	HUD_BLEEDER,
	NUM_HUD_SPRITES = 70,
};

extern float BigMessageInUse[6];

class CHud
{
public:
	static CSprite2d Sprites[NUM_HUD_SPRITES];
	static wchar m_HelpMessage[HELP_MSG_LENGTH];
	static wchar m_LastHelpMessage[HELP_MSG_LENGTH];
	static uint32 m_HelpMessageState;
	static uint32 m_HelpMessageTimer;
	static int32 m_HelpMessageFadeTimer;
	static wchar m_HelpMessageToPrint[HELP_MSG_LENGTH];
	static float m_HelpMessageDisplayTime;
	static bool m_HelpMessageDisplayForever;
	static bool	m_HelpMessageQuick;
	static uint32 m_ZoneState;
	static int32 m_ZoneFadeTimer;
	static uint32 m_ZoneNameTimer;
	static wchar *m_pZoneName;
	static wchar *m_pLastZoneName;
	static wchar *m_ZoneToPrint;
	static wchar *m_VehicleName;
	static wchar *m_pLastVehicleName;
	static wchar *m_pVehicleNameToPrint;
	static uint32 m_VehicleState;
	static int32 m_VehicleFadeTimer;
	static uint32 m_VehicleNameTimer;
	static wchar m_Message[256];
	static wchar m_PagerMessage[256];
	static bool m_Wants_To_Draw_Hud;
	static bool m_Wants_To_Draw_3dMarkers;
	static wchar m_BigMessage[8][128];
	static int16 m_ItemToFlash;
	static bool m_HideRadar;
	static int32 m_ClockState;

	// These aren't really in CHud
	static float BigMessageAlpha[6];
	static float BigMessageX[6];
	static float OddJob2OffTimer;
	static bool CounterOnLastFrame[NUMONSCREENCOUNTERS];
	static float OddJob2XOffset;
	static uint16 CounterFlashTimer[NUMONSCREENCOUNTERS];
	static uint16 OddJob2Timer;
	static bool TimerOnLastFrame;
	static int16 OddJob2On;
	static uint16 TimerFlashTimer;
	static int16 PagerSoundPlayed;
	static int32 SpriteBrightness;
	static float PagerXOffset;
	static int16 PagerTimer;
	static int16 PagerOn;

	static uint32 m_WantedFadeTimer;
	static uint32 m_WantedState;
	static uint32 m_WantedTimer;
	static uint32 m_EnergyLostFadeTimer;
	static uint32 m_EnergyLostState;
	static uint32 m_EnergyLostTimer;
	static uint32 m_DisplayScoreFadeTimer;
	static uint32 m_DisplayScoreState;
	static uint32 m_DisplayScoreTimer;
	static uint32 m_WeaponFadeTimer;
	static uint32 m_WeaponState;
	static uint32 m_WeaponTimer;

	static uint32 m_LastDisplayScore;
	static uint32 m_LastWanted;
	static uint32 m_LastWeapon;
	static uint32 m_LastTimeEnergyLost;

	static wchar* gLastPrintForeverString;
	static uint8 m_HudAlpha;

public:
	static void Draw();
	static void DrawAfterFade();
	static void GetRidOfAllHudMessages();
#ifdef RELOADABLES
	static void ReloadTXD();
#endif
	static void Initialise();
	static void ReInitialise();
	static void SetBigMessage(wchar *message, uint16 style);
	static void SetHelpMessage(wchar *message, bool quick, bool displayForever = false);
	static bool IsHelpMessageBeingDisplayed(void);
	static void SetMessage(wchar *message);
	static void SetPagerMessage(wchar *message);
	static void SetVehicleName(wchar *name);
	static void SetZoneName(wchar *name);
	static void Shutdown();
	static float DrawFadeState(DRAW_FADE_STATE, int);
	static void ResetWastedText(void);
	static void DrawHealthBar(int16 value);
	static void DrawArmourBar(int16 value);
	static void DrawTimeAndCashNumbers(char *str, float x, float y, bool secondSet);
	static void DrawCash();
	static void DrawTime();

	static void UseTimerCounterFontSettings();
};
