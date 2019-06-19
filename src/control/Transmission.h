#pragma once

struct tGear
{
	float fMaxVelocity;
	float fShiftUpVelocity;
	float fShiftDownVelocity;
};

class cTransmission
{
public:
	// Gear 0 is reverse, 1-5 are forward
	tGear Gears[6];
	char nDriveType;
	char nEngineType;
	int8 nNumberOfGears;
	uint8 Flags;
	float fEngineAcceleration;
	float fMaxVelocity;
	float fUnkMaxVelocity;
	float fMaxReverseVelocity;
	float field_5C;

	void InitGearRatios(void);
};
