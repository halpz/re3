#pragma once

class CVector
{
public:
	float x, y, z;
	CVector(void) {}
	CVector(float x, float y, float z) : x(x), y(y), z(z) {}
#ifdef RWCORE_H
	CVector(const RwV3d &v) : x(v.x), y(v.y), z(v.z) {}

	operator RwV3d (void) const {
		RwV3d vecRw = { this->x, this->y, this->z };
		return vecRw;
	}
	
	operator RwV3d *(void) {
		return (RwV3d*)this;
	}
	
	operator RwV3d &(void) {
		return *((RwV3d*)this);
	}
#endif
	float Magnitude(void) const { return sqrt(x*x + y*y + z*z); }
	float MagnitudeSqr(void) const { return x*x + y*y + z*z; }
	float Magnitude2D(void) const { return sqrt(x*x + y*y); }
	void Normalise(void) {
		float sq = MagnitudeSqr();
		if(sq > 0.0f){
			float invsqrt = 1.0f/sqrt(sq); // CMaths::RecipSqrt
			x *= invsqrt;
			y *= invsqrt;
			z *= invsqrt;
		}else
			x = 1.0f;
	}

	inline const CVector &operator+=(CVector const &right) {
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	inline const CVector &operator-=(CVector const &right) {
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	inline const CVector &operator*=(float right) {
		x *= right;
		y *= right;
		z *= right;
		return *this;
	}

	inline const CVector &operator/=(float right) {
		x /= right;
		y /= right;
		z /= right;
		return *this;
	}

	inline CVector operator-() const {
		return CVector(-x, -y, -z);
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

inline CVector operator+(const CVector &left, const CVector &right)
{
	return CVector(left.x + right.x, left.y + right.y, left.z + right.z);
}

inline CVector operator-(const CVector &left, const CVector &right)
{
	return CVector(left.x - right.x, left.y - right.y, left.z - right.z);
}

inline CVector operator*(const CVector &left, float right)
{
	return CVector(left.x * right, left.y * right, left.z * right);
}

inline CVector operator*(float left, const CVector &right)
{
	return CVector(left * right.x, left * right.y, left * right.z);
}

inline CVector operator/(const CVector &left, float right)
{
	return CVector(left.x / right, left.y / right, left.z / right);
}
