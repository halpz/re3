#pragma once

class CVehicle;

class CCarCtrl
{
public:
	static void SwitchVehicleToRealPhysics(CVehicle*);
	static void AddToCarArray(int32 id, int32 vehclass);
	static void UpdateCarCount(CVehicle*, bool);
	static int32 ChooseCarModel(int32 vehclass);

	static int32 &NumLawEnforcerCars;
};
