#include "common.h"
#include "patcher.h"
#include "main.h"
#include "PedRoutes.h"

WRAPPER int16 CRouteNode::GetRouteThisPointIsOn(int16) { EAXJMP(0x4EE7A0); }
WRAPPER CVector CRouteNode::GetPointPosition(int16) { EAXJMP(0x4EE780); }