#pragma once

class CStats
{
public:
	enum {
		TOTAL_FASTEST_TIMES = 16,
		TOTAL_HIGHEST_SCORES = 16
	};
	static int32 &DaysPassed;
	static int32 &HeadsPopped;
	static bool& CommercialPassed;
	static bool& IndustrialPassed;
	static bool& SuburbanPassed;
	static int32 &NumberKillFrenziesPassed;
	static int32 &PeopleKilledByOthers;
	static int32 &HelisDestroyed;
	static int32 *PedsKilledOfThisType;	//[NUM_PEDTYPES]
	static int32 &TimesDied;
	static int32 &TimesArrested;
	static int32 &KillsSinceLastCheckpoint;
	static int32 &DistanceTravelledInVehicle;
	static int32 &DistanceTravelledOnFoot;
	static int32 &CarsExploded;
	static int32 &PeopleKilledByPlayer;
	static int32 &ProgressMade;
	static int32 &TotalProgressInGame;
	static float &MaximumJumpDistance;
	static float &MaximumJumpHeight;
	static int32 &MaximumJumpFlips;
	static int32 &MaximumJumpSpins;
	static int32 &BestStuntJump;
	static int32 &NumberOfUniqueJumpsFound;
	static int32 &TotalNumberOfUniqueJumps;
	static int32 &PassengersDroppedOffWithTaxi;
	static int32 &MoneyMadeWithTaxi;
	static int32 &MissionsGiven;
	static int32 &MissionsPassed;
	static char (&LastMissionPassedName)[8];
	static int32 &TotalLegitimateKills;
	static int32 &ElBurroTime;
	static int32 &Record4x4One;
	static int32 &Record4x4Two;
	static int32 &Record4x4Three;
	static int32 &Record4x4Mayhem;
	static int32 &LivesSavedWithAmbulance;
	static int32 &CriminalsCaught;
	static int32 &HighestLevelAmbulanceMission;
	static int32 &FiresExtinguished;
	static int32 &LongestFlightInDodo;
	static int32 &TimeTakenDefuseMission;
	static int32 &TotalNumberKillFrenzies;
	static int32 &TotalNumberMissions;
	static int32(&FastestTimes)[TOTAL_FASTEST_TIMES];
	static int32(&HighestScores)[TOTAL_HIGHEST_SCORES];

public:
	static void RegisterFastestTime(int32, int32);
	static void RegisterHighestScore(int32, int32);
	static void AnotherKillFrenzyPassed();
	static void AnotherLifeSavedWithAmbulance();
	static void AnotherCriminalCaught();
	static void RegisterLevelAmbulanceMission(int32);
	static void AnotherFireExtinguished();
	static void Register4x4OneTime(int32);
	static void Register4x4TwoTime(int32);
	static void Register4x4ThreeTime(int32);
	static void Register4x4MayhemTime(int32);
	static void RegisterLongestFlightInDodo(int32);
	static void RegisterTimeTakenDefuseMission(int32);
	static void SetTotalNumberKillFrenzies(int32);
	static void SetTotalNumberMissions(int32);
	static void CheckPointReachedUnsuccessfully() { KillsSinceLastCheckpoint = 0; };
	static void CheckPointReachedSuccessfully() { TotalLegitimateKills += KillsSinceLastCheckpoint; KillsSinceLastCheckpoint = 0; };
	static void RegisterElBurroTime(int32);
};