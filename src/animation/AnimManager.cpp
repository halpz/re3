#include "common.h"

#include "General.h"
#include "RwHelper.h"
#include "ModelInfo.h"
#include "ModelIndices.h"
#include "FileMgr.h"
#include "RpAnimBlend.h"
#include "AnimBlendClumpData.h"
#include "AnimBlendAssociation.h"
#include "AnimBlendAssocGroup.h"
#include "AnimManager.h"

CAnimBlock CAnimManager::ms_aAnimBlocks[NUMANIMBLOCKS];
CAnimBlendHierarchy CAnimManager::ms_aAnimations[NUMANIMATIONS];
int32 CAnimManager::ms_numAnimBlocks;
int32 CAnimManager::ms_numAnimations;
CAnimBlendAssocGroup *CAnimManager::ms_aAnimAssocGroups;
CLinkList<CAnimBlendHierarchy*> CAnimManager::ms_animCache;

AnimAssocDesc aStdAnimDescs[] = {
	{ ANIM_WALK, ASSOC_REPEAT | ASSOC_MOVEMENT | ASSOC_HAS_TRANSLATION | ASSOC_WALK },
	{ ANIM_RUN, ASSOC_REPEAT | ASSOC_MOVEMENT | ASSOC_HAS_TRANSLATION | ASSOC_WALK },
	{ ANIM_SPRINT, ASSOC_REPEAT | ASSOC_MOVEMENT | ASSOC_HAS_TRANSLATION | ASSOC_WALK },
	{ ANIM_IDLE_STANCE, ASSOC_REPEAT },
	{ ANIM_WALK_START, ASSOC_HAS_TRANSLATION },
	{ ANIM_RUN_STOP, ASSOC_DELETEFADEDOUT | ASSOC_HAS_TRANSLATION },
	{ ANIM_RUN_STOP_R, ASSOC_DELETEFADEDOUT | ASSOC_HAS_TRANSLATION },
	{ ANIM_IDLE_CAM, ASSOC_REPEAT | ASSOC_PARTIAL },
	{ ANIM_IDLE_HBHB, ASSOC_REPEAT | ASSOC_PARTIAL },
	{ ANIM_IDLE_TIRED, ASSOC_REPEAT },
	{ ANIM_IDLE_ARMED, ASSOC_REPEAT | ASSOC_PARTIAL },
	{ ANIM_IDLE_CHAT, ASSOC_REPEAT | ASSOC_PARTIAL },
	{ ANIM_IDLE_TAXI, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_KO_SHOT_FRONT1, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION | ASSOC_FRONTAL  },
	{ ANIM_KO_SHOT_FRONT2, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION | ASSOC_FRONTAL  },
	{ ANIM_KO_SHOT_FRONT3, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION | ASSOC_FRONTAL  },
	{ ANIM_KO_SHOT_FRONT4, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION | ASSOC_FRONTAL  },
	{ ANIM_KO_SHOT_FACE, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION | ASSOC_FRONTAL  },
	{ ANIM_KO_SHOT_STOM, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_KO_SHOT_ARML, ASSOC_PARTIAL | ASSOC_FRONTAL  },
	{ ANIM_KO_SHOT_ARMR, ASSOC_PARTIAL | ASSOC_FRONTAL  },
	{ ANIM_KO_SHOT_LEGL, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_KO_SHOT_LEGR, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_KD_LEFT, ASSOC_PARTIAL | ASSOC_FRONTAL  },
	{ ANIM_KD_RIGHT, ASSOC_PARTIAL | ASSOC_FRONTAL  },
	{ ANIM_KO_SKID_FRONT, ASSOC_PARTIAL },
	{ ANIM_KO_SPIN_R, ASSOC_PARTIAL },
	{ ANIM_KO_SKID_BACK, ASSOC_PARTIAL | ASSOC_FRONTAL  },
	{ ANIM_KO_SPIN_L, ASSOC_PARTIAL },
	{ ANIM_SHOT_FRONT_PARTIAL, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_SHOT_LEFT_PARTIAL, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_SHOT_BACK_PARTIAL, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_SHOT_RIGHT_PARTIAL, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_HIT_FRONT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_HIT_LEFT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_HIT_BACK, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_HIT_RIGHT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FLOOR_HIT, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_HIT_BODYBLOW, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_HIT_CHEST, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_HIT_HEAD, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_HIT_WALK, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_HIT_WALL, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_FLOOR_HIT_F, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL | ASSOC_FRONTAL  },
	{ ANIM_HIT_BEHIND, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_PUNCH_R, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_KICK_FLOOR, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_BAT_H, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_BAT_V, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_HGUN_BODY, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_WEAPON_AK_BODY, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_PUMP, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_SNIPER, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_THROW, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_THROWU, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_WEAPON_START_THROW, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_BOMBER, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_HGUN_RELOAD, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_AK_RELOAD, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_FPS_PUNCH, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FPS_BAT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FPS_UZI, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FPS_PUMP, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FPS_AK, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FPS_M16, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FPS_ROCKET, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_IDLE, ASSOC_REPEAT },
	{ ANIM_FIGHT2_IDLE, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_SH_F, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_FIGHT_BODYBLOW, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_HEAD, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_KICK, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_KNEE, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_LHOOK, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_PUNCH, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_FIGHT_ROUNDHOUSE, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_FIGHT_LONGKICK, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_FIGHT_PPUNCH, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_CAR_JACKED_RHS, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_CAR_LJACKED_RHS, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_CAR_JACKED_LHS, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_CAR_LJACKED_LHS, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_CAR_QJACK, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_QJACKED, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_CAR_ALIGN_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_ALIGNHI_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_OPEN_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_DOORLOCKED_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_PULLOUT_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_PULLOUT_LOW_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_GETIN_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_GETIN_LOW_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CLOSEDOOR_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CLOSEDOOR_LOW_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_ROLLDOOR, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_ROLLDOOR_LOW, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_GETOUT_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_GETOUT_LOW_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CLOSE_LHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_ALIGN_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_ALIGNHI_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_OPEN_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_DOORLOCKED_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_PULLOUT_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_PULLOUT_LOW_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_GETIN_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_GETIN_LOW_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CLOSEDOOR_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CLOSEDOOR_LOW_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_SHUFFLE_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_LSHUFFLE_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_SIT, ASSOC_DELETEFADEDOUT },
	{ ANIM_CAR_LSIT, ASSOC_DELETEFADEDOUT },
	{ ANIM_CAR_SITP, ASSOC_DELETEFADEDOUT },
	{ ANIM_CAR_SITPLO, ASSOC_DELETEFADEDOUT },
	{ ANIM_DRIVE_L, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_DRIVE_R, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_DRIVE_LOW_L, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_DRIVE_LOW_R, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_DRIVEBY_L, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_DRIVEBY_R, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_CAR_LB, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_DRIVE_BOAT, ASSOC_DELETEFADEDOUT },
	{ ANIM_CAR_GETOUT_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_GETOUT_LOW_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CLOSE_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_HOOKERTALK, ASSOC_REPEAT | ASSOC_PARTIAL },
	{ ANIM_COACH_OPEN_L, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_COACH_OPEN_R, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_COACH_IN_L, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_COACH_IN_R, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_COACH_OUT_L, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_TRAIN_GETIN, ASSOC_PARTIAL },
	{ ANIM_TRAIN_GETOUT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CRAWLOUT_RHS, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_CAR_CRAWLOUT_RHS2, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_OPEN_L, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_GETIN_L, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_CLOSE_L, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_GETOUT_L, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_OPEN, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_GETIN, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_CLOSE, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_VAN_GETOUT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_GETUP1, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_GETUP2, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_GETUP3, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_GETUP_FRONT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_JUMP_LAUNCH, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_JUMP_GLIDE, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_JUMP_LAND, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_FALL_FALL, ASSOC_REPEAT | ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_FALL_GLIDE, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_FALL_LAND, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_FALL_COLLAPSE, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_EV_STEP, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_EV_DIVE, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION | ASSOC_FRONTAL  },
	{ ANIM_XPRESS_SCRATCH, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_IDLE  },
	{ ANIM_ROAD_CROSS, ASSOC_REPEAT | ASSOC_PARTIAL },
	{ ANIM_TURN_180, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_ARREST_GUN, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_DROWN, ASSOC_PARTIAL },
	{ ANIM_CPR, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_DUCK_DOWN, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_DUCK_LOW, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_RBLOCK_CSHOOT, ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
	{ ANIM_WEAPON_THROWU2, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_HANDSUP, ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_HANDSCOWER, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_HAS_TRANSLATION },
	{ ANIM_FUCKU, ASSOC_DELETEFADEDOUT | ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL | ASSOC_NOWALK  },
	{ ANIM_PHONE_IN, ASSOC_PARTIAL },
	{ ANIM_PHONE_OUT, ASSOC_FADEOUTWHENDONE | ASSOC_PARTIAL },
	{ ANIM_PHONE_TALK, ASSOC_REPEAT | ASSOC_DELETEFADEDOUT | ASSOC_PARTIAL },
};
AnimAssocDesc aStdAnimDescsSide[] = {
	{ ANIM_WALK, ASSOC_REPEAT | ASSOC_MOVEMENT | ASSOC_HAS_TRANSLATION | ASSOC_WALK | ASSOC_HAS_X_TRANSLATION },
	{ ANIM_RUN, ASSOC_REPEAT | ASSOC_MOVEMENT | ASSOC_HAS_TRANSLATION | ASSOC_WALK | ASSOC_HAS_X_TRANSLATION },
	{ ANIM_SPRINT, ASSOC_REPEAT | ASSOC_MOVEMENT | ASSOC_HAS_TRANSLATION | ASSOC_WALK | ASSOC_HAS_X_TRANSLATION },
	{ ANIM_IDLE_STANCE, ASSOC_REPEAT },
	{ ANIM_WALK_START, ASSOC_HAS_TRANSLATION | ASSOC_HAS_X_TRANSLATION },
};
char const *aStdAnimations[] = {
	"walk_civi",
	"run_civi",
	"sprint_panic",
	"idle_stance",
	"walk_start",
	"run_stop",
	"run_stopR",
	"idle_cam",
	"idle_hbhb",
	"idle_tired",
	"idle_armed",
	"idle_chat",
	"idle_taxi",
	"KO_shot_front",
	"KO_shot_front",
	"KO_shot_front",
	"KO_shot_front",
	"KO_shot_face",
	"KO_shot_stom",
	"KO_shot_arml",
	"KO_shot_armR",
	"KO_shot_legl",
	"KO_shot_legR",
	"KD_left",
	"KD_right",
	"KO_skid_front",
	"KO_spin_R",
	"KO_skid_back",
	"KO_spin_L",
	"SHOT_partial",
	"SHOT_leftP",
	"SHOT_partial",
	"SHOT_rightP",
	"HIT_front",
	"HIT_L",
	"HIT_back",
	"HIT_R",
	"FLOOR_hit",
	"HIT_bodyblow",
	"HIT_chest",
	"HIT_head",
	"HIT_walk",
	"HIT_wall",
	"FLOOR_hit_f",
	"HIT_behind",
	"punchR",
	"KICK_floor",
	"WEAPON_bat_h",
	"WEAPON_bat_v",
	"WEAPON_hgun_body",
	"WEAPON_AK_body",
	"WEAPON_pump",
	"WEAPON_sniper",
	"WEAPON_throw",
	"WEAPON_throwu",
	"WEAPON_start_throw",
	"bomber",
	"WEAPON_hgun_rload",
	"WEAPON_AK_rload",
	"FPS_PUNCH",
	"FPS_BAT",
	"FPS_UZI",
	"FPS_PUMP",
	"FPS_AK",
	"FPS_M16",
	"FPS_ROCKET",
	"FIGHTIDLE",
	"FIGHT2IDLE",
	"FIGHTsh_F",
	"FIGHTbodyblow",
	"FIGHThead",
	"FIGHTkick",
	"FIGHTknee",
	"FIGHTLhook",
	"FIGHTpunch",
	"FIGHTrndhse",
	"FIGHTlngkck",
	"FIGHTppunch",
	"car_jackedRHS",
	"car_LjackedRHS",
	"car_jackedLHS",
	"car_LjackedLHS",
	"CAR_Qjack",
	"CAR_Qjacked",
	"CAR_align_LHS",
	"CAR_alignHI_LHS",
	"CAR_open_LHS",
	"CAR_doorlocked_LHS",
	"CAR_pullout_LHS",
	"CAR_pulloutL_LHS",
	"CAR_getin_LHS",
	"CAR_getinL_LHS",
	"CAR_closedoor_LHS",
	"CAR_closedoorL_LHS",
	"CAR_rolldoor",
	"CAR_rolldoorLO",
	"CAR_getout_LHS",
	"CAR_getoutL_LHS",
	"CAR_close_LHS",
	"CAR_align_RHS",
	"CAR_alignHI_RHS",
	"CAR_open_RHS",
	"CAR_doorlocked_RHS",
	"CAR_pullout_RHS",
	"CAR_pulloutL_RHS",
	"CAR_getin_RHS",
	"CAR_getinL_RHS",
	"CAR_closedoor_RHS",
	"CAR_closedoorL_RHS",
	"CAR_shuffle_RHS",
	"CAR_Lshuffle_RHS",
	"CAR_sit",
	"CAR_Lsit",
	"CAR_sitp",
	"CAR_sitpLO",
	"DRIVE_L",
	"Drive_R",
	"Drive_LO_l",
	"Drive_LO_R",
	"Driveby_L",
	"Driveby_R",
	"CAR_LB",
	"DRIVE_BOAT",
	"CAR_getout_RHS",
	"CAR_getoutL_RHS",
	"CAR_close_RHS",
	"car_hookertalk",
	"COACH_opnL",
	"COACH_opnR",
	"COACH_inL",
	"COACH_inR",
	"COACH_outL",
	"TRAIN_getin",
	"TRAIN_getout",
	"CAR_crawloutRHS",
	"CAR_crawloutRHS",
	"VAN_openL",
	"VAN_getinL",
	"VAN_closeL",
	"VAN_getoutL",
	"VAN_open",
	"VAN_getin",
	"VAN_close",
	"VAN_getout",
	"Getup",
	"Getup",
	"Getup",
	"Getup_front",
	"JUMP_launch",
	"JUMP_glide",
	"JUMP_land",
	"FALL_fall",
	"FALL_glide",
	"FALL_land",
	"FALL_collapse",
	"EV_step",
	"EV_dive",
	"XPRESSscratch",
	"roadcross",
	"TURN_180",
	"ARRESTgun",
	"DROWN",
	"CPR",
	"DUCK_down",
	"DUCK_low",
	"RBLOCK_Cshoot",
	"WEAPON_throwu",
	"handsup",
	"handsCOWER",
	"FUCKU",
	"PHONE_in",
	"PHONE_out",
	"PHONE_talk",
};
char const *aPlayerAnimations[] = {
	"walk_player",
	"run_player",
	"SPRINT_civi",
	"IDLE_STANCE",
	"walk_start",
};
char const *aPlayerWithRocketAnimations[] = {
	"walk_rocket",
	"run_rocket",
	"run_rocket",
	"idle_rocket",
	"walk_start_rocket",
};
char const *aPlayer1ArmedAnimations[] = {
	"walk_player",
	"run_1armed",
	"SPRINT_civi",
	"IDLE_STANCE",
	"walk_start",
};
char const *aPlayer2ArmedAnimations[] = {
	"walk_player",
	"run_armed",
	"run_armed",
	"idle_stance",
	"walk_start",
};
char const *aPlayerBBBatAnimations[] = {
	"walk_player",
	"run_player",
	"run_player",
	"IDLE_STANCE",
	"walk_start",
};
char const *aShuffleAnimations[] = {
	"WALK_shuffle",
	"RUN_civi",
	"SPRINT_civi",
	"IDLE_STANCE",
};
char const *aOldAnimations[] = {
	"walk_old",
	"run_civi",
	"sprint_civi",
	"idle_stance",
};
char const *aGang1Animations[] = {
	"walk_gang1",
	"run_gang1",
	"sprint_civi",
	"idle_stance",
};
char const *aGang2Animations[] = {
	"walk_gang2",
	"run_gang1",
	"sprint_civi",
	"idle_stance",
};
char const *aFatAnimations[] = {
	"walk_fat",
	"run_civi",
	"woman_runpanic",
	"idle_stance",
};
char const *aOldFatAnimations[] = {
	"walk_fatold",
	"run_fatold",
	"woman_runpanic",
	"idle_stance",
};
char const *aStdWomanAnimations[] = {
	"woman_walknorm",
	"woman_run",
	"woman_runpanic",
	"woman_idlestance",
};
char const *aWomanShopAnimations[] = {
	"woman_walkshop",
	"woman_run",
	"woman_run",
	"woman_idlestance",
};
char const *aBusyWomanAnimations[] = {
	"woman_walkbusy",
	"woman_run",
	"woman_runpanic",
	"woman_idlestance",
};
char const *aSexyWomanAnimations[] = {
	"woman_walksexy",
	"woman_run",
	"woman_runpanic",
	"woman_idlestance",
};
char const *aOldWomanAnimations[] = {
	"woman_walkold",
	"woman_run",
	"woman_runpanic",
	"woman_idlestance",
};
char const *aFatWomanAnimations[] = {
	"walk_fat",
	"woman_run",
	"woman_runpanic",
	"woman_idlestance",
};
char const *aPanicChunkyAnimations[] = {
	"run_fatold",
	"woman_runpanic",
	"woman_runpanic",
	"idle_stance",
};
char const *aPlayerStrafeBackAnimations[] = {
	"walk_player_back",
	"run_player_back",
	"run_player_back",
	"IDLE_STANCE",
	"walk_start_back",
};
char const *aPlayerStrafeLeftAnimations[] = {
	"walk_player_left",
	"run_left",
	"run_left",
	"IDLE_STANCE",
	"walk_start_left",
};
char const *aPlayerStrafeRightAnimations[] = {
	"walk_player_right",
	"run_right",
	"run_right",
	"IDLE_STANCE",
	"walk_start_right",
};
char const *aRocketStrafeBackAnimations[] = {
	"walk_rocket_back",
	"run_rocket_back",
	"run_rocket_back",
	"idle_rocket",
	"walkst_rocket_back",
};
char const *aRocketStrafeLeftAnimations[] = {
	"walk_rocket_left",
	"run_rocket_left",
	"run_rocket_left",
	"idle_rocket",
	"walkst_rocket_left",
};
char const *aRocketStrafeRightAnimations[] = {
	"walk_rocket_right",
	"run_rocket_right",
	"run_rocket_right",
	"idle_rocket",
	"walkst_rocket_right",
};

#define awc(a) ARRAY_SIZE(a), a
const AnimAssocDefinition CAnimManager::ms_aAnimAssocDefinitions[NUM_ANIM_ASSOC_GROUPS] = {
	{ "man", "ped", MI_COP, awc(aStdAnimations), aStdAnimDescs },
	{ "player", "ped", MI_COP, awc(aPlayerAnimations), aStdAnimDescs },
	{ "playerrocket", "ped", MI_COP, awc(aPlayerWithRocketAnimations), aStdAnimDescs },
	{ "player1armed", "ped", MI_COP, awc(aPlayer1ArmedAnimations), aStdAnimDescs },
	{ "player2armed", "ped", MI_COP, awc(aPlayer2ArmedAnimations), aStdAnimDescs },
	{ "playerBBBat", "ped", MI_COP, awc(aPlayerBBBatAnimations), aStdAnimDescs },
	{ "shuffle", "ped", MI_COP, awc(aShuffleAnimations), aStdAnimDescs },
	{ "oldman", "ped", MI_COP, awc(aOldAnimations), aStdAnimDescs },
	{ "gang1", "ped", MI_COP, awc(aGang1Animations), aStdAnimDescs },
	{ "gang2", "ped", MI_COP, awc(aGang2Animations), aStdAnimDescs },
	{ "fatman", "ped", MI_COP, awc(aFatAnimations), aStdAnimDescs },
	{ "oldfatman", "ped", MI_COP, awc(aOldFatAnimations), aStdAnimDescs },
	{ "woman", "ped", MI_COP, awc(aStdWomanAnimations), aStdAnimDescs },
	{ "shopping", "ped", MI_COP, awc(aWomanShopAnimations), aStdAnimDescs },
	{ "busywoman", "ped", MI_COP, awc(aBusyWomanAnimations), aStdAnimDescs },
	{ "sexywoman", "ped", MI_COP, awc(aSexyWomanAnimations), aStdAnimDescs },
	{ "oldwoman", "ped", MI_COP, awc(aOldWomanAnimations), aStdAnimDescs },
	{ "fatwoman", "ped", MI_COP, awc(aFatWomanAnimations), aStdAnimDescs },
	{ "panicchunky", "ped", MI_COP, awc(aPanicChunkyAnimations), aStdAnimDescs },
	{ "playerback", "ped", MI_COP, awc(aPlayerStrafeBackAnimations), aStdAnimDescs },
	{ "playerleft", "ped", MI_COP, awc(aPlayerStrafeLeftAnimations), aStdAnimDescsSide },
	{ "playerright", "ped", MI_COP, awc(aPlayerStrafeRightAnimations), aStdAnimDescsSide },
	{ "rocketback", "ped", MI_COP, awc(aRocketStrafeBackAnimations), aStdAnimDescs },
	{ "rocketleft", "ped", MI_COP, awc(aRocketStrafeLeftAnimations), aStdAnimDescsSide },
	{ "rocketright", "ped", MI_COP, awc(aRocketStrafeRightAnimations), aStdAnimDescsSide },
};
#undef awc

void
CAnimManager::Initialise(void)
{
	ms_numAnimations = 0;
	ms_numAnimBlocks = 0;
	ms_animCache.Init(25);

//	dumpanimdata();
}

void
CAnimManager::Shutdown(void)
{
	int i;

	ms_animCache.Shutdown();

	for(i = 0; i < ms_numAnimations; i++)
		ms_aAnimations[i].Shutdown();

	delete[] ms_aAnimAssocGroups;
}

void
CAnimManager::UncompressAnimation(CAnimBlendHierarchy *hier)
{
	if(!hier->compressed){
		if(hier->linkPtr){
			hier->linkPtr->Remove();
			ms_animCache.head.Insert(hier->linkPtr);
		}
	}else{
		CLink<CAnimBlendHierarchy*> *link = ms_animCache.Insert(hier);
		if(link == nil){
			ms_animCache.tail.prev->item->RemoveUncompressedData();
			ms_animCache.Remove(ms_animCache.tail.prev);
			link = ms_animCache.Insert(hier);
		}
		hier->linkPtr = link;
		hier->Uncompress();
	}
}

CAnimBlock*
CAnimManager::GetAnimationBlock(const char *name)
{
	int i;

	for(i = 0; i < ms_numAnimBlocks; i++)
		if(strcasecmp(ms_aAnimBlocks[i].name, name) == 0)
			return &ms_aAnimBlocks[i];
	return nil;
}

CAnimBlendHierarchy*
CAnimManager::GetAnimation(const char *name, CAnimBlock *animBlock)
{
	int i;
	CAnimBlendHierarchy *hier = &ms_aAnimations[animBlock->firstIndex];

	for(i = 0; i < animBlock->numAnims; i++){
		if(!CGeneral::faststricmp(hier->name, name))
			return hier;
		hier++;
	}
	return nil;
}

const char*
CAnimManager::GetAnimGroupName(AssocGroupId groupId)
{
	return ms_aAnimAssocDefinitions[groupId].name;
}

CAnimBlendAssociation*
CAnimManager::CreateAnimAssociation(AssocGroupId groupId, AnimationId animId)
{
	return ms_aAnimAssocGroups[groupId].CopyAnimation(animId);
}

CAnimBlendAssociation*
CAnimManager::GetAnimAssociation(AssocGroupId groupId, AnimationId animId)
{
	return ms_aAnimAssocGroups[groupId].GetAnimation(animId);
}

CAnimBlendAssociation*
CAnimManager::GetAnimAssociation(AssocGroupId groupId, const char *name)
{
	return ms_aAnimAssocGroups[groupId].GetAnimation(name);
}

CAnimBlendAssociation*
CAnimManager::AddAnimation(RpClump *clump, AssocGroupId groupId, AnimationId animId)
{
	CAnimBlendAssociation *anim = CreateAnimAssociation(groupId, animId);
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	if(anim->IsMovement()){
		CAnimBlendAssociation *syncanim = nil;
		CAnimBlendLink *link;
		for(link = clumpData->link.next; link; link = link->next){
			syncanim = CAnimBlendAssociation::FromLink(link);
			if(syncanim->IsMovement())
				break;
		}
		if(link){
			anim->SyncAnimation(syncanim);
			anim->flags |= ASSOC_RUNNING;
		}else
			anim->Start(0.0f);
	}else
		anim->Start(0.0f);

	clumpData->link.Prepend(&anim->link);
	return anim;
}

CAnimBlendAssociation*
CAnimManager::AddAnimationAndSync(RpClump *clump, CAnimBlendAssociation *syncanim, AssocGroupId groupId, AnimationId animId)
{
	CAnimBlendAssociation *anim = CreateAnimAssociation(groupId, animId);
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	if (anim->IsMovement() && syncanim){
		anim->SyncAnimation(syncanim);
		anim->flags |= ASSOC_RUNNING;
	}else
		anim->Start(0.0f);

	clumpData->link.Prepend(&anim->link);
	return anim;
}

CAnimBlendAssociation*
CAnimManager::BlendAnimation(RpClump *clump, AssocGroupId groupId, AnimationId animId, float delta)
{
	int removePrevAnim = 0;
	CAnimBlendClumpData *clumpData = *RPANIMBLENDCLUMPDATA(clump);
	CAnimBlendAssociation *anim = GetAnimAssociation(groupId, animId);
	bool isMovement = anim->IsMovement();
	bool isPartial = anim->IsPartial();
	CAnimBlendLink *link;
	CAnimBlendAssociation *found = nil, *movementAnim = nil;
	for(link = clumpData->link.next; link; link = link->next){
		anim = CAnimBlendAssociation::FromLink(link);
		if(isMovement && anim->IsMovement())
			movementAnim = anim;
		if(anim->animId == animId)
			found = anim;
		else{
			if(isPartial == anim->IsPartial()){
				if(anim->blendAmount > 0.0f){
					float blendDelta = -delta*anim->blendAmount;
					if(blendDelta < anim->blendDelta || !isPartial)
						anim->blendDelta = blendDelta;
				}else{
					anim->blendDelta = -1.0f;
				}
				anim->flags |= ASSOC_DELETEFADEDOUT;
				removePrevAnim = 1;
			}
		}
	}
	if(found){
		found->blendDelta = (1.0f - found->blendAmount)*delta;
		if(!found->IsRunning() && found->currentTime == found->hierarchy->totalLength)
			found->Start(0.0f);
	}else{
		found = AddAnimationAndSync(clump, movementAnim, groupId, animId);
		if(!removePrevAnim && !isPartial){
			found->blendAmount = 1.0f;
			return found;
		}
		found->blendAmount = 0.0f;
		found->blendDelta = delta;
	}
	UncompressAnimation(found->hierarchy);
	return found;
}

void
CAnimManager::LoadAnimFiles(void)
{
	int i, j;

	LoadAnimFile("ANIM\\PED.IFP");

	// Create all assoc groups
	ms_aAnimAssocGroups = new CAnimBlendAssocGroup[NUM_ANIM_ASSOC_GROUPS];
	for(i = 0; i < NUM_ANIM_ASSOC_GROUPS; i++){
		CBaseModelInfo *mi = CModelInfo::GetModelInfo(ms_aAnimAssocDefinitions[i].modelIndex);
		RpClump *clump = (RpClump*)mi->CreateInstance();
		RpAnimBlendClumpInit(clump);
		CAnimBlendAssocGroup *group = &ms_aAnimAssocGroups[i];
		const AnimAssocDefinition *def = &ms_aAnimAssocDefinitions[i];
		group->CreateAssociations(def->blockName, clump, def->animNames, def->numAnims);
		for(j = 0; j < group->numAssociations; j++)
			group->GetAnimation(j)->flags |= def->animDescs[j].flags;
#ifdef PED_SKIN
		// forgot on xbox/android
		if(IsClumpSkinned(clump))
			RpClumpForAllAtomics(clump, AtomicRemoveAnimFromSkinCB, nil);
#endif
		RpClumpDestroy(clump);
	}
}

void
CAnimManager::LoadAnimFile(const char *filename)
{
	int fd;
	fd = CFileMgr::OpenFile(filename, "rb");
	assert(fd > 0);
	LoadAnimFile(fd, true);
	CFileMgr::CloseFile(fd);
}

void
CAnimManager::LoadAnimFile(int fd, bool compress)
{
	#define ROUNDSIZE(x) if((x) & 3) (x) += 4 - ((x)&3)
	struct IfpHeader {
		char ident[4];
		uint32 size;
	};
	IfpHeader anpk, info, name, dgan, cpan, anim;
	int numANPK;
	char buf[256];
	int i, j, k, l;
	float *fbuf = (float*)buf;

	CFileMgr::Read(fd, (char*)&anpk, sizeof(IfpHeader));
	if(strncmp(anpk.ident, "ANLF", 4) == 0){
		ROUNDSIZE(anpk.size);
		CFileMgr::Read(fd, buf, anpk.size);
		numANPK = *(int*)buf;
	}else if(strncmp(anpk.ident, "ANPK", 4) == 0){
		CFileMgr::Seek(fd, -8, 1);
		numANPK = 1;
	}

	for(i = 0; i < numANPK; i++){
		// block name
		CFileMgr::Read(fd, (char*)&anpk, sizeof(IfpHeader));
		ROUNDSIZE(anpk.size);
		CFileMgr::Read(fd, (char*)&info, sizeof(IfpHeader));
		ROUNDSIZE(info.size);
		CFileMgr::Read(fd, buf, info.size);
		CAnimBlock *animBlock = &ms_aAnimBlocks[ms_numAnimBlocks++];
		strncpy(animBlock->name, buf+4, 24);
		animBlock->numAnims = *(int*)buf;

		animBlock->firstIndex = ms_numAnimations;

		for(j = 0; j < animBlock->numAnims; j++){
			CAnimBlendHierarchy *hier = &ms_aAnimations[ms_numAnimations++];

			// animation name
			CFileMgr::Read(fd, (char*)&name, sizeof(IfpHeader));
			ROUNDSIZE(name.size);
			CFileMgr::Read(fd, buf, name.size);
			hier->SetName(buf);

			// DG info has number of nodes/sequences
			CFileMgr::Read(fd, (char*)&dgan, sizeof(IfpHeader));
			ROUNDSIZE(dgan.size);
			CFileMgr::Read(fd, (char*)&info, sizeof(IfpHeader));
			ROUNDSIZE(info.size);
			CFileMgr::Read(fd, buf, info.size);
			hier->numSequences = *(int*)buf;
			hier->sequences = new CAnimBlendSequence[hier->numSequences];

			CAnimBlendSequence *seq = hier->sequences;
			for(k = 0; k < hier->numSequences; k++, seq++){
				// Each node has a name and key frames
				CFileMgr::Read(fd, (char*)&cpan, sizeof(IfpHeader));
				ROUNDSIZE(dgan.size);
				CFileMgr::Read(fd, (char*)&anim, sizeof(IfpHeader));
				ROUNDSIZE(anim.size);
				CFileMgr::Read(fd, buf, anim.size);
				int numFrames = *(int*)(buf+28);
#ifdef PED_SKIN
				if(anim.size == 44)
					seq->SetBoneTag(*(int*)(buf+40));
#endif
				seq->SetName(buf);
				if(numFrames == 0)
					continue;

				CFileMgr::Read(fd, (char*)&info, sizeof(info));
				if(strncmp(info.ident, "KR00", 4) == 0){
					seq->SetNumFrames(numFrames, false);
					KeyFrame *kf = seq->GetKeyFrame(0);
					for(l = 0; l < numFrames; l++, kf++){
						CFileMgr::Read(fd, buf, 0x14);
						kf->rotation.x = -fbuf[0];
						kf->rotation.y = -fbuf[1];
						kf->rotation.z = -fbuf[2];
						kf->rotation.w = fbuf[3];
						kf->deltaTime = fbuf[4];	// absolute time here
					}
				}else if(strncmp(info.ident, "KRT0", 4) == 0){
					seq->SetNumFrames(numFrames, true);
					KeyFrameTrans *kf = (KeyFrameTrans*)seq->GetKeyFrame(0);
					for(l = 0; l < numFrames; l++, kf++){
						CFileMgr::Read(fd, buf, 0x20);
						kf->rotation.x = -fbuf[0];
						kf->rotation.y = -fbuf[1];
						kf->rotation.z = -fbuf[2];
						kf->rotation.w = fbuf[3];
						kf->translation.x = fbuf[4];
						kf->translation.y = fbuf[5];
						kf->translation.z = fbuf[6];
						kf->deltaTime = fbuf[7];	// absolute time here
					}
				}else if(strncmp(info.ident, "KRTS", 4) == 0){
					seq->SetNumFrames(numFrames, true);
					KeyFrameTrans *kf = (KeyFrameTrans*)seq->GetKeyFrame(0);
					for(l = 0; l < numFrames; l++, kf++){
						CFileMgr::Read(fd, buf, 0x2C);
						kf->rotation.x = -fbuf[0];
						kf->rotation.y = -fbuf[1];
						kf->rotation.z = -fbuf[2];
						kf->rotation.w = fbuf[3];
						kf->translation.x = fbuf[4];
						kf->translation.y = fbuf[5];
						kf->translation.z = fbuf[6];
						// scaling ignored
						kf->deltaTime = fbuf[10];	// absolute time here
					}
				}

				// convert absolute time to deltas
				for(l = seq->numFrames-1; l > 0; l--){
					KeyFrame *kf1 = seq->GetKeyFrame(l);
					KeyFrame *kf2 = seq->GetKeyFrame(l-1);
					kf1->deltaTime -= kf2->deltaTime;
				}
			}

			hier->RemoveQuaternionFlips();
			if(compress)
				hier->RemoveUncompressedData();
			else
				hier->CalcTotalTime();
		}
	}
}

void
CAnimManager::RemoveLastAnimFile(void)
{
	int i;
	ms_numAnimBlocks--;
	ms_numAnimations = ms_aAnimBlocks[ms_numAnimBlocks].firstIndex;
	for(i = 0; i < ms_aAnimBlocks[ms_numAnimBlocks].numAnims; i++)
		ms_aAnimations[ms_aAnimBlocks[ms_numAnimBlocks].firstIndex + i].RemoveAnimSequences();
}
