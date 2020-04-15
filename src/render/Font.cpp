#include "common.h"
#include "patcher.h"
#include "Sprite2d.h"
#include "TxdStore.h"
#include "Font.h"

CFontDetails &CFont::Details = *(CFontDetails*)0x8F317C;
int16 &CFont::NewLine = *(int16*)0x95CC94;
#ifdef MORE_LANGUAGES
CSprite2d CFont::Sprite[4];
#else
CSprite2d *CFont::Sprite = (CSprite2d*)0x95CC04;
#endif

#ifdef MORE_LANGUAGES
uint8 CFont::LanguageSet = FONT_LANGSET_EFIGS;
int32 CFont::Slot = -1;
#define JAP_TERMINATION (0x8000 | '~')

int16 CFont::Size[2][3][193] = {
	{
#else
int16 CFont::Size[3][193] = {
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
	}
#endif
};

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
	Sprite[0].SetTexture("font2", "font2_mask");
	if (LanguageSet == FONT_LANGSET_JAPANESE) {
		Sprite[1].SetTexture("FONTJAP", "FONTJAP_mask");
		Sprite[3].SetTexture("FONTJAP", "FONTJAP_mask");
	}
	else
		Sprite[1].SetTexture("pager", "pager_mask");
	Sprite[2].SetTexture("font1", "font1_mask");
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
		if (LanguageSet == FONT_LANGSET_JAPANESE)
			Sprite[3].Delete();
		CTxdStore::PushCurrentTxd();
		CTxdStore::RemoveTxd(Slot);
		switch (set)
		{
		case FONT_LANGSET_EFIGS:
		default:
			CTxdStore::LoadTxd(Slot, "MODELS/FONTS.TXD");
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
	Sprite[2].Delete();
	if (LanguageSet == FONT_LANGSET_JAPANESE)
		Sprite[3].Delete();
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
	if (LanguageSet == FONT_LANGSET_JAPANESE)
		CSprite2d::GetBank(15, Sprite[3].m_pTexture);
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
	float xoff = c % 16;
	float yoff = c / 16;
	if (LanguageSet == FONT_LANGSET_JAPANESE && (Details.style == FONT_PAGER || Details.style == FONT_JAPANESE)) {
		w = 21.0f;
		xoff = (float)(c % 48);// *w / 1024.0f;
		yoff = c / 48;
	}

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
	}else if (LanguageSet == FONT_LANGSET_JAPANESE && (Details.style == FONT_PAGER || Details.style == FONT_JAPANESE)) {
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
	}
	else
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

bool CFont::IsJapanesePunctuation(wchar *a1)
{
	wchar v2;

	v2 = *a1;
	if (v2 != 0xE7
		&& v2 != 0x124
		&& v2 != 0x126
		&& v2 != 0x128
		&& v2 != 0x104
		&& v2 != ','
		&& v2 != '>'
		&& v2 != '!'
		&& v2 != 0x99
		&& v2 != '?'
		&& v2 != ':')
	{
		return false;
	}
	return true;
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

void
CFont::PrintString(float xstart, float ystart, wchar *s)
{
	/*
	if (1)
	{
		wchar* result; // eax
		__int16 numSpaces; // bx
		wchar* start; // ebp
		double v6; // st7
		float v7; // ST2C_4
		float v8; // ST2C_4
		double v9; // st5
		double v10; // st7
		double v11; // st5
		float v12; // ST10_4
		float v13; // ST00_4
		float v14; // ST34_4
		unsigned __int16* v15; // eax
		wchar* t; // esi
		unsigned __int16 v17; // ax
		double v18; // st7
		double v19; // st7
		float v20; // ST34_4
		double v21; // st7
		double v22; // st7
		double v23; // st7
		double xleft_d; // st6
		float xleft; // ST00_4
		float v26; // ST34_4
		float v27; // [esp+24h] [ebp-44h]
		float lineLength; // [esp+28h] [ebp-40h]
		float v29; // [esp+30h] [ebp-38h]
		float x; // [esp+40h] [ebp-28h]
		float y; // [esp+44h] [ebp-24h]
		char first; // [esp+4Bh] [ebp-1Dh]
		CRect v33; // [esp+4Ch] [ebp-1Ch]

		result = s;
		if (*s != '*')
		{
			if (CFont::Details.background == 1)
			{
				CFont::GetTextRect(&v33, xstart, ystart, s);
				CSprite2d::DrawRect(v33, CFont::Details.backgroundColor);
			}
			numSpaces = 0;
			lineLength = 0.0;
			start = s;
			first = 1;
			if (CFont::Details.centre != 1 && CFont::Details.rightJustify != 1)
				x = xstart;
			else
				x = 0.0;
			y = ystart;
			while (1)
			{
				while (1)
				{
					while (1)
					{
						result = s;
						if (!*s)
							return;// result;
						v27 = CFont::GetStringWidth(s, false);
						if (CFont::Details.centre == 1)
							v6 = CFont::Details.centreSize;
						else
							v6 = CFont::Details.rightJustify == 1 ? xstart - CFont::Details.rightJustifyWrap : CFont::Details.wrapX;
						v7 = v6;
						v8 = v7 - SCREEN_WIDTH * 0.0015625f * 21.0 * 2.0;
						if (x + v27 <= v8 || first)
							break;
						if (someJapCheck(s))
							--s;
						if (CFont::Details.justify != 1 || CFont::Details.centre)
							v9 = 0.0;
						else
							v9 = (CFont::Details.wrapX - lineLength) / (double)numSpaces;
						v10 = v9;
						if (CFont::Details.centre)
						{
							v11 = xstart - x * 0.5;
						}
						else if (CFont::Details.rightJustify)
						{
							v11 = xstart - x;
						}
						else
						{
							v11 = xstart;
						}
						v12 = v10;
						v13 = v11;
						CFont::PrintString(v13, y, start, s, v12, xstart);
						start = s;
						if (CFont::Details.centre != 1 && CFont::Details.rightJustify != 1)
							x = xstart;
						else
							x = 0.0;
						v14 = 32.0 * CFont::Details.scaleY * 0.3636363636363636 + 2.0 * CFont::Details.scaleY;
						numSpaces = 0;
						first = 1;
						y = v14 + y;
						lineLength = 0.0;
					}
					v15 = CFont::GetNextSpace(s);
					t = v15;
					v17 = *v15;
					if (!v17 || !t[1] && v17 == ' ')
						break;
					if (!first)
						++numSpaces;
					first = 0;
					v21 = CFont::GetStringWidth(s, 0);
					x = v21 + x;
					if (sub_511630(s))
						x = x + 21.0;
					s = t;
					v22 = CFont::GetCharacterSize(*t - 32);
					++s;
					x = v22 + x;
					lineLength = x;
					if (!*s)
					{
						v23 = CFont::GetStringWidth(s, 0);
						x = v23 + x;
						if (sub_511630(s))
							x = x + 21.0;
						if (CFont::Details.centre)
						{
							xleft_d = xstart - x * 0.5;
						}
						else if (CFont::Details.rightJustify)
						{
							xleft_d = xstart - x;
						}
						else
						{
							xleft_d = xstart;
						}
						xleft = xleft_d;
						if (CFont::PrintString(xleft, y, start, s, 0.0, xstart))
						{
							start = s;
							if (CFont::Details.centre != 1 && CFont::Details.rightJustify != 1)
								x = xstart;
							else
								x = 0.0;
							v26 = 32.0 * CFont::Details.scaleY * 0.3636363636363636 + 2.0 * CFont::Details.scaleY;
							numSpaces = 0;
							first = 1;
							y = v26 + y;
							lineLength = 0.0;
						}
					}
				}
				if (!t[1] && v17 == ' ')
					*t = 0;
				v18 = CFont::GetStringWidth(s, 0);
				s = t;
				x = v18 + x;
				if (CFont::Details.centre)
					break;
				if (CFont::Details.rightJustify)
				{
					v19 = xstart - x;
				LABEL_43:
					v29 = v19;
					goto LABEL_44;
				}
				v29 = xstart;
			LABEL_44:
				if (CFont::PrintString(v29, y, start, s, 0.0, xstart))
				{
					start = s;
					if (CFont::Details.centre != 1 && CFont::Details.rightJustify != 1)
						x = xstart;
					else
						x = 0.0;
					v20 = 32.0 * CFont::Details.scaleY * 0.3636363636363636 + 2.0 * CFont::Details.scaleY;
					numSpaces = 0;
					first = 1;
					y = v20 + y;
					lineLength = 0.0;
				}
			}
			v19 = xstart - x * 0.5;
			goto LABEL_43;
		}
		return;
	}*/

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
				if (LanguageSet == FONT_LANGSET_JAPANESE && (Details.style == FONT_JAPANESE || Details.style == FONT_PAGER))
					xend -= SCREEN_SCALE_X(21.0f * 2.0f);
				if(x + GetStringWidth(s) > xend && !first){
					if (LanguageSet == FONT_LANGSET_JAPANESE && IsJapanesePunctuation(s))
						s--;
					// flush line
					float spaceWidth = !Details.justify || Details.centre ? 0.0f :
						(Details.wrapX - lineLength) / numSpaces;
					float xleft = Details.centre ? xstart - x/2 :
					              Details.rightJustify ? xstart - x :
					              xstart;
					PrintString(xleft, y, start, s, spaceWidth, xstart);
					// reset things
					lineLength = 0.0f;
					numSpaces = 0;
					first = true;
					if(Details.centre || Details.rightJustify)
						x = 0.0f;
					else
						x = xstart;
					if (LanguageSet == FONT_LANGSET_JAPANESE && (Details.style == FONT_JAPANESE || Details.style == FONT_PAGER))
						y += 32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY;
					else
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
			if (LanguageSet == FONT_LANGSET_JAPANESE && (Details.style == FONT_JAPANESE || Details.style == FONT_PAGER) && IsAnsiCharacter(s))
				x += 21.0f;
			lineLength = x;
			s = t+1;
			if (LanguageSet == FONT_LANGSET_JAPANESE && (Details.style == FONT_JAPANESE || Details.style == FONT_PAGER) && !*s) {
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
		if (PrintString(xleft, y, start, s, 0.0f, xstart) && LanguageSet == FONT_LANGSET_JAPANESE && (Details.style == FONT_JAPANESE || Details.style == FONT_PAGER)) {
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
		PrintString(xleft, y, start, s, 0.0f)
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
	bool v14 = false;

#ifdef MORE_LANGUAGES
	if (IsJapanese()) {
		t = s;
		wchar unused;
		while (*t) {
			if (*t == JAP_TERMINATION || *t == '~')
				t = ParseToken(t, &unused, true);
			if (NewLine) {
				n++;
				NewLine = false;
				v14 = true;
			}
			t++;
		}
	}
#endif

	if (v14) n--;

	if(Details.centre || Details.rightJustify)
		x = 0.0f;
	else
		x = xstart;
	y = ystart;

	while(*s){
		float f = (Details.centre ? Details.centreSize : Details.wrapX);
		if (IsJapaneseFont())
			f -= SCREEN_SCALE_X(21.0f * 2.0f);

		if(x + GetStringWidth(s) > f){
			if (LanguageSet == FONT_LANGSET_JAPANESE)
			{
				if (IsJapanesePunctuation(s))
					s--;
			}
			// reached end of line
			if(Details.centre || Details.rightJustify)
				x = 0.0f;
			else
				x = xstart;
			n++;
			// Why even?
			if (LanguageSet == FONT_LANGSET_JAPANESE)
				y += 32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY;
			else
				y += 32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY;
		}else{
			// still space in current line
			t = GetNextSpace(s);
			if(*t == '\0'){
				// end of string
				x += GetStringWidth(s);
				if ((LanguageSet == FONT_LANGSET_JAPANESE) && IsAnsiCharacter(s))
					x += 21.0f;
				n++;
				s = t;
			}else{
				x += GetStringWidth(s);
				if ((LanguageSet == FONT_LANGSET_JAPANESE) && IsAnsiCharacter(s))
					x += 21.0f;
				s = t+1;
				x += GetCharacterSize(*t - ' ');
				if (LanguageSet == FONT_LANGSET_JAPANESE && !*s)
					n++;
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

	if (IsJapanese()) {
		numLines = GetNumberLines(xstart, ystart, s);
		//maxlength = Details.centreSize;
	}else{
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
	}

	if(Details.centre){
		if(Details.backgroundOnlyText){
			rect->left = xstart - maxlength/2 - 4.0f;
			rect->right = xstart + maxlength/2 + 4.0f;
			if (IsJapaneseFont()) {
				rect->bottom = (32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY) * numLines + ystart + (4.0f / 2.75f);
				rect->top = ystart - (4.0f / 2.75f);
			} else {
				rect->bottom = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f;
				rect->top = ystart - 2.0f;
			}
		}else{
			rect->left = xstart - Details.centreSize*0.5f - 4.0f;
			rect->right = xstart + Details.centreSize*0.5f + 4.0f;
			if (IsJapaneseFont()) {
				rect->bottom = (32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY) * numLines + ystart + (4.0f / 2.75f);
				rect->top = ystart - (4.0f / 2.75f);
			} else {
				rect->bottom = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f;
				rect->top = ystart - 2.0f;
			}
		}
	}else{
		rect->left = xstart - 4.0f;
		rect->right = Details.wrapX;
		// WTF?
		rect->bottom = ystart - 4.0f + 4.0f;
		if (IsJapaneseFont())
			rect->top = (32.0f * CFont::Details.scaleY / 2.75f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f + (4.0f / 2.75f);
		else
			rect->top = (32.0f * CFont::Details.scaleY * 0.5f + 2.0f * CFont::Details.scaleY) * numLines + ystart + 2.0f + 2.0f;
	}
}

#ifdef MORE_LANGUAGES
bool
CFont::PrintString(float x, float y, wchar *start, wchar *&end, float spwidth, float japX)
{
	wchar *s, c, unused;

	if (LanguageSet == FONT_LANGSET_JAPANESE) {
		float v14 = 0.0f;
		for (s = start; s < end; s++) {
			if (*s == JAP_TERMINATION || *s == '~')
				s = ParseToken(s, &unused, true);
			if (NewLine) {
				NewLine = false;
				break;
			}
			v14 += GetCharacterSize(*s - ' ');
		}
		s = start;
		if (Details.centre)
		{
			x = japX - v14 * 0.5;
		}
		else if (Details.rightJustify)
		{
			x = japX - v14;
		}
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
#endif

float
CFont::GetCharacterWidth(wchar c)
{
#ifdef MORE_LANGUAGES
	if (IsJapanese())
	{
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
		case FONT_HEADING:
			return Size[0][Details.style][c];
		}
	}

	else if (Details.proportional)
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

	if (IsJapanese())
	{
		if (!Details.proportional)
			return Size[0][Details.style][192] * Details.scaleX;
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
		case FONT_HEADING:
			return Size[0][Details.style][c] * Details.scaleX;
		}
	}
	else if(Details.proportional)
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

	if (LanguageSet == FONT_LANGSET_JAPANESE)
	{
		/*	unsigned __int16* v2; // ebx
			double v3; // st4
			int v4; // edx
			double v5; // st7
			unsigned __int16 v6; // ax
			unsigned __int16 v7; // ax
			double v8; // st3
			float v10; // [esp+0h] [ebp-20h]
			float v11; // [esp+4h] [ebp-1Ch]

			v2 = (unsigned __int16*)s;
			v10 = 0.0;
			do
			{
				if ((*v2 != ' ' || spaces) && *v2)
				{
					v3 = CFont::Details.scaleX;
					v4 = 193 * (signed __int16)CFont::Details.style;
					v5 = 29.4 * CFont::Details.scaleX;
					do
					{
						v6 = *v2;
						if (*v2 == 0x807Eu || v6 == '~')
						{
							do
								++v2;
							while (*v2 != 0x807Eu && *v2 != '~');
							++v2;
							goto LABEL_27;
						}
						v7 = v6 - ' ';
						if (CFont::Details.proportional == 1)
						{
							if (v7 > 94u && CFont::Details.style != FONT_HEADING && CFont::Details.style != FONT_BANK)
							{
								if (v7 >= 254u || CFont::Details.style != FONT_PAGER)
								{
									switch (CFont::Details.style)
									{
									case FONT_JAPANESE:
										v8 = v5;
										goto LABEL_25;
									case FONT_BANK:
										v8 = 10.0 * CFont::Details.scaleX;
										goto LABEL_25;
									case FONT_PAGER:
										v8 = 31.5 * CFont::Details.scaleX;
										goto LABEL_25;
									case FONT_HEADING:
										v11 = Size[0][Details.style][v7] * CFont::Details.scaleX;
										break;
									}
								}
								else
								{
									v11 = v5;
								}
								goto def_510DAD;
							}
							if (Details.style == FONT_JAPANESE)
								v8 = Size_jp[v7] * Details.scaleX;
							else
								v8 = CFont::Size[0][Details.style][v7] * v3;
						}
						else
						{
							v8 = CFont::Size[0][CFont::Details.style][192] * v3;
						}
					LABEL_25:
						v11 = v8;
					def_510DAD:
						v10 = v10 + v11;
					LABEL_27:
						if (*v2 != 0x807Eu && *v2 != '~')
							++v2;
					} while (*v2 == 0x807Eu || *v2 == '~');
				}
			} while (IsAnsiCharacter(v2));
			return v10;*/

		/*for (;; s++)
		{
			if (*s == '\0' && (!spaces || (*s == ' ' || !sub_511630(s) && *s != '~' && *s != JAP_TERMINATION)))
				return w;
			while (*s == '~' || *s == JAP_TERMINATION) {
				s++;
				while (*s != '~' && *s != JAP_TERMINATION) s++;
				s++;
				if (*s == ' ' && spaces)
					return w;
			}
			w += GetCharacterSize(*s - ' ');
			s++;
			if ((*s != '~' && *s != JAP_TERMINATION) && ((*s == ' ' || !sub_511630(s)) && !spaces))
				return w;
		}*/

		do
		{
			if ((*s != ' ' || spaces) && *s != '\0') {
				do {
					while (*s == '~' || *s == JAP_TERMINATION) {
						s++;
						while (!(*s == '~' || *s == JAP_TERMINATION)) s++;
						s++;
						//if (*s != JAP_TERMINATION && *s != '~')
						//	++s;
						//continue;
					}
					w += GetCharacterSize(*s - ' ');
					//if (*s != JAP_TERMINATION && *s != '~')
					++s;
				} while (*s == '~' || *s == JAP_TERMINATION);
			}
		} while (IsAnsiCharacter(s));//*/
	}
	else
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

wchar*
CFont::GetNextSpace(wchar *s)
{
	if (IsJapanese()) {
		unsigned __int16* v1; // ebx

		v1 = s;
		while (*v1 == ' ' || !*v1)
		{
		LABEL_11:
			if (!IsAnsiCharacter(v1))
				return v1;
		}
		while (1)
		{
			if (*v1 == 0x807Eu || *v1 == '~')
			{
				do
					++v1;
				while (*v1 != 0x807Eu && *v1 != '~');
				++v1;
				if (*v1 == ' ')
					return v1;
			}
			++v1;
			if (*v1 != 0x807Eu && *v1 != '~')
				goto LABEL_11;
		}

		if (*v1 == ' ' || !*v1)
		{
			if (IsAnsiCharacter(v1))
			{
				do
				{
					if (*v1 == 0x807Eu || *v1 == '~')
					{
						do
							++v1;
						while (*v1 != 0x807Eu && *v1 != '~');
						++v1;
						if (*v1 == ' ')
							return v1;
					}
					++v1;
					if (*v1 != 0x807Eu && *v1 != '~')
						if (!IsAnsiCharacter(v1))
							return v1;
				} while (*v1 == ' ' || !*v1);
			}
		}

		/*for (;; s++)
		{
			if (*s == '\0' || *s == ' ' || (!sub_511630(s) && *s != '~' && *s != JAP_TERMINATION))
				return s;
			if (*s == '~' || *s == JAP_TERMINATION) {
				s++;
				while (*s != '~' && *s != JAP_TERMINATION) s++;
				s++;
				if (*s == ' ' )
					return s;
			}
			//s++;
			//if (*s == ' ' || (!sub_511630(s) && *s != '~' && *s != JAP_TERMINATION))
			//	return s;
		}*/

		/*for (;*s != ' ' && *s != '\0' && sub_511630(s); s++) {
			while (*s == '~' || *s == JAP_TERMINATION) {
				s++;
				while (*s != '~' && *s != JAP_TERMINATION) s++;
				s++;
				if (*s == ' ' || ((*s != '~' && *s != JAP_TERMINATION) && !sub_511630(s)))
					return s;
			}
		}
		return s;*/
		/*while (*s == ' ' || !*s) {
		LABEL_11:
			if (!sub_511630(s))
				return s;
		}*/

		/*while (*s != ' ' && *s != '\0')
		{
			while (*s == JAP_TERMINATION || *s == '~')
			{
				do
					++s;
				while (*s != JAP_TERMINATION && *s != '~');
				++s;
				if (*s == ' ')
					return s;
			}
			++s;
			if (!sub_511630(s))
				return s;
			//if (*s != JAP_TERMINATION && *s != '~')
			//	goto LABEL_11;
		}
		return s;*/


		//for (; *s != ' ' && *s != '\0';) {
		//	if (!sub_511630(s))
		//		break;
		//	//for (; *s == '~' || *s == JAP_TERMINATION;s++) {
		//	//	s++;
		//	//	while (!(*s == '~' || *s == JAP_TERMINATION)) s++;
		//	//	s++;
		//	//	if (*s == ' ')
		//	//		return s;
		//	//	if (!sub_511630(s))
		//	//		return s;
		//	//}
		//	while (true)
		//	{
		//		if (*s == '~' || *s == JAP_TERMINATION) {
		//			s++;
		//			while (*s != '~' || *s == JAP_TERMINATION) s++;
		//			s++;
		//			if (*s == ' ')
		//				return s;
		//		}
		//		s++;
		//		if (!(*s == '~' || *s == JAP_TERMINATION))
		//			break;
		//	}
		//}
		//return s;


		for (;*s != ' ' && *s != '\0' && IsAnsiCharacter(s); s++ ) {
			if (*s == '~' || *s == JAP_TERMINATION)
			{
				s++;
				while (*s != '~' && *s != JAP_TERMINATION) s++;
				s++;
				if (*s == ' ' || ((*s != '~' && *s != JAP_TERMINATION) && !IsAnsiCharacter(s)))
					break;
			}
		}
	}
	else
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
CFont::ParseToken(wchar *s, wchar*, bool japShit)
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
#endif

void
CFont::DrawFonts(void)
{
	CSprite2d::DrawBank(Details.bank);
	CSprite2d::DrawBank(Details.bank+1);
	CSprite2d::DrawBank(Details.bank+2);
	if (IsJapanese())
		CSprite2d::DrawBank(Details.bank+3);
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
	/*if (LanguageSet == FONT_LANGSET_JAPANESE) {
		x *= 1.35f;
		y *= 1.25f;
	}*/
	Details.scaleX = x;
	Details.scaleY = y;
}

void
CFont::SetBackgroundColor(const CRGBA &col)
{
	Details.backgroundColor = col;
}

void
CFont::SetColor(const CRGBA &col)
{
	Details.color = col;
	if (Details.alphaFade < 255.0f)
		Details.color.a *= Details.alphaFade / 255.0f;
}

void
CFont::SetDropColor(const CRGBA &col)
{
	Details.dropColor = col;
	if (Details.alphaFade < 255.0f)
		Details.dropColor.a *= Details.alphaFade / 255.0f;
}

STARTPATCHES

	InjectHook(0x500A40, CFont::Initialise, PATCH_JUMP);
	InjectHook(0x500BA0, CFont::Shutdown, PATCH_JUMP);
	InjectHook(0x500BE0, CFont::InitPerFrame, PATCH_JUMP);
	InjectHook(0x500C30, CFont::PrintChar, PATCH_JUMP);
	InjectHook(0x500F50, (void (*)(float, float, wchar*))CFont::PrintString, PATCH_JUMP);
	InjectHook(0x501260, CFont::GetNumberLines, PATCH_JUMP);
	InjectHook(0x5013B0, CFont::GetTextRect, PATCH_JUMP);
	//InjectHook(0x501730, (void (*)(float, float, wchar*, wchar*, float))CFont::PrintString, PATCH_JUMP);
	InjectHook(0x5017E0, CFont::GetCharacterWidth, PATCH_JUMP);
	InjectHook(0x501840, CFont::GetCharacterSize, PATCH_JUMP);
	InjectHook(0x5018A0, CFont::GetStringWidth, PATCH_JUMP);
	InjectHook(0x501960, CFont::GetNextSpace, PATCH_JUMP);
	InjectHook(0x5019A0, CFont::ParseToken, PATCH_JUMP);
	InjectHook(0x501B50, CFont::DrawFonts, PATCH_JUMP);
	InjectHook(0x501E80, CFont::character_code, PATCH_JUMP);

	InjectHook(0x501B80, CFont::SetScale, PATCH_JUMP);
	InjectHook(0x501BA0, CFont::SetSlantRefPoint, PATCH_JUMP);
	InjectHook(0x501BC0, CFont::SetSlant, PATCH_JUMP);
	InjectHook(0x501BD0, CFont::SetColor, PATCH_JUMP);
	InjectHook(0x501C60, CFont::SetJustifyOn, PATCH_JUMP);
	InjectHook(0x501C80, CFont::SetJustifyOff, PATCH_JUMP);
	InjectHook(0x501C90, CFont::SetCentreOn, PATCH_JUMP);
	InjectHook(0x501CB0, CFont::SetCentreOff, PATCH_JUMP);
	InjectHook(0x501CC0, CFont::SetWrapx, PATCH_JUMP);
	InjectHook(0x501CD0, CFont::SetCentreSize, PATCH_JUMP);
	InjectHook(0x501CE0, CFont::SetBackgroundOn, PATCH_JUMP);
	InjectHook(0x501CF0, CFont::SetBackgroundOff, PATCH_JUMP);
	InjectHook(0x501D00, CFont::SetBackgroundColor, PATCH_JUMP);
	InjectHook(0x501D30, CFont::SetBackGroundOnlyTextOn, PATCH_JUMP);
	InjectHook(0x501D40, CFont::SetBackGroundOnlyTextOff, PATCH_JUMP);
	InjectHook(0x501D50, CFont::SetRightJustifyOn, PATCH_JUMP);
	InjectHook(0x501D70, CFont::SetRightJustifyOff, PATCH_JUMP);
	InjectHook(0x501D90, CFont::SetPropOff, PATCH_JUMP);
	InjectHook(0x501DA0, CFont::SetPropOn, PATCH_JUMP);
	InjectHook(0x501DB0, CFont::SetFontStyle, PATCH_JUMP);
	InjectHook(0x501DC0, CFont::SetRightJustifyWrap, PATCH_JUMP);
	InjectHook(0x501DD0, CFont::SetAlphaFade, PATCH_JUMP);
	InjectHook(0x501DE0, CFont::SetDropColor, PATCH_JUMP);
	InjectHook(0x501E70, CFont::SetDropShadowPosition, PATCH_JUMP);

ENDPATCHES
