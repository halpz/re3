#pragma once

class CVehicle;

class CCarAI
{
public:
	static void UpdateCarAI(CVehicle*);
	static void MakeWayForCarWithSiren(CVehicle *veh);
};
