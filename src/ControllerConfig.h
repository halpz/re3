#pragma once

// dinput.h
typedef struct DIJOYSTATE2 {
    LONG    lX;                     /* x-axis position              */
    LONG    lY;                     /* y-axis position              */
    LONG    lZ;                     /* z-axis position              */
    LONG    lRx;                    /* x-axis rotation              */
    LONG    lRy;                    /* y-axis rotation              */
    LONG    lRz;                    /* z-axis rotation              */
    LONG    rglSlider[2];           /* extra axes positions         */
    DWORD   rgdwPOV[4];             /* POV directions               */
    BYTE    rgbButtons[128];        /* 128 buttons                  */
    LONG    lVX;                    /* x-axis velocity              */
    LONG    lVY;                    /* y-axis velocity              */
    LONG    lVZ;                    /* z-axis velocity              */
    LONG    lVRx;                   /* x-axis angular velocity      */
    LONG    lVRy;                   /* y-axis angular velocity      */
    LONG    lVRz;                   /* z-axis angular velocity      */
    LONG    rglVSlider[2];          /* extra axes velocities        */
    LONG    lAX;                    /* x-axis acceleration          */
    LONG    lAY;                    /* y-axis acceleration          */
    LONG    lAZ;                    /* z-axis acceleration          */
    LONG    lARx;                   /* x-axis angular acceleration  */
    LONG    lARy;                   /* y-axis angular acceleration  */
    LONG    lARz;                   /* z-axis angular acceleration  */
    LONG    rglASlider[2];          /* extra axes accelerations     */
    LONG    lFX;                    /* x-axis force                 */
    LONG    lFY;                    /* y-axis force                 */
    LONG    lFZ;                    /* z-axis force                 */
    LONG    lFRx;                   /* x-axis torque                */
    LONG    lFRy;                   /* y-axis torque                */
    LONG    lFRz;                   /* z-axis torque                */
    LONG    rglFSlider[2];          /* extra axes forces            */
} DIJOYSTATE2, *LPDIJOYSTATE2;


// based on x-gtasa

enum eControllerType
{
	KEYBOARD,
	OPTIONAL_EXTRA,
	MOUSE,
	JOYSTICK,
};

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
	
};

VALIDATE_SIZE(CControllerConfigManager, 0x143C);

extern CControllerConfigManager &ControlsManager;