#include "common.h"
#include "patcher.h"
#include "DMAudio.h"
#include "Timer.h"
#include "RecordDataForGame.h"
#include "RecordDataForChase.h"
#include <Windows.h>

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

UInt32 oldPcTimer;
UInt32 suspendPcTimer;

UInt32 _nCyclesPerMS = 1;

LARGE_INTEGER _oldPerfCounter;
LARGE_INTEGER perfSuspendCounter;

UInt32 suspendDepth;

_TODO("We need skeleton.c for RsTimer()");

RwUInt32 RsTimer(void)
{
	return ((RwUInt32 (__cdecl *)())0x584890)();
}

void CTimer::Initialise(void)
{
	debug("Initialising CTimer...\n");
	
	ms_fTimeScale = 1.0f;
	ms_fTimeStep = 1.0f;
	suspendDepth = 0;
	m_UserPause = false;
	m_CodePause = false;
	m_snTimeInMillisecondsNonClipped = 0;
	m_snPreviousTimeInMilliseconds = 0;
	m_snTimeInMilliseconds = 1;
	
	LARGE_INTEGER perfFreq;
	if ( QueryPerformanceFrequency(&perfFreq) )
	{
		OutputDebugString("Performance counter available\n");
		_nCyclesPerMS = UInt32(perfFreq.QuadPart / 1000);
		QueryPerformanceCounter(&_oldPerfCounter);
	}
	else
	{
		OutputDebugString("Performance counter not available, using millesecond timer\n");
		_nCyclesPerMS = 0;
		oldPcTimer = RsTimer();
	}
	
	m_snTimeInMilliseconds = m_snPreviousTimeInMilliseconds;
	
	m_FrameCounter = 0;
	
	DMAudio.ResetTimers(m_snPreviousTimeInMilliseconds);
	
	debug("CTimer ready\n");
}

void CTimer::Shutdown(void)
{
	;
}

void CTimer::Update(void)
{
	m_snPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
	
	if ( (Double)_nCyclesPerMS != 0.0 )
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);
		
		Int64 updInCycles = (pc.LowPart - _oldPerfCounter.LowPart) & 0x7FFFFFFF;
		
		_oldPerfCounter = pc;
		
		Double updInCyclesScaled = (Double)updInCycles * ms_fTimeScale;
		
		Double upd = updInCyclesScaled / (Double)_nCyclesPerMS;

		m_snTimeInMillisecondsPauseMode += Int64(upd);
		
		if ( GetIsPaused() )
			ms_fTimeStep = 0.0f;
		else
		{
			m_snTimeInMilliseconds = Int64(upd);
			m_snTimeInMillisecondsNonClipped += Int64(upd);
			ms_fTimeStep = updInCyclesScaled / (Double)_nCyclesPerMS / 20.0;
		}
	}
	else
	{
		UInt32 timer = RsTimer();
		
		UInt32 updInMs = timer - oldPcTimer;
		
		Double upd = (Double)updInMs * ms_fTimeScale;
		
		oldPcTimer = timer;
		
		m_snTimeInMillisecondsPauseMode += Int64(upd);
															 
		if ( GetIsPaused() )
			ms_fTimeStep = 0.0f;
		else
		{
			m_snTimeInMilliseconds += Int64(upd);
			m_snTimeInMillisecondsNonClipped += Int64(upd);
			ms_fTimeStep = upd / 1000.0f * 50.0f;
		}
	}
	
	if ( ms_fTimeStep < 0.01f && !GetIsPaused() )
		ms_fTimeStep = 0.01f;

	ms_fTimeStepNonClipped = ms_fTimeStep;
	
	if ( CRecordDataForGame::RecordingState != _TODOCONST(2) )
	{
		ms_fTimeStep = min(3.0f, ms_fTimeStep);

		if ( (m_snTimeInMilliseconds - m_snPreviousTimeInMilliseconds) > 60 )
			m_snTimeInMilliseconds = m_snPreviousTimeInMilliseconds + 60;
	}
  
	if ( CRecordDataForChase::Status == _TODOCONST(1) )
	{
		ms_fTimeStep = 1.0f;
		m_snTimeInMilliseconds = m_snPreviousTimeInMilliseconds + 16;
	}
  
	m_FrameCounter++;
}

void CTimer::Suspend(void)
{
	if ( ++suspendDepth > 1 )
		return;
	
	if ( (Double)_nCyclesPerMS != 0.0 )
		QueryPerformanceCounter(&perfSuspendCounter);
	else
		suspendPcTimer = RsTimer();
}

void CTimer::Resume(void)
{
	if ( --suspendDepth != 0 )
		return;

	if ( (Double)_nCyclesPerMS != 0.0 )
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);

		_oldPerfCounter.LowPart += pc.LowPart - perfSuspendCounter.LowPart;
	}
	else
		oldPcTimer += RsTimer() - suspendPcTimer;
}

UInt32 CTimer::GetCyclesPerMillisecond(void)
{
	if (_nCyclesPerMS != 0)
		return _nCyclesPerMS;
	else 
		return 1;
}

UInt32 CTimer::GetCurrentTimeInCycles(void)
{
	if ( _nCyclesPerMS != 0 )
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);
		return (pc.LowPart - _oldPerfCounter.LowPart) & 0x7FFFFFFF;
	}
	else
		return RsTimer() - oldPcTimer;
}

Bool CTimer::GetIsSlowMotionActive(void)
{
	return ms_fTimeScale < 1.0f;
}

void CTimer::Stop(void)
{
	m_snPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
}

void CTimer::StartUserPause(void)
{
	m_UserPause = true;
}

void CTimer::EndUserPause(void)
{
	m_UserPause = false;
}

#if 0
STARTPATCHES	
	InjectHook(0x4ACE60, CTimer::Initialise, PATCH_JUMP);
	InjectHook(0x4ACF60, CTimer::Shutdown, PATCH_JUMP);
	InjectHook(0x4ACF70, CTimer::Update, PATCH_JUMP);
	InjectHook(0x4AD310, CTimer::Suspend, PATCH_JUMP);
	InjectHook(0x4AD370, CTimer::Resume, PATCH_JUMP);
	InjectHook(0x4AD3F0, CTimer::GetCyclesPerMillisecond, PATCH_JUMP);
	InjectHook(0x4AD410, CTimer::GetCurrentTimeInCycles, PATCH_JUMP);
	InjectHook(0x4AD450, CTimer::GetIsSlowMotionActive, PATCH_JUMP);
	InjectHook(0x4AD480, CTimer::Stop, PATCH_JUMP);
	InjectHook(0x4AD490, CTimer::StartUserPause, PATCH_JUMP);
	InjectHook(0x4AD4A0, CTimer::EndUserPause, PATCH_JUMP);
ENDPATCHES
#endif

