#pragma once

#include "Placeable.h"

enum eParticleObjectType
{
	POBJECT_PAVEMENT_STEAM,
	POBJECT_PAVEMENT_STEAM_SLOWMOTION,
	POBJECT_WALL_STEAM,
	POBJECT_WALL_STEAM_SLOWMOTION,
	POBJECT_DARK_SMOKE,
	POBJECT_FIRE_HYDRANT,
	POBJECT_CAR_WATER_SPLASH,
	POBJECT_PED_WATER_SPLASH,
	POBJECT_SPLASHES_AROUND,
	POBJECT_SMALL_FIRE,
	POBJECT_BIG_FIRE,
	POBJECT_DRY_ICE,
	POBJECT_DRY_ICE_SLOWMOTION,
	POBJECT_FIRE_TRAIL,
	POBJECT_SMOKE_TRAIL,
	POBJECT_FIREBALL_AND_SMOKE,
	POBJECT_ROCKET_TRAIL,
	POBJECT_EXPLOSION_ONCE,
	POBJECT_CATALINAS_GUNFLASH,
	POBJECT_CATALINAS_SHOTGUNFLASH,
};

class CParticleObject : CPlaceable
{
public:
	static void AddObject(uint16 type, const CVector &pos, bool remove);
	static void AddObject(uint16 type, const CVector &pos, float size, bool remove);
	static void AddObject(uint16 type, const CVector &pos, const CVector &dir, float size, bool remove);
	static void Initialise();
	static void UpdateAll();

	void dtor() { this->CParticleObject::~CParticleObject(); }
};
