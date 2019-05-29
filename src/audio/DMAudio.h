#pragma once

class CEntity;

class cDMAudio
{
public:
	void ReportCollision(CEntity *A, CEntity *B, uint8 surfA, uint8 surfB, float impulse, float speed);
	void ResetTimers(UInt32 timerval); 
};
extern cDMAudio &DMAudio;
