#include "common.h"
#include "patcher.h"
#include "Curves.h"

WRAPPER float CCurves::CalcSpeedScaleFactor(CVector*, CVector*, float, float, float, float) { EAXJMP(0x420410); }
WRAPPER void CCurves::CalcCurvePoint(CVector*, CVector*, CVector*, CVector*, float, int32, CVector*, CVector*) { EAXJMP(0x4204D0); }
