#include "common.h"
#include "patcher.h"
#include "Weather.h"
#include "Collision.h"
#include "SurfaceTable.h"

float (*CSurfaceTable::ms_aAdhesiveLimitTable)[NUMADHESIVEGROUPS] = (float (*)[NUMADHESIVEGROUPS])0x8E29D4;

int
CSurfaceTable::GetAdhesionGroup(uint8 surfaceType)
{
	switch(surfaceType){
	case SURFACE_0:		return ADHESIVE_ROAD;
	case SURFACE_1:		return ADHESIVE_ROAD;
	case SURFACE_2:		return ADHESIVE_LOOSE;
	case SURFACE_3:		return ADHESIVE_LOOSE;
	case SURFACE_4:		return ADHESIVE_HARD;
	case SURFACE_5:		return ADHESIVE_ROAD;
	case SURFACE_6:		return ADHESIVE_HARD;
	case SURFACE_7:		return ADHESIVE_HARD;
	case SURFACE_8:		return ADHESIVE_HARD;
	case SURFACE_9:		return ADHESIVE_HARD;
	case SURFACE_10:	return ADHESIVE_HARD;
	case SURFACE_11:	return ADHESIVE_HARD;
	case SURFACE_12:	return ADHESIVE_HARD;
	case SURFACE_13:	return ADHESIVE_HARD;
	case SURFACE_14:	return ADHESIVE_HARD;
	case SURFACE_15:	return ADHESIVE_HARD;
	case SURFACE_16:	return ADHESIVE_HARD;
	case SURFACE_17:	return ADHESIVE_RUBBER;
	case SURFACE_18:	return ADHESIVE_LOOSE;
	case SURFACE_19:	return ADHESIVE_WET;
	case SURFACE_20:	return ADHESIVE_ROAD;
	case SURFACE_21:	return ADHESIVE_ROAD;
	case SURFACE_22:	return ADHESIVE_ROAD;
	case SURFACE_23:	return ADHESIVE_RUBBER;
	case SURFACE_24:	return ADHESIVE_HARD;
	case SURFACE_25:	return ADHESIVE_LOOSE;
	case SURFACE_26:	return ADHESIVE_LOOSE;
	case SURFACE_27:	return ADHESIVE_HARD;
	case SURFACE_28:	return ADHESIVE_HARD;
	case SURFACE_29:	return ADHESIVE_RUBBER;
	case SURFACE_30:	return ADHESIVE_LOOSE;
	case SURFACE_31:	return ADHESIVE_HARD;
	case SURFACE_32:	return ADHESIVE_HARD;
	default:		return ADHESIVE_ROAD;
	}
}

float
CSurfaceTable::GetWetMultiplier(uint8 surfaceType)
{
	switch(surfaceType){
	case SURFACE_0:
	case SURFACE_1:
	case SURFACE_4:
	case SURFACE_5:
	case SURFACE_8:
	case SURFACE_20:
	case SURFACE_21:
	case SURFACE_22:
	case SURFACE_25:
	case SURFACE_30:
	case SURFACE_31:
		return 1.0f - CWeather::WetRoads*0.25f;

	case SURFACE_2:
	case SURFACE_6:
	case SURFACE_7:
	case SURFACE_9:
	case SURFACE_10:
	case SURFACE_11:
	case SURFACE_12:
	case SURFACE_13:
	case SURFACE_14:
	case SURFACE_15:
	case SURFACE_16:
	case SURFACE_17:
	case SURFACE_23:
	case SURFACE_24:
	case SURFACE_26:
	case SURFACE_27:
	case SURFACE_28:
	case SURFACE_29:
	case SURFACE_32:
		return 1.0f - CWeather::WetRoads*0.4f;

	default:
		return 1.0f;
	}
}

float
CSurfaceTable::GetAdhesiveLimit(CColPoint &colpoint)
{
	return ms_aAdhesiveLimitTable[GetAdhesionGroup(colpoint.surfaceB)][GetAdhesionGroup(colpoint.surfaceA)];
}
