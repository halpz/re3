#include "common.h"
#include "PedModelInfo.h"
#include "Bones.h"

int
ConvertPedNode2BoneTag(int node)
{
	switch(node){
	case PED_MID:	return BONE_spine1;
	case PED_HEAD:	return BONE_head;
	case PED_UPPERARML:	return BONE_l_upperarm;
	case PED_UPPERARMR:	return BONE_r_upperarm;
	case PED_HANDL:	return BONE_l_hand;
	case PED_HANDR:	return BONE_r_hand;
	case PED_UPPERLEGL:	return BONE_l_thigh;
	case PED_UPPERLEGR:	return BONE_r_thigh;
	case PED_FOOTL:	return BONE_l_foot;
	case PED_FOOTR:	return BONE_r_foot;
	case PED_LOWERLEGR:	return BONE_r_calf;
	case PED_LOWERLEGL:	return BONE_l_calf;
	case PED_FOREARML:	return BONE_l_forearm;
	case PED_FOREARMR:	return BONE_r_forearm;
	case PED_CLAVICLEL:	return BONE_l_clavicle;
	case PED_CLAVICLER:	return BONE_r_clavicle;
	case PED_NECK:	return BONE_neck;
	}
	assert(0 && "this node has no bone");
	return -1;
}

const char*
ConvertBoneTag2BoneName(int tag)
{
	switch(tag){
	case BONE_root:	return "Root";
	case BONE_pelvis:	return "Pelvis";
	case BONE_spine:	return "Spine";
	case BONE_spine1:	return "Spine1";
	case BONE_neck:	return "Neck";
	case BONE_head:	return "Head";
	case BONE_r_clavicle:	return "Bip01 R Clavicle";
	case BONE_r_upperarm:	return "R UpperArm";
	case BONE_r_forearm:	return "R Forearm";
	case BONE_r_hand:	return "R Hand";
	case BONE_r_finger:	return "R Fingers";
	case BONE_l_clavicle:	return "Bip01 L Clavicle";
	case BONE_l_upperarm:	return "L UpperArm";
	case BONE_l_forearm:	return "L Forearm";
	case BONE_l_hand:	return "L Hand";
	case BONE_l_finger:	return "L Fingers";
	case BONE_l_thigh:	return "L Thigh";
	case BONE_l_calf:	return "L Calf";
	case BONE_l_foot:	return "L Foot";
	case BONE_r_thigh:	return "R Thigh";
	case BONE_r_calf:	return "R Calf";
	case BONE_r_foot:	return "R Foot";
	}
	return nil;
}
