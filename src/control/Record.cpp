#include "common.h"
#include "patcher.h"
#include "Record.h"

#include "FileMgr.h"
#include "Pad.h"
#include "Pools.h"
#include "Timer.h"

uint16 &CRecordDataForGame::RecordingState = *(uint16*)0x95CC24;
uint8*& CRecordDataForGame::pDataBuffer = *(uint8**)0x8F1B70;
uint8*& CRecordDataForGame::pDataBufferPointer = *(uint8**)0x8F1AB0;
int& CRecordDataForGame::FId = *(int*)0x885BA4;
tGameBuffer& CRecordDataForGame::pDataBufferForFrame = *(tGameBuffer*)0x72CED0;

uint8 &CRecordDataForChase::Status = *(uint8*)0x95CDCE;

#define MEMORY_FOR_GAME_RECORD (150000)

void CRecordDataForGame::Init(void)
{
	RecordingState = STATE_NONE;
	if (pDataBuffer)
		delete[] pDataBuffer;
	pDataBufferPointer = nil;
	pDataBuffer = nil;
#ifndef GTA_PS2 // this stuff is not present on PS2
	FId = CFileMgr::OpenFile("playback.dat", "r");
	if (FId <= 0) {
		if ((FId = CFileMgr::OpenFile("record.dat", "r")) <= 0)
			RecordingState = STATE_NONE;
		else {
			CFileMgr::CloseFile(FId);
			FId = CFileMgr::OpenFileForWriting("record.dat");
			RecordingState = STATE_RECORD;
		}
	}
	else {
		RecordingState = STATE_PLAYBACK;
	}
	if (RecordingState == STATE_PLAYBACK) {
		pDataBufferPointer = (uint8*)malloc(MEMORY_FOR_GAME_RECORD);
		pDataBuffer = pDataBufferPointer;
		pDataBuffer[CFileMgr::Read(FId, (char*)pDataBufferPointer, MEMORY_FOR_GAME_RECORD) + 8] = -1;
		CFileMgr::CloseFile(FId);
	}
#else
	RecordingState = STATE_NONE; // second time to make sure
#endif
}

void CRecordDataForGame::SaveOrRetrieveDataForThisFrame(void)
{
	switch (RecordingState) {
	case STATE_RECORD:
	{
		pDataBufferForFrame.m_fTimeStep = CTimer::GetTimeStep();
		pDataBufferForFrame.m_nTimeInMilliseconds = CTimer::GetTimeInMilliseconds();
		pDataBufferForFrame.m_nSizeOfPads[0] = 0;
		pDataBufferForFrame.m_nSizeOfPads[1] = 0;
		pDataBufferForFrame.m_nChecksum = CalcGameChecksum();
		uint8* pController1 = PackCurrentPadValues(pDataBufferForFrame.m_ControllerBuffer, &CPad::GetPad(0)->OldState, &CPad::GetPad(0)->NewState);
		pDataBufferForFrame.m_nSizeOfPads[0] = (pController1 - pDataBufferForFrame.m_ControllerBuffer) / 2;
		uint8* pController2 = PackCurrentPadValues(pController1, &CPad::GetPad(1)->OldState, &CPad::GetPad(1)->NewState);
		pDataBufferForFrame.m_nSizeOfPads[1] = (pController2 - pController1) / 2;
		uint8* pEndPtr = pController2;
		if ((pDataBufferForFrame.m_nSizeOfPads[0] + pDataBufferForFrame.m_nSizeOfPads[1]) & 1)
			pEndPtr += 2;
		CFileMgr::Write(FId, (char*)&pDataBufferForFrame, pEndPtr - (uint8*)&pDataBufferForFrame);
		break;
	}
	case STATE_PLAYBACK:
		if (pDataBufferPointer[8] == -1)
			CPad::GetPad(0)->NewState.Clear();
		else {
			tGameBuffer* pData = (tGameBuffer*)pDataBufferPointer;
			CTimer::SetTimeInMilliseconds(pData->m_nTimeInMilliseconds);
			CTimer::SetTimeStep(pData->m_fTimeStep);
			uint8 size1 = pData->m_nSizeOfPads[0];
			uint8 size2 = pData->m_nSizeOfPads[1];
			pDataBufferPointer = (uint8*)&pData->m_ControllerBuffer;
			pDataBufferPointer = UnPackCurrentPadValues(pDataBufferPointer, size1, &CPad::GetPad(0)->NewState);
			pDataBufferPointer = UnPackCurrentPadValues(pDataBufferPointer, size2, &CPad::GetPad(1)->NewState);
			if ((size1 + size2) & 1)
				pDataBufferPointer += 2;
			if (pData->m_nChecksum != CalcGameChecksum())
				printf("Playback out of sync\n");
		}
	}
}

#define PROCESS_BUTTON_STATE_STORE(buf, os, ns, field, id) \
	do { \
		if (os->field != os->field){ \
			*buf++ = id; \
			*buf++ = ns->field; \
		} \
	} while (0);

uint8* CRecordDataForGame::PackCurrentPadValues(uint8* buf, CControllerState* os, CControllerState* ns)
{
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, LeftStickX, 0);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, LeftStickY, 1);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, LeftShoulder1, 2);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, RightStickY, 3);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, LeftShoulder1, 4);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, LeftShoulder2, 5);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, RightShoulder1, 6);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, RightShoulder2, 7);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, DPadUp, 8);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, DPadDown, 9);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, DPadLeft, 10);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, DPadRight, 11);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, Start, 12);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, Select, 13);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, Square, 14);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, Triangle, 15);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, Cross, 16);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, Circle, 17);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, LeftShock, 18);
	PROCESS_BUTTON_STATE_STORE(buf, os, ns, RightShock, 19);
	return buf;
}
#undef PROCESS_BUTTON_STATE_STORE

#define PROCESS_BUTTON_STATE_RESTORE(buf, state, field, id) case id: state->field = *buf++; break;

uint8* CRecordDataForGame::UnPackCurrentPadValues(uint8* buf, uint8 total, CControllerState* state)
{
	for (uint8 i = 0; i < total; i++) {
		switch (*buf++) {
			PROCESS_BUTTON_STATE_RESTORE(buf, state, LeftStickX, 0);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, LeftStickY, 1);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, LeftShoulder1, 2);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, RightStickY, 3);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, LeftShoulder1, 4);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, LeftShoulder2, 5);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, RightShoulder1, 6);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, RightShoulder2, 7);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, DPadUp, 8);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, DPadDown, 9);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, DPadLeft, 10);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, DPadRight, 11);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, Start, 12);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, Select, 13);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, Square, 14);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, Triangle, 15);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, Cross, 16);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, Circle, 17);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, LeftShock, 18);
			PROCESS_BUTTON_STATE_RESTORE(buf, state, RightShock, 19);
		}
	}
	return buf;
}

#undef PROCESS_BUTTON_STATE_RESTORE

uint16 CRecordDataForGame::CalcGameChecksum(void)
{
	uint32 checksum = 0;
	int i = CPools::GetPedPool()->GetSize();
	while (i--) {
		CPed* pPed = CPools::GetPedPool()->GetSlot(i);
		if (!pPed)
			continue;
		checksum ^= pPed->GetModelIndex() ^ *(uint32*)&pPed->GetPosition().z ^ *(uint32*)&pPed->GetPosition().y ^ *(uint32*)&pPed->GetPosition().x;
	}
	i = CPools::GetVehiclePool()->GetSize();
	while (i--) {
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
		if (!pVehicle)
			continue;
		checksum ^= pVehicle->GetModelIndex() ^ *(uint32*)&pVehicle->GetPosition().z ^ *(uint32*)&pVehicle->GetPosition().y ^ *(uint32*)&pVehicle->GetPosition().x;
	}
	return checksum ^ checksum >> 16;
}

WRAPPER void CRecordDataForChase::Init(void)
{
	EAXJMP(0x434780);
}

WRAPPER void CRecordDataForChase::SaveOrRetrieveDataForThisFrame(void) { EAXJMP(0x4347F0); }
WRAPPER void CRecordDataForChase::ProcessControlCars(void) { EAXJMP(0x435540); }
WRAPPER void CRecordDataForChase::SaveOrRetrieveCarPositions(void) { EAXJMP(0x434B20); }
WRAPPER void CRecordDataForChase::StartChaseScene(float) { EAXJMP(0x435690); }
WRAPPER void CRecordDataForChase::CleanUpChaseScene() { EAXJMP(0x4357C0); }
WRAPPER void CRecordDataForChase::RemoveCarFromChase(int32) { EAXJMP(0x435BC0); }
WRAPPER CVehicle* CRecordDataForChase::TurnChaseCarIntoScriptCar(int32) { EAXJMP(0x435C00); }

