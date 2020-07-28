#pragma once

class CPedPlacement {
public:
	static bool FindZCoorForPed(CVector* pos);
	static CEntity* IsPositionClearOfCars(Const CVector*);
	static bool IsPositionClearForPed(const CVector& pos, float radius = -1.0f, int total = -1, CEntity** entities = nil);
};