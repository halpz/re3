#pragma once


// based on x-gtasa

enum eControllerType
{
	KEYBOARD,
	OPTIONAL_EXTRA,
	MOUSE,
	JOYSTICK,
	TOTAL_CONTROLLER_TYPES
};

enum e_ControllerAction
{
	PED_FIREWEAPON = 0,
	PED_CYCLE_WEAPON_RIGHT,
	PED_CYCLE_WEAPON_LEFT,
	GO_FORWARD,
	GO_BACK,
	GO_LEFT,
	GO_RIGHT,
	PED_SNIPER_ZOOM_IN,
	PED_SNIPER_ZOOM_OUT,
	VEHICLE_ENTER_EXIT,
	CAMERA_CHANGE_VIEW_ALL_SITUATIONS,
	PED_JUMPING,
	PED_SPRINT,
	PED_LOOKBEHIND,
	//PED_DUCK,				// VC
	//PED_ANSWER_PHONE,		// VC
	VEHICLE_ACCELERATE,
	VEHICLE_BRAKE,
	VEHICLE_CHANGE_RADIO_STATION,
	VEHICLE_HORN,
	TOGGLE_SUBMISSIONS,
	VEHICLE_HANDBRAKE,
	PED_1RST_PERSON_LOOK_LEFT,
	PED_1RST_PERSON_LOOK_RIGHT,
	VEHICLE_LOOKLEFT,
	VEHICLE_LOOKRIGHT,
	VEHICLE_LOOKBEHIND,
	VEHICLE_TURRETLEFT,
	VEHICLE_TURRETRIGHT,
	VEHICLE_TURRETUP,
	VEHICLE_TURRETDOWN,
	PED_CYCLE_TARGET_LEFT,
	PED_CYCLE_TARGET_RIGHT,
	PED_CENTER_CAMERA_BEHIND_PLAYER,
	PED_LOCK_TARGET,
	NETWORK_TALK,
	PED_1RST_PERSON_LOOK_UP,
	PED_1RST_PERSON_LOOK_DOWN,

	CONTROLLERACTION_36, // unk, unused?

	TOGGLE_DPAD,
	SWITCH_DEBUG_CAM_ON,
	TAKE_SCREEN_SHOT,
	SHOW_MOUSE_POINTER_TOGGLE,

	TOTAL_CONTROL_ACTIONS
};

class CMouseControllerState;

#define ACTIONNAME_LENGTH 40

class CControllerConfigManager
{
public:
	struct tControllerConfigBind
	{
		RsKeyCodes m_Key;
		int32 m_ContSetOrder;
	};

	bool firstCapture;
	DIJOYSTATE2 m_OldState;
	DIJOYSTATE2 m_NewState;
	wchar m_aActionNames[TOTAL_CONTROL_ACTIONS][ACTIONNAME_LENGTH];
	bool m_aButtonStates[17];
	tControllerConfigBind m_aSettings[TOTAL_CONTROL_ACTIONS][TOTAL_CONTROLLER_TYPES];
	uint8 m_aSimCheckers[4][4];
	bool m_bMouseAssociated;
	
	void UpdateJoyButtonState(int padnumber);
	void UpdateJoyInConfigMenus_ButtonDown(int button, int padnumber);
	void AffectControllerStateOn_ButtonDown(int button, eControllerType type);
	void UpdateJoyInConfigMenus_ButtonUp(int button, int padnumber);
	void AffectControllerStateOn_ButtonUp(int button, int padnumber);
	
	int32 GetJoyButtonJustDown();
	void LoadSettings(int32 file);
	void SaveSettings(int32 file);
	void MakeControllerActionsBlank();
	void InitDefaultControlConfiguration();
	void InitDefaultControlConfigMouse(CMouseControllerState const &mousestate);
	void InitDefaultControlConfigJoyPad(unsigned int buttons);
	void ClearSimButtonPressCheckers();
	void AffectPadFromKeyBoard();
	void AffectPadFromMouse();
	void ClearSettingsAssociatedWithAction(int, int);

	void GetWideStringOfCommandKeys(uint16, wchar*, uint16);
};

VALIDATE_SIZE(CControllerConfigManager, 0x143C);

extern CControllerConfigManager &ControlsManager;