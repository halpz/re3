#pragma once

// same as RW skeleton
/*
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
	KEY_NUMKEYS
};
*/


class CControllerState
{
public:
	int16 LeftStickX, LeftStickY;
	int16 RightStickX, RightStickY;
	int16 LeftShoulder1, LeftShoulder2;
	int16 RightShoulder1, RightShoulder2;
	int16 DPadUp, DPadDown, DPadLeft, DPadRight;
	int16 Start, Select;
	int16 Square, Triangle, Cross, Circle;
	int16 LeftShock, RightShock;
	int16 NetworkTalk;
	float GetLeftStickX(void) { return LeftStickX/32767.0f; };
	float GetLeftStickY(void) { return LeftStickY/32767.0f; };
	float GetRightStickX(void) { return RightStickX/32767.0f; };
	float GetRightStickY(void) { return RightStickY/32767.0f; };

	void Clear(void);
};
static_assert(sizeof(CControllerState) == 0x2A, "CControllerState: error");

struct CMouseControllerState
{
	uint32 btns;	// bit 0-2 button 1-3
	int x, y;
};

class CKeyboardState
{
public:
	Int16 F[12];
	Int16 VK_KEYS[256];
	Int16 ESC;
	Int16 INS;
	Int16 DEL;
	Int16 HOME;
	Int16 END;
	Int16 PGUP;
	Int16 PGDN;
	Int16 UP;
	Int16 DOWN;
	Int16 LEFT;
	Int16 RIGHT;
	Int16 SCROLLLOCK;
	Int16 PAUSE;
	Int16 NUMLOCK;
	Int16 DIV;
	Int16 MUL;
	Int16 SUB;
	Int16 ADD;
	Int16 ENTER;
	Int16 DECIMAL;
	Int16 NUM1;
	Int16 NUM2;
	Int16 NUM3;
	Int16 NUM4;
	Int16 NUM5;
	Int16 NUM6;
	Int16 NUM7;
	Int16 NUM8;
	Int16 NUM9;
	Int16 NUM0;
	Int16 BACKSP;
	Int16 TAB;
	Int16 CAPSLOCK;
	Int16 EXTENTER;
	Int16 LSHIFT;
	Int16 RSHIFT;
	Int16 SHIFT;
	Int16 LCTRL;
	Int16 RCTRL;
	Int16 LALT;
	Int16 RALT;
	Int16 LWIN;
	Int16 RWIN;
	Int16 APPS;
	
	void Clear();
};

VALIDATE_SIZE(CKeyboardState, 0x270);

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
	static CKeyboardState &OldKeyState;
	static CKeyboardState &NewKeyState;
	static CKeyboardState &TempKeyState;
	static CMouseControllerState &OldMouseControllerState;
	static CMouseControllerState &NewMouseControllerState;
	static CMouseControllerState &PCTempMouseControllerState;
	
	static Bool &m_bMapPadOneToPadTwo;

	int GetLeftShoulder1(void) { return NewState.LeftShoulder1; }
	int GetLeftShoulder2(void) { return NewState.LeftShoulder2; }
	int GetRightShoulder1(void) { return NewState.RightShoulder1; }
	int GetRightShoulder2(void) { return NewState.RightShoulder2; }

	bool ForceCameraBehindPlayer(void);
	bool GetWeapon(void);
	bool GetLookBehindForCar(void);
	bool GetLookBehindForPed(void);
	bool GetLookLeft(void);
	bool GetLookRight(void);

	static void UpdatePads(void);
	static CPad *GetPad(int n) { return &Pads[n]; }
	static void PrintErrorMessage(void);
	
	void AddToPCCheatString(Char c);
};
static_assert(sizeof(CPad) == 0xFC, "CPad: error");

#define IsButtonJustDown(pad, btn) \
	(!(pad)->OldState.btn && (pad)->NewState.btn)
