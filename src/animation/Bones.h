#pragma once

enum BoneTag
{
	BONE_root = 0,
	BONE_pelvis = 1,
	BONE_spine = 2,
	BONE_spine1 = 3,
	BONE_neck = 4,
	BONE_head = 5,
	BONE_l_clavicle = 31,
	BONE_l_upperarm = 32,
	BONE_l_forearm = 33,
	BONE_l_hand = 34,
	BONE_l_finger = 35,
	BONE_r_clavicle = 21,
	BONE_r_upperarm = 22,
	BONE_r_forearm = 23,
	BONE_r_hand = 24,
	BONE_r_finger = 25,
	BONE_l_thigh = 41,
	BONE_l_calf = 42,
	BONE_l_foot = 43,
	BONE_r_thigh = 51,
	BONE_r_calf = 52,
	BONE_r_foot = 53,
};

int ConvertPedNode2BoneTag(int node);
const char *ConvertBoneTag2BoneName(int tag);
