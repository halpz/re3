#pragma once

#include "Camera.h"
#include "Ped.h"
#include "Pools.h"
#include "Pickup.h"
#include "Radar.h"
#include "References.h"
#include "Vehicle.h"
#include "Wanted.h"
#include "World.h"
#include "common.h"

struct CAddressInReplayBuffer
{
	uint32 m_nOffset;
	uint8 *m_pBase;
	uint8 m_bSlot;
};

struct CStoredAnimationState
{
	uint8 animId;
	uint8 time;
	uint8 speed;
	uint8 secAnimId;
	uint8 secTime;
	uint8 secSpeed;
	uint8 blendAmount;
	uint8 partAnimId;
	uint8 partAnimTime;
	uint8 partAnimSpeed;
	uint8 partBlendAmount;
};

struct CStoredDetailedAnimationState
{
	uint8 aAnimId[3];
	uint8 aCurTime[3];
	uint8 aSpeed[3];
	uint8 aBlendAmount[3];
	uint8 aFunctionCallbackID[3];
	uint16 aFlags[3];
	uint8 aAnimId2[6];
	uint8 aCurTime2[6];
	uint8 aSpeed2[6];
	uint8 aBlendAmount2[6];
	uint8 aFunctionCallbackID2[6];
	uint16 aFlags2[6];
};

class CReplay
{
	enum {
		MODE_RECORD = 0,
		MODE_PLAYBACK = 1
	};

	enum {
		REPLAYCAMMODE_ASSTORED = 0,
		REPLAYCAMMODE_TOPDOWN = 1,
		REPLAYCAMMODE_FIXED = 2
	};

	enum {
		REPLAYPACKET_END = 0,
		REPLAYPACKET_VEHICLE = 1,
		REPLAYPACKET_PED_HEADER = 2,
		REPLAYPACKET_PED_UPDATE = 3,
		REPLAYPACKET_GENERAL = 4,
		REPLAYPACKET_CLOCK = 5,
		REPLAYPACKET_WEATHER = 6,
		REPLAYPACKET_ENDOFFRAME = 7,
		REPLAYPACKET_TIMER = 8,
		REPLAYPACKET_BULLET_TRACES = 9
	};

	enum {
		REPLAYBUFFER_UNUSED = 0,
		REPLAYBUFFER_PLAYBACK = 1,
		REPLAYBUFFER_RECORD = 2
	};


	struct tGeneralPacket
	{
		uint8 type;
		bool in_rcvehicle;
		CMatrix camera_pos;
		CVector player_pos;
	};
	static_assert(sizeof(tGeneralPacket) == 88, "tGeneralPacket: error");

	struct tClockPacket
	{
		uint8 type;
		uint8 hours;
		uint8 minutes;
	private:
		uint8 __align;
	};
	static_assert(sizeof(tClockPacket) == 4, "tClockPacket: error");

	struct tWeatherPacket
	{
		uint8 type;
		uint8 old_weather;
		uint8 new_weather;
		float interpolation;
	};
	static_assert(sizeof(tWeatherPacket) == 8, "tWeatherPacket: error");

	struct tTimerPacket
	{
		uint8 type;
		uint32 timer;
	};
	static_assert(sizeof(tTimerPacket) == 8, "tTimerPacket: error");

	struct tPedHeaderPacket
	{
		uint8 type;
		uint8 index;
		uint16 mi;
		uint8 pedtype;
	private:
		uint8 __align[3];
	};
	static_assert(sizeof(tPedHeaderPacket) == 8, "tPedHeaderPacket: error");

	struct tBulletTracePacket
	{
		uint8 type;
		uint8 frames;
		uint8 lifetime;
		uint8 index;
		CVector inf;
		CVector sup;
	};
	static_assert(sizeof(tBulletTracePacket) == 28, "tBulletTracePacket: error");

	struct tEndOfFramePacket
	{
		uint8 type;
	private:
		uint8 __align[3];
	};
	static_assert(sizeof(tEndOfFramePacket) == 4, "tEndOfFramePacket: error");

	struct tPedUpdatePacket
	{
		uint8 type;
		uint8 index;
		int8 heading;
		int8 vehicle_index;
		CStoredAnimationState anim_state;
		CCompressedMatrixNotAligned matrix;
		int8 assoc_group_id;
		uint8 weapon_model;
	};
	static_assert(sizeof(tPedUpdatePacket) == 40, "tPedUpdatePacket: error");

	struct tVehicleUpdatePacket
	{
		uint8 type;
		uint8 index;
		uint8 health;
		uint8 acceleration;
		CCompressedMatrixNotAligned matrix;
		int8 door_angles[2];
		uint16 mi;
		uint32 panels;
		int8 velocityX;
		int8 velocityY;
		int8 velocityZ;
		union{
			int8 car_gun;
			uint8 wheel_state;
		};
		uint8 wheel_susp_dist[4];
		uint8 wheel_rotation[4];
		uint8 door_status;
		uint8 primary_color;
		uint8 secondary_color;
	};
	static_assert(sizeof(tVehicleUpdatePacket) == 48, "tVehicleUpdatePacket: error");

private:
	static uint8 &Mode;
	static CAddressInReplayBuffer &Record;
	static CAddressInReplayBuffer &Playback;
	static uint8 *&pBuf0;
	static CAutomobile *&pBuf1;
	static uint8 *&pBuf2;
	static CPlayerPed *&pBuf3;
	static uint8 *&pBuf4;
	static CCutsceneHead *&pBuf5;
	static uint8 *&pBuf6;
	static CPtrNode *&pBuf7;
	static uint8 *&pBuf8;
	static CEntryInfoNode *&pBuf9;
	static uint8 *&pBuf10;
	static CDummyPed *&pBuf11;
	static CBlip *&pRadarBlips;
	static CCamera *&pStoredCam;
	static CSector *&pWorld1;
	static CReference *&pEmptyReferences;
	static CStoredDetailedAnimationState *&pPedAnims;
	static CPickup *&pPickups;
	static CReference *&pReferences;
	static uint8 (&BufferStatus)[8];
	static uint8 (&Buffers)[8][100000];
	static bool &bPlayingBackFromFile;
	static bool &bReplayEnabled;
	static uint32 &SlowMotion;
	static uint32 &FramesActiveLookAroundCam;
	static bool &bDoLoadSceneWhenDone;
	static CPtrList &WorldPtrList;
	static CPtrList &BigBuildingPtrList;
	static CWanted &PlayerWanted;
	static CPlayerInfo &PlayerInfo;
	static uint32 &Time1;
	static uint32 &Time2;
	static uint32 &Time3;
	static uint32 &Time4;
	static uint32 &Frame;
	static uint8 &ClockHours;
	static uint8 &ClockMinutes;
	static uint16 &OldWeatherType;
	static uint16 &NewWeatherType;
	static float &WeatherInterpolationValue;
	static float &TimeStepNonClipped;
	static float &TimeStep;
	static float &TimeScale;
	static float &CameraFixedX;
	static float &CameraFixedY;
	static float &CameraFixedZ;
	static int32 &OldRadioStation;
	static int8 &CameraMode;
	static bool &bAllowLookAroundCam;
	static float &LoadSceneX;
	static float &LoadSceneY;
	static float &LoadSceneZ;
	static float &CameraFocusX;
	static float &CameraFocusY;
	static float &CameraFocusZ;
	static bool &bPlayerInRCBuggy;

public:
	static void Init(void);
	static void DisableReplays(void);
	static void EnableReplays(void);
	static void Update(void);
	static void FinishPlayback(void);
	static void EmptyReplayBuffer(void);
	static void Display(void);
	static void TriggerPlayback(uint8 cam_mode, float cam_x, float cam_y, float cam_z, bool load_scene);
	static void StreamAllNecessaryCarsAndPeds(void);
	static bool ShouldStandardCameraBeProcessed(void);

	inline static bool IsPlayingBack() { return Mode == MODE_PLAYBACK; }
	inline static bool IsPlayingBackFromFile() { return bPlayingBackFromFile; }

//private:
	static void RecordThisFrame(void);
	static void StorePedUpdate(CPed *ped, int id);
	static void StorePedAnimation(CPed *ped, CStoredAnimationState *state);
	static void StoreDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state);
	static void ProcessPedUpdate(CPed *ped, float interpolation, CAddressInReplayBuffer *buffer);
	static void RetrievePedAnimation(CPed *ped, CStoredAnimationState *state);
	static void RetrieveDetailedPedAnimation(CPed *ped, CStoredDetailedAnimationState *state);
	static void PlaybackThisFrame(void);
	static void StoreCarUpdate(CVehicle *vehicle, int id);
	static void ProcessCarUpdate(CVehicle *vehicle, float interpolation, CAddressInReplayBuffer *buffer);
	static bool PlayBackThisFrameInterpolation(CAddressInReplayBuffer *buffer, float interpolation, uint32 *pTimer);
	static void ProcessReplayCamera(void);
	static void StoreStuffInMem(void);
	static void RestoreStuffFromMem(void);
	static void EmptyPedsAndVehiclePools(void);
	static void EmptyAllPools(void);
	static void MarkEverythingAsNew(void);
	static void SaveReplayToHD(void);
	static void FindFirstFocusCoordinate(CVector *coord);
	static void ProcessLookAroundCam(void);
	static size_t FindSizeOfPacket(uint8);
};
