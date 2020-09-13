#include "common.h"

#include "Stats.h"
#include "Text.h"
#include "World.h"
#include "Pad.h"
#include "DMAudio.h"

#include <climits>

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
int32 CStats::ProgressMade;
int32 CStats::TotalProgressInGame;
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

// --MIAMI: functions below are done, but there are some to be moved from Frontend

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
	ProgressMade = 0;
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
	IndustrialPassed = 0;
	CommercialPassed = 0;
	SuburbanPassed = 0;
	PamphletMissionPassed = 0;
	NoMoreHurricanes = 0;
	ShowChaseStatOnScreen = 0;
	abSonyCDs[0] = 0;
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
	if (fMediaLevel < 20.0f) return TheText.Get("MEDIA1");
	if (fMediaLevel < 50.0f) return TheText.Get("MEDIA2");
	if (fMediaLevel < 75.0f) return TheText.Get("MEDIA3");
	if (fMediaLevel < 100.0f) return TheText.Get("MEDIA4");
	if (fMediaLevel < 150.0f) return TheText.Get("MEDIA5");
	if (fMediaLevel < 200.0f) return TheText.Get("MEDIA6");
	if (fMediaLevel < 250.0f) return TheText.Get("MEDIA7");
	if (fMediaLevel < 300.0f) return TheText.Get("MEDIA8");
	if (fMediaLevel < 350.0f) return TheText.Get("MEDIA9");
	if (fMediaLevel < 400.0f) return TheText.Get("MEDIA10");
	if (fMediaLevel < 500.0f) return TheText.Get("MEDIA11");
	if (fMediaLevel < 600.0f) return TheText.Get("MEDIA12");
	if (fMediaLevel < 700.0f) return TheText.Get("MEDIA13");
	if (fMediaLevel < 800.0f) return TheText.Get("MEDIA14");
	if (fMediaLevel < 900.0f) return TheText.Get("MEDIA15");
	if (fMediaLevel < 1000.0f) return TheText.Get("MEDIA16");
	if (fMediaLevel < 1200.0f) return TheText.Get("MEDIA17");
	if (fMediaLevel < 1400.0f) return TheText.Get("MEDIA18");
	if (fMediaLevel < 1600.0f) return TheText.Get("MEDIA19");
	if (fMediaLevel < 1800.0f) return TheText.Get("MEDIA20");
	return TheText.Get("MEDIA21");
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
		rating += (float)CStats::BulletsThatHit / (float)CStats::RoundsFiredByPlayer * 500.0f;
	if (TotalProgressInGame)
		rating += (float)CStats::ProgressMade / (float)CStats::TotalProgressInGame * 1000.0f;
	return rating;
}

float CStats::GetPercentageProgress()
{
	float percentCompleted = (CStats::TotalProgressInGame == 0 ? 0 :
		CStats::ProgressMade * 100.0f / (CGame::nastyGame ? CStats::TotalProgressInGame : CStats::TotalProgressInGame - 1.0f));

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