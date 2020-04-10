#pragma once

class CAutomobile;
class CVehicle;
class CControllerState;

enum {
	RECORDSTATE_0,
	RECORDSTATE_1,
	RECORDSTATE_2,
};

class CRecordDataForChase
{
	enum {
		NUM_CHASE_CARS = 20
	};
public:
	static uint8 &Status;
	static int &PositionChanges;
	static uint8 &CurrentCar;
	static CAutomobile*(&pChaseCars)[NUM_CHASE_CARS];
	static uint32 &AnimStartTime;

	static void SaveOrRetrieveDataForThisFrame(void);
	static void ProcessControlCars(void);
	static void SaveOrRetrieveCarPositions(void);
	static void StartChaseScene(float);
	static void CleanUpChaseScene();
	static void RemoveCarFromChase(int32);
	static CVehicle* TurnChaseCarIntoScriptCar(int32);
	static void Init(void);
};

struct tGameBuffer
{
	float m_fTimeStep;
	uint32 m_nTimeInMilliseconds;
	uint8 m_nSizeOfPads[2];
	uint16 m_nChecksum;
	uint8 m_ControllerBuffer[116];
};

class CRecordDataForGame
{
	enum {
		STATE_NONE = 0,
		STATE_RECORD = 1,
		STATE_PLAYBACK = 2,
	};
	static uint16& RecordingState;
	static uint8* &pDataBuffer;
	static uint8* &pDataBufferPointer;
	static int &FId;
	static tGameBuffer &pDataBufferForFrame;

public:
	static bool IsRecording() { return RecordingState == STATE_RECORD; }
	static bool IsPlayingBack() { return RecordingState == STATE_PLAYBACK; }

	static void SaveOrRetrieveDataForThisFrame(void);
	static void Init(void);

private:
	static uint16 CalcGameChecksum(void);
	static uint8* PackCurrentPadValues(uint8*, CControllerState*, CControllerState*);
	static uint8* UnPackCurrentPadValues(uint8*, uint8, CControllerState*);
};
