#include "common.h"

#include "main.h"
#include "Sprite2d.h"
#include "TxdStore.h"
#include "Font.h"
#ifdef BUTTON_ICONS
#include "FileMgr.h"
#endif
#include "Timer.h"
#include "Frontend.h"

//--LCS: todo scaling (needs CSprite2d reversed), SuspendHandler, ReplaceGermanSZ, volatile mem, other todos

void
AsciiToUnicode(const char *src, wchar *dst)
{
	while((*dst++ = (unsigned char)*src++) != '\0');
}

void
UnicodeStrcat(wchar *dst, wchar *append)
{
	UnicodeStrcpy(&dst[UnicodeStrlen(dst)], append);
}

void
UnicodeStrcpy(wchar *dst, const wchar *src)
{
	while((*dst++ = *src++) != '\0');
}

int
UnicodeStrlen(const wchar *str)
{
	int len;
	for(len = 0; *str != '\0'; len++, str++);
	return len;
}

void
UnicodeMakeUpperCase(wchar *dst, const wchar *src) //idk what to do with it, seems to be incorrect implementation by R*
{
	while (*src != '\0') {
		if (*src < 'a' || *src > 'z')
			*dst = *src;
		else
			*dst = *src - 32;
		dst++;
		src++;
	}
	*dst = '\0';
}

CFontDetails CFont::Details;
bool16 CFont::NewLine;
CSprite2d CFont::Sprite[MAX_FONTS];
CFontRenderState CFont::RenderState;

int16 CFont::Size[MAX_FONTS][419] = {
	{15, 6,  8,  24, 22, 28, 28, 2,  8,  8,  12, 24, 8,  10, 8,  12, 24, 8,  22, 20, 24, 22, 22, 22, 24, 22, 8,  8,  22, 22, 24, 16, 28, 26, 20, 22, 22, 18, 18,
		24, 22, 4,  16, 20, 18, 26, 20, 24, 20, 24, 22, 24, 20, 20, 26, 32, 26, 26, 20, 10, 12, 8,  22, 18, 6,  26, 20, 22, 22, 18, 18, 24, 22, 4,  16, 20, 18, 26,
		20, 24, 20, 24, 22, 24, 20, 20, 26, 32, 26, 26, 20, 10, 12, 8,  22, 18, 26, 26, 26, 26, 26, 26, 26, 22, 18, 18, 18, 18, 8,  8,  10, 10, 26, 20, 24, 24, 24,
		24, 24, 22, 24, 20, 20, 20, 20, 26, 22, 20, 26, 26, 26, 26, 26, 26, 26, 22, 18, 18, 18, 18, 8,  8,  10, 10, 26, 20, 24, 24, 24, 24, 24, 22, 24, 20, 20, 20,
		20, 26, 22, 24, 24, 8,  16, 10, 8,  28, 8,  8,  18, 16, 10, 28, 8,  28, 24, 6,  16, 22, 18, 24, 4,  14, 10, 26, 14, 16, 26, 12, 2,  16, 16, 32, 19, 19, 19,
		19, 19, 19, 19, 19, 24, 19, 19, 19, 19, 19, 19, 19, 19, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -2, 0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  -2, 0,  -2, -2, 0,  0,  0,  0,  -2, -2, -2, 0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  -2, 0,  -2, -2, 0,  0,  0,  0,  -2, -2, -2, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -2, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -2, 0,  -2, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  -2, 0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  28},
	{10, 12, 20, 24, 28, 30, 28, 12, 14, 14, 20, 24, 12, 16, 10, 28, 26, 20, 24, 24, 26, 24, 24, 24, 24, 24, 12, 12, 22, 22, 24, 24, 32, 28, 24, 26, 26, 24, 22,
		28, 26, 10, 22, 26, 22, 30, 28, 28, 26, 30, 26, 26, 28, 26, 26, 32, 26, 26, 26, 14, 18, 14, 22, 22, 14, 22, 22, 22, 22, 22, 18, 22, 22, 10, 12, 20, 10, 28,
		20, 22, 22, 22, 20, 22, 20, 20, 20, 30, 20, 22, 20, 16, 10, 16, 20, 0,  28, 28, 28, 28, 28, 28, 32, 26, 24, 24, 24, 24, 14, 14, 18, 16, 30, 28, 28, 28, 28,
		28, 28, 20, 30, 26, 26, 26, 26, 28, 26, 22, 22, 22, 22, 22, 22, 22, 32, 22, 22, 22, 22, 22, 14, 14, 18, 16, 22, 20, 22, 22, 22, 22, 22, 22, 24, 20, 20, 20,
		20, 22, 22, 22, 26, 12, 18, 18, 12, 32, 12, 12, 18, 18, 18, 32, 12, 32, 28, 10, 22, 28, 24, 28, 10, 26, 16, 30, 16, 20, 30, 18, 14, 18, 24, 32, 30, 30, 30,
		30, 24, 28, 24, 20, 24, 20, 20, 22, 20, 20, 10, 10, 10, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  -2, 0,  0,  0,  -2, -2, 0,  0,  2,  0,  0,  0,  0,  -2, -2, 0,  0,  0,  -2, -2, -2, 0,  -2, 0,  -2, 0,  0,  0,  0,  0,  0,
		0,  0,  -2, -2, 0,  0,  -2, 0,  -2, 1,  0,  -2, -1, 0,  0,  0,  -2, 0,  0,  0,  -2, 0,  0,  -2, 0,  -2, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  -2, -2, -2, -2, 0,  0,  -2, 0,  0,  0,  0,  -2, -2, -2, -2, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  28},
	{15, 8,  0,  0,  18, 0,  22, 8,  13, 13, 0,  0,  7,  0,  8,  22, 18, 17, 18, 18, 20, 18, 18, 18, 18, 18, 8, 18, 18, 18, 18, 18, 15, 18, 18, 8, 18, 18, 13,
		28, 18, 18, 18, 18, 18, 18, 20, 18, 19, 30, 18, 18, 18, 18, 18, 18, 0,  18, 0,  28, 18, 18, 18, 18, 0,  8, 8,  8,  8,  0,  18, 18, 18, 18, 0, 18, 0,  0,
		18, 18, 18, 18, 0,  0,  20, 30, 18, 8,  9,  9,  18, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  22}
};


int FontSizeIncrementers[] = { 4, -2, 2 };

wchar foreign_table[128] = {
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0, 176,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0, 177,   0,   0,   0,   0,   0,  95,   0,   0,   0,   0, 175,
	128, 129, 130,   0, 131,   0, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141,
	  0, 173, 142, 143, 144,   0, 145,   0,   0, 146, 147, 148, 149,   0,   0, 150,
	151, 152, 153,   0, 154,   0, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
	  0, 174, 165, 166, 167,   0, 168,   0,   0, 169, 170, 171, 172,   0,   0,   0,
};

union tFontRenderStatePointer
{
	CFontRenderState *pRenderState;
	wchar *pStr;

	void Align()
	{
		if ((uintptr)pStr % 4)
			pStr++;
	}
};

tFontRenderStatePointer FontRenderStatePointer;
uint8 FontRenderStateBuf[1024];

#ifdef BUTTON_ICONS
CSprite2d CFont::ButtonSprite[MAX_BUTTON_ICONS];
int CFont::PS2Symbol = BUTTON_NONE;
int CFont::ButtonsSlot = -1;
#endif // BUTTON_ICONS

//--TODO(LCS): volatile memory
void
CFont::Initialise(void)
{
	int slot;

	if (gMakeResources)
	{
		slot = CTxdStore::AddTxdSlot("fonts");
		CTxdStore::LoadTxd(slot, "MODELS/FONTS.TXD");
		CTxdStore::AddRef(slot);
		CTxdStore::PushCurrentTxd();
		CTxdStore::SetCurrentTxd(slot);
		Sprite[0].SetTexture("font2", "font2m");
		Sprite[1].SetTexture("font1", "font1m");
		Sprite[2].SetTexture("font3", "font3m");
		CTxdStore::PopCurrentTxd();
	}
	else
		slot = CTxdStore::FindTxdSlot("fonts");
	SetScale(1.0f, 1.0f);
	SetSlantRefPoint(SCREEN_WIDTH, 0.0f);
	SetSlant(0.0f);
	SetColor(CRGBA(255, 255, 255, 0));
	SetJustifyOff();
	SetCentreOff();
	SetWrapx(SCREEN_WIDTH);
	SetCentreSize(SCREEN_WIDTH);
	SetBackgroundOff();
	SetBackgroundColor(CRGBA(128, 128, 128, 128));
	SetBackGroundOnlyTextOff();
	SetPropOn();
	SetFontStyle(FONT_BANK);
	SetRightJustifyWrap(0.0f);
	SetAlphaFade(255.0f);
	SetDropShadowPosition(0);
	SetOutlineColor(CRGBA(0, 0, 0, 0));
	SetOutlineOn(0);
	SetNewLineAdd(0);
	SetNewLineAdd(2);

	/*
	if (mspCompressedTexList)
	{
		// TODO (LCS): volatile shit
	}
	*/

#if !defined(GAMEPAD_MENU) && defined(BUTTON_ICONS)
	// loaded in CMenuManager with GAMEPAD_MENU defined
	LoadButtons("MODELS/X360BTNS.TXD");
#endif
}

#ifdef BUTTON_ICONS
void
CFont::LoadButtons(const char *txdPath)
{
	if (int file = CFileMgr::OpenFile(txdPath)) {
		CFileMgr::CloseFile(file);
		if (ButtonsSlot == -1)
			ButtonsSlot = CTxdStore::AddTxdSlot("buttons");
		else {
			for (int i = 0; i < MAX_BUTTON_ICONS; i++)
				ButtonSprite[i].Delete();
			CTxdStore::RemoveTxd(ButtonsSlot);
		}
		CTxdStore::LoadTxd(ButtonsSlot, txdPath);
		CTxdStore::AddRef(ButtonsSlot);
		CTxdStore::PushCurrentTxd();
		CTxdStore::SetCurrentTxd(ButtonsSlot);
		ButtonSprite[BUTTON_UP].SetTexture("thumblyu");
		ButtonSprite[BUTTON_DOWN].SetTexture("thumblyd");
		ButtonSprite[BUTTON_LEFT].SetTexture("thumblxl");
		ButtonSprite[BUTTON_RIGHT].SetTexture("thumblxr");
		ButtonSprite[BUTTON_CROSS].SetTexture("cross");
		ButtonSprite[BUTTON_CIRCLE].SetTexture("circle");
		ButtonSprite[BUTTON_SQUARE].SetTexture("square");
		ButtonSprite[BUTTON_TRIANGLE].SetTexture("triangle");
		ButtonSprite[BUTTON_L1].SetTexture("l1");
		ButtonSprite[BUTTON_L2].SetTexture("l2");
		ButtonSprite[BUTTON_L3].SetTexture("l3");
		ButtonSprite[BUTTON_R1].SetTexture("r1");
		ButtonSprite[BUTTON_R2].SetTexture("r2");
		ButtonSprite[BUTTON_R3].SetTexture("r3");
		ButtonSprite[BUTTON_RSTICK_UP].SetTexture("thumbryu");
		ButtonSprite[BUTTON_RSTICK_DOWN].SetTexture("thumbryd");
		ButtonSprite[BUTTON_RSTICK_LEFT].SetTexture("thumbrxl");
		ButtonSprite[BUTTON_RSTICK_RIGHT].SetTexture("thumbrxr");
		CTxdStore::PopCurrentTxd();
	}
	else {
		if (ButtonsSlot != -1) {
			for (int i = 0; i < MAX_BUTTON_ICONS; i++)
				ButtonSprite[i].Delete();
			CTxdStore::RemoveTxdSlot(ButtonsSlot);
			ButtonsSlot = -1;
		}
	}
}
#endif // BUTTON_ICONS

#ifdef MORE_LANGUAGES
void
CFont::ReloadFonts(uint8 set)
{
	if (Slot != -1 && LanguageSet != set) {
		Sprite[0].Delete();
		Sprite[1].Delete();
		Sprite[2].Delete();
		if (IsJapanese())
			Sprite[3].Delete();
		CTxdStore::PushCurrentTxd();
		CTxdStore::RemoveTxd(Slot);
		switch (set)
		{
		case FONT_LANGSET_EFIGS:
		default:
			CTxdStore::LoadTxd(Slot, "MODELS/FONTS.TXD");
			break;
		case FONT_LANGSET_POLISH:
			CTxdStore::LoadTxd(Slot, "MODELS/FONTS_P.TXD");
			break;
		case FONT_LANGSET_RUSSIAN:
			CTxdStore::LoadTxd(Slot, "MODELS/FONTS_R.TXD");
			break;
		case FONT_LANGSET_JAPANESE:
			CTxdStore::LoadTxd(Slot, "MODELS/FONTS_J.TXD");
			break;
		}
		CTxdStore::SetCurrentTxd(Slot);
		Sprite[0].SetTexture("font2", "font2_mask");
		if (set == FONT_LANGSET_JAPANESE) {
			Sprite[1].SetTexture("FONTJAP", "FONTJAP_mask");
			Sprite[3].SetTexture("FONTJAP", "FONTJAP_mask");
		}
		else
			Sprite[1].SetTexture("pager", "pager_mask");
		Sprite[2].SetTexture("font1", "font1_mask");
		CTxdStore::PopCurrentTxd();
	}
	LanguageSet = set;
}
#endif

//--TODO(LCS): gpFonts
void
CFont::Shutdown(void)
{
#ifdef BUTTON_ICONS
	if (ButtonsSlot != -1) {
		for (int i = 0; i < MAX_BUTTON_ICONS; i++)
			ButtonSprite[i].Delete();
		CTxdStore::RemoveTxdSlot(ButtonsSlot);
		ButtonsSlot = -1;
	}
#endif
	Sprite[0].Delete();
	Sprite[1].Delete();
	Sprite[2].Delete();
#ifdef MORE_LANGUAGES
	if (IsJapanese())
		Sprite[3].Delete();
	CTxdStore::RemoveTxdSlot(Slot);
	Slot = -1;
#else
	CTxdStore::RemoveTxdSlot(CTxdStore::FindTxdSlot("fonts"));
#endif
}

//--LCS: Done
void
CFont::InitPerFrame(void)
{
	RenderState.style = -1;
	Details.anonymous_25 = 0;
	FontRenderStatePointer.pRenderState = (CFontRenderState*)FontRenderStateBuf;
	SetDropShadowPosition(0);
	NewLine = false;
#ifdef BUTTON_ICONS
	PS2Symbol = BUTTON_NONE;
#endif
}

#ifdef BUTTON_ICONS
void
CFont::DrawButton(float x, float y)
{
	if (x <= 0.0f || x > SCREEN_WIDTH || y <= 0.0f || y > SCREEN_HEIGHT)
		return;

	if (PS2Symbol != BUTTON_NONE) {
		CRect rect;
		rect.left = x;
		rect.top = RenderState.scaleY + RenderState.scaleY + y;
		rect.right = RenderState.scaleY * 17.0f + x;
		rect.bottom = RenderState.scaleY * 19.0f + y;

		int vertexAlphaState;
		void *raster;
		RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &vertexAlphaState);
		RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &raster);
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
		if (RenderState.bIsShadow)
			ButtonSprite[PS2Symbol].Draw(rect, RenderState.color);
		else
			ButtonSprite[PS2Symbol].Draw(rect, CRGBA(255, 255, 255, RenderState.color.a));
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, raster);
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)vertexAlphaState);
	}
}
#endif

//--LCS: TODO (mostly done but could use some checking)
void
CFont::PrintChar(float x, float y, wchar c)
{
	if (!(c >= 0 && c < 209)) return;

	bool bDontPrint = false;
	if(x <= 0.0f || x > SCREEN_WIDTH ||
	   y <= -12.0f || y > SCREEN_HEIGHT)	// BUG: game uses SCREENW again
		return;

	bDontPrint = c == '\0';
	float w = GetCharacterWidth(c) / 32.0f;

	if ( !RenderState.proportional && RenderState.rightJustify )
		x += (GetCharacterWidth(c) - GetCharacterWidth(c, true)) * RenderState.scaleX;

	if (Details.bFontHalfTexture && c == 208)
		c = '\0';


	float xoff = c % 16;
	float yoff = c / 16;

	// small float modifiers were left for pc

	if(RenderState.style == FONT_BANK || RenderState.style == FONT_STANDARD){
		if (bDontPrint) return;
		if (RenderState.slant == 0.0f) {
			if (c < 192) {
				CSprite2d::AddToBuffer(
					CRect(x, y,
						x + 32.0f * RenderState.scaleX * 0.96f,
						y + 40.0f * RenderState.scaleY * 0.5f),
					RenderState.color,
					xoff / 16.0f, yoff / 12.8f + 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f,
					xoff / 16.0f, (yoff + 1.0f) / 12.8f - 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f - 0.0021f);
			} else {
				float xScale = 0.54f;
				if (FrontEndMenuManager.m_PrefsUseWideScreen)
					xScale = 0.486f;
				CSprite2d::AddToBuffer(
					CRect(x, y + RenderState.scaleY * 4.0f,
						x + 32.0f * RenderState.scaleY * xScale * 0.96f,
						y + 4.0f * RenderState.scaleY + 16.0f * RenderState.scaleY),
					RenderState.color,
					xoff / 16.0f, yoff / 12.8f + 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f,
					xoff / 16.0f, (yoff + 1.0f) / 12.8f - 0.017f,
					(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f - 0.017f);
			}
		} else
			CSprite2d::AddToBuffer(
				CRect(x, y,
					x + 32.0f * RenderState.scaleX * 0.96f,
					y + 40.0f * RenderState.scaleY * 0.5f),
				RenderState.color,
				xoff / 16.0f, yoff / 12.8f + 0.00055f,
				(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f + 0.01f,
				xoff / 16.0f, (yoff + 1.0f) / 12.8f - 0.009f,
				(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f - 0.0021f + 0.01f);
	} else {
		if (bDontPrint) return;
		CSprite2d::AddToBuffer(
			CRect(x, y,
				x + 32.0f * RenderState.scaleX * w,
				y + 32.0f * RenderState.scaleY * 0.5f),
			RenderState.color,
			xoff / 16.0f, yoff / 6.4f,
			(xoff + w) / 16.0f, yoff / 6.4f,
			xoff / 16.0f, (yoff + 1.0f) / 6.4f,
			(xoff + w) / 16.0f, (yoff + 1.0f) / 6.4f);
	}
}

#ifdef MORE_LANGUAGES
bool CFont::IsJapanesePunctuation(wchar *str)
{
	return (*str == 0xE7 || *str == 0x124 || *str == 0x126 || *str == 0x128 || *str == 0x104 || *str == ',' || *str == '>' || *str == '!' || *str == 0x99 || *str == '?' || *str == ':');
}

bool CFont::IsAnsiCharacter(wchar *s)
{
	if (*s >= 'A' && *s <= 'Z')
		return true;
	if (*s >= 'a' && *s <= 'z')
		return true;
	if (*s >= '0' && *s <= ':')
		return true;
	if (*s == '(' || *s == ')')
		return true;
	if (*s == 'D' || *s == '$')
		return true;
	return false;
}
#endif

//--LCS: TODO (mostly done but could use some checking)
void
CFont::RenderFontBuffer()
{
	if (FontRenderStatePointer.pRenderState == (CFontRenderState*)FontRenderStateBuf) return;

	float textPosX;
	float textPosY;
	CRGBA color;
	bool bBold = false;
	bool bFlash = false;

	Sprite[RenderState.style].SetRenderState();
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE); // TODO: not in lcs
	RenderState = *(CFontRenderState*)&FontRenderStateBuf[0];
	textPosX = RenderState.fTextPosX;
	textPosY = RenderState.fTextPosY;
	color = RenderState.color;
	tFontRenderStatePointer pRenderStateBufPointer;
	pRenderStateBufPointer.pRenderState = (CFontRenderState*)&FontRenderStateBuf[0];
	for (++pRenderStateBufPointer.pRenderState; pRenderStateBufPointer.pStr < FontRenderStatePointer.pStr; pRenderStateBufPointer.pStr++) {
		if (*pRenderStateBufPointer.pStr == '\0') {
			tFontRenderStatePointer tmpPointer = pRenderStateBufPointer;
			tmpPointer.pStr++;
			tmpPointer.Align();
			if (tmpPointer.pStr >= FontRenderStatePointer.pStr)
				break;

			RenderState = *(tmpPointer.pRenderState++);

			pRenderStateBufPointer = tmpPointer;

			textPosX = RenderState.fTextPosX;
			textPosY = RenderState.fTextPosY;
			color = RenderState.color;
		}
		if (*pRenderStateBufPointer.pStr == '~') {
#ifdef BUTTON_ICONS
			PS2Symbol = BUTTON_NONE;
#endif
			pRenderStateBufPointer.pStr = ParseToken(pRenderStateBufPointer.pStr, color, bFlash, bBold);
#ifdef BUTTON_ICONS
			if(PS2Symbol != BUTTON_NONE) {
				DrawButton(textPosX, textPosY);
				textPosX += RenderState.scaleY * 17.0f;
				PS2Symbol = BUTTON_NONE;
			}
#endif
			if (bFlash) {
				if (CTimer::GetTimeInMilliseconds() - Details.nFlashTimer > 300) {
					Details.bFlashState = !Details.bFlashState;
					Details.nFlashTimer = CTimer::GetTimeInMilliseconds();
				}
				Details.color.alpha = Details.bFlashState ? 0 : 255;
			}
			if (!RenderState.bIsShadow && !RenderState.bOutlineOn)
				RenderState.color = color;
		}
		wchar c = *pRenderStateBufPointer.pStr;
		c -= ' ';
		if (c == 200) c = '^';
		if (c == 201) c = '>';
		if (RenderState.bFontHalfTexture) 
			c = FindNewCharacter(c);
		if (RenderState.slant != 0.0f)
			textPosY = (RenderState.slantRefX - textPosX) * RenderState.slant + RenderState.slantRefY;
		PrintChar(textPosX, textPosY, c);
		if (bBold) {
			PrintChar(textPosX + 1.0f, textPosY, c);
			PrintChar(textPosX + 2.0f, textPosY, c);
			textPosX += 2.0f;
		}
		textPosX += RenderState.scaleX * GetCharacterWidth(c);
//#ifdef FIX_BUGS
//		// PS2 uses different chars for some symbols
//		if (!RenderState.bFontHalfTexture && c == 30) c = 61; // wanted star
//#endif
		if (c == '\0')
			textPosX += RenderState.fExtraSpace;
	}
	CSprite2d::RenderVertexBuffer();
	FontRenderStatePointer.pRenderState = (CFontRenderState*)FontRenderStateBuf;
}


//--LCS: TODO
void
CFont::PrintString(float x, float y, uint32, wchar *start, wchar *end, float spwidth)
{
	wchar *s;

	if (RenderState.style != Details.style) {
		RenderFontBuffer();
		RenderState.style = Details.style;
	}

	if (Details.outlineColor.a != 0) {
		CRGBA color = Details.color;
		Details.color = Details.outlineColor;
		Details.bOutlineOn = true;
		Details.outlineColor.a = 0;
		Details.dropShadowPosition = 0;
		Details.bIsShadow = false;
		PrintString(x, y, Details.anonymous_25, start, end, spwidth);
		Details.color = color;
		Details.bOutlineOn = false;
	} else {
		float dropShadowPosition = Details.dropShadowPosition;
		if (dropShadowPosition != 0.0f && (Details.style == FONT_BANK || Details.style == FONT_STANDARD)) {
			CRGBA color = Details.color;
			Details.color = Details.dropColor;
			Details.dropShadowPosition = 0;
			Details.bIsShadow = true;
			if (Details.slant != 0.0f) {
				Details.slantRefX += SCREEN_SCALE_X(dropShadowPosition);
				Details.slantRefY += SCREEN_SCALE_Y(dropShadowPosition);
				PrintString(SCREEN_SCALE_X(dropShadowPosition) + x, SCREEN_SCALE_Y(dropShadowPosition) + y, Details.anonymous_25, start, end, spwidth);
				Details.slantRefX -= SCREEN_SCALE_X(dropShadowPosition);
				Details.slantRefY -= SCREEN_SCALE_Y(dropShadowPosition);
			} else {
				PrintString(SCREEN_SCALE_X(dropShadowPosition) + x, SCREEN_SCALE_Y(dropShadowPosition) + y, Details.anonymous_25, start, end, spwidth);
			}
			Details.color = color;
			Details.dropShadowPosition = dropShadowPosition;
			Details.bIsShadow = false;
		}
	}
	if ((uintptr)FontRenderStatePointer.pStr >= (uintptr)&FontRenderStateBuf[ARRAY_SIZE(FontRenderStateBuf)] - sizeof(wchar) * (end - start + 2) - sizeof(CFontRenderState))
		RenderFontBuffer();
	CFontRenderState *pRenderState = FontRenderStatePointer.pRenderState;
	pRenderState->fTextPosX = x;
	pRenderState->fTextPosY = y;
	pRenderState->scaleX = Details.scaleX;
	pRenderState->scaleY = Details.scaleY;
	pRenderState->color = Details.color;
	pRenderState->fExtraSpace = spwidth;
	pRenderState->slant = Details.slant;
	pRenderState->slantRefX = Details.slantRefX;
	pRenderState->slantRefY = Details.slantRefY;
	pRenderState->bFontHalfTexture = Details.bFontHalfTexture;
	pRenderState->proportional = Details.proportional;
	pRenderState->style = Details.style;
	pRenderState->bIsShadow = Details.bIsShadow;
	FontRenderStatePointer.pRenderState++;

	for(s = start; s < end;){
		if (*s == '~') {
			for (wchar *i = ParseToken(s); s != i; FontRenderStatePointer.pStr++) {
				*FontRenderStatePointer.pStr = *(s++);
			}
			if (Details.bFlash) {
				if (CTimer::GetTimeInMilliseconds() - Details.nFlashTimer > 300) {
					Details.bFlashState = !Details.bFlashState;
					Details.nFlashTimer = CTimer::GetTimeInMilliseconds();
				}
				Details.color.a = Details.bFlashState ? 0 : 255;
			}
		} else
			*(FontRenderStatePointer.pStr++) = *(s++);
	}
	*(FontRenderStatePointer.pStr++) = '\0';
	FontRenderStatePointer.Align();
}

// LCS: Done
void
CFont::PrintStringFromBottom(float x, float y, wchar *str)
{
	y -= (32.0f * Details.scaleY / 2.0f + Details.line * Details.scaleY) * GetNumberLines(x, y, str);
	if (Details.slant != 0.0f)
		y -= ((Details.slantRefX - x) * Details.slant + Details.slantRefY);
	PrintString(x, y, str);
}

//--LCS: TODO
void
CFont::PrintString(float xstart, float ystart, wchar *s)
{
	CRect rect;
	int numSpaces;
	float lineLength;
	float x, y;
	bool first;
	wchar *start, *t;

	CRGBA outlineColor = Details.outlineColor;
	CFont::SetFlashOff();

	if(*s == '*')
		return;

	Details.anonymous_25++;
	if(Details.background){
		RenderState.color = Details.color;
		GetNumberLines(xstart, ystart, s);	// BUG: result not used
		GetTextRect(&rect, xstart, ystart, s);
		CSprite2d::DrawRect(rect, Details.backgroundColor);
	}

	lineLength = 0.0f;
	numSpaces = 0;
	first = true;
	if(Details.centre || Details.rightJustify)
		x = 0.0f;
	else
		x = xstart;
	y = ystart;
	start = s;

	// This is super ugly, I blame R*
	for(;;){
		for(;;){
			for(;;){
				if(*s == '\0')
					return;
				float xend = Details.centre ? Details.centreSize :
				           Details.rightJustify ? xstart - Details.rightJustifyWrap :
				           Details.wrapX;
#ifdef MORE_LANGUAGES
				if (IsJapaneseFont())
					xend -= SCREEN_SCALE_X(21.0f * 2.0f);
#endif
				if(x + GetStringWidth(s) > xend && !first){
#ifdef MORE_LANGUAGES
					if (IsJapanese() && IsJapanesePunctuation(s))
						s--;
#endif
					// flush line
					float spaceWidth = !Details.justify || Details.centre ? 0.0f :
						(Details.wrapX - lineLength) / numSpaces;
					float xleft = Details.centre ? xstart - x/2 :
					              Details.rightJustify ? xstart - x :
					              xstart;
#ifdef MORE_LANGUAGES
					PrintString(xleft, y, start, s, spaceWidth, xstart);
#else
					PrintString(xleft, y, Details.anonymous_25, start, s, spaceWidth);
#endif
					// reset things
					lineLength = 0.0f;
					numSpaces = 0;
					first = true;
					if(Details.centre || Details.rightJustify)
						x = 0.0f;
					else
						x = xstart;
#ifdef MORE_LANGUAGES
					if (IsJapaneseFont())
						y += 32.0f * Details.scaleY / 2.75f + 2.0f * Details.scaleY;
					else
#endif
						y += 32.0f * Details.scaleY * 0.5f + 2.0f * Details.scaleY;
					start = s;
				}else
					break;
			}
			// advance by one word
			t = GetNextSpace(s);
			if(t[0] == '\0' ||
			   t[0] == ' ' && t[1] == '\0')
				break;
			if(!first)
				numSpaces++;
			first = false;
			x += GetStringWidth(s) + GetCharacterSize(*t - ' ');
#ifdef MORE_LANGUAGES
			if (IsJapaneseFont() && IsAnsiCharacter(s))
				x += 21.0f;
#endif
			lineLength = x;
			s = t+1;
#ifdef MORE_LANGUAGES
			if (IsJapaneseFont() && !*s) {
				x += GetStringWidth(s);
				if (IsAnsiCharacter(s))
					x += 21.0f;
				float xleft = Details.centre ? xstart - x / 2 :
					Details.rightJustify ? xstart - x :
					xstart;
				if (PrintString(xleft, y, start, s, 0.0f, xstart))
				{
					start = s;
					if (!Details.centre && !Details.rightJustify)
						x = xstart;
					else
						x = 0.0f;

					y += 32.0f * Details.scaleY / 2.75f + 2.0f * Details.scaleY;
					numSpaces = 0;
					first = true;
					lineLength = 0.0f;
				}
			}
#endif
		}
		// print rest
		if(t[0] == ' ' && t[1] == '\0')
			t[0] = '\0';
		x += GetStringWidth(s);
		s = t;
		float xleft = Details.centre ? xstart - x/2 :
		              Details.rightJustify ? xstart - x :
		              xstart;
#ifdef MORE_LANGUAGES
		if (PrintString(xleft, y, start, s, 0.0f, xstart) && IsJapaneseFont()) {
			start = s;
			if (!Details.centre && !Details.rightJustify)
				x = xstart;
			else
				x = 0.0f;
			y += 32.0f * Details.scaleY / 2.75f + 2.0f * Details.scaleY;
			numSpaces = 0;
			first = true;
			lineLength = 0.0f;
		}
#else
		PrintString(xleft, y, Details.anonymous_25, start, s, 0.0f);
#endif
	}
}

//--LCS: TODO
int
CFont::GetNumberLines(float xstart, float ystart, wchar *s)
{
	int n;
	float x, y;
	wchar *t;
	n = 0;

#ifdef MORE_LANGUAGES
	bool bSomeJapBool = false;

	if (IsJapanese()) {
		t = s;
		wchar unused;
		while (*t) {
			if (*t == JAP_TERMINATION || *t == '~')
				t = ParseToken(t, &unused, true);
			if (NewLine) {
				n++;
				NewLine = false;
				bSomeJapBool = true;
			}
			t++;
		}
	}

	if (bSomeJapBool) n--;
#endif

	if(Details.centre || Details.rightJustify)
		x = 0.0f;
	else
		x = xstart;
	y = ystart;

	while(*s){
#ifdef FIX_BUGS
		float f = Details.centre ? Details.centreSize :
		           Details.rightJustify ? xstart - Details.rightJustifyWrap :
		           Details.wrapX;
#else
		float f = (Details.centre ? Details.centreSize : Details.wrapX);
#endif

#ifdef MORE_LANGUAGES
		if (IsJapaneseFont())
			f -= SCREEN_SCALE_X(21.0f * 2.0f);
#endif

		if(x + GetStringWidth(s) > f){
#ifdef MORE_LANGUAGES
			if (IsJapanese())
			{
				if (IsJapanesePunctuation(s))
					s--;
			}
#endif
			// reached end of line
			if(Details.centre || Details.rightJustify)
				x = 0.0f;
			else
				x = xstart;
			n++;
			// Why even?
#ifdef MORE_LANGUAGES
			if (IsJapanese())
				y += 32.0f * Details.scaleY / 2.75f + 2.0f * Details.scaleY;
			else
#endif
				y += 32.0f * Details.scaleY * 0.5f + 2.0f * Details.scaleY;
		}else{
			// still space in current line
			t = GetNextSpace(s);
			if(*t == '\0'){
				// end of string
				x += GetStringWidth(s);
#ifdef MORE_LANGUAGES
				if (IsJapanese() && IsAnsiCharacter(s))
					x += 21.0f;
#endif
				n++;
				s = t;
			}else{
				x += GetStringWidth(s);
#ifdef MORE_LANGUAGES
				if (IsJapanese() && IsAnsiCharacter(s))
					x += 21.0f;
#endif
				s = t+1;
				x += GetCharacterSize(*t - ' ');
#ifdef MORE_LANGUAGES
				if (IsJapanese() && !*s)
					n++;
#endif
			}
		}
	}

	return n;
}

//--LCS: TODO
void
CFont::GetTextRect(CRect *rect, float xstart, float ystart, wchar *s)
{
	int numLines;
	float x, y;
	int16 maxlength;
	wchar *t;

	maxlength = 0;
	numLines = 0;

#ifdef MORE_LANGUAGES
	if (IsJapanese()) {
		numLines = GetNumberLines(xstart, ystart, s);
	}else{
#endif
		if(Details.centre || Details.rightJustify)
			x = 0.0f;
		else
			x = xstart;
		y = ystart;

#ifdef FIX_BUGS
		float xEnd = Details.centre ? Details.centreSize :
		           Details.rightJustify ? xstart - Details.rightJustifyWrap :
		           Details.wrapX;
#else
		float xEnd = (Details.centre ? Details.centreSize : Details.wrapX);
#endif
		while(*s){
			if(x + GetStringWidth(s) > xEnd){
				// reached end of line
				if(x > maxlength)
					maxlength = x;
				if(Details.centre || Details.rightJustify)
					x = 0.0f;
				else
					x = xstart;
				numLines++;
				y += 32.0f * Details.scaleY * 0.5f + 2.0f * Details.scaleY;
			}else{
				// still space in current line
				t = GetNextSpace(s);
				if(*t == '\0'){
					// end of string
					x += GetStringWidth(s);
					if(x > maxlength)
						maxlength = x;
					numLines++;
					s = t;
				}else{
					x += GetStringWidth(s);
					x += GetCharacterSize(*t - ' ');
					s = t+1;
				}
			}
		}
#ifdef MORE_LANGUAGES
	}
#endif

	if(Details.centre){
		if(Details.backgroundOnlyText){
			rect->left = xstart - maxlength/2 - 4.0f;
			rect->right = xstart + maxlength/2 + 4.0f;
#ifdef MORE_LANGUAGES
			if (IsJapaneseFont()) {
				rect->bottom = (32.0f * Details.scaleY / 2.75f + 2.0f * Details.scaleY) * numLines + ystart + (4.0f / 2.75f);
				rect->top = ystart - (4.0f / 2.75f);
			} else {
#endif
				rect->bottom = (32.0f * Details.scaleY * 0.5f + 2.0f * Details.scaleY) * numLines + ystart + 2.0f;
				rect->top = ystart - 2.0f;
#ifdef MORE_LANGUAGES
			}
#endif
		}else{
			rect->left = xstart - Details.centreSize*0.5f - 4.0f;
			rect->right = xstart + Details.centreSize*0.5f + 4.0f;
#ifdef MORE_LANGUAGES
			if (IsJapaneseFont()) {
				rect->bottom = (32.0f * Details.scaleY / 2.75f + 2.0f * Details.scaleY) * numLines + ystart + (4.0f / 2.75f);
				rect->top = ystart - (4.0f / 2.75f);
			} else {
#endif
				rect->bottom = (32.0f * Details.scaleY * 0.5f + 2.0f * Details.scaleY) * numLines + ystart + 2.0f;
				rect->top = ystart - 2.0f;
#ifdef MORE_LANGUAGES
			}
#endif
		}
	}else{
		rect->left = xstart - 4.0f;
		rect->right = Details.wrapX;
		// WTF?
		rect->bottom = ystart - 4.0f + 4.0f;
#ifdef MORE_LANGUAGES
		if (IsJapaneseFont())
			rect->top = (32.0f * Details.scaleY / 2.75f + 2.0f * Details.scaleY) * numLines + ystart + 2.0f + (4.0f / 2.75f);
		else
#endif
			rect->top = (32.0f * Details.scaleY * 0.5f + 2.0f * Details.scaleY) * numLines + ystart + 2.0f + 2.0f;
	}
}

//--LCS: done
bool IsPunctuation(wchar c)
{
	switch (c)
	{
	case '!':
	case '?':
	case '.':
	case ',':
	case ':':
	case ';':
	
	// these are lucid it seems
	//case '$':
	//case '/':
	//case '\\':
		return true;
	}
	return false;
}

//--LCS: done
float
CFont::GetCharacterWidth(wchar c, bool forceProportional)
{
	if (RenderState.proportional || forceProportional)
	{
		float inc = c < 192 ? 0.0f : 4.0f;
		return Size[RenderState.style][c] + Size[RenderState.style][c + 209] + FontSizeIncrementers[RenderState.style] + inc;
	} else {
		if (IsPunctuation(c + ' '))
			return Size[RenderState.style][418] / 1.6f + FontSizeIncrementers[RenderState.style];
		else
			return Size[RenderState.style][418] + FontSizeIncrementers[RenderState.style];
	}
}

//--LCS: done
float
CFont::GetCharacterSize(wchar c)
{
//#ifdef FIX_BUGS
	// PS2 don't call FindNewCharacter in here at all, and also uses different chars for some symbols
//	if (!Details.bFontHalfTexture && c == 30) c = 61; // wanted star
//#endif
	if (Details.bFontHalfTexture)
		c = FindNewCharacter(c);
	if (Details.proportional) {
		float inc = c < 192 ? 0.0f : 4.0f;
		return (Size[Details.style][c] + Size[Details.style][c + 209] + FontSizeIncrementers[Details.style] + inc) * Details.scaleX;
	} else {
		if (IsPunctuation(c + ' '))
			return (Size[Details.style][418] + FontSizeIncrementers[Details.style]) / 1.6f * Details.scaleX;
		else
			return Size[Details.style][418] + FontSizeIncrementers[Details.style] * Details.scaleX;
	}
}

//--LCS: TODO
float
CFont::GetStringWidth(wchar *s, bool spaces)
{
	float w;

	w = 0.0f;
#ifdef MORE_LANGUAGES
	if (IsJapanese())
	{
		do
		{
			if ((*s != ' ' || spaces) && *s != '\0') {
				do {
					while (*s == '~' || *s == JAP_TERMINATION) {
						s++;
#ifdef BUTTON_ICONS
						switch (*s) {
						case 'U':
						case 'D':
						case '<':
						case '>':
						case 'X':
						case 'O':
						case 'Q':
						case 'T':
						case 'K':
						case 'M':
						case 'A':
						case 'J':
						case 'V':
						case 'C':
						case '(':
						case ')':
							w += 17.0f * Details.scaleY;
							break;
						default:
							break;
						}
#endif
						while (!(*s == '~' || *s == JAP_TERMINATION)) s++;
						s++;
					}
					w += GetCharacterSize(*s - ' ');
					++s;
				} while (*s == '~' || *s == JAP_TERMINATION);
			}
		} while (IsAnsiCharacter(s));
	} else
#endif
	{
		for (wchar c = *s; (c != ' ' || spaces) && c != '\0'; c = *(++s)) {
			if (c == '~') {
				s++;
#ifdef BUTTON_ICONS
				switch (*s) {
				case 'U':
				case 'D':
				case '<':
				case '>':
				case 'X':
				case 'O':
				case 'Q':
				case 'T':
				case 'K':
				case 'M':
				case 'A':
				case 'J':
				case 'V':
				case 'C':
				case '(':
				case ')':
					w += 17.0f * Details.scaleY;
					break;
				default:
					break;
				}
#endif
				while (*s != '~') {
					s++;
				}
			}
			else {
				w += GetCharacterSize(c - ' ');
			}
		}
	}
	return w;
}


#ifdef MORE_LANGUAGES
float
CFont::GetStringWidth_Jap(wchar* s)
{
	float w;

	w = 0.0f;
	for (; *s != '\0';) {
		do {
			while (*s == '~' || *s == JAP_TERMINATION) {
				s++;
				while (!(*s == '~' || *s == JAP_TERMINATION)) s++;
				s++;
			}
			w += GetCharacterSize(*s - ' ');
			++s;
		} while (*s == '~' || *s == JAP_TERMINATION);
	}
	return w;
}
#endif

//--LCS: done
bool16
CFont::CheckNewLine(wchar *s)
{
	while (*s == ' ')
		s++;

	if (*s == '~')
		return s[1] == 'N' || s[1] == 'n';
	return false;
}

//--LCS: TODO
wchar*
CFont::GetNextSpace(wchar *s)
{
#ifdef MORE_LANGUAGES
	if (IsJapanese()) {
		do
		{
			if (*s != ' ' && *s != '\0') {
				do {
					while (*s == '~' || *s == JAP_TERMINATION) {
						s++;
						while (!(*s == '~' || *s == JAP_TERMINATION)) s++;
						s++;
					}
					++s;
				} while (*s == '~' || *s == JAP_TERMINATION);
			}
		} while (IsAnsiCharacter(s));
	} else
#endif
	{
		for(; *s != ' ' && *s != '\0'; s++)
			if(*s == '~'){
				s++;
				while(*s != '~') s++;
			}
	}
	return s;
}

//--LCS: done
wchar*
CFont::ParseToken(wchar* str, CRGBA &color, bool &flash, bool &bold)
{
	Details.anonymous_23 = false;
	wchar *s = str + 1;
	if (Details.color.r || Details.color.g || Details.color.b)
	{
		switch (*s)
		{
		case 'B':
			bold = !bold;
			break;
		case 'Y':
			color.r = 255;
			color.g = 227;
			color.b = 79;
			break;
		case 'b':
			color.r = 77;
			color.g = 155;
			color.b = 210;
			break;
		case 'f':
			flash = !flash;
			break;
		case 'g':
			color.r = 75;
			color.g = 151;
			color.b = 75;
			Details.anonymous_23 = true;
			break;
		case 'h':
			color.r = 255;
			color.g = 255;
			color.b = 255;
			Details.anonymous_23 = true;
			break;
		case 'l':
			color.r = 0;
			color.g = 0;
			color.b = 0;
			Details.anonymous_23 = true;
			break;
		case 'o':
			color.r = 229;
			color.g = 125;
			color.b = 126;
			break;
		case 'p':
			color.r = 151;
			color.g = 82;
			color.b = 197;
			break;
		case 'q':
			color.r = 199;
			color.g = 144;
			color.b = 203;
			break;
		case 'r':
			color.r = 174;
			color.g = 0;
			color.b = 0;
			break;
		case 't':
			color.r = 86;
			color.g = 212;
			color.b = 146;
			break;
		case 'w':
			color.r = 225;
			color.g = 225;
			color.b = 225;
			Details.anonymous_23 = true;
			break;
		case 'x':
			color.r = 132;
			color.g = 146;
			color.b = 197;
			break;
		case 'y':
			color.r = 255;
			color.g = 255;
			color.b = 0;
			break;
#ifdef BUTTON_ICONS
		case 'U': PS2Symbol = BUTTON_UP; break;
		case 'D': PS2Symbol = BUTTON_DOWN; break;
		case '<': PS2Symbol = BUTTON_LEFT; break;
		case '>': PS2Symbol = BUTTON_RIGHT; break;
		case 'X': PS2Symbol = BUTTON_CROSS; break;
		case 'O': PS2Symbol = BUTTON_CIRCLE; break;
		case 'Q': PS2Symbol = BUTTON_SQUARE; break;
		case 'T': PS2Symbol = BUTTON_TRIANGLE; break;
		case 'K': PS2Symbol = BUTTON_L1; break;
		case 'M': PS2Symbol = BUTTON_L2; break;
		case 'A': PS2Symbol = BUTTON_L3; break;
		case 'J': PS2Symbol = BUTTON_R1; break;
		case 'V': PS2Symbol = BUTTON_R2; break;
		case 'C': PS2Symbol = BUTTON_R3; break;
		case 'H': PS2Symbol = BUTTON_RSTICK_UP; break;
		case 'L': PS2Symbol = BUTTON_RSTICK_DOWN; break;
		case '(': PS2Symbol = BUTTON_RSTICK_LEFT; break;
		case ')': PS2Symbol = BUTTON_RSTICK_RIGHT; break;
#endif
		default:
			break;
		}
	}
	while (*s != '~')
		++s;

	// seem to be gone in lcs
	//if (*(++s) == '~')
	//	s = ParseToken(s, color, flash, bold);

	// wtf?
	if (*s == '\0') s++;
	s++;
	return s;
}

//--LCS: done
wchar*
CFont::ParseToken(wchar *s)
{
	bool flash = false;
	bool bold = false;
	CRGBA color = Details.color;
	s = ParseToken(s, color, flash, bold);
	Details.bFlash = flash;
	Details.bBold = bold;

	if (Details.anonymous_23)
		Details.color = color;
	return s;
}

//--LCS: done
void
CFont::FilterOutTokensFromString(wchar *str)
{
	int newIdx = 0;
	wchar copy[256], *c;
	UnicodeStrcpy(copy, str);

	for (c = copy; *c != '\0'; c++) {
		if (*c == '~') {
			c++;
			while (*c != '~') c++;
		} else {
			str[newIdx++] = *c;
		}
	}
	str[newIdx] = '\0';
}

//--LCS: done
void
CFont::DrawFonts(void)
{
	RenderFontBuffer();
}

//--LCS: done
void
CFont::SetScale(float x, float y)
{
	Details.scaleX = x;
	Details.scaleY = y;
}

//--LCS: done
void
CFont::SetSlantRefPoint(float x, float y)
{
	Details.slantRefX = x;
	Details.slantRefY = y;
}

//--LCS: done
void
CFont::SetSlant(float s)
{
	Details.slant = s;
}

//--LCS: done
void
CFont::SetColor(CRGBA col)
{
	Details.color = col;
	if (Details.alphaFade < 255.0f)
		Details.color.a *= Details.alphaFade / 255.0f;
}

//--LCS: done
void
CFont::SetFlashOff()
{
	Details.bFlash = false;
}

//--LCS: done
void
CFont::SetJustifyOn(void)
{
	Details.justify = true;
	Details.centre = false;
	Details.rightJustify = false;
}

//--LCS: done
void
CFont::SetJustifyOff(void)
{
	Details.justify = false;
	Details.rightJustify = false;
}

//--LCS: done
void
CFont::SetCentreOn(void)
{
	Details.centre = true;
	Details.justify = false;
	Details.rightJustify = false;
}

//--LCS: done
void
CFont::SetCentreOff(void)
{
	Details.centre = false;
}

//--LCS: TODO
void
CFont::SetWrapx(float x)
{
	// uncomment when scaling is done
	//x = clamp(x, 0.0f, DEFAULT_SCREEN_WIDTH);
	Details.wrapX = x;
}

//--LCS: done
void
CFont::SetCentreSize(float s)
{
	Details.centreSize = s;
}

//--LCS: done
void
CFont::SetBackgroundOn(void)
{
	Details.background = true;
}

//--LCS: done
void
CFont::SetBackgroundOff(void)
{
	Details.background = false;
}

//--LCS: done
void
CFont::SetBackgroundColor(CRGBA col)
{
	Details.backgroundColor = col;
}

//--LCS: done
void
CFont::SetBackGroundOnlyTextOn(void)
{
	Details.backgroundOnlyText = true;
}

//--LCS: done
void
CFont::SetBackGroundOnlyTextOff(void)
{
	Details.backgroundOnlyText = false;
}

//--LCS: done
void
CFont::SetRightJustifyOn(void)
{
	Details.rightJustify = true;
	Details.justify = false;
	Details.centre = false;
}

//--LCS: done
void
CFont::SetRightJustifyOff(void)
{
	Details.rightJustify = false;
	Details.justify = false;
	Details.centre = false;
}

//--LCS: done
void
CFont::SetPropOff(void)
{
	Details.proportional = false;
}

//--LCS: done
void
CFont::SetPropOn(void)
{
	Details.proportional = true;
}

//--LCS: done
void
CFont::SetFontStyle(int16 style)
{
	if (style == FONT_HEADING) {
		Details.style = FONT_HEADING;
		Details.bFontHalfTexture = true;
	}
	else {
		Details.style = style;
		Details.bFontHalfTexture = false;
	}
}

//--LCS: done
void
CFont::SetRightJustifyWrap(float wrap)
{
	Details.rightJustifyWrap = wrap;
}

//--LCS: done
void
CFont::SetAlphaFade(float fade)
{
	Details.alphaFade = fade;
}

//--LCS: done
void
CFont::SetDropColor(CRGBA col)
{
	Details.dropColor = col;
	if (Details.alphaFade < 255.0f)
		// TODO: was this a copypaste bug in here?
		//Details.dropColor.a *= Details.alphaFade / 255.0f;
		Details.dropColor.a = Details.color.a * Details.alphaFade / 255.0f;
}


//--LCS: done
void
CFont::SetOutlineColor(CRGBA col)
{
	Details.outlineColor = col;
	if (Details.alphaFade < 255.0f)
		Details.outlineColor.a *= Details.alphaFade / 255.0f;
}

//--LCS: done
void
CFont::SetOutlineOn(int on)
{
	Details.bOutlineOn = on;
}

//--LCS: done
void
CFont::SetNewLineAdd(int line)
{
	Details.line = line;
}

//--LCS: done
void
CFont::SetDropShadowPosition(int16 pos)
{
	Details.dropShadowPosition = pos;
}

int16 CFont::FindNewCharacter(int16 c)
{
    if (c >= 33 && c <= 33 + 25)
        return c - 6;
    else if(c >= 65 && c <= 65 + 25)
        return c - 38;
    else if (c >= 96 && c <= 96 + 31)
        return c - 43;
    else if (c >= 128 && c <= 128 + 31)
        return c - 75;

	switch (c)
	{
	case 190:
		return 90;
	case 175:
		return 87;
	case 184:
		return 88;
	case 187:
		return 89;
	case 31:
		return 88;
	}
	if (c >= 27 && c < 31)
		return 2;
	if (c >= 180 && c < 256)
		c = 2;
	return c;
}

wchar
CFont::character_code(uint8 c)
{
	if(c < 128)
		return c;
	return foreign_table[c-128];
}
