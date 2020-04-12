#pragma once
#include "Sprite2d.h"

enum eItems
{
	ITEM_NONE = -1,
	ITEM_ARMOUR = 3,
	ITEM_HEALTH = 4,
	ITEM_RADAR = 8
};

enum eSprites 
{
	HUD_FIST,
	HUD_BAT,
	HUD_PISTOL,
	HUD_UZI,
	HUD_SHOTGUN,
	HUD_AK47,
	HUD_M16,
	HUD_SNIPER,
	HUD_ROCKET,
	HUD_FLAME,
	HUD_MOLOTOV,
	HUD_GRENADE,
	HUD_DETONATOR,
	HUD_RADARDISC = 15,
	HUD_PAGER = 16,
	HUD_SITESNIPER = 20,
	HUD_SITEM16,
	HUD_SITEROCKET,
	NUM_HUD_SPRITES,
};

class CHud
{
public:
	static CSprite2d Sprites[NUM_HUD_SPRITES];
	static wchar m_HelpMessage[256];
	static wchar m_LastHelpMessage[256];
	static uint32 m_HelpMessageState;
	static uint32 m_HelpMessageTimer;
	static int32 m_HelpMessageFadeTimer;
	static wchar m_HelpMessageToPrint[256];
	static float &m_HelpMessageDisplayTime;
	static float m_fHelpMessageTime;
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
	static wchar m_BigMessage[6][128];
	static int16 m_ItemToFlash;

	// These aren't really in CHud
	static float BigMessageInUse[6];
	static float BigMessageAlpha[6];
	static float BigMessageX[6];
	static float OddJob2OffTimer;
	static bool CounterOnLastFrame;
	static float OddJob2XOffset;
	static uint16 CounterFlashTimer;
	static uint16 OddJob2Timer;
	static bool TimerOnLastFrame;
	static int16 OddJob2On;
	static uint16 TimerFlashTimer;
	static int16 PagerSoundPlayed;
	static int32 SpriteBrightness;
	static float PagerXOffset;
	static int16 PagerTimer;
	static int16 PagerOn;

public:
	static void Draw();
	static void DrawAfterFade();
	static void GetRidOfAllHudMessages();
	static void Initialise();
	static void ReInitialise();
	static void SetBigMessage(wchar *message, int16 style);
	static void SetHelpMessage(wchar *message, bool quick);
	static void SetMessage(wchar *message);
	static void SetPagerMessage(wchar *message);
	static void SetVehicleName(wchar *name);
	static void SetZoneName(wchar *name);
	static void Shutdown();
};
