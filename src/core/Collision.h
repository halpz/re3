#pragma once

#include "templates.h"
#include "Game.h"	// for eLevelName
#ifdef VU_COLLISION
#include "VuVector.h"
#endif

// If you spawn many tanks at once, you will see that collisions of two entity exceeds 32.
#if defined(FIX_BUGS) && !defined(SQUEEZE_PERFORMANCE)
#define MAX_COLLISION_POINTS 64
#else
#define MAX_COLLISION_POINTS 32
#endif

struct CompressedVector
{
#ifdef COMPRESSED_COL_VECTORS
	int16 x, y, z;
	CVector Get(void) const { return CVector(x, y, z)/128.0f; };
	void Set(float x, float y, float z) { this->x = x*128.0f; this->y = y*128.0f; this->z = z*128.0f; };
#ifdef GTA_PS2
	void Unpack(uint128 &qword) const {
		__asm__ volatile (
			"lh      $8, 0(%1)\n"
			"lh      $9, 2(%1)\n"
			"lh      $10, 4(%1)\n"
			"pextlw  $10, $8\n"
			"pextlw  $2, $9, $10\n"
			"sq      $2, %0\n"
			: "=m" (qword)
			: "r" (this)
			: "$8", "$9", "$10", "$2"
		);
	}
#else
	void Unpack(int32 *qword) const {
		qword[0] = x;
		qword[1] = y;
		qword[2] = z;
		qword[3] = 0;	// junk
	}
#endif
#else
	float x, y, z;
	CVector Get(void) const { return CVector(x, y, z); };
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };
#endif
};

struct CSphere
{
	// NB: this has to be compatible with a CVuVector
	CVector center;
	float radius;
	void Set(float radius, const CVector &center) { this->center = center; this->radius = radius; }
};

struct CBox
{
	CVector min;
	CVector max;
	CVector GetSize(void) { return max - min; }
	void Set(const CVector &min, const CVector &max) {  this->min = min; this->max = max; }
};

struct CColSphere : public CSphere
{
	uint8 surface;
	uint8 piece;

	void Set(float radius, const CVector &center, uint8 surf, uint8 piece);
	bool IntersectRay(CVector const &from, CVector const &dir, CVector &entry, CVector &exit);
	using CSphere::Set;
};

struct CColBox : public CBox
{
	uint8 surface;
	uint8 piece;

	void Set(const CVector &min, const CVector &max, uint8 surf, uint8 piece);
	using CBox::Set;
};

struct CColLine
{
	// NB: this has to be compatible with two CVuVectors
	CVector p0;
	int pad0;
	CVector p1;
	int pad1;

	CColLine(void) { };
	CColLine(const CVector &p0, const CVector &p1) { this->p0 = p0; this->p1 = p1; };
	void Set(const CVector &p0, const CVector &p1);
};

struct CColTriangle
{
	uint16 a;
	uint16 b;
	uint16 c;
	uint8 surface;

	void Set(const CompressedVector *v, int a, int b, int c, uint8 surf, uint8 piece);
};

struct CColTrianglePlane
{
#ifdef VU_COLLISION
	CompressedVector normal;
	int16 dist;

	void Set(const CVector &va, const CVector &vb, const CVector &vc);
	void Set(const CompressedVector *v, CColTriangle &tri) { Set(v[tri.a].Get(), v[tri.b].Get(), v[tri.c].Get()); }
	void GetNormal(CVector &n) const { n.x = normal.x/4096.0f; n.y = normal.y/4096.0f; n.z = normal.z/4096.0f; }
	float CalcPoint(const CVector &v) const { CVector n; GetNormal(n); return DotProduct(n, v) - dist/128.0f; };
#ifdef GTA_PS2
	void Unpack(uint128 &qword) const {
		__asm__ volatile (
			"lh      $8, 0(%1)\n"
			"lh      $9, 2(%1)\n"
			"lh      $10, 4(%1)\n"
			"lh      $11, 6(%1)\n"
			"pextlw  $10, $8\n"
			"pextlw  $11, $9\n"
			"pextlw  $2, $11, $10\n"
			"sq      $2, %0\n"
			: "=m" (qword)
			: "r" (this)
			: "$8", "$9", "$10", "$11", "$2"
		);
	}
#else
	void Unpack(int32 *qword) const {
		qword[0] = normal.x;
		qword[1] = normal.y;
		qword[2] = normal.z;
		qword[3] = dist;
	}
#endif
#else
	CVector normal;
	float dist;
	uint8 dir;

	void Set(const CVector &va, const CVector &vb, const CVector &vc);
	void Set(const CompressedVector *v, CColTriangle &tri) { Set(v[tri.a].Get(), v[tri.b].Get(), v[tri.c].Get()); }
	void GetNormal(CVector &n) const { n = normal; }
	float GetNormalX() const { return normal.x; }
	float GetNormalY() const { return normal.y; }
	float GetNormalZ() const { return normal.z; }
	float CalcPoint(const CVector &v) const { return DotProduct(normal, v) - dist; };
#endif
};

struct CColPoint
{
	CVector point;
	int pad1;
	// the surface normal on the surface of point
	CVector normal;
	int pad2;
	uint8 surfaceA;
	uint8 pieceA;
	uint8 surfaceB;
	uint8 pieceB;
	float depth;

	CColPoint& operator=(const CColPoint& other);
};

struct CStoredCollPoly
{
#ifdef VU_COLLISION
	CVuVector verts[3];
#else
	CVector verts[3];
#endif
	bool valid;
};

//--MIAMI: done struct
struct CColModel
{
	CSphere boundingSphere;
	CBox boundingBox;
	int16 numSpheres;
	int16 numBoxes;
	int16 numTriangles;
	int8 numLines;
	uint8 level;	// colstore slot but probably still named level
	bool ownsCollisionVolumes;
	CColSphere *spheres;
	CColLine *lines;
	CColBox *boxes;
	CompressedVector *vertices;
	CColTriangle *triangles;
	CColTrianglePlane *trianglePlanes;

	CColModel(void);
	~CColModel(void);
	void RemoveCollisionVolumes(void);
	void CalculateTrianglePlanes(void);
	void RemoveTrianglePlanes(void);
	CLink<CColModel*> *GetLinkPtr(void);
	void SetLinkPtr(CLink<CColModel*>*);
	void GetTrianglePoint(CVector &v, int i) const;

	CColModel& operator=(const CColModel& other);
};

class CCollision
{
public:
	static eLevelName ms_collisionInMemory;
	static CLinkList<CColModel*> ms_colModelCache;

	static void Init(void);
	static void Shutdown(void);
	static void Update(void);
	static void LoadCollisionWhenINeedIt(bool changeLevel);
	static void SortOutCollisionAfterLoad(void);
	static void LoadCollisionScreen(eLevelName level);
	static void DrawColModel(const CMatrix &mat, const CColModel &colModel);
	static void DrawColModel_Coloured(const CMatrix &mat, const CColModel &colModel, int32 id);

	static void CalculateTrianglePlanes(CColModel *model);
	static void RemoveTrianglePlanes(CColModel *model);

	// all these return true if there's a collision
	static bool TestSphereSphere(const CSphere &s1, const CSphere &s2);
	static bool TestSphereBox(const CSphere &sph, const CBox &box);
	static bool TestLineBox(const CColLine &line, const CBox &box);
	static bool TestVerticalLineBox(const CColLine &line, const CBox &box);
	static bool TestLineTriangle(const CColLine &line, const CompressedVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane);
	static bool TestLineSphere(const CColLine &line, const CColSphere &sph);
	static bool TestSphereTriangle(const CColSphere &sphere, const CompressedVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane);
	static bool TestLineOfSight(const CColLine &line, const CMatrix &matrix, CColModel &model, bool ignoreSeeThrough, bool ignoreShootThrough);

	static bool ProcessSphereSphere(const CColSphere &s1, const CColSphere &s2, CColPoint &point, float &mindistsq);
	static bool ProcessSphereBox(const CColSphere &sph, const CColBox &box, CColPoint &point, float &mindistsq);
	static bool ProcessLineBox(const CColLine &line, const CColBox &box, CColPoint &point, float &mindist);
	static bool ProcessVerticalLineTriangle(const CColLine &line, const CompressedVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane, CColPoint &point, float &mindist, CStoredCollPoly *poly);
	static bool ProcessLineTriangle(const CColLine &line , const CompressedVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane, CColPoint &point, float &mindist, CStoredCollPoly *poly = nil);
	static bool ProcessLineSphere(const CColLine &line, const CColSphere &sphere, CColPoint &point, float &mindist);
	static bool ProcessSphereTriangle(const CColSphere &sph, const CompressedVector *verts, const CColTriangle &tri, const CColTrianglePlane &plane, CColPoint &point, float &mindistsq);
	static bool ProcessLineOfSight(const CColLine &line, const CMatrix &matrix, CColModel &model, CColPoint &point, float &mindist, bool ignoreSeeThrough, bool ignoreShootThrough);
	static bool ProcessVerticalLine(const CColLine &line, const CMatrix &matrix, CColModel &model, CColPoint &point, float &mindist, bool ignoreSeeThrough, bool ignoreShootThrough, CStoredCollPoly *poly);
	static int32 ProcessColModels(const CMatrix &matrixA, CColModel &modelA, const CMatrix &matrixB, CColModel &modelB, CColPoint *spherepoints, CColPoint *linepoints, float *linedists);
	static bool IsStoredPolyStillValidVerticalLine(const CVector &pos, float z, CColPoint &point, CStoredCollPoly *poly);

	static float DistToLine(const CVector *l0, const CVector *l1, const CVector *point);
	static float DistToLine(const CVector *l0, const CVector *l1, const CVector *point, CVector &closest);
};
