#include "common.h"
#include "General.h"
#include "Pad.h"
#include "DMAudio.h"
#include "Camera.h"
#include "Darkel.h"
#include "Explosion.h"
#include "World.h"
#include "CarCtrl.h"
#include "Stats.h"
#include "AnimManager.h"
#include "AnimBlendAssociation.h"
#include "Ped.h"
#include "PlayerPed.h"
#include "DamageManager.h"
#include "Vehicle.h"
#include "Automobile.h"
#include "Bike.h"

#define FAKESUSPENSION (99999.992f)

CBike::CBike(int32 id, uint8 CreatedBy)
 : CVehicle(CreatedBy)
{
	int i;
	CVehicleModelInfo *mi = (CVehicleModelInfo*)CModelInfo::GetModelInfo(id);
	switch(GetModelIndex()){
	case MI_ANGEL:
	case MI_FREEWAY:
		m_bikeAnimType = ASSOCGRP_BIKE_HARLEY;
		break;
	case MI_PIZZABOY:
	case MI_FAGGIO:
		m_bikeAnimType = ASSOCGRP_BIKE_VESPA;
		break;
	case MI_PCJ600:
		m_bikeAnimType = ASSOCGRP_BIKE_STANDARD;
		break;
	case MI_SANCHEZ:
		m_bikeAnimType = ASSOCGRP_BIKE_DIRT;
		break;
	}
	m_vehType = VEHICLE_TYPE_BIKE;

	m_fFireBlowUpTimer = 0.0f;
	m_doingBurnout = 0;
	m_bike_flag01 = false;

	SetModelIndex(id);

	pHandling = mod_HandlingManager.GetHandlingData((eHandlingId)mi->m_handlingId);
	pBikeHandling = mod_HandlingManager.GetBikePointer((eHandlingId)mi->m_handlingId);
	pFlyingHandling = mod_HandlingManager.GetFlyingPointer((eHandlingId)mi->m_handlingId);

	m_bike_unused1 = 20.0f;
	m_bike_unused2 = 0;

	mi->ChooseVehicleColour(m_currentColour1, m_currentColour2);

	m_fRearForkLength = 0.0f;
	m_fFrontForkY = 0.0;
	m_fFrontForkZ = 0.0;
	m_fFrontForkSlope = Tan(DEGTORAD(mi->m_bikeSteerAngle));

	m_fMass = pHandling->fMass;
	m_fTurnMass = pHandling->fTurnMass;
	m_vecCentreOfMass = pHandling->CentreOfMass;
	m_vecCentreOfMass.z = 0.1f;
	m_fAirResistance = pHandling->Dimension.x*pHandling->Dimension.z/m_fMass;
	m_fElasticity = 0.05f;
	m_fBuoyancy = pHandling->fBuoyancy;

	m_fSteerAngle = 0.0f;
	m_fBikeSteerAngle = 0.0f;
	m_fLeanLRAngle = 0.0f;
	m_fLeanLRAngle2 = 0.0f;
	m_fGasPedal = 0.0f;
	m_fBrakePedal = 0.0f;
	m_fLeanInput = 0.0f;
	field_478 = 0;
	field_47C = 0;
	m_pSetOnFireEntity = nil;
	m_pBombRigger = nil;
	m_fGasPedalAudio = 0.0f;
	m_bike_flag02 = false;
	m_bike_flag04 = false;
	m_bike_flag08 = false;
	m_bike_flag10 = false;
	m_bike_flag20 = false;
	m_bike_flag40 = false;
	m_bike_flag80 = false;

	m_fTireTemperature = 0.0f;
	someAngle = 0.0f;
	field_490 = 0;

	for(i = 0; i < 2; i++){
		m_aWheelRotation[i] = 0.0f;
		m_aWheelSpeed[i] = 0.0f;
		m_aWheelState[i] = WHEEL_STATE_NORMAL;
		m_aWheelSkidmarkType[i] = SKIDMARK_NORMAL;
		m_aWheelSkidmarkBloody[i] = false;
		m_aWheelSkidmarkUnk[0] = false;
		m_wheelStatus[i] = WHEEL_STATUS_OK;
	}

	for(i = 0; i < 4; i++){
		m_aGroundPhysical[i] = nil;
		m_aGroundOffset[i] = CVector(0.0f, 0.0f, 0.0f);
		m_aSuspensionSpringRatioPrev[i] = m_aSuspensionSpringRatio[i] = 1.0f;
		m_aWheelTimer[i] = 0.0f;
	}

	m_nWheelsOnGround = 0;
	m_nDriveWheelsOnGround = 0;
	m_nDriveWheelsOnGroundPrev = 0;
	m_fHeightAboveRoad = 0.0f;
	m_fTraction = 1.0f;

	CColModel *colModel = mi->GetColModel();
	if(colModel->lines == nil){
		colModel->lines = (CColLine*)RwMalloc(4*sizeof(CColLine));
		colModel->numLines = 4;
	}
	// BUG? this would make more sense in the if above
	colModel->lines[0].p0.z = FAKESUSPENSION;

	SetupSuspensionLines();

	AutoPilot.m_nCarMission = MISSION_NONE;
	AutoPilot.m_nTempAction = TEMPACT_NONE;
	AutoPilot.m_nTimeToStartMission = CTimer::GetTimeInMilliseconds();
	AutoPilot.m_bStayInCurrentLevel = false;

	SetStatus(STATUS_SIMPLE);
	bUseCollisionRecords = true;
	m_nNumPassengers = 0;
	bIsVan = false;
	bIsBus = false;
	bIsBig = false;
	bLowVehicle = false;
	bPedPhysics = false;

	bLeanMatrixClean = false;
	m_leanMatrix = GetMatrix();
}

void
CBike::SetModelIndex(uint32 id)
{
	CVehicle::SetModelIndex(id);
	SetupModelNodes();
}

void
CBike::ProcessControl(void)
{
}

void
CBike::Teleport(CVector pos)
{
	CWorld::Remove(this);

	SetPosition(pos);
	SetOrientation(0.0f, 0.0f, 0.0f);
	SetMoveSpeed(0.0f, 0.0f, 0.0f);
	SetTurnSpeed(0.0f, 0.0f, 0.0f);

	ResetSuspension();

	CWorld::Add(this);
}

void
CBike::PreRender(void)
{
}

void
CBike::Render(void)
{
	CVehicleModelInfo *mi = (CVehicleModelInfo*)CModelInfo::GetModelInfo(GetModelIndex());

	m_nSetPieceExtendedRangeTime = CTimer::GetTimeInMilliseconds() + 3000;
	mi->SetVehicleColour(m_currentColour1, m_currentColour2);
	CEntity::Render();
}

int32
CBike::ProcessEntityCollision(CEntity *ent, CColPoint *colpoints)
{
	int i;
	CColModel *colModel;

	if(GetStatus() != STATUS_SIMPLE)
		bVehicleColProcessed = true;

	colModel = GetColModel();

	int numWheelCollisions = 0;
	float prevRatios[4] = { 0.0f, 0.0f, 0.0f, 0.0f};
	for(i = 0; i < 4; i++)
		prevRatios[i] = m_aSuspensionSpringRatio[i];

	if(m_bIsVehicleBeingShifted || bSkipLineCol || ent->IsPed() ||
	   GetModelIndex() == MI_DODO && ent->IsVehicle())
		colModel->numLines = 0;

	int numCollisions = CCollision::ProcessColModels(GetMatrix(), *colModel,
		ent->GetMatrix(), *ent->GetColModel(),
		colpoints,
		m_aWheelColPoints, m_aSuspensionSpringRatio);

	// m_aSuspensionSpringRatio are now set to the point where the tyre touches ground.
	// In ProcessControl these will be re-normalized to ignore the tyre radius.

	if(colModel->numLines){
		for(i = 0; i < 4; i++)
			if(m_aSuspensionSpringRatio[i] < 1.0f && m_aSuspensionSpringRatio[i] < prevRatios[i]){
				numWheelCollisions++;

				// wheel is touching a physical
				if(ent->IsVehicle() || ent->IsObject()){
					CPhysical *phys = (CPhysical*)ent;

					m_aGroundPhysical[i] = phys;
					phys->RegisterReference((CEntity**)&m_aGroundPhysical[i]);
					m_aGroundOffset[i] = m_aWheelColPoints[i].point - phys->GetPosition();
				}

				m_nSurfaceTouched = m_aWheelColPoints[i].surfaceB;
				if(ent->IsBuilding())
					m_pCurGroundEntity = ent;
			}
	}else
		colModel->numLines = 4;

	if(numCollisions > 0 || numWheelCollisions > 0){
		AddCollisionRecord(ent);
		if(!ent->IsBuilding())
			((CPhysical*)ent)->AddCollisionRecord(this);

		if(numCollisions > 0)
			if(ent->IsBuilding() ||
			   ent->IsObject() && ((CPhysical*)ent)->bInfiniteMass)
				bHasHitWall = true;
	}

	return numCollisions;
}

static int16 nLastControlInput;
static float fMouseCentreRange = 0.35f;
static float fMouseSteerSens = -0.0035f;
static float fMouseCentreMult = 0.975f;

void
CBike::ProcessControlInputs(uint8 pad)
{
	float speed = DotProduct(m_vecMoveSpeed, GetForward());

	if(CPad::GetPad(pad)->GetExitVehicle())
		bIsHandbrakeOn = true;
	else
		bIsHandbrakeOn = !!CPad::GetPad(pad)->GetHandBrake();

	// Steer left/right
#ifdef FIX_BUGS
	if(CCamera::m_bUseMouse3rdPerson && !CVehicle::m_bDisableMouseSteering){
		if(CPad::GetPad(pad)->GetMouseX() != 0.0f){
			m_fSteerInput += fMouseSteerSens*CPad::GetPad(pad)->GetMouseX();
			nLastControlInput = 2;
			if(Abs(m_fSteerInput) < fMouseCentreRange)
				m_fSteerInput *= Pow(fMouseCentreMult, CTimer::GetTimeStep());
		}else if(CPad::GetPad(pad)->GetSteeringLeftRight() || nLastControlInput != 2){
			// mouse hasn't move, steer with pad like below
			m_fSteerInput += (-CPad::GetPad(pad)->GetSteeringLeftRight()/128.0f - m_fSteerInput)*
				0.2f*CTimer::GetTimeStep();
			nLastControlInput = 0;
		}
	}else
#endif
	{
		m_fSteerInput += (-CPad::GetPad(pad)->GetSteeringLeftRight()/128.0f - m_fSteerInput)*
			0.2f*CTimer::GetTimeStep();
		nLastControlInput = 0;
	}
	m_fSteerInput = clamp(m_fSteerInput, -1.0f, 1.0f);

	// Lean forward/backward
	float updown = -CPad::GetPad(pad)->GetSteeringUpDown()/128.0f + CPad::GetPad(pad)->GetCarGunUpDown()/128.0f;
	m_fLeanInput += (updown - m_fLeanInput)*0.2f*CTimer::GetTimeStep();
	m_fLeanInput = clamp(m_fLeanInput, -1.0f, 1.0f);

	// Accelerate/Brake
	float acceleration = (CPad::GetPad(pad)->GetAccelerate() - CPad::GetPad(pad)->GetBrake())/255.0f;
	if(GetModelIndex() == MI_DODO && acceleration < 0.0f)
		acceleration *= 0.3f;
	if(Abs(speed) < 0.01f){
		// standing still, go into direction we want
		if(CPad::GetPad(pad)->GetAccelerate() > 150.0f && CPad::GetPad(pad)->GetBrake() > 150.0f){
			m_fGasPedal = CPad::GetPad(pad)->GetAccelerate()/255.0f;
			m_fBrakePedal = CPad::GetPad(pad)->GetBrake()/255.0f;
			m_doingBurnout = 1;
		}else{
			m_fGasPedal = acceleration;
			m_fBrakePedal = 0.0f;
		}
	}else{
#if 1
		// simpler than the code below
		if(speed * acceleration < 0.0f){
			// if opposite directions, have to brake first
			m_fGasPedal = 0.0f;
			m_fBrakePedal = Abs(acceleration);
		}else{
			// accelerating in same direction we were already going
			m_fGasPedal = acceleration;
			m_fBrakePedal = 0.0f;
		}
#else
		if(speed < 0.0f){
			// moving backwards currently
			if(acceleration < 0.0f){
				// still go backwards
				m_fGasPedal = acceleration;
				m_fBrakePedal = 0.0f;
			}else{
				// want to go forwards, so brake
				m_fGasPedal = 0.0f;
				m_fBrakePedal = acceleration;
			}
		}else{
			// moving forwards currently
			if(acceleration < 0.0f){
				// want to go backwards, so brake
				m_fGasPedal = 0.0f;
				m_fBrakePedal = -acceleration;
			}else{
				// still go forwards
				m_fGasPedal = acceleration;
				m_fBrakePedal = 0.0f;
			}
		}
#endif
	}

	// Actually turn wheels
	static float fValue;	// why static?
	if(m_fSteerInput < 0.0f)
		fValue = -sq(m_fSteerInput);
	else
		fValue = sq(m_fSteerInput);
	m_fSteerAngle = DEGTORAD(pHandling->fSteeringLock) * fValue;

	if(bComedyControls){
		if(((CTimer::GetTimeInMilliseconds() >> 10) & 0xF) < 12)
			m_fGasPedal = 1.0f;
		if((((CTimer::GetTimeInMilliseconds() >> 10)+6) & 0xF) < 12)
			m_fBrakePedal = 0.0f;
		bIsHandbrakeOn = false;
		if(CTimer::GetTimeInMilliseconds() & 0x800)
			m_fSteerAngle += 0.08f;
		else
			m_fSteerAngle -= 0.03f;
	}

	// Brake if player isn't in control
	// BUG: game always uses pad 0 here
	if(CPad::GetPad(pad)->ArePlayerControlsDisabled()){
		m_fBrakePedal = 1.0f;
		bIsHandbrakeOn = true;
		m_fGasPedal = 0.0f;

		FindPlayerPed()->KeepAreaAroundPlayerClear();

		// slow down car immediately
		speed = m_vecMoveSpeed.Magnitude();
		if(speed > 0.28f)
			m_vecMoveSpeed *= 0.28f/speed;
	}
}

void
CBike::GetComponentWorldPosition(int32 component, CVector &pos)
{
	if(m_aBikeNodes[component] == nil){
		printf("BikeNode missing: %d %d\n", GetModelIndex(), component);
		return;
	}
	RwMatrix *ltm = RwFrameGetLTM(m_aBikeNodes[component]);
	pos = *RwMatrixGetPos(ltm);
}

bool
CBike::IsComponentPresent(int32 component)
{
	return m_aBikeNodes[component] != nil;
}

void
CBike::SetComponentRotation(int32 component, CVector rotation)
{
	CMatrix mat(RwFrameGetMatrix(m_aBikeNodes[component]));
	CVector pos = mat.GetPosition();
	// BUG: all these set the whole matrix
	mat.SetRotateX(DEGTORAD(rotation.x));
	mat.SetRotateY(DEGTORAD(rotation.y));
	mat.SetRotateZ(DEGTORAD(rotation.z));
	mat.Translate(pos);
	mat.UpdateRW();
}

bool
CBike::IsDoorReady(eDoors door)
{
	return true;
}

bool
CBike::IsDoorFullyOpen(eDoors door)
{
	return false;
}

bool
CBike::IsDoorClosed(eDoors door)
{
	return false;
}

bool
CBike::IsDoorMissing(eDoors door)
{
	return true;
}

void
CBike::RemoveRefsToVehicle(CEntity *ent)
{
	int i;
	for(i = 0; i < 4; i++)
		if(m_aGroundPhysical[i] == ent)
			m_aGroundPhysical[i] = nil;
}

void
CBike::BlowUpCar(CEntity *culprit)
{
	if(!bCanBeDamaged)
		return;

	// explosion pushes vehicle up
	m_vecMoveSpeed.z += 0.13f;
	SetStatus(STATUS_WRECKED);
	bRenderScorched = true;

	m_fHealth = 0.0f;
	m_nBombTimer = 0;

	TheCamera.CamShake(0.7f, GetPosition().x, GetPosition().y, GetPosition().z);

	KillPedsInVehicle();

	bEngineOn = false;
	bLightsOn = false;
	ChangeLawEnforcerState(false);

	CExplosion::AddExplosion(this, culprit, EXPLOSION_CAR, GetPosition(), 0);
	CDarkel::RegisterCarBlownUpByPlayer(this);
}

bool
CBike::SetUpWheelColModel(CColModel *colModel)
{
	// TODO, but unused
	return true;
}

void
CBike::BurstTyre(uint8 wheel, bool applyForces)
{
	if(bTyresDontBurst)
		return;

	switch(wheel){
	case CAR_PIECE_WHEEL_LF: wheel = BIKEWHEEL_FRONT; break;
	case CAR_PIECE_WHEEL_LR: wheel = BIKEWHEEL_REAR; break;
	default: assert(0 && "invalid wheel");
	}

	if(m_wheelStatus[wheel] == WHEEL_STATUS_OK){
		m_wheelStatus[wheel] = WHEEL_STATUS_BURST;
#ifdef FIX_BUGS
		CStats::TyresPopped++;
#endif
// TODO(MIAMI)
//		DMAudio.PlayOneShot(m_audioEntityId, SOUND_15, 0.0f);

		if(GetStatus() == STATUS_SIMPLE){
			SetStatus(STATUS_PHYSICS);
			CCarCtrl::SwitchVehicleToRealPhysics(this);
		}

		if(applyForces){
			ApplyMoveForce(GetRight() * m_fMass * CGeneral::GetRandomNumberInRange(-0.02f, 0.02f));
			ApplyTurnForce(GetRight() * m_fTurnMass * CGeneral::GetRandomNumberInRange(-0.02f, 0.02f), GetForward());
		}
// TODO: knock off driver
	}
}

bool
CBike::IsRoomForPedToLeaveCar(uint32 component, CVector *doorOffset)
{
	CColPoint colpoint;
	CEntity *ent;
	colpoint.point = CVector(0.0f, 0.0f, 0.0f);
	CVehicleModelInfo *mi = (CVehicleModelInfo*)CModelInfo::GetModelInfo(GetModelIndex());

	CVector seatPos = mi->GetFrontSeatPosn();
	if(component == CAR_DOOR_RR || component == CAR_DOOR_LR)
		seatPos = mi->m_positions[CAR_POS_BACKSEAT];
	if(component == CAR_DOOR_LF || component == CAR_DOOR_LR)
		seatPos.x = -seatPos.x;
	seatPos = GetMatrix() * seatPos;

	CVector doorPos = CPed::GetPositionToOpenCarDoor(this, component);
	if(doorOffset){
		CVector off = *doorOffset;
		if(component == CAR_DOOR_RF || component == CAR_DOOR_RR)
			off.x = -off.x;
		doorPos += Multiply3x3(GetMatrix(), off);
	}

	if(GetUp().z < 0.0f){
		seatPos.z += 0.5f;
		doorPos.z += 0.5f;
	}

	CVector dist = doorPos - seatPos;

	// Removing that makes thiProcessEntityCollisions func. return false for van doors.
	doorPos.z += 0.5f;
	float length = dist.Magnitude();
	CVector pedPos = seatPos + dist*((length+0.6f)/length);

	if(!CWorld::GetIsLineOfSightClear(seatPos, pedPos, true, false, false, true, false, false))
		return false;
	if(CWorld::TestSphereAgainstWorld(doorPos, 0.6f, this, true, true, false, true, false, false))
		return false;
	if(CWorld::ProcessVerticalLine(doorPos, 1000.0f, colpoint, ent, true, false, false, true, false, false, nil))
		if(colpoint.point.z > doorPos.z && colpoint.point.z < doorPos.z + 0.6f)
			return false;
	float upperZ = colpoint.point.z;
	if(!CWorld::ProcessVerticalLine(doorPos, -1000.0f, colpoint, ent, true, false, false, true, false, false, nil))
		return false;
	if(upperZ != 0.0f && upperZ < colpoint.point.z)
		return false;
	return true;
}

float
CBike::GetHeightAboveRoad(void)
{
	return m_fHeightAboveRoad;
}

void
CBike::PlayCarHorn(void)
{
	int r;

	if (IsAlarmOn() || m_nCarHornTimer != 0)
		return;

	if (m_nCarHornDelay) {
		m_nCarHornDelay--;
		return;
	}

	m_nCarHornDelay = (CGeneral::GetRandomNumber() & 0x7F) + 150;
	r = m_nCarHornDelay & 7;
	if(r < 2){
		m_nCarHornTimer = 45;
	}else if(r < 4){
		if(pDriver)
			pDriver->Say(SOUND_PED_CAR_COLLISION);
		m_nCarHornTimer = 45;
	}else{
		if(pDriver)
			pDriver->Say(SOUND_PED_CAR_COLLISION);
	}
}

void
CBike::PlayHornIfNecessary(void)
{
	if(AutoPilot.m_bSlowedDownBecauseOfPeds ||
	   AutoPilot.m_bSlowedDownBecauseOfCars)
		PlayCarHorn();
}

void
CBike::ResetSuspension(void)
{
	int i;
	for(i = 0; i < 2; i++){
		m_aWheelRotation[i] = 0.0f;
		m_aWheelState[i] = WHEEL_STATE_NORMAL;
	}
	for(i = 0; i < 4; i++){
		m_aSuspensionSpringRatio[i] = 1.0f;
		m_aWheelTimer[i] = 0.0f;
	}
}

// TODO: maybe put this somewhere else
inline void
GetRelativeMatrix(RwMatrix *mat, RwFrame *frm, RwFrame *end)
{
	*mat = *RwFrameGetMatrix(frm);
	frm = RwFrameGetParent(frm);
	while(frm){
		RwMatrixTransform(mat, RwFrameGetMatrix(frm), rwCOMBINEPOSTCONCAT);
		frm = RwFrameGetParent(frm);
		if(frm == end)
			frm = nil;
	}
}

void
CBike::SetupSuspensionLines(void)
{
	int i;
	CVector posn;
	float suspOffset = 0.0f;
	RwFrame *node = nil;
	CVehicleModelInfo *mi = (CVehicleModelInfo*)CModelInfo::GetModelInfo(GetModelIndex());
	CColModel *colModel = mi->GetColModel();
	RwMatrix *mat = RwMatrixCreate();

	bool initialized = colModel->lines[0].p0.z != FAKESUSPENSION;

	for(i = 0; i < 4; i++){
		if(initialized){
			posn = colModel->lines[i].p0;
			if(i < 2)
				posn.z = m_aWheelBasePosition[0];
			else
				posn.z = m_aWheelBasePosition[1];
		}else{
			switch(i){
			case BIKESUSP_FRONT_1:
				node = m_aBikeNodes[BIKE_WHEEL_FRONT];
				suspOffset = 0.25f*mi->m_wheelScale;
				break;
			case BIKESUSP_FRONT_2:
				node = m_aBikeNodes[BIKE_WHEEL_FRONT];
				suspOffset = -0.25f*mi->m_wheelScale;
				break;
			case BIKESUSP_REAR_1:
				node = m_aBikeNodes[BIKE_WHEEL_REAR];
				suspOffset = 0.25f*mi->m_wheelScale;
				break;
			case BIKESUSP_REAR_2:
				node = m_aBikeNodes[BIKE_WHEEL_REAR];
				suspOffset = -0.25f*mi->m_wheelScale;
				break;
			}

			GetRelativeMatrix(mat, node, node);
			posn = *RwMatrixGetPos(mat);
			if(i == BIKESUSP_FRONT_1)
				m_aWheelBasePosition[BIKEWHEEL_FRONT] = posn.z;
			else if(i == BIKESUSP_REAR_1){
				m_aWheelBasePosition[BIKEWHEEL_REAR] = posn.z;

				GetRelativeMatrix(mat, node, m_aBikeNodes[BIKE_FORKS_REAR]);
				float dz = posn.z - RwMatrixGetPos(mat)->z;
				float dy = posn.y - RwMatrixGetPos(mat)->y;
				m_fRearForkLength = Sqrt(SQR(dy) + SQR(dz));
			}
			posn.y += suspOffset;
		}

		// uppermost wheel position
		posn.z += pHandling->fSuspensionUpperLimit;
		colModel->lines[i].p0 = posn;

		// lowermost wheel position
		posn.z += pHandling->fSuspensionLowerLimit - pHandling->fSuspensionUpperLimit;
		// lowest point on tyre
		posn.z -= mi->m_wheelScale*0.5f;
		colModel->lines[i].p1 = posn;

		// this is length of the spring at rest
		m_aSuspensionSpringLength[i] = pHandling->fSuspensionUpperLimit - pHandling->fSuspensionLowerLimit;
		m_aSuspensionLineLength[i] = colModel->lines[i].p0.z - colModel->lines[i].p1.z;
	}

	if(!initialized){
		GetRelativeMatrix(mat, m_aBikeNodes[BIKE_FORKS_REAR], m_aBikeNodes[BIKE_FORKS_REAR]);
		m_fFrontForkY = RwMatrixGetPos(mat)->y;
		m_fFrontForkZ = RwMatrixGetPos(mat)->z;
	}

	// Compress spring somewhat to get normal height on road
	m_fHeightAboveRoad = m_aSuspensionSpringLength[0]*(1.0f - 1.0f/(4.0f*pHandling->fSuspensionForceLevel))
			- colModel->lines[0].p0.z + mi->m_wheelScale*0.5f;
	for(i = 0; i < 2; i++)
		m_aWheelPosition[i] = mi->m_wheelScale*0.5f - m_fHeightAboveRoad;

	// adjust col model to include suspension lines
	if(colModel->boundingBox.min.z > colModel->lines[0].p1.z)
		colModel->boundingBox.min.z = colModel->lines[0].p1.z;
	float radius = Max(colModel->boundingBox.min.Magnitude(), colModel->boundingBox.max.Magnitude());
	if(colModel->boundingSphere.radius < radius)
		colModel->boundingSphere.radius = radius;

#ifdef FIX_BUGS
	RwMatrixDestroy(mat);
#endif
}

void
CBike::CalculateLeanMatrix(void)
{
	if(bLeanMatrixClean)
		return;

	CMatrix mat;
	mat.SetRotateX(-0.05f*Abs(m_fLeanLRAngle));
	mat.RotateY(m_fLeanLRAngle);
	m_leanMatrix = GetMatrix();
	m_leanMatrix = m_leanMatrix * mat;
	// place wheel back on ground
	m_leanMatrix.GetPosition() += GetUp()*(1.0f-Cos(m_fLeanLRAngle))*GetColModel()->boundingBox.min.z;
	bLeanMatrixClean = true;
}

void
CBike::GetCorrectedWorldDoorPosition(CVector &pos, CVector p1, CVector p2)
{
	CVector &fwd = GetForward();
	CVector rightWorld = CrossProduct(fwd, CVector(0.0f, 0.0f, 1.0f));
	CVector upWorld = CrossProduct(rightWorld, fwd);
	CColModel *colModel = GetColModel();
	float onSide = DotProduct(GetUp(), rightWorld);
	float diff = Max(colModel->boundingBox.max.z-colModel->boundingBox.max.x, 0.0f);
	pos = CVector(0.0f, 0.0f, 0.0f);
	float y = p2.y - p1.y;
	float x = onSide*diff + p2.x + p1.x;
	float z = p2.z - p1.z;
	pos = x*rightWorld + y*fwd + z*upWorld + GetPosition();
}

void
CBike::Fix(void)
{
	bIsDamaged = false;
	m_bike_flag40 = false;
	m_wheelStatus[0] = WHEEL_STATUS_OK;
	m_wheelStatus[1] = WHEEL_STATUS_OK;
}

void
CBike::SetupModelNodes(void)
{
	int i;
	for(i = 0; i < BIKE_NUM_NODES; i++)
		m_aBikeNodes[i] = nil;
	CClumpModelInfo::FillFrameArray(GetClump(), m_aBikeNodes);
}

void
CBike::ReduceHornCounter(void)
{
	if(m_nCarHornTimer != 0)
		m_nCarHornTimer--;
}
