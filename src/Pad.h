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
};
static_assert(sizeof(CPad) == 0xFC, "CPad: error");

#define IsButtonJustDown(pad, btn) \
	(!(pad)->OldState.btn && (pad)->NewState.btn)
