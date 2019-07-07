#pragma once
#include "Weapon.h"

enum eKillFrenzyStatus
{
	KILLFRENZY_NONE,
	KILLFRENZY_ONGOING,
	KILLFRENZY_PASSED,
	KILLFRENZY_FAILED,
};

class CDarkel
{
private:
	static int32 &TimeLimit;
	static int32 &PreviousTime;
	static int32 &TimeOfFrenzyStart;
	static int32 &WeaponType;
	static int32 &AmmoInterruptedWeapon;
	static int32 &KillsNeeded;
	static int8 &InterruptedWeapon;
	static int8 &bStandardSoundAndMessages;
	static int8 &bNeedHeadShot;
	static int8 &bProperKillFrenzy;
	static eKillFrenzyStatus &Status;
	static int16 *RegisteredKills;
	static int32 &ModelToKill;
	static int32 &ModelToKill2;
	static int32 &ModelToKill3;
	static int32 &ModelToKill4;
	static wchar *pStartMessage;

public:
	static int32 CalcFade(uint32 time, int32 min, uint32 max);
	static void DrawMessages(void);
	static bool FrenzyOnGoing();
	static void Init();
	static int16 QueryModelsKilledByPlayer(int32 modelId);
	static eKillFrenzyStatus ReadStatus();
	static int32 RegisterCarBlownUpByPlayer(eKillFrenzyStatus status);
	static void RegisterKillByPlayer(int32 modelid, eWeaponType weapontype, bool flag);
	static void RegisterKillNotByPlayer();
	static void ResetModelsKilledByPlayer();
	static void ResetOnPlayerDeath();
	static void StartFrenzy(eWeaponType weaponType, int32 time, int16 kill, int32 modelId0, wchar *text, int32 modelId2, int32 modelId3, int32 modelId4, bool standardSound, bool needHeadShot);
	static void Update();

};
