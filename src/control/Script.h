#pragma once
#include "Sprite2d.h"

struct CScriptRectangle 
{
	Bool m_bIsUsed;
	Bool m_bIsAntialiased;
	uint16 m_wTextureId;
	CRect m_sRect;
	CRGBA m_sColor;
};

struct CTextLine 
{
	Float m_fScaleX;
	Float m_fScaleY;
	CRGBA m_sColor;
	Bool m_bJustify;
	Bool m_bCentered;
	Bool m_bBackground;
	Bool m_bBackgroundOnly;
	Float m_fWrapX;
	Float m_fCenterSize;
	CRGBA m_sBackgroundColor;
	Bool m_bTextProportional;
	int32 field_29;
	Bool m_bRightJustify;
	int32 field_31;
	int32 m_nFont;
	Float field_36;
	Float field_40;
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
