#include "common.h"
#include "patcher.h"
#include "Quaternion.h"

// TODO: move more stuff into here

void
CQuaternion::Slerp(const CQuaternion &q1, const CQuaternion &q2, float theta, float invSin, float t)
{
	if(theta == 0.0f)
		*this = q2;
	else{
		float w1, w2;
		if(theta > PI/2){
			theta = PI - theta;
			w1 = Sin((1.0f - t) * theta) * invSin;
			w2 = -sin(t * theta) * invSin;
		}else{
			w1 = Sin((1.0f - t) * theta) * invSin;
			w2 = Sin(t * theta) * invSin;
		}
		*this = w1*q1 + w2*q2;
	}
}

void
CQuaternion::Get(RwMatrix *matrix)
{
	float x2 = x+x;
	float y2 = y+y;
	float z2 = z+z;

	float x_2x = x * x2;
	float x_2y = x * y2;
	float x_2z = x * z2;
	float y_2y = y * y2;
	float y_2z = y * z2;
	float z_2z = z * z2;
	float w_2x = w * x2;
	float w_2y = w * y2;
	float w_2z = w * z2;

	matrix->right.x = 1.0f - (y_2y + z_2z);
	matrix->up.x = x_2y - w_2z;
	matrix->at.x = x_2z + w_2y;
	matrix->right.y = x_2y + w_2z;
	matrix->up.y = 1.0f - (x_2x + z_2z);
	matrix->at.y = y_2z - w_2x;
	matrix->right.z = x_2z - w_2y;
	matrix->up.z = y_2z + w_2x;
	matrix->at.z = 1.0f - (x_2x + y_2y);
}

STARTPATCHES
	InjectHook(0x4BA1C0, &CQuaternion::Slerp, PATCH_JUMP);
	InjectHook(0x4BA0D0, &CQuaternion::Get, PATCH_JUMP);
ENDPATCHES
