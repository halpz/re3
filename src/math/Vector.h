#pragma once

class CVector
{
public:
	float x, y, z;
	CVector(void) {}
	CVector(float x, float y, float z) : x(x), y(y), z(z) {}
//	CVector(CVector &refVector) : x(refVector.x), y(refVector.y), z(refVector.z) { }
//	CVector(const CVector &refVector) : x(refVector.x), y(refVector.y), z(refVector.z) {}
//	CVector(CVector2D &refVector, float _z = 0.0f) : x(refVector.x), y(refVector.y), z(_z) {}
#ifdef RWCORE_H
	CVector(RwV3d const &v) : x(v.x), y(v.y), z(v.z) {}

	operator RwV3d (void) const {
		RwV3d vecRw = { this->x, this->y, this->z };
		return vecRw;
	}
	
	operator RwV3d *(void)
	{
		return (RwV3d *)this;
	}
	
	operator RwV3d &(void)
	{
		return *((RwV3d *)this);
	}
#endif
	float Magnitude(void) const { return sqrt(x*x + y*y + z*z); }
	float MagnitudeSqr(void) const { return x*x + y*y + z*z; }
	float Magnitude2D(void) const { return sqrt(x*x + y*y); }
	void Normalise(void);


	// operator =
	inline CVector const& operator = (CVector const &refRight)
	{
		x = refRight.x;
		y = refRight.y;
		z = refRight.z;
		return *this;
	}
	
	inline CVector const& operator = (float fRight)
	{
		x = fRight;
		y = fRight;
		z = fRight;
		return *this;
	}
	
	// operator +=
	inline CVector const& operator += (CVector const &refRight)
	{
		x += refRight.x;
		y += refRight.y;
		z += refRight.z;
		return *this;
	}
	
	inline CVector const& operator += (float fRight)
	{
		x += fRight;
		y += fRight;
		z += fRight;
		return *this;
	}
	
	// operator -=
	inline CVector const& operator -= (CVector const &refRight)
	{
		x -= refRight.x;
		y -= refRight.y;
		z -= refRight.z;
		return *this;
	}
	
	inline CVector const& operator -= (float fRight)
	{
		x -= fRight;
		y -= fRight;
		z -= fRight;
		return *this;
	}
	
	// operator *=
	inline CVector const& operator *= (CVector const &refRight)
	{
		x *= refRight.x;
		y *= refRight.y;
		z *= refRight.z;
		return *this;
	}
	
	inline CVector const& operator *= (float fRight)
	{
		x *= fRight;
		y *= fRight;
		z *= fRight;
		return *this;
	}
	
	// operator /=
	inline CVector const& operator /= (CVector const &refRight)
	{
		x /= refRight.x;
		y /= refRight.y;
		z /= refRight.z;
		return *this;
	}
	
	inline CVector const& operator /= (float fRight)
	{
		x /= fRight;
		y /= fRight;
		z /= fRight;
		return *this;
	}
	
	inline CVector operator - () const
    {
        return CVector(-x, -y, -z);
    }
	
	bool IsZero(void) { return x == 0.0f && y == 0.0f && z == 0.0f; }
};

//extern CVector operator*(CMatrix const& matrix, CVector const& vector);

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

// operator +
extern CVector operator + (CVector const &refLeft, CVector const &refRight);
extern CVector operator + (CVector const &refLeft, float fRight);
extern CVector operator + (float fLeft, CVector const &refRight);

// operator -
extern CVector operator - (CVector const &refLeft, CVector const &refRight);
extern CVector operator - (CVector const &refLeft, float fRight);
extern CVector operator - (float fLeft, CVector const &refRight);
 
// operator *
extern CVector operator * (CVector const &refLeft, CVector const &refRight);
extern CVector operator * (CVector const &refLeft, float fRight);
extern CVector operator * (float fLeft, CVector const &refRight);
 
// operator /
extern CVector operator / (CVector const &refLeft, CVector const &refRight);
extern CVector operator / (CVector const &refLeft, float fRight);
extern CVector operator / (float fLeft, CVector const &refRight);