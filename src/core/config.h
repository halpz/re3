#pragma once

enum Config {
	NUMCDIMAGES = 12,	// gta3.img duplicates (not used on PC)
	MAX_CDIMAGES = 8,	// additional cdimages
	MAX_CDCHANNELS = 5,

	MODELINFOSIZE = 5500,
	TXDSTORESIZE = 850,
	EXTRADIRSIZE = 128,

	SIMPLEMODELSIZE = 5000,
	TIMEMODELSIZE = 30,
	CLUMPMODELSIZE = 5,
	PEDMODELSIZE = 90,
	VEHICLEMODELSIZE = 120,
	TWODFXSIZE = 2000,

	MAXVEHICLESLOADED = 50,	// 70 on mobile

	NUMOBJECTINFO = 168, // object.dat

	// Pool sizes
	NUMPTRNODES = 30000,  // 26000 on PS2
	NUMENTRYINFOS = 5400, // 3200 on PS2
	NUMPEDS = 140,		  // 90 on PS2
	NUMVEHICLES = 110,	// 70 on PS2
	NUMBUILDINGS = 5500,  // 4915 on PS2
	NUMTREADABLES = 1214,
	NUMOBJECTS = 450,
	NUMDUMMIES = 2802, // 2368 on PS2
	NUMAUDIOSCRIPTOBJECTS = 256,

	NUMTEMPOBJECTS = 30,

	// Link list lengths
	// TODO: alpha list
	NUMCOLCACHELINKS = 200,
	NUMREFERENCES = 800,

	// Zones
	NUMAUDIOZONES = 36,
	NUMZONES = 50,
	NUMMAPZONES = 25,

	// Cull zones
	NUMCULLZONES = 512,
	NUMATTRIBZONES = 288,
	NUMZONEINDICES = 55000,

	NUMHANDLINGS = 57,

	PATHNODESIZE = 4500,

	NUMWEATHERS = 4,
	NUMHOURS = 24,

	NUMEXTRADIRECTIONALS = 4,
	NUMANTENNAS = 8,
	NUMCORONAS = 56,
	NUMPOINTLIGHTS = 32,

	NUMONSCREENTIMERENTRIES = 1,
	NUMRADARBLIPS = 32,
	NUMPICKUPS = 336,
	NUMEVENTS = 64,

	NUM_CARGENS = 160
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
#	define RANDOMSPLASH
#elif defined GTA_PC
#	define GTA3_1_1_PATCH
#	ifdef GTA_PS2_STUFF
//#		define USE_PS2_RAND	// this is unsafe until we have the game reversed
#		define RANDOMSPLASH	// use random splash as on PS2
#		define PS2_MATFX
#	endif
#elif defined GTA_XBOX
#endif

#ifdef MASTER
	// only in master builds
#else
	// not in master builds
#endif

#ifdef FINAL
	// in all games
#	define USE_MY_DOCUMENTS	// use my documents directory for user files
#else
	// not in any game
#	define NASTY_GAME	// nasty game for all languages
#	define NO_MOVIES	// disable intro videos
#	define CHATTYSPLASH	// print what the game is loading
#endif

#define FIX_BUGS		// fix bugs in the game, TODO: use this more
#define KANGAROO_CHEAT
#define ASPECT_RATIO_SCALE
#define USE_DEBUG_SCRIPT_LOADER
#define EXPLODING_AIRTRAIN	// can blow up jumbo jet with rocket launcher
