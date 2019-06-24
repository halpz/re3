#include "common.h"
#include "patcher.h"
#include "Vehicle.h"
#include "Pools.h"
#include "CarCtrl.h"
#include "ModelIndices.h"

bool &CVehicle::bWheelsOnlyCheat = *(bool *)0x95CD78;
bool &CVehicle::bAllDodosCheat = *(bool *)0x95CD75;
bool &CVehicle::bCheat3 = *(bool *)0x95CD66;
bool &CVehicle::bCheat4 = *(bool *)0x95CD65;
bool &CVehicle::bCheat5 = *(bool *)0x95CD64;
	
void *CVehicle::operator new(size_t sz) { return CPools::GetVehiclePool()->New();  }
void CVehicle::operator delete(void *p, size_t sz) { CPools::GetVehiclePool()->Delete((CVehicle*)p); }

bool
CVehicle::IsLawEnforcementVehicle(void)
{
	switch (m_modelIndex) {
		case MI_FBICAR:
		case MI_POLICE:
		case MI_ENFORCER:
		case MI_PREDATOR:
		case MI_RHINO:
		case MI_BARRACKS:
			return true;
		default:
			return false;
	}
}

void
CVehicle::ChangeLawEnforcerState(bool enable)
{
	if (enable) {
		if (!bIsLawEnforcer) {
			bIsLawEnforcer = true;
			CCarCtrl::NumLawEnforcerCars++;
		}
	} else {
		if (bIsLawEnforcer) {
			bIsLawEnforcer = false;
			CCarCtrl::NumLawEnforcerCars--;
		}
	}
}

void
CVehicle::RemoveDriver(void)
{
	m_status = STATUS_ABANDONED;
	pDriver = nil;
}

bool
CVehicle::IsUpsideDown(void)
{
	return GetUp().z <= -0.9f;
}

STARTPATCHES
	InjectHook(0x552820, &CVehicle::ChangeLawEnforcerState, PATCH_JUMP);
	InjectHook(0x5520A0, &CVehicle::RemoveDriver, PATCH_JUMP);
ENDPATCHES