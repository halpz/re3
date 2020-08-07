#pragma once

class TYPEALIGN(16) CVuVector : public CVector
{
public:
	float w;
	CVuVector(void) {}
	CVuVector(float x, float y, float z) : CVector(x, y, z) {}
	CVuVector(float x, float y, float z, float w) : CVector(x, y, z), w(w) {}
	CVuVector(const CVector &v) : CVector(v.x, v.y, v.z) {}
#ifdef RWCORE_H
	CVuVector(const RwV3d &v) : CVector(v.x, v.y, v.z) {}

	operator RwV3d (void) const {
		RwV3d vecRw = { this->x, this->y, this->z };
		return vecRw;
	}
	
	operator RwV3d *(void) {
		return (RwV3d*)this;
	}
#endif
/*
	void Normalise(void) {
		float sq = MagnitudeSqr();
		// TODO: VU0 code
		if(sq > 0.0f){
			float invsqrt = RecipSqrt(sq);
			x *= invsqrt;
			y *= invsqrt;
			z *= invsqrt;
		}else
			x = 1.0f;
	}
*/
};

void TransformPoint(CVuVector &out, const CMatrix &mat, const CVuVector &in);
void TransformPoint(CVuVector &out, const CMatrix &mat, const RwV3d &in);
void TransformPoints(CVuVector *out, int n, const CMatrix &mat, const RwV3d *in, int stride);
void TransformPoints(CVuVector *out, int n, const CMatrix &mat, const CVuVector *in);
