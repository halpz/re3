#pragma once

class CVector
{
public:
	float x, y, z;
	CVector(void) {}
	CVector(float x, float y, float z) : x(x), y(y), z(z) {}
//	CVector(rw::V3d const &v) : x(v.x), y(v.y), z(v.z) {}
	float Magnitude(void) const { return sqrt(x*x + y*y + z*z); }
	float MagnitudeSqr(void) const { return x*x + y*y + z*z; }
	float Magnitude2D(void) const { return sqrt(x*x + y*y); }
	void Normalise(void){
		float sq = MagnitudeSqr();
		if(sq > 0.0f){
			float invsqrt = 1.0f/sqrt(sq);
			x *= invsqrt;
			y *= invsqrt;
			z *= invsqrt;
		}else
			x = 1.0f;
	}
//	rw::V3d ToRW(void){
//		return rw::makeV3d(x, y, z);
//	}
//	void operator=(rw::V3d const &rhs){
//		x = rhs.x;
//		y = rhs.y;
//		z = rhs.z;
//	}
	CVector operator-(const CVector &rhs) const {
		return CVector(x-rhs.x, y-rhs.y, z-rhs.z);
	}
	CVector operator+(const CVector &rhs) const {
		return CVector(x+rhs.x, y+rhs.y, z+rhs.z);
	}
	CVector operator*(float t) const {
		return CVector(x*t, y*t, z*t);
	}
	CVector operator/(float t) const {
		return CVector(x/t, y/t, z/t);
	}
	CVector &operator-=(const CVector &rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}
	CVector &operator+=(const CVector &rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}
	CVector &operator*=(float t) {
		this->x *= t;
		this->y *= t;
		this->z *= t;
		return *this;
	}
	CVector &operator/=(float t) {
		this->x /= t;
		this->y /= t;
		this->z /= t;
		return *this;
	}
	bool IsZero(void) { return x == 0.0f && y == 0.0f && z == 0.0f; }
};

inline float
DotProduct(const CVector &v1, const CVector &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline CVector
CrossProduct(const CVector &v1, const CVector &v2)
{
	return CVector(
		v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x);
}
