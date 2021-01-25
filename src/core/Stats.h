#pragma once

#include "PedType.h"
#include "audio_enums.h"

class CStats
{
public:
	enum {
		TOTAL_FASTEST_TIMES = 23,
		TOTAL_HIGHEST_SCORES = 5,
		TOTAL_BEST_POSITIONS = 1,
		TOTAL_PROPERTIES = 15
	};
	static int32 SeagullsKilled;
	static int32 DaysPassed;
	static int32 HeadsPopped;
	static int32 CommercialPassed;
	static int32 IndustrialPassed;
	static int32 SuburbanPassed;
	static int32 NumberKillFrenziesPassed;
	static int32 PeopleKilledByOthers;
	static int32 HelisDestroyed;
	static int32 PedsKilledOfThisType[NUM_PEDTYPES];
	static int32 TimesDied;
	static int32 TimesArrested;
	static int32 KillsSinceLastCheckpoint;
	static float DistanceTravelledByCar;
	static float DistanceTravelledByHelicoptor;
	static float DistanceTravelledByBike;
	static float DistanceTravelledByBoat;
	static float DistanceTravelledByPlane;
	static float DistanceTravelledByGolfCart;
	static float DistanceTravelledOnFoot;
	static int32 FlightTime;
	static int32 TimesDrowned;
	static int32 PhotosTaken;
	static float LoanSharks;
	static float StoresKnockedOff;
	static float MovieStunts;
	static float Assassinations;
	static float PizzasDelivered;
	static float GarbagePickups;
	static float IceCreamSold;
	static float TopShootingRangeScore;
	static float ShootingRank;
	static int32 CarsExploded;
	static int32 BoatsExploded;
	static int32 WantedStarsAttained;
	static int32 WantedStarsEvaded;
	static int32 PeopleKilledByPlayer;
	static float ProgressMade;
	static float TotalProgressInGame;
	static float MaximumJumpDistance;
	static float MaximumJumpHeight;
	static int32 MaximumJumpFlips;
	static int32 MaximumJumpSpins;
	static int32 BestStuntJump;
	static int32 NumberOfUniqueJumpsFound;
	static int32 TotalNumberOfUniqueJumps;
	static int32 PassengersDroppedOffWithTaxi;
	static int32 MoneyMadeWithTaxi;
	static int32 MissionsGiven;
	static int32 MissionsPassed;
	static char  LastMissionPassedName[8];
	static int32 TotalLegitimateKills;
	static int32 LivesSavedWithAmbulance;
	static int32 CriminalsCaught;
	static int32 HighestLevelAmbulanceMission;
	static int32 HighestLevelVigilanteMission;
	static int32 HighestLevelFireMission;
	static int32 FiresExtinguished;
	static int32 TotalNumberKillFrenzies;
	static int32 TotalNumberMissions;
	static int32 RoundsFiredByPlayer;
	static int32 KgsOfExplosivesUsed;
	static int32 BulletsThatHit;
	static int32 BestTimeBombDefusal;
	static int32 FastestTimes[TOTAL_FASTEST_TIMES];
	static int32 HighestScores[TOTAL_HIGHEST_SCORES];
	static int32 BestPositions[TOTAL_BEST_POSITIONS];
	static bool PropertyOwned[TOTAL_PROPERTIES];
	static int32 NumPropertyOwned;
	static int32 PropertyDestroyed;
	static float HighestChaseValue;
	static int32 CheatedCount;
	static int32 ShowChaseStatOnScreen;
	static int32 PamphletMissionPassed;
	static bool abSonyCDs[1];
	static int32 BloodRingKills;
	static int32 BloodRingTime;
	static float FavoriteRadioStationList[NUM_RADIOS];
	static int32 Sprayings;
	static float AutoPaintingBudget;
	static int32 NoMoreHurricanes;
	static float FashionBudget;
	static float PropertyBudget;
	static float WeaponBudget;
	static int32 SafeHouseVisits;
	static int32 TyresPopped;

	static int32 LongestWheelie;
	static int32 LongestStoppie;
	static int32 Longest2Wheel;
	static float LongestWheelieDist;
	static float LongestStoppieDist;
	static float Longest2WheelDist;

public:
	static void Init(void);
	static void RegisterFastestTime(int32, int32);
	static void RegisterHighestScore(int32, int32);
	static void RegisterBestPosition(int32, int32);
	static void AnotherLifeSavedWithAmbulance();
	static void AnotherCriminalCaught();
	static void RegisterLevelAmbulanceMission(int32);
	static void RegisterLevelVigilanteMission(int32);
	static void RegisterLevelFireMission(int32);
	static void AnotherFireExtinguished();
	static wchar *FindCriminalRatingString();
	static wchar *FindChaseString(float fMediaLevel);
	static void AnotherKillFrenzyPassed();
	static void SetTotalNumberKillFrenzies(int32);
	static void SetTotalNumberMissions(int32);
	static void CheckPointReachedSuccessfully() { TotalLegitimateKills += KillsSinceLastCheckpoint; KillsSinceLastCheckpoint = 0; };
	static void CheckPointReachedUnsuccessfully() { KillsSinceLastCheckpoint = 0; };
	static int32 FindCriminalRatingNumber();
	static void SaveStats(uint8 *buf, uint32 *size);
	static void LoadStats(uint8 *buf, uint32 size);
	static float GetPercentageProgress();

	static void MoneySpentOnWeapons(int32);
	static void MoneySpentOnProperty(int32);
	static void MoneySpentOnAutoPainting(int32);
	static void MoneySpentOnFashion(int32);

	static void NumOfVisitsFromLoanSharks(int32);
	static void NumOfStoresKnockedOff(int32);
	static void NumOfMovieStunts(int32);
	static void NumOfAssassinations(int32);
	static void NumOfPizzasDelivered(int32);
	static void NumOfGarbagePickups(int32);
	static void NumOfIceCreamSold(int32);
	static void AddNumBloodRingKills(int32);

	static void LongestTimeInBloodRing(int32);
	static void AddPropertyAsOwned(int32);
	static void PopulateFavoriteRadioStationList();
	static float GetFavoriteRadioStationList(int32);
	static void BuildStatLine(Const char *, void *, int, void *, int);
	static int ConstructStatLine(int);
};
