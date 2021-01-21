#pragma once

#include "ModelInfo.h"

#define MODELINDICES \
	X("fire_hydrant",	MI_FIRE_HYDRANT) \
	X("phonesign",		MI_PHONESIGN) \
	X("noparkingsign1",	MI_NOPARKINGSIGN1) \
	X("bussign1",		MI_BUSSIGN1) \
	X("roadworkbarrier1",	MI_ROADWORKBARRIER1) \
	X("dump1",		MI_DUMP1) \
	X("trafficcone",	MI_TRAFFICCONE) \
	X("newsstand1",		MI_NEWSSTAND) \
	X("postbox1",		MI_POSTBOX1) \
	X("bin1",		MI_BIN) \
	X("wastebin",		MI_WASTEBIN) \
	X("phonebooth1",	MI_PHONEBOOTH1) \
	X("parkingmeter",	MI_PARKINGMETER) \
	X("parkingmeterg",	MI_PARKINGMETER2) \
	X("mall_fans",		MI_MALLFAN) \
	X("htl_fan_rotate_nt",	MI_HOTELFAN_NIGHT) \
	X("htl_fan_rotate_dy",	MI_HOTELFAN_DAY) \
	X("hotroomfan",		MI_HOTROOMFAN) \
	X("trafficlight1",	MI_TRAFFICLIGHTS) \
	X("MTraffic4",		MI_TRAFFICLIGHTS_VERTICAL) \
	X("MTraffic1",		MI_TRAFFICLIGHTS_MIAMI) \
	X("MTraffic2",		MI_TRAFFICLIGHTS_TWOVERTICAL) \
	X("lamppost1",		MI_SINGLESTREETLIGHTS1) \
	X("lamppost2",		MI_SINGLESTREETLIGHTS2) \
	X("lamppost3",		MI_SINGLESTREETLIGHTS3) \
	X("doublestreetlght1",	MI_DOUBLESTREETLIGHTS) \
	X("Streetlamp1",	MI_STREETLAMP1) \
	X("Streetlamp2",	MI_STREETLAMP2) \
	X("veg_tree3",		MI_TREE2) \
	X("veg_treea1",		MI_TREE3) \
	X("veg_treeb1",		MI_TREE6) \
	X("veg_treea3",		MI_TREE8) \
	X("doc_crane_cab0",	MODELID_CRANE_1) \
	X("doc_crane_cab01",	MODELID_CRANE_2) \
	X("doc_crane_cab02",	MODELID_CRANE_3) \
	X("doc_crane_cab03",	MODELID_CRANE_4) \
	X("boatcranelg0",	MODELID_CRANE_5) \
	X("LODnetopa0",		MODELID_CRANE_6) \
	X("package1",		MI_COLLECTABLE1) \
	X("Money",		MI_MONEY) \
	X("barrel1",		MI_CARMINE) \
	X("dk_paynspraydoor",	MI_GARAGEDOOR2) \
	X("dk_waretankdoor1",	MI_GARAGEDOOR3) \
	X("hav_garagedoor1",	MI_GARAGEDOOR4) \
	X("hav_garagedoor02",	MI_GARAGEDOOR5) \
	X("hav_garagedoor03",	MI_GARAGEDOOR6) \
	X("hav_garagedoor04",	MI_GARAGEDOOR7) \
	X("lh_showdoor03",	MI_GARAGEDOOR9) \
	X("lh_showdoor1",	MI_GARAGEDOOR10) \
	X("lhtankdoor",		MI_GARAGEDOOR11) \
	X("nbtgardoor",		MI_GARAGEDOOR12) \
	X("dk_camjonesdoor",	MI_GARAGEDOOR13) \
	X("nbtgardoor02",	MI_GARAGEDOOR14) \
	X("dt_savedra",		MI_GARAGEDOOR15) \
	X("dt_savedrb",		MI_GARAGEDOOR16) \
	X("dk_bombdoor",	MI_GARAGEDOOR18) \
	X("haiwshpnsdoor",	MI_GARAGEDOOR19) \
	X("wshpnsdoor",		MI_GARAGEDOOR20) \
	X("nbecpnsdoor",	MI_GARAGEDOOR21) \
	X("nbtgardoor03",	MI_GARAGEDOOR22) \
	X("dt_savedrc",		MI_GARAGEDOOR23) \
	X("dt_savedrd",		MI_GARAGEDOOR24) \
	X("man_frntstepGD",	MI_GARAGEDOOR25) \
	X("svegrgedoor",	MI_GARAGEDOOR26) \
	X("barrel2",		MI_NAUTICALMINE) \
	X("briefcase",		MI_BRIEFCASE) \
	X("wglasssmash",	MI_GLASS1) \
	X("glassfx_composh",	MI_GLASS8) \
	X("barrel4",		MI_EXPLODINGBARREL) \
	X("adrenaline",		MI_PICKUP_ADRENALINE) \
	X("bodyarmour",		MI_PICKUP_BODYARMOUR) \
	X("info",		MI_PICKUP_INFO) \
	X("health",		MI_PICKUP_HEALTH) \
	X("bonus",		MI_PICKUP_BONUS) \
	X("bribe",		MI_PICKUP_BRIBE) \
	X("killfrenzy",		MI_PICKUP_KILLFRENZY) \
	X("camerapickup",	MI_PICKUP_CAMERA) \
	X("bigdollar",		MI_PICKUP_REVENUE) \
	X("pickupsave",		MI_PICKUP_SAVEGAME) \
	X("property_locked",	MI_PICKUP_PROPERTY) \
	X("property_fsale",	MI_PICKUP_PROPERTY_FORSALE) \
	X("clothesp",		MI_PICKUP_CLOTHES) \
	X("bollardlight",	MI_BOLLARDLIGHT) \
	X("bar_barrier10",	MI_FENCE) \
	X("bar_barrier12",	MI_FENCE2) \
	X("petrolpump",		MI_PETROLPUMP) \
	X("washgaspump",	MI_PETROLPUMP2) \
	X("bouy",		MI_BUOY) \
	X("parktable1",		MI_PARKTABLE) \
	X("lamppost1",		MI_LAMPPOST1) \
	X("veg_palm04",		MI_VEG_PALM01) \
	X("veg_palwee02",	MI_VEG_PALM02) \
	X("veg_palmkbb11",	MI_VEG_PALM03) \
	X("veg_palmkb4",	MI_VEG_PALM04) \
	X("veg_palm02",		MI_VEG_PALM05) \
	X("veg_palmkb3",	MI_VEG_PALM06) \
	X("veg_palmbig14",	MI_VEG_PALM07) \
	X("veg_palm01",		MI_VEG_PALM08) \
	X("mlamppost",		MI_MLAMPPOST) \
	X("roadworkbarrier1",	MI_BARRIER1) \
	X("littleha_police",	MI_LITTLEHA_POLICE) \
	X("telgrphpole02",	MI_TELPOLE02) \
	X("trafficlight1",	MI_TRAFFICLIGHT01) \
	X("parkbench1",		MI_PARKBENCH) \
	X("plc_stinger",	MI_PLC_STINGER) \
	X("od_lightbeam",	MI_LIGHTBEAM) \
	X("ap_radar1_01",	MI_AIRPORTRADAR) \
	X("rcbomb",		MI_RCBOMB) \
	X("beachball",		MI_BEACHBALL) \
	X("sandcastle1",	MI_SANDCASTLE1) \
	X("sandcastle2",	MI_SANDCASTLE2) \
	X("jellyfish",		MI_JELLYFISH) \
	X("jellyfish01",	MI_JELLYFISH01) \
	X("fish1single",	MI_FISH1SINGLE) \
	X("fish1s",		MI_FISH1S) \
	X("fish2single",	MI_FISH2SINGLE) \
	X("fish2s",		MI_FISH2S) \
	X("fish3single",	MI_FISH3SINGLE) \
	X("fish3s",		MI_FISH3S) \
	X("turtle",		MI_TURTLE) \
	X("dolphin",		MI_DOLPHIN) \
	X("shark",		MI_SHARK) \
	X("submarine",		MI_SUBMARINE) \
	X("Esc_step",		MI_ESCALATORSTEP) \
	X("lounge_wood_up",	MI_LOUNGE_WOOD_UP) \
	X("lounge_towel_up",	MI_LOUNGE_TOWEL_UP) \
	X("lounge_wood_dn",	MI_LOUNGE_WOOD_DN) \
	X("lotion",		MI_LOTION) \
	X("beachtowel01",	MI_BEACHTOWEL01) \
	X("beachtowel02",	MI_BEACHTOWEL02) \
	X("beachtowel03",	MI_BEACHTOWEL03) \
	X("beachtowel04",	MI_BEACHTOWEL04) \
	X("blimp_night",	MI_BLIMP_NIGHT) \
	X("blimp_day",		MI_BLIMP_DAY) \
	X("yt_main_body",	MI_YT_MAIN_BODY) \
	X("yt_main_body2",	MI_YT_MAIN_BODY2) \
	X("oddjgaragdoor", MI_LCS_GARAGEDOOR01) \
	X("bombdoor", MI_LCS_GARAGEDOOR02) \
	X("door_bombshop", MI_LCS_GARAGEDOOR03) \
	X("vheistlocdoor", MI_LCS_GARAGEDOOR04) \
	X("door2_garage", MI_LCS_GARAGEDOOR05) \
	X("ind_slidedoor", MI_LCS_GARAGEDOOR06) \
	X("bankjobdoor", MI_LCS_GARAGEDOOR07) \
	X("door_jmsgrage", MI_LCS_GARAGEDOOR08) \
	X("ind_safeh_gdoor", MI_LCS_GARAGEDOOR09) \
	X("door_sfehousegrge", MI_LCS_GARAGEDOOR10) \
	X("shedgaragedoor", MI_LCS_GARAGEDOOR11) \
	X("door4_garage", MI_LCS_GARAGEDOOR12) \
	X("door_col_compnd_01", MI_LCS_GARAGEDOOR13) \
	X("door_col_compnd_02", MI_LCS_GARAGEDOOR14) \
	X("door_col_compnd_03", MI_LCS_GARAGEDOOR15) \
	X("door_col_compnd_04", MI_LCS_GARAGEDOOR16) \
	X("door_col_compnd_05", MI_LCS_GARAGEDOOR17) \
	X("impex_door", MI_LCS_GARAGEDOOR18) \
	X("SalvGarage", MI_LCS_GARAGEDOOR19) \
	X("door3_garage", MI_LCS_GARAGEDOOR20) \
	X("leveldoor2", MI_LCS_GARAGEDOOR21) \
	X("double_garage_dr", MI_LCS_GARAGEDOOR22) \
	X("amcogaragedoor", MI_LCS_GARAGEDOOR23) \
	X("towergaragedoor1", MI_LCS_GARAGEDOOR24) \
	X("towergaragedoor2", MI_LCS_GARAGEDOOR25) \
	X("towergaragedoor3", MI_LCS_GARAGEDOOR26) \
	X("plysve_gragedoor", MI_LCS_GARAGEDOOR27) \
	X("impexpsubgrgdoor", MI_LCS_GARAGEDOOR28) \
	X("Sub_sprayshopdoor", MI_LCS_GARAGEDOOR29) \
	X("ind_plyrwoor", MI_LCS_GARAGEDOOR30) \
	X("8ballsuburbandoor", MI_LCS_GARAGEDOOR31) \
	X("door_nthgrage", MI_LCS_GARAGEDOOR32) \
	X("hangardoor1", MI_LCS_GARAGEDOOR33) \
	X("hangardoor2", MI_LCS_GARAGEDOOR34) \
	X("neds_door", MI_LCS_GARAGEDOOR35) \
	X("fs_wrhsedoor", MI_LCS_GARAGEDOOR36) \
	X("jm_ContraGarage", MI_LCS_GARAGEDOOR37) \
	X("jm_imp_SalvGarage", MI_LCS_GARAGEDOOR38) \
	X("crushercrush", MI_LCS_GARAGEDOOR39) \
	X("crushertop", MI_LCS_GARAGEDOOR40) \
	X("crusher_crane", MI_LCS_CRANE01) \

// NB: MI_LCS_ <- temporary stuff so that garages started somewhat working

#define X(name, var) extern int16 var;
	MODELINDICES
#undef X

// and some hardcoded ones
// expand as needed
enum
{
	MI_PLAYER = 0,
	MI_COP,
	MI_SWAT,
	MI_FBI,
	MI_ARMY,
	MI_MEDIC,
	MI_FIREMAN,
	MI_MALE01,

	MI_TAXI_D = 9,
	MI_PIMP,
	MI_CRIMINAL01,
	MI_CRIMINAL02,
	MI_MALE02,
	MI_MALE03,
	MI_FATMALE01,
	MI_FATMALE02,
	MI_FEMALE01,
	MI_FEMALE02,
	MI_FEMALE03,
	MI_FATFEMALE01,
	MI_FATFEMALE02,
	MI_PROSTITUTE,
	MI_PROSTITUTE2,
	MI_P_MAN1,
	MI_P_MAN2,
	MI_P_WOM1,
	MI_P_WOM2,
	MI_CT_MAN1,
	MI_CT_MAN2,
	MI_CT_WOM1,
	MI_CT_WOM2,
	MI_LI_MAN1,
	MI_LI_MAN2,
	MI_LI_WOM1,
	MI_LI_WOM2,
	MI_DOCKER1,
	MI_DOCKER2,
	MI_SCUM_MAN,
	MI_SCUM_WOM,
	MI_WORKER1,
	MI_WORKER2,
	MI_B_MAN1,
	MI_B_MAN2,
	MI_B_MAN3,
	MI_B_WOM1,
	MI_B_WOM2,
	MI_B_WOM3,
	MI_MOD_MAN,
	MI_MOD_WOM,
	MI_ST_MAN,
	MI_ST_WOM,
	MI_FAN_MAN1,
	MI_FAN_MAN2,
	MI_FAN_WOM,
	MI_HOS_MAN,
	MI_HOS_WOM,
	MI_CONST1,
	MI_CONST2,
	MI_SHOPPER1,
	MI_SHOPPER2,
	MI_SHOPPER3,
	MI_STUD_MAN,
	MI_STUD_WOM,
	MI_CAS_MAN,
	MI_CAS_WOM,
	MI_CAMP_MAN,
	MI_CAMP_WOM,
	MI_HITMAN,

	MI_GANG01 = 79,
	MI_GANG02,
	MI_GANG03,
	MI_GANG04,
	MI_GANG05,
	MI_GANG06,
	MI_GANG07,
	MI_GANG08,
	MI_GANG09,
	MI_GANG10,
	MI_GANG11,
	MI_GANG12,
	MI_GANG13,
	MI_GANG14,
	MI_GANG15,
	MI_GANG16,
	MI_GANG17,
	MI_GANG18,
	MI_VICE1,
	MI_VICE2,
	MI_VICE3,
	MI_VICE4,
	MI_VICE5,
	MI_VICE6,
	MI_VICE7,
	MI_VICE8,
	MI_WFYG1,
	MI_WFYG2,// = 106,	// last regular ped
	// three more peds possible
	MI_SPECIAL01 = 109,
	MI_SPECIAL02,
	MI_SPECIAL03,
	MI_SPECIAL04,
	MI_SPECIAL05,
	MI_SPECIAL06,
	MI_SPECIAL07,
	MI_SPECIAL08,
	MI_SPECIAL09,
	MI_SPECIAL10,
	MI_SPECIAL11,
	MI_SPECIAL12,
	MI_SPECIAL13,
	MI_SPECIAL14,
	MI_SPECIAL15,
	MI_SPECIAL16,
	MI_SPECIAL17,
	MI_SPECIAL18,
	MI_SPECIAL19,
	MI_SPECIAL20,
	MI_SPECIAL21,// = 129,

	MI_LAST_PED = MI_SPECIAL21,
	MI_FIRST_VEHICLE,

	MI_SPIDER = MI_FIRST_VEHICLE,
	MI_LANDSTAL,
	MI_IDAHO,
	MI_STINGER,
	MI_LINERUN,
	MI_PEREN,
	MI_SENTINEL,
	MI_PATRIOT,
	MI_FIRETRUCK,
	MI_TRASH,
	MI_STRETCH,
	MI_MANANA,
	MI_INFERNUS,
	MI_BLISTA,
	MI_PONY,
	MI_MULE,
	MI_CHEETAH,
	MI_AMBULAN,
	MI_FBICAR,
	MI_MOONBEAM,
	MI_ESPERANT,
	MI_TAXI,
	MI_KURUMA,
	MI_BOBCAT,
	MI_MRWHOOP,
	MI_BFINJECT,
	MI_HEARSE,
	MI_POLICE,
	MI_ENFORCER,
	MI_SECURICA,
	MI_BANSHEE,
	MI_BUS,
	MI_RHINO,
	MI_BARRACKS,
	MI_DODO,
	MI_COACH,
	MI_CABBIE,
	MI_STALLION,
	MI_RUMPO,
	MI_RCBANDIT,
	MI_BELLYUP,
	MI_MRWONGS,
	MI_MAFIA,
	MI_YARDIE,
	MI_YAKUZA,
	MI_DIABLOS,
	MI_COLUMB,
	MI_HOODS,
	MI_PANLANT,
	MI_FLATBED,
	MI_YANKEE,
	MI_BORGNINE,
	MI_TOYZ,
	MI_CAMPVAN,
	MI_BALLOT,
	MI_SHELBY,
	MI_PONTIAC,
	MI_ESPRIT,
	MI_AMMOTRUK,
	MI_HOTROD,
	MI_SINDACCO_CAR,
	MI_FORELLI_CAR,
	MI_FERRY,
	MI_GHOST,
	MI_SPEEDER,
	MI_REEFER,
	MI_PREDATOR,
	MI_TRAIN,
	MI_ESCAPE,
	MI_CHOPPER,
	MI_AIRTRAIN,
	MI_DEADDODO,
	MI_ANGEL,
	MI_PIZZABOY,
	MI_NOODLEBOY,
	MI_PCJ600,
	MI_FAGGIO,
	MI_FREEWAY,
	MI_ANGEL2,
	MI_SANCHEZ2,
	MI_SANCHEZ,
	MI_RCGOBLIN,
	MI_RCRAIDER,
	MI_HUNTER,
	MI_MAVERICK,
	MI_POLMAV,
	MI_VCNMAV,

	MI_LAST_VEHICLE = MI_VCNMAV,

	// HACK HACK, hopefully temporary
	MI_SEASPAR = -1000,
	MI_SPARROW,
	MI_RCBARON,
	MI_TOPFUN,
	MI_CADDY,
	MI_BAGGAGE,
	MI_FBIRANCH,
	MI_VICECHEE,
	MI_RIO,
	MI_SQUALO,
	MI_JETMAX,
	MI_COASTG,
	MI_DINGHY,
	MI_MARQUIS,
	MI_SKIMMER,
	MI_TROPIC,
	MI_SANDKING,
	MI_VOODOO,
	MI_CUBAN,
	MI_PHEONIX,
	MI_COMET,
	MI_SABRE,
	MI_VIRGO,
	MI_RANCHER,
	MI_BLISTAC,
	MI_WASHING,
	MI_ADMIRAL,
	MI_SABRETUR,
	MI_DELUXO,
	MI_HOTRING,
	MI_REGINA,
	MI_SENTXS,
	MI_GLENDALE,
	MI_OCEANIC,
	MI_HERMES,
	MI_GREENWOO,
	MI_LOVEFIST,
	MI_GANGBUR,
	MI_BURRITO,
	MI_SPAND,
	MI_PACKER,
	MI_WALTON,
	MI_ROMERO,

	MI_WHEEL_RIM = 237,
	MI_WHEEL_OFFROAD,
	MI_WHEEL_TRUCK,

	MI_CAR_DOOR,// = 240,
	MI_CAR_BUMPER,
	MI_CAR_PANEL,
	MI_CAR_BONNET,
	MI_CAR_BOOT,
	MI_CAR_WHEEL,
	MI_BODYPARTA,
	MI_BODYPARTB,

	MI_WHEEL_SPORT = 250,
	MI_WHEEL_SALOON,
	MI_WHEEL_LIGHTVAN,
	MI_WHEEL_CLASSIC,
	MI_WHEEL_ALLOY,
	MI_WHEEL_LIGHTTRUCK,
	MI_WHEEL_SMALLCAR,

	MI_AIRTRAIN_VLO, // = 257,
	MI_MOBILE,

	MI_BRASS_KNUCKLES, // 259
	MI_SCREWDRIVER,
	MI_GOLFCLUB,
	MI_NIGHTSTICK,
	MI_KNIFE,
	MI_BASEBALL_BAT,
	MI_HAMMER,
	MI_MEAT_CLEAVER,
	MI_MACHETE,
	MI_KATANA,
	MI_CHAINSAW,
	MI_GRENADE,
	MI_TEARGAS,
	MI_MOLOTOV,
	MI_MISSILE,
	MI_COLT45,
	MI_PYTHON,
	MI_RUGER,
	MI_SHOTGUN,
	MI_SPAS12_SHOTGUN,
	MI_STUBBY_SHOTGUN,
	MI_M4,
	MI_TEC9,
	MI_UZI,
	MI_SILENCEDINGRAM,
	MI_MP5,
	MI_SNIPERRIFLE,
	MI_LASERSCOPE,
	MI_ROCKETLAUNCHER,
	MI_FLAMETHROWER,
	MI_M60,
	MI_MINIGUN,
	MI_BOMB,
	MI_CAMERA,
	MI_FINGERS,
	MI_MINIGUN2,

	MI_CUTOBJ01 = 120,
	MI_CUTOBJ02,
	MI_CUTOBJ03,
	MI_CUTOBJ04,
	MI_CUTOBJ05,
	MI_CUTOBJ06,
	MI_CUTOBJ07,
	MI_CUTOBJ08,
	MI_CUTOBJ09,
	MI_CUTOBJ10,

	NUM_DEFAULT_MODELS = 300
};

enum{
	NUM_OF_SPECIAL_CHARS = 21,
	NUM_OF_CUTSCENE_OBJECTS = 5
};

void InitModelIndices(void);
void MatchModelString(const char *name, int16 id);
void TestModelIndices(void);

inline bool
IsGlass(int16 id)
{
	CSimpleModelInfo *mi = (CSimpleModelInfo*)CModelInfo::GetModelInfo(id);
	return mi->IsBuilding() && (mi->m_isCodeGlass || mi->m_isArtistGlass);
}

inline bool
IsTrafficLight(int16 id)
{
	return id == MI_TRAFFICLIGHTS ||
		id == MI_TRAFFICLIGHTS_VERTICAL ||
		id == MI_TRAFFICLIGHTS_MIAMI ||
		id == MI_TRAFFICLIGHTS_TWOVERTICAL;
}

inline bool
IsLightWithoutShift(int16 id)
{
	return id == MI_TRAFFICLIGHTS ||
		id == MI_SINGLESTREETLIGHTS1 ||
		id == MI_SINGLESTREETLIGHTS2 ||
		id == MI_SINGLESTREETLIGHTS3 ||
		id == MI_DOUBLESTREETLIGHTS;
}

inline bool
IsLightWithPreRenderEffects(int16 id)
{
	return IsTrafficLight(id) ||
		id == MI_SINGLESTREETLIGHTS1 ||
		id == MI_SINGLESTREETLIGHTS2 ||
		id == MI_SINGLESTREETLIGHTS3 ||
		id == MI_DOUBLESTREETLIGHTS;
}

inline bool
IsLightThatNeedsRepositioning(int16 id)
{
	return id == MI_SINGLESTREETLIGHTS1 ||
		id == MI_SINGLESTREETLIGHTS2 ||
		id == MI_SINGLESTREETLIGHTS3 ||
		id == MI_TRAFFICLIGHTS_MIAMI ||
		id == MI_TRAFFICLIGHTS_TWOVERTICAL ||
		id == MI_MLAMPPOST ||
		id == MI_STREETLAMP1 ||
		id == MI_STREETLAMP2;
}

inline bool
IsLightObject(int16 id)
{
	return id == MI_TRAFFICLIGHTS_MIAMI ||
		id == MI_MLAMPPOST ||
		id == MI_SINGLESTREETLIGHTS1 ||
		id == MI_SINGLESTREETLIGHTS2 ||
		id == MI_SINGLESTREETLIGHTS3 ||
		id == MI_DOUBLESTREETLIGHTS ||
		id == MI_TRAFFICLIGHTS_TWOVERTICAL;
}

inline bool
IsLampPost(int16 id)
{
	return id == MI_SINGLESTREETLIGHTS1 ||
		id == MI_SINGLESTREETLIGHTS2 ||
		id == MI_SINGLESTREETLIGHTS3 ||
		id == MI_BOLLARDLIGHT ||
		id == MI_MLAMPPOST ||
		id == MI_STREETLAMP1 ||
		id == MI_STREETLAMP2 ||
		id == MI_TELPOLE02 ||
		id == MI_TRAFFICLIGHTS_MIAMI ||
		id == MI_TRAFFICLIGHTS_TWOVERTICAL;
}

inline bool
IsBodyPart(int16 id)
{
	return id == MI_BODYPARTA || id == MI_BODYPARTB;
}

inline bool
IsPedModel(int16 id)
{
	return id >= MI_PLAYER && id <= MI_LAST_PED;
}
inline bool
IsPalmTreeModel(int16 id)
{
	return	id == MI_VEG_PALM01 ||
		id == MI_VEG_PALM02 ||
		id == MI_VEG_PALM03 ||
		id == MI_VEG_PALM04 ||
		id == MI_VEG_PALM05 ||
		id == MI_VEG_PALM06 ||
		id == MI_VEG_PALM07 ||
		id == MI_VEG_PALM08;
}

inline bool
IsTreeModel(int16 id)
{
	return	id == MI_TREE2 ||
		id == MI_TREE3 ||
		id == MI_TREE6 ||
		id == MI_TREE8 ||
		IsPalmTreeModel(id);
}

inline bool
IsPolicePedModel(int16 id)
{
	return id == MI_COP ||
		id == MI_SWAT ||
		id == MI_FBI ||
		id == MI_ARMY;
}

inline bool
IsPoliceVehicleModel(int16 id)
{
	return id == MI_CHOPPER ||
		id == MI_PREDATOR ||
		id == MI_POLICE ||
		id == MI_ENFORCER;
}

inline bool
IsExplosiveThingModel(int16 id)
{
	return id == MI_EXPLODINGBARREL ||
		id == MI_PETROLPUMP ||
		id == MI_PETROLPUMP2;
}

inline bool 
IsFence(int16 id)
{
	return id == MI_FENCE ||
		id == MI_FENCE2;
}
