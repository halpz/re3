#include "common.h"
#include "patcher.h"
#include "Transmission.h"

void
cTransmission::InitGearRatios(void)
{
	static tGear *pGearRatio0 = nil;
	static tGear *pGearRatio1 = nil;
	int i;
	float velocityDiff;

	memset(Gears, 0, sizeof(Gears));

	for(i = 1; i <= nNumberOfGears; i++){
		pGearRatio0 = &Gears[i-1];
		pGearRatio1 = &Gears[i];

		pGearRatio1->fMaxVelocity = (float)i / nNumberOfGears * fMaxVelocity;

		velocityDiff = pGearRatio1->fMaxVelocity - pGearRatio0->fMaxVelocity;

		if(i >= nNumberOfGears){
			pGearRatio1->fShiftUpVelocity = fMaxVelocity;
		}else{
			Gears[i+1].fShiftDownVelocity = velocityDiff*0.42f + pGearRatio0->fMaxVelocity;
			pGearRatio1->fShiftUpVelocity = velocityDiff*0.6667f + pGearRatio0->fMaxVelocity;
		}
	}

	// Reverse gear
	Gears[0].fMaxVelocity = fMaxReverseVelocity;
	Gears[0].fShiftUpVelocity = -0.01f;
	Gears[0].fShiftDownVelocity = fMaxReverseVelocity;

	Gears[1].fShiftDownVelocity = -0.01f;
}

void
cTransmission::CalculateGearForSimpleCar(float speed, uint8 &gear)
{
	static tGear *pGearRatio = &Gears[gear];
	fCurVelocity = speed;
	if(speed > pGearRatio->fShiftUpVelocity)
		gear++;
	else if(speed < pGearRatio->fShiftDownVelocity){
		if(gear - 1 < 0)
			gear = 0;
		else
			gear--;
	}
}
