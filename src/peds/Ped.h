#pragma once

#include "Physical.h"
#include "Weapon.h"
#include "PedStats.h"
#include "PedType.h"
#include "PedIK.h"
#include "AnimManager.h"
#include "AnimBlendClumpData.h"
#include "AnimBlendAssociation.h"
#include "WeaponInfo.h"
#include "Fire.h"
#include "DMAudio.h"

struct CPathNode;

struct CPedAudioData
{
	int m_nFixedDelayTime;
	int m_nOverrideFixedDelayTime;
	int m_nOverrideMaxRandomDelayTime;
	int m_nMaxRandomDelayTime;
};

enum
{
	ENDFIGHT_NORMAL,
	ENDFIGHT_WITH_A_STEP,
	ENDFIGHT_FAST
};

struct FightMove
{
	AnimationId animId;
	float startFireTime;
	float endFireTime;
	float comboFollowOnTime;
	float strikeRadius;
	uint8 hitLevel;
	uint8 damage;
	uint8 flags;
};
static_assert(sizeof(FightMove) == 0x18, "FightMove: error");

enum PedFightMoves
{
	FIGHTMOVE_NULL,
	// Attacker
	FIGHTMOVE_STDPUNCH,
	FIGHTMOVE_IDLE,
	FIGHTMOVE_SHUFFLE_F,
	FIGHTMOVE_KNEE,
	FIGHTMOVE_HEADBUTT,
	FIGHTMOVE_PUNCHJAB,
	FIGHTMOVE_PUNCHHOOK,
	FIGHTMOVE_KICK,
	FIGHTMOVE_LONGKICK,
	FIGHTMOVE_ROUNDHOUSE,
	FIGHTMOVE_BODYBLOW,
	FIGHTMOVE_GROUNDKICK,
	// Opponent
	FIGHTMOVE_HITFRONT,
	FIGHTMOVE_HITBACK,
	FIGHTMOVE_HITRIGHT,
	FIGHTMOVE_HITLEFT,
	FIGHTMOVE_HITBODY,
	FIGHTMOVE_HITCHEST,
	FIGHTMOVE_HITHEAD,
	FIGHTMOVE_HITBIGSTEP,
	FIGHTMOVE_HITONFLOOR,
	FIGHTMOVE_HITBEHIND,
	FIGHTMOVE_IDLE2NORM
};

enum ePedPieceTypes
{
	PEDPIECE_TORSO,
	PEDPIECE_MID,
	PEDPIECE_LEFTARM,
	PEDPIECE_RIGHTARM,
	PEDPIECE_LEFTLEG,
	PEDPIECE_RIGHTLEG,
	PEDPIECE_HEAD,
};

enum eWaitState {
	WAITSTATE_FALSE,
	WAITSTATE_TRAFFIC_LIGHTS,
	WAITSTATE_CROSS_ROAD,
	WAITSTATE_CROSS_ROAD_LOOK,
	WAITSTATE_LOOK_PED,
	WAITSTATE_LOOK_SHOP,
	WAITSTATE_LOOK_ACCIDENT,
	WAITSTATE_FACEOFF_GANG,
	WAITSTATE_DOUBLEBACK,
	WAITSTATE_HITWALL,
	WAITSTATE_TURN180,
	WAITSTATE_SURPRISE,
	WAITSTATE_STUCK,
	WAITSTATE_LOOK_ABOUT,
	WAITSTATE_PLAYANIM_DUCK,
	WAITSTATE_PLAYANIM_COWER,
	WAITSTATE_PLAYANIM_TAXI,
	WAITSTATE_PLAYANIM_HANDSUP,
	WAITSTATE_PLAYANIM_HANDSCOWER,
	WAITSTATE_PLAYANIM_CHAT,
	WAITSTATE_FINISH_FLEE
};

enum eObjective : uint32 {
	OBJECTIVE_NONE,
	OBJECTIVE_IDLE,
	OBJECTIVE_FLEE_TILL_SAFE,
	OBJECTIVE_GUARD_SPOT,
	OBJECTIVE_GUARD_AREA,
	OBJECTIVE_WAIT_IN_CAR,
	OBJECTIVE_WAIT_IN_CAR_THEN_GETOUT,
	OBJECTIVE_KILL_CHAR_ON_FOOT,
	OBJECTIVE_KILL_CHAR_ANY_MEANS,
	OBJECTIVE_FLEE_CHAR_ON_FOOT_TILL_SAFE,
	OBJECTIVE_FLEE_CHAR_ON_FOOT_ALWAYS,
	OBJECTIVE_GOTO_CHAR_ON_FOOT,
	OBJECTIVE_FOLLOW_PED_IN_FORMATION,
	OBJECTIVE_LEAVE_VEHICLE,
	OBJECTIVE_ENTER_CAR_AS_PASSENGER,
	OBJECTIVE_ENTER_CAR_AS_DRIVER,
	OBJECTIVE_FOLLOW_CAR_IN_CAR,
	OBJECTIVE_FIRE_AT_OBJ_FROM_VEHICLE,
	OBJECTIVE_DESTROY_OBJ,
	OBJECTIVE_DESTROY_CAR,
	OBJECTIVE_GOTO_AREA_ANY_MEANS,
	OBJECTIVE_GOTO_AREA_ON_FOOT,
	OBJECTIVE_RUN_TO_AREA,
	OBJECTIVE_23,
	OBJECTIVE_24,
	OBJECTIVE_FIGHT_CHAR,
	OBJECTIVE_SET_LEADER,
	OBJECTIVE_FOLLOW_ROUTE,
	OBJECTIVE_SOLICIT,
	OBJECTIVE_HAIL_TAXI,
	OBJECTIVE_CATCH_TRAIN,
	OBJECTIVE_BUY_ICE_CREAM,
	OBJECTIVE_STEAL_ANY_CAR,
	OBJECTIVE_MUG_CHAR,
	OBJECTIVE_FLEE_CAR,
	OBJECTIVE_35
};

enum {
	RANDOM_CHAR = 1,
	MISSION_CHAR,
};

enum PedLineUpPhase {
	LINE_UP_TO_CAR_START,
	LINE_UP_TO_CAR_END,
	LINE_UP_TO_CAR_2
};

enum PedOnGroundState {
	NO_PED,
	PED_IN_FRONT_OF_ATTACKER,
	PED_ON_THE_FLOOR,
	PED_DEAD_ON_THE_FLOOR
};

enum PedState
{
	PED_NONE,
	PED_IDLE,
	PED_LOOK_ENTITY,
	PED_LOOK_HEADING,
	PED_WANDER_RANGE,
	PED_WANDER_PATH,
	PED_SEEK_POS,
	PED_SEEK_ENTITY,
	PED_FLEE_POS,
	PED_FLEE_ENTITY,
	PED_PURSUE,
	PED_FOLLOW_PATH,
	PED_SNIPER_MODE,
	PED_ROCKET_ODE,
	PED_DUMMY,
	PED_PAUSE,
	PED_ATTACK,
	PED_FIGHT,
	PED_FACE_PHONE,
	PED_MAKE_CALL,
	PED_CHAT,
	PED_MUG,
	PED_AIM_GUN,
	PED_AI_CONTROL,
	PED_SEEK_CAR,
	PED_SEEK_IN_BOAT,
	PED_FOLLOW_ROUTE,
	PED_CPR,
	PED_SOLICIT,
	PED_BUY_ICECREAM,
	PED_INVESTIGATE,
	PED_STEP_AWAY,
	PED_ON_FIRE,

	PED_UNKNOWN,	// HANG_OUT in Fire_Head's idb

	PED_STATES_NO_AI,
	PED_JUMP,
	PED_FALL,
	PED_GETUP,
	PED_STAGGER,
	PED_DIVE_AWAY,

	PED_STATES_NO_ST,
	PED_ENTER_TRAIN,
	PED_EXIT_TRAIN,
	PED_ARREST_PLAYER,
	PED_DRIVING,
	PED_PASSENGER,
	PED_TAXI_PASSENGER,
	PED_OPEN_DOOR,
	PED_DIE,
	PED_DEAD,
	PED_CARJACK,
	PED_DRAG_FROM_CAR,
	PED_ENTER_CAR,
	PED_STEAL_CAR,
	PED_EXIT_CAR,
	PED_HANDS_UP,
	PED_ARRESTED,
};

enum eMoveState {
	PEDMOVE_NONE,
	PEDMOVE_STILL,
	PEDMOVE_WALK,
	PEDMOVE_RUN,
	PEDMOVE_SPRINT,
};

class CVehicle;

class CPed : public CPhysical
{
public:
	// 0x128
	CStoredCollPoly m_collPoly;
	float m_fCollisionSpeed;

	// cf. https://github.com/DK22Pac/plugin-sdk/blob/master/plugin_sa/game_sa/CPed.h from R*
	uint8 bIsStanding : 1;
	uint8 m_ped_flagA2 : 1;
	uint8 bIsAttacking : 1;		// doesn't reset after fist fight, also stores (CTimer::GetTimeInMilliseconds() < m_lastHitTime)
	uint8 bIsPointingGunAt : 1;
	uint8 bIsLooking : 1;
	uint8 m_ped_flagA20 : 1;	// "look" method? - probably missing in SA
	uint8 bIsRestoringLook : 1;
	uint8 bIsAimingGun : 1;

	uint8 bIsRestoringGun : 1;
	uint8 bCanPointGunAtTarget : 1;
	uint8 bIsTalking : 1;
	uint8 bIsInTheAir : 1;
	uint8 bIsLanding : 1;
	uint8 m_ped_flagB20 : 1;
	uint8 m_ped_flagB40 : 1;
	uint8 m_ped_flagB80 : 1;

	uint8 m_ped_flagC1 : 1;
	uint8 bRespondsToThreats : 1;
	uint8 bRenderPedInCar : 1;
	uint8 bChangedSeat : 1;
	uint8 bUpdateAnimHeading : 1;
	uint8 bBodyPartJustCameOff : 1;
	uint8 m_ped_flagC40 : 1;
	uint8 m_ped_flagC80 : 1;

	uint8 m_ped_flagD1 : 1;
	uint8 m_ped_flagD2 : 1; // seen an event
	uint8 m_ped_flagD4 : 1;
	uint8 m_ped_flagD8 : 1;
	uint8 bIsPedDieAnimPlaying : 1;
	uint8 bIsFleeing : 1;
	uint8 m_ped_flagD40 : 1;	// reset when objective changes
	uint8 bScriptObjectiveCompleted : 1;

	uint8 bKindaStayInSamePlace : 1;
	uint8 m_ped_flagE2 : 1;
	uint8 bNotAllowedToDuck : 1;
	uint8 bCrouchWhenShooting : 1;
	uint8 bIsDucking : 1;	// set if you don't want ped to attack
	uint8 bGetUpAnimStarted : 1;
	uint8 bDoBloodyFootprints : 1;
	uint8 m_ped_flagE80 : 1;

	uint8 m_ped_flagF1 : 1;
	uint8 m_ped_flagF2 : 1;
	uint8 m_ped_flagF4 : 1;
	uint8 m_ped_flagF8 : 1;
	uint8 bWillBeQuickJacked : 1;
	uint8 m_ped_flagF20 : 1;
	uint8 m_ped_flagF40 : 1;
	uint8 bDuckAndCover : 1;

	uint8 m_ped_flagG1 : 1;
	uint8 m_ped_flagG2 : 1;
	uint8 m_ped_flagG4 : 1;
	uint8 m_ped_flagG8 : 1;
	uint8 m_ped_flagG10 : 1;
	uint8 m_ped_flagG20 : 1;
	uint8 m_ped_flagG40 : 1;
	uint8 m_ped_flagG80 : 1;

	uint8 m_ped_flagH1 : 1;
	uint8 m_ped_flagH2 : 1;
	uint8 m_ped_flagH4 : 1;
	uint8 bClearObjective : 1;
	uint8 m_ped_flagH10 : 1;
	uint8 m_ped_flagH20 : 1;
	uint8 m_ped_flagH40 : 1;
	uint8 m_ped_flagH80 : 1;

	uint8 m_ped_flagI1 : 1;
	uint8 bNoCriticalHits : 1; // if set, limbs won't came off
	uint8 m_ped_flagI4 : 1;
	uint8 bHasAlreadyBeenRecorded : 1;
	uint8 bIsFell : 1;
	uint8 m_ped_flagI20 : 1;
	uint8 m_ped_flagI40 : 1;
	uint8 m_ped_flagI80 : 1;

	uint8 stuff10[3];
	uint8 CharCreatedBy;
	uint8 field_161;
	uint8 pad_162[2];
	eObjective m_objective;
	eObjective m_prevObjective;
	CPed *m_pedInObjective;
	CVehicle *m_carInObjective;
	uint32 field_174;
	uint32 field_178;
	uint32 field_17C;
	CPed *m_leader;
	uint32 m_pedFormation;
	uint32 m_fearFlags;
	CEntity *m_threatEntity;
	CVector2D m_eventOrThreat;
	uint32 m_eventType;
	CEntity* m_pEventEntity;
	float m_fAngleToEvent;
	AnimBlendFrameData *m_pFrames[PED_NODE_MAX];
	AssocGroupId m_animGroup;
	CAnimBlendAssociation *m_pVehicleAnim;
	CVector2D m_vecAnimMoveDelta;
	CVector m_vecOffsetSeek;
	CPedIK m_pedIK; 
	float m_actionX;
	float m_actionY;
	uint32 m_nPedStateTimer;
	PedState m_nPedState;
	PedState m_nLastPedState;
	eMoveState m_nMoveState;
	int32 m_nStoredMoveState;
	int32 m_nPrevMoveState;
	eWaitState m_nWaitState;
	uint32 m_nWaitTimer;
	void *m_pPathNodesStates[8]; // seems unused
	CVector2D m_stPathNodeStates[10];
	uint16 m_nPathNodes;
	int16 m_nCurPathNode;
	int8 m_nPathState;
private:
	int8 _pad2B5[3];
public:
	CPathNode *m_pNextPathNode;
	CPathNode *m_pLastPathNode;
	float m_fHealth;
	float m_fArmour;
	int16 m_routeLastPoint;
	uint16 m_routePoints;
	int16 m_routePos;
	int16 m_routeType;
	int16 m_routeCurDir;
	uint16 field_2D2;
	CVector2D m_moved;
	float m_fRotationCur;
	float m_fRotationDest;
	float m_headingRate;
	uint16 m_vehEnterType;	// TODO: this is more like a door, not a type
	uint16 m_walkAroundType;
	CEntity *m_pCurrentPhysSurface;
	CVector m_vecOffsetFromPhysSurface;
	CEntity *m_pCurSurface;
	CVector m_vecSeekVehicle;
	CEntity *m_pSeekTarget;
	CVehicle *m_pMyVehicle;
	bool bInVehicle;
	uint8 pad_315[3];
	float field_318;
	bool bRunningToPhone;
	uint8 field_31D;
	int16 m_phoneId;
	uint32 m_lookingForPhone; // unused
	uint32 m_phoneTalkTimer;
	void *m_lastAccident;
	int32 m_nPedType;
	CPedStats *m_pedStats;
	float m_fleeFromPosX;
	float m_fleeFromPosY;
	CEntity *m_fleeFrom;
	uint32 m_fleeTimer;
	uint32 field_344;
	uint32 m_lastThreatTimer;
	CEntity *m_pCollidingEntity;
	uint8 m_stateUnused;
	uint8 pad_351[3];
	uint32 m_timerUnused;
	CEntity *m_targetUnused;
	CWeapon m_weapons[WEAPONTYPE_TOTAL_INVENTORY_WEAPONS];
	eWeaponType m_storedWeapon;
	uint8 m_currentWeapon;			// eWeaponType
	uint8 m_maxWeaponTypeAllowed;	// eWeaponType
	uint8 m_wepSkills;
	uint8 m_wepAccuracy;
	CEntity *m_pPointGunAt;
	CVector m_vecHitLastPos;
	PedFightMoves m_lastFightMove;
	uint8 m_fightButtonPressure;
	int8 m_fightUnk2;	// TODO
	bool m_takeAStepAfterAttack;
	uint8 pad_4B3;
	CFire *m_pFire;
	CEntity *m_pLookTarget;
	float m_fLookDirection;
	int32 m_wepModelID;
	uint32 m_leaveCarTimer;
	uint32 m_getUpTimer;
	uint32 m_lookTimer;
	uint32 m_standardTimer;
	uint32 m_attackTimer;
	uint32 m_lastHitTime; // obviously not correct
	uint32 m_hitRecoverTimer;
	uint32 m_objectiveTimer;
	uint32 m_duckTimer;
	uint32 m_duckAndCoverTimer;
	int32 m_bloodyFootprintCount;
	uint8 m_panicCounter;
	uint8 m_deadBleeding;
	int8 m_bodyPartBleeding;		// PedNode
	uint8 m_field_4F3;
	CPed *m_nearPeds[10];
	uint16 m_numNearPeds;
	int8 m_lastWepDam;
	uint8 pad_51F;
	uint32 m_lastSoundStart;
	uint32 m_soundStart;
	uint16 m_lastQueuedSound;
	uint16 m_queuedSound;
	CVector m_vecSeekPosEx;
	float m_seekExAngle;

	static void *operator new(size_t);
	static void *operator new(size_t, int);
	static void operator delete(void*, size_t);
	static void operator delete(void*, int);

	CPed(uint32 pedType);
	~CPed(void);

	void SetModelIndex(uint32 mi);
	void ProcessControl(void);
	void Teleport(CVector);
	void PreRender(void);
	void Render(void);
	bool SetupLighting(void);
	void RemoveLighting(bool);
	void FlagToDestroyWhenNextProcessed(void);
	int32 ProcessEntityCollision(CEntity*, CColPoint*);

	virtual void SetMoveAnim(void);

	void AddWeaponModel(int id);
	void AimGun(void);
	void KillPedWithCar(CVehicle *veh, float impulse);
	void Say(uint16 audio);
	void SetLookFlag(CEntity *target, bool unknown);
	void SetLookFlag(float direction, bool unknown);
	void SetLookTimer(int time);
	void SetDie(AnimationId anim, float arg1, float arg2);
	void SetDead(void);
	void ApplyHeadShot(eWeaponType weaponType, CVector pos, bool evenOnPlayer);
	void RemoveBodyPart(PedNode nodeId, int8 direction);
	void SpawnFlyingComponent(int, int8);
	bool OurPedCanSeeThisOne(CEntity *target);
	void Avoid(void);
	void Attack(void);
	void ClearAimFlag(void);
	void ClearLookFlag(void);
	void RestorePreviousState(void);
	void ClearAttack(void);
	bool IsPedHeadAbovePos(float zOffset);
	void RemoveWeaponModel(int modelId);
	void SetCurrentWeapon(uint32 weaponType);
	void Duck(void);
	void ClearDuck(void);
	void ClearPointGunAt(void);
	void BeingDraggedFromCar(void);
	void RestartNonPartialAnims(void);
	void LineUpPedWithCar(PedLineUpPhase phase);
	void SetPedPositionInCar(void);
	void PlayFootSteps(void);
	void QuitEnteringCar(void);
	void BuildPedLists(void);
	uint32 GiveWeapon(eWeaponType weaponType, uint32 ammo);
	void CalculateNewOrientation(void);
	float WorkOutHeadingForMovingFirstPerson(float);
	void CalculateNewVelocity(void);
	bool CanPedJumpThis(int32);
	bool CanSeeEntity(CEntity*, float);
	void RestorePreviousObjective(void);
	void SetIdle(void);
	void SetObjective(eObjective, void*);
	void SetObjective(eObjective);
	void SetObjective(eObjective, int16, int16);
	void ClearChat(void);
	void InformMyGangOfAttack(CEntity*);
	void SetFollowRoute(int16, int16);
	void ReactToAttack(CEntity*);
	void SetDuck(uint32);
	void RegisterThreatWithGangPeds(CEntity*);
	bool TurnBody(void);
	void Chat(void);
	void CheckAroundForPossibleCollisions(void);
	void SetSeek(CVector, float);
	void SetSeek(CEntity*, float);
	bool MakePhonecall(void);
	bool FacePhone(void);
	CPed *CheckForDeadPeds(void);
	bool CheckForExplosions(CVector2D &area);
	CPed *CheckForGunShots(void);
	uint8 CheckForPointBlankPeds(CPed*);
	bool CheckIfInTheAir(void);
	void ClearAll(void);
	void SetPointGunAt(CEntity*);
	bool Seek(void);
	bool SetWanderPath(int8);
	void SetFollowPath(CVector);
	void ClearAttackByRemovingAnim(void);
	void SetStoredState(void);
	void StopNonPartialAnims(void);
	bool InflictDamage(CEntity*, eWeaponType, float, ePedPieceTypes, uint8);
	void ClearFlee(void);
	void ClearFall(void);
	void SetGetUp(void);
	void ClearInvestigateEvent(void);
	void ClearLeader(void);
	void ClearLook(void);
	void ClearObjective(void);
	void ClearPause(void);
	void ClearSeek(void);
	void ClearWeapons(void);
	void RestoreGunPosition(void);
	void RestoreHeadingRate(void);
	void SetAimFlag(CEntity* to);
	void SetAimFlag(float angle);
	void SetAmmo(eWeaponType weaponType, uint32 ammo);
	void SetEvasiveStep(CEntity*, uint8);
	void GrantAmmo(eWeaponType, uint32);
	void SetEvasiveDive(CPhysical*, uint8);
	void SetAttack(CEntity*);
	void StartFightAttack(uint8);
	void LoadFightData(void);
	void SetWaitState(eWaitState, void*);
	bool FightStrike(CVector&);
	int GetLocalDirection(CVector2D&);
	void StartFightDefend(uint8, uint8, uint8);
	void PlayHitSound(CPed*);
	void SetFall(int, AnimationId, uint8);
	void SetFlee(CEntity*, int);
	void SetFlee(CVector2D&, int);
	void RemoveInCarAnims(void);
	void CollideWithPed(CPed*);
	void SetDirectionToWalkAroundObject(CEntity*);
	void CreateDeadPedMoney(void);
	void CreateDeadPedWeaponPickups(void);
	void SetAttackTimer(uint32);
	void SetBeingDraggedFromCar(CVehicle*, uint32, bool);
	void SetRadioStation(void);
	void SetBuyIceCream(void);
	void SetChat(CEntity*, uint32);
	void DeadPedMakesTyresBloody(void);
	void MakeTyresMuddySectorList(CPtrList&);
	uint8 DoesLOSBulletHitPed(CColPoint &point);
	bool DuckAndCover(void);
	void EndFight(uint8);
	void EnterCar(void);
	uint8 GetNearestTrainPedPosition(CVehicle*, CVector&);
	uint8 GetNearestTrainDoor(CVehicle*, CVector&);
	void LineUpPedWithTrain(void);
	void ExitCar(void);
	void Fight(void);

	// Static methods
	static CVector GetLocalPositionToOpenCarDoor(CVehicle *veh, uint32 component, float offset);
	static CVector GetPositionToOpenCarDoor(CVehicle *veh, uint32 component, float seatPosMult);
	static CVector GetPositionToOpenCarDoor(CVehicle* veh, uint32 component);

	// Callbacks
	static RwObject *SetPedAtomicVisibilityCB(RwObject *object, void *data);
	static RwFrame *RecurseFrameChildrenVisibilityCB(RwFrame *frame, void *data);
	static void PedGetupCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedStaggerCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedEvadeCB(CAnimBlendAssociation *assoc, void *arg);
	static void FinishDieAnimCB(CAnimBlendAssociation *assoc, void *arg);
	static void FinishedWaitCB(CAnimBlendAssociation *assoc, void *arg);
	static void FinishLaunchCB(CAnimBlendAssociation *assoc, void *arg);
	static void FinishHitHeadCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedAnimGetInCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedAnimDoorOpenCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedAnimPullPedOutCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedAnimDoorCloseCB(CAnimBlendAssociation *assoc, void *arg);
	static void SetInCarCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedSetOutCarCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedAnimAlignCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedSetDraggedOutCarCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedAnimStepOutCarCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedSetInTrainCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedSetOutTrainCB(CAnimBlendAssociation *assoc, void *arg);
	static void FinishedAttackCB(CAnimBlendAssociation *assoc, void *arg);
	static void FinishFightMoveCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedAnimDoorCloseRollingCB(CAnimBlendAssociation *assoc, void *arg);
	static void FinishJumpCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedLandCB(CAnimBlendAssociation *assoc, void *arg);
	static void RestoreHeadingRateCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedSetQuickDraggedOutCarPositionCB(CAnimBlendAssociation *assoc, void *arg);
	static void PedSetDraggedOutCarPositionCB(CAnimBlendAssociation *assoc, void *arg);

	// functions that I see unnecessary to hook
	bool IsPlayer(void);
	bool UseGroundColModel(void);
	bool CanSetPedState(void);
	bool IsPedInControl(void);
	bool CanPedDriveOff(void);
	bool CanBeDeleted(void);
	bool CanStrafeOrMouseControl(void);
	bool CanPedReturnToState(void);
	void SetMoveState(eMoveState);
	bool IsTemporaryObjective(eObjective objective);
	void SetObjectiveTimer(int);
	bool SelectGunIfArmed(void);
	bool IsPointerValid(void);
	void SortPeds(CPed**, int, int);
	void ForceStoredObjective(eObjective);
	void SetStoredObjective(void);
	void SetLeader(CEntity* leader);
	void SetPedStats(ePedStats);
	bool IsGangMember(void);
	void Die(void);
	void EnterTrain(void);
	void ExitTrain(void);
	void Fall(void);

	bool HasWeapon(uint8 weaponType) { return m_weapons[weaponType].m_eWeaponType == weaponType; }
	CWeapon &GetWeapon(uint8 weaponType) { return m_weapons[weaponType]; }
	CWeapon *GetWeapon(void) { return &m_weapons[m_currentWeapon]; }
	RwFrame *GetNodeFrame(int nodeId) { return m_pFrames[nodeId]->frame; }
	PedState GetPedState(void) { return m_nPedState; }
	void SetPedState(PedState state) { m_nPedState = state; }

	// set by 0482:set_threat_reaction_range_multiplier opcode
	static uint16 &distanceMultToCountPedNear;

	static CVector &offsetToOpenRegularCarDoor;
	static CVector &offsetToOpenLowCarDoor;
	static CVector &offsetToOpenVanDoor;
	static bool &bNastyLimbsCheat;
	static bool &bPedCheat2;
	static bool &bPedCheat3;
	static CColPoint &ms_tempColPoint;
	static uint16 &nPlayerInComboMove;
	static FightMove (&tFightMoves)[24];
	static CPedAudioData (&PedAudioData)[38];

#ifndef FINAL
	static bool bUnusedFightThingOnPlayer;
#endif
};

void FinishFuckUCB(CAnimBlendAssociation *assoc, void *arg);

static_assert(offsetof(CPed, m_nPedState) == 0x224, "CPed: error");
static_assert(offsetof(CPed, m_pCurSurface) == 0x2FC, "CPed: error");
static_assert(offsetof(CPed, m_pMyVehicle) == 0x310, "CPed: error");
static_assert(offsetof(CPed, m_nPedType) == 0x32C, "CPed: error");
static_assert(offsetof(CPed, m_pCollidingEntity) == 0x34C, "CPed: error");
static_assert(offsetof(CPed, m_weapons) == 0x35C, "CPed: error");
static_assert(offsetof(CPed, m_currentWeapon) == 0x498, "CPed: error");
static_assert(offsetof(CPed, m_lookTimer) == 0x4CC, "CPed: error");
static_assert(offsetof(CPed, m_bodyPartBleeding) == 0x4F2, "CPed: error");
static_assert(offsetof(CPed, m_pedInObjective) == 0x16C, "CPed: error");
static_assert(offsetof(CPed, m_pEventEntity) == 0x19C, "CPed: error");
static_assert(sizeof(CPed) == 0x53C, "CPed: error");
