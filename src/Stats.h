#pragma once

class CStats
{
public:
	static int32 &DaysPassed;
	static int32 &HeadShots;
  static bool& CommercialPassed;
	static int32 &NumberKillFrenziesPassed;
	static int32 &PeopleKilledByOthers;

public:
	static void AnotherKillFrenzyPassed();
};