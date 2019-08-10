#pragma once

class CGeneral
{
public:
	static float GetATanOfXY(float x, float y){
		if(x == 0.0f && y == 0.0f)
			return 0.0f;
		float xabs = Abs(x);
		float yabs = Abs(y);

		if(xabs < yabs){
			if(y > 0.0f){
				if(x > 0.0f)
					return 0.5f*PI - Atan2(x / y, 1.0f);
				else
					return 0.5f*PI + Atan2(-x / y, 1.0f);
			}else{
				if(x > 0.0f)
					return 1.5f*PI + Atan2(x / -y, 1.0f);
				else
					return 1.5f*PI - Atan2(-x / -y, 1.0f);
			}
		}else{
			if(y > 0.0f){
				if(x > 0.0f)
					return Atan2(y / x, 1.0f);
				else
					return PI - Atan2(y / -x, 1.0f);
			}else{
				if(x > 0.0f)
					return 2.0f*PI - Atan2(-y / x, 1.0f);
				else
					return PI + Atan2(-y / -x, 1.0f);
			}
		}
	}

	static float LimitAngle(float angle)
	{
		float result = angle;

		while (result >= 180.0f) {
			result -= 2 * 180.0f;
		}

		while (result < -180.0f) {
			result += 2 * 180.0f;
		}

		return result;
	}


	static float LimitRadianAngle(float angle)
	{
		float result;

		if (angle < -25.0f)
			result = -25.0f;
		else if (angle > 25.0f)
			result = 25.0f;
		else
			result = angle;

		while (result >= PI) {
			result -= 2 * PI;
		}

		while (result < -PI) {
			result += 2 * PI;
		}
	
		return result;
	}

	// Returns an angle such that x2/y2 looks at x1/y1 with its forward vector if rotated by that angle
	static float GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		if (y == 0.0f)
			y = 0.0001f;

		if (x > 0.0f) {
			if (y > 0.0f)
				return PI - Atan2(x / y, 1.0f);
			else
				return -Atan2(x / y, 1.0f);
		} else {
			if (y > 0.0f)
				return -(PI + Atan2(x / y, 1.0f));
			else
				return -Atan2(x / y, 1.0f);
		}
	}

	// not too sure about all these...
	static uint16 GetRandomNumber(void)
		{ return myrand() & MYRAND_MAX; }
	static bool GetRandomTrueFalse(void)
		{ return GetRandomNumber() < MYRAND_MAX / 2; }
	// Probably don't want to ever reach high
	static float GetRandomNumberInRange(float low, float high)
		{ return low + (high - low)*(GetRandomNumber()/float(MYRAND_MAX + 1)); }
		
	static int32 GetRandomNumberInRange(int32 low, int32 high)
		{ return low + (high - low)*(GetRandomNumber()/float(MYRAND_MAX + 1)); }
};
