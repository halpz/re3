#pragma once

class CStats
{
public:
	static int32 &DaysPassed;
	static int32 &HeadShots;
	static int32 &NumberKillFrenziesPassed;
	static int32 &PeopleKilledByOthers;

	static void AnotherKillFrenzyPassed();
};