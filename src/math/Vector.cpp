#include "common.h"

void
CVector::Normalise(void)
{
	float sq = MagnitudeSqr();
	if (sq > 0.0f) {
		float invsqrt = RecipSqrt(sq);
		x *= invsqrt;
		y *= invsqrt;
		z *= invsqrt;
	} else
		x = 1.0f;
}

CVector
CrossProduct(const CVector &v1, const CVector &v2)
{
	return CVector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

CVector
Multiply3x3(const CMatrix &mat, const CVector &vec)
{
	// TODO: VU0 code
	return CVector(mat.right.x * vec.x + mat.forward.x * vec.y + mat.up.x * vec.z,
	               mat.right.y * vec.x + mat.forward.y * vec.y + mat.up.y * vec.z,
	               mat.right.z * vec.x + mat.forward.z * vec.y + mat.up.z * vec.z);
}

CVector
Multiply3x3(const CVector &vec, const CMatrix &mat)
{
	return CVector(mat.right.x * vec.x + mat.right.y * vec.y + mat.right.z * vec.z,
	               mat.forward.x * vec.x + mat.forward.y * vec.y + mat.forward.z * vec.z,
	               mat.up.x * vec.x + mat.up.y * vec.y + mat.up.z * vec.z);
}

CVector
operator*(const CMatrix &mat, const CVector &vec)
{
	// TODO: VU0 code
	return CVector(mat.right.x * vec.x + mat.forward.x * vec.y + mat.up.x * vec.z + mat.pos.x,
	               mat.right.y * vec.x + mat.forward.y * vec.y + mat.up.y * vec.z + mat.pos.y,
	               mat.right.z * vec.x + mat.forward.z * vec.y + mat.up.z * vec.z + mat.pos.z);
}
