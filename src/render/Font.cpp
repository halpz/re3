#include "common.h"

#include "Sprite2d.h"
#include "TxdStore.h"
#include "Font.h"

CFontDetails CFont::Details;
int16 CFont::NewLine;
CSprite2d CFont::Sprite[MAX_FONTS];

#ifdef MORE_LANGUAGES
uint8 CFont::LanguageSet = FONT_LANGSET_EFIGS;
int32 CFont::Slot = -1;

int16 CFont::Size[LANGSET_MAX][MAX_FONTS][193] = {
	{
#else
int16 CFont::Size[MAX_FONTS][193] = {
#endif
		{
		13, 12, 31, 35, 23, 35, 31,  9, 14, 15, 25, 30, 11, 17, 13, 31,
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
	}
#else
	CTxdStore::LoadTxd(slot, "MODELS/FONTS.TXD");
#endif
	CTxdStore::AddRef(slot);
	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(slot);
	Sprite[0].SetTexture("font2", "font2_mask");
	Sprite[1].SetTexture("pager", "pager_mask");
	Sprite[2].SetTexture("font1", "font1_mask");
	SetScale(1.0f, 1.0f);
	SetSlantRefPoint(SCREEN_WIDTH, 0.0f);
	SetSlant(0.0f);
	SetColor(CRGBA(0xFF, 0xFF, 0xFF, 0));
	SetJustifyOff();
	SetCentreOff();
	SetWrapx(640.0f);
	SetCentreSize(640.0f);
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
		}
		CTxdStore::SetCurrentTxd(Slot);
		Sprite[0].SetTexture("font2", "font2_mask");
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
	Sprite[2].Delete();
#ifdef MORE_LANGUAGES
	CTxdStore::RemoveTxdSlot(Slot);
	Slot = -1;
#else
	CTxdStore::RemoveTxdSlot(CTxdStore::FindTxdSlot("fonts"));
#endif
}

void
CFont::InitPerFrame(void)
{
	Details.bank = CSprite2d::GetBank(30, Sprite[0].m_pTexture);
	CSprite2d::GetBank(15, Sprite[1].m_pTexture);
	CSprite2d::GetBank(15, Sprite[2].m_pTexture);
	SetDropShadowPosition(0);
	NewLine = 0;
}

void
CFont::PrintChar(float x, float y, wchar c)
{
	if(x <= 0.0f || x > SCREEN_WIDTH ||
	   y <= 0.0f || y > SCREEN_HEIGHT)	// BUG: game uses SCREENW again
		return;

	float w = GetCharacterWidth(c) / 32.0f;
	float xoff = c & 0xF;
	float yoff = c >> 4;

	if(Details.style == FONT_BANK || Details.style == FONT_HEADING){
		if(Details.dropShadowPosition != 0){
			CSprite2d::AddSpriteToBank(Details.bank + Details.style,	// BUG: game doesn't add bank
				CRect(x + SCREEN_SCALE_X(Details.dropShadowPosition),
				      y + SCREEN_SCALE_Y(Details.dropShadowPosition),
				      x + SCREEN_SCALE_X(Details.dropShadowPosition) + 32.0f * Details.scaleX * 1.0f,
				      y + SCREEN_SCALE_Y(Details.dropShadowPosition) + 40.0f * Details.scaleY * 0.5f),
				Details.dropColor,
				xoff/16.0f,                 yoff/12.8f,
				(xoff+1.0f)/16.0f - 0.001f, yoff/12.8f,
				xoff/16.0f,                 (yoff+1.0f)/12.8f,
				(xoff+1.0f)/16.0f - 0.001f, (yoff+1.0f)/12.8f - 0.0001f);
		}
		CSprite2d::AddSpriteToBank(Details.bank + Details.style,	// BUG: game doesn't add bank
			CRect(x, y,
			      x + 32.0f * Details.scaleX * 1.0f,
			      y + 40.0f * Details.scaleY * 0.5f),
			Details.color,
			xoff/16.0f,                 yoff/12.8f,
			(xoff+1.0f)/16.0f - 0.001f, yoff/12.8f,
			xoff/16.0f,                 (yoff+1.0f)/12.8f - 0.002f,
			(xoff+1.0f)/16.0f - 0.001f, (yoff+1.0f)/12.8f - 0.002f);
	}else{
		CSprite2d::AddSpriteToBank(Details.bank + Details.style,	// BUG: game doesn't add bank
			CRect(x, y,
			      x + 32.0f * Details.scaleX * w,
			      y + 32.0f * Details.scaleY * 0.5f),
			Details.color,
			xoff/16.0f,               yoff/16.0f,
			(xoff+w)/16.0f,           yoff/16.0f,
			xoff/16.0f,               (yoff+1.0f)/16.0f,
			(xoff+w)/16.0f - 0.0001f, (yoff+1.0f)/16.0f - 0.0001f);
	}
}

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
				int xend = Details.centre ? Details.centreSize :
				           Details.rightJustify ? xstart - Details.rightJustifyWrap :
				           Details.wrapX;
				if(x + GetStringWidth(s) > xend && !first){
					// flush line
					float spaceWidth = !Details.justify || Details.centre ? 0.0f :
						(Details.wrapX - lineLength) / numSpaces;
					float xleft = Details.centre ? xstart - x/2 :
					              Details.rightJustify ? xstart - x :
					              xstart;
					PrintString(xleft, y, start, s, spaceWidth);
					// reset things
					lineLength = 0.0f;
					numSpaces = 0;
					first = true;
					if(Details.centre || Details.rightJustify)
						x = 0.0f;
					else
						x = xstart;
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
			lineLength = x;
			s = t+1;
		}
		// print rest
		if(t[0] == ' ' && t[1] == '\0')
			t[0] = '\0';
		x += GetStringWidth(s);
		s = t;
		float xleft = Details.centre ? xstart - x/2 :
		              Details.rightJustify ? xstart - x :
		              xstart;
		PrintString(xleft, y, start, s, 0.0f);
	}
}

int
CFont::GetNumberLines(float xstart, float ystart, wchar *s)
{
	int n;
	float x, y;
	wchar *t;

	n = 0;
	if(Details.centre || Details.rightJustify)
		x = 0.0f;
	else
		x = xstart;
	y = ystart;

	while(*s){
		if(x + GetStringWidth(s) > (Details.centre ? Details.centreSize : Details.wrapX)){
			// reached end of line
			if(Details.centre || Details.rightJustify)
				x = 0.0f;
			else
				x = xstart;
			n++;
			// Why even?
			y += 32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY;
		}else{
			// still space in current line
			t = GetNextSpace(s);
			if(*t == '\0'){
				// end of string
				x += GetStringWidth(s);
				n++;
				s = t;
			}else{
				x += GetStringWidth(s);
				x += GetCharacterSize(*t - ' ');
				s = t+1;
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

	if(Details.centre){
		if(Details.backgroundOnlyText){
			rect->left = xstart - maxlength/2 - 4.0f;
			rect->right = xstart + maxlength/2 + 4.0f;
			rect->bottom = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines +
				ystart + 2.0f;
			rect->top = ystart - 2.0f;
		}else{
			rect->left = xstart - Details.centreSize*0.5f - 4.0f;
			rect->right = xstart + Details.centreSize*0.5f + 4.0f;
			rect->bottom = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines +
				ystart + 2.0f;
			rect->top = ystart - 2.0f;
		}
	}else{
		rect->left = xstart - 4.0f;
		rect->right = Details.wrapX;
		// WTF?
		rect->bottom = ystart - 4.0f + 4.0f;
		rect->top = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines +
				ystart + 2.0f + 2.0f;
	}
}

void
CFont::PrintString(float x, float y, wchar *start, wchar *end, float spwidth)
{
	wchar *s, c, unused;

	for(s = start; s < end; s++){
		if(*s == '~')
			s = ParseToken(s, &unused);
		c = *s - ' ';
		if(Details.slant != 0.0f)
			y = (Details.slantRefX - x)*Details.slant + Details.slantRefY;
		PrintChar(x, y, c);
		x += GetCharacterSize(c);
		if(c == 0)	// space
			x += spwidth;
	}
}

float
CFont::GetCharacterWidth(wchar c)
{
#ifdef MORE_LANGUAGES
	if (Details.proportional)
		return Size[LanguageSet][Details.style][c];
	else
		return Size[LanguageSet][Details.style][192];
#else
	if (Details.proportional)
		return Size[Details.style][c];
	else
		return Size[Details.style][192];
#endif // MORE_LANGUAGES
}

float
CFont::GetCharacterSize(wchar c)
{
#ifdef MORE_LANGUAGES
	if(Details.proportional)
		return Size[LanguageSet][Details.style][c] * Details.scaleX;
	else
		return Size[LanguageSet][Details.style][192] * Details.scaleX;
#else
	if (Details.proportional)
		return Size[Details.style][c] * Details.scaleX;
	else
		return Size[Details.style][192] * Details.scaleX;
#endif // MORE_LANGUAGES
}

float
CFont::GetStringWidth(wchar *s, bool spaces)
{
	float w;

	w = 0.0f;
	for(; (*s != ' ' || spaces) && *s != '\0'; s++){
		if(*s == '~'){
			s++;
			while(*s != '~') s++;
			s++;
			if(*s == ' ' && !spaces)
				break;
		}
		w += GetCharacterSize(*s - ' ');
	}
	return w;
}

wchar*
CFont::GetNextSpace(wchar *s)
{
	for(; *s != ' ' && *s != '\0'; s++)
		if(*s == '~'){
			s++;
			while(*s != '~') s++;
			s++;
			if(*s == ' ')
				break;
		}
	return s;
}

wchar*
CFont::ParseToken(wchar *s, wchar*)
{
	s++;
	if(Details.color.r || Details.color.g || Details.color.b)
		switch(*s){
		case 'N':
		case 'n':
			NewLine = 1;
			break;
		case 'b': SetColor(CRGBA(0x80, 0xA7, 0xF3, 0xFF)); break;
		case 'g': SetColor(CRGBA(0x5F, 0xA0, 0x6A, 0xFF)); break;
		case 'h': SetColor(CRGBA(0xE1, 0xE1, 0xE1, 0xFF)); break;
		case 'l': SetColor(CRGBA(0x00, 0x00, 0x00, 0xFF)); break;
		case 'p': SetColor(CRGBA(0xA8, 0x6E, 0xFC, 0xFF)); break;
		case 'r': SetColor(CRGBA(0x71, 0x2B, 0x49, 0xFF)); break;
		case 'w': SetColor(CRGBA(0xAF, 0xAF, 0xAF, 0xFF)); break;
		case 'y': SetColor(CRGBA(0xD2, 0xC4, 0x6A, 0xFF)); break;
		}
	while(*s != '~') s++;
	return s+1;
}

void
CFont::DrawFonts(void)
{
	CSprite2d::DrawBank(Details.bank);
	CSprite2d::DrawBank(Details.bank+1);
	CSprite2d::DrawBank(Details.bank+2);
}

wchar
CFont::character_code(uint8 c)
{
	if(c < 128)
		return c;
	return foreign_table[c-128];
}
