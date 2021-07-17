#pragma once

struct ActiveOccluderLine {
	CVector2D origin;
	CVector2D direction;
	float length; 
};

class CActiveOccluder {

public:
	ActiveOccluderLine lines[6];
	int32 linesCount;
	float radius; 

	bool IsPointWithinOcclusionArea(float x, float y, float area);
};

class COccluder
{
public:
	int16 length, width, height;
	int16 x, y, z;
	uint16 angle;
	int16 listIndex;

	bool NearCamera();
	bool ProcessOneOccluder(CActiveOccluder *occl);
	bool ProcessLineSegment(int corner1, int corner2, CActiveOccluder* occl);
	float GetAngle(void) { return angle*TWOPI/UINT16_MAX; }
};

class COcclusion
{
public:
	static int32 NumOccludersOnMap;
	static int16 FarAwayList;
	static int16 NearbyList;
	static int16 ListWalkThroughFA;
	static int16 PreviousListWalkThroughFA;
	static int16 NumActiveOccluders;

	static COccluder aOccluders[NUMOCCLUSIONVOLUMES];
	static CActiveOccluder aActiveOccluders[NUMACTIVEOCCLUDERS];

	static void Init(void);
	static void AddOne(float x, float y, float z, float width, float length, float height, float angle);
	static void ProcessBeforeRendering(void); 
	static bool OccluderHidesBehind(CActiveOccluder *occl1, CActiveOccluder *occl2);
	static bool IsAABoxOccluded(CVector pos, float width, float length, float height);
	static bool IsPositionOccluded(CVector pos, float side);
#ifndef MASTER
	static void Render();
#endif
};

bool CalcScreenCoors(CVector const &in, CVector *out, float *outw, float *outh);
bool CalcScreenCoors(CVector const &in, CVector *out);

#ifndef MASTER
extern bool bDispayOccDebugStuff;
#endif