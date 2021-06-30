#include "common.h"

#include "AudioManager.h"
#include "audio_enums.h"

#include "Automobile.h"
#include "Boat.h"
#include "Bridge.h"
#include "Camera.h"
#include "Cranes.h"
#include "DMAudio.h"
#include "Entity.h"
#include "Explosion.h"
#include "Fire.h"
#include "Garages.h"
#include "General.h"
#include "HandlingMgr.h"
#include "Heli.h"
#include "ModelIndices.h"
#include "MusicManager.h"
#include "Pad.h"
#include "Ped.h"
#include "Physical.h"
#include "Placeable.h"
#include "Plane.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "Projectile.h"
#include "ProjectileInfo.h"
#include "Replay.h"
#include "Stats.h"
#include "SurfaceTable.h"
#include "Train.h"
#include "Transmission.h"
#include "Vehicle.h"
#include "WaterCannon.h"
#include "Weather.h"
#include "ZoneCull.h"
#include "sampman.h"
#include "Bike.h"
#include "WindModifiers.h"
#include "Fluff.h"
#include "Script.h"
#include "Wanted.h"

#ifndef GTA_PS2
#define CHANNEL_PLAYER_VEHICLE_ENGINE m_nActiveSamples
#endif

enum PLAY_STATUS { PLAY_STATUS_STOPPED = 0, PLAY_STATUS_PLAYING, PLAY_STATUS_FINISHED };
enum LOADING_STATUS { LOADING_STATUS_NOT_LOADED = 0, LOADING_STATUS_LOADED, LOADING_STATUS_FAILED };

void
cAudioManager::PreInitialiseGameSpecificSetup() const
{
	BankStartOffset[SFX_BANK_0] = SAMPLEBANK_START;
#ifdef GTA_PS2
	BankStartOffset[SAMPLEBANK_CAR_PACARD] = SFX_CAR_ACCEL_1;
	BankStartOffset[SAMPLEBANK_CAR_PATHFINDER] = SFX_CAR_ACCEL_2;
	BankStartOffset[SAMPLEBANK_CAR_PORSCHE] = SFX_CAR_ACCEL_3;
	BankStartOffset[SAMPLEBANK_CAR_SPIDER] = SFX_CAR_ACCEL_4;
	BankStartOffset[SAMPLEBANK_CAR_MERC] = SFX_CAR_ACCEL_5;
	BankStartOffset[SAMPLEBANK_CAR_MACKTRUCK] = SFX_CAR_ACCEL_6;
	BankStartOffset[SAMPLEBANK_CAR_HOTROD] = SFX_CAR_ACCEL_7;
	BankStartOffset[SAMPLEBANK_CAR_COBRA] = SFX_CAR_ACCEL_8;
	BankStartOffset[SAMPLEBANK_CAR_NONE] = SFX_CAR_ACCEL_9;
	BankStartOffset[SAMPLEBANK_FRONTEND] = SFX_PAGE_CHANGE_AND_BACK_LEFT;
	BankStartOffset[SAMPLEBANK_TRAIN] = SFX_TRAIN_STATION_AMBIENCE_LOOP;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_1] = SFX_CLUB_1;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_2] = SFX_CLUB_2;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_3] = SFX_CLUB_3;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_4] = SFX_CLUB_4;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_5] = SFX_CLUB_5;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_6] = SFX_CLUB_6;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_7] = SFX_CLUB_7;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_8] = SFX_CLUB_8;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_9] = SFX_CLUB_9;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_10] = SFX_CLUB_10;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_11] = SFX_CLUB_11;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_12] = SFX_CLUB_12;
	BankStartOffset[SAMPLEBANK_BUILDING_CLUB_RAGGA] = SFX_CLUB_RAGGA;
	BankStartOffset[SAMPLEBANK_BUILDING_STRIP_CLUB_1] = SFX_STRIP_CLUB_1;
	BankStartOffset[SAMPLEBANK_BUILDING_STRIP_CLUB_2] = SFX_STRIP_CLUB_2;
	BankStartOffset[SAMPLEBANK_BUILDING_WORKSHOP] = SFX_WORKSHOP_1;
	BankStartOffset[SAMPLEBANK_BUILDING_PIANO_BAR] = SFX_PIANO_BAR_1;
	BankStartOffset[SAMPLEBANK_BUILDING_SAWMILL] = SFX_SAWMILL_LOOP;
	BankStartOffset[SAMPLEBANK_BUILDING_DOG_FOOD_FACTORY] = SFX_DOG_FOOD_FACTORY;
	BankStartOffset[SAMPLEBANK_BUILDING_LAUNDERETTE] = SFX_LAUNDERETTE_LOOP;
	BankStartOffset[SAMPLEBANK_BUILDING_RESTAURANT_CHINATOWN] = SFX_RESTAURANT_CHINATOWN;
	BankStartOffset[SAMPLEBANK_BUILDING_RESTAURANT_ITALY] = SFX_RESTAURANT_ITALY;
	BankStartOffset[SAMPLEBANK_BUILDING_RESTAURANT_GENERIC_1] = SFX_RESTAURANT_GENERIC_1;
	BankStartOffset[SAMPLEBANK_BUILDING_RESTAURANT_GENERIC_2] = SFX_RESTAURANT_GENERIC_2;
	BankStartOffset[SAMPLEBANK_BUILDING_AIRPORT] = SFX_AIRPORT_ANNOUNCEMENT_1;
	BankStartOffset[SAMPLEBANK_BUILDING_SHOP] = SFX_SHOP_LOOP;
	BankStartOffset[SAMPLEBANK_BUILDING_CINEMA] = SFX_CINEMA_BASS_1;
	BankStartOffset[SAMPLEBANK_BUILDING_DOCKS] = SFX_DOCKS_FOGHORN;
	BankStartOffset[SAMPLEBANK_BUILDING_HOME] = SFX_HOME_1;
	BankStartOffset[SAMPLEBANK_BUILDING_PORN_1] = SFX_PORN_1_LOOP;
	BankStartOffset[SAMPLEBANK_BUILDING_PORN_2] = SFX_PORN_2_LOOP;
	BankStartOffset[SAMPLEBANK_BUILDING_PORN_3] = SFX_PORN_3_LOOP;
	BankStartOffset[SAMPLEBANK_BUILDING_POLICE_BALL] = SFX_POLICE_BALL_1;
	BankStartOffset[SAMPLEBANK_BUILDING_BANK_ALARM] = SFX_BANK_ALARM_1;
	BankStartOffset[SAMPLEBANK_BUILDING_RAVE_INDUSTRIAL] = SFX_RAVE_INDUSTRIAL;
	BankStartOffset[SAMPLEBANK_BUILDING_RAVE_COMMERCIAL] = SFX_RAVE_COMMERCIAL;
	BankStartOffset[SAMPLEBANK_BUILDING_RAVE_SUBURBAN] = SFX_RAVE_SUBURBAN;
	BankStartOffset[SAMPLEBANK_BUILDING_RAVE_COMMERCIAL_2] = SFX_RAVE_COMMERCIAL_2;
	BankStartOffset[SAMPLEBANK_BUILDING_39] = SFX_CLUB_1_1;
	BankStartOffset[SAMPLEBANK_BUILDING_40] = SFX_CLUB_1_2;
	BankStartOffset[SAMPLEBANK_BUILDING_41] = SFX_CLUB_1_3;
	BankStartOffset[SAMPLEBANK_BUILDING_42] = SFX_CLUB_1_4;
	BankStartOffset[SAMPLEBANK_BUILDING_43] = SFX_CLUB_1_5;
	BankStartOffset[SAMPLEBANK_BUILDING_44] = SFX_CLUB_1_6;
	BankStartOffset[SAMPLEBANK_BUILDING_45] = SFX_CLUB_1_7;
	BankStartOffset[SAMPLEBANK_BUILDING_46] = SFX_CLUB_1_8;
	BankStartOffset[SAMPLEBANK_BUILDING_47] = SFX_CLUB_1_9;
	BankStartOffset[SAMPLEBANK_EXTRAS] = SFX_EXPLOSION_1;
#endif // GTA_PS2
	BankStartOffset[SFX_BANK_PED_COMMENTS] = SAMPLEBANK_PED_START;
}

void
cAudioManager::PostInitialiseGameSpecificSetup()
{
	m_nFireAudioEntity = CreateEntity(AUDIOTYPE_FIRE, &gFireManager);
	if (m_nFireAudioEntity >= 0)
		SetEntityStatus(m_nFireAudioEntity, TRUE);

	m_nCollisionEntity = CreateEntity(AUDIOTYPE_COLLISION, (void *)1);
	if (m_nCollisionEntity >= 0)
		SetEntityStatus(m_nCollisionEntity, TRUE);

	m_nFrontEndEntity = CreateEntity(AUDIOTYPE_FRONTEND, (void *)1);
	if (m_nFrontEndEntity >= 0)
		SetEntityStatus(m_nFrontEndEntity, TRUE);

	m_nProjectileEntity = CreateEntity(AUDIOTYPE_PROJECTILE, (void *)1);
	if (m_nProjectileEntity >= 0)
		SetEntityStatus(m_nProjectileEntity, TRUE);

	m_nWaterCannonEntity = CreateEntity(AUDIOTYPE_WATERCANNON, (void *)1);
	if (m_nWaterCannonEntity >= 0)
		SetEntityStatus(m_nWaterCannonEntity, TRUE);

	m_nPoliceChannelEntity = CreateEntity(AUDIOTYPE_POLICERADIO, (void *)1);
	if (m_nPoliceChannelEntity >= 0)
		SetEntityStatus(m_nPoliceChannelEntity, TRUE);
#ifdef GTA_BRIDGE
	m_nBridgeEntity = CreateEntity(AUDIOTYPE_BRIDGE, (void*)1);
	if (m_nBridgeEntity >= 0)
		SetEntityStatus(m_nBridgeEntity, TRUE);
#endif // GTA_BRIDGE
	m_nEscalatorEntity = CreateEntity(AUDIOTYPE_ESCALATOR, (void*)1);
	if (m_nEscalatorEntity >= 0)
		SetEntityStatus(m_nEscalatorEntity, TRUE);

	m_nExtraSoundsEntity = CreateEntity(AUDIOTYPE_EXTRA_SOUNDS, (void*)1);
	if (m_nExtraSoundsEntity >= 0)
		SetEntityStatus(m_nExtraSoundsEntity, TRUE);


	m_sMissionAudio.m_nSampleIndex[0] = NO_SAMPLE;
	m_sMissionAudio.m_nLoadingStatus[0] = LOADING_STATUS_NOT_LOADED;
	m_sMissionAudio.m_nPlayStatus[0] = PLAY_STATUS_STOPPED;
	m_sMissionAudio.m_bIsPlaying[0] = FALSE;
	m_sMissionAudio.m_bIsPlayed[0] = FALSE;
	m_sMissionAudio.m_bPredefinedProperties[0] = TRUE;
	m_sMissionAudio.m_nMissionAudioCounter[0] = 0;
	m_sMissionAudio.m_bIsMobile[0] = FALSE;
	field_5538 = 127;
	m_sMissionAudio.m_nSampleIndex[1] = NO_SAMPLE;
	m_sMissionAudio.m_nLoadingStatus[1] = LOADING_STATUS_NOT_LOADED;
	m_sMissionAudio.m_nPlayStatus[1] = PLAY_STATUS_STOPPED;
	m_sMissionAudio.m_bIsPlaying[1] = FALSE;
	m_sMissionAudio.m_bIsPlayed[1] = FALSE;
	m_sMissionAudio.m_bPredefinedProperties[1] = TRUE;
	m_sMissionAudio.m_nMissionAudioCounter[1] = 0;
	m_sMissionAudio.m_bIsMobile[1] = FALSE;
	field_5538 = 127;

	ResetAudioLogicTimers(CTimer::GetTimeInMilliseconds());
	m_bIsPlayerShutUp = FALSE;
	m_nPlayerMood = PLAYER_MOOD_CALM;
	m_nPlayerMoodTimer = 0;
}

void
cAudioManager::PreTerminateGameSpecificShutdown()
{
#ifdef GTA_BRIDGE
	if (m_nBridgeEntity >= 0) {
		DestroyEntity(m_nBridgeEntity);
		m_nBridgeEntity = AEHANDLE_NONE;
	}
#endif
	if (m_nEscalatorEntity >= 0) {
		DestroyEntity(m_nEscalatorEntity);
		m_nEscalatorEntity = AEHANDLE_NONE;
	}
	if (m_nExtraSoundsEntity >= 0) {
		DestroyEntity(m_nExtraSoundsEntity);
		m_nExtraSoundsEntity = AEHANDLE_NONE;
	}
	if (m_nPoliceChannelEntity >= 0) {
		DestroyEntity(m_nPoliceChannelEntity);
		m_nPoliceChannelEntity = AEHANDLE_NONE;
	}
	if (m_nWaterCannonEntity >= 0) {
		DestroyEntity(m_nWaterCannonEntity);
		m_nWaterCannonEntity = AEHANDLE_NONE;
	}
	if (m_nFireAudioEntity >= 0) {
		DestroyEntity(m_nFireAudioEntity);
		m_nFireAudioEntity = AEHANDLE_NONE;
	}
	if (m_nCollisionEntity >= 0) {
		DestroyEntity(m_nCollisionEntity);
		m_nCollisionEntity = AEHANDLE_NONE;
	}
	if (m_nFrontEndEntity >= 0) {
		DestroyEntity(m_nFrontEndEntity);
		m_nFrontEndEntity = AEHANDLE_NONE;
	}
	if (m_nProjectileEntity >= 0) {
		DestroyEntity(m_nProjectileEntity);
		m_nProjectileEntity = AEHANDLE_NONE;
	}
}

void
cAudioManager::PostTerminateGameSpecificShutdown()
{
	;
}

void
cAudioManager::ResetAudioLogicTimers(uint32 timer)
{
	for (int32 i = 0; i < m_nAudioEntitiesTotal; i++) {
		if (m_asAudioEntities[m_anAudioEntityIndices[i]].m_nType == AUDIOTYPE_PHYSICAL) {
			CPed *ped = (CPed *)m_asAudioEntities[m_anAudioEntityIndices[i]].m_pEntity;
			if (ped->IsPed()) {
				ped->m_lastSoundStart = timer;
				ped->m_soundStart = timer + m_anRandomTable[0] % 3000;
			}
		}
	}
	ClearMissionAudio(0);
	ClearMissionAudio(1);
	SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
}

void
cAudioManager::ProcessReverb() const
{
#ifdef FIX_BUGS
	const uint32 numChannels = NUM_CHANNELS_GENERIC;
#else
	const uint32 numChannels = NUM_CHANNELS_GENERIC+1;
#endif

	if (SampleManager.UpdateReverb() && m_bDynamicAcousticModelingStatus) {
#ifndef GTA_PS2
		for (uint32 i = 0; i < numChannels; i++) {
			if (m_asActiveSamples[i].m_bReverbFlag)
				SampleManager.SetChannelReverbFlag(i, TRUE);
		}
#endif
	}
}

float
cAudioManager::GetDistanceSquared(const CVector &v) const
{
	const CVector &c = TheCamera.GetPosition();
	return sq(v.x - c.x) + sq(v.y - c.y) + sq((v.z - c.z) * 0.2f);
}

void
cAudioManager::CalculateDistance(bool8 &distCalculated, float dist)
{
	if (!distCalculated) {
		m_sQueueSample.m_fDistance = Sqrt(dist);
		distCalculated = TRUE;
	}
}

CVehicle *cAudioManager::FindVehicleOfPlayer()
{
	CVehicle* vehicle = FindPlayerVehicle();
	CPlayerPed* ped = FindPlayerPed();
	if (vehicle == nil && ped != nil) {
		CEntity *attachedTo = ped->m_attachedTo;
		if (attachedTo && attachedTo->IsVehicle())
			vehicle = (CVehicle*)attachedTo;
	}
	return vehicle;
}

void
cAudioManager::ProcessPlayerMood()
{
	CPlayerPed *playerPed;
	uint32& lastMissionPassedTime = CTheScripts::GetLastMissionPassedTime();
	uint32 curTime = CTimer::GetTimeInMilliseconds();

	if (m_nPlayerMoodTimer <= curTime) {
		playerPed = FindPlayerPed();
		if (playerPed != nil) {

			if (playerPed->m_pWanted->GetWantedLevel() > 3) {
				m_nPlayerMood = PLAYER_MOOD_ANGRY;
				return;
			}
			if (playerPed->m_pWanted->GetWantedLevel() > 1) {
				m_nPlayerMood = PLAYER_MOOD_PISSED_OFF;
				return;
			}

			if (lastMissionPassedTime != -1) {
				if (curTime < lastMissionPassedTime) {
					lastMissionPassedTime = curTime;
					return;
				}
				if (curTime < lastMissionPassedTime + 180000) {
					m_nPlayerMood = PLAYER_MOOD_WISECRACKING;
					return;
				}
			}
			m_nPlayerMood = PLAYER_MOOD_CALM;
		}
	}
}

void
cAudioManager::ProcessSpecial()
{
	CPlayerPed *playerPed;

	if (m_nUserPause) {
		if (!m_nPreviousUserPause) {
			SampleManager.SetEffectsFadeVolume(MAX_VOLUME);
			SampleManager.SetMusicFadeVolume(MAX_VOLUME);
		}
	} else {
		if (!CReplay::IsPlayingBack())
			ProcessPlayerMood();
		playerPed = FindPlayerPed();
		if (playerPed != nil) {
			if (playerPed->m_audioEntityId >= 0 && m_asAudioEntities[playerPed->m_audioEntityId].m_bIsUsed) {
				if (playerPed->EnteringCar()) {
					if(!playerPed->bInVehicle && CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle == nil)
						SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
				}
			}
		}
	}
}

void
cAudioManager::ProcessEntity(int32 id)
{
	if (m_asAudioEntities[id].m_bStatus) {
		m_sQueueSample.m_nEntityIndex = id;
		switch (m_asAudioEntities[id].m_nType) {
		case AUDIOTYPE_PHYSICAL:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessPhysical(id);
			}
			break;
		case AUDIOTYPE_EXPLOSION:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessExplosions(id);
			}
			break;
		case AUDIOTYPE_FIRE:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessFires(id);
			}
			break;
		case AUDIOTYPE_WEATHER:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				if(CGame::currArea == AREA_MAIN_MAP || CGame::currArea == AREA_EVERYWHERE)
					ProcessWeather(id);
			}
			break;
/*		case AUDIOTYPE_CRANE:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessCrane();
			}
			break;*/
		case AUDIOTYPE_SCRIPTOBJECT:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessScriptObject(id);
			}
			break;
#ifdef GTA_BRIDGE
		case AUDIOTYPE_BRIDGE:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessBridge();
			}
			break;
#endif
		case AUDIOTYPE_FRONTEND:
			m_sQueueSample.m_bReverbFlag = FALSE;
			ProcessFrontEnd();
			break;
		case AUDIOTYPE_PROJECTILE:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessProjectiles();
			}
			break;
		case AUDIOTYPE_GARAGE:
			if (!m_nUserPause)
				ProcessGarages();
			break;
		case AUDIOTYPE_FIREHYDRANT:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessFireHydrant();
			}
			break;
		case AUDIOTYPE_WATERCANNON:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessWaterCannon(id);
			}
			break;
		case AUDIOTYPE_ESCALATOR:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessEscalators();
			}
			break;
		case AUDIOTYPE_EXTRA_SOUNDS:
			if (!m_nUserPause) {
				m_sQueueSample.m_bReverbFlag = TRUE;
				ProcessExtraSounds();
			}
			break;
		default:
			return;
		}
	}
}

void
cAudioManager::ProcessPhysical(int32 id)
{
	CPhysical *entity = (CPhysical *)m_asAudioEntities[id].m_pEntity;
	if (entity) {
		switch (entity->GetType()) {
		case ENTITY_TYPE_VEHICLE:
			ProcessVehicle((CVehicle *)m_asAudioEntities[id].m_pEntity);
			break;
		case ENTITY_TYPE_PED:
			ProcessPed((CPhysical *)m_asAudioEntities[id].m_pEntity);
			break;
		default:
			return;
		}
	}
}

#pragma region VEHICLE AUDIO
enum eVehicleModel {
	LANDSTAL,
	IDAHO,
	STINGER,
	LINERUN,
	PEREN,
	SENTINEL,
	RIO,
	FIRETRUK,
	TRASH,
	STRETCH,
	MANANA,
	INFERNUS,
	VOODOO,
	PONY,
	MULE,
	CHEETAH,
	AMBULAN,
	FBICAR,
	MOONBEAM,
	ESPERANT,
	TAXI,
	WASHING,
	BOBCAT,
	MRWHOOP,
	BFINJECT,
	HUNTER,
	POLICE,
	ENFORCER,
	SECURICA,
	BANSHEE,
	PREDATOR,
	BUS,
	RHINO,
	BARRACKS,
	CUBAN,
	CHOPPER,
	ANGEL,
	COACH,
	CABBIE,
	STALLION,
	RUMPO,
	RCBANDIT,
	ROMERO,
	PACKER,
	SENTXS,
	ADMIRAL,
	SQUALO,
	SEASPAR,
	PIZZABOY,
	GANGBUR,
	AIRTRAIN,
	DEADDODO,
	SPEEDER,
	REEFER,
	TROPIC,
	FLATBED,
	YANKEE,
	CADDY,
	ZEBRA,
	TOPFUN,
	SKIMMER,
	PCJ600,
	FAGGIO,
	FREEWAY,
	RCBARON,
	RCRAIDER,
	GLENDALE,
	OCEANIC,
	SANCHEZ,
	SPARROW,
	PATRIOT,
	LOVEFIST,
	COASTG,
	DINGHY,
	HERMES,
	SABRE,
	SABRETUR,
	PHEONIX,
	WALTON,
	REGINA,
	COMET,
	DELUXO,
	BURRITO,
	SPAND,
	MARQUIS,
	BAGGAGE,
	KAUFMAN,
	MAVERICK,
	VCNMAV,
	RANCHER,
	FBIRANCH,
	VIRGO,
	GREENWOO,
	JETMAX,
	HOTRING,
	SANDKING,
	BLISTAC,
	POLMAV,
	BOXVILLE,
	BENSON,
	MESA,
	RCGOBLIN,
	HOTRINA,
	HOTRINB,
	BLOODRA,
	BLOODRB,
	VICECHEE,
	CAR237,
	CAR238,
	CAR239,
	MAX_CARS,

	// HACK so this compiles
	// TODO(MIAMI): check it out
	DODO = -1
};

enum
{
	OLD_DOOR = 0,
	NEW_DOOR,
	TRUCK_DOOR,
	BUS_DOOR,
};


struct tVehicleSampleData {
	eSfxSample m_nAccelerationSampleIndex;
	uint8 m_nBank;
	eSfxSample m_nHornSample;
	int32 m_nHornFrequency;
	uint8 m_nSirenOrAlarmSample;
	int32 m_nSirenOrAlarmFrequency;
	uint8 m_bDoorType;
};

const tVehicleSampleData aVehicleSettings[MAX_CARS] = {
	{SFX_CAR_REV_10, SFX_BANK_PATHFINDER, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9935, OLD_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 11487, SFX_CAR_HORN_JEEP, 9900, OLD_DOOR},
	{SFX_CAR_REV_2, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9890, NEW_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_HORN_JEEP, 9960, TRUCK_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 12893, SFX_CAR_HORN_JEEP, 9500, OLD_DOOR},
	{SFX_CAR_REV_4, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 10706, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_POLICE_SIREN_SLOW, 10588, TRUCK_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 31478, SFX_CAR_HORN_JEEP, 9800, TRUCK_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_BMW328, 9538, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_HORN_JEEP, 10000, OLD_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_BMW328, 12017, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_9, SFX_BANK_CADILLAC, SFX_CAR_HORN_JEEP, 22293, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18286, SFX_CAR_HORN_JEEP, 9600, OLD_DOOR},
	{SFX_CAR_REV_2, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 22295, SFX_AMBULANCE_SIREN_SLOW, 12688, OLD_DOOR},
	{SFX_CAR_REV_4, SFX_BANK_MERC, SFX_CAR_HORN_PORSCHE, 9271, SFX_POLICE_SIREN_SLOW, 11471, NEW_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 12170, SFX_CAR_HORN_JEEP, 9400, OLD_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_BMW328, 11000, SFX_CAR_HORN_JEEP, 9300, OLD_DOOR},
	{SFX_CAR_REV_10, SFX_BANK_PATHFINDER, SFX_CAR_HORN_BMW328, 10796, SFX_CAR_HORN_JEEP, 9200, NEW_DOOR},
	{SFX_CAR_REV_4, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 10500, SFX_CAR_HORN_JEEP, 9100, NEW_DOOR},
	{SFX_CAR_REV_10, SFX_BANK_PATHFINDER, SFX_CAR_HORN_PICKUP, 10924, SFX_CAR_HORN_JEEP, 9000, OLD_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 11025, SFX_ICE_CREAM_TUNE, 11025, OLD_DOOR},
	{SFX_CAR_REV_6, SFX_BANK_HOTROD, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9100, OLD_DOOR},
	{SFX_HELI_APACHE_1, SFX_BANK_HELI_APACHE, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9200, NEW_DOOR},
	{SFX_CAR_REV_4, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 10706, SFX_POLICE_SIREN_SLOW, 10511, NEW_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 17260, SFX_POLICE_SIREN_SLOW, 11029, OLD_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_HORN_JEEP, 9300, OLD_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10400, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_POLICE_SIREN_SLOW, 11912, NEW_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_BUS2, 11652, SFX_CAR_HORN_JEEP, 9500, BUS_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_HORN_JEEP, 9600, TRUCK_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 28043, SFX_CAR_HORN_JEEP, 9700, TRUCK_DOOR},
	{SFX_CAR_REV_6, SFX_BANK_HOTROD, SFX_CAR_HORN_JEEP, 25400, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_17, SFX_BANK_VTWIN, SFX_CAR_HORN_JEEP, 26313, SFX_CAR_HORN_JEEP, 10000, NEW_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_BUS, 16291, SFX_CAR_HORN_JEEP, 10100, BUS_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_HORN_JEEP, 9900, OLD_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10233, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_RC_REV, SFX_BANK_RC, SFX_CAR_HORN_PICKUP, 20000, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29000, SFX_CAR_HORN_JEEP, 9400, TRUCK_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_BMW328, 9003, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_4, SFX_BANK_MERC, SFX_CAR_HORN_PORSCHE, 12375, SFX_CAR_HORN_JEEP, 9200, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_BUS2, 15554, SFX_CAR_HORN_JEEP, 9100, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_BUS2, 13857, SFX_CAR_HORN_JEEP, 9000, TRUCK_DOOR},
	{SFX_MOPED_REV, SFX_BANK_MOPED, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 9100, NEW_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_JEEP, 22043, SFX_CAR_HORN_JEEP, 9200, OLD_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_5, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 28043, SFX_CAR_HORN_JEEP, 9800, TRUCK_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18286, SFX_CAR_HORN_JEEP, 9900, OLD_DOOR},
	{SFX_CAR_REV_12, SFX_BANK_GOLF_CART, SFX_CAR_HORN_JEEP, 28500, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_8, SFX_BANK_PONTIAC_SLOW, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_SEAPLANE_PRO1, SFX_BANK_PLANE_SEAPLANE, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_20, SFX_BANK_SPORTS_BIKE, SFX_CAR_HORN_JEEP, 27000, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_MOPED_REV, SFX_BANK_MOPED, SFX_CAR_HORN_JEEP, 31000, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_17, SFX_BANK_VTWIN, SFX_CAR_HORN_PICKUP, 11000, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_RC_REV, SFX_BANK_RC, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 15000, NEW_DOOR},
	{SFX_CAR_RC_HELI, SFX_BANK_RC_HELI, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 15000, NEW_DOOR},
	{SFX_CAR_REV_9, SFX_BANK_CADILLAC, SFX_CAR_HORN_56CHEV, 10300, SFX_CAR_HORN_JEEP, 9100, OLD_DOOR},
	{SFX_CAR_REV_9, SFX_BANK_CADILLAC, SFX_CAR_HORN_56CHEV, 10500, SFX_CAR_HORN_JEEP, 9000, OLD_DOOR},
	{SFX_CAR_REV_19, SFX_BANK_HONDA250, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 9000, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9100, TRUCK_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_TRUCK, 28000, SFX_CAR_HORN_JEEP, 9200, TRUCK_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_PICKUP, 11200, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_9, SFX_BANK_CADILLAC, SFX_CAR_HORN_56CHEV, 10700, SFX_CAR_HORN_JEEP, 9600, OLD_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_BMW328, 9000, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_6, SFX_BANK_HOTROD, SFX_CAR_HORN_BMW328, 9200, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_11, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10540, SFX_CAR_HORN_JEEP, 9935, TRUCK_DOOR},
	{SFX_CAR_REV_8, SFX_BANK_PONTIAC_SLOW, SFX_CAR_HORN_PICKUP, 11000, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_2, SFX_BANK_PORSCHE, SFX_CAR_HORN_BMW328, 9500, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_BMW328, 9700, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_8, SFX_BANK_PONTIAC_SLOW, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_HORN_JEEP, 9600, OLD_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18000, SFX_CAR_HORN_JEEP, 9500, TRUCK_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_8, SFX_BANK_PONTIAC_SLOW, SFX_CAR_HORN_JEEP, 27513, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_8, SFX_BANK_PONTIAC_SLOW, SFX_CAR_HORN_56CHEV, 10700, SFX_CAR_HORN_JEEP, 9200, OLD_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9100, TRUCK_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9000, TRUCK_DOOR},
	{SFX_CAR_REV_10, SFX_BANK_PATHFINDER, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_HORN_JEEP, 9100, TRUCK_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_BUS2, 17900, SFX_POLICE_SIREN_SLOW, 10511, TRUCK_DOOR},
	{SFX_CAR_REV_4, SFX_BANK_MERC, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9200, NEW_DOOR},
	{SFX_CAR_REV_8, SFX_BANK_PONTIAC_SLOW, SFX_CAR_HORN_BMW328, 9600, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_4, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10000, SFX_CAR_HORN_JEEP, 9500, OLD_DOOR},
	{SFX_CAR_REV_6, SFX_BANK_HOTROD, SFX_CAR_HORN_PORSCHE, 10500, SFX_CAR_HORN_JEEP, 9600, OLD_DOOR},
	{SFX_CAR_REV_10, SFX_BANK_PATHFINDER, SFX_CAR_HORN_JEEP, 25513, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_3, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_10, SFX_BANK_PATHFINDER, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_RC_HELI, SFX_BANK_RC_HELI, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_6, SFX_BANK_HOTROD, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_7, SFX_BANK_COBRA, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_9, SFX_BANK_CADILLAC, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_2, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_POLICE_SIREN_SLOW, 11000, NEW_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9200, NEW_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_1, CAR_SFX_BANKS_OFFSET, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR} };



bool8 bPlayerJustEnteredCar;

const bool8 hornPatternsArray[8][44] = {
    {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  FALSE, FALSE, FALSE, FALSE},
    {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,
     TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE},
    {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE,
     FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, FALSE},
    {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE,  TRUE,  FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE,
     TRUE,  TRUE,  TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE, FALSE},
    {FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    {FALSE, FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    {FALSE, FALSE, TRUE, TRUE, TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, TRUE,  TRUE,
     TRUE,  TRUE,  TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE, TRUE, TRUE, TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE,  TRUE,  FALSE, FALSE},
    {FALSE, FALSE, TRUE,  TRUE,  TRUE, TRUE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
     FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE},
};

void cAudioManager::ProcessVehicle(CVehicle* veh)
{
	CVehicle* playerVeh;
	cVehicleParams params;
	CBike* bike;
	CAutomobile* automobile;

	playerVeh = FindVehicleOfPlayer();
	if (playerVeh == veh
		|| CGame::currArea == AREA_OVALRING
		|| CGame::currArea == AREA_BLOOD
		|| CGame::currArea == AREA_DIRT
		|| CGame::currArea == AREA_EVERYWHERE
		|| CGame::currArea == AREA_MALL
		|| CGame::currArea == AREA_MAIN_MAP) {
		m_sQueueSample.m_vecPos = veh->GetPosition();
		params.m_bDistanceCalculated = FALSE;
		params.m_pVehicle = veh;
		params.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		params.m_pTransmission = veh->pHandling != nil ? &veh->pHandling->Transmission : nil;
		params.m_nIndex = veh->m_modelIndex - MI_FIRST_VEHICLE;
		if (veh->GetStatus() == STATUS_SIMPLE)
			params.m_fVelocityChange = veh->AutoPilot.m_fMaxTrafficSpeed * 0.02f;
		else
			params.m_fVelocityChange = DotProduct(veh->m_vecMoveSpeed, veh->GetForward());
		params.m_VehicleType = veh->m_vehType;
		
		if (CGame::currArea == AREA_MALL && playerVeh != veh) {
			ProcessVehicleOneShots(params);
			ProcessVehicleSirenOrAlarm(params);
			ProcessEngineDamage(params);
			return;
		}
		switch (params.m_VehicleType) {
		case VEHICLE_TYPE_CAR:
			automobile = (CAutomobile*)veh;
			UpdateGasPedalAudio(veh, params.m_VehicleType);
			if (veh->m_modelIndex == MI_RCBANDIT || veh->m_modelIndex == MI_RCBARON) {
				ProcessModelVehicle(params);
				ProcessEngineDamage(params);
			} else if (veh->m_modelIndex == MI_RCRAIDER || veh->m_modelIndex == MI_RCGOBLIN) {
				ProcessModelHeliVehicle(params);
				ProcessEngineDamage(params);
			} else {
				switch (veh->GetVehicleAppearance()) {
				case VEHICLE_APPEARANCE_HELI:
					ProcessCarHeli(params);
					ProcessVehicleFlatTyre(params);
					ProcessEngineDamage(params);
					break;
				case VEHICLE_APPEARANCE_BOAT:
				case VEHICLE_APPEARANCE_PLANE:
					break;
				default:
					if (ProcessVehicleRoadNoise(params)) {
						ProcessReverseGear(params);
						if (CWeather::WetRoads > 0.0f)
							ProcessWetRoadNoise(params);
						ProcessVehicleSkidding(params);
						ProcessVehicleFlatTyre(params);
						ProcessVehicleHorn(params);
						ProcessVehicleSirenOrAlarm(params);
						if (UsesReverseWarning(params.m_nIndex))
							ProcessVehicleReverseWarning(params);
						if(HasAirBrakes(params.m_nIndex))
							ProcessAirBrakes(params);
						ProcessCarBombTick(params);
						ProcessVehicleEngine(params);
						ProcessEngineDamage(params);
						ProcessVehicleDoors(params);
					}
					break;
				}
			}
			ProcessVehicleOneShots(params);
			automobile->m_fVelocityChangeForAudio = params.m_fVelocityChange;
			break;
		case VEHICLE_TYPE_BOAT:
			if (veh->m_modelIndex == MI_SKIMMER)
				ProcessCarHeli(params);
			else
				ProcessBoatEngine(params);
			ProcessBoatMovingOverWater(params);
			ProcessVehicleOneShots(params);
			break;
		case VEHICLE_TYPE_HELI: 
			ProcessCarHeli(params);
			ProcessVehicleOneShots(params);
			break;
		case VEHICLE_TYPE_PLANE:
			ProcessPlane(params);
			ProcessVehicleOneShots(params);
			ProcessVehicleFlatTyre(params);
			break;
		case VEHICLE_TYPE_BIKE:
			bike = (CBike*)veh;
			UpdateGasPedalAudio(veh, params.m_VehicleType);
			if (ProcessVehicleRoadNoise(params)) {
				if (CWeather::WetRoads > 0.0f)
					ProcessWetRoadNoise(params);
				ProcessVehicleSkidding(params);
				ProcessVehicleHorn(params);
				ProcessVehicleSirenOrAlarm(params);
				ProcessCarBombTick(params);
				ProcessEngineDamage(params);
				ProcessVehicleEngine(params);
				ProcessVehicleFlatTyre(params);
			}
			ProcessVehicleOneShots(params);
			bike->m_fVelocityChangeForAudio = params.m_fVelocityChange;
			break;
		default:
			break;
		}
		ProcessRainOnVehicle(params);
	}
}

void
cAudioManager::ProcessRainOnVehicle(cVehicleParams& params)
{
	const int SOUND_INTENSITY = 22.0f;

	CVehicle *veh;
	uint8 emittingVol;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY) || CWeather::Rain <= 0.01f || CCullZones::CamNoRain() && CCullZones::PlayerNoRain())
		return;

	veh = params.m_pVehicle;
	veh->m_bRainAudioCounter++;
	if (veh->m_bRainAudioCounter >= 2) {
		veh->m_bRainAudioCounter = 0;
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		emittingVol = 30.0f * CWeather::Rain;
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = veh->m_bRainSamplesCounter++;
			if (veh->m_bRainSamplesCounter > 4)
				veh->m_bRainSamplesCounter = 68;
			m_sQueueSample.m_nSampleIndex = (m_anRandomTable[1] & 3) + SFX_CAR_RAIN_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 9;
			m_sQueueSample.m_nFrequency = m_anRandomTable[1] % 4000 + 28000;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bReverbFlag = FALSE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
}

bool8
cAudioManager::ProcessReverseGear(cVehicleParams& params)
{
	const int reverseGearIntensity = 30;

	CAutomobile* automobile;
	float modificator;
	uint8 emittingVolume;

	if (params.m_fDistance >= SQR(reverseGearIntensity))
		return FALSE;
	automobile = (CAutomobile*)params.m_pVehicle;
	if (automobile->m_modelIndex == MI_CADDY)
		return TRUE;
	if (automobile->bEngineOn && (automobile->m_fGasPedal < 0.0f || automobile->m_nCurrentGear == 0)) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		if (automobile->m_nDriveWheelsOnGround != 0) {
			modificator = params.m_fVelocityChange / params.m_pTransmission->fMaxReverseVelocity;
		} else {
			if (automobile->m_nDriveWheelsOnGroundPrev != 0)
				automobile->m_fGasPedalAudio *= 0.4f;
			modificator = automobile->m_fGasPedalAudio;
		}
		modificator = Abs(modificator);
		emittingVolume = modificator * 24.0f;
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVolume, reverseGearIntensity, m_sQueueSample.m_fDistance);

		if (m_sQueueSample.m_nVolume != 0) {
			if (params.m_pVehicle->m_fGasPedal >= 0.0f) {
				m_sQueueSample.m_nCounter = 62;
				m_sQueueSample.m_nSampleIndex = SFX_REVERSE_GEAR_2;
			} else {
				m_sQueueSample.m_nCounter = 61;
				m_sQueueSample.m_nSampleIndex = SFX_REVERSE_GEAR;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_nFrequency = (6000.0f * modificator) + 7000;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVolume;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = reverseGearIntensity;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
	return TRUE;
}

void
cAudioManager::ProcessModelVehicle(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 35.0f;

	static uint32 prevFreq = 14000;
	static uint8 prevVolume = 0;

	uint32 freq;
	int16 acceletateState;
	int16 brakeState;
	uint8 volume;
	bool8 isPlayerVeh;
	bool8 vehSlowdown;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return;

	if (FindPlayerVehicle() == params.m_pVehicle)
		isPlayerVeh = TRUE;
	else
#ifdef FIX_BUGS
		isPlayerVeh = CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle == params.m_pVehicle;
#else
		isPlayerVeh = CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle != nil;
#endif
	if (params.m_pVehicle->m_modelIndex == MI_RCBANDIT) {
		if (((CAutomobile*)params.m_pVehicle)->m_nDriveWheelsOnGround != 0) {
			volume = Min(127, 127.0f * Abs(params.m_fVelocityChange) * 3.0f);
			freq = 8000.0f * Abs(params.m_fVelocityChange) + 14000;
		} else {
			volume = 127;
			freq = 25000;
		}
		if (isPlayerVeh) {
			volume = Clamp2(volume, prevVolume, 7);
			freq = Clamp2(freq, prevFreq, 800);
		}
		if (volume > 0) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(volume, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nCounter = 2;
				m_sQueueSample.m_nSampleIndex = SFX_RC_REV;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 1;
				m_sQueueSample.m_nFrequency = freq;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = volume;
				SET_LOOP_OFFSETS(SFX_RC_REV)
				m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 4;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
		if (isPlayerVeh) {
			prevFreq = freq;
			prevVolume = volume;
		}
	} else if (params.m_pVehicle != nil) {
		if (isPlayerVeh) {
			acceletateState = Pads[0].GetAccelerate();
			brakeState = Pads[0].GetBrake();
		} else {
			acceletateState = 255.0f * params.m_pVehicle->m_fGasPedal;
			brakeState = 255.0f * params.m_pVehicle->m_fBrakePedal;
		}
		if (acceletateState < brakeState)
			acceletateState = brakeState;
		if (acceletateState <= 0) {
			vehSlowdown = TRUE;
			volume = 127;
			freq = 18000;
		} else {
			vehSlowdown = FALSE;
			volume = Min(127, (127 * acceletateState / 255) * 3.0f * Abs(params.m_fVelocityChange));
			freq = Min(22000, (8000 * acceletateState / 255 + 14000) * 3.0f * Abs(params.m_fVelocityChange));
		}
		if (isPlayerVeh && !vehSlowdown) {
			volume = Clamp2(volume, prevVolume, 7);
			freq = Clamp2(freq, prevFreq, 800);
		}
		if (!vehSlowdown)
#ifdef THIS_IS_STUPID
			freq += 8000.0f * Abs(DotProduct(params.m_pVehicle->GetUp(), CVector(0.0f, 1.0f, 0.0f)));
#else
			freq += 8000.0f * Abs(params.m_pVehicle->GetUp().y);
#endif
		if (params.m_pVehicle->bIsDrowning)
			volume /= 4;
		if (volume > 0) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(volume, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				if (vehSlowdown) {
					m_sQueueSample.m_nCounter = 0;
					m_sQueueSample.m_nSampleIndex = SFX_RC_IDLE;
					m_sQueueSample.m_nReleasingVolumeDivider = 6;
				} else {
					m_sQueueSample.m_nCounter = 2;
					m_sQueueSample.m_nSampleIndex = SFX_RC_REV;
					m_sQueueSample.m_nReleasingVolumeDivider = 4;
				}
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_nFrequency = freq;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = volume;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
		if (isPlayerVeh) {
			if (vehSlowdown) {
				prevFreq = freq;
				prevVolume = volume;
			}
		}
	}
}

void
cAudioManager::ProcessModelHeliVehicle(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 35.0f;

	static uint32 prevFreq = 22050;

	uint32 freq;
	bool8 isPlayerVeh;
	int16 acceletateState;
	int16 brakeState;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return;

	if (FindPlayerVehicle() == params.m_pVehicle)
		isPlayerVeh = TRUE;
	else
#ifdef FIX_BUGS
		isPlayerVeh = CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle == params.m_pVehicle;
#else
		isPlayerVeh = CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle != nil;
#endif
	if (isPlayerVeh) {
		brakeState = Pads[0].GetBrake();
		acceletateState = Max(Pads[0].GetAccelerate(), Abs(Pads[0].GetCarGunUpDown()) * 2);
	} else {
		acceletateState = 255.0f * params.m_pVehicle->m_fGasPedal;
		brakeState = 255.0f * params.m_pVehicle->m_fBrakePedal;
	}
	if (acceletateState < brakeState)
		acceletateState = brakeState;
	freq = Clamp2(5 * acceletateState + 22050, prevFreq, 30);
	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
	m_sQueueSample.m_nVolume = ComputeVolume(70, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 2;
		m_sQueueSample.m_nSampleIndex = SFX_CAR_RC_HELI;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nFrequency = freq;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = 70;
		SET_LOOP_OFFSETS(SFX_CAR_RC_HELI)
		m_sQueueSample.m_fSpeedMultiplier = 3.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 4;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
	if (isPlayerVeh)
		prevFreq = freq;
}

bool8
cAudioManager::ProcessVehicleRoadNoise(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 95.0f;

	int32 emittingVol;
	uint32 freq;
	float multiplier;
	int sampleFreq;
	float velocity;
	uint8 wheelsOnGround;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;
	switch (params.m_VehicleType) {
	case VEHICLE_TYPE_CAR:
		wheelsOnGround = ((CAutomobile*)params.m_pVehicle)->m_nWheelsOnGround;
		break;
	case VEHICLE_TYPE_BIKE:
		wheelsOnGround = ((CBike*)params.m_pVehicle)->m_nWheelsOnGround;
		break;
	default:
		wheelsOnGround = 4;
		break;
	}
	if (params.m_pTransmission == nil || wheelsOnGround == 0)
		return TRUE;

	velocity = Abs(params.m_fVelocityChange);
	if (velocity > 0.0f) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		emittingVol = 30.f * Min(1.f, velocity / (0.5f * params.m_pTransmission->fMaxVelocity));
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			if (params.m_pVehicle->m_nSurfaceTouched == SURFACE_WATER) {
				m_sQueueSample.m_nSampleIndex = SFX_BOAT_WATER_LOOP;
				freq = 6050 * emittingVol / 30 + 16000;
			} else {
				m_sQueueSample.m_nSampleIndex = SFX_ROAD_NOISE;
				multiplier = (m_sQueueSample.m_fDistance / SOUND_INTENSITY) * 0.5f;
				sampleFreq = SampleManager.GetSampleBaseFrequency(SFX_ROAD_NOISE);
				freq = (sampleFreq * multiplier) + ((3 * sampleFreq) / 4);
			}
			m_sQueueSample.m_nFrequency = freq;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 6.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 4;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}

	return TRUE;
}

bool8
cAudioManager::ProcessWetRoadNoise(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 30.0f;

	float relativeVelocity;
	int32 emittingVol;
	float multiplier;
	int freq;
	float velocity;
	uint8 wheelsOnGround;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;
	switch (params.m_VehicleType) {
	case VEHICLE_TYPE_CAR:
		wheelsOnGround = ((CAutomobile*)params.m_pVehicle)->m_nWheelsOnGround;
		break;
	case VEHICLE_TYPE_BIKE:
		wheelsOnGround = ((CBike*)params.m_pVehicle)->m_nWheelsOnGround;
		break;
	default:
		wheelsOnGround = 4;
		break;
	}
	if (params.m_pTransmission == nil || wheelsOnGround == 0)
		return TRUE;

	velocity = Abs(params.m_fVelocityChange);
	if (velocity > 0.0f) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		relativeVelocity = Min(1.0f, velocity / (0.5f * params.m_pTransmission->fMaxVelocity));
		emittingVol = 23.0f * relativeVelocity * CWeather::WetRoads;
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 1;
			m_sQueueSample.m_nSampleIndex = SFX_ROAD_NOISE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			multiplier = (m_sQueueSample.m_fDistance / SOUND_INTENSITY) * 0.5f;
			freq = SampleManager.GetSampleBaseFrequency(SFX_ROAD_NOISE);
			m_sQueueSample.m_nFrequency = freq + freq * multiplier;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 6.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 4;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}

	return TRUE;
}

void
cAudioManager::ProcessVehicleEngine(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 50.0f;

	CVehicle* playerVeh;
	CVehicle* veh;
	CAutomobile* automobile;
	cTransmission* transmission;
	CBike* bike;
	tWheelState* wheelState;
	float* gasPedalAudioPtr;

	int32 freq = 0;
	uint8 currentGear;
	uint8 emittingVol;
	int8 wheelsOnGround;
	int8 wheelsOnGroundPrev;
	float relativeGearChange;
	float relativeChange;
	float modificator;
	float traction;
	bool8 isMoped;
	bool8 caddyBool;

	isMoped = FALSE;
	caddyBool = FALSE;
	traction = 0.0f;
	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return;
	playerVeh = FindPlayerVehicle();
	veh = params.m_pVehicle;
	if (playerVeh == veh && veh->GetStatus() == STATUS_WRECKED) {
		SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
		return;
	}
	if (!veh->bEngineOn)
		return;
	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
	if (playerVeh == veh && veh->m_modelIndex != MI_CADDY) {
		ProcessPlayersVehicleEngine(params, params.m_pVehicle);
		return;
	}
	transmission = params.m_pTransmission;
	if (transmission != nil) {
		switch (veh->m_modelIndex) {
		case MI_PIZZABOY:
		case MI_FAGGIO:
			isMoped = TRUE;
			currentGear = transmission->nNumberOfGears;
			break;
		case MI_CADDY:
			currentGear = transmission->nNumberOfGears;
			caddyBool = TRUE;
			break;
		default:
			currentGear = veh->m_nCurrentGear;
			break;
		}
		switch (params.m_VehicleType) {
		case VEHICLE_TYPE_CAR:
			automobile = (CAutomobile*)veh;
			wheelsOnGround = automobile->m_nDriveWheelsOnGround;
			wheelsOnGroundPrev = automobile->m_nDriveWheelsOnGroundPrev;
			wheelState = automobile->m_aWheelState;
			gasPedalAudioPtr = &automobile->m_fGasPedalAudio;
			break;
		case VEHICLE_TYPE_BIKE:
			bike = (CBike*)veh;
			wheelsOnGround = bike->m_nDriveWheelsOnGround;
			wheelsOnGroundPrev = bike->m_nDriveWheelsOnGroundPrev;
			wheelState = bike->m_aWheelState;
			gasPedalAudioPtr = &bike->m_fGasPedalAudio;
			break;
		default:
			debug(" ** AUDIOLOG: Unrecognised vehicle type %d in ProcessVehicleEngine() * \n", params.m_VehicleType);
			return;
		}

		if (wheelsOnGround != 0) {
			if (!veh->bIsHandbrakeOn || isMoped && caddyBool) { //mb bug, bcs it's can't be TRUE together
				if (veh->GetStatus() == STATUS_SIMPLE || isMoped || caddyBool) {
					traction = 0.0f;
				} else {
					switch (transmission->nDriveType) {
					case '4':
						if (params.m_VehicleType == VEHICLE_TYPE_BIKE) {
							for (int i = 0; i < 2; i++)
								if (wheelState[i] == WHEEL_STATE_SPINNING)
									traction += 0.1f;
						} else {
							for (int i = 0; i < 4; i++)
								if (wheelState[i] == WHEEL_STATE_SPINNING)
									traction += 0.05f;
						}
						break;
					case 'F':
						if (params.m_VehicleType == VEHICLE_TYPE_BIKE) {
							if (wheelState[BIKEWHEEL_FRONT] == WHEEL_STATE_SPINNING)
								traction += 0.2f;
						} else {
							if (wheelState[CARWHEEL_FRONT_LEFT] == WHEEL_STATE_SPINNING)
								traction += 0.1f;
							if (wheelState[CARWHEEL_FRONT_RIGHT] == WHEEL_STATE_SPINNING)
								traction += 0.1f;
						}
						break;
					case 'R':
						if (params.m_VehicleType == VEHICLE_TYPE_BIKE) {
							if (wheelState[BIKEWHEEL_REAR] == WHEEL_STATE_SPINNING)
								traction += 0.2f;
						} else {
							if (wheelState[CARWHEEL_REAR_LEFT] == WHEEL_STATE_SPINNING)
								traction += 0.1f;
							if (wheelState[CARWHEEL_REAR_RIGHT] == WHEEL_STATE_SPINNING)
								traction += 0.1f;
						}
						break;
					default:
						break;
					}
				}
			} else if (params.m_fVelocityChange == 0.0f) {
				traction = 0.9f;
			}
			if (transmission->fMaxVelocity <= 0.0f) {
				relativeChange = 0.0f;
				modificator = 0.0f;
			} else {
				if (!isMoped && !caddyBool) {
					if (currentGear != 0) {
						relativeGearChange = Min(1.0f,
							params.m_fVelocityChange - transmission->Gears[currentGear].fShiftDownVelocity) / transmission->fMaxVelocity * 2.5f;
						if (traction == 0.0f && veh->GetStatus() != STATUS_SIMPLE && 
							params.m_fVelocityChange < transmission->Gears[1].fShiftUpVelocity)
							traction = 0.7f;
						relativeChange = traction * *gasPedalAudioPtr * 0.95f + (1.0f - traction) * relativeGearChange;
					} else {
						relativeChange = Min(1.0f,
							1.0f - Abs((params.m_fVelocityChange - transmission->Gears[0].fShiftDownVelocity) / transmission->fMaxReverseVelocity));
					}
					modificator = relativeChange;
				} else {
					modificator = Min(1.0f, Abs(params.m_fVelocityChange / transmission->fMaxVelocity > 1.0f));
				}
			}
		} else {
			if (wheelsOnGroundPrev != 0)
				*gasPedalAudioPtr *= 0.4f;
			relativeChange = *gasPedalAudioPtr;
			modificator = relativeChange;
		}
		if (currentGear != 0 || wheelsOnGround == 0)
			freq = 1200 * currentGear + 18000.0f * modificator + 14000;
		else if (params.m_VehicleType == VEHICLE_TYPE_BIKE)
			freq = 22050;
		else
			freq = 13000.0f * modificator + 14000;
		if (modificator >= 0.75f)
			emittingVol = 90;
		else
			emittingVol = modificator * (4.0f / 3.0f) * 15.0f + 75;
	} else {
		modificator = 0.0f;
		emittingVol = 75;
	}
	if (veh->bIsDrowning)
		emittingVol /= 4;
	if (caddyBool) {
		emittingVol = 100.0f * modificator;
		freq = 2130.0f * modificator + 4270;
		m_sQueueSample.m_nCounter = 2;
	}
	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		if (!caddyBool) {
			if (veh->GetStatus() == STATUS_SIMPLE) {
				if (modificator < 0.02f) {
					m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nBank - CAR_SFX_BANKS_OFFSET + SFX_CAR_IDLE_1;
					m_sQueueSample.m_nCounter = 52;
					freq = 10000.0f * modificator + 22050;
				} else {
					m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nAccelerationSampleIndex;
					m_sQueueSample.m_nCounter = 2;
				}
			} else {
				if (veh->m_fGasPedal < 0.02f) {
					m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nBank - CAR_SFX_BANKS_OFFSET + SFX_CAR_IDLE_1;
					m_sQueueSample.m_nCounter = 52;
					freq = 10000.0f * modificator + 22050;
				} else {
					m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nAccelerationSampleIndex;
					m_sQueueSample.m_nCounter = 2;
				}
			}
			m_sQueueSample.m_nFrequency = freq + 100 * m_sQueueSample.m_nBankIndex % 1000;
		} else {
			if (FindVehicleOfPlayer() == params.m_pVehicle)
				m_sQueueSample.m_nSampleIndex = SFX_CAR_AFTER_ACCEL_12;
			else
				m_sQueueSample.m_nSampleIndex = SFX_CAR_REV_12;
			m_sQueueSample.m_nFrequency = freq + 20 * m_sQueueSample.m_nBankIndex % 100;
		}
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		if (m_sQueueSample.m_nSampleIndex == SFX_CAR_IDLE_5 || m_sQueueSample.m_nSampleIndex == SFX_CAR_REV_5)
			m_sQueueSample.m_nFrequency /= 2;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = emittingVol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 6.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 8;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
}

void
cAudioManager::UpdateGasPedalAudio(CVehicle* veh, int vehType)
{
	float gasPedal = Abs(veh->m_fGasPedal);
	float* gasPealAudioPtr;

	switch(vehType) {
	case VEHICLE_TYPE_CAR: gasPealAudioPtr = &((CAutomobile *)veh)->m_fGasPedalAudio; break;
	case VEHICLE_TYPE_BIKE: gasPealAudioPtr = &((CBike *)veh)->m_fGasPedalAudio; break;
	default: return;
	}
	if (*gasPealAudioPtr < gasPedal)
		*gasPealAudioPtr = Min(*gasPealAudioPtr + 0.09f, gasPedal);
	else
		*gasPealAudioPtr = Max(*gasPealAudioPtr - 0.07f, gasPedal);
}

void
cAudioManager::PlayerJustGotInCar() const
{
	if (m_bIsInitialised)
		bPlayerJustEnteredCar = TRUE;
}

void
cAudioManager::PlayerJustLeftCar(void) const
{
	// UNUSED: This is a perfectly empty function.
}

void
cAudioManager::AddPlayerCarSample(uint8 emittingVolume, int32 freq, uint32 sample, uint8 bank, uint8 counter, bool8 notLooping)
{
	m_sQueueSample.m_nVolume = ComputeVolume(emittingVolume, 50.f, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = counter;
		m_sQueueSample.m_nSampleIndex = sample;
#ifdef GTA_PS2
		m_sQueueSample.m_nBankIndex = bank;
#else
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#endif // GTA_PS2
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 0;
		m_sQueueSample.m_nFrequency = freq;
		if (notLooping) {
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nReleasingVolumeDivider = 8;
		} else {
			m_sQueueSample.m_nLoopCount = 1;
		}
		m_sQueueSample.m_nEmittingVolume = emittingVolume;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 6.0f;
		m_sQueueSample.m_fSoundIntensity = 50.0f;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
}

void
cAudioManager::ProcessCesna(cVehicleParams &params)
{
	if(params.m_fDistance < SQR(200)) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		m_sQueueSample.m_nVolume = ComputeVolume(80, 200.f, m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 52;
			m_sQueueSample.m_nSampleIndex = SFX_CESNA_IDLE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 0;
			m_sQueueSample.m_nFrequency = 12500;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nReleasingVolumeDivider = 8;
			m_sQueueSample.m_nEmittingVolume = 80;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_fSoundIntensity = 200.0f;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
		if(params.m_fDistance < SQR(90)) {
			m_sQueueSample.m_nVolume = ComputeVolume(80, 90.f, m_sQueueSample.m_fDistance);
			if(m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nCounter = 2;
				m_sQueueSample.m_nSampleIndex = SFX_CESNA_REV;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_nFrequency = 25000;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nReleasingVolumeDivider = 4;
				m_sQueueSample.m_nEmittingVolume = 80;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 4.0f;
				m_sQueueSample.m_fSoundIntensity = 90.0f;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
	}
}

void
cAudioManager::ProcessPlayersVehicleEngine(cVehicleParams& params, CVehicle* veh)
{
	static int32 GearFreqAdj[] = { 6000, 6000, 3400, 1200, 0, -1000 };

	tWheelState* wheelState;
	CAutomobile* automobile;
	CBike* bike;
	CVector pos;
	float* gasPedalAudioPtr;

	int32 accelerateState;
	int32 brakeState;
	int32 freq;
	int32 baseFreq;
	int32 freqModifier;
	uint32 gearSoundLength;
	uint32 soundOffset;
	uint8 engineSoundType;
	uint8 wheelInUseCounter;
	uint8 wheelsOnGround;
	uint8 vol;
	uint8 currentGear;
	uint8 wheelsOnGroundPrev;

	float accelerationMultipler;
	float gasPedalAudio;
	float velocityChangeForAudio;
	float relativeVelocityChange;
	float time;
	bool8 channelUsed;
	bool8 lostTraction;
	bool8 noGearBox;
	bool8 stuckInSand;
	bool8 processedAccelSampleStopped;
	bool8 isMoped;

	static uint32 gearSoundStartTime = CTimer::GetTimeInMilliseconds();
	static int32 nCruising = 0;
	static int16 LastAccel = 0;
	static uint8 CurrentPretendGear = 1;
	static bool8 bLostTractionLastFrame = FALSE;
	static bool8 bHandbrakeOnLastFrame = FALSE;
	static bool8 bAccelSampleStopped = TRUE;

	lostTraction = FALSE;
	isMoped = params.m_pVehicle->m_modelIndex == MI_PIZZABOY || params.m_pVehicle->m_modelIndex == MI_FAGGIO;
	processedAccelSampleStopped = FALSE;
	if (bPlayerJustEnteredCar) {
		bAccelSampleStopped = TRUE;
		bPlayerJustEnteredCar = FALSE;
		nCruising = 0;
		LastAccel = 0;
		bLostTractionLastFrame = FALSE;
		CurrentPretendGear = 1;
		bHandbrakeOnLastFrame = FALSE;
	}
	if (CReplay::IsPlayingBack()) {
		accelerateState = (255.0f * Clamp(params.m_pVehicle->m_fGasPedal, 0.0f, 1.0f));
		brakeState = (255.0f * Clamp(params.m_pVehicle->m_fBrakePedal, 0.0f, 1.0f));
	} else {
		accelerateState = Pads[0].GetAccelerate();
		brakeState = Pads[0].GetBrake();
	}
	channelUsed = SampleManager.GetChannelUsedFlag(CHANNEL_PLAYER_VEHICLE_ENGINE);
	if (isMoped) {
		CurrentPretendGear = params.m_pTransmission->nNumberOfGears;
		currentGear = CurrentPretendGear;
		if (params.m_pVehicle->bIsHandbrakeOn) {
			brakeState = 0;
			nCruising = 0;
			LastAccel = 0;
			accelerateState = 0;
		} else {
			nCruising = 1;
		}
	} else {
		currentGear = params.m_pVehicle->m_nCurrentGear;
	}

	switch (params.m_VehicleType) {
	case VEHICLE_TYPE_CAR:
		automobile = (CAutomobile*)params.m_pVehicle;
		wheelsOnGround = automobile->m_nDriveWheelsOnGround;
		wheelsOnGroundPrev = automobile->m_nDriveWheelsOnGroundPrev;
		gasPedalAudioPtr = &automobile->m_fGasPedalAudio;
		wheelState = automobile->m_aWheelState;
		velocityChangeForAudio = automobile->m_fVelocityChangeForAudio;
		break;
	case VEHICLE_TYPE_BIKE:
		bike = (CBike*)params.m_pVehicle;
		wheelsOnGround = bike->m_nDriveWheelsOnGround;
		wheelsOnGroundPrev = bike->m_nDriveWheelsOnGroundPrev;
		gasPedalAudioPtr = &bike->m_fGasPedalAudio;
		wheelState = bike->m_aWheelState;
		velocityChangeForAudio = bike->m_fVelocityChangeForAudio;
		break;
	default:
		debug(" ** AUDIOLOG: Unrecognised vehicle type %d in ProcessVehicleEngine() * \n", params.m_VehicleType);
		return;
	}
	if (!isMoped) {
		switch (params.m_pTransmission->nDriveType) {
		case '4':
			if (params.m_VehicleType != VEHICLE_TYPE_BIKE) {
				wheelInUseCounter = 0;
				for (uint8 i = 0; i < 4; i++) {
					if (wheelState[i] != WHEEL_STATE_NORMAL)
						++wheelInUseCounter;
				}
				if (wheelInUseCounter > 2)
					lostTraction = TRUE;
			}
			break;
		case 'F':
			if (params.m_VehicleType == VEHICLE_TYPE_BIKE) {
				if (wheelState[BIKEWHEEL_FRONT] != WHEEL_STATE_NORMAL)
					lostTraction = TRUE;
			} else {
				if ((wheelState[CARWHEEL_FRONT_LEFT] != WHEEL_STATE_NORMAL || wheelState[CARWHEEL_FRONT_RIGHT] != WHEEL_STATE_NORMAL) &&
					(wheelState[CARWHEEL_REAR_LEFT] != WHEEL_STATE_NORMAL || wheelState[CARWHEEL_REAR_RIGHT] != WHEEL_STATE_NORMAL))
					lostTraction = TRUE;
			}
			break;
		case 'R':
			if (params.m_VehicleType == VEHICLE_TYPE_BIKE) {
				if (wheelState[BIKEWHEEL_REAR] != WHEEL_STATE_NORMAL)
					lostTraction = TRUE;
			} else {
				if (wheelState[CARWHEEL_REAR_LEFT] != WHEEL_STATE_NORMAL || wheelState[CARWHEEL_REAR_RIGHT] != WHEEL_STATE_NORMAL)
					lostTraction = TRUE;
			}
			break;
		default:
			break;
		}
	}
	if (params.m_fVelocityChange != 0.0f) {
		time = params.m_pVehicle->m_vecMoveSpeed.z / params.m_fVelocityChange;
		if (time > 0.0f)
			freqModifier = -(Min(0.2f, time) * 3000.0f * 5.0f);
		else
			freqModifier = -(Max(-0.2f, time) * 3000.0f * 5.0f);
		if (params.m_fVelocityChange < -0.001f)
			freqModifier = -freqModifier;
	} else
		freqModifier = 0;
	if (params.m_VehicleType == VEHICLE_TYPE_BIKE && bike->bExtraSpeed)
		freqModifier += 1400;
	gearSoundLength = 0;
	engineSoundType = aVehicleSettings[params.m_nIndex].m_nBank;
	soundOffset = 3 * (engineSoundType - CAR_SFX_BANKS_OFFSET);
	noGearBox = FALSE;
	switch (engineSoundType) {
	case SFX_BANK_PONTIAC:
		gearSoundLength = 2526;
		break;
	case SFX_BANK_PORSCHE:
		gearSoundLength = 3587;
		break;
	case SFX_BANK_SPIDER:
		gearSoundLength = 4898;
		break;
	case SFX_BANK_MERC:
		gearSoundLength = 4003;
		break;
	case SFX_BANK_TRUCK:
		gearSoundLength = 6289;
		break;
	case SFX_BANK_HOTROD:
		gearSoundLength = 2766;
		break;
	case SFX_BANK_COBRA:
		gearSoundLength = 3523;
		break;
	case SFX_BANK_PONTIAC_SLOW:
		gearSoundLength = 2773;
		break;
	case SFX_BANK_CADILLAC:
		gearSoundLength = 2560;
		break;
	case SFX_BANK_PATHFINDER:
		gearSoundLength = 4228;
		break;
	case SFX_BANK_PACARD:
		gearSoundLength = 4648;
		break;
	case SFX_BANK_VTWIN:
		gearSoundLength = 3480;
		break;
	case SFX_BANK_HONDA250:
		gearSoundLength = 2380;
		break;
	case SFX_BANK_SPORTS_BIKE:
		gearSoundLength = 2410;
		break;
	default:
		noGearBox = TRUE;
		break;
	}
	if (!channelUsed || nCruising || noGearBox) {
		gearSoundStartTime = CTimer::GetTimeInMilliseconds();
	} else {
		gearSoundLength -= 1000;
		if (CTimer::GetTimeInMilliseconds() - gearSoundStartTime > gearSoundLength) {
			channelUsed = FALSE;
			gearSoundStartTime = CTimer::GetTimeInMilliseconds();
		}
	}
	relativeVelocityChange = 2.0f * params.m_fVelocityChange / params.m_pTransmission->fMaxVelocity;
	accelerationMultipler = Clamp(relativeVelocityChange, 0.0f, 1.0f);
	gasPedalAudio = accelerationMultipler;
	switch (engineSoundType) {
	case SFX_BANK_MOPED:
		++soundOffset;
		break;
	case SFX_BANK_HONDA250:
		soundOffset += 2;
		break;
	case SFX_BANK_SPORTS_BIKE:
		soundOffset += 3;
		break;
	default:
		break;
	}
	if (accelerateState <= 0) {
		if (params.m_fVelocityChange < -0.001f) {
			if (channelUsed) {
				SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
				bAccelSampleStopped = TRUE;
			}
			if (wheelsOnGround == 0 || params.m_pVehicle->bIsHandbrakeOn || lostTraction)
				gasPedalAudio = *gasPedalAudioPtr;
			else if (params.m_VehicleType == VEHICLE_TYPE_BIKE)
				gasPedalAudio = 0.0f;
			else
				gasPedalAudio = Min(1.0f, params.m_fVelocityChange / params.m_pTransmission->fMaxReverseVelocity);
			*gasPedalAudioPtr = Max(0.0f, gasPedalAudio);
		} else if (LastAccel > 0) {
			if (channelUsed) {
				SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
				bAccelSampleStopped = TRUE;
			}
			nCruising = 0;
			if (wheelsOnGround == 0
				|| params.m_pVehicle->bIsHandbrakeOn
				|| lostTraction
				|| params.m_fVelocityChange < 0.01f && *gasPedalAudioPtr > 0.2f) {
				if (isMoped) {
					gasPedalAudio = 0.0f;
				} else {
					*gasPedalAudioPtr *= 0.6f;
					gasPedalAudio = *gasPedalAudioPtr;
				}
			}
			if (gasPedalAudio > 0.05f) {
				freq = (5000.f * (gasPedalAudio - 0.05f) * 20.f / 19) + 19000;
				vol = (25.0f * (gasPedalAudio - 0.05f) * 20.f / 19) + 40;
				if (params.m_pVehicle->bIsDrowning)
					vol /= 4;
				if (engineSoundType == SFX_BANK_TRUCK)
					freq /= 2;
				AddPlayerCarSample(vol, freq, soundOffset + SFX_CAR_FINGER_OFF_ACCEL_1, engineSoundType, 63, FALSE);
			}
		}
		freq = (10000.f * gasPedalAudio) + 22050;
		vol = 110 - (40.0f * gasPedalAudio);
		if (engineSoundType == SFX_BANK_TRUCK)
			freq /= 2;
		if (params.m_pVehicle->bIsDrowning)
			vol /= 4;
		AddPlayerCarSample(vol, freq, engineSoundType - CAR_SFX_BANKS_OFFSET + SFX_CAR_IDLE_1, SFX_BANK_0, 52, TRUE);

		CurrentPretendGear = Max(1, currentGear);
	}
	else {
		if (nCruising == 0){
			stuckInSand = params.m_VehicleType == VEHICLE_TYPE_CAR && ((CAutomobile*)params.m_pVehicle)->bStuckInSand;
			if (accelerateState < 150 || wheelsOnGround == 0 || params.m_pVehicle->bIsHandbrakeOn || lostTraction
				|| (currentGear < 2 && params.m_fVelocityChange - velocityChangeForAudio < 0.01f) || brakeState > 0) {

				if (((wheelsOnGround && !params.m_pVehicle->bIsHandbrakeOn && !lostTraction ) || stuckInSand) && brakeState <= 0) {
					baseFreq = (8000.0f * accelerationMultipler) + 16000;
					vol = (25.0f * accelerationMultipler) + 60;
					*gasPedalAudioPtr = accelerationMultipler;
				} else {
					if (wheelsOnGround == 0 && wheelsOnGroundPrev != 0 || (params.m_pVehicle->bIsHandbrakeOn && !bHandbrakeOnLastFrame || lostTraction && !bLostTractionLastFrame)
						&& wheelsOnGround != 0) {
						*gasPedalAudioPtr *= 0.6f;
					}
					freqModifier = 0;
					if (engineSoundType != SFX_BANK_GOLF_CART && engineSoundType != SFX_BANK_CAR_CHAINSAW)
						baseFreq = (25000.0f * *gasPedalAudioPtr) + 14000;
					else
						baseFreq = (15000.0f * *gasPedalAudioPtr) + 14000;
					vol = (25.0f * *gasPedalAudioPtr) + 60;
				}
				freq = freqModifier + baseFreq;
				if (engineSoundType == SFX_BANK_TRUCK)
					freq /= 2;
				if (channelUsed) {
					SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
					bAccelSampleStopped = TRUE;
				}
				if (params.m_pVehicle->bIsDrowning)
					vol /= 4;
				AddPlayerCarSample(vol, freq, engineSoundType - CAR_SFX_BANKS_OFFSET + SFX_CAR_REV_1, SFX_BANK_0, 2, TRUE);
			} else {
				TranslateEntity(&m_sQueueSample.m_vecPos, &pos);
				if (bAccelSampleStopped) {
					if (CurrentPretendGear != 1 || currentGear != 2)
						CurrentPretendGear = Max(1, currentGear - 1);
					processedAccelSampleStopped = TRUE;
					bAccelSampleStopped = FALSE;
				}
				if (channelUsed) {
					SampleManager.SetChannelEmittingVolume(CHANNEL_PLAYER_VEHICLE_ENGINE, 120);
					SampleManager.SetChannel3DPosition(CHANNEL_PLAYER_VEHICLE_ENGINE, pos.x, pos.y, pos.z);
					SampleManager.SetChannel3DDistances(CHANNEL_PLAYER_VEHICLE_ENGINE, 50.0f, 12.5f);
					freq = (GearFreqAdj[CurrentPretendGear] + freqModifier + 22050) ;
					if (engineSoundType == SFX_BANK_TRUCK)
						freq /= 2;
					SampleManager.SetChannelFrequency(CHANNEL_PLAYER_VEHICLE_ENGINE, freq);
					if (!channelUsed) {
						SampleManager.SetChannelReverbFlag(CHANNEL_PLAYER_VEHICLE_ENGINE, m_bDynamicAcousticModelingStatus != FALSE);
						SampleManager.StartChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
					}
				} else if (processedAccelSampleStopped) {
					gearSoundStartTime = CTimer::GetTimeInMilliseconds();
					params.m_pVehicle->bAudioChangingGear = TRUE;
					if (!SampleManager.InitialiseChannel(CHANNEL_PLAYER_VEHICLE_ENGINE, soundOffset + SFX_CAR_ACCEL_1, SFX_BANK_0))
						return;
					SampleManager.SetChannelLoopCount(CHANNEL_PLAYER_VEHICLE_ENGINE, 1);
					SampleManager.SetChannelLoopPoints(CHANNEL_PLAYER_VEHICLE_ENGINE, 0, -1);

					SampleManager.SetChannelEmittingVolume(CHANNEL_PLAYER_VEHICLE_ENGINE, 120);
					SampleManager.SetChannel3DPosition(CHANNEL_PLAYER_VEHICLE_ENGINE, pos.x, pos.y, pos.z);
					SampleManager.SetChannel3DDistances(CHANNEL_PLAYER_VEHICLE_ENGINE, 50.0f, 12.5f);
					freq = (GearFreqAdj[CurrentPretendGear] + freqModifier + 22050);
					if (engineSoundType == SFX_BANK_TRUCK)
						freq /= 2;
					SampleManager.SetChannelFrequency(CHANNEL_PLAYER_VEHICLE_ENGINE, freq);
					if (!channelUsed) {
						SampleManager.SetChannelReverbFlag(CHANNEL_PLAYER_VEHICLE_ENGINE, m_bDynamicAcousticModelingStatus != FALSE);
						SampleManager.StartChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
					}
				} else if (CurrentPretendGear < params.m_pTransmission->nNumberOfGears - 1) {
					++CurrentPretendGear;
					gearSoundStartTime = CTimer::GetTimeInMilliseconds();
					params.m_pVehicle->bAudioChangingGear = TRUE;
					if (!SampleManager.InitialiseChannel(CHANNEL_PLAYER_VEHICLE_ENGINE, soundOffset + SFX_CAR_ACCEL_1, SFX_BANK_0))
						return;
					SampleManager.SetChannelLoopCount(CHANNEL_PLAYER_VEHICLE_ENGINE, 1);
					SampleManager.SetChannelLoopPoints(CHANNEL_PLAYER_VEHICLE_ENGINE, 0, -1);

					SampleManager.SetChannelEmittingVolume(CHANNEL_PLAYER_VEHICLE_ENGINE, 120);
					SampleManager.SetChannel3DPosition(CHANNEL_PLAYER_VEHICLE_ENGINE, pos.x, pos.y, pos.z);
					SampleManager.SetChannel3DDistances(CHANNEL_PLAYER_VEHICLE_ENGINE, 50.0f, 12.5f);
					freq = (GearFreqAdj[CurrentPretendGear] + freqModifier + 22050);
					if (engineSoundType == SFX_BANK_TRUCK)
						freq /= 2;
					SampleManager.SetChannelFrequency(CHANNEL_PLAYER_VEHICLE_ENGINE, freq);
					if (!channelUsed) {
						SampleManager.SetChannelReverbFlag(CHANNEL_PLAYER_VEHICLE_ENGINE, m_bDynamicAcousticModelingStatus != FALSE);
						SampleManager.StartChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
					}
				} else {
					nCruising = 1;
					goto PlayCruising;
				}
			}
		} else {
PlayCruising:
			bAccelSampleStopped = TRUE;
			SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
			if (isMoped || accelerateState >= 150 && wheelsOnGround && brakeState <= 0 && !params.m_pVehicle->bIsHandbrakeOn
				&& !lostTraction && currentGear >= params.m_pTransmission->nNumberOfGears - 1) {
				if (accelerateState >= 220 && params.m_fVelocityChange + 0.001f >= velocityChangeForAudio) {
					if (nCruising < 800)
						++nCruising;
				} else if (nCruising > 3) {
					--nCruising;
				}
				freq = 27 * nCruising + freqModifier + 22050;
				if (engineSoundType == SFX_BANK_TRUCK)
					freq /= 2;
				AddPlayerCarSample(120, freq, soundOffset + SFX_CAR_AFTER_ACCEL_1, engineSoundType, 64, TRUE);
			} else {
				nCruising = 0;
			}
		}
	}
	LastAccel = accelerateState;
	bHandbrakeOnLastFrame = params.m_pVehicle->bIsHandbrakeOn;
	bLostTractionLastFrame = lostTraction;
	return;
}

bool8
cAudioManager::ProcessVehicleSkidding(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 40.0f;

	CAutomobile *automobile;
	CBike *bike;
	uint8 numWheels;
	uint8 wheelsOnGround;
	float gasPedalAudio;
	tWheelState* wheelStateArr;


	cTransmission *transmission;
	int32 emittingVol;
	float newSkidVal = 0.0f;
	float skidVal = 0.0f;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;
	switch (params.m_VehicleType) {
	case VEHICLE_TYPE_CAR:
		automobile = (CAutomobile*)params.m_pVehicle;
		numWheels = 4;
		wheelStateArr = automobile->m_aWheelState;
		wheelsOnGround = automobile->m_nWheelsOnGround;
		gasPedalAudio = automobile->m_fGasPedalAudio;
		break;
	case VEHICLE_TYPE_BIKE:
		bike = (CBike*)params.m_pVehicle;
		numWheels = 2;
		wheelStateArr = bike->m_aWheelState;
		wheelsOnGround = bike->m_nWheelsOnGround;
		gasPedalAudio = bike->m_fGasPedalAudio;
		break;
	default:
		debug("\n * AUDIOLOG:  ProcessVehicleSkidding() Unsupported vehicle type %d * \n", params.m_VehicleType);
		return TRUE;
	}
	if (wheelsOnGround == 0)
		return TRUE;
	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);

	for (int32 i = 0; i < numWheels; i++) {
		if (wheelStateArr[i] == WHEEL_STATE_NORMAL)
			continue;
		transmission = params.m_pTransmission;
		switch (transmission->nDriveType) {
		case '4':
			newSkidVal = GetVehicleDriveWheelSkidValue(params.m_pVehicle, wheelStateArr[i], gasPedalAudio, transmission, params.m_fVelocityChange);
			break;
		case 'F':
			if (i == CARWHEEL_FRONT_LEFT || i == CARWHEEL_FRONT_RIGHT)
				newSkidVal = GetVehicleDriveWheelSkidValue(params.m_pVehicle, wheelStateArr[i], gasPedalAudio, transmission, params.m_fVelocityChange);
			else
				newSkidVal = GetVehicleNonDriveWheelSkidValue(params.m_pVehicle, wheelStateArr[i], transmission, params.m_fVelocityChange);
			break;
		case 'R':
			if (i == CARWHEEL_REAR_LEFT || i == CARWHEEL_REAR_RIGHT)
				newSkidVal = GetVehicleDriveWheelSkidValue(params.m_pVehicle, wheelStateArr[i], gasPedalAudio, transmission, params.m_fVelocityChange);
			else
				newSkidVal = GetVehicleNonDriveWheelSkidValue(params.m_pVehicle, wheelStateArr[i], transmission, params.m_fVelocityChange);
			break;
		default:
			break;
		}
		skidVal = Max(skidVal, newSkidVal);
	}

	if (skidVal > 0.0f) {
		emittingVol = 50.f * skidVal;
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 3;
			switch (params.m_pVehicle->m_nSurfaceTouched) {
			case SURFACE_GRASS:
			case SURFACE_HEDGE:
				m_sQueueSample.m_nSampleIndex = SFX_RAIN;
				emittingVol /= 4;
				m_sQueueSample.m_nFrequency = 13000.f * skidVal + 35000.f;
				m_sQueueSample.m_nVolume /= 4;
				if (m_sQueueSample.m_nVolume == 0)
					return TRUE;
				break;
			case SURFACE_GRAVEL:
			case SURFACE_MUD_DRY:
			case SURFACE_SAND:
			case SURFACE_WATER:
			case SURFACE_SAND_BEACH:
				m_sQueueSample.m_nSampleIndex = SFX_GRAVEL_SKID;
				m_sQueueSample.m_nFrequency = 6000.f * skidVal + 10000.f;
				break;

			default:
				m_sQueueSample.m_nSampleIndex = SFX_SKID;
				m_sQueueSample.m_nFrequency = 5000.f * skidVal + 11000.f;
				if (params.m_VehicleType == VEHICLE_TYPE_BIKE)
					m_sQueueSample.m_nFrequency += 2000;
				break;
			}

			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 8;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
	return TRUE;
}

float
cAudioManager::GetVehicleDriveWheelSkidValue(CVehicle *veh, tWheelState wheelState, float gasPedalAudio, cTransmission *transmission, float velocityChange)
{
	float relativeVelChange = 0.0f;
	float velChange;
	float relativeVel;

	switch (wheelState)
	{
	case WHEEL_STATE_SPINNING:
		if (gasPedalAudio > 0.4f)
			relativeVelChange = (gasPedalAudio - 0.4f) * (5.0f / 3.0f) * 0.75f;
		break;
	case WHEEL_STATE_SKIDDING:
		relativeVelChange = Min(1.0f, Abs(velocityChange) / transmission->fMaxVelocity);
		break;
	case WHEEL_STATE_FIXED:
		relativeVel = gasPedalAudio;
		if (relativeVel > 0.4f)
			relativeVel = (gasPedalAudio - 0.4f) * (5.0f / 3.0f);

		velChange = Abs(velocityChange);
		if (velChange > 0.04f)
			relativeVelChange = Min(1.0f, velChange / transmission->fMaxVelocity);
		if (relativeVel > relativeVelChange)
			relativeVelChange = relativeVel;

		break;
	default:
		break;
	}

	return Max(relativeVelChange, Min(1.0f, Abs(veh->m_vecTurnSpeed.z) * 20.0f));
}

float
cAudioManager::GetVehicleNonDriveWheelSkidValue(CVehicle *veh, tWheelState wheelState, cTransmission *transmission, float velocityChange)
{
	float relativeVelChange = 0.0f;

	if (wheelState == WHEEL_STATE_SKIDDING)
		relativeVelChange = Min(1.0f, Abs(velocityChange) / transmission->fMaxVelocity);

	return Max(relativeVelChange, Min(1.0f, Abs(veh->m_vecTurnSpeed.z) * 20.0f));
}

bool8
cAudioManager::ProcessVehicleHorn(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 40.0f;

	CVehicle *veh;
	uint8 volume;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;

	veh = params.m_pVehicle;
	if (veh->m_bSirenOrAlarm && UsesSirenSwitching(params))
		return TRUE;

	if (veh->m_modelIndex == MI_MRWHOOP)
		return TRUE;

	if (veh->IsAlarmOn())
		return TRUE;

	if (veh->m_nCarHornTimer != 0) {
		if (veh->GetStatus() != STATUS_PLAYER) {
			veh->m_nCarHornTimer = Min(44, veh->m_nCarHornTimer);
			if (veh->m_nCarHornTimer == 44)
				veh->m_nCarHornPattern = (m_FrameCounter + m_sQueueSample.m_nEntityIndex) & 7;

			if (!hornPatternsArray[veh->m_nCarHornPattern][44 - veh->m_nCarHornTimer])
				return TRUE;
		}

		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		volume = veh->bIsDrowning ? 20 : 80;
		m_sQueueSample.m_nVolume = ComputeVolume(volume, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 4;
			m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nHornSample;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_nFrequency = aVehicleSettings[params.m_nIndex].m_nHornFrequency;
			m_sQueueSample.m_nLoopCount = 0;
#ifdef FIX_BUGS
			m_sQueueSample.m_nEmittingVolume = volume;
#else
			m_sQueueSample.m_nEmittingVolume = 80;
#endif
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 5.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 4;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
	return TRUE;
}

bool8
cAudioManager::UsesSiren(cVehicleParams& params) const
{
	return params.m_pVehicle->UsesSiren();
}

bool8
cAudioManager::UsesSirenSwitching(cVehicleParams& params) const
{
	if (params.m_nIndex == FIRETRUK || params.m_nIndex == MRWHOOP)
		return FALSE;
	return UsesSiren(params);
}

bool8
cAudioManager::ProcessVehicleSirenOrAlarm(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 110.0f;

	CVehicle *veh;
	uint8 volume;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;

	veh = params.m_pVehicle;
	if (!veh->m_bSirenOrAlarm && !veh->IsAlarmOn())
		return TRUE;

	if (veh->IsAlarmOn()) {
		if (CTimer::GetTimeInMilliseconds() > veh->m_nCarHornTimer)
			veh->m_nCarHornTimer = CTimer::GetTimeInMilliseconds() + 750;

		if (veh->m_nCarHornTimer < CTimer::GetTimeInMilliseconds() + 375)
			return TRUE;
	}

	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
	volume = veh->bIsDrowning ? 20 : 80;
	m_sQueueSample.m_nVolume = ComputeVolume(volume, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 5;
		if (UsesSiren(params)) {
			if (params.m_pVehicle->GetStatus() == STATUS_ABANDONED)
				return TRUE;
			if (veh->m_nCarHornTimer != 0 && params.m_nIndex != FIRETRUK && params.m_nIndex != MRWHOOP) {
				m_sQueueSample.m_nSampleIndex = SFX_SIREN_FAST;
				if (params.m_nIndex == FBIRANCH)
					m_sQueueSample.m_nFrequency = 12668;
				else
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SIREN_FAST);
				m_sQueueSample.m_nCounter = 60;
			} else if (params.m_nIndex == VICECHEE) {
				m_sQueueSample.m_nSampleIndex = SFX_POLICE_SIREN_SLOW;
				m_sQueueSample.m_nFrequency = 11440;
			} else {
				m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nSirenOrAlarmSample;
				m_sQueueSample.m_nFrequency = aVehicleSettings[params.m_nIndex].m_nSirenOrAlarmFrequency;
			}
		} else {
			m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nHornSample;
			m_sQueueSample.m_nFrequency = aVehicleSettings[params.m_nIndex].m_nHornFrequency;
		}
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = volume;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 7.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 5;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
	return TRUE;
}

bool8
cAudioManager::UsesReverseWarning(int32 model) const
{
	return model == LINERUN || model == FIRETRUK || model == BUS || model == COACH || model == PACKER || model == FLATBED;
}

bool8
cAudioManager::ProcessVehicleReverseWarning(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 50.0f;

	CVehicle *veh = params.m_pVehicle;
	uint8 volume;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;

	if (veh->bEngineOn && veh->m_fGasPedal < 0.0f) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		volume = veh->bIsDrowning ? 15 : 60;
		m_sQueueSample.m_nVolume = ComputeVolume(volume, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 12;
			m_sQueueSample.m_nSampleIndex = SFX_REVERSE_WARNING;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_nFrequency = (100 * m_sQueueSample.m_nEntityIndex & 1023) + SampleManager.GetSampleBaseFrequency(SFX_REVERSE_WARNING);
			m_sQueueSample.m_nLoopCount = 0;
#ifdef FIX_BUGS
			m_sQueueSample.m_nEmittingVolume = volume;
#else
			m_sQueueSample.m_nEmittingVolume = 60;
#endif
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
	return TRUE;
}

bool8
cAudioManager::ProcessVehicleDoors(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 40.0f;

	CAutomobile *automobile;
	int8 doorState;
	int32 emittingVol;
	float velocity;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;

	automobile = (CAutomobile *)params.m_pVehicle;
	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
	for (int32 i = 0; i < ARRAY_SIZE(automobile->Doors); i++) {
		if (automobile->Damage.GetDoorStatus(i) == DOOR_STATUS_SWINGING) {
			doorState = automobile->Doors[i].m_nDoorState;
			if (doorState == DOORST_OPEN || doorState == DOORST_CLOSED) {
				velocity = Min(0.3f, Abs(automobile->Doors[i].m_fAngVel));
				if (velocity > 0.0035f) {
					emittingVol = (100.0f * velocity * 10.0f / 3.0f);
					m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
					if (m_sQueueSample.m_nVolume != 0) {
						m_sQueueSample.m_nCounter = i + 6;
						m_sQueueSample.m_nSampleIndex = m_anRandomTable[1] % 6 + SFX_COL_CAR_PANEL_1;
						m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex) + RandomDisplacement(1000);
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						m_sQueueSample.m_bIs2D = FALSE;
						m_sQueueSample.m_nReleasingVolumeModificator = 10;
						m_sQueueSample.m_nLoopCount = 1;
						m_sQueueSample.m_nEmittingVolume = emittingVol;
						RESET_LOOP_OFFSETS
						m_sQueueSample.m_fSpeedMultiplier = 1.0f;
						m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
						m_sQueueSample.m_bReleasingSoundFlag = TRUE;
						m_sQueueSample.m_bReverbFlag = TRUE;
						m_sQueueSample.m_bRequireReflection = TRUE;
						AddSampleToRequestedQueue();
					}
				}
			}
		}
	}
	return TRUE;
}

bool8
cAudioManager::ProcessAirBrakes(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 30.0f;
	CAutomobile *automobile;
	uint8 volume;

	if (params.m_fDistance > SQR(SOUND_INTENSITY))
		return FALSE;
	automobile = (CAutomobile *)params.m_pVehicle;
	if (!automobile->bEngineOn)
		return TRUE;

	if ((automobile->m_fVelocityChangeForAudio < 0.025f || params.m_fVelocityChange >= 0.025f) &&
	    (automobile->m_fVelocityChangeForAudio > -0.025f || params.m_fVelocityChange <= 0.025f))
		return TRUE;

	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
	volume = m_anRandomTable[0] % 10 + 70;
	m_sQueueSample.m_nVolume = ComputeVolume(volume, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 13;
		m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_AIR_BRAKES);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 10;
		m_sQueueSample.m_nLoopCount = 1;
		m_sQueueSample.m_nEmittingVolume = volume;
		RESET_LOOP_OFFSETS
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = TRUE;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}

	return TRUE;
}

bool8
cAudioManager::HasAirBrakes(int32 model) const
{
	return model == LINERUN || model == FIRETRUK || model == TRASH || model == BUS || model == BARRACKS 
		|| model == COACH || model == PACKER || model == FLATBED;
}

bool8
cAudioManager::ProcessEngineDamage(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 40.0f;

	float health;
	uint8 emittingVolume;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;
	if (params.m_pVehicle->m_modelIndex == MI_CADDY)
		return TRUE;
	if (params.m_pVehicle->GetStatus() == STATUS_WRECKED)
		return TRUE;
	health = params.m_pVehicle->m_fHealth;
	if (health < 390.0f) {
		if (health < 250.0f) {
			emittingVolume = 60;
			m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
			m_sQueueSample.m_nReleasingVolumeModificator = 7;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE);
		} else {
			emittingVolume = 30;
			m_sQueueSample.m_nSampleIndex = SFX_PALM_TREE_LO;
			m_sQueueSample.m_nReleasingVolumeModificator = 7;
			m_sQueueSample.m_nFrequency = 27000;
		}
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		if (params.m_pVehicle->bIsDrowning)
			emittingVolume /= 2;
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVolume, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 28;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVolume;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
	return TRUE;
}

bool8
cAudioManager::ProcessCarBombTick(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 40.0f;
	const uint8 EMITTING_VOLUME = 60;

	uint8 bombType;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;
	if (params.m_pVehicle->bEngineOn) {
		switch (params.m_VehicleType) {
		case VEHICLE_TYPE_CAR:
			bombType = params.m_pVehicle->m_bombType;
			break;
		case VEHICLE_TYPE_BIKE:
			bombType = params.m_pVehicle->m_bombType;
			break;
		default:
			debug("\n * AUDIOLOG:  ProcessCarBombTick()  Unsupported vehicle type %d * \n", params.m_VehicleType);
			return TRUE;
			break;
		}
		if (bombType == CARBOMB_TIMEDACTIVE) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(EMITTING_VOLUME, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nCounter = 35;
				m_sQueueSample.m_nSampleIndex = SFX_COUNTDOWN;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_COUNTDOWN);
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = EMITTING_VOLUME;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 3;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
	}
	return TRUE;
}

void
cAudioManager::ProcessVehicleOneShots(cVehicleParams& params)
{
	int16 event;
	uint8 emittingVol;
	float relVol;
	float vol;
	bool8 noReflections;
	bool8 isHeli;
	float maxDist;
	static uint8 GunIndex = 53;

	for (int i = 0; i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; i++) {
		noReflections = FALSE;
		isHeli = FALSE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		event = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i];
		switch (event) {
		case SOUND_CAR_DOOR_CLOSE_BONNET:
		case SOUND_CAR_DOOR_CLOSE_BUMPER:
		case SOUND_CAR_DOOR_CLOSE_FRONT_LEFT:
		case SOUND_CAR_DOOR_CLOSE_FRONT_RIGHT:
		case SOUND_CAR_DOOR_CLOSE_BACK_LEFT:
		case SOUND_CAR_DOOR_CLOSE_BACK_RIGHT: {
			const float SOUND_INTENSITY = 50.0f;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[2] % 5 + 122;
			switch (aVehicleSettings[params.m_nIndex].m_bDoorType) {
			case OLD_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_OLD_CAR_DOOR_CLOSE;
				break;
			case NEW_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_NEW_CAR_DOOR_CLOSE;
				break;
			case TRUCK_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_TRUCK_DOOR_CLOSE;
				break;
			case BUS_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
				break;
			default:
				m_sQueueSample.m_nSampleIndex = SFX_NEW_CAR_DOOR_CLOSE;
				break;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#ifdef THIS_IS_STUPID
			m_sQueueSample.m_nCounter = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] + 22;
#else
			m_sQueueSample.m_nCounter = event + 22;
#endif
			if (params.m_pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI)
				m_sQueueSample.m_nFrequency = 28062;
			else
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_CAR_DOOR_OPEN_BONNET:
		case SOUND_CAR_DOOR_OPEN_BUMPER:
		case SOUND_CAR_DOOR_OPEN_FRONT_LEFT:
		case SOUND_CAR_DOOR_OPEN_FRONT_RIGHT:
		case SOUND_CAR_DOOR_OPEN_BACK_LEFT:
		case SOUND_CAR_DOOR_OPEN_BACK_RIGHT: {
			const float SOUND_INTENSITY = 50.0f;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[1] % 10 + 117;
			switch (aVehicleSettings[params.m_nIndex].m_bDoorType) {
			case OLD_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_OLD_CAR_DOOR_OPEN;
				break;
			case TRUCK_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_TRUCK_DOOR_OPEN;
				break;
			case BUS_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
				break;
			default:
				m_sQueueSample.m_nSampleIndex = SFX_NEW_CAR_DOOR_OPEN;
				break;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#ifdef THIS_IS_STUPID
			m_sQueueSample.m_nCounter = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] + 10;
#else
			m_sQueueSample.m_nCounter = event + 10;
#endif
			if (params.m_pVehicle->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI)
				m_sQueueSample.m_nFrequency = 23459;
			else
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_CAR_WINDSHIELD_CRACK: {
			const float SOUND_INTENSITY = 40.0f;
			maxDist = SQR(SOUND_INTENSITY);
			m_sQueueSample.m_nSampleIndex = SFX_GLASS_CRACK;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 68;
			emittingVol = m_anRandomTable[1] % 30 + 80; //GetRandomNumberInRange(1, 80, 109)
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_CRACK);
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		} break;
		case SOUND_CAR_JUMP: 
		case SOUND_CAR_JUMP_2: {
			const float SOUND_INTENSITY = 35.0f;
			static uint8 WheelIndex = 82;
			maxDist = SQR(SOUND_INTENSITY);
#ifdef THIS_IS_STUPID
			if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] == SOUND_CAR_JUMP_2) {
#else
			if (event == SOUND_CAR_JUMP_2) {
#endif
				m_sQueueSample.m_nSampleIndex = SFX_TYRE_BURST_B;
				emittingVol = Max(50.0f, 2 * (60.0f * m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]));
			} else {
				m_sQueueSample.m_nSampleIndex = SFX_TYRE_BUMP;
				emittingVol = Max(80.f, 2 * (100.0f * m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]));
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = WheelIndex++;
			if (WheelIndex > 85)
				WheelIndex = 82;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TYRE_BUMP);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
			if (params.m_VehicleType == VEHICLE_TYPE_BIKE)
				m_sQueueSample.m_nFrequency *= 2;
			m_sQueueSample.m_nReleasingVolumeModificator = 6;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			break;
		}
		case SOUND_CAR_TYRE_POP: {
			const float SOUND_INTENSITY = 60.0f;
			static uint8 WheelIndex = 91;
			m_sQueueSample.m_nSampleIndex = SFX_TYRE_BURST;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = WheelIndex++;
			if (WheelIndex > 94)
				WheelIndex = 91;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TYRE_BURST);
			m_sQueueSample.m_nFrequency += RandomDisplacement(2000);
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[4] % 10 + 117;
			break;
		}
		case SOUND_CAR_ENGINE_START: {
			const float SOUND_INTENSITY = 40.0f;
			if (params.m_pVehicle->GetVehicleAppearance() != VEHICLE_APPEARANCE_CAR
				|| params.m_pVehicle->m_modelIndex == MI_CADDY)
				continue;
			emittingVol = 60;
			maxDist = SQR(SOUND_INTENSITY);
			m_sQueueSample.m_nSampleIndex = SFX_CAR_STARTER;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 33;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_STARTER);
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_CAR_LIGHT_BREAK: {
			const float SOUND_INTENSITY = 30.0f;
			m_sQueueSample.m_nSampleIndex = SFX_GLASS_SHARD_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 37;
			m_sQueueSample.m_nFrequency = 9 * SampleManager.GetSampleBaseFrequency(SFX_GLASS_SHARD_1) / 10;
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 8);
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[4] % 10 + 30;
			break;
		}
		case SOUND_CAR_HYDRAULIC_1:
		case SOUND_CAR_HYDRAULIC_2: {
			const float SOUND_INTENSITY = 35.0f;
			if (event == SOUND_CAR_HYDRAULIC_1)
				m_sQueueSample.m_nFrequency = 15600;
			else
				m_sQueueSample.m_nFrequency = 13118;
			m_sQueueSample.m_nSampleIndex = SFX_SUSPENSION_FAST_MOVE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 51;
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 8);
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[0] % 15 + 55;
			break;
		}
		case SOUND_CAR_HYDRAULIC_3: {
			const float SOUND_INTENSITY = 35.0f;
			m_sQueueSample.m_nSampleIndex = SFX_SUSPENSION_SLOW_MOVE_LOOP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 86;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SUSPENSION_SLOW_MOVE_LOOP);
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_nReleasingVolumeDivider = 7;
			noReflections = TRUE;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[0] % 15 + 55;
			break;
		}
		case SOUND_CAR_JERK: {
			const float SOUND_INTENSITY = 35.0f;
			m_sQueueSample.m_nSampleIndex = SFX_SHAG_SUSPENSION;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 87;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SHAG_SUSPENSION);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 8);
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[1] % 15 + 55;
			break;
		}
		case SOUND_CAR_SPLASH: {
			const float SOUND_INTENSITY = 60.0f;
			static uint8 WaveIndex = 41;
			vol = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			if (vol <= 150.0f)
				continue;
			if (vol > 800.0f)
				m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] = 800.0f;
			relVol = (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] - 150.0f) / 650.0f;
			m_sQueueSample.m_nSampleIndex = (m_anRandomTable[0] & 1) + SFX_BOAT_SPLASH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = WaveIndex++;
			if (WaveIndex > 46)
				WaveIndex = 41;
			m_sQueueSample.m_nFrequency = (7000.0f * relVol) + 6000;
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			emittingVol = (35.0f * relVol);
			maxDist = SQR(SOUND_INTENSITY);
			break;
		}
		/*case SOUND_17: {
			const float SOUND_INTENSITY = 50.0f;
			m_sQueueSample.m_nSampleIndex = SFX_POLICE_BOAT_THUMB_OFF;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 47;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_POLICE_BOAT_THUMB_OFF) + RandomDisplacement(600);
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			emittingVol = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			maxDist = SQR(SOUND_INTENSITY);
			break;
		}*/
#ifdef GTA_TRAIN
		case SOUND_TRAIN_DOOR_CLOSE:
		case SOUND_TRAIN_DOOR_OPEN: {
			const float SOUND_INTENSITY = 35.0f;
			m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 59;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 11025;
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 5.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[1] % 20 + 70;
			break;
		}
#endif
		case SOUND_CAR_TANK_TURRET_ROTATE: {
			const float SOUND_INTENSITY = 40.0f;
			vol = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			if (vol > 24.0f / 625.0f)
				vol = 24.0f / 625.0f;
			m_sQueueSample.m_nSampleIndex = SFX_TANK_TURRET;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 79;
			m_sQueueSample.m_nFrequency = (3000.0f * vol * 625.0f / 24.0f) + 9000;
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			emittingVol = (37.0f * vol * 625.0f / 24.0f) + 90;
			maxDist = SQR(SOUND_INTENSITY);
			noReflections = TRUE;
			break;
		}
		case SOUND_CAR_BOMB_TICK: {
			const float SOUND_INTENSITY = 30.0f;
			m_sQueueSample.m_nSampleIndex = SFX_BOMB_BEEP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 80;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BOMB_BEEP);
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			m_sQueueSample.m_bRequireReflection = TRUE;
			emittingVol = 60;
			break;
		}
		case SOUND_PLANE_ON_GROUND: {
			const float SOUND_INTENSITY = 180.0f;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_LAND_WHEELS;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 81;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_JUMBO_LAND_WHEELS);
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[4] % 25 + 75;
			break;
		}
		case SOUND_HELI_BLADE:{
			const float SOUND_INTENSITY = 35.0f;
			static uint8 HeliIndex = 89;
			relVol = ((CAutomobile*)params.m_pVehicle)->m_aWheelSpeed[1] * 50.0f / 11.0f;
			if (relVol < 0.2f || relVol == 1.0f)
				continue;
			emittingVol = (1.0f - relVol) * 70.0f;
			maxDist = SQR(SOUND_INTENSITY);
			m_sQueueSample.m_nSampleIndex = SFX_CAR_HELI_ROT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = HeliIndex++;
			if (HeliIndex > 90)
				HeliIndex = 89;
			m_sQueueSample.m_nFrequency = (8000.0f * relVol) + 16000;
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			break;
		}
		case SOUND_WEAPON_SHOT_FIRED: {
			const float SOUND_INTENSITY = 120.0f;
			CVehicle *playerVeh;
			CPlayerPed *playerPed;

			switch (params.m_pVehicle->m_modelIndex) {
			case MI_HUNTER:
			case MI_CHOPPER:
			case MI_SEASPAR:
			case MI_SPARROW:
			case MI_MAVERICK:
			case MI_VCNMAV:
				if (params.m_pVehicle->m_modelIndex == MI_HUNTER) {
					if (Pads[0].GetHandBrake() == 0) {
						playerVeh = FindPlayerVehicle();
						playerPed = FindPlayerPed();
						if (playerVeh == nil && playerPed != nil) {
							if (playerPed->m_attachedTo != nil && playerPed->m_attachedTo->GetType() == ENTITY_TYPE_VEHICLE)
								playerVeh = (CVehicle*)playerPed->m_attachedTo;
						}
						if (playerVeh != params.m_pVehicle) {
							m_sQueueSample.m_nSampleIndex = SFX_M60_LEFT;
							m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						} else {
							m_sQueueSample.m_nSampleIndex = SFX_ROCKET_LEFT;
							m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						}
					} else {
						m_sQueueSample.m_nSampleIndex = SFX_M60_LEFT;
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					}
				} else {
					m_sQueueSample.m_nSampleIndex = SFX_M60_LEFT;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				}
				maxDist = SQR(SOUND_INTENSITY);
				m_sQueueSample.m_nCounter = GunIndex++;
				emittingVol = MAX_VOLUME;
				if (GunIndex > 58)
					GunIndex = 53;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_M60_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
				m_sQueueSample.m_nReleasingVolumeModificator = 2;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bRequireReflection = TRUE;
				isHeli = TRUE;
				break;
			default:
			{
				maxDist = SQR(SOUND_INTENSITY);
#ifdef FIX_BUGS
				int32 sampleIndex;
				int32 frequency;
				CPed *pPed = params.m_pVehicle->pDriver;
				if(!pPed)
					break;
				if(!pPed->HasWeaponSlot(WEAPONSLOT_SUBMACHINEGUN)) {
					sampleIndex = SFX_UZI_LEFT;
					frequency = SampleManager.GetSampleBaseFrequency(sampleIndex);
					frequency += RandomDisplacement(frequency / 32);
				} else
					switch(pPed->GetWeapon(WEAPONSLOT_SUBMACHINEGUN).m_eWeaponType) {
					case WEAPONTYPE_TEC9:
						sampleIndex = SFX_TEC_LEFT;
						frequency = RandomDisplacement(500) + 17000;
						break;
					case WEAPONTYPE_SILENCED_INGRAM:
						sampleIndex = SFX_TEC_LEFT;
						frequency = RandomDisplacement(1000) + 34000;
						break;
					case WEAPONTYPE_MP5:
						sampleIndex = SFX_MP5_LEFT;
						frequency = SampleManager.GetSampleBaseFrequency(sampleIndex);
						frequency += RandomDisplacement(frequency / 32);
						break;
					default:
						sampleIndex = SFX_UZI_LEFT;
						frequency = SampleManager.GetSampleBaseFrequency(sampleIndex);
						frequency += RandomDisplacement(frequency / 32);
						break;
					}
				m_sQueueSample.m_nSampleIndex = sampleIndex;
#else
				m_sQueueSample.m_nSampleIndex = SFX_UZI_LEFT;
#endif
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = GunIndex++;
				emittingVol = m_anRandomTable[2] % 15 + 65;
				if(GunIndex > 58) GunIndex = 53;
#ifdef FIX_BUGS
				m_sQueueSample.m_nFrequency = frequency;
#else
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_UZI_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
#endif
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bRequireReflection = TRUE;
				break;
			}
			}
			break;
		}
		case SOUND_WEAPON_HIT_VEHICLE: {
			const float SOUND_INTENSITY = 40.0f;
			m_sQueueSample.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % ARRAY_SIZE(m_anRandomTable)] % 6 + SFX_BULLET_CAR_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 34;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
			m_sQueueSample.m_nReleasingVolumeModificator = 7;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[3] % 20 + 90;
			break;
		}
		case SOUND_BOMB_TIMED_ACTIVATED:
		case SOUND_91:
		case SOUND_BOMB_ONIGNITION_ACTIVATED:
		case SOUND_BOMB_TICK: {
			const float SOUND_INTENSITY = 50.0f;
			m_sQueueSample.m_nSampleIndex = SFX_ARM_BOMB;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 36;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ARM_BOMB);
			m_sQueueSample.m_nReleasingVolumeModificator = 0;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bRequireReflection = TRUE;
			emittingVol = 50;
			maxDist = SQR(SOUND_INTENSITY);
			break;
		}
		case SOUND_PED_HELI_PLAYER_FOUND: {
			cPedParams pedParams;
			pedParams.m_bDistanceCalculated = params.m_bDistanceCalculated;
			pedParams.m_fDistance = params.m_fDistance;
			SetupPedComments(pedParams, SOUND_PED_HELI_PLAYER_FOUND);
			continue;
		}
		/* case SOUND_PED_BODYCAST_HIT:
			pedParams.m_pPed = nil;
			pedParams.m_bDistanceCalculated = FALSE;
			pedParams.m_fDistance = 0.0f;
			pedParams.m_bDistanceCalculated = params.m_bDistanceCalculated;
			pedParams.m_fDistance = params.m_fDistance;
			SetupPedComments(&pedParams, SOUND_PED_BODYCAST_HIT);
			continue; */
		case SOUND_PED_VCPA_PLAYER_FOUND: {
			cPedParams pedParams;
			pedParams.m_bDistanceCalculated = params.m_bDistanceCalculated;
			pedParams.m_fDistance = params.m_fDistance;
			SetupPedComments(pedParams, SOUND_PED_VCPA_PLAYER_FOUND);
			continue;
		}
		case SOUND_WATER_FALL: {
			const float SOUND_INTENSITY = 40.0f;
			static uint32 WaterFallFrame = 0;
			if (m_FrameCounter <= WaterFallFrame)
				continue;
			WaterFallFrame = m_FrameCounter + 6;
			m_sQueueSample.m_nSampleIndex = SFX_SPLASH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 15;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 16000;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			m_sQueueSample.m_bRequireReflection = TRUE;
			emittingVol = m_anRandomTable[4] % 20 + 90;
			break;
		}
		case SOUND_SPLATTER: {
			const float SOUND_INTENSITY = 40.0f;
			static uint8 CrunchOffset = 0;
			m_sQueueSample.m_nSampleIndex = CrunchOffset + SFX_PED_CRUNCH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 48;
			m_sQueueSample.m_nFrequency = RandomDisplacement(6000) + 16000;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			++CrunchOffset;
			maxDist = SQR(SOUND_INTENSITY);
			emittingVol = m_anRandomTable[4] % 20 + 55;
			CrunchOffset %= 2;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_CAR_PED_COLLISION: {
			const float SOUND_INTENSITY = 40.0f;
			vol = Min(20.0f, m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]);
			emittingVol = Min(127, (3 * (vol / 20.0f * 127.f)) / 2);
			if (emittingVol == 0)
				continue;

			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 50;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			maxDist = SQR(SOUND_INTENSITY);
			break;
		}
		default:
			continue;
		}
		if (params.m_fDistance < maxDist) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				if (noReflections) {
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				} else {
					m_sQueueSample.m_nLoopCount = 1;
					m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				}
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bReverbFlag = TRUE;
				if (isHeli) {
					if (0.2f * m_sQueueSample.m_fSoundIntensity > m_sQueueSample.m_fDistance) {
						m_sQueueSample.m_bIs2D = TRUE;
						m_sQueueSample.m_nOffset = 0;
#ifdef THIS_IS_STUPID
						goto AddSample;
#else
						AddSampleToRequestedQueue();
						m_sQueueSample.m_nOffset = 127;
						m_sQueueSample.m_nSampleIndex++;
						m_sQueueSample.m_nCounter = GunIndex++;
						if (GunIndex > 58)
							GunIndex = 53;
						m_sQueueSample.m_bRequireReflection = FALSE;
						AddSampleToRequestedQueue();
						continue;
#endif
					}
					isHeli = FALSE;
				}
				m_sQueueSample.m_bIs2D = FALSE;
#ifdef THIS_IS_STUPID
AddSample:
				AddSampleToRequestedQueue();
				if (isHeli) {
					m_sQueueSample.m_nOffset = 127;
					m_sQueueSample.m_nSampleIndex++;
					m_sQueueSample.m_nCounter = GunIndex++;
					if (GunIndex > 58)
						GunIndex = 53;
					m_sQueueSample.m_bRequireReflection = 0;
					AddSampleToRequestedQueue();
				}
#else
				AddSampleToRequestedQueue();
#endif
				continue;

			}
		}
	}
}

#ifdef GTA_TRAIN
bool8
cAudioManager::ProcessTrainNoise(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 300.0f;

	CTrain *train;
	uint8 emittingVol;
	float speedMultipler;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;

	if (params.m_fVelocityChange > 0.0f) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		train = (CTrain *)params.m_pVehicle;
		speedMultipler = Min(1.0f, train->m_fSpeed * 250.f / 51.f);
		emittingVol = (75.f * speedMultipler);
		if (train->m_fWagonPosition == 0.0f) {
			m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nCounter = 32;
				m_sQueueSample.m_nSampleIndex = SFX_TRAIN_FAR;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 2;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TRAIN_FAR);
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 3;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
		const float SOUND_INTENSITY = 70.0f;
		if (params.m_fDistance < SQR(SOUND_INTENSITY)) {
			m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nCounter = 33;
				m_sQueueSample.m_nSampleIndex = SFX_TRAIN_NEAR;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 5;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TRAIN_NEAR) + 100 * m_sQueueSample.m_nEntityIndex % 987;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 6.0f;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 3;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
	}
	return TRUE;
}
#endif
bool8
cAudioManager::ProcessBoatEngine(cVehicleParams& params)
{
	CBoat *boat;
	float padRelativeAccerate;

	bool8 isV12 = FALSE;
	static int32 LastFreq = 2000;
	static int8 LastVol = 0;

	static const float intensity = 90.0f;

	if (params.m_fDistance < SQR(intensity)) {
		boat = (CBoat *)params.m_pVehicle;
		if(boat->GetStatus() == STATUS_WRECKED)
			return TRUE;

		float freqModificator;
		float volModificator;
		int BaseVol;
		int BaseFreq;

		switch(boat->GetModelIndex()) {
		case MI_RIO:
			freqModificator = 490.0f;
			volModificator = 60.0f;
			BaseVol = 20;
			BaseFreq = 1888;
			break;
		case MI_PREDATOR:
		case MI_SQUALO:
		case MI_SPEEDER:
		case MI_COASTG:
		case MI_DINGHY:
		case MI_JETMAX:
			freqModificator = 6000.0f;
			volModificator = 60.0f;
			isV12 = TRUE;
			BaseFreq = 9000;
			BaseVol = 20;
			break;
		case MI_REEFER:
			freqModificator = 715.0f;
			volModificator = 80.0f;
			BaseVol = 0;
			BaseFreq = 3775;
			break;
		case MI_TROPIC:
		case MI_MARQUIS:
			freqModificator = 463.0f;
			volModificator = 60.0f;
			BaseVol = 20;
			BaseFreq = 1782;
			break;
		default:
			return TRUE;
		}

		bool8 bIsPlayerVeh;

		if(FindPlayerVehicle() == params.m_pVehicle) {
			float padAccelerate = Max(Pads[0].GetAccelerate(), Pads[0].GetBrake());
			padRelativeAccerate = padAccelerate / 255.0f;
			bIsPlayerVeh = TRUE;
		} else {
			padRelativeAccerate = Max(params.m_pVehicle->m_fGasPedal, params.m_pVehicle->m_fBrakePedal);
			bIsPlayerVeh = FALSE;
		}

		int Freq = BaseFreq + (padRelativeAccerate * freqModificator);
		int Vol = BaseVol + (padRelativeAccerate * volModificator);

		if(!boat->bPropellerInWater)
			Freq = (9 * Freq) / 8;

		if(bIsPlayerVeh) {
			if(Freq > LastFreq) {
				if(isV12)
					Freq = Min(Freq, LastFreq + 100);
				else
					Freq = Min(Freq, LastFreq + 15);
			} else {
				if(isV12)
					Freq = Max(Freq, LastFreq - 100);
				else
					Freq = Max(Freq, LastFreq - 15);
			}
			if(Vol > LastVol)
				Vol = Min(Vol, LastVol + 3);
			else
				Vol = Max(Vol, LastVol - 3);
		}

		if (Vol > 0) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, intensity, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nFrequency = Freq;
				m_sQueueSample.m_nCounter = 40;
				if (isV12)
					m_sQueueSample.m_nSampleIndex = SFX_BOAT_V12_LOOP;
				else
					m_sQueueSample.m_nSampleIndex = SFX_BOAT_CRUISER_LOOP;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = Vol;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_fSoundIntensity = intensity;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 7;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}

		if(boat->GetModelIndex() == MI_REEFER) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(80, intensity, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nFrequency = 6000;
				m_sQueueSample.m_nCounter = 39;
				m_sQueueSample.m_nSampleIndex = SFX_FISHING_BOAT_IDLE;
				m_sQueueSample.m_nFrequency += (m_sQueueSample.m_nEntityIndex * 65536) % 1000;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = 80;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_fSoundIntensity = intensity;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 7;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
		if(bIsPlayerVeh) {
			LastFreq = Freq;
			LastVol = Vol;
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessBoatMovingOverWater(cVehicleParams& params)
{
	float velocityChange;
	int32 vol;
	float multiplier;

	if (params.m_fDistance > SQR(50))
		return FALSE;

	velocityChange = Abs(params.m_fVelocityChange);
	if (velocityChange <= 0.0005f && ((CBoat*)params.m_pVehicle)->bBoatInWater)
		return TRUE;

	velocityChange = Min(0.75f, velocityChange);
	multiplier = (velocityChange - 0.0005f) / (1499.0f / 2000.0f);
	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
	vol = (30.f * multiplier);
	m_sQueueSample.m_nVolume = ComputeVolume(vol, 50.f, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 38;
		m_sQueueSample.m_nSampleIndex = SFX_BOAT_WATER_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nFrequency = (6050.f * multiplier) + 16000;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = vol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_fSoundIntensity = 50.0f;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 6;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}

	return TRUE;
}

void
cAudioManager::ProcessCarHeli(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 250.0f;

	CVehicle* playerVeh;
	CVehicle* veh;
	CAutomobile* automobile;
	CBoat* boat;

	uint8 emittingVol;
	int16 brakeState;
	int16 accelerateState;
	uint32 freq;
	float propellerSpeed;
	float freqModifier; //may be relate to angle with horison
	float cameraAngle;
	bool8 distanceCalculatedOld;
	float distanceOld;
	CVector vecPosOld;

	float volumeModifier;//TODO find better name
	bool8 hunterBool;
	
	static uint32 freqFrontPrev = 14287;
	static uint32 freqPropellerPrev = 7143;
	static uint32 freqSkimmerPrev = 14287;

	boat = nil;
	automobile = nil;
	hunterBool = FALSE;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return;

	playerVeh = FindPlayerVehicle();
	veh = params.m_pVehicle;
	if (playerVeh == veh) {
		accelerateState = Pads[0].GetAccelerate();
		brakeState = Pads[0].GetBrake();
	} else {
		accelerateState = veh->m_fGasPedal * 255.0f;
		brakeState = veh->m_fBrakePedal * 255.0f;
	}
	freqModifier = Abs(veh->GetUp().y);
	cameraAngle = (DotProduct(veh->GetMatrix().GetForward(), TheCamera.GetForward()) + 1.0f) / 2.0f;
	if (veh->m_modelIndex == MI_SKIMMER) {
		boat = (CBoat*)veh;
		propellerSpeed = boat->m_fMovingSpeed * 50.0f / 11.0f;
	} else if (params.m_VehicleType == VEHICLE_TYPE_HELI) {
		propellerSpeed = 1.0f;
	} else {
		automobile = (CAutomobile*)veh;
		propellerSpeed = automobile->m_aWheelSpeed[1] * 50.0f / 11.0f;
	}

	if (propellerSpeed == 0.0f)
		return;

	propellerSpeed = Min(1.0f, propellerSpeed);
	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);


	//sound on long distances
	if (m_sQueueSample.m_fDistance >= 40.0f)
		emittingVol = propellerSpeed * 75.0f;
	else if (m_sQueueSample.m_fDistance >= 25.0f)
		emittingVol = (m_sQueueSample.m_fDistance - 25.0f) * (75.0f * propellerSpeed) / 15.0f;
	else
		emittingVol = 0;
	if (emittingVol != 0) {
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 88;
			if (boat != nil) {
				m_sQueueSample.m_nSampleIndex = SFX_SEAPLANE_PRO3;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				if (accelerateState > 0 || brakeState > 0)
					m_sQueueSample.m_nFrequency = 4600 + Min(1.0f, (Max(accelerateState, brakeState) / 255.0f) * freqModifier) * 563;
				else
					m_sQueueSample.m_nFrequency = 3651 + Min(1.0f, freqModifier) * 949;
			} else {
				m_sQueueSample.m_nSampleIndex = SFX_HELI_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			}
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 6.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
	
	CVector backPropellerPos;
	if (automobile != nil)
		automobile->GetComponentWorldPosition(CAR_BOOT, backPropellerPos);
	else if (params.m_VehicleType == VEHICLE_TYPE_HELI) 
#ifdef FIX_BUGS
		backPropellerPos = 
#endif
		params.m_pVehicle->GetMatrix() * CVector(0.0f, -10.0f, 0.0f);
	else
		backPropellerPos = m_sQueueSample.m_vecPos;

	if (params.m_fDistance >= SQR(140.0f))
		return;

	if (propellerSpeed >= 0.4f)
		volumeModifier = (propellerSpeed - 0.4f) * 5.0f / 3.0f;
	else
		volumeModifier = 0.0f;
	if (!boat) {
		freq = Min(1300, 7000.0f * freqModifier);
		if (playerVeh == veh && (accelerateState > 0 || brakeState > 0) && freq < 1300)//unnesesary freqModifier alredy <= 1300
			freq = 1300;
		if (veh->m_modelIndex == MI_HUNTER)
			hunterBool = TRUE;
	}


	//sound from front of helicopter
	emittingVol = (1.0f - cameraAngle) * volumeModifier * 127.0f;
	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, 140.0f, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 3;
		if (hunterBool) {
			m_sQueueSample.m_nSampleIndex = SFX_HELI_APACHE_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nFrequency = (volumeModifier + 1.0f) * 16000 + freq;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 6.0f;
			m_sQueueSample.m_fSoundIntensity = 140.0f;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		} else if (boat != nil) {
			m_sQueueSample.m_nSampleIndex = SFX_SEAPLANE_PRO1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;

			if (accelerateState > 0 || brakeState > 0)
				m_sQueueSample.m_nFrequency = 18000 + Min(1.0f, freqModifier * (Max(accelerateState, brakeState) / 255.0f)) * 2204;
			else
				m_sQueueSample.m_nFrequency = 14287 + Min(1.0f, freqModifier) * 3713;
			if (propellerSpeed < 1.0f)
				m_sQueueSample.m_nFrequency = (propellerSpeed + 1.0f) * (m_sQueueSample.m_nFrequency / 2.0f);
			m_sQueueSample.m_nFrequency = Clamp2(m_sQueueSample.m_nFrequency, freqFrontPrev, 197);
			freqFrontPrev = m_sQueueSample.m_nFrequency;

			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 6.0f;
			m_sQueueSample.m_fSoundIntensity = 140.0f;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		} else {
			m_sQueueSample.m_nSampleIndex = SFX_CAR_HELI_MAI;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nFrequency = (volumeModifier + 1) * 16000 + freq;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 6.0f;
			m_sQueueSample.m_fSoundIntensity = 140.0f;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}


	//after accel rotor sound
	emittingVol = ((cameraAngle + 1.0f) * volumeModifier * 127.0f) / 2.0f;
	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, 140.0f, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 1;
		if (hunterBool) {
			m_sQueueSample.m_nSampleIndex = SFX_HELI_APACHE_2;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nFrequency = (volumeModifier + 1) * 16000 + freq;
		} else if (boat) {
			m_sQueueSample.m_nSampleIndex = SFX_SEAPLANE_PRO2;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;

			if (accelerateState > 0 || brakeState > 0)
				m_sQueueSample.m_nFrequency = 9000 + Min(1.0f, (Max(accelerateState, brakeState) / 255) * freqModifier) * 1102;
			else
				m_sQueueSample.m_nFrequency = 7143 + Min(1.0f, freqModifier) * 1857;

			if (propellerSpeed < 1.0f)
				m_sQueueSample.m_nFrequency = (propellerSpeed + 1) * (m_sQueueSample.m_nFrequency / 2);

			m_sQueueSample.m_nFrequency = Clamp2(m_sQueueSample.m_nFrequency, freqPropellerPrev, 98);
			freqPropellerPrev = m_sQueueSample.m_nFrequency;
		} else {
			m_sQueueSample.m_nSampleIndex = SFX_CAR_HELI_MAI2;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nFrequency = (volumeModifier + 1) * 16000 + freq;
		}
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = emittingVol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 6.0f;
		m_sQueueSample.m_fSoundIntensity = 140.0f;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 5;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}


	//engine starting sound 
	if (boat == nil && params.m_VehicleType != VEHICLE_TYPE_HELI && m_sQueueSample.m_fDistance < 30.0f) { //strange way to check if automobile != nil
		if (automobile->bEngineOn) {
			if (propellerSpeed < 1.0f) {
				emittingVol = (1.0f - propellerSpeed / 2.0f) * 70.0f;
				m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, 30.0f, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume) {
					if (hunterBool) {
						m_sQueueSample.m_nSampleIndex = SFX_HELI_APACHE_4;
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						freq = 3000.0f * propellerSpeed + 30000;
					} else {
						m_sQueueSample.m_nSampleIndex = SFX_CAR_HELI_STA;
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						freq = 3000.0f * propellerSpeed + 6000;
					}
					m_sQueueSample.m_nFrequency = freq;
					m_sQueueSample.m_nCounter = 12;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nReleasingVolumeModificator = 1;
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_nEmittingVolume = emittingVol;
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 6.0f;
					m_sQueueSample.m_fSoundIntensity = 30.0f;
					m_sQueueSample.m_bReleasingSoundFlag = FALSE;
					m_sQueueSample.m_nReleasingVolumeDivider = 30;
					m_sQueueSample.m_bReverbFlag = TRUE;
					m_sQueueSample.m_bRequireReflection = FALSE;
					AddSampleToRequestedQueue();
				}
			}
		}
	}


	if (boat) {
		if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_FIXED && m_sQueueSample.m_fDistance < 20.0f && propellerSpeed > 0.0f) {
			m_sQueueSample.m_nVolume = ComputeVolume(propellerSpeed * 100.0f, 20.0f, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume) {

				if (accelerateState > 0 || brakeState > 0)
					m_sQueueSample.m_nFrequency = 18000 + Min(1.0f, (Max(accelerateState, brakeState) / 255.0f) * freqModifier) * 2204;
				else
					m_sQueueSample.m_nFrequency = 14287 + Min(1.0f, freqModifier) * 3713;
				if (propellerSpeed < 1.0f)
					m_sQueueSample.m_nFrequency = (propellerSpeed + 1) * (m_sQueueSample.m_nFrequency / 2.0f);
				m_sQueueSample.m_nFrequency = Clamp2(m_sQueueSample.m_nFrequency, freqSkimmerPrev, 197);
				freqSkimmerPrev = m_sQueueSample.m_nFrequency;

				m_sQueueSample.m_nSampleIndex = SFX_SEAPLANE_PRO4;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = 12;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = propellerSpeed * 100.0f;
				SET_LOOP_OFFSETS(SFX_SEAPLANE_PRO4)
				m_sQueueSample.m_fSpeedMultiplier = 5.0f;
				m_sQueueSample.m_fSoundIntensity = 20.0f;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 7;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
	} else {
		//vacuum cleaner sound
		vecPosOld = m_sQueueSample.m_vecPos;
		distanceCalculatedOld = params.m_bDistanceCalculated;
		distanceOld = params.m_fDistance;

		m_sQueueSample.m_vecPos = backPropellerPos;
		params.m_bDistanceCalculated = FALSE;
		params.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (params.m_fDistance < SQR(27.0f)) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(volumeModifier * 25.0f, 27.0f, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume) {
				m_sQueueSample.m_nCounter = 2;
				m_sQueueSample.m_nSampleIndex = hunterBool ? SFX_HELI_APACHE_3 : SFX_CAR_HELI_REA;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 1;
				m_sQueueSample.m_nFrequency = (volumeModifier + 1.0f) * 16000;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = volumeModifier * 25.0f;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 6.0f;
				m_sQueueSample.m_fSoundIntensity = 27.0f;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 5;
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
		
		m_sQueueSample.m_vecPos = vecPosOld;
		params.m_bDistanceCalculated = distanceCalculatedOld;
		params.m_fDistance = distanceOld;
	}
}

void
cAudioManager::ProcessVehicleFlatTyre(cVehicleParams& params)
{
	const float SOUND_INTENSITY = 60.0f;

	CAutomobile* automobile;
	CBike* bike;
	bool8 wheelBurst;
	uint8 emittingVol;

	float modifier;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return;

	switch (params.m_VehicleType) {
	case VEHICLE_TYPE_CAR:
		automobile = (CAutomobile*)params.m_pVehicle;
		wheelBurst = FALSE;
		for (int i = 0; i < 4; i++)
			if (automobile->Damage.GetWheelStatus(i) == WHEEL_STATUS_BURST && automobile->m_aWheelTimer[i] > 0.0f)
				wheelBurst = TRUE;
		if (!wheelBurst)
			return;
		break;
	case VEHICLE_TYPE_BIKE:
		bike = (CBike*)params.m_pVehicle;
		wheelBurst = FALSE;
		for(int i = 0; i < 2; i++)
			if (bike->m_wheelStatus[i] == WHEEL_STATUS_BURST && bike->m_aWheelTimer[i] > 0.0f)
				wheelBurst = TRUE;
		if (!wheelBurst)
			return;
		break;
	default:
		return;
	}
	modifier = Min(1.0f, Abs(params.m_fVelocityChange) / (0.3f * params.m_pTransmission->fMaxVelocity));
	if (modifier > 0.01f) { //mb can be replaced by (emittingVol > 1)
		emittingVol = (100.0f * modifier);
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume) {
			m_sQueueSample.m_nCounter = 95;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_nSampleIndex = SFX_TYRE_BURST_L;
			m_sQueueSample.m_nFrequency = (5500.0f * modifier) + 8000;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			SET_LOOP_OFFSETS(SFX_TYRE_BURST_L)
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
}

//TODO use it in ProcessVehicle
void
cAudioManager::ProcessPlane(cVehicleParams& params)
{
	switch (params.m_nIndex) {
	case AIRTRAIN:
		ProcessJumbo(params);
		break;
	case DEADDODO:
		ProcessCesna(params);
		break;
	default:
		break;
	}
}

#pragma region JUMBO
uint8 gJumboVolOffsetPercentage;

void
DoJumboVolOffset()
{
	if (!(AudioManager.GetFrameCounter() % (AudioManager.GetRandomNumber(0) % 6 + 3)))
		gJumboVolOffsetPercentage = AudioManager.GetRandomNumber(1) % 60;
}

void
cAudioManager::ProcessJumbo(cVehicleParams& params)
{
	CPlane *plane;
	float position;

	 if (params.m_fDistance >= SQR(440))
		return;

	CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
	plane = (CPlane*)params.m_pVehicle;
	DoJumboVolOffset();
	position = PlanePathPosition[plane->m_nPlaneId];
	if (position <= TakeOffPoint) {
		if (plane->m_fSpeed > 0.103344f) {
			ProcessJumboAccel(plane);
		} else {
			ProcessJumboTaxi();
		}
	} else if (position <= TakeOffPoint + 300.0f) {
		ProcessJumboTakeOff(plane);
	} else if (position <= LandingPoint - 350.0f) {
		ProcessJumboFlying();
	} else if (position <= LandingPoint) {
		ProcessJumboLanding(plane);
	} else if (plane->m_fSpeed > 0.103344f) {
		ProcessJumboDecel(plane);
	} else {
		ProcessJumboTaxi();
	}
}

void
cAudioManager::ProcessJumboTaxi()
{
	if (SetupJumboFlySound(20)) {
		if (SetupJumboTaxiSound(75))
			SetupJumboWhineSound(18, 29500);
	}
}

void
cAudioManager::ProcessJumboAccel(CPlane *plane)
{
	int32 engineFreq;
	int32 vol;
	float modificator;
	float freqModifier;

	if (SetupJumboFlySound(20)) {
		modificator = Min(1.0f, (plane->m_fSpeed - 0.103344f) * 1.6760077f);
		if (SetupJumboRumbleSound(MAX_VOLUME * modificator) && SetupJumboTaxiSound((1.0f - modificator) * 75.f)) {
			if (modificator < 0.2f) {
				freqModifier = modificator * 5.0f;
				vol = MAX_VOLUME * freqModifier;
				engineFreq = 6050.0f * freqModifier + 16000;
			} else {
				freqModifier = 1.0f;
				engineFreq = 22050;
				vol = MAX_VOLUME;
			}
			SetupJumboEngineSound(vol, engineFreq);
			SetupJumboWhineSound(18, 14600.0f * freqModifier + 29500);
		}
	}
}

void
cAudioManager::ProcessJumboTakeOff(CPlane *plane)
{
	const float modificator = (PlanePathPosition[plane->m_nPlaneId] - TakeOffPoint) / 300.f;

	if (SetupJumboFlySound((107.f * modificator) + 20) && SetupJumboRumbleSound(MAX_VOLUME * (1.f - modificator))) {
		if (SetupJumboEngineSound(MAX_VOLUME, 22050))
			SetupJumboWhineSound(18.f * (1.f - modificator), 44100);
	}
}

void
cAudioManager::ProcessJumboFlying()
{
	if (SetupJumboFlySound(MAX_VOLUME))
		SetupJumboEngineSound(63, 22050);
}

void
cAudioManager::ProcessJumboLanding(CPlane *plane)
{
	const float modificator = (LandingPoint - PlanePathPosition[plane->m_nPlaneId]) / 350.f;
	if (SetupJumboFlySound(107.f * modificator + 20)) {
		if (SetupJumboTaxiSound(75.f * (1.f - modificator))) {
			SetupJumboEngineSound(MAX_VOLUME, 22050);
			SetupJumboWhineSound(18.f * (1.f - modificator), 14600.f * modificator + 29500);
		}
	}
}

void
cAudioManager::ProcessJumboDecel(CPlane *plane)
{
	if (SetupJumboFlySound(20) && SetupJumboTaxiSound(75)) {
		const float modificator = Min(1.f, (plane->m_fSpeed - 0.103344f) * 1.6760077f);
		SetupJumboEngineSound(MAX_VOLUME * modificator, 6050.f * modificator + 16000);
		SetupJumboWhineSound(18, 29500);
	}
}

bool8
cAudioManager::SetupJumboTaxiSound(uint8 vol)
{
	const float SOUND_INTENSITY = 180.0f;
	if (m_sQueueSample.m_fDistance >= SOUND_INTENSITY)
		return FALSE;

	uint8 emittingVol = (vol / 2) + ((vol / 2) * m_sQueueSample.m_fDistance / SOUND_INTENSITY);

	if (m_sQueueSample.m_fDistance / SOUND_INTENSITY < 0.7f)
		emittingVol -= emittingVol * gJumboVolOffsetPercentage / 100;
	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);

	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 1;
		m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nFrequency = GetJumboTaxiFreq();
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = emittingVol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 4;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
	return TRUE;
}

bool8
cAudioManager::SetupJumboWhineSound(uint8 emittingVol, uint32 freq)
{
	const float SOUND_INTENSITY = 170.0f;

	if (m_sQueueSample.m_fDistance >= SOUND_INTENSITY)
		return FALSE;

	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);

	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 2;
		m_sQueueSample.m_nSampleIndex = SFX_JUMBO_WHINE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nFrequency = freq;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = emittingVol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 4;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
	return TRUE;
}

bool8
cAudioManager::SetupJumboEngineSound(uint8 vol, uint32 freq)
{
	const float SOUND_INTENSITY = 180.0f;
	if (m_sQueueSample.m_fDistance >= SOUND_INTENSITY)
		return FALSE;

	uint8 emittingVol = vol - gJumboVolOffsetPercentage / 100;
	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 3;
		m_sQueueSample.m_nSampleIndex = SFX_JUMBO_ENGINE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nFrequency = freq;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = emittingVol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 4;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
	return TRUE;
}

bool8
cAudioManager::SetupJumboFlySound(uint8 emittingVol)
{
	const float SOUND_INTENSITY = 440.0f;
	if(m_sQueueSample.m_fDistance >= SOUND_INTENSITY) return FALSE;

	int32 vol = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
	m_sQueueSample.m_nVolume = vol;
	if(m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 0;
		m_sQueueSample.m_nSampleIndex = SFX_JUMBO_DIST_FLY;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_JUMBO_DIST_FLY);
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = emittingVol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 5;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE; // todo port fix to re3
		AddSampleToRequestedQueue();
	}
	return TRUE;
}

bool8
cAudioManager::SetupJumboRumbleSound(uint8 emittingVol)
{
	const float SOUND_INTENSITY = 240.0f;
	if (m_sQueueSample.m_fDistance >= SOUND_INTENSITY)
		return FALSE;

	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);

	if (m_sQueueSample.m_nVolume != 0) {
		m_sQueueSample.m_nCounter = 5;
		m_sQueueSample.m_nSampleIndex = SFX_JUMBO_RUMBLE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_JUMBO_RUMBLE);
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_nEmittingVolume = emittingVol;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 12;
		m_sQueueSample.m_nOffset = 0;
		m_sQueueSample.m_bReverbFlag = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
		m_sQueueSample.m_nCounter = 6;
		m_sQueueSample.m_nSampleIndex = SFX_JUMBO_RUMBLE;
		m_sQueueSample.m_nFrequency += 200;
		m_sQueueSample.m_nOffset = MAX_VOLUME;
		AddSampleToRequestedQueue();
	}
	return TRUE;
}

int32
cAudioManager::GetJumboTaxiFreq() const
{
	return (1.f / 180 * 10950 * m_sQueueSample.m_fDistance) + 22050; // todo port fix to re3
}

#pragma endregion Some jumbo crap

#pragma endregion All the vehicle audio code

#pragma region PED AUDIO
void
cAudioManager::ProcessPed(CPhysical *ped)
{
	cPedParams params;

	m_sQueueSample.m_vecPos = ped->GetPosition();

	params.m_bDistanceCalculated = FALSE;
	params.m_pPed = (CPed *)ped;
	params.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
	ProcessPedOneShots(params);
}

void
cAudioManager::ProcessPedOneShots(cPedParams &params)
{
	uint8 emittingVol;
	int32 sampleIndex;

	CPed *ped = params.m_pPed;

	bool8 narrowSoundRange;
	int16 sound;
	bool8 stereo;
	CWeapon *weapon;
	float maxDist = 0.f; // uninitialized variable

	static uint8 iSound = 21;
	static uint32 iSplashFrame = 0;

	weapon = params.m_pPed->GetWeapon();
	for (uint32 i = 0; i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; i++) {
		stereo = FALSE;
		narrowSoundRange = FALSE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		sound = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i];
		switch (sound) {
		case SOUND_STEP_START:
		case SOUND_STEP_END:
			if (params.m_pPed->bIsInTheAir)
				continue;
			emittingVol = m_anRandomTable[3] % 15 + 45;
			if (FindPlayerPed() != m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity)
				emittingVol /= 2;
			maxDist = 400.f;
			switch (params.m_pPed->m_nSurfaceTouched) {
			case SURFACE_GRASS:
				sampleIndex = m_anRandomTable[1] % 5 + SFX_FOOTSTEP_GRASS_1;
				break;
			case SURFACE_GRAVEL:
			case SURFACE_MUD_DRY:
				sampleIndex = m_anRandomTable[4] % 5 + SFX_FOOTSTEP_GRAVEL_1;
				break;
			case SURFACE_CAR:
			case SURFACE_GARAGE_DOOR:
			case SURFACE_CAR_PANEL:
			case SURFACE_THICK_METAL_PLATE:
			case SURFACE_SCAFFOLD_POLE:
			case SURFACE_LAMP_POST:
			case SURFACE_FIRE_HYDRANT:
			case SURFACE_GIRDER:
			case SURFACE_METAL_CHAIN_FENCE:
			case SURFACE_CONTAINER:
			case SURFACE_NEWS_VENDOR:
				sampleIndex = m_anRandomTable[0] % 5 + SFX_FOOTSTEP_METAL_1;
				break;
			case SURFACE_SAND:
				sampleIndex = (m_anRandomTable[4] & 3) + SFX_FOOTSTEP_SAND_1;
				break;
			case SURFACE_WATER:
				sampleIndex = (m_anRandomTable[3] & 3) + SFX_FOOTSTEP_WATER_1;
				break;
			case SURFACE_WOOD_CRATES:
			case SURFACE_WOOD_BENCH:
			case SURFACE_WOOD_SOLID:
				sampleIndex = m_anRandomTable[2] % 5 + SFX_FOOTSTEP_WOOD_1;
				break;
			case SURFACE_HEDGE:
				sampleIndex = m_anRandomTable[2] % 5 + SFX_COL_VEG_1;
				break;
			default:
				sampleIndex = m_anRandomTable[2] % 5 + SFX_FOOTSTEP_CONCRETE_1;
				break;
			}
			m_sQueueSample.m_nSampleIndex = sampleIndex;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] - SOUND_STEP_START + 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 17);
			switch (params.m_pPed->m_nMoveState) {
			case PEDMOVE_WALK:
				emittingVol /= 4;
				m_sQueueSample.m_nFrequency = 9 * m_sQueueSample.m_nFrequency / 10;
				break;
			case PEDMOVE_RUN:
				emittingVol /= 2;
				m_sQueueSample.m_nFrequency = 11 * m_sQueueSample.m_nFrequency / 10;
				break;
			case PEDMOVE_SPRINT:
				m_sQueueSample.m_nFrequency = 12 * m_sQueueSample.m_nFrequency / 10;
				break;
			default:
				break;
			}
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 20.0f;
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		case SOUND_FALL_LAND:
		case SOUND_FALL_COLLAPSE:
			if (ped->bIsInTheAir)
				continue;
			maxDist = SQR(30);
			emittingVol = m_anRandomTable[3] % 20 + 80;
			if (ped->m_nSurfaceTouched == SURFACE_WATER) {
				m_sQueueSample.m_nSampleIndex = (m_anRandomTable[3] & 3) + SFX_FOOTSTEP_WATER_1;
			} else if (sound == SOUND_FALL_LAND) {
				m_sQueueSample.m_nSampleIndex = SFX_BODY_LAND;
			} else {
				m_sQueueSample.m_nSampleIndex = SFX_BODY_LAND_AND_FALL;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 17);
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		case SOUND_FIGHT_37:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_1;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_38:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_1;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_39:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_1;
			m_sQueueSample.m_nFrequency = 20000;
			goto AddFightSound;
		case SOUND_FIGHT_40:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_2;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_41:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_2;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_42:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_2;
			m_sQueueSample.m_nFrequency = 20000;
			goto AddFightSound;
		case SOUND_FIGHT_43:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_4;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_44:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_4;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_45:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_4;
			m_sQueueSample.m_nFrequency = 20000;
			goto AddFightSound;
		case SOUND_FIGHT_46:
		case SOUND_187:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_5;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_47:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_5;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_48:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_5;
			m_sQueueSample.m_nFrequency = 20000;
		AddFightSound:
			{
				uint32 soundParams = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]; // wtf? storing int as float
				uint8 damagerType = soundParams & 0xFF;
				uint32 weaponType = soundParams >> 8;

				if (damagerType == ENTITY_TYPE_PED) {
					if (weaponType == WEAPONTYPE_BRASSKNUCKLE) {
						CPed* ped = params.m_pPed;
						uint32 fightMove = ped->m_curFightMove;
						if (fightMove == FIGHTMOVE_BACKLEFT || fightMove == FIGHTMOVE_STDPUNCH || fightMove == FIGHTMOVE_PUNCH ||
							ped->m_nPedState == PED_ATTACK) {
							CEntity* damageEntity = ped->m_pDamageEntity;
							if (!damageEntity)
								m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 2 + SFX_HAMMER_HIT_1;
							else if (damageEntity->GetType() != ENTITY_TYPE_PED)
								m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 2 + SFX_HAMMER_HIT_1;
							else if (((CPed*)damageEntity)->m_curFightMove != FIGHTMOVE_HITHEAD)
								m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 2 + SFX_HAMMER_HIT_1;
							else
								m_sQueueSample.m_nSampleIndex = SFX_HAMMER_HIT_1;
						}
					}
				}
				else {
					m_sQueueSample.m_nSampleIndex = m_anRandomTable[4] % 6 + SFX_COL_CAR_PANEL_1;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
					m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
				}
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound;
			narrowSoundRange = TRUE;
			++iSound;
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			maxDist = SQR(30);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = m_anRandomTable[3] % 26 + 100;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		case SOUND_WEAPON_BAT_ATTACK:
		case SOUND_WEAPON_KNIFE_ATTACK:
		{
			uint32 soundParams = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]; // wtf? storing int as float
			uint8 damagerType = soundParams & 0xFF;
			uint32 weaponType = soundParams >> 8;
			if (damagerType == ENTITY_TYPE_PED) {
				switch (weaponType) {
				case WEAPONTYPE_SCREWDRIVER:
				case WEAPONTYPE_KNIFE:
				case WEAPONTYPE_CLEAVER:
				case WEAPONTYPE_MACHETE:
				case WEAPONTYPE_KATANA:
					if (sound == SOUND_WEAPON_KNIFE_ATTACK)
						m_sQueueSample.m_nSampleIndex = SFX_KNIFE_SLASH;
					else
						m_sQueueSample.m_nSampleIndex = SFX_KNIFE_STAB;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
					m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
					break;
				case WEAPONTYPE_HAMMER:
					m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 2 + SFX_HAMMER_HIT_1;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
					m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
					break;
				default:
					m_sQueueSample.m_nSampleIndex = SFX_BAT_HIT_LEFT;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_nFrequency = RandomDisplacement(2000) + 22000;
					stereo = TRUE;
					break;
				}
			}
			else {
				m_sQueueSample.m_nSampleIndex = m_anRandomTable[4] % 6 + SFX_COL_CAR_PANEL_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
			}
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			maxDist = SQR(30);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = m_anRandomTable[2] % 20 + 100;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_WEAPON_CHAINSAW_IDLE:
			if (FindVehicleOfPlayer())
				continue;
			m_sQueueSample.m_nSampleIndex = SFX_CAR_CHAINSAW_IDLE;
#ifdef GTA_PS2
			m_sQueueSample.m_nBankIndex = SFX_BANK_CAR_CHAINSAW;
#else
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#endif
			m_sQueueSample.m_nCounter = 70;
			m_sQueueSample.m_nFrequency = 27000;
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = 50.0f;
			maxDist = SQR(50);
			m_sQueueSample.m_nLoopCount = 0;
			emittingVol = 100;
			SET_LOOP_OFFSETS(SFX_CAR_CHAINSAW_IDLE)
			m_sQueueSample.m_nEmittingVolume = 100;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			break;
		case SOUND_WEAPON_CHAINSAW_ATTACK:
			if (FindVehicleOfPlayer())
				continue;
			m_sQueueSample.m_nSampleIndex = SFX_CAR_CHAINSAW_ATTACK;
#ifdef GTA_PS2
			m_sQueueSample.m_nBankIndex = SFX_BANK_CAR_CHAINSAW;
#else
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#endif
			m_sQueueSample.m_nCounter = 68;
			m_sQueueSample.m_nFrequency = 27000;
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = 60.0f;
			maxDist = SQR(60);
			m_sQueueSample.m_nLoopCount = 0;
			emittingVol = 100;
			SET_LOOP_OFFSETS(SFX_CAR_CHAINSAW_ATTACK)
			m_sQueueSample.m_nEmittingVolume = 100;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			break;
		case SOUND_WEAPON_CHAINSAW_MADECONTACT:
			if (FindVehicleOfPlayer())
				continue;
			if ((int32)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] != ENTITY_TYPE_PED)
				ReportCollision(params.m_pPed, params.m_pPed, SURFACE_CAR, SURFACE_TARMAC, 0.0f, 0.09f);
			m_sQueueSample.m_nSampleIndex = SFX_CAR_CHAINSAW_ATTACK;
#ifdef GTA_PS2
			m_sQueueSample.m_nBankIndex = SFX_BANK_CAR_CHAINSAW;
#else
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#endif
			m_sQueueSample.m_nCounter = 68;
			m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 22000;
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = 60.0f;
			maxDist = SQR(60);
			m_sQueueSample.m_nLoopCount = 0;
			emittingVol = 100;
			SET_LOOP_OFFSETS(SFX_CAR_CHAINSAW_ATTACK)
			m_sQueueSample.m_nEmittingVolume = 100;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 5;
			break;
		case SOUND_WEAPON_SHOT_FIRED:
			weapon = ped->GetWeapon();
			if (!weapon)
				continue;
			switch (weapon->m_eWeaponType) {
			case WEAPONTYPE_ROCKET:
			case WEAPONTYPE_ROCKETLAUNCHER:
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ROCKET_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 1;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[0] % 20 + 80;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_COLT45:
				m_sQueueSample.m_nSampleIndex = SFX_COLT45_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_COLT45_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[1] % 10 + 90;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_PYTHON:
				m_sQueueSample.m_nSampleIndex = SFX_PYTHON_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PYTHON_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = 127;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_SHOTGUN:
			case WEAPONTYPE_STUBBY_SHOTGUN:
				m_sQueueSample.m_nSampleIndex = SFX_SHOTGUN_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SHOTGUN_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[2] % 10 + 100;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_SPAS12_SHOTGUN:
				m_sQueueSample.m_nSampleIndex = SFX_SPAS12_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SPAS12_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[2] % 10 + 100;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_TEC9:
				m_sQueueSample.m_nSampleIndex = SFX_TEC_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 17000;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[3] % 15 + 70;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_UZI:
			case WEAPONTYPE_MINIGUN:
				m_sQueueSample.m_nSampleIndex = SFX_UZI_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_UZI_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[3] % 15 + 70;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_SILENCED_INGRAM:
				m_sQueueSample.m_nSampleIndex = SFX_TEC_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 34000;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[3] % 15 + 70;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_MP5:
				m_sQueueSample.m_nSampleIndex = SFX_MP5_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_MP5_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[3] % 15 + 70;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_M4:
				m_sQueueSample.m_nSampleIndex = SFX_RUGER_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 43150;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[3] % 15 + 90;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_RUGER:
				m_sQueueSample.m_nSampleIndex = SFX_RUGER_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RUGER_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[3] % 15 + 90;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_SNIPERRIFLE:
			case WEAPONTYPE_LASERSCOPE:
				m_sQueueSample.m_nSampleIndex = SFX_SNIPER_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				if (weapon->m_eWeaponType == WEAPONTYPE_SNIPERRIFLE)
					m_sQueueSample.m_nFrequency = 25472;
				else
					m_sQueueSample.m_nFrequency = 20182;
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = m_anRandomTable[4] % 10 + 110;
				m_sQueueSample.m_nEmittingVolume = emittingVol;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				m_sQueueSample.m_bRequireReflection = TRUE;
				stereo = TRUE;
				break;
			case WEAPONTYPE_FLAMETHROWER:
				m_sQueueSample.m_nSampleIndex = SFX_FLAMETHROWER_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = 9;
				emittingVol = 90;
				m_sQueueSample.m_nFrequency = (10 * m_sQueueSample.m_nEntityIndex & 2047) + SampleManager.GetSampleBaseFrequency(SFX_FLAMETHROWER_LEFT);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 4.0f;
				m_sQueueSample.m_fSoundIntensity = 60.0f;
				maxDist = SQR(60);
				m_sQueueSample.m_nLoopCount = 0;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_nEmittingVolume = 90;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 6;
				stereo = TRUE;
				break;
			case WEAPONTYPE_M60:
			case WEAPONTYPE_HELICANNON:
				m_sQueueSample.m_nSampleIndex = SFX_M60_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_M60_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_fSoundIntensity = 120.0f;
				maxDist = SQR(120);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				emittingVol = 127;
				m_sQueueSample.m_nEmittingVolume = 127;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				stereo = TRUE;
				break;
			default:
				continue;
			}
			break;
		case SOUND_WEAPON_RELOAD:
			switch ((int32)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]) {
			case WEAPONTYPE_ROCKET:
			case WEAPONTYPE_ROCKETLAUNCHER:
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ROCKET_RELOAD);
				break;
			case WEAPONTYPE_COLT45:
			case WEAPONTYPE_PYTHON:
				m_sQueueSample.m_nSampleIndex = SFX_PISTOL_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PISTOL_RELOAD) + RandomDisplacement(300);
				break;
			case WEAPONTYPE_SHOTGUN:
			case WEAPONTYPE_SPAS12_SHOTGUN:
			case WEAPONTYPE_STUBBY_SHOTGUN:
			case WEAPONTYPE_RUGER:
				m_sQueueSample.m_nSampleIndex = SFX_AK47_RELOAD;
				m_sQueueSample.m_nFrequency = 30290;
				break;
			case WEAPONTYPE_TEC9:
			case WEAPONTYPE_UZI:
			case WEAPONTYPE_SILENCED_INGRAM:
			case WEAPONTYPE_MP5:
			case WEAPONTYPE_M4:
			case WEAPONTYPE_M60:
			case WEAPONTYPE_HELICANNON:
				m_sQueueSample.m_nSampleIndex = SFX_AK47_RELOAD;
				m_sQueueSample.m_nFrequency = 39243;
				break;
			case WEAPONTYPE_SNIPERRIFLE:
			case WEAPONTYPE_LASERSCOPE:
				m_sQueueSample.m_nSampleIndex = SFX_RIFLE_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RIFLE_RELOAD);
				break;
			default:
				continue;
			}
			emittingVol = 75;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency += RandomDisplacement(300);
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nReleasingVolumeModificator = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			maxDist = SQR(30);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_nEmittingVolume = 75;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		case SOUND_WEAPON_AK47_BULLET_ECHO:
		{
			uint32 weaponType = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			switch (weaponType) {
			case WEAPONTYPE_SPAS12_SHOTGUN:
				m_sQueueSample.m_nSampleIndex = SFX_SPAS12_TAIL_LEFT;
				break;
			case WEAPONTYPE_TEC9:
			case WEAPONTYPE_SILENCED_INGRAM:
				m_sQueueSample.m_nSampleIndex = SFX_TEC_TAIL;
				break;
			case WEAPONTYPE_UZI:
			case WEAPONTYPE_MP5:
				m_sQueueSample.m_nSampleIndex = SFX_UZI_END_LEFT;
				break;
			case WEAPONTYPE_M4:
			case WEAPONTYPE_RUGER:
			case WEAPONTYPE_SNIPERRIFLE:
			case WEAPONTYPE_LASERSCOPE:
				m_sQueueSample.m_nSampleIndex = SFX_RUGER_TAIL;
				break;
			case WEAPONTYPE_M60:
			case WEAPONTYPE_HELICANNON:
				m_sQueueSample.m_nSampleIndex = SFX_M60_TAIL_LEFT;
				break;
			default:
				continue;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			switch (weaponType) {
			case WEAPONTYPE_TEC9:
				m_sQueueSample.m_nFrequency = 13000;
				break;
			case WEAPONTYPE_SILENCED_INGRAM:
				m_sQueueSample.m_nFrequency = 26000;
				break;
			case WEAPONTYPE_M4:
				m_sQueueSample.m_nFrequency = 15600;
				break;
			case WEAPONTYPE_SNIPERRIFLE:
				m_sQueueSample.m_nFrequency = 9959;
				break;
			case WEAPONTYPE_LASERSCOPE:
				m_sQueueSample.m_nFrequency = 7904;
				break;
			default:
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				break;
			}
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 120.0f;
			maxDist = SQR(120);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = m_anRandomTable[4] % 10 + 80;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_WEAPON_FLAMETHROWER_FIRE:
			m_sQueueSample.m_nSampleIndex = SFX_FLAMETHROWER_START_LEFT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_FLAMETHROWER_START_LEFT);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_fSoundIntensity = 60.0f;
			maxDist = SQR(60);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = 70;
			m_sQueueSample.m_nEmittingVolume = 70;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			break;
		case SOUND_WEAPON_HIT_PED:
			m_sQueueSample.m_nSampleIndex = SFX_BULLET_PED;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BULLET_PED);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 8);
			m_sQueueSample.m_nReleasingVolumeModificator = 7;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			maxDist = SQR(30);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = m_anRandomTable[0] % 20 + 90;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			break;
		case SOUND_SPLASH:
			if (m_FrameCounter <= iSplashFrame)
				continue;
			iSplashFrame = m_FrameCounter + 6;
			m_sQueueSample.m_nSampleIndex = SFX_SPLASH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1400) + 20000;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 40.0f;
			maxDist = SQR(40);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = m_anRandomTable[2] % 30 + 70;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		case SOUND_MELEE_ATTACK_START:
		{
			uint32 weaponType = ((uint32)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]) >> 8;
			switch (weaponType)
			{
			case WEAPONTYPE_SCREWDRIVER:
			case WEAPONTYPE_KNIFE:
			case WEAPONTYPE_CLEAVER:
			case WEAPONTYPE_MACHETE:
			case WEAPONTYPE_KATANA:
				m_sQueueSample.m_nSampleIndex = SFX_KNIFE_SWING;
				break;
			default:
				m_sQueueSample.m_nSampleIndex = SFX_GOLF_CLUB_SWING;
				break;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
			m_sQueueSample.m_nReleasingVolumeModificator = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 30.0f;
			if (weaponType == WEAPONTYPE_UNARMED || weaponType == WEAPONTYPE_BRASSKNUCKLE)
				emittingVol = m_anRandomTable[1] % 10 + 35;
			else
				emittingVol = m_anRandomTable[2] % 20 + 70;
			maxDist = SQR(30);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_SKATING:
		{
			uint32 soundParams = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			uint8 param1 = soundParams & 0xFF;
			uint32 param2 = soundParams >> 8;
			m_sQueueSample.m_nSampleIndex = (m_anRandomTable[3] & 1) + SFX_SKATE_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound;
			stereo = TRUE;
			++iSound;
			m_sQueueSample.m_nFrequency = m_anRandomTable[1] % 1000 + 17000;
			if (param2 == 0)
				m_sQueueSample.m_nFrequency = (3 * m_sQueueSample.m_nFrequency) / 4;
			m_sQueueSample.m_nReleasingVolumeModificator = 6;
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = 20.0f;
			maxDist = SQR(20);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = (m_anRandomTable[2] % 20 + 70) * param1 / 127;
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		}
		case SOUND_WEAPON_MINIGUN_ATTACK:
			m_sQueueSample.m_nSampleIndex = SFX_MINIGUN_FIRE_LEFT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 68;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_MINIGUN_FIRE_LEFT);
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = 150.0f;
			emittingVol = 127;
			maxDist = SQR(150);
			m_sQueueSample.m_nLoopCount = 0;
			SET_LOOP_OFFSETS(SFX_MINIGUN_FIRE_LEFT)
			m_sQueueSample.m_nEmittingVolume = 127;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			break;
		case SOUND_WEAPON_MINIGUN_2:
			m_sQueueSample.m_nSampleIndex = SFX_MINIGUN_FIRE_RIGHT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 69;
			m_sQueueSample.m_nFrequency = 18569;
			m_sQueueSample.m_nReleasingVolumeModificator = 2;
			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
			m_sQueueSample.m_fSoundIntensity = 150.0f;
			emittingVol = 127.0f * m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			maxDist = SQR(150);
			m_sQueueSample.m_nLoopCount = 0;
			SET_LOOP_OFFSETS(SFX_MINIGUN_FIRE_RIGHT)
			m_sQueueSample.m_nEmittingVolume = emittingVol;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			break;
		case SOUND_WEAPON_MINIGUN_3:
			m_sQueueSample.m_nSampleIndex = SFX_MINIGUN_STOP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 69;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_MINIGUN_STOP);
			m_sQueueSample.m_nReleasingVolumeModificator = 4;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_fSoundIntensity = 150.0f;
			maxDist = SQR(150);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			emittingVol = 127;
			m_sQueueSample.m_nEmittingVolume = 127;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bRequireReflection = TRUE;
			break;
		case SOUND_SHIRT_WIND_FLAP:
			if (params.m_pPed->IsPlayer() && params.m_pPed->m_pMyVehicle) {
				if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] > 0.0f) {
					if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] > 1.0f)
						m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] = 1.0f;

					emittingVol = 90.0f * m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];

					switch (params.m_pPed->m_pMyVehicle->GetModelIndex())
					{
					case MI_ANGEL:
					case MI_FREEWAY:
						m_sQueueSample.m_nSampleIndex = SFX_CAR_WIND_17;
						break;
					case MI_PIZZABOY:
					case MI_FAGGIO:
						m_sQueueSample.m_nSampleIndex = SFX_CAR_WIND_18;
						break;
					case MI_PCJ600:
						m_sQueueSample.m_nSampleIndex = SFX_CAR_WIND_20;
						break;
					case MI_SANCHEZ:
						m_sQueueSample.m_nSampleIndex = SFX_CAR_WIND_19;
						break;
					default:
						continue;
					};

					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_nCounter = 71;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
					m_sQueueSample.m_nReleasingVolumeModificator = 3;
					m_sQueueSample.m_fSpeedMultiplier = 3.0f;
					m_sQueueSample.m_fSoundIntensity = 15.0f;
					maxDist = SQR(15);
					m_sQueueSample.m_nLoopCount = 0;
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_nEmittingVolume = emittingVol;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_bReleasingSoundFlag = FALSE;
					m_sQueueSample.m_nReleasingVolumeDivider = 3;
				}
			}
			continue;
		default:
			SetupPedComments(params, sound);
			continue;
		}

		if (narrowSoundRange && iSound > 60)
			iSound = 21;
		if (params.m_fDistance < maxDist) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				if (stereo) {
					if (m_sQueueSample.m_fDistance < 0.2f * m_sQueueSample.m_fSoundIntensity) {
						m_sQueueSample.m_bIs2D = TRUE;
						m_sQueueSample.m_nOffset = 0;
					} else {
						stereo = FALSE;
					}
				}
				m_sQueueSample.m_bReverbFlag = TRUE;
				AddSampleToRequestedQueue();
				if (stereo) {
					m_sQueueSample.m_nOffset = 127;
					++m_sQueueSample.m_nSampleIndex;
					if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] != SOUND_WEAPON_SHOT_FIRED ||
					    weapon->m_eWeaponType != WEAPONTYPE_FLAMETHROWER) {
						m_sQueueSample.m_nCounter = iSound++;
						if (iSound > 60)
							iSound = 21;
					} else {
						++m_sQueueSample.m_nCounter;
					}
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::SetPedTalkingStatus(CPed *ped, bool8 status)
{
	if (ped != nil)
		ped->m_canTalk = status;
}

void
cAudioManager::SetPlayersMood(uint8 mood, uint32 time)
{
	if (!m_bIsInitialised) return;

	if (mood < MAX_PLAYER_MOODS) {
		m_nPlayerMood = mood;
		m_nPlayerMoodTimer = CTimer::GetTimeInMilliseconds() + time;
	}

}

void
cAudioManager::SetupPedComments(cPedParams &params, uint16 sound)
{
	CPed *ped = params.m_pPed;
	uint8 emittingVol;
	float soundIntensity;
	tPedComment pedComment;

	if(ped != nil) {
		if(!ped->m_canTalk) return;
		m_bGenericSfx = FALSE;
		pedComment.m_nSampleIndex = GetPedCommentSfx(ped, sound);
		if(pedComment.m_nSampleIndex == NO_SAMPLE) return;
		soundIntensity = 40.0f;
	} else {
		m_bGenericSfx = TRUE;
		switch(sound) {
		case SOUND_PED_HELI_PLAYER_FOUND:
			soundIntensity = 400.0f;
			pedComment.m_nSampleIndex = GetRandomNumberInRange(m_sQueueSample.m_nEntityIndex % 4, SFX_POLICE_HELI_1, SFX_POLICE_HELI_20);
			break;
		case SOUND_PED_VCPA_PLAYER_FOUND:
			soundIntensity = 400.0f;
#ifdef FIX_BUGS
			pedComment.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % 4] % 23 + SFX_POLICE_BOAT_1;
#else
			pedComment.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % 4] % 29 + SFX_POLICE_BOAT_1;
#endif
			break;
		case SOUND_INJURED_PED_MALE_OUCH:
			soundIntensity = 40.0f;
			pedComment.m_nSampleIndex = GetRandomNumberInRange(m_sQueueSample.m_nEntityIndex % 4, SFX_GENERIC_MALE_GRUNT_1, SFX_GENERIC_MALE_GRUNT_41);
			break;
		case SOUND_INJURED_PED_FEMALE:
			soundIntensity = 40.0f;
			pedComment.m_nSampleIndex = GetRandomNumberInRange(m_sQueueSample.m_nEntityIndex % 4, SFX_GENERIC_FEMALE_GRUNT_1, SFX_GENERIC_FEMALE_GRUNT_33);
			break;
		default:
			return;
		}
	}

	if(params.m_fDistance < SQR(soundIntensity)) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		if(CWorld::GetIsLineOfSightClear(TheCamera.GetPosition(), m_sQueueSample.m_vecPos, true, false, false, false, false, false))
			emittingVol = MAX_VOLUME;
		else
			emittingVol = 31;
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, soundIntensity, m_sQueueSample.m_fDistance);
		pedComment.m_nProcess = 10;
		if(m_sQueueSample.m_nVolume != 0) {
			pedComment.m_nEntityIndex = m_sQueueSample.m_nEntityIndex;
			pedComment.m_vecPos = m_sQueueSample.m_vecPos;
			pedComment.m_fDistance = m_sQueueSample.m_fDistance;
			pedComment.m_bVolume = m_sQueueSample.m_nVolume;
			m_sPedComments.Add(&pedComment);
		}
	}
}

uint32
cAudioManager::GetPedCommentSfx(CPed *ped, int32 sound)
{
	if(ped->m_nPedState != PED_FALL || sound == MI_VICE8 || sound == MI_WFYG1 || sound == MI_WFYG2) {
		if(ped->m_getUpTimer == UINT32_MAX || ped->m_getUpTimer > CTimer::GetTimeInMilliseconds()) {
			if(sound != SOUND_PED_DAMAGE && sound != SOUND_PED_HIT && sound != SOUND_PED_LAND) return NO_SAMPLE;
		}
		if(ped->IsPlayer()) return GetPlayerTalkSfx(ped, sound);
		switch(ped->GetModelIndex()) {
		case MI_PLAYER: return GetPlayerTalkSfx(ped, sound);
		case MI_COP: return GetCopTalkSfx(ped, sound);
		case MI_SWAT: return GetSwatTalkSfx(ped, sound);
		case MI_FBI: return GetFBITalkSfx(ped, sound);
		case MI_ARMY: return GetGenericMaleTalkSfx(ped, sound);
		case MI_MEDIC: return GetMedicTalkSfx(ped, sound);
		case MI_FIREMAN: return GetFiremanTalkSfx(ped, sound);
		case MI_MALE01: return GetDefaultTalkSfx(ped, sound);
		case MI_HFYST: return GetHFYSTTalkSfx(ped, sound);
		case MI_HFOST: return GetHFOSTTalkSfx(ped, sound);
		case MI_HMYST: return GetHMYSTTalkSfx(ped, sound);
		case MI_HMOST: return GetHMOSTTalkSfx(ped, sound);
		case MI_HFYRI: return GetHFYRITalkSfx(ped, sound);
		case MI_HFORI: return GetHFORITalkSfx(ped, sound);
		case MI_HMYRI: return GetHMYRITalkSfx(ped, sound);
		case MI_HMORI: return GetHMORITalkSfx(ped, sound);
		case MI_HFYBE: return GetHFYBETalkSfx(ped, sound);
		case MI_HFOBE: return GetHFOBETalkSfx(ped, sound);
		case MI_HMYBE: return GetHMYBETalkSfx(ped, sound);
		case MI_HMOBE: return GetHMOBETalkSfx(ped, sound);
		case MI_HFYBU: return GetHFYBUTalkSfx(ped, sound);
		case MI_HFYMD: return GetHFYMDTalkSfx(ped, sound);
		case MI_HFYCG: return GetHFYCGTalkSfx(ped, sound);
		case MI_HFYPR: return GetHFYPRTalkSfx(ped, sound);
		case MI_HFOTR: return GetHFOTRTalkSfx(ped, sound);
		case MI_HMOTR: return GetHMOTRTalkSfx(ped, sound);
		case MI_HMYAP: return GetHMYAPTalkSfx(ped, sound);
		case MI_HMOCA: return GetHMOCATalkSfx(ped, sound);
		case MI_BMODK: return GetBMODKTalkSfx(ped, sound);
		case MI_BMYKR: return GetBMYCRTalkSfx(ped, sound);
		case MI_BFYST: return GetBFYSTTalkSfx(ped, sound);
		case MI_BFOST: return GetBFOSTTalkSfx(ped, sound);
		case MI_BMYST: return GetBMYSTTalkSfx(ped, sound);
		case MI_BMOST: return GetBMOSTTalkSfx(ped, sound);
		case MI_BFYRI: return GetBFYRITalkSfx(ped, sound);
		case MI_BFORI: return GetBFORITalkSfx(ped, sound);
		case MI_BMYRI: return GetBMYRITalkSfx(ped, sound);
		case MI_BFYBE: return GetBFYBETalkSfx(ped, sound);
		case MI_BMYBE: return GetBMYBETalkSfx(ped, sound);
		case MI_BFOBE: return GetBFOBETalkSfx(ped, sound);
		case MI_BMOBE: return GetBMOBETalkSfx(ped, sound);
		case MI_BMYBU: return GetBMYBUTalkSfx(ped, sound);
		case MI_BFYPR: return GetBFYPRTalkSfx(ped, sound);
		case MI_BFOTR: return GetBFOTRTalkSfx(ped, sound);
		case MI_BMOTR: return GetBMOTRTalkSfx(ped, sound);
		case MI_BMYPI: return GetBMYPITalkSfx(ped, sound);
		case MI_BMYBB: return GetBMYBBTalkSfx(ped, sound);
		case MI_WMYCR: return GetWMYCRTalkSfx(ped, sound);
		case MI_WFYST: return GetWFYSTTalkSfx(ped, sound);
		case MI_WFOST: return GetWFOSTTalkSfx(ped, sound);
		case MI_WMYST: return GetWMYSTTalkSfx(ped, sound);
		case MI_WMOST: return GetWMOSTTalkSfx(ped, sound);
		case MI_WFYRI: return GetWFYRITalkSfx(ped, sound);
		case MI_WFORI: return GetWFORITalkSfx(ped, sound);
		case MI_WMYRI: return GetWMYRITalkSfx(ped, sound);
		case MI_WMORI: return GetWMORITalkSfx(ped, sound);
		case MI_WFYBE: return GetWFYBETalkSfx(ped, sound);
		case MI_WMYBE: return GetWMYBETalkSfx(ped, sound);
		case MI_WFOBE: return GetWFOBETalkSfx(ped, sound);
		case MI_WMOBE: return GetWMOBETalkSfx(ped, sound);
		case MI_WMYCW: return GetWMYCWTalkSfx(ped, sound);
		case MI_WMYGO: return GetWMYGOTalkSfx(ped, sound);
		case MI_WFOGO: return GetWFOGOTalkSfx(ped, sound);
		case MI_WMOGO: return GetWMOGOTalkSfx(ped, sound);
		case MI_WFYLG: return GetWFYLGTalkSfx(ped, sound);
		case MI_WMYLG: return GetWMYLGTalkSfx(ped, sound);
		case MI_WFYBU: return GetWFYBUTalkSfx(ped, sound);
		case MI_WMYBU: return GetWMYBUTalkSfx(ped, sound);
		case MI_WMOBU: return GetWMOBUTalkSfx(ped, sound);
		case MI_WFYPR: return GetWFYPRTalkSfx(ped, sound);
		case MI_WFOTR: return GetWFOTRTalkSfx(ped, sound);
		case MI_WMOTR: return GetWMOTRTalkSfx(ped, sound);
		case MI_WMYPI: return GetWMYPITalkSfx(ped, sound);
		case MI_WMOCA: return GetWMOCATalkSfx(ped, sound);
		case MI_WFYJG: return GetWFYJGTalkSfx(ped, sound);
		case MI_WMYJG: return GetWMYJGTalkSfx(ped, sound);
		case MI_WFYSK: return GetWFYSKTalkSfx(ped, sound);
		case MI_WMYSK: return GetWMYSKTalkSfx(ped, sound);
		case MI_WFYSH: return GetWFYSHTalkSfx(ped, sound);
		case MI_WFOSH: return GetWFOSHTalkSfx(ped, sound);
		case MI_JFOTO: return GetJFOTOTalkSfx(ped, sound);
		case MI_JMOTO: return GetJMOTOTalkSfx(ped, sound);
		case MI_CBA:
		case MI_CBB: return GetCBTalkSfx(ped, sound);
		case MI_HNA:
		case MI_HNB: return GetHNTalkSfx(ped, sound);
		case MI_SGA:
		case MI_SGB: return GetSGTalkSfx(ped, sound);
		case MI_CLA:
		case MI_CLB: return GetCLTalkSfx(ped, sound);
		case MI_GDA:
		case MI_GDB: return GetGDTalkSfx(ped, sound);
		case MI_BKA:
		case MI_BKB: return GetBKTalkSfx(ped, sound);
		case MI_PGA:
		case MI_PGB: return GetPGTalkSfx(ped, sound);
		case MI_VICE1:
		case MI_VICE2:
		case MI_VICE3:
		case MI_VICE4:
		case MI_VICE5:
		case MI_VICE6:
		case MI_VICE7:
		case MI_VICE8: return GetVICETalkSfx(ped, sound, ped->GetModelIndex());
		case MI_WFYG1: return GetWFYG1TalkSfx(ped, sound);
		case MI_WFYG2: return GetWFYG2TalkSfx(ped, sound);
		case MI_SPECIAL01:
		case MI_SPECIAL02:
		case MI_SPECIAL03:
		case MI_SPECIAL04:
		case MI_SPECIAL05:
		case MI_SPECIAL06:
		case MI_SPECIAL07:
		case MI_SPECIAL08:
		case MI_SPECIAL09:
		case MI_SPECIAL10:
		case MI_SPECIAL11:
		case MI_SPECIAL12:
		case MI_SPECIAL13:
		case MI_SPECIAL14:
		case MI_SPECIAL15:
		case MI_SPECIAL16:
		case MI_SPECIAL17:
		case MI_SPECIAL18:
		case MI_SPECIAL19:
		case MI_SPECIAL20:
		case MI_SPECIAL21: return NO_SAMPLE;
		default: return GetGenericMaleTalkSfx(ped, sound);
		}
	}

	return NO_SAMPLE;
}

void
cAudioManager::GetPhrase(uint32 &phrase, uint32 &prevPhrase, uint32 sample, uint32 maxOffset) const
{
	phrase = sample + m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] % maxOffset;

	// check if the same sfx like last time, if yes, then try use next one,
	// if exceeded range, then choose first available sample
	if (phrase == prevPhrase && ++phrase >= sample + maxOffset)
		phrase = sample;
	prevPhrase = phrase;
}

#pragma region PED_COMMENTS

#define cooldown_phrase(count)		static uint8 cooldown = 0;\
if (cooldown != 0) {\
	if (++cooldown == count) cooldown = 0;\
	return NO_SAMPLE;\
}\
cooldown = 1;

uint32
cAudioManager::GetPlayerTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	if(m_bIsPlayerShutUp) return NO_SAMPLE;
	switch(sound) {
	case SOUND_PED_DEATH: return SFX_PLAYER_DEATH;
	case SOUND_PED_DAMAGE:
	case SOUND_PED_BULLET_HIT: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_HIT_BULLET_1, 33); break;
	case SOUND_PED_HIT:
	case SOUND_PED_DEFEND: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_HIT_FIST_1, 42); break;
	case SOUND_PED_LAND: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_HIT_GROUND_1, 35); break;
	case SOUND_PED_BURNING: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ON_FIRE_1, 16); break;
	case SOUND_PED_PLAYER_REACTTOCOP:
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_BUSTED_1, 38);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_BUSTED_1, 20);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_BUSTED_1, 22);
			break;
		}
		break;
	case SOUND_PED_ON_FIRE: {
		cooldown_phrase(8);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_SHOOT_1, 29);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_SHOOT_1, 39);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_SHOOT_1, 9);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_SHOOT_1, 35);
			break;
		}
		break;
	}
	case SOUND_PED_AIMING: {
		cooldown_phrase(8);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_PULL_GUN_1, 25);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_PULL_GUN_1, 52);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_PULL_GUN_1, 19);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_PULL_GUN_1, 39);
			break;
		}
		break;
	}
	case SOUND_PED_CAR_JACKING: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_JACKING_1, 36);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_JACKING_1, 43);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_JACKING_1, 18);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_JACKING_1, 40);
			break;
		}
		break;
	}
	case SOUND_PED_MUGGING: {
		cooldown_phrase(8);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_PICK_UP_CASH_1, 25);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_PICK_UP_CASH_1, 12);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_PICK_UP_CASH_1, 23);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_PICK_UP_CASH_1, 11);
			break;
		}
		break;
	}
	case SOUND_PED_CAR_JACKED: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_JACKED_1, 21);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_JACKED_1, 33);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_JACKED_1, 18);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_JACKED_1, 24);
			break;
		}
		break;
	}
	case SOUND_PED_PLAYER_AFTERSEX: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_AFTERSEX_1, 18); break;
	case SOUND_PED_PLAYER_BEFORESEX:
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_SEX_1, 18);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_SEX_1, 10);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_SEX_1, 8);
			break;
		}
		break;
	case SOUND_PED_PLAYER_FARFROMCOPS: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_CHASED_1, 9);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_CHASED_1, 7);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_CHASED_1, 20);
			break;
		}
		break;
	}
	case SOUND_PED_ATTACK: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_FIGHT_1, 61);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_FIGHT_1, 61);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_FIGHT_1, 27);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_FIGHT_1, 47);
			break;
		}
		break;
	}
	case SOUND_PED_CRASH_VEHICLE:
	case SOUND_PED_CRASH_CAR:
	case SOUND_PED_ANNOYED_DRIVER: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_CRASH_1, 44);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_CRASH_1, 41);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_CRASH_1, 19);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_CRASH_1, 43);
			break;
		}
		break;
	}
	case SOUND_PED_SOLICIT: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_PISSED_OFF_PICK_UP_HOOKER_1, 17);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_ANGRY_PICK_UP_HOOKER_1, 6);
			break;
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_WISECRACKING_PICK_UP_HOOKER_1, 11);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_CALM_PICK_UP_HOOKER_1, 22);
			break;
		}
		break;
	}
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetCopTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	PedState objective;
	switch(sound) {
	case SOUND_PED_ARREST_COP: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_ARREST_1, 4); break;
	case SOUND_PED_PULLOUTWEAPON: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_PULLOUTWEAPON_1, 3); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_SAVED_1, 2); break;
	case SOUND_PED_COP_TARGETING: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_COP_TARGETING_1, 4); break;
	case SOUND_PED_COP_MANYCOPSAROUND: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_COP_MANYCOPSAROUND_1, 2); break;
	case SOUND_PED_GUNAIMEDAT2: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_GUNAIMEDAT2_1, 2); break;
	case SOUND_PED_COP_ALONE: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_COP_ALONE_1, 4); break;
	case SOUND_PED_GUNAIMEDAT3: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_GUNAIMEDAT2_1, 2); break;
	case SOUND_PED_COP_ASK_FOR_ID: {
		cooldown_phrase(4);
		GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_COP_ASK_FOR_ID_1, 2);
		break;
	}
	case SOUND_PED_COP_LITTLECOPSAROUND:
		objective = FindPlayerPed()->m_nPedState;
		if(objective == PED_ARRESTED || objective == PED_DEAD || objective == PED_DIE) return NO_SAMPLE;
		GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_COP_LITTLECOPSAROUND_1, 4);
		break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_FIGHT_1, 4); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_DODGE_1, 3); break;
#ifdef FIX_BUGS
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_CAR_CRASH_1, 4); break;
#endif
	case SOUND_PED_PED_COLLISION:
		if(FindPlayerPed()->m_pWanted->GetWantedLevel() > 0)
			GetPhrase(sfx, ped->m_lastComment, SFX_COP_VOICE_1_BUMP_1, 5);
		else
			return NO_SAMPLE;
		break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_COP_VOICE_2_ARREST_1 - SFX_COP_VOICE_1_ARREST_1) * (m_sQueueSample.m_nEntityIndex % 5) + sfx;
}

uint32
cAudioManager::GetSwatTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	switch(sound) {
	case SOUND_PED_COP_HELIPILOTPHRASE: GetPhrase(sfx, ped->m_lastComment, SFX_SWAT_VOICE_1_COP_HELIPILOTPHRASE_1, 7); break;
	case SOUND_PED_COP_TARGETING: GetPhrase(sfx, ped->m_lastComment, SFX_SWAT_VOICE_1_COP_TARGETING_1, 4); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_SWAT_VOICE_1_DODGE_1, 3); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	sfx += (SFX_SWAT_VOICE_2_DODGE_1 - SFX_SWAT_VOICE_1_DODGE_1) * (m_sQueueSample.m_nEntityIndex % 3);
	return sfx;
}

uint32
cAudioManager::GetFBITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	switch(sound) {
#ifdef FIX_BUGS
	case SOUND_PED_COP_TARGETING: GetPhrase(sfx, ped->m_lastComment, SFX_FBI_VOICE_1_COP_TARGETING_1, 6); break;
#else
	case SOUND_PED_COP_TARGETING: GetPhrase(sfx, ped->m_lastComment, SFX_FBI_VOICE_1_COP_TARGETING_1, 4); break;
#endif
	case SOUND_PED_COP_MANYCOPSAROUND: GetPhrase(sfx, ped->m_lastComment, SFX_FBI_VOICE_1_COP_MANYCOPSAROUND_1, 3); break;
	case SOUND_PED_GUNAIMEDAT2: sfx = SFX_FBI_VOICE_1_GUNAIMEDAT2_1; break;
	case SOUND_PED_GUNAIMEDAT3: GetPhrase(sfx, ped->m_lastComment, SFX_FBI_VOICE_1_GUNAIMEDAT3_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE:
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_FBI_VOICE_1_CAR_CRASH_1, 4); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
#ifdef FIX_BUGS
	sfx += (SFX_FBI_VOICE_2_GUNAIMEDAT3_1 - SFX_FBI_VOICE_1_GUNAIMEDAT3_1) * (m_sQueueSample.m_nEntityIndex % 3);
#else
	sfx += 16 * (m_sQueueSample.m_nEntityIndex % 3);
#endif
	return sfx;
}

uint32
cAudioManager::GetArmyTalkSfx(CPed *ped, int16 sound)
{
	return GetGenericMaleTalkSfx(ped, sound);
}

uint32
cAudioManager::GetMedicTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	switch(sound) {
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_MEDIC_VOICE_1_FIGHT_1, 6); break;
	case SOUND_PED_HEALING: GetPhrase(sfx, ped->m_lastComment, SFX_MEDIC_VOICE_1_AT_VICTIM_1, 17); break;
	case SOUND_PED_LEAVE_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_MEDIC_VOICE_1_GET_OUT_VAN_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	sfx += (SFX_MEDIC_VOICE_2_FIGHT_1 - SFX_MEDIC_VOICE_1_FIGHT_1) * (m_sQueueSample.m_nEntityIndex % 2);
	return sfx;
}

uint32
cAudioManager::GetFiremanTalkSfx(CPed *ped, int16 sound)
{
	return GetGenericMaleTalkSfx(ped, sound);
}

uint32
cAudioManager::GetDefaultTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_GUN_PANIC_1, 12); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_JACKED_1, 12); break;
#ifdef FIX_BUGS
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_JACKING_1, 13); break;
#endif
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_MUGGED_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_SAVED_1, 4); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_TAXI_1, 5); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_FIGHT_1, 16); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_DODGE_1, 19); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_RUN_1, 19); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_GENERIC_CRASH_1, 13); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_CAR_CRASH_1, 15); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_BLOCKED_1, 16); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_LOST_1, 5); break;
#ifdef FIX_BUGS
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_EYEING_1, 6); break;
#else
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_EYEING_1, 6); break;
#endif
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_SHOCKED_1, 6); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_BUMP_1, 25); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_DEFAULT_VOICE_CHAT_1, 25); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFYSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_JACKING_1, 4); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_MUGGING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_MUGGED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HFYST_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_BLOCKED_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_LOST_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYST_CHAT_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFOSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_GUN_COOL_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_MUGGED_1, 3); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_GENERIC_CRASH_1, 11); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_BLOCKED_1, 9); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_LOST_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_BUMP_1, 12); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOST_CHAT_1, 11); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMYSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_GUN_PANIC_1, 6); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HMYST_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_HMYST_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_DODGE_1, 6); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_BUMP_1, 13); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYST_CHAT_1, 11); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMOSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_JACKING_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_MUGGED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HMOST_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_DODGE_1, 9); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_BLOCKED_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: return SFX_HMOST_EYEING_1;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HMOST_CHAT_1, 11); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFYRITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_MUGGED_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HFYRI_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_DODGE_1, 10); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_LOST_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFYRI_BUMP_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFORITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_GUN_PANIC_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_JACKED_1, 9); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HFORI_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_HFORI_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_DODGE_1, 6); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_BLOCKED_1, 6); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFORI_BUMP_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMYRITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_GUN_PANIC_1, 7); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_JACKING_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: return SFX_HMYRI_MUGGED_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_FIGHT_1, 5); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_DODGE_1, 9); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_GENERIC_CRASH_1, 12); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_BLOCKED_1, 7); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMYRI_BUMP_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMORITalkSfx(CPed *ped, int16 sound)
{

	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_MUGGED_1, 3); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_DODGE_1, 7); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_RUN_1, 6); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_GENERIC_CRASH_1, 11); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_CAR_CRASH_1, 6); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_LOST_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HMORI_CHAT_1, 8); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFYBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_GUN_PANIC_1, 7); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_JACKED_1, 7); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HFYBE_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_DODGE_1, 11); break;
#ifdef FIX_BUGS // assumption
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_RUN_1, 7); break;
#endif
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_CAR_CRASH_1, 6); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_LOST_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_BUMP_1, 8); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBE_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFOBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_JACKED_1, 6); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HFOBE_SAVED_1;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_DODGE_1, 7); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_GENERIC_CRASH_1, 5); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_CAR_CRASH_1, 6); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_BLOCKED_1, 6); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_LOST_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOBE_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMYBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_GUN_PANIC_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_JACKED_1, 12); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HMYBE_SAVED_1;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_INNOCENT_1, 4); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HMYBE_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_DODGE_1, 7); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_GENERIC_CRASH_1, 10); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_CAR_CRASH_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_LOST_1, 3); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_EYEING_1, 5); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYBE_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMOBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HMOBE_GUN_PANIC_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HMOBE_JACKED_1, 6); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_HMOBE_INNOCENT_1, 3); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMOBE_DODGE_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HMOBE_BLOCKED_1, 10); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_HMOBE_EYEING_1, 4); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMOBE_BUMP_1, 8); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}

	return sfx;
}

uint32
cAudioManager::GetHFYBUTalkSfx(CPed *ped, int16 sound)
{

	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_JACKING_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HFYBU_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_HFYBU_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_GENERIC_CRASH_1, 12); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_LOST_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFYBU_BUMP_1, 11); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFYMDTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYMD_GUN_PANIC_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYMD_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_HFYMD_SAVED_1, 3); break;
#ifdef FIX_BUGS
	case SOUND_PED_TAXI_WAIT: return SFX_HFYMD_TAXI_1;
#else
	case SOUND_PED_TAXI_WAIT: return SFX_BFOBE_TAXI_1;
#endif
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYMD_FIGHT_1, 9); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYMD_DODGE_1, 8); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYMD_SOLICIT_1, 15); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFYMD_BUMP_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFYCGTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HFYCG_GUN_PANIC_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYCG_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HFYCG_SAVED_1;
#ifdef FIX_BUGS
	case SOUND_PED_TAXI_WAIT: return SFX_HFYCG_TAXI_1;
#else
	case SOUND_PED_TAXI_WAIT: return SFX_BFOBE_TAXI_1;
#endif
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYCG_DODGE_1, 8); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HFYCG_RUN_1, 4); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYCG_SOLICIT_1, 14); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFYCG_BUMP_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFYPRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_GUN_COOL_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HFYPR_SAVED_1;
	case SOUND_PED_PLAYER_BEFORESEX: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_FUCKING_1, 8); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HFYPR_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_FIGHT_1, 10); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_DODGE_1, 9); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_SOLICIT_1, 14); break;
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_EYEING_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HFYPR_CHAT_1, 12); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHFOTRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_GUN_COOL_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_HFOTR_SAVED_1;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_FIGHT_1, 6); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_DODGE_1, 8); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HFOTR_CHAT_1, 12); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMOTRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_GUN_COOL_1, 6); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HMOTR_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_DODGE_1, 11); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_SOLICIT_1, 8); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_BUMP_1, 8); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HMOTR_CHAT_1, 9); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMYAPTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_GUN_PANIC_1, 7); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_JACKED_1, 7); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_RUN_1, 6); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_GENERIC_CRASH_1, 6); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_BLOCKED_1, 9); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_EYEING_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HMYAP_CHAT_1, 9); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHMOCATalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_JACKING_1, 11); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_JACKED_1, 10); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_MUGGED_1, 7); break;
	case SOUND_PED_TAXI_WAIT: return SFX_HMOCA_TAXI_1;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_RUN_1, 2); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_BLOCKED_1, 8); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_EYEING_1, 2); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HMOCA_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMODKTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_GUN_PANIC_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_JACKED_1, 9); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_MUGGED_1, 2); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_INNOCENT_1, 3); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BMODK_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_DODGE_1, 7); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_CAR_CRASH_1, 10); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_BLOCKED_1, 8); break;
	case SOUND_PED_147: // this is some cut behaviour, the guy was selling something
		GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_UNK_147_1, 11);
		// what is this? some sort of censorship?
		switch(sfx) {
		case SFX_BMODK_UNK_147_5:
		case SFX_BMODK_UNK_147_6:
		case SFX_BMODK_UNK_147_7: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_UNK_147_1, 4); break;
		default: break;
		}
		break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMODK_BUMP_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMYCRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_GUN_COOL_1, 6); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_JACKING_1, 12); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_MUGGING_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_MUGGED_1, 3); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_SAVED_1, 2); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_INNOCENT_1, 4); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_DODGE_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_BLOCKED_1, 12); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMYCR_BUMP_1, 11); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFYSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_GUN_PANIC_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BFYST_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_RUN_1, 6); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_LOST_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_BUMP_1, 9); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYST_CHAT_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFOSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BFOST_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_DODGE_1, 11); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_BLOCKED_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_LOST_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BFOST_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMYSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_GUN_COOL_1, 6); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_JACKING_1, 4); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_MUGGING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_MUGGED_1, 2); break;
#ifdef FIX_BUGS
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_TAXI_1, 2); break;
#else
	case SOUND_PED_TAXI_WAIT: return SFX_BMYST_TAXI_1;
#endif
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_FIGHT_1, 6); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_DODGE_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_BLOCKED_1, 8); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYST_CHAT_1, 12); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMOSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_GUN_PANIC_1, 9); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_MUGGED_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BMOST_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_BMOST_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_DODGE_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_GENERIC_CRASH_1, 13); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_CAR_CRASH_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_LOST_1, 6); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_EYEING_1, 6); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_BUMP_1, 17); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BMOST_CHAT_1, 18); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFYRITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_GUN_PANIC_1, 4); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_MUGGED_1, 3); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BFYRI_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_DODGE_1, 8); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_RUN_1, 6); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_BLOCKED_1, 9); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_EYEING_1, 3); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_SHOCKED_1, 4); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BFYRI_BUMP_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFORITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_JACKED_1, 4); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BFORI_SAVED_1;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_LOST_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BFORI_BUMP_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMYRITalkSfx(CPed *ped, int16 sound)
{

	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_GUN_PANIC_1, 7); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_JACKED_1, 4); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BMYRI_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_BMYRI_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_DODGE_1, 8); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_BLOCKED_1, 6); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: return SFX_BMYRI_EYEING_1;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMYRI_BUMP_1, 7); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFYBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_GUN_COOL_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_MUGGED_1, 5); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_TAXI_1, 3); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_DODGE_1, 10); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_RUN_1, 6); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_GENERIC_CRASH_1, 8); break;
#ifdef FIX_BUGS
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_CAR_CRASH_1, 10); break;
#else
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_CAR_CRASH_1, 8); break;
#endif
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_BLOCKED_1, 12); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_LOST_1, 4); break;
#ifdef FIX_BUGS
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_EYEING_1, 4); break;
#else
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_EYEING_1, 4); break;
#endif
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_SHOCKED_1, 4); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYBE_CHAT_1, 16); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMYBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_GUN_COOL_1, 4); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_JACKING_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: return SFX_BMYBE_MUGGED_1;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BMYBE_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_BMYBE_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: return SFX_BMYBE_LOST_1;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBE_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFOBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_MUGGED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BFOBE_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_DODGE_1, 9); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_BLOCKED_1, 8); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_BUMP_1, 8); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BFOBE_CHAT_1, 8); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMOBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_MUGGED_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_SAVED_1, 3); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BMOBE_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_FIGHT_1, 10); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_DODGE_1, 11); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_CAR_CRASH_1, 9); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_BUMP_1, 5); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BMOBE_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMYBUTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BMYBU_SAVED_1;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_INNOCENT_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BMYBU_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_FIGHT_1, 5); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_BLOCKED_1, 8); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBU_BUMP_1, 7); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFYPRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_GUN_COOL_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BFYPR_SAVED_1;
	case SOUND_PED_PLAYER_BEFORESEX: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_FUCKING_1, 7); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_DODGE_1, 7); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_SOLICIT_1, 13); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BFYPR_CHAT_1, 13); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBFOTRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_GUN_COOL_1, 6); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_MUGGING_1, 3); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BFOTR_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_BFOTR_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_FIGHT_1, 6); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_DODGE_1, 9); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_SOLICIT_1, 5); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BFOTR_CHAT_1, 15); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMOTRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_GUN_COOL_1, 5); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_SAVED_1, 1); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_INNOCENT_1, 4); break;
	case SOUND_PED_TAXI_WAIT: return SFX_BMOTR_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_DODGE_1, 11); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_RUN_1, 7); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_SOLICIT_1, 7); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_EYEING_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BMOTR_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMYPITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: return SFX_BMYPI_MUGGED_1;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_BMYPI_SAVED_1;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_GENERIC_CRASH_1, 13); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_CAR_CRASH_1, 5); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_BLOCKED_1, 6); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_EYEING_1, 4); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMYPI_BUMP_1, 9); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBMYBBTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_JACKING_1, 9); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_MUGGING_1, 8); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_JACKED_1, 11); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_MUGGED_1, 5); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_SAVED_1, 6); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_INNOCENT_1, 4); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_TAXI_1, 3); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_FIGHT_1, 12); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_DODGE_1, 18); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_GENERIC_CRASH_1, 9); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_BLOCKED_1, 13); break;
	case SOUND_PED_JEER: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_JEER_1, 16); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_EYEING_1, 16); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_SHOCKED_1, 6); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_BUMP_1, 17); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BMYBB_CHAT_1, 21); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYCRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_JACKING_1, 6); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_MUGGING_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_MUGGED_1, 3); break;
	case SOUND_PED_TAXI_WAIT: return SFX_WMYCR_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_GENERIC_CRASH_1, 9); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_CAR_CRASH_1, 9); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCR_BUMP_1, 18); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_JACKING_1, 4); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_MUGGING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFYST_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WFYST_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_BLOCKED_1, 6); break;
	case SOUND_PED_WAIT_DOUBLEBACK: return SFX_WFYST_LOST_1;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYST_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFOSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_GUN_PANIC_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_MUGGED_1, 5); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_SAVED_1, 4); break;
	case SOUND_PED_TAXI_WAIT: return SFX_WFOST_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_DODGE_1, 12); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_RUN_1, 7); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_GENERIC_CRASH_1, 10); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_CAR_CRASH_1, 11); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_BLOCKED_1, 12); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_LOST_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_BUMP_1, 19); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOST_CHAT_1, 16); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_GUN_PANIC_1, 5); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_MUGGING_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: return SFX_WMYST_MUGGED_1;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMYST_SAVED_1;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_INNOCENT_1, 3); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_DODGE_1, 10); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_RUN_1, 7); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_GENERIC_CRASH_1, 5); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYST_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMOSTTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_JACKED_1, 4); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMOST_SAVED_1;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_INNOCENT_1, 3); break;
	case SOUND_PED_TAXI_WAIT: return SFX_WMOST_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_DODGE_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_BLOCKED_1, 8); break;
	case SOUND_PED_JEER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_JEER_1, 4); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOST_CHAT_1, 9); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYRITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_JACKED_1, 7); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFYRI_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WFYRI_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_RUN_1, 5); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYRI_BUMP_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFORITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_GUN_PANIC_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_MUGGED_1, 3); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFORI_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WFORI_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_DODGE_1, 11); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_CAR_CRASH_1, 10); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_BLOCKED_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_LOST_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFORI_BUMP_1, 11); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYRITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_GUN_PANIC_1, 8); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_JACKED_1, 8); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMYRI_SAVED_1;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_RUN_1, 5); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_GENERIC_CRASH_1, 11); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_BLOCKED_1, 10); break;
	case SOUND_PED_WAIT_DOUBLEBACK: return SFX_WMYRI_LOST_1;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_EYEING_1, 3); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_SHOCKED_1, 4); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_BUMP_1, 8); break;
#ifdef FIX_BUGS
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYRI_CHAT_1, 10); break;
#endif
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMORITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_GUN_PANIC_1, 9); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_MUGGED_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_DODGE_1, 10); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_RUN_1, 12); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_CAR_CRASH_1, 6); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_BLOCKED_1, 10); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_EYEING_1, 3); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_SHOCKED_1, 4); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMORI_BUMP_1, 14); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_JACKED_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFYBE_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WFYBE_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_DODGE_1, 8); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_RUN_1, 5); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_GENERIC_CRASH_1, 6); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_CAR_CRASH_1, 6); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_BLOCKED_1, 7); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBE_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_GUN_PANIC_1, 8); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_JACKING_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_JACKED_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_DODGE_1, 12); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_RUN_1, 5); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_BLOCKED_1, 9); break;
	case SOUND_PED_JEER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_JEER_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_LOST_1, 3); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_SHOCKED_1, 6); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_BUMP_1, 14); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBE_CHAT_1, 11); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFOBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_JACKED_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_SAVED_1, 3); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_DODGE_1, 8); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_RUN_1, 7); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_GENERIC_CRASH_1, 10); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_BLOCKED_1, 8); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOBE_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMOBETalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_JACKING_1, 4); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_MUGGING_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_JACKED_1, 8); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_SAVED_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_DODGE_1, 8); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_BLOCKED_1, 6); break;
	case SOUND_PED_JEER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_JEER_1, 16); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_BUMP_1, 12); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYCWTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_GUN_PANIC_1, 6); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: return SFX_WMYCW_MUGGED_1;
#ifdef FIX_BUGS
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_INNOCENT_1, 3); break;
#endif
	case SOUND_PED_TAXI_WAIT: return SFX_WMYCW_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_BLOCKED_1, 9); break;
	case SOUND_PED_JEER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_JEER_1, 5); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_EYEING_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_BUMP_1, 9); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYCW_CHAT_1, 15); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYGOTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMYGO_SAVED_1;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_TAXI_1, 3); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_DODGE_1, 11); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_RUN_1, 6); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_CAR_CRASH_1, 7); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_BUMP_1, 9); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYGO_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFOGOTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFOGO_SAVED_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_FIGHT_1, 14); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_RUN_1, 2); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_CAR_CRASH_1, 8); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_BUMP_1, 8); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOGO_CHAT_1, 11); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMOGOTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_GUN_PANIC_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_JACKED_1, 6); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMOGO_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WMOGO_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_FIGHT_1, 13); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_DODGE_1, 12); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_RUN_1, 5); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_CAR_CRASH_1, 9); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_BUMP_1, 8); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOGO_CHAT_1, 9); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYLGTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFYLG_GUN_COOL_1, 5); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFYLG_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WFYLG_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYLG_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYLG_DODGE_1, 8); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYLG_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYLG_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYLGTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WMYLG_GUN_COOL_1, 6); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMYLG_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WMYLG_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYLG_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYLG_DODGE_1, 9); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYLG_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYLG_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYBUTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_GUN_PANIC_1, 8); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_MUGGED_1, 4); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_TAXI_1, 2); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_RUN_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_CAR_CRASH_1, 9); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYBU_BUMP_1, 21); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYBUTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_GUN_PANIC_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: return SFX_WMYBU_MUGGED_1;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_SAVED_1, 2); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_INNOCENT_1, 2); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_DODGE_1, 10); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_RUN_1, 3); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_GENERIC_CRASH_1, 5); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_CAR_CRASH_1, 9); break;
#ifdef FIX_BUGS
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_BLOCKED_1, 9); break;
#else
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBE_BLOCKED_1, 6); break;
#endif
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_LOST_1, 5); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_SHOCKED_1, 5); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYBU_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMOBUTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_GUN_PANIC_1, 6); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_JACKED_1, 7); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_SAVED_1, 3); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_FIGHT_1, 3); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_DODGE_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_CAR_CRASH_1, 7); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_BLOCKED_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_LOST_1, 3); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMOBU_BUMP_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYPRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_GUN_COOL_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFYPR_SAVED_1;
	case SOUND_PED_PLAYER_BEFORESEX: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_FUCKING_1, 5); break;
	case SOUND_PED_TAXI_WAIT: return SFX_WFYPR_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_FIGHT_1, 9); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_DODGE_1, 10); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_SOLICIT_1, 15); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYPR_CHAT_1, 14); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFOTRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFOTR_GUN_COOL_1, 6); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFOTR_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WFOTR_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOTR_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFOTR_RUN_1, 6); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOTR_SOLICIT_1, 9); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFOTR_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOTR_CHAT_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMOTRTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_GUN_COOL_1, 5); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMOTR_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WMOTR_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_FIGHT_1, 6); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_DODGE_1, 17); break;
	case SOUND_PED_SOLICIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_SOLICIT_1, 7); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_SHOCKED_1, 3); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMOTR_CHAT_1, 13); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYPITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_SAVED_1, 2); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_INNOCENT_1, 2); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_TAXI_1, 4); break;
#ifdef FIX_BUGS
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_FIGHT_1, 9); break;
#else
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_FIGHT_1, 7); break;
#endif
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_DODGE_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_BLOCKED_1, 8); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_EYEING_1, 6); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYPI_BUMP_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMOCATalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_GUN_PANIC_1, 6); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_JACKING_1, 11); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_JACKED_1, 10); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMOCA_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WMOCA_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_FIGHT_1, 8); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_GENERIC_CRASH_1, 9); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_CAR_CRASH_1, 10); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_BLOCKED_1, 12); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMOCA_BUMP_1, 6); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYJGTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYJG_GUN_PANIC_1, 4); break;
	case SOUND_PED_ACCIDENTREACTION1: sfx = SFX_WFYJG_SAVED_1; break;
	case SOUND_PED_TAXI_WAIT: sfx = SFX_WFYJG_TAXI_1; break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYJG_DODGE_1, 8); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFYJG_RUN_1, 6); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYJG_BUMP_1, 12); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYJGTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYJG_GUN_PANIC_1, 4); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYJG_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WMYJG_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WMYJG_TAXI_1;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WMYJG_RUN_1, 5); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYJG_BLOCKED_1, 10); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYJG_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYJG_BUMP_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYSKTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSK_GUN_PANIC_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSK_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSK_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: return SFX_WFYSK_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSK_FIGHT_1, 11); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSK_DODGE_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSK_BLOCKED_1, 11); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSK_BUMP_1, 18); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWMYSKTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_GUN_PANIC_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_SAVED_1, 2); break;
	case SOUND_PED_INNOCENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_INNOCENT_1, 3); break;
	case SOUND_PED_TAXI_WAIT: return SFX_WMYSK_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_FIGHT_1, 5); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_DODGE_1, 10); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_BUMP_1, 14); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WMYSK_CHAT_1, 13); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYSHTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_GUN_COOL_1, 9); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_SAVED_1, 4); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_DODGE_1, 11); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_RUN_1, 11); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_LOST_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_SHOCKED_1, 5); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_BUMP_1, 12); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYSH_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFOSHTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_GUN_COOL_1, 10); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_SAVED_1, 3); break;
	case SOUND_PED_TAXI_WAIT: return SFX_WFOSH_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_DODGE_1, 10); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_RUN_1, 9); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_LOST_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_SHOCKED_1, 5); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFOSH_CHAT_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetJFOTOTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_GUN_PANIC_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_SAVED_1, 2); break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_TAXI_1, 2); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_RUN_1, 5); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_GENERIC_CRASH_1, 6); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: return SFX_JFOTO_LOST_1;
	case SOUND_PED_CHAT_EVENT: return SFX_JFOTO_SHOCKED_1;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_JFOTO_CHAT_1, 13); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetJMOTOTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_GUN_PANIC_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_JACKED_1, 4); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_JMOTO_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_JMOTO_TAXI_1;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_DODGE_1, 6); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_RUN_1, 4); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_GENERIC_CRASH_1, 6); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_CAR_CRASH_1, 6); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: return SFX_JMOTO_LOST_1;
	case SOUND_PED_CHAT_EVENT: return SFX_JMOTO_SHOCKED_1;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_BUMP_1, 8); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_JMOTO_CHAT_1, 7); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetCBTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_JACKING_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_JACKED_1, 4); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: sfx = SFX_CUBAN_GANG_1_SAVED_1; break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_FIGHT_1, 9); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_DODGE_1, 9); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_CAR_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_GANG_1_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_CUBAN_GANG_2_BLOCKED_1 - SFX_CUBAN_GANG_1_BLOCKED_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetHNTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_MUGGED_1, 3); break;
	case SOUND_PED_ACCIDENTREACTION1: sfx = SFX_HAITIAN_GANG_1_SAVED_1; break;
	case SOUND_PED_TAXI_WAIT: sfx = SFX_HAITIAN_GANG_1_TAXI_1; break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_FIGHT_1, 10); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_DODGE_1, 10); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_GENERIC_CRASH_1, 9); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_BLOCKED_1, 9); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_LOST_1, 4); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_BUMP_1, 12); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_HAITIAN_GANG_1_CHAT_1, 14); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_HAITIAN_GANG_2_BLOCKED_1 - SFX_HAITIAN_GANG_1_BLOCKED_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetSGTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_JACKING_1, 5); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_MUGGING_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_MUGGED_1, 3); break;
	case SOUND_PED_ACCIDENTREACTION1: sfx = SFX_STREET_GANG_1_SAVED_1; break;
	case SOUND_PED_TAXI_WAIT: sfx = SFX_STREET_GANG_1_TAXI_1; break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_FIGHT_1, 10); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_DODGE_1, 9); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_GENERIC_CRASH_1, 6); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_CAR_CRASH_1, 6); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_BLOCKED_1, 8); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_EYEING_1, 3); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_STREET_GANG_1_CHAT_1, 12); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	if(ped->GetModelIndex() == MI_SGB) sfx += (SFX_STREET_GANG_2_BLOCKED_1 - SFX_STREET_GANG_1_BLOCKED_1);
	return sfx;
}

uint32
cAudioManager::GetCLTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_JACKING_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_JACKED_1, 6); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: sfx = SFX_CUBAN_LORD_GANG_1_SAVED_1; break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_FIGHT_1, 10); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_DODGE_1, 13); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_CAR_CRASH_1, 10); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_BLOCKED_1, 10); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_EYEING_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_CUBAN_LORD_GANG_1_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_CUBAN_LORD_GANG_2_BLOCKED_1 - SFX_CUBAN_LORD_GANG_1_BLOCKED_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetGDTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_GUN_COOL_1, 6); break;
	case SOUND_PED_ACCIDENTREACTION1: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_SAVED_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_FIGHT_1, 7); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_DODGE_1, 9); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_GUARD_DUTY_1_CHAT_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_GUARD_DUTY_2_BUMP_1 - SFX_GUARD_DUTY_1_BUMP_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetBKTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_GUN_COOL_1, 5); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_JACKING_1, 4); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_JACKED_1, 8); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: sfx = SFX_BIKER_GANG_1_SAVED_1; break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_FIGHT_1, 9); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_DODGE_1, 9); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_GENERIC_CRASH_1, 8); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_BLOCKED_1, 10); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_LOST_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_BUMP_1, 10); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_BIKER_GANG_1_CHAT_1, 12); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_BIKER_GANG_2_BLOCKED_1 - SFX_BIKER_GANG_1_BLOCKED_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetPGTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_GUN_COOL_1, 4); break;
	case SOUND_PED_CAR_JACKING: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_JACKING_1, 5); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: sfx = SFX_PLAYER_GANG_1_SAVED_1; break;
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_TAXI_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_FIGHT_1, 5); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_DODGE_1, 7); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_GENERIC_CRASH_1, 5); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_CAR_CRASH_1, 5); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_BLOCKED_1, 10); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_LOST_1, 2); break;
	case SOUND_PED_CHAT_SEXY_MALE: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_SHOCKED_1, 2); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_BUMP_1, 5); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_PLAYER_GANG_1_CHAT_1, 8); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_PLAYER_GANG_2_BLOCKED_1 - SFX_PLAYER_GANG_1_BLOCKED_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetVICETalkSfx(CPed *ped, int16 sound, int16 model)
{
	uint32 sfx;
	if(model == MI_VICE6) {

		switch(sound) {
		case SOUND_PED_ARREST_COP: GetPhrase(sfx, ped->m_lastComment, SFX_VICE_VOICE_6_ARREST_1, 3); break;
		case SOUND_PED_MIAMIVICE_EXITING_CAR: return SFX_VICE_VOICE_6_MIAMIVICE_EXITING_CAR_1;
		default: return GetGenericMaleTalkSfx(ped, sound);
		}
	}
	switch(sound) {
	case SOUND_PED_ARREST_COP: GetPhrase(sfx, ped->m_lastComment, SFX_VICE_VOICE_1_ARREST_1, 3); break;
	case SOUND_PED_MIAMIVICE_EXITING_CAR: sfx = SFX_VICE_VOICE_1_MIAMIVICE_EXITING_CAR_1; break;

	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	sfx += (SFX_VICE_VOICE_2_ARREST_1-SFX_VICE_VOICE_1_ARREST_1) * (m_sQueueSample.m_nEntityIndex % 5);
	return sfx;
}

uint32
cAudioManager::GetWFYG1TalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_GUN_COOL_1, 6); break;
	case SOUND_PED_MUGGING: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_MUGGING_1, 2); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_MUGGED_1, 2); break;
	case SOUND_PED_ACCIDENTREACTION1: return SFX_WFYG1_SAVED_1;
	case SOUND_PED_TAXI_WAIT: return SFX_WFYG1_TAXI_1;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_FIGHT_1, 4); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_DODGE_1, 9); break;
	case SOUND_PED_FLEE_RUN: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_RUN_1, 2); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_BLOCKED_1, 7); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_LOST_1, 3); break;
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_EYEING_1, 2); break;
	case SOUND_PED_CHAT_EVENT: return SFX_WFYG1_SHOCKED_1;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG1_CHAT_1, 10); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWFYG2TalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_GUN_COOL_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_JACKED_1, 5); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_MUGGED_1, 2); break;
#ifdef FIX_BUGS
	case SOUND_PED_TAXI_WAIT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_TAXI_1, 2); break;
#else
	case SOUND_PED_TAXI_WAIT: return SFX_WFYG2_TAXI_1;
#endif
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_FIGHT_1, 5); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_DODGE_1, 8); break;
	case SOUND_PED_CRASH_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_GENERIC_CRASH_1, 7); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_CAR_CRASH_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_BLOCKED_1, 5); break;
	case SOUND_PED_WAIT_DOUBLEBACK: return SFX_WFYG2_LOST_1;
	case SOUND_PED_CHAT_SEXY_FEMALE: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_EYEING_1, 4); break;
	case SOUND_PED_CHAT_EVENT: return SFX_WFYG2_SHOCKED_1;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_BUMP_1, 11); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_WFYG2_CHAT_1, 9); break;
	default: return GetGenericFemaleTalkSfx(ped, sound);
	}

	return sfx;
}

uint32
cAudioManager::GetGenericMaleTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	m_bGenericSfx = TRUE;
	switch(sound) {
	case SOUND_PED_DEATH: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_MALE_DEATH_1, 41); break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_MALE_GRUNT_1, 41); break;
	case SOUND_PED_BURNING: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_MALE_FIRE_1, 32); break;
	case SOUND_PED_FLEE_SPRINT: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_MALE_PANIC_1, 35); break;
	default: return NO_SAMPLE;
	}
	return sfx;
}

uint32
cAudioManager::GetGenericFemaleTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	m_bGenericSfx = TRUE;
	switch(sound) {
	case SOUND_PED_DEATH: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_FEMALE_DEATH_1, 22); break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_FEMALE_GRUNT_1, 33); break;
	case SOUND_PED_BURNING: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_FEMALE_FIRE_1, 17); break;
	case SOUND_PED_FLEE_SPRINT: GetPhrase(sfx, ped->m_lastComment, SFX_GENERIC_FEMALE_PANIC_1, 27); break;
	default: return NO_SAMPLE;
	}
	return sfx;
}

void
cPedComments::Add(tPedComment *com)
{
	uint8 index;

	if (m_nCommentsInBank[m_nActiveBank] >= NUM_PED_COMMENTS_SLOTS) {
		index = m_nIndexMap[m_nActiveBank][NUM_PED_COMMENTS_SLOTS - 1];
		if (m_asPedComments[m_nActiveBank][index].m_bVolume > com->m_bVolume)
			return;
	} else {
		index = m_nCommentsInBank[m_nActiveBank]++;
	}

	m_asPedComments[m_nActiveBank][index] = *com;

	uint32 i = 0;
	if (index != 0) {
		for (i = 0; i < index; i++) {
			if (m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][i]].m_bVolume < m_asPedComments[m_nActiveBank][index].m_bVolume) {
				break;
			}
		}

		if (i < index)
			memmove(&m_nIndexMap[m_nActiveBank][i + 1], &m_nIndexMap[m_nActiveBank][i], NUM_PED_COMMENTS_SLOTS - 1 - i);
	}

	m_nIndexMap[m_nActiveBank][i] = index;
}

void
cPedComments::Process()
{
	uint32 sampleIndex;
	uint8 actualUsedBank;
	tPedComment *comment;
	bool8 prevUsed = FALSE;
	static uint8 counter = 0;
	static int32 prevSamples[10];

	if(AudioManager.m_nUserPause != 0) return;

	if(m_nCommentsInBank[m_nActiveBank]) {
		for(int i = 0; i < ARRAY_SIZE(prevSamples); i++) {
			if(m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_nSampleIndex ==
			   prevSamples[(counter + 1 + i) % ARRAY_SIZE(prevSamples)]) {
				m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_nProcess = -1;
				prevUsed = TRUE;
				break;
			}
		}
		if(!prevUsed) {
			sampleIndex = m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_nSampleIndex;
			if(!SampleManager.IsPedCommentLoaded(sampleIndex)) {
#if defined(GTA_PC) && !defined(FIX_BUGS)
				if(!m_bDelay)
#endif
					SampleManager.LoadPedComment(sampleIndex);
			} else {
				AudioManager.m_sQueueSample.m_nEntityIndex = m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_nEntityIndex;
				AudioManager.m_sQueueSample.m_nCounter = 0;
				AudioManager.m_sQueueSample.m_nSampleIndex = sampleIndex;
				AudioManager.m_sQueueSample.m_nBankIndex = SFX_BANK_PED_COMMENTS;
				AudioManager.m_sQueueSample.m_nReleasingVolumeModificator = 3;
				AudioManager.m_sQueueSample.m_nVolume = m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_bVolume;
				AudioManager.m_sQueueSample.m_fDistance = m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_fDistance;
				AudioManager.m_sQueueSample.m_nLoopCount = 1;
#ifndef GTA_PS2
				AudioManager.m_sQueueSample.m_nLoopStart = 0;
				AudioManager.m_sQueueSample.m_nLoopEnd = -1;
#endif
				AudioManager.m_sQueueSample.m_nEmittingVolume = MAX_VOLUME;
				AudioManager.m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				AudioManager.m_sQueueSample.m_fSoundIntensity = 40.0f;
				AudioManager.m_sQueueSample.m_bReleasingSoundFlag = TRUE;
				AudioManager.m_sQueueSample.m_vecPos = m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_vecPos;
				AudioManager.m_sQueueSample.m_bReverbFlag = TRUE;
				AudioManager.m_sQueueSample.m_bRequireReflection = TRUE;
				AudioManager.m_sQueueSample.m_bIs2D = FALSE;
#ifdef FIX_BUGS
				if (sampleIndex >= SFX_PLAYER_ANGRY_BUSTED_1 && sampleIndex < TOTAL_AUDIO_SAMPLES) { // check if player sfx
					AudioManager.m_sQueueSample.m_bIs2D = TRUE;
					AudioManager.m_sQueueSample.m_nOffset = 63;
				}
#endif // FIX_BUGS
				AudioManager.m_sQueueSample.m_nFrequency =
				    SampleManager.GetSampleBaseFrequency(AudioManager.m_sQueueSample.m_nSampleIndex) + AudioManager.RandomDisplacement(750);
				if(CTimer::GetIsSlowMotionActive()) AudioManager.m_sQueueSample.m_nFrequency /= 2;
				m_asPedComments[m_nActiveBank][m_nIndexMap[m_nActiveBank][0]].m_nProcess = -1;
				prevSamples[counter++] = sampleIndex;
				if(counter == 10) counter = 0;
				AudioManager.AddSampleToRequestedQueue();
#if defined(GTA_PC) && !defined(FIX_BUGS)
				m_nDelayTimer = CTimer::GetTimeInMilliseconds();
				m_bDelay = TRUE;
#endif
			}
		}
	}

	// Switch bank
	if (m_nActiveBank == 0) {
		actualUsedBank = 0;
		m_nActiveBank = 1;
	} else {
		actualUsedBank = 1;
		m_nActiveBank = 0;
	}
	comment = m_asPedComments[actualUsedBank];
	for (uint32 i = 0; i < m_nCommentsInBank[actualUsedBank]; i++) {
		if (m_asPedComments[actualUsedBank][m_nIndexMap[actualUsedBank][i]].m_nProcess > 0) {
			--m_asPedComments[actualUsedBank][m_nIndexMap[actualUsedBank][i]].m_nProcess;
			Add(&comment[m_nIndexMap[actualUsedBank][i]]);
		}
	}

	for (uint32 i = 0; i < NUM_PED_COMMENTS_SLOTS; i++) {
		m_nIndexMap[actualUsedBank][i] = NUM_PED_COMMENTS_SLOTS;
	}
	m_nCommentsInBank[actualUsedBank] = 0;
#if defined(GTA_PC) && !defined(FIX_BUGS)
	if(m_bDelay)
		if(CTimer::GetTimeInMilliseconds() - m_nDelayTimer > 6000) m_bDelay = FALSE;
#endif
}

#undef cooldown_phrase

#pragma endregion

#pragma endregion All the ped audio code

void
cAudioManager::ProcessExplosions(int32 explosion)
{
	uint8 type;
	float distSquared;

	for (uint8 i = 0; i < ARRAY_SIZE(gaExplosion); i++) {
		if (CExplosion::DoesExplosionMakeSound(i) && CExplosion::GetExplosionActiveCounter(i) == 1) {
			CExplosion::ResetExplosionActiveCounter(i);
			type = CExplosion::GetExplosionType(i);
			switch (type) {
			case EXPLOSION_GRENADE:
			case EXPLOSION_ROCKET:
			case EXPLOSION_BARREL:
			case EXPLOSION_TANK_GRENADE:
				m_sQueueSample.m_fSoundIntensity = 200.0f;
				m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_2;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 19000;
				m_sQueueSample.m_nReleasingVolumeModificator = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bRequireReflection = TRUE;
				break;
			case EXPLOSION_MOLOTOV:
				m_sQueueSample.m_fSoundIntensity = 150.0f;
				m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_3;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 19000;
				m_sQueueSample.m_nReleasingVolumeModificator = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bRequireReflection = FALSE;
				break;
			case EXPLOSION_MINE:
			case EXPLOSION_HELI_BOMB:
				m_sQueueSample.m_fSoundIntensity = 200.0f;
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_LEFT;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 12347;
				m_sQueueSample.m_nReleasingVolumeModificator = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bRequireReflection = TRUE;
				break;
			default:
				m_sQueueSample.m_fSoundIntensity = 200.0f;
				m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_1;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 19500;
				if (type == EXPLOSION_HELI)
					m_sQueueSample.m_nFrequency = 8 * m_sQueueSample.m_nFrequency / 10; //same *= 8 / 10;
				m_sQueueSample.m_nReleasingVolumeModificator = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_GENERIC_EXTRA;
				break;
			}
			m_sQueueSample.m_vecPos = *CExplosion::GetExplosionPosition(i);
			distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(m_sQueueSample.m_fSoundIntensity)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(MAX_VOLUME, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume != 0) {
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 1;
					m_sQueueSample.m_bReleasingSoundFlag = TRUE;
					m_sQueueSample.m_nEmittingVolume = MAX_VOLUME;
					RESET_LOOP_OFFSETS
					m_sQueueSample.m_bReverbFlag = TRUE;
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::ProcessFires(int32)
{
	CEntity *entity;
	uint8 emittingVol;
	float distSquared;

	for (uint8 i = 0; i < NUM_FIRES; i++) {
		if (gFireManager.m_aFires[i].m_bIsOngoing && gFireManager.m_aFires[i].m_bAudioSet) {
			entity = gFireManager.m_aFires[i].m_pEntity;
			if (entity) {
				switch (entity->GetType()) {
				case ENTITY_TYPE_BUILDING:
					m_sQueueSample.m_fSoundIntensity = 80.0f;
					m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
					emittingVol = 100;
					m_sQueueSample.m_nFrequency = 8 * SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE) / 10;
					m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency / 64);
					m_sQueueSample.m_nReleasingVolumeModificator = 6;
					break;
				case ENTITY_TYPE_PED:
					m_sQueueSample.m_fSoundIntensity = 25.0f;
					m_sQueueSample.m_nSampleIndex = SFX_PED_ON_FIRE;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PED_ON_FIRE);
					emittingVol = 60;
					m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency / 64);
					m_sQueueSample.m_nReleasingVolumeModificator = 10;
					break;
				default:
					m_sQueueSample.m_fSoundIntensity = 80.0f;
					m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE);
					m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency / 64);
					emittingVol = 80;
					m_sQueueSample.m_nReleasingVolumeModificator = 8;
				}
			} else {
				m_sQueueSample.m_fSoundIntensity = 80.0f;
				m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE);
				emittingVol = 80;
				m_sQueueSample.m_nReleasingVolumeModificator = 8;
			}
			m_sQueueSample.m_vecPos = gFireManager.m_aFires[i].m_vecPos;
			distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(m_sQueueSample.m_fSoundIntensity)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume != 0) {
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_nReleasingVolumeDivider = 10;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_bReleasingSoundFlag = FALSE;
					m_sQueueSample.m_nEmittingVolume = emittingVol;
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_bReverbFlag = TRUE;
					m_sQueueSample.m_bRequireReflection = FALSE;
					AddSampleToRequestedQueue();
				}
			}
			if (gFireManager.m_aFires[i].m_bExtinguishedWithWater) {
				gFireManager.m_aFires[i].m_bExtinguishedWithWater = FALSE;
				emittingVol = 100.0f * gFireManager.m_aFires[i].m_fWaterExtinguishCountdown;
				m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume != 0) {
					m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
					m_sQueueSample.m_nFrequency = 19591;
					m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency / 64);
					m_sQueueSample.m_nReleasingVolumeModificator = 9;
					m_sQueueSample.m_nCounter = i + 40;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_nReleasingVolumeDivider = 10;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_bReleasingSoundFlag = FALSE;
					m_sQueueSample.m_nEmittingVolume = emittingVol;
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_bReverbFlag = TRUE;
					m_sQueueSample.m_bRequireReflection = FALSE;
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::ProcessWaterCannon(int32)
{
	const float SOUND_INTENSITY = 30.0f;

	for (int32 i = 0; i < NUM_WATERCANNONS; i++) {
		if (CWaterCannons::aCannons[i].m_nId) {
			m_sQueueSample.m_vecPos = CWaterCannons::aCannons[0].m_avecPos[CWaterCannons::aCannons[i].m_nCur];
			float distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(SOUND_INTENSITY)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(50, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume != 0) {
					m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
					m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_nFrequency = 15591;
					m_sQueueSample.m_nReleasingVolumeModificator = 5;
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_nReleasingVolumeDivider = 8;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_bReleasingSoundFlag = FALSE;
					m_sQueueSample.m_nEmittingVolume = 50;
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_bReverbFlag = TRUE;
					m_sQueueSample.m_bRequireReflection = FALSE;
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

//positon of arcade machines
CVector aVecExtraSoundPosition[] = { CVector(-1042.546f, 88.794f, 11.324f), CVector(-1004.476f, 181.697f, 11.324f) };

void 
cAudioManager::ProcessExtraSounds()
{
	const float SOUND_INTENSITY = 18.0f;
	const uint8 EMITTING_VOLUME = 50;

	float distance;

	for (int i = 0; i < ARRAY_SIZE(aVecExtraSoundPosition); i++) {
		m_sQueueSample.m_vecPos = aVecExtraSoundPosition[i];
		distance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distance < SQR(SOUND_INTENSITY)) {
			m_sQueueSample.m_fDistance = Sqrt(distance);
			m_sQueueSample.m_nVolume = ComputeVolume(EMITTING_VOLUME, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nCounter = i;
				m_sQueueSample.m_nSampleIndex = SFX_ARCADE;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ARCADE);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 4;
				m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				m_sQueueSample.m_nEmittingVolume = EMITTING_VOLUME;
				SET_LOOP_OFFSETS(SFX_ARCADE)
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_bRequireReflection = FALSE;
				m_sQueueSample.m_nReleasingVolumeDivider = 3;
				AddSampleToRequestedQueue();
			}
		}
	}
}

void
cAudioManager::ProcessEscalators()
{
	const float SOUND_INTENSITY = 30.0f;
	const uint8 EMITTING_VOLUME = 26;

	float distance;

	for (int i = 0; i < CEscalators::NumEscalators; i++) {
		if (!CEscalators::GetEscalator(i).IsActive())
			continue;
		m_sQueueSample.m_vecPos = CEscalators::GetEscalator(i).GetPosition();
		distance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distance < SQR(SOUND_INTENSITY)) {
			m_sQueueSample.m_fDistance = Sqrt(distance);
			m_sQueueSample.m_nVolume = ComputeVolume(EMITTING_VOLUME, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nSampleIndex = SFX_BOAT_V12_LOOP;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = i * 50 % 250 + 3973;
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				m_sQueueSample.m_nReleasingVolumeDivider = 5;
				m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
				m_sQueueSample.m_nCounter = i;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nEmittingVolume = EMITTING_VOLUME;
				SET_LOOP_OFFSETS(SFX_BOAT_V12_LOOP)
				m_sQueueSample.m_bReverbFlag = TRUE;
				m_sQueueSample.m_bReleasingSoundFlag = FALSE;
				m_sQueueSample.m_bRequireReflection = FALSE;
				AddSampleToRequestedQueue();
			}
		}
	}
}

#pragma region SCRIPT_OBJECTS
const int SCRIPT_OBJECT_INTENSITY_S = 30;
const int SCRIPT_OBJECT_INTENSITY_L = 80;

void
cAudioManager::ProcessScriptObject(int32 id)
{
	if (MusicManager.m_nMusicMode == MUSICMODE_GAME) {
		cAudioScriptObject* entity = (cAudioScriptObject*)m_asAudioEntities[id].m_pEntity;
		if (entity != nil) {
			m_sQueueSample.m_vecPos = entity->Posn;
			if (m_asAudioEntities[id].m_AudioEvents == 1)
				ProcessOneShotScriptObject(m_asAudioEntities[id].m_awAudioEvent[0]);
			else
				ProcessLoopingScriptObject(entity->AudioId);
		}
	}
}

void
cAudioManager::ProcessOneShotScriptObject(uint8 sound)
{
	CPlayerPed *playerPed;
	uint8 emittingVolume;
	float distSquared;

	static uint8 iSound = 0;

	switch (sound) {
	case SCRIPT_SOUND_POLICE_CELL_DOOR_CLUNK:
		m_sQueueSample.m_fSoundIntensity = 40.0f;
		m_sQueueSample.m_nSampleIndex = SFX_COL_GATE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = 10600;
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		emittingVolume = 60;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		break;
	case SCRIPT_SOUND_GARAGE_DOOR_CLUNK:
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = SFX_COL_CAR_PANEL_2; // huh?
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = 22000;
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
		m_sQueueSample.m_nReleasingVolumeModificator = 4;
		emittingVolume = 60;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		break;
	case SCRIPT_SOUND_SHOOTING_RANGE_TARGET_HIT:
	case SCRIPT_SOUND_BULLET_HIT_GROUND_1:
	case SCRIPT_SOUND_BULLET_HIT_GROUND_2:
	case SCRIPT_SOUND_BULLET_HIT_GROUND_3:
		m_sQueueSample.m_fSoundIntensity = 50.0f;
		m_sQueueSample.m_nSampleIndex = m_anRandomTable[iSound % 5] % 3 + SFX_BULLET_WALL_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
		m_sQueueSample.m_nReleasingVolumeModificator = 9;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		emittingVolume = m_anRandomTable[2] % 20 + 90;
		break;
	case SCRIPT_SOUND_WILLIE_CARD_SWIPE:
		emittingVolume = 70;
		m_sQueueSample.m_fSoundIntensity = 40.0f;
		m_sQueueSample.m_nSampleIndex = SFX_BOMB_BEEP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = 20159;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_fSpeedMultiplier = 1.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		break;
	case SCRIPT_SOUND_MALE_AMBULANCE_OUCH:
	{
		cPedParams pedParams;
		pedParams.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		SetupPedComments(pedParams, SOUND_INJURED_PED_MALE_OUCH);
		return;
	}
	case SCRIPT_SOUND_FEMALE_AMBULANCE_OUCH:
	{
		cPedParams pedParams;
		pedParams.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		SetupPedComments(pedParams, SOUND_INJURED_PED_FEMALE);
		return;
	}
	case SCRIPT_SOUND_SEAPLANE_LOW_FUEL:
		m_sQueueSample.m_fSoundIntensity = 1000.0f;
		m_sQueueSample.m_nSampleIndex = SFX_SEAPLANE_LOW;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		emittingVolume = 100;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_HORN_JEEP); // BUG?
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		break;
	case SCRIPT_SOUND_PAYPHONE_RINGING:
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = SFX_PHONE_RING;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		emittingVolume = 80;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PHONE_RING);
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		break;
	case SCRIPT_SOUND_GLASS_BREAK_L:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = SFX_GLASS_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		emittingVolume = 70;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_SMASH);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_GLASS_BREAK_S:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = SFX_GLASS_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		emittingVolume = 60;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_SMASH);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_GLASS_CRACK:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = SFX_GLASS_CRACK;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		emittingVolume = 70;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_CRACK);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		break;
	case SCRIPT_SOUND_GLASS_LIGHT_BREAK:
		m_sQueueSample.m_fSoundIntensity = 55.0f;
		m_sQueueSample.m_nSampleIndex = (m_anRandomTable[4] & 3) + SFX_GLASS_SHARD_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(2000) + 19000;
		m_sQueueSample.m_nReleasingVolumeModificator = 9;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		emittingVolume = RandomDisplacement(11) + 25;
		break;
	case SCRIPT_SOUND_BOX_DESTROYED_1:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = SFX_WOODEN_BOX_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(1500) + 18600;
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		emittingVolume = m_anRandomTable[2] % 20 + 80;
		break;
	case SCRIPT_SOUND_BOX_DESTROYED_2:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = SFX_CARDBOARD_BOX_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(1500) + 18600;
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		emittingVolume = m_anRandomTable[2] % 20 + 80;
		break;
	case SCRIPT_SOUND_METAL_COLLISION:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 5 + SFX_COL_CAR_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		emittingVolume = m_anRandomTable[2] % 30 + 70;
		break;
	case SCRIPT_SOUND_TIRE_COLLISION:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = SFX_TYRE_BUMP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		emittingVolume = m_anRandomTable[2] % 30 + 60;
		break;
	case SCRIPT_SOUND_HIT_BALL:
		m_sQueueSample.m_fSoundIntensity = 60.0f;
		m_sQueueSample.m_nSampleIndex = SFX_HIT_BALL;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
		m_sQueueSample.m_nReleasingVolumeModificator = 5;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_bRequireReflection = TRUE;
		emittingVolume = m_anRandomTable[2] % 30 + 60;
		break;
	case SCRIPT_SOUND_GUNSHELL_DROP:
		playerPed = FindPlayerPed();
		if (playerPed) {
			switch (playerPed->m_nSurfaceTouched) {
			case SURFACE_GRASS:
			case SURFACE_GRAVEL:
			case SURFACE_MUD_DRY:
			case SURFACE_TRANSPARENT_CLOTH:
			case SURFACE_PED:
			case SURFACE_SAND:
			case SURFACE_RUBBER:
			case SURFACE_HEDGE:
			case SURFACE_SAND_BEACH:
				m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_2;
				m_sQueueSample.m_nFrequency = RandomDisplacement(600) + 10600;
				m_sQueueSample.m_nReleasingVolumeModificator = 18;
				break;
			case SURFACE_WATER:
				return;
			default:
				m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_1;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1500) + 30000;
				m_sQueueSample.m_nReleasingVolumeModificator = 15;
				break;
			}
		} else {
			m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_1;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1500) + 30000;
			m_sQueueSample.m_nReleasingVolumeModificator = 15;
		}
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		emittingVolume = m_anRandomTable[2] % 20 + 30;
		break;
	case SCRIPT_SOUND_GUNSHELL_DROP_SOFT:
		m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_2;
		m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 11000;
		m_sQueueSample.m_nReleasingVolumeModificator = 18;
		m_sQueueSample.m_fSoundIntensity = 20.0f;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		emittingVolume = m_anRandomTable[2] % 20 + 30;
		break;
	default:
		return;
	}

	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < SQR(m_sQueueSample.m_fSoundIntensity)) {
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVolume, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = iSound++;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_nEmittingVolume = emittingVolume;
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_bReverbFlag = TRUE;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessLoopingScriptObject(uint8 sound)
{
	uint8 emittingVolume;
	float distSquared;

	switch(sound) {
	case SCRIPT_SOUND_BANK_ALARM_LOOP:
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDINGS_BANK_ALARM;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_BANK_ALARM;
		emittingVolume = 90;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BUILDINGS_BANK_ALARM);
		m_sQueueSample.m_nReleasingVolumeModificator = 2;
		m_sQueueSample.m_nReleasingVolumeDivider = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_POLICE_CELL_DOOR_SLIDING_LOOP:
	case SCRIPT_SOUND_GARAGE_DOOR_SLIDING_LOOP:
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = SFX_GARAGE_DOOR_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		emittingVolume = 90;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GARAGE_DOOR_LOOP);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_SNORING_LOOP:
		m_sQueueSample.m_fSoundIntensity = 6.0f;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_SNORE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_SNORING;
		emittingVolume = 25;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BUILDING_SNORE);
		m_sQueueSample.m_nReleasingVolumeModificator = 6;
		m_sQueueSample.m_nReleasingVolumeDivider = 3;
		m_sQueueSample.m_fSpeedMultiplier = 3.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_SHOOTING_RANGE_TARGET_MOVING_LOOP:
		m_sQueueSample.m_fSoundIntensity = 40.0f;
		m_sQueueSample.m_nSampleIndex = SFX_TANK_TURRET;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		emittingVolume = 60;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TANK_TURRET);
		m_sQueueSample.m_nReleasingVolumeModificator = 4;
		m_sQueueSample.m_nReleasingVolumeDivider = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_BAR_1:
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_BAR_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_BAR_1;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_BAR_2:
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_BAR_2;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_BAR_2;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_BAR_3:
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_BAR_3;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_BAR_3;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_BAR_4:
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_BAR_4;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_BAR_4;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_MALIBU_1:
		if(MusicManager.m_nPlayingTrack == STREAMED_SOUND_MALIBU_AMBIENT) return;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_MAL1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_MALIBU_1;
		MusicManager.SetMalibuClubTrackPos(SCRIPT_SOUND_NEW_BUILDING_MALIBU_1);
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_MALIBU_2:
		if(MusicManager.m_nPlayingTrack == STREAMED_SOUND_MALIBU_AMBIENT) return;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_MAL2;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_MALIBU_2;
		MusicManager.SetMalibuClubTrackPos(SCRIPT_SOUND_NEW_BUILDING_MALIBU_2);
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_MALIBU_3:
		if(MusicManager.m_nPlayingTrack == STREAMED_SOUND_MALIBU_AMBIENT) return;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_MAL3;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_MALIBU_3;
		MusicManager.SetMalibuClubTrackPos(SCRIPT_SOUND_NEW_BUILDING_MALIBU_3);
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_STRIP_1:
		if(MusicManager.m_nPlayingTrack == STREAMED_SOUND_STRIPCLUB_AMBIENT) return;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_STR1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_STRIP_1;
		MusicManager.SetStripClubTrackPos(SCRIPT_SOUND_NEW_BUILDING_STRIP_1);
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_STRIP_2:
		if(MusicManager.m_nPlayingTrack == STREAMED_SOUND_STRIPCLUB_AMBIENT) return;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_STR2;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_STRIP_2;
		MusicManager.SetStripClubTrackPos(SCRIPT_SOUND_NEW_BUILDING_STRIP_2);
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_STRIP_3:
		if(MusicManager.m_nPlayingTrack == STREAMED_SOUND_STRIPCLUB_AMBIENT) return;
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_STR3;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_STRIP_3;
		MusicManager.SetStripClubTrackPos(SCRIPT_SOUND_NEW_BUILDING_STRIP_3);
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_BUILDING_CHURCH:
		m_sQueueSample.m_nSampleIndex = SFX_BUILDING_CHURCH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CHURCH;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		emittingVolume = 127;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		m_sQueueSample.m_nReleasingVolumeDivider = 15;
		m_sQueueSample.m_fSpeedMultiplier = 4.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_NEW_WATERFALL:
		emittingVolume = 30;
		m_sQueueSample.m_fSoundIntensity = 80.0f;
		m_sQueueSample.m_nSampleIndex = SFX_BOAT_WATER_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = 20812;
		m_sQueueSample.m_nReleasingVolumeModificator = 4;
		m_sQueueSample.m_nReleasingVolumeDivider = 9;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	default: return;
	}

	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if(distSquared < SQR(m_sQueueSample.m_fSoundIntensity)) {
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(emittingVolume, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
		if(m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_bReverbFlag = TRUE;
			m_sQueueSample.m_nEmittingVolume = emittingVolume;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
}
#pragma endregion All the code for script object audio on the map

void
cAudioManager::ProcessWeather(int32 id)
{
	uint8 vol;
	float x;
	float y;
	float modifier;
	float wind;

	static uint8 iSound = 0;

	if (m_asAudioEntities[id].m_AudioEvents != 0 && m_asAudioEntities[id].m_awAudioEvent[0] == SOUND_LIGHTNING) {
		if (m_asAudioEntities[id].m_afVolume[0] >= 10.f) {
			m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_GENERIC_EXTRA;
			m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 4000;
			vol = (m_asAudioEntities[id].m_afVolume[0] - 10.0f) + 40;
		} else {
			m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_2;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 4000;
			vol = (m_asAudioEntities[id].m_afVolume[0]) + 35;
		}
		m_sQueueSample.m_nVolume = vol;
		if (TheCamera.SoundDistUp < 20.0f)
			m_sQueueSample.m_nVolume /= 2;
		if (iSound == 4)
			iSound = 0;
		m_sQueueSample.m_nCounter = iSound++;
		m_sQueueSample.m_nReleasingVolumeModificator = 0;
		m_sQueueSample.m_nOffset = (m_anRandomTable[2] & 15) + 55;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_nLoopCount = 1;
		m_sQueueSample.m_bReleasingSoundFlag = TRUE;
		m_sQueueSample.m_nEmittingVolume = m_sQueueSample.m_nVolume;
		RESET_LOOP_OFFSETS
		m_sQueueSample.m_bReverbFlag = FALSE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
	if (CWeather::Rain > 0.0f && (!CCullZones::CamNoRain() || !CCullZones::PlayerNoRain())) {
		m_sQueueSample.m_nSampleIndex = SFX_RAIN;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RAIN);
		m_sQueueSample.m_nVolume = (uint8)(25.0f * CWeather::Rain);
		m_sQueueSample.m_nCounter = 4;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nReleasingVolumeModificator = 0;
		m_sQueueSample.m_nOffset = 63;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 30;
		m_sQueueSample.m_bReverbFlag = FALSE;
		m_sQueueSample.m_nEmittingVolume = m_sQueueSample.m_nVolume;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
	}
	x = 0.0f;
	y = 0.0f;
	CWindModifiers::FindWindModifier(TheCamera.GetPosition(), &x, &y);
	modifier = Max(Abs(x), Abs(y)) * 10.0f;
	modifier = Min(1.0f, modifier);
	wind = Max(CWeather::Wind, modifier);
	if (wind > 0.0f && CObject::fDistToNearestTree < 75.0f) {
		m_sQueueSample.m_nSampleIndex = SFX_PALM_TREE_LO;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PALM_TREE_LO);
		m_sQueueSample.m_nVolume = (m_anRandomTable[1] % 10 + 45.0f) * (75.0f - CObject::fDistToNearestTree) * (4.0f / 300.0f) * wind;
		m_sQueueSample.m_nCounter = 5;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nReleasingVolumeModificator = 1;
		m_sQueueSample.m_nOffset = 63;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		m_sQueueSample.m_nReleasingVolumeDivider = 7;
		m_sQueueSample.m_bReverbFlag = FALSE;
		m_sQueueSample.m_nEmittingVolume = m_sQueueSample.m_nVolume;
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
		CObject::fDistToNearestTree = 999999.9f;
	}
}

void
cAudioManager::ProcessFrontEnd()
{
	bool8 stereo;
	bool8 processedPickup;
	bool8 processedMission;
	bool8 staticFreq;
	bool8 center;
	int16 sample;

	static uint8 iSound = 0;
	static uint32 cPickupNextFrame = 0;
	static uint32 cPartMisComNextFrame = 0;
	static uint32 radioDial = SFX_RADIO_DIAL_1;

	for (uint32 i = 0; i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; i++) {
		staticFreq = FALSE;
		processedPickup = FALSE;
		center = FALSE;
		processedMission = FALSE;
		stereo = FALSE;
		switch (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i]) {
		case SOUND_WEAPON_SNIPER_SHOT_NO_ZOOM:
			m_sQueueSample.m_nSampleIndex = SFX_ERROR_FIRE_RIFLE;
			break;
		case SOUND_WEAPON_ROCKET_SHOT_NO_ZOOM:
			m_sQueueSample.m_nSampleIndex = SFX_ERROR_FIRE_ROCKET_LAUNCHER;
			break;
		case SOUND_GARAGE_NO_MONEY:
		case SOUND_GARAGE_BAD_VEHICLE:
		case SOUND_GARAGE_BOMB_ALREADY_SET:
			m_sQueueSample.m_nSampleIndex = SFX_WEAPON_LEFT;
			stereo = TRUE;
			staticFreq = TRUE;
			center = TRUE;
			break;
		case SOUND_GARAGE_OPENING:
		case SOUND_71: //case SOUND_41:
		case SOUND_GARAGE_VEHICLE_DECLINED:
		case SOUND_GARAGE_VEHICLE_ACCEPTED:
		case SOUND_EVIDENCE_PICKUP:
		case SOUND_UNLOAD_GOLD:
			stereo = TRUE;
			processedPickup = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_MONEY_LEFT;
			break;
		case SOUND_GARAGE_BOMB1_SET:
		case SOUND_GARAGE_BOMB2_SET:
		case SOUND_GARAGE_BOMB3_SET:
		case SOUND_PICKUP_WEAPON_BOUGHT:
		case SOUND_PICKUP_WEAPON:
			center = TRUE;
			processedPickup = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_WEAPON_LEFT;
			stereo = TRUE;
			break;
		case SOUND_PICKUP_HEALTH:
		case SOUND_81: //case SOUND_4B:
		case SOUND_PICKUP_ADRENALINE:
		case SOUND_PICKUP_ARMOUR:
			stereo = TRUE;
			processedPickup = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_MONEY_LEFT;
			break;
		case SOUND_80:
			stereo = TRUE;
			processedPickup = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_WEAPON_LEFT;
			center = TRUE;
			staticFreq = TRUE;
			break;
		case SOUND_PICKUP_BONUS:
		case SOUND_FRONTEND_MENU_STARTING:
		case SOUND_HUD:
			stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_INFO_LEFT;
			center = TRUE;
			break;
		case SOUND_PICKUP_MONEY:
			stereo = TRUE;
			processedPickup = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_MONEY_LEFT;
			break;
		case SOUND_PICKUP_HIDDEN_PACKAGE:
		case SOUND_PICKUP_PACMAN_PILL:
		case SOUND_PICKUP_PACMAN_PACKAGE:
		case SOUND_PICKUP_FLOAT_PACKAGE:
			center = TRUE;
			processedPickup = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_PART_MISSION_COMPLETE_LEFT;
			stereo = TRUE;
			break;
		case SOUND_RACE_START_3:
		case SOUND_RACE_START_2:
		case SOUND_RACE_START_1:
		case SOUND_PART_MISSION_COMPLETE:
			stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_PART_MISSION_COMPLETE_LEFT;
			processedMission = TRUE;
			center = TRUE;
			break;
		case SOUND_RACE_START_GO:
			stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_GO_LEFT;
			center = TRUE;
			break;
		case SOUND_CLOCK_TICK:
			m_sQueueSample.m_nSampleIndex = SFX_TIMER;
			break;
		case SOUND_FRONTEND_RADIO_TURN_OFF:
		case SOUND_FRONTEND_RADIO_TURN_ON:
			m_sQueueSample.m_nSampleIndex = SFX_RADIO_CLICK;
			break;
		case SOUND_FRONTEND_HURRICANE:
			m_sQueueSample.m_nSampleIndex = SFX_HURRICANE_MA;
			break;
		case SOUND_BULLETTRACE_1:
		case SOUND_BULLETTRACE_2:
			m_sQueueSample.m_nSampleIndex = (m_anRandomTable[0] % 2) + SFX_BULLET_PASS_1;
			break;
		case SOUND_AMMUNATION_IMRAN_ARM_BOMB:
			m_sQueueSample.m_nSampleIndex = SFX_ARM_BOMB;
			break;
		case SOUND_RADIO_CHANGE:
			m_sQueueSample.m_nSampleIndex = (m_anRandomTable[1] % 2) ? radioDial + 1 : radioDial + 2;
			if (m_sQueueSample.m_nSampleIndex > SFX_RADIO_DIAL_12)
				m_sQueueSample.m_nSampleIndex -= 12;
			radioDial = m_sQueueSample.m_nSampleIndex;
			break;
		case SOUND_FRONTEND_HIGHLIGHT_OPTION:
			stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_FE_HIGHLIGHT_LEFT;
			break;
		case SOUND_FRONTEND_ENTER_OR_ADJUST:
			stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_FE_SELECT_LEFT;
			break;
		case SOUND_FRONTEND_BACK:
			stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_FE_BACK_LEFT;
			break;
		case SOUND_FRONTEND_FAIL:
			stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_FE_ERROR_LEFT;
			break;
		case SOUND_FRONTEND_AUDIO_TEST:
			m_sQueueSample.m_nSampleIndex = m_anRandomTable[0] % 3 + SFX_FE_NOISE_BURST_1;
			break;
		default:
			continue;
		}

		if (processedPickup) {
			if (m_FrameCounter <= cPickupNextFrame)
				continue;
			cPickupNextFrame = m_FrameCounter + 5;
		} else if (processedMission) {
			if (m_FrameCounter <= cPartMisComNextFrame)
				continue;
			cPartMisComNextFrame = m_FrameCounter + 5;
		}

		sample = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i];

		if (sample == SOUND_FRONTEND_RADIO_TURN_OFF)
			m_sQueueSample.m_nFrequency = 28509;
		else if (sample == SOUND_FRONTEND_RADIO_TURN_ON)
			m_sQueueSample.m_nFrequency = 32000;
		else if (sample == SOUND_BULLETTRACE_1 || sample == SOUND_BULLETTRACE_2) {
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 32);
		} else if (staticFreq)
			m_sQueueSample.m_nFrequency = 5382;
		else
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);

		m_sQueueSample.m_nVolume = 127;
		if (m_sQueueSample.m_nSampleIndex == SFX_HURRICANE_MA && CWeather::Wind > 1.0f)
			m_sQueueSample.m_nVolume = (CWeather::Wind - 1.0f) * m_sQueueSample.m_nVolume;
		m_sQueueSample.m_nCounter = iSound++;
		m_sQueueSample.m_nLoopCount = 1;
		m_sQueueSample.m_bReleasingSoundFlag = TRUE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_FRONT_END_MENU;
		m_sQueueSample.m_nReleasingVolumeModificator = 0;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_nEmittingVolume = m_sQueueSample.m_nVolume;
		RESET_LOOP_OFFSETS
		if (stereo) {
			m_sQueueSample.m_nOffset = 0;
			m_sQueueSample.m_fDistance = 1.0f;
		} else {
			sample = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i];
			if (sample == SOUND_BULLETTRACE_1) {
				m_sQueueSample.m_nOffset = 20;
				m_sQueueSample.m_nVolume = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
				m_sQueueSample.m_nReleasingVolumeModificator = 10;
				m_sQueueSample.m_fDistance = 100.0f;
			} else if (sample == SOUND_BULLETTRACE_2) {
				m_sQueueSample.m_nOffset = 107;
				m_sQueueSample.m_nVolume = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
				m_sQueueSample.m_nReleasingVolumeModificator = 10;
				m_sQueueSample.m_fDistance = 100.0f;
			} else {
				m_sQueueSample.m_nOffset = 63;
				m_sQueueSample.m_fDistance = 1.0f;
			}
		}
		m_sQueueSample.m_bReverbFlag = FALSE;
		m_sQueueSample.m_bRequireReflection = FALSE;
		AddSampleToRequestedQueue();
		if (stereo) {
			++m_sQueueSample.m_nSampleIndex;
			m_sQueueSample.m_nCounter = iSound++;
			m_sQueueSample.m_nOffset = 127 - m_sQueueSample.m_nOffset;
			AddSampleToRequestedQueue();
		}
		if (center) {
			++m_sQueueSample.m_nSampleIndex;
			m_sQueueSample.m_nCounter = iSound++;
			m_sQueueSample.m_nOffset = 63;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			AddSampleToRequestedQueue();
		}
	}
}

/*void
cAudioManager::ProcessCrane()
{
	CCrane *crane = (CCrane *)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity;
	float distSquared;
	bool8 distCalculated = FALSE;
	static const int intensity = 80;

	if (crane) {
		if (crane->m_nCraneStatus == CCrane::ACTIVATED) {
			if (crane->m_nCraneState != CCrane::IDLE) {
				m_sQueueSample.m_vecPos = crane->m_pCraneEntity->GetPosition();
				distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
				if (distSquared < SQR(intensity)) {
					CalculateDistance(distCalculated, distSquared);
					m_sQueueSample.m_nVolume = ComputeVolume(100, 80.f, m_sQueueSample.m_fDistance);
					if (m_sQueueSample.m_nVolume != 0) {
						m_sQueueSample.m_nCounter = 0;
						m_sQueueSample.m_nSampleIndex = SFX_CRANE_MAGNET;
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						m_sQueueSample.m_bIs2D = FALSE;
						m_sQueueSample.m_nReleasingVolumeModificator = 2;
						m_sQueueSample.m_nFrequency = 6000;
						m_sQueueSample.m_nLoopCount = 0;
						m_sQueueSample.m_nEmittingVolume = 100;
						SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
						m_sQueueSample.m_fSpeedMultiplier = 4.0f;
						m_sQueueSample.m_fSoundIntensity = intensity;
						m_sQueueSample.m_bReleasingSoundFlag = FALSE;
						m_sQueueSample.m_nReleasingVolumeDivider = 3;
						m_sQueueSample.m_bReverbFlag = TRUE;
						m_sQueueSample.m_bRequireReflection = FALSE;
						AddSampleToRequestedQueue();
					}
					if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents) {
						m_sQueueSample.m_nCounter = 1;
						m_sQueueSample.m_nSampleIndex = SFX_COL_CAR_2;
						m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_COL_CAR_2);
						m_sQueueSample.m_nLoopCount = 1;
						m_sQueueSample.m_bReleasingSoundFlag = TRUE;
						m_sQueueSample.m_bReverbFlag = TRUE;
						m_sQueueSample.m_bRequireReflection = TRUE;
						AddSampleToRequestedQueue();
					}
				}
			}
		}
	}
}*/

void
cAudioManager::ProcessProjectiles()
{
	uint8 emittingVol;
	float distSquared;

	for (int32 i = 0; i < NUM_PROJECTILES; i++) {
		if (CProjectileInfo::GetProjectileInfo(i)->m_bInUse) {
			switch (CProjectileInfo::GetProjectileInfo(i)->m_eWeaponType) {
			case WEAPONTYPE_TEARGAS:
				emittingVol = 80;
				m_sQueueSample.m_fSoundIntensity = 40.0f;
				m_sQueueSample.m_nSampleIndex = SFX_PALM_TREE_LO;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = 13879;
				m_sQueueSample.m_nReleasingVolumeModificator = 7;
				break;
			case WEAPONTYPE_MOLOTOV:
				emittingVol = 50;
				m_sQueueSample.m_fSoundIntensity = 30.0f;
				m_sQueueSample.m_nSampleIndex = SFX_PED_ON_FIRE;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = 32 * SampleManager.GetSampleBaseFrequency(SFX_PED_ON_FIRE) / 25;
				m_sQueueSample.m_nReleasingVolumeModificator = 7;
				break;
			case WEAPONTYPE_ROCKET:
				emittingVol = 127;
				m_sQueueSample.m_fSoundIntensity = 90.0f;
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_FLY;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ROCKET_FLY);
				m_sQueueSample.m_nReleasingVolumeModificator = 3;
				break;
			default:
				return;
			}
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_vecPos = CProjectileInfo::ms_apProjectile[i]->GetPosition();
			distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(m_sQueueSample.m_fSoundIntensity)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, m_sQueueSample.m_fSoundIntensity, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume != 0) {
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_nEmittingVolume = emittingVol;
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_bReleasingSoundFlag = FALSE;
					m_sQueueSample.m_bReverbFlag = TRUE;
					m_sQueueSample.m_bRequireReflection = FALSE;
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::ProcessGarages()
{
	const float SOUND_INTENSITY = 80.0f;

	CEntity *entity;
	uint8 state;
	uint32 sampleIndex;
	uint8 j;
	float distSquared;
	bool8 distCalculated;

	static uint8 iSound = 32;

	for (uint32 i = 0; i < CGarages::NumGarages; ++i) {
		if (CGarages::aGarages[i].m_eGarageType == GARAGE_NONE)
			continue;
		entity = CGarages::aGarages[i].m_pDoor1;
		if (entity == nil)
			continue;
		m_sQueueSample.m_vecPos = entity->GetPosition();
		distCalculated = FALSE;
		distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distSquared < SQR(SOUND_INTENSITY)) {
			state = CGarages::aGarages[i].m_eGarageState;
			// while is here just to exit prematurely and avoid goto
			while (state == GS_OPENING || state == GS_CLOSING || state == GS_AFTERDROPOFF) {
				CalculateDistance(distCalculated, distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(90, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume != 0) {
					if (CGarages::aGarages[i].m_eGarageType == GARAGE_CRUSHER) {
						if (CGarages::aGarages[i].m_eGarageState == GS_AFTERDROPOFF) {
							if (m_FrameCounter & 1) {
								if (m_anRandomTable[1] & 1)
									sampleIndex = m_anRandomTable[2] % 5 + SFX_COL_CAR_1;
								else
									sampleIndex = m_anRandomTable[2] % 6 + SFX_COL_CAR_PANEL_1;
								m_sQueueSample.m_nSampleIndex = sampleIndex;
								m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex) / 2;
								m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 16);
								m_sQueueSample.m_nLoopCount = 1;
								m_sQueueSample.m_bReleasingSoundFlag = TRUE;
								m_sQueueSample.m_nCounter = iSound++;
								if (iSound < 32)
									iSound = 32;
							} else break; // premature exit to go straight to the for loop
						} else {
							m_sQueueSample.m_nSampleIndex = SFX_FISHING_BOAT_IDLE;
							m_sQueueSample.m_nFrequency = 6543;

							m_sQueueSample.m_nCounter = i;
							m_sQueueSample.m_nLoopCount = 0;
							m_sQueueSample.m_nReleasingVolumeDivider = 3;
							m_sQueueSample.m_bReleasingSoundFlag = FALSE;
						}
					} else {
						m_sQueueSample.m_nSampleIndex = SFX_GARAGE_DOOR_LOOP;
						m_sQueueSample.m_nFrequency = 13961;

						m_sQueueSample.m_nCounter = i;
						m_sQueueSample.m_nLoopCount = 0;
						m_sQueueSample.m_nReleasingVolumeDivider = 3;
						m_sQueueSample.m_bReleasingSoundFlag = FALSE;
					}

					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nReleasingVolumeModificator = 3;
					m_sQueueSample.m_nEmittingVolume = 90;
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
					m_sQueueSample.m_bReverbFlag = TRUE;
					m_sQueueSample.m_bRequireReflection = FALSE;
					AddSampleToRequestedQueue();
				}
				break;
			}
		}
		for (j = 0; j < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; ++j) {
			switch (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[j]) {
			case SOUND_GARAGE_DOOR_CLOSED:
			case SOUND_GARAGE_DOOR_OPENED:
				if (distSquared < SQR(SOUND_INTENSITY)) {
					CalculateDistance(distCalculated, distSquared);
					m_sQueueSample.m_nVolume = ComputeVolume(60, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
					if (m_sQueueSample.m_nVolume != 0) {
						if (CGarages::aGarages[i].m_eGarageType == GARAGE_CRUSHER) {
							m_sQueueSample.m_nSampleIndex = SFX_COL_CAR_PANEL_2;
							m_sQueueSample.m_nFrequency = 6735;
						} else if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[j] == SOUND_GARAGE_DOOR_OPENED) {
							m_sQueueSample.m_nSampleIndex = SFX_COL_CAR_PANEL_2;
							m_sQueueSample.m_nFrequency = 22000;
						} else {
							m_sQueueSample.m_nSampleIndex = SFX_COL_GARAGE_DOOR_1;
							m_sQueueSample.m_nFrequency = 18000;
						}
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						m_sQueueSample.m_nReleasingVolumeModificator = 4;
						m_sQueueSample.m_nEmittingVolume = 60;
						m_sQueueSample.m_fSpeedMultiplier = 0.0f;
						m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
						m_sQueueSample.m_bReverbFlag = TRUE; 
						m_sQueueSample.m_bIs2D = FALSE;
						m_sQueueSample.m_bReleasingSoundFlag = TRUE;
						m_sQueueSample.m_nLoopCount = 1;
						RESET_LOOP_OFFSETS
						m_sQueueSample.m_nCounter = iSound++;
						if (iSound < 32)
							iSound = 32;
						m_sQueueSample.m_bRequireReflection = TRUE;
						AddSampleToRequestedQueue();
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void
cAudioManager::ProcessFireHydrant()
{
	const float SOUND_INTENSITY = 35;

	float distSquared;
	bool8 distCalculated = FALSE;

	m_sQueueSample.m_vecPos = ((CEntity *)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity)->GetPosition();
	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < SQR(SOUND_INTENSITY)) {
		CalculateDistance(distCalculated, distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(40, 35.0f, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
			m_sQueueSample.m_nReleasingVolumeModificator = 4;
			m_sQueueSample.m_nFrequency = 15591;
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_nEmittingVolume = 40;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			AddSampleToRequestedQueue();
		}
	}
}
#ifdef GTA_BRIDGE
#pragma region BRIDGE
const int bridgeIntensity = 400;

void
cAudioManager::ProcessBridge()
{
	float dist;
	bool8 distCalculated = FALSE;

	if (CBridge::pLiftRoad) {
		m_sQueueSample.m_vecPos = CBridge::pLiftRoad->GetPosition();
		dist = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (dist < SQR(450.0f)) {
			CalculateDistance(distCalculated, dist);
			switch (CBridge::State) {
			case STATE_BRIDGE_LOCKED:
			case STATE_LIFT_PART_IS_UP:
			case STATE_LIFT_PART_ABOUT_TO_MOVE_UP:
				ProcessBridgeWarning();
				break;
			case STATE_LIFT_PART_MOVING_DOWN:
			case STATE_LIFT_PART_MOVING_UP:
				ProcessBridgeWarning();
				ProcessBridgeMotor();
				break;
			default:
				break;
			}
			ProcessBridgeOneShots();
		}
	}
}

void
cAudioManager::ProcessBridgeWarning()
{
	if (CStats::CommercialPassed && m_sQueueSample.m_fDistance < 450.f) {
		m_sQueueSample.m_nVolume = ComputeVolume(100, 450.f, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_nSampleIndex = SFX_BRIDGE_OPEN_WARNING;
			m_sQueueSample.m_nBankIndex = SAMPLEBANK_EXTRAS;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BRIDGE_OPEN_WARNING);
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = 100;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = 450.0f;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 8;
			m_sQueueSample.m_bReverbFlag = FALSE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessBridgeMotor()
{
	if (m_sQueueSample.m_fDistance < bridgeIntensity) {
		m_sQueueSample.m_nVolume = ComputeVolume(MAX_VOLUME, bridgeIntensity, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 1;
			m_sQueueSample.m_nSampleIndex = SFX_FISHING_BOAT_IDLE; // todo check sfx name
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_nFrequency = 5500;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nEmittingVolume = MAX_VOLUME;
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = bridgeIntensity;
			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
			m_sQueueSample.m_nReleasingVolumeDivider = 3;
			m_sQueueSample.m_bReverbFlag = FALSE;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessBridgeOneShots()
{
	if (CBridge::State == STATE_LIFT_PART_IS_UP && CBridge::OldState == STATE_LIFT_PART_MOVING_UP)
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	else if (CBridge::State == STATE_LIFT_PART_IS_DOWN && CBridge::OldState == STATE_LIFT_PART_MOVING_DOWN)
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	else if (CBridge::State == STATE_LIFT_PART_MOVING_UP && CBridge::OldState == STATE_LIFT_PART_ABOUT_TO_MOVE_UP)
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	else if (CBridge::State == STATE_LIFT_PART_MOVING_DOWN && CBridge::OldState == STATE_LIFT_PART_IS_UP)
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	else return;

	if (m_sQueueSample.m_fDistance < bridgeIntensity) {
		m_sQueueSample.m_nVolume = ComputeVolume(MAX_VOLUME, bridgeIntensity, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume != 0) {
			m_sQueueSample.m_nCounter = 2;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nReleasingVolumeModificator = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_nEmittingVolume = MAX_VOLUME;
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_fSoundIntensity = bridgeIntensity;
			m_sQueueSample.m_bReleasingSoundFlag = TRUE;
			m_sQueueSample.m_bReverbFlag = FALSE;
			m_sQueueSample.m_bRequireReflection = FALSE;
			AddSampleToRequestedQueue();
		}
	}
}
#pragma endregion
#endif

#pragma region MISSION_AUDIO
bool8 g_bMissionAudioLoadFailed[MISSION_AUDIO_SLOTS];

struct MissionAudioData {
	const char *m_pName;
	int32 m_nId;
};


const MissionAudioData MissionAudioNameSfxAssoc[] = {
	{"mobring", STREAMED_SOUND_MISSION_MOBR1},    {"pagring", STREAMED_SOUND_MISSION_PAGER},    {"carrev", STREAMED_SOUND_MISSION_CARREV},
	{"bikerev", STREAMED_SOUND_MISSION_BIKEREV},  {"liftop", STREAMED_SOUND_MISSION_LIFTOP},    {"liftcl", STREAMED_SOUND_MISSION_LIFTCL},
	{"liftrun", STREAMED_SOUND_MISSION_LIFTRUN},  {"liftbel", STREAMED_SOUND_MISSION_LIFTBEL},  {"inlift", STREAMED_SOUND_MISSION_INLIFT},
	{"caml", STREAMED_SOUND_MISSION_CAMERAL},     {"camr", STREAMED_SOUND_MISSION_CAMERAR},     {"cheer1", STREAMED_SOUND_MISSION_CHEER1},
	{"cheer2", STREAMED_SOUND_MISSION_CHEER2},    {"cheer3", STREAMED_SOUND_MISSION_CHEER3},    {"cheer4", STREAMED_SOUND_MISSION_CHEER4},
	{"ooh1", STREAMED_SOUND_MISSION_OOH1},        {"ooh2", STREAMED_SOUND_MISSION_OOH2},        {"race1", STREAMED_SOUND_MISSION_RACE1},
	{"race2", STREAMED_SOUND_MISSION_RACE2},      {"race3", STREAMED_SOUND_MISSION_RACE3},      {"race4", STREAMED_SOUND_MISSION_RACE4},
	{"race5", STREAMED_SOUND_MISSION_RACE5},      {"race6", STREAMED_SOUND_MISSION_RACE6},      {"race7", STREAMED_SOUND_MISSION_RACE7},
	{"race8", STREAMED_SOUND_MISSION_RACE8},      {"race9", STREAMED_SOUND_MISSION_RACE9},      {"race10", STREAMED_SOUND_MISSION_RACE10},
	{"race11", STREAMED_SOUND_MISSION_RACE11},    {"race12", STREAMED_SOUND_MISSION_RACE12},    {"race13", STREAMED_SOUND_MISSION_RACE13},
	{"race14", STREAMED_SOUND_MISSION_RACE14},    {"race15", STREAMED_SOUND_MISSION_RACE15},    {"hot1", STREAMED_SOUND_MISSION_HOT1},
	{"hot2", STREAMED_SOUND_MISSION_HOT2},        {"hot3", STREAMED_SOUND_MISSION_HOT3},        {"hot4", STREAMED_SOUND_MISSION_HOT4},
	{"hot5", STREAMED_SOUND_MISSION_HOT5},        {"hot6", STREAMED_SOUND_MISSION_HOT6},        {"hot7", STREAMED_SOUND_MISSION_HOT7},
	{"hot8", STREAMED_SOUND_MISSION_HOT8},        {"hot9", STREAMED_SOUND_MISSION_HOT9},        {"hot10", STREAMED_SOUND_MISSION_HOT10},
	{"hot11", STREAMED_SOUND_MISSION_HOT11},      {"hot12", STREAMED_SOUND_MISSION_HOT12},      {"hot13", STREAMED_SOUND_MISSION_HOT13},
	{"hot14", STREAMED_SOUND_MISSION_HOT14},      {"hot15", STREAMED_SOUND_MISSION_HOT15},      {"lanstp1", STREAMED_SOUND_MISSION_LANSTP1},
	{"lanstp2", STREAMED_SOUND_MISSION_LANSTP2},  {"lanamu1", STREAMED_SOUND_MISSION_LANAMU1},  {"lanamu2", STREAMED_SOUND_MISSION_LANAMU2},
	{"airhrnl", STREAMED_SOUND_MISSION_AIRHORNL}, {"airhrnr", STREAMED_SOUND_MISSION_AIRHORNR}, {"sniper", STREAMED_SOUND_MISSION_SNIPSCRL},
	{"snipsh", STREAMED_SOUND_MISSION_SNIPSHORT}, {"bloroof", STREAMED_SOUND_MISSION_BLOWROOF}, {"sfx_01", STREAMED_SOUND_MISSION_SFX_01},
	{"sfx_02", STREAMED_SOUND_MISSION_SFX_02},    {"LAW1_1", STREAMED_SOUND_MISSION_LAW1_1},    {"LAW1_2", STREAMED_SOUND_MISSION_LAW1_2},
	{"LAW1_3", STREAMED_SOUND_MISSION_LAW1_3},    {"LAW1_4", STREAMED_SOUND_MISSION_LAW1_4},    {"LAW1_5", STREAMED_SOUND_MISSION_LAW1_5},
	{"LAW1_6", STREAMED_SOUND_MISSION_LAW1_6},    {"LAW1_7", STREAMED_SOUND_MISSION_LAW1_7},    {"LAW1_8", STREAMED_SOUND_MISSION_LAW1_8},
	{"LAW1_9", STREAMED_SOUND_MISSION_LAW1_9},    {"LAW1_10", STREAMED_SOUND_MISSION_LAW1_10},  {"LAW2_1", STREAMED_SOUND_MISSION_LAW2_1},
	{"LAW2_2", STREAMED_SOUND_MISSION_LAW2_2},    {"LAW2_3", STREAMED_SOUND_MISSION_LAW2_3},    {"LAW2_4", STREAMED_SOUND_MISSION_LAW2_4},
	{"LAW2_5", STREAMED_SOUND_MISSION_LAW2_5},    {"LAW2_6", STREAMED_SOUND_MISSION_LAW2_6},    {"LAW2_7", STREAMED_SOUND_MISSION_LAW2_7},
	{"LAW2_8", STREAMED_SOUND_MISSION_LAW2_8},    {"LAW2_9", STREAMED_SOUND_MISSION_LAW2_9},    {"LAW2_10", STREAMED_SOUND_MISSION_LAW2_10},
	{"LAW3_1", STREAMED_SOUND_MISSION_LAW3_1},    {"LAW3_2", STREAMED_SOUND_MISSION_LAW3_2},    {"LAW3_3", STREAMED_SOUND_MISSION_LAW3_3},
	{"LAW3_4", STREAMED_SOUND_MISSION_LAW3_4},    {"LAW3_5", STREAMED_SOUND_MISSION_LAW3_5},    {"LAW3_6", STREAMED_SOUND_MISSION_LAW3_6},
	{"LAW3_10", STREAMED_SOUND_MISSION_LAW3_10},  {"LAW3_11", STREAMED_SOUND_MISSION_LAW3_11},  {"LAW3_12", STREAMED_SOUND_MISSION_LAW3_12},
	{"LAW3_13", STREAMED_SOUND_MISSION_LAW3_13},  {"LAW3_14", STREAMED_SOUND_MISSION_LAW3_14},  {"LAW3_16", STREAMED_SOUND_MISSION_LAW3_16},
	{"LAW3_17", STREAMED_SOUND_MISSION_LAW3_17},  {"LAW3_18", STREAMED_SOUND_MISSION_LAW3_18},  {"LAW3_19", STREAMED_SOUND_MISSION_LAW3_19},
	{"LAW3_20", STREAMED_SOUND_MISSION_LAW3_20},  {"LAW3_21", STREAMED_SOUND_MISSION_LAW3_21},  {"LAW3_22", STREAMED_SOUND_MISSION_LAW3_22},
	{"LAW3_23", STREAMED_SOUND_MISSION_LAW3_23},  {"LAW3_24", STREAMED_SOUND_MISSION_LAW3_24},  {"LAW3_25", STREAMED_SOUND_MISSION_LAW3_25},
	{"LAW4_1a", STREAMED_SOUND_MISSION_LAW4_1A},  {"LAW4_1b", STREAMED_SOUND_MISSION_LAW4_1B},  {"LAW4_1c", STREAMED_SOUND_MISSION_LAW4_1C},
	{"LAW4_1d", STREAMED_SOUND_MISSION_LAW4_1D},  {"LAW4_10", STREAMED_SOUND_MISSION_LAW4_10},  {"LAW4_3", STREAMED_SOUND_MISSION_LAW4_3},
	{"LAW4_4", STREAMED_SOUND_MISSION_LAW4_4},    {"LAW4_5", STREAMED_SOUND_MISSION_LAW4_5},    {"LAW4_6", STREAMED_SOUND_MISSION_LAW4_6},
	{"LAW4_7", STREAMED_SOUND_MISSION_LAW4_7},    {"LAW4_8", STREAMED_SOUND_MISSION_LAW4_8},    {"LAW4_9", STREAMED_SOUND_MISSION_LAW4_9},
	{"COL1_1", STREAMED_SOUND_MISSION_COL1_1},    {"COL1_2", STREAMED_SOUND_MISSION_COL1_2},    {"COL1_3", STREAMED_SOUND_MISSION_COL1_3},
	{"COL1_4", STREAMED_SOUND_MISSION_COL1_4},    {"COL1_5", STREAMED_SOUND_MISSION_COL1_5},    {"COL1_6", STREAMED_SOUND_MISSION_COL1_6},
	{"COL1_7", STREAMED_SOUND_MISSION_COL1_7},    {"COL1_8", STREAMED_SOUND_MISSION_COL1_8},    {"COL2_1", STREAMED_SOUND_MISSION_COL2_1},
	{"COL2_2", STREAMED_SOUND_MISSION_COL2_2},    {"COL2_3", STREAMED_SOUND_MISSION_COL2_3},    {"COL2_4", STREAMED_SOUND_MISSION_COL2_4},
	{"COL2_5", STREAMED_SOUND_MISSION_COL2_5},    {"COL2_6a", STREAMED_SOUND_MISSION_COL2_6A},  {"COL2_7", STREAMED_SOUND_MISSION_COL2_7},
	{"COL2_8", STREAMED_SOUND_MISSION_COL2_8},    {"COL2_9", STREAMED_SOUND_MISSION_COL2_9},    {"COL2_10", STREAMED_SOUND_MISSION_COL2_10},
	{"COL2_11", STREAMED_SOUND_MISSION_COL2_11},  {"COL2_12", STREAMED_SOUND_MISSION_COL2_12},  {"COL2_13", STREAMED_SOUND_MISSION_COL2_13},
	{"COL2_14", STREAMED_SOUND_MISSION_COL2_14},  {"COL2_15", STREAMED_SOUND_MISSION_COL2_15},  {"COL2_16", STREAMED_SOUND_MISSION_COL2_16},
	{"COL3_1", STREAMED_SOUND_MISSION_COL3_1},    {"COL3_2", STREAMED_SOUND_MISSION_COL3_2},    {"COL3_2a", STREAMED_SOUND_MISSION_COL3_2A},
	{"COL3_2b", STREAMED_SOUND_MISSION_COL3_2B},  {"COL3_3", STREAMED_SOUND_MISSION_COL3_3},    {"COL3_4", STREAMED_SOUND_MISSION_COL3_4},
	{"COL3_5", STREAMED_SOUND_MISSION_COL3_5},    {"COL3_6", STREAMED_SOUND_MISSION_COL3_6},    {"COL3_7", STREAMED_SOUND_MISSION_COL3_7},
	{"COL3_8", STREAMED_SOUND_MISSION_COL3_8},    {"COL3_9", STREAMED_SOUND_MISSION_COL3_9},    {"COL3_10", STREAMED_SOUND_MISSION_COL3_10},
	{"COL3_11", STREAMED_SOUND_MISSION_COL3_11},  {"COL3_12", STREAMED_SOUND_MISSION_COL3_12},  {"COL3_13", STREAMED_SOUND_MISSION_COL3_13},
	{"COL3_14", STREAMED_SOUND_MISSION_COL3_14},  {"COL3_15", STREAMED_SOUND_MISSION_COL3_15},  {"COL3_16", STREAMED_SOUND_MISSION_COL3_16},
	{"COL3_17", STREAMED_SOUND_MISSION_COL3_17},  {"COL3_18", STREAMED_SOUND_MISSION_COL3_18},  {"COL3_19", STREAMED_SOUND_MISSION_COL3_19},
	{"COL3_20", STREAMED_SOUND_MISSION_COL3_20},  {"COL3_21", STREAMED_SOUND_MISSION_COL3_21},  {"COL3_23", STREAMED_SOUND_MISSION_COL3_23},
	{"COL3_24", STREAMED_SOUND_MISSION_COL3_24},  {"COL3_25", STREAMED_SOUND_MISSION_COL3_25},  {"COL4_1", STREAMED_SOUND_MISSION_COL4_1},
	{"COL4_2", STREAMED_SOUND_MISSION_COL4_2},    {"COL4_3", STREAMED_SOUND_MISSION_COL4_3},    {"COL4_4", STREAMED_SOUND_MISSION_COL4_4},
	{"COL4_5", STREAMED_SOUND_MISSION_COL4_5},    {"COL4_6", STREAMED_SOUND_MISSION_COL4_6},    {"COL4_7", STREAMED_SOUND_MISSION_COL4_7},
	{"COL4_8", STREAMED_SOUND_MISSION_COL4_8},    {"COL4_9", STREAMED_SOUND_MISSION_COL4_9},    {"COL4_10", STREAMED_SOUND_MISSION_COL4_10},
	{"COL4_11", STREAMED_SOUND_MISSION_COL4_11},  {"COL4_12", STREAMED_SOUND_MISSION_COL4_12},  {"COL4_13", STREAMED_SOUND_MISSION_COL4_13},
	{"COL4_14", STREAMED_SOUND_MISSION_COL4_14},  {"COL4_15", STREAMED_SOUND_MISSION_COL4_15},  {"COL4_16", STREAMED_SOUND_MISSION_COL4_16},
	{"COL4_17", STREAMED_SOUND_MISSION_COL4_17},  {"COL4_18", STREAMED_SOUND_MISSION_COL4_18},  {"COL4_19", STREAMED_SOUND_MISSION_COL4_19},
	{"COL4_20", STREAMED_SOUND_MISSION_COL4_20},  {"COL4_21", STREAMED_SOUND_MISSION_COL4_21},  {"COL4_22", STREAMED_SOUND_MISSION_COL4_22},
	{"COL4_23", STREAMED_SOUND_MISSION_COL4_23},  {"COL4_24", STREAMED_SOUND_MISSION_COL4_24},  {"COL4_25", STREAMED_SOUND_MISSION_COL4_25},
	{"COL4_26", STREAMED_SOUND_MISSION_COL4_26},  {"COL5_1", STREAMED_SOUND_MISSION_COL5_1},    {"COL5_2", STREAMED_SOUND_MISSION_COL5_2},
	{"COL5_3", STREAMED_SOUND_MISSION_COL5_3},    {"COL5_4", STREAMED_SOUND_MISSION_COL5_4},    {"COL5_5", STREAMED_SOUND_MISSION_COL5_5},
	{"COL5_6", STREAMED_SOUND_MISSION_COL5_6},    {"COL5_7", STREAMED_SOUND_MISSION_COL5_7},    {"COL5_8", STREAMED_SOUND_MISSION_COL5_8},
	{"COL5_9", STREAMED_SOUND_MISSION_COL5_9},    {"COL5_10", STREAMED_SOUND_MISSION_COL5_10},  {"COL5_11", STREAMED_SOUND_MISSION_COL5_11},
	{"COL5_12", STREAMED_SOUND_MISSION_COL5_12},  {"COL5_13", STREAMED_SOUND_MISSION_COL5_13},  {"COL5_14", STREAMED_SOUND_MISSION_COL5_14},
	{"COL5_15", STREAMED_SOUND_MISSION_COL5_15},  {"COL5_16", STREAMED_SOUND_MISSION_COL5_16},  {"COL5_17", STREAMED_SOUND_MISSION_COL5_17},
	{"COL5_18", STREAMED_SOUND_MISSION_COL5_18},  {"COL5_19", STREAMED_SOUND_MISSION_COL5_19},  {"COL5_20", STREAMED_SOUND_MISSION_COL5_20},
	{"COL5_21", STREAMED_SOUND_MISSION_COL5_21},  {"COL5_22", STREAMED_SOUND_MISSION_COL5_22},  {"COK1_1", STREAMED_SOUND_MISSION_COK1_1},
	{"COK1_2", STREAMED_SOUND_MISSION_COK1_2},    {"COK1_3", STREAMED_SOUND_MISSION_COK1_3},    {"COK1_4", STREAMED_SOUND_MISSION_COK1_4},
	{"COK1_5", STREAMED_SOUND_MISSION_COK1_5},    {"COK1_6", STREAMED_SOUND_MISSION_COK1_6},    {"COK2_1", STREAMED_SOUND_MISSION_COK2_1},
	{"COK2_2", STREAMED_SOUND_MISSION_COK2_2},    {"COK2_3", STREAMED_SOUND_MISSION_COK2_3},    {"COK2_4", STREAMED_SOUND_MISSION_COK2_4},
	{"COK2_5", STREAMED_SOUND_MISSION_COK2_5},    {"COK2_6", STREAMED_SOUND_MISSION_COK2_6},    {"COK2_7a", STREAMED_SOUND_MISSION_COK2_7A},
	{"COK2_7b", STREAMED_SOUND_MISSION_COK2_7B},  {"COK2_7c", STREAMED_SOUND_MISSION_COK2_7C},  {"COK2_8a", STREAMED_SOUND_MISSION_COK2_8A},
	{"COK2_8b", STREAMED_SOUND_MISSION_COK2_8B},  {"COK2_8c", STREAMED_SOUND_MISSION_COK2_8C},  {"COK2_8d", STREAMED_SOUND_MISSION_COK2_8D},
	{"COK2_9", STREAMED_SOUND_MISSION_COK2_9},    {"COK210a", STREAMED_SOUND_MISSION_COK210A},  {"COK210b", STREAMED_SOUND_MISSION_COK210B},
	{"COK210c", STREAMED_SOUND_MISSION_COK210C},  {"COK212a", STREAMED_SOUND_MISSION_COK212A},  {"COK212b", STREAMED_SOUND_MISSION_COK212B},
	{"COK2_13", STREAMED_SOUND_MISSION_COK2_13},  {"COK2_14", STREAMED_SOUND_MISSION_COK2_14},  {"COK2_15", STREAMED_SOUND_MISSION_COK2_15},
	{"COK2_16", STREAMED_SOUND_MISSION_COK2_16},  {"COK2_20", STREAMED_SOUND_MISSION_COK2_20},  {"COK2_21", STREAMED_SOUND_MISSION_COK2_21},
	{"COK2_22", STREAMED_SOUND_MISSION_COK2_22},  {"COK3_1", STREAMED_SOUND_MISSION_COK3_1},    {"COK3_2", STREAMED_SOUND_MISSION_COK3_2},
	{"COK3_3", STREAMED_SOUND_MISSION_COK3_3},    {"COK3_4", STREAMED_SOUND_MISSION_COK3_4},    {"COK4_1", STREAMED_SOUND_MISSION_COK4_1},
	{"COK4_2", STREAMED_SOUND_MISSION_COK4_2},    {"COK4_3", STREAMED_SOUND_MISSION_COK4_3},    {"COK4_4", STREAMED_SOUND_MISSION_COK4_4},
	{"COK4_5", STREAMED_SOUND_MISSION_COK4_5},    {"COK4_6", STREAMED_SOUND_MISSION_COK4_6},    {"COK4_7", STREAMED_SOUND_MISSION_COK4_7},
	{"COK4_8", STREAMED_SOUND_MISSION_COK4_8},    {"COK4_9", STREAMED_SOUND_MISSION_COK4_9},    {"COK4_9A", STREAMED_SOUND_MISSION_COK4_9A},
	{"COK4_10", STREAMED_SOUND_MISSION_COK4_10},  {"COK4_11", STREAMED_SOUND_MISSION_COK4_11},  {"COK4_12", STREAMED_SOUND_MISSION_COK4_12},
	{"COK4_13", STREAMED_SOUND_MISSION_COK4_13},  {"COK4_14", STREAMED_SOUND_MISSION_COK4_14},  {"COK4_15", STREAMED_SOUND_MISSION_COK4_15},
	{"COK4_16", STREAMED_SOUND_MISSION_COK4_16},  {"COK4_17", STREAMED_SOUND_MISSION_COK4_17},  {"COK4_18", STREAMED_SOUND_MISSION_COK4_18},
	{"COK4_19", STREAMED_SOUND_MISSION_COK4_19},  {"COK4_20", STREAMED_SOUND_MISSION_COK4_20},  {"COK4_21", STREAMED_SOUND_MISSION_COK4_21},
	{"COK4_22", STREAMED_SOUND_MISSION_COK4_22},  {"COK4_23", STREAMED_SOUND_MISSION_COK4_23},  {"COK4_24", STREAMED_SOUND_MISSION_COK4_24},
	{"COK4_25", STREAMED_SOUND_MISSION_COK4_25},  {"COK4_26", STREAMED_SOUND_MISSION_COK4_26},  {"COK4_27", STREAMED_SOUND_MISSION_COK4_27},
	{"RESC_1", STREAMED_SOUND_MISSION_RESC_1},    {"RESC_2", STREAMED_SOUND_MISSION_RESC_2},    {"RESC_3", STREAMED_SOUND_MISSION_RESC_3},
	{"RESC_4", STREAMED_SOUND_MISSION_RESC_4},    {"RESC_5", STREAMED_SOUND_MISSION_RESC_5},    {"RESC_6", STREAMED_SOUND_MISSION_RESC_6},
	{"RESC_7", STREAMED_SOUND_MISSION_RESC_7},    {"RESC_8", STREAMED_SOUND_MISSION_RESC_8},    {"RESC_9", STREAMED_SOUND_MISSION_RESC_9},
	{"RESC_10", STREAMED_SOUND_MISSION_RESC_10},  {"ASS_1", STREAMED_SOUND_MISSION_ASS_1},      {"ASS_2", STREAMED_SOUND_MISSION_ASS_2},
	{"ASS_3", STREAMED_SOUND_MISSION_ASS_3},      {"ASS_4", STREAMED_SOUND_MISSION_ASS_4},      {"ASS_5", STREAMED_SOUND_MISSION_ASS_5},
	{"ASS_6", STREAMED_SOUND_MISSION_ASS_6},      {"ASS_7", STREAMED_SOUND_MISSION_ASS_7},      {"ASS_8", STREAMED_SOUND_MISSION_ASS_8},
	{"ASS_9", STREAMED_SOUND_MISSION_ASS_9},      {"ASS_10", STREAMED_SOUND_MISSION_ASS_10},    {"ASS_11", STREAMED_SOUND_MISSION_ASS_11},
	{"ASS_12", STREAMED_SOUND_MISSION_ASS_12},    {"ASS_13", STREAMED_SOUND_MISSION_ASS_13},    {"ASS_14", STREAMED_SOUND_MISSION_ASS_14},
	{"BUD1_1", STREAMED_SOUND_MISSION_BUD1_1},    {"BUD1_2", STREAMED_SOUND_MISSION_BUD1_2},    {"BUD1_3", STREAMED_SOUND_MISSION_BUD1_3},
	{"BUD1_4", STREAMED_SOUND_MISSION_BUD1_4},    {"BUD1_5", STREAMED_SOUND_MISSION_BUD1_5},    {"BUD1_9", STREAMED_SOUND_MISSION_BUD1_9},
	{"BUD1_10", STREAMED_SOUND_MISSION_BUD1_10},  {"BUD2_1", STREAMED_SOUND_MISSION_BUD2_1},    {"BUD2_2", STREAMED_SOUND_MISSION_BUD2_2},
	{"BUD2_3", STREAMED_SOUND_MISSION_BUD2_3},    {"BUD2_4", STREAMED_SOUND_MISSION_BUD2_4},    {"BUD2_5", STREAMED_SOUND_MISSION_BUD2_5},
	{"BUD2_6", STREAMED_SOUND_MISSION_BUD2_6},    {"BUD2_7", STREAMED_SOUND_MISSION_BUD2_7},    {"BUD3_1a", STREAMED_SOUND_MISSION_BUD3_1A},
	{"BUD3_1b", STREAMED_SOUND_MISSION_BUD3_1B},  {"BUD3_1", STREAMED_SOUND_MISSION_BUD3_1},    {"BUD3_2", STREAMED_SOUND_MISSION_BUD3_2},
	{"BUD3_3", STREAMED_SOUND_MISSION_BUD3_3},    {"BUD3_4", STREAMED_SOUND_MISSION_BUD3_4},    {"BUD3_1c", STREAMED_SOUND_MISSION_BUD3_1C},
	{"BUD3_5", STREAMED_SOUND_MISSION_BUD3_5},    {"BUD3_6", STREAMED_SOUND_MISSION_BUD3_6},    {"BUD3_7", STREAMED_SOUND_MISSION_BUD3_7},
	{"BUD3_8a", STREAMED_SOUND_MISSION_BUD3_8A},  {"BUD3_8b", STREAMED_SOUND_MISSION_BUD3_8B},  {"BUD3_8c", STREAMED_SOUND_MISSION_BUD3_8C},
	{"BUD3_9a", STREAMED_SOUND_MISSION_BUD3_9A},  {"BUD3_9b", STREAMED_SOUND_MISSION_BUD3_9B},  {"BUD3_9c", STREAMED_SOUND_MISSION_BUD3_9C},
	{"CAP1_2", STREAMED_SOUND_MISSION_CAP1_2},    {"CAP1_3", STREAMED_SOUND_MISSION_CAP1_3},    {"CAP1_4", STREAMED_SOUND_MISSION_CAP1_4},
	{"CAP1_5", STREAMED_SOUND_MISSION_CAP1_5},    {"CAP1_6", STREAMED_SOUND_MISSION_CAP1_6},    {"CAP1_7", STREAMED_SOUND_MISSION_CAP1_7},
	{"CAP1_8", STREAMED_SOUND_MISSION_CAP1_8},    {"CAP1_9", STREAMED_SOUND_MISSION_CAP1_9},    {"CAP1_10", STREAMED_SOUND_MISSION_CAP1_10},
	{"CAP1_11", STREAMED_SOUND_MISSION_CAP1_11},  {"CAP1_12", STREAMED_SOUND_MISSION_CAP1_12},  {"FINKILL", STREAMED_SOUND_MISSION_FINKILL},
	{"FIN_1a", STREAMED_SOUND_MISSION_FIN_1A},    {"FIN_1b", STREAMED_SOUND_MISSION_FIN_1B},    {"FIN_1c", STREAMED_SOUND_MISSION_FIN_1C},
	{"FIN_2b", STREAMED_SOUND_MISSION_FIN_2B},    {"FIN_2c", STREAMED_SOUND_MISSION_FIN_2C},    {"FIN_3", STREAMED_SOUND_MISSION_FIN_3},
	{"FIN_4", STREAMED_SOUND_MISSION_FIN_4},      {"FIN_5", STREAMED_SOUND_MISSION_FIN_5},      {"FIN_6", STREAMED_SOUND_MISSION_FIN_6},
	{"FIN_10", STREAMED_SOUND_MISSION_FIN_10},    {"FIN_11a", STREAMED_SOUND_MISSION_FIN_11A},  {"FIN_11b", STREAMED_SOUND_MISSION_FIN_11B},
	{"FIN_12a", STREAMED_SOUND_MISSION_FIN_12A},  {"FIN_12b", STREAMED_SOUND_MISSION_FIN_12B},  {"FIN_12c", STREAMED_SOUND_MISSION_FIN_12C},
	{"FIN_13", STREAMED_SOUND_MISSION_FIN_13},    {"BNK1_1", STREAMED_SOUND_MISSION_BNK1_1},    {"BNK1_2", STREAMED_SOUND_MISSION_BNK1_2},
	{"BNK1_3", STREAMED_SOUND_MISSION_BNK1_3},    {"BNK1_4", STREAMED_SOUND_MISSION_BNK1_4},    {"BNK1_5", STREAMED_SOUND_MISSION_BNK1_5},
	{"BNK1_6", STREAMED_SOUND_MISSION_BNK1_6},    {"BNK1_7", STREAMED_SOUND_MISSION_BNK1_7},    {"BNK1_8", STREAMED_SOUND_MISSION_BNK1_8},
	{"BNK1_10", STREAMED_SOUND_MISSION_BNK1_10},  {"BNK1_11", STREAMED_SOUND_MISSION_BNK1_11},  {"BNK1_12", STREAMED_SOUND_MISSION_BNK1_12},
	{"BNK1_13", STREAMED_SOUND_MISSION_BNK1_13},  {"BNK1_14", STREAMED_SOUND_MISSION_BNK1_14},  {"BNK2_1", STREAMED_SOUND_MISSION_BNK2_1},
	{"BNK2_2", STREAMED_SOUND_MISSION_BNK2_2},    {"BNK2_3", STREAMED_SOUND_MISSION_BNK2_3},    {"BNK2_4", STREAMED_SOUND_MISSION_BNK2_4},
	{"BNK2_5", STREAMED_SOUND_MISSION_BNK2_5},    {"BNK2_6", STREAMED_SOUND_MISSION_BNK2_6},    {"BNK2_7", STREAMED_SOUND_MISSION_BNK2_7},
	{"BNK2_8", STREAMED_SOUND_MISSION_BNK2_8},    {"BNK2_9", STREAMED_SOUND_MISSION_BNK2_9},    {"BNK3_1", STREAMED_SOUND_MISSION_BNK3_1},
	{"BNK3_2", STREAMED_SOUND_MISSION_BNK3_2},    {"BNK3_3a", STREAMED_SOUND_MISSION_BNK3_3A},  {"BNK3_3b", STREAMED_SOUND_MISSION_BNK3_3B},
	{"BNK3_3c", STREAMED_SOUND_MISSION_BNK3_3C},  {"BNK3_4a", STREAMED_SOUND_MISSION_BNK3_4A},  {"BNK3_4b", STREAMED_SOUND_MISSION_BNK3_4B},
	{"BNK3_4c", STREAMED_SOUND_MISSION_BNK3_4C},  {"BNK4_1", STREAMED_SOUND_MISSION_BNK4_1},    {"BNK4_2", STREAMED_SOUND_MISSION_BNK4_2},
	{"BNK4_3A", STREAMED_SOUND_MISSION_BNK4_3A},  {"BNK4_3B", STREAMED_SOUND_MISSION_BNK4_3B},  {"BNK4_3C", STREAMED_SOUND_MISSION_BNK4_3C},
	{"BNK4_3D", STREAMED_SOUND_MISSION_BNK4_3D},  {"BNK4_3E", STREAMED_SOUND_MISSION_BNK4_3E},  {"BNK4_3F", STREAMED_SOUND_MISSION_BNK4_3F},
	{"BNK4_3G", STREAMED_SOUND_MISSION_BNK4_3G},  {"BNK4_3H", STREAMED_SOUND_MISSION_BNK4_3H},  {"BNK4_3I", STREAMED_SOUND_MISSION_BNK4_3I},
	{"BNK4_3J", STREAMED_SOUND_MISSION_BNK4_3J},  {"BNK4_3K", STREAMED_SOUND_MISSION_BNK4_3K},  {"BNK4_3M", STREAMED_SOUND_MISSION_BNK4_3M},
	{"BNK4_3O", STREAMED_SOUND_MISSION_BNK4_3O},  {"BNK4_3P", STREAMED_SOUND_MISSION_BNK4_3P},  {"BNK4_3Q", STREAMED_SOUND_MISSION_BNK4_3Q},
	{"BNK4_3R", STREAMED_SOUND_MISSION_BNK4_3R},  {"BNK4_3S", STREAMED_SOUND_MISSION_BNK4_3S},  {"BNK4_3T", STREAMED_SOUND_MISSION_BNK4_3T},
	{"BNK4_3U", STREAMED_SOUND_MISSION_BNK4_3U},  {"BNK4_3V", STREAMED_SOUND_MISSION_BNK4_3V},  {"BNK4_4a", STREAMED_SOUND_MISSION_BNK4_4A},
	{"BNK4_4b", STREAMED_SOUND_MISSION_BNK4_4B},  {"BNK4_5", STREAMED_SOUND_MISSION_BNK4_5},    {"BNK4_6", STREAMED_SOUND_MISSION_BNK4_6},
	{"BNK4_7", STREAMED_SOUND_MISSION_BNK4_7},    {"BNK4_8", STREAMED_SOUND_MISSION_BNK4_8},    {"BNK4_9", STREAMED_SOUND_MISSION_BNK4_9},
	{"BNK4_10", STREAMED_SOUND_MISSION_BNK4_10},  {"BNK4_11", STREAMED_SOUND_MISSION_BNK4_11},  {"BK4_12a", STREAMED_SOUND_MISSION_BK4_12A},
	{"BK4_12b", STREAMED_SOUND_MISSION_BK4_12B},  {"BK4_12c", STREAMED_SOUND_MISSION_BK4_12C},  {"BNK4_13", STREAMED_SOUND_MISSION_BNK4_13},
	{"BK4_14a", STREAMED_SOUND_MISSION_BK4_14A},  {"BK4_14b", STREAMED_SOUND_MISSION_BK4_14B},  {"BNK4_15", STREAMED_SOUND_MISSION_BNK4_15},
	{"BNK4_16", STREAMED_SOUND_MISSION_BNK4_16},  {"BNK4_17", STREAMED_SOUND_MISSION_BNK4_17},  {"BNK4_18", STREAMED_SOUND_MISSION_BNK4_18},
	{"BK4_19a", STREAMED_SOUND_MISSION_BK4_19A},  {"BK4_19b", STREAMED_SOUND_MISSION_BK4_19B},  {"BK4_20a", STREAMED_SOUND_MISSION_BK4_20A},
	{"BK4_20b", STREAMED_SOUND_MISSION_BK4_20B},  {"BNK4_21", STREAMED_SOUND_MISSION_BNK4_21},  {"BNK422a", STREAMED_SOUND_MISSION_BNK422A},
	{"BNK422b", STREAMED_SOUND_MISSION_BNK422B},  {"BK4_23a", STREAMED_SOUND_MISSION_BK4_23A},  {"BK4_23b", STREAMED_SOUND_MISSION_BK4_23B},
	{"BK4_23c", STREAMED_SOUND_MISSION_BK4_23C},  {"BK4_23d", STREAMED_SOUND_MISSION_BK4_23D},  {"BK4_24a", STREAMED_SOUND_MISSION_BK4_24A},
	{"BK4_24b", STREAMED_SOUND_MISSION_BK4_24B},  {"BNK4_25", STREAMED_SOUND_MISSION_BNK4_25},  {"BNK4_26", STREAMED_SOUND_MISSION_BNK4_26},
	{"BNK4_27", STREAMED_SOUND_MISSION_BNK4_27},  {"BNK4_28", STREAMED_SOUND_MISSION_BNK4_28},  {"BNK4_29", STREAMED_SOUND_MISSION_BNK4_29},
	{"BNK4_30", STREAMED_SOUND_MISSION_BNK4_30},  {"BK4_31a", STREAMED_SOUND_MISSION_BK4_31A},  {"BK4_31b", STREAMED_SOUND_MISSION_BK4_31B},
	{"BNK4_32", STREAMED_SOUND_MISSION_BNK4_32},  {"BK4_34a", STREAMED_SOUND_MISSION_BK4_34A},  {"BK4_34b", STREAMED_SOUND_MISSION_BK4_34B},
	{"BK4_35a", STREAMED_SOUND_MISSION_BK4_35A},  {"BK4_35b", STREAMED_SOUND_MISSION_BK4_35B},  {"BNK4_36", STREAMED_SOUND_MISSION_BNK4_36},
	{"BNK4_37", STREAMED_SOUND_MISSION_BNK4_37},  {"BNK4_38", STREAMED_SOUND_MISSION_BNK4_38},  {"BNK_39", STREAMED_SOUND_MISSION_BNK4_39},
	{"BK4_40a", STREAMED_SOUND_MISSION_BK4_40A},  {"BK4_40b", STREAMED_SOUND_MISSION_BK4_40B},  {"BNK4_41", STREAMED_SOUND_MISSION_BNK4_41},
	{"BNK4_42", STREAMED_SOUND_MISSION_BNK4_42},  {"BNK4_43", STREAMED_SOUND_MISSION_BNK4_43},  {"BNK4_44", STREAMED_SOUND_MISSION_BNK4_44},
	{"BNK4_45", STREAMED_SOUND_MISSION_BNK4_45},  {"BNK4_46", STREAMED_SOUND_MISSION_BNK4_46},  {"BNK4_47", STREAMED_SOUND_MISSION_BNK4_47},
	{"BNK4_48", STREAMED_SOUND_MISSION_BNK4_48},  {"BNK4_49", STREAMED_SOUND_MISSION_BNK4_49},  {"BNK450A", STREAMED_SOUND_MISSION_BNK450A},
	{"BNK450B", STREAMED_SOUND_MISSION_BNK450B},  {"BNK4_51", STREAMED_SOUND_MISSION_BNK4_51},  {"BNK4_94", STREAMED_SOUND_MISSION_BNK4_94},
	{"BNK4_95", STREAMED_SOUND_MISSION_BNK4_95},  {"BNK4_96", STREAMED_SOUND_MISSION_BNK4_96},  {"BNK4_97", STREAMED_SOUND_MISSION_BNK4_97},
	{"BNK4_98", STREAMED_SOUND_MISSION_BNK4_98},  {"BNK4_99", STREAMED_SOUND_MISSION_BNK4_99},  {"CNT1_1", STREAMED_SOUND_MISSION_CNT1_1},
	{"CNT1_2", STREAMED_SOUND_MISSION_CNT1_2},    {"CNT1_3", STREAMED_SOUND_MISSION_CNT1_3},    {"CNT1_4", STREAMED_SOUND_MISSION_CNT1_4},
	{"CNT1_5", STREAMED_SOUND_MISSION_CNT1_5},    {"CNT2_1", STREAMED_SOUND_MISSION_CNT2_1},    {"CNT2_2", STREAMED_SOUND_MISSION_CNT2_2},
	{"CNT2_3", STREAMED_SOUND_MISSION_CNT2_3},    {"CNT2_4", STREAMED_SOUND_MISSION_CNT2_4},    {"PORN1_1", STREAMED_SOUND_MISSION_PORN1_1},
	{"PORN1_2", STREAMED_SOUND_MISSION_PORN1_2},  {"PORN1_3", STREAMED_SOUND_MISSION_PORN1_3},  {"PRN1_3A", STREAMED_SOUND_MISSION_PRN1_3A},
	{"PORN1_4", STREAMED_SOUND_MISSION_PORN1_4},  {"PORN1_5", STREAMED_SOUND_MISSION_PORN1_5},  {"PORN1_6", STREAMED_SOUND_MISSION_PORN1_6},
	{"PORN1_7", STREAMED_SOUND_MISSION_PORN1_7},  {"PORN1_8", STREAMED_SOUND_MISSION_PORN1_8},  {"PORN1_9", STREAMED_SOUND_MISSION_PORN1_9},
	{"PRN1_10", STREAMED_SOUND_MISSION_PRN1_10},  {"PRN1_11", STREAMED_SOUND_MISSION_PRN1_11},  {"PRN1_12", STREAMED_SOUND_MISSION_PRN1_12},
	{"PRN1_13", STREAMED_SOUND_MISSION_PRN1_13},  {"PRN1_14", STREAMED_SOUND_MISSION_PRN1_14},  {"PRN1_15", STREAMED_SOUND_MISSION_PRN1_15},
	{"PRN1_16", STREAMED_SOUND_MISSION_PRN1_16},  {"PRN1_17", STREAMED_SOUND_MISSION_PRN1_17},  {"PRN1_18", STREAMED_SOUND_MISSION_PRN1_18},
	{"PRN1_19", STREAMED_SOUND_MISSION_PRN1_19},  {"PRN1_20", STREAMED_SOUND_MISSION_PRN1_20},  {"PRN1_21", STREAMED_SOUND_MISSION_PRN1_21},
	{"PORN3_1", STREAMED_SOUND_MISSION_PORN3_1},  {"PORN3_2", STREAMED_SOUND_MISSION_PORN3_2},  {"PORN3_3", STREAMED_SOUND_MISSION_PORN3_3},
	{"PORN3_4", STREAMED_SOUND_MISSION_PORN3_4},  {"TAX1_1", STREAMED_SOUND_MISSION_TAX1_1},    {"TAX1_2", STREAMED_SOUND_MISSION_TAX1_2},
	{"TAX1_3", STREAMED_SOUND_MISSION_TAX1_3},    {"TAX1_4", STREAMED_SOUND_MISSION_TAX1_4},    {"TAX1_5", STREAMED_SOUND_MISSION_TAX1_5},
	{"TAX2_1", STREAMED_SOUND_MISSION_TAX2_1},    {"TAX2_2", STREAMED_SOUND_MISSION_TAX2_2},    {"TAX2_3", STREAMED_SOUND_MISSION_TAX2_3},
	{"TAX2_4", STREAMED_SOUND_MISSION_TAX2_4},    {"TAX2_5", STREAMED_SOUND_MISSION_TAX2_5},    {"TAX2_6", STREAMED_SOUND_MISSION_TAX2_6},
	{"TAX2_7", STREAMED_SOUND_MISSION_TAX2_7},    {"TAX3_1", STREAMED_SOUND_MISSION_TAX3_1},    {"TAX3_2", STREAMED_SOUND_MISSION_TAX3_2},
	{"TAX3_3", STREAMED_SOUND_MISSION_TAX3_3},    {"TAX3_4", STREAMED_SOUND_MISSION_TAX3_4},    {"TAX3_5", STREAMED_SOUND_MISSION_TAX3_5},
	{"TEX1_1", STREAMED_SOUND_MISSION_TEX1_1},    {"TEX1_2", STREAMED_SOUND_MISSION_TEX1_2},    {"TEX1_3", STREAMED_SOUND_MISSION_TEX1_3},
	{"TEX1_4", STREAMED_SOUND_MISSION_TEX1_4},    {"TEX1_5", STREAMED_SOUND_MISSION_TEX1_5},    {"TEX1_6", STREAMED_SOUND_MISSION_TEX1_6},
	{"TEX2_1", STREAMED_SOUND_MISSION_TEX2_1},    {"TEX3_1", STREAMED_SOUND_MISSION_TEX3_1},    {"TEX3_2", STREAMED_SOUND_MISSION_TEX3_2},
	{"TEX3_3", STREAMED_SOUND_MISSION_TEX3_3},    {"TEX3_4", STREAMED_SOUND_MISSION_TEX3_4},    {"TEX3_5", STREAMED_SOUND_MISSION_TEX3_5},
	{"TEX3_6", STREAMED_SOUND_MISSION_TEX3_6},    {"TEX3_7", STREAMED_SOUND_MISSION_TEX3_7},    {"TEX3_8", STREAMED_SOUND_MISSION_TEX3_8},
	{"PHIL1_2", STREAMED_SOUND_MISSION_PHIL1_2},  {"PHIL1_3", STREAMED_SOUND_MISSION_PHIL1_3},  {"PHIL2_1", STREAMED_SOUND_MISSION_PHIL2_1},
	{"PHIL2_2", STREAMED_SOUND_MISSION_PHIL2_2},  {"PHIL2_3", STREAMED_SOUND_MISSION_PHIL2_3},  {"PHIL2_4", STREAMED_SOUND_MISSION_PHIL2_4},
	{"PHIL2_5", STREAMED_SOUND_MISSION_PHIL2_5},  {"PHIL2_6", STREAMED_SOUND_MISSION_PHIL2_6},  {"PHIL2_7", STREAMED_SOUND_MISSION_PHIL2_7},
	{"PHIL2_8", STREAMED_SOUND_MISSION_PHIL2_8},  {"PHIL2_9", STREAMED_SOUND_MISSION_PHIL2_9},  {"PHIL210", STREAMED_SOUND_MISSION_PHIL210},
	{"PHIL211", STREAMED_SOUND_MISSION_PHIL211},  {"BIKE1_1", STREAMED_SOUND_MISSION_BIKE1_1},  {"BIKE1_2", STREAMED_SOUND_MISSION_BIKE1_2},
	{"BIKE1_3", STREAMED_SOUND_MISSION_BIKE1_3},  {"ROK1_1a", STREAMED_SOUND_MISSION_ROK1_1A},  {"ROK1_1b", STREAMED_SOUND_MISSION_ROK1_1B},
	{"ROK1_5", STREAMED_SOUND_MISSION_ROK1_5},    {"ROK1_6", STREAMED_SOUND_MISSION_ROK1_6},    {"ROK1_7", STREAMED_SOUND_MISSION_ROK1_7},
	{"ROK1_8", STREAMED_SOUND_MISSION_ROK1_8},    {"ROK1_9", STREAMED_SOUND_MISSION_ROK1_9},    {"PSYCH_1", STREAMED_SOUND_MISSION_PSYCH_1},
	{"PSYCH_2", STREAMED_SOUND_MISSION_PSYCH_2},  {"ROK2_01", STREAMED_SOUND_MISSION_ROK2_01},  {"ROK3_1", STREAMED_SOUND_MISSION_ROK3_1},
	{"ROK3_2", STREAMED_SOUND_MISSION_ROK3_2},    {"ROK3_3", STREAMED_SOUND_MISSION_ROK3_3},    {"ROK3_4", STREAMED_SOUND_MISSION_ROK3_4},
	{"ROK3_5", STREAMED_SOUND_MISSION_ROK3_5},    {"ROK3_6", STREAMED_SOUND_MISSION_ROK3_6},    {"ROK3_7", STREAMED_SOUND_MISSION_ROK3_7},
	{"ROK3_8", STREAMED_SOUND_MISSION_ROK3_8},    {"ROK3_9", STREAMED_SOUND_MISSION_ROK3_9},    {"ROK3_10", STREAMED_SOUND_MISSION_ROK3_10},
	{"ROK3_11", STREAMED_SOUND_MISSION_ROK3_11},  {"ROK3_12", STREAMED_SOUND_MISSION_ROK3_12},  {"ROK3_13", STREAMED_SOUND_MISSION_ROK3_13},
	{"ROK3_14", STREAMED_SOUND_MISSION_ROK3_14},  {"ROK3_15", STREAMED_SOUND_MISSION_ROK3_15},  {"ROK3_16", STREAMED_SOUND_MISSION_ROK3_16},
	{"ROK3_17", STREAMED_SOUND_MISSION_ROK3_17},  {"ROK3_18", STREAMED_SOUND_MISSION_ROK3_18},  {"ROK3_19", STREAMED_SOUND_MISSION_ROK3_19},
	{"ROK3_20", STREAMED_SOUND_MISSION_ROK3_20},  {"ROK3_21", STREAMED_SOUND_MISSION_ROK3_21},  {"ROK3_22", STREAMED_SOUND_MISSION_ROK3_22},
	{"ROK3_23", STREAMED_SOUND_MISSION_ROK3_23},  {"ROK3_24", STREAMED_SOUND_MISSION_ROK3_24},  {"ROK3_25", STREAMED_SOUND_MISSION_ROK3_25},
	{"ROK3_26", STREAMED_SOUND_MISSION_ROK3_26},  {"ROK3_27", STREAMED_SOUND_MISSION_ROK3_27},  {"ROK3_62", STREAMED_SOUND_MISSION_ROK3_62},
	{"ROK3_63", STREAMED_SOUND_MISSION_ROK3_63},  {"ROK3_64", STREAMED_SOUND_MISSION_ROK3_64},  {"ROK3_65", STREAMED_SOUND_MISSION_ROK3_65},
	{"ROK3_66", STREAMED_SOUND_MISSION_ROK3_66},  {"ROK3_67", STREAMED_SOUND_MISSION_ROK3_67},  {"ROK3_68", STREAMED_SOUND_MISSION_ROK3_68},
	{"ROK3_69", STREAMED_SOUND_MISSION_ROK3_69},  {"ROK3_70", STREAMED_SOUND_MISSION_ROK3_70},  {"ROK3_71", STREAMED_SOUND_MISSION_ROK3_71},
	{"ROK3_73", STREAMED_SOUND_MISSION_ROK3_73},  {"HAT_1a", STREAMED_SOUND_MISSION_HAT_1A},    {"intro1", STREAMED_SOUND_MISSION_INTRO1},
	{"intro2", STREAMED_SOUND_MISSION_INTRO2},    {"intro3", STREAMED_SOUND_MISSION_INTRO3},    {"intro4", STREAMED_SOUND_MISSION_INTRO4},
	{"CUB1_1", STREAMED_SOUND_MISSION_CUB1_1},    {"CUB1_2", STREAMED_SOUND_MISSION_CUB1_2},    {"CUB1_3", STREAMED_SOUND_MISSION_CUB1_3},
	{"CUB1_4", STREAMED_SOUND_MISSION_CUB1_4},    {"CUB1_5", STREAMED_SOUND_MISSION_CUB1_5},    {"CUB1_6", STREAMED_SOUND_MISSION_CUB1_6},
	{"CUB1_7", STREAMED_SOUND_MISSION_CUB1_7},    {"CUB1_8", STREAMED_SOUND_MISSION_CUB1_8},    {"CUB1_9", STREAMED_SOUND_MISSION_CUB1_9},
	{"CUB1_10", STREAMED_SOUND_MISSION_CUB1_10},  {"CUB2_1", STREAMED_SOUND_MISSION_CUB2_1},    {"CUB2_2", STREAMED_SOUND_MISSION_CUB2_2},
	{"CUB2_3a", STREAMED_SOUND_MISSION_CUB2_3A},  {"CUB2_3b", STREAMED_SOUND_MISSION_CUB2_3B},  {"CUB2_3c", STREAMED_SOUND_MISSION_CUB2_3C},
	{"CUB2_4a", STREAMED_SOUND_MISSION_CUB2_4A},  {"CUB2_5", STREAMED_SOUND_MISSION_CUB2_5},    {"CUB2_6", STREAMED_SOUND_MISSION_CUB2_6},
	{"CUB2_7", STREAMED_SOUND_MISSION_CUB2_7},    {"CUB2_8", STREAMED_SOUND_MISSION_CUB2_8},    {"CUB2_9", STREAMED_SOUND_MISSION_CUB2_9},
	{"CUB2_10", STREAMED_SOUND_MISSION_CUB2_10},  {"CUB2_11", STREAMED_SOUND_MISSION_CUB2_11},  {"CUB3_1", STREAMED_SOUND_MISSION_CUB3_1},
	{"CUB3_2", STREAMED_SOUND_MISSION_CUB3_2},    {"CUB3_3", STREAMED_SOUND_MISSION_CUB3_3},    {"CUB3_4", STREAMED_SOUND_MISSION_CUB3_4},
	{"CUB4_1", STREAMED_SOUND_MISSION_CUB4_1},    {"CUB4_2", STREAMED_SOUND_MISSION_CUB4_2},    {"CUB4_3", STREAMED_SOUND_MISSION_CUB4_3},
	{"CUB4_4", STREAMED_SOUND_MISSION_CUB4_4},    {"CUB4_5", STREAMED_SOUND_MISSION_CUB4_5},    {"CUB4_5A", STREAMED_SOUND_MISSION_CUB4_5A},
	{"CUB4_6", STREAMED_SOUND_MISSION_CUB4_6},    {"CUB4_7", STREAMED_SOUND_MISSION_CUB4_7},    {"CUB4_8", STREAMED_SOUND_MISSION_CUB4_8},
	{"CUB4_9", STREAMED_SOUND_MISSION_CUB4_9},    {"CUB4_10", STREAMED_SOUND_MISSION_CUB4_10},  {"CUB4_11", STREAMED_SOUND_MISSION_CUB4_11},
	{"CUB4_12", STREAMED_SOUND_MISSION_CUB4_12},  {"CUB4_13", STREAMED_SOUND_MISSION_CUB4_13},  {"CUB4_14", STREAMED_SOUND_MISSION_CUB4_14},
	{"CUB4_15", STREAMED_SOUND_MISSION_CUB4_15},  {"CUB4_16", STREAMED_SOUND_MISSION_CUB4_16},  {"golf_1", STREAMED_SOUND_MISSION_GOLF_1},
	{"golf_2", STREAMED_SOUND_MISSION_GOLF_2},    {"golf_3", STREAMED_SOUND_MISSION_GOLF_3},    {"bar_1", STREAMED_SOUND_MISSION_BAR_1},
	{"bar_2", STREAMED_SOUND_MISSION_BAR_2},      {"bar_3", STREAMED_SOUND_MISSION_BAR_3},      {"bar_4", STREAMED_SOUND_MISSION_BAR_4},
	{"bar_5", STREAMED_SOUND_MISSION_BAR_5},      {"bar_6", STREAMED_SOUND_MISSION_BAR_6},      {"bar_7", STREAMED_SOUND_MISSION_BAR_7},
	{"bar_8", STREAMED_SOUND_MISSION_BAR_8},      {"strip_1", STREAMED_SOUND_MISSION_STRIP_1},  {"strip_2", STREAMED_SOUND_MISSION_STRIP_2},
	{"strip_3", STREAMED_SOUND_MISSION_STRIP_3},  {"strip_4", STREAMED_SOUND_MISSION_STRIP_4},  {"strip_5", STREAMED_SOUND_MISSION_STRIP_5},
	{"strip_6", STREAMED_SOUND_MISSION_STRIP_6},  {"strip_7", STREAMED_SOUND_MISSION_STRIP_7},  {"strip_8", STREAMED_SOUND_MISSION_STRIP_8},
	{"strip_9", STREAMED_SOUND_MISSION_STRIP_9},  {"star_1", STREAMED_SOUND_MISSION_STAR_1},    {"star_2", STREAMED_SOUND_MISSION_STAR_2},
	{"star_3", STREAMED_SOUND_MISSION_STAR_3},    {"star_4", STREAMED_SOUND_MISSION_STAR_4},    {"mob_01a", STREAMED_SOUND_MISSION_MOB_01A},
	{"mob_01b", STREAMED_SOUND_MISSION_MOB_01B},  {"mob_01c", STREAMED_SOUND_MISSION_MOB_01C},  {"mob_02a", STREAMED_SOUND_MISSION_MOB_02A},
	{"mob_02b", STREAMED_SOUND_MISSION_MOB_02B},  {"mob_02c", STREAMED_SOUND_MISSION_MOB_02C},  {"mob_03a", STREAMED_SOUND_MISSION_MOB_03A},
	{"mob_03b", STREAMED_SOUND_MISSION_MOB_03B},  {"mob_03c", STREAMED_SOUND_MISSION_MOB_03C},  {"mob_03d", STREAMED_SOUND_MISSION_MOB_03D},
	{"mob_03e", STREAMED_SOUND_MISSION_MOB_03E},  {"shark_1", STREAMED_SOUND_MISSION_SHARK_1},  {"shark_2", STREAMED_SOUND_MISSION_SHARK_2},
	{"shark_3", STREAMED_SOUND_MISSION_SHARK_3},  {"shark_4", STREAMED_SOUND_MISSION_SHARK_4},  {"shark_5", STREAMED_SOUND_MISSION_SHARK_5},
	{"mob_04a", STREAMED_SOUND_MISSION_MOB_04A},  {"mob_04b", STREAMED_SOUND_MISSION_MOB_04B},  {"mob_04c", STREAMED_SOUND_MISSION_MOB_04C},
	{"mob_04d", STREAMED_SOUND_MISSION_MOB_04D},  {"mob_05a", STREAMED_SOUND_MISSION_MOB_05A},  {"mob_05b", STREAMED_SOUND_MISSION_MOB_05B},
	{"mob_05c", STREAMED_SOUND_MISSION_MOB_05C},  {"mob_05d", STREAMED_SOUND_MISSION_MOB_05D},  {"mob_06a", STREAMED_SOUND_MISSION_MOB_06A},
	{"mob_06b", STREAMED_SOUND_MISSION_MOB_06B},  {"mob_06c", STREAMED_SOUND_MISSION_MOB_06C},  {"mob_07a", STREAMED_SOUND_MISSION_MOB_07A},
	{"mob_07b", STREAMED_SOUND_MISSION_MOB_07B},  {"mob_08a", STREAMED_SOUND_MISSION_MOB_08A},  {"mob_08b", STREAMED_SOUND_MISSION_MOB_08B},
	{"mob_08c", STREAMED_SOUND_MISSION_MOB_08C},  {"mob_08d", STREAMED_SOUND_MISSION_MOB_08D},  {"mob_08e", STREAMED_SOUND_MISSION_MOB_08E},
	{"mob_08f", STREAMED_SOUND_MISSION_MOB_08F},  {"mob_08g", STREAMED_SOUND_MISSION_MOB_08G},  {"mob_09a", STREAMED_SOUND_MISSION_MOB_09A},
	{"mob_09b", STREAMED_SOUND_MISSION_MOB_09B},  {"mob_09c", STREAMED_SOUND_MISSION_MOB_09C},  {"mob_09d", STREAMED_SOUND_MISSION_MOB_09D},
	{"mob_09e", STREAMED_SOUND_MISSION_MOB_09E},  {"mob_09f", STREAMED_SOUND_MISSION_MOB_09F},  {"mob_10a", STREAMED_SOUND_MISSION_MOB_10A},
	{"mob_10b", STREAMED_SOUND_MISSION_MOB_10B},  {"mob_10c", STREAMED_SOUND_MISSION_MOB_10C},  {"mob_10d", STREAMED_SOUND_MISSION_MOB_10D},
	{"mob_10e", STREAMED_SOUND_MISSION_MOB_10E},  {"mob_11a", STREAMED_SOUND_MISSION_MOB_11A},  {"mob_11b", STREAMED_SOUND_MISSION_MOB_11B},
	{"mob_11c", STREAMED_SOUND_MISSION_MOB_11C},  {"mob_11d", STREAMED_SOUND_MISSION_MOB_11D},  {"mob_11e", STREAMED_SOUND_MISSION_MOB_11E},
	{"mob_11f", STREAMED_SOUND_MISSION_MOB_11F},  {"mob_14a", STREAMED_SOUND_MISSION_MOB_14A},  {"mob_14b", STREAMED_SOUND_MISSION_MOB_14B},
	{"mob_14c", STREAMED_SOUND_MISSION_MOB_14C},  {"mob_14d", STREAMED_SOUND_MISSION_MOB_14D},  {"mob_14e", STREAMED_SOUND_MISSION_MOB_14E},
	{"mob_14f", STREAMED_SOUND_MISSION_MOB_14F},  {"mob_14g", STREAMED_SOUND_MISSION_MOB_14G},  {"mob_14h", STREAMED_SOUND_MISSION_MOB_14H},
	{"mob_16a", STREAMED_SOUND_MISSION_MOB_16A},  {"mob_16b", STREAMED_SOUND_MISSION_MOB_16B},  {"mob_16c", STREAMED_SOUND_MISSION_MOB_16C},
	{"mob_16d", STREAMED_SOUND_MISSION_MOB_16D},  {"mob_16e", STREAMED_SOUND_MISSION_MOB_16E},  {"mob_16f", STREAMED_SOUND_MISSION_MOB_16F},
	{"mob_16g", STREAMED_SOUND_MISSION_MOB_16G},  {"mob_17a", STREAMED_SOUND_MISSION_MOB_17A},  {"mob_17b", STREAMED_SOUND_MISSION_MOB_17B},
	{"mob_17c", STREAMED_SOUND_MISSION_MOB_17C},  {"mob_17d", STREAMED_SOUND_MISSION_MOB_17D},  {"mob_17e", STREAMED_SOUND_MISSION_MOB_17E},
	{"mob_17g", STREAMED_SOUND_MISSION_MOB_17G},  {"mob_17h", STREAMED_SOUND_MISSION_MOB_17H},  {"mob_17i", STREAMED_SOUND_MISSION_MOB_17I},
	{"mob_17j", STREAMED_SOUND_MISSION_MOB_17J},  {"mob_17k", STREAMED_SOUND_MISSION_MOB_17K},  {"mob_17l", STREAMED_SOUND_MISSION_MOB_17L},
	{"mob_18a", STREAMED_SOUND_MISSION_MOB_18A},  {"mob_18b", STREAMED_SOUND_MISSION_MOB_18B},  {"mob_18c", STREAMED_SOUND_MISSION_MOB_18C},
	{"mob_18d", STREAMED_SOUND_MISSION_MOB_18D},  {"mob_18e", STREAMED_SOUND_MISSION_MOB_18E},  {"mob_18f", STREAMED_SOUND_MISSION_MOB_18F},
	{"mob_18g", STREAMED_SOUND_MISSION_MOB_18G},  {"mob_20a", STREAMED_SOUND_MISSION_MOB_20A},  {"mob_20b", STREAMED_SOUND_MISSION_MOB_20B},
	{"mob_20c", STREAMED_SOUND_MISSION_MOB_20C},  {"mob_20d", STREAMED_SOUND_MISSION_MOB_20D},  {"mob_20e", STREAMED_SOUND_MISSION_MOB_20E},
	{"mob_24a", STREAMED_SOUND_MISSION_MOB_24A},  {"mob_24b", STREAMED_SOUND_MISSION_MOB_24B},  {"mob_24c", STREAMED_SOUND_MISSION_MOB_24C},
	{"mob_24d", STREAMED_SOUND_MISSION_MOB_24D},  {"mob_24e", STREAMED_SOUND_MISSION_MOB_24E},  {"mob_24f", STREAMED_SOUND_MISSION_MOB_24F},
	{"mob_24g", STREAMED_SOUND_MISSION_MOB_24G},  {"mob_24h", STREAMED_SOUND_MISSION_MOB_24H},  {"mob_25a", STREAMED_SOUND_MISSION_MOB_25A},
	{"mob_25b", STREAMED_SOUND_MISSION_MOB_25B},  {"mob_25c", STREAMED_SOUND_MISSION_MOB_25C},  {"mob_25d", STREAMED_SOUND_MISSION_MOB_25D},
	{"mob_26a", STREAMED_SOUND_MISSION_MOB_26A},  {"mob_26b", STREAMED_SOUND_MISSION_MOB_26B},  {"mob_26c", STREAMED_SOUND_MISSION_MOB_26C},
	{"mob_26d", STREAMED_SOUND_MISSION_MOB_26D},  {"mob_26e", STREAMED_SOUND_MISSION_MOB_26E},  {"mob_29a", STREAMED_SOUND_MISSION_MOB_29A},
	{"mob_29b", STREAMED_SOUND_MISSION_MOB_29B},  {"mob_29c", STREAMED_SOUND_MISSION_MOB_29C},  {"mob_29d", STREAMED_SOUND_MISSION_MOB_29D},
	{"mob_29e", STREAMED_SOUND_MISSION_MOB_29E},  {"mob_29f", STREAMED_SOUND_MISSION_MOB_29F},  {"mob_29g", STREAMED_SOUND_MISSION_MOB_29G},
	{"mob_30a", STREAMED_SOUND_MISSION_MOB_30A},  {"mob_30b", STREAMED_SOUND_MISSION_MOB_30B},  {"mob_30c", STREAMED_SOUND_MISSION_MOB_30C},
	{"mob_30d", STREAMED_SOUND_MISSION_MOB_30D},  {"mob_30e", STREAMED_SOUND_MISSION_MOB_30E},  {"mob_30f", STREAMED_SOUND_MISSION_MOB_30F},
	{"mob_33a", STREAMED_SOUND_MISSION_MOB_33A},  {"mob_33b", STREAMED_SOUND_MISSION_MOB_33B},  {"mob_33c", STREAMED_SOUND_MISSION_MOB_33C},
	{"mob_33d", STREAMED_SOUND_MISSION_MOB_33D},  {"mob_34a", STREAMED_SOUND_MISSION_MOB_34A},  {"mob_34b", STREAMED_SOUND_MISSION_MOB_34B},
	{"mob_34c", STREAMED_SOUND_MISSION_MOB_34C},  {"mob_34d", STREAMED_SOUND_MISSION_MOB_34D},  {"mob_35a", STREAMED_SOUND_MISSION_MOB_35A},
	{"mob_35b", STREAMED_SOUND_MISSION_MOB_35B},  {"mob_35c", STREAMED_SOUND_MISSION_MOB_35C},  {"mob_35d", STREAMED_SOUND_MISSION_MOB_35D},
	{"mob_36a", STREAMED_SOUND_MISSION_MOB_36A},  {"mob_36b", STREAMED_SOUND_MISSION_MOB_36B},  {"mob_36c", STREAMED_SOUND_MISSION_MOB_36C},
	{"mob_40a", STREAMED_SOUND_MISSION_MOB_40A},  {"mob_40b", STREAMED_SOUND_MISSION_MOB_40B},  {"mob_40c", STREAMED_SOUND_MISSION_MOB_40C},
	{"mob_40d", STREAMED_SOUND_MISSION_MOB_40D},  {"mob_40e", STREAMED_SOUND_MISSION_MOB_40E},  {"mob_40f", STREAMED_SOUND_MISSION_MOB_40F},
	{"mob_40g", STREAMED_SOUND_MISSION_MOB_40G},  {"mob_40h", STREAMED_SOUND_MISSION_MOB_40H},  {"mob_40i", STREAMED_SOUND_MISSION_MOB_40I},
	{"mob_41a", STREAMED_SOUND_MISSION_MOB_41A},  {"mob_41b", STREAMED_SOUND_MISSION_MOB_41B},  {"mob_41c", STREAMED_SOUND_MISSION_MOB_41C},
	{"mob_41d", STREAMED_SOUND_MISSION_MOB_41D},  {"mob_41e", STREAMED_SOUND_MISSION_MOB_41E},  {"mob_41f", STREAMED_SOUND_MISSION_MOB_41F},
	{"mob_41g", STREAMED_SOUND_MISSION_MOB_41G},  {"mob_41h", STREAMED_SOUND_MISSION_MOB_41H},  {"mob_42a", STREAMED_SOUND_MISSION_MOB_42A},
	{"mob_42b", STREAMED_SOUND_MISSION_MOB_42B},  {"mob_42c", STREAMED_SOUND_MISSION_MOB_42C},  {"mob_42d", STREAMED_SOUND_MISSION_MOB_42D},
	{"mob_42e", STREAMED_SOUND_MISSION_MOB_42E},  {"mob_43a", STREAMED_SOUND_MISSION_MOB_43A},  {"mob_43b", STREAMED_SOUND_MISSION_MOB_43B},
	{"mob_43c", STREAMED_SOUND_MISSION_MOB_43C},  {"mob_43d", STREAMED_SOUND_MISSION_MOB_43D},  {"mob_43e", STREAMED_SOUND_MISSION_MOB_43E},
	{"mob_43f", STREAMED_SOUND_MISSION_MOB_43F},  {"mob_43g", STREAMED_SOUND_MISSION_MOB_43G},  {"mob_43h", STREAMED_SOUND_MISSION_MOB_43H},
	{"mob_45a", STREAMED_SOUND_MISSION_MOB_45A},  {"mob_45b", STREAMED_SOUND_MISSION_MOB_45B},  {"mob_45c", STREAMED_SOUND_MISSION_MOB_45C},
	{"mob_45d", STREAMED_SOUND_MISSION_MOB_45D},  {"mob_45e", STREAMED_SOUND_MISSION_MOB_45E},  {"mob_45f", STREAMED_SOUND_MISSION_MOB_45F},
	{"mob_45g", STREAMED_SOUND_MISSION_MOB_45G},  {"mob_45h", STREAMED_SOUND_MISSION_MOB_45H},  {"mob_45i", STREAMED_SOUND_MISSION_MOB_45I},
	{"mob_45j", STREAMED_SOUND_MISSION_MOB_45J},  {"mob_45k", STREAMED_SOUND_MISSION_MOB_45K},  {"mob_45l", STREAMED_SOUND_MISSION_MOB_45L},
	{"mob_45m", STREAMED_SOUND_MISSION_MOB_45M},  {"mob_45n", STREAMED_SOUND_MISSION_MOB_45N},  {"mob_46a", STREAMED_SOUND_MISSION_MOB_46A},
	{"mob_46b", STREAMED_SOUND_MISSION_MOB_46B},  {"mob_46c", STREAMED_SOUND_MISSION_MOB_46C},  {"mob_46d", STREAMED_SOUND_MISSION_MOB_46D},
	{"mob_46e", STREAMED_SOUND_MISSION_MOB_46E},  {"mob_46f", STREAMED_SOUND_MISSION_MOB_46F},  {"mob_46g", STREAMED_SOUND_MISSION_MOB_46G},
	{"mob_46h", STREAMED_SOUND_MISSION_MOB_46H},  {"mob_47a", STREAMED_SOUND_MISSION_MOB_47A},  {"mob_52a", STREAMED_SOUND_MISSION_MOB_52A},
	{"mob_52b", STREAMED_SOUND_MISSION_MOB_52B},  {"mob_52c", STREAMED_SOUND_MISSION_MOB_52C},  {"mob_52d", STREAMED_SOUND_MISSION_MOB_52D},
	{"mob_52e", STREAMED_SOUND_MISSION_MOB_52E},  {"mob_52f", STREAMED_SOUND_MISSION_MOB_52F},  {"mob_52g", STREAMED_SOUND_MISSION_MOB_52G},
	{"mob_52h", STREAMED_SOUND_MISSION_MOB_52H},  {"mob_54a", STREAMED_SOUND_MISSION_MOB_54A},  {"mob_54b", STREAMED_SOUND_MISSION_MOB_54B},
	{"mob_54c", STREAMED_SOUND_MISSION_MOB_54C},  {"mob_54d", STREAMED_SOUND_MISSION_MOB_54D},  {"mob_54e", STREAMED_SOUND_MISSION_MOB_54E},
	{"mob_55a", STREAMED_SOUND_MISSION_MOB_55A},  {"mob_55b", STREAMED_SOUND_MISSION_MOB_55B},  {"mob_55c", STREAMED_SOUND_MISSION_MOB_55C},
	{"mob_55d", STREAMED_SOUND_MISSION_MOB_55D},  {"mob_55e", STREAMED_SOUND_MISSION_MOB_55E},  {"mob_55f", STREAMED_SOUND_MISSION_MOB_55F},
	{"mob_56a", STREAMED_SOUND_MISSION_MOB_56A},  {"mob_56b", STREAMED_SOUND_MISSION_MOB_56B},  {"mob_56c", STREAMED_SOUND_MISSION_MOB_56C},
	{"mob_56d", STREAMED_SOUND_MISSION_MOB_56D},  {"mob_56e", STREAMED_SOUND_MISSION_MOB_56E},  {"mob_56f", STREAMED_SOUND_MISSION_MOB_56F},
	{"mob_57a", STREAMED_SOUND_MISSION_MOB_57A},  {"mob_57b", STREAMED_SOUND_MISSION_MOB_57B},  {"mob_57c", STREAMED_SOUND_MISSION_MOB_57C},
	{"mob_57d", STREAMED_SOUND_MISSION_MOB_57D},  {"mob_57e", STREAMED_SOUND_MISSION_MOB_57E},  {"mob_58a", STREAMED_SOUND_MISSION_MOB_58A},
	{"mob_58b", STREAMED_SOUND_MISSION_MOB_58B},  {"mob_58c", STREAMED_SOUND_MISSION_MOB_58C},  {"mob_58d", STREAMED_SOUND_MISSION_MOB_58D},
	{"mob_58e", STREAMED_SOUND_MISSION_MOB_58E},  {"mob_58f", STREAMED_SOUND_MISSION_MOB_58F},  {"mob_58g", STREAMED_SOUND_MISSION_MOB_58G},
	{"mob_61a", STREAMED_SOUND_MISSION_MOB_61A},  {"mob_61b", STREAMED_SOUND_MISSION_MOB_61B},  {"mob_62a", STREAMED_SOUND_MISSION_MOB_62A},
	{"mob_62b", STREAMED_SOUND_MISSION_MOB_62B},  {"mob_62c", STREAMED_SOUND_MISSION_MOB_62C},  {"mob_62d", STREAMED_SOUND_MISSION_MOB_62D},
	{"mob_63a", STREAMED_SOUND_MISSION_MOB_63A},  {"mob_63b", STREAMED_SOUND_MISSION_MOB_63B},  {"mob_63c", STREAMED_SOUND_MISSION_MOB_63C},
	{"mob_63d", STREAMED_SOUND_MISSION_MOB_63D},  {"mob_63e", STREAMED_SOUND_MISSION_MOB_63E},  {"mob_63f", STREAMED_SOUND_MISSION_MOB_63F},
	{"mob_63g", STREAMED_SOUND_MISSION_MOB_63G},  {"mob_63h", STREAMED_SOUND_MISSION_MOB_63H},  {"mob_63i", STREAMED_SOUND_MISSION_MOB_63I},
	{"mob_63j", STREAMED_SOUND_MISSION_MOB_63J},  {"mob_66a", STREAMED_SOUND_MISSION_MOB_66A},  {"mob_66b", STREAMED_SOUND_MISSION_MOB_66B},
	{"mob_68a", STREAMED_SOUND_MISSION_MOB_68A},  {"mob_68b", STREAMED_SOUND_MISSION_MOB_68B},  {"mob_68c", STREAMED_SOUND_MISSION_MOB_68C},
	{"mob_68d", STREAMED_SOUND_MISSION_MOB_68D},  {"mob_70a", STREAMED_SOUND_MISSION_MOB_70A},  {"mob_70b", STREAMED_SOUND_MISSION_MOB_70B},
	{"mob_71a", STREAMED_SOUND_MISSION_MOB_71A},  {"mob_71b", STREAMED_SOUND_MISSION_MOB_71B},  {"mob_71c", STREAMED_SOUND_MISSION_MOB_71C},
	{"mob_71d", STREAMED_SOUND_MISSION_MOB_71D},  {"mob_71e", STREAMED_SOUND_MISSION_MOB_71E},  {"mob_71f", STREAMED_SOUND_MISSION_MOB_71F},
	{"mob_71g", STREAMED_SOUND_MISSION_MOB_71G},  {"mob_71h", STREAMED_SOUND_MISSION_MOB_71H},  {"mob_71i", STREAMED_SOUND_MISSION_MOB_71I},
	{"mob_71j", STREAMED_SOUND_MISSION_MOB_71J},  {"mob_71k", STREAMED_SOUND_MISSION_MOB_71K},  {"mob_71l", STREAMED_SOUND_MISSION_MOB_71L},
	{"mob_71m", STREAMED_SOUND_MISSION_MOB_71M},  {"mob_71n", STREAMED_SOUND_MISSION_MOB_71N},  {"mob_72a", STREAMED_SOUND_MISSION_MOB_72A},
	{"mob_72b", STREAMED_SOUND_MISSION_MOB_72B},  {"mob_72c", STREAMED_SOUND_MISSION_MOB_72C},  {"mob_72d", STREAMED_SOUND_MISSION_MOB_72D},
	{"mob_72e", STREAMED_SOUND_MISSION_MOB_72E},  {"mob_72f", STREAMED_SOUND_MISSION_MOB_72F},  {"mob_72g", STREAMED_SOUND_MISSION_MOB_72G},
	{"mob_73a", STREAMED_SOUND_MISSION_MOB_73A},  {"mob_73c", STREAMED_SOUND_MISSION_MOB_73C},  {"mob_73d", STREAMED_SOUND_MISSION_MOB_73D},
	{"mob_73f", STREAMED_SOUND_MISSION_MOB_73F},  {"mob_73g", STREAMED_SOUND_MISSION_MOB_73G},  {"mob_73i", STREAMED_SOUND_MISSION_MOB_73I},
	{"mob_95a", STREAMED_SOUND_MISSION_MOB_95A},  {"mob_96a", STREAMED_SOUND_MISSION_MOB_96A},  {"mob_98a", STREAMED_SOUND_MISSION_MOB_98A},
	{"mob_99a", STREAMED_SOUND_MISSION_MOB_99A},  {"job1_1b", STREAMED_SOUND_MISSION_JOB1_1B},  {"job1_1c", STREAMED_SOUND_MISSION_JOB1_1C},
	{"job1_1d", STREAMED_SOUND_MISSION_JOB1_1D},  {"job2_1b", STREAMED_SOUND_MISSION_JOB2_1B},  {"job2_2", STREAMED_SOUND_MISSION_JOB2_2},
	{"job2_3", STREAMED_SOUND_MISSION_JOB2_3},    {"job2_4", STREAMED_SOUND_MISSION_JOB2_4},    {"job2_5", STREAMED_SOUND_MISSION_JOB2_5},
	{"job2_6", STREAMED_SOUND_MISSION_JOB2_6},    {"job2_7", STREAMED_SOUND_MISSION_JOB2_7},    {"job2_8", STREAMED_SOUND_MISSION_JOB2_8},
	{"job2_9", STREAMED_SOUND_MISSION_JOB2_9},    {"job3_1", STREAMED_SOUND_MISSION_JOB3_1},    {"job3_2", STREAMED_SOUND_MISSION_JOB3_2},
	{"job3_3", STREAMED_SOUND_MISSION_JOB3_3},    {"job4_1", STREAMED_SOUND_MISSION_JOB4_1},    {"job4_2", STREAMED_SOUND_MISSION_JOB4_2},
	{"job4_3", STREAMED_SOUND_MISSION_JOB4_3},    {"job5_1", STREAMED_SOUND_MISSION_JOB5_1},    {"job5_2", STREAMED_SOUND_MISSION_JOB5_2},
	{"job5_3", STREAMED_SOUND_MISSION_JOB5_3},    {"bjm1_20", STREAMED_SOUND_MISSION_BJM1_20},  {"bjm1_4", STREAMED_SOUND_MISSION_BJM1_4},
	{"bjm1_5", STREAMED_SOUND_MISSION_BJM1_5},    {"merc_39", STREAMED_SOUND_MISSION_MERC_39},  {"mono_1", STREAMED_SOUND_MISSION_MONO_1},
	{"mono_2", STREAMED_SOUND_MISSION_MONO_2},    {"mono_3", STREAMED_SOUND_MISSION_MONO_3},    {"mono_4", STREAMED_SOUND_MISSION_MONO_4},
	{"mono_5", STREAMED_SOUND_MISSION_MONO_5},    {"mono_6", STREAMED_SOUND_MISSION_MONO_6},    {"mono_7", STREAMED_SOUND_MISSION_MONO_7},
	{"mono_8", STREAMED_SOUND_MISSION_MONO_8},    {"mono_9", STREAMED_SOUND_MISSION_MONO_9},    {"mono10", STREAMED_SOUND_MISSION_MONO10},
	{"mono11", STREAMED_SOUND_MISSION_MONO11},    {"mono12", STREAMED_SOUND_MISSION_MONO12},    {"mono13", STREAMED_SOUND_MISSION_MONO13},
	{"mono14", STREAMED_SOUND_MISSION_MONO14},    {"mono15", STREAMED_SOUND_MISSION_MONO15},    {"mono16", STREAMED_SOUND_MISSION_MONO16},
	{"fud_01", STREAMED_SOUND_MISSION_FUD_01},    {"fud_02", STREAMED_SOUND_MISSION_FUD_02},    {"fud_03", STREAMED_SOUND_MISSION_FUD_03},
	{"fud_04", STREAMED_SOUND_MISSION_FUD_04},    {"fud_05", STREAMED_SOUND_MISSION_FUD_05},    {"fud_06", STREAMED_SOUND_MISSION_FUD_06},
	{"fud_07", STREAMED_SOUND_MISSION_FUD_07},    {"fud_08", STREAMED_SOUND_MISSION_FUD_08},    {"fud_09", STREAMED_SOUND_MISSION_FUD_09},
	{"fud_10", STREAMED_SOUND_MISSION_FUD_10},    {"fud_11", STREAMED_SOUND_MISSION_FUD_11},    {"fud_12", STREAMED_SOUND_MISSION_FUD_12},
	{"fud_13", STREAMED_SOUND_MISSION_FUD_13},    {"fud_14", STREAMED_SOUND_MISSION_FUD_14},    {"fud_15", STREAMED_SOUND_MISSION_FUD_15},
	{"fud_16", STREAMED_SOUND_MISSION_FUD_16},    {"fud_17", STREAMED_SOUND_MISSION_FUD_17},    {"fud_18", STREAMED_SOUND_MISSION_FUD_18},
	{"fud_19", STREAMED_SOUND_MISSION_FUD_19},    {"fud_20", STREAMED_SOUND_MISSION_FUD_20},    {"burg_01", STREAMED_SOUND_MISSION_BURG_01},
	{"burg_02", STREAMED_SOUND_MISSION_BURG_02},  {"burg_03", STREAMED_SOUND_MISSION_BURG_03},  {"burg_04", STREAMED_SOUND_MISSION_BURG_04},
	{"burg_05", STREAMED_SOUND_MISSION_BURG_05},  {"burg_06", STREAMED_SOUND_MISSION_BURG_06},  {"burg_07", STREAMED_SOUND_MISSION_BURG_07},
	{"burg_08", STREAMED_SOUND_MISSION_BURG_08},  {"burg_09", STREAMED_SOUND_MISSION_BURG_09},  {"burg_10", STREAMED_SOUND_MISSION_BURG_10},
	{"burg_11", STREAMED_SOUND_MISSION_BURG_11},  {"burg_12", STREAMED_SOUND_MISSION_BURG_12},  {"crust01", STREAMED_SOUND_MISSION_CRUST01},
	{"crust02", STREAMED_SOUND_MISSION_CRUST02},  {"crust03", STREAMED_SOUND_MISSION_CRUST03},  {"crust04", STREAMED_SOUND_MISSION_CRUST04},
	{"crust05", STREAMED_SOUND_MISSION_CRUST05},  {"crust06", STREAMED_SOUND_MISSION_CRUST06},  {"crust07", STREAMED_SOUND_MISSION_CRUST07},
	{"crust08", STREAMED_SOUND_MISSION_CRUST08},  {"crust09", STREAMED_SOUND_MISSION_CRUST09},  {"band_01", STREAMED_SOUND_MISSION_BAND_01},
	{"band_02", STREAMED_SOUND_MISSION_BAND_02},  {"band_03", STREAMED_SOUND_MISSION_BAND_03},  {"band_04", STREAMED_SOUND_MISSION_BAND_04},
	{"band_05", STREAMED_SOUND_MISSION_BAND_05},  {"band_06", STREAMED_SOUND_MISSION_BAND_06},  {"band_07", STREAMED_SOUND_MISSION_BAND_07},
	{"band_08", STREAMED_SOUND_MISSION_BAND_08},  {"shaft01", STREAMED_SOUND_MISSION_SHAFT01},  {"shaft02", STREAMED_SOUND_MISSION_SHAFT02},
	{"shaft03", STREAMED_SOUND_MISSION_SHAFT03},  {"shaft04", STREAMED_SOUND_MISSION_SHAFT04},  {"shaft05", STREAMED_SOUND_MISSION_SHAFT05},
	{"shaft06", STREAMED_SOUND_MISSION_SHAFT06},  {"shaft07", STREAMED_SOUND_MISSION_SHAFT07},  {"shaft08", STREAMED_SOUND_MISSION_SHAFT08},
	{"piss_01", STREAMED_SOUND_MISSION_PISS_01},  {"piss_02", STREAMED_SOUND_MISSION_PISS_02},  {"piss_03", STREAMED_SOUND_MISSION_PISS_03},
	{"piss_04", STREAMED_SOUND_MISSION_PISS_04},  {"piss_05", STREAMED_SOUND_MISSION_PISS_05},  {"piss_06", STREAMED_SOUND_MISSION_PISS_06},
	{"piss_07", STREAMED_SOUND_MISSION_PISS_07},  {"piss_08", STREAMED_SOUND_MISSION_PISS_08},  {"piss_09", STREAMED_SOUND_MISSION_PISS_09},
	{"piss_10", STREAMED_SOUND_MISSION_PISS_10},  {"piss_11", STREAMED_SOUND_MISSION_PISS_11},  {"piss_12", STREAMED_SOUND_MISSION_PISS_12},
	{"piss_13", STREAMED_SOUND_MISSION_PISS_13},  {"piss_14", STREAMED_SOUND_MISSION_PISS_14},  {"piss_15", STREAMED_SOUND_MISSION_PISS_15},
	{"piss_16", STREAMED_SOUND_MISSION_PISS_16},  {"piss_17", STREAMED_SOUND_MISSION_PISS_17},  {"piss_18", STREAMED_SOUND_MISSION_PISS_18},
	{"piss_19", STREAMED_SOUND_MISSION_PISS_19},  {"gimme01", STREAMED_SOUND_MISSION_GIMME01},  {"gimme02", STREAMED_SOUND_MISSION_GIMME02},
	{"gimme03", STREAMED_SOUND_MISSION_GIMME03},  {"gimme04", STREAMED_SOUND_MISSION_GIMME04},  {"gimme05", STREAMED_SOUND_MISSION_GIMME05},
	{"gimme06", STREAMED_SOUND_MISSION_GIMME06},  {"gimme07", STREAMED_SOUND_MISSION_GIMME07},  {"gimme08", STREAMED_SOUND_MISSION_GIMME08},
	{"gimme09", STREAMED_SOUND_MISSION_GIMME09},  {"gimme10", STREAMED_SOUND_MISSION_GIMME10},  {"gimme11", STREAMED_SOUND_MISSION_GIMME11},
	{"gimme12", STREAMED_SOUND_MISSION_GIMME12},  {"gimme13", STREAMED_SOUND_MISSION_GIMME13},  {"gimme14", STREAMED_SOUND_MISSION_GIMME14},
	{"gimme15", STREAMED_SOUND_MISSION_GIMME15},  {"bust_01", STREAMED_SOUND_MISSION_BUST_01},  {"bust_02", STREAMED_SOUND_MISSION_BUST_02},
	{"bust_03", STREAMED_SOUND_MISSION_BUST_03},  {"bust_04", STREAMED_SOUND_MISSION_BUST_04},  {"bust_05", STREAMED_SOUND_MISSION_BUST_05},
	{"bust_06", STREAMED_SOUND_MISSION_BUST_06},  {"bust_07", STREAMED_SOUND_MISSION_BUST_07},  {"bust_08", STREAMED_SOUND_MISSION_BUST_08},
	{"bust_09", STREAMED_SOUND_MISSION_BUST_09},  {"bust_10", STREAMED_SOUND_MISSION_BUST_10},  {"bust_11", STREAMED_SOUND_MISSION_BUST_11},
	{"bust_12", STREAMED_SOUND_MISSION_BUST_12},  {"bust_13", STREAMED_SOUND_MISSION_BUST_13},  {"bust_14", STREAMED_SOUND_MISSION_BUST_14},
	{"bust_15", STREAMED_SOUND_MISSION_BUST_15},  {"bust_16", STREAMED_SOUND_MISSION_BUST_16},  {"bust_17", STREAMED_SOUND_MISSION_BUST_17},
	{"bust_18", STREAMED_SOUND_MISSION_BUST_18},  {"bust_19", STREAMED_SOUND_MISSION_BUST_19},  {"bust_20", STREAMED_SOUND_MISSION_BUST_20},
	{"bust_21", STREAMED_SOUND_MISSION_BUST_21},  {"bust_22", STREAMED_SOUND_MISSION_BUST_22},  {"bust_23", STREAMED_SOUND_MISSION_BUST_23},
	{"bust_24", STREAMED_SOUND_MISSION_BUST_24},  {"bust_25", STREAMED_SOUND_MISSION_BUST_25},  {"bust_26", STREAMED_SOUND_MISSION_BUST_26},
	{"bust_27", STREAMED_SOUND_MISSION_BUST_27},  {"bust_28", STREAMED_SOUND_MISSION_BUST_28},  {nil, 0} };

int32
FindMissionAudioSfx(const char *name)
{
	for (uint32 i = 0; MissionAudioNameSfxAssoc[i].m_pName != nil; ++i) {
		if (!CGeneral::faststricmp(MissionAudioNameSfxAssoc[i].m_pName, name))
			return MissionAudioNameSfxAssoc[i].m_nId;
	}
	debug("Can't find mission audio %s", name);
	return NO_SAMPLE;
}

bool8
cAudioManager::MissionScriptAudioUsesPoliceChannel(int32 soundMission) const
{
	return FALSE;
}

void
cAudioManager::PreloadMissionAudio(uint8 slot, Const char *name)
{
	if (m_bIsInitialised && slot < MISSION_AUDIO_SLOTS) {
		int32 missionAudioSfx = FindMissionAudioSfx(name);
		if (missionAudioSfx != NO_SAMPLE) {
			m_sMissionAudio.m_nSampleIndex[slot] = missionAudioSfx;
			m_sMissionAudio.m_nLoadingStatus[slot] = LOADING_STATUS_NOT_LOADED;
			m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_STOPPED;
			m_sMissionAudio.m_bIsPlaying[slot] = FALSE;
			m_sMissionAudio.m_nMissionAudioCounter[slot] = m_nTimeSpent * SampleManager.GetStreamedFileLength(missionAudioSfx) / 1000;
			m_sMissionAudio.m_nMissionAudioCounter[slot] *= 4;
			m_sMissionAudio.m_bIsPlayed[slot] = FALSE;
			m_sMissionAudio.m_bPredefinedProperties[slot] = TRUE;
			g_bMissionAudioLoadFailed[slot] = FALSE;
		}
	}
}

uint8
cAudioManager::GetMissionAudioLoadingStatus(uint8 slot) const
{
	if (m_bIsInitialised && slot < MISSION_AUDIO_SLOTS)
		return m_sMissionAudio.m_nLoadingStatus[slot];

	return LOADING_STATUS_LOADED;
}

void
cAudioManager::SetMissionAudioLocation(uint8 slot, float x, float y, float z)
{
	if (m_bIsInitialised && slot < MISSION_AUDIO_SLOTS) {
		m_sMissionAudio.m_bPredefinedProperties[slot] = FALSE;
		m_sMissionAudio.m_vecPos[slot] = CVector(x, y, z);
	}
}

void
cAudioManager::PlayLoadedMissionAudio(uint8 slot)
{
	if (m_bIsInitialised && slot < MISSION_AUDIO_SLOTS && m_sMissionAudio.m_nSampleIndex[slot] != NO_SAMPLE && m_sMissionAudio.m_nLoadingStatus[slot] == LOADING_STATUS_LOADED &&
	    m_sMissionAudio.m_nPlayStatus[slot] == PLAY_STATUS_STOPPED)
		m_sMissionAudio.m_bIsPlayed[slot] = TRUE;
}

bool8
cAudioManager::ShouldDuckMissionAudio(uint8 slot) const
{
	if (IsMissionAudioSamplePlaying(slot))
		return m_sMissionAudio.m_nSampleIndex[slot] != STREAMED_SOUND_MISSION_ROK2_01;
	return FALSE;
}

bool8
cAudioManager::IsMissionAudioSamplePlaying(uint8 slot) const
{
	if (m_bIsInitialised) {
		if (slot < MISSION_AUDIO_SLOTS)
			return m_sMissionAudio.m_nPlayStatus[slot] == PLAY_STATUS_PLAYING;
		else
			return TRUE;
	} else {
		static int32 cPretendFrame[MISSION_AUDIO_SLOTS] = { 1, 1 };

		return (cPretendFrame[slot]++ % 64) != 0;
	}
}

bool8
cAudioManager::IsMissionAudioSampleFinished(uint8 slot)
{
	if (m_bIsInitialised) {
		if (slot < MISSION_AUDIO_SLOTS)
			return m_sMissionAudio.m_nPlayStatus[slot] == PLAY_STATUS_FINISHED;
		else
			return TRUE;
	}

	static int32 cPretendFrame[MISSION_AUDIO_SLOTS] = { 1, 1 };

	return (cPretendFrame[slot]++ % 64) == 0;
}

void
cAudioManager::ClearMissionAudio(uint8 slot)
{
	if (m_bIsInitialised && slot < MISSION_AUDIO_SLOTS) {
		m_sMissionAudio.m_nSampleIndex[slot] = NO_SAMPLE;
		m_sMissionAudio.m_nLoadingStatus[slot] = LOADING_STATUS_NOT_LOADED;
		m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_STOPPED;
		m_sMissionAudio.m_bIsPlaying[slot] = FALSE;
		m_sMissionAudio.m_bIsPlayed[slot] = FALSE;
		m_sMissionAudio.m_bPredefinedProperties[slot] = TRUE;
		m_sMissionAudio.m_nMissionAudioCounter[slot] = 0;
		m_sMissionAudio.m_bIsMobile[slot] = FALSE;
		SampleManager.StopStreamedFile(slot + 1);
	}
}

void
cAudioManager::ProcessMissionAudioSlot(uint8 slot)
{
	float dist;
	uint8 emittingVol;
	uint8 pan;
	float distSquared;
	CVector vec;

	static uint8 nCheckPlayingDelay[MISSION_AUDIO_SLOTS] = { 0, 0 };
	static uint8 nFramesUntilFailedLoad[MISSION_AUDIO_SLOTS] = { 0, 0 };
	static uint8 nFramesForPretendPlaying[MISSION_AUDIO_SLOTS] = { 0, 0 };

	if (m_sMissionAudio.m_nSampleIndex[slot] == NO_SAMPLE) return;

	switch (m_sMissionAudio.m_nLoadingStatus[slot]) {
	case LOADING_STATUS_NOT_LOADED:
		SampleManager.PreloadStreamedFile(m_sMissionAudio.m_nSampleIndex[slot], slot + 1);
		m_sMissionAudio.m_nLoadingStatus[slot] = LOADING_STATUS_LOADED;
		nFramesUntilFailedLoad[slot] = 0;
		break;
	case LOADING_STATUS_LOADED:
		if (!m_sMissionAudio.m_bIsPlayed[slot])
			return;
		if (g_bMissionAudioLoadFailed[slot]) {
			if (m_bTimerJustReset) {
				ClearMissionAudio(slot);
				SampleManager.StopStreamedFile(slot + 1);
				nFramesForPretendPlaying[slot] = 0;
				nCheckPlayingDelay[slot] = 0;
				nFramesUntilFailedLoad[slot] = 0;
			} else if (!m_nUserPause) {
				if (++nFramesForPretendPlaying[slot] < 90) {
					m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_PLAYING;
				} else {
					m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_FINISHED;
					m_sMissionAudio.m_nSampleIndex[slot] = NO_SAMPLE;
				}
			}
			break;
		}
		switch (m_sMissionAudio.m_nPlayStatus[slot]) {
		case PLAY_STATUS_STOPPED:
			if (MissionScriptAudioUsesPoliceChannel(m_sMissionAudio.m_nSampleIndex[slot])) {
				SetMissionScriptPoliceAudio(m_sMissionAudio.m_nSampleIndex[slot]);
			} else {
				if (m_nUserPause)
					SampleManager.PauseStream(TRUE, slot + 1);
				if (m_sMissionAudio.m_bPredefinedProperties[slot]) {
					if (m_sMissionAudio.m_nSampleIndex[slot] == STREAMED_SOUND_MISSION_CAMERAL)
						SampleManager.SetStreamedVolumeAndPan(80, 0, TRUE, slot + 1);
					else if (m_sMissionAudio.m_nSampleIndex[slot] == STREAMED_SOUND_MISSION_CAMERAR)
						SampleManager.SetStreamedVolumeAndPan(80, 127, TRUE, slot + 1);
					else
						SampleManager.SetStreamedVolumeAndPan(80, 63, TRUE, slot + 1);
				} else {
					distSquared = GetDistanceSquared(m_sMissionAudio.m_vecPos[slot]);
					if (distSquared >= SQR(80.0f)) {
						emittingVol = 0;
						pan = 63;
					} else {
						emittingVol = 80;
						if (distSquared > 0.0f) {
							dist = Sqrt(distSquared);
							emittingVol = ComputeVolume(80, 80.0f, dist);
						}
						TranslateEntity(&m_sMissionAudio.m_vecPos[slot], &vec);
						pan = ComputePan(80.f, &vec);
					}
					SampleManager.SetStreamedVolumeAndPan(emittingVol, pan, TRUE, slot + 1);
				}
				SampleManager.StartPreloadedStreamedFile(slot + 1);
			}
			m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_PLAYING;
			nCheckPlayingDelay[slot] = 30;
			if (m_sMissionAudio.m_nSampleIndex[slot] >= STREAMED_SOUND_MISSION_MOB_01A && m_sMissionAudio.m_nSampleIndex[slot] <= STREAMED_SOUND_MISSION_MOB_99A)
				m_sMissionAudio.m_bIsMobile[slot] = TRUE;
			break;
		case PLAY_STATUS_PLAYING:
			if (m_bTimerJustReset) {
				ClearMissionAudio(slot);
				SampleManager.StopStreamedFile(slot + 1);
				break;
			}
			if (MissionScriptAudioUsesPoliceChannel(m_sMissionAudio.m_nSampleIndex[slot])) {
				if (!m_nUserPause) {
					if (nCheckPlayingDelay[slot]) {
						--nCheckPlayingDelay[slot];
					} else if ((g_bMissionAudioLoadFailed[slot] && m_sMissionAudio.m_nMissionAudioCounter[slot]-- == 0) || GetMissionScriptPoliceAudioPlayingStatus() == PLAY_STATUS_FINISHED) {
						m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_FINISHED;
						if (m_sMissionAudio.m_nSampleIndex[slot] >= STREAMED_SOUND_MISSION_MOB_01A && m_sMissionAudio.m_nSampleIndex[slot] <= STREAMED_SOUND_MISSION_MOB_99A)
							m_sMissionAudio.m_bIsMobile[slot] = FALSE;
						m_sMissionAudio.m_nSampleIndex[slot] = NO_SAMPLE;
						SampleManager.StopStreamedFile(slot + 1);
						m_sMissionAudio.m_nMissionAudioCounter[slot] = 0;
					}
				}
			} else if (m_sMissionAudio.m_bIsPlaying[slot]) {
				if (SampleManager.IsStreamPlaying(slot + 1) || m_nUserPause || m_nPreviousUserPause) {
					if (m_nUserPause)
						SampleManager.PauseStream(TRUE, slot + 1);
					else
					{
						SampleManager.PauseStream(FALSE, slot + 1);
						if (!m_sMissionAudio.m_bPredefinedProperties[slot]) {
							distSquared = GetDistanceSquared(m_sMissionAudio.m_vecPos[slot]);
							if (distSquared >= SQR(80.0f)) {
								emittingVol = 0;
								pan = 63;
							} else {
								emittingVol = 127;
								if (distSquared > 0.0f) {
									dist = Sqrt(distSquared);
									emittingVol = ComputeVolume(127, 80.0f, dist);
								}
								TranslateEntity(&m_sMissionAudio.m_vecPos[slot], &vec);
								pan = ComputePan(80.f, &vec);
							}
							SampleManager.SetStreamedVolumeAndPan(emittingVol, pan, TRUE, slot + 1);
						}
					}
				} else if (m_sMissionAudio.m_nSampleIndex[slot] == STREAMED_SOUND_MISSION_ROK2_01) {
					m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_STOPPED;
				} else {
					m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_FINISHED;
					if (m_sMissionAudio.m_nSampleIndex[slot] >= STREAMED_SOUND_MISSION_MOB_01A && m_sMissionAudio.m_nSampleIndex[slot] <= STREAMED_SOUND_MISSION_MOB_99A)
						m_sMissionAudio.m_bIsMobile[slot] = FALSE;
					m_sMissionAudio.m_nSampleIndex[slot] = NO_SAMPLE;
					SampleManager.StopStreamedFile(slot + 1);
					m_sMissionAudio.m_nMissionAudioCounter[slot] = 0;
				}
			} else {
				if (m_nUserPause)
					break;
				if (nCheckPlayingDelay[slot]--) {
					if (!SampleManager.IsStreamPlaying(slot + 1))
						break;
					nCheckPlayingDelay[slot] = 0;
				}
				m_sMissionAudio.m_bIsPlaying[slot] = TRUE;
			}
			break;
		default:
			break;
		}
		break;
	case LOADING_STATUS_FAILED:
		if (++nFramesUntilFailedLoad[slot] >= 120) {
			nFramesForPretendPlaying[slot] = 0;
			g_bMissionAudioLoadFailed[slot] = TRUE;
			nFramesUntilFailedLoad[slot] = 0;
			m_sMissionAudio.m_nLoadingStatus[slot] = LOADING_STATUS_LOADED;
		}
		break;
	default:
		break;
	}
}

void
cAudioManager::ProcessMissionAudio()
{
	if (!m_bIsInitialised) return;
	
	for (int i = 0; i < MISSION_AUDIO_SLOTS; i++)
		ProcessMissionAudioSlot(i);

	if (m_sMissionAudio.m_bIsMobile[0] || m_sMissionAudio.m_bIsMobile[1])
		field_5538 = 64;
	else if (field_5538 < 127) {
		field_5538 += 5;
		if (field_5538 > 127)
			field_5538 = 127;
	}
}
#pragma endregion All the mission audio stuff
