#pragma once

#include "templates.h"
#include "ColBox.h"
#include "ColSphere.h"
#include "ColLine.h"
#include "ColPoint.h"
#include "ColTriangle.h"

struct CColModel
{
	CSphere boundingSphere;
	CBox boundingBox;
	int16 numSpheres;
	int16 numBoxes;
	int16 numTriangles;
	int8 numLines;
	int8 numTriBBoxes;
	uint8 level;	// colstore slot but probably still named level
	bool ownsCollisionVolumes;
	CColSphere *spheres;
	CColLine *lines;
	CColBox *boxes;
	CColTriBBox *triBBoxes;
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

	void *operator new(size_t) throw();
	void operator delete(void *p, size_t) throw();
	CColModel& operator=(const CColModel& other);

	bool Write(base::cRelocatableChunkWriter &writer, bool allocSpace);
};