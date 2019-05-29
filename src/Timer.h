#pragma once

class CTimer
{
public: // remove when each variable will be encapsulated
	static uint32 &m_snTimeInMilliseconds;
	static uint32 &m_snTimeInMillisecondsPauseMode;
	static uint32 &m_snTimeInMillisecondsNonClipped;
	static uint32 &m_snPreviousTimeInMilliseconds;
	static uint32 &m_FrameCounter;
	static float &ms_fTimeScale;
	static float &ms_fTimeStep;
	static float &ms_fTimeStepNonClipped;
	static bool  &m_UserPause;
	static bool  &m_CodePause;
public:
	static float GetTimeStep(void) { return ms_fTimeStep; }
	static void SetTimeStep(float ts) { ms_fTimeStep = ts; }
	static uint32 GetFrameCounter(void) { return m_FrameCounter; }
	static uint32 GetTimeInMilliseconds(void) { return m_snTimeInMilliseconds; }
};
