#pragma

#include "Sprite2d.h"

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

	static int &m_PrefsBrightness;

	void DrawFrontEnd(void);
};
static_assert(sizeof(CMenuManager) == 0x564, "CMenuManager: error");

extern CMenuManager &FrontEndMenuManager;
