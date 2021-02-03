#pragma once

#include "SurfaceTable.h"

// TODO(LCS): maybe this was in a union with CVuVector? or is the alignment manual?
struct TYPEALIGN(16) CSphere
{
	// NB: this has to be compatible with a CVuVector
	RwV3d center;
	float radius;
	void Set(float radius, const CVector &center) { this->center = center; this->radius = radius; }
};

struct CColSphere : public CSphere
{
	uint8 surface;
	uint8 piece;

	void Set(float radius, const CVector &center, uint8 surf, uint8 piece);
	bool IntersectRay(CVector const &from, CVector const &dir, CVector &entry, CVector &exit);
	using CSphere::Set;
};