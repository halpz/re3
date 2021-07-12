#include "common.h"

#include "Stats.h"
#include "Text.h"
#include "World.h"
#include "Pad.h"
#include "DMAudio.h"
#include "main.h"
#include "Font.h"
#include "Frontend.h"
#include "audio_enums.h"

#include <climits>

#ifdef USE_PRECISE_MEASUREMENT_CONVERTION
#define MILES_IN_METER 0.000621371192f
#define FEET_IN_METER 3.28084f
#else
#define MILES_IN_METER (1 / 1670.f)
#define FEET_IN_METER 3.33f
#endif

int32 CStats::SeagullsKilled;
int32 CStats::BoatsExploded;
int32 CStats::WantedStarsAttained;
int32 CStats::WantedStarsEvaded;
int32 CStats::DaysPassed;
int32 CStats::HeadsPopped;
int32 CStats::CommercialPassed;
int32 CStats::IndustrialPassed;
int32 CStats::SuburbanPassed;
int32 CStats::NumberKillFrenziesPassed;
int32 CStats::PeopleKilledByOthers;
int32 CStats::HelisDestroyed;
int32 CStats::PedsKilledOfThisType[NUM_PEDTYPES];
int32 CStats::TimesDied;
int32 CStats::TimesArrested;
int32 CStats::KillsSinceLastCheckpoint;
float CStats::DistanceTravelledByCar;
float CStats::DistanceTravelledByHelicoptor;
float CStats::DistanceTravelledByBike;
float CStats::DistanceTravelledByBoat;
float CStats::DistanceTravelledByPlane;
float CStats::DistanceTravelledByGolfCart;
float CStats::DistanceTravelledOnFoot;
int32 CStats::FlightTime;
int32 CStats::TimesDrowned;
int32 CStats::PhotosTaken;
float CStats::LoanSharks;
float CStats::StoresKnockedOff;
float CStats::MovieStunts;
float CStats::Assassinations;
float CStats::PizzasDelivered;
float CStats::GarbagePickups;
float CStats::IceCreamSold;
float CStats::TopShootingRangeScore;
float CStats::ShootingRank;
float CStats::ProgressMade;
float CStats::TotalProgressInGame;
int32 CStats::CarsExploded;
int32 CStats::PeopleKilledByPlayer;
float CStats::MaximumJumpDistance;
float CStats::MaximumJumpHeight;
int32 CStats::MaximumJumpFlips;
int32 CStats::MaximumJumpSpins;
int32 CStats::BestStuntJump;
int32 CStats::NumberOfUniqueJumpsFound;
int32 CStats::TotalNumberOfUniqueJumps;
int32 CStats::PassengersDroppedOffWithTaxi;
int32 CStats::MoneyMadeWithTaxi;
int32 CStats::MissionsGiven;
int32 CStats::MissionsPassed;
char CStats::LastMissionPassedName[8];
int32 CStats::TotalLegitimateKills;
int32 CStats::LivesSavedWithAmbulance;
int32 CStats::CriminalsCaught;
int32 CStats::HighestLevelAmbulanceMission;
int32 CStats::HighestLevelVigilanteMission;
int32 CStats::HighestLevelFireMission;
int32 CStats::FiresExtinguished;
int32 CStats::TotalNumberKillFrenzies;
int32 CStats::TotalNumberMissions;
int32 CStats::RoundsFiredByPlayer;
int32 CStats::KgsOfExplosivesUsed;
int32 CStats::BulletsThatHit;
int32 CStats::BestTimeBombDefusal;
int32 CStats::FastestTimes[CStats::TOTAL_FASTEST_TIMES];
int32 CStats::HighestScores[CStats::TOTAL_HIGHEST_SCORES];
int32 CStats::BestPositions[CStats::TOTAL_BEST_POSITIONS];
bool CStats::PropertyOwned[CStats::TOTAL_PROPERTIES];
int32 CStats::NumPropertyOwned;
int32 CStats::PropertyDestroyed;
float CStats::HighestChaseValue;
int32 CStats::CheatedCount;
int32 CStats::ShowChaseStatOnScreen;
int32 CStats::PamphletMissionPassed;
bool CStats::abSonyCDs[1];
int32 CStats::BloodRingKills;
int32 CStats::BloodRingTime;
float CStats::FavoriteRadioStationList[NUM_RADIOS];

int32 CStats::Sprayings;
float CStats::AutoPaintingBudget;
int32 CStats::NoMoreHurricanes;
float CStats::FashionBudget;
float CStats::PropertyBudget;
float CStats::WeaponBudget;
int32 CStats::SafeHouseVisits;
int32 CStats::TyresPopped;

int32 CStats::LongestWheelie;
int32 CStats::LongestStoppie;
int32 CStats::Longest2Wheel;
float CStats::LongestWheelieDist;
float CStats::LongestStoppieDist;
float CStats::Longest2WheelDist;

void CStats::Init()
{
	PeopleKilledByOthers = 0;
	PeopleKilledByPlayer = 0;
	CarsExploded = 0;
	BoatsExploded = 0;
	RoundsFiredByPlayer = 0;
	for (int i = 0; i < NUM_PEDTYPES; i++)
		PedsKilledOfThisType[i] = 0;
	HelisDestroyed = 0;
	ProgressMade = 0.0f;
	KgsOfExplosivesUsed = 0;
	BulletsThatHit = 0;
	TyresPopped = 0;
	HeadsPopped = 0;
	WantedStarsAttained = 0;
	WantedStarsEvaded = 0;
	TimesArrested = 0;
	TimesDied = 0;
	DaysPassed = 0;
	SafeHouseVisits = 0;
	Sprayings = 0;
	MaximumJumpDistance = 0;
	MaximumJumpHeight = 0;
	MaximumJumpFlips = 0;
	MaximumJumpSpins = 0;
	BestStuntJump = 0;
	NumberOfUniqueJumpsFound = 0;
	TotalNumberOfUniqueJumps = 0;
	MissionsGiven = 0;
	MissionsPassed = 0;
	PassengersDroppedOffWithTaxi = 0;
	MoneyMadeWithTaxi = 0;
	DistanceTravelledOnFoot = 0;
	DistanceTravelledByCar = 0;
	DistanceTravelledByBike = 0;
	DistanceTravelledByBoat = 0;
	DistanceTravelledByGolfCart = 0;
	DistanceTravelledByHelicoptor = 0;
#ifdef FIX_BUGS
	DistanceTravelledByPlane = 0;
#endif
	LivesSavedWithAmbulance = 0;
	CriminalsCaught = 0;
	HighestLevelVigilanteMission = 0;
	HighestLevelAmbulanceMission = 0;
	HighestLevelFireMission = 0;
	FiresExtinguished = 0;
	PhotosTaken = 0;
	NumberKillFrenziesPassed = 0;
	TotalNumberKillFrenzies = 0;
	TotalNumberMissions = 0;
	FlightTime = 0;
	TimesDrowned = 0;
	SeagullsKilled = 0;
	WeaponBudget = 0.0f;
	FashionBudget = 0.0f;
	LoanSharks = 0.0f;
	StoresKnockedOff = 0.0f;
	MovieStunts = 0.0f;
	Assassinations = 0.0f;
	PizzasDelivered = 0.0f;
	GarbagePickups = 0.0f;
	IceCreamSold = 0.0f;
	TopShootingRangeScore = 0.0f;
	ShootingRank = 0.0f;
	LongestWheelie = 0;
	LongestStoppie = 0;
	Longest2Wheel = 0;
	LongestWheelieDist = 0.0f;
	LongestStoppieDist = 0.0f;
	Longest2WheelDist = 0.0f;
	PropertyBudget = 0.0f;
	AutoPaintingBudget = 0.0f;
	PropertyDestroyed = 0;
	HighestChaseValue = 0.0f;
	CheatedCount = 0;

	for (int i = 0; i < TOTAL_FASTEST_TIMES; i++)
		FastestTimes[i] = 0;
	for (int i = 0; i < TOTAL_HIGHEST_SCORES; i++)
		HighestScores[i] = 0;
	for (int i = 0; i < TOTAL_BEST_POSITIONS; i++)
		BestPositions[i] = INT_MAX;

	KillsSinceLastCheckpoint = 0;
	TotalLegitimateKills = 0;

	for (int i = 0; i < ARRAY_SIZE(LastMissionPassedName); i++)
		LastMissionPassedName[i] = 0;

	IndustrialPassed = 0;
	CommercialPassed = 0;
	SuburbanPassed = 0;
	PamphletMissionPassed = 0;
	NoMoreHurricanes = 0;
	ShowChaseStatOnScreen = 0;
	for (int i = 0; i < ARRAY_SIZE(abSonyCDs); i++)
		abSonyCDs[i] = 0;
	PopulateFavoriteRadioStationList();

	NumPropertyOwned = 0;
	for (int i = 0; i < TOTAL_PROPERTIES; i++)
		PropertyOwned[i] = false;

	BloodRingKills = 0;
	BloodRingTime = 0;
}

void CStats::RegisterFastestTime(int32 index, int32 time)
{
	assert(index >= 0 && index < TOTAL_FASTEST_TIMES);
	if (FastestTimes[index] == 0)
		FastestTimes[index] = time;
	else
		FastestTimes[index] = Min(FastestTimes[index], time);
}

void CStats::RegisterHighestScore(int32 index, int32 score)
{
	assert(index >= 0 && index < TOTAL_HIGHEST_SCORES);
	HighestScores[index] = Max(HighestScores[index], score);
}

void CStats::RegisterBestPosition(int32 index, int32 position)
{
	assert(index >= 0 && index < TOTAL_BEST_POSITIONS);
	BestPositions[index] = Min(BestPositions[index], position);
}

void CStats::AnotherLifeSavedWithAmbulance()
{
	++LivesSavedWithAmbulance;
}

void CStats::AnotherCriminalCaught()
{
	++CriminalsCaught;
}

void CStats::RegisterLevelAmbulanceMission(int32 level)
{
	HighestLevelAmbulanceMission = Max(HighestLevelAmbulanceMission, level);
}

void CStats::RegisterLevelVigilanteMission(int32 level)
{
	HighestLevelVigilanteMission = Max(HighestLevelVigilanteMission, level);
}

void CStats::RegisterLevelFireMission(int32 level)
{
	HighestLevelFireMission = Max(HighestLevelFireMission, level);
}

void CStats::AnotherFireExtinguished()
{
	++FiresExtinguished;
}

void CStats::AnotherKillFrenzyPassed()
{
	++NumberKillFrenziesPassed;
}

void CStats::SetTotalNumberKillFrenzies(int32 total)
{
	TotalNumberKillFrenzies = total;
}

void CStats::SetTotalNumberMissions(int32 total)
{
	TotalNumberMissions = total;
}

wchar *CStats::FindCriminalRatingString()
{
	int rating = FindCriminalRatingNumber();

	if (rating < 0) {
		if (rating > -500) return TheText.Get("RATNG53");
		if (rating > -2000) return TheText.Get("RATNG54");
		if (rating > -4000) return TheText.Get("RATNG55");
		if (rating > -6000) return TheText.Get("RATNG56");
		return TheText.Get("RATNG57");
	}
	if (rating < 20) return TheText.Get("RATNG1");
	if (rating < 50) return TheText.Get("RATNG2");
	if (rating < 75) return TheText.Get("RATNG3");
	if (rating < 100) return TheText.Get("RATNG4");
	if (rating < 120) return TheText.Get("RATNG5");
	if (rating < 150) return TheText.Get("RATNG6");
	if (rating < 200) return TheText.Get("RATNG7");
	if (rating < 240) return TheText.Get("RATNG8");
	if (rating < 270) return TheText.Get("RATNG9");
	if (rating < 300) return TheText.Get("RATNG10");
	if (rating < 335) return TheText.Get("RATNG11");
	if (rating < 370) return TheText.Get("RATNG12");
	if (rating < 400) return TheText.Get("RATNG13");
	if (rating < 450) return TheText.Get("RATNG14");
	if (rating < 500) return TheText.Get("RATNG15");
	if (rating < 550) return TheText.Get("RATNG16");
	if (rating < 600) return TheText.Get("RATNG17");
	if (rating < 610) return TheText.Get("RATNG18");
	if (rating < 650) return TheText.Get("RATNG19");
	if (rating < 700) return TheText.Get("RATNG20");
	if (rating < 850) return TheText.Get("RATNG21");
	if (rating < 1000) return TheText.Get("RATNG22");
	if (rating < 1005) return TheText.Get("RATNG23");
	if (rating < 1150) return TheText.Get("RATNG24");
	if (rating < 1300) return TheText.Get(TimesArrested > 0 ? "RATNG25" : "RATNG24");
	if (rating < 1500) return TheText.Get("RATNG26");
	if (rating < 1700) return TheText.Get("RATNG27");
	if (rating < 2000) return TheText.Get("RATNG28");
	if (rating < 2100) return TheText.Get("RATNG29");
	if (rating < 2300) return TheText.Get("RATNG30");
	if (rating < 2500) return TheText.Get("RATNG31");
	if (rating < 2750) return TheText.Get("RATNG32");
	if (rating < 3000) return TheText.Get("RATNG33");
	if (rating < 3500) return TheText.Get("RATNG34");
	if (rating < 4000) return TheText.Get("RATNG35");
	if (rating < 5000) return TheText.Get("RATNG36");
	if (rating < 7500) return TheText.Get("RATNG37");
	if (rating < 10000) return TheText.Get("RATNG38");
	if (rating < 20000) return TheText.Get("RATNG39");
	if (rating < 30000) return TheText.Get("RATNG40");
	if (rating < 40000) return TheText.Get("RATNG41");
	if (rating < 50000) return TheText.Get("RATNG42");
	if (rating < 65000) return TheText.Get("RATNG43");
	if (rating < 80000) return TheText.Get("RATNG44");
	if (rating < 100000) return TheText.Get("RATNG45");
	if (rating < 150000) return TheText.Get("RATNG46");
	if (rating < 200000) return TheText.Get("RATNG47");
	if (rating < 300000) return TheText.Get("RATNG48");
	if (rating < 375000) return TheText.Get("RATNG49");
	if (rating < 500000) return TheText.Get(FlightTime / 60000 / 60 > 10 ? "RATNG50" : "RATNG49");
	if (rating < 1000000) return TheText.Get("RATNG51");
	return TheText.Get(CWorld::Players[CWorld::PlayerInFocus].m_nVisibleMoney > 10000000 ? "RATNG52" : "RATNG51");
}

wchar *CStats::FindChaseString(float fMediaLevel) {
	if (fMediaLevel < 20.0f) return TheText.Get("CHASE1");
	if (fMediaLevel < 50.0f) return TheText.Get("CHASE2");
	if (fMediaLevel < 75.0f) return TheText.Get("CHASE3");
	if (fMediaLevel < 100.0f) return TheText.Get("CHASE4");
	if (fMediaLevel < 150.0f) return TheText.Get("CHASE5");
	if (fMediaLevel < 200.0f) return TheText.Get("CHASE6");
	if (fMediaLevel < 250.0f) return TheText.Get("CHASE7");
	if (fMediaLevel < 300.0f) return TheText.Get("CHASE8");
	if (fMediaLevel < 350.0f) return TheText.Get("CHASE9");
	if (fMediaLevel < 400.0f) return TheText.Get("CHASE10");
	if (fMediaLevel < 500.0f) return TheText.Get("CHASE11");
	if (fMediaLevel < 600.0f) return TheText.Get("CHASE12");
	if (fMediaLevel < 700.0f) return TheText.Get("CHASE13");
	if (fMediaLevel < 800.0f) return TheText.Get("CHASE14");
	if (fMediaLevel < 900.0f) return TheText.Get("CHASE15");
	if (fMediaLevel < 1000.0f) return TheText.Get("CHASE16");
	if (fMediaLevel < 1200.0f) return TheText.Get("CHASE17");
	if (fMediaLevel < 1400.0f) return TheText.Get("CHASE18");
	if (fMediaLevel < 1600.0f) return TheText.Get("CHASE19");
	if (fMediaLevel < 1800.0f) return TheText.Get("CHASE20");
	return TheText.Get("CHASE21");
}

int32 CStats::FindCriminalRatingNumber()
{
	int32 rating;

	rating = FiresExtinguished + 10 * HighestLevelFireMission + 10 * HighestLevelAmbulanceMission
		+ CriminalsCaught + LivesSavedWithAmbulance
		+ 30 * HelisDestroyed + TotalLegitimateKills - 3 * TimesArrested - 3 * TimesDied
		+ CWorld::Players[CWorld::PlayerInFocus].m_nMoney / 5000;
	if (CPad::bHasPlayerCheated || CheatedCount > 0) {
		rating -= CheatedCount;
		if (rating <= -10000)
			rating = -10000;

	} else if (rating <= 0) {
		rating = 0;
	}

	if (RoundsFiredByPlayer > 100)
		rating += (float)BulletsThatHit / (float)RoundsFiredByPlayer * 500.0f;
	if (TotalProgressInGame)
		rating += ProgressMade / TotalProgressInGame * 1000.0f;
	return rating;
}

float CStats::GetPercentageProgress()
{
	float percentCompleted = (TotalProgressInGame == 0.f ? 0.f :
		100.0f * ProgressMade / (CGame::nastyGame ? TotalProgressInGame : TotalProgressInGame - 1.0f));

	return Min(percentCompleted, 100.0f);
}

void CStats::MoneySpentOnWeapons(int32 money)
{
	WeaponBudget += money;
}

void CStats::MoneySpentOnProperty(int32 money)
{
	PropertyBudget += money;
}

void CStats::MoneySpentOnAutoPainting(int32 money)
{
	AutoPaintingBudget += money;
}

void CStats::MoneySpentOnFashion(int32 money)
{
	FashionBudget += money;
}

void CStats::NumOfVisitsFromLoanSharks(int32 num)
{
	LoanSharks += num;
}

void CStats::NumOfStoresKnockedOff(int32 num)
{
	StoresKnockedOff += num;
}

void CStats::NumOfMovieStunts(int32 num)
{
	MovieStunts += num;
}

void CStats::NumOfAssassinations(int32 num)
{
	Assassinations += num;
}

void CStats::NumOfPizzasDelivered(int32 num)
{
	PizzasDelivered += num;
}

void CStats::NumOfGarbagePickups(int32 num)
{
	GarbagePickups += num;
}

void CStats::NumOfIceCreamSold(int32 num)
{
	IceCreamSold += num;
}

void CStats::AddNumBloodRingKills(int32 num)
{
	BloodRingKills += num;
}

void CStats::LongestTimeInBloodRing(int32 time)
{
	if (BloodRingTime < time)
		BloodRingTime = time;
}

void CStats::AddPropertyAsOwned(int32 id)
{
	if (!PropertyOwned[id]) {
		PropertyOwned[id] = true;
		++NumPropertyOwned;
	}
}

float CStats::GetFavoriteRadioStationList(int32 station)
{
	return FavoriteRadioStationList[station];
}

void CStats::SaveStats(uint8 *buf, uint32 *size)
{
	CheckPointReachedSuccessfully();
	uint8 *buf_start = buf;
	*size = sizeof(PeopleKilledByPlayer) +
		sizeof(PeopleKilledByOthers) +
		sizeof(CarsExploded) +
		sizeof(BoatsExploded) +
		sizeof(TyresPopped) +
		sizeof(RoundsFiredByPlayer) +
		sizeof(PedsKilledOfThisType) +
		sizeof(HelisDestroyed) +
		sizeof(ProgressMade) +
		sizeof(TotalProgressInGame) +
		sizeof(KgsOfExplosivesUsed) +
		sizeof(BulletsThatHit) +
		sizeof(HeadsPopped) +
		sizeof(WantedStarsAttained) +
		sizeof(WantedStarsEvaded) +
		sizeof(TimesArrested) +
		sizeof(TimesDied) +
		sizeof(DaysPassed) +
		sizeof(SafeHouseVisits) +
		sizeof(Sprayings) +
		sizeof(MaximumJumpDistance) +
		sizeof(MaximumJumpHeight) +
		sizeof(MaximumJumpFlips) +
		sizeof(MaximumJumpSpins) +
		sizeof(BestStuntJump) +
		sizeof(NumberOfUniqueJumpsFound) +
		sizeof(TotalNumberOfUniqueJumps) +
		sizeof(MissionsGiven) +
		sizeof(PassengersDroppedOffWithTaxi) +
		sizeof(MoneyMadeWithTaxi) +
		sizeof(IndustrialPassed) +
		sizeof(CommercialPassed) +
		sizeof(SuburbanPassed) +
		sizeof(PamphletMissionPassed) +
		sizeof(NoMoreHurricanes) +
		sizeof(DistanceTravelledOnFoot) +
		sizeof(DistanceTravelledByCar) +
		sizeof(DistanceTravelledByBike) +
		sizeof(DistanceTravelledByBoat) +
		sizeof(DistanceTravelledByGolfCart) +
		sizeof(DistanceTravelledByHelicoptor) +
		sizeof(DistanceTravelledByPlane) +
		sizeof(LivesSavedWithAmbulance) +
		sizeof(CriminalsCaught) +
		sizeof(FiresExtinguished) +
		sizeof(HighestLevelVigilanteMission) +
		sizeof(HighestLevelAmbulanceMission) +
		sizeof(HighestLevelFireMission) +
		sizeof(PhotosTaken) +
		sizeof(NumberKillFrenziesPassed) +
		sizeof(TotalNumberKillFrenzies) +
		sizeof(TotalNumberMissions) +
		sizeof(FlightTime) +
		sizeof(TimesDrowned) +
		sizeof(SeagullsKilled) +
		sizeof(WeaponBudget) +
		sizeof(FashionBudget) +
		sizeof(LoanSharks) +
		sizeof(StoresKnockedOff) +
		sizeof(MovieStunts) +
		sizeof(Assassinations) +
		sizeof(PizzasDelivered) +
		sizeof(GarbagePickups) +
		sizeof(IceCreamSold) +
		sizeof(TopShootingRangeScore) +
		sizeof(ShootingRank) +
		sizeof(LongestWheelie) +
		sizeof(LongestStoppie) +
		sizeof(Longest2Wheel) +
		sizeof(LongestWheelieDist) +
		sizeof(LongestStoppieDist) +
		sizeof(Longest2WheelDist) +
		sizeof(PropertyBudget) +
		sizeof(AutoPaintingBudget) +
		sizeof(PropertyDestroyed) +
		sizeof(NumPropertyOwned) +
		sizeof(BloodRingKills) +
		sizeof(BloodRingTime) +
		sizeof(PropertyOwned) +
		sizeof(HighestChaseValue) +
		sizeof(FastestTimes) +
		sizeof(HighestScores) +
		sizeof(BestPositions) +
		sizeof(KillsSinceLastCheckpoint) +
		sizeof(TotalLegitimateKills) +
		sizeof(LastMissionPassedName) +
		sizeof(CheatedCount) +
		sizeof(FavoriteRadioStationList);

#define CopyToBuf(buf, data) memcpy(buf, &data, sizeof(data)); buf += sizeof(data);
	CopyToBuf(buf, PeopleKilledByPlayer);
	CopyToBuf(buf, PeopleKilledByOthers);
	CopyToBuf(buf, CarsExploded);
	CopyToBuf(buf, BoatsExploded);
	CopyToBuf(buf, TyresPopped);
	CopyToBuf(buf, RoundsFiredByPlayer);
	CopyToBuf(buf, PedsKilledOfThisType);
	CopyToBuf(buf, HelisDestroyed);
	CopyToBuf(buf, ProgressMade);
	CopyToBuf(buf, TotalProgressInGame);
	CopyToBuf(buf, KgsOfExplosivesUsed);
	CopyToBuf(buf, BulletsThatHit);
	CopyToBuf(buf, HeadsPopped);
	CopyToBuf(buf, WantedStarsAttained);
	CopyToBuf(buf, WantedStarsEvaded);
	CopyToBuf(buf, TimesArrested);
	CopyToBuf(buf, TimesDied);
	CopyToBuf(buf, DaysPassed);
	CopyToBuf(buf, SafeHouseVisits);
	CopyToBuf(buf, Sprayings);
	CopyToBuf(buf, MaximumJumpDistance);
	CopyToBuf(buf, MaximumJumpHeight);
	CopyToBuf(buf, MaximumJumpFlips);
	CopyToBuf(buf, MaximumJumpSpins);
	CopyToBuf(buf, BestStuntJump);
	CopyToBuf(buf, NumberOfUniqueJumpsFound);
	CopyToBuf(buf, TotalNumberOfUniqueJumps);
	CopyToBuf(buf, MissionsGiven);
	CopyToBuf(buf, PassengersDroppedOffWithTaxi);
	CopyToBuf(buf, MoneyMadeWithTaxi);
	CopyToBuf(buf, IndustrialPassed);
	CopyToBuf(buf, CommercialPassed);
	CopyToBuf(buf, SuburbanPassed);
	CopyToBuf(buf, PamphletMissionPassed);
	CopyToBuf(buf, NoMoreHurricanes);
	CopyToBuf(buf, DistanceTravelledOnFoot);
	CopyToBuf(buf, DistanceTravelledByCar);
	CopyToBuf(buf, DistanceTravelledByBike);
	CopyToBuf(buf, DistanceTravelledByBoat);
	CopyToBuf(buf, DistanceTravelledByGolfCart);
	CopyToBuf(buf, DistanceTravelledByHelicoptor);
	CopyToBuf(buf, DistanceTravelledByPlane);
	CopyToBuf(buf, LivesSavedWithAmbulance);
	CopyToBuf(buf, CriminalsCaught);
	CopyToBuf(buf, FiresExtinguished);
	CopyToBuf(buf, HighestLevelVigilanteMission);
	CopyToBuf(buf, HighestLevelAmbulanceMission);
	CopyToBuf(buf, HighestLevelFireMission);
	CopyToBuf(buf, PhotosTaken);
	CopyToBuf(buf, NumberKillFrenziesPassed);
	CopyToBuf(buf, TotalNumberKillFrenzies);
	CopyToBuf(buf, TotalNumberMissions);
	CopyToBuf(buf, FlightTime);
	CopyToBuf(buf, TimesDrowned);
	CopyToBuf(buf, SeagullsKilled);
	CopyToBuf(buf, WeaponBudget);
	CopyToBuf(buf, FashionBudget);
	CopyToBuf(buf, LoanSharks);
	CopyToBuf(buf, StoresKnockedOff);
	CopyToBuf(buf, MovieStunts);
	CopyToBuf(buf, Assassinations);
	CopyToBuf(buf, PizzasDelivered);
	CopyToBuf(buf, GarbagePickups);
	CopyToBuf(buf, IceCreamSold);
	CopyToBuf(buf, TopShootingRangeScore);
	CopyToBuf(buf, ShootingRank);
	CopyToBuf(buf, LongestWheelie);
	CopyToBuf(buf, LongestStoppie);
	CopyToBuf(buf, Longest2Wheel);
	CopyToBuf(buf, LongestWheelieDist);
	CopyToBuf(buf, LongestStoppieDist);
	CopyToBuf(buf, Longest2WheelDist);
	CopyToBuf(buf, PropertyBudget);
	CopyToBuf(buf, AutoPaintingBudget);
	CopyToBuf(buf, PropertyDestroyed);
	CopyToBuf(buf, NumPropertyOwned);
	CopyToBuf(buf, BloodRingKills);
	CopyToBuf(buf, BloodRingTime);
	CopyToBuf(buf, PropertyOwned);
	CopyToBuf(buf, HighestChaseValue);
	CopyToBuf(buf, FastestTimes);
	CopyToBuf(buf, HighestScores);
	CopyToBuf(buf, BestPositions);
	CopyToBuf(buf, KillsSinceLastCheckpoint);
	CopyToBuf(buf, TotalLegitimateKills);
	CopyToBuf(buf, LastMissionPassedName);
	CopyToBuf(buf, CheatedCount);
	PopulateFavoriteRadioStationList();
	CopyToBuf(buf, FavoriteRadioStationList);

	assert(buf - buf_start == *size);
#undef CopyToBuf
}

void CStats::LoadStats(uint8 *buf, uint32 size)
{
	uint8* buf_start = buf;

#define CopyFromBuf(buf, data) memcpy(&data, buf, sizeof(data)); buf += sizeof(data);

	CopyFromBuf(buf, PeopleKilledByPlayer);
	CopyFromBuf(buf, PeopleKilledByOthers);
	CopyFromBuf(buf, CarsExploded);
	CopyFromBuf(buf, BoatsExploded);
	CopyFromBuf(buf, TyresPopped);
	CopyFromBuf(buf, RoundsFiredByPlayer);
	CopyFromBuf(buf, PedsKilledOfThisType);
	CopyFromBuf(buf, HelisDestroyed);
	CopyFromBuf(buf, ProgressMade);
	CopyFromBuf(buf, TotalProgressInGame);
	CopyFromBuf(buf, KgsOfExplosivesUsed);
	CopyFromBuf(buf, BulletsThatHit);
	CopyFromBuf(buf, HeadsPopped);
	CopyFromBuf(buf, WantedStarsAttained);
	CopyFromBuf(buf, WantedStarsEvaded);
	CopyFromBuf(buf, TimesArrested);
	CopyFromBuf(buf, TimesDied);
	CopyFromBuf(buf, DaysPassed);
	CopyFromBuf(buf, SafeHouseVisits);
	CopyFromBuf(buf, Sprayings);
	CopyFromBuf(buf, MaximumJumpDistance);
	CopyFromBuf(buf, MaximumJumpHeight);
	CopyFromBuf(buf, MaximumJumpFlips);
	CopyFromBuf(buf, MaximumJumpSpins);
	CopyFromBuf(buf, BestStuntJump);
	CopyFromBuf(buf, NumberOfUniqueJumpsFound);
	CopyFromBuf(buf, TotalNumberOfUniqueJumps);
	CopyFromBuf(buf, MissionsGiven);
	CopyFromBuf(buf, PassengersDroppedOffWithTaxi);
	CopyFromBuf(buf, MoneyMadeWithTaxi);
	CopyFromBuf(buf, IndustrialPassed);
	CopyFromBuf(buf, CommercialPassed);
	CopyFromBuf(buf, SuburbanPassed);
	CopyFromBuf(buf, PamphletMissionPassed);
	CopyFromBuf(buf, NoMoreHurricanes);
	CopyFromBuf(buf, DistanceTravelledOnFoot);
	CopyFromBuf(buf, DistanceTravelledByCar);
	CopyFromBuf(buf, DistanceTravelledByBike);
	CopyFromBuf(buf, DistanceTravelledByBoat);
	CopyFromBuf(buf, DistanceTravelledByGolfCart);
	CopyFromBuf(buf, DistanceTravelledByHelicoptor);
	CopyFromBuf(buf, DistanceTravelledByPlane);
	CopyFromBuf(buf, LivesSavedWithAmbulance);
	CopyFromBuf(buf, CriminalsCaught);
	CopyFromBuf(buf, FiresExtinguished);
	CopyFromBuf(buf, HighestLevelVigilanteMission);
	CopyFromBuf(buf, HighestLevelAmbulanceMission);
	CopyFromBuf(buf, HighestLevelFireMission);
	CopyFromBuf(buf, PhotosTaken);
	CopyFromBuf(buf, NumberKillFrenziesPassed);
	CopyFromBuf(buf, TotalNumberKillFrenzies);
	CopyFromBuf(buf, TotalNumberMissions);
	CopyFromBuf(buf, FlightTime);
	CopyFromBuf(buf, TimesDrowned);
	CopyFromBuf(buf, SeagullsKilled);
	CopyFromBuf(buf, WeaponBudget);
	CopyFromBuf(buf, FashionBudget);
	CopyFromBuf(buf, LoanSharks);
	CopyFromBuf(buf, StoresKnockedOff);
	CopyFromBuf(buf, MovieStunts);
	CopyFromBuf(buf, Assassinations);
	CopyFromBuf(buf, PizzasDelivered);
	CopyFromBuf(buf, GarbagePickups);
	CopyFromBuf(buf, IceCreamSold);
	CopyFromBuf(buf, TopShootingRangeScore);
	CopyFromBuf(buf, ShootingRank);
	CopyFromBuf(buf, LongestWheelie);
	CopyFromBuf(buf, LongestStoppie);
	CopyFromBuf(buf, Longest2Wheel);
	CopyFromBuf(buf, LongestWheelieDist);
	CopyFromBuf(buf, LongestStoppieDist);
	CopyFromBuf(buf, Longest2WheelDist);
	CopyFromBuf(buf, PropertyBudget);
	CopyFromBuf(buf, AutoPaintingBudget);
	CopyFromBuf(buf, PropertyDestroyed);
	CopyFromBuf(buf, NumPropertyOwned);
	CopyFromBuf(buf, BloodRingKills);
	CopyFromBuf(buf, BloodRingTime);
	CopyFromBuf(buf, PropertyOwned);
	CopyFromBuf(buf, HighestChaseValue);
	CopyFromBuf(buf, FastestTimes);
	CopyFromBuf(buf, HighestScores);
	CopyFromBuf(buf, BestPositions);
	CopyFromBuf(buf, KillsSinceLastCheckpoint);
	CopyFromBuf(buf, TotalLegitimateKills);
	CopyFromBuf(buf, LastMissionPassedName);
	CopyFromBuf(buf, CheatedCount);
	CopyFromBuf(buf, FavoriteRadioStationList);

	assert(buf - buf_start == size);
#undef CopyFromBuf
}

void
CStats::PopulateFavoriteRadioStationList()
{
	float* pListenTimeArray = DMAudio.GetListenTimeArray();
	for (int i = 0; i < NUM_RADIOS; i++)
		FavoriteRadioStationList[i] = pListenTimeArray[i];
}

void
CStats::BuildStatLine(Const char *text, void *stat, int displayType, void *stat2, int isTime)
{
#define STAT_D *(int*)stat
#define STAT_F *(float*)stat
#define STAT2_D *(int*)stat2
#define STAT2_F *(float*)stat2
	if (!text)
		return;

	gString2[0] = '\0';
	if (isTime == 1) {
		if (*((int*)stat2) >= 10)
			sprintf(gString2, " %d:%d", STAT_D, STAT2_D);
		else
			sprintf(gString2, " %d:0%d", STAT_D, STAT2_D);

	} else if (stat2) {
#ifdef MORE_LANGUAGES
		if (CFont::IsJapanese()) {
			switch (displayType) {
				case 0:
				case 4:
				sprintf(gString2, "  %d/%d", STAT_D, STAT2_D);
				break;
				case 1:
				sprintf(gString2, "  %.2f/%.2f", STAT_F, STAT2_F);
				break;
				case 2:
				sprintf(gString2, "  %d%%/%d%%", STAT_D, STAT2_D);
				break;
				case 3:
				sprintf(gString2, "  $%.2f/$%.2f", STAT_F, STAT2_F);
				break;
				default:
				break;
			}
		} else
#endif
		{
			switch (displayType) {
				case 0:
				sprintf(gString2, "  %d %s %d", STAT_D, UnicodeToAscii(TheText.Get("FEST_OO")), STAT2_D);
				break;
				case 1:
				sprintf(gString2, "  %.2f %s %.2f", STAT_F, UnicodeToAscii(TheText.Get("FEST_OO")), STAT2_F);
				break;
				case 2:
				sprintf(gString2, "  %d%% %s %d%%", STAT_D, UnicodeToAscii(TheText.Get("FEST_OO")), STAT2_D);
				break;
				case 3:
				sprintf(gString2, "  $%.2f %s $%.2f", STAT_F, UnicodeToAscii(TheText.Get("FEST_OO")), STAT2_F);
				break;
				case 4:
				sprintf(gString2, "  %d_ %s %d_", STAT_D, UnicodeToAscii(TheText.Get("FEST_OO")), STAT2_D);
				break;
				default:
				break;
			}
		}
	} else if (stat) {
		switch (displayType) {
			case 0:
			sprintf(gString2, "%d", STAT_D);
			break;
			case 1:
			sprintf(gString2, "%.2f", STAT_F);
			break;
			case 2:
			sprintf(gString2, "%d%%", STAT_D);
			break;
			case 3:
			sprintf(gString2, "$%.2f", STAT_F);
			break;
			case 4:
#ifdef MORE_LANGUAGES
			if (CFont::IsJapanese())
				sprintf(gString2, "%d", STAT_D);
			else
#endif
				sprintf(gString2, "%d_", STAT_D);
			break;
			default:
			break;
		}
	}
	UnicodeStrcpy(gUString, TheText.Get(text));
	CFont::FilterOutTokensFromString(gUString);
	AsciiToUnicode(gString2, gUString2);
#undef STAT_D
#undef STAT_F
#undef STAT2_D
#undef STAT2_F
}

// rowIdx 99999 returns total numbers of rows. otherwise it returns 0.
int
CStats::ConstructStatLine(int rowIdx)
{

#define STAT_LINE_1(varType, left, right1, type) \
	do { \
		if(counter == rowIdx){ \
			varType a = right1; \
			BuildStatLine(left, &a, type, nil, 0); \
			return 0; \
		} counter++; \
	} while(0)

#define STAT_LINE_2(varType, left, right1, type, right2, time) \
	do { \
		if(counter == rowIdx){ \
			varType a = right1; \
			varType b = right2; \
			BuildStatLine(left, &a, type, &b, time); \
			return 0; \
		} counter++; \
	} while(0)

#define TEXT_ON_LEFT_GXT(name) \
	do { \
		if(counter == rowIdx){ \
			BuildStatLine(name, nil, 0, nil, 0); \
			return 0; \
		} counter++; \
	} while(0)

#define TEXT_ON_RIGHT(text) \
	do { \
		if(counter == rowIdx){ \
			gUString[0] = '\0'; \
			UnicodeStrcpy(gUString2, text); \
			return 0; \
		} counter++; \
	} while(0)

#define FASTEST_TIME(id, str) \
	do { \
		if(FastestTimes[id]) { \
			if(counter == rowIdx){ \
				int hour = 0, minute; \
				for (int i = FastestTimes[id]; i > 59; i -= 60) hour++; \
				for (minute = FastestTimes[id]; minute > 59; minute -= 60); \
				if (minute < 0) minute = -minute; \
				BuildStatLine(str, &hour, 0, &minute, 1); \
				return 0; \
			} \
			counter++; \
		} \
	} while(0)

	switch (rowIdx) {
		case 0: {
			int percentCompleted = GetPercentageProgress();
			BuildStatLine("PER_COM", &percentCompleted, 2, nil, 0);
			return 0;
		}
		case 1: {
			BuildStatLine("NMISON", &MissionsGiven, 0, nil, 0);
			return 0;
		}
		case 2: {
			int hour = (CTimer::GetTimeInMilliseconds() / 60000) / 60;
			int minute = (CTimer::GetTimeInMilliseconds() / 60000) % 60;
			BuildStatLine("ST_TIME", &hour, 0, &minute, 1);
			return 0;
		}
		case 3: {
			BuildStatLine("DAYSPS", &DaysPassed, 0, nil, 0);
			return 0;
		}
		case 4: {
			BuildStatLine("NUMSHV", &SafeHouseVisits, 0, nil, 0);
			return 0;
		}
	}
	int counter = 5;
	
	if (CGame::nastyGame) {
		STAT_LINE_2(int, "FEST_RP", NumberKillFrenziesPassed, 0, TotalNumberKillFrenzies, 0);
	}
	
	CPlayerInfo &player = CWorld::Players[CWorld::PlayerInFocus];

	// Hidden packages shouldn't be shown with percent
#ifdef FIX_BUGS
	STAT_LINE_2(int, "PERPIC", player.m_nCollectedPackages, 0, player.m_nTotalPackages, 0);
#else
	float fPackagesPercent = 0.0f;
	if (player.m_nTotalPackages != 0)
		fPackagesPercent = player.m_nCollectedPackages * 100.0f / player.m_nTotalPackages;

	STAT_LINE_2(int, "PERPIC", fPackagesPercent, 0, 100, 0);
#endif

	if (CGame::nastyGame) {
		STAT_LINE_1(int, "PE_WAST", PeopleKilledByPlayer, 0);
		STAT_LINE_1(int, "PE_WSOT", PeopleKilledByOthers, 0);
	}
	STAT_LINE_1(int, "CAR_EXP", CarsExploded, 0);
	STAT_LINE_1(int, "BOA_EXP", BoatsExploded, 0);
	STAT_LINE_1(int, "HEL_DST", HelisDestroyed, 0);
	STAT_LINE_1(int, "TYREPOP", TyresPopped, 0);
	STAT_LINE_1(int, "ST_STAR", WantedStarsAttained, 0);
	STAT_LINE_1(int, "ST_STGN", WantedStarsEvaded, 0);
	STAT_LINE_1(int, "TM_BUST", TimesArrested, 0);
	STAT_LINE_1(int, "TM_DED", TimesDied, 0);

#ifdef MORE_LANGUAGES
	// JP version removed it altogether actually
	if (!CFont::IsJapanese())
#endif
	STAT_LINE_1(int, "ST_HEAD", HeadsPopped, 0);

	static uint32 lastProcessedDay = UINT32_MAX;
	static uint32 lastPoliceSpending = 0;

	// What a random stat...
	if (lastProcessedDay != DaysPassed) {
		lastProcessedDay = DaysPassed;
		lastPoliceSpending = (CTimer::GetTimeInMilliseconds() & 255 + 80) * 255.44f;
	}
	STAT_LINE_1(float, "DAYPLC", lastPoliceSpending, 3);

	int mostPatheticGang = 0;
	int mostKill = 0;
	for (int i = PEDTYPE_GANG1; i < PEDTYPE_GANG9; ++i) {
		if (CStats::PedsKilledOfThisType[i] > mostKill) {
			mostKill = CStats::PedsKilledOfThisType[i];
			mostPatheticGang = i;
		}
	}
	if (mostPatheticGang > 0) {
		TEXT_ON_LEFT_GXT("ST_GANG");

		switch (mostPatheticGang) {
			case PEDTYPE_GANG1:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG1"));
				break;
			case PEDTYPE_GANG2:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG2"));
				break;
			case PEDTYPE_GANG3:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG3"));
				break;
			case PEDTYPE_GANG4:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG4"));
				break;
			case PEDTYPE_GANG5:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG5"));
				break;
			case PEDTYPE_GANG6:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG6"));
				break;
			case PEDTYPE_GANG7:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG7"));
				break;
			case PEDTYPE_GANG8:
				TEXT_ON_RIGHT(TheText.Get("ST_GNG8"));
				break;
			default:
				break;
		}
	}

	STAT_LINE_1(int, "GNG_WST", PedsKilledOfThisType[PEDTYPE_GANG9] + PedsKilledOfThisType[PEDTYPE_GANG8]
			+ PedsKilledOfThisType[PEDTYPE_GANG7] + PedsKilledOfThisType[PEDTYPE_GANG6]
			+ PedsKilledOfThisType[PEDTYPE_GANG5] + PedsKilledOfThisType[PEDTYPE_GANG4]
			+ PedsKilledOfThisType[PEDTYPE_GANG3] + PedsKilledOfThisType[PEDTYPE_GANG2]
			+ PedsKilledOfThisType[PEDTYPE_GANG1], 0);

	STAT_LINE_1(int, "DED_CRI", PedsKilledOfThisType[PEDTYPE_CRIMINAL], 0);
	STAT_LINE_1(int, "KGS_EXP", KgsOfExplosivesUsed, 0);
	STAT_LINE_1(int, "BUL_FIR", RoundsFiredByPlayer, 0);
	STAT_LINE_1(int, "BUL_HIT", BulletsThatHit, 0);
;
	STAT_LINE_1(int, "ACCURA", RoundsFiredByPlayer == 0 ? 0 : (BulletsThatHit * 100.0f / (float)RoundsFiredByPlayer), 2);

	switch (FrontEndMenuManager.m_PrefsLanguage) {
		case CMenuManager::LANGUAGE_AMERICAN:
#ifndef USE_MEASUREMENTS_IN_METERS
			STAT_LINE_1(float, "FEST_DF", DistanceTravelledOnFoot * MILES_IN_METER, 1);
			STAT_LINE_1(float, "FEST_DC", DistanceTravelledByCar * MILES_IN_METER, 1);
			STAT_LINE_1(float, "DISTBIK", DistanceTravelledByBike * MILES_IN_METER, 1);
			STAT_LINE_1(float, "DISTBOA", DistanceTravelledByBoat * MILES_IN_METER, 1);
			STAT_LINE_1(float, "DISTGOL", DistanceTravelledByGolfCart * MILES_IN_METER, 1);
			STAT_LINE_1(float, "DISTHEL", DistanceTravelledByHelicoptor * MILES_IN_METER, 1);
#ifdef FIX_BUGS
			STAT_LINE_1(float, "TOT_DIS", (DistanceTravelledOnFoot + DistanceTravelledByCar + DistanceTravelledByBoat + DistanceTravelledByBike
				+ DistanceTravelledByGolfCart + DistanceTravelledByHelicoptor + DistanceTravelledByPlane) * MILES_IN_METER, 1);
			STAT_LINE_1(float, "MXCARD", MaximumJumpDistance * FEET_IN_METER, 1);
			STAT_LINE_1(float, "MXCARJ", MaximumJumpHeight * FEET_IN_METER, 1);
#else
			STAT_LINE_1(float, "TOT_DIS", (DistanceTravelledOnFoot + DistanceTravelledByCar + DistanceTravelledByBoat + DistanceTravelledByBike
				+ DistanceTravelledByGolfCart + DistanceTravelledByHelicoptor) * MILES_IN_METER, 1);
#endif
			break;
#endif
		case CMenuManager::LANGUAGE_FRENCH:
		case CMenuManager::LANGUAGE_GERMAN:
		case CMenuManager::LANGUAGE_ITALIAN:
		case CMenuManager::LANGUAGE_SPANISH:
#ifdef MORE_LANGUAGES
		case CMenuManager::LANGUAGE_POLISH:
		case CMenuManager::LANGUAGE_RUSSIAN:
		case CMenuManager::LANGUAGE_JAPANESE:
#endif
			STAT_LINE_1(float, "FESTDFM", DistanceTravelledOnFoot, 1);
			STAT_LINE_1(float, "FESTDCM", DistanceTravelledByCar, 1);
			STAT_LINE_1(float, "DISTBIM", DistanceTravelledByBike, 1);
			STAT_LINE_1(float, "DISTBOM", DistanceTravelledByBoat, 1);
			STAT_LINE_1(float, "DISTGOM", DistanceTravelledByGolfCart, 1);
			STAT_LINE_1(float, "DISTHEM", DistanceTravelledByHelicoptor, 1);
#ifdef FIX_BUGS
			STAT_LINE_1(float, "TOTDISM", DistanceTravelledOnFoot + DistanceTravelledByCar + DistanceTravelledByBoat
				+ DistanceTravelledByBike + DistanceTravelledByGolfCart + DistanceTravelledByHelicoptor + DistanceTravelledByPlane, 1);
			STAT_LINE_1(float, "MXCARDM", MaximumJumpDistance, 1);
			STAT_LINE_1(float, "MXCARJM", MaximumJumpHeight, 1);
#else
			STAT_LINE_1(float, "TOTDISM", DistanceTravelledOnFoot + DistanceTravelledByCar + DistanceTravelledByBoat
				+ DistanceTravelledByGolfCart + DistanceTravelledByHelicoptor, 1);
#endif
			break;
		default:
			break;
	}

	// They were selecting the unit according to language in III, but they deleted the feet code in VC. Weird
#ifndef FIX_BUGS
	STAT_LINE_1(float, "MXCARDM", MaximumJumpDistance, 1);
	STAT_LINE_1(float, "MXCARJM", MaximumJumpHeight, 1);
#endif
	STAT_LINE_1(int, "MXFLIP", MaximumJumpFlips, 0);
	STAT_LINE_2(int, "NOUNIF", NumberOfUniqueJumpsFound, 0, TotalNumberOfUniqueJumps, 0);
	STAT_LINE_1(int, "MXJUMP", MaximumJumpSpins, 4);

	TEXT_ON_LEFT_GXT("BSTSTU");
	switch (BestStuntJump) {
		case 1:
			TEXT_ON_RIGHT(TheText.Get("INSTUN"));
			break;
		case 2:
			TEXT_ON_RIGHT(TheText.Get("PRINST"));
			break;
		case 3:
			TEXT_ON_RIGHT(TheText.Get("DBINST"));
			break;
		case 4:
			TEXT_ON_RIGHT(TheText.Get("DBPINS"));
			break;
		case 5:
			TEXT_ON_RIGHT(TheText.Get("TRINST"));
			break;
		case 6:
			TEXT_ON_RIGHT(TheText.Get("PRTRST"));
			break;
		case 7:
			TEXT_ON_RIGHT(TheText.Get("QUINST"));
			break;
		case 8:
			TEXT_ON_RIGHT(TheText.Get("PQUINS"));
			break;
		default:
			TEXT_ON_RIGHT(TheText.Get("NOSTUC"));
			break;
	}
	STAT_LINE_1(int, "ST_WHEE", LongestWheelie, 0);
	STAT_LINE_1(float, "ST_WHED", LongestWheelieDist, 1);
	STAT_LINE_1(int, "ST_STOP", LongestStoppie, 0);
	STAT_LINE_1(float, "ST_STOD", LongestStoppieDist, 1);
	STAT_LINE_1(int, "ST_2WHE", Longest2Wheel, 0);
	STAT_LINE_1(float, "ST_2WHD", Longest2WheelDist, 1);

	if (LoanSharks > 0.0f)
		STAT_LINE_1(int, "ST_LOAN", LoanSharks, 0);

	STAT_LINE_1(int, "FEST_CC", CriminalsCaught, 0);
	STAT_LINE_1(int, "FEST_HV", HighestLevelVigilanteMission, 0);
	STAT_LINE_1(int, "PASDRO", PassengersDroppedOffWithTaxi, 0);
	STAT_LINE_1(float, "MONTAX", MoneyMadeWithTaxi, 3);
	STAT_LINE_1(int, "FEST_LS", LivesSavedWithAmbulance, 0);
	STAT_LINE_1(int, "FEST_HA", HighestLevelAmbulanceMission, 0);
	STAT_LINE_1(int, "FEST_FE", FiresExtinguished, 0);
	STAT_LINE_1(int, "FIRELVL", HighestLevelFireMission, 0);

	STAT_LINE_2(int, "ST_STOR", StoresKnockedOff, 0, 15, 0);

	if (MovieStunts > 0.0f)
		STAT_LINE_1(int, "ST_MOVI", MovieStunts, 0);

	STAT_LINE_2(int, "ST_ASSI", Assassinations, 0, 5, 0);

	if (PhotosTaken > 0)
		STAT_LINE_1(int, "ST_PHOT", PhotosTaken, 0);

	if (PizzasDelivered > 0.0f)
		STAT_LINE_1(int, "ST_PIZZ", PizzasDelivered, 0);

	if (GarbagePickups > 0.0f)
		STAT_LINE_1(int, "ST_GARB", GarbagePickups, 0);

	if (IceCreamSold > 0.0f)
		STAT_LINE_1(int, "ST_ICEC", IceCreamSold, 0);

	if (HighestScores[1])
		STAT_LINE_1(int, "STHC_02", HighestScores[1], 0);

	FASTEST_TIME(0, "STFT_01");
	FASTEST_TIME(1, "STFT_02");
	FASTEST_TIME(2, "STFT_03");
	FASTEST_TIME(3, "STFT_04");
	FASTEST_TIME(4, "STFT_05");
	FASTEST_TIME(5, "STFT_06");
	FASTEST_TIME(6, "STFT_07");
	FASTEST_TIME(7, "STFT_08");
	FASTEST_TIME(8, "STFT_09");
	FASTEST_TIME(9, "STFT_10");
	FASTEST_TIME(10, "STFT_11");
	FASTEST_TIME(11, "STFT_12");
	FASTEST_TIME(12, "STFT_13");
	FASTEST_TIME(13, "STFT_14");
	FASTEST_TIME(14, "STFT_15");
	FASTEST_TIME(15, "STFT_16");
	FASTEST_TIME(16, "STFT_17");
	FASTEST_TIME(17, "STFT_18");
	FASTEST_TIME(18, "STFT_19");
	FASTEST_TIME(19, "STFT_20");
	FASTEST_TIME(22, "STFT_23");

	if (HighestScores[0])
		STAT_LINE_1(int, "STHC_01", HighestScores[0], 0);

	if (HighestScores[3])
		STAT_LINE_1(int, "STHC_04", HighestScores[3], 0);

	if (HighestScores[2])
		STAT_LINE_1(int, "STHC_03", HighestScores[2], 0);

	if (BestPositions[0] != INT_MAX)
		STAT_LINE_1(int, "STHC_05", BestPositions[0], 0);

	FASTEST_TIME(20, "STFT_21");

	if (FastestTimes[21])
#ifdef FIX_BUGS
		STAT_LINE_1(float, "STFT_22", Floor(FastestTimes[21] / 10) / 100, 1);
#else
		STAT_LINE_1(float, "STFT_22", FastestTimes[21] / 1000, 1);
#endif

	if (TopShootingRangeScore > 0.0f)
		STAT_LINE_1(int, "TOP_SHO", TopShootingRangeScore, 0);

	if (ShootingRank > 0.0f)
		STAT_LINE_1(int, "SHO_RAN", ShootingRank, 0);

	int flightMinute = (FlightTime / 60000) % 60;
	int flightHour = (FlightTime / 60000) / 60;
	STAT_LINE_2(int, "ST_FTIM", flightHour, 0, flightMinute, 1);

	// We always have pilot rank if we flew more then 5 minutes
#ifndef FIX_BUGS
	if (flightHour != 0)
		TEXT_ON_LEFT_GXT("ST_PRAN");
#endif

#ifdef FIX_BUGS
#define FL_TIME_MORE_THAN(hour, minute) (flightHour > hour || (flightHour == hour && flightMinute >= minute))
#else
#define FL_TIME_MORE_THAN(hour, minute) (flightHour > hour || flightMinute >= minute)
#endif

	if (FL_TIME_MORE_THAN(0,5)) {

#ifdef FIX_BUGS
		TEXT_ON_LEFT_GXT("ST_PRAN");
#endif
		if (!FL_TIME_MORE_THAN(0,10)) TEXT_ON_RIGHT(TheText.Get("ST_PR01"));
		else if (!FL_TIME_MORE_THAN(0,20)) TEXT_ON_RIGHT(TheText.Get("ST_PR02"));
		else if (!FL_TIME_MORE_THAN(0,30)) TEXT_ON_RIGHT(TheText.Get("ST_PR03"));
		else if (!FL_TIME_MORE_THAN(1,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR04"));
		else if (!FL_TIME_MORE_THAN(1,30)) TEXT_ON_RIGHT(TheText.Get("ST_PR05"));
		else if (!FL_TIME_MORE_THAN(2,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR06"));
		else if (!FL_TIME_MORE_THAN(2,30)) TEXT_ON_RIGHT(TheText.Get("ST_PR07"));
		else if (!FL_TIME_MORE_THAN(3,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR08"));
		else if (!FL_TIME_MORE_THAN(3,30)) TEXT_ON_RIGHT(TheText.Get("ST_PR09"));
		else if (!FL_TIME_MORE_THAN(4,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR10"));
		else if (!FL_TIME_MORE_THAN(5,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR11"));
		else if (!FL_TIME_MORE_THAN(10,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR12"));
		else if (!FL_TIME_MORE_THAN(20,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR13"));
		else if (!FL_TIME_MORE_THAN(25,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR14"));
		else if (!FL_TIME_MORE_THAN(30,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR15"));
		else if (!FL_TIME_MORE_THAN(49,2)) TEXT_ON_RIGHT(TheText.Get("ST_PR16"));
		else if (!FL_TIME_MORE_THAN(50,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR17"));
		else if (!FL_TIME_MORE_THAN(100,0)) TEXT_ON_RIGHT(TheText.Get("ST_PR18"));
		else TEXT_ON_RIGHT(TheText.Get("ST_PR19"));
	}
#undef FL_TIME_MORE_THAN

	if (BloodRingKills > 0)
		STAT_LINE_1(int, "ST_BRK", BloodRingKills, 0);

	if (BloodRingTime > 0)
		STAT_LINE_1(int, "ST_LTBR", BloodRingTime, 0);

	STAT_LINE_1(int, "ST_DRWN", TimesDrowned, 0);

	if (SeagullsKilled > 0)
		STAT_LINE_1(int, "SEAGULL", SeagullsKilled, 0);

	bool playerHatesRadio = true;
	float* pListenTimeArray = DMAudio.GetListenTimeArray();
	for (int i = 0; i < NUM_RADIOS; i++) {
		FavoriteRadioStationList[i] = pListenTimeArray[i];
		if (FavoriteRadioStationList[i] != 0.0) // double
			playerHatesRadio = false;
	}

	if (!playerHatesRadio) {
		// Most listened
		TEXT_ON_LEFT_GXT("FST_MFR");
		float mostListenTime = FavoriteRadioStationList[0];
		int mostListenedRadio = 0;
		for (int i = 0; i < NUM_RADIOS; i++) {
			if (FavoriteRadioStationList[i] > mostListenTime) {
				mostListenTime = FavoriteRadioStationList[i];
				mostListenedRadio = i;
			}
		}
		switch (mostListenedRadio) {
			case WILDSTYLE:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM0"));
				break;
			case FLASH_FM:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM1"));
				break;
			case KCHAT:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM2"));
				break;
			case FEVER:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM3"));
				break;
			case V_ROCK:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM4"));
				break;
			case VCPR:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM5"));
				break;
			case RADIO_ESPANTOSO:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM6"));
				break;
			case EMOTION:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM7"));
				break;
			case WAVE:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM8"));
				break;
			case USERTRACK:
				TEXT_ON_RIGHT(TheText.Get("FEA_MP3"));
				break;
			default:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM8")); // heh
				break;
		}

		// Least listened
		TEXT_ON_LEFT_GXT("FST_LFR");
		float leastListenTime = FavoriteRadioStationList[0];
		int leastListenedRadio = 0;
		for (int i = 0; i < NUM_RADIOS; i++) {
#ifdef FIX_BUGS
			if (!DMAudio.IsMP3RadioChannelAvailable() && i == USERTRACK)
				continue;
#endif
			if (FavoriteRadioStationList[i] < leastListenTime) {
				leastListenTime = FavoriteRadioStationList[i];
				leastListenedRadio = i;
			}
		}
#ifndef FIX_BUGS
		if (!DMAudio.IsMP3RadioChannelAvailable() && leastListenedRadio == USERTRACK)
			leastListenedRadio = WAVE;
#endif

		switch (leastListenedRadio) {
			case WILDSTYLE:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM0"));
				break;
			case FLASH_FM:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM1"));
				break;
			case KCHAT:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM2"));
				break;
			case FEVER:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM3"));
				break;
			case V_ROCK:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM4"));
				break;
			case VCPR:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM5"));
				break;
			case RADIO_ESPANTOSO:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM6"));
				break;
			case EMOTION:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM7"));
				break;
			case WAVE:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM8"));
				break;
			case USERTRACK:
				TEXT_ON_RIGHT(TheText.Get("FEA_MP3"));
				break;
			default:
				TEXT_ON_RIGHT(TheText.Get("FEA_FM8")); // heh
				break;
		}
	}
	STAT_LINE_1(int, "SPRAYIN", Sprayings, 0);
	STAT_LINE_1(float, "ST_WEAP", WeaponBudget, 3);
	STAT_LINE_1(float, "ST_FASH", FashionBudget, 3);
	STAT_LINE_1(float, "ST_PROP", PropertyBudget, 3);
	STAT_LINE_1(float, "ST_AUTO", AutoPaintingBudget, 3);
	STAT_LINE_1(float, "ST_DAMA", PropertyBudget, 3);

	if (NumPropertyOwned > 0) {
		STAT_LINE_1(int, "PROPOWN", NumPropertyOwned, 0);
		if (PropertyOwned[0]) TEXT_ON_RIGHT(TheText.Get("STPR_1"));
		if (PropertyOwned[1]) TEXT_ON_RIGHT(TheText.Get("STPR_2"));
		if (PropertyOwned[2]) TEXT_ON_RIGHT(TheText.Get("STPR_3"));
		if (PropertyOwned[3]) TEXT_ON_RIGHT(TheText.Get("STPR_4"));
		if (PropertyOwned[4]) TEXT_ON_RIGHT(TheText.Get("STPR_5"));
		if (PropertyOwned[5]) TEXT_ON_RIGHT(TheText.Get("STPR_6"));
		if (PropertyOwned[6]) TEXT_ON_RIGHT(TheText.Get("STPR_7"));
		if (PropertyOwned[7]) TEXT_ON_RIGHT(TheText.Get("STPR_8"));
		if (PropertyOwned[8]) TEXT_ON_RIGHT(TheText.Get("STPR_9"));
		if (PropertyOwned[9]) TEXT_ON_RIGHT(TheText.Get("STPR_10"));
		if (PropertyOwned[10]) TEXT_ON_RIGHT(TheText.Get("STPR_11"));
		if (PropertyOwned[11]) TEXT_ON_RIGHT(TheText.Get("STPR_12"));
		if (PropertyOwned[12]) TEXT_ON_RIGHT(TheText.Get("STPR_13"));
		if (PropertyOwned[13]) TEXT_ON_RIGHT(TheText.Get("STPR_14"));
		if (PropertyOwned[14]) TEXT_ON_RIGHT(TheText.Get("STPR_15"));
	}
	STAT_LINE_1(int, "CHASE", HighestChaseValue, 0);
	TEXT_ON_RIGHT(FindChaseString(HighestChaseValue));

	return counter;

#undef STAT_LINE_1
#undef STAT_LINE_2
#undef TEXT_ON_LEFT_GXT
#undef TEXT_ON_RIGHT
#undef FASTEST_TIME
}
