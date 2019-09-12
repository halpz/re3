#include "common.h"
#include "patcher.h"
#include "Record.h"

uint16 &CRecordDataForGame::RecordingState = *(uint16*)0x95CC24;

uint8 &CRecordDataForChase::Status = *(uint8*)0x95CDCE;

WRAPPER void CRecordDataForChase::ProcessControlCars(void) { EAXJMP(0x435540); }
WRAPPER void CRecordDataForChase::SaveOrRetrieveCarPositions(void) { EAXJMP(0x434B20); }