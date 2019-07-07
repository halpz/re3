#include "common.h"
#include "Stats.h"

int32 &CStats::DaysPassed = *(int32*)0x8F2BB8;
int32 &CStats::HeadShots = *(int32*)0x8F647C;
bool& CStats::CommercialPassed = *(bool*)0x8F4334;
int32 &CStats::NumberKillFrenziesPassed = *(int32*)0x8E287C;
int32 &CStats::PeopleKilledByOthers = *(int32*)0x8E2C50;

void CStats::AnotherKillFrenzyPassed()
{
	++NumberKillFrenziesPassed;
}