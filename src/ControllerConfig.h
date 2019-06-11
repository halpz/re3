#pragma once


// based on x-gtasa

enum eControllerType
{
	KEYBOARD,
	OPTIONAL_EXTRA,
	MOUSE,
	JOYSTICK,
};

class CMouseControllerState;

class CControllerConfigManager
{
public:
	struct tControllerConfigBind
	{
		RsKeyCodes m_Key;
		Int32 m_ContSetOrder;
	};

	Bool field_0;
	char _pad0[3];
	DIJOYSTATE2 m_OldState;
	DIJOYSTATE2 m_NewState;
	WChar m_aActionNames[41][40];
	Bool m_aButtonStates[17];
	char _pad1[3];
	tControllerConfigBind m_aSettings[41][4];
	UInt8 m_aSimCheckers[4][4];
	Bool m_bMouseAssociated;
	char _pad2[3];
	
	void UpdateJoyButtonState(int padnumber);
	void UpdateJoyInConfigMenus_ButtonDown(int button, int padnumber);
	void AffectControllerStateOn_ButtonDown(int button, eControllerType type);
	void UpdateJoyInConfigMenus_ButtonUp(int button, int padnumber);
	void AffectControllerStateOn_ButtonUp(int button, int padnumber);
	
	Int32 GetJoyButtonJustDown();
	void LoadSettings(Int32 file);
	void MakeControllerActionsBlank();
	void InitDefaultControlConfiguration();
	void InitDefaultControlConfigMouse(CMouseControllerState const &mousestate);
	void InitDefaultControlConfigJoyPad(unsigned int buttons);
	
};

VALIDATE_SIZE(CControllerConfigManager, 0x143C);

extern CControllerConfigManager &ControlsManager;