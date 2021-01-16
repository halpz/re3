#pragma once

void AsciiToUnicode(const char *src, wchar *dst);
void UnicodeStrcpy(wchar *dst, const wchar *src);
void UnicodeStrcat(wchar *dst, wchar *append);
int UnicodeStrlen(const wchar *str);
void UnicodeMakeUpperCase(wchar *dst, const wchar *src);

struct CFontDetails
{
	CRGBA color;
	float scaleX;
	float scaleY;
	float slant;
	float slantRefX;
	float slantRefY;
	bool justify;
	bool centre;
	bool rightJustify;
	bool background;
	bool backgroundOnlyText;
	bool proportional;
	bool bIsShadow;
	bool bFlash;
	bool bBold;
	float alphaFade;
	CRGBA backgroundColor;
	float wrapX;
	float centreSize;
	float rightJustifyWrap;
	int16 style;
	bool bFontHalfTexture;
	uint32 bank;
	int16 dropShadowPosition;
	CRGBA dropColor;
	bool bFlashState;
	int nFlashTimer;
	bool anonymous_23;
	uint32 anonymous_25;
	uint32 anonymous_26;
	CRGBA outlineColor;
	int32 bOutlineOn;
	uint32 line;
};

struct CFontRenderState
{
	uint32 anonymous_0;
	float fTextPosX;
	float fTextPosY;
	float scaleX;
	float scaleY;
	CRGBA color;
	float fExtraSpace;
	float slant;
	float slantRefX;
	float slantRefY;
	bool bIsShadow;
	bool bFontHalfTexture;
	bool proportional;
	bool anonymous_14;
	int16 style;
};

class CSprite2d;

enum {
	FONT_BANK,
	FONT_STANDARD,
	FONT_HEADING,
	MAX_FONTS
};

enum {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT,
};

#ifdef MORE_LANGUAGES
enum
{
	FONT_LANGSET_EFIGS,
	FONT_LANGSET_RUSSIAN,
	FONT_LANGSET_POLISH,
	FONT_LANGSET_JAPANESE,
	LANGSET_MAX
};

#define FONT_LOCALE(style) (CFont::IsJapanese() ? FONT_JAPANESE : style)
#else
#define FONT_LOCALE(style) (style)
#endif

#ifdef BUTTON_ICONS
enum
{
	BUTTON_NONE = -1,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_CROSS,
	BUTTON_CIRCLE,
	BUTTON_SQUARE,
	BUTTON_TRIANGLE,
	BUTTON_L1,
	BUTTON_L2,
	BUTTON_L3,
	BUTTON_R1,
	BUTTON_R2,
	BUTTON_R3,
	BUTTON_RSTICK_LEFT,
	BUTTON_RSTICK_RIGHT,
	MAX_BUTTON_ICONS
};
#endif // BUTTON_ICONS


class CFont
{
#ifdef MORE_LANGUAGES
	static int16 Size[LANGSET_MAX][MAX_FONTS][193];
	static uint8 LanguageSet;
	static int32 Slot;
#else
	static int16 Size[MAX_FONTS][419];
#endif
	static int16 NewLine;
public:
	static CSprite2d Sprite[MAX_FONTS];
	static CFontDetails Details;
	static CFontRenderState RenderState;

#ifdef BUTTON_ICONS
	static int32 ButtonsSlot;
	static CSprite2d ButtonSprite[MAX_BUTTON_ICONS];
	static int PS2Symbol;

	static void DrawButton(float x, float y);
#endif // BUTTON_ICONS


	static void Initialise(void);
	static void Shutdown(void);
	static void InitPerFrame(void);
	static void PrintChar(float x, float y, wchar c);
	static void PrintString(float x, float y, wchar *s);
#ifdef XBOX_SUBTITLES
	static void PrintStringFromBottom(float x, float y, wchar *str);
	static void PrintOutlinedString(float x, float y, wchar *str, float outlineStrength, bool fromBottom, CRGBA outlineColor);
#endif
	static int GetNumberLines(float xstart, float ystart, wchar *s);
	static void GetTextRect(CRect *rect, float xstart, float ystart, wchar *s);
#ifdef MORE_LANGUAGES
	static bool PrintString(float x, float y, wchar *start, wchar* &end, float spwidth, float japX);
#else
	static void PrintString(float x, float y, uint32, wchar *start, wchar *end, float spwidth);
#endif
	static void PrintStringFromBottom(float x, float y, wchar *str);
	static float GetCharacterWidth(wchar c);
	static float GetCharacterSize(wchar c);
	static float GetStringWidth(wchar *s, bool spaces = false);
#ifdef MORE_LANGUAGES
	static float GetStringWidth_Jap(wchar* s);
#endif
	static uint16 *GetNextSpace(wchar *s);
#ifdef MORE_LANGUAGES
	static uint16 *ParseToken(wchar *s, bool japShit = false);
#else
	static uint16 *ParseToken(wchar *s);
	static uint16* ParseToken(wchar *s, CRGBA &color, bool &flash, bool &bold);
#endif
	static void DrawFonts(void);
	static void RenderFontBuffer(void);
	static uint16 character_code(uint8 c);

	static CFontDetails GetDetails() { return Details; }
	static void SetScale(float x, float y);
	static void SetSlantRefPoint(float x, float y) { Details.slantRefX = x; Details.slantRefY = y; }
	static void SetSlant(float s) { Details.slant = s; }
	static void SetJustifyOn(void) {
		Details.justify = true;
		Details.centre = false;
		Details.rightJustify = false;
	}
	static void SetJustifyOff(void) {
		Details.justify = false;
		Details.rightJustify = false;
	}
	static void SetRightJustifyOn(void) {
		Details.rightJustify = true;
		Details.justify = false;
		Details.centre = false;
	}
	static void SetRightJustifyOff(void) {
		Details.rightJustify = false;
		Details.justify = false;
		Details.centre = false;
	}
	static void SetCentreOn(void) {
		Details.centre = true;
		Details.justify = false;
		Details.rightJustify = false;
	}
	static void SetCentreOff(void) {
		Details.centre = false;
	}
	static void SetAlignment(uint8 alignment) {
		if (alignment == ALIGN_LEFT) {
			CFont::Details.justify = true;
			CFont::Details.centre = false;
			CFont::Details.rightJustify = false;
		}
		else if (alignment == ALIGN_CENTER) {
			CFont::Details.justify = false;
			CFont::Details.centre = true;
			CFont::Details.rightJustify = false;
		}
		else if (alignment == ALIGN_RIGHT) {
			CFont::Details.justify = false;
			CFont::Details.centre = false;
			CFont::Details.rightJustify = true;
		}
	}
	static void SetWrapx(float x) { Details.wrapX = x; }
	static void SetCentreSize(float s) { Details.centreSize = s; }
	static void SetBackgroundOn(void) { Details.background = true; }
	static void SetBackgroundOff(void) { Details.background = false; }
	static void SetBackGroundOnlyTextOn(void) { Details.backgroundOnlyText = true; }
	static void SetBackGroundOnlyTextOff(void) { Details.backgroundOnlyText = false; }
	static void SetPropOn(void) { Details.proportional = true; }
	static void SetPropOff(void) { Details.proportional = false; }
	static void SetFontStyle(int16 style);
	static void SetRightJustifyWrap(float wrap) { Details.rightJustifyWrap = wrap; }
	static void SetAlphaFade(float fade) { Details.alphaFade = fade; }
	static void SetDropShadowPosition(int16 pos) { Details.dropShadowPosition = pos; }
	static void SetBackgroundColor(CRGBA col);
	static void SetColor(CRGBA col);
	static void SetDropColor(CRGBA col);

	static void SetOutlineColor(CRGBA col);
	static void SetOutlineOn(int on) { Details.bOutlineOn = on; }
	static void SetNewLineAdd(int line) { Details.line = line; }

	static int16 FindNewCharacter(int16 c);
	static void FilterOutTokensFromString(wchar*);
#ifdef MORE_LANGUAGES
	static void ReloadFonts(uint8 set);

	// japanese stuff
	static bool IsAnsiCharacter(wchar* s);
	static bool IsJapanesePunctuation(wchar* str);
	static bool IsJapanese() { return LanguageSet == FONT_LANGSET_JAPANESE; }
	static bool IsJapaneseFont() { return IsJapanese() && (Details.style == FONT_JAPANESE || Details.style == FONT_PAGER);  }
#endif
};
