#include "common.h"
#include "patcher.h"
#include "main.h"
#include "PedRoutes.h"

CRouteNode (&gaRoutes)[NUMPEDROUTES] = *(CRouteNode(*)[NUMPEDROUTES]) * (uintptr*)0x62E090;

int16
CRouteNode::GetRouteThisPointIsOn(int16 point)
{
	return gaRoutes[point].m_route;
}

// Actually GetFirstPointOfRoute
int16
CRouteNode::GetRouteStart(int16 route)
{
	for (int i = 0; i < NUMPEDROUTES; i++) {
		if (route == gaRoutes[i].m_route)
			return i;
	}
	return -1;
}

CVector
CRouteNode::GetPointPosition(int16 point)
{
	return gaRoutes[point].m_pos;
}

void
CRouteNode::AddRoutePoint(int16 route, CVector pos)
{
	uint16 point;
	for (point = 0; point < NUMPEDROUTES; point++) {
		if (gaRoutes[point].m_route == -1)
			break;
	}
#ifdef FIX_BUGS
	if (point == NUMPEDROUTES)
		return;
#endif
	gaRoutes[point].m_route = route;
	gaRoutes[point].m_pos = pos;
}
