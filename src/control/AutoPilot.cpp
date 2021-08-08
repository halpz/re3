#include "common.h"

#include "AutoPilot.h"

#include "CarCtrl.h"
#include "Curves.h"
#include "PathFind.h"
#include "SaveBuf.h"

//--LCS: file done

void CAutoPilot::ModifySpeed(float speed)
{
	m_fMaxTrafficSpeed = Max(0.01f, speed);
	float positionBetweenNodes = (float)(CTimer::GetTimeInMilliseconds() - m_nTimeEnteredCurve) / m_nTimeToSpendOnCurrentCurve;
	CCarPathLink* pCurrentLink = &ThePaths.m_carPathLinks[m_nCurrentPathNodeInfo];
	CCarPathLink* pNextLink = &ThePaths.m_carPathLinks[m_nNextPathNodeInfo];
	float currentPathLinkForwardX = m_nCurrentDirection * ThePaths.m_carPathLinks[m_nCurrentPathNodeInfo].GetDirX();
	float currentPathLinkForwardY = m_nCurrentDirection * ThePaths.m_carPathLinks[m_nCurrentPathNodeInfo].GetDirY();
	float nextPathLinkForwardX = m_nNextDirection * ThePaths.m_carPathLinks[m_nNextPathNodeInfo].GetDirX();
	float nextPathLinkForwardY = m_nNextDirection * ThePaths.m_carPathLinks[m_nNextPathNodeInfo].GetDirY();
	CVector positionOnCurrentLinkIncludingLane(
		pCurrentLink->GetX() + ((m_nCurrentLane + 0.5f) * LANE_WIDTH) * currentPathLinkForwardY,
		pCurrentLink->GetY() - ((m_nCurrentLane + 0.5f) * LANE_WIDTH) * currentPathLinkForwardX,
		0.0f);
	CVector positionOnNextLinkIncludingLane(
		pNextLink->GetX() + ((m_nNextLane + 0.5f) * LANE_WIDTH) * nextPathLinkForwardY,
		pNextLink->GetY() - ((m_nNextLane + 0.5f) * LANE_WIDTH) * nextPathLinkForwardX,
		0.0f);
	m_nTimeToSpendOnCurrentCurve = CCurves::CalcSpeedScaleFactor(
		&positionOnCurrentLinkIncludingLane,
		&positionOnNextLinkIncludingLane,
		currentPathLinkForwardX, currentPathLinkForwardY,
		nextPathLinkForwardX, nextPathLinkForwardY
	) * (1000.0f / m_fMaxTrafficSpeed);
#ifdef FIX_BUGS
	/* Casting timer to float is very unwanted, and in this case even causes crashes. */
	m_nTimeEnteredCurve = CTimer::GetTimeInMilliseconds() -
		(uint32)(positionBetweenNodes * m_nTimeToSpendOnCurrentCurve);
#else
	m_nTimeEnteredCurve = CTimer::GetTimeInMilliseconds() - positionBetweenNodes * m_nTimeToSpendOnCurrentCurve;
#endif
}

void CAutoPilot::RemoveOnePathNode()
{
	--m_nPathFindNodesCount;
	for (int i = 0; i < m_nPathFindNodesCount; i++)
		m_aPathFindNodesInfo[i] = m_aPathFindNodesInfo[i + 1];
}

#ifdef COMPATIBLE_SAVES
void CAutoPilot::Save(uint8*& buf)
{
	WriteSaveBuf(buf, m_nCurrentRouteNode);
	WriteSaveBuf(buf, m_nNextRouteNode);
	WriteSaveBuf(buf, m_nPrevRouteNode);
	WriteSaveBuf(buf, m_nTimeEnteredCurve);
	WriteSaveBuf(buf, m_nTimeToSpendOnCurrentCurve);
	WriteSaveBuf(buf, m_nCurrentPathNodeInfo);
	WriteSaveBuf(buf, m_nNextPathNodeInfo);
	WriteSaveBuf(buf, m_nPreviousPathNodeInfo);
	WriteSaveBuf(buf, m_nAntiReverseTimer);
	WriteSaveBuf(buf, m_nTimeToStartMission);
	WriteSaveBuf(buf, m_nPreviousDirection);
	WriteSaveBuf(buf, m_nCurrentDirection);
	WriteSaveBuf(buf, m_nNextDirection);
	WriteSaveBuf(buf, m_nCurrentLane);
	WriteSaveBuf(buf, m_nNextLane);
	WriteSaveBuf(buf, m_nDrivingStyle);
	WriteSaveBuf(buf, m_nCarMission);
	WriteSaveBuf(buf, m_nTempAction);
	WriteSaveBuf(buf, m_nTimeTempAction);
	WriteSaveBuf(buf, m_fMaxTrafficSpeed);
	WriteSaveBuf(buf, m_nCruiseSpeed);
	WriteSaveBuf(buf, m_nCruiseSpeedMultiplierType);
	ZeroSaveBuf(buf, 2);
	WriteSaveBuf(buf, m_fCruiseSpeedMultiplier);
	uint8 flags = 0;
	if (m_bSlowedDownBecauseOfCars) flags |= BIT(0);
	if (m_bSlowedDownBecauseOfPeds) flags |= BIT(1);
	if (m_bStayInCurrentLevel) flags |= BIT(2);
	if (m_bStayInFastLane) flags |= BIT(3);
	if (m_bIgnorePathfinding) flags |= BIT(4);
	WriteSaveBuf(buf, flags);
	WriteSaveBuf(buf, m_nSwitchDistance);
	ZeroSaveBuf(buf, 2);
	WriteSaveBuf(buf, m_vecDestinationCoors.x);
	WriteSaveBuf(buf, m_vecDestinationCoors.y);
	WriteSaveBuf(buf, m_vecDestinationCoors.z);
	ZeroSaveBuf(buf, 32);
	WriteSaveBuf(buf, m_nPathFindNodesCount);
	ZeroSaveBuf(buf, 6);
}

void CAutoPilot::Load(uint8*& buf)
{
	ReadSaveBuf(&m_nCurrentRouteNode, buf);
	ReadSaveBuf(&m_nNextRouteNode, buf);
	ReadSaveBuf(&m_nPrevRouteNode, buf);
	ReadSaveBuf(&m_nTimeEnteredCurve, buf);
	ReadSaveBuf(&m_nTimeToSpendOnCurrentCurve, buf);
	ReadSaveBuf(&m_nCurrentPathNodeInfo, buf);
	ReadSaveBuf(&m_nNextPathNodeInfo, buf);
	ReadSaveBuf(&m_nPreviousPathNodeInfo, buf);
	ReadSaveBuf(&m_nAntiReverseTimer, buf);
	ReadSaveBuf(&m_nTimeToStartMission, buf);
	ReadSaveBuf(&m_nPreviousDirection, buf);
	ReadSaveBuf(&m_nCurrentDirection, buf);
	ReadSaveBuf(&m_nNextDirection, buf);
	ReadSaveBuf(&m_nCurrentLane, buf);
	ReadSaveBuf(&m_nNextLane, buf);
	ReadSaveBuf(&m_nDrivingStyle, buf);
	ReadSaveBuf(&m_nCarMission, buf);
	ReadSaveBuf(&m_nTempAction, buf);
	ReadSaveBuf(&m_nTimeTempAction, buf);
	ReadSaveBuf(&m_fMaxTrafficSpeed, buf);
	ReadSaveBuf(&m_nCruiseSpeed, buf);
	ReadSaveBuf(&m_nCruiseSpeedMultiplierType, buf);
	SkipSaveBuf(buf, 2);
	ReadSaveBuf(&m_fCruiseSpeedMultiplier, buf);
	uint8 flags;
	ReadSaveBuf(&flags, buf);
	m_bSlowedDownBecauseOfCars = !!(flags & BIT(0));
	m_bSlowedDownBecauseOfPeds = !!(flags & BIT(1));
	m_bStayInCurrentLevel = !!(flags & BIT(2));
	m_bStayInFastLane = !!(flags & BIT(3));
	m_bIgnorePathfinding = !!(flags & BIT(4));
	ReadSaveBuf(&m_nSwitchDistance, buf);
	SkipSaveBuf(buf, 2);
	ReadSaveBuf(&m_vecDestinationCoors.x, buf);
	ReadSaveBuf(&m_vecDestinationCoors.y, buf);
	ReadSaveBuf(&m_vecDestinationCoors.z, buf);
	SkipSaveBuf(buf, 32);
	ReadSaveBuf(&m_nPathFindNodesCount, buf);
	SkipSaveBuf(buf, 6);
}
#endif