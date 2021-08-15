#include "common.h"

#include "Timer.h"
#include "HandlingMgr.h"
#include "Transmission.h"

//--LCS: file done
void
cTransmission::InitGearRatios(void)
{
	static tGear *pGearRatio0 = nil;
	static tGear *pGearRatio1 = nil;
	int i;
	float velocityDiff;

	memset(Gears, 0, sizeof(Gears));

	float baseVelocity = 0.5f*fMaxVelocity / nNumberOfGears;
	float step = (fMaxVelocity - baseVelocity) / nNumberOfGears;

	for(i = 1; i <= nNumberOfGears; i++){
		pGearRatio0 = &Gears[i-1];
		pGearRatio1 = &Gears[i];

		pGearRatio1->fMaxVelocity = baseVelocity + i*step;

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
	static tGear *pGearRatio;

	pGearRatio = &Gears[gear];
	fCurVelocity = speed;
	if(speed > pGearRatio->fShiftUpVelocity){
		if(gear + 1 > nNumberOfGears)
			gear = nNumberOfGears;
		else
			gear++;
	}else if(speed < pGearRatio->fShiftDownVelocity){
		if(gear - 1 < 0)
			gear = 0;
		else
			gear--;
	}
}

float TRANSMISSION_NITROS_INERTIA_MULT = 0.5f;
float TRANSMISSION_AI_CHEAT_INERTIA_MULT = 0.75f;
float TRANSMISSION_NITROS_MULT = 2.0f;
float TRANSMISSION_AI_CHEAT_MULT = 1.2f;
float TRANSMISSION_SMOOTHER_FRAC = 0.85f;
float TRANSMISSION_FREE_ACCELERATION = 0.1f;

float
cTransmission::CalculateDriveAcceleration(const float &gasPedal, uint8 &gear, float &time, const float &velocity, float *inertiaVar1, float *inertiaVar2, uint8 nDriveWheels, uint8 cheat)
{
	static float fAcceleration = 0.0f;
	static float fVelocity;
	static float fCheat;
	static tGear *pGearRatio;

	fVelocity = velocity;
	if(fVelocity < fMaxReverseVelocity)
		return 0.0f;
	if(fVelocity > fMaxVelocity)
		return 0.0f;
	fCurVelocity = fVelocity;

	assert(gear <= nNumberOfGears);

	pGearRatio = &Gears[gear];
	if(fVelocity > pGearRatio->fShiftUpVelocity){
		if(gear != 0 || gasPedal > 0.0f){
			gear++;
			return CalculateDriveAcceleration(gasPedal, gear, time, fVelocity, nil, nil, 0, false);
		}
	}else if(fVelocity < pGearRatio->fShiftDownVelocity && gear != 0){
		if(gear != 1 || gasPedal < 0.0f){
			gear--;
			return CalculateDriveAcceleration(gasPedal, gear, time, fVelocity, nil, nil, 0, false);
		}
	}

	float accelMul;

	if(nNumberOfGears == 1){
		accelMul = 1.0f;
	}else if(gear == 0){
		accelMul = 4.5f;
	}else{
		float f = 1.0f - (gear-1.0f)/(nNumberOfGears-1.0f);
		if(Flags & HANDLING_1G_BOOST)
			accelMul = SQR(f)*5.0f + 1.0f;
		else if(Flags & HANDLING_2G_BOOST)
			accelMul = SQR(f)*4.0f + 1.0f;
		else
			accelMul = SQR(f)*3.0f + 1.0f;
	}

	fCheat = 1.0f;
	float nitroMult = 1.0f;
	if(cheat == 1)
		fCheat = TRANSMISSION_AI_CHEAT_MULT;
	else if(cheat == 2)
		nitroMult = TRANSMISSION_NITROS_MULT;

	fAcceleration = fEngineAcceleration*CTimer::GetTimeStep()*0.4f*accelMul*gasPedal*fCheat*nitroMult;

	if(inertiaVar1 != nil && inertiaVar2 != nil){
		if(nDriveWheels == 0){
			float f = TRANSMISSION_FREE_ACCELERATION*CTimer::GetTimeStep()*Abs(gasPedal)/fEngineInertia;
			*inertiaVar1 = Min(*inertiaVar1 + f, 1.0f);
			*inertiaVar2 = 0.1f;
		}else{
			float var1;
			// What is being calculated here?
			// TODO: find better names for the inertia vars
			if(gear == 0){
				var1 = ((fMaxVelocity/nNumberOfGears)*(1.0f-0.6667f) - fVelocity) /
				       ((fMaxVelocity/nNumberOfGears)*(1.0f-0.6667f) - Gears[gear].fShiftDownVelocity);
			}else if(gear == 1){
				var1 = ((fMaxVelocity/nNumberOfGears)*(1.0f-0.6667f) + fVelocity) /
				       ((fMaxVelocity/nNumberOfGears)*(1.0f-0.6667f) + Gears[gear].fShiftUpVelocity);
			}else{
				var1 = (fVelocity - Gears[gear].fShiftDownVelocity) /
				       (Gears[gear].fShiftUpVelocity - Gears[gear].fShiftDownVelocity);
			}
			float inertiaMult = var1 - *inertiaVar1;
			if(cheat == 1)
				inertiaMult *= TRANSMISSION_AI_CHEAT_INERTIA_MULT;
			else if(cheat == 2)
				inertiaMult *= TRANSMISSION_NITROS_INERTIA_MULT;
			float var2target = 1.0f - inertiaMult*fEngineInertia;
			var2target = Clamp(var2target, 0.1f, 1.0f);
			*inertiaVar2 = (1.0f-TRANSMISSION_SMOOTHER_FRAC)*var2target + TRANSMISSION_SMOOTHER_FRAC*(*inertiaVar2);
			*inertiaVar1 = var1;
			fAcceleration *= *inertiaVar2;
		}
	}

	float targetVelocity = Gears[gear].fMaxVelocity*fCheat;
	if(Gears[gear].fMaxVelocity < 0.0f && targetVelocity > fVelocity)
		fAcceleration *= 1.0f - Min((targetVelocity - fVelocity)/0.05f, 1.0f);
	else if(Gears[gear].fMaxVelocity > 0.0f && targetVelocity < fVelocity)
		fAcceleration *= 1.0f - Min((fVelocity - targetVelocity)/0.05f, 1.0f);
	return fAcceleration;
}

// TEMP old VC code until we have bikes
float
cTransmission::CalculateDriveAcceleration(const float &gasPedal, uint8 &gear, float &time, const float &velocity, bool cheat)
{
	static float fAcceleration = 0.0f;
	static float fVelocity;
	static float fCheat;
	static tGear *pGearRatio;

	fVelocity = velocity;
	if(fVelocity < fMaxReverseVelocity){
		fVelocity = fMaxReverseVelocity;
		return 0.0f;
	}
	if(fVelocity > fMaxVelocity){
		fVelocity = fMaxVelocity;
		return 0.0f;
	}
	fCurVelocity = fVelocity;

	assert(gear <= nNumberOfGears);

	pGearRatio = &Gears[gear];
	if(fVelocity > pGearRatio->fShiftUpVelocity){
		if(gear != 0 || gasPedal > 0.0f){
			gear++;
			return CalculateDriveAcceleration(gasPedal, gear, time, fVelocity, false);
		}
	}else if(fVelocity < pGearRatio->fShiftDownVelocity && gear != 0){
		if(gear != 1 || gasPedal < 0.0f){
			gear--;
			return CalculateDriveAcceleration(gasPedal, gear, time, fVelocity, false);
		}
	}

	float speedMul, accelMul;

	if(gear < 1){
		// going reverse
		accelMul = (Flags & HANDLING_2G_BOOST) ? 2.0f : 1.0f;
		speedMul = -1.0f;
	}else if(nNumberOfGears == 1){
		accelMul = 1.0f;
		speedMul = 1.0f;
	}else{
		// BUG or not? this is 1.0 normally but 0.0 in the highest gear
		float f = 1.0f - (gear-1)/(nNumberOfGears-1);
		speedMul = 3.0f*sq(f) + 1.0f;
		// This is pretty ugly, could be written more clearly
		if(Flags & HANDLING_2G_BOOST){
			if(gear == 1)
				accelMul = (Flags & HANDLING_1G_BOOST) ? 2.0f : 1.6f;
			else if(gear == 2)
				accelMul = 1.3f;
			else
				accelMul = 1.0f;
		}else if(Flags & HANDLING_1G_BOOST && gear == 1){
			accelMul = 2.0f;
		}else
			accelMul = 1.0f;
	}

	if(cheat)
		fCheat = 1.2f;
	else
		fCheat = 1.0f;
	float targetVelocity = Gears[gear].fMaxVelocity*speedMul*fCheat;
	float accel = (targetVelocity - fVelocity) * (fEngineAcceleration*accelMul) / Abs(targetVelocity);
	if(Abs(fVelocity) < Abs(Gears[gear].fMaxVelocity*fCheat))
		fAcceleration = gasPedal * accel * CTimer::GetTimeStep();
	else
		fAcceleration = 0.0f;
	return fAcceleration;
}
