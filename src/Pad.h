#pragma once

// same as RW skeleton
enum Key
{
	// ascii...

	KEY_ESC   = 128,

	KEY_F1    = 129,
	KEY_F2    = 130,
	KEY_F3    = 131,
	KEY_F4    = 132,
	KEY_F5    = 133,
	KEY_F6    = 134,
	KEY_F7    = 135,
	KEY_F8    = 136,
	KEY_F9    = 137,
	KEY_F10   = 138,
	KEY_F11   = 139,
	KEY_F12   = 140,

	KEY_INS   = 141,
	KEY_DEL   = 142,
	KEY_HOME  = 143,
	KEY_END   = 144,
	KEY_PGUP  = 145,
	KEY_PGDN  = 146,

	KEY_UP    = 147,
	KEY_DOWN  = 148,
	KEY_LEFT  = 149,
	KEY_RIGHT = 150,

	// some stuff ommitted

	KEY_BACKSP = 168,
	KEY_TAB    = 169,
	KEY_CAPSLK = 170,
	KEY_ENTER  = 171,
	KEY_LSHIFT = 172,
	KEY_RSHIFT = 173,
	KEY_LCTRL  = 174,
	KEY_RCTRL  = 175,
	KEY_LALT   = 176,
	KEY_RALT   = 177,

	KEY_NULL,	// unused
	KEY_NUMKEYS,
};


class CControllerState
{
public:
	int16 leftX, leftY;
	int16 rightX, rightY;
	int16 l1, l2;
	int16 r1, r2;
	int16 up, down, left, right;
	int16 start, select;
	int16 square, triangle, cross, circle;
	int16 leftshock, rightshock;
	int16 networktalk;
	float getLeftX(void) { return leftX/32767.0f; };
	float getLeftY(void) { return leftY/32767.0f; };
	float getRightX(void) { return rightX/32767.0f; };
	float getRightY(void) { return rightY/32767.0f; };

	void Clear(void);
};
static_assert(sizeof(CControllerState) == 0x2A, "CControllerState: error");

struct CMouseControllerState
{
	uint32 btns;	// bit 0-2 button 1-3
	int x, y;
};

class CPad
{
public:
	CControllerState NewState;
	CControllerState OldState;
	CControllerState PCTempKeyState;
	CControllerState PCTempJoyState;
	CControllerState PCTempMouseState;
	// straight out of my IDB
	int16 Phase;
	int16 Mode;
	int16 ShakeDur;
	int8 ShakeFreq;
	int8 bHornHistory[5];
	int8 iCurrHornHistory;
	int8 DisablePlayerControls;
	int8 JustOutOfFrontEnd;
	int8 bApplyBrakes;
	int32 unk[3];
	int32 LastTimeTouched;
	int32 AverageWeapon;
	int32 AverageEntries;

	static CPad *Pads;	//[2];
	static uint16 *OldKeyState;	//[KEY_NUMKEYS];
	static uint16 *NewKeyState;	//[KEY_NUMKEYS];
	static uint16 *TempKeyState;	//[KEY_NUMKEYS];
	static CMouseControllerState &OldMouseControllerState;
	static CMouseControllerState &NewMouseControllerState;
	static CMouseControllerState &PCTempMouseControllerState;

	static CPad *GetPad(int n) { return &Pads[n]; }
};
static_assert(sizeof(CPad) == 0xFC, "CPad: error");

#define IsButtonJustDown(pad, btn) \
	(!(pad)->OldState.btn && (pad)->NewState.btn)
