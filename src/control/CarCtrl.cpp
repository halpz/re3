#include "common.h"
#include "patcher.h"
#include "CarCtrl.h"

int &CCarCtrl::NumLawEnforcerCars = *(int*)0x8F1B38;
int &CCarCtrl::NumAmbulancesOnDuty = *(int*)0x885BB0;
int &CCarCtrl::NumFiretrucksOnDuty = *(int*)0x9411F0;
bool &CCarCtrl::bCarsGeneratedAroundCamera = *(bool*)0x95CD8A;
float& CCarCtrl::CarDensityMultiplier = *(float*)0x5EC8B4;
int32 &CCarCtrl::NumMissionCars = *(int32*)0x8F1B54;
int32 &CCarCtrl::NumRandomCars = *(int32*)0x943118;
int32 &CCarCtrl::NumParkedCars = *(int32*)0x8F29E0;

WRAPPER void CCarCtrl::SwitchVehicleToRealPhysics(CVehicle*) { EAXJMP(0x41F7F0); }
WRAPPER void CCarCtrl::AddToCarArray(int32 id, int32 vehclass) { EAXJMP(0x4182F0); }
WRAPPER void CCarCtrl::UpdateCarCount(CVehicle*, bool) { EAXJMP(0x4202E0); }
WRAPPER int32 CCarCtrl::ChooseCarModel(int32 vehclass) { EAXJMP(0x418110); }
WRAPPER bool CCarCtrl::JoinCarWithRoadSystemGotoCoors(CVehicle*, CVector, bool) { EAXJMP(0x41FA00); }
WRAPPER void CCarCtrl::JoinCarWithRoadSystem(CVehicle*) { EAXJMP(0x41F820); }
WRAPPER void CCarCtrl::SteerAICarWithPhysics(CVehicle*) { EAXJMP(0x41DA60); }
WRAPPER void CCarCtrl::UpdateCarOnRails(CVehicle*) { EAXJMP(0x418880); }
WRAPPER void CCarCtrl::ScanForPedDanger(CVehicle *veh) { EAXJMP(0x418F40); }
WRAPPER void CCarCtrl::RemoveFromInterestingVehicleList(CVehicle* v) { EAXJMP(0x41F7A0); }

bool
CCarCtrl::MapCouldMoveInThisArea(float x, float y)
{
	// bridge moves up and down
	return x > -342.0f && x < -219.0f &&
		y > -677.0f && y < -580.0f;
}
