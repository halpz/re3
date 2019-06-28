#pragma once

enum {
	RECORDSTATE_0,
	RECORDSTATE_1,
	RECORDSTATE_2,
};

class CRecordDataForGame
{
public:
	static uint16 &RecordingState;
};

class CRecordDataForChase
{
public:
	static uint8 &Status;
};
