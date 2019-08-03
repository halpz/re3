#pragma once

class CStats
{
public:
	static int32 &DaysPassed;
	static int32 &HeadShots;
	static bool& CommercialPassed;
	static bool& IndustrialPassed;
	static int32 &NumberKillFrenziesPassed;
	static int32 &PeopleKilledByOthers;
	static int32 &HelisDestroyed;
	static int32 *PedsKilledOfThisType;	//[NUM_PEDTYPES]

public:
	static void AnotherKillFrenzyPassed();
};