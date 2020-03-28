#pragma once

class CPedPlacement {
public:
	static void FindZCoorForPed(CVector* pos);
	static CEntity* IsPositionClearOfCars(CVector*);
	static bool IsPositionClearForPed(CVector*);
};