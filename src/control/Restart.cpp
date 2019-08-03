#include "common.h"
#include "patcher.h"
#include "Restart.h"

WRAPPER void CRestart::AddHospitalRestartPoint(const CVector&, float) { EAXJMP(0x436100); }
WRAPPER void CRestart::AddPoliceRestartPoint(const CVector&, float) { EAXJMP(0x436150); }
WRAPPER void CRestart::OverrideNextRestart(const CVector&, float) { EAXJMP(0x4366C0); }