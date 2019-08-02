#include "common.h"
#include "patcher.h"
#include "CarGen.h"

#include "Automobile.h"
#include "Boat.h"
#include "Camera.h"
#include "CarCtrl.h"
#include "CutsceneMgr.h"
#include "General.h"
#include "Pools.h"
#include "Streaming.h"
#include "Timer.h"
#include "Vehicle.h"
#include "World.h"

uint8 &CTheCarGenerators::ProcessCounter = *(uint8*)0x95CDAF;
uint32 &CTheCarGenerators::NumOfCarGenerators = *(uint32*)0x8E2C1C;
CCarGenerator (&CTheCarGenerators::CarGeneratorArray)[NUM_CARGENS] = *(CCarGenerator(*)[NUM_CARGENS])*(uintptr*)0x87CB18;
uint8 &CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter = *(uint8*)0x95CDC6;
uint32 &CTheCarGenerators::CurrentActiveCount = *(uint32*)0x8F2C5C;

void CCarGenerator::SwitchOff()
{
	m_nUsesRemaining = 0;
	--CTheCarGenerators::CurrentActiveCount;
}

void CCarGenerator::SwitchOn()
{
	m_nUsesRemaining = -1;
	m_nTimer = CalcNextGen();
	++CTheCarGenerators::CurrentActiveCount;
}

uint32 CCarGenerator::CalcNextGen()
{
	return CTimer::GetTimeInMilliseconds() + 4;
}

void CCarGenerator::DoInternalProcessing()
{
	if (CheckForBlockage()) {
		m_nTimer += 4;
		if (m_nUsesRemaining == 0)
			--CTheCarGenerators::CurrentActiveCount;
		return;
	}
	if (CCarCtrl::NumParkedCars >= 10)
		return;
	CStreaming::RequestModel(m_nModelIndex, STREAMFLAGS_DEPENDENCY);
	if (!CStreaming::HasModelLoaded(m_nModelIndex))
		return;
	if (CModelInfo::IsBoatModel(m_nModelIndex)){
		CBoat* pBoat = new CBoat(m_nModelIndex, PARKED_VEHICLE);
		pBoat->bIsStatic = false;
		pBoat->bEngineOn = false;
		CVector pos = m_vecPos;
		if (pos.z <= -100.0f)
			pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
		pos.z += pBoat->GetDistanceFromCentreOfMassToBaseOfModel();
		pBoat->GetPosition() = pos;
		pBoat->SetOrientation(0.0f, 0.0f, DEGTORAD(m_fAngle));
		pBoat->m_status = STATUS_ABANDONED;
		pBoat->m_nDoorLock = CARLOCK_UNLOCKED;
		CWorld::Add(pBoat);
		if (CGeneral::GetRandomNumberInRange(0, 100) < m_nAlarm)
			pBoat->m_nAlarmState = -1;
		if (CGeneral::GetRandomNumberInRange(0, 100) < m_nDoorlock)
			pBoat->m_nDoorLock = CARLOCK_LOCKED;
		if (m_nColor1 != -1 && m_nColor2){
			pBoat->m_currentColour1 = m_nColor1;
			pBoat->m_currentColour2 = m_nColor2;
		}
		m_nVehicleHandle = CPools::GetVehiclePool()->GetIndex(pBoat);
	}else{
		bool groundFound = false;
		CVector pos = m_vecPos;
		if (pos.z > -100.0f){
			pos.z = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &groundFound);
		}else{
			CColPoint cp;
			CEntity* pEntity;
			groundFound = CWorld::ProcessVerticalLine(CVector(pos.x, pos.y, 1000.0f), -1000.0f,
				cp, pEntity, true, false, false, false, false, false, nil);
			if (groundFound)
				pos.z = cp.point.z;
		}
		if (!groundFound) {
			debug("CCarGenerator::DoInternalProcessing - can't find ground z for new car x = %f y = %f \n", m_vecPos.x, m_vecPos.y);
		}else{
			CAutomobile* pCar = new CAutomobile(m_nModelIndex, PARKED_VEHICLE);
			pCar->bIsStatic = false;
			pCar->bEngineOn = false;
			pos.z += pCar->GetDistanceFromCentreOfMassToBaseOfModel();
			pCar->GetPosition() = pos;
			pCar->SetOrientation(0.0f, 0.0f, DEGTORAD(m_fAngle));
			pCar->m_status = STATUS_ABANDONED;
			pCar->bLightsOn = false;
			pCar->m_nDoorLock = CARLOCK_UNLOCKED;
			CWorld::Add(pCar);
			if (CGeneral::GetRandomNumberInRange(0, 100) < m_nAlarm)
				pCar->m_nAlarmState = -1;
			if (CGeneral::GetRandomNumberInRange(0, 100) < m_nDoorlock)
				pCar->m_nDoorLock = CARLOCK_LOCKED;
			if (m_nColor1 != -1 && m_nColor2) {
				pCar->m_currentColour1 = m_nColor1;
				pCar->m_currentColour2 = m_nColor2;
			}
			m_nVehicleHandle = CPools::GetVehiclePool()->GetIndex(pCar);
		}
	}
	if (m_nUsesRemaining < -1) /* I don't think this is a correct comparasion */
		--m_nUsesRemaining;
	m_nTimer = CalcNextGen();
	if (m_nUsesRemaining == 0)
		--CTheCarGenerators::CurrentActiveCount;
}

void CCarGenerator::Process()
{
	if (m_nVehicleHandle == -1 && 
		(CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter || CTimer::GetTimeInMilliseconds() >= m_nTimer) &&
		m_nUsesRemaining != 0 && CheckIfWithinRangeOfAnyPlayer())
		DoInternalProcessing();
	if (m_nVehicleHandle == -1)
		return;
	CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(m_nVehicleHandle);
	if (!pVehicle){
		m_nVehicleHandle = -1;
		return;
	}
	if (pVehicle->m_status != STATUS_PLAYER)
		return;
	m_nTimer += 60000;
	m_nVehicleHandle = -1;
	m_bIsBlocking = true;
	pVehicle->bExtendedRange = false;
}

void CCarGenerator::Setup(float x, float y, float z, float angle, int32 mi, int16 color1, int16 color2, uint8 force, uint8 alarm, uint8 lock, uint16 min_delay, uint16 max_delay)
{
	CMatrix m1, m2, m3; /* Unused but present on stack, so I'll leave them. */
	m_vecPos = CVector(x, y, z);
	m_fAngle = angle;
	m_nModelIndex = mi;
	m_nColor1 = color1;
	m_nColor2 = color2;
	m_bForceSpawn = force;
	m_nAlarm = alarm;
	m_nDoorlock = lock;
	m_nMinDelay = min_delay;
	m_nMaxDelay = max_delay;
	m_nVehicleHandle = -1;
	m_nTimer = CTimer::GetTimeInMilliseconds() + 1;
	m_nUsesRemaining = 0;
	m_bIsBlocking = false;
	m_vecInf = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->boundingBox.min;
	m_vecSup = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->boundingBox.max;
	m_fSize = max(m_vecInf.Magnitude(), m_vecSup.Magnitude());
}

bool CCarGenerator::CheckForBlockage()
{
	int16 entities;
	CWorld::FindObjectsKindaColliding(CVector(m_vecPos), m_fSize, 1, &entities, 2, nil, false, true, true, false, false);
	return entities > 0;
}

bool CCarGenerator::CheckIfWithinRangeOfAnyPlayer()
{
	CVector2D direction = FindPlayerCentreOfWorld(CWorld::PlayerInFocus) - m_vecPos;
	float distance = direction.Magnitude();
	float farclip = 120.0f * TheCamera.GenerationDistMultiplier;
	float nearclip = farclip - 20.0f;
	if (distance >= farclip){
		if (m_bIsBlocking)
			m_bIsBlocking = false;
		return false;
	}
	if (CTheCarGenerators::GenerateEvenIfPlayerIsCloseCounter)
		return true;
	if (m_bIsBlocking)
		return false;
	if (distance < nearclip)
		return false;
	return DotProduct2D(direction, FindPlayerSpeed()) <= 0;
}

void CCarGenerator::Save(uint8* buffer)
{
	*(uint32*)(buffer) = m_nModelIndex;
	*(CVector*)(buffer + 4) = m_vecPos;
	*(float*)(buffer + 16) = m_fAngle;
	*(int16*)(buffer + 20) = m_nColor1;
	*(int16*)(buffer + 22) = m_nColor2;
	*(bool*)(buffer + 24) = m_bForceSpawn;
	*(uint8*)(buffer + 25) = m_nAlarm;
	*(uint8*)(buffer + 26) = m_nDoorlock;
	*(uint8*)(buffer + 27) = 0;
	*(uint16*)(buffer + 28) = m_nMinDelay;
	*(uint16*)(buffer + 30) = m_nMaxDelay;
	*(uint32*)(buffer + 32) = m_nTimer;
	*(int32*)(buffer + 36) = m_nVehicleHandle;
	*(uint16*)(buffer + 40) = m_nUsesRemaining;
	*(bool*)(buffer + 42) = m_bIsBlocking;
	*(uint8*)(buffer + 43) = 0;
	*(CVector*)(buffer + 44) = m_vecInf;
	*(CVector*)(buffer + 56) = m_vecSup;
	*(float*)(buffer + 68) = m_fSize;
}

void CCarGenerator::Load(uint8* buffer)
{
	m_nModelIndex = *(uint32*)(buffer);
	m_vecPos = *(CVector*)(buffer + 4);
	m_fAngle = *(float*)(buffer + 16);
	m_nColor1 = *(int16*)(buffer + 20);
	m_nColor2 = *(int16*)(buffer + 22);
	m_bForceSpawn = *(bool*)(buffer + 24);
	m_nAlarm = *(uint8*)(buffer + 25);
	m_nDoorlock = *(uint8*)(buffer + 26);
	m_nMinDelay = *(uint16*)(buffer + 28);
	m_nMaxDelay = *(uint16*)(buffer + 30);
	m_nTimer = *(uint32*)(buffer + 32);
	m_nVehicleHandle = *(int32*)(buffer + 36);
	m_nUsesRemaining = *(uint16*)(buffer + 40);
	m_bIsBlocking = *(bool*)(buffer + 42);
	m_vecInf = *(CVector*)(buffer + 44);
	m_vecSup = *(CVector*)(buffer + 56);
	m_fSize = *(float*)(buffer + 68);
}

void CTheCarGenerators::Process()
{
	if (FindPlayerTrain() || CCutsceneMgr::IsRunning())
		return;
	if (++CTheCarGenerators::ProcessCounter == 4)
		CTheCarGenerators::ProcessCounter = 0;
	for (uint32 i = ProcessCounter; i < NumOfCarGenerators; i += 4)
		CTheCarGenerators::CarGeneratorArray[i].Process();
	if (GenerateEvenIfPlayerIsCloseCounter)
		GenerateEvenIfPlayerIsCloseCounter--;
}

int32 CTheCarGenerators::CreateCarGenerator(float x, float y, float z, float angle, int32 mi, int16 color1, int16 color2, uint8 force, uint8 alarm, uint8 lock, uint16 min_delay, uint16 max_delay)
{
	CarGeneratorArray[NumOfCarGenerators].Setup(x, y, z, angle, mi, color1, color2, force, alarm, lock, min_delay, max_delay);
	return NumOfCarGenerators++;
}

void CTheCarGenerators::Init()
{
	GenerateEvenIfPlayerIsCloseCounter = 0;
	NumOfCarGenerators = 0;
	ProcessCounter = 0;
	CurrentActiveCount = 0;
}

void CTheCarGenerators::SaveAllCarGenerators(uint8 *buffer, uint32 *size)
{
	*size = 28 + 72 * NUM_CARGENS;
	buffer[0] = 'C';
	buffer[1] = 'G';
	buffer[2] = 'N';
	buffer[3] = '\0';
	*(uint32*)(buffer + 4) = *size - 8;
	*(uint32*)(buffer + 8) = 12; /* what is this? */
	*(uint32*)(buffer + 12) = NumOfCarGenerators;
	*(uint32*)(buffer + 16) = CurrentActiveCount;
	*(uint8*)(buffer + 20) = ProcessCounter;
	*(uint8*)(buffer + 21) = GenerateEvenIfPlayerIsCloseCounter;
	*(uint16*)(buffer + 22) = 0;
	*(uint32*)(buffer + 24) = 72 * NUM_CARGENS;
	buffer += 28;
	for (int i = 0; i < NUM_CARGENS; i++){
		CarGeneratorArray[i].Save(buffer);
		buffer += 72;
	}
}

void CTheCarGenerators::LoadAllCarGenerators(uint8* buffer, uint32 size)
{
	Init();
	assert(size == 28 + NUM_CARGENS * 72);
	assert(buffer[0] == 'C');
	assert(buffer[1] == 'G');
	assert(buffer[2] == 'N');
	assert(buffer[3] == '\0');
	assert(*(uint32*)(buffer + 4) == size - 8);
	NumOfCarGenerators = *(uint32*)(buffer + 12);
	CurrentActiveCount = *(uint32*)(buffer + 16);
	ProcessCounter = *(uint8*)(buffer + 20);
	GenerateEvenIfPlayerIsCloseCounter = *(uint8*)(buffer + 21);
	assert(*(uint32*)(buffer + 24) == 72 * NUM_CARGENS);
	buffer += 28;
	for (int i = 0; i < NUM_CARGENS; i++) {
		CarGeneratorArray[i].Load(buffer);
		buffer += 72;
	}
}

STARTPATCHES
InjectHook(0x543020, CTheCarGenerators::Init, PATCH_JUMP);
InjectHook(0x542F40, CTheCarGenerators::Process, PATCH_JUMP);
InjectHook(0x543050, CTheCarGenerators::SaveAllCarGenerators, PATCH_JUMP);
InjectHook(0x5431E0, CTheCarGenerators::LoadAllCarGenerators, PATCH_JUMP);
ENDPATCHES
