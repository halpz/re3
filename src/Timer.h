#pragma once

class CTimer
{
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
	static inline void SetTimeStep(float ts) { ms_fTimeStep = ts; }
	static float GetTimeStepNonClipped(void) { return ms_fTimeStepNonClipped; }
	static inline void SetTimeStepNonClipped(float ts) { ms_fTimeStepNonClipped = ts; }
	static uint32 GetFrameCounter(void) { return m_FrameCounter; }
	static inline void SetFrameCounter(uint32 fc) { m_FrameCounter = fc; }
	static uint32 GetTimeInMilliseconds(void) { return m_snTimeInMilliseconds; }
	static inline void SetTimeInMilliseconds(uint32 t) { m_snTimeInMilliseconds = t; }
	static uint32 GetTimeInMillisecondsNonClipped(void) { return m_snTimeInMillisecondsNonClipped; }
	static inline void SetTimeInMillisecondsNonClipped(uint32 t) { m_snTimeInMillisecondsNonClipped = t; }
	static uint32 GetTimeInMillisecondsPauseMode(void) { return m_snTimeInMillisecondsPauseMode; }
	static inline void SetTimeInMillisecondsPauseMode(uint32 t) { m_snTimeInMillisecondsPauseMode = t; }
	static uint32 GetPreviousTimeInMilliseconds(void) { return m_snPreviousTimeInMilliseconds; }
	static inline void SetPreviousTimeInMilliseconds(uint32 t) { m_snPreviousTimeInMilliseconds = t; }
	static float GetTimeScale(void) { return ms_fTimeScale; }
	static inline void SetTimeScale(float ts) { ms_fTimeScale = ts; }
	static inline float GetFrameTimeStepInMilliseconds() { return ms_fTimeStep / 50.0f * 1000.0f; }

	static bool GetIsPaused() { return m_UserPause || m_CodePause; }
	static bool GetIsUserPaused() { return m_UserPause; }
	static void SetCodePause(bool pause) { m_CodePause = pause; }
	
	static void Initialise(void);
	static void Shutdown(void);
	static void Update(void);
	static void Suspend(void);
	static void Resume(void);
	static uint32 GetCyclesPerMillisecond(void);
	static uint32 GetCurrentTimeInCycles(void);
	static bool GetIsSlowMotionActive(void);
	static void Stop(void);
	static void StartUserPause(void);
	static void EndUserPause(void);
};
