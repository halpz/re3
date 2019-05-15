#pragma once

#include "Treadable.h"

struct CPathNode
{
	CVector pos;
	CPathNode *prev;	//?
	CPathNode *next;
	int16 unknown;
	int16 objectIndex;
	int16 firstLink;
	uint8 numLinks;
	uint8 flags;
	uint8 group;
/*	VC:
	int16 unk1;
	int16 nextIndex;
	int16 x;
	int16 y;
	int16 z;
	int16 unknown;
	int16 firstLink;
	int8 width;
	int8 group;
	int8 numLinks : 4;
	int8 bDeadEnd : 1;
	int8 bTurnedOff : 1;	// flag 8 in node info
	int8 flagA40 : 1;	// flag 20 in node info
	int8 flagA80 : 1;	// flag 4 in node info
	int8 flagB1 : 1;	// flag 10 in node info
	int8 flagB2 : 1;	// flag 2 in node info
	int8 flagB4 : 1;
	int8 speedLimit : 2;	// speed limit
	int8 flagB20 : 1;
	int8 flagB40 : 1;
	int8 flagB80 : 1;
	int8 spawnRate : 4;
	int8 flagsC : 4;
*/
};

struct CCarPathLink
{
	float posX;
	float posY;
	float dirX;
	float dirY;
	int16 pathNodeIndex;
	int8 numLeftLanes;
	int8 numRightLanes;
	int8 trafficLightType;
	int8 field15;
	// probably only padding
	int8 field16;
	int8 field17;
};

struct CPathInfoForObject
{
	int16 x;
	int16 y;
	int16 z;
	int8 type;
	int8 next;
	int8 numLeftLanes;
	int8 numRightLanes;
	uint8 flag;
};

struct CTempNode
{
	CVector pos;
	float dirX;
	float dirY;
	int16 link1;
	int16 link2;
	int8 numLeftLanes;
	int8 numRightLanes;
	int8 linkState;
	// probably padding
	int8 field1B;
};

struct CTempDetachedNode	// unused
{
	uint8 foo[20];
};

class CPathFind
{
public:
/*	For reference VC:
	CPathNode pathNodes[9650];
	CCarPathLink m_carPathLinks[3500];
	CBuilding *m_mapObjects[1250];
	// 0x8000 is cross road flag
	// 0x4000 is traffic light flag
	uint16 m_connections[20400];
	uint8 m_distances[20400];
	int16 m_carPathConnections[20400];
*/
	CPathNode m_pathNodes[4930];
	CCarPathLink m_carPathLinks[2076];
	CTreadable *m_mapObjects[1250];
	uint8 m_objectFlags[1250];
	int16 m_connections[10260];
	int16 m_distances[10260];
	uint8 m_connectionFlags[10260];
	int16 m_carPathConnections[10260];
	int32 m_numPathNodes;
	int32 m_numCarPathNodes;
	int32 m_numPedPathNodes;
	int16 m_numMapObjects;
	int16 m_numConnections;
	int32 m_numCarPathLinks;
	int32 h;
	uint8 m_numGroups[2];
	CPathNode m_aExtraPaths[872];

	void PreparePathData(void);
	void CountFloodFillGroups(uint8 type);
	void PreparePathDataForType(uint8 type, CTempNode *tempnodes, CPathInfoForObject *objectpathinfo,
		float unk, CTempDetachedNode *detachednodes, int unused);
	void CalcNodeCoors(int16 x, int16 y, int16 z, int32 id, CVector *out);
};
static_assert(sizeof(CPathFind) == 0x4c8f4, "CPathFind: error");

extern CPathFind &ThePaths;
