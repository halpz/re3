#pragma once
#include "Sprite2d.h"

struct CScriptRectangle 
{
	bool m_bIsUsed;
	bool m_bIsAntialiased;
	uint16 m_wTextureId;
	CRect m_sRect;
	CRGBA m_sColor;
};

struct CTextLine 
{
	float m_fScaleX;
	float m_fScaleY;
	CRGBA m_sColor;
	bool m_bJustify;
	bool m_bCentered;
	bool m_bBackground;
	bool m_bBackgroundOnly;
	float m_fWrapX;
	float m_fCenterSize;
	CRGBA m_sBackgroundColor;
	bool m_bTextProportional;
	int32 field_29;
	bool m_bRightJustify;
	int32 field_31;
	int32 m_nFont;
	float field_36;
	float field_40;
	wchar m_awText[500];
};

class CTheScripts
{
public:
	static uint8 *ScriptSpace;//[160*1024]
	static CTextLine* IntroTextLines;
	static CScriptRectangle* IntroRectangles;
	static CSprite2d* ScriptSprites;
};
