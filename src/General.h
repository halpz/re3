#pragma once

class CGeneral
{
public:
	static float GetATanOfXY(float x, float y){
//	why exactly doesn't this work?
//		if(y >= 0.0f) return atan2(x, y);
//		return atan2(x, y) + 2*M_PI;

		if(x == 0.0f && y == 0.0f)
			return 0.0f;
		float xabs = fabs(x);
		float yabs = fabs(y);

		if(xabs < yabs){
			if(y > 0.0f){
				if(x > 0.0f)
					return 0.5f*PI - atan2(x / y, 1.0f);
				else
					return 0.5f*PI + atan2(-x / y, 1.0f);
			}else{
				if(x > 0.0f)
					return 1.5f*PI + atan2(x / -y, 1.0f);
				else
					return 1.5f*PI - atan2(-x / -y, 1.0f);
			}
		}else{
			if(y > 0.0f){
				if(x > 0.0f)
					return atan2(y / x, 1.0f);
				else
					return PI - atan2(y / -x, 1.0f);
			}else{
				if(x > 0.0f)
					return 2.0f*PI - atan2(-y / x, 1.0f);
				else
					return PI + atan2(-y / -x, 1.0f);
			}
		}
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

	static float GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		if (y == 0.0f)
			y = 0.0001f;

		if (x > 0.0f) {
			if (y > 0.0f)
				return PI - atan2(x / y, 1.0f);
			else
				return -atan2(x / y, 1.0f);
		} else {
			if (y > 0.0f)
				return -(PI + atan2(x / y, 1.0f));
			else
				return -atan2(x / y, 1.0f);
		}
	}

	// not too sure about all these...
	static uint16 GetRandomNumber(void)
		{ return myrand() & 0xFFFF; }
	// Probably don't want to ever reach high
	static float GetRandomNumberInRange(float low, float high)
		{ return low + (high - low)*(GetRandomNumber()/float(MYRAND_MAX + 1)); }
		
	static int32 GetRandomNumberInRange(int32 low, int32 high)
		{ return low + (high - low)*(GetRandomNumber()/float(MYRAND_MAX + 1)); }
};
