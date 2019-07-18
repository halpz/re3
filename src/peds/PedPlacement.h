#pragma once

class CVector;
class CEntity;

class CPedPlacement {
public:
	static void FindZCoorForPed(CVector* pos);
	static CEntity* IsPositionClearOfCars(CVector*);
};