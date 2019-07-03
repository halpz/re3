#pragma once
#include "Ped.h"
#include "Object.h"
#include "Sprite2d.h"
#include "Vehicle.h"

struct CScriptRectangle 
{
	bool m_bIsUsed;
	bool m_bIsAntialiased;
	uint16 m_wTextureId;
	CRect m_sRect;
	CRGBA m_sColor;
};

struct CTextLine 
{
	float m_fScaleX;
	float m_fScaleY;
	CRGBA m_sColor;
	bool m_bJustify;
	bool m_bCentered;
	bool m_bBackground;
	bool m_bBackgroundOnly;
	float m_fWrapX;
	float m_fCenterSize;
	CRGBA m_sBackgroundColor;
	bool m_bTextProportional;
	int32 field_29;
	bool m_bRightJustify;
	int32 field_31;
	int32 m_nFont;
	float field_36;
	float field_40;
	wchar m_awText[500];
};

struct CRunningScript
{
	CRunningScript *next;
	CRunningScript *prev;
	uint8 m_abScriptName[8];
	uint32 m_nIp;
	uint32 m_anStack[6];
	uint16 m_nStackPointer;
	void* m_anLocalVariables[18];
	bool m_bCondResult;
	bool m_bIsMissionThread;
	bool m_bSkipWakeTime;
	uint32 m_nWakeTime;
	uint16 m_wIfOp;
	bool m_bNotFlag;
	bool m_bWBCheck;
	bool m_bWastedOrBusted;
	bool m_bMissionFlag;
};

enum {
	CLEANUP_UNUSED = 0,
	CLEANUP_CAR,
	CLEANUP_CHAR,
	CLEANUP_OBJECT
};

struct CMissionCleanupEntity
{
	uint8 type;
	int32 id;
};

enum {
	MAX_CLEANUP = 50,
	MAX_UPSIDEDOWN_CAR_CHECKS = 6,
	MAX_STUCK_CAR_CHECKS = 6
};

class CMissionCleanup
{
	CMissionCleanupEntity m_sEntities[MAX_CLEANUP];
	uint8 m_bCount;

public:
	CMissionCleanup();

	void Init();
	CMissionCleanupEntity* FindFree();
	void AddEntityToList(int32, uint8);
	void RemoveEntityFromList(int32, uint8);
	void Process();
};

struct CUpsideDownCarCheckEntry
{
	int32 m_nVehicleIndex;
	uint32 m_nUpsideDownTimer;
};

class CUpsideDownCarCheck
{
	CUpsideDownCarCheckEntry m_sCars[MAX_UPSIDEDOWN_CAR_CHECKS];

public:
	void Init();
};

struct CStuckCarCheckEntry
{
	int32 m_nVehicleIndex;
	CVector m_vecPos;
	int32 m_nStartTime;
	float m_fDistance;
	uint32 m_nStuckTime;
	bool m_bStuck;
};

class CStuckCarCheck
{
	CStuckCarCheckEntry m_sCars[MAX_STUCK_CAR_CHECKS];

public:
	void Init();
};

class CTheScripts
{
public:
	static uint8(&ScriptSpace)[160 * 1024];
	static CTextLine(&IntroTextLines)[2];
	static CScriptRectangle(&IntroRectangles)[16];
	static CSprite2d(&ScriptSprites)[16];
	static bool &DbgFlag;
	static uint32 &OnAMissionFlag;
	static CMissionCleanup &MissionCleanup;
	static CStuckCarCheck &StuckCars;
	static CUpsideDownCarCheck &UpsideDownCars;
	static int32 &StoreVehicleIndex;
	static bool &StoreVehicleWasRandom;

public:
	static bool IsPlayerOnAMission();
	static void ScriptDebugLine3D(float x1, float y1, float z1, float x2, float y2, float z2, int col, int col2);
	static void CleanUpThisVehicle(CVehicle*);
	static void CleanUpThisPed(CPed*);
	static void CleanUpThisObject(CObject*);
};
