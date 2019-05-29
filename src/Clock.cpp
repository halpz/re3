#include "common.h"
#include "patcher.h"
#include "Timer.h"
#include "Pad.h"
#include "Clock.h"

uint8  &CClock::ms_nGameClockHours = *(uint8*)0x95CDA6;
uint8  &CClock::ms_nGameClockMinutes = *(uint8*)0x95CDC8;
uint16 &CClock::ms_nGameClockSeconds = *(uint16*)0x95CC7C;
uint8  &CClock::ms_Stored_nGameClockHours = *(uint8*)0x95CD7B;
uint8  &CClock::ms_Stored_nGameClockMinutes = *(uint8*)0x95CD9B;
uint16 &CClock::ms_Stored_nGameClockSeconds = *(uint16*)0x95CC9C;
uint32 &CClock::ms_nMillisecondsPerGameMinute = *(uint32*)0x8F2C64;
int32  &CClock::ms_nLastClockTick = *(int32*)0x9430E4;
bool   &CClock::ms_bClockHasBeenStored = *(bool*)0x95CD82;

void
CClock::Initialise(uint32 scale)
{
	debug("Initialising CClock...\n");
	ms_nGameClockHours = 12;
	ms_nGameClockMinutes = 0;
	ms_nGameClockSeconds = 0;
	ms_nMillisecondsPerGameMinute = scale;
	ms_nLastClockTick = CTimer::GetTimeInMilliseconds();
	ms_bClockHasBeenStored = false;
	debug("CClock ready\n");
}

void
CClock::Update(void)
{
	if(CPad::GetPad(1)->GetRightShoulder1()){
		ms_nGameClockMinutes += 8;
		ms_nLastClockTick = CTimer::GetTimeInMilliseconds();
		if(ms_nGameClockMinutes >= 60){
			ms_nGameClockHours++;
			ms_nGameClockMinutes = 0;
			if(ms_nGameClockHours >= 24)
				ms_nGameClockHours = 0;
		}
	}else
	if(CTimer::GetTimeInMilliseconds() - ms_nLastClockTick >
	   ms_nMillisecondsPerGameMinute){
		ms_nGameClockMinutes++;
		ms_nLastClockTick += ms_nMillisecondsPerGameMinute;
		if(ms_nGameClockMinutes >= 60){
			ms_nGameClockHours++;
			ms_nGameClockMinutes = 0;
			if(ms_nGameClockHours >= 24)
				ms_nGameClockHours = 0;
				// TODO: stats days passed
		}
	}
	ms_nGameClockSeconds +=
			60
			* (CTimer::GetTimeInMilliseconds() - ms_nLastClockTick)
			/ ms_nMillisecondsPerGameMinute;
}

void
CClock::SetGameClock(uint8 h, uint8 m)
{
	ms_nGameClockHours = h;
	ms_nGameClockMinutes = m;
	ms_nGameClockSeconds = 0;
	ms_nLastClockTick = CTimer::GetTimeInMilliseconds();
}

int32
CClock::GetGameClockMinutesUntil(uint8 h, uint8 m)
{
	int32 now, then;
	now = ms_nGameClockHours*60 + ms_nGameClockMinutes;
	then = h*60 + m;
	if(then < now)
		then += 24*60;
	return then-now;
}

bool
CClock::GetIsTimeInRange(uint8 h1, uint8 h2)
{
	if(h1 > h2)
		return ms_nGameClockHours >= h1 || ms_nGameClockHours < h2;
	else
		return ms_nGameClockHours >= h1 && ms_nGameClockHours < h2;
}

void
CClock::StoreClock(void)
{
	ms_Stored_nGameClockHours = ms_nGameClockHours;
	ms_Stored_nGameClockMinutes = ms_nGameClockMinutes;
	ms_Stored_nGameClockSeconds = ms_nGameClockSeconds;
	ms_bClockHasBeenStored = true;
}

void
CClock::RestoreClock(void)
{
	ms_nGameClockHours = ms_Stored_nGameClockHours;
	ms_nGameClockMinutes = ms_Stored_nGameClockMinutes;
	ms_nGameClockSeconds = ms_Stored_nGameClockSeconds;
}


STARTPATCHES
	InjectHook(0x473370, CClock::Initialise, PATCH_JUMP);
	InjectHook(0x473460, CClock::Update, PATCH_JUMP);
	InjectHook(0x4733C0, CClock::SetGameClock, PATCH_JUMP);
	InjectHook(0x4733F0, CClock::GetGameClockMinutesUntil, PATCH_JUMP);
	InjectHook(0x473420, CClock::GetIsTimeInRange, PATCH_JUMP);
	InjectHook(0x473540, CClock::StoreClock, PATCH_JUMP);
	InjectHook(0x473570, CClock::RestoreClock, PATCH_JUMP);
ENDPATCHES
