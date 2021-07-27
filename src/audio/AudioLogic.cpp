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
	{SFX_CAR_REV_PORSHE, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9890, NEW_DOOR},
	{SFX_CAR_REV_PATHFINDER, SFX_BANK_PATHFINDER, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9935, OLD_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 11487, SFX_CAR_HORN_JEEP, 9900, OLD_DOOR},
	{SFX_CAR_REV_PORSHE, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9890, NEW_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_HORN_JEEP, 9960, TRUCK_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 12893, SFX_CAR_HORN_JEEP, 9500, OLD_DOOR},
	{SFX_CAR_REV_MERC, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 10706, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_PATHFINDER, SFX_BANK_PATHFINDER, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9800, TRUCK_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_POLICE_SIREN_SLOW, 10588, TRUCK_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 31478, SFX_CAR_HORN_JEEP, 9800, TRUCK_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_BMW328, 9538, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_HORN_JEEP, 10000, OLD_DOOR},
	{SFX_CAR_REV_PORSHE, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 11487, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18286, SFX_CAR_HORN_JEEP, 9600, OLD_DOOR},
	{SFX_CAR_REV_PORSHE, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 22295, SFX_AMBULANCE_SI, 12688, OLD_DOOR},
	{SFX_CAR_REV_MERC, SFX_BANK_MERC, SFX_CAR_HORN_PORSCHE, 9271, SFX_POLICE_SIREN_SLOW, 11471, NEW_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 12170, SFX_CAR_HORN_JEEP, 9400, OLD_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_BMW328, 11000, SFX_CAR_HORN_JEEP, 9300, OLD_DOOR},
	{SFX_CAR_REV_PATHFINDER, SFX_BANK_PATHFINDER, SFX_CAR_HORN_BMW328, 10796, SFX_CAR_HORN_JEEP, 9200, NEW_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 11487, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_PATHFINDER, SFX_BANK_PATHFINDER, SFX_CAR_HORN_PICKUP, 10924, SFX_CAR_HORN_JEEP, 9000, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 11025, SFX_ICE_CREAM_TUNE, 11025, OLD_DOOR},
	{SFX_CAR_REV_HOTROD, SFX_BANK_HOTROD, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9100, OLD_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 11487, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_MERC, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 10706, SFX_POLICE_SIREN_SLOW, 10511, NEW_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 17260, SFX_POLICE_SIREN_SLOW, 11029, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_HORN_JEEP, 9300, OLD_DOOR},
	{SFX_CAR_REV_COBRA, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10400, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_BUS2, 11652, SFX_CAR_HORN_JEEP, 9500, BUS_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_HORN_JEEP, 9600, TRUCK_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 28043, SFX_CAR_HORN_JEEP, 9700, TRUCK_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_BUS, 16291, SFX_CAR_HORN_JEEP, 10100, BUS_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_HORN_JEEP, 9900, OLD_DOOR},
	{SFX_CAR_REV_PACARD, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10233, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_RC_REV, SFX_BANK_RC, SFX_CAR_HORN_PICKUP, 20000, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 31478, SFX_CAR_HORN_JEEP, 9800, TRUCK_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 31478, SFX_CAR_HORN_JEEP, 9800, TRUCK_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_PONTIAC, SFX_CAR_HORN_BMW328, 9003, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_COBRA, SFX_BANK_COBRA, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_PORSHE, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_HOTROD, SFX_BANK_HOTROD, SFX_CAR_HORN_56CHEV, 11487, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_PATHFINDER, SFX_BANK_PATHFINDER, SFX_CAR_HORN_PICKUP, 10924, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 28043, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18286, SFX_CAR_HORN_JEEP, 9900, OLD_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_PONTIAC, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18286, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_SPIDER, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_HORN_JEEP, 9700, OLD_DOOR},
	{SFX_CAR_REV_COBRA, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10400, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_COBRA, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10400, SFX_CAR_HORN_JEEP, 9700, NEW_DOOR},
	{SFX_CAR_REV_PORSHE, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_TRUCK, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 31478, SFX_CAR_HORN_JEEP, 9800, TRUCK_DOOR},
	{SFX_CAR_REV_HOTROD, SFX_BANK_HOTROD, SFX_CAR_HORN_JEEP, 25400, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_COBRA, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10400, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_COBRA, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10400, SFX_CAR_HORN_JEEP, 9800, OLD_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_POLICE_SIREN_SLOW, 11912, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_POLICE_SIREN_SLOW, 11912, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_POLICE_SIREN_SLOW, 11912, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9900, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9300, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_VTWI, SFX_BANK_VTWIN, SFX_CAR_HORN_JEEP, 26313, SFX_CAR_HORN_JEEP, 10000, NEW_DOOR},
	{SFX_MOPED_REV, SFX_BANK_MOPED, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 9100, NEW_DOOR},
	{SFX_MOPED_REV, SFX_BANK_MOPED, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 9100, NEW_DOOR},
	{SFX_CAR_REV_SPORTCAR, SFX_BANK_SPORTS_BIKE, SFX_CAR_HORN_JEEP, 27000, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_MOPED_REV, SFX_BANK_MOPED, SFX_CAR_HORN_JEEP, 31000, SFX_CAR_HORN_JEEP, 9500, NEW_DOOR},
	{SFX_CAR_REV_VTWI, SFX_BANK_VTWIN, SFX_CAR_HORN_PICKUP, 11000, SFX_CAR_HORN_JEEP, 9400, NEW_DOOR},
	{SFX_CAR_REV_VTWI, SFX_BANK_VTWIN, SFX_CAR_HORN_JEEP, 26313, SFX_CAR_HORN_JEEP, 10000, NEW_DOOR},
	{SFX_CAR_REV_HONDA, SFX_BANK_HONDA250, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 9000, NEW_DOOR},
	{SFX_CAR_REV_HONDA, SFX_BANK_HONDA250, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 9000, NEW_DOOR},
	{SFX_CAR_RC_HELI, SFX_BANK_RC_HELI, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9600, NEW_DOOR},
	{SFX_CAR_RC_HELI, SFX_BANK_RC_HELI, SFX_CAR_HORN_JEEP, 30000, SFX_CAR_HORN_JEEP, 15000, NEW_DOOR},
	{SFX_CAR_ACCEL_22, SFX_BANK_HELI_APACHE, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9200, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9100, TRUCK_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9800, NEW_DOOR},
	{SFX_CAR_REV_PONT, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_HORN_JEEP, 9000, TRUCK_DOOR}
};

const eSfxSample aEngineSounds[][2] = {
	{ SFX_CAR_IDLE_PONT, SFX_CAR_REV_PONT },
	{ SFX_CAR_IDLE_PORSHE, SFX_CAR_REV_PORSHE },
	{ SFX_CAR_IDLE_SPIDER, SFX_CAR_REV_SPIDER },
	{ SFX_CAR_IDLE_MERC, SFX_CAR_REV_MERC },
	{ SFX_CAR_IDLE_TRUCK, SFX_CAR_REV_TRUCK },
	{ SFX_CAR_IDLE_HOTROD, SFX_CAR_REV_HOTROD },
	{ SFX_CAR_IDLE_COBRA, SFX_CAR_REV_COBRA },
	{ SFX_CAR_IDLE_PONT2, SFX_CAR_REV_PONT2 },
	{ SFX_CAR_IDLE_CADI, SFX_CAR_REV_CADI },
	{ SFX_CAR_IDLE_PATHFINDER, SFX_CAR_REV_PATHFINDER },
	{ SFX_CAR_IDLE_PACARD, SFX_CAR_REV_PACARD },
	{ SFX_CAR_IDLE_GOLFCART, SFX_CAR_REV_GOLFCART },
	{ SFX_CAR_IDLE_GOLFCART, SFX_CAR_REV_GOLFCART },
	{ SFX_CAR_IDLE_GOLFCART, SFX_CAR_REV_GOLFCART },
	{ SFX_CAR_IDLE_GOLFCART, SFX_CAR_REV_GOLFCART },
	{ SFX_CAR_IDLE_GOLFCART, SFX_CAR_REV_GOLFCART },
	{ SFX_CAR_IDLE_VTWI, SFX_CAR_REV_VTWI },
	{ SFX_MOPED_IDLE, SFX_MOPED_REV },
	{ SFX_CAR_IDLE_HONDA, SFX_CAR_REV_HONDA },
	{ SFX_CAR_IDLE_SPORTCAR, SFX_CAR_REV_SPORTCAR },
	{ SFX_CAR_IDLE_UNUSED1, SFX_CAR_REV_UNUSED1 },
	{ SFX_CAR_IDLE_UNUSED2, SFX_CAR_REV_UNUSED2 },
	{ SFX_CAR_IDLE_UNUSED3, SFX_CAR_REV_UNUSED3 },
	{ SFX_CAR_IDLE_UNUSED4, SFX_CAR_REV_UNUSED4 },
};

bool8 bPlayerJustEnteredCar;

const bool8 hornPatternsArray[8][44] = {
    {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    {FALSE, FALSE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE,  FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE, TRUE, TRUE, FALSE, FALSE},
    {FALSE, FALSE, TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE,  FALSE,
     FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE, FALSE, FALSE},
    {FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE, TRUE,  TRUE,
     TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE},
    {FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE,
     TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
    {FALSE, FALSE, TRUE,  TRUE,  TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE,  TRUE,
     FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE},
    {FALSE, FALSE, TRUE, TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, TRUE, TRUE,  TRUE,
     TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE}
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
#ifdef GTA_TRAIN
		case VEHICLE_TYPE_TRAIN:
			ProcessTrainNoise(params);
			ProcessVehicleOneShots(params);
			break;
#endif
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
					m_sQueueSample.m_nSampleIndex = aEngineSounds[aVehicleSettings[params.m_nIndex].m_nBank - CAR_SFX_BANKS_OFFSET][0];
					m_sQueueSample.m_nCounter = 52;
					freq = 10000.0f * modificator + 22050;
				} else {
					m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nAccelerationSampleIndex;
					m_sQueueSample.m_nCounter = 2;
				}
			} else {
				if (veh->m_fGasPedal < 0.02f) {
					m_sQueueSample.m_nSampleIndex = aEngineSounds[aVehicleSettings[params.m_nIndex].m_nBank - CAR_SFX_BANKS_OFFSET][0];
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
				m_sQueueSample.m_nSampleIndex = SFX_CAR_REV_GOLFCART;
			m_sQueueSample.m_nFrequency = freq + 20 * m_sQueueSample.m_nBankIndex % 100;
		}
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nReleasingVolumeModificator = 3;
		if (m_sQueueSample.m_nSampleIndex == SFX_CAR_IDLE_TRUCK || m_sQueueSample.m_nSampleIndex == SFX_CAR_REV_TRUCK)
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
	soundOffset = gBankStartOffset[engineSoundType] - gBankStartOffset[CAR_SFX_BANKS_OFFSET];
	//soundOffset = 3 * (engineSoundType - CAR_SFX_BANKS_OFFSET);
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
	/*switch (engineSoundType) {
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
	}*/
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
		AddPlayerCarSample(vol, freq, aEngineSounds[engineSoundType - CAR_SFX_BANKS_OFFSET][0], SFX_BANK_0, 52, TRUE);

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
				AddPlayerCarSample(vol, freq, aEngineSounds[engineSoundType - CAR_SFX_BANKS_OFFSET][1], SFX_BANK_0, 2, TRUE);
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
				if(!pPed->HasWeaponSlot(WEAPONSLOT_SUBMACHINEGUN) || (params.m_pVehicle->GetModelIndex() == MI_PREDATOR && !pPed->IsPedDoingDriveByShooting())) {
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
	const float SOUND_INTENSITY = 140.0f;

	CTrain *train;
	uint8 emittingVol;
	float speedMultipler;

	if (params.m_fDistance >= SQR(SOUND_INTENSITY))
		return FALSE;

	if (params.m_fVelocityChange > 0.0f) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		train = (CTrain *)params.m_pVehicle;
		speedMultipler = Min(1.0f, train->m_fSpeed * 250.f / 51.f);
		emittingVol = (70.f * speedMultipler);
		if (train->m_fWagonPosition == 0.0f) {
			m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume != 0) {
				m_sQueueSample.m_nCounter = 32;
				m_sQueueSample.m_nSampleIndex = SFX_TRAIN;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nReleasingVolumeModificator = 2;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TRAIN);
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
		//const float SOUND_INTENSITY = 70.0f;
		//if (params.m_fDistance < SQR(SOUND_INTENSITY)) {
		//	m_sQueueSample.m_nVolume = ComputeVolume(emittingVol, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
		//	if (m_sQueueSample.m_nVolume != 0) {
		//		m_sQueueSample.m_nCounter = 33;
		//		m_sQueueSample.m_nSampleIndex = SFX_TRAIN_NEAR;
		//		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		//		m_sQueueSample.m_bIs2D = FALSE;
		//		m_sQueueSample.m_nReleasingVolumeModificator = 5;
		//		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TRAIN_NEAR) + 100 * m_sQueueSample.m_nEntityIndex % 987;
		//		m_sQueueSample.m_nLoopCount = 0;
		//		m_sQueueSample.m_nEmittingVolume = emittingVol;
		//		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		//		m_sQueueSample.m_fSpeedMultiplier = 6.0f;
		//		m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
		//		m_sQueueSample.m_bReleasingSoundFlag = FALSE;
		//		m_sQueueSample.m_nReleasingVolumeDivider = 3;
		//		m_sQueueSample.m_bReverbFlag = TRUE;
		//		m_sQueueSample.m_bRequireReflection = FALSE;
		//		AddSampleToRequestedQueue();
		//	}
		//}
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
struct sToniReactions
{
	uint32 sfx[4];
	uint32 count[4];
};

const sToniReactions aReactions[8] = {
    {{SFX_TONI_PISSED_OFF_CRASH_01, SFX_TONI_ANGRY_CRASH_01, SFX_TONI_WISECRACKING_CRASH_01, NULL}, {25, 29, 17, 0}},
    {{SFX_TONI_PISSED_OFF_FIGHT_01, SFX_TONI_ANGRY_FIGHT_01, SFX_TONI_WISECRACKING_FIGHT_01, NULL}, {18, 39, 20, 0}},
    {{SFX_TONI_PISSED_OFF_JACKED_01, SFX_TONI_ANGRY_JACKED_01, SFX_TONI_WISECRACKING_JACKED_01, NULL}, {11, 16, 17, 0}},
    {{SFX_TONI_PISSED_OFF_JACKING_01, SFX_TONI_ANGRY_JACKING_01, SFX_TONI_WISECRACKING_JACKING_01, NULL}, {25, 33, 12, 0}},
    {{SFX_TONI_ANGRY_PICK_UP_HOOKER_01, SFX_TONI_ANGRY_PICK_UP_HOOKER_01, SFX_TONI_WISECRACKING_PICK_UP_HOOKER_01, NULL}, {8, 8, 11, 0}},
    {{SFX_TONI_PISSED_OFF_PULL_GUN_01, SFX_TONI_ANGRY_PULL_GUN_01, SFX_TONI_WISECRACKING_PULL_GUN_01, NULL}, {18, 29, 19, 0}},
    {{SFX_TONI_CALM_SEX_01, SFX_TONI_ANGRY_SEX_01, SFX_TONI_ANGRY_SEX_01, SFX_TONI_WISECRACKING_SEX_01}, {11, 10, 10, 10}},
    {{SFX_TONI_CALM_SHOOT_01, SFX_TONI_PISSED_OFF_SHOOT_01, SFX_TONI_ANGRY_SHOOT_01, SFX_TONI_WISECRACKING_SHOOT_01}, {30, 31, 36, 26}}
};

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
		case SOUND_186:
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
						// LCS:removed for now
						//if (fightMove == FIGHTMOVE_BACKLEFT || fightMove == FIGHTMOVE_STDPUNCH || fightMove == FIGHTMOVE_PUNCH ||
						if (
							ped->m_nPedState == PED_ATTACK) {
							CEntity* damageEntity = ped->m_pDamageEntity;
							if (!damageEntity)
								m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 2 + SFX_HAMMER_HIT_1;
							else if (damageEntity->GetType() != ENTITY_TYPE_PED)
								m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 2 + SFX_HAMMER_HIT_1;
							// LCS:removed for now
							//else if (((CPed*)damageEntity)->m_curFightMove != FIGHTMOVE_HITHEAD)
							else if(1)
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
				//m_sQueueSample.m_nSampleIndex = SFX_M60_TAIL_LEFT;
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
			pedComment.m_nSampleIndex = NO_SAMPLE; //GetRandomNumberInRange(m_sQueueSample.m_nEntityIndex % 4, SFX_POLICE_HELI_1, SFX_POLICE_HELI_20);
			break;
		case SOUND_PED_VCPA_PLAYER_FOUND:
			soundIntensity = 400.0f;
			pedComment.m_nSampleIndex = NO_SAMPLE; //m_anRandomTable[m_sQueueSample.m_nEntityIndex % 4] % 23 + SFX_POLICE_BOAT_1;
			break;
		case SOUND_INJURED_PED_MALE_OUCH:
			soundIntensity = 40.0f;
			pedComment.m_nSampleIndex = NO_SAMPLE; // = GetRandomNumberInRange(m_sQueueSample.m_nEntityIndex % 4, SFX_GENERIC_MALE_GRUNT_1, SFX_GENERIC_MALE_GRUNT_41);
			break;
		case SOUND_INJURED_PED_FEMALE:
			soundIntensity = 40.0f;
			pedComment.m_nSampleIndex = NO_SAMPLE; // = GetRandomNumberInRange(m_sQueueSample.m_nEntityIndex % 4, SFX_GENERIC_FEMALE_GRUNT_1, SFX_GENERIC_FEMALE_GRUNT_33);
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
	if(ped->m_nPedState != PED_FALL || sound == SOUND_PED_DAMAGE || sound == SOUND_PED_HIT || sound == SOUND_PED_LAND) {
		if(ped->m_getUpTimer == UINT32_MAX || ped->m_getUpTimer > CTimer::GetTimeInMilliseconds()) {
			if(sound != SOUND_PED_DAMAGE && sound != SOUND_PED_HIT && sound != SOUND_PED_LAND) return NO_SAMPLE;
		}
		if(ped->IsPlayer()) return GetPlayerTalkSfx(ped, sound);
		switch(ped->GetModelIndex()) {
		case MI_PLAYER: return GetPlayerTalkSfx(ped, sound);
		case MI_COP: return GetCopTalkSfx(ped, sound);
		case MI_SWAT: return GetSwatTalkSfx(ped, sound);
		case MI_FBI: return GetFBITalkSfx(ped, sound);
		case MI_ARMY: return GetArmyTalkSfx(ped, sound);
		case MI_MEDIC: return GetMedicTalkSfx(ped, sound);
		case MI_FIREMAN: return GetFiremanTalkSfx(ped, sound);
		case MI_MALE01: return GetDefaultTalkSfx(ped, sound);
/*	LCS: removed for now
		case MI_TAXI_D:
		case MI_MALE03: return GetHFORITalkSfx(ped, sound);
		case MI_PIMP: return GetHFOSTTalkSfx(ped, sound);
		case MI_CRIMINAL01: return GetHMYSTTalkSfx(ped, sound);
		case MI_CRIMINAL02: return GetHMOSTTalkSfx(ped, sound);
		case MI_MALE02: return GetHFYRITalkSfx(ped, sound);
		case MI_FATMALE01:
		case MI_FATMALE02: return GetHMORITalkSfx(ped, sound);
		case MI_FEMALE01: return GetHFYBETalkSfx(ped, sound);
		case MI_FEMALE02: return GetHFOBETalkSfx(ped, sound);
		case MI_FEMALE03: return GetHMYBETalkSfx(ped, sound);
		case MI_FATFEMALE01: return GetHMYRITalkSfx(ped, sound);
		case MI_FATFEMALE02: return GetHFYBUTalkSfx(ped, sound);
		case MI_PROSTITUTE: return GetHFYMDTalkSfx(ped, sound);
		case MI_PROSTITUTE2: return GetHFYCGTalkSfx(ped, sound);
		case MI_P_MAN1: return GetHFYPRTalkSfx(ped, sound);
		case MI_P_MAN2: return GetHFOTRTalkSfx(ped, sound);
		case MI_P_WOM1: return GetHMOTRTalkSfx(ped, sound);
		case MI_P_WOM2: return GetHMYAPTalkSfx(ped, sound);
		case MI_CT_MAN1: return GetHMOCATalkSfx(ped, sound);
		case MI_CT_MAN2: return GetBMODKTalkSfx(ped, sound);
		case MI_CT_WOM1: return GetBMYCRTalkSfx(ped, sound);
		case MI_CT_WOM2: return GetBFYSTTalkSfx(ped, sound);
		case MI_LI_MAN1: return GetBFOSTTalkSfx(ped, sound);
		case MI_LI_MAN2: return GetBMYSTTalkSfx(ped, sound);
		case MI_LI_WOM1: return GetBMOSTTalkSfx(ped, sound);
		case MI_LI_WOM2: return GetBFYRITalkSfx(ped, sound);
		case MI_DOCKER1: 
		case MI_DOCKER2: return GetBFORITalkSfx(ped, sound);
		case MI_SCUM_MAN: return GetBFYBETalkSfx(ped, sound);
		case MI_SCUM_WOM: return GetBMYBETalkSfx(ped, sound);
		case MI_WORKER1: return GetBFOBETalkSfx(ped, sound);
		case MI_WORKER2: return GetBMOBETalkSfx(ped, sound);
		case MI_B_MAN1: return GetBMYBUTalkSfx(ped, sound);
		case MI_B_MAN2: return GetBFYPRTalkSfx(ped, sound);
		case MI_B_MAN3: return GetBFOTRTalkSfx(ped, sound);
		case MI_B_WOM1: return GetBMOTRTalkSfx(ped, sound);
		case MI_B_WOM2: return GetBMYPITalkSfx(ped, sound);
		case MI_B_WOM3: return GetBMYBBTalkSfx(ped, sound);
		case MI_MOD_MAN: return GetWMYCRTalkSfx(ped, sound);
		case MI_MOD_WOM: return GetWFYSTTalkSfx(ped, sound);
		case MI_ST_MAN: return GetWFOSTTalkSfx(ped, sound);
		case MI_ST_WOM: return GetWMYSTTalkSfx(ped, sound);
		case MI_FAN_MAN1: return GetWMOSTTalkSfx(ped, sound);
		case MI_FAN_MAN2: return GetWFYRITalkSfx(ped, sound);
		case MI_FAN_WOM: return GetWFORITalkSfx(ped, sound);
		case MI_HOS_MAN: return GetWMYRITalkSfx(ped, sound);
		case MI_HOS_WOM: return GetWMORITalkSfx(ped, sound);
		case MI_CONST1: return GetWFYBETalkSfx(ped, sound);
		case MI_CONST2: return GetWMYBETalkSfx(ped, sound);
		case MI_SHOPPER1: return GetWFOBETalkSfx(ped, sound);
		case MI_SHOPPER2: return GetWMOBETalkSfx(ped, sound);
		case MI_SHOPPER3: return GetWMYCWTalkSfx(ped, sound);
		case MI_STUD_MAN: return GetWMYGOTalkSfx(ped, sound);
		case MI_STUD_WOM: return GetWFOGOTalkSfx(ped, sound);
		case MI_CAS_MAN: return GetWMOGOTalkSfx(ped, sound);
		case MI_CAS_WOM: return GetWFYLGTalkSfx(ped, sound);
		case MI_CAMP_MAN: return GetCAMPMANTalkSfx(ped, sound);
		case MI_CAMP_WOM: return GetCAMPWOMTalkSfx(ped, sound);
		case MI_JFOTO: return GetJFOTOTalkSfx(ped, sound);
		case MI_JMOTO: return GetJMOTOTalkSfx(ped, sound);
		case MI_GANG01: return GetGangLeoneATalkSfx(ped, sound);
		case MI_GANG02: return GetGangLeoneBTalkSfx(ped, sound);
		case MI_GANG03: return GetGangTriadATalkSfx(ped, sound);
		case MI_GANG04: return GetGangTriadBTalkSfx(ped, sound);
		case MI_GANG05: return GetGangDiabloATalkSfx(ped, sound);
		case MI_GANG06: return GetGangDiabloBTalkSfx(ped, sound);
		case MI_GANG07: return GetGangYakuzaATalkSfx(ped, sound);
		case MI_GANG08: return GetGangYakuzaBTalkSfx(ped, sound);
		case MI_GANG09: return GetGangYardieATalkSfx(ped, sound);
		case MI_GANG10: return GetGangYardieBTalkSfx(ped, sound);
		case MI_GANG11: return GetGangColumbianATalkSfx(ped, sound);
		case MI_GANG12: return GetGangColumbianBTalkSfx(ped, sound);
		case MI_GANG13: return GetGangHoodATalkSfx(ped, sound);
		case MI_GANG14: return GetGangHoodBTalkSfx(ped, sound);
		case MI_GANG15: return GetGangForelliATalkSfx(ped, sound);
		case MI_GANG16: return GetGangForelliBTalkSfx(ped, sound);
		case MI_GANG17: return GetGangSindaccosATalkSfx(ped, sound);
		case MI_GANG18: return GetGangSindaccosBTalkSfx(ped, sound);
/*    LCS: cut
		case MI_HFYST: return GetHFYSTTalkSfx(ped, sound);
		case MI_HMOBE: return GetHMOBETalkSfx(ped, sound);
		case MI_BMYRI: return GetBMYRITalkSfx(ped, sound);
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
*/
		case MI_VICE1:
		case MI_VICE2:
		case MI_VICE3:
		case MI_VICE4:
		case MI_VICE5:
		case MI_VICE7:
		case MI_VICE8:// return GetViceWhiteTalkSfx(ped, sound);
		case MI_VICE6:// return GetViceBlackTalkSfx(ped, sound);
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
		case MI_SPECIAL21: //GetSpecialCharacterTalkSfx(ped, sound)
			return NO_SAMPLE;
		default: return GetGenericMaleTalkSfx(ped, sound);
		}
	}

	return NO_SAMPLE;
}

void
cAudioManager::GetPhrase(uint32 &phrase, uint32 &prevPhrase, uint32 sample, uint32 maxOffset) const
{
	if (maxOffset == 0) {
		phrase = prevPhrase = NO_SAMPLE;
		return;
	}

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
	case SOUND_PED_DEATH:
	case SOUND_PED_PLAYER_AFTERSEX: return NO_SAMPLE;
	case SOUND_PED_DAMAGE:
	case SOUND_PED_BULLET_HIT: GetPhrase(sfx, ped->m_lastComment, SFX_TONI_GENERAL_IMP_HI_01, 16); break;
	case SOUND_PED_HIT:
	case SOUND_PED_DEFEND: GetPhrase(sfx, ped->m_lastComment, SFX_TONI_GENERAL_IMP_LOW_01, 15); break;
	case SOUND_PED_LAND: GetPhrase(sfx, ped->m_lastComment, SFX_TONI_GENERAL_HIT_GROUND_01, 12); break;
	case SOUND_PED_BURNING: GetPhrase(sfx, ped->m_lastComment, SFX_TONI_GENERAL_ON_FIRE_01, 7); break;
	case SOUND_PED_PLAYER_REACTTOCOP:
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_PISSED_OFF_BUSTED_01, 12);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_ANGRY_BUSTED_01, 16);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_BUSTED_01, 25);
			break;
		}
		break;
	case SOUND_PED_ON_FIRE: {
		cooldown_phrase(8);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_CALM:
		case PLAYER_MOOD_PISSED_OFF:
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[7].sfx[m_nPlayerMood], aReactions[7].count[m_nPlayerMood]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_SEX_01, 30); // bruh
			break;
		}
		break;
	}
	case SOUND_PED_AIMING: {
		cooldown_phrase(8);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[5].sfx[m_nPlayerMood-1], aReactions[5].count[m_nPlayerMood-1]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_PULL_GUN_01, 35);
			break;
		}
		break;
	}
	case SOUND_PED_CAR_JACKING: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[3].sfx[m_nPlayerMood-1], aReactions[3].count[m_nPlayerMood-1]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_JACKING_01, 35);
			break;
		}
		break;
	}
	case SOUND_PED_MUGGING: {
		cooldown_phrase(8);
		sfx = NO_SAMPLE;
		break;
	}
	case SOUND_PED_CAR_JACKED: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[2].sfx[m_nPlayerMood-1], aReactions[2].count[m_nPlayerMood-1]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_JACKED_01, 23);
			break;
		}
		break;
	}
	case SOUND_PED_PLAYER_BEFORESEX:
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_CALM:
		case PLAYER_MOOD_PISSED_OFF:
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[6].sfx[m_nPlayerMood], aReactions[6].count[m_nPlayerMood]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_SEX_01, 10);
			break;
		}
		break;
	case SOUND_PED_PLAYER_FARFROMCOPS: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_PISSED_OFF_CHASED_01, 25);
			break;
		case PLAYER_MOOD_ANGRY:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_ANGRY_CHASED_01, 25);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_CHASED_01, 20);
			break;
		}
		break;
	}
	case SOUND_PED_ATTACK: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[1].sfx[m_nPlayerMood-1], aReactions[1].count[m_nPlayerMood-1]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_FIGHT_01, 42);
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
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[0].sfx[m_nPlayerMood-1], aReactions[0].count[m_nPlayerMood-1]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_CRASH_01, 31);
			break;
		}
		break;
	}
	case SOUND_PED_SOLICIT: {
		cooldown_phrase(4);
		switch(m_nPlayerMood) {
		case PLAYER_MOOD_PISSED_OFF:
		case PLAYER_MOOD_ANGRY:
		case PLAYER_MOOD_WISECRACKING:
			GetPhrase(sfx, ped->m_lastComment, aReactions[4].sfx[m_nPlayerMood-1], aReactions[4].count[m_nPlayerMood-1]);
			break;
		default:
			GetPhrase(sfx, ped->m_lastComment, SFX_TONI_CALM_PICK_UP_HOOKER_01, 18);
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
	case SOUND_PED_ARREST_COP: GetPhrase(sfx, ped->m_lastComment, SFX_COP1_ARREST_1, 2); break;
	case SOUND_PED_PULLOUTWEAPON:
	case SOUND_PED_ACCIDENTREACTION1: 
	case SOUND_PED_COP_MANYCOPSAROUND: 
	case SOUND_PED_GUNAIMEDAT2:
	case SOUND_PED_COP_ALONE:
	case SOUND_PED_GUNAIMEDAT3:
		return NO_SAMPLE;
	case SOUND_PED_COP_TARGETING: GetPhrase(sfx, ped->m_lastComment, SFX_COP1_SHOOT_1, 6); break;
	case SOUND_PED_COP_ASK_FOR_ID: {
		cooldown_phrase(4);
		return NO_SAMPLE;
	}
	case SOUND_PED_COP_LITTLECOPSAROUND:
		objective = FindPlayerPed()->m_nPedState;
		if(objective == PED_ARRESTED || objective == PED_DEAD || objective == PED_DIE) return NO_SAMPLE;
		GetPhrase(sfx, ped->m_lastComment, SFX_COP1_CHASE_FOOT_1, 6);
		break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_COP1_FIGHT_1, 3); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, ped->m_lastComment, SFX_COP1_DODGE_1, 2); break;
	case SOUND_PED_PED_COLLISION:
		if(FindPlayerPed()->m_pWanted->GetWantedLevel() > 0)
			GetPhrase(sfx, ped->m_lastComment, SFX_COP1_BUMP_1, 5);
		else
			return NO_SAMPLE;
		break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return (SFX_COP2_ARREST_1 - SFX_COP1_ARREST_1) * (m_sQueueSample.m_nEntityIndex % 6) + sfx;
}

uint32
cAudioManager::GetSwatTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	switch(sound) {
	case SOUND_PED_COP_HELIPILOTPHRASE: GetPhrase(sfx, ped->m_lastComment, SFX_SWAT_VOICE_1_ROPE_1, 2); break;
	case SOUND_PED_COP_TARGETING: GetPhrase(sfx, ped->m_lastComment, SFX_SWAT_VOICE_1_SHOOT_1, 5); break;
	case SOUND_PED_EVADE: return NO_SAMPLE;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	sfx += (SFX_SWAT_VOICE_2_ROPE_1 - SFX_SWAT_VOICE_1_ROPE_1) * (m_sQueueSample.m_nEntityIndex % 2);
	return sfx;
}

uint32
cAudioManager::GetFBITalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;
	switch(sound) {
	case SOUND_PED_COP_TARGETING: GetPhrase(sfx, ped->m_lastComment, SFX_FBI_VOICE_1_SHOOT_1, 5); break;
	case SOUND_PED_COP_MANYCOPSAROUND:
	case SOUND_PED_GUNAIMEDAT2:
	case SOUND_PED_GUNAIMEDAT3:
	case SOUND_PED_CRASH_VEHICLE:
	case SOUND_PED_CRASH_CAR: return NO_SAMPLE;
#ifdef FIX_BUGS
	case SOUND_PED_LEAVE_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_FBI_VOICE_1_VAN_1, 2); break;
#endif
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
#ifdef FIX_BUGS
	sfx += (SFX_FBI_VOICE_2_SHOOT_1 - SFX_FBI_VOICE_1_SHOOT_1) * (m_sQueueSample.m_nEntityIndex % 2);
#else
	sfx += 5 * (m_sQueueSample.m_nEntityIndex % 2);
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
	case SOUND_PED_HEALING: GetPhrase(sfx, ped->m_lastComment, SFX_AMBULAN_VOICE_1_VICTIM_1, 17); break;
	case SOUND_PED_LEAVE_VEHICLE: GetPhrase(sfx, ped->m_lastComment, SFX_AMBULAN_VOICE_1_VAN_1, 10); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	sfx += (SFX_AMBULAN_VOICE_2_VAN_1 - SFX_AMBULAN_VOICE_1_VAN_1) * (m_sQueueSample.m_nEntityIndex % 2);
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
	case SOUND_PED_HANDS_COWER: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_GUN_THREATENED_1, 2); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_JACKED_CAR_1, 2); break;
	case SOUND_PED_ROBBED:
	case SOUND_PED_ACCIDENTREACTION1:
	case SOUND_PED_TAXI_WAIT:
	case SOUND_PED_EVADE:
	case SOUND_PED_FLEE_RUN:
	case SOUND_PED_CRASH_VEHICLE:
	case SOUND_PED_WAIT_DOUBLEBACK:
#ifdef FIX_BUGS
	case SOUND_PED_CHAT_SEXY_MALE:
#else
	case SOUND_PED_CHAT_SEXY_FEMALE:
#endif
		GetPhrase(sfx, ped->m_lastComment, NO_SAMPLE, 0);
		break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_FIGHT_1, 3); break;
	case SOUND_PED_CRASH_CAR: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_CRASH_CAR_1, 2); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_DRIVER_BLOCKED_1, 2); break;
	case SOUND_PED_CHAT_EVENT: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_SHOCKED_1, 1); break;
	case SOUND_PED_PED_COLLISION: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_BUMP_1, 3); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, ped->m_lastComment, SFX_MALE01_CHAT_1, 4); break;
	default: return GetGenericMaleTalkSfx(ped, sound);
	}
	return sfx;
}
/*
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
// LCS removed for now
//	if(ped->GetModelIndex() == MI_SGB) sfx += (SFX_STREET_GANG_2_BLOCKED_1 - SFX_STREET_GANG_1_BLOCKED_1);
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
*/
uint32
cAudioManager::GetGenericMaleTalkSfx(CPed *ped, int16 sound)
{
	uint32 sfx;

	m_bGenericSfx = TRUE;
	switch(sound) {
	case SOUND_PED_DEATH: GetPhrase(sfx, ped->m_lastComment, SFX_MALE_DEATH_01, 28); break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND: GetPhrase(sfx, ped->m_lastComment, SFX_MALE_PAIN_01, 51); break;
	case SOUND_PED_BURNING: GetPhrase(sfx, ped->m_lastComment, SFX_MALE_PAIN_ON_FIRE_01, 21); break;
	case SOUND_PED_FLEE_SPRINT: GetPhrase(sfx, ped->m_lastComment, SFX_MALE_PANIC_01, 23); break;
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
	case SOUND_PED_DEATH: GetPhrase(sfx, ped->m_lastComment, SFX_FEMALE_DEATH_01, 16); break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND: GetPhrase(sfx, ped->m_lastComment, SFX_FEMALE_PAIN_01, 34); break;
	case SOUND_PED_BURNING: GetPhrase(sfx, ped->m_lastComment, SFX_FEMALE_PAIN_ON_FIRE_01, 11); break;
	case SOUND_PED_FLEE_SPRINT: GetPhrase(sfx, ped->m_lastComment, SFX_FEMALE_PANIC_01, 13); break;
	case SOUND_PED_PLAYER_BEFORESEX: GetPhrase(sfx, ped->m_lastComment, SFX_FEMALE_SEX_01, 11); break;
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
				if (sampleIndex >= SFX_TONI_ANGRY_BUSTED_01 && sampleIndex <= SFX_TONI_WISECRACKING_SHOOT_26) { // check if player sfx
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
	//const float SOUND_INTENSITY = 18.0f;
	//const uint8 EMITTING_VOLUME = 50;

	//float distance;

	//for (int i = 0; i < ARRAY_SIZE(aVecExtraSoundPosition); i++) {
	//	m_sQueueSample.m_vecPos = aVecExtraSoundPosition[i];
	//	distance = GetDistanceSquared(m_sQueueSample.m_vecPos);
	//	if (distance < SQR(SOUND_INTENSITY)) {
	//		m_sQueueSample.m_fDistance = Sqrt(distance);
	//		m_sQueueSample.m_nVolume = ComputeVolume(EMITTING_VOLUME, SOUND_INTENSITY, m_sQueueSample.m_fDistance);
	//		if (m_sQueueSample.m_nVolume != 0) {
	//			m_sQueueSample.m_nCounter = i;
	//			m_sQueueSample.m_nSampleIndex = SFX_ARCADE;
	//			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
	//			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ARCADE);
	//			m_sQueueSample.m_bIs2D = FALSE;
	//			m_sQueueSample.m_nLoopCount = 0;
	//			m_sQueueSample.m_bReleasingSoundFlag = FALSE;
	//			m_sQueueSample.m_nReleasingVolumeModificator = 4;
	//			m_sQueueSample.m_fSpeedMultiplier = 3.0f;
	//			m_sQueueSample.m_nEmittingVolume = EMITTING_VOLUME;
	//			SET_LOOP_OFFSETS(SFX_ARCADE)
	//			m_sQueueSample.m_bReverbFlag = TRUE;
	//			m_sQueueSample.m_fSoundIntensity = SOUND_INTENSITY;
	//			m_sQueueSample.m_bRequireReflection = FALSE;
	//			m_sQueueSample.m_nReleasingVolumeDivider = 3;
	//			AddSampleToRequestedQueue();
	//		}
	//	}
	//}
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
	//case SCRIPT_SOUND_PAYPHONE_RINGING:
	//	m_sQueueSample.m_fSoundIntensity = 80.0f;
	//	m_sQueueSample.m_nSampleIndex = SFX_PHONE_RING;
	//	m_sQueueSample.m_nBankIndex = SFX_BANK_0;
	//	emittingVolume = 80;
	//	m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PHONE_RING);
	//	m_sQueueSample.m_nReleasingVolumeModificator = 1;
	//	m_sQueueSample.m_fSpeedMultiplier = 2.0f;
	//	m_sQueueSample.m_bIs2D = FALSE;
	//	m_sQueueSample.m_bRequireReflection = FALSE;
	//	break;
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
			m_sQueueSample.m_nSampleIndex = SFX_FE_INFO_LEFT;
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
			//m_sQueueSample.m_nSampleIndex = SFX_HURRICANE_MA;
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
			if (m_sQueueSample.m_nSampleIndex > SFX_RADIO_DIAL_3)
				m_sQueueSample.m_nSampleIndex -= 3;
			radioDial = m_sQueueSample.m_nSampleIndex;
			break;
		case SOUND_FRONTEND_HIGHLIGHT_OPTION:
			//stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_FE_HIGHLIGHT;
			break;
		case SOUND_FRONTEND_ENTER_OR_ADJUST:
			//stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_FE_SELECT;
			break;
		case SOUND_FRONTEND_BACK:
			//stereo = TRUE;
			m_sQueueSample.m_nSampleIndex = SFX_FE_BACK;
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
		//if (m_sQueueSample.m_nSampleIndex == SFX_HURRICANE_MA && CWeather::Wind > 1.0f)
		//	m_sQueueSample.m_nVolume = (CWeather::Wind - 1.0f) * m_sQueueSample.m_nVolume;
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
	// TODO: LCS
/*	if (CStats::CommercialPassed && m_sQueueSample.m_fDistance < 450.f) {
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
	}*/
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
	{"JDAISH2", SFX_JD_SHOCKED_2},
	{"JDAICR2", SFX_JD_CRASH_CAR_2},
	{"JDAICR1", SFX_JD_CRASH_CAR_1},
	{"MHAIJC1", SFX_MICKEY_JACKED_CAR_1},
	{"JDAICR3", SFX_JD_CRASH_CAR_3},
	{"CSHUTR", SFX_CSHUTR},
	{"DRKNOCK", SFX_DRKNOCK},
	{"NEDS4CA", SFX_NEDS4CA},
	{"RUNPAST", SFX_RUNPAST},
	{"LEAR", SFX_LEAR},
	{"TING", SFX_TING},
	{"CLICK", SFX_CLICK},
	{"BBell", SFX_BRIDGE_BELL},
	{"CHOP_1", SFX_CHOP_1},
	{"CHOP_2", SFX_CHOP_2},
	{"MAC4_CM", SFX_MAC4_CM},
	{"MAC4_CN", SFX_MAC4_CN},
	{"MAC4_CO", SFX_MAC4_CO},
	{"MAC4_CP", SFX_MAC4_CP},
	{"MAC4_CQ", SFX_MAC4_CQ},
	{"MAC4_CR", SFX_MAC4_CR},
	{"MAC4_CS", SFX_MAC4_CS},
	{"SBell", SFX_SHOPBELL},
	{"PROSCR1", SFX_PROSTITUTE_SHOCKED_2},
	{"PROSCR2", SFX_PROSTITUTE_SHOCKED_3},
	{"COLT_45", SFX_COLT_45},
	{"SAL4_AJ", SFX_SAL4_AJ},
	{"JD_SLPN", SFX_JD_SLPN},
	{"MDON2AH", SFX_MDON2AH},
	{"SAL4_EA", SFX_SAL4_EA},
	{"mobring", SFX_SFX_RING},
	{"pagring", SFX_SFX_PAGER_RING},
	{"carrev", SFX_SFX_WILLIE_CAR_REV},
	{"bikerev", SFX_SFX_WILLIE_BIKE_REV},
	{"liftop", SFX_SFX_LIFT_OPEN},
	{"liftcl", SFX_SFX_LIFT_CLOSE},
	{"liftrun", SFX_SFX_LIFT_RUNNING},
	{"liftbel", SFX_SFX_LIFT_BELL},
	{"inlift", SFX_SFX_IN_LIFT},
	{"caml", SFX_SFX_CAMERA_LEFT},
	{"camr", SFX_SFX_CAMERA_RIGHT},
	{"cheer1", SFX_SFX_CHEER1},
	{"cheer2", SFX_SFX_CHEER2},
	{"cheer3", SFX_SFX_CHEER3},
	{"cheer4", SFX_SFX_CHEER4},
	{"ooh1", SFX_SFX_OOH1},
	{"ooh2", SFX_SFX_OOH2},
	{"lanstp1", SFX_SFX_LANSTP1},
	{"lanstp2", SFX_SFX_LANSTP2},
	{"lanamu1", SFX_SFX_LANAMU1},
	{"lanamu2", SFX_SFX_LANAMU2},
	{"airhrnl", SFX_SFX_AIRHORN_LEFT},
	{"airhrnr", SFX_SFX_AIRHORN_RIGHT},
	{"sniper", SFX_SFX_SNIPER_SHOT_1},
	{"snipsh", SFX_SFX_SNIPER_SHOT_2},
	{"bloroof", SFX_SFX_BLOW_ROOF},
	{"sfx_01", SFX_SFX_SFX_01},
	{"sfx_02", SFX_SFX_SFX_02},
	{"ANG1_AA", SFX_SFX_ANG1_AA},
	{"ANG1_AB", SFX_SFX_ANG1_AB},
	{"ANG1_AC", SFX_SFX_ANG1_AC},
	{"ANG1_AD", SFX_SFX_ANG1_AD},
	{"ANG1_AE", SFX_SFX_ANG1_AE},
	{"ANG1_AF", SFX_SFX_ANG1_AF},
	{"ANG1_AG", SFX_SFX_ANG1_AG},
	{"ANG1_AH", SFX_SFX_ANG1_AH},
	{"ANG1_AI", SFX_SFX_ANG1_AI},
	{"ANG1_AJ", SFX_SFX_ANG1_AJ},
	{"ANG1_AK", SFX_SFX_ANG1_AK},
	{"ANG1_AL", SFX_SFX_ANG1_AL},
	{"ANG1_AM", SFX_SFX_ANG1_AM},
	{"ANG1_AN", SFX_SFX_ANG1_AN},
	{"ANG1_AO", SFX_SFX_ANG1_AO},
	{"ANG1_AP", SFX_SFX_ANG1_AP},
	{"ANG1_AQ", SFX_SFX_ANG1_AQ},
	{"ANG1_AR", SFX_SFX_ANG1_AR},
	{"ANG1_AS", SFX_SFX_ANG1_AS},
	{"ANG1_AT", SFX_SFX_ANG1_AT},
	{"ANG1_AU", SFX_SFX_ANG1_AU},
	{"ANG1_AV", SFX_SFX_ANG1_AV},
	{"ANG1_AW", SFX_SFX_ANG1_AW},
	{"JDT3_AA", SFX_SFX_JDT3_AA},
	{"JDT3_AB", SFX_SFX_JDT3_AB},
	{"JDT3_AC", SFX_SFX_JDT3_AC},
	{"JDT3_AD", SFX_SFX_JDT3_AD},
	{"JDT3_AE", SFX_SFX_JDT3_AE},
	{"JDT3_AG", SFX_SFX_JDT3_AG},
	{"JDT3_AH", SFX_SFX_JDT3_AH},
	{"JDT3_BA", SFX_SFX_JDT3_BA},
	{"JDT3_BB", SFX_SFX_JDT3_BB},
	{"JDT3_BC", SFX_SFX_JDT3_BC},
	{"JDT3_BD", SFX_SFX_JDT3_BD},
	{"JDT3_BE", SFX_SFX_JDT3_BE},
	{"JDT3_BF", SFX_SFX_JDT3_BF},
	{"MAR4_AA", SFX_SFX_MAR4_AA},
	{"MAR4_AB", SFX_SFX_MAR4_AB},
	{"MAR4_AC", SFX_SFX_MAR4_AC},
	{"MAR4_AD", SFX_SFX_MAR4_AD},
	{"MAR4_BA", SFX_SFX_MAR4_BA},
	{"MAR4_BB", SFX_SFX_MAR4_BB},
	{"MAR4_BC", SFX_SFX_MAR4_BC},
	{"MAR4_BD", SFX_SFX_MAR4_BD},
	{"MAR4_BE", SFX_SFX_MAR4_BE},
	{"MAR4_BF", SFX_SFX_MAR4_BF},
	{"MAR4_BG", SFX_SFX_MAR4_BG},
	{"AVEN_AA", SFX_AVEN_AA},
	{"AVEN_AB", SFX_AVEN_AB},
	{"AVEN_AC", SFX_AVEN_AC},
	{"AVEN_AD", SFX_AVEN_AD},
	{"AVEN_AE", SFX_AVEN_AE},
	{"AVEN_AF", SFX_AVEN_AF},
	{"AVEN_AG", SFX_AVEN_AG},
	{"AVEN_AH", SFX_AVEN_AH},
	{"AVEN_AI", SFX_AVEN_AI},
	{"AVEN_AJ", SFX_AVEN_AJ},
	{"AVEN_AK", SFX_AVEN_AK},
	{"AVEN_AL", SFX_AVEN_AL},
	{"AVEN_AM", SFX_AVEN_AM},
	{"AVEN_AN", SFX_AVEN_AN},
	{"AVEN_AO", SFX_AVEN_AO},
	{"AVEN_AP", SFX_AVEN_AP},
	{"AVEN_AQ", SFX_AVEN_AQ},
	{"AVEN_AR", SFX_AVEN_AR},
	{"AVEN_AS", SFX_AVEN_AS},
	{"AVEN_AT", SFX_AVEN_AT},
	{"AVEN_AU", SFX_AVEN_AU},
	{"AVEN_AV", SFX_AVEN_AV},
	{"AVEN_AW", SFX_AVEN_AW},
	{"AVE1_AA", SFX_AVE1_AA},
	{"AVE1_AB", SFX_AVE1_AB},
	{"AVE1_AC", SFX_AVE1_AC},
	{"AVE1_AD", SFX_AVE1_AD},
	{"AVE1_AE", SFX_AVE1_AE},
	{"AVE1_AF", SFX_AVE1_AF},
	{"AVE1_AG", SFX_AVE1_AG},
	{"AVE2_AA", SFX_AVE2_AA},
	{"AVE2_AC", SFX_AVE2_AC},
	{"AVE2_AD", SFX_AVE2_AD},
	{"AVE2_AE", SFX_AVE2_AE},
	{"AVE2_AG", SFX_AVE2_AG},
	{"AVE2_AH", SFX_AVE2_AH},
	{"AVE3_AA", SFX_AVE3_AA},
	{"AVE3_AB", SFX_AVE3_AB},
	{"AVE3_AC", SFX_AVE3_AC},
	{"AVE3_AD", SFX_AVE3_AD},
	{"AVE3_AE", SFX_AVE3_AE},
	{"AVE3_AF", SFX_AVE3_AF},
	{"AVE3_AG", SFX_AVE3_AG},
	{"AVE4_AA", SFX_AVE4_AA},
	{"AVE4_AB", SFX_AVE4_AB},
	{"AVE4_AD", SFX_AVE4_AD},
	{"AVE4_AE", SFX_AVE4_AE},
	{"AVE4_AF", SFX_AVE4_AF},
	{"AVE4_AG", SFX_AVE4_AG},
	{"AVE4_AH", SFX_AVE4_AH},
	{"AVE5_AA", SFX_AVE5_AA},
	{"AVE5_AB", SFX_AVE5_AB},
	{"AVE5_AC", SFX_AVE5_AC},
	{"AVE5_AD", SFX_AVE5_AD},
	{"AVE5_AE", SFX_AVE5_AE},
	{"AVE5_AF", SFX_AVE5_AF},
	{"AVE5_AG", SFX_AVE5_AG},
	{"AVE6_AA", SFX_AVE6_AA},
	{"AVE6_AB", SFX_AVE6_AB},
	{"AVE6_AC", SFX_AVE6_AC},
	{"AVE6_AD", SFX_AVE6_AD},
	{"AVE6_AE", SFX_AVE6_AE},
	{"BONS2BA", SFX_BONS2BA},
	{"BONS2BB", SFX_BONS2BB},
	{"BONS2BC", SFX_BONS2BC},
	{"BONS2BD", SFX_BONS2BD},
	{"BONS2BE", SFX_BONS2BE},
	{"CAD1_AA", SFX_CAD1_AA},
	{"CAD1_AB", SFX_CAD1_AB},
	{"CAD1_AC", SFX_CAD1_AC},
	{"CAD1_AD", SFX_CAD1_AD},
	{"CAD1_AE", SFX_CAD1_AE},
	{"CAD2_AA", SFX_CAD2_AA},
	{"CAD2_AB", SFX_CAD2_AB},
	{"CAD2_AC", SFX_CAD2_AC},
	{"CAD2_AD", SFX_CAD2_AD},
	{"CAD2_AE", SFX_CAD2_AE},
	{"CAD2_AF", SFX_CAD2_AF},
	{"CAD3_AA", SFX_CAD3_AA},
	{"CAD3_AB", SFX_CAD3_AB},
	{"CAD3_AC", SFX_CAD3_AC},
	{"CAD3_AD", SFX_CAD3_AD},
	{"CAD3_AE", SFX_CAD3_AE},
	{"CAD3_AF", SFX_CAD3_AF},
	{"CAD4_AA", SFX_CAD4_AA},
	{"CAD4_AB", SFX_CAD4_AB},
	{"CAD4_AC", SFX_CAD4_AC},
	{"CAD4_AD", SFX_CAD4_AD},
	{"CAD4_AE", SFX_CAD4_AE},
	{"CAD4_AF", SFX_CAD4_AF},
	{"CAD5_AA", SFX_CAD5_AA},
	{"CAD5_AB", SFX_CAD5_AB},
	{"CAD5_AC", SFX_CAD5_AC},
	{"CAD5_AD", SFX_CAD5_AD},
	{"CAD5_AE", SFX_CAD5_AE},
	{"CAD5_AF", SFX_CAD5_AF},
	{"CAD6_AA", SFX_CAD6_AA},
	{"CAD6_AB", SFX_CAD6_AB},
	{"CAD6_AC", SFX_CAD6_AC},
	{"CAD6_AD", SFX_CAD6_AD},
	{"CAD6_AE", SFX_CAD6_AE},
	{"CAD6_AF", SFX_CAD6_AF},
	{"CAD7_AB", SFX_CAD7_AB},
	{"CAD7_AC", SFX_CAD7_AC},
	{"CAD7_AD", SFX_CAD7_AD},
	{"CAD7_AE", SFX_CAD7_AE},
	{"CAD8_AB", SFX_CAD8_AB},
	{"CAD8_AC", SFX_CAD8_AC},
	{"CAD8_AD", SFX_CAD8_AD},
	{"CAD8_AE", SFX_CAD8_AE},
	{"CAD8_AF", SFX_CAD8_AF},
	{"CAD9_AA", SFX_CAD9_AA},
	{"CAD9_AB", SFX_CAD9_AB},
	{"CAD9_AC", SFX_CAD9_AC},
	{"CAD9_AD", SFX_CAD9_AD},
	{"CAD9_AE", SFX_CAD9_AE},
	{"CAD9_AF", SFX_CAD9_AF},
	{"DONH1CA", SFX_DONH1CA},
	{"DONH1DA", SFX_DONH1DA},
	{"DONH1DB", SFX_DONH1DB},
	{"DONH1EA", SFX_DONH1EA},
	{"DONH1EB", SFX_DONH1EB},
	{"DONH1EC", SFX_DONH1EC},
	{"DONH1ED", SFX_DONH1ED},
	{"DONH1EE", SFX_DONH1EE},
	{"DONH1FA", SFX_DONH1FA},
	{"DONH1GA", SFX_DONH1GA},
	{"DONH1GB", SFX_DONH1GB},
	{"DONH1GC", SFX_DONH1GC},
	{"DONH1HA", SFX_DONH1HA},
	{"DONH1IA", SFX_DONH1IA},
	{"DONH1IB", SFX_DONH1IB},
	{"DONH1JA", SFX_DONH1JA},
	{"DONH1JB", SFX_DONH1JB},
	{"DONH1JC", SFX_DONH1JC},
	{"DONH1JD", SFX_DONH1JD},
	{"DONH1JE", SFX_DONH1JE},
	{"DONH2AA", SFX_DONH2AA},
	{"DONH2AB", SFX_DONH2AB},
	{"DONH2AC", SFX_DONH2AC},
	{"DONH2AD", SFX_DONH2AD},
	{"DONH2AF", SFX_DONH2AF},
	{"DONH2AG", SFX_DONH2AG},
	{"DONH2AH", SFX_DONH2AH},
	{"DONH2BA", SFX_DONH2BA},
	{"DONH2BB", SFX_DONH2BB},
	{"DONH2BC", SFX_DONH2BC},
	{"DONH2BD", SFX_DONH2BD},
	{"DONH2BE", SFX_DONH2BE},
	{"DONH2BF", SFX_DONH2BF},
	{"DONH2BG", SFX_DONH2BG},
	{"DONH2BH", SFX_DONH2BH},
	{"DONH2BI", SFX_DONH2BI},
	{"DONH2BJ", SFX_DONH2BJ},
	{"DONH2BK", SFX_DONH2BK},
	{"DONH2BL", SFX_DONH2BL},
	{"DONH2CA", SFX_DONH2CA},
	{"DONH2CB", SFX_DONH2CB},
	{"DONH2CC", SFX_DONH2CC},
	{"DONH2CD", SFX_DONH2CD},
	{"DONH2CE", SFX_DONH2CE},
	{"DONH2CF", SFX_DONH2CF},
	{"DONH2CG", SFX_DONH2CG},
	{"DONH2DA", SFX_DONH2DA},
	{"DONH2DB", SFX_DONH2DB},
	{"DONH2DC", SFX_DONH2DC},
	{"DONH2EA", SFX_DONH2EA},
	{"DONH2EC", SFX_DONH2EC},
	{"DONH3AA", SFX_DONH3AA},
	{"DONH3AB", SFX_DONH3AB},
	{"DONH3AC", SFX_DONH3AC},
	{"DONH3AD", SFX_DONH3AD},
	{"DONH3AE", SFX_DONH3AE},
	{"DONH3AF", SFX_DONH3AF},
	{"DONH3AG", SFX_DONH3AG},
	{"DONH3AH", SFX_DONH3AH},
	{"DONH3AI", SFX_DONH3AI},
	{"DONH3BA", SFX_DONH3BA},
	{"DONH3BB", SFX_DONH3BB},
	{"DONH3CA", SFX_DONH3CA},
	{"DONH3DA", SFX_DONH3DA},
	{"DONH3EA", SFX_DONH3EA},
	{"DONH3EB", SFX_DONH3EB},
	{"DONH3EC", SFX_DONH3EC},
	{"DONH3ED", SFX_DONH3ED},
	{"DONH3EE", SFX_DONH3EE},
	{"DONH3EF", SFX_DONH3EF},
	{"DONH3FA", SFX_DONH3FA},
	{"DONH3GA", SFX_DONH3GA},
	{"DONH3GB", SFX_DONH3GB},
	{"DONH3GC", SFX_DONH3GC},
	{"DONH3GD", SFX_DONH3GD},
	{"DONH3GE", SFX_DONH3GE},
	{"DONH3GF", SFX_DONH3GF},
	{"DONH3HA", SFX_DONH3HA},
	{"DONH3HB", SFX_DONH3HB},
	{"DONH4AA", SFX_DONH4AA},
	{"DONH4AB", SFX_DONH4AB},
	{"DONH4AC", SFX_DONH4AC},
	{"DONH4AD", SFX_DONH4AD},
	{"DONH4AE", SFX_DONH4AE},
	{"DONH4AF", SFX_DONH4AF},
	{"DONH4AG", SFX_DONH4AG},
	{"DONH4AH", SFX_DONH4AH},
	{"DONH4AI", SFX_DONH4AI},
	{"DONH4AJ", SFX_DONH4AJ},
	{"DONH5AA", SFX_DONH5AA},
	{"DONH5AB", SFX_DONH5AB},
	{"DONH5AC", SFX_DONH5AC},
	{"DONH5AD", SFX_DONH5AD},
	{"DONH5AE", SFX_DONH5AE},
	{"DONH5AF", SFX_DONH5AF},
	{"DONH5AG", SFX_DONH5AG},
	{"DONH5AH", SFX_DONH5AH},
	{"DONH5AI", SFX_DONH5AI},
	{"DONH5AJ", SFX_DONH5AJ},
	{"DONH5BA", SFX_DONH5BA},
	{"DONH6BA", SFX_DONH6BA},
	{"DONH6CA", SFX_DONH6CA},
	{"DONH6CB", SFX_DONH6CB},
	{"DONH6DA", SFX_DONH6DA},
	{"DONH6DB", SFX_DONH6DB},
	{"DONH6EA", SFX_DONH6EA},
	{"DONH6EB", SFX_DONH6EB},
	{"DONH6EC", SFX_DONH6EC},
	{"DONH6FA", SFX_DONH6FA},
	{"DONH6GA", SFX_DONH6GA},
	{"DONH6GB", SFX_DONH6GB},
	{"DONH6GC", SFX_DONH6GC},
	{"DONH6GD", SFX_DONH6GD},
	{"DONH6GF", SFX_DONH6GF},
	{"DONS1AA", SFX_DONS1AA},
	{"DONS1AB", SFX_DONS1AB},
	{"DONS1AC", SFX_DONS1AC},
	{"DONS1BA", SFX_DONS1BA},
	{"DONS1BB", SFX_DONS1BB},
	{"DONS2AA", SFX_DONS2AA},
	{"DONS2AB", SFX_DONS2AB},
	{"DONS2AC", SFX_DONS2AC},
	{"DONS2AD", SFX_DONS2AD},
	{"DONS2AE", SFX_DONS2AE},
	{"DONS2AF", SFX_DONS2AF},
	{"DONS2BA", SFX_DONS2BA},
	{"DONS2BB", SFX_DONS2BB},
	{"DONS2BC", SFX_DONS2BC},
	{"DONS2BD", SFX_DONS2BD},
	{"DONS2BE", SFX_DONS2BE},
	{"DONS2CA", SFX_DONS2CA},
	{"DONS2CB", SFX_DONS2CB},
	{"DONS2CC", SFX_DONS2CC},
	{"DONS2CD", SFX_DONS2CD},
	{"DONS2CE", SFX_DONS2CE},
	{"DONS2CF", SFX_DONS2CF},
	{"DONS2CG", SFX_DONS2CG},
	{"DONS2CH", SFX_DONS2CH},
	{"DONS2CI", SFX_DONS2CI},
	{"DONS2CJ", SFX_DONS2CJ},
	{"DONS2CK", SFX_DONS2CK},
	{"DONS2CL", SFX_DONS2CL},
	{"DONS2CM", SFX_DONS2CM},
	{"DONS2CN", SFX_DONS2CN},
	{"DONS4AA", SFX_DONS4AA},
	{"DONS4AB", SFX_DONS4AB},
	{"DONS4AC", SFX_DONS4AC},
	{"DONS4AD", SFX_DONS4AD},
	{"DONS4AE", SFX_DONS4AE},
	{"DONS4AF", SFX_DONS4AF},
	{"DONS5AA", SFX_DONS5AA},
	{"DONS5AB", SFX_DONS5AB},
	{"DONS5AC", SFX_DONS5AC},
	{"DONS5AD", SFX_DONS5AD},
	{"DONS5AE", SFX_DONS5AE},
	{"DONS5BA", SFX_DONS5BA},
	{"DONS5BB", SFX_DONS5BB},
	{"DONS5BC", SFX_DONS5BC},
	{"DONS5BD", SFX_DONS5BD},
	{"DONS5BE", SFX_DONS5BE},
	{"DONS5CA", SFX_DONS5CA},
	{"DONS5DA", SFX_DONS5DA},
	{"DONS5EA", SFX_DONS5EA},
	{"DONS5EB", SFX_DONS5EB},
	{"DONS6AA", SFX_DONS6AA},
	{"DONS6AB", SFX_DONS6AB},
	{"DONS6AC", SFX_DONS6AC},
	{"DONS6AD", SFX_DONS6AD},
	{"DONS6AE", SFX_DONS6AE},
	{"DONS6AF", SFX_DONS6AF},
	{"DONS6AG", SFX_DONS6AG},
	{"DONS7AA", SFX_DONS7AA},
	{"DONS7AB", SFX_DONS7AB},
	{"DONS7AC", SFX_DONS7AC},
	{"DONS7AD", SFX_DONS7AD},
	{"DONS7AE", SFX_DONS7AE},
	{"DONS7AF", SFX_DONS7AF},
	{"DONS7AG", SFX_DONS7AG},
	{"HIT1_AA", SFX_HIT1_AA},
	{"HIT1_AB", SFX_HIT1_AB},
	{"HIT1_AC", SFX_HIT1_AC},
	{"HIT1_AD", SFX_HIT1_AD},
	{"HIT1_AE", SFX_HIT1_AE},
	{"HIT1_AF", SFX_HIT1_AF},
	{"HIT1_AG", SFX_HIT1_AG},
	{"HIT2_AA", SFX_HIT2_AA},
	{"HIT2_AB", SFX_HIT2_AB},
	{"HIT2_AC", SFX_HIT2_AC},
	{"HIT2_AD", SFX_HIT2_AD},
	{"HIT2_AE", SFX_HIT2_AE},
	{"HIT2_AF", SFX_HIT2_AF},
	{"HIT2_AG", SFX_HIT2_AG},
	{"HIT2_AH", SFX_HIT2_AH},
	{"HIT3_AA", SFX_HIT3_AA},
	{"HIT3_AB", SFX_HIT3_AB},
	{"HIT3_AC", SFX_HIT3_AC},
	{"HIT3_AD", SFX_HIT3_AD},
	{"HIT3_AE", SFX_HIT3_AE},
	{"HIT3_AF", SFX_HIT3_AF},
	{"HIT3_AG", SFX_HIT3_AG},
	{"HITM_AA", SFX_HITM_AA},
	{"HITM_AB", SFX_HITM_AB},
	{"HITM_AC", SFX_HITM_AC},
	{"HITM_AD", SFX_HITM_AD},
	{"JDT1_BA", SFX_JDT1_BA},
	{"JDT1_BB", SFX_JDT1_BB},
	{"JDT1_CA", SFX_JDT1_CA},
	{"JDT1_CB", SFX_JDT1_CB},
	{"JDT1_DA", SFX_JDT1_DA},
	{"JDT1_DB", SFX_JDT1_DB},
	{"JDT1_DC", SFX_JDT1_DC},
	{"JDT1_DD", SFX_JDT1_DD},
	{"JDT1_DE", SFX_JDT1_DE},
	{"JDT1_DF", SFX_JDT1_DF},
	{"JDT1_DG", SFX_JDT1_DG},
	{"JDT1_DH", SFX_JDT1_DH},
	{"JDT1_DI", SFX_JDT1_DI},
	{"JDT1_DJ", SFX_JDT1_DJ},
	{"JDT1_EA", SFX_JDT1_EA},
	{"JDT1_EB", SFX_JDT1_EB},
	{"JDT1_EC", SFX_JDT1_EC},
	{"JDT1_ED", SFX_JDT1_ED},
	{"JDT1_EE", SFX_JDT1_EE},
	{"JDT1_FA", SFX_JDT1_FA},
	{"JDT1_FB", SFX_JDT1_FB},
	{"JDT1_FC", SFX_JDT1_FC},
	{"JDT1_FD", SFX_JDT1_FD},
	{"JDT1_FE", SFX_JDT1_FE},
	{"JDT1_FF", SFX_JDT1_FF},
	{"JDT1_GA", SFX_JDT1_GA},
	{"JDT1_HA", SFX_JDT1_HA},
	{"JDT1_HB", SFX_JDT1_HB},
	{"JDT1_HC", SFX_JDT1_HC},
	{"JDT1_HD", SFX_JDT1_HD},
	{"JDT1_HE", SFX_JDT1_HE},
	{"JDT1_HF", SFX_JDT1_HF},
	{"JDT1_IA", SFX_JDT1_IA},
	{"JDT1_JA", SFX_JDT1_JA},
	{"JDT1_JB", SFX_JDT1_JB},
	{"JDT1_KA", SFX_JDT1_KA},
	{"JDT1_KB", SFX_JDT1_KB},
	{"JDT1_KC", SFX_JDT1_KC},
	{"JDT1_KD", SFX_JDT1_KD},
	{"JDT1_KE", SFX_JDT1_KE},
	{"JDT1_KF", SFX_JDT1_KF},
	{"JDT1_LA", SFX_JDT1_LA},
	{"JDT1_LB", SFX_JDT1_LB},
	{"JDT2_AA", SFX_JDT2_AA},
	{"JDT2_AB", SFX_JDT2_AB},
	{"JDT2_AC", SFX_JDT2_AC},
	{"JDT2_AD", SFX_JDT2_AD},
	{"JDT2_AE", SFX_JDT2_AE},
	{"JDT2_AF", SFX_JDT2_AF},
	{"JDT2_AG", SFX_JDT2_AG},
	{"JDT2_AH", SFX_JDT2_AH},
	{"JDT2_BA", SFX_JDT2_BA},
	{"JDT2_BB", SFX_JDT2_BB},
	{"JDT2_BC", SFX_JDT2_BC},
	{"JDT2_CA", SFX_JDT2_CA},
	{"JDT2_CB", SFX_JDT2_CB},
	{"JDT2_DA", SFX_JDT2_DA},
	{"JDT2_DC", SFX_JDT2_DC},
	{"JDT2_DD", SFX_JDT2_DD},
	{"JDT2_DE", SFX_JDT2_DE},
	{"JDT2_DF", SFX_JDT2_DF},
	{"JDT3_AA", SFX_JDT3_AA},
	{"JDT3_AB", SFX_JDT3_AB},
	{"JDT3_AC", SFX_JDT3_AC},
	{"JDT3_AD", SFX_JDT3_AD},
	{"JDT3_AE", SFX_JDT3_AE},
	{"JDT3_AG", SFX_JDT3_AG},
	{"JDT3_AH", SFX_JDT3_AH},
	{"JDT3_BA", SFX_JDT3_BA},
	{"JDT3_BB", SFX_JDT3_BB},
	{"JDT3_BC", SFX_JDT3_BC},
	{"JDT3_BD", SFX_JDT3_BD},
	{"JDT3_BE", SFX_JDT3_BE},
	{"JDT3_BF", SFX_JDT3_BF},
	{"JDT4_AA", SFX_JDT4_AA},
	{"JDT4_AB", SFX_JDT4_AB},
	{"JDT4_AC", SFX_JDT4_AC},
	{"JDT4_AD", SFX_JDT4_AD},
	{"JDT4_AE", SFX_JDT4_AE},
	{"JDT4_AF", SFX_JDT4_AF},
	{"JDT5_BA", SFX_JDT5_BA},
	{"JDT5_CA", SFX_JDT5_CA},
	{"JDT5_CC", SFX_JDT5_CC},
	{"JDT5_CD", SFX_JDT5_CD},
	{"JDT5_CE", SFX_JDT5_CE},
	{"JDT5_CG", SFX_JDT5_CG},
	{"JDT5_CI", SFX_JDT5_CI},
	{"JDT5_DA", SFX_JDT5_DA},
	{"JDT5_EA", SFX_JDT5_EA},
	{"JDT5_EB", SFX_JDT5_EB},
	{"JDT5_EC", SFX_JDT5_EC},
	{"JDT5_ED", SFX_JDT5_ED},
	{"JDT5_EE", SFX_JDT5_EE},
	{"JDT6_AA", SFX_JDT6_AA},
	{"JDT6_AB", SFX_JDT6_AB},
	{"JDT6_AC", SFX_JDT6_AC},
	{"JDT6_AE", SFX_JDT6_AE},
	{"JDT6_AF", SFX_JDT6_AF},
	{"JDT6_AG", SFX_JDT6_AG},
	{"JDT6_AH", SFX_JDT6_AH},
	{"JDT6_BA", SFX_JDT6_BA},
	{"JDT6_BB", SFX_JDT6_BB},
	{"JDT6_BC", SFX_JDT6_BC},
	{"JDT6_BD", SFX_JDT6_BD},
	{"JDT6_BE", SFX_JDT6_BE},
	{"JDT6_BF", SFX_JDT6_BF},
	{"JDT6_BG", SFX_JDT6_BG},
	{"JDT7_AA", SFX_JDT7_AA},
	{"JDT7_AB", SFX_JDT7_AB},
	{"JDT7_AC", SFX_JDT7_AC},
	{"JDT7_AD", SFX_JDT7_AD},
	{"JDT7_AE", SFX_JDT7_AE},
	{"JDT7_AF", SFX_JDT7_AF},
	{"JDT7_AG", SFX_JDT7_AG},
	{"JDT7_BA", SFX_JDT7_BA},
	{"JDT7_BB", SFX_JDT7_BB},
	{"JDT7_BC", SFX_JDT7_BC},
	{"JDT7_CA", SFX_JDT7_CA},
	{"JDT7_CB", SFX_JDT7_CB},
	{"JDT7_CC", SFX_JDT7_CC},
	{"JDT8_AA", SFX_JDT8_AA},
	{"JDT8_AB", SFX_JDT8_AB},
	{"JDT8_AC", SFX_JDT8_AC},
	{"JDT8_AD", SFX_JDT8_AD},
	{"JDT8_AE", SFX_JDT8_AE},
	{"JDT8_AF", SFX_JDT8_AF},
	{"JDT8_AG", SFX_JDT8_AG},
	{"JDT8_AH", SFX_JDT8_AH},
	{"JDT8_CA", SFX_JDT8_CA},
	{"JDT8_CB", SFX_JDT8_CB},
	{"JDT8_DA", SFX_JDT8_DA},
	{"JDT8_DB", SFX_JDT8_DB},
	{"JDT8_DC", SFX_JDT8_DC},
	{"JDT8_DD", SFX_JDT8_DD},
	{"JDT8_DE", SFX_JDT8_DE},
	{"JDT8_DF", SFX_JDT8_DF},
	{"JDT8_DG", SFX_JDT8_DG},
	{"JDT8_EA", SFX_JDT8_EA},
	{"JDT8_EB", SFX_JDT8_EB},
	{"JDT8_EC", SFX_JDT8_EC},
	{"JDT8_ED", SFX_JDT8_ED},
	{"JDT8_EE", SFX_JDT8_EE},
	{"JDT8_FA", SFX_JDT8_FA},
	{"JDT8_FB", SFX_JDT8_FB},
	{"JDT8_FC", SFX_JDT8_FC},
	{"JDX_AA", SFX_JDX_AA},
	{"JDX_AB", SFX_JDX_AB},
	{"JDX_AC", SFX_JDX_AC},
	{"M8B1AA", SFX_M8B1AA},
	{"M8B1AB", SFX_M8B1AB},
	{"MAC1_AA", SFX_MAC1_AA},
	{"MAC1_AB", SFX_MAC1_AB},
	{"MAC1_AC", SFX_MAC1_AC},
	{"MAC1_AD", SFX_MAC1_AD},
	{"MAC1_AE", SFX_MAC1_AE},
	{"MAC1_AF", SFX_MAC1_AF},
	{"MAC1_AG", SFX_MAC1_AG},
	{"MAC1_AH", SFX_MAC1_AH},
	{"MAC1_AI", SFX_MAC1_AI},
	{"MAC1_AJ", SFX_MAC1_AJ},
	{"MAC1_AK", SFX_MAC1_AK},
	{"MAC1_AL", SFX_MAC1_AL},
	{"MAC1_AM", SFX_MAC1_AM},
	{"MAC1_AN", SFX_MAC1_AN},
	{"MAC1_AO", SFX_MAC1_AO},
	{"MAC1_BA", SFX_MAC1_BA},
	{"MAC1_BB", SFX_MAC1_BB},
	{"MAC1_BC", SFX_MAC1_BC},
	{"MAC1_BD", SFX_MAC1_BD},
	{"MAC1_BE", SFX_MAC1_BE},
	{"MAC1_BF", SFX_MAC1_BF},
	{"MAC1_BG", SFX_MAC1_BG},
	{"MAC1_CA", SFX_MAC1_CA},
	{"MAC1_CB", SFX_MAC1_CB},
	{"MAC1_DA", SFX_MAC1_DA},
	{"MAC1_EA", SFX_MAC1_EA},
	{"MAC1_FA", SFX_MAC1_FA},
	{"MAC1_FB", SFX_MAC1_FB},
	{"MAC1_GA", SFX_MAC1_GA},
	{"MAC1_GB", SFX_MAC1_GB},
	{"MAC1_HA", SFX_MAC1_HA},
	{"MAC1_IA", SFX_MAC1_IA},
	{"MAC1_IB", SFX_MAC1_IB},
	{"MAC1_JA", SFX_MAC1_JA},
	{"MAC1_JB", SFX_MAC1_JB},
	{"MAC2_AA", SFX_MAC2_AA},
	{"MAC2_AB", SFX_MAC2_AB},
	{"MAC2_AC", SFX_MAC2_AC},
	{"MAC2_AD", SFX_MAC2_AD},
	{"MAC2_AE", SFX_MAC2_AE},
	{"MAC2_AF", SFX_MAC2_AF},
	{"MAC2_AG", SFX_MAC2_AG},
	{"MAC2_AH", SFX_MAC2_AH},
	{"MAC2_AI", SFX_MAC2_AI},
	{"MAC2_BA", SFX_MAC2_BA},
	{"MAC2_BB", SFX_MAC2_BB},
	{"MAC2_BC", SFX_MAC2_BC},
	{"MAC3_AA", SFX_MAC3_AA},
	{"MAC3_AB", SFX_MAC3_AB},
	{"MAC3_AC", SFX_MAC3_AC},
	{"MAC3_AD", SFX_MAC3_AD},
	{"MAC3_AE", SFX_MAC3_AE},
	{"MAC3_AF", SFX_MAC3_AF},
	{"MAC3_AG", SFX_MAC3_AG},
	{"MAC3_AH", SFX_MAC3_AH},
	{"MAC3_AI", SFX_MAC3_AI},
	{"MAC3_AJ", SFX_MAC3_AJ},
	{"MAC3_AK", SFX_MAC3_AK},
	{"MAC3_AL", SFX_MAC3_AL},
	{"MAC3_AM", SFX_MAC3_AM},
	{"MAC3_AN", SFX_MAC3_AN},
	{"MAC3_BA", SFX_MAC3_BA},
	{"MAC4_AA", SFX_MAC4_AA},
	{"MAC4_AB", SFX_MAC4_AB},
	{"MAC4_AC", SFX_MAC4_AC},
	{"MAC4_AD", SFX_MAC4_AD},
	{"MAC4_AE", SFX_MAC4_AE},
	{"MAC4_AF", SFX_MAC4_AF},
	{"MAC4_AG", SFX_MAC4_AG},
	{"MAC4_AH", SFX_MAC4_AH},
	{"MAC4_AI", SFX_MAC4_AI},
	{"MAC4_AJ", SFX_MAC4_AJ},
	{"MAC4_AK", SFX_MAC4_AK},
	{"MAC4_AL", SFX_MAC4_AL},
	{"MAC4_BA", SFX_MAC4_BA},
	{"MAC4_BB", SFX_MAC4_BB},
	{"MAC4_BC", SFX_MAC4_BC},
	{"MAC4_BD", SFX_MAC4_BD},
	{"MAC4_BE", SFX_MAC4_BE},
	{"MAC4_BF", SFX_MAC4_BF},
	{"MAC4_BG", SFX_MAC4_BG},
	{"MAC4_BI", SFX_MAC4_BI},
	{"MAC4_BJ", SFX_MAC4_BJ},
	{"MAC4_BL", SFX_MAC4_BL},
	{"MAC4_BM", SFX_MAC4_BM},
	{"MAC4_BO", SFX_MAC4_BO},
	{"MAC4_BP", SFX_MAC4_BP},
	{"MAC4_BQ", SFX_MAC4_BQ},
	{"MAC4_BR", SFX_MAC4_BR},
	{"MAC4_BS", SFX_MAC4_BS},
	{"MAC4_BT", SFX_MAC4_BT},
	{"MAC4_BU", SFX_MAC4_BU},
	{"MAC4_CA", SFX_MAC4_CA},
	{"MAC4_CB", SFX_MAC4_CB},
	{"MAC4_CC", SFX_MAC4_CC},
	{"MAC4_CD", SFX_MAC4_CD},
	{"MAC4_CE", SFX_MAC4_CE},
	{"MAC4_CF", SFX_MAC4_CF},
	{"MAC4_CG", SFX_MAC4_CG},
	{"MAC4_CH", SFX_MAC4_CH},
	{"MAC4_CI", SFX_MAC4_CI},
	{"MAC4_CK", SFX_MAC4_CK},
	{"MAC4_CM", SFX_MAC4_CM},
	{"MAC5_AA", SFX_MAC5_AA},
	{"MAC5_AB", SFX_MAC5_AB},
	{"MAC5_AC", SFX_MAC5_AC},
	{"MAC5_AD", SFX_MAC5_AD},
	{"MAC5_AE", SFX_MAC5_AE},
	{"MAC5_AF", SFX_MAC5_AF},
	{"MAC5_AG", SFX_MAC5_AG},
	{"MAC5_AH", SFX_MAC5_AH},
	{"MAC5_AI", SFX_MAC5_AI},
	{"MAC5_AJ", SFX_MAC5_AJ},
	{"MAC5_AK", SFX_MAC5_AK},
	{"MAC5_AL", SFX_MAC5_AL},
	{"MAC5_AM", SFX_MAC5_AM},
	{"MAC5_AN", SFX_MAC5_AN},
	{"MAR1_AA", SFX_MAR1_AA},
	{"MAR1_AB", SFX_MAR1_AB},
	{"MAR1_AC", SFX_MAR1_AC},
	{"MAR1_AD", SFX_MAR1_AD},
	{"MAR1_AE", SFX_MAR1_AE},
	{"MAR1_BA", SFX_MAR1_BA},
	{"MAR1_CA", SFX_MAR1_CA},
	{"MAR1_DA", SFX_MAR1_DA},
	{"MAR1_DB", SFX_MAR1_DB},
	{"MAR1_EA", SFX_MAR1_EA},
	{"MAR1_FA", SFX_MAR1_FA},
	{"MAR1_FB", SFX_MAR1_FB},
	{"MAR1_FC", SFX_MAR1_FC},
	{"MAR1_FD", SFX_MAR1_FD},
	{"MAR1_GA", SFX_MAR1_GA},
	{"MAR1_GB", SFX_MAR1_GB},
	{"MAR1_GC", SFX_MAR1_GC},
	{"MAR1_HA", SFX_MAR1_HA},
	{"MAR1_HB", SFX_MAR1_HB},
	{"MAR1_HC", SFX_MAR1_HC},
	{"MAR1_IA", SFX_MAR1_IA},
	{"MAR1_IB", SFX_MAR1_IB},
	{"MAR1_IC", SFX_MAR1_IC},
	{"MAR2_AA", SFX_MAR2_AA},
	{"MAR2_AB", SFX_MAR2_AB},
	{"MAR2_AC", SFX_MAR2_AC},
	{"MAR2_AD", SFX_MAR2_AD},
	{"MAR2_AE", SFX_MAR2_AE},
	{"MAR2_AF", SFX_MAR2_AF},
	{"MAR2_AG", SFX_MAR2_AG},
	{"MAR2_AH", SFX_MAR2_AH},
	{"MAR2_BA", SFX_MAR2_BA},
	{"MAR2_BB", SFX_MAR2_BB},
	{"MAR2_BC", SFX_MAR2_BC},
	{"MAR2_CA", SFX_MAR2_CA},
	{"MAR2_CB", SFX_MAR2_CB},
	{"MAR2_CC", SFX_MAR2_CC},
	{"MAR2_CD", SFX_MAR2_CD},
	{"MAR2_CE", SFX_MAR2_CE},
	{"MAR2_DA", SFX_MAR2_DA},
	{"MAR2_EA", SFX_MAR2_EA},
	{"MAR2_EB", SFX_MAR2_EB},
	{"MAR2_EC", SFX_MAR2_EC},
	{"MAR2_FA", SFX_MAR2_FA},
	{"MAR2_FB", SFX_MAR2_FB},
	{"MAR2_GA", SFX_MAR2_GA},
	{"MAR2_GB", SFX_MAR2_GB},
	{"MAR2_GC", SFX_MAR2_GC},
	{"MAR2_GE", SFX_MAR2_GE},
	{"MAR2_GG", SFX_MAR2_GG},
	{"MAR2_GH", SFX_MAR2_GH},
	{"MAR2_HA", SFX_MAR2_HA},
	{"MAR2_HB", SFX_MAR2_HB},
	{"MAR2_HC", SFX_MAR2_HC},
	{"MAR3_AA", SFX_MAR3_AA},
	{"MAR3_AB", SFX_MAR3_AB},
	{"MAR3_AC", SFX_MAR3_AC},
	{"MAR3_AD", SFX_MAR3_AD},
	{"MAR3_BA", SFX_MAR3_BA},
	{"MAR3_BB", SFX_MAR3_BB},
	{"MAR3_BC", SFX_MAR3_BC},
	{"MAR3_BD", SFX_MAR3_BD},
	{"MAR3_BE", SFX_MAR3_BE},
	{"MAR3_BF", SFX_MAR3_BF},
	{"MAR4_BA", SFX_MAR4_BA},
	{"MAR4_BC", SFX_MAR4_BC},
	{"MAR4_BD", SFX_MAR4_BD},
	{"MAR4_BF", SFX_MAR4_BF},
	{"MAR5_AA", SFX_MAR5_AA},
	{"MAR5_AB", SFX_MAR5_AB},
	{"MAR5_AC", SFX_MAR5_AC},
	{"MAR5_AD", SFX_MAR5_AD},
	{"MAR5_AE", SFX_MAR5_AE},
	{"MAR5_BA", SFX_MAR5_BA},
	{"MAR5_BB", SFX_MAR5_BB},
	{"MAR5_CA", SFX_MAR5_CA},
	{"MAR5_CB", SFX_MAR5_CB},
	{"MAR5_CC", SFX_MAR5_CC},
	{"MAR5_CD", SFX_MAR5_CD},
	{"MAR5_CE", SFX_MAR5_CE},
	{"MAR5_EA", SFX_MAR5_EA},
	{"MAR5_EB", SFX_MAR5_EB},
	{"MAR5_EC", SFX_MAR5_EC},
	{"MAR5_FA", SFX_MAR5_FA},
	{"MAR5_FB", SFX_MAR5_FB},
	{"MAR5_FC", SFX_MAR5_FC},
	{"MAR5_FD", SFX_MAR5_FD},
	{"MAR5_FE", SFX_MAR5_FE},
	{"MAR5_FF", SFX_MAR5_FF},
	{"MARX_AA", SFX_MARX_AA},
	{"MARX_AB", SFX_MARX_AB},
	{"MARX_AC", SFX_MARX_AC},
	{"MDON1AA", SFX_MDON1AA},
	{"MDON1AB", SFX_MDON1AB},
	{"MDON1AC", SFX_MDON1AC},
	{"MDON2AA", SFX_MDON2AA},
	{"MDON2AB", SFX_MDON2AB},
	{"MDON2AC", SFX_MDON2AC},
	{"MDON2AD", SFX_MDON2AD},
	{"MDON2AE", SFX_MDON2AE},
	{"MDON2AF", SFX_MDON2AF},
	{"MDON2AG", SFX_MDON2AG},
	{"MDON3AA", SFX_MDON3AA},
	{"MDON3AB", SFX_MDON3AB},
	{"MDON3AC", SFX_MDON3AC},
	{"MDON3AD", SFX_MDON3AD},
	{"MDON3AE", SFX_MDON3AE},
	{"MDON3AF", SFX_MDON3AF},
	{"MDON3AG", SFX_MDON3AG},
	{"MJDT1AA", SFX_MJDT1AA},
	{"MJDT1AB", SFX_MJDT1AB},
	{"MJDT1AC", SFX_MJDT1AC},
	{"MJDT1AE", SFX_MJDT1AE},
	{"MMA1AA", SFX_MMA1AA},
	{"MMA1AB", SFX_MMA1AB},
	{"MMA1AC", SFX_MMA1AC},
	{"MMA1AD", SFX_MMA1AD},
	{"MMA1AE", SFX_MMA1AE},
	{"MMA2AA", SFX_MMA2AA},
	{"MMA2AB", SFX_MMA2AB},
	{"MMA2AC", SFX_MMA2AC},
	{"MMA2AD", SFX_MMA2AD},
	{"MMA2AE", SFX_MMA2AE},
	{"MMA2AF", SFX_MMA2AF},
	{"MMA2AG", SFX_MMA2AG},
	{"MMA2AH", SFX_MMA2AH},
	{"MMA2AI", SFX_MMA2AI},
	{"MMA2AJ", SFX_MMA2AJ},
	{"MMAR1AA", SFX_MMAR1AA},
	{"MMAR1AB", SFX_MMAR1AB},
	{"MMAR1AC", SFX_MMAR1AC},
	{"MMAR1AD", SFX_MMAR1AD},
	{"MMCA1AA", SFX_MMCA1AA},
	{"MMCA1AB", SFX_MMCA1AB},
	{"MMCA1AC", SFX_MMCA1AC},
	{"MMCA1AD", SFX_MMCA1AD},
	{"MMCA2AA", SFX_MMCA2AA},
	{"MMCA2AB", SFX_MMCA2AB},
	{"MMCA2AC", SFX_MMCA2AC},
	{"MMCA2AD", SFX_MMCA2AD},
	{"MMCA2AE", SFX_MMCA2AE},
	{"MMCA2AF", SFX_MMCA2AF},
	{"MSA10AA", SFX_MSA10AA},
	{"MSA10AB", SFX_MSA10AB},
	{"MSA10AC", SFX_MSA10AC},
	{"MSA10AD", SFX_MSA10AD},
	{"MSA11AA", SFX_MSA11AA},
	{"MSA11AB", SFX_MSA11AB},
	{"MSA11AC", SFX_MSA11AC},
	{"MSA11AD", SFX_MSA11AD},
	{"MSA12AA", SFX_MSA12AA},
	{"MSA12AC", SFX_MSA12AC},
	{"MSA12AD", SFX_MSA12AD},
	{"MSA13AA", SFX_MSA13AA},
	{"MSA13AB", SFX_MSA13AB},
	{"MSA13AC", SFX_MSA13AC},
	{"MSA13AD", SFX_MSA13AD},
	{"MSA13AE", SFX_MSA13AE},
	{"MSA13AF", SFX_MSA13AF},
	{"MSA13AG", SFX_MSA13AG},
	{"MSA13AH", SFX_MSA13AH},
	{"MSA14AA", SFX_MSA14AA},
	{"MSA14AB", SFX_MSA14AB},
	{"MSA14AC", SFX_MSA14AC},
	{"MSA14AD", SFX_MSA14AD},
	{"MSAL5AA", SFX_MSAL5AA},
	{"MSAL5AB", SFX_MSAL5AB},
	{"MSAL6AA", SFX_MSAL6AA},
	{"MSAL6AB", SFX_MSAL6AB},
	{"MSAL6AC", SFX_MSAL6AC},
	{"MSAL6AD", SFX_MSAL6AD},
	{"MSAL7AA", SFX_MSAL7AA},
	{"MSAL7AB", SFX_MSAL7AB},
	{"MSAL7AC", SFX_MSAL7AC},
	{"MSAL7AD", SFX_MSAL7AD},
	{"MSAL7AE", SFX_MSAL7AE},
	{"MSAL7AF", SFX_MSAL7AF},
	{"MSAL7AG", SFX_MSAL7AG},
	{"MSAL8AA", SFX_MSAL8AA},
	{"MSAL8AB", SFX_MSAL8AB},
	{"MSAL8AC", SFX_MSAL8AC},
	{"MSAL8AD", SFX_MSAL8AD},
	{"MSAL8AF", SFX_MSAL8AF},
	{"MSAL8AG", SFX_MSAL8AG},
	{"MSAL9AA", SFX_MSAL9AA},
	{"MSAL9AB", SFX_MSAL9AB},
	{"MSAL9AC", SFX_MSAL9AC},
	{"MSAL9AD", SFX_MSAL9AD},
	{"MSAL9AE", SFX_MSAL9AE},
	{"MSAL9AF", SFX_MSAL9AF},
	{"MTOS1AA", SFX_MTOS1AA},
	{"MTOS1AB", SFX_MTOS1AB},
	{"MTOS1AC", SFX_MTOS1AC},
	{"MTOS1AD", SFX_MTOS1AD},
	{"MTOS1AE", SFX_MTOS1AE},
	{"MTOS1AF", SFX_MTOS1AF},
	{"MTOS1AG", SFX_MTOS1AG},
	{"MTOS2AA", SFX_MTOS2AA},
	{"MTOS2AB", SFX_MTOS2AB},
	{"MTOS2AC", SFX_MTOS2AC},
	{"MTOS2AD", SFX_MTOS2AD},
	{"MTOS2AE", SFX_MTOS2AE},
	{"MTOS2AF", SFX_MTOS2AF},
	{"MTOS2AG", SFX_MTOS2AG},
	{"MVIC1AA", SFX_MVIC1AA},
	{"MVIC1AB", SFX_MVIC1AB},
	{"MVIC1AC", SFX_MVIC1AC},
	{"MVIC1AD", SFX_MVIC1AD},
	{"MVIC1AE", SFX_MVIC1AE},
	{"MVIC1AF", SFX_MVIC1AF},
	{"MVIC1AG", SFX_MVIC1AG},
	{"MVIC1AH", SFX_MVIC1AH},
	{"MVIC1AI", SFX_MVIC1AI},
	{"MVIC1AJ", SFX_MVIC1AJ},
	{"MVIC1AK", SFX_MVIC1AK},
	{"NEDS1AA", SFX_NEDS1AA},
	{"NEDS1AB", SFX_NEDS1AB},
	{"NEDS1AC", SFX_NEDS1AC},
	{"NEDS1AD", SFX_NEDS1AD},
	{"NEDS1AE", SFX_NEDS1AE},
	{"NEDS1AF", SFX_NEDS1AF},
	{"NEDS1AG", SFX_NEDS1AG},
	{"NEDS1BC", SFX_NEDS1BC},
	{"NEDS1BE", SFX_NEDS1BE},
	{"NEDS2AA", SFX_NEDS2AA},
	{"NEDS2AB", SFX_NEDS2AB},
	{"NEDS2AC", SFX_NEDS2AC},
	{"NEDS2AD", SFX_NEDS2AD},
	{"NEDS2AE", SFX_NEDS2AE},
	{"NEDS2AF", SFX_NEDS2AF},
	{"NEDS2BA", SFX_NEDS2BA},
	{"NEDS3AA", SFX_NEDS3AA},
	{"NEDS3AB", SFX_NEDS3AB},
	{"NEDS3AC", SFX_NEDS3AC},
	{"NEDS3AD", SFX_NEDS3AD},
	{"NEDS4AA", SFX_NEDS4AA},
	{"NEDS4AB", SFX_NEDS4AB},
	{"NEDS4AC", SFX_NEDS4AC},
	{"NEDS4AD", SFX_NEDS4AD},
	{"NEDS4AE", SFX_NEDS4AE},
	{"NEDS4BA", SFX_NEDS4BA},
	{"NEDS4BB", SFX_NEDS4BB},
	{"NEDS4BC", SFX_NEDS4BC},
	{"NEDS4BD", SFX_NEDS4BD},
	{"NEDS4BE", SFX_NEDS4BE},
	{"NEDS4BF", SFX_NEDS4BF},
	{"RAC1_AA", SFX_RAC1_AA},
	{"RAC1_AB", SFX_RAC1_AB},
	{"RAC1_AC", SFX_RAC1_AC},
	{"RAC1_AD", SFX_RAC1_AD},
	{"RAC1_AE", SFX_RAC1_AE},
	{"RAC1_AF", SFX_RAC1_AF},
	{"RAC1_AG", SFX_RAC1_AG},
	{"RAC2_AA", SFX_RAC2_AA},
	{"RAC2_AB", SFX_RAC2_AB},
	{"RAC2_AC", SFX_RAC2_AC},
	{"RAC2_AD", SFX_RAC2_AD},
	{"RAC2_AE", SFX_RAC2_AE},
	{"RAC2_AF", SFX_RAC2_AF},
	{"RAC3_AB", SFX_RAC3_AB},
	{"RAC3_AC", SFX_RAC3_AC},
	{"RAC3_AD", SFX_RAC3_AD},
	{"RAC3_AE", SFX_RAC3_AE},
	{"RAC3_AF", SFX_RAC3_AF},
	{"RAC3_AG", SFX_RAC3_AG},
	{"RAYS1AA", SFX_RAYS1AA},
	{"RAYS1AB", SFX_RAYS1AB},
	{"RAYS1AC", SFX_RAYS1AC},
	{"RAYS1BA", SFX_RAYS1BA},
	{"RAYS1BB", SFX_RAYS1BB},
	{"RAYS1CA", SFX_RAYS1CA},
	{"RAYS1CB", SFX_RAYS1CB},
	{"RAYS1CC", SFX_RAYS1CC},
	{"RAYS1CD", SFX_RAYS1CD},
	{"RAYS1CE", SFX_RAYS1CE},
	{"RAYS1CF", SFX_RAYS1CF},
	{"RAYS1DA", SFX_RAYS1DA},
	{"RAYS1DB", SFX_RAYS1DB},
	{"RAYS1DC", SFX_RAYS1DC},
	{"RAYS2AA", SFX_RAYS2AA},
	{"RAYS2AB", SFX_RAYS2AB},
	{"RAYS2AD", SFX_RAYS2AD},
	{"RAYS2AE", SFX_RAYS2AE},
	{"RAYS2AF", SFX_RAYS2AF},
	{"RAYS2AG", SFX_RAYS2AG},
	{"RAYS2AH", SFX_RAYS2AH},
	{"RAYS2AI", SFX_RAYS2AI},
	{"RAYS2CA", SFX_RAYS2CA},
	{"RAYS2DA", SFX_RAYS2DA},
	{"RAYS4AA", SFX_RAYS4AA},
	{"RAYS4AB", SFX_RAYS4AB},
	{"RAYS4AC", SFX_RAYS4AC},
	{"RAYS4AD", SFX_RAYS4AD},
	{"RAYS4AE", SFX_RAYS4AE},
	{"RAYS4AF", SFX_RAYS4AF},
	{"RAYS5AA", SFX_RAYS5AA},
	{"RAYS5AB", SFX_RAYS5AB},
	{"RAYS5AC", SFX_RAYS5AC},
	{"RAYS5AD", SFX_RAYS5AD},
	{"RAYS5AE", SFX_RAYS5AE},
	{"RAYS5AF", SFX_RAYS5AF},
	{"RAYS5AG", SFX_RAYS5AG},
	{"RAYS5AH", SFX_RAYS5AH},
	{"RAYS5AI", SFX_RAYS5AI},
	{"SAL1_AA", SFX_SAL1_AA},
	{"SAL1_AB", SFX_SAL1_AB},
	{"SAL1_AC", SFX_SAL1_AC},
	{"SAL1_AE", SFX_SAL1_AE},
	{"SAL2_AA", SFX_SAL2_AA},
	{"SAL2_AB", SFX_SAL2_AB},
	{"SAL2_AC", SFX_SAL2_AC},
	{"SAL2_AD", SFX_SAL2_AD},
	{"SAL2_AF", SFX_SAL2_AF},
	{"SAL2_AG", SFX_SAL2_AG},
	{"SAL2_CK", SFX_SAL2_CK},
	{"SAL2_DA", SFX_SAL2_DA},
	{"SAL2_DB", SFX_SAL2_DB},
	{"SAL2_DC", SFX_SAL2_DC},
	{"SAL2_EA", SFX_SAL2_EA},
	{"SAL3_AA", SFX_SAL3_AA},
	{"SAL3_AD", SFX_SAL3_AD},
	{"SAL3_AE", SFX_SAL3_AE},
	{"SAL3_AF", SFX_SAL3_AF},
	{"SAL3_AG", SFX_SAL3_AG},
	{"SAL3_AI", SFX_SAL3_AI},
	{"SAL3_BB", SFX_SAL3_BB},
	{"SAL3_CB", SFX_SAL3_CB},
	{"SALH4AB", SFX_SALH4AB},
	{"SALH4AC", SFX_SALH4AC},
	{"SALH4AE", SFX_SALH4AE},
	{"SALH4AF", SFX_SALH4AF},
	{"SALH4AH", SFX_SALH4AH},
	{"SALH4AI", SFX_SALH4AI},
	{"SALH4AJ", SFX_SALH4AJ},
	{"SAL4_AA", SFX_SAL4_AA},
	{"SAL4_AB", SFX_SAL4_AB},
	{"SAL4_AC", SFX_SAL4_AC},
	{"SAL4_AD", SFX_SAL4_AD},
	{"SAL4_AE", SFX_SAL4_AE},
	{"SAL4_AF", SFX_SAL4_AF},
	{"SAL4_AH", SFX_SAL4_AH},
	{"SAL4_AI", SFX_SAL4_AI},
	{"SAL4_BA", SFX_SAL4_BA},
	{"SAL4_CA", SFX_SAL4_CA},
	{"SAL4_CB", SFX_SAL4_CB},
	{"SAL4_CC", SFX_SAL4_CC},
	{"SAL4_CD", SFX_SAL4_CD},
	{"SAL4_CE", SFX_SAL4_CE},
	{"SAL4_CF", SFX_SAL4_CF},
	{"SAL4_CG", SFX_SAL4_CG},
	{"SAL4_CH", SFX_SAL4_CH},
	{"SAL4_CI", SFX_SAL4_CI},
	{"SAL4_CJ", SFX_SAL4_CJ},
	{"SAL4_CK", SFX_SAL4_CK},
	{"SAL4_CL", SFX_SAL4_CL},
	{"SAL4_CM", SFX_SAL4_CM},
	{"SAL4_CN", SFX_SAL4_CN},
	{"SAL4_CO", SFX_SAL4_CO},
	{"SAL4_CP", SFX_SAL4_CP},
	{"SAL4_CQ", SFX_SAL4_CQ},
	{"SAL4_DA", SFX_SAL4_DA},
	{"SAL5_AB", SFX_SAL5_AB},
	{"SAL5_AE", SFX_SAL5_AE},
	{"SAL5_AH", SFX_SAL5_AH},
	{"SAL5_AI", SFX_SAL5_AI},
	{"SAL5_AJ", SFX_SAL5_AJ},
	{"SAL6_AA", SFX_SAL6_AA},
	{"SAL6_AB", SFX_SAL6_AB},
	{"SAL6_AC", SFX_SAL6_AC},
	{"SAL6_AE", SFX_SAL6_AE},
	{"SAL6_AF", SFX_SAL6_AF},
	{"SAL6_AG", SFX_SAL6_AG},
	{"SAL6_AH", SFX_SAL6_AH},
	{"SAL6_AI", SFX_SAL6_AI},
	{"SAL6_AJ", SFX_SAL6_AJ},
	{"SAL6_BA", SFX_SAL6_BA},
	{"SAL6_BB", SFX_SAL6_BB},
	{"SAL6_BC", SFX_SAL6_BC},
	{"SAL6_BD", SFX_SAL6_BD},
	{"SAL6_BE", SFX_SAL6_BE},
	{"SAL6_BF", SFX_SAL6_BF},
	{"SAL6_BH", SFX_SAL6_BH},
	{"SAL6_BJ", SFX_SAL6_BJ},
	{"SAL6_BK", SFX_SAL6_BK},
	{"SAL7_AA", SFX_SAL7_AA},
	{"SAL7_AB", SFX_SAL7_AB},
	{"SAL7_AC", SFX_SAL7_AC},
	{"SAL7_AD", SFX_SAL7_AD},
	{"SAL7_AE", SFX_SAL7_AE},
	{"SAL7_AF", SFX_SAL7_AF},
	{"SAL7_AG", SFX_SAL7_AG},
	{"SAL7_AI", SFX_SAL7_AI},
	{"SAL7_AJ", SFX_SAL7_AJ},
	{"SAL7_AK", SFX_SAL7_AK},
	{"SAL7_BA", SFX_SAL7_BA},
	{"SAL7_BB", SFX_SAL7_BB},
	{"SAL7_BC", SFX_SAL7_BC},
	{"SAL7_BD", SFX_SAL7_BD},
	{"SAL7_BE", SFX_SAL7_BE},
	{"SAL7_BF", SFX_SAL7_BF},
	{"SAL7_BG", SFX_SAL7_BG},
	{"SAL7_BH", SFX_SAL7_BH},
	{"SAL7_CA", SFX_SAL7_CA},
	{"SAL7_CB", SFX_SAL7_CB},
	{"SAL7_CC", SFX_SAL7_CC},
	{"SAL8_AA", SFX_SAL8_AA},
	{"SAL8_AB", SFX_SAL8_AB},
	{"SAL8_AC", SFX_SAL8_AC},
	{"SAL8_BA", SFX_SAL8_BA},
	{"SAL8_BC", SFX_SAL8_BC},
	{"SAL8_BD", SFX_SAL8_BD},
	{"SAL8_BE", SFX_SAL8_BE},
	{"SAL8_BF", SFX_SAL8_BF},
	{"SAL8_CA", SFX_SAL8_CA},
	{"SAL8_CC", SFX_SAL8_CC},
	{"SAL8_DA", SFX_SAL8_DA},
	{"SAL8_DB", SFX_SAL8_DB},
	{"SAL8_DC", SFX_SAL8_DC},
	{"SAL8_EA", SFX_SAL8_EA},
	{"SAL8_EC", SFX_SAL8_EC},
	{"SAL8_ED", SFX_SAL8_ED},
	{"SAL8_EE", SFX_SAL8_EE},
	{"SAL8_FA", SFX_SAL8_FA},
	{"SAL8_GA", SFX_SAL8_GA},
	{"SAL8_GB", SFX_SAL8_GB},
	{"SALH1GB", SFX_SALH1GB},
	{"SALH1HB", SFX_SALH1HB},
	{"SALH2AA", SFX_SALH2AA},
	{"SALH2AB", SFX_SALH2AB},
	{"SALH2AC", SFX_SALH2AC},
	{"SALH2AD", SFX_SALH2AD},
	{"SALH2AE", SFX_SALH2AE},
	{"SALH2AF", SFX_SALH2AF},
	{"SALH2AG", SFX_SALH2AG},
	{"SALH2AH", SFX_SALH2AH},
	{"SALH2BA", SFX_SALH2BA},
	{"SALH2BB", SFX_SALH2BB},
	{"SALH2BC", SFX_SALH2BC},
	{"SALH2BD", SFX_SALH2BD},
	{"SALH2BH", SFX_SALH2BH},
	{"SALH2BI", SFX_SALH2BI},
	{"SALH2CA", SFX_SALH2CA},
	{"SALH3AA", SFX_SALH3AA},
	{"SALH3AB", SFX_SALH3AB},
	{"SALH3AC", SFX_SALH3AC},
	{"SALH3AD", SFX_SALH3AD},
	{"SALH3AE", SFX_SALH3AE},
	{"SALH3AF", SFX_SALH3AF},
	{"SALH3AG", SFX_SALH3AG},
	{"SALH3AH", SFX_SALH3AH},
	{"SALH3AI", SFX_SALH3AI},
	{"SALH3AJ", SFX_SALH3AJ},
	{"SALH3AK", SFX_SALH3AK},
	{"SALH3BA", SFX_SALH3BA},
	{"SALH3BB", SFX_SALH3BB},
	{"SALH3CA", SFX_SALH3CA},
	{"SALH3CC", SFX_SALH3CC},
	{"SALH3CD", SFX_SALH3CD},
	{"SALH4AA", SFX_SALH4AA},
	{"SALH4AD", SFX_SALH4AD},
	{"SALH4AG", SFX_SALH4AG},
	{"SALH4BA", SFX_SALH4BA},
	{"SALH4BB", SFX_SALH4BB},
	{"SALH4BC", SFX_SALH4BC},
	{"SALH4CA", SFX_SALH4CA},
	{"SALH5CA", SFX_SALH5CA},
	{"SALH5CB", SFX_SALH5CB},
	{"SALH5CC", SFX_SALH5CC},
	{"SALH5DA", SFX_SALH5DA},
	{"SALH5DB", SFX_SALH5DB},
	{"SALH5EA", SFX_SALH5EA},
	{"SALH5EB", SFX_SALH5EB},
	{"SALH5FA", SFX_SALH5FA},
	{"SALH5GA", SFX_SALH5GA},
	{"SALH5GB", SFX_SALH5GB},
	{"SALH5GC", SFX_SALH5GC},
	{"SALH5HA", SFX_SALH5HA},
	{"SALH5IA", SFX_SALH5IA},
	{"SALH5IB", SFX_SALH5IB},
	{"SALH5JA", SFX_SALH5JA},
	{"SALH5KA", SFX_SALH5KA},
	{"SALH5KB", SFX_SALH5KB},
	{"SALH5LA", SFX_SALH5LA},
	{"SALH5LB", SFX_SALH5LB},
	{"SALH5MA", SFX_SALH5MA},
	{"SALH5MB", SFX_SALH5MB},
	{"SALH5MC", SFX_SALH5MC},
	{"SALH5NA", SFX_SALH5NA},
	{"SALH5OA", SFX_SALH5OA},
	{"SALH5OB", SFX_SALH5OB},
	{"SALH5OC", SFX_SALH5OC},
	{"SALH5OD", SFX_SALH5OD},
	{"SALH5OE", SFX_SALH5OE},
	{"SALH5OF", SFX_SALH5OF},
	{"SALH5OG", SFX_SALH5OG},
	{"SALH5OH", SFX_SALH5OH},
	{"SALH5OI", SFX_SALH5OI},
	{"SALH5OJ", SFX_SALH5OJ},
	{"SALH5OK", SFX_SALH5OK},
	{"SALS1AA", SFX_SALS1AA},
	{"SALS1AB", SFX_SALS1AB},
	{"SALS1AC", SFX_SALS1AC},
	{"SALS1AD", SFX_SALS1AD},
	{"SALS1AE", SFX_SALS1AE},
	{"SALS1AF", SFX_SALS1AF},
	{"SALS1AG", SFX_SALS1AG},
	{"SALS1AH", SFX_SALS1AH},
	{"SALS1AI", SFX_SALS1AI},
	{"SALS2AA", SFX_SALS2AA},
	{"SALS2AB", SFX_SALS2AB},
	{"SALS2AC", SFX_SALS2AC},
	{"SALS2AD", SFX_SALS2AD},
	{"SALS2BC", SFX_SALS2BC},
	{"SALS2BD", SFX_SALS2BD},
	{"SALS2BE", SFX_SALS2BE},
	{"SALS2BF", SFX_SALS2BF},
	{"SALS2CD", SFX_SALS2CD},
	{"SALS3AA", SFX_SALS3AA},
	{"SALS3AB", SFX_SALS3AB},
	{"SALS3AC", SFX_SALS3AC},
	{"SALS3BB", SFX_SALS3BB},
	{"SALS3BD", SFX_SALS3BD},
	{"SALS3CA", SFX_SALS3CA},
	{"SALS3CB", SFX_SALS3CB},
	{"SALS3CC", SFX_SALS3CC},
	{"SALS3CD", SFX_SALS3CD},
	{"SALS3CE", SFX_SALS3CE},
	{"SALS3CF", SFX_SALS3CF},
	{"SALS3CG", SFX_SALS3CG},
	{"SALS3DA", SFX_SALS3DA},
	{"SALS3DE", SFX_SALS3DE},
	{"SALS3DH", SFX_SALS3DH},
	{"SALS3DI", SFX_SALS3DI},
	{"SALS4AA", SFX_SALS4AA},
	{"SALS4AB", SFX_SALS4AB},
	{"SALS4AC", SFX_SALS4AC},
	{"SALS4AD", SFX_SALS4AD},
	{"SALS4AE", SFX_SALS4AE},
	{"SALS4AF", SFX_SALS4AF},
	{"SALS4BA", SFX_SALS4BA},
	{"SALS4BB", SFX_SALS4BB},
	{"SALS4BC", SFX_SALS4BC},
	{"SALS4BD", SFX_SALS4BD},
	{"SALS4BE", SFX_SALS4BE},
	{"SALS4BF", SFX_SALS4BF},
	{"SALS4BG", SFX_SALS4BG},
	{"SALS4BH", SFX_SALS4BH},
	{"SALS5AA", SFX_SALS5AA},
	{"SALS5AB", SFX_SALS5AB},
	{"SALS5AC", SFX_SALS5AC},
	{"SALS5AD", SFX_SALS5AD},
	{"SALS5AE", SFX_SALS5AE},
	{"SALS5AF", SFX_SALS5AF},
	{"SALS5BA", SFX_SALS5BA},
	{"SALS5BB", SFX_SALS5BB},
	{"SALS5BC", SFX_SALS5BC},
	{"SALS5BD", SFX_SALS5BD},
	{"SALS5BE", SFX_SALS5BE},
	{"SALS5BF", SFX_SALS5BF},
	{"SALS5BG", SFX_SALS5BG},
	{"SALS5CA", SFX_SALS5CA},
	{"SALS5CB", SFX_SALS5CB},
	{"SALS5CC", SFX_SALS5CC},
	{"SALS5CD", SFX_SALS5CD},
	{"SALS5CE", SFX_SALS5CE},
	{"SALS5CF", SFX_SALS5CF},
	{"SALS5CG", SFX_SALS5CG},
	{"SALS6AA", SFX_SALS6AA},
	{"SALS6AB", SFX_SALS6AB},
	{"SALS6AD", SFX_SALS6AD},
	{"SALS6AE", SFX_SALS6AE},
	{"SALS6AF", SFX_SALS6AF},
	{"SALS6AG", SFX_SALS6AG},
	{"SALS6AH", SFX_SALS6AH},
	{"SALX_AA", SFX_SALX_AA},
	{"SALX_AB", SFX_SALX_AB},
	{"SALX_AC", SFX_SALX_AC},
	{"SALX_AD", SFX_SALX_AD},
	{"SALX_AE", SFX_SALX_AE},
	{"SALX_AF", SFX_SALX_AF},
	{"SALX_AG", SFX_SALX_AG},
	{"SALX_AH", SFX_SALX_AH},
	{"SALX_AI", SFX_SALX_AI},
	{"SALX_AK", SFX_SALX_AK},
	{"SALX_AL", SFX_SALX_AL},
	{"SALX_AM", SFX_SALX_AM},
	{"SALX_AN", SFX_SALX_AN},
	{"SALX_AO", SFX_SALX_AO},
	{"SALX_AP", SFX_SALX_AP},
	{"SALX_AQ", SFX_SALX_AQ},
	{"SALX_AR", SFX_SALX_AR},
	{"SALX_AS", SFX_SALX_AS},
	{"TAN1_AA", SFX_TAN1_AA},
	{"TAN1_AB", SFX_TAN1_AB},
	{"TAN1_AD", SFX_TAN1_AD},
	{"TAN1_AE", SFX_TAN1_AE},
	{"TAN1_AF", SFX_TAN1_AF},
	{"TAN1_AG", SFX_TAN1_AG},
	{"TAN1_AH", SFX_TAN1_AH},
	{"TAN1_AI", SFX_TAN1_AI},
	{"TAN1_AJ", SFX_TAN1_AJ},
	{"TAN2_AA", SFX_TAN2_AA},
	{"TAN2_AB", SFX_TAN2_AB},
	{"TAN2_AC", SFX_TAN2_AC},
	{"TAN2_AE", SFX_TAN2_AE},
	{"TAN2_AF", SFX_TAN2_AF},
	{"TAN2_AG", SFX_TAN2_AG},
	{"TAN2_AH", SFX_TAN2_AH},
	{"TAN2_AJ", SFX_TAN2_AJ},
	{"TAN3_AA", SFX_TAN3_AA},
	{"TAN3_AB", SFX_TAN3_AB},
	{"TAN3_AC", SFX_TAN3_AC},
	{"TAN3_AD", SFX_TAN3_AD},
	{"TAN3_AE", SFX_TAN3_AE},
	{"TAN3_AF", SFX_TAN3_AF},
	{"TAN3_AG", SFX_TAN3_AG},
	{"TAN3_AH", SFX_TAN3_AH},
	{"TOSH1AA", SFX_TOSH1AA},
	{"TOSH1AB", SFX_TOSH1AB},
	{"TOSH1AC", SFX_TOSH1AC},
	{"TOSH1AD", SFX_TOSH1AD},
	{"TOSH2AA", SFX_TOSH2AA},
	{"TOSH2AB", SFX_TOSH2AB},
	{"TOSH2AC", SFX_TOSH2AC},
	{"TOSH2AE", SFX_TOSH2AE},
	{"TOSH2AF", SFX_TOSH2AF},
	{"TOSH2AG", SFX_TOSH2AG},
	{"TOSH2AH", SFX_TOSH2AH},
	{"TOSH2AI", SFX_TOSH2AI},
	{"TOSH2AJ", SFX_TOSH2AJ},
	{"TOSH2AK", SFX_TOSH2AK},
	{"TOSH2AL", SFX_TOSH2AL},
	{"TOSH2AM", SFX_TOSH2AM},
	{"TOSH3AA", SFX_TOSH3AA},
	{"TOSH3AB", SFX_TOSH3AB},
	{"TOSH3AC", SFX_TOSH3AC},
	{"TOSH3AD", SFX_TOSH3AD},
	{"TOSH3AE", SFX_TOSH3AE},
	{"TOSH3AF", SFX_TOSH3AF},
	{"TOSH3AG", SFX_TOSH3AG},
	{"TOSH3AH", SFX_TOSH3AH},
	{"TOSH3AI", SFX_TOSH3AI},
	{"TOSH3AJ", SFX_TOSH3AJ},
	{"TOSH3AK", SFX_TOSH3AK},
	{"TOSH3BA", SFX_TOSH3BA},
	{"TOSH3BB", SFX_TOSH3BB},
	{"TOSH3CA", SFX_TOSH3CA},
	{"TOSH3CB", SFX_TOSH3CB},
	{"TOSH3CC", SFX_TOSH3CC},
	{"TOSH3CD", SFX_TOSH3CD},
	{"TOSH3CE", SFX_TOSH3CE},
	{"TOSH3CF", SFX_TOSH3CF},
	{"TOSH3CG", SFX_TOSH3CG},
	{"TOSH3CH", SFX_TOSH3CH},
	{"TOSH3CI", SFX_TOSH3CI},
	{"TOSH3CJ", SFX_TOSH3CJ},
	{"TOSH3CK", SFX_TOSH3CK},
	{"TOSH3DA", SFX_TOSH3DA},
	{"TOSH3EA", SFX_TOSH3EA},
	{"TOSH3FA", SFX_TOSH3FA},
	{"TOSH3FB", SFX_TOSH3FB},
	{"TOSH3FC", SFX_TOSH3FC},
	{"TOSH3FD", SFX_TOSH3FD},
	{"TOSH3FE", SFX_TOSH3FE},
	{"TOSH3FF", SFX_TOSH3FF},
	{"TOSH3GA", SFX_TOSH3GA},
	{"TOSH3GB", SFX_TOSH3GB},
	{"TOSH3HA", SFX_TOSH3HA},
	{"TOSH4AA", SFX_TOSH4AA},
	{"TOSH4AB", SFX_TOSH4AB},
	{"TOSH4AC", SFX_TOSH4AC},
	{"TOSH4AD", SFX_TOSH4AD},
	{"TOSH4AE", SFX_TOSH4AE},
	{"TOSH4AF", SFX_TOSH4AF},
	{"TOSH4AG", SFX_TOSH4AG},
	{"TOSH4AH", SFX_TOSH4AH},
	{"TOSH4AI", SFX_TOSH4AI},
	{"TOSH4AJ", SFX_TOSH4AJ},
	{"TOSH4BA", SFX_TOSH4BA},
	{"TOSH4BB", SFX_TOSH4BB},
	{"TOSH4BC", SFX_TOSH4BC},
	{"TOSH4CA", SFX_TOSH4CA},
	{"TOSH4CB", SFX_TOSH4CB},
	{"TOSH4CC", SFX_TOSH4CC},
	{"TOSH4CD", SFX_TOSH4CD},
	{"TOSH4CE", SFX_TOSH4CE},
	{"TOSH4DA", SFX_TOSH4DA},
	{"TOSH4DB", SFX_TOSH4DB},
	{"TOSH4DC", SFX_TOSH4DC},
	{"VAL1_AA", SFX_VAL1_AA},
	{"VAL1_AB", SFX_VAL1_AB},
	{"VAL1_AC", SFX_VAL1_AC},
	{"VAL1_AD", SFX_VAL1_AD},
	{"VAL1_AE", SFX_VAL1_AE},
	{"VAL1_AF", SFX_VAL1_AF},
	{"VAL1_AG", SFX_VAL1_AG},
	{"VAL1_AH", SFX_VAL1_AH},
	{"VAL1_AI", SFX_VAL1_AI},
	{"VAL2_AA", SFX_VAL2_AA},
	{"VAL2_AB", SFX_VAL2_AB},
	{"VAL2_AC", SFX_VAL2_AC},
	{"VAL2_AD", SFX_VAL2_AD},
	{"VAL2_AE", SFX_VAL2_AE},
	{"VAL2_AF", SFX_VAL2_AF},
	{"VAL2_AG", SFX_VAL2_AG},
	{"VAL2_AH", SFX_VAL2_AH},
	{"VAL2_AI", SFX_VAL2_AI},
	{"VAL3_AA", SFX_VAL3_AA},
	{"VAL3_AB", SFX_VAL3_AB},
	{"VAL3_AC", SFX_VAL3_AC},
	{"VAL3_AD", SFX_VAL3_AD},
	{"VAL3_AE", SFX_VAL3_AE},
	{"VAL3_AF", SFX_VAL3_AF},
	{"VIC1_BA", SFX_VIC1_BA},
	{"VIC1_BB", SFX_VIC1_BB},
	{"VIC1_BC", SFX_VIC1_BC},
	{"VIC1_BD", SFX_VIC1_BD},
	{"VIC1_BE", SFX_VIC1_BE},
	{"VIC1_BF", SFX_VIC1_BF},
	{"VIC1_CA", SFX_VIC1_CA},
	{"VIC1_CB", SFX_VIC1_CB},
	{"VIC1_CC", SFX_VIC1_CC},
	{"VIC1_CD", SFX_VIC1_CD},
	{"VIC1_CE", SFX_VIC1_CE},
	{"VIC1_DA", SFX_VIC1_DA},
	{"VIC1_DB", SFX_VIC1_DB},
	{"VIC1_DC", SFX_VIC1_DC},
	{"VIC1_DD", SFX_VIC1_DD},
	{"VIC1_DE", SFX_VIC1_DE},
	{"VIC1_DF", SFX_VIC1_DF},
	{"VIC1_DG", SFX_VIC1_DG},
	{"VIC1_DH", SFX_VIC1_DH},
	{"VIC2_AA", SFX_VIC2_AA},
	{"VIC2_AB", SFX_VIC2_AB},
	{"VIC2_AC", SFX_VIC2_AC},
	{"VIC2_AD", SFX_VIC2_AD},
	{"VIC2_AF", SFX_VIC2_AF},
	{"VIC2_AG", SFX_VIC2_AG},
	{"VIC2_AH", SFX_VIC2_AH},
	{"VIC2_BA", SFX_VIC2_BA},
	{"VIC2_BE", SFX_VIC2_BE},
	{"VIC2_BI", SFX_VIC2_BI},
	{"VIC3_AA", SFX_VIC3_AA},
	{"VIC3_AB", SFX_VIC3_AB},
	{"VIC3_AD", SFX_VIC3_AD},
	{"VIC3_AE", SFX_VIC3_AE},
	{"VIC3_AF", SFX_VIC3_AF},
	{"VIC3_AG", SFX_VIC3_AG},
	{"VIC3_AH", SFX_VIC3_AH},
	{"VIC3_AJ", SFX_VIC3_AJ},
	{"VIC3_AK", SFX_VIC3_AK},
	{"VIC3_AL", SFX_VIC3_AL},
	{"VIC3_AM", SFX_VIC3_AM},
	{"VIC3_AN", SFX_VIC3_AN},
	{"VIC3_AO", SFX_VIC3_AO},
	{"VIC3_BA", SFX_VIC3_BA},
	{"VIC3_BB", SFX_VIC3_BB},
	{"VIC3_BC", SFX_VIC3_BC},
	{"VIC4_AA", SFX_VIC4_AA},
	{"VIC4_AB", SFX_VIC4_AB},
	{"VIC4_AC", SFX_VIC4_AC},
	{"VIC4_AD", SFX_VIC4_AD},
	{"VIC4_AE", SFX_VIC4_AE},
	{"VIC4_AF", SFX_VIC4_AF},
	{"VIC4_AG", SFX_VIC4_AG},
	{"VIC4_AH", SFX_VIC4_AH},
	{"VIC4_AI", SFX_VIC4_AI},
	{"VIC4_AJ", SFX_VIC4_AJ},
	{"VIC4_AK", SFX_VIC4_AK},
	{"VIC4_AL", SFX_VIC4_AL},
	{"VIC4_AM", SFX_VIC4_AM},
	{"VIC4_AN", SFX_VIC4_AN},
	{"VIC4_BA", SFX_VIC4_BA},
	{"VIC4_BB", SFX_VIC4_BB},
	{"VIC4_BC", SFX_VIC4_BC},
	{"VIC4_BD", SFX_VIC4_BD},
	{"VIC4_BE", SFX_VIC4_BE},
	{"VIC4_BF", SFX_VIC4_BF},
	{"VIC4_BG", SFX_VIC4_BG},
	{"VIC4_BH", SFX_VIC4_BH},
	{"VIC5_AA", SFX_VIC5_AA},
	{"VIC5_AB", SFX_VIC5_AB},
	{"VIC5_AC", SFX_VIC5_AC},
	{"VIC5_AD", SFX_VIC5_AD},
	{"VIC5_AE", SFX_VIC5_AE},
	{"VIC5_AF", SFX_VIC5_AF},
	{"VIC5_AG", SFX_VIC5_AG},
	{"VIC5_AH", SFX_VIC5_AH},
	{"VIC5_AI", SFX_VIC5_AI},
	{"VIC5_AJ", SFX_VIC5_AJ},
	{"VIC5_AK", SFX_VIC5_AK},
	{"VIC5_AL", SFX_VIC5_AL},
	{"VIC5_FA", SFX_VIC5_FA},
	{"VIC5_FD", SFX_VIC5_FD},
	{"VIC5_FF", SFX_VIC5_FF},
	{"VIC5_FG", SFX_VIC5_FG},
	{"VIC5_FH", SFX_VIC5_FH},
	{"VIC5_FI", SFX_VIC5_FI},
	{"VIC5_FJ", SFX_VIC5_FJ},
	{"VIC5_FK", SFX_VIC5_FK},
	{"VIC6_AA", SFX_VIC6_AA},
	{"VIC6_AB", SFX_VIC6_AB},
	{"VIC6_AC", SFX_VIC6_AC},
	{"VIC6_AD", SFX_VIC6_AD},
	{"VIC6_AE", SFX_VIC6_AE},
	{"VIC6_AF", SFX_VIC6_AF},
	{"VIC6_AG", SFX_VIC6_AG},
	{"VIC6_AH", SFX_VIC6_AH},
	{"VIC6_AI", SFX_VIC6_AI},
	{"VIC6_AJ", SFX_VIC6_AJ},
	{"VIC6_AK", SFX_VIC6_AK},
	{"VIC6_AL", SFX_VIC6_AL},
	{"VIC6_AM", SFX_VIC6_AM},
	{"VIC6_AN", SFX_VIC6_AN},
	{"VIC6_AO", SFX_VIC6_AO},
	{"VIC7_AA", SFX_VIC7_AA},
	{"VIC7_AB", SFX_VIC7_AB},
	{"VIC7_AC", SFX_VIC7_AC},
	{"VIC7_AD", SFX_VIC7_AD},
	{"VIC7_AE", SFX_VIC7_AE},
	{"VIC7_AG", SFX_VIC7_AG},
	{"VIC7_AH", SFX_VIC7_AH},
	{"VIC7_AJ", SFX_VIC7_AJ},
	{"VIC7_AL", SFX_VIC7_AL},
	{"VIC7_AM", SFX_VIC7_AM},
	{"VIC7_AN", SFX_VIC7_AN},
	{"VIC7_AO", SFX_VIC7_AO},
	{"VIC7_BA", SFX_VIC7_BA},
	{"VIC7_BB", SFX_VIC7_BB},
	{"VIC7_BC", SFX_VIC7_BC},
	{"VIC7_BD", SFX_VIC7_BD},
	{"VIC7_BE", SFX_VIC7_BE},
	{"VIC7_BF", SFX_VIC7_BF},
	{"VIC7_BG", SFX_VIC7_BG},
	{"VIC7_BH", SFX_VIC7_BH},
	{"VIC7_BI", SFX_VIC7_BI},
	{"WAC1_AA", SFX_WAC1_AA},
	{"WAC1_AB", SFX_WAC1_AB},
	{"WAC1_AC", SFX_WAC1_AC},
	{"WAC1_AD", SFX_WAC1_AD},
	{"WAC1_AE", SFX_WAC1_AE},
	{"WAC1_AF", SFX_WAC1_AF},
	{"WAC1_AG", SFX_WAC1_AG},
	{"WAC1_AH", SFX_WAC1_AH},
	{"WAC2_AA", SFX_WAC2_AA},
	{"WAC2_AB", SFX_WAC2_AB},
	{"WAC2_AC", SFX_WAC2_AC},
	{"WAC2_AD", SFX_WAC2_AD},
	{"WAC2_AE", SFX_WAC2_AE},
	{"WAC2_AF", SFX_WAC2_AF},
	{"WAC2_AG", SFX_WAC2_AG},
	{"WED1_AA", SFX_WED1_AA},
	{"WED1_AB", SFX_WED1_AB},
	{"WED1_AC", SFX_WED1_AC},
	{"WED1_AD", SFX_WED1_AD},
	{"WED1_AE", SFX_WED1_AE},
	{"WED1_AF", SFX_WED1_AF},
	{"WED1_AG", SFX_WED1_AG},
	{"WED2_AA", SFX_WED2_AA},
	{"WED2_AB", SFX_WED2_AB},
	{"WED2_AC", SFX_WED2_AC},
	{"WED2_AD", SFX_WED2_AD},
	{"WED2_AE", SFX_WED2_AE},
	{"WED2_AF", SFX_WED2_AF},
	{"WED2_AG", SFX_WED2_AG},
	{"WED2_AH", SFX_WED2_AH},
	{"WED3_AA", SFX_WED3_AA},
	{"WED3_AB", SFX_WED3_AB},
	{"WED3_AC", SFX_WED3_AC},
	{"WED3_AD", SFX_WED3_AD},
	{"WED3_AE", SFX_WED3_AE},
	{"WED3_AF", SFX_WED3_AF},
	{"WED3_AG", SFX_WED3_AG},
	{"WED3_AH", SFX_WED3_AH},
	{"WED3_AI", SFX_WED3_AI},
	{"WED3_AJ", SFX_WED3_AJ},
	{"WED3_AK", SFX_WED3_AK},
	{"WED3_AL", SFX_WED3_AL},
	{"DONH3IA", SFX_DONH3IA},
	{"DONH3JA", SFX_DONH3JA},
	{"DONH5CA", SFX_DONH5CA},
	{"DONH5CB", SFX_DONH5CB},
	{"DONS7CA", SFX_DONS7CA},
	{"DONS7CB", SFX_DONS7CB},
	{"DONS7CC", SFX_DONS7CC},
	{"DONS7CD", SFX_DONS7CD},
	{"DONS7CE", SFX_DONS7CE},
	{"JDT1_MA", SFX_JDT1_MA},
	{"JDT1_MB", SFX_JDT1_MB},
	{"JDT1_MC", SFX_JDT1_MC},
	{"JDT1_MD", SFX_JDT1_MD},
	{"JDT1_ME", SFX_JDT1_ME},
	{"JDT1_MF", SFX_JDT1_MF},
	{"JDT1_MG", SFX_JDT1_MG},
	{"JDT1_MH", SFX_JDT1_MH},
	{"JDT4_BA", SFX_JDT4_BA},
	{"JDT4_BB", SFX_JDT4_BB},
	{"JDT4_BC", SFX_JDT4_BC},
	{"JDT5_FA", SFX_JDT5_FA},
	{"JDT5_FB", SFX_JDT5_FB},
	{"JDT5_FC", SFX_JDT5_FC},
	{"JDT5_GA", SFX_JDT5_GA},
	{"JDT5_GB", SFX_JDT5_GB},
	{"JDT6_CA", SFX_JDT6_CA},
	{"JDT6_CB", SFX_JDT6_CB},
	{"JDT6_DA", SFX_JDT6_DA},
	{"JDT7_CD", SFX_JDT7_CD},
	{"JDT8_AI", SFX_JDT8_AI},
	{"JDT8_BA", SFX_JDT8_BA},
	{"JDT8_FD", SFX_JDT8_FD},
	{"JDT8_FE", SFX_JDT8_FE},
	{"JDT8_FF", SFX_JDT8_FF},
	{"JDT8_FG", SFX_JDT8_FG},
	{"JDT8_FH", SFX_JDT8_FH},
	{"JDT8_GA", SFX_JDT8_GA},
	{"JDT8_HA", SFX_JDT8_HA},
	{"JDT8_HB", SFX_JDT8_HB},
	{"MAC1_JC", SFX_MAC1_JC},
	{"MAC4_DA", SFX_MAC4_DA},
	{"MAC4_DB", SFX_MAC4_DB},
	{"MAC4_DC", SFX_MAC4_DC},
	{"MAC4_DD", SFX_MAC4_DD},
	{"MAC4_DE", SFX_MAC4_DE},
	{"MAC4_DF", SFX_MAC4_DF},
	{"MAC4_DG", SFX_MAC4_DG},
	{"MAC4_DH", SFX_MAC4_DH},
	{"MAR1_HD", SFX_MAR1_HD},
	{"MAR2_GF", SFX_MAR2_GF},
	{"MAR5_DA", SFX_MAR5_DA},
	{"MAR5_DB", SFX_MAR5_DB},
	{"MAR5_DC", SFX_MAR5_DC},
	{"MAR5_EA", SFX_MAR5_EA},
	{"MAR5_EB", SFX_MAR5_EB},
	{"MAR5_EC", SFX_MAR5_EC},
	{"MAR5_ED", SFX_MAR5_ED},
	{"NEDS1BA", SFX_NEDS1BA},
	{"NEDS1BB", SFX_NEDS1BB},
	{"NEDS1BC", SFX_NEDS1BC},
	{"NEDS1BD", SFX_NEDS1BD},
	{"NEDS1BE", SFX_NEDS1BE},
	{"NEDS1BF", SFX_NEDS1BF},
	{"NOOD_AA", SFX_NOOD_AA},
	{"NOOD_AB", SFX_NOOD_AB},
	{"NOOD_AC", SFX_NOOD_AC},
	{"NOOD_AD", SFX_NOOD_AD},
	{"NOOD_AE", SFX_NOOD_AE},
	{"NOOD_AF", SFX_NOOD_AF},
	{"NOOD_AG", SFX_NOOD_AG},
	{"NOOD_AH", SFX_NOOD_AH},
	{"NOOD_AI", SFX_NOOD_AI},
	{"NOOD_AJ", SFX_NOOD_AJ},
	{"NOOD_AK", SFX_NOOD_AK},
	{"NOOD_AL", SFX_NOOD_AL},
	{"NOOD_AM", SFX_NOOD_AM},
	{"NOOD_AN", SFX_NOOD_AN},
	{"NOOD_AO", SFX_NOOD_AO},
	{"NOOD_AP", SFX_NOOD_AP},
	{"NOOD_AQ", SFX_NOOD_AQ},
	{"NOOD_AR", SFX_NOOD_AR},
	{"NOOD_AS", SFX_NOOD_AS},
	{"NOOD_AT", SFX_NOOD_AT},
	{"PIZZ_AA", SFX_PIZZ_AA},
	{"PIZZ_AB", SFX_PIZZ_AB},
	{"PIZZ_AC", SFX_PIZZ_AC},
	{"PIZZ_AD", SFX_PIZZ_AD},
	{"PIZZ_AE", SFX_PIZZ_AE},
	{"PIZZ_AF", SFX_PIZZ_AF},
	{"PIZZ_AG", SFX_PIZZ_AG},
	{"PIZZ_AH", SFX_PIZZ_AH},
	{"PIZZ_AI", SFX_PIZZ_AI},
	{"PIZZ_AJ", SFX_PIZZ_AJ},
	{"PIZZ_AK", SFX_PIZZ_AK},
	{"PIZZ_AL", SFX_PIZZ_AL},
	{"PIZZ_AM", SFX_PIZZ_AM},
	{"PIZZ_AN", SFX_PIZZ_AN},
	{"PIZZ_AO", SFX_PIZZ_AO},
	{"PIZZ_AP", SFX_PIZZ_AP},
	{"PIZZ_AQ", SFX_PIZZ_AQ},
	{"PIZZ_AR", SFX_PIZZ_AR},
	{"PIZZ_AS", SFX_PIZZ_AS},
	{"PIZZ_AT", SFX_PIZZ_AT},
	{"RAYS2BA", SFX_RAYS2BA},
	{"RAYS2BB", SFX_RAYS2BB},
	{"RAYS2CA", SFX_RAYS2CA},
	{"RAYS2CB", SFX_RAYS2CB},
	{"RAYS2DA", SFX_RAYS2DA},
	{"RAYS2DB", SFX_RAYS2DB},
	{"RAYS2EA", SFX_RAYS2EA},
	{"RAYS2EB", SFX_RAYS2EB},
	{"RAYS4AA", SFX_RAYS4AA},
	{"RAYS4AB", SFX_RAYS4AB},
	{"RAYS4AC", SFX_RAYS4AC},
	{"RAYS4AD", SFX_RAYS4AD},
	{"RAYS4AE", SFX_RAYS4AE},
	{"RAYS4AF", SFX_RAYS4AF},
	{"RAYS4BA", SFX_RAYS4BA},
	{"RAYS4BB", SFX_RAYS4BB},
	{"RAYS4BC", SFX_RAYS4BC},
	{"RAYS4BD", SFX_RAYS4BD},
	{"RAYS4BE", SFX_RAYS4BE},
	{"RAYS4BF", SFX_RAYS4BF},
	{"RAYS4BG", SFX_RAYS4BG},
	{"RAYS5BA", SFX_RAYS5BA},
	{"RAYS5BB", SFX_RAYS5BB},
	{"RMN_AA", SFX_RMN_AA},
	{"RMN_AB", SFX_RMN_AB},
	{"RMN_AC", SFX_RMN_AC},
	{"RMN_AD", SFX_RMN_AD},
	{"RMN_AE", SFX_RMN_AE},
	{"RMN_AF", SFX_RMN_AF},
	{"RMN_AG", SFX_RMN_AG},
	{"RMN_AH", SFX_RMN_AH},
	{"RMN_AI", SFX_RMN_AI},
	{"RMN_AJ", SFX_RMN_AJ},
	{"RMN_AK", SFX_RMN_AK},
	{"SAL1_BA", SFX_SAL1_BA},
	{"SAL1_BB", SFX_SAL1_BB},
	{"SAL1_BC", SFX_SAL1_BC},
	{"SAL1_BD", SFX_SAL1_BD},
	{"SAL2_BA", SFX_SAL2_BA},
	{"SAL2_BB", SFX_SAL2_BB},
	{"SAL2_BC", SFX_SAL2_BC},
	{"SAL2_BD", SFX_SAL2_BD},
	{"SAL2_CA", SFX_SAL2_CA},
	{"SAL2_CB", SFX_SAL2_CB},
	{"SAL2_CC", SFX_SAL2_CC},
	{"SAL2_CD", SFX_SAL2_CD},
	{"SAL2_CE", SFX_SAL2_CE},
	{"SAL2_CF", SFX_SAL2_CF},
	{"SAL2_CG", SFX_SAL2_CG},
	{"SAL2_CH", SFX_SAL2_CH},
	{"SAL2_CI", SFX_SAL2_CI},
	{"SAL2_CJ", SFX_SAL2_CJ},
	{"SAL2_CL", SFX_SAL2_CL},
	{"SAL2_CM", SFX_SAL2_CM},
	{"SAL2_CN", SFX_SAL2_CN},
	{"SAL2_CO", SFX_SAL2_CO},
	{"SAL2_CP", SFX_SAL2_CP},
	{"SAL2_CQ", SFX_SAL2_CQ},
	{"SAL2_CR", SFX_SAL2_CR},
	{"SAL2_CS", SFX_SAL2_CS},
	{"SAL2_CT", SFX_SAL2_CT},
	{"SAL2_CU", SFX_SAL2_CU},
	{"SAL2_CV", SFX_SAL2_CV},
	{"SAL2_DD", SFX_SAL2_DD},
	{"SAL2_DE", SFX_SAL2_DE},
	{"SAL3_BA", SFX_SAL3_BA},
	{"SAL3_CA", SFX_SAL3_CA},
	{"SAL3_DA", SFX_SAL3_DA},
	{"SAL4_AA", SFX_SAL4_AA},
	{"SAL5_AA", SFX_SAL5_AA},
	{"SAL5_AD", SFX_SAL5_AD},
	{"SAL5_AF", SFX_SAL5_AF},
	{"SAL5_AG", SFX_SAL5_AG},
	{"SAL6_CA", SFX_SAL6_CA},
	{"SAL6_CB", SFX_SAL6_CB},
	{"SAL6_CC", SFX_SAL6_CC},
	{"SAL6_CD", SFX_SAL6_CD},
	{"SAL7_CD", SFX_SAL7_CD},
	{"SAL8_HA", SFX_SAL8_HA},
	{"SAL8_HB", SFX_SAL8_HB},
	{"SAL8_HC", SFX_SAL8_HC},
	{"SAL8_HD", SFX_SAL8_HD},
	{"SAL8_HE", SFX_SAL8_HE},
	{"SAL8_HF", SFX_SAL8_HF},
	{"SAL8_HG", SFX_SAL8_HG},
	{"SAL8_HH", SFX_SAL8_HH},
	{"SALH1AA", SFX_SALH1AA},
	{"SALH1AB", SFX_SALH1AB},
	{"SALH1BA", SFX_SALH1BA},
	{"SALH1BB", SFX_SALH1BB},
	{"SALH1CA", SFX_SALH1CA},
	{"SALH1CB", SFX_SALH1CB},
	{"SALH1DA", SFX_SALH1DA},
	{"SALH1EA", SFX_SALH1EA},
	{"SALH1EB", SFX_SALH1EB},
	{"SALH1FB", SFX_SALH1FB},
	{"SALH1FC", SFX_SALH1FC},
	{"SALH1FG", SFX_SALH1FG},
	{"SALH1GA", SFX_SALH1GA},
	{"SALH1GB", SFX_SALH1GB},
	{"SALH1HA", SFX_SALH1HA},
	{"SALH2BE", SFX_SALH2BE},
	{"SALH2BF", SFX_SALH2BF},
	{"SALH2BG", SFX_SALH2BG},
	{"SALH4CB", SFX_SALH4CB},
	{"SALS1BA", SFX_SALS1BA},
	{"SALS1BB", SFX_SALS1BB},
	{"SALS1BC", SFX_SALS1BC},
	{"SALS1BD", SFX_SALS1BD},
	{"SALS2BA", SFX_SALS2BA},
	{"SALS2BB", SFX_SALS2BB},
	{"SALS2CA", SFX_SALS2CA},
	{"SALS2CB", SFX_SALS2CB},
	{"SALS2CC", SFX_SALS2CC},
	{"SALS2CE", SFX_SALS2CE},
	{"SALS3BA", SFX_SALS3BA},
	{"SALS3BC", SFX_SALS3BC},
	{"SALS3DB", SFX_SALS3DB},
	{"SALS3DC", SFX_SALS3DC},
	{"SALS3DD", SFX_SALS3DD},
	{"SALS3DF", SFX_SALS3DF},
	{"SALS3DG", SFX_SALS3DG},
	{"STRE_AA", SFX_STRE_AA},
	{"STRE_AB", SFX_STRE_AB},
	{"STRE_AC", SFX_STRE_AC},
	{"STRE_AD", SFX_STRE_AD},
	{"STRE_AE", SFX_STRE_AE},
	{"STRE_AF", SFX_STRE_AF},
	{"STRE_AG", SFX_STRE_AG},
	{"STRE_BA", SFX_STRE_BA},
	{"STRE_BB", SFX_STRE_BB},
	{"STRE_BC", SFX_STRE_BC},
	{"STRE_BD", SFX_STRE_BD},
	{"STRE_BE", SFX_STRE_BE},
	{"STRE_BF", SFX_STRE_BF},
	{"STRE_BG", SFX_STRE_BG},
	{"STRE_CA", SFX_STRE_CA},
	{"STRE_CB", SFX_STRE_CB},
	{"STRE_CC", SFX_STRE_CC},
	{"TOSH1BA", SFX_TOSH1BA},
	{"TOSH1BB", SFX_TOSH1BB},
	{"TOSH1BC", SFX_TOSH1BC},
	{"TOSH1BD", SFX_TOSH1BD},
	{"TOSH3IA", SFX_TOSH3IA},
	{"TOSH3IB", SFX_TOSH3IB},
	{"VIC2_BB", SFX_VIC2_BB},
	{"VIC2_BC", SFX_VIC2_BC},
	{"VIC2_BD", SFX_VIC2_BD},
	{"VIC2_BF", SFX_VIC2_BF},
	{"VIC2_BH", SFX_VIC2_BH},
	{"VIC2_BJ", SFX_VIC2_BJ},
	{"VIC2_CA", SFX_VIC2_CA},
	{"VIC2_DA", SFX_VIC2_DA},
	{"VIC2_DB", SFX_VIC2_DB},
	{"VIC2_DE", SFX_VIC2_DC},
	{"VIC4_CA", SFX_VIC4_CA},
	{"VIC4_CB", SFX_VIC4_CB},
	{"VIC5_DA", SFX_VIC5_DA},
	{"VIC5_DB", SFX_VIC5_DB},
	{"VIC5_DC", SFX_VIC5_DC},
	{"VIC5_EA", SFX_VIC5_EA},
	{"VIC5_EB", SFX_VIC5_EB},
	{"VIC5_EC", SFX_VIC5_EC},
	{"VIC5_FB", SFX_VIC5_FB},
	{"VIC5_FC", SFX_VIC5_FC},
	{"VIC5_FE", SFX_VIC5_FE},
	{"VIC6_BA", SFX_VIC6_BA},
	{"VIC6_BB", SFX_VIC6_BB},
	{"VIC7_CA", SFX_VIC7_CA},
	{"VIC7_CB", SFX_VIC7_CB},
	{"VIC7_CC", SFX_VIC7_CC},
	{"LCN_AA", SFX_LCN_AA},
	{"LCN_AB", SFX_LCN_AB},
	{"MSA12AB", SFX_SFX_ANG1_AA},
	{"BNK1_12", SFX_SFX_BNK1_12},
	{"TAX1_1", SFX_SFX_TAX1_1},
	{"TAX1_2", SFX_SFX_TAX1_2},
	{"TAX1_3", SFX_SFX_TAX1_3},
	{"TAX1_4", SFX_SFX_TAX1_4},
	{"TAX1_5", SFX_SFX_TAX1_5},
	{"TAX2_1", SFX_SFX_TAX2_1},
	{"TAX2_2", SFX_SFX_TAX2_2},
	{"TAX2_3", SFX_SFX_TAX2_3},
	{"TAX2_4", SFX_SFX_TAX2_4},
	{"TAX2_5", SFX_SFX_TAX2_5},
	{"TAX2_6", SFX_SFX_TAX2_6},
	{"TAX2_7", SFX_SFX_TAX2_7},
	{"TAX3_1", SFX_SFX_TAX3_1},
	{"TAX3_2", SFX_SFX_TAX3_2},
	{"TAX3_3", SFX_SFX_TAX3_3},
	{"TAX3_4", SFX_SFX_TAX3_4},
	{"TAX3_5", SFX_SFX_TAX3_5},
	{nil, 0}
};

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

// LCS: mission audio turns from streamed to sampled

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
			m_sMissionAudio.m_nMissionAudioCounter[slot] = m_nTimeSpent * SampleManager.GetSampleLength(missionAudioSfx) / SampleManager.GetSampleBaseFrequency(missionAudioSfx);
			m_sMissionAudio.m_nMissionAudioCounter[slot] = 11 * m_sMissionAudio.m_nMissionAudioCounter[slot] / 10;
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
	//if (IsMissionAudioSamplePlaying(slot))
	//	return m_sMissionAudio.m_nSampleIndex[slot] != STREAMED_SOUND_MISSION_ROK2_01;
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
		SampleManager.StopChannel(slot + CHANNEL_MISSION_AUDIO_1);
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
		// TODO: LoadMissionAudio
		SampleManager.LoadPedComment(m_sMissionAudio.m_nSampleIndex[slot]);
		SampleManager.SetChannelFrequency(slot + CHANNEL_MISSION_AUDIO_1, SampleManager.GetSampleBaseFrequency(m_sMissionAudio.m_nSampleIndex[slot]));
		m_sMissionAudio.m_nLoadingStatus[slot] = LOADING_STATUS_LOADED;
		nFramesUntilFailedLoad[slot] = 0;
		break;
	case LOADING_STATUS_LOADED:
		if (!m_sMissionAudio.m_bIsPlayed[slot])
			return;
		if (g_bMissionAudioLoadFailed[slot]) {
			if (m_bTimerJustReset) {
				ClearMissionAudio(slot);
				SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
				SampleManager.StopChannel(slot + CHANNEL_MISSION_AUDIO_1);
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
				SampleManager.InitialiseChannel(slot + CHANNEL_MISSION_AUDIO_1, m_sMissionAudio.m_nSampleIndex[slot], SFX_BANK_PED_COMMENTS);
				if(m_nUserPause)
					SampleManager.SetChannelFrequency(slot + CHANNEL_MISSION_AUDIO_1, 0);
				else
					SampleManager.SetChannelFrequency(slot + CHANNEL_MISSION_AUDIO_1, SampleManager.GetSampleBaseFrequency(m_sMissionAudio.m_nSampleIndex[slot]));
				if (m_sMissionAudio.m_bPredefinedProperties[slot]) {
					SampleManager.SetChannelVolume(slot + CHANNEL_MISSION_AUDIO_1, 127);
					SampleManager.SetChannelPan(slot + CHANNEL_MISSION_AUDIO_1, 63);
					if (m_sMissionAudio.m_nSampleIndex[slot] == SFX_SFX_CAMERA_LEFT || m_sMissionAudio.m_nSampleIndex[slot] == SFX_SFX_AIRHORN_LEFT)
						SampleManager.SetChannelPan(slot + CHANNEL_MISSION_AUDIO_1, 0);
					else if (m_sMissionAudio.m_nSampleIndex[slot] == SFX_SFX_CAMERA_RIGHT || m_sMissionAudio.m_nSampleIndex[slot] == SFX_SFX_AIRHORN_RIGHT)
						SampleManager.SetChannelPan(slot + CHANNEL_MISSION_AUDIO_1, 127);
					else
						SampleManager.SetChannelPan(slot + CHANNEL_MISSION_AUDIO_1, 63);
				} else {
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
					SampleManager.SetChannelVolume(slot + CHANNEL_MISSION_AUDIO_1, emittingVol);
					SampleManager.SetChannelPan(slot + CHANNEL_MISSION_AUDIO_1, pan);
				}
				SampleManager.StartChannel(slot + CHANNEL_MISSION_AUDIO_1);
			}
			m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_PLAYING;
			nCheckPlayingDelay[slot] = 30;
			break;
		case PLAY_STATUS_PLAYING:
			if (m_bTimerJustReset) {
				ClearMissionAudio(slot);
				SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
				SampleManager.StopChannel(slot + CHANNEL_MISSION_AUDIO_1);
				break;
			}
			if (MissionScriptAudioUsesPoliceChannel(m_sMissionAudio.m_nSampleIndex[slot])) {
				if (!m_nUserPause) {
					if (nCheckPlayingDelay[slot]) {
						--nCheckPlayingDelay[slot];
					} else if ((g_bMissionAudioLoadFailed[slot] && m_sMissionAudio.m_nMissionAudioCounter[slot]-- == 0) || GetMissionScriptPoliceAudioPlayingStatus() == PLAY_STATUS_FINISHED) {
						debug("FINISHED PLAYINGXXXXXXXXXXXXX");
						m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_FINISHED;
						m_sMissionAudio.m_nSampleIndex[slot] = NO_SAMPLE;
						SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
						m_sMissionAudio.m_nMissionAudioCounter[slot] = 0;
					}
				}
			} else if (m_sMissionAudio.m_bIsPlaying[slot]) {
				if(SampleManager.GetChannelUsedFlag(slot + CHANNEL_MISSION_AUDIO_1) || m_nUserPause || m_nPreviousUserPause) {
					if(m_nUserPause)
						SampleManager.SetChannelFrequency(slot + CHANNEL_MISSION_AUDIO_1, 0);
					else
					{
						SampleManager.SetChannelFrequency(slot + CHANNEL_MISSION_AUDIO_1, SampleManager.GetSampleBaseFrequency(m_sMissionAudio.m_nSampleIndex[slot]));
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
							SampleManager.SetChannelVolume(slot + CHANNEL_MISSION_AUDIO_1, emittingVol);
							SampleManager.SetChannelPan(slot + CHANNEL_MISSION_AUDIO_1, pan);
						}
					}
				} else {
					m_sMissionAudio.m_nPlayStatus[slot] = PLAY_STATUS_FINISHED;
					m_sMissionAudio.m_nSampleIndex[slot] = NO_SAMPLE;
					SampleManager.StopChannel(slot + CHANNEL_MISSION_AUDIO_1);
					m_sMissionAudio.m_nMissionAudioCounter[slot] = 0;
				}
			} else {
				if (m_nUserPause)
					break;
				if (nCheckPlayingDelay[slot]--) {
					if (!SampleManager.GetChannelUsedFlag(slot + CHANNEL_MISSION_AUDIO_1))
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
