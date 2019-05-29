#include "common.h"
#include "Vector.h"

void CVector::Normalise()
{
	float sq = MagnitudeSqr();
	if(sq > 0.0f){
		float invsqrt = 1.0f/sqrt(sq); // CMaths::RecipSqrt
		x *= invsqrt;
		y *= invsqrt;
		z *= invsqrt;
	}else
		x = 1.0f;
}

// operator +
CVector operator + (CVector const &refLeft, CVector const &refRight)
{
	return CVector(refLeft.x + refRight.x, refLeft.y + refRight.y, refLeft.z + refRight.z);
}

CVector operator + (CVector const &refLeft, float fRight)
{
	return CVector(refLeft.x + fRight, refLeft.y + fRight, refLeft.z + fRight);
}

CVector operator + (float fLeft, CVector const &refRight)
{
	return CVector(fLeft + refRight.x, fLeft + refRight.y, fLeft + refRight.z);
}

// operator -
CVector operator - (CVector const &refLeft, CVector const &refRight)
{
	return CVector(refLeft.x - refRight.x, refLeft.y - refRight.y, refLeft.z - refRight.z);
}

CVector operator - (CVector const &refLeft, float fRight)
{
	return CVector(refLeft.x - fRight, refLeft.y - fRight, refLeft.z - fRight);
}

CVector operator - (float fLeft, CVector const &refRight)
{
	return CVector(fLeft - refRight.x, fLeft - refRight.y, fLeft - refRight.z);
}

// operator *
CVector operator * (CVector const &refLeft, CVector const &refRight)
{
	return CVector(refLeft.x * refRight.x, refLeft.y * refRight.y, refLeft.z * refRight.z);
}

CVector operator * (CVector const &refLeft, float fRight)
{
	return CVector(refLeft.x * fRight, refLeft.y * fRight, refLeft.z * fRight);
}

CVector operator * (float fLeft, CVector const &refRight)
{
	return CVector(fLeft * refRight.x, fLeft * refRight.y, fLeft * refRight.z);
}

// operator /
CVector operator / (CVector const &refLeft, CVector const &refRight)
{
	return CVector(refLeft.x / refRight.x, refLeft.y / refRight.y, refLeft.z / refRight.z);
}

CVector operator / (CVector const &refLeft, float fRight)
{
	return CVector(refLeft.x / fRight, refLeft.y / fRight, refLeft.z / fRight);
}

CVector operator / (float fLeft, CVector const &refRight)
{
	return CVector(fLeft / refRight.x, fLeft / refRight.y, fLeft / refRight.z);
}