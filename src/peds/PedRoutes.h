#pragma once

class CRouteNode
{
public:
	int16 m_route;
	CVector m_pos;

	static int16 GetRouteThisPointIsOn(int16);
	static CVector GetPointPosition(int16);
	static int16 GetRouteStart(int16);
};