#include "common.h"
#include "patcher.h"
#include "PathFind.h"

CPathFind &ThePaths = *(CPathFind*)0x8F6754;

WRAPPER int32 CPathFind::FindNodeClosestToCoors(CVector coors, uint8 type, float distLimit, bool disabled, bool betweenLevels) { EAXJMP(0x42CC30); }
WRAPPER CPathNode** CPathFind::FindNextNodeWandering(uint8, CVector, CPathNode**, CPathNode**, uint8, uint8*) { EAXJMP(0x42B9F0); }
WRAPPER bool CPathFind::NewGenerateCarCreationCoors(float, float, float, float, float, float, bool, CVector*, int32*, int32*, float*, bool) { EAXJMP(0x42BF10); }
WRAPPER bool CPathFind::TestCoorsCloseness(CVector, bool, CVector) { EAXJMP(0x42C8C0); }
int TempListLength;

enum
{
	NodeTypeExtern = 1,
	NodeTypeIntern = 2,

	PathTypeCar = 0,
	PathTypePed = 1,

	PathNodeFlag1 = 1,	// used?
	PathNodeFlag2 = 2,
	PathNodeDeadEnd = 4,
	PathNodeDisabled = 8,
	PathNodeBetweenLevels = 0x10,

	ConnectionCrossRoad = 1,
	ConnectionTrafficLight = 2,
};

// link flags:
//	1: crosses road
//	2: ped traffic light
// pathnode flags:
//	1:
//	2:
//	4:	dead end
//	8:	switched off
//	10:	road between levels??
// navi node flags:
//	1:	bridge light
// object flags:
//	1
//	2	east/west road(?)

CPathInfoForObject *&InfoForTileCars = *(CPathInfoForObject**)0x8F1A8C;
CPathInfoForObject *&InfoForTilePeds  = *(CPathInfoForObject**)0x8F1AE4;
// unused
CTempDetachedNode *&DetachedNodesCars = *(CTempDetachedNode**)0x8E2824;
CTempDetachedNode *&DetachedNodesPeds = *(CTempDetachedNode**)0x8E28A0;

void
CPathFind::StoreNodeInfoPed(int16 id, int16 node, int8 type, int8 next, int16 x, int16 y, int16 z, int16 width, bool crossing)
{
	int i;

	i = id*12 + node;
	InfoForTilePeds[i].type = type;
	InfoForTilePeds[i].next = next;
	InfoForTilePeds[i].x = x;
	InfoForTilePeds[i].y = y;
	InfoForTilePeds[i].z = z;
	InfoForTilePeds[i].numLeftLanes = 0;
	InfoForTilePeds[i].numRightLanes = 0;
	InfoForTilePeds[i].crossing = crossing;
}

void
CPathFind::StoreNodeInfoCar(int16 id, int16 node, int8 type, int8 next, int16 x, int16 y, int16 z, int16 width, int8 numLeft, int8 numRight)
{
	int i;

	i = id*12 + node;
	InfoForTileCars[i].type = type;
	InfoForTileCars[i].next = next;
	InfoForTileCars[i].x = x;
	InfoForTileCars[i].y = y;
	InfoForTileCars[i].z = z;
	InfoForTileCars[i].numLeftLanes = numLeft;
	InfoForTileCars[i].numRightLanes = numRight;
}

void
CPathFind::RegisterMapObject(CTreadable *mapObject)
{
	m_mapObjects[m_numMapObjects++] = mapObject;
}

void
CPathFind::PreparePathData(void)
{
	int i, j, k;
	int numExtern, numIntern, numLanes;
	float maxX, maxY;
	CTempNode *tempNodes;

	printf("PreparePathData\n");
	// UNUSED: CPathFind::LoadPathFindData
	if(InfoForTileCars && InfoForTilePeds &&
	   DetachedNodesCars && DetachedNodesPeds){
		tempNodes = new CTempNode[4000];

		m_numConnections = 0;
		for(i = 0; i < PATHNODESIZE; i++)
			m_pathNodes[i].flags &= ~(PathNodeFlag1 | PathNodeFlag2);

		for(i = 0; i < PATHNODESIZE; i++){
			numExtern = 0;
			numIntern = 0;
			for(j = 0; j < 12; j++){
				if(InfoForTileCars[i*12 + j].type == NodeTypeExtern)
					numExtern++;
				if(InfoForTileCars[i*12 + j].type == NodeTypeIntern)
					numIntern++;
			}
			if(numIntern > 1 && numExtern != 2)
				printf("ILLEGAL BLOCK. MORE THAN 1 INTERNALS AND NOT 2 EXTERNALS (Modelindex:%d)\n", i);
		}

		for(i = 0; i < PATHNODESIZE; i++)
			for(j = 0; j < 12; j++)
				if(InfoForTileCars[i*12 + j].type == NodeTypeExtern){
					if(InfoForTileCars[i*12 + j].numLeftLanes < 0)
						printf("ILLEGAL BLOCK. NEGATIVE NUMBER OF LANES (Obj:%d)\n", i);
					if(InfoForTileCars[i*12 + j].numRightLanes < 0)
						printf("ILLEGAL BLOCK. NEGATIVE NUMBER OF LANES (Obj:%d)\n", i);
					if(InfoForTileCars[i*12 + j].numLeftLanes + InfoForTileCars[i*12 + j].numRightLanes <= 0)
						printf("ILLEGAL BLOCK. NO LANES IN NODE (Obj:%d)\n", i);
				}

		m_numPathNodes = 0;
		PreparePathDataForType(PathTypeCar, tempNodes, InfoForTileCars, 1.0f, DetachedNodesCars, 100);
		m_numCarPathNodes = m_numPathNodes;
		PreparePathDataForType(PathTypePed, tempNodes, InfoForTilePeds, 1.0f, DetachedNodesPeds, 50);
		m_numPedPathNodes = m_numPathNodes - m_numCarPathNodes;

		// TODO: figure out what exactly is going on here
		// Some roads seem to get a west/east flag
		for(i = 0; i < m_numMapObjects; i++){
			numExtern = 0;
			numIntern = 0;
			numLanes = 0;
			maxX = 0.0f;
			maxY = 0.0f;
			for(j = 0; j < 12; j++){
				k = i*12 + j;
				if(InfoForTileCars[k].type == NodeTypeExtern){
					numExtern++;
					if(InfoForTileCars[k].numLeftLanes + InfoForTileCars[k].numRightLanes > numLanes)
						numLanes = InfoForTileCars[k].numLeftLanes + InfoForTileCars[k].numRightLanes;
					maxX = max(maxX, Abs(InfoForTileCars[k].x));
					maxY = max(maxY, Abs(InfoForTileCars[k].y));
				}else if(InfoForTileCars[k].type == NodeTypeIntern)
					numIntern++;
			}

			if(numIntern == 1 && numExtern == 2){
				if(numLanes < 4){
					if((i & 7) == 4){		// WHAT?
						m_objectFlags[i] |= PathNodeFlag1;
						if(maxX > maxY)
							m_objectFlags[i] |= PathNodeFlag2;
						else
							m_objectFlags[i] &= ~PathNodeFlag2;
					}
				}else{
					m_objectFlags[i] |= PathNodeFlag1;
					if(maxX > maxY)
						m_objectFlags[i] |= PathNodeFlag2;
					else
						m_objectFlags[i] &= ~PathNodeFlag2;
				}
			}
		}

		delete[] tempNodes;

		CountFloodFillGroups(PathTypeCar);
		CountFloodFillGroups(PathTypePed);

		delete[] InfoForTileCars;
		InfoForTileCars = nil;
		delete[] InfoForTilePeds;
		InfoForTilePeds = nil;
		delete[] DetachedNodesCars;
		DetachedNodesCars = nil;
		delete[] DetachedNodesPeds;
		DetachedNodesPeds = nil;
	}
	printf("Done with PreparePathData\n");
}

/* String together connected nodes in a list by a flood fill algorithm */
void
CPathFind::CountFloodFillGroups(uint8 type)
{
	int start, end;
	int i, l;
	uint16 n;
	CPathNode *node, *prev;

	switch(type){
	case PathTypeCar:
		start = 0;
		end = m_numCarPathNodes;
		break;
	case PathTypePed:
		start = m_numCarPathNodes;
		end = start + m_numPedPathNodes;
		break;
	}

	for(i = start; i < end; i++)
		m_pathNodes[i].group = 0;

	n = 0;
	for(;;){
		n++;
		if(n > 1500){
			for(i = start; m_pathNodes[i].group && i < end; i++);
			printf("NumNodes:%d Accounted for:%d\n", end - start, i - start);
		}

		// Look for unvisited node
		for(i = start; m_pathNodes[i].group && i < end; i++);
		if(i == end)
			break;

		node = &m_pathNodes[i];
		node->next = nil;
		node->group = n;

		if(node->numLinks == 0){
			if(type == PathTypeCar)
				printf("Single car node: %f %f %f (%d)\n",
					node->pos.x, node->pos.y, node->pos.z,
					m_mapObjects[node->objectIndex]->m_modelIndex);
			else
				printf("Single ped node: %f %f %f\n",
					node->pos.x, node->pos.y, node->pos.z);
		}

		while(node){
			prev = node;
			node = node->next;
			for(i = 0; i < prev->numLinks; i++){
				l = m_connections[prev->firstLink + i];
				if(m_pathNodes[l].group == 0){
					m_pathNodes[l].group = n;
					if(m_pathNodes[l].group == 0)
						m_pathNodes[l].group = 0x80;	// ???
					m_pathNodes[l].next = node;
					node = &m_pathNodes[l];
				}
			}
		}
	}

	m_numGroups[type] = n-1;
	printf("GraphType:%d. FloodFill groups:%d\n", type, n);
}

void
CPathFind::PreparePathDataForType(uint8 type, CTempNode *tempnodes, CPathInfoForObject *objectpathinfo,
	float maxdist, CTempDetachedNode *detachednodes, int unused)
{
	static CVector CoorsXFormed;
	int i, j, k, l;
	int l1, l2;
	int start, typeoff;
	float posx, posy;
	float dx, dy, mag;
	float nearestDist;
	int nearestId;
	int next;
	int oldNumPathNodes, oldNumLinks;
	CVector dist;
	int iseg, jseg;
	int istart, jstart;
	int done, cont;

	typeoff = 12*type;
	oldNumPathNodes = m_numPathNodes;
	oldNumLinks = m_numConnections;

	// Initialize map objects
	for(i = 0; i < m_numMapObjects; i++)
		for(j = 0; j < 12; j++)
			m_mapObjects[i]->m_nodeIndicesCars[typeoff + j] = -1;

	// Calculate internal nodes, store them and connect them to defining object
	for(i = 0; i < m_numMapObjects; i++){
		start = 12*m_mapObjects[i]->m_modelIndex;
		for(j = 0; j < 12; j++){
			if(objectpathinfo[start + j].type != NodeTypeIntern)
				continue;
			CalcNodeCoors(
				objectpathinfo[start + j].x,
				objectpathinfo[start + j].y,
				objectpathinfo[start + j].z,
				i,
				&CoorsXFormed);
			m_pathNodes[m_numPathNodes].pos = CoorsXFormed;
			m_pathNodes[m_numPathNodes].objectIndex = i;
			m_pathNodes[m_numPathNodes].flags |= PathNodeFlag1;
			m_mapObjects[i]->m_nodeIndicesCars[typeoff + j] = m_numPathNodes++;
		}
	}

	// Insert external nodes into TempList
	TempListLength = 0;
	for(i = 0; i < m_numMapObjects; i++){
		start = 12*m_mapObjects[i]->m_modelIndex;

		for(j = 0; j < 12; j++){
			if(objectpathinfo[start + j].type != NodeTypeExtern)
				continue;
			CalcNodeCoors(
				objectpathinfo[start + j].x,
				objectpathinfo[start + j].y,
				objectpathinfo[start + j].z,
				i,
				&CoorsXFormed);

			// find closest unconnected node
			nearestId = -1;
			nearestDist = maxdist;
			for(k = 0; k < TempListLength; k++){
				if(tempnodes[k].linkState != 1)
					continue;
				dx = tempnodes[k].pos.x - CoorsXFormed.x;
				if(Abs(dx) < nearestDist){
					dy = tempnodes[k].pos.y - CoorsXFormed.y;
					if(Abs(dy) < nearestDist){
						nearestDist = max(Abs(dx), Abs(dy));
						nearestId = k;
					}
				}
			}

			if(nearestId < 0){
				// None found, add this one to temp list
				tempnodes[TempListLength].pos = CoorsXFormed;
				next = objectpathinfo[start + j].next;
				if(next < 0){
					// no link from this node, find link to this node
					next = 0;
					for(k = start; j != objectpathinfo[k].next; k++)
						next++;
				}
				// link to connecting internal node
				tempnodes[TempListLength].link1 = m_mapObjects[i]->m_nodeIndicesCars[typeoff + next];
				if(type == PathTypeCar){
					tempnodes[TempListLength].numLeftLanes = objectpathinfo[start + j].numLeftLanes;
					tempnodes[TempListLength].numRightLanes = objectpathinfo[start + j].numRightLanes;
				}
				tempnodes[TempListLength++].linkState = 1;
			}else{
				// Found nearest, connect it to our neighbour
				next = objectpathinfo[start + j].next;
				if(next < 0){
					// no link from this node, find link to this node
					next = 0;
					for(k = start; j != objectpathinfo[k].next; k++)
						next++;
				}
				tempnodes[nearestId].link2 = m_mapObjects[i]->m_nodeIndicesCars[typeoff + next];
				tempnodes[nearestId].linkState = 2;

				// collapse this node with nearest we found
				dx = m_pathNodes[tempnodes[nearestId].link1].pos.x - m_pathNodes[tempnodes[nearestId].link2].pos.x;
				dy = m_pathNodes[tempnodes[nearestId].link1].pos.y - m_pathNodes[tempnodes[nearestId].link2].pos.y;
				tempnodes[nearestId].pos = (tempnodes[nearestId].pos + CoorsXFormed)*0.5f;
				mag = Sqrt(dx*dx + dy*dy);
				tempnodes[nearestId].dirX = dx/mag;
				tempnodes[nearestId].dirY = dy/mag;
				// do something when number of lanes doesn't agree
				if(type == PathTypeCar)
					if(tempnodes[nearestId].numLeftLanes != 0 && tempnodes[nearestId].numRightLanes != 0 &&
					   (objectpathinfo[start + j].numLeftLanes == 0 || objectpathinfo[start + j].numRightLanes == 0)){
						// why switch left and right here?
						tempnodes[nearestId].numLeftLanes = objectpathinfo[start + j].numRightLanes;
						tempnodes[nearestId].numRightLanes = objectpathinfo[start + j].numLeftLanes;
					}
			}
		}
	}

	// Loop through previously added internal nodes and link them
	for(i = oldNumPathNodes; i < m_numPathNodes; i++){
		// Init link
		m_pathNodes[i].numLinks = 0;
		m_pathNodes[i].firstLink = m_numConnections;

		// See if node connects to external nodes
		for(j = 0; j < TempListLength; j++){
			if(tempnodes[j].linkState != 2)
				continue;

			// Add link to other side of the external
			if(tempnodes[j].link1 == i)
				m_connections[m_numConnections] = tempnodes[j].link2;
			else if(tempnodes[j].link2 == i)
				m_connections[m_numConnections] = tempnodes[j].link1;
			else
				continue;

			dist = m_pathNodes[i].pos - m_pathNodes[m_connections[m_numConnections]].pos;
			m_distances[m_numConnections] = dist.Magnitude();
			m_connectionFlags[m_numConnections] = 0;

			if(type == PathTypeCar){
				// IMPROVE: use a goto here
				// Find existing car path link
				for(k = 0; k < m_numCarPathLinks; k++){
					if(m_carPathLinks[k].dirX == tempnodes[j].dirX &&
					   m_carPathLinks[k].dirY == tempnodes[j].dirY &&
					   m_carPathLinks[k].posX == tempnodes[j].pos.x &&
					   m_carPathLinks[k].posY == tempnodes[j].pos.y){
						m_carPathConnections[m_numConnections] = k;
						k = m_numCarPathLinks;
					}
				}
				// k is m_numCarPathLinks+1 if we found one
				if(k == m_numCarPathLinks){
					m_carPathLinks[m_numCarPathLinks].dirX = tempnodes[j].dirX;
					m_carPathLinks[m_numCarPathLinks].dirY = tempnodes[j].dirY;
					m_carPathLinks[m_numCarPathLinks].posX = tempnodes[j].pos.x;
					m_carPathLinks[m_numCarPathLinks].posY = tempnodes[j].pos.y;
					m_carPathLinks[m_numCarPathLinks].pathNodeIndex = i;
					m_carPathLinks[m_numCarPathLinks].numLeftLanes = tempnodes[j].numLeftLanes;
					m_carPathLinks[m_numCarPathLinks].numRightLanes = tempnodes[j].numRightLanes;
					m_carPathLinks[m_numCarPathLinks].trafficLightType = 0;
					m_carPathConnections[m_numConnections] = m_numCarPathLinks++;
				}
			}

			m_pathNodes[i].numLinks++;
			m_numConnections++;
		}

		// Find i inside path segment
		iseg = 0;
		for(j = max(oldNumPathNodes, i-12); j < i; j++)
			if(m_pathNodes[j].objectIndex == m_pathNodes[i].objectIndex)
				iseg++;

		istart = 12*m_mapObjects[m_pathNodes[i].objectIndex]->m_modelIndex;
		// Add links to other internal nodes
		for(j = max(oldNumPathNodes, i-12); j < min(m_numPathNodes, i+12); j++){
			if(m_pathNodes[i].objectIndex != m_pathNodes[j].objectIndex || i == j)
				continue;
			// N.B.: in every path segment, the externals have to be at the end
			jseg = j-i + iseg;

			jstart = 12*m_mapObjects[m_pathNodes[j].objectIndex]->m_modelIndex;
			if(objectpathinfo[istart + iseg].next == jseg ||
			   objectpathinfo[jstart + jseg].next == iseg){
				// Found a link between i and j
				m_connections[m_numConnections] = j;
				dist = m_pathNodes[i].pos - m_pathNodes[j].pos;
				m_distances[m_numConnections] = dist.Magnitude();

				if(type == PathTypeCar){
					posx = (m_pathNodes[i].pos.x + m_pathNodes[j].pos.x)*0.5f;
					posy = (m_pathNodes[i].pos.y + m_pathNodes[j].pos.y)*0.5f;
					dx = m_pathNodes[j].pos.x - m_pathNodes[i].pos.x;
					dy = m_pathNodes[j].pos.y - m_pathNodes[i].pos.y;
					mag = Sqrt(dx*dx + dy*dy);
					dx /= mag;
					dy /= mag;
					if(i < j){
						dx = -dx;
						dy = -dy;
					}
					// IMPROVE: use a goto here
					// Find existing car path link
					for(k = 0; k < m_numCarPathLinks; k++){
						if(m_carPathLinks[k].dirX == dx &&
						   m_carPathLinks[k].dirY == dy &&
						   m_carPathLinks[k].posX == posx &&
						   m_carPathLinks[k].posY == posy){
							m_carPathConnections[m_numConnections] = k;
							k = m_numCarPathLinks;
						}
					}
					// k is m_numCarPathLinks+1 if we found one
					if(k == m_numCarPathLinks){
						m_carPathLinks[m_numCarPathLinks].dirX = dx;
						m_carPathLinks[m_numCarPathLinks].dirY = dy;
						m_carPathLinks[m_numCarPathLinks].posX = posx;
						m_carPathLinks[m_numCarPathLinks].posY = posy;
						m_carPathLinks[m_numCarPathLinks].pathNodeIndex = i;
						m_carPathLinks[m_numCarPathLinks].numLeftLanes = -1;
						m_carPathLinks[m_numCarPathLinks].numRightLanes = -1;
						m_carPathLinks[m_numCarPathLinks].trafficLightType = 0;
						m_carPathConnections[m_numConnections] = m_numCarPathLinks++;
					}
				}else{
					// Crosses road
					if(objectpathinfo[istart + iseg].next == jseg && objectpathinfo[istart + iseg].crossing ||
					   objectpathinfo[jstart + jseg].next == iseg && objectpathinfo[jstart + jseg].crossing)
						m_connectionFlags[m_numConnections] |= ConnectionCrossRoad;
					else
						m_connectionFlags[m_numConnections] &= ~ConnectionCrossRoad;
				}

				m_pathNodes[i].numLinks++;
				m_numConnections++;
			}
		}
	}

	if(type == PathTypeCar){
		done = 0;
		// Set number of lanes for all nodes somehow
		// very strange code
		for(k = 0; !done && k < 10; k++){
			done = 1;
			for(i = 0; i < m_numPathNodes; i++){
				if(m_pathNodes[i].numLinks != 2)
					continue;
				l1 = m_carPathConnections[m_pathNodes[i].firstLink];
				l2 = m_carPathConnections[m_pathNodes[i].firstLink+1];

				if(m_carPathLinks[l1].numLeftLanes == -1 &&
				   m_carPathLinks[l2].numLeftLanes != -1){
					done = 0;
					if(m_carPathLinks[l2].pathNodeIndex == i){
						// why switch left and right here?
						m_carPathLinks[l1].numLeftLanes = m_carPathLinks[l2].numRightLanes;
						m_carPathLinks[l1].numRightLanes = m_carPathLinks[l2].numLeftLanes;
					}else{
						m_carPathLinks[l1].numLeftLanes = m_carPathLinks[l2].numLeftLanes;
						m_carPathLinks[l1].numRightLanes = m_carPathLinks[l2].numRightLanes;
					}
					m_carPathLinks[l1].pathNodeIndex = i;
				}else if(m_carPathLinks[l1].numLeftLanes != -1 &&
				         m_carPathLinks[l2].numLeftLanes == -1){
					done = 0;
					if(m_carPathLinks[l1].pathNodeIndex == i){
						// why switch left and right here?
						m_carPathLinks[l2].numLeftLanes = m_carPathLinks[l1].numRightLanes;
						m_carPathLinks[l2].numRightLanes = m_carPathLinks[l1].numLeftLanes;
					}else{
						m_carPathLinks[l2].numLeftLanes = m_carPathLinks[l1].numLeftLanes;
						m_carPathLinks[l2].numRightLanes = m_carPathLinks[l1].numRightLanes;
					}
					m_carPathLinks[l2].pathNodeIndex = i;
				}else if(m_carPathLinks[l1].numLeftLanes == -1 &&
				         m_carPathLinks[l2].numLeftLanes == -1)
					done = 0;
			}
		}

		// Fall back to default values for number of lanes
		for(i = 0; i < m_numPathNodes; i++)
			for(j = 0; j < m_pathNodes[i].numLinks; j++){
				k = m_carPathConnections[m_pathNodes[i].firstLink + j];
				if(m_carPathLinks[k].numLeftLanes < 0)
					m_carPathLinks[k].numLeftLanes = 1;
				if(m_carPathLinks[k].numRightLanes < 0)
					m_carPathLinks[k].numRightLanes = 1;
			}
	}

	// Set flags for car nodes
	if(type == PathTypeCar){
		do{
			cont = 0;
			for(i = 0; i < m_numPathNodes; i++){
				m_pathNodes[i].flags &= ~PathNodeDisabled;
				m_pathNodes[i].flags &= ~PathNodeBetweenLevels;
				// See if node is a dead end, if so, we're not done yet
				if((m_pathNodes[i].flags & PathNodeDeadEnd) == 0){
					k = 0;
					for(j = 0; j < m_pathNodes[i].numLinks; j++)
						if((m_pathNodes[m_connections[m_pathNodes[i].firstLink + j]].flags & PathNodeDeadEnd) == 0)
							k++;
					if(k < 2){
						m_pathNodes[i].flags |= PathNodeDeadEnd;
						cont = 1;
					}
				}
			}
		}while(cont);
	}

	// Remove isolated ped nodes
	if(type == PathTypePed)
		for(i = oldNumPathNodes; i < m_numPathNodes; i++){
			if(m_pathNodes[i].numLinks != 0)
				continue;

			// Remove node
			for(j = i; j < m_numPathNodes-1; j++)
				m_pathNodes[j] = m_pathNodes[j+1];

			// Fix links
			for(j = oldNumLinks; j < m_numConnections; j++)
				if(m_connections[j] >= i)
					m_connections[j]--;

			// Also in treadables
			for(j = 0; j < m_numMapObjects; j++)
				for(k = 0; k < 12; k++){
					if(m_mapObjects[j]->m_nodeIndicesPeds[k] == i){
						// remove this one
						for(l = k; l < 12-1; l++)
							m_mapObjects[j]->m_nodeIndicesPeds[l] = m_mapObjects[j]->m_nodeIndicesPeds[l+1];
						m_mapObjects[j]->m_nodeIndicesPeds[11] = -1;
					}else if(m_mapObjects[j]->m_nodeIndicesPeds[k] > i)
						m_mapObjects[j]->m_nodeIndicesPeds[k]--;
				}

			i--;
			m_numPathNodes--;
		}
}

void
CPathFind::CalcNodeCoors(int16 x, int16 y, int16 z, int id, CVector *out)
{
	CVector pos;
	pos.x = x / 16.0f;
	pos.y = y / 16.0f;
	pos.z = z / 16.0f;
	*out = m_mapObjects[id]->GetMatrix() * pos;
}

WRAPPER void CPathFind::SetLinksBridgeLights(float, float, float, float, bool) { EAXJMP(0x42E3B0); }

STARTPATCHES
	InjectHook(0x429610, &CPathFind::PreparePathData, PATCH_JUMP);
	InjectHook(0x429C20, &CPathFind::PreparePathDataForType, PATCH_JUMP);
	InjectHook(0x42B810, &CPathFind::CountFloodFillGroups, PATCH_JUMP);
ENDPATCHES
