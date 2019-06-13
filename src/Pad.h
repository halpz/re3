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
VALIDATE_SIZE(CControllerState, 0x2A);

class CMouseControllerState
{
public:
	//uint32 btns;	// bit 0-2 button 1-3

	Bool LMB;
	Bool RMB;
	Bool MMB;
	Bool WHEELUP;
	Bool WHEELDN;
	Bool MXB1;
	Bool MXB2;
	char _pad0;
	
	Float x, y;
	
	CMouseControllerState();
	void Clear();
};

VALIDATE_SIZE(CMouseControllerState, 0x10);

class CMousePointerStateHelper
{
public:
	Bool bInvertHorizontally;
	Bool bInvertVertically;
	
	CMouseControllerState GetMouseSetUp();
};

VALIDATE_SIZE(CMousePointerStateHelper, 0x2);

extern CMousePointerStateHelper &MousePointerStateHelper;


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

enum
{
	// taken from miss2
	PAD1 = 0,
	PAD2,
	
	MAX_PADS
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
	UInt8 ShakeFreq;
	int8 bHornHistory[5];
	UInt8 iCurrHornHistory;
	Bool DisablePlayerControls;
	int8 bApplyBrakes;
	Char _unk[12]; //int32 unk[3];
	char _pad0[3];
	int32 LastTimeTouched;
	int32 AverageWeapon;
	int32 AverageEntries;
	
	CPad() { }
	~CPad() { }

	static Bool &bDisplayNoControllerMessage;
	static Bool &bObsoleteControllerMessage;
	static Bool &m_bMapPadOneToPadTwo;
	
	static CKeyboardState &OldKeyState;
	static CKeyboardState &NewKeyState;
	static CKeyboardState &TempKeyState;
	static Char KeyBoardCheatString[18];
	static CMouseControllerState &OldMouseControllerState;
	static CMouseControllerState &NewMouseControllerState;
	static CMouseControllerState &PCTempMouseControllerState;
	
	
	
	
	void Clear(Bool bResetPlayerControls);
	void ClearMouseHistory();
	void UpdateMouse();
	CControllerState ReconcileTwoControllersInput(CControllerState const &State1, CControllerState const &State2);
	void StartShake(Int16 nDur, UInt8 nFreq);
	void StartShake_Distance(Int16 nDur, UInt8 nFreq, Float fX, Float fY, Float fz);
	void StartShake_Train(Float fX, Float fY);
	void AddToPCCheatString(Char c);

	static void UpdatePads(void);
	void ProcessPCSpecificStuff(void);
	void Update(Int16 unk);
	
	static void DoCheats(void);
	void DoCheats(Int16 unk);
	
	static void StopPadsShaking(void);
	void StopShaking(Int16 unk);
	
	static CPad *GetPad(Int32 pad);
	
	Int16 GetSteeringLeftRight(void);
	Int16 GetSteeringUpDown(void);
	Int16 GetCarGunUpDown(void);
	Int16 GetCarGunLeftRight(void);
	Int16 GetPedWalkLeftRight(void);
	Int16 GetPedWalkUpDown(void);
	Int16 GetAnalogueUpDown(void);
	Bool GetLookLeft(void);
	Bool GetLookRight(void);
	Bool GetLookBehindForCar(void);
	Bool GetLookBehindForPed(void);
	Bool GetHorn(void);
	Bool HornJustDown(void);
	Bool GetCarGunFired(void);
	Bool CarGunJustDown(void);
	Int16 GetHandBrake(void);
	Int16 GetBrake(void);
	Bool GetExitVehicle(void);
	Bool ExitVehicleJustDown(void);
	Int32 GetWeapon(void);
	Bool WeaponJustDown(void);
	Int16 GetAccelerate(void);
	Bool CycleCameraModeUpJustDown(void);
	Bool CycleCameraModeDownJustDown(void);
	Bool ChangeStationJustDown(void);
	Bool CycleWeaponLeftJustDown(void);
	Bool CycleWeaponRightJustDown(void);
	Bool GetTarget(void);
	Bool TargetJustDown(void);
	Bool JumpJustDown(void);
	Bool GetSprint(void);
	Bool ShiftTargetLeftJustDown(void);
	Bool ShiftTargetRightJustDown(void);
	Bool GetAnaloguePadUp(void);
	Bool GetAnaloguePadDown(void);
	Bool GetAnaloguePadLeft(void);
	Bool GetAnaloguePadRight(void);
	Bool GetAnaloguePadLeftJustUp(void);
	Bool GetAnaloguePadRightJustUp(void);
	Bool ForceCameraBehindPlayer(void);
	Bool SniperZoomIn(void);
	Bool SniperZoomOut(void);
	Int16 SniperModeLookLeftRight(void);
	Int16 SniperModeLookUpDown(void);
	Int16 LookAroundLeftRight(void);
	Int16 LookAroundUpDown(void);
	void ResetAverageWeapon(void);
	static void PrintErrorMessage(void);
	static void ResetCheats(void);
	static Char *EditString(Char *pStr, Int32 nSize);
	static Int32 *EditCodesForControls(Int32 *pRsKeys, Int32 nSize);

	// mouse
	inline Bool GetLeftMouseJustDown() { return !!(NewMouseControllerState.LMB && !OldMouseControllerState.LMB); }

	// keyboard
	
	inline Bool GetCharJustDown(Char c) { return !!(NewKeyState.VK_KEYS[c] && !OldKeyState.VK_KEYS[c]); }
	inline Bool GetFJustDown(Int32 n)   { return !!(NewKeyState.F[n] && !OldKeyState.F[n]); }
	inline Bool GetEscapeJustDown()     { return !!(NewKeyState.ESC && !OldKeyState.ESC); }
	inline Bool GetInsertJustDown()     { return !!(NewKeyState.INS && !OldKeyState.INS); }
	inline Bool GetDeleteJustDown()     { return !!(NewKeyState.DEL && !OldKeyState.DEL); }
	inline Bool GetHomeJustDown()       { return !!(NewKeyState.HOME && !OldKeyState.HOME); }
	inline Bool GetEndJustDown()        { return !!(NewKeyState.END && !OldKeyState.END); }
	inline Bool GetPageUpJustDown()     { return !!(NewKeyState.PGUP && !OldKeyState.PGUP); }
	inline Bool GetPageDownJustDown()   { return !!(NewKeyState.PGDN && !OldKeyState.PGDN); }
	inline Bool GetUpJustDown()         { return !!(NewKeyState.UP && !OldKeyState.UP); }
	inline Bool GetDownJustDown()       { return !!(NewKeyState.DOWN && !OldKeyState.DOWN); }
	inline Bool GetLeftJustDown()       { return !!(NewKeyState.LEFT && !OldKeyState.LEFT); }
	inline Bool GetRightJustDown()      { return !!(NewKeyState.RIGHT && !OldKeyState.RIGHT); }
	inline Bool GetScrollLockJustDown() { return !!(NewKeyState.SCROLLLOCK && !OldKeyState.SCROLLLOCK); }
	inline Bool GetPauseJustDown()      { return !!(NewKeyState.PAUSE && !OldKeyState.PAUSE); }
	inline Bool GetNumLockJustDown()    { return !!(NewKeyState.NUMLOCK && !OldKeyState.NUMLOCK); }
	inline Bool GetDivideJustDown()     { return !!(NewKeyState.DIV && !OldKeyState.DIV); }
	inline Bool GetTimesJustDown()      { return !!(NewKeyState.MUL && !OldKeyState.MUL); }
	inline Bool GetMinusJustDown()      { return !!(NewKeyState.SUB && !OldKeyState.SUB); }
	inline Bool GetPlusJustDown()       { return !!(NewKeyState.ADD && !OldKeyState.ADD); }
	inline Bool GetPadEnterJustDown()   { return !!(NewKeyState.ENTER && !OldKeyState.ENTER); } //  GetEnterJustDown
	inline Bool GetPadDelJustDown()     { return !!(NewKeyState.DECIMAL && !OldKeyState.DECIMAL); }
	inline Bool GetPad1JustDown()       { return !!(NewKeyState.NUM1 && !OldKeyState.NUM1); }
	inline Bool GetPad2JustDown()       { return !!(NewKeyState.NUM2 && !OldKeyState.NUM2); }
	inline Bool GetPad3JustDown()       { return !!(NewKeyState.NUM3 && !OldKeyState.NUM3); }
	inline Bool GetPad4JustDown()       { return !!(NewKeyState.NUM4 && !OldKeyState.NUM4); }
	inline Bool GetPad5JustDown()       { return !!(NewKeyState.NUM5 && !OldKeyState.NUM5); }
	inline Bool GetPad6JustDown()       { return !!(NewKeyState.NUM6 && !OldKeyState.NUM6); }
	inline Bool GetPad7JustDown()       { return !!(NewKeyState.NUM7 && !OldKeyState.NUM7); }
	inline Bool GetPad8JustDown()       { return !!(NewKeyState.NUM8 && !OldKeyState.NUM8); }
	inline Bool GetPad9JustDown()       { return !!(NewKeyState.NUM9 && !OldKeyState.NUM9); }
	inline Bool GetPad0JustDown()       { return !!(NewKeyState.NUM0 && !OldKeyState.NUM0); }
	inline Bool GetBackspaceJustDown()  { return !!(NewKeyState.BACKSP && !OldKeyState.BACKSP); }
	inline Bool GetTabJustDown()        { return !!(NewKeyState.TAB && !OldKeyState.TAB); }
	inline Bool GetCapsLockJustDown()   { return !!(NewKeyState.CAPSLOCK && !OldKeyState.CAPSLOCK); }
	inline Bool GetEnterJustDown()      { return !!(NewKeyState.EXTENTER && !OldKeyState.EXTENTER); }
	inline Bool GetLeftShiftJustDown()  { return !!(NewKeyState.LSHIFT && !OldKeyState.LSHIFT); }
	inline Bool GetShiftJustDown()      { return !!(NewKeyState.SHIFT && !OldKeyState.SHIFT); }
	inline Bool GetRightShiftJustDown() { return !!(NewKeyState.RSHIFT && !OldKeyState.RSHIFT); }
	inline Bool GetLeftCtrlJustDown()   { return !!(NewKeyState.LCTRL && !OldKeyState.LCTRL); }
	inline Bool GetRightCtrlJustDown()  { return !!(NewKeyState.RCTRL && !OldKeyState.RCTRL); }
	inline Bool GetLeftAltJustDown()    { return !!(NewKeyState.LALT && !OldKeyState.LALT); }
	inline Bool GetRightAltJustDown()   { return !!(NewKeyState.RALT && !OldKeyState.RALT); }
	inline Bool GetLeftWinJustDown()    { return !!(NewKeyState.LWIN && !OldKeyState.LWIN); }
	inline Bool GetRightWinJustDown()   { return !!(NewKeyState.RWIN && !OldKeyState.RWIN); }
	inline Bool GetAppsJustDown()       { return !!(NewKeyState.APPS && !OldKeyState.APPS); }
	
	// pad

	inline Bool GetTriangleJustDown()       { return !!(NewState.Triangle && !OldState.Triangle); }
	inline Bool GetCircleJustDown()         { return !!(NewState.Circle && !OldState.Circle); }
	inline Bool GetCrossJustDown()          { return !!(NewState.Cross && !OldState.Cross); }
	inline Bool GetSquareJustDown()         { return !!(NewState.Square && !OldState.Square); }
	inline Bool GetDPadUpJustDown()         { return !!(NewState.DPadUp && !OldState.DPadUp); }
	inline Bool GetDPadDownJustDown()       { return !!(NewState.DPadDown && !OldState.DPadDown); }
	inline Bool GetDPadLeftJustDown()       { return !!(NewState.DPadLeft && !OldState.DPadLeft); }
	inline Bool GetDPadRightJustDown()      { return !!(NewState.DPadRight && !OldState.DPadRight); }
	inline Bool GetLeftShoulder1JustDown()  { return !!(NewState.LeftShoulder1 && !OldState.LeftShoulder1); }
	inline Bool GetLeftShoulder2JustDown()  { return !!(NewState.LeftShoulder2 && !OldState.LeftShoulder2); }
	inline Bool GetRightShoulder1JustDown() { return !!(NewState.RightShoulder1 && !OldState.RightShoulder1); }
	inline Bool GetRightShoulder2JustDown() { return !!(NewState.RightShoulder2 && !OldState.RightShoulder2); }
	
	inline Int32 GetLeftShoulder1(void)  { return NewState.LeftShoulder1; }
	inline Int32 GetLeftShoulder2(void)  { return NewState.LeftShoulder2; }
	inline Int32 GetRightShoulder1(void) { return NewState.RightShoulder1; }
	inline Int32 GetRightShoulder2(void) { return NewState.RightShoulder2; }
};
VALIDATE_SIZE(CPad, 0xFC);

#define IsButtonJustDown(pad, btn) \
	(!(pad)->OldState.btn && (pad)->NewState.btn)
	
void LittleTest(void);