#include "common.h"
#include "patcher.h"
#include "Timer.h"

uint32 &CTimer::m_snTimeInMilliseconds = *(uint32*)0x885B48;
uint32 &CTimer::m_snTimeInMillisecondsPauseMode = *(uint32*)0x5F7614;
uint32 &CTimer::m_snTimeInMillisecondsNonClipped = *(uint32*)0x9412E8;
uint32 &CTimer::m_snPreviousTimeInMilliseconds = *(uint32*)0x8F29E4;
uint32 &CTimer::m_FrameCounter = *(uint32*)0x9412EC;
float &CTimer::ms_fTimeScale = *(float*)0x8F2C20;
float &CTimer::ms_fTimeStep = *(float*)0x8E2CB4;
float &CTimer::ms_fTimeStepNonClipped = *(float*)0x8E2C4C;
bool  &CTimer::m_UserPause = *(bool*)0x95CD7C;
bool  &CTimer::m_CodePause = *(bool*)0x95CDB1;
