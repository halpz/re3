#pragma once

class CVector2D
{
public:
	float x, y;
	CVector2D(void) {}
	CVector2D(float x, float y) : x(x), y(y) {}
	CVector2D(const CVector &v) : x(v.x), y(v.y) {}
	float Magnitude(void) const { return Sqrt(x*x + y*y); }
	float MagnitudeSqr(void) const { return x*x + y*y; }

	void Normalise(void){
		float sq = MagnitudeSqr();
		if(sq > 0.0f){
			float invsqrt = 1.0f/Sqrt(sq);
			x *= invsqrt;
			y *= invsqrt;
		}else
			x = 0.0f;
	}
	CVector2D operator-(const CVector2D &rhs) const {
		return CVector2D(x-rhs.x, y-rhs.y);
	}
	CVector2D operator+(const CVector2D &rhs) const {
		return CVector2D(x+rhs.x, y+rhs.y);
	}
	CVector2D operator*(float t) const {
		return CVector2D(x*t, y*t);
	}
};

inline float
DotProduct2D(const CVector2D &v1, const CVector2D &v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

inline float
CrossProduct2D(const CVector2D &v1, const CVector2D &v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}
