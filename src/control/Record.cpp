#include "common.h"

#include "Record.h"

#include "FileMgr.h"
#include "Pad.h"
#include "Pools.h"
#include "Streaming.h"
#include "Timer.h"
#include "VehicleModelInfo.h"
#include "World.h"

uint16 CRecordDataForGame::RecordingState;

void CRecordDataForGame::Init(void)
{
	RecordingState = STATE_NONE;
}

void CRecordDataForGame::SaveOrRetrieveDataForThisFrame(void)
{
}

uint8* CRecordDataForGame::PackCurrentPadValues(uint8* buf, CControllerState* os, CControllerState* ns)
{
	return nil;
}

uint8* CRecordDataForGame::UnPackCurrentPadValues(uint8* buf, uint8 total, CControllerState* state)
{
	return nil;
}

uint16 CRecordDataForGame::CalcGameChecksum(void)
{
	return 0;
}

uint8 CRecordDataForChase::Status;

void CRecordDataForChase::Init(void)
{
	Status = STATE_NONE;
}

void CRecordDataForChase::SaveOrRetrieveDataForThisFrame(void)
{
}

void CRecordDataForChase::SaveOrRetrieveCarPositions(void)
{
}

void CRecordDataForChase::StoreInfoForCar(CAutomobile* pCar, CCarStateEachFrame* pState)
{
}

void CRecordDataForChase::RestoreInfoForMatrix(CMatrix& matrix, CCarStateEachFrame* pState)
{
}

void CRecordDataForChase::RestoreInfoForCar(CAutomobile* pCar, CCarStateEachFrame* pState, bool stop)
{
}

void CRecordDataForChase::ProcessControlCars(void)
{
}

bool CRecordDataForChase::ShouldThisPadBeLeftAlone(uint8 pad)
{
	return false;
}

void CRecordDataForChase::GiveUsACar(int32 mi, CVector pos, float angle, CAutomobile** ppCar, uint8 colour1, uint8 colour2)
{
}

void RemoveUnusedCollision(void)
{
}

void CRecordDataForChase::StartChaseScene(float startTime)
{
}

void CRecordDataForChase::CleanUpChaseScene(void)
{
}

void CRecordDataForChase::SetUpCarsForChaseScene(void)
{
}

void CRecordDataForChase::CleanUpCarsForChaseScene(void)
{
}

void CRecordDataForChase::RemoveCarFromChase(int32 i)
{
}

CVehicle* CRecordDataForChase::TurnChaseCarIntoScriptCar(int32 i)
{
	return nil;
}

