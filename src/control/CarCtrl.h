#pragma once

class CVehicle;

class CCarCtrl
{
public:
	static void SwitchVehicleToRealPhysics(CVehicle*);
	static void AddToCarArray(int id, int vehclass);
	static void UpdateCarCount(CVehicle*, bool);

	static int32 &NumLawEnforcerCars;
};
