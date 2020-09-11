#pragma once

enum Config {
	NUMPLAYERS = 1,

	NUMCDIMAGES = 6, // gta3.img duplicates (not used on PC)
	MAX_CDIMAGES = 8, // additional cdimages
	MAX_CDCHANNELS = 5,

	MODELINFOSIZE = 6500,
	TXDSTORESIZE = 1385,
	COLSTORESIZE = 31,
	EXTRADIRSIZE = 256,
	CUTSCENEDIRSIZE = 512,

	SIMPLEMODELSIZE = 3885,
	TIMEMODELSIZE = 385,
	CLUMPMODELSIZE = 5,
	WEAPONMODELSIZE = 37,
	PEDMODELSIZE = 130,
	VEHICLEMODELSIZE = 110,
	TWODFXSIZE = 1210,

	MAXVEHICLESLOADED = 50, // 70 on mobile

	NUMOBJECTINFO = 400, // TODO(MIAMI): fantasy	// object.dat

	// Pool sizes
	NUMPTRNODES = 50000,
	NUMENTRYINFOS = 3200,
	NUMPEDS = 140,
	NUMVEHICLES = 110,
	NUMBUILDINGS = 7000,
	NUMTREADABLES = 1,
	NUMOBJECTS = 460,
	NUMDUMMIES = 2340,
	NUMAUDIOSCRIPTOBJECTS = 192,
	NUMCOLMODELS = 4400,
	NUMCUTSCENEOBJECTS = 50,	// does not exist in VC

	NUMANIMBLOCKS = 35,
	NUMANIMATIONS = 450,

	NUMTEMPOBJECTS = 40,

	// Path data
	NUM_PATHNODES = 9650,
	NUM_CARPATHLINKS = 3500,
	NUM_MAPOBJECTS = 1250,
	NUM_PATHCONNECTIONS = 20400,

	// Link list lengths
	NUMALPHALIST = 20,
	NUMBOATALPHALIST = 20,
	NUMALPHAENTITYLIST = 200,
	NUMALPHAUNTERWATERENTITYLIST = 30,
	NUMCOLCACHELINKS = 50,
	NUMREFERENCES = 800,

	// Zones
	NUMAUDIOZONES = 14,
	NUMINFOZONES = 169,
	NUMMAPZONES = 39,
	NUMNAVIGZONES = 20,

	// Cull zones
	NUMATTRIBZONES = 704,

	NUMOCCLUSIONVOLUMES = 350,
	NUMACTIVEOCCLUDERS = 48,

	PATHNODESIZE = 4500,

	NUMWEATHERS = 7,
	NUMHOURS = 24,

	NUMEXTRADIRECTIONALS = 4,
	NUMANTENNAS = 8,
	NUMCORONAS = 56,
	NUMPOINTLIGHTS = 32,
	NUM3DMARKERS = 32,
	NUMBRIGHTLIGHTS = 32,
	NUMSHINYTEXTS = 32,
	NUMMONEYMESSAGES = 16,
	NUMPICKUPMESSAGES = 16,
	NUMBULLETTRACES = 16,
	NUMMBLURSTREAKS = 4,
	NUMSKIDMARKS = 32,

	NUMONSCREENTIMERENTRIES = 1,
	NUMRADARBLIPS = 75,
	NUMGENERALPICKUPS = 320,
	NUMSCRIPTEDPICKUPS = 16,
	NUMPICKUPS = NUMGENERALPICKUPS + NUMSCRIPTEDPICKUPS,
	NUMCOLLECTEDPICKUPS = 20,
	NUMPACMANPICKUPS = 256,
	NUMEVENTS = 64,

	NUM_CARGENS = 185,

	NUM_PATH_NODES_IN_AUTOPILOT = 8,

	NUM_ACCIDENTS = 20,
	NUM_FIRES = 40,
	NUM_GARAGES = 32,
	NUM_PROJECTILES = 32,

	NUM_GLASSPANES = 45,
	NUM_GLASSENTITIES = 32,
	NUM_WATERCANNONS = 3,

	NUMPEDROUTES = 200,
	NUMPHONES = 50,
	NUMPEDGROUPS = 67,
	NUMMODELSPERPEDGROUP = 16,
	MAXZONEPEDSLOADED = 8,
	NUMSHOTINFOS = 100,

	NUMROADBLOCKS = 300,
	NUM_SCRIPT_ROADBLOCKS = 16,

	NUMVISIBLEENTITIES = 2000,
	NUMINVISIBLEENTITIES = 150,

	NUM_AUDIOENTITY_EVENTS = 4,
	NUM_PED_COMMENTS_BANKS = 2,
	NUM_PED_COMMENTS_SLOTS = 20,

	NUM_SOUNDS_SAMPLES_BANKS = 2,
	NUM_SOUNDS_SAMPLES_SLOTS = 27,
	NUM_AUDIOENTITIES = 250,

	NUM_AUDIO_REFLECTIONS = 8,
	NUM_SCRIPT_MAX_ENTITIES = 40,

	NUM_GARAGE_STORED_CARS = 4,

	NUM_CRANES = 8,
	NUM_ESCALATORS = 22,

	NUM_EXPLOSIONS = 48,

	NUM_SETPIECES = 96,
	NUM_SHORTCUT_START_POINTS = 16
};

// We'll use this once we're ready to become independent of the game
// Use it to mark bugs in the code that will prevent the game from working then
//#define STANDALONE

// We don't expect to compile for PS2 or Xbox
// but it might be interesting for documentation purposes
#define GTA_PC
//#define GTA_PS2
//#define GTA_XBOX

// This enables things from the PS2 version on PC
#define GTA_PS2_STUFF

// This is enabled for all released games.
// any debug stuff that isn't left in any game is not in FINAL
//#define FINAL

// This is enabled for all released games except mobile
// any debug stuff that is only left in mobile, is not in MASTER
//#define MASTER

#if defined GTA_PS2
#	define GTA_PS2_STUFF
#	define RANDOMSPLASH
#	define VU_COLLISION
#elif defined GTA_PC
#	define GTA3_1_1_PATCH
//#	define GTA3_STEAM_PATCH
//# define GTAVC_JP_PATCH
#	ifdef GTA_PS2_STUFF
#		define USE_PS2_RAND
#		define RANDOMSPLASH	// use random splash as on PS2
#		define PS2_MATFX
#	endif
#elif defined GTA_XBOX
#endif

#ifdef VU_COLLISION
#define COMPRESSED_COL_VECTORS	// current need compressed vectors in this code
#endif

#ifdef MASTER
	// only in master builds
#else
	// not in master builds
	#define VALIDATE_SAVE_SIZE
#endif

#ifdef FINAL
	// in all games
#	define USE_MY_DOCUMENTS	// use my documents directory for user files
#else
	// not in any game
#	define NASTY_GAME	// nasty game for all languages
#	define NO_MOVIES	// disable intro videos
#	define NO_CDCHECK
#	define CHATTYSPLASH	// print what the game is loading
#	define DEBUGMENU
#	define TIMEBARS		// print debug timers
#endif

#define FIX_BUGS		// fixes bugs that we've came across during reversing, TODO: use this more
//#define MORE_LANGUAGES		// Add more translations to the game
#define COMPATIBLE_SAVES // this allows changing structs while keeping saves compatible
#define FIX_HIGH_FPS_BUGS_ON_FRONTEND

// Just debug menu entries
#ifdef DEBUGMENU
#define RELOADABLES			// some debug menu options to reload TXD files
#define MISSION_SWITCHER // from debug menu
#endif

// Rendering/display
#define ASPECT_RATIO_SCALE	// Not just makes everything scale with aspect ratio, also adds support for all aspect ratios
#define DEFAULT_NATIVE_RESOLUTION	// Set default video mode to your native resolution (fixes Windows 10 launch)
#define USE_TXD_CDIMAGE		// generate and load textures from txd.img
#define PS2_ALPHA_TEST		// emulate ps2 alpha test 
#define IMPROVED_VIDEOMODE	// save and load videomode parameters instead of a magic number
//#define DISABLE_LOADING_SCREEN // disable the loading screen which vastly improves the loading time
//#define NO_ISLAND_LOADING  // disable loadscreen between islands via loading all island data at once, consumes more memory and CPU
//#define USE_TEXTURE_POOL
//#define CUTSCENE_BORDERS_SWITCH
//#define EXTENDED_COLOURFILTER		// more options for colour filter (replaces mblur)
//#define EXTENDED_PIPELINES		// custom render pipelines (includes Neo)
//#define MULTISAMPLING		// adds MSAA option TODO

#ifdef LIBRW
// these are not supported with librw yet
#	undef MULTISAMPLING
#endif

// Water & Particle
#define PC_PARTICLE
//#define PS2_ALTERNATIVE_CARSPLASH // unused on PS2
// #define PC_WATER
#define WATER_CHEATS

//#define USE_CUTSCENE_SHADOW_FOR_PED
#define DISABLE_CUTSCENE_SHADOWS

// Pad
#if !defined(RW_GL3) && defined(_WIN32)
#define XINPUT
#endif
#define DETECT_PAD_INPUT_SWITCH // Adds automatic switch of pad related stuff between controller and kb/m
#define KANGAROO_CHEAT
#define ALLCARSHELI_CHEAT
#define ALT_DODO_CHEAT
#define WALLCLIMB_CHEAT
#define REGISTER_START_BUTTON
//#define BIND_VEHICLE_FIREWEAPON // Adds ability to rebind fire key for 'in vehicle' controls

// Hud, frontend and radar
#define HUD_ENHANCEMENTS	// Adjusts some aspects to make the HUD look/behave a little bit better.
#define BETA_SLIDING_TEXT
#define TRIANGULAR_BLIPS	// height indicating triangular radar blips, as in VC
#define PC_MENU

#ifndef PC_MENU
#	define PS2_MENU
//#	define PS2_MENU_USEALLPAGEICONS
//#	define PS2_LIKE_MENU	// An effort to recreate PS2 menu, cycling through tabs, different bg etc.
#else
#	define MAP_ENHANCEMENTS			// Adding waypoint etc.
#	define TRIANGLE_BACK_BUTTON
//#	define CIRCLE_BACK_BUTTON
//#define CUSTOM_FRONTEND_OPTIONS
#	define GRAPHICS_MENU_OPTIONS
#define LEGACY_MENU_OPTIONS
#define MUCH_SHORTER_OUTRO_SCREEN

// Script
#define USE_DEBUG_SCRIPT_LOADER	// Loads main.scm by default. Hold R for main_freeroam.scm and D for main_d.scm
#define USE_MEASUREMENTS_IN_METERS // makes game use meters instead of feet in script
#define USE_PRECISE_MEASUREMENT_CONVERTION // makes game convert feet to meeters more precisely
//#define MISSION_REPLAY // mobile feature
#endif
//#define SIMPLIER_MISSIONS // apply simplifications from mobile
#define USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
#define SCRIPT_LOG_FILE_LEVEL 1 // 0 == no log, 1 == overwrite every frame, 2 == full log

#ifndef USE_ADVANCED_SCRIPT_DEBUG_OUTPUT
#define USE_BASIC_SCRIPT_DEBUG_OUTPUT
#endif

// Replay
//#define DONT_FIX_REPLAY_BUGS // keeps various bugs in CReplay, some of which are fairly cool!
//#define USE_BETA_REPLAY_MODE // adds another replay mode, a few seconds slomo (caution: buggy!)

// Vehicles
#define EXPLODING_AIRTRAIN	// can blow up jumbo jet with rocket launcher
#define CPLANE_ROTORS		// make the rotors of the NPC police heli rotate

// Pickups
//#define MONEY_MESSAGES
#define CAMERA_PICKUP

// Peds
#define PED_SKIN		// support for skinned geometry on peds
#define ANIMATE_PED_COL_MODEL
#define VC_PED_PORTS			// various ports from VC's CPed, mostly subtle
#define CANCELLABLE_CAR_ENTER

// Camera
#define IMPROVED_CAMERA		// Better Debug cam, and maybe more in the future
#define FREE_CAM		// Rotating cam

// Audio
#ifndef AUDIO_OAL // is not working yet for openal
#define AUDIO_CACHE // cache sound lengths to speed up the cold boot
#endif
//#define PS2_AUDIO   // changes audio paths for cutscenes and radio to PS2 paths, needs vbdec to support VB with MSS


//#define SQUEEZE_PERFORMANCE
#ifdef SQUEEZE_PERFORMANCE
	#undef PS2_ALPHA_TEST
	#undef NO_ISLAND_LOADING
	#define PC_PARTICLE
	#define VC_PED_PORTS // To not process collisions always. But should be tested if that's really beneficial
#endif