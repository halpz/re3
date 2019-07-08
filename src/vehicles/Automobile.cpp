#include "common.h"
#include "patcher.h"
#include "VisibilityPlugins.h"
#include "SurfaceTable.h"
#include "HandlingMgr.h"
#include "Automobile.h"

bool &CAutomobile::m_sAllTaxiLights = *(bool*)0x95CD21;

WRAPPER CAutomobile* CAutomobile::ctor(int, uint8) { EAXJMP(0x52C6B0); }

CAutomobile::CAutomobile(int mi, uint8 owner)
{
	ctor(mi, owner);
}


void
CAutomobile::SetModelIndex(uint32 id)
{
	CVehicle::SetModelIndex(id);
	SetupModelNodes();
}

WRAPPER void CAutomobile::ProcessControl(void) { EAXJMP(0x531470); }
WRAPPER void CAutomobile::Teleport(CVector v) { EAXJMP(0x535180); }
WRAPPER void CAutomobile::PreRender(void) { EAXJMP(0x535B40); }
WRAPPER void CAutomobile::Render(void) { EAXJMP(0x539EA0); }


WRAPPER void CAutomobile::ProcessControlInputs(uint8) { EAXJMP(0x53B660); }

void
CAutomobile::GetComponentWorldPosition(int32 component, CVector &pos)
{
	if(m_aCarNodes[component] == nil){
		printf("CarNode missing: %d %d\n", GetModelIndex(), component);
		return;
	}
	RwMatrix *ltm = RwFrameGetLTM(m_aCarNodes[component]);
	pos = *RwMatrixGetPos(ltm);
}

bool
CAutomobile::IsComponentPresent(int32 comp)
{
	return m_aCarNodes[comp] != nil;
}

void
CAutomobile::SetComponentRotation(int32 component, CVector rotation)
{
	CMatrix mat(RwFrameGetMatrix(m_aCarNodes[component]));
	CVector pos = *mat.GetPosition();
	// BUG: all these set the whole matrix
	mat.SetRotateX(DEGTORAD(rotation.x));
	mat.SetRotateY(DEGTORAD(rotation.y));
	mat.SetRotateZ(DEGTORAD(rotation.z));
	mat.GetPosition() += pos;
	mat.UpdateRW();
}

WRAPPER void CAutomobile::OpenDoor(int32, eDoors door, float) { EAXJMP(0x52E750); }
WRAPPER void CAutomobile::ProcessOpenDoor(uint32, uint32, float) { EAXJMP(0x52E910); }

bool
CAutomobile::IsDoorReady(eDoors door)
{
	if(Doors[door].IsClosed() || IsDoorMissing(door))
		return true;
	int doorflag = 0;
	// TODO: enum?
	switch(door){
	case DOOR_FRONT_LEFT: doorflag = 1; break;
	case DOOR_FRONT_RIGHT: doorflag = 4; break;
	case DOOR_REAR_LEFT: doorflag = 2; break;
	case DOOR_REAR_RIGHT: doorflag = 8; break;
	}
	return (doorflag & m_nGettingInFlags) == 0;
}

bool
CAutomobile::IsDoorFullyOpen(eDoors door)
{
	return Doors[door].IsFullyOpen() || IsDoorMissing(door);
}

bool
CAutomobile::IsDoorClosed(eDoors door)
{
	return !!Doors[door].IsClosed();
}

bool
CAutomobile::IsDoorMissing(eDoors door)
{
	return Damage.GetDoorStatus(door) == DOOR_STATUS_MISSING;
}

void
CAutomobile::RemoveRefsToVehicle(CEntity *ent)
{
	int i;
	for(i = 0; i < 4; i++)
		if(m_aGroundPhysical[i] == ent)
			m_aGroundPhysical[i] = nil;
}

WRAPPER void CAutomobile::BlowUpCar(CEntity *ent) { EAXJMP(0x53BC60); }

bool
CAutomobile::SetUpWheelColModel(CColModel *colModel)
{
	CVehicleModelInfo *mi = (CVehicleModelInfo*)CModelInfo::GetModelInfo(GetModelIndex());
	CColModel *vehColModel = mi->GetColModel();

	colModel->boundingSphere = vehColModel->boundingSphere;
	colModel->boundingBox = vehColModel->boundingBox;

	CMatrix mat;
	mat.Attach(RwFrameGetMatrix(m_aCarNodes[CAR_WHEEL_LF]));
	colModel->spheres[0].Set(mi->m_wheelScale, mat.GetPosition(), SURFACE_TIRE, CAR_PIECE_WHEEL_LF);
	mat.Attach(RwFrameGetMatrix(m_aCarNodes[CAR_WHEEL_LB]));
	colModel->spheres[1].Set(mi->m_wheelScale, mat.GetPosition(), SURFACE_TIRE, CAR_PIECE_WHEEL_LR);
	mat.Attach(RwFrameGetMatrix(m_aCarNodes[CAR_WHEEL_RF]));
	colModel->spheres[2].Set(mi->m_wheelScale, mat.GetPosition(), SURFACE_TIRE, CAR_PIECE_WHEEL_RF);
	mat.Attach(RwFrameGetMatrix(m_aCarNodes[CAR_WHEEL_RB]));
	colModel->spheres[3].Set(mi->m_wheelScale, mat.GetPosition(), SURFACE_TIRE, CAR_PIECE_WHEEL_RR);

	if(m_aCarNodes[CAR_WHEEL_LM] != nil && m_aCarNodes[CAR_WHEEL_RM] != nil){
		mat.Attach(RwFrameGetMatrix(m_aCarNodes[CAR_WHEEL_LM]));
		colModel->spheres[4].Set(mi->m_wheelScale, mat.GetPosition(), SURFACE_TIRE, CAR_PIECE_WHEEL_RF);
		mat.Attach(RwFrameGetMatrix(m_aCarNodes[CAR_WHEEL_RM]));
		colModel->spheres[5].Set(mi->m_wheelScale, mat.GetPosition(), SURFACE_TIRE, CAR_PIECE_WHEEL_RR);
		colModel->numSpheres = 6;
	}else
		colModel->numSpheres = 4;

	return true;
}

WRAPPER void CAutomobile::BurstTyre(uint8 tyre) { EAXJMP(0x53C0E0); }
WRAPPER bool CAutomobile::IsRoomForPedToLeaveCar(uint32, CVector *) { EAXJMP(0x53C5B0); }

float
CAutomobile::GetHeightAboveRoad(void)
{
	return m_fHeightAboveRoad;
}

WRAPPER void CAutomobile::PlayCarHorn(void) { EAXJMP(0x53C450); }





WRAPPER void CAutomobile::SpawnFlyingComponent(int32 component, uint32 type) { EAXJMP(0x530300); }

void
CAutomobile::SetPanelDamage(int32 component, ePanels panel, bool noFlyingComponents)
{
	int status = Damage.GetPanelStatus(panel);
	if(m_aCarNodes[component] == nil)
		return;
	if(status == PANEL_STATUS_SMASHED1){
		// show damaged part
		SetComponentVisibility(m_aCarNodes[component], ATOMIC_FLAG_DAM);
	}else if(status == PANEL_STATUS_MISSING){
		if(!noFlyingComponents)
			SpawnFlyingComponent(component, COMPGROUP_PANEL);
		// hide both
		SetComponentVisibility(m_aCarNodes[component], ATOMIC_FLAG_NONE);
	}
}

void
CAutomobile::SetBumperDamage(int32 component, ePanels panel, bool noFlyingComponents)
{
	int status = Damage.GetPanelStatus(panel);
	if(m_aCarNodes[component] == nil){
		printf("Trying to damage component %d of %s\n",
			component, CModelInfo::GetModelInfo(GetModelIndex())->GetName());
		return;
	}
	if(status == PANEL_STATUS_SMASHED1){
		// show damaged part
		SetComponentVisibility(m_aCarNodes[component], ATOMIC_FLAG_DAM);
	}else if(status == PANEL_STATUS_MISSING){
		if(!noFlyingComponents)
			SpawnFlyingComponent(component, COMPGROUP_BUMPER);
		// hide both
		SetComponentVisibility(m_aCarNodes[component], ATOMIC_FLAG_NONE);
	}
}

void
CAutomobile::SetDoorDamage(int32 component, eDoors door, bool noFlyingComponents)
{
	int status = Damage.GetDoorStatus(door);
	if(m_aCarNodes[component] == nil){
		printf("Trying to damage component %d of %s\n",
			component, CModelInfo::GetModelInfo(GetModelIndex())->GetName());
		return;
	}

	if(door == DOOR_BOOT && status == DOOR_STATUS_SWINGING && m_handling->Flags & HANDLING_NOSWING_BOOT){
		Damage.SetDoorStatus(DOOR_BOOT, DOOR_STATUS_MISSING);
		status = DOOR_STATUS_MISSING;
	}

	if(status == DOOR_STATUS_SMASHED){
		// show damaged part
		SetComponentVisibility(m_aCarNodes[component], ATOMIC_FLAG_DAM);
	}else if(status == DOOR_STATUS_SWINGING){
		// turn off angle cull for swinging doors
		RwFrameForAllObjects(m_aCarNodes[component], CVehicleModelInfo::SetAtomicFlagCB, (void*)ATOMIC_FLAG_NOCULL);
	}else if(status == DOOR_STATUS_MISSING){
		if(!noFlyingComponents){
			if(door == DOOR_BONNET)
				SpawnFlyingComponent(component, COMPGROUP_BONNET);
			else if(door == DOOR_BOOT)
				SpawnFlyingComponent(component, COMPGROUP_BOOT);
			else
				SpawnFlyingComponent(component, COMPGROUP_DOOR);
		}
		// hide both
		SetComponentVisibility(m_aCarNodes[component], ATOMIC_FLAG_NONE);
	}
}


static RwObject*
SetVehicleAtomicVisibilityCB(RwObject *object, void *data)
{
	uint32 flags = (uint32)(uintptr)data;
	RpAtomic *atomic = (RpAtomic*)object;
	if((CVisibilityPlugins::GetAtomicId(atomic) & (ATOMIC_FLAG_OK|ATOMIC_FLAG_DAM)) == flags)
		RpAtomicSetFlags(atomic, rpATOMICRENDER);
	else
		RpAtomicSetFlags(atomic, 0);
	return object;
}

void
CAutomobile::SetComponentVisibility(RwFrame *frame, uint32 flags)
{
	HideAllComps();
	m_veh_flagC2 = true;
	RwFrameForAllObjects(frame, SetVehicleAtomicVisibilityCB, (void*)flags);
}

void
CAutomobile::SetupModelNodes(void)
{
	int i;
	for(i = 0; i < NUM_CAR_NODES; i++)
		m_aCarNodes[i] = nil;
	CClumpModelInfo::FillFrameArray((RpClump*)m_rwObject, m_aCarNodes);
}

void
CAutomobile::SetTaxiLight(bool light)
{
	bTaxiLight = light;
}

bool
CAutomobile::GetAllWheelsOffGround(void)
{
	return m_nWheelsOnGround == 0;
}

void
CAutomobile::HideAllComps(void)
{
	// empty
}

void
CAutomobile::ShowAllComps(void)
{
	// empty
}

void
CAutomobile::ReduceHornCounter(void)
{
	if(m_nCarHornTimer != 0)
		m_nCarHornTimer--;
}

void
CAutomobile::SetAllTaxiLights(bool set)
{
	m_sAllTaxiLights = set;
}

class CAutomobile_ : public CAutomobile
{
public:
	void dtor() { CAutomobile::~CAutomobile(); }
	void SetModelIndex_(uint32 id) { CAutomobile::SetModelIndex(id); }
	void ProcessControl_(void) { CAutomobile::ProcessControl(); }
	void Teleport_(CVector v) { CAutomobile::Teleport(v); }
	void PreRender_(void) { CAutomobile::PreRender(); }
	void Render_(void) { CAutomobile::Render(); }

	void ProcessControlInputs_(uint8 x) { CAutomobile::ProcessControlInputs(x); }
	void GetComponentWorldPosition_(int32 component, CVector &pos) { CAutomobile::GetComponentWorldPosition(component, pos); }
	bool IsComponentPresent_(int32 component) { return CAutomobile::IsComponentPresent(component); }
	void SetComponentRotation_(int32 component, CVector rotation) { CAutomobile::SetComponentRotation(component, rotation); }
	void OpenDoor_(int32 component, eDoors door, float ratio) { CAutomobile::OpenDoor(component, door, ratio); }
	void ProcessOpenDoor_(uint32 component, uint32 anim, float time) { CAutomobile::ProcessOpenDoor(component, anim, time); }
	bool IsDoorReady_(eDoors door) { return CAutomobile::IsDoorReady(door); }
	bool IsDoorFullyOpen_(eDoors door) { return CAutomobile::IsDoorFullyOpen(door); }
	bool IsDoorClosed_(eDoors door) { return CAutomobile::IsDoorClosed(door); }
	bool IsDoorMissing_(eDoors door) { return CAutomobile::IsDoorMissing(door); }
	void RemoveRefsToVehicle_(CEntity *ent) { CAutomobile::RemoveRefsToVehicle(ent); }
	void BlowUpCar_(CEntity *ent) { CAutomobile::BlowUpCar(ent); }
	bool SetUpWheelColModel_(CColModel *colModel) { return CAutomobile::SetUpWheelColModel(colModel); }
	void BurstTyre_(uint8 tyre) { CAutomobile::BurstTyre(tyre); }
	bool IsRoomForPedToLeaveCar_(uint32 door, CVector *pos) { return CAutomobile::IsRoomForPedToLeaveCar(door, pos); }
	float GetHeightAboveRoad_(void) { return CAutomobile::GetHeightAboveRoad(); }
	void PlayCarHorn_(void) { CAutomobile::PlayCarHorn(); }
};

STARTPATCHES
	InjectHook(0x52D170, &CAutomobile_::dtor, PATCH_JUMP);
	InjectHook(0x52D190, &CAutomobile_::SetModelIndex_, PATCH_JUMP);
	InjectHook(0x52E5F0, &CAutomobile_::GetComponentWorldPosition_, PATCH_JUMP);
	InjectHook(0x52E660, &CAutomobile_::IsComponentPresent_, PATCH_JUMP);
	InjectHook(0x52E680, &CAutomobile_::SetComponentRotation_, PATCH_JUMP);
	InjectHook(0x52EF10, &CAutomobile_::IsDoorReady_, PATCH_JUMP);
	InjectHook(0x52EF90, &CAutomobile_::IsDoorFullyOpen_, PATCH_JUMP);
	InjectHook(0x52EFD0, &CAutomobile_::IsDoorClosed_, PATCH_JUMP);
	InjectHook(0x52F000, &CAutomobile_::IsDoorMissing_, PATCH_JUMP);
	InjectHook(0x53BF40, &CAutomobile_::RemoveRefsToVehicle_, PATCH_JUMP);
	InjectHook(0x53BF70, &CAutomobile_::SetUpWheelColModel_, PATCH_JUMP);
	InjectHook(0x437690, &CAutomobile_::GetHeightAboveRoad_, PATCH_JUMP);
	InjectHook(0x5301A0, &CAutomobile::SetPanelDamage, PATCH_JUMP);
	InjectHook(0x530120, &CAutomobile::SetBumperDamage, PATCH_JUMP);
	InjectHook(0x530200, &CAutomobile::SetDoorDamage, PATCH_JUMP);
	InjectHook(0x5300E0, &CAutomobile::SetComponentVisibility, PATCH_JUMP);
	InjectHook(0x52D1B0, &CAutomobile::SetupModelNodes, PATCH_JUMP);
	InjectHook(0x53C420, &CAutomobile::SetTaxiLight, PATCH_JUMP);
	InjectHook(0x53BC40, &CAutomobile::GetAllWheelsOffGround, PATCH_JUMP);
	InjectHook(0x5308C0, &CAutomobile::ReduceHornCounter, PATCH_JUMP);
	InjectHook(0x53C440, &CAutomobile::SetAllTaxiLights, PATCH_JUMP);
ENDPATCHES
