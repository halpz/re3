#include "common.h"
#include "main.h"
#include "patcher.h"
#include "Timer.h"
#include "Vehicle.h"
#include "Pools.h"
#include "HandlingMgr.h"
#include "CarCtrl.h"
#include "Population.h"
#include "ModelIndices.h"
#include "World.h"
#include "Lights.h"
#include "PointLights.h"
#include "Renderer.h"
#include "DMAudio.h"
#include "Radar.h"

bool &CVehicle::bWheelsOnlyCheat = *(bool *)0x95CD78;
bool &CVehicle::bAllDodosCheat = *(bool *)0x95CD75;
bool &CVehicle::bCheat3 = *(bool *)0x95CD66;
bool &CVehicle::bCheat4 = *(bool *)0x95CD65;
bool &CVehicle::bCheat5 = *(bool *)0x95CD64;
bool &CVehicle::m_bDisableMouseSteering = *(bool *)0x60252C;

void *CVehicle::operator new(size_t sz) { return CPools::GetVehiclePool()->New();  }
void *CVehicle::operator new(size_t sz, int handle) { return CPools::GetVehiclePool()->New(handle); }
void CVehicle::operator delete(void *p, size_t sz) { CPools::GetVehiclePool()->Delete((CVehicle*)p); }
void CVehicle::operator delete(void *p, int handle) { CPools::GetVehiclePool()->Delete((CVehicle*)p); }

CVehicle::~CVehicle()
{
	m_nAlarmState = 0;
	if (m_audioEntityId >= 0){
		DMAudio.DestroyEntity(m_audioEntityId);
		m_audioEntityId = -5;
	}
	CRadar::ClearBlipForEntity(BLIP_CAR, CPools::GetVehiclePool()->GetIndex(this));
	if (pDriver)
		pDriver->FlagToDestroyWhenNextProcessed();
	for (int i = 0; i < m_nNumMaxPassengers; i++){
		if (pPassengers[i])
			pPassengers[i]->FlagToDestroyWhenNextProcessed();
	}
	if (m_pCarFire)
		m_pCarFire->Extinguish();
	CCarCtrl::UpdateCarCount(this, true);
	if (bIsAmbulanceOnDuty){
		CCarCtrl::NumAmbulancesOnDuty--;
		bIsAmbulanceOnDuty = false;
	}
	if (bIsFireTruckOnDuty){
		CCarCtrl::NumFiretrucksOnDuty--;
		bIsFireTruckOnDuty = false;
	}
}

void
CVehicle::SetModelIndex(uint32 id)
{
	CEntity::SetModelIndex(id);
	m_aExtras[0] = CVehicleModelInfo::ms_compsUsed[0];
	m_aExtras[1] = CVehicleModelInfo::ms_compsUsed[1];
	m_nNumMaxPassengers = CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(id);
}

bool
CVehicle::SetupLighting(void)
{
	ActivateDirectional();
	SetAmbientColoursForPedsCarsAndObjects();

	if(bRenderScorched){
		WorldReplaceNormalLightsWithScorched(Scene.world, 0.1f);
	}else{
		CVector coors = GetPosition();
		float lighting = CPointLights::GenerateLightsAffectingObject(&coors);
		if(!bHasBlip && lighting != 1.0f){
			SetAmbientAndDirectionalColours(lighting);
			return true;
		}
	}

	return false;
}

void
CVehicle::RemoveLighting(bool reset)
{
	CRenderer::RemoveVehiclePedLights(this, reset);
}

float
CVehicle::GetHeightAboveRoad(void)
{
	return -1.0f * CModelInfo::GetModelInfo(GetModelIndex())->GetColModel()->boundingBox.min.z;
}


bool
CVehicle::IsLawEnforcementVehicle(void)
{
	switch(GetModelIndex()){
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

bool
CVehicle::UsesSiren(uint32 id)
{
	switch(id){
	case MI_FIRETRUCK:
	case MI_AMBULAN:
	case MI_FBICAR:
	case MI_MRWHOOP:
	case MI_POLICE:
	case MI_ENFORCER:
	case MI_PREDATOR:
		return true;
	default:
		return false;
	}
}

bool
CVehicle::IsVehicleNormal(void)
{
	if(pDriver && m_nNumPassengers == 0 && m_status != STATUS_WRECKED){
		switch(GetModelIndex())
		case MI_FIRETRUCK:
		case MI_AMBULAN:
		case MI_TAXI:
		case MI_POLICE:
		case MI_ENFORCER:
		case MI_BUS:
		case MI_RHINO:
		case MI_BARRACKS:
		case MI_DODO:
		case MI_COACH:
		case MI_CABBIE:
		case MI_RCBANDIT:
		case MI_BORGNINE:
			return false;
	}
	return false;
}

bool
CVehicle::CarHasRoof(void)
{
	if((m_handling->Flags & HANDLING_HAS_NO_ROOF) == 0)
		return true;
	if(m_aExtras[0] && m_aExtras[1])
		return false;
	return true;
}

bool
CVehicle::IsUpsideDown(void)
{
	if(GetUp().z > -0.9f)
		return false;
	return true;
}

bool
CVehicle::IsOnItsSide(void)
{
	if(GetRight().z < 0.8f && GetRight().z > -0.8f)
		return false;
	return true;
}

bool
CVehicle::CanBeDeleted(void)
{
	int i;

	if(m_nNumGettingIn || m_nGettingOutFlags)
		return false;

	if(pDriver){
		// This looks like it was inlined
		if(pDriver->CharCreatedBy == MISSION_CHAR)
			return false;
		if(pDriver->GetPedState() != PED_DRIVING &&
		   pDriver->GetPedState() != PED_DEAD)
			return false;
	}

	for(i = 0; i < 8; i++){
		// Same check as above
		if(pPassengers[i]){
			if(pPassengers[i]->CharCreatedBy == MISSION_CHAR)
				return false;
			if(pPassengers[i]->GetPedState() != PED_DRIVING &&
			   pPassengers[i]->GetPedState() != PED_DEAD)
				return false;
		}
		// and then again... probably because something was inlined
		if(pPassengers[i]){
			if(pPassengers[i]->GetPedState() != PED_DRIVING &&
			   pPassengers[i]->GetPedState() != PED_DEAD)
				return false;
		}
	}

	switch(VehicleCreatedBy){
	case RANDOM_VEHICLE: return true;
	case MISSION_VEHICLE: return false;
	case PARKED_VEHICLE: return true;
	case PERMANENT_VEHICLE: return false;
	}
	return true;
}

bool
CVehicle::CanPedOpenLocks(CPed *ped)
{
	if(m_nDoorLock == CARLOCK_LOCKED ||
	   m_nDoorLock == CARLOCK_COP_CAR ||
	   m_nDoorLock == CARLOCK_LOCKED_PLAYER_INSIDE)
		return false;
	if(ped->IsPlayer() && m_nDoorLock == CARLOCK_LOCKOUT_PLAYER_ONLY)
		return false;
	return true;
}

bool
CVehicle::CanPedEnterCar(void)
{
	CVector up = GetUp();
	// can't enter when car is on side
	if(up.z > 0.1f || up.z < -0.1f){
		// also when car is moving too fast
		if(m_vecMoveSpeed.MagnitudeSqr() > sq(0.2f))
			return false;
		if(m_vecTurnSpeed.MagnitudeSqr() > sq(0.2f))
			return false;
		return true;
	}
	return false;
}

bool
CVehicle::CanPedExitCar(void)
{
	CVector up = GetUp();
	if(up.z > 0.1f || up.z < -0.1f){
		// can't exit when car is moving too fast
		if(m_vecMoveSpeed.MagnitudeSqr() > 0.005f)
			return false;
		// if car is slow enough, check turn speed
		if(fabs(m_vecTurnSpeed.x) > 0.01f ||
		   fabs(m_vecTurnSpeed.y) > 0.01f ||
		   fabs(m_vecTurnSpeed.z) > 0.01f)
			return false;
		return true;
	}else{
		// What is this? just > replaced by >= ??

		// can't exit when car is moving too fast
		if(m_vecMoveSpeed.MagnitudeSqr() >= 0.005f)
			return false;
		// if car is slow enough, check turn speed
		if(fabs(m_vecTurnSpeed.x) >= 0.01f ||
		   fabs(m_vecTurnSpeed.y) >= 0.01f ||
		   fabs(m_vecTurnSpeed.z) >= 0.01f)
			return false;
		return true;
	}
}

void
CVehicle::ChangeLawEnforcerState(uint8 enable)
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

CPed*
CVehicle::SetUpDriver(void)
{
	if(pDriver)
		return pDriver;
	if(VehicleCreatedBy != RANDOM_VEHICLE)
		return nil;

	pDriver = CPopulation::AddPedInCar(this);
	pDriver->m_pMyVehicle = this;
	pDriver->m_pMyVehicle->RegisterReference((CEntity**)&pDriver->m_pMyVehicle);
	pDriver->bInVehicle = true;
	pDriver->SetPedState(PED_DRIVING);
	if(bIsBus)
		pDriver->m_ped_flagC4 = false;
	return pDriver;
}

CPed*
CVehicle::SetupPassenger(int n)
{
	if(pPassengers[n])
		return pPassengers[n];

	pPassengers[n] = CPopulation::AddPedInCar(this);
	pPassengers[n]->m_pMyVehicle = this;
	pPassengers[n]->m_pMyVehicle->RegisterReference((CEntity**)&pPassengers[n]->m_pMyVehicle);
	pPassengers[n]->bInVehicle = true;
	pPassengers[n]->SetPedState(PED_DRIVING);
	if(bIsBus)
		pPassengers[n]->m_ped_flagC4 = false;
	return pPassengers[n];
}

void
CVehicle::SetDriver(CPed *driver)
{
	pDriver = driver;
	pDriver->RegisterReference((CEntity**)&pDriver);

	if(bFreebies && driver == FindPlayerPed()){
		if(GetModelIndex() == MI_AMBULAN)
			FindPlayerPed()->m_fHealth = min(FindPlayerPed()->m_fHealth + 20.0f, 100.0f);
		else if(GetModelIndex() == MI_TAXI)
			CWorld::Players[CWorld::PlayerInFocus].m_nMoney += 25;
		else if(GetModelIndex() == MI_POLICE)
			driver->GiveWeapon(WEAPONTYPE_SHOTGUN, 5);
		else if(GetModelIndex() == MI_ENFORCER)
			driver->m_fArmour = max(driver->m_fArmour, 100.0f);
		else if(GetModelIndex() == MI_CABBIE || GetModelIndex() == MI_BORGNINE)
			CWorld::Players[CWorld::PlayerInFocus].m_nMoney += 25;
		bFreebies = false;
	}

	ApplyTurnForce(0.0f, 0.0f, -0.2f*driver->m_fMass,
		driver->GetPosition().x - GetPosition().x,
		driver->GetPosition().y - GetPosition().y,
		0.0f);
}

bool
CVehicle::AddPassenger(CPed *passenger)
{
	int i;

	ApplyTurnForce(0.0f, 0.0f, -0.2f*passenger->m_fMass,
		passenger->GetPosition().x - GetPosition().x,
		passenger->GetPosition().y - GetPosition().y,
		0.0f);

	for(i = 0; i < m_nNumMaxPassengers; i++)
		if(pPassengers[i] == nil){
			pPassengers[i] = passenger;
			m_nNumPassengers++;
			return true;
		}
	return false;
}

bool
CVehicle::AddPassenger(CPed *passenger, uint8 n)
{
	if(bIsBus)
		return AddPassenger(passenger);

	ApplyTurnForce(0.0f, 0.0f, -0.2f*passenger->m_fMass,
		passenger->GetPosition().x - GetPosition().x,
		passenger->GetPosition().y - GetPosition().y,
		0.0f);

	if(n < m_nNumMaxPassengers && pPassengers[n] == nil){
		pPassengers[n] = passenger;
		m_nNumPassengers++;
		return true;
	}
	return false;
}

void
CVehicle::RemoveDriver(void)
{
	m_status = STATUS_ABANDONED;
	pDriver = nil;
}

void
CVehicle::RemovePassenger(CPed *p)
{
	if (IsTrain()){
		for (int i = 0; i < 8; i++){
			if (pPassengers[i] == p) {
				pPassengers[i] = nil;
				m_nNumPassengers--;
				return;
			}
		}
		return;
	}
	for (int i = 0; i < m_nNumMaxPassengers; i++){
		if (pPassengers[i] == p){
			pPassengers[i] = nil;
			m_nNumPassengers--;
			return;
		}
	}
}

void
CVehicle::ProcessCarAlarm(void)
{
	uint32 step;

	if(m_nAlarmState == 0 || m_nAlarmState == -1)
		return;

	step = CTimer::GetTimeStep()/50.0f * 1000.0f;
	if((uint16)m_nAlarmState < step)
		m_nAlarmState = 0;
	else
		m_nAlarmState -= step;
}

bool
CVehicle::IsSphereTouchingVehicle(float sx, float sy, float sz, float radius)
{
	float x, y, z;
	// sphere relative to vehicle
	CVector sph = CVector(sx, sy, sz) - GetPosition();
	CColModel *colmodel = CModelInfo::GetModelInfo(GetModelIndex())->GetColModel();

	x = DotProduct(sph, GetRight());
	if(colmodel->boundingBox.min.x - radius > x ||
	   colmodel->boundingBox.max.x + radius < x)
		return false;
	y = DotProduct(sph, GetForward());
	if(colmodel->boundingBox.min.y - radius > y ||
	   colmodel->boundingBox.max.y + radius < y)
		return false;
	z = DotProduct(sph, GetUp());
	if(colmodel->boundingBox.min.z - radius > z ||
	   colmodel->boundingBox.max.z + radius < z)
		return false;

	return true;
}

STARTPATCHES
	InjectHook(0x551170, &CVehicle::SetModelIndex_, PATCH_JUMP);
	InjectHook(0x4A7DD0, &CVehicle::SetupLighting_, PATCH_JUMP);
	InjectHook(0x4A7E60, &CVehicle::RemoveLighting_, PATCH_JUMP);
	InjectHook(0x417E60, &CVehicle::GetHeightAboveRoad_, PATCH_JUMP);

	InjectHook(0x552880, &CVehicle::IsLawEnforcementVehicle, PATCH_JUMP);
	InjectHook(0x552820, &CVehicle::ChangeLawEnforcerState, PATCH_JUMP);
	InjectHook(0x552200, &CVehicle::UsesSiren, PATCH_JUMP);
	InjectHook(0x5527E0, &CVehicle::IsVehicleNormal, PATCH_JUMP);
	InjectHook(0x552B70, &CVehicle::CarHasRoof, PATCH_JUMP);
	InjectHook(0x552230, &CVehicle::IsUpsideDown, PATCH_JUMP);
	InjectHook(0x552260, &CVehicle::IsOnItsSide, PATCH_JUMP);
	InjectHook(0x5511B0, &CVehicle::CanBeDeleted, PATCH_JUMP);
	InjectHook(0x5522A0, &CVehicle::CanPedOpenLocks, PATCH_JUMP);
	InjectHook(0x5522F0, &CVehicle::CanPedEnterCar, PATCH_JUMP);
	InjectHook(0x5523C0, &CVehicle::CanPedExitCar, PATCH_JUMP);
	InjectHook(0x5520C0, &CVehicle::SetUpDriver, PATCH_JUMP);
	InjectHook(0x552160, &CVehicle::SetupPassenger, PATCH_JUMP);
	InjectHook(0x551F20, &CVehicle::SetDriver, PATCH_JUMP);
	InjectHook(0x551D90, (bool (CVehicle::*)(CPed*))&CVehicle::AddPassenger, PATCH_JUMP);
	InjectHook(0x551E10, (bool (CVehicle::*)(CPed*,uint8))&CVehicle::AddPassenger, PATCH_JUMP);
	InjectHook(0x5520A0, &CVehicle::RemoveDriver, PATCH_JUMP);
	InjectHook(0x551EB0, &CVehicle::RemovePassenger, PATCH_JUMP);
	InjectHook(0x5525A0, &CVehicle::ProcessCarAlarm, PATCH_JUMP);
	InjectHook(0x552620, &CVehicle::IsSphereTouchingVehicle, PATCH_JUMP);
ENDPATCHES
