#include "common.h"

#include "Sprite2d.h"
#include "TxdStore.h"
#include "Font.h"
#ifdef BUTTON_ICONS
#include "FileMgr.h"
#endif
#include "Timer.h"

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

#ifdef MORE_LANGUAGES
uint8 CFont::LanguageSet = FONT_LANGSET_EFIGS;
int32 CFont::Slot = -1;
#define JAP_TERMINATION (0x8000 | '~')

int16 CFont::Size[LANGSET_MAX][MAX_FONTS][210] = {
	{
#else
int16 CFont::Size[MAX_FONTS][210] = {
#endif
	{
		//FONT2 EFIGS
		//SPC,!,         $,  %,  &,  ',  [,  ],      +,  ,   -,  .,    
		12, 9,  22, 17, 19, 19, 25, 4,  33, 33, 25, 35, 11, 10,  6, 33,
		//0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  :,                 ??,
		18, 10, 17, 17, 17, 17, 17, 15, 12, 16,  5, 30, 30, 30, 30, 30,
		//   A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,
		12, 16, 19, 16, 19, 18, 18, 17, 22, 11, 17, 18, 18, 30, 22, 19,
		//P, Q,  R,  S,  T,  U,  V,  W,  X,  Y,  Z, ??, ??, ??,  ¡,  \,
		#ifdef FIX_BUGS
		22, 19, 19, 20, 18, 19, 19, 29, 19, 18, 19, 19, 33, 33, 10, 19,
		#else
		22, 19, 19, 20, 18, 19, 19, 29, 19, 18, 19, 19, 33, 33, 19, 19,
		#endif
		//??,a,  b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m,  n,  o,
		12, 14, 11, 11, 16, 11, 12, 14, 14, 10, 13, 12, 10, 19, 18, 12,
		//p, q,  r,  s,  t,  u,  v,  w,  x,  y,  z, ??, ??, ??, ??, ??,
		16, 13, 13, 11, 12, 15, 12, 15, 13, 12, 12, 37, 33, 37, 35, 37,
		//À, Á,  Â,  Ä,  Æ,  Ç,  È,  É,  Ê,  Ë,  Ì,  Í,  Î,  Ï,  Ò,  Ó,
		16, 16, 16, 16, 33, 17, 18, 18, 18, 18, 11, 11, 11, 11, 19, 19,
		//Ô, Ö,  Ù,  Ú,  Û,  Ü,  ß,  à,  á,  â,  ä,  æ,  ç,  è,  é,  ê,
		19, 19, 19, 19, 19, 19, 15, 14, 14, 14, 14, 20, 14, 11, 11, 11,
		//ë, ì,  í,  î,  ï,  ò,  ó,  ô,  ö,  ù,  ú,  û,  ü,  Ñ,  ñ,  ¿,
		#ifdef FIX_BUGS
		11, 10, 10, 10, 10, 12, 12, 12, 12, 15, 15, 15, 15, 22, 18, 21,
		#else
		11, 10, 10, 10, 10, 12, 12, 12, 12, 15, 15, 15, 15, 24, 18, 21,
		#endif
		//i,BLANKS
		10, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
		19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
		19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
		19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
		//space, unprop
		19, 16
	},
	{
		//FONT1 EFIGS
		//Characters with a '2' refer to the Pricedown font.
		//Characters that are referred as '*I' are characters that contain icons for PS2/XBOX, but contain regular characters on PC
		//in order to display them properly in the Keyboard controls menu.
		//!2,!, *I,(R),  $,  %,  &,  ',  [,  ], *I,  +,  ,   -,  ., *I,
		15,  7, 31, 25, 20, 23, 21,  7, 11, 10, 26, 14,  6, 12,  6, 26,
		//0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  :, *I, *I, *I, *I,  ?,
		20,  7, 20, 20, 21, 20, 20, 19, 21, 20,  8, 30, 24, 30, 24, 19,
		//TM,A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,
		20, 22, 22, 21, 22, 18, 18, 22, 22,  9, 14, 21, 18, 27, 21, 24,
		//P, Q,  R,  S,  T,  U,  V,  W,  X,  Y,  Z, *I,  \, *I,  ¡,  °,
		#ifdef FIX_BUGS
		22, 22, 23, 20, 19, 23, 22, 31, 23, 23, 21, 25, 13, 30,  7, 19,
		#else
		22, 22, 23, 20, 19, 23, 22, 31, 23, 23, 21, 25, 13, 30, 10, 19,
		#endif
		//(C),a, b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m,  n,  o,
		10, 17, 17, 16, 17, 17, 11, 17, 17,  7,  7, 18,  7, 25, 17, 17,
		//p, q,  r,  s,  t,  u,  v,  w,  x,  y,  z, *I, *I, $2, (2, )2,
		17, 17, 11, 17, 11, 17, 18, 25, 19, 18, 17, 28, 26, 20, 15, 15,
		//À, Á,  Â,  Ä,  Æ,  Ç,  È,  É,  Ê,  Ë,  Ì,  Í,  Î,  Ï,  Ò,  Ó,
		20, 20, 20, 20, 29, 22, 19, 19, 19, 19,  9,  9,  9,  9, 23, 23,
		//Ô, Ö,  Ù,  Ú,  Û,  Ü,  ß,  à,  á,  â,  ä,  æ,  ç,  è,  é,  ê,
		23, 23, 24, 24, 24, 24, 20, 19, 17, 17, 17, 30, 16, 17, 17, 17,
		//ë, ì,  í,  î,  ï,  ò,  ó,  ô,  ö,  ù,  ú,  û,  ü,  Ñ,  ñ,  ¿,
		#ifdef FIX_BUGS
		17, 11, 11, 15, 12, 17, 17, 17, 17, 17, 17, 17, 17, 21, 17, 19,
		#else
		17, 11, 11, 15, 12, 17, 17, 17, 17, 17, 17, 17, 17, 19, 20, 20,
		#endif
		//02,12,22, 32, 42, 52, 62, 72, 82, 92, :2, A2, B2, C2, D2, E2,
		20, 18, 19, 19, 21, 19, 19, 19, 19, 19, 16, 19, 19, 19, 20, 19,
		//F2,G2,H2, I2, J2, K2, L2, M2, N2, O2, P2, Q2, R2, S2, T2, U2,
		16, 19, 19,  9, 19, 20, 14, 29, 19, 19, 19, 19, 19, 19, 21, 19,
		//V2,W2,X2, Y2, Z2, À2, Á2, Â2, Ä2, Æ2, Ç2, È2, É2, Ê2, Ë2, Ì2,
		20, 32, 20, 19, 19, 19, 19, 19, 19, 29, 19, 19, 19, 19, 19,  9,
		//Í2,Î2,Ï2, Ò2, Ó2, Ô2, Ö2, Ù2, Ú2, Û2, Ü2, ß2, Ñ2, ¿2, '2, .2,
		#ifdef FIX_BUGS
		 9,  9,  9, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 10,  9,
		#else
		 9,  9,  9, 19, 19, 19, 19, 19, 19, 19, 19, 19, 21, 21, 10,  9,
		#endif
		//space, unprop
		10, 20
	}

#ifdef MORE_LANGUAGES
	},
	{
        {
			5,  9,  9,  0,  17, 17, 23, 3,  21, 18, 0,  8,  3,  8,  3,  0,
			16, 9,  16, 16, 15, 19, 15, 14, 17, 17, 4,  4,  0,  0,  0,  17,
			19, 17, 19, 15, 21, 18, 19, 16, 21, 13, 15, 21, 20, 28, 21, 18,
			22, 17, 21, 20, 18, 18, 20, 26, 22, 18, 18, 0,  8,  0,  9,  8,
			0,  14, 11, 12, 16, 11, 13, 13, 15, 10, 14, 15, 11, 21, 17, 10,
			20, 15, 12, 12, 16, 17, 13, 16, 13, 21, 11, 0,  0,  0,  0,  0, 
			20, 19, 19, 22, 27, 15, 18, 18, 20, 26, 21, 23, 17, 22, 21, 17,
			26, 25, 26, 17, 20, 26, 17, 16, 11, 12, 13, 21, 11, 17, 17, 12,
			21, 17, 17, 15, 24, 16, 10, 20, 23, 16, 7,  9,  16, 23, 12, 11,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  19,
			19, 16
		},
        {
			11, 5,  10, 15, 19, 22, 20, 5,  9,  8,  11, 12, 5,  12, 6,  12,
			19, 5,  18, 19, 20, 18, 19, 18, 20, 19, 5,  6,  26, 12, 30, 19,
			23, 21, 20, 20, 20, 16, 16, 21, 19, 5,  13, 19, 16, 24, 20, 21,
			20, 21, 20, 19, 17, 20, 21, 30, 22, 21, 20, 25, 13, 30,  5,  9,
			10, 15, 15, 14, 15, 16, 10, 15, 15, 5,  5,  15, 5,  23, 15, 16,
			15, 15, 9,  16, 10, 15, 17, 24, 18, 15, 15, 27, 5,  19, 2,  2, 
			20, 20, 16, 23, 30, 19, 20, 20, 21, 24, 19, 19, 20, 23, 22, 19,
			27, 29, 25, 20, 20, 28, 24, 16, 16, 14, 19, 25, 16, 16, 16, 17,
			19, 16, 16, 17, 25, 19, 15, 23, 26, 21, 16, 14, 22, 20, 16, 19,
			15, 14, 15, 16, 17, 15, 15, 15, 15, 15, 7,  15, 15, 15, 15, 15,
			13, 15, 15, 7,  15, 16, 13, 23, 15, 15, 15, 15, 15, 15, 17, 15,
			16, 24, 17, 17, 17, 15, 15, 13, 20, 23, 15, 17, 17, 16, 24, 15,
			15, 15, 23, 18, 15, 23, 26, 23, 16, 15, 23, 15, 15, 19, 2,  2,
			10, 20
		},
	},	
	{
		{
			//FONT2 EFIGS
			//SPC,!,         $,  %,  &,  ',  [,  ],      +,  ,   -,  .,    
			12, 9,  22, 17, 19, 19, 25, 4,  33, 33, 25, 35, 11, 10,  6, 33,
			//0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  :,                 ??,
			18, 10, 17, 17, 17, 17, 17, 15, 12, 16,  5, 30, 30, 30, 30, 30,
			//   A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,
			12, 16, 19, 16, 19, 18, 18, 17, 22, 11, 17, 18, 18, 30, 22, 19,
			//P, Q,  R,  S,  T,  U,  V,  W,  X,  Y,  Z, ??, ??, ??,  ¡,  \,
			22, 19, 19, 20, 18, 19, 19, 29, 19, 18, 19, 19, 33, 33, 10, 19,
			//??,a,  b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m,  n,  o,
			12, 14, 11, 11, 16, 11, 12, 14, 14, 10, 13, 12, 10, 19, 18, 12,
			//p, q,  r,  s,  t,  u,  v,  w,  x,  y,  z, ??, ??, ??, ??, ??,
			16, 13, 13, 11, 12, 15, 12, 15, 13, 12, 12, 37, 33, 37, 35, 37,
			//À, Á,  Â,  Ä,  Æ,  Ç,  È,  É,  Ê,  Ë,  Ì,  Í,  Î,  Ï,  Ò,  Ó,
			16, 16, 16, 16, 33, 17, 18, 18, 18, 18, 11, 11, 11, 11, 19, 19,
			//Ô, Ö,  Ù,  Ú,  Û,  Ü,  ß,  à,  á,  â,  ä,  æ,  ç,  è,  é,  ê,
			19, 19, 19, 19, 19, 19, 15, 14, 14, 14, 14, 20, 14, 11, 11, 11,
			//ë, ì,  í,  î,  ï,  ò,  ó,  ô,  ö,  ù,  ú,  û,  ü,  Ñ,  ñ,  ¿,
			11, 10, 10, 10, 10, 12, 12, 12, 12, 15, 15, 15, 15, 22, 18, 21,
			//i,BLANKS
			10, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
			//space, unprop
			19, 16
		},
		{
			//FONT1 EFIGS
			//Characters with a '2' refer to the Pricedown font.
			//Characters that are referred as '*I' are characters that contain icons for PS2/XBOX, but contain regular characters on PC
			//in order to display them properly in the Keyboard controls menu.
			//!2,!, *I,(R),  $,  %,  &,  ',  [,  ], *I,  +,  ,   -,  ., *I,
			15,  7, 31, 25, 20, 23, 21,  7, 11, 10, 26, 14,  6, 12,  6, 26,
			//0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  :, *I, *I, *I, *I,  ?,
			20,  7, 20, 20, 21, 20, 20, 19, 21, 20,  8, 30, 24, 30, 24, 19,
			//TM,A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L,  M,  N,  O,
			20, 22, 22, 21, 22, 18, 18, 22, 22,  9, 14, 21, 18, 27, 21, 24,
			//P, Q,  R,  S,  T,  U,  V,  W,  X,  Y,  Z, *I,  \, *I,  ¡,  °,
			22, 22, 23, 20, 19, 23, 22, 31, 23, 23, 21, 25, 13, 30,  7, 19,
			//(C),a, b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m,  n,  o,
			10, 17, 17, 16, 17, 17, 11, 17, 17,  7,  7, 18,  7, 25, 17, 17,
			//p, q,  r,  s,  t,  u,  v,  w,  x,  y,  z, *I, *I, $2, (2, )2,
			17, 17, 11, 17, 11, 17, 18, 25, 19, 18, 17, 28, 26, 20, 15, 15,
			//À, Á,  Â,  Ä,  Æ,  Ç,  È,  É,  Ê,  Ë,  Ì,  Í,  Î,  Ï,  Ò,  Ó,
			20, 20, 20, 20, 29, 22, 19, 19, 19, 19,  9,  9,  9,  9, 23, 23,
			//Ô, Ö,  Ù,  Ú,  Û,  Ü,  ß,  à,  á,  â,  ä,  æ,  ç,  è,  é,  ê,
			23, 23, 24, 24, 24, 24, 20, 19, 17, 17, 17, 30, 16, 17, 17, 17,
			//ë, ì,  í,  î,  ï,  ò,  ó,  ô,  ö,  ù,  ú,  û,  ü,  Ñ,  ñ,  ¿,
			17, 11, 11, 15, 12, 17, 17, 17, 17, 17, 17, 17, 17, 21, 17, 19,
			//02,12,22, 32, 42, 52, 62, 72, 82, 92, :2, A2, B2, C2, D2, E2,
			20, 18, 19, 19, 21, 19, 19, 19, 19, 19, 16, 19, 19, 19, 20, 19,
			//F2,G2,H2, I2, J2, K2, L2, M2, N2, O2, P2, Q2, R2, S2, T2, U2,
			16, 19, 19,  9, 19, 20, 14, 29, 19, 19, 19, 19, 19, 19, 21, 19,
			//V2,W2,X2, Y2, Z2, À2, Á2, Â2, Ä2, Æ2, Ç2, È2, É2, Ê2, Ë2, Ì2,
			20, 32, 20, 19, 19, 19, 19, 19, 19, 29, 19, 19, 19, 19, 19,  9,
			//Í2,Î2,Ï2, Ò2, Ó2, Ô2, Ö2, Ù2, Ú2, Û2, Ü2, ß2, Ñ2, ¿2, '2, .2,
			 9,  9,  9, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 10,  9,
			//space, unprop
			10, 20
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
	CTxdStore::PopCurrentTxd();

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
		if (IsJapanese())
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
		case FONT_LANGSET_JAPANESE:
			CTxdStore::LoadTxd(Slot, "MODELS/FONTS_J.TXD");
			break;
		}
		CTxdStore::SetCurrentTxd(Slot);
		Sprite[0].SetTexture("font2", "font2_mask");
		if (set == FONT_LANGSET_JAPANESE) {
			Sprite[2].SetTexture("FONTJAP", "FONTJAP_mask");
		}
		Sprite[1].SetTexture("font1", "font1_mask");
		CTxdStore::PopCurrentTxd();
	}
	LanguageSet = set;
}
#endif

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

	if(RenderState.style == FONT_BANK || RenderState.style == FONT_STANDARD){
		if (bDontPrint) return;
		if (RenderState.slant == 0.0f) {
#ifdef FIX_BUGS
			if (c < 192) {
#else
			if (c < 193) {
#endif
				CSprite2d::AddToBuffer(
					CRect(x, y,
						x + 32.0f * RenderState.scaleX * 1.0f,
						y + 40.0f * RenderState.scaleY * 0.5f),
					RenderState.color,
					xoff / 16.0f, yoff / 12.8f + 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f,
					xoff / 16.0f, (yoff + 1.0f) / 12.8f - 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f - 0.0021f);
			} else {
				CSprite2d::AddToBuffer(
					CRect(x, y,
						x + 32.0f * RenderState.scaleX * 1.0f,
						y + 33.0f * RenderState.scaleY * 0.5f),
					RenderState.color,
					xoff / 16.0f, yoff / 12.8f + 0.0021f,
					(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f,
					xoff / 16.0f, (yoff + 1.0f) / 12.8f - 0.017f,
					(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f - 0.017f);
			}
		} else
			CSprite2d::AddToBuffer(
				CRect(x, y,
					x + 32.0f * RenderState.scaleX * 1.0f,
					y + 40.0f * RenderState.scaleY * 0.5f),
				RenderState.color,
				xoff / 16.0f, yoff / 12.8f + 0.00055f,
				(xoff + 1.0f) / 16.0f - 0.001f, yoff / 12.8f + 0.0021f + 0.01f,
				xoff / 16.0f, (yoff + 1.0f) / 12.8f - 0.009f,
				(xoff + 1.0f) / 16.0f - 0.001f, (yoff + 1.0f) / 12.8f - 0.0021f + 0.01f);
#ifdef MORE_LANGUAGES
	/*}else if (IsJapaneseFont()) {
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
			xoff * w / 1024.0f + (1.0f / 48.0f) - 0.001f, (yoff + 1.0f) / 25.6f - 0.0001f);*/
#endif
	} else {
		if (bDontPrint) return;
		CSprite2d::AddToBuffer(
			CRect(x, y,
				x + 32.0f * RenderState.scaleX * w,
				y + 32.0f * RenderState.scaleY * 0.5f),
			RenderState.color,
			xoff / 16.0f, yoff / 16.0f,
			(xoff + w) / 16.0f, yoff / 16.0f,
			xoff / 16.0f, (yoff + 1.0f) / 16.0f,
			(xoff + w) / 16.0f - 0.0001f, (yoff + 1.0f) / 16.0f - 0.0001f);
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
CFont::RenderFontBuffer()
{
	if (FontRenderStatePointer.pRenderState == (CFontRenderState*)FontRenderStateBuf) return;

	float textPosX;
	float textPosY;
	CRGBA color;
	bool bBold = false;
	bool bFlash = false;

	Sprite[RenderState.style].SetRenderState();
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
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
			if (!RenderState.bIsShadow)
				RenderState.color = color;
		}
		wchar c = *pRenderStateBufPointer.pStr;
		c -= ' ';
		if (RenderState.bFontHalfTexture) 
			c = FindNewCharacter(c); 
		else if (c > 155) 
			c = '\0'; 

		if (RenderState.slant != 0.0f)
			textPosY = (RenderState.slantRefX - textPosX) * RenderState.slant + RenderState.slantRefY;
		PrintChar(textPosX, textPosY, c);
		if (bBold) {
			PrintChar(textPosX + 1.0f, textPosY, c);
			PrintChar(textPosX + 2.0f, textPosY, c);
			textPosX += 2.0f;
		}
#ifdef FIX_BUGS
		// PS2 uses different chars for some symbols
		if (!RenderState.bFontHalfTexture && c == 30) c = 61; // wanted star
#endif
		textPosX += RenderState.scaleX * GetCharacterWidth(c);
		if (c == '\0')
			textPosX += RenderState.fExtraSpace;
	}
	CSprite2d::RenderVertexBuffer();
	FontRenderStatePointer.pRenderState = (CFontRenderState*)FontRenderStateBuf;
}

#if 0 //def MORE_LANGUAGES
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
CFont::PrintString(float x, float y, uint32, wchar *start, wchar *end, float spwidth)
{
	wchar *s;

	if (RenderState.style != Details.style) {
		RenderFontBuffer();
		RenderState.style = Details.style;
	}

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
	if (FontRenderStatePointer.pStr >= (wchar*)&FontRenderStateBuf[ARRAY_SIZE(FontRenderStateBuf)] - (end - start + 26)) // why 26?
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
#endif

void
CFont::PrintStringFromBottom(float x, float y, wchar *str)
{
	y -= (32.0f * Details.scaleY / 2.0f + 2.0f * Details.scaleY) * GetNumberLines(x, y, str);
	if (Details.slant != 0.0f)
		y -= ((Details.slantRefX - x) * Details.slant + Details.slantRefY);
	PrintString(x, y, str);
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

	Details.bFlash = false;

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
#if 0//def MORE_LANGUAGES
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
#if 0 //def MORE_LANGUAGES
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
#if 0 //def MORE_LANGUAGES
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

int
CFont::GetNumberLines(float xstart, float ystart, wchar *s)
{
	int n;
	float x, y;
	wchar *t;
	n = 0;

#if 0//def MORE_LANGUAGES
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

float
CFont::GetCharacterWidth(wchar c)
{
#ifdef MORE_LANGUAGES
	if (IsJapanese()) {
		if (!RenderState.proportional)
			return Size[0][Details.style][192];
		if (c <= 94 || Details.style == FONT_HEADING || RenderState.style == FONT_BANK) {
			switch (RenderState.style)
			{
			case FONT_JAPANESE:
				return Size_jp[c];
			default:
				return Size[0][RenderState.style][c];
			}
		}

		switch (RenderState.style)
		{
		case FONT_JAPANESE:
			return 29.4f;
		case FONT_BANK:
			return 10.0f;
		default:
			return Size[0][RenderState.style][c];
		}
	}

	else if (RenderState.proportional)
		return Size[LanguageSet][RenderState.style][c];
	else
		return Size[LanguageSet][RenderState.style][209];
#else

	if (RenderState.proportional)
		return Size[RenderState.style][c];
	else
		return Size[RenderState.style][209];
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

		switch (Details.style)
		{
		case FONT_JAPANESE:
			return 29.4f * Details.scaleX;
		case FONT_BANK:
			return 10.0f * Details.scaleX;
		default:
			return Size[0][Details.style][c] * Details.scaleX;
		}
	}
	else
	{
		if (!Details.bFontHalfTexture && c == 30) c = 61; // wanted star
		if (Details.bFontHalfTexture)
			c = FindNewCharacter(c);
		if (Details.proportional)
			return Size[LanguageSet][Details.style][c] * Details.scaleX;
		else
			return Size[LanguageSet][Details.style][209] * Details.scaleX;
	}
#else

#ifdef FIX_BUGS
	// PS2 don't call FindNewCharacter in here at all, and also uses different chars for some symbols
	if (!Details.bFontHalfTexture && c == 30) c = 61; // wanted star
#endif
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
#ifdef FIX_BUGS
		case 'x':
			color.r = 0;
			color.g = 255;
			color.b = 255;
			break;
#else
		case 'x':
			color.r = 132;
			color.g = 146;
			color.b = 197;
			break;
#endif
		case 'y':
			color.r = 255;
			color.g = 227;
			color.b = 79;
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
	if (*(++s) == '~')
		s = ParseToken(s, color, flash, bold);
	return s;
}

#if 0//def MORE_LANGUAGES
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
	Details.anonymous_23 = false;
	s++;
	if(Details.color.r || Details.color.g || Details.color.b)
		switch(*s){
		case 'B':
			Details.bBold = !Details.bBold;
			break;
		case 'N':
		case 'n':
			NewLine = true;
			break;
		case 'b':
			Details.color.r = 27;
			Details.color.g = 89;
			Details.color.b = 130;
			Details.anonymous_23 = true;
			break;
		case 'f':
			Details.bFlash = !Details.bFlash;
			if (!Details.bFlash)
				Details.color.a = 255;
			break;
		case 'g':
			Details.color.r = 255;
			Details.color.g = 150;
			Details.color.b = 225;
			Details.anonymous_23 = true;
			break;
		case 'h':
			Details.color.r = 225;
			Details.color.g = 225;
			Details.color.b = 225;
			Details.anonymous_23 = true;
			break;
		case 'l':
			Details.color.r = 0;
			Details.color.g = 0;
			Details.color.b = 0;
			Details.anonymous_23 = true;
			break;
		case 'o':
			Details.color.r = 229;
			Details.color.g = 125;
			Details.color.b = 126;
			Details.anonymous_23 = true;
			break;
		case 'p':
			Details.color.r = 168;
			Details.color.g = 110;
			Details.color.b = 252;
			Details.anonymous_23 = true;
			break;
		case 'q':
			Details.color.r = 199;
			Details.color.g = 144;
			Details.color.b = 203;
			Details.anonymous_23 = true;
			break;
		case 'r':
			Details.color.r = 255;
			Details.color.g = 150;
			Details.color.b = 225;
			Details.anonymous_23 = true;
			break;
		case 't':
			Details.color.r = 86;
			Details.color.g = 212;
			Details.color.b = 146;
			Details.anonymous_23 = true;
			break;
		case 'w':
			Details.color.r = 175;
			Details.color.g = 175;
			Details.color.b = 175;
			Details.anonymous_23 = true;
			break;
		case 'x':
#ifdef FIX_BUGS
			Details.color.r = 0;
			Details.color.g = 255;
			Details.color.b = 255;
#else
			Details.color.r = 132;
			Details.color.g = 146;
			Details.color.b = 197;
#endif
			Details.anonymous_23 = true;
			break;
		case 'y':
			Details.color.r = 255;
			Details.color.g = 227;
			Details.color.b = 79;
			Details.anonymous_23 = true;
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
		}
	while(*s != '~') s++;
	if (*(++s) == '~')
		s = ParseToken(s);
	return s;
}
#endif

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

void
CFont::DrawFonts(void)
{
	RenderFontBuffer();
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
CFont::SetSlantRefPoint(float x, float y)
{
	Details.slantRefX = x;
	Details.slantRefY = y;
}

void
CFont::SetSlant(float s)
{
	Details.slant = s;
}

void
CFont::SetColor(CRGBA col)
{
	Details.color = col;
	if (Details.alphaFade < 255.0f)
		Details.color.a *= Details.alphaFade / 255.0f;
}

void
CFont::SetJustifyOn(void)
{
	Details.justify = true;
	Details.centre = false;
	Details.rightJustify = false;
}

void
CFont::SetJustifyOff(void)
{
	Details.justify = false;
	Details.rightJustify = false;
}

void
CFont::SetCentreOn(void)
{
	Details.centre = true;
	Details.justify = false;
	Details.rightJustify = false;
}

void
CFont::SetCentreOff(void)
{
	Details.centre = false;
}

void
CFont::SetWrapx(float x)
{
	Details.wrapX = x;
}

void
CFont::SetCentreSize(float s)
{
	Details.centreSize = s;
}

void
CFont::SetBackgroundOn(void)
{
	Details.background = true;
}

void
CFont::SetBackgroundOff(void)
{
	Details.background = false;
}

void
CFont::SetBackgroundColor(CRGBA col)
{
	Details.backgroundColor = col;
}

void
CFont::SetBackGroundOnlyTextOn(void)
{
	Details.backgroundOnlyText = true;
}

void
CFont::SetBackGroundOnlyTextOff(void)
{
	Details.backgroundOnlyText = false;
}

void
CFont::SetRightJustifyOn(void)
{
	Details.rightJustify = true;
	Details.justify = false;
	Details.centre = false;
}

void
CFont::SetRightJustifyOff(void)
{
	Details.rightJustify = false;
	Details.justify = false;
	Details.centre = false;
}

void
CFont::SetPropOff(void)
{
	Details.proportional = false;
}

void
CFont::SetPropOn(void)
{
	Details.proportional = true;
}

void
CFont::SetFontStyle(int16 style)
{
	if (style == FONT_HEADING) {
		Details.style = FONT_STANDARD;
		Details.bFontHalfTexture = true;
	} else {
		Details.style = style;
		Details.bFontHalfTexture = false;
	}
}

void
CFont::SetRightJustifyWrap(float wrap)
{
	Details.rightJustifyWrap = wrap;
}

void
CFont::SetAlphaFade(float fade)
{
	Details.alphaFade = fade;
}

void
CFont::SetDropColor(CRGBA col)
{
	Details.dropColor = col;
	if (Details.alphaFade < 255.0f)
		Details.dropColor.a *= Details.alphaFade / 255.0f;
}

void
CFont::SetDropShadowPosition(int16 pos)
{
	Details.dropShadowPosition = pos;
}

wchar CFont::FindNewCharacter(wchar c)
{
	if (c >= 16 && c <= 26) return c + 128;
	if (c >= 8 && c <= 9) return c + 86;
	if (c == 4) return c + 89;
	if (c == 7) return 206;
	if (c == 14) return 207;
	if (c >= 33 && c <= 58) return c + 122;
	if (c >= 65 && c <= 90) return c + 90;
	if (c >= 96 && c <= 118) return c + 85;
	if (c >= 119 && c <= 140) return c + 62;
	if (c >= 141 && c <= 142) return 204;
	if (c == 143) return 205;
	if (c == 1) return 208;
	return c;
}

wchar
CFont::character_code(uint8 c)
{
	if(c < 128)
		return c;
	return foreign_table[c-128];
}