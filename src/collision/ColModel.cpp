#include "common.h"
#include "main.h"
#include "ColModel.h"
#include "Collision.h"
#include "Game.h"
#include "MemoryHeap.h"
#include "Pools.h"

CColModel::CColModel(void)
{
	boundingSphere.Set(0.0001f, CVector(0.0f, 0.0f, 0.0f));
	boundingBox.Set(CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f));
	numTriBBoxes = 0;
	triBBoxes = nil;
	numSpheres = 0;
	spheres = nil;
	numLines = 0;
	lines = nil;
	numBoxes = 0;
	boxes = nil;
	numTriangles = 0;
	vertices = nil;
	triangles = nil;
	trianglePlanes = nil;
	level = LEVEL_GENERIC;	// generic col slot
//	ownsCollisionVolumes = true;
}

CColModel::~CColModel(void)
{
	if(!gNASTY_NASTY_MEM_SHUTDOWN_HACK){
		RemoveTrianglePlanes();
		RemoveCollisionVolumes();
	}
}

//--LCS: no pool used, but maybe we better keep it?
void*
CColModel::operator new(size_t) throw()
{
	CColModel* node = CPools::GetColModelPool()->New();
	assert(node);
	return node;
}

void
CColModel::operator delete(void *p, size_t) throw()
{
	CPools::GetColModelPool()->Delete((CColModel*)p);
}

void
CColModel::RemoveCollisionVolumes(void)
{
#ifdef FIX_BUGS
	// why is this missing?
	if(ownsCollisionVolumes)
#endif
	if(!gUseChunkFiles){
		delete[] triBBoxes;
		delete[] spheres;
		delete[] lines;
		delete[] boxes;
		delete[] vertices;
		delete[] triangles;
	}
	CCollision::RemoveTrianglePlanes(this);
	numSpheres = 0;
	numTriBBoxes = 0;
	numLines = 0;
	numBoxes = 0;
	numTriangles = 0;
	spheres = nil;
#ifdef FIX_BUGS
	triBBoxes = nil;
#endif
	lines = nil;
	boxes = nil;
	vertices = nil;
	triangles = nil;
}

void
CColModel::CalculateTrianglePlanes(void)
{
	PUSH_MEMID(MEMID_COLLISION);

	// HACK: allocate space for one more element to stuff the link pointer into
	trianglePlanes = new CColTrianglePlane[numTriangles+1];
	REGISTER_MEMPTR(&trianglePlanes);
	for(int i = 0; i < numTriangles; i++)
		trianglePlanes[i].Set(vertices, triangles[i]);

	POP_MEMID();
}

void
CColModel::RemoveTrianglePlanes(void)
{
	if(trianglePlanes){
		delete[] trianglePlanes;
		trianglePlanes = nil;
	}
}

void
CColModel::SetLinkPtr(CLink<CColModel*> *lptr)
{
	assert(trianglePlanes);
	*(CLink<CColModel*>**)ALIGNPTR(&trianglePlanes[numTriangles]) = lptr;
}

CLink<CColModel*>*
CColModel::GetLinkPtr(void)
{
	assert(trianglePlanes);
	return *(CLink<CColModel*>**)ALIGNPTR(&trianglePlanes[numTriangles]);
}

void
CColModel::GetTrianglePoint(CVector &v, int i) const
{
	v = vertices[i].Get();
}

CColModel&
CColModel::operator=(const CColModel &other)
{
	int i;
	int numVerts;

	boundingSphere = other.boundingSphere;
	boundingBox = other.boundingBox;

	// copy tri bboxes
	if(other.numTriBBoxes){
		if(numTriBBoxes != other.numTriBBoxes){
			numTriBBoxes = other.numTriBBoxes;
			delete[] triBBoxes;
			triBBoxes = new CColTriBBox[numTriBBoxes];
		}
		for(i = 0; i < numTriBBoxes; i++)
			triBBoxes[i] = other.triBBoxes[i];
	}else{
		numTriBBoxes = 0;
		delete[] triBBoxes;
		triBBoxes = nil;
	}

	// copy spheres
	if(other.numSpheres){
		if(numSpheres != other.numSpheres){
			numSpheres = other.numSpheres;
			delete[] spheres;
			spheres = new CColSphere[numSpheres];
		}
		for(i = 0; i < numSpheres; i++)
			spheres[i] = other.spheres[i];
	}else{
		numSpheres = 0;
		delete[] spheres;
		spheres = nil;
	}

	// copy lines
	if(other.numLines){
		if(numLines != other.numLines){
			numLines = other.numLines;
			delete[] lines;
			lines = new CColLine[numLines];
		}
		for(i = 0; i < numLines; i++)
			lines[i] = other.lines[i];
	}else{
		numLines = 0;
		delete[] lines;
		lines = nil;
	}

	// copy boxes
	if(other.numBoxes){
		if(numBoxes != other.numBoxes){
			numBoxes = other.numBoxes;
			delete[] boxes;
			boxes = new CColBox[numBoxes];
		}
		for(i = 0; i < numBoxes; i++)
			boxes[i] = other.boxes[i];
	}else{
		numBoxes = 0;
		delete[] boxes;
		boxes = nil;
	}

	// copy mesh
	if(other.numTriangles){
		// copy vertices
		numVerts = -1;
		for(i = 0; i < other.numTriangles; i++){
			if(other.triangles[i].a > numVerts)
				numVerts = other.triangles[i].a;
			if(other.triangles[i].b > numVerts)
				numVerts = other.triangles[i].b;
			if(other.triangles[i].c > numVerts)
				numVerts = other.triangles[i].c;
		}
		numVerts++;
		delete[] vertices;
		if(numVerts){
			vertices = new CompressedVector[numVerts];
			for(i = 0; i < numVerts; i++)
				vertices[i] = other.vertices[i];
		}

		// copy triangles
		if(numTriangles != other.numTriangles){
			numTriangles = other.numTriangles;
			delete[] triangles;
			triangles = new CColTriangle[numTriangles];
		}
		for(i = 0; i < numTriangles; i++)
			triangles[i] = other.triangles[i];
	}else{
		numTriangles = 0;
		delete[] triangles;
		triangles = nil;
		delete[] vertices;
		vertices = nil;
	}
	return *this;
}

bool
CColModel::Write(base::cRelocatableChunkWriter &writer, bool allocSpace)
{
	int numVerts = -1;
	for(int i = 0; i < numTriangles; i++){
		if(triangles[i].a > numVerts)
			numVerts = triangles[i].a;
		if(triangles[i].b > numVerts)
			numVerts = triangles[i].b;
		if(triangles[i].c > numVerts)
			numVerts = triangles[i].c;
	}
	numVerts++;

	if(allocSpace)
		writer.AllocateRaw(this, sizeof(*this), 16, false, true);
	writer.AllocateRaw(spheres, sizeof(*spheres)*numSpheres, 16, false, true);
	writer.AddPatch(&spheres);
	writer.AllocateRaw(lines, sizeof(*lines)*numLines, 16, false, true);
	writer.AddPatch(&lines);
	writer.AllocateRaw(boxes, sizeof(*boxes)*numBoxes, 16, false, true);
	writer.AddPatch(&boxes);
	if(triBBoxes && numTriBBoxes != 0){
		writer.AllocateRaw(triBBoxes, sizeof(*triBBoxes)*numTriBBoxes, 16, false, true);
		writer.AddPatch(&triBBoxes);
	}else
		triBBoxes = nil;
	if(numTriangles != 0){
		writer.AllocateRaw(vertices, sizeof(*vertices)*numVerts, 2, false, true);
		writer.AddPatch(&vertices);
		writer.AllocateRaw(triangles, sizeof(*triangles)*numTriangles, 2, false, true);
		writer.AddPatch(&triangles);
		RemoveTrianglePlanes();
	}
	return 1;
}
