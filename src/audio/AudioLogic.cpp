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
#include "ParticleObject.h"
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

#ifndef GTA_PS2
#define CHANNEL_PLAYER_VEHICLE_ENGINE m_nActiveSamples
#endif

enum eVehicleModel {
	LANDSTAL,
	IDAHO,
	STINGER,
	LINERUN,
	PEREN,
	SENTINEL,
	PATRIOT,
	FIRETRUK,
	TRASH,
	STRETCH,
	MANANA,
	INFERNUS,
	BLISTA,
	PONY,
	MULE,
	CHEETAH,
	AMBULAN,
	FBICAR,
	MOONBEAM,
	ESPERANT,
	TAXI,
	KURUMA,
	BOBCAT,
	MRWHOOP,
	BFINJECT,
	CORPSE,
	POLICE,
	ENFORCER,
	SECURICA,
	BANSHEE,
	PREDATOR,
	BUS,
	RHINO,
	BARRACKS,
	TRAIN,
	CHOPPER,
	DODO,
	COACH,
	CABBIE,
	STALLION,
	RUMPO,
	RCBANDIT,
	BELLYUP,
	MRWONGS,
	MAFIA,
	YARDIE,
	YAKUZA,
	DIABLOS,
	COLUMB,
	HOODS,
	AIRTRAIN,
	DEADDODO,
	SPEEDER,
	REEFER,
	PANLANT,
	FLATBED,
	YANKEE,
	ESCAPE,
	BORGNINE,
	TOYZ,
	GHOST,
	CAR151,
	CAR152,
	CAR153,
	CAR154,
	CAR155,
	CAR156,
	CAR157,
	CAR158,
	CAR159,
	MAX_CARS
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

Const static tVehicleSampleData aVehicleSettings[MAX_CARS] = {
    {SFX_CAR_REV_2, SFX_BANK_PATHFINDER, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 11487, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_8, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_ALARM_1, 10928, NEW_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_ALARM_1, 9935, TRUCK_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 12893, SFX_CAR_ALARM_1, 8941, OLD_DOOR},
    {SFX_CAR_REV_5, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 10706, SFX_CAR_ALARM_1, 11922, NEW_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_ALARM_1, 7948, TRUCK_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_POLICE_SIREN_SLOW, 11556, TRUCK_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 31478, SFX_CAR_ALARM_1, 8941, TRUCK_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_BMW328, 9538, SFX_CAR_ALARM_1, 12220, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_3, SFX_BANK_PORSCHE, SFX_CAR_HORN_BMW328, 12017, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_2, SFX_BANK_PATHFINDER, SFX_CAR_HORN_JEEP, 22295, SFX_CAR_ALARM_1, 12200, NEW_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_ALARM_1, 13400, NEW_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18286, SFX_CAR_ALARM_1, 9935, TRUCK_DOOR},
    {SFX_CAR_REV_3, SFX_BANK_PORSCHE, SFX_CAR_HORN_PORSCHE, 11025, SFX_CAR_ALARM_1, 13600, NEW_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 22295, SFX_AMBULANCE_SIREN_SLOW, 8795, TRUCK_DOOR},
    {SFX_CAR_REV_5, SFX_BANK_MERC, SFX_CAR_HORN_PORSCHE, 9271, SFX_POLICE_SIREN_SLOW, 16168, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 12170, SFX_CAR_ALARM_1, 8000, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_BUS2, 12345, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_2, SFX_BANK_PATHFINDER, SFX_CAR_HORN_BMW328, 10796, SFX_CAR_ALARM_1, 8543, NEW_DOOR},
    {SFX_CAR_REV_5, SFX_BANK_MERC, SFX_CAR_HORN_PORSCHE, 9271, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_2, SFX_BANK_PATHFINDER, SFX_CAR_HORN_PICKUP, 10924, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_PICKUP, 11025, SFX_ICE_CREAM_TUNE, 11025, OLD_DOOR},
    {SFX_CAR_REV_7, SFX_BANK_HOTROD, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_ALARM_1, 10000, OLD_DOOR},
    {SFX_CAR_REV_5, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 10706, SFX_POLICE_SIREN_SLOW, 13596, NEW_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 17260, SFX_POLICE_SIREN_SLOW, 13000, TRUCK_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_ALARM_1, 9935, TRUCK_DOOR},
    {SFX_CAR_REV_8, SFX_BANK_COBRA, SFX_CAR_HORN_PORSCHE, 10400, SFX_CAR_ALARM_1, 10123, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 26513, SFX_POLICE_SIREN_SLOW, 13596, OLD_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_BUS2, 11652, SFX_CAR_ALARM_1, 10554, BUS_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_ALARM_1, 8000, TRUCK_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 28043, SFX_CAR_ALARM_1, 9935, TRUCK_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_TRUCK, 29711, SFX_CAR_ALARM_1, 9935, BUS_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CESNA_IDLE, SFX_BANK_0, SFX_CAR_HORN_JEEP, 26513, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_BUS, 16291, SFX_CAR_ALARM_1, 7500, BUS_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10233, SFX_CAR_ALARM_1, 8935, OLD_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_PICKUP, 8670, SFX_CAR_ALARM_1, 8935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_PICKUP, 2000, SFX_CAR_ALARM_1, 17000, OLD_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_5, SFX_BANK_MERC, SFX_CAR_HORN_BMW328, 9003, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_2, SFX_BANK_PATHFINDER, SFX_CAR_HORN_PORSCHE, 12375, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_5, SFX_BANK_MERC, SFX_CAR_HORN_BUS2, 15554, SFX_CAR_ALARM_1, 9935, NEW_DOOR},
    {SFX_CAR_REV_7, SFX_BANK_HOTROD, SFX_CAR_HORN_BUS2, 13857, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_7, SFX_BANK_HOTROD, SFX_CAR_HORN_PICKUP, 10924, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, TRUCK_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 20143, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_0, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9000, OLD_DOOR},
    {SFX_CAR_REV_6, SFX_BANK_TRUCK, SFX_CAR_HORN_TRUCK, 28043, SFX_CAR_ALARM_1, 9935, TRUCK_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS, 18286, SFX_CAR_ALARM_1, 9935, TRUCK_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_56CHEV, 10842, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_4, SFX_BANK_SPIDER, SFX_CAR_HORN_BUS2, 18000, SFX_CAR_ALARM_1, 13400, NEW_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR},
    {SFX_CAR_REV_1, SFX_BANK_PACARD, SFX_CAR_HORN_JEEP, 21043, SFX_CAR_ALARM_1, 9935, OLD_DOOR}};


uint32 gPornNextTime;
uint32 gSawMillNextTime;
uint32 gShopNextTime;
uint32 gAirportNextTime;
uint32 gCinemaNextTime;
uint32 gDocksNextTime;
uint32 gHomeNextTime;
uint32 gCellNextTime;
uint32 gNextCryTime;

void
cAudioManager::PreInitialiseGameSpecificSetup()
{
	BankStartOffset[SFX_BANK_0] = SAMPLEBANK_START;
#ifdef GTA_PS2
	BankStartOffset[SFX_BANK_PACARD] = SFX_CAR_ACCEL_1;
	BankStartOffset[SFX_BANK_PATHFINDER] = SFX_CAR_ACCEL_2;
	BankStartOffset[SFX_BANK_PORSCHE] = SFX_CAR_ACCEL_3;
	BankStartOffset[SFX_BANK_SPIDER] = SFX_CAR_ACCEL_4;
	BankStartOffset[SFX_BANK_MERC] = SFX_CAR_ACCEL_5;
	BankStartOffset[SFX_BANK_TRUCK] = SFX_CAR_ACCEL_6;
	BankStartOffset[SFX_BANK_HOTROD] = SFX_CAR_ACCEL_7;
	BankStartOffset[SFX_BANK_COBRA] = SFX_CAR_ACCEL_8;
	BankStartOffset[SFX_BANK_NONE] = SFX_CAR_ACCEL_9;
	BankStartOffset[SFX_BANK_FRONT_END_MENU] = SFX_PAGE_CHANGE_AND_BACK_LEFT;
	BankStartOffset[SFX_BANK_TRAIN] = SFX_TRAIN_STATION_AMBIENCE_LOOP;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_1] = SFX_CLUB_1;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_2] = SFX_CLUB_2;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_3] = SFX_CLUB_3;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_4] = SFX_CLUB_4;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_5] = SFX_CLUB_5;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_6] = SFX_CLUB_6;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_7] = SFX_CLUB_7;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_8] = SFX_CLUB_8;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_9] = SFX_CLUB_9;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_10] = SFX_CLUB_10;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_11] = SFX_CLUB_11;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_12] = SFX_CLUB_12;
	BankStartOffset[SFX_BANK_BUILDING_CLUB_RAGGA] = SFX_CLUB_RAGGA;
	BankStartOffset[SFX_BANK_BUILDING_STRIP_CLUB_1] = SFX_STRIP_CLUB_1;
	BankStartOffset[SFX_BANK_BUILDING_STRIP_CLUB_2] = SFX_STRIP_CLUB_2;
	BankStartOffset[SFX_BANK_BUILDING_WORKSHOP] = SFX_WORKSHOP_1;
	BankStartOffset[SFX_BANK_BUILDING_PIANO_BAR] = SFX_PIANO_BAR_1;
	BankStartOffset[SFX_BANK_BUILDING_SAWMILL] = SFX_SAWMILL_LOOP;
	BankStartOffset[SFX_BANK_BUILDING_DOG_FOOD_FACTORY] = SFX_DOG_FOOD_FACTORY;
	BankStartOffset[SFX_BANK_BUILDING_LAUNDERETTE] = SFX_LAUNDERETTE_LOOP;
	BankStartOffset[SFX_BANK_BUILDING_RESTAURANT_CHINATOWN] = SFX_RESTAURANT_CHINATOWN;
	BankStartOffset[SFX_BANK_BUILDING_RESTAURANT_ITALY] = SFX_RESTAURANT_ITALY;
	BankStartOffset[SFX_BANK_BUILDING_RESTAURANT_GENERIC_1] = SFX_RESTAURANT_GENERIC_1;
	BankStartOffset[SFX_BANK_BUILDING_RESTAURANT_GENERIC_2] = SFX_RESTAURANT_GENERIC_2;
	BankStartOffset[SFX_BANK_BUILDING_AIRPORT] = SFX_AIRPORT_ANNOUNCEMENT_1;
	BankStartOffset[SFX_BANK_BUILDING_SHOP] = SFX_SHOP_LOOP;
	BankStartOffset[SFX_BANK_BUILDING_CINEMA] = SFX_CINEMA_BASS_1;
	BankStartOffset[SFX_BANK_BUILDING_DOCKS] = SFX_DOCKS_FOGHORN;
	BankStartOffset[SFX_BANK_BUILDING_HOME] = SFX_HOME_1;
	BankStartOffset[SFX_BANK_BUILDING_PORN_1] = SFX_PORN_1_LOOP;
	BankStartOffset[SFX_BANK_BUILDING_PORN_2] = SFX_PORN_2_LOOP;
	BankStartOffset[SFX_BANK_BUILDING_PORN_3] = SFX_PORN_3_LOOP;
	BankStartOffset[SFX_BANK_BUILDING_POLICE_BALL] = SFX_POLICE_BALL_1;
	BankStartOffset[SFX_BANK_BUILDING_BANK_ALARM] = SFX_BANK_ALARM_1;
	BankStartOffset[SFX_BANK_BUILDING_RAVE_INDUSTRIAL] = SFX_RAVE_INDUSTRIAL;
	BankStartOffset[SFX_BANK_BUILDING_RAVE_COMMERCIAL] = SFX_RAVE_COMMERCIAL;
	BankStartOffset[SFX_BANK_BUILDING_RAVE_SUBURBAN] = SFX_RAVE_SUBURBAN;
	BankStartOffset[SFX_BANK_BUILDING_RAVE_COMMERCIAL_2] = SFX_RAVE_COMMERCIAL_2;
	BankStartOffset[SFX_BANK_BUILDING_39] = SFX_CLUB_1_1;
	BankStartOffset[SFX_BANK_BUILDING_40] = SFX_CLUB_1_2;
	BankStartOffset[SFX_BANK_BUILDING_41] = SFX_CLUB_1_3;
	BankStartOffset[SFX_BANK_BUILDING_42] = SFX_CLUB_1_4;
	BankStartOffset[SFX_BANK_BUILDING_43] = SFX_CLUB_1_5;
	BankStartOffset[SFX_BANK_BUILDING_44] = SFX_CLUB_1_6;
	BankStartOffset[SFX_BANK_BUILDING_45] = SFX_CLUB_1_7;
	BankStartOffset[SFX_BANK_BUILDING_46] = SFX_CLUB_1_8;
	BankStartOffset[SFX_BANK_BUILDING_47] = SFX_CLUB_1_9;
	BankStartOffset[SFX_BANK_GENERIC_EXTRA] = SFX_EXPLOSION_1;
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

	m_nBridgeEntity = CreateEntity(AUDIOTYPE_BRIDGE, (void *)1);
	if (m_nBridgeEntity >= 0)
		SetEntityStatus(m_nBridgeEntity, TRUE);

	m_nMissionAudioSampleIndex = NO_SAMPLE;
	m_nMissionAudioLoadingStatus = LOADING_STATUS_NOT_LOADED;
	m_nMissionAudioPlayStatus = PLAY_STATUS_STOPPED;
	m_bIsMissionAudioPlaying = FALSE;
	m_bIsMissionAudioAllowedToPlay = FALSE;
	m_bIsMissionAudio2D = TRUE;
	m_nMissionAudioFramesToPlay = 0;
	ResetAudioLogicTimers(CTimer::GetTimeInMilliseconds());
}

void
cAudioManager::PreTerminateGameSpecificShutdown()
{
	if (m_nBridgeEntity >= 0) {
		DestroyEntity(m_nBridgeEntity);
		m_nBridgeEntity = AEHANDLE_NONE;
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
	gPornNextTime = timer;
	gNextCryTime = timer;
	gSawMillNextTime = timer;
	gCellNextTime = timer;
	gShopNextTime = timer;
	gHomeNextTime = timer;
	gAirportNextTime = timer;
	gDocksNextTime = timer;
	gCinemaNextTime = timer;
	for (uint32 i = 0; i < m_nAudioEntitiesCount; i++) {
		if (m_asAudioEntities[m_aAudioEntityOrderList[i]].m_nType == AUDIOTYPE_PHYSICAL) {
			CPed *ped = (CPed *)m_asAudioEntities[m_aAudioEntityOrderList[i]].m_pEntity;
			if (ped->IsPed()) {
				ped->m_lastSoundStart = timer;
				ped->m_soundStart = timer + m_anRandomTable[0] % 3000;
			}
		}
	}
	ClearMissionAudio();
	SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
}

void
cAudioManager::ProcessReverb()
{
#ifdef EXTERNAL_3D_SOUND
	if (SampleManager.UpdateReverb() && m_bDynamicAcousticModelingStatus) {
#ifndef GTA_PS2
		for (uint32 i = 0; i <
#ifdef FIX_BUGS
		                   NUM_CHANNELS_GENERIC
#else
		                   NUM_CHANNELS_GENERIC+1
#endif
		     ;
		     i++) {
			if (m_asActiveSamples[i].m_bReverb)
				SampleManager.SetChannelReverbFlag(i, TRUE);
		}
#endif
	}
#else
	static uint8 OldVolL = 0;
	static uint8 OldVolR = 0;

	uint8 VolL = Min(40, 3 * (20 - TheCamera.SoundDistLeft)) + 20;
	uint8 VolR = Min(40, 3 * (20 - TheCamera.SoundDistRight)) + 20;

	uint8 VolUp = 5 * (20 - TheCamera.SoundDistUp);

	VolL = Min(MAX_VOLUME, VolL + VolUp);
	VolR = Min(MAX_VOLUME, VolR + VolUp);

	if (OldVolL != VolL || OldVolR != VolR) {
		SampleManager.UpdateReverb(VolL, VolR, 100, 15, 80);
		OldVolL = VolL;
		OldVolR = VolR;
	}
#endif
}

float
cAudioManager::GetDistanceSquared(const CVector &v)
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

void
cAudioManager::ProcessSpecial()
{
	if (m_bIsPaused) {
		if (!m_bWasPaused) {
			MusicManager.ChangeMusicMode(MUSICMODE_FRONTEND);
#ifdef GTA_PS2
			if (SampleManager.IsSampleBankLoaded(SFX_BANK_FRONT_END_MENU) == LOADING_STATUS_NOT_LOADED)
				SampleManager.LoadSampleBank(SFX_BANK_FRONT_END_MENU);
#else
			SampleManager.SetEffectsFadeVolume(MAX_VOLUME);
			SampleManager.SetMusicFadeVolume(MAX_VOLUME);
#endif
		}
#ifdef GTA_PS2
		else {
			int8 isBankLoaded = SampleManager.IsSampleBankLoaded(SFX_BANK_FRONT_END_MENU);
			if (isBankLoaded != -1 && isBankLoaded == LOADING_STATUS_NOT_LOADED) // what a useless -1 check
				SampleManager.LoadSampleBank(SFX_BANK_FRONT_END_MENU);
		}
#endif
	} else {
		if (m_bWasPaused) {
			MusicManager.StopFrontEndTrack();
			MusicManager.ChangeMusicMode(MUSICMODE_GAME);
		}
		CPlayerPed *playerPed = FindPlayerPed();
		if (playerPed) {
			if(!playerPed->EnteringCar() && !playerPed->bInVehicle)
				SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
#ifdef GTA_PS2
			else {
				int8 isBankLoaded = SampleManager.IsSampleBankLoaded(aVehicleSettings[playerPed->m_pMyVehicle->GetModelIndex() - MI_FIRST_VEHICLE].m_nBank);
				if (isBankLoaded != -1 && isBankLoaded == LOADING_STATUS_NOT_LOADED) { // again, useless -1 check
					if (playerPed->m_pMyVehicle->GetType() == ENTITY_TYPE_VEHICLE // no shit, what else could it be?
						&& playerPed->m_pMyVehicle->IsCar())
						SampleManager.LoadSampleBank(aVehicleSettings[playerPed->m_pMyVehicle->GetModelIndex() - MI_FIRST_VEHICLE].m_nBank);
				}
			}
#endif
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
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessPhysical(id);
			}
			break;
		case AUDIOTYPE_EXPLOSION:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessExplosions(id);
			}
			break;
		case AUDIOTYPE_FIRE:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessFires(id);
			}
			break;
		case AUDIOTYPE_WEATHER:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessWeather(id);
			}
			break;
		case AUDIOTYPE_CRANE:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessCrane();
			}
			break;
		case AUDIOTYPE_SCRIPTOBJECT:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessScriptObject(id);
			}
			break;
		case AUDIOTYPE_BRIDGE:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessBridge();
			}
			break;
		case AUDIOTYPE_FRONTEND:
			m_sQueueSample.m_bReverb = FALSE;
			ProcessFrontEnd();
			break;
		case AUDIOTYPE_PROJECTILE:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessProjectiles();
			}
			break;
		case AUDIOTYPE_GARAGE:
			if (!m_bIsPaused)
				ProcessGarages();
			break;
		case AUDIOTYPE_FIREHYDRANT:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessFireHydrant();
			}
			break;
		case AUDIOTYPE_WATERCANNON:
			if (!m_bIsPaused) {
				m_sQueueSample.m_bReverb = TRUE;
				ProcessWaterCannon(id);
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
			ProcessVehicle((CVehicle *)entity);
			break;
		case ENTITY_TYPE_PED:
			ProcessPed(entity);
			break;
		default:
			return;
		}
	}
}

enum
{
	RAIN_ON_VEHICLE_MAX_DIST = 22,
	RAIN_ON_VEHICLE_VOLUME = 30,

	REVERSE_GEAR_MAX_DIST = 30,
	REVERSE_GEAR_VOLUME = 24,

	MODEL_CAR_ENGINE_MAX_DIST = 30,
	MODEL_CAR_ENGINE_VOLUME = 90,

	VEHICLE_ROAD_NOISE_MAX_DIST = 95,
	VEHICLE_ROAD_NOISE_VOLUME = 30,

	WET_ROAD_NOISE_MAX_DIST = 30,
	WET_ROAD_NOISE_VOLUME = 23,

	VEHICLE_ENGINE_MAX_DIST = 50,
	VEHICLE_ENGINE_BASE_VOLUME = 80,
	VEHICLE_ENGINE_FULL_VOLUME = 120,

	CESNA_IDLE_MAX_DIST = 200,
	CESNA_REV_MAX_DIST = 90,
	CESNA_VOLUME = 80,

	PLAYER_VEHICLE_ENGINE_VOLUME = 85,

	VEHICLE_SKIDDING_MAX_DIST = 40,
	VEHICLE_SKIDDING_VOLUME = 50,

	VEHICLE_HORN_MAX_DIST = 40,
	VEHICLE_HORN_VOLUME = 80,

	VEHICLE_SIREN_MAX_DIST = 110,
	VEHICLE_SIREN_VOLUME = 80,

	VEHICLE_REVERSE_WARNING_MAX_DIST = 50,
	VEHICLE_REVERSE_WARNING_VOLUME = 60,

	VEHICLE_DOORS_MAX_DIST = 40,
	VEHICLE_DOORS_VOLUME = 100,

	AIR_BRAKES_MAX_DIST = 30,
	AIR_BRAKES_VOLUME = 70,

	ENGINE_DAMAGE_MAX_DIST = 40,
	ENGINE_DAMAGE_VOLUME = 6,
	ENGINE_DAMAGE_ON_FIRE_VOLUME = 60,

	CAR_BOMB_TICK_MAX_DIST = 40,
	CAR_BOMB_TICK_VOLUME = 60,

	VEHICLE_ONE_SHOT_DOOR_MAX_DIST = 50,
	VEHICLE_ONE_SHOT_DOOR_OPEN_VOLUME = 122,
	VEHICLE_ONE_SHOT_DOOR_CLOSE_VOLUME = 117,

	VEHICLE_ONE_SHOT_WINDSHIELD_CRACK_MAX_DIST = 30,
	VEHICLE_ONE_SHOT_WINDSHIELD_CRACK_VOLUME = 60,

	VEHICLE_ONE_SHOT_CAR_JUMP_MAX_DIST = 35,
	VEHICLE_ONE_SHOT_CAR_JUMP_VOLUME = 80,

	VEHICLE_ONE_SHOT_CAR_ENGINE_START_MAX_DIST = 40,
	VEHICLE_ONE_SHOT_CAR_ENGINE_START_VOLUME = 60,

	VEHICLE_ONE_SHOT_CAR_LIGHT_BREAK_VOLUME = 30,

	VEHICLE_ONE_SHOT_CAR_HYDRAULIC_MAX_DIST = 35,
	VEHICLE_ONE_SHOT_CAR_HYDRAULIC_VOLUME = 55,

	VEHICLE_ONE_SHOT_CAR_SPLASH_MAX_DIST = 40,
	VEHICLE_ONE_SHOT_CAR_SPLASH_VOLUME = 55,

	VEHICLE_ONE_SHOT_BOAT_SLOWDOWN_MAX_DIST = 50,

	VEHICLE_ONE_SHOT_TRAIN_DOOR_MAX_DIST = 35,
	VEHICLE_ONE_SHOT_TRAIN_DOOR_VOLUME = 70,

	VEHICLE_ONE_SHOT_CAR_TANK_TURRET_MAX_DIST = 40,
	VEHICLE_ONE_SHOT_CAR_TANK_TURRET_VOLUME = 90,

	VEHICLE_ONE_SHOT_CAR_BOMB_TICK_MAX_DIST = 30,
	VEHICLE_ONE_SHOT_CAR_BOMB_TICK_VOLUME = CAR_BOMB_TICK_VOLUME,

	VEHICLE_ONE_SHOT_PLANE_ON_GROUND_MAX_DIST = 180,
	VEHICLE_ONE_SHOT_PLANE_ON_GROUND_VOLUME = 75,

	VEHICLE_ONE_SHOT_WEAPON_SHOT_FIRED_MAX_DIST = 120,
	VEHICLE_ONE_SHOT_WEAPON_SHOT_FIRED_VOLUME = 65,

	VEHICLE_ONE_SHOT_WEAPON_HIT_VEHICLE_MAX_DIST = 40,
	VEHICLE_ONE_SHOT_WEAPON_HIT_VEHICLE_VOLUME = 90,

	VEHICLE_ONE_SHOT_BOMB_ARMED_MAX_DIST = 50,
	VEHICLE_ONE_SHOT_BOMB_ARMED_VOLUME = 50,

	VEHICLE_ONE_SHOT_WATER_FALL_MAX_DIST = 40,
	VEHICLE_ONE_SHOT_WATER_FALL_VOLUME = 90,

	VEHICLE_ONE_SHOT_SPLATTER_MAX_DIST = 40,
	VEHICLE_ONE_SHOT_SPLATTER_VOLUME = 55,

	VEHICLE_ONE_SHOT_CAR_PED_COLLISION_MAX_DIST = 40,

	TRAIN_NOISE_FAR_MAX_DIST = 300,
	TRAIN_NOISE_NEAR_MAX_DIST = 70,
	TRAIN_NOISE_VOLUME = 75,

	BOAT_ENGINE_MAX_DIST = 50,
	BOAT_ENGINE_REEFER_IDLE_VOLUME = 50,
	BOAT_ENGINE_REEFER_ACCEL_MIN_VOLUME = 15,
	BOAT_ENGINE_REEFER_ACCEL_VOLUME_MULT = 100,

	BOAT_ENGINE_LOW_ACCEL_VOLUME = 45,
	BOAT_ENGINE_HIGH_ACCEL_MIN_VOLUME = 15,
	BOAT_ENGINE_HIGH_ACCEL_VOLUME_MULT = 105,

	BOAT_MOVING_OVER_WATER_MAX_DIST = 50,
	BOAT_MOVING_OVER_WATER_VOLUME = 30,

	JUMBO_MAX_DIST = 440,
	JUMBO_RUMBLE_SOUND_MAX_DIST = 240,
	JUMBO_ENGINE_SOUND_MAX_DIST = 180,
	JUMBO_WHINE_SOUND_MAX_DIST = 170,

	PED_HEADPHONES_MAX_DIST = 7,
	PED_HEADPHONES_VOLUME = 42,
	PED_HEADPHONES_IN_CAR_VOLUME = 10,

	PED_ONE_SHOT_STEP_MAX_DIST = 20,
	PED_ONE_SHOT_STEP_VOLUME = 45,

	PED_ONE_SHOT_FALL_MAX_DIST = 30,
	PED_ONE_SHOT_FALL_VOLUME = 80,

	PED_ONE_SHOT_PUNCH_MAX_DIST = 30,
	PED_ONE_SHOT_PUNCH_VOLUME = 100,

	PED_ONE_SHOT_WEAPON_COLT45_MAX_DIST = 50,
	PED_ONE_SHOT_WEAPON_COLT45_VOLUME = 90,

	PED_ONE_SHOT_WEAPON_UZI_MAX_DIST = 80,
	PED_ONE_SHOT_WEAPON_UZI_VOLUME = 70,

	PED_ONE_SHOT_WEAPON_SHOTGUN_MAX_DIST = 60,
	PED_ONE_SHOT_WEAPON_SHOTGUN_VOLUME = 100,

	PED_ONE_SHOT_WEAPON_AK47_MAX_DIST = 80,
	PED_ONE_SHOT_WEAPON_AK47_VOLUME = 70,

	PED_ONE_SHOT_WEAPON_M16_MAX_DIST = 80,
	PED_ONE_SHOT_WEAPON_M16_VOLUME = 70,

	PED_ONE_SHOT_WEAPON_SNIPERRIFLE_MAX_DIST = 60,
	PED_ONE_SHOT_WEAPON_SNIPERRIFLE_VOLUME = 110,

	PED_ONE_SHOT_WEAPON_ROCKETLAUNCHER_MAX_DIST = 90,
	PED_ONE_SHOT_WEAPON_ROCKETLAUNCHER_VOLUME = 80,

	PED_ONE_SHOT_WEAPON_FLAMETHROWER_MAX_DIST = 60,
	PED_ONE_SHOT_WEAPON_FLAMETHROWER_VOLUME = 90,

	PED_ONE_SHOT_WEAPON_RELOAD_MAX_DIST = 30,
	PED_ONE_SHOT_WEAPON_RELOAD_VOLUME = 75,

	PED_ONE_SHOT_WEAPON_BULLET_ECHO_MAX_DIST = 80,
	PED_ONE_SHOT_WEAPON_BULLET_ECHO_VOLUME = 40,

	PED_ONE_SHOT_WEAPON_FLAMETHROWER_FIRE_MAX_DIST = 60,
	PED_ONE_SHOT_WEAPON_FLAMETHROWER_FIRE_VOLUME = 70,

	PED_ONE_SHOT_WEAPON_HIT_PED_MAX_DIST = 30,
	PED_ONE_SHOT_WEAPON_HIT_PED_VOLUME = 90,

	PED_ONE_SHOT_SPLASH_MAX_DIST = 40,
	PED_ONE_SHOT_SPLASH_PED_VOLUME = 70,

	PED_COMMENT_MAX_DIST = 50,
	PED_COMMENT_POLICE_HELI_MAX_DIST = 400,

	EXPLOSION_DEFAULT_MAX_DIST = 400,
	EXPLOSION_MOLOTOV_MAX_DIST = 200,
	EXPLOSION_MINE_MAX_DIST = 300,

	FIRE_DEFAULT_MAX_DIST = 50,
	FIRE_DEFAULT_VOLUME = 80,
	FIRE_BUILDING_MAX_DIST = 50,
	FIRE_BUILDING_VOLUME = 100,
	FIRE_PED_MAX_DIST = 25,
	FIRE_PED_VOLUME = 60,

	WATER_CANNON_MAX_DIST = 30,
	WATER_CANNON_VOLUME = 50,

	SCRIPT_OBJECT_GATE_MAX_DIST = 40,

	SCRIPT_OBJECT_BULLET_HIT_GROUND_MAX_DIST = 50,
	SCRIPT_OBJECT_BULLET_HIT_GROUND_VOLUME = 90,

	SCRIPT_OBJECT_TRAIN_ANNOUNCEMENT_MAX_DIST = 80,
	SCRIPT_OBJECT_TRAIN_ANNOUNCEMENT_VOLUME = MAX_VOLUME,

	SCRIPT_OBJECT_PAYPHONE_RINGING_MAX_DIST = 80,
	SCRIPT_OBJECT_PAYPHONE_RINGING_VOLUME = 80,

	SCRIPT_OBJECT_GLASS_BREAK_MAX_DIST = 60,
	SCRIPT_OBJECT_GLASS_BREAK_LONG_VOLUME = 70,
	SCRIPT_OBJECT_GLASS_BREAK_SHORT_VOLUME = 60,

	SCRIPT_OBJECT_GLASS_LIGHT_BREAK_MAX_DIST = 55,
	SCRIPT_OBJECT_GLASS_LIGHT_BREAK_VOLUME = 25,

	SCRIPT_OBJECT_BOX_DESTROYED_MAX_DIST = 60,
	SCRIPT_OBJECT_BOX_DESTROYED_VOLUME = 80,

	SCRIPT_OBJECT_METAL_COLLISION_VOLUME = 70,
	SCRIPT_OBJECT_TIRE_COLLISION_VOLUME = 60,

	SCRIPT_OBJECT_GUNSHELL_MAX_DIST = 20,
	SCRIPT_OBJECT_GUNSHELL_VOLUME = 30,

	SCRIPT_OBJECT_SHORT_MAX_DIST = 30,
	SCRIPT_OBJECT_LONG_MAX_DIST = 80,
	SCRIPT_OBJECT_DEFAULT_VOLUME = MAX_VOLUME,
	SCRIPT_OBJECT_RESAURANT_VOLUME = 110,
	SCRIPT_OBJECT_BANK_ALARM_VOLUME = 90,

	PORN_CINEMA_SHORT_MAX_DIST = 20,
	PORN_CINEMA_LONG_MAX_DIST = SCRIPT_OBJECT_LONG_MAX_DIST,
	PORN_CINEMA_VOLUME = SCRIPT_OBJECT_DEFAULT_VOLUME,
	PORN_CINEMA_MOAN_VOLUME = 90,
		
	WORK_SHOP_MAX_DIST = 20,
	WORK_SHOP_VOLUME = 30,

	SAWMILL_VOLUME = 30,
	SAWMILL_CUT_WOOD_VOLUME = 70,

	LAUNDERETTE_VOLUME = 45,
	LAUNDERETTE_SONG_VOLUME = 110,

	SHOP_VOLUME = 30,
	SHOP_TILL_VOLUME = 70,

	AIRPORT_VOLUME = 110,

	CINEMA_VOLUME = 30,
	DOCKS_VOLUME = 40,
	HOME_VOLUME = 40,
	POLICE_CELL_BEATING_VOLUME = 55,

	FRONTEND_VOLUME = 110,

	CRANE_MAX_DIST = 80,
	CRANE_VOLUME = 100,

	PROJECTILE_ROCKET_MAX_DIST = 90,
	PROJECTILE_ROCKET_VOLUME = MAX_VOLUME,

	PROJECTILE_MOLOTOV_MAX_DIST = 30,
	PROJECTILE_MOLOTOV_VOLUME = 50,

	GARAGES_MAX_DIST = 80,
	GARAGES_VOLUME = 90,
	GARAGES_DOOR_VOLUME = 60,

	FIRE_HYDRANT_MAX_DIST = 35,
	FIRE_HYDRANT_VOLUME = 40,

	BRIDGE_MOTOR_MAX_DIST = 400,
	BRIDGE_MOTOR_VOLUME = MAX_VOLUME,
	BRIDGE_MAX_DIST = BRIDGE_MOTOR_MAX_DIST + 50,

	BRIDGE_WARNING_VOLUME = 100,

	MISSION_AUDIO_MAX_DIST = 50,
#ifdef GTA_PS2
	MISSION_AUDIO_VOLUME = MAX_VOLUME,
#else
	MISSION_AUDIO_VOLUME = 80,
#endif
};

#pragma region VEHICLE AUDIO
bool8 bPlayerJustEnteredCar;

Const static bool8 HornPattern[8][44] = {
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

void
cAudioManager::ProcessVehicle(CVehicle *veh)
{
	cVehicleParams params;

	m_sQueueSample.m_vecPos = veh->GetPosition();
	params.m_bDistanceCalculated = FALSE;
	params.m_pVehicle = veh;
	params.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
	params.m_pTransmission = veh->pHandling != nil ? &veh->pHandling->Transmission : nil;
	params.m_nIndex = veh->GetModelIndex() - MI_FIRST_VEHICLE;
	if (params.m_pVehicle->GetStatus() == STATUS_SIMPLE)
		params.m_fVelocityChange = params.m_pVehicle->AutoPilot.m_fMaxTrafficSpeed * 0.02f;
	else
		params.m_fVelocityChange = DotProduct(params.m_pVehicle->m_vecMoveSpeed, params.m_pVehicle->GetForward());
	switch (params.m_pVehicle->m_vehType) {
	case VEHICLE_TYPE_CAR:
		UpdateGasPedalAudio((CAutomobile *)veh);
		if (params.m_nIndex == RCBANDIT) {
			ProcessModelCarEngine(params);
			ProcessVehicleOneShots(params);
			((CAutomobile *)veh)->m_fVelocityChangeForAudio = params.m_fVelocityChange;
			break;
		}
		if (params.m_nIndex == DODO) {
			if (!ProcessVehicleRoadNoise(params)) {
				ProcessVehicleOneShots(params);
				((CAutomobile *)veh)->m_fVelocityChangeForAudio = params.m_fVelocityChange;
				break;
			}
			if (CWeather::WetRoads > 0.0f)
				ProcessWetRoadNoise(params);
			ProcessVehicleSkidding(params);
		} else {
			if (!ProcessVehicleRoadNoise(params)) {
				ProcessVehicleOneShots(params);
				((CAutomobile *)veh)->m_fVelocityChangeForAudio = params.m_fVelocityChange;
				break;
			}
			ProcessReverseGear(params);
			if (CWeather::WetRoads > 0.0f)
				ProcessWetRoadNoise(params);
			ProcessVehicleSkidding(params);
			ProcessVehicleHorn(params);
			ProcessVehicleSirenOrAlarm(params);
			if (UsesReverseWarning(params.m_nIndex))
				ProcessVehicleReverseWarning(params);
			if (HasAirBrakes(params.m_nIndex))
				ProcessAirBrakes(params);
		}
		ProcessCarBombTick(params);
		ProcessVehicleEngine(params);
		ProcessEngineDamage(params);
		ProcessVehicleDoors(params);

		ProcessVehicleOneShots(params);
		((CAutomobile *)veh)->m_fVelocityChangeForAudio = params.m_fVelocityChange;
		break;
	case VEHICLE_TYPE_BOAT:
		ProcessBoatEngine(params);
		ProcessBoatMovingOverWater(params);
		ProcessVehicleOneShots(params);
		break;
	case VEHICLE_TYPE_TRAIN:
		ProcessTrainNoise(params);
		ProcessVehicleOneShots(params);
		break;
	case VEHICLE_TYPE_HELI:
		ProcessHelicopter(params);
		ProcessVehicleOneShots(params);
		break;
	case VEHICLE_TYPE_PLANE:
		ProcessPlane(params);
		ProcessVehicleOneShots(params);
		break;
	default:
		break;
	}
	ProcessRainOnVehicle(params);
}

void
cAudioManager::ProcessRainOnVehicle(cVehicleParams& params)
{
	if (params.m_fDistance < SQR(RAIN_ON_VEHICLE_MAX_DIST) && CWeather::Rain > 0.01f && (!CCullZones::CamNoRain() || !CCullZones::PlayerNoRain())) {
		CVehicle *veh = params.m_pVehicle;
		veh->m_bRainAudioCounter++;
		if (veh->m_bRainAudioCounter >= 2) {
			veh->m_bRainAudioCounter = 0;
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			uint8 Vol = RAIN_ON_VEHICLE_VOLUME * CWeather::Rain;
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, RAIN_ON_VEHICLE_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = veh->m_bRainSamplesCounter++;
				if (veh->m_bRainSamplesCounter > 4)
					veh->m_bRainSamplesCounter = 68;
				m_sQueueSample.m_nSampleIndex = (m_anRandomTable[1] & 3) + SFX_CAR_RAIN_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 9;
				m_sQueueSample.m_nFrequency = m_anRandomTable[1] % 4000 + 28000;
				m_sQueueSample.m_nLoopCount = 1;
				SET_EMITTING_VOLUME(Vol);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = RAIN_ON_VEHICLE_MAX_DIST;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_bReverb = FALSE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
	}
}

bool8
cAudioManager::ProcessReverseGear(cVehicleParams& params)
{
	CVehicle *veh;
	CAutomobile *automobile;
	uint8 Vol;
	float modificator;

	if (params.m_fDistance < SQR(REVERSE_GEAR_MAX_DIST)) {
		veh = params.m_pVehicle;
		if (veh->bEngineOn && (veh->m_fGasPedal < 0.0f || veh->m_nCurrentGear == 0)) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			automobile = (CAutomobile *)params.m_pVehicle;
			if (automobile->m_nWheelsOnGround > 0)
				modificator = params.m_fVelocityChange / params.m_pTransmission->fMaxReverseVelocity;
			else {
				if (automobile->m_nDriveWheelsOnGround > 0)
					automobile->m_fGasPedalAudio *= 0.4f;
				modificator = automobile->m_fGasPedalAudio;
			}
			modificator = ABS(modificator);
			Vol = (REVERSE_GEAR_VOLUME * modificator);
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, REVERSE_GEAR_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				if (params.m_pVehicle->m_fGasPedal < 0.0f) {
					m_sQueueSample.m_nCounter = 61;
					m_sQueueSample.m_nSampleIndex = SFX_REVERSE_GEAR;
				} else {
					m_sQueueSample.m_nCounter = 62;
					m_sQueueSample.m_nSampleIndex = SFX_REVERSE_GEAR_2;
				}
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_nFrequency = (6000 * modificator) + 7000;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(Vol);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				m_sQueueSample.m_MaxDistance = REVERSE_GEAR_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 5;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

void
cAudioManager::ProcessModelCarEngine(cVehicleParams& params)
{
	CAutomobile *automobile;
	float allowedVelocity;
	uint8 Vol;
	float velocityChange;

	if (params.m_fDistance < SQR(MODEL_CAR_ENGINE_MAX_DIST)) {
		automobile = (CAutomobile *)params.m_pVehicle;
		if (automobile->bEngineOn) {
			if (automobile->m_nWheelsOnGround > 0)
				velocityChange = Abs(params.m_fVelocityChange);
			else {
				if (automobile->m_nDriveWheelsOnGround > 0)
					automobile->m_fGasPedalAudio *= 0.4f;
				velocityChange = automobile->m_fGasPedalAudio * params.m_pTransmission->fMaxVelocity;
			}
			if (velocityChange > 0.001f) {
				allowedVelocity = 0.5f * params.m_pTransmission->fMaxVelocity;
				if (velocityChange < allowedVelocity)
					Vol = (MODEL_CAR_ENGINE_VOLUME * velocityChange / allowedVelocity);
				else
					Vol = MODEL_CAR_ENGINE_VOLUME;
				if (Vol > 0) {
					CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
					m_sQueueSample.m_nVolume = ComputeVolume(Vol, MODEL_CAR_ENGINE_MAX_DIST, m_sQueueSample.m_fDistance);
					if (m_sQueueSample.m_nVolume > 0) {
						m_sQueueSample.m_nCounter = 2;
						m_sQueueSample.m_nSampleIndex = SFX_REMOTE_CONTROLLED_CAR;
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						m_sQueueSample.m_bIs2D = FALSE;
						m_sQueueSample.m_nPriority = 1;
						m_sQueueSample.m_nFrequency = (11025 * velocityChange / params.m_pTransmission->fMaxVelocity + 11025);
						m_sQueueSample.m_nLoopCount = 0;
						SET_EMITTING_VOLUME(Vol);
						SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
						m_sQueueSample.m_fSpeedMultiplier = 3.0f;
						m_sQueueSample.m_MaxDistance = MODEL_CAR_ENGINE_MAX_DIST;
						m_sQueueSample.m_bStatic = FALSE;
						m_sQueueSample.m_nFramesToPlay = 3;
						m_sQueueSample.m_bReverb = TRUE;
						SET_SOUND_REFLECTION(FALSE);
						AddSampleToRequestedQueue();
					}
				}
			}
		}
	}
}

bool8
cAudioManager::ProcessVehicleRoadNoise(cVehicleParams& params)
{
	uint8 Vol;
	uint32 freq;
	float multiplier;
	int sampleFreq;
	float velocity;

	if (params.m_fDistance < SQR(VEHICLE_ROAD_NOISE_MAX_DIST)) {
		if ((params.m_pTransmission != nil) && (((CAutomobile*)params.m_pVehicle)->m_nDriveWheelsOnGround > 0)) {
			velocity = Abs(params.m_fVelocityChange);
			if (velocity > 0.0f) {
				CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
				Vol = VEHICLE_ROAD_NOISE_VOLUME * Min(1.0f, velocity / (0.5f * params.m_pTransmission->fMaxVelocity));
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, VEHICLE_ROAD_NOISE_MAX_DIST, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = 0;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nPriority = 3;
					if (params.m_pVehicle->m_nSurfaceTouched == SURFACE_WATER) {
						m_sQueueSample.m_nSampleIndex = SFX_BOAT_WATER_LOOP;
						freq = 6050 * Vol / VEHICLE_ROAD_NOISE_VOLUME + 16000;
					} else {
						m_sQueueSample.m_nSampleIndex = SFX_ROAD_NOISE;
						multiplier = (m_sQueueSample.m_fDistance / VEHICLE_ROAD_NOISE_MAX_DIST) * 0.5f;
						sampleFreq = SampleManager.GetSampleBaseFrequency(SFX_ROAD_NOISE);
						freq = (sampleFreq * multiplier) + ((3 * sampleFreq) >> 2);
					}
					m_sQueueSample.m_nFrequency = freq;
					m_sQueueSample.m_nLoopCount = 0;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 6.0f;
					m_sQueueSample.m_MaxDistance = VEHICLE_ROAD_NOISE_MAX_DIST;
					m_sQueueSample.m_bStatic = FALSE;
					m_sQueueSample.m_nFramesToPlay = 4;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessWetRoadNoise(cVehicleParams& params)
{
	float relativeVelocity;
	uint8 Vol;
	float multiplier;
	int freq;
	float velChange;

	if (params.m_fDistance < SQR(WET_ROAD_NOISE_MAX_DIST)) {
		if ((params.m_pTransmission != nil) && (((CAutomobile*)params.m_pVehicle)->m_nDriveWheelsOnGround > 0)) {
			velChange = Abs(params.m_fVelocityChange);
			if (velChange > 0.0f) {
				CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
				relativeVelocity = Min(1.0f, velChange / (0.5f * params.m_pTransmission->fMaxVelocity));
				Vol = WET_ROAD_NOISE_VOLUME * relativeVelocity * CWeather::WetRoads;
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, WET_ROAD_NOISE_MAX_DIST, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = 1;
					m_sQueueSample.m_nSampleIndex = SFX_ROAD_NOISE;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nPriority = 3;
					multiplier = (m_sQueueSample.m_fDistance / WET_ROAD_NOISE_MAX_DIST) * 0.5f;
					freq = SampleManager.GetSampleBaseFrequency(SFX_ROAD_NOISE);
					m_sQueueSample.m_nFrequency = freq + freq * multiplier;
					m_sQueueSample.m_nLoopCount = 0;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 6.0f;
					m_sQueueSample.m_MaxDistance = WET_ROAD_NOISE_MAX_DIST;
					m_sQueueSample.m_bStatic = FALSE;
					m_sQueueSample.m_nFramesToPlay = 4;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessVehicleEngine(cVehicleParams& params)
{
	CAutomobile *automobile;
	float relativeGearChange;
#ifdef FIX_BUGS
	uint32 freq = 0; // uninitialized variable
#else
	uint32 freq;
#endif
	uint8 Vol;
	cTransmission *transmission;
	uint8 currentGear;
	float modificator;
	float traction = 0.0f;

	if (params.m_fDistance < SQR(VEHICLE_ENGINE_MAX_DIST)) {
		if (FindPlayerVehicle() == params.m_pVehicle && params.m_pVehicle->GetStatus() == STATUS_WRECKED) {
			SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
			return TRUE;
		}
		if (params.m_pVehicle->bEngineOn) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			automobile = (CAutomobile *)params.m_pVehicle;
			if (params.m_nIndex == DODO)
				ProcessCesna(params);
			else if (FindPlayerVehicle() == automobile)
				ProcessPlayersVehicleEngine(params, automobile);
			else {
				transmission = params.m_pTransmission;
				if (transmission != nil) {
					currentGear = params.m_pVehicle->m_nCurrentGear;
					if (automobile->m_nWheelsOnGround > 0) {
						if (automobile->bIsHandbrakeOn) {
							if (params.m_fVelocityChange == 0.0f)
								traction = 0.9f;
						} else if (params.m_pVehicle->GetStatus() == STATUS_SIMPLE) {
							traction = 0.0f;
						} else {
							switch (transmission->nDriveType) {
							case '4':
								for (uint8 i = 0; i < ARRAY_SIZE(automobile->m_aWheelState); i++) {
									if (automobile->m_aWheelState[i] == WHEEL_STATE_SPINNING)
										traction += 0.05f;
								}
								break;
							case 'F':
								if (automobile->m_aWheelState[CARWHEEL_FRONT_LEFT] == WHEEL_STATE_SPINNING)
									traction += 0.1f;
								if (automobile->m_aWheelState[CARWHEEL_FRONT_RIGHT] == WHEEL_STATE_SPINNING)
									traction += 0.1f;
								break;
							case 'R':
								if (automobile->m_aWheelState[CARWHEEL_REAR_LEFT] == WHEEL_STATE_SPINNING)
									traction += 0.1f;
								if (automobile->m_aWheelState[CARWHEEL_REAR_RIGHT] == WHEEL_STATE_SPINNING)
									traction += 0.1f;
								break;
							default:
								break;
							}
						}
						if (transmission->fMaxVelocity > 0.0f) {
							if (currentGear > 0) {
								relativeGearChange =
									Min(1.0f, (params.m_fVelocityChange - transmission->Gears[currentGear].fShiftDownVelocity) / transmission->fMaxVelocity * 2.5f);
								if (traction == 0.0f && automobile->GetStatus() != STATUS_SIMPLE &&
									params.m_fVelocityChange < transmission->Gears[1].fShiftUpVelocity) {
									traction = 0.7f;
								}
								modificator = traction * automobile->m_fGasPedalAudio * 0.95f + (1.0f - traction) * relativeGearChange;
							} else
								modificator =
									Min(1.0f, 1.0f - Abs((params.m_fVelocityChange - transmission->Gears[0].fShiftDownVelocity) / transmission->fMaxReverseVelocity));
						}
						else
							modificator = 0.0f;
					} else {
						if (automobile->m_nDriveWheelsOnGround > 0)
							automobile->m_fGasPedalAudio *= 0.4f;
						modificator = automobile->m_fGasPedalAudio;
					}
					if (currentGear == 0 && automobile->m_nWheelsOnGround > 0)
						freq = 13000 * modificator + 14000;
					else
						freq = 1200 * currentGear + 18000 * modificator + 14000;
					if (modificator < 0.75f)
						Vol = modificator / 0.75f * (VEHICLE_ENGINE_FULL_VOLUME-VEHICLE_ENGINE_BASE_VOLUME) + VEHICLE_ENGINE_BASE_VOLUME;
					else
						Vol = VEHICLE_ENGINE_FULL_VOLUME;
				} else {
					modificator = 0.0f;
					Vol = VEHICLE_ENGINE_BASE_VOLUME;
				}
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, VEHICLE_ENGINE_MAX_DIST, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					if (automobile->GetStatus() == STATUS_SIMPLE) {
						if (modificator < 0.02f) {
							m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nBank - CAR_SFX_BANKS_OFFSET + SFX_CAR_IDLE_1;
							freq = modificator * 10000 + 22050;
							m_sQueueSample.m_nCounter = 52;
						} else {
							m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nAccelerationSampleIndex;
							m_sQueueSample.m_nCounter = 2;
						}
					} else {
						if (automobile->m_fGasPedal < 0.05f) {
							m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nBank - CAR_SFX_BANKS_OFFSET + SFX_CAR_IDLE_1;
							freq = modificator * 10000 + 22050;
							m_sQueueSample.m_nCounter = 52;
						} else {
							m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nAccelerationSampleIndex;
							m_sQueueSample.m_nCounter = 2;
						}
					}
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nPriority = 3;
					m_sQueueSample.m_nFrequency = freq + 100 * m_sQueueSample.m_nEntityIndex % 1000;
					if (m_sQueueSample.m_nSampleIndex == SFX_CAR_IDLE_6 || m_sQueueSample.m_nSampleIndex == SFX_CAR_REV_6)
						m_sQueueSample.m_nFrequency >>= 1;
					m_sQueueSample.m_nLoopCount = 0;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 6.0f;
					m_sQueueSample.m_MaxDistance = VEHICLE_ENGINE_MAX_DIST;
					m_sQueueSample.m_bStatic = FALSE;
					m_sQueueSample.m_nFramesToPlay = 8;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

void
cAudioManager::UpdateGasPedalAudio(CAutomobile *automobile)
{
	float gasPedal = Abs(automobile->m_fGasPedal);
	float gasPedalAudio = automobile->m_fGasPedalAudio;

	if (gasPedalAudio < gasPedal)
		automobile->m_fGasPedalAudio = Min(gasPedalAudio + 0.09f, gasPedal);
	else
		automobile->m_fGasPedalAudio = Max(gasPedalAudio - 0.07f, gasPedal);
}

void
cAudioManager::PlayerJustGotInCar()
{
	if (m_bIsInitialised)
		bPlayerJustEnteredCar = TRUE;
}

void
cAudioManager::PlayerJustLeftCar(void)
{
	// UNUSED: This is a perfectly empty function.
}

void
cAudioManager::AddPlayerCarSample(uint8 Vol, uint32 freq, uint32 sample, uint8 bank, uint8 counter, bool8 bLooping)
{
	m_sQueueSample.m_nVolume = ComputeVolume(Vol, VEHICLE_ENGINE_MAX_DIST, m_sQueueSample.m_fDistance);
	if (m_sQueueSample.m_nVolume > 0) {
		m_sQueueSample.m_nCounter = counter;
		m_sQueueSample.m_nSampleIndex = sample;
#ifdef GTA_PS2
		m_sQueueSample.m_nBankIndex = bank;
#else
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#endif // GTA_PS2
		m_sQueueSample.m_bIs2D = FALSE;
		m_sQueueSample.m_nPriority = 0;
		m_sQueueSample.m_nFrequency = freq;
		if (bLooping) {
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nFramesToPlay = 8;
		} else
			m_sQueueSample.m_nLoopCount = 1;
		SET_EMITTING_VOLUME(Vol);
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		m_sQueueSample.m_fSpeedMultiplier = 6.0f;
		m_sQueueSample.m_MaxDistance = VEHICLE_ENGINE_MAX_DIST;
		m_sQueueSample.m_bStatic = FALSE;
		m_sQueueSample.m_bReverb = TRUE;
		SET_SOUND_REFLECTION(FALSE);
		AddSampleToRequestedQueue();
	}
}

void
cAudioManager::ProcessCesna(cVehicleParams& params)
{
	static uint8 nAccel = 0;

#ifdef THIS_IS_STUPID
	((CAutomobile *)params.m_pVehicle)->Damage.GetEngineStatus();
#endif

	if (FindPlayerVehicle() == params.m_pVehicle) {
		if (params.m_nIndex == DODO) {
			if (Pads[0].GetAccelerate() > 0) {
				if (nAccel < 60)
					nAccel++;
			} else
				if (nAccel > 0)
					nAccel--;
			AddPlayerCarSample(PLAYER_VEHICLE_ENGINE_VOLUME * (60 - nAccel) / 60 + 20, 8500 * nAccel / 60 + 17000, SFX_CESNA_IDLE, SFX_BANK_0, 52, TRUE);
			AddPlayerCarSample(PLAYER_VEHICLE_ENGINE_VOLUME * nAccel / 60 + 20, 8500 * nAccel / 60 + 17000, SFX_CESNA_REV, SFX_BANK_0, 2, TRUE);
		}
	} else if (params.m_nIndex == DODO) {
		AddPlayerCarSample(PLAYER_VEHICLE_ENGINE_VOLUME + 20, 17000, SFX_CESNA_IDLE, SFX_BANK_0, 52, TRUE);
	} else if (params.m_fDistance < SQR(CESNA_IDLE_MAX_DIST)) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		m_sQueueSample.m_nVolume = ComputeVolume(CESNA_VOLUME, CESNA_IDLE_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 52;
			m_sQueueSample.m_nSampleIndex = SFX_CESNA_IDLE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 0;
			m_sQueueSample.m_nFrequency = 12500;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_nFramesToPlay = 8;
			SET_EMITTING_VOLUME(CESNA_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 8.0f;
			m_sQueueSample.m_MaxDistance = CESNA_IDLE_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		if (params.m_fDistance < SQR(CESNA_REV_MAX_DIST)) {
			m_sQueueSample.m_nVolume = ComputeVolume(CESNA_VOLUME, CESNA_REV_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 2;
				m_sQueueSample.m_nSampleIndex = SFX_CESNA_REV;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 0;
				m_sQueueSample.m_nFrequency = 25000;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_nFramesToPlay = 4;
				SET_EMITTING_VOLUME(CESNA_VOLUME);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 8.0f;
				m_sQueueSample.m_MaxDistance = CESNA_REV_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
	}
}

void
cAudioManager::ProcessPlayersVehicleEngine(cVehicleParams& params, CAutomobile *automobile)
{
	static int32 GearFreqAdj[] = {6000, 6000, 3400, 1200, 0, -1000};

	cTransmission *transmission;
	float relativeVelocityChange;
	float accelerationMultipler;
	uint8 wheelInUseCounter;
	float time;
	int baseFreq;
	uint8 vol;
	int32 freq;

	int freqModifier;
	uint32 soundOffset;
	uint8 engineSoundType;
	int16 accelerateState;
	bool8 channelUsed;
	uint8 currentGear;
	float gasPedalAudio;
	CVector pos;
	bool8 slowingDown;

	static int16 LastAccel = 0;
	static int16 LastBrake = 0;
	static uint8 CurrentPretendGear = 1;
	static bool8 bLostTractionLastFrame = FALSE;
	static bool8 bHandbrakeOnLastFrame = FALSE;
	static uint32 nCruising = 0;
	static bool8 bAccelSampleStopped = TRUE;

	bool8 lostTraction = FALSE;
	bool8 processedAccelSampleStopped = FALSE;
	if (bPlayerJustEnteredCar) {
		bAccelSampleStopped = TRUE;
		bPlayerJustEnteredCar = FALSE;
		nCruising = 0;
		LastAccel = 0;
		bLostTractionLastFrame = FALSE;
		LastBrake = 0;
		bHandbrakeOnLastFrame = FALSE;
		CurrentPretendGear = 1;
	}
#ifdef FIX_BUGS // fix acceleration sound on exiting the vehicle
	if (CReplay::IsPlayingBack() || FindPlayerPed()->GetPedState() == PED_EXIT_CAR)
#else
	if (CReplay::IsPlayingBack())
#endif
		accelerateState = 255 * Clamp(automobile->m_fGasPedal, 0.0f, 1.0f);
	else
		accelerateState = Pads[0].GetAccelerate();

	slowingDown = params.m_fVelocityChange < -0.001f;
	channelUsed = SampleManager.GetChannelUsedFlag(CHANNEL_PLAYER_VEHICLE_ENGINE);
	transmission = params.m_pTransmission;
	relativeVelocityChange = 2.0f * params.m_fVelocityChange / transmission->fMaxVelocity;

	accelerationMultipler = Clamp(relativeVelocityChange, 0.0f, 1.0f);
	gasPedalAudio = accelerationMultipler;
	currentGear = params.m_pVehicle->m_nCurrentGear;

	switch (transmission->nDriveType)
	{
	case '4':
		wheelInUseCounter = 0;
		for (uint8 i = 0; i < ARRAY_SIZE(automobile->m_aWheelState); i++) {
			if (automobile->m_aWheelState[i] != WHEEL_STATE_NORMAL)
				wheelInUseCounter++;
		}
		if (wheelInUseCounter > 2)
			lostTraction = TRUE;
		break;
	case 'F':
		if ((automobile->m_aWheelState[CARWHEEL_FRONT_LEFT] != WHEEL_STATE_NORMAL || automobile->m_aWheelState[CARWHEEL_FRONT_RIGHT] != WHEEL_STATE_NORMAL) &&
		    (automobile->m_aWheelState[CARWHEEL_REAR_LEFT] != WHEEL_STATE_NORMAL || automobile->m_aWheelState[CARWHEEL_REAR_RIGHT] != WHEEL_STATE_NORMAL))
			lostTraction = TRUE;
		break;
	case 'R':
		if ((automobile->m_aWheelState[CARWHEEL_REAR_LEFT] != WHEEL_STATE_NORMAL) || (automobile->m_aWheelState[CARWHEEL_REAR_RIGHT] != WHEEL_STATE_NORMAL))
			lostTraction = TRUE;
		break;
	default:
		break;
	}

	if (params.m_fVelocityChange != 0.0f) {
		time = params.m_pVehicle->m_vecMoveSpeed.z / params.m_fVelocityChange;
		if (time > 0.0f)
			freqModifier = -(Min(0.2f, time) * 3000 * 5);
		else
			freqModifier = -(Max(-0.2f, time) * 3000 * 5);
		if (slowingDown)
			freqModifier = -freqModifier;
	} else
		freqModifier = 0;

	engineSoundType = aVehicleSettings[params.m_nIndex].m_nBank;
	soundOffset = 3 * (engineSoundType - CAR_SFX_BANKS_OFFSET);
	if (accelerateState > 0) {
		if (nCruising > 0) {
PlayCruising:
			bAccelSampleStopped = TRUE;
			if (accelerateState < 150 || automobile->m_nWheelsOnGround == 0 || automobile->bIsHandbrakeOn || lostTraction ||
				currentGear < params.m_pTransmission->nNumberOfGears - 1) {
				nCruising = 0;
			} else {
				if (accelerateState < 220 || params.m_fVelocityChange + 0.001f < automobile->m_fVelocityChangeForAudio) {
					if (nCruising > 3)
						nCruising--;
				} else
					if (nCruising < 800)
						nCruising++;
				freq = 27 * nCruising + freqModifier + 22050;
				if (engineSoundType == SFX_BANK_TRUCK)
					freq >>= 1;
				AddPlayerCarSample(PLAYER_VEHICLE_ENGINE_VOLUME, freq, (soundOffset + SFX_CAR_AFTER_ACCEL_1), engineSoundType, 64, TRUE);
			}
		} else {
			if (accelerateState < 150 || automobile->m_nWheelsOnGround == 0 || automobile->bIsHandbrakeOn || lostTraction ||
				currentGear < 2 && params.m_fVelocityChange - automobile->m_fVelocityChangeForAudio < 0.01f) { // here could be used abs
				if (automobile->m_nWheelsOnGround == 0 || automobile->bIsHandbrakeOn || lostTraction) {
					if (automobile->m_nWheelsOnGround == 0 && automobile->m_nDriveWheelsOnGround > 0 ||
						(automobile->bIsHandbrakeOn && !bHandbrakeOnLastFrame || lostTraction && !bLostTractionLastFrame) && automobile->m_nWheelsOnGround > 0)
						automobile->m_fGasPedalAudio *= 0.6f;
					freqModifier = 0;
					baseFreq = (15000 * automobile->m_fGasPedalAudio) + 14000;
					vol = (25 * automobile->m_fGasPedalAudio) + 60;
				} else {
					baseFreq = (8000 * accelerationMultipler) + 16000;
					vol = (25 * accelerationMultipler) + 60;
					automobile->m_fGasPedalAudio = accelerationMultipler;
				}
				freq = freqModifier + baseFreq;
				if (engineSoundType == SFX_BANK_TRUCK)
					freq >>= 1;
				if (channelUsed) {
					SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
					bAccelSampleStopped = TRUE;
				}
				AddPlayerCarSample(vol, freq, (engineSoundType - CAR_SFX_BANKS_OFFSET + SFX_CAR_REV_1), SFX_BANK_0, 2, TRUE);
			} else {
				TranslateEntity(&m_sQueueSample.m_vecPos, &pos);
#ifndef EXTERNAL_3D_SOUND
				m_sQueueSample.m_nPan = ComputePan(m_sQueueSample.m_fDistance, &pos);
#endif
				if (bAccelSampleStopped) {
					if (CurrentPretendGear != 1 || currentGear != 2)
						CurrentPretendGear = Max(1, currentGear - 1);
					processedAccelSampleStopped = TRUE;
					bAccelSampleStopped = FALSE;
				}

				if (!channelUsed) {
					if (!processedAccelSampleStopped) {
						if (CurrentPretendGear < params.m_pTransmission->nNumberOfGears - 1)
							CurrentPretendGear++;
						else {
							nCruising = 1;
							goto PlayCruising;
						}
					}

#ifdef GTA_PS2
					SampleManager.InitialiseChannel(CHANNEL_PLAYER_VEHICLE_ENGINE, soundOffset + SFX_CAR_ACCEL_1, SFX_BANK_0);
#else
					if (!SampleManager.InitialiseChannel(CHANNEL_PLAYER_VEHICLE_ENGINE, soundOffset + SFX_CAR_ACCEL_1, SFX_BANK_0))
						return;
#endif
					SampleManager.SetChannelLoopCount(CHANNEL_PLAYER_VEHICLE_ENGINE, 1);
#ifndef GTA_PS2
					SampleManager.SetChannelLoopPoints(CHANNEL_PLAYER_VEHICLE_ENGINE, 0, -1);
#endif
				}

#ifdef EXTERNAL_3D_SOUND
				SampleManager.SetChannelEmittingVolume(CHANNEL_PLAYER_VEHICLE_ENGINE, PLAYER_VEHICLE_ENGINE_VOLUME);
				SampleManager.SetChannel3DPosition(CHANNEL_PLAYER_VEHICLE_ENGINE, pos.x, pos.y, pos.z);
				SampleManager.SetChannel3DDistances(CHANNEL_PLAYER_VEHICLE_ENGINE, VEHICLE_ENGINE_MAX_DIST, VEHICLE_ENGINE_MAX_DIST / 4.0f);
#else
				
				SampleManager.SetChannelVolume(CHANNEL_PLAYER_VEHICLE_ENGINE, ComputeVolume(PLAYER_VEHICLE_ENGINE_VOLUME, VEHICLE_ENGINE_MAX_DIST, m_sQueueSample.m_fDistance));
				SampleManager.SetChannelPan(CHANNEL_PLAYER_VEHICLE_ENGINE, m_sQueueSample.m_nPan);
#endif
				freq = GearFreqAdj[CurrentPretendGear] + freqModifier + 22050;
				if (engineSoundType == SFX_BANK_TRUCK)
					freq >>= 1;
#ifdef USE_TIME_SCALE_FOR_AUDIO
				SampleManager.SetChannelFrequency(CHANNEL_PLAYER_VEHICLE_ENGINE, freq * CTimer::GetTimeScale());
#else
				SampleManager.SetChannelFrequency(CHANNEL_PLAYER_VEHICLE_ENGINE, freq);
#endif
				if (!channelUsed) {
#if GTA_VERSION >= GTA3_PC_10
					SampleManager.SetChannelReverbFlag(CHANNEL_PLAYER_VEHICLE_ENGINE, m_bDynamicAcousticModelingStatus != FALSE);
#else
					SampleManager.SetChannelReverbFlag(CHANNEL_PLAYER_VEHICLE_ENGINE, TRUE);
#endif
					SampleManager.StartChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
				}
			}
		}
	} else {
		if (slowingDown) {
			if (channelUsed) {
				SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
				bAccelSampleStopped = TRUE;
			}
			if (automobile->m_nWheelsOnGround == 0 || automobile->bIsHandbrakeOn || lostTraction)
				gasPedalAudio = automobile->m_fGasPedalAudio;
			else
				gasPedalAudio = Min(1.0f, params.m_fVelocityChange / params.m_pTransmission->fMaxReverseVelocity);

			gasPedalAudio = Max(0.0f, gasPedalAudio);
			automobile->m_fGasPedalAudio = gasPedalAudio;
		} else if (LastAccel > 0) {
			if (channelUsed) {
				SampleManager.StopChannel(CHANNEL_PLAYER_VEHICLE_ENGINE);
				bAccelSampleStopped = TRUE;
			}
			nCruising = 0;
			if (automobile->m_nWheelsOnGround == 0 || automobile->bIsHandbrakeOn || lostTraction ||
			    params.m_fVelocityChange < 0.01f && automobile->m_fGasPedalAudio > 0.2f) {
				automobile->m_fGasPedalAudio *= 0.6f;
				gasPedalAudio = automobile->m_fGasPedalAudio;
			}
			if (gasPedalAudio > 0.05f) {
				freq = (5000 * (gasPedalAudio - 0.05f) / 0.95f) + 19000;
				if (engineSoundType == SFX_BANK_TRUCK)
					freq >>= 1;
				AddPlayerCarSample((25 * (gasPedalAudio - 0.05f) / 0.95f) + 40, freq, (soundOffset + SFX_CAR_FINGER_OFF_ACCEL_1), engineSoundType, 63,
				                   FALSE);
			}
		}
		freq = (10000 * gasPedalAudio) + 22050;
		if (engineSoundType == SFX_BANK_TRUCK)
			freq >>= 1;
		AddPlayerCarSample(110 - (40 * gasPedalAudio), freq, (engineSoundType - CAR_SFX_BANKS_OFFSET + SFX_CAR_IDLE_1), SFX_BANK_0, 52, TRUE);

		CurrentPretendGear = Max(1, currentGear);
	}
	LastAccel = accelerateState;

	bHandbrakeOnLastFrame = !!automobile->bIsHandbrakeOn;
	bLostTractionLastFrame = lostTraction;
}

bool8
cAudioManager::ProcessVehicleSkidding(cVehicleParams& params)
{
	CAutomobile *automobile;
	cTransmission *transmission;
	uint8 Vol;
	float newSkidVal = 0.0f;
	float skidVal = 0.0f;

	if (params.m_fDistance < SQR(VEHICLE_SKIDDING_MAX_DIST)) {
		automobile = (CAutomobile *)params.m_pVehicle;
		if (automobile->m_nWheelsOnGround > 0) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			for (uint8 i = 0; i < ARRAY_SIZE(automobile->m_aWheelState); i++) {
				if (automobile->m_aWheelState[i] == WHEEL_STATE_NORMAL || automobile->Damage.GetWheelStatus(i) == WHEEL_STATUS_MISSING)
					continue;
				transmission = params.m_pTransmission;
				switch (transmission->nDriveType) {
				case '4':
					newSkidVal = GetVehicleDriveWheelSkidValue(i, automobile, transmission, params.m_fVelocityChange);
					break;
				case 'F':
					if (i == CARWHEEL_FRONT_LEFT || i == CARWHEEL_FRONT_RIGHT)
						newSkidVal = GetVehicleDriveWheelSkidValue(i, automobile, transmission, params.m_fVelocityChange);
					else
						newSkidVal = GetVehicleNonDriveWheelSkidValue(i, automobile, transmission, params.m_fVelocityChange);
					break;
				case 'R':
					if (i == CARWHEEL_REAR_LEFT || i == CARWHEEL_REAR_RIGHT)
						newSkidVal = GetVehicleDriveWheelSkidValue(i, automobile, transmission, params.m_fVelocityChange);
					else
						newSkidVal = GetVehicleNonDriveWheelSkidValue(i, automobile, transmission, params.m_fVelocityChange);
					break;
				default:
					break;
				}
				skidVal = Max(skidVal, newSkidVal);
			}

			if (skidVal > 0.0f) {
				Vol = VEHICLE_SKIDDING_VOLUME * skidVal;
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, VEHICLE_SKIDDING_MAX_DIST, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = 3;
					switch (params.m_pVehicle->m_nSurfaceTouched) {
					case SURFACE_GRASS:
					case SURFACE_HEDGE:
						m_sQueueSample.m_nSampleIndex = SFX_RAIN;
						Vol >>= 2;
						m_sQueueSample.m_nFrequency = 13000 * skidVal + 35000;
						m_sQueueSample.m_nVolume >>= 2;
						if (m_sQueueSample.m_nVolume == 0)
							return TRUE;
						break;
					case SURFACE_GRAVEL:
					case SURFACE_MUD_DRY:
					case SURFACE_SAND:
					case SURFACE_WATER:
						m_sQueueSample.m_nSampleIndex = SFX_GRAVEL_SKID;
						m_sQueueSample.m_nFrequency = 6000 * skidVal + 10000;
						break;

					default:
						m_sQueueSample.m_nSampleIndex = SFX_SKID;
						m_sQueueSample.m_nFrequency = 5000 * skidVal + 11000;
						break;
					}

					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nPriority = 8;
					m_sQueueSample.m_nLoopCount = 0;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 3.0f;
					m_sQueueSample.m_MaxDistance = VEHICLE_SKIDDING_MAX_DIST;
					m_sQueueSample.m_bStatic = FALSE;
					m_sQueueSample.m_nFramesToPlay = 3;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

float
cAudioManager::GetVehicleDriveWheelSkidValue(uint8 wheel, CAutomobile *automobile, cTransmission *transmission, float velocityChange)
{
	float relativeVelChange = 0.0f;
	float gasPedalAudio = automobile->m_fGasPedalAudio;
	float velChange;
	float relativeVel;

	switch (automobile->m_aWheelState[wheel])
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

	return Max(relativeVelChange, Min(1.0f, Abs(automobile->m_vecTurnSpeed.z) * 20.0f));
}

float
cAudioManager::GetVehicleNonDriveWheelSkidValue(uint8 wheel, CAutomobile *automobile, cTransmission *transmission, float velocityChange)
{
	float relativeVelChange = 0.0f;

	if (automobile->m_aWheelState[wheel] == WHEEL_STATE_SKIDDING)
		relativeVelChange = Min(1.0f, Abs(velocityChange) / transmission->fMaxVelocity);

	return Max(relativeVelChange, Min(1.0f, Abs(automobile->m_vecTurnSpeed.z) * 20.0f));
}

bool8
cAudioManager::ProcessVehicleHorn(cVehicleParams& params)
{
	if (params.m_fDistance < SQR(VEHICLE_HORN_MAX_DIST)) {
		if (params.m_pVehicle->m_bSirenOrAlarm && UsesSirenSwitching(params.m_nIndex))
			return TRUE;

		if (params.m_pVehicle->GetModelIndex() == MI_MRWHOOP)
			return TRUE;

		if (params.m_pVehicle->m_nCarHornTimer > 0) {
			if (params.m_pVehicle->GetStatus() != STATUS_PLAYER) {
				params.m_pVehicle->m_nCarHornTimer = Min(44, params.m_pVehicle->m_nCarHornTimer);
				if (params.m_pVehicle->m_nCarHornTimer == 44)
					params.m_pVehicle->m_nCarHornPattern = (m_FrameCounter + m_sQueueSample.m_nEntityIndex) & 7;
				if (!HornPattern[params.m_pVehicle->m_nCarHornPattern][44 - params.m_pVehicle->m_nCarHornTimer])
					return TRUE;
			}

			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(VEHICLE_HORN_VOLUME, VEHICLE_HORN_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 4;
				m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nHornSample;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 2;
				m_sQueueSample.m_nFrequency = aVehicleSettings[params.m_nIndex].m_nHornFrequency;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(VEHICLE_HORN_VOLUME);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 5.0f;
				m_sQueueSample.m_MaxDistance = VEHICLE_HORN_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 3;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::UsesSiren(uint32 model)
{
	switch (model) {
	case FIRETRUK:
	case AMBULAN:
	case FBICAR:
	case POLICE:
	case ENFORCER:
	case PREDATOR:
		return TRUE;
	default:
		return FALSE;
	}
}

bool8
cAudioManager::UsesSirenSwitching(uint32 model)
{
	switch (model) {
	case AMBULAN:
	case POLICE:
	case ENFORCER:
	case PREDATOR:
		return TRUE;
	default:
		return FALSE;
	}
}

bool8
cAudioManager::ProcessVehicleSirenOrAlarm(cVehicleParams& params)
{
	if (params.m_fDistance < SQR(VEHICLE_SIREN_MAX_DIST)) {
		CVehicle *veh = params.m_pVehicle;
		if (veh->m_bSirenOrAlarm || veh->IsAlarmOn()) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(VEHICLE_SIREN_VOLUME, VEHICLE_SIREN_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 5;
				if (UsesSiren(params.m_nIndex)) {
					if (params.m_pVehicle->GetStatus() == STATUS_ABANDONED)
						return TRUE;
					if (veh->m_nCarHornTimer > 0 && params.m_nIndex != FIRETRUK) {
						m_sQueueSample.m_nSampleIndex = SFX_SIREN_FAST;
						if (params.m_nIndex == FBICAR)
							m_sQueueSample.m_nFrequency = 16113;
						else
							m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SIREN_FAST);
						m_sQueueSample.m_nCounter = 60;
					} else {
						m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nSirenOrAlarmSample;
						m_sQueueSample.m_nFrequency = aVehicleSettings[params.m_nIndex].m_nSirenOrAlarmFrequency;
					}
				} else {
					m_sQueueSample.m_nSampleIndex = aVehicleSettings[params.m_nIndex].m_nSirenOrAlarmSample;
					m_sQueueSample.m_nFrequency = aVehicleSettings[params.m_nIndex].m_nSirenOrAlarmFrequency;
				}
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 1;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(VEHICLE_SIREN_VOLUME);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 7.0f;
				m_sQueueSample.m_MaxDistance = VEHICLE_SIREN_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 5;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::UsesReverseWarning(uint32 model)
{
	return model == LINERUN || model == FIRETRUK || model == TRASH || model == BUS || model == COACH;
}

bool8
cAudioManager::ProcessVehicleReverseWarning(cVehicleParams& params)
{
	CVehicle *veh = params.m_pVehicle;

	if (params.m_fDistance < SQR(VEHICLE_REVERSE_WARNING_MAX_DIST)) {
		if (veh->bEngineOn && veh->m_fGasPedal < 0.0f) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(VEHICLE_REVERSE_WARNING_VOLUME, VEHICLE_REVERSE_WARNING_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 12;
				m_sQueueSample.m_nSampleIndex = SFX_REVERSE_WARNING;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 2;
				m_sQueueSample.m_nFrequency = (100 * m_sQueueSample.m_nEntityIndex % 1024) + SampleManager.GetSampleBaseFrequency(SFX_REVERSE_WARNING);
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(VEHICLE_REVERSE_WARNING_VOLUME);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 3.0f;
				m_sQueueSample.m_MaxDistance = VEHICLE_REVERSE_WARNING_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 3;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessVehicleDoors(cVehicleParams& params)
{
	CAutomobile *automobile;
	int8 doorState;
	uint8 Vol;
	float velocity;

	if (params.m_fDistance < SQR(VEHICLE_DOORS_MAX_DIST)) {
		automobile = (CAutomobile *)params.m_pVehicle;
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		for (uint8 i = 0; i < ARRAY_SIZE(automobile->Doors); i++) {
			if (automobile->Damage.GetDoorStatus(i) == DOOR_STATUS_SWINGING) {
				doorState = automobile->Doors[i].m_nDoorState;
				if (doorState == DOORST_OPEN || doorState == DOORST_CLOSED) {
					velocity = Min(0.3f, Abs(automobile->Doors[i].m_fAngVel));
					if (velocity > 0.0035f) {
						Vol = (VEHICLE_DOORS_VOLUME * velocity / 0.3f);
						m_sQueueSample.m_nVolume = ComputeVolume(Vol, VEHICLE_DOORS_MAX_DIST, m_sQueueSample.m_fDistance);
						if (m_sQueueSample.m_nVolume > 0) {
							m_sQueueSample.m_nCounter = i + 6;
							m_sQueueSample.m_nSampleIndex = m_anRandomTable[1] % 6 + SFX_COL_CAR_PANEL_1;
							m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex) + RandomDisplacement(1000);
							m_sQueueSample.m_nBankIndex = SFX_BANK_0;
							m_sQueueSample.m_bIs2D = FALSE;
							m_sQueueSample.m_nPriority = 10;
							m_sQueueSample.m_nLoopCount = 1;
							SET_EMITTING_VOLUME(Vol);
							RESET_LOOP_OFFSETS
							m_sQueueSample.m_fSpeedMultiplier = 1.0f;
							m_sQueueSample.m_MaxDistance = VEHICLE_DOORS_MAX_DIST;
							m_sQueueSample.m_bStatic = TRUE;
							m_sQueueSample.m_bReverb = TRUE;
							SET_SOUND_REFLECTION(TRUE);
							AddSampleToRequestedQueue();
						}
					}
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessAirBrakes(cVehicleParams& params)
{
	CAutomobile *automobile;
	uint8 Vol;

	if (params.m_fDistance < SQR(AIR_BRAKES_MAX_DIST)) {
		automobile = (CAutomobile *)params.m_pVehicle;
		if (automobile->bEngineOn && (automobile->m_fVelocityChangeForAudio >= 0.025f && params.m_fVelocityChange < 0.025f ||
			automobile->m_fVelocityChangeForAudio <= -0.025f && params.m_fVelocityChange > 0.025f)) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			Vol = m_anRandomTable[0] % 10 + AIR_BRAKES_VOLUME;
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, AIR_BRAKES_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 13;
				m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_AIR_BRAKES);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 10;
				m_sQueueSample.m_nLoopCount = 1;
				SET_EMITTING_VOLUME(Vol);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = AIR_BRAKES_MAX_DIST;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::HasAirBrakes(uint32 model)
{
	return model == LINERUN || model == FIRETRUK || model == TRASH || model == BUS || model == COACH;
}

bool8
cAudioManager::ProcessEngineDamage(cVehicleParams& params)
{
	CAutomobile *veh;
	uint8 engineStatus;
	uint8 Vol;

	if (params.m_fDistance < SQR(ENGINE_DAMAGE_MAX_DIST)) {
		veh = (CAutomobile *)params.m_pVehicle;
		if (veh->bEngineOn) {
			engineStatus = veh->Damage.GetEngineStatus();
			if (engineStatus > 250 || engineStatus < 100)
				return TRUE;
			if (engineStatus >= 225) {
				Vol = ENGINE_DAMAGE_ON_FIRE_VOLUME;
				m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
				m_sQueueSample.m_nPriority = 7;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE);
			} else {
				m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
				Vol = ENGINE_DAMAGE_VOLUME;
				m_sQueueSample.m_nPriority = 7;
				m_sQueueSample.m_nFrequency = 40000;
			}
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, ENGINE_DAMAGE_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 28;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(Vol);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_MaxDistance = ENGINE_DAMAGE_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 3;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessCarBombTick(cVehicleParams& params)
{
	CAutomobile *automobile;

	if (params.m_fDistance < SQR(CAR_BOMB_TICK_MAX_DIST)) {
		automobile = (CAutomobile *)params.m_pVehicle;
		if (automobile->bEngineOn && automobile->m_bombType == CARBOMB_TIMEDACTIVE) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(CAR_BOMB_TICK_VOLUME, CAR_BOMB_TICK_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 35;
				m_sQueueSample.m_nSampleIndex = SFX_COUNTDOWN;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_COUNTDOWN);
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(CAR_BOMB_TICK_VOLUME);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_MaxDistance = CAR_BOMB_TICK_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 3;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

void
cAudioManager::ProcessVehicleOneShots(cVehicleParams& params)
{
	int16 event;
	uint8 Vol;
	float eventRelVol;
	float eventVol;
	bool8 bLoop;
	float maxDist;

	static uint8 WaveIndex = 41;
	static uint8 GunIndex = 53;

	for (uint16 i = 0; i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; i++) {
		bLoop = FALSE;
		SET_SOUND_REFLECTION(FALSE);
		event = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i];
		switch (event) {
		case SOUND_CAR_WINDSHIELD_CRACK:
			maxDist = SQR(VEHICLE_ONE_SHOT_WINDSHIELD_CRACK_MAX_DIST);
			m_sQueueSample.m_nSampleIndex = SFX_GLASS_CRACK;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 68;
			Vol = m_anRandomTable[1] % 30 + VEHICLE_ONE_SHOT_WINDSHIELD_CRACK_VOLUME;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_CRACK);
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_WINDSHIELD_CRACK_MAX_DIST;
			break;
		case SOUND_CAR_DOOR_OPEN_BONNET:
		case SOUND_CAR_DOOR_OPEN_BUMPER:
		case SOUND_CAR_DOOR_OPEN_FRONT_LEFT:
		case SOUND_CAR_DOOR_OPEN_FRONT_RIGHT:
		case SOUND_CAR_DOOR_OPEN_BACK_LEFT:
		case SOUND_CAR_DOOR_OPEN_BACK_RIGHT:
			maxDist = SQR(VEHICLE_ONE_SHOT_DOOR_MAX_DIST);
			Vol = m_anRandomTable[1] % (MAX_VOLUME - VEHICLE_ONE_SHOT_DOOR_CLOSE_VOLUME) + VEHICLE_ONE_SHOT_DOOR_CLOSE_VOLUME;
			switch (aVehicleSettings[params.m_nIndex].m_bDoorType) {
			case OLD_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_OLD_CAR_DOOR_OPEN;
				break;
			case NEW_DOOR:
			default:
				m_sQueueSample.m_nSampleIndex = SFX_NEW_CAR_DOOR_OPEN;
				break;
			case TRUCK_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_TRUCK_DOOR_OPEN;
				break;
			case BUS_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
				break;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#ifdef THIS_IS_STUPID
			m_sQueueSample.m_nCounter = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] + 10;
#else
			m_sQueueSample.m_nCounter = event + 10;
#endif
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_DOOR_MAX_DIST;
			SET_SOUND_REFLECTION(TRUE);
			break;
		case SOUND_CAR_DOOR_CLOSE_BONNET:
		case SOUND_CAR_DOOR_CLOSE_BUMPER:
		case SOUND_CAR_DOOR_CLOSE_FRONT_LEFT:
		case SOUND_CAR_DOOR_CLOSE_FRONT_RIGHT:
		case SOUND_CAR_DOOR_CLOSE_BACK_LEFT:
		case SOUND_CAR_DOOR_CLOSE_BACK_RIGHT:
			maxDist = SQR(VEHICLE_ONE_SHOT_DOOR_MAX_DIST);
			Vol = m_anRandomTable[2] % (MAX_VOLUME - VEHICLE_ONE_SHOT_DOOR_OPEN_VOLUME) + VEHICLE_ONE_SHOT_DOOR_OPEN_VOLUME;
			switch (aVehicleSettings[params.m_nIndex].m_bDoorType) {
			case OLD_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_OLD_CAR_DOOR_CLOSE;
				break;
			case NEW_DOOR:
			default:
				m_sQueueSample.m_nSampleIndex = SFX_NEW_CAR_DOOR_CLOSE;
				break;
			case TRUCK_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_TRUCK_DOOR_CLOSE;
				break;
			case BUS_DOOR:
				m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
				break;
			}
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
#ifdef THIS_IS_STUPID
			m_sQueueSample.m_nCounter = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] + 22;
#else
			m_sQueueSample.m_nCounter = event + 22;
#endif
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_DOOR_MAX_DIST;
			SET_SOUND_REFLECTION(TRUE);
			break;
		case SOUND_CAR_ENGINE_START: 
			Vol = VEHICLE_ONE_SHOT_CAR_ENGINE_START_VOLUME;
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_ENGINE_START_MAX_DIST);
			m_sQueueSample.m_nSampleIndex = SFX_CAR_STARTER;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 33;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_STARTER);
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_ENGINE_START_MAX_DIST;
			SET_SOUND_REFLECTION(TRUE);
			break;
		case SOUND_WEAPON_HIT_VEHICLE:
			m_sQueueSample.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % ARRAY_SIZE(m_anRandomTable)] % 6 + SFX_BULLET_CAR_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 34;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
			m_sQueueSample.m_nPriority = 7;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_WEAPON_HIT_VEHICLE_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_WEAPON_HIT_VEHICLE_MAX_DIST);
			Vol = m_anRandomTable[3] % 20 + VEHICLE_ONE_SHOT_WEAPON_HIT_VEHICLE_VOLUME;
			break;
		case SOUND_BOMB_TIMED_ACTIVATED:
		case SOUND_55:
		case SOUND_BOMB_ONIGNITION_ACTIVATED:
		case SOUND_BOMB_TICK:
			m_sQueueSample.m_nSampleIndex = SFX_ARM_BOMB;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 36;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ARM_BOMB);
			m_sQueueSample.m_nPriority = 0;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_BOMB_ARMED_MAX_DIST;
			SET_SOUND_REFLECTION(TRUE);
			Vol = VEHICLE_ONE_SHOT_BOMB_ARMED_VOLUME;
			maxDist = SQR(VEHICLE_ONE_SHOT_BOMB_ARMED_MAX_DIST);
			break;
		case SOUND_CAR_LIGHT_BREAK:
			m_sQueueSample.m_nSampleIndex = SFX_GLASS_SHARD_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 37;
			m_sQueueSample.m_nFrequency = 9 * SampleManager.GetSampleBaseFrequency(SFX_GLASS_SHARD_1) / 10;
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 3);
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_WINDSHIELD_CRACK_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_WINDSHIELD_CRACK_MAX_DIST);
			Vol = m_anRandomTable[4] % 10 + VEHICLE_ONE_SHOT_CAR_LIGHT_BREAK_VOLUME;
			break;
		case SOUND_PLANE_ON_GROUND: 
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_LAND_WHEELS;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 81;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_JUMBO_LAND_WHEELS);
			m_sQueueSample.m_nPriority = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_PLANE_ON_GROUND_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_PLANE_ON_GROUND_MAX_DIST);
			Vol = m_anRandomTable[4] % 25 + VEHICLE_ONE_SHOT_PLANE_ON_GROUND_VOLUME;
			break;
		case SOUND_CAR_JERK: 
			m_sQueueSample.m_nSampleIndex = SFX_SHAG_SUSPENSION;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 87;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SHAG_SUSPENSION);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 3);
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_HYDRAULIC_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_HYDRAULIC_MAX_DIST);
			Vol = m_anRandomTable[1] % 15 + VEHICLE_ONE_SHOT_CAR_HYDRAULIC_VOLUME;
			break;
		case SOUND_CAR_HYDRAULIC_1:
		case SOUND_CAR_HYDRAULIC_2:
			if (event == SOUND_CAR_HYDRAULIC_1)
				m_sQueueSample.m_nFrequency = 15600;
			else
				m_sQueueSample.m_nFrequency = 13118;
			m_sQueueSample.m_nSampleIndex = SFX_SUSPENSION_FAST_MOVE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 51;
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 3);
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_HYDRAULIC_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_HYDRAULIC_MAX_DIST);
			Vol = m_anRandomTable[0] % 15 + VEHICLE_ONE_SHOT_CAR_HYDRAULIC_VOLUME;
			break;
		case SOUND_CAR_HYDRAULIC_3:
			m_sQueueSample.m_nSampleIndex = SFX_SUSPENSION_SLOW_MOVE_LOOP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 86;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SUSPENSION_SLOW_MOVE_LOOP);
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_HYDRAULIC_MAX_DIST;
			m_sQueueSample.m_nFramesToPlay = 7;
			bLoop = TRUE;
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_HYDRAULIC_MAX_DIST);
			Vol = m_anRandomTable[0] % 15 + VEHICLE_ONE_SHOT_CAR_HYDRAULIC_VOLUME;
			break;
		case SOUND_WATER_FALL:
			m_sQueueSample.m_nSampleIndex = SFX_SPLASH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 15;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 16000;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_WATER_FALL_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_WATER_FALL_MAX_DIST);
			SET_SOUND_REFLECTION(TRUE);
			Vol = m_anRandomTable[4] % 20 + VEHICLE_ONE_SHOT_WATER_FALL_VOLUME;
			break;
		case SOUND_CAR_BOMB_TICK:
			m_sQueueSample.m_nSampleIndex = SFX_BOMB_BEEP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 80;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BOMB_BEEP);
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_BOMB_TICK_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_BOMB_TICK_MAX_DIST);
			SET_SOUND_REFLECTION(TRUE);
			Vol = VEHICLE_ONE_SHOT_CAR_BOMB_TICK_VOLUME;
			break;
		case SOUND_CAR_SPLASH:
			eventVol = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			if (eventVol <= 300)
				continue;
			if (eventVol > 1200)
				m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] = 1200;
			eventRelVol = (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] - 300) / (1200 - 300);
			m_sQueueSample.m_nSampleIndex = (m_anRandomTable[0] % 2) + SFX_BOAT_SPLASH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = WaveIndex++;
			if (WaveIndex > 46)
				WaveIndex = 41;
			m_sQueueSample.m_nFrequency = (7000 * eventRelVol) + 6000;
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_SPLASH_MAX_DIST;
			Vol = (VEHICLE_ONE_SHOT_CAR_SPLASH_VOLUME * eventRelVol);
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_SPLASH_MAX_DIST);
			break;
		case SOUND_BOAT_SLOWDOWN:
			m_sQueueSample.m_nSampleIndex = SFX_POLICE_BOAT_THUMB_OFF;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 47;
			m_sQueueSample.m_nFrequency = RandomDisplacement(600) + SampleManager.GetSampleBaseFrequency(SFX_POLICE_BOAT_THUMB_OFF);
			m_sQueueSample.m_nPriority = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_BOAT_SLOWDOWN_MAX_DIST;
			Vol = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			maxDist = SQR(VEHICLE_ONE_SHOT_BOAT_SLOWDOWN_MAX_DIST);
			break;
		case SOUND_CAR_JUMP:
		{
			static uint8 iWheelIndex = 82;
			Vol = Max(VEHICLE_ONE_SHOT_CAR_JUMP_VOLUME, 2 * (100 * m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]));
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_JUMP_MAX_DIST);
			m_sQueueSample.m_nSampleIndex = SFX_TYRE_BUMP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iWheelIndex++;
			if (iWheelIndex > 85)
				iWheelIndex = 82;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TYRE_BUMP);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
			if (params.m_nIndex == RCBANDIT) {
				m_sQueueSample.m_nFrequency <<= 1;
				Vol >>= 1;
			}
			m_sQueueSample.m_nPriority = 6;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_JUMP_MAX_DIST;
			break;
		}
		case SOUND_WEAPON_SHOT_FIRED:
			Vol = m_anRandomTable[2];
			maxDist = SQR(VEHICLE_ONE_SHOT_WEAPON_SHOT_FIRED_MAX_DIST);
			m_sQueueSample.m_nSampleIndex = SFX_UZI_LEFT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = GunIndex++;
			Vol = Vol % 15 + VEHICLE_ONE_SHOT_WEAPON_SHOT_FIRED_VOLUME;
			if (GunIndex > 58)
				GunIndex = 53;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_UZI_LEFT);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_WEAPON_SHOT_FIRED_MAX_DIST;
			break;
		case SOUND_TRAIN_DOOR_CLOSE:
		case SOUND_TRAIN_DOOR_OPEN:
			m_sQueueSample.m_nSampleIndex = SFX_AIR_BRAKES;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 59;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 11025;
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 5.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_TRAIN_DOOR_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_TRAIN_DOOR_MAX_DIST);
			Vol = m_anRandomTable[1] % 20 + VEHICLE_ONE_SHOT_TRAIN_DOOR_VOLUME;
			break;
		case SOUND_SPLATTER:
		{
			static uint8 CrunchOffset = 0;
			m_sQueueSample.m_nSampleIndex = CrunchOffset + SFX_PED_CRUNCH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 48;
			m_sQueueSample.m_nFrequency = RandomDisplacement(600) + SampleManager.GetSampleBaseFrequency(SFX_PED_CRUNCH_1);
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_SPLATTER_MAX_DIST;
			CrunchOffset++;
			maxDist = SQR(VEHICLE_ONE_SHOT_SPLATTER_MAX_DIST);
			Vol = m_anRandomTable[4] % 20 + VEHICLE_ONE_SHOT_SPLATTER_VOLUME;
			CrunchOffset %= 2;
			SET_SOUND_REFLECTION(TRUE);
			break;
		}
		case SOUND_CAR_PED_COLLISION:
			eventVol = Min(20.0f, m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i]);
			Vol = (eventVol / 20 * MAX_VOLUME);
			if (Vol == 0)
				continue;

			m_sQueueSample.m_nSampleIndex = (m_anRandomTable[2] % 4) + SFX_FIGHT_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 50;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex) >> 1;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_PED_COLLISION_MAX_DIST;
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_PED_COLLISION_MAX_DIST);
			break;
		case SOUND_PED_HELI_PLAYER_FOUND:
		{
			cPedParams pedParams;
			pedParams.m_bDistanceCalculated = params.m_bDistanceCalculated;
			pedParams.m_fDistance = params.m_fDistance;
			SetupPedComments(pedParams, SOUND_PED_HELI_PLAYER_FOUND);
			continue;
		}
		case SOUND_PED_BODYCAST_HIT:
		{
			cPedParams pedParams;
			pedParams.m_bDistanceCalculated = params.m_bDistanceCalculated;
			pedParams.m_fDistance = params.m_fDistance;
			SetupPedComments(pedParams, SOUND_PED_BODYCAST_HIT);
			continue;
		}
		case SOUND_CAR_TANK_TURRET_ROTATE:
			eventVol = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i];
			if (eventVol > 96.0f / 2500.0f)
				eventVol = 96.0f / 2500.0f;
			m_sQueueSample.m_nSampleIndex = SFX_TANK_TURRET;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 79;
			m_sQueueSample.m_nFrequency = (3000 * eventVol / (96.0f / 2500.0f)) + 9000;
			m_sQueueSample.m_nPriority = 2;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_nFramesToPlay = 3;
			m_sQueueSample.m_MaxDistance = VEHICLE_ONE_SHOT_CAR_TANK_TURRET_MAX_DIST;
			Vol = (37 * eventVol / (96.0f / 2500.0f)) + VEHICLE_ONE_SHOT_CAR_TANK_TURRET_VOLUME;
			maxDist = SQR(VEHICLE_ONE_SHOT_CAR_TANK_TURRET_MAX_DIST);
			bLoop = TRUE;
			break;
		default:
			continue;
		}
		if (params.m_fDistance < maxDist) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				if (bLoop) {
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_bStatic = FALSE;
				} else {
					m_sQueueSample.m_nLoopCount = 1;
					m_sQueueSample.m_bStatic = TRUE;
				}
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bReverb = TRUE;
				m_sQueueSample.m_bIs2D = FALSE;
				AddSampleToRequestedQueue();
			}
		}
	}
}

bool8
cAudioManager::ProcessTrainNoise(cVehicleParams& params)
{
	CTrain *train;
	uint8 Vol;
	float speedMultipler;

	if (params.m_fDistance < SQR(TRAIN_NOISE_FAR_MAX_DIST)){
		if (params.m_fVelocityChange > 0.0f) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			train = (CTrain *)params.m_pVehicle;
			speedMultipler = Min(1.0f, train->m_fSpeed * 250.0f / 51.0f);
			Vol = (TRAIN_NOISE_VOLUME * speedMultipler);
			if (train->m_fWagonPosition == 0.0f) {
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, TRAIN_NOISE_FAR_MAX_DIST, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = 32;
					m_sQueueSample.m_nSampleIndex = SFX_TRAIN_FAR;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nPriority = 2;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TRAIN_FAR);
					m_sQueueSample.m_nLoopCount = 0;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 3.0f;
					m_sQueueSample.m_MaxDistance = TRAIN_NOISE_FAR_MAX_DIST;
					m_sQueueSample.m_bStatic = FALSE;
					m_sQueueSample.m_nFramesToPlay = 3;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
			if (params.m_fDistance < SQR(TRAIN_NOISE_NEAR_MAX_DIST)) {
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, TRAIN_NOISE_NEAR_MAX_DIST, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = 33;
					m_sQueueSample.m_nSampleIndex = SFX_TRAIN_NEAR;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nPriority = 5;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TRAIN_NEAR) + 100 * m_sQueueSample.m_nEntityIndex % 987;
					m_sQueueSample.m_nLoopCount = 0;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 6.0f;
					m_sQueueSample.m_MaxDistance = TRAIN_NOISE_NEAR_MAX_DIST;
					m_sQueueSample.m_bStatic = FALSE;
					m_sQueueSample.m_nFramesToPlay = 3;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessBoatEngine(cVehicleParams& params)
{
	CBoat *boat;
	float padRelativeAccerate;
	float gasPedal;
	float padAccelerate;
	uint8 Vol;
	float oneShotVol;

	static uint16 LastAccel = 0;
	static uint8 LastVol = 0;

	if (params.m_fDistance < SQR(BOAT_ENGINE_MAX_DIST)) {
		boat = (CBoat *)params.m_pVehicle;
		if (params.m_nIndex == REEFER) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(BOAT_ENGINE_REEFER_IDLE_VOLUME, BOAT_ENGINE_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 39;
				m_sQueueSample.m_nSampleIndex = SFX_FISHING_BOAT_IDLE;
				m_sQueueSample.m_nFrequency = 10386;
				m_sQueueSample.m_nFrequency += (m_sQueueSample.m_nEntityIndex << 16) % 1000;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(BOAT_ENGINE_REEFER_IDLE_VOLUME);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_MaxDistance = BOAT_ENGINE_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 7;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
			if (FindPlayerVehicle() == params.m_pVehicle) {
				padAccelerate = Max(Pads[0].GetAccelerate(), Pads[0].GetBrake());
				padRelativeAccerate = padAccelerate / 255.0f;
				Vol = (BOAT_ENGINE_REEFER_ACCEL_VOLUME_MULT * padRelativeAccerate) + BOAT_ENGINE_REEFER_ACCEL_MIN_VOLUME;
				m_sQueueSample.m_nFrequency = (3000 * padRelativeAccerate) + 6000;
				if (!boat->bPropellerInWater)
					m_sQueueSample.m_nFrequency = 11 * m_sQueueSample.m_nFrequency / 10;
			} else {
				gasPedal = Abs(boat->m_fGasPedal);
				if (gasPedal > 0.0f) {
					Vol = (BOAT_ENGINE_REEFER_ACCEL_VOLUME_MULT * gasPedal) + BOAT_ENGINE_REEFER_ACCEL_MIN_VOLUME;
					m_sQueueSample.m_nFrequency = (3000 * gasPedal) + 6000;
					if (!boat->bPropellerInWater)
						m_sQueueSample.m_nFrequency = 11 * m_sQueueSample.m_nFrequency / 10;
				} else {
					m_sQueueSample.m_nFrequency = 6000;
					Vol = BOAT_ENGINE_REEFER_ACCEL_MIN_VOLUME;
				}
			}
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, BOAT_ENGINE_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 40;
				m_sQueueSample.m_nSampleIndex = SFX_POLICE_BOAT_ACCEL;
				m_sQueueSample.m_nFrequency += (m_sQueueSample.m_nEntityIndex << 16) % 1000;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(Vol);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_MaxDistance = BOAT_ENGINE_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 7;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		} else {
			if (FindPlayerVehicle() == params.m_pVehicle) {
				padAccelerate = Max(Pads[0].GetAccelerate(), Pads[0].GetBrake());
				if (padAccelerate <= 20) {
					Vol = BOAT_ENGINE_LOW_ACCEL_VOLUME - BOAT_ENGINE_LOW_ACCEL_VOLUME * padAccelerate / 40;
					m_sQueueSample.m_nFrequency = 100 * padAccelerate + 11025;
					m_sQueueSample.m_nCounter = 39;
					m_sQueueSample.m_nSampleIndex = SFX_POLICE_BOAT_IDLE;
					if (LastAccel > 20) {
						oneShotVol = LastVol;
						PlayOneShot(m_sQueueSample.m_nEntityIndex, SOUND_BOAT_SLOWDOWN, oneShotVol);
					}
				} else {
					Vol = BOAT_ENGINE_HIGH_ACCEL_VOLUME_MULT * padAccelerate / 255 + BOAT_ENGINE_HIGH_ACCEL_MIN_VOLUME;
					m_sQueueSample.m_nFrequency = 4000 * padAccelerate / 255 + 8000;
					if (!boat->m_bIsAnchored)
						m_sQueueSample.m_nFrequency = 11 * m_sQueueSample.m_nFrequency / 10;
					m_sQueueSample.m_nCounter = 40;
					m_sQueueSample.m_nSampleIndex = SFX_POLICE_BOAT_ACCEL;
				}
				LastVol = Vol;
				LastAccel = padAccelerate;
			} else {
				gasPedal = Abs(boat->m_fGasPedal);
				if (gasPedal > 0.0f) {
					Vol = (BOAT_ENGINE_HIGH_ACCEL_VOLUME_MULT * gasPedal) + BOAT_ENGINE_HIGH_ACCEL_MIN_VOLUME;
					m_sQueueSample.m_nFrequency = (4000 * gasPedal) + 8000;
					if (!boat->m_bIsAnchored)
						m_sQueueSample.m_nFrequency = 11 * m_sQueueSample.m_nFrequency / 10;
					m_sQueueSample.m_nCounter = 40;
					m_sQueueSample.m_nSampleIndex = SFX_POLICE_BOAT_ACCEL;
				} else {
					m_sQueueSample.m_nFrequency = 11025;
					Vol = BOAT_ENGINE_LOW_ACCEL_VOLUME;
					m_sQueueSample.m_nCounter = 39;
					m_sQueueSample.m_nSampleIndex = SFX_POLICE_BOAT_IDLE;
				}
			}
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, BOAT_ENGINE_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nFrequency += (m_sQueueSample.m_nEntityIndex << 16) % 1000;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(Vol);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_MaxDistance = BOAT_ENGINE_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 7;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::ProcessBoatMovingOverWater(cVehicleParams& params)
{
	float velocityChange;
	uint8 Vol;
	float multiplier;

	if (params.m_fDistance < SQR(BOAT_MOVING_OVER_WATER_MAX_DIST)) {
		velocityChange = Abs(params.m_fVelocityChange);
		if (velocityChange > 0.0005f && ((CBoat*)params.m_pVehicle)->bBoatInWater) {
			velocityChange = Min(0.75f, velocityChange);
			multiplier = (velocityChange - 0.0005f) / (1499.0f / 2000.0f);
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			Vol = (BOAT_MOVING_OVER_WATER_VOLUME * multiplier);
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, BOAT_MOVING_OVER_WATER_MAX_DIST, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = 38;
				m_sQueueSample.m_nSampleIndex = SFX_BOAT_WATER_LOOP;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_nFrequency = (6050 * multiplier) + 16000;
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(Vol);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				m_sQueueSample.m_MaxDistance = BOAT_MOVING_OVER_WATER_MAX_DIST;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 3;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

struct tHelicopterSampleData {
	float m_fMaxDistance;
	float m_fBaseDistance;
	uint8 m_bBaseVolume;
};
static Const tHelicopterSampleData gHeliSfxRanges[3] = {{400, 380, 100}, {100, 70, MAX_VOLUME}, {60, 30, MAX_VOLUME}};

bool8
cAudioManager::ProcessHelicopter(cVehicleParams& params)
{
	CHeli *heli;
	float MaxDist;
	float dist;
	float baseDist;
	uint8 Vol;

	if (params.m_fDistance < SQR(gHeliSfxRanges[0].m_fMaxDistance)) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		heli = (CHeli *)params.m_pVehicle;
		for (uint32 i = 0; i < ARRAY_SIZE(gHeliSfxRanges); i++) {
			MaxDist = gHeliSfxRanges[i].m_fMaxDistance;
			dist = m_sQueueSample.m_fDistance;
			if (dist < MaxDist) {
				baseDist = gHeliSfxRanges[i].m_fBaseDistance;
				if (dist < baseDist)
					Vol = gHeliSfxRanges[i].m_bBaseVolume;
				else
					Vol = (gHeliSfxRanges[i].m_bBaseVolume * ((MaxDist - dist) / (MaxDist - baseDist)));
			} else
				return TRUE;

			m_sQueueSample.m_nVolume = ComputeVolume(Vol, gHeliSfxRanges[i].m_fMaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nCounter = i + 65;
				m_sQueueSample.m_nSampleIndex = i + SFX_HELI_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nPriority = 0;
				m_sQueueSample.m_nFrequency = 1200 * heli->m_nHeliId + SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nLoopCount = 0;
				SET_EMITTING_VOLUME(Vol);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_fSpeedMultiplier = 6.0f;
				m_sQueueSample.m_MaxDistance = gHeliSfxRanges[i].m_fMaxDistance;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 3;
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}
		return TRUE;
	}
	return FALSE;
}

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
		debug("Plane Model Id is %d\n, ", params.m_pVehicle->GetModelIndex());
		break;
	}
}

#pragma region JUMBO
uint8 gJumboVolOffsetPercentage;

void
DoJumboVolOffset()
{
	if (!(AudioManager.m_FrameCounter % (AudioManager.m_anRandomTable[0] % 6 + 3)))
		gJumboVolOffsetPercentage = AudioManager.m_anRandomTable[1] % 60;
}

void
cAudioManager::ProcessJumbo(cVehicleParams& params)
{
	CPlane *plane;
	float position;

	if (params.m_fDistance < SQR(JUMBO_MAX_DIST)) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		plane = (CPlane *)params.m_pVehicle;
		DoJumboVolOffset();
		position = PlanePathPosition[plane->m_nPlaneId];
		if (position > TakeOffPoint) {
			if (300.0f + TakeOffPoint < position) {
				if (LandingPoint - 350.0f < position) {
					if (position > LandingPoint) {
						if (plane->m_fSpeed > 0.103344f)
							ProcessJumboDecel(plane);
						else
							ProcessJumboTaxi();
					}
					else
						ProcessJumboLanding(plane);
				}
				else
					ProcessJumboFlying();
			} else
				ProcessJumboTakeOff(plane);
		} else {
			if (plane->m_fSpeed > 0.103344f)
				ProcessJumboAccel(plane);
			else
				ProcessJumboTaxi();
		}
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
	uint32 engineFreq;
	uint8 vol;
	float modificator;
	float freqMult;

	if (SetupJumboFlySound(20)) {
		modificator = Min(1.0f, (plane->m_fSpeed - 0.103344f) * 1.6760077f);
		if (SetupJumboRumbleSound(MAX_VOLUME * modificator) && SetupJumboTaxiSound((1.0f - modificator) * 75)) {
			if (modificator >= 0.2f) {
				freqMult = 1;
				engineFreq = 22050;
				vol = MAX_VOLUME;
			} else {
				freqMult = modificator * 5;
				vol = freqMult * MAX_VOLUME;
				engineFreq = freqMult * 6050 + 16000;
			}
			SetupJumboEngineSound(vol, engineFreq);
			SetupJumboWhineSound(18, 14600 * freqMult + 29500);
		}
	}
}

void
cAudioManager::ProcessJumboTakeOff(CPlane *plane)
{
	float modificator = (PlanePathPosition[plane->m_nPlaneId] - TakeOffPoint) / 300;
	if (SetupJumboFlySound((107 * modificator) + 20) && SetupJumboRumbleSound(MAX_VOLUME * (1.0f - modificator))) {
		if (SetupJumboEngineSound(MAX_VOLUME, 22050))
			SetupJumboWhineSound(18 * (1.0f - modificator), 44100);
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
	float modificator = (LandingPoint - PlanePathPosition[plane->m_nPlaneId]) / 350;
	if (SetupJumboFlySound(107 * modificator + 20)) {
		if (SetupJumboTaxiSound(75 * (1.0f - modificator))) {
			SetupJumboEngineSound(MAX_VOLUME, 22050);
			SetupJumboWhineSound(18 * (1.0f - modificator), 14600 * modificator + 29500);
		}
	}
}

void
cAudioManager::ProcessJumboDecel(CPlane *plane)
{
	if (SetupJumboFlySound(20) && SetupJumboTaxiSound(75)) {
		float modificator = Min(1.0f, (plane->m_fSpeed - 0.103344f) * 1.6760077f);
		SetupJumboEngineSound(MAX_VOLUME * modificator, 6050 * modificator + 16000);
		SetupJumboWhineSound(18, 29500);
	}
}

bool8
cAudioManager::SetupJumboTaxiSound(uint8 vol)
{
	if (m_sQueueSample.m_fDistance < JUMBO_ENGINE_SOUND_MAX_DIST) {
		uint8 Vol = (vol >> 1) + ((vol >> 1) * m_sQueueSample.m_fDistance / JUMBO_ENGINE_SOUND_MAX_DIST);

		if (m_sQueueSample.m_fDistance / JUMBO_ENGINE_SOUND_MAX_DIST < 0.7f)
			Vol -= Vol * gJumboVolOffsetPercentage / 100;
		m_sQueueSample.m_nVolume = ComputeVolume(Vol, JUMBO_ENGINE_SOUND_MAX_DIST, m_sQueueSample.m_fDistance);

		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 1;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = GetJumboTaxiFreq();
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(Vol);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_MaxDistance = JUMBO_ENGINE_SOUND_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 4;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::SetupJumboWhineSound(uint8 Vol, uint32 freq)
{
	if (m_sQueueSample.m_fDistance < JUMBO_WHINE_SOUND_MAX_DIST) {
		m_sQueueSample.m_nVolume = ComputeVolume(Vol, JUMBO_WHINE_SOUND_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 2;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_WHINE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = freq;
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(Vol);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_MaxDistance = JUMBO_WHINE_SOUND_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 4;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::SetupJumboEngineSound(uint8 Vol, uint32 freq)
{
	if (m_sQueueSample.m_fDistance < JUMBO_ENGINE_SOUND_MAX_DIST) {
		uint8 FinalVol = Vol - gJumboVolOffsetPercentage / 100;
		m_sQueueSample.m_nVolume = ComputeVolume(FinalVol, JUMBO_ENGINE_SOUND_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 3;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_ENGINE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = freq;
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(FinalVol);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_MaxDistance = JUMBO_ENGINE_SOUND_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 4;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::SetupJumboFlySound(uint8 Vol)
{
	if (m_sQueueSample.m_fDistance < JUMBO_MAX_DIST) {
		m_sQueueSample.m_nVolume = ComputeVolume(Vol, JUMBO_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_DIST_FLY;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_JUMBO_DIST_FLY);
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(Vol);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_MaxDistance = JUMBO_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 5;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		return TRUE;
	}
	return FALSE;
}

bool8
cAudioManager::SetupJumboRumbleSound(uint8 Vol)
{
	if (m_sQueueSample.m_fDistance < JUMBO_RUMBLE_SOUND_MAX_DIST) {
		m_sQueueSample.m_nVolume = ComputeVolume(Vol, JUMBO_RUMBLE_SOUND_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 5;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_RUMBLE;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = TRUE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_JUMBO_RUMBLE);
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(Vol);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_MaxDistance = JUMBO_RUMBLE_SOUND_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 12;
			m_sQueueSample.m_nPan = 0;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
			m_sQueueSample.m_nCounter = 6;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_RUMBLE;
			m_sQueueSample.m_nFrequency += 200;
			m_sQueueSample.m_nPan = 127;
			AddSampleToRequestedQueue();
		}
		return TRUE;
	}
	return FALSE;
}

int32
cAudioManager::GetJumboTaxiFreq()
{
	return (1.0f / 180 * 10950 * m_sQueueSample.m_fDistance) + 22050;
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
	if (ped->GetModelIndex() == MI_FATMALE02)
		ProcessPedHeadphones(params);
	ProcessPedOneShots(params);
}

void
cAudioManager::ProcessPedHeadphones(cPedParams &params)
{
	CPed *ped;
	CAutomobile *veh;
	uint8 Vol;

	if (params.m_fDistance < SQR(PED_HEADPHONES_MAX_DIST)) {
		ped = params.m_pPed;
		if (ped->bBodyPartJustCameOff && ped->m_bodyPartBleeding == PED_HEAD)
			return;

		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		if (ped->bInVehicle && ped->m_nPedState == PED_DRIVING) {
			Vol = PED_HEADPHONES_IN_CAR_VOLUME;
			veh = (CAutomobile *)ped->m_pMyVehicle;
			if (veh && veh->IsCar()) {
				for (int32 i = DOOR_FRONT_LEFT; i < ARRAY_SIZE(veh->Doors); i++) {
					if (!veh->IsDoorClosed((eDoors)i) || veh->IsDoorMissing((eDoors)i)) {
						Vol = PED_HEADPHONES_VOLUME;
						break;
					}
				}
			}
		} else
			Vol = PED_HEADPHONES_VOLUME;

		m_sQueueSample.m_nVolume = ComputeVolume(Vol, PED_HEADPHONES_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 64;
			m_sQueueSample.m_nSampleIndex = SFX_HEADPHONES;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_HEADPHONES);
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(Vol);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_MaxDistance = PED_HEADPHONES_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 5;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessPedOneShots(cPedParams &params)
{
	uint8 Vol;
	uint32 sampleIndex;

	CPed *ped = params.m_pPed;

	bool8 narrowSoundRange;
	int16 sound;
	bool8 stereo;
	CWeapon *weapon;
#ifdef FIX_BUGS
	float maxDist = 0.0f; // uninitialized variable
#else
	float maxDist;
#endif

	static uint8 iSound = 21;

	weapon = params.m_pPed->GetWeapon();
	for (uint32 i = 0; i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; i++) {
		stereo = FALSE;
		narrowSoundRange = FALSE;
		SET_SOUND_REFLECTION(FALSE);
		sound = m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i];
		switch (sound) {
		case SOUND_FALL_LAND:
		case SOUND_FALL_COLLAPSE:
			if (ped->bIsInTheAir)
				continue;
			maxDist = SQR(PED_ONE_SHOT_FALL_MAX_DIST);
			Vol = m_anRandomTable[3] % 20 + PED_ONE_SHOT_FALL_VOLUME;
			if (ped->m_nSurfaceTouched == SURFACE_WATER)
				m_sQueueSample.m_nSampleIndex = (m_anRandomTable[3] % 4) + SFX_FOOTSTEP_WATER_1;
			else if (sound == SOUND_FALL_LAND)
				m_sQueueSample.m_nSampleIndex = SFX_BODY_LAND;
			else
				m_sQueueSample.m_nSampleIndex = SFX_BODY_LAND_AND_FALL;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency / 17);
			m_sQueueSample.m_nPriority = 2;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_FALL_MAX_DIST;
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			SET_EMITTING_VOLUME(Vol);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
			SET_SOUND_REFLECTION(TRUE);
			break;
		case SOUND_STEP_START:
		case SOUND_STEP_END:
			if (params.m_pPed->bIsInTheAir)
				continue;
			Vol = m_anRandomTable[3] % 15 + PED_ONE_SHOT_STEP_VOLUME;
			if (FindPlayerPed() != m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity)
				Vol >>= 1;
			maxDist = SQR(PED_ONE_SHOT_STEP_MAX_DIST);
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
				Vol >>= 2;
				m_sQueueSample.m_nFrequency = 9 * m_sQueueSample.m_nFrequency / 10;
				break;
			case PEDMOVE_RUN:
				Vol >>= 1;
				m_sQueueSample.m_nFrequency = 11 * m_sQueueSample.m_nFrequency / 10;
				break;
			case PEDMOVE_SPRINT:
				m_sQueueSample.m_nFrequency = 12 * m_sQueueSample.m_nFrequency / 10;
				break;
			default:
				break;
			}
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_STEP_MAX_DIST;
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			SET_EMITTING_VOLUME(Vol);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
			SET_SOUND_REFLECTION(TRUE);
			break;
		case SOUND_WEAPON_AK47_BULLET_ECHO:
		case SOUND_WEAPON_UZI_BULLET_ECHO:
		case SOUND_WEAPON_M16_BULLET_ECHO:
			m_sQueueSample.m_nSampleIndex = SFX_UZI_END_LEFT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_UZI_END_LEFT);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_BULLET_ECHO_MAX_DIST;
			maxDist = SQR(PED_ONE_SHOT_WEAPON_BULLET_ECHO_MAX_DIST);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			Vol = m_anRandomTable[4] % 10 + PED_ONE_SHOT_WEAPON_BULLET_ECHO_VOLUME;
			SET_EMITTING_VOLUME(Vol);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
#ifdef AUDIO_REFLECTIONS
			if (m_bDynamicAcousticModelingStatus)
				m_sQueueSample.m_bReflections = TRUE;
			else
#endif
				stereo = TRUE;
			break;
		case SOUND_WEAPON_FLAMETHROWER_FIRE:
			m_sQueueSample.m_nSampleIndex = SFX_FLAMETHROWER_START_LEFT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_FLAMETHROWER_START_LEFT);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_FLAMETHROWER_FIRE_MAX_DIST;
			maxDist = SQR(PED_ONE_SHOT_WEAPON_FLAMETHROWER_FIRE_MAX_DIST);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			Vol = PED_ONE_SHOT_WEAPON_FLAMETHROWER_FIRE_VOLUME;
			SET_EMITTING_VOLUME(PED_ONE_SHOT_WEAPON_FLAMETHROWER_FIRE_VOLUME);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
			break;
		case SOUND_WEAPON_SHOT_FIRED:
			weapon = ped->GetWeapon();
			switch (weapon->m_eWeaponType) {
			case WEAPONTYPE_COLT45:
				m_sQueueSample.m_nSampleIndex = SFX_COLT45_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_COLT45_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_COLT45_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_COLT45_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				Vol = m_anRandomTable[1] % 10 + PED_ONE_SHOT_WEAPON_COLT45_VOLUME;
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = TRUE;
#ifdef AUDIO_REFLECTIONS
				if (m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bReflections = TRUE;
				else
#endif
					stereo = TRUE;
				break;
			case WEAPONTYPE_ROCKETLAUNCHER:
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ROCKET_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.m_nPriority = 1;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_ROCKETLAUNCHER_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_ROCKETLAUNCHER_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				Vol = m_anRandomTable[0] % 20 + PED_ONE_SHOT_WEAPON_ROCKETLAUNCHER_VOLUME;
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = TRUE;
#ifdef AUDIO_REFLECTIONS
				if (m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bReflections = TRUE;
				else
#endif
					stereo = TRUE;
				break;
			case WEAPONTYPE_FLAMETHROWER:
				m_sQueueSample.m_nSampleIndex = SFX_FLAMETHROWER_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = 9;
				Vol = PED_ONE_SHOT_WEAPON_FLAMETHROWER_VOLUME;
				m_sQueueSample.m_nFrequency = (10 * m_sQueueSample.m_nEntityIndex % 2048) + SampleManager.GetSampleBaseFrequency(SFX_FLAMETHROWER_LEFT);
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 4.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_FLAMETHROWER_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_FLAMETHROWER_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 0;
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				SET_EMITTING_VOLUME(PED_ONE_SHOT_WEAPON_FLAMETHROWER_VOLUME);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nFramesToPlay = 6;
#ifdef AUDIO_REFLECTIONS
				if (m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bReflections = TRUE;
				else
#endif
					stereo = TRUE;
				break;
			case WEAPONTYPE_AK47:
				m_sQueueSample.m_nSampleIndex = SFX_AK47_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_AK47_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_AK47_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_AK47_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				Vol = m_anRandomTable[1] % 15 + PED_ONE_SHOT_WEAPON_AK47_VOLUME;
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = TRUE;
				break;
			case WEAPONTYPE_UZI:
				m_sQueueSample.m_nSampleIndex = SFX_UZI_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_UZI_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_UZI_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_UZI_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				Vol = m_anRandomTable[3] % 15 + PED_ONE_SHOT_WEAPON_UZI_VOLUME;
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = TRUE;
				break;
			case WEAPONTYPE_SNIPERRIFLE:
				m_sQueueSample.m_nSampleIndex = SFX_SNIPER_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SNIPER_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_SNIPERRIFLE_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_SNIPERRIFLE_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				Vol = m_anRandomTable[4] % 10 + PED_ONE_SHOT_WEAPON_SNIPERRIFLE_VOLUME;
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = TRUE;
#ifdef AUDIO_REFLECTIONS
				if (m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bReflections = TRUE;
				else
#endif
					stereo = TRUE;
				break;
			case WEAPONTYPE_SHOTGUN:
				m_sQueueSample.m_nSampleIndex = SFX_SHOTGUN_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SHOTGUN_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_SHOTGUN_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_SHOTGUN_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				Vol = m_anRandomTable[2] % 10 + PED_ONE_SHOT_WEAPON_SHOTGUN_VOLUME;
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = TRUE;
#ifdef AUDIO_REFLECTIONS
				if (m_bDynamicAcousticModelingStatus)
					m_sQueueSample.m_bReflections = TRUE;
				else
#endif
					stereo = TRUE;
				break;
			case WEAPONTYPE_M16:
				m_sQueueSample.m_nSampleIndex = SFX_M16_LEFT;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nCounter = iSound++;
				narrowSoundRange = TRUE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_M16_LEFT);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_M16_MAX_DIST;
				maxDist = SQR(PED_ONE_SHOT_WEAPON_M16_MAX_DIST);
				m_sQueueSample.m_nLoopCount = 1;
				RESET_LOOP_OFFSETS
				Vol = m_anRandomTable[4] % 15 + PED_ONE_SHOT_WEAPON_M16_VOLUME;
				SET_EMITTING_VOLUME(Vol);
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_bStatic = TRUE;
				break;
			default:
				continue;
			}

			break;
		case SOUND_WEAPON_RELOAD:
			weapon = &ped->m_weapons[ped->m_currentWeapon];
			switch (weapon->m_eWeaponType) {
			case WEAPONTYPE_COLT45:
				m_sQueueSample.m_nSampleIndex = SFX_PISTOL_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PISTOL_RELOAD) + RandomDisplacement(300);
				break;
			case WEAPONTYPE_UZI:
				m_sQueueSample.m_nSampleIndex = SFX_M16_RELOAD;
				m_sQueueSample.m_nFrequency = 39243;
				break;
			case WEAPONTYPE_AK47:
				m_sQueueSample.m_nSampleIndex = SFX_AK47_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_AK47_RELOAD);
				break;
			case WEAPONTYPE_M16:
				m_sQueueSample.m_nSampleIndex = SFX_M16_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_M16_RELOAD);
				break;
			case WEAPONTYPE_SHOTGUN:
				m_sQueueSample.m_nSampleIndex = SFX_AK47_RELOAD;
				m_sQueueSample.m_nFrequency = 30290;
				break;
			case WEAPONTYPE_ROCKETLAUNCHER:
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ROCKET_RELOAD);
				break;
			case WEAPONTYPE_SNIPERRIFLE:
				m_sQueueSample.m_nSampleIndex = SFX_RIFLE_RELOAD;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RIFLE_RELOAD);
				break;
			default:
				continue;
			}
			Vol = PED_ONE_SHOT_WEAPON_RELOAD_VOLUME;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency += RandomDisplacement(300);
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_RELOAD_MAX_DIST;
			maxDist = SQR(PED_ONE_SHOT_WEAPON_RELOAD_MAX_DIST);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			SET_EMITTING_VOLUME(PED_ONE_SHOT_WEAPON_RELOAD_VOLUME);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
			SET_SOUND_REFLECTION(TRUE);
			break;
		case SOUND_WEAPON_HIT_PED:
			m_sQueueSample.m_nSampleIndex = SFX_BULLET_PED;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BULLET_PED);
			m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 3);
			m_sQueueSample.m_nPriority = 7;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_WEAPON_HIT_PED_MAX_DIST;
			maxDist = SQR(PED_ONE_SHOT_WEAPON_HIT_PED_MAX_DIST);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			Vol = m_anRandomTable[0] % 20 + PED_ONE_SHOT_WEAPON_HIT_PED_VOLUME;
			SET_EMITTING_VOLUME(Vol);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
			break;
		case SOUND_WEAPON_BAT_ATTACK:
			m_sQueueSample.m_nSampleIndex = SFX_BAT_HIT_LEFT;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency = RandomDisplacement(2000) + 22000;
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_PUNCH_MAX_DIST;
			maxDist = SQR(PED_ONE_SHOT_PUNCH_MAX_DIST);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			Vol = m_anRandomTable[2] % 20 + PED_ONE_SHOT_PUNCH_VOLUME;
			SET_EMITTING_VOLUME(Vol);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
#ifdef AUDIO_REFLECTIONS
			if (m_bDynamicAcousticModelingStatus)
				m_sQueueSample.m_bReflections = TRUE;
			else
#endif
				stereo = TRUE;
			break;
		case SOUND_FIGHT_PUNCH_33:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_1;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_KICK_34:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_1;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_HEADBUTT_35:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_1;
			m_sQueueSample.m_nFrequency = 20000;
			goto AddFightSound;
		case SOUND_FIGHT_PUNCH_36:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_2;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_PUNCH_37:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_2;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_CLOSE_PUNCH_38:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_2;
			m_sQueueSample.m_nFrequency = 20000;
			goto AddFightSound;
		case SOUND_FIGHT_PUNCH_39:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_4;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_PUNCH_OR_KICK_BELOW_40:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_4;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_PUNCH_41:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_4;
			m_sQueueSample.m_nFrequency = 20000;
			goto AddFightSound;
		case SOUND_FIGHT_PUNCH_FROM_BEHIND_42:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_5;
			m_sQueueSample.m_nFrequency = 18000;
			goto AddFightSound;
		case SOUND_FIGHT_KNEE_OR_KICK_43:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_5;
			m_sQueueSample.m_nFrequency = 16500;
			goto AddFightSound;
		case SOUND_FIGHT_KICK_44:
			m_sQueueSample.m_nSampleIndex = SFX_FIGHT_5;
			m_sQueueSample.m_nFrequency = 20000;
		AddFightSound:
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound;
			narrowSoundRange = TRUE;
			iSound++;
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_PUNCH_MAX_DIST;
			maxDist = SQR(PED_ONE_SHOT_PUNCH_MAX_DIST);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			Vol = m_anRandomTable[3] % 26 + PED_ONE_SHOT_PUNCH_VOLUME;
			SET_EMITTING_VOLUME(Vol);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
			SET_SOUND_REFLECTION(TRUE);
			break;
		case SOUND_SPLASH:
			m_sQueueSample.m_nSampleIndex = SFX_SPLASH_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nCounter = iSound++;
			narrowSoundRange = TRUE;
			m_sQueueSample.m_nFrequency = RandomDisplacement(1400) + 20000;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_fSpeedMultiplier = 0.0f;
			m_sQueueSample.m_MaxDistance = PED_ONE_SHOT_SPLASH_MAX_DIST;
			maxDist = SQR(PED_ONE_SHOT_SPLASH_MAX_DIST);
			m_sQueueSample.m_nLoopCount = 1;
			RESET_LOOP_OFFSETS
			Vol = m_anRandomTable[2] % 30 + PED_ONE_SHOT_SPLASH_PED_VOLUME;
			SET_EMITTING_VOLUME(Vol);
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_bStatic = TRUE;
			SET_SOUND_REFLECTION(TRUE);
			break;
		default:
			SetupPedComments(params, sound);
			continue;
		}

		if (narrowSoundRange && iSound > 60)
			iSound = 21;
		if (params.m_fDistance < maxDist) {
			CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				if (stereo) {
					if (m_sQueueSample.m_fDistance < 0.2f * m_sQueueSample.m_MaxDistance) {
						m_sQueueSample.m_bIs2D = TRUE;
						m_sQueueSample.m_nPan = 0;
					} else
						stereo = FALSE;
				}
				m_sQueueSample.m_bReverb = TRUE;
				AddSampleToRequestedQueue();
				if (stereo) {
					m_sQueueSample.m_nPan = 127;
					m_sQueueSample.m_nSampleIndex++;
					if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i] == SOUND_WEAPON_SHOT_FIRED &&
					    weapon->m_eWeaponType == WEAPONTYPE_FLAMETHROWER)
						m_sQueueSample.m_nCounter++;
					else {
						m_sQueueSample.m_nCounter = iSound++;
						if (iSound > 60)
							iSound = 21;
					}
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::SetupPedComments(cPedParams &params, uint16 sound)
{
	CPed *ped = params.m_pPed;
	uint8 Vol;
	float maxDist;
	tPedComment pedComment;

	if (ped != nil) {
		switch (sound) {
		case SOUND_AMMUNATION_WELCOME_1:
			pedComment.m_nSampleIndex = SFX_AMMU_D;
			break;
		case SOUND_AMMUNATION_WELCOME_2:
			pedComment.m_nSampleIndex = SFX_AMMU_E;
			break;
		case SOUND_AMMUNATION_WELCOME_3:
			pedComment.m_nSampleIndex = SFX_AMMU_F;
			break;
		default:
			pedComment.m_nSampleIndex = GetPedCommentSfx(ped, sound);
			if (pedComment.m_nSampleIndex == NO_SAMPLE)
				return;
			break;
		}

		maxDist = PED_COMMENT_MAX_DIST;
	} else {
		switch (sound) {
#ifdef GTA_PS2
		case SOUND_PAGER:
			maxDist = PED_COMMENT_MAX_DIST;
			pedComment.m_nSampleIndex = SFX_PAGER;
			break;
#endif
		case SOUND_PED_HELI_PLAYER_FOUND:
			maxDist = PED_COMMENT_POLICE_HELI_MAX_DIST;
			pedComment.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % 4] % 29 + SFX_POLICE_HELI_1;
			break;
		case SOUND_PED_BODYCAST_HIT:
			if (CTimer::GetTimeInMilliseconds() <= gNextCryTime)
				return;
			maxDist = PED_COMMENT_MAX_DIST;
			gNextCryTime = CTimer::GetTimeInMilliseconds() + 500;
			pedComment.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % 4] % 4 + SFX_PLASTER_BLOKE_1;
			break;
		case SOUND_INJURED_PED_MALE_OUCH:
		case SOUND_INJURED_PED_MALE_PRISON:
			maxDist = PED_COMMENT_MAX_DIST;
			pedComment.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % 4] % 15 + SFX_GENERIC_MALE_GRUNT_1;
			break;
		case SOUND_INJURED_PED_FEMALE:
			maxDist = PED_COMMENT_MAX_DIST;
			pedComment.m_nSampleIndex = m_anRandomTable[m_sQueueSample.m_nEntityIndex % 4] % 11 + SFX_GENERIC_FEMALE_GRUNT_1;
			break;
		default:
			return;
		}
	}

	if (params.m_fDistance < SQR(maxDist)) {
		CalculateDistance(params.m_bDistanceCalculated, params.m_fDistance);
		if (sound != SOUND_PAGER) {
			switch (sound) {
			case SOUND_AMMUNATION_WELCOME_1:
			case SOUND_AMMUNATION_WELCOME_2:
			case SOUND_AMMUNATION_WELCOME_3:
				Vol = PED_COMMENT_VOLUME;
				break;
			default:
				if (CWorld::GetIsLineOfSightClear(TheCamera.GetPosition(), m_sQueueSample.m_vecPos, true, false, false, false, false, false))
					Vol = PED_COMMENT_VOLUME;
				else
					Vol = PED_COMMENT_VOLUME_BEHIND_WALL;
				break;
			}
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, maxDist, m_sQueueSample.m_fDistance);
			pedComment.m_nLoadingTimeout = 10;
			if (m_sQueueSample.m_nVolume > 0) {
				pedComment.m_nEntityIndex = m_sQueueSample.m_nEntityIndex;
				pedComment.m_vecPos = m_sQueueSample.m_vecPos;
				pedComment.m_fDistance = m_sQueueSample.m_fDistance;
				pedComment.m_nVolume = m_sQueueSample.m_nVolume;
#if defined(EXTERNAL_3D_SOUND) && defined(FIX_BUGS)
				pedComment.m_nEmittingVolume = Vol;
#endif
				m_sPedComments.Add(&pedComment);
			}
		}
#ifdef GTA_PS2
		else {
			m_sQueueSample.m_nVolume = MAX_VOLUME;
			pedComment.m_nLoadingTimeout = 40;
		}
#endif
	}
}

int32
cAudioManager::GetPedCommentSfx(CPed *ped, uint16 sound)
{
	if (ped->IsPlayer())
		return GetPlayerTalkSfx(sound);

	switch (ped->GetModelIndex()) {
	case MI_COP:
		return GetCopTalkSfx(sound);
	case MI_SWAT:
		return GetSwatTalkSfx(sound);
	case MI_FBI:
		return GetFBITalkSfx(sound);
	case MI_ARMY:
		return GetArmyTalkSfx(sound);
	case MI_MEDIC:
		return GetMedicTalkSfx(sound);
	case MI_FIREMAN:
		return GetFiremanTalkSfx(sound);
	case MI_MALE01:
		return GetNormalMaleTalkSfx(sound);
	case MI_TAXI_D:
		return GetAsianTaxiDriverTalkSfx(sound);
	case MI_PIMP:
		return GetPimpTalkSfx(sound);
	case MI_GANG01:
	case MI_GANG02:
		return GetMafiaTalkSfx(sound);
	case MI_GANG03:
	case MI_GANG04:
		return GetTriadTalkSfx(sound);
	case MI_GANG05:
	case MI_GANG06:
		return GetDiabloTalkSfx(sound);
	case MI_GANG07:
	case MI_GANG08:
		return GetYakuzaTalkSfx(sound);
	case MI_GANG09:
	case MI_GANG10:
		return GetYardieTalkSfx(sound);
	case MI_GANG11:
	case MI_GANG12:
		return GetColumbianTalkSfx(sound);
	case MI_GANG13:
	case MI_GANG14:
		return GetHoodTalkSfx(sound);
	case MI_CRIMINAL01:
		return GetBlackCriminalTalkSfx(sound);
	case MI_CRIMINAL02:
		return GetWhiteCriminalTalkSfx(sound);
	case MI_SPECIAL01:
	case MI_SPECIAL02:
	case MI_SPECIAL03:
	case MI_SPECIAL04:
		return GetSpecialCharacterTalkSfx(ped->GetModelIndex(), sound);
	case MI_MALE02:
		return GetCasualMaleOldTalkSfx(sound);
	case MI_MALE03:
	case MI_P_MAN1:
	case MI_P_MAN2:
		return GetBlackProjectMaleTalkSfx(sound, ped->GetModelIndex());
	case MI_FATMALE01:
		return GetWhiteFatMaleTalkSfx(sound);
	case MI_FATMALE02:
		return GetBlackFatMaleTalkSfx(sound);
	case MI_FEMALE01:
		return GetBlackCasualFemaleTalkSfx(sound);
	case MI_FEMALE02:
	case MI_CAS_WOM:
		return GetWhiteCasualFemaleTalkSfx(sound);
	case MI_FEMALE03:
		return GetFemaleNo3TalkSfx(sound);
	case MI_FATFEMALE01:
		return GetBlackFatFemaleTalkSfx(sound);
	case MI_FATFEMALE02:
		return GetWhiteFatFemaleTalkSfx(sound);
	case MI_PROSTITUTE:
		return GetBlackFemaleProstituteTalkSfx(sound);
	case MI_PROSTITUTE2:
		return GetWhiteFemaleProstituteTalkSfx(sound);
	case MI_P_WOM1:
		return GetBlackProjectFemaleOldTalkSfx(sound);
	case MI_P_WOM2:
		return GetBlackProjectFemaleYoungTalkSfx(sound);
	case MI_CT_MAN1:
		return GetChinatownMaleOldTalkSfx(sound);
	case MI_CT_MAN2:
		return GetChinatownMaleYoungTalkSfx(sound);
	case MI_CT_WOM1:
		return GetChinatownFemaleOldTalkSfx(sound);
	case MI_CT_WOM2:
		return GetChinatownFemaleYoungTalkSfx(sound);
	case MI_LI_MAN1:
	case MI_LI_MAN2:
		return GetLittleItalyMaleTalkSfx(sound);
	case MI_LI_WOM1:
		return GetLittleItalyFemaleOldTalkSfx(sound);
	case MI_LI_WOM2:
		return GetLittleItalyFemaleYoungTalkSfx(sound);
	case MI_DOCKER1:
		return GetWhiteDockerMaleTalkSfx(sound);
	case MI_DOCKER2:
		return GetBlackDockerMaleTalkSfx(sound);
	case MI_SCUM_MAN:
		return GetScumMaleTalkSfx(sound);
	case MI_SCUM_WOM:
		return GetScumFemaleTalkSfx(sound);
	case MI_WORKER1:
		return GetWhiteWorkerMaleTalkSfx(sound);
	case MI_WORKER2:
		return GetBlackWorkerMaleTalkSfx(sound);
	case MI_B_MAN1:
	case MI_B_MAN3:
		return GetBusinessMaleYoungTalkSfx(sound, ped->GetModelIndex());
	case MI_B_MAN2:
		return GetBusinessMaleOldTalkSfx(sound);
	case MI_B_WOM1:
	case MI_B_WOM2:
		return GetWhiteBusinessFemaleTalkSfx(sound, ped->GetModelIndex());
	case MI_B_WOM3:
		return GetBlackBusinessFemaleTalkSfx(sound);
	case MI_MOD_MAN:
		return GetSupermodelMaleTalkSfx(sound);
	case MI_MOD_WOM:
		return GetSupermodelFemaleTalkSfx(sound);
	case MI_ST_MAN:
		return GetStewardMaleTalkSfx(sound);
	case MI_ST_WOM:
		return GetStewardFemaleTalkSfx(sound);
	case MI_FAN_MAN1:
	case MI_FAN_MAN2:
		return GetFanMaleTalkSfx(sound, ped->GetModelIndex());
	case MI_FAN_WOM:
		return GetFanFemaleTalkSfx(sound);
	case MI_HOS_MAN:
		return GetHospitalMaleTalkSfx(sound);
	case MI_HOS_WOM:
		return GetHospitalFemaleTalkSfx(sound);
	case MI_CONST1:
		return GetWhiteConstructionWorkerTalkSfx(sound);
	case MI_CONST2:
		return GetBlackConstructionWorkerTalkSfx(sound);
	case MI_SHOPPER1:
	case MI_SHOPPER2:
	case MI_SHOPPER3:
		return GetShopperFemaleTalkSfx(sound, ped->GetModelIndex());
	case MI_STUD_MAN:
		return GetStudentMaleTalkSfx(sound);
	case MI_STUD_WOM:
		return GetStudentFemaleTalkSfx(sound);
	case MI_CAS_MAN:
		return GetCasualMaleYoungTalkSfx(sound);
	default:
		return GetGenericMaleTalkSfx(sound);
	}
}

void
cAudioManager::GetPhrase(uint32 &phrase, uint32 &prevPhrase, uint32 sample, uint32 maxOffset)
{
	phrase = sample + m_anRandomTable[m_sQueueSample.m_nEntityIndex & 3] % maxOffset;

	// check if the same sfx like last time, if yes, then try use next one,
	// if exceeded range, then choose first available sample
	if (phrase == prevPhrase && ++phrase >= sample + maxOffset)
		phrase = sample;
	prevPhrase = phrase;
}

#pragma region PED_COMMENTS

uint32
cAudioManager::GetPlayerTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_DAMAGE:
		GetPhrase(sfx, lastSfx, SFX_CLAUDE_HIGH_DAMAGE_GRUNT_1, 11);
		break;
	case SOUND_PED_HIT:
		GetPhrase(sfx, lastSfx, SFX_CLAUDE_LOW_DAMAGE_GRUNT_1, 10);
		break;
	case SOUND_PED_LAND:
		GetPhrase(sfx, lastSfx, SFX_CLAUDE_HIT_GROUND_GRUNT_1, 6);
		break;
	default:
		sfx = NO_SAMPLE;
		break;
	}
	return sfx;
}

uint32
cAudioManager::GetCopTalkSfx(uint16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_ARREST_COP:
		GetPhrase(sfx, lastSfx, SFX_COP_VOICE_1_ARREST_1, 6);
		break;
	case SOUND_PED_PURSUIT_COP:
		pedState = FindPlayerPed()->m_nPedState;
		if (pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(sfx, lastSfx, SFX_COP_VOICE_1_CHASE_1, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}

	return (SFX_COP_VOICE_2_ARREST_1 - SFX_COP_VOICE_1_ARREST_1) * (m_sQueueSample.m_nEntityIndex % 5) + sfx;
}

uint32
cAudioManager::GetSwatTalkSfx(uint16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_ARREST_SWAT:
		GetPhrase(sfx, lastSfx, SFX_SWAT_VOICE_1_CHASE_1, 6);
		break;
	case SOUND_PED_PURSUIT_SWAT:
		pedState = FindPlayerPed()->m_nPedState;
		if (pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(sfx, lastSfx, SFX_SWAT_VOICE_1_CHASE_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}

	return (SFX_SWAT_VOICE_2_CHASE_1 - SFX_SWAT_VOICE_1_CHASE_1) * (m_sQueueSample.m_nEntityIndex % 4) + sfx;
}

uint32
cAudioManager::GetFBITalkSfx(uint16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_ARREST_FBI:
		GetPhrase(sfx, lastSfx, SFX_FBI_VOICE_1_CHASE_1, 6);
		break;
	case SOUND_PED_PURSUIT_FBI:
		pedState = FindPlayerPed()->m_nPedState;
		if (pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE)
			return NO_SAMPLE;
		GetPhrase(sfx, lastSfx, SFX_FBI_VOICE_1_CHASE_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}

	return (SFX_FBI_VOICE_2_CHASE_1 - SFX_FBI_VOICE_1_CHASE_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetArmyTalkSfx(uint16 sound)
{
	uint32 sfx;
	PedState pedState;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_PURSUIT_ARMY:
		pedState = FindPlayerPed()->m_nPedState;
		if(pedState == PED_ARRESTED || pedState == PED_DEAD || pedState == PED_DIE) return NO_SAMPLE;
		GetPhrase(sfx, lastSfx, SFX_ARMY_VOICE_1_CHASE_1, 15);
		break;
	default: return GetGenericMaleTalkSfx(sound);
	}

	return (SFX_ARMY_VOICE_2_CHASE_1 - SFX_ARMY_VOICE_1_CHASE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetMedicTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_MEDIC_VOICE_1_GUN_PANIC_1, 5);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_MEDIC_VOICE_1_CARJACKED_1, 5);
		break;
	case SOUND_PED_HEALING:
		GetPhrase(sfx, lastSfx, SFX_MEDIC_VOICE_1_AT_VICTIM_1, 12);
		break;
	case SOUND_PED_LEAVE_VEHICLE:
		GetPhrase(sfx, lastSfx, SFX_MEDIC_VOICE_1_GET_OUT_VAN_CHAT_1, 9);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_MEDIC_VOICE_1_RUN_FROM_FIGHT_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return (SFX_MEDIC_VOICE_2_GUN_PANIC_1 - SFX_MEDIC_VOICE_1_GUN_PANIC_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetFiremanTalkSfx(uint16 sound)
{
	return GetGenericMaleTalkSfx(sound);
}

uint32
cAudioManager::GetBusinessMaleOldTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_MRUN_FROM_FIGHT_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_OLD_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBusinessMaleYoungTalkSfx(uint16 sound, uint32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_RUN_FROM_FIGHT_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BUSINESS_MALE_YOUNG_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}

	if (model == MI_B_MAN3)
		sfx += (SFX_BUSINESS_MALE_YOUNG_VOICE_2_DRIVER_ABUSE_1 - SFX_BUSINESS_MALE_YOUNG_VOICE_1_DRIVER_ABUSE_1);
	return sfx;
}

uint32
cAudioManager::GetMafiaTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(sfx, lastSfx, SFX_MAFIA_MALE_VOICE_1_CARJACKING_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_MAFIA_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_MAFIA_MALE_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_MAFIA_MALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_MAFIA_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_MAFIA_MALE_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_MAFIA_MALE_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return (SFX_MAFIA_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_MAFIA_MALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 3) + sfx;
}

uint32
cAudioManager::GetTriadTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_GUN_COOL_1, 3);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_CARJACKING_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_TRIAD_MALE_VOICE_1_CHAT_1, 8);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetDiabloTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_GUN_COOL_1, 4);
		break;
	case SOUND_PED_HANDS_COWER:
		sound = SOUND_PED_FLEE_SPRINT;
		return GetGenericMaleTalkSfx(sound);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_CARJACKING_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_EYING_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_DIABLO_MALE_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return (SFX_DIABLO_MALE_VOICE_2_CHAT_1 - SFX_DIABLO_MALE_VOICE_1_CHAT_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetYakuzaTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(sfx, lastSfx, SFX_YAKUZA_MALE_VOICE_1_CARJACKING_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_YAKUZA_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_YAKUZA_MALE_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_YAKUZA_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_YAKUZA_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_YAKUZA_MALE_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return (SFX_YAKUZA_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_YAKUZA_MALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetYardieTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		sfx = SFX_YARDIE_MALE_VOICE_1_GUN_COOL_1;
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(sfx, lastSfx, SFX_YARDIE_MALE_VOICE_1_CARJACKING_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		sfx = SFX_YARDIE_MALE_VOICE_1_CARJACKED_1;
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_YARDIE_MALE_VOICE_1_FIGHT_1, 6);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_YARDIE_MALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_YARDIE_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_YARDIE_MALE_VOICE_1_EYING_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_YARDIE_MALE_VOICE_1_CHAT_1, 8);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return (SFX_YARDIE_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_YARDIE_MALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetColumbianTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKING:
		GetPhrase(sfx, lastSfx, SFX_COLUMBIAN_MALE_VOICE_1_CARJACKING_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_COLUMBIAN_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_COLUMBIAN_MALE_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_COLUMBIAN_MALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_COLUMBIAN_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_COLUMBIAN_MALE_VOICE_1_EYING_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_COLUMBIAN_MALE_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return (SFX_COLUMBIAN_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_COLUMBIAN_MALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetHoodTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_GUN_COOL_1, 5);
		break;
	case SOUND_PED_CAR_JACKING:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_CARJACKING_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_FIGHT_1, 6);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_EYING_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_HOOD_MALE_VOICE_1_CHAT_1, 6);
		break;

	default:
		return GetGenericMaleTalkSfx(sound);
		break;
	}
	return (SFX_HOOD_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_HOOD_MALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetBlackCriminalTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CRIMINAL_VOICE_1_GUN_COOL_1, 4);
		break;
	case SOUND_PED_CAR_JACKING:
		sfx = SFX_BLACK_CRIMINAL_VOICE_1_CARJACKING_1;
		break;
	case SOUND_PED_MUGGING:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CRIMINAL_VOICE_1_MUGGING_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CRIMINAL_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CRIMINAL_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CRIMINAL_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
		break;
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteCriminalTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CRIMINAL_VOICE_1_GUN_COOL_1, 3);
		break;
	case SOUND_PED_CAR_JACKING:
		sfx = SFX_WHITE_CRIMINAL_VOICE_1_CARJACKING_1;
		break;
	case SOUND_PED_MUGGING:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CRIMINAL_VOICE_1_MUGGING_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CRIMINAL_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CRIMINAL_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CRIMINAL_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
		break;
	}
	return sfx;
}

uint32
cAudioManager::GetCasualMaleOldTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_CASUAL_MALE_OLD_VOICE_1_CARJACKED_1, 3);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_CASUAL_MALE_OLD_VOICE_1_MUGGED_1, 4);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_CASUAL_MALE_OLD_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_CASUAL_MALE_OLD_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_CASUAL_MALE_OLD_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_CASUAL_MALE_OLD_VOICE_1_EYING_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_CASUAL_MALE_OLD_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetCasualMaleYoungTalkSfx(uint16 sound)
{
	return GetGenericMaleTalkSfx(sound);
}

uint32
cAudioManager::GetBlackCasualFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_GUN_PANIC_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_MUGGED_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_RUN_FROM_FIGHT_1, 2);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_1_VOICE_1_CHAT_1, 8);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteCasualFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CASUAL_FEMALE_VOICE_1_GUN_PANIC_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CASUAL_FEMALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		sfx = SFX_WHITE_CASUAL_FEMALE_VOICE_1_MUGGED_1;
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CASUAL_FEMALE_VOICE_1_DODGE_1, 3);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CASUAL_FEMALE_VOICE_1_RUN_FROM_FIGHT_1, 2);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CASUAL_FEMALE_VOICE_1_DRIVER_ABUSE_1, 8);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CASUAL_FEMALE_VOICE_1_SHOCKED_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_CASUAL_FEMALE_VOICE_1_CHAT_1, 4);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetFemaleNo3TalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_GUN_PANIC_1, 5);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_CARJACKED_1, 3);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_MUGGED_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_RUN_FROM_FIGHT_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_FEMALE_3_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteBusinessFemaleTalkSfx(uint16 sound, uint32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_RUN_FROM_FIGHT_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_BUSINESS_FEMALE_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}

	if (model == MI_B_WOM2)
		sfx += (SFX_WHITE_BUSINESS_FEMALE_VOICE_2_DRIVER_ABUSE_1 - SFX_WHITE_BUSINESS_FEMALE_VOICE_1_DRIVER_ABUSE_1);
	return sfx;
}

uint32
cAudioManager::GetBlackFatFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_FEMALE_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_FEMALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_FEMALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_FEMALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_FEMALE_VOICE_1_SHOCKED_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_FEMALE_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteFatMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_MALE_VOICE_1_CARJACKED_1, 3); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_MALE_VOICE_1_MUGGED_1, 3); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_MALE_VOICE_1_DODGE_1, 9); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_MALE_VOICE_1_DRIVER_ABUSE_1, 9); break;
	case SOUND_PED_WAIT_DOUBLEBACK: GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_MALE_VOICE_1_LOST_1, 2); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_MALE_VOICE_1_CHAT_1, 9); break;
	default: return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackFatMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_MALE_VOICE_1_CARJACKED_1, 4);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_MALE_VOICE_1_MUGGED_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_MALE_VOICE_1_DODGE_1, 7);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_WAIT_DOUBLEBACK:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_MALE_VOICE_1_LOST_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_FAT_MALE_VOICE_1_CHAT_1, 8);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteFatFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_FEMALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_FEMALE_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_FEMALE_VOICE_1_DRIVER_ABUSE_1, 8);
		break;
	case SOUND_PED_WAIT_DOUBLEBACK:
		GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_FEMALE_VOICE_1_LOST_1, 2);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_FEMALE_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_FAT_FEMALE_VOICE_1_CHAT_1, 8);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackFemaleProstituteTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROSTITUTE_VOICE_1_GUN_COOL_1, 4);
		break;
	case SOUND_PED_ROBBED:
		sfx = SFX_BLACK_PROSTITUTE_VOICE_1_MUGGED_1;
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROSTITUTE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROSTITUTE_VOICE_1_DODGE_1, 3);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROSTITUTE_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	case SOUND_PED_SOLICIT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROSTITUTE_VOICE_1_SOLICIT_1, 8);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROSTITUTE_VOICE_1_CHAT_1, 4);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return (SFX_BLACK_PROSTITUTE_VOICE_2_CHAT_1 - SFX_BLACK_PROSTITUTE_VOICE_1_CHAT_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetWhiteFemaleProstituteTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_WHITE_PROSTITUTE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_WHITE_PROSTITUTE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_PROSTITUTE_VOICE_1_DODGE_1, 3);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_PROSTITUTE_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	case SOUND_PED_SOLICIT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_PROSTITUTE_VOICE_1_SOLICIT_1, 8);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_PROSTITUTE_VOICE_1_CHAT_1, 4);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return (SFX_WHITE_PROSTITUTE_VOICE_2_CHAT_1 - SFX_WHITE_PROSTITUTE_VOICE_1_CHAT_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetBlackProjectMaleTalkSfx(uint16 sound, uint32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch(sound) {
	case SOUND_PED_HANDS_UP: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_GUN_COOL_1, 3); break;
	case SOUND_PED_CAR_JACKED: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_CARJACKED_1, 2); break;
	case SOUND_PED_ROBBED: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_MUGGED_1, 2); break;
	case SOUND_PED_ATTACK: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_FIGHT_1, 6); break;
	case SOUND_PED_EVADE: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_DODGE_1, 5); break;
	case SOUND_PED_ANNOYED_DRIVER: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_DRIVER_ABUSE_1, 7); break;
	case SOUND_PED_CHAT_SEXY: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_EYING_1, 3); break;
	case SOUND_PED_CHAT: GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_MALE_VOICE_1_CHAT_1, 6); break;
	default: return GetGenericMaleTalkSfx(sound);
	}

	if (model == MI_P_MAN2)
		sfx += (SFX_BLACK_PROJECT_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_BLACK_PROJECT_MALE_VOICE_1_DRIVER_ABUSE_1);
	return sfx;
}

uint32
cAudioManager::GetBlackProjectFemaleOldTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_OLD_VOICE_1_CARJACKED_1, 6);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_OLD_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_OLD_VOICE_1_DODGE_1, 10);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_OLD_VOICE_1_RUN_FROM_FIGHT_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_OLD_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_OLD_VOICE_1_SHOCKED_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_OLD_VOICE_1_CHAT_1, 10);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackProjectFemaleYoungTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_YOUNG_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_CAR_JACKED:
		sfx = SFX_BLACK_PROJECT_FEMALE_YOUNG_VOICE_1_CARJACKED_1;
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_YOUNG_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_YOUNG_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_YOUNG_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_YOUNG_VOICE_1_SHOCKED_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_PROJECT_FEMALE_YOUNG_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownMaleOldTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_OLD_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_OLD_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_OLD_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_OLD_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_OLD_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_OLD_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_OLD_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownMaleYoungTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_YOUNG_VOICE_1_GUN_PANIC_1, 2);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_YOUNG_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_YOUNG_VOICE_1_FIGHT_1, 6);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_YOUNG_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_YOUNG_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_YOUNG_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_MALE_YOUNG_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownFemaleOldTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_OLD_FEMALE_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_OLD_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_OLD_FEMALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_OLD_FEMALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT_EVENT:
		sfx = SFX_CHINATOWN_OLD_FEMALE_VOICE_1_SHOCKED_1;
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_OLD_FEMALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChinatownFemaleYoungTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_YOUNG_FEMALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_YOUNG_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_YOUNG_FEMALE_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_YOUNG_FEMALE_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_YOUNG_FEMALE_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_CHINATOWN_YOUNG_FEMALE_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetLittleItalyMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_MALE_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_MALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_MALE_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_MALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_MALE_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_MALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return (SFX_LITTLE_ITALY_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_LITTLE_ITALY_MALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetLittleItalyFemaleOldTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_OLD_FEMALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_OLD_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_OLD_FEMALE_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_OLD_FEMALE_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_OLD_FEMALE_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_OLD_FEMALE_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetLittleItalyFemaleYoungTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_YOUNG_FEMALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_YOUNG_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_YOUNG_FEMALE_VOICE_1_DODGE_1, 7);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_YOUNG_FEMALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_YOUNG_FEMALE_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_LITTLE_ITALY_YOUNG_FEMALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteDockerMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_DOCKER_MALE_VOICE_1_GUN_PANIC_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_WHITE_DOCKER_MALE_VOICE_1_FIGHT_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_DOCKER_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_DOCKER_MALE_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_WHITE_DOCKER_MALE_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_DOCKER_MALE_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackDockerMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_DOCKER_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_BLACK_DOCKER_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_DOCKER_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_DOCKER_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_BLACK_DOCKER_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_DOCKER_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetScumMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_SCUM_MALE_VOICE_1_GUN_PANIC_1, 5);
		break;
	case SOUND_PED_ROBBED:
		sfx = SFX_SCUM_MALE_VOICE_1_MUGGED_1;
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_SCUM_MALE_VOICE_1_FIGHT_1, 10);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_SCUM_MALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_SCUM_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_WAIT_DOUBLEBACK:
		GetPhrase(sfx, lastSfx, SFX_SCUM_MALE_VOICE_1_LOST_1, 3);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_SCUM_MALE_VOICE_1_EYING_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_SCUM_MALE_VOICE_1_CHAT_1, 9);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetScumFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_SCUM_FEMALE_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_SCUM_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_SCUM_FEMALE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_SCUM_FEMALE_VOICE_1_DODGE_1, 8);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_SCUM_FEMALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_SCUM_FEMALE_VOICE_1_CHAT_1, 13);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteWorkerMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_WORKER_MALE_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_WHITE_WORKER_MALE_VOICE_1_FIGHT_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_WORKER_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_WORKER_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_WHITE_WORKER_MALE_VOICE_1_EYING_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_WORKER_MALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackWorkerMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_WORKER_MALE_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_BLACK_WORKER_MALE_VOICE_1_FIGHT_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_WORKER_MALE_VOICE_1_DODGE_1, 3);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_WORKER_MALE_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_BLACK_WORKER_MALE_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_WORKER_MALE_VOICE_1_CHAT_1, 4);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackBusinessFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_GUN_PANIC_1, 5);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_CARAJACKED_1, 4);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_MUGGED_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_RUN_FROM_FIGHT_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_BUSINESS_FEMALE_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetSupermodelMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_MODEL_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_MODEL_MALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_MODEL_MALE_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_MODEL_MALE_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_MODEL_MALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_MODEL_MALE_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_MODEL_MALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetSupermodelFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_MODEL_FEMALE_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_MODEL_FEMALE_VOICE_1_MUGGED_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_MODEL_FEMALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_MODEL_FEMALE_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_MODEL_FEMALE_VOICE_1_SHOCKED_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_MODEL_FEMALE_VOICE_1_CHAT_1, 8);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetStewardMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_MALE_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_MALE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_MALE_VOICE_1_DODGE_1, 3);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_MALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_MALE_VOICE_1_CHAT_1, 4);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetStewardFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_FEMALE_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_FEMALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_FEMALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_STEWARD_FEMALE_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return (SFX_STEWARD_FEMALE_VOICE_2_DRIVER_ABUSE_1 - SFX_STEWARD_FEMALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetFanMaleTalkSfx(uint16 sound, uint32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_MALE_VOICE_1_FIGHT_1, 3);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_MALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_MALE_VOICE_1_SHOCKED_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_MALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}

	if (model == MI_FAN_MAN2)
		sfx += (SFX_FOOTBALL_MALE_VOICE_2_DRIVER_ABUSE_1 - SFX_FOOTBALL_MALE_VOICE_1_DRIVER_ABUSE_1);
	return sfx;
}

uint32
cAudioManager::GetFanFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_ROBBED:
		sfx = SFX_FOOTBALL_FEMALE_VOICE_1_MUGGED_1;
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_FEMALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_FEMALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_FEMALE_VOICE_1_SHOCKED_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_FOOTBALL_FEMALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return (SFX_FOOTBALL_FEMALE_VOICE_2_DRIVER_ABUSE_1 - SFX_FOOTBALL_FEMALE_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetHospitalMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_MALE_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_MALE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_MALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_MALE_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetHospitalFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_FEMALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_FEMALE_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_HOSPITAL_FEMALE_VOICE_1_CHAT_1, 6);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetWhiteConstructionWorkerTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_MALE_CONSTRUCTION_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_CAR_JACKED:
		sfx = SFX_WHITE_MALE_CONSTRUCTION_VOICE_1_CARJACKED_1;
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_WHITE_MALE_CONSTRUCTION_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_WHITE_MALE_CONSTRUCTION_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_WHITE_MALE_CONSTRUCTION_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_WHITE_MALE_CONSTRUCTION_VOICE_1_EYING_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_WHITE_MALE_CONSTRUCTION_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetBlackConstructionWorkerTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CONSTRUCTION_MALE_VOICE_1_GUN_PANIC_1, 3);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CONSTRUCTION_MALE_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CONSTRUCTION_MALE_VOICE_1_FIGHT_1, 5);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CONSTRUCTION_MALE_VOICE_1_DODGE_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CONSTRUCTION_MALE_VOICE_1_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CONSTRUCTION_MALE_VOICE_1_EYING_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_BLACK_CONSTRUCTION_MALE_VOICE_1_CHAT_1, 4);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetShopperFemaleTalkSfx(uint16 sound, uint32 model)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_SHOPPER_VOICE_1_CARJACKED_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_SHOPPER_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_SHOPPER_VOICE_1_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_SHOPPER_VOICE_1_DRIVER_ABUSE_1, 7);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_SHOPPER_VOICE_1_SHOCKED_1, 4);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_SHOPPER_VOICE_1_CHAT_1, 7);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}

	if (model == MI_SHOPPER2) {
		sfx += (SFX_SHOPPER_VOICE_2_DRIVER_ABUSE_1 - SFX_SHOPPER_VOICE_1_DRIVER_ABUSE_1);
	} else if (model == MI_SHOPPER3) {
		sfx += (SFX_SHOPPER_VOICE_3_DRIVER_ABUSE_1 - SFX_SHOPPER_VOICE_1_DRIVER_ABUSE_1);
	}
	return sfx;
}

uint32
cAudioManager::GetStudentMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_MALE_VOICE_1_GUN_PANIC_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_MALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_MALE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_MALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_MALE_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_MALE_VOICE_1_SHOCKED_1, 3);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_MALE_VOICE_1_CHAT_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetStudentFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_FEMALE_VOICE_1_GUN_PANIC_1, 4);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_FEMALE_VOICE_1_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_FEMALE_VOICE_1_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_FEMALE_VOICE_1_DODGE_1, 4);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_FEMALE_VOICE_1_DRIVER_ABUSE_1, 4);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_FEMALE_VOICE_1_SHOCKED_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_STUDENT_FEMALE_VOICE_1_CHAT_1, 4);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetSpecialCharacterTalkSfx(uint32 modelIndex, uint16 sound)
{
	char *modelName = CModelInfo::GetModelInfo(modelIndex)->GetModelName();
	if (!CGeneral::faststricmp(modelName, "eight") || !CGeneral::faststricmp(modelName, "eight2")) 
		return GetEightBallTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "frankie"))
		return GetSalvatoreTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "misty"))
		return GetMistyTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "ojg") || !CGeneral::faststricmp(modelName, "ojg_p"))
		return GetOldJapTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "cat"))
		return GetCatalinaTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "bomber"))
		return GetBomberTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "s_guard"))
		return GetSecurityGuardTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "chunky"))
		return GetChunkyTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "asuka"))
		return GetGenericFemaleTalkSfx(sound);
	if (!CGeneral::faststricmp(modelName, "maria"))
		return GetGenericFemaleTalkSfx(sound);
	return GetGenericMaleTalkSfx(sound);
}

uint32
cAudioManager::GetEightBallTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_8BALL_GUN_COOL_1, 2);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_8BALL_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_8BALL_FIGHT_1, 6);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_8BALL_DODGE_1, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetSalvatoreTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_SALVATORE_GUN_COOL_1, 4);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_SALVATORE_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_SALVATORE_FIGHT_1, 6);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_SALVATORE_DODGE_1, 3);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetMistyTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_MISTY_GUN_COOL_1, 5);
		break;
	case SOUND_PED_ROBBED:
		GetPhrase(sfx, lastSfx, SFX_MISTY_MUGGED_1, 2);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_MISTY_FIGHT_1, 4);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_MISTY_DODGE_1, 5);
		break;
	case SOUND_PED_TAXI_CALL:
		GetPhrase(sfx, lastSfx, SFX_MISTY_HERE_1, 4);
		break;
	default:
		return GetGenericFemaleTalkSfx(sound);
		break;
	}
	return sfx;
}

uint32
cAudioManager::GetOldJapTalkSfx(uint16 sound)
{
	return GetGenericMaleTalkSfx(sound);
}

uint32
cAudioManager::GetCatalinaTalkSfx(uint16 sound)
{
	return GetGenericFemaleTalkSfx(sound);
}

uint32
cAudioManager::GetBomberTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound)
	{
	case SOUND_PED_BOMBER:
		GetPhrase(sfx, lastSfx, SFX_BOMBERMAN_1, 7);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetSecurityGuardTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_SECURITY_GUARD_VOICE_1_GUN_COOL_1, 2);
		break;
	case SOUND_PED_HANDS_COWER:
		sfx = SFX_SECURITY_GUARD_VOICE_1_GUN_PANIC_1;
		break;
	case SOUND_PED_CAR_JACKED:
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_SECURITY_GUARD_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	case SOUND_PED_ATTACK:
		GetPhrase(sfx, lastSfx, SFX_SECURITY_GUARD_VOICE_1_FIGHT_1, 2);
		break;
	case SOUND_PED_FLEE_RUN:
#ifdef FIX_BUGS
		sfx = SFX_SECURITY_GUARD_VOICE_1_RUN_FROM_FIGHT_1;
#else
		GetPhrase(sfx, lastSfx, SFX_SECURITY_GUARD_VOICE_1_DRIVER_ABUSE_1, 12);
#endif
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetChunkyTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound)
	{
	case SOUND_PED_DEATH:
		return SFX_CHUNKY_DEATH;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_CHUNKY_RUN_1, 5);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}

	return sfx;
}

uint32
cAudioManager::GetAsianTaxiDriverTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_ASIAN_TAXI_DRIVER_VOICE_1_CARJACKED_1, 7);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_ASIAN_TAXI_DRIVER_VOICE_1_DRIVER_ABUSE_1, 6);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}

	return (SFX_ASIAN_TAXI_DRIVER_VOICE_2_DRIVER_ABUSE_1 - SFX_ASIAN_TAXI_DRIVER_VOICE_1_DRIVER_ABUSE_1) * (m_sQueueSample.m_nEntityIndex % 2) + sfx;
}

uint32
cAudioManager::GetPimpTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_UP:
		GetPhrase(sfx, lastSfx, SFX_PIMP_GUN_COOL_1, 7);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_PIMP_CARJACKED_1, 4);
		break;
	case SOUND_PED_DEFEND:
		GetPhrase(sfx, lastSfx, SFX_PIMP_FIGHT_1, 9);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_PIMP_DODGE_1, 6);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_PIMP_DRIVER_ABUSE_1, 5);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_PIMP_SHOCKED_1, 2);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_PIMP_CHAT_1, 17);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetNormalMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_HANDS_COWER:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_GUN_PANIC_1, 7);
		break;
	case SOUND_PED_CAR_JACKED:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_CARJACKED_1, 7);
		break;
	case SOUND_PED_EVADE:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_DODGE_1, 9);
		break;
	case SOUND_PED_FLEE_RUN:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_RUN_FROM_FIGHT_1, 5);
		break;
	case SOUND_PED_ANNOYED_DRIVER:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_DRIVER_ABUSE_1, 12);
		break;
	case SOUND_PED_CHAT_SEXY:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_EYING_1, 8);
		break;
	case SOUND_PED_CHAT_EVENT:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_SHOCKED_1, 10);
		break;
	case SOUND_PED_CHAT:
		GetPhrase(sfx, lastSfx, SFX_NORMAL_MALE_CHAT_1, 25);
		break;
	default:
		return GetGenericMaleTalkSfx(sound);
	}
	return sfx;
}

uint32
cAudioManager::GetGenericMaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_DEATH:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_MALE_DEATH_1, 8);
		break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_MALE_GRUNT_1, 15);
		break;
	case SOUND_PED_BURNING:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_MALE_FIRE_1, 8);
		break;
	case SOUND_PED_FLEE_SPRINT:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_MALE_PANIC_1, 6);
		break;
	default:
		return NO_SAMPLE;
	}
	return sfx;
}

uint32
cAudioManager::GetGenericFemaleTalkSfx(uint16 sound)
{
	uint32 sfx;
	static uint32 lastSfx = NO_SAMPLE;

	switch (sound) {
	case SOUND_PED_DEATH:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_FEMALE_DEATH_1, 10);
		break;
	case SOUND_PED_BULLET_HIT:
	case SOUND_PED_DEFEND:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_FEMALE_GRUNT_1, 11);
		break;
	case SOUND_PED_BURNING:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_FEMALE_FIRE_1, 9);
		break;
	case SOUND_PED_FLEE_SPRINT:
		GetPhrase(sfx, lastSfx, SFX_GENERIC_FEMALE_PANIC_1, 8);
		break;
	default:
		return NO_SAMPLE;
	}
	return sfx;
}

void
cPedComments::Add(tPedComment *com)
{
	uint8 index;

	// copypasted priority check from cAudioManager::AddSampleToRequestedQueue

	if (m_nPedCommentCount[m_nActiveQueue] >= NUM_PED_COMMENTS_SLOTS) {
		index = m_aPedCommentOrderList[m_nActiveQueue][NUM_PED_COMMENTS_SLOTS - 1];
		if (m_aPedCommentQueue[m_nActiveQueue][index].m_nVolume > com->m_nVolume)
			return;
	} else
		index = m_nPedCommentCount[m_nActiveQueue]++;

	m_aPedCommentQueue[m_nActiveQueue][index] = *com;

	// this bit is basically copypasted cAudioManager::AddDetailsToRequestedOrderList
	uint8 i = 0;
	if (index != 0) {
		for (i = 0; i < index; i++) {
			if (m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][i]].m_nVolume < m_aPedCommentQueue[m_nActiveQueue][index].m_nVolume)
				break;
		}

		if (i < index)
			memmove(&m_aPedCommentOrderList[m_nActiveQueue][i + 1], &m_aPedCommentOrderList[m_nActiveQueue][i], NUM_PED_COMMENTS_SLOTS - 1 - i);
	}

	m_aPedCommentOrderList[m_nActiveQueue][i] = index;
}

void
cPedComments::Process()
{
	uint32 sampleIndex;
	uint8 queue;

	if (AudioManager.m_bIsPaused) return;

	if (m_nPedCommentCount[m_nActiveQueue]) {
		sampleIndex = m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][0]].m_nSampleIndex;
		switch (SampleManager.IsPedCommentLoaded(sampleIndex))
		{
		case LOADING_STATUS_NOT_LOADED:
			SampleManager.LoadPedComment(sampleIndex);
#ifdef GTA_PS2 // on PC ped comment is loaded at once
			break;
#endif
		case LOADING_STATUS_LOADED:
			AudioManager.m_sQueueSample.m_nEntityIndex = m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][0]].m_nEntityIndex;
			AudioManager.m_sQueueSample.m_nCounter = 0;
			AudioManager.m_sQueueSample.m_nSampleIndex = sampleIndex;
			AudioManager.m_sQueueSample.m_nBankIndex = SFX_BANK_PED_COMMENTS;
			AudioManager.m_sQueueSample.m_nPriority = 3;
			AudioManager.m_sQueueSample.m_nVolume = m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][0]].m_nVolume;
			AudioManager.m_sQueueSample.m_fDistance = m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][0]].m_fDistance;
			AudioManager.m_sQueueSample.m_nLoopCount = 1;
#ifndef GTA_PS2
			AudioManager.m_sQueueSample.m_nLoopStart = 0;
			AudioManager.m_sQueueSample.m_nLoopEnd = -1;
#endif // !GTA_PS2
#ifdef EXTERNAL_3D_SOUND
	#ifdef FIX_BUGS
			AudioManager.m_sQueueSample.m_nEmittingVolume = m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][0]].m_nEmittingVolume;
	#else
			AudioManager.m_sQueueSample.m_nEmittingVolume = MAX_VOLUME;
	#endif // FIX_BUGS
#endif // EXTERNAL_3D_SOUND
#ifdef ATTACH_RELEASING_SOUNDS_TO_ENTITIES
			// let's disable doppler because if sounds funny as the sound moves
			// originally position of ped comment doesn't change so this has no effect anyway
			AudioManager.m_sQueueSample.m_fSpeedMultiplier = 0.0f;
#else
			AudioManager.m_sQueueSample.m_fSpeedMultiplier = 3.0f;
#endif
			switch (sampleIndex) {
			case SFX_POLICE_HELI_1:
			case SFX_POLICE_HELI_2:
			case SFX_POLICE_HELI_3:
#ifdef FIX_BUGS
			case SFX_POLICE_HELI_4:
			case SFX_POLICE_HELI_5:
			case SFX_POLICE_HELI_6:
			case SFX_POLICE_HELI_7:
			case SFX_POLICE_HELI_8:
			case SFX_POLICE_HELI_9:
			case SFX_POLICE_HELI_10:
			case SFX_POLICE_HELI_11:
			case SFX_POLICE_HELI_12:
			case SFX_POLICE_HELI_13:
			case SFX_POLICE_HELI_14:
			case SFX_POLICE_HELI_15:
			case SFX_POLICE_HELI_16:
			case SFX_POLICE_HELI_17:
			case SFX_POLICE_HELI_18:
			case SFX_POLICE_HELI_19:
			case SFX_POLICE_HELI_20:
			case SFX_POLICE_HELI_21:
			case SFX_POLICE_HELI_22:
			case SFX_POLICE_HELI_23:
			case SFX_POLICE_HELI_24:
			case SFX_POLICE_HELI_25:
			case SFX_POLICE_HELI_26:
			case SFX_POLICE_HELI_27:
			case SFX_POLICE_HELI_28:
			case SFX_POLICE_HELI_29:
#endif
				AudioManager.m_sQueueSample.m_MaxDistance = PED_COMMENT_POLICE_HELI_MAX_DIST;
				break;
			default:
				AudioManager.m_sQueueSample.m_MaxDistance = PED_COMMENT_MAX_DIST;
				break;
			}
			AudioManager.m_sQueueSample.m_bStatic = TRUE;
			AudioManager.m_sQueueSample.m_vecPos = m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][0]].m_vecPos;

			if (sampleIndex >= SFX_AMMU_D && sampleIndex <= SFX_AMMU_F) {
				AudioManager.m_sQueueSample.m_bReverb = FALSE;
#ifdef AUDIO_REFLECTIONS
				AudioManager.m_sQueueSample.m_bReflections = FALSE;
#endif
#ifdef FIX_BUGS
			}
			else if (sampleIndex >= SFX_POLICE_HELI_1 && sampleIndex <= SFX_POLICE_HELI_29) {
				AudioManager.m_sQueueSample.m_bReverb = TRUE;
#ifdef AUDIO_REFLECTIONS
				AudioManager.m_sQueueSample.m_bReflections = FALSE;
#endif // AUDIO_REFLECTIONS
#endif // FIX_BUGS
			}
			else {
				AudioManager.m_sQueueSample.m_bReverb = TRUE;
#ifdef AUDIO_REFLECTIONS
				AudioManager.m_sQueueSample.m_bReflections = TRUE;
#endif
			}

			AudioManager.m_sQueueSample.m_bIs2D = FALSE;
			AudioManager.m_sQueueSample.m_nFrequency =
				SampleManager.GetSampleBaseFrequency(AudioManager.m_sQueueSample.m_nSampleIndex) + AudioManager.RandomDisplacement(750);
#ifndef USE_TIME_SCALE_FOR_AUDIO
			if (CTimer::GetIsSlowMotionActive())
				AudioManager.m_sQueueSample.m_nFrequency >>= 1;
#endif
			m_aPedCommentQueue[m_nActiveQueue][m_aPedCommentOrderList[m_nActiveQueue][0]].m_nLoadingTimeout = -1;
			AudioManager.AddSampleToRequestedQueue();
			break;
		case LOADING_STATUS_LOADING: break;
		default: break;
		}
	}

	// Switch queue
	if (m_nActiveQueue == 0) {
		queue = 0;
		m_nActiveQueue = 1;
	} else {
		queue = 1;
		m_nActiveQueue = 0;
	}
	for (uint8 i = 0; i < m_nPedCommentCount[queue]; i++) {
		if (m_aPedCommentQueue[queue][m_aPedCommentOrderList[queue][i]].m_nLoadingTimeout > 0) {
			m_aPedCommentQueue[queue][m_aPedCommentOrderList[queue][i]].m_nLoadingTimeout--;
			Add(&m_aPedCommentQueue[queue][m_aPedCommentOrderList[queue][i]]);
		}
	}

	// clear queue
	for (uint8 i = 0; i < NUM_PED_COMMENTS_SLOTS; i++)
		m_aPedCommentOrderList[queue][i] = NUM_PED_COMMENTS_SLOTS;
	m_nPedCommentCount[queue] = 0;
}

#pragma endregion

#pragma endregion All the ped audio code

void
cAudioManager::ProcessExplosions(int32 id)
{
	uint8 type;
	float distSquared;

	for (uint8 i = 0; i < ARRAY_SIZE(gaExplosion); i++) {
		if (CExplosion::GetExplosionActiveCounter(i) == 1) {
			CExplosion::ResetExplosionActiveCounter(i);
			type = CExplosion::GetExplosionType(i);
			switch (type) {
			case EXPLOSION_GRENADE:
			case EXPLOSION_ROCKET:
			case EXPLOSION_BARREL:
			case EXPLOSION_TANK_GRENADE:
				m_sQueueSample.m_MaxDistance = EXPLOSION_DEFAULT_MAX_DIST;
				m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_2;
#ifdef GTA_PS2
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 19000;
#else
				m_sQueueSample.m_nFrequency = RandomDisplacement(2000) + 38000;
#endif
				m_sQueueSample.m_nPriority = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				break;
			case EXPLOSION_MINE:
			case EXPLOSION_HELI_BOMB:
				m_sQueueSample.m_MaxDistance = EXPLOSION_MINE_MAX_DIST;
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_LEFT;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 12347;
				m_sQueueSample.m_nPriority = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				break;
			case EXPLOSION_MOLOTOV:
				m_sQueueSample.m_MaxDistance = EXPLOSION_MOLOTOV_MAX_DIST;
				m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_3;
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 19000;
				m_sQueueSample.m_nPriority = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				break;
			default:
				m_sQueueSample.m_MaxDistance = EXPLOSION_DEFAULT_MAX_DIST;
				m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_1;
#ifdef GTA_PS2
				m_sQueueSample.m_nFrequency = RandomDisplacement(1000) + 19000;
#else
				m_sQueueSample.m_nFrequency = RandomDisplacement(2000) + 38000;
#endif
				if (type == EXPLOSION_HELI)
					m_sQueueSample.m_nFrequency = 8 * m_sQueueSample.m_nFrequency / 10;
				m_sQueueSample.m_nPriority = 0;
				m_sQueueSample.m_nBankIndex = SFX_BANK_GENERIC_EXTRA;
				break;
			}
			m_sQueueSample.m_vecPos = *CExplosion::GetExplosionPosition(i);
			distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(m_sQueueSample.m_MaxDistance)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(MAX_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 1;
					m_sQueueSample.m_bStatic = TRUE;
					m_sQueueSample.m_bReverb = TRUE;
					SET_EMITTING_VOLUME(MAX_VOLUME);
					RESET_LOOP_OFFSETS
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(TRUE);
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::ProcessFires(int32 id)
{
	CEntity *entity;
	uint8 Vol;
	float distSquared;

	for (uint8 i = 0; i < NUM_FIRES; i++) {
		if (gFireManager.m_aFires[i].m_bIsOngoing && gFireManager.m_aFires[i].m_bAudioSet) {
			entity = gFireManager.m_aFires[i].m_pEntity;
			if (entity) {
				switch (entity->GetType()) {
				case ENTITY_TYPE_BUILDING:
					m_sQueueSample.m_MaxDistance = FIRE_BUILDING_MAX_DIST;
					m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
					Vol = FIRE_BUILDING_VOLUME;
					m_sQueueSample.m_nFrequency = 8 * SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE) / 10;
					m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency >> 6);
					m_sQueueSample.m_nPriority = 6;
					break;
				case ENTITY_TYPE_PED:
					m_sQueueSample.m_MaxDistance = FIRE_PED_MAX_DIST;
					m_sQueueSample.m_nSampleIndex = SFX_PED_ON_FIRE;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PED_ON_FIRE);
					Vol = FIRE_PED_VOLUME;
					m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency >> 6);
					m_sQueueSample.m_nPriority = 10;
					break;
				default:
					m_sQueueSample.m_MaxDistance = FIRE_DEFAULT_MAX_DIST;
					m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
					m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE);
					m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency >> 6);
					Vol = FIRE_DEFAULT_VOLUME;
					m_sQueueSample.m_nPriority = 8;
				}
			} else {
				m_sQueueSample.m_MaxDistance = FIRE_DEFAULT_MAX_DIST;
				m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE);
				m_sQueueSample.m_nFrequency += i * (m_sQueueSample.m_nFrequency >> 6);
				Vol = FIRE_DEFAULT_VOLUME;
				m_sQueueSample.m_nPriority = 8;
			}
			m_sQueueSample.m_vecPos = gFireManager.m_aFires[i].m_vecPos;
			distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(m_sQueueSample.m_MaxDistance)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_nFramesToPlay = 10;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_bStatic = FALSE;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::ProcessWaterCannon(int32 id)
{
	for (uint32 i = 0; i < NUM_WATERCANNONS; i++) {
		if (CWaterCannons::aCannons[i].m_nId) {
			m_sQueueSample.m_vecPos = CWaterCannons::aCannons[0].m_avecPos[CWaterCannons::aCannons[i].m_nCur];
			float distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(WATER_CANNON_MAX_DIST)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
#ifdef FIX_BUGS
				m_sQueueSample.m_nVolume = ComputeVolume(WATER_CANNON_VOLUME, WATER_CANNON_MAX_DIST, m_sQueueSample.m_fDistance);
#else
				m_sQueueSample.m_nVolume = ComputeVolume(WATER_CANNON_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
#endif
				if (m_sQueueSample.m_nVolume > 0) {
#ifdef FIX_BUGS
					m_sQueueSample.m_MaxDistance = WATER_CANNON_MAX_DIST;
#else
					m_sQueueSample.m_MaxDistance = SQR(WATER_CANNON_MAX_DIST);
#endif
					m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_nFrequency = 15591;
					m_sQueueSample.m_nPriority = 5;
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_nFramesToPlay = 8;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 0;
					m_sQueueSample.m_bStatic = FALSE;
					SET_EMITTING_VOLUME(WATER_CANNON_VOLUME);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

#pragma region SCRIPT_OBJECTS
void
cAudioManager::ProcessScriptObject(int32 id)
{
	cAudioScriptObject *entity = (cAudioScriptObject *)m_asAudioEntities[id].m_pEntity;
	if (entity != nil) {
		m_sQueueSample.m_vecPos = entity->Posn;
		if (m_asAudioEntities[id].m_AudioEvents == 1)
			ProcessOneShotScriptObject(m_asAudioEntities[id].m_awAudioEvent[0]);
		else
			ProcessLoopingScriptObject(entity->AudioId);
	}
}

void
cAudioManager::ProcessOneShotScriptObject(uint8 sound)
{
	CPlayerPed *playerPed;
	uint8 Vol;
	float distSquared;

	static uint8 iSound = 0;

	switch (sound) {
	case SCRIPT_SOUND_BOX_DESTROYED_1:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_BOX_DESTROYED_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_WOODEN_BOX_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(1500) + 18600;
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		SET_SOUND_REFLECTION(TRUE);
		Vol = m_anRandomTable[2] % 20 + SCRIPT_OBJECT_BOX_DESTROYED_VOLUME;
		break;
	case SCRIPT_SOUND_BOX_DESTROYED_2:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_BOX_DESTROYED_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_CARDBOARD_BOX_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(1500) + 18600;
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		SET_SOUND_REFLECTION(TRUE);
		Vol = m_anRandomTable[2] % 20 + SCRIPT_OBJECT_BOX_DESTROYED_VOLUME;
		break;
	case SCRIPT_SOUND_METAL_COLLISION:
		m_sQueueSample.m_MaxDistance = COLLISION_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = m_anRandomTable[3] % 5 + SFX_COL_CAR_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		SET_SOUND_REFLECTION(TRUE);
		Vol = m_anRandomTable[2] % 30 + SCRIPT_OBJECT_METAL_COLLISION_VOLUME;
		break;
	case SCRIPT_SOUND_TIRE_COLLISION:
		m_sQueueSample.m_MaxDistance = COLLISION_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_TYRE_BUMP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		SET_SOUND_REFLECTION(TRUE);
		Vol = m_anRandomTable[2] % 30 + SCRIPT_OBJECT_TIRE_COLLISION_VOLUME;
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
				m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_2;
				m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 11000;
				m_sQueueSample.m_nPriority = 18;
				break;
			case SURFACE_WATER:
				return;
			default:
				m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_1;
				m_sQueueSample.m_nFrequency = RandomDisplacement(750) + 18000;
				m_sQueueSample.m_nPriority = 15;
				break;
			}
		} else {
			m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_1;
			m_sQueueSample.m_nFrequency = RandomDisplacement(750) + 18000;
			m_sQueueSample.m_nPriority = 15;
		}
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_GUNSHELL_MAX_DIST;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		Vol = m_anRandomTable[2] % 20 + SCRIPT_OBJECT_GUNSHELL_VOLUME;
		break;
	case SCRIPT_SOUND_GUNSHELL_DROP_SOFT:
		m_sQueueSample.m_nSampleIndex = SFX_BULLET_SHELL_HIT_GROUND_2;
		m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 11000;
		m_sQueueSample.m_nPriority = 18;
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_GUNSHELL_MAX_DIST;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		Vol = m_anRandomTable[2] % 20 + SCRIPT_OBJECT_GUNSHELL_VOLUME;
		break;
	case SCRIPT_SOUND_BULLET_HIT_GROUND_1:
	case SCRIPT_SOUND_BULLET_HIT_GROUND_2:
	case SCRIPT_SOUND_BULLET_HIT_GROUND_3:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_BULLET_HIT_GROUND_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = m_anRandomTable[iSound % 5] % 3 + SFX_BULLET_WALL_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 5);
		m_sQueueSample.m_nPriority = 9;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		Vol = m_anRandomTable[2] % 20 + SCRIPT_OBJECT_BULLET_HIT_GROUND_VOLUME;
		break;
	case SCRIPT_SOUND_TRAIN_ANNOUNCEMENT_1:
	case SCRIPT_SOUND_TRAIN_ANNOUNCEMENT_2:
		if (SampleManager.IsSampleBankLoaded(SFX_BANK_TRAIN) != LOADING_STATUS_LOADED)
			return;
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_TRAIN_ANNOUNCEMENT_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_TRAIN_STATION_ANNOUNCE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_TRAIN;
		Vol = SCRIPT_OBJECT_TRAIN_ANNOUNCEMENT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_TRAIN_STATION_ANNOUNCE);
		m_sQueueSample.m_nPriority = 0;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_PAYPHONE_RINGING:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_PAYPHONE_RINGING_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_PHONE_RING;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		Vol = SCRIPT_OBJECT_PAYPHONE_RINGING_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PHONE_RING);
		m_sQueueSample.m_nPriority = 1;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		SET_SOUND_REFLECTION(FALSE);
		break;
	case SCRIPT_SOUND_GLASS_BREAK_L:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_GLASS_BREAK_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_GLASS_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		Vol = SCRIPT_OBJECT_GLASS_BREAK_LONG_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_SMASH);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_GLASS_BREAK_S:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_GLASS_BREAK_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_GLASS_SMASH;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		Vol = SCRIPT_OBJECT_GLASS_BREAK_SHORT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_SMASH);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		break;
	case SCRIPT_SOUND_GLASS_CRACK:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_GLASS_BREAK_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_GLASS_CRACK;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		Vol = SCRIPT_OBJECT_GLASS_BREAK_LONG_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_GLASS_CRACK);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		SET_SOUND_REFLECTION(TRUE);
		break;
	case SCRIPT_SOUND_GLASS_LIGHT_BREAK:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_GLASS_LIGHT_BREAK_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = (m_anRandomTable[4] & 3) + SFX_GLASS_SHARD_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nFrequency = RandomDisplacement(2000) + 19000;
		m_sQueueSample.m_nPriority = 9;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		Vol = RandomDisplacement(11) + SCRIPT_OBJECT_GLASS_LIGHT_BREAK_VOLUME;
		break;
	case SCRIPT_SOUND_INJURED_PED_MALE_OUCH_S:
	case SCRIPT_SOUND_INJURED_PED_MALE_OUCH_L:
	{
		cPedParams pedParams;
		pedParams.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		SetupPedComments(pedParams, SOUND_INJURED_PED_MALE_OUCH);
		return;
	}
	case SCRIPT_SOUND_INJURED_PED_FEMALE_OUCH_S:
	case SCRIPT_SOUND_INJURED_PED_FEMALE_OUCH_L:
	{
		cPedParams pedParams;
		pedParams.m_fDistance = GetDistanceSquared(m_sQueueSample.m_vecPos);
		SetupPedComments(pedParams, SOUND_INJURED_PED_FEMALE);
		return;
	}
	case SCRIPT_SOUND_GATE_START_CLUNK:
	case SCRIPT_SOUND_GATE_STOP_CLUNK:
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_GATE_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_COL_GATE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		if (sound == SCRIPT_SOUND_GATE_START_CLUNK)
			m_sQueueSample.m_nFrequency = 10600;
		else
			m_sQueueSample.m_nFrequency = 9000;
		m_sQueueSample.m_nPriority = 1;
		m_sQueueSample.m_fSpeedMultiplier = 0.0f;
		m_sQueueSample.m_bIs2D = FALSE;
		SET_SOUND_REFLECTION(TRUE);
		Vol = RandomDisplacement(10) + 50;
		break;
	default:
		return;
	}

	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < SQR(m_sQueueSample.m_MaxDistance)) {
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = iSound++;
			m_sQueueSample.m_nLoopCount = 1;
			m_sQueueSample.m_bStatic = TRUE;
			SET_EMITTING_VOLUME(Vol);
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_bReverb = TRUE;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessLoopingScriptObject(uint8 sound)
{
	uint8 Vol;
	float distSquared;
	float maxDistSquared;
	bool8 bLoadBank = FALSE;

	switch (sound) {
	case SCRIPT_SOUND_PORN_CINEMA_1_S:
	case SCRIPT_SOUND_PORN_CINEMA_1_L:
	case SCRIPT_SOUND_PORN_CINEMA_2_S:
	case SCRIPT_SOUND_PORN_CINEMA_2_L:
	case SCRIPT_SOUND_PORN_CINEMA_3_S:
	case SCRIPT_SOUND_PORN_CINEMA_3_L:
	case SCRIPT_SOUND_MISTY_SEX_S:
	case SCRIPT_SOUND_MISTY_SEX_L:
		ProcessPornCinema(sound);
		return;
	case SCRIPT_SOUND_WORK_SHOP_LOOP_S:
	case SCRIPT_SOUND_WORK_SHOP_LOOP_L:
		ProcessWorkShopScriptObject(sound);
		return;
	case SCRIPT_SOUND_SAWMILL_LOOP_S:
	case SCRIPT_SOUND_SAWMILL_LOOP_L:
		ProcessSawMillScriptObject(sound);
		return;
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_S:
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_L:
		ProcessLaunderetteScriptObject(sound);
		return;
	case SCRIPT_SOUND_SHOP_LOOP_S:
	case SCRIPT_SOUND_SHOP_LOOP_L:
		ProcessShopScriptObject(sound);
		return;
	case SCRIPT_SOUND_AIRPORT_LOOP_S:
	case SCRIPT_SOUND_AIRPORT_LOOP_L:
		ProcessAirportScriptObject(sound);
		return;
	case SCRIPT_SOUND_CINEMA_LOOP_S:
	case SCRIPT_SOUND_CINEMA_LOOP_L:
		ProcessCinemaScriptObject(sound);
		return;
	case SCRIPT_SOUND_DOCKS_LOOP_S:
	case SCRIPT_SOUND_DOCKS_LOOP_L:
		ProcessDocksScriptObject(sound);
		return;
	case SCRIPT_SOUND_HOME_LOOP_S:
	case SCRIPT_SOUND_HOME_LOOP_L:
		ProcessHomeScriptObject(sound);
		return;
	case SCRIPT_SOUND_POLICE_CELL_BEATING_LOOP_S:
	case SCRIPT_SOUND_POLICE_CELL_BEATING_LOOP_L:
		ProcessPoliceCellBeatingScriptObject(sound);
		return;
	case SCRIPT_SOUND_BANK_ALARM_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto BankAlarm;
	case SCRIPT_SOUND_BANK_ALARM_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
BankAlarm:
		m_sQueueSample.m_nSampleIndex = SFX_BANK_ALARM_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_BANK_ALARM;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_BANK_ALARM_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BANK_ALARM_1);
		m_sQueueSample.m_nPriority = 2;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_POLICE_BALL_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto PoliceBall;
	case SCRIPT_SOUND_POLICE_BALL_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
PoliceBall:
		m_sQueueSample.m_nSampleIndex = SFX_POLICE_BALL_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_POLICE_BALL;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_POLICE_BALL_1);
		m_sQueueSample.m_nPriority = 2;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_1_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party1;
	case SCRIPT_SOUND_PARTY_1_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party1:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_1;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_1);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_2_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party2;
	case SCRIPT_SOUND_PARTY_2_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party2:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_2;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_2;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_2);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_3_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party3;
	case SCRIPT_SOUND_PARTY_3_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party3:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_3;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_3;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_3);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_4_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party4;
	case SCRIPT_SOUND_PARTY_4_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party4:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_4;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_4;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_4);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_5_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party5;
	case SCRIPT_SOUND_PARTY_5_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party5:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_5;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_5;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_5);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_6_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party6;
	case SCRIPT_SOUND_PARTY_6_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party6:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_6;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_6;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_6);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_7_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party7;
	case SCRIPT_SOUND_PARTY_7_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party7:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_7;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_7;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_7);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_8_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party8;
	case SCRIPT_SOUND_PARTY_8_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party8:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_8;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_8;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_8);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_9_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party9;
	case SCRIPT_SOUND_PARTY_9_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party9:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_9;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_9;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_9);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_10_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party10;
	case SCRIPT_SOUND_PARTY_10_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party10:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_10;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_10;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_10);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_11_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party11;
	case SCRIPT_SOUND_PARTY_11_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party11:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_11;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_11;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_11);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_12_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party12;
	case SCRIPT_SOUND_PARTY_12_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party12:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_12;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_12;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_12);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_13_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party13;
	case SCRIPT_SOUND_PARTY_13_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Party13:
		m_sQueueSample.m_nSampleIndex = SFX_CLUB_RAGGA;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CLUB_RAGGA;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CLUB_RAGGA);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_1_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto StripClub1;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_1_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
StripClub1:
		m_sQueueSample.m_nSampleIndex = SFX_STRIP_CLUB_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_STRIP_CLUB_1;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_STRIP_CLUB_1);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_2_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto StripClub2;
	case SCRIPT_SOUND_STRIP_CLUB_LOOP_2_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
StripClub2:
		m_sQueueSample.m_nSampleIndex = SFX_STRIP_CLUB_2;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_STRIP_CLUB_2;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_STRIP_CLUB_2);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PARTY_1_LOOP:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Party1; // BUG? Shouldn't this be Frankie piano?
	case SCRIPT_SOUND_FRANKIE_PIANO:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_PIANO_BAR_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_PIANO_BAR;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_PIANO_BAR_1);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_DOG_FOOD_FACTORY_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto DogFoodFactory;
	case SCRIPT_SOUND_DOG_FOOD_FACTORY_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
DogFoodFactory:
		m_sQueueSample.m_nSampleIndex = SFX_DOG_FOOD_FACTORY;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_DOG_FOOD_FACTORY;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_RESAURANT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_DOG_FOOD_FACTORY);
		m_sQueueSample.m_nPriority = 6;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_CHINATOWN_RESTAURANT_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto ChinatownRestaurant;
	case SCRIPT_SOUND_CHINATOWN_RESTAURANT_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
ChinatownRestaurant:
		m_sQueueSample.m_nSampleIndex = SFX_RESTAURANT_CHINATOWN;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_RESTAURANT_CHINATOWN;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_RESAURANT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RESTAURANT_CHINATOWN);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_CIPRIANI_RESAURANT_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto CiprianiRestaurant;
	case SCRIPT_SOUND_CIPRIANI_RESAURANT_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
CiprianiRestaurant:
		m_sQueueSample.m_nSampleIndex = SFX_RESTAURANT_ITALY;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_RESTAURANT_ITALY;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_RESAURANT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RESTAURANT_ITALY);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_47_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto GenericRestaurant1;
	case SCRIPT_SOUND_46_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
GenericRestaurant1:
		m_sQueueSample.m_nSampleIndex = SFX_RESTAURANT_GENERIC_1;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_RESTAURANT_GENERIC_1;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_RESAURANT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RESTAURANT_GENERIC_1);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_MARCO_BISTRO_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto GenericRestaurant2;
	case SCRIPT_SOUND_MARCO_BISTRO_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
GenericRestaurant2:
		m_sQueueSample.m_nSampleIndex = SFX_RESTAURANT_GENERIC_2;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_RESTAURANT_GENERIC_2;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_RESAURANT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RESTAURANT_GENERIC_2);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_LOOP_INDUSTRIAL_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto RaveLoop;
	case SCRIPT_SOUND_RAVE_LOOP_INDUSTRIAL_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
RaveLoop:
		m_sQueueSample.m_nSampleIndex = SFX_RAVE_INDUSTRIAL;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_RAVE_INDUSTRIAL;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RAVE_INDUSTRIAL);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_1_LOOP_L:
	case SCRIPT_SOUND_RAVE_2_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Rave1;
	case SCRIPT_SOUND_RAVE_1_LOOP_S:
	case SCRIPT_SOUND_RAVE_2_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Rave1:
		m_sQueueSample.m_nSampleIndex = SFX_RAVE_COMMERCIAL;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_RAVE_COMMERCIAL;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_RAVE_3_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
		goto Rave3;
	case SCRIPT_SOUND_RAVE_3_LOOP_S:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
Rave3:
		m_sQueueSample.m_nSampleIndex = SFX_RAVE_SUBURBAN;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_RAVE_SUBURBAN;
		bLoadBank = TRUE;
		Vol = SCRIPT_OBJECT_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RAVE_SUBURBAN);
		m_sQueueSample.m_nPriority = 3;
		m_sQueueSample.m_nFramesToPlay = 3;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	case SCRIPT_SOUND_PRETEND_FIRE_LOOP:
		maxDistSquared = SQR(FIRE_DEFAULT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = FIRE_DEFAULT_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_CAR_ON_FIRE;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		Vol = FIRE_DEFAULT_VOLUME;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_CAR_ON_FIRE);
		m_sQueueSample.m_nPriority = 8;
		m_sQueueSample.m_nFramesToPlay = 10;
		m_sQueueSample.m_fSpeedMultiplier = 2.0f;
		break;
	default:
		return;
	}

	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < maxDistSquared) {
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
#ifdef GTA_PS2
			if (bLoadBank && !LoadBankIfNecessary(m_sQueueSample.m_nBankIndex))
				return;
#endif
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_bReverb = TRUE;
			SET_EMITTING_VOLUME(Vol);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessPornCinema(uint8 sound)
{
	eSfxSample sample;
	uint32 time;
	int32 rand;
	float distSquared;
	float maxDistSquared;

	switch (sound) {
	case SCRIPT_SOUND_PORN_CINEMA_1_S:
	case SCRIPT_SOUND_MISTY_SEX_S:
		m_sQueueSample.m_nSampleIndex = SFX_PORN_1_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_PORN_1;
		maxDistSquared = SQR(PORN_CINEMA_SHORT_MAX_DIST);
		sample = SFX_PORN_1_GROAN_1;
		m_sQueueSample.m_MaxDistance = PORN_CINEMA_SHORT_MAX_DIST;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_1_L:
	case SCRIPT_SOUND_MISTY_SEX_L:
		m_sQueueSample.m_nSampleIndex = SFX_PORN_1_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_PORN_1;
		maxDistSquared = SQR(PORN_CINEMA_LONG_MAX_DIST);
		sample = SFX_PORN_1_GROAN_1;
		m_sQueueSample.m_MaxDistance = PORN_CINEMA_LONG_MAX_DIST;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_2_S:
		m_sQueueSample.m_nSampleIndex = SFX_PORN_2_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_PORN_2;
		maxDistSquared = SQR(PORN_CINEMA_SHORT_MAX_DIST);
		sample = SFX_PORN_2_GROAN_1;
		m_sQueueSample.m_MaxDistance = PORN_CINEMA_SHORT_MAX_DIST;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_2_L:
		m_sQueueSample.m_nSampleIndex = SFX_PORN_2_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_PORN_2;
		maxDistSquared = SQR(PORN_CINEMA_LONG_MAX_DIST);
		sample = SFX_PORN_2_GROAN_1;
		m_sQueueSample.m_MaxDistance = PORN_CINEMA_LONG_MAX_DIST;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_3_S:
		m_sQueueSample.m_nSampleIndex = SFX_PORN_3_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_PORN_3;
		maxDistSquared = SQR(PORN_CINEMA_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = PORN_CINEMA_SHORT_MAX_DIST;
		sample = SFX_PORN_3_GROAN_1;
		break;
	case SCRIPT_SOUND_PORN_CINEMA_3_L:
		m_sQueueSample.m_nSampleIndex = SFX_PORN_3_LOOP;
		m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_PORN_3;
		maxDistSquared = SQR(PORN_CINEMA_LONG_MAX_DIST);
		m_sQueueSample.m_MaxDistance = PORN_CINEMA_LONG_MAX_DIST;
		sample = SFX_PORN_3_GROAN_1;
		break;
	default:
#ifdef FIX_BUGS
		return;
#else
		break;
#endif
	}
	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
		if (!LoadBankIfNecessary(m_sQueueSample.m_nBankIndex))
			return;
#endif
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		if (sound != SCRIPT_SOUND_MISTY_SEX_S && sound != SCRIPT_SOUND_MISTY_SEX_L) {
			m_sQueueSample.m_nVolume = ComputeVolume(PORN_CINEMA_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nCounter = 0;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 0;
				m_sQueueSample.m_bStatic = FALSE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				SET_EMITTING_VOLUME(PORN_CINEMA_VOLUME);
				SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
			}
		}

		time = CTimer::GetTimeInMilliseconds();
		if (time > gPornNextTime) {
			m_sQueueSample.m_nVolume = ComputeVolume(PORN_CINEMA_MOAN_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				rand = m_anRandomTable[1] & 1;
				m_sQueueSample.m_nSampleIndex = rand + sample;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
				m_sQueueSample.m_nCounter = rand + 1;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 6;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
#ifdef FIX_BUGS
				SET_EMITTING_VOLUME(PORN_CINEMA_MOAN_VOLUME);
#endif
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
				gPornNextTime = time + 2000 + m_anRandomTable[3] % 6000;
			}
		}
	}
}

void
cAudioManager::ProcessWorkShopScriptObject(uint8 sound)
{
	float distSquared;
	float maxDistSquared;

	switch (sound) {
	case SCRIPT_SOUND_WORK_SHOP_LOOP_S:
	case SCRIPT_SOUND_WORK_SHOP_LOOP_L:
		maxDistSquared = SQR(WORK_SHOP_MAX_DIST);
		m_sQueueSample.m_MaxDistance = WORK_SHOP_MAX_DIST;
		break;
	default:
#ifdef FIX_BUGS
		return;
#else
		break;
#endif
	}
	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
		if (!LoadBankIfNecessary(SFX_BANK_BUILDING_WORKSHOP))
			return;
#endif
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(WORK_SHOP_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nSampleIndex = SFX_WORKSHOP_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_WORKSHOP;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_WORKSHOP_1);
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			SET_EMITTING_VOLUME(WORK_SHOP_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessSawMillScriptObject(uint8 sound)
{
	uint32 time;
	float distSquared;
	float maxDistSquared;

	switch (sound) {
	case SCRIPT_SOUND_SAWMILL_LOOP_S:
	case SCRIPT_SOUND_SAWMILL_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
		break;
	default:
#ifdef FIX_BUGS
		return;
#else
		break;
#endif
	}
	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
		if (!LoadBankIfNecessary(SFX_BANK_BUILDING_SAWMILL))
			return;
#endif
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(SAWMILL_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nSampleIndex = SFX_SAWMILL_LOOP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_SAWMILL;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SAWMILL_LOOP);
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			SET_EMITTING_VOLUME(SAWMILL_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		time = CTimer::GetTimeInMilliseconds();
		if (time > gSawMillNextTime) {
			m_sQueueSample.m_nVolume = ComputeVolume(SAWMILL_CUT_WOOD_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nSampleIndex = SFX_SAWMILL_CUT_WOOD;
				m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_SAWMILL;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nCounter = 1;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
#ifdef FIX_BUGS
				SET_EMITTING_VOLUME(SAWMILL_CUT_WOOD_VOLUME);
#endif
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
				gSawMillNextTime = time + 2000 + m_anRandomTable[3] % 4000;
			}
		}
	}
}

void
cAudioManager::ProcessLaunderetteScriptObject(uint8 sound)
{
	float maxDistSquared;

	switch (sound) {
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_S:
	case SCRIPT_SOUND_LAUNDERETTE_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
		break;
	default:
#ifdef FIX_BUGS
		return;
#else
		break;
#endif
	}
	float distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
		if (!LoadBankIfNecessary(SFX_BANK_BUILDING_LAUNDERETTE))
			return;
#endif
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(LAUNDERETTE_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nSampleIndex = SFX_LAUNDERETTE_LOOP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_LAUNDERETTE;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_LAUNDERETTE_LOOP);
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			SET_EMITTING_VOLUME(LAUNDERETTE_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		m_sQueueSample.m_nVolume = ComputeVolume(LAUNDERETTE_SONG_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nSampleIndex = SFX_LAUNDERETTE_SONG_LOOP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_LAUNDERETTE;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_LAUNDERETTE_SONG_LOOP);
			m_sQueueSample.m_nCounter = 1;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nPriority = 3;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			SET_EMITTING_VOLUME(LAUNDERETTE_SONG_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessShopScriptObject(uint8 sound)
{
	uint32 time;
	int32 rand;
	float distSquared;
	float maxDistSquared;

	switch (sound) {
	case SCRIPT_SOUND_SHOP_LOOP_S:
	case SCRIPT_SOUND_SHOP_LOOP_L:
		maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
		m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
		break;
	default:
#ifdef FIX_BUGS
		return;
#else
		break;
#endif
	}
	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
		if (!LoadBankIfNecessary(SFX_BANK_BUILDING_SHOP))
			return;
#endif
		m_sQueueSample.m_fDistance = Sqrt(distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(SHOP_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nSampleIndex = SFX_SHOP_LOOP;
			m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_SHOP;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_SHOP_LOOP);
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nLoopCount = 0;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nPriority = 5;
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			SET_EMITTING_VOLUME(SHOP_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
		time = CTimer::GetTimeInMilliseconds();
		if (time > gShopNextTime) {
			m_sQueueSample.m_nVolume = ComputeVolume(SHOP_TILL_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				rand = m_anRandomTable[1] & 1;
				m_sQueueSample.m_nSampleIndex = rand + SFX_SHOP_TILL_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_SHOP;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nCounter = rand + 1;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				SET_EMITTING_VOLUME(SHOP_TILL_VOLUME);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
				gShopNextTime = time + 3000 + m_anRandomTable[3] % 7000;
			}
		}
	}
}

void
cAudioManager::ProcessAirportScriptObject(uint8 sound)
{
	float maxDistSquared;
	static uint8 iSound = 0;

	uint32 time = CTimer::GetTimeInMilliseconds();
	if (time > gAirportNextTime) {
		switch (sound) {
		case SCRIPT_SOUND_AIRPORT_LOOP_S:
			maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
			break;
		case SCRIPT_SOUND_AIRPORT_LOOP_L:
			maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
			break;
		default:
#ifdef FIX_BUGS
			return;
#else
			break;
#endif
		}
		float distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
			if (!LoadBankIfNecessary(SFX_BANK_BUILDING_AIRPORT))
				return;
#endif
			m_sQueueSample.m_fDistance = Sqrt(distSquared);
			m_sQueueSample.m_nVolume = ComputeVolume(AIRPORT_VOLUME, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nSampleIndex = (m_anRandomTable[1] & 3) + SFX_AIRPORT_ANNOUNCEMENT_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_AIRPORT;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nCounter = iSound++;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				SET_EMITTING_VOLUME(AIRPORT_VOLUME);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
				gAirportNextTime = time + 10000 + m_anRandomTable[3] % 20000;
			}
		}
	}
}

void
cAudioManager::ProcessCinemaScriptObject(uint8 sound)
{
	float maxDistSquared;
	uint8 Vol;

	static uint8 iSound = 0;

	uint32 time = CTimer::GetTimeInMilliseconds();
	if (time > gCinemaNextTime) {
		switch (sound) {
		case SCRIPT_SOUND_CINEMA_LOOP_S:
			maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
			break;
		case SCRIPT_SOUND_CINEMA_LOOP_L:
			maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
			break;
		default:
#ifdef FIX_BUGS
			return;
#else
			break;
#endif
		}
		float distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
			if (!LoadBankIfNecessary(SFX_BANK_BUILDING_CINEMA))
				return;
#endif
			m_sQueueSample.m_fDistance = Sqrt(distSquared);
			Vol = m_anRandomTable[0] % 90 + CINEMA_VOLUME;
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nSampleIndex = iSound % 3 + SFX_CINEMA_BASS_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_CINEMA;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
				m_sQueueSample.m_nCounter = iSound++;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				SET_EMITTING_VOLUME(Vol);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
				gCinemaNextTime = time + 1000 + m_anRandomTable[3] % 4000;
			}
		}
	}
}

void
cAudioManager::ProcessDocksScriptObject(uint8 sound)
{
	uint32 time;
	uint8 Vol;
	float distSquared;
	float maxDistSquared;

	static uint8 iSound = 0;

	time = CTimer::GetTimeInMilliseconds();
	if (time > gDocksNextTime) {
		switch (sound) {
		case SCRIPT_SOUND_DOCKS_LOOP_S:
			maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
			break;
		case SCRIPT_SOUND_DOCKS_LOOP_L:
			maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
			break;
		default:
#ifdef FIX_BUGS
			return;
#else
			break;
#endif
		}
		distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distSquared < maxDistSquared) {
#ifdef GTA_PS2
			if (!LoadBankIfNecessary(SFX_BANK_BUILDING_DOCKS))
				return;
#endif
			m_sQueueSample.m_fDistance = Sqrt(distSquared);
			Vol = m_anRandomTable[0] % 60 + DOCKS_VOLUME;
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nSampleIndex = SFX_DOCKS_FOGHORN;
				m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_DOCKS;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_DOCKS_FOGHORN);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 3);
				m_sQueueSample.m_nCounter = iSound++;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 2.0f;
				SET_EMITTING_VOLUME(Vol);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
				gDocksNextTime = time + 10000 + m_anRandomTable[3] % 40000;
			}
		}
	}
}
void
cAudioManager::ProcessHomeScriptObject(uint8 sound)
{
	uint32 time;
	uint8 Vol;
	float dist;
	float maxDistSquared;

	static uint8 iSound = 0;

	time = CTimer::GetTimeInMilliseconds();
	if (time > gHomeNextTime) {
		switch (sound) {
		case SCRIPT_SOUND_HOME_LOOP_S:
			maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
			break;
		case SCRIPT_SOUND_HOME_LOOP_L:
			maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
			break;
		default:
#ifdef FIX_BUGS
			return;
#else
			break;
#endif
		}
		dist = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (dist < maxDistSquared) {
#ifdef GTA_PS2
			if (!LoadBankIfNecessary(SFX_BANK_BUILDING_HOME))
				return;
#endif
			m_sQueueSample.m_fDistance = Sqrt(dist);
			Vol = m_anRandomTable[0] % 30 + HOME_VOLUME;
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nSampleIndex = m_anRandomTable[0] % 5 + SFX_HOME_1;
				m_sQueueSample.m_nBankIndex = SFX_BANK_BUILDING_HOME;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
				m_sQueueSample.m_nCounter = iSound++;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				SET_EMITTING_VOLUME(Vol);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(TRUE);
				AddSampleToRequestedQueue();
				gHomeNextTime = time + 1000 + m_anRandomTable[3] % 4000;
			}
		}
	}
}
void
cAudioManager::ProcessPoliceCellBeatingScriptObject(uint8 sound)
{
	uint32 time = CTimer::GetTimeInMilliseconds();
	int32 sampleIndex;
	uint8 Vol;
	float distSquared;
	float maxDistSquared;

	static uint8 iSound = 0;

	if (time > gCellNextTime) {
		switch (sound) {
		case SCRIPT_SOUND_POLICE_CELL_BEATING_LOOP_S:
			maxDistSquared = SQR(SCRIPT_OBJECT_SHORT_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_SHORT_MAX_DIST;
			break;
		case SCRIPT_SOUND_POLICE_CELL_BEATING_LOOP_L:
			maxDistSquared = SQR(SCRIPT_OBJECT_LONG_MAX_DIST);
			m_sQueueSample.m_MaxDistance = SCRIPT_OBJECT_LONG_MAX_DIST;
			break;
		default:
#ifdef FIX_BUGS
			return;
#else
			break;
#endif
		}
		distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distSquared < maxDistSquared) {
			m_sQueueSample.m_fDistance = Sqrt(distSquared);
			if (m_FrameCounter & 1)
				sampleIndex = (m_anRandomTable[1] & 3) + SFX_FIGHT_1;
			else
				sampleIndex = (m_anRandomTable[3] & 1) + SFX_BAT_HIT_LEFT;
			m_sQueueSample.m_nSampleIndex = sampleIndex;
			Vol = m_anRandomTable[0] % 50 + POLICE_CELL_BEATING_VOLUME;
			m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
			if (m_sQueueSample.m_nVolume > 0) {
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
				m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
				m_sQueueSample.m_nCounter = iSound++;
				m_sQueueSample.m_bIs2D = FALSE;
				m_sQueueSample.m_nLoopCount = 1;
				m_sQueueSample.m_bStatic = TRUE;
				m_sQueueSample.m_nPriority = 3;
				m_sQueueSample.m_fSpeedMultiplier = 0.0f;
				SET_EMITTING_VOLUME(Vol);
				RESET_LOOP_OFFSETS
				m_sQueueSample.m_bReverb = TRUE;
				SET_SOUND_REFLECTION(FALSE);
				AddSampleToRequestedQueue();
				cPedParams params;
				params.m_bDistanceCalculated = TRUE;
				params.m_fDistance = distSquared;
				SetupPedComments(params, SOUND_INJURED_PED_MALE_PRISON);
			}
			gCellNextTime = time + 500 + m_anRandomTable[3] % 1500;
		}
	}
}
#pragma endregion All the code for script object audio on the map

void
cAudioManager::ProcessWeather(int32 id)
{
	uint8 Vol;
	static uint8 iSound = 0;

	if (m_asAudioEntities[id].m_AudioEvents > 0 && m_asAudioEntities[id].m_awAudioEvent[0] == SOUND_LIGHTNING) {
		if (m_asAudioEntities[id].m_afVolume[0] < 10) {
			m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_2;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 4000;
			Vol = (m_asAudioEntities[id].m_afVolume[0] * 10.0f * 0.1f);
			Vol += 35;
		} else {
			m_sQueueSample.m_nSampleIndex = SFX_EXPLOSION_1;
			m_sQueueSample.m_nBankIndex = SFX_BANK_GENERIC_EXTRA;
			m_sQueueSample.m_nFrequency = RandomDisplacement(500) + 4000;
			Vol = ((m_asAudioEntities[id].m_afVolume[0] - 10.0f) * 10.0f * 0.1f);
			Vol += 40;
		}
		m_sQueueSample.m_nVolume = Vol;
		if (TheCamera.SoundDistUp < 20.0f)
			m_sQueueSample.m_nVolume >>= 1;
		if (iSound == 4)
			iSound = 0;
		m_sQueueSample.m_nCounter = iSound++;
		m_sQueueSample.m_nPriority = 0;
		m_sQueueSample.m_nPan = (m_anRandomTable[2] % 16) + 55;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_nLoopCount = 1;
		m_sQueueSample.m_bStatic = TRUE;
		SET_EMITTING_VOLUME(m_sQueueSample.m_nVolume);
		RESET_LOOP_OFFSETS
		m_sQueueSample.m_bReverb = FALSE;
		SET_SOUND_REFLECTION(FALSE);
		AddSampleToRequestedQueue();
	}
	if (CWeather::Rain > 0.0f && (!CCullZones::CamNoRain() || !CCullZones::PlayerNoRain())) {
		m_sQueueSample.m_nSampleIndex = SFX_RAIN;
		m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_RAIN);
		m_sQueueSample.m_nVolume = (uint8)(25.0f * CWeather::Rain);
		m_sQueueSample.m_nCounter = 4;
		m_sQueueSample.m_nBankIndex = SFX_BANK_0;
		m_sQueueSample.m_nPriority = 0;
		m_sQueueSample.m_nPan = 63;
		m_sQueueSample.m_bIs2D = TRUE;
		m_sQueueSample.m_nLoopCount = 0;
		m_sQueueSample.m_bStatic = FALSE;
		m_sQueueSample.m_nFramesToPlay = 30;
		m_sQueueSample.m_bReverb = FALSE;
		SET_EMITTING_VOLUME(m_sQueueSample.m_nVolume);
		SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
		SET_SOUND_REFLECTION(FALSE);
		AddSampleToRequestedQueue();
	}
}

void
cAudioManager::ProcessFrontEnd()
{
	bool8 stereo;
	bool8 processedPickup;
	bool8 processedMission;
	bool8 frontendBank;
	int16 sample;

	static uint8 iSound = 0;
	static uint32 cPickupNextFrame = 0;
	static uint32 cPartMisComNextFrame = 0;

	for (uint32 i = 0; i < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; i++) {
		processedPickup = FALSE;
		stereo = FALSE;
		processedMission = FALSE;
		frontendBank = FALSE;
		switch (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[i]) {
		case SOUND_FRONTEND_RADIO_TURN_OFF:
		case SOUND_FRONTEND_RADIO_CHANGE:
			m_sQueueSample.m_nSampleIndex = SFX_RADIO_CLICK;
			break;
		case SOUND_HUD:
			m_sQueueSample.m_nSampleIndex = SFX_INFO;
			break;
		case SOUND_FRONTEND_MENU_STARTING:
			m_sQueueSample.m_nSampleIndex = SFX_START_BUTTON_LEFT;
			stereo = TRUE;
			break;
		case SOUND_FRONTEND_MENU_NEW_PAGE:
			m_sQueueSample.m_nSampleIndex = SFX_PAGE_CHANGE_AND_BACK_LEFT;
			stereo = TRUE;
			frontendBank = TRUE;
			break;
		case SOUND_FRONTEND_MENU_NAVIGATION:
			m_sQueueSample.m_nSampleIndex = SFX_HIGHLIGHT_LEFT;
			stereo = TRUE;
			frontendBank = TRUE;
			break;
		case SOUND_FRONTEND_MENU_SETTING_CHANGE:
			m_sQueueSample.m_nSampleIndex = SFX_SELECT_LEFT;
			stereo = TRUE;
			frontendBank = TRUE;
			break;
		case SOUND_FRONTEND_MENU_BACK:
			m_sQueueSample.m_nSampleIndex = SFX_SUB_MENU_BACK_LEFT;
			stereo = TRUE;
			frontendBank = TRUE;
			break;
		case SOUND_FRONTEND_STEREO:
			m_sQueueSample.m_nSampleIndex = SFX_STEREO_LEFT;
			stereo = TRUE;
			frontendBank = TRUE;
			break;
		case SOUND_FRONTEND_MONO:
			m_sQueueSample.m_nSampleIndex = SFX_MONO;
			frontendBank = TRUE;
			break;
		case SOUND_FRONTEND_AUDIO_TEST:
			m_sQueueSample.m_nSampleIndex = m_anRandomTable[0] % 3 + SFX_NOISE_BURST_1;
			frontendBank = TRUE;
			break;
		case SOUND_FRONTEND_FAIL:
			m_sQueueSample.m_nSampleIndex = SFX_ERROR_LEFT;
			frontendBank = TRUE;
			stereo = TRUE;
			break;
		case SOUND_RACE_START_GO:
			m_sQueueSample.m_nSampleIndex = SFX_PART_MISSION_COMPLETE;
			break;
		case SOUND_PART_MISSION_COMPLETE:
			m_sQueueSample.m_nSampleIndex = SFX_PART_MISSION_COMPLETE;
			processedMission = TRUE;
			break;
		case SOUND_RACE_START_3:
		case SOUND_RACE_START_2:
		case SOUND_RACE_START_1:
		case SOUND_CLOCK_TICK:
			m_sQueueSample.m_nSampleIndex = SFX_TIMER_BEEP;
			break;
		case SOUND_PAGER:
#ifdef GTA_PS2
		{
			cPedParams pedParams;
			pedParams.m_bDistanceCalculated = TRUE;
			SetupPedComments(pedParams, SOUND_PAGER);
			continue;
		}
#else
			m_sQueueSample.m_nSampleIndex = SFX_PAGER;
			break;
#endif
		case SOUND_WEAPON_SNIPER_SHOT_NO_ZOOM:
			m_sQueueSample.m_nSampleIndex = SFX_ERROR_FIRE_RIFLE;
			break;
		case SOUND_WEAPON_ROCKET_SHOT_NO_ZOOM:
			m_sQueueSample.m_nSampleIndex = SFX_ERROR_FIRE_ROCKET_LAUNCHER;
			break;
		case SOUND_PICKUP_WEAPON_BOUGHT:
		case SOUND_PICKUP_WEAPON:
			m_sQueueSample.m_nSampleIndex = SFX_PICKUP_1_LEFT;
			processedPickup = TRUE;
			stereo = TRUE;
			break;
		case SOUND_PICKUP_BONUS:
		case SOUND_PICKUP_MONEY:
		case SOUND_PICKUP_HIDDEN_PACKAGE:
		case SOUND_PICKUP_PACMAN_PILL:
		case SOUND_PICKUP_PACMAN_PACKAGE:
		case SOUND_PICKUP_FLOAT_PACKAGE:
			m_sQueueSample.m_nSampleIndex = SFX_PICKUP_3_LEFT;
			processedPickup = TRUE;
			stereo = TRUE;
			break;
		case SOUND_PICKUP_ERROR:
			m_sQueueSample.m_nSampleIndex = SFX_PICKUP_ERROR_LEFT;
			processedPickup = TRUE;
			stereo = TRUE;
			break;
		case SOUND_GARAGE_NO_MONEY:
		case SOUND_GARAGE_BAD_VEHICLE:
		case SOUND_GARAGE_BOMB_ALREADY_SET:
			m_sQueueSample.m_nSampleIndex = SFX_PICKUP_ERROR_LEFT;
			stereo = TRUE;
			break;
		case SOUND_GARAGE_OPENING:
		case SOUND_GARAGE_BOMB1_SET:
		case SOUND_GARAGE_BOMB2_SET:
		case SOUND_GARAGE_BOMB3_SET:
		case SOUND_41:
		case SOUND_GARAGE_VEHICLE_DECLINED:
		case SOUND_GARAGE_VEHICLE_ACCEPTED:
		case SOUND_PICKUP_HEALTH:
		case SOUND_4B:
		case SOUND_PICKUP_ADRENALINE:
		case SOUND_PICKUP_ARMOUR:
		case SOUND_EVIDENCE_PICKUP:
		case SOUND_UNLOAD_GOLD:
			m_sQueueSample.m_nSampleIndex = SFX_PICKUP_2_LEFT;
			processedPickup = TRUE;
			stereo = TRUE;
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
		if (sample == SFX_RAIN)
			m_sQueueSample.m_nFrequency = 28509;
		else if (sample == SFX_PICKUP_1_LEFT) {
			if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_afVolume[i] == 1.0f)
				m_sQueueSample.m_nFrequency = 48000;
			else
				m_sQueueSample.m_nFrequency = 32000;
		} else
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
		m_sQueueSample.m_nVolume = FRONTEND_VOLUME;
		m_sQueueSample.m_nCounter = iSound++;
		m_sQueueSample.m_nLoopCount = 1;
		m_sQueueSample.m_bStatic = TRUE;
		m_sQueueSample.m_nBankIndex = frontendBank ? SFX_BANK_FRONT_END_MENU : SFX_BANK_0;
		m_sQueueSample.m_nPriority = 0;
		m_sQueueSample.m_bIs2D = TRUE;
		SET_EMITTING_VOLUME(m_sQueueSample.m_nVolume);
		RESET_LOOP_OFFSETS
		if (stereo)
			m_sQueueSample.m_nPan = m_anRandomTable[0] & 31;
		else
			m_sQueueSample.m_nPan = 63;
		m_sQueueSample.m_bReverb = FALSE;
		SET_SOUND_REFLECTION(FALSE);
		AddSampleToRequestedQueue();
		if (stereo) {
			m_sQueueSample.m_nSampleIndex++;
			m_sQueueSample.m_nCounter = iSound++;
			m_sQueueSample.m_nPan = 127 - m_sQueueSample.m_nPan;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessCrane()
{
	CCrane *crane = (CCrane *)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity;
	float distSquared;
	bool8 distCalculated = FALSE;

	if (crane) {
		if (crane->m_nCraneStatus == CCrane::ACTIVATED) {
			if (crane->m_nCraneState != CCrane::IDLE) {
				m_sQueueSample.m_vecPos = crane->m_pCraneEntity->GetPosition();
				distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
				if (distSquared < SQR(CRANE_MAX_DIST)) {
					CalculateDistance(distCalculated, distSquared);
					m_sQueueSample.m_nVolume = ComputeVolume(CRANE_VOLUME, CRANE_MAX_DIST, m_sQueueSample.m_fDistance);
					if (m_sQueueSample.m_nVolume > 0) {
						m_sQueueSample.m_nCounter = 0;
						m_sQueueSample.m_nSampleIndex = SFX_CRANE_MAGNET;
						m_sQueueSample.m_nBankIndex = SFX_BANK_0;
						m_sQueueSample.m_bIs2D = FALSE;
						m_sQueueSample.m_nPriority = 2;
						m_sQueueSample.m_nFrequency = 6000;
						m_sQueueSample.m_nLoopCount = 0;
						SET_EMITTING_VOLUME(CRANE_VOLUME);
						SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
						m_sQueueSample.m_fSpeedMultiplier = 4.0f;
						m_sQueueSample.m_MaxDistance = CRANE_MAX_DIST;
						m_sQueueSample.m_bStatic = FALSE;
						m_sQueueSample.m_nFramesToPlay = 3;
						m_sQueueSample.m_bReverb = TRUE;
						SET_SOUND_REFLECTION(FALSE);
						AddSampleToRequestedQueue();
					}
					if (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents > 0) {
						m_sQueueSample.m_nCounter = 1;
						m_sQueueSample.m_nSampleIndex = SFX_COL_CAR_2;
						m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_COL_CAR_2);
						m_sQueueSample.m_nLoopCount = 1;
						m_sQueueSample.m_bStatic = TRUE;
						m_sQueueSample.m_bReverb = TRUE;
						SET_SOUND_REFLECTION(TRUE);
						AddSampleToRequestedQueue();
					}
				}
			}
		}
	}
}

void
cAudioManager::ProcessProjectiles()
{
	uint8 Vol;

	for (uint8 i = 0; i < NUM_PROJECTILES; i++) {
		if (CProjectileInfo::GetProjectileInfo(i)->m_bInUse) {
			switch (CProjectileInfo::GetProjectileInfo(i)->m_eWeaponType) {
			case WEAPONTYPE_ROCKETLAUNCHER:
				Vol = PROJECTILE_ROCKET_VOLUME;
				m_sQueueSample.m_MaxDistance = PROJECTILE_ROCKET_MAX_DIST;
				m_sQueueSample.m_nSampleIndex = SFX_ROCKET_FLY;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_ROCKET_FLY);
				m_sQueueSample.m_nPriority = 3;
				break;
			case WEAPONTYPE_MOLOTOV:
				Vol = PROJECTILE_MOLOTOV_VOLUME;
				m_sQueueSample.m_MaxDistance = PROJECTILE_MOLOTOV_MAX_DIST;
				m_sQueueSample.m_nSampleIndex = SFX_PED_ON_FIRE;
				m_sQueueSample.m_nBankIndex = SFX_BANK_0;
				m_sQueueSample.m_nFrequency = 32 * SampleManager.GetSampleBaseFrequency(SFX_PED_ON_FIRE) / 25;
				m_sQueueSample.m_nPriority = 7;
				break;
			default:
				continue;
			}
			m_sQueueSample.m_fSpeedMultiplier = 4.0f;
			m_sQueueSample.m_nFramesToPlay = 3;
			m_sQueueSample.m_vecPos = CProjectileInfo::ms_apProjectile[i]->GetPosition();
			float distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
			if (distSquared < SQR(m_sQueueSample.m_MaxDistance)) {
				m_sQueueSample.m_fDistance = Sqrt(distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(Vol, m_sQueueSample.m_MaxDistance, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					m_sQueueSample.m_nCounter = i;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nLoopCount = 0;
					SET_EMITTING_VOLUME(Vol);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_bStatic = FALSE;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
	}
}

void
cAudioManager::ProcessGarages()
{
	CEntity *entity;
	uint8 state;
	uint32 sampleIndex;
	uint8 j;
	float distSquared;
	bool8 distCalculated;

	static uint8 iSound = 32;

#ifdef FIX_BUGS
	for (uint32 i = 0; i < CGarages::NumGarages; i++) {
#else
	for (uint8 i = 0; i < CGarages::NumGarages; i++) {
#endif
		if (CGarages::aGarages[i].m_eGarageType == GARAGE_NONE)
			continue;
		entity = CGarages::aGarages[i].m_pDoor1;
		if (entity == nil)
			continue;
		m_sQueueSample.m_vecPos = entity->GetPosition();
		distCalculated = FALSE;
		distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (distSquared < SQR(GARAGES_MAX_DIST)) {
			state = CGarages::aGarages[i].m_eGarageState;
			if (state == GS_OPENING || state == GS_CLOSING || state == GS_AFTERDROPOFF) {
				CalculateDistance(distCalculated, distSquared);
				m_sQueueSample.m_nVolume = ComputeVolume(GARAGES_VOLUME, GARAGES_MAX_DIST, m_sQueueSample.m_fDistance);
				if (m_sQueueSample.m_nVolume > 0) {
					if (CGarages::aGarages[i].m_eGarageType == GARAGE_CRUSHER) {
						if (CGarages::aGarages[i].m_eGarageState == GS_AFTERDROPOFF) {
							if (m_FrameCounter & 1) {
								if (m_anRandomTable[1] & 1)
									sampleIndex = m_anRandomTable[2] % 5 + SFX_COL_CAR_1;
								else
									sampleIndex = m_anRandomTable[2] % 6 + SFX_COL_CAR_PANEL_1;
								m_sQueueSample.m_nSampleIndex = sampleIndex;
								m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex) >> 1;
								m_sQueueSample.m_nFrequency += RandomDisplacement(m_sQueueSample.m_nFrequency >> 4);
								m_sQueueSample.m_nLoopCount = 1;
								m_sQueueSample.m_bStatic = TRUE;
								m_sQueueSample.m_nCounter = iSound++;
								if (iSound < 32)
									iSound = 32;
							} else
								goto CheckGarageEvents; // premature exit to go straight to the for loop
						} else {
							m_sQueueSample.m_nSampleIndex = SFX_FISHING_BOAT_IDLE;
							m_sQueueSample.m_nFrequency = 6543;

							m_sQueueSample.m_nCounter = i;
							m_sQueueSample.m_nLoopCount = 0;
							m_sQueueSample.m_nFramesToPlay = 3;
							m_sQueueSample.m_bStatic = FALSE;
						}
					} else {
						m_sQueueSample.m_nSampleIndex = SFX_GARAGE_DOOR_LOOP;
						m_sQueueSample.m_nFrequency = 13961;

						m_sQueueSample.m_nCounter = i;
						m_sQueueSample.m_nLoopCount = 0;
						m_sQueueSample.m_nFramesToPlay = 3;
						m_sQueueSample.m_bStatic = FALSE;
					}

					m_sQueueSample.m_nBankIndex = SFX_BANK_0;
					m_sQueueSample.m_bIs2D = FALSE;
					m_sQueueSample.m_nPriority = 3;
					SET_EMITTING_VOLUME(GARAGES_VOLUME);
					SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
					m_sQueueSample.m_fSpeedMultiplier = 2.0f;
					m_sQueueSample.m_MaxDistance = GARAGES_MAX_DIST;
					m_sQueueSample.m_bReverb = TRUE;
					SET_SOUND_REFLECTION(FALSE);
					AddSampleToRequestedQueue();
				}
			}
		}
CheckGarageEvents:
		for (j = 0; j < m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_AudioEvents; j++) {
			switch (m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_awAudioEvent[j]) {
			case SOUND_GARAGE_DOOR_CLOSED:
			case SOUND_GARAGE_DOOR_OPENED:
				if (distSquared < SQR(GARAGES_MAX_DIST)) {
					CalculateDistance(distCalculated, distSquared);
					m_sQueueSample.m_nVolume = ComputeVolume(GARAGES_DOOR_VOLUME, GARAGES_MAX_DIST, m_sQueueSample.m_fDistance);
					if (m_sQueueSample.m_nVolume > 0) {
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
						m_sQueueSample.m_nPriority = 4;
						SET_EMITTING_VOLUME(GARAGES_DOOR_VOLUME);
						m_sQueueSample.m_fSpeedMultiplier = 0.0f;
						m_sQueueSample.m_MaxDistance = GARAGES_MAX_DIST;
						m_sQueueSample.m_bReverb = TRUE; 
						m_sQueueSample.m_bIs2D = FALSE;
						m_sQueueSample.m_bStatic = TRUE;
						m_sQueueSample.m_nLoopCount = 1;
						RESET_LOOP_OFFSETS
						m_sQueueSample.m_nCounter = iSound++;
						if (iSound < 32)
							iSound = 32;
						SET_SOUND_REFLECTION(TRUE);
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
	float distSquared;
	bool8 distCalculated = FALSE;

	m_sQueueSample.m_vecPos = ((CParticleObject*)m_asAudioEntities[m_sQueueSample.m_nEntityIndex].m_pEntity)->GetPosition();
	distSquared = GetDistanceSquared(m_sQueueSample.m_vecPos);
	if (distSquared < SQR(FIRE_HYDRANT_MAX_DIST)) {
		CalculateDistance(distCalculated, distSquared);
		m_sQueueSample.m_nVolume = ComputeVolume(FIRE_HYDRANT_VOLUME, FIRE_HYDRANT_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_nSampleIndex = SFX_JUMBO_TAXI;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 4;
			m_sQueueSample.m_nFrequency = 15591;
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(FIRE_HYDRANT_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_MaxDistance = FIRE_HYDRANT_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 3;
			m_sQueueSample.m_bReverb = TRUE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
	}
}

#pragma region BRIDGE
void
cAudioManager::ProcessBridge()
{
	float dist;
	bool8 distCalculated = FALSE;

	if (CBridge::pLiftRoad) {
		m_sQueueSample.m_vecPos = CBridge::pLiftRoad->GetPosition();
		dist = GetDistanceSquared(m_sQueueSample.m_vecPos);
		if (dist < SQR(BRIDGE_MAX_DIST)) {
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
	if (!CStats::CommercialPassed)
		return;

	if (m_sQueueSample.m_fDistance < BRIDGE_MAX_DIST) {
		m_sQueueSample.m_nVolume = ComputeVolume(BRIDGE_WARNING_VOLUME, BRIDGE_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 0;
			m_sQueueSample.m_nSampleIndex = SFX_BRIDGE_OPEN_WARNING;
			m_sQueueSample.m_nBankIndex = SFX_BANK_GENERIC_EXTRA;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(SFX_BRIDGE_OPEN_WARNING);
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(BRIDGE_WARNING_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_MaxDistance = BRIDGE_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 8;
			m_sQueueSample.m_bReverb = FALSE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessBridgeMotor()
{
	if (m_sQueueSample.m_fDistance < BRIDGE_MOTOR_MAX_DIST) {
		m_sQueueSample.m_nVolume = ComputeVolume(BRIDGE_MOTOR_VOLUME, BRIDGE_MOTOR_MAX_DIST, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 1;
			m_sQueueSample.m_nSampleIndex = SFX_FISHING_BOAT_IDLE; // todo check sfx name
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = 5500;
			m_sQueueSample.m_nLoopCount = 0;
			SET_EMITTING_VOLUME(BRIDGE_MOTOR_VOLUME);
			SET_LOOP_OFFSETS(m_sQueueSample.m_nSampleIndex)
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_MaxDistance = BRIDGE_MOTOR_MAX_DIST;
			m_sQueueSample.m_bStatic = FALSE;
			m_sQueueSample.m_nFramesToPlay = 3;
			m_sQueueSample.m_bReverb = FALSE;
			AddSampleToRequestedQueue();
		}
	}
}

void
cAudioManager::ProcessBridgeOneShots()
{
	float maxDist;

	if (CBridge::State == STATE_LIFT_PART_IS_UP && CBridge::OldState == STATE_LIFT_PART_MOVING_UP) {
		maxDist = BRIDGE_MOTOR_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	} else if (CBridge::State == STATE_LIFT_PART_IS_DOWN && CBridge::OldState == STATE_LIFT_PART_MOVING_DOWN) {
		maxDist = BRIDGE_MOTOR_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	} else if (CBridge::State == STATE_LIFT_PART_MOVING_UP && CBridge::OldState == STATE_LIFT_PART_ABOUT_TO_MOVE_UP) {
		maxDist = BRIDGE_MOTOR_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	} else if (CBridge::State == STATE_LIFT_PART_MOVING_DOWN && CBridge::OldState == STATE_LIFT_PART_IS_UP) {
		maxDist = BRIDGE_MOTOR_MAX_DIST;
		m_sQueueSample.m_nSampleIndex = SFX_COL_CONTAINER_1;
	} else return;

	if (m_sQueueSample.m_fDistance < maxDist) {
		m_sQueueSample.m_nVolume = ComputeVolume(BRIDGE_MOTOR_VOLUME, maxDist, m_sQueueSample.m_fDistance);
		if (m_sQueueSample.m_nVolume > 0) {
			m_sQueueSample.m_nCounter = 2;
			m_sQueueSample.m_nBankIndex = SFX_BANK_0;
			m_sQueueSample.m_bIs2D = FALSE;
			m_sQueueSample.m_nPriority = 1;
			m_sQueueSample.m_nFrequency = SampleManager.GetSampleBaseFrequency(m_sQueueSample.m_nSampleIndex);
			m_sQueueSample.m_nLoopCount = 1;
			SET_EMITTING_VOLUME(BRIDGE_MOTOR_VOLUME);
			RESET_LOOP_OFFSETS
			m_sQueueSample.m_fSpeedMultiplier = 2.0f;
			m_sQueueSample.m_MaxDistance = maxDist;
			m_sQueueSample.m_bStatic = TRUE;
			m_sQueueSample.m_bReverb = FALSE;
			SET_SOUND_REFLECTION(FALSE);
			AddSampleToRequestedQueue();
		}
	}
}
#pragma endregion

#pragma region MISSION_AUDIO
bool8 g_bMissionAudioLoadFailed;

struct MissionAudioData {
	const char *m_pName;
	uint32 m_nId;
};

Const MissionAudioData MissionAudioNameSfxAssoc[] = {
	{"lib_a1", SFX_MISSION_LIB_A1}, {"lib_a2", SFX_MISSION_LIB_A2},   {"lib_a", SFX_MISSION_LIB_A},
	{"lib_b", SFX_MISSION_LIB_B},   {"lib_c", SFX_MISSION_LIB_C},     {"lib_d", SFX_MISSION_LIB_D},
	{"l2_a", SFX_MISSION_L2_A},     {"j4t_1", SFX_MISSION_J4T_1},     {"j4t_2", SFX_MISSION_J4T_2},
	{"j4t_3", SFX_MISSION_J4T_3},   {"j4t_4", SFX_MISSION_J4T_4},     {"j4_a", SFX_MISSION_J4_A},
	{"j4_b", SFX_MISSION_J4_B},     {"j4_c", SFX_MISSION_J4_C},       {"j4_d", SFX_MISSION_J4_D},
	{"j4_e", SFX_MISSION_J4_E},     {"j4_f", SFX_MISSION_J4_F},       {"j6_1", SFX_MISSION_J6_1},
	{"j6_a", SFX_MISSION_J6_A},     {"j6_b", SFX_MISSION_J6_B},       {"j6_c", SFX_MISSION_J6_C},
	{"j6_d", SFX_MISSION_J6_D},     {"t4_a", SFX_MISSION_T4_A},       {"s1_a", SFX_MISSION_S1_A},
	{"s1_a1", SFX_MISSION_S1_A1},   {"s1_b", SFX_MISSION_S1_B},       {"s1_c", SFX_MISSION_S1_C},
	{"s1_c1", SFX_MISSION_S1_C1},   {"s1_d", SFX_MISSION_S1_D},       {"s1_e", SFX_MISSION_S1_E},
	{"s1_f", SFX_MISSION_S1_F},     {"s1_g", SFX_MISSION_S1_G},       {"s1_h", SFX_MISSION_S1_H},
	{"s1_i", SFX_MISSION_S1_I},     {"s1_j", SFX_MISSION_S1_J},       {"s1_k", SFX_MISSION_S1_K},
	{"s1_l", SFX_MISSION_S1_L},     {"s3_a", SFX_MISSION_S3_A},       {"s3_b", SFX_MISSION_S3_B},
	{"el3_a", SFX_MISSION_EL3_A},   {"mf1_a", SFX_MISSION_MF1_A},     {"mf2_a", SFX_MISSION_MF2_A},
	{"mf3_a", SFX_MISSION_MF3_A},   {"mf3_b", SFX_MISSION_MF3_B},     {"mf3_b1", SFX_MISSION_MF3_B1},
	{"mf3_c", SFX_MISSION_MF3_C},   {"mf4_a", SFX_MISSION_MF4_A},     {"mf4_b", SFX_MISSION_MF4_B},
	{"mf4_c", SFX_MISSION_MF4_C},   {"a1_a", SFX_MISSION_A1_A},       {"a3_a", SFX_MISSION_A3_A},
	{"a5_a", SFX_MISSION_A5_A},     {"a4_a", SFX_MISSION_A4_A},       {"a4_b", SFX_MISSION_A4_B},
	{"a4_c", SFX_MISSION_A4_C},     {"a4_d", SFX_MISSION_A4_D},       {"k1_a", SFX_MISSION_K1_A},
	{"k3_a", SFX_MISSION_K3_A},     {"r1_a", SFX_MISSION_R1_A},       {"r2_a", SFX_MISSION_R2_A},
	{"r2_b", SFX_MISSION_R2_B},     {"r2_c", SFX_MISSION_R2_C},       {"r2_d", SFX_MISSION_R2_D},
	{"r2_e", SFX_MISSION_R2_E},     {"r2_f", SFX_MISSION_R2_F},       {"r2_g", SFX_MISSION_R2_G},
	{"r2_h", SFX_MISSION_R2_H},     {"r5_a", SFX_MISSION_R5_A},       {"r6_a", SFX_MISSION_R6_A},
	{"r6_a1", SFX_MISSION_R6_A1},   {"r6_b", SFX_MISSION_R6_B},       {"lo2_a", SFX_MISSION_LO2_A},
	{"lo6_a", SFX_MISSION_LO6_A},   {"yd2_a", SFX_MISSION_YD2_A},     {"yd2_b", SFX_MISSION_YD2_B},
	{"yd2_c", SFX_MISSION_YD2_C},   {"yd2_c1", SFX_MISSION_YD2_C1},   {"yd2_d", SFX_MISSION_YD2_D},
	{"yd2_e", SFX_MISSION_YD2_E},   {"yd2_f", SFX_MISSION_YD2_F},     {"yd2_g", SFX_MISSION_YD2_G},
	{"yd2_h", SFX_MISSION_YD2_H},   {"yd2_ass", SFX_MISSION_YD2_ASS}, {"yd2_ok", SFX_MISSION_YD2_OK},
	{"h5_a", SFX_MISSION_H5_A},     {"h5_b", SFX_MISSION_H5_B},       {"h5_c", SFX_MISSION_H5_C},
	{"ammu_a", SFX_MISSION_AMMU_A}, {"ammu_b", SFX_MISSION_AMMU_B},   {"ammu_c", SFX_MISSION_AMMU_C},
#if GTA_VERSION < GTA3_PC_10
	{"ammu_d", SFX_AMMU_D }, {"ammu_e", SFX_AMMU_E}, {"ammu_f", SFX_AMMU_F},
	{"ammu_g", SFX_MISSION_AMMU_A},  {"ammu_h", SFX_MISSION_AMMU_A}, {"ammu_i", SFX_MISSION_AMMU_A},
	{"ammu_j", SFX_MISSION_AMMU_A}, {"ammu_k", SFX_MISSION_AMMU_A},
#endif
	{"door_1", SFX_MISSION_DOOR_1}, {"door_2", SFX_MISSION_DOOR_2},   {"door_3", SFX_MISSION_DOOR_3},
	{"door_4", SFX_MISSION_DOOR_4}, {"door_5", SFX_MISSION_DOOR_5},   {"door_6", SFX_MISSION_DOOR_6},
	{"t3_a", SFX_MISSION_T3_A},     {"t3_b", SFX_MISSION_T3_B},       {"t3_c", SFX_MISSION_T3_C},
	{"k1_b", SFX_MISSION_K1_B},     {"c_1", SFX_MISSION_CAT1},        {nil, 0}};

uint32
FindMissionAudioSfx(const char *name)
{
	for (uint32 i = 0; MissionAudioNameSfxAssoc[i].m_pName != nil; i++) {
		if (!CGeneral::faststricmp(MissionAudioNameSfxAssoc[i].m_pName, name))
			return MissionAudioNameSfxAssoc[i].m_nId;
	}
	debug("Can't find mission audio %s", name);
	return NO_SAMPLE;
}

bool8
cAudioManager::MissionScriptAudioUsesPoliceChannel(uint32 soundMission)
{
	switch (soundMission) {
	case SFX_MISSION_J6_D:
	case SFX_MISSION_T4_A:
	case SFX_MISSION_S1_H:
	case SFX_MISSION_S3_B:
	case SFX_MISSION_EL3_A:
	case SFX_MISSION_A3_A:
	case SFX_MISSION_A5_A:
	case SFX_MISSION_K1_A:
	case SFX_MISSION_R1_A:
	case SFX_MISSION_R5_A:
	case SFX_MISSION_LO2_A:
	case SFX_MISSION_LO6_A:
		return TRUE;
	default:
		return FALSE;
	}
}

void
cAudioManager::PreloadMissionAudio(Const char *name)
{
	if (m_bIsInitialised) {
		uint32 missionAudioSfx = FindMissionAudioSfx(name);
		if (missionAudioSfx != NO_SAMPLE) {
			m_nMissionAudioSampleIndex = missionAudioSfx;
			m_nMissionAudioLoadingStatus = LOADING_STATUS_NOT_LOADED;
			m_nMissionAudioPlayStatus = PLAY_STATUS_STOPPED;
			m_bIsMissionAudioPlaying = FALSE;
#ifdef GTA_PS2
			m_nMissionAudioFramesToPlay = m_nTimeSpent * SampleManager.GetSampleLength(missionAudioSfx) / SampleManager.GetSampleBaseFrequency(missionAudioSfx);
			m_nMissionAudioFramesToPlay = 11 * m_nMissionAudioFramesToPlay / 10;
#else
			m_nMissionAudioFramesToPlay = m_nTimeSpent * SampleManager.GetStreamedFileLength(missionAudioSfx) / 1000;
			m_nMissionAudioFramesToPlay *= 4;
#endif
			m_bIsMissionAudioAllowedToPlay = FALSE;
			m_bIsMissionAudio2D = TRUE;
			g_bMissionAudioLoadFailed = FALSE;
		}
	}
}

uint8
cAudioManager::GetMissionAudioLoadingStatus()
{
	if (m_bIsInitialised)
		return m_nMissionAudioLoadingStatus;

	return LOADING_STATUS_LOADED;
}

void
cAudioManager::SetMissionAudioLocation(float x, float y, float z)
{
	if (m_bIsInitialised) {
		m_bIsMissionAudio2D = FALSE;
		m_vecMissionAudioPosition = CVector(x, y, z);
	}
}

void
cAudioManager::PlayLoadedMissionAudio()
{
	if (m_bIsInitialised && m_nMissionAudioSampleIndex != NO_SAMPLE && m_nMissionAudioLoadingStatus == LOADING_STATUS_LOADED &&
	    m_nMissionAudioPlayStatus == PLAY_STATUS_STOPPED)
		m_bIsMissionAudioAllowedToPlay = TRUE;
}

bool8
cAudioManager::IsMissionAudioSampleFinished()
{
	if (m_bIsInitialised)
		return m_nMissionAudioPlayStatus == PLAY_STATUS_FINISHED;

	static uint32 cPretendFrame = 1;

	return (cPretendFrame++ & 63) == 0;
}

void
cAudioManager::ClearMissionAudio()
{
	if (m_bIsInitialised) {
		m_nMissionAudioSampleIndex = NO_SAMPLE;
		m_nMissionAudioLoadingStatus = LOADING_STATUS_NOT_LOADED;
		m_nMissionAudioPlayStatus = PLAY_STATUS_STOPPED;
		m_bIsMissionAudioPlaying = FALSE;
		m_bIsMissionAudioAllowedToPlay = FALSE;
		m_bIsMissionAudio2D = TRUE;
		m_nMissionAudioFramesToPlay = 0;
	}
}

void
cAudioManager::ProcessMissionAudio()
{
	float dist;
	uint8 Vol;
	uint8 pan;
	float distSquared;
	CVector vec;

	static uint8 nCheckPlayingDelay = 0;
	static uint8 nFramesUntilFailedLoad = 0;
	static uint8 nFramesForPretendPlaying = 0;

	if (m_bIsInitialised && m_nMissionAudioSampleIndex != NO_SAMPLE) {
		switch (m_nMissionAudioLoadingStatus) {
		case LOADING_STATUS_NOT_LOADED:
#ifdef GTA_PS2
			SampleManager.LoadPedComment(m_nMissionAudioSampleIndex);
			m_nMissionAudioLoadingStatus = LOADING_STATUS_LOADING;
#else
			SampleManager.PreloadStreamedFile(m_nMissionAudioSampleIndex, 1);
			m_nMissionAudioLoadingStatus = LOADING_STATUS_LOADED;
#endif
			nFramesUntilFailedLoad = 0;
			break;
		case LOADING_STATUS_LOADING:
#ifdef GTA_PS2
			if (SampleManager.IsPedCommentLoaded(m_nMissionAudioSampleIndex) == TRUE)
				m_nMissionAudioLoadingStatus = LOADING_STATUS_LOADED;
				// fallthrough
			else
#endif
			if (++nFramesUntilFailedLoad >= 90) {
				nFramesForPretendPlaying = 0;
				g_bMissionAudioLoadFailed = TRUE;
				nFramesUntilFailedLoad = 0;
				m_nMissionAudioLoadingStatus = LOADING_STATUS_LOADED;
				return;
			}
#ifdef GTA_PS2
			else {
				// try loading again
				SampleManager.LoadPedComment(m_nMissionAudioSampleIndex);
				return;
			}
#endif
		case LOADING_STATUS_LOADED:
			if (!m_bIsMissionAudioAllowedToPlay)
				break;
			if (g_bMissionAudioLoadFailed) {
				if (m_bTimerJustReset) {
					ClearMissionAudio();
#ifdef GTA_PS2
					SampleManager.StopChannel(CHANNEL_POLICE_RADIO); // why?
					SampleManager.StopChannel(CHANNEL_MISSION_AUDIO);
#else
					SampleManager.StopStreamedFile(1);
#endif
					nFramesForPretendPlaying = 0;
					nCheckPlayingDelay = 0;
					nFramesUntilFailedLoad = 0;
				} else if (!m_bIsPaused) {
					if (++nFramesForPretendPlaying >= 120) {
						m_nMissionAudioPlayStatus = PLAY_STATUS_FINISHED;
						m_nMissionAudioSampleIndex = NO_SAMPLE;
					} else
						m_nMissionAudioPlayStatus = PLAY_STATUS_PLAYING;
				}
				break;
			}
			switch (m_nMissionAudioPlayStatus) {
			case PLAY_STATUS_STOPPED:
				if (MissionScriptAudioUsesPoliceChannel(m_nMissionAudioSampleIndex))
					SetMissionScriptPoliceAudio(m_nMissionAudioSampleIndex);
				else {
#ifdef GTA_PS2
					SampleManager.InitialiseChannel(CHANNEL_MISSION_AUDIO, m_nMissionAudioSampleIndex, SFX_BANK_PED_COMMENTS);
					if (m_bIsPaused)
						SampleManager.SetChannelFrequency(CHANNEL_MISSION_AUDIO, 0);
					else
						SampleManager.SetChannelFrequency(CHANNEL_MISSION_AUDIO, SampleManager.GetSampleBaseFrequency(m_nMissionAudioSampleIndex));
#else
					if (m_bIsPaused)
						SampleManager.PauseStream(TRUE, 1);
#endif
					if (m_bIsMissionAudio2D) {
#ifdef GTA_PS2
						SampleManager.SetChannelVolume(CHANNEL_MISSION_AUDIO, MISSION_AUDIO_VOLUME);
						SampleManager.SetChannelPan(CHANNEL_MISSION_AUDIO, 63);
						SampleManager.SetChannelReverbFlag(CHANNEL_MISSION_AUDIO, FALSE);
#else
						SampleManager.SetStreamedVolumeAndPan(MISSION_AUDIO_VOLUME, 63, TRUE, 1);
#endif
					} else {
						distSquared = GetDistanceSquared(m_vecMissionAudioPosition);
						if (distSquared < SQR(MISSION_AUDIO_MAX_DIST)) {
							dist = Sqrt(distSquared);
							Vol = ComputeVolume(MISSION_AUDIO_VOLUME, MISSION_AUDIO_MAX_DIST, dist);
							TranslateEntity(&m_vecMissionAudioPosition, &vec);
							pan = ComputePan(MISSION_AUDIO_MAX_DIST, &vec);
						} else {
							Vol = 0;
							pan = 63;
						}
#ifdef GTA_PS2
						SampleManager.SetChannelVolume(CHANNEL_MISSION_AUDIO, Vol);
						SampleManager.SetChannelPan(CHANNEL_MISSION_AUDIO, pan);
						SampleManager.SetChannelReverbFlag(CHANNEL_MISSION_AUDIO, TRUE);
#else
						SampleManager.SetStreamedVolumeAndPan(Vol, pan, TRUE, 1);
#endif
					}
#ifdef GTA_PS2
					SampleManager.StartChannel(CHANNEL_MISSION_AUDIO);
#else
					SampleManager.StartPreloadedStreamedFile(1);
#endif
				}
				m_nMissionAudioPlayStatus = PLAY_STATUS_PLAYING;
				nCheckPlayingDelay = 30;
				break;
			case PLAY_STATUS_PLAYING:
				if (m_bTimerJustReset) {
					ClearMissionAudio();
#ifdef GTA_PS2
					SampleManager.StopChannel(CHANNEL_POLICE_RADIO); // why?
					SampleManager.StopChannel(CHANNEL_MISSION_AUDIO);
#else
					SampleManager.StopStreamedFile(1);
#endif
					return;
				}
				if (MissionScriptAudioUsesPoliceChannel(m_nMissionAudioSampleIndex)) {
					if (!m_bIsPaused) {
						if (nCheckPlayingDelay > 0) {
							nCheckPlayingDelay--;
						} else if (GetMissionScriptPoliceAudioPlayingStatus() == PLAY_STATUS_FINISHED || m_nMissionAudioFramesToPlay-- == 0) {
							m_nMissionAudioPlayStatus = PLAY_STATUS_FINISHED;
							m_nMissionAudioSampleIndex = NO_SAMPLE;
#ifdef GTA_PS2
							SampleManager.StopChannel(CHANNEL_POLICE_RADIO);
#else
							SampleManager.StopStreamedFile(1);
#endif
							m_nMissionAudioFramesToPlay = 0;
						}
					}
				} else if (m_bIsMissionAudioPlaying) {
#ifdef GTA_PS2
					if (!SampleManager.GetChannelUsedFlag(CHANNEL_MISSION_AUDIO) && !m_bIsPaused && !m_bWasPaused) {
#else
					if (!SampleManager.IsStreamPlaying(1) && !m_bIsPaused && !m_bWasPaused) {
#endif
						m_nMissionAudioPlayStatus = PLAY_STATUS_FINISHED;
						m_nMissionAudioSampleIndex = NO_SAMPLE;
#ifdef GTA_PS2
						SampleManager.StopChannel(CHANNEL_MISSION_AUDIO);
#else
						SampleManager.StopStreamedFile(1);
#endif
						m_nMissionAudioFramesToPlay = 0;
					} else {
#ifdef GTA_PS2
						if (m_bIsPaused)
							SampleManager.SetChannelFrequency(CHANNEL_MISSION_AUDIO, 0);
						else
							SampleManager.SetChannelFrequency(CHANNEL_MISSION_AUDIO, SampleManager.GetSampleBaseFrequency(m_nMissionAudioSampleIndex));
#else
						if (m_bIsPaused)
							SampleManager.PauseStream(TRUE, 1);
						else
							SampleManager.PauseStream(FALSE, 1);
#endif
					}
				} else {
					if (m_bIsPaused)
						break;
					if (nCheckPlayingDelay-- > 0) {
#ifdef GTA_PS2
						if (!SampleManager.GetChannelUsedFlag(CHANNEL_MISSION_AUDIO))
#else
						if (!SampleManager.IsStreamPlaying(1))
#endif
							break;
						nCheckPlayingDelay = 0;
					}
					m_bIsMissionAudioPlaying = TRUE;
				}
				break;
			default:
				break;
			}
			break;
		default:
			return;
		}
	}
}
#pragma endregion All the mission audio stuff
