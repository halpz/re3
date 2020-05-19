#include "common.h"

#include "Occlusion.h"

int32 COcclusion::NumOccludersOnMap;
int16 COcclusion::FarAwayList;
int16 COcclusion::NearbyList;
int16 COcclusion::ListWalkThroughFA;
int16 COcclusion::PreviousListWalkThroughFA;
COccluder COcclusion::aOccluders[NUMOCCLUSIONVOLUMES];

void
COcclusion::Init(void)
{
	NumOccludersOnMap = 0;
	FarAwayList = -1;
	NearbyList = -1;
	ListWalkThroughFA = -1;
	PreviousListWalkThroughFA = -1;
}

void
COcclusion::AddOne(float x, float y, float z, float width, float length, float height, float angle)
{
	if(NumOccludersOnMap >= NUMOCCLUSIONVOLUMES)
		return;

	aOccluders[NumOccludersOnMap].x = x;
	aOccluders[NumOccludersOnMap].y = y;
	aOccluders[NumOccludersOnMap].z = z;
	aOccluders[NumOccludersOnMap].width = width;
	aOccluders[NumOccludersOnMap].length = length;
	aOccluders[NumOccludersOnMap].height = height;
	while(angle < 0.0f) angle += 360.0f;
	while(angle > 360.0f) angle -= 360.0f;
	aOccluders[NumOccludersOnMap].angle = angle * UINT16_MAX/360.0f;
	aOccluders[NumOccludersOnMap].listIndex = FarAwayList;
	FarAwayList = NumOccludersOnMap++;
}

void
COcclusion::ProcessBeforeRendering(void)
{
}
