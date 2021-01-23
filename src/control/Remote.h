#pragma once

class CRemote
{
public:
	static CVehicle* GivePlayerRemoteControlledCar(float, float, float, float, uint16);
	static void TakeRemoteControlledCarFromPlayer(bool blowUp = true);
};
