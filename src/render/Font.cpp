#include "common.h"

#include "Sprite2d.h"
#include "TxdStore.h"
#include "Font.h"
#include "Timer.h"

CFontDetails CFont::Details;
int16 CFont::NewLine;
CSprite2d CFont::Sprite[MAX_FONTS];
CFontRenderState CFont::RenderState;

#ifdef MORE_LANGUAGES
uint8 CFont::LanguageSet = FONT_LANGSET_EFIGS;
int32 CFont::Slot = -1;
#define JAP_TERMINATION (0x8000 | '~')

int16 CFont::Size[LANGSET_MAX][MAX_FONTS][193] = {
	{
#else
int16 CFont::Size[MAX_FONTS][210] = {
#endif
	{
		12, 9,  22, 17, 19, 19, 25, 4,  33, 33, 25, 35, 11, 10, 6,  33, 18, 10, 17, 17, 17, 17, 17, 15, 12, 16, 5,  30, 30, 30, 30, 30, 12, 16, 19,
		16, 19, 18, 18, 17, 22, 11, 17, 18, 18, 30, 22, 19, 22, 19, 19, 20, 18, 19, 19, 29, 19, 18, 19, 19, 33, 33, 19, 19, 12, 14, 11, 11, 16, 11,
		12, 14, 14, 10, 13, 12, 10, 19, 18, 12, 16, 13, 13, 11, 12, 15, 12, 15, 13, 12, 12, 37, 33, 37, 35, 37, 16, 16, 16, 16, 33, 17, 18, 18, 18,
		18, 11, 11, 11, 11, 19, 19, 19, 19, 19, 19, 19, 19, 15, 14, 14, 14, 14, 20, 14, 11, 11, 11, 11, 10, 10, 10, 10, 12, 12, 12, 12, 15, 15, 15,
		15, 24, 18, 21, 10, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
		19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 16
	},
	{
		15, 7, 31, 25, 20, 23, 21, 7, 11, 10, 26, 14, 6, 12, 6, 26, 20, 7, 20, 20, 21, 20, 20, 19, 21, 20, 8, 30, 24, 30, 24, 19, 20, 22, 22, 21, 22, 18, 18, 22,
		22, 9, 14, 21, 18, 27, 21, 24, 22, 22, 23, 20, 19, 23, 22, 31, 23, 23, 21, 25, 13, 30, 10, 19, 10, 17, 17, 16, 17, 17, 11, 17, 17, 7, 7, 18, 7, 25, 17,
		17, 17, 17, 11, 17, 11, 17, 18, 25, 19, 18, 17, 28, 26, 20, 15, 15, 20, 20, 20, 20, 29, 22, 19, 19, 19, 19, 9, 9, 9, 9, 23, 23, 23, 23, 24, 24, 24, 24,
		20, 19, 17, 17, 17, 30, 16, 17, 17, 17, 17, 11, 11, 15, 12, 17, 17, 17, 17, 17, 17, 17, 17, 19, 20, 20, 20, 18, 19, 19, 21, 19, 19, 19, 19, 19, 16, 19,
		19, 19, 20, 19, 16, 19, 19, 9, 19, 20, 14, 29, 19, 19, 19, 19, 19, 19, 21, 19, 20, 32, 20, 19, 19, 19, 19, 19, 19, 29, 19, 19, 19, 19, 19, 9, 9, 9, 9,
		19, 19, 19, 19, 19, 19, 19, 19, 19, 21, 21, 10, 9, 10, 20
	}
#ifdef MORE_LANGUAGES
	},
	{
		{ 13, 12, 31, 35, 23, 35, 31, 9, 14, 15, 25, 30, 11, 17,
			13, 31, 23, 16, 22, 21, 24, 23, 23, 20, 23, 22, 10,
			35, 26, 26, 26, 26, 30, 26, 24, 23, 24, 22, 21, 24,
			26, 10, 20, 26, 22, 29, 26, 25, 23, 25, 24, 24, 22,
			25, 24, 29, 29, 23, 25, 37, 22, 37, 35, 37, 35, 21,
			22, 21, 21, 22, 13, 22, 21, 10, 16, 22, 11, 32, 21,
			21, 23, 22, 16, 20, 14, 21, 20, 30, 25, 21, 21, 13,
			33, 13, 13, 13, 24, 22, 22, 19, 26, 21, 30, 20, 23,
			23, 21, 24, 26, 23, 22, 23, 21, 22, 20, 20, 26, 25,
			24, 22, 31, 32, 23, 30, 22, 22, 32, 23, 19, 18, 18,
			15, 22, 19, 27, 19, 20, 20, 18, 22, 24, 20, 19, 19,
			20, 19, 16, 19, 28, 20, 20, 18, 26, 27, 19, 26, 18,
			19, 27, 19, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
			26, 26, 26, 18, 26, 26, 26, 26, 26, 26, 26, 26, 26,
			26, 26, 26, 26, 26, 26, 26, 26, 26, 20 },
		{ 13, 9, 21, 35, 23, 35, 35, 11, 35, 35, 25, 35, 11,
			17, 13, 33, 28, 14, 22, 21, 24, 23, 23, 21, 23, 22,
			10, 35, 13, 35, 13, 33, 5, 25, 22, 23, 24, 21, 21, 24,
			24, 9, 20, 24, 21, 27, 25, 25, 22, 25, 23, 20, 23, 23,
			23, 31, 23, 23, 23, 37, 33, 37, 35, 37, 35, 21, 19,
			19, 21, 19, 17, 21, 21, 8, 17, 18, 14, 24, 21, 21, 20,
			22, 19, 20, 20, 19, 20, 26, 21, 20, 21, 33, 33, 33,
			33, 35, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 16, },
		{ 15, 14, 16, 25, 19,
			26, 22, 11, 18, 18, 27, 26, 13, 19, 9, 27, 19, 18, 19,
			19, 22, 19, 20, 18, 19, 20, 12, 32, 15, 32, 15, 35,
			15, 19, 19, 19, 19, 19, 16, 19, 20, 9, 19, 20, 14, 29,
			19, 20, 19, 19, 19, 19, 21, 19, 20, 32, 20, 19, 19,
			33, 31, 39, 37, 39, 37, 21, 21, 21, 23, 21, 19, 23, 23, 10, 19, 20, 16, 26, 23,
			21, 21, 20, 20, 22, 21, 22, 22, 26, 22, 22, 23, 35,
			35, 35, 35, 37, 19, 19, 19, 19, 19, 19, 29, 19, 19,
			19, 20, 22, 31, 19, 19, 19, 19, 19, 29, 19, 29, 19,
			21, 19, 30, 31, 21, 29, 19, 19, 29, 19, 21, 23, 32,
			21, 21, 30, 31, 22, 21, 32, 33, 23, 32, 21, 21, 32,
			21, 19, 19, 30, 31, 22, 22, 21, 32, 33, 23, 32, 21,
			21, 32, 21, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 11, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19 },
	},

	{
		{
			13, 12, 31, 35, 23, 35, 31, 9, 14, 15, 25, 30, 11, 17, 13, 31,
				23, 16, 22, 21, 24, 23, 23, 20, 23, 22, 10, 35, 26, 26, 26, 26,
				30, 26, 24, 23, 24, 22, 21, 24, 26, 10, 20, 26, 22, 29, 26, 25,
				23, 25, 24, 24, 22, 25, 24, 29, 29, 23, 25, 37, 22, 37, 35, 37,
				35, 21, 22, 21, 21, 22, 13, 22, 21, 10, 16, 22, 11, 32, 21, 21,
				23, 22, 16, 20, 14, 21, 20, 30, 25, 21, 21, 33, 33, 33, 33, 35,
				27, 27, 27, 27, 32, 24, 23, 23, 23, 23, 11, 11, 11, 11, 26, 26,
				26, 26, 26, 26, 26, 25, 26, 21, 21, 21, 21, 32, 23, 22, 22, 22,
				22, 11, 11, 11, 11, 22, 22, 22, 22, 22, 22, 22, 22, 26, 21, 24,
				12, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
				26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 18, 26, 26,
				26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
				20
		},

		{
			13,  9, 21, 35, 23, 35, 35, 11, 35, 35, 25, 35, 11, 17, 13, 33,
			28, 14, 22, 21, 24, 23, 23, 21, 23, 22, 10, 35, 13, 35, 13, 33,
			5, 25, 22, 23, 24, 21, 21, 24, 24,  9, 20, 24, 21, 27, 25, 25,
			22, 25, 23, 20, 23, 23, 23, 31, 23, 23, 23, 37, 33, 37, 35, 37,
			35, 21, 19, 19, 21, 19, 17, 21, 21,  8, 17, 18, 14, 24, 21, 21,
			20, 22, 19, 20, 20, 19, 20, 26, 21, 20, 21, 33, 33, 33, 33, 35,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			16
		},

		{
			15, 14, 16, 25, 19, 26, 22, 11, 18, 18, 27, 26, 13, 19,  9, 27,
			19, 18, 19, 19, 22, 19, 20, 18, 19, 20, 12, 32, 15, 32, 15, 35,
			15, 19, 19, 19, 19, 19, 16, 19, 20,  9, 19, 20, 14, 29, 19, 20,
			19, 19, 19, 19, 21, 19, 20, 32, 20, 19, 19, 33, 31, 39, 37, 39,
			37, 21, 21, 21, 23, 21, 19, 23, 23, 10, 19, 20, 16, 26, 23, 23,
			20, 20, 20, 22, 21, 22, 22, 26, 22, 22, 23, 35, 35, 35, 35, 37,
			19, 19, 19, 19, 29, 19, 19, 19, 19, 19,  9,  9,  9,  9, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 30, 19, 19, 19, 19,
			19, 10, 10, 10, 10, 19, 19, 19, 19, 19, 19, 19, 19, 19, 23, 35,
			12, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 11, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19
		}
	}
#endif
};

#ifdef MORE_LANGUAGES
int16 Size_jp[] = {
	15, 14, 16, 20, 19, 26, 22, 11, 18, 18, 27, 26, 13, //; 0
	19, 20, 27, 19, 15, 19, 19, 21, 19, 20, 18, 19, 15, //; 13
	13, 28, 15, 32, 15, 35, 15, 19, 19, 19, 19, 17, 16, //; 26
	19, 20, 15, 19, 20, 14, 17, 19, 19, 19, 19, 19, 19, //; 39
	19, 19, 20, 25, 20, 19, 19, 33, 31, 39, 37, 39, 37, //; 52
	21, 21, 21, 19, 17, 15, 23, 21, 15, 19, 20, 16, 19, //; 65
	19, 19, 20, 20, 17, 22, 19, 22, 22, 19, 22, 22, 23, //; 78
	35, 35, 35, 35, 37, 19, 19, 19, 19, 29, 19, 19, 19, //; 91
	19, 19, 9, 9, 9, 9, 19, 19, 19, 19, 19, 19, 19, 19, //; 104
	19, 19, 19, 19, 19, 30, 19, 19, 19, 19, 19, 10, 10, //; 118
	10, 10, 19, 19, 19, 19, 19, 19, 19, 19, 19, 23, 35, //; 131
	12, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, //; 144
	19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, //; 157
	19, 19, 19, 11, 19, 19, 19, 19, 19, 19, 19, 19, 19, //; 170
	19, 19, 19, 19, 19, 19, 19, 19, 19, 21
};
#endif

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


void* FontRenderStatePointer;
uint8 FontRenderStateBuf[1024];

void
CFont::Initialise(void)
{
	int slot;

	slot = CTxdStore::AddTxdSlot("fonts");
#ifdef MORE_LANGUAGES
	Slot = slot;
	switch (LanguageSet)
	{
	case FONT_LANGSET_EFIGS:
	default:
		CTxdStore::LoadTxd(slot, "MODELS/FONTS.TXD");
		break;
	case FONT_LANGSET_POLISH:
		CTxdStore::LoadTxd(slot, "MODELS/FONTS_P.TXD");
		break;
	case FONT_LANGSET_RUSSIAN:
		CTxdStore::LoadTxd(slot, "MODELS/FONTS_R.TXD");
		break;
	case FONT_LANGSET_JAPANESE:
		CTxdStore::LoadTxd(slot, "MODELS/FONTS_J.TXD");
		break;
	}
#else
	CTxdStore::LoadTxd(slot, "MODELS/FONTS.TXD");
#endif
	CTxdStore::AddRef(slot);
	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(slot);
	Sprite[0].SetTexture("font2", "font2m");
#ifdef MORE_LANGUAGES
	if (IsJapanese()) {
		Sprite[1].SetTexture("FONTJAP", "FONTJAP_mask");
		Sprite[3].SetTexture("FONTJAP", "FONTJAP_mask");
	}
#endif // MORE_LANGUAGES
	Sprite[1].SetTexture("font1", "font1m");
	SetScale(1.0f, 1.0f);
	SetSlantRefPoint(SCREEN_WIDTH, 0.0f);
	SetSlant(0.0f);
	SetColor(CRGBA(0xFF, 0xFF, 0xFF, 0));
	SetJustifyOff();
	SetCentreOff();
	SetWrapx(DEFAULT_SCREEN_WIDTH);
	SetCentreSize(DEFAULT_SCREEN_WIDTH);
	SetBackgroundOff();
	SetBackgroundColor(CRGBA(0x80, 0x80, 0x80, 0x80));
	SetBackGroundOnlyTextOff();
	SetPropOn();
	SetFontStyle(FONT_BANK);
	SetRightJustifyWrap(0.0f);
	SetAlphaFade(255.0f);
	SetDropShadowPosition(0);
	CTxdStore::PopCurrentTxd();
}

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

void
CFont::Shutdown(void)
{
	Sprite[0].Delete();
	Sprite[1].Delete();
#ifdef MORE_LANGUAGES
	if (IsJapanese())
		Sprite[3].Delete();
	CTxdStore::RemoveTxdSlot(Slot);
	Slot = -1;
#else
	CTxdStore::RemoveTxdSlot(CTxdStore::FindTxdSlot("fonts"));
#endif
}

void
CFont::InitPerFrame(void)
{
	//Details.bank = CSprite2d::GetBank(30, Sprite[0].m_pTexture);
	//CSprite2d::GetBank(15, Sprite[1].m_pTexture);
	//CSprite2d::GetBank(15, Sprite[2].m_pTexture);

	RenderState.FontStyle = -1;
	Details.anonymous_25 = 0;
	FontRenderStatePointer = FontRenderStateBuf;
#ifdef MORE_LANGUAGES
	if (IsJapanese())
		CSprite2d::GetBank(15, Sprite[3].m_pTexture);
#endif
	SetDropShadowPosition(0);
	NewLine = 0;
}

void
CFont::PrintChar(float x, float y, wchar c)
{
	bool bDontPrint = false;
	if(x <= 0.0f || x > SCREEN_WIDTH ||
	   y <= 0.0f || y > SCREEN_HEIGHT)	// BUG: game uses SCREENW again
		return;

	bDontPrint = c == '\0';
	float w = GetCharacterWidth(c) / 32.0f;
	if (Details.bFontHalfTexture && c == 208)
		c = '\0';
	float xoff = c % 16;
	float yoff = c / 16;
#ifdef MORE_LANGUAGES
	if (IsJapaneseFont()) {
		w = 21.0f;
		xoff = (float)(c % 48);
		yoff = c / 48;
	}
#endif

	if(Details.style == FONT_BANK || Details.style == FONT_HEADING){
		if (bDontPrint) return;
		CSprite2d::AddToBuffer(
			CRect(x, y,
			      x + 32.0f * RenderState.fTextSizeX * w,
			      y + 32.0f * RenderState.fTextSizeX * 0.5f),
			RenderState.color,
			xoff/16.0f,                 yoff/16.0f,
			(xoff+ w)/16.0f, yoff/ 16.0f,
			xoff/16.0f,                 (yoff+1.0f)/ 16.0f,
			(xoff+ w)/16.0f - 0.0001f, (yoff+1.0f)/ 16.0f - 0.0001f);
#ifdef MORE_LANGUAGES
	}else if (IsJapaneseFont()) {
		if (Details.dropShadowPosition != 0) {
			CSprite2d::AddSpriteToBank(Details.bank + Details.style,	// BUG: game doesn't add bank
				CRect(x + SCREEN_SCALE_X(Details.dropShadowPosition),
					y + SCREEN_SCALE_Y(Details.dropShadowPosition),
					x + SCREEN_SCALE_X(Details.dropShadowPosition) + 32.0f * Details.scaleX * 1.0f,
					y + SCREEN_SCALE_Y(Details.dropShadowPosition) + 40.0f * Details.scaleY / 2.75f),
				Details.dropColor,
				xoff * w / 1024.0f, yoff / 25.6f,
				xoff * w / 1024.0f + (1.0f / 48.0f) - 0.001f, yoff / 25.6f,
				xoff * w / 1024.0f, (yoff + 1.0f) / 25.6f,
				xoff * w / 1024.0f + (1.0f / 48.0f) - 0.001f, (yoff + 1.0f) / 25.6f - 0.0001f);
		}
		CSprite2d::AddSpriteToBank(Details.bank + Details.style,	// BUG: game doesn't add bank
			CRect(x, y,
				x + 32.0f * Details.scaleX * 1.0f,
				y + 40.0f * Details.scaleY / 2.75f),
			Details.color,
			xoff * w / 1024.0f, yoff / 25.6f,
			xoff * w / 1024.0f + (1.0f / 48.0f) - 0.001f, yoff / 25.6f,
			xoff * w / 1024.0f, (yoff + 1.0f) / 25.6f - 0.002f,
			xoff * w / 1024.0f + (1.0f / 48.0f) - 0.001f, (yoff + 1.0f) / 25.6f - 0.0001f);
#endif
	}
	else
	{
		if (bDontPrint) return;
		if (RenderState.fSlant == 0.0f)
		{
			if (c < 193)
			{
				CSprite2d::AddToBuffer(
					CRect(x, y,
						x + 32.0f * RenderState.fTextSizeX * 1.0f,
						y + 40.0f * RenderState.fTextSizeY * 0.5f),
					RenderState.color,
					xoff / 16.0f, yoff / 12.8f + 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f,
					xoff / 16.0f, (yoff + 1.0f) / 12.8f + 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f + 0.0021f);
			}
			else
			{
				CSprite2d::AddToBuffer(
					CRect(x, y,
						x + 32.0f * RenderState.fTextSizeX * 1.0f,
						y + 33.0f * RenderState.fTextSizeY * 0.5f),
					RenderState.color,
					xoff / 16.0f, yoff / 12.8f,
					(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f - 0.017f,
					xoff / 16.0f, (yoff + 1.0f) / 12.8f,
					(xoff + 1.0f) / 16.0f - 0.001f, (yoff+1.0f) / 12.8f - 0.017f);
			}
		}
		else
			CSprite2d::AddToBuffer(
				CRect(x, y,
					x + 32.0f * RenderState.fTextSizeX * 1.0f,
					y + 40.0f * RenderState.fTextSizeY * 0.5f),
				RenderState.color,
				xoff / 16.0f, yoff / 12.8f,
				(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f + 0.01f,
				xoff / 16.0f, (yoff + 1.0f) / 12.8f,
				(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f + 0.0021f + 0.01f);
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

void
CFont::PrintString(float xstart, float ystart, wchar *s)
{
	CRect rect;
	int numSpaces;
	float lineLength;
	float x, y;
	bool first;
	wchar *start, *t;

	if(*s == '*')
		return;

	if(Details.background){
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
						y += 32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY;
					else
#endif
						y += 32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY;
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

					y += 32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY;
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
			y += 32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY;
			numSpaces = 0;
			first = true;
			lineLength = 0.0f;
		}
#else
		PrintString(xleft, y, start, s, 0.0f);
#endif
	}
}

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
		float f = (Details.centre ? Details.centreSize : Details.wrapX);
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
				y += 32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY;
			else
#endif
				y += 32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY;
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

		while(*s){
			if(x + GetStringWidth(s) > (Details.centre ? Details.centreSize : Details.wrapX)){
				// reached end of line
				if(x > maxlength)
					maxlength = x;
				if(Details.centre || Details.rightJustify)
					x = 0.0f;
				else
					x = xstart;
				numLines++;
				y += 32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY;
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
				rect->bottom = (32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY) * numLines + ystart + (4.0f / 2.75f);
				rect->top = ystart - (4.0f / 2.75f);
			} else {
#endif
				rect->bottom = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f;
				rect->top = ystart - 2.0f;
#ifdef MORE_LANGUAGES
			}
#endif
		}else{
			rect->left = xstart - Details.centreSize*0.5f - 4.0f;
			rect->right = xstart + Details.centreSize*0.5f + 4.0f;
#ifdef MORE_LANGUAGES
			if (IsJapaneseFont()) {
				rect->bottom = (32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY) * numLines + ystart + (4.0f / 2.75f);
				rect->top = ystart - (4.0f / 2.75f);
			} else {
#endif
				rect->bottom = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f;
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
			rect->top = (32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f + (4.0f / 2.75f);
		else
#endif
			rect->top = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f + 2.0f;
	}
}

#ifdef MORE_LANGUAGES
bool
CFont::PrintString(float x, float y, wchar *start, wchar *&end, float spwidth, float japX)
{
	wchar *s, c, unused;

	if (IsJapanese()) {
		float jx = 0.0f;
		for (s = start; s < end; s++) {
			if (*s == JAP_TERMINATION || *s == '~')
				s = ParseToken(s, &unused, true);
			if (NewLine) {
				NewLine = false;
				break;
			}
			jx += GetCharacterSize(*s - ' ');
		}
		s = start;
		if (Details.centre)
			x = japX - jx / 2.0f;
		else if (Details.rightJustify)
			x = japX - jx;
	}

	for (s = start; s < end; s++) {
		if (*s == '~' || (IsJapanese() && *s == JAP_TERMINATION))
			s = ParseToken(s, &unused);
		if (NewLine && IsJapanese()) {
			NewLine = false;
			end = s;
			return true;
		}
		c = *s - ' ';
		if (Details.slant != 0.0f && !IsJapanese())
			y = (Details.slantRefX - x) * Details.slant + Details.slantRefY;
		PrintChar(x, y, c);
		x += GetCharacterSize(c);
		if (c == 0 && (!NewLine || !IsJapanese()))	// space
			x += spwidth;
	}
	return false;
}
#else
void
CFont::PrintString(float x, float y, wchar *start, wchar *end, float spwidth)
{
	wchar *s, c, unused;

	if (RenderState.FontStyle != Details.style)
	{
		RenderFontBuffer();
		RenderState.FontStyle = Details.style;
	}

	float v7 = CFont::Details.dropShadowPosition;
	if (v7 != 0.0f && (CFont::Details.style == 0 || CFont::Details.style == 1))
	{
		auto v8 = CFont::Details.color;
		CFont::Details.color = CFont::Details.dropColor;
		CFont::Details.dropShadowPosition = 0;
		CFont::Details.bIsShadow = true;
		if (0.0f != CFont::Details.slant)
		{
			CFont::Details.slantRefX = (double)v7 + CFont::Details.slantRefX;
			CFont::Details.slantRefY = (double)v7 + CFont::Details.slantRefY;
			//CFont::PrintString(v7 + x, v7 + y, CFont::Details.anonymous_25, a4, a5, a6);
			CFont::PrintString(v7 + x, v7 + y, start, end, spwidth);
			CFont::Details.slantRefX = CFont::Details.slantRefX - (double)v7;
			CFont::Details.slantRefY = CFont::Details.slantRefY - (double)v7;
		}
		else
		{
			//CFont::PrintString(v12, v11, CFont::Details.anonymous_25, a4, a5, a6);
			CFont::PrintString(v7 + x, v7 + y, start, end, spwidth);
		}
		CFont::Details.color = v8;
		CFont::Details.dropShadowPosition = v7;
		CFont::Details.bIsShadow = 0;
	}
	if (FontRenderStatePointer >= (char*)&FontRenderStatePointer - 2 * (end - start + 26))
		CFont::RenderFontBuffer();
	CFontRenderState*  v13 = (CFontRenderState*)FontRenderStatePointer;
	v13->fTextPosX = x;
	v13->fTextPosY = y;
	v13->fTextSizeX = CFont::Details.scaleX;
	v13->fTextSizeY = CFont::Details.scaleY;
	v13->color.r = CFont::Details.color.r;
	v13->color.g = CFont::Details.color.g;
	v13->color.b = CFont::Details.color.b;
	v13->color.a = CFont::Details.color.a;
	v13->fExtraSpace = spwidth;
	v13->fSlant = CFont::Details.slant;
	v13->fSlantRefPointX = CFont::Details.slantRefX;
	v13->fSlantRefPointY = CFont::Details.slantRefY;
	v13->bFontHalfTexture = CFont::Details.bFontHalfTexture;
	v13->bProp = CFont::Details.proportional;
	v13->FontStyle = CFont::Details.style;
	v13->bIsShadow = CFont::Details.bIsShadow;
	FontRenderStatePointer = (char*)FontRenderStatePointer + 0x30;

	for(s = start; s < end; s++){
		if (*s == '~')
		{
			for (auto i = ParseToken(s); s != i; FontRenderStatePointer = (char*)FontRenderStatePointer + 2)
			{
				s = i;
				*(wchar*)FontRenderStatePointer = *s;
			}
			if (CFont::Details.bFlash)
			{
				if (CTimer::GetTimeInMilliseconds() - CFont::Details.nFlashTimer > 300)
				{
					Details.bFlashState = !Details.bFlashState;
					Details.nFlashTimer = CTimer::GetTimeInMilliseconds();
				}
				if (Details.bFlashState)
					Details.color.a = 0;
				else
					Details.color.a = 255;
			}
		}
		else
		{
			*(wchar*)FontRenderStatePointer = *s;
			FontRenderStatePointer = (char*)FontRenderStatePointer + 2;
		}
		/*c = *s - ' ';
		if(Details.slant != 0.0f)
			y = (Details.slantRefX - x)*Details.slant + Details.slantRefY;
		PrintChar(x, y, c);
		x += GetCharacterSize(c);
		if(c == 0)	// space
			x += spwidth;*/
	}
	*(wchar*)FontRenderStatePointer = 0;
	FontRenderStatePointer = (char*)FontRenderStatePointer + 2;
	if ((unsigned __int8)FontRenderStatePointer & 3)
		FontRenderStatePointer = (char*)FontRenderStatePointer + 2;
}
#endif

float
CFont::GetCharacterWidth(wchar c)
{
#ifdef MORE_LANGUAGES
	if (IsJapanese()) {
		if (!Details.proportional)
			return Size[0][Details.style][192];
		if (c <= 94 || Details.style == FONT_HEADING || Details.style == FONT_BANK) {
			switch (Details.style)
			{
			case FONT_JAPANESE:
				return Size_jp[c];
			default:
				return Size[0][Details.style][c];
			}
		}
		if (c < 254 && Details.style == FONT_PAGER)
			return 29.4f;

		switch (Details.style)
		{
		case FONT_JAPANESE:
			return 29.4f;
		case FONT_BANK:
			return 10.0f;
		case FONT_PAGER:
			return 31.5f;
		default:
			return Size[0][Details.style][c];
		}
	}

	else if (Details.proportional)
		return Size[LanguageSet][Details.style][c];
	else
		return Size[LanguageSet][Details.style][192];
#else
	if (Details.bFontHalfTexture)
		c = FindNewCharacter(c);
	if (Details.proportional)
		return Size[Details.style][c];
	else
		return Size[Details.style][209];
#endif // MORE_LANGUAGES
}

float
CFont::GetCharacterSize(wchar c)
{
#ifdef MORE_LANGUAGES

	if (IsJapanese())
	{
		if (!Details.proportional)
			return Size[0][Details.style][209] * Details.scaleX;
		if (c <= 94 || Details.style == FONT_HEADING || Details.style == FONT_BANK) {
			switch (Details.style)
			{
			case FONT_JAPANESE:
				return Size_jp[c] * Details.scaleX;
			default:
				return Size[0][Details.style][c] * Details.scaleX;
			}
		}
		if (c < 254 && (Details.style == FONT_PAGER))
			return 29.4f * Details.scaleX;

		switch (Details.style)
		{
		case FONT_JAPANESE:
			return 29.4f * Details.scaleX;
		case FONT_BANK:
			return 10.0f * Details.scaleX;
		case FONT_PAGER:
			return 31.5f * Details.scaleX;
		default:
			return Size[0][Details.style][c] * Details.scaleX;
		}
	}
	else if(Details.proportional)
		return Size[LanguageSet][Details.style][c] * Details.scaleX;
	else
		return Size[LanguageSet][Details.style][209] * Details.scaleX;
#else
	if (Details.bFontHalfTexture)
		c = FindNewCharacter(c);
	if (Details.proportional)
		return Size[Details.style][c] * Details.scaleX;
	else
		return Size[Details.style][209] * Details.scaleX;
#endif // MORE_LANGUAGES
}

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
		for (; (*s != ' ' || spaces) && *s != '\0'; s++) {
			if (*s == '~') {
				s++;
				while (*s != '~') s++;
				s++;
				if (*s == ' ' && !spaces)
					break;
			}
			w += GetCharacterSize(*s - ' ');
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
				s++;
				if(*s == ' ')
					break;
			}
	}
	return s;
}

#ifdef MORE_LANGUAGES
wchar*
CFont::ParseToken(wchar *s, bool japShit)
{
	s++;
	if ((Details.color.r || Details.color.g || Details.color.b) && !japShit) {
		wchar c = *s;
		if (IsJapanese())
			c &= 0x7FFF;
		switch (c) {
		case 'N':
		case 'n':
			NewLine = true;
			break;
		case 'b': SetColor(CRGBA(128, 167, 243, 255)); break;
		case 'g': SetColor(CRGBA(95, 160, 106, 255)); break;
		case 'h': SetColor(CRGBA(225, 225, 225, 255)); break;
		case 'l': SetColor(CRGBA(0, 0, 0, 255)); break;
		case 'p': SetColor(CRGBA(168, 110, 252, 255)); break;
		case 'r': SetColor(CRGBA(113, 43, 73, 255)); break;
		case 'w': SetColor(CRGBA(175, 175, 175, 255)); break;
		case 'y': SetColor(CRGBA(210, 196, 106, 255)); break;
		}
	} else if (IsJapanese()) {
		if ((*s & 0x7FFF) == 'N' || (*s & 0x7FFF) == 'n')
			NewLine = true;
	}
	while ((!IsJapanese() || (*s != JAP_TERMINATION)) && *s != '~') s++;
	return s + 1;
}
#else
wchar*
CFont::ParseToken(wchar *s)
{
	Details.anonymous_23 = 0;
	s++;
	if(Details.color.r || Details.color.g || Details.color.b)
		switch(*s){
		case 'B':
			Details.bBold = !Details.bBold;
		case 'N':
		case 'n':
			NewLine = 1;
			break;
		case 'b': SetColor(CRGBA(27, 89, 130, 255)); Details.anonymous_23 = 1; break;
		case 'f':
			Details.bFlash = !Details.bFlash;
			if (Details.bFlash)
				Details.color.a = 255;
			break;
		case 'g': SetColor(CRGBA(255, 150, 225, 255)); Details.anonymous_23 = 1; break;
		case 'h': SetColor(CRGBA(225, 225, 225, 255)); Details.anonymous_23 = 1; break;
		case 'l': SetColor(CRGBA(0, 0, 0, 255)); Details.anonymous_23 = 1; break;
		case 'o': SetColor(CRGBA(229, 125, 126, 255)); Details.anonymous_23 = 1; break;
		case 'p': SetColor(CRGBA(168, 110, 252, 255)); Details.anonymous_23 = 1; break;
		case 'q': SetColor(CRGBA(199, 144, 203, 255)); Details.anonymous_23 = 1; break;
		case 'r': SetColor(CRGBA(255, 150, 225, 255)); Details.anonymous_23 = 1; break;
		case 't': SetColor(CRGBA(86, 212, 146, 255)); Details.anonymous_23 = 1; break;
		case 'w': SetColor(CRGBA(175, 175, 175, 255)); Details.anonymous_23 = 1; break;
		case 'x': SetColor(CRGBA(132, 146, 197, 255)); Details.anonymous_23 = 1; break;
		case 'y': SetColor(CRGBA(255, 227, 79, 255)); Details.anonymous_23 = 1; break;
		}
	while(*s != '~') s++;
	s++;
	if (*s == '~')
		s = ParseToken(s);
	return s;
}
#endif

wchar*
CFont::ParseToken(wchar* str, CRGBA &color, bool &flash, bool &bold)
{
	wchar* v4; // eax
	wchar* result; // eax

	Details.anonymous_23 = 0;
	v4 = str + 1;
	if (Details.color.r || Details.color.g || Details.color.b)
	{
		switch (*v4)
		{
		case 'B':
			bold = !bold;
			break;
		case 'b':
			color.r = 27;
			color.g = 89;
			color.b = 130;
			break;
		case 'f':
			flash = !flash;
			break;
		case 'g':
			color.r = 255;
			color.g = 150;
			color.b = 225;
			break;
		case 'h':
			color.r = 225;
			color.g = 225;
			color.b = 225;
			break;
		case 'l':
			color.r = 0;
			color.g = 0;
			color.b = 0;
			break;
		case 'o':
			color.r = 229;
			color.g = 125;
			color.b = 126;
			break;
		case 'p':
			color.r = 168;
			color.g = 110;
			color.b = 252;
			break;
		case 'q':
			color.r = 199;
			color.g = 144;
			color.b = 203;
			break;
		case 'r':
			color.r = 255;
			color.g = 150;
			color.b = 225;
			break;
		case 't':
			color.r = 86;
			color.g = 212;
			color.b = 146;
			break;
		case 'w':
			color.r = 175;
			color.g = 175;
			color.b = 175;
			break;
		case 'x':
			color.r = 132;
			color.g = 146;
			color.b = 197;
			break;
		case 'y':
			color.r = 255;
			color.g = 227;
			color.b = 79;
			break;
		default:
			break;
		}
	}
	while (*v4 != '~')
		++v4;
	result = v4 + 1;
	if (*result == '~')
		result = CFont::ParseToken(result, color, flash, bold);
	return result;
}

void
CFont::DrawFonts(void)
{
	RenderFontBuffer();
}

void
CFont::RenderFontBuffer()
{
	int v0; // ebx
	//wchar_t* v1; // esi
	CFontRenderState* v2; // esi
	char v3; // al
	float v4; // ST04_4
	float v5; // ST04_4
	signed int v6; // eax
	float v7; // [esp+Ch] [ebp-24h]
	float v8; // [esp+10h] [ebp-20h]
	CRGBA v9; // [esp+1Ch] [ebp-14h]
	bool v10; // [esp+22h] [ebp-Eh]
	bool v11; // [esp+23h] [ebp-Dh]

	if (FontRenderStatePointer != FontRenderStateBuf) {
		v11 = false;
		v10 = false;
		Sprite[RenderState.FontStyle].SetRenderState();
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
		RenderState = *(CFontRenderState*)&FontRenderStateBuf[0];
		v7 = RenderState.fTextPosX;
		v8 = RenderState.fTextPosY;
		wchar* string = (wchar*)&FontRenderStateBuf[sizeof(CFontRenderState)];

		if (string < FontRenderStatePointer)
		{
			do
			{
				if (string[0] == '\0')
				{
					v2 = (CFontRenderState*)((uintptr)string + sizeof(CFontRenderState));
					if ((uintptr)v2 & 3)
						v2 = (CFontRenderState*)((uint8*)v2 + 2);
					if (v2 >= FontRenderStatePointer)
						break;

					RenderState = *v2;

					v7 = RenderState.fTextPosX;
					v8 = RenderState.fTextPosY;
				}
				if (string[0] == '~')
				{
					string = CFont::ParseToken(string, v9, v10, v11);
					//string = CFont::ParseToken(string);
					if (v10)
					{
						if (CTimer::GetTimeInMilliseconds() - Details.nFlashTimer > 300) {
							Details.bFlashState = !Details.bFlashState;
							Details.nFlashTimer = CTimer::GetTimeInMilliseconds();
						}
						Details.color.alpha = Details.bFlashState ? 0 : 255;
					}
					if (!RenderState.bIsShadow)
						RenderState.color = v9;
				}
				wchar v0 = string[0];
				//LOWORD(v0) = *v1;
				v0 -= 32;
				if (RenderState.bFontHalfTexture) 
					v0 = FindNewCharacter(v0); 
				else if (v0 > 155) 
					v0 = 0; 

				if (RenderState.fSlant != 0.0f)
					v8 = (RenderState.fSlantRefPointX - v7) * RenderState.fSlant + RenderState.fSlantRefPointY;
				CFont::PrintChar(v7, v8, v0);
				if (v11) {
					CFont::PrintChar(v7 + 1.0f, v8, v0);
					CFont::PrintChar(v7 + 2.0f, v8, v0);
					v7 += 2.0f;
				}
				if (CFont::RenderState.bProp == true)
					v6 = CFont::Size[RenderState.FontStyle][v0];
				else
					v6 = CFont::Size[RenderState.FontStyle][209];
				v7 = CFont::RenderState.fTextSizeX * v6 + v7;
				if (v0 == 0)
					v7 += CFont::RenderState.fExtraSpace;
				++string;
			} while (string < FontRenderStatePointer);
		}
		CSprite2d::RenderVertexBuffer();
		FontRenderStatePointer = FontRenderStateBuf;
	}
}


void
CFont::SetFontStyle(int16 style)
{
	if (style == FONT_HEADING)
	{
		Details.style = FONT_STANDARD;
		Details.bFontHalfTexture = true;
	}
	else
	{
		Details.style = style;
		Details.bFontHalfTexture = false;
	}
}

wchar CFont::FindNewCharacter(wchar c)
{
	if (c >= 16 && c <= 26)
		return c + 128;
	if (c >= 8 && c <= 9)
		return c + 86;
	if (c == 4)
		return c + 89;
	if (c == 7)
		return 206;
	if (c == 14)
		return 207;
	if (c >= 33 && c <= 58)
		return c + 122;
	if (c >= 65 && c <= 90)
		return c + 90;
	if (c >= 96 && c <= 118)
		return c + 85;
	if (c >= 119 && c <= 140)
		return c + 62;
	if (c >= 141 && c <= 142)
		return 204;
	if (c == 143)
		return 205;
	if (c == 1)
		return 208;
	return c;
}

wchar
CFont::character_code(uint8 c)
{
	if(c < 128)
		return c;
	return foreign_table[c-128];
}


void
CFont::SetScale(float x, float y)
{
#ifdef MORE_LANGUAGES
	/*if (IsJapanese()) {
		x *= 1.35f;
		y *= 1.25f;
	}*/
#endif
	Details.scaleX = x;
	Details.scaleY = y;
}

void
CFont::SetBackgroundColor(CRGBA col)
{
	Details.backgroundColor = col;
}

void
CFont::SetColor(CRGBA col)
{
	Details.color = col;
	if (Details.alphaFade < 255.0f)
		Details.color.a *= Details.alphaFade / 255.0f;
}

void
CFont::SetDropColor(CRGBA col)
{
	Details.dropColor = col;
	if (Details.alphaFade < 255.0f)
		Details.dropColor.a *= Details.alphaFade / 255.0f;
}
